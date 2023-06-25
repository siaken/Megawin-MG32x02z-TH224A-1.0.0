 /**
 ******************************************************************************
 * @file        MG32x02z_MEM_MID.h
 * @brief       Header file of Flash MID module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.01
 * @date        2021/04/21
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2016 Megawin</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Megawin nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SMIDL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
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
#ifndef _MG32x02z_MEM_MID_H
#define _MG32x02z_MEM_MID_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MG32x02z_Common_MID.h"
#include "MG32x02z_CSC_MID.h"
#include "MG32x02z_MEM.h"
#include "MG32x02z_RST.h"



/** @name  MG32x02z_MID_Driver
  * @{
  */

/** @defgroup  MEM MEM MID module driver
  * @{
  */
  
/** @defgroup  MEM_Private_Constants MEM Private Constants
  * @{
  */
#define MEM_TIMEOUT_VALUE      (50000U)         /*!< 50 s */
/**
  * @}
  */

/** @defgroup  MEM_Private_Macros MEM Private Macros
  * @{
  */

#if defined(MG32F02A132)
    #define IS_MEM_PROGRAM_ADDRESS(ADDRESS) (((ADDRESS) >= 0x18000000) && ((ADDRESS) < 0x18021000) || \
                                             ((ADDRESS) >= 0x1A000000) && ((ADDRESS) < 0x1A021000) || \
                                             ((ADDRESS) >= 0x1FF00000) && ((ADDRESS) < 0x1FF00400))

    #define IS_MEM_PROGRAM_ISP_ADDRESS(ADDRESS) ((ADDRESS) >= 0x1C000000) && ((ADDRESS) < 0x1C021000)

#elif defined(MG32F02A072) || defined(MA862)
    #define IS_MEM_PROGRAM_ADDRESS(ADDRESS) (((ADDRESS) >= 0x18000000) && ((ADDRESS) < 0x18012000) || \
                                             ((ADDRESS) >= 0x1A000000) && ((ADDRESS) < 0x1A012000) || \
                                             ((ADDRESS) >= 0x1FF00000) && ((ADDRESS) < 0x1FF00400))

    #define IS_MEM_PROGRAM_ISP_ADDRESS(ADDRESS) ((ADDRESS) >= 0x1C000000) && ((ADDRESS) < 0x1C012000)

#elif defined(MG32F02A032)
    #define IS_MEM_PROGRAM_ADDRESS(ADDRESS) (((ADDRESS) >= 0x18000000) && ((ADDRESS) < 0x18008000) || \
                                             ((ADDRESS) >= 0x1A000000) && ((ADDRESS) < 0x1A008000) || \
                                             ((ADDRESS) >= 0x1FF00000) && ((ADDRESS) < 0x1FF00400))

    #define IS_MEM_PROGRAM_ISP_ADDRESS(ADDRESS) ((ADDRESS) >= 0x1C000000) && ((ADDRESS) < 0x1C008000)

#elif defined(MG32F02A128) || defined(MG32F02U128)
    #define IS_MEM_PROGRAM_ADDRESS(ADDRESS) (((ADDRESS) >= 0x18000000) && ((ADDRESS) < 0x18020000) || \
                                             ((ADDRESS) >= 0x1A000000) && ((ADDRESS) < 0x1A020000) || \
                                             ((ADDRESS) >= 0x1FF00000) && ((ADDRESS) < 0x1FF00200))

    #define IS_MEM_PROGRAM_ISP_ADDRESS(ADDRESS) ((ADDRESS) >= 0x1C000000) && ((ADDRESS) < 0x1C020000)

#elif defined(MG32F02A064) || defined(MG32F02U064)
    #define IS_MEM_PROGRAM_ADDRESS(ADDRESS) (((ADDRESS) >= 0x18000000) && ((ADDRESS) < 0x18010000) || \
                                             ((ADDRESS) >= 0x1A000000) && ((ADDRESS) < 0x1A010000) || \
                                             ((ADDRESS) >= 0x1FF00000) && ((ADDRESS) < 0x1FF00200))

    #define IS_MEM_PROGRAM_ISP_ADDRESS(ADDRESS) ((ADDRESS) >= 0x1C000000) && ((ADDRESS) < 0x1C010000)
                                             
