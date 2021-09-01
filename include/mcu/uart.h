#if !defined(_UART_H_)
#define _UART_H_

#include <stdint.h>

typedef struct
{
  uint8_t rx_enabled;
  uint8_t tx_enabled;
  uint8_t baudrate;
} uart_t;

#ifdef __cplusplus
extern "C"
{
#endif
  void uart_init(uart_t *);
  void uart_putc(uart_t *, uint8_t);
  uint8_t uart_getc(uart_t *);
  void uart_print(uart_t *, uint8_t *);
#ifdef __cplusplus
}
#endif

#endif // _UART_H_