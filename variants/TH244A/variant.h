/*
  Copyright (c) 2022 megawin Technology Co., Ltd. All rights reserved.

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

#ifndef _VARIANT_ARDUINO_H_
#define _VARIANT_ARDUINO_H_

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/
#define   _Y_230419_

/** Frequency of the board main oscillator */
//#define VARIANT_MAINOSC		12000000

/** Master clock frequency */
//#define VARIANT_MCK			84000000

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "Arduino.h"

#ifdef __cplusplus
#include "UARTClass.h"
//#include "USARTClass.h"
#endif

//WI6LABS ----> TBD
#ifdef __cplusplus
extern "C" unsigned int PINCOUNT_fn();
#endif
#define PINS_COUNT           (PINCOUNT_fn())


/**
 * Libc porting layers
 */
#if defined (  __GNUC__  ) /* GCC CS3 */
#    include <syscalls.h> /** RedHat Newlib minimal stub */
#endif


/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

//#define digitalPinToPort(P)        ( g_APinDescription[P].ulPort )
//#define digitalPinToBitMask(P)     ( g_APinDescription[P].ulPin )

//defines here the type of the pin
/*
#define PIN_ATTR_NONE          (0UL<<0)
#define PIN_ATTR_COMBO         (1UL<<0)
#define PIN_ATTR_ADC           (1UL<<1)
#define PIN_ATTR_DAC           (1UL<<2)
#define PIN_ATTR_DIGITAL       (1UL<<3)
#define PIN_ATTR_TIMER         (1UL<<4)
#define PIN_ATTR_EXTINT        (1UL<<5)
#define PIN_ATTR_PWM           (1UL<<6)
#define PIN_ATTR_I2C           (1UL<<7)
#define PIN_ATTR_SPI           (1UL<<8)
#define PIN_ATTR_UART          (1UL<<9)
#define PIN_ATTR_USB           (1UL<<10)
#define PIN_ATTR_CMP           (1UL<<11)
*/


//defines here the ardduino IOs type
//digital pins
#define  ARDUINO_PIN_D0        (0)
#define  ARDUINO_PIN_D1        (1)
#define  ARDUINO_PIN_D2        (2)
#define  ARDUINO_PIN_D3        (3)
#define  ARDUINO_PIN_D4        (4)
#define  ARDUINO_PIN_D5        (5)
#define  ARDUINO_PIN_D6        (6)
#define  ARDUINO_PIN_D7        (7)
#define  ARDUINO_PIN_D8        (8)
#define  ARDUINO_PIN_D9        (9)

#define  ARDUINO_PIN_D10        (10)
#define  ARDUINO_PIN_D11        (11)
#define  ARDUINO_PIN_D12        (12)
#define  ARDUINO_PIN_D13        (13)
#define  ARDUINO_PIN_D14        (14)
#define  ARDUINO_PIN_D15        (15)
#define  ARDUINO_PIN_D16        (16)
#define  ARDUINO_PIN_D17        (17)
#define  ARDUINO_PIN_D18        (18)
#define  ARDUINO_PIN_D19        (19)

#define  ARDUINO_PIN_D20        (20)
#define  ARDUINO_PIN_D21        (21)
#define  ARDUINO_PIN_D22        (22)
#define  ARDUINO_PIN_D23        (23)
#define  ARDUINO_PIN_D24        (24)
#define  ARDUINO_PIN_D25        (25)
#define  ARDUINO_PIN_D26        (26)
#define  ARDUINO_PIN_D27        (27)
#define  ARDUINO_PIN_D28        (28)
#define  ARDUINO_PIN_D29        (29)

#define  ARDUINO_PIN_D30        (30)
#define  ARDUINO_PIN_D31        (31)
#define  ARDUINO_PIN_D32        (32)
#define  ARDUINO_PIN_D33        (33)
#define  ARDUINO_PIN_D34        (34)
#define  ARDUINO_PIN_D35        (35)
#define  ARDUINO_PIN_D36        (36)
#define  ARDUINO_PIN_D37        (37)
#define  ARDUINO_PIN_D38        (38)
#define  ARDUINO_PIN_D39        (39)

