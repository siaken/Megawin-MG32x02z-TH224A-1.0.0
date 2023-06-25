/**
 ******************************************************************************
 *
 * @file        MG32x02z_ADC_DRV.c
 *
 * @brief       This file provides firmware functions to manage the following 
 *              functionalities of the ADC peripheral:
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.22
 * @date        2022/01/25
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


/* Includes ------------------------------------------------------------------*/
#include "MG32x02z_ADC_DRV.h"


/* Wizard menu ---------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* External vairables --------------------------------------------------------*/

/**
 * @brief  	simple define
 *
 */ 

/**
 * @name	Deinitial ADC to default condition
 *   		
 */ 
///@{  
/**
 *******************************************************************************
 * @brief       Deinitializes the ADCx peripheral registers to their default reset 
 *			    values.
 * @details     Reset ADCx to default configuration
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return		No
 * @note 
 * @par         Example
 * @code
    ADC_DeInit(ADC0);
 * @endcode
 *******************************************************************************
 */
void ADC_DeInit(ADC_Struct *ADCx)
{
    ADCx->INT.W = 0x00000000;
    ADCx->CLK.W = 0x00000000;
    ADCx->CR0.W = 0x00000000;
    ADCx->CR1.W = 0x00000000;
    ADCx->MSK.W = 0x00000000;
    ADCx->START.W = 0x00001000;
#if defined(MG32_1ST)	
    ADCx->ANA.W = 0x00008000;
#endif
#if defined(MG32_2ND)
    ADCx->ANA.W = 0x00000300;
#endif
#if defined(MG32_3RD)
    ADCx->ANA.W = 0x00000200;
#endif
    // CAL
#if defined(MG32_3RD)
    ADCx->GAIN.W = (0x00000000 | (ADCx->GAIN.W & 0x1F000000));
#else
    ADCx->GAIN.W = 0x00000000;
#endif
    ADCx->SUM0.W = 0x00E00000;
    ADCx->SUM1.W = 0x00E00000;
    ADCx->SUM2.W = 0x00E00000;
    // TCAL
    ADCx->DAT0.B[2] = 0xC0;
    
    ADCx->STA.W = 0xFFFFFFFF;
}
///@}


/**
 * @name	Initializes the ADC Unit peripheral according to the specified\
 *          parameters in the ADC_InitTypeDef.
 *   		
 */ 
///@{  
/**
 *******************************************************************************
 * @brief       Fills each ADC_InitTypeDef member with its default value.
 * @param[in]   ADC_BaseInitStruct : pointer to a ADC_InitTypeDef
 *        	    structure which will be initialized.
 * @return		No
 * @note 
 * @par         Example
 * @code
    ADC_InitTypeDef ADC_BaseInitStruct;

    ADC_BaseStructure_Init(&ADC_BaseInitStruct);
 * @endcode
 *******************************************************************************
 */
 void ADC_BaseStructure_Init(ADC_InitTypeDef* ADC_BaseInitStruct)
{
    // config ADC clock 
    ADC_BaseInitStruct->ADCMainClockSelect = ADC_CKADC;
        ADC_BaseInitStruct->ADC_IntCK_Div = ADC_IntDIV16;   // for internal clock divider
        ADC_BaseInitStruct->ADC_CKPLL_Div = ADC_PLLDIV6;    // only for clock select PLL     
    
    // ADC data alignment mode (Right or Left)
    ADC_BaseInitStruct->ADC_DataAlign = ADC_RightJustified;
    
    // ADC conversion resolution 10 or 12 bit
    ADC_BaseInitStruct->ADC_ResolutionSel = ADC_12BitData;
    
    // ADC overwritten data or keep data
    ADC_BaseInitStruct->ADC_DataOverrunEvent = ADC_DataOverWritten;
}

/**
 *******************************************************************************
 * @brief       Initializes the ADC peripheral according to 
 *			    the specified parameters in the ADC_BaseInitStruct.
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in]   ADC_BaseInitStruct : pointer to a ADC_InitTypeDef
 *        	    structure that contains the configuration information for
 *        	    the specified ADC peripheral.
 * @return		No
 * @note 
 * @par         Example
 * @code
    ADC_InitTypeDef ADC_BaseInitStruct;
 
    ADC_Base_Init(ADC0, &ADC_BaseInitStruct);
 * @endcode
 *******************************************************************************
 */
void ADC_Base_Init(ADC_Struct* ADCx, ADC_InitTypeDef* ADC_BaseInitStruct)
{
    // ------------------------------------------------------------------------
    // config clock
    ADC_ClockSource_Select(ADCx, ADC_BaseInitStruct->ADCMainClockSelect);
        ADC_SetInternalClockDivider(ADCx, ADC_BaseInitStruct->ADC_IntCK_Div);
        ADC_SetPLLClockDivider(ADCx, ADC_BaseInitStruct->ADC_CKPLL_Div);
    
    // ADC data alignment
    ADC_DataAlignment_Select(ADCx, ADC_BaseInitStruct->ADC_DataAlign);
    
    // ADC conversion resolution
    ADC_DataResolution_Select(ADCx, ADC_BaseInitStruct->ADC_ResolutionSel);
    
    // ADC data overwritten or keep mode
    ADC_DataOverrunMode_Select(ADCx, ADC_BaseInitStruct->ADC_DataOverrunEvent);
    
    // ------------------------------------------------------------------------
    // Select ADC conversion time with 24 ADCK (Apply MG32F02A032/A128/U128/A064/U064/V032)
    #if defined(MG32_3RD) || defined(MG32_4TH)
        ADC_SetConversionTime(ADC0, ADC_FastCONV);
    #endif
    
    // ------------------------------------------------------------------------
    // ADC operation bias (Apply MG32F02A032/A128/U128/A064/U064/V032)
    #if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
        ADC_SetOperationCurrent(ADCx, ADC_BIAS_LVL3);
    #endif
    
    // ------------------------------------------------------------------------
    // ADC discharge function in ADC sample and hold state (Apply MG32F02V032)
    #if defined(MG32_4TH)
        ADC_Dischrge_Cmd(ADCx, ENABLE);
    #endif
    
    // ------------------------------------------------------------------------
    // ADC sample and hold clock phase state (Apply MG32F02A128/U128/A064/U064/V032)
    #if defined(MG32_3RD) || defined(MG32_4TH)
        ADC_SampleClockPhase_Select(ADCx, ADC_CK_PHASE2);
    #endif
    
}
///@}



/** 
 * @name		Config ADC clock 
 *
 */ 
///@{  
/**
 *******************************************************************************
 * @brief       Configures the ADCx counter direction.
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	PLLClockDIV : specifies the PLL clock divider
 *  @arg\b	    ADC_PLLDIV2 : divided by 2
 *  @arg\b	    ADC_PLLDIV4 : divided by 4
 *  @arg\b	    ADC_PLLDIV5 : divided by 5
 *  @arg\b	    ADC_PLLDIV6 : divided by 6
 * @return		No
 * @note 
 * @par         Example
 * @code
    ADC_SetPLLClockDivider(ADC0, ADC_PLLDIV6);
 * @endcode
 *******************************************************************************
 */
void ADC_SetPLLClockDivider(ADC_Struct* ADCx, ADC_PLLClockDivDef PLLClockDIV)
{
	ADCx->CLK.MBIT.CK_DIV2 = PLLClockDIV;
}

/**
 *******************************************************************************
 * @brief	    Configures ADC clock source
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCClockSrc : specifies the Main Counter direction to be used
 *  @arg\b	    ADC_CKADC : ADC clock from CK_ADC
 *  @arg\b	    ADC_CKPLL : ADC clock from PLL 
 *  @arg\b	    ADC_TM00TRGO : ADC clock from TM00 TRGO
 *  @arg\b	    ADC_TM01TRGO : ADC clock from TM01 TRGO
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_ClockSource_Select(ADC0, ADC_CKADC);
 * @endcode
 *******************************************************************************
 */
void ADC_ClockSource_Select(ADC_Struct* ADCx, ADC_ClockSourceDef ADCClockSrc)
{
	ADCx->CLK.MBIT.CK_SEL2 = ADCClockSrc;
}
/**
 *******************************************************************************
 * @brief	    Configures ADC internal clock input divider.
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	INTClockSrc : specifies the ADC inteernal clock divider
 *  @arg\b	    ADC_IntDIV1 : divided by 1
 *	@arg\b	    ADC_IntDIV2 : divided by 2
 *  @arg\b	    ADC_IntDIV4 : divided by 4
 *	@arg\b	    ADC_IntDIV16 : divided by 16
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetInternalClockDivider(ADC0, ADC_IntDIV2);
 * @endcode
 *******************************************************************************
 */
void ADC_SetInternalClockDivider(ADC_Struct* ADCx, ADC_INTClockDivDef INTClockSrc)
{
	ADCx->CLK.MBIT.CK_DIV = INTClockSrc;
}
#if defined(MG32_3RD) || defined(MG32_4TH)
/**
 *******************************************************************************
 * @brief	    Configures ADC conversion time.
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	CONVTime : specifies the ADC inteernal clock divider
 *  @arg\b	    ADC_FastCONV : Conversion time ~24 ADC clocks.
 *	@arg\b	    ADC_NormalCONV : Conversion time ~30 ADC clocks.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetConversionTime(ADC0, ADC_FastCONV);
 * @endcode
 *******************************************************************************
 */
