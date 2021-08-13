#include "events.h"

ev_t ev_queue[EV_QUEUE_SIZE] = {0};
volatile uint8_t ev_queue_head = 0;
volatile uint8_t ev_queue_tail = 0;
ev_t ev_current;

void ev_enqueue(uint8_t id, void *data)
{
  ev_disableInterrupts();
  ev_queue[ev_queue_tail].id = id;
  ev_queue[ev_queue_tail].data = data;
  uint8_t next = (ev_queue_tail + 1) % EV_QUEUE_SIZE;
  if (next == ev_queue_head)
  {
    // queue is full
    return;
  }
  ev_queue_tail = next;
  ev_enableInterrupts();
}

ev_t *ev_dequeue()
{
  // If head at the tail position then we have no new events
  if (ev_queue_head == ev_queue_tail)
  {
    return nullptr;
  }

  ev_disableInterrupts();
  ev_current = ev_queue[ev_queue_head];                // Store current event
  ev_queue_head = (ev_queue_head + 1) % EV_QUEUE_SIZE; // Move head to next position
  ev_enableInterrupts();

  return &ev_current;
}

uint8_t ev_pending()
{
  return ev_queue_head != ev_queue_tail;
}