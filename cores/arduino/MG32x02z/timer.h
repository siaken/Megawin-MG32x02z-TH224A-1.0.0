/**
 ******************************************************************************
 *
 ******************************************************************************
 * @file    timer.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIMER_H
#define __TIMER_H

/* Includes ------------------------------------------------------------------*/
#include "MG32x02z.h"
#include "system_MG32x02z.h"


#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
typedef enum {
  TIM00_E = 0,
  TIM01_E = 1,
  TIM10_E = 2,
  TIM16_E = 3,
  TIM20_E = 4,
  TIM26_E = 5,
  TIM36_E = 6,
  NB_TIMER_MANAGED
} timer_id_e;

/*
#define TM00                            ((TM_Struct*) TM00_Base)
#define TM01                            ((TM_Struct*) TM01_Base)
#define TM10                            ((TM_Struct*) TM10_Base)
#define TM16                            ((TM_Struct*) TM16_Base)
#define TM20                            ((TM_Struct*) TM20_Base)
#define TM26                            ((TM_Struct*) TM26_Base)
#define TM36                            ((TM_Struct*) TM36_Base)
*/

typedef enum {
  bits_8 = 0xFF,
  bits_16 = 0xFFFF,
  bits_32 = 0xFFFFFFFF
} timer_prescaler_limit;

typedef enum {
    
  TIMER_PERIOD    = 0x00000000,
  TIMER_PWM       = 0x00000001,
  TIMER_ONEPULSE  = 0x00000002,
  TIMER_OC        = 0x00000004,
  TIMER_RESERVED  = 0x00000080,
  TIMER_OTHER     = 0x80000000
} timer_mode_e;


typedef struct{
  GPIO_Struct * port;
  uint32_t pin;
  int32_t count;
  uint8_t state;
}timer_toggle_pin_config_str;

/// @brief defines the global attributes of the TIMER
typedef struct
{
    TM_HandleTypeDef *timInstance;
    IRQn_Type irqtype;
    void (*irqHandle)(timer_id_e);
    void (*User_irqHandle)(timer_id_e);
    void (*timer_clock_init)(void);
    void (*timer_clock_reset)(void);
    timer_mode_e timer_mode;
    timer_prescaler_limit prescalerLimit;
    timer_toggle_pin_config_str toggle_pin;
    uint8_t configured;
}timer_conf_t;

/* Exported constants --------------------------------------------------------*/
#define MAX_FREQ  65535

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void TIM_OC_MspInit(TM_HandleTypeDef *htim);
void TIM_OC_MspDeInit(TM_HandleTypeDef *htim);


void timer_cfg_init(void);

void timer_enable_clock(TM_HandleTypeDef *htim);
void timer_disable_clock(TM_HandleTypeDef *htim);

//void TimerHandleInit(timer_id_e timer_id, uint16_t period, uint16_t prescaler);
void TimerHandleInit(timer_id_e timer_id, uint16_t period);
void TimerHandleDeinit(timer_id_e timer_id);

void TimerPinInit(GPIO_Struct *port, uint32_t pin,  uint32_t afs, uint32_t frequency, uint32_t duration);
void TimerPinDeinit(GPIO_Struct *port, uint32_t pin);

void TimerPulseInit(timer_id_e timer_id, uint16_t period, uint16_t pulseWidth, void (*irqHandle)(timer_id_e));
void TimerPulseDeinit(timer_id_e timer_id);

void TIM_Base_MspInit(TM_HandleTypeDef *htim_base);
void TIM_Base_MspDeInit(TM_HandleTypeDef *htim_base);

timer_id_e getInactiveTimer(void);
timer_id_e isPinAssociateToTimer(GPIO_Struct *port, uint32_t pin);

uint32_t getTimerCounter(timer_id_e timer_id);
void setTimerCounter(timer_id_e timer_id, uint32_t value);
int setCCRRegister(timer_id_e timer_id, uint32_t channel, uint32_t value);
uint32_t getCCRRegister(timer_id_e timer_id, uint32_t channel);

void attachIntHandle( timer_id_e timer_id, void (*irqHandle)(timer_id_e)  );


#ifdef __cplusplus
}
#endif

#endif /* __TIMER_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
