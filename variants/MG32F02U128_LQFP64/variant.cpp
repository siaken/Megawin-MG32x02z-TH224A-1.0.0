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

#include "variant.h"


#include "MG32x02z.h"
#include "system_MG32x02z.h"
#include "MG32x02z_DRV.h"
#include "MG32x02z_ChipInit.h"
#include "MG32x02z_URT_MID.h"
#include "MG32x02z_ADC_MID.h"

#include "timer.h"
#include "UARTClass.h"
#include "hw_config.h"

#ifdef __cplusplus
extern "C" {
#endif


//INPUT_PULLUP
//GPIO_Pin_0

#define  GPA_CFG(x, afs, m)        .AFS=PA##x##_AFS_##afs,   .PinNum=x,  .GioPin=GPIO_Pin_##x, .ulPort=GPIOA,  .IO_Mode=m
#define  GPB_CFG(x, afs, m)        .AFS=PB##x##_AFS_##afs,   .PinNum=x,  .GioPin=GPIO_Pin_##x, .ulPort=GPIOB,  .IO_Mode=m
#define  GPC_CFG(x, afs, m)        .AFS=PC##x##_AFS_##afs,   .PinNum=x,  .GioPin=GPIO_Pin_##x, .ulPort=GPIOC,  .IO_Mode=m
#define  GPD_CFG(x, afs, m)        .AFS=PD##x##_AFS_##afs,   .PinNum=x,  .GioPin=GPIO_Pin_##x, .ulPort=GPIOD,  .IO_Mode=m
#define  GPE_CFG(x, afs, m)        .AFS=PE##x##_AFS_##afs,   .PinNum=x,  .GioPin=GPIO_Pin_##x, .ulPort=GPIOE,  .IO_Mode=m


#define  GPNULL_CFG()              .AFS=0,   .PinNum=((uint16_t)-1),  .GioPin=((uint16_t)-1), .ulPort=NULL,  .IO_Mode=0

PinDescription g_APinDescription[MAX_DIGITAL_IOS]=

//  arduino_id  |     PinNum    |   ulPort | mode               |          configured
{
  // 0 .. 19 - Digital pins
  // ----------------------
  { .arduino_id=ARDUINO_PIN_D0,
          GPA_CFG(7, GPA7, INPUT_PULLUP),   
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI, 
  	                       .ADCChannel= ADC_CHANNEL_7,   .IO_irqnb=EXINT0_IRQn,    .configured=false },
  	       
  { .arduino_id=ARDUINO_PIN_D1, 
          GPA_CFG(8, GPA8, INPUT_PULLUP),  
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_CMP|PIN_ATTR_SPI | PIN_ATTR_I2C|PIN_ATTR_DMA,  
  	                       .ADCChannel= ADC_CHANNEL_8,   .IO_irqnb=EXINT0_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D2, 
          GPA_CFG(9, GPA9, INPUT_PULLUP),   
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_CMP|PIN_ATTR_SPI | PIN_ATTR_I2C|PIN_ATTR_DMA, 
  	                       .ADCChannel= ADC_CHANNEL_9,   .IO_irqnb=EXINT0_IRQn,    .configured=false },	       

  { .arduino_id=ARDUINO_PIN_D3,
          GPA_CFG(10, GPA10, INPUT_PULLUP),   
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_CMP|PIN_ATTR_SPI | PIN_ATTR_I2C, 
  	                       .ADCChannel= ADC_CHANNEL_10,   .IO_irqnb=EXINT0_IRQn,    .configured=false },
  	                      
  	     	                       
  { .arduino_id=ARDUINO_PIN_D4, 
          GPA_CFG(11, GPA11, INPUT_PULLUP),   
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_CMP|PIN_ATTR_SPI | PIN_ATTR_I2C, 
  	                       .ADCChannel= ADC_CHANNEL_11,   .IO_irqnb=EXINT0_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D5, 
          GPA_CFG(12, GPA12, INPUT_PULLUP),   
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_USB|PIN_ATTR_SPI | PIN_ATTR_PWM, 
  	                       .ADCChannel= ADC_CHANNEL_12,   .IO_irqnb=EXINT0_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D6,   
          GPA_CFG(13, GPA13, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_USB|PIN_ATTR_SPI | PIN_ATTR_PWM, 
  	                       .ADCChannel= ADC_CHANNEL_13,   .IO_irqnb=EXINT0_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D7, 
          GPA_CFG(14, GPA14, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI, 
  	                       .ADCChannel= ADC_CHANNEL_14,   .IO_irqnb=EXINT0_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D8,  
          GPA_CFG(15, GPA15, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI, 
  	                       .ADCChannel= ADC_CHANNEL_15,   .IO_irqnb=EXINT0_IRQn,    .configured=false },                    
  	      
  	        	                       
  { .arduino_id=ARDUINO_PIN_D9,  
          GPB_CFG(0, GPB0, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_CMP|PIN_ATTR_SPI| PIN_ATTR_I2C, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D10,   
          GPB_CFG(1, GPB1, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_CMP|PIN_ATTR_SPI| PIN_ATTR_I2C, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D11,   
          GPB_CFG(2, GPB2, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI| PIN_ATTR_I2C|PIN_ATTR_ADC|PIN_ATTR_DAC, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D12,   
          GPB_CFG(3, GPB3, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI| PIN_ATTR_I2C|PIN_ATTR_ADC, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	        
  { .arduino_id=ARDUINO_PIN_D13, 
          GPB_CFG(4, GPB4, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D14, 
          GPB_CFG(5, GPB5, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D15,
          GPB_CFG(6, GPB6, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },

  { .arduino_id=ARDUINO_PIN_D16,  
          GPB_CFG(7, GPB7, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	       	                       
  { .arduino_id=ARDUINO_PIN_D17, 
          GPB_CFG(8, URT0_TX, OUTPUT), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI|PIN_ATTR_CMP, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D18, 
          GPB_CFG(9, URT0_RX, INPUT), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI|PIN_ATTR_CMP, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D19,  
          GPB_CFG(10, GPB10, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI| PIN_ATTR_I2C | PIN_ATTR_PWM, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },       


  // 20 .. 39 - Digital pins
  // ----------------------
  { .arduino_id=ARDUINO_PIN_D20,  
          GPB_CFG(11, GPB11, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART| PIN_ATTR_I2C|PIN_ATTR_DMA | PIN_ATTR_PWM,
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D21,
          GPB_CFG(12, GPB12, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL| PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_USB|PIN_ATTR_DMA , 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D22, 
          GPB_CFG(13, GPB13, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D23,  
          GPB_CFG(14, GPB14, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_DMA , 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D24,   
          GPB_CFG(15, GPB15, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_USB, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D25,   
          GPC_CFG(0, GPC0, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART| PIN_ATTR_I2C| PIN_ATTR_PWM, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT2_IRQn,    .configured=false },

  { .arduino_id=ARDUINO_PIN_D26,
          GPC_CFG(1, GPC1, INPUT_PULLUP),   
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART| PIN_ATTR_I2C|PIN_ATTR_ADC, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT2_IRQn,    .configured=false },

  { .arduino_id=ARDUINO_PIN_D27, 
          GPC_CFG(2, GPC2, INPUT_PULLUP),   
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_ADC, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT2_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D28,  
          GPC_CFG(3, GPC3, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT2_IRQn,    .configured=false },

  { .arduino_id=ARDUINO_PIN_D29,
          GPC_CFG(4, GPC4, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART| PIN_ATTR_I2C, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT2_IRQn,    .configured=false },

  { .arduino_id=ARDUINO_PIN_D30, 
          GPC_CFG(5, GPC5, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART| PIN_ATTR_I2C, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT2_IRQn,    .configured=false },

  	                       
  { .arduino_id=ARDUINO_PIN_D31, 
          GPC_CFG(6, RSTN, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART,  
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT2_IRQn,    .configured=false },

  { .arduino_id=ARDUINO_PIN_D32,  
          GPC_CFG(7, GPC7, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_ADC, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT2_IRQn,    .configured=false },


  	                       
  { .arduino_id=ARDUINO_PIN_D33, 
          GPC_CFG(8, GPC8, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART| PIN_ATTR_I2C|PIN_ATTR_ADC, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT2_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D34, 
          GPC_CFG(9, GPC9, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART| PIN_ATTR_I2C|PIN_ATTR_CMP, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT2_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D35,  
          GPC_CFG(10, GPC10, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART| PIN_ATTR_I2C|PIN_ATTR_CMP, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT2_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D36,  
          GPC_CFG(11, GPC11, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART| PIN_ATTR_I2C, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT2_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D37,   
          GPC_CFG(12, GPC12, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART| PIN_ATTR_PWM, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT2_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D38,  
          GPC_CFG(13, GPC13, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT2_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D39,  
          GPC_CFG(14, GPC14, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT2_IRQn,    .configured=false },


  // 40 .. 59 - Digital pins
  // ----------------------         
  { .arduino_id=ARDUINO_PIN_VSS1,
          GPNULL_CFG(),
  	             .mode=PIN_ATTR_NONE, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=NMI_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D41, 
          GPD_CFG(0, GPD0, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI| PIN_ATTR_PWM, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT3_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D42, 
          GPD_CFG(1, GPD1, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI,  
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT3_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D43,
          GPD_CFG(2, GPD2, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI|PIN_ATTR_USB| PIN_ATTR_PWM, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT3_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D44,  
          GPD_CFG(3, GPD3, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI|PIN_ATTR_USB, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT3_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_USBDM,  
          GPNULL_CFG(),
  	             .mode=PIN_ATTR_NONE, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=NMI_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_USBDP,  
          GPNULL_CFG(),
  	             .mode=PIN_ATTR_NONE, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=NMI_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_V33, 
          GPNULL_CFG(),
  	             .mode=PIN_ATTR_NONE, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=NMI_IRQn,    .configured=false },

  { .arduino_id=ARDUINO_PIN_D48, 
          GPD_CFG(7, GPD7, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT3_IRQn,    .configured=false },

  { .arduino_id=ARDUINO_PIN_D49,  
          GPD_CFG(8, GPD8, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT3_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D50, 
          GPD_CFG(9, GPD9, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI| PIN_ATTR_PWM, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT3_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D51,
          GPD_CFG(10, GPD10, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT3_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D52, 
          GPD_CFG(11, GPD11, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI|PIN_ATTR_DMA, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT3_IRQn,    .configured=false },


  { .arduino_id=ARDUINO_PIN_VSS,  
          GPNULL_CFG(),
  	             .mode=PIN_ATTR_NONE, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=NMI_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_VRD, 
          GPNULL_CFG(),
  	             .mode=PIN_ATTR_NONE, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=NMI_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_VDD, 
          GPNULL_CFG(),
  	             .mode=PIN_ATTR_NONE, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=NMI_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_VREF,
          GPNULL_CFG(),
  	             .mode=PIN_ATTR_NONE, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=NMI_IRQn,    .configured=false },


  { .arduino_id=ARDUINO_PIN_D57, 
          GPA_CFG(0, GPA0, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART, 
  	                       .ADCChannel= ADC_CHANNEL_0,   .IO_irqnb=EXINT0_IRQn,    .configured=false },

  { .arduino_id=ARDUINO_PIN_D58,
          GPA_CFG(1, GPA1, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART, 
  	                       .ADCChannel= ADC_CHANNEL_1,   .IO_irqnb=EXINT0_IRQn,    .configured=false },

  { .arduino_id=ARDUINO_PIN_D59,
          GPA_CFG(2, GPA2, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART, 
  	                       .ADCChannel= ADC_CHANNEL_2,   .IO_irqnb=EXINT0_IRQn,    .configured=false },


  // 60 .. 63 - Digital pins
  // ----------------------    
  { .arduino_id=ARDUINO_PIN_D60,
          GPA_CFG(3, GPA3, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART, 
  	                       .ADCChannel= ADC_CHANNEL_3,   .IO_irqnb=EXINT0_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D61, 
          GPA_CFG(4, GPA4, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART, 
  	                       .ADCChannel= ADC_CHANNEL_4,   .IO_irqnb=EXINT0_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D62,
          GPA_CFG(5, GPA5, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART, 
  	                       .ADCChannel= ADC_CHANNEL_5,   .IO_irqnb=EXINT0_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D63, 
          GPA_CFG(6, GPA6, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI, 
  	                       .ADCChannel= ADC_CHANNEL_6,   .IO_irqnb=EXINT0_IRQn,    .configured=false },
} ;



#ifdef __cplusplus
}
#endif

/*
 * UART objects
 */
Uart Serial( &mURT0,  
             ARDUINO_PIN_UART0_RX,
             ARDUINO_PIN_UART0_TX, 
             URT0_IRQn );

Uart Serial1( &mURT1, 
              ARDUINO_PIN_UART1_RX,
              ARDUINO_PIN_UART1_TX, 
              URT123_IRQn );

Uart Serial2( &mURT2,  
              ARDUINO_PIN_UART2_RX,
              ARDUINO_PIN_UART2_TX, 
              URT123_IRQn );

#if defined(URT3)
Uart Serial3( &mURT3,
              ARDUINO_PIN_UART3_RX,
              ARDUINO_PIN_UART3_TX, 
              URT123_IRQn );
#endif

Uart Serial4( &mURT4,  
              ARDUINO_PIN_UART4_RX,
              ARDUINO_PIN_UART4_TX, 
              URT4x_IRQn );
Uart Serial5( &mURT5,  
              ARDUINO_PIN_UART5_RX,
              ARDUINO_PIN_UART5_TX, 
              URT4x_IRQn );
Uart Serial6( &mURT6, 
              ARDUINO_PIN_UART6_RX,
              ARDUINO_PIN_UART6_TX, 
              URT4x_IRQn );
Uart Serial7( &mURT7,  
              ARDUINO_PIN_UART7_RX,
              ARDUINO_PIN_UART7_TX, 
              URT4x_IRQn );


void serialEvent() __attribute__((weak));
void serialEvent()
{
    ;
}

void serialEventRun(void)
{
    if(Serial.available() )
    {
        serialEvent();
    }

}



// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

void __libc_init_array(void);



void init( void )
{
    Pin_Struct*  pPinx;		
    GPIO_InitTypeDef GPIOX;
    int i;

    hw_config_init();


    // 基本初始化，如果是模拟或者时钟，则各模块各自进行初始化
    for(i=0; i<MAX_DIGITAL_IOS; i++)
    {
        if( ( g_APinDescription[i].mode==PIN_ATTR_NONE )
         || ( g_APinDescription[i].ulPort==NULL))
        {
            continue;

        }

        switch ( g_APinDescription[i].IO_Mode )
        {
            case INPUT:
                GPIOX.Mode = GPIO_MODE_OPENDRAIN_O;
                GPIOX.Pull = GPIO_NOPULLUP;
                break;

            case INPUT_PULLUP:
                GPIOX.Mode = GPIO_MODE_OPENDRAIN_O;
                GPIOX.Pull = GPIO_PULLUP;
                break;

            case INPUT_PULLDOWN:
                GPIOX.Mode = GPIO_MODE_OPENDRAIN_O;
                GPIOX.Pull = GPIO_NOPULLUP;
                break;

            case OUTPUT:
                GPIOX.Mode = GPIO_MODE_PUSHPULL_O;
                GPIOX.Pull = GPIO_PULLUP;
                break;
            default:
                GPIOX.Mode = GPIO_MODE_PUSHPULL_O;
                GPIOX.Pull = GPIO_PULLUP;
                break;
        }
        GPIOX.Pin            = g_APinDescription[i].GioPin;
        GPIOX.Speed          = GPIO_SPEED_LOW;
        GPIOX.OUTDrive       = GPIO_OUTDRIVE_LEVEL0;
        GPIOX.FilterDivider  = GPIO_FILTERDIVIDER_BYPASS;
        GPIOX.Inverse        = GPIO_INVERSE_DISABLE;
        GPIOX.Alternate      = g_APinDescription[i].AFS;
        pPinx = __GetPinxx_byGPIOx( g_APinDescription[i].ulPort, g_APinDescription[i].PinNum );
        
        MID_GPIO_Pin_Init(  pPinx,  &GPIOX);        
        g_APinDescription[i].configured = true;
    }

}

void initVariant()
{
    megawin_Uart_init();
        
    
    analogReadInit();
    analogOutputInit();

    Serial.begin( &mURT0,
                  ARDUINO_PIN_UART0_RX,
                  ARDUINO_PIN_UART0_TX,
                  URT0_IRQn,  9600  );
    
    timer_cfg_init();
    
    Megawin_EXIC_Init();

}



#ifdef __cplusplus
}
#endif




#ifdef __cplusplus
extern "C" {
#endif


extern uint32_t SystemCoreClock;
uint32_t HAL_RCC_GetHCLKFreq()
{
    return SystemCoreClock;
}


unsigned int PINCOUNT_fn() 
{
    return (sizeof(g_APinDescription) / sizeof(g_APinDescription[0]));
}




/* Private function prototypes -----------------------------------------------*/
int fputc(int ch, FILE *f __attribute__((unused)));
/*
 *******************************************************************************
 * @brief	 Replace printf fputc function.
 * @details     
 * @return      
 * @note       
 *******************************************************************************
 */
 /*
int fputc(int ch, FILE *f __attribute__((unused)))
{
    DEBUG_URTn->TDAT.B[0] = (uint8_t)ch;
    while((DEBUG_URTn->STA.W & URT_STA_TXF_mask_w)==0);
    
    return(ch);
}

*/


#ifdef __cplusplus
}
#endif


