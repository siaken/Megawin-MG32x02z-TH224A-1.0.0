 /**
 ******************************************************************************
 *
 * @file        MG32x02z_APB_MID.c
 *
 * @brief       This file provides firmware functions to manage the following 
 *              functionalities of the APB peripheral:
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.05
 * @date        2022/01/21
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



#include "MG32x02z_APB_MID.h"


/**
 * @name    Initial/Deinitial OBMx with MID_OBMx_HandleTypeDef
 *          
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief       Initializes the APB's (OBMx) peripheral and regular group according to
 *              parameters specified in structure "MID_OBMx_HandleTypeDef".
 * @param[in]   mOBMx : pointer to a MID_OBMx_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    MID_OBMx_HandleTypeDef mOBMx;
    
    mOBMx.Instance                  = OBM1;
    mOBMx.Init.OBMxMode             = APB_OBM_CLR;                  // STA bit is cleared by falling edge of OR signal
    mOBMx.Init.BKS0Src              = APB_BKS0_CMP0_OUT;            // sigle-end type
    mOBMx.Init.BKS0Polarity         = APB_OBM_BKS0_LOW;             // BKS0 : Non-Invert
    mOBMx.Init.BKS1Src              = APB_BKS1_TM01_TRGO;           // sigle-end type
    mOBMx.Init.BKS1Polarity         = APB_OBM_BKS1_LOW;             // BKS1 : Non-Invert
    mOBMx.Init.BKS2Src              = APB_BKS2_LOGIC_1;             // BKS2 always keep '1'
    mOBMx.Init.BKS2Polarity         = APB_OBM_BKS2_LOW;             // BKS2 : Non-Invert
    mOBMx.Init.OutChannel0Src       = APB_CH0_TM00_CKO;             // Channel0 output signal is TM00_CKO 
    mOBMx.Init.OutChannel0Polarity  = APB_OBM_CH0_LOW;              // Non-invert channel0 output
    mOBMx.Init.OutChannel1Src       = APB_CH1_LOGIC_0;              // Channel1 output '0' /w invert
    mOBMx.Init.OutChannel1Polarity  = APB_OBM_CH1_HIGH;             // Invert channel1 output
    mOBMx.Init.OBMxOutPolarity      = APB_OBM_PIN_LOW;              // Non-invert
    mOBMx.Init.SyncFilter           = OBM_SYNCHRONIZE_BYPASS;       // disable OBMx output filter
    mOBMx.Init.InitSTAState         = APB_OBM_INITSTA_HIGH;         // Set initial STA to '1'
    
    MID_OBMx_Init(&mOBMx);
 
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_OBMx_Init(MID_OBMx_HandleTypeDef* mOBMx)
{
    uint32_t tmpREG;
    
    /* Check APB handle */
    if(mOBMx == NULL) 
    {
        return MID_FAILURE;
    }
    else
    {
        /* Init the another GPIO module or SYCLK  ... */
        MID_OBMx_MspInit(mOBMx);
        
        /* Change APB peripheral state */
        mOBMx->State = MID_APB_STATE_BUSY;
    
        // ------------------------------------------------------------------------
        /* Config of OBMX parameters:                                             */
        // ------------------------------------------------------------------------
        tmpREG = mOBMx->Init.OutChannel0Polarity    | 
                 mOBMx->Init.OutChannel0Src         | 
                 mOBMx->Init.OutChannel1Polarity    | 
                 mOBMx->Init.OutChannel1Src         | 
                 mOBMx->Init.OBMxOutPolarity        | 
                 mOBMx->Init.SyncFilter;
        
        mOBMx->Instance->OBMx1.W = tmpREG;

        //
        tmpREG = mOBMx->Init.BKS0Polarity           | 
                 mOBMx->Init.BKS0Src                | 
                 mOBMx->Init.BKS1Polarity           | 
                 mOBMx->Init.BKS1Src                | 
                 mOBMx->Init.BKS2Polarity           | 
                 mOBMx->Init.BKS2Src                | 
                 mOBMx->Init.InitSTAState           | 
                 mOBMx->Init.OBMxMode;
        
        mOBMx->Instance->OBMx0.W = tmpREG;
        
        /* Initialize the APB state*/
        mOBMx->State = MID_APB_STATE_READY;
    }
    
    /* Return function status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Deinitialize the APB (OBMx) peripheral registers to their default
                reset values, with deinitialization of the MID_OBMx_MspDeInit.
 * @param[in]   mOBMx : pointer to a MID_OBMx_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    MID_OBMx_HandleTypeDef mOBMx;
 
    MID_OBMx_DeInit(&mOBMx);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_OBMx_DeInit(MID_OBMx_HandleTypeDef *mOBMx)
{

    /* Process locked */
    __MID_LOCK(mOBMx);

    /* Check the APB handle allocation and lock status */
    if(mOBMx == NULL) 
    {
        return MID_FAILURE;
    }
    else
    {
        /* Reset OBMx register */
        mOBMx->Instance->OBMx0.W = 0x0U;
        mOBMx->Instance->OBMx1.W = 0x0U;

        /* DeInit the low level hardware: GPIO, CLOCK and NVIC */
        MID_OBMx_MspDeInit(mOBMx);

        /* Set OBMx state */
        mOBMx->State = MID_APB_STATE_RESET;
    }

    /* Process unlocked */
    __MID_UNLOCK(mOBMx);

    /* Return function status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Initializes the APB Base MSP.
 * @param[in]   mOBMx : pointer to a MID_OBMx_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_OBMx_MspInit(MID_OBMx_HandleTypeDef* mOBMx)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mOBMx);
    /* NOTE : This function Should not be modified, when the callback is needed,
                the MID_OBMx_MspInit could be implemented in the user file
    */
}

