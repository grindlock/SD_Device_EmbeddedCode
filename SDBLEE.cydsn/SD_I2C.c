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

float current_read(uint32 address, uint8 reg){
    uint8 write_buff[1] ={0};
    write_buff[0] = reg;
    
  volatile  uint8 read_buff[4] = {0,0,0,0};
    
    I2C_1_I2CMasterWriteBuf(address, (uint8 *) write_buff, 1, I2C_1_I2C_MODE_NO_STOP);
    while((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_WR_CMPLT) == 0){}
    
     I2C_1_I2CMasterReadBuf(address, (uint8 *) read_buff, 4, I2C_1_I2C_MODE_REPEAT_START);
    while((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_RD_CMPLT) == 0){}
    
    int tempCurrent = (read_buff[0] << 24 | read_buff[1] << 16 | read_buff[2] << 8 | read_buff[3]);
    float formattedCurrent = tempCurrent/10000.f;
 
    return formattedCurrent;
}

float voltage_read(uint32 address, uint8 reg){
    
    uint16 tempVolt = Read_sensor_word(address, reg);
    float formattedVolt = tempVolt/10.0f;
    return formattedVolt;
}

float line_frequency_read(uint32 address, uint8 reg){
    
    uint16 temLFreq = Read_sensor_word(address, reg);
    float formattedLineFrequency = temLFreq/1000.0f;
    return formattedLineFrequency;
}

uint16 x_accelerometer_read(uint32 address, uint8 regLSB, uint8 regMSB){
    uint8 lsb = Read_sensor_byte(address, regLSB);
    uint8 msb = Read_sensor_byte(address, regMSB);
    
    uint16 x = (msb << 8) | (lsb & 0xf0);
    x = x >> 4;
    
    return x;
}

uint16 y_accelerometer_read(uint32 address, uint8 regLSB, uint8 regMSB){
    uint8 lsb = Read_sensor_byte(address, regLSB);
    uint8 msb = Read_sensor_byte(address, regMSB);
    
    uint16 y = msb << 8 | (lsb & 0xf0);
    y = y >> 4;
    
    return y;
}

uint16 z_accelerometer_read(uint32 address, uint8 regLSB, uint8 regMSB){
    uint8 lsb = Read_sensor_byte(address, regLSB);
    uint8 msb = Read_sensor_byte(address, regMSB);
    
    uint16 z = msb << 8 | (lsb & 0xf0);
    z = z >> 4;
    
    return z;
}

uint16 gpio_expander_read(uint32 address, uint8 reg){
    // i think to read a expecific pin i have to pass the 
    uint16 read = Read_sensor_byte(address, reg);
    return 0;
}
/* [] END OF FILE */
