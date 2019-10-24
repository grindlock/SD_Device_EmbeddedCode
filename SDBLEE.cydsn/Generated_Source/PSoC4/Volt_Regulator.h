/*******************************************************************************
* File Name: Volt_Regulator.h
* Version 2.50
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Sequencing Successive Approximation ADC Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_ADC_SAR_SEQ_Volt_Regulator_H)
#define CY_ADC_SAR_SEQ_Volt_Regulator_H

#include "cytypes.h"
#include "CyLib.h"


/***************************************
*      Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
    uint32 dftRegVal;
} Volt_Regulator_BACKUP_STRUCT;


/**************************************
*    Enumerated Types and Parameters
**************************************/

/*  Clock Source setting constants */
#define Volt_Regulator__EXTERNAL 0
#define Volt_Regulator__INTERNAL 1

/*  Sample Mode setting constants */
#define Volt_Regulator__FREERUNNING 0
#define Volt_Regulator__HARDWARESOC 1

/*  Reference type setting constants */
#define Volt_Regulator__VDDA_2 0
#define Volt_Regulator__VDDA 1
#define Volt_Regulator__INTERNAL1024 2
#define Volt_Regulator__INTERNAL1024BYPASSED 3
#define Volt_Regulator__INTERNALVREF 4
#define Volt_Regulator__INTERNALVREFBYPASSED 5
#define Volt_Regulator__VDDA_2BYPASSED 6
#define Volt_Regulator__EXTERNALVREF 7

/* Input buffer gain setting constants */
#define Volt_Regulator__DISABLED 0
#define Volt_Regulator__ONE 1
#define Volt_Regulator__TWO 2
#define Volt_Regulator__FOUR 3
#define Volt_Regulator__EIGHT 4
#define Volt_Regulator__SIXTEEN 5

/* Negative input setting sonstants in single ended mode */
#define Volt_Regulator__VSS 0
#define Volt_Regulator__VREF 1
#define Volt_Regulator__OTHER 2

/* Compare mode setting constants:
*    Mode0 - Disable
*    Mode1 - Result < Low_Limit
*    Mode2 - Low_Limit <= Result < High_Limit
*    Mode3 - High_Limit <= Result
*    Mode4 - (Result < Low_Limit) or (High_Limit <= Result)
*/
#define Volt_Regulator__MODE0 0
#define Volt_Regulator__MODE1 1
#define Volt_Regulator__MODE2 2
#define Volt_Regulator__MODE3 3

#define Volt_Regulator__RES8 0
#define Volt_Regulator__RES10 1

#define Volt_Regulator__RIGHT 0
#define Volt_Regulator__LEFT 1

#define Volt_Regulator__FSIGNED 1
#define Volt_Regulator__FUNSIGNED 0

#define Volt_Regulator__ACCUMULATE 0
#define Volt_Regulator__FIXEDRESOLUTION 1



/***************************************
*   Conditional Compilation Parameters
****************************************/ 

#define Volt_Regulator_CY_SAR_IP_VER0               	(0u)
#define Volt_Regulator_CY_SAR_IP_VER1               	(1u)

#if (CY_PSOC4_4100 || CY_PSOC4_4200)
    #define Volt_Regulator_CY_SAR_IP_VER              (Volt_Regulator_CY_SAR_IP_VER0)
#else /* Other devices */
    #define Volt_Regulator_CY_SAR_IP_VER              (Volt_Regulator_CY_SAR_IP_VER1)
#endif  /* (CY_PSOC4_4100 || CY_PSOC4_4200) */


/***************************************
*    Initial Parameter Constants
***************************************/
#define Volt_Regulator_DEFAULT_SAMPLE_MODE_SEL        (0u)
#define Volt_Regulator_DEFAULT_VREF_SEL               (1u)
#define Volt_Regulator_DEFAULT_NEG_INPUT_SEL          (0u)
#define Volt_Regulator_DEFAULT_ALT_RESOLUTION_SEL     (0u)
#define Volt_Regulator_DEFAULT_JUSTIFICATION_SEL      (0u)
#define Volt_Regulator_DEFAULT_DIFF_RESULT_FORMAT_SEL (0u)
#define Volt_Regulator_DEFAULT_SE_RESULT_FORMAT_SEL   (1u)
#define Volt_Regulator_DEFAULT_CLOCK_SOURCE           (1u)
#define Volt_Regulator_DEFAULT_VREF_MV_VALUE          (3300)
#define Volt_Regulator_DEFAULT_BUFFER_GAIN            (0u)
#define Volt_Regulator_DEFAULT_AVG_SAMPLES_NUM        (0u)
#define Volt_Regulator_DEFAULT_AVG_SAMPLES_DIV        (0u < 4u) ? (int16)(0x100u >> (7u - 0u)) : (int16)(0x100u >> 4u)
#define Volt_Regulator_DEFAULT_AVG_MODE               (1u)
#define Volt_Regulator_MAX_RESOLUTION                 (12u)
#define Volt_Regulator_DEFAULT_LOW_LIMIT              (7u)
#define Volt_Regulator_DEFAULT_HIGH_LIMIT             (2047u)
#define Volt_Regulator_DEFAULT_COMPARE_MODE           (0u)
#define Volt_Regulator_DEFAULT_ACLKS_NUM              (2u)
#define Volt_Regulator_DEFAULT_BCLKS_NUM              (2u)
#define Volt_Regulator_DEFAULT_CCLKS_NUM              (2u)
#define Volt_Regulator_DEFAULT_DCLKS_NUM              (2u)
#define Volt_Regulator_TOTAL_CHANNELS_NUM             (1u)
#define Volt_Regulator_SEQUENCED_CHANNELS_NUM         (1u)
#define Volt_Regulator_DEFAULT_EN_CHANNELS            (1u)
#define Volt_Regulator_NOMINAL_CLOCK_FREQ             (1000000)
#define Volt_Regulator_INJ_CHANNEL_ENABLED            (0u)
#define Volt_Regulator_IRQ_REMOVE                     (0u)

