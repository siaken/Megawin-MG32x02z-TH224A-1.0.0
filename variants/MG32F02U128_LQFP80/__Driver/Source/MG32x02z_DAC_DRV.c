/**
 ******************************************************************************
 *
 * @file        MG32x02z_DAC_DRV.c
 *
 * @brief       This file provides firmware functions to manage the following 
 *              functionalities of the DAC peripheral:
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.16
 * @date        2020/09/17
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


#include "MG32x02z_DAC_DRV.h"


/**
 * @brief  	simple define
 *
 */ 

/**
 * @name	Deinitial DAC to default condition
 *   		
 */ 
///@{  
/**
 *******************************************************************************
 * @brief       Deinitializes the DACx peripheral registers to their default reset 
 *			    values.
 * @details     Reset DACx to default configuration.
 * @return		None.
 * @note 
 * @par         Example
 * @code
    DAC_DeInit(DAC);
 * @endcode
 *******************************************************************************
 */
void DAC_DeInit(DAC_Struct* DACx)
{
     DACx->INT.W = 0x00000000;
     DACx->CR0.W = 0x00000000;
     DACx->DAT0.W = 0x00000000;
     DACx->STA.W = 0xFFFFFFFF;
}
///@}




/**
 * @name	Enable/Disable DAC macro
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    Enable or Disable DAC macro.
 * @param[in]   DACx : specifies DAC peripheral.
 * @param[in] 	NewState: new state of DAC
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    None.
 * @note 
 * @par         Example
 * @code
    DAC_Cmd(DAC, ENABLE);
 * @endcode
 *******************************************************************************
 */
void DAC_Cmd(DAC_Struct* DACx, FunctionalState NewState)
{
    DACx->CR0.MBIT.DA0_EN = NewState;

}

/**
 *******************************************************************************
 * @brief	    Get DAC state.
 * @param[in]   DACx : specifies DAC peripheral.
 * @return 	    DRV_Success : equal running.
 *              DRV_Failure :  DAC shutdown.
 * @note 
 * @par         Example
 * @code
    tmp = DAC_GetDACState(DAC);
 * @endcode
 *******************************************************************************
 */
DRV_Return DAC_GetDACState(DAC_Struct* DACx)
{
    if (DACx->CR0.MBIT.DA0_EN)
        return DRV_Success;
    else 
        return DRV_Failure;

}
///@}


/**
 * @name	Config DAC output ability
 *   		
 */ 
///@{ 
#if defined(MG32_1ST)
/**
 *******************************************************************************
 * @brief	    Config DAC output current ability.
 * @param[in]   DACx : specifies DAC peripheral.
 * @param[in] 	OutCurr: output current level
 *  @arg\b	    DAC_M0 : ~0.5mA.
 *	@arg\b	    DAC_M1 : ~1mA.
 *	@arg\b	    DAC_M2 : ~2mA.
 * @return 	    None.
 * @note 
 * @par         Example
 * @code
    DAC_CurrentMode_Select(DAC, DAC_M1);
 * @endcode
 *******************************************************************************
 */
void DAC_CurrentMode_Select(DAC_Struct* DACx, DAC_CurrentModeDef OutCurr)
{
    DACx->CR0.MBIT.CMOD0_SEL = OutCurr;

}
#endif

#if defined(MG32_3RD)
/**
 *******************************************************************************
 * @brief	    Config DAC output buffer.
 * @param[in]   DACx : specifies DAC peripheral.
 * @param[in] 	NewState: new state of DAC buffer
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    None.
 * @note 
 * @par         Example
 * @code
    DAC_OutputBuffer_Cmd(DAC, ENABLE);
 * @endcode
 *******************************************************************************
 */
void DAC_OutputBuffer_Cmd(DAC_Struct* DACx, FunctionalState NewState)
{
    DACx->CR0.MBIT.BUF0_EN = NewState;

}
#endif
///@}



/**
 * @name	Read/Write Data
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    Get DAC DTA0 data.
 * @param[in]   DACx : specifies DAC peripheral.
 * @return 	    DAT0 data.
 * @note 
 * @par         Example
 * @code
    tmp = DAC_GetDAT0(DAC);
 * @endcode
 *******************************************************************************
 */
uint16_t DAC_GetDAT0(DAC_Struct* DACx)
{
    return DACx->DAT0.H[0];
}

/**
 *******************************************************************************
 * @brief	    Set DAC DTA0 data.
 * @param[in]   DACx : specifies DAC peripheral.
 * @param[in] 	dat: control output value .
 * @return 	    None.
 * @note 
 * @par         Example
 * @code
    DAC_SetDAT0(DAC, 512);
 * @endcode
 *******************************************************************************
 */
