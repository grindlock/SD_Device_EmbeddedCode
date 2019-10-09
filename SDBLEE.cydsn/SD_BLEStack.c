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
//#include "SD_BLEStack.h"
//
//void bleStack(uint32 event, void* eventParam){
//    CYBLE_API_RESULT_T apiResult;
//    CYBLE_GAP_CONN_UPDATE_PARAM_T gapConnUpdateParam;
//    CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReq;
//    switch(event){
//     
//        case CYBLE_EVT_STACK_ON:
//            apiResult = CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
//            if(apiResult != CYBLE_ERROR_OK){}
//            break;
//        case CYBLE_EVT_HARDWARE_ERROR:
//            // handle what to do
//            break;
//        case CYBLE_EVT_GAP_DEVICE_CONNECTED:
//            break;
//        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
//            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
//            break;
//        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
//             if(CYBLE_STATE_DISCONNECTED == CyBle_GetState()){
//                apiResult = CyBle_GappStartAdvertisement(CYBLE_SCANNING_FAST);
//            }
//            break;
//        case CYBLE_EVT_GATT_CONNECT_IND:
//            connHandle = *(CYBLE_CONN_HANDLE_T *)eventParam;
//            break;
//        case CYBLE_EVT_GATT_DISCONNECT_IND:
//            connHandle.bdHandle = 0;
//            break;
//        case CYBLE_EVT_GATTS_WRITE_REQ:
//            wrReq = (CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam; //CYBLE_DAC_SERVICE_VOLT_VOLTCCCD_DESC_HANDLE
////            if(wrReq->handleValPair.attrHandle == CYBLE_MYADC_VOLT_VOLTCCCD_DESC_HANDLE){
////                CyBle_GattsWriteAttributeValue( &wrReq->handleValPair, 0, &connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
////                dacNotification = wrReq->handleValPair.value.val[0];
////            }
////            if(wrReq->handleValPair.attrHandle == CYBLE_RGB_RGB_LED_CHAR_HANDLE){
////              if(CYBLE_GATT_ERR_NONE == CyBle_GattsWriteAttributeValue(&wrReq->handleValPair, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED)){
////                    
////                    Red_Write(!wrReq->handleValPair.value.val[0]);
////                    CyBle_GattsWriteRsp(cyBle_connHandle);
////                }   
////            }
//            CyBle_GattsWriteRsp(connHandle);
//            
//            break; 
//        
//     default:
//        break;
//    }
//    
//}

/* [] END OF FILE */
