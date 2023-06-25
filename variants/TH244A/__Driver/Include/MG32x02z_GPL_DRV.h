/**
 ******************************************************************************
 *
 * @file        MG32x02z_GPL_DRV.h
 *
 * @brief       This is the C code format driver head file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.16
 * @date        2021/07/13
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
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



#ifndef __MG32x02z_GPL_DRV_H
#define __MG32x02z_GPL_DRV_H
//#define _MG32x02z_GPL_DRV_H_VER                            0.01



/* Includes ------------------------------------------------------------------*/
#include "MG32x02z__Common_DRV.h"
#include "MG32x02z_GPL.h" 

/** 
 * @name    Parity
 *
 */ 
///@{ 

/**
  * @brief  Parity Setting
  */

#define GPL_PARITY_MASK          GPL_CR0_PAR_POL_mask_w
#define GPL_PARITY_EVEN          GPL_CR0_PAR_POL_even_w
#define GPL_PARITY_ODD           GPL_CR0_PAR_POL_odd_w
#define IS_GPL_PARITY(SELECT) (((SELECT) == GPL_PARITY_MASK) || \
                               ((SELECT) == GPL_PARITY_EVEN) || \
                               ((SELECT) == GPL_PARITY_ODD))



/** @brief  Parity Output
  */

#define GPL_FLAG_MASK               (GPL_STA_PAR32_OUT_mask_w | GPL_STA_PAR16_OUT_mask_w | GPL_STA_PAR8_OUT_mask_w)
#define GPL_FLAG_PARITY32           GPL_STA_PAR32_OUT_mask_w
#define GPL_FLAG_PARITY16_ALL       GPL_STA_PAR16_OUT_mask_w
#define GPL_FLAG_PARITY16_LOW       0x00010000 
#define GPL_FLAG_PARITY16_HIGH      0x00020000
#define GPL_FLAG_PARITY8_ALL        GPL_STA_PAR8_OUT_mask_w
#define GPL_FLAG_PARITY8_BYTE_0     0x00000100
#define GPL_FLAG_PARITY8_BYTE_1     0x00000200
#define GPL_FLAG_PARITY8_BYTE_2     0x00000400
#define GPL_FLAG_PARITY8_BYTE_3     0x00000800
#define IS_GPL_FLAG(FLAG) (((FLAG) == GPL_FLAG_MASK) || \
                           ((FLAG) == GPL_FLAG_PARITY32) || \
                           ((FLAG) == GPL_FLAG_PARITY16_ALL) || \
                           ((FLAG) == GPL_FLAG_PARITY16_LOW) || \
                           ((FLAG) == GPL_FLAG_PARITY16_HIGH) || \
                           ((FLAG) == GPL_FLAG_PARITY8_ALL) || \
                           ((FLAG) == GPL_FLAG_PARITY8_BYTE_0) || \
                           ((FLAG) == GPL_FLAG_PARITY8_BYTE_1) || \
                           ((FLAG) == GPL_FLAG_PARITY8_BYTE_2) || \
                           ((FLAG) == GPL_FLAG_PARITY8_BYTE_3))
///@}


/** 
 * @name    INVERSE Data
 *
 */ 
///@{

/**
  * @brief  Data INVERSE
  */
#define GPL_INVERSE_MASK            GPL_CR0_IN_INV_mask_w
#define GPL_INVERSE_DISABLE         GPL_CR0_IN_INV_disable_w
#define GPL_INVERSE_ENABLE          GPL_CR0_IN_INV_enable_w
#define IS_GPL_INVERSE(INVERSE) (((INVERSE) == GPL_INVERSE_MASK) || \
                                 ((INVERSE) == GPL_INVERSE_DISABLE) || \
                                 ((INVERSE) == GPL_INVERSE_ENABLE))
///@}



/** 
 * @name    Order for Byte
 *
 */ 
///@{

/**
  * @brief  Byte Order
  */
#define GPL_BYTE_ORDER_CHANGE_MASK       GPL_CR0_BEND_EN_mask_w
#define GPL_BYTE_ORDER_CHANGE_DISABLE    GPL_CR0_BEND_EN_disable_w
#define GPL_BYTE_ORDER_CHANGE_ENABLE     GPL_CR0_BEND_EN_enable_w
#define IS_GPL_BYTE_ORDER_CHANGE(BYTE_ORDER) (((BYTE_ORDER) == GPL_BYTE_ORDER_CHANGE_MASK) || \
                                              ((BYTE_ORDER) == GPL_BYTE_ORDER_CHANGE_DISABLE) || \
                                              ((BYTE_ORDER) == GPL_BYTE_ORDER_CHANGE_ENABLE))

/**
  * @brief  16-Bits Byte Order
  */
