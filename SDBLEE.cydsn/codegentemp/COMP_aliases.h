/*******************************************************************************
* File Name: COMP.h  
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

#if !defined(CY_PINS_COMP_ALIASES_H) /* Pins COMP_ALIASES_H */
#define CY_PINS_COMP_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define COMP_0			(COMP__0__PC)
#define COMP_0_PS		(COMP__0__PS)
#define COMP_0_PC		(COMP__0__PC)
#define COMP_0_DR		(COMP__0__DR)
#define COMP_0_SHIFT	(COMP__0__SHIFT)
#define COMP_0_INTR	((uint16)((uint16)0x0003u << (COMP__0__SHIFT*2u)))

#define COMP_INTR_ALL	 ((uint16)(COMP_0_INTR))


#endif /* End Pins COMP_ALIASES_H */


/* [] END OF FILE */
