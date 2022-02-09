#include <avr/io.h>
#include <avr/interrupt.h>
#include <drivers/onewire.h>
#include <mcu/util.h>
#include <mcu/uart.h>
#include <avr/xmega.h>

#define LED_PORT PORTA
#define LED_PIN PIN6

uart_t uart = {
    .baudrate = 9600,
    .config = {
        .rx_enabled = 0,
        .tx_enabled = 1,
    },
};

void to_hex(uint8_t n, char *buf)
{
  uint8_t lower = n & 0x0F;
  uint8_t upper = (n & 0xF0) >> 4;
  buf[0] = (lower < 10 ? lower + '0' : lower + 'A' - 10);
  buf[1] = (upper < 10 ? upper + '0' : upper + 'A' - 10);
  buf[2] = '\0';
}

int main(void)
{
  // _PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, 0);
  sei();
  uart_init(&uart);
  delay_init();
  uart_print(&uart, "Hello, world!\r\n");

  // Set Onewire as input
  OW_PORT.DIRCLR = 1 << OW_PIN;

  for (;;)
  {
    delay_ms(2000);

    // Read OneWire device serial
    ow_reset();
    ow_write(OW_CMD_READ);
    uint8_t serial[8];
    for (int i = 0; i < 8; i++)
    {
      serial[i] = ow_read();
    }

    uart_print(&uart, "\r\n\r\nSerial: ");
    char buf[3];
    // Print serial
    for (int i = 0; i < 8; i++)
    {
      to_hex(serial[i], buf);
      uart_print(&uart, buf);
    }
  }
}

