#include "mcu/spi.h"
#include <avr/io.h>

/*
  MOSI - PA1
  MISO - PA2
  SCK - PA3
*/

void spi_init(void)
{
  PORTA.DIRSET = PIN1_bm | PIN3_bm;
  PORTA.DIRCLR = PIN2_bm;

  SPI0.CTRLB = SPI_SSD_bm;
  SPI0.CTRLA = SPI_MASTER_bm | SPI_PRESC_DIV16_gc | SPI_ENABLE_bm;
}

uint8_t spi_transfer(uint8_t data)
{
  // Wait for data register to be empty so we can send new data
  while (!(SPI0.INTFLAGS & SPI_DREIF_bm))
    ;
  // Set new tx byte
  SPI0.DATA = data;
  // Wait for byte to be sent
  while (!(SPI0.INTFLAGS & SPI_IF_bm))
    ;
  return SPI0.DATA;
}