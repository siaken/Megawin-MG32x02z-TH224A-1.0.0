/**
 ******************************************************************************
 *
 * @file        MG32x02z_DMA_MID.h
 *
 * @brief       This file provides firmware functions to manage the following 
 *              functionalities of the DMA peripheral:
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.05
 * @date        2022/07/04
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2016 MegaWin Technology Co., Ltd.
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

#ifndef _MG32x02z_DMA_MID_H

/*!< _MG32x02z_DMA_DRV_H */ 
#define _MG32x02z_DMA_MID_H

#include "MG32x02z.h"
#include "MG32x02z_Common_MID.h"
#include "MG32x02z_DMA.h"
#include "MG32x02z__ExtraStruct.h"
#include "MG32x02z_SYS.h"


/** 
 * @enum		MID_DMA_CallbackIDTypeDef
 * @brief		MID DMA Callback ID structure definition
 */        
typedef enum
{
  MID_DMA_XFER_CPLT_CB_ID          = 0x00U,                 /*!< Full transfer.                             */
  MID_DMA_XFER_HALFCPLT_CB_ID      = 0x01U,                 /*!< Half transfer.                             */
  MID_DMA_XFER_ERROR_CB_ID         = 0x02U,                 /*!< Error.                                     */ 
  MID_DMA_XFER_ABORT_CB_ID         = 0x03U,                 /*!< Abort.                                     */ 
  MID_DMA_XFER_ALL_CB_ID           = 0x04U                  /*!< All.                                       */ 
    
}MID_DMA_CallbackIDTypeDef;                                                                 


/** 
 * @enum		MID_DMA_StateTypeDef
 * @brief		MID State structures definition 
 */        
typedef enum 
{ 
    MID_DMA_STATE_BUSY,                                     /*!< An internal process is running.            */ 
    MID_DMA_STATE_READY,                                    /*!< Peripheral Initialized and ready for use.  */
    MID_DMA_STATE_RESET                                     /*!< DMA not yet initialized or disabled.       */    
} MID_DMA_StateTypeDef;

/** 
  * @brief  HAL DMA Error Code structure definition  
  */ 
typedef enum
{
  MID_DMA_FULL_TRANSFER      = 0x00U,                       /*!< Full transfer.                             */
  MID_DMA_HALF_TRANSFER      = 0x01U                        /*!< Half Transfer.                             */
}MID_DMA_LevelCompleteTypeDef;      

/**
 * @name	DMA_Error_Code
 *   		DMA Error Code
 */ 
//!@{
#define MID_DMA_ERROR_NONE          (0x00000000U)           /*!< No error.                                  */
#define MID_DMA_ERROR_TE            (0x00000001U)           /*!< Transfer error.                            */
#define MID_DMA_ERROR_NO_XFER       (0x00000004U)           /*!< no ongoin transfer.                        */
#define MID_DMA_ERROR_TIMEOUT       (0x00000020U)           /*!< Timeout error.                             */
#define MID_DMA_ERROR_NOT_SUPPORTED (0x00000100U)           /*!< Not supported mode.                        */     
//!@}


/**
 * @name	DMA_Destination_incremented_mode
 *   		DMA Peripheral incremented mode
 */ 
//!@{
#define DMA_DINC_ENABLE         DMA_CH0B_CH0_DINC_enable_w  /*!< Peripheral increment mode Enable.          */
#define DMA_DINC_DISABLE        DMA_CH0B_CH0_DINC_disable_w /*!< Peripheral increment mode Disable.         */
//!@}

/**
 * @name	DMA_Source_incremented_mode
 *   		DMA Memory incremented mode
 */ 
//!@{
#define DMA_SINC_ENABLE         DMA_CH0B_CH0_SINC_enable_w  /*!< Peripheral increment mode Enable.          */
#define DMA_SINC_DISABLE        DMA_CH0B_CH0_SINC_disable_w /*!< Peripheral increment mode Disable.         */
//!@}

/**
 * @name	DMA_BurstSize_Mode
 *   		DMA transfer burst size
 */ 
