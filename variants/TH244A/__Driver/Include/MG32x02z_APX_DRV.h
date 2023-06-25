/**
 ******************************************************************************
 *
 * @file        MG32x02z_APX_DRV.h
 *
 * @brief       This file contains all the functions prototypes for the APX
 *              firmware library.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.04
 * @date        2022/03/17
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************
 * @par 		Disclaimer 
 *		The Demo software is provided "AS IS"  without any warranty, either 
 *		expressed or implied, including, but not limited to, the implied warranties 
 *		of merchantability and fitness for a particular purpose.  The author will 
 *		not be liable for any special, incidental, consequential or indirect 
 *		damages due to loss of data or any other reason. 
 *		These statements agree with the world wide and local dictated laws about 
 *		authorship and violence against these laws. 
 ******************************************************************************
 ******************************************************************************
 */ 
#ifndef __MG32x02z_APX_DRV_H
#define __MG32x02z_APX_DRV_H
//#define _MG32x02z_APX_DRV_H_VER 0.01



#include "MG32x02z__Common_DRV.h"
#include "MG32x02z_APX.h"
#include "MG32x02z__ExtraStruct.h"


#if defined(MG32_4TH)
/**
 * @brief  	ASB base address config
 *
 */ 
#define APX_ASBChannelCR0_Base          0x5F010050      /*!< ASB channel control register0 base address.*/
#define APX_ASBChannelCR0_RSTTX_SHIFT   1               /*!< ASB_RSTTX shift byte in ASBChannelCR0.*/
#define APX_ASBChannelCR1_Base          0x5F010054      /*!< ASB Channel cotnrol register1 base address.*/
#define APX_ASBChannelPCNT_Base         0x5F010056      /*!< ASB Channel pixel count bass address.*/

/**
 * @brief  	ASB channel control registers - total size define
 *
 */ 
#define APX_ASBChannel_SHIFT            0x08            /*!< Every ASB channel control registers total size (byte)*/

/**
 * @brief  	ASB Channelx control mask define
 *
 */ 
#define ASB_CHANNEL0_CMD_MASK           0x01            /*!< ASB channel0 output switch control mask.*/
#define ASB_CHANNEL1_CMD_MASK           0x02            /*!< ASB channel0 output switch control mask.*/
#define ASB_CHANNEL2_CMD_MASK           0x04            /*!< ASB channel0 output switch control mask.*/
#define ASB_CHANNEL3_CMD_MASK           0x08            /*!< ASB channel0 output switch control mask.*/
#endif 



/**
 * @name	APX_ITSTAFlag
 *   	    APX status flag 
 */ 
//!@{
#define APX_CCL1F       APX_STA_CCL1F_happened_w        /*!< CCL-1 output low-to-high detect flag. */
#define APX_CCL0F       APX_STA_CCL0F_happened_w        /*!< CCL-0 output low-to-high detect flag. */
#if defined(MG32_4TH)
    #define APX_ASB0_TXF    APX_STA_ASB0_TXF_happened_w /*!< ASB channel-0 transmit data threshold low flag. */     
    #define APX_ASB1_TXF    APX_STA_ASB1_TXF_happened_w /*!< ASB channel-1 transmit data threshold low flag. */  
    #define APX_ASB2_TXF    APX_STA_ASB2_TXF_happened_w /*!< ASB channel-2 transmit data threshold low flag. */  
    #define APX_ASB3_TXF    APX_STA_ASB3_TXF_happened_w /*!< ASB channel-3 transmit data threshold low flag. */  

    #define APX_ASB0_TCF    APX_STA_ASB0_TCF_happened_w /*!< ASB channel-0 transmission complete flag. */ 
    #define APX_ASB1_TCF    APX_STA_ASB1_TCF_happened_w /*!< ASB channel-1 transmission complete flag. */ 
    #define APX_ASB2_TCF    APX_STA_ASB2_TCF_happened_w /*!< ASB channel-2 transmission complete flag. */ 
    #define APX_ASB3_TCF    APX_STA_ASB3_TCF_happened_w /*!< ASB channel-3 transmission complete flag. */ 
#endif
//!@}

