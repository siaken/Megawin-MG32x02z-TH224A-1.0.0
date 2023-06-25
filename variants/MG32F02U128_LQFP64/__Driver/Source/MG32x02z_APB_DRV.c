/**
 ******************************************************************************
 *
 * @file        MG32x02z_APB_DRV.c
 *
 * @brief       This file provides firmware functions to manage the following 
 *              functionalities of the APB peripheral:
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.16
 * @date        2021/09/08
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


#include "MG32x02z_APB_DRV.h"


/**
 * @name	relevant to Timer
 *   		
 */ 
///@{  
/**
 *******************************************************************************
 * @brief	    Starup TimerX Simultaneously by this function
 * @param[in] 	TMxEnBit: specifies main/2nd Timer/Counter Enable bit
 *  @arg\b      APB_TM36_EN2: TM36 2nd Timer/Counter enable bit
 *  @arg\b      APB_TM26_EN2: TM26 2nd Timer/Counter enable bit
 *  @arg\b      APB_TM20_EN2: TM20 2nd Timer/Counter enable bit
 *  @arg\b      APB_TM16_EN2: TM16 2nd Timer/Counter enable bit
 *  @arg\b      APB_TM10_EN2: TM10 2nd Timer/Counter enable bit
 *  @arg\b      APB_TM01_EN2: TM01 2nd Timer/Counter enable bit
 *  @arg\b      APB_TM00_EN2: TM00 2nd Timer/Counter enable bit
 *  @arg\b      APB_TM36_EN: TM36 main Timer/Counter enable bit
 *  @arg\b      APB_TM26_EN: TM26 main Timer/Counter enable bit
 *  @arg\b      APB_TM20_EN: TM20 main Timer/Counter enable bit
 *  @arg\b      APB_TM16_EN: TM16 main Timer/Counter enable bit
 *  @arg\b      APB_TM10_EN: TM10 main Timer/Counter enable bit
 *  @arg\b      APB_TM01_EN: TM01 main Timer/Counter enable bit
 *  @arg\b      APB_TM00_EN: TM00 main Timer/Counter enable bit
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    // Startup TM00
    APB_TimerX_Cmd(APB_TM00_EN | APB_TM00_EN2);
 * @endcode
 *******************************************************************************
 */
void APB_TimerX_Cmd(uint32_t TMxEnBit)
{
    APB->CR1.W |= TMxEnBit;
}

/**
 *******************************************************************************
 * @brief	    Config ITR6 source 
 * @param[in] 	ITR6Src: specifies ITR6 source 
 *  @arg\b      ITR6_TM00_TRGO: TM00's TRGO signal
 *  @arg\b      ITR6_TM10_TRGO: TM10's TRGO signal
 *  @arg\b      ITR6_TM20_TRGO: TM20's TRGO signal
 *  @arg\b      ITR6_TM36_TRGO: TM36's TRGO signal
 *  @arg\b      ITR6_INT_PB: INT_PB signal
 *  @arg\b      ITR6_URT1_TMO: URT1's TMO signal
 *  @arg\b      ITR6_URT2_BRO: URT2's BRO signal
 *  @arg\b      ITR6_URT2_TMO: URT2's TMO signal
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_ITR6_Select(ITR6_TM10_TRGO);
 * @endcode
 *******************************************************************************
 */
void APB_ITR6_Select(APB_TimerITR6SrcDef ITR6Src)
{
    APB->CR2.MBIT.ITR6_MUX = ITR6Src;
}

/**
 *******************************************************************************
 * @brief	    Config ITR7 source 
 * @param[in] 	ITR7Src: specifies ITR7 source 
 *  @arg\b      ITR7_TM01_TRGO: TM01's TRGO signal
 *  @arg\b      ITR7_TM16_TRGO: TM16's TRGO signal
 *  @arg\b      ITR7_TM26_TRGO: TM26's TRGO signal
 *  @arg\b      ITR7_ADC0_OUT: ADC0_OUT signal
 *  @arg\b      ITR7_INT_PD: INT_PD signal
 *  @arg\b      ITR7_URT1_BRO: URT1's BRO signal
 *  @arg\b      ITR7_URT3_BRO: URT3's BRO signal 
 *  @arg\b      ITR7_URT3_TMO: URT3's TMO signal 
 *  @arg\b      ITR7_ICKO_INT: ICKO interrupt event
 *  @arg\b      ITR7_RTC_OUT: RTC Output signal
 *  @arg\b      ITR7_TM36_XOR: ITR7_TM36_XOR
 *  @arg\b      ITR7_NCO0_OUT: NCO0_OUT
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_ITR7_Select(ITR7_TM16_TRGO);
 * @endcode
 *******************************************************************************
 */
