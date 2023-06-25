/**
 ******************************************************************************
 *
 * @file        MG32x02z_CMP_DRV.c
 *
 * @brief       This file provides firmware functions to manage the following 
 *              functionalities of the CMP peripheral:
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.19
 * @date        2021/09/06
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


#include "MG32x02z_CMP_DRV.h"


/**
 * @brief  	simple define
 *
 */ 

/**
 * @name	Deinitial CMP to default condition
 *   		
 */ 
///@{  
/**
 *******************************************************************************
 * @brief       Deinitializes the CMP peripheral registers to their default reset 
 *			    values.
 * @details     Reset CMPx to default configuration
 * @return		No
 * @note 
 * @par         Example
 * @code
    CMP_DeInit(CMP);
 * @endcode
 *******************************************************************************
 */
void CMP_DeInit(void)
{
     CMP->INT.W = 0x00000000;
     CMP->ANA.W = 0x00000000;
     CMP->CR0.W = 0x00000000;
     CMP->CR1.W = 0x00000000;
#if defined(MG32_1ST)   
     CMP->CR2.W = 0x00000000;
     CMP->CR3.W = 0x00000000;
#endif
     CMP->STA.W = 0xFFFFFFFF;
}
///@}





/**
 * @name	Enable/Disable AC0~AC3 macro
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    Enable or Disable CMPACx(0~3) comparator macro
 * @param[in]   CMPACx : where x can be 0/1/2/3 peripheral.
 * @param[in] 	NewState: new state of CMP
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    CMP_Cmd(CMPAC0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void CMP_Cmd(CMPAC_Struct* CMPACx, FunctionalState NewState)
{
    CMPACx->CR.MBIT.EN = NewState;
}
/**
 *******************************************************************************
 * @brief	    Config CMPACx(0~3) response speed 
 * @param[in]   CMPACx : where x can be 0/1/2/3 peripheral.
 * @param[in] 	PowerLevelSel: the state of response time 
 *  @arg\b	    CMP_Normal : fast response 
 *  @arg\b	    CMP_Slow : slow response (low power mode)
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    CMP_Power_Select(CMPAC0, CMP_Normal);
 * @endcode
 *******************************************************************************
 */
void CMP_Power_Select(CMPAC_Struct* CMPACx, CMP_PowerLevelDef PowerLevelSel)
{
    CMPACx->CR.MBIT.RES = PowerLevelSel;

}
///@}





/**
 * @name	Config common configuration for AC0~AC3 macro
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    Config ACx(0~3) macro synchronized clock for comparator output
 * @param[in]   CMPACx : where x can be 0/1/2/3 peripheral.
 * @param[in] 	SYNCHClockSrc: select synchronized clock
 *  @arg\b	    CMP_ByPass : bypass (no schronized)
 *  @arg\b	    CMP_CMPCK : synchronized clock from CMP_PROC
 *  @arg\b	    CMP_TM00_TRGO : synchronized clock from TM00 TRGO
 *  @arg\b	    CMP_TM01_TRGO : synchronized clock from TM01 TRGO
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    CMP_FilterClock_Select(CMPAC0, CMP_ByPass);
 * @endcode
 *******************************************************************************
 */
void CMP_FilterClock_Select(CMPAC_Struct* CMPACx, CMP_SynchClockSrcDef SYNCHClockSrc)
{    
    CMPACx->CR.MBIT.FSEL = SYNCHClockSrc;
}

/**
 *******************************************************************************
 * @brief       Configures the CMPACx synchronized filter clock divider
 * @param[in]   CMPACx : where x can be 0/1/2/3 peripheral.
 * @param[in] 	SYNCHClockDiv : specifies the synchronized filter clock divider
 *  @arg\b	    CMP_SFDIV1 : divided by 1
 *  @arg\b	    CMP_SFDIV2 : divided by 2
 *  @arg\b	    CMP_SFDIV4 : divided by 4
 *  @arg\b	    CMP_SFDIV8 : divided by 8
 * @return		No
 * @note 
 * @par         Example
 * @code
    CMP_FilterClockDivider_Select(CMPAC3, CMP_SFDIV2);
 * @endcode
 *******************************************************************************
 */
void CMP_FilterClockDivider_Select(CMPAC_Struct* CMPACx, CMP_SYNCHClockDivDef SYNCHClockDiv)
{    
    CMPACx->CR.MBIT.FDIV = SYNCHClockDiv;
}

