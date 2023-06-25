/**
 ******************************************************************************
 *
 * @file        MG32x02z_APX_MID.c
 *
 * @brief       This file provides firmware functions to manage the following 
 *              functionalities of the APX peripheral:
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.02
 * @date        2022/03/17
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



#include "MG32x02z_APX_MID.h"




 /**
 * @name	Initial/Deinitial APX's CCL with CCL_HandleTypeDef
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief       Initializes the APX's CCL peripheral and regular group according to
 *              parameters specified in structure "CCL_HandleTypeDef".
 * @param[in]   mCCL : pointer to a CCL_HandleTypeDef
 * @return		  MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    CCL_HandleTypeDef mCCL;
    
    mCCL.Instance                   = CCL0;
    mCCL.TruthTable                 = APX_3IN_AND;                  // "AND" gate with 3 line input.
    mCCL.CCL_INTClockDivision       = CCL_INTERNALCLOCK_DIV1;       // CCL internal clock divide 1.
    mCCL.MUX0Input                  = CCLx_MUX0_IN5;                // CCL IN0 input MUX select PB0 signal.
    mCCL.MUX1Input                  = CCLx_MUX1_IN5;                // CCL IN1 input MUX select PB1 signal.
    mCCL.MUX2Input                  = CCLx_MUX2_IN5;                // CCL IN2 input MUX select PB2 signal.
    mCCL.CCL_SQIN                   = CCL_SQIN_1;                   // CCL sequential logic input is '1'.
    mCCL.SEQMode                    = CCL_SQSEL_DISABLE;            // Disable SQSEL effect.
    mCCL.EdgeDetectMode             = CCL_DISABLE_DETECTOR;         // Disable edge detect.
    mCCL.OutputSync                 = APX_DISABLE_SYNCHRONIZE;      // Bypass.
    mCCL.OutputPol                  = CCL_OUTPUTPOL_NONINVERTED;    // CCL output on GPIO isn't inverted.
    
    MID_APX_CCL_Init(&mCCL);
 
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_APX_CCL_Init(CCL_HandleTypeDef* mCCL)
{
    uint32_t tmpREG;
    
    /* Check APX handle */
    if(mCCL == NULL) 
    {
        return MID_FAILURE;
    }
    else
    {
        /* Init the low level hardware : SYSCFG to access CCL */
        MID_APX_CCL_MspInit(mCCL);
        
        /* Change APX peripheral state */
        mCCL->State = MID_CCL_STATE_BUSY;
    
        // ------------------------------------------------------------------------
        /* Config of APX parameters:                                              */
        // ------------------------------------------------------------------------
        // Config CCL input mux
        tmpREG = mCCL->MUX0Input                    | 
                 mCCL->MUX1Input                    | 
                 mCCL->MUX2Input;
        mCCL->Instance->CCLx1.W = tmpREG;
                 
        // Config CCL base parameters
        tmpREG = (mCCL->TruthTable << 16)           | 
                 mCCL->CCL_INTClockDivision         | 
                 mCCL->CCL_SQIN                     | 
                 mCCL->SEQMode                      | 
                 mCCL->EdgeDetectMode               | 
                 mCCL->OutputSync                   | 
                 mCCL->OutputPol; 
        // initial CCLx0 + enable truth table 
        mCCL->Instance->CCLx0.W = tmpREG | APX_CCL00_CCL0_TEN_enable_w;
        
        /* Initialize the APX state*/
        mCCL->State = MID_CCL_STATE_READY;
    }
    
    /* Return function status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Deinitialize the APX'S CCL peripheral registers to their default reset
 *         		values, with deinitialization of the APX MSP.
 * @param[in]   mCCL : pointer to a CCL_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    CCL_HandleTypeDef mCCL;
 
    MID_APX_CCL_DeInit(&mCCL);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_APX_CCL_DeInit(CCL_HandleTypeDef* mCCL)
{

    /* Process locked */
    __MID_LOCK(mCCL);

    /* Check the APX handle allocation and lock status */
    if(mCCL == NULL) 
    {
        return MID_FAILURE;
    }
    else
    {
        /* 1. Disable APX */
        __DRV_APX_CCL_DISABLE(mCCL);

        /* 2. Reset APX register */
        mCCL->Instance->CCLx0.W = (0x00000000U);
        mCCL->Instance->CCLx1.W = (0x00000000U);

        /* DeInit the low level hardware: GPIO, CLOCK and NVIC */
        MID_APX_CCL_MspDeInit(mCCL);

        /* Set APX state */
        mCCL->State = MID_CCL_STATE_RESET;
    }

    /* Process unlocked */
    __MID_UNLOCK(mCCL);

    /* Return function status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Initializes the APX Base MSP.
 * @param[in]   mCCL : pointer to a CCL_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_APX_CCL_MspInit(CCL_HandleTypeDef* mCCL)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mCCL);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the MID_APX_CCL_MspInit could be implemented in the user file
   */
}

