/*******************************************************************************
* File Name: volt.h  
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

#if !defined(CY_PINS_volt_ALIASES_H) /* Pins volt_ALIASES_H */
#define CY_PINS_volt_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define volt_0			(volt__0__PC)
#define volt_0_PS		(volt__0__PS)
#define volt_0_PC		(volt__0__PC)
#define volt_0_DR		(volt__0__DR)
#define volt_0_SHIFT	(volt__0__SHIFT)
#define volt_0_INTR	((uint16)((uint16)0x0003u << (volt__0__SHIFT*2u)))

#define volt_INTR_ALL	 ((uint16)(volt_0_INTR))


#endif /* End Pins volt_ALIASES_H */


/* [] END OF FILE */
