/*******************************************************************************
* File Name: volt.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_volt_H) /* Pins volt_H */
#define CY_PINS_volt_H

#include "cytypes.h"
#include "cyfitter.h"
#include "volt_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} volt_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   volt_Read(void);
void    volt_Write(uint8 value);
uint8   volt_ReadDataReg(void);
#if defined(volt__PC) || (CY_PSOC4_4200L) 
    void    volt_SetDriveMode(uint8 mode);
#endif
void    volt_SetInterruptMode(uint16 position, uint16 mode);
uint8   volt_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void volt_Sleep(void); 
void volt_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(volt__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define volt_DRIVE_MODE_BITS        (3)
    #define volt_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - volt_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the volt_SetDriveMode() function.
         *  @{
         */
        #define volt_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define volt_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define volt_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define volt_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define volt_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define volt_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define volt_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define volt_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define volt_MASK               volt__MASK
#define volt_SHIFT              volt__SHIFT
#define volt_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in volt_SetInterruptMode() function.
     *  @{
     */
        #define volt_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define volt_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define volt_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define volt_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(volt__SIO)
    #define volt_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(volt__PC) && (CY_PSOC4_4200L)
    #define volt_USBIO_ENABLE               ((uint32)0x80000000u)
    #define volt_USBIO_DISABLE              ((uint32)(~volt_USBIO_ENABLE))
    #define volt_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define volt_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define volt_USBIO_ENTER_SLEEP          ((uint32)((1u << volt_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << volt_USBIO_SUSPEND_DEL_SHIFT)))
    #define volt_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << volt_USBIO_SUSPEND_SHIFT)))
    #define volt_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << volt_USBIO_SUSPEND_DEL_SHIFT)))
    #define volt_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(volt__PC)
    /* Port Configuration */
    #define volt_PC                 (* (reg32 *) volt__PC)
#endif
/* Pin State */
#define volt_PS                     (* (reg32 *) volt__PS)
/* Data Register */
#define volt_DR                     (* (reg32 *) volt__DR)
/* Input Buffer Disable Override */
#define volt_INP_DIS                (* (reg32 *) volt__PC2)

/* Interrupt configuration Registers */
#define volt_INTCFG                 (* (reg32 *) volt__INTCFG)
#define volt_INTSTAT                (* (reg32 *) volt__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define volt_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(volt__SIO)
    #define volt_SIO_REG            (* (reg32 *) volt__SIO)
#endif /* (volt__SIO_CFG) */

/* USBIO registers */
#if !defined(volt__PC) && (CY_PSOC4_4200L)
    #define volt_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define volt_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define volt_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define volt_DRIVE_MODE_SHIFT       (0x00u)
#define volt_DRIVE_MODE_MASK        (0x07u << volt_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins volt_H */


/* [] END OF FILE */
