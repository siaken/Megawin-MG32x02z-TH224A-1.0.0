/**
 ******************************************************************************
 *
 * @file        MG32x02z_CMP_Init.h
 *
 * @brief       This file is used to configure CMP setting.
 *              Apply device : MG32F02A032
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

#ifndef _MG32x02z_CMP_Init_H

#define _MG32x02z_CMP_Init_H

/* Includes ------------------------------------------------------------------*/
/* Wizard menu ---------------------------------------------------------------*/
//*** <<< Use Configuration Wizard in Context Menu >>> ***
//  <e0.0> CMP0 Config
//      <i> The chip builds in one CMP module which embeds four general purpose analog comparators with flexible
//      <i> input multiplexer, internal voltage references of R-ladder and independent digital synchronized filter for
//      <i> each analog comparator. 
//
//      <o0.8..10> Analog input positive channel selection <0=> IVREF <1=> CMP0_I0 (PA8) <2=> CMP0_I1 (PA9) <3=> CMP_C0 (PB0) <4=> CMP_C1 (PB1) <5=> DAC_P0
//      <o0.12..14> Analog input NEGATIVE channel selection <0=> IVREF <1=> CMP0_I0 (PA8) <2=> CMP0_I1 (PA9) <3=> CMP_C0 (PB0) <4=> CMP_C1 (PB1) <5=> DAC_P0
//      <o0.3> Response time <0=> Normal <1=> Slow (Low Power)
//      <o0.4> input hysteresis select <0=> No : no hysteresis <1=> LVL1 : with hysteresis about 10mV
//      <o0.16> Inverse analog comparator polarity <0=> Normal (Positive) <1=> Inverse (Negative)
//      <o0.17> Inverse analog comparator output pin <0=> Disable <1=> Inverse to Pin
//      <e1.0> Analog comparator's clock filter
//          <i> If user don't enable clock filter function it means "Bypass".
//          <o1.18..19> Analog comparator's clock filter <1=> CMP_CK <2=> TM00_TRGO <3=> TM01_TRGO
//          <o1.20..21> Analog comparator clock filter divider <0=> DIV1 <1=> DIV2 <2=> DIV4 <3=>DIV8
//      </e1>
//  </e>
#define CONF_CMP_AC0_BASE       0x00002100
#define CONF_CMP_AC0_FILTER     0x00040000

#if ((CONF_CMP_AC0_FILTER & 0x00000001) == 0)
    #define CONF_CMP_AC0        (CONF_CMP_AC0_BASE)
#else
    #define CONF_CMP_AC0        (CONF_CMP_AC0_BASE | (CONF_CMP_AC0_FILTER & 0xFFFFFFF0))
#endif


//  <e0.0> CMP1 Config
//      <i> The chip builds in one CMP module which embeds four general purpose analog comparators with flexible
//      <i> input multiplexer, internal voltage references of R-ladder and independent digital synchronized filter for
//      <i> each analog comparator. 
//
//      <o0.8..10> Analog input positive channel selection <0=> IVREF2 <1=> CMP1_I0 (PA10) <2=> CMP1_I1 (PA11) <3=> CMP_C0 (PB0) <4=> CMP_C1 (PB1) <5=> DAC_P0
//      <o0.12..14> Analog input NEGATIVE channel selection <0=> IVREF2 <1=> CMP1_I0 (PA10) <2=> CMP1_I1 (PA11) <3=> CMP_C0 (PB0) <4=> CMP_C1 (PB1) <5=> DAC_P0
//      <o0.3> Response time <0=> Normal <1=> Slow (Low Power)
//      <o0.4> input hysteresis select <0=> No : no hysteresis <1=> LVL1 : with hysteresis about 10mV
//      <o0.16> Inverse analog comparator polarity <0=> Normal (Positive) <1=> Inverse (Negative)
//      <o0.17> Inverse analog comparator output pin <0=> Disable <1=> Inverse to Pin
//      <e1.0> Analog comparator's clock filter
//          <i> If user don't enable clock filter function it means "Bypass".
//          <o1.18..19> Analog comparator's clock filter <1=> CMP_CK <2=> TM00_TRGO <3=> TM01_TRGO
//          <o1.20..21> Analog comparator clock filter divider <0=> DIV1 <1=> DIV2 <2=> DIV4 <3=>DIV8
//      </e1>
//  </e>
#define CONF_CMP_AC1_BASE       0x00002100
#define CONF_CMP_AC1_FILTER     0x00040000

#if ((CONF_CMP_AC1_FILTER & 0x00000001) == 0)
    #define CONF_CMP_AC1        (CONF_CMP_AC1_BASE)
#else
    #define CONF_CMP_AC1        (CONF_CMP_AC1_BASE | (CONF_CMP_AC1_FILTER & 0xFFFFFFF0))
#endif


//  <e0.0> IVREF Config
//      <i> The analog comparator is built-in internal voltage references - IVREF with 64-steps Rladder structure. 
//      <i> They can use as one of the analog comparator input and compare with another input from external source. (for CMP0)
//
//      <o0.1> Analog comparator main internal reference (R-ladder) top source select. <0=> VDDA (analog power voltage) <1=> VR0 (LDO VR0 output) 
//      <o0.2..7> Analog comparator main internal reference (R-ladder:0~63) <0-64>
//  </e>
//  <e0.8> IVREF2 Config
//      <i> The analog comparator is built-in internal voltage references - IVREF2 with 64-steps Rladder structure. 
//      <i> They can use as one of the analog comparator input and compare with another input from external source. (for CMP1)
//
//      <o0.9> Analog comparator main internal reference (R-ladder) top source select. <0=> VDDA (analog power voltage) <1=> VR0 (LDO VR0 output) 
//      <o0.10..15> Analog comparator 2nd internal reference (R-ladder:0~63) <0-64>
//  </e>
#define CONF_CMP_ANA            0

//*** <<< end of configuration section >>>    ***
 
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/**
 * @name	Function announce
 *   		
 */
///@{  
void CMP_ACx_Init(void);    
///@}

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* External vairables --------------------------------------------------------*/

#endif  // _MG32x02z_CMP_INIT_H
