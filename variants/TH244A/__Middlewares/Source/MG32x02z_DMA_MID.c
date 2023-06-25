/**
 ******************************************************************************
 *
 * @file        MG32x02z_DMA_MID.c
 *
 * @brief       This file provides firmware functions to manage the following 
 *              functionalities of the DMA peripheral:
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.03
 * @date        2020/07/03
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



#include "MG32x02z_DMA_MID.h"

 
 /**
 * @name	Initial/Deinitial DMA with DMA_HandleTypeDef
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief       Initializes the DMA Unit according to the specified 
 *              parameters in the DMA_HandleTypeDef and create the associated handle.
 * @param[in]   mDMA : pointer to a DMA_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    DMA_HandleTypeDef mDMA;
    
    mDMA.Instance = &DMA;
    mDMA.Init.SrcPeri = MID_DMA_MEMORY_READ;
    mDMA.Init.DesPeri = MID_DMA_DAC_WRITE;
    mDMA.Init.BSize = DMA_BSIZE_2BYTE;
    mDMA.Init.MEMMode = MID_DMA_MEMORY_NORMAL;
    mDMA.Init.Priority = DMA_PRIORITY_HIGH;
    mDMA.Init.LoopMode = DMA_LOOP_DISABLE;
    mDMA.PriorityMode = DMA_LEVEL;
 
    MID_DMA_Init(&mDMA);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_DMA_Init(DMA_HandleTypeDef *mDMA)
{

    /* Check the DMA handle allocation */
    if(NULL == mDMA)
    {
        return MID_FAILURE;
    }

    /* Reset DMA channel */
    mDMA->DMAChannelIndex->A.W &= ~(DMA_CR0_EN_enable_w);

    /* Change DMA peripheral state */
    mDMA->State = MID_DMA_STATE_BUSY;

    /* Config DMA macro priority mode, Extra-GPL channel and Enable DMA*/
#if defined(MG32_1ST) || defined(MG32_3RD)
    mDMA->Instance->CR0.W |= (mDMA->PriorityMode | mDMA->ExtraGPL_Channel | DMA_CR0_EN_enable_w);
#else
    mDMA->Instance->CR0.W |= (mDMA->ExtraGPL_Channel | DMA_CR0_EN_enable_w);
#endif   
    
    /* Prepare the DMA Channel configuration and Enable */
    /* Burst Size, Loop Mode, Memory Address increase mode, Priority */
#if defined(MG32_1ST) || defined(MG32_3RD)
    
    // dummy number for MG32_1ST
    #if defined(MG32_1ST)
        mDMA->DMAChannelIndex->NUM.H[0] = 0x0002;
    #endif
    
    mDMA->DMAChannelIndex->A.W = mDMA->Init.BSize | mDMA->Init.LoopMode | mDMA->Init.MEMMode | mDMA->Init.Priority |  \
                           DMA_CR0_EN_enable_w;
#else
    mDMA->DMAChannelIndex->A.W = mDMA->Init.BSize | mDMA->Init.LoopMode | mDMA->Init.MEMMode | DMA_CR0_EN_enable_w;
#endif   

#if defined(MG32_1ST)
    if (mDMA->DMAChannelIndex == DMAChannel0)           // Disable DMAChannel0 Loop mode
        SYS->CR0.W &= ~(SYS_CR0_CH0_LAST_yes_w);
    else if (mDMA->DMAChannelIndex == DMAChannel1)      // Disable DMAChannel1 Loop mode
        SYS->CR0.W &= ~(SYS_CR0_CH1_LAST_yes_w);
    else                                                // Disable DMAChannel2 Loop mode
        SYS->CR0.W &= ~(SYS_CR0_CH2_LAST_yes_w);