/**
 * @name	APX_InterruptBitDef
 *   	    APX interrupt bir definition
 */ 
//!@{
#define APX_CCL1_IE     APX_INT_CCL1_IE_enable_w        /*!< CCL-1 output low-to-high detect interrupt enable. */
#define APX_CCL0_IE     APX_INT_CCL0_IE_enable_w        /*!< CCL-0 output low-to-high detect interrupt enable. */
#if defined(MG32_4TH)
    #define APX_ASB0_TIE    APX_INT_ASB0_TIE_enable_w   /*!< ASB channel-0 transmit data register empty interrupt. */
    #define APX_ASB1_TIE    APX_INT_ASB1_TIE_enable_w   /*!< ASB channel-1 transmit data register empty interrupt. */
    #define APX_ASB2_TIE    APX_INT_ASB2_TIE_enable_w   /*!< ASB channel-2 transmit data register empty interrupt. */
    #define APX_ASB3_TIE    APX_INT_ASB3_TIE_enable_w   /*!< ASB channel-3 transmit data register empty interrupt. */
                                                            
    #define APX_ASB0_TCIE   APX_INT_ASB0_TCIE_enable_w  /*!< ASB channel-0 transmission complete interrupt enable. */
    #define APX_ASB1_TCIE   APX_INT_ASB1_TCIE_enable_w  /*!< ASB channel-1 transmission complete interrupt enable. */
    #define APX_ASB2_TCIE   APX_INT_ASB2_TCIE_enable_w  /*!< ASB channel-2 transmission complete interrupt enable. */
    #define APX_ASB3_TCIE   APX_INT_ASB3_TCIE_enable_w  /*!< ASB channel-3 transmission complete interrupt enable. */
#endif
//!@}