/* Determines whether the configuration contains external negative input. */
#define Volt_Regulator_SINGLE_PRESENT                 (0u)
#define Volt_Regulator_CHANNELS_MODE                  (0u)
#define Volt_Regulator_MAX_CHANNELS_EN_MASK           (0xffffu >> (16u - Volt_Regulator_SEQUENCED_CHANNELS_NUM))


/***************************************
*        Function Prototypes
***************************************/

void Volt_Regulator_Start(void);
void Volt_Regulator_Stop(void);
void Volt_Regulator_Init(void);
void Volt_Regulator_Enable(void);
void Volt_Regulator_StartConvert(void);
void Volt_Regulator_StopConvert(void);
uint32 Volt_Regulator_IsEndConversion(uint32 retMode);
int16 Volt_Regulator_GetResult16(uint32 chan);
void Volt_Regulator_SetChanMask(uint32 mask);
void Volt_Regulator_SetLowLimit(uint32 lowLimit);
void Volt_Regulator_SetHighLimit(uint32 highLimit);
void Volt_Regulator_SetLimitMask(uint32 mask);
void Volt_Regulator_SetSatMask(uint32 mask);
void Volt_Regulator_SetOffset(uint32 chan, int16 offset);
void Volt_Regulator_SetGain(uint32 chan, int32 adcGain);
#if(Volt_Regulator_INJ_CHANNEL_ENABLED)
    void Volt_Regulator_EnableInjection(void);
#endif /* Volt_Regulator_INJ_CHANNEL_ENABLED */
#if(Volt_Regulator_DEFAULT_JUSTIFICATION_SEL == Volt_Regulator__RIGHT)
    int16 Volt_Regulator_CountsTo_mVolts(uint32 chan, int16 adcCounts);
    int32 Volt_Regulator_CountsTo_uVolts(uint32 chan, int16 adcCounts);
    float32 Volt_Regulator_CountsTo_Volts(uint32 chan, int16 adcCounts);
#endif /* End Volt_Regulator_DEFAULT_JUSTIFICATION_SEL == Volt_Regulator__RIGHT */
void Volt_Regulator_Sleep(void);
void Volt_Regulator_Wakeup(void);
void Volt_Regulator_SaveConfig(void);
void Volt_Regulator_RestoreConfig(void);

CY_ISR_PROTO( Volt_Regulator_ISR );


/**************************************
*           API Constants
**************************************/
/* Constants for Sleep mode states */
#define Volt_Regulator_DISABLED                   (0x00u)
#define Volt_Regulator_ENABLED                    (0x01u)
#define Volt_Regulator_STARTED                    (0x02u)
#define Volt_Regulator_BOOSTPUMP_ENABLED          (0x04u)

/*   Constants for IsEndConversion() "retMode" parameter  */
#define Volt_Regulator_RETURN_STATUS              (0x01u)
#define Volt_Regulator_WAIT_FOR_RESULT            (0x02u)
#define Volt_Regulator_RETURN_STATUS_INJ          (0x04u)
#define Volt_Regulator_WAIT_FOR_RESULT_INJ        (0x08u)

#define Volt_Regulator_MAX_FREQUENCY              (18000000)       /*18Mhz*/

#define Volt_Regulator_RESOLUTION_12              (12u)
#define Volt_Regulator_RESOLUTION_10              (10u)
#define Volt_Regulator_RESOLUTION_8               (8u)

#define Volt_Regulator_10US_DELAY                 (10u)

#define Volt_Regulator_10V_COUNTS                 (10.0F)
#define Volt_Regulator_10MV_COUNTS                (10000)
#define Volt_Regulator_10UV_COUNTS                (10000000L)


/***************************************
* Global variables external identifier
***************************************/

extern uint8 Volt_Regulator_initVar;
extern volatile int16 Volt_Regulator_offset[Volt_Regulator_TOTAL_CHANNELS_NUM];
extern volatile int32 Volt_Regulator_countsPer10Volt[Volt_Regulator_TOTAL_CHANNELS_NUM];


/***************************************
*              Registers
***************************************/

#define Volt_Regulator_SAR_CTRL_REG                (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CTRL )
#define Volt_Regulator_SAR_CTRL_PTR                ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CTRL )

#define Volt_Regulator_SAR_SAMPLE_CTRL_REG         (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_SAMPLE_CTRL )
#define Volt_Regulator_SAR_SAMPLE_CTRL_PTR         ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_SAMPLE_CTRL )

#define Volt_Regulator_SAR_SAMPLE_TIME01_REG       (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_SAMPLE_TIME01 )
#define Volt_Regulator_SAR_SAMPLE_TIME01_PTR       ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_SAMPLE_TIME01 )

#define Volt_Regulator_SAR_SAMPLE_TIME23_REG       (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_SAMPLE_TIME23 )
#define Volt_Regulator_SAR_SAMPLE_TIME23_PTR       ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_SAMPLE_TIME23 )

#define Volt_Regulator_SAR_RANGE_THRES_REG         (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_RANGE_THRES )
#define Volt_Regulator_SAR_RANGE_THRES_PTR         ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_RANGE_THRES )

#define Volt_Regulator_SAR_RANGE_COND_REG          (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_RANGE_COND )
#define Volt_Regulator_SAR_RANGE_COND_PTR          ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_RANGE_COND )

#define Volt_Regulator_SAR_CHAN_EN_REG             (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_EN )
#define Volt_Regulator_SAR_CHAN_EN_PTR             ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_EN )

