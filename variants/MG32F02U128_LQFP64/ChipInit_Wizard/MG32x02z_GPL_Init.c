
/**
 ******************************************************************************
 *
 * @file        MG32x02z_GPL_Init.c
 * @brief       The GPL Init C file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.00
 * @date        2017/07/07
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
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
#include "MG32x02z_GPL_Init.h"


void GPL_Init(void)
{
    // GPL CRC Disable
    GPL->CR1.B[0] &= ~GPL_CR1_CRC_EN_mask_b0;

    // GPL Config
    GPL->CR0.W = GPL_Config0_CR0;
    GPL->CRCINIT.W = GPL_Config0_CRCINIT;
    GPL->CR1.W = GPL_Config0_CR1;
}


