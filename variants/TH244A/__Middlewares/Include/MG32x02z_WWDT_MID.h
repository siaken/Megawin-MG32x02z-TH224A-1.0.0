/**
 ******************************************************************************
 *
 * @file        MG32x02z_WWDT_MID.h
 *
 * @brief       Header file of WWDT MID module.
 * @par         Project
 *              MG32x02z
 * @version     V1.01
 * @date        2022/06/24
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
#ifndef _MG32x02z_WWDT_MID_H
#define _MG32x02z_WWDT_MID_H

/* Includes ------------------------------------------------------------------*/
#include "MG32x02z_Common_MID.h"
#include "MG32x02z_WWDT.h"


/* Exported types ------------------------------------------------------------*/

/** 
  * @brief WWDT_Exported_Types WWDT Exported Types
  */
 
/** 
  * @struct WWDT_InitTypeDef
  * @brief  WWDT initial tructure definition
  */
///@{
typedef struct
{
    uint32_t WWDT_WIN;              /*!< Specifies the WWDT window value to be compared to the downcounter.
                                    This parameter must be a number Min_Data = 0x00 and Max_Data = 0xFF */
    
    uint32_t WWDT_WRN;              /*!< Specifies the WWDT window value to be compared to the downcounter.
                                    This parameter must be a number Min_Data = 0x00 and Max_Data = 0xFF */
    
    uint32_t WWDT_RLR;              /*!< Specifies the WWDT window value to be compared to the downcounter.
                                    This parameter must be a number Min_Data = 0x40 and Max_Data = 0x7F */
    
    uint32_t WWDT_INT_SEL;          /*!< Interrupt enable WWDT_INT_WRN , WWDT_INT_IE , WWDT_INT_TIE */
    
    uint32_t WWDT_DIV_SEL;          /*!< WWDT intput divider select DIV1/256. */
    
    
    uint32_t WWDT_PRE_DIV_SEL;      /*!< WWDT intput predivider select (/1/2/4/8) */
    
    
    uint32_t WWDT_CLK_SEL;          /*!< WWDT input clock select (APB , UT) */
    
    
    uint32_t WWDT_RST_SEL;          /*!< WWDT reset enable , WWDT_TF, WWDT_WINF */
    
    
}WWDT_InitTypeDef;
///@}

/** 
  * @struct WWDT_HandleTypeDef
  * @brief  WWDT handle structure definition
  */
///@{
typedef struct
{
  WWDT_Struct                 *Instance;  /*!< Register base address    */

  WWDT_InitTypeDef             Init;      /*!< WWDT required parameters */

}WWDT_HandleTypeDef;
///@}

/* Exported constants --------------------------------------------------------*/

/** 
  * @brief WWDT_Exported_Constants WWDT Exported Constants
  */
///@{

/** 
	*	@name  WWDT Interrupt Config.
  */
///@{
#define	WWDT_IT_WIN WWDT_INT_WIN_IE_enable_w                /*!< WWDT enable window interrupt even */
#define	WWDT_IT_WRN WWDT_INT_WRN_IE_enable_w                /*!< WWDT enable warning interrupt even */
#define	WWDT_IT_TIE WWDT_INT_TIE_enable_w                   /*!< WWDT enable overflow interrupt even */
///@}

/** 
  * @name  WWDT Flag Config.
  */
///@{
#define WWDT_WRNF       WWDT_STA_WRNF_mask_w                /*!< WWDT counter warning flag */
#define WWDT_WINF       WWDT_STA_WINF_mask_w                /*!< WWDT counter refreshing and value over the window compare threshold condition flag  */
#define WWDT_TF         WWDT_STA_TF_mask_w                  /*!< WWDT timer timeout interrupt flag */
#define WWDT_ALLF       (WWDT_WRNF | WWDT_WINF | WWDT_TF)   /*!< WWDT all flag */
///@}

/** 
  * @name  WWDT Clock Config.
  */
///@{
#define WWDT_CLK_APB WWDT_CLK_CK_SEL_ck_apb_w               /*!< WWDT APB Clock Source Select from APB */
#define WWDT_CLK_UT  WWDT_CLK_CK_SEL_ck_ut_w                /*!< WWDT APB Clock Source Select from UT */
///@}

/** 
  * @name WWDT Enable Config
  */
///@{
#define	WWDT_CR0_EN	WWDT_CR0_EN_enable_w                    /*!< WWDT Enable bit  */
///@}

/**
  * @name WWDT Prescaler Config.
  */
///@{
#define WWDT_PRESCALER_1                    0x00000000U       /*!< WWDT counter clock = (PCLK1 /1.../128)/1 */
#define	WWDT_PRESCALER_256                  0x00000100U       /*!< WWDT counter clock = (PCLK1 /1 or /256)1 */
///@}

///@}

/* Private macros ------------------------------------------------------------*/

/**
 ******************************************************************************
 * @brief  WWDT_Private_Macros
 * @param  "__WINDOW__"  WWDT window detect register check
 * @note		Just check the register value ,is not specify function.
 * @retval None
 ******************************************************************************
 */
///@{
#define IS_WWDT_WINDOW(__WINDOW__)          (((__WINDOW__) >= WWDT_INT_W_6) && ((__WINDOW__) <= WWDT_INT_W))							/*!< WWDT Window Detect enable or disable check */
///@}

/**
 ******************************************************************************
 * @brief  WWDT_Private_Macros
 * @param 	"__COUNTER__" WWDT counter value get.
 * @note		Just check the register value ,is not specify function.
 * @retval None
 ******************************************************************************
 */
///@{
#define IS_WWDT_COUNTER(__COUNTER__)        (((__COUNTER__) >= WWDT_CR_T_6) && ((__COUNTER__) <= WWDT_CR_T))							/*!< WWDT Counter value check */
///@}

