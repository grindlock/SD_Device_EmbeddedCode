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

struct errorCode{
    
    
};

struct dataCollected {
    
    float localTemp;
    float remoteTemp1;
    float remoteTemp2; 
    float remoteTemp3;
    float voltCompressor;
    float voltFan;
    float volt;
    float currentCompressor;
    float currentFan; 
    float current;
    float lineFreqComp;
    float lineFreqFan;
    float linFreq;
    float airFlow;
    uint16 accX;
    uint16 accY;
    uint16 accZ;
    
};

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
            if(wrReq.handleValPair.attrHandle == CYBLE_RVAC_SENSOR_SENSORCCCD_DESC_HANDLE){
                
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

void SendDataNotify(uint8 *data, uint8 len){
    CYBLE_GATTS_HANDLE_VALUE_NTF_T notiHandle;
    

     notiHandle.attrHandle = CYBLE_RVAC_SENSOR_CHAR_HANDLE;
     notiHandle.value.val = data;
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
        
        sensorNotCCCDHandle.attrHandle = CYBLE_RVAC_SENSOR_SENSORCCCD_DESC_HANDLE;
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
    
    if(test_sensor(ADDR_HUMTEMP, )==0){
    }
    else if(test_sensor(ADDR_TEMP431, REG_MANUF_ID431)==0){
    }
    else if(test_sensor(ADDR_TEMP432, REG_MANUF_ID432)==0){
    }
    else if(test_sensor()==0){
    }
    else if(test_sensor()==0){
    }
    else if(test_sensor()==0){
    }
    else if(test_sensor()==0){
    }
    else if(test_sensor()==0){
    }
    else if(test_sensor()==0){
    }
    else if(test_sensor()==0){
    }
    else if(test_sensor()==0){
    }
    else if(test_sensor()==0){
    }
    else if(test_sensor()==0){
    }
    
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    isr_1_StartEx(wdtSleepInt);
    CySysWdtEnable(CY_SYS_WDT_COUNTER0);
    
    
    CyBle_Start(bleStack);
    //isr_1_Start();
    
    I2C_1_Start();
    
    UART_1_Start();

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    srand(time(0));
    for(;;)
    {
        Red_Write(1);
        //WDT_ISR_StartEx();
       
        /* Place your application code here. */
        
        
        
        advPayload[16] = collectedData[0];
        advPayload[17] = collectedData[1];
        advPayload[18] = collectedData[2];
        advPayload[19] = collectedData[3];
        
        

       if(bleConnected == 1){

        updateNotificationCCCD();
        
        if(isNotify == 1){
            Green_Write(1);
            if(CyBle_GattGetBusStatus() == CYBLE_STACK_STATE_FREE){
             Blue_Write(0);
                SendDataNotify(collectedData, 4);
                Blue_Write(1);
           }
        }
        else{
            Green_Write(thermostat[0]);
        }
    }else{ 
        Blue_Write(1);
        Green_Write(1);}
        
    //UART_1_PutChar(thermostat[0]);

        CyBle_GapUpdateAdvData(cyBle_discoveryModeInfo.advData, cyBle_discoveryModeInfo.scanRspData); //Update data in Advertisment Packet 
        CyBle_ProcessEvents();
    }
}

/* [] END OF FILE */
