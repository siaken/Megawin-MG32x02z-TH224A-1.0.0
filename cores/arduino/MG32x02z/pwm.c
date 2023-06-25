/*
 Copyright (c) 2011 Arduino.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include  "pwm.h"

#define  PWMPIN_AFS_CFG(a, num, afs)      .pin=MCU_##a##num, .pinAFS=a##num##_AFS_##afs

#ifdef  MG32F02U128
static pwm_config_str  pwm_cfg[NB_PWM_CHANNELS] = 
{
    /////========================================================
    {   //D42
        PWMPIN_AFS_CFG(PA, 12, TM26_OC00),
        .timStruct     = TM26,
        .timChannel    = MID_TM_Channel0,

        .timHandle = 
        {
            .Instance                  = TM26,
            .Init.TM_CounterMode       = TM_SEPARATE_UP,
            .Init.TM_Period            = 1023,
            .Init.TM_Prescaler         = 0,
        },
        .clock_freq  = PWM_FREQUENCY,
        .doInit      = 0,
    },

    {   //D43
        PWMPIN_AFS_CFG(PA, 13, TM26_OC10),
        .timStruct     = TM26,
        .timChannel    = MID_TM_Channel1,

        .timHandle = 
        {
            .Instance                  = TM26,
            .Init.TM_CounterMode       = TM_SEPARATE_UP,
            .Init.TM_Period            = 1023,
            .Init.TM_Prescaler         = 0,
        },
        .clock_freq  = PWM_FREQUENCY,
        .doInit      = 0,
    },
    /////========================================================
    
    {   //D3
        PWMPIN_AFS_CFG(PB, 10, TM20_OC11),
        .timStruct     = TM20,
        .timChannel    = MID_TM_Channel1,

        .timHandle = 
        {
            .Instance                  = TM20,
            .Init.TM_CounterMode       = TM_SEPARATE_UP,
            .Init.TM_Period            = 1023,
            .Init.TM_Prescaler         = 0,
        },
        .clock_freq  = PWM_FREQUENCY,
        .doInit      = 0,
    },
    
    

    {   //D5
        PWMPIN_AFS_CFG(PB, 11, TM36_OC12),
        .timStruct     = TM36,
        .timChannel    = MID_TM_Channel1,

        .timHandle = 
        {
            .Instance                  = TM36,
            .Init.TM_CounterMode       = TM_SEPARATE_UP,
            .Init.TM_Period            = 1023,
            .Init.TM_Prescaler         = 0,
        },
        .clock_freq  = PWM_FREQUENCY,
        .doInit      = 0,
    },
    
    {   //D6
        PWMPIN_AFS_CFG(PC, 0, TM20_OC00),
        .timStruct     = TM20,
        .timChannel    = MID_TM_Channel0,

        .timHandle = 
        {
            .Instance                  = TM20,
            .Init.TM_CounterMode       = TM_SEPARATE_UP,
            .Init.TM_Period            = 1023,
            .Init.TM_Prescaler         = 0,
        },
        .clock_freq  = PWM_FREQUENCY,
        .doInit      = 0,
    },
    
    

    {   //D8
        PWMPIN_AFS_CFG(PC, 12, TM36_OC3),
        .timStruct     = TM36,
        .timChannel    = MID_TM_Channel3,

        .timHandle = 
        {
            .Instance                  = TM36,
            .Init.TM_CounterMode       = TM_SEPARATE_UP,
            .Init.TM_Period            = 1023,
            .Init.TM_Prescaler         = 0,
        },
        .clock_freq  = PWM_FREQUENCY,
        .doInit      = 0,
    },
    
    {   //D9
        PWMPIN_AFS_CFG(PD, 0, TM36_OC2),
        .timStruct     = TM36,
        .timChannel    = MID_TM_Channel2,

        .timHandle = 
        {
            .Instance                  = TM36,
            .Init.TM_CounterMode       = TM_SEPARATE_UP,
            .Init.TM_Period            = 1023,
            .Init.TM_Prescaler         = 0,
        },
        .clock_freq  = PWM_FREQUENCY,
        .doInit      = 0,
    },
    
    {   //D11
        PWMPIN_AFS_CFG(PD, 2, TM26_OC00),
        .timStruct     = TM26,
        .timChannel    = MID_TM_Channel0,

        .timHandle = 
        {
            .Instance                  = TM26,
            .Init.TM_CounterMode       = TM_SEPARATE_UP,
            .Init.TM_Period            = 1023,
            .Init.TM_Prescaler         = 0,
        },
        .clock_freq  = PWM_FREQUENCY,
        .doInit      = 0,
    },
    
    {   //D10
        PWMPIN_AFS_CFG(PD, 9, TM26_OC11),
        .timStruct     = TM26,
        .timChannel    = MID_TM_Channel1,

        .timHandle = 
        {
            .Instance                  = TM26,
            .Init.TM_CounterMode       = TM_SEPARATE_UP,
            .Init.TM_Period            = 1023,
            .Init.TM_Prescaler         = 0,
        },
        .clock_freq  = PWM_FREQUENCY,
        .doInit      = 0,
    },
};


#endif


int8_t get_pwm_instance( uint32_t pin )
{
    int8_t i;

    for(i = 0; i < NB_PWM_CHANNELS; i++) 
    {
        if( ( pwm_cfg[i].pin == pin) ) 
        {
            return i;
        }
    }
    return -1;
}


/**
  * @brief PWM_MspInit Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  * @param pin : Arduino pin
  * @retval None
  */
