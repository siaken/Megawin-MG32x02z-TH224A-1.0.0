/**
 *******************************************************************************
 *
 * @file        MG32x02z_PW_DRV.c
 *
 * @brief       This is the C code format driver file for PW module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.24
 * @date        2022/08/22
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2021 Megawin Technology Co., Ltd.
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


#include "MG32x02z_PW_DRV.h"

/**
 * @name    LDO configuration
 *
 */ 
///@{  
/**
 *******************************************************************************
 * @brief       Core voltage LDO mode select when STOP mode.
 * @details  
 * @param[in]   LdoSelect:
 *  @arg\b          PW_Normal_LDO.
 *  @arg\b          PW_LowPower_LDO.
 * @return
 * @note
 * @par         Example
 * @code
    PW_STOPModeLDO_Select(PW_LowPower_LDO);
 * @endcode
 *******************************************************************************
 */
void PW_STOPModeLDO_Select (PW_LDOMode_TypeDef LdoSelect)
{
    PW->CR0.MBIT.LDO_STP = LdoSelect;
}


/**
 *******************************************************************************
 * @brief       Core voltage LDO mode select when ON mode.
 * @details  
 * @param[in]   LdoSelect:
 *  @arg\b          PW_Normal_LDO.
 *  @arg\b          PW_LowPower_LDO.
 * @return
 * @note
 * @par         Example
 * @code
    PW_ONModeLDO_Select(PW_Normal_LDO);
 * @endcode
 *******************************************************************************
 */
void PW_ONModeLDO_Select (PW_LDOMode_TypeDef LdoSelect)
{
    PW->CR0.MBIT.LDO_ON = LdoSelect;
}
///@}


/**
 * @name	BODx & others
 *   		
 */ 
///@{
#if (defined(PW_CR0_BOD2_TRGS_mask_w))
/**
 *******************************************************************************
 * @brief       BOD2 Interrupt trigger selection.
 * @details  
 * @param[in]   BOD2_TRGS:
 *  @arg\b          PW_BODx_Reserved.
 *  @arg\b          PW_BODx_RisingEdge.
 *  @arg\b          PW_BODx_FallingEdge.
 *  @arg\b          PW_BODx_DualEdge.
 * @return
 * @note
 * @par         Example
 * @code
    PW_BOD2Trigger_Select(PW_BODx_FallingEdge);
 * @endcode
 *******************************************************************************
 */
void PW_BOD2Trigger_Select (PW_BODx_TRGS_TypeDef BOD2_TRGS)
{
    PW->CR0.MBIT.BOD2_TRGS = BOD2_TRGS;
}
#endif

#if defined(PW_CR0_BOD2_EN_mask_w) 
/**
 *******************************************************************************
 * @brief       Enable or disable BOD2 fucntion 
 * @details  
 * @param[in]   NewState:
 *  @arg\b          ENABLE.
 *  @arg\b          DISABLE.
 * @return
 * @note
 * @par         Example
 * @code
    PW_BOD2_Cmd(ENABLE);
 * @endcode
 *******************************************************************************
 */
void PW_BOD2_Cmd (FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        PW->CR0.MBIT.BOD2_EN = SET;
    }
    else
    {
        PW->CR0.MBIT.BOD2_EN = CLR;
    }
}
#endif

#if defined(PW_STA_BOD2_S_mask_w)
/**
 *******************************************************************************
 * @brief       Get one intterupt source status
 * @details  
 * @return      DRV_Return: Rerutn CSC_ITSrc status. 
 *  @arg\b          PW_HighThreshold.
 *  @arg\b          PW_LowThreshold.
 * @note
 * @par         Example
 * @code
    Starus = PW_GetBod2Status();
 * @endcode
 *******************************************************************************
 */ 
DRV_Return PW_GetBod2Status (void)
{    
    DRV_Return bitstatus = PW_HighThreshold;
    
    if((PW->STA.MBIT.BOD2_S) != 0)
    {
        bitstatus = PW_LowThreshold;
    }
    else
    {
        bitstatus = PW_HighThreshold;
    }
    return bitstatus;
}
#endif