#define GPL_16Bits_BYTE_ORDER_CHANGE_MASK       GPL_CR0_BEND16_EN_mask_w
#define GPL_16Bits_BYTE_ORDER_CHANGE_DISABLE    GPL_CR0_BEND16_EN_disable_w
#define GPL_16Bits_BYTE_ORDER_CHANGE_ENABLE     GPL_CR0_BEND16_EN_enable_w
#define IS_GPL_16Bits_BYTE_ORDER_CHANGE(BYTE_ORDER) (((BYTE_ORDER) == GPL_16Bits_BYTE_ORDER_CHANGE_MASK) || \
                                                     ((BYTE_ORDER) == GPL_16Bits_BYTE_ORDER_CHANGE_DISABLE) || \
                                                     ((BYTE_ORDER) == GPL_16Bits_BYTE_ORDER_CHANGE_ENABLE))

/**
  * @brief  Before Bit Order
  */
#define GPL_BEFORE_BIT_ORDER_MASK         GPL_CR0_BREV_MDS_mask_w
#define GPL_BEFORE_BIT_ORDER_DISABLE      GPL_CR0_BREV_MDS_disable_w
#define GPL_BEFORE_BIT_ORDER_8BITS        GPL_CR0_BREV_MDS_8bit_w
#define GPL_BEFORE_BIT_ORDER_16BITS       GPL_CR0_BREV_MDS_16bit_w
#define GPL_BEFORE_BIT_ORDER_32BITS       GPL_CR0_BREV_MDS_32bit_w
#define IS_GPL_BEFORE_BIT_ORDER(SELECT) (((SELECT) == GPL_BEFORE_BIT_ORDER_MASK) || \
                                         ((SELECT) == GPL_BEFORE_BIT_ORDER_DISABLE) || \
                                         ((SELECT) == GPL_BEFORE_BIT_ORDER_8BITS) || \
                                         ((SELECT) == GPL_BEFORE_BIT_ORDER_16BITS) || \
                                         ((SELECT) == GPL_BEFORE_BIT_ORDER_32BITS))
/**
  * @brief  After Bit Order
  */
#define GPL_AFTER_BIT_ORDER_MASK         GPL_CR1_CRC_BREV_mask_w
#define GPL_AFTER_BIT_ORDER_DISABLE      GPL_CR1_CRC_BREV_disable_w
#define GPL_AFTER_BIT_ORDER_8BITS        GPL_CR1_CRC_BREV_8bit_w
#define GPL_AFTER_BIT_ORDER_16BITS       GPL_CR1_CRC_BREV_16bit_w
#define GPL_AFTER_BIT_ORDER_32BITS       GPL_CR1_CRC_BREV_32bit_w
#define IS_GPL_AFTER_BIT_ORDER(SELECT) (((SELECT) == AFTER_BIT_ORDER_MASK) || \
                                        ((SELECT) == GPL_AFTER_BIT_ORDER_DISABLE) || \
                                        ((SELECT) == GPL_AFTER_BIT_ORDER_8BITS) || \
                                        ((SELECT) == GPL_AFTER_BIT_ORDER_16BITS) || \
                                        ((SELECT) == GPL_AFTER_BIT_ORDER_32BITS))

///@}


/** 
 * @name    CRC
 *
 */ 
///@{

/**
  * @brief  CRC Mode
  */
#define GPL_CRC_MODE_MASK        GPL_CR1_CRC_MDS_mask_w
#define GPL_CRC_MODE_CCITT16     GPL_CR1_CRC_MDS_ccitt16_w  /* 0x1021 */
#define GPL_CRC_MODE_CRC8        GPL_CR1_CRC_MDS_crc8_w       /* 0x07 */
#define GPL_CRC_MODE_CRC16       GPL_CR1_CRC_MDS_crc16_w   /* 0x8005 */
#define GPL_CRC_MODE_CRC32       GPL_CR1_CRC_MDS_crc32_w   /* 0x04C11DB7 */
#define IS_GPL_CRC_MODE(SELECT) (((SELECT) == GPL_CRC_MODE_MASK) || \
                                 ((SELECT) == GPL_CRC_MODE_CCITT16) || \
                                 ((SELECT) == GPL_CRC_MODE_CRC8) || \
                                 ((SELECT) == GPL_CRC_MODE_CRC16) || \
                                 ((SELECT) == GPL_CRC_MODE_CRC32))



/**
  * @brief  CRC Data Size
  */
