#if !defined(_DRIVER_ADS1118_H_)
#define _DRIVER_ADS1118_H_

#include <avr/io.h>
#include <stdint.h>

#define ADS1118_PGA_6114 0b000
#define ADS1118_PGA_4096 0b001
#define ADS1118_PGA_2048 0b010
#define ADS1118_PGA_1024 0b011
#define ADS1118_PGA_0512 0b100
#define ADS1118_PGA_0256 0b001
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

#define ADS1118_SS_bp 0x0F
#define ADS1118_SS_bm (0b1 << ADS1118_SS_bp)
#define ADS1118_MUX_bp 0x0C
#define ADS1118_MUX_bm (0b111 << ADS1118_MUX_bp)
#define ADS1118_PGA_bp 0x09
#define ADS1118_PGA_bm (0b111 << ADS1118_PGA_bp)
#define ADS1118_MODE_bp 0x08
#define ADS1118_MODE_bm (0b1 << ADS1118_MODE_bp)
#define ADS1118_DR_bp 0x05
#define ADS1118_DR_bm (0b111 << ADS1118_DR_bp)
#define ADS1118_TS_MODE_bp 0x04
#define ADS1118_TS_MODE_bm (0b1 << ADS1118_TS_MODE_bp)
#define ADS1118_PULLUP_bp 0x01
#define ADS1118_PULLUP_bm (0b1 << ADS1118_PULLUP_bp)
#define ADS1118_NOP_bp 0x01
#define ADS1118_NOP_bm (0b11 << ADS1118_NOP_bp)

#define ADS1118_CONFIG(MODE, MUX, PGA, DR, PULLUP) (      \
    ((MODE << ADS1118_MODE_bp) & ADS1118_MODE_bm) |       \
    ((MUX << ADS1118_MUX_bp) & ADS1118_MUX_bm) |          \
    ((PGA << ADS1118_PGA_bp) & ADS1118_PGA_bm) |          \
    ((DR << ADS1118_DR_bp) & ADS1118_DR_bm) |             \
    ((PULLUP << ADS1118_PULLUP_bp) & ADS1118_PULLUP_bm) | \
    ((ADS1118_NOP_VALID << ADS1118_NOP_bp) & ADS1118_NOP_bm))

typedef union
{
  uint16_t word;
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
  } fields;
  struct
  {
    uint8_t lsb;
    uint8_t msb;
  } byte;
} ads1118_config;

typedef struct
{
  PORT_t *cs_port;
  uint8_t cs_pin;
  ads1118_config config;
} ads1118_t;

#ifdef __cplusplus
extern "C"
{
#endif

  void ads1118_init(ads1118_t *);
  void ads1118_setup(ads1118_t *ads);
  double ads1118_read(ads1118_t *);

#ifdef __cplusplus
}
#endif

#endif // _DRIVER_ADS1118_H_