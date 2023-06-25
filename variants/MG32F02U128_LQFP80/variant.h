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
#define ARDUINO_PIN_D0           (0ul)
#define ARDUINO_PIN_D1           (1ul)
#define ARDUINO_PIN_D2           (2ul)
#define ARDUINO_PIN_D3           (3ul)
#define ARDUINO_PIN_D4           (4ul)
#define ARDUINO_PIN_D5           (5ul)
#define ARDUINO_PIN_D6           (6ul)
#define ARDUINO_PIN_D7           (7ul)
#define ARDUINO_PIN_D8           (8ul)
#define ARDUINO_PIN_D9           (9ul)
#define ARDUINO_PIN_D10          (10ul)
#define ARDUINO_PIN_D11          (11ul)
#define ARDUINO_PIN_D12          (12ul)
#define ARDUINO_PIN_D13          (13ul)
#define ARDUINO_PIN_D14          (14ul)
#define ARDUINO_PIN_D15          (15ul)
#define ARDUINO_PIN_D16          (16ul)
#define ARDUINO_PIN_D17          (17ul)
#define ARDUINO_PIN_D18          (18ul)
#define ARDUINO_PIN_D19          (19ul)


#define ARDUINO_PIN_D20          (20ul)
#define ARDUINO_PIN_D21          (21ul)
#define ARDUINO_PIN_D22          (22ul)
#define ARDUINO_PIN_D23          (23ul)
#define ARDUINO_PIN_D24          (24ul)
#define ARDUINO_PIN_D25          (25ul)
#define ARDUINO_PIN_VDD2         (26ul)   //#define ARDUINO_PIN_D26          (26ul)
#define ARDUINO_PIN_D27          (27ul)
#define ARDUINO_PIN_D28          (28ul)
#define ARDUINO_PIN_VSS2         (29ul)   //#define ARDUINO_PIN_D29          (29ul)
#define ARDUINO_PIN_D30          (30ul)
#define ARDUINO_PIN_D31          (31ul)
#define ARDUINO_PIN_D32          (32ul)
#define ARDUINO_PIN_D33          (33ul)
#define ARDUINO_PIN_D34          (34ul)
#define ARDUINO_PIN_D35          (35ul)
#define ARDUINO_PIN_D36          (36ul)
#define ARDUINO_PIN_D37          (37ul)
#define ARDUINO_PIN_D38          (38ul)
#define ARDUINO_PIN_D39          (39ul)


#define ARDUINO_PIN_D40          (40ul)
#define ARDUINO_PIN_D41          (41ul)
#define ARDUINO_PIN_D42          (42ul)
#define ARDUINO_PIN_D43          (43ul)
#define ARDUINO_PIN_D44          (44ul)
#define ARDUINO_PIN_D45          (45ul)
#define ARDUINO_PIN_D46          (46ul)
#define ARDUINO_PIN_D47          (47ul)
#define ARDUINO_PIN_VSS1         (48ul)   //#define ARDUINO_PIN_D48          (48ul)
#define ARDUINO_PIN_D49          (49ul)
#define ARDUINO_PIN_D50          (50ul)
#define ARDUINO_PIN_D51          (51ul)
#define ARDUINO_PIN_D52          (52ul)
#define ARDUINO_PIN_D53          (53ul)
#define ARDUINO_PIN_D54          (54ul)
#define ARDUINO_PIN_D55          (55ul)
#define ARDUINO_PIN_D56          (56ul)
#define ARDUINO_PIN_USBDM        (57ul)  //#define ARDUINO_PIN_D57          (57ul)
#define ARDUINO_PIN_USBDP        (58ul)  //#define ARDUINO_PIN_D58          (58ul)
#define ARDUINO_PIN_V33          (59ul)  //#define ARDUINO_PIN_D59          (59ul)


