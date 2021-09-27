#include "os/os.h"
#include <stddef.h>

#ifdef AVR
#include <avr/sleep.h>
#endif

void os_sleep_task(void);
os_task task_sleep = {
    .func = &os_sleep_task,
    .priority = 0,
};

void os_init(void)
{
  os_pushTask(&task_sleep);
}

void os_processTasks(void)
{
  static os_task *next = NULL;
  while ((next = os_popTask()) != NULL)
  {
    next->func();
  }
}

void os_sleep_task(void)
{
  os_presleep();
  // Only actually enter sleep if there is no task queued anymore
  if (os_peekTask() == NULL)
  {
#ifdef AVR
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_mode();
#endif
  }
  os_postsleep();

  // Loop this task infinitely
  os_pushTask(&task_sleep);
}