/**
 ******************************************************************************
 *
 * @file        MG32x02z_CMP_MID.c
 *
 * @brief       This file provides firmware functions to manage the following 
 *              functionalities of the CMP peripheral:
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.04
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



#include "MG32x02z_CMP_MID.h"



/* Fixed timeout values for CMP settling time  */
#define CMP_Settle_Time     2       /*!< Unit: ms */

 /**
 * @name	Initial/Deinitial CMP with CMP_HandleTypeDef
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief       Initializes the CMP peripheral and regular group according to
 *              parameters specified in structure "CMP_HandleTypeDef".
 * @param[in]   mCMP : pointer to a CMP_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    CMP_HandleTypeDef mCMP;
    
    mCMP.Instance                   = CMPAC0;
    mCMP.Init.InvertingInput        = CMP_INVERTINGINPUT_IO0;       // Inverting PIN Input
    mCMP.Init.NonInvertingInput     = CMP_NONINVERTINGINPUT_IO1;    // Non-Inverting PIN Input
    mCMP.Init.ComparatorPol         = CMP_POSITIVE_POLARITY;        // CMP Possitive polarity
    mCMP.Init.OutputPol             = CMP_OUTPUTPOL_NONINVERTED;    // CMP non-invert output
    mCMP.Init.Hysteresis            = CMP_HYSTERESIS_LOW;           // Hysteresis window config
    mCMP.Init.Mode                  = CMP_MODE_HIGHSPEED;           // High speed for CMP
    mCMP.Init.TriggerMode           = CMP_TRIGGERMODE_IT_RISING;    // Rising edge of CMP_OUT
    mCMP.Init.OutputSync            = CMP_SYNCHRONIZE_BYPASS;       // CMP_OUT without filter function
    mCMP.Init.SyncFilterDIV         = CMP_SYNCHRONIZE_DIV1;         // no used when select BYPASS option
    mCMP.IntVref.IntVREF0_Level     = 32;                           // Internal VREF0 selection
    mCMP.IntVref.IntVREF1_Level     = 32;                           // Internal VREF1 selection
    
    MID_CMP_Init(&mCMP);
 
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_CMP_Init(CMP_HandleTypeDef* mCMP)
{
    uint32_t tmpREG;
    
    /* Check CMP handle */
    if(mCMP == NULL) 
    {
        return MID_FAILURE;
    }
    else
    {
        /* Init the low level hardware : SYSCFG to access comparators */
        MID_CMP_MspInit(mCMP);
        
        /* Change CMP peripheral state */
        mCMP->State = MID_CMP_STATE_BUSY;
    
        // ------------------------------------------------------------------------
        /* Config of CMP parameters:                                              */
        // ------------------------------------------------------------------------
        tmpREG = mCMP->Init.InvertingInput      | 
                 mCMP->Init.NonInvertingInput   | 
                 mCMP->Init.ComparatorPol       | 
                 mCMP->Init.OutputPol           | 
        #if defined(MG32_2ND) || defined(MG32_3RD)
                 mCMP->Init.Hysteresis          |
        #endif
                 mCMP->Init.Mode                | 
                 mCMP->Init.OutputSync          | 
                 mCMP->Init.SyncFilterDIV; 
        
        mCMP->Instance->CR.W = tmpREG;
        
        // internal VREF0 : En/Dis & R-ladder selection
        if((mCMP->Instance == CMPAC0) && ((mCMP->Init.InvertingInput == CMP_INVERTINGINPUT_IVREF) || (mCMP->Init.NonInvertingInput == CMP_NONINVERTINGINPUT_IVREF))) 
        {
            if(mCMP->IntVref.IntVREF0_Level > 63)
            {
                mCMP->State = MID_CMP_STATE_RESET;
                return MID_FAILURE;                         // parameter failure
            }
            
            // enable internal VREF0 and config R-ladder
            tmpREG = CMP->ANA.W & ~CMP_ANA_IVREF_RS_mask_w;
            tmpREG |= (mCMP->IntVref.IntVREF0_Level << 2) | CMP_ANA_IVREF_EN_enable_w;
            CMP->ANA.W = tmpREG;
        }
        
        // internal VREF1 : En/Dis & R-ladder selection
        if((mCMP->Instance != CMPAC0) && ((mCMP->Init.InvertingInput == CMP_INVERTINGINPUT_IVREF) || (mCMP->Init.NonInvertingInput == CMP_NONINVERTINGINPUT_IVREF))) 
        {
            if(mCMP->IntVref.IntVREF1_Level > 63)
            {
                mCMP->State = MID_CMP_STATE_RESET;
                return MID_FAILURE;                         // parameter failure
            }
            
            // enable internal VREF0 and config R-ladder
            tmpREG = CMP->ANA.W & ~CMP_ANA_IVREF2_RS_mask_w;
            tmpREG |= (mCMP->IntVref.IntVREF1_Level << 10) | CMP_ANA_IVREF2_EN_enable_w;
            CMP->ANA.W = tmpREG;
            
        }        
        /* Initialize the CMP state*/
        mCMP->State = MID_CMP_STATE_READY;
    }
    
    /* Return function status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Deinitialize the CMP peripheral registers to their default reset
 *         		values, with deinitialization of the CMP MSP.
 * @param[in]   mCMP : pointer to a CMP_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    CMP_HandleTypeDef mCMP;
 
    MID_CMP_DeInit(&mCMP);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_CMP_DeInit(CMP_HandleTypeDef *mCMP)
{

    /* Process locked */
    __MID_LOCK(mCMP);

    /* Check the CMP handle allocation and lock status */
    if(mCMP == NULL) 
    {
        return MID_FAILURE;
    }
    else
    {
        /* 1. Disable CMP */
        __DRV_CMP_DISABLE(mCMP);

        /* 2. Reset CMP register */
        mCMP->Instance->CR.W = (0x00000000U);

        /* DeInit the low level hardware: GPIO, CLOCK and NVIC */
        MID_CMP_MspDeInit(mCMP);

        /* Set CMP state */
        mCMP->State = MID_CMP_STATE_RESET;
    }

    /* Process unlocked */
    __MID_UNLOCK(mCMP);

    /* Return function status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Initializes the CMP Base MSP.
 * @param[in]   mCMP : pointer to a CMP_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_CMP_MspInit(CMP_HandleTypeDef* mCMP)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mCMP);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the MID_CMP_MspInit could be implemented in the user file
   */
}

