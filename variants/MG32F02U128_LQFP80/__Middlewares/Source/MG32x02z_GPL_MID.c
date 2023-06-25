/**
 ******************************************************************************
 * @file        MG32x02z_GPL_MID.c
 * @brief       GPL MID module driver.
 *              This file provides firmware functions to manage the following 
 *              functionalities of the General Purpose Logic (GPL) peripheral:
 *                + Initialization and de-initialization functions
 *                + Peripheral Control functions 
 *                + Peripheral State functions
 * @par         Project
 *              MG32x02z
 * @version     V2.00
 * @date        2021/01/25
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2019 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************
 * @par         Disclaimer 
 *              The Demo software is provided "AS IS"  without any warranty, either 
 *              expressed or implied, including, but not limited to, the implied warranties 
 *              of merchantability and fitness for a particular purpose.  The author will 
 *              not be liable for any special, incidental, consequential or indirect 
 *              damages due to loss of data or any other reason. 
 *              These statements agree with the world wide and local dictated laws about 
 *              authorship and violence against these laws. 
 ******************************************************************************
 @verbatim
 ===============================================================================
                     ##### How to use this driver #####
 ===============================================================================
   [..]
        (+) Enable GPL AHB clock using __MID_RCC_GPL_CLK_ENABLE();
        (+) Initialize GPL calculator
            (++)specify generating polynomial (IP default or non-default one)
            (++)specify initialization value (IP default or non-default one)
            (++)specify input data format
            (++)specify input or output data inversion mode if any
        (+) Use MID_CRC_Accumulate() function to compute the GPL value of the 
            input data buffer starting with the previously computed GPL as 
            initialization value
        (+) Use MID_CRC_Calculate() function to compute the GPL value of the 
            input data buffer starting with the defined initialization value 
            (default or non-default) to initiate GPL calculation

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2019 megawin</center></h2>
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
#include "MG32x02z_GPL_MID.h"

/** @name  MG32x02z_MID_Driver
  * @{
  */

/** @name  GPL GPL
  * @brief GPL MID module driver.
  * @{
  */

//#ifdef MID_GPL_MODULE_ENABLED
//#ifdef 1

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/** @defgroup GPL_Private_Functions GPL Private Functions
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @name  GPL_Exported_Functions GPL Exported Functions
  * @{
  */

/** @name  GPL_Exported_Functions_Group1 Initialization/de-initialization functions
 *  @brief Initialization and Configuration functions. 
 *
@verbatim    
 ===============================================================================
            ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize the GPL according to the specified parameters 
          in the GPL_InitTypeDef and create the associated handle
      (+) DeInitialize the GPL peripheral
      (+) Initialize the GPL MSP (MCU Specific Package)
      (+) DeInitialize the GPL MSP
 
@endverbatim
  * @{
  */

/**
 ******************************************************************************
 * @brief  Initialize the GPL according to the specified
 *         parameters in the GPL_InitTypeDef and initialize the associated handle.
 * @param  mgpl GPL handle
 * @retval MID status
 ******************************************************************************
 */
