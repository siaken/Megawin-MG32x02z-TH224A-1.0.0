/**
 *******************************************************************************
 *
 * @file        MG32x02z_IWDT_DRV.c
 *
 * @brief       This is the C code format driver file for the IWDT module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.11
 * @date        2018/01/31
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2018 Megawin Technology Co., Ltd.
 *              All rights reserved.
 *
 *******************************************************************************
 * @par Disclaimer 
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
 
#include "MG32x02z_IWDT_DRV.h"


/**
 * @name	Clock Divider
 *   		
 */ 
///@{
/**
 *******************************************************************************
 * @brief  	    Select IWDT internal clock CK_IWDT_INT input divider. 
 * @details  
 * @param[in]   IWDT_DIVS:
 * 	@arg\b			IWDT_DIV_1.
 * 	@arg\b			IWDT_DIV_2.
 * 	@arg\b			IWDT_DIV_4.
 * 	@arg\b			IWDT_DIV_8.
 * 	@arg\b			IWDT_DIV_16.
 * 	@arg\b			IWDT_DIV_32.
 * 	@arg\b			IWDT_DIV_64.
 * 	@arg\b			IWDT_DIV_128.
 * 	@arg\b			IWDT_DIV_256.
 * 	@arg\b			IWDT_DIV_512.
 * 	@arg\b			IWDT_DIV_1024.
 * 	@arg\b			IWDT_DIV_2048.
 * 	@arg\b			IWDT_DIV_4096.
 * @return	    	
 * @note
 * @par         Example
 * @code
    IWDT_Divider_Select(IWDT_DIV_4096);
 * @endcode
 *******************************************************************************
 */
void IWDT_Divider_Select (IWDT_DIVS_TypeDef IWDT_DIVS)
{
    IWDT->CLK.MBIT.CK_DIV = IWDT_DIVS;
}
///@}


/**
 * @name	Counter
 *   		
 */
///@{
/**
 *******************************************************************************
 * @brief  	    Get IWDT counter value.
 * @details  
 * @return	    	
 * @note
 * @par         Example
 * @code
    CNT = IWDT_GetCounter();
 * @endcode
 *******************************************************************************
 */
uint8_t IWDT_GetCounter (void)
{
    return IWDT->CNT.B[0];
}

/**
 *******************************************************************************
 * @brief  	    Reload and refresh the counter.
 * @details  
 * @return	    	
 * @note
 * @par         Example
 * @code
    IWDT_RefreshCounter();
 * @endcode
 *******************************************************************************
 */
void IWDT_RefreshCounter (void)
{
    IWDT->KEY.H[0] = 0x2014;
}
///@}


/**
 * @name	Wake Up
 *   		
 */
///@{
/**
 *******************************************************************************
 * @brief  	    Configure IWDT detect IWDT XXXX flag wakeup from STOP mode.
 * @details  
 * @param[in]   IWDT_WK:
 * 	@arg\b			IWDT_EW1_WPEN.
 * 	@arg\b			IWDT_EW0_WPEN.
 * 	@arg\b			IWDT_TF_WPEN.
 * @param[in]   NewState:
 * 	@arg\b			ENABLE.
 * 	@arg\b			DISABLE.
 * @return	    	
 * @note
 * @par         Example
 * @code
    IWDT_StopModeWakeUpEvent_Config((IWDT_EW1_WPEN | IWDT_EW0_WPEN), ENABLE);
 * @endcode
 *******************************************************************************
 */
void IWDT_StopModeWakeUpEvent_Config (uint32_t IWDT_WK, FunctionalState NewState)
{
    uint32_t Reg;
    
    Reg = IWDT->CR0.W;
    if(NewState != DISABLE)
    {
        Reg |= IWDT_WK;
    }
    else
    {
        Reg &= ~IWDT_WK;
    }
    
    IWDT->CR0.W = Reg;
}
///@}


/**
 * @name	Command
 *   		
 */
///@{
/**
 *******************************************************************************
 * @brief  	    Enable or disable IWDT modeule.
 * @details  
 * @param[in]   NewState:
 * 	@arg\b			ENABLE.
 * 	@arg\b			DISABLE.
 * @return	    	
 * @note
 * @par         Example
 * @code
    IWDT_Cmd(ENABLE);
 * @endcode
 *******************************************************************************
 */
void IWDT_Cmd (FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        IWDT->CR0.MBIT.EN = 1;
    }
    else
    {
        IWDT->CR0.MBIT.EN = 0;
    }
}
///@}


/**
 * @name    Interrupt
 *   		
 */
///@{
/**
 *******************************************************************************
 * @brief       Get all intterupt source status.
 * @details    
 * @return	    Return CSC status register value.
 * @note
 * @par         Example
 * @code
    Status = IWDT_GetAllFlagStatus();
 * @endcode
 *******************************************************************************
 */
uint32_t IWDT_GetAllFlagStatus (void)
{
    return IWDT->STA.W;
}

/**
 *******************************************************************************
 * @brief  	    Get one intterupt source status
 * @details  
 * @param[in]   IWDT_ITSrc:
 * 	@arg\b			IWDT_EW1F.
 * 	@arg\b			IWDT_EW0F.
 * 	@arg\b			IWDT_TF.
 * @return	    DRV_Return:
 * 	@arg\b			DRV_Happened.
 * 	@arg\b			DRV_UnHappened.
 * @note
 * @par         Example
 * @code
    Status = IWDT_GetSingleFlagStatus(IWDT_EW1F);
 * @endcode
 *******************************************************************************
 */
DRV_Return IWDT_GetSingleFlagStatus (uint32_t IWDT_ITSrc)
{
    DRV_Return bitstatus = DRV_Normal;
    
    if ((IWDT->STA.W & IWDT_ITSrc) != (uint32_t)DISABLE)
    {
        bitstatus = DRV_Happened;
    }
    else
    {
        bitstatus = DRV_Normal;
    }
    return  bitstatus;
}	

/**
 *******************************************************************************
 * @brief  	    Clear intterupt source state
 * @details  
 * @param[in]   IWDT_ITSrc:
 * 	@arg\b			IWDT_EW1F.
 * 	@arg\b			IWDT_EW0F.
 * 	@arg\b			IWDT_TF.
 * @return	 
 * @note
 * @par         Example
 * @code
    IWDT_ClearFlag(IWDT_EW1F | IWDT_EW0F);
 * @endcode
 *******************************************************************************
 */
void IWDT_ClearFlag (uint32_t IWDT_ITSrc)
{
    IWDT->STA.W = IWDT_ITSrc;
}

/**
 *******************************************************************************
 * @brief  	    config interrupt source
 * @details  
 * @param[in]   IWDT_ITSrc:
 * 	@arg\b			IWDT_INT_EW1.
 * 	@arg\b			IWDT_INT_EW0.
 * 	@arg\b			IWDT_INT_TF.
 * @param[in]   NewState:
 * 	@arg\b			ENABLE.
 * 	@arg\b			DISABLE.
 * @return	    	
 * @note
 * @par         Example
 * @code
    IWDT_IT_Config((IWDT_INT_EW1 | IWDT_INT_EW0), ENABLE);
 * @endcode
 *******************************************************************************
 */
void IWDT_IT_Config (uint32_t IWDT_ITSrc, FunctionalState NewState)
{
    uint32_t  Reg;
    
    Reg = IWDT->INT.W;
    
    if(NewState != DISABLE)
    {
        Reg |= IWDT_ITSrc;
    }
    else
    {
        Reg &= ~IWDT_ITSrc;
    }
    IWDT->INT.W = Reg;
}
///@}

 