//!@{
#define DMA_BSIZE_1BYTE         DMA_CH0A_CH0_BSIZE_one_w    /*!< Burst size setting : 1 byte.               */ 
#define DMA_BSIZE_2BYTE         DMA_CH0A_CH0_BSIZE_two_w    /*!< Burst size setting : 2 byte.               */
#define DMA_BSIZE_4BYTE         DMA_CH0A_CH0_BSIZE_four_w   /*!< Burst size setting : 4 byte.               */
//!@}

#if defined(MG32_1ST)
/**
 * @name	DMA_Source_MemPeri
 *   		DMA source from memory or peripheral
 */ 
//!@{
#define MID_DMA_MEMORY_READ         (0x0000U)               /*!< DMA source from memory.                    */                  
#define MID_DMA_ADC0_SAMPLE         (0x0001U)               /*!< DMA source from ADC0.                      */
#define MID_DMA_I2C0_READ           (0x0002U)               /*!< DMA source from I2C0_RX.                   */
#define MID_DMA_I2C1_READ           (0x0003U)               /*!< DMA source from I2C1_RX.                   */
#define MID_DMA_URT0_READ           (0x0004U)               /*!< DMA source from URT0_RX.                   */
#define MID_DMA_URT1_READ           (0x0005U)               /*!< DMA source from URT1_RX.                   */
#define MID_DMA_URT2_READ           (0x0006U)               /*!< DMA source from URT2_RX.                   */
#define MID_DMA_URT3_READ           (0x0007U)               /*!< DMA source from URT3_RX.                   */
#define MID_DMA_SPI0_READ           (0x0008U)               /*!< DMA source from SPI0_RX.                   */
#define MID_DMA_TM36_CAPTURE3       (0x000FU)               /*!< DMA source from TM36 channel3 capture data.*/
//!@}

/**
 * @name	DMA_Destination_MemPeri
 *   		DMA destination can be memory or peripheral
 */ 
//!@{
#define MID_DMA_MEMORY_WRITE        (0x0000U)               /*!< DMA destination is memory.                 */           
#define MID_DMA_DAC_WRITE           (0x0100U)               /*!< DMA destination is DAC0.                   */
#define MID_DMA_I2C0_WRITE          (0x0200U)               /*!< DMA destination is I2C0_TX.                */
#define MID_DMA_I2C1_WRITE          (0x0300U)               /*!< DMA destination is I2C1_TX.                */
#define MID_DMA_URT0_WRITE          (0x0400U)               /*!< DMA destination is URT0_TX.                */
#define MID_DMA_URT1_WRITE          (0x0500U)               /*!< DMA destination is URT1_TX.                */
#define MID_DMA_URT2_WRITE          (0x0600U)               /*!< DMA destination is URT2_TX.                */
#define MID_DMA_URT3_WRITE          (0x0700U)               /*!< DMA destination is URT3_TX.                */
#define MID_DMA_SPI0_WRITE          (0x0800U)               /*!< DMA destination is SPI0_TX.                */
#define MID_DMA_GPL_WRITE           (0x0B00U)               /*!< DMA destination is GPL.                    */
#define MID_DMA_TM36_CC0B_WRITE     (0x0C00U)               /*!< DMA destination is TM36's CC0B.            */
#define MID_DMA_TM36_CC1B_WRITE     (0x0D00U)               /*!< DMA destination is TM36's CC1B.            */
#define MID_DMA_TM36_CC2B_WRITE     (0x0E00U)               /*!< DMA destination is TM36's CC2B.            */
//!@}
#endif

#if defined(MG32_2ND)
/**
 * @name	DMA_Source_MemPeri
 *   		DMA source from memory or peripheral
 */ 
