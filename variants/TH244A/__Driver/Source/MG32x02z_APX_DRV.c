/**
 ******************************************************************************
 *
 * @file        MG32x02z_APX_DRV.c
 *
 * @brief       This file provides firmware functions to manage the following 
 *              functionalities of the APB peripheral:
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.18
 * @date        2022/05/10
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
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


#include "MG32x02z_APX_DRV.h"


/**
 * @name	CCL's truth table control
 *   		
 */ 
///@{  
/**
 *******************************************************************************
 * @brief	    Select CCLx truth table function.
 * @param[in]   CCLx: where x can be 0,1 to select the CCLx peripheral.
 * @param[in] 	TFunc: specifies truth table function.
 *  @arg\b      APX_3IN_AND: Run truth table with 3-input "AND".
 *  @arg\b      APX_3IN_NAND: Run truth table with 3-input "AND".
 *  @arg\b      APX_3IN_OR: Run truth table with 3-input "AND".
 *  @arg\b      APX_3IN_NOR: Run truth table with 3-input "AND".
 *  @arg\b      APX_3IN_XOR: Run truth table with 3-input "AND".
 *  @arg\b      APX_3IN_XNOR: Run truth table with 3-input "AND".
 *  @arg\b      APX_2IN_AND: Run truth table with 2-input "OR". *[IN2] mask.
 *  @arg\b      APX_2IN_NAND: Run truth table with 2-input "OR". *[IN2] mask.
 *  @arg\b      APX_2IN_OR: Run truth table with 2-input "OR". *[IN2] mask.
 *  @arg\b      APX_2IN_NOR: Run truth table with 2-input "OR". *[IN2] mask.
 *  @arg\b      APX_2IN_XOR: Run truth table with 2-input "OR". *[IN2] mask.
 *  @arg\b      APX_2IN_XNOR: Run truth table with 2-input "OR". *[IN2] mask.
 *  @arg\b      APX_IN0_NOT: Run truth table with "NOT" IN0.
 *  @arg\b      APX_IN1_NOT: Run truth table with "NOT" IN1.
 *  @arg\b      APX_IN2_NOT: Run truth table with "NOT" IN2.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APX_CCLTruthTable_Select(CCL1, APX_3IN_NOR);
 * @endcode
 *******************************************************************************
 */
void APX_CCLTruthTable_Select(CCL_Struct* CCLx, APX_TruthTableDef TFunc)
{
    CCLx->CCLx0.MBIT.TRUTH = TFunc;
}

/**
 *******************************************************************************
 * @brief	    Turn on/off Truth table function.
 * @param[in]   CCLx: where x can be 0,1 to select the CCLx peripheral.
 * @param[in] 	NewState: new state of truth table.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APX_CCLTruthTable_Cmd(CCL0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void APX_CCLTruthTable_Cmd(CCL_Struct* CCLx, FunctionalState NewState)
{
    CCLx->CCLx0.MBIT.TEN = NewState;
}

///@}




/**
 * @name	CCL control
 *   		
 */ 
///@{  

/**
 *******************************************************************************
 * @brief       Get CCLx output state.
 * @param[in]   CCLx: where x can be 0,1 to select the CCLx peripheral.
 * @return		return OBMx output 0/1 state 
 *  @arg        DRV_Logic1 : '1' 
 *  @arg        DRV_Logic0 : '0'
 * @note 
 * @par         Example
 * @code
    tmp = APX_GetCCLxOutputState(OBM1);
 * @endcode
 *******************************************************************************
 */
DRV_Return APX_GetCCLxOutputState(CCL_Struct* CCLx)
{
    if (CCLx == CCL0)
    {
        if (APX->STA.MBIT.CCL0_OUT)
            return DRV_Logic1;
        else 
            return DRV_Logic0;
    }
    if (APX->STA.MBIT.CCL1_OUT)
        return DRV_Logic1;
    else 
        return DRV_Logic0;
}

/**
 *******************************************************************************
 * @brief	    Config CCL0 sequential logic input CCL_S0 select.
 * @param[in]   CCLx: where x can be 0 to select the CCLx peripheral.
 * @param[in] 	CCLxSQIN : specifies the CCL_S0 logic to be used
 *  @arg	    APX_CCLx_S0_0 : CCLx_S0 sequential logic input is '0'. 
 *	@arg	    APX_CCLx_S0_1 : CCLx_S0 sequential logic input is '1'. 
 *  @arg	    APX_CCLx_S0_CCL1_S1 : CCL0_S0 sequential logic input is CCL_S1.
 *                                    This item is only for CCL0.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APX_SetCCLSnState(CCL0, APX_CCLx_S0_1);
 * @endcode
 *******************************************************************************
 */
void APX_SetCCLSnState(CCL_Struct* CCLx, APX_CCLx_SQIN CCLxSQIN)
{
	CCLx->CCLx0.MBIT.SQIN = CCLxSQIN;
}

