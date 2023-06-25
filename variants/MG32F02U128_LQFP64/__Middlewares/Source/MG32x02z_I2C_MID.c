/**
 ******************************************************************************
 * @file        MG32x02z_I2C_MID.c
 * @brief       I2C MID module driver.
 *              This file provides firmware functions to manage the following
 *              functionalities of the Inter Integrated Circuit (I2C) peripheral:
 *                  + Initialization and de-initialization functions
 *                  + IO operation functions
 *                  + Peripheral State and Errors functions
 * @par         Project
 *              MG32x02z
 * @version     V1.10
 * @date        2020/10/04
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
  @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
    [..]
    The I2C MID driver can be used as follows:

    (#) Declare a I2C_HandleTypeDef handle structure, for example:
        I2C_HandleTypeDef  mI2C;

    (#)Initialize the I2C low level resources by implementing the MID_I2C_MspInit() API:
        (##) Enable the I2Cx interface clock
        (##) I2C pins configuration
            (+++) Enable the clock for the I2C GPIOs
            (+++) Configure I2C pins as alternate function open-drain
        (##) NVIC configuration if you need to use interrupt process
            (+++) Configure the I2Cx interrupt priority
            (+++) Enable the NVIC I2C IRQ Channel

    (#) Configure the Communication Clock Timing, Own Address1, Master Addressing mode, Dual Addressing mode,
        Own Address2, Own Address2 Mask, General call in the mI2C Init structure.

    (#) Initialize the I2C registers by calling the MID_I2C_Init(), configures also the low level Hardware
        (GPIO, CLOCK, NVIC...etc) by calling the customized MID_I2C_MspInit(&mI2C) API.

    (#) To check if target device is ready for communication, use the function MID_I2C_IsDeviceReady()

    (#) For I2C IO and IO MEM operations, three operation modes are available within this driver :

    *** Polling mode IO operation ***
    =================================
    [..]
      (+) Transmit in master mode an amount of data in blocking mode using MID_I2C_Master_Transmit()
      (+) Receive in master mode an amount of data in blocking mode using MID_I2C_Master_Receive()
      (+) Transmit in slave mode an amount of data in blocking mode using MID_I2C_Slave_Transmit()
      (+) Receive in slave mode an amount of data in blocking mode using MID_I2C_Slave_Receive()

    *** Polling mode IO MEM operation ***
    =====================================
    [..]
      (+) Write an amount of data in blocking mode to a specific memory address using MID_I2C_Mem_Write()
      (+) Read an amount of data in blocking mode from a specific memory address using MID_I2C_Mem_Read()

    *** Interrupt mode IO operation ***
    ===================================
    [..]
      (+) Transmit in master mode an amount of data in non-blocking mode using MID_I2C_Master_Transmit_IT()
      (+) At transmission end of transfer, MID_I2C_MasterTxCpltCallback() is executed and user can
           add his own code by customization of function pointer MID_I2C_MasterTxCpltCallback()
      (+) Receive in master mode an amount of data in non-blocking mode using MID_I2C_Master_Receive_IT()
      (+) At reception end of transfer, MID_I2C_MasterRxCpltCallback() is executed and user can
           add his own code by customization of function pointer MID_I2C_MasterRxCpltCallback()
      (+) Transmit in slave mode an amount of data in non-blocking mode using MID_I2C_Slave_Transmit_IT()
      (+) At transmission end of transfer, MID_I2C_SlaveTxCpltCallback() is executed and user can
           add his own code by customization of function pointer MID_I2C_SlaveTxCpltCallback()
      (+) Receive in slave mode an amount of data in non-blocking mode using MID_I2C_Slave_Receive_IT()
      (+) At reception end of transfer, MID_I2C_SlaveRxCpltCallback() is executed and user can
           add his own code by customization of function pointer MID_I2C_SlaveRxCpltCallback()
      (+) In case of transfer Error, MID_I2C_ErrorCallback() function is executed and user can
           add his own code by customization of function pointer MID_I2C_ErrorCallback()
      (+) Discard a slave receive I2C process communication using __DRV_I2C_GENERATE_NACK() macro.
           This action will inform Master to generate a Stop condition to discard the communication.

    *** Interrupt mode IO MEM operation ***
    =======================================
    [..]
      (+) Write an amount of data in non-blocking mode with Interrupt to a specific memory address using
          MID_I2C_Mem_Write_IT()
      (+) At transmission end of transfer, MID_I2C_MasterTxCpltCallback() is executed and user can
           add his own code by customization of function pointer MID_I2C_MasterTxCpltCallback()
      (+) Read an amount of data in non-blocking mode with Interrupt from a specific memory address using
          MID_I2C_Mem_Read_IT()
      (+) At transmission end of transfer, MID_I2C_MasterTxCpltCallback() is executed and user can
           add his own code by customization of function pointer MID_I2C_MasterTxCpltCallback()
      (+) At reception end of transfer, MID_I2C_MasterRxCpltCallback() is executed and user can
           add his own code by customization of function pointer MID_I2C_MasterRxCpltCallback()
      (+) In case of transfer Error, MID_I2C_ErrorCallback() function is executed and user can
           add his own code by customization of function pointer MID_I2C_ErrorCallback()

     *** I2C MID driver macros list ***
     ==================================
     [..]
       Below the list of most used macros in I2C MID driver.

      (+) __DRV_I2C_ENABLE: Enable the I2C peripheral
      (+) __DRV_I2C_DISABLE: Disable the I2C peripheral
      (+) __DRV_I2C_GENERATE_NACK: Generate a Non-Acknowledge I2C peripheral in Slave mode
      (+) __DRV_I2C_GET_FLAG: Check whether the specified I2C flag is set or not
      (+) __DRV_I2C_CLEAR_FLAG: Clear the specified I2C pending flag
      (+) __DRV_I2C_ENABLE_IT: Enable the specified I2C interrupt
      (+) __DRV_I2C_DISABLE_IT: Disable the specified I2C interrupt

     [..]
       (@) You can refer to the I2C MID driver header file for more useful macros

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

/* Wizards- ------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
#include "MG32x02z_I2C_MID.h"
#include "MG32x02z_CSC_MID.h"

#include "MG32x02z_DRV.h"
#include <Arduino.h>
/** @name I2C I2C 
 * @brief I2C MID module driver
 * @{
 */

//#ifdef MID_I2C_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/**
 * @name I2C_Private_Define I2C Private Define
 * @{
 */

#if 0
/**
 * @brief  I2C Internal define
*/
#define I2C_TIMING_CLEAR_MASK       ((uint32_t)0xFFFFFFFFU)  /*!< I2C TIMING clear register Mask */
#define I2C_TIMEOUT_BUSY            ((uint32_t)25U)          /*!< 25 ms */
#define I2C_TIMEOUT_FLAG            ((uint32_t)25U)          /*!< 25 ms */

/* Private define for reference PreviousState usage */
#define I2C_STATE_MSK               ((uint32_t)((MID_I2C_STATE_BUSY_TX | MID_I2C_STATE_BUSY_RX) & (~MID_I2C_STATE_READY))) /*!< Mask State define, keep only RX and TX bits           */
#define I2C_STATE_NONE              ((uint32_t)(MID_I2C_MODE_NONE))                                                        /*!< Default Value                                         */
#define I2C_STATE_MASTER_BUSY_TX    ((uint32_t)((MID_I2C_STATE_BUSY_TX & I2C_STATE_MSK) | MID_I2C_MODE_MASTER))            /*!< Master Busy TX, combinaison of State LSB and Mode enum */
#define I2C_STATE_MASTER_BUSY_RX    ((uint32_t)((MID_I2C_STATE_BUSY_RX & I2C_STATE_MSK) | MID_I2C_MODE_MASTER))            /*!< Master Busy RX, combinaison of State LSB and Mode enum */
#define I2C_STATE_SLAVE_BUSY_TX     ((uint32_t)((MID_I2C_STATE_BUSY_TX & I2C_STATE_MSK) | MID_I2C_MODE_SLAVE))             /*!< Slave Busy TX, combinaison of State LSB and Mode enum */
#define I2C_STATE_SLAVE_BUSY_RX     ((uint32_t)((MID_I2C_STATE_BUSY_RX & I2C_STATE_MSK) | MID_I2C_MODE_SLAVE))             /*!< Slave Busy RX, combinaison of State LSB and Mode enum */
#define I2C_STATE_MEM_BUSY_TX       ((uint32_t)((MID_I2C_STATE_BUSY_TX & I2C_STATE_MSK) | MID_I2C_MODE_MEM))               /*!< Memory Busy TX, combinaison of State LSB and Mode enum */
#define I2C_STATE_MEM_BUSY_RX       ((uint32_t)((MID_I2C_STATE_BUSY_RX & I2C_STATE_MSK) | MID_I2C_MODE_MEM))               /*!< Memory Busy RX, combinaison of State LSB and Mode enum */

/* Private define to centralize the enable/disable of Interrupts */
#define I2C_IT_BUF                  I2C_INT_BUF_IE_mask_w                                                                  /*!< Using on Buffmode */
/**
 * @}
 */

/* Private macro -------------------------------------------------------------*/
/**
 * @brief       I2C_BUFFMODE_DISABLE
 * @param       "__HANDLE__": specifies the I2C Handle.
 * @return      None
 * @{
 */
#define I2C_BUFFMODE_DISABLE(__HANDLE__)        ((__HANDLE__)->Instance->CR0.B[0] &= ~I2C_CR0_BUF_EN_mask_b0)               /*!< Buffmode disable */
 /** @}
 */

/**
 * @brief       I2C_GET_BUFFMODE_STATE
 * @param       "__HANDLE__": specifies the I2C Handle.
 * @return      FlagStatus
 * @{
 */
#define I2C_GET_BUFFMODE_STATE(__HANDLE__)      ((((__HANDLE__)->Instance->CR0.B[0] & I2C_CR0_BUF_EN_mask_b0) == 0) ? CLR : SET)    /*!< Get BufferMode Register Bit State */
 /** @}
 */

#endif

#pragma GCC diagnostic ignored"-Wimplicit-fallthrough="

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void I2C_ListenP(I2C_HandleTypeDef *mI2C);
static MID_StatusTypeDef I2C_BytemodeMasterEventHandle(I2C_HandleTypeDef *mI2C);
static MID_StatusTypeDef I2C_Master_ISR_IT(struct tag_I2C_HandleTypeDef *mI2C, uint32_t ITFlags, uint32_t ITSources);
 MID_StatusTypeDef I2C_BytemodeSlaveEventHandle(I2C_HandleTypeDef *mI2C);

//static MID_StatusTypeDef I2C_Slave_ISR_IT(struct tag_I2C_HandleTypeDef *mI2C, uint32_t ITFlags, uint32_t ITSources);
MID_StatusTypeDef I2C_Slave_ISR_IT(struct tag_I2C_HandleTypeDef *mI2C, uint32_t ITFlags, uint32_t ITSources);

static MID_StatusTypeDef I2C_WaitOnEVENTFlagUntilTimeout(I2C_HandleTypeDef *mI2C, uint32_t Timeout, uint32_t Tickstart);


/* Exported functions --------------------------------------------------------*/
/** @name I2C_Exported_Functions I2C Exported Functions
 * @{
 */

/** @name   I2C_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief      Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This subsection provides a set of functions allowing to initialize and
          deinitialize the I2Cx peripheral:

      (+) User must Implement MID_I2C_MspInit() function in which he configures
          all related peripherals resources (CLOCK, GPIO, DMA, IT and NVIC ).

      (+) Call the function MID_I2C_Init() to configure the selected device with
          the selected configuration:
        (++) Clock Timing
        (++) Own Address 1
        (++) Own Address 1 Mask
        (++) Addressing mode (Master, Slave)
        (++) Dual Addressing mode
        (++) Own Address 2
        (++) General call mode

      (+) Call the function MID_I2C_DeInit() to restore the default configuration
          of the selected I2Cx peripheral.

@endverbatim
 * @{
 */

/**
 ******************************************************************************
 * @brief  Initializes the I2C according to the specified parameters
 *         in the MID_I2C_GetInitTiming and initialize the associated handle.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @param  SCLClock: I2C Transfor Speed 
 * @retval MID status
 * Compiler Level Default Code 620Byte / RO-data 0 / RW-data 0 / ZI-data 0
 ******************************************************************************
 */
uint32_t MID_I2C_GetInitTiming(I2C_HandleTypeDef *mI2C, uint32_t SCLClock)  
{
    __IO uint32_t lI2Cx_CK_PRFreq = 0;
    __IO uint32_t lI2C_PSC = 1;
    __IO uint32_t lI2C_DIV = 1;
    __IO uint32_t lI2C_DIV_CNT = 0;
    __IO uint32_t lI2C_HT_LT;

    union{
        uint32_t W;
        struct {
            uint32_t                    :2;
            uint32_t CLKSource          :2;
            uint32_t Divider            :3;
            uint32_t                    :1;
            uint32_t Prescal            :4;
            uint32_t TimeoutClockSource :1;
            uint32_t                    :3;
            uint32_t LowTime            :8;
            uint32_t HighTime           :8;
        }Struct;
    }I2C_CLK_Config;

    /* Check the I2C handle allocation */
    if(mI2C == NULL)
    {
        return MID_ERROR;
    }

    I2C_CLK_Config.W = 0UL;

    if(mI2C->Instance == I2C0)
    {
        lI2Cx_CK_PRFreq = MID_CSC_GetCK_PRFreq(MID_CSC_CK_PR_I2C0);
    }

  #if defined(I2C1)
    if(mI2C->Instance == I2C1)
    {
        lI2Cx_CK_PRFreq = MID_CSC_GetCK_PRFreq(MID_CSC_CK_PR_I2C1);
    }
  #endif

    if(lI2Cx_CK_PRFreq <= 900000)
    {
        lI2C_PSC = 1;
        lI2C_DIV = 1;
        lI2C_HT_LT = 9;
    }
    else
    {
      #if defined(MG32_1ST)
        do{           
            lI2C_HT_LT = lI2Cx_CK_PRFreq / SCLClock / lI2C_PSC / lI2C_DIV;
            if((lI2C_HT_LT >= 32) || (lI2C_HT_LT <= 9))
            {
                lI2C_PSC ++;
                if(lI2C_PSC > 8)
                {
                    lI2C_PSC = 1;
                    lI2C_DIV += lI2C_DIV;
                }
            }
        }while((lI2C_HT_LT >= 32) || (lI2C_HT_LT <= 9));
      #else
        do{
            lI2C_HT_LT = lI2Cx_CK_PRFreq / SCLClock / lI2C_PSC / lI2C_DIV;
            if((lI2C_HT_LT >= 64) || (lI2C_HT_LT <= 9)) 
            {
                lI2C_PSC ++;
                if(lI2C_PSC > 16)
                {
                    lI2C_PSC = 1;
                    lI2C_DIV += lI2C_DIV;
                }
            }
        }while((lI2C_HT_LT >= 64) || (lI2C_HT_LT <= 9));
      #endif
    }

    if(lI2C_DIV == 1)
        lI2C_DIV_CNT = 0;
    else
    {
        lI2C_DIV = (lI2C_DIV >> 1);
        do{
            lI2C_DIV_CNT ++;
            lI2C_DIV = (lI2C_DIV >> 1);
        }while(lI2C_DIV != 0);
    }
    I2C_CLK_Config.Struct.CLKSource = 0;
    I2C_CLK_Config.Struct.Prescal = lI2C_PSC - 1;
    I2C_CLK_Config.Struct.Divider = lI2C_DIV_CNT;
    I2C_CLK_Config.Struct.LowTime = (lI2C_HT_LT >> 1) - 1;
    I2C_CLK_Config.Struct.HighTime = (lI2C_HT_LT - (lI2C_HT_LT >> 1));

    return I2C_CLK_Config.W;
}

/**
 ******************************************************************************
 * @brief  Initializes the I2C according to the specified parameters
 *         in the I2C_InitTypeDef and initialize the associated handle.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @retval MID status
 * @par         Example
 * @code
    I2C_HandleTypeDef mI2C0;
 
    mI2C0.Instance = I2C0;
    mI2C0.Init.Timing = MID_I2C_GetInitTiming(&mI2C0, 1000000);
    mI2C0.Init.OwnAddress1 = 0x20;
    mI2C0.Init.DualAddressMode = I2C_DUALADDRESS_ENABLE;
    mI2C0.Init.OwnAddress2 = 0x80;
    mI2C0.Init.GeneralCallMode = I2C_GENERALCALL_ENABLE;
    MID_I2C_Init(&mI2C0);
 * @endcode  
 ******************************************************************************
 */
MID_StatusTypeDef MID_I2C_Init(I2C_HandleTypeDef *mI2C)
{
    /* Check the I2C handle allocation */
    if(mI2C == NULL)
    {
        return MID_ERROR;
    }

    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(mI2C->Instance));
    assert_param(IS_I2C_OWN_ADDRESS1(mI2C->Init.OwnAddress1));
    assert_param(IS_I2C_OWN_ADDRESS1_MASK(mI2C->Init.OwnAddress1Masks));
    assert_param(IS_I2C_ADDRESSING_MODE(mI2C->Init.AddressingMode));
    assert_param(IS_I2C_DUAL_ADDRESS(mI2C->Init.DualAddressMode));
    assert_param(IS_I2C_OWN_ADDRESS2(mI2C->Init.OwnAddress2));
    assert_param(IS_I2C_GENERAL_CALL(mI2C->Init.GeneralCallMode));

    if(mI2C->State == MID_I2C_STATE_RESET)
    {
        /* Allocate lock resource and initialize it */
        mI2C->Lock = MID_UnLocked;

        /* Init the low level hardware : GPIO, CLOCK, CORTEX...etc */
        MID_I2C_MspInit(mI2C);
    }

    mI2C->State = MID_I2C_STATE_BUSY;

    /* Disable the selected I2C peripheral */
    __DRV_I2C_DISABLE(mI2C);

    /*---------------------------- I2Cx TIMINGR Configuration ------------------*/
    /* Configure I2Cx: Frequency range */
    /* Bits[31:24] HT */
    /* Bits[23:16] LT */
    /* Bits[12]    Timeout clock source select */
    /* Bits[27:24] Prescale */
    /* Bits[23:20] Divider */
    /* Bits[03:02] CK_I2C0 source select */
    mI2C->Instance->CLK.W = (mI2C->Init.Timing & (I2C_CLK_TMO_CKS_mask_w | I2C_CLK_CK_PSC_mask_w | I2C_CLK_CK_DIV_mask_w | I2C_CLK_CK_SEL_mask_w));
    mI2C->Instance->CR1.W = ((mI2C->Init.Timing >> 16) & (I2C_CR1_HT_mask_w | I2C_CR1_LT_mask_w));

    /*------------------- I2Cx SADR Own Address1 Configuration -----------------*/
    /* Disable Own Address1 before set the Own Address1 configuration */
    mI2C->Instance->CR0.W &= ~I2C_CR0_SADR_EN_mask_w;

    /* Configure I2Cx: Own Address1 */
    mI2C->Instance->SADR.B[0] = (uint8_t)mI2C->Init.OwnAddress1;

#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
    /* Configure I2Cx: Own Address1 Mask */
    mI2C->Instance->MASK.B[0] = (uint8_t)mI2C->Init.OwnAddress1Masks;
#endif

    /*------------------- I2Cx SADR Own Address2 Configuration -----------------*/
    /* Disable Own Address2 before set the Own Address2 configuration */
    mI2C->Instance->CR0.W &= ~I2C_CR0_SADR2_EN_mask_w;

    /* Configure I2Cx: Own Address2 */
    mI2C->Instance->SADR.B[1] = (uint8_t)mI2C->Init.OwnAddress2;

    /*---------------------------- I2Cx CR0 Configuration ----------------------*/
    /* Configure I2Cx: Generalcall, Dual mode and Enable Own Address1 */
    mI2C->Instance->CR0.W |= (mI2C->Init.GeneralCallMode | mI2C->Init.DualAddressMode | I2C_CR0_SADR_EN_mask_w);
    __DRV_I2C_STA_STO_AA_001(mI2C);

    /* Enable the selected I2C peripheral */
    __DRV_I2C_ENABLE(mI2C);

    mI2C->ErrorCode = MID_I2C_ERROR_NONE;
    mI2C->State = MID_I2C_STATE_READY;
    mI2C->Mode = MID_I2C_MODE_NONE;

    return MID_OK;
}