/**
 *******************************************************************************
 * @brief       DeInitializes CMP Base MSP.
 * @param[in]   mCMP : pointer to a CMP_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_CMP_MspDeInit(CMP_HandleTypeDef* mCMP)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mCMP);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the MID_CMP_MspDeInit could be implemented in the user file
   */
}
///@} 


/**
 * @name	CMP_Exported_Functions_Group I/O operation functions 
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief       Start the comparator 
 * @param[in]   mCMP : pointer to a CMP_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    MID_CMP_Start(&mCMP);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_CMP_Start(CMP_HandleTypeDef* mCMP)
{
    uint32_t tickstart;
    
    /* Get tick count */
    tickstart = MID_GetTick();
    
    /* Check the CMP handle allocation and lock status */
    if(mCMP == NULL)
    {
        return MID_FAILURE;
    }
    else
    {

        if(mCMP->State == MID_CMP_STATE_READY)
        {
            /* Enable the selected comparator */
            __DRV_CMP_ENABLE(mCMP);

            /* Set MID CMP handle state */
            mCMP->State = MID_CMP_STATE_BUSY;

            /* Delay for CMP settle time */
            while((MID_GetTick()-tickstart) < CMP_Settle_Time);

            /* Set MID CMP handle state */
            mCMP->State = MID_CMP_STATE_READY;
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
 * @brief       Stop the comparator 
 * @param[in]   mCMP : pointer to a CMP_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    MID_CMP_Stop(&mCMP);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_CMP_Stop(CMP_HandleTypeDef* mCMP)
{
    #if defined(MG32_1ST)
    uint32_t tmpREG=0;
    #endif
    
    /* Check the CMP handle allocation and lock status */
    if(mCMP == NULL)
    {
        return MID_FAILURE;
    }
    else
    {
        /* Stop potential conversion on going, on regular group */
        __DRV_CMP_DISABLE(mCMP);
        
        // disable IVREF0/1
        if((mCMP->Instance == CMPAC0) && (((mCMP->Instance->CR.W & CMP_CR0_AC0_NMUX_mask_w) == 0) || ((mCMP->Instance->CR.W & CMP_CR0_AC0_PMUX_mask_w) == 0)))
        {
            // enable internal VREF0 and config R-ladder
            CMP->ANA.W &= ~CMP_ANA_IVREF_EN_enable_w;
        }

        if(mCMP->Instance != CMPAC0) 
        {
            //
            #if defined(MG32_2ND) || defined(MG32_3RD)
            if((CMP->CR1.W & CMP_CR1_AC1_EN_enable_b0) == 0)
                CMP->ANA.W &= ~CMP_ANA_IVREF2_EN_enable_w;
            #endif
            #if defined(MG32_1ST)
            if((CMP->CR2.W & CMP_CR2_AC2_EN_enable_b0) != 0)
                tmpREG += 1;
            if((CMP->CR3.W & CMP_CR3_AC3_EN_enable_b0) != 0)
                tmpREG += 1;
            
            if(tmpREG == 0)
                CMP->ANA.W &= ~CMP_ANA_IVREF2_EN_enable_w;
            #endif
        }
        
        
        /* Set CMP state */
        mCMP->State = MID_CMP_STATE_READY;
    }
    
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Enables the interrupt and starts the comparator
 * @param[in]   mCMP : pointer to a CMP_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @par         Example
 * @code
    MID_CMP_Start_IT(&mCMP);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_CMP_Start_IT(CMP_HandleTypeDef* mCMP)
{
    
    /* Check the CMP handle allocation and lock status */
    if(mCMP == NULL)
    {
        return MID_FAILURE;
    }
    else
    {
        MID_CMP_Start(mCMP);
        
        if(mCMP->State == MID_CMP_STATE_READY)
        {
            if(mCMP->Instance == CMPAC0)
            {
                CMP->INT.W |= mCMP->Init.TriggerMode;
                __DRV_CMP_ENABLE_ITEA();
            }
            if(mCMP->Instance == CMPAC1)
            {
                CMP->INT.W |= (mCMP->Init.TriggerMode << 4);
                __DRV_CMP_ENABLE_ITEA();
            }
            #if defined(MG32_1ST)
                if(mCMP->Instance == CMPAC2)
                {
                    CMP->INT.W |= (mCMP->Init.TriggerMode << 8);
                    __DRV_CMP_ENABLE_ITEA();
                }
                if(mCMP->Instance == CMPAC3)
                {
                    CMP->INT.W |= (mCMP->Init.TriggerMode << 12);
                    __DRV_CMP_ENABLE_ITEA();
                }
            #endif
            else
            {
                return MID_FAILURE;
            }
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
 * @brief       Stop comparator interruption.
 * @param[in]   mCMP : pointer to a CMP_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    CMP_HandleTypeDef mCMP;
 
    MID_CMP_Stop_IT(&mCMP);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_CMP_Stop_IT(CMP_HandleTypeDef* mCMP)
{

    /* Process locked */
    __MID_LOCK(mCMP);

    /* Disable interrupt */
    if(mCMP->State == MID_CMP_STATE_READY)
    {
        if(mCMP->Instance == CMPAC0)
        {
            CMP->INT.W &= ~mCMP->Init.TriggerMode;
        }
        if(mCMP->Instance == CMPAC1)
        {
            CMP->INT.W &= ~(mCMP->Init.TriggerMode << 4);
        }
        #if defined(MG32_1ST)
            if(mCMP->Instance == CMPAC2)
            {
                CMP->INT.W &= ~(mCMP->Init.TriggerMode << 8);
            }
            if(mCMP->Instance == CMPAC3)
            {
                CMP->INT.W &= ~(mCMP->Init.TriggerMode << 12);
            }
        #endif
        else
        {
            return MID_FAILURE;
        }
    }
    else
    {
        return MID_FAILURE;
    }
    

    // disable ITEA
    if((CMP->INT.W & (0xFFFFFFFE)) == 0x00000000U)
        __DRV_CMP_DISABLE_ITEA();
    
    /* Stop comparator */
    MID_CMP_Stop(mCMP);
    
    /* Process unlocked */
    __MID_UNLOCK(mCMP);

    /* Return function status */
    return MID_SUCCESS;
}
///@} 


/**
 * @name	CMP_Exported_Functions_Group Peripheral State functions
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief       Handles CMP interrupt request.  
 * @param[in]   mCMP : pointer to a CMP_HandleTypeDef
 * @return		None
 * @note 
 * @par         Example
 * @code
    CMP_HandleTypeDef mCMP;
 
    MID_CMP_IRQHandler(&mCMP);
 * @endcode
 *******************************************************************************
 */
void MID_CMP_IRQHandler(CMP_HandleTypeDef* mCMP)
{
    /* ========== Check CMP flag ========== */
    if(__DRV_CMP_GET_FLAG(CMP_CMP0_FLAG_RISING) || __DRV_CMP_GET_FLAG(CMP_CMP0_FLAG_FALLING))
    {
        /* Clear CMP Exti pending bit */
        __DRV_CMP_CLEAR_FLAG(CMP_CMP0_FLAG_ALL);
        
        /* CMP trigger user callback */
        MID_CMP_TriggerCallbackAC0(mCMP);    
    }
    else if(__DRV_CMP_GET_FLAG(CMP_CMP1_FLAG_RISING) || __DRV_CMP_GET_FLAG(CMP_CMP1_FLAG_FALLING))
    {
        /* Clear CMP Exti pending bit */
        __DRV_CMP_CLEAR_FLAG(CMP_CMP1_FLAG_ALL);
        
        /* CMP trigger user callback */
        MID_CMP_TriggerCallbackAC1(mCMP);    
    }
    #if defined(MG32_1ST)
        else if(__DRV_CMP_GET_FLAG(CMP_CMP2_FLAG_RISING) || __DRV_CMP_GET_FLAG(CMP_CMP2_FLAG_FALLING))
        {
            /* Clear CMP Exti pending bit */
            __DRV_CMP_CLEAR_FLAG(CMP_CMP2_FLAG_ALL);
            
            /* CMP trigger user callback */
            MID_CMP_TriggerCallbackAC2(mCMP);    
        }
        else if(__DRV_CMP_GET_FLAG(CMP_CMP3_FLAG_RISING) || __DRV_CMP_GET_FLAG(CMP_CMP3_FLAG_FALLING))
        {
            /* Clear CMP Exti pending bit */
            __DRV_CMP_CLEAR_FLAG(CMP_CMP3_FLAG_ALL);
            
            /* CMP trigger user callback */
            MID_CMP_TriggerCallbackAC3(mCMP);    
        }
    #endif

}


/**
 *******************************************************************************
 * @brief       Return the output level (high or low) of the selected comparator. 
 *              The output level depends on the selected polarity.
 *              If the comparator polarity is CMP_POSITIVE_POLARITY:
 *                - Comparator output is low when the non-inverting input is at a lower
 *                  voltage than the inverting input
 *                - Comparator output is high when the non-inverting input is at a higher
 *                  voltage than the inverting input
 *              If the comparator polarity is CMP_NEGATIVE_POLARITY:
 *                - Comparator output is high when the non-inverting input is at a lower
 *                  voltage than the inverting input
 *                - Comparator output is low when the non-inverting input is at a higher
 *                  voltage than the inverting input
 * @param[in]   mCMP : pointer to a CMP_HandleTypeDef
 * @return		Returns the selected comparator output level: CMP_OUTPUTLEVEL_LOW or CMP_OUTPUTLEVEL_HIGH.
 * @note 
 * @par         Example
 * @code
 
    MID_CMP_GetOutputLevel(&mCMP);
 * @endcode
 *******************************************************************************
 */
uint32_t MID_CMP_GetOutputLevel(CMP_HandleTypeDef* mCMP)
{
    uint32_t STABITDef=0x00000000U;
    
    if(mCMP->Instance == CMPAC0)
        STABITDef = CMP->STA.W & CMP_STA_AC0_S_mask_w;
    else if(mCMP->Instance == CMPAC1)
        STABITDef = CMP->STA.W & CMP_STA_AC1_S_mask_w;
    #if defined(MG32_1ST)   
    else if(mCMP->Instance == CMPAC2)
        STABITDef = CMP->STA.W & CMP_STA_AC2_S_mask_w;
    else if(mCMP->Instance == CMPAC3)
        STABITDef = CMP->STA.W & CMP_STA_AC3_S_mask_w;
    #endif
    
    if(STABITDef != 0U)
    {
        return(CMP_OUTPUTLEVEL_HIGH);
    }
    return(CMP_OUTPUTLEVEL_LOW);
}


/**
 *******************************************************************************
 * @brief       Comparator AC0 callback.
 * @param[in]   mCMP : pointer to a CMP_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_CMP_TriggerCallbackAC0(CMP_HandleTypeDef* mCMP)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mCMP);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the MID_CMP_TriggerCallbackAC0 could be implemented in the user file
   */
}

/**
 *******************************************************************************
 * @brief       Comparator AC1 callback.
 * @param[in]   mCMP : pointer to a CMP_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_CMP_TriggerCallbackAC1(CMP_HandleTypeDef* mCMP)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mCMP);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the MID_CMP_TriggerCallbackAC1 could be implemented in the user file
   */
}

#if defined(MG32_1ST)
/**
 *******************************************************************************
 * @brief       Comparator AC2 callback.
 * @param[in]   mCMP : pointer to a CMP_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_CMP_TriggerCallbackAC2(CMP_HandleTypeDef* mCMP)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mCMP);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the MID_CMP_TriggerCallbackAC2 could be implemented in the user file
   */
}

/**
 *******************************************************************************
 * @brief       Comparator AC3 callback.
 * @param[in]   mCMP : pointer to a CMP_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_CMP_TriggerCallbackAC3(CMP_HandleTypeDef* mCMP)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mCMP);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the MID_CMP_TriggerCallbackAC3 could be implemented in the user file
   */
}
#endif
///@} 


/**
 * @name	CMP_Exported_Functions_Group1 Peripheral State functions
 *   		
 */ 
///@{ 

/**
 *******************************************************************************
 * @brief       Return the CMP state
 * @param[in]   mCMP : pointer to a CMP_HandleTypeDef
 * @return		CMP state
 *******************************************************************************
 */
uint32_t MID_CMP_GetState(CMP_HandleTypeDef *mCMP)
{
  /* Check the CMP handle allocation */
  if(mCMP == NULL)
  {
    return MID_CMP_STATE_RESET;
  }

  return mCMP->State;
}

///@}