void APB_ITR7_Select(APB_TimerITR7SrcDef ITR7Src)
{
    APB->CR2.MBIT.ITR7_MUX = ITR7Src;
}
///@}
	
	
/**
 * @name	Break singal source/inverse config
 *   		
 */ 
///@{  
/**
 *******************************************************************************
 * @brief	    Config Break signal source channel 0
 * @param[in]   OBMx: specifies the APB's OBMx macro
 *      	    This parameter can be OBMx where x: 1 to select the OBMx peripheral.
 * @param[in] 	BKS0Sel: specifies channel 0 source 
 *  @arg\b      BKS0_Logic_1: Output '1' state 
 *  @arg\b      BKS0_INT_PA: INT_PA signal state
 *  @arg\b      BKS0_INT_PC: INT_PC signal state
 *  @arg\b      BKS0_ADC0_OUT:  ADC0_OUT signal
 *  @arg\b      BKS0_TM00_TRGO: TM00's TRGO signal
 *  @arg\b      BKS0_TM10_TRGO: TM10's TRGO signal
 *  @arg\b      BKS0_TM20_TRGO: TM20's TRGO signal 
 *  @arg\b      BKS0_CCL_P0: CCL_P0 output state
 *  @arg\b      BKS0_TM20_OC00: TM20's OC00 output state
 *  @arg\b      BKS0_TM36_OC2: TM36's OC2 output state 
 *  @arg\b      BKS0_TM00_TRGO: TM00's TRGO signal
 *  @arg\b      BKS0_TM10_TRGO: TM10's TRGO signal
 *  @arg\b      BKS0_CMP0_OUT: CMP0's output state   
 *  @arg\b      BKS0_URT0_TX: URT0's TX signal
 *  @arg\b      BKS0_URT2_TX: URT2's TX signal
 *  @arg\b      BKS0_URT0_RX: URT0's RX signal
 *  @arg\b      BKS0_URT2_RX: URT2's RX signal
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_BreakSourceChannel0_Select(OBM1, BKS0_TM00_TRGO);
 * @endcode
 *******************************************************************************
 */
void APB_BreakSourceChannel0_Select(OBM_Struct* OBMx, BKS0SrcDef BKS0Sel)
{
    OBMx->OBMx0.MBIT.BKS0 = BKS0Sel;
}

/**
 *******************************************************************************
 * @brief	    Config Break signal source channel 1
 * @param[in]   OBMx: specifies the APB's OBMx macro
 *      	    This parameter can be OBMx where x: 1 to select the OBMx peripheral.
 * @param[in] 	BKS1Sel: specifies channel 1 source 
 *  @arg\b      BKS1_Logic_1: Output '1' state  
 *  @arg\b      BKS1_INT_PB: INT_PB signal state  
 *  @arg\b      BKS1_INT_PD: INT_PD signal state  
 *  @arg\b      BKS1_INT_BOD1: BOD1 signal state  
 *  @arg\b      BKS1_TM01_TRGO: TM01's TRGO signal  
 *  @arg\b      BKS1_TM16_TRGO: TM16's TRGO signal  
 *  @arg\b      BKS1_TM26_TRGO: TM26's TRGO signal  
 *  @arg\b      BKS1_CCL_P1: CCL_P1 output state
 *  @arg\b      BKS1_TM20_OC10: TM20's OC10 output state   
 *  @arg\b      BKS1_TM36_OC3: TM36's OC3 output state  
 *  @arg\b      BKS1_CMP1_OUT: CMP1's output state   
 *  @arg\b      BKS1_URT1_TX: URT1's TX signal  
 *  @arg\b      BKS1_URT3_TX: URT3's TX signal  
 *  @arg\b      BKS1_URT1_RX: URT1's RX signal  
 *  @arg\b      BKS1_URT3_RX: URT3's RX signal  
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_BreakSourceChannel1_Select(OBM1, BKS1_TM01_TRGO);
 * @endcode
 *******************************************************************************
 */
void APB_BreakSourceChannel1_Select(OBM_Struct* OBMx, BKS1SrcDef BKS1Sel)
{
    OBMx->OBMx0.MBIT.BKS1 = BKS1Sel;
}