#elif defined(MG32F02U031)
    #define IS_MEM_PROGRAM_ADDRESS(ADDRESS) (((ADDRESS) >= 0x18000000) && ((ADDRESS) < 0x18008000) || \
                                             ((ADDRESS) >= 0x1A000000) && ((ADDRESS) < 0x1A008000) || \
                                             ((ADDRESS) >= 0x1FF00000) && ((ADDRESS) < 0x1FF00200))

    #define IS_MEM_PROGRAM_ISP_ADDRESS(ADDRESS) ((ADDRESS) >= 0x1C000000) && ((ADDRESS) < 0x1C008000)
#endif

/**
  * @}
  */  

/* Exported types ------------------------------------------------------------*/ 
/** @defgroup  MEM_Exported_Types MEM Exported Types
  * @{
  */  

/**
  * @brief  MEM Flash Procedure structure definition
  */
typedef enum 
{
    MEM_FLASH_PROC_NONE              = 0U, 
    MEM_FLASH_PROC_PAGEERASE         = 1U,
    MEM_FLASH_PROC_PROGRAM           = 2U,
} MEM_ProcedureTypeDef;

/** 
  * @brief  MEM_FLASH handle Structure definition
  */
typedef struct __attribute__((packed))
{
    MID_LockTypeDef             Lock;                 /*!< MEM locking object */

    __IO uint32_t               ErrorCode;            /*!< MEM error code, This parameter can be a value of MEM_Error_Codes  */
} MEM_ProcessTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup  MEM_Exported_Constants MEM Exported Constants.
  * @{
  */


/** @defgroup  MEM_Flash_Page_Size MEM Flash Page Size
  * @{
  */
#if defined(MG32_1ST) || defined(MG32_2ND)
  #define MEM_FLASH_PAGE_SIZE 0x000003FFUL                 /*!< MEM Flash Page Size */
#elif defined(MG32_3RD) || defined(MG32_4TH)
  #define MEM_FLASH_PAGE_SIZE 0x000001FFUL                 /*!< MEM Flash Page Size */
#endif


/**
  * @}
  */


/** @defgroup  MEM_Error_Codes MEM Error Codes.
  * @{
  */
#define MEM_ERROR_NONE             0x00U                   /*!< No error */
#define MEM_ERROR_IA               0x01U                   /*!< MEM Flash Illegal Address error */
#define MEM_ERROR_WR               0x02U                   /*!< MEM Flash Programming error */
#define MEM_ERROR_PROTECT          0x04U                   /*!< MEM Flash Write protection error */
#define MEM_ERROR_IHRCO            0x08U                   /*!< MEM Flash Clock Source error */
#define MEM_ERROR_IAP_SIZE         0x10U                   /*!< MEM Flash IAP Size error */
#define MEM_ERROR_READ             0x20U                   /*!< MEM Flash Read error */


/**
  * @}
  */


/** @defgroup  MEM_ACCRSS MEM ACCESS Enable or Disable.
  * @{
  */
#define MEM_ACCESS_AP_WRITE         MEM_CR1_AP_WEN_mask_w   /*!< MEM Flash AP Write */
#define MEM_ACCESS_IAP_EXECUTE      MEM_CR1_IAP_EXEC_mask_w /*!< MEM Flash IAP EXECUTE */
#define MEM_ACCESS_IAP_WRITE        MEM_CR1_IAP_WEN_mask_w  /*!< MEM Flash IAP Write */
#define MEM_ACCESS_ISPD_READ        MEM_CR1_ISPD_REN_mask_w /*!< MEM Flash ISPD Read */
#define MEM_ACCESS_ISPD_WRITE       MEM_CR1_ISPD_WEN_mask_w /*!< MEM Flash ISPD Write */

/**
  * @}
  */


/** @defgroup  MEM_WRITE_MODE MEM Write Mode.
  * @{
  */
#define MEM_WRITE_MODE_NONE         MEM_CR0_MDS_no_b0       /*!< MEM Write Flash Mode None */
#define MEM_WRITE_MODE_STANBY       MEM_CR0_MDS_no_b0       /*!< MEM Write Flash Mode STANBY */
#define MEM_WRITE_MODE_PAGEERASE    MEM_CR0_MDS_erase_b0    /*!< MEM Write Flash Mode PAGEERASE */
#define MEM_WRITE_MODE_PROGRAM      MEM_CR0_MDS_write_b0    /*!< MEM Write Flash Mode PROGRAM */


/**
  * @}
  */


/** @defgroup  MEM_BOOT_FROM MEM_BOOT_FROM Who.
  * @{
  */
#define MEM_BOOT_FROM_AP      MEM_CR0_BOOT_MS_application_flash_w   /*!< MEM_BOOT_FROM_AP */
#define MEM_BOOT_FROM_SRAM    MEM_CR0_BOOT_MS_embedded_sram_w       /*!< MEM_BOOT_FROM_SRAM */
#define MEM_BOOT_FROM_ISP     MEM_CR0_BOOT_MS_boot_flash_w          /*!< MEM_BOOT_FROM_ISP */
#define MEM_BOOT_MASK         MEM_CR0_BOOT_MS_mask_w                /*!< MEM_BOOT_MASK */


/**
  * @}
  */


/** @defgroup  MEM_FLASH_WAIT_STATE MEM FLASH WAIT STATE
  * @{
  */
#define MEM_FLASH_WAIT_STATE_0     0x00U                   /*!< MEM Flash Zero Latency cycle */
#define MEM_FLASH_WAIT_STATE_1     MEM_CR0_FWAIT_one_b1    /*!< MEM Flash One Latency cycle */

#define IS_MEM_FLASH_WAIT_STATE(__WAIT_STATE__) (((__WAIT_STATE__) == MEM_FLASH_WAIT_STATE_0) || \
                                                 ((__WAIT_STATE__) == MEM_FLASH_WAIT_STATE_1)) /*!< MEM_FLASH_WAIT_STATE */