void DAC_SetDAT0(DAC_Struct* DACx,uint16_t dat)
{
    DACx->DAT0.H[0] = dat;
}

/**
 *******************************************************************************
 * @brief	    Get DAC DOR0 data (the value that DAC is conversing).
 * @param[in]   DACx : specifies DAC peripheral.
 * @return 	    DOR0 data.
 * @note 
 * @par         Example
 * @code
    tmp = DAC_GetOutput(DAC);
 * @endcode
 *******************************************************************************
 */
uint16_t DAC_GetOutput(DAC_Struct* DACx)
{
    return DACx->DOR0.H[0];
}

///@}






/**
 * @name	DAC trigger source for conversion
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    Config DAC trigger conversion source.
 * @param[in]   DACx : specifies DAC peripheral.
 * @param[in] 	DACTrgSel: select convertsion trigger source
 *  @arg\b	    DAC_SoftWare : SW setting to convert.
 *	@arg\b	    DAC_TRGPin : DAC external trigger pin.
 *	@arg\b	    DAC_CMP0Out : comparator0 output to convert.
 *	@arg\b	    DAC_TM00_TRGO : TM00 trigger out to convert.
 *	@arg\b	    DAC_TM01_TRGO : TM01 trigger out to convert.
 *	@arg\b	    DAC_TM10_TRGO : TM10 trigger out to convert.
 *	@arg\b	    DAC_ITR6 : APB ITR6 trigger out to convert. 
 *	@arg\b	    DAC_ITR7 : APB ITR7 trigger out to convert. 
 * @return 	    None.
 * @note 
 * @par         Example
 * @code
    DAC_TriggerSource_Select(DAC, DAC_TM00_TRGO);
 * @endcode
 *******************************************************************************
 */
void DAC_TriggerSource_Select(DAC_Struct* DACx, DAC_TriggerSourceDef DACTrgSel)
{
    DACx->CR0.MBIT.START0_SEL = DACTrgSel;
}

/**
 *******************************************************************************
 * @brief	    Config DAC trigger event (Disable/rising/falling/dual edge).
 * @param[in]   DACx : specifies DAC peripheral.
 * @param[in] 	DACEdgeSel: select trigger edge event to convert
 *  @arg\b	    DAC_DisableTrg : SW setting to convert.
 *	@arg\b	    DAC_AcceptRisingEdge : TM00 trigger out to convert. 
 *	@arg\b	    DAC_AcceptFallingEdge : External DAC pin trigger to convert.
 *	@arg\b	    DAC_AcceptDualEdge : comparator0 output to convert.
 * @return 	    None.
 * @note 
 * @par         Example
 * @code
    DAC_TriggerSource_Select(DAC, DAC_TRGPin);
    DAC_TriggerSource_Select(DAC, DAC_AcceptRisingEdge);
 * @endcode
 *******************************************************************************
 */
void DAC_TriggerEdge_Select(DAC_Struct* DACx, DAC_TriggerEdgeDef DACEdgeSel)
{
    DACx->CR0.MBIT.TRG0_SEL = DACEdgeSel;
}
///@}



/**
 * @name	DAC auxiliary control routine
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    Config DACx macro DATA alignment format.
 * @param[in]   DACx : specifies DAC peripheral.
 * @param[in] 	AlignMode: data alignment mode select (Right/Left)
 *  @arg\b	    DAC_RightJustified : Overwritten by new data.
 *	@arg\b	    DAC_LeftJustified : Preserved old date. 
 * @return 	    None.
 * @note 
 * @par         Example
 * @code
    DAC_DataAlignment_Select(DAC, DAC_RightJustified);
 * @endcode
 *******************************************************************************
 */
void DAC_DataAlignment_Select(DAC_Struct* DACx, DAC_DataAlignModeDef AlignMode)
{
    DACx->CR0.MBIT.ALIGN0_SEL = AlignMode;
}

/**
 *******************************************************************************
 * @brief	    Config DAC conversion data resolution.
 * @param[in]   DACx : specifies DAC peripheral.
 * @param[in] 	ResolutionData: data resolution (12/10/8 bit)
 *  @arg\b	    DAC_12BitData : data resolution = 12 bit. (for MG32F02A128/U128/A064/U064 chip)
 *  @arg\b	    DAC_10BitData : data resolution = 10 bit.
 *	@arg\b	    DAC_8BitData : data resolution = 8 bit.
 * @return 	    None.
 * @note 
 * @par         Example
 * @code
    DAC_DataResolution_Select(DAC, DAC_10BitData);
 * @endcode
 *******************************************************************************
 */
