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

#include "SD_I2C.h"


uint16 Read_sensor_word(uint32 address, uint8 reg){
    
    uint8 write_buff[1] ={0};
    write_buff[0] = reg;
    
  volatile  uint8 read_buff[2] = {0,0};
    
    I2C_1_I2CMasterWriteBuf(address, (uint8 *) write_buff, 1, I2C_1_I2C_MODE_NO_STOP);
    while((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_WR_CMPLT) == 0){}
    
     I2C_1_I2CMasterReadBuf(address, (uint8 *) read_buff, 2, I2C_1_I2C_MODE_REPEAT_START);
    while((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_RD_CMPLT) == 0){}
    
    return ((unsigned int) read_buff[0] << 8) | (unsigned int) read_buff[1];
}

uint8 Read_sensor_byte(uint32 address, uint8 reg){
    
    uint8 write_buff[1] ={0};
    write_buff[0] = reg;
    
  volatile  uint8 read_buff[2] = {0,0};
    
    I2C_1_I2CMasterWriteBuf(address, (uint8 *) write_buff, 1, I2C_1_I2C_MODE_NO_STOP);
    while((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_WR_CMPLT) == 0){}
    
     I2C_1_I2CMasterReadBuf(address, (uint8 *) read_buff, 1, I2C_1_I2C_MODE_REPEAT_START);
    while((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_RD_CMPLT) == 0){}
    
    return read_buff[0];
}

int test_sensor(uint32 address, uint8 reg){

return Read_sensor_byte(address, reg) != 0x00 ? 1 : 0;

}
uint16 humidity_read(uint32 address, uint8 reg){
    uint16 humidity = 0;
    humidity = ((125 * Read_sensor_word(address, reg))/65536)-6;
    return humidity;
}

uint8 temperature_local_read(uint32 address, uint8 reg){
  uint8 temperature = 0;
    temperature = Read_sensor_byte(address, reg);
    
    
    return 0;
}

uint8 temperature_remote_read(uint32 address, uint8 reg){
uint8 temperature = 0;
    temperature = Read_sensor_byte(address, reg);
    
    return 0;
}

uint8 current_read(uint32 address, uint8 reg){
 
    return 0;
}

uint8 voltage_read(uint32 address, uint8 reg){
 
    return 0;
}

/* [] END OF FILE */
