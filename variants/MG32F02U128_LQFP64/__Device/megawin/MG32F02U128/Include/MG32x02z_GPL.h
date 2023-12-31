/**
 ******************************************************************************
 *
 * @file        MG32x02z_GPL.h
 *
 * @brief       MG32x02z GPL Register Definitions Header File
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.22 (Register File Date : 2022_0815)
 * @date        2022/08/25 15:14 (H File Generated Date)
 * @author      HeadCodeGen V1.42
 * @copyright   Copyright (c) 2022 Megawin Technology Co., Ltd.
 *              All rights reserved.
 *
 * Important!   This file is generated by code generator. Do not edit!
 *
 ******************************************************************************
 */

#ifndef _MG32x02z_GPL_H
#define _MG32x02z_GPL_H
#define _MG32x02z_GPL_H_VER                         122     /*!< File Version */

#include "MG32x02z.h"

#if !(_MG32x02z_H_VER == _MG32x02z_GPL_H_VER)
    #error "_MG32x02z_GPL_H - Main/Module Version Mismatch !"
#endif

/**
 ******************************************************************************
 *
 * @struct      GPL_Struct
 *              GPL  [Module Structure Typedef]
 *
 ******************************************************************************
 */
typedef struct
{
    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
        struct
        {
            __I  uint8_t                :1;     //[0] 
            __I  uint8_t  DIVCF         :1;     //[1] Divider calculation complete flag.
                                        //0 = Not : divider calculating
                                        //1 = Complete : calculation complete
            __I  uint8_t  DIVZEF        :1;     //[2] Divider division by zero error flag.
                                        //0 = Normal : divisor is not zero
                                        //1 = Happened : divisor is zero
            __I  uint8_t                :5;     //[7..3] 
            __I  uint8_t  PAR8_OUT      :4;     //[11..8] GPL 8-bit data parity check output.
            __I  uint8_t  PAR16_OUT     :2;     //[13..12] GPL 16-bit data parity check output.
            __I  uint8_t  PAR32_OUT     :1;     //[14] GPL 32-bit data parity check output.
            __I  uint8_t                :1;     //[15] 
            __I  uint16_t               :16;    //[31..16] 
        }MBIT;
    }STA;                               /*!< STA        ~ Offset[0x00]  GPL status register */

    __I uint32_t  RESERVED0[3];         /*!< RESERVED0  ~ Offset[0x04]  Reserved */

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
        struct
        {
            __I  uint8_t                :1;     //[0] 
            __IO uint8_t  BEND_EN       :1;     //[1] Data byte Big/little endian change mode enable for 32-bit range.
                                        //0 = Disable
                                        //1 = Enable
            __IO uint8_t  BREV_MDS      :2;     //[3..2] Data bit order reverse change mode select.
                                        //0x0 = Disable
                                        //0x1 = 8bit : 8-bit range bit order reverse
                                        //0x2 = 16bit : 16-bit range bit order reverse
                                        //0x3 = 32bit : 32-bit range bit order reverse
            __IO uint8_t  BEND16_EN     :1;     //[4] Data byte Big/little endian change mode enable for 16-bit range.
                                        //0 = Disable
                                        //1 = Enable
            __I  uint8_t                :1;     //[5] 
            __IO uint8_t  IN_INV        :1;     //[6] Inverse input data enable.
                                        //0 = Disable
                                        //1 = Enable
            __I  uint8_t                :1;     //[7] 
            __I  uint8_t                :2;     //[9..8] 
            __IO uint8_t  PAR_POL       :1;     //[10] Data parity check polarity select.
                                        //0 = Even
                                        //1 = Odd
            __I  uint8_t                :5;     //[15..11] 
            __I  uint8_t                :8;     //[23..16] 
            __I  uint8_t                :6;     //[29..24] 
            __I  uint8_t                :1;     //[30] 
            __IO uint8_t  DMA_EN        :1;     //[31] Direct memory access enable bit
                                        //0 = Disable
                                        //1 = Enable
        }MBIT;
    }CR0;                               /*!< CR0        ~ Offset[0x10]  GPL control register 0 */

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
        struct
        {
            __IO uint8_t  CRC_EN        :1;     //[0] CRC function enable bit.
                                        //0 = Disable
                                        //1 = Enable
            __I  uint8_t                :1;     //[1] 
            __IO uint8_t  CRC_MDS       :2;     //[3..2] CRC mode select.
                                        //0x0 = CCITT16 : polynomial 0x1021
                                        //0x1 = CRC8 : polynomial 0x07
                                        //0x2 = CRC16 : polynomial 0x8005
                                        //0x3 = CRC32 : polynomial 0x4C11DB7
            __IO uint8_t  CRC_DSIZE     :2;     //[5..4] CRC operation data size
                                        //0x0 = 8bit
                                        //0x1 = 16bit
                                        //0x2 = 32bit
                                        //0x3 = Reserved
            __IO uint8_t  CRC_BREV      :2;     //[7..6] CRC data output bit order reverse change mode select.
                                        //0x0 = Disable
                                        //0x1 = 8bit : 8-bit range bit order reverse
                                        //0x2 = 16bit : 16-bit range bit order reverse
                                        //0x3 = 32bit : 32-bit range bit order reverse
            __I  uint8_t                :2;     //[9..8] 
            __I  uint8_t                :6;     //[15..10] 
            __IO uint8_t  DIV_TYPE      :1;     //[16] Hardware divider division type selection
                                        //0 = Unsigned : unsigned value division
                                        //1 = Signed : value with two's complemented
            __I  uint8_t                :7;     //[23..17] 
            __IO uint8_t  DIV_START     :1;     //[24] Hardware divider start calculation control bit
                                        //0 = No : no operation
                                        //1 = Start : start division
            __I  uint8_t                :7;     //[31..25] 
        }MBIT;
    }CR1;                               /*!< CR1        ~ Offset[0x14]  GPL control register 1 */

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
        struct
        {
            __IO uint32_t DIN           :32;    //[31..0] GPL data input register
        }MBIT;
    }DIN;                               /*!< DIN        ~ Offset[0x18]  GPL data input register */

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
        struct
        {
            __I  uint32_t DOUT          :32;    //[31..0] GPL data output register.
        }MBIT;
    }DOUT;                              /*!< DOUT       ~ Offset[0x1C]  GPL data output register */

    __I uint32_t  RESERVED1;            /*!< RESERVED1  ~ Offset[0x20]  Reserved */

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
        struct
        {
            __IO uint32_t CRC_INIT      :32;    //[31..0] Programmable initial CRC value
        }MBIT;
    }CRCINIT;                           /*!< CRCINIT    ~ Offset[0x24]  GPL CRC initial register */

    __I uint32_t  RESERVED2[2];         /*!< RESERVED2  ~ Offset[0x28]  Reserved */

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
        struct
        {
            __IO uint32_t DIVIDEND      :32;    //[31..0] This register is used to specify the dividend value for the division calculation.
        }MBIT;
    }DIVD;                              /*!< DIVD       ~ Offset[0x30]  GPL divider dividend data register */

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
        struct
        {
            __IO uint32_t DIVISOR       :32;    //[31..0] This register is used to specify the divisor value for the division calculation.
        }MBIT;
    }DIVS;                              /*!< DIVS       ~ Offset[0x34]  GPL divider divisor data register */

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
        struct
        {
            __I  uint32_t QUOTIENT      :32;    //[31..0] This register is used to record the quotient value for the division calculation.
        }MBIT;
    }QUT;                               /*!< QUT        ~ Offset[0x38]  GPL divider quotient data register */

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
        struct
        {
            __I  uint32_t REMAINDER     :32;    //[31..0] This register is used to record the remainder value for the division calculation.
        }MBIT;
    }REM;                               /*!< REM        ~ Offset[0x3C]  GPL divider remainder data register */

} GPL_Struct;

