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

// Data 
#include "project.h"
#include <time.h>

#include <stdio.h>
#include <stdlib.h>

#include "SD_I2C.h"

extern CYBLE_GAPP_DISC_MODE_INFO_T cyBle_discoveryModeInfo;
#define advPayload (cyBle_discoveryModeInfo.advData->advData)

CYBLE_CONN_HANDLE_T connHandle;
CYBLE_GATT_HANDLE_VALUE_PAIR_T thermoHandle;

uint8 collectedData[4];
uint8 isNotify = 0;
uint8 updateIsNotifyCCCDAttr = 0;
uint8 bleConnected = 0;

uint8 thermostat[4] = {1,1};
uint16 voltFromPin8; 
uint8 adcVoltConverted;

// 4 bytes
typedef struct{
    int8 err_Power;
    int8 err_Temp;
    int8 err_Hum;
    int8 err_Acc;
    
}errorCode;

errorCode error;

// 36 bytes
typedef struct{
    
    int16 localTemp;
    int16 remoteTemp1;
    int16 remoteTemp2; 
    int16 remoteTemp3;
    uint16 humidity;
    uint16 voltCompressor;
    uint16 voltFan;
    uint16 volt;
    uint16 currentCompressor;
    uint16 currentFan; 
    uint16 current;
    uint16 lineFreqComp;
    uint16 lineFreqFan;
    uint16 linFreq;
    uint16 airFlow;
    uint16 accX;
    uint16 accY;
    uint16 accZ;
    
}dataCollected;

dataCollected sensorData;
// 5 bytes
typedef struct{
    uint8 compressor;
    uint8 lowFan;
    uint8 highFan;
    uint16 setTemperature;
} thermostatData ;

thermostatData thermo;

void updateThermostatData(void){
    
    thermoHandle.attrHandle = CYBLE_RVAC_THERMOSTAT_THERMOCCCD_DESC_HANDLE;
    thermoHandle.value.val = thermostat;
    thermoHandle.value.len = 2; 
    thermoHandle.value.actualLen = 2; 
    
    CyBle_GattsWriteAttributeValue(&thermoHandle, 0, &cyBle_connHandle, 0);
}

void bleStack(uint32 event, void *eventParam){
    
    CYBLE_GATTS_WRITE_REQ_PARAM_T wrReq;
    
    switch(event){
     
        case CYBLE_EVT_STACK_ON:
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);

        case CYBLE_EVT_GAP_DEVICE_CONNECTED:
            //CyBle_GappStopAdvertisement(); 
            break;
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            isNotify = 0;
            break;
        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
             if(CyBle_GetState() == CYBLE_STATE_DISCONNECTED){
                 CyBle_GappStartAdvertisement(CYBLE_SCANNING_FAST);
            }
            break;
        case CYBLE_EVT_GATT_CONNECT_IND:
          
            bleConnected = 1;
            CyBle_GappStopAdvertisement();
            break;
        case CYBLE_EVT_GATT_DISCONNECT_IND:
        
            isNotify = 0;
            bleConnected = 0;
            // Update the notifications CCCD
            updateIsNotifyCCCDAttr = 1;
            
            // update the thermostat array with the thermosstat info.
            // ex. themostat[0] = readSensor();
            // update the data in the thermostat attibute
            updateThermostatData();
            
           break;
        case CYBLE_EVT_GATTS_WRITE_REQ:
            wrReq = *(CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam; //CYBLE_DAC_SERVICE_VOLT_VOLTCCCD_DESC_HANDLE
           
            // This handle the notofications
            if(wrReq.handleValPair.attrHandle == CYBLE_RVAC_SENSORS_SENSORCCCD_DESC_HANDLE){
                
               // CyBle_GattsWriteAttributeValue( &wrReq->handleValPair, 0, &connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
                isNotify = wrReq.handleValPair.value.val[0];//CYBLE_RVAC_SENSOR_SENSORCCCD_DESC_INDEX];
                
                updateIsNotifyCCCDAttr = 1;
            }
            
            // This handle data incoming
            if(wrReq.handleValPair.attrHandle == CYBLE_RVAC_THERMOSTAT_CHAR_HANDLE){
            
                thermostat[0] = wrReq.handleValPair.value.val[0];
                thermostat[1] = wrReq.handleValPair.value.val[1];
                
                updateThermostatData();
                
            }

            CyBle_GattsWriteRsp(cyBle_connHandle);
            
            break; 
        
     default:
        break;
    }
    
}

void SendDataNotify( uint8 len){
    CYBLE_GATTS_HANDLE_VALUE_NTF_T notiHandle;
    

     notiHandle.attrHandle = CYBLE_RVAC_SENSORS_CHAR_HANDLE;
     notiHandle.value.val = (uint8 *)&sensorData;
     notiHandle.value.len = len;
        
        CyBle_GattsNotification(cyBle_connHandle, &notiHandle);

}

void updateNotificationCCCD(void){
    CYBLE_GATT_HANDLE_VALUE_PAIR_T sensorNotCCCDHandle;
    
    uint8 sensorCCCDVal[2];
    
    if(updateIsNotifyCCCDAttr == 1){
        
     updateIsNotifyCCCDAttr = 0;
        sensorCCCDVal[0] = isNotify;
        sensorCCCDVal[1] = 0x00;
        
        sensorNotCCCDHandle.attrHandle = CYBLE_RVAC_SENSORS_SENSORCCCD_DESC_HANDLE;
        sensorNotCCCDHandle.value.val = sensorCCCDVal;
        sensorNotCCCDHandle.value.len = 2;
        
        CyBle_GattsWriteAttributeValue(&sensorNotCCCDHandle, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
        CyBle_ProcessEvents();
    }
}



uint8 randomNum(){
 
    return (uint8) (rand()%15)+1;
}

void wdtSleepInt(){
     Red_Write(0);
        collectedData[0] = randomNum();
        collectedData[1] = randomNum();
        collectedData[2] = randomNum();
        collectedData[3] = randomNum();
 
     CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER0_INT);
}