#define Volt_Regulator_SAR_START_CTRL_REG          (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_START_CTRL )
#define Volt_Regulator_SAR_START_CTRL_PTR          ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_START_CTRL )

#define Volt_Regulator_SAR_DFT_CTRL_REG            (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_DFT_CTRL )
#define Volt_Regulator_SAR_DFT_CTRL_PTR            ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_DFT_CTRL )

#define Volt_Regulator_SAR_CHAN_CONFIG_REG         (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_CONFIG00 )
#define Volt_Regulator_SAR_CHAN_CONFIG_PTR         ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_CONFIG00 )
#define Volt_Regulator_SAR_CHAN_CONFIG_IND         Volt_Regulator_cy_psoc4_sar__SAR_CHAN_CONFIG00

#define Volt_Regulator_SAR_CHAN_WORK_REG           (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_WORK00 )
#define Volt_Regulator_SAR_CHAN_WORK_PTR           ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_WORK00 )

#define Volt_Regulator_SAR_CHAN_RESULT_REG         (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT00 )
#define Volt_Regulator_SAR_CHAN_RESULT_PTR         ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT00 )
#define Volt_Regulator_SAR_CHAN_RESULT_IND         Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT00

#define Volt_Regulator_SAR_CHAN0_RESULT_REG         (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT00 )
#define Volt_Regulator_SAR_CHAN0_RESULT_PTR         ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT00 )

#define Volt_Regulator_SAR_CHAN1_RESULT_REG         (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT01 )
#define Volt_Regulator_SAR_CHAN1_RESULT_PTR         ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT01 )

#define Volt_Regulator_SAR_CHAN2_RESULT_REG         (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT02 )
#define Volt_Regulator_SAR_CHAN2_RESULT_PTR         ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT02 )

#define Volt_Regulator_SAR_CHAN3_RESULT_REG         (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT03 )
#define Volt_Regulator_SAR_CHAN3_RESULT_PTR         ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT03 )

#define Volt_Regulator_SAR_CHAN4_RESULT_REG         (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT04 )
#define Volt_Regulator_SAR_CHAN4_RESULT_PTR         ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT04 )

#define Volt_Regulator_SAR_CHAN5_RESULT_REG         (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT05 )
#define Volt_Regulator_SAR_CHAN5_RESULT_PTR         ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT05 )

#define Volt_Regulator_SAR_CHAN6_RESULT_REG         (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT06 )
#define Volt_Regulator_SAR_CHAN6_RESULT_PTR         ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT06 )

#define Volt_Regulator_SAR_CHAN7_RESULT_REG         (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT07 )
#define Volt_Regulator_SAR_CHAN7_RESULT_PTR         ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT07 )

#if(Volt_Regulator_CY_SAR_IP_VER != Volt_Regulator_CY_SAR_IP_VER0)
    #define Volt_Regulator_SAR_CHAN8_RESULT_REG     (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT08 )
    #define Volt_Regulator_SAR_CHAN8_RESULT_PTR     ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT08 )

    #define Volt_Regulator_SAR_CHAN9_RESULT_REG     (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT09 )
    #define Volt_Regulator_SAR_CHAN9_RESULT_PTR     ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT09 )

    #define Volt_Regulator_SAR_CHAN10_RESULT_REG    (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT10 )
    #define Volt_Regulator_SAR_CHAN10_RESULT_PTR    ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT10 )

    #define Volt_Regulator_SAR_CHAN11_RESULT_REG    (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT11 )
    #define Volt_Regulator_SAR_CHAN11_RESULT_PTR    ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT11 )

    #define Volt_Regulator_SAR_CHAN12_RESULT_REG    (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT12 )
    #define Volt_Regulator_SAR_CHAN12_RESULT_PTR    ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT12 )

    #define Volt_Regulator_SAR_CHAN13_RESULT_REG    (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT13 )
    #define Volt_Regulator_SAR_CHAN13_RESULT_PTR    ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT13 )

    #define Volt_Regulator_SAR_CHAN14_RESULT_REG    (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT14 )
    #define Volt_Regulator_SAR_CHAN14_RESULT_PTR    ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT14 )

    #define Volt_Regulator_SAR_CHAN15_RESULT_REG    (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT15 )
    #define Volt_Regulator_SAR_CHAN15_RESULT_PTR    ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT15 )
#endif /* (Volt_Regulator_CY_SAR_IP_VER != Volt_Regulator_CY_SAR_IP_VER0) */

#define Volt_Regulator_SAR_CHAN_WORK_VALID_REG     (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_WORK_VALID)
#define Volt_Regulator_SAR_CHAN_WORK_VALID_PTR     ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_WORK_VALID)

#define Volt_Regulator_SAR_CHAN_RESULT_VALID_REG  ( *(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT_VALID )
#define Volt_Regulator_SAR_CHAN_RESULT_VALID_PTR  ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_CHAN_RESULT_VALID )

#define Volt_Regulator_SAR_STATUS_REG              (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_STATUS )
#define Volt_Regulator_SAR_STATUS_PTR              ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_STATUS )

#define Volt_Regulator_SAR_AVG_START_REG           (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_AVG_STAT )
#define Volt_Regulator_SAR_AVG_START_PTR           ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_AVG_STAT )

#define Volt_Regulator_SAR_INTR_REG                (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_INTR )
#define Volt_Regulator_SAR_INTR_PTR                ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_INTR )

#define Volt_Regulator_SAR_INTR_SET_REG            (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_INTR_SET )
#define Volt_Regulator_SAR_INTR_SET_PTR            ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_INTR_SET )

#define Volt_Regulator_SAR_INTR_MASK_REG           (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_INTR_MASK )
#define Volt_Regulator_SAR_INTR_MASK_PTR           ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_INTR_MASK )

#define Volt_Regulator_SAR_INTR_MASKED_REG         (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_INTR_MASKED )
#define Volt_Regulator_SAR_INTR_MASKED_PTR         ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_INTR_MASKED )

