/**
 ******************************************************************************
 *
 * @file        MG32x02z_WWDT_MID.c
 *
 * @brief       WWDT middleware module driver.
 *              This file provides firmware functions to manage the following 
 *              functionalities of the Independent Watchdog (WWDT) peripheral:
 *              Initialization and Start functions
 * @par         Project
 *              MG32x02z
 * @version     V1.04
 * @date        2022/06/24
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2020 Megawin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************
 * @par Disclaimer 
 *      The Demo software is provided "AS IS"  without any warranty, either 
 *      expressed or implied, including, but not limited to, the implied warranties 
 *      of merchantability and fitness for a particular purpose.  The author will 
 *      not be liable for any special, incidental, consequential or indirect 
 *      damages due to loss of data or any other reason. 
 *      These statements agree with the world wide and local dictated laws about 
 *      authorship and violence against these laws. 
 ******************************************************************************
 ******************************************************************************
 */ 
 
#include "MG32x02z_WWDT_MID.h"

/**
 * @name Initialize the WWDT
 * 
 */ 
///@{
/**
 *******************************************************************************
 * @brief               WWDT module initailze
 * @return              MID Status
 * @note                Select WWDT clock
 *                      Select WWDT interrupt
 *                      Set WWDT count , window , warnning & reload value
 * @par         Example
 * @code
        mWWDT.Instance = WWDT;                                              //Mapping WWDT base address
        mWWDT.Init.WWDT_RLR = 32;                                           //SET WWDT reload register
        mWWDT.Init.WWDT_WIN = 64;                                           //SET WWDT window compare register
        mWWDT.Init.WWDT_WRN = 64;                                           //SET WWDT warnning compare register
        mWWDT.Init.WWDT_INT_SEL = (WWDT_IT_WIN|WWDT_IT_WRN|WWDT_IT_TIE);    //Enable WWDT interrupt
        mWWDT.Init.WWDT_CLK_SEL = WWDT_CLK_UT;                              //Select WWDT clock source from UT
        if (MID_WWDT_Init(&mWWDT) != MID_OK)                                //WWDT initial and return value check
        {
                WWDT_Error_Handler();
        }
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_WWDT_Init(WWDT_HandleTypeDef *mWWDT)
{
    /* Check the WWDT handle allocation */
    if(mWWDT == NULL)
    {
        return MID_ERROR;
    }

    /* Check the parameters */
    assert_param(IS_WWDT_ALL_INSTANCE(mWWDT->Instance));
    assert_param(IS_WWDT_PRESCALER(mWWDT->Init.Prescaler));
    assert_param(IS_WWDT_WINDOW(mWWDT->Init.Window));
    assert_param(IS_WWDT_COUNTER(mWWDT->Init.Counter));
    assert_param(IS_WWDT_EWI_MODE(mWWDT->Init.EWIMode));
    assert_param(IS_WWDT_WINDOW(mWWDT->Init.Window));
  
    /* Module unprotect  */
    WWDT->KEY.W = 0xA217;
    
    /* Init the low level hardware */
    MID_WWDT_MspInit(mWWDT);                        //For user control.

    /* Set WWDT Counter */
    WWDT->RLR.W = mWWDT->Init.WWDT_RLR;             //Write WWDT reload regiter.
    WWDT->KEY.W = 0x2014;                           //Reflash and Reload WWDT count register.

    /* Set WWDT Prescaler and Window */
    WWDT->WIN.W = mWWDT->Init.WWDT_WIN;             //Write window compare register, Prescaler counter we are not SUP.
    
    /* Set WWDT Prescaler and Warning */
    WWDT->WRN.W = mWWDT->Init.WWDT_WRN;             //Write Warnining compare register, Prescaler counter we are not SUP.
    
    /* Eanable WWDT Interrujpt */
    __DRV_WWDT_ENABLE_IT(mWWDT,mWWDT->Init.WWDT_INT_SEL);
    
    /* Enable WWDT Function */
    __DRV_WWDT_ENABLE(mWWDT);
    /* WWDT module protect*/
    WWDT->KEY.W = 0;
    
    /* Return function status */
    return MID_OK;
}
///@}

/**
 * @name Initialize the WWDT MSP
 * 
 */ 
///@{
/**
 *******************************************************************************
 * @brief       For the custmer configuration for the specified WWDT module.
 * @return
 * @note        When rewriting this function in user file, mechanism may be added
 *              to avoid multiple initialize when MID_WWDT_Init function is called
 *              again to change parameters.
 * @par         Example
 * @code
        MID_WWDT_MspInit(mWWDT);
 
 * @endcode
 *******************************************************************************
 */
__weak void MID_WWDT_MspInit(WWDT_HandleTypeDef *mWWDT)
{
  if(mWWDT->Instance==WWDT)
  {
  /* USER CODE BEGIN WWDT_MspInit 0 */

  /* USER CODE END WWDT_MspInit 0 */
    /* Peripheral clock enable */
    
  /* USER CODE BEGIN WWDT_MspInit 1 */

  /* USER CODE END WWDT_MspInit 1 */
  }
}
///@}


/**
 * @name Refresh the WWDT
 * 
 */ 
///@{
/**
 *******************************************************************************
 * @brief               Refresh the WWDT counter value
 * @return              MID status
 * @note                mWWDT  pointer to a WWDT_HandleTypeDef structure that contains
 *                      the configuration information for the specified WWDT module.
 * @par         Example
 * @code
        MID_WWDT_Refresh(mWWDT);
 
 * @endcode
 *******************************************************************************
 */

