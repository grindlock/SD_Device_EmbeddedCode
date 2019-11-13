/*******************************************************************************
* File Name: Comp_Out.h  
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

#if !defined(CY_PINS_Comp_Out_ALIASES_H) /* Pins Comp_Out_ALIASES_H */
#define CY_PINS_Comp_Out_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Comp_Out_0			(Comp_Out__0__PC)
#define Comp_Out_0_PS		(Comp_Out__0__PS)
#define Comp_Out_0_PC		(Comp_Out__0__PC)
#define Comp_Out_0_DR		(Comp_Out__0__DR)
#define Comp_Out_0_SHIFT	(Comp_Out__0__SHIFT)
#define Comp_Out_0_INTR	((uint16)((uint16)0x0003u << (Comp_Out__0__SHIFT*2u)))

#define Comp_Out_INTR_ALL	 ((uint16)(Comp_Out_0_INTR))


#endif /* End Pins Comp_Out_ALIASES_H */


/* [] END OF FILE */
