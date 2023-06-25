/**
 ******************************************************************************
 *
 * @file        MG32x02z_DMA_DRV.h
 *
 * @brief       This file contains all the functions prototypes for the DMA
 *              firmware library.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.19
 * @date        2021/09/07
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



#ifndef __MG32x02z_DMA_DRV_H
#define __MG32x02z_DMA_DRV_H
//#define _MG32x02z_DMA_DRV_H_VER 0.01



#include "MG32x02z__Common_DRV.h"
#include "MG32x02z_DMA.h"
#include "MG32x02z__ExtraStruct.h"
#if defined(MG32_1ST)
#include "MG32x02z_SYS.h"
#endif

/** @brief transfer error interrupt enable. */
#define DMA_Error_ITE       DMA_CH0A_CH0_EIE_mask_b2  
/** @brief transfer half interrupt enable */
#define DMA_Half_ITE        DMA_CH0A_CH0_HIE_mask_b2     
/** @brief transfer complete interrupt enable */
#define DMA_Complete_ITE    DMA_CH0A_CH0_CIE_mask_b2    

/** @brief DMA channel-4 transfer error flag */
#define DMA_FLAG_CH4_ERRF                 DMA_STA_CH4_ERRF_mask_w   /* DMA channel-4 transfer error flag. (set by hardware and clear by software writing 1) */
/** @brief DMA channel-4 transfer half flag */
#define DMA_FLAG_CH4_THF                  DMA_STA_CH4_THF_mask_w    /* DMA channel-4 transfer half flag. (set by hardware and clear by software writing 1) */
/** @brief DMA channel-4 transfer complete flag */
#define DMA_FLAG_CH4_TCF                  DMA_STA_CH4_TCF_mask_w    /* DMA channel-4 transfer complete flag. (set by hardware and clear by software writing 1) */
/** @brief DMA channel-4 global interrupt flag */
#define DMA_FLAG_CH4_GIF                  DMA_STA_CH4_GIF_mask_w    /* DMA channel-4 global interrupt flag. This bit will be set if any of other channel event interrupt flag is set. */
/** @brief DMA channel-3 transfer error flag */
#define DMA_FLAG_CH3_ERRF                 DMA_STA_CH3_ERRF_mask_w   /* DMA channel-3 transfer error flag. (set by hardware and clear by software writing 1) */
/** @brief DMA channel-3 transfer half flag */
#define DMA_FLAG_CH3_THF                  DMA_STA_CH3_THF_mask_w    /* DMA channel-3 transfer half flag. (set by hardware and clear by software writing 1) */
/** @brief DMA channel-3 transfer complete flag */
#define DMA_FLAG_CH3_TCF                  DMA_STA_CH3_TCF_mask_w    /* DMA channel-3 transfer complete flag. (set by hardware and clear by software writing 1) */
/** @brief DMA channel-3 global interrupt flag */
#define DMA_FLAG_CH3_GIF                  DMA_STA_CH3_GIF_mask_w    /* DMA channel-3 global interrupt flag. This bit will be set if any of other channel event interrupt flag is set. */
/** @brief DMA channel-2 transfer error flag */
#define DMA_FLAG_CH2_ERRF                 DMA_STA_CH2_ERRF_mask_w   /* DMA channel-2 transfer error flag. (set by hardware and clear by software writing 1) */
/** @brief DMA channel-2 transfer half flag */
#define DMA_FLAG_CH2_THF                  DMA_STA_CH2_THF_mask_w    /* DMA channel-2 transfer half flag. (set by hardware and clear by software writing 1) */
/** @brief DMA channel-2 transfer complete flag */
#define DMA_FLAG_CH2_TCF                  DMA_STA_CH2_TCF_mask_w    /* DMA channel-2 transfer complete flag. (set by hardware and clear by software writing 1) */
/** @brief DMA channel-2 global interrupt flag */
#define DMA_FLAG_CH2_GIF                  DMA_STA_CH2_GIF_mask_w    /* DMA channel-2 global interrupt flag. This bit will be set if any of other channel event interrupt flag is set. */
/** @brief DMA channel-1 transfer error flag */
#define DMA_FLAG_CH1_ERRF                 DMA_STA_CH1_ERRF_mask_w   /* DMA channel-1 transfer error flag. (set by hardware and clear by software writing 1) */
/** @brief DMA channel-1 transfer half flag */
#define DMA_FLAG_CH1_THF                  DMA_STA_CH1_THF_mask_w    /* DMA channel-1 transfer half flag. (set by hardware and clear by software writing 1) */
/** @brief DMA channel-1 transfer complete flag */
#define DMA_FLAG_CH1_TCF                  DMA_STA_CH1_TCF_mask_w    /* DMA channel-1 transfer complete flag. (set by hardware and clear by software writing 1) */
/** @brief DMA channel-1 global interrupt flag */
#define DMA_FLAG_CH1_GIF                  DMA_STA_CH1_GIF_mask_w    /* DMA channel-1 global interrupt flag. This bit will be set if any of other channel event interrupt flag is set. */
/** @brief DMA channel-0 transfer error flag */
#define DMA_FLAG_CH0_ERRF                 DMA_STA_CH0_ERRF_mask_w   /* DMA channel-0 transfer error flag. (set by hardware and clear by software writing 1) */
/** @brief DMA channel-0 transfer half flag */
#define DMA_FLAG_CH0_THF                  DMA_STA_CH0_THF_mask_w    /* DMA channel-0 transfer half flag. (set by hardware and clear by software writing 1) */
/** @brief DMA channel-0 transfer complete flag */
#define DMA_FLAG_CH0_TCF                  DMA_STA_CH0_TCF_mask_w    /* DMA channel-0 transfer complete flag. (set by hardware and clear by software writing 1) */
/** @brief DMA channel-0 global interrupt flag */
#define DMA_FLAG_CH0_GIF                  DMA_STA_CH0_GIF_mask_w    /* DMA channel-0 global interrupt flag. This bit will be set if any of other channel event interrupt flag is set. */