/**
  * @}
  */


/** @defgroup  MEM_Flag_definition MEM Flag definition
  * @{
  */
#define MEM_FLAG_BUSY               MEM_STA_FBUSYF_mask_w   /*!< MEM Flash Busy flag */ 
#define MEM_FLAG_IAE                MEM_STA_IAEF_mask_w     /*!< MEM Flash Illegal Address error flag */
#define MEM_FLAG_WRE                MEM_STA_WPEF_mask_w     /*!< MEM Flash Programming error flag */
#define MEM_FLAG_REE                MEM_STA_RPEF_mask_w     /*!< MEM Flash Programming error flag */
#define MEM_FLAG_EOP                MEM_STA_EOPF_mask_w     /*!< MEM Flash End of Operation flag */
#define MEM_FLAG_IAPSE              MEM_STA_IAPSEF_mask_w   /*!< MEM Flash IAP Size error Flag */


/**
  * @}
  */


/** @defgroup  MEM_FLASH_Interrupt_definition MEM Interrupt definition
  * @{
  */
#define MEM_IT_MASK                 MEM_INT_IEA_mask_w      /*!< MEM Controller All Interrupt source    */
#define MEM_IT_REE                  MEM_INT_RPE_IE_mask_w   /*!< Over Read Error Interrupt source       */
#define MEM_IT_WRE                  MEM_INT_WPE_IE_mask_w   /*!< Programming Error Interrupt source     */
#define MEM_IT_IAE                  MEM_INT_IAE_IE_mask_w   /*!< Illegal Address Error Interrupt source */
#define MEM_IT_EOP                  MEM_INT_EOP_IE_mask_w   /*!< End of MEM Flash Operation Interrupt source */


/**
  * @}
  */


