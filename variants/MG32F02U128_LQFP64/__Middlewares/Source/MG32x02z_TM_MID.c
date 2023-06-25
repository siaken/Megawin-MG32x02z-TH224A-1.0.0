/**
 ******************************************************************************
 *
 * @file        MG32x02z_TM_MID.c
 *
 * @brief       This file provides firmware functions to manage the following
 *              functionalities of the TM peripheral:
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.07
 * @date        2020/07/03
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2016 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************
 * @par         Disclaimer
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



#include "MG32x02z_TM_MID.h"

static void TM_OC0_SetConfig(TM_Struct* TMx, TM_OC_InitTypeDef* OC_Config);
static void TM_OC1_SetConfig(TM_Struct* TMx, TM_OC_InitTypeDef* OC_Config);
static void TM_OC2_SetConfig(TM_Struct* TMx, TM_OC_InitTypeDef* OC_Config);
static void TM_OC3_SetConfig(TM_Struct* TMx, TM_OC_InitTypeDef* OC_Config);
static void TM_SlaveTimer_SetConfig(TM_HandleTypeDef* mTM, TM_SlaveConfigTypeDef* sSlaveConfig);

/**
* @name    Initial/Deinitial TM with TM_HandleTypeDef
*
*/
///@{
/**
 *******************************************************************************
 * @brief       Initializes the TM base Unit according to the specified
 *              parameters in the TM_HandleTypeDef and create the associated handle.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM36;
    
    mTM36.Instance = TM36;
    mTM36.Init.TM_CounterMode = TM_CASCADE_UP;
    mTM36.Init.TM_Period = 1023;
    mTM36.Init.TM_Prescaler = 0;
    mTM36.State = MID_TM_STATE_RESET;

    MID_TM_Base_Init(&mTM36);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_Base_Init(TM_HandleTypeDef* mTM)
{
    /* Check the TM handle allocation */
    if(mTM == 0)
        return MID_FAILURE;

    if(mTM->State == MID_TM_STATE_RESET)
    {
        /* Allocate lock resource and initialize it */
        mTM->Lock = MID_UnLocked;

        /* Init the low level hardware : GPIO, CLOCK, NVIC */
        MID_TM_Base_MspInit(mTM);
    }

    /* Set the TM state */
    mTM->State= MID_TM_STATE_BUSY;

    /* Set the Time Base configuration */
    TM_Base_SetConfig(mTM->Instance, &mTM->Init);

    /* Initialize the TM state*/
    mTM->State = MID_TM_STATE_READY;

    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       DeInitializes the TM Base peripheral
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM36;

    MID_TM_Base_DeInit(&mTM36);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_Base_DeInit(TM_HandleTypeDef* mTM)
{
    mTM->State = MID_TM_STATE_BUSY;

    /* Disable the TM Peripheral Clock */
    __DRV_TM_DISABLE(mTM);

    /* DeInit the low level hardware: GPIO, CLOCK, NVIC */
    MID_TM_Base_MspDeInit(mTM);

    /* Change TM state */
    mTM->State = MID_TM_STATE_RESET;

    /* Release Lock */
    __MID_UNLOCK(mTM);

    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Initializes the TM Base MSP.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_TM_Base_MspInit(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_Base_MspInit could be implemented in the user file
     */
}

/**
 *******************************************************************************
 * @brief       DeInitializes TM Base MSP.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_TM_Base_MspDeInit(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_Base_MspDeInit could be implemented in the user file
     */
}


/**
* @name    Srart/Stop TM with TM_HandleTypeDef (IT, DMA)
*
*/
/**
 *******************************************************************************
 * @brief       Starts the TM Base generation.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM36;
    // to do ...
    
    MID_TM_Base_Start(&mTM36);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_Base_Start(TM_HandleTypeDef* mTM)
{
    /* Set the TM state */
    mTM->State= MID_TM_STATE_BUSY;

    /* Enable the Peripheral */
    __DRV_TM_ENABLE(mTM);

    /* Change the TM state*/
    mTM->State= MID_TM_STATE_READY;

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stop the TM Base generation.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM36;
    // to do ...
    
    MID_TM_Base_Stop(&mTM36);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_Base_Stop(TM_HandleTypeDef* mTM)
{
    /* Set the TM state */
    mTM->State= MID_TM_STATE_BUSY;

    /* Enable the Peripheral */
    __DRV_TM_DISABLE(mTM);

    /* Change the TM state*/
    mTM->State= MID_TM_STATE_READY;

    /* Return function status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Starts the TM Base generation in interrupt mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM36;
    // to do ...
    
    MID_TM_Base_Start_IT(&mTM36);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_Base_Start_IT(TM_HandleTypeDef* mTM)
{
    /* Enable the TM Update interrupt */
    __DRV_TM_ENABLE_IT(mTM, TM_IT_UPDATE);
    __DRV_TM_ENABLE_ITEA(mTM);

    /* Enable the Peripheral */
    __DRV_TM_ENABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stop the TM Base generation in interrupt mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM36;
    // to do ...
    
    MID_TM_Base_Stop_IT(&mTM36);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_Base_Stop_IT(TM_HandleTypeDef* mTM)
{
    /* Disable the TM Update interrupt */
    __DRV_TM_DISABLE_IT(mTM, TM_IT_UPDATE);
    if((mTM->Instance->INT.W & 0xFFFFFFFE) == 0)
        __DRV_TM_DISABLE_ITEA(mTM);
    
    /* Enable the Peripheral */
    __DRV_TM_DISABLE(mTM);

    /* check IT for ITEA */
    if((mTM->Instance->INT.W & 0xFFFFFFFE) == 0)
        __DRV_TM_DISABLE_ITEA(mTM);

    /* Return function status */
    return MID_SUCCESS;
}

///@}





/**
 * @name    Output Compare
 *
 */
///@{
/**
 *******************************************************************************
 * @brief       Starts the TM Output Compare signal generation.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM36;
    // Modify parameters & to do ...
    mTM36.Init.TM_CounterMode = TM_SEPARATE_UP;
    mTM36.Init.TM_ClockSource = TM_INTERNAL_CLOCK;
    mTM36.Init.TM_Period = 0x00FF;
    mTM36.Init.TM_Prescaler = 0;
    mTM36.State = MID_TM_STATE_RESET;
    
    MID_TM_OC_Init(&mTM36);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_OC_Init(TM_HandleTypeDef* mTM)
{
    if(mTM->State == MID_TM_STATE_RESET)
    {
        /* Allocate lock resource and initialize it */
        mTM->Lock = MID_UnLocked;

        /* Init the low level hardware : GPIO, CLOCK, NVIC and DMA */
        MID_TM_OC_MspInit(mTM);
    }

    /* Set the TM state */
    mTM->State= MID_TM_STATE_BUSY;

    /* Init the base time for the Output Compare */
    TM_Base_SetConfig(mTM->Instance,  &mTM->Init);

    /* Initialize the TM state*/
    mTM->State= MID_TM_STATE_READY;

    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stops the TM Output Compare signal generation.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM36;
    // Modify parameters & to do ...

    MID_TM_OC_DeInit(&mTM36);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_OC_DeInit(TM_HandleTypeDef* mTM)
{
    mTM->State = MID_TM_STATE_BUSY;

    /* Disable the TM Peripheral Clock */
    __DRV_TM_DISABLE(mTM);

    /* DeInit the low level hardware: GPIO, CLOCK, NVIC and DMA */
    MID_TM_OC_MspDeInit(mTM);

    /* Change TM state */
    mTM->State = MID_TM_STATE_RESET;

    /* Release Lock */
    __MID_UNLOCK(mTM);

    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Initializes the TM Output Compare MSP.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_TM_OC_MspInit(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_Base_MspInit could be implemented in the user file
     */
}

/**
 *******************************************************************************
 * @brief       DeInitializes TM Output Compare MSP.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_TM_OC_MspDeInit(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_Base_MspDeInit could be implemented in the user file
     */
}

