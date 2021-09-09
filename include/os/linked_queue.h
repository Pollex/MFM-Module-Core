#if !defined(_OS_LINKED_QUEUE_H_)
#define _OS_LINKED_QUEUE_H_

#include <stdint.h>

struct os_task
{
  void (*func)(void);
  uint8_t priority;
  struct os_task *next;
};
typedef struct os_task os_task_t;

#ifdef __cplusplus
extern "C"
{
#endif

  os_task_t *os_popTask(void);
  void os_pushTask(os_task_t *);

#ifdef __cplusplus
}
#endif

#endif // _OS_LINKED_QUEUE_H_