/*******************************************************************************
* File Name: COMP.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "COMP.h"

static COMP_BACKUP_STRUCT  COMP_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: COMP_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet COMP_SUT.c usage_COMP_Sleep_Wakeup
*******************************************************************************/
void COMP_Sleep(void)
{
    #if defined(COMP__PC)
        COMP_backup.pcState = COMP_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            COMP_backup.usbState = COMP_CR1_REG;
            COMP_USB_POWER_REG |= COMP_USBIO_ENTER_SLEEP;
            COMP_CR1_REG &= COMP_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(COMP__SIO)
        COMP_backup.sioState = COMP_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        COMP_SIO_REG &= (uint32)(~COMP_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: COMP_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to COMP_Sleep() for an example usage.
*******************************************************************************/
void COMP_Wakeup(void)
{
    #if defined(COMP__PC)
        COMP_PC = COMP_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            COMP_USB_POWER_REG &= COMP_USBIO_EXIT_SLEEP_PH1;
            COMP_CR1_REG = COMP_backup.usbState;
            COMP_USB_POWER_REG &= COMP_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(COMP__SIO)
        COMP_SIO_REG = COMP_backup.sioState;
    #endif
}


/* [] END OF FILE */
