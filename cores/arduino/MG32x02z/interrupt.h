/**
 ******************************************************************************
 *
 ******************************************************************************
 * @file    interrupt.H
 * @author  cuij
 * @version V1.0.0
 * @date    11-11-2022
 * @brief   The  code is that use adapted to Arduino interface
 *
 * @par         Project
 *              MG32x02z
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 * 
 ******************************************************************************* 
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2022 megawin Technology Co., Ltd.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __INTERRUPT_H
#define __INTERRUPT_H

/* Includes ------------------------------------------------------------------*/
#include "MG32x02z.h"
#include "system_MG32x02z.h"
#include "MG32x02z_CSC_Init.h"
#include "MG32x02z_GPIO_MID.h"
#include "MG32x02z_EXIC_MID.h"
#include "MG32x02z_EXIC_DRV.h"
//#include "hw_config.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
// void MID_EXIC_AFCallback( EXIC_HandleTypeDef* MEXIC_PX);
// void MID_EXIC_OFCallback( EXIC_HandleTypeDef* MEXIC_PX );


void megawin_ExicInterruptSet(  uint16_t  AdrIdx,  void (*callback)(void),    uint32_t mode );

void megawin_ExicInterruptEnablePort( GPIO_Struct *port );
void megawin_ExicInterruptDisable( uint16_t  AdrIdx );

void Megawin_EXIC_Init(void);



#ifdef __cplusplus
}
#endif










#ifdef __cplusplus
 extern "C" {
#endif



#ifdef __cplusplus
}
#endif





#endif /* __INTERRUPT_H */

/*********COPYRIGHT(c) 2022 megawin Technology Co., Ltd *****END OF FILE****/


