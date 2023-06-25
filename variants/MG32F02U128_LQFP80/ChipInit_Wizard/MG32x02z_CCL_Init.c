/**
 *******************************************************************************
 *
 * @file        MG32x02z_CCL_Init.c
 *
 * @brief       The APX CCL initial code C file 
 *              Apply device : MG32F02A128/U128/A064/U064
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
#include "MG32x02z_APX.h"
#include "MG32x02z_CCL_Init.h"

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
 * @brief  	    Initialized APX CCL module.
 * @param[in]   None
 * @return      None
 *******************************************************************************
 */
void APX_CCL_Init(void)
{

    /* CCL0 initial wizard */
    #if ((CONF_APX_CCL00 & 0x00000001) != 0)
        APX->CCL01.W = CONF_APX_CCL01;          
        APX->CCL00.W = CONF_APX_CCL00 & (~APX_CCL00_CCL0_EN_enable_w);          
        APX->CCL00.W |= (APX_CCL00_CCL0_EN_enable_w);          
    #endif
    
    /* CCL1 initial wizard */
    #if ((CONF_APX_CCL10 & 0x00000001) != 0)
        APX->CCL11.W = CONF_APX_CCL11;          
        APX->CCL10.W = CONF_APX_CCL00 & (~APX_CCL00_CCL0_EN_enable_w);     
        APX->CCL10.W |= (APX_CCL00_CCL0_EN_enable_w);     
    #endif   

}


