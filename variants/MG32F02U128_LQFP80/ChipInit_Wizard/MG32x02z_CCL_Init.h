/**
 ******************************************************************************
 *
 * @file        MG32x02z_CCL_Init.h
 *
 * @brief       This file is used to configure CCL setting.
 *              Apply device : MG32F02A128/U128/A064/U064
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.00
 * @date        2021/07/12
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2020 Megawin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************
 * @par         Disclaimer
 *      The Demo software is provided "AS IS"  without any warranty, either
 *      expressed or implied, including, but not limited to, the implied warranties
 *      of merchantability and fitness for a particular purpose.  The author will
 *      not be liable for any special, incidental, consequential or indirect
 *      damages due to loss of data or any other reason.
 *      These statements agree with the world wide and local dictated laws about
 *      authorship and violence against these laws.
 ******************************************************************************
 ******************************************************************************
 */

#ifndef _MG32x02z_CCL_Init_H

#define _MG32x02z_CCL_Init_H

/* Includes ------------------------------------------------------------------*/
/* Wizard menu ---------------------------------------------------------------*/
// <<< Use Configuration Wizard in Context Menu >>>

//  <e0.0> CCL0 Configuration
//      <i> Configurable Cstom Logic
//      <i> Each CCL block can be connected to the device pins or other internal peripherals' signal. The CCL can eliminate external extra logic
//      <i> gate devices for simple glue logic functions on user application. It supports the L-to-H signal detected event flag and the interrupt.
//  
//      <h> APX CCL input path    
//      <o1.0..3> CCL0 IN0 input Mux select. 
//          <0x0=> Disable : Mask input
//          <0x1=> IN01 : Feedback from CCLn_SEQ signal
//          <0x2=> IN02 : Link from CCLn_AO signal
//          <0x3=> IN03 : PB11
//          <0x4=> IN04 : PA8
//          <0x5=> IN05 : PB0
//          <0x6=> IN06 : PB8
//          <0x7=> IN07 : PE0
//          <0x8=> IN08 : CMP0_OUT
//          <0x9=> IN09 : URT0_TX
//          <0xA=> IN0A : SPI0_MOSI (output)
//          <0xB=> IN0B : TM36_OC00
//          <0xC=> IN0C : TM26_OC00
//          <0xD=> IN0D : SDT_I0
//          <0xE=> IN0E : OBM_P0
//
//      <o1.4..7> CCL0 IN1 input Mux select. 
//          <0x0=> Disable : Mask input
//          <0x1=> IN01 : Feedback from CCLn_SEQ signal
//          <0x2=> IN02 : Link from CCLn_AO signal
//          <0x3=> IN03 : PB3
//          <0x4=> IN04 : PA9
//          <0x5=> IN05 : PB1
//          <0x6=> IN06 : PB9
//          <0x7=> IN07 : PE1
//          <0x8=> IN08 : CMP1_OUT
//          <0x9=> IN09 : URT1_TX
//          <0xA=> IN0A : SPI0_MISO (output)
//          <0xB=> IN0B : TM36_OC10
//          <0xC=> IN0C : TM26_OC10
//          <0xD=> IN0D : SDT_I1
//          <0xE=> IN0E : OBM_I0
//
//      <o1.8..11> CCL0 IN2 input Mux select. 
//          <0x0=> Disable : Mask input
//          <0x1=> in01 : feedback from ccln_seq signal
//          <0x2=> in02 : link from ccln_ao signal
//          <0x3=> in03 : PC1
//          <0x4=> in04 : PA10
//          <0x5=> in05 : PB2
//          <0x6=> in06 : PB10
//          <0x7=> in07 : PE2
//          <0x8=> in08 : ADC0_OUT
//          <0x9=> in09 : URT4_TX
//          <0xa=> in0a : SPI0_CLK
//          <0xb=> in0b : TM36_OC2
//          <0xc=> in0c : TM20_OC00
//          <0xd=> in0d : SDT_P0
//          <0xe=> in0e : OBM_I1
//      </h>
// 
//      <e0.1> CCL0 truth table configuration
//          <i> Configuration sequential :
//          <i> 1. Truth Table -> 2.with Filter -> 3. Edge Detect -> 4. Sequential mode -> 5. Sequential input -> 6. Invert option
//
//          <o0.16..23> 1. CCL0 truth table output value <0-0xFF>
//              <i> Map input pattern from [IN0, IN1, IN2]
//              <i> example 3-line input :  'AND'=0x80, 'NAND'=0x7F, 'OR'=0xFE, 'NOR'=0x01, 'XOR'=0x96, 'XNOR'=0x69
//              <i> example 2-line input [IN2] mask :  'AND'=0x08, 'NAND'=0x07, 'OR'=0x0E, 'NOR'=0x01, 'XOR'=0x06, 'XNOR'=0x09
//              <i> example 1-line input :  'NOT'=0x55 (for IN0 only), 'NOT'=0x33 (for IN1 only), 'NOT'=0x0F (for IN2 only)
//
//          <o0.4..5> 2. CCL0 filter select. <0=> Disable <1=> SYNC : Synchronizer enable <2=> FILTER : Filter enable 
//          <o0.6..7> 3. CCL0 edge detector mode select <0=> Disable <0x1=> Rising <0x2=> Falling <0x3=> Dual-edge
//          <o0.8..10> 4. CCL0 sequential logic mode select <0=> Disable <0x1=> DFF : D flip flop <0x2=> JK : JK flip flop <0x3=> DLH : D latch <0x4=> RS : RS latch
//          <o0.24..25> 5. CCL0 sequential logic input CCL_S0 select <0=> 0 <1=> 1 <2=> CCL_S1 (apply for CCL1 active)
//          <o0.11> 6. CCL0 output inverse enable bit <0=> Disable <1=> Enable
//      </e>
//
//      <o0.12..13> CCL0 internal clock input divider <0x0=> DIV1 : divided by 1 <0x1=> DIV2 : divided by 2 <0x2=> DIV4 : divided by 4 <0x3=> DIV8 : divided by 8
//