MID_StatusTypeDef MID_GPL_Init(GPL_HandleTypeDef *mgpl)
{
    /* Check the GPL handle allocation */
    if(mgpl == NULL)
    {
        return MID_ERROR;
    }

    /* Check the parameters */
    assert_param(mgpl->Instance == GPL);

    mgpl->Instance->CR1.B[0] &= ~GPL_CR1_CRC_EN_mask_b0;
    mgpl->Instance->CRCINIT.W = mgpl->Init.CRCInitValue;

    if(mgpl->State == MID_GPL_STATE_RESET)
    {   
        /* Allocate lock resource and initialize it */
        mgpl->Lock = MID_UNLOCKED;

        /* Init the low level hardware */
        MID_GPL_MspInit(mgpl);
    }

    mgpl->State = MID_GPL_STATE_BUSY; 

    /* Reset DIN */
    __MID_GPL_SET_DIN(mgpl, 0x00000000UL);

    /* set input data trasfor mode */
    assert_param(IS_GPL_INPUTDATA_PARITY(mgpl->Init.InputDataParityMode));
    assert_param(IS_GPL_INPUTDATA_INVERSE(mgpl->Init.InputDataInverseMode));
    assert_param(IS_GPL_INPUTDATA_BYTEORDER(mgpl->Init.InputDataByteOrderMode));
    assert_param(IS_GPL_INPUTDATA_BYTEORDER16(mgpl->Init.InputDataByteOrder16Mode));
    assert_param(IS_GPL_INPUTDATA_BITORDER(mgpl->Init.InputDataBitOrderMode));

    /* Set Input Data Parity / Inverse / Byte Order / Bit Order Mode. */
  #if !defined(MG32_1ST)
    mgpl->Instance->CR0.W = (mgpl->Init.InputDataParityMode | \
                             mgpl->Init.InputDataInverseMode | \
                             mgpl->Init.InputDataByteOrderMode | \
                             mgpl->Init.InputDataByteOrder16Mode | \
                             mgpl->Init.InputDataBitOrderMode);
  #else
    mgpl->Instance->CR0.W = (mgpl->Init.InputDataParityMode | \
                             mgpl->Init.InputDataInverseMode | \
                             mgpl->Init.InputDataByteOrderMode | \
                             mgpl->Init.InputDataBitOrderMode);
  #endif

//    WRITE_REG(mgpl->Instance->CRCINIT.W, mgpl->Init.CRCInitValue);
    mgpl->Instance->CRCINIT.W = (uint32_t) mgpl->Init.CRCInitValue;

    /* Set CRC Input Data Width / CRC Polynomial / Output Bit Order Mode */
    assert_param(IS_GPL_CRC_INPUTDATA_WIDTH(mgpl->Init.InputDataByteOrderMode));
    assert_param(IS_GPL_CRC_POLYNOMIAL(mgpl->Init.InputDataByteOrder16Mode));
    assert_param(IS_GPL_OUTPUTDATA_BITORDER(mgpl->Init.InputDataBitOrderMode));
    mgpl->Instance->CR1.W = (mgpl->Init.CRCInputDataWidth | \
                             mgpl->Init.CRCPolynomial | \
                             mgpl->Init.OutputDataBitOrderMode);
 
    /* Set GPL CRC initial value has been 
     * picked up by user */
//    WRITE_REG(mgpl->Instance->CRCINIT.W, mgpl->Init.CRCInitValue);
    mgpl->Instance->CRCINIT.W = (uint32_t) mgpl->Init.CRCInitValue;

    /* Enable GPL CRC */
    mgpl->Instance->CR1.B[0] |= GPL_CR1_CRC_EN_mask_b0;

    /* Change GPL peripheral state */
    mgpl->State = MID_GPL_STATE_READY;

    /* Return function status */
    return MID_OK;
}



/**
 ******************************************************************************
 * @brief  DeInitialize the GPL peripheral. 
 * @param  mgpl GPL handle
 * @retval MID status
 ******************************************************************************
 */
MID_StatusTypeDef MID_GPL_DeInit(GPL_HandleTypeDef *mgpl)
{
    /* Check the GPL handle allocation */
    if(mgpl == NULL)
    {
        return MID_ERROR;
    }

    /* Check the parameters */
    assert_param(mgpl->Instance == GPL);

    /* Check the GPL peripheral state */
    if(mgpl->State == MID_GPL_STATE_BUSY)
    {
        return MID_BUSY;
    }

    /* Change GPL peripheral state */
    mgpl->State = MID_GPL_STATE_BUSY;

    /* Reset GPL calculation unit */
    mgpl->Instance->CR1.W = 0UL;
    mgpl->Instance->CR0.W = 0UL;
    mgpl->Instance->CRCINIT.W = 0UL;

    /* DeInit the low level hardware */
    MID_GPL_MspDeInit(mgpl);

    /* Change GPL peripheral state */
    mgpl->State = MID_GPL_STATE_RESET;

    /* Process unlocked */
    __MID_UNLOCK(mgpl);

    /* Return function status */
    return MID_OK;
}

