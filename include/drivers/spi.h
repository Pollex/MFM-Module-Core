#if !defined(_SPI_H_)
#define _SPI_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif
  void spi_init(void);
  uint8_t spi_transfer(uint8_t data);
#ifdef __cplusplus
}
#endif

#endif // _SPI_H_