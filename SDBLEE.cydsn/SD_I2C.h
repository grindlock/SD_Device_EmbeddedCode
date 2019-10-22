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
#if !defined(SD_I2C_H)
#define SD_I2C_H
    
#include "project.h"

// Si7006-A20 datasheet  https://www.silabs.com/documents/public/data-sheets/Si7006-A20.pdf (humidity)
#define ADDR_HUMTEMP      (0x40) // I2C address pag. 18
#define REG_HUMSENSOR_HUM (0xE5) // Read humidity register hold master mode pag. 18
#define REG_HUMSENSOR_TEM (0xE3) // Get temperature from the humidity reading pag. 18
#define REG_HUM_ID_0 (0xFA)
#define REG_HUM_ID_1 (0x0F) 
#define REG_HUM_ID_2 (0xFC) 
#define REG_HUM_ID_3 (0xC9) 
    
// TMP431 and TMP432 datasheet http://www.ti.com/lit/ds/symlink/tmp432.pdf (temperature)
#define ADDR_TEMP431 (0x4C)
#define REG_LH_TMP431 (0x00) // Read High Byte of the local temperature
#define REG_LL_TMP431 (0x15)//  Read low Byte of the local temperature
#define REG_RH_TEMP431 (0x01) // Read High Byte of the remote temperature
#define REG_RL_TEMP431 (x10)//   Read low Byte of the remote temperature
#define REG_MANUF_ID431 (0xFE) // Read manufacture id = 0x55
#define REG_TMP431ID    (0xFD) // Read the device ID = 0x31

#define ADDR_TEMP432 (0x4D)
#define REG_LH_TMP432 (0x00) // Read High Byte of the local temperature
#define REG_LL_TMP432 (0x29)//  Read low Byte of the local temperature
#define REG_RH1_TMP432 (0x01) // Read High Byte of the remote temperature 1
#define REG_RL1_TMP432 (0x10)//   Read low Byte of the remote temperature 1
#define REG_RH2_TMP432 (0x23) // Read High Byte of the remote temperature 2
#define REG_RL2_TMP432 (0x24)//   Read low Byte of the remote temperature 2
#define REG_MANUF_ID432 (0xFE) // Read manufacture id = 0x55
#define REG_TMP432ID   (0xFD) // Read the device ID = 0x32

// MCP39F521 datasheet http://ww1.microchip.com/downloads/en/DeviceDoc/20005442A.pdf (power monitoring)
#define ADDR_POWER1 (0x74)
#define ADDR_POWER2 (0x75)
#define ADDR_POWER3 (0x76)
#define REG_VOLTRMS (0x06)
#define REG_CURRRMS (0x0E)
#define REG_LINEFREQ (0x08)
#define REG_POWER_STATUS (0x02)
#define REG_POWER_VERSION (0x04)

// BMA253 datasheet https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMA253-DS000.pdf (accelerometer)
#define ADDR_ACC (0x18)
#define REG_ACCID (0x00)
#define REG_XLSB (0x02)
#define REG_XMSB (0x03)
#define REG_YLSB (0x04)
#define REG_YMSB (0x05)
#define REG_ZLSB (0x06)
#define REG_ZMSB (0x07)

// PCA9538A datasheet  https://www.nxp.com/docs/en/data-sheet/PCA9538A.pdf
#define ADDR_GPIO (0x70)
#define REG_

uint16 Read_sensor_word(uint32 address, uint8 reg);

uint8  Read_sensor_byte(uint32 address, uint8 reg);

int test_sensor(uint32 address, uint8 reg);

uint16 humidity_read(uint32 address, uint8 reg);

uint8 temperature_local_read(uint32 address, uint8 reg);

uint8 temperature_remote_read(uint32 address, uint8 reg);

float current_read(uint32 address, uint8 reg);

float voltage_read(uint32 address, uint8 reg);

float line_frequency_read(uint32 address, uint8 reg);

uint16 x_accelerometer_read(uint32 address, uint8 regLSB, uint8 regMSB);

uint16 y_accelerometer_read(uint32 address, uint8 regLSB, uint8 regMSB);

uint16 z_accelerometer_read(uint32 address, uint8 regLSB, uint8 regMSB);

uint16 gpio_expander_read(uint32 address, uint8 reg);

int humidity_sensor_ID();
int temperature_TI431_sensor_ID();
int temperature_TI432_sensor_ID();
int current_voltage_sensor_ID(uint32 address);



#endif
/* [] END OF FILE */
