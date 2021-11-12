#if !defined(_UART_H_)
#define _UART_H_

#include <stdint.h>

typedef struct
{
  union
  {
    struct
    {
      uint8_t rx_enabled : 1;
      uint8_t tx_enabled : 1;
    };
  } config;
  uint32_t baudrate;
} uart_t;

#ifdef __cplusplus
extern "C"
{
#endif
  void uart_init(uart_t *);
  void uart_putc(uart_t *, char);
  char uart_getc(uart_t *);
  void uart_print(uart_t *, char *);
#ifdef __cplusplus
}
#endif

#endif // _UART_H_