/**
 *******************************************************************************
 * @brief       Config CMPACx inverse for output pin
 * @param[in]   CMPACx : where x can be 0/1/2/3 peripheral.
 * @param[in] 	NewState : new inverse state for output pin
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return		No
 * @note 
 * @par         Example
 * @code
    CMP_InverseOutputPin(CMPAC2, DISABLE);
 * @endcode
 *******************************************************************************
 */
void CMP_InverseOutputPin(CMPAC_Struct* CMPACx, FunctionalState NewState)
{
    CMPACx->CR.MBIT.PINV = NewState;
}

/**
 *******************************************************************************
 * @brief       Set the CMPACx output Polarity 
 * @param[in]   CMPACx : where x can be 0/1/2/3 peripheral.
 * @param[in] 	OutPorSel : specifies state of output 
 *  @arg\b	    CMP_PositivePolarity : select positive 
 *  @arg\b	    CMP_NegativePolarity : select negative (inverse)
 * @return		No
 * @note 
 * @par         Example
 * @code
    CMP_OutputPolarity_Select(CMPAC1, CMP_PositivePolarity);
 * @endcode
 *******************************************************************************
 */
void CMP_OutputPolarity_Select(CMPAC_Struct* CMPACx, CMP_OutputPolarityDef OutPorSel)
{
    CMPACx->CR.MBIT.INV = OutPorSel;
}

///@}





/**
 * @name	Config internal reference
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief       Config CMPAC0 internal reference Enable/Disable
 * @param[in] 	CMPx : specifies comparator peripheral
 * @param[in] 	NewState : new inverse state for output pin
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return		No
 * @note 
 * @par         Example
 * @code
    CMP_IVREF_Cmd(CMP, ENABLE);
 * @endcode
 *******************************************************************************
 */
void CMP_IVREF_Cmd(CMP_Struct* CMPx, FunctionalState NewState)
{
    CMPx->ANA.MBIT.IVREF_EN = NewState;

}
    
/**
 *******************************************************************************
 * @brief       Config CMPAC1/2/3 internal reference Enable/Disable
 * @param[in] 	CMPx : specifies comparator peripheral
 * @param[in] 	NewState : new inverse state for output pin
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return		No
 * @note 
 * @par         Example
 * @code
    CMP_IVREF2_Cmd(CMP, ENABLE);
 * @endcode
 *******************************************************************************
 */
void CMP_IVREF2_Cmd(CMP_Struct* CMPx, FunctionalState NewState)
{
    CMPx->ANA.MBIT.IVREF2_EN = NewState;
    
}

/**
 *******************************************************************************
 * @brief       Config CMPAC0 internal reference R-ladder level
 * @param[in] 	CMPx : specifies comparator peripheral
 * @param[in] 	RefSel : internal reference select 0~63
 * @return 	    
 *  @arg        DRV_Failure : wrong parameter 
 *  @arg        DRV_Success : config pass
 * @note 
 * @par         Example
 * @code
    CMP_IVREF_Select(CMP, 12);
 * @endcode
 *******************************************************************************
 */
DRV_Return CMP_IVREF_Select(CMP_Struct* CMPx, uint8_t RefSel)
{
    
    if (RefSel > 63)
        return DRV_Failure;
        
    CMPx->ANA.MBIT.IVREF_RS = RefSel;
    
    return DRV_Success;
}
    
/**
 *******************************************************************************
 * @brief       Config CMPAC1/2/3 internal R-ladder level
 * @param[in] 	CMPx : specifies comparator peripheral
 * @param[in] 	RefSel : internal reference2 select 0~63
 * @return 	    
 *  @arg        DRV_Failure : wrong parameter 
 *  @arg        DRV_Success : config pass
 * @note 
 * @par         Example
 * @code
    CMP_IVREF2_Select(CMP, 32);
 * @endcode
 *******************************************************************************
 */
DRV_Return CMP_IVREF2_Select(CMP_Struct* CMPx, uint8_t RefSel)
{
    if (RefSel > 63)
        return DRV_Failure;
        
    CMPx->ANA.MBIT.IVREF2_RS = RefSel;
    
    return DRV_Success;
}

#if defined(MG32_3RD)