/**
 ******************************************************************************
 * @brief  DeInitialize the I2C peripheral.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @retval MID status
 ******************************************************************************
 */
MID_StatusTypeDef MID_I2C_DeInit(I2C_HandleTypeDef *mI2C)
{
    /* Check the I2C handle allocation */
    if(mI2C == NULL)
    {
        return MID_ERROR;
    }

    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(mI2C->Instance));

    mI2C->State = MID_I2C_STATE_BUSY;

    /* Disable the I2C Peripheral Clock */
    __DRV_I2C_DISABLE(mI2C);

    /* DeInit the low level hardware: GPIO, CLOCK, NVIC */
    MID_I2C_MspDeInit(mI2C);

    mI2C->ErrorCode = MID_I2C_ERROR_NONE;
    mI2C->State = MID_I2C_STATE_RESET;
    mI2C->Mode = MID_I2C_MODE_NONE;

    /* Release Lock */
    __MID_UNLOCK(mI2C);

  return MID_OK;
}

/**
 ******************************************************************************
 * @brief Initialize the I2C MSP(MCU Support Package).
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @retval None
 ******************************************************************************
 */
__weak void MID_I2C_MspInit(I2C_HandleTypeDef *mI2C)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mI2C);

  /* NOTE : This function should not be modified, when the callback is needed,
            the MID_I2C_MspInit could be implemented in the user file
  */
}

/**
 ******************************************************************************
 * @brief DeInitialize the I2C MSP.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @retval None
 ******************************************************************************
 */
__weak void MID_I2C_MspDeInit(I2C_HandleTypeDef *mI2C)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mI2C);

  /* NOTE : This function should not be modified, when the callback is needed,
            the MID_I2C_MspDeInit could be implemented in the user file
  */
}

/**
 * @}
 */

/** @name   I2C_Exported_Functions_Group2 Input and Output operation functions
 *  @brief      Data transfers functions
 *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to manage the I2C data
    transfers.

    (#) There are two modes of transfer:
       (++) Blocking mode : The communication is performed in the polling mode.
            The status of all data processing is returned by the same function
            after finishing transfer.
       (++) No-Blocking mode : The communication is performed using Interrupts.
            These functions return the status of the transfer startup.
            The end of the data processing will be indicated through the
            dedicated I2C IRQ when using Interrupt mode.

    (#) Blocking mode functions are :
        (++) MID_I2C_IsDeviceReady()
        (++) MID_I2C_Master_Transmit()
        (++) MID_I2C_Master_Transmit_RepeatStart()
        (++) MID_I2C_Master_Receive()
        (++) MID_I2C_Slave_Transmit()
        (++) MID_I2C_Slave_Receive()
        (++) MID_I2C_Mem_Write()
        (++) MID_I2C_Mem_Read()

    (#) No-Blocking mode functions with Interrupt are :
        (++) MID_I2C_Master_Transmit_IT()
        (++) MID_I2C_Master_Transmit_RepeatStart_IT()
        (++) MID_I2C_Master_Receive_IT()
        (++) MID_I2C_Slave_Transmit_IT()
        (++) MID_I2C_Slave_Receive_IT()
        (++) MID_I2C_Mem_Write_IT()
        (++) MID_I2C_Mem_Read_IT()

    (#) A set of Transfer Complete Callbacks are provided in non Blocking mode:
        (++) MID_I2C_MasterTxCpltCallback()
        (++) MID_I2C_MasterRxCpltCallback()
        (++) MID_I2C_SlaveTxCpltCallback()
        (++) MID_I2C_SlaveRxCpltCallback()
        (++) MID_I2C_ErrorCallback()
        (++) MID_I2C_AddrCallback()

@endverbatim
 * @{
 */

/**
 ******************************************************************************
 * @brief  Checks if target device is ready for communication.
 * @note   This function is used with Memory devices
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @param  DevAddress: Target device address
 * @param  Trials: Number of trials
 * @param  Timeout: Timeout duration
 * @retval MID status
 ******************************************************************************
 */
MID_StatusTypeDef MID_I2C_IsDeviceReady(I2C_HandleTypeDef *mI2C, uint16_t DevAddress, uint32_t Trials, uint32_t Timeout)
{
    __IO uint32_t tickstart = 0U;
    __IO uint32_t tickTemp = 0;
    __IO uint32_t I2C_Trials = 0U;
    __IO uint8_t lEventTemp;

    if((mI2C->State & (MID_I2C_STATE_READY | MID_I2C_STATE_BUSY)) == MID_I2C_STATE_READY)
    {
        if(__DRV_I2C_GET_FLAG(mI2C, I2C_FLAG_BUSY) != CLR)
        {
            if(__DRV_I2C_GET_FLAG(mI2C, I2C_FLAG_EVENT) != CLR)
            {
                lEventTemp = __DRV_I2C_GET_EVENTCODE(mI2C);
                if((lEventTemp != 0x08) && (lEventTemp != 0x10))
                    return MID_ERROR;
            }
        }

        /* Process Locked */
        __MID_LOCK(mI2C);

        I2C_BUFFMODE_DISABLE(mI2C);

        /* Disable All Interrupt */
        __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_ERR | I2C_IT_BUF | I2C_IT_EVENT); // Disable Interrupt

        /* Clear I2C Flag */
        __DRV_I2C_CLEAR_FLAG(mI2C, (I2C_FLAG_NACK | I2C_FLAG_ALOS | I2C_FLAG_BERR | I2C_FLAG_ROVR | I2C_FLAG_TOVR | I2C_FLAG_STOP | I2C_FLAG_RSTR));

        mI2C->ErrorCode = MID_I2C_ERROR_NONE;
        mI2C->State = MID_I2C_STATE_BUSY_TX;
        mI2C->Mode = MID_I2C_MODE_MASTER_STOP;

        /* Prepare transfer parameters */
        mI2C->DevAddress = DevAddress & 0xFFFE;
        mI2C->pBuffPtr = NULL;
        mI2C->XferSize = 0;
        mI2C->XferCount = 0;
        mI2C->XferISR = NULL;

        /* No need to Check TC flag, with AUTOEND mode the stop is automatically generated */
        /* Wait until STOPF flag is set or a NACK flag is set*/
        tickstart = MID_GetTick();

        do{
            /* Send Bus Start */
            lEventTemp = __DRV_I2C_GET_EVENTCODE(mI2C);
            if((lEventTemp == 0xF8) || (lEventTemp == 0xA0))
                __DRV_I2C_STA_1(mI2C);

            // 08 >> 18 or 20 >> Stop
            __DRV_I2C_WAIT_EVENT_FLAG(mI2C);    // 0x08
            I2C_BytemodeMasterEventHandle(mI2C);

            __DRV_I2C_WAIT_EVENT_FLAG(mI2C);    // 0x18 or 0x20
            lEventTemp = __DRV_I2C_GET_EVENTCODE(mI2C);

            if(__DRV_I2C_GET_EVENTCODE(mI2C) == 0x18)
                I2C_Trials = Trials;    // 0x18

            I2C_BytemodeMasterEventHandle(mI2C);

            I2C_Trials ++;
            tickTemp = MID_GetTick() - tickstart;
        }while((I2C_Trials < Trials) && (tickTemp < Timeout));

        if(lEventTemp == 0x18)
        {
            mI2C->ErrorCode = MID_I2C_ERROR_NONE;
            mI2C->State = MID_I2C_STATE_READY;

            /* Process Unlocked */
            __MID_UNLOCK(mI2C);
            return MID_OK;
        }

        mI2C->ErrorCode |= MID_I2C_ERROR_NACKF;
        mI2C->State = MID_I2C_STATE_READY | MID_I2C_STATE_ERROR;

        if(tickTemp < Timeout)
        {
            /* Process Unlocked */
            __MID_UNLOCK(mI2C);
            return MID_ERROR;
        }
        else
        {
            mI2C->ErrorCode |= MID_I2C_ERROR_TIMEOUT;
            /* Process Unlocked */
            __MID_UNLOCK(mI2C);
            return MID_TIMEOUT;
        }
    }
    else
    {
        return MID_BUSY;
    }
}

