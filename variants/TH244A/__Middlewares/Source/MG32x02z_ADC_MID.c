/**
 ******************************************************************************
 *
 * @file        MG32x02z_ADC_MID.c
 *
 * @brief       This file provides firmware functions to manage the following 
 *              functionalities of the ADC peripheral:
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.12
 * @date        2022/09/16
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2016 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************
 * @par 		Disclaimer 
 *		The Demo software is provided "AS IS"  without any warranty, either 
 *		expressed or implied, including, but not limited to, the implied warranties 
 *		of merchantability and fitness for a particular purpose.  The author will 
 *		not be liable for any special, incidental, consequential or indirect 
 *		damages due to loss of data or any other reason. 
 *		These statements agree with the world wide and local dictated laws about 
 *		authorship and violence against these laws. 
 ******************************************************************************
 ******************************************************************************
 */ 



#include "MG32x02z_ADC_MID.h"


/* Fixed timeout values for ADC calibration, enable settling time, disable  */
/* settling time.                                                           */
/* Values defined to be higher than worst cases: low clock frequency,       */
/* maximum prescaler.                                                       */
/* Ex of profile low frequency : Clock source at 0.1 MHz, ADC clock         */
/* prescaler 4, sampling time 7.5 ADC clock cycles, resolution 12 bits.     */
/* Unit: ms                                                                 */
#define ADC_ENABLE_TIMEOUT              10U /*!< Unit: ms */
#define ADC_DISABLE_TIMEOUT             2U  /*!< Unit: ms */
#define ADC_STOP_CONVERSION_TIMEOUT     2U  /*!< Unit: ms */

/* Delay for ADC stabilization time.                                        */
/* Maximum delay is 1us (refer to device datasheet, parameter tSTAB).       */
/* Unit: us                                                                 */
#define ADC_STAB_DELAY_US               1U  /*!< Unit: ms */

/* Delay for temperature sensor stabilization time.                         */
/* Maximum delay is 10us (refer to device datasheet, parameter tSTART).     */
/* Unit: us                                                                 */
#define ADC_TEMPSENSOR_DELAY_US         10U /*!< Unit: ms */

static MID_StatusTypeDef ADC_Enable(ADC_HandleTypeDef* mADC);
static MID_StatusTypeDef ADC_Disable(ADC_HandleTypeDef* mADC);
static MID_StatusTypeDef ADC_ConversionStop(ADC_HandleTypeDef* mADC);
static void ADC_DMAConvCplt(DMA_HandleTypeDef *hdma);
static void ADC_DMAHalfConvCplt(DMA_HandleTypeDef *hdma);
static void ADC_DMAError(DMA_HandleTypeDef *hdma);


 /**
 * @name	Initial/Deinitial ADC with ADC_HandleTypeDef
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief       Initializes the ADC peripheral and regular group according to
 *              parameters specified in structure "ADC_InitTypeDef".
 * @param[in]   mADC : pointer to a ADC_InitTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    ADC_HandleTypeDef mADC;
    
    mADC.Instance = ADC0;
    mADC.Init.ADCConType            = ADC_CONV_SINGLE;          // sigle-end type
    mADC.Init.ADCClock              = ADC_CLOCKPROC_DIV4;       // ADC clock = CK_ADC / 4
    mADC.Init.Resolution            = ADC_RESOLUTION_10B;       // ADC conversion resolution
    mADC.Init.DataAlign             = ADC_DATAALIGN_RIGHT;      // right-justified align
    mADC.Init.ConversionMode        = ADC_ONESHOT;              // conversion trigger mode = One soht mode
    mADC.Init.LowPowerAutoWait      = ADC_CONTINUE_NEXT;        // Disable ADC Wait mode
    mADC.Init.LowPowerAutoPowerOff  = ADC_NORMAL_POWER;         // Disable ADC Autor Power Off mode
    mADC.Init.PowerupTimerDIV       = ADC_SCNT_CLK_DIV16;       // ADC SCNT internal clock divider (DIV16). (for MG32_3RD, MG32_4TH)
    mADC.Init.PowerupTimerCNT       = 10;                       // ADC power-on start up counter. (for MG32_3RD, MG32_4TH)
    mADC.Init.TriggerConverionSrc   = ADC_SOFTWARE_START;       // Select software trigger
    mADC.Init.TriggerConverionEdge  = ADC_TRIGCONVEDGE_NONE;
    mADC.Init.Overrun               = ADC_ACCEPT_OVERRUN;       // Over write able
    mADC.Init.ExtendSamplingTime    = 0;                        // Sample & Hold time = 0
    mADC.Init.PGACmd                = PGA_ENABLE;               // Enable ADC PGA
    mADC.Init.PGAGain               = 0;                        // PGA Gain=x1, ADC Gain is equal : (1+(ADC0_GAIN_PGA*3)/(63+(63-ADC0_GAIN_PGA)*3))
    mADC.State                      = MID_ADC_STATE_RESET;      // Reset state
    
    MID_ADC_Init(&mADC);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_ADC_Init(ADC_HandleTypeDef* mADC)
{
    uint32_t tmpREG;
    
    // ------------------------------------------------------------------------
    /* Check ADC handle                                                       */
    // ------------------------------------------------------------------------
    if(mADC == NULL)
    {
        return MID_FAILURE;
    }
        
    // ------------------------------------------------------------------------
    if (mADC->State == MID_ADC_STATE_RESET)
    {
        /* Initialize ADC error code */
        __DRV_ADC_CLEAR_ERRORCODE(mADC);
        
        /* Allocate lock resource and initialize it */
        mADC->Lock = MID_UnLocked;
        
        /* Init the low level hardware */
        MID_ADC_MspInit(mADC);
    }

    // ------------------------------------------------------------------------
    /* Enable the ADC peripheral                                              */
    // ------------------------------------------------------------------------
    ADC_Enable(mADC);
    
    // ------------------------------------------------------------------------
    /* Config ADC Clock + Power-on control with Auto-off function             */
    // ------------------------------------------------------------------------
    #if defined(MG32_1ST) || defined(MG32_2ND)
        mADC->Instance->CLK.W = mADC->Init.ADCClock;
    #endif
    #if defined(MG32_3RD) || defined(MG32_4TH)
        mADC->Instance->CLK.W = (mADC->Init.ADCClock                        |\
                                 mADC->Init.PowerupTimerDIV                 |\
                                 mADC->Init.PowerupTimerCNT << 28);
    #endif
        
    // ------------------------------------------------------------------------
    /* Config of ADC parameters:                                              */
    /*  - Conversion Type (Single-End or Different mode)                      */
    /*  - LowPowerAutoWait mode                                               */
    /*  - LowPowerAutoPowerOff mode                                           */
    /*  - resolution                                                          */
    // ------------------------------------------------------------------------
    #if defined(MG32_1ST)
        tmpREG = mADC->Instance->CR0.W & ~(ADC_CR0_AUTOFF_EN_mask_w         |\
                 ADC_CR0_WAIT_EN_mask_w | ADC_CR0_RES_SEL_mask_w            |\
                 ADC_CR0_MDS_mask_w | ADC_CR0_CODE_FMT_mask_w);
                 
        tmpREG |= (mADC->Init.LowPowerAutoWait | mADC->Init.LowPowerAutoPowerOff |\
                  mADC->Init.Resolution | mADC->Init.ADCConType);
    #endif
    #if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
        tmpREG = mADC->Instance->CR0.W & ~(                                 \
                 ADC_CR0_WAIT_EN_mask_w | ADC_CR0_RES_SEL_mask_w);
                 
        tmpREG |= (mADC->Init.LowPowerAutoWait |                            \
                  mADC->Init.Resolution | mADC->Init.ADCConType);
    #endif
    
    // ------------------------------------------------------------------------
    // Setting output code (unsigned or 2's complment)
    #if defined(MG32_1ST)
    if(mADC->Init.ADCConType == ADC_CONV_DIFFERENT)     
        tmpREG |= ADC_CR0_CODE_FMT_2s_w;
    #endif
        
    // ------------------------------------------------------------------------
    // Config ADC base parameters
    mADC->Instance->CR0.W = tmpREG;
    
    // ------------------------------------------------------------------------
    /*  - PGA parameters                                                      */
    // ------------------------------------------------------------------------
    #if defined(MG32_1ST) || defined(MG32_2ND) || defined(MG32_3RD)
        // --------------------------------------------------------------------
        /*  - PGA Command                                                     */
        // --------------------------------------------------------------------
        if (mADC->Init.PGACmd == PGA_ENABLE)
            __DRV_ADC_PGA_ENABLE(mADC);
        else
            __DRV_ADC_PGA_DISABLE(mADC);
        
        // --------------------------------------------------------------------
        /*  - PGA Gain                                                        */
        // --------------------------------------------------------------------
        __DRV_ADC_PGA_UPDATE_GAIN(mADC, mADC->Init.PGAGain);
        
    #endif

    // ------------------------------------------------------------------------
    /*  overrun                                                               */
    /*  data alignment                                                        */
    // ------------------------------------------------------------------------
    tmpREG = mADC->Instance->CR1.W & ~(ADC_CR1_ALIGN_SEL_mask_w             |\
                                       ADC_CR1_OVR_MDS_mask_w);
    tmpREG |= (mADC->Init.Overrun | mADC->Init.DataAlign);
    mADC->Instance->CR1.W = tmpREG;
    
    // ------------------------------------------------------------------------
    /*  ConversionMode mode                                                   */
    /*  Trigger Converion Source                                              */
    /*  Trigger Converion edge                                                */
    // ------------------------------------------------------------------------
    tmpREG = mADC->Instance->START.W & ~(ADC_START_START_SEL_mask_w | ADC_START_TRG_SEL_mask_w | \
             ADC_START_CONV_MDS_mask_w | ADC_START_TRG_CONT_mask_w);
    tmpREG |= (mADC->Init.TriggerConverionSrc | mADC->Init.TriggerConverionEdge | mADC->Init.ConversionMode);
    mADC->Instance->START.W = tmpREG;
    
    // ------------------------------------------------------------------------
    /* Update ADC configuration register with previous settings               */
    // ------------------------------------------------------------------------
    tmpREG = mADC->Instance->CR0.W & ~(ADC_CR0_SMP_SEL_mask_w);
    tmpREG |= (mADC->Init.ExtendSamplingTime << 16);
    mADC->Instance->CR0.W = tmpREG;

    // ------------------------------------------------------------------------
    /* Another ADC performance parameters control.                            */
    // ------------------------------------------------------------------------
    #if defined (MG32_3RD) || defined(MG32_4TH)
        __DRV_ADC_SET_CONVERSTION_TIME(mADC, ADC_FAST_CONVERSION);
        __DRV_ADC_SET_OPERATION_CURRENT(mADC, ADC_OP_BIAS_LVL3);
        __DRV_ADC_SET_CLOCK_PHASE(mADC, ADC_CLOCK_PHASE2);
        #if defined(MG32_4TH)
            __DRV_ADC_DISCHARGE_ENABLE(mADC);
        #endif
    #endif
    #if defined (MG32_2ND)
        __DRV_ADC_SET_OPERATION_CURRENT(mADC, ADC_OP_BIAS_LVL3);
    #endif

    // ------------------------------------------------------------------------
    /* ADC calibration                                                        */
    // ------------------------------------------------------------------------
    MID_ADC_Calibration_Start(mADC);
    
    // ------------------------------------------------------------------------
    /* PGA calibration                                                        */
    // ------------------------------------------------------------------------
    #if defined(MG32_1ST) || defined(MG32_2ND) || defined(MG32_3RD)
        if (mADC->Init.PGACmd == PGA_ENABLE)
            MID_ADC_PGACalibration_Start(mADC);
    #endif
    
    // ------------------------------------------------------------------------
    /* Return function status                                                 */
    // ------------------------------------------------------------------------
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Deinitialize the ADC peripheral registers to their default reset
 *         		values, with deinitialization of the ADC MSP.
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    ADC_HandleTypeDef mADC;
 
    MID_ADC_DeInit(&mADC);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_ADC_DeInit(ADC_HandleTypeDef *mADC)
{

    /* Process locked */
    __MID_LOCK(mADC);

    /* 1. Stop potential conversion on going, on regular group */
    ADC_ConversionStop(mADC);

    /* Disable ADC end of conversion interrupt for regular group */
    /* Disable ADC overrun interrupt */
    __DRV_ADC_DISABLE_IT(mADC, (ADC_IT_ESMP | ADC_IT_E1CNV | ADC_IT_OVR));

    /* 2. Disable the ADC peripheral */
    ADC_Disable(mADC);

    /* Set ADC state */
    mADC->State = MID_ADC_STATE_READY;

    /* Process unlocked */
    __MID_UNLOCK(mADC);

    /* Return function status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Initializes the ADC Base MSP.
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_ADC_MspInit(ADC_HandleTypeDef* mADC)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mADC);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the MID_ADC_MspInit could be implemented in the user file
   */
}