#ifdef __cplusplus
extern "C" {
#endif


/** 
 * @enum        DMA_ChannelFlagDef
 * @brief       specifies the DMA Channel flag 
 */        
typedef enum 
{ 
    DMA_Chx_TCF = DMA_CH0A_CH0_TC2F_happened_b3,                    /*!< select DMA channel x complete flag */
    DMA_Chx_THF = DMA_CH0A_CH0_TH2F_happened_b3,                    /*!< select DMA channel x half flag */
    DMA_Chx_ERRF = DMA_CH0A_CH0_ERR2F_happened_b3,                  /*!< select DMA channel x error flag */
    DMA_Chx_AllFlags = DMA_Chx_TCF | DMA_Chx_THF | DMA_Chx_ERRF     /*!< Select DMA channel x all flags */
        
} DMA_ChannelFlagDef;

#if defined(MG32_1ST)
/** 
 * @enum        DMA_DataWithGPLDef
 * @brief       specifies the DMA GPL source to check
 */        
typedef enum 
{ 
    DMA_GPL_DISABLE,    /*!< no any channel with GPL function */
    DMA_GPL_CHANNEL_0,  /*!< select DMA channel 0 data through GPL macro */
    DMA_GPL_CHANNEL_1,  /*!< select DMA channel 1 data through GPL macro */
    DMA_GPL_CHANNEL_2   /*!< select DMA channel 2 data through GPL macro  */
} DMA_DataWithGPLDef;
#endif

#if defined(MG32_2ND)
/** 
 * @enum        DMA_DataWithGPLDef
 * @brief       specifies the DMA GPL source to check
 */        
typedef enum 
{ 
    DMA_GPL_DISABLE,    /*!< no any channel with GPL function */
    DMA_GPL_CHANNEL_0   /*!< select DMA channel 0 data through GPL macro */
} DMA_DataWithGPLDef;
#endif

#if defined(MG32_3RD)
/** 
 * @enum        DMA_DataWithGPLDef
 * @brief       specifies the DMA GPL source to check
 */        
typedef enum 
{ 
    DMA_GPL_DISABLE,    /*!< no any channel with GPL function */
    DMA_GPL_CHANNEL_0,  /*!< select DMA channel 0 data through GPL macro */
    DMA_GPL_CHANNEL_1,  /*!< select DMA channel 1 data through GPL macro */
    DMA_GPL_CHANNEL_2,  /*!< select DMA channel 2 data through GPL macro  */
    DMA_GPL_CHANNEL_3,  /*!< select DMA channel 3 data through GPL macro  */
    DMA_GPL_CHANNEL_4   /*!< select DMA channel 4 data through GPL macro  */
} DMA_DataWithGPLDef;

#endif

#if defined(MG32_4TH)
/** 
 * @enum        DMA_DataWithGPLDef
 * @brief       specifies the DMA GPL source to check
 */        
typedef enum 
{ 
    DMA_GPL_DISABLE,    /*!< no any channel with GPL function */
    DMA_GPL_CHANNEL_0,  /*!< select DMA channel 0 data through GPL macro */
    DMA_GPL_CHANNEL_1,  /*!< select DMA channel 1 data through GPL macro */
    DMA_GPL_CHANNEL_2,  /*!< select DMA channel 2 data through GPL macro  */
    DMA_GPL_CHANNEL_3   /*!< select DMA channel 3 data through GPL macro  */
} DMA_DataWithGPLDef;
#endif


/** 
 * @enum		DMA_PriorityModeDef
 * @brief		DMA channel priority mode select
 */        
typedef enum 
{ 
    DMA_Round_Robin,    /*!< control by Round Robin method */
    DMA_Priority_Level  /*!< control by channel priority level */
} DMA_PriorityModeDef;


/** 
 * @enum		DMA_BurstSizeDef
 * @brief		Indicates the number of transfers that make up a single DMA data transfer
 */        
typedef enum 
{ 
    DMA_BurstSize_1Byte=0,  /*!< 1 byte */
    DMA_BurstSize_2Byte=1,  /*!< 2 bytes */
    DMA_BurstSize_4Byte=3   /*!< 4 bytes */
} DMA_BurstSizeDef;




/** 
 * @enum		DMA_ExtTriggerModeDef
 * @brief		DMA channel external pin trigger request mode select. 
 */        
typedef enum 
{ 
    DMA_DisableExtTrg,  /*!< disable external request pin input */
    DMA_SingleExtTrg,   /*!< single request mode */
    DMA_BlockExtTrg,    /*!< block request mode */
    DMA_DemandExtTrg    /*!< demand request mode (active high) */
} DMA_ExtTriggerModeDef;


#if defined(MG32_1ST)
/** 
 * @enum		DMA_SourcenRequestDef
 * @brief		DMA channel transfer peripheral source select
 */        
typedef enum 
{ 
    DMA_MEM_Read=0,     /*!< from memory */
    DMA_ADC0_IN=1,      /*!< from ADC conversion data */
    DMA_I2C0_RX=2,      /*!< from I2C0 external in data */
    DMA_I2C1_RX=3,      /*!< from I2C1 external in data */
    DMA_URT0_RX=4,      /*!< from URT0 RX data */
    DMA_URT1_RX=5,      /*!< from URT1 RX data */
    DMA_URT2_RX=6,      /*!< from URT2 RX data */
    DMA_URT3_RX=7,      /*!< from URT3 RX data */
    DMA_SPI0_RX=8,      /*!< from SPI0 MISO data */
    DMA_TM36_IC3=15     /*!< from TM36 capture data */
} DMA_SourcenRequestDef;

/** 
 * @enum		DMA_DestinationRequestDef
 * @brief		DMA channel transfer peripheral destination select
 */        
typedef enum 
{ 
    DMA_MEM_Write=0,    /*!< to memory */
    DMA_DAC0_OUT=1,     /*!< to DAC output control */
    DMA_I2C0_TX=2,      /*!< to I2C0 output */
    DMA_I2C1_TX=3,      /*!< to I2C1 output */
    DMA_URT0_TX=4,      /*!< to URT0 TX output */
    DMA_URT1_TX=5,      /*!< to URT1 TX output */
    DMA_URT2_TX=6,      /*!< to URT2 TX output */
    DMA_URT3_TX=7,      /*!< to URT3 TX output */
    DMA_SPI0_TX=8,      /*!< to SPI0 MOSI output */
    DMA_GPL_Write=11,   /*!< to GPL function control */
    DMA_TM36_CC0B=12,   /*!< to TM36 channel 0 - buffer data */
    DMA_TM36_CC1B=13,   /*!< to TM36 channel 1 - buffer data */
    DMA_TM36_CC2B=14    /*!< to TM36 channel 2 - buffer data */
} DMA_DestinationRequestDef;
#endif

#if defined(MG32_2ND)
/** 
 * @enum		DMA_SourcenRequestDef
 * @brief		DMA channel transfer peripheral source select
 */        
typedef enum 
{ 
    DMA_MEM_Read=0,     /*!< from memory */
    DMA_ADC0_IN=1,      /*!< from ADC conversion data */
    DMA_I2C0_RX=2,      /*!< from I2C0 external in data */
    DMA_URT0_RX=4,      /*!< from URT0 RX data */
    DMA_URT1_RX=5,      /*!< from URT1 RX data */
    DMA_SPI0_RX=8,      /*!< from SPI0 MISO data */
    DMA_TM36_IC3=15     /*!< from TM36 capture data */
} DMA_SourcenRequestDef;

/** 
 * @enum		DMA_DestinationRequestDef
 * @brief		DMA channel transfer peripheral destination select
 */        
typedef enum 
{ 
    DMA_MEM_Write=0,    /*!< to memory */
    DMA_I2C0_TX=2,      /*!< to I2C0 output */
    DMA_URT0_TX=4,      /*!< to URT0 TX output */
    DMA_URT1_TX=5,      /*!< to URT1 TX output */
    DMA_SPI0_TX=8,      /*!< to SPI0 MOSI output */
    DMA_GPL_Write=11,   /*!< to GPL function control */
    DMA_TM36_CC0B=12,   /*!< to TM36 channel 0 - buffer data */
    DMA_TM36_CC1B=13,   /*!< to TM36 channel 1 - buffer data */
    DMA_TM36_CC2B=14    /*!< to TM36 channel 2 - buffer data */
} DMA_DestinationRequestDef;
#endif

#if defined(MG32_3RD)
/** 
 * @enum		DMA_SourcenRequestDef
 * @brief		DMA channel transfer peripheral source select
 */        
typedef enum 
{ 
    DMA_MEM_Read=0,     /*!< from memory */
    DMA_ADC0_IN=1,      /*!< from ADC conversion data */
    DMA_I2C0_RX=2,      /*!< from I2C0 external in data */
    DMA_I2C1_RX=3,      /*!< from I2C1 external in data */
    DMA_URT0_RX=4,      /*!< from URT0 RX data */
    DMA_URT1_RX=5,      /*!< from URT1 RX data */
    DMA_URT2_RX=6,      /*!< from URT2 RX data */
    DMA_SPI0_RX=8,      /*!< from SPI0 MISO data */
    DMA_USB_RX=10,      /*!< from USB_RX data */
    DMA_TM36_IC3=15     /*!< from TM36 capture data */
} DMA_SourcenRequestDef;

/** 
 * @enum		DMA_DestinationRequestDef
 * @brief		DMA channel transfer peripheral destination select
 */        
typedef enum 
{ 
    DMA_MEM_Write=0,    /*!< to memory */
    DMA_DAC0_OUT=1,     /*!< to DAC output control */
    DMA_I2C0_TX=2,      /*!< to I2C0 output */
    DMA_I2C1_TX=3,      /*!< to I2C1 output */
    DMA_URT0_TX=4,      /*!< to URT0 TX output */
    DMA_URT1_TX=5,      /*!< to URT1 TX output */
    DMA_URT2_TX=6,      /*!< to URT2 TX output */
    DMA_SPI0_TX=8,      /*!< to SPI0 MOSI output */
    DMA_USB_TX=10,      /*!< to USB TX output */
    DMA_GPL_Write=11,   /*!< to GPL function control */
    DMA_TM36_CC0B=12,   /*!< to TM36 channel 0 - buffer data */
    DMA_TM36_CC1B=13,   /*!< to TM36 channel 1 - buffer data */
    DMA_TM36_CC2B=14    /*!< to TM36 channel 2 - buffer data */
} DMA_DestinationRequestDef;
#endif

#if defined(MG32_4TH)
/** 
 * @enum		DMA_SourcenRequestDef
 * @brief		DMA channel transfer peripheral source select
 */        
typedef enum 
{ 
    DMA_MEM_Read=0,     /*!< from memory */
    DMA_ADC0_IN=1,      /*!< from ADC conversion data */
    DMA_I2C0_RX=2,      /*!< from I2C0 external in data */
    DMA_I2C1_RX=3,      /*!< from I2C1 external in data */
    DMA_URT0_RX=4,      /*!< from URT0 RX data */
    DMA_URT1_RX=5,      /*!< from URT1 RX data */
    DMA_SPI0_RX=8,      /*!< from SPI0 MISO data */
    DMA_TM36_IC2=14,    /*!< from TM36_IC2 capture data */
    DMA_TM36_IC3=15     /*!< from TM36_IC3 capture data */
} DMA_SourcenRequestDef;

/** 
 * @enum		DMA_DestinationRequestDef
 * @brief		DMA channel transfer peripheral destination select
 */        
typedef enum 
{ 
    DMA_MEM_Write=0,    /*!< to memory */
    DMA_I2C0_TX=2,      /*!< to I2C0 output */
    DMA_I2C1_TX=3,      /*!< to I2C1 output */
    DMA_URT0_TX=4,      /*!< to URT0 TX output */
    DMA_URT1_TX=5,      /*!< to URT1 TX output */
    DMA_SPI0_TX=8,      /*!< to SPI0 MOSI output */
    DMA_GPL_Write=11,   /*!< to GPL function control */
    DMA_TM36_CC0B=12,   /*!< to TM36 channel 0 - buffer data */
    DMA_TM36_CC1B=13,   /*!< to TM36 channel 1 - buffer data */
    DMA_TM36_CC2B=14,   /*!< to TM36 channel 2 - buffer data */
    DMA_ASB0_TX=16,     /*!< to APX_ASB0_TX output */
    DMA_ASB1_TX=17,     /*!< to APX_ASB1_TX output */
    DMA_ASB2_TX=18,     /*!< to APX_ASB2_TX output */
    DMA_ASB3_TX=19      /*!< to APX_ASB3_TX output */
} DMA_DestinationRequestDef;
#endif


/** 
 * @enum		DMA_ExternTriggerPinDef
 * @brief		DMA channel external trigger pin select.
 */        
typedef enum 
{ 
    DMA_ExtTRG0=0,  /*!< control by DMA_TRG0 pin state  */
    DMA_ExtTRG1=1   /*!< control by DMA_TRG1 pin state  */
} DMA_ExternTriggerPinDef;

/** 
 * @enum		DMA_ChxCurrentStateDef
 * @brief		the current DMA channel state
 */        
typedef enum 
{ 
    DMA_HoldState,  /*!< DMA in holding state  */
    DMA_Running,    /*!< DMA running state  */
    DMA_Idle,       /*!< DMA finish state  */
    DMA_Finish      /*!< DMA idle state  */
} DMA_ChxCurrentStateDef;

/** 
 * @enum		DMA_LevelPriorityDef
 * @brief		config DMA level priority 
 */        
typedef enum 
{ 
    DMA_LowestPriority,     /*!< lowest priority  */
    DMA_NormalPriority,     /*!< normal priority  */
    DMA_HighPriority,       /*!< high priority  */
    DMA_HighestPriority     /*!< highest priority  */
} DMA_LevelPriorityDef;

#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
/** 
 * @enum		DMA_FGBUSWidfthDef
 * @brief		DMA flash-to-GPL transfer bus width select.
 */        
typedef enum 
{ 
    DMA_Flash2GPL_8bit,		/*!< 8bit  */
    DMA_Flash2GPL_32bit 	/*!< 32bit  */
} DMA_FGBUSWidfthDef;
#endif


/** 
 * @struct  DMA_BaseInitTypeDef
 * @brief   DMA Base channel initial structure
 */        
typedef struct __attribute__((packed))				
{ 
    DMA_ExternTriggerPinDef ExtTrgPin;  /*!< Specifies the extern trigger pin select.  
                                             This parameter can be a value of DMA_ExtTRG0/DMA_ExtTRG1 */	
    
    DMA_ExtTriggerModeDef ExtTrgMode;   /*!< select DMA channel 0 data through GPL macro 
                                             This parameter can be a value of DMA_DisableExtTrg/DMA_SingleExtTrg
                                             DMA_BlockExtTrg/DMA_DemandExtTrg */	
        
    DMAChannel_Struct* DMAChx;          /*!< Specifies the DMA channel : DMAChannel0/1/2 */ 
    
    FunctionalState	DMALoopCmd;			/*!< Specifies the DMA loop mode : 
                                             This parameter can be a value of ENABLE/DISABLE */ 
    
    FunctionalState SrcSINCSel;	        /*!< Specifies the DMA auto increase source address mode : 
                                             This parameter can be a value of ENABLE/DISABLE */ 
    
	FunctionalState DestDINCSel;		/*!< Specifies the DMA auto increase destination address mode : 
                                             This parameter can be a value of ENABLE/DISABLE */ 

	DMA_SourcenRequestDef SrcSymSel;	/*!< DMA channel transfer peripheral source select */ 

	DMA_DestinationRequestDef DestSymSel;/*!< DMA channel transfer peripheral destination select */
	
	DMA_BurstSizeDef BurstDataSize;     /*!< specifies DMA transfer burst size : 1/2/4 Bytes */ 
	    
	uint32_t DMATransferNUM;			/*!< Specifies the DMA transfer data count initial number.
                                             0 (0 meas 131072) ~ 131071 (transfer 65535 data) */

	void* DMASourceAddr;			    /*!< Specifies the DMA source memory address */

	void* DMADestinationAddr;		    /*!< Specifies the DMA destination memory address */
    
} DMA_BaseInitTypeDef;




/**
 * @name	Function announce
 *   		
 */ 
///@{  

void DMA_DeInit(DMA_Struct* DMAx);
void DMA_BaseInitStructure_Init(DMA_BaseInitTypeDef* DMA_BaseInitStruct);
void DMA_Base_Init(DMA_BaseInitTypeDef* DMA_BaseInitStruct);
void DMA_Cmd(FunctionalState NewState);
void DMA_SetExtraGPLChannel(DMA_Struct* DMAx,DMA_DataWithGPLDef GPLChxSel);
DMA_DataWithGPLDef DMA_GetCHxUseGPL(DMA_Struct* DMAx);
void DMA_PriorityMode_Select(DMA_Struct* DMAx, DMA_PriorityModeDef DMAPriorityModeSel);
#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
void DMA_FlashMode_Select(DMA_Struct* DMAx, DMA_FGBUSWidfthDef FGBSel);
#endif
void DMA_StartRequest(DMAChannel_Struct* DMAChx);
void DMA_Channel_Cmd(DMAChannel_Struct* DMAChx, FunctionalState NewState);
void DMA_SetBurstSize(DMAChannel_Struct* DMAChx, DMA_BurstSizeDef BurstSizeSel);
void DMA_LoopMode_Cmd(DMAChannel_Struct* DMAChx, FunctionalState NewState);
void DMA_LastCycle_Cmd(DMAChannel_Struct* DMAChx, FunctionalState NewState);
void DMA_Hold_Cmd(DMAChannel_Struct* DMAChx, FunctionalState NewState);
void DMA_IncreaseTxPerformance(DMAChannel_Struct* DMAChx, FunctionalState NewState);
void DMA_IncreaseRxPerformance(DMAChannel_Struct* DMAChx, FunctionalState NewState);
void DMA_SetExtTriggerMode(DMAChannel_Struct* DMAChx, DMA_ExtTriggerModeDef DMAExtTrgSel);
void DMA_SetExtTriggerPin(DMAChannel_Struct* DMAChx, DMA_ExternTriggerPinDef DMAExtTrgPinSel);
void DMA_AutoIncreaseDestinationAddress(DMAChannel_Struct* DMAChx, FunctionalState NewState);
void DMA_AutoIncreaseSourceAddress(DMAChannel_Struct* DMAChx, FunctionalState NewState);
void DMA_Destination_Select(DMAChannel_Struct* DMAChx, DMA_DestinationRequestDef DestinationMacroSel);
void DMA_Source_Select(DMAChannel_Struct* DMAChx, DMA_SourcenRequestDef SourceMacroSel);
void DMA_SetDestinationAddress(DMAChannel_Struct* DMAChx, void* DestinationAddress);
void DMA_SetSourceAddress(DMAChannel_Struct* DMAChx, void* SourceAddress);
uint32_t* DMA_GetCurrentSourceAddress(DMAChannel_Struct* DMAChx);
uint32_t* DMA_GetCurrentDestinationAddress(DMAChannel_Struct* DMAChx);
void DMA_SetTransferDataNumber(DMAChannel_Struct* DMAChx, uint32_t NumDatas);
uint32_t DMA_GetRemainDataCount(DMAChannel_Struct* DMAChx);
void DMA_SetPriority(DMAChannel_Struct* DMAChx, DMA_LevelPriorityDef DMALevelSel);
void DMA_SetChxSKIP3Mode(DMAChannel_Struct* DMAChx, FunctionalState NewState);
void DMA_IT_Config(DMAChannel_Struct* DMAChx, uint32_t DMA_ITSrc, FunctionalState NewState);
void DMA_ITEA_Cmd(DMA_Struct* DMAx, FunctionalState NewState);
DRV_Return DMA_GetSingleFlagStatus(DMA_Struct* DMAx, uint32_t DMA_ITSrc);
uint32_t DMA_GetAllFlagStatus(DMA_Struct* DMAx);
void DMA_ClearFlag(DMA_Struct* DMAx, uint32_t DMA_ITSrc);
DRV_Return DMA_GetChannelFlag(DMAChannel_Struct* DMAChx, DMA_ChannelFlagDef DMA_ChxITSrc);
void DMA_ClearChannelFlag(DMAChannel_Struct* DMAChx, DMA_ChannelFlagDef DMA_ChxITSrc);

///@}

#ifdef __cplusplus
}
#endif
#endif