#define Volt_Regulator_SAR_SATURATE_INTR_REG       (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_SATURATE_INTR )
#define Volt_Regulator_SAR_SATURATE_INTR_PTR       ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_SATURATE_INTR )

#define Volt_Regulator_SAR_SATURATE_INTR_SET_REG   (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_SATURATE_INTR_SET )
#define Volt_Regulator_SAR_SATURATE_INTR_SET_PTR   ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_SATURATE_INTR_SET )

#define Volt_Regulator_SAR_SATURATE_INTR_MASK_REG (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_SATURATE_INTR_MASK )
#define Volt_Regulator_SAR_SATURATE_INTR_MASK_PTR ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_SATURATE_INTR_MASK )

#define Volt_Regulator_SAR_SATURATE_INTR_MASKED_REG \
                                                 (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_SATURATE_INTR_MASKED )
#define Volt_Regulator_SAR_SATURATE_INTR_MASKED_PTR \
                                                 ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_SATURATE_INTR_MASKED )

#define Volt_Regulator_SAR_RANGE_INTR_REG          (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_RANGE_INTR )
#define Volt_Regulator_SAR_RANGE_INTR_PTR          ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_RANGE_INTR )

#define Volt_Regulator_SAR_RANGE_INTR_SET_REG      (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_RANGE_INTR_SET )
#define Volt_Regulator_SAR_RANGE_INTR_SET_PTR      ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_RANGE_INTR_SET )

#define Volt_Regulator_SAR_RANGE_INTR_MASK_REG     (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_RANGE_INTR_MASK )
#define Volt_Regulator_SAR_RANGE_INTR_MASK_PTR     ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_RANGE_INTR_MASK )

#define Volt_Regulator_SAR_RANGE_INTR_MASKED_REG   (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_RANGE_INTR_MASKED )
#define Volt_Regulator_SAR_RANGE_INTR_MASKED_PTR   ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_RANGE_INTR_MASKED )

#define Volt_Regulator_SAR_INTR_CAUSE_REG          (*(reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_INTR_CAUSE )
#define Volt_Regulator_SAR_INTR_CAUSE_PTR          ( (reg32 *) Volt_Regulator_cy_psoc4_sar__SAR_INTR_CAUSE )

#if(Volt_Regulator_INJ_CHANNEL_ENABLED)
    #define Volt_Regulator_SAR_INJ_CHAN_CONFIG_REG \
                                                 (*(reg32 *) Volt_Regulator_cy_psoc4_sarmux_8__SAR_INJ_CHAN_CONFIG )
    #define Volt_Regulator_SAR_INJ_CHAN_CONFIG_PTR    \
                                                 ( (reg32 *) Volt_Regulator_cy_psoc4_sarmux_8__SAR_INJ_CHAN_CONFIG )

    #define Volt_Regulator_SAR_INJ_RESULT_REG    (*(reg32 *) Volt_Regulator_cy_psoc4_sarmux_8__SAR_INJ_RESULT )
    #define Volt_Regulator_SAR_INJ_RESULT_PTR    ( (reg32 *) Volt_Regulator_cy_psoc4_sarmux_8__SAR_INJ_RESULT )
#endif /* Volt_Regulator_INJ_CHANNEL_ENABLED */
    
#define Volt_Regulator_MUX_SWITCH0_REG           (*(reg32 *)  Volt_Regulator_cy_psoc4_sar__SAR_MUX_SWITCH0 )
#define Volt_Regulator_MUX_SWITCH0_PTR           ( (reg32 *)  Volt_Regulator_cy_psoc4_sar__SAR_MUX_SWITCH0 )

#define Volt_Regulator_MUX_SWITCH_HW_CTRL_REG    (*(reg32 *)  Volt_Regulator_cy_psoc4_sar__SAR_MUX_SWITCH_HW_CTRL )
#define Volt_Regulator_MUX_SWITCH_HW_CTRL_PTR    ( (reg32 *)  Volt_Regulator_cy_psoc4_sar__SAR_MUX_SWITCH_HW_CTRL )

#define Volt_Regulator_PUMP_CTRL_REG             (*(reg32 *)  Volt_Regulator_cy_psoc4_sar__SAR_PUMP_CTRL )
#define Volt_Regulator_PUMP_CTRL_PTR             ( (reg32 *)  Volt_Regulator_cy_psoc4_sar__SAR_PUMP_CTRL )

#define Volt_Regulator_ANA_TRIM_REG              (*(reg32 *)  Volt_Regulator_cy_psoc4_sar__SAR_ANA_TRIM )
#define Volt_Regulator_ANA_TRIM_PTR              ( (reg32 *)  Volt_Regulator_cy_psoc4_sar__SAR_ANA_TRIM )

#define Volt_Regulator_WOUNDING_REG              (*(reg32 *)  Volt_Regulator_cy_psoc4_sar__SAR_WOUNDING )
#define Volt_Regulator_WOUNDING_PTR              ( (reg32 *)  Volt_Regulator_cy_psoc4_sar__SAR_WOUNDING )


/**************************************
*       Register Constants
**************************************/
#define Volt_Regulator_INTC_NUMBER                (Volt_Regulator_IRQ__INTC_NUMBER)
#define Volt_Regulator_INTC_PRIOR_NUMBER          (Volt_Regulator_IRQ__INTC_PRIOR_NUM)

/* defines for CTRL register */
#define Volt_Regulator_VREF_INTERNAL1024          (0x00000040Lu)
#define Volt_Regulator_VREF_EXTERNAL              (0x00000050Lu)
#define Volt_Regulator_VREF_VDDA_2                (0x00000060Lu)
#define Volt_Regulator_VREF_VDDA                  (0x00000070Lu)
#define Volt_Regulator_VREF_INTERNAL1024BYPASSED  (0x000000C0Lu)
#define Volt_Regulator_VREF_VDDA_2BYPASSED        (0x000000E0Lu)
#define Volt_Regulator_VREF_INTERNALVREF          (0x00000040Lu)
#define Volt_Regulator_VREF_INTERNALVREFBYPASSED  (0x000000C0Lu)

