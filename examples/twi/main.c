#include <avr/io.h>

#include "mcu/twi.h"

#define LED_PORT PORTA
#define LED_PIN PIN6
#define SENSOR_PWR_PORT PORTA
#define SENSOR_PWR_PIN PIN5

int main(void)
{
  SENSOR_PWR_PORT.DIRSET = 1 << SENSOR_PWR_PIN;
  SENSOR_PWR_PORT.OUTCLR = 1 << SENSOR_PWR_PIN;
  LED_PORT.DIRSET = 1 << LED_PIN;

  twi_init(0x36);
}

void twi_cmd_10_handler(uint8_t *buf, uint8_t len)
{
  LED_PORT.OUTTGL = 1 << LED_PIN;
}

twi_cmd_t twi_cmds[] = {
    {0x10, &twi_cmd_10_handler},
};