/**
 *******************************************************************************
 * @brief       DeInitializes ADC Base MSP.
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_ADC_MspDeInit(ADC_HandleTypeDef* mADC)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mADC);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the MID_ADC_MspDeInit could be implemented in the user file
   */
}
///@} 


/**
 * @name	ADC_Exported_Functions_Group2 IO operation functions (IO operation functions)
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief       Enables ADC, starts conversion of regular group.
 *				Interruptions enabled in this function: None.
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    // Configure for the selected ADC regular channel to be converted.   
    MID_ADC_ConfigChannel(&mADC, &ADCChannelMux);
    
    // Trigger ADC Conversion
    MID_ADC_Start(&mADC);
    
    //  poll ADC flag
    MID_ADC_PollForConversion(&mADC, 10);
    
    // return ADC result
    return (uint16_t) MID_ADC_GetValue(&mADC);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_ADC_Start(ADC_HandleTypeDef* mADC)
{
    /* Enable conversion of                                                  */
    if(mADC->Init.TriggerConverionSrc == ADC_SOFTWARE_START)
        mADC->Instance->START.W |= ADC_START_START_mask_w;
    
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stop ADC conversion of regular group, disable ADC peripheral.
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    MID_ADC_Stop(&mADC);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_ADC_Stop(ADC_HandleTypeDef* mADC)
{
    /* Stop potential conversion on going, on regular group */
    ADC_ConversionStop(mADC);
    
    /* Set ADC state */
    mADC->State = MID_ADC_STATE_READY;
    
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Wait for regular group conversion to be completed.
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @param[in]   Timeout : Specify the timeout setting
 * @return		MID_StatusTypeDef
 * @note   	    ADC conversion flags E1CNVF are cleared by this function, with 
 *              an exception: if low power feature "LowPowerAutoWait" is enabled,
 *              flags are not cleared to not interfere with this feature until 
 *              data register is read using function MID_ADC_GetValue().
 * @note   	    This function cannot be used in a particular setup: ADC configured 
 *         	    in DMA mode and polling for end of each conversion.
 *         	    In this case, DMA resets the flag E1CNVF and polling cannot be
 *         	    performed on each conversion. Nevertheless, polling can still 
 *         	    be performed on the complete sequence.
 * @par         Example
 * @code
    // Configure for the selected ADC regular channel to be converted.   
    MID_ADC_ConfigChannel(&mADC, &ADCChannelMux);
    
    // Trigger ADC Conversion
    MID_ADC_Start(&mADC);
    
    //  poll ADC flag
    MID_ADC_PollForConversion(&mADC, 10);
    
    // return ADC result
    return (uint16_t) MID_ADC_GetValue(&mADC);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_ADC_PollForConversion(ADC_HandleTypeDef* mADC, uint32_t Timeout)
{
    uint32_t tickstart;

    /* Get tick count */
    tickstart = MID_GetTick();
    
    /* Wait until End of Conversion flag is raised */
    switch(mADC->Init.ConversionMode)
    {
    /* Trigger once and conversion once                                       */
    case ADC_ONESHOT:
        __DRV_ADC_DISABLE_IT(mADC, ADC_IT_E1CNV);
        
        /* Wait until End of Conversion flag is raised */
        while(1)
        {
            // one channel conversion end flag
            if(__DRV_ADC_GET_FLAG(mADC, ADC_FLAG_E1CNV) != 0x00)
            {
                mADC->State = MID_ADC_STATE_READY;
                return MID_SUCCESS;
            }
            
            /* Check if timeout is disabled (set to infinite wait) */ 
            if(Timeout != MID_MAX_DELAY)
            {
                if((MID_GetTick()-tickstart) > Timeout)
                {
                    /* Update ADC state machine to timeout */
                    mADC->State = MID_ADC_STATE_TIMEOUT;

                    /* Process unlocked */
                    __MID_UNLOCK(mADC);

										break;
                }
            }
        }
				return MID_TIMEOUT;
    
    /* Trigger once and repeat convesion one channel                          */
    case ADC_REPITIVE_CHANNEL:   
        __DRV_ADC_DISABLE_IT(mADC, ADC_IT_E1CNV);
        // one channel conversion end flag
        /* Wait until End of Conversion flag is raised */
        while(1)
        {
            // one channel conversion end flag
            if(__DRV_ADC_GET_FLAG(mADC, ADC_FLAG_E1CNV) != 0x00)
            {
                mADC->State = MID_ADC_STATE_READY;
                return MID_SUCCESS;
            }
            
            /* Check if timeout is disabled (set to infinite wait) */ 
            if(Timeout != MID_MAX_DELAY)
            {
                if((MID_GetTick()-tickstart) > Timeout)
                {
                    /* Update ADC state machine to timeout */
                    mADC->State = MID_ADC_STATE_TIMEOUT;

                    /* Process unlocked */
                    __MID_UNLOCK(mADC);

										break;
                }
            }
        }
				return MID_TIMEOUT;
    
    /* Manual trigger conversion                                              */
    case ADC_SCAN_MANUAL:   
        __DRV_ADC_DISABLE_IT(mADC, ADC_IT_E1CNV);
        // one channel conversion end flag
        /* Wait until End of Conversion flag is raised */
        while(1)
        {
            // one channel conversion end flag
            if(__DRV_ADC_GET_FLAG(mADC, ADC_FLAG_E1CNV) != 0x00)
            {
                mADC->State = MID_ADC_STATE_READY;
                return MID_SUCCESS;
            }
            
            /* Check if timeout is disabled (set to infinite wait) */ 
            if(Timeout != MID_MAX_DELAY)
            {
                if((MID_GetTick()-tickstart) > Timeout)
                {
                    /* Update ADC state machine to timeout */
                    mADC->State = MID_ADC_STATE_TIMEOUT;

                    /* Process unlocked */
                    __MID_UNLOCK(mADC);

										break;
                }
            }
        }
				return MID_TIMEOUT;
    
    /* TTrigger once and auto scan mask channel                               */
    case ADC_SCAN_AUTO:   
        __DRV_ADC_DISABLE_IT(mADC, ADC_IT_E1CNV | ADC_IT_ESCNV);
        // scan conversion end flag
        /* Wait until End of Conversion flag is raised */
        while(1)
        {
            // one channel conversion end flag
            if(__DRV_ADC_GET_FLAG(mADC, ADC_FLAG_ESCNV) != 0x00)
            {
                mADC->State = MID_ADC_STATE_READY;
                return MID_SUCCESS;
            }
            
            /* Check if timeout is disabled (set to infinite wait) */ 
            if(Timeout != MID_MAX_DELAY)
            {
                if((MID_GetTick()-tickstart) > Timeout)
                {
                    /* Update ADC state machine to timeout */
                    mADC->State = MID_ADC_STATE_TIMEOUT;

                    /* Process unlocked */
                    __MID_UNLOCK(mADC);

										break;
                }
            }
        }
				return MID_TIMEOUT;
    
    /* Conversion loop mode                                                   */
    case ADC_LOOP_AUTO:   
        __DRV_ADC_DISABLE_IT(mADC, ADC_IT_E1CNV | ADC_IT_ESCNV);
        
        if(mADC->Instance->MSK.H[0] != 0x0000)
        {
            /* Wait until End of Conversion flag is raised */
            while(1)
            {
                // one channel conversion end flag
                if(__DRV_ADC_GET_FLAG(mADC, ADC_FLAG_ESCNV) != 0x00)
                {
                    mADC->State = MID_ADC_STATE_READY;
                    return MID_SUCCESS;
                }
                
                /* Check if timeout is disabled (set to infinite wait) */ 
                if(Timeout != MID_MAX_DELAY)
                {
                    if((MID_GetTick()-tickstart) > Timeout)
                    {
                        /* Update ADC state machine to timeout */
                        mADC->State = MID_ADC_STATE_TIMEOUT;

                        /* Process unlocked */
                        __MID_UNLOCK(mADC);

												break;
                    }
                }
            }
						return MID_TIMEOUT;
        }
        else
        {
            /* Wait until End of Conversion flag is raised */
            while(1)
            {
                // one channel conversion end flag
                if(__DRV_ADC_GET_FLAG(mADC, ADC_FLAG_E1CNV) != 0x00)
                {
                    mADC->State = MID_ADC_STATE_READY;
                    return MID_SUCCESS;
                }
                
                /* Check if timeout is disabled (set to infinite wait) */ 
                if(Timeout != MID_MAX_DELAY)
                {
                    if((MID_GetTick()-tickstart) > Timeout)
                    {
                        /* Update ADC state machine to timeout */
                        mADC->State = MID_ADC_STATE_TIMEOUT;

                        /* Process unlocked */
                        __MID_UNLOCK(mADC);

												break;
                    }
                }
            }
        }
				return MID_TIMEOUT;
    
    default:
        mADC->State = MID_ADC_STATE_READY;
        mADC->ErrorCode = MID_ADC_ERROR_INTERNAL;
        return MID_FAILURE;
    }
    
}

/**
 *******************************************************************************
 * @brief       Poll for conversion event.
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @param[in]   EventType : EventType the ADC event type.
 *              This parameter can be one of the following values:
 *  @arg\b	    ADC_AWD_EVENT: ADC Analog watchdog event
 *  @arg\b	    ADC_OVR_EVENT: ADC Overrun event
 * @param[in]   Timeout : Specify the timeout setting
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    ADC_HandleTypeDef mADC;
 
    MID_ADC_PollForEvent(&mADC, ADC_OVR_EVENT);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_ADC_PollForEvent(ADC_HandleTypeDef* mADC, uint32_t EventType, uint32_t Timeout)
{
    uint32_t tickstart = 0;
    
    /* Get tick count */
    tickstart = MID_GetTick();
    
    /* Check selected event flag */
    while(__DRV_ADC_GET_EVENT(mADC, EventType) == 0x0000)
    {
        /* Check if timeout is disable (set to infinite wait) */
        if(Timeout != MID_MAX_DELAY)
        {
            if((Timeout == 0U) || ((MID_GetTick() - tickstart) > Timeout))
            {
                /* Update ADC state machine to timeout */
                mADC->State = MID_ADC_STATE_TIMEOUT;
                
                /* Process unlocked */
                __MID_UNLOCK(mADC);
                
                return MID_TIMEOUT;
            }
        }     
    }
    
    switch(EventType)
    {
    /* Analog watchdog (level out of window) event */
    case ADC_AWD_EVENT:
        /* Set ADC state */
        mADC->State = MID_ADC_STATE_AWD1;

        /* Clear ADC analog watchdog flag */
        __DRV_ADC_CLEAR_FLAG(mADC, ADC_FLAG_AWD);
        break;

    /* Overrun event */
    default: /* Case ADC_OVR_EVENT */
        /* If overrun is set to overwrite previous data, overrun event is not     */
        /* considered as an error.                                                */
        /* (cf ref manual "Managing conversions without using the DMA and without */
        /* overrun ")                                                             */
        if (mADC->Init.Overrun == ADC_ACCEPT_OVERRUN)
        {
            /* Set ADC state */
            mADC->State = MID_ADC_STATE_REG_OVR;

            /* Set ADC error code to overrun */
            mADC->ErrorCode = MID_ADC_ERROR_OVR;
        }

        /* Clear ADC Overrun flag */
        __DRV_ADC_CLEAR_FLAG(mADC, ADC_FLAG_OVR);
        break;
    }
  
    
    /* Return function status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Enables ADC, starts conversion of regular group with interruption.
 *         		Interruptions enabled in this function:
 *         		 - ADC_IT_E1CNV (end of conversion of regular group) or ADC_IT_ESCNV 
 *                 (end of sequence of regular group) depending on ADC initialization 
 *         		   parameter "EOCSelection"
 *         		 - overrun (if available)
 *         		Each of these interruptions has its dedicated callback function.
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    ADC_HandleTypeDef mADC;
 
    MID_ADC_Start_IT(&mADC);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_ADC_Start_IT(ADC_HandleTypeDef* mADC)
{
  
    /* Perform ADC enable and conversion start if no conversion is on going  */
    
    /* Process locked */
    __MID_LOCK(mADC);
     
    /* Set ADC state                                                         */
    /* - Clear state bitfield related to regular group conversion results    */
    /* - Set state bitfield related to regular operation                     */
    mADC->State = MID_ADC_STATE_REG_BUSY;                                    
                                                                             
    /* Reset ADC all error code fields */                                    
    mADC->ErrorCode = MID_ADC_ERROR_NONE;                                    
                                                                             
    /* Process unlocked */                                                   
    /* Unlock before starting ADC conversions: in case of potential          */
    /* interruption, to let the process to ADC IRQ Handler.                  */
    __MID_UNLOCK(mADC);                                                      
                                                                             
    /* Clear regular group conversion flag and overrun flag */               
    /* (To ensure of no unknown state from potential previous ADC            */
    /* operations)                                                           */
    __DRV_ADC_CLEAR_FLAG(mADC, (ADC_FLAG_ESMP | ADC_FLAG_E1CNV | ADC_FLAG_ESCNV | ADC_FLAG_OVR));
      
    /* Clear all IT                                                          */
    __DRV_ADC_DISABLE_IT(mADC, (ADC_IT_ESMP | ADC_IT_E1CNV | ADC_IT_ESCNV | ADC_IT_OVR));
    
    /* Enable IT what ADC conversion mode                                    */
    switch(mADC->Init.ConversionMode)
    {
    /* Trigger once and conversion once                                       */
    case ADC_ONESHOT:
        __DRV_ADC_ENABLE_IT(mADC, (ADC_IT_E1CNV | ADC_IT_OVR));
        __DRV_ADC_ENABLE_ITEA(mADC);
        break;
    
    /* Trigger once and repeat convesion one channel                          */
    case ADC_REPITIVE_CHANNEL:   
        __DRV_ADC_ENABLE_IT(mADC, (ADC_IT_E1CNV | ADC_IT_OVR));
        __DRV_ADC_ENABLE_ITEA(mADC);
        break;
    
    /* Manual trigger conversion                                              */
    case ADC_SCAN_MANUAL:   
        __DRV_ADC_ENABLE_IT(mADC, (ADC_IT_E1CNV | ADC_IT_ESCNV | ADC_IT_OVR));
        __DRV_ADC_ENABLE_ITEA(mADC);
        break;
    
    /* Trigger once and auto scan mask channel                               */
    case ADC_SCAN_AUTO:   
        __DRV_ADC_ENABLE_IT(mADC, (ADC_IT_ESCNV | ADC_IT_OVR));
        __DRV_ADC_ENABLE_ITEA(mADC);
        break;
    
    /* Conversion loop mode                                                   */
    case ADC_LOOP_AUTO:   
        if(mADC->Instance->MSK.H[0] != 0x0000)
            __DRV_ADC_ENABLE_IT(mADC, (ADC_IT_ESCNV | ADC_IT_OVR));
        else
            __DRV_ADC_ENABLE_IT(mADC, (ADC_IT_E1CNV | ADC_IT_OVR));
        
        __DRV_ADC_ENABLE_ITEA(mADC);
        break;
    
    default:
        return MID_FAILURE;
    }

      
    /* Enable conversion of regular group.                                  */
    /* If software start has been selected, conversion starts immediately.  */
    /* If external trigger has been selected, conversion will start at next */
    /* trigger event.                                                       */
    if(mADC->Init.TriggerConverionSrc == ADC_SOFTWARE_START)
        mADC->Instance->START.W |= ADC_START_START_mask_w;
    
    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stop ADC conversion of regular group, disable interruption of 
 *         		end-of-conversion, disable ADC peripheral.
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    ADC_HandleTypeDef mADC;
 
    MID_ADC_Stop_IT(&mADC);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_ADC_Stop_IT(ADC_HandleTypeDef* mADC)
{

    /* Process locked */
    __MID_LOCK(mADC);

    /* 1. Stop potential conversion on going, on regular group */
    ADC_ConversionStop(mADC);

    /* Disable ADC end of conversion interrupt for regular group */
    /* Disable ADC overrun interrupt */
    __DRV_ADC_DISABLE_IT(mADC, (ADC_IT_E1CNV | ADC_IT_ESCNV | ADC_IT_OVR));

    /* 2. Disable the ADC peripheral */
    ADC_Disable(mADC);

    /* Set ADC state */
    mADC->State = MID_ADC_STATE_READY;

    /* Process unlocked */
    __MID_UNLOCK(mADC);

    /* Return function status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Enables ADC, starts conversion of regular group and transfers result
 *         		through DMA.
 *         		Interruptions enabled in this function:
 *         		 - DMA transfer complete
 *         		 - DMA half transfer
 *         		 - overrun
 *         		Each of these interruptions has its dedicated callback function.
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @param[in]   pData : The destination buffer address.
 * @param[in]   Length : The length of data to be transferred.
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    MID_ADC_Start_DMA(&mADC, &DestinationAddress, 20);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_ADC_Start_DMA(ADC_HandleTypeDef* mADC, uint32_t* pData, uint32_t Length)
{
    
    /* Perform ADC enable and conversion start if no conversion is on going */

    /* Process locked */
    __MID_LOCK(mADC);

    /* Enable the ADC peripheral */
    ADC_Enable(mADC);

    /* Process unlocked */
    /* Unlock before starting ADC conversions: in case of potential         */
    /* interruption, to let the process to ADC IRQ Handler.                 */
    __MID_UNLOCK(mADC);
    
    /* Set the DMA Period elapsed callback */
    mADC->DMA_Handle->XferCpltCallback  = ADC_DMAConvCplt;

    /* Set the DMA half transfer complete callback */
    mADC->DMA_Handle->XferHalfCpltCallback = ADC_DMAHalfConvCplt;

    /* Set the DMA error callback */
    mADC->DMA_Handle->XferErrorCallback = ADC_DMAError ;

    /* Clear regular group conversion flag and overrun flag */
    /* (To ensure of no unknown state from potential previous ADC           */
    /* operations)                                                          */
    __DRV_ADC_CLEAR_FLAG(mADC, (ADC_FLAG_ESMP | ADC_FLAG_E1CNV | ADC_FLAG_ESCNV | ADC_FLAG_OVR));

    /* Enable ADC overrun interrupt */
    __DRV_ADC_ENABLE_IT(mADC, ADC_IT_OVR);
    __DRV_ADC_ENABLE_ITEA(mADC);

    /* Enable the ADC Capture/Compare 0 DMA request */
    __DRV_ADC_ENABLE_DMA(mADC);
      
    /* Start the DMA channel */
    MID_DMA_Start_IT(mADC->DMA_Handle, 0, (uint32_t)pData, Length);  

    /* Set ADC state                                                        */
    /* - Clear state bitfield related to regular group conversion results   */
    /* - Set state bitfield related to regular operation                    */
    mADC->State = MID_ADC_STATE_REG_BUSY;

    /* Reset ADC all error code fields */
    mADC->ErrorCode = MID_ADC_ERROR_NONE;

    /* Enable conversion of regular group.                                  */
    /* If software start has been selected, conversion starts immediately.  */
    /* If external trigger has been selected, conversion will start at next */
    /* trigger event.                                                       */
    mADC->Instance->START.W |= ADC_START_START_mask_w;
    
    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stop ADC conversion of regular group, disable ADC DMA transfer, disable 
 *         		ADC peripheral.
 *         		Each of these interruptions has its dedicated callback function.
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @note 
 * @par         Example
 * @code
    ADC_HandleTypeDef mADC;
 
    MID_ADC_Stop_DMA(&mADC);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_ADC_Stop_DMA(ADC_HandleTypeDef* mADC)
{
    
    /* Process locked */
    __MID_LOCK(mADC);

    /* 1. Stop potential conversion on going, on regular group */
    ADC_ConversionStop(mADC);

    /* Disable ADC DMA (ADC DMA configuration ADC_CFGR_DMACFG is kept) */
    __DRV_ADC_DISABLE_DMA(mADC);

    /* Disable the DMA channel (in case of DMA in circular mode or stop while */
    /* while DMA transfer is on going)                                        */
    /* Check if DMA channel effectively disabled */
    MID_DMA_Abort(mADC->DMA_Handle);

    /* Disable ADC overrun interrupt */
    __DRV_ADC_DISABLE_IT(mADC, ADC_IT_OVR);

    /* 2. Disable the ADC peripheral */
    /* Update "tmp_MID_status" only if DMA channel disabling passed, to keep  */
    /* in memory a potential failing status.                                  */
    ADC_Disable(mADC);

    /* Check if ADC is effectively disabled */
    mADC->State = MID_ADC_STATE_READY;

    /* Process unlocked */
    __MID_UNLOCK(mADC);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Get ADC conversion result.
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @return		ADC conversion data
 *******************************************************************************
 */
uint32_t MID_ADC_GetValue(ADC_HandleTypeDef* mADC)
{
    /* Return ADC converted value */ 
    return mADC->Instance->DAT0.H[0];
}

/**
 *******************************************************************************
 * @brief       Get ADC SUM0 accumulation result.
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @return		ADC SUM0 accumulation data
 *******************************************************************************
 */
uint32_t MID_ADC_GetSUM0Value(ADC_HandleTypeDef* mADC)
{
    /* Return ADC accumulation value */ 
    return mADC->Instance->SUM0.H[0];
}


/**
 *******************************************************************************
 * @brief       Get ADC SUM1 accumulation result.
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @return		ADC SUM1 accumulation data
 *******************************************************************************
 */
uint32_t MID_ADC_GetSUM1Value(ADC_HandleTypeDef* mADC)
{
    /* Return ADC accumulation value */ 
    return mADC->Instance->SUM1.H[0];
}


/**
 *******************************************************************************
 * @brief       Get ADC SUM2 accumulation result.
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @return		ADC SUM2 accumulation data
 *******************************************************************************
 */
uint32_t MID_ADC_GetSUM2Value(ADC_HandleTypeDef* mADC)
{
    /* Return ADC accumulation value */ 
    return mADC->Instance->SUM2.H[0];
}


/**
 *******************************************************************************
 * @brief       Handles ADC interrupt request.  
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @return		None
 * @note 
 * @par         Example
 * @code
    ADC_HandleTypeDef mADC;
 
    MID_ADC_IRQHandler(&mADC);
 * @endcode
 *******************************************************************************
 */
void MID_ADC_IRQHandler(ADC_HandleTypeDef* mADC)
{
    /* ========== Check End of Conversion flag for regular group ========== */
    if(__DRV_ADC_GET_EVENT(mADC, ADC_IT_CONVERSION) && __DRV_ADC_GET_IT_EVENT(mADC, ADC_IT_CONVERSION))
    {

        /* Determine whether any further conversion upcoming on group regular     */
        /* by external trigger, continuous mode or scan sequence on going.        */
        switch(mADC->Init.ConversionMode)
        {
        case ADC_ONESHOT:           // One chnnel complete end
            __DRV_ADC_DISABLE_IT(mADC, (ADC_IT_E1CNV));
            break;
        
        case ADC_REPITIVE_CHANNEL:  // Repitive sample channel
            break;
        
        case ADC_SCAN_MANUAL:       // until ADC scan complete 
            if(__DRV_ADC_GET_FLAG(mADC, ADC_FLAG_ESCNV) == 0x00)
            {
                __DRV_ADC_DISABLE_IT(mADC, (ADC_IT_E1CNV | ADC_IT_ESCNV));
                mADC->State = MID_ADC_STATE_READY;
            }
            break;
            
        case ADC_SCAN_AUTO:         // Scan complete end 
            __DRV_ADC_DISABLE_IT(mADC, (ADC_IT_E1CNV | ADC_IT_ESCNV));
            mADC->State = MID_ADC_STATE_READY;
            break;
        
        case ADC_LOOP_AUTO:         // Don't stop ADC conversion mode
            break;
        
        default:
            break;
        }
        

        /* Conversion complete callback */
        /* Note: into callback, to determine if conversion has been triggered     */
        /*       from EOC or EOS, possibility to use:                             */
        /*        " if( ____DRV_ADC_GET_FLAG(&mADC, ADC_FLAG_EOS)) "              */
        MID_ADC_ConvCpltCallback(mADC);


        /* Clear regular group conversion flag */
        /* Note: in case of overrun set to ADC_OVR_DATA_PRESERVED, end of         */
        /*       conversion flags clear induces the release of the preserved data.*/
        /*       Therefore, if the preserved data value is needed, it must be     */
        /*       read preliminarily into MID_ADC_ConvCpltCallback().              */
        __DRV_ADC_CLEAR_FLAG(mADC, (ADC_FLAG_E1CNV | ADC_FLAG_ESCNV) );
    }

    /* ========== Check Analog watchdog flags ========== */
    if(__DRV_ADC_GET_EVENT(mADC, ADC_FLAG_AWD) && __DRV_ADC_GET_IT_EVENT(mADC, ADC_IT_AWD))
    {
        /* Set ADC state */
        mADC->State = MID_ADC_STATE_AWD1;

        /* Level out of window callback */ 
        MID_ADC_LevelOutOfWindowCallback(mADC);

        /* Clear ADC Analog watchdog flag */
        __DRV_ADC_CLEAR_FLAG(mADC, ADC_FLAG_AWD);

    }


    /* ========== Check Overrun flag ========== */
    if(__DRV_ADC_GET_FLAG(mADC, ADC_FLAG_OVR) && __DRV_ADC_GET_IT_SOURCE(mADC, ADC_IT_OVR))
    {
        /* If overrun is set to overwrite previous data (default setting),        */
        /* overrun event is not considered as an error.                           */
        /* (cf ref manual "Managing conversions without using the DMA and without */
        /* overrun ")                                                             */
        /* Exception for usage with DMA overrun event always considered as an     */
        /* error.                                                                 */
        if (mADC->Init.Overrun == ADC_ACCEPT_OVERRUN)  
        {
            /* Set ADC error code to overrun */
            mADC->ErrorCode = MID_ADC_ERROR_OVR;

            /* Clear ADC overrun flag */
            __DRV_ADC_CLEAR_FLAG(mADC, ADC_FLAG_OVR);

            /* Error callback */ 
            MID_ADC_ErrorCallback(mADC);
        }

        /* Clear the Overrun flag */
        __DRV_ADC_CLEAR_FLAG(mADC, ADC_FLAG_OVR);
    }
    /* ========== Check accumulation event ========== */
    if(__DRV_ADC_GET_EVENT(mADC, ADC_SUM_EVENT) && __DRV_ADC_GET_IT_EVENT(mADC, ADC_IT_SUM))
    {
        
        /* ADC Sum callback */
        MID_ADC_SumCallback(mADC);
        
        /* Clear all accumulation flag */
        __DRV_ADC_CLEAR_FLAG(mADC, ADC_FLAG_SUM);
    }

}


/**
 *******************************************************************************
 * @brief       Conversion complete callback in non blocking mode 
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_ADC_ConvCpltCallback(ADC_HandleTypeDef* mADC)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mADC);

}


/**
 *******************************************************************************
 * @brief       Conversion DMA half-transfer callback in non blocking mode 
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* mADC)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mADC);

  /* NOTE : This function should not be modified. When the callback is needed,
            function MID_ADC_ConvHalfCpltCallback must be implemented in the user file.
   */
}

/**
 *******************************************************************************
 * @brief       Analog watchdog callback in non blocking mode. 
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @return		None
 * @note 
 * @par         Example
 * @code
    MID_ADC_LevelOutOfWindowCallback(&mADC);
 * @endcode
 *******************************************************************************
 */
__weak void MID_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* mADC)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mADC);

}

