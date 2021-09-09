#include "os/linked_queue.h"
#include <stddef.h>

os_task_t *head = NULL;

os_task_t *os_popTask(void)
{
  os_task_t *poppedTask = head;

  // Queue is empty
  if (poppedTask == NULL)
    return NULL;

  // Set next task as head
  if (poppedTask->next != NULL)
  {
    head = poppedTask->next;
  }

  // Return popped task
  return poppedTask;
}

void os_pushTask(os_task_t *t)
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
    head->next = t;
    head = t;
    return;
  }

  // Move forward through linked list until the priority at the cursor
  // is lower than that of the to be inserted task, or cursor is NULL
  os_task_t *cursor = head;
  while (cursor->next != NULL && cursor->next->priority >= t->priority)
  {
    cursor = cursor->next;
  }

  // Insert task
  cursor->next = t;
}