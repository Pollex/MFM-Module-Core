#if !defined(_OS_H_)
#define _OS_H_

#include "linked_queue.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef os_presleep
  void os_presleep(void);
#endif
#ifndef os_postsleep
  void os_postsleep(void);
#endif

  void os_init(void);
  void os_loop(void);
#ifdef __cplusplus
}
#endif

#endif // _OS_H_