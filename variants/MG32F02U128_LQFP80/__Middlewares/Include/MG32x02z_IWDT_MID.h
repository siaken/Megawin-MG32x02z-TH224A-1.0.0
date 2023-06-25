/**
 ******************************************************************************
 *
 * @file        MG32x02z_IWDT_MID.h
 *
 * @brief       Header file of IWDT MID module.
 * @par         Project
 *              MG32x02z
 * @version     V1.02
 * @date        2021/08/04
 * @author      megawin Software Center
 * @copyright    Copyright (c) 2019 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************
 * @par         Disclaimer 
 *      The Demo software is provided "AS IS"  without any warranty, either 
 *      expressed or implied, including, but not limited to, the implied warranties 
 *      of merchantability and fitness for a particular purpose.  The author will 
 *      not be liable for any special, incidental, consequential or indirect 
 *      damages due to loss of data or any other reason. 
 *      These statements agree with the world wide and local dictated laws about 
 *      authorship and violence against these laws. 
 ******************************************************************************
 ******************************************************************************
 */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MG32x02z_IWDT_MID_H
#define _MG32x02z_IWDT_MID_H

/* Includes ------------------------------------------------------------------*/
#include "MG32x02z_Common_MID.h"
#include "MG32x02z_IWDT.h"
#include "MG32x02z.h"

/** 
  * @brief MG32x02z_MID_Driver
  */

/* Exported types ------------------------------------------------------------*/
/** 
  * @brief IWDT_Exported_Types IWDT Exported Types
  */

/** 
  * @struct IWDT_InitTypeDef
  * @brief	IWDT Init structure definition
  */
///@{
typedef struct
{
  uint32_t Prescaler;           /*!< Select the prescaler of the IWDT.
                                    This parameter can be a value of IWDT_Prescaler */

  uint32_t  Interrupt;          /*!< IWDT  Interrupt Enable Select> */


  uint32_t  Counter;            /*!< IWDT  Count value setting> */

} IWDT_InitTypeDef;
///@}
    
/** 
  * @struct	 IWDT_HandleTypeDef
  * @brief  IWDT Handle Structure definition  
  */
///@{
typedef struct
{
  IWDT_Struct *Instance;       /*!< Register base address    */

  IWDT_InitTypeDef             Init;      	/*!< IWDT required parameters */

}IWDT_HandleTypeDef;
///@}

/* Exported constants --------------------------------------------------------*/

/** 
  * @brief IWDT_Exported_Constants IWDT Exported Constants
  */
///@{
#define IWDT_PRESCALER_1        0x00000000U                   /*!< IWDT prescaler set to 1 */
#define IWDT_PRESCALER_2        0x00000010U                   /*!< IWDT prescaler set to 2 */
#define IWDT_PRESCALER_4        0x00000020U                   /*!< IWDT prescaler set to 4 */
#define IWDT_PRESCALER_8        0x00000030U                   /*!< IWDT prescaler set to 8 */
#define IWDT_PRESCALER_16       0x00000040U                   /*!< IWDT prescaler set to 16 */
#define IWDT_PRESCALER_32       0x00000050U                   /*!< IWDT prescaler set to 32 */
#define IWDT_PRESCALER_64       0x00000060U                   /*!< IWDT prescaler set to 64 */
#define IWDT_PRESCALER_128      0x00000070U                   /*!< IWDT prescaler set to 128 */
#define IWDT_PRESCALER_256      0x00000080U                   /*!< IWDT prescaler set to 256 */
#define IWDT_PRESCALER_512      0x00000090U                   /*!< IWDT prescaler set to 512 */
#define IWDT_PRESCALER_1024     0x000000A0U                   /*!< IWDT prescaler set to 1024 */
#define IWDT_PRESCALER_2048     0x000000B0U                   /*!< IWDT prescaler set to 2048 */
#define IWDT_PRESCALER_4096     0x000000C0U                   /*!< IWDT prescaler set to 4096 */
///@}

/* Exported macros -----------------------------------------------------------*/
/**
  * @brief IWDT_Exported_Macros IWDT Exported Macros
  */
    
