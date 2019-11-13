/*******************************************************************************
* File Name: Fan_Low.c  
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
#include "Fan_Low.h"

static Fan_Low_BACKUP_STRUCT  Fan_Low_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Fan_Low_Sleep
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
*  \snippet Fan_Low_SUT.c usage_Fan_Low_Sleep_Wakeup
*******************************************************************************/
void Fan_Low_Sleep(void)
{
    #if defined(Fan_Low__PC)
        Fan_Low_backup.pcState = Fan_Low_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Fan_Low_backup.usbState = Fan_Low_CR1_REG;
            Fan_Low_USB_POWER_REG |= Fan_Low_USBIO_ENTER_SLEEP;
            Fan_Low_CR1_REG &= Fan_Low_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Fan_Low__SIO)
        Fan_Low_backup.sioState = Fan_Low_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Fan_Low_SIO_REG &= (uint32)(~Fan_Low_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Fan_Low_Wakeup
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
*  Refer to Fan_Low_Sleep() for an example usage.
*******************************************************************************/
void Fan_Low_Wakeup(void)
{
    #if defined(Fan_Low__PC)
        Fan_Low_PC = Fan_Low_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Fan_Low_USB_POWER_REG &= Fan_Low_USBIO_EXIT_SLEEP_PH1;
            Fan_Low_CR1_REG = Fan_Low_backup.usbState;
            Fan_Low_USB_POWER_REG &= Fan_Low_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Fan_Low__SIO)
        Fan_Low_SIO_REG = Fan_Low_backup.sioState;
    #endif
}


/* [] END OF FILE */
