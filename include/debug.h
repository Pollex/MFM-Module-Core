#if !defined(_DEBUG_H_)
#define _DEBUG_H_

#include <stdio.h>
#include <stdint.h>
#include "mcu/uart.h"

#ifdef __cplusplus
extern "C"
{
#endif

  char buf[32] = {0};
  void uart_printf(uart_t *uart, const char *__fmt, va_list argp)
  {
    sprintf(buf, __fmt, argp);
    uart_print(uart, buf);
  }

#ifdef __cplusplus
}
#endif

#endif // _DEBUG_H_