/**
 ******************************************************************************
 * @brief  Transmits in master mode an amount of data in blocking mode.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @param  DevAddress: Target device address
 * @param  pData: Pointer to data buffer
 * @param  Size: Amount of data to be sent
 * @param  Timeout: Timeout duration
 * @retval MID status
 ******************************************************************************
 */
MID_StatusTypeDef MID_I2C_Master_Transmit(I2C_HandleTypeDef *mI2C, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint32_t tickstart = 0U;
    __IO uint8_t lEventTemp;

    if((mI2C->State & (MID_I2C_STATE_READY | MID_I2C_STATE_BUSY)) == MID_I2C_STATE_READY)
    {
        if(__DRV_I2C_GET_FLAG(mI2C, I2C_FLAG_BUSY) != CLR)
        {
            if(__DRV_I2C_GET_FLAG(mI2C, I2C_FLAG_EVENT) != CLR)
            {
                lEventTemp = __DRV_I2C_GET_EVENTCODE(mI2C);
                if((lEventTemp != 0x08) && (lEventTemp != 0x10))
                {
                    return MID_ERROR;
                }
            }
        }

        /* Process Locked */
        __MID_LOCK(mI2C);

        I2C_BUFFMODE_DISABLE(mI2C);

        /* Disable All Interrupt */
        __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_ERR | I2C_IT_BUF | I2C_IT_EVENT); // Disable Interrupt

        /* Clear I2C Flag */
        __DRV_I2C_CLEAR_FLAG(mI2C, (I2C_FLAG_NACK | I2C_FLAG_ALOS | I2C_FLAG_BERR | I2C_FLAG_ROVR | I2C_FLAG_TOVR | I2C_FLAG_STOP | I2C_FLAG_RSTR));

        mI2C->ErrorCode = MID_I2C_ERROR_NONE;
        mI2C->State = MID_I2C_STATE_BUSY_TX;
        mI2C->Mode = MID_I2C_MODE_MASTER_STOP;

        /* Prepare transfer parameters */
        mI2C->DevAddress = DevAddress & 0xFFFE;
        mI2C->pBuffPtr = pData;
        mI2C->XferSize = Size;
        mI2C->XferCount = 0;
        mI2C->XferISR = NULL;

        /* Init tickstart for timeout management */
        tickstart = MID_GetTick();

        /* Send Bus Start */
        lEventTemp = __DRV_I2C_GET_EVENTCODE(mI2C);

        if((lEventTemp == 0xF8) || (lEventTemp == 0xA0))
        {
            __DRV_I2C_STA_1(mI2C);
        }

        do
        {
            I2C_BytemodeMasterEventHandle(mI2C);
            if(I2C_WaitOnEVENTFlagUntilTimeout(mI2C, Timeout, tickstart) != MID_OK)
            {
                /* Process Unlocked */
                __MID_UNLOCK(mI2C);
                return MID_ERROR;
            }
            I2C_BytemodeMasterEventHandle(mI2C);
        }while((mI2C->State & MID_I2C_STATE_BUSY) != 0);

        mI2C->State = MID_I2C_STATE_READY;
        mI2C->Mode = MID_I2C_MODE_NONE;

        /* Process Unlocked */
        __MID_UNLOCK(mI2C);

        if(mI2C->ErrorCode != MID_I2C_ERROR_NONE)
        {
            return MID_ERROR;
        }
        else
        {
            return MID_OK;
        }
    }
    else
    {
        return MID_BUSY;
    }
}

/**
 ******************************************************************************
 * @brief  Transmits in master mode an amount of data in blocking mode.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @param  DevAddress: Target device address
 * @param  pData: Pointer to data buffer
 * @param  Size: Amount of data to be sent
 * @param  Timeout: Timeout duration
 * @retval MID status
 ******************************************************************************
 */
MID_StatusTypeDef MID_I2C_Master_Transmit_RepeatStart(I2C_HandleTypeDef *mI2C, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint32_t tickstart = 0U;
    __IO uint8_t lEventTemp;

    if((mI2C->State & (MID_I2C_STATE_READY | MID_I2C_STATE_BUSY)) == MID_I2C_STATE_READY)
    {
        if(__DRV_I2C_GET_FLAG(mI2C, I2C_FLAG_BUSY) != CLR)
        {
            if(__DRV_I2C_GET_FLAG(mI2C, I2C_FLAG_EVENT) != CLR)
            {
                lEventTemp = __DRV_I2C_GET_EVENTCODE(mI2C);
                if((lEventTemp != 0x08) && (lEventTemp != 0x10))
                    return MID_ERROR;
            }
        }

        /* Process Locked */
        __MID_LOCK(mI2C);

        I2C_BUFFMODE_DISABLE(mI2C);

        /* Disable All Interrupt */
        __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_ERR | I2C_IT_BUF | I2C_IT_EVENT); // Disable Interrupt

        /* Clear I2C Flag */
        __DRV_I2C_CLEAR_FLAG(mI2C, (I2C_FLAG_NACK | I2C_FLAG_ALOS | I2C_FLAG_BERR | I2C_FLAG_ROVR | I2C_FLAG_TOVR | I2C_FLAG_STOP | I2C_FLAG_RSTR));

        mI2C->ErrorCode = MID_I2C_ERROR_NONE;
        mI2C->State = MID_I2C_STATE_BUSY_TX;
        mI2C->Mode = MID_I2C_MODE_MASTER_RREPEATSTART;

        /* Prepare transfer parameters */
        mI2C->DevAddress = DevAddress & 0xFFFE;
        mI2C->pBuffPtr = pData;
        mI2C->XferSize = Size;
        mI2C->XferCount = 0;
        mI2C->XferISR = NULL;

        /* Init tickstart for timeout management */
        tickstart = MID_GetTick();

        /* Send Bus Start */
        lEventTemp = __DRV_I2C_GET_EVENTCODE(mI2C);
        if((lEventTemp == 0xF8) || (lEventTemp == 0xA0))
            __DRV_I2C_STA_1(mI2C);

        do{
            if(I2C_WaitOnEVENTFlagUntilTimeout(mI2C, Timeout, tickstart) != MID_OK)
            {
                /* Process Unlocked */
                __MID_UNLOCK(mI2C);
                return MID_ERROR;
            }
            I2C_BytemodeMasterEventHandle(mI2C);
        }while((mI2C->State & MID_I2C_STATE_BUSY) != 0);

        mI2C->State = MID_I2C_STATE_READY;
        mI2C->Mode = MID_I2C_MODE_NONE;

        /* Process Unlocked */
        __MID_UNLOCK(mI2C);

        if(mI2C->ErrorCode != MID_I2C_ERROR_NONE)
            return MID_ERROR;
        else
            return MID_OK;
    }
    else
    {
        return MID_BUSY;
    }
}

/**
 ******************************************************************************
 * @brief  Receives in master mode an amount of data in blocking mode.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @param  DevAddress: Target device address
 * @param  pData: Pointer to data buffer
 * @param  Size: Amount of data to be sent
 * @param  Timeout: Timeout duration
 * @retval MID status
 ******************************************************************************
 */
MID_StatusTypeDef MID_I2C_Master_Receive(I2C_HandleTypeDef *mI2C, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint32_t tickstart = 0U;
    __IO uint8_t lEventTemp;

    if((mI2C->State & (MID_I2C_STATE_READY | MID_I2C_STATE_BUSY)) == MID_I2C_STATE_READY)
    {
        if(__DRV_I2C_GET_FLAG(mI2C, I2C_FLAG_BUSY) != CLR)
        {
            if(__DRV_I2C_GET_FLAG(mI2C, I2C_FLAG_EVENT) != CLR)
            {
                lEventTemp = __DRV_I2C_GET_EVENTCODE(mI2C);
                if((lEventTemp != 0x08) && (lEventTemp != 0x10))
                    return MID_ERROR;
            }
        }

        /* Process Locked */
        __MID_LOCK(mI2C);

        I2C_BUFFMODE_DISABLE(mI2C);

        /* Disable All Interrupt */
        __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_ERR | I2C_IT_BUF | I2C_IT_EVENT); // Disable Interrupt

        /* Clear I2C Flag */
        __DRV_I2C_CLEAR_FLAG(mI2C, (I2C_FLAG_NACK | I2C_FLAG_ALOS | I2C_FLAG_BERR | I2C_FLAG_ROVR | I2C_FLAG_TOVR | I2C_FLAG_STOP | I2C_FLAG_RSTR));

        mI2C->ErrorCode = MID_I2C_ERROR_NONE;
        mI2C->State = MID_I2C_STATE_BUSY_RX;
        mI2C->Mode = MID_I2C_MODE_MASTER_STOP;

        /* Prepare transfer parameters */
        mI2C->DevAddress = DevAddress | 0x0001;
        mI2C->pBuffPtr = pData;
        mI2C->XferSize = Size;
        mI2C->XferCount = 0;
        mI2C->XferISR = NULL;

        /* Init tickstart for timeout management */
        tickstart = MID_GetTick();

        /* Send Bus Start */
        lEventTemp = __DRV_I2C_GET_EVENTCODE(mI2C);
        if((lEventTemp == 0xF8) || (lEventTemp == 0xA0))
            __DRV_I2C_STA_1(mI2C);

        do{
            if(I2C_WaitOnEVENTFlagUntilTimeout(mI2C, Timeout, tickstart) != MID_OK)
            {
                /* Process Unlocked */
                __MID_UNLOCK(mI2C);
                return MID_ERROR;
            }
            I2C_BytemodeMasterEventHandle(mI2C);
        }while((mI2C->State & MID_I2C_STATE_BUSY) != 0);

        mI2C->State = MID_I2C_STATE_READY;
        mI2C->Mode = MID_I2C_MODE_NONE;

        /* Process Unlocked */
        __MID_UNLOCK(mI2C);

        if(mI2C->ErrorCode != MID_I2C_ERROR_NONE)
            return MID_ERROR;
        else
            return MID_OK;
    }
    else
    {
        return MID_BUSY;
    }
}

/**
 ******************************************************************************
 * @brief  Transmits in slave mode an amount of data in blocking mode.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @param  pData: Pointer to data buffer
 * @param  Size: Amount of data to be sent
 * @param  Timeout: Timeout duration
 * @retval MID status
 ******************************************************************************
 */
MID_StatusTypeDef MID_I2C_Slave_Transmit(I2C_HandleTypeDef *mI2C, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint32_t tickstart = 0U;
////    uint8_t lEventCode;

    if((mI2C->State & (MID_I2C_STATE_READY | MID_I2C_STATE_BUSY)) == MID_I2C_STATE_READY)
    {
        if((pData == NULL) || (Size == 0U))
        {
            return  MID_ERROR;
        }

        /* Process Locked */
        __MID_LOCK(mI2C);

        /* Disable All Interrupt */
        __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_ERR | I2C_IT_BUF | I2C_IT_EVENT); // Disable Interrupt

        /* Clear I2C Flag */
        __DRV_I2C_CLEAR_FLAG(mI2C, (I2C_FLAG_NACK | I2C_FLAG_ALOS | I2C_FLAG_BERR | I2C_FLAG_ROVR | I2C_FLAG_TOVR | I2C_FLAG_STOP | I2C_FLAG_RSTR));

        mI2C->ErrorCode = MID_I2C_ERROR_NONE;
        mI2C->State = MID_I2C_STATE_BUSY_TX;
        mI2C->Mode = MID_I2C_MODE_SLAVE;

        /* Prepare transfer parameters */
        mI2C->DevAddress = 0;
        mI2C->pBuffPtr = pData;
        mI2C->XferSize = Size;
        mI2C->XferCount = 0;
        mI2C->XferISR = NULL;

        /* Init tickstart for timeout management*/
        tickstart = MID_GetTick();

        /* Enable Address Acknowledge */
        mI2C->Instance->CR0.W |= (I2C_CR0_SADR_EN_mask_w | mI2C->Init.DualAddressMode | mI2C->Init.GeneralCallMode);
        __DRV_I2C_STA_STO_AA_001(mI2C);

////        /* Wait until match own Address */
////        do{
////            if(I2C_WaitOnEVENTFlagUntilTimeout(mI2C, Timeout, tickstart) != MID_OK)
////            {
////                /* Process Unlocked */
////                __MID_UNLOCK(mI2C);
////                return MID_ERROR;
////            }
////            lEventCode = __DRV_I2C_GET_EVENTCODE(mI2C);
////        }while((lEventCode != 0xA8) && (lEventCode != 0xB0));
////        I2C_BytemodeSlaveEventHandle(mI2C);

        /* Wait until Data Transfor to Stop */
        do{
            if(I2C_WaitOnEVENTFlagUntilTimeout(mI2C, Timeout, tickstart) != MID_OK)
            {
                /* Process Unlocked */
                __MID_UNLOCK(mI2C);
                return MID_TIMEOUT;
            }
            I2C_BytemodeSlaveEventHandle(mI2C);
        }while((mI2C->State & MID_I2C_STATE_BUSY) != 0);

        /* Disable Address Acknowledge */
        mI2C->State = MID_I2C_STATE_READY;
        mI2C->Mode  = MID_I2C_MODE_NONE;

        /* Process Unlocked */
        __MID_UNLOCK(mI2C);

        if(mI2C->ErrorCode != MID_I2C_ERROR_NONE)
        {
            return MID_ERROR;
        }
        else
        {
            return MID_OK;
        }
    }
    else
    {
        return MID_BUSY;
    }
}