/**
 *******************************************************************************
 * @brief       DeInitializes APB Base MSP.
 * @param[in]   mOBMx : pointer to a MID_OBMx_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_OBMx_MspDeInit(MID_OBMx_HandleTypeDef* mOBMx)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mOBMx);
    /* NOTE : This function Should not be modified, when the callback is needed,
                the MID_OBMx_MspDeInit could be implemented in the user file
    */
}
///@} 


/**
 * @name    APB_Exported_Functions_Group2 I/O operation functions 
 *          
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief       Start the APB (OBMx) 
 * @param[in]   mOBMx : pointer to a MID_OBMx_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    MID_OBMx_Start(&mOBMx);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_OBMx_Start(MID_OBMx_HandleTypeDef* mOBMx)
{
    MID_StatusTypeDef status;
    
    status = MID_OBMx_Init(mOBMx);    
    return status;
}


/**
 *******************************************************************************
 * @brief       Stop the APB (OBMx)  
 * @param[in]   mOBMx : pointer to a MID_OBMx_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    MID_OBMx_Stop(&mOBMx);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_OBMx_Stop(MID_OBMx_HandleTypeDef* mOBMx)
{
    MID_OBMx_DeInit(mOBMx);
    
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Enables the interrupt and starts the APB (OBMx) 
 * @param[in]   mOBMx : pointer to a MID_OBMx_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @par         Example
 * @code
    MID_OBMx_Start_IT(&mOBMx);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_OBMx_Start_IT(MID_OBMx_HandleTypeDef* mOBMx)
{
    
    /* Check the APB handle allocation and lock status */
    if(mOBMx == NULL)
    {
        return MID_FAILURE;
    }
    else
    {
        MID_OBMx_Init(mOBMx);
        
        if(mOBMx->State == MID_APB_STATE_READY)
        {
            #if !defined(MG32_1ST)
            if(mOBMx->Instance == OBM0)
                __DRV_APB_ENABLE_IT(APB_IT_OBM0);
            #endif
            if(mOBMx->Instance == OBM1)
                __DRV_APB_ENABLE_IT(APB_IT_OBM1);
            
            __DRV_APB_ENABLE_ITEA();
            SYS->INT.MBIT.IEA = 1;
            
        }
        else
        {
            return MID_FAILURE;
        }
    }
    
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Disable interruption of OBMx
 * @param[in]   mOBMx : pointer to a MID_OBMx_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    MID_OBMx_HandleTypeDef mOBMx;
 
    MID_OBMx_Stop_IT(&mOBMx);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_OBMx_Stop_IT(MID_OBMx_HandleTypeDef* mOBMx)
{

    /* Process locked */
    __MID_LOCK(mOBMx);

    /* 1. Stop potential conversion on going, on regular group */
    if(mOBMx->State == MID_APB_STATE_READY)
    {
        #if !defined(MG32_1ST)
        if(mOBMx->Instance == OBM0)
            __DRV_APB_DISABLE_IT(APB_IT_OBM0);
        #endif
        if(mOBMx->Instance == OBM1)
            __DRV_APB_DISABLE_IT(APB_IT_OBM1);
            
    }
    else
    {
        return MID_FAILURE;
    }
    

    // disable ITEA
    if((APB->INT.W & (0xFFFFFFFE)) == 0x00000000U)
        __DRV_APB_DISABLE_ITEA();
    
    /* Process unlocked */
    __MID_UNLOCK(mOBMx);

    /* Return function status */
    return MID_SUCCESS;
}
///@} 


