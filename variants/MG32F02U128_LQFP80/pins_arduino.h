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
#ifndef _PINS_ARDUINO_H_
#define _PINS_ARDUINO_H_
// API compatibility
#include "variant.h"


typedef enum {
  AFS0   = 0,
  AFS1   = 1,
  AFS2   = 2,
  AFS3   = 3,
  AFS4   = 4,
  AFS5   = 5,
  AFS6   = 6,
  AFS7   = 7,
  AFS8   = 8,
  AFS9   = 9,
  AFS10  = 10,
  AFS11  = 11,
} PIN_AFS_e;


 
#define PA0_AFS_0         AFS0
#define PA0_AFS_6         AFS6
#define PA0_AFS_7         AFS7
#define PA0_AFS_8         AFS8
#define PA0_AFS_9         AFS9
#define PA0_AFS_10        AFS10
#define PA0_AFS_11        AFS11

#define PA0_AFS_GPA0         PA0_AFS_0
#define PA0_AFS_SDT_P0       PA0_AFS_6
#define PA0_AFS_CCL_P0       PA0_AFS_7
#define PA0_AFS_MA0          PA0_AFS_8
#define PA0_AFS_MAD0         PA0_AFS_9
#define PA0_AFS_TM36_OC00    PA0_AFS_10
#define PA0_AFS_URT4_TX      PA0_AFS_11

 
#define PA1_AFS_0         AFS0
#define PA1_AFS_7         AFS7
#define PA1_AFS_8         AFS8
#define PA1_AFS_9         AFS9
#define PA1_AFS_10        AFS10
#define PA1_AFS_11        AFS11
 
#define PA1_AFS_GPA1         PA1_AFS_0
#define PA1_AFS_CCL_P1       PA1_AFS_7
#define PA1_AFS_MA1          PA1_AFS_8
#define PA1_AFS_MAD1         PA1_AFS_9
#define PA1_AFS_TM36_OC10    PA1_AFS_10
#define PA1_AFS_URT4_RX      PA1_AFS_11


#define PA2_AFS_0         AFS0
#define PA2_AFS_6         AFS6
#define PA2_AFS_8         AFS8
#define PA2_AFS_9         AFS9
#define PA2_AFS_10        AFS10
#define PA2_AFS_11        AFS11

#define PA2_AFS_GPA2         PA2_AFS_0
#define PA2_AFS_SDT_I0       PA2_AFS_6
#define PA2_AFS_MA2          PA2_AFS_8
#define PA2_AFS_MAD2         PA2_AFS_9
#define PA2_AFS_TM36_OC2     PA2_AFS_10
#define PA2_AFS_URT5_TX      PA2_AFS_11


#define PA3_AFS_0         AFS0
#define PA3_AFS_6         AFS6
#define PA3_AFS_8         AFS8
#define PA3_AFS_9         AFS9
#define PA3_AFS_10        AFS10
#define PA3_AFS_11        AFS11

#define PA3_AFS_GPA3       PA3_AFS_0
#define PA3_AFS_SDT_I1     PA3_AFS_6
#define PA3_AFS_MA3        PA3_AFS_8
#define PA3_AFS_MAD3       PA3_AFS_9
#define PA3_AFS_TM36_OC2N  PA3_AFS_10
#define PA3_AFS_URT5_RX    PA3_AFS_11


#define PA4_AFS_0         AFS0
#define PA4_AFS_8         AFS8
#define PA4_AFS_9         AFS9
#define PA4_AFS_10        AFS10
#define PA4_AFS_11        AFS11

#define PA4_AFS_GPA4        PA4_AFS_0
#define PA4_AFS_MA4         PA4_AFS_8
#define PA4_AFS_MAD4        PA4_AFS_9
#define PA4_AFS_TM20_OC00   PA4_AFS_10
#define PA4_AFS_URT0_TX     PA4_AFS_11


#define PA5_AFS_0         AFS0
#define PA5_AFS_8         AFS8
#define PA5_AFS_9         AFS9
#define PA5_AFS_10        AFS10
#define PA5_AFS_11        AFS11

#define PA5_AFS_GPA5        PA5_AFS_0
#define PA5_AFS_MA5         PA5_AFS_8
#define PA5_AFS_MAD5        PA5_AFS_9
#define PA5_AFS_TM20_OC10   PA5_AFS_10
#define PA5_AFS_URT0_RX     PA5_AFS_11


#define PA6_AFS_0         AFS0
#define PA6_AFS_7         AFS7
#define PA6_AFS_8         AFS8
#define PA6_AFS_9         AFS9
#define PA6_AFS_10        AFS10
#define PA6_AFS_11        AFS11

#define PA6_AFS_GPA6        PA6_AFS_0
#define PA6_AFS_SPI0_D3     PA6_AFS_7
#define PA6_AFS_MA6         PA6_AFS_8
#define PA6_AFS_MAD6        PA6_AFS_9
#define PA6_AFS_TM20_OC0H   PA6_AFS_10
#define PA6_AFS_URT0_CLK    PA6_AFS_11


#define PA7_AFS_0         AFS0
#define PA7_AFS_7         AFS7
#define PA7_AFS_8         AFS8
#define PA7_AFS_9         AFS9
#define PA7_AFS_10        AFS10
#define PA7_AFS_11        AFS11

#define PA7_AFS_GPA7         PA7_AFS_0
#define PA7_AFS_SPI0_D2      PA7_AFS_7
#define PA7_AFS_MA7          PA7_AFS_8
#define PA7_AFS_MAD7         PA7_AFS_9
#define PA7_AFS_TM20_OC1H    PA7_AFS_10
#define PA7_AFS_URT0_NSS     PA7_AFS_11


#define PA8_AFS_0         AFS0
#define PA8_AFS_1         AFS1
#define PA8_AFS_3         AFS3
#define PA8_AFS_4         AFS4
#define PA8_AFS_5         AFS5
#define PA8_AFS_6         AFS6
#define PA8_AFS_7         AFS7
#define PA8_AFS_8         AFS8
#define PA8_AFS_9         AFS9
#define PA8_AFS_10        AFS10
#define PA8_AFS_11        AFS11

#define PA8_AFS_GPA8         PA8_AFS_0
#define PA8_AFS_DMA_TRG0     PA8_AFS_1
#define PA8_AFS_I2C0_SCL     PA8_AFS_3
#define PA8_AFS_URT2_BRO     PA8_AFS_4
#define PA8_AFS_SDT_I0       PA8_AFS_5
#define PA8_AFS_TM20_IC0     PA8_AFS_6
#define PA8_AFS_SPI0_NSS     PA8_AFS_7
#define PA8_AFS_MA8          PA8_AFS_8
#define PA8_AFS_MAD0         PA8_AFS_9
#define PA8_AFS_TM36_OC0H    PA8_AFS_10
#define PA8_AFS_URT4_TX      PA8_AFS_11


#define PA9_AFS_0         AFS0
#define PA9_AFS_1         AFS1
#define PA9_AFS_3         AFS3
#define PA9_AFS_4         AFS4
#define PA9_AFS_6         AFS6
#define PA9_AFS_7         AFS7
#define PA9_AFS_8         AFS8
#define PA9_AFS_9         AFS9
#define PA9_AFS_10        AFS10
#define PA9_AFS_11        AFS11

#define PA9_AFS_GPA9          PA9_AFS_0
#define PA9_AFS_DMA_TRG1      PA9_AFS_1
#define PA9_AFS_I2C1_SCL      PA9_AFS_3
#define PA9_AFS_URT2_TMO      PA9_AFS_4
#define PA9_AFS_TM20_IC1      PA9_AFS_6
#define PA9_AFS_SPI0_MISO     PA9_AFS_7
#define PA9_AFS_MA9           PA9_AFS_8
#define PA9_AFS_MAD1          PA9_AFS_9
#define PA9_AFS_TM36_OC1H     PA9_AFS_10
#define PA9_AFS_URT5_TX       PA9_AFS_11


#define PA10_AFS_0         AFS0
#define PA10_AFS_1         AFS1
#define PA10_AFS_2         AFS2
#define PA10_AFS_3         AFS3
#define PA10_AFS_4         AFS4
#define PA10_AFS_5         AFS5
#define PA10_AFS_6         AFS6
#define PA10_AFS_7         AFS7
#define PA10_AFS_8         AFS8
#define PA10_AFS_9         AFS9
#define PA10_AFS_10        AFS10
#define PA10_AFS_11        AFS11

#define PA10_AFS_GPA10          PA10_AFS_0
#define PA10_AFS_TM36_BK0       PA10_AFS_1
#define PA10_AFS_SPI0_D2        PA10_AFS_2
#define PA10_AFS_I2C0_SDA       PA10_AFS_3
#define PA10_AFS_URT2_CTS       PA10_AFS_4
#define PA10_AFS_SDT_I1         PA10_AFS_5
#define PA10_AFS_TM26_IC0       PA10_AFS_6
#define PA10_AFS_SPI0_CLK       PA10_AFS_7
#define PA10_AFS_MA10           PA10_AFS_8
#define PA10_AFS_MAD2           PA10_AFS_9
#define PA10_AFS_TM36_OC2H      PA10_AFS_10
#define PA10_AFS_URT4_RX        PA10_AFS_11


#define PA11_AFS_0         AFS0
#define PA11_AFS_1         AFS1
#define PA11_AFS_2         AFS2
#define PA11_AFS_3         AFS3
#define PA11_AFS_4         AFS4
#define PA11_AFS_6         AFS6
#define PA11_AFS_7         AFS7
#define PA11_AFS_8         AFS8
#define PA11_AFS_9         AFS9
#define PA11_AFS_10        AFS10
#define PA11_AFS_11        AFS11