void ADC_SetConversionTime(ADC_Struct* ADCx, ADC_ConversionTimeDef CONVTime)
{
	ADCx->ANA.MBIT.CONV_TIME = CONVTime;
}
#endif
///@}



/**
 * @name	Config window detect function routine
 *   		
 */ 
///@{ 
// Config window detect function routine
/**
 *******************************************************************************
 * @brief	    Configures lower threshold of window detect function
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	LThreshold: setting lower threshold
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetLowerThreshold(ADC0, 100);
 * @endcode
 *******************************************************************************
 */
void ADC_SetLowerThreshold(ADC_Struct* ADCx, int16_t LThreshold)
{
    ADCx->WINDTH.H[0] = (uint16_t) LThreshold;
}
/**
 *******************************************************************************
 * @brief	    Configures higher threshold of window detect function
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	HThreshold: setting lower threshold
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetHigherThreshold(ADC0, 1000);
 * @endcode
 *******************************************************************************
 */
void ADC_SetHigherThreshold(ADC_Struct* ADCx, int16_t HThreshold)
{
    ADCx->WINDTH.H[1] = (uint16_t) HThreshold;
}
/**
 *******************************************************************************
 * @brief	    Configures window detect function apply channel
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	WINDApply : specifies the ADC inteernal clock divider
 *  @arg\b	    ADC_WINDSingle : window detect function only apply single channel
 *	@arg\b	    ADC_WINDAll : window detect function apply all channel
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_WindowDetectRange_Select(ADC0, ADC_WINDSingle);
 * @endcode
 *******************************************************************************
 */
void ADC_WindowDetectRange_Select(ADC_Struct* ADCx, ADC_WindowDetectApplyDef WINDApply)
{
    ADCx->CR1.MBIT.WIND_MDS = WINDApply;
}
/**
 *******************************************************************************
 * @brief	    Enable/Disable window detect function 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of window detect function
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_WindowDetect_Cmd(ADC0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_WindowDetect_Cmd(ADC_Struct* ADCx, FunctionalState NewState)
{
    ADCx->CR1.MBIT.WIND_EN = NewState;
}
/**
 *******************************************************************************
 * @brief	    Select ADC Out property
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCOutSel: select window detect result
 *  @arg\b	    ADC_WDL_Event : WDLF - outside low
 *	@arg\b	    ADC_WDI_Event : WDIF - inside
 *  @arg\b	    ADC_WDH_Event : WDHF - outside high
 * @return 	    none
 * @note        
 * @par         Example
 * @code
    ADC_Output_Select(ADC0, ADC_WDI_Event);
 * @endcode
 *******************************************************************************
 */
void ADC_Output_Select(ADC_Struct* ADCx,ADC_OutputDef ADCOutSel)
{
    ADCx->CR1.MBIT.OUT_SEL = ADCOutSel;
}
///@}


#if defined(MG32_1ST) || defined(MG32_2ND) || defined(MG32_3RD)
/**
 * @name	config PGA property 
 *   		
 */ 
///@{ 
// config PGA property 
/**
 *******************************************************************************
 * @brief	    Enable/Disable PGA function 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of PGA
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_PGA_Cmd(ADC0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_PGA_Cmd(ADC_Struct* ADCx, FunctionalState NewState)
{
    ADCx->ANA.MBIT.PGA_EN = NewState;
}
/**
 *******************************************************************************
 * @brief	    Config PGA gain
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	PGAGain: setting gain x1~x4
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetPGAGain(ADC0, 10);
 * @endcode
 *******************************************************************************
 */
void ADC_SetPGAGain(ADC_Struct* ADCx, uint8_t PGAGain)
{
    ADCx->GAIN.MBIT.GAIN_PGA = PGAGain;
}

/**
 *******************************************************************************
 * @brief	    St PGA offset
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	PGAOFFT: 0~63
 * @return 	    none
 *******************************************************************************
 */
void ADC_SetPGAOffset(ADC_Struct* ADCx, uint8_t PGAOFFT)
{
    ADCx->GAIN.MBIT.OFFT_PGA = PGAOFFT;
}
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wfloat-equal"
#endif
/**
 *******************************************************************************
 * @brief	    Enable/Disable PGA calibration state
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of PGA calibration ON/OFF
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_PGAOffsetCalibration_Cmd(ADC0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_PGAOffsetCalibration_Cmd(ADC_Struct* ADCx, FunctionalState NewState)
{
#if defined(MG32_1ST) || defined(MG32_2ND)
    uint8_t VOD_x, VOD_0, VOD_63;
    uint8_t PGAOFFT;
    
    if (NewState == DISABLE)
        return;
    
    // enable PGA calibration state
    ADCx->CAL.MBIT.CAL_POFFT = 1;
    
    //
    PGAOFFT = 32;
    ADC_SetPGAOffset(ADCx, PGAOFFT);
    ADC_PGA_Cmd(ADCx, ENABLE);
    
    // read VOD
    VOD_x = ADCx->STA.MBIT.POF;
    
    ADC_SetPGAOffset(ADCx, 0);
    VOD_0 = ADCx->STA.MBIT.POF;
    
    ADC_SetPGAOffset(ADCx, 63);
    VOD_63 = ADCx->STA.MBIT.POF;
    
    if((VOD_0 == VOD_x) && (VOD_63 == VOD_x))
    {
        ADC_SetPGAOffset(ADCx, PGAOFFT);
        ADCx->CAL.MBIT.CAL_POFFT = 0;
        return;
    }
    
    // read VOD 
    if (ADCx->STA.MBIT.POF != VOD_x)
    {
        PGAOFFT  = 33;
        ADC_SetPGAOffset(ADCx, PGAOFFT);
        
        while (1)
        {
            if (ADCx->STA.MBIT.POF != VOD_x) break;
            PGAOFFT ++;
            ADC_SetPGAOffset(ADCx, PGAOFFT);
        }
    } else 
    {
        PGAOFFT  = 31;
        ADC_SetPGAOffset(ADCx, PGAOFFT);
        
        while (1)
        {
            if (ADCx->STA.MBIT.POF != VOD_x) break;
            PGAOFFT --;
            ADC_SetPGAOffset(ADCx, PGAOFFT);
        }
        
    }
        
    // Disable calibration 
    ADCx->CAL.MBIT.CAL_POFFT = 0;
#elif defined(MG32_3RD)
    uint8_t OFFT_PGA_MaxIDX, OFFT_PGA_MinIDX, OFFT_PGA_ActIDX, old_PGA_Gain, TargetIDX;
    uint8_t COMPCNT;
    uint32_t i, j;
    uint16_t ResultADC;
    double Disable_PGA_Value, MinCompareValue; 
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

    if (NewState == DISABLE)
        return;
    
    // RESAVE
    rADC_MSK = ADCx->MSK.W;
    rADC_START = ADCx->START.W;
    rADC_CR0 = ADCx->CR0.W;    
    rADC_CR1 = ADCx->CR1.W;    
    rSUM0 = ADCx->SUM0.W;
    rSUM1 = ADCx->SUM1.W;
    rSUM2 = ADCx->SUM2.W;
     
    // ------------------------------------------------------------------------
    // check VBUF state
    if (PW->CR0.MBIT.IVR_EN == CLR)
    {
        // Enable VBUF + select (0)
        UnProtectModuleReg(PWprotect);
        PW_VoltageBuffer(ENABLE);
        ProtectModuleReg(PWprotect);
        
        // delay a time (2020.02.17) - VBUF settling time
        for(i=0;i<65536;i++);
    }
        
    // config ADC mode for PGA calibration 
    ADC_SetSumNumber(ADCx, 0);                  // Disable ADC accumulation function
    ADC_WindowDetect_Cmd(ADCx, DISABLE);        // Disable Window detect function
    ADC_ConversionMode_Select(ADCx, ADCMode);   // Change ADC to One-Shot mode
    ADC_TriggerSource_Select(ADCx, ADC_START);  // Trigger mode 
    ADC_SetOutputCodeFormat(ADCx, ADC_UnsignedFormat);
    ADC_DataResolution_Select(ADCx, ADC_12BitData);
    
    // ------------------------------------------------------------------------
    // Dsiable PGA & disable PGAOUT
    ADC_PGA_Cmd(ADCx, DISABLE);
    
    // Sample ADC conversion without PGA
    old_PGA_Gain = ADCx->GAIN.MBIT.GAIN_PGA;
    ADC_InternalChannel_Select(ADCx, ADC_INT_VPG);
    ADC_SetExtendSampling(ADCx, 255);
    //
    {
        // abandon 10 conversion data
        for (j=0;j<10;j++)
        {
            ADC_SoftwareConversion_Cmd(ADCx, ENABLE);        
            while (ADC_GetSingleFlagStatus (ADCx, ADC_E1CNVF) == DRV_UnHappened);
            ADC_ClearFlag(ADCx,ADC_E1CNVF);
        }
        
        // Average
        for (j=0,ResultADC=0;j<10;j++)
        {
            ADC_SoftwareConversion_Cmd(ADCx, ENABLE);        
            while (ADC_GetSingleFlagStatus (ADCx, ADC_E1CNVF) == DRV_UnHappened);
            ADC_ClearFlag(ADCx,ADC_E1CNVF);
            ResultADC += ADC_GetDAT0Data(ADCx);
        }
        ResultADC = ResultADC / 10;
        
        // Disable_PGA_Value = Average * PGA gain
        Disable_PGA_Value = ((double) ResultADC) * PGA_Gain_V[old_PGA_Gain];
    }
    
    // ------------------------------------------------------------------------
    // Enable PGA
    ADC_PGA_Cmd(ADCx, ENABLE);
    
    // Initial OFFT of PGA
    COMPCNT = 0;
    OFFT_PGA_MinIDX = 0;
    OFFT_PGA_MaxIDX = 31;
    TargetIDX = OFFT_PGA_ActIDX = OFFT_PGA_MaxIDX >> 1;
    MinCompareValue = 65535;
    
    // ------------------------------------------------------------------------
    // Compare ADC x PGA 
    while(COMPCNT < 6 )
    {
        // set ADC_GAIN_OFFT
        ADC_SetPGAOffset(ADCx, OFFT_PGA_ActIDX);
        
        // Average ADC conversion
        for (i=0, ResultADC=0 ; i<10; i++)
        {
            ADC_SoftwareConversion_Cmd(ADCx, ENABLE);
            while (ADC_GetSingleFlagStatus (ADCx,ADC_E1CNVF) == DRV_UnHappened);
            ADC_ClearFlag(ADCx, (ADC_E1CNVF | ADC_ESMPF));
            ResultADC += ADC_GetDAT0Data(ADCx);
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
    ADC_SetPGAOffset(ADCx, TargetIDX);
    // restore
    ADCx->MSK.W = rADC_MSK;
    ADCx->START.W = rADC_START;
    ADCx->CR0.W = rADC_CR0;    
    ADCx->CR1.W = rADC_CR1;    
    ADCx->SUM0.W = rSUM0;
    ADCx->SUM1.W = rSUM1;
    ADCx->SUM2.W = rSUM2;
            
#endif
}
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
#pragma clang diagnostic pop
#endif
///@}
#endif


/**
 * @name	ADC Calibration
 *   		
 */ 