#ifdef __cplusplus
extern "C" {
#endif
/** 
 * @enum		APX_CCLx_SQIN
 * @brief		APX CCLx_SQIN definition
 */        
typedef enum 
{
    APX_CCLx_S0_0 = 0,                      /*!< CCLx_S0 sequential logic input is '0'. */
    APX_CCLx_S0_1,                          /*!< CCLx_S0 sequential logic input is '1'. */
    APX_CCLx_S0_CCL1_S1                     /*!< CCLx_S0 sequential logic input is CCL_S1. (Only for CCL0) */
} APX_CCLx_SQIN;


/** 
 * @enum		APX_TruthTableDef
 * @brief		APX Truth table definition
 */        
typedef enum 
{
    APX_3IN_AND     = 0x80,                 /*!< Run truth table with 3-input "AND". */
    APX_3IN_NAND    = 0x7F,                 /*!< Run truth table with 3-input "NAND". */
    APX_3IN_OR      = 0xFE,                 /*!< Run truth table with 3-input "OR". */
    APX_3IN_NOR     = 0x01,                 /*!< Run truth table with 3-input "NOR". */
    APX_3IN_XOR     = 0x96,                 /*!< Run truth table with 3-input "XOR". */
    APX_3IN_XNOR    = 0x69,                 /*!< Run truth table with 3-input "XNOR". */
    APX_2IN_AND     = 0x08,                 /*!< Run truth table with 2-input "AND". *[IN2] mask. */
    APX_2IN_NAND    = 0x07,                 /*!< Run truth table with 2-input "NAND". *[IN2] mask. */
    APX_2IN_OR      = 0x0E,                 /*!< Run truth table with 2-input "OR". *[IN2] mask. */
    APX_2IN_NOR     = 0x01,                 /*!< Run truth table with 2-input "NOR". *[IN2] mask. */
    APX_2IN_XOR     = 0x06,                 /*!< Run truth table with 2-input "XOR". *[IN2] mask. */
    APX_2IN_XNOR    = 0x09,                 /*!< Run truth table with 2-input "XNOR". *[IN2] mask. */
    APX_IN0_NOT     = 0x55,                 /*!< Run truth table with "NOT" IN0. */
    APX_IN1_NOT     = 0x33,                 /*!< Run truth table with "NOT" IN1. */
    APX_IN2_NOT     = 0x0F                  /*!< Run truth table with "NOT" IN2. */
} APX_TruthTableDef;

/** 
 * @enum		APX_INTClockDivDef
 * @brief		APX internal clock divider definition
 */        
typedef enum 
{ 
    APX_IntDIV1=0,                          /*!< APX internal clock divider (DIV1). */
    APX_IntDIV2,                            /*!< APX internal clock divider (DIV2). */
    APX_IntDIV4,                            /*!< APX internal clock divider (DIV4). */
    APX_IntDIV8                             /*!< APX internal clock divider (DIV8). */
} APX_INTClockDivDef;

/** 
 * @enum		APX_SQLogicModeSel
 * @brief		CCL sequential logic mode select.
 */        
typedef enum 
{ 
    APX_SQSEL_DISABLE=0,                    /*!< CCL sequential logic mode select disable. */
    APX_SQSEL_D_Flipflop,                   /*!< CCL sequential logic mode select D flip flop. */
    APX_SQSEL_JK_Flipflop,                  /*!< CCL sequential logic mode select JK flip flop. */
    APX_SQSEL_D_Latch,                      /*!< CCL sequential logic mode select D latch. */
    APX_SQSEL_RS_Latch                      /*!< CCL sequential logic mode select RS latch. */
} APX_SQLogicModeSel;


/** 
 * @enum		APX_EdgeDetectSel
 * @brief		CCL edge detector mode select.
 */    
typedef enum 
{
    APX_CCL_Disable=0,                      /*!< disable detect function */
    APX_CCL_RisingEdge,                     /*!< Rising edge detect function */
    APX_CCL_FallingEdge,                    /*!< Falling edge detect function */
    APX_CCL_DualEdge                        /*!< dual edge to detect function */
} APX_EdgeDetectSel;


/** 
 * @enum		APX_CCLFilterDef
 * @brief		CCL filter function
 */        
typedef enum
{
    APX_DisableFilter=0,                    /*!< Disable filter. */
    APX_SYNCFilter,                         /*!< Synchronizer enabled. */
    APX_FILTER                              /*!< Filter enabled. */
} APX_CCLFilterDef;

#if defined(MG32_3RD)
/** 
 * @enum		APX_CCL_MUX2Def
 * @brief		CCL IN2 input Mux select
 */        
typedef enum 
{
    APX_MUX2_DISABLE = 0,                   /*!< Disable CCL MUX2. */
    APX_MUX2_CCL_SEQ,                       /*!< CCL MUX2 is from CCLx_SEQ. */
    APX_MUX2_CCL_AO,                        /*!< CCL MUX2 is from CCLx_AO. */
    APX_MUX2_PC1,                           /*!< CCL MUX2 is from PC1. */
    APX_MUX2_PA10,                          /*!< CCL MUX2 is from PA10. */
    APX_MUX2_PB2,                           /*!< CCL MUX2 is from PB2. */
    APX_MUX2_PB10,                          /*!< CCL MUX2 is from PB10. */
    APX_MUX2_PE2,                           /*!< CCL MUX2 is from PE2. */
    APX_MUX2_ADC0_OUT,                      /*!< CCL MUX2 is from ADC0_OUT. */
    APX_MUX2_URT4_TX,                       /*!< CCL MUX2 is from URT4_TX. */
    APX_MUX2_SPI0_CLK,                      /*!< CCL MUX2 is from SPI0_CLK. */
    APX_MUX2_TM36_OC2,                      /*!< CCL MUX2 is from TM36_OC2. */
    APX_MUX2_TM20_OC00,                     /*!< CCL MUX2 is from TM20_OC00. */
    APX_MUX2_OBM_I1                         /*!< CCL MUX2 is from OBM_I1. */
} APX_CCL_MUX2Def;

/** 
 * @enum		APX_CCL_MUX1Def
 * @brief		CCL IN1 input Mux select
 */        
typedef enum 
{
    APX_MUX1_DISABLE = 0,                   /*!< Disable CCL MUX1. */
    APX_MUX1_CCL_SEQ,                       /*!< CCL MUX1 is from CCLx_SEQ. */
    APX_MUX1_CCL_AO,                        /*!< CCL MUX1 is from CCLx_AO. */
    APX_MUX1_PB3,                           /*!< CCL MUX1 is from PB3. */
    APX_MUX1_PA9,                           /*!< CCL MUX1 is from PA9. */
    APX_MUX1_PB1,                           /*!< CCL MUX1 is from PB1. */
    APX_MUX1_PB9,                           /*!< CCL MUX1 is from PB9. */
    APX_MUX1_PE1,                           /*!< CCL MUX1 is from PE1. */
    APX_MUX1_CMP1_OUT,                      /*!< CCL MUX1 is from CMP1_OUT. */
    APX_MUX1_URT1_TX,                       /*!< CCL MUX1 is from URT1_TX. */
    APX_MUX1_SPI0_MISO,                     /*!< CCL MUX1 is from SPI0_MISO(output). */
    APX_MUX1_TM36_OC10,                     /*!< CCL MUX1 is from TM36_OC10. */
    APX_MUX1_TM26_OC10,                     /*!< CCL MUX1 is from TM26_OC10. */
    APX_MUX1_OBM_I0                         /*!< CCL MUX1 is from OBM_I0. */
} APX_CCL_MUX1Def;

/** 
 * @enum		APX_CCL_MUX0Def
 * @brief		CCL IN0 input Mux select
 */        
typedef enum 
{
    APX_MUX0_DISABLE = 0,                   /*!< Disable CCL MUX0. */
    APX_MUX0_CCL_SEQ,                       /*!< CCL MUX0 is from CCLx_SEQ. */
    APX_MUX0_CCL_AO,                        /*!< CCL MUX0 is from CCLx_AO. */
    APX_MUX0_PB11,                          /*!< CCL MUX0 is from PB11. */
    APX_MUX0_PA8,                           /*!< CCL MUX0 is from PA8. */
    APX_MUX0_PB0,                           /*!< CCL MUX0 is from PB0. */
    APX_MUX0_PB8,                           /*!< CCL MUX0 is from PB8. */
    APX_MUX0_PE0,                           /*!< CCL MUX0 is from PE0. */
    APX_MUX0_CMP0_OUT,                      /*!< CCL MUX0 is from CMP0_OUT. */
    APX_MUX0_URT0_TX,                       /*!< CCL MUX0 is from URT0_TX. */
    APX_MUX0_SPI0_MOSI,                     /*!< CCL MUX0 is from SPI0_MOSI(output). */
    APX_MUX0_TM36_OC00,                     /*!< CCL MUX0 is from TM36_OC00. */
    APX_MUX0_TM26_OC00,                     /*!< CCL MUX0 is from TM26_OC00. */
    APX_MUX0_OBM_P0                         /*!< CCL MUX0 is from OBM_P0. */
} APX_CCL_MUX0Def;
#endif

#if defined(MG32_4TH)
/** 
 * @enum		APX_CCL_MUX2Def
 * @brief		CCL IN2 input Mux select
 */        
typedef enum 
{
    APX_MUX2_DISABLE = 0,                   /*!< Disable CCL MUX2.                      */
    APX_MUX2_CCL_SEQ = 1,                   /*!< CCL MUX2 is from CCLx_SEQ.             */
    APX_MUX2_CCL_AO = 2,                    /*!< CCL MUX2 is from CCLx_AO.              */
    APX_MUX2_PC1 = 3,                       /*!< CCL MUX2 is from PC1.                  */
    APX_MUX2_PA10 = 4,                      /*!< CCL MUX2 is from PA10.                 */
    APX_MUX2_PB2 = 5,                       /*!< CCL MUX2 is from PB2.                  */
    APX_MUX2_PB10 = 6,                      /*!< CCL MUX2 is from PB10.                 */
    APX_MUX2_ADC0_OUT = 8,                  /*!< CCL MUX2 is from ADC0_OUT.             */
    APX_MUX2_SPI0_CLK = 10,                 /*!< CCL MUX2 is from SPI0_CLK.             */
    APX_MUX2_TM36_OC2 = 11,                 /*!< CCL MUX2 is from TM36_OC2.             */
    APX_MUX2_TM20_OC00 = 12,                /*!< CCL MUX2 is from TM20_OC00.            */
} APX_CCL_MUX2Def;

/** 
 * @enum		APX_CCL_MUX1Def
 * @brief		CCL IN1 input Mux select
 */        
typedef enum 
{
    APX_MUX1_DISABLE = 0,                   /*!< Disable CCL MUX1.                      */
    APX_MUX1_CCL_SEQ = 1,                   /*!< CCL MUX1 is from CCLx_SEQ.             */
    APX_MUX1_CCL_AO = 2,                    /*!< CCL MUX1 is from CCLx_AO.              */
    APX_MUX1_PB3 = 3,                       /*!< CCL MUX1 is from PB3.                  */
    APX_MUX1_PA9 = 4,                       /*!< CCL MUX1 is from PA9.                  */
    APX_MUX1_PB1 = 5,                       /*!< CCL MUX1 is from PB1.                  */
    APX_MUX1_PB9 = 6,                       /*!< CCL MUX1 is from PB9.                  */
    APX_MUX1_URT1_TX = 9,                   /*!< CCL MUX1 is from URT1_TX.              */
    APX_MUX1_SPI0_MISO = 10,                /*!< CCL MUX1 is from SPI0_MISO(output).    */
    APX_MUX1_TM36_OC10 = 11,                /*!< CCL MUX1 is from TM36_OC10.            */
} APX_CCL_MUX1Def;

/** 
 * @enum		APX_CCL_MUX0Def
 * @brief		CCL IN0 input Mux select
 */        
typedef enum 
{
    APX_MUX0_DISABLE = 0,                   /*!< Disable CCL MUX0.                      */
    APX_MUX0_CCL_SEQ = 1,                   /*!< CCL MUX0 is from CCLx_SEQ.             */
    APX_MUX0_CCL_AO = 2,                    /*!< CCL MUX0 is from CCLx_AO.              */
    APX_MUX0_PB11 = 3,                      /*!< CCL MUX0 is from PB11.                 */
    APX_MUX0_PA8 = 4,                       /*!< CCL MUX0 is from PA8.                  */
    APX_MUX0_PB0 = 5,                       /*!< CCL MUX0 is from PB0.                  */
    APX_MUX0_PB8 = 6,                       /*!< CCL MUX0 is from PB8.                  */
    APX_MUX0_URT0_TX = 9,                   /*!< CCL MUX0 is from URT0_TX.              */
    APX_MUX0_SPI0_MOSI = 10,                /*!< CCL MUX0 is from SPI0_MOSI(output).    */
    APX_MUX0_TM36_OC00 = 11,                /*!< CCL MUX0 is from TM36_OC00.            */
} APX_CCL_MUX0Def;
#endif



#if defined(APX_CR0_ASB0_ENX_mask_w)
/**
 * @name        ASB_SyncCode  ASB SYNC code setting
 *             
 */ 
///@{
#define ASB_SYNCCODE_CODE0        APX_CR0_ASB_SYNC_code0_b3      /*!< ASB SYNC code is Code0. */
#define ASB_SYNCCODE_CODE1        APX_CR0_ASB_SYNC_code1_b3      /*!< ASB SYNC code is Code1. */
///@}

/**
 * @name        ASB_IdleStatus  ASB IDLE state level
 *             
 */ 
///@{
#define ASB_IDLESTATUS_LOW        APX_CR0_ASB_IDLE_low_b3        /*!< ASB IDLE state level is Low. */
#define ASB_IDLESTATUS_HIGH       APX_CR0_ASB_IDLE_high_b3       /*!< ASB IDLE state level is high. */
///@}

/**
 * @name        ASB_ResetStatus  ASB Reset status level
 *             
 */ 
///@{
#define ASB_RSTSTATUS_LOW         APX_CR0_ASB_RST_low_b3         /*!< ASB RESET status is Low. */
#define ASB_RSTSTAUTS_HIGH        APX_CR0_ASB_RST_high_b3        /*!< ASB RESET status is high. */
///@}

/**
 * @name        ASB_ResetSync ASB RESET code synchronous mode enable.
 *
 */
///@{
#define ASB_RST_SYNC_ENABLE       APX_CR0_ASB_SYEN_enable_w      /*!< ASB RESET code synchronous mode enable. */
#define ASB_RST_SYNC_DISABLE      APX_CR0_ASB_SYEN_disable_w     /*!< ASB RESET code synchronous mode disable. */
///@}

/**
 * @name        ASB_ClockInverse  ASB shift clock output signal inverse.
 *             
 */ 
///@{
#define ASB_CLOCK_INVERSE_ENABLE  APX_CR0_ASB_CINV_enable_w        /*!< ASB shift clock output signal inverse*/
#define ASB_CLOKC_INVERSE_DISABLE APX_CR0_ASB_CINV_disable_w       /*!< ASB shift clock output signal no inverse.*/
///@}


#define ASB_CHANNELCONFIG_MASK    (APX_ASB00_ASB0_TXTH_mask_w | APX_ASB00_ASB0_PLEN_mask_w | APX_ASB00_ASB0_INV_mask_w | \
                                   APX_ASB00_ASB0_DINV_mask_w | APX_ASB00_ASB0_MSBEN_mask_w| APX_ASB00_ASB0_MDS_mask_w)       /*!< ASB configuration register mask .*/

