/**
 ******************************************************************************
 *
 * @file        MG32x02z_DMA_DRV.c
 *
 * @brief       This file provides firmware functions to manage the following 
 *              functionalities of the DMA peripheral.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.19
 * @date        2020/11/12
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




#include "MG32x02z_DMA_DRV.h"


/**
 * @brief  	simple define
 *
 */ 

/**
 * @name	Deinitial DMA to default condition
 *   		
 */ 
///@{  
/**
 *******************************************************************************
 * @brief       Deinitializes the DMA peripheral registers to their default reset 
 *			    values.
 * @details     Reset DMAx to default configuration
 * @return		No
 * @note 
 * @par         Example
 * @code
    DMA_DeInit(DMA);
 * @endcode
 *******************************************************************************
 */
void DMA_DeInit(DMA_Struct* DMAx)
{
    // interrupt
    DMAx->INT.W = 0x00000000;
    
    // channel 0
    DMAx->CH0A.W = 0x00000000;
    DMAx->CH0B.W = 0x00030000;
    DMAx->CH0NUM.W = 0x00000000;
    DMAx->CH0SSA.W = 0x00000000;
    DMAx->CH0DSA.W = 0x00000000;
    
#if defined(MG32_1ST) || defined(MG32_3RD) || defined(MG32_4TH)
    // channel 1
    DMAx->CH1A.W = 0x00000000;
    DMAx->CH1B.W = 0x00030000;
    DMAx->CH1NUM.W = 0x00000000;
    DMAx->CH1SSA.W = 0x00000000;
    DMAx->CH1DSA.W = 0x00000000;
    
    // channel 2
    DMAx->CH2A.W = 0x00000000;
    DMAx->CH2B.W = 0x00030000;
    DMAx->CH2NUM.W = 0x00000000;
    DMAx->CH2SSA.W = 0x00000000;
    DMAx->CH2DSA.W = 0x00000000;
#endif

#if defined(MG32_3RD)
    // channel 3
    DMAx->CH3A.W = 0x00000000;
    DMAx->CH3B.W = 0x00030000;
    DMAx->CH3NUM.W = 0x00000000;
    DMAx->CH3SSA.W = 0x00000000;
    DMAx->CH3DSA.W = 0x00000000;
    
    // channel 4
    DMAx->CH4A.W = 0x00000000;
    DMAx->CH4B.W = 0x00030000;
    DMAx->CH4NUM.W = 0x00000000;
    DMAx->CH4SSA.W = 0x00000000;
    DMAx->CH4DSA.W = 0x00000000;

#endif
    
    // Global control
    DMAx->CR0.W = 0x00000000;
    DMAx->STA.W = 0xFFFFFFFF;
}
///@}


/**
 * @name	Initializes the DMA Unit peripheral according to the specified\
 *          parameters in the DMA_BaseInitTypeDef.
 *   		
 */ 
///@{  
/**
 *******************************************************************************
 * @brief       Fills each DMA_BaseInitTypeDef member with its default value.
 * @param[in]   DMA_BaseInitStruct : pointer to a DMA_BaseInitTypeDef
 *        	    structure which will be initialized.
 * @return		No
 * @note 
 * @par         Example
 * @code
    DMA_BaseInitStructure_Init(&DMATestPattern);
 * @endcode
 *******************************************************************************
 */
 void DMA_BaseInitStructure_Init(DMA_BaseInitTypeDef* DMA_BaseInitStruct)
{
    // external trigger pin and mode config
    DMA_BaseInitStruct->ExtTrgPin = DMA_ExtTRG0;
    DMA_BaseInitStruct->ExtTrgMode = DMA_DisableExtTrg;
    
    // DMA channel select
    DMA_BaseInitStruct->DMAChx = DMAChannel0;
    
    // channel x loop mode config
    DMA_BaseInitStruct->DMALoopCmd = DISABLE;
    
    // channel x source/destination auto increase address
    DMA_BaseInitStruct->SrcSINCSel = ENABLE;
    DMA_BaseInitStruct->DestDINCSel = ENABLE;
    
    // DMA source peripheral config
    DMA_BaseInitStruct->SrcSymSel = DMA_MEM_Read;
    
    // DMA destination peripheral config
    DMA_BaseInitStruct->DestSymSel = DMA_MEM_Write;
    
    // DMA Burst size config
    DMA_BaseInitStruct->BurstDataSize = DMA_BurstSize_1Byte;
    
    // DMA transfer data count initial number
    DMA_BaseInitStruct->DMATransferNUM = 10;
    
    // source/destination config
    DMA_BaseInitStruct->DMASourceAddr = (void*) 0x20000000;
    DMA_BaseInitStruct->DMADestinationAddr = (void*) (0x20000000+10);
    
}

/**
 *******************************************************************************
 * @brief       Initializes the DMA peripheral according to 
 *			    the specified parameters in the DMA_BaseInitStruct.
 * @param[in]   DMA_BaseInitStruct : pointer to a DMA_BaseInitTypeDef
 *        	    structure that contains the configuration information for
 *        	    the specified DMA peripheral.
 * @return		No
 * @note 
 * @par         Example
 * @code
    DMA_Base_Init(&DMATestPattern);
 * @endcode
 *******************************************************************************
 */