//!@{
#define MID_DMA_MEMORY_READ         (0x0000U)               /*!< DMA source from memory.                    */                  
#define MID_DMA_ADC0_SAMPLE         (0x0001U)               /*!< DMA source from ADC0.                      */
#define MID_DMA_I2C0_READ           (0x0002U)               /*!< DMA source from I2C0_RX.                   */
#define MID_DMA_URT0_READ           (0x0004U)               /*!< DMA source from URT0_RX.                   */
#define MID_DMA_URT1_READ           (0x0005U)               /*!< DMA source from URT1_RX.                   */
#define MID_DMA_SPI0_READ           (0x0008U)               /*!< DMA source from SPI0_RX.                   */
#define MID_DMA_TM36_CAPTURE3       (0x000FU)               /*!< DMA source from TM36 channel3 capture data.*/
//!@}

/**
 * @name	DMA_Destination_MemPeri
 *   		DMA destination can be memory or peripheral
 */ 
//!@{
#define MID_DMA_MEMORY_WRITE        (0x0000U)               /*!< DMA destination is memory.                 */           
#define MID_DMA_I2C0_WRITE          (0x0200U)               /*!< DMA destination is I2C0_TX.                */
#define MID_DMA_URT0_WRITE          (0x0400U)               /*!< DMA destination is URT0_TX.                */
#define MID_DMA_URT1_WRITE          (0x0500U)               /*!< DMA destination is URT1_TX.                */
#define MID_DMA_SPI0_WRITE          (0x0800U)               /*!< DMA destination is SPI0_TX.                */
#define MID_DMA_GPL_WRITE           (0x0B00U)               /*!< DMA destination is GPL.                    */
#define MID_DMA_TM36_CC0B_WRITE     (0x0C00U)               /*!< DMA destination is TM36's CC0B.            */
#define MID_DMA_TM36_CC1B_WRITE     (0x0D00U)               /*!< DMA destination is TM36's CC1B.            */
#define MID_DMA_TM36_CC2B_WRITE     (0x0E00U)               /*!< DMA destination is TM36's CC2B.            */
//!@}
#endif

#if defined(MG32_3RD)
/**
 * @name	DMA_Source_MemPeri
 *   		DMA source from memory or peripheral
 */ 
//!@{
#define MID_DMA_MEMORY_READ         (0x0000U)               /*!< DMA source from memory */                  
#define MID_DMA_ADC0_SAMPLE         (0x0001U)               /*!< DMA source from ADC0 */
#define MID_DMA_I2C0_READ           (0x0002U)               /*!< DMA source from I2C0_RX */
#define MID_DMA_I2C1_READ           (0x0003U)               /*!< DMA source from I2C1_RX */
#define MID_DMA_URT0_READ           (0x0004U)               /*!< DMA source from URT0_RX */
#define MID_DMA_URT1_READ           (0x0005U)               /*!< DMA source from URT1_RX */
#define MID_DMA_URT2_READ           (0x0006U)               /*!< DMA source from URT2_RX */
#define MID_DMA_SPI0_READ           (0x0008U)               /*!< DMA source from SPI0_RX */
#define MID_DMA_USB_READ            (0x000AU)               /*!< DMA source from USB_RX */
#define MID_DMA_TM36_CAPTURE3       (0x000FU)               /*!< DMA source from TM36 channel3 capture data */
//!@}

/**
 * @name	DMA_Destination_MemPeri
 *   		DMA destination can be memory or peripheral
 */ 
//!@{
#define MID_DMA_MEMORY_WRITE        (0x0000U)               /*!< DMA destination is memory */           
#define MID_DMA_DAC_WRITE           (0x0100U)               /*!< DMA destination is DAC0 */
#define MID_DMA_I2C0_WRITE          (0x0200U)               /*!< DMA destination is I2C0_TX */
#define MID_DMA_I2C1_WRITE          (0x0300U)               /*!< DMA destination is I2C1_TX */
#define MID_DMA_URT0_WRITE          (0x0400U)               /*!< DMA destination is URT0_TX */
#define MID_DMA_URT1_WRITE          (0x0500U)               /*!< DMA destination is URT1_TX */
#define MID_DMA_URT2_WRITE          (0x0600U)               /*!< DMA destination is URT2_TX */
#define MID_DMA_SPI0_WRITE          (0x0800U)               /*!< DMA destination is SPI0_TX */
#define MID_DMA_USB_WRITE           (0x000AU)               /*!< DMA destination from USB_TX */
#define MID_DMA_GPL_WRITE           (0x0B00U)               /*!< DMA destination is GPL */
#define MID_DMA_TM36_CC0B_WRITE     (0x0C00U)               /*!< DMA destination is TM36's CC0B */
#define MID_DMA_TM36_CC1B_WRITE     (0x0D00U)               /*!< DMA destination is TM36's CC1B */
#define MID_DMA_TM36_CC2B_WRITE     (0x0E00U)               /*!< DMA destination is TM36's CC2B */
//!@}
#endif