/**
 *******************************************************************************
 * @brief	    Inverse CCLx output.
 * @param[in]   CCLx: where x can be 0,1 to select the CCLx peripheral.
 * @param[in] 	NewState: inverse External Trigger
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APX_InverseCCLOutput_Cmd(CCL0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void APX_InverseCCLOutput_Cmd(CCL_Struct* CCLx, FunctionalState NewState)
{
    CCLx->CCLx0.MBIT.INV = NewState;
    
}

/**
 *******************************************************************************
 * @brief	    Config CCLx input clock divider.
 * @param[in]   CCLx: where x can be 0,1 to select the CCLx peripheral.
 * @param[in] 	INTClockSrc : specifies the CCL internal clock divider to be used
 *  @arg	    APX_IntDIV1 : divided by 1.
 *	@arg	    APX_IntDIV2 : divided by 2.
 *  @arg	    APX_IntDIV4 : divided by 4.
 *	@arg	    APX_IntDIV8 : divided by 8.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APX_SetCCLIntClockDivider(CCL0, APX_IntDIV4);
 * @endcode
 *******************************************************************************
 */
void APX_SetCCLIntClockDivider(CCL_Struct* CCLx, APX_INTClockDivDef INTClockSrc)
{
	CCLx->CCLx0.MBIT.DIV = INTClockSrc;
}

/**
 *******************************************************************************
 * @brief	    Config CCLx sequential logic mode.
 * @param[in]   CCLx: where x can be 0,1 to select the CCLx peripheral.
 * @param[in] 	INTClockSrc : specifies the Main Counter direction to be used
 *  @arg	    APX_SQSEL_DISABLE=0: CCL sequential logic mode select disable.
 *	@arg	    APX_SQSEL_D_Flipflop: CCL sequential logic mode select D flip flop.
 *  @arg	    APX_SQSEL_JK_Flipflop: CCL sequential logic mode select JK flip flop.
 *	@arg	    APX_SQSEL_D_Latch: CCL sequential logic mode select D latch.
 *	@arg	    APX_SQSEL_RS_Latch: CCL sequential logic mode select RS latch.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APX_SQSEL_Select(CCL0, APX_SQSEL_JK_Flipflop);
 * @endcode
 *******************************************************************************
 */
void APX_SQSEL_Select(CCL_Struct* CCLx, APX_SQLogicModeSel INTClockSrc)
{
	CCLx->CCLx0.MBIT.SQSEL = INTClockSrc;
}

/**
 *******************************************************************************
 * @brief	    Config CCLx edge detect mode.
 * @param[in]   CCLx: where x can be 0,1 to select the CCLx peripheral.
 * @param[in] 	EdgeSel : specifies the Main Counter direction to be used
 *  @arg	    APX_CCL_Disable: disable detect function.
 *	@arg	    APX_CCL_RisingEdge: Rising edge detect function.
 *  @arg	    APX_CCL_FallingEdge: Falling edge detect function.
*	@arg	    APX_CCL_DualEdge: dual edge to detect function.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APX_EDSEL_Select(CCL0, APX_CCL_RisingEdge);
 * @endcode
 *******************************************************************************
 */
void APX_EDSEL_Select(CCL_Struct* CCLx, APX_EdgeDetectSel EdgeSel)
{
	CCLx->CCLx0.MBIT.EDSEL = EdgeSel;
}

/**
 *******************************************************************************
 * @brief	    Config CCLx filter.   
 * @param[in]   CCLx: where x can be 0,1 to select the CCLx peripheral.
 * @param[in] 	FilterDef: specifies filter function
 *  @arg\b      APX_DisableFilter: Disable filter. 
 *  @arg\b      APX_SYNCFilter: Synchronizer enabled. 
 *  @arg\b      APX_FILTER: Filter enabled. 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APX_SetFilterFunction( CCL0, APX_SYNCFilter);
 * @endcode
 *******************************************************************************
 */
void APX_SetFilterFunction(CCL_Struct* CCLx, APX_CCLFilterDef FilterDef)
{
    CCLx->CCLx0.MBIT.FTSEL = FilterDef;
}

/**
 *******************************************************************************
 * @brief	    Turn on/off CCLx.
 * @param[in]   CCLx: where x can be 0,1 to select the CCLx peripheral.
 * @param[in] 	NewState: new state of truth table.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APX_CCL_Cmd(CCL0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void APX_CCL_Cmd(CCL_Struct* CCLx, FunctionalState NewState)
{
    CCLx->CCLx0.MBIT.EN = NewState;
}
///@}




/**
 * @name	CCL MUX input select
 *   		
 */ 