#define PA11_AFS_GPA11          PA11_AFS_0
#define PA11_AFS_DAC_TRG0       PA11_AFS_1
#define PA11_AFS_SPI0_D3        PA11_AFS_2
#define PA11_AFS_I2C1_SDA       PA11_AFS_3
#define PA11_AFS_URT2_RTS       PA11_AFS_4
#define PA11_AFS_TM26_IC1       PA11_AFS_6
#define PA11_AFS_SPI0_MOSI      PA11_AFS_7
#define PA11_AFS_MA11           PA11_AFS_8
#define PA11_AFS_MAD3           PA11_AFS_9
#define PA11_AFS_TM36_OC3H      PA11_AFS_10
#define PA11_AFS_URT5_RX        PA11_AFS_11


#define PA12_AFS_0         AFS0
#define PA12_AFS_2         AFS2
#define PA12_AFS_4         AFS4
#define PA12_AFS_5         AFS5
#define PA12_AFS_6         AFS6
#define PA12_AFS_7         AFS7
#define PA12_AFS_8         AFS8
#define PA12_AFS_9         AFS9
#define PA12_AFS_10        AFS10
#define PA12_AFS_11        AFS11

#define PA12_AFS_GPA12          PA12_AFS_0
#define PA12_AFS_USB_S0         PA12_AFS_2
#define PA12_AFS_URT1_BRO       PA12_AFS_4
#define PA12_AFS_TM10_ETR       PA12_AFS_5
#define PA12_AFS_TM36_IC0       PA12_AFS_6
#define PA12_AFS_SPI0_D5        PA12_AFS_7
#define PA12_AFS_MA12           PA12_AFS_8
#define PA12_AFS_MAD4           PA12_AFS_9
#define PA12_AFS_TM26_OC00      PA12_AFS_10
#define PA12_AFS_URT6_TX        PA12_AFS_11


#define PA13_AFS_0         AFS0
#define PA13_AFS_1         AFS1
#define PA13_AFS_2         AFS2
#define PA13_AFS_3         AFS3
#define PA13_AFS_4         AFS4
#define PA13_AFS_5         AFS5
#define PA13_AFS_6         AFS6
#define PA13_AFS_7         AFS7
#define PA13_AFS_8         AFS8
#define PA13_AFS_9         AFS9
#define PA13_AFS_10        AFS10
#define PA13_AFS_11        AFS11

#define PA13_AFS_GPA13           PA13_AFS_0
#define PA13_AFS_CPU_TXEV        PA13_AFS_1
#define PA13_AFS_USB_S1          PA13_AFS_2
#define PA13_AFS_URT0_BRO        PA13_AFS_3
#define PA13_AFS_URT1_TMO        PA13_AFS_4
#define PA13_AFS_TM10_TRGO       PA13_AFS_5
#define PA13_AFS_TM36_IC1        PA13_AFS_6
#define PA13_AFS_SPI0_D6         PA13_AFS_7
#define PA13_AFS_MA13            PA13_AFS_8
#define PA13_AFS_MAD5            PA13_AFS_9
#define PA13_AFS_TM26_OC10       PA13_AFS_10
#define PA13_AFS_URT6_RX         PA13_AFS_11


#define PA14_AFS_0         AFS0
#define PA14_AFS_1         AFS1
#define PA14_AFS_2         AFS2
#define PA14_AFS_3         AFS3
#define PA14_AFS_4         AFS4
#define PA14_AFS_5         AFS5
#define PA14_AFS_6         AFS6
#define PA14_AFS_7         AFS7
#define PA14_AFS_8         AFS8
#define PA14_AFS_9         AFS9
#define PA14_AFS_10        AFS10
#define PA14_AFS_11        AFS11

#define PA14_AFS_GPA14          PA14_AFS_0
#define PA14_AFS_CPU_RXEV       PA14_AFS_1
#define PA14_AFS_OBM_I0         PA14_AFS_2
#define PA14_AFS_URT0_TMO       PA14_AFS_3
#define PA14_AFS_URT1_CTS       PA14_AFS_4
#define PA14_AFS_TM16_ETR       PA14_AFS_5
#define PA14_AFS_TM36_IC2       PA14_AFS_6
#define PA14_AFS_SPI0_D7        PA14_AFS_7
#define PA14_AFS_MA14           PA14_AFS_8
#define PA14_AFS_MAD6           PA14_AFS_9
#define PA14_AFS_TM26_OC0H      PA14_AFS_10
#define PA14_AFS_URT7_TX        PA14_AFS_11


#define PA15_AFS_0         AFS0
#define PA15_AFS_1         AFS1
#define PA15_AFS_2         AFS2
#define PA15_AFS_3         AFS3
#define PA15_AFS_4         AFS4
#define PA15_AFS_5         AFS5
#define PA15_AFS_6         AFS6
#define PA15_AFS_7         AFS7
#define PA15_AFS_8         AFS8
#define PA15_AFS_9         AFS9
#define PA15_AFS_10        AFS10
#define PA15_AFS_11        AFS11

#define PA15_AFS_GPA15          PA15_AFS_0
#define PA15_AFS_CPU_NMI        PA15_AFS_1
#define PA15_AFS_OBM_I1         PA15_AFS_2
#define PA15_AFS_URT0_DE        PA15_AFS_3
#define PA15_AFS_URT1_RTS       PA15_AFS_4
#define PA15_AFS_TM16_TRGO      PA15_AFS_5
#define PA15_AFS_TM36_IC3       PA15_AFS_6
#define PA15_AFS_SPI0_D4        PA15_AFS_7
#define PA15_AFS_MA15           PA15_AFS_8
#define PA15_AFS_MAD7           PA15_AFS_9
#define PA15_AFS_TM26_OC1H      PA15_AFS_10
#define PA15_AFS_URT7_RX        PA15_AFS_11

/////============================================================================================

#define PB0_AFS_0         AFS0
#define PB0_AFS_1         AFS1
#define PB0_AFS_2         AFS2
#define PB0_AFS_3         AFS3
#define PB0_AFS_4         AFS4
#define PB0_AFS_5         AFS5
#define PB0_AFS_6         AFS6
#define PB0_AFS_7         AFS7
#define PB0_AFS_8         AFS8
#define PB0_AFS_9         AFS9
#define PB0_AFS_11        AFS11

#define PB0_AFS_GPB0              PB0_AFS_0
#define PB0_AFS_I2C1_SCL          PB0_AFS_1
#define PB0_AFS_SPI0_NSS          PB0_AFS_2
#define PB0_AFS_TM01_ETR          PB0_AFS_3
#define PB0_AFS_TM00_CKO          PB0_AFS_4
#define PB0_AFS_TM16_ETR          PB0_AFS_5
#define PB0_AFS_TM26_IC0          PB0_AFS_6
#define PB0_AFS_TM36_ETR          PB0_AFS_7
#define PB0_AFS_MA15              PB0_AFS_8
#define PB0_AFS_URT1_NSS          PB0_AFS_9
#define PB0_AFS_URT6_TX           PB0_AFS_11



#define PB1_AFS_0         AFS0
#define PB1_AFS_1         AFS1
#define PB1_AFS_2         AFS2
#define PB1_AFS_3         AFS3
#define PB1_AFS_4         AFS4
#define PB1_AFS_5         AFS5
#define PB1_AFS_6         AFS6
#define PB1_AFS_7         AFS7
#define PB1_AFS_9         AFS9
#define PB1_AFS_11        AFS11

#define PB1_AFS_GPB1             PB1_AFS_0
#define PB1_AFS_I2C1_SDA         PB1_AFS_1
#define PB1_AFS_SPI0_MISO        PB1_AFS_2
#define PB1_AFS_TM01_TRGO        PB1_AFS_3
#define PB1_AFS_TM10_CKO         PB1_AFS_4
#define PB1_AFS_TM16_TRGO        PB1_AFS_5
#define PB1_AFS_TM26_IC1         PB1_AFS_6
#define PB1_AFS_TM36_TRGO        PB1_AFS_7
#define PB1_AFS_URT1_RX          PB1_AFS_9
#define PB1_AFS_URT6_RX          PB1_AFS_11



#define PB2_AFS_0         AFS0
#define PB2_AFS_1         AFS1
#define PB2_AFS_2         AFS2
#define PB2_AFS_3         AFS3
#define PB2_AFS_4         AFS4
#define PB2_AFS_5         AFS5
#define PB2_AFS_6         AFS6
#define PB2_AFS_7         AFS7
#define PB2_AFS_9         AFS9
#define PB2_AFS_10        AFS10
#define PB2_AFS_11        AFS11

#define PB2_AFS_GPB2             PB2_AFS_0
#define PB2_AFS_ADC0_TRG         PB2_AFS_1
#define PB2_AFS_SPI0_CLK         PB2_AFS_2
#define PB2_AFS_TM01_CKO         PB2_AFS_3
#define PB2_AFS_URT2_TX          PB2_AFS_4
#define PB2_AFS_TM16_CKO         PB2_AFS_5
#define PB2_AFS_TM26_OC0H        PB2_AFS_6
#define PB2_AFS_I2C0_SDA         PB2_AFS_7
#define PB2_AFS_URT1_CLK         PB2_AFS_9
#define PB2_AFS_URT0_TX          PB2_AFS_10
#define PB2_AFS_URT7_TX          PB2_AFS_11



#define PB3_AFS_0         AFS0
#define PB3_AFS_1         AFS1
#define PB3_AFS_2         AFS2
#define PB3_AFS_3         AFS3
#define PB3_AFS_4         AFS4
#define PB3_AFS_5         AFS5
#define PB3_AFS_6         AFS6
#define PB3_AFS_7         AFS7
#define PB3_AFS_9         AFS9
#define PB3_AFS_10        AFS10
#define PB3_AFS_11        AFS11

