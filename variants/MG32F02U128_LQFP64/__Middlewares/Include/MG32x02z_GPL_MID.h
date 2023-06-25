/**
 ******************************************************************************
 * @file        MG32x02z_GPL_MID.h
 * @brief       Header file of GPL MID module.
 * @par         Project
 *              MG32x02z
 * @version     V2.01
 * @date        2021/04/21
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2019 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2019 megawin </center></h2>
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
#ifndef _MG32x02z_GPL_MID_H
#define _MG32x02z_GPL_MID_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MG32x02z_Common_MID.h"
#include "MG32x02z_CSC.h"
#include "MG32x02z_GPL.h"

/** @name  MG32x02z_MID_Driver
  * @{
  */

/** @name  GPL GPL
  * @{
  */ 

/* Exported constants --------------------------------------------------------*/
/** @name  GPL_Exported_Constants GPL Exported Constants
  * @{
  */

/** @name  GPL_Input_Data_Parity Input Data Parity
 *  @{
 */
#define GPL_INPUTDATA_PARITY_EVEN    GPL_CR0_PAR_POL_even_w                             /*!< GPL PARTIY EVEN Setting */
#define GPL_INPUTDATA_PARITY_ODD     GPL_CR0_PAR_POL_odd_w                              /*!< GPL PARTIY ODDD Setting */
#define IS_GPL_INPUTDATA_PARITY(PARITY)    (((PARITY) == GPL_INPUTDATA_PARITY_EVEN) || \
                                            ((PARITY) == GPL_INPUTDATA_PARITY_ODD))     /*!< GPL PARTIY Param Check */
/**
  * @}
  */


/** @name  GPL_Input_Data_Inverse Input Data Inverse
  * @{
  */
#define GPL_INPUTDATA_INVERSE_DISABLE    GPL_CR0_IN_INV_disable_w                       /*!< GPL Inverse Disable */
#define GPL_INPUTDATA_INVERSE_ENABLE     GPL_CR0_IN_INV_enable_w                        /*!< GPL Inverse Enable */
#define IS_GPL_INPUTDATA_INVERSE(INVERSE)    (((INVERSE) == GPL_INPUTDATA_INVERSE_DISABLE) || \
                                              ((INVERSE) == GPL_INPUTDATA_INVERSE_ENABLE))  /*!< GPL Inverse Param check*/
/**
  * @}
  */


/** @name  GPL_Input_Data_Byte_Order Input Data Byte Order Change
  * @{
  */
#define GPL_INPUTDATA_BYTEORDER_DISABLE    GPL_CR0_BEND_EN_disable_w                    /*!< GPL Byte Order Change Disable */
#define GPL_INPUTDATA_BYTEORDER_ENABLE     GPL_CR0_BEND_EN_enable_w                     /*!< GPL Byte Order Change Enable  */
#define IS_GPL_INPUTDATA_BYTEORDER(BYTEORDER)    (((BYTEORDER) == GPL_INPUTDATA_BYTEORDER_DISABLE) || \
                                                  ((BYTEORDER) == GPL_INPUTDATA_BYTEORDER_ENABLE)) /*!< GPL Byte Order Change Param check*/
/**
  * @}
  */

/** @name  GPL_Input_Data_Byte_Order_16 Input Data Byte Order 16-Bit Change
  * @{
  */
#if defined(MG32_1ST)
  #define GPL_INPUTDATA_BYTEORDER16_DISABLE    ((uint32_t)0x00000000)                     /*!< GPL 16-Bit Byte Order Change Disable */
  #define GPL_INPUTDATA_BYTEORDER16_ENABLE     ((uint32_t)0x00000010)                     /*!< GPL 16-Bit Byte Order Change Enable */
#else
  #define GPL_INPUTDATA_BYTEORDER16_DISABLE    GPL_CR0_BEND16_EN_disable_w                /*!< GPL 16-Bit Byte Order Change Disable */
  #define GPL_INPUTDATA_BYTEORDER16_ENABLE     GPL_CR0_BEND16_EN_enable_w                 /*!< GPL 16-Bit Byte Order Change Enable */