/**
 ******************************************************************************
 *
 * @name        GPL  [Base Address/Type]
 *
 ******************************************************************************
 */
///@{
#define GPL_Base                        ((uint32_t)0x4B000000)              /*!< General Purpose Logic Control */
#define GPL                             ((GPL_Struct*) GPL_Base)
///@}

/**
 ******************************************************************************
 *
 * @name        GPL  [Register Definitions]
 *
 ******************************************************************************
 */
/**
 ******************************************************************************
 * @name        GPL_STA  [register's definitions]
 *              Offset[0x00]  GPL status register (0x4B000000)
 ******************************************************************************
 */
///@{
#define GPL_STA_default                             ((uint32_t)0x00000000)  /*!< Reg Reset Default Value */

/* Bit fields of GPL_STA */
#define GPL_STA_PAR32_OUT_mask_w                    ((uint32_t)0x00004000)  /*!< Bit Mask of 32bit */
#define GPL_STA_PAR32_OUT_mask_h0                   ((uint16_t)0x4000)      /*!< Bit Mask of 16bit */
#define GPL_STA_PAR32_OUT_mask_b1                   ((uint8_t )0x40)        /*!< Bit Mask of 8bit */
#define GPL_STA_PAR32_OUT_shift_w                   (14)                    /*!< Bit Shift of 32bit */
#define GPL_STA_PAR32_OUT_shift_h0                  (14)                    /*!< Bit Shift of 16bit */
#define GPL_STA_PAR32_OUT_shift_b1                  (6)                     /*!< Bit Shift of 8bit */

#define GPL_STA_PAR16_OUT_mask_w                    ((uint32_t)0x00003000)  /*!< Bit Mask of 32bit */
#define GPL_STA_PAR16_OUT_mask_h0                   ((uint16_t)0x3000)      /*!< Bit Mask of 16bit */
#define GPL_STA_PAR16_OUT_mask_b1                   ((uint8_t )0x30)        /*!< Bit Mask of 8bit */
#define GPL_STA_PAR16_OUT_shift_w                   (12)                    /*!< Bit Shift of 32bit */
#define GPL_STA_PAR16_OUT_shift_h0                  (12)                    /*!< Bit Shift of 16bit */
#define GPL_STA_PAR16_OUT_shift_b1                  (4)                     /*!< Bit Shift of 8bit */

