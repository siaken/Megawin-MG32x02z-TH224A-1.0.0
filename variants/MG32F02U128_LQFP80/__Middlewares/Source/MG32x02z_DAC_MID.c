/**
 ******************************************************************************
 *
 * @file        MG32x02z_DAC_MID.c
 *
 * @brief       This file provides firmware functions to manage the following 
 *              functionalities of the DAC peripheral:
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.04
 * @date        2022/09/16
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



#include "MG32x02z_DAC_MID.h"


static void DAC_DMAConvCplt(DMA_HandleTypeDef *hdma);   
static void DAC_DMAHalfConvCplt(DMA_HandleTypeDef *hdma);   
static void DAC_DMAError(DMA_HandleTypeDef *hdma);   



 /**
 * @name	Initial/Deinitial DAC with DAC_HandleTypeDef
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief       Initialize the DAC peripheral according to the specified parameters
 *              in structure "DAC_InitTypeDef"  and initialize the associated handle.
 * @param[in]   mDAC : pointer to a DAC_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    DAC_HandleTypeDef mDAC;
    
    mDAC.Instance                   = DAC;
    mDAC.Init.TriggerConverionSrc   = DAC_TRIGGERSOURCE_WRITE_DAT0; // Write DAC_DAT0 to update DAC output
    mDAC.Init.TriggerConverionEdge  = DAC_RISING_EDGE_UPDATE;       // No function when select WRITE_DAT
    mDAC.Init.DataAlign             = DAC_ALIGN_10B_R;              // DAC data is 10bit /w right justif
    mDAC.Init.OutputLevel           = DAC_OUTPUTCURRENT_MODE1;      // DAC output ~1mA 
    mDAC.Init.InteruptMode          = DAC_IT_READY;                 // DAC will trigger INT when READY flag happened.
    mDAC.State                      = MID_DAC_STATE_RESET;          // Reset state    
    
    MID_DAC_Init(&mDAC);
 
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_DAC_Init(DAC_HandleTypeDef* mDAC)
{
    uint32_t tmpREG;
    
    /* Check DAC handle */
    if(mDAC == NULL) 
    {
        return MID_FAILURE;
    }
    
    if(mDAC->State == MID_DAC_STATE_RESET) 
    {
        /* Allocate lock resource and initialize it */
        mDAC->Lock = MID_UnLocked;

        /* Init the low level hardware */
        MID_DAC_MspInit(mDAC);
    }
    
        
    /* Change DAC peripheral state */
    mDAC->State = MID_DAC_STATE_BUSY;

    // ------------------------------------------------------------------------
    /* Config of DAC parameters:                                              */
    // ------------------------------------------------------------------------
    #if defined(MG32_1ST)
    tmpREG = mDAC->Init.TriggerConverionSrc     | 
             mDAC->Init.TriggerConverionEdge    | 
             mDAC->Init.DataAlign               | 
             mDAC->Init.OutputLevel;
    #elif defined(MG32_3RD)
    tmpREG = mDAC->Init.TriggerConverionSrc     | 
             mDAC->Init.TriggerConverionEdge    | 
             mDAC->Init.DataAlign;              // Less OutputLevel option
    #endif
    
    
    mDAC->Instance->CR0.W = tmpREG;

/*
    // for MG32F02A128/U128/A064/U064 - Enable DAC buffer.
    #if defined(MG32_3RD)
        mDAC->Instance->CR0.W |= DAC_CR0_BUF0_EN_enable_w;
    #endif
*/
   // for MG32F02A128/U128/A064/U064 - disable DAC buffer.
   mDAC->Instance->CR0.MBIT.BUF0_EN = 0;



    /* Initialize the DAC state*/
    mDAC->State = MID_DAC_STATE_READY;

    /* Set DAC error code to none */
    mDAC->ErrorCode = MID_DAC_ERROR_NONE;
    
    /* Return function status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Deinitialize the DAC peripheral registers to their default reset
 *         		values, with deinitialization of the DAC MSP.
 * @param[in]   mDAC : pointer to a DAC_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    DAC_HandleTypeDef mDAC;
 
    MID_DAC_DeInit(&mDAC);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_DAC_DeInit(DAC_HandleTypeDef *mDAC)
{

    /* Process locked */
    __MID_LOCK(mDAC);

    /* Check the DAC handle allocation and lock status */
    if(mDAC == NULL) 
    {
        return MID_FAILURE;
    }
    else
    {
        /* Change DAC state */
        mDAC->State = MID_DAC_STATE_BUSY;
        
        /* DeInit the low level hardware */
        MID_DAC_MspDeInit(mDAC);
        
        /* Set DAC error code to none */
        mDAC->ErrorCode = MID_DAC_ERROR_NONE;
        
        /* Change DAC state */
        mDAC->State = MID_DAC_STATE_RESET;

    }

    /* Process unlocked */
    __MID_UNLOCK(mDAC);

    /* Return function status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Initializes the DAC Base MSP.
 * @param[in]   mDAC : pointer to a DAC_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_DAC_MspInit(DAC_HandleTypeDef* mDAC)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mDAC);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the MID_DAC_MspInit could be implemented in the user file
   */
}