#endif
#define IS_GPL_INPUTDATA_BYTEORDER16(BYTEORDER16)    (((BYTEORDER16) == GPL_INPUTDATA_BYTEORDER16_DISABLE) || \
                                                      ((BYTEORDER16) == GPL_INPUTDATA_BYTEORDER16_ENABLE))  /*!< GPL 16-Bit Byte Order Change Param check*/
/**
  * @}
  */

/** @name  GPL_Input_Data_Bit_Order Input Data Bit Order Change
  * @{
  */
#define GPL_INPUTDATA_BITORDER_NONE        GPL_CR0_BREV_MDS_disable_w                   /*!< GPL Input Bit Order Change Disable */
#define GPL_INPUTDATA_BITORDER_BYTE        GPL_CR0_BREV_MDS_8bit_w                      /*!< GPL Input Bit Order Change with 8-Bit */
#define GPL_INPUTDATA_BITORDER_HALFWORD    GPL_CR0_BREV_MDS_16bit_w                     /*!< GPL Input Bit Order Change with 16-Bit */
#define GPL_INPUTDATA_BITORDER_WORD        GPL_CR0_BREV_MDS_32bit_w                     /*!< GPL Input Bit Order Change with 32-Bit */
#define IS_GPL_INPUTDATA_BITORDER(BITORDER)    (((BITORDER) == GPL_INPUTDATA_BITORDER_NONE) || \
                                                ((BITORDER) == GPL_INPUTDATA_BITORDER_BYTE) || \
                                                ((BITORDER) == GPL_INPUTDATA_BITORDER_HALFWORD) || \
                                                ((BITORDER) == GPL_INPUTDATA_BITORDER_WORD))    /*!< GPL Input Bit Order Change Param check */
/**
  * @}
  */


/** @name  GPL_CRC_Input_Data_Width CRC Input Data Width
  * @{
  */
#define GPL_CRC_INPUTDATA_WIDTH_8B     GPL_CR1_CRC_DSIZE_8bit_w                         /*!< GPL CRC Input Data Width 8-Bit */
#define GPL_CRC_INPUTDATA_WIDTH_16B    GPL_CR1_CRC_DSIZE_16bit_w                        /*!< GPL CRC Input Data Width 16-Bit */
#define GPL_CRC_INPUTDATA_WIDTH_32B    GPL_CR1_CRC_DSIZE_32bit_w                        /*!< GPL CRC Input Data Width 32-Bit */
#define IS_GPL_CRC_INPUTDATA_WIDTH(WIDTH)    (((WIDTH) == GPL_CRC_INPUTDATA_WIDTH_8B) || \
                                              ((WIDTH) == GPL_CRC_INPUTDATA_WIDTH_16B) || \
                                              ((WIDTH) == GPL_CRC_INPUTDATA_WIDTH_32B)) /*!< GPL CRC Input Data Width Param check */
/**
  * @}
  */


/** @name  GPL_CRC_Ploynomial CRC Polynomial Use
  * @{
  */
#define GPL_CRC_POLYNOMIAL_CCITT16_0x1021     GPL_CR1_CRC_MDS_ccitt16_w                 /*!< GPL CRC POLYNOMIAL CCITT16, x^16 + x^12 + x^5 + 1 */
#define GPL_CRC_POLYNOMIAL_CRC8_0x07          GPL_CR1_CRC_MDS_crc8_w                    /*!< GPL CRC POLYNOMIAL CRC-8, x^8 + x^2 + x + 1 */
#define GPL_CRC_POLYNOMIAL_CRC16_0x8005       GPL_CR1_CRC_MDS_crc16_w                   /*!< GPL CRC POLYNOMIAL CRC-16, x^16 + x^12 + x^5 + 1 */
#define GPL_CRC_POLYNOMIAL_CRC32_0x4C11DB7    GPL_CR1_CRC_MDS_crc32_w                   /*!< GPL CRC POLYNOMIAL CRC-32, x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11 + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x + 1 */
#define IS_GPL_CRC_POLYNOMIAL(POLYNOMIAL)    (((POLYNOMIAL) == GPL_CRC_POLYNOMIAL_CCITT16_0x1021) || \
                                              ((POLYNOMIAL) == GPL_CRC_POLYNOMIAL_CRC8_0x07) || \
                                              ((POLYNOMIAL) == GPL_CRC_POLYNOMIAL_CRC16_0x8005) || \
                                              ((POLYNOMIAL) == GPL_CRC_POLYNOMIAL_CRC32_0x4C11DB7)) /*!< GPL CRC POLYNOMIAL CRC Param check */
