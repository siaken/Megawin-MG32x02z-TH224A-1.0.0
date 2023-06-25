/**
 ******************************************************************************
 *
 * @file        MG32x02z_TM_DRV.c
 *
 * @brief       This file provides firmware functions to manage the following 
 *              functionalities of the TM peripheral:
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.28
 * @date        2020/04/20
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




#include "MG32x02z_TM_DRV.h"


/**
 * @name	Deinitial Timer to default condition
 *   		
 */ 
///@{  
/**
 *******************************************************************************
 * @brief       Deinitializes the TMx peripheral registers to their default reset 
 *			    values.
 *
 * @details     Reset TMx to default configuration
 * @param[in]   TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @return		No
 * @note 
 * @par         Example
 * @code
    TM_DeInit(TM10);
 * @endcode
 *******************************************************************************
 */
void TM_DeInit(TM_Struct *TMx)
{
    TMx->CR0.W = 0x00000000;
    TMx->CR1.W = 0x00000000;
    TMx->TRG.W = 0x00000000;
    TMx->STA.W = 0xFFFFFFFF;
    TMx->INT.W = 0x00000000;
    TMx->CLK.W = 0x00000000;
    TMx->CKO.W = 0x00000008;
    TMx->CNT.W = 0x00000000;
    TMx->ARR.W = 0x00000000;
    TMx->PSCNT.W = 0x00000000;
    TMx->PSARR.W = 0x00000000;
    TMx->CCMDS.W = 0x00000000;
    TMx->ICCR.W = 0x00000000;
    TMx->OSCR.W = 0x0000F0F0;
    TMx->OCCR0.W = 0x00000000;
    TMx->OCCR1.W = 0x00000000;
    TMx->PWM.W = 0x00000000;
    TMx->BS.W = 0x00000000;
    TMx->CC0A.W = 0x00000000;
    TMx->CC0B.W = 0x00000000;
    TMx->CC1A.W = 0x00000000;
    TMx->CC1B.W = 0x00000000;
    TMx->CC2A.W = 0x00000000;
    TMx->CC2B.W = 0x00000000;
    TMx->CC3A.W = 0x00000000;
    TMx->CC3B.W = 0x00000000;
}
///@}








/** 
 * @name		Auto initial Timer with internal clock input
 *
 */ 
///@{  
 
/**
 *******************************************************************************
 * @brief       Fills each TM_TMBaseInitStruct member with its default value.
 * @param[in]   TM_TMBaseInitStruct : pointer to a TM_TimeBaseInitTypeDef
 *        	    structure which will be initialized.
 * @return		No
 * @note 
 * @par         Example
 * @code
    TM_TimeBaseInitTypeDef TM_TMBaseInitStruct;
 
    TM_TimeBaseStruct_Init(&TM_TMBaseInitStruct);
 * @endcode
 *******************************************************************************
 */
 void TM_TimeBaseStruct_Init(TM_TimeBaseInitTypeDef *TM_TMBaseInitStruct)
{
    TM_TMBaseInitStruct->TM_Prescaler = 5;
    TM_TMBaseInitStruct->TM_CounterMode = Cascade;
    TM_TMBaseInitStruct->TM_Period = 5;
    TM_TMBaseInitStruct->TM_MainClockSource = TM_CK_INT;
    TM_TMBaseInitStruct->TM_2ndClockSource = TM_CK_INT;
    TM_TMBaseInitStruct->TM_MainClockDirection = TM_UpCount;
    TM_TMBaseInitStruct->TM_2ndClockDirection = TM_UpCount;
    TM_TMBaseInitStruct->TM_IntClockDivision = TM_IntDIV1;
	
}

/**
 *******************************************************************************
 * @brief       Initializes the TMx Time Base Unit peripheral according to 
 *			    the specified parameters in the TM_TMBaseInitStruct.
 * @param[in]   TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in]   TM_TMBaseInitStruct : pointer to a TM_TimeBaseInitTypeDef
 *        	    structure that contains the configuration information for
 *        	    the specified TM peripheral.
 * @return		No
 * @note 
 * @par         Example
 * @code
    TM_TimeBase_Init(TM26, &TM_TMBaseInitStruct);
 * @endcode
 *******************************************************************************
 */
void TM_TimeBase_Init(TM_Struct *TMx, TM_TimeBaseInitTypeDef *TM_TMBaseInitStruct)
{
    // setting parameters
    // prescaler counter initial value
    if(TM_TMBaseInitStruct->TM_2ndClockDirection == TM_UpCount)
        TM_Prescaler_Config(TMx, 0, TM_TMBaseInitStruct->TM_Prescaler);
    else
        TM_Prescaler_Config(TMx, TM_TMBaseInitStruct->TM_Prescaler, TM_TMBaseInitStruct->TM_Prescaler);
        
    // main counter initial value
    if(TM_TMBaseInitStruct->TM_MainClockDirection == TM_UpCount)
        TM_Counter_Config(TMx, 0, TM_TMBaseInitStruct->TM_Period);
    else
        TM_Counter_Config(TMx, TM_TMBaseInitStruct->TM_Period, TM_TMBaseInitStruct->TM_Period);
    
    // counter operation mode (Full Counter/Cascade/Separate)
    TM_TimerMode_Select(TMx, TM_TMBaseInitStruct->TM_CounterMode);
    
    // clock source (TM_CK_INT or TM_CK_EXT)
    TM_CounterClock_Select(TMx, TM_TMBaseInitStruct->TM_MainClockSource);
    TM_PrescalerClock_Select(TMx, TM_TMBaseInitStruct->TM_2ndClockSource);
    
    TM_SetInternalClockDivider(TMx, TM_TMBaseInitStruct->TM_IntClockDivision);
    
    // setting main/prescaler counter direction
    TM_SetCounterDirection(TMx, TM_TMBaseInitStruct->TM_MainClockDirection);
    TM_SetPrescalerDirection(TMx, TM_TMBaseInitStruct->TM_2ndClockDirection);
	
}
///@}








/** 
 * @name		Timer clock configuration functions
 *
 */ 
///@{  
/**
 *******************************************************************************
 * @brief       Select the timer internal clock source.
 * @param[in]   TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in]   INTClockSrc : specifies the Main Counter direction to be used
 *  @arg\b	    TM_PROC : the clock from CSC macro (CK_SYS or CK_APB)
 *	@arg\b	    TM_CK_PLL : the clock from CK_PLL 
 *	@arg\b	    TM_CK_LS : the clock from CK_LS 
 * @return		No
 * @note 
 * @par         Example
 * @code
    TM_InternalClockSource_Select(TM00, TM_PROC);       // AHB or APB clock (config by CSC Wizard)
 * @endcode
 *******************************************************************************
 */
void TM_InternalClockSource_Select(TM_Struct* TMx, TM_INTClockSrcDef INTClockSrc)
{
	TMx->CLK.MBIT.CKI_SEL = INTClockSrc;
}

/**
 *******************************************************************************
 * @brief	    Select main counter clock source .
 * @param[in]   TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in]   TMClockSelect: specifies the Counter clock 
 *  @arg\b	    TM_CK_INT : clock from internal clock (CK_SYS/CK_APB or CK_LS)
 *	@arg\b	    TM_CK_EXT :	clock from external (ETR, ITRx, IN0 or IN1)
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_CounterClock_Select(TM36, TM_CK_INT);
 * @endcode
 *******************************************************************************
 */
void TM_CounterClock_Select(TM_Struct* TMx, TM_ClockSourceDef TMClockSelect)
{
    TMx->CLK.MBIT.CKS_SEL = TMClockSelect;    
}

/**
 *******************************************************************************
 * @brief	    Config Timer internal clock CK_TMx_INT input divider.
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 21 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	INTClockSrc : specifies the internal clock divider to be used
 *  @arg	    TM_IntDIV1 : divided by 1
 *	@arg	    TM_IntDIV2 : divided by 2
 *  @arg	    TM_IntDIV4 : divided by 4
 *	@arg	    TM_IntDIV8 : divided by 8
 * @return 	    none
 *******************************************************************************
 */
void TM_SetInternalClockDivider(TM_Struct* TMx, TM_INTClockDivDef INTClockSrc)
{
	TMx->CLK.MBIT.CKI_DIV = INTClockSrc;
}

/**
 *******************************************************************************
 * @brief	    Select prescaler counter clock source .
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	TMClockSelect: specifies the Counter clock 
 *  @arg\b	    TM_CK_INT : clock from internal clock (CK_SYS/CK_APB or CK_LS)
 *	@arg\b	    TM_CK_EXT :	clock from external (ETR, ITRx, IN0 or IN1)
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_PrescalerClock_Select(TM36, TM_CK_INT);
 * @endcode
 *******************************************************************************
 */
void TM_PrescalerClock_Select(TM_Struct* TMx, TM_ClockSourceDef TMClockSelect)
{
    TMx->CLK.MBIT.CKS2_SEL = TMClockSelect;    
}

/**
 *******************************************************************************
 * @brief	    Config external clock source
 * @param[in]   TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	TMExtClockSelect: specifies the Counter clock 
 *  @arg\b	    TM_CKETR : external Timer trigger signals (reference GPIO AFS function)
 *	@arg\b	    TM_CKITR : internal Timer trigger signals (from another Timer's TRGO)
 *	@arg\b	    TM_CKIN0 : external Timer trigger signals (reference GPIO AFS function)
 *	@arg\b	    TM_CKIN1 : external Timer trigger signals (reference GPIO AFS function)
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_ExternalClock_Select(TM16, TM_CKITR);
 * @endcode
 *******************************************************************************
 */
void TM_ExternalClock_Select(TM_Struct* TMx, TM_ExternalClockSourceDef TMExtClockSelect)
{
    TMx->CLK.MBIT.CKE_SEL = TMExtClockSelect;    
}

/**
 *******************************************************************************
 * @brief       config internal Timer trigger signals
 * @param[in]   TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	TM_ITRSource: specifies the Counter clock 
 *  @arg\b	    ITR0~ITR7 : depend Timer module (reference Timer Internal Trigger 
 *              and Channel Input Signals Table)
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_ITRx_Select(TM16, ITR2);
 * @endcode
 *******************************************************************************
 */
void TM_ITRx_Select(TM_Struct* TMx, TM_ITRSourceDef TM_ITRSource)
{
    TMx->TRG.MBIT.ITR_MUX = TM_ITRSource;    
}
///@}








/** 
 * @name		Timer mode (Cascade/Separate/Full_Counter)
 *
 */ 
///@{  
/**
 *******************************************************************************
 * @brief	    Select the TMx mode 
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	TM_TimerMode : specifies the timer operation mode
 *  @arg\b      Cascade : 16/8-bit counter with 16/8-bit prescaler Mode
 *  @arg\b      Separate : Separated two 16/8-bit counters Mode
 *  @arg\b      Full_Counter : 32/16-bit counter Mode
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_TimerMode_Select(TM10, Separate);
 * @endcode
 *******************************************************************************
 */
void TM_TimerMode_Select(TM_Struct* TMx, TM_CounterModeDef TM_TimerMode)
{
    TMx->CR0.MBIT.MDS = TM_TimerMode;
}
///@}








/** 
 * @name		Timer main counter configuration functions
 *
 */ 
///@{  

/**
 *******************************************************************************
 * @brief	    Configures the TMx counter direction.
 * @param[in]   TMx: where x can be 16, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	DIR : specifies the Main Counter direction to be used
 *  @arg\b	    TM_UpCount : Up Counting Mode
 *	@arg\b	    TM_DownCount :	Down Counting Mode
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_SetCounterDirection(TM26, TM_DownCount);
 * @endcode
 *******************************************************************************
 */
void TM_SetCounterDirection(TM_Struct* TMx, TM_DirectionDef DIR)
{
    TMx->CR0.MBIT.DIR = DIR;
#if defined(MG32_1ST)
	if (TMx == TM36)
	{
		TMx->CR0.MBIT.DIR2 = TMx->CR0.MBIT.DIR;
	}
#endif		
	
}

/**
 *******************************************************************************
 * @brief       Gets the TMx main counter current value.
 * @param[in]   TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @return      return counter value
 * @note 
 * @par         Example
 * @code
    tmp = TM_GetCounter(TM36);
 * @endcode
 *******************************************************************************
 */
uint16_t TM_GetCounter(TM_Struct* TMx)
{
    return TMx->CNT.H[0];
}

/**
 *******************************************************************************
 * @brief	    Configures the TMx main counter and reload value.
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	TM_Counter : specifies the main counter Register value
 * @param[in] 	TM_CounterReload : specifies the Prescaler reload Register value
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    // initial main counter starts from 10, and count range is 0x00~0x50
    TM_Counter_Config(TM01, 0x10, 0x50);
 * @endcode
 *******************************************************************************
 */
