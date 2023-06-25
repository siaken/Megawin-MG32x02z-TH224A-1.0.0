
/**
 *******************************************************************************
 *
 * @file        MG32x02z_PW_Init.c
 *
 * @brief       The PW Init C file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.10
 * @date        2018/01/31
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

#include "MG32x02z_PW_Init.h"



/**
 *******************************************************************************
 * @brief  	    initialized PW module.
 * @details  
 * @return	    None	
 * @note
 * @par         Example
 * @code
    PW_Init ();
 * @endcode
 *******************************************************************************
 */
void PW_Init (void)
{
    PW->KEY.MBIT.KEY = 0xA217;          // Unprotest PW module register
    PW->INT.W = CONF_PW_InitConfig[1];
    PW->CR0.W = CONF_PW_InitConfig[3];
    PW->CR1.W = CONF_PW_InitConfig[4];
    PW->WKSTP0.W = CONF_PW_InitConfig[5];
    PW->WKSTP1.W = CONF_PW_InitConfig[6];
    PW->KEY.MBIT.KEY = 0x0000;          // Unprotest PW module register
}


