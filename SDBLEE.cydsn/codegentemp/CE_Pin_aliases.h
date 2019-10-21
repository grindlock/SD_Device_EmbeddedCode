/*******************************************************************************
* File Name: CE_Pin.h  
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

#if !defined(CY_PINS_CE_Pin_ALIASES_H) /* Pins CE_Pin_ALIASES_H */
#define CY_PINS_CE_Pin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define CE_Pin_0			(CE_Pin__0__PC)
#define CE_Pin_0_PS		(CE_Pin__0__PS)
#define CE_Pin_0_PC		(CE_Pin__0__PC)
#define CE_Pin_0_DR		(CE_Pin__0__DR)
#define CE_Pin_0_SHIFT	(CE_Pin__0__SHIFT)
#define CE_Pin_0_INTR	((uint16)((uint16)0x0003u << (CE_Pin__0__SHIFT*2u)))

#define CE_Pin_INTR_ALL	 ((uint16)(CE_Pin_0_INTR))


#endif /* End Pins CE_Pin_ALIASES_H */


/* [] END OF FILE */