#define GPL_CRC_DATA_SIZE_MASK       GPL_CR1_CRC_DSIZE_mask_w
#define GPL_CRC_DATA_SIZE_8BITS      GPL_CR1_CRC_DSIZE_8bit_w
#define GPL_CRC_DATA_SIZE_16BITS     GPL_CR1_CRC_DSIZE_16bit_w
#define GPL_CRC_DATA_SIZE_32BITS     GPL_CR1_CRC_DSIZE_32bit_w
#define IS_GPL_CRC_DATA_SIZE_SELECT(SELECT) (((SELECT) == GPL_CRC_DATA_SIZE_MASK) || \
                                             ((SELECT) == GPL_CRC_DATA_SIZE_8BITS) || \
                                             ((SELECT) == GPL_CRC_DATA_SIZE_16BITS) || \
                                             ((SELECT) == GPL_CRC_DATA_SIZE_32BITS))

/**
  * @brief  CRC Enable / Disable
  */
#define GPL_CRC_MASK       GPL_CR1_CRC_EN_mask_w
#define GPL_CRC_DISABLE    GPL_CR1_CRC_EN_disable_w
#define GPL_CRC_ENABLE     GPL_CR1_CRC_EN_enable_w
#define IS_GPL_CRC(CRC) (((CRC) == GPL_CRC_MASK) || \
                         ((CRC) == GPL_CRC_DISABLE) || \
                         ((CRC) == GPL_CRC_ENABLE))

///@}



/**
 * @name    GPL DMA
 *          
 */ 
///@{

/**
  * @brief  DMA Enable / Disable
  */
#define GPL_DMA_MASK       GPL_CR0_DMA_EN_mask_b3
#define GPL_DMA_DISABLE    GPL_CR0_DMA_EN_disable_b3
#define GPL_DMA_ENABLE     GPL_CR0_DMA_EN_enable_b3
#define IS_GPL_DMA(CRC) (((CRC) == GPL_DMA_MASK) || \
                         ((CRC) == GPL_DMA_DISABLE) || \
                         ((CRC) == GPL_DMA_ENABLE))

///@}