/**
  * @}
  */
  
/* Exported macro ------------------------------------------------------------*/

/** @defgroup  MEM_Exported_Macros MEM Exported Macros
 *  @brief macros to control MEM features
 *  @{
 */
 

/** @defgroup  MEM_REG_PROTECT MEM Regster Access Protect
 *  @brief macros to handle MEM Regster Access Protect
 * @{
 */

/**
  * @brief  Set the MEM Regster Access UnProtect
  * @retval None
  */
#define __MID_MEM_UNPROTECT()     (MEM->KEY.H[0] = 0xA217U)     /*!< MEM Flash Write UnProtect with AP / IAP / ISPD */
#define __MID_MEM_UNPROTECT2()    (MEM->KEY.H[1] = 0xA217U)     /*!< MEM Flash Write UnProtect with ISP */
#define __DRV_MEM_UNPROTECT()     (MEM->KEY.H[0] = 0xA217U)     /*!< MEM Flash Write UnProtect with AP / IAP / ISPD */
#define __DRV_MEM_UNPROTECT2()    (MEM->KEY.H[1] = 0xA217U)     /*!< MEM Flash Write UnProtect with ISP */


/**
 * @brief  Set the MEM Regster Access Protect
 * @retval None
 */ 
#define __MID_MEM_PROTECT()     (MEM->KEY.H[0] = 0U)    /*!< MEM Flash Write Protect with AP / IAP / ISPD */
#define __MID_MEM_PROTECT2()    (MEM->KEY.H[1] = 0U)    /*!< MEM Flash Write Protect with ISP */
#define __DRV_MEM_PROTECT()     (MEM->KEY.H[0] = 0U)    /*!< MEM Flash Write Protect with AP / IAP / ISPD */
#define __DRV_MEM_PROTECT2()    (MEM->KEY.H[1] = 0U)    /*!< MEM Flash Write Protect with ISP */


/**
 * @brief  Get the MEM Protect State
 * @retval MEM Protect State
 *         The value of this SET or RESET, SET is Protect.
 */ 
#define __MID_MEM_GET_PROTECT_STATE()    (MEM->KEY.H[0])    /*!< MEM Flash Protect State */
#define __DRV_MEM_GET_PROTECT_STATE()    (MEM->KEY.H[0])    /*!< MEM Flash Protect State */

/**
 * @}
 */



/** @defgroup  MEM_REG_PROTECT MEM Regster Access Protect
 *  @brief macros to handle MEM Regster Access Protect
 * @{
 */     
#define __MID_MEM_ENABLE()     (MEM->CR0.B[0] = MEM_CR0_EN_mask_b0)     /*!< MEM Flash Write Enable */
#define __MID_MEM_DISABLE()    (MEM->CR0.B[0] &= ~MEM_CR0_EN_mask_b0)   /*!< MEM Flash Write Disable */
#define __DRV_MEM_ENABLE()     (MEM->CR0.B[0] = MEM_CR0_EN_mask_b0)     /*!< MEM Flash Write Enable */
#define __DRV_MEM_DISABLE()    (MEM->CR0.B[0] &= ~MEM_CR0_EN_mask_b0)   /*!< MEM Flash Write Disable */

/**
 * @}
 */


/** @defgroup  MEM_ACCESS MEM Access Type
 *  @brief macros to handle MEM Access Type.
 * @{
 */
#define __MID_MEM_ACCESS_ENABLE(__MEM_ACCESS__)    (MEM->CR1.W |= (__MEM_ACCESS__))     /*!< MEM Flash Access Enable */
#define __MID_MEM_ACCESS_DISABLE(__MEM_ACCESS__)    (MEM->CR1.W &= ~(__MEM_ACCESS__))   /*!< MEM Flash Access Disable */
#define __MID_MEM_GET_ACCESS_STATE()    (MEM->CR1.W)                                    /*!< MEM Flash Access State */
#define __DRV_MEM_ACCESS_ENABLE(__MEM_ACCESS__)    (MEM->CR1.W |= (__MEM_ACCESS__))     /*!< MEM Flash Access Enable */
#define __DRV_MEM_ACCESS_DISABLE(__MEM_ACCESS__)    (MEM->CR1.W &= ~(__MEM_ACCESS__))   /*!< MEM Flash Access Disable */
#define __DRV_MEM_GET_ACCESS_STATE()    (MEM->CR1.W)                                    /*!< MEM Flash Access State */