/**
 *******************************************************************************
 * @brief	    config Break signal source channel 2
 * @param[in]   OBMx: specifies the APB's OBMx macro
 *      	    This parameter can be OBMx where x: 1 to select the OBMx peripheral.
 * @param[in] 	BKS2Sel: specifies channel 2 source 
 *  @arg\b      BKS2_Logic_1: Output '1' state  
 *  @arg\b      BKS2_SPI0_MOSI: SPI0's MOSI output state  
 *  @arg\b      BKS2_TM36_TRGO: TM36's TRGO signal  
 *  @arg\b      BKS2_CMP2_OUT: CMP2's output state   
 *  @arg\b      BKS2_CMP3_OUT: CMP3's output state   
 *  @arg\b      BKS2_URT2_BRO: URT2's BRO signal  
 *  @arg\b      BKS2_URT2_TMO: URT2's TMO signal  
 *  @arg\b      BKS2_URT3_BRO: URT3's BRO signal  
 *  @arg\b      BKS2_URT3_TMO: URT3's TM0 signal  
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_BreakSourceChannel2_Select(OBM1, BKS2_TM36_TRGO);
 * @endcode
 *******************************************************************************
 */
void APB_BreakSourceChannel2_Select(OBM_Struct* OBMx, BKS2SrcDef BKS2Sel)
{
    OBMx->OBMx0.MBIT.BKS2 = BKS2Sel;
}
/**
 *******************************************************************************
 * @brief	    Inverse BKS0 output signal
 * @param[in]   OBMx: specifies the APB's OBMx macro
 *      	    This parameter can be OBMx where x: 1 to select the OBMx peripheral.
 * @param[in] 	NewState: config inverse function
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_InverseBKS0_Cmd(OBM1, ENABLE);
 * @endcode
 *******************************************************************************
 */
void APB_InverseBKS0_Cmd(OBM_Struct* OBMx, FunctionalState NewState)
{
    OBMx->OBMx0.MBIT.BKN0 = NewState;
}
/**
 *******************************************************************************
 * @brief	    Inverse BKS1 output signal
 * @param[in]   OBMx: specifies the APB's OBMx macro
 *      	    This parameter can be OBMx where x: 1 to select the OBMx peripheral.
 * @param[in] 	NewState: config inverse function
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_InverseBKS1_Cmd(OBM1, ENABLE);
 * @endcode
 *******************************************************************************
 */
void APB_InverseBKS1_Cmd(OBM_Struct* OBMx, FunctionalState NewState)
{
    OBMx->OBMx0.MBIT.BKN1 = NewState;
}
/**
 *******************************************************************************
 * @brief	    Inverse BKS2 output signal
 * @param[in]   OBMx: specifies the APB's OBMx macro
 *      	    This parameter can be OBMx where x: 1 to select the OBMx peripheral.
 * @param[in] 	NewState: config inverse function
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_InverseBKS2_Cmd(OBM1, ENABLE);
 * @endcode
 *******************************************************************************
 */
void APB_InverseBKS2_Cmd(OBM_Struct* OBMx, FunctionalState NewState)
{
    OBMx->OBMx0.MBIT.BKN2 = NewState;
}
///@}



/**
 * @name	config OBMx operation mode
 *   		
 */ 
///@{  
/**
 *******************************************************************************
 * @brief	    Config OBMx operation mode  
 * @param[in]   OBMx: specifies the APB's OBMx macro
 *      	    This parameter can be OBMx where x: 1 to select the OBMx peripheral.
 * @param[in] 	OPMode: specifies operation mode
 *  @arg\b      OBMx_LevelSwitch: operate in AND mode  
 *  @arg\b      OBMx_ClearByFallingEdge: accept falling edge to clear initial state  
 *  @arg\b      OBMx_SetByFallingEdge: accept falling edge to set initial state      
 *  @arg\b      OBMx_DualEdgeSwitch: accept falling edge to toggle initial state  
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_OBMxOpMode_Select(OBM1, OBMx_LevelSwitch);
 * @endcode
 *******************************************************************************
 */
void APB_OBMxOpMode_Select(OBM_Struct* OBMx, OBMxOperateModeTypedef OPMode)
{
    OBMx->OBMx0.MBIT.MDS = OPMode;
}
///@}



/**
 * @name	OBMx output signal control
 *   		
 */ 