/**
  * @}
  */


/** @name  GPL_Output_Data_Bit_Order Output Data Bit Order Change
  * @{
  */
#define GPL_OUTPUTDATA_BITORDER_NONE        GPL_CR1_CRC_BREV_disable_w                  /*!< GPL CRC Output Bit Order Change Disable */
#define GPL_OUTPUTDATA_BITORDER_BYTE        GPL_CR1_CRC_BREV_8bit_w                     /*!< GPL CRC Output Bit Order Change with 8-Bit */
#define GPL_OUTPUTDATA_BITORDER_HALFWORD    GPL_CR1_CRC_BREV_16bit_w                    /*!< GPL CRC Output Bit Order Change with 16-Bit */
#define GPL_OUTPUTDATA_BITORDER_WORD        GPL_CR1_CRC_BREV_32bit_w                    /*!< GPL CRC Output Bit Order Change with 32-Bit */
#define IS_GPL_OUTPUTDATA_BITORDER(BITORDER)    (((BITORDER) == GPL_OUTPUTDATA_BITORDER_NONE) || \
                                                 ((BITORDER) == GPL_OUTPUTDATA_BITORDER_BYTE) || \
                                                 ((BITORDER) == GPL_OUTPUTDATA_BITORDER_HALFWORD) || \
                                                 ((BITORDER) == GPL_OUTPUTDATA_BITORDER_WORD))   /*!< GPL CRC Output Bit Order Change Param check */
/**
  * @}
  */

/**
  * @}
  */


/* Exported types ------------------------------------------------------------*/ 
/** @name  GPL_Exported_Types GPL Exported Types
  * @{
  */

/** 
 ******************************************************************************
  * @brief  GPL MID State Structure definition
 ******************************************************************************
  */
typedef enum
{                                            
    MID_GPL_STATE_RESET     = 0x00U,  /*!< GPL not yet initialized or disabled */
    MID_GPL_STATE_READY     = 0x01U,  /*!< GPL initialized and ready for use   */
    MID_GPL_STATE_BUSY      = 0x02U,  /*!< GPL internal process is ongoing     */
    MID_GPL_STATE_TIMEOUT   = 0x03U,  /*!< GPL timeout state                   */
    MID_GPL_STATE_ERROR     = 0x04U   /*!< GPL error state                     */
}MID_GPL_StateTypeDef;


/** 
 ******************************************************************************
  * @brief GPL Init Structure definition  
 ******************************************************************************
  */ 