/**
 ******************************************************************************
 * @brief  WWDT_Private_Macros
 * @param	"__PRESCALER__" WWDT prescaler check.
 * @note		Just check the register value ,is not specify function.
 * @retval None
 ******************************************************************************
 */
///@{
#define IS_WWDT_PRESCALER(__PRESCALER__)    (((__PRESCALER__) == WWDT_PRESCALER_1) || \
                                            ((__PRESCALER__) == WWDT_PRESCALER_256))    /*!< WWDT Prescaler check */
                                            
///@}

/* Exported macros ------------------------------------------------------------*/

 /** 
 * @brief WWDT_Exported_Macros WWDT Exported Macros
 */
///@{

/**
 *******************************************************************************
 * @brief  Enable the WWDT peripheral.
 * @param  "__HANDLE__"  WWDT handle
 * @retval None
 *******************************************************************************
 */
#define __DRV_WWDT_ENABLE(__HANDLE__)                         ((__HANDLE__)->Instance->CR0.W = WWDT_CR0_EN)
  
/**
 *******************************************************************************
 * @brief  Enable the WWDT early wakeup interrupt.
 * @param  "__HANDLE__" WWDT handle
 * @param  "__INTERRUPT__"  specifies the interrupt to enable.
 *         This parameter can be one of the following values:
 * @note   Once enabled this interrupt cannot be disabled except by a system reset.
 * @retval None
 *******************************************************************************
 */
#define __DRV_WWDT_ENABLE_IT(__HANDLE__, __INTERRUPT__)       ((__HANDLE__)->Instance->INT.W = (__INTERRUPT__))
  
/**
 *******************************************************************************
 * @brief  Check whether the selected WWDT interrupt has occurred or not.
 * @param  "__HANDLE__"  WWDT handle
 * @param  "__INTERRUPT__"  specifies the it to check.
 *       	This parameter can be one of the following values:
 * @note 	WWDT_FLAG_EWIF: Early wakeup interrupt IT
 * @retval The new state of WWDT_FLAG (SET or RESET).
 *******************************************************************************
 */
#define __DRV_WWDT_GET_IT(__HANDLE__, __INTERRUPT__)        __DRV_WWDT_GET_FLAG((__HANDLE__),(__INTERRUPT__))
  
/** 
 *******************************************************************************
 * @brief	Clear the WWDT interrupt pending bits.
 *         		bits to clear the selected interrupt pending bits.
 * @param  "__HANDLE__"  WWDT handle
 * @param  "__INTERRUPT__"  specifies the interrupt pending bit to clear.
 *       	This parameter can be one of the following values:
 * @note 	WWDT_FLAG_EWIF: Early wakeup interrupt flag
 *******************************************************************************
  */
#define __DRV_WWDT_CLEAR_IT(__HANDLE__, __INTERRUPT__)      __DRV_WWDT_CLEAR_FLAG((__HANDLE__), (__INTERRUPT__))
  
/**
 *******************************************************************************
 * @brief	Check whether the specified WWDT flag is set or not.
 * @param  "__HANDLE__"  WWDT handle
 * @param  "__FLAG__"  specifies the flag to check.
 *       	This parameter can be one of the following values:
 * @note 	WWDT_FLAG_EWIF: Early wakeup interrupt flag
 * @retval	The new state of WWDT_FLAG (SET or RESET).
 *******************************************************************************
 */
#define __DRV_WWDT_GET_FLAG(__HANDLE__, __FLAG__)           (((__HANDLE__)->Instance->STA.W & (__FLAG__)) == (__FLAG__))
  
/**
 *******************************************************************************
 * @brief	Clear the WWDT's pending flags.
 * @param  "__HANDLE__"  WWDT handle
 * @param  "__FLAG__"  specifies the flag to clear.
 *       	This parameter can be one of the following values:
 * @note 	WWDT_FLAG_EWIF: Early wakeup interrupt flag
 * @retval	None
 *******************************************************************************
 */
#define __DRV_WWDT_CLEAR_FLAG(__HANDLE__, __FLAG__)         ((__HANDLE__)->Instance->STA.W = (__FLAG__))

/** 
 *******************************************************************************
 * @brief	Check whether the specified WWDT interrupt source is enabled or not.
 * @param  "__HANDLE__"  WWDT Handle.
 * @param  "__INTERRUPT__"  specifies the WWDT interrupt source to check.
 *       	This parameter can be one of the following values:
 * @note 	WWDT_IT_EWI: Early Wakeup Interrupt
 * @retval	state of "__INTERRUPT__" (TRUE or FALSE).
 *******************************************************************************
 */
#define __DRV_WWDT_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) (((__HANDLE__)->Instance->INT.W & (__INTERRUPT__)) == (__INTERRUPT__))
///@}

/**
 * @    Function announce
 * @brief   WWDT base initial/Deinitial	
 */ 
///@{
MID_StatusTypeDef MID_WWDT_Init(WWDT_HandleTypeDef *mWWDT);
void MID_WWDT_MspInit(WWDT_HandleTypeDef *mWWDT);

MID_StatusTypeDef MID_WWDT_Refresh(void);
void MID_WWDT_IRQHandler(WWDT_HandleTypeDef *mWWDT);
void MID_WWDT_WRNINTCallback(WWDT_HandleTypeDef* mWWDT);
void MID_WWDT_WININTCallback(WWDT_HandleTypeDef* mWWDT);
void MID_WWDT_TFINTCallback(WWDT_HandleTypeDef* mWWDT);
void WWDT_Error_Handler(WWDT_HandleTypeDef *mWWDT);
///@}   

#endif /* _MG32x02z_MID_WWDT_H */