/**
 * @name        ASBChannel_SignalInverse ASB channel output inverse
 *
 */
///@{
#define ASB_SIGNAL_INVERSE_ENABLE    APX_ASB00_ASB0_INV_enable_w    /*!< ASB channel output signal inverse.*/
#define ASB_SIGNAL_INVERSE_DISABLE   APX_ASB00_ASB0_INV_disable_w   /*!< ASB channel output signal no inverse.*/
///@}

/**
 * @name        ASBChannel_DataOrder  ASB channel data order.
 *             
 */
///@{
#define ASB_DATA_MSB                 APX_ASB00_ASB0_MSBEN_enable_w  /*!<ASB channel data order is MSB.*/
#define ASB_DATA_LSB                 APX_ASB00_ASB0_MSBEN_disable_w /*!<ASB channel data order is LSB.*/
///@}


/**
 * @name        ASBChannel_DataInverse ASB channel inverse transmitted data.
 *
 */
///@{
#define ASB_DATA_INVERSE_ENABLE      APX_ASB00_ASB0_DINV_enable_w   /*!< ASB channel data reverse.*/
#define ASB_DATA_INVERSE_DISABLE     APX_ASB00_ASB0_DINV_disable_w  /*!< ASB channel data no reverse.*/
///}

/**
 * @name        ASBChannel_PixelLength ASB channel pixel length
 *
 */