/**
 *******************************************************************************
 * @brief       ADC error callback in non blocking mode
 *        		(ADC conversion with interruption or transfer by DMA)
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_ADC_ErrorCallback(ADC_HandleTypeDef *mADC)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mADC);

}

/**
 *******************************************************************************
 * @brief       ADC Sum callback in non blocking mode
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_ADC_SumCallback(ADC_HandleTypeDef *mADC)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mADC);

}
///@}


/**
 * @name	Config ADC conversion channel & window detect
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief       Configures the the selected channel to be linked to the regular
 *         		group.
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @param[in]   ChannelMux : pointer to a ADC_HandleTypeDef
 *  @arg\b	    Channel : The channel select for ADC ADC_ONESHOT or 
 *              ADC_REPITIVE_CHANNEL mode.
 *  @arg\b	    SequenceChannelMUX : The channel select for ADC_SCAN_MANUALt 
 *              or ADC_SCAN_AUTO or ADC_LOOP_AUTO mode.
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    MID_ADC_ConfigChannel(&mADC, &ADCChannelMux);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_ADC_ConfigChannel(ADC_HandleTypeDef* mADC, ADC_ChannelConfTypeDef *ChannelMux)
{
    /* Process locked */
    __MID_LOCK(mADC);

    /* Parameters update conditioned to ADC state:                              */
    /*  - Channel number                                                        */
    switch(mADC->Init.ConversionMode)
    {
    /* Trigger once and conversion once                                       */
    case ADC_ONESHOT:
    /* Trigger once and repeat convesion one channel                          */
    case ADC_REPITIVE_CHANNEL:   
        __DRV_ADC_CHSELR_CHANNEL(mADC, ChannelMux->Channel);
        break;
    
    /* Manual trigger conversion                                              */
    case ADC_SCAN_MANUAL:   
    /* TTrigger once and auto scan mask channel                               */
    case ADC_SCAN_AUTO:   
    /* Conversion loop mode                                                   */
    case ADC_LOOP_AUTO:   
        if ((ChannelMux->Channel & ADC_START_CH_SEL_mask_w) == 0)
            ADC0->START.W &= ~(ADC_START_CH_SEL_mask_w);            // select external channel
        else
            ADC0->START.W |= (ADC_START_CH_SEL_mask_w);             // select internal channel
            
        __DRV_ADC_RQGULAR_CHANNEL(mADC, ChannelMux->SequenceChannelMUX);
        break;
    
    default:
        return MID_FAILURE;
    }

    /* Process unlocked */
    __MID_UNLOCK(mADC);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Configures the analog watchdog.
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @param[in]   AnalogWDGConfig : pointer to a ADC_AnalogWDGConfTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    ADC_AnalogWDGConfTypeDef ADC_WDG;

    // modify parameters
    ADC_WDG.WatchdogMode    = ADC_ANALOGWATCHDOG_SINGLE_REG;
    ADC_WDG.Channel         = ADC_CHANNEL_3;
    ADC_WDG.ITMode          = NULL;                 // polling mode
    ADC_WDG.HighThreshold   = 3000;                 
    ADC_WDG.LowThreshold    = 1000; 
    ADC_WDG.WatchdogDataLimit = ADC_ANALOGWATCHDOG_KEEP_DATA;   // keep data when result is ouside
 
    MID_ADC_AnalogWDGConfig(&mADC, &ADC_WDG);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_ADC_AnalogWDGConfig(ADC_HandleTypeDef* mADC, ADC_AnalogWDGConfTypeDef* AnalogWDGConfig)
{
    
    /* Process locked */
    __MID_LOCK(mADC);
        
    /* Parameters update conditioned to ADC state:                              */
    /* Parameters that can be updated when ADC is disabled or enabled without   */
    /* conversion on going on regular group:                                    */
    if(AnalogWDGConfig->WatchdogMode == ADC_ANALOGWATCHDOG_NONE)
    {
        mADC->Instance->CR1.W &= ~(ADC_CR1_WIND_EN_disable_w);
        __DRV_ADC_DISABLE_IT(mADC, ADC_IT_AWD);
    }
    else
    {
        /*  - Analog watchdog mode                                           */
        mADC->Instance->CR1.W &= ~(ADC_CR1_WIND_MDS_mask_w);
        mADC->Instance->CR1.W |= AnalogWDGConfig->WatchdogMode;

        /*  - Analog watchdog channels (Only support scan channel mode)      */
        mADC->Instance->START.W &= ~(ADC_START_CH_SEL_mask_w | ADC_START_CH_MUX_mask_w);
        mADC->Instance->START.W |= (AnalogWDGConfig->Channel & ~(ADC_START_CH_SEL_mask_w));        
        
        /*  - Analog watchdog thresholds                                     */
        mADC->Instance->WINDTH.MBIT.WIND_HT = (uint16_t) AnalogWDGConfig->HighThreshold;
        mADC->Instance->WINDTH.MBIT.WIND_LT = (uint16_t) AnalogWDGConfig->LowThreshold;
        
        /*  - Analog watchdog thresholds with ADC data output               */
        mADC->Instance->CR0.W &= ~(ADC_CR0_LIM_MDS_mask_w);
        mADC->Instance->CR0.W |= (AnalogWDGConfig->WatchdogDataLimit);        
        
        /*  - Analog watchdog interrupt                                      */
        __DRV_ADC_ENABLE_IT(mADC, AnalogWDGConfig->ITMode);
        
    }
    /* Process unlocked */
    __MID_UNLOCK(mADC);
    
    /* Return function status */
    return MID_SUCCESS;
    
}