void TM_Counter_Config(TM_Struct* TMx, uint16_t TM_Counter, uint16_t TM_CounterReload)
{
    TMx->CNT.H[0] = TM_Counter;
    TMx->ARR.H[0] = TM_CounterReload;
}

/**
 *******************************************************************************
 * @brief	    Turn on/off the TMx main counter .
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: new state of the TMx main counter.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_Counter_Cmd(TM01, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_Counter_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    if (NewState == ENABLE)
        TMx->CR0.B[0] |= TM_CR0_EN_enable_b0;
    else
        TMx->CR0.B[0] &= ~(TM_CR0_EN_mask_h0);
}

/**
 *******************************************************************************
 * @brief	    Config Reset or Gating function for counter 
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in]   CMode: specifies the reset or gate main counter function
 *              This parameter can be: ResetCounter or GatingCounter.
 *  @arg\b	    ResetCounter : reset counter by software
 *	@arg\b	    GatingCounter :	gating counter by software
 * @param[in] 	NewState: new state of the TMx peripheral.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_Counter_SW(TM36, ResetCounter, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_Counter_SW(TM_Struct* TMx, TM_CounterResetGateSW_Def CMode, FunctionalState NewState)
{
    if (NewState == ENABLE)
        TMx->TRG.B[3] |= CMode;
    else
        TMx->TRG.B[3] &= ~(CMode);
}
///@}








/** 
 * @name		Timer prescaler counter config functions
 *
 */ 
///@{  
/**
 *******************************************************************************
 * @brief	    Configures the TMx prescaler direction
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	DIR : specifies the Main Counter direction to be used
 *  @arg\b	    TM_UpCount : Up Counting Mode
 *	@arg\b	    TM_DownCount :	Down Counting Mode
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_SetPrescalerDirection(TM36, TM_UpCount);
 * @endcode
 *******************************************************************************
 */
void TM_SetPrescalerDirection(TM_Struct* TMx, TM_DirectionDef DIR)
{
#if defined(MG32_1ST)
	if(TMx == TM36)
		TMx->CR0.MBIT.DIR2 = TMx->CR0.MBIT.DIR;		// TM36 Prescaler direction is the same as main counter
	else
		TMx->CR0.MBIT.DIR2 = DIR;
#endif
    
#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
    TMx->CR0.MBIT.DIR2 = DIR;
#endif
    
}

/**
 *******************************************************************************
 * @brief	    Gets the TMx prescaler value.
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @return 	    return prescaler counter value
 * @note 
 * @par         Example
 * @code
    tmp = TM_GetPrescaler(TM16);
 * @endcode
 *******************************************************************************
 */
uint16_t TM_GetPrescaler(TM_Struct* TMx)
{
    return TMx->PSCNT.H[0];
}

/**
 *******************************************************************************
 * @brief	    Configures the TMx prescaler counter and reload value
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	TM_Prescaler : specifies the Prescaler Register value
 * @param[in] 	TM_PrescalerReload : specifies the Prescaler reload Register value
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    // initial prescaler counter starts from 0x1010 and count range is 0x0000~0xFFFF
    TM_Prescaler_Config(TM10, 0x1010, 0xFFFF);
 * @endcode
 *******************************************************************************
 */
void TM_Prescaler_Config(TM_Struct* TMx, uint16_t TM_Prescaler, uint16_t TM_PrescalerReload)
{
    TMx->PSCNT.H[0] = TM_Prescaler;
    TMx->PSARR.H[0] = TM_PrescalerReload;
}

/**
 *******************************************************************************
 * @brief	    Turn on/off the TMx prescaler .
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: new state of the TMx prescaler counter.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_Prescaler_Cmd(TM26, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_Prescaler_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    if (NewState == ENABLE)
        TMx->CR0.B[0] |= TM_CR0_EN2_enable_b0;
    else
        TMx->CR0.B[0] &= ~(TM_CR0_EN2_mask_b0);
}

/**
 *******************************************************************************
 * @brief	    Config Reset or Gating function for prescaler counter 
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in]   CMode: specifies the reset or gate prescaler counter function
 *              This parameter can be: ResetCounter or GatingCounter.
 *  @arg\b	    ResetCounter : reset counter by software
 *	@arg\b	    GatingCounter :	gating counter by software
 * @param[in] 	NewState: new state of the TMx peripheral.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    // Gating TM10's prescaler counter
    TM_Prescaler_SW(TM16, GatingCounter, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_Prescaler_SW(TM_Struct* TMx, TM_PrescalerResetGateSW_Def CMode, FunctionalState NewState)
{
    if (NewState == ENABLE)
        TMx->TRG.B[3] |= CMode;
    else
        TMx->TRG.B[3] &= ~(CMode);
}
///@}








/** 
 * @name		Turn on/off timer (counter and prescaler)
 *
 */ 
///@{  
/**
 *******************************************************************************
 * @brief	    Turn on/off the TMx counter & prescaler .
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: new state of the TMx peripheral.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_Timer_Cmd(TM20, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_Timer_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    if (NewState == ENABLE)
        TMx->CR0.B[0] |= TM_CR0_EN_enable_b0 | TM_CR0_EN2_enable_b0;
    else
        TMx->CR0.B[0] &= ~(TM_CR0_EN_mask_b0 | TM_CR0_EN2_mask_b0);
}
///@}








/** 
 * @name		TRGI configuration and action
 *
 */ 
///@{  
/**
 *******************************************************************************
 * @brief	    Gating Prescaler counter function
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: config gating function for prescaler
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_GatePrescaler_SW(TM10, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_GatePrescaler_SW(TM_Struct* TMx,FunctionalState NewState)
{
    TMx->TRG.MBIT.GT2_SW = NewState;
}

/**
 *******************************************************************************
 * @brief	    Gating main counter function
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: config gating function for main counter
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_GateCounter_SW(TM10, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_GateCounter_SW(TM_Struct* TMx,FunctionalState NewState)
{
    TMx->TRG.MBIT.GT_SW = NewState;
}

/**
 *******************************************************************************
 * @brief	    Reset Prescaler counter function
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: config reset function for prescaler by software
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_ResetPrescaler_SW(TM36, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_ResetPrescaler_SW(TM_Struct* TMx,FunctionalState NewState)
{
    TMx->TRG.MBIT.RST2_SW = NewState;
}

/**
 *******************************************************************************
 * @brief	    Reset main counter function
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: config reset function for main counter by software
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_ResetCounter_SW(TM36, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_ResetCounter_SW(TM_Struct* TMx,FunctionalState NewState)
{
    TMx->TRG.MBIT.RST_SW = NewState;
}
/**
 *******************************************************************************
 * @brief	    Config TRGI signal source
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	TRGISel: specifies the timer operation mode
 *  @arg\b      TRGI_ETR
 *  @arg\b      TRGI_ITR
 *  @arg\b      TRGI_IN0
 *  @arg\b      TRGI_IN1
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_TriggerSource_Select(TM36, TRGI_IN0);
 * @endcode
 *******************************************************************************
 */
void TM_TriggerSource_Select(TM_Struct* TMx, TM_TRGITrgSourceDef TRGISel)
{
    TMx->TRG.MBIT.TRG_MUX = TRGISel;
}

/**
 *******************************************************************************
 * @brief	    Select main counter action when TRGI event happended
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	TRGIMDS: specifies the timer operation mode
 *  @arg\b      TRGI_NoOP : No operation - default 
 *  @arg\b      TRGI_StartupRising : startup counter when TRGI rising edge 
 *  @arg\b      TRGI_ResetRising : reset counter when TRGI rising edge
 *  @arg\b      TRGI_GATE_High : gating counter when TRGI in high level
 *  @arg\b      TRGI_Rest_DualEdge : reset counter when TRGI rising or falling (dual) edge
 *  @arg\b      TRGI_StartupFalling : startup counter when TRGI falling edge
 *  @arg\b      TRGI_ResetFalling : reset counter when TRGI falling edge 
 *  @arg\b      TRGI_GATE_Low : gating counter when TRGI in low level 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_TRGICounter_Select(TM10, TRGI_ResetRising);
 * @endcode
 *******************************************************************************
 */
void TM_TRGICounter_Select(TM_Struct* TMx, TM_TRGIModeDef TRGIMDS)
{
    TMx->TRG.MBIT.TRGI_MDS = TRGIMDS;
}

/**
 *******************************************************************************
 * @brief	    Config prescaler counter action when TRGI event happended
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	TRGIMDS: specifies the timer operation mode
 *  @arg\b      TRGI_NoOP : No operation - default 
 *  @arg\b      TRGI_StartupRising : startup counter when TRGI rising edge 
 *  @arg\b      TRGI_ResetRising : reset counter when TRGI rising edge
 *  @arg\b      TRGI_GATE_High : gating counter when TRGI in high level
 *  @arg\b      TRGI_Rest_DualEdge : reset counter when TRGI rising or falling (dual) edge
 *  @arg\b      TRGI_StartupFalling : startup counter when TRGI falling edge
 *  @arg\b      TRGI_ResetFalling : reset counter when TRGI falling edge 
 *  @arg\b      TRGI_GATE_Low : gating counter when TRGI in low level 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_TRGIPrescaler_Select(TM10, TRGI_StartupFalling);
 * @endcode
 *******************************************************************************
 */
void TM_TRGIPrescaler_Select(TM_Struct* TMx, TM_TRGIModeDef TRGIMDS)
{
    TMx->TRG.MBIT.TRGI2_MDS = TRGIMDS;
}

/**
 *******************************************************************************
 * @brief	    Config update event source
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	UEVCon: specifies the timer update event source  
 *  @arg\b      UEV_All : output all UEV pulses (overflow and underflow)
 *  @arg\b      UEV_TOF : output timer overflow pulses (from TUF or TUF2)
 *  @arg\b      UEV_UDF : output timer underflow pulses (from TDF or TDF2)
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_UEV_Config(TM10, UEV_TOF);
 * @endcode
 *******************************************************************************
 */
void TM_UEV_Config(TM_Struct* TMx, TM_UEVSrcDef UEVCon)
{
    TMx->TRG.MBIT.UEV_SEL = UEVCon;
}

/**
 *******************************************************************************
 * @brief	    Generate the TRGO event by software.
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: new state of the TMx peripheral.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    // TM10: Generate plus TRGO by Software
    TM_TRGOOut_SW(TM10, ENABLE);
    TM_TRGOOut_SW(TM10, DISABLE);
 * @endcode
 *******************************************************************************
 */
void TM_TRGOOut_SW(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->TRG.MBIT.TRGO_SW = NewState;
}

/**
 *******************************************************************************
 * @brief	    Configures the TMx's TRGO source
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	TM_TRGOCon: specifies the timer TRGO source  
 *  @arg\b      TRGO_RST : output main counter's reset event
 *  @arg\b      TRGO_EN : output timer running state
 *  @arg\b      TRGO_UEV : output main counter Update event (TOF or TUF)
 *  @arg\b      TRGO_TOF : output TRGO (TOF flag state)     
 *  @arg\b      TRGO_TUF : output TRGO (TUF flag state)     
 *  @arg\b      TRGO_EN2 : output TRGO when prescaler counter running       
 *  @arg\b      TRGO_TOF2 : output TRGO (TOF2 flag state)     
 *  @arg\b      TRGO_TMx_DIR : output TRGO (Main Timer direction event)      
 *  @arg\b      TRGO_UEV2 : output prescaler counter Update event (TOF2 or TUF2)
 *  @arg\b      TRGO_SW : output TRGO by sofware      
 *  @arg\b      TRGO_OS0 : output TRGO (channel-0 output state)     
 *  @arg\b      TRGO_OS1 : output TRGO (channel-1 output state)     
 *  @arg\b      TRGO_OS2 : output TRGO (channel-2 output state)     
 *  @arg\b      TRGO_OS3 : output TRGO (channel-3 output state)     
 *  @arg\b      TRGO_TRGI : output TRGI state     
 *  @arg\b      TRGO_POE : output TRGO (preload signal)     
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_TRGO_Select(TM00, TRGO_UEV);
 * @endcode
 *******************************************************************************
 */
void TM_TRGO_Select(TM_Struct* TMx, TM_TRGOSrcDef TM_TRGOCon )
{
    TMx->TRG.MBIT.TRGO_MDS = TM_TRGOCon;
}

/**
 *******************************************************************************
 * @brief	    Inverse the TRGO output state
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: config inverse function for OC0H
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_InverseTRGO_Cmd(TM20, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_InverseTRGO_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->TRG.MBIT.TRGO_INV = NewState;
}

///@}





/** 
 * @name		Input pin configuration
 *
 */ 
///@{  