/**
 *******************************************************************************
 * @brief       BOD1 detect voltage threshold select
 * @details  
 * @param[in]   BOD1_TH:
 *  @arg\b          PW_BOD1_2V0.
 *  @arg\b          PW_BOD1_2V4.
 *  @arg\b          PW_BOD1_3V7.
 *  @arg\b          PW_BOD1_4V2.
 * @return
 * @note
 * @par         Example
 * @code
    PW_BOD1Threshold_Select (PW_BOD1_3V7);
 * @endcode
 *******************************************************************************
 */
void PW_BOD1Threshold_Select (PW_BOD1_TH_TypeDef BOD1_TH)
{
    PW->CR0.MBIT.BOD1_TH = BOD1_TH;
}
 
/**
 *******************************************************************************
 * @brief       BOD1 Interrupt trigger selection.
 * @details  
 * @param[in]   BOD1_TRGS:
 *  @arg\b          PW_BODx_Reserved.
 *  @arg\b          PW_BODx_RisingEdge.
 *  @arg\b          PW_BODx_FallingEdge.
 *  @arg\b          PW_BODx_DualEdge.
 * @return
 * @note
 * @par         Example
 * @code
    PW_BOD1Trigger_Select(PW_BODx_FallingEdge);
 * @endcode
 *******************************************************************************
 */
void PW_BOD1Trigger_Select (PW_BODx_TRGS_TypeDef BOD1_TRGS)
{
    PW->CR0.MBIT.BOD1_TRGS = BOD1_TRGS;
}

/**
 *******************************************************************************
 * @brief       Enable or disable BOD1 fucntion 
 * @details  
 * @param[in]   NewState:
 *  @arg\b          ENABLE.
 *  @arg\b          DISABLE.
 * @return
 * @note
 * @par         Example
 * @code
    PW_BOD1_Cmd(ENABLE);
 * @endcode
 *******************************************************************************
 */
void PW_BOD1_Cmd (FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        PW->CR0.MBIT.BOD1_EN = SET;
    }
    else
    {
        PW->CR0.MBIT.BOD1_EN = CLR;
    }
}

/**
 *******************************************************************************
 * @brief       Enable or disable voltage buffer source.
 * @details  
 * @param[in]   NewState:
 *  @arg\b          ENABLE.
 *  @arg\b          DISABLE.
 * @return
 * @note
 * @par         Example
 * @code
    PW_VoltageBuffer(ENABLE);
 * @endcode
 *******************************************************************************
 */  
void PW_VoltageBuffer (FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        PW->CR0.MBIT.IVR_EN = SET;
    }
    else
    {
        PW->CR0.MBIT.IVR_EN = CLR;
    }
}

/**
 *******************************************************************************
 * @brief       Enable or disable BOD0 fucntion 
 * @details  
 * @param[in]   NewState:
 *  @arg\b          ENABLE.
 *  @arg\b          DISABLE.
 * @return
 * @note
 * @par         Example
 * @code
    PW_BOD0_Cmd(ENABLE);
 * @endcode
 *******************************************************************************
 */
void PW_BOD0_Cmd (FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        PW->CR0.MBIT.BOD0_EN = SET;
    }
    else
    {
        PW->CR0.MBIT.BOD0_EN = CLR;
    }
}

/**
 *******************************************************************************
 * @brief       Get one intterupt source status
 * @details  
 * @return      DRV_Return: Rerutn CSC_ITSrc status. 
 *  @arg\b          PW_HighThreshold.
 *  @arg\b          PW_LowThreshold.
 * @note
 * @par         Example
 * @code
    Starus = PW_GetBod1Status();
 * @endcode
 *******************************************************************************
 */ 
