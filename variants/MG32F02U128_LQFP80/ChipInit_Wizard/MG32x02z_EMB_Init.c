/**
 ******************************************************************************
 *
 * @file        MG32x02z_EMB_Init.c
 *
 * @brief       MG32x02z EMB Initial C Code File
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.00
 * @date        2016/04/11
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2016 MegaWin Technology Co., Ltd.
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
 */

/* Includes -----------------------------------------------------------------*/
#include "MG32x02z_EMB_Init.h"


/* Private typedef ----------------------------------------------------------*/

/* Private define -----------------------------------------------------------*/

/* Private macro ------------------------------------------------------------*/

/* Private variables --------------------------------------------------------*/

/* Private function prototypes ----------------------------------------------*/

/* Private functions --------------------------------------------------------*/
void EMB_Initial(void)
{
    EMB->CR0.B[0] &= ~EMB_CR0_EN_mask_b0;
    EMB->INT.W = EMB_Config_INT;
    EMB->CLK.W = EMB_Config_CLK;
    EMB->CR0.W = EMB_Config_CR0 | ((uint32_t)0x00000100);
    EMB->CR1.W = EMB_Config_CR1;
    EMB->CR2.W = EMB_Config_CR2;

#if(EMB_Mode_Select == EMB_Mode_NOAddress)
#endif

#if(EMB_Mode_Select == EMB_Mode_NoLatch_16BitAddress)
            EMB->CR0.W |= EMB_CR0_BUS_MDS_separated_w;
#endif

#if(EMB_Mode_Select == EMB_Mode_1AddressPhase_30BitAddress)
            EMB->CR0.W |= EMB_CR0_BUS_MDS_multiplex_w | 
                          EMB_CR0_ADR_SEL_30bit_w;
#endif

#if(EMB_Mode_Select == EMB_Mode_1AddressPhase_24BitAddress)
            EMB->CR0.W |= EMB_CR0_BUS_MDS_multiplex_w |
                          EMB_CR0_ADR_SEL_24bit_w;
#endif

#if(EMB_Mode_Select == EMB_Mode_2AddressPhase_30BitAddress)
            EMB->CR0.W |= EMB_CR0_BUS_MDS_multiplex_w | 
                          EMB_CR0_ADR_SEL_30bit_w |
                          EMB_CR0_ADR_TWO_mask_w;
#endif

#if(EMB_Mode_Select == EMB_Mode_2AddressPhase_24BitAddress)
            EMB->CR0.W |= EMB_CR0_BUS_MDS_multiplex_w |
                          EMB_CR0_ADR_SEL_30bit_w |
                          EMB_CR0_ADR_TWO_mask_w;
#endif

    EMB->CR0.B[0] |= EMB_CR0_EN_mask_b0;
}


/******************* (C) COPYRIGHT 2018 Megawin ************ END OF FILE *****/ 