///@{  
/**
 *******************************************************************************
 * @brief       Get OBMx output state 
 * @param[in]   OBMx: specifies the APB's OBMx macro
 *      	    This parameter can be OBMx where x: 1 to select the OBMx peripheral.
 * @return		return OBMx output 0/1 state 
 *  @arg        DRV_Logic1 : '1' 
 *  @arg        DRV_Logic0 : '0'
 * @note 
 * @par         Example
 * @code
    tmp = APB_OBMxOpMode_Select(OBM1);
 * @endcode
 *******************************************************************************
 */
DRV_Return APB_GetOBMxOutputState(OBM_Struct* OBMx)
{
#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
    if (OBMx == OBM0)
    {
        if (APB->STA.MBIT.OBM0_OUT)
            return DRV_Logic1;
        else 
            return DRV_Logic0;
    }
#endif    
    if ((APB->STA.MBIT.OBM1_OUT) && (OBMx == OBM1))
        return DRV_Logic1;
    else 
        return DRV_Logic0;
}

/**
 *******************************************************************************
 * @brief	    Inverse OBMx output signal
 * @param[in]   OBMx: specifies the APB's OBMx macro
 *      	    This parameter can be OBMx where x: 1 to select the OBMx peripheral.
 * @param[in] 	NewState: config inverse function
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_InverseOBMxOutput_Cmd(OBM1, DISABLE);
 * @endcode
 *******************************************************************************
 */
void APB_InverseOBMxOutput_Cmd(OBM_Struct* OBMx, FunctionalState NewState)
{
    OBMx->OBMx1.MBIT.POL = NewState;
}
/**
 *******************************************************************************
 * @brief	    Config OBMx output with clock filter   
 * @param[in]   OBMx: specifies the APB's OBMx macro
 *      	    This parameter can be OBMx where x: 1 to select the OBMx peripheral.
 * @param[in] 	FilterClks: specifies filter clock source 
 *  @arg\b      OBMx_FilterDisable: Disable clock filter  
 *  @arg\b      OBMx_APBCLKx3: filter clock by APB clock x 3  
 *  @arg\b      OBMx_APBCLKx24: filter clock by APB clock x 8 x 3  
 *  @arg\b      OBMx_TM00_TRGOx3: filter clock by TM00 TRGO x 3  
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_OutputFilter_Select(OBM1, OBMx_APBCLKx3);
 * @endcode
 *******************************************************************************
 */
void APB_OutputFilter_Select(OBM_Struct* OBMx, OBMxFilterTypedef FilterClks)
{
    OBMx->OBMx1.MBIT.FCKS = FilterClks;
}
///@}

/**
 * @name	update or get signal state
 *   		
 */ 
///@{  
/**
 *******************************************************************************
 * @brief       Get OBMx switch state 
 * @param[in]   OBMx: specifies the APB's OBMx macro
 *      	    This parameter can be OBMx where x: 1 to select the OBMx peripheral.
 * @return		return OBMx switch 0/1 state 
 *  @arg        DRV_Logic1 : '1' 
 *  @arg        DRV_Logic0 : '0'
 * @note 
 * @par         Example
 * @code
    tmp = APB_GetOBMxSwitchState(OBM1);
 * @endcode
 *******************************************************************************
 */
DRV_Return APB_GetOBMxSwitchState(OBM_Struct* OBMx)	
{
#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
    if(OBMx == OBM0)
    {
        if(APB->STA.MBIT.OBM0_SW)
            return DRV_Logic1;
        else 
            return DRV_Logic0;
    }
    
#endif    
    if ((APB->STA.MBIT.OBM1_SW) && (OBMx == OBM1))
        return DRV_Logic1;
    else 
        return DRV_Logic0;
    
}

/**
 *******************************************************************************
 * @brief       Update OBMx initial state
 * @param[in]   OBMx: specifies the APB's OBMx macro
 *      	    This parameter can be OBMx where x: 1 to select the OBMx peripheral.
 * @param[in]   CurSta: specifies the initial channel. 
 *              This parameter can be: SET or CLR.
 * @return		none
 * @note 
 * @par         Example
 * @code
    APB_SetOBMxInitState(OBM1, CLR);
 * @endcode
 *******************************************************************************
 */