/**
 *******************************************************************************
 * @brief       Config analog comparator main internal reference (R-ladder) 
 *              top source select.
 * @param[in] 	CMPx : specifies comparator peripheral.
 * @param[in] 	RefTopSel : the new state of Vref top source.
 *  @arg\b	    CMP_VrefTop_VDD : VDDA (analog power voltage)
 *  @arg\b	    CMP_VrefTop_VR0 : VR0 (LDO VR0 output)
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    CMP_IVREFTopSource_Select(CMP, CMP_VrefTop_VDD);
 * @endcode
 *******************************************************************************
 */
void CMP_IVREFTopSource_Select(CMP_Struct* CMPx, CMP_VrefTopSourceSel RefTopSel)
{
    CMPx->ANA.MBIT.IVREF_SEL = RefTopSel;
}

/**
 *******************************************************************************
 * @brief       Config analog comparator 2nd internal reference (R-ladder) 
 *              top source select.
 * @param[in] 	CMPx : specifies comparator peripheral
 * @param[in] 	Ref2TopSel : the new state of Vref2 top source.
 *  @arg\b	    CMP_VrefTop_VDD : VDDA (analog power voltage)
 *  @arg\b	    CMP_VrefTop_VR0 : VR0 (LDO VR0 output)
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    CMP_IVREF2TopSource_Select(CMP, CMP_VrefTop_VDD);
 * @endcode
 *******************************************************************************
 */
void CMP_IVREF2TopSource_Select(CMP_Struct* CMPx, CMP_VrefTopSourceSel Ref2TopSel)
{
    CMPx->ANA.MBIT.IVREF2_SEL = Ref2TopSel;
}

#endif
///@}




    
#if defined(MG32_3RD)
/**
 * @name	Config comparator IVREF output macro
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    Enable or Disable IVREF output to CMP0_I0 pin for positive 
 *              channel MUX .
 * @param[in]   CMPACx : where x can be 0 peripheral.
 * @param[in] 	NewState: new state of CMP
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    CMP_AC0IVREFOuput_Cmd(CMPAC0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void CMP_AC0IVREFOuput_Cmd(CMPAC_Struct* CMPACx, FunctionalState NewState)
{
    if(CMPACx == CMPAC0)
        CMPACx->CR.MBIT.IVROE = NewState;
}

/**
 *******************************************************************************
 * @brief	    Enable or Disable IVREF output to CMP1_I0 pin for positive 
 *              channel MUX .
 * @param[in]   CMPACx : where x can be 0 peripheral.
 * @param[in] 	NewState: new state of CMP
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    CMP_AC1IVREFOuput_Cmd(CMPAC1, ENABLE);
 * @endcode
 *******************************************************************************
 */
void CMP_AC1IVREFOuput_Cmd(CMPAC_Struct* CMPACx, FunctionalState NewState)
{
    if(CMPACx == CMPAC1)
        CMPACx->CR.MBIT.IVROE = NewState;
}

#endif
///@}





/**
 * @name	config input source for AC0~AC3 macro
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief       Config CMPACx positive input property
 * @param[in]   CMPACx : where x can be 0/1/2/3 peripheral.
 * @param[in] 	ACzPPin: select positive pin input
 *  @arg\b	    CMP_ACzIVREF : select internal reference be input 
 *  @arg\b	    CMP_ACz_I0 : select ACz input0 be input
 *  @arg\b	    CMP_ACz_I1 : select ACz input1 be input
 *  @arg\b	    CMP_ACz_CMPC0 : select CMP common input0 be input
 *  @arg\b	    CMP_ACz_CMPC1 : select CMP common input1 be input
 *  @arg\b	    CMP_ACzLDO : select LDO be input
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    CMP_PositivePin_Select(CMPAC0, CMP_ACz_I0);
 * @endcode
 *******************************************************************************
 */
void CMP_PositivePin_Select(CMPAC_Struct* CMPACx, CMP_ACPinInputDef ACzPPin)
{
    CMPACx->CR.MBIT.PMUX = ACzPPin;
    
}