#define GPL_STA_PAR8_OUT_mask_w                     ((uint32_t)0x00000F00)  /*!< Bit Mask of 32bit */
#define GPL_STA_PAR8_OUT_mask_h0                    ((uint16_t)0x0F00)      /*!< Bit Mask of 16bit */
#define GPL_STA_PAR8_OUT_mask_b1                    ((uint8_t )0x0F)        /*!< Bit Mask of 8bit */
#define GPL_STA_PAR8_OUT_shift_w                    (8)                     /*!< Bit Shift of 32bit */
#define GPL_STA_PAR8_OUT_shift_h0                   (8)                     /*!< Bit Shift of 16bit */
#define GPL_STA_PAR8_OUT_shift_b1                   (0)                     /*!< Bit Shift of 8bit */

#define GPL_STA_DIVZEF_mask_w                       ((uint32_t)0x00000004)  /*!< Bit Mask of 32bit */
#define GPL_STA_DIVZEF_mask_h0                      ((uint16_t)0x0004)      /*!< Bit Mask of 16bit */
#define GPL_STA_DIVZEF_mask_b0                      ((uint8_t )0x04)        /*!< Bit Mask of 8bit */
#define GPL_STA_DIVZEF_normal_w                     ((uint32_t)0x00000000)  /*!< Bit Value =(0):Normal of 32bit */
#define GPL_STA_DIVZEF_normal_h0                    ((uint16_t)0x0000)      /*!< Bit Value =(0):Normal of 16bit */
#define GPL_STA_DIVZEF_normal_b0                    ((uint8_t )0x00)        /*!< Bit Value =(0):Normal of 8bit */
#define GPL_STA_DIVZEF_happened_w                   ((uint32_t)0x00000004)  /*!< Bit Value =(1):Happened of 32bit */
#define GPL_STA_DIVZEF_happened_h0                  ((uint16_t)0x0004)      /*!< Bit Value =(1):Happened of 16bit */
#define GPL_STA_DIVZEF_happened_b0                  ((uint8_t )0x04)        /*!< Bit Value =(1):Happened of 8bit */

#define GPL_STA_DIVCF_mask_w                        ((uint32_t)0x00000002)  /*!< Bit Mask of 32bit */
#define GPL_STA_DIVCF_mask_h0                       ((uint16_t)0x0002)      /*!< Bit Mask of 16bit */
#define GPL_STA_DIVCF_mask_b0                       ((uint8_t )0x02)        /*!< Bit Mask of 8bit */
#define GPL_STA_DIVCF_not_w                         ((uint32_t)0x00000000)  /*!< Bit Value =(0):Not of 32bit */
#define GPL_STA_DIVCF_not_h0                        ((uint16_t)0x0000)      /*!< Bit Value =(0):Not of 16bit */
#define GPL_STA_DIVCF_not_b0                        ((uint8_t )0x00)        /*!< Bit Value =(0):Not of 8bit */
#define GPL_STA_DIVCF_complete_w                    ((uint32_t)0x00000002)  /*!< Bit Value =(1):Complete of 32bit */
#define GPL_STA_DIVCF_complete_h0                   ((uint16_t)0x0002)      /*!< Bit Value =(1):Complete of 16bit */
#define GPL_STA_DIVCF_complete_b0                   ((uint8_t )0x02)        /*!< Bit Value =(1):Complete of 8bit */

///@}
/**
 ******************************************************************************
 * @name        GPL_CR0  [register's definitions]
 *              Offset[0x10]  GPL control register 0 (0x4B000010)
 ******************************************************************************
 */
///@{
#define GPL_CR0_default                             ((uint32_t)0x00000000)  /*!< Reg Reset Default Value */

/* Bit fields of GPL_CR0 */
#define GPL_CR0_DMA_EN_mask_w                       ((uint32_t)0x80000000)  /*!< Bit Mask of 32bit */
#define GPL_CR0_DMA_EN_mask_h1                      ((uint16_t)0x8000)      /*!< Bit Mask of 16bit */
#define GPL_CR0_DMA_EN_mask_b3                      ((uint8_t )0x80)        /*!< Bit Mask of 8bit */
#define GPL_CR0_DMA_EN_disable_w                    ((uint32_t)0x00000000)  /*!< Bit Value =(0):Disable of 32bit */
#define GPL_CR0_DMA_EN_disable_h1                   ((uint16_t)0x0000)      /*!< Bit Value =(0):Disable of 16bit */
#define GPL_CR0_DMA_EN_disable_b3                   ((uint8_t )0x00)        /*!< Bit Value =(0):Disable of 8bit */
#define GPL_CR0_DMA_EN_enable_w                     ((uint32_t)0x80000000)  /*!< Bit Value =(1):Enable of 32bit */
#define GPL_CR0_DMA_EN_enable_h1                    ((uint16_t)0x8000)      /*!< Bit Value =(1):Enable of 16bit */
#define GPL_CR0_DMA_EN_enable_b3                    ((uint8_t )0x80)        /*!< Bit Value =(1):Enable of 8bit */

