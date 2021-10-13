#include "mcu/util.h"

#ifndef F_CPU
#define F_CPU 1000000
#endif

void delay_us(uint32_t us)
{
  uint32_t cycles = us * 1.3 / (1000000.0 / F_CPU) / 4;
  while (cycles--)
  {
    __asm("nop");
  }
}

void delay_ms(uint32_t ms)
{
  uint32_t cycles = ms / (1000.0 / F_CPU);
  while (cycles--)
  {
    __asm("nop");
  }
}
