/*******************************************************************************
* File Name: COMP.h  
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

#if !defined(CY_PINS_COMP_H) /* Pins COMP_H */
#define CY_PINS_COMP_H

#include "cytypes.h"
#include "cyfitter.h"
#include "COMP_aliases.h"


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
} COMP_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   COMP_Read(void);
void    COMP_Write(uint8 value);
uint8   COMP_ReadDataReg(void);
#if defined(COMP__PC) || (CY_PSOC4_4200L) 
    void    COMP_SetDriveMode(uint8 mode);
#endif
void    COMP_SetInterruptMode(uint16 position, uint16 mode);
uint8   COMP_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void COMP_Sleep(void); 
void COMP_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(COMP__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define COMP_DRIVE_MODE_BITS        (3)
    #define COMP_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - COMP_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the COMP_SetDriveMode() function.
         *  @{
         */
        #define COMP_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define COMP_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define COMP_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define COMP_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define COMP_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define COMP_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define COMP_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define COMP_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define COMP_MASK               COMP__MASK
#define COMP_SHIFT              COMP__SHIFT
#define COMP_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in COMP_SetInterruptMode() function.
     *  @{
     */
        #define COMP_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define COMP_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define COMP_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define COMP_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(COMP__SIO)
    #define COMP_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(COMP__PC) && (CY_PSOC4_4200L)
    #define COMP_USBIO_ENABLE               ((uint32)0x80000000u)
    #define COMP_USBIO_DISABLE              ((uint32)(~COMP_USBIO_ENABLE))
    #define COMP_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define COMP_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define COMP_USBIO_ENTER_SLEEP          ((uint32)((1u << COMP_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << COMP_USBIO_SUSPEND_DEL_SHIFT)))
    #define COMP_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << COMP_USBIO_SUSPEND_SHIFT)))
    #define COMP_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << COMP_USBIO_SUSPEND_DEL_SHIFT)))
    #define COMP_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(COMP__PC)
    /* Port Configuration */
    #define COMP_PC                 (* (reg32 *) COMP__PC)
#endif
/* Pin State */
#define COMP_PS                     (* (reg32 *) COMP__PS)
/* Data Register */
#define COMP_DR                     (* (reg32 *) COMP__DR)
/* Input Buffer Disable Override */
#define COMP_INP_DIS                (* (reg32 *) COMP__PC2)

/* Interrupt configuration Registers */
#define COMP_INTCFG                 (* (reg32 *) COMP__INTCFG)
#define COMP_INTSTAT                (* (reg32 *) COMP__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define COMP_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(COMP__SIO)
    #define COMP_SIO_REG            (* (reg32 *) COMP__SIO)
#endif /* (COMP__SIO_CFG) */

/* USBIO registers */
#if !defined(COMP__PC) && (CY_PSOC4_4200L)
    #define COMP_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define COMP_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define COMP_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define COMP_DRIVE_MODE_SHIFT       (0x00u)
#define COMP_DRIVE_MODE_MASK        (0x07u << COMP_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins COMP_H */


/* [] END OF FILE */