#define PB3_AFS_GPB3             PB3_AFS_0
#define PB3_AFS_ADC0_OUT         PB3_AFS_1
#define PB3_AFS_SPI0_MOSI        PB3_AFS_2
#define PB3_AFS_NCO_P0           PB3_AFS_3
#define PB3_AFS_URT2_RX          PB3_AFS_4
#define PB3_AFS_TM36_CKO         PB3_AFS_5
#define PB3_AFS_TM26_OC1H        PB3_AFS_6
#define PB3_AFS_I2C0_SCL         PB3_AFS_7 
#define PB3_AFS_URT1_TX          PB3_AFS_9
#define PB3_AFS_URT0_RX          PB3_AFS_10
#define PB3_AFS_URT7_RX          PB3_AFS_11



#define PB4_AFS_0         AFS0
#define PB4_AFS_1         AFS1
#define PB4_AFS_2         AFS2
#define PB4_AFS_3         AFS3
#define PB4_AFS_4         AFS4
#define PB4_AFS_5         AFS5
#define PB4_AFS_6         AFS6
#define PB4_AFS_8         AFS8
#define PB4_AFS_9         AFS9

#define PB4_AFS_GPB4             PB4_AFS_0
#define PB4_AFS_TM01_CKO         PB4_AFS_1
#define PB4_AFS_SPI0_D3          PB4_AFS_2
#define PB4_AFS_TM26_TRGO        PB4_AFS_3
#define PB4_AFS_URT2_CLK         PB4_AFS_4
#define PB4_AFS_TM20_IC0         PB4_AFS_5
#define PB4_AFS_TM36_IC0         PB4_AFS_6
#define PB4_AFS_MALE             PB4_AFS_8
#define PB4_AFS_MAD8             PB4_AFS_9



#define PB5_AFS_0         AFS0
#define PB5_AFS_1         AFS1
#define PB5_AFS_2         AFS2
#define PB5_AFS_3         AFS3
#define PB5_AFS_4         AFS4
#define PB5_AFS_5         AFS5
#define PB5_AFS_6         AFS6
#define PB5_AFS_8         AFS8
#define PB5_AFS_9         AFS9

#define PB5_AFS_GPB5             PB5_AFS_0
#define PB5_AFS_TM16_CKO         PB5_AFS_1
#define PB5_AFS_SPI0_D2          PB5_AFS_2
#define PB5_AFS_TM26_ETR         PB5_AFS_3
#define PB5_AFS_URT2_NSS         PB5_AFS_4
#define PB5_AFS_TM20_IC1         PB5_AFS_5
#define PB5_AFS_TM36_IC1         PB5_AFS_6
#define PB5_AFS_MOE              PB5_AFS_8
#define PB5_AFS_MAD9             PB5_AFS_9



#define PB6_AFS_0         AFS0
#define PB6_AFS_1         AFS1
#define PB6_AFS_2         AFS2
#define PB6_AFS_3         AFS3
#define PB6_AFS_4         AFS4
#define PB6_AFS_5         AFS5
#define PB6_AFS_6         AFS6
#define PB6_AFS_8         AFS8
#define PB6_AFS_9         AFS9
#define PB6_AFS_11        AFS11

#define PB6_AFS_GPB6              PB6_AFS_0
#define PB6_AFS_CPU_RXEV          PB6_AFS_1
#define PB6_AFS_SPI0_NSSI         PB6_AFS_2
#define PB6_AFS_URT0_BRO          PB6_AFS_3
#define PB6_AFS_URT2_CTS          PB6_AFS_4
#define PB6_AFS_TM20_ETR          PB6_AFS_5
#define PB6_AFS_TM36_IC2          PB6_AFS_6
#define PB6_AFS_MWE               PB6_AFS_8
#define PB6_AFS_MAD10             PB6_AFS_9
#define PB6_AFS_URT2_TX           PB6_AFS_11


#define PB7_AFS_0         AFS0
#define PB7_AFS_1         AFS1
#define PB7_AFS_3         AFS3
#define PB7_AFS_4         AFS4
#define PB7_AFS_5         AFS5
#define PB7_AFS_6         AFS6
#define PB7_AFS_8         AFS8
#define PB7_AFS_9         AFS9
#define PB7_AFS_11        AFS11

#define PB7_AFS_GPB7              PB7_AFS_0
#define PB7_AFS_CPU_TXEV          PB7_AFS_1
#define PB7_AFS_URT0_TMO          PB7_AFS_3
#define PB7_AFS_URT2_RTS          PB7_AFS_4
#define PB7_AFS_TM20_TRGO         PB7_AFS_5
#define PB7_AFS_TM36_IC3          PB7_AFS_6
#define PB7_AFS_MCE               PB7_AFS_8
#define PB7_AFS_MALE2             PB7_AFS_9
#define PB7_AFS_URT2_RX           PB7_AFS_11


#define PB8_AFS_0         AFS0
#define PB8_AFS_1         AFS1
#define PB8_AFS_2         AFS2
#define PB8_AFS_3         AFS3
#define PB8_AFS_4         AFS4
#define PB8_AFS_5         AFS5
#define PB8_AFS_6         AFS6
#define PB8_AFS_7         AFS7
#define PB8_AFS_8         AFS8
#define PB8_AFS_9         AFS9
#define PB8_AFS_10        AFS10
#define PB8_AFS_11        AFS11

#define PB8_AFS_GPB8               PB8_AFS_0
#define PB8_AFS_CMP0_P0            PB8_AFS_1
#define PB8_AFS_RTC_OUT            PB8_AFS_2
#define PB8_AFS_URT0_TX            PB8_AFS_3
#define PB8_AFS_URT2_BRO           PB8_AFS_4
#define PB8_AFS_TM20_OC01          PB8_AFS_5
#define PB8_AFS_TM36_OC01          PB8_AFS_6
#define PB8_AFS_SPI0_D3            PB8_AFS_7
#define PB8_AFS_MAD0               PB8_AFS_8
#define PB8_AFS_SDT_P0             PB8_AFS_9
#define PB8_AFS_OBM_P0             PB8_AFS_10
#define PB8_AFS_URT4_TX            PB8_AFS_11


#define PB9_AFS_0         AFS0
#define PB9_AFS_1         AFS1
#define PB9_AFS_2         AFS2
#define PB9_AFS_3         AFS3
#define PB9_AFS_4         AFS4
#define PB9_AFS_5         AFS5
#define PB9_AFS_6         AFS6
#define PB9_AFS_7         AFS7
#define PB9_AFS_8         AFS8
#define PB9_AFS_9         AFS9
#define PB9_AFS_10        AFS10
#define PB9_AFS_11        AFS11

#define PB9_AFS_GPB9               PB9_AFS_0
#define PB9_AFS_CMP1_P0            PB9_AFS_1
#define PB9_AFS_RTC_TS             PB9_AFS_2
#define PB9_AFS_URT0_RX            PB9_AFS_3
#define PB9_AFS_URT2_TMO           PB9_AFS_4
#define PB9_AFS_TM20_OC02          PB9_AFS_5
#define PB9_AFS_TM36_OC02          PB9_AFS_6
#define PB9_AFS_SPI0_D2            PB9_AFS_7
#define PB9_AFS_MAD1               PB9_AFS_8
#define PB9_AFS_MAD8               PB9_AFS_9
#define PB9_AFS_OBM_P1             PB9_AFS_10
#define PB9_AFS_URT4_RX            PB9_AFS_11


#define PB10_AFS_0         AFS0
#define PB10_AFS_2         AFS2
#define PB10_AFS_3         AFS3
#define PB10_AFS_4         AFS4
#define PB10_AFS_5         AFS5
#define PB10_AFS_6         AFS6
#define PB10_AFS_7         AFS7
#define PB10_AFS_8         AFS8
#define PB10_AFS_9         AFS9
#define PB10_AFS_10        AFS10

#define PB10_AFS_GPB10               PB10_AFS_0
#define PB10_AFS_I2C0_SCL            PB10_AFS_2
#define PB10_AFS_URT0_NSS            PB10_AFS_3
#define PB10_AFS_URT2_DE             PB10_AFS_4
#define PB10_AFS_TM20_OC11           PB10_AFS_5
#define PB10_AFS_TM36_OC11           PB10_AFS_6
#define PB10_AFS_URT1_TX             PB10_AFS_7
#define PB10_AFS_MAD2                PB10_AFS_8
#define PB10_AFS_MAD1                PB10_AFS_9
#define PB10_AFS_SPI0_NSSI           PB10_AFS_10


#define PB11_AFS_0         AFS0
#define PB11_AFS_2         AFS2
#define PB11_AFS_3         AFS3
#define PB11_AFS_4         AFS4
#define PB11_AFS_5         AFS5
#define PB11_AFS_6         AFS6
#define PB11_AFS_7         AFS7
#define PB11_AFS_8         AFS8
#define PB11_AFS_9         AFS9
#define PB11_AFS_10        AFS10
#define PB11_AFS_11        AFS11

#define PB11_AFS_GPB11               PB11_AFS_0
#define PB11_AFS_I2C0_SDA            PB11_AFS_2
#define PB11_AFS_URT0_DE             PB11_AFS_3
#define PB11_AFS_IR_OUT              PB11_AFS_4
#define PB11_AFS_TM20_OC12           PB11_AFS_5
#define PB11_AFS_TM36_OC12           PB11_AFS_6
#define PB11_AFS_URT1_RX             PB11_AFS_7
#define PB11_AFS_MAD3                PB11_AFS_8
#define PB11_AFS_MAD9                PB11_AFS_9
#define PB11_AFS_DMA_TRG0            PB11_AFS_10
#define PB11_AFS_URT0_CLK            PB11_AFS_11


