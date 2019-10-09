/*******************************************************************************
* File Name: UART_1.h
* Version 1.50
*
* Description:
*  This file provides constants and parameter values for the Software Transmit
*  UART Component.
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef CY_SW_TX_UART_UART_1_H
#define CY_SW_TX_UART_UART_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"

#define UART_1_BAUD_RATE                      (9600u)
#define UART_1_PIN_STATIC_MODE                (1u)


/***************************************
*        Function Prototypes
***************************************/
#if(UART_1_PIN_STATIC_MODE == 1u)
    void UART_1_Start(void) ;
#else
    void UART_1_StartEx(uint8 port, uint8 pin) ;
#endif /* (UART_1_PIN_STATIC_MODE == 1u) */

void UART_1_Stop(void) ;
void UART_1_PutChar(uint8 txDataByte) ;
void UART_1_PutString(const char8 string[]) ;
void UART_1_PutArray(const uint8 array[], uint32 byteCount) ;
void UART_1_PutHexByte(uint8 txHexByte) ;
void UART_1_PutHexInt(uint16 txHexInt) ;
void UART_1_PutCRLF(void) ;

#endif /* CY_SW_TX_UART_UART_1_H */


/* [] END OF FILE */