/**
 *******************************************************************************
 * @brief       Config CMPACx negative input property
 * @param[in]   CMPACx : where x can be 0/1/2/3 peripheral.
 * @param[in] 	ACzNPin: select positive pin input
 *  @arg\b	    CMP_ACzIVREF : select internal reference be input 
 *  @arg\b	    CMP_ACz_I0 : select ACz input0 be input
 *  @arg\b	    CMP_ACz_I1 : select ACz input1 be input
 *  @arg\b	    CMP_ACz_CMPC0 : select CMP common input0 be input
 *  @arg\b	    CMP_ACz_CMPC1 : select CMP common input1 be input
 *  @arg\b	    CMP_ACzLDO : select LDO be input
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    CMP_NegativePin_Select(CMPAC1, CMP_ACz_I0);
 * @endcode
 *******************************************************************************
 */
void CMP_NegativePin_Select(CMPAC_Struct* CMPACx, CMP_ACPinInputDef ACzNPin)
{
    CMPACx->CR.MBIT.NMUX = ACzNPin;
    
}

///@}





#if defined(MG32_2ND) || defined(MG32_3RD)
/**
 * @name	Set comparator hystersis window level
 *   		
 */ 
///@{ 
//
/**
 *******************************************************************************
 * @brief	    Set CMPACx hysteresis window level
 * @param[in]   CMPACx : where x can be 0/1/2/3 peripheral.
 * @param[in] 	ACzHyLevel: Hystersis window level select
 *  @arg\b	    CMP_DisableHystersis : Disable comparator hysteresis window
 *  @arg\b	    CMP_HysteresisLevel1 : Config Hysteresis window level1 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    CMP_SetHysteresisWindow(CMPAC0, CMP_DisableHysteresis);
 * @endcode
 *******************************************************************************
 */
