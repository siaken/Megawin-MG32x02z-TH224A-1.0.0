/**
 *******************************************************************************
 *
 * @file        MG32x02z_RTC_Init.c
 *
 * @brief       The RTC initial code C file
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.03
 * @date        2021/07/30
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2020 Megawin Technology Co., Ltd.
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

#include "MG32x02z_RTC_Init.h"
#include "MG32x02z_PW.h"
#include "MG32x02z_CSC.h"
#include "MG32x02z_SYS.h"
#include "RTE_Components.h"





#if (CONF_RTC_INT_CON&0x00000001) == 0x00000001
    #if !defined(MG32x02z_SYS_IRQ_)
        #warning Enable RTC_IEA but, RTC NVIC non enable.
    #endif
#endif

/**
 *******************************************************************************
 * @brief       initialized RTC module.
 * @details  
 * @param[in]   RTC_Init:
 * 	@arg\b      Use keil wizard define table index..
 * @return      
 * @note
 * @par         Example
 * @code
                RTC_Init();
 * @endcode
 *******************************************************************************
 */
void RTC_Init(void)
{
    // RTC module register unlocked.
    RTC->KEY.MBIT.KEY = 0xA217;
    
    // RTC input clock & divider select.
    RTC->CLK.W = CONF_RTC_CLK_SEL;
    
    // RTC interrupt event enable.
    RTC->INT.W = CONF_RTC_INT_CON;
    
    // Set RTC Control Register Value.
    RTC->CR0.W = (CONF_RTC_CR0_CON&~(RTC_CR0_EN_mask_w));
    // RTC Reload Value Set.
    RTC->RLR.W = CONF_RTC_RLR;
    // RTC Count Value Set.
    RTC->CR0.B[0] &= ~RTC_CR0_RCR_MDS_mask_b0;
    RTC->CR0.B[0] |= RTC_CR0_RCR_MDS_forced_reload_b0;
    RTC->CR1.MBIT.RC_START = 1;
    while(RTC->STA.MBIT.RCRF==0);
    RTC->STA.B[0] |= RTC_STA_RCRF_happened_b0;
    RTC->CR0.B[0] &= ~RTC_CR0_RCR_MDS_mask_b0;
    RTC->CR0.B[0] |= RTC_CR0_RCR_MDS_auto_reload_b0;
    
    
    // Interrupt enable check
    if(CONF_RTC_INT_CON!=DISABLE)
    {
        PW->KEY.MBIT.KEY = 0xA217;
        SYS->INT.MBIT.IEA = 1;                  // Enable System module all interrupt.
        PW->KEY.MBIT.KEY = 0x712A;
    }
    // Wake up enable check
    if((RTC->CR0.W&(RTC_CR0_TF_WPEN_mask_w|RTC_CR0_PC_WPEN_mask_w|RTC_CR0_ALM_WPEN_mask_w))!=DISABLE)
    {
        // CSC module register unlocked.
        CSC->KEY.MBIT.KEY = 0xA217;
        CSC->SLP0.MBIT.SLP_RTC = 1;             // Enable RTC clock at SLEEP mode
        CSC->STP0.MBIT.STP_RTC = 1;             // Enable RTC clock at STOP mode
        // CSC module register locked.
        CSC->KEY.MBIT.KEY = 0x217A;
    }
    // Alarm Enable Check
    if((CONF_RTC_CR0_CON&RTC_CR0_ALM_EN_mask_w)!=DISABLE)
    {
        RTC->ALM.W = CONF_RTC_ALM;           // Alarm value set.
    }
    // RTC Function Enable
    RTC->CR0.MBIT.EN = 1;
    
    // RTC module register locked
    RTC->KEY.MBIT.KEY = 0x217A;
}