#define Volt_Regulator_NEG_VSSA_KELVIN            (0x00000000Lu)
#define Volt_Regulator_NEG_VSSA                   (0x00000200Lu)
#define Volt_Regulator_NEG_VREF                   (0x00000E00Lu)
#if(Volt_Regulator_TOTAL_CHANNELS_NUM > 1u)
    #define Volt_Regulator_NEG_OTHER              (uint16)((uint16)Volt_Regulator_cy_psoc4_sarmux_8__VNEG0 << 9u)
#else
    #define Volt_Regulator_NEG_OTHER              (0)
#endif /* Volt_Regulator_TOTAL_CHANNELS_NUM > 1u */

#define Volt_Regulator_SAR_HW_CTRL_NEGVREF        (0x00002000Lu)

#define Volt_Regulator_BOOSTPUMP_EN               (0x00100000Lu)

#define Volt_Regulator_NORMAL_PWR                 (0x00000000Lu)
#define Volt_Regulator_HALF_PWR                   (0x01000000Lu)
#define Volt_Regulator_MORE_PWR                   (0x02000000Lu)
#define Volt_Regulator_QUARTER_PWR                (0x03000000Lu)
#define Volt_Regulator_DEEPSLEEP_ON               (0x08000000Lu)

#define Volt_Regulator_DSI_SYNC_CONFIG            (0x10000000Lu)
#define Volt_Regulator_DSI_MODE                   (0x20000000Lu)
#define Volt_Regulator_SWITCH_DISABLE             (0x40000000Lu)
#define Volt_Regulator_ENABLE                     (0x80000000Lu)

/* defines for STATUS register */
#define Volt_Regulator_STATUS_BUSY                (0x80000000Lu)

/* defines for SAMPLE_CTRL register */
#define Volt_Regulator_ALT_RESOLUTION_10BIT       (0x00000001Lu)
#define Volt_Regulator_ALT_RESOLUTION_8BIT        (0x00000000Lu)

#define Volt_Regulator_DATA_ALIGN_LEFT            (0x00000002Lu)
#define Volt_Regulator_DATA_ALIGN_RIGHT           (0x00000000Lu)

#define Volt_Regulator_SE_SIGNED_RESULT           (0x00000004Lu)
#define Volt_Regulator_SE_UNSIGNED_RESULT         (0x00000000Lu)

#define Volt_Regulator_DIFF_SIGNED_RESULT         (0x00000008Lu)
#define Volt_Regulator_DIFF_UNSIGNED_RESULT       (0x00000000Lu)

#define Volt_Regulator_AVG_CNT_OFFSET             (4u)
#define Volt_Regulator_AVG_CNT_MASK               (0x00000070Lu)
#define Volt_Regulator_AVG_SHIFT                  (0x00000080Lu)

#define Volt_Regulator_CONTINUOUS_EN              (0x00010000Lu)
#define Volt_Regulator_DSI_TRIGGER_EN             (0x00020000Lu)
#define Volt_Regulator_DSI_TRIGGER_LEVEL          (0x00040000Lu)
#define Volt_Regulator_DSI_SYNC_TRIGGER           (0x00080000Lu)
#define Volt_Regulator_EOS_DSI_OUT_EN             (0x80000000Lu)

/* defines for SAMPLE_TIME01 / SAMPLE_TIME23 registers */
#define Volt_Regulator_SAMPLE_TIME13_OFFSET       (16u)
#define Volt_Regulator_SAMPLE_TIME02_MASK         (0x000003FFLu)
#define Volt_Regulator_SAMPLE_TIME13_MASK         (0x03FF0000Lu)

/* defines for RANGE_THRES registers */
#define Volt_Regulator_RANGE_HIGH_OFFSET          (16u)
#define Volt_Regulator_RANGE_HIGH_MASK            (0xFFFF0000Lu)
#define Volt_Regulator_RANGE_LOW_MASK             (0x0000FFFFLu)

/* defines for RANGE_COND register */
/* Compare mode setting constants:
*    BELOW   - Result < Low_Limit
*    INSIDE  - Low_Limit <= Result < High_Limit
*    ABOVE   - High_Limit <= Result
*    OUTSIDE - (Result < Low_Limit) or (High_Limit <= Result)
*/
#define Volt_Regulator_CMP_MODE_BELOW             (0x00000000Lu)
#define Volt_Regulator_CMP_MODE_INSIDE            (0x40000000Lu)
#define Volt_Regulator_CMP_MODE_ABOVE             (0x80000000Lu)
#define Volt_Regulator_CMP_MODE_OUTSIDE           (0xC0000000Lu)
#define Volt_Regulator_CMP_OFFSET                 (30u)

/* defines for _START_CTRL register */
#define Volt_Regulator_FW_TRIGGER                 (0x00000001Lu)

/* defines for DFT_CTRL register */
#define Volt_Regulator_DLY_INC                    (0x00000001Lu)
#define Volt_Regulator_HIZ                        (0x00000002Lu)
#define Volt_Regulator_DFT_INC_MASK               (0x000F0000Lu)
#define Volt_Regulator_DFT_OUTC_MASK              (0x00700000Lu)
#define Volt_Regulator_SEL_CSEL_DFT_MASK          (0x0F000000Lu)

