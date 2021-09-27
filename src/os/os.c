#include "os/os.h"
#include <stddef.h>

#ifdef AVR
#include <avr/sleep.h>
#endif

uint8_t sleepLocks = 0;

void os_init(void)
{
}

void os_lockSleep(void)
{
  sleepLocks++;
}

void os_unlockSleep(void)
{
  sleepLocks--;
}

void os_processTasks(void)
{
  static os_task *next = NULL;
  while ((next = os_popTask()) != NULL)
  {
    next->func();
  }
}

void os_sleep(void)
{
  if (sleepLocks > 0)
    return;

  os_presleep();
  // Only actually enter sleep if there is no task queued anymore and sleep is not locked
  if (os_peekTask() == NULL && sleepLocks == 0)
  {
#ifdef AVR
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_mode();
#endif
  }
  os_postsleep();
}