#if !defined(_MCU_UTIL_H_)
#define _MCU_UTIL_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif
  void delay_us(uint32_t);
  void delay_ms(uint32_t);
#ifdef __cplusplus
}
#endif

#endif // _MCU_UTIL_H_