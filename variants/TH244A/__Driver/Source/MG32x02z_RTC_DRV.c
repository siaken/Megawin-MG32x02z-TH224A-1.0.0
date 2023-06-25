/**
 *******************************************************************************
 *
 * @file        MG32x02z_RTC_DRV.c
 *
 * @brief       This is the C code format driver file for the RTC module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.12
 * @date        2022/09/16
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2018 Megawin Technology Co., Ltd.
 *              All rights reserved.
 *
 *******************************************************************************
 * @par         Disclaimer 
 * The Demo software is provided "AS IS" without any warranty, either 
 * expressed or implied, including, but not limited to, the implied warranties 
 * of merchantability and fitness for a particular purpose. The author will 
 * not be liable for any special, incidental, consequential or indirect 
 * damages due to loss of data or any other reason. 
 * These statements agree with the world wide and local dictated laws about 
 * authorship and violence against these laws. 
 *******************************************************************************
 *******************************************************************************
 */
 
#include "MG32x02z_RTC_DRV.h"


/**
 * @name	Clock
 *   		
 */ 
///@{
/**
 *******************************************************************************
 * @brief  	    Select RTC input clock CK_RTC source.
 * @details  
 * @param[in]   RTC_CLKS:
 * 	@arg\b			RTC_CK_LS.
 * 	@arg\b			RTC_CK_UT.
 * 	@arg\b			RTC_CK_APB
 * 	@arg\b			RTC_TM01_TRGO
 * @return	    	
 * @note
 * @par         Example
 * @code
    RTC_CLK_Select(RTC_CK_LS);
 * @endcode
 *******************************************************************************
 */
void RTC_CLK_Select (RTC_CLKS_TypeDef RTC_CLKS)
{
    RTC->CLK.MBIT.CK_SEL = RTC_CLKS;
}


/**
 *******************************************************************************
 * @brief  	    RTC internal clock CK_RTC_INT input pre-divider.
 * @details  
 * @param[in]   RTC_PDIV:
 * 	@arg\b			RTC_PDIV_4096.
 * 	@arg\b			RTC_PDIV_1.
 * @return	    	
 * @note
 * @par         Example
 * @code
    RTC_PreDivider_Select(RTC_PDIV_4096);
 * @endcode
 *******************************************************************************
 */
void RTC_PreDivider_Select (RTC_PDIVS_TypeDef RTC_PDIV)
{
    RTC->CLK.MBIT.CK_PDIV = RTC_PDIV;
}
 
 
/**
 *******************************************************************************
 * @brief  	    RTC internal clock CK_RTC_INT input divider. 
 * @details  
 * @param[in]   RTC_DIV:
 * 	@arg\b			RTC_DIV_1.
 * 	@arg\b			RTC_DIV_2.
 * 	@arg\b			RTC_DIV_4.
 * 	@arg\b			RTC_DIV_8.
 * @return	    	
 * @note
 * @par         Example
 * @code
    RTC_Divider_Select(RTC_DIV_8);
 * @endcode
 *******************************************************************************
 */
void RTC_Divider_Select (RTC_DIVS_TypeDef RTC_DIV)
{
    RTC->CLK.MBIT.CK_DIV = RTC_DIV;
}
///@}


/**
 * @name	Alarm
 *   		
 */
///@{
/**
 *******************************************************************************
 * @brief  	    Get RTC Alarm compare value register.
 * @details  
 * @return	    RTC ALM value
 * 	@arg\b			0 ~ 4294967295.
 * @note
 * @par         Example
 * @code
    Time = RTC_GetAlarmCompareValue();
 * @endcode
 *******************************************************************************
 */
uint32_t RTC_GetAlarmCompareValue (void)
{
    return RTC->ALM.W;
}
 

/**
 *******************************************************************************
 * @brief  	    Set RTC Alarm compare value register.
 * @details  
 * @param[in]   RTC_ALM:
 * 	@arg\b			0 ~ 4294967295.
 * @return	    	
 * @note
 * @par         Example
 * @code
    RTC_SetAlarmCompareValue(65535);
 * @endcode
 *******************************************************************************
 */
void RTC_SetAlarmCompareValue (uint32_t RTC_ALM)
{
    RTC->ALM.W = RTC_ALM;
}


