#include "events.h"

ev_t ev_queue[EV_QUEUE_SIZE] = {0};
uint8_t ev_queue_head = 0;
uint8_t ev_queue_tail = 0;
ev_t ev_current;

void ev_enqueue(uint8_t id, void *data)
{

  uint8_t new_tail = ev_queue_tail + 1;
  if (new_tail >= EV_QUEUE_SIZE)
    new_tail = 0;

  // If the next tail position would overwrite the head,
  // then we have no space left in the queue and we would
  // start overwriting the unprocessed events
  if (new_tail == ev_queue_head)
  {
    // No place in queue
    return;
  }

  ev_disableInterrupts();
  ev_queue[ev_queue_tail] = {0};       // Clear tail ev
  ev_t *ev = &ev_queue[ev_queue_tail]; // Get (now empty) tail
  ev_enableInterrupts();

  ev->id = id;     // Set ID
  ev->data = data; // Set Data

  // Update tail
  ev_queue_tail = new_tail;
}

ev_t *ev_dequeue()
{
  // If head at the tail position then we have no new events
  if (ev_queue_head == ev_queue_tail)
  {
    return nullptr;
  }

  ev_disableInterrupts();
  // Dequeue event
  ev_current = ev_queue[ev_queue_head];
  ev_enableInterrupts();

  // Advance head
  ev_queue_head++;
  if (ev_queue_head >= EV_QUEUE_SIZE)
    ev_queue_head = 0;

  return &ev_current;
}

uint8_t ev_pending()
{
  return ev_queue_head != ev_queue_tail;
}