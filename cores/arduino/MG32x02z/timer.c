
/**
 ******************************************************************************
 *
 ******************************************************************************
 * @file    timer.c
 * @author  cuij
 * @version V1.0.0
 * @date    11-11-2022
 * @brief   The  code is that use adapted to Arduino interface
 *
 * @par         Project
 *              MG32x02z
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2022 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 * 
 ******************************************************************************* 
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2022 megawin Technology Co., Ltd.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
 *******************************************************************************
 */
/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32f0xx_system
  * @{
  */

/** @addtogroup STM32F0xx_System_Private_Includes
  * @{
  */
#include "Arduino.h"


#include "MG32x02z.h"
#include "system_MG32x02z.h"
#include "MG32x02z_GPIO_DRV.h"

#include "MG32x02z_TM_DRV.h"
#include "MG32x02z_TM_MID.h"


#include "hw_config.h"
#include "timer.h"
#include "digital_io.h"
#include "clock.h"
//#include "analog.h"

#ifdef __cplusplus
 extern "C" {
#endif

/**
  * @}
  */

/** @addtogroup 
  * @{
  */

/**
  * @}
  */

/** @addtogroup 
  * @{
  */

/**
  * @}
  */

/** @addtogroup 
* @{
*/

extern TM_HandleTypeDef         mTM00;
extern TM_HandleTypeDef         mTM01;
extern TM_HandleTypeDef         mTM10;
extern TM_HandleTypeDef         mTM16;
extern TM_HandleTypeDef         mTM20;
extern TM_HandleTypeDef         mTM26;
extern TM_HandleTypeDef         mTM36;


static void TIMx_PeriodElapsedCallback(timer_id_e timer_id);
static timer_id_e get_timer_id_from_handle(TM_HandleTypeDef *htim);

static int CalTime (  timer_id_e timer_id,     uint32_t frequency, 
                      uint16_t*  clockDiv,     uint16_t* lowPeriod,   uint16_t* highPeriod );
/**
  * @}
  */

/** @addtogroup 
  * @{
  */

static void TM00_clock_enable(void)   { MID_TM_Base_Start_IT(&mTM00); }
static void TM00_clock_reset(void)    { MID_TM_Base_Stop_IT(&mTM00); }
static void TM01_clock_enable(void)   { MID_TM_Base_Start_IT(&mTM01); }
static void TM01_clock_reset(void)    { MID_TM_Base_Stop_IT(&mTM01); }
static void TM10_clock_enable(void)   { MID_TM_Base_Start_IT(&mTM10); }
static void TM10_clock_reset(void)    { MID_TM_Base_Stop_IT(&mTM10); }
static void TM16_clock_enable(void)   { MID_TM_Base_Start_IT(&mTM16); }
static void TM16_clock_reset(void)    { MID_TM_Base_Stop_IT(&mTM16); }
static void TM20_clock_enable(void)   { MID_TM_Base_Start_IT(&mTM20); }
static void TM20_clock_reset(void)    { MID_TM_Base_Stop_IT(&mTM20); }
static void TM26_clock_enable(void)   { MID_TM_Base_Start_IT(&mTM26); }
static void TM26_clock_reset(void)    { MID_TM_Base_Stop_IT(&mTM26); }
static void TM36_clock_enable(void)   { MID_TM_Base_Start_IT(&mTM36); }
static void TM36_clock_reset(void)    { MID_TM_Base_Stop_IT(&mTM36); }


/**
  * @}
  */

/** @addtogroup 
  * @{
  */

/// @brief timer caracteristics
//extern analog_config_str g_analog_config[NB_ANALOG_CHANNELS];
//static TM_HandleTypeDef g_TimerHandle[NB_TIMER_MANAGED];

static timer_conf_t g_timer_config[NB_TIMER_MANAGED] = 
{
  {
    //TIMER ID and IRQ TIM00
    .timInstance = NULL, 
    .irqtype     = TM0x_IRQn,
    .irqHandle   = TIMx_PeriodElapsedCallback,  
    .User_irqHandle   = NULL,
    .timer_mode  = TIMER_PWM,
    //timer clock init
    .timer_clock_init  = TM00_clock_enable,
    //timer clock reset
    .timer_clock_reset = TM00_clock_reset,
    //timer prescaler limit : 8 or 16 bits
    .prescalerLimit    = bits_16,
    //toggle pin configuration
    .toggle_pin = { .port = NULL },
    .configured = 0
  },
  {
    //TIMER ID and IRQ TM01
    .timInstance = NULL, 
    .irqtype     = TM0x_IRQn,
    .irqHandle   = TIMx_PeriodElapsedCallback,
    .User_irqHandle   = NULL,
    .timer_mode  = TIMER_PWM,
    //timer clock init
    .timer_clock_init  = TM01_clock_enable,
    //timer clock reset
    .timer_clock_reset = TM01_clock_reset,
    //timer prescaler limit : 8 or 16 bits
    .prescalerLimit    = bits_16,
    //toggle pin configuration
    .toggle_pin = { .port = NULL },
    .configured = 0
  },

  {
    //TIMER ID and IRQ TM10
    .timInstance = NULL,
    .irqtype     = TM10_IRQn,
    .irqHandle   = TIMx_PeriodElapsedCallback,
    .User_irqHandle   = NULL,
    .timer_mode  = TIMER_PWM,
    //timer clock init
    .timer_clock_init = TM10_clock_enable,
    //timer clock reset
    .timer_clock_reset = TM10_clock_reset,
    //timer prescaler limit : 8 or 16 bits
    .prescalerLimit    = bits_32,
    //toggle pin configuration
    .toggle_pin = { .port = NULL },
    .configured = 0
  },
  {
    //TIMER ID and IRQ TM16
    .timInstance = NULL, 
    .irqtype     = TM1x_IRQn,
    .irqHandle   = TIMx_PeriodElapsedCallback,
    .User_irqHandle   = NULL,
    .timer_mode  = TIMER_PWM,
    //timer clock init
    .timer_clock_init  = TM16_clock_enable,
    //timer clock reset
    .timer_clock_reset = TM16_clock_reset,
    //timer prescaler limit : 8 or 16 bits
    .prescalerLimit    = bits_16,
    //toggle pin configuration
    .toggle_pin = { .port = NULL },
    .configured = 0
  },
  {
    //TIMER ID and IRQ TM20
    .timInstance = NULL, 
    .irqtype     = TM20_IRQn,
    .irqHandle   = TIMx_PeriodElapsedCallback,
    .User_irqHandle   = NULL,
    .timer_mode  = TIMER_RESERVED,
    //timer clock init
    .timer_clock_init  = TM20_clock_enable,
    //timer clock reset
    .timer_clock_reset = TM20_clock_reset,
    //timer prescaler limit : 8 or 16 bits
    .prescalerLimit    = bits_16,
    //toggle pin configuration
    .toggle_pin = { .port = NULL },
    .configured = 0
  },
  {
    //TIMER ID and IRQ TM26
    .timInstance = NULL, 
    .irqtype     = TM2x_IRQn,
    .irqHandle   = TIMx_PeriodElapsedCallback,
    .User_irqHandle   = NULL,
    .timer_mode  = TIMER_OTHER,
    //timer clock init
    .timer_clock_init  = TM26_clock_enable,
    //timer clock reset
    .timer_clock_reset = TM26_clock_reset,
    //timer prescaler limit : 8 or 16 bits
    .prescalerLimit    = bits_16,
    //toggle pin configuration
    .toggle_pin = { .port = NULL },
    .configured = 0
  },
  {
    //TIMER ID and IRQ TM36
    .timInstance = NULL, 
    .irqtype     = TM3x_IRQn,
    .irqHandle   = TIMx_PeriodElapsedCallback,
    .User_irqHandle   = NULL,
    .timer_mode  = TIMER_OTHER,
    //timer clock init
    .timer_clock_init  = TM36_clock_enable,
    //timer clock reset
    .timer_clock_reset = TM36_clock_reset,
    //timer prescaler limit : 8 or 16 bits
    .prescalerLimit    = bits_16,
    //toggle pin configuration
    .toggle_pin = { .port = NULL },
    .configured = 0
  }
};



/*
extern TM_HandleTypeDef         mTM00;
extern TM_HandleTypeDef         mTM01;
extern TM_HandleTypeDef         mTM10;
extern TM_HandleTypeDef         mTM16;
extern TM_HandleTypeDef         mTM20;
extern TM_HandleTypeDef         mTM26;
extern TM_HandleTypeDef         mTM36;
*/

void timer_cfg_init(void)
{
    mTM00.Instance  = TM00;
    g_timer_config[TIM00_E].timInstance = &mTM00;
    g_timer_config[TIM00_E].irqtype     = TM0x_IRQn;

    mTM01.Instance  = TM01;
    g_timer_config[TIM01_E].timInstance = &mTM01;
    g_timer_config[TIM01_E].irqtype     = TM0x_IRQn;
    
    mTM10.Instance  = TM10;
    g_timer_config[TIM10_E].timInstance = &mTM10;
    g_timer_config[TIM10_E].irqtype     = TM10_IRQn;
    
    mTM16.Instance  = TM16;
    g_timer_config[TIM16_E].timInstance = &mTM16;
    g_timer_config[TIM16_E].irqtype     = TM1x_IRQn;
    
    mTM20.Instance  = TM20;
    g_timer_config[TIM20_E].timInstance = &mTM20;
    g_timer_config[TIM20_E].irqtype     = TM20_IRQn;
    
    mTM26.Instance  = TM26;
    g_timer_config[TIM26_E].timInstance = &mTM26;
    g_timer_config[TIM26_E].irqtype     = TM2x_IRQn;
    
    mTM36.Instance  = TM36;
    g_timer_config[TIM36_E].timInstance = &mTM36;
    g_timer_config[TIM36_E].irqtype     = TM3x_IRQn;
}

/**
  * @}
  */

/**
  * @brief  This function returns the corresponding timer id function of the
  *         handle
  * @param  htim : one of the defined
  * @retval the TIMx id
  */
timer_id_e get_timer_id_from_handle(TM_HandleTypeDef *htim)
{
    timer_id_e timer_id = NB_TIMER_MANAGED;
    uint8_t i;
    for(i = 0; i<NB_TIMER_MANAGED; i++)
    {
        if( g_timer_config[i].timInstance == htim ) 
        {
            timer_id = i;
            break;
        }
    }
    return timer_id;
}


/**
  * @brief  Enable the timer clock
  * @param  htim : one of the defined timer
  * @retval None
  */
void timer_enable_clock(TM_HandleTypeDef *htim)
{
    uint8_t i = 0;
    for(i = 0; i < NB_TIMER_MANAGED; i++) 
    {
        if( g_timer_config[i].timInstance == htim ) 
        {
            g_timer_config[i].timer_clock_init();
            g_timer_config[i].configured = 1;
            break;
        }
    }
}

/**
  * @brief  Disable the timer clock
  * @param  htim : one of the defined timer
  * @retval None
  */
void timer_disable_clock(TM_HandleTypeDef *htim)
{
    uint8_t i = 0;
    for(i = 0; i < NB_TIMER_MANAGED; i++)
    {
        if(g_timer_config[i].timInstance == htim)
        {
            if(NULL != g_timer_config[i].timer_clock_reset)
            {
                g_timer_config[i].timer_clock_reset();
            }
            g_timer_config[i].configured = 0;
            break;
        }
    }
}

/**
  * @brief  Find the first timer not used
  * @param  none
  * @retval The id of the first timer not used if not the number of id.
  */
timer_id_e getInactiveTimer(void)
{
    timer_id_e timer_id = NB_TIMER_MANAGED;
    uint8_t i = 0;
    for(i = 0; i < NB_TIMER_MANAGED; i++)
    {
        if((g_timer_config[i].configured == 0) 
         &&(g_timer_config[i].timer_mode == TIMER_OTHER) )
        {
            timer_id = i;
            break;
        }
    }

    return timer_id;
}

/**
  * @brief  Search the timer associate to a pin
  * @param  port : port pointer
  * @param  pin : pin number
  * @retval The timer id
  */
timer_id_e isPinAssociateToTimer(GPIO_Struct *port, uint32_t pin)
{
    uint8_t i = 0;
    timer_id_e timer_id = NB_TIMER_MANAGED;

    for(i = 0; i < NB_TIMER_MANAGED; i++)
    {
        if((g_timer_config[i].toggle_pin.port == port) 
         &&(g_timer_config[i].toggle_pin.pin == pin)  ) 
        {
            timer_id = i;
            break;
        }
    }
    return timer_id;
}

////=====================================================================
/**
  * @brief  TIMER Initialization - clock init and nvic init
  * @param  htim_base : one of the defined timer
  * @retval None
  */
void TIM_Base_MspInit(TM_HandleTypeDef *htim_base)
{
    timer_id_e timer_id;

    timer_id = get_timer_id_from_handle(htim_base);
    if(NB_TIMER_MANAGED <= timer_id) 
    {
        return;
    }

    timer_enable_clock(htim_base);

    MID_NVIC_SetPriority(g_timer_config[timer_id].irqtype, 3);

    MID_NVIC_EnableIRQ(g_timer_config[timer_id].irqtype);
}

/**
  * @brief  TIMER Deinitialization - clock and nvic
  * @param  htim_base : one of the defined timer
  * @retval None
  */
void TIM_Base_MspDeInit(TM_HandleTypeDef *htim_base)
{
    timer_id_e timer_id;

    timer_id = get_timer_id_from_handle(htim_base);
    if(NB_TIMER_MANAGED == timer_id)
    {
        return;
    }

    timer_disable_clock(htim_base);

    MID_NVIC_DisableIRQ(g_timer_config[timer_id].irqtype);
}


/**
  * @brief  This function will set the timer to the required value
  * @param  timer_id : timer_id_e
  * @param  frequency : frequency for timer
  * @retval None
  */
void TimerHandleInit(timer_id_e timer_id, uint16_t frequency )
{
    uint16_t  clockDiv;
    uint16_t  lowPeriod;
    uint16_t  highPeriod;
    
    TM_ClockConfigTypeDef CKConfig;
    

    if(timer_id >= NB_TIMER_MANAGED)
    {
        return;
    }

    CalTime (  timer_id,     frequency, 
               &clockDiv,  &lowPeriod,   &highPeriod );

    
    g_timer_config[timer_id].timInstance->Init.TM_Period         = lowPeriod;
    g_timer_config[timer_id].timInstance->Init.TM_Prescaler      = highPeriod;
    g_timer_config[timer_id].timInstance->Init.TM_CounterMode    = TM_CASCADE_UP;

    if( MID_TM_Base_Init( g_timer_config[timer_id].timInstance) != MID_SUCCESS )
    {
        return;
    }

    switch (clockDiv)
    {
        case 1:
            CKConfig.TM_INTClockDivision    = TM_INTERNALCLOCK_DIVDER_DIV1;
            break;
        case 2:
            CKConfig.TM_INTClockDivision    = TM_INTERNALCLOCK_DIVDER_DIV2;
            break;
        case 4:
            CKConfig.TM_INTClockDivision    = TM_INTERNALCLOCK_DIVDER_DIV4;
            break;
        case 8:
            CKConfig.TM_INTClockDivision    = TM_INTERNALCLOCK_DIVDER_DIV8;
            break;
        default:
            CKConfig.TM_INTClockDivision    = TM_INTERNALCLOCK_DIVDER_DIV1;
            break;
    }
    // ------------------------------------------------------------------------
    // 2.Initial clock.
    // ------------------------------------------------------------------------
    CKConfig.TM_ClockSource         = TM_INTERNAL_CLOCK;
    CKConfig.TM_ExternalClockSource = 0;
    CKConfig.TM_InternalClockSource = TM_INTERNALCLOCK_PROC;
    MID_TM_ConfigClockSource( g_timer_config[timer_id].timInstance, &CKConfig);  

    // ------------------------------------------------------------------------
    // 3.Enable TMx and IT.
    // ------------------------------------------------------------------------
    MID_NVIC_EnableIRQ( g_timer_config[timer_id].irqtype );

    if( MID_TM_Base_Start_IT( g_timer_config[timer_id].timInstance ) != MID_SUCCESS)
    {
        return;
    }

}

/**
  * @brief  This function will reset the timer
  * @param  timer_id : timer_id_e
  * @retval None
  */
void TimerHandleDeinit(timer_id_e timer_id)
{
    MID_TM_Base_DeInit( g_timer_config[timer_id].timInstance );
    MID_TM_Base_Stop_IT( g_timer_config[timer_id].timInstance );
}

/**
  * @brief  This function will set the timer to generate pulse in interrupt mode with a particular duty cycle
  * @param  timer_id : timer_id_e
  * @param  period : timer period in microseconds
  * @param  pulseWidth : pulse width in microseconds
  * @param  irqHandle : interrupt routine to call
  * @retval None
  */
void TimerPulseInit(timer_id_e timer_id, uint16_t period, uint16_t pulseWidth, void (*irqHandle)(timer_id_e))
{
    TM_TimeBaseInitTypeDef   TM_TimeBase_InitStruct;
    TM_OC_InitTypeDef        sConfig;
    TM_ClockConfigTypeDef    CKConfig;

    if(timer_id >= NB_TIMER_MANAGED)
    {
        return;
    }
    if( g_timer_config[timer_id].configured == 1 ) 
    {
        return;
    }
    TM_DeInit( g_timer_config[timer_id].timInstance->Instance );

    // ----------------------------------------------------
    // 1.TimeBase structure initial
    TM_TimeBaseStruct_Init(&TM_TimeBase_InitStruct);

    // modify parameter
    TM_TimeBase_InitStruct.TM_MainClockDirection    = TM_UpCount;
    TM_TimeBase_InitStruct.TM_Period                = period; 
    TM_TimeBase_InitStruct.TM_Prescaler             = (uint32_t)(MID_CSC_GetCK_HSFreq() / 1000000) - 1;
    TM_TimeBase_InitStruct.TM_CounterMode           = Cascade;

    TM_TimeBase_Init( g_timer_config[timer_id].timInstance->Instance, &TM_TimeBase_InitStruct);

    //min pulse = 1us - max pulse = 65535us
    g_timer_config[timer_id].timInstance->Init.TM_Period            = period;
    g_timer_config[timer_id].timInstance->Init.TM_Prescaler         = (uint32_t)(MID_CSC_GetCK_HSFreq() / 1000000) - 1;
    g_timer_config[timer_id].timInstance->Init.TM_CounterMode       = TM_CASCADE_UP;
    g_timer_config[timer_id].User_irqHandle                         = irqHandle;


    MID_TM_OC_Struct_Init(&sConfig);
    sConfig.OCMode  = TM_CH_16bit_OutputCompare;
    sConfig.Pulse   = pulseWidth;                          // duty cycle of channel0


    if( MID_TM_OC_Init( g_timer_config[timer_id].timInstance ) != MID_SUCCESS ) 
    {
        return;
    }


    // ------------------------------------------------------------------------
    // 2.Clock initial.
    // ------------------------------------------------------------------------
    CKConfig.TM_ClockSource         = TM_INTERNAL_CLOCK;
    CKConfig.TM_ExternalClockSource = 0;
    CKConfig.TM_INTClockDivision    = TM_INTERNALCLOCK_DIVDER_DIV1;
    CKConfig.TM_InternalClockSource = TM_INTERNALCLOCK_PROC;
    if( MID_TM_ConfigClockSource(&mTM20, &CKConfig) != MID_SUCCESS )
    {
        return;
    }


    if( MID_TM_OC_ConfigChannel( g_timer_config[timer_id].timInstance,   &sConfig,   MID_TM_Channel0) != MID_SUCCESS )
    {
        return;
    }
    
    MID_NVIC_EnableIRQ(g_timer_config[timer_id].irqtype);
    
    if(MID_TM_OC_Start_IT( g_timer_config[timer_id].timInstance,  MID_TM_Channel0) != MID_SUCCESS)
    {
        return;
    }
}

////=====================================================================

/**
  * @brief  This function will reset the pulse generation
  * @param  timer_id : timer_id_e
  * @retval None
  */
void TimerPulseDeinit(timer_id_e timer_id)
{
    if(timer_id >= NB_TIMER_MANAGED)
    {
        return;
    }
    g_timer_config[timer_id].User_irqHandle = NULL;

    if( MID_TM_OC_DeInit( g_timer_config[timer_id].timInstance) != MID_SUCCESS ) 
    {
        return;
    }
    TM_DeInit( g_timer_config[timer_id].timInstance->Instance );

    MID_TM_OC_Stop_IT( g_timer_config[timer_id].timInstance, MID_TM_Channel0 );
//    MID_TM_OC_Stop_IT( g_timer_config[timer_id].timInstance, MID_TM_Channel2 );
//    MID_TM_OC_Stop_IT( g_timer_config[timer_id].timInstance, MID_TM_Channel3 );
}


/**
  * @brief  Initializes the TIM Output Compare MSP.
  * @param  htim: TIM handle
  * @retval None
  */
void TIM_OC_MspInit(TM_HandleTypeDef *htim)
{
    timer_id_e timer_id;

    timer_id = get_timer_id_from_handle(htim);
    if(NB_TIMER_MANAGED == timer_id) 
    {
        return;
    }

    timer_enable_clock(htim);
    MID_NVIC_SetPriority(g_timer_config[timer_id].irqtype, 3);
    MID_NVIC_EnableIRQ(g_timer_config[timer_id].irqtype);
}

/**
  * @brief  DeInitialize TIM Output Compare MSP.
  * @param  htim: TIM handle
  * @retval None
  */
void TIM_OC_MspDeInit(TM_HandleTypeDef *htim)
{
    timer_id_e timer_id;

    timer_id = get_timer_id_from_handle(htim);
    if(NB_TIMER_MANAGED == timer_id)
    {
        return;
    }

    timer_disable_clock(htim);
    MID_NVIC_DisableIRQ(g_timer_config[timer_id].irqtype);
}


/**
  * @brief  Period elapsed callback in non-blocking mode
  * @param  timer_id : id of the timer
  * @retval None
  */
void TIMx_PeriodElapsedCallback(timer_id_e timer_id)
{
    if(g_timer_config[timer_id].toggle_pin.port != NULL)
    {
        if(g_timer_config[timer_id].toggle_pin.count > 0)
        {
            g_timer_config[timer_id].toggle_pin.count--;

            if(g_timer_config[timer_id].toggle_pin.state == 0)
            {
                g_timer_config[timer_id].toggle_pin.state = 1;
                digital_io_write(g_timer_config[timer_id].toggle_pin.port,
                                 g_timer_config[timer_id].toggle_pin.pin, 1);
            }
            else
            {
                g_timer_config[timer_id].toggle_pin.state = 0;
                digital_io_write(g_timer_config[timer_id].toggle_pin.port,
                                 g_timer_config[timer_id].toggle_pin.pin, 0);
            }
        }
        else if(g_timer_config[timer_id].toggle_pin.count == -1)
        {
            if(g_timer_config[timer_id].toggle_pin.state == 0)
            {
                g_timer_config[timer_id].toggle_pin.state = 1;
                digital_io_write(g_timer_config[timer_id].toggle_pin.port,
                                 g_timer_config[timer_id].toggle_pin.pin, 1);
            }
            else 
            {
                g_timer_config[timer_id].toggle_pin.state = 0;
                digital_io_write(g_timer_config[timer_id].toggle_pin.port,
                                 g_timer_config[timer_id].toggle_pin.pin, 0);
            }
        }
        else
        {
            digital_io_write( g_timer_config[timer_id].toggle_pin.port,
                              g_timer_config[timer_id].toggle_pin.pin, 0);
        }
    }
}



/////=======================================================================
/**
  * @brief  Period elapsed callback in non-blocking mode
  * @param  htim : TIM handle
  * @retval None
  */
void TIM_PeriodElapsedCallback(TM_HandleTypeDef *htim)
{
    timer_id_e timer_id = get_timer_id_from_handle(htim);
    if(NB_TIMER_MANAGED == timer_id)
    {
        return;
    }

    if(g_timer_config[timer_id].irqHandle != NULL)
    {
        g_timer_config[timer_id].irqHandle(timer_id);
    }
    
    
    if(g_timer_config[timer_id].User_irqHandle != NULL)
    {
        g_timer_config[timer_id].User_irqHandle(timer_id);
    }
}
/////=======================================================================
static int CalTime (  timer_id_e timer_id,     uint32_t frequency, 
                      uint16_t*  clockDiv,     uint16_t* lowPeriod,   uint16_t* highPeriod )
{
    int i;
    uint32_t modResult;
    uint32_t remainder = 0;
    uint32_t Lastremainder = 0;
    uint32_t Cnt = 0;
    
    uint32_t period; 
    period = (uint32_t)( (MID_CSC_GetCK_HSFreq() / frequency) ); 

    *clockDiv   = 6;
    *lowPeriod  = 65535;
    *highPeriod =  65535;

    if( period <= 256 )
    {
        *clockDiv = 1;
        *lowPeriod = period-1;
        *highPeriod = 0;
        return 0;
    }
    
    if( ( timer_id != TIM00_E) && (timer_id != TIM01_E) )
    {
        if( (period)<65536 )
        {
            *clockDiv = 1;
            *lowPeriod = (uint16_t)(period)-1;
            *highPeriod = 0;
            return 0;
        }

        for( i =0; i<4; i++  )
        {
            for( Cnt=1;  Cnt<=65536;  Cnt++ )
            {
                modResult = (period)/(Cnt<<i);
                if( modResult > 65536 )
                {
                    continue;
                }

                remainder = period % (Cnt<<i);
                if( remainder == 0 )
                {
                    *clockDiv   =  (1<<i);
                    *lowPeriod  =  Cnt-1;
                    *highPeriod =  modResult-1;
                    return 0;
                }
                else 
                {
                    remainder = ((Cnt<<i)/remainder);
                    if( Lastremainder < remainder  )
                    {
                        Lastremainder  = remainder;
                        *clockDiv   =  (1<<i);
                        *lowPeriod  =  Cnt-1;
                        *highPeriod =  modResult-1;
                    }
                }
            }
        }
        return 0;
    }

    //TIM00_E TIM01_E
    //能在8倍以内解决问题
    for( i =0; i<4; i++  )
    {
        for( Cnt=1;  Cnt<=256;  Cnt++ )
        {
            modResult = (period)/(Cnt<<i);
            if( modResult > 255 )
            {
                continue;
            }

            remainder = period % (Cnt<<i);
            if( remainder == 0 )
            {
                *clockDiv   =  (1<<i);
                *lowPeriod  =  Cnt-1;
                *highPeriod =  modResult-1;
                return 0;
            }
            else 
            {
                remainder = ((Cnt<<i)/remainder);
                if( Lastremainder < remainder  )
                {
                    Lastremainder  = remainder;
                    *clockDiv   =  (1<<i);
                    *lowPeriod  =  Cnt-1;
                    *highPeriod =  modResult-1;
                }
            }
        }
    }
    return 0;
}

/**
  * @brief  This function will set the tone timer to the required value and
  *         configure the pin to toggle.
  * @param  port : pointer to GPIO_TypeDef
  * @param  pin : pin number to toggle
  * @param  frequency : toggle frequency (in hertz)
  * @param  duration : toggle time
  * @retval None
  */
void TimerPinInit(GPIO_Struct *port, uint32_t pin,  uint32_t afs, uint32_t frequency, uint32_t duration)
{
/*
    uint16_t  clockDiv;
    uint16_t  lowPeriod;
    uint16_t  highPeriod;
    
    
    uint8_t end = 0;
    uint32_t prescaler = 1;
    uint32_t period = 0;
*/
    timer_id_e timer_id;

    timer_id = isPinAssociateToTimer(port,pin);

    if(timer_id == NB_TIMER_MANAGED)
    {
        timer_id = getInactiveTimer();
        if(timer_id == NB_TIMER_MANAGED)
        {
            return;
        }
    }

    if(frequency > MAX_FREQ)
    {
        return;
    }

    g_timer_config[timer_id].toggle_pin.port = port;
    g_timer_config[timer_id].toggle_pin.pin = pin;
    g_timer_config[timer_id].toggle_pin.state = 0;



    //Calculate the toggle count
    if (duration > 0) 
    {
         //div2 for pin turn up and down
        g_timer_config[timer_id].toggle_pin.count = ((frequency * duration) / 1000) * 2;
    }
    else
    {
        g_timer_config[timer_id].toggle_pin.count = -1;
    }

    digital_io_init( port,  pin,   afs,  GPIO_MODE_PUSHPULL_O,   GPIO_NOPULLUP);

     //div2 for pin turn up and down
    g_timer_config[timer_id].irqHandle = TIMx_PeriodElapsedCallback;
    TimerHandleInit(timer_id,   frequency/2 );
}
/////=======================================================================



/**
  * @brief  This function will reset the tone timer
  * @param  port : pointer to port
  * @param  pin : pin number to toggle
  * @retval None
  */
void TimerPinDeinit(GPIO_Struct *port, uint32_t pin)
{
    timer_id_e timer_id = isPinAssociateToTimer(port,pin);

    if(timer_id < NB_TIMER_MANAGED)
    {
        TimerHandleDeinit(timer_id);
        g_timer_config[timer_id].toggle_pin.port = NULL;
        g_timer_config[timer_id].toggle_pin.pin = 0;
        g_timer_config[timer_id].toggle_pin.count = 0;
        g_timer_config[timer_id].toggle_pin.state = 0;
    }
}

/**
  * @brief  Get the counter value.
  * @param  timer_id : id of the timer
  * @retval Counter value
  */
uint32_t getTimerCounter(timer_id_e timer_id)
{
    if(timer_id < NB_TIMER_MANAGED)
    {
        return TM_GetCounter( g_timer_config[timer_id].timInstance->Instance );
    }
    else
    {
        return 0;
    }
}

/**
  * @brief  Set the counter value.
  * @param  timer_id : id of the timer
  * @param  value : counter value
  * @retval None
  */
void setTimerCounter(timer_id_e timer_id, uint32_t value)
{
    if(timer_id < NB_TIMER_MANAGED)
    {
        TM_Counter_Config( g_timer_config[timer_id].timInstance->Instance,  value,  value );
    }
}



/**
  * @brief  Set the TIM Capture Compare Register value.
  * @param  timer_id : id of the timer
  * @param  channel : TIM Channels to be configured.
                      where x can 2x,36 to select the TM peripheral.
  * @param  value : register new register.
  * @retval None
  */
int setCCRRegister(timer_id_e timer_id, uint32_t channel, uint32_t value)
{
    //TM_OC_InitTypeDef OC_Config;
    
    if(timer_id >= NB_TIMER_MANAGED)
    {
        return -1;
    }
    
    /* Check input state */
    __MID_LOCK( g_timer_config[timer_id].timInstance );

    g_timer_config[timer_id].timInstance->State = MID_TM_STATE_BUSY;

    switch( channel )
    {
        case MID_TM_Channel0:
            TM_SetCC0A( g_timer_config[timer_id].timInstance->Instance, value );
            TM_SetCC0B( g_timer_config[timer_id].timInstance->Instance, value );
            break;

        case MID_TM_Channel1:
            TM_SetCC1A( g_timer_config[timer_id].timInstance->Instance, value );
            TM_SetCC1B( g_timer_config[timer_id].timInstance->Instance, value );
            break;

        case MID_TM_Channel2:
            TM_SetCC2A( g_timer_config[timer_id].timInstance->Instance, value );
            TM_SetCC2B( g_timer_config[timer_id].timInstance->Instance, value );
            break;

        case MID_TM_Channel3:
            TM_SetCC3A( g_timer_config[timer_id].timInstance->Instance, value );
            TM_SetCC3B( g_timer_config[timer_id].timInstance->Instance, value );
            break;

        default:
            break;
    }
    g_timer_config[timer_id].timInstance->State = MID_TM_STATE_READY;

    /* Release Lock */
    __MID_UNLOCK( g_timer_config[timer_id].timInstance );
    
    
    return 0;

}


/**
  * @brief  Set the TIM Capture Compare Register value.
  * @param  timer_id : id of the timer
  * @param  channel : TIM Channels to be configured.
  * @retval CRR value.
  */
uint32_t getCCRRegister(timer_id_e timer_id, uint32_t channel)
{
    if(timer_id < NB_TIMER_MANAGED)
    {
        return  MID_TM_ReadCapturedValue( g_timer_config[timer_id].timInstance, channel);
    }
    else
    {
        return 0;
    }
}





/**
  * @brief  Attached an interrupt handler
  * @param  timer_id : id of the timer
  * @param  irqHandle : interrupt handler
  * @retval none
  */
void attachIntHandle( timer_id_e timer_id, void (*irqHandle)(timer_id_e)  )
{
    if(timer_id < NB_TIMER_MANAGED)
    {
        g_timer_config[timer_id].irqHandle = irqHandle;
    }
}


////==========================================================================
////==========================================================================
////==========================================================================



/******************************************************************************/
/*                            TIMx IRQ HANDLER                                */
/******************************************************************************/

#if (defined(TM00_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       TM00 interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void TM00_IRQ(void)
{
    //  Main counter
    if (TM_GetSingleFlagStatus(TM00, TMx_TUF2) == DRV_Happened)
    {
        // Timer underflow flag
        MID_TM_OC_DelayElapsedCallback( &mTM00 );

        TM_ClearFlag (TM00, TMx_TUF2);
    }

    if (TM_GetSingleFlagStatus(TM00, TMx_TOF2) == DRV_Happened)
    {
        // Timer overflow flag
        MID_TM_OC_DelayElapsedCallback( &mTM00 );

        TM_ClearFlag (TM00, TMx_TOF2);
    }
    if (TM_GetSingleFlagStatus(TM00, TMx_TOF) == DRV_Happened)
    {
        // Main Timer overflow flag
        MID_TM_OC_DelayElapsedCallback( &mTM00 );

        TM_ClearFlag (TM00, TMx_TOF);
    }

    // external trigger
    if (TM_GetSingleFlagStatus(TM00, TMx_EXF) == DRV_Happened)
    {
        // Timer external trigger flag
        MID_TM_OC_DelayElapsedCallback( &mTM00 );

        TM_ClearFlag (TM00, TMx_EXF);
    }
    
    TM_ClearFlag(TM00, TMx_EXF);
}
#endif

#if (defined(TM01_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       TM01 interrupt function. 
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void TM01_IRQ(void)
{
    //  Main counter
    if (TM_GetSingleFlagStatus(TM01, TMx_TUF2) == DRV_Happened)
    {
        // Timer underflow flag
        MID_TM_OC_DelayElapsedCallback( &mTM01 );

        TM_ClearFlag (TM01, TMx_TUF2);
    }
    if (TM_GetSingleFlagStatus(TM01, TMx_TOF2) == DRV_Happened)
    {
        // Timer overflow flag
        MID_TM_OC_DelayElapsedCallback( &mTM01 );

        TM_ClearFlag (TM01, TMx_TOF2);
    }
    if (TM_GetSingleFlagStatus(TM01, TMx_TOF) == DRV_Happened)
    {
        // Main Timer overflow flag
        MID_TM_OC_DelayElapsedCallback( &mTM01 );

        TM_ClearFlag (TM01, TMx_TOF);
    }

    // external trigger
    if (TM_GetSingleFlagStatus(TM01, TMx_EXF) == DRV_Happened)
    {
        // Timer external trigger flag
        MID_TM_OC_DelayElapsedCallback( &mTM01 );

        TM_ClearFlag (TM01, TMx_EXF);
    }
    TM_ClearFlag(TM01, TMx_EXF);
}
#endif

#if (defined(TM10_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       TM10 interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void TM10_IRQ(void)
{
    //  Main counter
    if (TM_GetSingleFlagStatus(TM10, TMx_TUF2) == DRV_Happened)
    {
        // Timer underflow flag
        MID_TM_OC_DelayElapsedCallback( &mTM10 );

        TM_ClearFlag (TM10, TMx_TUF2);
    }
    if (TM_GetSingleFlagStatus(TM10, TMx_TOF2) == DRV_Happened)
    {
        // Timer overflow flag
        MID_TM_OC_DelayElapsedCallback( &mTM10 );

        TM_ClearFlag (TM10, TMx_TOF2);
    }
    if (TM_GetSingleFlagStatus(TM10, TMx_TOF) == DRV_Happened)
    {
        // Main Timer overflow flag
        MID_TM_OC_DelayElapsedCallback( &mTM10 );
        
        TM_ClearFlag (TM10, TMx_TOF);
    }

    // external trigger
    if (TM_GetSingleFlagStatus(TM10, TMx_EXF) == DRV_Happened)
    {
        // Timer external trigger flag
        MID_TM_OC_DelayElapsedCallback( &mTM10 );

        TM_ClearFlag (TM10, TMx_EXF);
    }
    TM_ClearFlag(TM10, TMx_EXF);
}
#endif

#if (defined(TM16_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       TM16 interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void TM16_IRQ(void)
{
    //  Main counter
    if (TM_GetSingleFlagStatus(TM16, TMx_TUF2) == DRV_Happened)
    {
        // Timer underflow flag
        MID_TM_OC_DelayElapsedCallback( &mTM16 );

        TM_ClearFlag (TM16, TMx_TUF2);
    }
    if (TM_GetSingleFlagStatus(TM16, TMx_TUF) == DRV_Happened)
    {
        // Main Timer underflow flag
        MID_TM_OC_DelayElapsedCallback( &mTM16 );

        TM_ClearFlag (TM16, TMx_TUF);
    }
    if (TM_GetSingleFlagStatus(TM16, TMx_TOF2) == DRV_Happened)
    {
        // Timer overflow flag
        MID_TM_OC_DelayElapsedCallback( &mTM16 );

        TM_ClearFlag (TM16, TMx_TOF2);
    }
    if (TM_GetSingleFlagStatus(TM16, TMx_TOF) == DRV_Happened)
    {
        // Main Timer overflow flag
        MID_TM_OC_DelayElapsedCallback( &mTM16 );

        TM_ClearFlag (TM16, TMx_TOF);
    }

    // external trigger
    if (TM_GetSingleFlagStatus(TM16, TMx_EXF) == DRV_Happened)
    {
        // Timer external trigger flag
        MID_TM_OC_DelayElapsedCallback( &mTM16 );

        TM_ClearFlag (TM16, TMx_EXF);
    }
    TM_ClearFlag(TM16, TMx_EXF);
}
#endif

#if (defined(TM20_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       TM20 interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void TM20_IRQ(void)
{
    #if defined(MG32_4TH)
    if (TM_GetSingleFlagStatus(TM20, TMx_IDCF) == DRV_Happened)
    {
        // Repetition timer underflow flag. 
        MID_TM_OC_DelayElapsedCallback( &mTM20 );

        TM_ClearFlag (TM20, TMx_IDCF);
    }
    #endif
    // ------------------------------------------------------------------------
    #if defined(MG32_3RD) || defined(MG32_4TH)
    if (TM_GetSingleFlagStatus(TM20, TMx_RTUF) == DRV_Happened)
    {
        // Repetition timer underflow flag. 
        MID_TM_OC_DelayElapsedCallback( &mTM20 );

        TM_ClearFlag (TM20, TMx_RTUF);
    }
    #endif
    // ------------------------------------------------------------------------
    // Channel1 - IC/OC 
    if (TM_GetSingleFlagStatus(TM20, TMx_CF1B) == DRV_Happened)
    {
        // Timer IC1 falling edge flag/OC1 event sub flag
        MID_TM_OC_DelayElapsedCallback( &mTM20 );

        TM_ClearFlag (TM20, TMx_CF1B);
    }
    if (TM_GetSingleFlagStatus(TM20, TMx_CF1A) == DRV_Happened)
    {
        // Timer IC1 falling edge flag/OC1 event main flag
        MID_TM_OC_DelayElapsedCallback( &mTM20 );

        TM_ClearFlag (TM20, TMx_CF1A);
    }

    // Channel0 - IC/OC 
    if (TM_GetSingleFlagStatus(TM20, TMx_CF0B) == DRV_Happened)
    {
        // Timer IC0 falling edge flag/OC0 event sub flag
        MID_TM_OC_DelayElapsedCallback( &mTM20 );

        TM_ClearFlag (TM20, TMx_CF0B);
    }
    if (TM_GetSingleFlagStatus(TM20, TMx_CF0A) == DRV_Happened)
    {
        // Timer IC0 falling edge flag/OC0 event main flag
        MID_TM_OC_DelayElapsedCallback( &mTM20 );
        
        TM_ClearFlag (TM20, TMx_CF0A);
    }

    // ------------------------------------------------------------------------
    // Main counter
    if (TM_GetSingleFlagStatus(TM20, TMx_TUF2) == DRV_Happened)
    {
        // Timer underflow flag
        MID_TM_OC_DelayElapsedCallback( &mTM20 );

        TM_ClearFlag (TM20, TMx_TUF2);
    }
    if (TM_GetSingleFlagStatus(TM20, TMx_TOF2) == DRV_Happened)
    {
        // Timer overflow flag
        MID_TM_OC_DelayElapsedCallback( &mTM20 );

        TM_ClearFlag (TM20, TMx_TOF2);
    }
    if (TM_GetSingleFlagStatus(TM20, TMx_TOF) == DRV_Happened)
    {
        // Main Timer overflow flag
        MID_TM_OC_DelayElapsedCallback( &mTM20 );

        TM_ClearFlag (TM20, TMx_TOF);
    }

    // ------------------------------------------------------------------------
    // external trigger
    if (TM_GetSingleFlagStatus(TM20, TMx_EXF) == DRV_Happened)
    {
        // Timer external trigger flag
        MID_TM_OC_DelayElapsedCallback( &mTM20 );
        
        TM_ClearFlag (TM20, TMx_EXF);
    }
    TM_ClearFlag(TM20, TMx_EXF);
}
#endif

#if (defined(TM26_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       TM26 interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void TM26_IRQ(void)
{
    #if defined(MG32_3RD)
    if (TM_GetSingleFlagStatus(TM26, TMx_RTUF) == DRV_Happened)
    {
        // Repetition timer underflow flag.
        MID_TM_OC_DelayElapsedCallback( &mTM26 );

        TM_ClearFlag (TM26, TMx_RTUF);
    }
    #endif

    // QEI event
    if (TM_GetSingleFlagStatus(TM26, TMx_QPEF) == DRV_Happened)
    {
        // Main Timer QEI phase state transition error detect flag.
        MID_TM_OC_DelayElapsedCallback( &mTM26 );

        TM_ClearFlag (TM26, TMx_QPEF);
    }
    if (TM_GetSingleFlagStatus(TM26, TMx_IDXF) == DRV_Happened)
    {
        // Main Timer QEI external index signal input active detect and internal timer reset flag.
        MID_TM_OC_DelayElapsedCallback( &mTM26 );

        TM_ClearFlag (TM26, TMx_IDXF);
    }
    if (TM_GetSingleFlagStatus(TM26, TMx_DIRCF) == DRV_Happened)
    {
        // Main Timer up/down counting direction change flag.
        MID_TM_OC_DelayElapsedCallback( &mTM26 );

        TM_ClearFlag (TM26, TMx_DIRCF);
    }

    // Channel1 - IC/OC 
    if (TM_GetSingleFlagStatus(TM26, TMx_CF1B) == DRV_Happened)
    {
        // Timer IC1 falling edge flag/OC1 event sub flag
        MID_TM_OC_DelayElapsedCallback( &mTM26 );

        TM_ClearFlag (TM26, TMx_CF1B);
    }
    if (TM_GetSingleFlagStatus(TM26, TMx_CF1A) == DRV_Happened)
    {
        // Timer IC1 falling edge flag/OC1 event main flag
        MID_TM_OC_DelayElapsedCallback( &mTM26 );

        TM_ClearFlag (TM26, TMx_CF1A);
    }

    // Channel0 - IC/OC 
    if (TM_GetSingleFlagStatus(TM26, TMx_CF0B) == DRV_Happened)
    {
        // Timer IC0 falling edge flag/OC0 event sub flag
        MID_TM_OC_DelayElapsedCallback( &mTM26 );

        TM_ClearFlag (TM26, TMx_CF0B);
    }
    if (TM_GetSingleFlagStatus(TM26, TMx_CF0A) == DRV_Happened)
    {
        // Timer IC0 falling edge flag/OC0 event main flag
        MID_TM_OC_DelayElapsedCallback( &mTM26 );
        
        TM_ClearFlag (TM26, TMx_CF0A);
    }

    //  / Main counter
    if (TM_GetSingleFlagStatus(TM26, TMx_TUF2) == DRV_Happened)
    {
        //  Timer underflow flag
        MID_TM_OC_DelayElapsedCallback( &mTM26 );

        TM_ClearFlag (TM26, TMx_TUF2);
    }
    if (TM_GetSingleFlagStatus(TM26, TMx_TUF) == DRV_Happened)
    {
        // Main Timer underflow flag
        MID_TM_OC_DelayElapsedCallback( &mTM26 );

        TM_ClearFlag (TM26, TMx_TUF);
    }
    if (TM_GetSingleFlagStatus(TM26, TMx_TOF2) == DRV_Happened)
    {
        // Timer overflow flag
        MID_TM_OC_DelayElapsedCallback( &mTM26 );

        TM_ClearFlag (TM26, TMx_TOF2);
    }
    if (TM_GetSingleFlagStatus(TM26, TMx_TOF) == DRV_Happened)
    {
        // Main Timer overflow flag
        MID_TM_OC_DelayElapsedCallback( &mTM26 );

        TM_ClearFlag (TM26, TMx_TOF);
    }

    // external trigger
    if (TM_GetSingleFlagStatus(TM26, TMx_EXF) == DRV_Happened)
    {
        // Timer external trigger flag
        MID_TM_OC_DelayElapsedCallback( &mTM26 );

        TM_ClearFlag (TM26, TMx_EXF);
    }
    
    TM_ClearFlag(TM26, TMx_EXF);
}
#endif







#if (defined(TM36_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       TM36 interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void TM36_IRQ(void)
{
    // ------------------------------------------------------------------------
    // Duty capture flag.
    #if defined(MG32_4TH)
    if (TM_GetSingleFlagStatus(TM36, TMx_IDCF) == DRV_Happened)
    {
        // Input duty capture complete flag.. 
        MID_TM_OC_DelayElapsedCallback( &mTM36 );

        TM_ClearFlag (TM36, TMx_IDCF);
    }
    #endif

    // ------------------------------------------------------------------------
    // Repetition timer flag.
    #if defined(MG32_3RD) || defined(MG32_4TH)
    if (TM_GetSingleFlagStatus(TM36, TMx_RTUF) == DRV_Happened)
    {
        // Repetition timer underflow flag. 
        MID_TM_OC_DelayElapsedCallback( &mTM36 );

        TM_ClearFlag (TM36, TMx_RTUF);
    }
    #endif

    // ------------------------------------------------------------------------
    // QEI event
    if (TM_GetSingleFlagStatus(TM36, TMx_QPEF) == DRV_Happened)
    {
        // Main Timer QEI phase state transition error detect flag.
        MID_TM_OC_DelayElapsedCallback( &mTM36 );

        TM_ClearFlag (TM36, TMx_QPEF);
    }
    if (TM_GetSingleFlagStatus(TM36, TMx_IDXF) == DRV_Happened)
    {
        // Main Timer QEI external index signal input active detect and internal timer reset flag.
        MID_TM_OC_DelayElapsedCallback( &mTM36 );

        TM_ClearFlag (TM36, TMx_IDXF);
    }
    if (TM_GetSingleFlagStatus(TM36, TMx_DIRCF) == DRV_Happened)
    {
        // Main Timer up/down counting direction change flag.
        MID_TM_OC_DelayElapsedCallback( &mTM36 );

        TM_ClearFlag (TM36, TMx_DIRCF);
    }

    // ------------------------------------------------------------------------
    // Sub event - IC/OC 
    if (TM_GetSingleFlagStatus(TM36, TMx_CF3B) == DRV_Happened)
    {
        // Timer IC3 falling edge flag/OC3 event sub flag
        MID_TM_OC_DelayElapsedCallback( &mTM36 );

        TM_ClearFlag (TM36, TMx_CF3B);
    }
    if (TM_GetSingleFlagStatus(TM36, TMx_CF2B) == DRV_Happened)
    {
        // Timer IC2 falling edge flag/OC2 event sub flag
        MID_TM_OC_DelayElapsedCallback( &mTM36 );

        TM_ClearFlag (TM36, TMx_CF2B);
    }
    if (TM_GetSingleFlagStatus(TM36, TMx_CF1B) == DRV_Happened)
    {
        // Timer IC1 falling edge flag/OC1 event sub flag
        MID_TM_OC_DelayElapsedCallback( &mTM36 );

        TM_ClearFlag (TM36, TMx_CF1B);
    }
    if (TM_GetSingleFlagStatus(TM36, TMx_CF0B) == DRV_Happened)
    {
        // Timer IC1 falling edge flag/OC1 event sub flag
        MID_TM_OC_DelayElapsedCallback( &mTM36 );

        TM_ClearFlag (TM36, TMx_CF0B);
    }

    // Main event - IC/OC 
    if (TM_GetSingleFlagStatus(TM36, TMx_CF3A) == DRV_Happened)
    {
        // Timer IC3 falling edge flag/OC3 event sub flag
        MID_TM_OC_DelayElapsedCallback( &mTM36 );

        TM_ClearFlag (TM36, TMx_CF3A);
    }
    if (TM_GetSingleFlagStatus(TM36, TMx_CF2A) == DRV_Happened)
    {
        // Timer IC2 falling edge flag/OC2 event sub flag
        MID_TM_OC_DelayElapsedCallback( &mTM36 );

        TM_ClearFlag (TM36, TMx_CF2A);
    }
    if (TM_GetSingleFlagStatus(TM36, TMx_CF1A) == DRV_Happened)
    {
        // Timer IC1 falling edge flag/OC1 event sub flag
        MID_TM_OC_DelayElapsedCallback( &mTM36 );

        TM_ClearFlag (TM36, TMx_CF1A);
    }
    if (TM_GetSingleFlagStatus(TM36, TMx_CF0A) == DRV_Happened)
    {
        // Timer IC1 falling edge flag/OC1 event sub flag
        MID_TM_OC_DelayElapsedCallback( &mTM36 );

        TM_ClearFlag (TM36, TMx_CF0A);
    }

    // ------------------------------------------------------------------------
    //  Main counter
    if (TM_GetSingleFlagStatus(TM36, TMx_TUF2) == DRV_Happened)
    {
        // Timer underflow flag
        MID_TM_OC_DelayElapsedCallback( &mTM36 );

        TM_ClearFlag (TM36, TMx_TUF2);
    }
    if (TM_GetSingleFlagStatus(TM36, TMx_TUF) == DRV_Happened)
    {
        // Main Timer underflow flag
        MID_TM_OC_DelayElapsedCallback( &mTM36 );

        TM_ClearFlag (TM36, TMx_TUF);
    }
    if (TM_GetSingleFlagStatus(TM36, TMx_TOF2) == DRV_Happened)
    {
        // Timer overflow flag
        MID_TM_OC_DelayElapsedCallback( &mTM36 );

        TM_ClearFlag (TM36, TMx_TOF2);
    }
    if (TM_GetSingleFlagStatus(TM36, TMx_TOF) == DRV_Happened)
    {
        // Main Timer overflow flag
        MID_TM_OC_DelayElapsedCallback( &mTM36 );

        TM_ClearFlag (TM36, TMx_TOF);
    }

    // ------------------------------------------------------------------------
    // Break input event
    if (TM_GetSingleFlagStatus(TM36, TMx_BKF) == DRV_Happened)
    {
        // Timer external trigger flag
        MID_TM_OC_DelayElapsedCallback( &mTM36 );

        TM_ClearFlag (TM36, TMx_BKF);
    }

    // ------------------------------------------------------------------------
    // external trigger
    if (TM_GetSingleFlagStatus(TM36, TMx_EXF) == DRV_Happened)
    {
        // Timer external trigger flag
        MID_TM_OC_DelayElapsedCallback( &mTM36 );

        TM_ClearFlag (TM36, TMx_EXF);
    }
    TM_ClearFlag(TM36, TMx_EXF);
}
#endif



#ifdef __cplusplus
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/