#if defined(MG32_4TH)
/**
 * @name	DMA_Source_MemPeri
 *   		DMA source from memory or peripheral
 */ 
//!@{
#define MID_DMA_MEMORY_READ         (0x0000U)               /*!< DMA source from memory.                    */                  
#define MID_DMA_ADC0_SAMPLE         (0x0001U)               /*!< DMA source from ADC0.                      */
#define MID_DMA_I2C0_READ           (0x0002U)               /*!< DMA source from I2C0_RX.                   */
#define MID_DMA_I2C1_READ           (0x0003U)               /*!< DMA source from I2C1_RX.                   */
#define MID_DMA_URT0_READ           (0x0004U)               /*!< DMA source from URT0_RX.                   */
#define MID_DMA_URT1_READ           (0x0005U)               /*!< DMA source from URT1_RX.                   */
#define MID_DMA_SPI0_READ           (0x0008U)               /*!< DMA source from SPI0_RX.                   */
#define MID_DMA_TM36_CAPTURE3       (0x000FU)               /*!< DMA source from TM36 channel3 capture data.*/
//!@}

/**
 * @name	DMA_Destination_MemPeri
 *   		DMA destination can be memory or peripheral
 */ 
//!@{
#define MID_DMA_MEMORY_WRITE        (0x0000U)               /*!< DMA destination is memory.                 */           
#define MID_DMA_I2C0_WRITE          (0x0200U)               /*!< DMA destination is I2C0_TX.                */
#define MID_DMA_I2C1_WRITE          (0x0300U)               /*!< DMA destination is I2C1_TX.                */
#define MID_DMA_URT0_WRITE          (0x0400U)               /*!< DMA destination is URT0_TX.                */
#define MID_DMA_URT1_WRITE          (0x0500U)               /*!< DMA destination is URT1_TX.                */
#define MID_DMA_SPI0_WRITE          (0x0800U)               /*!< DMA destination is SPI0_TX.                */
#define MID_DMA_GPL_WRITE           (0x0B00U)               /*!< DMA destination is GPL.                    */
#define MID_DMA_TM36_CC0B_WRITE     (0x0C00U)               /*!< DMA destination is TM36's CC0B.            */
#define MID_DMA_TM36_CC1B_WRITE     (0x0D00U)               /*!< DMA destination is TM36's CC1B.            */
#define MID_DMA_TM36_CC2B_WRITE     (0x0E00U)               /*!< DMA destination is TM36's CC2B.            */
#define MID_DMA_ASB0_TX_WRITE       (0x1000U)               /*!< DMA destination is ASB0_TX.                */
#define MID_DMA_ASB1_TX_WRITE       (0x1100U)               /*!< DMA destination is ASB1_TX.                */
#define MID_DMA_ASB2_TX_WRITE       (0x1200U)               /*!< DMA destination is ASB2_TX.                */
#define MID_DMA_ASB3_TX_WRITE       (0x1300U)               /*!< DMA destination is ASB3_TX.                */
//!@}
#endif

/**
 * @name	DMA_Memory_AddressMode
 *   		DMA memory address increase mode
 */ 
