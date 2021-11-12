#include "mcu/spi.h"
#include <avr/io.h>

/*
  MOSI - PA1
  MISO - PA2
  SCK - PA3
*/

void spi_init(spi_t *spi)
{
  PORTA.DIRSET = PIN1_bm | PIN3_bm;                          // MOSI and CLK as output
  SPI0.CTRLB = SPI_SSD_bm                                    // Disable multi-master bus
               | ((spi->mode << SPI_MODE_gp) & SPI_MODE_gm); // Set mode from config

  // Depending on the clock speed, this might need a CLK_DIV
  SPI0.CTRLA = SPI_MASTER_bm                                      // Set to master mode
               | ((spi->data_order << SPI_DORD_bp) & SPI_DORD_bm) // Set data order from config
               | SPI_ENABLE_bm;                                   // Enable peripheral
}

uint8_t spi_transfer(spi_t *spi, uint8_t data)
{
  // Set new tx byte
  SPI0.DATA = data;
  // Wait for byte to be sent
  while (!(SPI0.INTFLAGS & SPI_IF_bm))
    ;
  return SPI0.DATA;
}