/**
 ******************************************************************************
 * @brief  Initializes the GPL MSP.
 * @param  mgpl GPL handle
 * @retval None
 ******************************************************************************
 */
__weak void MID_GPL_MspInit(GPL_HandleTypeDef *mgpl)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mgpl);

    /* NOTE : This function should not be modified, when the callback is needed,
            the MID_GPL_MspInit can be implemented in the user file
    */
}

/**
 ******************************************************************************
  * @brief  DeInitialize the GPL MSP.
  * @param  mgpl GPL handle
  * @retval None
 ******************************************************************************
  */
__weak void MID_GPL_MspDeInit(GPL_HandleTypeDef *mgpl)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mgpl);

    /* NOTE : This function should not be modified, when the callback is needed,
              the MID_GPL_MspDeInit can be implemented in the user file
    */
}

/**
  * @}
  */

/**
 ******************************************************************************
 * @name  GPL_Exported_Functions_Group2 Peripheral Control functions 
 * @brief management functions. 
 ******************************************************************************
 *
@verbatim   
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================  
    [..]  This section provides functions allowing to:
      (+) compute the 7U, 8U, 16 or 32-bit GPL value of an 8U, 16 or 32-bit data buffer
          using the combination of the previous GPL value and the new one
          
       [..]  or
          
      (+) compute the 7U, 8U, 16 or 32-bit GPL value of an 8U, 16 or 32-bit data buffer
          independently of the previous GPL value.

@endverbatim
  * @{
  */

/**
 ******************************************************************************
 * @brief  Compute the 7, 8, 16 or 32-bit GPL value of an 8, 16 or 32-bit data buffer
 *         starting with the previously computed GPL as initialization value.
 * @param  mgpl GPL handle
 * @param  pBuffer pointer to the input data buffer, exact input data format is
 *         provided by mgpl->InputDataFormat.  
 * @param  BufferLength input data buffer length (number of bytes if pBuffer
 *         type is * uint8_t, number of MIDf-words if pBuffer type is * uint16_t,
 *         number of words if pBuffer type is * uint32_t).
 * @note   By default, the API expects a uint32_t pointer as input buffer parameter.
 *         Input buffer pointers with other types simply need to be cast in uint32_t
 *         and the API will internally adjust its input data processing based on the
 *         handle field mgpl->InputDataFormat.
 * @retval uint32_t GPL CRC (returned value LSBs for GPL CRC shorter than 32 bits)
 ******************************************************************************
 */