/**
 *******************************************************************************
 * @brief       DeInitializes DAC Base MSP.
 * @param[in]   mDAC : pointer to a DAC_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_DAC_MspDeInit(DAC_HandleTypeDef* mDAC)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mDAC);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the MID_DAC_MspDeInit could be implemented in the user file
   */
}
///@} 


/**
 * @name	DAC_Exported_Functions_Group2 I/O operation functions 
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief       Start the comparator 
 * @param[in]   mDAC : pointer to a DAC_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    MID_DAC_Start(&mDAC);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_DAC_Start(DAC_HandleTypeDef* mDAC)
{
    
    /* Process locked */
    __MID_LOCK(mDAC);
    
    /* Change DAC state */
    mDAC->State = MID_DAC_STATE_BUSY;
    
    /* Enable the DAC & output DAC */
    __DRV_DAC_ENABLE(mDAC);

    /* Change DAC state */
    mDAC->State = MID_DAC_STATE_READY;
    
    /* Process unlocked */
    __MID_UNLOCK(mDAC);
    
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stop the comparator 
 * @param[in]   mDAC : pointer to a DAC_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    MID_DAC_Stop(&mDAC);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_DAC_Stop(DAC_HandleTypeDef* mDAC)
{
    
    /* Process locked */
    __MID_LOCK(mDAC);
    
    /* Change DAC state */
    mDAC->State = MID_DAC_STATE_BUSY;
    
    /* Enable the DAC & output DAC */
    __DRV_DAC_DISABLE(mDAC);

    /* Change DAC state */
    mDAC->State = MID_DAC_STATE_READY;
    
    /* Process unlocked */
    __MID_UNLOCK(mDAC);
    
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Enables the interrupt and starts the comparator
 * @param[in]   mDAC : pointer to a DAC_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @par         Example
 * @code
    MID_DAC_Start_IT(&mDAC);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_DAC_Start_IT(DAC_HandleTypeDef* mDAC)
{
    
    /* Check the DAC handle allocation and lock status */
    if(mDAC == NULL)
    {
        return MID_FAILURE;
    }
    else
    {
        /* Enable DAC interrupt  */
        mDAC->Instance->INT.W |= mDAC->Init.InteruptMode;
        __DRV_DAC_ENABLE_ITEA();
        
        /* Enable the DAC & output DAC */
        __DRV_DAC_ENABLE(mDAC);
    }
    
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Stop DAC conversion of regular group, disable interruption of 
 *         		end-of-conversion, disable DAC peripheral.
 * @param[in]   mDAC : pointer to a DAC_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    DAC_HandleTypeDef mDAC;
 
    MID_DAC_Stop_IT(&mDAC);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_DAC_Stop_IT(DAC_HandleTypeDef* mDAC)
{

    /* Process locked */
    __MID_LOCK(mDAC);

    /* 1. Stop potential conversion on going, on regular group */
    if(mDAC->State == MID_DAC_STATE_READY)
    {
        mDAC->Instance->INT.W &= ~mDAC->Init.InteruptMode;
    }
    else
    {
        return MID_FAILURE;
    }
    

    // disable ITEA
    if((mDAC->Instance->INT.W & (0xFFFFFFFE)) == 0x00000000U)
    {
        __DRV_DAC_DISABLE_ITEA();
        /* Enable the DAC & output DAC */
        __DRV_DAC_DISABLE(mDAC);
    }

    /* Process unlocked */
    __MID_UNLOCK(mDAC);

    /* Return function status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Enables DAC and starts conversion with DMA access.
 * @param[in]   mDAC : pointer to a DAC_HandleTypeDef
 * @param[in]   pData : The destination buffer address.
 * @param[in]   Length : The length of data to be transferred.
 * @return		MID_StatusTypeDef
 * @par         Example
 * @code
    DAC_HandleTypeDef mDAC;
    DMA_HandleTypeDef hDMA;

    // initial DAC
    mDAC.Instance                   = DAC;
    mDAC.Init.TriggerConverionSrc   = DAC_TRIGGERSOURCE_TM10_TRGO;  // DAC update source from TM10 TRGO
    mDAC.Init.TriggerConverionEdge  = DAC_RISING_EDGE_UPDATE;       // DAC accept rising edge of TM10_TRGO to update DAC
    mDAC.Init.DataAlign             = DAC_ALIGN_10B_R;              // DAC data is 10bit /w right justif
    mDAC.Init.OutputLevel           = DAC_OUTPUTCURRENT_MODE0;      // DAC output ~0.5mA 
    mDAC.Init.InteruptMode          = DAC_IT_READY;                 // DAC will trigger INT when READY flag happened.
    mDAC.State                      = MID_DAC_STATE_RESET;          // Reset state    
    
    MID_DAC_Init(&mDAC);
    
    // initial DMA. (M2P)
    hDMA.Instance               = DMA;
	hDMA.DMAChannelIndex        = DMAChannel0;                  // only DMA channel0 can support M2M mode  
	hDMA.Init.SrcPeri	        = MID_DMA_MEMORY_READ;          // Source symbol is memory
	hDMA.Init.DesPeri	        = MID_DMA_DAC_WRITE;            // Destination symbol is DAC
	hDMA.Init.BSize 	        = DMA_BSIZE_2BYTE;              // Burst size is 1 byte
	hDMA.Init.MEMMode	        = MID_DMA_MEMORY_NORMAL;        // Normal memory access mode    
    hDMA.Init.LoopMode	        = DMA_LOOP_DISABLE;             // DISABLE Loop mode
    hDMA.Parent                 = &mDAC;
    
	MID_DMA_Init(&hDMA);

    // initial DAC with DMA 
    mDAC.DMA_Handle = &hDMA;
    MID_DAC_Start_DMA(&mDAC, (uint32_t *) &DAC_DMA_Pattern, 20);
    
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_DAC_Start_DMA(DAC_HandleTypeDef* mDAC, uint32_t* pData, uint32_t Length)
{
    
    /* Perform DAC enable and conversion start if no conversion is on going */

    /* Process locked */
    __MID_LOCK(mDAC);

    /* Set the DMA Period elapsed callback */
    mDAC->DMA_Handle->XferCpltCallback  = DAC_DMAConvCplt;

    /* Set the DMA half transfer complete callback */
    mDAC->DMA_Handle->XferHalfCpltCallback = DAC_DMAHalfConvCplt;

    /* Set the DMA error callback */
    mDAC->DMA_Handle->XferErrorCallback = DAC_DMAError ;

    /* Clear regular group conversion flag and overrun flag */
    /* (To ensure of no unknown state from potential previous DAC           */
    /* operations)                                                          */
    __DRV_DAC_CLEAR_FLAG(mDAC, (DAC_FLAG_READY | DAC_FLAG_UNDERRUN));

    /* Enable DAC overrun interrupt */
    __DRV_DAC_ENABLE_IT(mDAC, DAC_IT_UNDERRUN);

    /* Enable the DAC Capture/Compare 0 DMA request */
    __DRV_DAC_ENABLE_DMA(mDAC);
      
    /* Start the DMA channel */
    MID_DMA_Start_IT(mDAC->DMA_Handle, (uint32_t)pData, 0, Length);  

    /* Set DAC state                                                        */
    /* - Clear state bitfield related to regular group conversion results   */
    /* - Set state bitfield related to regular operation                    */
    mDAC->State = MID_DAC_STATE_READY;

    /* Reset DAC all error code fields */
    mDAC->ErrorCode = MID_DAC_ERROR_NONE;
    
    __DRV_DMA_START_REQUEST(mDAC->DMA_Handle->DMAChannelIndex);
    
    /* Enable the DAC & output DAC */
    __DRV_DAC_ENABLE(mDAC);
    
    /* Process unlocked */
    /* Unlock before starting DAC conversions: in case of potential         */
    /* interruption, to let the process to DAC IRQ Handler.                 */
    __MID_UNLOCK(mDAC);
    
    /* Return function status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Disables DAC and stop conversion.
 * @param[in]   mDAC : pointer to a DAC_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    DAC_HandleTypeDef mDAC;
 
    MID_DAC_Stop_IT(&mDAC);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_DAC_Stop_DMA(DAC_HandleTypeDef* mDAC)
{

    /* Process locked */
    __MID_LOCK(mDAC);
    
    /* Disable the selected DAC & DMA request */
    __DRV_DAC_DISABLE_DMA(mDAC);
    
     /* Disable the Peripheral */
    __DRV_DAC_DISABLE(mDAC);  

    /* Disable the DMA channel */
    MID_DMA_Abort(mDAC->DMA_Handle);
    
    /* Enable DAC overrun interrupt */
    __DRV_DAC_DISABLE_IT(mDAC, DAC_IT_UNDERRUN);

    /* Change DAC state */
    mDAC->State = MID_DAC_STATE_READY;
    
    /* Process unlocked */
    __MID_UNLOCK(mDAC);

    /* Return function status */
    return MID_SUCCESS;
}
///@} 


/**
 * @name	DAC_Exported_Functions_Group Peripheral State functions
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief       Handles DAC interrupt request.  
 * @param[in]   mDAC : pointer to a DAC_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
void MID_DAC_IRQHandler(DAC_HandleTypeDef* mDAC)
{
    if(__DRV_DAC_GET_IT_SOURCE(mDAC, DAC_IT_UNDERRUN))
    { 
        /* Check underrun channel 1 flag */
        if(__DRV_DAC_GET_FLAG(mDAC, DAC_FLAG_UNDERRUN))
        {
        /* Change DAC state to error state */
        mDAC->State = MID_DAC_STATE_ERROR;
        
        /* Set DAC error code with DMA underrun error */
        mDAC->ErrorCode |= MID_DAC_ERROR_DMAUNDERRUN;
        
        /* Clear the underrun flag */
        __DRV_DAC_CLEAR_FLAG(mDAC, DAC_FLAG_UNDERRUN);
        
        /* Disable the selected DAC with DMA request */
        __DRV_DAC_DISABLE_DMA(mDAC);
        
        /* Error callback */ 
        MID_DAC_DMAUnderrunCallback(mDAC);
        }
    }
    if(__DRV_DAC_GET_IT_SOURCE(mDAC, DAC_IT_READY))
    { 
        /* Check underrun channel 1 flag */
        if(__DRV_DAC_GET_FLAG(mDAC, DAC_FLAG_READY))
        {
        /* Change DAC state to error state */
        mDAC->State = MID_DAC_STATE_READY;
        
        /* Set DAC error code with DMA underrun error */
        mDAC->ErrorCode |= MID_DAC_ERROR_DMAUNDERRUN;
        
        /* Clear the ready flag */
        __DRV_DAC_CLEAR_FLAG(mDAC, DAC_FLAG_READY);
        
        /* Disable the selected DAC with DMA request */
        __DRV_DAC_DISABLE_DMA(mDAC);
        
        /* Error callback */ 
        MID_DAC_ReadyCallback(mDAC);
        }
    }
}

