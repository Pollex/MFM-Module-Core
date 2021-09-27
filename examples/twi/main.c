#include <avr/io.h>
#include <avr/interrupt.h>

#include "mcu/twi.h"

#define LED_PORT PORTA
#define LED_PIN PIN6
#define SENSOR_PWR_PORT PORTA
#define SENSOR_PWR_PIN PIN5

int main(void)
{
  // Enable interrupts
  sei();
  // Set the LED Pin to an output
  LED_PORT.DIRSET = 1 << LED_PIN;
  // Turn off the LED
  LED_PORT.OUTCLR = 1 << LED_PIN;

  // Initialize TWI with our address 0x36 (Will be shifted by the mcu driver)
  twi_init(0x36);

  // Loop forever, allowing interrupts to happen
  for (;;)
    ;
}

// Our handler for cmd 10, keep these as short as possible!
void twi_cmd_10_handler(uint8_t *buf, uint8_t len)
{
  LED_PORT.OUTTGL = 1 << LED_PIN;
}

// Define our TWI commands
twi_cmd_t twi_cmds[] = {
    // 0x10 will fire cmd_10
    {0x10, &twi_cmd_10_handler},
};