/* configuration for clock speed > 9 Mhz based on
* characterization results
*/
#define Volt_Regulator_SEL_CSEL_DFT_CHAR          (0x03000000Lu)
#define Volt_Regulator_EN_CSEL_DFT                (0x10000000Lu)
#define Volt_Regulator_DCEN                       (0x20000000Lu)
#define Volt_Regulator_ADFT_OVERRIDE              (0x80000000Lu)

/* defines for CHAN_CONFIG / DIE_CHAN_CONFIG register
*  and channelsConfig parameter
*/
#define Volt_Regulator_SARMUX_VIRT_SELECT         (0x00000070Lu)
#define Volt_Regulator_DIFFERENTIAL_EN            (0x00000100Lu)
#define Volt_Regulator_ALT_RESOLUTION_ON          (0x00000200Lu)
#define Volt_Regulator_AVERAGING_EN               (0x00000400Lu)

#define Volt_Regulator_SAMPLE_TIME_SEL_SHIFT      (12u)
#define Volt_Regulator_SAMPLE_TIME_SEL_MASK       (0x00003000Lu)

#define Volt_Regulator_CHANNEL_CONFIG_MASK        (0x00003700Lu)

/* for CHAN_CONFIG only */
#define Volt_Regulator_DSI_OUT_EN                 (0x80000000Lu)

/* for INJ_CHAN_CONFIG only */
#define Volt_Regulator_INJ_TAILGATING             (0x40000000Lu)
#define Volt_Regulator_INJ_CHAN_EN                (0x80000000Lu)

/* defines for CHAN_WORK register */
#define Volt_Regulator_SAR_WRK_MAX_12BIT          (0x00001000Lu)
#define Volt_Regulator_SAR_WRK_MAX_10BIT          (0x00000400Lu)
#define Volt_Regulator_SAR_WRK_MAX_8BIT           (0x00000100Lu)

/* defines for CHAN_RESULT register */
#define Volt_Regulator_RESULT_MASK                (0x0000FFFFLu)
#define Volt_Regulator_SATURATE_INTR_MIR          (0x20000000Lu)
#define Volt_Regulator_RANGE_INTR_MIR             (0x40000000Lu)
#define Volt_Regulator_CHAN_RESULT_VALID_MIR      (0x80000000Lu)

/* defines for INTR_MASK register */
#define Volt_Regulator_EOS_MASK                   (0x00000001Lu)
#define Volt_Regulator_OVERFLOW_MASK              (0x00000002Lu)
#define Volt_Regulator_FW_COLLISION_MASK          (0x00000004Lu)
#define Volt_Regulator_DSI_COLLISION_MASK         (0x00000008Lu)
#define Volt_Regulator_INJ_EOC_MASK               (0x00000010Lu)
#define Volt_Regulator_INJ_SATURATE_MASK          (0x00000020Lu)
#define Volt_Regulator_INJ_RANGE_MASK             (0x00000040Lu)
#define Volt_Regulator_INJ_COLLISION_MASK         (0x00000080Lu)

/* defines for INJ_RESULT register */
#define Volt_Regulator_INJ_COLLISION_INTR_MIR     (0x10000000Lu)
#define Volt_Regulator_INJ_SATURATE_INTR_MIR      (0x20000000Lu)
#define Volt_Regulator_INJ_RANGE_INTR_MIR         (0x40000000Lu)
#define Volt_Regulator_INJ_EOC_INTR_MIR           (0x80000000Lu)

/* defines for MUX_SWITCH0 register */
#define Volt_Regulator_MUX_FW_VSSA_VMINUS         (0x00010000Lu)

/* defines for PUMP_CTRL register */
#define Volt_Regulator_PUMP_CTRL_ENABLED          (0x80000000Lu)

/* additional defines for channelsConfig parameter */
#define Volt_Regulator_IS_SATURATE_EN_MASK        (0x00000001Lu)
#define Volt_Regulator_IS_RANGE_CTRL_EN_MASK      (0x00000002Lu)

/* defines for WOUNDING register */
#define Volt_Regulator_WOUNDING_12BIT             (0x00000000Lu)
#define Volt_Regulator_WOUNDING_10BIT             (0x00000001Lu)
#define Volt_Regulator_WOUNDING_8BIT              (0x00000002Lu)

/* Trim value based on characterization */
#define Volt_Regulator_TRIM_COEF                  (2u)

#if(Volt_Regulator_MAX_RESOLUTION == Volt_Regulator_RESOLUTION_10)
    #define Volt_Regulator_ALT_WOUNDING           Volt_Regulator_WOUNDING_10BIT
#else
    #define Volt_Regulator_ALT_WOUNDING           Volt_Regulator_WOUNDING_8BIT
#endif /* Volt_Regulator_MAX_RESOLUTION == Volt_Regulator_RESOLUTION_10 */

#if(Volt_Regulator_DEFAULT_VREF_SEL == Volt_Regulator__VDDA_2)
    #define Volt_Regulator_DEFAULT_VREF_SOURCE    Volt_Regulator_VREF_VDDA_2
#elif(Volt_Regulator_DEFAULT_VREF_SEL == Volt_Regulator__VDDA)
    #define Volt_Regulator_DEFAULT_VREF_SOURCE    Volt_Regulator_VREF_VDDA
#elif(Volt_Regulator_DEFAULT_VREF_SEL == Volt_Regulator__INTERNAL1024)
    #define Volt_Regulator_DEFAULT_VREF_SOURCE    Volt_Regulator_VREF_INTERNAL1024
#elif(Volt_Regulator_DEFAULT_VREF_SEL == Volt_Regulator__INTERNAL1024BYPASSED)
    #define Volt_Regulator_DEFAULT_VREF_SOURCE    Volt_Regulator_VREF_INTERNAL1024BYPASSED
#elif(Volt_Regulator_DEFAULT_VREF_SEL == Volt_Regulator__INTERNALVREF)
    #define Volt_Regulator_DEFAULT_VREF_SOURCE    Volt_Regulator_VREF_INTERNALVREF
