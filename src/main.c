#include "main.h"

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "ev_events.h"
#include "events.h"
#include "drivers/twi.h"
#include "drivers/uart.h"

const static uint8_t message[] = "Hello world!";

int main(void)
{
  sei();
  twi_init(0x36);

  uart_init(9600);

  PORTA.DIRSET = PIN6_bm;
  PORTA.OUTCLR = PIN6_bm;

  // Infinite loop
  for (;;)
    ;
}

void twi_cmd_10_handler(uint8_t *data, uint8_t len)
{
  PORTA.OUTTGL = PIN6_bm;
  // Copy message to data buffer
  memcpy(data, message, sizeof(message));

  // Send message over uart
  for (uint8_t i = 0; i < sizeof(message); i++)
  {
    uart_write(message[i]);
  }
}

twi_cmd_t twi_cmds[] = {
    {0x10, twi_cmd_10_handler},
};