///@{ 
#if defined(MG32_1ST)	
/******************************************************************************
 * @brief       Calibrate offset of middle
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return      none
 * @note        no release
 *****************************************************************************/
void ADC_VRMCalibration(ADC_Struct* ADCx,uint8_t VRMV) 
{
    int32_t VRPV, VRNV, VRM;
    int32_t CaliV;
    uint8_t i;
    
    UnProtectModuleReg(CFGprotect); 

    VRM = VRMV;
    
    // middle trim
    while (1)
    {
        ADC_InternalChannel_Select(ADCx, ADC_INT_VSSA);
        for (i=0, VRNV=0 ; i<10; i++)
        {
            ADC_SoftwareConversion_Cmd(ADCx, ENABLE);
            while (ADC_GetSingleFlagStatus (ADCx,ADC_E1CNVF) == DRV_UnHappened);
            ADC_ClearFlag(ADCx, (ADC_E1CNVF | ADC_ESMPF));
        }
        for (i=0, VRNV=0 ; i<10; i++)
        {
            ADC_SoftwareConversion_Cmd(ADCx, ENABLE);
            while (ADC_GetSingleFlagStatus (ADCx,ADC_E1CNVF) == DRV_UnHappened);
            ADC_ClearFlag(ADCx, (ADC_E1CNVF | ADC_ESMPF));
            VRNV += ADC_GetDAT0Data(ADCx);
        }
        VRNV = VRNV / 10;
        
        //-------------------------------------------------
        ADC_InternalChannel_Select(ADCx, ADC_INT_IVREF);
        for (i=0, VRNV=0 ; i<10; i++)
        {
            ADC_SoftwareConversion_Cmd(ADCx, ENABLE);
            while (ADC_GetSingleFlagStatus (ADCx,ADC_E1CNVF) == DRV_UnHappened);
            ADC_ClearFlag(ADCx, (ADC_E1CNVF | ADC_ESMPF));
        }
        for (i=0, VRPV=0 ; i<10; i++)
        {
            ADC_SoftwareConversion_Cmd(ADCx, ENABLE);
            while (ADC_GetSingleFlagStatus (ADCx,ADC_E1CNVF) == DRV_UnHappened);
            ADC_ClearFlag(ADCx, (ADC_E1CNVF | ADC_ESMPF));
            VRPV += ADC_GetDAT0Data(ADCx);
        }
        VRPV = VRPV / 10;
        
        
        //-------------------------------------------------
        CaliV = (VRNV + VRPV) >> 1;
        CaliV = CaliV - 2048;
        CaliV = CaliV / 2;
        VRM = VRM + CaliV;
        CFG_SetADC0RefMiddle((uint8_t) VRM);
        
                
        if (CaliV == 1) break;
        if (CaliV == 0) break;
        if (CaliV == -1) break;
        
        
    }
        
    // 2018.08.29 test
    VRM = VRM + 1;
    CFG_SetADC0RefMiddle((uint8_t) VRM);
}
#endif        
    