#define GPL_CR0_PAR_POL_mask_w                      ((uint32_t)0x00000400)  /*!< Bit Mask of 32bit */
#define GPL_CR0_PAR_POL_mask_h0                     ((uint16_t)0x0400)      /*!< Bit Mask of 16bit */
#define GPL_CR0_PAR_POL_mask_b1                     ((uint8_t )0x04)        /*!< Bit Mask of 8bit */
#define GPL_CR0_PAR_POL_even_w                      ((uint32_t)0x00000000)  /*!< Bit Value =(0):Even of 32bit */
#define GPL_CR0_PAR_POL_even_h0                     ((uint16_t)0x0000)      /*!< Bit Value =(0):Even of 16bit */
#define GPL_CR0_PAR_POL_even_b1                     ((uint8_t )0x00)        /*!< Bit Value =(0):Even of 8bit */
#define GPL_CR0_PAR_POL_odd_w                       ((uint32_t)0x00000400)  /*!< Bit Value =(1):Odd of 32bit */
#define GPL_CR0_PAR_POL_odd_h0                      ((uint16_t)0x0400)      /*!< Bit Value =(1):Odd of 16bit */
#define GPL_CR0_PAR_POL_odd_b1                      ((uint8_t )0x04)        /*!< Bit Value =(1):Odd of 8bit */

#define GPL_CR0_IN_INV_mask_w                       ((uint32_t)0x00000040)  /*!< Bit Mask of 32bit */
#define GPL_CR0_IN_INV_mask_h0                      ((uint16_t)0x0040)      /*!< Bit Mask of 16bit */
#define GPL_CR0_IN_INV_mask_b0                      ((uint8_t )0x40)        /*!< Bit Mask of 8bit */
#define GPL_CR0_IN_INV_disable_w                    ((uint32_t)0x00000000)  /*!< Bit Value =(0):Disable of 32bit */
#define GPL_CR0_IN_INV_disable_h0                   ((uint16_t)0x0000)      /*!< Bit Value =(0):Disable of 16bit */
#define GPL_CR0_IN_INV_disable_b0                   ((uint8_t )0x00)        /*!< Bit Value =(0):Disable of 8bit */
#define GPL_CR0_IN_INV_enable_w                     ((uint32_t)0x00000040)  /*!< Bit Value =(1):Enable of 32bit */
#define GPL_CR0_IN_INV_enable_h0                    ((uint16_t)0x0040)      /*!< Bit Value =(1):Enable of 16bit */
#define GPL_CR0_IN_INV_enable_b0                    ((uint8_t )0x40)        /*!< Bit Value =(1):Enable of 8bit */

#define GPL_CR0_BEND16_EN_mask_w                    ((uint32_t)0x00000010)  /*!< Bit Mask of 32bit */
#define GPL_CR0_BEND16_EN_mask_h0                   ((uint16_t)0x0010)      /*!< Bit Mask of 16bit */
#define GPL_CR0_BEND16_EN_mask_b0                   ((uint8_t )0x10)        /*!< Bit Mask of 8bit */
#define GPL_CR0_BEND16_EN_disable_w                 ((uint32_t)0x00000000)  /*!< Bit Value =(0):Disable of 32bit */
#define GPL_CR0_BEND16_EN_disable_h0                ((uint16_t)0x0000)      /*!< Bit Value =(0):Disable of 16bit */
#define GPL_CR0_BEND16_EN_disable_b0                ((uint8_t )0x00)        /*!< Bit Value =(0):Disable of 8bit */
#define GPL_CR0_BEND16_EN_enable_w                  ((uint32_t)0x00000010)  /*!< Bit Value =(1):Enable of 32bit */
#define GPL_CR0_BEND16_EN_enable_h0                 ((uint16_t)0x0010)      /*!< Bit Value =(1):Enable of 16bit */
#define GPL_CR0_BEND16_EN_enable_b0                 ((uint8_t )0x10)        /*!< Bit Value =(1):Enable of 8bit */