/**
 *******************************************************************************
 * @brief  	    Get alarm fucntion state.
 * @details  
 * @return	    NewState
 * 	@arg\b			DRV_True.
 * 	@arg\b			DRV_False.
 * @note
 * @par         Example
 * @code
    RTC_GetAlarmState();
 * @endcode
 *******************************************************************************
 */
DRV_Return RTC_GetAlarmState (void)
{
    DRV_Return bitstatus = DRV_False;
    
    if(RTC->CR0.MBIT.ALM_EN != 0)
        bitstatus = DRV_True;

    return bitstatus;
}


/**
 *******************************************************************************
 * @brief  	    Enable or disable alarm fucntion.
 * @details  
 * @param[in]   NewState:
 * 	@arg\b			ENABLE.
 * 	@arg\b			DISABLE.
 * @return	    	
 * @note
 * @par         Example
 * @code
    RTC_Alarm_Cmd(ENABLE);
 * @endcode
 *******************************************************************************
 */
void RTC_Alarm_Cmd (FunctionalState NewState)
{
    uint8_t Reg;
    
    Reg = RTC->CR0.B[0];
    if(NewState != DISABLE)
    {
        Reg |= RTC_ALM_EN;
    }
    else
    {
        Reg &= ~RTC_ALM_EN;
    }
    
    RTC->CR0.B[0] = Reg;
}
///@}


/**
 * @name	Capture, Reload And Mode
 *   		
 */ 
///@{
/**
 *******************************************************************************
 * @brief  	    Get RTC counter reload register.
 * @details  
 * @return	    RCR value
 * 	@arg\b			0 ~ 4294967295.
 * @note
 * @par         Example
 * @code
    Time = RTC_GetReloadReg();
 * @endcode
 *******************************************************************************
 */
uint32_t RTC_GetReloadReg (void)
{ 
    return RTC->RLR.W;
}


/**
 *******************************************************************************
 * @brief  	    Get RTC counter capture register.
 * @details  
 * @return	    CAP value
 * 	@arg\b			0 ~ 4294967295.
 * @note
 * @par         Example
 * @code
    Time = RTC_GetCaptureReg();
 * @endcode
 *******************************************************************************
 */
uint32_t RTC_GetCaptureReg (void)
{ 
    return RTC->CAP.W;
}

 
/**
 *******************************************************************************
 * @brief  	    Set RTC counter reload register. 
 * @details  
 * @param[in]   RTC_RCR:
 * 	@arg\b			0 ~ 4294967295.
 * @return	    	
 * @note
 * @par         Example
 * @code
    RTC_SetReloadReg(65536);
 * @endcode
 *******************************************************************************
 */
void RTC_SetReloadReg (uint32_t RTC_RCR)
{
    RTC->RLR.W = RTC_RCR;
}
///@}


/**
 * @name	Command & Mode
 *   		
 */ 
///@{
/**
 *******************************************************************************
 * @brief  	    Enable or disable RTC function 
 * @details  
 * @param[in]   NewState:
 * 	@arg\b			ENABLE.
 * 	@arg\b			DISABLE.
 * @return	    	
 * @note
 * @par         Example
 * @code
    RTC_Cmd(ENABLE);
 * @endcode
 *******************************************************************************
 */
void RTC_Cmd (FunctionalState NewState)
{
    uint8_t Reg;
    
    Reg = RTC->CR0.B[0];
    if(NewState != DISABLE)
    {
        Reg |= RTC_CR0_EN;
    }
    else
    {
        Reg &= ~RTC_CR0_EN;
    }
    RTC->CR0.B[0] = Reg;
}

/**
 *******************************************************************************
 * @brief  	    RTC_RCR register control mode select
 * @details  
 * @param[in]   RTC_MODS:
 * 	@arg\b			RTC_RCR_MOD_DirectlyCapture.
 * 	@arg\b			RTC_RCR_MOD_DelayedCapture.
 * 	@arg\b			RTC_RCR_MOD_ForceReload
 * 	@arg\b			RTC_RCR_MOD_AutoReload
 * @return	    	
 * @note
 * @par         Example
 * @code
    RTC_RCR_Mode_Select(RTC_RCR_MOD_ForceReload);
 * @endcode
 *******************************************************************************
 */
