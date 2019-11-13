/*******************************************************************************
* File Name: Fan_Low.h  
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

#if !defined(CY_PINS_Fan_Low_H) /* Pins Fan_Low_H */
#define CY_PINS_Fan_Low_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Fan_Low_aliases.h"


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
} Fan_Low_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Fan_Low_Read(void);
void    Fan_Low_Write(uint8 value);
uint8   Fan_Low_ReadDataReg(void);
#if defined(Fan_Low__PC) || (CY_PSOC4_4200L) 
    void    Fan_Low_SetDriveMode(uint8 mode);
#endif
void    Fan_Low_SetInterruptMode(uint16 position, uint16 mode);
uint8   Fan_Low_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Fan_Low_Sleep(void); 
void Fan_Low_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Fan_Low__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Fan_Low_DRIVE_MODE_BITS        (3)
    #define Fan_Low_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Fan_Low_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Fan_Low_SetDriveMode() function.
         *  @{
         */
        #define Fan_Low_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Fan_Low_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Fan_Low_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Fan_Low_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Fan_Low_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Fan_Low_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Fan_Low_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Fan_Low_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Fan_Low_MASK               Fan_Low__MASK
#define Fan_Low_SHIFT              Fan_Low__SHIFT
#define Fan_Low_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Fan_Low_SetInterruptMode() function.
     *  @{
     */
        #define Fan_Low_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Fan_Low_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Fan_Low_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Fan_Low_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Fan_Low__SIO)
    #define Fan_Low_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Fan_Low__PC) && (CY_PSOC4_4200L)
    #define Fan_Low_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Fan_Low_USBIO_DISABLE              ((uint32)(~Fan_Low_USBIO_ENABLE))
    #define Fan_Low_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Fan_Low_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Fan_Low_USBIO_ENTER_SLEEP          ((uint32)((1u << Fan_Low_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Fan_Low_USBIO_SUSPEND_DEL_SHIFT)))
    #define Fan_Low_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Fan_Low_USBIO_SUSPEND_SHIFT)))
    #define Fan_Low_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Fan_Low_USBIO_SUSPEND_DEL_SHIFT)))
    #define Fan_Low_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Fan_Low__PC)
    /* Port Configuration */
    #define Fan_Low_PC                 (* (reg32 *) Fan_Low__PC)
#endif
/* Pin State */
#define Fan_Low_PS                     (* (reg32 *) Fan_Low__PS)
/* Data Register */
#define Fan_Low_DR                     (* (reg32 *) Fan_Low__DR)
/* Input Buffer Disable Override */
#define Fan_Low_INP_DIS                (* (reg32 *) Fan_Low__PC2)

/* Interrupt configuration Registers */
#define Fan_Low_INTCFG                 (* (reg32 *) Fan_Low__INTCFG)
#define Fan_Low_INTSTAT                (* (reg32 *) Fan_Low__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Fan_Low_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Fan_Low__SIO)
    #define Fan_Low_SIO_REG            (* (reg32 *) Fan_Low__SIO)
#endif /* (Fan_Low__SIO_CFG) */

/* USBIO registers */
#if !defined(Fan_Low__PC) && (CY_PSOC4_4200L)
    #define Fan_Low_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Fan_Low_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Fan_Low_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Fan_Low_DRIVE_MODE_SHIFT       (0x00u)
#define Fan_Low_DRIVE_MODE_MASK        (0x07u << Fan_Low_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Fan_Low_H */


/* [] END OF FILE */
