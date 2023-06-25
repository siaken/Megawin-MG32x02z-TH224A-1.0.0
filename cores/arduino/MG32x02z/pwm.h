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
#ifndef _PWM_H_
#define _PWM_H_


#include "Arduino.h"
#include <inttypes.h>

#include "MG32x02z.h"
#include "system_MG32x02z.h"

#include "MG32x02z.h"
#include "system_MG32x02z.h"
#include "MG32x02z_GPIO_DRV.h"

#include "MG32x02z_TM_DRV.h"
#include "MG32x02z_TM_MID.h"


#include "hw_config.h"
#include "timer.h"
#include "digital_io.h"
#include "clock.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
typedef struct
{
    uint32_t                pin;
    uint16_t                pinAFS;
    uint16_t                padding;

    TM_Struct              *timStruct;
    uint32_t                timChannel;
    TM_OC_InitTypeDef       sConfig;
    TM_ClockConfigTypeDef   CKConfig;
    TM_HandleTypeDef        timHandle;

    uint32_t                clock_freq;
    uint32_t                doInit;
}pwm_config_str;


/* Exported constants --------------------------------------------------------*/
#ifdef  MG32F02U128
#define NB_PWM_CHANNELS       16
#endif


/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
/**
  * @brief  This function will set the PWM to the required value
  * @param  pin : the gpio pin to use
  * @param  period : period of the tim counter
  * @param  value : the value to push on the PWM output
  * @param  do_init : if set to 1 the initialization of the PWM is done
  * @retval None
  */
void pwm_start( uint32_t pin, uint32_t period, uint32_t value, uint8_t do_init );


/**
  * @brief  This function will disable the PWM
  * @param  pin : the gpio pin to use
  * @retval None
  */
void pwm_stop(  uint32_t pin );


/**
  * @brief  This function will set the PWM frequency value
  * @param  pin : the gpio pin to use
  * @param  clock_freq : frequency of the tim clock
  * @retval None
  */
void pwm_setFrequency(uint32_t ulPin,  uint32_t freq);




#ifdef __cplusplus
}
#endif





#endif