DRV_Return PW_GetBod1Status (void)
{    
    DRV_Return bitstatus = PW_HighThreshold;
    
    if((PW->STA.MBIT.BOD1_S) != 0)
    {
        bitstatus = PW_LowThreshold;
    }
    else
    {
        bitstatus = PW_HighThreshold;
    }
    return bitstatus;
}
///@}


/**
 * @name    Action mode
 *
 */ 
///@{ 
#if defined(PW_CR1_SLP_CMP0_mask_w)
/**
 *******************************************************************************
 * @brief       Peripheral sleep mode continuous run configure.
 * @details  
 * @param[in]   SLP_Periph:
 *  @arg\b          PW_SLPPO_CMP0
 *  @arg\b          PW_SLPPO_CMP1
 *  @arg\b          PW_SLPPO_CMP2 (Support MG32F02A132/A072)
 *  @arg\b          PW_SLPPO_CMP3 (Support MG32F02A132/A072)
 * @param       NewState
 *      @arg        DISABLE
 *      @arg        ENABLE 
 * @return
 * @note
 * @par         Example
 * @code
    PW_PeriphSLEEPModeContinuous_Config(PW_SLPPO_CMP0, ENABLE);
    PW_PeriphSLEEPModeContinuous_Config(PW_SLPPO_CMP1, DISABLE);
 * @endcode
 *******************************************************************************
 */ 
void PW_PeriphSLEEPModeContinuous_Config (PW_SLP_Periph_TypeDef SLP_Periph, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        PW->CR1.W |= SLP_Periph;
    }
    else
    {
        PW->CR1.W &= ~SLP_Periph;
    }
}
#endif

/**
 *******************************************************************************
 * @brief  	    Peripheral stop mode continuous run configure.
 * @details  
 * @param[in]   STP_Periph:
 *  @arg\b          PW_STPPO_POR
 *  @arg\b          PW_STPPO_BOD0
 *  @arg\b          PW_STPPO_BOD1
 *  @arg\b          PW_STPPO_BOD2 (Support MG32F02U128/U064/A128/A064)
 *  @arg\b          PW_STPPO_CMP0
 *  @arg\b          PW_STPPO_CMP1
 *  @arg\b          PW_STPPO_CMP2 (Support MG32F02A132/A072)
 *  @arg\b          PW_STPPO_CMP3 (Support MG32F02A132/A072)
 * @param       NewState
 *      @arg        DISABLE
 *      @arg        ENABLE 
 * @return
 * @note
 * @par         Example
 * @code
    PW_PeriphSTOPModeContinuous_Config(PW_STPPO_BOD1, DISABLE);
    PW_PeriphSTOPModeContinuous_Config(PW_STPPO_CMP0, DISABLE);
 * @endcode
 *******************************************************************************
 */ 
void PW_PeriphSTOPModeContinuous_Config (PW_STP_Periph_TypeDef STP_Periph,FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        PW->CR1.W |= STP_Periph;
    }
    else
    {
        PW->CR1.W &= ~STP_Periph;
    }
}
///@}


/**
 * @name    Wake up
 *
 */ 
///@{  
 /**
 *******************************************************************************
 * @brief       Peripheral event wakeup from STOP mode configure.
 * @details  
 * @param[in]   WKSTP_Periph:
 *  @arg\b          PW_WKSTP_BOD0
 *  @arg\b          PW_WKSTP_BOD1
 *  @arg\b          PW_WKSTP_BOD2 (Support MG32F02U128/U064/A128/A064)
 *  @arg\b          PW_WKSTP_CMP0
 *  @arg\b          PW_WKSTP_CMP1
 *  @arg\b          PW_WKSTP_CMP2 (Support MG32F02A132/A072)
 *  @arg\b          PW_WKSTP_CMP3 (Support MG32F02A132/A072)
 *  @arg\b          PW_WKSTP_RTC
 *  @arg\b          PW_WKSTP_IWDT
 *  @arg\b          PW_WKSTP_I2C0
 *  @arg\b          PW_WKSTP_I2C1 (Support MG32F02A132/A072U128/U064/A128/A064)
 * @param[in]   NewState:
 *  @arg\b          DISABLE
 *  @arg\b          ENABLE
 * @return
 * @note
 * @par         Example
 * @code
    PW_PeriphSTOPModeWakeUp_Config(PW_WKSTP_I2C0, ENABLE);
    PW_PeriphSTOPModeWakeUp_Config(PW_WKSTP_IWDT, ENABLE);
 * @endcode
 *******************************************************************************
 */
