#include <avr/io.h>
#include <avr/xmega.h>
#include <mcu/util.h>

#define LED_PORT PORTA
#define LED_PIN PIN6
int main(void)
{
  // Prescaler
  // _PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, CLKCTRL_PDIV_4X_gc | CLKCTRL_PEN_bm);
  delay_init();

  LED_PORT.DIRSET = 1 << LED_PIN;
  LED_PORT.OUTCLR = 1 << LED_PIN;

  for (;;)
  {
    delay_ms(500);
    LED_PORT.OUTTGL = 1 << LED_PIN;
  }
}