/**
 *******************************************************************************
 * @brief	    Config channel-0 IN0 source.
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	TM_ICxSrc: specifies the timer IC0's source  
 *  @arg\b      TMx_InputMUX_Pin : channel0 input trigger source from Pin
 *  @arg\b      TMx_InputMUX_ITR : channel0 input trigger source from ITR mux
 *  @arg\b      TMx_InputMUX_Line2 : channel0 input trigger source from line2
 *  @arg\b      TMx_InputMUX_Line3 : channel0 input trigger source from line3
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_IN0Source_Select(TM36, TMx_InputMUX_Pin);
 * @endcode
 *******************************************************************************
 */
void TM_IN0Source_Select(TM_Struct* TMx, TM_ICxMuxDef TM_ICxSrc)
{
    TMx->ICCR.MBIT.IC0_MUX = TM_ICxSrc;
}

/**
 *******************************************************************************
 * @brief	    Config channel-0 IN0 trigger edge source.
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	TM_ICxTrg: Timer channel 0 input trigger edge select.
 *  @arg\b      IC_Disable : disable capture data
 *  @arg\b      IC_RisingEdge : Rising edge
 *  @arg\b      IC_FallingEdge : Falling edge
 *  @arg\b      IC_DualEdge : Dual-edge
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_IN0TriggerEvent_Select(TM36, IC_RisingEdge);
 * @endcode
 *******************************************************************************
 */
void TM_IN0TriggerEvent_Select(TM_Struct* TMx, TM_ICxTrgDef TM_ICxTrg)
{
    TMx->ICCR.MBIT.IC0_TRGS = TM_ICxTrg;
}

/**
 *******************************************************************************
 * @brief	    Config channel-1 IN1 source.
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	TM_ICxSrc: specifies the timer IC0's source  
 *  @arg\b      TMx_InputMUX_Pin : channel1 input trigger source from Pin
 *  @arg\b      TMx_InputMUX_ITR : channel1 input trigger source from ITR mux
 *  @arg\b      TMx_InputMUX_Line2 : channel1 input trigger source from line2
 *  @arg\b      TMx_InputMUX_Line3 : channel1 input trigger source from line3
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_IN1Source_Select(TM26, TMx_InputMUX_Pin);
 * @endcode
 *******************************************************************************
 */
void TM_IN1Source_Select(TM_Struct* TMx, TM_ICxMuxDef TM_ICxSrc)
{
    TMx->ICCR.MBIT.IC1_MUX = TM_ICxSrc;
}

/**
 *******************************************************************************
 * @brief	    Config channel-1 IN1 trigger edge source.
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	TM_ICxTrg: Timer channel 1 input trigger edge select.
 *  @arg\b      IC_Disable : disable capture data
 *  @arg\b      IC_RisingEdge : Rising edge
 *  @arg\b      IC_FallingEdge : Falling edge
 *  @arg\b      IC_DualEdge : Dual-edge
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_IN1TriggerEvent_Select(TM26, IC_RisingEdge);
 * @endcode
 *******************************************************************************
 */
void TM_IN1TriggerEvent_Select(TM_Struct* TMx, TM_ICxTrgDef TM_ICxTrg)
{
    TMx->ICCR.MBIT.IC1_TRGS = TM_ICxTrg;
}

/**
 *******************************************************************************
 * @brief	    Config channel-2 IN2 source.
 * @param[in]	TMx: where x can be 36 to select the TM peripheral.
 * @param[in] 	TM_ICxSrc: specifies the timer IC0's source  
 *  @arg\b      TMx_InputMUX_Pin : channel2 input trigger source from Pin
 *  @arg\b      TMx_InputMUX_ITR : channel2 input trigger source from ITR mux
 *  @arg\b      TMx_InputMUX_Line2 : channel2 input trigger source from line2
 *  @arg\b      TMx_InputMUX_Line3 : channel2 input trigger source from line3
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_IN2Source_Select(TM36, TMx_InputMUX_Pin);
 * @endcode
 *******************************************************************************
 */
void TM_IN2Source_Select(TM_Struct* TMx, TM_ICxMuxDef TM_ICxSrc)
{
    TMx->ICCR.MBIT.IC2_MUX = TM_ICxSrc;
}

/**
 *******************************************************************************
 * @brief	    Config channel-2 IN2 trigger edge source.
 * @param[in]	TMx: where x can be 36 to select the TM peripheral.
 * @param[in] 	TM_ICxTrg: Timer channel 2 input trigger edge select.
 *  @arg\b      IC_Disable : disable capture data
 *  @arg\b      IC_RisingEdge : Rising edge
 *  @arg\b      IC_FallingEdge : Falling edge
 *  @arg\b      IC_DualEdge : Dual-edge
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_IN2TriggerEvent_Select(TM36, IC_RisingEdge);
 * @endcode
 *******************************************************************************
 */
void TM_IN2TriggerEvent_Select(TM_Struct* TMx, TM_ICxTrgDef TM_ICxTrg)
{
    TMx->ICCR.MBIT.IC2_TRGS = TM_ICxTrg;
}

/**
 *******************************************************************************
 * @brief	    Config channel-3 IN3 source.
 * @param[in]	TMx: where x can be 36 to select the TM peripheral.
 * @param[in] 	TM_ICxSrc: specifies the timer IC0's source  
 *  @arg\b      TMx_InputMUX_Pin : channel3 input trigger source from Pin
 *  @arg\b      TMx_InputMUX_ITR : channel3 input trigger source from ITR mux
 *  @arg\b      TMx_InputMUX_Line2 : channel3 input trigger source from line2
 *  @arg\b      TMx_InputMUX_Line3 : channel3 input trigger source from line3
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_IN3Source_Select(TM36, TMx_InputMUX_Pin);
 * @endcode
 *******************************************************************************
 */
void TM_IN3Source_Select(TM_Struct* TMx, TM_ICxMuxDef TM_ICxSrc)
{
    TMx->ICCR.MBIT.IC3_MUX = TM_ICxSrc;
}

/**
 *******************************************************************************
 * @brief	    Config channel-3 IN3 trigger edge source.
 * @param[in]	TMx: where x can be 36 to select the TM peripheral.
 * @param[in] 	TM_ICxTrg: Timer channel 3 input trigger edge select.
 *  @arg\b      IC_Disable : disable capture data
 *  @arg\b      IC_RisingEdge : Rising edge
 *  @arg\b      IC_FallingEdge : Falling edge
 *  @arg\b      IC_DualEdge : Dual-edge
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_IN3TriggerEvent_Select(TM36, IC_FallingEdge);
 * @endcode
 *******************************************************************************
 */
void TM_IN3TriggerEvent_Select(TM_Struct* TMx, TM_ICxTrgDef TM_ICxTrg)
{
    TMx->ICCR.MBIT.IC3_TRGS = TM_ICxTrg;
}
///@}





/** 
 * @name		Clock out configuration
 *
 */ 
///@{  

/**
 *******************************************************************************
 * @brief	    clock output source select
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	TM_CKOSel: select CKO source.
 *  @arg\b      MainCKO : toggle output pin when main counter overflow or underflow
 *  @arg\b      PrescalerCKO : toggle output pin when prescaler counter overflow or underflow
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_ClockOutSource_Select(TM00, MainCKO);
 * @endcode
 *******************************************************************************
 */
void TM_ClockOutSource_Select(TM_Struct* TMx, TM_CKOSrcDef TM_CKOSel)
{
    TMx->CKO.MBIT.CKO_SEL = TM_CKOSel;
}

/**
 *******************************************************************************
 * @brief	    Enable or Disable clock output
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: new state of the TMx clock out (enable/disable).
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_ClockOut_Cmd(TM20, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_ClockOut_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CKO.MBIT.CKO_EN = NewState;
}

/**
 *******************************************************************************
 * @brief	    Initial CKO output state
 * @param[in]	TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	PinState: new state of CKO output initial state.
 *      	    This parameter can be: CLR or SET.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_CKOOutputState_Init(TM01, SET);
 * @endcode
 *******************************************************************************
 */
void TM_CKOOutputState_Init(TM_Struct* TMx, BitAction PinState)
{
    uint8_t temp;
    
    temp = TMx->CKO.B[0];
    temp |= TM_CKO_unLock;
    
    if (PinState == SET)
        temp |= TM_CKO_State;
    else
        temp &= ~TM_CKO_State;
        
    TMx->CKO.B[0] = temp;
}
///@}





/** 
 * @name		Channel-0 output pin configuration
 *
 */ 
///@{  
// Ouptu control of channel 0
/**
 *******************************************************************************
 * @brief	    Inverse the OC0x (OC00,OC01,OC02) output state
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	NewState: config inverse function
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_InverseOC0z_Cmd(TM20, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_InverseOC0z_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR1.MBIT.OC0_INV = NewState;
}

/**
 *******************************************************************************
 * @brief	    Initial OC0x (OC00,OC01,OC02) output state
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	PinState: initial the OC0z output state.
 *      	    This parameter can be: CLR or SET.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC0zOutputState_Init(TM36, CLR);
 * @endcode
 *******************************************************************************
 */
void TM_OC0zOutputState_Init(TM_Struct* TMx, BitAction PinState)
{
    uint8_t temp;
    
    temp = TMx->OSCR.B[0];
    temp |= TM_OS0_unLock;
    
    if (PinState == SET)
        temp |= TM_OS0_State;
    else
        temp &= ~TM_OS0_State;
        
    TMx->OSCR.B[0] = temp;
}

/**
 *******************************************************************************
 * @brief	    Initial OC0x (OC00,OC01,OC02) break output state
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	BKPinState: set the OC0z break output state.
 *      	    This parameter can be: CLR or SET.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC0zBreakStopState_Init(TM36, CLR);
 * @endcode
 *******************************************************************************
 */