#endif
    
    /* Prepare the DMA Channel configuration */
    /* Source, Destination, Source memory increase, Destination memory increase */
    mDMA->DMAChannelIndex->B.W = mDMA->Init.SrcPeri | mDMA->Init.DesPeri | DMA_SINC_ENABLE | DMA_DINC_ENABLE;
      
    /* Clean callbacks */
    mDMA->XferCpltCallback = NULL;
    mDMA->XferHalfCpltCallback = NULL;
    mDMA->XferErrorCallback = NULL;
    mDMA->XferAbortCallback = NULL;

    /* Initialise the error code */
    mDMA->ErrorCode = MID_DMA_ERROR_NONE;

    /* Initialize the DMA state*/
    mDMA->State = MID_DMA_STATE_READY;

    /* Allocate lock resource and initialize it */
    mDMA->Lock = MID_UnLocked;

    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       DeInitializes the DMA peripheral 
 * @param[in]   mDMA : pointer to a DMA_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    DMA_HandleTypeDef mDMA;
 
    MID_DMA_DeInit(&mDMA);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_DMA_DeInit(DMA_HandleTypeDef *mDMA)
{
    /* Check the DMA handle allocation */
    if(NULL == mDMA)
    {
        return MID_FAILURE;
    }

    /* Disable the selected DMA Channelx */
    mDMA->DMAChannelIndex->A.W &= ~(DMA_CR0_EN_enable_w);

    /* Clear all flags */
    mDMA->DMAChannelIndex->A.W |= DMA_CH_ALL_FLAG;

    /* Initialize the error code */
    mDMA->ErrorCode = MID_DMA_ERROR_NONE;

    /* Initialize the DMA state */
    mDMA->State = MID_DMA_STATE_RESET;

    /* Release Lock */
    __MID_UNLOCK(mDMA);

    return MID_SUCCESS;
}
///@}



 /**
 * @name	DMA_Exported_Functions_Group2 Input and Output operation functions
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief       Start the DMA Transfer.
 * @param[in]   mDMA : pointer to a DMA_HandleTypeDef
 * @param[in]   SrcAddress : source address
 * @param[in]   DstAddress : destination address
 * @param[in]   DataLength : the length of DMA access size
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    DMA_HandleTypeDef mDMA;
 
    MID_DMA_Start(&mDMA, (uint32_t *) SrcAddress, (uint32_t *) DestinationAddress, 20);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_DMA_Start(DMA_HandleTypeDef *mDMA, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)
{
	MID_StatusTypeDef status = MID_SUCCESS;
  
    /* Process locked */
    __MID_LOCK(mDMA);

    if(MID_DMA_STATE_READY == mDMA->State)
    {
        /* Change DMA peripheral state */  
        mDMA->State = MID_DMA_STATE_BUSY;

        mDMA->ErrorCode = MID_DMA_ERROR_NONE;

        //  	/* Disable the peripheral */
        //    mDMA->DMAChannelIndex->A.W &= ~(DMA_CR0_EN_enable_w);

        /* Configure the source, destination address and the data length */
        DMA_SetConfig(mDMA, SrcAddress, DstAddress, DataLength);

        /* Send DMA request */
        mDMA->DMAChannelIndex->A.W |= (DMA_CH0A_CH0_REQ_enable_w);
    }
    else
    {
        /* Process Unlocked */
        __MID_UNLOCK(mDMA);

        /* Remain BUSY */
        status = MID_BUSY;
    }  

    return status; 
}


/**
 *******************************************************************************
 * @brief       Start the DMA Transfer with interrupt enabled.
 * @param[in]   mDMA : pointer to a DMA_HandleTypeDef
 * @param[in]   SrcAddress : source address
 * @param[in]   DstAddress : destination address
 * @param[in]   DataLength : the length of DMA access size
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    DMA_HandleTypeDef mDMA;
 
    MID_DMA_Start_IT(&mDMA, (uint32_t *) SrcAddress, (uint32_t *) DestinationAddress, 20);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_DMA_Start_IT(DMA_HandleTypeDef *mDMA, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)
{
    uint32_t tmp;
    
	MID_StatusTypeDef status = MID_SUCCESS;
  
    /* Process locked */
    __MID_LOCK(mDMA);

    if(MID_SUCCESS == status)
    {
        /* Change DMA peripheral state */  
        mDMA->State = MID_DMA_STATE_BUSY;

        mDMA->ErrorCode = MID_DMA_ERROR_NONE;

        /* Enable the DMA IEA interrupt bit */
        __DRV_DMA_ENABLE_ITEA(mDMA);

        /* Enable the transfer complete, & transfer error interrupts */
        /* Half transfer interrupt is optional: enable it only if associated callback is available */
        if(NULL != mDMA->XferHalfCpltCallback )
        {
            tmp = mDMA->DMAChannelIndex->A.W;
            tmp |= (DMA_IT_TC | DMA_IT_HT | DMA_IT_TE);
            mDMA->DMAChannelIndex->A.W = tmp;
        }
        else
        {        
            tmp = mDMA->DMAChannelIndex->A.W;
            tmp |= (DMA_IT_TC | DMA_IT_TE);
            tmp &= ~(DMA_IT_HT);
            mDMA->DMAChannelIndex->A.W = tmp;
        }

        /* Configure the source, destination address and the data length */
        DMA_SetConfig(mDMA, SrcAddress, DstAddress, DataLength);

        /* Send DMA request */
        mDMA->DMAChannelIndex->A.W |= (DMA_CH0A_CH0_REQ_enable_w);

        /* Change DMA peripheral state */  
        mDMA->State = MID_DMA_STATE_READY;

    }
    else
    {
        /* Process Unlocked */
        __MID_UNLOCK(mDMA);

        /* Remain BUSY */
        status = MID_BUSY;
    }  

    return status; 
}

