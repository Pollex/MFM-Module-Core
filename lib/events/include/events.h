#if !defined(_EVENTS_H_)
#define _EVENTS_H_

#include <stdint.h>
#include "ev_events.h"

#ifndef EV_QUEUE_SIZE
#define EV_QUEUE_SIZE 32
#endif

typedef struct ev
{
  uint8_t id;
  void *data;
} ev_t;

#ifdef __cplusplus
extern "C"
{
#endif

  void ev_enqueue(uint8_t id, void *data);
  ev_t *ev_dequeue();
  uint8_t ev_pending();

  void ev_enableInterrupts();
  void ev_disableInterrupts();

#ifdef __cplusplus
}
#endif

#endif // _EVENTS_H_