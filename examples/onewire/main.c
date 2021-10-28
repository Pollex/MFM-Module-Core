#include <avr/io.h>
#include <avr/interrupt.h>
#include <drivers/onewire.h>
#include <mcu/util.h>
#include <avr/xmega.h>

#define LED_PORT PORTA
#define LED_PIN PIN6

int main(void)
{
  // _PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, CLKCTRL_PEN_bm | CLKCTRL_PDIV_8X_gc);
  sei();
  // Set Onewire as input
  OW_PORT.DIRCLR = 1 << OW_PIN;

  // Read OneWire device serial
  ow_reset();
  ow_write(OW_CMD_READ);
  ow_read();
  ow_read();
  ow_read();
  ow_read();
  ow_read();
  ow_read();
  ow_read();
  ow_read();

  for (;;)
    ;
}