MID_StatusTypeDef MID_WWDT_Refresh(void)
{
    /* Write to WWDT CR the WWDT Counter value to refresh with */
    WWDT->KEY.W = 0x2014;
    
    /* Return function status */
    return MID_OK;
}
///@}

/**
 * @name Handle WWDT interrupt request.
 * 
 */ 
///@{
/**
 *******************************************************************************
 * @brief           WWDT interrupt request.
 * @return
 * @note            The Early Wakeup Interrupt (EWI) can be used if specific safety operations
 *                  or data logging must be performed before the actual reset is generated.
 *                  The EWI interrupt is enabled by calling MID_WWDT_Init function with 
 *                  EWIMode set to WWDT_EWI_ENABLE.
 *
 *                  When the downcounter reaches the value 0x40, and EWI interrupt is
 *                  generated and the corresponding Interrupt Service Routine (ISR) can
 *                  be used to trigger specific actions (such as communications or data
 *                  logging), before resetting the device.
 * @par             Example
 * @code
        MID_WWDT_IRQHandler(&mWWDT);
 
 * @endcode
 *******************************************************************************
 */
void MID_WWDT_IRQHandler(WWDT_HandleTypeDef *mWWDT)
{
    /* Check if Overfloat Interrupt is enable */
    if(__DRV_WWDT_GET_IT_SOURCE(mWWDT,WWDT_IT_TIE) != CLR)
    {
        /* Check if WWDT Early Wakeup Interrupt occurred */
        if(__DRV_WWDT_GET_FLAG(mWWDT, WWDT_TF) != CLR)
        {
            /* Clear the WWDT Early Wakeup flag */
            __DRV_WWDT_CLEAR_FLAG(mWWDT, WWDT_TF);

            /* Overfloat interrupt callback */ 
            MID_WWDT_TFINTCallback(mWWDT);
        }
    }
    
    /* Check if Window Interrupt is enable */
    if(__DRV_WWDT_GET_IT_SOURCE(mWWDT,WWDT_IT_WIN) != CLR)
    {
        /* Check if WWDT Early Wakeup Interrupt occurred */
        if(__DRV_WWDT_GET_FLAG(mWWDT, WWDT_WINF) != CLR)
        {
            /* Clear the WWDT Early Wakeup flag */
            __DRV_WWDT_CLEAR_FLAG(mWWDT, WWDT_WINF);

            /* Window interrupt callback */ 
            MID_WWDT_WININTCallback(mWWDT);
        }
    }

    /* Check if Warning Interrupt is enable */
    if(__DRV_WWDT_GET_IT_SOURCE(mWWDT,WWDT_IT_WRN) != CLR)
    {
        /* Check if WWDT Early Wakeup Interrupt occurred */
        if(__DRV_WWDT_GET_FLAG(mWWDT, WWDT_WRNF) != CLR)
        {
            /* Clear the WWDT Early Wakeup flag */
            __DRV_WWDT_CLEAR_FLAG(mWWDT, WWDT_WRNF);

            /* Warning interrupt callback */ 
            MID_WWDT_WRNINTCallback(mWWDT);
        }
    }
}
///@}

/**
 * @name WWDT Warning Interrupt Callback.
 * 
 */ 
///@{
/**
 *******************************************************************************
 * @brief       WWDT Warning Interrupt callback.
 * @param[in]   mWWDT  pointer to a WWDT_HandleTypeDef structure that contains
 *              the configuration information for the specified WWDT module.
 * @return      None
 *******************************************************************************
 */
__weak void MID_WWDT_WRNINTCallback(WWDT_HandleTypeDef *mWWDT)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mWWDT);

    /* NOTE: This function should not be modified, when the callback is needed,
           the MID_WWDT_EarlyWakeupCallback could be implemented in the user file
    */
}

/**
 *******************************************************************************
 * @brief       WWDT Warning Interrupt callback.
 * @param[in]   mWWDT pointer to a WWDT_HandleTypeDef structure that contains
  *             the configuration information for the specified WWDT module.
 * @return      None
 *******************************************************************************
 */
__weak void MID_WWDT_WININTCallback(WWDT_HandleTypeDef *mWWDT)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mWWDT);

    /* NOTE: This function should not be modified, when the callback is needed,
           the MID_WWDT_EarlyWakeupCallback could be implemented in the user file
    */
}

/**
 *******************************************************************************
 * @brief       WWDT Overflow Interrupt callback.
 * @param[in]   mWWDT pointer to a WWDT_HandleTypeDef structure that contains
 *              the configuration information for the specified WWDT module.
 * @return      None
 *******************************************************************************
 */
__weak void MID_WWDT_TFINTCallback(WWDT_HandleTypeDef *mWWDT)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mWWDT);

    /* NOTE: This function should not be modified, when the callback is needed,
       the MID_WWDT_EarlyWakeupCallback could be implemented in the user file
    */
}
///@}

/**
 * @name WWDT Initial Error Function.
 * 
 */ 
///@{
/**
 *******************************************************************************
 * @brief       This function is executed in case of error occurrence.
 * @return
 * @note
 * @par         
 *******************************************************************************
 */
__weak void WWDT_Error_Handler(WWDT_HandleTypeDef *mWWDT)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    UNUSED(mWWDT);
    /* USER CODE END Error_Handler_Debug */
}
///@}


/************************ (C) COPYRIGHT Megawin Technology *****END OF FILE****/


