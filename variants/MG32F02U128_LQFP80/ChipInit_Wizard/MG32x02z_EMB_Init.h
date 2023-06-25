
/**
 ******************************************************************************
 *
 * @file        MG32x02z_EMB_Init.h
 *
 * @brief       MG32x02z EMB Initial header File
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.00
 * @date        2016/04/11
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2016 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************
 * @par 		Disclaimer 
 *		The Demo software is provided "AS IS"  without any warranty, either 
 *		expressed or implied, including, but not limited to, the implied warranties 
 *		of merchantability and fitness for a particular purpose.  The author will 
 *		not be liable for any special, incidental, consequential or indirect 
 *		damages due to loss of data or any other reason. 
 *		These statements agree with the world wide and local dictated laws about 
 *		authorship and violence against these laws. 
 ******************************************************************************
 */ 

//*** <<< Use Configuration Wizard in Context Menu >>> ***

//<e1.0> EMB Initial Enable
//  <o0.0..3> EMB Mode Select
//                                <0=> No Address
//                                <1=> No Ext. Latch, 16Bit Address 
//                                <2=> 1 Address Phase, 30Bit Address 
//                                <3=> 1 Address Phase, 24Bit Address 
//                                <4=> 2 Address Phase, 30Bit Address 
//  <q4.3> Synchronous transaction enable
//  <q5.3> CLK Output Inverse Enable
//  <o4.16..17> EMB CE signal mode select. <0=>CE
//                                         <1=>ALE
//                                         <2=>ALE2
//  <e5.16> CE Output SoftWare Control Enable
//    <o5.17> CE Output Initial <0=> Logic-Low
//                              <1=> Logic-High
//  </e>
//  <q5.0> CE Output Inverse Enable
//  <o5.28..29> OE Output Signal Select <0=>OE
//                                      <1=>TM10_CKO 
//                                      <2=>TM16_CKO 
//                                      <3=>TM20_CKO 
//  <o4.26> OE Control timing Select <0=>Toggle
//                                   <1=>Drive Low
//  <o5.30..31> WE Output Signal Select <0=>WE
//                                      <1=>TM10_CKO 
//                                      <2=>TM16_CKO 
//                                      <3=>TM20_CKO 
//  <e4.1> Write Enable
//  <o4.27> WE Control timing Select <0=>Toggle
//                                   <1=>Drive Low
//  </e>
//  <o4.24> EMB MALE2 signal mode select. <0=>ALE2
//                                        <1=>ALE
//  <e5.18> ALE Output SoftWare Control Enable
//    <o5.19> ALE Output Initial <0=> Logic-Low
//                               <1=> Logic-High
//  </e>
//  <q5.1> ALE Output Inverse Enable 
//  <e5.20> ALE2 Output SoftWare Control Enable
//    <o5.21> ALE2 Output Initial <0=> Logic-Low
//                                <1=> Logic-High
//  </e>
//  <q5.2> ALE2 Output Inverse Enable 
//  <e5.22> BW0 Output SoftWare Control Enable
//    <o5.23> BW0 Output Initial <0=> Logic-Low
//                               <1=> Logic-High
//  </e>
//  <e5.24> BW1 Output SoftWare Control Enable
//    <o5.25> BW1 Output Initial <0=> Logic-Low
//                               <1=> Logic-High
//  </e>
//  <q5.8> Enable Address Reverse, 0 to 31 change to 31 to 0
//  <e2.0> Interrupt Enable
//    <q2.2> Write-protect error Interrupt
//  </e>
//  <q4.31> DMA Enable
//  <o3.4..6> EMB_CK_PSC clock Divider 
//                                <0=> DIV1 : CK_EMB Divided by 1
//                                <1=> DIV2 : CK_EMB Divided by 2
//                                <2=> DIV4 : CK_EMB Divided by 4
//                                <3=> DIV8 : CK_EMB Divided by 8
//                                <4=> DIV16 : CK_EMB Divided by 16
//                                <5=> DIV32 : CK_EMB Divided by 32
//                                <6=> DIV64 : CK_EMB Divided by 64
//                                <7=> DIV128 : CK_EMB Divided by 128
//  <o6.0..3> Address Setup Time (unit:MCLK) <0-1>
//  <o6.4..7> Address Pulse width (unit:MCLK) <1-16>
//  <o6.8..11> Address Hold Time (unit:MCLK) <0-1>
//  <o6.12..15> Data Setup Time (unit:MCLK) <0-1>
//  <o6.16..19> Data Pulse width (unit:MCLK) <1-16>
//  <o6.20..23> Data Hold Time (unit:MCLK) <0-1>
//</e>

//*** <<< end of configuration section >>> ***

/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef __MG32x02z_EMB_Init_H
#define __MG32x02z_EMB_Init_H

#ifdef __cplusplus
 extern "C" {
#endif 



/* Includes -----------------------------------------------------------------*/
#include "MG32x02z_EMB_DRV.h"

/* Exported types -----------------------------------------------------------*/

/* Exported constants -------------------------------------------------------*/
#define EMB_Mode_Select         1
#define EMB_Config_Enable       0x1
#define EMB_Config_INT          0x0
#define EMB_Config_CLK          0x0
#define EMB_Config_CR0          0x0
#define EMB_Config_CR1          0x000000
#define EMB_Config_CR2          69649

#define EMB_Mode_NOAddress                     0
#define EMB_Mode_NoLatch_16BitAddress          1
#define EMB_Mode_1AddressPhase_30BitAddress    2
#define EMB_Mode_1AddressPhase_24BitAddress    3
#define EMB_Mode_2AddressPhase_30BitAddress    4
#define EMB_Mode_2AddressPhase_24BitAddress    5

/* Exported macro -----------------------------------------------------------*/

/* Exported functions -------------------------------------------------------*/
void EMB_Initial(void);



#ifdef __cplusplus
}
#endif

#endif
/******************* (C) COPYRIGHT 2018 Megawin ************ END OF FILE *****/ 