/**
 * @name	APB_Exported_Functions_Group Peripheral State functions
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief       Handles APB OBMx interrupt request.  
 * @param[in]   mOBMx : pointer to a MID_OBMx_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
void MID_OBMx_IRQHandler(MID_OBMx_HandleTypeDef* mOBMx)
{
    /* ========== Check APB flag ========== */
    #if !defined(MG32_1ST)
    if(__DRV_APB_GET_FLAG(APB_FLAG_OBM0))
    {
        /* Clear APB Exti pending bit */
        __DRV_APB_CLEAR_FLAG(APB_FLAG_OBM0);
        
        /* APB trigger user callback */
        MID_OBMx_TriggerCallbackOBM0(mOBMx);    
    }
    #endif
    if(__DRV_APB_GET_FLAG(APB_FLAG_OBM1))
    {
        /* Clear APB Exti pending bit */
        __DRV_APB_CLEAR_FLAG(APB_FLAG_OBM1);
        
        /* APB trigger user callback */
        MID_OBMx_TriggerCallbackOBM1(mOBMx);    
    }

}

/**
 *******************************************************************************
 * @brief       Return the output level (high or low) of APB OBMx
 * @param[in]   mOBMx : pointer to a MID_OBMx_HandleTypeDef
 * @return		Returns the selected OBM output level: OBM_OUTPUTLEVEL_LOW or OBM_OUTPUTLEVEL_HIGH.
 * @note 
 * @par         Example
 * @code
    uint32_t OutputLevel;

    OutputLevel = MID_OBMx_GetOutputLevel(&mOBMx);
 * @endcode
 *******************************************************************************
 */
uint32_t MID_OBMx_GetOutputLevel(MID_OBMx_HandleTypeDef* mOBMx)
{
    uint32_t STABITDef=0x00000000U;
    
    #if !defined(MG32_1ST)
    if(mOBMx->Instance == OBM0)
        STABITDef = APB->STA.W & APB_STA_OBM0_OUT_mask_w;
    #endif
    if(mOBMx->Instance == OBM1)
        STABITDef = APB->STA.W & APB_STA_OBM1_OUT_mask_w;
    
    if(STABITDef != 0U)
    {
        return(OBM_OUTPUTLEVEL_HIGH);
    }
    return(OBM_OUTPUTLEVEL_LOW);
}


/**
 *******************************************************************************
 * @brief       APB OBM1 callback.
 * @param[in]   mOBMx : pointer to a MID_OBMx_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_OBMx_TriggerCallbackOBM0(MID_OBMx_HandleTypeDef* mOBMx)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mOBMx);
    /* NOTE : This function Should not be modified, when the callback is needed,
                the MID_OBMx_TriggerCallbackOBM0 could be implemented in the user file
    */
}

/**
 *******************************************************************************
 * @brief       APB OBM1 callback.
 * @param[in]   mOBMx : pointer to a MID_OBMx_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_OBMx_TriggerCallbackOBM1(MID_OBMx_HandleTypeDef* mOBMx)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mOBMx);
    /* NOTE : This function Should not be modified, when the callback is needed,
                the MID_OBMx_TriggerCallbackOBM1 could be implemented in the user file
    */
}

/**
 *******************************************************************************
 * @brief       Return the APB OBMx Switch Signal Status
 * @param[in]   mOBMx : pointer to a MID_OBMx_HandleTypeDef
 * @return		Returns the selected OBMx output level: OBM_SWITCHSTATUS_LOW or OBM_SWITCHSTATUS_HIGH.
 *******************************************************************************
 */
