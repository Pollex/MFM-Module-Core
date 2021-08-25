#include <avr/io.h>
#include "mcu/spi.h"
#include "drivers/ads1118.h"

ads1118_t ads = {
    .cs_port = &PORTB,
    .cs_pin = PIN2,
    .config = ADS1118_CONFIG(ADS1118_MODE_SINGLESHOT, ADS1118_MUX_AIN0_GND, ADS1118_PGA_4096, ADS1118_DR_8, ADS1118_PULLUP_DISABLE),
};

int main(void)
{
  spi_init();
  ads1118_init(&ads);

  // Change mux
  ads.config.fields.mux = ADS1118_MUX_AIN1_GND;

  // Explicitly push new configuration to the device.
  // Note that reading also updates the configuration. However, this method may be useful to put the device in
  // continuous mode without having to read the value
  ads1118_setup(&ads);

  for (;;)
  {
    double millivolts = ads1118_read(&ads);
    // Do something
    // TODO: Send to UART
  }
}