void PW_PeriphSTOPModeWakeUp_Config (PW_WKSTP_Periph_TypeDef WKSTP_Periph, FunctionalState NewState)
{
    uint32_t  REG;
    
    if(WKSTP_Periph < 32)
    {
        REG = 0x00000001 << WKSTP_Periph;
        if(NewState != DISABLE)
        {
            PW->WKSTP0.W |= REG;
        }
        else
        {
            PW->WKSTP0.W &= ~REG;
        }
    }
    else
    {
        REG = 0x00000001 << (WKSTP_Periph & 0x1F);
        if(NewState != DISABLE)
        {
            PW->WKSTP1.W |= REG;
        }
        else
        {
            PW->WKSTP1.W &= ~REG;
        }
    }
}

/**
 *******************************************************************************
 * @brief       MCU wake up delay selection
 * @details  
 * @param[in]   WakeUpDly:
 *  @arg\b          PW_WK_15us.
 *  @arg\b          PW_WK_45us.
 *  @arg\b          PW_WK_75us.
 *  @arg\b          PW_WK_135us.
 * @return
 * @note
 * @par         Example
 * @code
    PW_WakeUpDelay_Select(PW_WK_135us);
 * @endcode
 *******************************************************************************
 */
void PW_WakeUpDelay_Select (PW_WakeUpDly_TypeDef WakeUpDly)
{
    PW->CR0.MBIT.WKSTP_DSEL = WakeUpDly;
}

/**
 *******************************************************************************
 * @brief       MCU wake up delay selection
 * @details  
 * @return      DRV_Return
 *  @arg\b          PW_None
 *  @arg\b          PW_Sleep
 *  @arg\b          PW_Stop
 * @return
 * @note
 * @par         Example
 * @code
    Status = PW_GetWakeUpMode();
 * @endcode
 *******************************************************************************
 */
DRV_Return PW_GetWakeUpMode (void)
{
    DRV_Return bitstatus = PW_None;
    
    if(PW->STA.MBIT.BOD1_S == 0)
    {
        bitstatus = PW_None;
    }
    
    if(PW->STA.MBIT.BOD1_S == 1)
    {
        bitstatus = PW_Sleep;
    }
    
    if(PW->STA.MBIT.BOD1_S == 1)
    {
        bitstatus = PW_Stop;
    }
    return bitstatus;
}

#if defined(PW_CR0_WKSLP_MDS_mask_w)
/**
 *******************************************************************************
 * @brief       Wakeup mode selection from SLEEP mode.
 * @details  
 * @param[in]   WakeUpModeSelect:
 *  @arg\b          PW_Normal_SleepMode
 *  @arg\b          PW_LowPower_SleepMode
 * @return
 * @note
 * @par         Example
 * @code
    PW_WakeUpMode_Select(PW_LowPower_SleepMode);
    
 * @endcode
 *******************************************************************************
 */ 
void PW_WakeUpMode_Select (PW_WakeUpMode_TypeDef WakeUpModeSelect)
{
    PW->CR0.MBIT.WKSLP_MDS = WakeUpModeSelect;
}
#endif
///@}


/**
 * @name    Interrupt
 *
 */ 
///@{  
/**
 *******************************************************************************
 * @brief       Get all intterupt source state.
 * @details    
 * @return      Return PW status register value.
 * @note
 * @par         Example
 * @code
    Status = PW_GetAllFlagStatus();
 * @endcode
 *******************************************************************************
 */