/**
 *******************************************************************************
 * @brief       DeInitializes APX Base MSP.
 * @param[in]   mCCL : pointer to a CCL_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_APX_CCL_MspDeInit(CCL_HandleTypeDef* mCCL)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mCCL);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the MID_APX_CCL_MspDeInit could be implemented in the user file
   */
}
///@} 


/**
 * @name	APX_Exported_Functions_Group I/O operation functions 
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief       Start the CCL 
 * @param[in]   mCCL : pointer to a CCL_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    MID_APX_CCL_Start(&mCCL);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_APX_CCL_Start(CCL_HandleTypeDef* mCCL)
{
    
    /* Check the APX handle allocation and lock status */
    if(mCCL == NULL)
    {
        return MID_FAILURE;
    }
    else
    {

        if(mCCL->State == MID_CCL_STATE_READY)
        {
            /* Enable the selected CCL */
            __DRV_APX_CCL_ENABLE(mCCL);

            /* Set MID APX handle state */
            mCCL->State = MID_CCL_STATE_READY;
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
 * @brief       Stop the CCL 
 * @param[in]   mCCL : pointer to a CCL_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    MID_APX_CCL_Stop(&mCCL);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_APX_CCL_Stop(CCL_HandleTypeDef* mCCL)
{
    
    /* Check the APX handle allocation and lock status */
    if(mCCL == NULL)
    {
        return MID_FAILURE;
    }
    else
    {
        /* Stop potential conversion on going, on regular group */
        __DRV_APX_CCL_DISABLE(mCCL);
        
        /* Set APX state */
        mCCL->State = MID_CCL_STATE_READY;
    }
    
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Enables the interrupt and starts the CCL
 * @param[in]   mCCL : pointer to a CCL_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @par         Example
 * @code
    MID_APX_CCL_Start_IT(&mCCL);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_APX_CCL_Start_IT(CCL_HandleTypeDef* mCCL)
{
    
    /* Check the APX handle allocation and lock status */
    if(mCCL == NULL)
    {
        return MID_FAILURE;
    }
    else
    {
        /* Start & Enable CCLx */
        MID_APX_CCL_Start(mCCL);
        
        if(mCCL->State == MID_CCL_STATE_READY)
        {
            /* Enable peripheral CCLx IT */
            if(mCCL->Instance == CCL0)
            {
                __DRV_APX_ENABLE_IT(APX_IT_CCL0);
                __DRV_APX_ENABLE_ITEA();
            }
            else if(mCCL->Instance == CCL1)
            {
                __DRV_APX_ENABLE_IT(APX_IT_CCL1);
                __DRV_APX_ENABLE_ITEA();
            }
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
 * @brief       Stop CCL interruption.
 * @param[in]   mCCL : pointer to a CCL_HandleTypeDef
 * @return		MID_StatusTypeDef
 * @note 
 * @par         Example
 * @code
    CCL_HandleTypeDef mCCL;
 
    MID_APX_CCL_Stop_IT(&mCCL);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_APX_CCL_Stop_IT(CCL_HandleTypeDef* mCCL)
{

    /* Process locked */
    __MID_LOCK(mCCL);

    /* Disable interrupt */
    if(mCCL->State == MID_CCL_STATE_READY)
    {
        if(mCCL->State == MID_CCL_STATE_READY)
        {
            /* Enable peripheral CCLx IT */
            if(mCCL->Instance == CCL0)
            {
                __DRV_APX_DISABLE_IT(APX_IT_CCL0);
            }
            else if(mCCL->Instance == CCL1)
            {
                __DRV_APX_DISABLE_IT(APX_IT_CCL1);
            }
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
    else
    {
        return MID_FAILURE;
    }
    

    // disable ITEA
    if((APX->INT.W & (0xFFFFFFFE)) == 0x00000000U)
        __DRV_APX_DISABLE_ITEA();
    
    /* Stop CCL */
    MID_APX_CCL_Stop(mCCL);
    
    /* Process unlocked */
    __MID_UNLOCK(mCCL);

    /* Return function status */
    return MID_SUCCESS;
}
///@} 






/**
 * @name	APX_Exported_Functions_Group Peripheral State functions
 *   		
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief       Handles APX CCL interrupt request.  
 * @param[in]   mCCL : pointer to a CCL_HandleTypeDef
 * @return		None
 * @note 
 * @par         Example
 * @code
    CCL_HandleTypeDef mCCL;
 
    MID_APX_IRQHandler(&mCCL);
 * @endcode
 *******************************************************************************
 */
void MID_APX_CCL_IRQHandler(CCL_HandleTypeDef* mCCL)
{
    /* ========== Check APX flag ========== */
    if((__DRV_APX_GET_FLAG(APX_CCL0_FLAG)) && (__DRV_APX_GET_IT_SOURCE(APX_IT_CCL0)))
    {
        /* Clear APX Exti pending bit */
        __DRV_APX_CLEAR_FLAG(APX_CCL0_FLAG);
        
        /* APX trigger user callback */
        MID_APX_CCL0_TriggerCallback(mCCL);    
    }
    else if((__DRV_APX_GET_FLAG(APX_CCL1_FLAG)) || (__DRV_APX_GET_IT_SOURCE(APX_IT_CCL0)))
    {
        /* Clear APX Exti pending bit */
        __DRV_APX_CLEAR_FLAG(APX_CCL1_FLAG);
        
        /* APX trigger user callback */
        MID_APX_CCL1_TriggerCallback(mCCL);    
    }

}



/**
 *******************************************************************************
 * @brief       Return the output level (high or low) of the selected APX CCL. 
 * @param[in]   mCCL : pointer to a CCL_HandleTypeDef
 * @return		Returns the selected CCL output level: CCL_OUTPUTLEVEL_LOW or CCL_OUTPUTLEVEL_HIGH.
 * @note 
 * @par         Example
 * @code
 
    MID_APX_CCL_GetOutputLevel(&mCCL);
 * @endcode
 *******************************************************************************
 */
uint32_t MID_APX_CCL_GetOutputLevel(CCL_HandleTypeDef* mCCL)
{
    uint32_t STABITDef=0x00000000U;
    
    if(mCCL->Instance == CCL0)
        STABITDef = APX->STA.W & APX_STA_CCL0_OUT_mask_w;
    else if(mCCL->Instance == CCL1)
        STABITDef = APX->STA.W & APX_STA_CCL1_OUT_mask_w;
    
    if(STABITDef != 0U)
    {
        return(CCL_OUTPUTLEVEL_HIGH);
    }
    return(CCL_OUTPUTLEVEL_LOW);
}


/**
 *******************************************************************************
 * @brief       APX CCL0 callback.
 * @param[in]   mCCL : pointer to a CCL_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_APX_CCL0_TriggerCallback(CCL_HandleTypeDef* mCCL)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mCCL);
    /* NOTE : This function Should not be modified, when the callback is needed,
            the MID_APX_CCL0_TriggerCallback could be implemented in the user file
    */
}

/**
 *******************************************************************************
 * @brief       APX CCL1 callback.
 * @param[in]   mCCL : pointer to a CCL_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
__weak void MID_APX_CCL1_TriggerCallback(CCL_HandleTypeDef* mCCL)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mCCL);
    /* NOTE : This function Should not be modified, when the callback is needed,
            the MID_APX_CCL1_TriggerCallback could be implemented in the user file
    */
}



///@} 


/**
 * @name	APX_Exported_Functions_Group1 Peripheral State functions
 *   		
 */ 
///@{ 

/**
 *******************************************************************************
 * @brief       Return the APX state
 * @param[in]   mCCL : pointer to a CCL_HandleTypeDef
 * @return		APX state
 *******************************************************************************
 */
uint32_t MID_APX_CCL_GetState(CCL_HandleTypeDef* mCCL)
{
  /* Check the APX handle allocation */
  if(mCCL == NULL)
  {
    return MID_CCL_STATE_RESET;
  }

  return mCCL->State;
}



///@}

