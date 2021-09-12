#if !defined(_OS_H_)
#define _OS_H_

#include "linked_queue.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef os_presleep
#warning "User should define void os_presleep(void) method!"
  void os_presleep(void){};
#endif
#ifndef os_postsleep
#warning "User should define void os_postsleep(void) method!"
  void os_postsleep(void){};
#endif

  void os_clearTasks(void);
  void os_loop(void);
#ifdef __cplusplus
}
#endif

#endif // _OS_H_