/**
 *******************************************************************************
 * @brief	    Enable/Disable ADC calibration state
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of ADC calibration 
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_StartCalibration(ADC0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_StartCalibration(ADC_Struct* ADCx, FunctionalState NewState)
{
#if defined(MG32_1ST)
    int16_t VRP, VRN, VRM;
    int32_t VRPV, VRNV;
    uint8_t i;
    uint32_t rADC_MSK, rADC_START, rADC_CR0, rADC_CR1;
    uint32_t rSUM0, rSUM1, rSUM2;
    
    //
    if (NewState == DISABLE)
        return;
   
    // RESAVE
    rADC_MSK = ADCx->MSK.W;
    rADC_START = ADCx->START.W;
    rADC_CR0 = ADCx->CR0.W;   
    rADC_CR1 = ADCx->CR1.W;   
    rSUM0 = ADCx->SUM0.W;
    rSUM1 = ADCx->SUM1.W;
    rSUM2 = ADCx->SUM2.W;
    
    // reset SUM_NUM & window detect
    ADCx->CR1.W &= ~(ADC_CR1_SUM_NUM_mask_w | ADC_CR1_WIND_EN_enable_w);

    // config ADC mode for calibration 
    ADC_ConversionMode_Select(ADCx, ADCMode);
    ADC_TriggerSource_Select(ADCx, ADC_START);
    ADC_SingleDifferentMode_Select(ADCx, ADC_SingleMode);
    ADC_SetOutputCodeFormat(ADCx, ADC_UnsignedFormat);
    ADC_DataResolution_Select(ADCx, ADC_12BitData);
    
    // start calibration
    UnProtectModuleReg(CFGprotect); 
    
    VRP = 32;
    VRN = 32;
    VRM = 32;
    CFG_SetADC0RefTop((uint8_t) VRP);
    CFG_SetADC0RefMiddle((uint8_t) VRM);
    CFG_SetADC0RefBottom((uint8_t) VRN);
    
    
    VRN = 0;
    while(1)
    {
        CFG_SetADC0RefBottom((uint8_t) VRN);
        ADC_ChannelMUX_Select(ADCx, ADC_InternalChannel);
        ADC_InternalChannel_Select(ADCx, ADC_INT_VSSA);
        for (i=0, VRNV=0 ; i<10; i++)
        {
            ADC_SoftwareConversion_Cmd(ADCx, ENABLE);
            while (ADC_GetSingleFlagStatus (ADCx,ADC_E1CNVF) == DRV_UnHappened);
            ADC_ClearFlag(ADCx, (ADC_E1CNVF | ADC_ESMPF));
        }
        for (i=0, VRNV=0 ; i<10; i++)
        {
            ADC_SoftwareConversion_Cmd(ADCx, ENABLE);
            while (ADC_GetSingleFlagStatus (ADCx,ADC_E1CNVF) == DRV_UnHappened);
            ADC_ClearFlag(ADCx, (ADC_E1CNVF | ADC_ESMPF));
            if( ADC_GetDAT0Data(ADCx) == 0x0000) break;
            VRNV += ADC_GetDAT0Data(ADCx);
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
    
    CFG_SetADC0RefMiddle(32);
    CFG_SetADC0RefBottom(32);
    VRP = 0;
    while(1)
    {
        CFG_SetADC0RefTop((uint8_t) VRP);
        
        ADC_InternalChannel_Select(ADCx, ADC_INT_IVREF);
        for (i=0, VRPV=0 ; i<10; i++)
        {
            ADC_SoftwareConversion_Cmd(ADCx, ENABLE);
            while (ADC_GetSingleFlagStatus (ADCx,ADC_E1CNVF) == DRV_UnHappened);
            ADC_ClearFlag(ADCx, (ADC_E1CNVF | ADC_ESMPF));
        }
        for (i=0, VRPV=0 ; i<10; i++)
        {
            ADC_SoftwareConversion_Cmd(ADCx, ENABLE);
            while (ADC_GetSingleFlagStatus (ADCx,ADC_E1CNVF) == DRV_UnHappened);
            ADC_ClearFlag(ADCx, (ADC_E1CNVF | ADC_ESMPF));
            if( ADC_GetDAT0Data(ADCx) < 4095) break;
            VRPV += ADC_GetDAT0Data(ADCx);
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
    
    CFG_SetADC0RefTop((uint8_t) VRP);
    CFG_SetADC0RefMiddle((uint8_t) VRM);
    CFG_SetADC0RefBottom((uint8_t) VRN);
    
    
    VRM = (CFG_GetADC0RefTop() + CFG_GetADC0RefBottom()) / 2;
    CFG_SetADC0RefMiddle((uint8_t) VRM);
    
//    // middle trim
    ADC_VRMCalibration(ADCx, (uint8_t) VRM);
            
    ProtectModuleReg(CFGprotect);   
    
    ADCx->MSK.W = rADC_MSK;
    ADCx->START.W = rADC_START;
    ADCx->CR0.W = rADC_CR0;    
    ADCx->CR1.W = rADC_CR1;    
    ADCx->SUM0.W = rSUM0;
    ADCx->SUM1.W = rSUM1;
    ADCx->SUM2.W = rSUM2;
#elif defined(MG32_2ND)
    //
    if (NewState == DISABLE)
        return;
    
    // Clear ADC STA flag
    ADC_ClearFlag(ADCx, 0xFFFFFFFF);
    return;
    
#elif defined(MG32_3RD) || defined(MG32_4TH)
    int16_t ADC_CONV;
    uint8_t i, OFFT_ADC_MinIDX;
    uint32_t rADC_MSK, rADC_START, rADC_CR0, rADC_CR1;
    uint32_t rSUM0, rSUM1, rSUM2;
   
    //
    if (NewState == DISABLE)
        return;
   
    // RESAVE
    rADC_MSK = ADCx->MSK.W;
    rADC_START = ADCx->START.W;
    rADC_CR0 = ADCx->CR0.W;  
    rADC_CR1 = ADCx->CR1.W;  
    rSUM0 = ADCx->SUM0.W;
    rSUM1 = ADCx->SUM1.W;
    rSUM2 = ADCx->SUM2.W;
   
    // reset SUM_NUM & window detect
    ADCx->CR1.W &= ~(ADC_CR1_SUM_NUM_mask_w | ADC_CR1_WIND_EN_enable_w);

    // config ADC mode for calibration
    ADC_ConversionMode_Select(ADCx, ADCMode);
    ADC_TriggerSource_Select(ADCx, ADC_START);
    ADC_SingleDifferentMode_Select(ADCx, ADC_SingleMode);
    ADC_SetOutputCodeFormat(ADCx, ADC_UnsignedFormat);
    ADC_DataResolution_Select(ADCx, ADC_12BitData);
   
    // ------------------------------------------------------------------------
    // start calibration - Offset issue
    // ------------------------------------------------------------------------
    ADC_InternalChannel_Select(ADCx, ADC_INT_VSSA); // select internal channel VSSA
   
    OFFT_ADC_MinIDX = 0;

    // ------------------------------------------------------------------------
    // 1. Scan minimum index when ADC sample not equal '0'
    // ------------------------------------------------------------------------
    while(1)
    {
        // set ADC_GAIN_OFFT
        ADCx->GAIN.MBIT.OFFT_ADC = OFFT_ADC_MinIDX;

        // sample internal VSS
        ADC_SoftwareConversion_Cmd(ADCx, ENABLE);
        while (ADC_GetSingleFlagStatus (ADCx,ADC_E1CNVF) == DRV_UnHappened);
        ADC_ClearFlag(ADCx, (ADC_E1CNVF | ADC_ESMPF));
        ADC_CONV = ADC_GetDAT0Data(ADCx);
        
       
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
        ADCx->GAIN.MBIT.OFFT_ADC = OFFT_ADC_MinIDX;
               
        // Average ADC conversion
        
        
        for (i=0, ADC_CONV=0 ; i<8; i++)
        {
            ADC_SoftwareConversion_Cmd(ADCx, ENABLE);
            while (ADC_GetSingleFlagStatus (ADCx,ADC_E1CNVF) == DRV_UnHappened);
            ADC_ClearFlag(ADCx, (ADC_E1CNVF | ADC_ESMPF));
            ADC_CONV += ADC_GetDAT0Data(ADCx);
        
       
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
            if(OFFT_ADC_MinIDX == 0) break;         // No trimming range in this issue
            OFFT_ADC_MinIDX --;         // make sure -> ADC can convert '0'
            break;
        }
        //
        if (OFFT_ADC_MinIDX > 31) break;
       
    }
   
    // desire ADC_GAIN_OFFT
    ADCx->GAIN.MBIT.OFFT_ADC = OFFT_ADC_MinIDX;
    

    // restore
    ADCx->MSK.W = rADC_MSK;
    ADCx->START.W = rADC_START;
    ADCx->CR0.W = rADC_CR0;    
    ADCx->CR1.W = rADC_CR1;    
    ADCx->SUM0.W = rSUM0;
    ADCx->SUM1.W = rSUM1;
    ADCx->SUM2.W = rSUM2;
#endif   
}
///@}



/**
 * @name	ADC Auxrity config
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    Enable or Disable ADC macro
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of ADC
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_Cmd(ADC0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_Cmd(ADC_Struct* ADCx, FunctionalState NewState)
{
    ADCx->CR0.MBIT.EN = NewState;
}

/**
 *******************************************************************************
 * @brief	    Enable or Disable DMA access ADC result
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of ADC
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_DMA_Cmd(ADC0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_DMA_Cmd(ADC_Struct* ADCx, FunctionalState NewState)
{
    ADCx->CR0.MBIT.DMA_EN = NewState;
}

#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
/**
 *******************************************************************************
 * @brief	    Set ADC data size for DMA transmission 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	DMADataSize: select dats size for DMA transmission
 *  @arg\b	    ADC_DMA_32bit : ADC will transfer ADC0_DAT0 for DMA transmission
 *	@arg\b	    ADC_DMA_16bit : ADC will transfer the bit[15:0] of ADC0_DAT0 for 
 *                              DMA transmission
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_DMADataSize_Select(ADC0, ADC_DMA_16bit);
 * @endcode
 *******************************************************************************
 */
void ADC_DMADataSize_Select(ADC_Struct* ADCx, ADC_DMADataSizeDef DMADataSize)
{
    ADCx->CR0.MBIT.DMA_DSIZE = DMADataSize;
}


/**
 *******************************************************************************
 * @brief	    Set ADC assert E1CNVF during DMA transmission
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	DMAMaskFlagDef: Select flag state during DMA access
 *  @arg\b	    ADC_Mask_E1CNVF : E1CNVF flag will be masked after ADC conversion
 *                                end during DMA access.
 *	@arg\b	    ADC_Assert_E1CNVF : E1CNVF flag asserted mode select during DMA access
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_DMAMaskFlag_Select(ADC0, ADC_Assert_E1CNVF);
 * @endcode
 *******************************************************************************
 */
void ADC_DMAMaskFlag_Select(ADC_Struct* ADCx, ADC_DMAMaskE1CNVFDef DMAMaskFlagDef)
{
    ADCx->CR0.MBIT.DMA_MDS = DMAMaskFlagDef;
}


/**
 *******************************************************************************
 * @brief	    Get ADC next conversion channel
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return 	    Next Channel seletion
 * @note 
 * @par         Example
 * @code
    tmp = ADC_GetNextConversionChannel(ADC0);
 * @endcode
 *******************************************************************************
 */
uint8_t ADC_GetNextConversionChannel(ADC_Struct* ADCx)
{
    return ADCx->STA.MBIT.CNV_CH;
}
#endif

#if defined(MG32_1ST) || defined(MG32_3RD) || defined(MG32_4TH)		
/**
 *******************************************************************************
 * @brief	    Config ADC into idle when stop conversion
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of ADC AutoOff (save power)
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_AutoOff_Cmd(ADC0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_AutoOff_Cmd(ADC_Struct* ADCx, FunctionalState NewState)
{
    ADCx->CR0.MBIT.AUTOFF_EN = NewState;
}
#endif

#if defined(MG32_3RD) || defined(MG32_4TH)
/**
 *******************************************************************************
 * @brief	    Setup startup count value within AUTOFF_EN=1.
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCSCNTime: This value is 0~15. 
 *              This means that the stabilization time is 1 ~ 16T.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetStartupTime(ADC0, 6);
 * @endcode
 *******************************************************************************
 */
void ADC_SetStartupTime(ADC_Struct* ADCx, uint16_t ADCSCNTime)
{
    ADCx->CLK.MBIT.SCNT = (uint8_t) ADCSCNTime;
}

/**
 *******************************************************************************
 * @brief	    Config startup count clock divider within AUTOFF_EN=1.
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCSCNDIV: specifies the SCNT clock divider
 *  @arg\b	    ADC_SCNTIntDIV1 : divided by 1
 *  @arg\b	    ADC_SCNTIntDIV4 : divided by 4
 *  @arg\b	    ADC_SCNTIntDIV16 : divided by 16
 *  @arg\b	    ADC_SCNTIntDIV32 : divided by 32
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetStartupDivider(ADC0, ADC_SCNTIntDIV4);
 * @endcode
 *******************************************************************************
 */
void ADC_SetStartupDivider(ADC_Struct* ADCx, ADC_SCNTClockDivDef ADCSCNDIV)
{
    ADCx->CLK.MBIT.CK_SDIV = ADCSCNDIV;
}
#endif

/**
 *******************************************************************************
 * @brief	    ADC had readed data then start the next 
 *              conversion (for low frequency MCU)
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of ADC conversion wait mode
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_WaitDataReadOut(ADC0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_WaitDataReadOut(ADC_Struct* ADCx, FunctionalState NewState)
{
    ADCx->CR0.MBIT.WAIT_EN = NewState;
}

/**
 *******************************************************************************
 * @brief	    Extend sampling time for ADC conversion 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCSampleTime: 0~255 (1T~256T)
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetExtendSampling(ADC0, 6);
 * @endcode
 *******************************************************************************
 */
