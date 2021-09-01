#include "mcu/uart.h"
#include <avr/io.h>

/*
  RX = PB3
  TX = PB2
*/

#define F_CPU 2666666L
#define BAUD(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

void uart_init(uint16_t baud)
{
  // Set PORT directions and outputs
  PORTB.DIRSET = PIN2_bm;
  PORTB.DIRCLR = PIN3_bm;
  PORTA.OUTSET = PIN2_bm;

  // Set UART formats
  USART0.BAUD = (uint16_t)BAUD(9600);

  // Enable Receiver and Transmitter
  USART0.CTRLB = USART_RXEN_bm | USART_TXEN_bm;
}

void uart_wait_tx_ready(void)
{
  while (!(USART0.STATUS & USART_DREIF_bm))
    ;
}

void uart_wait_rx_complete(void)
{
  while (!(USART0.STATUS & USART_RXCIF_bm))
    ;
}

void uart_write(uint8_t data)
{
  uart_wait_tx_ready();
  USART0.TXDATAL = data;
}

uint8_t uart_read()
{
  uart_wait_rx_complete();
  return USART0.RXDATAL;
}

void uart_print(uint8_t *str)
{
  for (uint8_t i = 0; str[i] != '\0'; i++)
  {
    uart_write(str[i]);
  }
}