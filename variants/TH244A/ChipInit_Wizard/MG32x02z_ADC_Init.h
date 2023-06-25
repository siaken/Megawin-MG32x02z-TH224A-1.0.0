/**
 *******************************************************************************
 * @file        MG32x02z_ADC_Init.h
 *
 * @brief       The ADC initial code h file
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.02
 * @date        2022/09/20
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2016 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************* 
 * @par         Disclaimer
 * The Demo software is provided "AS IS" without any warranty, either
 * expressed or implied, including, but not limited to, the implied warranties
 * of merchantability and fitness for a particular purpose. The author will
 * not be liable for any special, incidental, consequential or indirect
 * damages due to loss of data or any other reason.
 * These statements agree with the world wide and local dictated laws about
 * authorship and violence against these laws.
 *******************************************************************************
 *******************************************************************************
 */
#include "MG32x02z.h"
#include "MG32x02z_ADC.h"
#include "RTE_Components.h"


#ifndef _MG32x02z_ADC_INIT_H
/*!< _MG32x02z_TM_INIT_H */ 
#define _MG32x02z_ADC_INIT_H

#include "MG32x02z_ADC_DRV.h"


//*** <<< Use Configuration Wizard in Context Menu >>> ***

// <h> ADC base parameters
//      <o0.16..23> ADC0 sampling time select <0-255>
//          <i> 0T ~ 255T clocks.T= CK_ADC0_INT
//      <o0.6..7> ADC0 data resolution select. <0=> 12-bit <1=> 10-bit <2=> 8-bit
//      <o1.3> ADC0 data alignment select <0=> Right (Right alignment) <1=> Left (Left alignment)
//      <o1.24..28> ADC adjusted 2's complement value of digital offset adjuster <0x10=> -16 <0x11=> -15 <0x12=> -14 <0x13=> -13 <0x14=> -12 <0x15=> -11
//                                                                              <0x16=> -10 <0x17=> -9 <0x18=> -8 <0x19=> -7 <0x1A=> -6 <0x1B=> -5
//                                                                              <0x1C=> -4 <0x1D=> -3 <0x1E=> -2 <0x1F=> -1 <0x00=> 0 <0x01=> +1
//                                                                              <0x02=> +2 <0x03=> +3 <0x04=> +4 <0x05=> +5 <0x06=> +6 <0x07=> +7
//                                                                              <0x08=> +8 <0x09=> +9 <0x0A=> +10 <0x0B=> +11 <0x0C=> +12 <0x0D=> +13 <0x0E=> +14 <0x0F=> +15
//      <o1.8> ADC0 data buffer overrun mode select <0=> Overwritten (Overwritten by new data) <1=> Keep (Preserved old date)
//      <o2.19..25> ADC0 conversion mode select <0x00=> ADC One shot mode <0x01=> ADC Continue mode <0x20=> Scan mode <0x21=> Scan continue mode <0x40=> Loop mode
//          <i> ADC One Shot mode : Convert one ADC data from single channel after one start trigger, then stop conversion.
//          <i> ADC Continue mode : Convert one ADC data from single channel after one start trigger, then hardware automatically start next ADC conversion continuously and does not stop conversion.
//          <i> Scan mode : Convert one ADC data from one selected channel after one start trigger, then stop conversion. To follow and convert next ADC data from next selected channel after next start trigger. Run the same steps for all selected channels.
//          <i> Scan continue mode : Convert multiple ADC data continuously from multiple selected channels after one start trigger, then stop conversion when scan finished for all selected channels.
//          <i> Loop mode : When ADC conversion start by one start trigger, hardware does the channel scan ADC conversion one by one until finish the conversion for all selected channels. And hardware automatically start next channel scan ADC conversion continuously and does not stop.
//      <o3.16..18> ADC0 start control source select <0x0=> SW : ADC0_START register setting <0x1=> TM00 : TM00_TRGO <0x2=> PIN : ADC0_TRG : ADC external trigger pin
//                                                   <0x3=> CMP0 : CMP0_OUT <0x4=> CMP1 : CMP1_OUT <0x5=> TM01 : TM01_TRGO <0x6=> TM20 : TM20_TRGO <7=> TM36 : TM36_TRGO
//      <o3.20..21> ADC0 start trigger selection <0x0=> Disable <0x1=> Rising edge <0x2=> Falling edge <0x4=> Dual-edge
//          <i> When selects Disable, the edge trigger detection is disabled and no start trigger signal output. When ADC0_START_SEL = SW (ADC0_START register setting), this register is no effect.
//      <o3.8..12> ADC One shot mode / ADC Continue Mode - channel select
//          <0=> PA0
//          <1=> PA1
//          <2=> PA2
//          <3=> PA3
//          <4=> PA4
//          <5=> PA5
//          <6=> PA6
//          <7=> PA7
//          <8=> PA8
//          <9=> PA9
//          <10=> PA10
//          <11=> PA11
//          <12=> PA12
//          <13=> PA13
//          <14=> PA14
//          <15=> PA15
//          <16=> Internal VSSA
//          <18=> INT_DACP0
//          <19=> INT_VBG (VBUF)
//          <24=> INT_LDO (VR0)
//          <25=> TSO Output 
//          <26=> 1/2 Vdd Output 
//      <h> Scan/Loop mode - sequence channel scan
//          <q4.0> PA0
//          <q4.1> PA1
//          <q4.2> PA2
//          <q4.3> PA3
//          <q4.4> PA4
//          <q4.5> PA5
//          <q4.6> PA6
//          <q4.7> PA7
//          <q4.8> PA8
//          <q4.9> PA9
//          <q4.10> PA10
//          <q4.11> PA11
//          <q4.12> PA12
//          <q4.13> PA13
//          <q4.14> PA14
//          <q4.15> PA15
//      </h>
// </h>
#define CONF_ADC_CR0_REG            0
#define CONF_ADC_CR1_REG            0x00000000
#define CONF_ADC_START_CONV_MDS     0x00000000
#define CONF_ADC_START_START_SEL    0x000000
#define CONF_ADC_MSK_MSKx           0x0000