#define GPL_CR0_BREV_MDS_mask_w                     ((uint32_t)0x0000000C)  /*!< Bit Mask of 32bit */
#define GPL_CR0_BREV_MDS_mask_h0                    ((uint16_t)0x000C)      /*!< Bit Mask of 16bit */
#define GPL_CR0_BREV_MDS_mask_b0                    ((uint8_t )0x0C)        /*!< Bit Mask of 8bit */
#define GPL_CR0_BREV_MDS_disable_w                  ((uint32_t)0x00000000)  /*!< Bit Value =(0x0):Disable of 32bit */
#define GPL_CR0_BREV_MDS_disable_h0                 ((uint16_t)0x0000)      /*!< Bit Value =(0x0):Disable of 16bit */
#define GPL_CR0_BREV_MDS_disable_b0                 ((uint8_t )0x00)        /*!< Bit Value =(0x0):Disable of 8bit */
#define GPL_CR0_BREV_MDS_8bit_w                     ((uint32_t)0x00000004)  /*!< Bit Value =(0x1):8bit of 32bit */
#define GPL_CR0_BREV_MDS_8bit_h0                    ((uint16_t)0x0004)      /*!< Bit Value =(0x1):8bit of 16bit */
#define GPL_CR0_BREV_MDS_8bit_b0                    ((uint8_t )0x04)        /*!< Bit Value =(0x1):8bit of 8bit */
#define GPL_CR0_BREV_MDS_16bit_w                    ((uint32_t)0x00000008)  /*!< Bit Value =(0x2):16bit of 32bit */
#define GPL_CR0_BREV_MDS_16bit_h0                   ((uint16_t)0x0008)      /*!< Bit Value =(0x2):16bit of 16bit */
#define GPL_CR0_BREV_MDS_16bit_b0                   ((uint8_t )0x08)        /*!< Bit Value =(0x2):16bit of 8bit */
#define GPL_CR0_BREV_MDS_32bit_w                    ((uint32_t)0x0000000C)  /*!< Bit Value =(0x3):32bit of 32bit */
#define GPL_CR0_BREV_MDS_32bit_h0                   ((uint16_t)0x000C)      /*!< Bit Value =(0x3):32bit of 16bit */
#define GPL_CR0_BREV_MDS_32bit_b0                   ((uint8_t )0x0C)        /*!< Bit Value =(0x3):32bit of 8bit */

#define GPL_CR0_BEND_EN_mask_w                      ((uint32_t)0x00000002)  /*!< Bit Mask of 32bit */
#define GPL_CR0_BEND_EN_mask_h0                     ((uint16_t)0x0002)      /*!< Bit Mask of 16bit */
#define GPL_CR0_BEND_EN_mask_b0                     ((uint8_t )0x02)        /*!< Bit Mask of 8bit */
#define GPL_CR0_BEND_EN_disable_w                   ((uint32_t)0x00000000)  /*!< Bit Value =(0):Disable of 32bit */
#define GPL_CR0_BEND_EN_disable_h0                  ((uint16_t)0x0000)      /*!< Bit Value =(0):Disable of 16bit */
#define GPL_CR0_BEND_EN_disable_b0                  ((uint8_t )0x00)        /*!< Bit Value =(0):Disable of 8bit */
#define GPL_CR0_BEND_EN_enable_w                    ((uint32_t)0x00000002)  /*!< Bit Value =(1):Enable of 32bit */
#define GPL_CR0_BEND_EN_enable_h0                   ((uint16_t)0x0002)      /*!< Bit Value =(1):Enable of 16bit */
#define GPL_CR0_BEND_EN_enable_b0                   ((uint8_t )0x02)        /*!< Bit Value =(1):Enable of 8bit */

///@}
/**
 ******************************************************************************
 * @name        GPL_CR1  [register's definitions]
 *              Offset[0x14]  GPL control register 1 (0x4B000014)
 ******************************************************************************
 */
///@{
#define GPL_CR1_default                             ((uint32_t)0x00000000)  /*!< Reg Reset Default Value */

/* Bit fields of GPL_CR1 */
#define GPL_CR1_DIV_START_mask_w                    ((uint32_t)0x01000000)  /*!< Bit Mask of 32bit */
#define GPL_CR1_DIV_START_mask_h1                   ((uint16_t)0x0100)      /*!< Bit Mask of 16bit */
#define GPL_CR1_DIV_START_mask_b3                   ((uint8_t )0x01)        /*!< Bit Mask of 8bit */
#define GPL_CR1_DIV_START_no_w                      ((uint32_t)0x00000000)  /*!< Bit Value =(0):No of 32bit */
#define GPL_CR1_DIV_START_no_h1                     ((uint16_t)0x0000)      /*!< Bit Value =(0):No of 16bit */
#define GPL_CR1_DIV_START_no_b3                     ((uint8_t )0x00)        /*!< Bit Value =(0):No of 8bit */
#define GPL_CR1_DIV_START_start_w                   ((uint32_t)0x01000000)  /*!< Bit Value =(1):Start of 32bit */
#define GPL_CR1_DIV_START_start_h1                  ((uint16_t)0x0100)      /*!< Bit Value =(1):Start of 16bit */
#define GPL_CR1_DIV_START_start_b3                  ((uint8_t )0x01)        /*!< Bit Value =(1):Start of 8bit */

