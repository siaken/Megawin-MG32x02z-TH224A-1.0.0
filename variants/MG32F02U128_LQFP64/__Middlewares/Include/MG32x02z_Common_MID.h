 /**
 ******************************************************************************
 *
 * @file        MG32x02z_Common_MID.h
 * @brief       Header file of Common Configuration module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.00
 * @date        2019/10/22
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2019 megawin Technology Co., Ltd.</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of megawin Technology Co., Ltd. nor the names of its
 *      contributors may be used to endorse or promote products derived from this
 *      software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SMID_L THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MG32x02z_Common_MID_H
#define _MG32x02z_Common_MID_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "MG32x02z.h"
#include "MG32x02z_SYS.h"
#include "MG32x02z_CONF_MID.h"
#include "MG32x02z_cortex_MID.h"

/* Exported types ------------------------------------------------------------*/

/** 
  * @enum   MID_StatusTypeDef
  * @brief  MID Status structures definition  
  */  
typedef enum __attribute__((packed))
{
    MID_SUCCESS  = 0x00,    /*!< Success    */
    MID_FAILURE  = 0x01,    /*!< Failure    */
    MID_OK       = 0x00,    /*!< OK         */
    MID_ERROR    = 0x01,    /*!< Error      */
    MID_BUSY     = 0x02,    /*!< Busy       */
    MID_TIMEOUT  = 0x03,    /*!< Timout     */
}MID_StatusTypeDef;



/** 
  * @enum   MID_LockTypeDef
  * @brief  MID Lock structures definition  
  */
typedef enum __attribute__((packed))
{
    MID_UnLocked = 0x00,
    MID_UNLOCKED = 0x00,
    MID_Locked   = 0x01,
    MID_LOCKED   = 0x01,
}MID_LockTypeDef;




#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))  /*!< MID Status param Check */


/** 
  * @enum   ErrorStatus
  * @brief  MID Lock structures definition  
  */
typedef enum
{
    ERROR = 0,
    SUCCESS = !ERROR
}   ErrorStatus;


/** 
  * @enum   MID_ProtectTypeDef
  * @brief  MID Lock structures definition  
  */
typedef enum
{
    RSTmodule    = (uint32_t)0x4C00000C,
    CSCmodule    = (uint32_t)0x4C01000C,  
    PWmodule     = (uint32_t)0x4C02000C,
    MEMmodule    = (uint32_t)0x4D00000C,  
    MEM2module   = (uint32_t)0x4D00000E,
    CFGmodule    = (uint32_t)0x4FF0000C,
    IWDTmodule   = (uint32_t)0x5D00000C,  
    WWDTmodule   = (uint32_t)0x5D01000C,  
    RTCmodule    = (uint32_t)0x5D04000C,
}MID_ProtectTypeDef;          /*!< Definitions for protection function */



/* Exported constants -------------------------------------------------------*/



/* Exported macro ------------------------------------------------------------*/

#define MID_MAX_DELAY               0xFFFFFFFFU      /*!< Max Delay Time */

#define MID_IS_BIT_SET(REG, BIT)    (((REG) & (BIT)) == (BIT))
#define MID_IS_BIT_CLR(REG, BIT)    (((REG) & (BIT)) == 0U)

#define __MID_LINKDMA(__HANDLE__, __PPP_DMA_FIELD__, __DMA_HANDLE__)               \
                        do{                                                      \
                              (__HANDLE__)->__PPP_DMA_FIELD__ = &(__DMA_HANDLE__); \
                              (__DMA_HANDLE__).Parent = (__HANDLE__);             \
                          } while(0)

#define assert_param(expr) ((void)0U)               /*!< assert_param Not Check */
        
#define UNUSED(x) ((void)(x))                       /*!< UNUSED Function */

/** @brief Reset the Handle's State field.
  * @param "__HANDLE__" specifies the Peripheral Handle.
  * @note  This macro can be used for the following purpose:
  *          - When the Handle is declared as local variable; before passing it as parameter
  *            to HAL_PPP_Init() for the first time, it is mandatory to use this macro
  *            to set to 0 the Handle's "State" field.
  *            Otherwise, "State" field may have any random value and the first time the function
  *            HAL_PPP_Init() is called, the low level hardware initialization will be missed
  *            (i.e. HAL_PPP_MspInit() will not be executed).
  *          - When there is a need to reconfigure the low level hardware: instead of calling
  *            HAL_PPP_DeInit() then HAL_PPP_Init(), user can make a call to this macro then HAL_PPP_Init().
  *            In this later function, when the Handle's "State" field is set to 0, it will execute the function
  *            HAL_PPP_MspInit() which will reconfigure the low level hardware.
  * @retval None
  */
#define __MID_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = 0)

#if (USE_RTOS == 1)
  #error " USE_RTOS should be 0 in the current MID release "
#else
    #define __MID_LOCK(__HANDLE__)                                             \
                                    do{                                        \
                                        if((__HANDLE__)->Lock == MID_Locked)   \
                                        {                                      \
                                           return MID_BUSY;                    \
                                        }                                      \
                                        else                                   \
                                        {                                      \
                                           (__HANDLE__)->Lock = MID_Locked;    \
                                        }                                      \
                                      }while (0)  /*!< Module Lcok */


    #define __MID_UNLOCK(__HANDLE__)                                            \
                                      do{                                       \
                                          (__HANDLE__)->Lock = MID_UnLocked;    \
                                        }while (0)  /*!< Module UnLcok */
#endif /* USE_RTOS */

#define __MID_UnProtectModule(__MODULE__)   ((__MODULE__)->Instance->KEY.H[0] = 0xA217U)        /*!< Module Register UnProtect */
#define __MID_ProtectModule(__MODULE__)    ((__MODULE__)->Instance->KEY.H[0] = 0U)              /*!< Module Register Protect */

/* Exported functions -------------------------------------------------------*/

/** @name MID_Exported_Functions
  * @{
  */

/** @name MID_Exported_Functions_Group1
  * @{
  */
/* Initialization and de-initialization functions  ******************************/
MID_StatusTypeDef MID_Init(void);
MID_StatusTypeDef MID_DeInit(void);
void MID_MspInit(void);
void MID_MspDeInit(void);
MID_StatusTypeDef MID_InitTick(uint32_t TickPriority);
/**
  * @}
  */

/** @name MID_Exported_Functions_Group2
  * @{
  */

/* Peripheral Control functions  ************************************************/
void MID_IncTick(void);
void MID_ClearTick(void);
void MID_Delay(__IO uint32_t Delay);
uint32_t MID_GetTick(void);
void MID_SuspendTick(void);
void MID_ResumeTick(void);
MID_StatusTypeDef MID_ProtectModuleReg(MID_ProtectTypeDef Module);
MID_StatusTypeDef MID_UnProtectModuleReg(MID_ProtectTypeDef Module);
/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __MG32x02z_MID_COMMON */



/************** (C) COPYRIGHT megawin Technology Co., Ltd. *****END OF FILE****/


