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


#include "pwm.h"

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



PinDescription  g_APinDescription[MAX_DIGITAL_IOS]=
{
    { .arduino_id=ARDUINO_PIN_D0, 
          GPC_CFG(9, GPC9, INPUT_PULLUP), 
                 .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART| PIN_ATTR_I2C|PIN_ATTR_CMP, 
                           .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT2_IRQn,    .configured=false },

  { .arduino_id=ARDUINO_PIN_D1, 
          GPC_CFG(8, GPC8, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART| PIN_ATTR_I2C|PIN_ATTR_ADC, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT2_IRQn,    .configured=false },
  	                         	        
  { .arduino_id=ARDUINO_PIN_D2, 
          GPB_CFG(4, GPB4, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D3,  
          GPB_CFG(10, GPB10, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI| PIN_ATTR_I2C | PIN_ATTR_PWM, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },       

  { .arduino_id=ARDUINO_PIN_D4,  
          GPC_CFG(7, GPC7, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_ADC, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT2_IRQn,    .configured=false },

  { .arduino_id=ARDUINO_PIN_D5,  
          GPB_CFG(11, GPB11, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART| PIN_ATTR_I2C|PIN_ATTR_DMA | PIN_ATTR_PWM,
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D6,   
          GPC_CFG(0, GPC0, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART| PIN_ATTR_I2C| PIN_ATTR_PWM, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT2_IRQn,    .configured=false },

  { .arduino_id=ARDUINO_PIN_D7, 
          GPB_CFG(5, GPB5, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D8,   
          GPC_CFG(12, GPC12, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART| PIN_ATTR_PWM, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT2_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D9, 
          GPD_CFG(0, GPD0, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI| PIN_ATTR_PWM, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT3_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D10, 
          GPD_CFG(9, GPD9, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI| PIN_ATTR_PWM, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT3_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D11,
          GPD_CFG(2, GPD2, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI|PIN_ATTR_USB| PIN_ATTR_PWM, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT3_IRQn,    .configured=false },

  { .arduino_id=ARDUINO_PIN_D12, 
          GPD_CFG(7, GPD7, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT3_IRQn,    .configured=false },

  { .arduino_id=ARDUINO_PIN_D13,  
          GPD_CFG(8, GPD8, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT3_IRQn,    .configured=false },



  { .arduino_id=ARDUINO_PIN_D14, 
          GPA_CFG(0, GPA0, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART, 
  	                       .ADCChannel= ADC_CHANNEL_0,   .IO_irqnb=EXINT0_IRQn,    .configured=false },

  { .arduino_id=ARDUINO_PIN_D15,
          GPA_CFG(1, GPA1, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART, 
  	                       .ADCChannel= ADC_CHANNEL_1,   .IO_irqnb=EXINT0_IRQn,    .configured=false },

  { .arduino_id=ARDUINO_PIN_D16,
          GPA_CFG(2, GPA2, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART, 
  	                       .ADCChannel= ADC_CHANNEL_2,   .IO_irqnb=EXINT0_IRQn,    .configured=false },


  { .arduino_id=ARDUINO_PIN_D17,
          GPA_CFG(3, GPA3, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART, 
  	                       .ADCChannel= ADC_CHANNEL_3,   .IO_irqnb=EXINT0_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D18, 
          GPA_CFG(4, GPA4, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART, 
  	                       .ADCChannel= ADC_CHANNEL_4,   .IO_irqnb=EXINT0_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D19,
          GPA_CFG(5, GPA5, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART, 
  	                       .ADCChannel= ADC_CHANNEL_5,   .IO_irqnb=EXINT0_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D20,   
          GPB_CFG(3, GPB3, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI| PIN_ATTR_I2C|PIN_ATTR_ADC, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D21,   
          GPB_CFG(2, GPB2, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI| PIN_ATTR_I2C|PIN_ATTR_ADC|PIN_ATTR_DAC, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D22,  
          GPC_CFG(11, GPC11, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART| PIN_ATTR_I2C, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT2_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D23,  
          GPC_CFG(10, GPC10, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART| PIN_ATTR_I2C|PIN_ATTR_CMP, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT2_IRQn,    .configured=false },

  { .arduino_id=ARDUINO_PIN_D24,  
          GPB_CFG(7, GPB7, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D25,
          GPB_CFG(6, GPB6, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D26, 
          GPB_CFG(13, GPB13, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D27,  
          GPB_CFG(14, GPB14, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_DMA , 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D28,   
          GPB_CFG(15, GPB15, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_USB, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D29,
          GPB_CFG(12, GPB12, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL| PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_USB|PIN_ATTR_DMA , 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D30,   
          GPB_CFG(1, GPB1, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_CMP|PIN_ATTR_SPI| PIN_ATTR_I2C, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D31,  
          GPB_CFG(0, GPB0, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_CMP|PIN_ATTR_SPI| PIN_ATTR_I2C, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D32, 
          GPD_CFG(1, GPD1, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI,  
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT3_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D33,  
          GPD_CFG(3, GPD3, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI|PIN_ATTR_USB, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT3_IRQn,    .configured=false },
  	               
  { .arduino_id=ARDUINO_PIN_D34,
          GPD_CFG(10, GPD10, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT3_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D35, 
          GPD_CFG(11, GPD11, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI|PIN_ATTR_DMA, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT3_IRQn,    .configured=false },
               
  { .arduino_id=ARDUINO_PIN_D36, 
          GPA_CFG(6, GPA6, INPUT_PULLUP),
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI, 
  	                       .ADCChannel= ADC_CHANNEL_6,   .IO_irqnb=EXINT0_IRQn,    .configured=false },

  { .arduino_id=ARDUINO_PIN_D37,
          GPA_CFG(7, GPA7, INPUT_PULLUP),   
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI, 
  	                       .ADCChannel= ADC_CHANNEL_7,   .IO_irqnb=EXINT0_IRQn,    .configured=false },
  	       
  { .arduino_id=ARDUINO_PIN_D38, 
          GPA_CFG(8, GPA8, INPUT_PULLUP),  
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_CMP|PIN_ATTR_SPI | PIN_ATTR_I2C|PIN_ATTR_DMA,  
  	                       .ADCChannel= ADC_CHANNEL_8,   .IO_irqnb=EXINT0_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D39, 
          GPA_CFG(9, GPA9, INPUT_PULLUP),   
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_CMP|PIN_ATTR_SPI | PIN_ATTR_I2C|PIN_ATTR_DMA, 
  	                       .ADCChannel= ADC_CHANNEL_9,   .IO_irqnb=EXINT0_IRQn,    .configured=false },	       

  { .arduino_id=ARDUINO_PIN_D40,
          GPA_CFG(10, GPA10, INPUT_PULLUP),   
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_CMP|PIN_ATTR_SPI | PIN_ATTR_I2C, 
  	                       .ADCChannel= ADC_CHANNEL_10,   .IO_irqnb=EXINT0_IRQn,    .configured=false },
  	                      
  	     	                       
  { .arduino_id=ARDUINO_PIN_D41, 
          GPA_CFG(11, GPA11, INPUT_PULLUP),   
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_CMP|PIN_ATTR_SPI | PIN_ATTR_I2C, 
  	                       .ADCChannel= ADC_CHANNEL_11,   .IO_irqnb=EXINT0_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D42, 
          GPA_CFG(12, GPA12, INPUT_PULLUP),   
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_USB|PIN_ATTR_SPI | PIN_ATTR_PWM, 
  	                       .ADCChannel= ADC_CHANNEL_12,   .IO_irqnb=EXINT0_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D43,   
          GPA_CFG(13, GPA13, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_USB|PIN_ATTR_SPI | PIN_ATTR_PWM, 
  	                       .ADCChannel= ADC_CHANNEL_13,   .IO_irqnb=EXINT0_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D44, 
          GPA_CFG(14, GPA14, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI, 
  	                       .ADCChannel= ADC_CHANNEL_14,   .IO_irqnb=EXINT0_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D45,  
          GPA_CFG(15, GPA15, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_ADC|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI, 
  	                       .ADCChannel= ADC_CHANNEL_15,   .IO_irqnb=EXINT0_IRQn,    .configured=false },          
  	                       
  	                       
  { .arduino_id=ARDUINO_PIN_D46,
          GPC_CFG(1, GPC1, INPUT_PULLUP),   
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART| PIN_ATTR_I2C|PIN_ATTR_ADC, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT2_IRQn,    .configured=false },

  { .arduino_id=ARDUINO_PIN_D47, 
          GPC_CFG(6, RSTN, INPUT_PULLUP), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART,  
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT2_IRQn,    .configured=false },


  { .arduino_id=ARDUINO_PIN_D48, 
          GPB_CFG(8, URT0_TX, OUTPUT), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI|PIN_ATTR_CMP, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },
  	                       
  { .arduino_id=ARDUINO_PIN_D49, 
          GPB_CFG(9, URT0_RX, INPUT), 
  	             .mode=PIN_ATTR_DIGITAL|PIN_ATTR_TIMER |PIN_ATTR_EXTINT|PIN_ATTR_UART|PIN_ATTR_SPI|PIN_ATTR_CMP, 
  	                       .ADCChannel=NB_ADC_CHANNEL_MANAGED,   .IO_irqnb=EXINT1_IRQn,    .configured=false },

};




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
    return (sizeof(g_APinDescription) / sizeof(PinDescription));
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


/*
 * \brief Set the analog PWM output frequency.
 *
 * \param ulPin
 * 3: Set the PWM frequency of pin D3. (The frequency of D6 pin will be modified synchronously)
 * 5: Set the PWM frequency of pin D5. (The frequency of D8 and D9 pins will be modified synchronously)
 * 6: Set the PWM frequency of pin D6. (The frequency of D6 pin will be modified synchronously)
 * 8: Set the PWM frequency of pin D8. (The frequency of D5 and D9 pins will be modified synchronously)
 * 9: Set the PWM frequency of pin D9. (The frequency of D5 and D8 pins will be modified synchronously)
 * 10: Set the PWM frequency of pin D10. (The frequency of D11 pin will be modified synchronously)
 * 11: Set the PWM frequency of pin D11. (The frequency of D10 pin will be modified synchronously)
 * Or use optional macros:
 * PWM_FRQ_D3_D6: Set the PWM frequency of pin D3 and pin D6 at the same time. (same as setting pin D3 or pin D6 separately)
 * PWM_FRQ_D5_D8_D9: Set the PWM frequency of pin D5, pin D8 and pin D9 at the same time. (Same effect as setting pin D5, pin D8 or pin D9 separately)
 * PWM_FRQ_D10_D11: Set the PWM frequency of pin D10 and pin D1 at the same time (same as setting pin D10 or pin D11 separately).
 * PWM_FRQ_ALL: Set the PWM frequency of all pins simultaneously.
 *
 * \param freq£ºthe frequency 300~5000(Hz)
 */
void analogWriteFrequency( uint32_t ulPin,  uint32_t freq)
{
    if( freq < 300 )
    {
        freq = 300;
    }
    else if( freq > 5000 )
    {
        freq = 5000;
    }
    
    switch( ulPin )
    {
        case 3:
        case 6:
        case PWM_FRQ_D3_D6:
            pwm_setFrequency(  3,  freq );
            pwm_setFrequency(  6,  freq );
            break;
        case 5:
        case 8:
        case 9:
        case PWM_FRQ_D5_D8_D9:
            pwm_setFrequency(  5,  freq );
            pwm_setFrequency(  8,  freq );
            pwm_setFrequency(  9,  freq );
            break;
        case 10:
        case 11:
        case PWM_FRQ_D10_D11:
            pwm_setFrequency(  10,  freq );
            pwm_setFrequency(  11,  freq );
            break;
        case PWM_FRQ_ALL:
            pwm_setFrequency(  3,  freq );
            pwm_setFrequency(  6,  freq );
            pwm_setFrequency(  5,  freq );
            pwm_setFrequency(  8,  freq );
            pwm_setFrequency(  9,  freq );
            pwm_setFrequency(  10,  freq );
            pwm_setFrequency(  11,  freq );
            break;
        default:
            return;
    }
    
    //pwm_setFrequency(  ulPin,  freq );
    return;
}



#ifdef __cplusplus
}
#endif


