/*******************************************************************************
* File Name: ST3_4.h  
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

#if !defined(CY_PINS_ST3_4_ALIASES_H) /* Pins ST3_4_ALIASES_H */
#define CY_PINS_ST3_4_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define ST3_4_0			(ST3_4__0__PC)
#define ST3_4_0_PS		(ST3_4__0__PS)
#define ST3_4_0_PC		(ST3_4__0__PC)
#define ST3_4_0_DR		(ST3_4__0__DR)
#define ST3_4_0_SHIFT	(ST3_4__0__SHIFT)
#define ST3_4_0_INTR	((uint16)((uint16)0x0003u << (ST3_4__0__SHIFT*2u)))

#define ST3_4_INTR_ALL	 ((uint16)(ST3_4_0_INTR))


#endif /* End Pins ST3_4_ALIASES_H */


/* [] END OF FILE */
