/**
 ******************************************************************************
 * @file        MG32x02z_EMB_MID.c
 * @brief       EMB MID module driver.
 *              This file provides firmware functions to manage the following
 *              functionalities of the Inter Integrated Circuit (EMB) peripheral:
 *                  + Initialization and de-initialization functions
 *
 * @par         Project
 *              MG32x02z
 * @version     V2.53
 * @date        2020/03/17
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

/* Includes ------------------------------------------------------------------*/
#include "MG32x02z_EMB_MID.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @name EMB_Functions_Group1 Initialization/de-initialization functions
  *  @{
  */

/**
 ******************************************************************************
 * @brief  Initialize the EMB device according to the specified
 *         control parameters in the EMB_Mode_InitTypeDef
 * @param  mEMB: Pointer to a EMB_HandleTypeDef structure that contains
 *               the configuration information for the specified EMB.
 * @retval MID status
 * @note
 * @par         Example I80 16-Bits to LCD Ili9341
 * @code
      EMB_HandleTypeDef mEMB;

      mEMB.Instance = EMB;
      mEMB.Init.DeviceAccess = EMB_DEVICE_ACCESS_ASYNCHRONOUS;
      mEMB.Init.WriteSignal = EMB_WRITE_SIGNAL_TOGGLE;
      mEMB.Init.ReadSignal = EMB_READ_SIGNAL_TOGGLE;
      mEMB.Init.DataAddressMux = EMB_DATA_ADDRESS_MUX_DISABLE;
      mEMB.Init.DataAddressMuxMode = EMB_DATA_ADDRESS_MULTIPLEX_1ALE;
      mEMB.Init.AddressRange = EMB_ADDRESS_RANGE_16BIT;
      mEMB.Init.WriteAccess = EMC_WRITE_ACCESS_ENABLE;
    #if defined(MG32_3RD)
      mEMB.Init.DeviceDataWidth = EMB_DEVICE_DATA_BUS_WIDTH_16;
      mEMB.Init.AddressMAM1 = EMB_ADDRESS_MAM1_SIGNAL_DISABLE;
      mEMB.Init.WriteByteAccess = EMB_WRITE_BYTE_ACCESS_DISABLE;
      mEMB.Extended.MADBusByteSwap = EMB_MAD_BYTE_SWAP_DISABLE;
      mEMB.Extended.MADBusReverse = EMB_MAD_REVERSE_DISABLE;
    #endif
      mEMB.Extended.MABusReverse = EMB_MA_REVERSE_DISABLE;
      mEMB.Extended.MCLK_Inverse = EMB_MCLK_INVERSE_DISABLE;
      mEMB.Extended.MALE2_Inverse = EMB_MALE2_INVERSE_DISABLE;
      mEMB.Extended.MALE_Inverse = EMB_MALE_INVERSE_DISABLE;
      mEMB.Extended.MCE_Inverse = EMB_MCE_INVERSE_DISABLE;
      mEMB.CLKPrescaler = 1;
      mEMB.AddressSetupTime = 0;
      mEMB.AddressPulseTime = 1;
      mEMB.AddressHoldTime = 0;
      mEMB.DataSetupTime = 1;
      mEMB.DataAccessTime = 2;
      mEMB.DataHoldTime = 1;
      mEMB.IdleTime = 0;
      MID_EMB_Init(&mEMB);
 * @endcode
 ******************************************************************************
 */
MID_StatusTypeDef MID_EMB_Init(EMB_HandleTypeDef *mEMB)
{
    //__IO uint32_t lTemp32;
    /* Check the parameters */
    assert_param(IS_EMB_DEVICE(mEMB->Mode.DeviceAccess));
    assert_param(IS_EMB_WRITE_SIGNAL(mEMB->Mode.WriteSignal));
    assert_param(IS_EMB_READ_SIGNAL(mEMB->Mode.ReadSignal));
    assert_param(IS_EMB_MUX(mEMB->Mode.DataAddressMux));
    assert_param(IS_EMB_MUX_MODE(mEMB->Mode.DataAddressMuxMode));
    assert_param(IS_EMB_WRITE(mEMB->Mode.WriteAccess));
    assert_param(IS_EMB_RANGE(mEMB->Mode.AddressRange));

    assert_param(IS_EMB_MA_REVERSE(mEMB->Extended.MABusReverse));
    assert_param(IS_EMB_MCLK_INVERSE(mEMB->Extended.MCLK_Inverse));
    assert_param(IS_EMB_MALE2_INVERSE(mEMB->Extended.MALE2_Inverse));
    assert_param(IS_EMB_MALE_INVERSE(mEMB->Extended.MALE_Inverse));
    assert_param(IS_EMB_MCE_INVERSE(mEMB->Extended.MCE_Inverse));

    assert_param(IS_EMB_PRESCALER(mEMB->CLKPrescaler));
    assert_param(IS_EMB_DATA_SETUP_TIME(mEMB->DataSetupTime));
    assert_param(IS_EMB_DATA_ACCESS_TIME(mEMB->DataAccessTime));
    assert_param(IS_EMB_DATA_HOLD_TIME(mEMB->DataHoldTime));
    assert_param(IS_EMB_ADDRESS_SETUP_TIME(mEMB->AddressSetupTime));
    assert_param(IS_EMB_ADDRESS_PLUSE_TIME(mEMB->AddressPulseTime));
    assert_param(IS_EMB_ADDRESS_HOLD_TIME(mEMB->AddressHoldTime));

  #if defined(MG32_3RD)
    assert_param(IS_EMB_MAM1_SIGNAL(mEMB->ModeInit.AddressMAM1));
    assert_param(IS_EMB_DEVICE_DATA_WIDTH(mEMB->ModeInit.DeviceDataWidth));
    assert_param(IS_EMB_BYTE_WRITE(mEMB->ModeInit.WriteByteAccess));

    assert_param(IS_EMB_MAD_BYTE_REVERSE(mEMB->Extended.MADBusByteSwap));
    assert_param(IS_EMB_MAD_REVERSE(mEMB->Extended.MADBusReverse));

    assert_param(IS_EMB_IDLE_TIME(mEMB->IdleTime));
  #endif

    if((mEMB->Instance->STA.W & EMB_STA_BUSYF_mask_w) == 0)
    {
        __DRV_EMB_DISABLE(mEMB);

        MID_EMB_MspInit(mEMB);

        mEMB->Instance->CLK.W = ((mEMB->CLKPrescaler - 1) << 4);

      #if defined(MG32_1ST)
        mEMB->Instance->CR0.W = (EMB_CR0_DMA_EN_mask_w | \
                                 mEMB->Init.WriteSignal | \
                                 mEMB->Init.ReadSignal | \
                                 mEMB->Init.AddressRange | \
                                 mEMB->Init.DataAddressMuxMode | \
                                 mEMB->Init.DataAddressMux | \
                                 mEMB->Init.DeviceAccess | \
                                 mEMB->Init.WriteAccess);

        mEMB->Instance->CR1.W = (mEMB->Extended.MABusReverse | \
                                 mEMB->Extended.MCLK_Inverse | \
                                 mEMB->Extended.MALE2_Inverse | \
                                 mEMB->Extended.MALE_Inverse | \
                                 mEMB->Extended.MCE_Inverse | \
                                 0x00000200);

        mEMB->Instance->CR2.W = ((mEMB->AddressSetupTime << 0) | \
                                ((mEMB->AddressPulseTime - 1) << 4) | \
                                 (mEMB->AddressHoldTime << 8) | \
                                 (mEMB->DataSetupTime << 12) | \
                                ((mEMB->DataAccessTime - 1) << 16) | \
                                 (mEMB->DataHoldTime << 20 ));
      #endif

      #if defined(MG32_3RD)
        mEMB->Instance->CR0.W = EMB_CR0_DMA_EN_mask_w | \
                                mEMB->Init.WriteSignal | \
                                mEMB->Init.ReadSignal | \
                                mEMB->Init.AddressRange | \
                                mEMB->Init.DataAddressMuxMode | \
                                mEMB->Init.DataAddressMux | \
                                mEMB->Init.AddressMAM1 | \
                                mEMB->Init.DeviceDataWidth | \
                                mEMB->Init.DeviceAccess | \
                                mEMB->Init.WriteByteAccess | \
                                mEMB->Init.WriteAccess | \
                                0;

        mEMB->Instance->CR1.W = mEMB->Extended.MADBusByteSwap | \
                                mEMB->Extended.MADBusReverse | \
                                mEMB->Extended.MABusReverse | \
                                mEMB->Extended.MCLK_Inverse | \
                                mEMB->Extended.MALE2_Inverse | \
                                mEMB->Extended.MALE_Inverse | \
                                mEMB->Extended.MCE_Inverse | \
                                0;

        mEMB->Instance->CR2.W = (mEMB->AddressSetupTime << 0) | \
                               ((mEMB->AddressPulseTime - 1) << 4) | \
                                (mEMB->AddressHoldTime << 8) | \
                                (mEMB->DataSetupTime << 12) | \
                               ((mEMB->DataAccessTime - 1) << 16) | \
                                (mEMB->DataHoldTime << 20 ) | \
                                (mEMB->IdleTime << 24) | \
                                0;
      #endif
        __DRV_EMB_ENABLE(mEMB);
    }
    else
    {
        return MID_BUSY;
    }
    return MID_OK;
}

/**
 ******************************************************************************
 * @brief  Initialize the EMB device according to the specified
 *         control parameters in the EMB_Mode_InitTypeDef
 * @param  mEMB: Pointer to a EMB_HandleTypeDef structure that contains
 *               the configuration information for the specified EMB.
 * @retval MID status
 ******************************************************************************
 */
MID_StatusTypeDef MID_EMB_DeInit(EMB_HandleTypeDef *mEMB)
{
    if((mEMB->Instance->STA.W & EMB_STA_BUSYF_mask_w) == 0)
    {
        mEMB->Instance->CR0.W = 0;
        mEMB->Instance->INT.W = 0;
        mEMB->Instance->CLK.W = 0;
        mEMB->Instance->CR1.W = 0;
        mEMB->Instance->CR2.W = 0;

        MID_EMB_MspDeInit(mEMB);

        return MID_OK;
    }
    else
    {
        return MID_BUSY;
    }
}

/**
 *******************************************************************************
 * @brief       Initalize the EMB MSP.
 * @details     
 * @param[in]   mEMB : EMB handle.
 * @return      No
 * @exception   No
 * @note        No
 *******************************************************************************
 */
__weak void MID_EMB_MspInit(EMB_HandleTypeDef* mEMB)
{
    //===========================================================
    //Prevent unsed argument(s) compilation warning
    UNUSED(mEMB);
    
    //===========================================================
    //Note : This function should not be modified , when the callback is needed,
    //       the MID_URT_MspInit can be implemented in the user file.
    
}

/**
 *******************************************************************************
 * @brief       DeInitalize the EMB MSP.
 * @details     
 * @param[in]   mEMB : EMB handle.
 * @return      No
 * @exception   No
 * @note        No
 *******************************************************************************
 */
__weak void MID_EMB_MspDeInit(EMB_HandleTypeDef* mEMB)
{
    //===========================================================
    //Prevent unsed argument(s) compilation warning
    UNUSED(mEMB);
    
    //===========================================================
    //Note : This function should not be modified , when the callback is needed,
    //       the MID_URT_MspDeInit can be implemented in the user file.
    
}

/**
 * @}
 */

/** @name EMB_Functions_Group2 EMB Control functions
 *  @{
 */
/**
 ******************************************************************************
 * @brief  Enables connect device write operation.
 * @param  mEMB: Pointer to a EMB_HandleTypeDef structure that contains
 *               the configuration information for the specified EMB.
 * @retval MID status
 ******************************************************************************
 */
MID_StatusTypeDef MID_EMB_WriteOperation_Enable(EMB_HandleTypeDef *mEMB)
{
    /* Enable write operation */
    mEMB->Instance->CR0.W |= EMB_CR0_WEN_mask_w;
    return MID_OK;
}

/**
 ******************************************************************************
 * @brief  Disables connect device write operation.
 * @param  mEMB: Pointer to a EMB_HandleTypeDef structure that contains
 *               the configuration information for the specified EMB.
 * @retval MID status
 ******************************************************************************
 */
MID_StatusTypeDef MID_EMB_WriteOperation_Disable(EMB_HandleTypeDef *mEMB)
{
    if((mEMB->Instance->STA.W & EMB_STA_BUSYF_mask_w) == 0)
    {
        /* Disable write operation */
        mEMB->Instance->CR0.W &= ~EMB_CR0_WEN_mask_w;
        return MID_OK;
    }
    else
    {
        return MID_BUSY;
    }
}

/**
 * @}
 */

#if defined(MG32_3RD)
/**
 ******************************************************************************
 * @brief  Access illegal address error detection callback.
 * @param  mEMB: Pointer to a EMB_HandleTypeDef structure that contains
 *               the configuration information for the specified EMB.
 * @retval None
 ******************************************************************************
 */
__weak void MID_EMB_IllegalAddressCallback(EMB_HandleTypeDef *mEMB __attribute__((unused)))
{
    
}

/**
 ******************************************************************************
 * @brief  Byte-write error callback.
 * @param  mEMB: Pointer to a EMB_HandleTypeDef structure that contains
 *               the configuration information for the specified EMB.
 * @retval None
 ******************************************************************************
 */
__weak void MID_EMB_ByteWriteProtectCallback(EMB_HandleTypeDef *mEMB __attribute__((unused)))
{
    
}
#endif

#if defined(MG32_1ST) || defined(MG32_3RD)
/**
 ******************************************************************************
 * @brief  Write-protect error detect callback.
 * @param  mEMB: Pointer to a EMB_HandleTypeDef structure that contains
 *               the configuration information for the specified EMB.
 * @retval None
 ******************************************************************************
 */
__weak void MID_EMB_WriteProtectCallback(EMB_HandleTypeDef *mEMB  __attribute__((unused)))
{
    
}
#endif


/**
 ******************************************************************************
 * @brief  This function handles EMB interrupt request.
 * @param  mEMB: Pointer to a EMB_HandleTypeDef structure that contains
 *               the configuration information for the specified EMB.
 * @retval None
 ******************************************************************************
 */
void MID_EMB_IRQHandler(EMB_HandleTypeDef *mEMB)
{
  #if defined(MG32_3RD)
    if(((mEMB->Instance->STA.W & EMB_STA_IAEF_mask_w) != 0) && ((mEMB->Instance->INT.W & EMB_INT_IAE_IE_mask_w) != 0))
    {
        MID_EMB_IllegalAddressCallback(mEMB);
    }

    if(((mEMB->Instance->STA.W & EMB_STA_BWEF_mask_w) != 0) && ((mEMB->Instance->INT.W & EMB_INT_BWE_IE_mask_w) != 0))
    {
        MID_EMB_ByteWriteProtectCallback(mEMB);
    }
  #endif

  #if defined(MG32_1ST) || defined(MG32_3RD)
    if(((mEMB->Instance->STA.W & EMB_STA_WPEF_mask_w) != 0) && ((mEMB->Instance->INT.W & EMB_INT_WPE_IE_mask_w) != 0))
    {
        MID_EMB_WriteProtectCallback(mEMB);
    }
  #endif
}