uint32_t MID_GPL_CRC_Accumulate(GPL_HandleTypeDef *mgpl, uint32_t *pBuffer, uint32_t BufferLength)
{
    uint32_t index = 0U; /* GPL input data buffer index */
    uint16_t * lpBuffer16 = (uint16_t *)pBuffer;
    uint8_t  * lpBuffer8 = (uint8_t *)pBuffer;
    union{
        uint32_t W;
        uint16_t H[2];
        uint8_t  B[4];
    }temp;  /* GPL output (read from mgpl->Instance->DOUT register) */

    temp.W = 0;

    /* Process locked */
    __MID_LOCK(mgpl); 

    /* Change GPL peripheral state */  
    mgpl->State = MID_GPL_STATE_BUSY;

    switch (mgpl->Init.CRCInputDataWidth)
    {
        case GPL_CRC_INPUTDATA_WIDTH_32B:  
            /* Enter Data to the GPL calculator */
            for(index = 0U; index < BufferLength; index++)
            {
                mgpl->Instance->DIN.W = pBuffer[index];
            }
            temp.W = mgpl->Instance->DOUT.W;
            break;

        case GPL_CRC_INPUTDATA_WIDTH_16B: 
            /* Enter Data to the GPL calculator */
          #if defined(MG32_1ST)
            if(mgpl->Init.InputDataByteOrder16Mode == GPL_INPUTDATA_BYTEORDER16_DISABLE)
            {
                for(index = 0U; index < BufferLength; index++)
                {
                    mgpl->Instance->DIN.H[0] = lpBuffer16[index];
                }
            }
            else
            {
                for(index = 0U; index < BufferLength; index++)
                {
                    temp.H[0] = lpBuffer16[index];
                    temp.B[3] = temp.B[0];
                    temp.B[0] = temp.B[1];
                    temp.B[1] = temp.B[3];
                    mgpl->Instance->DIN.H[0] = temp.H[0];
                }
            }
            temp.W = mgpl->Instance->DOUT.W;
          #else
            for(index = 0U; index < BufferLength; index++)
            {
                mgpl->Instance->DIN.H[0] = lpBuffer16[index];
            }
            temp.W = mgpl->Instance->DOUT.W;
          #endif
            break;

        case GPL_CRC_INPUTDATA_WIDTH_8B: 
            for(index = 0U; index < BufferLength; index++)
            {
                mgpl->Instance->DIN.B[0] = lpBuffer8[index];
            }
            temp.W = mgpl->Instance->DOUT.W;
            break;

        default:
            break;
    }

    /* Change GPL peripheral state */    
    mgpl->State = MID_GPL_STATE_READY; 

    /* Process unlocked */
    __MID_UNLOCK(mgpl);

    /* Return the GPL computed value */ 
    return temp.W;
}


/**
 ******************************************************************************
 * @brief  Compute the 7, 8, 16 or 32-bit GPL value of an 8, 16 or 32-bit data buffer
 *         starting with mgpl->Instance->INIT as initialization value.
 * @param  mgpl GPL handle
 *
 * @param  pBuffer pointer to the input data buffer, exact input data format is
 *         provided by mgpl->InputDataFormat.
 *
 * @param  BufferLength input data buffer length (number of bytes if pBuffer
 *         type is * uint8_t, number of MIDf-words if pBuffer type is * uint16_t,
 *         number of words if pBuffer type is * uint32_t).
 *
 * @note   By default, the API expects a uint32_t pointer as input buffer parameter.
 *         Input buffer pointers with other types simply need to be cast in uint32_t
 *         and the API will internally adjust its input data processing based on the
 *         handle field mgpl->InputDataFormat. 
 *
 * @retval uint32_t GPL CRC (returned value LSBs for GPL CRC shorter than 32 bits)
 ******************************************************************************
 */