uint32_t PW_GetAllFlagStatus (void)
 {
    return PW->STA.W;
 }
 
/**
 *******************************************************************************
 * @brief       Get one intterupt source state
 * @details  
 * @param[in]   PW_ITSrc:
 *  @arg\b          PW_PORF
 *  @arg\b          PW_BOD0F
 *  @arg\b          PW_BOD1F
 *  @arg\b          PW_BOD2F (Support MG32F02U128/U064/A128/A064)
 *  @arg\b          PW_WKF
 * @return      DRV_Return: Rerutn RST flag status. 
 *  @arg\b          DRV_Happened.
 *  @arg\b          DRV_UnHappened.
 * @note
 * @par         Example
 * @code
    Status = PW_GetSingleFlagStatus(PW_PORF);
 * @endcode
 *******************************************************************************
 */        
DRV_Return PW_GetSingleFlagStatus (uint32_t PW_ITSrc)
{
    DRV_Return bitstatus = DRV_Normal;
    
    if((PW->STA.W & PW_ITSrc) != 0)
    {
        bitstatus = DRV_Happened;
    }
    else
    {
        bitstatus = DRV_Normal;
    }

    return bitstatus;
}

/**
 *******************************************************************************
 * @brief       Clear intterupt source state
 * @details  
 * @param[in]   PW_ITSrc:
 *  @arg\b          PW_PORF
 *  @arg\b          PW_BOD0F
 *  @arg\b          PW_BOD1F
 *  @arg\b          PW_BOD2F (Support MG32F02U128/U064/A128/A064)
 *  @arg\b          PW_WKF
 *  @arg\b          PW_ALLF
 * @return    
 * @note
 * @par         Example
 * @code
    PW_ClearFlag(PW_PORF | PW_BOD0F);
 * @endcode
 *******************************************************************************
 */
void PW_ClearFlag (uint32_t PW_ITSrc)
{
    PW->STA.W = PW_ITSrc;
}
 
/**
 *******************************************************************************
 * @brief       config interrupt source
 * @details  
 * @param[in]   PW_ITSrc:
 *  @arg\b          PW_INT_WK
 *  @arg\b          PW_INT_BOD2 (Support MG32F02U128/U064/A128/A064)
 *  @arg\b          PW_INT_BOD1
 *  @arg\b          PW_INT_BOD0
 * @param[in]   NewState:
 *  @arg\b          DRV_Happened
 *  @arg\b          DRV_Normal
 * @return
 * @note
 * @par         Example
 * @code
    PW_IT_Config((PW_INT_WK | PW_INT_BOD0), ENABLE);
 * @endcode
 *******************************************************************************
 */
void PW_IT_Config (uint32_t PW_ITSrc, FunctionalState NewState)
{
    uint32_t  Reg;
    
    Reg = PW->INT.W;
    
    if(NewState != DISABLE)
    {
        Reg |= PW_ITSrc;
    }
    else
    {
        Reg &= ~PW_ITSrc;
    }
    
    PW->INT.W = Reg;
}

/**
 *******************************************************************************
 * @brief	    Read PW interrupt enable register. 
 * @details     
 * @return      PW interrupt enable register value.
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = PW_GetITStatus();
 * @endcode
 *******************************************************************************
 */
uint32_t PW_GetITStatus (void)
{
    return(PW->INT.W);
}


/**
 *******************************************************************************
 * @brief       Enable/Disable all interrupt 
 * @details  
 * @param[in]   NewState:
 *  @arg\b          ENABLE.
 *  @arg\b          DISABLE.
 * @return
 * @note
 * @par         Example
 * @code
    PW_ITEA_Cmd(ENABLE);
 * @endcode
 *******************************************************************************
 */
void PW_ITEA_Cmd (FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        PW->INT.MBIT.IEA = SET;
    }
    else
    {
        PW->INT.MBIT.IEA = CLR;
    }
}
///@}





