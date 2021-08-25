#include "drivers/ads1118.h"

#include <avr/io.h>
#include "mcu/spi.h"

#define MODE_bm 1 << 0x08
#define RESOLUTION 0.03125

#define CS_PORT(ads) (*(PORT_t *)ads->cs_port)

void select(ads1118_t *ads)
{
  CS_PORT(ads).OUTCLR = 1 << ads->cs_pin;
}
void deselect(ads1118_t *ads)
{
  CS_PORT(ads).OUTSET = 1 << ads->cs_pin;
}

void delay_8us(void)
{
  // Delay 8us. Assuming F_CLK is 20MHz that would mean 160 cycles.
  // Just to be sure we take 200 cycles.
  for (uint8_t ix = 0; ix < 200; ix++)
  {
    __asm("nop");
  }
}

uint16_t transfer(ads1118_t *ads)
{
  uint8_t cfg_h = ads->config >> 8;
  uint8_t cfg_l = ads->config;

  select(ads);
  uint8_t conv_h = spi_transfer(cfg_h);
  uint8_t conv_l = spi_transfer(cfg_l);
  deselect(ads);

  uint16_t conversion = (conv_h << 8) | conv_l;

  float temperature;

  // If conversion is a positive temperature (MSB is 0)
  if ((conversion & 0x8000) == 0)
  {
    temperature = conversion * RESOLUTION;
  }
  else
  { // Conversion is a negative number
    conversion -= 1;
    conversion = ~(conversion);
    temperature = conversion * -RESOLUTION;
  }

  return temperature;
}

void ads1118_init(ads1118_t *ads)
{
  CS_PORT(ads).DIRSET = 1 << ads->cs_pin;
  deselect(ads);
}

float ads1118_read(ads1118_t *ads)
{
  uint8_t is_singleshot = ads->config & MODE_bm;

  if (is_singleshot)
  {
    transfer(ads); // Perform Single Shot measurement
    delay_8us();   // Wait 8 US to complete WARN: Should wait for MOSI to go low...
  }
  return transfer(ads); // Read newest conversion results
}