//!@{
#define MID_DMA_MEMORY_NORMAL       DMA_CH0A_CH0_ADSEL_normal_w /*!< DMA memory access in one by one.       */
#define MID_DMA_MEMORY_SKIP3        DMA_CH0A_CH0_ADSEL_skip3_w  /*!< Enable memory access with SKIP3 mode.  */
//!@}

/**
 * @name	DMA_Priority_level
 *   		DMA Priority level
 */ 
//!@{
#define DMA_PRIORITY_LOW            DMA_CH0A_CH0_PLS_lv0_w  /*!< Priority level : Low.                      */
#define DMA_PRIORITY_MEDIUM         DMA_CH0A_CH0_PLS_lv1_w  /*!< Priority level : Medium.                   */
#define DMA_PRIORITY_HIGH           DMA_CH0A_CH0_PLS_lv2_w  /*!< Priority level : High.                     */
#define DMA_PRIORITY_VERY_HIGH      DMA_CH0A_CH0_PLS_lv3_w  /*!< Priority level : Very_High.                */
//!@}

#if !defined(MG32_2ND)
/**
 * @name	DMA_Priority_Mode
 *   		DMA Priority mode
 */ 
//!@{
#define DMA_ROUND_ROBIN             DMA_CR0_PRI_MDS_round_w  /*!< Priority mode : round robin.              */
#define DMA_LEVEL                   DMA_CR0_PRI_MDS_level_w  /*!< Priority mode : Priority level.           */
//!@}
#endif

/**
 * @name	DMA_ChannelFlag
 *   		DMA flag Definition
 */ 
//!@{
#define DMA_CH_FLAG_ERRF            DMA_CH0A_CH0_ERR2F_mask_w   /*!< DMA Channel Error Flag.                */
#define DMA_CH_FLAG_HALF            DMA_CH0A_CH0_TH2F_mask_w    /*!< DMA Channel Half Flag.                 */
#define DMA_CH_FLAG_COMPLETE        DMA_CH0A_CH0_TC2F_mask_w    /*!< DMA Channel Complete Flag.             */
#define DMA_CH_ALL_FLAG             (DMA_CH_FLAG_ERRF | DMA_CH_FLAG_HALF | DMA_CH_FLAG_COMPLETE)    /*!< DMA channel flag (include ERRF, HALF, COMPLETE). */
//!@}

/**
 * @name	DMA_interrupt_enable_definitions
 *   		DMA interrupt enable definitions
 */ 
//!@{
#define DMA_IT_TC                   DMA_CH0A_CH0_CIE_enable_w   /*!< DMA Channel complete interrupt.        */
#define DMA_IT_HT                   DMA_CH0A_CH0_HIE_enable_w   /*!< DMA Channel half interrupt.            */
#define DMA_IT_TE                   DMA_CH0A_CH0_EIE_enable_w   /*!< DMA Channel error interrupt.           */    
//!@}

/**
 * @name	DMA_LoopMode_Active
 *   		DMA loop mode enable definitions
 */ 
//!@{
#define DMA_LOOP_ENABLE             DMA_CH0A_CH0_LOOP_enable_w  /*!< Enable DMA loop mode.                  */
#define DMA_LOOP_DISABLE            DMA_CH0A_CH0_LOOP_disable_w /*!< DMA access once cycle.                 */  
//!@}



/** 
 * @struct  DMA_InitTypeDef
 * @brief   DMA Configuration Structure definition
 */        
typedef struct __attribute__((packed)) {				
    uint32_t SrcPeri;               /*!< Specifies the source from memory or peripheral.
                                         This parameter can be a value of reference DMA_Source_MemPeri */
                                    
    uint32_t DesPeri;               /*!< Specifies the destination to memory or peripheral.
                                         This parameter can be a value of reference DMA_Destination_MemPeri */
                                    
    uint32_t BSize;                 /*!< Specifies the Peripheral data width.
                                         This parameter can be a value of reference DMA_BurstSize_Mode */
                    
    uint32_t MEMMode;               /*!< Specifies the operation mode of the DMA Channelx.
                                         This parameter can be a value of reference DMA_Memory_AddressMode */
                                    
#if defined(MG32_1ST) || defined(MG32_3RD) || defined(MG32_4TH)
    uint32_t Priority;              /*!< Specifies the software priority for the DMA Channelx.
                                         This parameter can be a value of reference DMA_Priority_level only apply in Priority level mode */
#endif
                                        
    uint32_t LoopMode;              /*!< Specifies the loop mode for the DMA Channelx.
                                         This parameter can be a value of reference DMA_LoopMode_Active */
} DMA_InitTypeDef;				