#elif(Volt_Regulator_DEFAULT_VREF_SEL == Volt_Regulator__INTERNALVREFBYPASSED)
    #define Volt_Regulator_DEFAULT_VREF_SOURCE    Volt_Regulator_VREF_INTERNALVREFBYPASSED
#elif(Volt_Regulator_DEFAULT_VREF_SEL == Volt_Regulator__VDDA_2BYPASSED)
    #define Volt_Regulator_DEFAULT_VREF_SOURCE    Volt_Regulator_VREF_VDDA_2BYPASSED
#else
    #define Volt_Regulator_DEFAULT_VREF_SOURCE    Volt_Regulator_VREF_EXTERNAL
#endif /* Volt_Regulator_DEFAULT_VREF_SEL == Volt_Regulator__VDDA_2 */

#if(Volt_Regulator_DEFAULT_NEG_INPUT_SEL == Volt_Regulator__VSS)
    /* Connect NEG input of SARADC to VSSA close to the SARADC for single channel mode */
    #if(Volt_Regulator_TOTAL_CHANNELS_NUM == 1u)
        #define Volt_Regulator_DEFAULT_SE_NEG_INPUT    Volt_Regulator_NEG_VSSA
    #else
        #define Volt_Regulator_DEFAULT_SE_NEG_INPUT    Volt_Regulator_NEG_VSSA_KELVIN
    #endif /* (Volt_Regulator_TOTAL_CHANNELS_NUM == 1u) */
    /* Do not connect VSSA to VMINUS when one channel in differential mode used */
    #if((Volt_Regulator_TOTAL_CHANNELS_NUM == 1u) && (Volt_Regulator_CHANNELS_MODE != 0u))
        #define Volt_Regulator_DEFAULT_MUX_SWITCH0     0u
    #else    /* miltiple channels or one single channel */
        #define Volt_Regulator_DEFAULT_MUX_SWITCH0     Volt_Regulator_MUX_FW_VSSA_VMINUS
    #endif /* (Volt_Regulator_TOTAL_CHANNELS_NUM == 1u) */
#elif(Volt_Regulator_DEFAULT_NEG_INPUT_SEL == Volt_Regulator__VREF)
    /* Do not connect VNEG to VREF when one channel in differential mode used */
    #if((Volt_Regulator_TOTAL_CHANNELS_NUM == 1u) && (Volt_Regulator_CHANNELS_MODE != 0u))
        #define Volt_Regulator_DEFAULT_SE_NEG_INPUT    0u
    #else    /* miltiple channels or one single channel */
        #define Volt_Regulator_DEFAULT_SE_NEG_INPUT    Volt_Regulator_NEG_VREF
    #endif /* (Volt_Regulator_TOTAL_CHANNELS_NUM == 1u) */
    #define Volt_Regulator_DEFAULT_MUX_SWITCH0     0u
#elif (Volt_Regulator_SINGLE_PRESENT != 0u)
    #define Volt_Regulator_DEFAULT_SE_NEG_INPUT    Volt_Regulator_NEG_OTHER
    #define Volt_Regulator_DEFAULT_MUX_SWITCH0     0u
#else
    #define Volt_Regulator_DEFAULT_SE_NEG_INPUT    0u
    #define Volt_Regulator_DEFAULT_MUX_SWITCH0     0u
#endif /* Volt_Regulator_DEFAULT_NEG_INPUT_SEL == Volt_Regulator__VREF */

/* If the SAR is configured for multiple channels, always set SAR_HW_CTRL_NEGVREF to 1 */
#if(Volt_Regulator_TOTAL_CHANNELS_NUM == 1u)
    #define Volt_Regulator_DEFAULT_HW_CTRL_NEGVREF 0u
#else
    #define Volt_Regulator_DEFAULT_HW_CTRL_NEGVREF Volt_Regulator_SAR_HW_CTRL_NEGVREF
#endif /* (Volt_Regulator_TOTAL_CHANNELS_NUM == 1u) */


#if(Volt_Regulator_DEFAULT_ALT_RESOLUTION_SEL == Volt_Regulator__RES8)
    #define Volt_Regulator_DEFAULT_ALT_RESOLUTION     (Volt_Regulator_ALT_RESOLUTION_8BIT)
    #define Volt_Regulator_DEFAULT_MAX_WRK_ALT        (Volt_Regulator_SAR_WRK_MAX_8BIT)
#else
    #define Volt_Regulator_DEFAULT_ALT_RESOLUTION     (Volt_Regulator_ALT_RESOLUTION_10BIT)
    #define Volt_Regulator_DEFAULT_MAX_WRK_ALT        (Volt_Regulator_SAR_WRK_MAX_10BIT)
#endif /* End Volt_Regulator_DEFAULT_ALT_RESOLUTION_SEL == Volt_Regulator__RES8 */

#if(Volt_Regulator_DEFAULT_JUSTIFICATION_SEL == Volt_Regulator__RIGHT)
    #define Volt_Regulator_DEFAULT_JUSTIFICATION  Volt_Regulator_DATA_ALIGN_RIGHT
#else
    #define Volt_Regulator_DEFAULT_JUSTIFICATION  Volt_Regulator_DATA_ALIGN_LEFT
#endif /* Volt_Regulator_DEFAULT_JUSTIFICATION_SEL == Volt_Regulator__RIGHT */

#if(Volt_Regulator_DEFAULT_DIFF_RESULT_FORMAT_SEL == Volt_Regulator__FSIGNED)
    #define Volt_Regulator_DEFAULT_DIFF_RESULT_FORMAT Volt_Regulator_DIFF_SIGNED_RESULT
#else
    #define Volt_Regulator_DEFAULT_DIFF_RESULT_FORMAT Volt_Regulator_DIFF_UNSIGNED_RESULT
