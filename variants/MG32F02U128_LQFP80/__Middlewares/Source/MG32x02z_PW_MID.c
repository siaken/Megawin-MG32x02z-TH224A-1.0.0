/**
 *******************************************************************************
 *
 * @file        MG32x02z_PW_MID.c
 *
 * @brief       This is the C code format middleware file for PW module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.03
 * @date        2022/06/22
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
#include "MG32x02z_PW_MID.h" 


/**
 *******************************************************************************
 * @brief       De-Initialize PW perioheral.
 * @details  
 * @return      None
 * @note
 * @par         Example
 * @code
    MID_PW_DeInit();
 * @endcode
 *******************************************************************************
 */
void MID_PW_DeInit (void)
{
    PW->KEY.MBIT.KEY = 0xA217;
    PW->STA.W = 0x000000FC;
    PW->INT.W = 0x00000000;
    PW->CR0.W = 0x00000090;
    PW->CR1.W = 0x00000000;
    PW->WKSTP0.W = 0x00000000;
    PW->WKSTP1.W = 0x00000000;
    PW->KEY.MBIT.KEY = 0;
}
  

/**
 *******************************************************************************
 * @brief       Enters SLEEP mode.
 * @details  
 * @param[in]   SLEEPEntry
 *  @arg\b          PW_SLEEPENTRY_WFI
 *  @arg\b          PW_SLEEPENTRY_WFE
 * @return      None
 * @note
 * @par         Example
 * @code
    MID_PW_EnterSLEEPMode(PW_SLEEPENTRY_WFI);
 * @endcode
 *******************************************************************************
 */
void MID_PW_EnterSLEEPMode (uint8_t SLEEPEntry)
{
    // Check the parameters
    assert_param(IS_PW_SLEEP_ENTRY(SLEEPEntry));
    
    // Clear SLEEPDEEP bit of Cortex System Control Register
    SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);

    // Select SLEEP mode entry
    if(SLEEPEntry == PW_SLEEPENTRY_WFI)
    {
        // Request Wait For Interrupt
        __WFI();
    }
    else
    {
        // Request Wait For Event
        __SEV();
        __WFE();
        __WFE();
    }
}


/**
 *******************************************************************************
 * @brief       Enters STOP mode. 
 * @details  
 * @param[in]   STOPEntry
 *  @arg\b          PW_STOPENTRY_WFI
 *  @arg\b          PW_STOPENTRY_WFE
 * @return      None
 * @note
 * @par         Example
 * @code
    MID_PW_EnterSTOPMode(PW_STOPENTRY_WFI);
 * @endcode
 *******************************************************************************
 */
void MID_PW_EnterSTOPMode (uint8_t STOPEntry)
{
    // Check the parameters
    assert_param(IS_PW_STOP_ENTRY(STOPEntry));

    // Set SLEEPDEEP bit of Cortex System Control Register
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    // Select STOP mode entry
    if(STOPEntry == PW_STOPENTRY_WFI)
    {
        // Request Wait For Interrupt
        __WFI();
    }
    else
    {
        // Request Wait For Event
        __SEV();
        __WFE();
        __WFE();
    }

    // Reset SLEEPDEEP bit of Cortex System Control Register
    SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
}


/**
 *******************************************************************************
 * @brief       Indicates Sleep-On-Exit when returning from Handler mode to 
 *              Thread mode. 
 * @details  
 * @return      None
 * @note
 * @par         Example
 * @code
    MID_PW_EnableSleepOnExit();
 * @endcode
 *******************************************************************************
 */
void MID_PW_EnableSleepOnExit (void)
{
    // Set SLEEPONEXIT bit of Cortex System Control Register
    SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPONEXIT_Msk));
}


/**
 *******************************************************************************
 * @brief       Disables Sleep-On-Exit feature when returning from Handler mode 
 *              to Thread mode.
 * @details  
 * @return      None
 * @note
 * @par         Example
 * @code
    MID_PW_DisableSleepOnExit();
 * @endcode
 *******************************************************************************
 */
void MID_PW_DisableSleepOnExit (void)
{
    // Clear SLEEPONEXIT bit of Cortex System Control Register
    CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPONEXIT_Msk));
}


/**
 *******************************************************************************
 * @brief       Configure BOD1
 * @details  
 * @param[in]   sConfigBOD1
 *  @arg\b          BODx_TRIGGER:
 *          \n          PW_BODx_TRG_RESERVED
 *          \n          PW_BODx_TRG_RISING
 *          \n          PW_BODx_TRG_FALLING
 *          \n          PW_BODx_TRG_DUAL
*  @arg\b           BODx_THRESHOLD:
 *          \n          PW_BOD1_TH_2V0
 *          \n          PW_BOD1_TH_2V4
 *          \n          PW_BOD1_TH_3V7
 *          \n          PW_BOD1_TH_4V2
 * @return      None
 * @note
 * @par         Example
 * @code
    PW_BODxTypeDef  BOD1;
    
    BOD1.BODx_THRESHOLD = PW_BOD1_TH_3V7;
    BOD1.BODx_TRIGGER = PW_BODx_TRG_FALLING;
    MID_PW_ConfigBOD1 (&BOD1_CFG);
 * @endcode
 *******************************************************************************
 */