#define  ARDUINO_PIN_D40        (40)
#define  ARDUINO_PIN_D41        (41)
#define  ARDUINO_PIN_D42        (42)
#define  ARDUINO_PIN_D43        (43)
#define  ARDUINO_PIN_D44        (44)
#define  ARDUINO_PIN_D45        (45)
#define  ARDUINO_PIN_D46        (46)
#define  ARDUINO_PIN_D47        (47)
#define  ARDUINO_PIN_D48        (48)
#define  ARDUINO_PIN_D49        (49)

#define  MCU_PC9               ARDUINO_PIN_D0
#define  MCU_PC8               ARDUINO_PIN_D1
#define  MCU_PB4               ARDUINO_PIN_D2
#define  MCU_PB10              ARDUINO_PIN_D3
#define  MCU_PC7               ARDUINO_PIN_D4
#define  MCU_PB11              ARDUINO_PIN_D5
#define  MCU_PC0               ARDUINO_PIN_D6
#define  MCU_PB5               ARDUINO_PIN_D7
#define  MCU_PC12              ARDUINO_PIN_D8
#define  MCU_PD0               ARDUINO_PIN_D9
#define  MCU_PD9               ARDUINO_PIN_D10
#define  MCU_PD2               ARDUINO_PIN_D11
#define  MCU_PD7               ARDUINO_PIN_D12
#define  MCU_PD8               ARDUINO_PIN_D13
#define  MCU_PA0               ARDUINO_PIN_D14
#define  MCU_PA1               ARDUINO_PIN_D15
#define  MCU_PA2               ARDUINO_PIN_D16
#define  MCU_PA3               ARDUINO_PIN_D17
#define  MCU_PA4               ARDUINO_PIN_D18
#define  MCU_PA5               ARDUINO_PIN_D19
#define  MCU_PB3               ARDUINO_PIN_D20
#define  MCU_PB2               ARDUINO_PIN_D21
#define  MCU_PC11              ARDUINO_PIN_D22
#define  MCU_PC10              ARDUINO_PIN_D23
#define  MCU_PB7               ARDUINO_PIN_D24
#define  MCU_PB6               ARDUINO_PIN_D25
#define  MCU_PB13              ARDUINO_PIN_D26
#define  MCU_PB14              ARDUINO_PIN_D27
#define  MCU_PB15              ARDUINO_PIN_D28
#define  MCU_PB12              ARDUINO_PIN_D29
#define  MCU_PB1               ARDUINO_PIN_D30
#define  MCU_PB0               ARDUINO_PIN_D31
#define  MCU_PD1               ARDUINO_PIN_D32
#define  MCU_PD3               ARDUINO_PIN_D33
#define  MCU_PD10              ARDUINO_PIN_D34
#define  MCU_PD11              ARDUINO_PIN_D35
#define  MCU_PA6               ARDUINO_PIN_D36
#define  MCU_PA7               ARDUINO_PIN_D37
#define  MCU_PA8               ARDUINO_PIN_D38
#define  MCU_PA9               ARDUINO_PIN_D39
#define  MCU_PA10              ARDUINO_PIN_D40
#define  MCU_PA11              ARDUINO_PIN_D41
#define  MCU_PA12              ARDUINO_PIN_D42
#define  MCU_PA13              ARDUINO_PIN_D43
#define  MCU_PA14              ARDUINO_PIN_D44
#define  MCU_PA15              ARDUINO_PIN_D45
#define  MCU_PC1               ARDUINO_PIN_D46
#define  MCU_PC6               ARDUINO_PIN_D47
#define  MCU_PB8               ARDUINO_PIN_D48
#define  MCU_PB9               ARDUINO_PIN_D49



#define MAX_DIGITAL_IOS           (46+1+1+2)      //(45pin+Button+RST+uart02)


#define  MCU_PC4   ((uint32_t)-1)       //(-1)       //unuse
#define  MCU_PC5   ((uint32_t)-1)       //(-1)       //unuse
#define  MCU_PC13  ((uint32_t)-1)       //(-1)       //unuse
#define  MCU_PC14  ((uint32_t)-1)       //(-1)       //unuse