uint32_t MID_OBMx_GetSwitchState(MID_OBMx_HandleTypeDef *mOBMx)
{
    uint32_t SwitchStatus = 0;
    
    /* Check the APB handle allocation */
    #if defined(MG32_2ND)
    if(mOBMx->Instance == OBM0)
    {
        SwitchStatus = APB->STA.W & APB_STA_OBM0_SW_mask_w;
    }
    #endif
    if(mOBMx->Instance == OBM1)
    {
        SwitchStatus = APB->STA.W & APB_STA_OBM1_SW_mask_w;
    }

    if(SwitchStatus != 0U)
    {
        return(OBM_SWITCHSTATUS_HIGH);
    }
    return(OBM_SWITCHSTATUS_LOW);
}
/**
 *******************************************************************************
 * @brief       Update OBM switch signal state.
 * @param[in]   mOBMx : pointer to a MID_OBMx_HandleTypeDef handle.
 * @param[in]   InitState : pointer to a APB_OBMx_InitialState_Def.
 *  @arg\b	    APB_OBM_INITSTA_LOW : OBMx set switch initial state to 0.
 *  @arg\b	    APB_OBM_INITSTA_HIGH :OBMx set switch initial state to 1.
 * @return		None
 *******************************************************************************
 */
MID_StatusTypeDef MID_APB_UpdateSwitchState(MID_OBMx_HandleTypeDef *mOBMx, uint32_t InitState)                
{
    uint32_t tmpREG;
        
    /* Process locked */
    __MID_LOCK(mOBMx);

    if(mOBMx->State == MID_APB_STATE_READY)
    {
        tmpREG = mOBMx->Instance->OBMx0.W & ~APB_OBM10_OBM1_STA_mask_w;
        tmpREG |= InitState;
        mOBMx->Instance->OBMx0.W = tmpREG;
    }
    else
    {
        __MID_UNLOCK(mOBMx);
        return MID_FAILURE;
    }
    
    /* Process unlocked */
    __MID_UNLOCK(mOBMx);

    /* Return function status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Return the APB state
 * @param[in]   mOBMx : pointer to a MID_OBMx_HandleTypeDef
 * @return		APB state
 *******************************************************************************
 */
uint32_t MID_OBMx_GetState(MID_OBMx_HandleTypeDef *mOBMx)
{
    /* Check the APB handle allocation */
    if(mOBMx == NULL)
    {
        return MID_APB_STATE_RESET;
    }
    
    return mOBMx->State;
}



#if defined(MG32_3RD) || defined(MG32_4TH)
/**
 *******************************************************************************
 * @brief       Handles NCO interrupt request.  
 * @return		None
 *******************************************************************************
 */
void MID_NCO_IRQHandler(void)
{
    if(__DRV_APB_GET_FLAG(APB_FLAG_NCO))
    {
        /* Clear APB Exti pending bit */
        __DRV_APB_CLEAR_FLAG(APB_FLAG_NCO);
        
        /* APB trigger user callback */
        MID_APB_NCOTriggerCallback();    
    }

}

/**
 *******************************************************************************
 * @brief       APB NCO callback.
 * @return		None
 *******************************************************************************
 */
__weak void MID_APB_NCOTriggerCallback(void)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(APB);
    /* NOTE : This function Should not be modified, when the callback is needed,
                the MID_APB_TriggerCallbackNCO could be implemented in the user file
    */
}
#endif
///@} 


#if defined(MG32_3RD) || defined(MG32_4TH)
/**
 * @name	APB_Exported_Functions_Group1 Peripheral State functions
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief       Return the NCO Output Status
 * @return		Returns the selected NCO output level: NCO_OUTPUTLEVEL_LOW or NCO_OUTPUTLEVEL_HIGH.
 *******************************************************************************
 */
uint32_t MID_NCO_GetOutputState(void)
{
    uint32_t SwitchStatus;
    
    /* Check the NCO Output */
    SwitchStatus = APB->STA.W & APB_STA_NCO0_OUT_mask_w;

    if(SwitchStatus != 0U)
    {
        return(NCO_OUTPUTLEVEL_HIGH);
    }
    return(NCO_OUTPUTLEVEL_LOW);
}
///@}
#endif


