#if !defined(_DRIVER_ADS1118_H_)
#define _DRIVER_ADS1118_H_

#include <stdint.h>

#define ADS1118_PGA_6114 0b000;
#define ADS1118_PGA_4096 0b001;
#define ADS1118_PGA_2048 0b010;
#define ADS1118_PGA_1024 0b011;
#define ADS1118_PGA_0512 0b100;
#define ADS1118_PGA_0256 0b001;
#define ADS1118_MODE_CONTINUOUS 0b0
#define ADS1118_MODE_SINGLESHOT 0b1
#define ADS1118_DR_8 0b000
#define ADS1118_DR_16 0b001
#define ADS1118_DR_32 0b010
#define ADS1118_DR_64 0b011
#define ADS1118_DR_128 0b100
#define ADS1118_DR_250 0b101
#define ADS1118_DR_475 0b110
#define ADS1118_DR_860 0b111
#define ADS1118_PULLUP_DISABLE 0b00
#define ADS1118_PULLUP_ENABLE 0b01
#define ADS1118_NOP_INVALID 0b00
#define ADS1118_NOP_VALID 0b01

#define ADS1118_CONFIG(PGA, MODE, DR, PULLUP) ( \
    ((PGA & 0x03) << 9) |                       \
    ((MODE & 0x01) << 8) |                      \
    ((DR & 0x03) << 5) |                        \
    ((PULLUP & 0x01) << 3) |                    \
    (ADS1118_NOP_VALID << 1))

typedef struct
{
  uint8_t cs_port;
  uint8_t cs_pin;
  uint16_t config;
} ads1118_t;

#ifdef __cplusplus
extern "C"
{
#endif

  void ads1118_init(ads1118_t *);
  float ads1118_read(ads1118_t *);

#ifdef __cplusplus
}
#endif

#endif // _DRIVER_ADS1118_H_