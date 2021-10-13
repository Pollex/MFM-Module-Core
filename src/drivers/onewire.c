#include "drivers/onewire.h"

#include <avr/io.h>
#include <util/delay.h>

#define PORT(p) (*(PORT_t *)p)

void ow_low(onewire_t *ow)
{
  // Set out low
  PORT(ow->port).DIRSET = 1 << ow->pin;
  PORT(ow->port).OUTCLR = 1 << ow->pin;
}

void ow_high(onewire_t *ow)
{
  // Set input (preferably floating)
  PORT(ow->port).DIRCLR = 1 << ow->pin;
}

uint8_t ow_sample(onewire_t *ow)
{
  return PORT(ow->port).IN & (1 << ow->pin);
}

uint8_t ow_reset(onewire_t *ow)
{
  _delay_us(OW_TIME_G);
  ow_low(ow);
  _delay_us(OW_TIME_H);
  ow_high(ow);
  _delay_us(OW_TIME_I);
  uint8_t v = ow_sample(ow);
  _delay_us(OW_TIME_J);
  return v;
}

void ow_write_bit(onewire_t *ow, uint8_t bit)
{
  // Bit is 1
  if (bit)
  {
    ow_low(ow);
    _delay_us(OW_TIME_A);
    ow_high(ow);
    _delay_us(OW_TIME_B);
    return;
  }
  // Bit is 0
  ow_low(ow);
  _delay_us(OW_TIME_C);
  ow_high(ow);
  _delay_us(OW_TIME_D);
}

uint8_t ow_read_bit(onewire_t *ow)
{
  ow_low(ow);
  _delay_us(OW_TIME_A);
  ow_high(ow);
  _delay_us(OW_TIME_E);
  uint8_t val = ow_sample(ow);
  _delay_us(OW_TIME_F);
}

void ow_write_byte(onewire_t *ow, uint8_t data)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    ow_write_bit(ow, (data >> i) & 0x01);
  }
}

uint8_t ow_read_byte(onewire_t *ow)
{
  uint8_t data = 0;
  for (uint8_t i = 0; i < 8; i++)
  {
    data |= ow_read_bit(ow) << i;
  }
  return data;
}