void DAC_DataResolution_Select(DAC_Struct* DACx, DAC_ResolutionDef ResolutionData)
{
    DACx->CR0.MBIT.RES0_SEL = ResolutionData;
}
///@}




/**
 * @name	interrupt and flag (SET/CLEAR/Config) 
 *   		
 */ 
///@{ 
//
/**
 *******************************************************************************
 * @brief	    Config interrupt source (Enable/Disable).
 * @param[in]   DACx : specifies DAC peripheral.
 * @param[in] 	DAC_ITSrc: interrupt source 
 *  @arg\b	    Underrun_IE : DAC conversion underrun event. 
 *  @arg\b	    Ready_IE : ready to update new data. 
 * @param[in] 	NewState: new state of the DACx interrupt key.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    None.
 * @note        
 * @note 
 * @par         Example
 * @code
    DAC_IT_Config(DAC, Ready_IE, ENABLE);
 * @endcode
 *******************************************************************************
 */
void DAC_IT_Config(DAC_Struct* DACx, uint32_t DAC_ITSrc, FunctionalState NewState)
{
    if (NewState == ENABLE)
        DACx->INT.W |= DAC_ITSrc;
    else
        DACx->INT.W &= ~DAC_ITSrc;
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable all interrupt. 
 * @param[in]   DACx : specifies DAC peripheral.
 * @param[in] 	NewState: new state of the DACx all interrupt key
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    None.
 * @note        
 * @note 
 * @par         Example
 * @code
    DAC_ITEA_Cmd(DAC, ENABLE);
 * @endcode
 *******************************************************************************
 */
void DAC_ITEA_Cmd(DAC_Struct* DACx, FunctionalState NewState)
{
    DACx->INT.MBIT.IEA = NewState;
}

/**
 *******************************************************************************
 * @brief	    Get one interrupt source state.
 * @param[in]   DACx : specifies DAC peripheral.
 * @param[in] 	DAC_ITSrc: interrupt source item
 *  @arg\b	    Underrun_Flag : DAC conversion underrun flag.  
 *  @arg\b	    Ready_Flag : ready flag to update new data. 
 * @return 	    reference define of DRV_Return
 *  @arg        DRV_Happened : Happen.
 *  @arg        DRV_UnHappened : Unhappen.
 * @note        
 * @note 
 * @par         Example
 * @code
    if (DAC_GetSingleFlagStatus(DAC, Ready_Flag) == DRV_Happened)
    {
        // to do ...
    }    
 * @endcode
 *******************************************************************************
 */
DRV_Return DAC_GetSingleFlagStatus(DAC_Struct* DACx, uint32_t DAC_ITSrc)
{
    if (DACx->STA.W & DAC_ITSrc)
        return DRV_Happened;
    else 
        return DRV_UnHappened;
    
}

/**
 *******************************************************************************
 * @brief	    Get all interrupt source state.
 * @param[in]   DACx : specifies DAC peripheral.
 * @return 	    response what happended of STA.
 * @note 
 * @par         Example
 * @code
    DAC_GetAllFlagStatus(DAC);
 * @endcode
 *******************************************************************************
 */
uint32_t DAC_GetAllFlagStatus(DAC_Struct* DACx)
{
    return DACx->STA.W;
}

/**
 *******************************************************************************
 * @brief	    Clear one or all interrupt source state.
 * @param[in]   DACx : specifies DAC peripheral.
 * @param[in] 	DAC_ITSrc: interrupt source item
 *  @arg\b	    Underrun_Flag : DAC conversion underrun flag.  
 *  @arg\b	    Ready_Flag : ready flag to update new data. 
 * @return 	    None.
 * @note        
 * @note 
 * @par         Example
 * @code
    DAC_ClearFlag(DAC, Ready_Flag);
 * @endcode
 *******************************************************************************
 */
void DAC_ClearFlag(DAC_Struct* DACx, uint32_t DAC_ITSrc)
{
    DACx->STA.W = DAC_ITSrc;
}
///@}



/**
 * @name	DMA control of DAC (only support TX mode) 
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    Enable or Disable DMA for DAC macro.
 * @param[in]   DACx : specifies DAC peripheral.
 * @param[in] 	NewState: new state of DAC
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    None.
 * @note 
 * @par         Example
 * @code
    DAC_DMA_Cmd(DAC, ENABLE);
 * @endcode
 *******************************************************************************
 */
void DAC_DMA_Cmd(DAC_Struct* DACx, FunctionalState NewState)
{
    DACx->CR0.MBIT.DMA_EN = NewState;

}
///@}

