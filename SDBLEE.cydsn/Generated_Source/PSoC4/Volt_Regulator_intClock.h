/*******************************************************************************
* File Name: Volt_Regulator_intClock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Volt_Regulator_intClock_H)
#define CY_CLOCK_Volt_Regulator_intClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void Volt_Regulator_intClock_StartEx(uint32 alignClkDiv);
#define Volt_Regulator_intClock_Start() \
    Volt_Regulator_intClock_StartEx(Volt_Regulator_intClock__PA_DIV_ID)

#else

void Volt_Regulator_intClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void Volt_Regulator_intClock_Stop(void);

void Volt_Regulator_intClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Volt_Regulator_intClock_GetDividerRegister(void);
uint8  Volt_Regulator_intClock_GetFractionalDividerRegister(void);

#define Volt_Regulator_intClock_Enable()                         Volt_Regulator_intClock_Start()
#define Volt_Regulator_intClock_Disable()                        Volt_Regulator_intClock_Stop()
#define Volt_Regulator_intClock_SetDividerRegister(clkDivider, reset)  \
    Volt_Regulator_intClock_SetFractionalDividerRegister((clkDivider), 0u)
#define Volt_Regulator_intClock_SetDivider(clkDivider)           Volt_Regulator_intClock_SetDividerRegister((clkDivider), 1u)
#define Volt_Regulator_intClock_SetDividerValue(clkDivider)      Volt_Regulator_intClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define Volt_Regulator_intClock_DIV_ID     Volt_Regulator_intClock__DIV_ID

#define Volt_Regulator_intClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define Volt_Regulator_intClock_CTRL_REG   (*(reg32 *)Volt_Regulator_intClock__CTRL_REGISTER)
#define Volt_Regulator_intClock_DIV_REG    (*(reg32 *)Volt_Regulator_intClock__DIV_REGISTER)

#define Volt_Regulator_intClock_CMD_DIV_SHIFT          (0u)
#define Volt_Regulator_intClock_CMD_PA_DIV_SHIFT       (8u)
#define Volt_Regulator_intClock_CMD_DISABLE_SHIFT      (30u)
#define Volt_Regulator_intClock_CMD_ENABLE_SHIFT       (31u)

#define Volt_Regulator_intClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << Volt_Regulator_intClock_CMD_DISABLE_SHIFT))
#define Volt_Regulator_intClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << Volt_Regulator_intClock_CMD_ENABLE_SHIFT))

#define Volt_Regulator_intClock_DIV_FRAC_MASK  (0x000000F8u)
#define Volt_Regulator_intClock_DIV_FRAC_SHIFT (3u)
#define Volt_Regulator_intClock_DIV_INT_MASK   (0xFFFFFF00u)
#define Volt_Regulator_intClock_DIV_INT_SHIFT  (8u)

#else 

#define Volt_Regulator_intClock_DIV_REG        (*(reg32 *)Volt_Regulator_intClock__REGISTER)
#define Volt_Regulator_intClock_ENABLE_REG     Volt_Regulator_intClock_DIV_REG
#define Volt_Regulator_intClock_DIV_FRAC_MASK  Volt_Regulator_intClock__FRAC_MASK
#define Volt_Regulator_intClock_DIV_FRAC_SHIFT (16u)
#define Volt_Regulator_intClock_DIV_INT_MASK   Volt_Regulator_intClock__DIVIDER_MASK
#define Volt_Regulator_intClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_Volt_Regulator_intClock_H) */

/* [] END OF FILE */
