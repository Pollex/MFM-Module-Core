#include "drivers/sen0313.h"
#include "mcu/uart.h"

#define TX_PORT(ads) (*(sen->tx_port))

void sen0313_init(sen0313_t *sen)
{
  uart_init(9600);
  TX_PORT(ads).DIRSET = 1 << sen->tx_pin;
  sen0313_setup(sen);
}

void sen0313_setup(sen0313_t *sen)
{
  if (sen->mode == SEN0313_MODE_RAW)
  {
    TX_PORT(ads).OUTSET = 1 << sen->tx_pin;
    return;
  }
  TX_PORT(ads).OUTCLR = 1 << sen->tx_pin;
}

uint16_t sen0313_read(sen0313_t *sen)
{
  uint8_t buffer[3] = {0};

  // Wait for a start byte
  while (uart_read() != 0xFF)
    ;

  // Wait for the first byte
  do
  {
    buffer[0] = uart_read();
  } while (buffer[0] == 0xFF);
  buffer[1] = uart_read();
  buffer[2] = uart_read();

  uint16_t checksum = (0xFF + buffer[0] + buffer[1]) & 0x00FF;
  if (checksum != buffer[2])
  {
    // return 0xffff;
  }
  return (buffer[0] << 8) | buffer[1];
}