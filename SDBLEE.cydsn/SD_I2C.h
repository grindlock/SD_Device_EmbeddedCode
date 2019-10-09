/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "project.h"

// Si7006-A20 datasheet  https://www.silabs.com/documents/public/data-sheets/Si7006-A20.pdf
#define ADDR_HUMTEMP      (0x40) // I2C address pag. 18
#define REG_HUMSENSOR_HUM (0xE5) // Read humidity register hold master mode pag. 18
#define REG_HUMSENSOR_TEM (0xE3) // Get temperature from the humidity reading pag. 18

// TMP431 and TMP432 datasheet http://www.ti.com/lit/ds/symlink/tmp432.pdf
#define ADDR_TEMP431 (0x4C)
#define REG_LH_TMP431 (0x00) // Read High Byte of the local temperature
#define REG_LL_TMP431 (0x15)//  Read low Byte of the local temperature
#define REG_MANUF_ID431 (0xFE) // Read manufacture id = 0x55
#define REG_TMP431ID    (0xFD) // Read the device ID = 0x31

#define ADDR_TEMP432 (0x4D)
#define REG_LH_TMP432 (0x00) // Read High Byte of the local temperature
#define REG_LL_TMP432 (0x29)//  Read low Byte of the local temperature
#define REG_MANUF_ID432 (0xFE) // Read manufacture id = 0x55
#define REG_TMP432ID   (0xFD) // Read the device ID = 0x32

// MCP39F511 datasheet http://ww1.microchip.com/downloads/en/DeviceDoc/20005442A.pdf
#define ADDR_POWER1 ()
#define ADDR_POWER2 ()
#define ADDR_POWER3 ()
#define REG_VOLTRMS (0x06)
#define REG_CURRRMS (0x0E)
#define REG_POWER_STATUS (0x02)
#define REG_POWER_VER (0x04)

uint16 Read_sensor_word(uint32 address, uint8 reg);
uint8  Read_sensor_byte(uint32 address, uint8 reg);

int test_sensor(uint32 address, uint8 reg);

uint16 humidity_read(uint32 address, uint8 reg);

uint8 temperature_local_read(uint32 address, uint8 reg);

uint8 temperature_remote_read(uint32 address, uint8 reg);

uint8 current_read(uint32 address, uint8 reg);

uint8 voltage_read(uint32 address, uint8 reg);




/* [] END OF FILE */