typedef struct __attribute__((packed))
{
    uint32_t InputDataParityMode;       /*!< This parameter is a value of GPL_Input_Data_Parity and specifies input data inversion mode. 
                                             Can be either one of the following values 
                                             GPL_INPUTDATA_PARITY_EVEN
                                             GPL_INPUTDATA_PARITY_ODD */

    uint32_t InputDataInverseMode;      /*!< This parameter is a value of GPL_Input_Data_Inverse and specifies input data inversion mode. 
                                             Can be either one of the following values 
                                             GPL_INPUTDATA_INVERSE_DISABLE   no input data inverse
                                             GPL_INPUTDATA_INVERSE_ENABLE    input data inverse, 0x1A2B3C4D becomes 0xE5D4C3B2 */

    uint32_t InputDataByteOrderMode;    /*!< This parameter is a value of GPL_Input_Data_Byte_Order and specifies input data inversion mode. 
                                             Can be either one of the following values 
                                             GPL_INPUTDATA_BYTEORDER_DISABLE   no input data byte order change
                                             GPL_INPUTDATA_BYTEORDER_ENABLE    input data byte order Change, 0x12345678 is converted into 0x78563412 */

    uint32_t InputDataByteOrder16Mode;  /*!< This parameter is a value of GPL_Input_Data_Byte_Order_16 and specifies input data inversion mode. 
                                             Can be either one of the following values 
                                             GPL_INPUTDATA_BYTEORDER16_DISABLE   no input data byte order Change with 16-Bits
                                             GPL_INPUTDATA_BYTEORDER16_ENABLE    input data byte order Change with 16-Bits, 0x12345678 is converted into 0x34127856 */

    uint32_t InputDataBitOrderMode;     /*!< This parameter is a value of GPL_Input_Data_Bit_Order and specifies input data inversion mode. 
                                             Can be either one of the following values
                                             GPL_INPUTDATA_BITORDER_NONE       no input data bit order change
                                             GPL_INPUTDATA_BITORDER_BYTE       input data bit order Change with 8-Bits, 0x1A2B3C4D is converted into 0x58D43CB2
                                             GPL_INPUTDATA_BITORDER_HALFWORD   input data bit order Change with 16-Bits, 0x1A2B3C4D is converted into 0xD458B23C
                                             GPL_INPUTDATA_BITORDER_WORD       input data bit order Change with 32-Bits, 0x1A2B3C4D is converted into 0xB23CD458 */

    uint32_t CRCInputDataWidth;         /*!< This parameter is a value of GPL_CRC_Input_Data_Width and indicates CRC length.
                                             Value can be either one of
                                             GPL_CRC_INPUTDATA_WIDTH_8B    input data is a stream of bytes (8-bit data)
                                             GPL_CRC_INPUTDATA_WIDTH_16B   input data is a stream of bytes (16-bit data)
                                             GPL_CRC_INPUTDATA_WIDTH_32B   input data is a stream of bytes (32-bit data) */

    uint32_t CRCInitValue;              /*!< Init value to initiate CRC computation. No need to specify it if DefaultInitValueUse 
                                             is set to DEFAULT_INIT_VALUE_ENABLE   */

    uint32_t CRCPolynomial;             /*!< This parameter is a value of GPL_CRC_Ploynomial and indicates if default init value is used. 
                                             Set GPL generating polynomial. 8, 16 or 32-bit long value for a polynomial degree
                                             respectively equal to 8, 16 or 32. This field is written in normal representation, 
                                             GPL_CRC_Polynomial_CCITT16_0x1021    X^16 + X^12 + X^5 + 1
                                             GPL_CRC_Polynomial_CRC8_0x07         X^8 + X^2 + X + 1
                                             GPL_CRC_Polynomial_CRC16_0x8005      X^16 + X^15 + X^2 + 1
                                             GPL_CRC_Polynomial_CRC32_0x4C11DB7   X^32 + X^26 + X^23 + X^22 + X^16 + X^12 + X^11 + X^10 + X^8 + X^7 + X^5 + X^4 + X^2 + X + 1   */

    uint32_t OutputDataBitOrderMode;    /*!< This parameter is a value of GPL_Output_Data_Bit_Order and specifies output data (i.e. CRC) inversion mode.
                                             Can be either 
                                             GPL_OUTPUTDATA_BITORDER_NONE       no Output data bit order change
                                             GPL_OUTPUTDATA_BITORDER_BYTE       Output data bit order Change with 8-Bits, 0x1A2B3C4D is converted into 0x58D43CB2
                                             GPL_OUTPUTDATA_BITORDER_HALFWORD   Output data bit order Change with 16-Bits, 0x1A2B3C4D is converted into 0xD458B23C
                                             GPL_OUTPUTDATA_BITORDER_WORD       Output data bit order Change with 32-Bits, 0x1A2B3C4D is converted into 0xB23CD458 */
}GPL_InitTypeDef;


/** 
 ******************************************************************************
  * @brief  GPL Handle Structure definition  
 ******************************************************************************
  */ 
typedef struct __attribute__((packed))
{
    GPL_Struct                  *Instance;   /*!< Register base address        */ 

    GPL_InitTypeDef             Init;        /*!< GPL configuration parameters */

    MID_LockTypeDef             Lock;        /*!< GPL Locking object           */

    __IO MID_GPL_StateTypeDef   State;       /*!< GPL communication state      */

}GPL_HandleTypeDef;
/**
 * @}
 */

/* Exported macros -----------------------------------------------------------*/

/** @name  GPL_Exported_Macros GPL Exported Macros
 * @{
 */

