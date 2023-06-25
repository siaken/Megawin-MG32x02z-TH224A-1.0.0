/**
 ******************************************************************************
 *
 * @file        MG32x02z_IWDT_MID.c
 *
 * @brief       IWDT middleware module driver.
 *              This file provides firmware functions to manage the following 
 *              functionalities of the Independent Watchdog (IWDT) peripheral:
 *              Initialization and Start functions
 * @par         Project
 *              MG32x02z
 * @version     V1.01
 * @date        2019/10/18
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2019 Megawin Technology Co., Ltd.
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

#include "MG32x02z_IWDT_MID.h"


#define MID_IWDT_DEFAULT_TIMEOUT            39U             /*!< IWDT init timeout set */

  
/**
 * @name Initialize the IWDT
 * 
 */ 
///@{
/**
 *******************************************************************************
 * @brief       Initialize the IWDT according to the specified parameters in the 
 *              IWDT_InitTypeDef and start watchdog. Before exiting function, 
 *              watchdog is refreshed in order to have correct time base.
 * @param[in]   mIWDT
 * @return              
 * @note        Select IWDT clock
 *              Select IWDT interrupt
 * @par         Example
 * @code
        IWDT_HandleTypeDef mIWDT;
        
        mIWDT.Instance = IWDT;                                                      //Mapping IWDT base address
        mIWDT.Init.Interrupt = (IWDT_IT_EW1|IWDT_IT_EW0|IWDT_IT_TIE);                 //ENABLE IWDT
        mIWDT.Init.Prescaler = IWDT_PRESCALER_256;
        if (MID_IWDT_Init(&mIWDT) != MID_OK)
        {
            IWDT_Error_Handler(&mIWDT);
        }
    
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_IWDT_Init(IWDT_HandleTypeDef *mIWDT)
{
    uint32_t tickstart;

    /* Check the IWDT handle allocation */
    if(mIWDT == NULL)
    {
    return MID_ERROR;
    }

    /* Check the parameters */
    assert_param(IS_IWDT_ALL_INSTANCE(mIWDT->Instance));
    assert_param(IS_IWDT_PRESCALER(mIWDT->Init.Prescaler));
    assert_param(IS_IWDT_RELOAD(mIWDT->Init.Reload));
    assert_param(IS_IWDT_WINDOW(mIWDT->Init.Window));

    /* Enable write access to IWDT Protect Disable, IWDT_RLR and IWDT_WINR registers by writing
    0xA217 in KEY */
    IWDT_ENABLE_WRITE_ACCESS(mIWDT);
    mIWDT->Instance->KEY.W = 0xA217;

    /* Enable IWDT. LSI is turned on automaticaly */
    __DRV_IWDT_START(mIWDT);
    
    __DRV_IWDT_CLEAR_FLAG(mIWDT, IWDT_STA_ALLF);
    
    /* Write to IWDT registers the Prescaler & Reload values to work with */
    mIWDT->Instance->CLK.MBIT.CK_DIV = (uint8_t)mIWDT->Init.Prescaler;
    __DRV_IWDT_RELOAD_COUNTER(mIWDT);

    /* Write to IWDT registers the Prescaler & Reload values to work with */
    __DRV_IWDT_INT_ENABLE(mIWDT,mIWDT->Init.Interrupt);

    /* Check pending flag, if previous update not done, return timeout */
    tickstart = MID_GetTick();

    /* Wait for register to be updated */
    while(mIWDT->Instance->STA.W != NONE)
    {
        if((MID_GetTick() - tickstart ) > MID_IWDT_DEFAULT_TIMEOUT)
        {
            return MID_TIMEOUT;
        }
    }
    
    IWDT_DISABLE_WRITE_ACCESS(mIWDT);
    
    /* Return function status */
    return MID_OK;
}
///@}
 
/**
 * @name Refresh the IWDT.
 *   
 */ 
///@{
/**
 *******************************************************************************
 * @brief       IWDT refresh counter.
 * @details  
 * @return      MID status
 * @note
 * @par         Example
 *******************************************************************************
 */
MID_StatusTypeDef MID_IWDT_Refresh(IWDT_HandleTypeDef *mIWDT)
{
  /* Reload IWDT counter with value defined in the reload register */
  __DRV_IWDT_RELOAD_COUNTER(mIWDT);

  /* Return function status */
  return MID_OK;
}
///@}

/**
 * @name Handle IWDT interrupt request.
 * 
 */ 
