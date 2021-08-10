#if !defined(_TWI_H_)
#define _TWI_H_

#include <stdint.h>

typedef struct
{

} twi_t;

#ifdef __cplusplus
extern "C"
{
#endif

  void twi_init(void);
  void twi_ack(void);
  void twi_nack(void);
  uint8_t twi_available(void);

#ifdef __cplusplus
}
#endif

#endif // _TWI_H_