void APB_SetOBMxInitState(OBM_Struct* OBMx, BitAction CurSta)
{
    uint8_t RegT;
    
    RegT = OBMx->OBMx0.B[0] | APB_OBMx_unlocked;
    
    if (CurSta == SET)
        RegT |= APB_OBMx_initial_1;
    else
        RegT &= ~APB_OBMx_initial_1;
    
    OBMx->OBMx0.B[0] = RegT;
    
}

/**
 *******************************************************************************
 * @brief       Get OBMx initial state 
 * @param[in]   OBMx: specifies the APB's OBMx macro
 *      	    This parameter can be OBMx where x: 1 to select the OBMx peripheral.
 * @return		return OBMx initial state 
 *  @arg        DRV_Logic1 : '1' 
 *  @arg        DRV_Logic0 : '0'
 * @note 
 * @par         Example
 * @code
    tmp = APB_GetOBMxInitState(OBM1);
 * @endcode
 *******************************************************************************
 */
DRV_Return APB_GetOBMxInitState(OBM_Struct* OBMx)	
{
    if (OBMx->OBMx0.MBIT.STA)
        return DRV_Logic1;
    else 
        return DRV_Logic0;
    
}
///@}


/**
 * @name	config OBMx output channel 0/1 source / inverse function
 *   		
 */ 
///@{  
/**
 *******************************************************************************
 * @brief	    Config output channel 0 source.
 * @param[in]   OBMx: specifies the APB's OBMx macro
 *      	    This parameter can be OBMx where x: 1 to select the OBMx peripheral.
 * @param[in] 	OBM0LSSel: specifies output channel 0 source 
 *  @arg\b      OBMxCH0_Logic_0: Output '0' state  
 *  @arg\b      OBMxCH0_INT_PA: Output INT_PA state  
 *  @arg\b      OBMxCH0_INT_PC: Output INT_PC state  
 *  @arg\b      OBMxCH0_TM00_CKO: Output TM00_CKO state  
 *  @arg\b      OBMxCH0_TM10_CKO: Output TM10_CKO state  
 *  @arg\b      OBMxCH0_TM20_CKO: Output TM20_CKO state  
 *  @arg\b      OBMxCH0_TM36_CKO: Output TM36_CKO state  
 *  @arg\b      OBMxCH0_TM20_OC00: Output TM20_OC00 state  
 *  @arg\b      OBMxCH0_TM36_OC00: Output TM36_OC00 state  
 *  @arg\b      OBMxCH0_TM36_OC2: Output TM20_OC2 state  
 *  @arg\b      OBMxCH0_OBM_I0: Output OBMx Break Signal Input channel 0 state  
 *  @arg\b      OBMxCH0_ITR6: Output ITR6 state  
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_OutputChannel0Source_Select(OBM1, OBMxCH0_TM10_CKO);
 * @endcode
 *******************************************************************************
 */
void APB_OutputChannel0Source_Select(OBM_Struct* OBMx, OBMxChannel0TypeDef OBM0LSSel)
{
    OBMx->OBMx1.MBIT.MUX0 = OBM0LSSel;
}

/**
 *******************************************************************************
 * @brief	    Config output channel 1 source.
 * @param[in]   OBMx: specifies the APB's OBMx macro
 *      	    This parameter can be OBMx where x: 1 to select the OBMx peripheral.
 * @param[in] 	OBM0HSSel: specifies output channel 0 source 
 *  @arg\b      OBMxCH1_Logic_0: Output '0' state 
 *  @arg\b      OBMxCH1_INT_PB: Output INT_PB state 
 *  @arg\b      OBMxCH1_INT_PD: Output INT_PD state 
 *  @arg\b      OBMxCH1_TM01_CKO: Output TM01_CKO state 
 *  @arg\b      OBMxCH1_TM16_CKO: Output TM16_CKO state 
 *  @arg\b      OBMxCH1_TM26_CKO: Output TM26_CKO state 
 *  @arg\b      OBMxCH1_TM20_OC01: Output TM20_OC01 state 
 *  @arg\b      OBMxCH1_TM36_OC01: Output TM36_OC01 state 
 *  @arg\b      OBMxCH1_TM36_OC3: Output TM20_OC3 state 
 *  @arg\b      OBMxCH1_OBM_I1: Output OBMx Break Signal Input channel 1 state 
 *  @arg\b      OBMxCH1_ITR7: Output ITR7 state 
 *  @arg\b      OBMxCH1_ICKO_INT: Output ICKO_INT state 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_OutputChannel1Source_Select(OBM1, OBMxCH1_TM01_CKO);
 * @endcode
 *******************************************************************************
 */