void DMA_Base_Init(DMA_BaseInitTypeDef* DMA_BaseInitStruct)
{
    // external trigger pin and mode config
    DMA_SetExtTriggerPin(DMA_BaseInitStruct->DMAChx, DMA_BaseInitStruct->ExtTrgPin);
    DMA_SetExtTriggerMode(DMA_BaseInitStruct->DMAChx, DMA_BaseInitStruct->ExtTrgMode);
    
    // channel x loop mode config
    DMA_LoopMode_Cmd(DMA_BaseInitStruct->DMAChx, DMA_BaseInitStruct->DMALoopCmd);
    
    // channel x source/destination auto increase address
    DMA_AutoIncreaseSourceAddress(DMA_BaseInitStruct->DMAChx, DMA_BaseInitStruct->SrcSINCSel);
    DMA_AutoIncreaseDestinationAddress(DMA_BaseInitStruct->DMAChx, DMA_BaseInitStruct->DestDINCSel);
    
    // DMA source peripheral config
    DMA_Source_Select(DMA_BaseInitStruct->DMAChx, DMA_BaseInitStruct->SrcSymSel);
    
    // DMA destination peripheral config
    DMA_Destination_Select(DMA_BaseInitStruct->DMAChx, DMA_BaseInitStruct->DestSymSel);
    
    // DMA Burst size config
    DMA_SetBurstSize(DMA_BaseInitStruct->DMAChx, DMA_BaseInitStruct->BurstDataSize);
    
    // DMA transfer data count initial number
    DMA_SetTransferDataNumber(DMA_BaseInitStruct->DMAChx, DMA_BaseInitStruct->DMATransferNUM);
    
    // source/destination config
    if (DMA_BaseInitStruct->SrcSymSel == DMA_MEM_Read)
        DMA_SetSourceAddress(DMA_BaseInitStruct->DMAChx, DMA_BaseInitStruct->DMASourceAddr);
    if (DMA_BaseInitStruct->DestSymSel == DMA_MEM_Write)
        DMA_SetDestinationAddress(DMA_BaseInitStruct->DMAChx, DMA_BaseInitStruct->DMADestinationAddr);
    
}
///@}



/**
 * @name	Enable/Disable DMA unit peripheral
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    Enable or Disable DMA macro
 * @param[in] 	NewState: new state of DMA
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    DMA_Cmd(ENABLE);
 * @endcode
 *******************************************************************************
 */
void DMA_Cmd(FunctionalState NewState)
{
    DMA->CR0.MBIT.EN = NewState;

}
///@}


/**
 * @name	DMA global control riutine 
 *   		
 */ 
///@{  
/**
 *******************************************************************************
 * @brief       specified GPL data from Channel X.
 * @param[in] 	DMAx : specifies the DMA.
 * @param[in] 	GPLChxSel : specifies the DMA GPL source to check.
 * @arg\b	    DMA_GPL_DISABLE: no any channel with GPL function
 * @arg\b	    DMA_GPL_CHANNEL_0: select DMA channel 0 data through GPL macro
 * @arg\b	    DMA_GPL_CHANNEL_1: select DMA channel 1 data through GPL macro 
 * @arg\b	    DMA_GPL_CHANNEL_2: select DMA channel 2 data through GPL macro 
 * @arg\b	    DMA_GPL_CHANNEL_3: select DMA channel 3 data through GPL macro 
 * @arg\b	    DMA_GPL_CHANNEL_4: select DMA channel 4 data through GPL macro 
 * @return		none
 * @note 
 * @par         Example
 * @code
    DMA_SetExtraGPLChannel(DMA, DMA_GPL_CHANNEL_0);
 * @endcode
 *******************************************************************************
 */
void DMA_SetExtraGPLChannel(DMA_Struct* DMAx,DMA_DataWithGPLDef GPLChxSel)
{
    DMAx->CR0.MBIT.GPL_CHS = GPLChxSel;
}

/**
 *******************************************************************************
 * @brief       Get DMA GPL Channel Select.
 * @param[in] 	DMAx : specifies the DMA.
 * @return		DMA_DataWithGPLDef declare 
 * @arg\b	    DMA_GPL_DISABLE: no any channel with GPL function
 * @arg\b	    DMA_GPL_CHANNEL_0: select DMA channel 0 data through GPL macro
 * @arg\b	    DMA_GPL_CHANNEL_1: select DMA channel 1 data through GPL macro 
 * @arg\b	    DMA_GPL_CHANNEL_2: select DMA channel 2 data through GPL macro 
 * @arg\b	    DMA_GPL_CHANNEL_3: select DMA channel 2 data through GPL macro 
 * @arg\b	    DMA_GPL_CHANNEL_4: select DMA channel 2 data through GPL macro 
 * @note 
 * @par         Example
 * @code
    DMA_GetCHxUseGPL(DMA);
 * @endcode
 *******************************************************************************
 */
DMA_DataWithGPLDef DMA_GetCHxUseGPL(DMA_Struct* DMAx)
{
    return (DMA_DataWithGPLDef) DMAx->CR0.MBIT.GPL_CHS;
}

