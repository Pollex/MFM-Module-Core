#include "main.h"

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "ev_events.h"
#include "events.h"
#include "twi.h"

int main(void)
{
  sei();
  twi_init();

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