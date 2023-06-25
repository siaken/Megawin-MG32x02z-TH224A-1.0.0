/**
 ******************************************************************************
 *
 * @file        MG32x02z_CM0_DRV.h
 *
 * @brief       This is the C Code Include format example file.
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

#ifndef _MG32x02z_CM0_DRV_H
#define _MG32x02z_CM0_DRV_H
#define _MG32x02z_CM0_DRV_H_VER                            0.01           /*!<MG32x02z Driver ver.*/


#include "MG32x02z__Common_DRV.h"


#ifdef __cplusplus
extern "C" {
#endif


/** 
 * @name    SysTick
 *
 */ 
///@{ 

/** 
 * @enum		CM0_SysTickClkSrcDef
 * @brief		CM0 Selects the SysTick timer clock source. 
 */    
typedef enum{
    Reference = 0,
    CK_ST = 0,
    Processor = 1,
    }CM0_SysTickClkSrcDef;

// Systick
#define __CM0_SysTickIT_Enable()                    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk
#define __CM0_SysTickIT_Disable()                   SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk

#define __CM0_SysTick_Enable()                      SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk
#define __CM0_SysTick_Disable()                     SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk

#define __CM0_SysTickClcokSource_Processor()        SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk
#define __CM0_SysTickClcokSource_Reference()        SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk
#define __CM0_SysTickClcokSource_CK_ST()            SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk

#define __CM0_GetSysTickCurrentValue()              SysTick->VAL

void CM0_SysTick_Cmd(FunctionalState State);
void CM0_SysTickIT_Cmd(FunctionalState State);
void CM0_SysTickClockSource_Select(CM0_SysTickClkSrcDef Select);
uint32_t CM0_GetSysTickCurrentValue(void);

///@}


#ifdef __cplusplus
}
#endif

#endif