/**
 ******************************************************************************
 * @brief  Receive in slave mode an amount of data in blocking mode
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @param  pData: Pointer to data buffer
 * @param  Size: Amount of data to be sent
 * @param  Timeout: Timeout duration
 * @retval MID status
 ******************************************************************************
 */
MID_StatusTypeDef MID_I2C_Slave_Receive(I2C_HandleTypeDef *mI2C, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint32_t tickstart = 0U;
    uint8_t lEventCode;

    if((mI2C->State & (MID_I2C_STATE_READY | MID_I2C_STATE_BUSY)) == MID_I2C_STATE_READY)
    {
        if((pData == NULL) || (Size == 0U))
        {
            return  MID_ERROR;
        }
        /* Process Locked */
        __MID_LOCK(mI2C);

        /* Disable All Interrupt */
        __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_ERR | I2C_IT_BUF | I2C_IT_EVENT); // Disable Interrupt

        /* Clear I2C Flag */
        __DRV_I2C_CLEAR_FLAG(mI2C, (I2C_FLAG_NACK | I2C_FLAG_ALOS | I2C_FLAG_BERR | I2C_FLAG_ROVR | I2C_FLAG_TOVR | I2C_FLAG_STOP | I2C_FLAG_RSTR));

        mI2C->ErrorCode = MID_I2C_ERROR_NONE;
        mI2C->State = MID_I2C_STATE_BUSY_RX;
        mI2C->Mode = MID_I2C_MODE_SLAVE;

        /* Prepare transfer parameters */
        mI2C->DevAddress = 0;
        mI2C->pBuffPtr = pData;
        mI2C->XferSize = Size;
        mI2C->XferCount = 0;
        mI2C->XferISR = NULL;

        /* Init tickstart for timeout management*/
        tickstart = MID_GetTick();

        /* Enable Address Acknowledge */
        mI2C->Instance->CR0.W |= (I2C_CR0_SADR_EN_mask_w | mI2C->Init.DualAddressMode | mI2C->Init.GeneralCallMode);
        __DRV_I2C_STA_STO_AA_001(mI2C);

        /* Wait until match own Address */
        do{
          
            I2C_BytemodeSlaveEventHandle(mI2C);
            if(I2C_WaitOnEVENTFlagUntilTimeout(mI2C, Timeout, tickstart) != MID_OK)
            {
                /* Process Unlocked */
                __MID_UNLOCK(mI2C);
                return MID_ERROR;
            }
            lEventCode = __DRV_I2C_GET_EVENTCODE(mI2C);
        }while((lEventCode != 0x60) && (lEventCode != 0x68) && (lEventCode != 0x70) && (lEventCode != 0x78));
        I2C_BytemodeSlaveEventHandle(mI2C);

        /* Wait until Data Transfor to Stop */
        do{
            if(I2C_WaitOnEVENTFlagUntilTimeout(mI2C, Timeout, tickstart) != MID_OK)
            {
                /* Process Unlocked */
                __MID_UNLOCK(mI2C);
                return MID_TIMEOUT;
            }
            I2C_BytemodeSlaveEventHandle(mI2C);
        }while((mI2C->State & MID_I2C_STATE_BUSY) != 0);

        // /* Disable Address Acknowledge */
        // mI2C->Instance->CR2 |= I2C_CR2_NACK;

        mI2C->State = MID_I2C_STATE_READY;
        mI2C->Mode = MID_I2C_MODE_NONE;

        /* Process Unlocked */
        __MID_UNLOCK(mI2C);

        if(mI2C->ErrorCode != MID_I2C_ERROR_NONE)
        {
            return MID_ERROR;
        }
        else
        {
            return MID_OK;
        }
    }
    else
    {
        return MID_BUSY;
    }
}

/**
 ******************************************************************************
 * @brief  Transmit in master mode an amount of data in non-blocking mode with Interrupt
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @param  DevAddress: Target device address
 * @param  pData: Pointer to data buffer
 * @param  Size: Amount of data to be sent
 * @retval MID status
 ******************************************************************************
 */
MID_StatusTypeDef MID_I2C_Master_Transmit_IT(I2C_HandleTypeDef *mI2C, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
    __IO uint8_t lEventTemp;

    if((mI2C->State & (MID_I2C_STATE_READY | MID_I2C_STATE_BUSY)) == MID_I2C_STATE_READY)
    {
        if(__DRV_I2C_GET_FLAG(mI2C, I2C_FLAG_BUSY) != CLR)
        {
            if(__DRV_I2C_GET_FLAG(mI2C, I2C_FLAG_EVENT) != CLR)
            {
                lEventTemp = __DRV_I2C_GET_EVENTCODE(mI2C);
                if((lEventTemp != 0x08) && (lEventTemp != 0x10))
                    return MID_ERROR;
            }
        }

        /* Process Locked */
        __MID_LOCK(mI2C);

        I2C_BUFFMODE_DISABLE(mI2C);

        /* Disable All Interrupt */
        __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_ERR | I2C_IT_BUF | I2C_IT_EVENT); // Disable Interrupt

        /* Clear I2C Flag */
        __DRV_I2C_CLEAR_FLAG(mI2C, (I2C_FLAG_NACK | I2C_FLAG_ALOS | I2C_FLAG_BERR | I2C_FLAG_ROVR | I2C_FLAG_TOVR | I2C_FLAG_STOP | I2C_FLAG_RSTR));

        mI2C->ErrorCode = MID_I2C_ERROR_NONE;
        mI2C->State = MID_I2C_STATE_BUSY_TX;
        mI2C->Mode = MID_I2C_MODE_MASTER_STOP;

        /* Prepare transfer parameters */
        mI2C->DevAddress = DevAddress & 0xFFFE;
        mI2C->pBuffPtr = pData;
        mI2C->XferSize = Size;
        mI2C->XferCount = 0;
        mI2C->XferISR = I2C_Master_ISR_IT;

        /* Send Bus Start */
        lEventTemp = __DRV_I2C_GET_EVENTCODE(mI2C);
        if((lEventTemp == 0xF8) || (lEventTemp == 0xA0))
            __DRV_I2C_STA_1(mI2C);

        /* Process Unlocked */
        __MID_UNLOCK(mI2C);

        /* Note : The I2C interrupts must be enabled after unlocking current process
                  to avoid the risk of I2C interrupt handle execution before current
                  process unlock */

        /* Enable IEA, EVENT, interrupt */
        /* possible to enable all of these */
        /* I2C_IT_IEA | I2C_IT_EVENT */
        __DRV_I2C_ENABLE_IT(mI2C, (I2C_IT_IEA | I2C_IT_EVENT| I2C_IT_BUF)); // Enable Interrupt

        return MID_OK;
    }
    else
    {
        return MID_BUSY;
    }
}

/**
 ******************************************************************************
 * @brief  Transmit in master mode an amount of data in non-blocking mode with Interrupt
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @param  DevAddress: Target device address
 * @param  pData: Pointer to data buffer
 * @param  Size: Amount of data to be sent
 * @retval MID status
 ******************************************************************************
 */
MID_StatusTypeDef MID_I2C_Master_Transmit_RepeatStart_IT(I2C_HandleTypeDef *mI2C, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
    __IO uint8_t lEventTemp;

    if((mI2C->State & (MID_I2C_STATE_READY | MID_I2C_STATE_BUSY)) == MID_I2C_STATE_READY)
    {
        if(__DRV_I2C_GET_FLAG(mI2C, I2C_FLAG_BUSY) != CLR)
        {
            if(__DRV_I2C_GET_FLAG(mI2C, I2C_FLAG_EVENT) != CLR)
            {
                lEventTemp = __DRV_I2C_GET_EVENTCODE(mI2C);
                if((lEventTemp != 0x08) && (lEventTemp != 0x10))
                    return MID_ERROR;
            }
        }

        /* Process Locked */
        __MID_LOCK(mI2C);

        I2C_BUFFMODE_DISABLE(mI2C);

        /* Disable All Interrupt */
        __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_ERR | I2C_IT_BUF | I2C_IT_EVENT); // Disable Interrupt

        /* Clear I2C Flag */
        __DRV_I2C_CLEAR_FLAG(mI2C, (I2C_FLAG_NACK | I2C_FLAG_ALOS | I2C_FLAG_BERR | I2C_FLAG_ROVR | I2C_FLAG_TOVR | I2C_FLAG_STOP | I2C_FLAG_RSTR));

        mI2C->ErrorCode = MID_I2C_ERROR_NONE;
        mI2C->State = MID_I2C_STATE_BUSY_TX;
        mI2C->Mode = MID_I2C_MODE_MASTER_RREPEATSTART;

        /* Prepare transfer parameters */
        mI2C->DevAddress = DevAddress & 0xFFFE;
        mI2C->pBuffPtr = pData;
        mI2C->XferSize = Size;
        mI2C->XferCount = 0;
        mI2C->XferISR = I2C_Master_ISR_IT;

        /* Send Bus Start */
        lEventTemp = __DRV_I2C_GET_EVENTCODE(mI2C);
        if((lEventTemp == 0xF8) || (lEventTemp == 0xA0))
            __DRV_I2C_STA_1(mI2C);

        /* Process Unlocked */
        __MID_UNLOCK(mI2C);

        /* Note : The I2C interrupts must be enabled after unlocking current process
                  to avoid the risk of I2C interrupt handle execution before current
                  process unlock */

        /* Enable IEA, EVENT, interrupt */
        /* possible to enable all of these */
        /* I2C_IT_IEA | I2C_IT_EVENT */
        __DRV_I2C_ENABLE_IT(mI2C, (I2C_IT_IEA | I2C_IT_EVENT| I2C_IT_BUF)); // Enable Interrupt

        return MID_OK;
    }
    else
    {
        return MID_BUSY;
    }
}

/**
 ******************************************************************************
 * @brief  Receive in master mode an amount of data in non-blocking mode with Interrupt
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @param  DevAddress: Target device address
 * @param  pData: Pointer to data buffer
 * @param  Size: Amount of data to be sent
 * @retval MID status
 ******************************************************************************
 */
MID_StatusTypeDef MID_I2C_Master_Receive_IT(I2C_HandleTypeDef *mI2C, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
    __IO uint8_t lEventTemp;

    if((mI2C->State & (MID_I2C_STATE_READY | MID_I2C_STATE_BUSY)) == MID_I2C_STATE_READY)
    {
        if(__DRV_I2C_GET_FLAG(mI2C, I2C_FLAG_BUSY) != CLR)
        {
            if(__DRV_I2C_GET_FLAG(mI2C, I2C_FLAG_EVENT) != CLR)
            {
                lEventTemp = __DRV_I2C_GET_EVENTCODE(mI2C);
                if((lEventTemp != 0x08) && (lEventTemp != 0x10))
                    return MID_ERROR;
            }
        }

        if((pData == NULL) || (Size == 0U))
        {
            return  MID_ERROR;
        }

        /* Process Locked */
        __MID_LOCK(mI2C);

        I2C_BUFFMODE_DISABLE(mI2C);

        /* Disable All Interrupt */
        __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_ERR | I2C_IT_BUF | I2C_IT_EVENT); // Disable Interrupt

        /* Clear I2C Flag */
        __DRV_I2C_CLEAR_FLAG(mI2C, (I2C_FLAG_NACK | I2C_FLAG_ALOS | I2C_FLAG_BERR | I2C_FLAG_ROVR | I2C_FLAG_TOVR | I2C_FLAG_STOP | I2C_FLAG_RSTR));

        mI2C->ErrorCode = MID_I2C_ERROR_NONE;
        mI2C->State = MID_I2C_STATE_BUSY_RX;
        mI2C->Mode = MID_I2C_MODE_MASTER_STOP;

        /* Prepare transfer parameters */
        mI2C->DevAddress = DevAddress | 0x0001;
        mI2C->pBuffPtr = pData;
        mI2C->XferSize = Size;
        mI2C->XferCount = 0;
        mI2C->XferISR = I2C_Master_ISR_IT;

        /* Send Bus Start */
        lEventTemp = __DRV_I2C_GET_EVENTCODE(mI2C);
        if((lEventTemp == 0xF8) || (lEventTemp == 0xA0))
            __DRV_I2C_STA_1(mI2C);

        /* Process Unlocked */
        __MID_UNLOCK(mI2C);

        /* Note : The I2C interrupts must be enabled after unlocking current process
                  to avoid the risk of I2C interrupt handle execution before current
                  process unlock */

        /* Enable IEA, EVENT, interrupt */
        /* possible to enable all of these */
        /* I2C_IT_IEA | I2C_IT_EVENT */
        __DRV_I2C_ENABLE_IT(mI2C, (I2C_IT_IEA | I2C_IT_EVENT| I2C_IT_BUF)); // Enable Interrupt

        return MID_OK;
    }
    else
    {
        return MID_BUSY;
    }
}

/**
 ******************************************************************************
 * @brief  Transmit in slave mode an amount of data in non-blocking mode with Interrupt
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @param  pData: Pointer to data buffer
 * @param  Size: Amount of data to be sent
 * @retval MID status
 ******************************************************************************
 */