void TM_OC0zBreakStopState_Init(TM_Struct* TMx, BitAction BKPinState)
{
    TMx->BS.MBIT.STP0_STA = BKPinState;
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable the OC0x (OC00,OC01,OC02) output 
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	NewState: OC0z (OC00, OC01, OC02) Output Enable
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC0zOutput_Cmd(TM20, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_OC0zOutput_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR0.MBIT.OC0_OE0 = NewState;
    TMx->OCCR0.MBIT.OC0_OE1 = NewState;
    TMx->OCCR0.MBIT.OC0_OE2 = NewState;
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable the OC00 output 
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	NewState: OC00 Output Enable
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC00Output_Cmd(TM20, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_OC00Output_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR0.MBIT.OC0_OE0 = NewState;
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable the OC01 output 
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	NewState: OC01 Output Enable
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC01Output_Cmd(TM26, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_OC01Output_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR0.MBIT.OC0_OE1 = NewState;
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable the OC02 output 
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	NewState: OC02 Output Enable
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC02Output_Cmd(TM36, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_OC02Output_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR0.MBIT.OC0_OE2 = NewState;
}

/**
 *******************************************************************************
 * @brief	    Inverse the OC0N output state
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	NewState: config inverse function for OC0N
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_InverseOC0N_Cmd(TM36, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_InverseOC0N_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR1.MBIT.OC0N_INV = NewState;
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable the OC0N output 
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	NewState: OC0N Output Enable
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC0NOutput_Cmd(TM36, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_OC0NOutput_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR0.MBIT.OC0N_OE = NewState;
}

/**
 *******************************************************************************
 * @brief	    Initial OC0N break output state
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	BKPinState: set the OC0N break output state.
 *      	    This parameter can be: CLR or SET.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC0NBreakStopState_Init(TM36, CLR);
 * @endcode
 *******************************************************************************
 */
void TM_OC0NBreakStopState_Init(TM_Struct* TMx, BitAction BKPinState)
{
    TMx->BS.MBIT.STP0N_STA = BKPinState;
}

/**
 *******************************************************************************
 * @brief	    Inverse the OC0H output state
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	NewState: config inverse function for OC0H
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_InverseOC0H_Cmd(TM26, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_InverseOC0H_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR1.MBIT.OC0H_INV = NewState;
}
/**
 *******************************************************************************
 * @brief	    Initial OC0H output state
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	PinState: initial the OC0H output state.
 *      	    This parameter can be: CLR or SET.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC0HOutputState_Init(TM26, CLR);
 * @endcode
 *******************************************************************************
 */
void TM_OC0HOutputState_Init(TM_Struct* TMx, BitAction PinState)
{
    uint8_t temp;
    
    temp = TMx->OSCR.B[1];
    temp |= TM_OS0H_unLock;
    
    if (PinState == SET)
        temp |= TM_OS0H_State;
    else
        temp &= ~TM_OS0H_State;
        
    TMx->OSCR.B[1] = temp;
}
///@}






/** 
 * @name		Channel-1 output pin configuration
 *
 */ 
///@{  
// Ouptu control of channel 1
/**
 *******************************************************************************
 * @brief	    Inverse the OC1x (OC10,OC11,OC12) output state
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	NewState: config inverse function
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_InverseOC1z_Cmd(TM20, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_InverseOC1z_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR1.MBIT.OC1_INV = NewState;
}

/**
 *******************************************************************************
 * @brief	    Initial OC1x (OC10,OC11,OC12) output state
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	PinState: initial the OC1z output state.
 *      	    This parameter can be: CLR or SET.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC1zOutputState_Init(TM20, CLR);
 * @endcode
 *******************************************************************************
 */
void TM_OC1zOutputState_Init(TM_Struct* TMx, BitAction PinState)
{
    uint8_t temp;
    
    temp = TMx->OSCR.B[0];
    temp |= TM_OS1_unLock;
    
    if (PinState == SET)
        temp |= TM_OS1_State;
    else
        temp &= ~TM_OS1_State;
        
    TMx->OSCR.B[0] = temp;
}

/**
 *******************************************************************************
 * @brief	    Initial OC1x (OC10,OC11,OC12) break output state
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	BKPinState: set the OC1z break output state.
 *      	    This parameter can be: CLR or SET.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC1zBreakStopState_Init(TM20, CLR);
 * @endcode
 *******************************************************************************
 */
void TM_OC1zBreakStopState_Init(TM_Struct* TMx, BitAction BKPinState)
{
    TMx->BS.MBIT.STP1_STA = BKPinState;
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable the OC1x (OC10,OC11,OC12) output 
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	NewState: OC1z (OC10, OC11, OC12) Output Enable
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC1zOutput_Cmd(TM20, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_OC1zOutput_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR0.MBIT.OC1_OE0 = NewState;
    TMx->OCCR0.MBIT.OC1_OE1 = NewState;
    TMx->OCCR0.MBIT.OC1_OE2 = NewState;
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable the OC10 output 
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	NewState: OC10 Output Enable
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC10Output_Cmd(TM26, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_OC10Output_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR0.MBIT.OC1_OE0 = NewState;
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable the OC11 output 
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	NewState: OC11 Output Enable
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC11Output_Cmd(TM26, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_OC11Output_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR0.MBIT.OC1_OE1 = NewState;
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable the OC12 output 
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	NewState: OC12 Output Enable
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC12Output_Cmd(TM26, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_OC12Output_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR0.MBIT.OC1_OE2 = NewState;
}

/**
 *******************************************************************************
 * @brief	    Inverse the OC1N output state
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	NewState: config inverse function for OC1N
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_InverseOC1N_Cmd(TM26, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_InverseOC1N_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR1.MBIT.OC1N_INV = NewState;
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable the OC1N output 
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	NewState: OC1N Output Enable
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC1NOutput_Cmd(TM26, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_OC1NOutput_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR0.MBIT.OC1N_OE = NewState;
}

/**
 *******************************************************************************
 * @brief	    Initial OC1N break output state
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	BKPinState: set the OC1N break output state.
 *      	    This parameter can be: CLR or SET.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC1NBreakStopState_Init(TM20, CKR);
 * @endcode
 *******************************************************************************
 */
void TM_OC1NBreakStopState_Init(TM_Struct* TMx, BitAction BKPinState)
{
    TMx->BS.MBIT.STP1N_STA = BKPinState;
}

/**
 *******************************************************************************
 * @brief	    Inverse the OC1H output state
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	NewState: config inverse function for OC1H
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_InverseOC1H_Cmd(TM20, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_InverseOC1H_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR1.MBIT.OC1H_INV = NewState;
}
/**
 *******************************************************************************
 * @brief	    Initial OC1H output state
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	PinState: initial the OC1H output state.
 *      	    This parameter can be: CLR or SET.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC1HOutputState_Init(TM20, CLR);
 * @endcode
 *******************************************************************************
 */
void TM_OC1HOutputState_Init(TM_Struct* TMx, BitAction PinState)
{
    uint8_t temp;
    
    temp = TMx->OSCR.B[1];
    temp |= TM_OS1H_unLock;
    
    if (PinState == SET)
        temp |= TM_OS1H_State;
    else
        temp &= ~TM_OS1H_State;
        
    TMx->OSCR.B[1] = temp;
}
///@}






/** 
 * @name		Channel-2 output pin configuration
 *
 */ 
///@{  
// Ouptu control of channel 2
/**
 *******************************************************************************
 * @brief	    Inverse the OC2 output state
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	NewState: config inverse function
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_InverseOC2_Cmd(TM36, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_InverseOC2_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR1.MBIT.OC2_INV = NewState;
}

/**
 *******************************************************************************
 * @brief	    Initial OC2 output state
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	PinState: initial the OC2 output state.
 *      	    This parameter can be: CLR or SET.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC2OutputState_Init(TM36, CLR);
 * @endcode
 *******************************************************************************
 */
void TM_OC2OutputState_Init(TM_Struct* TMx, BitAction PinState)
{
    uint8_t temp;
    
    temp = TMx->OSCR.B[0];
    temp |= TM_OS2_unLock;
    
    if (PinState == SET)
        temp |= TM_OS2_State;
    else
        temp &= ~TM_OS2_State;
        
    TMx->OSCR.B[0] = temp;
}

/**
 *******************************************************************************
 * @brief	    Initial OC2 break output state
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	BKPinState: set the OC2 break output state.
 *      	    This parameter can be: CLR or SET.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC2BreakStopState_Init(TM36, CLR);
 * @endcode
 *******************************************************************************
 */
void TM_OC2BreakStopState_Init(TM_Struct* TMx, BitAction BKPinState)
{
    TMx->BS.MBIT.STP2_STA = BKPinState;
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable the OC2 output 
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	NewState: OC2 Output Enable
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC2Output_Cmd(TM36, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_OC2Output_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR0.MBIT.OC2_OE = NewState;
}

/**
 *******************************************************************************
 * @brief	    Inverse the OC2N output state
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	NewState: config inverse function for OC2N
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_InverseOC2N_Cmd(TM36, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_InverseOC2N_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR1.MBIT.OC2N_INV = NewState;
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable the OC2N output 
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	NewState: OC2N Output Enable
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC2NOutput_Cmd(TM36, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_OC2NOutput_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR0.MBIT.OC2N_OE = NewState;
}

/**
 *******************************************************************************
 * @brief	    Initial OC2N break output state
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	BKPinState: set the OC2N break output state.
 *      	    This parameter can be: CLR or SET.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC2NBreakStopState_Init(TM36, CLR);
 * @endcode
 *******************************************************************************
 */
void TM_OC2NBreakStopState_Init(TM_Struct* TMx, BitAction BKPinState)
{
    TMx->BS.MBIT.STP2N_STA = BKPinState;
}

/**
 *******************************************************************************
 * @brief	    Inverse the OC2H output state
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	NewState: config inverse function for OC2H
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_InverseOC2H_Cmd(TM36, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_InverseOC2H_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR1.MBIT.OC2H_INV = NewState;
}
/**
 *******************************************************************************
 * @brief	    Initial OC2H output state
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	PinState: initial the OC2H output state.
 *      	    This parameter can be: CLR or SET.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC2HOutputState_Init(TM36, CLR);
 * @endcode
 *******************************************************************************
 */
void TM_OC2HOutputState_Init(TM_Struct* TMx, BitAction PinState)
{
    uint8_t temp;
    
    temp = TMx->OSCR.B[1];
    temp |= TM_OS2H_unLock;
    
    if (PinState == SET)
        temp |= TM_OS2H_State;
    else
        temp &= ~TM_OS2H_State;
        
    TMx->OSCR.B[1] = temp;
}
///@}






/** 
 * @name		Channel-3 output pin configuration
 *
 */ 
///@{  
// Ouptu control of channel 3
/**
 *******************************************************************************
 * @brief	    Inverse the OC3 output state
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	NewState: config inverse function
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_InverseOC3_Cmd(TM36, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_InverseOC3_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR1.MBIT.OC3_INV = NewState;
}

/**
 *******************************************************************************
 * @brief	    Initial OC3 output state
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	PinState: initial the OC3 output state.
 *      	    This parameter can be: CLR or SET.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC3OutputState_Init(TM36, CLR);
 * @endcode
 *******************************************************************************
 */
void TM_OC3OutputState_Init(TM_Struct* TMx, BitAction PinState)
{
    uint8_t temp;
    
    temp = TMx->OSCR.B[0];
    temp |= TM_OS3_unLock;
    
    if (PinState == SET)
        temp |= TM_OS3_State;
    else
        temp &= ~TM_OS3_State;
        
    TMx->OSCR.B[0] = temp;
}

/**
 *******************************************************************************
 * @brief	    Initial OC3 break output state
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	BKPinState: set the OC3 break output state.
 *      	    This parameter can be: CLR or SET.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC3BreakStopState_Init(TM36, CLR);
 * @endcode
 *******************************************************************************
 */
void TM_OC3BreakStopState_Init(TM_Struct* TMx, BitAction BKPinState)
{
    TMx->BS.MBIT.STP3_STA = BKPinState;
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable the OC3 output 
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	NewState: OC3 Output Enable
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC3Output_Cmd(TM36, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_OC3Output_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR0.MBIT.OC3_OE = NewState;
}

/**
 *******************************************************************************
 * @brief	    Inverse the OC3H output state
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	NewState: config inverse function for OC3H
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_InverseOC3H_Cmd(TM36, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_InverseOC3H_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR1.MBIT.OC3H_INV = NewState;
}

/**
 *******************************************************************************
 * @brief	    Initial OC3H output state
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	PinState: initial the OC3H output state.
 *      	    This parameter can be: CLR or SET.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC3HOutputState_Init(TM36, CLR);
 * @endcode
 *******************************************************************************
 */
void TM_OC3HOutputState_Init(TM_Struct* TMx, BitAction PinState)
{
    uint8_t temp;
    
    temp = TMx->OSCR.B[1];
    temp |= TM_OS3H_unLock;
    
    if (PinState == SET)
        temp |= TM_OS3H_State;
    else
        temp &= ~TM_OS3H_State;
        
    TMx->OSCR.B[1] = temp;
}
///@}






/** 
 * @name		Break configuration
 *
 */ 
///@{  
// Break configuration
/**
 *******************************************************************************
 * @brief	    Enable external trigger event for Break
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	BKSrc: select external trigger event 
 *  @arg\b      TMBK_ExtPin : TM36 Break External trigger pin   
 *  @arg\b      TMBK_BOD1 : TM36 Break External trigger event from BOD1 event  
 *  @arg\b      TMBK_INTPB : TM36 Break External trigger event from INT_PB
 *  @arg\b      TMBK_ADC0OUT : TM36 Break External trigger event from ADC0_OUT (Window detect)
 *  @arg\b      TMBK_COMP0OUT : TM36 Break External trigger event from Comparator0 output
 *  @arg\b      TMBK_COMP1OUT : TM36 Break External trigger event from Comparator1 output
 *  @arg\b      TMBK_COMP2OUT : TM36 Break External trigger event from Comparator2 output
 *  @arg\b      TMBK_COMP3OUT : TM36 Break External trigger event from Comparator3 output   
 * @param[in] 	NewState: config Break external trigger event function
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_ExternalBreakEvent_Config(TM36, TMBK_COMP0OUT, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_ExternalBreakEvent_Config(TM_Struct* TMx, TM_BKExtSrcDef BKSrc, FunctionalState NewState)
{
    if (NewState == ENABLE)
        TMx->BS.B[1] |= BKSrc;
    else
        TMx->BS.B[1] &= ~BKSrc;
}

/**
 *******************************************************************************
 * @brief	    Enable internal trigger event for Break
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	BKSrc: select internal trigger event 
 *  @arg\b      TMBK_ClockFailure : Clock failure event  
 *  @arg\b      TMBK_CPULOCKUP : CPU LOCKUP
 * @param[in] 	NewState: config Break internal trigger event function
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_InternalBreakEvent_Config(TM36, TMBK_ClockFailure, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_InternalBreakEvent_Config(TM_Struct* TMx, TM_BKIntSrcDef BKSrc, FunctionalState NewState)
{
    if (NewState == ENABLE)
        TMx->BS.B[2] |= BKSrc;
    else
        TMx->BS.B[2] &= ~BKSrc;
}

/**
 *******************************************************************************
 * @brief	    Generate the Break event by software.
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	NewState: Generate Break event 
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_BreakTrigger_SW(TM36, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_BreakTrigger_SW(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->BS.MBIT.BKSW_EN = NewState;
}

/**
 *******************************************************************************
 * @brief	    Enable Break function for channel3
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	NewState: config break function for OC3
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_BreakCH3_Cmd(TM36, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_BreakCH3_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->BS.MBIT.BK_EN3 = NewState;
}

/**
 *******************************************************************************
 * @brief	    Enable Break function for channels (CH0~CH2)
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	NewState: config break function for OC0~2
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_BreakCH012_Cmd(TM36, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_BreakCH012_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->BS.MBIT.BK_EN = NewState;
}

/**
 *******************************************************************************
 * @brief	    Config Break active method
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	BKMode: select the other (Latch/Cycle-by-Cycle)
 *  @arg\b      TM_Latch : latch mode 
 *  @arg\b      TM_CycleByCycle : cycle by cycle mode
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_BreakMode_Select(TM36, TM_Latch);
 * @endcode
 *******************************************************************************
 */
void TM_BreakMode_Select(TM_Struct* TMx, TM_BKModeDef BKMode)
{
    TMx->BS.MBIT.BK_MDS = BKMode;
}

/**
 *******************************************************************************
 * @brief	    Config channel-0 output method when break happended
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	BKPinMode: select pin output mode
 *  @arg\b      TM_BKStop : output Break Stop state 
 *  @arg\b      TM_BKHold : hold in current state
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC0BreakControl_Select(TM36, TM_BKStop);
 * @endcode
 *******************************************************************************
 */
void TM_OC0BreakControl_Select(TM_Struct* TMx, TM_BKPinModeDef BKPinMode)
{
    TMx->BS.MBIT.BK0_CTL = BKPinMode;
}


/**
 *******************************************************************************
 * @brief	    Config channel-1 output method when break happended
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	BKPinMode: select pin output mode
 *  @arg\b      TM_BKStop : output Break Stop state 
 *  @arg\b      TM_BKHold : hold in current state
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC1BreakControl_Select(TM36, TM_BKStop);
 * @endcode
 *******************************************************************************
 */
void TM_OC1BreakControl_Select(TM_Struct* TMx, TM_BKPinModeDef BKPinMode)
{
    TMx->BS.MBIT.BK1_CTL = BKPinMode;
}

/**
 *******************************************************************************
 * @brief	    Config channel-2 output method when break happended
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	BKPinMode: select pin output mode
 *  @arg\b      TM_BKStop : output Break Stop state 
 *  @arg\b      TM_BKHold : hold in current state
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC2BreakControl_Select(TM36, TM_BKStop);
 * @endcode
 *******************************************************************************
 */
void TM_OC2BreakControl_Select(TM_Struct* TMx, TM_BKPinModeDef BKPinMode)
{
    TMx->BS.MBIT.BK2_CTL = BKPinMode;
}

/**
 *******************************************************************************
 * @brief	    Config channel-3 output method when break happended
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	BKPinMode: select pin output mode
 *  @arg\b      TM_BKStop : output Break Stop state 
 *  @arg\b      TM_BKHold : hold in current state
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_OC3BreakControl_Select(TM36, TM_BKStop);
 * @endcode
 *******************************************************************************
 */
void TM_OC3BreakControl_Select(TM_Struct* TMx, TM_BKPinModeDef BKPinMode)
{
    TMx->BS.MBIT.BK3_CTL = BKPinMode;
}
///@}



/**
 * @name	preload (event/output channel) configuration
 *   		
 */ 
///@{  
/**
 *******************************************************************************
 * @brief	    Config preload event source
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @param[in] 	PreLoad: select preload event source from
 *  @arg\b      TM_Preload_XOR : XOR (IN0,IN1,IN2)
 *  @arg\b      TM_Preload_INT_PB : INT_PB
 *  @arg\b      TM_Preload_INT_PD : INT_PD
 * @param[in] 	NewState: config break function for OC0~2
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note        
 * @par         Example
 * @code
    TM_PreloadEventSource_Config(TM20, TM_Preload_XOR, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_PreloadEventSource_Config(TM_Struct* TMx, uint8_t PreLoad, FunctionalState NewState)
{
    if (NewState == ENABLE)
        TMx->OCCR1.B[3] |= PreLoad;
    else
        TMx->OCCR1.B[3] &= ~PreLoad;
    
}
/**
 *******************************************************************************
 * @brief	    Software trigger preload function
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @param[in] 	NewState: trigger preload 
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note        Set by software and clear by hardware
 * @par         Example
 * @code
    TM_PreloadActive_SW(TM26, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_PreloadActive_SW(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR1.MBIT.POE_SW = NewState;
}
/**
 *******************************************************************************
 * @brief	    Config OC0z output channel for preload function
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @param[in] 	TM_OC0z3ch: config output OC0x ( with or )
 *  @arg\b      TM_POC00 : output OC00
 *  @arg\b      TM_POC01 : output OC01
 *  @arg\b      TM_POC02 : output OC02
 *  @arg\b      TM_POC0_Disable : disable preload output
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_PreloadOC0z_Config(TM26, TM_POC02);
 * @endcode
 *******************************************************************************
 */
void TM_PreloadOC0z_Config(TM_Struct* TMx, uint8_t TM_OC0z3ch)
{
    TMx->OCCR1.B[2] &= ~(TM_POC00 | TM_POC01 | TM_POC02);
    TMx->OCCR1.B[2] |= TM_OC0z3ch;
    
}
/**
 *******************************************************************************
 * @brief	    Config OC1z output channel for preload function
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @param[in] 	TM_OC1z3ch: config output OC1x ( with or )
 *  @arg\b      TM_POC10 : output OC10
 *  @arg\b      TM_POC11 : output OC11
 *  @arg\b      TM_POC12 : output OC12
 *  @arg\b      TM_POC1_Disable : disable preload output
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_PreloadOC1z_Config(TM26, TM_POC10);
 * @endcode
 *******************************************************************************
 */
void TM_PreloadOC1z_Config(TM_Struct* TMx, uint8_t TM_OC1z3ch)
{
    TMx->OCCR1.B[2] &= ~(TM_POC10 | TM_POC11 | TM_POC12);
    TMx->OCCR1.B[2] |= TM_OC1z3ch;
}
///@}



/**
 * @name	Config channel X function mode 
 *   		
 */ 
///@{  
// channel x function mode config
/**
 *******************************************************************************
 * @brief	    Config channel0 function 
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @param[in] 	CHFuncMds: config channel0 function
 *  @arg\b      TM_NoOperation : no operation
 *  @arg\b      TM_InputCapture : 16 bit input capture
 *  @arg\b      TM_OutputCompare : 16bit output compare
 *  @arg\b      TM_8bitx2OutputCompare : 8bitx2 output compare
 *  @arg\b      TM_16bitPWM : 16bit PWM 
 *  @arg\b      TM_8bitx2PWM : 8bitx2 PWM 
 *  @arg\b      TM_16bitPWMDTG : 16bit PWM with Dead Time control (only support TM36)
 *  @arg\b      TM_8bitx2PWMDTG : 8bitx2 PWM with Dead Time control (only support TM36)
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_CH0Function_Config(TM20, TM_InputCapture);
 * @endcode
 *******************************************************************************
 */
void TM_CH0Function_Config(TM_Struct* TMx, CHFMDef CHFuncMds)
{
    TMx->CCMDS.MBIT.CC0_MDS = CHFuncMds;
}
/**
 *******************************************************************************
 * @brief	    Config channel1 function 
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @param[in] 	CHFuncMds: config channel0 function
 *  @arg\b      TM_NoOperation : no operation
 *  @arg\b      TM_InputCapture : 16 bit input capture
 *  @arg\b      TM_OutputCompare : 16bit output compare
 *  @arg\b      TM_8bitx2OutputCompare : 8bitx2 output compare
 *  @arg\b      TM_16bitPWM : 16bit PWM 
 *  @arg\b      TM_8bitx2PWM : 8bitx2 PWM 
 *  @arg\b      TM_16bitPWMDTG : 16bit PWM with Dead Time control (only support TM36)
 *  @arg\b      TM_8bitx2PWMDTG : 8bitx2 PWM with Dead Time control (only support TM36)
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_CH1Function_Config(TM20, TM_16bitPWM);
 * @endcode
 *******************************************************************************
 */
void TM_CH1Function_Config(TM_Struct* TMx, CHFMDef CHFuncMds)
{
    TMx->CCMDS.MBIT.CC1_MDS = CHFuncMds;
}
/**
 *******************************************************************************
 * @brief	    Config channel2 function 
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	CHFuncMds: config channel0 function
 *  @arg\b      TM_NoOperation : no operation
 *  @arg\b      TM_InputCapture : 16 bit input capture
 *  @arg\b      TM_OutputCompare : 16bit output compare
 *  @arg\b      TM_8bitx2OutputCompare : 8bitx2 output compare
 *  @arg\b      TM_16bitPWM : 16bit PWM 
 *  @arg\b      TM_8bitx2PWM : 8bitx2 PWM 
 *  @arg\b      TM_16bitPWMDTG : 16bit PWM with Dead Time control (only support TM36)
 *  @arg\b      TM_8bitx2PWMDTG : 8bitx2 PWM with Dead Time control (only support TM36)
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_CH2Function_Config(TM36, TM_16bitPWMDTG);
 * @endcode
 *******************************************************************************
 */
void TM_CH2Function_Config(TM_Struct* TMx, CHFMDef CHFuncMds)
{
    TMx->CCMDS.MBIT.CC2_MDS = CHFuncMds;
}
/**
 *******************************************************************************
 * @brief	    Config channel3 function 
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	CHFuncMds: config channel0 function
 *  @arg\b      TM_NoOperation : no operation
 *  @arg\b      TM_InputCapture : 16 bit input capture
 *  @arg\b      TM_OutputCompare : 16bit output compare
 *  @arg\b      TM_8bitx2OutputCompare : 8bitx2 output compare
 *  @arg\b      TM_16bitPWM : 16bit PWM 
 *  @arg\b      TM_8bitx2PWM : 8bitx2 PWM 
 *  @arg\b      TM_16bitPWMDTG : 16bit PWM with Dead Time control (only support TM36)
 *  @arg\b      TM_8bitx2PWMDTG : 8bitx2 PWM with Dead Time control (only support TM36)
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_CH3Function_Config(TM36, TM_16bitPWM);
 * @endcode
 *******************************************************************************
 */
void TM_CH3Function_Config(TM_Struct* TMx, CHFMDef CHFuncMds)
{
    TMx->CCMDS.MBIT.CC3_MDS = CHFuncMds;
}
///@}







#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
/** 
 * @name		Timer output delay mode
 *
 */ 
///@{  

/**
 *******************************************************************************
 * @brief	    Enable or Disable the TMx OC/PWM output delay phase.
 * @param[in]   TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	NewState: new state of the TMx peripheral.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_Timer_Cmd(TM20, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_OutputDelayMode_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->OCCR1.MBIT.ODLY_SEL = NewState;
}
///@}
#endif





/**
* @name	    Input Capture : get data (Full Counter) 
 *   		
 */ 
///@{  
// Get capture valure for Full-Counter mode
/**
 *******************************************************************************
 * @brief	    Get channel0 capture data in Input capture (Full Counter mode)
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @return 	    channel0 capture data (32bit-Full counter mode)
 * @note 
 * @par         Example
 * @code
    tmp = TM_GetIC0Value(TM20);
 * @endcode
 *******************************************************************************
 */
uint32_t TM_GetIC0Value(TM_Struct* TMx)
{
    ctype WW;
    
    WW.H[1] = TMx->CC0A.H[0];
    WW.H[0] = TMx->CC0B.H[0];
    return WW.W;
}
/**
 *******************************************************************************
 * @brief	    Get channel1 capture data in Input capture (Full Counter mode)
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @return 	    channel1 capture data (32bit-Full counter mode)
 * @note 
 * @par         Example
 * @code
    tmp = TM_GetIC1Value(TM26);
 * @endcode
 *******************************************************************************
 */
uint32_t TM_GetIC1Value(TM_Struct* TMx)
{
    ctype WW;
    
    WW.H[1] = TMx->CC1A.H[0];
    WW.H[0] = TMx->CC1B.H[0];
    return WW.W;
}
/**
 *******************************************************************************
 * @brief	    Get channel2 capture data in Input capture (Full Counter mode)
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @return 	    channel2 capture data (32bit-Full counter mode)
 * @note 
 * @par         Example
 * @code
    tmp = TM_GetIC2Value(TM36);
 * @endcode
 *******************************************************************************
 */
uint32_t TM_GetIC2Value(TM_Struct* TMx)
{
    ctype WW;
    
    WW.H[1] = TMx->CC2A.H[0];
    WW.H[0] = TMx->CC2B.H[0];
    return WW.W;
}
/**
 *******************************************************************************
 * @brief	    Get channel3 capture data in Input capture (Full Counter mode)
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @return 	    channel3 capture data (32bit-Full counter mode)
 * @note 
 * @par         Example
 * @code
    tmp = TM_GetIC3Value(TM36);
 * @endcode
 *******************************************************************************
 */
uint32_t TM_GetIC3Value(TM_Struct* TMx)
{
    ctype WW;
    
    WW.H[1] = TMx->CC3A.H[0];
    WW.H[0] = TMx->CC3B.H[0];
    return WW.W;
}
///@}





/**
* @name	    Config input capture data with 'OverWrite' or 'Keep' mode
 *   		
 */ 
///@{  
// Config input capture data mode
/**
 *******************************************************************************
 * @brief	    Config channel0 write mode (overwritten or keep)
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @param[in] 	NewState: config channel0 over writable
 *  @arg\b      TM_OverWrite : Overwritten by new data (default)
 *  @arg\b      TM_Keep : Preserved old data
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_IC0OverWritten_Cmd(TM26, TM_OverWrite);
 * @endcode
 *******************************************************************************
 */
void TM_IC0OverWritten_Cmd(TM_Struct* TMx, OverWriteCmd NewState)
{
    TMx->CR1.MBIT.OVR0_MDS = NewState;
}
/**
 *******************************************************************************
 * @brief	    Config channel1 write mode (overwritten or keep)
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @param[in] 	NewState: config channel1 over writable
 *  @arg\b      TM_OverWrite : Overwritten by new data (default)
 *  @arg\b      TM_Keep : Preserved old data
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_IC1OverWritten_Cmd(TM26, TM_OverWrite);
 * @endcode
 *******************************************************************************
 */
void TM_IC1OverWritten_Cmd(TM_Struct* TMx, OverWriteCmd NewState)
{
    TMx->CR1.MBIT.OVR1_MDS = NewState;
}
/**
 *******************************************************************************
 * @brief	    Config channel2 write mode (overwritten or keep)
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	NewState: config channel2 over writable
 *  @arg\b      TM_OverWrite : Overwritten by new data (default)
 *  @arg\b      TM_Keep : Preserved old data
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_IC2OverWritten_Cmd(TM36, TM_Keep);
 * @endcode
 *******************************************************************************
 */
void TM_IC2OverWritten_Cmd(TM_Struct* TMx, OverWriteCmd NewState)
{
    TMx->CR1.MBIT.OVR2_MDS = NewState;
}
/**
 *******************************************************************************
 * @brief	    Config channel3 write mode (overwritten or keep)
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	NewState: config channel3 over writable
 *  @arg\b      TM_OverWrite : Overwritten by new data (default)
 *  @arg\b      TM_Keep : Preserved old data
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_IC3OverWritten_Cmd(TM36, TM_Keep);
 * @endcode
 *******************************************************************************
 */
void TM_IC3OverWritten_Cmd(TM_Struct* TMx, OverWriteCmd NewState)
{
    TMx->CR1.MBIT.OVR3_MDS = NewState;
}
///@}




/**
* @name	    Software trigger to capture (Rising or Falling edge)
 *   		
 */ 
///@{  
// Software trigger to capture
/**
 *******************************************************************************
 * @brief	    Software trigger rising-edge event to capture data for channel0
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @param[in] 	NewState: Software channel0 trigger rising capture 
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note        Set by software and clear by hardware
 * @par         Example
 * @code
    TM_RisingCaptureIC0_SW(TM26, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_RisingCaptureIC0_SW(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CR1.MBIT.CC0A_SEN = NewState;
}
/**
 *******************************************************************************
 * @brief	    Software trigger rising-edge event to capture data for channel1
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @param[in] 	NewState: Software channel1 trigger rising capture 
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note        Set by software and clear by hardware
 * @par         Example
 * @code
    TM_RisingCaptureIC1_SW(TM26, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_RisingCaptureIC1_SW(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CR1.MBIT.CC1A_SEN = NewState;
}
/**
 *******************************************************************************
 * @brief	    Software trigger rising-edge event to capture data for channel2
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	NewState: Software channel2 trigger rising capture 
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note        Set by software and clear by hardware
 * @par         Example
 * @code
    TM_RisingCaptureIC2_SW(TM36, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_RisingCaptureIC2_SW(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CR1.MBIT.CC2A_SEN = NewState;
}
/**
 *******************************************************************************
 * @brief	    Software trigger rising-edge event to capture data for channel3
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	NewState: Software channel3 trigger rising capture 
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note        Set by software and clear by hardware
 * @par         Example
 * @code
    TM_RisingCaptureIC3_SW(TM36, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_RisingCaptureIC3_SW(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CR1.MBIT.CC3A_SEN = NewState;
}
/**
 *******************************************************************************
 * @brief	    Software trigger falling-edge event to capture data for channel0
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @param[in] 	NewState: Software channel0 trigger falling capture 
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note        Set by software and clear by hardware
 * @par         Example
 * @code
    TM_FallingCaptureIC0_SW(TM20, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_FallingCaptureIC0_SW(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CR1.MBIT.CC0B_SEN = NewState;
}
/**
 *******************************************************************************
 * @brief	    Software trigger falling-edge event to capture data for channel1
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @param[in] 	NewState: Software channel1 trigger falling capture
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note        Set by software and clear by hardware
 * @par         Example
 * @code
    TM_FallingCaptureIC1_SW(TM26, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_FallingCaptureIC1_SW(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CR1.MBIT.CC1B_SEN = NewState;
}
/**
 *******************************************************************************
 * @brief	    Software trigger falling-edge event to capture data for channel2
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	NewState: Software channel2 trigger falling capture
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note        Set by software and clear by hardware
 * @par         Example
 * @code
    TM_FallingCaptureIC2_SW(TM36, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_FallingCaptureIC2_SW(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CR1.MBIT.CC2B_SEN = NewState;
}
/**
 *******************************************************************************
 * @brief	    Software trigger falling-edge event to capture data for channel3
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	NewState: Software channel3 trigger falling capture
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note        Set by software and clear by hardware
 * @par         Example
 * @code
    TM_FallingCaptureIC3_SW(TM36, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_FallingCaptureIC3_SW(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CR1.MBIT.CC3B_SEN = NewState;
}
///@}




/**
* @name	    Input Capture : get data (Casade or separate mode)
 *   		
 */ 
///@{  
// get capture value for cascade/separate mode
/**
 *******************************************************************************
 * @brief	    Get channel0 capture data in Input capture mode
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @return 	    channel0 capture data (16bit)
 * @note 
 * @par         Example
 * @code
    tmp = TM_GetCC0A(TM20);
 * @endcode
 *******************************************************************************
 */
uint16_t TM_GetCC0A(TM_Struct* TMx)
{
    return TMx->CC0A.H[0];
}
/**
 *******************************************************************************
 * @brief	    Get channel1 capture data in Input capture mode
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @return 	    channel1 capture data (16bit)
 * @note 
 * @par         Example
 * @code
    tmp = TM_GetCC1A(TM20);
 * @endcode
 *******************************************************************************
 */
uint16_t TM_GetCC1A(TM_Struct* TMx)
{
    return TMx->CC1A.H[0];
}
/**
 *******************************************************************************
 * @brief	    Get channel2 capture data in Input capture mode
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @return 	    channel2 capture data (16bit)
 * @note 
 * @par         Example
 * @code
    tmp = TM_GetCC2A(TM36);
 * @endcode
 *******************************************************************************
 */
uint16_t TM_GetCC2A(TM_Struct* TMx)
{
    return TMx->CC2A.H[0];
}
/**
 *******************************************************************************
 * @brief	    Get channel3 capture data in Input capture mode
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @return 	    channel3 capture data (16bit)
 * @note 
 * @par         Example
 * @code
    tmp = TM_GetCC3A(TM36);
 * @endcode
 *******************************************************************************
 */
uint16_t TM_GetCC3A(TM_Struct* TMx)
{
    return TMx->CC3A.H[0];
}
/**
 *******************************************************************************
 * @brief	    Get channel0 capture data in Input capture mode
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @return 	    channel0 capture data (16bit)
 * @note 
 * @par         Example
 * @code
    tmp = TM_GetCC0B(TM36);
 * @endcode
 *******************************************************************************
 */
uint16_t TM_GetCC0B(TM_Struct* TMx)
{
    return TMx->CC0B.H[0];
}
/**
 *******************************************************************************
 * @brief	    Get channel1 capture data in Input capture mode
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @return 	    channel1 capture data (16bit)
 * @note 
 * @par         Example
 * @code
    tmp = TM_GetCC1B(TM26);
 * @endcode
 *******************************************************************************
 */
uint16_t TM_GetCC1B(TM_Struct* TMx)
{
    return TMx->CC1B.H[0];
}
/**
 *******************************************************************************
 * @brief	    Get channel2 capture data in Input capture mode
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @return 	    channel2 capture data (16bit)
 * @note 
 * @par         Example
 * @code
    tmp = TM_GetCC2B(TM36);
 * @endcode
 *******************************************************************************
 */
uint16_t TM_GetCC2B(TM_Struct* TMx)
{
    return TMx->CC2B.H[0];
}
/**
 *******************************************************************************
 * @brief	    Get channel3 capture data in Input capture mode
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @return 	    channel3 capture data (16bit)
 * @note 
 * @par         Example
 * @code
    tmp = TM_GetCC3B(TM36);
 * @endcode
 *******************************************************************************
 */
uint16_t TM_GetCC3B(TM_Struct* TMx)
{
    return TMx->CC3B.H[0];
}
///@}





/**
 * @name	Set compare/reload value for cascade/separate mode
 *   		
 */ 
///@{  
// set compare/reload value for cascade/separate mode
/**
 *******************************************************************************
 * @brief	    Set channel0 compare data 
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @param[in] 	HfWDat: compare data 
 *      	    specifies the compare value
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_SetCC0A(TM20, 0x1001);
 * @endcode
 *******************************************************************************
 */
void TM_SetCC0A(TM_Struct* TMx,uint16_t HfWDat)
{
    TMx->CC0A.H[0] = HfWDat;
}
/**
 *******************************************************************************
 * @brief	    Set channel1 compare data 
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @param[in] 	HfWDat: compare data 
 *      	    specifies the compare value
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_SetCC1A(TM20, 0x1001);
 * @endcode
 *******************************************************************************
 */
void TM_SetCC1A(TM_Struct* TMx,uint16_t HfWDat)
{
    TMx->CC1A.H[0] = HfWDat;
}
/**
 *******************************************************************************
 * @brief	    Set channel2 compare data 
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @param[in] 	HfWDat: compare data 
 *      	    specifies the compare value
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_SetCC2A(TM36, 0x1001);
 * @endcode
 *******************************************************************************
 */
void TM_SetCC2A(TM_Struct* TMx,uint16_t HfWDat)
{
    TMx->CC2A.H[0] = HfWDat;
}
/**
 *******************************************************************************
 * @brief	    Set channel3 compare data 
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @param[in] 	HfWDat: compare data 
 *      	    specifies the compare value
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_SetCC3A(TM36, 0x1001);
 * @endcode
 *******************************************************************************
 */
void TM_SetCC3A(TM_Struct* TMx,uint16_t HfWDat)
{
    TMx->CC3A.H[0] = HfWDat;
}
/**
 *******************************************************************************
 * @brief	    Set channel0 reload data 
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @param[in] 	HfWDat: compare data 
 *      	    specifies the reload value for channel0
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_SetCC0B(TM26, 0x1001);
 * @endcode
 *******************************************************************************
 */
void TM_SetCC0B(TM_Struct* TMx,uint16_t HfWDat)
{
    TMx->CC0B.H[0] = HfWDat;
}
/**
 *******************************************************************************
 * @brief	    Set channel1 reload data 
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @param[in] 	HfWDat: compare data 
 *      	    specifies the reload value for channel1
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_SetCC1B(TM26, 0x1001);
 * @endcode
 *******************************************************************************
 */
void TM_SetCC1B(TM_Struct* TMx,uint16_t HfWDat)
{
    TMx->CC1B.H[0] = HfWDat;
}
/**
 *******************************************************************************
 * @brief	    Set channel2 reload data 
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @param[in] 	HfWDat: compare data 
 *      	    specifies the reload value for channel2
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_SetCC2B(TM36, 0x1001);
 * @endcode
 *******************************************************************************
 */
void TM_SetCC2B(TM_Struct* TMx,uint16_t HfWDat)
{
    TMx->CC2B.H[0] = HfWDat;
}
/**
 *******************************************************************************
 * @brief	    Set channel3 reload data 
 * @param[in]	TMx: where x can 2x,36 to select the TM peripheral.
 * @param[in] 	HfWDat: compare data 
 *      	    specifies the reload value for channel3
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_SetCC3B(TM36, 0x1001);
 * @endcode
 *******************************************************************************
 */
void TM_SetCC3B(TM_Struct* TMx,uint16_t HfWDat)
{
    TMx->CC3B.H[0] = HfWDat;
}
///@}





/**
 * @name	Generate flag by software
 *   		
 */ 
///@{  
// Generate flag by software 
/**
 *******************************************************************************
 * @brief	    Software setting CF0A flag
 * @param[in]	TMx: where x can be 2x and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: new state of CF0A flag.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note        Set by software and clear by hardware
 * @par         Example
 * @code
    TM_GenerateCF0A_SW(TM26, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_GenerateCF0A_SW(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CR1.MBIT.CC0A_SEN = NewState;
}
/**
 *******************************************************************************
 * @brief	    Software setting CF1A flag
 * @param[in]	TMx: where x can be 2x and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: new state of CF1A flag.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note        Set by software and clear by hardware
 * @par         Example
 * @code
    TM_GenerateCF1A_SW(TM26, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_GenerateCF1A_SW(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CR1.MBIT.CC1A_SEN = NewState;
}
/**
 *******************************************************************************
 * @brief	    Software setting CF2A flag
 * @param[in]	TMx: where x can be 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: new state of CF2A flag.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note        Set by software and clear by hardware
 * @par         Example
 * @code
    TM_GenerateCF2A_SW(TM36, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_GenerateCF2A_SW(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CR1.MBIT.CC2A_SEN = NewState;
}
/**
 *******************************************************************************
 * @brief	    Software setting CF3A flag
 * @param[in]	TMx: where x can be 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: new state of CF3A flag.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note        Set by software and clear by hardware
 * @par         Example
 * @code
    TM_GenerateCF3A_SW(TM36, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_GenerateCF3A_SW(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CR1.MBIT.CC3A_SEN = NewState;
}
/**
 *******************************************************************************
 * @brief	    Software setting CF0B flag
 * @param[in]	TMx: where x can be 2x and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: new state of CF0B flag.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note        Set by software and clear by hardware
 * @par         Example
 * @code
    TM_GenerateCF0B_SW(TM26, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_GenerateCF0B_SW(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CR1.MBIT.CC0B_SEN = NewState;
}
/**
 *******************************************************************************
 * @brief	    Software setting CF1B flag
 * @param[in]	TMx: where x can be 2x and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: new state of CF1B flag.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note        Set by software and clear by hardware
 * @par         Example
 * @code
    TM_GenerateCF1B_SW(TM26, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_GenerateCF1B_SW(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CR1.MBIT.CC1B_SEN = NewState;
}
/**
 *******************************************************************************
 * @brief	    Software setting CF2B flag
 * @param[in]	TMx: where x can be 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: new state of CF2B flag.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note        Set by software and clear by hardware
 * @par         Example
 * @code
    TM_GenerateCF2B_SW(TM36, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_GenerateCF2B_SW(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CR1.MBIT.CC2B_SEN = NewState;
}
/**
 *******************************************************************************
 * @brief	    Software setting CF3B flag
 * @param[in]	TMx: where x can be 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: new state of CF3B flag.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note        Set by software and clear by hardware
 * @par         Example
 * @code
    TM_GenerateCF3B_SW(TM36, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_GenerateCF3B_SW(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CR1.MBIT.CC3B_SEN = NewState;
}
///@}




/**
 * @name	Control reload (simultaneously reload / stop reload)
 *   		
 */ 
///@{  
// control reload (simultaneously reload / stop reload)
/**
 *******************************************************************************
 * @brief	    Reload simultaneously to prevent glitch
 * @param[in]	TMx: where x can be 2x and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: control reload key
 *  @arg\b      TM_SimultaneouslyReload : simultaneously reload from CCxB 
 *              to CCxA when counter overflow/underflow
 *  @arg\b      TM_StopReload : stop reload from CCxB to CCxA when counter 
 *              overflow/underflow
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_ReloadFromCCxB_Cmd(TM26, TM_StopReload);
 * @endcode
 *******************************************************************************
 */
void TM_ReloadFromCCxB_Cmd(TM_Struct* TMx, ReloadTimeDef NewState)
{
    TMx->CCMDS.MBIT.OC_LCK = NewState;
}
///@}





/**
 * @name	Edge or Central align for PWM mode
 *   		
 */ 
///@{  
// Edge or Central align for PWM mode
/**
 *******************************************************************************
 * @brief	    Config Edge or Central align for PWM mode
 * @param[in]	TMx: where x can be 36 to select the TM peripheral.
 * @param[in] 	AMode: config alignment 
 *  @arg\b      TM_EdgeAlign : edge alignment
 *  @arg\b      TM_CenterAlign : Center-alignment 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_AlignmentMode_Select(TM36, TM_CenterAlign);
 * @endcode
 *******************************************************************************
 */
void TM_AlignmentMode_Select(TM_Struct* TMx, AlignMode AMode)
{
    TMx->PWM.MBIT.PWM_MDS = AMode;
}
///@}



/**
 * @name	QEI : count A & B signal (up/down count)
 *   		
 */ 
///@{  
// QEI : count A & B signal (up/down count)
/**
 *******************************************************************************
 * @brief	    QEI mode: special count mode - dpeend IN0/IN1 (please 
 *              reference function table)
 * @param[in]	TMx: where x can be 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	EXUDMds: config alignment 
 *  @arg\b      TM_NoEXUD : No operation (up/down control by TM36_DIR)
 *  @arg\b      TM_IN0POS : IN0 positive (high level up count, low level down count)
 *  @arg\b      TM_IN0NEG : IN0 negative (low level up count, high level down count) 
 *  @arg\b      TM_BOTH : Both TM36_IN0 and TM36_IN1 edge
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_QEI_Select(TM26, TM_BOTH);
 * @endcode
 *******************************************************************************
 */
void TM_QEI_Select(TM_Struct* TMx, EXUDMDSDef EXUDMds)
{
    TMx->TRG.MBIT.QEI_MDS = EXUDMds;
}
/**
 *******************************************************************************
 * @brief	    Reset main counter with QEI index signal
 * @param[in]	TMx: where x can be 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: reset counter when IDX happend
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_QEIReset_Cmd(TM26, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_QEIReset_Cmd(TM_Struct* TMx,FunctionalState NewState)
{
    TMx->TRG.MBIT.IDX_EN = NewState;
}
/**
 *******************************************************************************
 * @brief	    Select QEI index state to reset main counter
 * @param[in]	TMx: where x can be 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	TM_IDXSel:  reset timer transition state 
 *  @arg	    TM_S1toS2 : reset main counter between QEI state 1 and state 2 
 *  @arg	    TM_S2toS3 : reset main counter between QEI state 2 and state 3
 *  @arg	    TM_S3toS4 : reset main counter between QEI state 3 and state 4 
 *  @arg	    TM_S4toS1 : reset main counter between QEI state 4 and state 1 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_QEIResetIDX_Select(TM36, TM_S1toS2);
 * @endcode
 *******************************************************************************
 */
void TM_QEIResetIDX_Select(TM_Struct* TMx,TM_QEIResetIndexDef TM_IDXSel)
{
    TMx->TRG.MBIT.IDX_MDS = TM_IDXSel;
}
/**
 *******************************************************************************
 * @brief	    Inverse QEI direction 
 * @param[in]	TMx: where x can be 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: Invert counting direction 
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_InverseQEIDirection(TM26, DISABLE);
 * @endcode
 *******************************************************************************
 */
void TM_InverseQEIDirection(TM_Struct* TMx,FunctionalState NewState)
{
    TMx->CR0.MBIT.DIR_INV = NewState;
}

///@}



/**
 * @name	Clock out/PWM with AutoStop 
 *   		
 */ 
///@{  
// Clock out/PWM with AutoStop
/**
 *******************************************************************************
 * @brief	    Clock out with AutoStop function
 * @param[in]   TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState:  Auto stop after timer counting overflow/underflow 
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_AutoStop_Cmd(TM10, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_AutoStop_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CR0.MBIT.ASTOP_EN = NewState;
}

#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
/**
 *******************************************************************************
 * @brief	    Repeat clock-out output when AutoStop enable.
 * @param[in]   TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState:  Auto stop after timer counting overflow/underflow 
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_RepeatAutoStopMode_Cmd(TM10, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_RepeatAutoStopMode_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CR0.MBIT.ACLEAR_EN = NewState;
}
#endif

#if defined(MG32_3RD) || defined(MG32_4TH)
/**
 *******************************************************************************
 * @brief	    Control repetition counter (Enable or Disable).
 * @param[in]   TMx: where x can be 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState:  Repetition counter counting underflow 
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_RepetitionCounter_Cmd(TM20, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_RepetitionCounter_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CR0.MBIT.RC_EN = NewState;
}

/**
 *******************************************************************************
 * @brief	    Control PWM output when repetition counter underflow.
 * @param[in]   TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	NewState:  Output PWM before repetition counter underflow 
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_ControlPWM_Cmd(TM20, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_ControlPWM_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CR0.MBIT.RC_STP = NewState;
}

/**
 *******************************************************************************
 * @brief	    Configures the TMx repetition counter and reload value.
 * @param[in]	TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in] 	TM_RCounter : specifies the main counter Register value
 * @param[in] 	TM_RCounterReload : specifies the Prescaler reload Register value
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    // initial repetition counter starts/reload from 0x50. (count down behavior)
    TM_RepetitionCounter_Config(TM20, 0x50, 0x50);
 * @endcode
 *******************************************************************************
 */
void TM_RepetitionCounter_Config(TM_Struct* TMx, uint8_t TM_RCounter, uint8_t TM_RCounterReload)
{
    ctype word;

    word.B[0] = TM_RCounter;
    word.B[2] = TM_RCounterReload;
    TMx->RCNT.W = word.W;
}

/**
 *******************************************************************************
 * @brief       Select the RCNT clock source.
 * @param[in]   TMx: where x can be 20, 26 and 36 to select the TM peripheral.
 * @param[in]   RCNTClockSrc : specifies the repetition counter clock to be used
 *  @arg\b	    TM_RCNT_CKMAIN : the clock from main counter overflow/underflow
 *	@arg\b	    TM_RCNT_CKCKO : the clock from CKO 
 *	@arg\b	    TM_RCNT_TC : the clock from main counter clock 
 * @return		No
 * @note 
 * @par         Example
 * @code
    TM_RepetitionCounterClock_Select(TM20, TM_RCNT_CKMAIN);    
 * @endcode
 *******************************************************************************
 */
void TM_RepetitionCounterClock_Select(TM_Struct* TMx, TM_RCNTClockDef RCNTClockSrc)
{
	TMx->CLK.MBIT.RC_CKS = RCNTClockSrc;
}

#endif
///@}




/**
 * @name	Dead time config 
 *   		
 */ 
///@{  
/**
 *******************************************************************************
 * @brief	    Configures Timer internal clock divider for Deadtime.
 * @param[in]	TMx: where x can be 36 to select the TM 
 *              peripheral.
 * @param[in] 	DTClockDiv : specifies the Main Counter direction to be used
 *  @arg	    TM_DTDIV1 : divided by 1
 *	@arg	    TM_DTDIV2 : divided by 2
 *  @arg	    TM_DTDIV4 : divided by 4
 *	@arg	    TM_DTDIV8 : divided by 8
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_SetDeadZoneClockDivider(TM36, TM_DTDIV2);
 * @endcode
 *******************************************************************************
 */
void TM_SetDeadZoneClockDivider(TM_Struct* TMx, TM_DTClockDivDef DTClockDiv)
{
    TMx->CLK.MBIT.DTG_DIV = DTClockDiv;
}    

/**
 *******************************************************************************
 * @brief	    Config dead time zone (size)
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	DTTime: setting dead time zone size
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_SetDeadTime(TM36, 125);
 * @endcode
 *******************************************************************************
 */
void TM_SetDeadTime(TM_Struct* TMx, uint8_t DTTime)
{
    TMx->PWM.MBIT.DTG_DY = DTTime;
}
///@}




#if defined(MG32_4TH)
/** 
 * @name		Input pin configuration
 *
 */ 
///@{  

/**
 *******************************************************************************
 * @brief	    Enable/Disable Input duty capture. 
 * @param[in]   TMx: where x can be 20 and 36 to select the TM peripheral.
 * @param[in] 	NewState: new state of the TMx all interrupt key.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_DutyCapture_Cmd(TM20, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_DutyCapture_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CR0.MBIT.IDC_EN = NewState;
}
///@}
#endif






/**
 * @name	Interrupt and flag (SET/CLEAR/Config) 
 *   		
 */ 
///@{ 
//
/**
 *******************************************************************************
 * @brief	    Config interrupt source (Enable/Disable)
 * @param[in]   TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	TM_ITSrc: interrupt source. 
 *  @arg	    TMx_IDC_IE : Input duty capture complete interrupt enable. 
 *  @arg	    TMx_RTU_IE : Repetition timer underflow interrupt enable.
 *  @arg	    TMx_QPE_IE : Main Timer QEI phase state transition error detect interrupt enable.
 *  @arg	    TMx_IDX_IE : Main Timer QEI external index signal input active detect interrupt enable.
 *  @arg	    TMx_DIRC_IE: Main Timer up/down counting direction change interrupt enable.
 *  @arg	    TMx_CC3_IE : Timer IC3/OC3 interrupt enable.
 *  @arg	    TMx_CC2_IE : Timer IC2/OC2 interrupt enable.
 *  @arg	    TMx_CC1_IE : Timer IC1/OC1 interrupt enable.
 *  @arg	    TMx_CC0_IE : Timer IC0/OC0 interrupt enable.
 *  @arg	    TMx_TIE2_IE : 2nd Timer overflow/underflow interrupt enable. 
 *  @arg	    TMx_TIE_IE : Timer overflow/underflow interrupt enable. 
 *  @arg	    TMx_EXIE : Timer external trigger interrupt enable. 
 *  @arg	    TMx_BKIE : Timer break input interrupt enable. 
 * @param[in] 	NewState: new state of the TMx interrupt key.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none.
 * @note 
 * @par         Example
 * @code
    TM_IT_Config(TM36, (TMx_CC0_IE | TMx_TIE_IE), ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_IT_Config(TM_Struct* TMx, uint32_t TM_ITSrc, FunctionalState NewState)
{
    if (NewState == ENABLE)
        TMx->INT.W |= TM_ITSrc;
    else
        TMx->INT.W &= ~TM_ITSrc;
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable all interrupt 
 * @param[in]   TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: new state of the TMx all interrupt key.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_ITEA_Cmd(TM20, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_ITEA_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->INT.MBIT.IEA = NewState;
}

/**
 *******************************************************************************
 * @brief	    Get one interrupt source state.
 * @param[in]   TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	TM_ITSTAFlag: interrupt source item
 *  @arg	    TMx_IDCF : Input duty capture complete flag.
 *  @arg	    TMx_RTUF : Repetition timer underflow flag.
 *  @arg	    TMx_QPEF : Main Timer QEI phase state transition error detect flag.
 *	@arg	    TMx_IDXF : Main Timer QEI external index signal input active detect.
 *  @arg	    TMx_DIRCF : Main Timer up/down counting direction change flag.
 *	@arg	    TMx_CF3B : Timer IC3 falling edge flag/OC3 event sub flag.
 *	@arg	    TMx_CF2B : Timer IC2 falling edge flag/OC2 event sub flag.
 *	@arg	    TMx_CF1B : Timer IC1 falling edge flag/OC1 event sub flag.
 *	@arg	    TMx_CF0B : Timer IC0 falling edge flag/OC0 event sub flag.
 *	@arg	    TMx_CF3A : Timer IC3 rising edge flag/OC3 event main flag.
 *	@arg	    TMx_CF2A : Timer IC2 rising edge flag/OC2 event main flag.
 *	@arg	    TMx_CF1A : Timer IC1 rising edge flag/OC1 event main flag.
 *	@arg	    TMx_CF0A : Timer IC0 rising edge flag/OC0 event main flag.
 *	@arg	    TMx_TUF2 : 2nd Timer underflow flag.
 *	@arg	    TMx_TUF : Main Timer underflow flag.
 *	@arg	    TMx_TOF2 : 2nd Timer overflow flag.
 *	@arg	    TMx_TOF : Main Timer overflow flag.
 *	@arg	    TMx_EXF : Timer external trigger flag.
 *	@arg	    TMx_BKF : Timer break input flag.
 *	@arg	    TMx_DIRF : Main Timer up/down counting flag.
 * @return 	    reference define of DRV_Return.
 *	@arg	    DRV_Happened : The flag happened.
 *	@arg	    DRV_UnHappened : The flag unhappened.
 * @note 
 * @par         Example
 * @code
    if(TM_GetSingleFlagStatus(TM20, TMx_TOF) == DRV_Happened)
    {
        // to do ...
    }
 * @endcode
 *******************************************************************************
 */
DRV_Return TM_GetSingleFlagStatus(TM_Struct* TMx, uint32_t TM_ITSTAFlag)
{
    if (TMx->STA.W & TM_ITSTAFlag)
        return DRV_Happened;
    else
        return DRV_UnHappened;
    
}

/**
 *******************************************************************************
 * @brief	    Get all interrupt source state.
 * @param[in]   TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @return 	    response what happended of STA.
 *  @arg	    TMx_IDCF : Input duty capture complete flag.
 *  @arg	    TMx_RTUF : Repetition timer underflow flag.
 *  @arg	    TMx_QPEF : Main Timer QEI phase state transition error detect flag.
 *	@arg	    TMx_IDXF : Main Timer QEI external index signal input active detect.
 *  @arg	    TMx_DIRCF : Main Timer up/down counting direction change flag.
 *	@arg	    TMx_CF3B : Timer IC3 falling edge flag/OC3 event sub flag.
 *	@arg	    TMx_CF2B : Timer IC2 falling edge flag/OC2 event sub flag.
 *	@arg	    TMx_CF1B : Timer IC1 falling edge flag/OC1 event sub flag.
 *	@arg	    TMx_CF0B : Timer IC0 falling edge flag/OC0 event sub flag.
 *	@arg	    TMx_CF3A : Timer IC3 rising edge flag/OC3 event main flag.
 *	@arg	    TMx_CF2A : Timer IC2 rising edge flag/OC2 event main flag.
 *	@arg	    TMx_CF1A : Timer IC1 rising edge flag/OC1 event main flag.
 *	@arg	    TMx_CF0A : Timer IC0 rising edge flag/OC0 event main flag.
 *	@arg	    TMx_TUF2 : 2nd Timer underflow flag.
 *	@arg	    TMx_TUF : Main Timer underflow flag.
 *	@arg	    TMx_TOF2 : 2nd Timer overflow flag.
 *	@arg	    TMx_TOF : Main Timer overflow flag.
 *	@arg	    TMx_EXF : Timer external trigger flag.
 *	@arg	    TMx_BKF : Timer break input flag.
 *	@arg	    TMx_DIRF : Main Timer up/down counting flag.
 * @note 
 * @par         Example
 * @code
    tmp = TM_GetAllFlagStatus(TM36);
 * @endcode
 *******************************************************************************
 */
uint32_t TM_GetAllFlagStatus(TM_Struct* TMx)
{
    return TMx->STA.W;
}

/**
 *******************************************************************************
 * @brief	    clear one or all interrupt source state.
 * @param[in]   TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	TM_ITSrc: interrupt source item.
 *  @arg	    TMx_IDCF : Input duty capture complete flag.
 *  @arg	    TMx_RTUF : Repetition timer underflow flag.
 *  @arg	    TMx_QPEF : Main Timer QEI phase state transition error detect flag.
 *	@arg	    TMx_IDXF : Main Timer QEI external index signal input active detect.
 *  @arg	    TMx_DIRCF : Main Timer up/down counting direction change flag.
 *	@arg	    TMx_CF3B : Timer IC3 falling edge flag/OC3 event sub flag.
 *	@arg	    TMx_CF2B : Timer IC2 falling edge flag/OC2 event sub flag.
 *	@arg	    TMx_CF1B : Timer IC1 falling edge flag/OC1 event sub flag.
 *	@arg	    TMx_CF0B : Timer IC0 falling edge flag/OC0 event sub flag.
 *	@arg	    TMx_CF3A : Timer IC3 rising edge flag/OC3 event main flag.
 *	@arg	    TMx_CF2A : Timer IC2 rising edge flag/OC2 event main flag.
 *	@arg	    TMx_CF1A : Timer IC1 rising edge flag/OC1 event main flag.
 *	@arg	    TMx_CF0A : Timer IC0 rising edge flag/OC0 event main flag.
 *	@arg	    TMx_TUF2 : 2nd Timer underflow flag.
 *	@arg	    TMx_TUF : Main Timer underflow flag.
 *	@arg	    TMx_TOF2 : 2nd Timer overflow flag.
 *	@arg	    TMx_TOF : Main Timer overflow flag.
 *	@arg	    TMx_EXF : Timer external trigger flag.
 *	@arg	    TMx_BKF : Timer break input flag.
 *	@arg	    TMx_DIRF : Main Timer up/down counting flag.
 * @return 	    none.
 * @note 
 * @par         Example
 * @code
    TM_ClearFlag(TM20, TMx_CF0A);
 * @endcode
 *******************************************************************************
 */
void TM_ClearFlag(TM_Struct* TMx, uint32_t TM_ITSrc)
{
    TMx->STA.W = TM_ITSrc;
}
///@}



/**
 * @name	Update event config routine 
 *   		
 */ 
///@{ 
// Update event config routine 
/**
 *******************************************************************************
 * @brief	    Enable/Diable external trigger event.
 * @param[in]   TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: new state of the External Trigger.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_ExtTRGI_Cmd(TM20, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_ExtTRGI_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CR0.MBIT.EX_EN = NewState;
}
/**
 *******************************************************************************
 * @brief	    Inverse external trigger event 
 * @param[in]   TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: inverse External Trigger
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_InverseExtTRGI_Cmd(TM26, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_InverseExtTRGI_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CR0.MBIT.EX_INV = NewState;
}
/**
 *******************************************************************************
 * @brief	    Enable/Diable external trigger update event.
 * @param[in]   TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: update from External Trigger
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_ExtTRGI2UEV_Cmd(TM36, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_ExtTRGI2UEV_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CR0.MBIT.UEX_EN = NewState;
}
/**
 *******************************************************************************
 * @brief	    Reload main counter by software
 * @param[in]   TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: software control update event
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note        Automatically clear by hardware
 * @par         Example
 * @code
    TM_ForceUpdate_SW(TM26, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_ForceUpdate_SW(TM_Struct* TMx, FunctionalState NewState)
{
    TMx->CR0.MBIT.USW_EN = NewState;
}
/**
 *******************************************************************************
 * @brief	    Enable/Diable update event 
 * @param[in]   TMx: where x can be 00, 01, 10, 16, 20, 26 and 36 to select the TM 
 *              peripheral.
 * @param[in] 	NewState: new state of the update event
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_UEV_Cmd(TM26, ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_UEV_Cmd(TM_Struct* TMx, FunctionalState NewState)
{
    if(NewState == DISABLE)
        TMx->CR0.B[1] |= TM_CR0_UEV_DIS_disable_b1;
    else
        TMx->CR0.B[1] &= ~TM_CR0_UEV_DIS_disable_b1;
}

///@}


/**
 * @name	TM36 channel configuration for DMA 
 *   		
 */ 
///@{ 
// DMA peripheral channel config 
/**
 *******************************************************************************
 * @brief	    Enable/Diable TMx channel for DMA access
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	DMA_TMChannelSrc: interrupt source item
 *  @arg	    TMx_DMA_OC0 : Direct memory access enable for OC0
 *	@arg	    TMx_DMA_OC1 : Direct memory access enable for OC1
 *  @arg	    TMx_DMA_OC2 : Direct memory access enable for OC2
 *	@arg	    TMx_DMA_IC3 : Direct memory access enable for IC3
 * @param[in] 	NewState: new state of the External Trigger
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_DMAChannel_Cmd(TM36, (TMx_DMA_OC0 | TMx_DMA_OC1 | TMx_DMA_OC2), ENABLE);
 * @endcode
 *******************************************************************************
 */
void TM_DMAChannel_Cmd(TM_Struct* TMx, uint32_t DMA_TMChannelSrc, FunctionalState NewState)
{
    if (NewState == ENABLE)
        TMx->CCMDS.W |= DMA_TMChannelSrc;
    else
        TMx->CCMDS.W &= ~DMA_TMChannelSrc;
        
}

/**
 *******************************************************************************
 * @brief	    Config TMx Update event for DMA access
 * @param[in]	TMx: where x can 36 to select the TM peripheral.
 * @param[in] 	TM_UpdateEvent: config DMA update event 
 *  @arg	    TM_UpdateEvent_TOF : request is asserted at TOF active
 *	@arg	    TM_Update_TOF_ITR : request is asserted at both TOF active and 
 *              ITR input signal
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    TM_DMAUpdateMode_Select(TM36, TM_Update_TOF_ITR);
 * @endcode
 *******************************************************************************
 */
void TM_DMAUpdateMode_Select(TM_Struct* TMx, DMA_UpdateEventSel TM_UpdateEvent)
{
    TMx->CCMDS.MBIT.DMA_OMDS = TM_UpdateEvent;
}


///@}