/**
 *******************************************************************************
 * @brief       Configures the analog watchdog.
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @param[in]   AccumulateConfig : pointer to a ADC_AccumulateConfDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    ADC_AccumulateConfDef sSUM;

    // modify parameters
    sSUM.AccumulationMode   = ADC_ACCUMULATE_DECLARE_SUMCH;
    sSUM.SUM0_Channel       = ADC_SUMx_CHANNEL3;
    sSUM.SUM1_Channel       = ADC_SUMx_CHANNEL9;
    sSUM.SUM2_Channel       = ADC_SUMx_CHANNEL12;
    sSUM.SUM0_Init          = 0;
    sSUM.SUM1_Init          = 0;
    sSUM.SUM2_Init          = 0;
    sSUM.ITMode             = (ADC_IT_SUMO | ADC_IT_SUMC | ADC_IT_SUMOVR);
    sSUM.AccumulateNumber   = 10;
    sSUM.SOverrun           = ADC_SUM_ACCEPT_OVERRUN;
    
    MID_ADC_AccumulateConfig(&mADC, &sSUM);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_ADC_AccumulateConfig(ADC_HandleTypeDef* mADC, ADC_AccumulateConfDef* AccumulateConfig)
{
    uint32_t tmpReg;
    
    /* Process locked */
    __MID_LOCK(mADC);
        
    /* Parameters update conditioned to ADC accumulation mode, data, numbers    */
    tmpReg = mADC->Instance->CR1.W & ~(
                ADC_CR1_SUM_NUM_mask_w |    /* accumulation data number */
                ADC_CR1_SUM_MDS_mask_w |    /* ADC data accumulation sum channel mode selec */
                ADC_CR1_SOVR_MDS_mask_w);   /* ADC data sum overrun mode */
    
    tmpReg |= ((AccumulateConfig->AccumulateNumber << 16)  | AccumulateConfig->SOverrun | AccumulateConfig->AccumulationMode);
    mADC->Instance->CR1.W = tmpReg;
        
    /* Parameters update conditioned to SUM0/1/2 channel                        */
    tmpReg = mADC->Instance->MSK.W & ~(
                ADC_MSK_SUM0_MUX_mask_w |   
                ADC_MSK_SUM1_MUX_mask_w |   
                ADC_MSK_SUM2_MUX_mask_w);   
    
    tmpReg |= ((AccumulateConfig->SUM0_Channel << 16) | (AccumulateConfig->SUM1_Channel << 20) | (AccumulateConfig->SUM2_Channel << 24));
    mADC->Instance->MSK.W = tmpReg;
    
    /* Initial SUM0/1/2 base value for accumulation                             */
    mADC->Instance->SUM0.W = (AccumulateConfig->SUM0_Init & 0x0000FFFF);  
    mADC->Instance->SUM1.W = (AccumulateConfig->SUM1_Init & 0x0000FFFF);  
    mADC->Instance->SUM2.W = (AccumulateConfig->SUM2_Init & 0x0000FFFF);  
    
    /*  - Accumulation interrupt                                                */
    __DRV_ADC_ENABLE_IT(mADC, AccumulateConfig->ITMode);
    if(AccumulateConfig->ITMode != 0)
        __DRV_ADC_ENABLE_ITEA(mADC);
        
    /* Process unlocked */
    __MID_UNLOCK(mADC);
    
    /* Return function status */
    return MID_SUCCESS;
    
}

