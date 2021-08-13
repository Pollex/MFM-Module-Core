#include "drivers/twi.h"

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "ev_events.h"
#include "events.h"

uint8_t twi_buffer[TWI_BUFFER_LENGTH] = {0};
volatile uint8_t twi_buffer_index = 0;
volatile uint8_t twi_busy = 0;

void twi_ack() { TWI0.SCTRLB = 3; }
void twi_nack() { TWI0.SCTRLB = 7; }     //RESPONSE, NACK
void twi_complete() { TWI0.SCTRLB = 2; } //COMPTRANS
void twi_end()
{
  twi_complete();
  twi_busy = 0;
}

void twi_init(uint8_t addr)
{
  // Enable interrupts
  TWI0.SCTRLA = TWI_DIEN_bm | TWI_APIEN_bm | TWI_PIEN_bm;
  // Set addr
  TWI0.SADDR = addr << 1;
  // Enable
  TWI0.SCTRLA |= TWI_ENABLE_bm;
  sei();
}

ISR(TWI0_TWIS_vect)
{
  uint8_t s = TWI0.SSTATUS;
  uint8_t isErr = s & (TWI_COLL_bm | TWI_BUSERR_bm);
  uint8_t isRead = (s & (TWI_DIF_bm | TWI_DIR_bm)) == 0x82;
  uint8_t isWrite = (s & (TWI_DIF_bm | TWI_DIR_bm)) == 0x80;
  uint8_t isAddr = (s & (TWI_APIF_bm | TWI_AP_bm)) == 0x41;
  uint8_t isStop = (s & (TWI_APIF_bm | TWI_AP_bm)) == 0x40;

  if (isErr || isStop)
  {
    return twi_end();
  }

  if (isAddr)
  {
    twi_busy = 1;
    twi_buffer_index = 0;
    return twi_ack();
  }

  if (isWrite)
  {
    if (twi_buffer_index >= TWI_BUFFER_LENGTH)
      return twi_nack();
    twi_buffer[twi_buffer_index++] = TWI0.SDATA;
    return twi_ack();
  }

  if (isRead)
  {
    return twi_ack();
  }
}