#define PB12_AFS_0         AFS0
#define PB12_AFS_1         AFS1
#define PB12_AFS_2         AFS2
#define PB12_AFS_3         AFS3
#define PB12_AFS_7         AFS7
#define PB12_AFS_8         AFS8
#define PB12_AFS_9         AFS9
#define PB12_AFS_11        AFS11

#define PB12_AFS_GPB12               PB12_AFS_0
#define PB12_AFS_DMA_TRG0            PB12_AFS_1
#define PB12_AFS_NCO_P0              PB12_AFS_2
#define PB12_AFS_USB_S0              PB12_AFS_3
#define PB12_AFS_URT1_CLK            PB12_AFS_7
#define PB12_AFS_MAD4                PB12_AFS_8
#define PB12_AFS_MAD2                PB12_AFS_9
#define PB12_AFS_URT5_TX             PB12_AFS_11



#define PB13_AFS_0         AFS0
#define PB13_AFS_1         AFS1
#define PB13_AFS_2         AFS2
#define PB13_AFS_3         AFS3
#define PB13_AFS_5         AFS5
#define PB13_AFS_6         AFS6
#define PB13_AFS_7         AFS7
#define PB13_AFS_8         AFS8
#define PB13_AFS_9         AFS9
#define PB13_AFS_10        AFS10
#define PB13_AFS_11        AFS11

#define PB13_AFS_GPB13               PB13_AFS_0
#define PB13_AFS_DAC_TRG0            PB13_AFS_1
#define PB13_AFS_TM00_ETR            PB13_AFS_2
#define PB13_AFS_URT0_CTS            PB13_AFS_3
#define PB13_AFS_TM20_ETR            PB13_AFS_5
#define PB13_AFS_TM36_ETR            PB13_AFS_6
#define PB13_AFS_URT0_CLK            PB13_AFS_7
#define PB13_AFS_MAD5                PB13_AFS_8
#define PB13_AFS_MAD10               PB13_AFS_9
#define PB13_AFS_CCL_P0              PB13_AFS_10
#define PB13_AFS_URT4_RX              PB13_AFS_11


#define PB14_AFS_0         AFS0
#define PB14_AFS_1         AFS1
#define PB14_AFS_2         AFS2
#define PB14_AFS_3         AFS3
#define PB14_AFS_5         AFS5
#define PB14_AFS_6         AFS6
#define PB14_AFS_7         AFS7
#define PB14_AFS_8         AFS8
#define PB14_AFS_9         AFS9
#define PB14_AFS_10        AFS10
#define PB14_AFS_11        AFS11

#define PB14_AFS_GPB14               PB14_AFS_0
#define PB14_AFS_DMA_TRG0            PB14_AFS_1
#define PB14_AFS_TM00_TRGO           PB14_AFS_2
#define PB14_AFS_URT0_RTS            PB14_AFS_3
#define PB14_AFS_TM20_TRGO           PB14_AFS_5
#define PB14_AFS_TM36_BK0            PB14_AFS_6
#define PB14_AFS_URT0_NSS            PB14_AFS_7
#define PB14_AFS_MAD6                PB14_AFS_8
#define PB14_AFS_MAD3                PB14_AFS_9
#define PB14_AFS_CCL_P1              PB14_AFS_10
#define PB14_AFS_URT4_TX             PB14_AFS_11


#define PB15_AFS_0         AFS0
#define PB15_AFS_1         AFS1
#define PB15_AFS_2         AFS2
#define PB15_AFS_3         AFS3
#define PB15_AFS_7         AFS7
#define PB15_AFS_8         AFS8
#define PB15_AFS_9         AFS9
#define PB15_AFS_11        AFS11

#define PB15_AFS_GPB15               PB15_AFS_0
#define PB15_AFS_IR_OUT              PB15_AFS_1
#define PB15_AFS_NCO_CK0             PB15_AFS_2
#define PB15_AFS_USB_S1              PB15_AFS_3
#define PB15_AFS_URT1_NSS            PB15_AFS_7
#define PB15_AFS_MAD7                PB15_AFS_8
#define PB15_AFS_MAD11               PB15_AFS_9
#define PB15_AFS_URT5_RX             PB15_AFS_11


/////============================================================================================
#define PC0_AFS_0         AFS0
#define PC0_AFS_1         AFS1
#define PC0_AFS_2         AFS2
#define PC0_AFS_3         AFS3
#define PC0_AFS_4         AFS4
#define PC0_AFS_5         AFS5
#define PC0_AFS_6         AFS6
#define PC0_AFS_7         AFS7
#define PC0_AFS_8         AFS8
#define PC0_AFS_9         AFS9
#define PC0_AFS_10        AFS10
#define PC0_AFS_11        AFS11

#define PC0_AFS_GPC0               PC0_AFS_0
#define PC0_AFS_ICKO               PC0_AFS_1
#define PC0_AFS_TM00_CKO           PC0_AFS_2
#define PC0_AFS_URT0_CLK           PC0_AFS_3
#define PC0_AFS_URT2_CLK           PC0_AFS_4
#define PC0_AFS_TM20_OC00          PC0_AFS_5
#define PC0_AFS_TM36_OC00          PC0_AFS_6
#define PC0_AFS_I2C0_SCL           PC0_AFS_7
#define PC0_AFS_MCLK               PC0_AFS_8
#define PC0_AFS_MWE                PC0_AFS_9
#define PC0_AFS_URT0_TX            PC0_AFS_10
#define PC0_AFS_URT5_TX            PC0_AFS_11


#define PC1_AFS_0         AFS0
#define PC1_AFS_1         AFS1
#define PC1_AFS_2         AFS2
#define PC1_AFS_3         AFS3
#define PC1_AFS_4         AFS4
#define PC1_AFS_5         AFS5
#define PC1_AFS_6         AFS6
#define PC1_AFS_7         AFS7
#define PC1_AFS_8         AFS8
#define PC1_AFS_9         AFS9
#define PC1_AFS_10        AFS10
#define PC1_AFS_11        AFS11

#define PC1_AFS_GPC1               PC1_AFS_0
#define PC1_AFS_ADC0_TRG           PC1_AFS_1
#define PC1_AFS_TM01_CKO           PC1_AFS_2
#define PC1_AFS_TM36_IC0           PC1_AFS_3
#define PC1_AFS_URT1_CLK           PC1_AFS_4
#define PC1_AFS_TM20_OC0N          PC1_AFS_5
#define PC1_AFS_TM36_OC0N          PC1_AFS_6
#define PC1_AFS_I2C0_SDA           PC1_AFS_7
#define PC1_AFS_MAD8               PC1_AFS_8
#define PC1_AFS_MAD4               PC1_AFS_9
#define PC1_AFS_URT0_RX            PC1_AFS_10
#define PC1_AFS_URT5_RX            PC1_AFS_11


#define PC2_AFS_0         AFS0
#define PC2_AFS_1         AFS1
#define PC2_AFS_2         AFS2
#define PC2_AFS_3         AFS3
#define PC2_AFS_4         AFS4
#define PC2_AFS_5         AFS5
#define PC2_AFS_6         AFS6
#define PC2_AFS_7         AFS7
#define PC2_AFS_8         AFS8
#define PC2_AFS_9         AFS9

#define PC2_AFS_GPC2               PC2_AFS_0
#define PC2_AFS_ADC0_OUT           PC2_AFS_1
#define PC2_AFS_TM10_CKO           PC2_AFS_2
#define PC2_AFS_OBM_P0             PC2_AFS_3
#define PC2_AFS_URT2_CLK           PC2_AFS_4
#define PC2_AFS_TM20_OC10          PC2_AFS_5
#define PC2_AFS_TM36_OC10          PC2_AFS_6
#define PC2_AFS_SDT_I0             PC2_AFS_7
#define PC2_AFS_MAD9               PC2_AFS_8
#define PC2_AFS_MAD12              PC2_AFS_9


#define PC3_AFS_0         AFS0
#define PC3_AFS_1         AFS1
#define PC3_AFS_2         AFS2
#define PC3_AFS_3         AFS3
#define PC3_AFS_4         AFS4
#define PC3_AFS_5         AFS5
#define PC3_AFS_6         AFS6
#define PC3_AFS_7         AFS7
#define PC3_AFS_8         AFS8
#define PC3_AFS_9         AFS9

#define PC3_AFS_GPC3               PC3_AFS_0
#define PC3_AFS_OBM_P1             PC3_AFS_1
#define PC3_AFS_TM16_CKO           PC3_AFS_2
#define PC3_AFS_URT0_CLK           PC3_AFS_3
#define PC3_AFS_URT1_CLK           PC3_AFS_4
#define PC3_AFS_TM20_OC1N          PC3_AFS_5
#define PC3_AFS_TM36_OC1N          PC3_AFS_6
#define PC3_AFS_SDT_I1             PC3_AFS_7
#define PC3_AFS_MAD10              PC3_AFS_8
#define PC3_AFS_MAD5               PC3_AFS_9


#define PC4_AFS_0         AFS0
#define PC4_AFS_1         AFS1
#define PC4_AFS_2         AFS2
#define PC4_AFS_3         AFS3
#define PC4_AFS_4         AFS4
#define PC4_AFS_6         AFS6
#define PC4_AFS_7         AFS7
#define PC4_AFS_11        AFS11

#define PC4_AFS_GPC4               PC4_AFS_0
#define PC4_AFS_SWCLK              PC4_AFS_1
#define PC4_AFS_I2C0_SCL           PC4_AFS_2
#define PC4_AFS_URT0_RX            PC4_AFS_3
#define PC4_AFS_URT1_RX            PC4_AFS_4
#define PC4_AFS_TM36_OC2           PC4_AFS_6
#define PC4_AFS_SDT_I0             PC4_AFS_7
#define PC4_AFS_URT6_RX            PC4_AFS_11