/**
 *******************************************************************************
 * @brief       DMA channel priority mode select. 
 * @param[in] 	DMAx : specifies the DMA.
 * @param[in] 	DMAPriorityModeSel : specifies the DMA priority mode
 * @arg\b	    DMA_Round_Robin: control by Round Robin method
 * @arg\b	    DMA_Priority_Level:  control by channel priority level
 * @return		none
 * @note 
 * @par         Example
 * @code
    DMA_PriorityMode_Select(DMA, DMA_Round_Robin);
 * @endcode
 *******************************************************************************
 */
void DMA_PriorityMode_Select(DMA_Struct* DMAx, DMA_PriorityModeDef DMAPriorityModeSel)
{
#if defined(MG32_1ST) || defined(MG32_3RD) || defined(MG32_4TH)
    DMAx->CR0.MBIT.PRI_MDS = DMAPriorityModeSel;
#else
    // No function
    if (DMAPriorityModeSel > 10)
        DMAx->STA.B[0] |= 0;
#endif
}

#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
/**
 *******************************************************************************
 * @brief       Config DMA flash data width. 
 * @param[in] 	DMAx : specifies the DMA.
 * @param[in] 	FGBSel : Specifies the DMA flash-to-GPL transfer bus width select.
 * @arg\b	    DMA_Flash2GPL_8bit: 8bit bus width.
 * @arg\b	    DMA_Flash2GPL_32bit: Only support Flash to GPL with 32bit.
 * @return		none
 * @note 
 * @par         Example
 * @code
    DMA_FlashMode_Select(DMA, DMA_Flash2GPL_8bit);
 * @endcode
 *******************************************************************************
 */
void DMA_FlashMode_Select(DMA_Struct* DMAx, DMA_FGBUSWidfthDef FGBSel)
{
    DMAx->CR0.MBIT.FGBUS_SEL = FGBSel;
}
#endif
///@}



/**
 * @name	DMA channel control riutine 
 *   		
 */ 
///@{  
/**
 *******************************************************************************
 * @brief	    Start DMA channel data transfer request
 * @param[in] 	DMAChx: specifies the DMA channel 
 *      	    This parameter can be DMAChannelx where x: 0,1,2,3 or 4 to select the 
 *              DMA peripheral.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    DMA_StartRequest(DMAChannel2);
 * @endcode
 *******************************************************************************
 */
void DMA_StartRequest(DMAChannel_Struct* DMAChx)
{
    DMAChx->A.MBIT.REQ = 1;
}



/**
 *******************************************************************************
 * @brief	    Enable/Disable DMA channel transfer 
 * @param[in] 	DMAChx: specifies the DMA channel 
 *      	    This parameter can be DMAChannelx where x: 0,1,2,3 or 4 to select the 
 *              DMA peripheral.
 * @param[in] 	NewState: new state of the DMAChannelx
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    DMA_Channel_Cmd(DMAChannel2, ENABLE);
 * @endcode
 *******************************************************************************
 */
void DMA_Channel_Cmd(DMAChannel_Struct* DMAChx, FunctionalState NewState)
{
    DMAChx->A.MBIT.EN = NewState;
}

/**
 *******************************************************************************
 * @brief	    Config DMA Burst transfer size
 * @param[in] 	DMAChx: specifies the DMA channel 
 *      	    This parameter can be DMAChannelx where x: 0,1,2,3 or 4 to select the 
 *              DMA peripheral.
 * @param[in] 	BurstSizeSel: specifies the number of tranfers 
 *  @arg\b	    DMA_BurstSize_1Byte : 1 byte
 *	@arg\b	    DMA_BurstSize_2Byte : 2 bytes
 *	@arg\b	    DMA_BurstSize_4Byte : 4 bytes
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    DMA_SetBurstSize(DMAChannel0, DMA_BurstSize_2Byte);     // e.g. DMA M2P (TM36_OC0) - 2 bytes
 * @endcode
 *******************************************************************************
 */
