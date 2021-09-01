#include "main.h"

#include <stdio.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#include "mcu/twi.h"
#include "mcu/spi.h"
#include "drivers/sen0313.h"

#define SENSOR_ENABLE_PORT PORTA
#define SENSOR_ENABLE_PIN PIN5

sen0313_t sen0313 = {
    .tx_port = &PORTB,
    .tx_pin = PIN2,
    .mode = SEN0313_MODE_RAW,
};

void sensors_on(void)
{
  SENSOR_ENABLE_PORT.OUTSET = (1 << SENSOR_ENABLE_PIN);
}

void sensors_off(void)
{
  SENSOR_ENABLE_PORT.OUTCLR = (1 << SENSOR_ENABLE_PIN);
}

int main(void)
{
  sei();
  SENSOR_ENABLE_PORT.DIRSET = 1 << SENSOR_ENABLE_PIN;
  PORTA.DIRSET = PIN6_bm; // SMBAlert
  sensors_on();

  spi_init();

  sen0313_init(&sen0313);

  // Infinite loop
  for (;;)
  {
    uint16_t dist_mm = sen0313_read(&sen0313);
    spi_transfer(dist_mm >> 8);
    spi_transfer(dist_mm);

    for (uint32_t i = 0; i < 500000; i++)
      __asm("nop");
  }
}

twi_cmd_t twi_cmds[] = {
    // {0x10, twi_cmd_10_handler},
};