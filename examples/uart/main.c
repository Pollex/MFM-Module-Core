#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#include "mcu/uart.h"

#define LED_PORT PORTA
#define LED_PIN PIN6
#define SENSOR_PWR_PORT PORTA
#define SENSOR_PWR_PIN PIN5

uart_t uart = {
    .baudrate = 9600,
    .config = {
        .rx_enabled = 1,
        .tx_enabled = 1,
    },
};

int main(void)
{
  // Initialize uart
  uart_init(&uart);
  uart_print(&uart, "Hello, world!\r\n");
  uart_print(&uart, "This example echoes RX to TX, try typing something: \r\n");

  // Infinite loop
  for (;;)
  {
    // Receive a character on uart, and then immediatly transmit it (echo).
    uart_putc(&uart, uart_getc(&uart));
  }
}