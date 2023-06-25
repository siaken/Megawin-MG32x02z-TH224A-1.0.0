/**
 *******************************************************************************
 *
 * @file        MG32x02z_WWDT_DRV.c
 *
 * @brief       This is the C code format driver file for the WWDT module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.12
 * @date        2019/01/03
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2019 Megawin Technology Co., Ltd.
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
 
#include "MG32x02z_WWDT_DRV.h"


/**
 * @name	Clock
 *   		
 */ 
///@{
/**
 *******************************************************************************
 * @brief  	    WWDT input clock CK_WWDT source select. 
 * @details  
 * @param[in]   WWDT_CLKS:
 * 	@arg\b			WWDT_CK_APB.
 * 	@arg\b			WWDT_CK_UT.
 * @return	    	
 * @note
 * @par         Example
 * @code
    WWDT_CLK_Select(WWDT_CK_UT);
 * @endcode
 *******************************************************************************
 */
void WWDT_CLK_Select(WWDT_CLKS_TypeDef WWDT_CLKS)
{
    WWDT->CLK.MBIT.CK_SEL = WWDT_CLKS;
}


/**
 *******************************************************************************
 * @brief  	    WWDT internal clock CK_WWDT_INT input divider select. 
 * @details  
 * @param[in]   WWDT_DIVS:
 * 	@arg\b			WWDT_DIV_1
 * 	@arg\b			WWDT_DIV_2
 * 	@arg\b			WWDT_DIV_4
 * 	@arg\b			WWDT_DIV_8
 * 	@arg\b			WWDT_DIV_16
 * 	@arg\b			WWDT_DIV_32
 * 	@arg\b			WWDT_DIV_64
 * 	@arg\b			WWDT_DIV_128
 * @return	    	
 * @note
 * @par         Example
 * @code
    WWDT_DIV_Select(WWDT_DIV_128);
 * @endcode
 *******************************************************************************
 */
void WWDT_DIV_Select (WWDT_DIVS_TypeDef WWDT_DIVS)
{
    WWDT->CLK.MBIT.CK_DIV = WWDT_DIVS;
}


/**
 *******************************************************************************
 * @brief  	    WWDT internal clock CK_WWDT_INT pre-divider value. 
 * @details  
 * @param[in]   WWDT_PDIVS:
 * 	@arg\b			WWDT_PDIV_1
 * 	@arg\b			WWDT_PDIV_256
 * @return	    	
 * @note
 * @par         Example
 * @code
    WWDT_PDIV_Select(WWDT_PDIV_256);
 * @endcode
 *******************************************************************************
 */
void WWDT_PDIV_Select (WWDT_PDIVS_TypeDef WWDT_PDIVS)
{
    WWDT->CLK.MBIT.CK_PDIV = WWDT_PDIVS;
}

///@}
 

/**
 * @name	Command
 *   		
 */ 
///@{
/**
 *******************************************************************************
 * @brief  	    Enable or disable WWDT modeule. 
 * @details  
 * @param[in]   NewState:
 * 	@arg\b			ENABLE
 * 	@arg\b			DISABLE
 * @return	    	
 * @note
 * @par         Example
 * @code
    WWDT_Cmd(ENABLE);
 * @endcode
 *******************************************************************************
 */
void WWDT_Cmd (FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        WWDT->CR0.MBIT.EN = 1;
    }
    else
    {
        WWDT->CR0.MBIT.EN = 0;
    }
}
///@}


/**
 * @name	Counter, Reload And Threshold
 *   		
 */ 
///@{
/**
 *******************************************************************************
 * @brief  	    Get WWDT counter value. 
 * @details  
 * @return	    WWDT counter value 0x000 ~ 0x3FF 
 * @note
 * @par         Example
 * @code
    CNT = WWDT_GetCounter();
 * @endcode
 *******************************************************************************
 */
uint16_t WWDT_GetCounter (void)
{
    return WWDT->CNT.H[0];
} 


/**
 *******************************************************************************
 * @brief  	    Reload and refresh the counter.
 * @details  
 * @return	    
 * @note
 * @par         Example
 * @code
    WWDT_RefreshCounter();
 * @endcode
 *******************************************************************************
 */
void WWDT_RefreshCounter (void)
{
    WWDT->KEY.H[0] = 0x2014;
}


/**
 *******************************************************************************
 * @brief  	    Get WWDT counter reload register.
 * @details  
 * @return	    WWDT reload register
 * 	@arg\b			0 ~ 1023
 * @note
 * @par         Example
 * @code
    CNT = WWDT_GetReloadReg();
 * @endcode
 *******************************************************************************
 */
uint16_t WWDT_GetReloadReg (void)
{
    return WWDT->RLR.H[0];
}


/**
 *******************************************************************************
 * @brief  	    Set WWDT counter reload register.
 * @details  
 * @param[in]   WWDT_RLR:
 * 	@arg\b			0 ~ 1023
 * @return	    	
 * @note
 * @par         Example
 * @code
    WWDT_SetReloadReg(0x3FF);
 * @endcode
 *******************************************************************************
 */
void WWDT_SetReloadReg (uint16_t WWDT_RLR)
{
    WWDT->RLR.H[0] = WWDT_RLR;
}


/**
 *******************************************************************************
 * @brief  	    Get WWDT window compare threshold register.
 * @details  
 * @return	    WWDT window compare threshold
 * 	@arg\b			0 ~ 1023
 * @note
 * @par         Example
 * @code
    CNT = WWDT_GetWindowThreshold();
 * @endcode
 *******************************************************************************
 */
uint16_t WWDT_GetWindowThreshold (void)
{
    return WWDT->WIN.H[0];
}