/**
 * @}
 */


/** @defgroup  MEM_WRITE_MODE_SEL MEM Write Mode Select
 *  @brief macros to handle MEM Write Mode
 * @{
 */

/**
 *****************************************************************************
 * @brief  Config the specified MEM Flash Write Mode.
 * @param  "__MEM_WRITE_MODE__"  MEM Write Mode
 *         This parameter can be one of the following values:
 *     @arg @ref MEM_WRITE_MODE_STANBY      ALL Interrupt
 *     @arg @ref MEM_WRITE_MODE_PROGRAM     End of MEM Flash Operation Interrupt
 *     @arg @ref MEM_WRITE_MODE_PAGEERASE   Illegal Address Error Interrupt
 * @retval none
 *****************************************************************************
 */
#define __MID_MEM_SET_WRITE_MODE(__MEM_WRITE_MODE__)    (MEM->CR0.B[0] = ((MEM->CR0.B[0] & ~MEM_CR0_MDS_mask_b0) | (__MEM_WRITE_MODE__)))

/**
 *****************************************************************************
 * @brief  Config the specified MEM Flash Write Mode.
 * @param  "__MEM_WRITE_MODE__"  MEM Write Mode
 *         This parameter can be one of the following values:
 *     @arg @ref MEM_WRITE_MODE_STANBY      ALL Interrupt
 *     @arg @ref MEM_WRITE_MODE_PROGRAM     End of MEM Flash Operation Interrupt
 *     @arg @ref MEM_WRITE_MODE_PAGEERASE   Illegal Address Error Interrupt
 * @retval none
 *****************************************************************************
 */
#define __DRV_MEM_SET_WRITE_MODE(__MEM_WRITE_MODE__)    (MEM->CR0.B[0] = ((MEM->CR0.B[0] & ~MEM_CR0_MDS_mask_b0) | (__MEM_WRITE_MODE__)))

/**
 * @}
 */


/**
 *****************************************************************************
 * @brief  MEM Flash Write Sequence Key Single / Multiple
 * @retval none
 *****************************************************************************
 */
#define __MID_MEM_GET_SEQUEMTIAL_KEY_STATE()      (MEM->SKEY.B[0])                              /*!< MEM Flash Write Sequemtial State */
#define __MID_MEM_SET_SINGLE_WRITE_SEQUENCE()      MEM->SKEY.B[0] = 0x46; MEM->SKEY.B[0] = 0xB9 /*!< MEM Flash Single Write Sequence */
#define __MID_MEM_SET_MULTIPLE_WRITE_SEQUENCE()    MEM->SKEY.B[0] = 0x46; MEM->SKEY.B[0] = 0xBE /*!< MEM Flash Multiple Write Sequence */
#define __MID_MEM_SET_MULTIPLE_WRITE_PROTECT()    (MEM->SKEY.B[0] = 0)                          /*!< MEM Flash Multiple Write End */
#define __DRV_MEM_GET_SEQUEMTIAL_KEY_STATE()      (MEM->SKEY.B[0])                              /*!< MEM Flash Write Sequemtial State  */
#define __DRV_MEM_SET_SINGLE_WRITE_SEQUENCE()      MEM->SKEY.B[0] = 0x46; MEM->SKEY.B[0] = 0xB9 /*!< MEM Flash Single Write Sequence */
#define __DRV_MEM_SET_MULTIPLE_WRITE_SEQUENCE()    MEM->SKEY.B[0] = 0x46; MEM->SKEY.B[0] = 0xBE /*!< MEM Flash Multiple Write Sequence */
#define __DRV_MEM_SET_MULTIPLE_WRITE_PROTECT()    (MEM->SKEY.B[0] = 0)                          /*!< MEM Flash Multiple Write End */