/**
 *******************************************************************************
 * @brief       Abort the DMA Transfer.
 * @param[in]   mDMA : pointer to a DMA_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    DMA_HandleTypeDef mDMA;
 
    MID_DMA_Abort(&mDMA);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_DMA_Abort(DMA_HandleTypeDef *mDMA)
{
    
	/* Disable DMA IT */
	mDMA->DMAChannelIndex->A.W &= ~(DMA_IT_TC | DMA_IT_HT | DMA_IT_TE);
	
	/* Disable the channel */
    mDMA->DMAChannelIndex->A.W &= ~(DMA_CR0_EN_enable_w);
	
	/* Clear all flags */
    mDMA->DMAChannelIndex->A.W |= DMA_CH_ALL_FLAG;
	
	/* Change the DMA state*/
	mDMA->State = MID_DMA_STATE_READY; 
	
	/* Process Unlocked */
	__MID_UNLOCK(mDMA);
	
	return MID_SUCCESS; 
}


/**
 *******************************************************************************
 * @brief       Abort the DMA Transfer in Interrupt mode.
 * @param[in]   mDMA : pointer to a DMA_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    DMA_HandleTypeDef mDMA;
 
    MID_DMA_Abort_IT(&mDMA);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_DMA_Abort_IT(DMA_HandleTypeDef *mDMA)
{
    MID_StatusTypeDef status = MID_SUCCESS;

    if(MID_DMA_STATE_BUSY != mDMA->State)
    {
        /* no transfer ongoing */
        mDMA->ErrorCode = MID_DMA_ERROR_NO_XFER;

        status = MID_FAILURE;
    }
    else
    { 
        /* Disable DMA IT */
        mDMA->DMAChannelIndex->A.W &= ~(DMA_IT_TC | DMA_IT_HT | DMA_IT_TE);

        /* Disable the channel */
        mDMA->DMAChannelIndex->A.W &= ~(DMA_CR0_EN_enable_w);

        /* Clear all flags */
        mDMA->DMAChannelIndex->A.W |= DMA_CH_ALL_FLAG;

        /* Change the DMA state */
        mDMA->State = MID_DMA_STATE_READY;

        /* Process Unlocked */
        __MID_UNLOCK(mDMA);

        /* Call User Abort callback */ 
        if(mDMA->XferAbortCallback != NULL)
        {
            mDMA->XferAbortCallback(mDMA);
        } 
    }
    return status;
}

