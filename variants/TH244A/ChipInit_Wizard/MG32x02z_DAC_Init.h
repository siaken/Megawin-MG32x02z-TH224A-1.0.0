/**
 ******************************************************************************
 *
 * @file        MG32x02z_DAC_Init.h
 *
 * @brief       This file is used to configure DAC setting.
 *              Apply device : MG32F02A128/U128/A064/U064
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.01
 * @date        2021/09/08
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

#ifndef _MG32x02z_DAC_Init_H

#define _MG32x02z_DAC_Init_H

/* Includes ------------------------------------------------------------------*/
/* Wizard menu ---------------------------------------------------------------*/
//*** <<< Use Configuration Wizard in Context Menu >>> ***
//  <e0.0> DAC Configuration 
//      <i> MG32F02A128/U128/A064/U064 builds in one DAC module which embeds one 12-bit current mode DAC (digital-to-analog converter).
//      <i> The digital-to-analog conversion can be performed and start trigger by data register written, events (external pin input or internal events).
//      <i> The DAC can output a full-scale voltage from 0.2 volt to VDD-0.2 volt under the conversion rate up to 1MHz when DAC output buffer is on.
//  <q0.1> DAC output buffer enable 
//  <o0.4> DAC data alignment <0=> Right (Right alignment) <1=> Left (Left alignment)
//      <i> Data alignment for input code left/right justify
//  <o0.6..7> DAC data resolution <0=> 12-bit <1=> 10-bit <2=> 8-bit
//      <i> Configurable code width : 12/10/8-bit
//  <h> DAC start trigger control 
//      <o0.8..10> Trigger source <0=> WDAT : DAC_DAT0 register written
//                                <1=> PIN : DAC_TRG external trigger pin 
//                                <2=> CMP0 : CMP0_OUT
//                                <3=> TM00 : TM00_TRGO
//                                <4=> TM01 : TM01_TRGO 
//                                <5=> TM10 : TM10_TRGO 
//                                <6=> ITR6 : APB_ITR6
//                                <7=> ITR7 : APB_ITR7
//          <i> DAC start trigger control source select.
//      <o0.12..13> start trigger selection
//                                <0=> Disable    
//                                <1=> Rising edge
//                                <2=> Falling edge
//                                <3=> Dual-edge  
//          <i> DAC-0 start trigger selection. When selects Disable, the edge trigger detection is disabled and no start trigger signal output. 
//          <i> When DAC_START0_SEL = WDAT (DAC_DAT0 register written), this register is no effect.
//  </h>
//  </e>
#define CONF_DAC_CR0_REG    0x00000002   

//  <o0> Output code (ratio:x/4096) <0-4095>
//      <i> DAC: Voltage output / input range 0~4095 (for 12-bit mode)  
//      <i> if user select 10 or 8-bit mode, the initial wizard will automatically switch to 10 or 8-bit mode data
#define CONF_DAC_DAT0_PARA  0

//*** <<< end of configuration section >>>    ***
 
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

// DAC don't need to care about Left-Alignment
#if ((CONF_DAC_CR0_REG & 0x00000010) == 0)
    // DAC select Right-Alignment
    
    // ------------------------------------------------------------------------
    // Deal with 10/8 bit mode.
    #if ((CONF_DAC_CR0_REG & 0x000000C0) == 0x00000010)
        // DAC select 10-bit mode
        #define CONF_DAC_DAT0_REG   CONF_DAC_DAT0_PARA >> 2
    #elif ((CONF_DAC_CR0_REG & 0x000000C0) == 0x00000080)
        // DAC select 8-bit mode
        #define CONF_DAC_DAT0_REG   CONF_DAC_DAT0_PARA >> 4
    #else
        // DAC select 12-bit mode
        #define CONF_DAC_DAT0_REG   CONF_DAC_DAT0_PARA
    #endif 
#endif

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/**
 * @name	Function announce
 *   		
 */
///@{  
void DAC_Init(void);    
///@}

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* External vairables --------------------------------------------------------*/

#endif  // _MG32x02z_DAC_INIT_H
