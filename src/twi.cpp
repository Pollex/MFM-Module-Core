#include "twi.h"

#include <avr/interrupt.h>

#define TWI_BUF_SIZE 32
volatile uint8_t twi_buf[TWI_BUF_SIZE];
volatile uint8_t twi_buf_cnt = 0;

ISR(TWI0_TWIS_vect)
{
  if (TWI0.SSTATUS & TWI_APIF_bm)
  {
    // ADDR match
    if (TWI0.SSTATUS & TWI_AP_bm)
    {
      // Reset buffer
      twi_buf_cnt = 0;
      // ev_enqueue(EV_TWI_TRAN_START);
      twi_ack();
    }
    else
    {
      // I2C STOP
      twi_ack();
    }
  }

  if (TWI0.SSTATUS & TWI_DIF_bm)
  {
    if (twi_buf_cnt < TWI_BUF_SIZE)
    {
      twi_buf[twi_buf_cnt] = TWI0.SDATA;
      twi_buf_cnt++;
    }
    twi_ack();
  }
}

void twi_ack(void)
{
  TWI0.SCTRLB = TWI_SCMD_RESPONSE_gc;
}

void twi_nack(void)
{
  TWI0.SCTRLB = TWI_ACKACT_NACK_gc | TWI_SCMD_RESPONSE_gc;
}

void twi_init(void)
{
  TWI0.SADDR = 0x36 << 1;
  TWI0.SCTRLA = TWI_DIEN_bm | TWI_APIEN_bm | TWI_PIEN_bm | TWI_ENABLE_bm;
}

uint8_t twi_available()
{
  return twi_buf_cnt;
}