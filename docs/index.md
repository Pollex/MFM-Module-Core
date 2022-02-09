# MFM to Module communication

## SMBus commands

| Command | Name    | Type       | Description                               |
| ------- | ------- | ---------- | ----------------------------------------- |
| 0x10    | PERFORM | send byte  | Have the module perform a measurement     |
| 0x11    | READ    | read block | Read the measurement results              |
| 0x12    | STATUS  | read word  | Fetch the status register from the module |

## Internal

### TWI / I<sup>2</sup>C / SMBus

The usercode defines an array of `twi_cmd_t` structs. This struct contains the command byte code and a corresponding handler functions.

This handler is called in an ISR so it must respond instantly, for example when requesting measurement results. These results are stored in a variable and can be directly returned to the SMBus master.

When a command requires more time, it should queue an `os_task`. This task will be picked up by the os outside of the ISR. It will be picked up in the main loop.

Note that the ATTiny814 has no CRC peripheral to use for the PEC byte. Implementation of CRC-8 is not difficult, but can it be sequential aka do we need to store the bytes or can we process one by one realtime? (https://forum.digikey.com/t/crc-basics/13455)

The PEC byte can occur in two occasions:

- **Master write with no read**  
  Means the master will end on the PEC byte, since CMD parameter length is defined in the spec, the driver knows which byte is the PEC byte.
- **Master write, to read**  
  When reading, the driver knows the response length. If the master sends more clock cycles, the driver can provide the PEC. However, according to the specification (6.4.1.2.) the master should know whether the slave supports PEC.
