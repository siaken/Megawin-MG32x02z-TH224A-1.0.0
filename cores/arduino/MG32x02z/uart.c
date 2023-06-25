/**
 ******************************************************************************
 *
 ******************************************************************************
 * @file    uaet.c
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
/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup 
  * @{
  */

/** @addtogroup 
  * @{
  */
#include "MG32x02z.h"
#include "system_MG32x02z.h"
#include "uart.h"
#include "MG32x02z_URT.h"


#ifdef __cplusplus
 extern "C" {
#endif

/**
  * @}
  */

/** @addtogroup 
  * @{
  */

/// @brief number of received characters


/**
  * @}
  */

/** @addtogroup MG32x02z_System_Private_TypesDefinitions
  * @{
  */

/// @brief defines the global attributes of the UART


/**
  * @}
  */

/** @addtogroup MG32x02z_System_Private_Macros
  * @{
  */

/**
  * @}
  */





/** @addtogroup MG32x02z_System_Private_Variables
  * @{ URT4x_IRQn URT0
  */
/// @brief uart caracteristics


//@brief just a simple buffer for the uart reception


/**
  * @}
  */

/** @addtogroup MG32x02z_System_Private_FunctionPrototypes
  * @{
  */


/**
  * @}
  */

/** @addtogroup 
  * @{
  */





extern URT_HandleTypeDef        mURT0;
extern URT_HandleTypeDef        mURT1;
extern URT_HandleTypeDef        mURT2;
#if defined(URT3)
extern URT_HandleTypeDef        mURT3;
#endif
extern URT_HandleTypeDef        mURT4;
extern URT_HandleTypeDef        mURT5;
extern URT_HandleTypeDef        mURT6;
extern URT_HandleTypeDef        mURT7;


void megawin_Uart_init(void)
{
    // mURT0 URT0;
    mURT0.Instance            =  URT0;
    mURT0.Init.BaudRate       =  115200;                            
    mURT0.Init.WordLength     =  UART_WORDLENGTH_8B;
    mURT0.Init.HWFlowCtrl     =  URT_HWCONTROL_NONE;
    mURT0.Init.Mode           =  URT_TX_RX;
    mURT0.Init.OneBitSampling =  URT_ONEBIT_SAMPLE_THREE;
    mURT0.Init.Parity         =  URT_PARITY_NO;
    mURT0.Init.StopBits       =  URT_STOPBIT_1_0;
    
    mURT0.AdvancedInit.AdvFeatureInit     = URT_ADVFEATURE_NO_INIT;


    // mURT1 URT1;
    mURT1.Instance            =  URT1;
    mURT1.Init.BaudRate       =  115200;                            
    mURT1.Init.WordLength     =  UART_WORDLENGTH_8B;
    mURT1.Init.HWFlowCtrl     =  URT_HWCONTROL_NONE;
    mURT1.Init.Mode           =  URT_TX_RX;
    mURT1.Init.OneBitSampling =  URT_ONEBIT_SAMPLE_THREE;
    mURT1.Init.Parity         =  URT_PARITY_NO;
    mURT1.Init.StopBits       =  URT_STOPBIT_1_0;
    
    mURT1.AdvancedInit.AdvFeatureInit     = URT_ADVFEATURE_NO_INIT;


    // mURT2 URT2;
    mURT2.Instance            =  URT2;
    mURT2.Init.BaudRate       =  115200;                            
    mURT2.Init.WordLength     =  UART_WORDLENGTH_8B;
    mURT2.Init.HWFlowCtrl     =  URT_HWCONTROL_NONE;
    mURT2.Init.Mode           =  URT_TX_RX;
    mURT2.Init.OneBitSampling =  URT_ONEBIT_SAMPLE_THREE;
    mURT2.Init.Parity         =  URT_PARITY_NO;
    mURT2.Init.StopBits       =  URT_STOPBIT_1_0;
    
    mURT2.AdvancedInit.AdvFeatureInit     = URT_ADVFEATURE_NO_INIT;

#if defined(URT3)
    // mURT3 URT3;
    mURT3.Instance            =  URT3;
    mURT3.Init.BaudRate       =  115200;                            
    mURT3.Init.WordLength     =  UART_WORDLENGTH_8B;
    mURT3.Init.HWFlowCtrl     =  URT_HWCONTROL_NONE;
    mURT3.Init.Mode           =  URT_TX_RX;
    mURT3.Init.OneBitSampling =  URT_ONEBIT_SAMPLE_THREE;
    mURT3.Init.Parity         =  URT_PARITY_NO;
    mURT3.Init.StopBits       =  URT_STOPBIT_1_0;
    
    mURT3.AdvancedInit.AdvFeatureInit     = URT_ADVFEATURE_NO_INIT;
#endif

    // mURT4 URT4;
    mURT4.Instance            =  URT4;
    mURT4.Init.BaudRate       =  115200;                            
    mURT4.Init.WordLength     =  UART_WORDLENGTH_8B;
    mURT4.Init.HWFlowCtrl     =  URT_HWCONTROL_NONE;
    mURT4.Init.Mode           =  URT_TX_RX;
    mURT4.Init.OneBitSampling =  URT_ONEBIT_SAMPLE_THREE;
    mURT4.Init.Parity         =  URT_PARITY_NO;
    mURT4.Init.StopBits       =  URT_STOPBIT_1_0;
    
    mURT4.AdvancedInit.AdvFeatureInit     = URT_ADVFEATURE_NO_INIT;


    // mURT5 URT5;
    mURT5.Instance            =  URT5;
    mURT5.Init.BaudRate       =  115200;                            
    mURT5.Init.WordLength     =  UART_WORDLENGTH_8B;
    mURT5.Init.HWFlowCtrl     =  URT_HWCONTROL_NONE;
    mURT5.Init.Mode           =  URT_TX_RX;
    mURT5.Init.OneBitSampling =  URT_ONEBIT_SAMPLE_THREE;
    mURT5.Init.Parity         =  URT_PARITY_NO;
    mURT5.Init.StopBits       =  URT_STOPBIT_1_0;
    
    mURT5.AdvancedInit.AdvFeatureInit     = URT_ADVFEATURE_NO_INIT;


    // mURT6 URT6;
    mURT6.Instance            =  URT6;
    mURT6.Init.BaudRate       =  115200;                            
    mURT6.Init.WordLength     =  UART_WORDLENGTH_8B;
    mURT6.Init.HWFlowCtrl     =  URT_HWCONTROL_NONE;
    mURT6.Init.Mode           =  URT_TX_RX;
    mURT6.Init.OneBitSampling =  URT_ONEBIT_SAMPLE_THREE;
    mURT6.Init.Parity         =  URT_PARITY_NO;
    mURT6.Init.StopBits       =  URT_STOPBIT_1_0;
    
    mURT6.AdvancedInit.AdvFeatureInit     = URT_ADVFEATURE_NO_INIT;


    // mURT7 URT7;
    mURT7.Instance            =  URT7;
    mURT7.Init.BaudRate       =  115200;                            
    mURT7.Init.WordLength     =  UART_WORDLENGTH_8B;
    mURT7.Init.HWFlowCtrl     =  URT_HWCONTROL_NONE;
    mURT7.Init.Mode           =  URT_TX_RX;
    mURT7.Init.OneBitSampling =  URT_ONEBIT_SAMPLE_THREE;
    mURT7.Init.Parity         =  URT_PARITY_NO;
    mURT7.Init.StopBits       =  URT_STOPBIT_1_0;
    
    mURT7.AdvancedInit.AdvFeatureInit     = URT_ADVFEATURE_NO_INIT;

//    MID_URT_Init( &MURT_RX_IT);
//    NVIC_EnableIRQ( URT0_IRQn);
}



/**
  * @}
  */

/**
  * @}
  */



/**
  * @}
  */
#ifdef __cplusplus
}
#endif






/*********COPYRIGHT(c) 2022 megawin Technology Co., Ltd *****END OF FILE****/
