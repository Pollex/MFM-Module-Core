#include "main.h"

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "ev_events.h"
#include "events.h"
#include "drivers/twi.h"

void process_events(void);

int main(void)
{
  sei();
  twi_init(0x36);

  PORTA.DIRSET = PIN6_bm;
  PORTA.OUTCLR = PIN6_bm;

  // Infinite loop
  for (;;)
    ;
}

void process_events(void)
{
  // Get the next event
  ev_t *current_event = ev_dequeue();
  if (!current_event)
    return;

  // Process current event
  switch (current_event->id)
  {
  // Fired when a command byte is received
  // User must check if the command exists
  case EV_SMBUS_ASSERT_CMD:
    twi_ack();
    break;

  // Fired when a command w/ data is received
  // User must process the command
  case EV_SMBUS_CMD:
    // TODO: process command
    break;
  }
}