void APB_OutputChannel1Source_Select(OBM_Struct* OBMx, OBMxChannel1TypeDef OBM0HSSel)
{
    OBMx->OBMx1.MBIT.MUX1 = OBM0HSSel;
}

/**
 *******************************************************************************
 * @brief	    Inverse output channel 0  
 * @param[in]   OBMx: specifies the APB's OBMx macro
 *      	    This parameter can be OBMx where x: 1 to select the OBMx peripheral.
 * @param[in] 	NewState: config inverse function
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_InverseOutputChannel0_Cmd(OBM1, DISABLE);
 * @endcode
 *******************************************************************************
 */
void APB_InverseOutputChannel0_Cmd(OBM_Struct* OBMx, FunctionalState NewState)
{
    OBMx->OBMx1.MBIT.INV0 = NewState;
}

/**
 *******************************************************************************
 * @brief	    Inverse output channel 1 
 * @param[in]   OBMx: specifies the APB's OBMx macro
 *      	    This parameter can be OBMx where x: 1 to select the OBMx peripheral.
 * @param[in] 	NewState: config inverse function
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_InverseOutputChannel1_Cmd(OBM1, DISABLE);
 * @endcode
 *******************************************************************************
 */
void APB_InverseOutputChannel1_Cmd(OBM_Struct* OBMx, FunctionalState NewState)
{
    OBMx->OBMx1.MBIT.INV1 = NewState;
}
///@}



/**
 * @name	APB's IR peripheral
 *   		
 */ 
///@{  
/**
 *******************************************************************************
 * @brief       Select IRCLK source
 * @param[in] 	IRCLKSel: config IRCLK source.
 *  @arg\b      IRCLK_Logic_0:  Output '0' state 
 *  @arg\b      IRCLK_TM00_CKO: TM00's CKO signal
 *  @arg\b      IRCLK_TM01_CKO: TM01's CKO signal
 *  @arg\b      IRCLK_TM10_CKO: TM10's CKO signal
 *  @arg\b      IRCLK_TM16_TRGO: TM16's TRGO signal
 *  @arg\b      IRCLK_URT1_TMO: URT1's TMO signal
 *  @arg\b      IRCLK_URT2_TMO: URT2's TMO signal
 *  @arg\b      IRCLK_URT3_TMO: URT3's TMO signal
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_IRCLK_Select(IRCLK_TM00_CKO);
 * @endcode
 *******************************************************************************
 */
void APB_IRCLK_Select(IRCLKSrcDef IRCLKSel)
{
    APB->CR0.MBIT.IRCLK_MUX = IRCLKSel;
}

/**
 *******************************************************************************
 * @brief       Select IRDAT source
 * @param[in] 	IRDATSel: config IRDAT source.
 *  @arg\b      IRDAT_Logic_0: Output '0' state 
 *  @arg\b      IRDAT_TM20_TRGO: TM20's TRGO signal
 *  @arg\b      IRDAT_TM26_TRGO: TM26's TRGO signal
 *  @arg\b      IRDAT_TM36_TRGO: TM36's TRGO signal
 *  @arg\b      IRDAT_SPI0_MOSI: SPIO's MOSI signal
 *  @arg\b      IRDAT_URT1_TX: URT1's TX signal
 *  @arg\b      IRDAT_URT2_TX: URT2's TX signal
 *  @arg\b      IRDAT_URT3_TX: URT3's TX signal
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_IRCLK_Select(IRDAT_TM20_TRGO);
 * @endcode
 *******************************************************************************
 */
void APB_IRDAT_Select(IRDATSrcDef IRDATSel)
{
    APB->CR0.MBIT.IRDAT_MUX = IRDATSel;
}
	
/**
 *******************************************************************************
 * @brief	    Inverse IRCLK output signal
 * @param[in] 	NewState: config inverse function
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_InverseIRCLK_Cmd(DISABLE);
 * @endcode
 *******************************************************************************
 */
void APB_InverseIRCLK_Cmd(FunctionalState NewState)
{
    APB->CR0.MBIT.IRCLK_INV = NewState;
}

/**
 *******************************************************************************
 * @brief	    Inverse IRDAT output signal
 * @param[in] 	NewState: config inverse function
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_InverseIRDAT_Cmd(DISABLE); 
 * @endcode
 *******************************************************************************
 */
void APB_InverseIRDAT_Cmd(FunctionalState NewState)
{
    APB->CR0.MBIT.IRDAT_INV = NewState;
}
///@}



