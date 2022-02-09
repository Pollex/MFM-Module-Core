#if !defined(_SMBUS_H_)
#define _SMBUS_H_

#include <stdint.h>

#define SMBUS_ADDR_FIXED 0b00
#define SMBUS_ADDR_PERSISTENT 0b01
#define SMBUS_ADDR_VOLATILE 0b10
#define SMBUS_ADDR_RANDOM 0b11
#define SMBUS_PEC_UNSUPPORTED 0x00
#define SMBUS_PEC_SUPPORTED 0x01
#define SMBUS_UDID_VERSION_1 0b001
#define SMBUS_PROTOCOL_ZONE (1 << 7)
#define SMBUS_PROTOCOL_IPMI (1 << 6)
#define SMBUS_PROTOCOL_ASF (1 << 5)
#define SMBUS_PROTOCOL_OEM (1 << 4)
#define SMBUS_VERSION_1_0 0b0000
#define SMBUS_VERSION_1_1 0b0001
#define SMBUS_VERSION_2_0 0b0100
#define SMBUS_VERSION_3_0 0b0101

typedef union
{
  struct
  {
    // Device capabilities
    uint8_t address_type : 2;
    uint8_t reserved : 5;
    uint8_t pec_support : 1;

    // Version / Revision
    uint8_t reserved : 2;
    uint8_t udid_version : 3;
    uint8_t silicon_revision : 3;

    // Vendor ID
    uint16_t vendor_id;

    // Device ID
    uint16_t device_id;

    // Interface
    uint16_t supported_protocols : 12;
    uint8_t smbus_version : 4;

    // Subsystem Vendor ID
    uint16_t subsystem_vendor_id;

    // Subsystem Device ID
    uint16_t subsystem_device_id;

    // Vendor specific ID
    uint32_t vendor_specific_id;
  } fields;
  uint8_t bytes[16];
} smbus_udid_t;

#define SMBUS_DEFAULT_ADDRESS 0b1100001
#define SMBUS_CMD_PREPARE_ARP 0x01
#define SMBUS_CMD_RESET_DEVICE 0x02
#define SMBUS_CMD_GET_UDID 0x03
#define SMBUS_CMD_ASSIGN_ADDRESS 0x04

// Command with an address and set LSB indicates a directed GET_UDID command
#define SMBUS_CMD_GET_UDID_DIRECT(addr) ((addr << 1) | 0x01)
// Command with an address and unset LSB indicates a directed RESET_DEVICE command
#define SMBUS_CMD_RESET_DEVICE_DIRECT(addr) (addr << 1)

typedef struct
{
  uint8_t address_valid : 1;
  uint8_t address_resolve : 1;
} smbus_state_t;

#ifdef __cplusplus
extern "C"
{
#endif

  extern const smbus_udid_t smbus_udid;

#ifdef __cplusplus
}
#endif

#endif // _SMBUS_H_