void MID_PW_ConfigBOD1 (PW_BODxTypeDef *sConfigBOD1)
{
    uint32_t REG;

    REG = (PW->CR0.W & ~(PW_BOD1_TH_MASK | PW_BOD1_TRG_MASK));
    REG |= ((uint32_t) (sConfigBOD1->BODx_THRESHOLD << 10) | 
            (uint32_t) (sConfigBOD1->BODx_TRIGGER << 8));
    PW->CR0.W = REG;
}


#if defined(PW_WKSTP0_WKSTP_BOD2_mask_w)
/**
 *******************************************************************************
 * @brief       Configure BOD2
 * @details  
 * @param[in]   sConfigBOD2
 *  @arg\b          BODx_TRIGGER:
 *          \n          BODx_Reserved
 *          \n          BODx_RisingEdge
 *          \n          BODx_FallingEdge
 *          \n          BODx_DualEdge
 *  @arg\b          BODx_THRESHOLD:
 *          \n          None
 * @return      None
 * @note
 * @par         Example
 * @code
    PW_BODxTypeDef  BOD2;

    BOD2.BODx_TRIGGER = PW_BODx_TRG_FALLING;
    MID_PW_ConfigBOD2 (&BOD2_CFG);
 * @endcode
 *******************************************************************************
 */
void MID_PW_ConfigBOD2 (PW_BODxTypeDef *sConfigBOD2)
{
    uint32_t REG;
    
    REG = (PW->CR0.W & ~(PW_BOD2_TRG_MASK));
    REG |= (uint32_t) (sConfigBOD2->BODx_TRIGGER << 14);
    PW->CR0.W = REG;
}
#endif


/**
 *******************************************************************************
 * @brief       This function handles the BOD0/1/2/WK interrupt request.
 * @details  
 * @return      None
 * @note
 * @par         Example
 * @code
    MID_PW_BODxIRQHandler();
 * @endcode
 *******************************************************************************
 */
void MID_PW_IRQHandler (void)
{
    uint32_t itsource = PW->INT.W;
    uint32_t itflag   = PW->STA.W;
    uint32_t itieflag   = (itsource & itflag);
    
    
    
    /* When BOD0 happened  ----------------------------------------------------*/
    if((itieflag & PW_FLAG_BOD0F) != CLR)
    {
        // Clear BOD0F flag
        __DRV_PW_CLEAR_FLAG(PW_FLAG_BOD0F);
        MID_PW_BOD0Callback();
        return;
    }
    
    /* When BOD1 happened  ----------------------------------------------------*/
    if((itieflag & PW_FLAG_BOD1F) != CLR)
    {
        // Clear BOD1F flag
        __DRV_PW_CLEAR_FLAG(PW_FLAG_BOD1F);
        MID_PW_BOD1Callback();
        return;
    }
 
#if defined(MG32_3RD) || defined(MG32_4TH)
    /* When BOD2 happened  ----------------------------------------------------*/
    if((itieflag & PW_FLAG_BOD2F) != CLR)
    {
        // Clear BOD2F flag
        __DRV_PW_CLEAR_FLAG(PW_FLAG_BOD2F);
        MID_PW_BOD2Callback();
        return;
    }
#endif
    
    /* When WK happened  ------------------------------------------------------*/
    if((itieflag & PW_FLAG_WKF) != CLR)
    {
        // Clear WEF flag
        __DRV_PW_CLEAR_FLAG(PW_FLAG_WKF);
        MID_PW_WKCallback();
        return;
    }
}


/**
 *******************************************************************************
 * @brief       Middle power BOD0 call back
 * @details  
 * @return      None
 * @note
 * @par         Example
 * @code
    MID_PW_BOD0Callback();
 * @endcode
 *******************************************************************************
 */
__weak void MID_PW_BOD0Callback (void)
{
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_PW_BOD0Callback could be implemented in the user file
    */
}


/**
 *******************************************************************************
 * @brief       Middle power BOD1 call back
 * @details  
 * @return      None
 * @note
 * @par         Example
 * @code
    MID_PW_BOD1Callback();
 * @endcode
 *******************************************************************************
 */
__weak void MID_PW_BOD1Callback (void)
{
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_PW_BOD1Callback could be implemented in the user file
    */
}


#if defined(PW_WKSTP0_WKSTP_BOD2_mask_w)
/**
 *******************************************************************************
 * @brief       Middle power BOD2 call back
 * @details  
 * @return      None
 * @note
 * @par         Example
 * @code
    MID_PW_BOD2Callback();
 * @endcode
 *******************************************************************************
 */
__weak void MID_PW_BOD2Callback (void)
{
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_PW_BOD2Callback could be implemented in the user file
    */
}
#endif
   

/**
 *******************************************************************************
 * @brief       Middle power wakeup call back
 * @details  
 * @return      None
 * @note
 * @par         Example
 * @code
    MID_PW_WKCallback();
 * @endcode
 *******************************************************************************
 */
__weak void MID_PW_WKCallback (void)
{
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_PW_WKCallback could be implemented in the user file
    */
}