///@{
#define ASB_FRAME_PIXEL_4BYTE        APX_ASB00_ASB0_PLEN_4byte_w    /*!< ASB channel pixel length is 4 bytes.*/
#define ASB_FRAME_PIXEL_3BYTE        APX_ASB00_ASB0_PLEN_3byte_w    /*!< ASB channel pixel length is 3 bytes.*/
///@}

/**
 * @name        ASBChannel_TxFIFOThRESHOLD ASB channel data FIFO low threshold for transmitted
 *
 */
#define ASB_TX_FIFOTHRESHOLD_0BYTE  APX_ASB00_ASB0_TXTH_0byte_w     /*!< ASB channel data FIFO low threshold is 0 bytes.*/
#define ASB_TX_FIFOTHRESHOLD_2BYTE  APX_ASB00_ASB0_TXTH_2byte_w     /*!< ASB channel data FIFO low threshold is 2 bytes.*/


/**
 * @name        ASBChannel_OutputMode ASB channel output mode select.
 *
 */
///@{ 
#define ASB_MODE_ARGB                APX_ASB00_ASB0_MDS_argb_w      /*!< ASB channel output mode is ARGB.*/
#define ASB_MODE_SHIFT               APX_ASB00_ASB0_MDS_shift_w     /*!< ASB channel output mode is SHIFT.*/
///@}