/** @defgroup  MEM_FLASH_WAIT_STATE_SET MEM Flash Wait State Set
 *  @brief macros to handle MEM Flash Wait State
 * @{
 */

/**
 *****************************************************************************
 * @brief  Set the MEM Flash Wait State.
 * @param  "__WAIT_STATE__" MEM Flash Wait State
 *         The value of this parameter depend on device used within the same series
 * @retval None
 *****************************************************************************
 */
#define __MID_MEM_SET_FLASH_WAIT_STATE(__WAIT_STATE__)    (MEM->CR0.B[1] = (MEM->CR0.B[1] & (~MEM_CR0_FWAIT_mask_b1)) | (__WAIT_STATE__))

/**
 *****************************************************************************
 * @brief  Set the MEM Flash Wait State.
 * @param  "__WAIT_STATE__" MEM Flash Wait State
 *         The value of this parameter depend on device used within the same series
 * @retval None
 *****************************************************************************
 */
#define __DRV_MEM_SET_FLASH_WAIT_STATE(__WAIT_STATE__)    (MEM->CR0.B[1] = (MEM->CR0.B[1] & (~MEM_CR0_FWAIT_mask_b1)) | (__WAIT_STATE__))


/**
 *****************************************************************************
 * @brief  Get the MEM Flash Wait State.
 * @retval MEM Flash Wait State
 *         The value of this parameter depend on device used within the same series
 *****************************************************************************
 */ 
#define __MID_MEM_GET_FLASH_WAIT_STATE()    (MEM->CR0.B[1] & (~MEM_CR0_FWAIT_mask_b1))


/**
 *****************************************************************************
 * @brief  Get the MEM Flash Wait State.
 * @retval MEM Flash Wait State
 *         The value of this parameter depend on device used within the same series
 *****************************************************************************
 */ 
#define __DRV_MEM_GET_FLASH_WAIT_STATE()    (MEM->CR0.B[1] & (~MEM_CR0_FWAIT_mask_b1))


/**
 * @}
 */

/** @defgroup  MEM_Interrupt MEM Interrupts
 *  @brief macros to handle MEM interrupts
 * @{
 */ 

/**
 *****************************************************************************
 * @brief  Enable the specified MEM interrupt.
 * @param  "__INTERRUPT__"  MEM interrupt
 *         This parameter can be any combination of the following values:
 *     @arg      MEM_IT         ALL Interrupt
 *     @arg      MEM_IT_EOP     End of MEM Flash Operation Interrupt
 *     @arg      MEM_IT_IAE     Illegal Address Error Interrupt
 *     @arg      MEM_IT_WRE     Write Error Interrupt
 *     @arg      MEM_IT_REE     Read Error Interrupt
 * @retval none
 *****************************************************************************
 */  
#define __MID_MEM_ENABLE_IT(__INTERRUPT__)    (MEM->INT.B[0] |= (__INTERRUPT__))

/**
 *****************************************************************************
 * @brief  Enable the specified MEM interrupt.
 * @param  "__INTERRUPT__"  MEM interrupt
 *         This parameter can be any combination of the following values:
 *     @arg      MEM_IT         ALL Interrupt
 *     @arg      MEM_IT_EOP     End of MEM Flash Operation Interrupt
 *     @arg      MEM_IT_IAE     Illegal Address Error Interrupt
 *     @arg      MEM_IT_WRE     Write Error Interrupt
 *     @arg      MEM_IT_REE     Read Error Interrupt
 * @retval none
 *****************************************************************************
 */  
#define __DRV_MEM_ENABLE_IT(__INTERRUPT__)    (MEM->INT.B[0] |= (__INTERRUPT__))