/**
  * @name  Enable the IWDT peripheral.
  * @param  "__HANDLE__"  IWDT handle
  * @retval None
  */
///@{
#define __DRV_IWDT_START(__HANDLE__)                ((__HANDLE__)->Instance->CR0.W = IWDT_ENABLE)                /*!< IWDT Function Enable */
///@}
  
/**
  * @brief  Reload IWDT counter with value defined in the reload register
  *         (write access to IWDT_PR, IWDT_RLR & IWDT_WINR registers disabled).
  * @param  "__HANDLE__"  IWDT handle
  * @retval None
  */
///@{
#define __DRV_IWDT_RELOAD_COUNTER(__HANDLE__)       ((__HANDLE__)->Instance->KEY.W = IWDT_KEY_RELOAD)             /*!< IWDT Reload Function */
///@}
  
/**
  * @name IWDT Interrupt Config
  */
///@{
#define	IWDT_IT_EW1	IWDT_INT_EW1_IE_enable_w               /*!< IWDT early wake up 1 interrupt even enable */
#define	IWDT_IT_EW0	IWDT_INT_EW0_IE_enable_w               /*!< IWDT early wake up 0 interrupt even enable */
#define	IWDT_IT_TIE	IWDT_INT_TIE_enable_w                  /*!< IWDT overflow interrupt even enable */
///@}

/**
  * @name IWDT Interrupt Status Config
  */
///@{
#define IWDT_STA_EW1F IWDT_STA_EW1F_mask_w              /*!< IWDT early wake up 1 state bit define */
#define IWDT_STA_EW0F IWDT_STA_EW0F_mask_w              /*!< IWDT early wake up 0 state bit define */
#define IWDT_STA_TIEF IWDT_STA_TF_mask_w                /*!< IWDT overflow state bit define */
#define IWDT_STA_ALLF (IWDT_STA_EW1F_mask_w|IWDT_STA_EW0F_mask_w|IWDT_STA_TF_mask_w)    /*!< IWDT all state define */
///@}   
/* Private constants ---------------------------------------------------------*/
/** 
  * @name IWDT Private Constants
  */
  
/**
  * @name  IWDT Key Register define
  */
///@{
#define IWDT_KEY_RELOAD                 0x00002014U  /*!< IWDT Reload Counter Enable   */
#define IWDT_ENABLE                     0x00000001U  /*!< IWDT Peripheral Enable       */
#define IWDT_KEY_WRITE_ACCESS_ENABLE    0x0000A217U  /*!< IWDT KR Write Access Enable  */
#define IWDT_KEY_WRITE_ACCESS_DISABLE   0x00000000U  /*!< IWDT KR Write Access Disable */
///@}

/* Private macros ------------------------------------------------------------*/

/**
 *******************************************************************************
 * @brief 	IWDT Interrupt Enable.
 * @param  "__HANDLE__"  IWDT Handle.
 * @param  "__INTERRUPT__"  specifies the IWDT interrupt source to check.
 *******************************************************************************
  */
///@{
#define	__DRV_IWDT_INT_ENABLE(__HANDLE__,__INTERRUPT__) ((__HANDLE__)->Instance->INT.W = (__INTERRUPT__))                  /* !< IWDT Interrupt Enable Function */
///@}

/** 
 *******************************************************************************
 * @brief  Check whether the specified IWDT interrupt source is enabled or not.
 * @param  "__HANDLE__"  IWDT Handle.
 * @param  "__INTERRUPT__"  specifies the IWDT interrupt source to check.
 *         This parameter can be one of the following values:
 *         IWDT_IT_EW1: Early Wakeup 1 Interrupt
 *         IWDT_IT_EW0: Early Wakeup 0 Interrupt
 *         IWDT_IT_TIE: Overfloat Interrupt
 * @retval state of __INTERRUPT__ (TRUE or FALSE).
 *******************************************************************************
 */
///@{
#define	__DRV_IWDT_GET_INT_SOURCE(__HANDLE__, __INTERRUPT__) (((__HANDLE__)->Instance->INT.W & (__INTERRUPT__)) == (__INTERRUPT__))
///@}
  