void ADC_SetExtendSampling(ADC_Struct* ADCx, uint8_t ADCSampleTime)
{
    ADCx->CR0.MBIT.SMP_SEL = ADCSampleTime;
}

#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
/**
 *******************************************************************************
 * @brief	    Set ADC operation bias current. 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCBiasSel: ADC operation bias current control
 *  @arg\b	    ADC_BIAS_LVL0 : LVL0, Lowest current. 
 *	@arg\b	    ADC_BIAS_LVL1 : LVL1, Lower current. 
 *	@arg\b	    ADC_BIAS_LVL2 : LVL2, Higher current. 
 *	@arg\b	    ADC_BIAS_LVL3 : LVL3, Highest current.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetOperationCurrent(ADC0, ADC_BIAS_LVL3);
 * @endcode
 *******************************************************************************
 */
void ADC_SetOperationCurrent(ADC_Struct* ADCx, ADC_OperationBiasDef ADCBiasSel)
{
    ADCx->ANA.MBIT.BIAS = ADCBiasSel;
}
#endif

#if defined(MG32_4TH)
/**
 *******************************************************************************
 * @brief	    Enable/Disable discharge before ADC sample and hold. 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of ADC discharge mode
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_Dischrge_Cmd(ADC0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_Dischrge_Cmd(ADC_Struct* ADCx, FunctionalState NewState)
{
    ADCx->ANA.MBIT.DISCHR_EN = NewState;
}
#endif

#if defined(MG32_3RD) || defined(MG32_4TH)
/**
 *******************************************************************************
 * @brief	    Config ADC clock phase issue when ADC sample state. 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	CKPHSSel: new state of ADC sample clock.
 *  @arg\b	    ADC_CK_PHASE0 : ADC_CK_PHASE0 : Bypass. 
 *	@arg\b	    ADC_CK_PHASE1 : ADC_CK_PHASE1 : One step delay. 
 *	@arg\b	    ADC_CK_PHASE2 : ADC_CK_PHASE2 : Clock invert. 
 *	@arg\b	    ADC_CK_PHASE3 : ADC_CK_PHASE3 : Clock invert with one step delay. 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SampleClockPhase_Select(ADC0, ADC_CK_PHASE2);
 * @endcode
 *******************************************************************************
 */
void ADC_SampleClockPhase_Select(ADC_Struct* ADCx, ADC_SampleClockPhaseSel CKPHSSel)
{
    ADCx->CLK.MBIT.CK_DLY = CKPHSSel;
}
#endif
///@}




/**
 * @name	ADC Conversion mode configuration
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    Config ADC conversion mode
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCConvMode: select convertsion mode
 *  @arg\b	    ADCMode : One channel 
 *	@arg\b	    ADCContinueMode : One + Continue
 *	@arg\b	    ScanMode : Scan
 *	@arg\b	    ScanContinueMode : Scan + continue 
 *	@arg\b	    LoopMode : Loop
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_ConversionMode_Select(ADC0, ScanContinueMode);
 * @endcode
 *******************************************************************************
 */
void ADC_ConversionMode_Select(ADC_Struct* ADCx, ADC_ConversionModeDef ADCConvMode)
{
    switch(ADCConvMode)
    {
        case ADCMode:
            ADC_MainConversionMode_Select(ADCx, ADC_OneShot);
            ADC_ContinueMode_Cmd(ADCx, DISABLE);
            break;
        
        case ADCContinueMode:
            ADC_MainConversionMode_Select(ADCx, ADC_OneShot);
            ADC_ContinueMode_Cmd(ADCx, ENABLE);
            break;

        case ScanMode:
            ADC_MainConversionMode_Select(ADCx, ADC_Scan);
            ADC_ContinueMode_Cmd(ADCx, DISABLE);
            break;

        case ScanContinueMode:
            ADC_MainConversionMode_Select(ADCx, ADC_Scan);
            ADC_ContinueMode_Cmd(ADCx, ENABLE);
            break;

        case LoopMode:
            ADC_MainConversionMode_Select(ADCx, ADC_Loop);
            ADC_ContinueMode_Cmd(ADCx, DISABLE);
            break;

        /* -Wswitch-default: usual warning about switch with no default */
//        default:
//            break;
    }
            
}
/**
 *******************************************************************************
 * @brief	    Enable/Disable ADC countinue state
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of ADC continue mode
 *      	    This parameter can be: ENABLE or DISABLE.
 * @note        no release
 * @return 	    none
 *******************************************************************************
 */
void ADC_ContinueMode_Cmd(ADC_Struct* ADCx, FunctionalState NewState)
{
    ADCx->START.MBIT.TRG_CONT = NewState;
}
/**
 *******************************************************************************
 * @brief	    Hold ADC countinue mode
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: Hold conversion (En/Disable)
 *      	    This parameter can be: ENABLE or DISABLE.
 * @note        no release
 * @return 	    none
 *******************************************************************************
 */
void ADC_HoldConversion_Cmd(ADC_Struct* ADCx, FunctionalState NewState)
{
    ADCx->START.MBIT.HOLD = NewState;
}

/**
 *******************************************************************************
 * @brief	    Set ADC main conversion mode
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	MainCM: select main convertsion mode
 *  @arg\b	    ADC_OneShot : One shot 
 *	@arg\b	    ADC_Scan : scan mode
 *	@arg\b	    ADC_Loop : loop mode
 * @note        no release
 * @return 	    none
 *******************************************************************************
 */
void ADC_MainConversionMode_Select(ADC_Struct* ADCx, ADC_MainConversionModeDef MainCM)
{
    ADCx->START.MBIT.CONV_MDS = MainCM;
}
///@}





/**
 * @name	ADC trigger source for conversion
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    Config ADC trigger source for conversion
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCTrgSel: select convertsion trigger source
 *  @arg\b	    ADC_START : SW setting to convert
 *	@arg\b	    ADC_TM00_TRGO : TM00 trigger out to convert 
 *	@arg\b	    ADC_TRGPin : External ADC pin trigger to convert
 *	@arg\b	    ADC_CMP0Out : comparator0 output to convert
 *	@arg\b	    ADC_CMP1Out : comparator1 output to convert
 *	@arg\b	    ADC_TM01_TRGO : TM01 trigger out to convert 
 *	@arg\b	    ADC_TM20_TRGO : TM20 trigger out to convert 
 *	@arg\b	    ADC_TM36_TRGO : TM36 trigger out to convert 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_TriggerSource_Select(ADC0, ADC_START);
 * @endcode
 *******************************************************************************
 */
void ADC_TriggerSource_Select(ADC_Struct* ADCx, ADC_TriggerSourceDef ADCTrgSel)
{
    ADCx->START.MBIT.START_SEL = ADCTrgSel;
}

/**
 *******************************************************************************
 * @brief	    Software start ADC conversion
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of software trigger ADC conversion
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SoftwareConversion_Cmd(ADC0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_SoftwareConversion_Cmd(ADC_Struct* ADCx, FunctionalState NewState)
{
    ADCx->START.MBIT.START = NewState;
}

/**
 *******************************************************************************
 * @brief	    Config ADC trigger event (Disable/rising/falling/dual edge)
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCExtEdgeSel: select trigger edge event to convert
 *  @arg\b	    ADC_DisableTrg : disable to convert
 *	@arg\b	    ADC_AcceptRisingEdge : Rising edge trigger out to convert 
 *	@arg\b	    ADC_AcceptFallingEdge : Falling edge trigger out to convert
 *	@arg\b	    ADC_AcceptDualEdge : dual edge trigger out to convert
 * @return 	    none
 * @note        Apply ADC_TRGPin 
 * @par         Example
 * @code
    ADC_TriggerEdge_Select(ADC0, ADC_AcceptRisingEdge);
 * @endcode
 *******************************************************************************
 */
void ADC_TriggerEdge_Select(ADC_Struct* ADCx, ADC_TriggerEdgeDef ADCExtEdgeSel)
{
    ADCx->START.MBIT.TRG_SEL = ADCExtEdgeSel;
}
///@}




/**
 * @name	config conversion channel
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    Config ADC conversion channel MUX external 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ChannelSel: config channel for ADC channel input 
 *  @arg\b	    ADC_ExternalChannel : select external channel, AIN0~15
 *	@arg\b	    ADC_InternalChannel : select internal channel, ie. VSSA, IVREF...
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_ChannelMUX_Select(ADC0, ADC_ExternalChannel);
 * @endcode
 *******************************************************************************
 */
void ADC_ChannelMUX_Select(ADC_Struct* ADCx, ADC_ChannelMUX_Def ChannelSel)
{
    ADCx->START.MBIT.CH_SEL = ChannelSel;
}

/**
 *******************************************************************************
 * @brief	    Select channel for ADC conversion
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ExtCHSel: which external channel 
 *  @arg\b	    ADC_ExtAIN0 : select external channel AIN0
 *  @arg\b	    ADC_ExtAIN1 : select external channel AIN1
 *  @arg\b	    ADC_ExtAIN2 : select external channel AIN2
 *  @arg\b	    ADC_ExtAIN3 : select external channel AIN3
 *  @arg\b	    ADC_ExtAIN4 : select external channel AIN4 
 *  @arg\b	    ADC_ExtAIN5 : select external channel AIN5
 *  @arg\b	    ADC_ExtAIN6 : select external channel AIN6
 *  @arg\b	    ADC_ExtAIN7 : select external channel AIN7
 *  @arg\b	    ADC_ExtAIN8 : select external channel AIN8
 *  @arg\b	    ADC_ExtAIN9 : select external channel AIN9
 *  @arg\b	    ADC_ExtAIN10 : select external channel AIN10
 *  @arg\b	    ADC_ExtAIN11 : select external channel AIN11
 *  @arg\b	    ADC_ExtAIN12 : select external channel AIN12
 *  @arg\b	    ADC_ExtAIN13 : select external channel AIN13
 *  @arg\b	    ADC_ExtAIN14 : select external channel AIN14
 *  @arg\b	    ADC_ExtAIN15 : select external channel AIN15
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_ExternalChannel_Select(ADC0, ADC_ExtAIN3);
 * @endcode
 *******************************************************************************
 */