/**
 *******************************************************************************
 * @brief       Polling for transfer complete.
 * @param[in]   mDMA : pointer to a DMA_HandleTypeDef
 * @param[in]   CompleteLevel : Specifies the DMA level complete.
 * @param[in]   Timeout : Timeout duration.
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    DMA_HandleTypeDef mDMA;
  
    MID_DMA_PollForTransfer(&mDMA, MID_DMA_FULL_TRANSFER, 10);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_DMA_PollForTransfer(DMA_HandleTypeDef *mDMA, uint32_t CompleteLevel, uint32_t Timeout)
{
    uint32_t temp;
    uint32_t tickstart = 0U;

    if(MID_DMA_STATE_BUSY != mDMA->State)
    {
        /* no transfer ongoing */
        mDMA->ErrorCode = MID_DMA_ERROR_NO_XFER;
        __MID_UNLOCK(mDMA);
        return MID_FAILURE;
    }

    /* Polling mode not supported in loop mode */
    if ((0x0000) != (mDMA->DMAChannelIndex->A.MBIT.LOOP))
    {
        mDMA->ErrorCode = MID_DMA_ERROR_NOT_SUPPORTED;
        return MID_FAILURE;
    }

    /* Get the level transfer complete flag */
    if(MID_DMA_FULL_TRANSFER == CompleteLevel)
    {
        /* Transfer Complete flag */
        temp = DMA_CH0A_CH0_TC2F_happened_w;
    }
    else
    {
        /* Half Transfer Complete flag */
        temp = DMA_CH0A_CH0_TH2F_happened_w;
    }

    /* Get tick */
    tickstart = MID_GetTick();

    while(0x00000000 == (mDMA->DMAChannelIndex->A.W & temp))
    {
        if(0x00000000 != (mDMA->DMAChannelIndex->A.W & DMA_CH0A_CH0_ERR2F_happened_w))
        {      
            /* When a DMA transfer error occurs */
            /* Clear all flags */
            mDMA->DMAChannelIndex->A.W |= DMA_CH_ALL_FLAG;

            /* clear of its EN bits */
            mDMA->DMAChannelIndex->A.W &= ~(DMA_CR0_EN_enable_w);

            /* Update error code */
            mDMA->ErrorCode = MID_DMA_ERROR_TE;

            /* Change the DMA state */
            mDMA->State= MID_DMA_STATE_READY;       

            /* Process Unlocked */
            __MID_UNLOCK(mDMA);

            return MID_FAILURE;      
        }  
      
        /* Check for the Timeout */
        if(Timeout != MID_MAX_DELAY)
        {
            if((Timeout == 0U) || ((MID_GetTick() - tickstart) > Timeout))
            {
                /* Update error code */
                mDMA->ErrorCode = MID_DMA_ERROR_TIMEOUT;

                /* Change the DMA state */
                mDMA->State = MID_DMA_STATE_READY;

                /* Process Unlocked */
                __MID_UNLOCK(mDMA);

                return MID_FAILURE;
            }
        }
      
    }

    if(MID_DMA_FULL_TRANSFER == CompleteLevel)
    {
        /* Clear the transfer complete flag */
        mDMA->DMAChannelIndex->A.W |= DMA_CH_FLAG_COMPLETE | DMA_CH_FLAG_HALF;

        /* The selected Channelx EN bit is cleared (DMA is disabled and 
        all transfers are complete) */
        mDMA->State = MID_DMA_STATE_READY;
    }
    else
    { 
        /* Clear the half transfer complete flag */
        mDMA->DMAChannelIndex->A.W |= DMA_CH_FLAG_COMPLETE;
    }

    /* Process unlocked */
    __MID_UNLOCK(mDMA);  

    return MID_FAILURE;
}


/**
 *******************************************************************************
 * @brief       Handle DMA interrupt request.
 * @param[in]   mDMA : pointer to a DMA_HandleTypeDef
 * @return		MID_StatusTypeDef
 *******************************************************************************
 */