#endif /* Volt_Regulator_DEFAULT_DIFF_RESULT_FORMAT_SEL == Volt_Regulator__FSIGNED */

#if(Volt_Regulator_DEFAULT_SE_RESULT_FORMAT_SEL == Volt_Regulator__FSIGNED)
    #define Volt_Regulator_DEFAULT_SE_RESULT_FORMAT Volt_Regulator_SE_SIGNED_RESULT
#else
    #define Volt_Regulator_DEFAULT_SE_RESULT_FORMAT Volt_Regulator_SE_UNSIGNED_RESULT
#endif /* Volt_Regulator_DEFAULT_SE_RESULT_FORMAT_SEL == Volt_Regulator__FSIGNED */

#if(Volt_Regulator_DEFAULT_SAMPLE_MODE_SEL == Volt_Regulator__FREERUNNING)
    #define Volt_Regulator_DSI_TRIGGER        0u
#else /* Firmware trigger */
    #define Volt_Regulator_DSI_TRIGGER        (Volt_Regulator_DSI_TRIGGER_EN | Volt_Regulator_DSI_SYNC_TRIGGER)
#endif /* End Volt_Regulator_DEFAULT_SAMPLE_MODE == Volt_Regulator__FREERUNNING */

#if(Volt_Regulator_INJ_CHANNEL_ENABLED)
    #define Volt_Regulator_SAR_INTR_MASK      (Volt_Regulator_EOS_MASK | Volt_Regulator_INJ_EOC_MASK)
#else
    #define Volt_Regulator_SAR_INTR_MASK      (Volt_Regulator_EOS_MASK)
#endif /* Volt_Regulator_INJ_CHANNEL_ENABLED*/

#if(Volt_Regulator_DEFAULT_AVG_MODE == Volt_Regulator__FIXEDRESOLUTION)
    #define Volt_Regulator_AVG_SHIFT_MODE     Volt_Regulator_AVG_SHIFT
#else
    #define Volt_Regulator_AVG_SHIFT_MODE     0u
#endif /* End Volt_Regulator_DEFAULT_AVG_MODE */

#define Volt_Regulator_COMPARE_MODE           (uint32)((uint32)(Volt_Regulator_DEFAULT_COMPARE_MODE) \
                                                << Volt_Regulator_CMP_OFFSET)

#if(Volt_Regulator_TOTAL_CHANNELS_NUM > 1u)
    #define Volt_Regulator_DEFAULT_SWITCH_CONF    0u
#else /* Disable SAR sequencer from enabling routing switches in single channel mode */
    #define Volt_Regulator_DEFAULT_SWITCH_CONF    Volt_Regulator_SWITCH_DISABLE
#endif /* End Volt_Regulator_TOTAL_CHANNELS_NUM > 1 */

#define Volt_Regulator_DEFAULT_POWER \
       ((Volt_Regulator_NOMINAL_CLOCK_FREQ > (Volt_Regulator_MAX_FREQUENCY / 4)) ? Volt_Regulator_NORMAL_PWR : \
       ((Volt_Regulator_NOMINAL_CLOCK_FREQ > (Volt_Regulator_MAX_FREQUENCY / 8)) ? Volt_Regulator_HALF_PWR : \
                                                                                       Volt_Regulator_QUARTER_PWR))

#define Volt_Regulator_DEFAULT_CTRL_REG_CFG       (Volt_Regulator_DEFAULT_VREF_SOURCE \
                                                   | Volt_Regulator_DEFAULT_SE_NEG_INPUT \
                                                   | Volt_Regulator_DEFAULT_HW_CTRL_NEGVREF \
                                                   | Volt_Regulator_DEFAULT_POWER \
                                                   | Volt_Regulator_DSI_SYNC_CONFIG \
                                                   | Volt_Regulator_DEFAULT_SWITCH_CONF)

#define Volt_Regulator_DEFAULT_SAMPLE_CTRL_REG_CFG (Volt_Regulator_DEFAULT_DIFF_RESULT_FORMAT \
                                                    | Volt_Regulator_DEFAULT_SE_RESULT_FORMAT \
                                                    | Volt_Regulator_DEFAULT_JUSTIFICATION \
                                                    | Volt_Regulator_DEFAULT_ALT_RESOLUTION \
                                           | (uint8)(Volt_Regulator_DEFAULT_AVG_SAMPLES_NUM \
                                                   << Volt_Regulator_AVG_CNT_OFFSET) \
                                                    | Volt_Regulator_AVG_SHIFT_MODE \
                                                    | Volt_Regulator_DSI_TRIGGER \
                                                    | Volt_Regulator_EOS_DSI_OUT_EN)

#define Volt_Regulator_DEFAULT_RANGE_THRES_REG_CFG (Volt_Regulator_DEFAULT_LOW_LIMIT \
            | (uint32)((uint32)Volt_Regulator_DEFAULT_HIGH_LIMIT << Volt_Regulator_RANGE_HIGH_OFFSET))

#define Volt_Regulator_DEFAULT_SAMPLE_TIME01_REG_CFG (Volt_Regulator_DEFAULT_ACLKS_NUM \
            | (uint32)((uint32)Volt_Regulator_DEFAULT_BCLKS_NUM << Volt_Regulator_SAMPLE_TIME13_OFFSET))

#define Volt_Regulator_DEFAULT_SAMPLE_TIME23_REG_CFG (Volt_Regulator_DEFAULT_CCLKS_NUM \
            | (uint32)((uint32)Volt_Regulator_DEFAULT_DCLKS_NUM << Volt_Regulator_SAMPLE_TIME13_OFFSET))


#endif /* End CY_ADC_SAR_SEQ_Volt_Regulator_H */


/* [] END OF FILE */