void ADC_ExternalChannel_Select(ADC_Struct* ADCx, ADC_ExtChannelDef ExtCHSel)
{
    ADCx->START.B[1] = ExtCHSel;
}

/**
 *******************************************************************************
 * @brief       Select channel for ADC conversion
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in]   IntCHSel: which internal channel 
 *  @arg\b      ADC_INT_VSSA : select internal channel VSSA
 *  @arg\b      ADC_INT_IVREF : select internal channel IVREF
 *  @arg\b      ADC_INT_VBUF : select internal channel VBUF
 *  @arg\b      ADC_INT_DACP0 : select internal channel DAC_P0
 * @return      none
 * @note 
 * @par         Example
 * @code
    ADC_InternalChannel_Select(ADC0, ADC_INT_IVREF);
 * @endcode
 *******************************************************************************
 */
void ADC_InternalChannel_Select(ADC_Struct* ADCx, ADC_IntChannelDef IntCHSel)
{
    ADCx->START.B[1] = IntCHSel;
}

/**
 *******************************************************************************
 * @brief       Enable/Disable channel in scan/loop mode
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in]   MSKChannelSel : AIN0, AIN1 ... AIN15
 * @param[in]   NewState: new state of ADC Mask channel
 *              This parameter can be: ENABLE or DISABLE.
 * @return      none
 * @note 
 * @par         Example
 * @code
    ADC_ScanLoopChannel_Enable(ADC0, (ADC_MskAIN4 | ADC_MskAIN11), ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_ScanLoopChannel_Enable(ADC_Struct* ADCx, uint16_t MSKChannelSel, FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        #if defined(MG32_2ND)
            ADCx->MSK.H[0] |= MSKChannelSel & 0xFF0F;
        #endif
        #if defined(MG32_1ST) || defined(MG32_3RD)
            ADCx->MSK.H[0] |= MSKChannelSel;
        #endif
        #if defined(MG32_4TH)
            ADCx->MSK.H[0] |= MSKChannelSel & 0x0F0F;
        #endif
    }
    else
        ADCx->MSK.H[0] &= ~MSKChannelSel;
}


#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
/**
 *******************************************************************************
 * @brief       Config ADC change channel MUX timing when in Scan/Loop mode.
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in]   ADC_ChangTimeing: ADC change channel MUX timing
 *  @arg\b      ADC_ChangeMUX_E1CNVF : Change channel MUX when E1CNVF happened.
 *  @arg\b      ADC_ChangeMUX_ESMPF : Change channel MUX when ESMPF happened.
 * @return      none
 * @note 
 * @par         Example
 * @code
    ADC_ChangeMUXTiming_Select(ADC0, ADC_ChangeMUX_E1CNVF);
 * @endcode
 *******************************************************************************
 */
void ADC_ChangeMUXTiming_Select(ADC_Struct* ADCx, ADC_ChangeTimingDef ADC_ChangTimeing)
{
    ADCx->CR0.MBIT.CH_CHG = ADC_ChangTimeing;
}
#endif
///@}


/**
 * @name    config ADC conversion type mode
 *
 */ 
///@{
/**
 *******************************************************************************
 * @brief	    Config ADC conversion type (Single or Different)
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADC_ConversionType: config ADC conversion type 
 *  @arg\b	    ADC_SingleMode : Single conversion mode
 *	@arg\b	    ADC_DifferentMode : Different conversion mode
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SingleDifferentMode_Select(ADC0, ADC_SingleMode);
 * @endcode
 *******************************************************************************
 */
void ADC_SingleDifferentMode_Select(ADC_Struct* ADCx, ADC_ConversionTypeDef ADC_ConversionType)
{
#if defined(MG32_1ST)
    ADCx->CR0.MBIT.MDS = ADC_ConversionType;
#else
    if (ADC_ConversionType == ADC_SingleMode)
        ADCx->CR0.B[0] |= 0;
#endif
}

///@}



/**
 * @name	Accumulator for ADC data
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    Config process mode for spike data 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCLimitMode: new process mode 
 *  @arg\b	    ADC_LimitNoOperation : No operation for spike ADC conversion data
 *	@arg\b	    ADC_LimitSkip : Skip for spike ADC conversion data
 *	@arg\b	    ADC_LimitClamp : Clamp for spike ADC conversion data
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetLimitFunction(ADC0, ADC_LimitSkip);
 * @endcode
 *******************************************************************************
 */
void ADC_SetLimitFunction(ADC_Struct* ADCx, ADC_LimitModeDef ADCLimitMode)
{
    ADCx->CR0.MBIT.LIM_MDS = ADCLimitMode;
}

/**
 *******************************************************************************
 * @brief	    Select channel for accumulation-0
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	Sum0ChannelSel : SAIN0 or SAIN1 ... SAIN15
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetSum0Channel(ADC0, SAIN3);
 * @endcode
 *******************************************************************************
 */
void ADC_SetSum0Channel(ADC_Struct* ADCx,uint8_t Sum0ChannelSel)
{
    ADCx->MSK.MBIT.SUM0_MUX = Sum0ChannelSel;
}
/**
 *******************************************************************************
 * @brief	    Select channel for accumulation-1
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	Sum1ChannelSel : SAIN0 or SAIN1 ... SAIN15
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetSum1Channel(ADC0, SAIN5);
 * @endcode
 *******************************************************************************
 */
void ADC_SetSum1Channel(ADC_Struct* ADCx,uint8_t Sum1ChannelSel)
{
    ADCx->MSK.MBIT.SUM1_MUX = Sum1ChannelSel;
}
/**
 *******************************************************************************
 * @brief	    Select channel for accumulation-2
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	Sum2ChannelSel : SAIN0 or SAIN1 ... SAIN15
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetSum2Channel(ADC0, SAIN8);
 * @endcode
 *******************************************************************************
 */
void ADC_SetSum2Channel(ADC_Struct* ADCx,uint8_t Sum2ChannelSel)
{
    ADCx->MSK.MBIT.SUM2_MUX = Sum2ChannelSel;
}

/**
 *******************************************************************************
 * @brief	    Config accumulate mode for single/all cahnnel data 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCSumChXDef: new accumulate mode for sum0/1/2
 *  @arg\b	    ADC_SumSpeciallyChannel : specify single channel
 *	@arg\b	    ADC_SumAllChannel : accumulate all conversion channel data
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SumChannelMode_Select(ADC0, ADC_SumSpeciallyChannel);
 * @endcode
 *******************************************************************************
 */
void ADC_SumChannelMode_Select(ADC_Struct* ADCx,ADC_SumChannelXDef ADCSumChXDef)
{
    ADCx->CR1.MBIT.SUM_MDS = ADCSumChXDef;
}

/**
 *******************************************************************************
 * @brief	    Select channel for accumulation-2
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCSumNumbers: ADC data sum accumulation data number (0~64)
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetSumNumber(ADC0, 32);
 * @endcode
 *******************************************************************************
 */
void ADC_SetSumNumber(ADC_Struct* ADCx, uint8_t ADCSumNumbers)
{
    ADCx->CR1.MBIT.SUM_NUM = ADCSumNumbers;
}

/**
 *******************************************************************************
 * @brief	    Config data sum overrun mode select 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCSumOW: overrun mode select
 *  @arg\b	    ADC_SumOverWritten : Overwritten by new data
 *	@arg\b	    ADC_SumKeep : Preserved old date 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SumOverrunMode_Select(ADC0, ADC_SumKeep);
 * @endcode
 *******************************************************************************
 */
void ADC_SumOverrunMode_Select(ADC_Struct* ADCx, ADC_SumDataOWDef ADCSumOW)
{
    ADCx->CR1.MBIT.SOVR_MDS = ADCSumOW;
}

/**
 *******************************************************************************
 * @brief	    Get sum0 status flag 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return 	    sum0 flag (OVRF/CF/OF)
 * @note 
 * @par         Example
 * @code
    tmp = ADC_GetSum0Flags(ADC0);
 * @endcode
 *******************************************************************************
 */
uint16_t ADC_GetSum0Flags(ADC_Struct* ADCx)
{
    return ADCx->SUM0.H[1];
}
/**
 *******************************************************************************
 * @brief	    Get sum1 status flag 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return 	    sum1 flag (OVRF/CF/OF)
 * @note 
 * @par         Example
 * @code
    tmp = ADC_GetSum1Flags(ADC0);
 * @endcode
 *******************************************************************************
 */
uint16_t ADC_GetSum1Flags(ADC_Struct* ADCx)
{
    return ADCx->SUM1.H[1];
}
/**
 *******************************************************************************
 * @brief	    Get sum2 status flag 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return 	    sum2 flag (OVRF/CF/OF)
 * @note 
 * @par         Example
 * @code
    tmp = ADC_GetSum2Flags(ADC0);
 * @endcode
 *******************************************************************************
 */