void PWM_MspInit(  uint32_t pin )
{
    int8_t idx = -1;
    
    Pin_Struct*  pPinx;		
    GPIO_InitTypeDef GPIOX;

    idx = get_pwm_instance( pin );
    if( ( idx >= NB_PWM_CHANNELS ) ||(idx < 0 ) )
    {
        return;
    }
    
    /* Enable GPIO Channels Clock */
    /* Enable GPIO clock ****************************************/
    if( g_APinDescription[pin].ulPort == GPIOA ) 
    {
        __DRV_CSC_GPIOA_CLK_ENABLE();
    }
    else if( g_APinDescription[pin].ulPort == GPIOB )
    {
        __DRV_CSC_GPIOB_CLK_ENABLE();
    }
    else if( g_APinDescription[pin].ulPort == GPIOC )
    {
        __DRV_CSC_GPIOC_CLK_ENABLE();
    }


    GPIOX.Mode = GPIO_MODE_PUSHPULL_O;
    GPIOX.Pull = GPIO_NOPULLUP;

    GPIOX.Pin            = g_APinDescription[pin].GioPin;
    GPIOX.Speed          = GPIO_SPEED_HIGH;
    GPIOX.OUTDrive       = GPIO_OUTDRIVE_LEVEL0;
    GPIOX.FilterDivider  = GPIO_FILTERDIVIDER_BYPASS;
    GPIOX.Inverse        = GPIO_INVERSE_DISABLE;
    GPIOX.Alternate      = pwm_cfg[idx].pinAFS;
    pPinx = __GetPinxx_byGPIOx( g_APinDescription[pin].ulPort,  g_APinDescription[pin].PinNum );
    MID_GPIO_Pin_Init(  pPinx,  &GPIOX);

}


/**
  * @brief  DeInitializes TIM PWM_MspDeInit MSP.
  * @param  pin : Arduino pin
  * @retval None
  */
void PWM_MspDeInit(  uint32_t pin  )
{
    int8_t idx = -1;

    //Pin_Struct*  pPinx;		
    //GPIO_InitTypeDef GPIOX;

    idx = get_pwm_instance( pin );
    if( ( idx >= NB_PWM_CHANNELS ) ||(idx < 0 ) )
    {
        return;
    }

    pwm_cfg[idx].doInit      = 0;
    MID_TM_PWM_DeInit( &(pwm_cfg[idx].timHandle )   );
}

/**
  * @brief  This function will set the PWM frequency value
  * @param  pin : the gpio pin to use
  * @param  clock_freq : frequency of the tim clock
  * @retval None
  */
void pwm_setFrequency(uint32_t ulPin,  uint32_t freq)
{
    int  i = 0;

    //find the instance in the global
    i = get_pwm_instance( ulPin );
    if( ( i >= NB_PWM_CHANNELS ) ||(i < 0 ) )
    {
        return;
    }

    pwm_cfg[i].clock_freq = freq;
    pwm_cfg[i].doInit     = 0;

}

/**
  * @brief  This function will set the PWM to the required value
  * @param  pin : the gpio pin to use
  * @param  period : period of the tim counter
  * @param  value : the value to push on the PWM output
  * @param  do_init : if set to 1 the initialization of the PWM is done
  * @retval None
  */
