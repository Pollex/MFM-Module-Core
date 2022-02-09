#if !defined(_PERIF_DS18B20_H_)
#define _PERIF_DS18B20_H_

#include <stdint.h>

#define DS18B20_CONVERT 0x44
#define DS18B20_WRITE_SCRATCHPAD 0x4E
#define DS18B20_READ_SCRATCHPAD 0xBE

#ifdef __cplusplus
extern "C"
{
#endif

  float ds18b20_read(uint8_t id);

#ifdef __cplusplus
}
#endif

#endif // _PERIF_DS18B20_H_