#ifdef __cplusplus
 extern "C" {
#endif

/**
 * @name    Inverse
 *          Inverse Enable / Disable
 */ 
///@{
#define __GPL_Inverse_Enable()                                  (GPL->CR0.W |= GPL_INVERSE_ENABLE)
#define __GPL_Inverse_Disable()                                 (GPL->CR0.W &= (~GPL_INVERSE_MASK))
void GPL_Inverse_Cmd(FunctionalState State);
///@}

/** 
 * @name    Parity
 *          Parity Setting 
 */ 
///@{

#define __GPL_ParityCheck_Select(Parity__)                      (GPL->CR0.W = (GPL->CR0.B[1] & (~GPL_PARITY_MASK)) | (Parity__))
#define __GPL_ParityCheck_Odd()                                 (GPL->CR0.W |= GPL_PARITY_ODD)
#define __GPL_ParityCheck_Even()                                (GPL->CR0.W &= (~GPL_PARITY_MASK))
void GPL_ParityCheck_Select(uint32_t Parity);

#define __GPL_GetParityCheckWord(Data__)                        (GPL->DIN.W = (Data__); (GPL->STA.W & GPL_Flag_PAR32)?1:0)
uint8_t GPL_GetParityCheckWord(uint32_t Data);

#define __GPL_GetParityCheckHalfWord_High(Data__)               (GPL->DIN.W = (Data__); (GPL->STA.W & GPL_Flag_PAR_HighHalfWord)?1:0)
uint8_t GPL_GetParityCheckHalfWord_High(uint32_t Data);

#define __GPL_GetParityCheckHalfWord_Low(Data__)                (GPL->DIN.W = (Data__); (GPL->STA.W & GPL_Flag_PAR_LowHalfWord)?1:0)
uint8_t GPL_GetParityCheckHalfWord_Low(uint32_t Data);

#define __GPL_GetParityCheckHalfWord(Data__, HighLow__)         (GPL->DIN.W = (Data__); (HighLow__)?((GPL->STA.W & GPL_Flag_PAR_HighHalfWord)?1:0) : ((GPL->STA.W & GPL_Flag_PAR_LowHalfWord)?1:0))
uint8_t GPL_GetParityCheckHalfWord(uint32_t Data, uint16_t HalfWordX);

#define __GPL_GetParityCheckByte_0(Data__)                      (GPL->DIN.W = (Data__); (GPL->STA.W & GPL_Flag_PAR_Byte0)?1:0)
uint8_t GPL_GetParityCheckByte_0(uint32_t Data);

#define __GPL_GetParityCheckByte_1(Data__)                      (GPL->DIN.W = (Data__); (GPL->STA.W & GPL_Flag_PAR_Byte1)?1:0)
uint8_t GPL_GetParityCheckByte_1(uint32_t Data);

#define __GPL_GetParityCheckByte_2(Data__)                      (GPL->DIN.W = (Data__); (GPL->STA.W & GPL_Flag_PAR_Byte2)?1:0)
uint8_t GPL_GetParityCheckByte_2(uint32_t Data);

#define __GPL_GetParityCheckByte_3(Data__)                      (GPL->DIN.W = (Data__); (GPL->STA.W & GPL_Flag_PAR_Byte3)?1:0)
uint8_t GPL_GetParityCheckByte_3(uint32_t Data);

uint8_t GPL_GetParityCheckByte(uint32_t Data, uint8_t ByteX);

///@}



/**
 * @name    Order
 *          Order Setting
 */ 
///@{
#define __GPL_ByteOrderChange_Enable()                          (GPL->CR0.W |= GPL_BYTE_ORDER_CHANGE_MASK)
#define __GPL_ByteOrderChange_Disable()                         (GPL->CR0.W &= (~GPL_BYTE_ORDER_CHANGE_MASK))
void GPL_ByteOrderChange_Cmd(FunctionalState State);

#if !defined(MG32_1ST)
  #define __GPL_16BitsByteOrderChange_Enable()                  (GPL->CR0.W |= GPL_16Bits_BYTE_ORDER_CHANGE_MASK)
  #define __GPL_16BitsByteOrderChange_Disable()                 (GPL->CR0.W &= (~GPL_16Bits_BYTE_ORDER_CHANGE_MASK))
  void GPL_16BitsByteOrderChange_Cmd(FunctionalState State);
#endif

#define __GPL_BeforeBitOrderChange_Select(SELECT__)             (GPL->CR0.W = (GPL->CR0.W & (~GPL_BEFORE_BIT_ORDER_MASK)) | (SELECT__))
void GPL_BeforeBitOrderChange_Select(uint32_t Select);

#define __GPL_AfterBitOrderChange_Select(SELECT__)              (GPL->CR1.W = (GPL->CR1.W & (~GPL_AFTER_BIT_ORDER_MASK)) | (SELECT__))
void GPL_AfterBitOrderChange_Select(uint32_t Select);
///@}



/**
 * @name    CRC
 *          CRC Setting
 */ 
///@{
#define __GPL_CRC_Mode_Select(SELECT__)                         (GPL->CR1.W = (GPL->CR1.W & (~GPL_CRC_MODE_MASK)) | (SELECT__))
void GPL_CRC_Mode_Select(uint32_t Select);

#define __GPL_CRC_Data_Size_Select(SELECT__)                    (GPL->CR1.W = (GPL->CR1.W & (~GPL_CRC_DATA_SIZE_MASK)) | (SELECT__))
void GPL_CRC_Data_Size_Select(uint32_t Select);

#define __GPL_CRC_SetInitialValue(VALUE__)                      (GPL->CRCINIT.W = (VALUE__))
void GPL_CRC_SetInitValue(uint32_t InitialValue);

#define __GPL_CRC_Enable()                                      (GPL->CR1.W |= GPL_CRC_MASK)
#define __GPL_CRC_Disable()                                     (GPL->CR1.W &= ~GPL_CRC_MASK)
void GPL_CRC_Cmd(FunctionalState State);
///@}



/**
 * @name    Data Input and Calculation Results Output.
 *          
 */ 
///@{
#define __GPL_DataInput(DATA__)                                 (GPL->DIN.W = (uint32_t)(DATA__))
void GPL_DataInput(uint32_t Data);

#define __GPL_GetOutputData()                                   (GPL->DOUT.W)
uint32_t GPL_GetOutputData(void);
///@}



/**
 * @name    GPL DMA
 *          DMA Enable / Disable
 */ 
///@{
#define __GPL_DMA_Enable()                                      GPL->CR0.B[3] |= GPL_CR0_DMA_EN_mask_b3
#define __GPL_DMA_Disable()                                     GPL->CR0.B[3] &= ~GPL_CR0_DMA_EN_mask_b3
void GPL_DMA_Cmd(FunctionalState State);
///@}



/**
 * @name    Flag
 *          Get and Clear Results Flag 
 */ 
///@{
#define __GPL_GetAllFlagStatus()                                (GPL->STA.W)
uint32_t GPL_GetAllFlagStatus(void);

#define __GPL_GetFlagStatus(GPL_FLAG)                           ((GPL->STA.W & (GPL_FLAG)) == (GPL_FLAG))
DRV_Return GPL_GetFlagStatus(uint32_t GPL_FLAG);

#define __GPL_ClearFlag(GPL_FLAG)                               (GPL->STA.W = (GPL_FLAG))
void GPL_ClearFlag(uint32_t GPL_FLAG);
///@}

#ifdef __cplusplus
}
#endif

#endif


