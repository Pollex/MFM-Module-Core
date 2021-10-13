#include <avr/io.h>
#include "perif/ads1118.h"
#include "mcu/uart.h"
#include "debug.h"

// ADS1118 struct
// the config fields should not be left out, they will not revert to default values!
ads1118_t ads = {
    .cs_port = &PORTA,
    .cs_pin = PIN6,
    .config = {
        .fields = {
            .mux = ADS1118_MUX_AIN1_GND,
            .pga = ADS1118_PGA_4096,
            .mode = ADS1118_MODE_CONTINUOUS,
            .datarate = ADS1118_DR_128,
            .temperature_mode = 0,
            .pull_up = ADS1118_PULLUP_DISABLE,
            .nop = ADS1118_NOP_VALID,
        }}};

// UART is used in this example for logging
uart_t uart = {
    .baudrate = 9600,
    .config = {
        .tx_enabled = 1,
    }};

int main(void)
{
  // Initialize uart for logging
  uart_init(&uart);

  // Initialize ADS1118 sensor
  ads1118_init(&ads);

  // Change mux
  ads.config.fields.mux = ADS1118_MUX_AIN0_GND;

  // Explicitly push new configuration to the device.
  // Note that reading also updates the configuration. However, this method may be useful to put the device in
  // continuous mode without having to read the value
  ads1118_setup(&ads);

  for (;;)
  {
    // Read millivolts from ads1118
    float millivolts = ads1118_read(&ads);

    // Print out result
    uart_printf(&uart, "%f", millivolts);
  }
}