#define PC5_AFS_0         AFS0
#define PC5_AFS_1         AFS1
#define PC5_AFS_2         AFS2
#define PC5_AFS_3         AFS3
#define PC5_AFS_4         AFS4
#define PC5_AFS_6         AFS6
#define PC5_AFS_7         AFS7
#define PC5_AFS_11        AFS11

#define PC5_AFS_GPC5               PC5_AFS_0
#define PC5_AFS_SWDIO              PC5_AFS_1
#define PC5_AFS_I2C0_SDA           PC5_AFS_2
#define PC5_AFS_URT0_TX            PC5_AFS_3
#define PC5_AFS_URT1_TX            PC5_AFS_4
#define PC5_AFS_TM36_OC3           PC5_AFS_6
#define PC5_AFS_SDT_I1             PC5_AFS_7
#define PC5_AFS_URT6_TX            PC5_AFS_11



#define PC6_AFS_0         AFS0
#define PC6_AFS_1         AFS1
#define PC6_AFS_2         AFS2
#define PC6_AFS_3         AFS3
#define PC6_AFS_4         AFS4
#define PC6_AFS_5         AFS6
#define PC6_AFS_6         AFS7
#define PC6_AFS_8         AFS8
#define PC6_AFS_9         AFS9

#define PC6_AFS_GPC6               PC6_AFS_0
#define PC6_AFS_RSTN               PC6_AFS_1
#define PC6_AFS_RTC_TS             PC6_AFS_2
#define PC6_AFS_URT0_NSS           PC6_AFS_3
#define PC6_AFS_URT1_NSS           PC6_AFS_4
#define PC6_AFS_TM20_ETR           PC6_AFS_5
#define PC6_AFS_TM26_ETR           PC6_AFS_6
#define PC6_AFS_MBW1               PC6_AFS_8
#define PC6_AFS_MALE               PC6_AFS_9


#define PC7_AFS_0         AFS0
#define PC7_AFS_1         AFS1
#define PC7_AFS_2         AFS2
#define PC7_AFS_3         AFS3
#define PC7_AFS_4         AFS4
#define PC7_AFS_6         AFS7
#define PC7_AFS_8         AFS8
#define PC7_AFS_9         AFS9

#define PC7_AFS_GPC7               PC7_AFS_0
#define PC7_AFS_ADC0_TRG           PC7_AFS_1
#define PC7_AFS_RTC_OUT            PC7_AFS_2
#define PC7_AFS_URT0_DE            PC7_AFS_3
#define PC7_AFS_URT1_NSS           PC7_AFS_4
#define PC7_AFS_TM36_TRGO          PC7_AFS_6
#define PC7_AFS_MBW0               PC7_AFS_8
#define PC7_AFS_MCE                PC7_AFS_9


#define PC8_AFS_0         AFS0
#define PC8_AFS_1         AFS1
#define PC8_AFS_2         AFS2
#define PC8_AFS_3         AFS3
#define PC8_AFS_4         AFS4
#define PC8_AFS_5         AFS5
#define PC8_AFS_6         AFS6
#define PC8_AFS_7         AFS7
#define PC8_AFS_8         AFS8
#define PC8_AFS_9         AFS9
#define PC8_AFS_10        AFS10
#define PC8_AFS_11        AFS11

#define PC8_AFS_GPC8               PC8_AFS_0
#define PC8_AFS_ADC0_OUT           PC8_AFS_1
#define PC8_AFS_I2C0_SCL           PC8_AFS_2
#define PC8_AFS_URT0_BRO           PC8_AFS_3
#define PC8_AFS_URT1_TX            PC8_AFS_4
#define PC8_AFS_TM20_OC0H          PC8_AFS_5
#define PC8_AFS_TM36_OC0H          PC8_AFS_6
#define PC8_AFS_TM36_OC0N          PC8_AFS_7
#define PC8_AFS_MAD11              PC8_AFS_8
#define PC8_AFS_MAD13              PC8_AFS_9
#define PC8_AFS_CCL_P0             PC8_AFS_10
#define PC8_AFS_URT6_TX            PC8_AFS_11


#define PC9_AFS_0         AFS0
#define PC9_AFS_1         AFS1
#define PC9_AFS_2         AFS2
#define PC9_AFS_3         AFS3
#define PC9_AFS_4         AFS4
#define PC9_AFS_5         AFS5
#define PC9_AFS_6         AFS6
#define PC9_AFS_7         AFS7
#define PC9_AFS_8         AFS8
#define PC9_AFS_9         AFS9
#define PC9_AFS_10        AFS10
#define PC9_AFS_11        AFS11

#define PC9_AFS_GPC9               PC9_AFS_0 
#define PC9_AFS_CMP0_P0            PC9_AFS_1
#define PC9_AFS_I2C0_SDA           PC9_AFS_2
#define PC9_AFS_URT0_TMO           PC9_AFS_3
#define PC9_AFS_URT1_RX            PC9_AFS_4
#define PC9_AFS_TM20_OC1H          PC9_AFS_5
#define PC9_AFS_TM36_OC1H          PC9_AFS_6
#define PC9_AFS_TM36_OC1N          PC9_AFS_7
#define PC9_AFS_MAD12              PC9_AFS_8
#define PC9_AFS_MAD6               PC9_AFS_9
#define PC9_AFS_CCL_P1             PC9_AFS_10
#define PC9_AFS_URT6_RX            PC9_AFS_11


#define PC10_AFS_0         AFS0
#define PC10_AFS_1         AFS1
#define PC10_AFS_2         AFS2
#define PC10_AFS_3         AFS3
#define PC10_AFS_4         AFS4
#define PC10_AFS_5         AFS5
#define PC10_AFS_6         AFS6
#define PC10_AFS_7         AFS7
#define PC10_AFS_8         AFS8
#define PC10_AFS_9         AFS9
#define PC10_AFS_11        AFS11

#define PC10_AFS_GPC10               PC10_AFS_0
#define PC10_AFS_CMP1_P0             PC10_AFS_1
#define PC10_AFS_I2C1_SCL            PC10_AFS_2
#define PC10_AFS_URT0_TX             PC10_AFS_3
#define PC10_AFS_URT2_TX             PC10_AFS_4
#define PC10_AFS_URT1_TX             PC10_AFS_5
#define PC10_AFS_TM36_OC2H           PC10_AFS_6
#define PC10_AFS_TM36_OC2N           PC10_AFS_7
#define PC10_AFS_MAD13               PC10_AFS_8
#define PC10_AFS_MAD14               PC10_AFS_9
#define PC10_AFS_URT7_TX             PC10_AFS_11


#define PC11_AFS_0         AFS0
#define PC11_AFS_2         AFS2
#define PC11_AFS_3         AFS3
#define PC11_AFS_4         AFS4
#define PC11_AFS_5         AFS5
#define PC11_AFS_6         AFS6
#define PC11_AFS_7         AFS7
#define PC11_AFS_8         AFS8
#define PC11_AFS_9         AFS9
#define PC11_AFS_11        AFS11

#define PC11_AFS_GPC11               PC11_AFS_0
#define PC11_AFS_I2C1_SDA            PC11_AFS_2
#define PC11_AFS_URT0_RX             PC11_AFS_3
#define PC11_AFS_URT2_RX             PC11_AFS_4
#define PC11_AFS_URT1_RX             PC11_AFS_5
#define PC11_AFS_TM36_OC3H           PC11_AFS_6
#define PC11_AFS_TM26_OC01           PC11_AFS_7
#define PC11_AFS_MAD14               PC11_AFS_8
#define PC11_AFS_MAD7                PC11_AFS_9
#define PC11_AFS_URT7_RX             PC11_AFS_11


#define PC12_AFS_0         AFS0
#define PC12_AFS_2         AFS2
#define PC12_AFS_3         AFS3
#define PC12_AFS_4         AFS4
#define PC12_AFS_5         AFS5
#define PC12_AFS_6         AFS6
#define PC12_AFS_7         AFS7
#define PC12_AFS_8         AFS8
#define PC12_AFS_9         AFS9

#define PC12_AFS_GPC12               PC12_AFS_0
#define PC12_AFS_IR_OUT              PC12_AFS_2
#define PC12_AFS_DAC_TRG0            PC12_AFS_3
#define PC12_AFS_URT1_DE             PC12_AFS_4
#define PC12_AFS_TM10_TRGO           PC12_AFS_5
#define PC12_AFS_TM36_OC3            PC12_AFS_6
#define PC12_AFS_TM26_OC02           PC12_AFS_7
#define PC12_AFS_MAD15               PC12_AFS_8
#define PC12_AFS_SDT_P0              PC12_AFS_9



#define PC13_AFS_0         AFS0
#define PC13_AFS_1         AFS1
#define PC13_AFS_2         AFS2
#define PC13_AFS_3         AFS3
#define PC13_AFS_4         AFS4
#define PC13_AFS_5         AFS5
#define PC13_AFS_6         AFS6
#define PC13_AFS_7         AFS7
#define PC13_AFS_8         AFS8
#define PC13_AFS_9         AFS9
#define PC13_AFS_11        AFS11