MID_StatusTypeDef MID_I2C_Slave_Transmit_IT(I2C_HandleTypeDef *mI2C, uint8_t *pData, uint16_t Size)
{
    if((mI2C->State & (MID_I2C_STATE_READY | MID_I2C_STATE_BUSY)) == MID_I2C_STATE_READY)
    {
        if((pData == NULL) || (Size == 0U))
        {
            return  MID_ERROR;
        }

        /* Process Locked */
        __MID_LOCK(mI2C);

        /* Disable All Interrupt */
        __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_ERR | I2C_IT_BUF | I2C_IT_EVENT); // Disable Interrupt

        /* Clear I2C Flag */
        __DRV_I2C_CLEAR_FLAG(mI2C, (I2C_FLAG_NACK | I2C_FLAG_ALOS | I2C_FLAG_BERR | I2C_FLAG_ROVR | I2C_FLAG_TOVR | I2C_FLAG_STOP | I2C_FLAG_RSTR));

        mI2C->ErrorCode = MID_I2C_ERROR_NONE;

        mI2C->State = MID_I2C_STATE_BUSY_TX;
        mI2C->Mode = MID_I2C_MODE_SLAVE;

        /* Prepare transfer parameters */
        mI2C->DevAddress = 0;
        mI2C->pBuffPtr = pData;
        mI2C->XferSize = Size;
        mI2C->XferCount = 0;
        mI2C->XferISR = I2C_Slave_ISR_IT;

        /* Enable Address Acknowledge */
        mI2C->Instance->CR0.W |= (I2C_CR0_SADR_EN_mask_w | mI2C->Init.DualAddressMode | mI2C->Init.GeneralCallMode);
        __DRV_I2C_STA_STO_AA_001(mI2C);

        /* Process Unlocked */
        __MID_UNLOCK(mI2C);

        /* Note : The I2C interrupts must be enabled after unlocking current process
                  to avoid the risk of I2C interrupt handle execution before current
                  process unlock */

        /* Enable IEA, EVENT, interrupt */
        /* possible to enable all of these */
        /* I2C_IT_IEA | I2C_IT_EVENT */
        __DRV_I2C_ENABLE_IT(mI2C, (I2C_IT_IEA | I2C_IT_EVENT| I2C_IT_BUF)); // Enable Interrupt

        return MID_OK;
    }
    else
    {
        return MID_BUSY;
    }
}

/**
 ******************************************************************************
 * @brief  Receive in slave mode an amount of data in non-blocking mode with Interrupt
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @param  pData: Pointer to data buffer
 * @param  Size: Amount of data to be sent
 * @retval MID status
 ******************************************************************************
 */
MID_StatusTypeDef MID_I2C_Slave_Receive_IT(I2C_HandleTypeDef *mI2C, uint8_t *pData, uint16_t Size)
{
    if((mI2C->State & (MID_I2C_STATE_READY | MID_I2C_STATE_BUSY)) == MID_I2C_STATE_READY)
    {
        if((pData == NULL) || (Size == 0U))
        {
            return  MID_ERROR;
        }

        /* Process Locked */
        __MID_LOCK(mI2C);

        /* Disable All Interrupt */
        __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_ERR | I2C_IT_BUF | I2C_IT_EVENT); // Disable Interrupt

        /* Clear I2C Flag */
        __DRV_I2C_CLEAR_FLAG(mI2C, (I2C_FLAG_NACK | I2C_FLAG_ALOS | I2C_FLAG_BERR | I2C_FLAG_ROVR | I2C_FLAG_TOVR | I2C_FLAG_STOP | I2C_FLAG_RSTR));

        mI2C->ErrorCode = MID_I2C_ERROR_NONE;
        mI2C->State = MID_I2C_STATE_BUSY_RX;
        mI2C->Mode = MID_I2C_MODE_SLAVE;

        /* Prepare transfer parameters */
        mI2C->DevAddress = 0;
        mI2C->pBuffPtr = pData;
        mI2C->XferSize = Size;
        mI2C->XferCount = 0;
        mI2C->XferISR = I2C_Slave_ISR_IT;

        /* Enable Address Acknowledge */
        mI2C->Instance->CR0.W |= (I2C_CR0_SADR_EN_mask_w | mI2C->Init.DualAddressMode | mI2C->Init.GeneralCallMode);
        __DRV_I2C_STA_STO_AA_001(mI2C);

        /* Process Unlocked */
        __MID_UNLOCK(mI2C);

        /* Note : The I2C interrupts must be enabled after unlocking current process
                  to avoid the risk of I2C interrupt handle execution before current
                  process unlock */

        /* Enable IEA, EVENT, interrupt */
        /* possible to enable all of these */
        /* I2C_IT_IEA | I2C_IT_EVENT */
        __DRV_I2C_ENABLE_IT(mI2C, (I2C_IT_IEA | I2C_IT_EVENT| I2C_IT_BUF)); // Enable Interrupt

        return MID_OK;
    }
    else
    {
        return MID_BUSY;
    }
}








/**
 ******************************************************************************
 * @brief  Write an amount of data in blocking mode to a specific memory address
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @param  DevAddress: Target device address
 * @param  MemAddress: Internal memory address
 * @param  MemAddSize: Size of internal memory address
 * @param  pData: Pointer to data buffer
 * @param  Size: Amount of data to be sent
 * @param  Timeout: Timeout duration
 * @retval MID status
 ******************************************************************************
 */
MID_StatusTypeDef MID_I2C_Mem_Write(I2C_HandleTypeDef *mI2C, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint32_t tickstart = 0U;
    __IO uint8_t lEventTemp;
    union{
        uint8_t B[2];
        uint16_t H;
    }lMemAddress;

    /* Check the parameters */
    assert_param(IS_I2C_MEMADD_SIZE(MemAddSize));

    if((mI2C->State & (MID_I2C_STATE_READY | MID_I2C_STATE_BUSY)) == MID_I2C_STATE_READY)
    {
        if(__DRV_I2C_GET_FLAG(mI2C, I2C_FLAG_BUSY) != CLR)
        {
            if(__DRV_I2C_GET_FLAG(mI2C, I2C_FLAG_EVENT) != CLR)
            {
                lEventTemp = __DRV_I2C_GET_EVENTCODE(mI2C);
                if((lEventTemp != 0x08) && (lEventTemp != 0x10))
                    return MID_ERROR;
            }
        }

        /* Process Locked */
        __MID_LOCK(mI2C);

        I2C_BUFFMODE_DISABLE(mI2C);

        if(MemAddSize == I2C_MEMADD_SIZE_8BIT)
        {
            lMemAddress.H = MemAddress;
        }
        else
        {
            lMemAddress.B[0] = (uint8_t)(MemAddress >> 8);
            lMemAddress.B[1] = (uint8_t)MemAddress; 
        }

        /* Disable All Interrupt */
        __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_ERR | I2C_IT_BUF | I2C_IT_EVENT); // Disable Interrupt

        /* Clear I2C Flag */
        __DRV_I2C_CLEAR_FLAG(mI2C, (I2C_FLAG_NACK | I2C_FLAG_ALOS | I2C_FLAG_BERR | I2C_FLAG_ROVR | I2C_FLAG_TOVR | I2C_FLAG_STOP | I2C_FLAG_RSTR));

        mI2C->ErrorCode = MID_I2C_ERROR_NONE;
        mI2C->State = MID_I2C_STATE_BUSY_TX;
        mI2C->Mode = MID_I2C_MODE_MASTER_NONE;

        /* Prepare transfer parameters */
        mI2C->DevAddress = DevAddress & 0xFFFE;
        mI2C->pBuffPtr = (uint8_t *)(&lMemAddress);
        mI2C->XferSize = MemAddSize;
        mI2C->XferCount = 0;
        mI2C->XferISR = NULL;

        /* Init tickstart for timeout management*/
        tickstart = MID_GetTick();

        /* Send Bus Start */
        lEventTemp = __DRV_I2C_GET_EVENTCODE(mI2C);
        if((lEventTemp == 0xF8) || (lEventTemp == 0xA0))
            __DRV_I2C_STA_1(mI2C);

        do{
            if(I2C_WaitOnEVENTFlagUntilTimeout(mI2C, Timeout, tickstart) != MID_OK)
            {
                /* Process Unlocked */
                __MID_UNLOCK(mI2C);
                return MID_ERROR;
            }
            I2C_BytemodeMasterEventHandle(mI2C);
        }while((mI2C->State & MID_I2C_STATE_BUSY) != 0);

        if(mI2C->ErrorCode != MID_I2C_ERROR_NONE)
        {
            /* Process Unlocked */
            __MID_UNLOCK(mI2C);
            return MID_ERROR;
        }

        /* Clear I2C Flag */
        __DRV_I2C_CLEAR_FLAG(mI2C, (I2C_FLAG_NACK | I2C_FLAG_ALOS | I2C_FLAG_BERR | I2C_FLAG_ROVR | I2C_FLAG_TOVR | I2C_FLAG_STOP | I2C_FLAG_RSTR));

        // mI2C->ErrorCode = MID_I2C_ERROR_NONE;
        mI2C->State = MID_I2C_STATE_BUSY_TX;
        mI2C->Mode = MID_I2C_MODE_MASTER_STOP;

        /* Prepare transfer parameters */
        mI2C->pBuffPtr = pData;
        mI2C->XferSize = Size;
        mI2C->XferCount = 0;
        mI2C->XferISR = NULL;

        do{
            if(I2C_WaitOnEVENTFlagUntilTimeout(mI2C, Timeout, tickstart) != MID_OK)
            {
                /* Process Unlocked */
                __MID_UNLOCK(mI2C);
                return MID_ERROR;
            }
            I2C_BytemodeMasterEventHandle(mI2C);
        }while((mI2C->State & MID_I2C_STATE_BUSY) != 0);

        mI2C->State = MID_I2C_STATE_READY;
        mI2C->Mode  = MID_I2C_MODE_NONE;

        /* Process Unlocked */
        __MID_UNLOCK(mI2C);

        if(mI2C->ErrorCode != MID_I2C_ERROR_NONE)
            return MID_ERROR;
        else
            return MID_OK;
    }
    else
    {
        return MID_BUSY;
    }
}

/**
 ******************************************************************************
 * @brief  Read an amount of data in blocking mode from a specific memory address
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @param  DevAddress: Target device address
 * @param  MemAddress: Internal memory address
 * @param  MemAddSize: Size of internal memory address
 * @param  pData: Pointer to data buffer
 * @param  Size: Amount of data to be sent
 * @param  Timeout: Timeout duration
 * @retval MID status
 ******************************************************************************
 */
MID_StatusTypeDef MID_I2C_Mem_Read(I2C_HandleTypeDef *mI2C, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint32_t tickstart = 0U;
    __IO uint8_t lEventTemp;
    union{
        uint8_t B[2];
        uint16_t H;
    }lMemAddress;

    /* Check the parameters */
    assert_param(IS_I2C_MEMADD_SIZE(MemAddSize));

    if((mI2C->State & (MID_I2C_STATE_READY | MID_I2C_STATE_BUSY)) == MID_I2C_STATE_READY)
    {
        if(__DRV_I2C_GET_FLAG(mI2C, I2C_FLAG_BUSY) != CLR)
        {
            if(__DRV_I2C_GET_FLAG(mI2C, I2C_FLAG_EVENT) != CLR)
            {
                lEventTemp = __DRV_I2C_GET_EVENTCODE(mI2C);
                if((lEventTemp != 0x08) && (lEventTemp != 0x10))
                    return MID_ERROR;
            }
        }

        /* Process Locked */
        __MID_LOCK(mI2C);

        I2C_BUFFMODE_DISABLE(mI2C);

        if(MemAddSize == I2C_MEMADD_SIZE_8BIT)
        {
            lMemAddress.H = MemAddress;
        }
        else
        {
            lMemAddress.B[0] = (uint8_t)(MemAddress >> 8);
            lMemAddress.B[1] = (uint8_t)MemAddress; 
        }

        /* Disable All Interrupt */
        __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_ERR | I2C_IT_BUF | I2C_IT_EVENT); // Disable Interrupt

        /* Clear I2C Flag */
        __DRV_I2C_CLEAR_FLAG(mI2C, (I2C_FLAG_NACK | I2C_FLAG_ALOS | I2C_FLAG_BERR | I2C_FLAG_ROVR | I2C_FLAG_TOVR | I2C_FLAG_STOP | I2C_FLAG_RSTR));

        mI2C->ErrorCode = MID_I2C_ERROR_NONE;
        mI2C->State = MID_I2C_STATE_BUSY_TX;
        mI2C->Mode = MID_I2C_MODE_MASTER_RREPEATSTART;

        /* Prepare transfer parameters */
        mI2C->DevAddress = DevAddress & 0xFFFE;
        mI2C->pBuffPtr = (uint8_t *)(&lMemAddress);
        mI2C->XferSize = MemAddSize;
        mI2C->XferCount = 0;
        mI2C->XferISR = NULL;

        /* Init tickstart for timeout management*/
        tickstart = MID_GetTick();

        /* Send Bus Start */
        lEventTemp = __DRV_I2C_GET_EVENTCODE(mI2C);
        if((lEventTemp == 0xF8) || (lEventTemp == 0xA0))
            __DRV_I2C_STA_1(mI2C);

        do{
            if(I2C_WaitOnEVENTFlagUntilTimeout(mI2C, Timeout, tickstart) != MID_OK)
            {
                /* Process Unlocked */
                __MID_UNLOCK(mI2C);
                return MID_ERROR;
            }
            I2C_BytemodeMasterEventHandle(mI2C);
        }while((mI2C->State & MID_I2C_STATE_BUSY) != 0);

        if(mI2C->ErrorCode != MID_I2C_ERROR_NONE)
        {
            /* Process Unlocked */
            __MID_UNLOCK(mI2C);
            return MID_ERROR;
        }

        /* Clear I2C Flag */
        __DRV_I2C_CLEAR_FLAG(mI2C, (I2C_FLAG_NACK | I2C_FLAG_ALOS | I2C_FLAG_BERR | I2C_FLAG_ROVR | I2C_FLAG_TOVR | I2C_FLAG_STOP | I2C_FLAG_RSTR));

        // mI2C->ErrorCode = MID_I2C_ERROR_NONE;
        mI2C->State = MID_I2C_STATE_BUSY_RX;
        mI2C->Mode = MID_I2C_MODE_MASTER_STOP;

        /* Prepare transfer parameters */
        mI2C->DevAddress = DevAddress | 0x0001;
        mI2C->pBuffPtr = pData;
        mI2C->XferSize = Size;
        mI2C->XferCount = 0;
        mI2C->XferISR = NULL;

        do{
            if(I2C_WaitOnEVENTFlagUntilTimeout(mI2C, Timeout, tickstart) != MID_OK)
            {
                /* Process Unlocked */
                __MID_UNLOCK(mI2C);
                return MID_ERROR;
            }
            I2C_BytemodeMasterEventHandle(mI2C);
        }while((mI2C->State & MID_I2C_STATE_BUSY) != 0);

        mI2C->State = MID_I2C_STATE_READY;
        mI2C->Mode = MID_I2C_MODE_NONE;

        /* Process Unlocked */
        __MID_UNLOCK(mI2C);

        if(mI2C->ErrorCode != MID_I2C_ERROR_NONE)
            return MID_ERROR;
        else
            return MID_OK;
    }
    else
    {
        return MID_BUSY;
    }
}