////////////define ADC pin////////////////////////////////////////////////////
#define ARDUINO_PIN_A0               MCU_PA0
#define ARDUINO_PIN_A1               MCU_PA1
#define ARDUINO_PIN_A2               MCU_PA2
#define ARDUINO_PIN_A3               MCU_PA3
#define ARDUINO_PIN_A4               MCU_PA4
#define ARDUINO_PIN_A5               MCU_PA5
#define ARDUINO_PIN_A6               MCU_PA6
#define ARDUINO_PIN_A7               MCU_PA7
#define ARDUINO_PIN_A8               MCU_PA8
#define ARDUINO_PIN_A9               MCU_PA9
#define ARDUINO_PIN_A10              MCU_PA10
#define ARDUINO_PIN_A11              MCU_PA11
#define ARDUINO_PIN_A12              MCU_PA12
#define ARDUINO_PIN_A13              MCU_PA13
#define ARDUINO_PIN_A14              MCU_PA14
#define ARDUINO_PIN_A15              MCU_PA15

#define MAX_ANALOG_IOS               16


////////////define DAC pin////////////////////////////////////////////////////
#define ARDUINO_PIN_DAC0            MCU_PB2


//Analog pins
static const uint8_t A0  = ARDUINO_PIN_A0;
static const uint8_t A1  = ARDUINO_PIN_A1;
static const uint8_t A2  = ARDUINO_PIN_A2;
static const uint8_t A3  = ARDUINO_PIN_A3;
static const uint8_t A4  = ARDUINO_PIN_A4;
static const uint8_t A5  = ARDUINO_PIN_A5;

static const uint8_t A6   = ARDUINO_PIN_A6;
static const uint8_t A7   = ARDUINO_PIN_A7;
static const uint8_t A8   = ARDUINO_PIN_A8;
static const uint8_t A9   = ARDUINO_PIN_A9;
static const uint8_t A10  = ARDUINO_PIN_A10;
static const uint8_t A11  = ARDUINO_PIN_A11;
static const uint8_t A12  = ARDUINO_PIN_A12;
static const uint8_t A13  = ARDUINO_PIN_A13;
static const uint8_t A14  = ARDUINO_PIN_A14;
static const uint8_t A15  = ARDUINO_PIN_A15;




//ADC resolution is 12bits
#define ADC_RESOLUTION                10
#define DACC_RESOLUTION               12


//PWR resolution
#define PWM_RESOLUTION                8
#define PWM_FREQUENCY                 1000
#define PWM_MAX_DUTY_CYCLE            255


////--------------------------------------------------------


//SPI defintions
//define 16 channels. As many channel as digital IOs
#define SPI_CHANNELS_NUM        16

//default chip salect pin
#define BOARD_SPI_DEFAULT_SS    ARDUINO_PIN_D10

//In case SPI CS channel is not used we define a default one
#define BOARD_SPI_OWN_SS        BOARD_SPI_DEFAULT_SS   //SPI_CHANNELS_NUM

#define SPI_INTERFACES_COUNT    1


static const uint8_t SS   = BOARD_SPI_DEFAULT_SS;
static const uint8_t MOSI = ARDUINO_PIN_D11;
static const uint8_t MISO = ARDUINO_PIN_D12;
static const uint8_t SCK  = ARDUINO_PIN_D13;

//Enable Firmata
//Default pin set:
#define DEBUG_URTn       URT0             //URT4 
#define DEBUG_URTn_ID    USART0_E

#define  ARDUINO_PIN_UART0_TX         MCU_PB8
#define  ARDUINO_PIN_UART0_RX         MCU_PB9

#define  ARDUINO_PIN_UART1_TX         MCU_PC8
#define  ARDUINO_PIN_UART1_RX         MCU_PC9

#define  ARDUINO_PIN_UART2_TX         MCU_PB6
#define  ARDUINO_PIN_UART2_RX         MCU_PB7

#define  ARDUINO_PIN_UART4_TX         MCU_PB14
#define  ARDUINO_PIN_UART4_RX         MCU_PB13

