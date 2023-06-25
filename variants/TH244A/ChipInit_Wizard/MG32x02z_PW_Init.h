/**
 *******************************************************************************
 * @file        MG32x02z_PW_Init.h
 *
 * @brief       The PW initial code h file
 *
 * MG32x02z remote controller
 * @version     V1.15
 * @date        2022/01/04
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2020 Megawin Technology Co., Ltd.
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
#include "MG32x02z_PW.h"


#ifndef _MG32x02z_PW_INIT_H
/*!< _MG32x02z_PW_INIT_H */ 
#define _MG32x02z_PW_INIT_H


/**
 ******************************************************************************
 *
 * @struct      PW_InitConfig[]
 *              PW initial configuration array
 *
 ******************************************************************************
 */
//*** <<< Use Configuration Wizard in Context Menu >>> ***
static const unsigned int CONF_PW_InitConfig[] =
{
//  <h> Configure PW Module
//      <q3.1>  Enable Internal Voltage Reference (VBUF)
//      <i> VBUF = 1.4V, for ADC.
/*      <q3.4>  Enable BOD0 */
//      <e3.5>  Enable BOD1
//          <o3.10..12> Select BOD1 Detect Voltage threshold <0=> 2.0V
//                                                           <1=> 2.4V
//                                                           <2=> 3.7V
//                                                           <3=> 4.2V
//          <o3.8..9> Select Interrupt Trigger <0=> No Interrupt
//                                             <1=> Rising Edge
//                                             <2=> Falling Edge
//                                             <3=> Dual-Edge
//      </e>
//      <e3.13>  Enable BOD2
//          <i> Support MG32F02A128/A064/U128/U064/V032
//          <i> BOD2 Detect Voltage threshold 1.7V   
//          <o3.14..15> Select Interrupt Trigger <0=> No Interrupt
//                                               <1=> Rising Edge
//                                               <2=> Falling Edge
//                                               <3=> Dual-Edge
//      </e>
//      <o3.20..21> Select Wake-Up Delay From STOP Mode <0=> Level0 (0~15us)  
//                                                      <1=> Level1 (30~45us)  
//                                                      <2=> Level2 (60~75us)  
//                                                      <3=> Level3 (120~135us)      
/*      <o3.16..17> Select Low Power LDO <0=> LV0 (Lowest level)  */
/*                                       <1=> LV1 (the same LV2)  */
/*                                       <2=> LV2 (the same LV1)  */
/*                                       <3=> LV3 (Highest level) */
//      <o3.7> Select Core Voltage LDO When STOP Mode <0=> Normal
//                                                    <1=> Low Power
/*      <o3.6> Select Core Voltage LDO When ON Mode <0=> Normal    */
/*                                                  <1=> Low Power */
//      <o3.18> Wakeup Mode Select from SLEEP Mode <0=> Normal (Waiting 5 AHB clock)
//                                                 <1=> Low Power

//      <h> Configure Analog Module In SLEEP Mode 
//          <q4.16> Comparator CMP0
//              <i> Support MG32F02A132/A128/A072/A064/A032/U128/U064
//          <q4.17> Comparator CMP1
//              <i> Support MG32F02A132/A128/A072/A064/A032/U128/U064
//          <q4.18> Comparator CMP2
//              <i> Support MG32F02A132/A072
//          <q4.19> Comparator CMP3
//              <i> Support MG32F02A132/A072
//          <q4.24> USB
//              <i> Support MG32F02U128/U064
//      </h>

//      <h> Configure Analog Module In STOP Mode 
/*          <q4.1>  Power On  disable */
/*          <q4.4>  BOD0  disable     */
//          <q4.5>  BOD1
//          <q4.6>  BOD2 
//              <i> Support MG32F02U128/U064/A128/A064/V032
//          <q4.20> Comparator CMP0
//              <i> Support MG32F02A132/A128/A072/A064/A032/U128/U064
//          <q4.21> Comparator CMP1
//              <i> Support MG32F02A132/A128/A072/A064/A032/U128/U064
//          <q4.22> Comparator CMP2
//              <i> Support MG32F02A132/A072
//          <q4.23> Comparator CMP3
//              <i> Support MG32F02A132/A072
//          <q4.28> USB
//              <i> Support MG32F02U128/U064
//      </h>

//      <h> Configure Wakeup In STOP Mode
//      <i> GPIO wake-up by EXIC interrupt configured.
/*          <q5.4>  BOD0  disable*/
//          <q5.5>  BOD1
//          <q5.6>  BOD2
//              <i> Support MG32F02U128/U064/A128/A064/V032
//          <q5.16> Comparator CMP0
//              <i> Support MG32F02A132/A128/A072/A064/A032/U128/U064
//          <q5.17> Comparator CMP1
//              <i> Support MG32F02A132/A128/A072/A064/A032/U128/U064
//          <q5.18> Comparator CMP2
//              <i> Support MG32F02A132/A072
//          <q5.19> Comparator CMP3
//              <i> Support MG32F02A132/A072
//          <q5.24> USB
//              <i> Support MG32F02U128/U064
//          <q6.5>  RTC
//          <q6.6>  IWDT
//          <q6.8>  I2C0 (Detect Slave Address Only)
//          <q6.9>  I2C1 (Detect Slave Address Only)
//              <i> Support MG32F02A132/A128/A072/A064/U128/U064/V032
//      </h>

//      <e1.0> Configure Interrupt (IEA)
//          <q1.4>  BOD0
//          <q1.5>  BOD1
//          <q1.6>  BOD2
//              <i> Support MG32F02U128/U064/A128/A064/V032
//          <q1.7>  Wakeup
//      </e>
//  </h>

//*** <<< end of configuration section >>>    ***

0x00000000, // PW_STA 0 not use
0x00000000, // PW_INT 1 not use
0x00000000, // PW_KEY 2 not use
0x000020B0, // PW_CR0 3
0x00000000, // PW_CR1 4
0x00000000, // PW_WKSTP0 5
0x00000000, // PW_WKSTP1 6
};


/**
 * @name	Function announce
 *   		
 */
///@{  
void PW_Init (void);
///@}


#endif  // _MG32x02z_PW_INIT_H