/**
 ******************************************************************************
 * @brief  Write an amount of data in non-blocking mode with Interrupt to a specific memory address
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @param  DevAddress: Target device address
 * @param  MemAddress: Internal memory address
 * @param  MemAddSize: Size of internal memory address
 * @param  pData: Pointer to data buffer
 * @param  Size: Amount of data to be sent
 * @retval MID status
 ******************************************************************************
 */
MID_StatusTypeDef MID_I2C_Mem_Write_IT(I2C_HandleTypeDef *mI2C, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size)
{
    uint32_t tickstart = 0U;
    __IO uint8_t lEventTemp;
    union{
        uint8_t B[2];
        uint16_t H;
    }lMemAddress;

    /* Check the parameters */
    assert_param(IS_I2C_MEMADD_SIZE(MemAddSize));

    if((mI2C->State & (MID_I2C_STATE_READY | MID_I2C_STATE_BUSY)) == MID_I2C_STATE_READY)
    {
        if(__DRV_I2C_GET_FLAG(mI2C, I2C_FLAG_BUSY) != CLR)
        {
            if(__DRV_I2C_GET_FLAG(mI2C, I2C_FLAG_EVENT) != CLR)
            {
                lEventTemp = __DRV_I2C_GET_EVENTCODE(mI2C);
                if((lEventTemp != 0x08) && (lEventTemp != 0x10))
                    return MID_ERROR;
            }
        }

        /* Process Locked */
        __MID_LOCK(mI2C);

        I2C_BUFFMODE_DISABLE(mI2C);

        if(MemAddSize == I2C_MEMADD_SIZE_8BIT)
        {
            lMemAddress.H = MemAddress;
        }
        else
        {
            lMemAddress.B[0] = (uint8_t)(MemAddress >> 8);
            lMemAddress.B[1] = (uint8_t)MemAddress; 
        }

        /* Disable All Interrupt */
        __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_ERR | I2C_IT_BUF | I2C_IT_EVENT); // Disable Interrupt

        /* Clear I2C Flag */
        __DRV_I2C_CLEAR_FLAG(mI2C, (I2C_FLAG_NACK | I2C_FLAG_ALOS | I2C_FLAG_BERR | I2C_FLAG_ROVR | I2C_FLAG_TOVR | I2C_FLAG_STOP | I2C_FLAG_RSTR));

        mI2C->ErrorCode = MID_I2C_ERROR_NONE;
        mI2C->State = MID_I2C_STATE_BUSY_TX;
        mI2C->Mode = MID_I2C_MODE_MASTER_NONE;

        /* Prepare transfer parameters */
        mI2C->DevAddress = DevAddress & 0xFFFE;
        mI2C->pBuffPtr = (uint8_t *)(&lMemAddress);
        mI2C->XferSize = MemAddSize;
        mI2C->XferCount = 0;
        mI2C->XferISR = NULL;

        /* Init tickstart for timeout management*/
        tickstart = MID_GetTick();

        /* Send Bus Start */
        lEventTemp = __DRV_I2C_GET_EVENTCODE(mI2C);
        if((lEventTemp == 0xF8) || (lEventTemp == 0xA0))
            __DRV_I2C_STA_1(mI2C);

        do{
            if(I2C_WaitOnEVENTFlagUntilTimeout(mI2C, I2C_TIMEOUT_FLAG, tickstart) != MID_OK)
            {
                /* Process Unlocked */
                __MID_UNLOCK(mI2C);
                return MID_ERROR;
            }
            I2C_BytemodeMasterEventHandle(mI2C);
        }while((mI2C->State & MID_I2C_STATE_BUSY) != 0);

        if(mI2C->ErrorCode != MID_I2C_ERROR_NONE)
        {
            /* Process Unlocked */
            __MID_UNLOCK(mI2C);
            return MID_ERROR;
        }

        /* Clear I2C Flag */
        __DRV_I2C_CLEAR_FLAG(mI2C, (I2C_FLAG_NACK | I2C_FLAG_ALOS | I2C_FLAG_BERR | I2C_FLAG_ROVR | I2C_FLAG_TOVR | I2C_FLAG_STOP | I2C_FLAG_RSTR));

        // mI2C->ErrorCode = MID_I2C_ERROR_NONE;
        mI2C->State = MID_I2C_STATE_BUSY_TX;
        mI2C->Mode = MID_I2C_MODE_MASTER_STOP;

        /* Prepare transfer parameters */
        mI2C->pBuffPtr = pData;
        mI2C->XferSize = Size;
        mI2C->XferCount = 0;
        mI2C->XferISR = I2C_Master_ISR_IT;

        /* Process Unlocked */
        __MID_UNLOCK(mI2C);

        /* Note : The I2C interrupts must be enabled after unlocking current process
                  to avoid the risk of I2C interrupt handle execution before current
                  process unlock */

        /* Enable IEA, EVENT, interrupt */
        /* possible to enable all of these */
        /* I2C_IT_IEA | I2C_IT_EVENT */
        __DRV_I2C_ENABLE_IT(mI2C, (I2C_IT_IEA | I2C_IT_EVENT| I2C_IT_BUF)); // Enable Interrupt

        return MID_OK;
    }
    else
    {
        return MID_BUSY;
    }
}

/**
 ******************************************************************************
 * @brief  Read an amount of data in non-blocking mode with Interrupt from a specific memory address
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @param  DevAddress: Target device address
 * @param  MemAddress: Internal memory address
 * @param  MemAddSize: Size of internal memory address
 * @param  pData: Pointer to data buffer
 * @param  Size: Amount of data to be sent
 * @retval MID status
 ******************************************************************************
 */
MID_StatusTypeDef MID_I2C_Mem_Read_IT(I2C_HandleTypeDef *mI2C, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size)
{
    uint32_t tickstart = 0U;
    __IO uint8_t lEventTemp;
    union{
        uint8_t B[2];
        uint16_t H;
    }lMemAddress;

    /* Check the parameters */
    assert_param(IS_I2C_MEMADD_SIZE(MemAddSize));

    if((mI2C->State & (MID_I2C_STATE_READY | MID_I2C_STATE_BUSY)) == MID_I2C_STATE_READY)
    {
        if(__DRV_I2C_GET_FLAG(mI2C, I2C_FLAG_BUSY) != CLR)
        {
            if(__DRV_I2C_GET_FLAG(mI2C, I2C_FLAG_EVENT) != CLR)
            {
                lEventTemp = __DRV_I2C_GET_EVENTCODE(mI2C);
                if((lEventTemp != 0x08) && (lEventTemp != 0x10))
                    return MID_ERROR;
            }
        }

        /* Process Locked */
        __MID_LOCK(mI2C);

        I2C_BUFFMODE_DISABLE(mI2C);

        if(MemAddSize == I2C_MEMADD_SIZE_8BIT)
        {
            lMemAddress.H = MemAddress;
        }
        else
        {
            lMemAddress.B[0] = (uint8_t)(MemAddress >> 8);
            lMemAddress.B[1] = (uint8_t)MemAddress; 
        }

        /* Disable All Interrupt */
        __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_ERR | I2C_IT_BUF | I2C_IT_EVENT); // Disable Interrupt

        /* Clear I2C Flag */
        __DRV_I2C_CLEAR_FLAG(mI2C, (I2C_FLAG_NACK | I2C_FLAG_ALOS | I2C_FLAG_BERR | I2C_FLAG_ROVR | I2C_FLAG_TOVR | I2C_FLAG_STOP | I2C_FLAG_RSTR));

        mI2C->ErrorCode = MID_I2C_ERROR_NONE;
        mI2C->State = MID_I2C_STATE_BUSY_TX;
        mI2C->Mode = MID_I2C_MODE_MASTER_RREPEATSTART;

        /* Prepare transfer parameters */
        mI2C->DevAddress = DevAddress & 0xFFFE;
        mI2C->pBuffPtr = (uint8_t *)(&lMemAddress);
        mI2C->XferSize = MemAddSize;
        mI2C->XferCount = 0;
        mI2C->XferISR = NULL;

        /* Init tickstart for timeout management*/
        tickstart = MID_GetTick();

        /* Send Bus Start */
        lEventTemp = __DRV_I2C_GET_EVENTCODE(mI2C);
        if((lEventTemp == 0xF8) || (lEventTemp == 0xA0))
            __DRV_I2C_STA_1(mI2C);

        do{
            if(I2C_WaitOnEVENTFlagUntilTimeout(mI2C, I2C_TIMEOUT_FLAG, tickstart) != MID_OK)
            {
                /* Process Unlocked */
                __MID_UNLOCK(mI2C);
                return MID_ERROR;
            }
            I2C_BytemodeMasterEventHandle(mI2C);
        }while((mI2C->State & MID_I2C_STATE_BUSY) != 0);

        if(mI2C->ErrorCode != MID_I2C_ERROR_NONE)
        {
            /* Process Unlocked */
            __MID_UNLOCK(mI2C);
            return MID_ERROR;
        }

        /* Clear I2C Flag */
        __DRV_I2C_CLEAR_FLAG(mI2C, (I2C_FLAG_NACK | I2C_FLAG_ALOS | I2C_FLAG_BERR | I2C_FLAG_ROVR | I2C_FLAG_TOVR | I2C_FLAG_STOP | I2C_FLAG_RSTR));

        // mI2C->ErrorCode = MID_I2C_ERROR_NONE;
        mI2C->State = MID_I2C_STATE_BUSY_RX;
        mI2C->Mode = MID_I2C_MODE_MASTER_STOP;

        /* Prepare transfer parameters */
        mI2C->DevAddress = DevAddress | 0x0001;
        mI2C->pBuffPtr = pData;
        mI2C->XferSize = Size;
        mI2C->XferCount = 0;
        mI2C->XferISR = I2C_Master_ISR_IT;

        /* Send Bus Start */
        lEventTemp = __DRV_I2C_GET_EVENTCODE(mI2C);
        if((lEventTemp == 0xF8) || (lEventTemp == 0xA0))
            __DRV_I2C_STA_1(mI2C);

        /* Process Unlocked */
        __MID_UNLOCK(mI2C);

        /* Note : The I2C interrupts must be enabled after unlocking current process
                  to avoid the risk of I2C interrupt handle execution before current
                  process unlock */

        /* Enable IEA, EVENT, interrupt */
        /* possible to enable all of these */
        /* I2C_IT_IEA | I2C_IT_EVENT */
        __DRV_I2C_ENABLE_IT(mI2C, (I2C_IT_IEA | I2C_IT_EVENT| I2C_IT_BUF)); // Enable Interrupt

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

/** @name   I2C_IRQ_Handler_and_Callbacks IRQ Handler and Callbacks
 * @{
 */



#include "Arduino.h"
/**
 ******************************************************************************
 * @brief  This function handles I2C interrupt request.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @retval None
 ******************************************************************************
 */
void MID_I2C_IRQHandler(I2C_HandleTypeDef *mI2C)
{
    /* Get current IT Flags and IT sources value */
    uint32_t itflags   = READ_REG(mI2C->Instance->STA.W);
    uint32_t itsources = READ_REG(mI2C->Instance->INT.W);

    /* I2C events treatment -------------------------------------*/
    if(mI2C->XferISR != NULL)
    {
        mI2C->XferISR(mI2C, itflags, itsources);
    }
}

#if 0
/**
 ******************************************************************************
 * @brief  Master Tx Transfer completed callback.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @retval None
 ******************************************************************************
 */
__weak void MID_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *mI2C)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mI2C);

  /* NOTE : This function should not be modified, when the callback is needed,
            the MID_I2C_MasterTxCpltCallback could be implemented in the user file
  */
}

/**
 ******************************************************************************
 * @brief  Master Rx Transfer completed callback.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @retval None
 ******************************************************************************
 */
__weak void MID_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *mI2C)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mI2C);

  /* NOTE : This function should not be modified, when the callback is needed,
            the MID_I2C_MasterRxCpltCallback could be implemented in the user file
  */
}



