/**
 *******************************************************************************
 *
 * @file        MG32x02z_CMP_Init.c
 *
 * @brief       The CMP initial code C file 
 *              Apply device : MG32F02A032
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.00
 * @date        2021/07/12
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


/* Includes ------------------------------------------------------------------*/
#include "MG32x02z.h"
#include "MG32x02z_CMP.h"
#include "MG32x02z_CMP_Init.h"

/* Wizard menu ---------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* External vairables --------------------------------------------------------*/


/**
 *******************************************************************************
 * @brief  	    Initialized Analog Comparator module.
 * @param[in]   None
 * @return      None
 *******************************************************************************
 */
void CMP_ACx_Init(void)
{
    /* CMP Analog comparator : analog control register initial wizard */
    #if ((CONF_CMP_ANA & 0x00000101) != 0)
        CMP->ANA.W = CONF_CMP_ANA;
    #endif
    
    /* CMP0 initial wizard */
    #if ((CONF_CMP_AC0 & 0x00000001) != 0)
        CMP->CR0.W = CONF_CMP_AC0;    
    #endif
    
    /* CMP1 initial wizard */
    #if ((CONF_CMP_AC1 & 0x00000001) != 0)
        CMP->CR1.W = CONF_CMP_AC1;    
    #endif
    
}


