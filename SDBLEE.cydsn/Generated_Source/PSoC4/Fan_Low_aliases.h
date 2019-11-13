/*******************************************************************************
* File Name: Fan_Low.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Fan_Low_ALIASES_H) /* Pins Fan_Low_ALIASES_H */
#define CY_PINS_Fan_Low_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Fan_Low_0			(Fan_Low__0__PC)
#define Fan_Low_0_PS		(Fan_Low__0__PS)
#define Fan_Low_0_PC		(Fan_Low__0__PC)
#define Fan_Low_0_DR		(Fan_Low__0__DR)
#define Fan_Low_0_SHIFT	(Fan_Low__0__SHIFT)
#define Fan_Low_0_INTR	((uint16)((uint16)0x0003u << (Fan_Low__0__SHIFT*2u)))

#define Fan_Low_INTR_ALL	 ((uint16)(Fan_Low_0_INTR))


#endif /* End Pins Fan_Low_ALIASES_H */


/* [] END OF FILE */