void RTC_RCR_Mode_Select (RTC_RCR_MODS_TypeDef RTC_MODS)
{
    RTC->CR0.MBIT.RCR_MDS = RTC_MODS;
}
///@}


/**
 * @name    Wake Up
 *   		
 */ 
///@{
/**
 *******************************************************************************
 * @brief  	    Configure RTC detect RTC_XXXX flag wakeup from STOP mode.
 * @details  
 * @param[in]   RTC_WK:
 * 	@arg\b			RTC_TF_WPEN.
 * 	@arg\b			RTC_PC_WPEN.
 * 	@arg\b			RTC_ALM_WPEN.
 * @param[in]   NewState:
 * 	@arg\b			ENABLE.
 * 	@arg\b			DISABLE.
 * @return	    	
 * @note
 * @par         Example
 * @code
    RTC_StopModeWakeUpEvent_Config((RTC_TF_WPEN | RTC_PC_WPEN), ENABLE);
 * @endcode
 *******************************************************************************
 */
void RTC_StopModeWakeUpEvent_Config (uint32_t RTC_WK, FunctionalState NewState)
{
    uint32_t Reg;
    
    Reg = RTC->CR0.W;
    if(NewState != DISABLE)
    {
        Reg |= RTC_WK;
    }
    else
    {
        Reg &= ~RTC_WK;
    }
    RTC->CR0.W = Reg;
}
///@}


/**
 * @name	Output Signal
 *   		
 */ 
///@{
/**
 *******************************************************************************
 * @brief  	    RTC output signal select.
 * @details  
 * @param[in]   RTC_OUTS:
 * 	@arg\b			RTC_ALM.
 * 	@arg\b			RTC_PC.
 * 	@arg\b		    RTC_TS.
 * 	@arg\b	        RTC_TO.
 * @return	    	
 * @note
 * @par         Example
 * @code
    RTC_OutputSignal_Select(RTC_PC);
 * @endcode
 *******************************************************************************
 */
void RTC_OutputSignal_Select (RTC_OUTS_TypeDef RTC_OUTS)
{
    RTC->CR0.MBIT.OUT_SEL = RTC_OUTS;
}
 
/**
 *******************************************************************************
 * @brief  	    RTC_OUT output signal initial state. 
 * @details  
 * @param[in]   NewState:
 * 	@arg\b			DISABLE.
 * 	@arg\b			ENABLE.
 * @return	    	
 * @note
 * @par         Example
 * @code
    RTC_InitOutputSignalState_Cmd(ENABLE);
 * @endcode
 *******************************************************************************
 */
void RTC_InitOutputSignalState_Cmd (FunctionalState NewState)
{
    uint8_t Reg;
    
    Reg = RTC->CR0.B[1];
    if(NewState != DISABLE)
    {
        Reg |= RTC_OUT_MASK;
    }
    else
    {
        Reg &= ~RTC_OUT_MASK;
    }
    Reg |= RTC_OUT_UNLOCK;
    
    RTC->CR0.B[1] = Reg;
}
///@}


/**
 * @name	Trigger
 *   		
 */ 
///@{
/**
 *******************************************************************************
 * @brief  	    RTC time stamp trigger edge select. 
 * @details  
 * @param[in]   RTC_TSS:
 * 	@arg\b			RTC_TS_TRGS_Disable.
 * 	@arg\b			RTC_TS_TRGS_RisingEdge.
 * 	@arg\b			RTC_TS_TRGS_FallingEdge.
 * 	@arg\b			RTC_TS_TRGS_DualEdge.
 * @return	    	
 * @note
 * @par         Example
 * @code
    RTC_TriggerStamp_Select(RTC_TS_TRGS_FallingEdge);
 * @endcode
 *******************************************************************************
 */
void RTC_TriggerStamp_Select (RTC_TS_TRGS_TypeDef RTC_TSS)
{
    RTC->CR0.MBIT.TS_TRGS = RTC_TSS;
}
 
