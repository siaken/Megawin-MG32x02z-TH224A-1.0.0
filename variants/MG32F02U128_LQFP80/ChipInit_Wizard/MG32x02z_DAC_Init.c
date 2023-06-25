/**
 *******************************************************************************
 *
 * @file        MG32x02z_DAC_Init.c
 *
 * @brief       The DAC initial code C file 
 *              Apply device : MG32F02A128/U128/A064/U064
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.00
 * @date        2021/07/13
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
#include "MG32x02z_DAC.h"
#include "MG32x02z_DAC_Init.h"

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
 * @brief  	    Initialized DAC module.
 * @param[in]   None
 * @return      None
 *******************************************************************************
 */
void DAC_Init(void)
{
    /* DAC register initial */
    #if ((CONF_DAC_CR0_REG & 0x00000001) != 0)
        DAC->DAT0.W = CONF_DAC_DAT0_REG;
        DAC->CR0.W  = CONF_DAC_CR0_REG;
    #endif
        
}


