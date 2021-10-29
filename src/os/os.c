#include "os/os.h"

#ifdef AVR
#include <avr/sleep.h>
#include <util/atomic.h>
#endif

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
#ifdef AVR
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    if (os_isBusy())
      return;

    os_presleep();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_mode();
    os_postsleep();
  }
#endif
}