/**
 *******************************************************************************
 * @brief  Check whether the specified IWDT flag is set or not.
 * @param  "__HANDLE__"  IWDT handle
 * @param  "__FLAG__"  specifies the flag to check.
 *         This parameter can be one of the following values:
 *         IWDT_FLAG_EW1F: Early wakeup 1 interrupt flag
 *         IWDT_FLAG_EW0F: Early wakeup 0 interrupt flag
 *         IWDT_FLAG_TIEF: Overfloat interrupt flag
 * @retval The new state of IWDT_FLAG (SET or RESET).
 *******************************************************************************
  */
///@{
#define __DRV_IWDT_GET_FLAG(__HANDLE__, __FLAG__)           (((__HANDLE__)->Instance->STA.W & (__FLAG__)) == (__FLAG__))
///@}
  
/**
 *******************************************************************************
 * @brief  Clear the IWDT's pending flags.
 * @param  "__HANDLE__"  IWDT handle
 * @param  "__FLAG__"  specifies the flag to clear.
 * @note   This parameter can be one of the following values:
 *         IWDT_FLAG_EW1: Early wakeup 1 interrupt flag
 *         IWDT_FLAG_EW0: Early wakeup 0 interrupt flag
 *         IWDT_FLAG_TIE: Overfloat interrupt flag
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_IWDT_CLEAR_FLAG(__HANDLE__, __FLAG__)         ((__HANDLE__)->Instance->STA.W = (__FLAG__))
///@}
  
/**
 *******************************************************************************
 * @brief  Enable write access to IWDT_PR, IWDT_RLR and IWDT_WINR registers.
 * @param  "__HANDLE__"  IWDT handle
 * @retval None
 *******************************************************************************
 */
///@{
#define IWDT_ENABLE_WRITE_ACCESS(__HANDLE__)  ((__HANDLE__)->Instance->KEY.W = IWDT_KEY_WRITE_ACCESS_ENABLE)
///@}

/**
 *******************************************************************************
 * @brief  Disable write access to IWDT_PR, IWDT_RLR and IWDT_WINR registers.
 * @param  "__HANDLE__  IWDT handle
 * @retval None
 *******************************************************************************
 */
///@{
#define IWDT_DISABLE_WRITE_ACCESS(__HANDLE__) ((__HANDLE__)->Instance->KEY.W = IWDT_KEY_WRITE_ACCESS_DISABLE)
///@}
  
/**
 *******************************************************************************
 * @brief  Check IWDT prescaler value.
 * @param  "__PRESCALER__"  IWDT prescaler value
 * @retval None
 *******************************************************************************
 */
///@{
#define IS_IWDT_PRESCALER(__PRESCALER__)      (((__PRESCALER__) == IWDT_PRESCALER_4)  || \
                                               ((__PRESCALER__) == IWDT_PRESCALER_8)  || \
                                               ((__PRESCALER__) == IWDT_PRESCALER_16) || \
                                               ((__PRESCALER__) == IWDT_PRESCALER_32) || \
                                               ((__PRESCALER__) == IWDT_PRESCALER_64) || \
                                               ((__PRESCALER__) == IWDT_PRESCALER_128)|| \
                                               ((__PRESCALER__) == IWDT_PRESCALER_256))
///@}

/**
 * @name    Function announce
 * @brief   IWDT base initial/Deinitial	
 */ 
///@{
MID_StatusTypeDef MID_IWDT_Init(IWDT_HandleTypeDef *mIWDT);

MID_StatusTypeDef MID_IWDT_Refresh(IWDT_HandleTypeDef *mIWDT);
__weak void IWDT_Error_Handler(IWDT_HandleTypeDef *mIWDT);
__weak void MID_IWDT_TIEINTCallback(IWDT_HandleTypeDef* mIWDT);
__weak void MID_IWDT_EW1INTCallback(IWDT_HandleTypeDef* mIWDT);
__weak void MID_IWDT_EW0INTCallback(IWDT_HandleTypeDef* mIWDT);
void MID_IWDT_IRQHandler(IWDT_HandleTypeDef *mIWDT);
///@}  

#endif /* _MG32x02z_MID_IWDT_H */