/**
 *******************************************************************************
 * @brief       Set the specified data holding register value for DAC.
 * @param[in]   mDAC : Pointer to a DAC_HandleTypeDef
 * @param[in]   Data : Data to be loaded in the DAC_DAT0 register.
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
 
    MID_DAC_SetValue(&mDAC, 512);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_DAC_SetValue(DAC_HandleTypeDef* mDAC, uint32_t Data)
{
    switch(mDAC->Init.DataAlign)
    {    
    #if defined(MG32_3RD)
    case DAC_ALIGN_12B_R:
        mDAC->Instance->DAT0.H[0] = (uint16_t) Data;
        break;
    #endif
    #if defined(MG32_3RD)
    case DAC_ALIGN_12B_L:
        mDAC->Instance->DAT0.H[0] = (uint16_t) (Data << 4);
        break;
    #endif
    case DAC_ALIGN_10B_R:
        mDAC->Instance->DAT0.H[0] = (uint16_t) Data;
        break;
    case DAC_ALIGN_10B_L:
        mDAC->Instance->DAT0.H[0] = (uint16_t) (Data << 6);
        break;
    case DAC_ALIGN_8B_R:
        mDAC->Instance->DAT0.H[0] = (uint16_t) (Data & 0x00FF);
        break;
    case DAC_ALIGN_8B_L:
        mDAC->Instance->DAT0.H[0] = (uint16_t) (Data << 8);
        break;
    default:
        return MID_FAILURE;
        
    }
    
    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Conversion complete callback in non blocking mode. 
 * @param[in]   mDAC : pointer to a DAC_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_DAC_ReadyCallback(DAC_HandleTypeDef* mDAC)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mDAC);
    /* NOTE : This function Should not be modified, when the callback is needed,
                the MID_DAC_TriggerCallback could be implemented in the user file
    */
}