#if CONF_ADC_START_CONV_MDS>0x00080000
    #if CONF_ADC_MSK_MSKx==0
        #error "Error: ADC0 needs to enable sequence channel"
    #endif
#endif

//  <e0.2> PGA configuration
//      <o1.0..5> ADC0 input PGA gain adjust bits. Gain range is x1 ~ x4. <0-63> 
//          <i> 0: x1, 1: x1.012 ... 42: x2.0 ... 63: x4.0
//          <i> Gain = {1+(ADC0_GAIN_PGA*3)/[63+(63-ADC0_GAIN_PGA)*3]}
//  </e>
#define CONF_ADC_ANA_PGA_EN         0
#define CONF_ADC_GAIN_PGA           0


//  <e0.1> Auto-off function
//          <i> The ADC needs time to wake up. So please refer to the power-on configuration of CLK. 
//      <o1.24..25> ADC power-on start up counter clock divider. <0=> DIV1 <1=> DIV4 <2=> DIV16 <3=> DIV32
//          <i> This divider is used to divide the input APB clock to output as the start up counter clock.
//      <o2.0..3> ADC power-on start up counter. <0-15>
//          <i> This register is only valid when auto power-off mode is enabled (ADC0_AUTOFF_EN=1).
//          <i> The range 0~15 is indicated counter inital value 0~15. 
//  </e>
#define CONF_ADC_CR0_AUTOFF         0x00000000
#define CONF_ADC_CLK_SDIV           0x00000000
#define CONF_ADC_CLK_SCOUNT         0U

#define CONF_ADC_CLK_SCNT           (CONF_ADC_CLK_SDIV | (CONF_ADC_CLK_SCOUNT << 28)) 


//  <h> Clock configuration
//     <o0.8..9> ADC0 internal sampling clock CK_ADC0_INT source select <0=> CK_ADC_PR <1=> CK_PLL <3=> TM00_TRGO <3=> TM01_TRGO
//          <i> CK_ADC_PR from CSC (AHB or APB).
//          <i> CK_PLL (CSC must enable PLL).
//          <i> TM00_TRGO : TM00 periodic output overflow event (User must enable TM00).
//          <i> TM01_TRGO : TM01 periodic output overflow event (User must enable TM01).
//     <o1.4..5> Internal clock CK_ADC_PR input divider <0=> DIV1 <1=> DIV2 <3=> DIV4 <3=> DIV16
//     <o1.10..11> ADC0 input clock CK_PLL divider. <0=> DIV2 <1=> DIV4 <3=> DIV5 <3=> DIV6
//  </h>
#define CONF_ADC_CLK_SRC            0x00000000
#define CONF_ADC_CLK_DIV            0x00000000


//  <e0.0> Window detect threshold
//      <o3.14..15> ADC0 output code spike limit function <0=> No operation <1=> Skip <2=> Clamp
//      <o0.1> Apply channel <0=> Single <1=> All
//      <o0.4..5> ADC0_OUT output signal select <0=> WDL (window detect state for outside low) <1=> WDI (window detect state for inside) <2=> WDH (window detect state for outside high)
//      <o1.0..11> ADC0 Voltage window detect lower threshold <0-4095>
//          <i> window detect lower threshold : 0~4095@12bit
//      <o2.0..11> ADC0 voltage window detect higher threshold <0-4095>
//          <i> window detect higher threshold : 0~4095@12bit
//  </e>
#define CONF_ADC_CR1_WIND_EN        0x00000000  
#define CONF_ADC_WINDTH_LT          0  
#define CONF_ADC_WINDTH_HT          0  
#define CONF_ADC_CR0_LIM_MDS        0x0000