/** 
 * @struct  DMA_HandleTypeDef
 * @brief   DMA handle Structure definition
 */        
typedef struct __attribute__((packed)) tag_DMA_HandleTypeDef 
{  
    DMA_Struct            *Instance;                                                      /*!< Register base address                  */
                                                                                            
    DMA_InitTypeDef       Init;                                                           /*!< DMA communication parameters           */ 
                                                                                            
    MID_LockTypeDef       Lock;                                                           /*!< DMA locking object                     */  
                                                                                            
    MID_DMA_StateTypeDef  State;                                                          /*!< DMA transfer state                     */

#if defined(MG32_1ST) || defined(MG32_3RD) || defined(MG32_4TH)
    uint32_t              PriorityMode;                                                   /*!< DMA Priority Mode select .                
                                                                                                This parameter can be a value of reference DMA_Priority_Mode */
#endif
    
    uint32_t              ExtraGPL_Channel;                                               /*!< DMA data send to GPL calculating
                                                                                               0 : Disable data to GPL.
                                                                                               1 : GPL data from DMA channel-0.
                                                                                               2 : GPL data from DMA channel-1.
                                                                                               3 : GPL data from DMA channel-2.
                                                                                               */  
                                                                                            
    void                  *Parent;                                                        /*!< Parent object state                    */  
                                                                                            
    void                  (* XferCpltCallback)( struct tag_DMA_HandleTypeDef * mDMA);     /*!< DMA transfer complete callback         */
                                                                                           
    void                  (* XferHalfCpltCallback)( struct tag_DMA_HandleTypeDef * mDMA); /*!< DMA Half transfer complete callback    */
                                                                                           
    void                  (* XferErrorCallback)( struct tag_DMA_HandleTypeDef * mDMA);    /*!< DMA transfer error callback            */
                                                                                           
    void                  (* XferAbortCallback)( struct tag_DMA_HandleTypeDef * mDMA);    /*!< DMA transfer abort callback            */  
                                                                                            
    __IO uint32_t         ErrorCode;                                                      /*!< DMA Error code                         */
                                                                                            
    DMAChannel_Struct     *DMAChannelIndex;                                               /*!< DMA Channel Struct                     */
    
} DMA_HandleTypeDef;    



/**
 *******************************************************************************
 * @brief       Update the DMA source address.
 * @param[in]   "__HANDLECH__" : pointer to a DMAChannel_Struct.
 * @param[in]   "__SADR__" : specifies the DMA source address.
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_DMA_UPDATE_SSA(mADC.DMA_Handle->DMAChannelIndex, &AudioBuf);
 * @endcode
 *******************************************************************************
 */
#define __DRV_DMA_UPDATE_SSA(__HANDLECH__,__SADR__)     ((__HANDLECH__)->SSA.W = (__SADR__))

/**
 *******************************************************************************
 * @brief       Update the DMA destination address.
 * @param[in]   "__HANDLECH__" : pointer to a DMAChannel_Struct.
 * @param[in]   "__DADR__" : specifies the DMA source address.
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_DMA_UPDATE_DSA(mADC.DMA_Handle->DMAChannelIndex, &ReceiveBuf);
 * @endcode
 *******************************************************************************
 */
#define __DRV_DMA_UPDATE_DSA(__HANDLECH__,__DADR__)     ((__HANDLECH__)->DSA.W = (__DADR__))

