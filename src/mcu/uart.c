#include "mcu/uart.h"
#include <avr/io.h>

/*
  RX = PB3
  TX = PB2
*/

#define F_CPU 2666666L
#define BAUD(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

void uart_init(uart_t *uart)
{
  // Set UART formats
  USART0.BAUD = (uint16_t)BAUD(uart->baudrate);

  USART0.CTRLB = 0;

  // Enable Receiver
  if (uart->config.rx_enabled)
  {
    PORTB.DIRCLR = PIN3_bm;
    USART0.CTRLB |= USART_RXEN_bm;
  }

  // Enable Transmitter
  if (uart->config.tx_enabled)
  {
    PORTB.DIRSET = PIN2_bm;
    PORTB.OUTSET = PIN2_bm;
    USART0.CTRLB |= USART_TXEN_bm;
  }
}

void uart_putc(uart_t *uart, uint8_t data)
{
  while (!(USART0.STATUS & USART_DREIF_bm))
    ;
  USART0.TXDATAL = data;
}

uint8_t uart_getc(uart_t *uart)
{
  while (!(USART0.STATUS & USART_RXCIF_bm))
    ;
  return USART0.RXDATAL;
}

void uart_print(uart_t *uart, uint8_t *str)
{
  for (uint8_t i = 0; str[i] != '\0'; i++)
  {
    uart_putc(uart, str[i]);
  }
}