#define PC13_AFS_GPC13               PC13_AFS_0
#define PC13_AFS_XIN                 PC13_AFS_1
#define PC13_AFS_URT1_NSS            PC13_AFS_2
#define PC13_AFS_URT0_CTS            PC13_AFS_3
#define PC13_AFS_URT2_RX             PC13_AFS_4
#define PC13_AFS_TM10_ETR            PC13_AFS_5
#define PC13_AFS_TM26_ETR            PC13_AFS_6
#define PC13_AFS_TM36_OC00           PC13_AFS_7
#define PC13_AFS_TM20_IC0            PC13_AFS_8
#define PC13_AFS_SDT_I0              PC13_AFS_9
#define PC13_AFS_URT6_RX             PC13_AFS_11


#define PC14_AFS_0         AFS0
#define PC14_AFS_1         AFS1
#define PC14_AFS_2         AFS2
#define PC14_AFS_3         AFS3
#define PC14_AFS_4         AFS4
#define PC14_AFS_5         AFS5
#define PC14_AFS_6         AFS6
#define PC14_AFS_7         AFS7
#define PC14_AFS_8         AFS8
#define PC14_AFS_9         AFS9
#define PC14_AFS_11        AFS11

#define PC14_AFS_GPC14               PC14_AFS_0
#define PC14_AFS_XOUT                PC14_AFS_1
#define PC14_AFS_URT1_TMO            PC14_AFS_2
#define PC14_AFS_URT0_RTS            PC14_AFS_3
#define PC14_AFS_URT2_TX             PC14_AFS_4
#define PC14_AFS_TM10_CKO            PC14_AFS_5
#define PC14_AFS_TM26_TRGO           PC14_AFS_6
#define PC14_AFS_TM36_OC10           PC14_AFS_7
#define PC14_AFS_TM20_IC1            PC14_AFS_8
#define PC14_AFS_SDT_I1              PC14_AFS_9
#define PC14_AFS_URT6_TX             PC14_AFS_11


/////============================================================================================

#define PD0_AFS_0         AFS0
#define PD0_AFS_1         AFS1
#define PD0_AFS_2         AFS2
#define PD0_AFS_3         AFS3
#define PD0_AFS_4         AFS4
#define PD0_AFS_5         AFS5
#define PD0_AFS_6         AFS6
#define PD0_AFS_7         AFS7
#define PD0_AFS_8         AFS8
#define PD0_AFS_9         AFS9
#define PD0_AFS_11        AFS11

#define PD0_AFS_GPD0               PD0_AFS_0
#define PD0_AFS_OBM_I0             PD0_AFS_1
#define PD0_AFS_TM10_CKO           PD0_AFS_2
#define PD0_AFS_URT0_CLK           PD0_AFS_3
#define PD0_AFS_TM26_OC1N          PD0_AFS_4
#define PD0_AFS_TM20_CKO           PD0_AFS_5
#define PD0_AFS_TM36_OC2           PD0_AFS_6
#define PD0_AFS_SPI0_NSS           PD0_AFS_7
#define PD0_AFS_MA0                PD0_AFS_8
#define PD0_AFS_MCLK               PD0_AFS_9
#define PD0_AFS_URT2_NSS           PD0_AFS_11



#define PD1_AFS_0         AFS0
#define PD1_AFS_1         AFS1
#define PD1_AFS_2         AFS2
#define PD1_AFS_3         AFS3
#define PD1_AFS_4         AFS4
#define PD1_AFS_5         AFS5
#define PD1_AFS_6         AFS6
#define PD1_AFS_7         AFS7
#define PD1_AFS_8         AFS8
#define PD1_AFS_11        AFS11

#define PD1_AFS_GPD1               PD1_AFS_0
#define PD1_AFS_OBM_I1             PD1_AFS_1
#define PD1_AFS_TM16_CKO           PD1_AFS_2
#define PD1_AFS_URT0_CLK           PD1_AFS_3
#define PD1_AFS_NCO_CK0            PD1_AFS_4
#define PD1_AFS_TM26_CKO           PD1_AFS_5
#define PD1_AFS_TM36_OC2N          PD1_AFS_6
#define PD1_AFS_SPI0_CLK           PD1_AFS_7
#define PD1_AFS_MA1                PD1_AFS_8
#define PD1_AFS_URT2_CLK           PD1_AFS_11


#define PD2_AFS_0         AFS0
#define PD2_AFS_1         AFS1
#define PD2_AFS_2         AFS2
#define PD2_AFS_3         AFS3
#define PD2_AFS_4         AFS4
#define PD2_AFS_5         AFS5
#define PD2_AFS_6         AFS6
#define PD2_AFS_7         AFS7
#define PD2_AFS_8         AFS8
#define PD2_AFS_9         AFS9
#define PD2_AFS_11        AFS11

#define PD2_AFS_GPD2               PD2_AFS_0
#define PD2_AFS_USB_S0             PD2_AFS_1
#define PD2_AFS_TM00_CKO           PD2_AFS_2
#define PD2_AFS_URT1_CLK           PD2_AFS_3
#define PD2_AFS_TM26_OC00          PD2_AFS_4 
#define PD2_AFS_TM20_CKO           PD2_AFS_5
#define PD2_AFS_TM36_CKO           PD2_AFS_6
#define PD2_AFS_SPI0_MOSI          PD2_AFS_7
#define PD2_AFS_MA2                PD2_AFS_8
#define PD2_AFS_MAD4               PD2_AFS_9
#define PD2_AFS_URT2_TX            PD2_AFS_11



#define PD3_AFS_0         AFS0
#define PD3_AFS_1         AFS1
#define PD3_AFS_2         AFS2
#define PD3_AFS_3         AFS3
#define PD3_AFS_5         AFS5
#define PD3_AFS_6         AFS6
#define PD3_AFS_7         AFS7
#define PD3_AFS_8         AFS8
#define PD3_AFS_9         AFS9
#define PD3_AFS_10        AFS10
#define PD3_AFS_11        AFS11

#define PD3_AFS_GPD3               PD3_AFS_0
#define PD3_AFS_USB_S1             PD3_AFS_1
#define PD3_AFS_TM01_CKO           PD3_AFS_2
#define PD3_AFS_URT1_CLK           PD3_AFS_3
#define PD3_AFS_SPI0_MISO          PD3_AFS_5
#define PD3_AFS_TM26_CKO           PD3_AFS_6
#define PD3_AFS_SPI0_D3            PD3_AFS_7
#define PD3_AFS_MA3                PD3_AFS_8
#define PD3_AFS_MAD7               PD3_AFS_9
#define PD3_AFS_TM36_TRGO          PD3_AFS_10
#define PD3_AFS_URT2_RX            PD3_AFS_11



#define PD7_AFS_0         AFS0
#define PD7_AFS_1         AFS1
#define PD7_AFS_2         AFS2
#define PD7_AFS_3         AFS3
#define PD7_AFS_5         AFS5
#define PD7_AFS_6         AFS6
#define PD7_AFS_7         AFS7
#define PD7_AFS_8         AFS8
#define PD7_AFS_9         AFS9
#define PD7_AFS_10        AFS10

#define PD7_AFS_GPD7               PD7_AFS_0
#define PD7_AFS_TM00_CKO           PD7_AFS_1
#define PD7_AFS_TM01_ETR           PD7_AFS_2
#define PD7_AFS_URT1_DE            PD7_AFS_3
#define PD7_AFS_SPI0_MISO          PD7_AFS_5
#define PD7_AFS_TM26_OC0N          PD7_AFS_6
#define PD7_AFS_SPI0_D4            PD7_AFS_7
#define PD7_AFS_MA7                PD7_AFS_8
#define PD7_AFS_MAD0               PD7_AFS_9
#define PD7_AFS_TM36_IC0           PD7_AFS_10


#define PD8_AFS_0         AFS0
#define PD8_AFS_1         AFS1
#define PD8_AFS_2         AFS2
#define PD8_AFS_3         AFS3
#define PD8_AFS_5         AFS5
#define PD8_AFS_6         AFS6
#define PD8_AFS_7         AFS7
#define PD8_AFS_8         AFS8
#define PD8_AFS_9         AFS9
#define PD8_AFS_10        AFS10
#define PD8_AFS_11        AFS11

#define PD8_AFS_GPD8               PD8_AFS_0
#define PD8_AFS_CPU_TXEV           PD8_AFS_1
#define PD8_AFS_TM01_TRGO          PD8_AFS_2
#define PD8_AFS_URT1_RTS           PD8_AFS_3
#define PD8_AFS_SPI0_D2            PD8_AFS_5
#define PD8_AFS_TM26_OC10          PD8_AFS_6
#define PD8_AFS_SPI0_D7            PD8_AFS_7
#define PD8_AFS_MA8                PD8_AFS_8
#define PD8_AFS_MAD3               PD8_AFS_9
#define PD8_AFS_TM36_IC1           PD8_AFS_10
#define PD8_AFS_SPI0_CLK           PD8_AFS_11


#define PD9_AFS_0         AFS0
#define PD9_AFS_1         AFS1
#define PD9_AFS_2         AFS2
#define PD9_AFS_3         AFS3
#define PD9_AFS_5         AFS5
#define PD9_AFS_6         AFS6
#define PD9_AFS_7         AFS7
#define PD9_AFS_8         AFS8
#define PD9_AFS_9         AFS9
#define PD9_AFS_10        AFS10
#define PD9_AFS_11        AFS11

#define PD9_AFS_GPD9               PD9_AFS_0
#define PD9_AFS_CPU_RXEV           PD9_AFS_1
#define PD9_AFS_TM00_TRGO          PD9_AFS_2
#define PD9_AFS_URT1_CTS           PD9_AFS_3
#define PD9_AFS_SPI0_NSSI          PD9_AFS_5
#define PD9_AFS_TM26_OC11          PD9_AFS_6
#define PD9_AFS_SPI0_D6            PD9_AFS_7
#define PD9_AFS_MA9                PD9_AFS_8
#define PD9_AFS_MAD2               PD9_AFS_9
#define PD9_AFS_TM36_IC2           PD9_AFS_10
#define PD9_AFS_SPI0_NSS           PD9_AFS_11