/**
 *******************************************************************************
 * @brief       Clear the DMA interrupt pending bits.
 * @param[in]   "__HANDLECH__" : pointer to a DMAChannel_Struct.
 * @param[in]   "__FLAG__" : specifies the DMA interrupt flag to clear.
 *  @arg\b	    DMA_CH_FLAG_ERRF : DMA Channel Error Flag.
 *  @arg\b	    DMA_CH_FLAG_HALF : DMA Channel Half Flag.
 *  @arg\b	    DMA_CH_FLAG_COMPLETE : DMA Channel Complete Flag.
*  @arg\b	    DMA_CH_ALL_FLAG :  Any flag of ERRF, HALF, COMPLETE  
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_DMA_CLEAR_FLAG(mADC.DMA_Handle->DMAChannelIndex, DMA_CH_FLAG_COMPLETE);
 * @endcode
 *******************************************************************************
 */
#define __DRV_DMA_CLEAR_FLAG(__HANDLECH__,__FLAG__)     ((__HANDLECH__)->A.W |= (__FLAG__))

/**
 *******************************************************************************
 * @brief       Get the DMA interrupt pending bits.
 * @param[in]   "__HANDLECH__" : pointer to a DMAChannel_Struct.
 * @param[in]   "__FLAG__" : specifies the DMA interrupt flag to clear.
 *  @arg\b	    DMA_CH_FLAG_ERRF : DMA Channel Error Flag.
 *  @arg\b	    DMA_CH_FLAG_HALF : DMA Channel Half Flag.
 *  @arg\b	    DMA_CH_FLAG_COMPLETE : DMA Channel Complete Flag.
*  @arg\b	    DMA_CH_ALL_FLAG :  Any flag of ERRF, HALF, COMPLETE  
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_DMA_GET_FLAG(mADC.DMA_Handle->DMAChannelIndex, DMA_CH_FLAG_COMPLETE);
 * @endcode
 *******************************************************************************
 */
#define __DRV_DMA_GET_FLAG(__HANDLECH__,__FLAG__)      (((__HANDLECH__)->A.W & (__FLAG__)) == (__FLAG__))


/**
 *******************************************************************************
 * @brief       Enables the specified DMA All interrupt.
 * @param[in]   "__HANDLE__" : pointer to a DMA_HandleTypeDef
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_DMA_ENABLE_ITEA(&DMA_Handle);
 * @endcode
 *******************************************************************************
 */
#define __DRV_DMA_ENABLE_ITEA(__HANDLE__)    ((__HANDLE__)->Instance->INT.W |= DMA_INT_IEA_enable_w)

/**
 *******************************************************************************
 * @brief       Disables the specified DMA All interrupt.
 * @param[in]   "__HANDLE__" : pointer to a DMA_HandleTypeDef
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_DMA_DISABLE_ITEA(&DMA_Handle);
 * @endcode
 *******************************************************************************
 */
#define __DRV_DMA_DISABLE_ITEA(__HANDLE__)    ((__HANDLE__)->Instance->INT.W &= ~DMA_INT_IEA_enable_w)

/**
 *******************************************************************************
 * @brief       Enables the specified DMA interrupt.
 * @param[in]   "__HANDLECH__" : pointer to a DMAChannel_Struct.
 * @param[in]   "__INTERRUPT__" : specifies the DMA interrupt source to enable.
 *  @arg\b      DMA_IT_TC : Complete flag.
 *  @arg\b      DMA_IT_HT : Half size flag.
 *  @arg\b      DMA_IT_TE : Error flag.
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_DMA_ENABLE_IT(mADC.DMA_Handle->DMAChannelIndex, DMA_IT_HT);
 * @endcode
 *******************************************************************************
 */
#define __DRV_DMA_ENABLE_IT(__HANDLECH__,__INTERRUPT__)  \
        ((__HANDLECH__)->A.W  |= (__INTERRUPT__)) 

