/*******************************************************************************
* File Name: SDAT.h  
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

#if !defined(CY_PINS_SDAT_ALIASES_H) /* Pins SDAT_ALIASES_H */
#define CY_PINS_SDAT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SDAT_0			(SDAT__0__PC)
#define SDAT_0_PS		(SDAT__0__PS)
#define SDAT_0_PC		(SDAT__0__PC)
#define SDAT_0_DR		(SDAT__0__DR)
#define SDAT_0_SHIFT	(SDAT__0__SHIFT)
#define SDAT_0_INTR	((uint16)((uint16)0x0003u << (SDAT__0__SHIFT*2u)))

#define SDAT_INTR_ALL	 ((uint16)(SDAT_0_INTR))


#endif /* End Pins SDAT_ALIASES_H */


/* [] END OF FILE */