#define PD10_AFS_0         AFS0
#define PD10_AFS_1         AFS1
#define PD10_AFS_2         AFS2
#define PD10_AFS_3         AFS3
#define PD10_AFS_5         AFS5
#define PD10_AFS_6         AFS6
#define PD10_AFS_7         AFS7
#define PD10_AFS_8         AFS8
#define PD10_AFS_9         AFS9
#define PD10_AFS_10        AFS10
#define PD10_AFS_11        AFS11

#define PD10_AFS_GPD10               PD10_AFS_0
#define PD10_AFS_CPU_NMI             PD10_AFS_1
#define PD10_AFS_TM00_ETR            PD10_AFS_2
#define PD10_AFS_URT1_BRO            PD10_AFS_3
#define PD10_AFS_RTC_OUT             PD10_AFS_5
#define PD10_AFS_TM26_OC12           PD10_AFS_6
#define PD10_AFS_SPI0_D5             PD10_AFS_7
#define PD10_AFS_MA10                PD10_AFS_8
#define PD10_AFS_MAD1                PD10_AFS_9
#define PD10_AFS_TM36_IC3            PD10_AFS_10
#define PD10_AFS_SPI0_MOSI           PD10_AFS_11



#define PD11_AFS_0         AFS0
#define PD11_AFS_1         AFS1
#define PD11_AFS_2         AFS2
#define PD11_AFS_3         AFS3
#define PD11_AFS_5         AFS5
#define PD11_AFS_6         AFS6
#define PD11_AFS_7         AFS7
#define PD11_AFS_8         AFS8
#define PD11_AFS_9         AFS9

#define PD11_AFS_GPD11               PD11_AFS_0
#define PD11_AFS_CPU_NMI             PD11_AFS_1
#define PD11_AFS_DMA_TRG1            PD11_AFS_2
#define PD11_AFS_URT1_TMO            PD11_AFS_3
#define PD11_AFS_SPI0_D3             PD11_AFS_5
#define PD11_AFS_TM26_OC1N           PD11_AFS_6
#define PD11_AFS_SPI0_NSS            PD11_AFS_7
#define PD11_AFS_MA11                PD11_AFS_8
#define PD11_AFS_MWE                 PD11_AFS_9



#define PD12_AFS_0         AFS0
#define PD12_AFS_1         AFS1
#define PD12_AFS_2         AFS2
#define PD12_AFS_3         AFS3
#define PD12_AFS_4         AFS4
#define PD12_AFS_5         AFS5
#define PD12_AFS_6         AFS6
#define PD12_AFS_7         AFS7
#define PD12_AFS_8         AFS8
#define PD12_AFS_9         AFS9

#define PD12_AFS_GPD12               PD12_AFS_0
#define PD12_AFS_CMP0_P0             PD12_AFS_1
#define PD12_AFS_TM10_CKO            PD12_AFS_2
#define PD12_AFS_OBM_P0              PD12_AFS_3
#define PD12_AFS_TM00_CKO            PD12_AFS_4
#define PD12_AFS_SPI0_CLK            PD12_AFS_5
#define PD12_AFS_TM20_OC0H           PD12_AFS_6
#define PD12_AFS_TM26_OC0H           PD12_AFS_7
#define PD12_AFS_MA12                PD12_AFS_8
#define PD12_AFS_MALE2               PD12_AFS_9



#define PD13_AFS_0         AFS0
#define PD13_AFS_1         AFS1
#define PD13_AFS_2         AFS2
#define PD13_AFS_3         AFS3
#define PD13_AFS_4         AFS4
#define PD13_AFS_5         AFS5
#define PD13_AFS_6         AFS6
#define PD13_AFS_7         AFS7
#define PD13_AFS_8         AFS8
#define PD13_AFS_9         AFS9

#define PD13_AFS_GPD13               PD13_AFS_0
#define PD13_AFS_CMP1_P0             PD13_AFS_1
#define PD13_AFS_TM10_TRGO           PD13_AFS_2
#define PD13_AFS_OBM_P1              PD13_AFS_3
#define PD13_AFS_TM00_TRGO           PD13_AFS_4
#define PD13_AFS_NCO_CK0             PD13_AFS_5
#define PD13_AFS_TM20_OC1H           PD13_AFS_6
#define PD13_AFS_TM26_OC1H           PD13_AFS_7
#define PD13_AFS_MA13                PD13_AFS_8
#define PD13_AFS_MCE                 PD13_AFS_9


#define PD14_AFS_0         AFS0
#define PD14_AFS_2         AFS2
#define PD14_AFS_3         AFS3
#define PD14_AFS_4         AFS4
#define PD14_AFS_6         AFS6
#define PD14_AFS_7         AFS7
#define PD14_AFS_8         AFS8
#define PD14_AFS_9         AFS9
#define PD14_AFS_10        AFS10
#define PD14_AFS_11        AFS11

#define PD14_AFS_GPD14                  PD14_AFS_0
#define PD14_AFS_TM10_ETR               PD14_AFS_2
#define PD14_AFS_DAC_TRG0               PD14_AFS_3
#define PD14_AFS_TM00_ETR               PD14_AFS_4
#define PD14_AFS_TM20_IC0               PD14_AFS_6
#define PD14_AFS_TM26_IC0               PD14_AFS_7
#define PD14_AFS_MA14                   PD14_AFS_8
#define PD14_AFS_MOE                    PD14_AFS_9
#define PD14_AFS_CCL_P0                 PD14_AFS_10
#define PD14_AFS_URT5_TX                PD14_AFS_11


#define PD15_AFS_0         AFS0
#define PD15_AFS_2         AFS2
#define PD15_AFS_3         AFS3
#define PD15_AFS_4         AFS4
#define PD15_AFS_6         AFS6
#define PD15_AFS_7         AFS7
#define PD15_AFS_8         AFS8
#define PD15_AFS_10        AFS10
#define PD15_AFS_11        AFS11

#define PD15_AFS_GPD15               PD15_AFS_0
#define PD15_AFS_NCO_P0              PD15_AFS_2
#define PD15_AFS_IR_OUT              PD15_AFS_3
#define PD15_AFS_DMA_TRG0            PD15_AFS_4
#define PD15_AFS_TM20_IC1            PD15_AFS_6
#define PD15_AFS_TM26_IC1            PD15_AFS_7
#define PD15_AFS_MA15                PD15_AFS_8
#define PD15_AFS_CCL_P1              PD15_AFS_10
#define PD15_AFS_URT5_RX             PD15_AFS_11

/////============================================================================================

#define PE0_AFS_0         AFS0
#define PE0_AFS_1         AFS1
#define PE0_AFS_3         AFS3
#define PE0_AFS_4         AFS4
#define PE0_AFS_5         AFS5
#define PE0_AFS_6         AFS6
#define PE0_AFS_7         AFS7
#define PE0_AFS_8         AFS8
#define PE0_AFS_9         AFS9
#define PE0_AFS_11        AFS11

#define PE0_AFS_GPE0               PE0_AFS_0
#define PE0_AFS_OBM_I0             PE0_AFS_1
#define PE0_AFS_URT0_TX            PE0_AFS_3
#define PE0_AFS_DAC_TRG0           PE0_AFS_4
#define PE0_AFS_SPI0_NSS           PE0_AFS_5
#define PE0_AFS_TM20_OC00          PE0_AFS_6
#define PE0_AFS_TM26_OC00          PE0_AFS_7
#define PE0_AFS_MALE               PE0_AFS_8
#define PE0_AFS_MAD8               PE0_AFS_9
#define PE0_AFS_URT4_TX            PE0_AFS_11


#define PE1_AFS_0         AFS0
#define PE1_AFS_1         AFS1
#define PE1_AFS_3         AFS3
#define PE1_AFS_4         AFS4
#define PE1_AFS_5         AFS5
#define PE1_AFS_6         AFS6
#define PE1_AFS_7         AFS7
#define PE1_AFS_8         AFS8
#define PE1_AFS_9         AFS9
#define PE1_AFS_10        AFS10
#define PE1_AFS_11        AFS11

#define PE1_AFS_GPE1               PE1_AFS_0
#define PE1_AFS_OBM_I1             PE1_AFS_1
#define PE1_AFS_URT0_RX            PE1_AFS_3
#define PE1_AFS_DMA_TRG1           PE1_AFS_4
#define PE1_AFS_SPI0_MISO          PE1_AFS_5
#define PE1_AFS_TM20_OC01          PE1_AFS_6
#define PE1_AFS_TM26_OC01          PE1_AFS_7
#define PE1_AFS_MOE                PE1_AFS_8
#define PE1_AFS_MAD9               PE1_AFS_9
#define PE1_AFS_TM36_OC0H          PE1_AFS_10
#define PE1_AFS_URT4_RX            PE1_AFS_11



#define PE2_AFS_0         AFS0
#define PE2_AFS_1         AFS1
#define PE2_AFS_2         AFS2
#define PE2_AFS_3         AFS3
#define PE2_AFS_4         AFS4
#define PE2_AFS_5         AFS5
#define PE2_AFS_6         AFS6
#define PE2_AFS_7         AFS7
#define PE2_AFS_8         AFS8
#define PE2_AFS_9         AFS9
#define PE2_AFS_10        AFS10
#define PE2_AFS_11        AFS11