/**
 ******************************************************************************
 * @brief Get GPL Parity state
 * @param  "__HANDLE__" GPL handle.
 * @retval None
 ******************************************************************************
 */
#define __MID_GPL_GET_PARITY_8_STATE(__HANDLE__)     ((((__HANDLE__)->Instance->STA.B[1] & 0x01U) == 0)? 0 : 1) /*!< GPL Parity 8-Bit State */
#define __MID_GPL_GET_PARITY_16_STATE(__HANDLE__)    ((((__HANDLE__)->Instance->STA.B[1] & 0x10U) == 0)? 0 : 1) /*!< GPL Parity 16-Bit State */
#define __MID_GPL_GET_PARITY_32_STATE(__HANDLE__)    ((((__HANDLE__)->Instance->STA.B[1] & 0x40U) == 0)? 0 : 1) /*!< GPL Parity 32-Bit State */
#define __DRV_GPL_GET_PARITY_8_STATE(__HANDLE__)     ((((__HANDLE__)->Instance->STA.B[1] & 0x01U) == 0)? 0 : 1) /*!< GPL Parity 8-Bit State */
#define __DRV_GPL_GET_PARITY_16_STATE(__HANDLE__)    ((((__HANDLE__)->Instance->STA.B[1] & 0x10U) == 0)? 0 : 1) /*!< GPL Parity 16-Bit State */
#define __DRV_GPL_GET_PARITY_32_STATE(__HANDLE__)    ((((__HANDLE__)->Instance->STA.B[1] & 0x40U) == 0)? 0 : 1) /*!< GPL Parity 32-Bit State */


/**
 ******************************************************************************
 * @brief Reset GPL handle state
 * @param  "__HANDLE__" GPL handle.
 * @retval None
 ******************************************************************************
 */
#define __MID_GPL_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = MID_GPL_STATE_RESET)  /*!< Reset GPL handle state */
#define __DRV_GPL_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = MID_GPL_STATE_RESET)  /*!< Reset GPL handle state */


/**
 ******************************************************************************
 * @brief  Reset GPL CRC INIT Register Reset
 * @param  "__HANDLE__" GPL handle
 * @retval None.
 ******************************************************************************
 */
#define __MID_GPL_CRC_CRCINITIALVALUE_RESET(__HANDLE__) ((__HANDLE__)->Instance->CRCINIT.W = (__HANDLE__)->Init.CRCInitValue) /*!< Reset GPL CRC INIT Register Reset */
#define __DRV_GPL_CRC_CRCINITIALVALUE_RESET(__HANDLE__) ((__HANDLE__)->Instance->CRCINIT.W = (__HANDLE__)->Init.CRCInitValue) /*!< Reset GPL CRC INIT Register Reset */


/**
 ******************************************************************************
 * @brief  Set GPL CRC INIT non-default value
 * @param  "__HANDLE__" GPL handle
 * @param  "__INIT__"   32-bit CRC initial value  
 * @retval None.
 ******************************************************************************
 */
#define __MID_GPL_CRC_INITIALCRCVALUE_CONFIG(__HANDLE__, __INIT__) ((__HANDLE__)->Instance->CRCINIT.W = (__INIT__)) /*!< Set GPL CRC INIT non-default value */
#define __DRV_GPL_CRC_INITIALCRCVALUE_CONFIG(__HANDLE__, __INIT__) ((__HANDLE__)->Instance->CRCINIT.W = (__INIT__)) /*!< Set GPL CRC INIT non-default value */


/**
 ******************************************************************************
 * @brief  Reset GPL Data Input Register.
 * @param  "__HANDLE__" GPL handle
 * @retval None.
 ******************************************************************************
 */
#define __MID_GPL_DIN_RESET(__HANDLE__) ((__HANDLE__)->Instance->DIN.W |= 0x00000000UL) /*!< Reset GPL Data Input Register */
#define __DRV_GPL_DIN_RESET(__HANDLE__) ((__HANDLE__)->Instance->DIN.W |= 0x00000000UL) /*!< Reset GPL Data Input Register */


/**
 ******************************************************************************
 * @brief Stores a 32-bit data in the Data Input(DIN) register.
 * @param "__HANDLE__" GPL handle
 * @param "__VALUE__" 32-bit value to be stored in the ID register
 * @retval None
 ******************************************************************************
 */