void DMA_SetBurstSize(DMAChannel_Struct* DMAChx, DMA_BurstSizeDef BurstSizeSel)
{
    DMAChx->A.MBIT.BSIZE = BurstSizeSel;
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable DMA channel loop mode transfer 
 * @param[in] 	DMAChx: specifies the DMA channel 
 *      	    This parameter can be DMAChannelx where x: 0,1,2,3 or 4 to select the 
 *              DMA peripheral.
 * @param[in] 	NewState: new state of the loop mode
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    DMA_LoopMode_Cmd(DMAChannel0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void DMA_LoopMode_Cmd(DMAChannel_Struct* DMAChx, FunctionalState NewState)
{
    DMAChx->A.MBIT.LOOP = NewState;
}


/**
 *******************************************************************************
 * @brief	    Enable/Disable the last cycle of DMA transmission for DMA Loop 
 *              mode.
 * @param[in] 	DMAChx: specifies the DMA channel 
 *      	    This parameter can be DMAChannelx where x: 0,1,2,3 or 4 to select the 
 *              DMA peripheral.
 * @param[in] 	NewState: new state of the loop mode
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note        1. Must clear DMA Channel0/1/2 TCF flag before enable this function
 * @note        2. Must clear this function after DMA complete 
 * @note 
 * @par         Example
 * @code
    DMA_ClearFlag(DMA, DMA_FLAG_CH0_TCF);
    DMA_LastCycle_Cmd(DMAChannel0, ENABLE);
    
    // wait for DMA Channel0 complete
    while(DMA_GetSingleFlagStatus(DMA, DMA_FLAG_CH0_THF) == DRV_UnHappened);
    
    DMA_ClearFlag(DMA, DMA_FLAG_CH0_TCF);
    DMA_LastCycle_Cmd(DMAChannel0, DISABLE);
    
 * @endcode
 *******************************************************************************
 */
void DMA_LastCycle_Cmd(DMAChannel_Struct* DMAChx, FunctionalState NewState)
{
#if defined(MG32_1ST)
    if(DMAChx == DMAChannel0)
        SYS->CR0.MBIT.CH0_LAST = NewState;
    else if (DMAChx == DMAChannel1)
        SYS->CR0.MBIT.CH1_LAST = NewState;
    else if (DMAChx == DMAChannel2)
        SYS->CR0.MBIT.CH2_LAST = NewState;
    
    return;
#endif
#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
    DMAChx->A.MBIT.LAST = NewState;
    return;
#endif
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable hold DMA channel transfer 
 * @param[in] 	DMAChx: specifies the DMA channel 
 *      	    This parameter can be DMAChannelx where x: 0,1,2,3 or 4 to select the 
 *              DMA peripheral.
 * @param[in] 	NewState: new state of the holding mode
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    // Hold DMA Channel0 transmission
    DMA_Hold_Cmd(DMAChannel0, ENABLE);
    
    // to do ...    
    
    // Disable Hold & Continue DMA Channel0 transmission
    DMA_Hold_Cmd(DMAChannel0, DISABLE);
    
 * @endcode
 *******************************************************************************
 */
void DMA_Hold_Cmd(DMAChannel_Struct* DMAChx, FunctionalState NewState)
{
    DMAChx->A.MBIT.HOLD = NewState;
}



/**
 *******************************************************************************
 * @brief	    DMA channel external pin trigger request mode select. 
 * @param[in] 	DMAChx: specifies the DMA channel 
 *      	    This parameter can be DMAChannelx where x: 0,1,2,3 or 4 to select the 
 *              DMA peripheral.
 * @param[in] 	DMAExtTrgSel: specifies the External Trigger equest mode
 *  @arg\b	    DMA_DisableExtTrg : disable external request pin input
 *	@arg\b	    DMA_SingleExtTrg : single request mode
 *	@arg\b	    DMA_BlockExtTrg : block request mode
 *	@arg\b	    DMA_DemandExtTrg : demand request mode (active high)
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    DMA_SetExtTriggerMode(DMAChannel2, DMA_SingleExtTrg);
 * @endcode
 *******************************************************************************
 */
void DMA_SetExtTriggerMode(DMAChannel_Struct* DMAChx, DMA_ExtTriggerModeDef DMAExtTrgSel)
{
    DMAChx->A.MBIT.XMDS = DMAExtTrgSel;
}

/**
 *******************************************************************************
 * @brief	    DMA channel external trigger pin select.
 * @param[in] 	DMAChx: specifies the DMA channel 
 *      	    This parameter can be DMAChannelx where x: 0,1,2,3 or 4 to select the 
 *              DMA peripheral.
 * @param[in] 	DMAExtTrgPinSel: specifies the External Trigger pin from
 *  @arg\b	    DMA_ExtTRG0 : control by DMA_TRG0 pin state
 *	@arg\b	    DMA_ExtTRG1 : control by DMA_TRG1 pin state
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    DMA_SetExtTriggerPin(DMAChannel1, DMA_ExtTRG1);
 * @endcode
 *******************************************************************************
 */
void DMA_SetExtTriggerPin(DMAChannel_Struct* DMAChx, DMA_ExternTriggerPinDef DMAExtTrgPinSel)
{
#if defined(MG32_1ST) || defined(MG32_3RD) || defined(MG32_4TH)
    DMAChx->B.MBIT.XPIN = DMAExtTrgPinSel;
#else
    // No function
    if (DMAExtTrgPinSel > 10)
        DMAChx->B.B[0] |= 0;
#endif
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable DMA destination (memory) transfer address auto 
 *              increased 
 * @param[in] 	DMAChx: specifies the DMA channel 
 *      	    This parameter can be DMAChannelx where x: 0,1,2,3 or 4 to select the 
 *              DMA peripheral.
 * @param[in] 	NewState: new state of the Auto increase destination address
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    DMA_AutoIncreaseDestinationAddress(DMAChannel2, ENABLE);
 * @endcode
 *******************************************************************************
 */
void DMA_AutoIncreaseDestinationAddress(DMAChannel_Struct* DMAChx, FunctionalState NewState)
{
    DMAChx->B.MBIT.DINC = NewState;
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable DMA source (memory) transfer address auto 
 *              increased 
 * @param[in] 	DMAChx: specifies the DMA channel 
 *      	    This parameter can be DMAChannelx where x: 0,1,2,3 or 4 to select the 
 *              DMA peripheral.
 * @param[in] 	NewState: new state of the Auto increase source address
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    DMA_AutoIncreaseSourceAddress(DMAChannel0, DISABLE);
 * @endcode
 *******************************************************************************
 */
void DMA_AutoIncreaseSourceAddress(DMAChannel_Struct* DMAChx, FunctionalState NewState)
{
    DMAChx->B.MBIT.SINC = NewState;
}

/**
 *******************************************************************************
 * @brief	    Select DMA channel Destination Request peripheral
 * @param[in] 	DMAChx: specifies the DMA channel 
 *      	    This parameter can be DMAChannelx where x: 0,1,2,3 or 4 to select the 
 *              DMA peripheral.
 * @param[in] 	DestinationMacroSel: specifies the destination peripheral
 *  @arg\b	    DMA_MEM_Write : to memory
 *  @arg\b	    DMA_DAC0_OUT : to DAC output control 
 *	@arg\b	    DMA_I2C0_TX : to I2C0 output
 *	@arg\b	    DMA_I2C1_TX : to I2C1 output
 *  @arg\b	    DMA_URT0_TX : to URT0 TX outputt
 *	@arg\b	    DMA_URT1_TX : to URT1 TX output
 *	@arg\b	    DMA_URT2_TX : to URT2 TX output
 *	@arg\b	    DMA_URT3_TX : to URT3 TX output
 *  @arg\b	    DMA_SPI0_TX : to SPI0 MOSI output
 *	@arg\b	    DMA_GPL_Write : to GPL function control 
 *	@arg\b	    DMA_TM36_CC0B : to TM36 channel 0 - buffer data 
 *	@arg\b	    DMA_TM36_CC1B : to TM36 channel 1 - buffer data 
 *	@arg\b	    DMA_TM36_CC2B : to TM36 channel 2 - buffer data 
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    DMA_Destination_Select(DMAChannel2, DMA_URT0_TX);
 * @endcode
 *******************************************************************************
 */
void DMA_Destination_Select(DMAChannel_Struct* DMAChx, DMA_DestinationRequestDef DestinationMacroSel)
{
    DMAChx->B.MBIT.DET = DestinationMacroSel;
}

/**
 *******************************************************************************
 * @brief	    Select DMA channel Source Request peripheral
 * @param[in] 	DMAChx: specifies the DMA channel 
 *      	    This parameter can be DMAChannelx where x: 0,1,2,3 or 4 to select the 
 *              DMA peripheral.
 * @param[in] 	SourceMacroSel: specifies the source peripheral
 *  @arg\b	    DMA_MEM_Read : from memory 
 *	@arg\b	    DMA_ADC0_IN : from ADC conversion data
 *	@arg\b	    DMA_I2C0_RX : from I2C0 external in data 
 *	@arg\b	    DMA_I2C1_RX : from I2C1 external in data 
 *  @arg\b	    DMA_URT0_RX : from URT0 RX data 
 *	@arg\b	    DMA_URT1_RX : from URT1 RX data 
 *	@arg\b	    DMA_URT2_RX : from URT2 RX data 
 *	@arg\b	    DMA_URT3_RX : from URT3 RX data 
 *  @arg\b	    DMA_SPI0_RX : from SPI0 MISO in data 
 *	@arg\b	    DMA_TM36_IC3 : from TM36 capture data
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    DMA_Source_Select(DMAChannel0, DMA_MEM_Read);
 * @endcode
 *******************************************************************************
 */
void DMA_Source_Select(DMAChannel_Struct* DMAChx, DMA_SourcenRequestDef SourceMacroSel)
{
    DMAChx->B.MBIT.SRC = SourceMacroSel;
}

/**
 *******************************************************************************
 * @brief	    declare DMA destination memory address 
 * @param[in] 	DMAChx: specifies the DMA channel 
 *      	    This parameter can be DMAChannelx where x: 0,1,2,3 or 4 to select the 
 *              DMA peripheral.
 * @param[in] 	DestinationAddress: specifies destination memory address
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    DMA_SetDestinationAddress(DMAChannel2, ptrDestinationArrayAddress);
 * @endcode
 *******************************************************************************
 */
void DMA_SetDestinationAddress(DMAChannel_Struct* DMAChx, void* DestinationAddress)
{
    DMAChx->DSA.W = (uint32_t) DestinationAddress;
}
   
/**
 *******************************************************************************
 * @brief	    declare DMA source memory address 
 * @param[in] 	DMAChx: specifies the DMA channel 
 *      	    This parameter can be DMAChannelx where x: 0,1,2,3 or 4 to select the 
 *              DMA peripheral.
 * @param[in] 	SourceAddress: specifies source memory address
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    DMA_SetSourceAddress(DMAChannel0, ptrSourceArrayAddress);
 * @endcode
 *******************************************************************************
 */
void DMA_SetSourceAddress(DMAChannel_Struct* DMAChx, void* SourceAddress)
{
    DMAChx->SSA.W = (uint32_t) SourceAddress;
}

/**
 *******************************************************************************
 * @brief	    Get DMA channel x source current address register
 * @param[in] 	DMAChx: specifies the DMA channel 
 *      	    This parameter can be DMAChannelx where x: 0,1,2,3 or 4 to select the 
 *              DMA peripheral.
 * @return 	    DMA source or memory transfer current address. 
 * @note 
 * @par         Example
 * @code
    tmp = (uint32*) DMA_GetCurrentSourceAddress(DMAChannel2);
 * @endcode
 *******************************************************************************
 */
uint32_t* DMA_GetCurrentSourceAddress(DMAChannel_Struct* DMAChx)
{
    return (uint32_t*) DMAChx->SCA.W;
}

/**
 *******************************************************************************
 * @brief	    Get DMA channel-0 destination current address register
 * @param[in] 	DMAChx: specifies the DMA channel 
 *      	    This parameter can be DMAChannelx where x: 0,1,2,3 or 4 to select the 
 *              DMA peripheral.
 * @return 	    DMA destination or memory transfer current address. 
 * @note 
 * @par         Example
 * @code
    tmp = DMA_GetCurrentDestinationAddress(DMAChannel0);
 * @endcode
 *******************************************************************************
 */
uint32_t* DMA_GetCurrentDestinationAddress(DMAChannel_Struct* DMAChx)
{
    return (uint32_t*) DMAChx->DCA.W;
}

/**
 *******************************************************************************
 * @brief	    Config DMA transfer data count initial number
 * @param[in] 	DMAChx: specifies the DMA channel 
 *      	    This parameter can be DMAChannelx where x: 0,1,2,3 or 4 to select the 
 *              DMA peripheral.
 * @param[in] 	NumDatas: specifies the number of data  
 * @return 	    none
 * @note        This register value must equal the integer multiples of 
 *              Burst Size setting 
 * @note 
 * @par         Example
 * @code
    DMA_SetTransferDataNumber(DMAChannel0, 256);
 * @endcode
 *******************************************************************************
 */
void DMA_SetTransferDataNumber(DMAChannel_Struct* DMAChx, uint32_t NumDatas)
{
    DMAChx->NUM.W = NumDatas;
}

/**
 *******************************************************************************
 * @brief	    Get DMA transfer data count current value
 * @param[in] 	DMAChx: specifies the DMA channel 
 *      	    This parameter can be DMAChannelx where x: 0,1,2,3 or 4 to select the 
 *              DMA peripheral.
 * @return 	    get remain the current count value
 * @note        This register value must equal the integer multiples of 
 *              Burst Size setting 
 * @note 
 * @par         Example
 * @code
    tmp = DMA_GetRemainDataCount(DMAChannel1);
 * @endcode
 *******************************************************************************
 */
uint32_t DMA_GetRemainDataCount(DMAChannel_Struct* DMAChx)
{
    return DMAChx->CNT.W;
}

/**
 *******************************************************************************
 * @brief	    Set DMA channel priority of level mode
 * @param[in] 	DMAChx: specifies the DMA channel 
 *      	    This parameter can be DMAChannelx where x: 0,1,2,3 or 4 to select the 
 *              DMA peripheral.
 * @param[in] 	DMALevelSel: specifies the priority of level mode
 *  @arg\b	    DMA_LowestPriority : lowest priority
 *	@arg\b	    DMA_NormalPriority : normal priority
 *	@arg\b	    DMA_HighPriority : high priority
 *	@arg\b	    DMA_HighestPriority : highest priority
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    DMA_SetPriority(DMAChannel0, DMA_HighPriority);
 * @endcode
 *******************************************************************************
 */
void DMA_SetPriority(DMAChannel_Struct* DMAChx, DMA_LevelPriorityDef DMALevelSel)
{
#if defined(MG32_1ST) || defined(MG32_3RD) || defined(MG32_4TH)
    DMAChx->A.MBIT.PLS = DMALevelSel;
#else
    // No function
    if (DMALevelSel > 10)
        DMAChx->B.B[0] |= 0;
#endif
}

///@}

/**
 * @name	only support SKIP3 mode for channel 0 (memory to memory mode) 
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    Config DMA channelx skip 3 mode (in memory to memory)
 * @param[in] 	DMAChx: specifies the DMA channel 
 *      	    This parameter can be DMAChannelx where x: 0,1,2,3 or 4 to select the 
 *              DMA peripheral.
 * @param[in] 	NewState: new state of the channel 0 SKIP3 mode
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note 
 * @par         Example
 * @code
    // Enable DMA Channel2 with SKIP3 mode
    DMA_SetChxSKIP3Mode(DMAChannel2, ENABLE);
 * @endcode
 *******************************************************************************
 */
void DMA_SetChxSKIP3Mode(DMAChannel_Struct* DMAChx, FunctionalState NewState)
{
    DMAChx->A.MBIT.ADSEL = NewState;
}
///@}

/**
 * @name	interrupt and flag (SET/CLEAR/Config) 
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief	    config interrupt source (Enable/Disable)
 * @param[in] 	DMAChx: specifies the DMA channel 
 *      	    This parameter can be DMAChannelx where x: 0,1,2,3 or 4 to select the 
 *              DMA peripheral.
 * @param[in] 	DMA_ITSrc: Enable/Disable interrupt source 
 *  @arg\b	    DMA_Error_ITE : transfer error interrupt enable 
 *  @arg\b	    DMA_Half_ITE : transfer half interrupt enable
 *  @arg\b	    DMA_Complete_ITE : transfer complete interrupt enable
 * @param[in] 	NewState: new state of the DMAx interrupt key.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note        
 * @note 
 * @par         Example
 * @code
    // Enable DMA Channel1 Complete Flag for interrupt
    DMA_IT_Config(DMAChannel1, DMA_Complete_ITE, ENABLE);
 * @endcode
 *******************************************************************************
 */
void DMA_IT_Config(DMAChannel_Struct* DMAChx, uint32_t DMA_ITSrc, FunctionalState NewState)
{
    if (NewState == ENABLE)
        DMAChx->A.B[2] |= DMA_ITSrc;
    else
        DMAChx->A.B[2] &= ~DMA_ITSrc;
}

/**
 *******************************************************************************
 * @brief	    Enable/Disable all interrupt 
 * @param[in]   DMAx: where x can be 0 peripheral.
 * @param[in] 	NewState: new state of the DMAx all interrupt key.
 *      	    This parameter can be: ENABLE or DISABLE.
 * @return 	    none
 * @note        
 * @note 
 * @par         Example
 * @code
    DMA_ITEA_Cmd(DMA, ENABLE);
 * @endcode
 *******************************************************************************
 */
void DMA_ITEA_Cmd(DMA_Struct* DMAx, FunctionalState NewState)
{
    DMAx->INT.MBIT.IEA = NewState;
}

/**
 *******************************************************************************
 * @brief	    Get one interrupt source state
 * @param[in]   DMAx: where x can be 0 peripheral.
 * @param[in] 	DMA_ITSrc: interrupt source item
 *  @arg\b	    DMA_FLAG_CH4_ERRF : DMA channel-4 transfer error flag
 *  @arg\b	    DMA_FLAG_CH4_THF : DMA channel-4 transfer half flag
 *  @arg\b	    DMA_FLAG_CH4_TCF : DMA channel-4 transfer complete flag
 *  @arg\b	    DMA_FLAG_CH4_GIF : DMA channel-4 global interrupt flag
 *  @arg\b	    DMA_FLAG_CH3_ERRF : DMA channel-3 transfer error flag
 *  @arg\b	    DMA_FLAG_CH3_THF : DMA channel-3 transfer half flag
 *  @arg\b	    DMA_FLAG_CH3_TCF : DMA channel-3 transfer complete flag
 *  @arg\b	    DMA_FLAG_CH3_GIF : DMA channel-3 global interrupt flag
 *  @arg\b	    DMA_FLAG_CH2_ERRF : DMA channel-2 transfer error flag
 *  @arg\b	    DMA_FLAG_CH2_THF : DMA channel-2 transfer half flag
 *  @arg\b	    DMA_FLAG_CH2_TCF : DMA channel-2 transfer complete flag
 *  @arg\b	    DMA_FLAG_CH2_GIF : DMA channel-2 global interrupt flag
 *  @arg\b	    DMA_FLAG_CH1_ERRF : DMA channel-1 transfer error flag
 *  @arg\b	    DMA_FLAG_CH1_THF : DMA channel-1 transfer half flag
 *  @arg\b	    DMA_FLAG_CH1_TCF : DMA channel-1 transfer complete flag
 *  @arg\b	    DMA_FLAG_CH1_GIF : DMA channel-1 global interrupt flag
 *  @arg\b	    DMA_FLAG_CH0_ERRF : DMA channel-0 transfer error flag
 *  @arg\b	    DMA_FLAG_CH0_THF : DMA channel-0 transfer half flag
 *  @arg\b	    DMA_FLAG_CH0_TCF : DMA channel-0 transfer complete flag
 *  @arg\b	    DMA_FLAG_CH0_GIF : DMA channel-0 global interrupt flag
 * @return 	    The new state of DRV_Return(DRV_Happened or DRV_UnHappened)
 * @note        
 * @note 
 * @par         Example
 * @code
    if (DMA_GetSingleFlagStatus(DMA, DMA_FLAG_CH1_THF) == DRV_Happened) 
    {
        // to do ....
    }    
 * @endcode
 *******************************************************************************
 */
DRV_Return DMA_GetSingleFlagStatus(DMA_Struct* DMAx, uint32_t DMA_ITSrc)
{
    if (DMAx->STA.W & DMA_ITSrc)
        return DRV_Happened;
    else 
        return DRV_UnHappened;
    
}

/**
 *******************************************************************************
 * @brief	    Get all interrupt source state
 * @param[in]   DMAx: where x can be 0 peripheral.
 * @return 	    response what happended of STA
 * @note        
 * @note 
 * @par         Example
 * @code
    tmp = DMA_GetAllFlagStatus(DMA);
 * @endcode
 *******************************************************************************
 */
uint32_t DMA_GetAllFlagStatus(DMA_Struct* DMAx)
{
    return DMAx->STA.W;
}

/**
 *******************************************************************************
 * @brief	    Clear one or all interrupt source state
 * @param[in]   DMAx: where x can be 0 peripheral.
 * @param[in] 	DMA_ITSrc: interrupt source item
 *  @arg\b	    DMA_FLAG_CH4_ERRF : DMA channel-4 transfer error flag
 *  @arg\b	    DMA_FLAG_CH4_THF : DMA channel-4 transfer half flag
 *  @arg\b	    DMA_FLAG_CH4_TCF : DMA channel-4 transfer complete flag
 *  @arg\b	    DMA_FLAG_CH4_GIF : DMA channel-4 global interrupt flag
 *  @arg\b	    DMA_FLAG_CH3_ERRF : DMA channel-3 transfer error flag
 *  @arg\b	    DMA_FLAG_CH3_THF : DMA channel-3 transfer half flag
 *  @arg\b	    DMA_FLAG_CH3_TCF : DMA channel-3 transfer complete flag
 *  @arg\b	    DMA_FLAG_CH3_GIF : DMA channel-3 global interrupt flag
 *  @arg\b	    DMA_FLAG_CH2_ERRF : DMA channel-2 transfer error flag
 *  @arg\b	    DMA_FLAG_CH2_THF : DMA channel-2 transfer half flag
 *  @arg\b	    DMA_FLAG_CH2_TCF : DMA channel-2 transfer complete flag
 *  @arg\b	    DMA_FLAG_CH2_GIF : DMA channel-2 global interrupt flag
 *  @arg\b	    DMA_FLAG_CH1_ERRF : DMA channel-1 transfer error flag
 *  @arg\b	    DMA_FLAG_CH1_THF : DMA channel-1 transfer half flag
 *  @arg\b	    DMA_FLAG_CH1_TCF : DMA channel-1 transfer complete flag
 *  @arg\b	    DMA_FLAG_CH1_GIF : DMA channel-1 global interrupt flag
 *  @arg\b	    DMA_FLAG_CH0_ERRF : DMA channel-0 transfer error flag
 *  @arg\b	    DMA_FLAG_CH0_THF : DMA channel-0 transfer half flag
 *  @arg\b	    DMA_FLAG_CH0_TCF : DMA channel-0 transfer complete flag
 *  @arg\b	    DMA_FLAG_CH0_GIF : DMA channel-0 global interrupt flag
 * @return 	    none
 * @note        
 * @note 
 * @par         Example
 * @code
    // Clear DMA Channel0/1/2 TCF flag
    DMA_ClearFlag(DMA, (DMA_FLAG_CH0_TCF | DMA_FLAG_CH1_TCF | DMA_FLAG_CH2_TCF));
 * @endcode
 *******************************************************************************
 */
void DMA_ClearFlag(DMA_Struct* DMAx, uint32_t DMA_ITSrc)
{
    DMAx->STA.W = DMA_ITSrc;
}


/**
 *******************************************************************************
 * @brief	    Get one or all interrupt source state
 * @param[in] 	DMAChx: specifies the DMA channel 
 *      	    This parameter can be DMAChannelx where x: 0,1,2,3 or 4 to select the 
 *              DMA peripheral.
 * @param[in] 	DMA_ChxITSrc: interrupt source item
 *  @arg\b	    DMA_Chx_TCF : select DMA channel x complete flag
 *  @arg\b	    DMA_Chx_THF : select DMA channel x half flag
 *  @arg\b	    DMA_Chx_ERRF : select DMA channel x error flag
 *  @arg\b	    DMA_Chx_AllFlags : Select DMA channel x all flags
 * @return 	    The new state of DRV_Return(DRV_Happened or DRV_UnHappened)
 * @note        
 * @note 
 * @par         Example
 * @code
    if (DMA_GetChannelFlag(DMA, DMA_Chx_TCF) == DRV_Happened) 
    {
        // to do ....
    }    
 * @endcode
 *******************************************************************************
 */
DRV_Return DMA_GetChannelFlag(DMAChannel_Struct* DMAChx, DMA_ChannelFlagDef DMA_ChxITSrc)
{
    if (DMAChx->A.B[3] & DMA_ChxITSrc)
        return DRV_Happened;
    else 
        return DRV_UnHappened;
    
}

/**
 *******************************************************************************
 * @brief	    Clear one or all interrupt source state
 * @param[in] 	DMAChx: specifies the DMA channel 
 *      	    This parameter can be DMAChannelx where x: 0,1,2,3 or 4 to select the 
 *              DMA peripheral.
 * @param[in] 	DMA_ChxITSrc: interrupt source item
 *  @arg\b	    DMA_Chx_TCF : select DMA channel x complete flag
 *  @arg\b	    DMA_Chx_THF : select DMA channel x half flag
 *  @arg\b	    DMA_Chx_ERRF : select DMA channel x error flag
 *  @arg\b	    DMA_Chx_AllFlags : Select DMA channel x all flags
 * @return 	    none
 * @note        
 * @note 
 * @par         Example
 * @code
    // Clear DMA Channel1 TCF flag
    DMA_ClearChannelFlag(DMAChannel1, DMA_Chx_TCF);
 * @endcode
 *******************************************************************************
 */
void DMA_ClearChannelFlag(DMAChannel_Struct* DMAChx, DMA_ChannelFlagDef DMA_ChxITSrc)
{
    DMAChx->A.B[3] = DMA_ChxITSrc;
}
///@}