/**
 *******************************************************************************
 * @brief       Conversion complete callback in non blocking mode. 
 * @param[in]   mDAC : pointer to a DAC_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_DAC_ConvCpltCallback(DAC_HandleTypeDef* mDAC)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mDAC);
    /* NOTE : This function Should not be modified, when the callback is needed,
            the MID_DAC_TriggerCallback could be implemented in the user file
    */
}

/**
 *******************************************************************************
 * @brief       Conversion half DMA transfer callback in non-blocking mode. 
 * @param[in]   mDAC : pointer to a DAC_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_DAC_ConvHalfCpltCallback(DAC_HandleTypeDef* mDAC)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mDAC);
    /* NOTE : This function Should not be modified, when the callback is needed,
                the MID_DAC_TriggerCallback could be implemented in the user file
    */
}

/**
 *******************************************************************************
 * @brief       Error DAC callback 
 * @param[in]   mDAC : pointer to a DAC_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_DAC_ErrorCallback(DAC_HandleTypeDef *mDAC)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mDAC);
    
    /* NOTE : This function should not be modified. When the callback is needed,
            function MID_DAC_ConvCpltCallback must be implemented in the user file.
    */
}

/**
 *******************************************************************************
 * @brief       EDMA underrun DAC callback.
 * @param[in]   mDAC : pointer to a DAC_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_DAC_DMAUnderrunCallback(DAC_HandleTypeDef *mDAC)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mDAC);
    
    /* NOTE : This function should not be modified. When the callback is needed,
            function MID_DAC_ConvCpltCallback must be implemented in the user file.
    */
}
///@} 