/**
 *******************************************************************************
 * @brief       Starts the TM Output Compare signal generation.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM36;
    // Modify parameters & to do ...

    // set TM channel0 in OC mode (Ouput compare mode)
    MID_TM_OC_Start(&mTM36, MID_TM_Channel0);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_OC_Start(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    /* Enable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_16bit_OutputCompare);

    /* Enable the Peripheral */
    __DRV_TM_ENABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stops the TM Output Compare signal generation.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM36;
    // Modify parameters & to do ...

    // Stop TM channel1 in OC mode (Ouput compare mode)
    MID_TM_OC_Stop(&mTM36, MID_TM_Channel1);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_OC_Stop(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    /* Disable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_Disable);

    /* Disable the Peripheral */
    __DRV_TM_DISABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Starts the TM Output Compare signal generation in interrupt mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM36;
    // Modify parameters & to do ...

    // Set TM channel2 in OC mode (Ouput compare mode)
    // And enable TM channel2 interrupt service.
    MID_TM_OC_Start_IT(&mTM36, MID_TM_Channel2);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_OC_Start_IT(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    switch(Channel)
    {
    case MID_TM_Channel0:
    {
        /* Enable the TM Capture/Compare 0 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC0);
        __DRV_TM_ENABLE_ITEA(mTM);
    }
    break;

    case MID_TM_Channel1:
    {
        /* Enable the TM Capture/Compare 1 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC1);
        __DRV_TM_ENABLE_ITEA(mTM);
    }
    break;

    case MID_TM_Channel2:
    {
        /* Enable the TM Capture/Compare 2 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC2);
        __DRV_TM_ENABLE_ITEA(mTM);
    }
    break;

    case MID_TM_Channel3:
    {
        /* Enable the TM Capture/Compare 3 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC3);
        __DRV_TM_ENABLE_ITEA(mTM);
    }
    break;

    default:
        break;
    }

    /* Enable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_16bit_OutputCompare);

    // __MID_TM_ENABLE(mTM);
    __DRV_TM_ENABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stops the TM Output Compare signal generation in interrupt mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM36;
    // Modify parameters & to do ...

    // Set TM channel2 in OC mode (Ouput compare mode)
    // And disable TM channel2 interrupt service.
    MID_TM_OC_Stop_IT(&mTM36, MID_TM_Channel2);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_OC_Stop_IT(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    switch(Channel)
    {
    case MID_TM_Channel0:
    {
        /* Enable the TM Capture/Compare 0 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC0);
    }
    break;

    case MID_TM_Channel1:
    {
        /* Enable the TM Capture/Compare 1 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC1);
    }
    break;

    case MID_TM_Channel2:
    {
        /* Enable the TM Capture/Compare 2 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC2);
    }
    break;

    case MID_TM_Channel3:
    {
        /* Enable the TM Capture/Compare 3 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC3);
    }
    break;

    default:
        break;
    }

    // check INT to disable ITEA
    if((mTM->Instance->INT.W & 0xFFFFFFFE) == 0)
        __DRV_TM_DISABLE_ITEA(mTM);
    
    /* Enable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_Disable);

    /* Enable the Peripheral */
    __DRV_TM_DISABLE(mTM);

    /* check IT for ITEA */
    if((mTM->Instance->INT.W & 0xFFFFFFFE) == 0)
        __DRV_TM_DISABLE_ITEA(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Starts the TM Output Compare signal generation in DMA mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @param[in]   pData : The source Buffer address.
 * @param[in]   Length : The length of data to be transferred.
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM36;
    // Modify parameters & to do ...

    // Set TM channel3 in OC mode (Ouput compare mode)
    // And update TM channel3 CC3B with DMA access.
    MID_TM_OC_Start_DMA(&mTM36, MID_TM_Channel3);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_OC_Start_DMA(TM_HandleTypeDef* mTM, uint32_t Channel, uint32_t* pData, uint16_t Length)
{
    if((mTM->State) == (MID_TM_STATE_BUSY))
        return MID_BUSY;
    else if((mTM->State) == (MID_TM_STATE_READY))
    {
        if(((uint32_t)pData == 0U) && (Length > 0U))
            return MID_FAILURE;
        else
            mTM->State = MID_TM_STATE_BUSY;
    }

    switch(Channel)
    {
    case MID_TM_Channel0:
    {
        /* Set the DMA Period elapsed callback */
        mTM->hDMA[TM_DMA_ID_CC0]->XferCpltCallback = &TM_DMADelayPulseCplt;

        /* Set the DMA error callback */
        mTM->hDMA[TM_DMA_ID_CC0]->XferErrorCallback = TM_DMAError ;

        MID_DMA_Start_IT(mTM->hDMA[TM_DMA_ID_CC0], (uint32_t)pData, 0, Length);

        /* Enable the TM Capture/Compare 0 DMA request */
        __DRV_TM_ENABLE_DMA(mTM, TM_DMA_CH0_OC);
        
        /* Satart the TM counter */
        __DRV_TM_ENABLE(mTM);
    }
    break;

    case MID_TM_Channel1:
    {
        /* Set the DMA Period elapsed callback */
        mTM->hDMA[TM_DMA_ID_CC1]->XferCpltCallback = TM_DMADelayPulseCplt;

        /* Set the DMA error callback */
        mTM->hDMA[TM_DMA_ID_CC1]->XferErrorCallback = TM_DMAError ;

        MID_DMA_Start_IT(mTM->hDMA[TM_DMA_ID_CC1], (uint32_t)pData, 0, Length);

        /* Enable the TM Capture/Compare 1 DMA request */
        __DRV_TM_ENABLE_DMA(mTM, TM_DMA_CH1_OC);
        
        /* Satart the TM counter */
        __DRV_TM_ENABLE(mTM);
    }
    break;

    case MID_TM_Channel2:
    {
        /* Set the DMA Period elapsed callback */
        mTM->hDMA[TM_DMA_ID_CC2]->XferCpltCallback = TM_DMADelayPulseCplt;

        /* Set the DMA error callback */
        mTM->hDMA[TM_DMA_ID_CC2]->XferErrorCallback = TM_DMAError ;

        MID_DMA_Start_IT(mTM->hDMA[TM_DMA_ID_CC2], (uint32_t)pData, 0, Length);

        /* Enable the TM Capture/Compare 2 DMA request */
        __DRV_TM_ENABLE_DMA(mTM, TM_DMA_CH2_OC);
        
        /* Satart the TM counter */
        __DRV_TM_ENABLE(mTM);
    }
    break;

    case MID_TM_Channel3:
    {
        // MG32x02z MCU don't support Channel3 for OC output with DMA access
    }
    break;

    default:
        break;
    }

    /* Enable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_16bit_OutputCompare);

    // Break Control for OC mode
    /*   if(IS_TM_BREAK_INSTANCE(mTM->Instance) != RESET)
      {
        // to do ...
      }
     */
    mTM->State = MID_TM_STATE_READY;

    /* Enable the Peripheral */
    __DRV_TM_ENABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stops the TM Output Compare signal generation in DMA mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_OC_Stop_DMA(&mTM36, MID_TM_Channel3);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_OC_Stop_DMA(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    switch(Channel)
    {
    case MID_TM_Channel0:
        /* Disable the TM Capture/Compare 0 interrupt */
        __DRV_TM_DISABLE_DMA(mTM, TM_DMA_CH0_OC);
        break;

    case MID_TM_Channel1:
        /* Disable the TM Capture/Compare 1 DMA request */
        __DRV_TM_DISABLE_DMA(mTM, TM_DMA_CH1_OC);
        break;

    case MID_TM_Channel2:
        /* Disable the TM Capture/Compare 2 DMA request */
        __DRV_TM_DISABLE_DMA(mTM, TM_DMA_CH2_OC);
        break;

    case MID_TM_Channel3:
        // MG32x02z MCU don't support Channel3 for OC output with DMA access
        break;

    default:
        break;
    }

    /* Disable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_Disable);

    /* Disable the Peripheral */
    __DRV_TM_DISABLE(mTM);

    /* Change the mTM state */
    mTM->State = MID_TM_STATE_READY;

    /* Return function status */
    return MID_SUCCESS;
}
///@}



/**
 * @name    8bitx2 Output Compare
 *
 */
///@{
/**
 *******************************************************************************
 * @brief       Starts the TM 8bitx2 Output Compare signal generation.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;

    MID_TM_8Bx2OC_Init(&mTM);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_8Bx2OC_Init(TM_HandleTypeDef* mTM)
{
    if(mTM->State == MID_TM_STATE_RESET)
    {
        /* Allocate lock resource and initialize it */
        mTM->Lock = MID_UnLocked;

        /* Init the low level hardware : GPIO, CLOCK, NVIC and DMA */
        MID_TM_8Bx2OC_MspInit(mTM);
    }

    /* Set the TM state */
    mTM->State= MID_TM_STATE_BUSY;

    /* Init the base time for the Output Compare */
    TM_Base_SetConfig(mTM->Instance,  &mTM->Init);

    /* Initialize the TM state*/
    mTM->State= MID_TM_STATE_READY;

    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stops the TM 8bitx2 Output Compare signal generation.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;

    MID_TM_8Bx2OC_DeInit(&mTM);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_8Bx2OC_DeInit(TM_HandleTypeDef* mTM)
{
    mTM->State = MID_TM_STATE_BUSY;

    /* Disable the TM Peripheral Clock */
    __DRV_TM_DISABLE(mTM);

    /* DeInit the low level hardware: GPIO, CLOCK, NVIC and DMA */
    MID_TM_8Bx2OC_MspDeInit(mTM);

    /* Change TM state */
    mTM->State = MID_TM_STATE_RESET;

    /* Release Lock */
    __MID_UNLOCK(mTM);

    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Initializes the TM 8bitx2 Output Compare MSP.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_TM_8Bx2OC_MspInit(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_8Bx2OC_MspInit could be implemented in the user file
     */
}

/**
 *******************************************************************************
 * @brief       DeInitializes TM 8bitx2 Output Compare MSP.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_TM_8Bx2OC_MspDeInit(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_8Bx2OC_MspDeInit could be implemented in the user file
     */
}

/**
 *******************************************************************************
 * @brief       Starts the TM 8bitx2 Output Compare signal generation.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;

    MID_TM_8Bx2OC_Start(&mTM);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_8Bx2OC_Start(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    /* Enable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_8bitx2_OutputCompare);

    /* Enable the Peripheral */
    __DRV_TM_ENABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stops the TM 8bitx2 Output Compare signal generation.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;

    MID_TM_8Bx2OC_Stop(&mTM);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_8Bx2OC_Stop(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    /* Disable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_Disable);

    /* Disable the Peripheral */
    __DRV_TM_DISABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Starts the TM 8bitx2 Output Compare signal generation in 
 *              interrupt mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;

    MID_TM_8Bx2OC_Stop(&mTM, MID_TM_Channel0);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_8Bx2OC_Start_IT(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    switch(Channel)
    {
    case MID_TM_Channel0:
        /* Enable the TM Capture/Compare 0 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC0);
        __DRV_TM_ENABLE_ITEA(mTM);
        break;

    case MID_TM_Channel1:
        /* Enable the TM Capture/Compare 1 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC1);
        __DRV_TM_ENABLE_ITEA(mTM);
        break;

    case MID_TM_Channel2:
        /* Enable the TM Capture/Compare 2 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC2);
        __DRV_TM_ENABLE_ITEA(mTM);
        break;

    case MID_TM_Channel3:
        /* Enable the TM Capture/Compare 3 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC3);
        __DRV_TM_ENABLE_ITEA(mTM);
        break;

    default:
        break;
    }

    /* Enable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_8bitx2_OutputCompare);

    // __MID_TM_ENABLE(mTM);
    __DRV_TM_ENABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stops the TM 8bitx2 Output Compare signal generation in 
 *              interrupt mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;

    MID_TM_8Bx2OC_Stop(&mTM, MID_TM_Channel1);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_8Bx2OC_Stop_IT(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    switch(Channel)
    {
    case MID_TM_Channel0:
        /* Enable the TM Capture/Compare 0 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC0);
        break;

    case MID_TM_Channel1:
        /* Enable the TM Capture/Compare 1 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC1);
        break;

    case MID_TM_Channel2:
        /* Enable the TM Capture/Compare 2 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC2);
        break;

    case MID_TM_Channel3:
        /* Enable the TM Capture/Compare 3 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC3);
        break;

    default:
        break;
    }

    /* Enable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_Disable);

    /* Enable the Peripheral */
    __DRV_TM_DISABLE(mTM);

    /* check IT for ITEA */
    if((mTM->Instance->INT.W & 0xFFFFFFFE) == 0)
        __DRV_TM_DISABLE_ITEA(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Starts the TM 8bitx2 Output Compare signal generation in DMA mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @param[in]   pData : The source Buffer address.
 * @param[in]   Length : The length of data to be transferred.
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;

    MID_TM_8Bx2OC_Start_DMA(&mTM, MID_TM_Channel2);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_8Bx2OC_Start_DMA(TM_HandleTypeDef* mTM, uint32_t Channel, uint32_t* pData, uint16_t Length)
{
    if((mTM->State) == (MID_TM_STATE_BUSY))
        return MID_BUSY;
    else if((mTM->State) == (MID_TM_STATE_READY))
    {
        if(((uint32_t)pData == 0U) && (Length > 0U))
            return MID_FAILURE;
        else
            mTM->State = MID_TM_STATE_BUSY;
    }

    switch(Channel)
    {
    case MID_TM_Channel0:
        /* Set the DMA Period elapsed callback */
        mTM->hDMA[TM_DMA_ID_CC0]->XferCpltCallback = &TM_DMADelayPulseCplt;

        /* Set the DMA error callback */
        mTM->hDMA[TM_DMA_ID_CC0]->XferErrorCallback = TM_DMAError ;

        MID_DMA_Start_IT(mTM->hDMA[TM_DMA_ID_CC0], (uint32_t)pData, 0, Length);

        /* Enable the TM Capture/Compare 0 DMA request */
        __DRV_TM_ENABLE_DMA(mTM, TM_DMA_CH0_OC);
        break;

    case MID_TM_Channel1:
        /* Set the DMA Period elapsed callback */
        mTM->hDMA[TM_DMA_ID_CC1]->XferCpltCallback = TM_DMADelayPulseCplt;

        /* Set the DMA error callback */
        mTM->hDMA[TM_DMA_ID_CC1]->XferErrorCallback = TM_DMAError ;

        MID_DMA_Start_IT(mTM->hDMA[TM_DMA_ID_CC1], (uint32_t)pData, 0, Length);

        /* Enable the TM Capture/Compare 1 DMA request */
        __DRV_TM_ENABLE_DMA(mTM, TM_DMA_CH1_OC);
        break;

    case MID_TM_Channel2:
        /* Set the DMA Period elapsed callback */
        mTM->hDMA[TM_DMA_ID_CC2]->XferCpltCallback = TM_DMADelayPulseCplt;

        /* Set the DMA error callback */
        mTM->hDMA[TM_DMA_ID_CC2]->XferErrorCallback = TM_DMAError ;

        MID_DMA_Start_IT(mTM->hDMA[TM_DMA_ID_CC2], (uint32_t)pData, 0, Length);

        /* Enable the TM Capture/Compare 2 DMA request */
        __DRV_TM_ENABLE_DMA(mTM, TM_DMA_CH2_OC);
        break;

    case MID_TM_Channel3:
        // MG32x02z MCU don't support Channel3 for OC output
        break;

    default:
        break;
    }

    /* Enable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_8bitx2_OutputCompare);

    mTM->State = MID_TM_STATE_READY;

    /* Enable the Peripheral */
    __DRV_TM_ENABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stops the TM 8bitx2 Output Compare signal generation in DMA mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;

    MID_TM_8Bx2OC_Start_DMA(&mTM, MID_TM_Channel3);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_8Bx2OC_Stop_DMA(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    switch(Channel)
    {
    case MID_TM_Channel0:
        /* Disable the TM Capture/Compare 0 interrupt */
        __DRV_TM_DISABLE_DMA(mTM, TM_DMA_CH0_OC);
        break;

    case MID_TM_Channel1:
        /* Disable the TM Capture/Compare 1 DMA request */
        __DRV_TM_DISABLE_DMA(mTM, TM_DMA_CH1_OC);
        break;

    case MID_TM_Channel2:
        /* Disable the TM Capture/Compare 2 DMA request */
        __DRV_TM_DISABLE_DMA(mTM, TM_DMA_CH2_OC);
        break;

    case MID_TM_Channel3:
        // MG32x02z MCU don't support Channel3 for OC output
        break;

    default:
        break;
    }

    /* Disable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_Disable);

    /* Disable the Peripheral */
    __DRV_TM_DISABLE(mTM);

    /* Change the mTM state */
    mTM->State = MID_TM_STATE_READY;

    /* Return function status */
    return MID_SUCCESS;
}
///@}





/**
 * @name    PWM output configuration
 *
 */
///@{
/**
 *******************************************************************************
 * @brief       Initializes the TM PWM TMe Base according to the specified
 *              parameters in the TM_HandleTypeDef and create the associated handle.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM36;

    mTM36.Instance = TM36;
    mTM36.Init.TM_ClockSource = TM_INTERNAL_CLOCK;
    mTM36.Init.TM_CounterMode = TM_CASCADE_UP;
    mTM36.Init.TM_Period = 1023;
    mTM36.Init.TM_Prescaler = 0;
    mTM36.State = MID_TM_STATE_RESET;
    
    MID_TM_PWM_Init(&mTM36);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_PWM_Init(TM_HandleTypeDef* mTM)
{

    if(mTM->State == MID_TM_STATE_RESET)
    {
        /* Allocate lock resource and initialize it */
        mTM->Lock = MID_UnLocked;

        /* Init the low level hardware : GPIO, CLOCK, NVIC and DMA */
        MID_TM_PWM_MspInit(mTM);
    }

    /* Set the TM state */
    mTM->State= MID_TM_STATE_BUSY;

    /* Init the base time for the Output Compare */
    TM_Base_SetConfig(mTM->Instance,  &mTM->Init);

    /* Initialize the TM state*/
    mTM->State= MID_TM_STATE_READY;

    return MID_SUCCESS;

}


/**
 *******************************************************************************
 * @brief       DeInitializes the TM peripheral
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;

    MID_TM_PWM_DeInit(&mTM);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_PWM_DeInit(TM_HandleTypeDef* mTM)
{
    /* Release Lock */
    __MID_LOCK(mTM);
    
    mTM->State = MID_TM_STATE_BUSY;

    /* Disable the TM Peripheral Clock */
    __DRV_TM_DISABLE(mTM);

    /* DeInit the low level hardware: GPIO, CLOCK, NVIC and DMA */
    MID_TM_PWM_MspDeInit(mTM);

    /* Change TM state */
    mTM->State = MID_TM_STATE_RESET;

    /* Release Lock */
    __MID_UNLOCK(mTM);

    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Initializes the TM PWM MSP.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_TM_PWM_MspInit(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_PWM_MspInit could be implemented in the user file
     */
}


/**
 *******************************************************************************
 * @brief       DeInitializes TM PWM MSP.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_TM_PWM_MspDeInit(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_PWM_MspDeInit could be implemented in the user file
     */
}


/**
 *******************************************************************************
 * @brief       Starts the PWM signal generation.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;               
    TM_OC_InitTypeDef sConfig;
    
    MID_TM_OC_Struct_Init(&sConfig);               // default initial (output state)
    sConfig.OCMode = TM_CH_Disable;
    sConfig.Pulse = 0;                          // Duty cycle = 0%
    MID_TM_PWM_ConfigChannel(&mTM36, &sConfig, MID_TM_Channel0);
    MID_TM_PWM_ConfigChannel(&mTM36, &sConfig, MID_TM_Channel1);
    MID_TM_PWM_ConfigChannel(&mTM36, &sConfig, MID_TM_Channel2);

    MID_TM_PWM_Start(&mTM, MID_TM_Channel0);    // Channel0 be 16bit PWM output  
    MID_TM_PWM_Start(&mTM, MID_TM_Channel1);
    MID_TM_PWM_Start(&mTM, MID_TM_Channel2);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_PWM_Start(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    /* Enable the PWM channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_16bit_PWM);

    // Enable Break Control for PWM mode 
    if(mTM->Instance == TM36) 
    {
        // control TM36_BK_EN & TM36_BK_EN3
        __DRV_TM_ENABLE_BREAK(mTM);
    }
    
    /* Enable the Peripheral */
    __DRV_TM_ENABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stops the PWM signal generation.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_PWM_Stop(&mTM, MID_TM_Channel2);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_PWM_Stop(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    /* Disable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_Disable);

    // Disable Break Control for PWM mode 
    if(mTM->Instance == TM36) 
    {
        // control TM36_BK_EN & TM36_BK_EN3
        if((mTM->Instance->CCMDS.H[0] & TM_ALLCH_PWMMode) == 0x0000)
            __DRV_TM_DISABLE_BREAK(mTM);
    }

    /* Disable the Peripheral */
    __DRV_TM_DISABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Starts the PWM signal generation in interrupt mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_PWM_Start_IT(&mTM, MID_TM_Channel1);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_PWM_Start_IT(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    switch(Channel)
    {
    case MID_TM_Channel0:
    {
        /* Enable the TM Capture/Compare 0 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC0);
        __DRV_TM_ENABLE_ITEA(mTM);
    }
    break;

    case MID_TM_Channel1:
    {
        /* Enable the TM Capture/Compare 1 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC1);
        __DRV_TM_ENABLE_ITEA(mTM);
    }
    break;

    case MID_TM_Channel2:
    {
        /* Enable the TM Capture/Compare 2 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC2);
        __DRV_TM_ENABLE_ITEA(mTM);
    }
    break;

    case MID_TM_Channel3:
    {
        /* Enable the TM Capture/Compare 3 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC3);
        __DRV_TM_ENABLE_ITEA(mTM);
    }
    break;

    default:
        break;
    }

    /* Enable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_16bit_PWM);

    // Enable Break Control for PWM mode 
    if(mTM->Instance == TM36) 
    {
        // control TM36_BK_EN & TM36_BK_EN3
        __DRV_TM_ENABLE_BREAK(mTM);
    }


    // __MID_TM_ENABLE(mTM);
    __DRV_TM_ENABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stops the PWM signal generation in interrupt mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_PWM_Stop_IT(&mTM, MID_TM_Channel2);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_PWM_Stop_IT(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    switch(Channel)
    {
    case MID_TM_Channel0:
    {
        /* Enable the TM Capture/Compare 0 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC0);
    }
    break;

    case MID_TM_Channel1:
    {
        /* Enable the TM Capture/Compare 1 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC1);
    }
    break;

    case MID_TM_Channel2:
    {
        /* Enable the TM Capture/Compare 2 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC2);
    }
    break;

    case MID_TM_Channel3:
    {
        /* Enable the TM Capture/Compare 3 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC3);
    }
    break;

    default:
        break;
    }

    /* Enable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_Disable);

    // Disable Break Control for PWM mode 
    if(mTM->Instance == TM36) 
    {
        // control TM36_BK_EN & TM36_BK_EN3
        if((mTM->Instance->CCMDS.H[0] & TM_ALLCH_PWMMode) == 0x0000)
            __DRV_TM_DISABLE_BREAK(mTM);
    }

    /* Enable the Peripheral */
    __DRV_TM_DISABLE(mTM);

    /* check IT for ITEA */
    if((mTM->Instance->INT.W & 0xFFFFFFFE) == 0)
        __DRV_TM_DISABLE_ITEA(mTM);

    /* Return function status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Starts the TM PWM signal generation in DMA mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 * @param[in]   pData : The source Buffer address.
 * @param[in]   Length : The length of data to be transferred.
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef        mTM;
    TM_ClockConfigTypeDef   CKConfig;
    TM_OC_InitTypeDef       sConfig;
    DMA_HandleTypeDef       mTM_DMA[3];
    
    uint16_t Src0[] = {0x2525, 0x4000, 0x2525, 0x5000};
    uint16_t Src1[] = {0x2525, 0x3000, 0x2525, 0x4000};
    uint16_t Src2[] = {0x2525, 0x2000, 0x2525, 0x3000};
    
    // Time Base Init
    mTM.Instance                    = TM36;
    mTM.Init.TM_CounterMode         = TM_CASCADE_UP;
    mTM.Init.TM_Period              = 1023;
    mTM.Init.TM_Prescaler           = 0;
    mTM.State                       = MID_TM_STATE_RESET;
    MID_TM_PWM_Init(&mTM);
    
    // clock initial
    CKConfig.TM_ClockSource         = TM_INTERNAL_CLOCK;
    CKConfig.TM_ExternalClockSource = 0;
    CKConfig.TM_INTClockDivision    = TM_INTERNALCLOCK_DIVDER_DIV1;
    CKConfig.TM_InternalClockSource = TM_INTERNALCLOCK_PROC;
    MID_TM_ConfigClockSource(&mTM, &CKConfig);  

    // OCx pin initial
    MID_TM_OC_Struct_Init(&sConfig);
    sConfig.OCMode                  = TM_CH_16bit_PWM;
    sConfig.Pulse                   = 1000;
    MID_TM_PWM_ConfigChannel(&mTM, &sConfig, MID_TM_Channel0);

    sConfig.Pulse                   = 2000;
    MID_TM_PWM_ConfigChannel(&mTM, &sConfig, MID_TM_Channel1);

    sConfig.Pulse                   = 3000;
    MID_TM_PWM_ConfigChannel(&mTM, &sConfig, MID_TM_Channel2);
    
    sConfig.Pulse                   = 4000;
    MID_TM_PWM_ConfigChannel(&mTM, &sConfig, MID_TM_Channel3);

    // PWM output with DMA access (MG32F02A132 support 3 channels)
    mTM.hDMA[0] = &mTM_DMA[0];
    mTM.hDMA[1] = &mTM_DMA[1];
    mTM.hDMA[2] = &mTM_DMA[2];
    
    MID_TM_PWM_Start_DMA(&mTM, MID_TM_Channel0, (uint32_t *) &Src0, 8);
    MID_TM_PWM_Start_DMA(&mTM, MID_TM_Channel1, (uint32_t *) &Src1, 8);
    MID_TM_PWM_Start_DMA(&mTM, MID_TM_Channel2, (uint32_t *) &Src2, 8);
    
    
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_PWM_Start_DMA(TM_HandleTypeDef* mTM, uint32_t Channel, uint32_t* pData, uint16_t Length)
{
    if((mTM->State) == (MID_TM_STATE_BUSY))
        return MID_BUSY;
    else if((mTM->State) == (MID_TM_STATE_READY))
    {
        if(((uint32_t)pData == 0U) && (Length > 0U))
            return MID_FAILURE;
        else
            mTM->State = MID_TM_STATE_BUSY;
    }

    switch(Channel)
    {
    case MID_TM_Channel0:
    {
        /* Set the DMA Period elapsed callback */
        mTM->hDMA[TM_DMA_ID_CC0]->XferCpltCallback = &TM_DMADelayPulseCplt;

        /* Set the DMA error callback */
        mTM->hDMA[TM_DMA_ID_CC0]->XferErrorCallback = TM_DMAError ;

        MID_DMA_Start_IT(mTM->hDMA[TM_DMA_ID_CC0], (uint32_t)pData, 0, Length);

        /* Enable the TM Capture/Compare 0 DMA request */
        __DRV_TM_ENABLE_DMA(mTM, TM_DMA_CH0_OC);
    }
    break;

    case MID_TM_Channel1:
    {
        /* Set the DMA Period elapsed callback */
        mTM->hDMA[TM_DMA_ID_CC1]->XferCpltCallback = TM_DMADelayPulseCplt;

        /* Set the DMA error callback */
        mTM->hDMA[TM_DMA_ID_CC1]->XferErrorCallback = TM_DMAError ;

        MID_DMA_Start_IT(mTM->hDMA[TM_DMA_ID_CC1], (uint32_t)pData, 0, Length);

        /* Enable the TM Capture/Compare 1 DMA request */
        __DRV_TM_ENABLE_DMA(mTM, TM_DMA_CH1_OC);
    }
    break;

    case MID_TM_Channel2:
    {
        /* Set the DMA Period elapsed callback */
        mTM->hDMA[TM_DMA_ID_CC2]->XferCpltCallback = TM_DMADelayPulseCplt;

        /* Set the DMA error callback */
        mTM->hDMA[TM_DMA_ID_CC2]->XferErrorCallback = TM_DMAError ;
        
        MID_DMA_Start_IT(mTM->hDMA[TM_DMA_ID_CC2], (uint32_t)pData, 0, Length);

        /* Enable the TM Capture/Compare 2 DMA request */
        __DRV_TM_ENABLE_DMA(mTM, TM_DMA_CH2_OC);
    }
    break;

    case MID_TM_Channel3:
    {
        // MG32x02z MCU don't support Channel3 for OC output
    }
    break;

    default:
        break;
    }

    /* Enable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_16bit_PWM);

    // Enable Break Control for PWM mode 
    if(mTM->Instance == TM36) 
    {
        // control TM36_BK_EN & TM36_BK_EN3
        __DRV_TM_ENABLE_BREAK(mTM);
    }
    
    
    mTM->State = MID_TM_STATE_READY;

    /* Enable the Peripheral */
    __DRV_TM_ENABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Stops the TM PWM signal generation in DMA mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 * @note
 * @par         Example
 * @code
    MID_TM_PWM_Stop_DMA(&mTM, MID_TM_Channel1);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_PWM_Stop_DMA(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    switch(Channel)
    {
    case MID_TM_Channel0:
    {
        /* Disable the TM Capture/Compare 0 interrupt */
        __DRV_TM_DISABLE_DMA(mTM, TM_DMA_CH0_OC);
    }
    break;

    case MID_TM_Channel1:
    {
        /* Disable the TM Capture/Compare 1 DMA request */
        __DRV_TM_DISABLE_DMA(mTM, TM_DMA_CH1_OC);
    }
    break;

    case MID_TM_Channel2:
    {
        /* Disable the TM Capture/Compare 2 DMA request */
        __DRV_TM_DISABLE_DMA(mTM, TM_DMA_CH2_OC);
    }
    break;

    case MID_TM_Channel3:
    {
        // MG32x02z MCU don't support Channel3 for OC output
    }
    break;

    default:
        break;
    }

    /* Disable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_Disable);

    // Disable Break Control for PWM mode 
    if(mTM->Instance == TM36) 
    {
        // control TM36_BK_EN & TM36_BK_EN3
        if((mTM->Instance->CCMDS.H[0] & TM_ALLCH_PWMMode) == 0x0000)
            __DRV_TM_DISABLE_BREAK(mTM);
    }

    /* Disable the Peripheral */
    __DRV_TM_DISABLE(mTM);

    /* Change the mTM state */
    mTM->State = MID_TM_STATE_READY;

    /* Return function status */
    return MID_SUCCESS;
}

///@}





/**
 * @name    8Bitx2 PWM output configuration
 *
 */
///@{
/**
 *******************************************************************************
 * @brief       Initializes the TM PWM TMe Base according to the specified
 *              parameters in the TM_HandleTypeDef and create the associated handle.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM36;

    mTM36.Instance = TM36;
    mTM36.Init.TM_ClockSource = TM_INTERNAL_CLOCK;
    mTM36.Init.TM_CounterMode = TM_CASCADE_UP;
    mTM36.Init.TM_Period = 0x00FF;
    mTM36.Init.TM_Prescaler = 0;
    mTM36.State = MID_TM_STATE_RESET;
    
    MID_TM_8Bx2PWM_Init(&mTM36);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_8Bx2PWM_Init(TM_HandleTypeDef* mTM)
{

    if(mTM->State == MID_TM_STATE_RESET)
    {
        /* Allocate lock resource and initialize it */
        mTM->Lock = MID_UnLocked;

        /* Init the low level hardware : GPIO, CLOCK, NVIC and DMA */
        MID_TM_8Bx2PWM_MspInit(mTM);
    }

    /* Set the TM state */
    mTM->State= MID_TM_STATE_BUSY;

    /* Init the base time for the Output Compare */
    TM_Base_SetConfig(mTM->Instance,  &mTM->Init);

    /* Initialize the TM state*/
    mTM->State= MID_TM_STATE_READY;

    return MID_SUCCESS;

}


/**
 *******************************************************************************
 * @brief       DeInitializes the TM peripheral
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_8Bx2PWM_DeInit(&mTM);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_8Bx2PWM_DeInit(TM_HandleTypeDef* mTM)
{
    /* Release Lock */
    __MID_LOCK(mTM);
    
    mTM->State = MID_TM_STATE_BUSY;

    /* Disable the TM Peripheral Clock */
    __DRV_TM_DISABLE(mTM);

    /* DeInit the low level hardware: GPIO, CLOCK, NVIC and DMA */
    MID_TM_8Bx2PWM_MspDeInit(mTM);

    /* Change TM state */
    mTM->State = MID_TM_STATE_RESET;

    /* Release Lock */
    __MID_UNLOCK(mTM);

    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Initializes the TM PWM MSP.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_TM_8Bx2PWM_MspInit(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_8Bx2PWM_MspInit could be implemented in the user file
     */
}


/**
 *******************************************************************************
 * @brief       DeInitializes TM PWM MSP.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_TM_8Bx2PWM_MspDeInit(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_8Bx2PWM_MspDeInit could be implemented in the user file
     */
}


/**
 *******************************************************************************
 * @brief       Starts the PWM signal generation.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;               
    TM_OC_InitTypeDef sConfig;
    
    MID_TM_OC_Struct_Init(&sConfig);               // default initial (output state)
    sConfig.OCMode = TM_CH_16bit_PWM;
    sConfig.Pulse = 0;                          // Duty cycle = 0%, 0%
    MID_TM_PWM_ConfigChannel(&mTM36, &sConfig, MID_TM_Channel0);
    MID_TM_PWM_ConfigChannel(&mTM36, &sConfig, MID_TM_Channel1);
    MID_TM_PWM_ConfigChannel(&mTM36, &sConfig, MID_TM_Channel2);

    MID_TM_8Bx2PWM_Start(&mTM, MID_TM_Channel0);    // Channel0 be 8bit x 2 PWM output  
    MID_TM_8Bx2PWM_Start(&mTM, MID_TM_Channel1);
    MID_TM_8Bx2PWM_Start(&mTM, MID_TM_Channel2);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_8Bx2PWM_Start(TM_HandleTypeDef* mTM, uint32_t Channel)
{

    /* Enable the Capture compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_8bitx2_PWM);

    // Enable Break Control for PWM mode 
    if(mTM->Instance == TM36) 
    {
        // control TM36_BK_EN & TM36_BK_EN3
        __DRV_TM_ENABLE_BREAK(mTM);
    }

    /* Enable the Peripheral */
    __DRV_TM_ENABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stops the PWM signal generation.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_8Bx2PWM_Stop(&mTM);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_8Bx2PWM_Stop(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    /* Disable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_Disable);

    // Disable Break Control for PWM mode 
    if(mTM->Instance == TM36) 
    {
        // control TM36_BK_EN & TM36_BK_EN3
        if((mTM->Instance->CCMDS.H[0] & TM_ALLCH_PWMMode) == 0x0000)
            __DRV_TM_DISABLE_BREAK(mTM);
    }

    /* Disable the Peripheral */
    __DRV_TM_DISABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Starts the PWM signal generation in interrupt mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;
    TM_OC_InitTypeDef sConfig;
    
    // Time Base Init
    mTM.Instance = TM36;
    
    mTM.Init.TM_CounterMode = TM_SEPARATE_UP;
    mTM.Init.TM_ClockSource = TM_INTERNAL_CLOCK;
    mTM.Init.TM_Period = 0x00FF;
    mTM.Init.TM_Prescaler = 0;
    mTM.State = MID_TM_STATE_RESET;
    
    MID_TM_OC_Init(&mTM);
    
    // OCx pin initial
    MID_TM_OC_Struct_Init(&sConfig);
    sConfig.OCMode = TM_CH_16bit_OutputCompare;
    sConfig.Pulse = 1020;                       // H-Duty cycle=16/256, L-Duty cycle=32/256
    MID_TM_OC_ConfigChannel(&mTM, &sConfig, MID_TM_Channel0);

    sConfig.Pulse = 2030;                       // H-Duty cycle=32/256, L-Duty cycle=48/256
    MID_TM_OC_ConfigChannel(&mTM, &sConfig, MID_TM_Channel1);

    sConfig.Pulse = 3040;                       // H-Duty cycle=48/256, L-Duty cycle=64/256
    MID_TM_OC_ConfigChannel(&mTM, &sConfig, MID_TM_Channel2);

    // PWM output with DMA access
    MID_TM_8Bx2PWM_Start_IT(&mTM, MID_TM_Channel0, (uint32_t *) &Src0, 8);
    MID_TM_8Bx2PWM_Start_IT(&mTM, MID_TM_Channel1, (uint32_t *) &Src1, 8);
    MID_TM_8Bx2PWM_Start_IT(&mTM, MID_TM_Channel2, (uint32_t *) &Src2, 8);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_8Bx2PWM_Start_IT(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    switch(Channel)
    {
    case MID_TM_Channel0:
    {
        /* Enable the TM Capture/Compare 0 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC0);
        __DRV_TM_ENABLE_ITEA(mTM);
    }
    break;

    case MID_TM_Channel1:
    {
        /* Enable the TM Capture/Compare 1 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC1);
        __DRV_TM_ENABLE_ITEA(mTM);
    }
    break;

    case MID_TM_Channel2:
    {
        /* Enable the TM Capture/Compare 2 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC2);
        __DRV_TM_ENABLE_ITEA(mTM);
    }
    break;

    case MID_TM_Channel3:
    {
        /* Enable the TM Capture/Compare 3 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC3);
        __DRV_TM_ENABLE_ITEA(mTM);
    }
    break;

    default:
        break;
    }

    /* Enable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_8bitx2_PWM);

    // Enable Break Control for PWM mode 
    if(mTM->Instance == TM36) 
    {
        // control TM36_BK_EN & TM36_BK_EN3
        __DRV_TM_ENABLE_BREAK(mTM);
    }


    // __MID_TM_ENABLE(mTM);
    __DRV_TM_ENABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stops the PWM signal generation in interrupt mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_8Bx2PWM_Stop_IT(&mTM, MID_TM_Channel2);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_8Bx2PWM_Stop_IT(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    switch(Channel)
    {
    case MID_TM_Channel0:
    {
        /* Enable the TM Capture/Compare 0 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC0);
    }
    break;

    case MID_TM_Channel1:
    {
        /* Enable the TM Capture/Compare 1 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC1);
    }
    break;

    case MID_TM_Channel2:
    {
        /* Enable the TM Capture/Compare 2 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC2);
    }
    break;

    case MID_TM_Channel3:
    {
        /* Enable the TM Capture/Compare 3 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC3);
    }
    break;

    default:
        break;
    }

    /* Enable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_Disable);

    // Disable Break Control for PWM mode 
    if(mTM->Instance == TM36) 
    {
        // control TM36_BK_EN & TM36_BK_EN3
        if((mTM->Instance->CCMDS.H[0] & TM_ALLCH_PWMMode) == 0x0000)
            __DRV_TM_DISABLE_BREAK(mTM);
    }

    /* Enable the Peripheral */
    __DRV_TM_DISABLE(mTM);

    /* check IT for ITEA */
    if((mTM->Instance->INT.W & 0xFFFFFFFE) == 0)
        __DRV_TM_DISABLE_ITEA(mTM);

    /* Return function status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Starts the TM PWM signal generation in DMA mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @param[in]   pData : The source Buffer address.
 * @param[in]   Length : The length of data to be transferred.
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;
    TM_OC_InitTypeDef sConfig;
    
    uint16_t Src0[] = {0x2525, 0x4010, 0x2525, 0x5080};
    uint16_t Src1[] = {0x2525, 0x3020, 0x2525, 0x4090};
    uint16_t Src2[] = {0x2525, 0x2030, 0x2525, 0x30C0};
    
    // Time Base Init
    mTM.Instance = TM36;
    
    mTM.Init.TM_CounterMode = TM_SEPARATE_UP;
    mTM.Init.TM_ClockSource = TM_INTERNAL_CLOCK;
    mTM.Init.TM_Period = 0x00FF;
    mTM.Init.TM_Prescaler = 0;
    mTM.State = MID_TM_STATE_RESET;
    
    MID_TM_OC_Init(&mTM);
    
    // OCx pin initial
    MID_TM_OC_Struct_Init(&sConfig);
    sConfig.OCMode = TM_CH_16bit_OutputCompare;
    sConfig.Pulse = 1020;                       // H-Duty cycle=16/256, L-Duty cycle=32/256
    MID_TM_PWM_ConfigChannel(&mTM, &sConfig, MID_TM_Channel0);

    sConfig.Pulse = 2030;                       // H-Duty cycle=32/256, L-Duty cycle=48/256
    MID_TM_PWM_ConfigChannel(&mTM, &sConfig, MID_TM_Channel1);

    sConfig.Pulse = 3040;                       // H-Duty cycle=48/256, L-Duty cycle=64/256
    MID_TM_PWM_ConfigChannel(&mTM, &sConfig, MID_TM_Channel2);

    // PWM output with DMA access
    MID_TM_8Bx2PWM_Start_DMA(&mTM, MID_TM_Channel0, (uint32_t *) &Src0, 8);
    MID_TM_8Bx2PWM_Start_DMA(&mTM, MID_TM_Channel1, (uint32_t *) &Src1, 8);
    MID_TM_8Bx2PWM_Start_DMA(&mTM, MID_TM_Channel2, (uint32_t *) &Src2, 8);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_8Bx2PWM_Start_DMA(TM_HandleTypeDef* mTM, uint32_t Channel, uint32_t* pData, uint16_t Length)
{
    if((mTM->State) == (MID_TM_STATE_BUSY))
        return MID_BUSY;
    else if((mTM->State) == (MID_TM_STATE_READY))
    {
        if(((uint32_t)pData == 0U) && (Length > 0U))
            return MID_FAILURE;
        else
            mTM->State = MID_TM_STATE_BUSY;
    }

    switch(Channel)
    {
    case MID_TM_Channel0:
    {
        /* Set the DMA Period elapsed callback */
        mTM->hDMA[TM_DMA_ID_CC0]->XferCpltCallback = &TM_DMADelayPulseCplt;

        /* Set the DMA error callback */
        mTM->hDMA[TM_DMA_ID_CC0]->XferErrorCallback = TM_DMAError ;

        MID_DMA_Start_IT(mTM->hDMA[TM_DMA_ID_CC0], (uint32_t)pData, 0, Length);

        /* Enable the TM Capture/Compare 0 DMA request */
        __DRV_TM_ENABLE_DMA(mTM, TM_DMA_CH0_OC);
    }
    break;

    case MID_TM_Channel1:
    {
        /* Set the DMA Period elapsed callback */
        mTM->hDMA[TM_DMA_ID_CC1]->XferCpltCallback = TM_DMADelayPulseCplt;

        /* Set the DMA error callback */
        mTM->hDMA[TM_DMA_ID_CC1]->XferErrorCallback = TM_DMAError ;

        MID_DMA_Start_IT(mTM->hDMA[TM_DMA_ID_CC1], (uint32_t)pData, 0, Length);

        /* Enable the TM Capture/Compare 1 DMA request */
        __DRV_TM_ENABLE_DMA(mTM, TM_DMA_CH1_OC);
    }
    break;

    case MID_TM_Channel2:
    {
        /* Set the DMA Period elapsed callback */
        mTM->hDMA[TM_DMA_ID_CC2]->XferCpltCallback = TM_DMADelayPulseCplt;

        /* Set the DMA error callback */
        mTM->hDMA[TM_DMA_ID_CC2]->XferErrorCallback = TM_DMAError ;

        MID_DMA_Start_IT(mTM->hDMA[TM_DMA_ID_CC2], (uint32_t)pData, 0, Length);

        /* Enable the TM Capture/Compare 2 DMA request */
        __DRV_TM_ENABLE_DMA(mTM, TM_DMA_CH2_OC);
    }
    break;

    case MID_TM_Channel3:
    {
        // MG32x02z MCU don't support Channel3 for OC output
    }
    break;

    default:
        break;
    }

    /* Enable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_8bitx2_PWM);

    // Enable Break Control for PWM mode 
    if(mTM->Instance == TM36) 
    {
        // control TM36_BK_EN & TM36_BK_EN3
        __DRV_TM_ENABLE_BREAK(mTM);
    }
    
    /* update state */
    mTM->State = MID_TM_STATE_READY;

    /* Enable the Peripheral */
    __DRV_TM_ENABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Stops the TM PWM signal generation in DMA mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @note
 * @par         Example
 * @code
    MID_TM_8Bx2PWM_Stop_DMA(&mTM, MID_TM_Channel1);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_8Bx2PWM_Stop_DMA(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    switch(Channel)
    {
    case MID_TM_Channel0:
    {
        /* Disable the TM Capture/Compare 0 interrupt */
        __DRV_TM_DISABLE_DMA(mTM, TM_DMA_CH0_OC);
    }
    break;

    case MID_TM_Channel1:
    {
        /* Disable the TM Capture/Compare 1 DMA request */
        __DRV_TM_DISABLE_DMA(mTM, TM_DMA_CH1_OC);
    }
    break;

    case MID_TM_Channel2:
    {
        /* Disable the TM Capture/Compare 2 DMA request */
        __DRV_TM_DISABLE_DMA(mTM, TM_DMA_CH2_OC);
    }
    break;

    case MID_TM_Channel3:
    {
        // MG32x02z MCU don't support Channel3 for OC output
    }
    break;

    default:
        break;
    }

    /* Disable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_Disable);

    // Disable Break Control for PWM mode 
    if(mTM->Instance == TM36) 
    {
        // control TM36_BK_EN & TM36_BK_EN3
        if((mTM->Instance->CCMDS.H[0] & TM_ALLCH_PWMMode) == 0x0000)
            __DRV_TM_DISABLE_BREAK(mTM);
    }

    /* Disable the Peripheral */
    __DRV_TM_DISABLE(mTM);

    /* Change the mTM state */
    mTM->State = MID_TM_STATE_READY;

    /* Return function status */
    return MID_SUCCESS;
}

///@}



/**
 * @name    PWM with Dead-Tinme output configuration
 *
 */
///@{
/**
 *******************************************************************************
 * @brief       Initializes the TM PWM TMe Base according to the specified
 *              parameters in the TM_HandleTypeDef and create the associated handle.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM36;

    mTM36.Instance = TM36;
    mTM36.Init.TM_ClockSource = TM_INTERNAL_CLOCK;
    mTM36.Init.TM_CounterMode = TM_CASCADE_UP;
    mTM36.Init.TM_Period = 1023;
    mTM36.Init.TM_Prescaler = 0;
    
    MID_TM_PWM_DTG_Init(&mTM36);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_PWM_DTG_Init(TM_HandleTypeDef* mTM)
{

    if(mTM->State == MID_TM_STATE_RESET)
    {
        /* Allocate lock resource and initialize it */
        mTM->Lock = MID_UnLocked;

        /* Init the low level hardware : GPIO, CLOCK, NVIC and DMA */
        MID_TM_PWM_DTG_MspInit(mTM);
    }

    /* Set the TM state */
    mTM->State= MID_TM_STATE_BUSY;

    /* Init the base time for the Output Compare */
    TM_Base_SetConfig(mTM->Instance,  &mTM->Init);

    /* Initialize the TM state*/
    mTM->State= MID_TM_STATE_READY;

    return MID_SUCCESS;

}


/**
 *******************************************************************************
 * @brief       DeInitializes the TM peripheral
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;

    MID_TM_PWM_DTG_DeInit(&mTM);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_PWM_DTG_DeInit(TM_HandleTypeDef* mTM)
{
    /* Process Lockededed */
    __MID_LOCK(mTM);
    
    mTM->State = MID_TM_STATE_BUSY;

    /* Disable the TM Peripheral Clock */
    __DRV_TM_DISABLE(mTM);

    /* DeInit the low level hardware: GPIO, CLOCK, NVIC and DMA */
    MID_TM_PWM_DTG_MspDeInit(mTM);

    /* Change TM state */
    mTM->State = MID_TM_STATE_RESET;

    /* Release Lock */
    __MID_UNLOCK(mTM);

    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Initializes the TM PWM MSP.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_TM_PWM_DTG_MspInit(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_PWM_DTG_MspInit could be implemented in the user file
     */
}


/**
 *******************************************************************************
 * @brief       DeInitializes TM PWM MSP.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_TM_PWM_DTG_MspDeInit(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_PWM_DTG_MspDeInit could be implemented in the user file
     */
}


/**
 *******************************************************************************
 * @brief       Starts the PWM signal generation.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;               
    TM_OC_InitTypeDef sConfig;
    
    MID_TM_OC_Struct_Init(&sConfig);               // default initial (output state)
    sConfig.OCMode = TM_CH_Disable;
    sConfig.Pulse = 0;                          // Duty cycle = 0%
    MID_TM_PWM_ConfigChannel(&mTM36, &sConfig, MID_TM_Channel0);
    MID_TM_PWM_ConfigChannel(&mTM36, &sConfig, MID_TM_Channel1);
    MID_TM_PWM_ConfigChannel(&mTM36, &sConfig, MID_TM_Channel2);

    MID_TM_PWM_DTG_Start(&mTM, MID_TM_Channel0);    // Channel0 be 16bit PWM output  
    MID_TM_PWM_DTG_Start(&mTM, MID_TM_Channel1);
    MID_TM_PWM_DTG_Start(&mTM, MID_TM_Channel2);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_PWM_DTG_Start(TM_HandleTypeDef* mTM, uint32_t Channel)
{

    /* Enable the Capture compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_16bit_PWM_COMPLEMENT);

    // Enable Break Control for PWM mode 
    if(mTM->Instance == TM36) 
    {
        // control TM36_BK_EN & TM36_BK_EN3
        __DRV_TM_ENABLE_BREAK(mTM);
    }

    /* Enable the Peripheral */
    __DRV_TM_ENABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stops the PWM signal generation.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_PWM_DTG_Stop(&mTM, MID_TM_Channel1);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_PWM_DTG_Stop(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    /* Disable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_Disable);

    // Disable Break Control for PWM mode 
    if(mTM->Instance == TM36) 
    {
        // control TM36_BK_EN & TM36_BK_EN3
        if((mTM->Instance->CCMDS.H[0] & TM_ALLCH_PWMMode) == 0x0000)
            __DRV_TM_DISABLE_BREAK(mTM);
    }

    /* Disable the Peripheral */
    __DRV_TM_DISABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Starts the PWM signal generation in interrupt mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_PWM_DTG_Start_IT(&mTM, MID_TM_Channel1);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_PWM_DTG_Start_IT(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    switch(Channel)
    {
    case MID_TM_Channel0:
    {
        /* Enable the TM Capture/Compare 0 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC0);
        __DRV_TM_ENABLE_ITEA(mTM);
    }
    break;

    case MID_TM_Channel1:
    {
        /* Enable the TM Capture/Compare 1 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC1);
        __DRV_TM_ENABLE_ITEA(mTM);
    }
    break;

    case MID_TM_Channel2:
    {
        /* Enable the TM Capture/Compare 2 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC2);
        __DRV_TM_ENABLE_ITEA(mTM);
    }
    break;

    case MID_TM_Channel3:
    {
        // MG32x02z MCU don't support Channel3 for OC output
        return MID_FAILURE;
    }

    default:
        break;
    }

    /* Enable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_16bit_PWM_COMPLEMENT);

    // Enable Break Control for PWM mode 
    if(mTM->Instance == TM36) 
    {
        // control TM36_BK_EN & TM36_BK_EN3
        __DRV_TM_ENABLE_BREAK(mTM);
    }

    // __MID_TM_ENABLE(mTM);
    __DRV_TM_ENABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stops the PWM signal generation in interrupt mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_PWM_DTG_Stop_IT(&mTM, MID_TM_Channel1);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_PWM_DTG_Stop_IT(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    switch(Channel)
    {
    case MID_TM_Channel0:
    {
        /* Enable the TM Capture/Compare 0 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC0);
    }
    break;

    case MID_TM_Channel1:
    {
        /* Enable the TM Capture/Compare 1 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC1);
    }
    break;

    case MID_TM_Channel2:
    {
        /* Enable the TM Capture/Compare 2 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC2);
    }
    break;

    case MID_TM_Channel3:
    {
        /* update state */
        mTM->State = MID_TM_STATE_READY;
        // MG32x02z MCU don't support Channel3 for OC output
        return MID_FAILURE;
    }

    default:
        break;
    }

    /* Enable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_Disable);

    // Disable Break Control for PWM mode 
    if(mTM->Instance == TM36) 
    {
        // control TM36_BK_EN & TM36_BK_EN3
        if((mTM->Instance->CCMDS.H[0] & TM_ALLCH_PWMMode) == 0x0000)
            __DRV_TM_DISABLE_BREAK(mTM);
    }

    /* Enable the Peripheral */
    __DRV_TM_DISABLE(mTM);

    /* check IT for ITEA */
    if((mTM->Instance->INT.W & 0xFFFFFFFE) == 0)
        __DRV_TM_DISABLE_ITEA(mTM);

    /* Return function status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Starts the TM PWM signal generation in DMA mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 * @param[in]   pData : The source Buffer address.
 * @param[in]   Length : The length of data to be transferred.
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;
    TM_OC_InitTypeDef sConfig;
    
    uint16_t Src0[] = {0x2525, 0x4000, 0x2525, 0x5000};
    uint16_t Src1[] = {0x2525, 0x3000, 0x2525, 0x4000};
    uint16_t Src2[] = {0x2525, 0x2000, 0x2525, 0x3000};
    
    // Time Base Init
    mTM.Instance = TM36;
    
    mTM.Init.TM_CounterMode = TM_SEPARATE_UP;
    mTM.Init.TM_ClockSource = TM_INTERNAL_CLOCK;
    mTM.Init.TM_Period = 0x6000;
    mTM.Init.TM_Prescaler = 65535;
    mTM.State = MID_TM_STATE_RESET;
    
    MID_TM_OC_Init(&mTM);
    
    // OCx pin initial
    MID_TM_OC_Struct_Init(&sConfig);
    sConfig.OCMode = TM_CH_16bit_OutputCompare;
    sConfig.Pulse = 1000;
    MID_TM_OC_ConfigChannel(&mTM, &sConfig, MID_TM_Channel0);

    sConfig.Pulse = 2000;
    MID_TM_OC_ConfigChannel(&mTM, &sConfig, MID_TM_Channel1);

    sConfig.Pulse = 3000;
    MID_TM_OC_ConfigChannel(&mTM, &sConfig, MID_TM_Channel2);

    // PWM output with DMA access
    MID_TM_PWM_DTG_Start_DMA(&mTM, MID_TM_Channel0, (uint32_t *) &Src0, 8);
    MID_TM_PWM_DTG_Start_DMA(&mTM, MID_TM_Channel1, (uint32_t *) &Src1, 8);
    MID_TM_PWM_DTG_Start_DMA(&mTM, MID_TM_Channel2, (uint32_t *) &Src2, 8);
    
    
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_PWM_DTG_Start_DMA(TM_HandleTypeDef* mTM, uint32_t Channel, uint32_t* pData, uint16_t Length)
{
    if((mTM->State) == (MID_TM_STATE_BUSY))
        return MID_BUSY;
    else if((mTM->State) == (MID_TM_STATE_READY))
    {
        if(((uint32_t)pData == 0U) && (Length > 0U))
            return MID_FAILURE;
        else
            mTM->State = MID_TM_STATE_BUSY;
    }

    switch(Channel)
    {
    case MID_TM_Channel0:
    {
        /* Set the DMA Period elapsed callback */
        mTM->hDMA[TM_DMA_ID_CC0]->XferCpltCallback = &TM_DMADelayPulseCplt;

        /* Set the DMA error callback */
        mTM->hDMA[TM_DMA_ID_CC0]->XferErrorCallback = TM_DMAError ;

        MID_DMA_Start_IT(mTM->hDMA[TM_DMA_ID_CC0], (uint32_t)pData, 0, Length);

        /* Enable the TM Capture/Compare 0 DMA request */
        __DRV_TM_ENABLE_DMA(mTM, TM_DMA_CH0_OC);
    }
    break;

    case MID_TM_Channel1:
    {

        /* Set the DMA Period elapsed callback */
        mTM->hDMA[TM_DMA_ID_CC1]->XferCpltCallback = TM_DMADelayPulseCplt;

        /* Set the DMA error callback */
        mTM->hDMA[TM_DMA_ID_CC1]->XferErrorCallback = TM_DMAError ;

        MID_DMA_Start_IT(mTM->hDMA[TM_DMA_ID_CC1], (uint32_t)pData, 0, Length);

        /* Enable the TM Capture/Compare 1 DMA request */
        __DRV_TM_ENABLE_DMA(mTM, TM_DMA_CH1_OC);
    }
    break;

    case MID_TM_Channel2:
    {
        /* Set the DMA Period elapsed callback */
        mTM->hDMA[TM_DMA_ID_CC2]->XferCpltCallback = TM_DMADelayPulseCplt;

        /* Set the DMA error callback */
        mTM->hDMA[TM_DMA_ID_CC2]->XferErrorCallback = TM_DMAError ;

        MID_DMA_Start_IT(mTM->hDMA[TM_DMA_ID_CC2], (uint32_t)pData, 0, Length);

        /* Enable the TM Capture/Compare 2 DMA request */
        __DRV_TM_ENABLE_DMA(mTM, TM_DMA_CH2_OC);
    }
    break;

    case MID_TM_Channel3:
    {
        /* update state */
        mTM->State = MID_TM_STATE_READY;
        // MG32x02z MCU don't support Channel3 for OC output
        return MID_FAILURE;
    }

    default:
        break;
    }

    /* Enable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_16bit_PWM_COMPLEMENT);

    // Enable Break Control for PWM mode 
    if(mTM->Instance == TM36) 
    {
        // control TM36_BK_EN & TM36_BK_EN3
        __DRV_TM_ENABLE_BREAK(mTM);
    }
    
    /* update state */
    mTM->State = MID_TM_STATE_READY;

    /* Enable the Peripheral */
    __DRV_TM_ENABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Stops the TM PWM signal generation in DMA mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 * @note
 * @par         Example
 * @code
    MID_TM_PWM_DTG_Stop_DMA(&mTM, MID_TM_Channel0);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_PWM_DTG_Stop_DMA(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    switch(Channel)
    {
    case MID_TM_Channel0:
    {
        /* Disable the TM Capture/Compare 0 interrupt */
        __DRV_TM_DISABLE_DMA(mTM, TM_DMA_CH0_OC);
    }
    break;

    case MID_TM_Channel1:
    {
        /* Disable the TM Capture/Compare 1 DMA request */
        __DRV_TM_DISABLE_DMA(mTM, TM_DMA_CH1_OC);
    }
    break;

    case MID_TM_Channel2:
    {
        /* Disable the TM Capture/Compare 2 DMA request */
        __DRV_TM_DISABLE_DMA(mTM, TM_DMA_CH2_OC);
    }
    break;

    case MID_TM_Channel3:
    {
        // MG32x02z MCU don't support Channel3 for OC output
        
        /* Change the mTM state */
        mTM->State = MID_TM_STATE_READY;
        // MG32x02z MCU don't support Channel3 for OC output
        return MID_FAILURE;
    }

    default:
        break;
    }

    /* Disable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_Disable);

    // Disable Break Control for PWM mode 
    if(mTM->Instance == TM36) 
    {
        // control TM36_BK_EN & TM36_BK_EN3
        if((mTM->Instance->CCMDS.H[0] & TM_ALLCH_PWMMode) == 0x0000)
            __DRV_TM_DISABLE_BREAK(mTM);
    }

    /* Disable the Peripheral */
    __DRV_TM_DISABLE(mTM);

    /* Change the mTM state */
    mTM->State = MID_TM_STATE_READY;

    /* Return function status */
    return MID_SUCCESS;
}

///@}





/**
 * @name    8Bitx2 PWM with Dead-Tinme output configuration
 *
 */
///@{
/**
 *******************************************************************************
 * @brief       Initializes the TM PWM TMe Base according to the specified
 *              parameters in the TM_HandleTypeDef and create the associated handle.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM36;

    mTM36.Instance = TM36;
    mTM36.Init.TM_ClockSource = TM_INTERNAL_CLOCK;
    mTM36.Init.TM_CounterMode = TM_CASCADE_UP;
    mTM36.Init.TM_Period = 0x00FF;
    mTM36.Init.TM_Prescaler = 0;
    
    MID_TM_8Bx2PWM_DTG_Init(&mTM36);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_8Bx2PWM_DTG_Init(TM_HandleTypeDef* mTM)
{

    if(mTM->State == MID_TM_STATE_RESET)
    {
        /* Allocate lock resource and initialize it */
        mTM->Lock = MID_UnLocked;

        /* Init the low level hardware : GPIO, CLOCK, NVIC and DMA */
        MID_TM_8Bx2PWM_DTG_MspInit(mTM);
    }

    /* Set the TM state */
    mTM->State= MID_TM_STATE_BUSY;

    /* Init the base time for the Output Compare */
    TM_Base_SetConfig(mTM->Instance,  &mTM->Init);

    /* Initialize the TM state*/
    mTM->State= MID_TM_STATE_READY;

    return MID_SUCCESS;

}


/**
 *******************************************************************************
 * @brief       DeInitializes the TM peripheral
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_8Bx2PWM_DTG_DeInit(&mTM);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_8Bx2PWM_DTG_DeInit(TM_HandleTypeDef* mTM)
{
    mTM->State = MID_TM_STATE_BUSY;

    /* Disable the TM Peripheral Clock */
    __DRV_TM_DISABLE(mTM);

    /* DeInit the low level hardware: GPIO, CLOCK, NVIC and DMA */
    MID_TM_8Bx2PWM_DTG_MspDeInit(mTM);

    /* Change TM state */
    mTM->State = MID_TM_STATE_RESET;

    /* Release Lock */
    __MID_UNLOCK(mTM);

    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Initializes the TM PWM MSP.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 *******************************************************************************
 */
__weak void MID_TM_8Bx2PWM_DTG_MspInit(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_8Bx2PWM_DTG_MspInit could be implemented in the user file
     */
}


/**
 *******************************************************************************
 * @brief       DeInitializes TM PWM MSP.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 *******************************************************************************
 */
__weak void MID_TM_8Bx2PWM_DTG_MspDeInit(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_8Bx2PWM_DTG_MspDeInit could be implemented in the user file
     */
}


/**
 *******************************************************************************
 * @brief       Starts the PWM signal generation.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;               
    TM_OC_InitTypeDef sConfig;
    
    MID_TM_OC_Struct_Init(&sConfig);               // default initial (output state)
    sConfig.OCMode = TM_CH_Disable;
    sConfig.Pulse = 0;                          // Duty cycle = 0%, 0%
    MID_TM_PWM_ConfigChannel(&mTM36, &sConfig, MID_TM_Channel0);
    MID_TM_PWM_ConfigChannel(&mTM36, &sConfig, MID_TM_Channel1);
    MID_TM_PWM_ConfigChannel(&mTM36, &sConfig, MID_TM_Channel2);

    MID_TM_8Bx2PWM_Start(&mTM, MID_TM_Channel0);    // Channel0 be 8bit x 2 PWM output  
    MID_TM_8Bx2PWM_Start(&mTM, MID_TM_Channel1);
    MID_TM_8Bx2PWM_Start(&mTM, MID_TM_Channel2);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_8Bx2PWM_DTG_Start(TM_HandleTypeDef* mTM, uint32_t Channel)
{

    /* Enable the Capture compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_8bitx2_PWM_COMPLEMENT);

    // Enable Break Control for PWM mode 
    if(mTM->Instance == TM36) 
    {
        // control TM36_BK_EN & TM36_BK_EN3
        __DRV_TM_ENABLE_BREAK(mTM);
    }

    /* Enable the Peripheral */
    __DRV_TM_ENABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stops the PWM signal generation.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_8Bx2PWM_DTG_Stop(&mTM, MID_TM_Channel1);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_8Bx2PWM_DTG_Stop(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    /* Disable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_Disable);

    // Disable Break Control for PWM mode 
    if(mTM->Instance == TM36) 
    {
        // control TM36_BK_EN & TM36_BK_EN3
        if((mTM->Instance->CCMDS.H[0] & TM_ALLCH_PWMMode) == 0x0000)
            __DRV_TM_DISABLE_BREAK(mTM);
    }

    /* Disable the Peripheral */
    __DRV_TM_DISABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Starts the PWM signal generation in interrupt mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;
    TM_OC_InitTypeDef sConfig;
    
    // Time Base Init
    mTM.Instance = TM36;
    
    mTM.Init.TM_CounterMode = TM_SEPARATE_UP;
    mTM.Init.TM_ClockSource = TM_INTERNAL_CLOCK;
    mTM.Init.TM_Period = 0x00FF;
    mTM.Init.TM_Prescaler = 0;
    mTM.State = MID_TM_STATE_RESET;
    
    MID_TM_OC_Init(&mTM);
    
    // OCx pin initial
    MID_TM_OC_Struct_Init(&sConfig);
    sConfig.OCMode = TM_CH_16bit_OutputCompare;
    sConfig.Pulse = 1020;                       // H-Duty cycle=16/256, L-Duty cycle=32/256
    MID_TM_OC_ConfigChannel(&mTM, &sConfig, MID_TM_Channel0);

    sConfig.Pulse = 2030;                       // H-Duty cycle=32/256, L-Duty cycle=48/256
    MID_TM_OC_ConfigChannel(&mTM, &sConfig, MID_TM_Channel1);

    sConfig.Pulse = 3040;                       // H-Duty cycle=48/256, L-Duty cycle=64/256
    MID_TM_OC_ConfigChannel(&mTM, &sConfig, MID_TM_Channel2);

    // PWM output with DMA access
    MID_TM_8Bx2PWM_Start_IT(&mTM, MID_TM_Channel0, (uint32_t *) &Src0, 8);
    MID_TM_8Bx2PWM_Start_IT(&mTM, MID_TM_Channel1, (uint32_t *) &Src1, 8);
    MID_TM_8Bx2PWM_Start_IT(&mTM, MID_TM_Channel2, (uint32_t *) &Src2, 8);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_8Bx2PWM_DTG_Start_IT(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    switch(Channel)
    {
    case MID_TM_Channel0:
    {
        /* Enable the TM Capture/Compare 0 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC0);
        __DRV_TM_ENABLE_ITEA(mTM);
    }
    break;

    case MID_TM_Channel1:
    {
        /* Enable the TM Capture/Compare 1 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC1);
        __DRV_TM_ENABLE_ITEA(mTM);
    }
    break;

    case MID_TM_Channel2:
    {
        /* Enable the TM Capture/Compare 2 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC2);
        __DRV_TM_ENABLE_ITEA(mTM);
    }
    break;

    case MID_TM_Channel3:
    {
        // MG32x02z MCU don't support Channel3 for OC output
        return MID_FAILURE;
    }

    default:
        break;
    }

    /* Enable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_16bit_PWM_COMPLEMENT);

    // Enable Break Control for PWM mode 
    if(mTM->Instance == TM36) 
    {
        // control TM36_BK_EN & TM36_BK_EN3
        __DRV_TM_ENABLE_BREAK(mTM);
    }

    // __MID_TM_ENABLE(mTM);
    __DRV_TM_ENABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stops the PWM signal generation in interrupt mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_8Bx2PWM_DTG_Stop_IT(&mTM, MID_TM_Channel2);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_8Bx2PWM_DTG_Stop_IT(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    switch(Channel)
    {
    case MID_TM_Channel0:
    {
        /* Enable the TM Capture/Compare 0 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC0);
    }
    break;

    case MID_TM_Channel1:
    {
        /* Enable the TM Capture/Compare 1 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC1);
    }
    break;

    case MID_TM_Channel2:
    {
        /* Enable the TM Capture/Compare 2 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC2);
    }
    break;

    case MID_TM_Channel3:
    {
        // MG32x02z MCU don't support Channel3 for OC output
        return MID_FAILURE;
    }

    default:
        break;
    }

    /* Enable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_Disable);

    // Disable Break Control for PWM mode 
    if(mTM->Instance == TM36) 
    {
        // control TM36_BK_EN & TM36_BK_EN3
        if((mTM->Instance->CCMDS.H[0] & TM_ALLCH_PWMMode) == 0x0000)
            __DRV_TM_DISABLE_BREAK(mTM);
    }

    /* Enable the Peripheral */
    __DRV_TM_DISABLE(mTM);

    /* check IT for ITEA */
    if((mTM->Instance->INT.W & 0xFFFFFFFE) == 0)
        __DRV_TM_DISABLE_ITEA(mTM);

    /* Return function status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Starts the TM PWM signal generation in DMA mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 * @param[in]   pData : The source Buffer address.
 * @param[in]   Length : The length of data to be transferred.
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;
    TM_OC_InitTypeDef sConfig;
    
    uint16_t Src0[] = {0x2525, 0x4010, 0x2525, 0x5080};
    uint16_t Src1[] = {0x2525, 0x3020, 0x2525, 0x4090};
    uint16_t Src2[] = {0x2525, 0x2030, 0x2525, 0x30C0};
    
    // Time Base Init
    mTM.Instance = TM36;
    
    mTM.Init.TM_CounterMode = TM_SEPARATE_UP;
    mTM.Init.TM_ClockSource = TM_INTERNAL_CLOCK;
    mTM.Init.TM_Period = 0x00FF;
    mTM.Init.TM_Prescaler = 0;
    mTM.State = MID_TM_STATE_RESET;
    
    MID_TM_OC_Init(&mTM);
    
    // OCx pin initial
    MID_TM_OC_Struct_Init(&sConfig);
    sConfig.OCMode = TM_CH_16bit_OutputCompare;
    sConfig.Pulse = 1020;                       // H-Duty cycle=16/256, L-Duty cycle=32/256
    MID_TM_OC_ConfigChannel(&mTM, &sConfig, MID_TM_Channel0);

    sConfig.Pulse = 2030;                       // H-Duty cycle=32/256, L-Duty cycle=48/256
    MID_TM_OC_ConfigChannel(&mTM, &sConfig, MID_TM_Channel1);

    sConfig.Pulse = 3040;                       // H-Duty cycle=48/256, L-Duty cycle=64/256
    MID_TM_OC_ConfigChannel(&mTM, &sConfig, MID_TM_Channel2);

    // PWM output with DMA access
    MID_TM_8Bx2PWM_Start_DMA(&mTM, MID_TM_Channel0, (uint32_t *) &Src0, 8);
    MID_TM_8Bx2PWM_Start_DMA(&mTM, MID_TM_Channel1, (uint32_t *) &Src1, 8);
    MID_TM_8Bx2PWM_Start_DMA(&mTM, MID_TM_Channel2, (uint32_t *) &Src2, 8);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_8Bx2PWM_DTG_Start_DMA(TM_HandleTypeDef* mTM, uint32_t Channel, uint32_t* pData, uint16_t Length)
{
    if((mTM->State) == (MID_TM_STATE_BUSY))
        return MID_BUSY;
    else if((mTM->State) == (MID_TM_STATE_READY))
    {
        if(((uint32_t)pData == 0U) && (Length > 0U))
            return MID_FAILURE;
        else
            mTM->State = MID_TM_STATE_BUSY;
    }

    switch(Channel)
    {
    case MID_TM_Channel0:
    {
        /* Set the DMA Period elapsed callback */
        mTM->hDMA[TM_DMA_ID_CC0]->XferCpltCallback = &TM_DMADelayPulseCplt;

        /* Set the DMA error callback */
        mTM->hDMA[TM_DMA_ID_CC0]->XferErrorCallback = TM_DMAError ;

        MID_DMA_Start_IT(mTM->hDMA[TM_DMA_ID_CC0], (uint32_t)pData, 0, Length);

        /* Enable the TM Capture/Compare 0 DMA request */
        __DRV_TM_ENABLE_DMA(mTM, TM_DMA_CH0_OC);
    }
    break;

    case MID_TM_Channel1:
    {
        /* Set the DMA Period elapsed callback */
        mTM->hDMA[TM_DMA_ID_CC1]->XferCpltCallback = TM_DMADelayPulseCplt;

        /* Set the DMA error callback */
        mTM->hDMA[TM_DMA_ID_CC1]->XferErrorCallback = TM_DMAError ;

        MID_DMA_Start_IT(mTM->hDMA[TM_DMA_ID_CC1], (uint32_t)pData, 0, Length);

        /* Enable the TM Capture/Compare 1 DMA request */
        __DRV_TM_ENABLE_DMA(mTM, TM_DMA_CH1_OC);
    }
    break;

    case MID_TM_Channel2:
    {
        /* Set the DMA Period elapsed callback */
        mTM->hDMA[TM_DMA_ID_CC2]->XferCpltCallback = TM_DMADelayPulseCplt;

        /* Set the DMA error callback */
        mTM->hDMA[TM_DMA_ID_CC2]->XferErrorCallback = TM_DMAError ;
        
        MID_DMA_Start_IT(mTM->hDMA[TM_DMA_ID_CC2], (uint32_t)pData, 0, Length);

        /* Enable the TM Capture/Compare 2 DMA request */
        __DRV_TM_ENABLE_DMA(mTM, TM_DMA_CH2_OC);
    }
    break;

    case MID_TM_Channel3:
    {
        // MG32x02z MCU don't support Channel3 for OC output
        mTM->State = MID_TM_STATE_READY;
        return MID_FAILURE;
    }

    default:
        break;
    }

    /* Enable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_8bitx2_PWM_COMPLEMENT);

    // Enable Break Control for PWM mode 
    if(mTM->Instance == TM36) 
    {
        // control TM36_BK_EN & TM36_BK_EN3
        __DRV_TM_ENABLE_BREAK(mTM);
    }
    
    /* update state */
    mTM->State = MID_TM_STATE_READY;

    /* Enable the Peripheral */
    __DRV_TM_ENABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Stops the TM PWM signal generation in DMA mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 * @note
 * @par         Example
 * @code
    MID_TM_8Bx2PWM_DTG_Stop_DMA(&mTM, MID_TM_Channel0);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_8Bx2PWM_DTG_Stop_DMA(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    switch(Channel)
    {
    case MID_TM_Channel0:
    {
        /* Disable the TM Capture/Compare 0 interrupt */
        __DRV_TM_DISABLE_DMA(mTM, TM_DMA_CH0_OC);
    }
    break;

    case MID_TM_Channel1:
    {
        /* Disable the TM Capture/Compare 1 DMA request */
        __DRV_TM_DISABLE_DMA(mTM, TM_DMA_CH1_OC);
    }
    break;

    case MID_TM_Channel2:
    {
        /* Disable the TM Capture/Compare 2 DMA request */
        __DRV_TM_DISABLE_DMA(mTM, TM_DMA_CH2_OC);
    }
    break;

    case MID_TM_Channel3:
    {
        // MG32x02z MCU don't support Channel3 for OC output
        mTM->State = MID_TM_STATE_READY;
        return MID_FAILURE;
    }

    default:
        break;
    }

    /* Disable the Output compare channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_Disable);

    // Disable Break Control for PWM mode 
    if(mTM->Instance == TM36) 
    {
        // control TM36_BK_EN & TM36_BK_EN3
        if((mTM->Instance->CCMDS.H[0] & TM_ALLCH_PWMMode) == 0x0000)
            __DRV_TM_DISABLE_BREAK(mTM);
    }

    /* Disable the Peripheral */
    __DRV_TM_DISABLE(mTM);

    /* Change the mTM state */
    mTM->State = MID_TM_STATE_READY;

    /* Return function status */
    return MID_SUCCESS;
}

///@}





/**
 * @name    Time Input Capture functions
 *
 */
///@{
/**
 *******************************************************************************
 * @brief       Initializes the TM Input Capture TMe base according to the
 *              specified parameters in the TM_HandleTypeDef and create the
 *              associated handle.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM36;

    mTM36.Instance = TM36;
    mTM36.Init.TM_ClockSource = TM_INTERNAL_CLOCK;
    mTM36.Init.TM_CounterMode = TM_CASCADE_UP;
    mTM36.Init.TM_Period = 0xFFFF;
    mTM36.Init.TM_Prescaler = 0;
    
    MID_TM_IC_Init(&mTM36);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_IC_Init(TM_HandleTypeDef* mTM)
{
    /* Check the TM handle allocation */
    if(mTM == 0)
        return MID_FAILURE;

    if(mTM->State == MID_TM_STATE_RESET)
    {
        /* Allocate lock resource and initialize it */
        mTM->Lock = MID_UnLocked;

        /* Init the low level hardware : GPIO, CLOCK, NVIC and DMA */
        MID_TM_IC_MspInit(mTM);
    }

    /* Set the TM state */
    mTM->State= MID_TM_STATE_BUSY;

    /* Init the base time for the input capture */
    TM_Base_SetConfig(mTM->Instance, &mTM->Init);

    /* Initialize the TM state*/
    mTM->State= MID_TM_STATE_READY;

    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       DeInitializes the TM peripheral.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_PWM_Init(&mTM);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_IC_DeInit(TM_HandleTypeDef* mTM)
{
    mTM->State = MID_TM_STATE_BUSY;

    /* Disable the TM Peripheral Clock */
    __DRV_TM_DISABLE(mTM);

    /* DeInit the low level hardware: GPIO, CLOCK, NVIC and DMA */
    MID_TM_IC_MspDeInit(mTM);

    /* Change TM state */
    mTM->State = MID_TM_STATE_RESET;

    /* Release Lock */
    __MID_UNLOCK(mTM);

    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Initializes the TM Input Capture MSP.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 *******************************************************************************
 */
__weak void MID_TM_IC_MspInit(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_IC_MspInit could be implemented in the user file
     */
}


/**
 *******************************************************************************
 * @brief       DeInitializes TM Input Capture MSP.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 *******************************************************************************
 */
__weak void MID_TM_IC_MspDeInit(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_IC_MspDeInit could be implemented in the user file
     */
}


/**
 *******************************************************************************
 * @brief       Starts the TM Input Capture measurement.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    iConfig.ICSelection = MID_TM_INPUTMUX_PIN;        
    iConfig.ICPolarity  = TM_ICPOLARITY_DUALEDGE;
    iConfig.ICDataMode  = MID_TM_IC_KEEPDATA;
    MID_TM_IC_ConfigChannel(&mTM36, &iConfig, MID_TM_Channel3);

    MID_TM_IC_Start(&mTM36, MID_TM_Channel3);   
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_IC_Start(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    /* Enable the Input Capture channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_InputCapture);

    /* Enable the Peripheral */
    __DRV_TM_ENABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stops the TM Input Capture measurement.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_IC_Stop(&mTM, MID_TM_Channel1);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_IC_Stop(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    /* Disable the Input Capture channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_Disable);

    /* Disable the Peripheral */
    __DRV_TM_DISABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Starts the TM Input Capture measurement in interrupt mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    iConfig.ICSelection = MID_TM_INPUTMUX_PIN;
    iConfig.ICPolarity  = TM_ICPOLARITY_DISABLE;
    iConfig.ICDataMode  = MID_TM_IC_OVERWRITTEN;

    MID_TM_IC_ConfigChannel(&mTM36, &iConfig, MID_TM_Channel0);
    MID_TM_IC_ConfigChannel(&mTM36, &iConfig, MID_TM_Channel1);
    MID_TM_IC_ConfigChannel(&mTM36, &iConfig, MID_TM_Channel2);
    
    iConfig.ICSelection = MID_TM_INPUTMUX_LINE3;        // TM36_XOR trigger signal connect IC channel
    iConfig.ICPolarity = TM_ICPOLARITY_DUALEDGE;

    MID_TM_IC_ConfigChannel(&mTM36, &iConfig, MID_TM_Channel3);
    MID_TM_IC_Start_IT(&mTM36, MID_TM_Channel3);   
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_IC_Start_IT(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    switch(Channel)
    {
    case MID_TM_Channel0:
    {
        /* Enable the TM Capture/Compare 0 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC0);
        __DRV_TM_ENABLE_ITEA(mTM);
    }
    break;

    case MID_TM_Channel1:
    {
        /* Enable the TM Capture/Compare 1 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC1);
        __DRV_TM_ENABLE_ITEA(mTM);
    }
    break;

    case MID_TM_Channel2:
    {
        /* Enable the TM Capture/Compare 2 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC2);
        __DRV_TM_ENABLE_ITEA(mTM);
    }
    break;

    case MID_TM_Channel3:
    {
        /* Enable the TM Capture/Compare 3 interrupt */
        __DRV_TM_ENABLE_IT(mTM, TM_IT_CC3);
        __DRV_TM_ENABLE_ITEA(mTM);
    }
    break;

    default:
        break;
    }
    /* Enable the Input Capture channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_InputCapture);

    /* Enable the Peripheral */
    __DRV_TM_ENABLE(mTM);
    __DRV_TM_ENABLE_ITEA(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stops the TM Input Capture measurement in interrupt mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_IC_Stop_IT(&mTM, MID_TM_Channel3);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_IC_Stop_IT(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    switch(Channel)
    {
    case MID_TM_Channel0:
    {
        /* Disable the TM Capture/Compare 0 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC0);
    }
    break;

    case MID_TM_Channel1:
    {
        /* Disable the TM Capture/Compare 1 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC1);
    }
    break;

    case MID_TM_Channel2:
    {
        /* Disable the TM Capture/Compare 2 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC2);
    }
    break;

    case MID_TM_Channel3:
    {
        /* Disable the TM Capture/Compare 3 interrupt */
        __DRV_TM_DISABLE_IT(mTM, TM_IT_CC3);
    }
    break;

    default:
        break;
    }

    /* Disable the Input Capture channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_Disable);

    /* Disable the Peripheral */
    __DRV_TM_DISABLE(mTM);

    /* check IT for ITEA */
    if((mTM->Instance->INT.W & 0xFFFFFFFE) == 0)
        __DRV_TM_DISABLE_ITEA(mTM);


    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Starts the TM Input Capture measurement in DMA mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @param[in]   pData : The source Buffer address.
 * @param[in]   Length : The length of data to be transferred.
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_IC_Start_DMA(&mTM, MID_TM_Channel3, &Dest, 10);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_IC_Start_DMA(TM_HandleTypeDef* mTM, uint32_t Channel, uint32_t* pData, uint16_t Length)
{
    if((mTM->State) == (MID_TM_STATE_BUSY))
        return MID_BUSY;
    else if((mTM->State) == (MID_TM_STATE_READY))
    {
        if((pData == 0U) && (Length > 0U))
            return MID_FAILURE;
        else
            mTM->State = MID_TM_STATE_BUSY;
    }

    switch(Channel)
    {
    case MID_TM_Channel3:
    {
        /* Set the DMA Period elapsed callback */
        mTM->hDMA[TM_DMA_ID_CC3]->XferCpltCallback = TM_DMACaptureCplt;

        /* Set the DMA error callback */
        mTM->hDMA[TM_DMA_ID_CC3]->XferErrorCallback = TM_DMAError ;

        MID_DMA_Start_IT(mTM->hDMA[TM_DMA_ID_CC3], 0, (uint32_t) pData, Length);

        /* Enable the TM Capture/Compare 3  DMA request */
        __DRV_TM_ENABLE_DMA(mTM, TM_DMA_CH3_IC);
    }
    break;

    default:
        /* Change TM state */
        mTM->State = MID_TM_STATE_READY;
        return MID_FAILURE;
    }

    /* Enable the Input Capture channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_InputCapture);

    /* Enable the Peripheral */
    __DRV_TM_ENABLE(mTM);

    /* Change TM state */
    mTM->State = MID_TM_STATE_READY;

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stops the TM Input Capture measurement in DMA mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_IC_Stop_DMA(&mTM, MID_TM_Channel3);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_IC_Stop_DMA(TM_HandleTypeDef* mTM, uint32_t Channel)
{
    switch(Channel)
    {
    case MID_TM_Channel3:
    {
        /* Disable the TM Capture/Compare 3  DMA request */
        __DRV_TM_DISABLE_DMA(mTM, TM_DMA_CH3_IC);
    }
    break;

    default:
        /* Change TM state */
        mTM->State = MID_TM_STATE_READY;
        return MID_FAILURE;
    }

    /* Disable the Input Capture channel */
    TM_CCxChannelCmd(mTM->Instance, Channel, TM_CH_Disable);

    /* Disable the Peripheral */
    __DRV_TM_DISABLE(mTM);

    /* Change the mTM state */
    mTM->State = MID_TM_STATE_READY;

    /* Return function status */
    return MID_SUCCESS;
}

///@}


/**
 * @name  Time One Pulse functions
 *
 */
///@{
#if defined(MG32_3RD)
/**
 *******************************************************************************
 * @brief       Initializes the TM One Pulse TMe Base according to the specified
 *              parameters in the TM_HandleTypeDef and create the associated handle.
 *              User can control OC/PWM times by this function with every trigger event.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   sRCNTConfig : pointer to a TM_RCNTConfigTypeDef
 *  @arg\b      RCNTClkSrc : Specifies the timer's RCNT clock source event.
 *  @arg\b      RCNTCounter : Specifies the RCNT counter value.
 *  @arg\b      RCNTReload : Specifies the RCNT reload value.
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_RCNTConfigTypeDef    TMRCNT;
 
    TMRCNT.RCNTClkSrc   = TM_RCNT_MAIN_EVENT;
    TMRCNT.RCNTCounter  = 9;
    TMRCNT.RCNTReload   = 9;
 
    MID_TM_OnePulse_Init(&mTM, &TMRCNT);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_OnePulse_Init(TM_HandleTypeDef *mTM, TM_RCNTConfigTypeDef* sRCNTConfig)
{
    /* Check input state */
    __MID_LOCK(mTM);
    
    // check mTM or TM2x, TM3x
    if(mTM == 0)
    {
        return MID_FAILURE;
    }
    if((mTM->Instance != TM20) && (mTM->Instance != TM26) && (mTM->Instance != TM36))
    {
        /* Release Lock */
        __MID_UNLOCK(mTM);

        return MID_FAILURE;
    }

    //
    if(mTM->State == MID_TM_STATE_RESET)
    {
        /* Allocate lock resource and initialize it */
        __MID_UNLOCK(mTM);
      
        /* Init the low level hardware : GPIO, CLOCK, NVIC */
        MID_TM_OnePulse_MspInit(mTM);
    }

    /* Set the TM state */
    mTM->State= MID_TM_STATE_BUSY;
    
    /* Set RCNT clock source */
    mTM->Instance->CLK.W &= ~(TM_CLK_RC_CKS_mask_w);
    mTM->Instance->CLK.W |= (sRCNTConfig->RCNTClkSrc & ~(TM_CLK_RC_CKS_mask_w));
    
    /* Set RCNT clock source from CKO */
    if (sRCNTConfig->RCNTClkSrc != TM_RCNT_MAIN_EVENT)
    {   
        //
        mTM->Instance->CKO.W &= ~(TM_CKO_CKO_SEL_mask_w);
        mTM->Instance->CLK.W |= (sRCNTConfig->RCNTClkSrc & ~(TM_CKO_CKO_SEL_mask_w));
    }
    
    /* Cancel ASTOP + ACLEAN_EN function  */
    mTM->Instance->CR0.W &= ~(TM_OPMODE_REPETITIVE);                
    
    /* Config RCNT  */
    mTM->Instance->RCNT.W = (uint32_t) (sRCNTConfig->RCNTCounter & 0x000000FF) | 
                            (uint32_t) ((sRCNTConfig->RCNTReload & 0x000000FF) << 16);
    
    /* Initialize the TM state*/
    mTM->State= MID_TM_STATE_READY;

    /* Release Lock */
    __MID_UNLOCK(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       DeInitializes the TM One Pulse.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_OnePulse_DeInit(&mTM);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_OnePulse_DeInit(TM_HandleTypeDef *mTM)
{
    /* Check input state */
    __MID_LOCK(mTM);
    mTM->State = MID_TM_STATE_BUSY;

    /* Disable the TM Peripheral Clock */
    __DRV_TM_DISABLE(mTM);
    mTM->Instance->CR0.W &= ~(TM_CR0_RC_STP_enable_w | TM_CR0_RC_EN_enable_w);

    /* DeInit the low level hardware: GPIO, CLOCK, NVIC */
    MID_TM_OnePulse_MspDeInit(mTM);

    /* Change TM state */
    mTM->State = MID_TM_STATE_RESET;

    /* Release Lock */
    __MID_UNLOCK(mTM);

    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Initializes the TM One Pulse MSP.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_TM_OnePulse_MspInit(TM_HandleTypeDef *mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
            the MID_TM_OnePulse_MspInit could be implemented in the user file
    */
}


/**
 *******************************************************************************
 * @brief       DeInitializes TM One Pulse MSP.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_TM_OnePulse_MspDeInit(TM_HandleTypeDef *mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
            the MID_TM_OnePulse_MspDeInit could be implemented in the user file
    */
}


/**
 *******************************************************************************
 * @brief       Starts the TM One Pulse signal generation with PWM output.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @note        Caution: The Timer must active with TM slave mode. 
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;

    MID_TM_OnePulse_Start(&mTM);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_OnePulse_Start(TM_HandleTypeDef *mTM)
{
    /* Main Timer/Counter stop enable when repetition counter underflow.  */
    mTM->Instance->CR0.W |= (TM_CR0_RC_STP_enable_w | TM_CR0_RC_EN_enable_w);
    
    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stops the TM One Pulse signal generation.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return        MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;

    MID_TM_OnePulse_Stop(&mTM, MID_TM_Channel3);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_OnePulse_Stop(TM_HandleTypeDef *mTM)
{
    /* Disable the Peripheral */
    mTM->Instance->CR0.W &= ~(TM_CR0_RC_STP_enable_w | TM_CR0_RC_EN_enable_w);
    
    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Starts the TM One Pulse signal generation in interrupt mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return        MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_OnePulse_Start_IT(&mTM);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_OnePulse_Start_IT(TM_HandleTypeDef *mTM)
{
    /* Main Timer/Counter stop enable when repetition counter underflow.  */
    mTM->Instance->CR0.W |= (TM_CR0_RC_STP_enable_w | TM_CR0_RC_EN_enable_w);
    
    /* Enable the TM external trigger interrupt */
    __DRV_TM_ENABLE_IT(mTM, TM_IT_ONEPULSE);
    __DRV_TM_ENABLE_ITEA(mTM);

    /* Enable the Peripheral */
    __DRV_TM_ENABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stops the TM One Pulse signal generation in interrupt mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_OnePulse_Stop_IT(&mTM, MID_TM_Channel3);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_OnePulse_Stop_IT(TM_HandleTypeDef *mTM)
{
    /* Disable the TM Peripheral Clock */
    mTM->Instance->CR0.W &= ~(TM_CR0_RC_STP_enable_w | TM_CR0_RC_EN_enable_w);
    
    /* Disable the TM external trigger interrupt */
    __DRV_TM_DISABLE_IT(mTM, TM_IT_ONEPULSE);
    
    /* check IT for ITEA */
    if((mTM->Instance->INT.W & 0xFFFFFFFE) == 0)
        __DRV_TM_DISABLE_ITEA(mTM);

    /* Return function status */
    return MID_SUCCESS;
}

#endif
///@}



/**
 * @name    Time Encoder functions
 *
 */
///@{
/**
 *******************************************************************************
 * @brief       Initializes the TM Encoder Interface and create the associated handle.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    mTM36.Instance                  = TM36;
    mTM36.Init.TM_CounterMode       = TM_CASCADE_UP;
    mTM36.Init.TM_Period            = 0xFFFF;                   // 12, 18 or 24 Pulses per 360 ?Rotation
    mTM36.Init.TM_Prescaler         = 3;
    mTM36.State                     = MID_TM_STATE_RESET;
    
    MID_TM_Encoder_Init(&mTM36);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_Encoder_Init(TM_HandleTypeDef* mTM)
{

    /* Check the TM handle allocation */
    if(mTM == 0)
        return MID_FAILURE;

    if(mTM->State == MID_TM_STATE_RESET)
    {
        /* Allocate lock resource and initialize it */
        mTM->Lock = MID_UnLocked;

        /* Init the low level hardware : GPIO, CLOCK, NVIC and DMA */
        MID_TM_Encoder_MspInit(mTM);
    }

    /* Set the TM state */
    mTM->State= MID_TM_STATE_BUSY;

    /* Set the Time Base configuration */
    TM_Base_SetConfig(mTM->Instance, &mTM->Init);

    /* Initialize the TM state*/
    mTM->State= MID_TM_STATE_READY;

    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       DeInitializes the TM Encoder interface
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_Encoder_DeInit(&mTM);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_Encoder_DeInit(TM_HandleTypeDef* mTM)
{
    
    /* Process Locked */
    __MID_LOCK(mTM);
    
    mTM->State = MID_TM_STATE_BUSY;

    /* Disable the TM Peripheral Clock */
    __DRV_TM_DISABLE(mTM);

    /* DeInit the low level hardware: GPIO, CLOCK, NVIC */
    MID_TM_Encoder_MspDeInit(mTM);

    /* Change TM state */
    mTM->State = MID_TM_STATE_RESET;

    /* Release Lock */
    __MID_UNLOCK(mTM);

    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Initializes the TM Encoder Interface MSP.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 *******************************************************************************
 */
__weak void MID_TM_Encoder_MspInit(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_Encoder_MspInit could be implemented in the user file
     */
}


/**
 *******************************************************************************
 * @brief       DeInitializes TM Encoder Interface MSP.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 *******************************************************************************
 */
__weak void MID_TM_Encoder_MspDeInit(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_Encoder_MspDeInit could be implemented in the user file
     */
}


/**
 *******************************************************************************
 * @brief       Starts the TM Encoder Interface.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   sConfig : pointer to a TM_Encoder_InitTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM26;
    TM_ClockConfigTypeDef CKConfig;
    TM_Encoder_InitTypeDef TM26Encoder;
    // 
    mTM26.Instance                  = TM26;
    mTM26.Init.TM_CounterMode       = TM_CASCADE_UP;
    mTM26.Init.TM_Period            = 20;
    mTM26.Init.TM_Prescaler         = 3;
    MID_TM_Encoder_Init(&mTM26);
    // 
    CKConfig.TM_ClockSource         = TM_INTERNAL_CLOCK;
    CKConfig.TM_ExternalClockSource = TM_EXTERNAL_ETR;              
    CKConfig.TM_InternalClockSource = TM_INTERNALCLOCK_PROC;
    CKConfig.TM_INTClockDivision    = TM_INTERNALCLOCK_DIVDER_DIV1;
    MID_TM_ConfigClockSource(&mTM26, &CKConfig);  
    // 
    TM26Encoder.EncoderMode         = TM_ENCODERMODE_BOTHEDGE;
    TM26Encoder.EncoderDirection    = TM_ENCODER_DIRECTION_NORMAL;
    TM26Encoder.EncoderReset        = TM_ENCODER_RESET_DISABLE;
    TM26Encoder.IC0Selection        = MID_TM_INPUTMUX_PIN;
    TM26Encoder.IC1Selection        = MID_TM_INPUTMUX_PIN;
    MID_TM_Encoder_Start(&mTM26, &TM26Encoder); 
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_Encoder_Start(TM_HandleTypeDef* mTM, TM_Encoder_InitTypeDef* sConfig)
{
    uint32_t tmp;
    
    
    /* Config IC0 trigger source */
    mTM->Instance->ICCR.MBIT.IC0_MUX = (uint8_t) sConfig->IC0Selection;

    /* Config IC1 trigger source */
    mTM->Instance->ICCR.MBIT.IC1_MUX = (uint8_t) sConfig->IC1Selection;

    /* Config Encoder Direction polarity */
    tmp = mTM->Instance->CR0.W & ~(TM_CR0_DIR_INV_mask_w);
    tmp |= sConfig->EncoderDirection;
    mTM->Instance->CR0.W = tmp;

    /* Config Encoder Mode & IDX step */
    tmp = mTM->Instance->TRG.W & ~(TM_TRG_QEI_MDS_mask_w | TM_TRG_IDX_EN_mask_w | TM_TRG_IDX_MDS_mask_w);
    tmp |= (sConfig->EncoderMode | sConfig->EncoderReset);
    mTM->Instance->TRG.W = tmp;

    /* Encoder's index is fixed at ETR pin */

    /* Enable the Peripheral */
    __DRV_TM_ENABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stops the TM Encoder Interface.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_Encoder_Stop(&mTM);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_Encoder_Stop(TM_HandleTypeDef* mTM)
{

    /* Disable the Peripheral */
    __DRV_TM_DISABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Starts the TM Encoder Interface in interrupt mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   sConfig : pointer to a TM_Encoder_InitTypeDef
 * @param[in]   ITSrc : Specifies the Encoder interrupt
 *  @arg\b      TM_IT_QEI_DIRCHANGE : Encoder direction change event
 *  @arg\b      TM_IT_QEI_INDEX : Encoder recive index event
 *  @arg\b      TM_IT_QEI_ERROR : Encoder recive error position
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM26;
    TM_ClockConfigTypeDef CKConfig;
    TM_Encoder_InitTypeDef TM26Encoder;
    // 
    mTM26.Instance                  = TM26;
    mTM26.Init.TM_CounterMode       = TM_CASCADE_UP;
    mTM26.Init.TM_Period            = 20;
    mTM26.Init.TM_Prescaler         = 3;
    MID_TM_Encoder_Init(&mTM26);
    // 
    CKConfig.TM_ClockSource         = TM_INTERNAL_CLOCK;
    CKConfig.TM_ExternalClockSource = TM_EXTERNAL_ETR;              
    CKConfig.TM_InternalClockSource = TM_INTERNALCLOCK_PROC;
    CKConfig.TM_INTClockDivision    = TM_INTERNALCLOCK_DIVDER_DIV1;
    MID_TM_ConfigClockSource(&mTM26, &CKConfig);  
    // 
    TM26Encoder.EncoderMode         = TM_ENCODERMODE_BOTHEDGE;
    TM26Encoder.EncoderDirection    = TM_ENCODER_DIRECTION_NORMAL;
    TM26Encoder.EncoderReset        = TM_ENCODER_RESET_DISABLE;
    TM26Encoder.IC0Selection        = MID_TM_INPUTMUX_PIN;
    TM26Encoder.IC1Selection        = MID_TM_INPUTMUX_PIN;
    MID_TM_Encoder_Start_IT(&mTM26, &TM26Encoder, TM_IT_QEI_DIRCHANGE); 
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_Encoder_Start_IT(TM_HandleTypeDef* mTM, TM_Encoder_InitTypeDef* sConfig, uint32_t ITSrc)
{
    MID_TM_Encoder_Start(mTM, sConfig);
    
    /* Enable the encoder interface channels */
    __DRV_TM_ENABLE_IT(mTM, ITSrc);
    __DRV_TM_ENABLE_ITEA(mTM);

    /* Enable the Peripheral */
    __DRV_TM_ENABLE(mTM);

    /* Return function status */
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Stops the TM Encoder Interface in interrupt mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   ITSrc : Specifies the Encoder interrupt
 *  @arg\b      TM_IT_QEI_DIRCHANGE : Encoder direction change event
 *  @arg\b      TM_IT_QEI_INDEX : Encoder recive index event
 *  @arg\b      TM_IT_QEI_ERROR : Encoder recive error position
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_Encoder_Stop_IT(&mTM, TM_IT_QEI_INDEX);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_Encoder_Stop_IT(TM_HandleTypeDef* mTM, uint32_t ITSrc)
{
    /* Disable the encoder interface channels */
    __DRV_TM_DISABLE_IT(mTM, ITSrc);

    /* Disable the Peripheral */
    __DRV_TM_DISABLE(mTM);

    /* check IT for ITEA */
    if((mTM->Instance->INT.W & 0xFFFFFFFE) == 0)
        __DRV_TM_DISABLE_ITEA(mTM);

    /* Change the mTM state */
    mTM->State = MID_TM_STATE_READY;

    /* Return function status */
    return MID_SUCCESS;
}
///@}



/**
* @name IRQ handler management
*
*/
///@{
/**
 *******************************************************************************
 * @brief       This function handles TM interrupts requests.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 *******************************************************************************
 */
void MID_TM_IRQHandler(TM_HandleTypeDef* mTM)
{
    /* Capture compare 0 event */
    if(__DRV_TM_GET_EVENT(mTM, TM_EVENT_CH0))
    {
        if(__DRV_TM_GET_IT_SOURCE(mTM, TM_IT_CC0))
        {
            {
                mTM->Channel = MID_TM_Channel0;

                /* Input capture event */
                if(mTM->Instance->CCMDS.MBIT.CC0_MDS == TM_CH_InputCapture)
                {
                    MID_TM_IC_CaptureCallback(mTM);
                    __DRV_TM_CLEAR_FLAG(mTM, (TM_FLAG_CC0A | TM_FLAG_CC0B));
                }
                /* Output compare event */
                else
                {
                    __DRV_TM_CLEAR_FLAG(mTM, (TM_FLAG_CC0A | TM_FLAG_CC0B));
                    MID_TM_OC_DelayElapsedCallback(mTM);
                    MID_TM_PWM_PulseFinishedCallback(mTM);
                }
                mTM->Channel = MID_TM_ACTIVE_CHANNEL_CLEARED;
            }
        }
    }

    /* Capture compare 1 event */
    if(__DRV_TM_GET_EVENT(mTM, TM_EVENT_CH1))
    {
        if(__DRV_TM_GET_IT_SOURCE(mTM, TM_IT_CC1))
        {
            mTM->Channel = MID_TM_Channel1;
            /* Input capture event */
            if(mTM->Instance->CCMDS.MBIT.CC1_MDS == TM_CH_InputCapture)
            {
                MID_TM_IC_CaptureCallback(mTM);
                __DRV_TM_CLEAR_FLAG(mTM, (TM_FLAG_CC1A | TM_FLAG_CC1B));
            }
            /* Output compare event */
            else
            {
                __DRV_TM_CLEAR_FLAG(mTM, (TM_FLAG_CC1A | TM_FLAG_CC1B));
                MID_TM_OC_DelayElapsedCallback(mTM);
                MID_TM_PWM_PulseFinishedCallback(mTM);
            }
            mTM->Channel = MID_TM_ACTIVE_CHANNEL_CLEARED;
        }
    }
    /* Capture compare 2 event */
    if(__DRV_TM_GET_EVENT(mTM, TM_EVENT_CH2))
    {
        if(__DRV_TM_GET_IT_SOURCE(mTM, TM_IT_CC2))
        {
            mTM->Channel = MID_TM_Channel2;
            /* Input capture event */
            if(mTM->Instance->CCMDS.MBIT.CC2_MDS == TM_CH_InputCapture)
            {
                MID_TM_IC_CaptureCallback(mTM);
                __DRV_TM_CLEAR_FLAG(mTM, (TM_FLAG_CC2A | TM_FLAG_CC2B));
            }
            /* Output compare event */
            else
            {
                __DRV_TM_CLEAR_FLAG(mTM, (TM_FLAG_CC2A | TM_FLAG_CC2B));
                MID_TM_OC_DelayElapsedCallback(mTM);
                MID_TM_PWM_PulseFinishedCallback(mTM);
            }
            mTM->Channel = MID_TM_ACTIVE_CHANNEL_CLEARED;
        }
    }
    /* Capture compare 3 event */
    if(__DRV_TM_GET_EVENT(mTM, TM_EVENT_CH3))
    {
        if(__DRV_TM_GET_IT_SOURCE(mTM, TM_IT_CC3))
        {
            mTM->Channel = MID_TM_Channel3;
            /* Input capture event */
            if(mTM->Instance->CCMDS.MBIT.CC3_MDS == TM_CH_InputCapture)
            {
                MID_TM_IC_CaptureCallback(mTM);
                __DRV_TM_CLEAR_FLAG(mTM, (TM_FLAG_CC3A | TM_FLAG_CC3B));
            }
            /* Output compare event */
            else
            {
                __DRV_TM_CLEAR_FLAG(mTM, (TM_FLAG_CC3A | TM_FLAG_CC3B));
                MID_TM_OC_DelayElapsedCallback(mTM);
                MID_TM_PWM_PulseFinishedCallback(mTM);
            }
            mTM->Channel = MID_TM_ACTIVE_CHANNEL_CLEARED;
        }
    }

    #if defined(MG32_3RD)
    /* TM One Pulse event */
    if(__DRV_TM_GET_EVENT(mTM, (TM_EVENT_ONEPULSE)))
    {
        if(__DRV_TM_GET_IT_SOURCE(mTM, TM_IT_ONEPULSE))
        {
            __DRV_TM_CLEAR_FLAG(mTM, (TM_EVENT_ONEPULSE));
            MID_TM_OnePulseCallback(mTM);
        }
    }
    #endif

    /* TM Update event */
    if(__DRV_TM_GET_EVENT(mTM, (TM_FLAG_UPDATE_UP | TM_FLAG_UPDATE_DOWN)))
    {
        if(__DRV_TM_GET_IT_SOURCE(mTM, TM_IT_UPDATE))
        {
            __DRV_TM_CLEAR_FLAG(mTM, (TM_FLAG_UPDATE_UP | TM_FLAG_UPDATE_DOWN));
            MID_TM_PeriodElapsedCallback(mTM);
        }
    }
    /* TM Break input event */
    if(__DRV_TM_GET_FLAG(mTM, (TM_FLAG_BREAK)))
    {
        if(__DRV_TM_GET_IT_SOURCE(mTM, TM_IT_BREAK))
        {
            __DRV_TM_CLEAR_FLAG(mTM, TM_FLAG_BREAK);
            MID_TM_BreakCallback(mTM);
        }
    }
    /* TM Trigger detection event */
    if(__DRV_TM_GET_FLAG(mTM, TM_FLAG_EXTERNAL))
    {
        if(__DRV_TM_GET_IT_SOURCE(mTM, TM_IT_EXTERNAL))
        {
            __DRV_TM_CLEAR_FLAG(mTM, TM_FLAG_EXTERNAL);
            MID_TM_TriggerCallback(mTM);
        }
    }
    /* TM QEI direction change event */
    if(__DRV_TM_GET_FLAG(mTM, TM_FLAG_QEI_DIRCHANGE))
    {
        if(__DRV_TM_GET_IT_SOURCE(mTM, TM_IT_QEI_DIRCHANGE) != CLR)
        {
            __DRV_TM_CLEAR_FLAG(mTM, TM_FLAG_QEI_DIRCHANGE);
            MID_TM_QEI_DIRCHANGECallback(mTM);
        }
    }
    /* TM QEI direction change event */
    if(__DRV_TM_GET_FLAG(mTM, TM_FLAG_QEI_INDEX))
    {
        if(__DRV_TM_GET_IT_SOURCE(mTM, TM_IT_QEI_INDEX))
        {
            __DRV_TM_CLEAR_FLAG(mTM, TM_FLAG_QEI_INDEX);
            MID_TM_QEI_INDEXCallback(mTM);
        }
    }
    /* TM QEI direction change event */
    if(__DRV_TM_GET_FLAG(mTM, TM_FLAG_QEI_ERROR))
    {
        if(__DRV_TM_GET_IT_SOURCE(mTM, TM_IT_QEI_ERROR))
        {
            __DRV_TM_CLEAR_FLAG(mTM, TM_FLAG_QEI_ERROR);
            MID_TM_QEI_ErrorCallback(mTM);
        }
    }
    
    __DRV_TM_CLEAR_FLAG(mTM,     TM_FLAG_CC0A | TM_FLAG_CC1A | TM_FLAG_CC2A | TM_FLAG_CC3A
                               | TM_FLAG_CC0B | TM_FLAG_CC1B | TM_FLAG_CC2B | TM_FLAG_CC3B
                               | TM_FLAG_UPDATE_UP  | TM_FLAG_UPDATE_DOWN 
                               | TM_FLAG_UPDATE2_UP | TM_FLAG_UPDATE2_DOWN
                               | TM_FLAG_BREAK | TM_FLAG_EXTERNAL
                               | TM_FLAG_QEI_DIRCHANGE | TM_FLAG_QEI_INDEX
                               | TM_FLAG_QEI_ERROR | TM_FLAG_DIRECTION | TM_FLAG_ONEPULSE  ) ;

}
///@}



/**
 * @name    Peripheral Control functions
 *
 */
///@{
/**
 *******************************************************************************
 * @brief       Initializes the TM Output Compare Channels according to the
 *              specified parameters in the TM_OC_InitTypeDef.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   sConfig : pointer to a TM_OC_InitTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_OC_InitTypeDef sConfig;
    
    MID_TM_OC_Struct_Init(&sConfig);                   // initial default parameters
    sConfig.OCMode  = TM_CH_16bit_OutputCompare;
    sConfig.Pulse   = 200;                          // duty cycle 

    MID_TM_OC_ConfigChannel(&mTM, &sConfig, MID_TM_Channel1);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_OC_ConfigChannel(TM_HandleTypeDef* mTM, TM_OC_InitTypeDef* sConfig, uint32_t Channel)
{
    /* Check input state */
    __MID_LOCK(mTM);

    mTM->State = MID_TM_STATE_BUSY;

    switch(Channel)
    {
    case MID_TM_Channel0:
    {
        /* Configure the TM Channel 0 in Output Compare */
        TM_OC0_SetConfig(mTM->Instance, sConfig);
    }
    break;

    case MID_TM_Channel1:
    {
        /* Configure the TM Channel 1 in Output Compare */
        TM_OC1_SetConfig(mTM->Instance, sConfig);
    }
    break;

    case MID_TM_Channel2:
    {
        /* Configure the TM Channel 2 in Output Compare */
        TM_OC2_SetConfig(mTM->Instance, sConfig);
    }
    break;

    case MID_TM_Channel3:
    {
        /* Configure the TM Channel 3 in Output Compare */
        TM_OC3_SetConfig(mTM->Instance, sConfig);
    }
    break;

    default:
        break;
    }
    mTM->State = MID_TM_STATE_READY;

    /* Release Lock */
    __MID_UNLOCK(mTM);

    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Initializes the TM Input Capture Channels according to the
 *              specified parameters in the TM_IC_InitTypeDef.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   sConfig : pointer to a TM_OC_InitTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_IC_InitTypeDef sConfig;
    sConfig.ICPolarity  = TM_ICPOLARITY_RISING;
    sConfig.ICSelection = MID_TM_INPUTMUX_PIN;                          
    sConfig.ICDataMode  = MID_TM_IC_KEEPDATA;
  
    MID_TM_IC_ConfigChannel(&mTM, &sConfig, MID_TM_Channel0);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_IC_ConfigChannel(TM_HandleTypeDef* mTM, TM_IC_InitTypeDef* sConfig, uint32_t Channel)
{
    /* Process Locked */
    __MID_LOCK(mTM);

    mTM->State = MID_TM_STATE_BUSY;

    if(Channel == MID_TM_Channel0)
    {
        /* Config IC0 trigger source & edge */
        mTM->Instance->ICCR.W &= ~(TM_ICCR_IC0_MUX_mask_w | TM_ICCR_IC0_TRGS_mask_w);
        mTM->Instance->ICCR.W |= (sConfig->ICSelection | sConfig->ICPolarity);
        // Overwritten or keep data for channel 0
        mTM->Instance->CR1.W &= ~(TM_CR1_OVR0_MDS_mask_w);
        mTM->Instance->CR1.W |= (sConfig->ICDataMode);
    }
    else if(Channel == MID_TM_Channel1)
    {
        /* Config IC1 trigger source & edge */
        mTM->Instance->ICCR.W &= ~(TM_ICCR_IC1_MUX_mask_w | TM_ICCR_IC1_TRGS_mask_w);
        mTM->Instance->ICCR.W |= (sConfig->ICSelection << 4);
        mTM->Instance->ICCR.W |= (sConfig->ICPolarity << 2);
        // Overwritten or keep data for channel 1
        mTM->Instance->CR1.W &= ~(TM_CR1_OVR0_MDS_mask_w << 1);
        mTM->Instance->CR1.W |= (sConfig->ICDataMode << 1);
    }
    else if(Channel == MID_TM_Channel2)
    {
        /* Config IC2 trigger source & edge */
        mTM->Instance->ICCR.W &= ~(TM_ICCR_IC2_MUX_mask_w | TM_ICCR_IC2_TRGS_mask_w);
        mTM->Instance->ICCR.W |= (sConfig->ICSelection << 8);
        mTM->Instance->ICCR.W |= (sConfig->ICPolarity << 6);
        // Overwritten or keep data for channel 2
        mTM->Instance->CR1.W &= ~(TM_CR1_OVR0_MDS_mask_w << 2);
        mTM->Instance->CR1.W |= (sConfig->ICDataMode << 2);
    }
    else
    {
        /* Config IC3 trigger source & edge */
        mTM->Instance->ICCR.W &= ~(TM_ICCR_IC3_MUX_mask_w | TM_ICCR_IC3_TRGS_mask_w);
        mTM->Instance->ICCR.W |= (sConfig->ICSelection << 12);
        mTM->Instance->ICCR.W |= (sConfig->ICPolarity << 6);
        // Overwritten or keep data for channel 3
        mTM->Instance->CR1.W &= ~(TM_CR1_OVR0_MDS_mask_w << 3);
        mTM->Instance->CR1.W |= (sConfig->ICDataMode << 3);
    }

    mTM->State = MID_TM_STATE_READY;

    /* Release Lock */
    __MID_UNLOCK(mTM);

    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Initializes the TM PWM  channels according to the specified
 *              parameters in the TM_OC_InitTypeDef.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   sConfig : pointer to a TM_OC_InitTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_OC_InitTypeDef sConfig;
    
    MID_TM_OC_Struct_Init(&sConfig);                   // initial default parameters
    sConfig.OCMode  = TM_CH_16bit_PWM;
    sConfig.Pulse   = 200;                          // duty cycle 

    MID_TM_PWM_ConfigChannel(&mTM, &sConfig, MID_TM_Channel0);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_PWM_ConfigChannel(TM_HandleTypeDef* mTM, TM_OC_InitTypeDef* sConfig, uint32_t Channel)
{
    /* Check input state */
    __MID_LOCK(mTM);

    mTM->State = MID_TM_STATE_BUSY;

    switch(Channel)
    {
    case MID_TM_Channel0:
    {
        /* Configure the TM Channel 0 in PWM Compare */
        TM_OC0_SetConfig(mTM->Instance, sConfig);
    }
    break;

    case MID_TM_Channel1:
    {
        /* Configure the TM Channel 1 in PWM Compare */
        TM_OC1_SetConfig(mTM->Instance, sConfig);
    }
    break;

    case MID_TM_Channel2:
    {
        /* Configure the TM Channel 2 in PWM Compare */
        TM_OC2_SetConfig(mTM->Instance, sConfig);
    }
    break;

    case MID_TM_Channel3:
    {
        /* Configure the TM Channel 3 in PWM Compare */
        TM_OC3_SetConfig(mTM->Instance, sConfig);
    }
    break;

    default:
        break;
    }
    mTM->State = MID_TM_STATE_READY;

    /* Release Lock */
    __MID_UNLOCK(mTM);

    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Generate a software event
 * @param       mTM : TM handle
 * @param       EventSource : specifies the event source.
 *              This parameter can be one of the following values:
 *   @arg       TM_EVENTSOURCE_CC0A: Channel0 IC/OC event-A generation.
 *   @arg       TM_EVENTSOURCE_CC0B: Channel0 IC/OC event-B generation.
 *   @arg       TM_EVENTSOURCE_CC1A: Channel1 IC/OC event-A generation.
 *   @arg       TM_EVENTSOURCE_CC1B: Channel1 IC/OC event-B generation.
 *   @arg       TM_EVENTSOURCE_CC2A: Channel2 IC/OC event-A generation.
 *   @arg       TM_EVENTSOURCE_CC2B: Channel2 IC/OC event-B generation.
 *   @arg       TM_EVENTSOURCE_CC3A: Channel3 IC/OC event-A generation.
 *   @arg       TM_EVENTSOURCE_CC3B: Channel3 IC/OC event-B generation.
 *   @arg       TM_EVENTSOURCE_TRIGGER: Timer external update event generation.
 *   @arg       TM_EVENTSOURCE_BREAK: Timer Break event source generation.
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_GenerateEvent(mTM, TM_EVENTSOURCE_CC0A);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_GenerateEvent(TM_HandleTypeDef* mTM, uint32_t EventSource)
{
    /* Process Lockeded */
    __MID_LOCK(mTM);

    /* Change the TM state */
    mTM->State = MID_TM_STATE_BUSY;

    /* Set the event sources */
    switch(EventSource)
    {
    case TM_EVENTSOURCE_CC0A:
        mTM->Instance->CR1.W |= TM_CR1_CC0A_SEN_enable_w;
        break;
    case TM_EVENTSOURCE_CC0B:
        mTM->Instance->CR1.W |= TM_CR1_CC0B_SEN_enable_w;
        break;
    case TM_EVENTSOURCE_CC1A:
        mTM->Instance->CR1.W |= TM_CR1_CC1A_SEN_enable_w;
        break;
    case TM_EVENTSOURCE_CC1B:
        mTM->Instance->CR1.W |= TM_CR1_CC1B_SEN_enable_w;
        break;
    case TM_EVENTSOURCE_CC2A:
        mTM->Instance->CR1.W |= TM_CR1_CC2A_SEN_enable_w;
        break;
    case TM_EVENTSOURCE_CC2B:
        mTM->Instance->CR1.W |= TM_CR1_CC2B_SEN_enable_w;
        break;
    case TM_EVENTSOURCE_CC3A:
        mTM->Instance->CR1.W |= TM_CR1_CC3A_SEN_enable_w;
        break;
    case TM_EVENTSOURCE_CC3B:
        mTM->Instance->CR1.W |= TM_CR1_CC3B_SEN_enable_w;
        break;
    case TM_EVENTSOURCE_TRIGGER:
        mTM->Instance->CR0.W |= TM_CR0_USW_EN_enable_w;
        break;
    case TM_EVENTSOURCE_BREAK:
        mTM->Instance->BS.W |= TM_BS_BKSW_EN_enable_w;
        mTM->Instance->BS.W &= ~(TM_BS_BKSW_EN_enable_w);
        break;
    default:
        break;

    }

    /* Change the TM state */
    mTM->State = MID_TM_STATE_READY;

    /* Release Lock */
    __MID_UNLOCK(mTM);

    /* Return function status */
    return MID_SUCCESS;
}



/**
 *******************************************************************************
 * @brief       CConfigures the clock source to be used.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   sClockSourceConfig : pointer to a TM_ClockConfigTypeDef structure that
 *              contains the clock source information for the TM peripheral.
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_ClockConfigTypeDef CKConfig;

    CKConfig.TM_ClockSource         = TM_INTERNAL_CLOCK;
    CKConfig.TM_ExternalClockSource = 0;
    CKConfig.TM_INTClockDivision    = TM_INTERNALCLOCK_DIVDER_DIV1;
    CKConfig.TM_InternalClockSource = TM_INTERNALCLOCK_PROC;

    MID_TM_ConfigClockSource(&mTM20, &CKConfig);  
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_ConfigClockSource(TM_HandleTypeDef * mTM, TM_ClockConfigTypeDef * sClockSourceConfig)
{
    uint32_t tmpsmcr = 0U;

    /* Process Lockeded */
    __MID_LOCK(mTM);

    mTM->State = MID_TM_STATE_BUSY;

    /* Config Main Counter/Prescaler Clock source from Internal or External clock */
    /* Config Internal / External Clock source */
    tmpsmcr = mTM->Instance->CLK.W;
    tmpsmcr &= ~(TM_CLK_CKI_DIV_mask_w | TM_CLK_CKI_SEL_mask_w | TM_CLK_CKS2_SEL_mask_w | TM_CLK_CKS_SEL_mask_w | TM_CLK_CKE_SEL_mask_w);
    tmpsmcr |= (sClockSourceConfig->TM_ClockSource | sClockSourceConfig->TM_INTClockDivision | sClockSourceConfig->TM_InternalClockSource);
    tmpsmcr |= (sClockSourceConfig->TM_ExternalClockSource & ~(TM_TRG_ITR_MUX_mask_w));  
    mTM->Instance->CLK.W = tmpsmcr;

    /* Config ITRx Clock source */
    tmpsmcr = mTM->Instance->TRG.W;
    tmpsmcr &= ~(TM_TRG_ITR_MUX_mask_w);
    tmpsmcr |= (sClockSourceConfig->TM_ExternalClockSource & ~(TM_CLK_CKE_SEL_mask_w));  
    mTM->Instance->TRG.W = tmpsmcr;
  
    // Update state & unlock
    mTM->State = MID_TM_STATE_READY;

    /* Release Lock */
    __MID_UNLOCK(mTM);

    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Configures the TM in master mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   sMasterConfig : pointer to a TM_MasterConfigTypeDef structure that
 *              contains the selected trigger output (TRGO) and the Master.
*   @arg        MasterOutputTrigger: TRGO source.
*   @arg        MasterOutputPolarity: Invert TRGO or not.
*   @arg        MasterUpdateEvent: specify option of disable, TOF, TUF or both edge.
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_MasterConfigTypeDef TM_TRGOConfig;

    TM_TRGOConfig.MasterOutputTrigger   = TM_TRGO_UPDATE;
    TM_TRGOConfig.MasterOutputPolarity  = TM_MASTEROUTPUT_BYPASS;
    TM_TRGOConfig.MasterUpdateEvent     = TM_UPDATE_OVERFLOW;

    MID_TM_MasterConfigSynchronization(&mTM10, &TM_TRGOConfig);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_MasterConfigSynchronization(TM_HandleTypeDef* mTM, TM_MasterConfigTypeDef * sMasterConfig)
{
    uint32_t tmpTRGO;

    /* Process Lockeded */
    __MID_LOCK(mTM);
    
    mTM->State = MID_TM_STATE_BUSY;
    
    /* Load TRG reigter and mask TRGO control bit */
    tmpTRGO = mTM->Instance->TRG.W & ~(TM_TRG_TRGO_INV_mask_w | TM_TRG_UEV_SEL_mask_w | TM_TRG_TRGO_MDS_mask_w);
    
    /* Over write TRGO control parameters  */
    tmpTRGO |= (sMasterConfig->MasterOutputTrigger | sMasterConfig->MasterOutputPolarity | sMasterConfig->MasterUpdateEvent);
    
    /* Reset the TRG register */
    mTM->Instance->TRG.W = tmpTRGO;
        
    /* Release Lock */
    __MID_UNLOCK(mTM);
    
    return MID_SUCCESS;
}


/**
 *******************************************************************************
 * @brief       Configures the Break feature, dead time, OCx/OCxN State
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   sBreakDeadTimeConfig : pointer to a TM_ConfigBreakDeadConfigTypeDef structure that
 *              contains the BS/PWM Register configuration information for the TM peripheral.
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_BreakDeadTimeConfigTypeDef BKConfig;
 
    BKConfig.BreakMode              = TM_BK_CYCLE_BY_CYCLE;
    BKConfig.BreakCHxOutputMode     = MID_BREAK_STOP_STATE;
    BKConfig.BreakSourceSel         = MID_BK_ExtPin | MID_BK_ClockFailure | MID_BK_CPULOCKUP | MID_BK_BOD1;
    BKConfig.DeatTimeClockDivision  = MID_TM_CKDTG_DIV1;
    BKConfig.DeadTime               = DeadTime_Set;
    
    MID_TM_ConfigBreakDeadTime(&mTM36, &BKConfig);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_ConfigBreakDeadTime(TM_HandleTypeDef* mTM, TM_BreakDeadTimeConfigTypeDef *sBreakDeadTimeConfig)
{
    uint32_t tmpBS;
    
    tmpBS = (uint32_t) ((mTM->Instance->BS.W) & (0xFFFFFFF0));
    
    /* Process Lockeded */
    __MID_LOCK(mTM);

    // config BreakMode, Stop State, Break source
    tmpBS |= sBreakDeadTimeConfig->BreakMode;
    tmpBS |= sBreakDeadTimeConfig->BreakCHxOutputMode;
    tmpBS |= sBreakDeadTimeConfig->BreakSourceSel;
    
    mTM->Instance->BS.W = tmpBS;
    
    // config dead time clock divider
    mTM->Instance->CLK.W &= ~(TM_CLK_DTG_DIV_mask_w);
    mTM->Instance->CLK.W |= sBreakDeadTimeConfig->DeatTimeClockDivision;
    
    // config dead time
    mTM->Instance->PWM.W &= ~(TM_PWM_DTG_DY_mask_w);
    mTM->Instance->PWM.W |= (sBreakDeadTimeConfig->DeadTime << 8);

    /* Release Lock */
    __MID_UNLOCK(mTM);

    return MID_SUCCESS;
    
}

/**
 *******************************************************************************
 * @brief       Configures the TM in Slave mode (Disable, Reset, Gated, Trigger,¡K)
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   sSlaveConfig : pointer to a TM_SlaveConfigTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;
    TM_SlaveConfigTypeDef TMslave;
    
    TMslave.SlaveMode       = TM_SLAVEMODE_TRIGGER_RISINGEDGE;
    TMslave.InputTrigger    = TM_TS_IN0;

    MID_TM_SlaveConfigSynchronization(&mTM, &TMslave);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_SlaveConfigSynchronization(TM_HandleTypeDef* mTM, TM_SlaveConfigTypeDef* sSlaveConfig)
{
    /* Process Lockeded */
    __MID_LOCK(mTM);

    mTM->State = MID_TM_STATE_BUSY;

    TM_SlaveTimer_SetConfig(mTM, sSlaveConfig);

    /* Disable Trigger Interrupt */
    __DRV_TM_DISABLE_IT(mTM, TM_IT_EXTERNAL);

    mTM->State = MID_TM_STATE_READY;

    /* Release Lock */
    __MID_UNLOCK(mTM);

    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Configures the TM in Slave mode in interrupt mode (Disable, Reset
 *              , Gated, Trigger,¡K)
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   sSlaveConfig : specifies Timer channel selection
 *  @arg\b      SlaveMode : This parameter can be a value of 
 *              reference TM_Slave_Mode.
 *  @arg\b      InputTrigger : This parameter can be a value of 
 *              reference TM_Trigger_Selection.
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;
    TM_SlaveConfigTypeDef TMslave;
    
    TMslave.SlaveMode       = TM_SLAVEMODE_TRIGGER_RISINGEDGE;
    TMslave.InputTrigger    = TM_TS_IN0;

    MID_TM_SlaveConfigSynchronization_IT(&mTM, &TMslave);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_SlaveConfigSynchronization_IT(TM_HandleTypeDef* mTM, TM_SlaveConfigTypeDef* sSlaveConfig)
{
    /* Process Lockeded */
    __MID_LOCK(mTM);

    mTM->State = MID_TM_STATE_BUSY;

    TM_SlaveTimer_SetConfig(mTM, sSlaveConfig);

    /* Enable Trigger Interrupt */
    __DRV_TM_ENABLE_IT(mTM, TM_IT_EXTERNAL);

    mTM->State = MID_TM_STATE_READY;

    /* Release Lock */
    __MID_UNLOCK(mTM);

    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Configures the TM output clock with 50% duty cycle.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   sClockConfig : specifies Timer clockout configureation
 *  @arg\b      CKOInitState : The timer CKO output signal initial state. 
 *  @arg\b      CKOSource : The timer clock out source event.
 *  @arg\b      CKOCmd : The timer clockout function.
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;
    TM_CKOConfigTypeDef TMCKO;
    
    TMCKO.CKOInitState  = TM_CKOINIT_SET;
    TMCKO.CKOSource     = TM_CKOSOURCE_PRESCALER;
    TMCKO.CKOCmd        = ENABLE;

    MID_TM_ClockOut(&mTM, &TMCKO);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_TM_ClockOut(TM_HandleTypeDef* mTM, TM_CKOConfigTypeDef* sClockConfig)
{
    uint32_t tmpCKO;
    
    /* Check input state */
    __MID_LOCK(mTM);
    
    mTM->State = MID_TM_STATE_BUSY;

    // config CKO register
    tmpCKO = sClockConfig->CKOInitState | sClockConfig->CKOSource | sClockConfig->CKOCmd | TM_CKO_CKO_LCK_un_locked_w;
    mTM->Instance->CKO.W = tmpCKO;

    // release & unlock
    mTM->State = MID_TM_STATE_READY;
    
    /* Release Lock */
    __MID_UNLOCK(mTM);

    return MID_SUCCESS;
}

/**
 *******************************************************************************
 * @brief       Read the captured value from Capture Compare unit.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;

    MID_TM_ReadCapturedValue(&mTM, MID_TM_Channel1);
 * @endcode
 *******************************************************************************
 */
uint32_t MID_TM_ReadCapturedValue(TM_HandleTypeDef *mTM, uint32_t Channel)
{
    volatile ctype tmpreg;
    
    tmpreg.W = 0U;

    /* Process Locked */
    __MID_LOCK(mTM);

    switch (Channel)
    {
    case MID_TM_Channel0:
        // Fyll counter mode (32bit)
        if((mTM->Init.TM_CounterMode & 0x0020) != 0)
        {
            /* Return the capture 0 value */
            tmpreg.H[1] = mTM->Instance->CC0A.H[0];
            tmpreg.H[0] = mTM->Instance->CC0B.H[0];
        }
        else
        {   // Separate/Cascade mode (16 bit)
            if(__DRV_TM_GET_FLAG(mTM, TM_FLAG_CC0B))
                tmpreg.H[0] = mTM->Instance->CC0B.H[0];
            else
                tmpreg.H[0] = mTM->Instance->CC0A.H[0];
        }
        break;

    case MID_TM_Channel1:
        // Fyll counter mode (32bit)
        if((mTM->Init.TM_CounterMode & 0x0020) != 0)
        {
            /* Return the capture 0 value */
            tmpreg.H[1] = mTM->Instance->CC1A.H[0];
            tmpreg.H[0] = mTM->Instance->CC1B.H[0];
        }
        else
        {   // Separate/Cascade mode (16 bit)
            if(__DRV_TM_GET_FLAG(mTM, TM_FLAG_CC1B))
                tmpreg.H[0] = mTM->Instance->CC1B.H[0];
            else
                tmpreg.H[0] = mTM->Instance->CC1A.H[0];
        }
        break;
        
    case MID_TM_Channel2:
        // Fyll counter mode (32bit)
        if((mTM->Init.TM_CounterMode & 0x0020) != 0)
        {
            /* Return the capture 0 value */
            tmpreg.H[1] = mTM->Instance->CC2A.H[0];
            tmpreg.H[0] = mTM->Instance->CC2B.H[0];
        }
        else
        {   // Separate/Cascade mode (16 bit)
            if(__DRV_TM_GET_FLAG(mTM, TM_FLAG_CC2B))
                tmpreg.H[0] = mTM->Instance->CC2B.H[0];
            else
                tmpreg.H[0] = mTM->Instance->CC2A.H[0];
        }
        break;

    case MID_TM_Channel3:
        // Fyll counter mode (32bit)
        if((mTM->Init.TM_CounterMode & 0x0020) != 0)
        {
            /* Return the capture 0 value */
            tmpreg.H[1] = mTM->Instance->CC3A.H[0];
            tmpreg.H[0] = mTM->Instance->CC3B.H[0];
        }
        else
        {   // Separate/Cascade mode (16 bit)
            if(__DRV_TM_GET_FLAG(mTM, TM_FLAG_CC3B))
                tmpreg.H[0] = mTM->Instance->CC3B.H[0];
            else
                tmpreg.H[0] = mTM->Instance->CC3A.H[0];
        }
        break;
        
    default:
        break;
    }

    /* Release Lock */
    __MID_UNLOCK(mTM);
    
    return tmpreg.W;
}
///@}



/**
 * @name    TM Callbacks functions
 *
 */
///@{
/**
 *******************************************************************************
 * @brief       Period elapsed callback in non blocking mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
extern void TIM_PeriodElapsedCallback(TM_HandleTypeDef *htim);
__weak void MID_TM_PeriodElapsedCallback(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    //UNUSED(mTM);
    TIM_PeriodElapsedCallback( mTM );
    
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_PeriodElapsedCallback could be implemented in the user file
     */

}


/**
 *******************************************************************************
 * @brief       Output Compare callback in non blocking mode
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_TM_OC_DelayElapsedCallback(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_OC_DelayElapsedCallback could be implemented in the user file
     */

}

/**
 *******************************************************************************
 * @brief       Input Capture callback in non blocking mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_TM_IC_CaptureCallback(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_IC_CaptureCallback could be implemented in the user file
     */

}



/**
 *******************************************************************************
 * @brief       PWM Pulse finished callback in non blocking mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 *******************************************************************************
 */
__weak void MID_TM_PWM_PulseFinishedCallback(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_PWM_PulseFinishedCallback could be implemented in the user file
     */

}



/**
 *******************************************************************************
 * @brief       Hall Trigger detection callback in non blocking mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_TM_TriggerCallback(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_TriggerCallback could be implemented in the user file
     */

}



/**
 *******************************************************************************
 * @brief       TMer error callback in non blocking mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_TM_ErrorCallback(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_ErrorCallback could be implemented in the user file
     */

}

/**
 *******************************************************************************
 * @brief       Hall Break detection callback in non blocking mode
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_TM_BreakCallback(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_BreakCallback could be implemented in the user file
     */
}


/**
 *******************************************************************************
 * @brief       QEI direction change callback in non blocking mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_TM_QEI_DIRCHANGECallback(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_QEI_DIRCHANGECallback could be implemented in the user file
     */

}

/**
 *******************************************************************************
 * @brief       QEI index callback in non blocking mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_TM_QEI_INDEXCallback(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_QEI_INDEXCallback could be implemented in the user file
     */

}

/**
 *******************************************************************************
 * @brief       QEI receive error signal callback in non blocking mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_TM_QEI_ErrorCallback(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_QEI_ErrorCallback could be implemented in the user file
     */

}

/**
 *******************************************************************************
 * @brief       Repetition timer underflow signal callback in non blocking mode.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_TM_OnePulseCallback(TM_HandleTypeDef* mTM)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mTM);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_TM_QEI_ErrorCallback could be implemented in the user file
     */

}
///@}



/**
 * @name    Peripheral State functions
 *
 */
///@{
/**
 *******************************************************************************
 * @brief       Return the TM Base state.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 *******************************************************************************
 */
MID_TM_StateTypeDef MID_TM_Base_GetState(TM_HandleTypeDef* mTM)
{
    return mTM->State;
}

/**
 *******************************************************************************
 * @brief       Return the TM OC state.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 *******************************************************************************
 */
MID_TM_StateTypeDef MID_TM_OC_GetState(TM_HandleTypeDef* mTM)
{
    return mTM->State;
}

/**
 *******************************************************************************
 * @brief       Return the TM PWM state.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 *******************************************************************************
 */
MID_TM_StateTypeDef MID_TM_PWM_GetState(TM_HandleTypeDef* mTM)
{
    return mTM->State;
}

/**
 *******************************************************************************
 * @brief       Return the TM Input Capture state.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 *******************************************************************************
 */
MID_TM_StateTypeDef MID_TM_IC_GetState(TM_HandleTypeDef* mTM)
{
    return mTM->State;
}

#if defined(MG32_3RD)
/**
 *******************************************************************************
 * @brief       Return the TM One Pulse Mode state.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 *******************************************************************************
 */
MID_TM_StateTypeDef MID_TM_OnePulse_GetState(TM_HandleTypeDef* mTM)
{
    return mTM->State;
}
#endif

/**
 *******************************************************************************
 * @brief       Return the TM Encoder Mode state.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @return      MID_StatusTypeDef
 *******************************************************************************
 */
MID_TM_StateTypeDef MID_TM_Encoder_GetState(TM_HandleTypeDef* mTM)
{
    return mTM->State;
}

///@}



/**
 * @name    PWM output config
 *
 */
///@{
/**
 *******************************************************************************
 * @brief       Fills each TM_OC_InitTypeDef member with its default value.
 * @param[in]   sConfig : pointer to a TM_OC_InitTypeDef
 *              structure which will be initialized.
 * @return      No
 *******************************************************************************
 */
void MID_TM_OC_Struct_Init(TM_OC_InitTypeDef* sConfig)
{
    sConfig->OCMode         = TM_CH_16bit_OutputCompare;
    sConfig->Pulse          = 1000;                         // duty cycle setting
    sConfig->OCPolarity     = TM_OCPOLARITY_HIGH;           // No-Inverse
    sConfig->OCNPolarity    = TM_OCNPOLARITY_HIGH;          // No-Inverse
    sConfig->OCHPolarity    = TM_OCHPOLARITY_HIGH;          // No-Inverse
    sConfig->OCIdleState    = TM_OCIDLESTATE_RESET;         // OCxx : Output low in idle state
    sConfig->OCNIdleState   = TM_OCNIDLESTATE_RESET;        // OCxN : Output low in idle state
    sConfig->OCHIdleState   = TM_OCHIDLESTATE_RESET;        // OCxH : Output low in idle state
}


/**
 *******************************************************************************
 * @brief       TM DMA error call back.
 * @param[in]   hDMA : pointer to a DMA_HandleTypeDef
 * @return      MID_StatusTypeDef
 *******************************************************************************
 */
void TM_DMAError(DMA_HandleTypeDef* hDMA)
{
    TM_HandleTypeDef* mTM = (TM_HandleTypeDef*)((DMA_HandleTypeDef*)hDMA)->Parent;

    mTM->State= MID_TM_STATE_READY;

    MID_TM_ErrorCallback(mTM);
}


/**
 *******************************************************************************
 * @brief       TM DMA Delay Pulse complete callback.
 * @param[in]   hDMA : pointer to a DMA_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
void TM_DMADelayPulseCplt(DMA_HandleTypeDef* hDMA)
{
    TM_HandleTypeDef* mTM = (TM_HandleTypeDef*)((DMA_HandleTypeDef*)hDMA)->Parent;

    mTM->State = MID_TM_STATE_READY;

    if(hDMA == mTM->hDMA[TM_DMA_ID_CC0])
    {
        mTM->Channel = MID_TM_Channel0;
        // to do ...
    }
    else if(hDMA == mTM->hDMA[TM_DMA_ID_CC1])
    {
        mTM->Channel = MID_TM_Channel1;
        // to do ...
    }
    else if(hDMA == mTM->hDMA[TM_DMA_ID_CC2])
    {
        mTM->Channel = MID_TM_Channel2;
        // to do ...
    }
    else if(hDMA == mTM->hDMA[TM_DMA_ID_CC3])
    {
        mTM->Channel = MID_TM_Channel3;
        // to do ...
    }

    MID_TM_PWM_PulseFinishedCallback(mTM);

    mTM->Channel = MID_TM_ACTIVE_CHANNEL_CLEARED;
}

/**
 *******************************************************************************
 * @brief       TM DMA Capture complete callback.
 * @param[in]   hDMA : pointer to a DMA_HandleTypeDef
 * @return      MID_StatusTypeDef
 *******************************************************************************
 */
void TM_DMACaptureCplt(DMA_HandleTypeDef* hDMA)
{
    TM_HandleTypeDef* mTM = (TM_HandleTypeDef*)((DMA_HandleTypeDef*)hDMA)->Parent;

    mTM->State = MID_TM_STATE_READY;

    if(hDMA == mTM->hDMA[TM_DMA_ID_CC0])
    {
        mTM->Channel = MID_TM_Channel0;
        // to do ...
    }
    else if(hDMA == mTM->hDMA[TM_DMA_ID_CC1])
    {
        mTM->Channel = MID_TM_Channel1;
        // to do ...
    }
    else if(hDMA == mTM->hDMA[TM_DMA_ID_CC2])
    {
        mTM->Channel = MID_TM_Channel2;
        // to do ...
    }
    else if(hDMA == mTM->hDMA[TM_DMA_ID_CC3])
    {
        mTM->Channel = MID_TM_Channel3;
        // to do ...
    }

    MID_TM_IC_CaptureCallback(mTM);

    mTM->Channel = MID_TM_ACTIVE_CHANNEL_CLEARED;
}

/**
 *******************************************************************************
 * @brief       TM Base configuration.
 * @param[in]   TMx : pointer to a TM_Struct
 * @param[in]   Structure : pointer to a TM_Base_InitTypeDef
 * @return      None
 * @note
 * @par         Example
 * @code
    TM_Base_SetConfig(mTM->Instance, &mTM->Init);
 * @endcode
 *******************************************************************************
 */
void TM_Base_SetConfig(TM_Struct* TMx, TM_Base_InitTypeDef* Structure)
{
    uint32_t tmpcr1 = 0U;

    /* Set TM Time Base Unit parameters ----------------------------------------*/
    /* TM mode & direction */
    tmpcr1 = TMx->CR0.W & ~(TM_CR0_MDS_mask_w | TM_CR0_DIR_mask_w | TM_CR0_DIR2_mask_w);
    tmpcr1 |= Structure->TM_CounterMode;
    TMx->CR0.W = tmpcr1;

    /* Set the Autoreload value */
    TMx->ARR.W = (uint32_t)Structure->TM_Period ;

    /* Set the Prescaler value */
    TMx->PSARR.W = (uint32_t)Structure->TM_Prescaler;

    /* Generate an update event to reload the Main Counter and Prescaler  */
    TMx->TRG.W |= (TM_TRG_RST2_SW_enable_w | TM_TRG_RST_SW_enable_w);
    TMx->TRG.W &= ~(TM_TRG_RST2_SW_enable_w | TM_TRG_RST_SW_enable_w);

}

/**
 *******************************************************************************
 * @brief       TMe Ouput Compare 0 configuration.
 * @param[in]   TMx : pointer to a TM_HandleTypeDef
 * @param[in]   OC_Config : The ouput configuration structure
 * @return      None
 * @note
 * @par         Example
 * @code
    TM_OC0_SetConfig(&mTM->Instance, sConfig);
 * @endcode
 *******************************************************************************
 */
static void TM_OC0_SetConfig(TM_Struct* TMx, TM_OC_InitTypeDef* OC_Config)
{
    /* Set the Output Idle state (Break state) */
    TMx->BS.W &= ~(TM_BS_STP0_STA_mask_w | TM_BS_STP0N_STA_mask_w);
    TMx->BS.W |= ((OC_Config->OCIdleState  | OC_Config->OCNIdleState) << 0);

    /* Set the Output Idle state  */
    TMx->OSCR.W |= ((TM_OSCR_OS0_LCK_un_locked_w | OC_Config->OCIdleState |
                     TM_OSCR_OS0H_LCK_un_locked_w | OC_Config->OCHIdleState) << 0);

    /* Set the Output Polarity */
    TMx->OCCR1.W &= ~((TM_OCCR1_OC0_INV_mask_w | TM_OCCR1_OC0H_INV_mask_w | TM_OCCR1_OC0N_INV_mask_w) << 0);
    TMx->OCCR1.W |= ((OC_Config->OCPolarity | OC_Config->OCNPolarity | OC_Config->OCHPolarity) << 0);

    /* Set the Capture Compare Register value */
    TMx->CC0A.H[0] = TMx->CC0B.H[0] = OC_Config->Pulse;

    // Enable Ouput OC
    switch(OC_Config->OCMode)
    {
    case TM_CH_Disable:
        TMx->OCCR0.W &= ~(TM_OCCR0_OC0_OE0_enable_w | TM_OCCR0_OC0N_OE_enable_w);
        break;
    case TM_CH_16bit_OutputCompare:
        TMx->OCCR0.W |= (TM_OCCR0_OC0_OE0_enable_w);
        break;
    case TM_CH_8bitx2_OutputCompare:
        TMx->OCCR0.W |= (TM_OCCR0_OC0_OE0_enable_w | TM_OCCR0_OC0N_OE_enable_w);
        break;
    case TM_CH_16bit_PWM:
        TMx->OCCR0.W |= (TM_OCCR0_OC0_OE0_enable_w | TM_OCCR0_OC0N_OE_enable_w);
        break;
    case TM_CH_8bitx2_PWM:
        TMx->OCCR0.W |= (TM_OCCR0_OC0_OE0_enable_w | TM_OCCR0_OC0N_OE_enable_w);
        break;
    case TM_CH_16bit_PWM_COMPLEMENT:
        TMx->OCCR0.W |= (TM_OCCR0_OC0_OE0_enable_w | TM_OCCR0_OC0N_OE_enable_w);
        break;
    case TM_CH_8bitx2_PWM_COMPLEMENT:
        TMx->OCCR0.W |= (TM_OCCR0_OC0_OE0_enable_w | TM_OCCR0_OC0N_OE_enable_w);
        break;

    default:
        break;

    }

}

/**
 *******************************************************************************
 * @brief       TMe Ouput Compare 1 configuration.
 * @param[in]   TMx : pointer to a TM_HandleTypeDef
 * @param[in]   OC_Config : The ouput configuration structure
 * @return      None
 * @note
 * @par         Example
 * @code
    TM_OC1_SetConfig(&mTM->Instance, sConfig);
 * @endcode
 *******************************************************************************
 */
static void TM_OC1_SetConfig(TM_Struct* TMx, TM_OC_InitTypeDef* OC_Config)
{
    /* Set the Output Idle state (Break state) */
    TMx->BS.W &= ~((TM_BS_STP0_STA_mask_w | TM_BS_STP0N_STA_mask_w) << 1);
    TMx->BS.W |= ((OC_Config->OCIdleState | OC_Config->OCNIdleState) << 1);

    /* Set the Output Idle state  */
    TMx->OSCR.W |= ((TM_OSCR_OS0_LCK_un_locked_w | OC_Config->OCIdleState |
                     TM_OSCR_OS0H_LCK_un_locked_w | OC_Config->OCHIdleState) << 1);

    /* Set the Output Polarity */
    TMx->OCCR1.W &= ~((TM_OCCR1_OC0_INV_mask_w | TM_OCCR1_OC0H_INV_mask_w | TM_OCCR1_OC0N_INV_mask_w) << 1);
    TMx->OCCR1.W |= ((OC_Config->OCPolarity | OC_Config->OCNPolarity | OC_Config->OCHPolarity) << 1);

    /* Set the Capture Compare Register value */
    TMx->CC1A.H[0] = TMx->CC1B.H[0] = OC_Config->Pulse;

    // Enable Ouput OC
    switch(OC_Config->OCMode)
    {
    case TM_CH_Disable:
        TMx->OCCR0.W &= ~(TM_OCCR0_OC1_OE0_enable_w | TM_OCCR0_OC1N_OE_enable_w);
        break;
    case TM_CH_16bit_OutputCompare:
        TMx->OCCR0.W |= (TM_OCCR0_OC1_OE0_enable_w);
        break;
    case TM_CH_8bitx2_OutputCompare:
        TMx->OCCR0.W |= (TM_OCCR0_OC1_OE0_enable_w | TM_OCCR0_OC1N_OE_enable_w);
        break;
    case TM_CH_16bit_PWM:
        TMx->OCCR0.W |= (TM_OCCR0_OC1_OE0_enable_w | TM_OCCR0_OC1N_OE_enable_w);
        break;
    case TM_CH_8bitx2_PWM:
        TMx->OCCR0.W |= (TM_OCCR0_OC1_OE0_enable_w | TM_OCCR0_OC1N_OE_enable_w);
        break;
    case TM_CH_16bit_PWM_COMPLEMENT:
        TMx->OCCR0.W |= (TM_OCCR0_OC1_OE0_enable_w | TM_OCCR0_OC1N_OE_enable_w);
        break;
    case TM_CH_8bitx2_PWM_COMPLEMENT:
        TMx->OCCR0.W |= (TM_OCCR0_OC1_OE0_enable_w | TM_OCCR0_OC1N_OE_enable_w);
        break;

    default:
        break;

    }

}

/**
 *******************************************************************************
 * @brief       TMe Ouput Compare 2 configuration.
 * @param[in]   TMx : pointer to a TM_HandleTypeDef
 * @param[in]   OC_Config : The ouput configuration structure
 * @return      None
 * @note
 * @par         Example
 * @code
    TM_OC2_SetConfig(&mTM->Instance, sConfig);
 * @endcode
 *******************************************************************************
 */
static void TM_OC2_SetConfig(TM_Struct* TMx, TM_OC_InitTypeDef* OC_Config)
{
    /* Set the Output Idle state (Break state) */
    TMx->BS.W &= ~((TM_BS_STP0_STA_mask_w | TM_BS_STP0N_STA_mask_w) << 2);
    TMx->BS.W |= ((OC_Config->OCIdleState | OC_Config->OCNIdleState) << 2);

    /* Set the Output Idle state  */
    TMx->OSCR.W |= ((TM_OSCR_OS0_LCK_un_locked_w | OC_Config->OCIdleState |
                     TM_OSCR_OS0H_LCK_un_locked_w | OC_Config->OCHIdleState) << 2);

    /* Set the Output Polarity */
    TMx->OCCR1.W &= ~((TM_OCCR1_OC0_INV_mask_w | TM_OCCR1_OC0H_INV_mask_w | TM_OCCR1_OC0N_INV_mask_w) << 2);
    TMx->OCCR1.W |= ((OC_Config->OCPolarity | OC_Config->OCNPolarity | OC_Config->OCHPolarity) << 2);

    /* Set the Capture Compare Register value */
    TMx->CC2A.H[0] = TMx->CC2B.H[0] = OC_Config->Pulse;

    // Enable Ouput OC
    switch(OC_Config->OCMode)
    {
    case TM_CH_Disable:
        TMx->OCCR0.W &= ~(TM_OCCR0_OC2_OE_enable_w | TM_OCCR0_OC2N_OE_enable_w);
        break;
    case TM_CH_16bit_OutputCompare:
        TMx->OCCR0.W |= (TM_OCCR0_OC2_OE_enable_w);
        break;
    case TM_CH_8bitx2_OutputCompare:
        TMx->OCCR0.W |= (TM_OCCR0_OC2_OE_enable_w | TM_OCCR0_OC2N_OE_enable_w);
        break;
    case TM_CH_16bit_PWM:
        TMx->OCCR0.W |= (TM_OCCR0_OC2_OE_enable_w | TM_OCCR0_OC2N_OE_enable_w);
        break;
    case TM_CH_8bitx2_PWM:
        TMx->OCCR0.W |= (TM_OCCR0_OC2_OE_enable_w | TM_OCCR0_OC2N_OE_enable_w);
        break;
    case TM_CH_16bit_PWM_COMPLEMENT:
        TMx->OCCR0.W |= (TM_OCCR0_OC2_OE_enable_w | TM_OCCR0_OC2N_OE_enable_w);
        break;
    case TM_CH_8bitx2_PWM_COMPLEMENT:
        TMx->OCCR0.W |= (TM_OCCR0_OC2_OE_enable_w | TM_OCCR0_OC2N_OE_enable_w);
        break;

    default:
        break;

    }

}

/**
 *******************************************************************************
 * @brief       TMe Ouput Compare 3 configuration.
 * @param[in]   TMx : pointer to a TM_HandleTypeDef
 * @param[in]   OC_Config : The ouput configuration structure
 * @return      None
 * @note
 * @par         Example
 * @code
    TM_OC3_SetConfig(&mTM->Instance, sConfig);
 * @endcode
 *******************************************************************************
 */
static void TM_OC3_SetConfig(TM_Struct* TMx, TM_OC_InitTypeDef* OC_Config)
{
    /* Set the Output Idle state (Break state) */
    TMx->BS.W &= ~((TM_BS_STP0_STA_mask_w | TM_BS_STP0N_STA_mask_w) << 3);
    TMx->BS.W |= ((OC_Config->OCIdleState | OC_Config->OCNIdleState) << 3);

    /* Set the Output Idle state  */
    TMx->OSCR.W |= ((TM_OSCR_OS0_LCK_un_locked_w | OC_Config->OCIdleState |
                     TM_OSCR_OS0H_LCK_un_locked_w | OC_Config->OCHIdleState) << 3);

    /* Set the Output Polarity */
    TMx->OCCR1.W &= ~((TM_OCCR1_OC0_INV_mask_w | TM_OCCR1_OC0H_INV_mask_w | TM_OCCR1_OC0N_INV_mask_w) << 3);
    TMx->OCCR1.W |= ((OC_Config->OCPolarity | OC_Config->OCNPolarity | OC_Config->OCHPolarity) << 3);

    /* Set the Capture Compare Register value */
    TMx->CC3A.H[0] = TMx->CC3B.H[0] = OC_Config->Pulse;

    // Enable Ouput OC
    switch(OC_Config->OCMode)
    {
    case TM_CH_Disable:
        TMx->OCCR0.W &= ~(TM_OCCR0_OC3_OE_enable_w);
        break;
    case TM_CH_16bit_OutputCompare:
        TMx->OCCR0.W |= (TM_OCCR0_OC3_OE_enable_w);
        break;
    case TM_CH_8bitx2_OutputCompare:
        TMx->OCCR0.W |= (TM_OCCR0_OC3_OE_enable_w);
        break;
    case TM_CH_16bit_PWM:
        TMx->OCCR0.W |= (TM_OCCR0_OC3_OE_enable_w);
        break;
    case TM_CH_8bitx2_PWM:
        TMx->OCCR0.W |= (TM_OCCR0_OC3_OE_enable_w);
        break;
    case TM_CH_16bit_PWM_COMPLEMENT:
        TMx->OCCR0.W |= (TM_OCCR0_OC3_OE_enable_w);
        break;
    case TM_CH_8bitx2_PWM_COMPLEMENT:
        TMx->OCCR0.W |= (TM_OCCR0_OC3_OE_enable_w);
        break;

    default:
        break;

    }

}


/**
 *******************************************************************************
 * @brief       Time Slave configuration.
 * @param[in]   mTM : pointer to a TM_HandleTypeDef structure that contains
 *                    the configuration information for TM module.
 * @param[in]   sSlaveConfig: The slave configuration structure
 * @return      MID_StatusTypeDef
 *******************************************************************************
 */
static void TM_SlaveTimer_SetConfig(TM_HandleTypeDef* mTM, TM_SlaveConfigTypeDef* sSlaveConfig)
{
    uint32_t tmp;

    tmp = mTM->Instance->TRG.W;

    if((sSlaveConfig->InputTrigger & TM_TRG_TRG_MUX_mask_w) != TM_TRG_TRG_MUX_itr_w)
    {
        tmp &= ~(TM_TRG_TRG_MUX_mask_w | TM_TRG_TRGI2_MDS_mask_w | TM_TRG_TRGI_MDS_mask_w);

        tmp |= (sSlaveConfig->InputTrigger & ~TM_TRG_ITR_MUX_mask_w) | \
               (sSlaveConfig->SlaveMode);
    }
    else
    {
        tmp &= ~(TM_TRG_ITR_MUX_mask_w | TM_TRG_TRG_MUX_mask_w | TM_TRG_TRGI2_MDS_mask_w | \
                 TM_TRG_TRGI_MDS_mask_w);

        tmp |= (sSlaveConfig->InputTrigger)                         | \
               (sSlaveConfig->SlaveMode);
    }

    mTM->Instance->TRG.W = tmp;

}


/**
 *******************************************************************************
 * @brief       Enables or disables the TM Capture Compare Channel x..
 * @param[in]   TMx : pointer to a TM_Struct
 * @param[in]   Channel : specifies Timer channel selection
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @param[in]   ChannelMode : specifies Timer channel mode
 *  @arg\b      TM_CH_Disable : Disable channel mode (No operation)
 *  @arg\b      TM_CH_InputCapture : Capture mode
 *  @arg\b      TM_CH_16bit_OutputCompare : 16bit Output Compare mode
 *  @arg\b      TM_CH_8bitx2_OutputCompare : 8bit Output Compare mode
 *  @arg\b      TM_CH_16bit_PWM : 16bit PWM mode
 *  @arg\b      TM_CH_8bitx2_PWM : 8bitx2 PWM mode
 *  @arg\b      TM_CH_16bit_PWM_COMPLEMENT : 16bit PWM mode with complement output
 *  @arg\b      TM_CH_8bitx2_PWM_COMPLEMENT : 8bitx2 PWM mode with complement output
 * @return      None
 * @note
 * @par         Example
 * @code
    TM_HandleTypeDef mTM;

    TM_CCxChannelCmd(&mTM, MID_TM_Channel3, TM_CH_InputCapture);
 * @endcode
 *******************************************************************************
 */
void TM_CCxChannelCmd(TM_Struct* TMx, uint32_t Channel, uint32_t ChannelMode)
{
    uint32_t tmp = 0U;

    tmp = TM_CCMDS_CC0_MDS_mask_w << (Channel * 4);

    /* Reset the CCxE Bit */
    TMx->CCMDS.W &= ~tmp;

    /* Set or reset the CCxE Bit */
    TMx->CCMDS.W |= (uint32_t)(ChannelMode << (Channel * 4));


}


/**
 *******************************************************************************
 * @brief       Set the dead-time source clock divider. (Only foe TM36)
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   DeadTimeDivider : Timer internal dead time clock divider.
 *  @arg\b      MID_TM_CKDTG_DIV1 : divider by 1
 *  @arg\b      MID_TM_CKDTG_DIV2 : divider by 2
 *  @arg\b      MID_TM_CKDTG_DIV4 : divider by 4
 *  @arg\b      MID_TM_CKDTG_DIV8 : divider by 8
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_OC_SetDeadTimeDivider(&mTM36, MID_TM_CKDTG_DIV1);
    MID_TM_OC_SetDeadTime(&mTM36, DeadTime_Set);
 * @endcode
 *******************************************************************************
 */
void MID_TM_OC_SetDeadTimeDivider(TM_HandleTypeDef* mTM,  uint32_t DeadTimeDivider)
{
    mTM->Instance->CLK.W &= ~(TM_CLK_DTG_DIV_mask_w);
    mTM->Instance->CLK.W |= DeadTimeDivider;
}



/**
 *******************************************************************************
 * @brief       Set the dead-time delay. (Only foe TM36)
 * @param[in]   mTM : pointer to a TM_HandleTypeDef
 * @param[in]   DeadTime : DeadTime between Min_Data=0 to Max_Data=255
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    MID_TM_OC_SetDeadTimeDivider(&mTM36, MID_TM_CKDTG_DIV1);
    MID_TM_OC_SetDeadTime(&mTM36, DeadTime_Set);
 * @endcode
 *******************************************************************************
 */
void MID_TM_OC_SetDeadTime(TM_HandleTypeDef* mTM,  uint32_t DeadTime)
{
    mTM->Instance->PWM.W &= ~(TM_PWM_DTG_DY_mask_w);
    mTM->Instance->PWM.W |= (DeadTime << 8);
}

///@}