/**
 * @name   
 *             
 */ 
///@{
#define __DRV_APX_ASBChannel0_SendData(__DATA__)                APX->ASBDAT.B[0] = (uint8_t)(__DATA__)     /*!< ASB channel 0 send __DATA__. */
#define __DRV_APX_ASBChannel1_SendData(__DATA__)                APX->ASBDAT.B[1] = (uint8_t)(__DATA__)     /*!< ASB channel 1 send __DATA__. */
#define __DRV_APX_ASBChannel2_SendData(__DATA__)                APX->ASBDAT.B[2] = (uint8_t)(__DATA__)     /*!< ASB channel 2 send __DATA__. */
#define __DRV_APX_ASBChannel3_SendData(__DATA__)                APX->ASBDAT.B[3] = (uint8_t)(__DATA__)     /*!< ASB channel 3 send __DATA__. */
#define __DRV_APX_ASBChannel01_SendData(__DATA__)               APX->ASBDAT.H[0] = (uint16_t)(__DATA__)    /*!< ASB channel 0 send low byte of __DATA__ and channel 1 send high byte of __DATA__. */
#define __DRV_APX_ASBChannel23_SendData(__DATA__)               APX->ASBDAT.H[1] = (uint16_t)(__DATA__)    /*!< ASB channel 2 send low byte of __DATA__ and channel 3 send high byte of __DATA__. */
#define __DRV_APX_ASBAllChannel_SendData(__DATA__)              APX->ASBDAT.W    = (uint32_t)(__DATA__)    /*!< ASB channel 3 send byte3, ASB channel 2 send byte2
                                                                                                                ASB channel 1 send byte1, ASB channel 0 send byte0 */