#define GPL_CR1_DIV_TYPE_mask_w                     ((uint32_t)0x00010000)  /*!< Bit Mask of 32bit */
#define GPL_CR1_DIV_TYPE_mask_h1                    ((uint16_t)0x0001)      /*!< Bit Mask of 16bit */
#define GPL_CR1_DIV_TYPE_mask_b2                    ((uint8_t )0x01)        /*!< Bit Mask of 8bit */
#define GPL_CR1_DIV_TYPE_unsigned_w                 ((uint32_t)0x00000000)  /*!< Bit Value =(0):Unsigned of 32bit */
#define GPL_CR1_DIV_TYPE_unsigned_h1                ((uint16_t)0x0000)      /*!< Bit Value =(0):Unsigned of 16bit */
#define GPL_CR1_DIV_TYPE_unsigned_b2                ((uint8_t )0x00)        /*!< Bit Value =(0):Unsigned of 8bit */
#define GPL_CR1_DIV_TYPE_signed_w                   ((uint32_t)0x00010000)  /*!< Bit Value =(1):Signed of 32bit */
#define GPL_CR1_DIV_TYPE_signed_h1                  ((uint16_t)0x0001)      /*!< Bit Value =(1):Signed of 16bit */
#define GPL_CR1_DIV_TYPE_signed_b2                  ((uint8_t )0x01)        /*!< Bit Value =(1):Signed of 8bit */

#define GPL_CR1_CRC_BREV_mask_w                     ((uint32_t)0x000000C0)  /*!< Bit Mask of 32bit */
#define GPL_CR1_CRC_BREV_mask_h0                    ((uint16_t)0x00C0)      /*!< Bit Mask of 16bit */
#define GPL_CR1_CRC_BREV_mask_b0                    ((uint8_t )0xC0)        /*!< Bit Mask of 8bit */
#define GPL_CR1_CRC_BREV_disable_w                  ((uint32_t)0x00000000)  /*!< Bit Value =(0x0):Disable of 32bit */
#define GPL_CR1_CRC_BREV_disable_h0                 ((uint16_t)0x0000)      /*!< Bit Value =(0x0):Disable of 16bit */
#define GPL_CR1_CRC_BREV_disable_b0                 ((uint8_t )0x00)        /*!< Bit Value =(0x0):Disable of 8bit */
#define GPL_CR1_CRC_BREV_8bit_w                     ((uint32_t)0x00000040)  /*!< Bit Value =(0x1):8bit of 32bit */
#define GPL_CR1_CRC_BREV_8bit_h0                    ((uint16_t)0x0040)      /*!< Bit Value =(0x1):8bit of 16bit */
#define GPL_CR1_CRC_BREV_8bit_b0                    ((uint8_t )0x40)        /*!< Bit Value =(0x1):8bit of 8bit */
#define GPL_CR1_CRC_BREV_16bit_w                    ((uint32_t)0x00000080)  /*!< Bit Value =(0x2):16bit of 32bit */
#define GPL_CR1_CRC_BREV_16bit_h0                   ((uint16_t)0x0080)      /*!< Bit Value =(0x2):16bit of 16bit */
#define GPL_CR1_CRC_BREV_16bit_b0                   ((uint8_t )0x80)        /*!< Bit Value =(0x2):16bit of 8bit */
#define GPL_CR1_CRC_BREV_32bit_w                    ((uint32_t)0x000000C0)  /*!< Bit Value =(0x3):32bit of 32bit */
#define GPL_CR1_CRC_BREV_32bit_h0                   ((uint16_t)0x00C0)      /*!< Bit Value =(0x3):32bit of 16bit */
#define GPL_CR1_CRC_BREV_32bit_b0                   ((uint8_t )0xC0)        /*!< Bit Value =(0x3):32bit of 8bit */

#define GPL_CR1_CRC_DSIZE_mask_w                    ((uint32_t)0x00000030)  /*!< Bit Mask of 32bit */
#define GPL_CR1_CRC_DSIZE_mask_h0                   ((uint16_t)0x0030)      /*!< Bit Mask of 16bit */
#define GPL_CR1_CRC_DSIZE_mask_b0                   ((uint8_t )0x30)        /*!< Bit Mask of 8bit */
#define GPL_CR1_CRC_DSIZE_8bit_w                    ((uint32_t)0x00000000)  /*!< Bit Value =(0x0):8bit of 32bit */
#define GPL_CR1_CRC_DSIZE_8bit_h0                   ((uint16_t)0x0000)      /*!< Bit Value =(0x0):8bit of 16bit */
#define GPL_CR1_CRC_DSIZE_8bit_b0                   ((uint8_t )0x00)        /*!< Bit Value =(0x0):8bit of 8bit */
#define GPL_CR1_CRC_DSIZE_16bit_w                   ((uint32_t)0x00000010)  /*!< Bit Value =(0x1):16bit of 32bit */
#define GPL_CR1_CRC_DSIZE_16bit_h0                  ((uint16_t)0x0010)      /*!< Bit Value =(0x1):16bit of 16bit */
#define GPL_CR1_CRC_DSIZE_16bit_b0                  ((uint8_t )0x10)        /*!< Bit Value =(0x1):16bit of 8bit */
#define GPL_CR1_CRC_DSIZE_32bit_w                   ((uint32_t)0x00000020)  /*!< Bit Value =(0x2):32bit of 32bit */
#define GPL_CR1_CRC_DSIZE_32bit_h0                  ((uint16_t)0x0020)      /*!< Bit Value =(0x2):32bit of 16bit */
#define GPL_CR1_CRC_DSIZE_32bit_b0                  ((uint8_t )0x20)        /*!< Bit Value =(0x2):32bit of 8bit */