/**
 *******************************************************************************
 * @brief  	    Set WWDT window compare threshold register.
 * @details  
 * @param[in]   WWDT_WIN:
 * 	@arg\b			0 ~ 1023
 * @return	    	
 * @note
 * @par         Example
 * @code
    WWDT_SetWindowThreshold(0x1FF);
 * @endcode
 *******************************************************************************
 */
void WWDT_SetWindowThreshold (uint16_t WWDT_WIN)
{
    WWDT->WIN.H[0] = WWDT_WIN;
}


/**
 *******************************************************************************
 * @brief  	    Get WWDT warning interrupt compare threshold register.
 * @details  
 * @return	    WWDT warning interrupt compare threshold
 * 	@arg\b			0 ~ 1023
 * @note
 * @par         Example
 * @code
    CNT = WWDT_GetWarningThreshold();
 * @endcode
 *******************************************************************************
 */
uint16_t WWDT_GetWarningThreshold (void)
{
    return WWDT->WRN.H[0];
}


/**
 *******************************************************************************
 * @brief  	    Set WWDT window compare threshold register.
 * @details  
 * @param[in]   WWDT_WRN:
 * 	@arg\b			0 ~ 1023
 * @return	    	
 * @note
 * @par         Example
 * @code
    WWDT_SetWarningThreshold(0x0FF);
 * @endcode
 *******************************************************************************
 */
void WWDT_SetWarningThreshold (uint16_t WWDT_WRN)
{
    WWDT->WRN.H[0] = WWDT_WRN;
}
///@}


/**
 * @name	Reset Generate
 *   		
 */ 
///@{
/**
 *******************************************************************************
 * @brief  	    WWDT reset event source configure. 
 * @details  
 * @param[in]   WWDT_RSTGS:
 * 	@arg\b			WWDT_RSTW
 * 	@arg\b			WWDT_RSTF
 * @param[in]   NewState:
 * 	@arg\b			ENABLE
 * 	@arg\b			DISABLE
 * @note
 * @par         Example
 * @code
    WWDT_RstEvent_Config((WWDT_RSTW | WWDT_RSTW), ENABLE);
 * @endcode
 *******************************************************************************
 */
void WWDT_RstEvent_Config (uint8_t WWDT_RSTGS, FunctionalState NewState)
{
    uint8_t Reg;
    
    Reg = WWDT->CR0.B[0];
    if(NewState != DISABLE)
    {
        Reg |= WWDT_RSTGS;
    }
    else
    {
        Reg &= ~WWDT_RSTGS;
    }
        
    WWDT->CR0.B[0] = Reg;
}
///@}


/**
 * @name	Interrupt
 *   		
 */
///@{
/**
 *******************************************************************************
 * @brief       Get all intterupt source status.
 * @details    
 * @return	    Return WWDT status register value.
 * @note
 * @par         Example
 * @code
    Status = WWDT_GetAllFlagStatus();
 * @endcode
 *******************************************************************************
 */
uint32_t WWDT_GetAllFlagStatus (void)
{
    return WWDT->STA.W;
}

/**
 *******************************************************************************
 * @brief  	    Get one intterupt source status
 * @details  
 * @param[in]   WWDT_ITSrc:
 * 	@arg\b			WWDT_WRNF.
 * 	@arg\b			WWDT_WINF.
 * 	@arg\b			WWDT_TF.
 * @return	    DRV_Return:
 * 	@arg\b			DRV_Happened.
 * 	@arg\b			DRV_UnHappened.
 * @note
 * @par         Example
 * @code
    Status = WWDT_GetSingleFlagStatus(WWDT_WRNF);
 * @endcode
 *******************************************************************************
 */
DRV_Return WWDT_GetSingleFlagStatus (uint32_t WWDT_ITSrc)
{
    DRV_Return bitstatus = DRV_Normal;
    
    if ((WWDT->STA.W & WWDT_ITSrc) != (uint32_t)DISABLE)
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
 * @param[in]   WWDT_ITSrc:
 * 	@arg\b			WWDT_WRNF.
 * 	@arg\b			WWDT_WINF.
 * 	@arg\b			WWDT_TF.
 * 	@arg\b			WWDT_ALLF.
 * @return	 
 * @note
 * @par         Example
 * @code
    IWDT_ClearFlag(WWDT_WRNF | WWDT_WINF);
 * @endcode
 *******************************************************************************
 */
void WWDT_ClearFlag (uint32_t WWDT_ITSrc)
{
    WWDT->STA.W = WWDT_ITSrc;
}

/**
 *******************************************************************************
 * @brief  	    config interrupt source
 * @details  
 * @param[in]   WWDT_ITSrc:
 * 	@arg\b			WWDT_INT_WRN.
 * 	@arg\b			WWDT_INT_WIN.
 * 	@arg\b			WWDT_INT_TF.
 * @param[in]   NewState:
 * 	@arg\b			ENABLE.
 * 	@arg\b			DISABLE.
 * @return	    	
 * @note
 * @par         Example
 * @code
    WWDT_IT_Config((WWDT_INT_WRN | WWDT_INT_WIN), ENABLE);
 * @endcode
 *******************************************************************************
 */
void WWDT_IT_Config (uint32_t WWDT_ITSrc, FunctionalState NewState)
{
    uint32_t  Reg;
    
    Reg = WWDT->INT.W;
    
    if(NewState != DISABLE)
    {
        Reg |= WWDT_ITSrc;
    }
    else
    {
        Reg &= ~WWDT_ITSrc;
    }
    WWDT->INT.W = Reg;
}
///@}

