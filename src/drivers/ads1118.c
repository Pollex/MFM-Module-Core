#include "drivers/ads1118.h"

#include <avr/io.h>
#include "mcu/spi.h"

#define CS_PORT(ads) (*(ads->cs_port))

static const float fsr_map[] = {
    6.114,
    4.096,
    2.048,
    1.024,
    0.512,
    0.256,
    0.256,
    0.256,
};

#define RESOLUTION(PGA) (fsr_map[PGA] / (float)32768)

spi_t ads1118_spi = {
    .data_order = SPI_DORD_MSB,
    .mode = SPI_MODE_0,
};

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

/**
 * @brief Transfers the config to the ADS1118 and returns the conversion register
 * 
 * @param ads The ADS1118_t struct
 * @return uint16_t Conversion register
 */
uint16_t transfer(ads1118_t *ads)
{
  select(ads);
  uint8_t conv_h = spi_transfer(&ads1118_spi, ads->config.byte.msb);
  uint8_t conv_l = spi_transfer(&ads1118_spi, ads->config.byte.lsb);
  spi_transfer(&ads1118_spi, ads->config.byte.msb);
  spi_transfer(&ads1118_spi, ads->config.byte.lsb);
  deselect(ads);

  return (conv_h << 8) | conv_l;
}

void ads1118_setup(ads1118_t *ads)
{
  transfer(ads);
}

void ads1118_init(ads1118_t *ads)
{
  CS_PORT(ads).DIRSET = 1 << ads->cs_pin;
  deselect(ads);

  spi_init(&ads1118_spi);

  ads1118_setup(ads);
}

float ads1118_read(ads1118_t *ads)
{
  uint8_t is_singleshot = ads->config.fields.mode;
  uint16_t conversion;
  float millivolts;

  if (is_singleshot)
  {
    transfer(ads); // Perform Single Shot measurement
    delay_8us();   // Wait 8 US to complete WARN: Should wait for MOSI to go low...
  }
  conversion = transfer(ads); // Read newest conversion results

  // Calculate the resolution for the chosen gain
  float resolution = RESOLUTION(ads->config.fields.pga);

  // If conversion is a positive temperature (MSB is 0)
  if ((conversion & 0x8000) == 0)
  {
    millivolts = conversion * resolution;
  }
  else
  { // Conversion is a negative number
    conversion = (~(conversion) + 1);
    millivolts = (float)(conversion * resolution) * -1;
  }

  return millivolts;
}