uint16_t ADC_GetSum2Flags(ADC_Struct* ADCx)
{
    return ADCx->SUM2.H[1];
}
/**
 *******************************************************************************
 * @brief	    Clear sum0 flag
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADC_SUMxFlag: interrupt source item
 *  @arg\b	    ADC_SUMxOVRF : ADC0 data sum-0,1,2 register overrun flag                  
 *  @arg\b	    ADC_SUMxCF : ADC0 data sum-0,1,2 accumulation complete flag             
 *  @arg\b	    ADC_SUMxOF : ADC0 data sum-0,1,2 accumulation overflow flag 
 *  @arg\b	    ADC_SUMxUF : ADC0 data sum-0,1,2 accumulation underflow flag 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_ClearSum0Flags(ADC0, ADC_SUMxCF);
 * @endcode
 *******************************************************************************
 */
void ADC_ClearSum0Flags(ADC_Struct* ADCx, uint8_t ADC_SUMxFlag)
{
    ADCx->SUM0.H[1] = ADC_SUMxFlag;
}
/**
 *******************************************************************************
 * @brief	    Clear sum1 flag
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADC_SUMxFlag: interrupt source item
 *  @arg\b	    ADC_SUMxOVRF : ADC0 data sum-0,1,2 register overrun flag                  
 *  @arg\b	    ADC_SUMxCF : ADC0 data sum-0,1,2 accumulation complete flag             
 *  @arg\b	    ADC_SUMxOF : ADC0 data sum-0,1,2 accumulation overflow flag 
 *  @arg\b	    ADC_SUMxUF : ADC0 data sum-0,1,2 accumulation underflow flag 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_ClearSum1Flags(ADC0, ADC_SUMxOF);
 * @endcode
 *******************************************************************************
 */
void ADC_ClearSum1Flags(ADC_Struct* ADCx, uint8_t ADC_SUMxFlag)
{
    ADCx->SUM1.H[1] = ADC_SUMxFlag;
}
/**
 *******************************************************************************
 * @brief	    Clear sum2 flag
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADC_SUMxFlag: interrupt source item
 *  @arg\b	    ADC_SUMxOVRF : ADC0 data sum-0,1,2 register overrun flag                  
 *  @arg\b	    ADC_SUMxCF : ADC0 data sum-0,1,2 accumulation complete flag             
 *  @arg\b	    ADC_SUMxOF : ADC0 data sum-0,1,2 accumulation overflow flag 
 *  @arg\b	    ADC_SUMxUF : ADC0 data sum-0,1,2 accumulation underflow flag 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_ClearSum2Flags(ADC0, ADC_SUMxUF);
 * @endcode
 *******************************************************************************
 */
void ADC_ClearSum2Flags(ADC_Struct* ADCx, uint8_t ADC_SUMxFlag)
{
    ADCx->SUM2.H[1] = ADC_SUMxFlag;
}
/**
 *******************************************************************************
 * @brief	    Get sum0 data 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return 	    sum0 data
 * @note 
 * @par         Example
 * @code
    tmp = ADC_GetSum0Data(ADC0);
 * @endcode
 *******************************************************************************
 */
int16_t ADC_GetSum0Data(ADC_Struct* ADCx)
{
    return (int16_t) ADCx->SUM0.H[0];
}
/**
 *******************************************************************************
 * @brief	    Get sum1 data
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return 	    sum1 data
 * @note 
 * @par         Example
 * @code
    tmp = ADC_GetSum1Data(ADC0);
 * @endcode
 *******************************************************************************
 */
int16_t ADC_GetSum1Data(ADC_Struct* ADCx)
{
    return (int16_t) ADCx->SUM1.H[0];
}
/**
 *******************************************************************************
 * @brief	    Get sum2 data
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return 	    sum2 data
 * @note 
 * @par         Example
 * @code
    tmp = ADC_GetSum2Data(ADC0);
 * @endcode
 *******************************************************************************
 */
int16_t ADC_GetSum2Data(ADC_Struct* ADCx)
{
    return (int16_t) ADCx->SUM2.H[0];
}
/**
 *******************************************************************************
 * @brief	    Set sum0 data 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCSum0Initial: ADC sum-0 initial data 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetSum0Data(ADC0, 255);
 * @endcode
 *******************************************************************************
 */
void ADC_SetSum0Data(ADC_Struct* ADCx, int16_t ADCSum0Initial)
{
    ADCx->SUM0.H[0] = (uint16_t) ADCSum0Initial;
}
/**
 *******************************************************************************
 * @brief	    Set sum1 data
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCSum1Initial: ADC sum-1 initial data 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetSum1Data(ADC0, 25);
 * @endcode
 *******************************************************************************
 */
void ADC_SetSum1Data(ADC_Struct* ADCx, int16_t ADCSum1Initial)
{
    ADCx->SUM1.H[0] = (uint16_t) ADCSum1Initial;
}
/**
 *******************************************************************************
 * @brief	    Set sum2 data
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADCSum2Initial: ADC sum-2 initial data 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetSum2Data(ADC0, 1000);
 * @endcode
 *******************************************************************************
 */
void ADC_SetSum2Data(ADC_Struct* ADCx, int16_t ADCSum2Initial)
{
    ADCx->SUM2.H[0] = (uint16_t) ADCSum2Initial;
}
///@}





/**
 * @name	ADC conversion data configuration
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    Config ADC conversion data Alignment mode
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	AlignMode: data alignment mode select (Right/Left)
 *  @arg\b	    ADC_RightJustified : Right (Right alignment)
 *	@arg\b	    ADC_LeftJustified : Left (Left alignment)
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_DataAlignment_Select(ADC0, ADC_RightJustified);
 * @endcode
 *******************************************************************************
 */
void ADC_DataAlignment_Select(ADC_Struct* ADCx, ADC_DataAlignModeDef AlignMode)
{
    ADCx->CR1.MBIT.ALIGN_SEL = AlignMode;
}

/**
 *******************************************************************************
 * @brief	    Config ADC conversion data resolution
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ResolutionData: data resolution (12/10 bit)
 *  @arg\b	    ADC_12BitData : data resolution = 12 bit
 *	@arg\b	    ADC_10BitData : data resolution = 10 bit
 *	@arg\b	    ADC_8BitData : data resolution = 10 bit
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_DataResolution_Select(ADC0, ADC_12BitData);
 * @endcode
 *******************************************************************************
 */
void ADC_DataResolution_Select(ADC_Struct* ADCx, ADC_ResolutionDef ResolutionData)
{
    ADCx->CR0.MBIT.RES_SEL = ResolutionData;
}

/**
 *******************************************************************************
 * @brief	    Config data overrun mode select 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	DataOW: overrun mode select
 *  @arg\b	    ADC_DataOverWritten : Overwritten by new data
 *	@arg\b	    ADC_DataKeep : Preserved old date 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_DataOverrunMode_Select(ADC0, ADC_DataOverWritten);
 * @endcode
 *******************************************************************************
 */
void ADC_DataOverrunMode_Select(ADC_Struct* ADCx, ADC_DataOWDef DataOW)
{
    ADCx->CR1.MBIT.OVR_MDS = DataOW;
}

/**
 *******************************************************************************
 * @brief	    Get DATA status flag 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return 	    DATA flag (OVRF/CF)
 *  @arg\b	    ADC_DAT0_WDLF : ADC voltage window detect outside low event flag 
 *  @arg\b	    ADC_DAT0_WDIF : ADC voltage window detect inside event flag 
 *  @arg\b	    ADC_DAT0_WDHF : ADC voltage window detect outside high event flag 
 *  @arg\b	    ADC_DAT0_CF : ADC0 conversion data-0 complete in 1-time and 
 *                            data ready status bit 
 *  @arg\b	    ADC_DAT0_OVRF : ADC0 conversion data register-0 
 *                              overwrite/overrun indication status bit 
 * @note 
 * @par         Example
 * @code
    tmp = ADC_GetDAT0Flags(ADC0);
 * @endcode
 *******************************************************************************
 */
uint8_t ADC_GetDAT0Flags(ADC_Struct* ADCx)
{
    return ADCx->DAT0.B[2];
}

/**
 *******************************************************************************
 * @brief	    Get DATA conversion channel 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return 	    which channel
 * @note 
 * @par         Example
 * @code
    tmp = ADC_GetDAT0Channel(ADC0);
 * @endcode
 *******************************************************************************
 */
uint8_t ADC_GetDAT0Channel(ADC_Struct* ADCx)
{
    return ADCx->DAT0.MBIT.DAT0_CH;
}

/**
 *******************************************************************************
 * @brief	    Get dat0 data
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return 	    dat0 data
 * @note 
 * @par         Example
 * @code
    tmp = ADC_GetDAT0Data(ADC0);
 * @endcode
 *******************************************************************************
 */
int16_t ADC_GetDAT0Data(ADC_Struct* ADCx)
{
    return (int16_t) ADCx->DAT0.H[0];
}
/**
 *******************************************************************************
 * @brief	    Configures ADC output code with digital offset
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	sDigiOffset: specified 2s complement value of digital 
 *      	    This parameter can be: +15~-16.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_SetDigitalOffset(ADC0, 0);
 * @endcode
 *******************************************************************************
 */
