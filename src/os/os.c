#include "os/os.h"

#include <avr/sleep.h>
#include <util/atomic.h>

void os_init(void)
{
}

void os_processTasks(void)
{
  static os_task *next = 0;
  while ((next = os_popTask()) != 0)
  {
    next->func();
  }
}

uint8_t os_isBusy(void)
{
  return (os_hasLock() || os_peekTask() != 0);
}

void os_sleep(void)
{
  cli();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  if (!os_isBusy())
  {
    os_presleep();
    sleep_enable();
    sei();
    sleep_cpu();
    sleep_disable();
    os_postsleep();
  }
  sei();
}