#if defined(MG32_3RD) || defined(MG32_4TH)
/**
 * @name	APB's NCO peripheral
 *   		
 */ 
///@{  
/**
 *******************************************************************************
 * @brief       Select NCO input clock source.
 * @param[in] 	NCOClkSrc: config NCO clock.
 *  @arg\b      APB_NCO_IHRCO:  Output '0' state 
 *  @arg\b      APB_NCO_CK_PLL: TM00's CKO signal
 *  @arg\b      APB_NCO_APB: TM01's CKO signal
 *  @arg\b      APB_NCO_CK_LS: TM10's CKO signal
 *  @arg\b      APB_NCO_TM00_TRGO: TM16's TRGO signal
 *  @arg\b      APB_NCO_CK0: URT1's TMO signal
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_NCOClockSource_Select(APB_NCO_APB);
 * @endcode
 *******************************************************************************
 */
void APB_NCOClockSource_Select(APB_NCOInputClockSrcDef NCOClkSrc)
{
    APB->NCO00.MBIT.NCO0_CKS = NCOClkSrc;
}

/**
 *******************************************************************************
 * @brief       Select NCO output mode.
 * @param[in] 	NCOOutMode: config IRDAT source.
 *  @arg\b      APB_NCO_FDC: fixed duty cycle mode.
 *  @arg\b      APB_NCO_PFM: pulse frequency mode.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_NCOOutputMode_Select(APB_NCO_FDC);
 * @endcode
 *******************************************************************************
 */
void APB_NCOOutputMode_Select(APB_NCOOutputMode NCOOutMode)
{
    APB->NCO00.MBIT.NCO0_MDS = NCOOutMode;
}
	
/**
 *******************************************************************************
 * @brief	    Inverse NCO output.
 * @param[in] 	NewState: config inverse function
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_NCOInverseOutput_Cmd(DISABLE);
 * @endcode
 *******************************************************************************
 */
void APB_NCOInverseOutput_Cmd(FunctionalState NewState)
{
    APB->NCO00.MBIT.NCO0_INV = NewState;
}

/**
 *******************************************************************************
 * @brief	    Turn on/off the NCO peripheral.
 * @param[in] 	NewState: new state of the NCO.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_NCO_Cmd(ENABLE);
 * @endcode
 *******************************************************************************
 */
void APB_NCO_Cmd(FunctionalState NewState)
{
    APB->NCO00.MBIT.NCO0_EN = NewState;
}

/**
 *******************************************************************************
 * @brief       Select NCO PFM mode output pulse width.
 * @param[in] 	NCOPFMWidth: config PFM output width.
 *  @arg\b      APB_PFM_1Clock: 1 CK_NCOn clock period.
 *  @arg\b      APB_PFM_2Clock: 2 CK_NCOn clock period.
 *  @arg\b      APB_PFM_4Clock: 4 CK_NCOn clock period.
 *  @arg\b      APB_PFM_8Clock: 8 CK_NCOn clock period.
 *  @arg\b      APB_PFM_16Clock: 16 CK_NCOn clock period.
 *  @arg\b      APB_PFM_32Clock: 32 CK_NCOn clock period.
 *  @arg\b      APB_PFM_64Clock: 64 CK_NCOn clock period.
 *  @arg\b      APB_PFM_128Clock: 128 CK_NCOn clock period.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_NCOPFMWidth_Select(APB_PFM_2Clock);
 * @endcode
 *******************************************************************************
 */
void APB_NCOPFMWidth_Select(APB_NCOPFMWidtrhSelDef NCOPFMWidth)
{
    APB->NCO01.MBIT.NCO0_PWS = NCOPFMWidth;
}

/**
 *******************************************************************************
 * @brief	    Set NCO adder increment value.
 * @param[in] 	NCOINCV: NCO adder increment value. 
 *      	    specifies the increment value (0~1048575)
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_NCOSetINC(100);
 * @endcode
 *******************************************************************************
 */
void APB_NCOSetINC(uint32_t NCOINCV)
{
    APB->NCO00.MBIT.NCO0_INC = NCOINCV;
}


/**
 *******************************************************************************
 * @brief	    Set NCO adder accumulator value.
 * @param[in] 	NCOACCV: NCO adder accumulator value. 
 *      	    specifies the accumulator value (0~1048575)
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_NCOSetACC(100);
 * @endcode
 *******************************************************************************
 */
