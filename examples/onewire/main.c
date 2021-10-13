#define F_CPU 2666666UL

#include <avr/io.h>
#include <drivers/onewire.h>
#include <mcu/util.h>

#define LED_PORT PORTA
#define LED_PIN PIN6

onewire_t ow = {
    .port = &PORTA,
    .pin = 7,
};

int main(void)
{
  // Set LED as output
  LED_PORT.DIRSET = 1 << LED_PIN;
  LED_PORT.OUTCLR = 1 << LED_PIN;
  // Set Onewire as input
  PORTA.OUTCLR = 1 << PIN7;

  // ow_reset returns 1 if there is a device on the bus, otherwise 0
  uint8_t available = ow_reset(&ow);

  // If there are no devices on the bus, do something...
  if (!available)
  {
    // blink: short-on to signify "error"
    for (;;)
    {
      delay_ms(500);
      LED_PORT.OUTSET = 1 << LED_PIN;
      delay_ms(100);
      LED_PORT.OUTCLR = 1 << LED_PIN;
    }
  }

  // This tells the device on the bus to skip address matching
  // Currently this lib assumes there is only 1 device on the bus
  ow_write(&ow, OW_CMD_SKIP);

  // Write some random data
  ow_write(&ow, 0xBE);
  ow_write(&ow, 0xEF);

  // Read a byte
  uint8_t val = ow_read(&ow);

  // 0xff is also returned if no device responded,
  // all bits are left high by the pullup
  if (val == 0xff)
  {
    // Blink: long-on to signify "error"
    for (;;)
    {
      delay_ms(100);
      LED_PORT.OUTSET = 1 << LED_PIN;
      delay_ms(500);
      LED_PORT.OUTCLR = 1 << LED_PIN;
    }
  }

  // blink slow
  for (;;)
  {
    delay_ms(1000);
    LED_PORT.OUTTGL = 1 << LED_PIN;
  }
}