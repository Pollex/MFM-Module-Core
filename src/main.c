#include "main.h"

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#include "mcu/twi.h"

int main(void)
{
  // Infinite loop
  for (;;)
  {
  }
}

twi_cmd_t twi_cmds[] = {
    // {0x10, twi_cmd_10_handler},
};