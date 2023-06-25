/**
 ******************************************************************************
 * @file        MG32x02z_I2C_MID_ex.h
 * @brief       Header file of I2C MID Extended module.
 * @par         Project
 *              MG32x02z
 * @version     V1.02
 * @date        2021/04/21
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2020 megawin Technology Co., Ltd.
 *              All rights reserved.
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
#ifndef _MG32x02z_I2C_MID_EX_H
#define _MG32x02z_I2C_MID_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MG32x02z_Common_MID.h"
#include "MG32x02z_I2C_MID.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/**
 @ @name I2CEx_PreDriveTime I2C Extended Pre-Drive Time
 * @{
 */
#define I2C_PDT_MASK                    I2C_CR0_PDRV_SEL_mask_w     /*!< Pre-Drive Time Mask            */
#define I2C_PDT_NONE                    I2C_CR0_PDRV_SEL_0t_w       /*!< Zero Pre-Drive Time            */
#define I2C_PDT_0T                      I2C_CR0_PDRV_SEL_0t_w       /*!< 0 I2C_PR CLK Pre-Drive Time    */
#define I2C_PDT_1T                      I2C_CR0_PDRV_SEL_1t_w       /*!< 1 I2C_PR CLK Pre-Drive Time    */
#define I2C_PDT_2T                      I2C_CR0_PDRV_SEL_2t_w       /*!< 2 I2C_PR CLK Pre-Drive Time    */
#define I2C_PDT_3T                      I2C_CR0_PDRV_SEL_3t_w       /*!< 3 I2C_PR CLK Pre-Drive Time    */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Peripheral Control functions  ************************************************/


MID_StatusTypeDef MID_I2CEx_ConfigPreDriveTime(I2C_HandleTypeDef *hi2c, uint32_t PreDriveTimeSelection);

#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
  MID_StatusTypeDef MID_I2CEx_EnableWakeUp(I2C_HandleTypeDef *hi2c);
  MID_StatusTypeDef MID_I2CEx_DisableWakeUp(I2C_HandleTypeDef *hi2c);
#endif

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/**
 * @brief  I2CEx Parameter check
 * @{
 */
#define IS_I2C_DIGITAL_FILTER(FILTER)   ((FILTER) <= 0x0000000FU)

#define IS_I2C_FASTMODEPLUS(__CONFIG__) (((__CONFIG__) == I2C_PDT_MASK)     || \
                                         ((__CONFIG__) == I2C_PDT_NONE)    || \
                                         ((__CONFIG__) == I2C_PDT_0T)     || \
                                         ((__CONFIG__) == I2C_PDT_1T)     || \
                                         ((__CONFIG__) == I2C_PDT_2T)     || \
                                         ((__CONFIG__) == I2C_PDT_3T)     || \
                                         ((__CONFIG__) == I2C_PDT_MASK))    /*!< I2CEx_PreDriveTime I2C Extended Pre-Drive Time */
/**
 * @}
 */

/* Private Functions ---------------------------------------------------------*/
/* Private functions are defined in MG32x02z_I2C_MID_ex.c file */

#ifdef __cplusplus
}
#endif

#endif /* __MG32x02z_I2C_MID_EX_H */

/************** (C) COPYRIGHT megawin Technology Co., Ltd. *****END OF FILE****/


