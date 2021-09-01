#if !defined(_DRIVER_SEN0313_H_)
#define _DRIVER_SEN0313_H_

#include <stdint.h>
#include <avr/io.h>

#define SEN0313_MODE_PROCESSED 0x00
#define SEN0313_MODE_RAW 0x01

typedef struct
{
  PORT_t *tx_port;
  uint8_t tx_pin;
  uint8_t mode;
} sen0313_t;

#ifdef __cplusplus
extern "C"
{
#endif

  void sen0313_init(sen0313_t *);
  void sen0313_setup(sen0313_t *);
  uint16_t sen0313_read(sen0313_t *);
  void sen0313_debug(sen0313_t *, uint8_t *);

#ifdef __cplusplus
}
#endif

#endif // _DRIVER_SEN0313_H_