void ADC_SetDigitalOffset(ADC_Struct* ADCx, int8_t sDigiOffset)
{
    ADCx->CR1.MBIT.DOS_VAL = (uint8_t) sDigiOffset;
}

/**
 *******************************************************************************
 * @brief	    Configures ADC conversion data format
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	DatFormat: specified ADC output code format 
 *  @arg\b	    ADC_UnsignedFormat : ADC output unsigned data format
 *	@arg\b	    ADC_2sCompletementFormat : ADC output 2's complement data format
 * @return 	    none
 * @note        ADC_UnsignedFormat for ADC_SingleMode
 * @note        ADC_2sCompletementFormat for ADC_DifferentMode
 * @par         Example
 * @code
    ADC_SetOutputCodeFormat(ADC0, ADC_UnsignedFormat);
 * @endcode
 *******************************************************************************
 */
void ADC_SetOutputCodeFormat(ADC_Struct* ADCx, ADC_OutputCodeFormatDef DatFormat)
{
#if defined(MG32_1ST)
    ADCx->CR0.MBIT.CODE_FMT = DatFormat;
#else
    if (DatFormat == ADC_UnsignedFormat)
        ADCx->CR0.B[2] |= 0x00;
#endif
}
///@}




#if defined(MG32_3RD) || defined(MG32_4TH)
/**
 * @name	TSO (Temperature) function routine
 *   		
 */ 
///@{ 
// Config TSO function routine
/**
 *******************************************************************************
 * @brief	    Enable/Disable TSO output that sample by ADC.
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of TSO module.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_TSO_Cmd(ADC0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_TSO_Cmd(ADC_Struct* ADCx, FunctionalState NewState)
{
    ADCx->ANA.MBIT.TS_EN = NewState;
}

/**
 *******************************************************************************
 * @brief	    Config ADC Vref when sample TSO.
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	TSOVref: new state of the ADCx Vref .
 *  @arg\b	    ADC_VREF : ADC keep Vref pin when ADC sample TSO.
 *  @arg\b	    ADC_IVR24 : ADC Vref select IVR24 (2.4V) when ADC sample TSO.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_TSOVref_Select(ADC0, ADC_IVR24);
 * @endcode
 *******************************************************************************
 */
void ADC_TSOVref_Select(ADC_Struct* ADCx, ADC_TSOVrefSel TSOVref)
{
    ADCx->ANA.MBIT.TS_AUTO = TSOVref;
}

///@}
#endif 




/**
 * @name	Internal refernece 2.4V function routine
 *   		
 */ 
///@{ 
#if defined(MG32_3RD)
// Internal refernece 2.4V function routine
/**
 *******************************************************************************
 * @brief	    Enable/Disable Internal reference 2.4V.
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of TSO module.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_IVR24_Cmd(ADC0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_IVR24_Cmd(ADC_Struct* ADCx, FunctionalState NewState)
{
    ADCx->ANA.MBIT.IVR_EN = NewState;
}
#endif 

#if defined(MG32_3RD)
/**
 *******************************************************************************
 * @brief	    Config ADC reference source.
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	RefSel: new state of reference select.
 *  @arg\b	    ADC_VREF_Pin : external reference pin VREF+ (ADC_VREF).
 *  @arg\b	    ADC_INT_VR24 : internal reference voltage 2.4 volt.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_TopRefernce_Select(ADC0, ADC_INT_VR24);
 * @endcode
 *******************************************************************************
 */
void ADC_TopRefernce_Select(ADC_Struct* ADCx, ADC_ReferenceSel RefSel)
{
    ADCx->ANA.MBIT.IVREF_SEL = RefSel;
}
///@}
#endif 




/**
 * @name	interrupt and flag (SET/CLEAR/Config) 
 *   		
 */ 
///@{ 
//
/**
 *******************************************************************************
 * @brief	    Config interrupt source (Enable/Disable)
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADC_ITSrc: interrupt source 
 *  @arg\b	    ADC_SUMOVR_IE : ADC0 data sum-0,1,2  overrun event interrupt enable 
 *  @arg\b	    ADC_SUMC_IE : ADC0 data sum-0,1,2  accumulation complete interrupt  
 *  @arg\b	    ADC_SUMO_IE : ADC0 data sum-0,1,2  accumulation overflow or underflow interrupt enable 
 *  @arg\b	    ADC_WDH_IE : ADC0 voltage window detect outside high event interrupt enable 
 *  @arg\b	    ADC_WDI_IE : ADC0 voltage window detect inside event interrupt enable 
 *  @arg\b	    ADC_WDL_IE : ADC0 voltage window detect outside low event interrupt enabl 
 *  @arg\b	    ADC_OVR_IE : ADC0 conversion overrun event interrupt enable 
 *  @arg\b	    ADC_ESCNV_IE : ADC0 channel scan conversion end interrupt enable 
 *  @arg\b	    ADC_E1CNV_IE : ADC0 one-time conversion end interrupt enable 
 *  @arg\b	    ADC_ESMP_IE : ADC0 sampling end interrupt enable 
 * @param[in] 	NewState: new state of the ADCx interrupt key.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note        
 * @par         Example
 * @code
    ADC_IT_Config(ADC0, ADC_WDI_IE, ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_IT_Config(ADC_Struct* ADCx, uint32_t ADC_ITSrc, FunctionalState NewState)
{
    if (NewState == ENABLE)
        ADCx->INT.W |= ADC_ITSrc;
    else
        ADCx->INT.W &= ~ADC_ITSrc;
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable all interrupt 
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of the ADCx all interrupt key.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    ADC_ITEA_Cmd(ADC0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void ADC_ITEA_Cmd(ADC_Struct* ADCx, FunctionalState NewState)
{
    ADCx->INT.MBIT.IEA = NewState;
}

/**
 *******************************************************************************
 * @brief	    Get one interrupt source state
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADC_ITSTAFlag: interrupt flag
 *  @arg\b	    ADC_SUMOVRF : ADC0 data sum-0,1,2  register overrun flag                  
 *  @arg\b	    ADC_SUMCF : ADC0 data sum-0,1,2  accumulation complete flag             
 *  @arg\b	    ADC_SUMOF : ADC0 data sum-0,1,2 accumulation overflow or underflow flag 
 *  @arg\b	    ADC_WDHF : ADC0 voltage window detect outside high event flag          
 *  @arg\b	    ADC_WDIF : ADC0 voltage window detect inside event flag                
 *  @arg\b	    ADC_WDLF : ADC0 voltage window detect outside low event flag           
 *  @arg\b	    ADC_OVRF : ADC0 conversion overrun event flag                          
 *  @arg\b	    ADC_ESCNVF : ADC0 channel scan conversion end flag                       
 *  @arg\b	    ADC_E1CNVF : ADC0 one-time conversion end flagg                          
 *  @arg\b	    ADC_ESMPF : ADC0 sampling end flag                                      
 * @return 	    reference define of DRV_Return
 *  @arg  	    DRV_Happened : Happened
 *  @arg	    DRV_UnHappened : Unhappened
 * @note 
 * @par         Example
 * @code
    if(ADC_GetSingleFlagStatus(ADC0, ADC_WDIF) == DRV_Happened)
    {
        // to do ...
    }   
 * @endcode
 *******************************************************************************
 */
DRV_Return ADC_GetSingleFlagStatus(ADC_Struct* ADCx, uint32_t ADC_ITSTAFlag)
{   
    if (ADCx->STA.W & ADC_ITSTAFlag)
        return DRV_Happened;
    else
        return DRV_UnHappened;
    
    
}

/**
 *******************************************************************************
 * @brief	    Get all interrupt source state
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @return 	    response what happended of STA
 * @note        
 * @par         Example
 * @code
    tmp = ADC_GetAllFlagStatus(ADC0);
 * @endcode
 *******************************************************************************
 */
uint32_t ADC_GetAllFlagStatus(ADC_Struct* ADCx)
{
    return ADCx->STA.W;
}

/**
 *******************************************************************************
 * @brief	    Clear one or all interrupt source state
 * @param[in]   ADCx: where x can be 0 peripheral.
 * @param[in] 	ADC_ITSTAFlag: interrupt source item
 *  @arg\b	    ADC_SUMOVRF : ADC0 data sum-0,1,2  register overrun flag                  
 *  @arg\b	    ADC_SUMCF : ADC0 data sum-0,1,2  accumulation complete flag             
 *  @arg\b	    ADC_SUMOF : ADC0 data sum-0,1,2 accumulation overflow or underflow flag 
 *  @arg\b	    ADC_WDHF : ADC0 voltage window detect outside high event flag          
 *  @arg\b	    ADC_WDIF : ADC0 voltage window detect inside event flag                
 *  @arg\b	    ADC_WDLF : ADC0 voltage window detect outside low event flag           
 *  @arg\b	    ADC_OVRF : ADC0 conversion overrun event flag                          
 *  @arg\b	    ADC_ESCNVF : ADC0 channel scan conversion end flag                       
 *  @arg\b	    ADC_E1CNVF : ADC0 one-time conversion end flagg                          
 *  @arg\b	    ADC_ESMPF : ADC0 sampling end flag                                      
 * @return 	    none
 * @note        
 * @par         Example
 * @code
    ADC_ClearFlag(ADC0, ADC_E1CNVF);
 * @endcode
 *******************************************************************************
 */
void ADC_ClearFlag(ADC_Struct* ADCx, uint32_t ADC_ITSTAFlag)
{
    ADCx->STA.W = ADC_ITSTAFlag;
}
///@}