///@}


/** 
 * @struct      ASB_TypeDef
 * @brief       ASB (ARGB) base function initial 
 */        
typedef struct
{
    uint8_t    SyncCode;                    /*!< Specifies ASB SYNC code.                                                  This parameter can be a value of @ref ASB_SyncCode*/
        
    uint8_t    IdleStatus;                  /*!< Specifies ASB IDLE state level.
                                                 This parameter can be a value of @ref ASB_IdleStatus*/
            
    uint8_t    ResetStatus;                 /*!< Specifies ASB Reset code level.
                                                 This parameter can be a value of @ref ASB_ResetStatus*/
                                                
    uint8_t    ResetSync;                   /*!< Specifies ASB RESET code that whether synchronous or not.
                                                 This parameter can be a value of @ref ASB_ResetSync*/
            
    uint8_t    ClockInverse;                /*!< Specifies ASB shift clock output signal , whether inverse or not.
                                                    This parameter can be a value of @ref ASB_ClockInverse */
                                                
    uint8_t    ResetTime;                   /*!< Specifies ASB reset code time.*/
            
    uint8_t    Code1_HighWidthTime;         /*!< Specifies ASB Code 1 high time.*/
            
    uint8_t    Code0_HighWidthTime;         /*!< Specifies ASB Code 0 high time.*/
                                                
    uint8_t    BitTimeCounter;              /*!< Specifies ASB output bit time counter.*/
            
    uint8_t    BitTimePrescaler;            /*!< Specifies ASB output bit time prescaler.*/
} ASB_TypeDef;


/** 
 * @struct      ASBChannel_TypeDef
 * @brief       ASB (ARGB) channel type initial
 */        
typedef struct
{
    uint32_t  TX_FIFOThreshold;             /*!< Specifies ASB channel data FIFO low threshold for transmitted.
                                                 This parameter can be a value of @ref ASBChannel_TxFIFOThRESHOLD*/
                    
    uint32_t  DataOrder;                    /*!< Specifies ASB channel data order.
                                                 This parameter can be a value of @ref ASBChannel_DataOrder*/
                    
    uint32_t  DataInverse;                  /*!< Specifies ASB channel output data that whether inverse or not.
                                                 This parameter can be a value of @ref ASBChannel_DataInverse*/
                    
    uint32_t  SignalInverse;                /*!< Specifies ASB channel signal that whether inverse or not.
                                                 This parameter can be a value of @ref ASBChannel_SignalInverse.*/
                    
    uint32_t  PixelLength;                  /*!< Specifies ASB channel pixel length
                                                 This parameter can be a value of @ref ASBChannel_PixelLength.*/
                    
    uint32_t  OutputMode;                   /*!< Specifies ASB channel output mode select.
                                                 This parameter can be a value of @ref ASBChannel_OutputMode*/
    
} ASBChannel_TypeDef;
#endif 



/**
 * @name        APX (CCL) Truth table control function.
 *   		    
 */ 