#define GPL_CR1_CRC_MDS_mask_w                      ((uint32_t)0x0000000C)  /*!< Bit Mask of 32bit */
#define GPL_CR1_CRC_MDS_mask_h0                     ((uint16_t)0x000C)      /*!< Bit Mask of 16bit */
#define GPL_CR1_CRC_MDS_mask_b0                     ((uint8_t )0x0C)        /*!< Bit Mask of 8bit */
#define GPL_CR1_CRC_MDS_ccitt16_w                   ((uint32_t)0x00000000)  /*!< Bit Value =(0x0):CCITT16 of 32bit */
#define GPL_CR1_CRC_MDS_ccitt16_h0                  ((uint16_t)0x0000)      /*!< Bit Value =(0x0):CCITT16 of 16bit */
#define GPL_CR1_CRC_MDS_ccitt16_b0                  ((uint8_t )0x00)        /*!< Bit Value =(0x0):CCITT16 of 8bit */
#define GPL_CR1_CRC_MDS_crc8_w                      ((uint32_t)0x00000004)  /*!< Bit Value =(0x1):CRC8 of 32bit */
#define GPL_CR1_CRC_MDS_crc8_h0                     ((uint16_t)0x0004)      /*!< Bit Value =(0x1):CRC8 of 16bit */
#define GPL_CR1_CRC_MDS_crc8_b0                     ((uint8_t )0x04)        /*!< Bit Value =(0x1):CRC8 of 8bit */
#define GPL_CR1_CRC_MDS_crc16_w                     ((uint32_t)0x00000008)  /*!< Bit Value =(0x2):CRC16 of 32bit */
#define GPL_CR1_CRC_MDS_crc16_h0                    ((uint16_t)0x0008)      /*!< Bit Value =(0x2):CRC16 of 16bit */
#define GPL_CR1_CRC_MDS_crc16_b0                    ((uint8_t )0x08)        /*!< Bit Value =(0x2):CRC16 of 8bit */
#define GPL_CR1_CRC_MDS_crc32_w                     ((uint32_t)0x0000000C)  /*!< Bit Value =(0x3):CRC32 of 32bit */
#define GPL_CR1_CRC_MDS_crc32_h0                    ((uint16_t)0x000C)      /*!< Bit Value =(0x3):CRC32 of 16bit */
#define GPL_CR1_CRC_MDS_crc32_b0                    ((uint8_t )0x0C)        /*!< Bit Value =(0x3):CRC32 of 8bit */

#define GPL_CR1_CRC_EN_mask_w                       ((uint32_t)0x00000001)  /*!< Bit Mask of 32bit */
#define GPL_CR1_CRC_EN_mask_h0                      ((uint16_t)0x0001)      /*!< Bit Mask of 16bit */
#define GPL_CR1_CRC_EN_mask_b0                      ((uint8_t )0x01)        /*!< Bit Mask of 8bit */
#define GPL_CR1_CRC_EN_disable_w                    ((uint32_t)0x00000000)  /*!< Bit Value =(0):Disable of 32bit */
#define GPL_CR1_CRC_EN_disable_h0                   ((uint16_t)0x0000)      /*!< Bit Value =(0):Disable of 16bit */
#define GPL_CR1_CRC_EN_disable_b0                   ((uint8_t )0x00)        /*!< Bit Value =(0):Disable of 8bit */
#define GPL_CR1_CRC_EN_enable_w                     ((uint32_t)0x00000001)  /*!< Bit Value =(1):Enable of 32bit */
#define GPL_CR1_CRC_EN_enable_h0                    ((uint16_t)0x0001)      /*!< Bit Value =(1):Enable of 16bit */
#define GPL_CR1_CRC_EN_enable_b0                    ((uint8_t )0x01)        /*!< Bit Value =(1):Enable of 8bit */

///@}
/**
 ******************************************************************************
 * @name        GPL_DIN  [register's definitions]
 *              Offset[0x18]  GPL data input register (0x4B000018)
 ******************************************************************************
 */
///@{
#define GPL_DIN_default                             ((uint32_t)0x00000000)  /*!< Reg Reset Default Value */

/* Bit fields of GPL_DIN */
#define GPL_DIN_DIN_mask_w                          ((uint32_t)0xFFFFFFFF)  /*!< Bit Mask of 32bit */
#define GPL_DIN_DIN_shift_w                         (0)                     /*!< Bit Shift of 32bit */
#define GPL_DIN_DIN_shift_h0                        (0)                     /*!< Bit Shift of 16bit */
#define GPL_DIN_DIN_shift_b0                        (0)                     /*!< Bit Shift of 8bit */

///@}
/**
 ******************************************************************************
 * @name        GPL_DOUT  [register's definitions]
 *              Offset[0x1C]  GPL data output register (0x4B00001C)
 ******************************************************************************
 */
///@{
#define GPL_DOUT_default                            ((uint32_t)0x00000000)  /*!< Reg Reset Default Value */