uint32_t MID_GPL_CRC_Calculate(GPL_HandleTypeDef *mgpl, uint32_t *pBuffer, uint32_t BufferLength)
{
    uint32_t index = 0U; /* GPL input data buffer index */
    uint16_t * lpBuffer16 = (uint16_t *)pBuffer;
    uint8_t  * lpBuffer8 = (uint8_t *)pBuffer;
    union{
        uint32_t W;
        uint16_t H[2];
        uint8_t  B[4];
    }temp;  /* GPL output (read from mgpl->Instance->DOUT register) */

    temp.W = 0;

    /* Process locked */
    __MID_LOCK(mgpl); 

    /* Change GPL peripheral state */  
    mgpl->State = MID_GPL_STATE_BUSY;

    /* Reset GPL Calculation Unit (mgpl->Instance->INIT is 
     * written in mgpl->Instance->DR) */
    __MID_GPL_CRC_DISABLE(mgpl);
    __MID_GPL_CRC_CRCINITIALVALUE_RESET(mgpl);
    __MID_GPL_DIN_RESET(mgpl);
    __MID_GPL_CRC_ENABLE(mgpl);

    switch (mgpl->Init.CRCInputDataWidth)
    {
        case GPL_CRC_INPUTDATA_WIDTH_32B:  
            /* Enter Data to the GPL calculator */
            for(index = 0U; index < BufferLength; index++)
            {
                mgpl->Instance->DIN.W = pBuffer[index];
            }
            temp.W = mgpl->Instance->DOUT.W;
            break;

        case GPL_CRC_INPUTDATA_WIDTH_16B: 
            /* Enter Data to the GPL calculator */
          #if defined(MG32_1ST)
            if(mgpl->Init.InputDataByteOrder16Mode == GPL_INPUTDATA_BYTEORDER16_DISABLE)
            {
                for(index = 0U; index < BufferLength; index++)
                {
                    mgpl->Instance->DIN.H[0] = lpBuffer16[index];
                }
            }
            else
            {
                for(index = 0U; index < BufferLength; index++)
                {
                    temp.H[0] = lpBuffer16[index];
                    temp.B[3] = temp.B[0];
                    temp.B[0] = temp.B[1];
                    temp.B[1] = temp.B[3];
                    mgpl->Instance->DIN.H[0] = temp.H[0];
                }
            }
            temp.W = mgpl->Instance->DOUT.W;
          #else
            for(index = 0U; index < BufferLength; index++)
            {
                mgpl->Instance->DIN.H[0] = lpBuffer16[index];
            }
            temp.W = mgpl->Instance->DOUT.W;
          #endif
            break;

        case GPL_CRC_INPUTDATA_WIDTH_8B: 
            for(index = 0U; index < BufferLength; index++)
            {
                mgpl->Instance->DIN.B[0] = lpBuffer8[index];
            }
            temp.W = mgpl->Instance->DOUT.W;
            break;

        default:
            break;
    }

    /* Change GPL peripheral state */    
    mgpl->State = MID_GPL_STATE_READY; 

    /* Process unlocked */
    __MID_UNLOCK(mgpl);

    /* Return the CRC computed value */ 
    return temp.W;
}

/**
  * @}
  */

/**
 *******************************************************************************
 * @name  GPL_Exported_Functions_Group3 Peripheral State functions 
 * @brief Peripheral State functions. 
 *******************************************************************************
 *
@verbatim   
 ===============================================================================
                      ##### Peripheral State functions #####
 ===============================================================================
    [..]
    This subsection permits to get in run-time the status of the peripheral.

@endverbatim
  * @{
  */

/**
 *******************************************************************************
 * @brief  Return the GPL handle state.
 * @param  mgpl GPL handle
 * @retval MID state
 *******************************************************************************
 */
MID_GPL_StateTypeDef MID_GPL_GetState(GPL_HandleTypeDef *mgpl)
{
    /* Return GPL handle state */
    return mgpl->State;
}

/**
  * @}
  */

#if defined(MG32_3RD)
/**
 *******************************************************************************
 * @name  GPL_Exported_Functions_Group4 Peripheral functions 
 * @brief Peripheral functions. 
 *******************************************************************************
 *
@verbatim   
 ===============================================================================
                      ##### Peripheral functions #####
 ===============================================================================  
    [..]
     
    

@endverbatim
  * @{
  */

/**
 ******************************************************************************
 * @brief       Signed Division function to calculate (Dividend / Divisor)
 * @param[in]   Dividend : the dividend of the division, Range +2147483646 ~ -2147483647.
 * @param[in]   Divisor : the divisor of the division, Range +2147483646 ~ -2147483647.
 * @return      The result of (Dividend / Divisor)
 * @details     This is a division function to calculate (Dividend / Divisor)
 ******************************************************************************
 */
int32_t MID_GPL_HDIV_DIV(int32_t Dividend, int32_t Divisor)
{
    GPL->CR1.B[2] |= GPL_CR1_DIV_TYPE_mask_b2;
    GPL->DIVD.W = (uint32_t)Dividend;
    GPL->DIVS.W = (uint32_t)Divisor;
    GPL->CR1.W |= GPL_CR1_DIV_START_mask_w;

    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();

    return (int32_t) GPL->QUT.W;
}

/**
 ******************************************************************************
 * @brief       Unsigned division function to calculate (Dividend / Divisor)
 * @param[in]   Dividend : the dividend of the division, Range 0 ~ 4294967294.
 * @param[in]   Divisor : the divisor of the division, Range 0 ~ 4294967294.
 * @return      The result of (Dividend / Divisor)
 * @details     This is a division function to calculate (Dividend / Divisor)
 ******************************************************************************
 */
