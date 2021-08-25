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
#define ADS1118_MUX_AIN0_AIN1 0b000
#define ADS1118_MUX_AIN0_AIN3 0b001
#define ADS1118_MUX_AIN1_AIN3 0b010
#define ADS1118_MUX_AIN2_AIN3 0b011
#define ADS1118_MUX_AIN0_GND 0b100
#define ADS1118_MUX_AIN1_GND 0b101
#define ADS1118_MUX_AIN2_GND 0b110
#define ADS1118_MUX_AIN3_GND 0b111
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

typedef union
{
  struct
  {
    uint8_t reserved : 1;
    uint8_t nop : 2;
    uint8_t pull_up : 1;
    uint8_t temperature_mode : 1;
    uint8_t datarate : 3;
    uint8_t mode : 1;
    uint8_t pga : 3;
    uint8_t mux : 3;
    uint8_t single_shot : 1;
  } bits;
  uint16_t word;
  struct
  {
    uint8_t lsb;
    uint8_t msb;
  } byte;
} ads1118_config;

typedef struct
{
  uint8_t cs_port;
  uint8_t cs_pin;
  ads1118_config config;
} ads1118_t;

#ifdef __cplusplus
extern "C"
{
#endif

  void ads1118_init(ads1118_t *);
  void ads1118_mux(ads1118_t *, uint8_t mux);
  double ads1118_read(ads1118_t *);

#ifdef __cplusplus
}
#endif

#endif // _DRIVER_ADS1118_H_