///@{  
void APX_CCLTruthTable_Select(CCL_Struct* CCLx, APX_TruthTableDef TFunc);
void APX_CCLTruthTable_Cmd(CCL_Struct* CCLx, FunctionalState NewState);
///@{  

/**
 * @name        APX (CCL) control function.
 *             
 */ 
///@}
DRV_Return APX_GetCCLxOutputState(CCL_Struct* CCLx);
void APX_SetCCLSnState(CCL_Struct* CCLx, APX_CCLx_SQIN CCLS0Src);
void APX_InverseCCLOutput_Cmd(CCL_Struct* CCLx, FunctionalState NewState);
void APX_SetCCLIntClockDivider(CCL_Struct* CCLx, APX_INTClockDivDef INTClockSrc);
void APX_SQSEL_Select(CCL_Struct* CCLx, APX_SQLogicModeSel INTClockSrc);
void APX_EDSEL_Select(CCL_Struct* CCLx, APX_EdgeDetectSel EdgeSel);
void APX_SetFilterFunction(CCL_Struct* CCLx, APX_CCLFilterDef FilterDef);
void APX_CCL_Cmd(CCL_Struct* CCLx, FunctionalState NewState);
///@{  

/**
 * @name        APX (CCL) intput MUX select function.
 *             
 */ 
///@}
void APX_CCLMUX2_Select(CCL_Struct* CCLx, APX_CCL_MUX2Def MUX2Sel);
void APX_CCLMUX1_Select(CCL_Struct* CCLx, APX_CCL_MUX1Def MUX1Sel);
void APX_CCLMUX0_Select(CCL_Struct* CCLx, APX_CCL_MUX0Def MUX0Sel);
///@}


/**
 * @name        APX (CCL+ASB) interrupt/flag control
 *             
 */ 
///@{
void APX_IT_Config(APX_Struct* APXx, uint32_t ITsrc, FunctionalState NewState);
void APX_ITEA_Cmd(APX_Struct* APXx, FunctionalState NewState);
DRV_Return APX_GetSingleFlagStatus(APX_Struct* APXx, uint32_t ITSrc);
uint32_t APX_GetAllFlagStatus(APX_Struct* APXx);
void APX_ClearFlag(APX_Struct* APXx, uint32_t APX_ITSrc);
///@}

#if defined(APX_CR0_ASB0_ENX_mask_w)
/**
 * @name        ASB setting related function.
 *             
 */ 
///@{
void APX_ASB_Config( ASB_TypeDef *ASB_Type);                                         /*!< ASB common setting.*/
void APX_ASBChannel_Config( uint8_t ASB_Chx , ASBChannel_TypeDef* ASBChannel_Type);  /*!< ASB respective channel setting.*/
void APX_ASBChannel_Cmd( uint8_t ASB_Chx , FunctionalState ASB_Chx_Status);          /*!< ASB respective channel output swich.*/
void APX_ASBChannel_DMA_Cmd( uint32_t ASB_Chx , FunctionalState ASB_ChxDMA_Status);   /*!< ASB respective channel DMA swich.*/
///@}

/**
 * @name        ASB transmission related function.
 *             
 */ 
///@{
void APX_ASBChannel_TriggerResetSignal( uint32_t ASB_Chx);                             /*!< Software trigger to send Reset code.*/
uint8_t APX_ASBChannel_GetResetStatus( uint32_t ASB_Chx);                              /*!< Get status that software trigger to send Reset code. */
void APX_ASBChannel_ClearFIFO( uint32_t ASB_Chx);                                      /*!< Clear ASB_Chn ( 0 ~ 3) FIFO status.*/
void APX_ASBChannel_SetFrameSize( uint32_t ASB_Chx , uint8_t ASBChannel_FrameSize);    /*!< Set ASB_Chx frame size .*/
void APX_ASBChannel_SendData( uint32_t ASB_Chx , uint8_t ASB_Data);                    /*!< ASB_Chx ( 0 ~ n) send data.*/
void APX_ASBAllChannel_SendData( uint32_t ASB_Data);                                   /*!< All ASB_Channel send data.*/
///@}
#endif

#ifdef __cplusplus
}
#endif

#endif