#define ARDUINO_PIN_D60          (60ul)
#define ARDUINO_PIN_D61          (61ul)
#define ARDUINO_PIN_D62          (62ul)
#define ARDUINO_PIN_D63          (63ul)
#define ARDUINO_PIN_D64          (64ul)
#define ARDUINO_PIN_D65          (65ul)
#define ARDUINO_PIN_D66          (66ul)
#define ARDUINO_PIN_D67          (67ul)
#define ARDUINO_PIN_D68          (68ul)
#define ARDUINO_PIN_VSS          (69ul)   //#define ARDUINO_PIN_D69          (69ul)
#define ARDUINO_PIN_VR0          (70ul)   //#define ARDUINO_PIN_D70          (70ul)
#define ARDUINO_PIN_VDD          (71ul)   //#define ARDUINO_PIN_D71          (71ul)
#define ARDUINO_PIN_VREF         (72ul)   //#define ARDUINO_PIN_D72          (72ul)
#define ARDUINO_PIN_D73          (73ul)
#define ARDUINO_PIN_D74          (74ul)
#define ARDUINO_PIN_D75          (75ul)
#define ARDUINO_PIN_D76          (76ul)
#define ARDUINO_PIN_D77          (77ul)
#define ARDUINO_PIN_D78          (78ul)
#define ARDUINO_PIN_D79          (79ul)


//pin for hardware
/*
#define ARDUINO_PIN_VDD2         (26ul)
#define ARDUINO_PIN_VSS2         (29ul)
#define ARDUINO_PIN_VSS1         (48ul)

#define ARDUINO_PIN_USBDM        (57ul)
#define ARDUINO_PIN_USBDP        (58ul)
#define ARDUINO_PIN_V33          (59ul)
#define ARDUINO_PIN_VSS          (69ul)
#define ARDUINO_PIN_VR0          (70ul)
#define ARDUINO_PIN_VDD          (71ul)
#define ARDUINO_PIN_VREF         (72ul)
*/

#define MAX_DIGITAL_IOS           (80)



#define ARDUINO_PIN_A0               ARDUINO_PIN_D73
#define ARDUINO_PIN_A1               ARDUINO_PIN_D74
#define ARDUINO_PIN_A2               ARDUINO_PIN_D75
#define ARDUINO_PIN_A3               ARDUINO_PIN_D76
#define ARDUINO_PIN_A4               ARDUINO_PIN_D77
#define ARDUINO_PIN_A5               ARDUINO_PIN_D78
#define ARDUINO_PIN_A6               ARDUINO_PIN_D79
#define ARDUINO_PIN_A7               ARDUINO_PIN_D0
#define ARDUINO_PIN_A8               ARDUINO_PIN_D1
#define ARDUINO_PIN_A9               ARDUINO_PIN_D2
#define ARDUINO_PIN_A10              ARDUINO_PIN_D3
#define ARDUINO_PIN_A11              ARDUINO_PIN_D4
#define ARDUINO_PIN_A12              ARDUINO_PIN_D5
#define ARDUINO_PIN_A13              ARDUINO_PIN_D6
#define ARDUINO_PIN_A14              ARDUINO_PIN_D7
#define ARDUINO_PIN_A15              ARDUINO_PIN_D8

#define MAX_ANALOG_IOS               16

#define ARDUINO_PIN_DAC             ARDUINO_PIN_D11

#define ARDUINO_PIN_EXT1            ARDUINO_PIN_D12
#define ARDUINO_PIN_EXT2            ARDUINO_PIN_D13

//Morpho connector IOS
//#define ARDUINO_PIN_EXT               0x10000000




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
#define MCU_PA7               ARDUINO_PIN_D0
#define MCU_PA8               ARDUINO_PIN_D1
#define MCU_PA9               ARDUINO_PIN_D2
#define MCU_PA10              ARDUINO_PIN_D3
#define MCU_PA11              ARDUINO_PIN_D4
#define MCU_PA12              ARDUINO_PIN_D5
#define MCU_PA13              ARDUINO_PIN_D6
#define MCU_PA14              ARDUINO_PIN_D7
#define MCU_PA15              ARDUINO_PIN_D8

#define MCU_PB0               ARDUINO_PIN_D9
#define MCU_PB1               ARDUINO_PIN_D10
#define MCU_PB2               ARDUINO_PIN_D11
#define MCU_PB3               ARDUINO_PIN_D12

#define MCU_PE0               ARDUINO_PIN_D13
#define MCU_PE1               ARDUINO_PIN_D14
#define MCU_PE2               ARDUINO_PIN_D15
#define MCU_PE3               ARDUINO_PIN_D16

