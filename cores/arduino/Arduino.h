/*
  Arduino.h - Main include file for the Arduino SDK
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef Arduino_h
#define Arduino_h

#ifndef GCC_VERSION
#define GCC_VERSION (__GNUC__ * 10000 \
                     + __GNUC_MINOR__ * 100 \
                     + __GNUC_PATCHLEVEL__)
#endif
#if GCC_VERSION < 60300
  #error "GCC version 6.3 or higher is required"
#endif

#include "MG32x02z.h"
#include "MG32x02z_GPIO.h"
#include "system_MG32x02z.h"
#include "pins_arduino.h"
#include "MG32x02z_GPIO_DRV.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// some libraries and sketches depend on this
// AVR stuff, assuming Arduino.h or WProgram.h
// automatically includes it...
//#include <avr/pgmspace.h>
//#include <avr/interrupt.h>

#include "binary.h"
#include "itoa.h"



#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

#include "wiring_constants.h"

#include "uart.h"

//#define F_CPU SystemCoreClock //To be compatible with Arduino delay

#define clockCyclesPerMicrosecond() ( SystemCoreClock / 1000000L )
#define clockCyclesToMicroseconds(a) ( ((a) * 1000L) / (SystemCoreClock / 1000L) )
#define microsecondsToClockCycles(a) ( (a) * (SystemCoreClock / 1000000L) )

extern uint32_t SystemCoreClock;

void yield(void);

/* sketch */
extern void setup( void ) ;
extern void loop( void ) ;




#define  NB_ADC_CHANNEL_MANAGED   ((uint32_t)-1)

/* Types used for the tables below */
typedef struct _PinDescription
{
  uint16_t        arduino_id;
  uint16_t        AFS;
  uint16_t        PinNum ;
  uint16_t        GioPin ;
  GPIO_Struct    *ulPort;
  uint32_t        IO_Mode;
  uint32_t        mode;
  uint32_t        ADCChannel;
  IRQn_Type       IO_irqnb;
  uint32_t        configured;
} PinDescription ;

/*
#define INPUT          0x0
#define OUTPUT         0x1
#define INPUT_PULLUP   0x2
#define INPUT_PULLDOWN 0x3
*/


/**
 * Pin Attributes to be OR-ed
 */
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
#define PIN_ATTR_DMA           (1UL<<12)


//#define NB_PIN_DESCRIPTIONS (16*3)


void TestReg_clear();
int TestReg_push( uint32_t data );
int TestReg_print();


/* Pins table to be instanciated into variant.cpp */
extern PinDescription g_APinDescription[];

/* Define attribute */
#if defined   ( __CC_ARM   ) /* Keil uVision 4 */
    #define WEAK (__attribute__ ((weak)))
#elif defined ( __ICCARM__ ) /* IAR Ewarm 5.41+ */
    #define WEAK __weak
#elif defined (  __GNUC__  ) /* GCC CS */
    #define WEAK __attribute__ ((weak))
#endif


#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus


#ifdef __cplusplus

#include "WCharacter.h"
#include "WString.h"
#include "Tone.h"
#include "WMath.h"
#include "HardwareSerial.h"
#include "wiring_pulse.h"
#include "RTC.h"
#include "UARTClass.h"

#endif // __cplusplus



// Include board variant
#include "variant.h"
#include "wiring.h"
#include "wiring_digital.h"
#include "wiring_analog.h"
#include "wiring_shift.h"
#include "WInterrupts.h"



#endif // Arduino_h