void MID_DMA_IRQHandler(DMA_HandleTypeDef *mDMA)
{
    uint32_t tmp;

    /* Half Transfer Complete Interrupt management ******************************/
    if ((mDMA->DMAChannelIndex->A.W & (DMA_IT_HT | DMA_CH_FLAG_HALF)) == (DMA_IT_HT | DMA_CH_FLAG_HALF))
    {
    /* Disable the half transfer interrupt if the DMA mode is not CIRCULAR */
        if(mDMA->DMAChannelIndex->A.MBIT.LOOP == 0)
        {
            /* Disable the half transfer interrupt */
            tmp = mDMA->DMAChannelIndex->A.W;
            tmp &= ~(DMA_IT_HT | DMA_CH_ALL_FLAG);
            mDMA->DMAChannelIndex->A.W = tmp;
        }

        /* Clear the half transfer complete flag */
        tmp = mDMA->DMAChannelIndex->A.W & ~(DMA_CH_ALL_FLAG);
        tmp |= DMA_CH_FLAG_HALF;
        mDMA->DMAChannelIndex->A.W = tmp;

        /* DMA peripheral state is not updated in Half Transfer */
        /* State is updated only in Transfer Complete case */

        if(mDMA->XferHalfCpltCallback != NULL)
        {
            /* Half transfer callback */
            mDMA->XferHalfCpltCallback(mDMA);
        }
    }

    /* Transfer Complete Interrupt management ***********************************/
    if ((mDMA->DMAChannelIndex->A.W & (DMA_IT_TC | DMA_CH_FLAG_COMPLETE)) == (DMA_IT_TC | DMA_CH_FLAG_COMPLETE))
    {
        if(mDMA->DMAChannelIndex->A.MBIT.LOOP == 0)
        {
            /* Disable the transfer complete  & transfer error interrupts */
            /* if the DMA mode is not CIRCULAR */
            tmp = mDMA->DMAChannelIndex->A.W;
            tmp &= ~(DMA_IT_TE | DMA_IT_HT | DMA_IT_TC | DMA_CH_ALL_FLAG);
            mDMA->DMAChannelIndex->A.W = tmp;

            /* Change the DMA state */
            mDMA->State = MID_DMA_STATE_READY;
        }

        /* Clear the transfer complete flag */
        mDMA->DMAChannelIndex->A.W |= DMA_CH_ALL_FLAG;

        /* Process Unlocked */
        __MID_UNLOCK(mDMA);

        if(mDMA->XferCpltCallback != NULL)
        {
            /* Transfer complete callback */
            mDMA->XferCpltCallback(mDMA);
        }
    }

    /* Transfer Error Interrupt management ***************************************/
    else if ((mDMA->DMAChannelIndex->A.W & (DMA_IT_TE | DMA_CH_FLAG_ERRF)) == (DMA_IT_TE | DMA_CH_FLAG_ERRF))
    {
        /* When a DMA transfer error occurs */
        /* A hardware clear of its EN bits is performed */
        /* Then, disable all DMA interrupts */
        mDMA->DMAChannelIndex->A.W &= ~(DMA_IT_HT | DMA_IT_HT | DMA_IT_TE | DMA_CH_ALL_FLAG);

        /* Clear all flags */
        mDMA->DMAChannelIndex->A.W |= DMA_CH_ALL_FLAG;

        /* Update error code */
        mDMA->ErrorCode = MID_DMA_ERROR_TE;

        /* Change the DMA state */
        mDMA->State = MID_DMA_STATE_READY;    

        /* Process Unlocked */
        __MID_UNLOCK(mDMA); 

        if(mDMA->XferErrorCallback != NULL)
        {
            /* Transfer error callback */
            mDMA->XferErrorCallback(mDMA);
        }
    }
}
///@}


/**
 * @name	Output Compare
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief       Register callbacks.
 * @param[in]   mDMA : pointer to a DMA_HandleTypeDef structure that contains
 *                     the configuration information for the specified DMA Stream.
 * @param[in]   CallbackID : User Callback identifer
 *                           a MID_DMA_CallbackIDTypeDef ENUM as parameter.
 * @param[in]   pCallback : pointer to private callback function which has pointer to 
 *                         a DMA_HandleTypeDef structure as parameter.
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    MID_DMA_RegisterCallback(&mDMA, MID_DMA_XFER_CPLT_CB_ID, &DMACallBack);
 * @endcode
 *******************************************************************************
 */
__weak MID_StatusTypeDef MID_DMA_RegisterCallback(DMA_HandleTypeDef *mDMA, MID_DMA_CallbackIDTypeDef CallbackID, void (* pCallback)(DMA_HandleTypeDef * _mDMA))
{
    MID_StatusTypeDef status = MID_SUCCESS;

    /* Process locked */
    __MID_LOCK(mDMA);

    if(MID_DMA_STATE_READY == mDMA->State)
    {
        switch (CallbackID)
        {
        case  MID_DMA_XFER_CPLT_CB_ID:
            mDMA->XferCpltCallback = pCallback;
            break;

        case  MID_DMA_XFER_HALFCPLT_CB_ID:
            mDMA->XferHalfCpltCallback = pCallback;
            break;         

        case  MID_DMA_XFER_ERROR_CB_ID:
            mDMA->XferErrorCallback = pCallback;
            break;         
           
        case  MID_DMA_XFER_ABORT_CB_ID:
            mDMA->XferAbortCallback = pCallback;
            break; 
        
        case  MID_DMA_XFER_ALL_CB_ID:
            status = MID_FAILURE;
            break;  
        
//        __attribute__((fallthrough));
//        default:
//            status = MID_FAILURE;
//            break;                                                            
        }
    }
    else
    {
        status = MID_FAILURE;
    } 

    /* Release Lock */
    __MID_UNLOCK(mDMA);

    return status;
}


