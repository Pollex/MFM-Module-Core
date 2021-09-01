#if !defined(_UART_H_)
#define _UART_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif
  void uart_init(uint16_t baud);
  void uart_write(uint8_t);
  uint8_t uart_read(void);
  void uart_print(uint8_t *);
#ifdef __cplusplus
}
#endif

#endif // _UART_H_