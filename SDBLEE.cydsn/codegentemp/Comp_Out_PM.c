/*******************************************************************************
* File Name: Comp_Out.c  
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
#include "Comp_Out.h"

static Comp_Out_BACKUP_STRUCT  Comp_Out_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Comp_Out_Sleep
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
*  \snippet Comp_Out_SUT.c usage_Comp_Out_Sleep_Wakeup
*******************************************************************************/
void Comp_Out_Sleep(void)
{
    #if defined(Comp_Out__PC)
        Comp_Out_backup.pcState = Comp_Out_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Comp_Out_backup.usbState = Comp_Out_CR1_REG;
            Comp_Out_USB_POWER_REG |= Comp_Out_USBIO_ENTER_SLEEP;
            Comp_Out_CR1_REG &= Comp_Out_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Comp_Out__SIO)
        Comp_Out_backup.sioState = Comp_Out_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Comp_Out_SIO_REG &= (uint32)(~Comp_Out_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Comp_Out_Wakeup
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
*  Refer to Comp_Out_Sleep() for an example usage.
*******************************************************************************/
void Comp_Out_Wakeup(void)
{
    #if defined(Comp_Out__PC)
        Comp_Out_PC = Comp_Out_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Comp_Out_USB_POWER_REG &= Comp_Out_USBIO_EXIT_SLEEP_PH1;
            Comp_Out_CR1_REG = Comp_Out_backup.usbState;
            Comp_Out_USB_POWER_REG &= Comp_Out_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Comp_Out__SIO)
        Comp_Out_SIO_REG = Comp_Out_backup.sioState;
    #endif
}


/* [] END OF FILE */
