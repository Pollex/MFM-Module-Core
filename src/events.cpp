#include "events.h"
#include <avr/interrupt.h>

void ev_enableInterrupts()
{
  sei();
}
void ev_disableInterrupts()
{
  cli();
}