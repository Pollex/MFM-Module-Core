#include "os/linked_queue.h"

os_task *head = 0;

void os_clearTasks(void)
{
  head = 0;
}

os_task *os_peekTask(void)
{
  return head;
}

os_task *os_popTask(void)
{
  os_task *poppedTask = head;

  // Queue is empty
  if (poppedTask == 0)
    return 0;

  // Set next task as head
  head = poppedTask->next;

  // Return popped task
  return poppedTask;
}

void os_pushTask(os_task *t)
{
  // Case: Queue is empty
  if (head == 0)
  {
    head = t;
    return;
  }

  // Case: Head is lower prio
  if (head->priority < t->priority)
  {
    t->next = head;
    head = t;
    return;
  }

  // Move forward through linked list until the priority at the cursor
  // is lower than that of the to be inserted task, or cursor is 0
  os_task *cursor = head;
  while (cursor->next != 0 && cursor->next->priority >= t->priority)
  {
    cursor = cursor->next;
  }

  // Insert task
  t->next = cursor->next;
  cursor->next = t;
}