///@{
/**
 *******************************************************************************
 * @brief           IWDT Interrupt request
 * @details  
 * @return          Non
 * @note
 * @par             Example
 * @code
                    MID_IWDT_IRQHandler(mIWDT);
 
 * @endcode
 *******************************************************************************
 */
void MID_IWDT_IRQHandler(IWDT_HandleTypeDef *mIWDT)
{
    /* Check if Overfloat Interrupt is enable */
    if(__DRV_IWDT_GET_INT_SOURCE(mIWDT,IWDT_IT_EW1)!= CLR)
    {
        /* Check if IWDT Early Wakeup 1 Interrupt occurred */
        if(__DRV_IWDT_GET_FLAG(mIWDT,IWDT_STA_EW1F) != CLR)
        {
            __DRV_IWDT_CLEAR_FLAG(mIWDT,IWDT_STA_EW1F);

            /* IWDT eary wake up 1 interrupt callback */	
            MID_IWDT_EW1INTCallback(mIWDT);
        }
    }

    if(__DRV_IWDT_GET_INT_SOURCE(mIWDT,IWDT_IT_EW0)!= CLR)
    {
        /* Check if IWDT Early Wakeup 0 Interrupt occurred */
        if(__DRV_IWDT_GET_FLAG(mIWDT,IWDT_STA_EW0F) != CLR)
        {
                __DRV_IWDT_CLEAR_FLAG(mIWDT,IWDT_STA_EW0F);
            /* IWDT eary wake up 0 interrupt callback */
            MID_IWDT_EW0INTCallback(mIWDT);
        }
    }
    
    if(__DRV_IWDT_GET_INT_SOURCE(mIWDT,IWDT_IT_TIE)!= CLR)
    {
        /* Check if IWDT overfloat Interrupt occurred */
        if(__DRV_IWDT_GET_FLAG(mIWDT,IWDT_STA_TIEF) != CLR)
        {
            __DRV_IWDT_CLEAR_FLAG(mIWDT,IWDT_STA_TIEF);
            /* IWDT overfloat interrupt callback */
            MID_IWDT_TIEINTCallback(mIWDT);
        }
    }
}
///@}

/**
 * @name  IWDT Interrupt Callback.
 * 
 */ 
///@{
/**
 *******************************************************************************
 * @brief       IWDT Early Wake Up 0 Interrupt Callback.
 * @param[in]   mIWDT  pointer to a WWDT_HandleTypeDef structure that contains
 *              the configuration information for the specified IWDT module.
 * @return      None
 *******************************************************************************
 */
__weak void MID_IWDT_EW0INTCallback(IWDT_HandleTypeDef *mIWDT)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mIWDT);

    /* NOTE: This function should not be modified, when the callback is needed,
           the MID_IWDT_EarlyWakeupCallback could be implemented in the user file
    */
}

/**
 *******************************************************************************
 * @brief       IWDT Early Wake Up 1 Interrupt Callback.
 * @param[in]   mIWDT  pointer to a WWDT_HandleTypeDef structure that contains
 *              the configuration information for the specified IWDT module.
 * @return      None
 *******************************************************************************
 */
__weak void MID_IWDT_EW1INTCallback(IWDT_HandleTypeDef *mIWDT)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mIWDT);

    /* NOTE: This function should not be modified, when the callback is needed,
           the MID_IWDT_EarlyWakeupCallback could be implemented in the user file
    */
}

/**
 *******************************************************************************
 * @brief       IWDT Overflow Interrupt Callback.
 * @param[in]   mIWDT  pointer to a WWDT_HandleTypeDef structure that contains
 *              the configuration information for the specified IWDT module.
 * @return      None
 *******************************************************************************
 */
__weak void MID_IWDT_TIEINTCallback(IWDT_HandleTypeDef *mIWDT)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mIWDT);

    /* NOTE: This function should not be modified, when the callback is needed,
           the MID_IWDT_EarlyWakeupCallback could be implemented in the user file
    */
}
///@}

/**
 * @name IWDT_Error_Handler
 *
 */
///@{ 
/**
 *******************************************************************************
 * @brief       This function is executed in case of error occurrence.
 * @return      None
 *******************************************************************************
 */
__weak void IWDT_Error_Handler(IWDT_HandleTypeDef *mIWDT)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    UNUSED(mIWDT);
    /* USER CODE END Error_Handler_Debug */
}
///@}


/************************ (C) COPYRIGHT Megawin Technology Co., Ltd. *****END OF FILE****/