/**
 *****************************************************************************
 * @brief  Disable the specified MEM interrupt.
 * @param  "__INTERRUPT__"  MEM interrupt 
 *         This parameter can be any combination of the following values:
 *     @arg      MEM_IT         ALL Interrupt
 *     @arg      MEM_IT_EOP     End of MEM Flash Operation Interrupt
 *     @arg      MEM_IT_IAE     Illegal Address Error Interrupt
 *     @arg      MEM_IT_WRE     Write Error Interrupt
 *     @arg      MEM_IT_REE     Read Error Interrupt
 * @retval none
 *****************************************************************************
 */  
#define __MID_MEM_DISABLE_IT(__INTERRUPT__)    (MEM->INT.B[0] &= ~(__INTERRUPT__))

/**
 *****************************************************************************
 * @brief  Disable the specified MEM interrupt.
 * @param  "__INTERRUPT__"  MEM interrupt 
 *         This parameter can be any combination of the following values:
 *     @arg      MEM_IT         ALL Interrupt
 *     @arg      MEM_IT_EOP     End of MEM Flash Operation Interrupt
 *     @arg      MEM_IT_IAE     Illegal Address Error Interrupt
 *     @arg      MEM_IT_WRE     Write Error Interrupt
 *     @arg      MEM_IT_REE     Read Error Interrupt
 * @retval none
 *****************************************************************************
 */ 
#define __DRV_MEM_DISABLE_IT(__INTERRUPT__)    (MEM->INT.B[0] &= ~(__INTERRUPT__))


/**
 *****************************************************************************
 * @brief  Get the specified MEM flag status. 
 * @param  "__FLAG__" specifies the MEM flag to check.
 *         This parameter can be one of the following values:
 *     @arg      MEM_FLAG_BUSY        MEM Busy flag
 *     @arg      MEM_FLAG_IAE         MEM Illegal Address error flag
 *     @arg      MEM_FLAG_WRE         MEM Programming error flag
 *     @arg      MEM_FLAG_REE         MEM Programming error flag
 *     @arg      MEM_FLAG_EOP         MEM Flash End of Operation flag
 *     @arg      MEM_FLAG_IAPSE       MEM IAP Size error Flag
 * @retval The new state of __FLAG__ (SET or RESET).
 *****************************************************************************
 */
#define __MID_MEM_GET_FLAG(__FLAG__)    ((MEM->STA.W) & (__FLAG__))


/**
 *****************************************************************************
 * @brief  Get the specified MEM flag status. 
 * @param  "__FLAG__" specifies the MEM flag to check.
 *         This parameter can be one of the following values:
 *     @arg      MEM_FLAG_BUSY        MEM Busy flag
 *     @arg      MEM_FLAG_IAE         MEM Illegal Address error flag
 *     @arg      MEM_FLAG_WRE         MEM Programming error flag
 *     @arg      MEM_FLAG_REE         MEM Programming error flag
 *     @arg      MEM_FLAG_EOP         MEM Flash End of Operation flag
 *     @arg      MEM_FLAG_IAPSE       MEM IAP Size error Flag
 * @retval The new state of __FLAG__ (SET or RESET).
 *****************************************************************************
 */
#define __DRV_MEM_GET_FLAG(__FLAG__)    ((MEM->STA.W) & (__FLAG__))


/**
 *****************************************************************************
 * @brief  Clear the specified MEM flag.
 * @param  "__FLAG__" specifies the MEM flags to clear.
 *         This parameter can be any combination of the following values:
 *     @arg      MEM_FLAG_BUSY        MEM Busy flag
 *     @arg      MEM_FLAG_IAE         MEM Illegal Address error flag
 *     @arg      MEM_FLAG_WRE         MEM Programming error flag
 *     @arg      MEM_FLAG_REE         MEM Programming error flag
 *     @arg      MEM_FLAG_EOP         MEM End of Operation flag
 *     @arg      MEM_FLAG_IAPSE       MEM IAP Size error Flag
 * @retval none
 *****************************************************************************
 */
#define __MID_MEM_CLEAR_FLAG(__FLAG__)    ((MEM->STA.W) = (__FLAG__))