#define __MID_GPL_SET_DIN(__HANDLE__, __VALUE__) ((__HANDLE__)->Instance->DIN.W = (__VALUE__))  /*!< Data Input(DIN) register */
#define __DRV_GPL_SET_DIN(__HANDLE__, __VALUE__) ((__HANDLE__)->Instance->DIN.W = (__VALUE__))  /*!< Data Input(DIN) register */


/**
 ******************************************************************************
 * @brief  Returns the 32-bit data stored in the Data Output(DOUT) register.
 * @param  "__HANDLE__" GPL handle
 * @retval 8-bit value of the ID register 
 ******************************************************************************
 */
#define __MID_GPL_GET_DOUT(__HANDLE__) ((__HANDLE__)->Instance->DOUT.W) /*!<  Data Output(DOUT) register */
#define __DRV_GPL_GET_DOUT(__HANDLE__) ((__HANDLE__)->Instance->DOUT.W) /*!<  Data Output(DOUT) register */


/**
 ******************************************************************************
 * @brief  Enable CRC Operation.
 * @param  "__HANDLE__" GPL handle
 * @retval None
 ******************************************************************************
 */
#define __MID_GPL_CRC_ENABLE(__HANDLE__)    ((__HANDLE__)->Instance->CR1.W |= GPL_CR1_CRC_EN_mask_w)    /*!< Enable CRC Operation */
#define __DRV_GPL_CRC_ENABLE(__HANDLE__)    ((__HANDLE__)->Instance->CR1.W |= GPL_CR1_CRC_EN_mask_w)    /*!< Enable CRC Operation */


/**
 ******************************************************************************
 * @brief  Disable CRC Operation.
 * @param  "__HANDLE__" GPL handle
 * @retval None
 ******************************************************************************
 */
#define __MID_GPL_CRC_DISABLE(__HANDLE__)    ((__HANDLE__)->Instance->CR1.W &= ~GPL_CR1_CRC_EN_mask_w)  /*!< Disable CRC Operation */
#define __DRV_GPL_CRC_DISABLE(__HANDLE__)    ((__HANDLE__)->Instance->CR1.W &= ~GPL_CR1_CRC_EN_mask_w)  /*!< Disable CRC Operation */


#if defined(MG32_3RD)
//#include "stdlib.h"

/**
 ******************************************************************************
 * @brief  Hardware divider division type selection.
 * @retval None
 ******************************************************************************
 */
#define __MID_GPL_HDIV_UNSIGNED_CALCULATION()   GPL->CR1.B[2] &= (~GPL_CR1_DIV_TYPE_mask_b2)    /*!< Hardware Divider Unsinged Calculation */
#define __DRV_GPL_HDIV_UNSIGNED_CALCULATION()   GPL->CR1.B[2] &= (~GPL_CR1_DIV_TYPE_mask_b2)    /*!< Hardware Divider Unsinged Calculation */
#define HDIV_UNSIGNED_CALCULATION()             GPL->CR1.B[2] &= (~GPL_CR1_DIV_TYPE_mask_b2)    /*!< Hardware Divider Unsinged Calculation */
#define __MID_GPL_HDIV_SIGNED_CALCULATION()     GPL->CR1.B[2] |= GPL_CR1_DIV_TYPE_mask_b2       /*!< Hardware Divider Singed Calculation */
#define __DRV_GPL_HDIV_SIGNED_CALCULATION()     GPL->CR1.B[2] |= GPL_CR1_DIV_TYPE_mask_b2       /*!< Hardware Divider Singed Calculation */
#define HDIV_SIGNED_CALCULATION()               GPL->CR1.B[2] |= GPL_CR1_DIV_TYPE_mask_b2       /*!< Hardware Divider Singed Calculation */

/**
 ******************************************************************************
 * @brief  Get Remainder of the last division.
 * @retval Remainder
 ******************************************************************************
 */
#define __MID_GPL_HDIV_GET_REMAINDER()          GPL->REM.W                                      /*!< Return Remainder of the last division */
#define __DRV_GPL_HDIV_GET_REMAINDER()          GPL->REM.W                                      /*!< Return Remainder of the last division */
#define HDIV_GET_REMAINDER()                    GPL->REM.W                                      /*!< Return Remainder of the last division */