//  </e>
#define CONF_APX_CCL00      0x00000000
#define CONF_APX_CCL01      0x00000000

//  <e0.0> CCL1 Configuration
//      <i> Configurable Cstom Logic
//      <i> Each CCL block can be connected to the device pins or other internal peripherals' signal. The CCL can eliminate external extra logic
//      <i> gate devices for simple glue logic functions on user application. It supports the L-to-H signal detected event flag and the interrupt.
//  
//      <h> APX CCL input path    
//      <o1.0..3> CCL0 IN0 input Mux select. 
//          <0x0=> Disable : Mask input
//          <0x1=> IN01 : Feedback from CCLn_SEQ signal
//          <0x2=> IN02 : Link from CCLn_AO signal
//          <0x3=> IN03 : PB11
//          <0x4=> IN04 : PA8
//          <0x5=> IN05 : PB0
//          <0x6=> IN06 : PB8
//          <0x7=> IN07 : PE0
//          <0x8=> IN08 : CMP0_OUT
//          <0x9=> IN09 : URT0_TX
//          <0xA=> IN0A : SPI0_MOSI (output)
//          <0xB=> IN0B : TM36_OC00
//          <0xC=> IN0C : TM26_OC00
//          <0xD=> IN0D : SDT_I0
//          <0xE=> IN0E : OBM_P0
//
//      <o1.4..7> CCL0 IN1 input Mux select. 
//          <0x0=> Disable : Mask input
//          <0x1=> IN01 : Feedback from CCLn_SEQ signal
//          <0x2=> IN02 : Link from CCLn_AO signal
//          <0x3=> IN03 : PB3
//          <0x4=> IN04 : PA9
//          <0x5=> IN05 : PB1
//          <0x6=> IN06 : PB9
//          <0x7=> IN07 : PE1
//          <0x8=> IN08 : CMP1_OUT
//          <0x9=> IN09 : URT1_TX
//          <0xA=> IN0A : SPI0_MISO (output)
//          <0xB=> IN0B : TM36_OC10
//          <0xC=> IN0C : TM26_OC10
//          <0xD=> IN0D : SDT_I1
//          <0xE=> IN0E : OBM_I0
//
//      <o1.8..11> CCL0 IN2 input Mux select. 
//          <0x0=> Disable : Mask input
//          <0x1=> in01 : feedback from ccln_seq signal
//          <0x2=> in02 : link from ccln_ao signal
//          <0x3=> in03 : PC1
//          <0x4=> in04 : PA10
//          <0x5=> in05 : PB2
//          <0x6=> in06 : PB10
//          <0x7=> in07 : PE2
//          <0x8=> in08 : ADC0_OUT
//          <0x9=> in09 : URT4_TX
//          <0xa=> in0a : SPI0_CLK
//          <0xb=> in0b : TM36_OC2
//          <0xc=> in0c : TM20_OC00
//          <0xd=> in0d : SDT_P0
//          <0xe=> in0e : OBM_I1
//      </h>
// 
//      <e0.1> CCL1 truth enable
//          <i> Configuration sequential :
//          <i> 1. Truth Table (with Filter / without Filter) -> 2. Edge Detect -> 3. Sequential mode with Sequential input -> 4. Invert option
//
//          <o0.16..23> 1. CCL1 truth table output value <0-0xFF>
//              <i> Map input pattern from [IN0, IN1, IN2]
//              <i> example 3-line input :  'AND'=0x80, 'NAND'=0x7F, 'OR'=0xFE, 'NOR'=0x01, 'XOR'=0x96, 'XNOR'=0x69
//              <i> example 2-line input [IN2] mask :  'AND'=0x08, 'NAND'=0x07, 'OR'=0x0E, 'NOR'=0x01, 'XOR'=0x06, 'XNOR'=0x09
//              <i> example 1-line input :  'NOT'=0x55 (for IN0 only), 'NOT'=0x33 (for IN1 only), 'NOT'=0x0F (for IN2 only)
//          <o0.4..5> 1.1 CCL1 filter select. <0=> Disable <1=> SYNC : Synchronizer enable <2=> FILTER : Filter enable 
//
//          <o0.6..7> 2. CCL1 edge detector mode select <0=> Disable <0x1=> Rising <0x2=> Falling <0x3=> Dual-edge
//          <o0.8..10> 3. CCL1 sequential logic mode select <0=> Disable <0x1=> DFF : D flip flop <0x2=> JK : JK flip flop <0x3=> DLH : D latch <0x4=> RS : RS latch
//          <o0.24..25> 3.1 CCL1 sequential logic input CCL_S1 select <0=> 0 <1=> 1 
//          <o0.11> 4. CCL1 output inverse enable bit <0=> Disable <1=> Enable
//      </e>
//
//      <o0.12..13> CCL1 internal clock input divider <0x0=> DIV1 : divided by 1 <0x1=> DIV2 : divided by 2 <0x2=> DIV4 : divided by 4 <0x3=> DIV8 : divided by 8
//
//  </e>
#define CONF_APX_CCL10      0x00000000
#define CONF_APX_CCL11      0x00000000

// <<< end of Configuration section >>> 
 
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#if ((CONF_APX_CCL00 & 0x03000000) == 0x02000000)
    #if ((CONF_APX_CCL10 & 0x00000001) == 0)
        #warning "User don't enable CCL1. So User can't select CCL_S1 of sequential logic input in CCL0 configuration"
    #endif
#endif
    
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/**
 * @name	Function announce
 *   		
 */
///@{  
void APX_CCL_Init(void);    
///@}

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* External vairables --------------------------------------------------------*/

#endif  // _MG32x02z_CCL_INIT_H