void CMP_SetHysteresisWindow(CMPAC_Struct* CMPACx, CMP_HysteresisLevel ACzHyLevel)
{
    CMPACx->CR.MBIT.HYS = ACzHyLevel;    
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
 * @param[in]   CMPx : where comparator peripheral.
 * @param[in] 	CMP_ITSrc: interrupt source 
 *  @arg\b	    AC0_RisingEdge_IE : AC0 Rising edge interrupt enable 
 *  @arg\b	    AC0_FallingEdge_IE : AC0 Falling edge interrupt enable 
 *  @arg\b	    AC1_RisingEdge_IE : AC1 Rising edge interrupt enable 
 *  @arg\b	    AC1_FallingEdge_IE : AC1 Falling edge interrupt enable 
 *  @arg\b	    AC2_RisingEdge_IE : AC2 Rising edge interrupt enable 
 *  @arg\b	    AC2_FallingEdge_IE : AC2 Falling edge interrupt enable 
 *  @arg\b	    AC3_RisingEdge_IE : AC3 Rising edge interrupt enable 
 *  @arg\b	    AC3_FallingEdge_IE : AC3 Falling edge interrupt enable 
 * @param[in] 	NewState: new state of the CMPx interrupt key.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    CMP_IT_Config(CMP, AC0_RisingEdge_IE, ENABLE);
 * @endcode
 *******************************************************************************
 */
void CMP_IT_Config(CMP_Struct* CMPx, uint32_t CMP_ITSrc, FunctionalState NewState)
{
    if (NewState == ENABLE)
        CMPx->INT.W |= CMP_ITSrc;
    else
        CMPx->INT.W &= ~(CMP_ITSrc);
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable all interrupt 
 * @param[in]   CMPx : where comparator peripheral.
 * @param[in] 	NewState: new state of the CMPx all interrupt key.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    CMP_ITEA_Cmd(CMP, ENABLE);
 * @endcode
 *******************************************************************************
 */
void CMP_ITEA_Cmd(CMP_Struct* CMPx, FunctionalState NewState)
{
    CMPx->INT.MBIT.IEA = NewState;
}

/**
 *******************************************************************************
 * @brief	    Get one interrupt source state
 * @param[in]   CMPx : where comparator peripheral.
 * @param[in] 	CMP_ITSrc: interrupt source item
 *  @arg\b	    AC0_RisingEdge_Flag : Rising edge interrupt flag 
 *  @arg\b	    AC0_FallingEdge_Flag : Falling edge interrupt flag 
 *  @arg\b	    AC1_RisingEdge_Flag : Rising edge interrupt flag 
 *  @arg\b	    AC1_FallingEdge_Flag : Falling edge interrupt flag 
 *  @arg\b	    AC2_RisingEdge_Flag : Rising edge interrupt flag 
 *  @arg\b	    AC2_FallingEdge_Flag : Falling edge interrupt flag 
 *  @arg\b	    AC3_RisingEdge_Flag : Rising edge interrupt flag 
 *  @arg\b	    AC3_FallingEdge_Flag : Falling edge interrupt flag 
 * @return 	    reference define of DRV_Return
 *  @arg        DRV_Happened : Happen 
 *  @arg        DRV_UnHappened : Unhappen
 * @note 
 * @par         Example
 * @code
    if (CMP_GetSingleFlagStatus(CMP, AC2_RisingEdge_Flag) == DRV_Happened)
    {
        // to do ...
    }    
 * @endcode
 *******************************************************************************
 */
DRV_Return CMP_GetSingleFlagStatus(CMP_Struct* CMPx, uint32_t CMP_ITSrc)
{
    if (CMPx->STA.W & CMP_ITSrc)
        return DRV_Happened;
    else 
        return DRV_UnHappened;
    
}

/**
 *******************************************************************************
 * @brief	    Get all interrupt source state
 * @param[in]   CMPx : where comparator peripheral.
 * @return 	    response what happended of STA
 * @note 
 * @par         Example
 * @code
    tmp = CMP_GetAllFlagStatus(CMP);
 * @endcode
 *******************************************************************************
 */
uint32_t CMP_GetAllFlagStatus(CMP_Struct* CMPx)
{
    return CMPx->STA.W;
}

/**
 *******************************************************************************
 * @brief	    Clear one or all interrupt source state
 * @param[in]   CMPx : where comparator peripheral.
 *  @arg\b	    AC0_RisingEdge_Flag : Rising edge interrupt flag 
 *  @arg\b	    AC0_FallingEdge_Flag : Falling edge interrupt flag 
 *  @arg\b	    AC1_RisingEdge_Flag : Rising edge interrupt flag 
 *  @arg\b	    AC1_FallingEdge_Flag : Falling edge interrupt flag 
 *  @arg\b	    AC2_RisingEdge_Flag : Rising edge interrupt flag 
 *  @arg\b	    AC2_FallingEdge_Flag : Falling edge interrupt flag 
 *  @arg\b	    AC3_RisingEdge_Flag : Rising edge interrupt flag 
 *  @arg\b	    AC3_FallingEdge_Flag : Falling edge interrupt flag 
 * @param[in] 	CMP_ITSrc: interrupt source item
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    CMP_ClearFlag(CMP, (AC0_RisingEdge_Flag | AC1_FallingEdge_Flag));
 * @endcode
 *******************************************************************************
 */
void CMP_ClearFlag(CMP_Struct* CMPx, uint32_t CMP_ITSrc)
{
    CMPx->STA.W = CMP_ITSrc;
}
///@}





/**
 * @name	Get Comparator output
 *   		
 */ 
///@{ 
//
/**
 *******************************************************************************
 * @brief       Get the CMPACx output with inverse 
 * @param[in]   CMPACx : where x can be 0/1/2/3 peripheral.
 * @return		return CMPACx comparator output state 
 *  @arg\b	    DRV_Logic1 : Logic '1'
 *  @arg\b	    DRV_Logic0 : Logic '0'
 * @note 
 * @par         Example
 * @code
    tmp = CMP_GetOutput(CMPAC2);
 * @endcode
 *******************************************************************************
 */
DRV_Return CMP_GetOutput (CMPAC_Struct* CMPACx)
{
    DRV_Return RetBitV;
    
    RetBitV = DRV_Logic0; 
    if (CMPACx == CMPAC0)
    {
        if (CMP->STA.MBIT.AC0_S == SET)
            RetBitV = DRV_Logic1;
        else
            RetBitV = DRV_Logic0;
    }
    else if (CMPACx == CMPAC1)
    {
        if (CMP->STA.MBIT.AC1_S == SET)
            RetBitV = DRV_Logic1;
        else
            RetBitV = DRV_Logic0;
    }
#if defined(MG32_1ST)
    else if (CMPACx == CMPAC2)
        if (CMP->STA.MBIT.AC2_S == SET)
            RetBitV = DRV_Logic1;
        else
            RetBitV = DRV_Logic0;
    else 
        if (CMP->STA.MBIT.AC3_S == SET)
            RetBitV = DRV_Logic1;
        else
            RetBitV = DRV_Logic0;
#endif
    
        return RetBitV;
        
}
///@}