/**
 *******************************************************************************
 * @brief       Return the ADC state
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @return		ADC state
 *******************************************************************************
 */
uint32_t MID_ADC_GetState(ADC_HandleTypeDef* mADC)
{
    return mADC->State;
}


/**
 *******************************************************************************
 * @brief       Return the ADC error code
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @return		ADC Error Code
 *******************************************************************************
 */
uint32_t MID_ADC_GetError(ADC_HandleTypeDef *mADC)
{
    return mADC->ErrorCode;
}


/**
 *******************************************************************************
 * @brief       Enable the selected ADC.
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @return		MID_StatusTypeDef
 *******************************************************************************
 */
static MID_StatusTypeDef ADC_Enable(ADC_HandleTypeDef* mADC)
{
    uint32_t tickstart = 0U; 
    
    /* Enable the ADC peripheral */
    __DRV_ADC_ENABLE(mADC);
    
    /* Get tick count */
    tickstart = MID_GetTick();
    
    /* Wait for ADC effectively enabled */
    while(1)
    {
      if((MID_GetTick() - tickstart) > ADC_ENABLE_TIMEOUT)
          break;
    }   
    
   
    /* Return MID status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Disable the selected ADC.
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note        Prerequisite condition to use this function: ADC conversions must be
 *              stopped to disable the ADC.        
 *******************************************************************************
 */
static MID_StatusTypeDef ADC_Disable(ADC_HandleTypeDef* mADC)
{
    // Mandatory stop ADC
    __DRV_ADC_DISABLE(mADC);      

    /* Return MID status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Stop ADC conversion.
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note        Prerequisite condition to use this function: ADC conversions must be
 *              stopped to disable the ADC.        
 *******************************************************************************
 */
static MID_StatusTypeDef ADC_ConversionStop(ADC_HandleTypeDef* mADC)
{
    /* 1. Hold ADC                                                */
    mADC->Instance->START.W |= ADC_START_HOLD_mask_w;
    
    /* 2.1 Change ADC conversion mode to ADC_ONESHOT
       2.2 Discontinue 
       2.3 Trigger START conversion switch to 'SW : ADC0_START'
       2.4 Disable Trigger edge 
    */
    mADC->Instance->START.W &= ~(ADC_START_CONV_MDS_mask_w  | 
                                 ADC_START_TRG_CONT_mask_w  | 
                                 ADC_START_START_SEL_mask_w | 
                                 ADC_START_TRG_SEL_mask_w   );
        
    /* 3. Continue ADC convert                                    */
    mADC->Instance->START.W &= ~ADC_START_HOLD_mask_w;

    /* Return MID status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       DMA transfer complete callback. 
 * @param[in]   hDMA : pointer to a ADC_HandleTypeDef
 * @return      MID_StatusTypeDef
 *******************************************************************************
 */
static void ADC_DMAConvCplt(DMA_HandleTypeDef *hDMA)
{
    /* Retrieve ADC handle corresponding to current DMA handle */
    ADC_HandleTypeDef* mADC = ( ADC_HandleTypeDef* )((DMA_HandleTypeDef* )hDMA)->Parent;

    /* Disable ADC end of single conversion interrupt on group regular */
    /* Note: Overrun interrupt was enabled with EOC interrupt in        */
    /* MID_Start_IT(), but is not disabled here because can be used     */
    /* by overrun IRQ process below.                                    */
    __DRV_ADC_DISABLE_IT(mADC, (ADC_IT_E1CNV | ADC_IT_ESCNV));

    /* Set ADC state */
    mADC->State = MID_ADC_STATE_READY;

    /* Conversion complete callback */
    MID_ADC_ConvCpltCallback(mADC); 

}


/**
 *******************************************************************************
 * @brief       DMA half transfer complete callback. 
 * @param[in]   hDMA pointer to DMA handle.
 * @return      None
 *******************************************************************************
 */
static void ADC_DMAHalfConvCplt(DMA_HandleTypeDef *hDMA)
{
    /* Retrieve ADC handle corresponding to current DMA handle */
    ADC_HandleTypeDef* mADC = ( ADC_HandleTypeDef* )((DMA_HandleTypeDef* )hDMA)->Parent;
    
    /* Half conversion callback */
    MID_ADC_ConvHalfCpltCallback(mADC); 
}

/**
 *******************************************************************************
 * @brief		TM DMA error call back.
 * @param[in]   hDMA pointer to DMA handle.
 * @return      None
 *******************************************************************************
 */
static void ADC_DMAError(DMA_HandleTypeDef *hDMA)  
{
    /* Retrieve ADC handle corresponding to current DMA handle */
    ADC_HandleTypeDef* mADC = ( ADC_HandleTypeDef* )((DMA_HandleTypeDef* )hDMA)->Parent;
    
    /* Set ADC state */
    mADC->State = MID_ADC_STATE_ERROR_DMA;
    
    /* Set ADC error code to DMA error */
    mADC->ErrorCode = MID_ADC_ERROR_DMA;
    
    /* Error callback */
    MID_ADC_ErrorCallback(mADC); 
     
}    


#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wfloat-equal"
#endif
/**
 *******************************************************************************
 * @brief	    Enable/Disable PGA calibration state
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @return		MID_StatusTypeDef
 *******************************************************************************
 */
MID_StatusTypeDef MID_ADC_PGACalibration_Start(ADC_HandleTypeDef* mADC)
{
#if defined(MG32_3RD)
    uint8_t OFFT_PGA_MaxIDX, OFFT_PGA_MinIDX, OFFT_PGA_ActIDX, old_PGA_Gain, TargetIDX;
    uint8_t COMPCNT;
    uint32_t i, j;
    double ResultADC;
    double Disable_PGA_Value, MinCompareValue = 0x80000000; 
    uint32_t rADC_MSK, rADC_START, rADC_CR0, rADC_CR1;
    uint32_t rSUM0, rSUM1, rSUM2;
    
    double PGA_Gain_V[] = {
        1.000, 1.012, 1.024, 1.037, 1.050, 1.063, 1.077, 1.091, 1.105, 1.120, 
        1.135, 1.151, 1.167, 1.183, 1.200, 1.217, 1.235, 1.254, 1.273, 1.292,
        1.313, 1.333, 1.355, 1.377, 1.400, 1.424, 1.448, 1.474, 1.500, 1.527,
        1.556, 1.585, 1.615, 1.647, 1.680, 1.714, 1.750, 1.787, 1.826, 1.867,
        1.909, 1.953, 2.000, 2.049, 2.100, 2.154, 2.211, 2.270, 2.333, 2.400,
        2.471, 2.545, 2.625, 2.710, 2.800, 2.897, 3.000, 3.111, 3.231, 3.360,
        3.500, 3.652, 3.818, 4.000 
    };

    // RESAVE
    rADC_MSK = ADC0->MSK.W;
    rADC_START = ADC0->START.W;
    rADC_CR0 = ADC0->CR0.W;    
    rADC_CR1 = ADC0->CR1.W;    
    rSUM0 = ADC0->SUM0.W;
    rSUM1 = ADC0->SUM1.W;
    rSUM2 = ADC0->SUM2.W;
     
    // check VBUF state
    if (PW->CR0.MBIT.IVR_EN == CLR)
    {
        // Enable VBUF + select (0)
        MID_UnProtectModuleReg(PWmodule);
        __DRV_PW_ENANLE_VBUF();
        MID_ProtectModuleReg(PWmodule);
        
        // delay a time (2020.02.17) - VBUF settling time
        for(i=0;i<65536;i++);
    }
        
    // reset SUM_NUM & window detect
    mADC->Instance->CR1.W &= ~(ADC_CR1_SUM_NUM_mask_w | ADC_CR1_WIND_EN_enable_w);

    // config ADC mode for calibration 
    mADC->Instance->CR0.W = ADC_CR0_RES_SEL_12_bit_w | ADC_CR0_EN_enable_w;
    
    mADC->Instance->START.W = ADC_START_CONV_MDS_one_w | ADC_START_TRG_SEL_disable_w | \
                              ADC_START_START_SEL_sw_w;
    
    // ------------------------------------------------------------------------
    // Dsiable PGA & disable PGAOUT
    __DRV_ADC_PGA_DISABLE(mADC);
    
    // Sample ADC conversion without PGA
    old_PGA_Gain = mADC->Instance->GAIN.H[1] & ADC_GAIN_OFFT_PGA_mask_h1;
    __DRV_ADC_CHSELR_CHANNEL(mADC, ADC_CHANNEL_27);
    {
        for (j=0;j<10;j++)
        {
            mADC->Instance->START.W |= ADC_START_START_mask_w;          // MID_ADC_Start(mADC);
            while (__DRV_ADC_GET_FLAG(mADC,ADC_FLAG_E1CNV) == 0x00);
            __DRV_ADC_CLEAR_FLAG(mADC,(ADC_FLAG_E1CNV | ADC_FLAG_ESMP));
        }
        
        for (j=0,ResultADC=0;j<10;j++)
        {
            mADC->Instance->START.W |= ADC_START_START_mask_w;          // MID_ADC_Start(mADC);
            while (__DRV_ADC_GET_FLAG(mADC,ADC_FLAG_E1CNV) == 0x00);
            __DRV_ADC_CLEAR_FLAG(mADC,(ADC_FLAG_E1CNV | ADC_FLAG_ESMP));
            ResultADC += MID_ADC_GetValue(mADC);
        }
        ResultADC = ResultADC / 10;
        Disable_PGA_Value = ((double) ResultADC) * ((double) (PGA_Gain_V[old_PGA_Gain]));
    }
    
    // ------------------------------------------------------------------------
    // Enable PGA
    __DRV_ADC_PGA_ENABLE(mADC);
    
    // Initial OFFT of PGA
    COMPCNT = 0;
    OFFT_PGA_MinIDX = 0;
    OFFT_PGA_MaxIDX = 63;
    TargetIDX = OFFT_PGA_ActIDX = OFFT_PGA_MaxIDX >> 1;
    
    // ------------------------------------------------------------------------
    // Compare ADC x PGA 
    while(COMPCNT < 6 )
    {
        // set ADC_GAIN_OFFT
        __DRV_ADC_PGA_UPDATE_OFFT(mADC, OFFT_PGA_ActIDX);
        
        // Average ADC conversion
        for (i=0, ResultADC=0 ; i<10; i++)
        {
            mADC->Instance->START.W |= ADC_START_START_mask_w;          // MID_ADC_Start(mADC);
            while (__DRV_ADC_GET_FLAG(mADC,ADC_FLAG_E1CNV) == 0x00);
            __DRV_ADC_CLEAR_FLAG(mADC,(ADC_FLAG_E1CNV | ADC_FLAG_ESMP));
            ResultADC += MID_ADC_GetValue(mADC);
        }
        ResultADC = ResultADC / 10;
                
        // --------------------------------------------------------------------
        // exit condition
        if (ResultADC == Disable_PGA_Value)
        {
            TargetIDX = OFFT_PGA_ActIDX;
            break;
        }
        
        // --------------------------------------------------------------------
        // compare minimum MinCompareValue then get target index
        if (ResultADC >= Disable_PGA_Value)
        {
            if ((ResultADC - Disable_PGA_Value) < MinCompareValue)
            {
                TargetIDX = OFFT_PGA_ActIDX;
                MinCompareValue = (Disable_PGA_Value - ResultADC);
            }
        }
        else if ((Disable_PGA_Value - ResultADC) < MinCompareValue)
        {
            TargetIDX = OFFT_PGA_ActIDX;
            MinCompareValue = (Disable_PGA_Value - ResultADC);
        }
        
        // --------------------------------------------------------------------
        // check ADC_CONV data - Update OFFT_PGA_MaxIDX, OFFT_PGA_MinIDX & OFFT_PGA_ActIDX
        if (ResultADC >= Disable_PGA_Value)
        {
            OFFT_PGA_MaxIDX = OFFT_PGA_ActIDX;
            OFFT_PGA_ActIDX = (OFFT_PGA_MinIDX + OFFT_PGA_MaxIDX) >> 1;
        }
        else 
        {
            OFFT_PGA_MinIDX = OFFT_PGA_ActIDX;
            OFFT_PGA_ActIDX = (OFFT_PGA_MinIDX + OFFT_PGA_MaxIDX) >> 1;
        }
        
        COMPCNT ++;
    }

    // ------------------------------------------------------------------------
    // set ADC_GAIN_OFFT by TargetIDX
    __DRV_ADC_PGA_UPDATE_OFFT(mADC, TargetIDX);


    // restore
    ADC0->MSK.W = rADC_MSK;
    ADC0->START.W = rADC_START;
    ADC0->CR0.W = rADC_CR0;    
    ADC0->CR1.W = rADC_CR1;    
    ADC0->SUM0.W = rSUM0;
    ADC0->SUM1.W = rSUM1;
    ADC0->SUM2.W = rSUM2;
    
    return MID_SUCCESS;
    
#elif defined(MG32_1ST) || defined(MG32_2ND)
    uint8_t VOD_x, VOD_0, VOD_63;
    uint8_t PGAOFFT;
    
    // enable PGA calibration state
    mADC->Instance->CAL.W |= (ADC_CAL_CAL_POFFT_enable_w);
    
    //
    PGAOFFT = 32;
    mADC->Instance->GAIN.B[2] = (PGAOFFT);
    mADC->Instance->ANA.W |= (ADC_ANA_PGA_EN_enable_w);
    
    // read VOD
    VOD_x = ADC0->STA.MBIT.POF;
    
    mADC->Instance->GAIN.B[2] = (0);
    VOD_0 = ADC0->STA.MBIT.POF;
    
    mADC->Instance->GAIN.B[2] = (63);
    VOD_63 = ADC0->STA.MBIT.POF;
    
    if((VOD_0 == VOD_x) && (VOD_63 == VOD_x))
    {
        mADC->Instance->GAIN.B[2] = (PGAOFFT);
        mADC->Instance->CAL.W &= ~(ADC_CAL_CAL_POFFT_enable_w);
        return MID_FAILURE;
    }
    
    // read VOD 
    if (ADC0->STA.MBIT.POF != VOD_x)
    {
        PGAOFFT  = 33;
        mADC->Instance->GAIN.B[2] = (PGAOFFT);
        
        while (1)
        {
            if (ADC0->STA.MBIT.POF != VOD_x) break;
            PGAOFFT ++;
            mADC->Instance->GAIN.B[2] = (PGAOFFT);
        }
    } else 
    {
        PGAOFFT  = 31;
        mADC->Instance->GAIN.B[2] = (PGAOFFT);
        
        while (1)
        {
            if (ADC0->STA.MBIT.POF != VOD_x) break;
            PGAOFFT --;
            mADC->Instance->GAIN.B[2] = (PGAOFFT);
        }
        
    }
        
    // Disable calibration 
    mADC->Instance->CAL.W &= ~(ADC_CAL_CAL_POFFT_enable_w);
    return MID_SUCCESS;
#else
    (void)mADC;
    return MID_FAILURE;
#endif

}
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
#pragma clang diagnostic pop
#endif



/**
 *******************************************************************************
 * @brief       ADC start Calibration routine.
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @param[in]   VRMV : initial VRM (middle)
 * @return		MID_StatusTypeDef
 *******************************************************************************
 */
MID_StatusTypeDef MID_ADC_VRMCalibration_Start(ADC_HandleTypeDef* mADC, uint8_t VRMV)
{
#if defined(MG32_1ST)
    volatile int32_t VRPV, VRNV, VRM;
    int32_t CaliV;
    uint8_t i;
    
    MID_UnProtectModuleReg(CFGmodule); 

    VRM = VRMV;
    
    // middle trim
    while (1)
    {
        __DRV_ADC_CHSELR_CHANNEL(mADC, ADC_CHANNEL_16);
        for (i=0, VRNV=0 ; i<10; i++)
        {
            mADC->Instance->START.W |= ADC_START_START_mask_w;          // MID_ADC_Start(mADC);
            while (__DRV_ADC_GET_FLAG(mADC,ADC_FLAG_E1CNV) == 0x00);
            __DRV_ADC_CLEAR_FLAG(mADC,(ADC_FLAG_E1CNV | ADC_FLAG_ESMP));
        }
        for (i=0, VRNV=0 ; i<10; i++)
        {
            mADC->Instance->START.W |= ADC_START_START_mask_w;          // MID_ADC_Start(mADC);
            while (__DRV_ADC_GET_FLAG(mADC,ADC_FLAG_E1CNV) == 0x00);
            __DRV_ADC_CLEAR_FLAG(mADC,(ADC_FLAG_E1CNV | ADC_FLAG_ESMP));
            VRNV += MID_ADC_GetValue(mADC);
        }
        VRNV = VRNV / 10;
        
        //-------------------------------------------------
        __DRV_ADC_CHSELR_CHANNEL(mADC, ADC_CHANNEL_17);
        for (i=0, VRNV=0 ; i<10; i++)
        {
            mADC->Instance->START.W |= ADC_START_START_mask_w;          // MID_ADC_Start(mADC);
            while (__DRV_ADC_GET_FLAG(mADC,ADC_FLAG_E1CNV) == 0x00);
            __DRV_ADC_CLEAR_FLAG(mADC,(ADC_FLAG_E1CNV | ADC_FLAG_ESMP));
        }
        for (i=0, VRPV=0 ; i<10; i++)
        {
            mADC->Instance->START.W |= ADC_START_START_mask_w;          // MID_ADC_Start(mADC);
            while (__DRV_ADC_GET_FLAG(mADC,ADC_FLAG_E1CNV) == 0x00);
            __DRV_ADC_CLEAR_FLAG(mADC,(ADC_FLAG_E1CNV | ADC_FLAG_ESMP));
            VRPV += MID_ADC_GetValue(mADC);
        }
        VRPV = VRPV / 10;
        
        
        //-------------------------------------------------
        CaliV = (VRNV + VRPV) >> 1;
        CaliV = CaliV - 2048;
        CaliV = CaliV / 2;
        VRM = VRM + CaliV;
        __DRV_CFG_WRITE_ADCREFMIDDLE((uint8_t) VRM);
                        
        if (CaliV == 1) break;
        if (CaliV == 0) break;
        if (CaliV == -1) break;
        
    }
        
    // 
    VRM = VRM + 1;
    __DRV_CFG_WRITE_ADCREFMIDDLE((uint8_t) VRM);
#else
    (void)mADC;
    (void)VRMV;
#endif
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       ADC start Calibration routine.
 * @param[in]   mADC : pointer to a ADC_HandleTypeDef
 * @return		MID_StatusTypeDef
 *******************************************************************************
 */
MID_StatusTypeDef MID_ADC_Calibration_Start(ADC_HandleTypeDef* mADC)
{
#if defined(MG32_3RD)
    int16_t ADC_CONV = 0;
    uint8_t i, OFFT_ADC_MinIDX, ADC_CALI_Complete = 0;
    uint32_t rADC_MSK, rADC_START, rADC_CR0, rADC_CR1;
    uint32_t rSUM0, rSUM1, rSUM2;
   
    // RESAVE
    rADC_MSK = mADC->Instance->MSK.W;
    rADC_START = mADC->Instance->START.W;
    rADC_CR0 = mADC->Instance->CR0.W;    
    rADC_CR1 = mADC->Instance->CR1.W;    
    rSUM0 = mADC->Instance->SUM0.W;
    rSUM1 = mADC->Instance->SUM1.W;
    rSUM2 = mADC->Instance->SUM2.W;
   
    // reset SUM_NUM & window detect
    mADC->Instance->CR1.W &= ~(ADC_CR1_SUM_NUM_mask_w | ADC_CR1_WIND_EN_enable_w);

    // config ADC mode for calibration
    mADC->Instance->CR0.W = ADC_CR0_RES_SEL_12_bit_w | ADC_CR0_EN_enable_w;
   
    mADC->Instance->START.W = ADC_START_CONV_MDS_one_w | ADC_START_TRG_SEL_disable_w | \
                              ADC_START_START_SEL_sw_w;
   
    // start calibration
    // ------------------------------------------------------------------------
    // start calibration - Offset issue
    // ------------------------------------------------------------------------
    mADC->Instance->START.W &= ~(ADC_START_CH_MUX_mask_w | ADC_START_CH_SEL_mask_w);
    mADC->Instance->START.W = ADC_CHANNEL_16; // select internal channel VSSA
   
    OFFT_ADC_MinIDX = 0;

    // ------------------------------------------------------------------------
    // 1. Scan minimum index when ADC sample not equal '0'
    // ------------------------------------------------------------------------
    while(1)
    {
        // set ADC_GAIN_OFFT
        mADC->Instance->GAIN.W &= ~(ADC_GAIN_OFFT_ADC_mask_w);
        mADC->Instance->GAIN.W |= (uint32_t) (OFFT_ADC_MinIDX << ADC_GAIN_OFFT_ADC_shift_w);
       
        // sample internal VSS
        mADC->Instance->START.W |= ADC_START_START_mask_w;          // MID_ADC_Start(mADC);
        while (__DRV_ADC_GET_FLAG(mADC,ADC_FLAG_E1CNV) == 0x00);
        __DRV_ADC_CLEAR_FLAG(mADC,(ADC_FLAG_E1CNV | ADC_FLAG_ESMP));
        ADC_CONV += MID_ADC_GetValue(mADC);
       
       
        // check ADC_CONV data (search ADC_CONV==1 or 2)  
        if (ADC_CONV == 0)
        {
            OFFT_ADC_MinIDX ++;
        }
        else
        {
            if(OFFT_ADC_MinIDX < 2)     // No trimming range in this issue
            {
                OFFT_ADC_MinIDX = 0;
                break;        
            }
            OFFT_ADC_MinIDX -= 2;
            break;
        }
       
        //
        if (OFFT_ADC_MinIDX == 31) break;
       
    }
   
   
    // ------------------------------------------------------------------------
    // 2. average ADC conversion data -> decide the optimum
    // ------------------------------------------------------------------------
    while(1)
    {
        // set ADC_GAIN_OFFT
        ADC0->GAIN.MBIT.OFFT_ADC = OFFT_ADC_MinIDX;
               
        // Average ADC conversion
       
       
        for (i=0, ADC_CONV=0 ; i<8; i++)
        {
            mADC->Instance->START.W |= ADC_START_START_mask_w;          // MID_ADC_Start(mADC);
            while (__DRV_ADC_GET_FLAG(mADC,ADC_FLAG_E1CNV) == 0x00);
            __DRV_ADC_CLEAR_FLAG(mADC,(ADC_FLAG_E1CNV | ADC_FLAG_ESMP));
            ADC_CONV += MID_ADC_GetValue(mADC);
       
        }        
       
        // check ADC_CONV data (search ADC_CONV==1 or 2)  
        if (ADC_CONV == 0)
        {
            OFFT_ADC_MinIDX ++;
        }
        else if (ADC_CONV < 8)
        {
            break;
        }
        else
        {
            if(OFFT_ADC_MinIDX == 0)
            {
                ADC_CALI_Complete = 0;
                break;         // No trimming range in this issue
            }
            OFFT_ADC_MinIDX --;         // make sure -> ADC can convert '0'
            ADC_CALI_Complete = 1;
            break;
        }
        //
        if (OFFT_ADC_MinIDX == 31)
        {
            ADC_CALI_Complete = 0;
            break;
        }
       
    }
   
    // desire ADC_GAIN_OFFT
    mADC->Instance->GAIN.W &= ~(ADC_GAIN_OFFT_ADC_mask_w);
    mADC->Instance->GAIN.W |= (uint32_t) (OFFT_ADC_MinIDX << ADC_GAIN_OFFT_ADC_shift_w);
   
   
    // restore
    mADC->Instance->MSK.W = rADC_MSK;
    mADC->Instance->START.W = rADC_START;
    mADC->Instance->CR0.W = rADC_CR0;    
    mADC->Instance->CR1.W = rADC_CR1;    
    mADC->Instance->SUM0.W = rSUM0;
    mADC->Instance->SUM1.W = rSUM1;
    mADC->Instance->SUM2.W = rSUM2;

    if (ADC_CALI_Complete == 1)
        return MID_SUCCESS;
    else
        return MID_FAILURE;
   
#elif defined(MG32_1ST)
    int16_t VRP, VRN, VRM;
    int32_t VRPV, VRNV;
    uint8_t i;
    uint32_t rADC_MSK, rADC_START, rADC_CR0, rADC_CR1;
    uint32_t rSUM0, rSUM1, rSUM2;
    
    // RESAVE
    rADC_MSK = mADC->Instance->MSK.W;
    rADC_START = mADC->Instance->START.W;
    rADC_CR0 = mADC->Instance->CR0.W;    
    rADC_CR1 = mADC->Instance->CR1.W;    
    rSUM0 = mADC->Instance->SUM0.W;
    rSUM1 = mADC->Instance->SUM1.W;
    rSUM2 = mADC->Instance->SUM2.W;
    
    // reset SUM_NUM & window detect
    mADC->Instance->CR1.W &= ~(ADC_CR1_SUM_NUM_mask_w | ADC_CR1_WIND_EN_enable_w);

    // config ADC mode for calibration 
    mADC->Instance->CR0.W = ADC_CR0_CODE_FMT_unsigned_w | ADC_CR0_RES_SEL_12_bit_w | \
                            ADC_CR0_MDS_single_end_w | ADC_CR0_EN_enable_w;
    
    mADC->Instance->START.W = ADC_START_CONV_MDS_one_w | ADC_START_TRG_SEL_disable_w | \
                              ADC_START_START_SEL_sw_w;
    
    // start calibration
    MID_UnProtectModuleReg(CFGmodule); 
    
    VRP = 32;
    VRN = 32;
    VRM = 32;
    __DRV_CFG_WRITE_ADCREFTOP((uint8_t) VRP);
    __DRV_CFG_WRITE_ADCREFMIDDLE((uint8_t) VRM);
    __DRV_CFG_WRITE_ADCREFBOTTOM((uint8_t) VRN);
    
    
    VRN = 0;
    while(1)
    {
        __DRV_CFG_WRITE_ADCREFBOTTOM((uint8_t) VRN);
        __DRV_ADC_CHSELR_CHANNEL(mADC, ADC_CHANNEL_16);

        for (i=0, VRNV=0 ; i<10; i++)
        {
            mADC->Instance->START.W |= ADC_START_START_mask_w;          // MID_ADC_Start(mADC);
            while (__DRV_ADC_GET_FLAG(mADC,ADC_FLAG_E1CNV) == 0x00);
            __DRV_ADC_CLEAR_FLAG(mADC,(ADC_FLAG_E1CNV | ADC_FLAG_ESMP));
        }
        for (i=0, VRNV=0 ; i<10; i++)
        {
            mADC->Instance->START.W |= ADC_START_START_mask_w;          // MID_ADC_Start(mADC);
            while (__DRV_ADC_GET_FLAG(mADC,ADC_FLAG_E1CNV) == 0x00);
            __DRV_ADC_CLEAR_FLAG(mADC,(ADC_FLAG_E1CNV | ADC_FLAG_ESMP));
            if( MID_ADC_GetValue(mADC) == 0x0000) break;
            VRNV += MID_ADC_GetValue(mADC);
        }
        VRNV = VRNV / 10;

        
        if (VRNV > 0) VRN ++;
        if (VRNV == 0) 
        {
            VRN -= 1; 
            break;
        }
        if (VRN == 64) 
        {
            VRN = 32;
            break;
        }
    }
    
    __DRV_CFG_WRITE_ADCREFMIDDLE(32);
    __DRV_CFG_WRITE_ADCREFBOTTOM(32);
    VRP = 0;
    while(1)
    {
        __DRV_CFG_WRITE_ADCREFTOP((uint8_t) VRP);
        
        __DRV_ADC_CHSELR_CHANNEL(mADC, ADC_CHANNEL_17);
        for (i=0, VRPV=0 ; i<10; i++)
        {
            mADC->Instance->START.W |= ADC_START_START_mask_w;          // MID_ADC_Start(mADC);
            while (__DRV_ADC_GET_FLAG(mADC,ADC_FLAG_E1CNV) == 0x00);
            __DRV_ADC_CLEAR_FLAG(mADC,(ADC_FLAG_E1CNV | ADC_FLAG_ESMP));
        }
        for (i=0, VRPV=0 ; i<10; i++)
        {
            mADC->Instance->START.W |= ADC_START_START_mask_w;          // MID_ADC_Start(mADC);
            while (__DRV_ADC_GET_FLAG(mADC,ADC_FLAG_E1CNV) == 0x00);
            __DRV_ADC_CLEAR_FLAG(mADC,(ADC_FLAG_E1CNV | ADC_FLAG_ESMP));
            if( MID_ADC_GetValue(mADC)  < 4095) break;
            VRPV += MID_ADC_GetValue(mADC);
        }
        VRPV = VRPV / 10;
        
        if (VRPV > 4094) 
            VRP ++;
        else 
        {
            VRP --;
            break;
        }
        
        if (VRP == 64) 
        {
            VRP = 32;
            break;
        }
        
    }
    
    __DRV_CFG_WRITE_ADCREFTOP((uint8_t) VRP);
    __DRV_CFG_WRITE_ADCREFMIDDLE((uint8_t) VRM);
    __DRV_CFG_WRITE_ADCREFBOTTOM((uint8_t) VRN);
    
    VRM = (__DRV_CFG_READ_ADCREFTOP() + __DRV_CFG_READ_ADCREFBOTTOM()) / 2;
    __DRV_CFG_WRITE_ADCREFMIDDLE((uint8_t) VRM);
    
//    // middle trim
    MID_ADC_VRMCalibration_Start(mADC, (uint8_t) VRM);
            
    MID_ProtectModuleReg(CFGmodule);   
    
    mADC->Instance->MSK.W = rADC_MSK;
    mADC->Instance->START.W = rADC_START;
    mADC->Instance->CR0.W = rADC_CR0;    
    mADC->Instance->CR1.W = rADC_CR1;    
    mADC->Instance->SUM0.W = rSUM0;
    mADC->Instance->SUM1.W = rSUM1;
    mADC->Instance->SUM2.W = rSUM2;
    
    return MID_SUCCESS;
#elif defined(MG32_2ND)
    (void)mADC;
    return MID_SUCCESS;    
#else
    (void)mADC;
    return MID_SUCCESS;    
#endif    
}
///@}


