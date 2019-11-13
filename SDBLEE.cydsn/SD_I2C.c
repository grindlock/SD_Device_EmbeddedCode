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
    uint8 read[2] = {0,0};
    I2C_1_I2CMasterSendStart(ADDR_HUMTEMP, I2C_1_I2C_WRITE_XFER_MODE, 100u);
    I2C_1_I2CMasterWriteByte(REG_HUMSENSOR_HUM, 100u);
    I2C_1_I2CMasterSendRestart(ADDR_HUMTEMP,I2C_1_I2C_READ_XFER_MODE, 100u);
    I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read[0],100u);
    I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &read[1],100u);
    I2C_1_I2CMasterSendStop(100u);

humidity = ((read[0] << 8) | read[1]);

    humidity = ((125 * humidity)/65536)-6;
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

int humidity_sensor_ID(){
    
    uint8 write_buff[2] ={REG_HUM_ID_0, REG_HUM_ID_1};
    
    volatile  uint8 read_buff1[4] = {0,0,0,0};
    volatile  uint8 read_buff2[4] = {0,0,0,0};
    
    I2C_1_I2CMasterWriteBuf(ADDR_HUMTEMP, (uint8 *){REG_HUM_ID_0,REG_HUM_ID_1}, 2, I2C_1_I2C_MODE_NO_STOP);
    while((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_WR_CMPLT) == 0){}
    
     I2C_1_I2CMasterReadBuf(ADDR_HUMTEMP, (uint8 *) read_buff1, 4, I2C_1_I2C_MODE_REPEAT_START);
    while((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_RD_CMPLT) == 0){}
    
     I2C_1_I2CMasterWriteBuf(ADDR_HUMTEMP, (uint8 *){REG_HUM_ID_2,REG_HUM_ID_3}, 2, I2C_1_I2C_MODE_NO_STOP);
    while((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_WR_CMPLT) == 0){}
    
     I2C_1_I2CMasterReadBuf(ADDR_HUMTEMP, (uint8 *) read_buff2, 4, I2C_1_I2C_MODE_REPEAT_START);
    while((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_RD_CMPLT) == 0){}
    
    return  read_buff2[0] == 0x06? 1: 0;
}

int temperature_TI431_sensor_ID(){
    return Read_sensor_word(ADDR_TEMP431, REG_TMP431ID) == 0x31? 1:0;
}
int temperature_TI432_sensor_ID(){
    return Read_sensor_word(ADDR_TEMP432, REG_TMP432ID) == 0x32? 1:0;
}

int current_voltage_sensor_ID(uint32 address){
    return Read_sensor_word(address,REG_POWER_VERSION) != 0x0000? 1 : 0;
}

int accelerametor_sensor_ID(){
 return Read_sensor_byte(ADDR_ACC,REG_ACCID) == 0xFA? 1: 0;   
}

void initialized_gpioExp(){
   I2C_1_I2CMasterSendStart(ADDR_GPIO,I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(REG_GPIO_CONFIG, 100u);
   I2C_1_I2CMasterWriteByte(0xFF, 100u);
   I2C_1_I2CMasterSendStop(100u);
}

uint8 read_gpioExp_pins(){
   
  // initialized_gpioExp(0xFF);

    uint8 pins = 0u;

   I2C_1_I2CMasterSendStart(ADDR_GPIO, I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(REG_GPIO_READ, 100u);
   I2C_1_I2CMasterSendRestart(ADDR_GPIO,I2C_1_I2C_READ_XFER_MODE, 100u);
   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &pins,100u);
   I2C_1_I2CMasterSendStop(100u);
    
    return pins;
}

/*void write_gpioExp_pins(uint8 data){

    initialized_gpioExp(0x00);

   I2C_1_I2CMasterSendStart(ADDR_GPIO, I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(REG_GPIO_WRITE, 100u);
   I2C_1_I2CMasterWriteByte((uint8 *) &data,100u);
   I2C_1_I2CMasterSendStop(100u);
}*/


/* [] END OF FILE */
