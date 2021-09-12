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

void os_clearTasks(void)
{
  os_pushTask(&task_sleep);
}

void os_loop(void)
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

#endif
  }
  os_postsleep();

  // Loop this task infinitely
  os_pushTask(&task_sleep);
}