/**
 ******************************************************************************
 * @brief      Get previous HDIV status for divide by zero
 * @retval     0 : divisor is not zero
 * @retval     1 : divisor is zero
 * @details    This macro get previous HDIV status for divide by zero
 ******************************************************************************
 */
#define __MID_GPL_HDIV_IS_DIVBYZERO()   ((GPL->STA.B[0] & GPL_STA_DIVZEF_mask_b0) >> 2)         /*!< HDIV status for divide by zero */
#define __DRV_GPL_HDIV_IS_DIVBYZERO()   ((GPL->STA.B[0] & GPL_STA_DIVZEF_mask_b0) >> 2)         /*!< HDIV status for divide by zero */
#define HDIV_IS_DIVBYZERO()             ((GPL->STA.B[0] & GPL_STA_DIVZEF_mask_b0) >> 2)         /*!< HDIV status for divide by zero */

#endif

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @name  GPL_Exported_Functions GPL Exported Functions
 *  @{
 */

/**
 * @name  GPL_Exported_Functions_Group1 Initialization/de-initialization functions 
 *  @brief Initialization and Configuration functions. 
 *  @{
 */

/* Initialization and de-initialization functions *****************************/
MID_StatusTypeDef MID_GPL_Init(GPL_HandleTypeDef *mgpl);
MID_StatusTypeDef MID_GPL_DeInit(GPL_HandleTypeDef *mgpl);
void MID_GPL_MspInit(GPL_HandleTypeDef *mgpl);
void MID_GPL_MspDeInit(GPL_HandleTypeDef *mgpl);
/**
 *  @}
 */


/** @name  GPL_Exported_Functions_Group2 Peripheral Control functions 
 *  @brief management functions.
 *  @{
 */ 
 
/* Peripheral Control functions ***********************************************/
uint32_t MID_GPL_CRC_Accumulate(GPL_HandleTypeDef *mgpl, uint32_t *pBuffer, uint32_t BufferLength);
uint32_t MID_GPL_CRC_Calculate(GPL_HandleTypeDef *mgpl, uint32_t *pBuffer, uint32_t BufferLength); /*!< Calculate*/

/**
 *  @}
 */


/** @name  GPL_Exported_Functions_Group3 Peripheral State functions 
 *  @brief Peripheral State functions.
 *  @{
 */

/* Peripheral State and Error functions ***************************************/
MID_GPL_StateTypeDef MID_GPL_GetState(GPL_HandleTypeDef *mgpl);

/**
 *  @}
 */

#if defined(MG32_3RD)
/** @name  GPL_Exported_Functions_Group4 Peripheral State functions 
 *  @brief Peripheral State functions.
 *  @{
 */
int32_t MID_GPL_HDIV_DIV(int32_t Dividend, int32_t Divisor);
int32_t MID_GPL_HDIV_MOD(int32_t Dividend, int32_t Divisor);
uint32_t MID_GPL_HDIV_UDIV(uint32_t Dividend, uint32_t Divisor);
uint32_t MID_GPL_HDIV_UMOD(uint32_t Dividend, uint32_t Divisor);

#if defined(__MG32x02z_GPL_DRV_H)
  #undef HDIV_DIV
  #undef HDIV_MOD
  #undef HDIV_UDIV
  #undef HDIV_UMOD
#endif

#define HDIV_DIV    MID_GPL_HDIV_DIV                                                    /*!< Division function to calculate */
#define HDIV_MOD    MID_GPL_HDIV_MOD                                                    /*!< Remainder function to calculate */
#define HDIV_UDIV   MID_GPL_HDIV_UDIV                                                   /*!< Division function to unsigned alculate */
#define HDIV_UMOD   MID_GPL_HDIV_UMOD                                                   /*!< Remainder function to unsigned calculate */

/**
 *  @}
 */
#endif

/**
 *  @}
 */ 

/**
 *  @}
 */

/**
 *  @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __MG32x02z_GPL_MID_H */

/************** (C) COPYRIGHT megawin Technology Co., Ltd. *****END OF FILE****/


