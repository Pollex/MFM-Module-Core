#ifdef BOARD_MODULE

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "main.h"
#include "events.h"

int main(void)
{
  sei();
  init_twi();

  PORTA.DIRSET = PIN6_bm;
  PORTA.OUTCLR = PIN6_bm;

  const ev_t *current_event;

  // Infinite loop
  while (true)
  {
    // Process events
    while ((current_event = ev_dequeue()) != nullptr)
    {
      // Process current event
      switch (current_event->id)
      {
      case EV_TWI_TRAN_START:
        break;
      case EV_TWI_TRAN_END:
        if (twi_available() == 2)
          PORTA.OUTTGL = PIN6_bm;
        break;
      }
    }

    // Skip sleep if there are events pending
    if (ev_pending())
      continue;

    while (TWI0.SSTATUS & ~(0x3) != 0)
    {
      __asm("nop");
    }
    // Sleep
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_cpu();
    sleep_disable();
  }
}

#endif