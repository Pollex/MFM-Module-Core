#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/xmega.h>

#include <mcu/util.h>
#include <mcu/uart.h>
#include <drivers/onewire.h>
#include <perif/ds18b20.h>

// TODO: Does not display negative temperatures well

uart_t uart = {
    .baudrate = 9600,
    .config = {
        .rx_enabled = 0,
        .tx_enabled = 1,
    },
};

#define SENSOR_PWR_PORT PORTA
#define SENSOR_PWR_PIN PIN5

void intToChar(uint16_t n, char* buf) {
  uint16_t _n = n;
  uint8_t digits = 0;
  while (_n >= 10) {
    _n /= 10;
    digits++;
  }
  buf[digits+1] = '\0';

  uint8_t remainder = 0;
  while (n != 0) {
    remainder = n % 10;
    n /= 10;
    buf[digits--] = '0' + remainder;
  }
}

char intBuf[10];
int main(void)
{
  SENSOR_PWR_PORT.DIRSET = 1 << SENSOR_PWR_PIN;
  SENSOR_PWR_PORT.OUTSET = 1 << SENSOR_PWR_PIN;

  sei();
  delay_init();
  uart_init(&uart);
  uart_print(&uart, "Serial:\n");

  // Set Onewire as input
  OW_PORT.DIRCLR = 1 << OW_PIN;

  // Read ROM serial
  ow_reset();
  ow_write(OW_CMD_READ);
  for (uint8_t i = 0; i < 8; i++) {
    uint8_t serial = ow_read();
    uint8_t lower = serial & 0x0F;
    uint8_t upper = (serial & 0xF0) >> 4;

    uart_putc(&uart, (lower < 10 ? lower + '0' : lower + 'A' - 10));
    uart_putc(&uart, (upper < 10 ? upper + '0' : upper + 'A' - 10));
    uart_putc(&uart, ' ');
  }


  ow_reset();
  ow_write(0xCC);
  ow_write(0x4E);
  ow_write(0x00);
  ow_write(0x00);
  ow_write(0x03 << 5);

  delay_ms(10);

  ow_reset();
  ow_write(0xCC);
  ow_write(0x48);
  while(!ow_readBit())
    ;


  for (;;)
  {
    float temp = ds18b20_read(0);
    int16_t full = (int16_t)(temp);

    intToChar(full, intBuf);
    uart_print(&uart, "Temperature: ");
    uart_print(&uart, intBuf);
    uart_putc(&uart, '\n');
  }
}

void putchar_(char c)
{
  uart_putc(&uart, c);
}