/**
 *******************************************************************************
 * @brief  	    Trigger RTC timer counter reload and software capture start enable.
 * @details  
 * @return	    	
 * @note
 * @par         Example
 * @code
    RTC_TriggerStamp_SW();
 * @endcode
 *******************************************************************************
 */
void RTC_TriggerStamp_SW (void)
{
    RTC->CR1.B[0] = RTC_START;
}
///@}


/**
 * @name	Interrupt
 *   		
 */ 
///@{
/**
 *******************************************************************************
 * @brief  	    Get all intterupt source state. 
 * @details  
 * @return	    	
 * @note
 * @par         Example
 * @code
    FLAG = RTC_GetAllFlagStatus();
 * @endcode
 *******************************************************************************
 */
uint32_t RTC_GetAllFlagStatus (void)
{
    return RTC->STA.W;
}

/**
 *******************************************************************************
 * @brief  	    Get one intterupt source state.
 * @details  
 * @param[in]   RTC_Flag:
 * 	@arg\b			RTC_RCRF.
 * 	@arg\b			RTC_TOF
 * 	@arg\b			RTC_TSF
 * 	@arg\b			RTC_PCF
 * 	@arg\b			RTC_ALMF.
 * @return	    DRV_Return: Rerutn RTC_ITSrc status. 
 * 	@arg\b			DRV_Happened.
 * 	@arg\b			DRV_UnHappened.  	
 * @note
 * @par         Example
 * @code
    RTC_GetSingleFlagStatus(RTC_RCRF);
 * @endcode
 *******************************************************************************
 */
DRV_Return RTC_GetSingleFlagStatus (uint32_t RTC_Flag)
{
    DRV_Return bitstatus = DRV_Normal;
    
    if ((RTC->STA.W & RTC_Flag) != (uint32_t)DRV_Normal)
    {
        bitstatus = DRV_Happened;
    }
    return  bitstatus;
}
 
/**
 *******************************************************************************
 * @brief  	    Clear intterupt source state. 
 * @details  
 * @param[in]   RTC_Flag:
 * 	@arg\b			RTC_RCRF.
 * 	@arg\b			RTC_TOF
 * 	@arg\b			RTC_TSF
 * 	@arg\b			RTC_PCF
 * 	@arg\b			RTC_ALMF.
 * 	@arg\b			RTC_ALLF.
 * @return	    	
 * @note
 * @par         Example
 * @code
    RTC_ClearFlag(RTC_TSF | RTC_PCF);
 * @endcode
 *******************************************************************************
 */
void RTC_ClearFlag (uint32_t RTC_Flag)
{
    RTC->STA.W = RTC_Flag;
}

/**
 *******************************************************************************
 * @brief  	    Config interrupt source.
 * @details  
 * @param[in]   RTC_INT:
 * 	@arg\b			RTC_INT_RCR.
 * 	@arg\b			RTC_INT_TO.
 * 	@arg\b			RTC_INT_TS
 * 	@arg\b			RTC_INT_PC
 * 	@arg\b			RTC_INT_ALM
 * @param[in]   NewState:
 * 	@arg\b			ENABLE.
 * 	@arg\b			DISABLE.
 * @return	    	
 * @note
 * @par         Example
 * @code
    RTC_IT_Config(RTC_INT_RCR,ENABLE);
 * @endcode
 *******************************************************************************
 */
void RTC_IT_Config (uint32_t RTC_INT, FunctionalState NewState)
{
    uint32_t Reg;
    
    Reg = RTC->INT.W;
    if(NewState != DISABLE)
    {
        Reg |= RTC_INT;
    }
    else
    {
        NewState &= ~RTC_INT;
    }
    RTC->INT.W = Reg;
}
 
/**
 *******************************************************************************
 * @brief  	    RTC enable or disable all interrupt.. 
 * @details  
 * @param[in]   NewState:
 * 	@arg\b			ENABLE.
 * 	@arg\b			DISABLE.
 * @return	    	
 * @note
 * @par         Example
 * @code
    RTC_ITEA_Cmd(ENABLE);
 * @endcode
 *******************************************************************************
 */
void RTC_ITEA_Cmd (FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        RTC->INT.MBIT.IEA = 1;
    }
    else
    {
        RTC->INT.MBIT.IEA = 0;
    }
}
///@}


