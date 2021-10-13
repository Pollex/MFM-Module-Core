#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#include "mcu/twi.h"
#include "perif/sen0313.h"

#define LED_PORT PORTA
#define LED_PIN PIN6
#define SENSOR_PWR_PORT PORTA
#define SENSOR_PWR_PIN PIN5

sen0313_t sen0313 = {
    .mode = SEN0313_MODE_PROCESSED,
    .tx_port = &PORTB,
    .tx_pin = PIN2,
};

int main(void)
{
  // Set LED and SENSOR_PWR pins as outputs
  LED_PORT.DIRSET = 1 << LED_PIN;
  SENSOR_PWR_PORT.DIRSET = 1 << SENSOR_PWR_PIN;

  // Enable sensor power
  SENSOR_PWR_PORT.OUTSET = 1 << SENSOR_PWR_PIN;

  // Initialize sensor
  sen0313_init(&sen0313);

  // Infinite loop
  for (;;)
  {
    // Get distance in millimeter and centimeter
    uint16_t distance_mm = sen0313_read(&sen0313);
    uint8_t distance_cm = distance_mm / 10;

    // Enable LED if distance is less than 40 cm
    if (distance_cm < 40)
    {
      LED_PORT.OUTSET = 1 << LED_PIN;
    }
    else
    {
      LED_PORT.OUTCLR = 1 << LED_PIN;
    }
  }
}

twi_cmd_t twi_cmds[] = {
    // {0x10, twi_cmd_10_handler},
};