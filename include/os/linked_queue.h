#if !defined(_OS_LINKED_QUEUE_H_)
#define _OS_LINKED_QUEUE_H_

#include <stdint.h>

struct os_task_struct
{
  void (*func)(void);
  uint8_t priority;
  struct os_task_struct *next;
};
typedef struct os_task_struct os_task;

#ifdef __cplusplus
extern "C"
{
#endif

  os_task *os_peekTask(void);
  os_task *os_popTask(void);
  void os_pushTask(os_task *);
  void os_clearTasks(void);

#ifdef __cplusplus
}
#endif

#endif // _OS_LINKED_QUEUE_H_