uint32_t MID_GPL_HDIV_UDIV(uint32_t Dividend, uint32_t Divisor)
{
    GPL->CR1.B[2] &= (~GPL_CR1_DIV_TYPE_mask_b2);
    GPL->DIVD.W = Dividend;
    GPL->DIVS.W = Divisor;
    GPL->CR1.W |= GPL_CR1_DIV_START_mask_w;

    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();

    return GPL->QUT.W;
}

/**
 ******************************************************************************
 * @brief       To calculate the remainder of Dividend / Divisor, i.e., the result of Dividend mod Divisor.
 * @param[in]   Dividend : the dividend of the division, Range +2147483646 ~ -2147483647.
 * @param[in]   Divisor : the divisor of the division, Range +2147483646 ~ -2147483647.
 * @return      The remainder of (Dividend / Divisor)
 * @details     This function is used to calculate the remainder of Dividend / Divisor.
 ******************************************************************************
 */
int32_t MID_GPL_HDIV_MOD(int32_t Dividend, int32_t Divisor)
{
    GPL->CR1.B[2] |= GPL_CR1_DIV_TYPE_mask_b2;
    GPL->DIVD.W = (uint32_t)Dividend;
    GPL->DIVS.W = (uint32_t)Divisor;
    GPL->CR1.W |= GPL_CR1_DIV_START_mask_w;

    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();

    return (int32_t) GPL->REM.W;
}

/**
 ******************************************************************************
 * @brief       To calculate the remainder of Dividend / Divisor, i.e., the result of Dividend mod Divisor.
 * @param[in]   Dividend : the dividend of the division, Range 0 ~ 4294967294.
 * @param[in]   Divisor : the divisor of the division, Range 0 ~ 4294967294.
 * @return      The remainder of (Dividend / Divisor)
 * @details     This function is used to calculate the remainder of Dividend / Divisor.
 ******************************************************************************
 */
uint32_t MID_GPL_HDIV_UMOD(uint32_t Dividend, uint32_t Divisor)
{
    GPL->CR1.B[2] &= (~GPL_CR1_DIV_TYPE_mask_b2);
    GPL->DIVD.W = Dividend;
    GPL->DIVS.W = Divisor;
    GPL->CR1.W |= GPL_CR1_DIV_START_mask_w;

    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();

    return GPL->REM.W;
}

///**
// ******************************************************************************
// * @brief   computes the quotient and remainder of the division of the numerator
// *          numer by the denominator denom. If the division is inexact, the resulting
// *          quotient is the integer of lesser magnitude that is the nearest to the
// *          algebraic quotient. If the result cannot be represented, the behaviour is
// *          undefined; otherwise, quot * denom + rem shall equal numer.
// * @param[in] Dividend
// * @param[in] Divisor
// * @return  a structure of type div_t, comprising both the quotient and the
// *          remainder. the structure shall contain the following members,
// *          in either order.
// *          int quot; int rem;
// ******************************************************************************
// * @internal
// * @sign    V
// * @endinternal
// */
//div_t div(int Dividend, int Divisor)
//{
//    div_t lDIV_T;
//    GPL->CR1.B[2] |= GPL_CR1_DIV_TYPE_mask_b2;
//    GPL->DIVD.W = Dividend;
//    GPL->DIVS.W = Divisor;
//    GPL->CR1.W |= GPL_CR1_DIV_START_mask_w;
//
//    __NOP();
//    __NOP();
//    __NOP();
//    __NOP();
//    __NOP();
//    __NOP();
//    __NOP();
//    __NOP();
//
//    lDIV_T.quot = GPL->QUT.W;
//    lDIV_T.rem = GPL->REM.W;
//    return lDIV_T;
//}

/**
  * @}
  */
#endif

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************** (C) COPYRIGHT megawin Technology Co., Ltd. *****END OF FILE****/