void check_sensors(){
    error.err_Power = 0;
    error.err_Temp = 0;
    error.err_Hum = 0;
    error.err_Acc = 0;
    
    if(!humidity_sensor_ID()){
        error.err_Hum = 1;
    }
    else if(!temperature_TI431_sensor_ID()){
        error.err_Temp = 1;
    }
    else if(!temperature_TI432_sensor_ID()){
        error.err_Temp = 1;
    }
    else if(!current_voltage_sensor_ID(ADDR_POWER1)){
        error.err_Power = 1;
    }
    else if(!current_voltage_sensor_ID(ADDR_POWER2)){
        error.err_Power = 1;
    }
    else if(!current_voltage_sensor_ID(ADDR_POWER3)){
        error.err_Power = 1;
    }
    else if (!accelerametor_sensor_ID()){
        error.err_Acc = 1;
    }
    
}

//CY_ISR(Volt_Regulator_SAR_SEQ_ISR_LOC){
//    
//    uint32 intr_status;
//    intr_status =  Volt_Regulator_SAR_INTR_REG;;
//    
//    // place code here
//    
//    Volt_Regulator_SAR_INTR_REG = intr_status;
//    
//    
//}

void read_i2c_sensors(){
sensorData.humidity = humidity_read(ADDR_HUMTEMP, REG_HUMSENSOR_HUM);
sensorData.localTemp = temperature_local_read(ADDR_TEMP431, REG_LH_TMP431);
sensorData.remoteTemp1 = temperature_remote_read(ADDR_TEMP431, REG_RH_TEMP431);
sensorData.remoteTemp2 = temperature_remote_read(ADDR_TEMP432, REG_RH1_TMP432);
sensorData.remoteTemp3 = temperature_remote_read(ADDR_TEMP432, REG_RH2_TMP432);
sensorData.currentCompressor = cucurrent_read(ADDR_POWER1, REG_CURRRMS);
sensorData.currentFan = current_read(ADDR_POWER2, REG_CURRRMS);
sensorData.current = current_read(ADDR_POWER3, REG_CURRRMS);
sensorData.voltCompressor = voltage_read(ADDR_POWER1, REG_VOLTRMS);
sensorData.voltFan = voltage_read(ADDR_POWER2, REG_VOLTRMS);
sensorData.volt = voltage_read(ADDR_POWER3, REG_VOLTRMS);
sensorData.lineFreqComp = line_frequency_read(ADDR_POWER1, REG_LINEFREQ);
sensorData.lineFreqFan = line_frequency_read(ADDR_POWER2, REG_LINEFREQ);
sensorData.linFreq = line_frequency_read(ADDR_POWER3, REG_LINEFREQ);
sensorData.accX = x_accelerometer_read(ADDR_ACC, REG_XLSB, REG_XMSB);   
sensorData.accZ = y_accelerometer_read(ADDR_ACC, REG_YLSB, REG_YMSB); 
sensorData.accY = z_accelerometer_read(ADDR_ACC, REG_ZLSB, REG_ZMSB); 
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    isr_1_StartEx(wdtSleepInt); // sleep every second
    CySysWdtEnable(CY_SYS_WDT_COUNTER0);
    
    
    CyBle_Start(bleStack);

    
    I2C_1_Start();
    
    UART_1_Start();
    
    Volt_Regulator_Start(); // ADC at P3.2
//    Volt_Regulator_SAR_SEQ_IRQ_Enable();
//    Volt_Regulator_SAR(Volt_Regulator_SAR_SEQ_ISR_LOC);

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    srand(time(0));
    
    uint8 prevRead = 0;
    
    for(;;)
    {
        Red_Write(1);
        //WDT_ISR_StartEx();
       
        /* Place your application code here. */
        advPayload[16] = collectedData[0];
        advPayload[17] = collectedData[1];
        advPayload[18] = collectedData[2];
        advPayload[19] = collectedData[3];
        
        
        voltFromPin8 = Volt_Regulator_GetResult16(0);
        adcVoltConverted = Volt_Regulator_CountsTo_Volts(0,voltFromPin8)*10;
        
        //turn on or off the volt regulator
        if(adcVoltConverted != prevRead){
            prevRead = adcVoltConverted;
            if( adcVoltConverted >= 7){
                CE_Pin_Write(1);
                check_sensors();
               
            }
            else{
                CE_Pin_Write(0);
            }
        }
        
        
        

        
        ///BLE code
       if(bleConnected == 1){

        updateNotificationCCCD();
        
        if(isNotify == 1){
            Green_Write(1);
            if(CyBle_GattGetBusStatus() == CYBLE_STACK_STATE_FREE){
             Blue_Write(0);
                SendDataNotify(sizeof(sensorData));
                Blue_Write(1);
           }
        }
        else{
            Green_Write(thermostat[0]);
        }
    }else{ 
        Blue_Write(1);
        Green_Write(1);}
    //END Ble code
        


        CyBle_GapUpdateAdvData(cyBle_discoveryModeInfo.advData, cyBle_discoveryModeInfo.scanRspData); //Update data in Advertisment Packet 
        CyBle_ProcessEvents();
    }
}

/* [] END OF FILE */