/**
 ******************************************************************************
 * @brief  Slave Tx Transfer completed callback.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @retval None
 ******************************************************************************
 */
__weak void MID_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *mI2C)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mI2C);

  /* NOTE : This function should not be modified, when the callback is needed,
            the MID_I2C_SlaveTxCpltCallback could be implemented in the user file
  */
}

/**
 ******************************************************************************
 * @brief  Slave Rx Transfer completed callback.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @retval None
 ******************************************************************************
 */
__weak void MID_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *mI2C)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mI2C);

  /* NOTE : This function should not be modified, when the callback is needed,
            the MID_I2C_SlaveRxCpltCallback could be implemented in the user file
  */
}

/**
 ******************************************************************************
 * @brief  Slave Address Match callback.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @param  TransferDirection: Master request Transfer Direction (Write/Read), value of reference I2C_XFERDIRECTION
 * @param  AddrMatchCode: Address Match Code
 * @retval None
 ******************************************************************************
 */
__weak void MID_I2C_AddrCallback(I2C_HandleTypeDef *mI2C, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mI2C);
  UNUSED(TransferDirection);
  UNUSED(AddrMatchCode);

  /* NOTE : This function should not be modified, when the callback is needed,
            the MID_I2C_AddrCallback() could be implemented in the user file
  */
}



/**
 ******************************************************************************
 * @brief  I2C error callback.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @retval None
 ******************************************************************************
 */
__weak void MID_I2C_ErrorCallback(I2C_HandleTypeDef *mI2C)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mI2C);

  /* NOTE : This function should not be modified, when the callback is needed,
            the MID_I2C_ErrorCallback could be implemented in the user file
  */
}
#endif


/**
 * @}
 */

/** @name   I2C_Exported_Functions_Group3 Peripheral State, Mode and Error functions
 *  @brief      Peripheral State, Mode and Error functions
 *
@verbatim
 ===============================================================================
            ##### Peripheral State, Mode and Error functions #####
 ===============================================================================
    [..]
    This subsection permit to get in run-time the status of the peripheral
    and the data flow.

@endverbatim
 * @{
 */

/**
 ******************************************************************************
 * @brief  Return the I2C handle state.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @retval MID state
 ******************************************************************************
 */
uint32_t MID_I2C_GetState(I2C_HandleTypeDef *mI2C)
{
    /* Return I2C handle state */
    return mI2C->State;
}

/**
 ******************************************************************************
 * @brief  Returns the I2C Master, Slave, Memory or no mode.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *         the configuration information for I2C module
 * @retval MID mode
 ******************************************************************************
 */
uint32_t MID_I2C_GetMode(I2C_HandleTypeDef *mI2C)
{
    return mI2C->Mode;
}

/**
 ******************************************************************************
 * @brief  Return the I2C error code.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *              the configuration information for the specified I2C.
 * @retval I2C Error Code
 ******************************************************************************
*/
uint32_t MID_I2C_GetError(I2C_HandleTypeDef *mI2C)
{
    return mI2C->ErrorCode;
}

/**
 * @}
 */

/**
 * @}
 */

/** @name   I2C_Private_Functions
 * @{
 */

/**
 ******************************************************************************
 * @brief  I2C Listen Process
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *              the configuration information for the specified I2C.
 * @retval None
 ******************************************************************************
*/
static void I2C_ListenP(I2C_HandleTypeDef *mI2C)
{
    if((mI2C->Instance->CR0.B[0] & (I2C_CR0_SADR_EN_mask_b0 | I2C_CR0_SADR2_EN_mask_b0 | I2C_CR0_GC_EN_mask_b0)) != 0)
    {
        __DRV_I2C_STA_STO_AA_001(mI2C);
        mI2C->State |= MID_I2C_STATE_LISTEN;
    }
    else
    {
        __DRV_I2C_STA_STO_AA_000(mI2C);
    }
}

/**
 ******************************************************************************
 * @brief  Byte Mode Event handle the Master Mode.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @retval MID status
 ******************************************************************************
 */
static MID_StatusTypeDef I2C_BytemodeMasterEventHandle(I2C_HandleTypeDef *mI2C)
{
    uint8_t lState;


    if((mI2C->Instance->STA2.W & I2C_STA2_EVENTF2_mask_w) == 0)
    {
        return MID_OK;
    }


    lState = __DRV_I2C_GET_EVENTCODE(mI2C);
    switch(lState)
    {
        case 0x00:  // Bus Error
            mI2C->ErrorCode = MID_I2C_ERROR_BERR;
            mI2C->State |= MID_I2C_STATE_ERROR;

            if((mI2C->Instance->INT.W & I2C_IT_EVENT) != 0)
                MID_I2C_ErrorCallback(mI2C);

            __DRV_I2C_CLEAR_FLAG(mI2C, I2C_FLAG_BERR | I2C_FLAG_ERR);
            __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
            while(__DRV_I2C_GET_EVENTCODE(mI2C) != 0xF8);
            __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_EVENT);
            mI2C->State &= (~MID_I2C_STATE_BUSY);
            I2C_ListenP(mI2C);
            break;

        case 0x08:  // A START condition has been transmitted
        case 0x10:  // Repeated start condition
            __DRV_I2C_STA_0(mI2C);
            __DRV_I2C_WRITE_SBUF(mI2C, ((uint8_t)mI2C->DevAddress));
            __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
            break;

        case 0x20:  // MT SLA+W sent NACK received 
            if((mI2C->Mode & MID_I2C_MODE_NACKNext) == 0)
            {
                __DRV_I2C_CLEAR_FLAG(mI2C, I2C_FLAG_NACK | I2C_FLAG_ERR);
                __DRV_I2C_STA_STO_AA_010(mI2C);
                __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
                while(__DRV_I2C_GET_EVENTCODE(mI2C) != 0xF8);

                __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_EVENT);
                I2C_ListenP(mI2C);
                mI2C->ErrorCode = MID_I2C_ERROR_NACKF;
                mI2C->State |= MID_I2C_STATE_ERROR_TX;
                break;
            }

        #if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
        __attribute__((fallthrough));
        #endif
        case 0x18:  // MT SLA+W sent and ACK received
            mI2C->State &= ~MID_I2C_STATE_LISTEN;
            if((mI2C->Mode & MID_I2C_MODE_DMA_MTX) != 0)
            {
                __DRV_I2C_PSTA_PSTO_PAA_000(mI2C);
                mI2C->Instance->CR0.W |= I2C_CR0_DMA_TXEN_enable_w;
                __ISB();
                break;
            }
            goto EventCode0x28;

        case 0x30:  // MT DATA sent NACK received
            if((mI2C->Mode & MID_I2C_MODE_NACKNext) == 0)
            {
                if((mI2C->Mode & MID_I2C_MODE_DMA_MTX) != 0)
                {
                    mI2C->Mode &= ~MID_I2C_MODE_DMA_MTX;
                    mI2C->XferCount = (mI2C->XferSize - mI2C->hdmatx->Instance->CH0CNT.W);
                }
                if(mI2C->XferCount < mI2C->XferSize)
                {
                    mI2C->XferCount++;
                    mI2C->ErrorCode = MID_I2C_ERROR_NACKF;
                    mI2C->State |= MID_I2C_STATE_ERROR;
                }
                __DRV_I2C_CLEAR_FLAG(mI2C, I2C_FLAG_NACK | I2C_FLAG_ERR);
                __DRV_I2C_STA_STO_AA_010(mI2C);
                __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
                while(__DRV_I2C_GET_EVENTCODE(mI2C) != 0xF8);
    
                __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_EVENT);
                I2C_ListenP(mI2C);
                mI2C->State &= ~MID_I2C_STATE_BUSY;
                break;
            }

      EventCode0x28:
        case 0x28:  // MT DATA sent and ACK received
            if(mI2C->XferCount == mI2C->XferSize)
            {
                if((mI2C->Mode & MID_I2C_MODE_MASK) == MID_I2C_MODE_RREPEATSTART)
                {
                    __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_EVENT);
                    __DRV_I2C_STA_STO_AA_100(mI2C);
                    __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
                    while(__DRV_I2C_GET_EVENTCODE(mI2C) != 0x10);
                }

                if((mI2C->Mode & MID_I2C_MODE_MASK) == MID_I2C_MODE_STOP)
                {
                    __DRV_I2C_STA_STO_AA_010(mI2C);
                    __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
                    while(__DRV_I2C_GET_EVENTCODE(mI2C) != 0xF8);
                }

                __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_EVENT);
                I2C_ListenP(mI2C);
                mI2C->State &= ~MID_I2C_STATE_BUSY;

                if((mI2C->Instance->INT.W & I2C_IT_EVENT) != 0)
                    MID_I2C_MasterTxCpltCallback(mI2C);

                break;
            }

            __DRV_I2C_WRITE_SBUF(mI2C, mI2C->pBuffPtr[mI2C->XferCount]);
            mI2C->XferCount ++;
            __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
            break;

        case 0x38:  // Arbitration lost
            mI2C->ErrorCode = MID_I2C_ERROR_ARLO;
            mI2C->State |= MID_I2C_STATE_ERROR;

            if((mI2C->Instance->INT.W & I2C_IT_EVENT) != 0)
                MID_I2C_ErrorCallback(mI2C);

            __DRV_I2C_CLEAR_FLAG(mI2C, I2C_FLAG_ALOS | I2C_FLAG_ERR);
            __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_EVENT);
            I2C_ListenP(mI2C);
            mI2C->State &= (~MID_I2C_STATE_BUSY);
            __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
            break;

        case 0x40:  // SLA+R sent and ACK received
            mI2C->State &= ~MID_I2C_STATE_LISTEN;
            __DRV_I2C_STA_STO_AA_001(mI2C);
            if(mI2C->XferCount >= (mI2C->XferSize - 1))
            {
                __DRV_I2C_STA_STO_AA_000(mI2C);
                __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
                break;
            }

            if((mI2C->Mode & MID_I2C_MODE_DMA_MRX) != 0)
            {
                //if((mI2C->Mode.H & Sample_I2C_XferNext_Mask) == Sample_I2C_XferNext_RepeatStart)
                //    PreI2C_STA_STO_AA_100(mI2C->Instance);
                //else
                //    PreI2C_STA_STO_AA_010(mI2C->Instance);

                __DRV_I2C_PSTA_PSTO_PAA_000(mI2C);
                mI2C->Instance->CR0.W |= I2C_CR0_DMA_RXEN_mask_w;
                __ISB();
                break;
            }
            __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
            break;

        case 0x48:  // MR SLA+R sent NACK received
            mI2C->ErrorCode = MID_I2C_ERROR_NACKF;
            mI2C->State |= MID_I2C_STATE_ERROR;
            __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_EVENT);
            __DRV_I2C_CLEAR_FLAG(mI2C, I2C_FLAG_NACK | I2C_FLAG_ERR);
            __DRV_I2C_STA_STO_AA_010(mI2C);
            __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
            while(__DRV_I2C_GET_EVENTCODE(mI2C) != 0xF8);
            I2C_ListenP(mI2C);
            mI2C->State &= ~MID_I2C_STATE_BUSY;
            break;

        case 0x50:  // Data Received and ACK sent
            mI2C->pBuffPtr[mI2C->XferCount] = __DRV_I2C_READ_SBUF(mI2C);
            mI2C->XferCount++;
            if(mI2C->XferCount >= (mI2C->XferSize - 1))
                __DRV_I2C_STA_STO_AA_000(mI2C);
            __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
            break;

        case 0x58:  // Data Received and NACK sent
            mI2C->pBuffPtr[mI2C->XferCount] = __DRV_I2C_READ_SBUF(mI2C);
            mI2C->XferCount++;
            __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_EVENT);
            if((mI2C->Mode & MID_I2C_MODE_MASK) == MID_I2C_MODE_RREPEATSTART)
            {
                __DRV_I2C_STA_STO_AA_100(mI2C);
                __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
                while(__DRV_I2C_GET_EVENTCODE(mI2C) != 0x10);
            }
            else
            {
                __DRV_I2C_STA_STO_AA_010(mI2C);
                __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
                while(__DRV_I2C_GET_EVENTCODE(mI2C) != 0xF8);
            }
            I2C_ListenP(mI2C);
            mI2C->State &= ~MID_I2C_STATE_BUSY;

            if((mI2C->Instance->INT.W & I2C_IT_EVENT) != 0)
                MID_I2C_MasterRxCpltCallback(mI2C);

            break;

        case 0x68:  // Arbitration lost in SLA+R/W as master,
                    // Own SLA+W has been Received ACK has bee returned
        case 0x78:  // Arbitration lost in SLA+R/W as master,
                    // General Call address has been received ACK has been returned
            mI2C->ErrorCode = MID_I2C_ERROR_ARLO;
            mI2C->State |= (MID_I2C_STATE_LISTEN | MID_I2C_STATE_ERROR);

            if((mI2C->Instance->INT.W & I2C_IT_EVENT) != 0)
            {
                MID_I2C_AddrCallback(mI2C, I2C_DIRECTION_RECEIVE, (mI2C->Instance->SAC.H[0] & 0xFFFE));
            }
            __DRV_I2C_STA_STO_AA_001(mI2C);
            __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_EVENT);
            __DRV_I2C_CLEAR_FLAG(mI2C, I2C_FLAG_ALOS | I2C_FLAG_ERR);
            mI2C->State &= ~MID_I2C_STATE_BUSY;
            break;

        case 0xB0:  // Arbitration lost in SLA+R/W as master,
                // Own SLA+R has been Received ACK has bee returned
            mI2C->ErrorCode = MID_I2C_ERROR_ARLO;
            mI2C->State |= (MID_I2C_STATE_LISTEN | MID_I2C_STATE_ERROR);

            if((mI2C->Instance->INT.W & I2C_IT_EVENT) != 0)
                MID_I2C_AddrCallback(mI2C, I2C_DIRECTION_TRANSMIT, (mI2C->Instance->SAC.H[0] & 0xFFFE));

            __DRV_I2C_STA_STO_AA_001(mI2C);
            __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_EVENT);
            __DRV_I2C_CLEAR_FLAG(mI2C, I2C_FLAG_ALOS | I2C_FLAG_ERR);
            mI2C->State &= ~MID_I2C_STATE_BUSY;
            break;
    }
    return MID_OK;
}

