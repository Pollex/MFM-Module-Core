## Sensormodule registry


### Theory

The Multiflexmeter uses sensor modules to interface with any kind of sensor required. This process is plug-and-play and does not require any configuration to the device. 

The main controller and the module controller communicate through I2C / SMBus. Each module has a persistent(/non-volatile) address that is unique on that bus. The address is assigned through the SMBus Address Resolution Protocol.

The main controller builds an uplink message by concatenating the sensor module address with its sensor type and measured data.

`addr (7 bits) | type id length (1 bit) | type id (8 or 16 bits) | payload (variable)`

### Registry

| Type ID | Name                | Description                                 |
| ------- | ------------------- | ------------------------------------------- |
| 0x10    | Waterlevel SEN0313  | SEN0313 + DS18B20 module                    |
| 0x11    | STS Pressure sensor | 2 slots STS Pressure sensor with ADC module |