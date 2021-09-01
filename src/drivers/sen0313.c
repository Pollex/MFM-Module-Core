#include "drivers/sen0313.h"
#include "mcu/uart.h"

#define TX_PORT(sen) (*(sen->tx_port))

uart_t sen0313_uart = {
    .baudrate = 9600,
    .rx_enabled = 1,
    .tx_enabled = 0};

void sen0313_init(sen0313_t *sen)
{
  uart_init(&sen0313_uart);
  TX_PORT(sen).DIRSET = 1 << sen->tx_pin;
  sen0313_setup(sen);
}

void sen0313_setup(sen0313_t *sen)
{
  if (sen->mode == SEN0313_MODE_RAW)
  {
    TX_PORT(sen).OUTSET = 1 << sen->tx_pin;
    return;
  }
  TX_PORT(sen).OUTCLR = 1 << sen->tx_pin;
}

uint16_t sen0313_read(sen0313_t *sen)
{
  uint8_t buffer[4] = {0};

  // Wait for a start byte
  do
  {
    buffer[0] = uart_getc(&sen0313_uart);
  } while (buffer[0] != 0xFF);

  // Read other bytes
  for (uint8_t i = 1; i < 4; i++)
    buffer[i] = uart_getc(&sen0313_uart);

  uint16_t checksum = (buffer[0] + buffer[1] + buffer[2]) & 0x00FF;
  if (checksum != buffer[3])
  {
    return 0xFFFF;
  }

  uint16_t distance = (buffer[0] << 8) | buffer[1];
  return distance / 10;
}

void sen0313_debug(sen0313_t *sen, uint8_t *buffer)
{
  // Wait for a start byte
  while (uart_getc(&sen0313_uart) != 0xFF)
    ;

  // Read other bytes
  for (uint8_t i = 0; i < 3; i++)
    buffer[i] = uart_getc(&sen0313_uart);
}