/**
 *******************************************************************************
 * @brief       UnRegister callbacks.
 * @param[in]   mDMA : pointer to a DMA_HandleTypeDef
 * @param[in]   CallbackID : ID
 * @return		MID_StatusTypeDef
 *******************************************************************************
 */
__weak MID_StatusTypeDef MID_DMA_UnRegisterCallback(DMA_HandleTypeDef *mDMA, MID_DMA_CallbackIDTypeDef CallbackID)
{
    MID_StatusTypeDef status = MID_SUCCESS;

    /* Process locked */
    __MID_LOCK(mDMA);

    if(MID_DMA_STATE_READY == mDMA->State)
    {
        switch (CallbackID)
        {
        case  MID_DMA_XFER_CPLT_CB_ID:
            mDMA->XferCpltCallback = NULL;
            break;

        case  MID_DMA_XFER_HALFCPLT_CB_ID:
            mDMA->XferHalfCpltCallback = NULL;
            break;         

        case  MID_DMA_XFER_ERROR_CB_ID:
            mDMA->XferErrorCallback = NULL;
            break;         

        case  MID_DMA_XFER_ABORT_CB_ID:
            mDMA->XferAbortCallback = NULL;
            break; 

        case   MID_DMA_XFER_ALL_CB_ID:
            mDMA->XferCpltCallback = NULL;
            mDMA->XferHalfCpltCallback = NULL;
            mDMA->XferErrorCallback = NULL;
            mDMA->XferAbortCallback = NULL;
            break; 

//        __attribute__((fallthrough));
//        default:
//            status = MID_FAILURE;
//            break;                                                            
        }
    }
    else
    {
        status = MID_FAILURE;
    } 

    /* Release Lock */
    __MID_UNLOCK(mDMA);

    return status;
}

/**
 *******************************************************************************
 * @brief       Returns the DMA state.
 * @param[in]   mDMA : pointer to a DMA_HandleTypeDef
 * @return		MID_DMA_StateTypeDef
 * @note 
 * @par         Example
 * @code
    MID_DMA_GetState(&mDMA);
 * @endcode
 *******************************************************************************
 */
MID_DMA_StateTypeDef MID_DMA_GetState(DMA_HandleTypeDef *mDMA)
{
    return mDMA->State;
}

/**
 *******************************************************************************
 * @brief       Return the DMA error code.
 * @param[in]   mDMA : pointer to a DMA_HandleTypeDef
 * @return		DMA Error Code
 *******************************************************************************
 */
uint32_t MID_DMA_GetError(DMA_HandleTypeDef *mDMA)
{
    return mDMA->ErrorCode;
}

/**
 *******************************************************************************
 * @brief       Starts the TIM Output Compare signal generation.
 * @param[in]   mDMA : pointer to a DMA_HandleTypeDef
 * @param[in]   SrcAddress : The source memory Buffer address
 * @param[in]   DstAddress : The destination memory Buffer address
 * @param[in]   DataLength : The length of data to be transferred from source 
 *                           to destination
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    DMA_SetConfig(&mDMA, &SrcAddr, &DestAddr, Length);
 * @endcode
 *******************************************************************************
 */
void DMA_SetConfig(DMA_HandleTypeDef *mDMA, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)
{
	/* Clear all flags */
    mDMA->DMAChannelIndex->A.W |= DMA_CH_ALL_FLAG;
    
    /* Config DMA channel parameters */
    mDMA->DMAChannelIndex->A.W |= mDMA->Init.MEMMode | mDMA->Init.BSize | mDMA->Init.LoopMode;
    mDMA->DMAChannelIndex->B.W = mDMA->Init.DesPeri | DMA_DINC_ENABLE | \
                                 mDMA->Init.SrcPeri | DMA_SINC_ENABLE;

    /* Source from memory */
    if(mDMA->Init.SrcPeri == MID_DMA_MEMORY_READ)
    {
        /* Configure DMA Channel source address */
        mDMA->DMAChannelIndex->SSA.W = SrcAddress;
    }
    
    /* Destination to memory */
    if(mDMA->Init.DesPeri == MID_DMA_MEMORY_WRITE)
    {
        /* Configure DMA Channel source address */
        mDMA->DMAChannelIndex->DSA.W = DstAddress;
    }

    /* Configure DMA Channel data length */
    mDMA->DMAChannelIndex->NUM.W = DataLength;
    
}
///@}