#define MCU_PB4               ARDUINO_PIN_D17
#define MCU_PB5               ARDUINO_PIN_D18
#define MCU_PB6               ARDUINO_PIN_D19

////--------------------------------------------------------
#define MCU_PB7               ARDUINO_PIN_D20
#define MCU_PB8               ARDUINO_PIN_D21
#define MCU_PB9               ARDUINO_PIN_D22
#define MCU_PB10              ARDUINO_PIN_D23
#define MCU_PB11              ARDUINO_PIN_D24
#define MCU_PB12              ARDUINO_PIN_D25

#define MCU_PB13              ARDUINO_PIN_D27
#define MCU_PB14              ARDUINO_PIN_D28
#define MCU_PB15              ARDUINO_PIN_D30

#define MCU_PE8               ARDUINO_PIN_D31
#define MCU_PE9               ARDUINO_PIN_D32


#define MCU_PC0               ARDUINO_PIN_D33
#define MCU_PC1               ARDUINO_PIN_D34
#define MCU_PC2               ARDUINO_PIN_D35
#define MCU_PC3               ARDUINO_PIN_D36
#define MCU_PC4               ARDUINO_PIN_D37
#define MCU_PC5               ARDUINO_PIN_D38
#define MCU_PC6               ARDUINO_PIN_D39

////--------------------------------------------------------
#define MCU_PC7               ARDUINO_PIN_D40
#define MCU_PC8               ARDUINO_PIN_D41
#define MCU_PC9               ARDUINO_PIN_D42
#define MCU_PC10              ARDUINO_PIN_D43
#define MCU_PC11              ARDUINO_PIN_D44
#define MCU_PC12              ARDUINO_PIN_D45
#define MCU_PC13              ARDUINO_PIN_D46
#define MCU_PC14              ARDUINO_PIN_D47



#define MCU_PE12              ARDUINO_PIN_D49
#define MCU_PE13              ARDUINO_PIN_D50
#define MCU_PE14              ARDUINO_PIN_D51
#define MCU_PE15              ARDUINO_PIN_D52

#define MCU_PD0               ARDUINO_PIN_D53
#define MCU_PD1               ARDUINO_PIN_D54
#define MCU_PD2               ARDUINO_PIN_D55
#define MCU_PD3               ARDUINO_PIN_D56

////--------------------------------------------------------

#define MCU_PD7               ARDUINO_PIN_D60
#define MCU_PD8               ARDUINO_PIN_D61
#define MCU_PD9               ARDUINO_PIN_D62
#define MCU_PD10              ARDUINO_PIN_D63
#define MCU_PD11              ARDUINO_PIN_D64
#define MCU_PD12              ARDUINO_PIN_D65
#define MCU_PD13              ARDUINO_PIN_D66
#define MCU_PD14              ARDUINO_PIN_D67
#define MCU_PD15              ARDUINO_PIN_D68



#define MCU_PA0               ARDUINO_PIN_D73
#define MCU_PA1               ARDUINO_PIN_D74
#define MCU_PA2               ARDUINO_PIN_D75
#define MCU_PA3               ARDUINO_PIN_D76
#define MCU_PA4               ARDUINO_PIN_D77
#define MCU_PA5               ARDUINO_PIN_D78
#define MCU_PA6               ARDUINO_PIN_D79

////--------------------------------------------------------
//On-board LED pin number
#define LED_BUILTIN                   13

//SPI defintions
//define 16 channels. As many channel as digital IOs
#define SPI_CHANNELS_NUM        16

//default chip salect pin
#define BOARD_SPI_DEFAULT_SS    MCU_PD9

//In case SPI CS channel is not used we define a default one
#define BOARD_SPI_OWN_SS        SPI_CHANNELS_NUM

#define SPI_INTERFACES_COUNT    1

static const uint8_t SS   = BOARD_SPI_DEFAULT_SS;
static const uint8_t MOSI = MCU_PD2;
static const uint8_t MISO = MCU_PD7;
static const uint8_t SCK  = MCU_PD8;

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

//#define analogInputToDigitalPin(p)  ((p < 7) ? ((p) + ARDUINO_PIN_D74) : (p))
#define analogInputToDigitalPin(p)    (p)



#ifdef __cplusplus
}
#endif


#endif /* _VARIANT_ARDUINO_STM32_ */


