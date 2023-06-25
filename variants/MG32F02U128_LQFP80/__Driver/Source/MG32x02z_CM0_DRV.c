/**
 ******************************************************************************
 *
 * @file        MG32x02z_CM0_DRV.c
 *
 * @brief       This is the C code format driver file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.00
 * @date        2018/05/21
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



#include "MG32x02z_CM0_DRV.h"



/**
 * @name	SysTick
 *          SysTick Setting 
 */ 
///@{

/**
 *******************************************************************************
 * @brief       SysTick Enable / Disable.
 * @details
 *              
 * @param[in]   State
 *  @arg\b      ENABLE
 *  @arg\b      DISABLE
 * @return		None
 * @exception   None
 * @note        
 * @par         Example
 * @code
                CM0_SysTick_Cmd(ENABLE);
                CM0_SysTick_Cmd(DISABLE);
 * @endcode
 * @par         Modify
 *              void CM0_SysTick_Cmd(FunctionalState State)
 *******************************************************************************
 */
void CM0_SysTick_Cmd(FunctionalState State)
{
    if(State == ENABLE)
        SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    else
        SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}



/**
 *******************************************************************************
 * @brief       SysTick Interrupt Enable / Disable.
 * @details
 *              
 * @param[in]   State
 *  @arg\b      ENABLE
 *  @arg\b      DISABLE
 * @return		None
 * @exception   None
 * @note        
 * @par         Example
 * @code
                CM0_SysTick_Cmd(ENABLE);
                CM0_SysTick_Cmd(DISABLE);
 * @endcode
 * @par         Modify
 *              void CM0_SysTick_IT_Cmd(FunctionalState State)
 *******************************************************************************
 */
void CM0_SysTickIT_Cmd(FunctionalState State)
{
    if(State == ENABLE)
        SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
    else
        SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
}



/**
 *******************************************************************************
 * @brief       SysTick Clock Source Select.
 * @details
 *              
 * @param[in]   Select
 *  @arg\b      CK_ST
 *  @arg\b      Processor
 * @return		None
 * @exception   None
 * @note        
 * @par         Example
 * @code
                CM0_SysTick_Cmd(ENABLE);
                CM0_SysTick_Cmd(DISABLE);
 * @endcode
 * @par         Modify
 *              void CM0_SysTickClockSource_Select(FunctionalState State)
 *******************************************************************************
 */
void CM0_SysTickClockSource_Select(CM0_SysTickClkSrcDef Select)
{
    if(Select == Processor)
        SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
    else
        SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;
}



/**
 *******************************************************************************
 * @brief       Get SysTick Current Value.
 * @details
 *              
 * @return		None
 * @exception   None
 * @note        
 * @par         Example
 * @code
                Temp = CM0_GetSysTickCurrentValue();
 * @endcode
 * @par         Modify
 *              uint32_t CM0_GetSysTickCurrentValue(void)
 *******************************************************************************
 */
uint32_t CM0_GetSysTickCurrentValue(void)
{
    return SysTick->VAL;
}



///@}