/**
 *******************************************************************************
 * @brief       Disables the specified DMA interrupt.
 * @param[in]   "__HANDLECH__" : pointer to a DMAChannel_Struct.
 * @param[in]   "__INTERRUPT__" : specifies the DMA interrupt source to disable.
 *  @arg\b      DMA_IT_TC : Complete flag.
 *  @arg\b      DMA_IT_HT : Half size flag.
 *  @arg\b      DMA_IT_TE : Error flag.
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_DMA_DISABLE_IT(mADC.DMA_Handle->DMAChannelIndex, DMA_IT_HT);
 * @endcode
 *******************************************************************************
 */
#define __DRV_DMA_DISABLE_IT(__HANDLECH__,__INTERRUPT__)  \
        ((__HANDLECH__)->A.W  &= ~(__INTERRUPT__)) 

/**
 *******************************************************************************
 * @brief       Start the DMA request.
 * @param[in]   "__HANDLECH__" : pointer to a DMAChannel_Struct.
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_DMA_START_REQUEST(mADC.DMA_Handle->DMAChannelIndex);
 * @endcode
 *******************************************************************************
 */
#define __DRV_DMA_START_REQUEST(__HANDLECH__)    ((__HANDLECH__)->A.W |= DMA_CH0A_CH0_REQ_mask_w)

/**
 *******************************************************************************
 * @brief       Set DMA with the last transmission.
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_DMA_SET_LASTCYCLE(mADC.DMA_Handle->DMAChannelIndex);
 * @endcode
 *******************************************************************************
 */
#if defined(MG32_1ST)
#define __DRV_DMA_SET_LASTCYCLE(__HANDLECH__)       \
    do{                                             \
        if((__HANDLECH__) == DMAChannel0)           \
            SYS->CR0.W |= (SYS_CR0_CH0_LAST_yes_w); \
        else if ((__HANDLECH__) == DMAChannel1)     \
            SYS->CR0.W |= (SYS_CR0_CH1_LAST_yes_w); \
        else if ((__HANDLECH__) == DMAChannel2)     \
            SYS->CR0.W |= (SYS_CR0_CH2_LAST_yes_w); \
    }while (0)
#else
    #define __DRV_DMA_SET_LASTCYCLE(__HANDLECH__)       ((__HANDLECH__)->A.W |= (DMA_CH0A_CH0_LAST_yes_w))
#endif 


/**
 * @name    Function announce
 * @brief   DMA base initial/Deinitial	
 */ 
///@{
MID_StatusTypeDef MID_DMA_Init(DMA_HandleTypeDef *mDMA);
MID_StatusTypeDef MID_DMA_DeInit(DMA_HandleTypeDef *mDMA);
MID_StatusTypeDef MID_DMA_Start(DMA_HandleTypeDef *mDMA, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
MID_StatusTypeDef MID_DMA_Start_IT(DMA_HandleTypeDef *mDMA, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
MID_StatusTypeDef MID_DMA_Abort(DMA_HandleTypeDef *mDMA);
MID_StatusTypeDef MID_DMA_Abort_IT(DMA_HandleTypeDef *mDMA);
MID_StatusTypeDef MID_DMA_PollForTransfer(DMA_HandleTypeDef *mDMA, uint32_t CompleteLevel, uint32_t Timeout);
void MID_DMA_IRQHandler(DMA_HandleTypeDef *mDMA);
MID_StatusTypeDef MID_DMA_RegisterCallback(DMA_HandleTypeDef *mDMA, MID_DMA_CallbackIDTypeDef CallbackID, void (* pCallback)( DMA_HandleTypeDef * _mDMA));
MID_StatusTypeDef MID_DMA_UnRegisterCallback(DMA_HandleTypeDef *mDMA, MID_DMA_CallbackIDTypeDef CallbackID);
MID_DMA_StateTypeDef MID_DMA_GetState(DMA_HandleTypeDef *mDMA);
uint32_t MID_DMA_GetError(DMA_HandleTypeDef *mDMA);
///@}



/**
 * @name    Function announce
 * @brief   addtogroup DMA_Private_Functions
 */ 
///@{
void DMA_SetConfig(DMA_HandleTypeDef *mDMA, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
///@}

#endif
