#if !defined(_SPI_H_)
#define _SPI_H_

#include <stdint.h>

#define SPI_DORD_MSB 0
#define SPI_DORD_LSB 1
#define SPI_MODE_0 0
#define SPI_MODE_1 1
#define SPI_MODE_2 2
#define SPI_MODE_3 3

typedef struct
{
  uint8_t data_order : 1;
  uint8_t mode : 2;
} spi_t;

#ifdef __cplusplus
extern "C"
{
#endif
  void spi_init(spi_t *spi);
  uint8_t spi_transfer(spi_t *spi, uint8_t data);
#ifdef __cplusplus
}
#endif

#endif // _SPI_H_