void pwm_start( uint32_t pin,
                uint32_t period,  uint32_t value,        uint8_t do_init )
{
    uint32_t Cnt = (SystemCoreClock/PWM_FREQUENCY)-1;
    int  i = 0;
    Pin_Struct*  pPinx;		
    GPIO_InitTypeDef GPIOX;
    
    do_init = do_init;
    
    //find the instance in the global
    i = get_pwm_instance( pin );
    if( ( i >= NB_PWM_CHANNELS ) ||(i < 0 ) )
    {
        return;
    }

    Cnt = (SystemCoreClock/(pwm_cfg[i].clock_freq))-1;
    if( pwm_cfg[i].doInit == 0 )
    {
        GPIOX.Mode = GPIO_MODE_PUSHPULL_O;
        GPIOX.Pull = GPIO_PULLUP;
        GPIOX.Pin            = g_APinDescription[ pwm_cfg[i].pin ].GioPin;
        GPIOX.Speed          = GPIO_SPEED_LOW;
        GPIOX.OUTDrive       = GPIO_OUTDRIVE_LEVEL0;
        GPIOX.FilterDivider  = GPIO_FILTERDIVIDER_BYPASS;
        GPIOX.Inverse        = GPIO_INVERSE_DISABLE;
        GPIOX.Alternate      = pwm_cfg[i].pinAFS;
        pPinx = __GetPinxx_byGPIOx( g_APinDescription[pwm_cfg[i].pin].ulPort, g_APinDescription[pwm_cfg[i].pin].PinNum );
        MID_GPIO_Pin_Init(  pPinx,  &GPIOX);     

        // ------------------------------------------------------------------------
        // 1.Initial TM26 for 10-bit PWM.
        // ------------------------------------------------------------------------
        pwm_cfg[i].timHandle.Instance                  = pwm_cfg[i].timStruct;
        pwm_cfg[i].timHandle.Init.TM_CounterMode       = TM_SEPARATE_UP;
        pwm_cfg[i].timHandle.Init.TM_Period            = (SystemCoreClock/(pwm_cfg[i].clock_freq))-1;
        pwm_cfg[i].timHandle.Init.TM_Prescaler         = 0;
        MID_TM_PWM_Init( &pwm_cfg[i].timHandle );
        
        // ------------------------------------------------------------------------
        // 2.Initial TM26 clock mode.
        // ------------------------------------------------------------------------
        pwm_cfg[i].CKConfig.TM_ClockSource         = TM_INTERNAL_CLOCK;
        pwm_cfg[i].CKConfig.TM_ExternalClockSource = 0;
        pwm_cfg[i].CKConfig.TM_INTClockDivision    = TM_INTERNALCLOCK_DIVDER_DIV1;
        pwm_cfg[i].CKConfig.TM_InternalClockSource = TM_INTERNALCLOCK_PROC;
        
        MID_TM_ConfigClockSource(&pwm_cfg[i].timHandle, &pwm_cfg[i].CKConfig);  
        
        // ------------------------------------------------------------------------
        // 3.TM26 PWM output channel configuration.
        // ------------------------------------------------------------------------
        MID_TM_OC_Struct_Init(&pwm_cfg[i].sConfig);               // default initial (output state)
        pwm_cfg[i].sConfig.OCMode = TM_CH_16bit_PWM;
        
        pwm_cfg[i].sConfig.Pulse = ((Cnt*value)/period);
        MID_TM_PWM_ConfigChannel(&pwm_cfg[i].timHandle, &pwm_cfg[i].sConfig, pwm_cfg[i].timChannel);

        TM_OC1zOutput_Cmd( pwm_cfg[i].timStruct, ENABLE);

        // ------------------------------------------------------------------------
        // 4.Start PWM output.
        // ------------------------------------------------------------------------
        MID_TM_PWM_Start( &pwm_cfg[i].timHandle, pwm_cfg[i].timChannel);    // Channel0 be 16bit PWM output (Blocking mode: Polling) 
    }

  	// ------------------------------------------------------------------------
  	// 5.Update duty cycle.
  	// ------------------------------------------------------------------------
  	__DRV_TM_SET_COMPARE_B( &pwm_cfg[i].timHandle, pwm_cfg[i].timChannel, ((Cnt*value)/period) );

    pwm_cfg[i].doInit = 1;
    return;
}


/**
  * @brief  This function will disable the PWM
  * @param  pin : the gpio pin to use
  * @retval None
  */
void pwm_stop(  uint32_t pin )
{
    int8_t idx = -1;

    //find the instance in the global
    idx = get_pwm_instance( pin );
    if( ( idx >= NB_PWM_CHANNELS ) ||(idx < 0 ) )
    {
        return;
    }

    pwm_cfg[idx].doInit     = 0;
    MID_TM_PWM_Stop(  &(pwm_cfg[idx].timHandle),   pwm_cfg[idx].timChannel );

//    MID_TM_PWM_DeInit( &(pwm_cfg[idx].timHandle) );
}