///@{  
/**
 *******************************************************************************
 * @brief	    Config CCL MUX2 source.
 * @param[in]   CCLx: where x can be 0,1 to select the CCLx peripheral.
 * @param[in] 	MUX2Sel: specifies the timer IC0's source  
 *  @arg\b      APX_MUX2_DISABLE: Disable CCL MUX2. 
 *  @arg\b      APX_MUX2_CCL_SEQ: CCL MUX2 is from CCLx_SEQ. 
 *  @arg\b      APX_MUX2_CCL_AO: CCL MUX2 is from CCLx_AO. 
 *  @arg\b      APX_MUX2_PC1: CCL MUX2 is from PC1. 
 *  @arg\b      APX_MUX2_PA10: CCL MUX2 is from PA10. 
 *  @arg\b      APX_MUX2_PB2: CCL MUX2 is from PB2. 
 *  @arg\b      APX_MUX2_PB10: CCL MUX2 is from PB10. 
 *  @arg\b      APX_MUX2_PE2: CCL MUX2 is from PE2. 
 *  @arg\b      APX_MUX2_ADC0_OUT: CCL MUX2 is from ADC0_OUT. 
 *  @arg\b      APX_MUX2_URT4_TX: CCL MUX2 is from URT4_TX. 
 *  @arg\b      APX_MUX2_SPI0_CLK: CCL MUX2 is from SPI0_CLK. 
 *  @arg\b      APX_MUX2_TM36_OC2: CCL MUX2 is from TM36_OC2. 
 *  @arg\b      APX_MUX2_TM20_OC00: CCL MUX2 is from TM20_OC00. 
 *  @arg\b      APX_MUX2_OBM_I1: CCL MUX2 is from OBM_I1. 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APX_CCLMUX2_Select(CCL1, APX_MUX2_PA10);
 * @endcode
 *******************************************************************************
 */
void APX_CCLMUX2_Select(CCL_Struct* CCLx, APX_CCL_MUX2Def MUX2Sel)
{
    CCLx->CCLx1.MBIT.MUX2 = MUX2Sel;
}

/**
 *******************************************************************************
 * @brief	    Config CCL MUX1 source.
 * @param[in]   CCLx: where x can be 0,1 to select the CCLx peripheral.
 * @param[in] 	MUX1Sel: specifies the timer IC0's source  
 *  @arg\b      APX_MUX1_DISABLE: Disable CCL MUX1. 
 *  @arg\b      APX_MUX1_CCL_SEQ: CCL MUX1 is from CCLx_SEQ. 
 *  @arg\b      APX_MUX1_CCL_AO: CCL MUX1 is from CCLx_AO. 
 *  @arg\b      APX_MUX1_PB3: CCL MUX1 is from PB3. 
 *  @arg\b      APX_MUX1_PA9: CCL MUX1 is from PA9. 
 *  @arg\b      APX_MUX1_PB1: CCL MUX1 is from PB1. 
 *  @arg\b      APX_MUX1_PB9: CCL MUX1 is from PB9. 
 *  @arg\b      APX_MUX1_PE1: CCL MUX1 is from PE1. 
 *  @arg\b      APX_MUX1_CMP1_OUT: CCL MUX1 is from CMP1_OUT. 
 *  @arg\b      APX_MUX1_URT1_TX: CCL MUX1 is from URT1_TX. 
 *  @arg\b      APX_MUX1_SPI0_MISO: CCL MUX1 is from SPI0_MISO. 
 *  @arg\b      APX_MUX1_TM36_OC10: CCL MUX1 is from TM36_OC10. 
 *  @arg\b      APX_MUX1_TM26_OC10: CCL MUX1 is from TM26_OC10. 
 *  @arg\b      APX_MUX1_OBM_I0: CCL MUX1 is from OBM_I0. 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APX_CCLMUX1_Select(CCL0, APX_MUX1_PB3);
 * @endcode
 *******************************************************************************
 */
void APX_CCLMUX1_Select(CCL_Struct* CCLx, APX_CCL_MUX1Def MUX1Sel)
{
    CCLx->CCLx1.MBIT.MUX1 = MUX1Sel;
}


/**
 *******************************************************************************
 * @brief	    Config CCL MUX0 source.
 * @param[in]   CCLx: where x can be 0,1 to select the CCLx peripheral.
 * @param[in] 	MUX0Sel: specifies the timer IC0's source  
 *  @arg\b      APX_MUX0_DISABLE: Disable CCL MUX0. 
 *  @arg\b      APX_MUX0_CCL_SEQ: CCL MUX0 is from CCLx_SEQ. 
 *  @arg\b      APX_MUX0_CCL_AO: CCL MUX0 is from CCLx_AO. 
 *  @arg\b      APX_MUX0_PB11: CCL MUX0 is from PB11. 
 *  @arg\b      APX_MUX0_PA8: CCL MUX0 is from PA8. 
 *  @arg\b      APX_MUX0_PB0: CCL MUX0 is from PB0. 
 *  @arg\b      APX_MUX0_PB8: CCL MUX0 is from PB8. 
 *  @arg\b      APX_MUX0_PE0: CCL MUX0 is from PE0. 
 *  @arg\b      APX_MUX0_CMP0_OUT: CCL MUX0 is from CMP1_OUT. 
 *  @arg\b      APX_MUX0_URT0_TX: CCL MUX0 is from URT1_TX. 
 *  @arg\b      APX_MUX0_SPI0_MOSI: CCL MUX0 is from SPI0_MOSI. 
 *  @arg\b      APX_MUX0_TM36_OC00: CCL MUX0 is from TM36_OC00. 
 *  @arg\b      APX_MUX0_TM26_OC00: CCL MUX0 is from TM26_OC00. 
 *  @arg\b      APX_MUX0_OBM_P0: CCL MUX0 is from OBM_P0. 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APX_CCLMUX0_Select(CCL1, APX_MUX0_PB8);
 * @endcode
 *******************************************************************************
 */
