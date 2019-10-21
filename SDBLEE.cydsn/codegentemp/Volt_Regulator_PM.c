/*******************************************************************************
* File Name: Volt_Regulator_PM.c
* Version 2.50
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Volt_Regulator.h"


/***************************************
* Local data allocation
***************************************/

static Volt_Regulator_BACKUP_STRUCT  Volt_Regulator_backup =
{
    Volt_Regulator_DISABLED,
    0u    
};


/*******************************************************************************
* Function Name: Volt_Regulator_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Volt_Regulator_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: Volt_Regulator_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Volt_Regulator_RestoreConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: Volt_Regulator_Sleep
********************************************************************************
*
* Summary:
*  Stops the ADC operation and saves the configuration registers and component
*  enable state. Should be called just prior to entering sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Volt_Regulator_backup - modified.
*
*******************************************************************************/
void Volt_Regulator_Sleep(void)
{
    /* During deepsleep/ hibernate mode keep SARMUX active, i.e. do not open
    *   all switches (disconnect), to be used for ADFT
    */
    Volt_Regulator_backup.dftRegVal = Volt_Regulator_SAR_DFT_CTRL_REG & (uint32)~Volt_Regulator_ADFT_OVERRIDE;
    Volt_Regulator_SAR_DFT_CTRL_REG |= Volt_Regulator_ADFT_OVERRIDE;
    if((Volt_Regulator_SAR_CTRL_REG  & Volt_Regulator_ENABLE) != 0u)
    {
        if((Volt_Regulator_SAR_SAMPLE_CTRL_REG & Volt_Regulator_CONTINUOUS_EN) != 0u)
        {
            Volt_Regulator_backup.enableState = Volt_Regulator_ENABLED | Volt_Regulator_STARTED;
        }
        else
        {
            Volt_Regulator_backup.enableState = Volt_Regulator_ENABLED;
        }
        Volt_Regulator_StopConvert();
        Volt_Regulator_Stop();
        
        /* Disable the SAR internal pump before entering the chip low power mode */
        if((Volt_Regulator_SAR_CTRL_REG & Volt_Regulator_BOOSTPUMP_EN) != 0u)
        {
            Volt_Regulator_SAR_CTRL_REG &= (uint32)~Volt_Regulator_BOOSTPUMP_EN;
            Volt_Regulator_backup.enableState |= Volt_Regulator_BOOSTPUMP_ENABLED;
        }
    }
    else
    {
        Volt_Regulator_backup.enableState = Volt_Regulator_DISABLED;
    }
}


/*******************************************************************************
* Function Name: Volt_Regulator_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component enable state and configuration registers.
*  This should be called just after awaking from sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Volt_Regulator_backup - used.
*
*******************************************************************************/
void Volt_Regulator_Wakeup(void)
{
    Volt_Regulator_SAR_DFT_CTRL_REG = Volt_Regulator_backup.dftRegVal;
    if(Volt_Regulator_backup.enableState != Volt_Regulator_DISABLED)
    {
        /* Enable the SAR internal pump  */
        if((Volt_Regulator_backup.enableState & Volt_Regulator_BOOSTPUMP_ENABLED) != 0u)
        {
            Volt_Regulator_SAR_CTRL_REG |= Volt_Regulator_BOOSTPUMP_EN;
        }
        Volt_Regulator_Enable();
        if((Volt_Regulator_backup.enableState & Volt_Regulator_STARTED) != 0u)
        {
            Volt_Regulator_StartConvert();
        }
    }
}
/* [] END OF FILE */
