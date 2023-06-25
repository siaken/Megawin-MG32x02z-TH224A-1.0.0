/**
 ******************************************************************************
 * @file        MG32x02z_I2C_MID_ex.c
 * @brief       I2C Extended MID module driver.
 *              This file provides firmware functions to manage the following
 *              functionalities of I2C Extended peripheral:
 *                  + Extended features functions
 * @par         Project
 *              MG32x02z
 * @version     V1.01
 * @date        2020/08/04
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2020 megawin Technology Co., Ltd.
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
 @verbatim
 ==============================================================================
              ##### I2C peripheral Extended features  #####
 ==============================================================================

 [..] Comparing to other previous devices, the I2C interface for MG32x02z
      devices contains the following additional features

      (+) Possibility to disable or enable Analog Noise Filter
      (+) Use of a configured Digital Noise Filter
      (+) Use of a configured Pre Drive Time
      (+) Disable or enable wakeup from Stop modes

                    ##### How to use this driver #####
 ==============================================================================
 [..] This driver provides functions to configure Noise Filter and Wake Up Feature
   (#) Configure I2C Digital noise filter using the function MID_I2CEx_ConfigDigitalFilter()
   (#) Configure I2C PreDrive Time using the function MID_I2CEx_ConfigPreDriveTime()
   (#) Configure the enable or disable of I2C Wake Up Mode using the functions :
         (++) MID_I2CEx_EnableWakeUp()
         (++) MID_I2CEx_DisableWakeUp()
 @endverbatim
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2020 megawin Technology Co., Ltd.</center></h2>
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

/* Includes ------------------------------------------------------------------*/
#include "MG32x02z_I2C_MID_ex.h"

/** @name MG32x02z_Driver_MID
 * @{
 */

/** @name I2CEx I2CEx
 * @brief I2C Extended MID module driver
 * @{
 */

// #ifdef MID_I2C_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @name I2CEx_Exported_Functions I2C Extended Exported Functions
 * @{
 */

/** @name    I2CEx_Exported_Functions_Group1 Extended features functions
 * @brief    Extended features functions
 *
@verbatim
 ===============================================================================
                      ##### Extended features functions #####
 ===============================================================================
    [..] This section provides functions allowing to:
      (+) Configure Noise Filters
      (+) Configure Wake Up Feature
      (+) Configure Fast Mode Plus

@endverbatim
 * @{
 */


/**
 ******************************************************************************
 * @brief Config the I2C Pre-Drive Time driving capability.
 * @param mI2C: I2C handle. 
 * @param PreDriveTimeSelection: Selects the Pre-Drive Time.
 *   This parameter can be one of the reference I2CEx_PreDriveTime values
 * @retval None
 ******************************************************************************
 */
MID_StatusTypeDef MID_I2CEx_ConfigPreDriveTime(I2C_HandleTypeDef *mI2C, uint32_t PreDriveTimeSelection)
{
    uint32_t lRegTmp;
    /* Check the parameter */
    assert_param(IS_I2C_PREDRIVETIME(PreDriveTimeSelection));

    if((mI2C->State & MID_I2C_STATE_READY) != 0)
    {
        /* Process Locked */
        __MID_LOCK(mI2C);

        mI2C->State = MID_I2C_STATE_BUSY;

        /* Disable the selected I2C peripheral */
        __DRV_I2C_DISABLE(mI2C);

        /* Enable wakeup from stop mode */
        lRegTmp = mI2C->Instance->CR0.W;
        lRegTmp &= ~I2C_PDT_MASK;
        lRegTmp |= PreDriveTimeSelection;
        mI2C->Instance->CR0.W = lRegTmp;

        __DRV_I2C_ENABLE(mI2C);

        mI2C->State = MID_I2C_STATE_READY;

        /* Process Unlocked */
        __MID_UNLOCK(mI2C);

        return MID_OK;
    }
    else
    {
        return MID_BUSY;
    }
}

#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
/**
 ******************************************************************************
 * @brief  Enable I2C wakeup from stop mode.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2Cx peripheral.
 * @retval MID status
 ******************************************************************************
 */
MID_StatusTypeDef MID_I2CEx_EnableWakeUp(I2C_HandleTypeDef *mI2C)
{
    /* Check the parameters */
    assert_param(IS_I2C_WAKEUP_FROMSTOP_INSTANCE(mI2C->Instance));

    if((mI2C->State & MID_I2C_STATE_READY) != 0)
    {
        /* Process Locked */
        __MID_LOCK(mI2C);

        mI2C->State = MID_I2C_STATE_BUSY;

        /* Disable the selected I2C peripheral */
        __DRV_I2C_DISABLE(mI2C);

        /* Enable wakeup from stop mode */
        mI2C->Instance->INT.W |= I2C_INT_WUP_IE_mask_w;

        __DRV_I2C_ENABLE(mI2C);

        mI2C->State = MID_I2C_STATE_READY;

        /* Process Unlocked */
        __MID_UNLOCK(mI2C);

        return MID_OK;
    }
    else
    {
        return MID_BUSY;
    }
}

/**
 ******************************************************************************
 * @brief  Disable I2C wakeup from stop mode.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2Cx peripheral.
 * @retval MID status
 ******************************************************************************
 */
MID_StatusTypeDef MID_I2CEx_DisableWakeUp(I2C_HandleTypeDef *mI2C)
{
    /* Check the parameters */
    assert_param(IS_I2C_WAKEUP_FROMSTOP_INSTANCE(mI2C->Instance));

    if((mI2C->State & MID_I2C_STATE_READY) != 0)
    {
        /* Process Locked */
        __MID_LOCK(mI2C);

        mI2C->State = MID_I2C_STATE_BUSY;

        /* Disable the selected I2C peripheral */
        __DRV_I2C_DISABLE(mI2C);

        /* Enable wakeup from stop mode */
        mI2C->Instance->INT.W &= (~I2C_INT_WUP_IE_mask_w);

        __DRV_I2C_ENABLE(mI2C);

        mI2C->State = MID_I2C_STATE_READY;

        /* Process Unlocked */
        __MID_UNLOCK(mI2C);

        return MID_OK;
    }
    else
    {
        return MID_BUSY;
    }
}
#endif

/**
 * @}
 */

/**
 * @}
 */

// #endif /* MID_I2C_MODULE_ENABLED */
/**
 * @}
 */

/**
 * @}
 */

/************** (C) COPYRIGHT megawin Technology Co., Ltd. *****END OF FILE****/