void APX_CCLMUX0_Select(CCL_Struct* CCLx, APX_CCL_MUX0Def MUX0Sel)
{
    CCLx->CCLx1.MBIT.MUX0 = MUX0Sel;
}

///@}







/**
 * @name	interrupt and flag (SET/CLEAR/Config) 
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    Config interrupt source (Enable/Disable).
 * @param[in] 	APXx: specifies the APX macro. 
 * @param[in] 	ITsrc: Enable/Disable interrupt source 
 *  @arg\b	    APX_CCL1_IE: CCL-1 output low-to-high detect interrupt enable.
 *  @arg\b	    APX_CCL0_IE: CCL-0 output low-to-high detect interrupt enable.
 *  @arg\b	    APX_ASB0_TIE: ASB channel-0 transmit data register empty interrupt.
 *  @arg\b	    APX_ASB1_TIE: ASB channel-1 transmit data register empty interrupt.
 *  @arg\b	    APX_ASB2_TIE: ASB channel-2 transmit data register empty interrupt.
 *  @arg\b	    APX_ASB3_TIE: ASB channel-3 transmit data register empty interrupt.
 *  @arg\b	    APX_ASB0_TCIE: ASB channel-0 transmission complete interrupt enable.
 *  @arg\b	    APX_ASB1_TCIE: ASB channel-1 transmission complete interrupt enable.
 *  @arg\b	    APX_ASB2_TCIE: ASB channel-2 transmission complete interrupt enable.
 *  @arg\b	    APX_ASB3_TCIE: ASB channel-3 transmission complete interrupt enable.
 * @param[in] 	NewState: new state of the APXx interrupt key.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APX_IT_Config(APX, APX_CCL0_IE, ENABLE);
 * @endcode
 *******************************************************************************
 */
