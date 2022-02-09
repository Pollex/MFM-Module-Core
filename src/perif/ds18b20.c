#include "perif/ds18b20.h"
#include "drivers/onewire.h"
#include <mcu/util.h>

#define ERROR_VALUE 85
#define MAX_RETRIES 5

void convert_t(uint8_t id) {
  ow_reset();
  ow_write(OW_CMD_SKIP);
  ow_write(DS18B20_CONVERT);
}

uint16_t read_temp() {
  ow_reset();
  ow_write(OW_CMD_SKIP);
  ow_write(DS18B20_READ_SCRATCHPAD);

  uint8_t lsb = ow_read();
  uint8_t msb = ow_read();

  return ((uint16_t)msb << 8) | (uint16_t)lsb;
}

float ds18b20_read(uint8_t id) {
  // Read a new tempetarutre which is set in the scratchpad
  convert_t(id);

  // Wait for conversion to complete
  while(!ow_readBit())
  {
    delay_ms(20);
  }

  // Read scratchpad to get temperature bytes
  // sometimes read_temp returns 0xffff, so we retry up to `MAX_RETRIES` times
  uint8_t retries = 0;
  uint16_t raw;
  do {
    raw = read_temp();
    retries++;
    if (retries > MAX_RETRIES) {
      return ERROR_VALUE;
    }
  } while (raw == 0xffff);

  // Convert
  uint8_t sign = raw >> 15;
  float temp = (float)((raw & 0x7FFF) * 0.0625);
  return temp * (sign ? -1 : 1);
}