/**
 *****************************************************************************
 * @brief  Clear the specified MEM flag.
 * @param  "__FLAG__" specifies the MEM flags to clear.
 *         This parameter can be any combination of the following values:
 *     @arg      MEM_FLAG_BUSY        MEM Busy flag
 *     @arg      MEM_FLAG_IAE         MEM Illegal Address error flag
 *     @arg      MEM_FLAG_WRE         MEM Programming error flag
 *     @arg      MEM_FLAG_REE         MEM Programming error flag
 *     @arg      MEM_FLAG_EOP         MEM End of Operation flag
 *     @arg      MEM_FLAG_IAPSE       MEM IAP Size error Flag
 * @retval none
 *****************************************************************************
 */
#define __DRV_MEM_CLEAR_FLAG(__FLAG__)    ((MEM->STA.W) = (__FLAG__))


/**
 * @}
 */

/**
 * @}
 */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup  FLASH_Exported_Functions
 * @{
 */

/** @addtogroup  MEM_Exported_Functions_Group1
 * @{
 */
/* IO operation functions *****************************************************/
MID_StatusTypeDef MID_MEM_FlashProgram(uint32_t Address, uint32_t Data);
MID_StatusTypeDef MID_MEM_FlashPageErase(uint32_t PageAddress);

MID_StatusTypeDef MID_MEM_ConfigIAPSize(uint32_t Size);

MID_StatusTypeDef MID_MEM_IAPSizeLock(void);
FunctionalState MID_MEM_GetIAPSizeLockState(void);

MID_StatusTypeDef MID_MEM_IAPExecuteDisable(void);
FunctionalState MID_MEM_GetIAPExecuteState(void);

/* MEM IRQHandler and Callbacks used in non blocking modes (Interrupt and DMA) */
/* MEM IRQ handler method */
void MID_MEM_IRQHandler(void);
/* Callbacks in non blocking modes */
void MID_MEM_ITHandlerCallback(void);

/**
 *****************************************************************************
 * @brief  Check MEM IAP Space Size
 * @retval Value IAP Size Byte.
 *****************************************************************************
 */
#define MID_MEM_GetIAPSize()    (MEM->IAPSZ.W << 2)


/**
 *****************************************************************************
 * @brief  Check MEM Boot FROM Who.
 * @retval Status MEM_BOOT_MASK         MEM FLASH Busy flag
 *                MEM_BOOT_FROM_AP      MEM FLASH Illegal Address error flag
 *                MEM_BOOT_FROM_ISP     MEM FLASH Programming error flag
 *                MEM_BOOT_FROM_SRAM    MEM FLASH Programming error flag
 *****************************************************************************
 */
#define MID_MEM_GetBootFromState()    (MEM->CR0.W & (~MEM_CR0_BOOT_MS_mask_w))


void MID_MEM_WarmResettoAP(void) __attribute__((noreturn));
void MID_MEM_WarmResettoISP(void) __attribute__((noreturn));
void MID_MEM_WarmResettoSRAM(void) __attribute__((noreturn));

/**
 * @}
 */

/** @addtogroup  MEM_Exported_Functions_Group2
 * @{
 */
/* Peripheral Control functions ***********************************************/
MID_StatusTypeDef MID_MEM_Unlock(void);
MID_StatusTypeDef MID_MEM_Lock(void);

/**
 * @}
 */

/** @addtogroup  MEM_Exported_Functions_Group3
 * @{
 */
/* Peripheral State and Error functions ***************************************/
uint32_t MID_MEM_GetError(void);

/**
 * @}
 */

/**
 * @}
 */

/* Private function -------------------------------------------------*/
/** @addtogroup  MEM_Private_Functions
 * @{
 */
MID_StatusTypeDef MID_MEM_WaitForLastOperation(uint32_t Timeout);

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

#endif /* __MG32x02z_MEM_MID_H */

/************** (C) COPYRIGHT megawin Technology Co., Ltd. *****END OF FILE****/