void APB_NCOSetACC(uint32_t NCOACCV)
{
    APB->NCO01.MBIT.NCO0_ACC = NCOACCV;
}

/**
 *******************************************************************************
 * @brief       Get NCO output state 
 * @return		return OBMx output 0/1 state 
 *  @arg        DRV_Logic1 : '1' 
 *  @arg        DRV_Logic0 : '0'
 * @note 
 * @par         Example
 * @code
    tmp = APB_NCOGetOutputState();
 * @endcode
 *******************************************************************************
 */
DRV_Return APB_NCOGetOutputState()
{
    if (APB->STA.MBIT.NCO0_OUT)
        return DRV_Logic1;
    else 
        return DRV_Logic0;
}

///@}
#endif



/**
 * @name	interrupt and flag (SET/CLEAR/Config) 
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    Config interrupt source (Enable/Disable)
 * @param[in] 	APBx: specifies the APB macro 
 * @param[in] 	ITsrc: Enable/Disable interrupt source 
 *  @arg\b	    APB_OBM0_IE: OBM0 interrupt control bit.
 *  @arg\b	    APB_OBM1_IE: OBM1 interrupt control bit.
 *  @arg\b	    APB_NCO0_IE: NCO0 interrupt control bit.
 * @param[in] 	NewState: new state of the APBx interrupt key.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_IT_Config(APB, APB_OBM1_IE, ENABLE);
 * @endcode
 *******************************************************************************
 */
void APB_IT_Config(APB_Struct* APBx, uint32_t ITsrc, FunctionalState NewState)
{
    if (NewState == ENABLE)
        APBx->INT.W |= ITsrc;
    else
        APBx->INT.W &= ~ITsrc;
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable all interrupt 
 * @param[in] 	APBx: specifies the APB macro 
 * @param[in] 	NewState: new state of the APBx all interrupt key.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_ITEA_Cmd(APB, ENABLE);
 * @endcode
 *******************************************************************************
 */
void APB_ITEA_Cmd(APB_Struct* APBx, FunctionalState NewState)
{
    APBx->INT.MBIT.IEA = NewState;
}

/**
 *******************************************************************************
 * @brief	    Get one interrupt source state.
 * @param[in] 	APBx: specifies the APB macro.
 * @param[in] 	ITSrc: interrupt source item
 *  @arg\b	    APB_OBM0F: APB OBM0 trigger event detect flag.
 *  @arg\b	    APB_OBM1F: APB OBM1 trigger event detect flag.
 *  @arg\b	    APB_NCO0F: NCO0 adder overflow event flag.
 * @return 	    reference define of DRV_Return
 *  @arg        DRV_Happened : Happen 
 *  @arg        DRV_UnHappened : Unhappen
 * @note 
 * @par         Example
 * @code
    if(APB_GetSingleFlagStatus(APB, APB_OBM1F) == DRV_Happened)
    {
        // to do ...
    }   
 * @endcode
 *******************************************************************************
 */
DRV_Return APB_GetSingleFlagStatus(APB_Struct* APBx, uint32_t ITSrc)
{
    if (APBx->STA.W & ITSrc)
        return DRV_Happened;
    else 
        return DRV_UnHappened;
    
}

/**
 *******************************************************************************
 * @brief	    Get all interrupt source state
 * @param[in] 	APBx: specifies the APB macro 
 * @return 	    response what happended of STA
 * @note 
 * @par         Example
 * @code
    tmp = APB_GetAllFlagStatus(APB);
 * @endcode
 *******************************************************************************
 */
uint32_t APB_GetAllFlagStatus(APB_Struct* APBx)
{
    return APBx->STA.W;
}

/**
 *******************************************************************************
 * @brief	    Clear one or all interrupt source state
 * @param[in] 	APBx: specifies the APB macro 
 * @param[in] 	APB_ITSrc: interrupt source item
 *  @arg\b	    APB_OBM0F: APB OBM0 trigger event detect flag
 *  @arg\b	    APB_OBM1F: APB OBM1 trigger event detect flag
 *  @arg\b	    APB_NCO0F: NCO0 adder overflow event flag.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    APB_ClearFlag(APB, APB_OBM1F);
 * @endcode
 *******************************************************************************
 */
void APB_ClearFlag(APB_Struct* APBx, uint32_t APB_ITSrc)
{
    APBx->STA.W = APB_ITSrc;
}


///@}