/**
 ******************************************************************************
 * @brief  Interrupt Sub-Routine which handle the Interrupt Flags Master Mode with Interrupt.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @param  ITFlags: Interrupt flags to handle.
 * @param  ITSources: Interrupt sources enabled.
 * @retval MID status
 ******************************************************************************
 */
static MID_StatusTypeDef I2C_Master_ISR_IT(struct tag_I2C_HandleTypeDef *mI2C, uint32_t ITFlags, uint32_t ITSources)
{
    //uint32_t tmpITFlags = ITFlags;
    //uint16_t devaddress = 0U;
    //uint8_t lState;

    /* Process Locked */
    __MID_LOCK(mI2C);

   if(((mI2C->Instance->CR0.W & I2C_CR0_BUF_EN_mask_w) == 0) && ((ITFlags & I2C_FLAG_EVENT) != 0))
    {
        I2C_BytemodeMasterEventHandle(mI2C);
    }

    if(((ITFlags & I2C_FLAG_TMOUT) != 0) && ((ITSources & I2C_IT_TMOUT) != 0))
    {

    }

    /* Process Unlocked */
    __MID_UNLOCK(mI2C);

    return MID_OK;
}


/**
 ******************************************************************************
 * @brief  Byte Mode Event handle the Slave Mode.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @retval MID status
 ******************************************************************************
 */
MID_StatusTypeDef I2C_BytemodeSlaveEventHandle(I2C_HandleTypeDef *mI2C)
{
    uint8_t lState;

    if((mI2C->Instance->STA2.W & I2C_STA2_EVENTF2_mask_w) == 0)
    {
        return MID_OK;
    }

    lState = __DRV_I2C_GET_EVENTCODE(mI2C);
    switch(lState)
    {
        case 0x00:  // Bus Error
            mI2C->ErrorCode = MID_I2C_ERROR_BERR;
            mI2C->State |= MID_I2C_STATE_ERROR;

            if((mI2C->Instance->INT.W & I2C_IT_EVENT) != 0)
                MID_I2C_ErrorCallback(mI2C);

            __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_EVENT);
            __DRV_I2C_CLEAR_FLAG(mI2C, I2C_FLAG_BERR | I2C_FLAG_ERR);
            __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
            I2C_ListenP(mI2C);
            mI2C->State &= ~MID_I2C_STATE_BUSY;
            break;

        case 0x38:  // Arbitration lost
            mI2C->ErrorCode = MID_I2C_ERROR_ARLO;
            mI2C->State |= MID_I2C_STATE_ERROR;

            if((mI2C->Instance->INT.W & I2C_IT_EVENT) != 0)
                MID_I2C_ErrorCallback(mI2C);

            __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_EVENT);
            __DRV_I2C_CLEAR_FLAG(mI2C, I2C_FLAG_ALOS | I2C_FLAG_ERR);
            __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
            I2C_ListenP(mI2C);
            mI2C->State &= ~(uint32_t)MID_I2C_STATE_BUSY;
            break;

        case 0x68:  // Arbitration lost in SLA+R/W as master,
                    // Own SLA+W has been Received ACK has bee returned
        case 0x78:  // Arbitration lost in SLA+R/W as master,
                    // General Call address has been received ACK has been returned
        case 0x60:  // Own SLA+W has bee Received ACK has been returned
        case 0x70:  // General Call address has been received ACK has been returned
            if((mI2C->Instance->INT.W & I2C_IT_EVENT) != 0)
            {
                MID_I2C_AddrCallback(mI2C, I2C_DIRECTION_RECEIVE, (mI2C->Instance->SAC.H[0] & 0xFFFE));
            }

            if(mI2C->XferCount != 0)
            {  
                __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_EVENT);
                break;
            }

            mI2C->State &= ~MID_I2C_STATE_LISTEN;
            if((mI2C->Mode & MID_I2C_MODE_DMA_SRX) != 0)
            {
                __DRV_I2C_PSTA_PSTO_PAA_001(mI2C);
                mI2C->Instance->CR0.W |= I2C_CR0_DMA_RXEN_mask_w;
                __ISB();
            }
            __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
            break;

        case 0x80:  // Data byte has been received ACK has been return
        case 0x90:  // Previously address with General Call address
                    // Data byte has been received ACK has been return
            mI2C->pBuffPtr[mI2C->XferCount] = __DRV_I2C_READ_SBUF(mI2C);
            mI2C->XferCount++;
            if(mI2C->XferCount >= (mI2C->XferSize))
            {
                __DRV_I2C_STA_STO_AA_000(mI2C);
            }
            __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
            break;

        case 0x88:  // Data byte has been received Not ACK has been return
        case 0x98:  // Previously address with General Call address
                    // Data byte has been received Not ACK has been return
            mI2C->XferCount++;
            mI2C->ErrorCode = MID_I2C_ERROR_OVR;
            mI2C->State |= MID_I2C_STATE_ERROR;
            __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_EVENT);
            __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
            I2C_ListenP(mI2C);
            mI2C->State &= ~MID_I2C_STATE_BUSY;
            break;

        case 0xA0:  // A STOP or repeated START has been received while will addressed as SLV/REC
            if((mI2C->Mode & (MID_I2C_MODE_DMA_SRX | MID_I2C_MODE_DMA_STX)) != 0)
            {
                if((mI2C->hdmarx->Instance->CH0CNT.W == 0) && ((mI2C->hdmarx->Instance->CH0A.W & DMA_CH0A_CH0_REQ_enable_w) != 0))
                {
                    mI2C->XferCount = mI2C->hdmarx->Instance->CH0CNT.W;
                }
                else
                {
                    mI2C->XferCount = (mI2C->XferSize - mI2C->hdmarx->Instance->CH0CNT.W);
                }
            }

            if (mI2C->XferCount == 0)
            {
                mI2C->State |= MID_I2C_STATE_LISTEN;
                __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
                break;
            }

            if(mI2C->XferCount < (mI2C->XferSize - 1))
            {
                mI2C->ErrorCode = MID_I2C_ERROR_NACKF;
                //mI2C->State.B |= MID_I2C_STATE_ERROR;
            }

            MID_I2C_SlaveRxCpltCallback( mI2C );

            __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_EVENT);
            __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
            I2C_ListenP(mI2C);
            mI2C->State &= ~MID_I2C_STATE_BUSY;
            break;

        case 0xA8:  // Own SLA+R has bee Received ACK has been returned
        case 0xB0:  // Arbitration lost in SLA+R/W as master,
                    // Own SLA+R has been Received ACK has bee returned
            if((mI2C->Instance->INT.W & I2C_IT_EVENT) != 0)
            {
                MID_I2C_AddrCallback(mI2C, I2C_DIRECTION_TRANSMIT, (mI2C->Instance->SAC.H[0] & 0xFFFE));
            }
            
            if(mI2C->XferCount != 0)
            {
                __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_EVENT);
                break;
            }

            mI2C->State &= ~MID_I2C_STATE_LISTEN;
            if((mI2C->Mode & MID_I2C_MODE_DMA_STX) != 0)
            {
                __DRV_I2C_PSTA_PSTO_PAA_000(mI2C);
                mI2C->Instance->CR0.W |= I2C_CR0_DMA_TXEN_mask_w;
                __ISB();
                break;
            }
        #if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
        __attribute__((fallthrough));
        #endif

        case 0xB8:  // Data byte in SIDAT has been transmitted ACK has been received
            if(mI2C->XferCount < mI2C->XferSize)
            {
                __DRV_I2C_WRITE_SBUF(mI2C, (mI2C->pBuffPtr[mI2C->XferCount]));
                mI2C->XferCount ++;

            }
            else
            {
                mI2C->ErrorCode = MID_I2C_ERROR_OVR;
                mI2C->State |= MID_I2C_STATE_ERROR;
                __DRV_I2C_STA_STO_AA_000(mI2C);
                __DRV_I2C_WRITE_SBUF(mI2C, 0xFF);
            }
            __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
            break;

        case 0xC0:  // Data byte or Last data byte in SIDAT has been transmitted Not ACK has been received
            if((mI2C->Mode & MID_I2C_MODE_DMA_STX) != 0)
            {
                mI2C->XferCount = (mI2C->XferSize - mI2C->hdmatx->Instance->CH0CNT.H[0]);
            }
            if(mI2C->XferCount < (mI2C->XferSize))
            {
                mI2C->ErrorCode = MID_I2C_ERROR_NACKF;
                mI2C->State |= MID_I2C_STATE_ERROR;
            }
            __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_EVENT);
            __DRV_I2C_CLEAR_FLAG(mI2C, (I2C_FLAG_NACK | I2C_FLAG_ERR));
            __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
            I2C_ListenP(mI2C);
            mI2C->State &= ~MID_I2C_STATE_BUSY;
            break;

        case 0xC8:  // Last Data byte in SIDAT has been transmitted ACK has been received
            if(mI2C->XferCount >= (mI2C->XferSize - 1))
            {
                mI2C->ErrorCode = MID_I2C_ERROR_OVR;
                mI2C->State |= MID_I2C_STATE_ERROR;
            }

            do{
                if((mI2C->Instance->STA2.B[1] & I2C_STA2_EVENTF2_mask_b1) != 0)
                {
                    mI2C->XferCount ++;
                    __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
                }
            }while(__DRV_I2C_GET_EVENTCODE(mI2C) == 0xC8);

            __DRV_I2C_DISABLE_IT(mI2C, I2C_IT_EVENT);
            __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
            I2C_ListenP(mI2C);
            mI2C->State &= ~MID_I2C_STATE_BUSY;
            break;
    }

    return MID_OK;
}

/**
 ******************************************************************************
 * @brief  Interrupt Sub-Routine which handle the Interrupt Flags Slave Mode with Interrupt.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @param  ITFlags: Interrupt flags to handle.
 * @param  ITSources: Interrupt sources enabled.
 * @retval MID status
 ******************************************************************************
 */
MID_StatusTypeDef I2C_Slave_ISR_IT(struct tag_I2C_HandleTypeDef *mI2C, uint32_t ITFlags, uint32_t ITSources)
{
    //uint32_t tmpITFlags = ITFlags;
    //uint16_t devaddress = 0U;
    //uint8_t lState;


    /* Process Locked */
    __MID_LOCK(mI2C);

    if( ((mI2C->Instance->CR0.W & I2C_CR0_BUF_EN_mask_w) == 0) && ((ITFlags & I2C_FLAG_EVENT) != 0) )
    {
        I2C_BytemodeSlaveEventHandle(mI2C);
    }


    if(((ITFlags & I2C_FLAG_TMOUT) != 0) && ((ITSources & I2C_IT_TMOUT) != 0))
    {

    }

    /* Check if STOPF is set */
    if( ((ITFlags & I2C_FLAG_STOP) != 0) && ((ITSources & I2C_IT_STPSTR) != 0) )
    {
        //MID_I2C_SlaveRxCpltCallback( mI2C );
        __DRV_I2C_STA_STO_AA_001( mI2C );
        mI2C->State |= MID_I2C_STATE_LISTEN;
    }
   
    __DRV_I2C_CLEAR_FLAG( mI2C,  (I2C_FLAG_NACK | I2C_FLAG_ALOS | I2C_FLAG_BERR | I2C_FLAG_ROVR | I2C_FLAG_TOVR | I2C_FLAG_STOP | I2C_FLAG_RSTR)  );
    __DRV_I2C_CLEAR_EVENT_FLAG(mI2C);
    __DRV_I2C_ENABLE_IT(  mI2C,   I2C_IT_IEA|I2C_IT_EVENT| I2C_IT_BUF );


    /* Process Unlocked */
    __MID_UNLOCK(mI2C);

    return MID_OK;
}

/**
 ******************************************************************************
 * @brief  This function handles I2C Communication Timeout for specific usage of TXIS flag.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @param  Timeout: Timeout duration
 * @param  Tickstart: Tick start value
 * @retval MID status
 ******************************************************************************
 */
static MID_StatusTypeDef I2C_WaitOnEVENTFlagUntilTimeout(I2C_HandleTypeDef *mI2C, uint32_t Timeout, uint32_t Tickstart)
{
    uint32_t ltemp32;
    while( __DRV_I2C_GET_FLAG(mI2C, I2C_FLAG_EVENT) == CLR )
    {
       // /* Check if a NACK is detected */
       // if(I2C_IsAcknowledgeFailed(mI2C, Timeout, Tickstart) != MID_OK)
       // {
       //     return MID_ERROR;
       // }

        /* Check for the Timeout */
        if((Timeout != MID_MAX_DELAY) && (Timeout != 0U))
        {
            ltemp32 = (MID_GetTick() - Tickstart);
            if(ltemp32 > Timeout)
            {
                mI2C->ErrorCode = MID_I2C_ERROR_TIMEOUT;
                mI2C->State = MID_I2C_STATE_READY;
                mI2C->Mode = MID_I2C_MODE_NONE;

                return MID_ERROR;
            }
        }
    }
    return MID_OK;
}



/**
 * @}
 */

/**
 * @}
 */
//#endif /* MID_I2C_MODULE_ENABLED */


/************** (C) COPYRIGHT megawin Technology Co., Ltd. *****END OF FILE****/