void APX_IT_Config(APX_Struct* APXx, uint32_t ITsrc, FunctionalState NewState)
{
    if (NewState == ENABLE)
        APXx->INT.W |= ITsrc;
    else
        APXx->INT.W &= ~ITsrc;
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable all interrupt. 
 * @param[in] 	APXx: specifies the APX macro. 
 * @param[in] 	NewState: new state of the APXx all interrupt key.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none.
 * @note 
 * @par         Example
 * @code
    APX_ITEA_Cmd(APX, ENABLE);
 * @endcode
 *******************************************************************************
 */
void APX_ITEA_Cmd(APX_Struct* APXx, FunctionalState NewState)
{
    APXx->INT.MBIT.IEA = NewState;
}

/**
 *******************************************************************************
 * @brief	    Get one interrupt source state.
 * @param[in] 	APXx: specifies the APX macro.
 * @param[in] 	ITSrc: interrupt source item
 *  @arg\b	    APX_CCL1F: CCL-1 output low-to-high detect flag.
 *  @arg\b	    APX_CCL0F: CCL-0 output low-to-high detect flag.
 *  @arg\b	    APX_ASB0_TXF: ASB channel-0 transmit data threshold low flag.
 *  @arg\b	    APX_ASB1_TXF: ASB channel-1 transmit data threshold low flag.
 *  @arg\b	    APX_ASB2_TXF: ASB channel-2 transmit data threshold low flag.
 *  @arg\b	    APX_ASB3_TXF: ASB channel-3 transmit data threshold low flag.
 *  @arg\b	    APX_ASB0_TCF: ASB channel-0 transmission complete flag.
 *  @arg\b	    APX_ASB1_TCF: ASB channel-1 transmission complete flag.
 *  @arg\b	    APX_ASB2_TCF: ASB channel-2 transmission complete flag.
 *  @arg\b	    APX_ASB3_TCF: ASB channel-3 transmission complete flag.
 * @return 	    reference define of DRV_Return.
 *  @arg        DRV_Happened : Happen. 
 *  @arg        DRV_UnHappened : Unhappen.
 * @note 
 * @par         Example
 * @code
    if(APX_GetSingleFlagStatus(APX, APX_CCL0F) == DRV_Happened)
    {
        // to do ...
    }   
 * @endcode
 *******************************************************************************
 */
DRV_Return APX_GetSingleFlagStatus(APX_Struct* APXx, uint32_t ITSrc)
{
    if (APXx->STA.W & ITSrc)
        return DRV_Happened;
    else 
        return DRV_UnHappened;
    
}

/**
 *******************************************************************************
 * @brief	    Get all interrupt source state.
 * @param[in] 	APXx: specifies the APX macro.
 * @return 	    response what happended of STA.
 * @note 
 * @par         Example
 * @code
    tmp = APX_GetAllFlagStatus(APX);
 * @endcode
 *******************************************************************************
 */
uint32_t APX_GetAllFlagStatus(APX_Struct* APXx)
{
    return APXx->STA.W;
}

/**
 *******************************************************************************
 * @brief	    Clear one or all interrupt source state.
 * @param[in] 	APXx: specifies the APX macro.
 * @param[in] 	APX_ITSrc: interrupt source item
 *  @arg\b	    APX_CCL1F: CCL-1 output low-to-high detect flag.
 *  @arg\b	    APX_CCL0F: CCL-0 output low-to-high detect flag.
 *  @arg\b	    APX_ASB0_TXF: ASB channel-0 transmit data threshold low flag.
 *  @arg\b	    APX_ASB1_TXF: ASB channel-1 transmit data threshold low flag.
 *  @arg\b	    APX_ASB2_TXF: ASB channel-2 transmit data threshold low flag.
 *  @arg\b	    APX_ASB3_TXF: ASB channel-3 transmit data threshold low flag.
 *  @arg\b	    APX_ASB0_TCF: ASB channel-0 transmission complete flag.
 *  @arg\b	    APX_ASB1_TCF: ASB channel-1 transmission complete flag.
 *  @arg\b	    APX_ASB2_TCF: ASB channel-2 transmission complete flag.
 *  @arg\b	    APX_ASB3_TCF: ASB channel-3 transmission complete flag.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APX_ClearFlag(APX, APX_OBM1F);
 * @endcode
 *******************************************************************************
 */
void APX_ClearFlag(APX_Struct* APXx, uint32_t APX_ITSrc)
{
    APXx->STA.W = APX_ITSrc;
}

///@}

#if defined(APX_CR0_ASB0_ENX_mask_w)
/**
 * @name  ASB Control
 *             
 */ 
///@{
/**
 *******************************************************************************
 * @brief	    ASB configure
 * @param[in]   ASB_Type :
 *   @arg\b     SyncCode : Specifies ASB SYNC code
 *       \n     - ASB_SYNCCODE_CODE0 : ASB SYNC code is code0.
 *       \n     - ASB_SYNCCODE_CODE1 : ASB SYNC code is code1.
 *          
 *   @arg\b     IdleStatus : Specifies ASB IDLE state level
 *       \n     - ASB_IDLESTATUS_LOW : ASB IDLE status level is low.
 *       \n     - ASB_IDLESTATUS_HIGH: ASB IDLE status level is high.
 *  
 *   @arg\b     ResetStatus : Specifies ASB Reset code level
 *       \n     - ASB_RSTSTATUS_LOW : ASB Reset status is low.
 *       \n     - ASB_RSTSTAUTS_HIGH: ASB Reset status is high.
 *  
 *   @arg\b     ResetSync : Specifies ASB RESET code that whether synchronous or not.
 *       \n     - ASB_RST_SYNC_ENABLE : ASB Reset code synchronous mode enable.
 *       \n     - ASB_RST_SYNC_DISABLE: ASB Reset code synchronous mode disable.
 *  
 *   @arg\b     ClockInverse : Specifies ASB shift clock output signal , whether inverse or not.
 *       \n     - ASB_CLOCK_INVERSE_ENABLE : ASB shift clock output signal inverse.
 *       \n     - ASB_CLOKC_INVERSE_DISABLE: ASB shift clock output signal no inverse.
 *  
 *   @arg\b     BitTimeCounter : 1 ~ 8  (Specifies ASB output bit time counter.)
 *  
 *   @arg\b     BitTimePrescaler : 2 ~ 32 (Specifies ASB output bit time prescaler.)
 *  
 *   @arg\b     ResetTime : 1 ~ 64 (Specifies ASB reset code time.)
 *  
 *   @arg\b     Code1_HighWidthTime : 1 ~ 32 (Specifies ASB Code 1 high time.)
 *  
 *   @arg\b     Code0_HighWidthTime : 1 ~ 32 (Specifies ASB Code 0 high time.)
 * @return 	    
 * @note 
 * 1. Code 0  
 * ---------
 *   H           L
 * l-------l-------------l                   
 * l<------------------->l Bit time = ( BaudRatePrescaler * BaudRateCounter)
 * l<----->l Code 0 high time = ( BaudRatePrescaler * Code0_HighWidthTime)
 *
 * 2. Code 1   
 * --------------
 *   H               L
 * l------------|--------l
 * l<------------------->l Bit time = ( BaudRatePrescaler * BaudRateCounter)
 * l<---------->l Code 1 high time = ( BaudRatePrescaler * Code1_HighWidthTime)
 *
 * 3. Reset Signal = ( Bit time * ResetTime)
 *
 *  Note :
 *      1. BaudRateCounter has to larger than Code0_HighWidthTime. ( BaudRateCounter > Code0_HighWidthTime)
 *      2. BaudRateCounter has to larger than Code1_HighWidthTime. ( BaudRateCounter > Code1_HighWidthTime)      
 * @par       Example
 * @code    
     ASB_TypeDef  ASB_CTR;
     
     ASB_CTR.SyncCode            = ASB_SYNCCODE_CODE0;
     ASB_CTR.IdleStatus          = ASB_IDLESTATUS_LOW;
     ASB_CTR.ResetStatus         = ASB_RSTSTATUS_LOW;
     ASB_CTR.ResetSync           = ASB_RST_SYNC_DISABLE;
     ASB_CTR.ClockInverse        = ASB_CLOKC_INVERSE_DISABLE;
     ASB_CTR.BitTimePrescaler    = 2  - 1; 
     ASB_CTR.BitTimeCounter      = 30 - 1;                      // Bit time = 1.25us  in 48MHz
     ASB_CTR.ResetTime           = 40 - 1;                      // Reset time = 50us in 48MHz
     ASB_CTR.Code0_HighWidthTime = 8  - 1;                      // Code0's T0H is about 0.33us in 48MHz
     ASB_CTR.Code1_HighWidthTime = 22 - 1;                      // Code1's T1H is about 9.17us in 48Mhz
     APX_ASB_Config(&ASB_CTR);
 
 * @endcode
 *******************************************************************************
 */
void APX_ASB_Config( ASB_TypeDef *ASB_Type)
{   
   
   APX->CR0.B[3] = ( ASB_Type->SyncCode | ASB_Type->IdleStatus | ASB_Type->ResetStatus | ASB_Type->ClockInverse );
   
   APX->CR1.B[0] = ASB_Type->Code0_HighWidthTime;
   APX->CR1.B[1] = ASB_Type->Code1_HighWidthTime;
   APX->CR1.B[2] = ASB_Type->ResetTime;

   APX->CR1.B[3] = ((uint8_t)((ASB_Type->BitTimeCounter  << APX_CR1_ASB_CNT_shift_b3)) | (ASB_Type->BitTimePrescaler));
}

/**
 *******************************************************************************
 * @brief	    ASB channel configure.
 * @param[in]   ASB_Chx: ASB channel handle ( 0 ~ 3)
 * @param[in]   ASBChannel_Type 
 *   @arg\b     TX_FIFOThreshold : Specifies ASB channel data FIFO low threshold for transmitted.
 *       \n     - ASB_TX_FIFOTHRESHOLD_0BYTE : ASB channel data FIFO low threshold is 0 bytes.
 *       \n     - ASB_TX_FIFOTHRESHOLD_2BYTE : ASB channel data FIFO low threshold is 2 bytes.
 *  
 *   @arg\b     DataOrder : Specifies ASB channel data order.
 *       \n     - : ASB_DATA_MSB : ASB channel data order is MSB.
 *       \n     - : ASB_DATA_LSB : ASB channel data order is LSB
 *  
 *   @arg\b     DataInverse : Specifies ASB channel output data that whether inverse or not.
 *       \n     - : ASB_DATA_INVERSE_ENABLE  : ASB channel data reverse.
 *       \n     - : ASB_DATA_INVERSE_DISABLE : ASB channel data no reverse.
 *  
 *   @arg\b     SignalInverse : Specifies ASB channel signal that whether inverse or not.
 *       \n     - : ASB_SIGNAL_INVERSE_ENABLE  : ASB channel output signal inverse.
 *       \n     - : ASB_SIGNAL_INVERSE_DISABLE : ASB channel output signal no inverse.
 *  
 *   @arg\b     PixelLength : Specifies ASB channel pixel length
 *       \n     - : ASB_FRAME_PIXEL_4BYTE : ASB channel pixel length is 4 bytes.
 *       \n     - : ASB_FRAME_PIXEL_3BYTE : ASB channel pixel length is 3 bytes.
 *  
 *   @arg\b     OutputMode : Specifies ASB channel output mode select.
 *       \n     - : ASB_MODE_ARGB  : ASB channel output mode is ARGB.
 *       \n     - : ASB_MODE_SHIFT : ASB channel output mode is SHIFT.
 *  
 * @return 	     
 * @note        No 
 * @par         Example
 * @code
    ASBChannel_TypeDef     ASBChannel0_CTR;
    
    ASBChannel0_CTR.OutputMode       = ASB_MODE_ARGB;
    ASBChannel0_CTR.DataOrder        = ASB_DATA_MSB;
    ASBChannel0_CTR.DataInverse      = ASB_DATA_INVERSE_DISABLE;
    ASBChannel0_CTR.SignalInverse    = ASB_SIGNAL_INVERSE_DISABLE;
    ASBChannel0_CTR.PixelLength      = ASB_FRAME_PIXEL_3BYTE;
    ASBChannel0_CTR.TX_FIFOThreshold = ASB_TX_FIFOTHRESHOLD_2BYTE;
    APX_ASBChannel_Config( 0 , &ASBChannel0_CTR);
 * @endcode
 *******************************************************************************
 */
void APX_ASBChannel_Config( uint8_t ASB_Chx , ASBChannel_TypeDef* ASBChannel_Type)
{
    uint32_t *ASBChannel_CR_Reg;
    
    ASBChannel_CR_Reg = (uint32_t*)(APX_ASBChannelCR0_Base + ( APX_ASBChannel_SHIFT * ASB_Chx)); 
    
    *ASBChannel_CR_Reg = *ASBChannel_CR_Reg & (~ASB_CHANNELCONFIG_MASK);
    *ASBChannel_CR_Reg = *ASBChannel_CR_Reg | (ASBChannel_Type->DataInverse      |
                                               ASBChannel_Type->DataOrder        |
                                               ASBChannel_Type->PixelLength      |
                                               ASBChannel_Type->OutputMode       |
                                               ASBChannel_Type->SignalInverse    |
                                               ASBChannel_Type->TX_FIFOThreshold);

}
/**
 *******************************************************************************
 * @brief	    ASB Channeln output enable or disable
 * @param[in]   ASB_Chx: The parameter can multiple choice.
 *    @arg\b    ASB_CHANNEL0_CMD_MASK:
 *    @arg\b    ASB_CHANNEL1_CMD_MASK:
 *    @arg\b    ASB_CHANNEL2_CMD_MASK:
 *    @arg\b    ASB_CHANNEL3_CMD_MASK:
 * @param[in]   ASB_Chx_Status :
 *    @arg\b    ENABLE:  ASB channel output enable.
 *    @arg\b    DISABLE: ASB channel output disable.
 * @return 	      
 * @note        
 * @par         Example
 * @code
       APX_ASBChannel_Cmd( (ASB_CHANNEL0_CMD_MASK | ASB_CHANNEL1_CMD_MASK) , ENABLE);    // ASB channel 0 and channel 1 enable together.

       or 

       APX_ASBChannel_Cmd( (ASB_CHANNEL2_CMD_MASK | ASB_CHANNEL3_CMD_MASK) , DISABLE);   // ASB channel 0 and channel 1 disable together.
 * @endcode
 *******************************************************************************
 */
void APX_ASBChannel_Cmd( uint8_t ASB_Chx , FunctionalState ASB_Chx_Status)
{
    uint32_t *ASB_DMA_Reg;
    
    ASB_DMA_Reg = (uint32_t*)(APX_ASBChannelCR0_Base + ( APX_ASBChannel_SHIFT * ASB_Chx)); 
    
    
    *ASB_DMA_Reg = ((*ASB_DMA_Reg & (~APX_ASB00_ASB0_EN_mask_w)) | (APX_ASB00_ASB0_EN_mask_w * ASB_Chx_Status));
}
/**
 *******************************************************************************
 * @brief	    Control DMA of ASB channel, whether enable or not.
 * @param[in]   ASB_Chx (0 ~ 3): select the ASB channel peripheral.
 * @param[in]   ASB_ChxDMA_Status:
 *   @arg\b     ENABLE:  Enable DMA of the ASB channel.
 *   @arg\b     DISABLE: Disable DMA of the ASB channel.
 * @return 	      
 * @note        No
 * @par         Example
 * @code
     APX_ASBChannel_DMA_Cmd( 0 , ENABLE);    // Enable DMA of ASB Channel 0

     or

     APX_ASBChannel_DMA_Cmd( 1 , DISABLE);   // Disable DMA of ASB Channel 1
 * @endcode
 *******************************************************************************
 */
void APX_ASBChannel_DMA_Cmd( uint32_t ASB_Chx , FunctionalState ASB_ChxDMA_Status)
{
    uint32_t *ASB_DMA_Reg;
    
    ASB_DMA_Reg = (uint32_t*)(APX_ASBChannelCR0_Base + ( APX_ASBChannel_SHIFT * ASB_Chx)); 
    
    
    *ASB_DMA_Reg = ((*ASB_DMA_Reg & (~APX_ASB00_ASB0_DMAEN_mask_w)) | (APX_ASB00_ASB0_DMAEN_mask_w * ASB_ChxDMA_Status));
}

/**
 *******************************************************************************
 * @brief	    Clear FIFO of ASB Channel   
 * @param[in]   ASB_Chx (0 ~ 3): select the ASB channel peripheral.  
 * @return 	      
 * @note        No
 * @par         Example
 * @code
     APX_ASBChannel_ClearFIFO( 2);     // Clear FIFO of ASB channel2. 
 * @endcode
 *******************************************************************************
 */
void APX_ASBChannel_ClearFIFO( uint32_t ASB_Chx)
{
    uint32_t *ASB_ClearFIFO_Reg;
    
    ASB_ClearFIFO_Reg = (uint32_t*)(APX_ASBChannelCR0_Base + ( APX_ASBChannel_SHIFT * ASB_Chx));
    
    *ASB_ClearFIFO_Reg = *ASB_ClearFIFO_Reg | APX_ASB00_ASB0_FCLR_mask_w;
}
/**
 *******************************************************************************
 * @brief	  Software trigger reset code.   
 * @param[in] ASB_Chx (0 ~ 3): select the ASB channel peripheral.
 * @return 	    
 * @note      No
 * @par       Example
 * @code
     APX_ASBChannel_TriggerResetSignal( 1);    // Trigger ASB channel0 to send Reset code  
 * @endcode
 *******************************************************************************
 */
void APX_ASBChannel_TriggerResetSignal( uint32_t ASB_Chx)
{
    uint32_t *ASB_TriggerRst_Reg;
    
    ASB_TriggerRst_Reg = (uint32_t*)(APX_ASBChannelCR0_Base + ( APX_ASBChannel_SHIFT * ASB_Chx));         
    
    *ASB_TriggerRst_Reg = *ASB_TriggerRst_Reg | APX_ASB00_ASB0_RSTTX_mask_w;
}

/**
 *******************************************************************************
 * @brief	    Get status that software trigger reset code.  
 * @param[in]   ASB_Chx (0 ~ 3): select the ASB channel peripheral.  
 * @return 	      
 *   @arg\b     0: The Reset code already completed.
 *   @arg\b     1: The Reset code sends not finish yet.
 * @note        No 
 * @par         Example
 * @code    
       if( APX_ASBChannel_GetResetStatus(0) == 1)      // ASB Channel0 Reset code sends not finish yet.      
       {
           // to do......
       }
 * @endcode
 *******************************************************************************
 */
uint8_t APX_ASBChannel_GetResetStatus( uint32_t ASB_Chx)
{
    uint8_t *ASB_GetReset_Reg;
    
    ASB_GetReset_Reg = (uint8_t*)((APX_ASBChannelCR0_Base + APX_ASBChannelCR0_RSTTX_SHIFT) + ( APX_ASBChannel_SHIFT * ASB_Chx));   
    
    return( ( (*ASB_GetReset_Reg) & APX_ASB00_ASB0_RSTTX_send_b1));
}

/**
 *******************************************************************************
 * @brief	    Control ASB Channel auto to send Reset code after how many pixel sizes already send.
 * @param[in]   ASB_Chx (0 ~ 3): select the ASB channel peripheral.
 * @param[in]   ASBChannel_FrameSize ( 1 ~ 256): Set Pixel sizes. 
 * @return 	      
 * @note        No
 * @par         Example
 * @code
       APX_ASBChannel_SetFrameSize( 1 , 20);   // ASB channel0 auto to send Reset code after 30 byte pixel already sends.
 * @endcode
 *******************************************************************************
 */
void APX_ASBChannel_SetFrameSize( uint32_t ASB_Chx , uint8_t ASBChannel_FrameSize)
{
    uint8_t *ASB_FrameSize_Reg;
    
    ASB_FrameSize_Reg = (uint8_t*)(APX_ASBChannelPCNT_Base + ( APX_ASBChannel_SHIFT * ASB_Chx));

    *ASB_FrameSize_Reg = ASBChannel_FrameSize;
}

/**
 *******************************************************************************
 * @brief	    Control ASB channel to send data.  
 * @param[in]   ASB_Chx (0 ~ 3): select the ASB channel peripheral.
 * @param[in]   ASB_Data : Transfer data.
 * @return 	    
 * @note        No  
 * @par         Example
 * @code      
       APX_ASBChannel_SendData( 0 , 0x55)    // ASB Channel0 send 0x55.
 * @endcode
 *******************************************************************************
 */
void APX_ASBChannel_SendData( uint32_t ASB_Chx , uint8_t ASB_Data)
{
    APX->ASBDAT.B[ASB_Chx] = ASB_Data;   
}

/**
 *******************************************************************************
 * @brief	    Control all ASB channel to send data.
 * @param[in]   ASB_Data : Transfer data. 
 * @return 	      
 * @note        No
 * @par         Example
 * @code
       APX_ASBAllChannel_SendData(0x12345678);   // ASB Channel 0 send 0x78.
                                                // ASB Channel 1 send 0x56.
                                                // ASB Channel 2 send 0x34.
                                                // ASB Channel 3 send 0x12.
 * @endcode
 *******************************************************************************
 */
void APX_ASBAllChannel_SendData( uint32_t ASB_Data)
{
    APX->ASBDAT.W = ASB_Data;
}

///@}
#endif