#define PE2_AFS_GPE2               PE2_AFS_0
#define PE2_AFS_OBM_P0             PE2_AFS_1
#define PE2_AFS_I2C1_SCL           PE2_AFS_2
#define PE2_AFS_URT1_TX            PE2_AFS_3
#define PE2_AFS_NCO_P0             PE2_AFS_4
#define PE2_AFS_SPI0_CLK           PE2_AFS_5
#define PE2_AFS_TM20_OC02          PE2_AFS_6
#define PE2_AFS_TM26_OC02          PE2_AFS_7
#define PE2_AFS_MWE                PE2_AFS_8
#define PE2_AFS_MAD10              PE2_AFS_9
#define PE2_AFS_TM36_OC1H          PE2_AFS_10
#define PE2_AFS_URT5_TX            PE2_AFS_11


#define PE3_AFS_0         AFS0
#define PE3_AFS_1         AFS1
#define PE3_AFS_2         AFS2
#define PE3_AFS_3         AFS3
#define PE3_AFS_4         AFS4
#define PE3_AFS_5         AFS5
#define PE3_AFS_6         AFS6
#define PE3_AFS_7         AFS7
#define PE3_AFS_8         AFS8
#define PE3_AFS_9         AFS9
#define PE3_AFS_11        AFS11

#define PE3_AFS_GPE3               PE3_AFS_0
#define PE3_AFS_OBM_P1             PE3_AFS_1
#define PE3_AFS_I2C1_SDA           PE3_AFS_2
#define PE3_AFS_URT1_RX            PE3_AFS_3
#define PE3_AFS_NCO_CK0            PE3_AFS_4
#define PE3_AFS_SPI0_MOSI          PE3_AFS_5
#define PE3_AFS_TM20_OC0N          PE3_AFS_6
#define PE3_AFS_TM26_OC0N          PE3_AFS_7
#define PE3_AFS_MCE                PE3_AFS_8
#define PE3_AFS_MALE2              PE3_AFS_9
#define PE3_AFS_URT5_RX            PE3_AFS_11


#define PE8_AFS_0         AFS0
#define PE8_AFS_1         AFS1
#define PE8_AFS_2         AFS2
#define PE8_AFS_3         AFS3
#define PE8_AFS_4         AFS4
#define PE8_AFS_5         AFS5
#define PE8_AFS_6         AFS6
#define PE8_AFS_7         AFS7
#define PE8_AFS_9         AFS9
#define PE8_AFS_11        AFS11

#define PE8_AFS_GPE8              PE8_AFS_0
#define PE8_AFS_CPU_TXEV          PE8_AFS_1
#define PE8_AFS_OBM_I0            PE8_AFS_2
#define PE8_AFS_URT2_TX           PE8_AFS_3
#define PE8_AFS_SDT_I0            PE8_AFS_4
#define PE8_AFS_TM36_CKO          PE8_AFS_5
#define PE8_AFS_TM20_CKO          PE8_AFS_6
#define PE8_AFS_TM26_CKO          PE8_AFS_7
#define PE8_AFS_MAD11             PE8_AFS_9
#define PE8_AFS_URT4_TX           PE8_AFS_11


#define PE9_AFS_0         AFS0
#define PE9_AFS_1         AFS1
#define PE9_AFS_2         AFS2
#define PE9_AFS_3         AFS3
#define PE9_AFS_4         AFS4
#define PE9_AFS_5         AFS5
#define PE9_AFS_6         AFS6
#define PE9_AFS_7         AFS7
#define PE9_AFS_9         AFS9
#define PE9_AFS_11        AFS11

#define PE9_AFS_GPE9              PE9_AFS_0
#define PE9_AFS_CPU_RXEV          PE9_AFS_1
#define PE9_AFS_OBM_I1            PE9_AFS_2
#define PE9_AFS_URT2_RX           PE9_AFS_3
#define PE9_AFS_SDT_I1            PE9_AFS_4
#define PE9_AFS_TM36_TRGO         PE9_AFS_5
#define PE9_AFS_TM20_TRGO         PE9_AFS_6
#define PE9_AFS_TM26_TRGO         PE9_AFS_7
#define PE9_AFS_MOE               PE9_AFS_9
#define PE9_AFS_URT4_RX           PE9_AFS_11


#define PE10_AFS_0         AFS0
#define PE10_AFS_1         AFS1
#define PE10_AFS_2         AFS2
#define PE10_AFS_3         AFS3
#define PE10_AFS_4         AFS4
#define PE10_AFS_9         AFS9

#define PE10_AFS_GPE10              PE10_AFS_0
#define PE10_AFS_I2C0_SCL           PE10_AFS_1
#define PE10_AFS_I2C1_SCL           PE10_AFS_2
#define PE10_AFS_URT0_TX            PE10_AFS_3
#define PE10_AFS_URT4_TX            PE10_AFS_4
#define PE10_AFS_SDT_I0             PE10_AFS_9


#define PE11_AFS_0         AFS0
#define PE11_AFS_1         AFS1
#define PE11_AFS_2         AFS2
#define PE11_AFS_3         AFS3
#define PE11_AFS_4         AFS4
#define PE11_AFS_9         AFS9

#define PE11_AFS_GPE11               PE11_AFS_0
#define PE11_AFS_I2C0_SDA            PE11_AFS_1
#define PE11_AFS_I2C1_SDA            PE11_AFS_2
#define PE11_AFS_URT0_RX             PE11_AFS_3
#define PE11_AFS_URT4_RX             PE11_AFS_4
#define PE11_AFS_SDT_I1              PE11_AFS_9


#define PE12_AFS_0         AFS0
#define PE12_AFS_1         AFS1
#define PE12_AFS_2         AFS2
#define PE12_AFS_4         AFS4
#define PE12_AFS_5         AFS5
#define PE12_AFS_6         AFS6
#define PE12_AFS_7         AFS7
#define PE12_AFS_8         AFS8
#define PE12_AFS_11        AFS11

#define PE12_AFS_GPE12               PE12_AFS_0
#define PE12_AFS_ADC0_TRG            PE12_AFS_1
#define PE12_AFS_USB_S0              PE12_AFS_2
#define PE12_AFS_TM01_CKO            PE12_AFS_4
#define PE12_AFS_TM16_CKO            PE12_AFS_5
#define PE12_AFS_TM20_OC10           PE12_AFS_6
#define PE12_AFS_TM26_OC10           PE12_AFS_7
#define PE12_AFS_MBW0                PE12_AFS_8
#define PE12_AFS_URT6_TX             PE12_AFS_11


#define PE13_AFS_0         AFS0
#define PE13_AFS_1         AFS1
#define PE13_AFS_2         AFS2
#define PE13_AFS_4         AFS4
#define PE13_AFS_5         AFS5
#define PE13_AFS_6         AFS6
#define PE13_AFS_7         AFS7
#define PE13_AFS_8         AFS8
#define PE13_AFS_10        AFS10
#define PE13_AFS_11        AFS11

#define PE13_AFS_GPE13               PE13_AFS_0
#define PE13_AFS_ADC0_OUT            PE13_AFS_1
#define PE13_AFS_USB_S1              PE13_AFS_2
#define PE13_AFS_TM01_TRGO           PE13_AFS_4
#define PE13_AFS_TM16_TRGO           PE13_AFS_5
#define PE13_AFS_TM20_OC11           PE13_AFS_6
#define PE13_AFS_TM26_OC11           PE13_AFS_7
#define PE13_AFS_MBW1                PE13_AFS_8
#define PE13_AFS_TM36_OC2H           PE13_AFS_10
#define PE13_AFS_URT6_RX             PE13_AFS_11


#define PE14_AFS_0         AFS0
#define PE14_AFS_1         AFS1
#define PE14_AFS_2         AFS2
#define PE14_AFS_4         AFS4
#define PE14_AFS_5         AFS5
#define PE14_AFS_6         AFS6
#define PE14_AFS_7         AFS7
#define PE14_AFS_8         AFS8
#define PE14_AFS_9         AFS9
#define PE14_AFS_10        AFS10
#define PE14_AFS_11        AFS11

#define PE14_AFS_GPE14               PE14_AFS_0
#define PE14_AFS_RTC_OUT             PE14_AFS_1
#define PE14_AFS_I2C1_SCL            PE14_AFS_2
#define PE14_AFS_TM01_ETR            PE14_AFS_4
#define PE14_AFS_TM16_ETR            PE14_AFS_5
#define PE14_AFS_TM20_OC12           PE14_AFS_6
#define PE14_AFS_TM26_OC12           PE14_AFS_7
#define PE14_AFS_MALE2               PE14_AFS_8
#define PE14_AFS_CCL_P0              PE14_AFS_9
#define PE14_AFS_TM36_OC3H           PE14_AFS_10
#define PE14_AFS_URT7_TX             PE14_AFS_11



#define PE15_AFS_0         AFS0
#define PE15_AFS_1         AFS1
#define PE15_AFS_2         AFS2
#define PE15_AFS_4         AFS4
#define PE15_AFS_5         AFS5
#define PE15_AFS_6         AFS6
#define PE15_AFS_7         AFS7
#define PE15_AFS_8         AFS8
#define PE15_AFS_9         AFS9
#define PE15_AFS_11        AFS11

#define PE15_AFS_GPE15               PE15_AFS_0
#define PE15_AFS_RTC_TS              PE15_AFS_1
#define PE15_AFS_I2C1_SDA            PE15_AFS_2
#define PE15_AFS_TM36_BK0            PE15_AFS_4
#define PE15_AFS_TM36_ETR            PE15_AFS_5
#define PE15_AFS_TM20_OC1N           PE15_AFS_6
#define PE15_AFS_TM26_OC1N           PE15_AFS_7
#define PE15_AFS_MALE                PE15_AFS_8
#define PE15_AFS_CCL_P1              PE15_AFS_9
#define PE15_AFS_URT7_RX             PE15_AFS_11
/////============================================================================================

/////============================================================================================




#endif