#if CONF_ADC_WINDTH_LT > CONF_ADC_WINDTH_HT
    #error "Error: window detect lower threshold > window detect higher threshold"
#endif 

// <h> ADC0 data accumulation sum
//      <o0.16..22> ADC0 data sum accumulation data number <0-64>
//          <i> Value 0 indicates to disable accumulation and the maximum value 0x40 indicates 64 data to accumulate.
//      <o0.10> ADC0 data accumulation sum channel mode select <0=> Single (Single channel) <1=> All (All selected scan channels)
//          <i> When selects Single mode for ADC one shot conversion mode, the ADC0_SUM0_MUX selection channel data is accumulated into ADC0_SUM0. When selects All mode, the all selection channel data are accumulated one-by-one into ADC0_SUM0 only.
//          <i> When selects Single mode for ADC channel scan conversion mode, the ADC0_SUM1_MUX/ADC0_SUM2_MUX selection channel data are also separately accumulated into ADC0_SUM1/ADC0_SUM2.   
//      <o0.9> ADC0 data sum overrun mode select <0=> Overwritten (Overwritten by new data) <1=> Keep (Preserved old date)
//      <o1.16..19> Analog input channel selection for ADC0 data sum-0 function <0=> PA0 <1=> PA1 <2=> PA2 <3=> PA3 <4=> PA4 <5=> PA5 <6=> PA6 <7=> PA7 <8=> PA8
//                                                                              <9=> PA9 <10=> PA10 <11=> PA11 <12=> PA12 <13=> PA13 <14=> PA14 <15=> PA15
//      <o2.0..15> ADC0 data accumulator sum-0 initial value <0-65535>
//      <o1.20..23> Analog input channel selection for ADC0 data sum-1 function <0=> PA0 <1=> PA1 <2=> PA2 <3=> PA3 <4=> PA4 <5=> PA5 <6=> PA6 <7=> PA7 <8=> PA8
//                                                                              <9=> PA9 <10=> PA10 <11=> PA11 <12=> PA12 <13=> PA13 <14=> PA14 <15=> PA15
//      <o3.0..15> ADC0 data accumulator sum-1 initial value <0-65535>
//      <o1.24..27> Analog input channel selection for ADC0 data sum-2 function <0=> PA0 <1=> PA1 <2=> PA2 <3=> PA3 <4=> PA4 <5=> PA5 <6=> PA6 <7=> PA7 <8=> PA8
//                                                                              <9=> PA9 <10=> PA10 <11=> PA11 <12=> PA12 <13=> PA13 <14=> PA14 <15=> PA15
//      <o4.0..15> ADC0 data accumulator sum-2 initial value <0-65535>
// </h>
#define CONF_ADC_CR1_SUM_NUM        1024  
#define CONF_ADC_MSK_SUMx_MUX       0x00000000
#define CONF_ADC_SUM0               0
#define CONF_ADC_SUM1               0
#define CONF_ADC_SUM2               0

// ----------------------------------------------------------------------------
#define CONF_ADC_CLK_SETTING        0x00002000      // Config CK_DLY 
#define CONF_ADC_ANA_SETTING        0x00000300      // Config BIAS

// ----------------------------------------------------------------------------
#define CONF_ADC_CLK                (CONF_ADC_CLK_SRC | CONF_ADC_CLK_DIV | CONF_ADC_CLK_SETTING | CONF_ADC_CLK_SCNT)
#define CONF_ADC_WINDTH             ((CONF_ADC_WINDTH_HT << 16) | CONF_ADC_WINDTH_LT)
#define CONF_ADC_CR0                (CONF_ADC_CR0_REG | CONF_ADC_CR0_LIM_MDS | CONF_ADC_CR0_AUTOFF)
#define CONF_ADC_CR1                (CONF_ADC_CR1_REG | CONF_ADC_CR1_WIND_EN | CONF_ADC_CR1_SUM_NUM)
#define CONF_ADC_MSK                (CONF_ADC_MSK_SUMx_MUX | CONF_ADC_MSK_MSKx)
#define CONF_ADC_START              (CONF_ADC_START_CONV_MDS | CONF_ADC_START_START_SEL)
#define CONF_ADC_ANA                (CONF_ADC_ANA_PGA_EN)
#define CONF_ADC_GAIN               (CONF_ADC_GAIN_PGA)
//*** <<< end of configuration section >>>    ***






/**
 * @name	Function announce
 *   		
 */
///@{  
void ADC_Init (void);
///@}


#endif  // _MG32x02z_TM_INIT_H