#define  ARDUINO_PIN_UART5_TX         MCU_PB12
#define  ARDUINO_PIN_UART5_RX         MCU_PB15


#define  ARDUINO_PIN_UART6_TX         MCU_PB0
#define  ARDUINO_PIN_UART6_RX         MCU_PB1

#define  ARDUINO_PIN_UART7_TX         MCU_PB2
#define  ARDUINO_PIN_UART7_RX         MCU_PB3


#define  ARDUINO_PIN_I2C0_SCL         MCU_PB3
#define  ARDUINO_PIN_I2C0_SDL         MCU_PB2

#define  ARDUINO_PIN_I2C1_SCL         MCU_PC10
#define  ARDUINO_PIN_I2C1_SDL         MCU_PC11

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
/*
 * UART objects
 */
extern Uart Serial;
extern Uart Serial1;
extern Uart Serial2;
#if defined(URT3)
extern Uart Serial3;
#endif
extern Uart Serial4;
extern Uart Serial5;
extern Uart Serial6;
extern Uart Serial7;
#endif



#if defined(EXIC_PE_Base)
#define  __GetIOMx_byGPIOx( x )   ( (IOM_Struct *)( ((x)==GPIOA)?IOMA_Base:  (((x)==GPIOB)?IOMB_Base:  (((x)==GPIOC)?IOMC_Base:   (((x)==GPIOD)?IOMD_Base: (((x)==GPIOE)?IOME_Base: 0)  )))) )
#define  __GetEXICx_byGPIOx( x )  (EXIC_HandleTypeDef *)( ((x)==GPIOA)?(&mEXIC_PA): (((x)==GPIOB)?(&mEXIC_PB): (((x)==GPIOC)?(&mEXIC_PC):  (((x)==GPIOD)?(&mEXIC_PD):(((x)==GPIOE)?(&mEXIC_PE): 0)  ))))   
#else
#define  __GetIOMx_byGPIOx( x )   ( (IOM_Struct *)( ((x)==GPIOA)?IOMA_Base:  (((x)==GPIOB)?IOMB_Base:  (((x)==GPIOC)?IOMC_Base:   (((x)==GPIOD)?IOMD_Base: 0  )))) )
#define  __GetEXICx_byGPIOx( x )  (EXIC_HandleTypeDef *)( ((x)==GPIOA)?(&mEXIC_PA): (((x)==GPIOB)?(&mEXIC_PB): (((x)==GPIOC)?(&mEXIC_PC):  (((x)==GPIOD)?(&mEXIC_PD):0  ))))   
#endif


#define  __GetPinxx_byGPIOx( Port, PinNum )  ((Pin_Struct*)((uint32_t) ( ((uint32_t) __GetIOMx_byGPIOx( (Port) )) + (0x4*PinNum))))

#ifdef __cplusplus
extern "C" {
#endif

extern uint32_t SystemCoreClock;

/* Pins table to be instanciated into variant.cpp */
//extern const PinDescription g_APinDescription[MAX_DIGITAL_IOS];

unsigned int PINCOUNT_fn();
uint32_t HAL_RCC_GetHCLKFreq();
void init( );
void initVariant();


// Interrupts
#define digitalPinToInterrupt(p)  ((p) < MAX_DIGITAL_IOS ? (p) : -1)
  
#define digitalPinToPort(P)        ( g_APinDescription[P].ulPort )
#define digitalPinToBitMask(P)     ( g_APinDescription[P].GioPin )

#define portOutputRegister(port)   ( &(port->OUT.W) )
#define portInputRegister(port)    ( &(port->IN.H[0]) )

//#define analogInputToDigitalPin(p)  ((p < 7) ? ((p) + MCU_PIN_D57) : (p-7))
#define analogInputToDigitalPin(p)    (p)


#define PWM_FRQ_D3_D6              0x1000
#define PWM_FRQ_D5_D8_D9           0x2000
#define PWM_FRQ_D10_D11            0x3000
#define PWM_FRQ_ALL                0xFFFF

#ifdef __cplusplus
}
#endif



#define LED_BUILTIN     (13)


#endif /* _VARIANT_ARDUINO_STM32_ */


