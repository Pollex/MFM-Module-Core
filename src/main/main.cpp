#ifdef BOARD_MAIN

#include <Arduino.h>
#include <Wire.h>

#define SCL PIN_PC0
#define SDA PIN_PC1

void setup(void)
{
  pinMode(SCL, OUTPUT);
  pinMode(SDA, OUTPUT);
  digitalWrite(SCL, LOW);
  digitalWrite(SDA, LOW);

  Wire.begin();
  Wire.beginTransmission(0x36);
  Wire.write(0xDE);
  Wire.write(0xAD);
  Wire.endTransmission();
}

void loop(void)
{
}

#endif