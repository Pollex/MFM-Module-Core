#include "os/linked_queue.h"
#include <stddef.h>

os_task *head = NULL;

void os_init(void)
{
  head = NULL;
}

os_task *os_popTask(void)
{
  os_task *poppedTask = head;

  // Queue is empty
  if (poppedTask == NULL)
    return NULL;

  // Set next task as head
  head = poppedTask->next;

  // Return popped task
  return poppedTask;
}

void os_pushTask(os_task *t)
{
  // Case: Queue is empty
  if (head == NULL)
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
  // is lower than that of the to be inserted task, or cursor is NULL
  os_task *cursor = head;
  while (cursor->next != NULL && cursor->next->priority >= t->priority)
  {
    cursor = cursor->next;
  }

  // Insert task
  cursor->next = t;
}