/* Bit fields of GPL_DOUT */
#define GPL_DOUT_DOUT_mask_w                        ((uint32_t)0xFFFFFFFF)  /*!< Bit Mask of 32bit */
#define GPL_DOUT_DOUT_shift_w                       (0)                     /*!< Bit Shift of 32bit */
#define GPL_DOUT_DOUT_shift_h0                      (0)                     /*!< Bit Shift of 16bit */
#define GPL_DOUT_DOUT_shift_b0                      (0)                     /*!< Bit Shift of 8bit */

///@}
/**
 ******************************************************************************
 * @name        GPL_CRCINIT  [register's definitions]
 *              Offset[0x24]  GPL CRC initial register (0x4B000024)
 ******************************************************************************
 */
///@{
#define GPL_CRCINIT_default                         ((uint32_t)0x00000000)  /*!< Reg Reset Default Value */

/* Bit fields of GPL_CRCINIT */
#define GPL_CRCINIT_CRC_INIT_mask_w                 ((uint32_t)0xFFFFFFFF)  /*!< Bit Mask of 32bit */
#define GPL_CRCINIT_CRC_INIT_shift_w                (0)                     /*!< Bit Shift of 32bit */
#define GPL_CRCINIT_CRC_INIT_shift_h0               (0)                     /*!< Bit Shift of 16bit */
#define GPL_CRCINIT_CRC_INIT_shift_b0               (0)                     /*!< Bit Shift of 8bit */

///@}
/**
 ******************************************************************************
 * @name        GPL_DIVD  [register's definitions]
 *              Offset[0x30]  GPL divider dividend data register (0x4B000030)
 ******************************************************************************
 */
///@{
#define GPL_DIVD_default                            ((uint32_t)0x00000000)  /*!< Reg Reset Default Value */

/* Bit fields of GPL_DIVD */
#define GPL_DIVD_DIVIDEND_mask_w                    ((uint32_t)0xFFFFFFFF)  /*!< Bit Mask of 32bit */
#define GPL_DIVD_DIVIDEND_shift_w                   (0)                     /*!< Bit Shift of 32bit */
#define GPL_DIVD_DIVIDEND_shift_h0                  (0)                     /*!< Bit Shift of 16bit */
#define GPL_DIVD_DIVIDEND_shift_b0                  (0)                     /*!< Bit Shift of 8bit */

///@}
/**
 ******************************************************************************
 * @name        GPL_DIVS  [register's definitions]
 *              Offset[0x34]  GPL divider divisor data register (0x4B000034)
 ******************************************************************************
 */
///@{
#define GPL_DIVS_default                            ((uint32_t)0x00000000)  /*!< Reg Reset Default Value */

/* Bit fields of GPL_DIVS */
#define GPL_DIVS_DIVISOR_mask_w                     ((uint32_t)0xFFFFFFFF)  /*!< Bit Mask of 32bit */
#define GPL_DIVS_DIVISOR_shift_w                    (0)                     /*!< Bit Shift of 32bit */
#define GPL_DIVS_DIVISOR_shift_h0                   (0)                     /*!< Bit Shift of 16bit */
#define GPL_DIVS_DIVISOR_shift_b0                   (0)                     /*!< Bit Shift of 8bit */

///@}
/**
 ******************************************************************************
 * @name        GPL_QUT  [register's definitions]
 *              Offset[0x38]  GPL divider quotient data register (0x4B000038)
 ******************************************************************************
 */
///@{
#define GPL_QUT_default                             ((uint32_t)0x00000000)  /*!< Reg Reset Default Value */

/* Bit fields of GPL_QUT */
#define GPL_QUT_QUOTIENT_mask_w                     ((uint32_t)0xFFFFFFFF)  /*!< Bit Mask of 32bit */
#define GPL_QUT_QUOTIENT_shift_w                    (0)                     /*!< Bit Shift of 32bit */
#define GPL_QUT_QUOTIENT_shift_h0                   (0)                     /*!< Bit Shift of 16bit */
#define GPL_QUT_QUOTIENT_shift_b0                   (0)                     /*!< Bit Shift of 8bit */

///@}
/**
 ******************************************************************************
 * @name        GPL_REM  [register's definitions]
 *              Offset[0x3C]  GPL divider remainder data register (0x4B00003C)
 ******************************************************************************
 */
///@{
#define GPL_REM_default                             ((uint32_t)0x00000000)  /*!< Reg Reset Default Value */

/* Bit fields of GPL_REM */
#define GPL_REM_REMAINDER_mask_w                    ((uint32_t)0xFFFFFFFF)  /*!< Bit Mask of 32bit */
#define GPL_REM_REMAINDER_shift_w                   (0)                     /*!< Bit Shift of 32bit */
#define GPL_REM_REMAINDER_shift_h0                  (0)                     /*!< Bit Shift of 16bit */
#define GPL_REM_REMAINDER_shift_b0                  (0)                     /*!< Bit Shift of 8bit */

///@}

#endif  // _MG32x02z_GPL_H

/*----------------------------------------------------------------------------*/
/*                         End of file MG32x02z_GPL.h                         */
/*----------------------------------------------------------------------------*/