/**
 * @name	DAC_Exported_Functions_Group1 Peripheral State functions
 *   		
 */ 
///@{ 

/**
 *******************************************************************************
 * @brief       Returns the last data output value of the selected DAC.
 * @param[in]   mDAC : pointer to a DAC_HandleTypeDef
 * @return		DAC state
 *******************************************************************************
 */
uint32_t MID_DAC_GetValue(DAC_HandleTypeDef *mDAC)
{
    /* Check the DAC handle allocation */
    return mDAC->Instance->DOR0.W;
}




/**
 *******************************************************************************
 * @brief       Return the DAC state
 * @param[in]   mDAC : pointer to a DAC_HandleTypeDef
 * @return		DAC state
 *******************************************************************************
 */
MID_DAC_StateTypeDef MID_DAC_GetState(DAC_HandleTypeDef* mDAC)
{
    /* Return DAC handle state */
    return mDAC->State;
}



/**
 *******************************************************************************
 * @brief       Return the DAC error code
 * @param[in]   mDAC : pointer to a DAC_HandleTypeDef
 * @return		DAC Error Code
 *******************************************************************************
 */
uint32_t MID_DAC_GetError(DAC_HandleTypeDef* mDAC)
{
    /* Return DAC handle state */
    return mDAC->ErrorCode;
}



/**
 * @name	DAC_Private_Functions
 *   		
 */ 

/**
 *******************************************************************************
 * @brief       DMA conversion complete callback. 
 * @param[in]   mDMA : pointer to a DMA_HandleTypeDef structure that contains
 *                     the configuration information for the specified DMA module.
 * @return		None
 *******************************************************************************
 */
static void DAC_DMAConvCplt(DMA_HandleTypeDef *mDMA)   
{
    DAC_HandleTypeDef* mDAC = ( DAC_HandleTypeDef* )((DMA_HandleTypeDef* )mDMA)->Parent;
    
    MID_DAC_ConvCpltCallback(mDAC); 
    
    mDAC->State= MID_DAC_STATE_READY;
}

/**
 *******************************************************************************
 * @brief       DMA half transfer complete callback. 
 * @param[in]   mDMA : pointer to a DMA_HandleTypeDef structure that contains
 *                     the configuration information for the specified DMA module.
 * @return		None
 *******************************************************************************
 */
static void DAC_DMAHalfConvCplt(DMA_HandleTypeDef *mDMA)   
{
    DAC_HandleTypeDef* mDAC = ( DAC_HandleTypeDef* )((DMA_HandleTypeDef* )mDMA)->Parent;
    /* Conversion complete callback */
    MID_DAC_ConvHalfCpltCallback(mDAC); 
}

/**
 *******************************************************************************
 * @brief		TM DMA error call back.
 * @param[in]   mDMA : pointer to a DMA_HandleTypeDef structure that contains
 *                     the configuration information for the specified DMA module.
 * @return      None
 *******************************************************************************
 */
static void DAC_DMAError(DMA_HandleTypeDef *mDMA)   
{
    DAC_HandleTypeDef* mDAC = ( DAC_HandleTypeDef* )((DMA_HandleTypeDef* )mDMA)->Parent;
    
    /* Set DAC error code to DMA error */
    mDAC->ErrorCode |= MID_DAC_ERROR_DMA;
    
    MID_DAC_ErrorCallback(mDAC); 
    
    mDAC->State= MID_DAC_STATE_READY;
}

///@}


