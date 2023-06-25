
/**
 ******************************************************************************
 *
 * @file        MG32x02z_GPL_Init.h
 *
 * @brief       The GPL Init C file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.01
 * @date        2017/03/09
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 * 
 ******************************************************************************* 
 * @par Disclaimer
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


#ifndef __MG32x02z_GPL_INIT_H
#define __MG32x02z_GPL_INIT_H
#define __MG32x02z_GPL_INIT_H_VER                          0.01     /*!< File Version */



//*** <<< Use Configuration Wizard in Context Menu >>> ***
//  <o1.10> Data parity check polarity select. <0=>Even <1=>Odd
//  <q1.31> Direct memory access.
//  <q1.6> Inverse input data.
//  <q1.1> Data byte Big/little endian change mode.
//  <o1.2..3> Data bit order. <0=>Disable <1=>8-bits <2=>16-bits <3=>32-bits
//  <e2.0> CRC function.
//    <o2.2..3> CRC mode. <0=> CRC16 CCITT : polynomial 0x1021
//                        <1=> CRC8 ATM : polynomial 0x07
//                        <2=> CRC16 IBM : polynomial 0x8005
//                        <3=> CRC32 IEEE802.3 : polynomial 0x4C11DB7
//    <o2.4..5> CRC operation data size. <1=> 8-bits
//                                       <2=> 16-bits
//                                       <3=> 32-bits
//    <O3> Programmable initial CRC value
//  </e>
//  <o2.6..7> Data output bit order reverse change mode select. <0=>Disable <1=>8-bits <2=>16-bits <3=>32-bits
//*** <<< end of configuration section >>> ***
#define     GPL_Config0_Enable       0
#define     GPL_Config0_CR0          0x80000000
#define     GPL_Config0_CR1          0x00000010
#define     GPL_Config0_CRCINIT      0x00000000



#ifdef __cplusplus
 extern "C" {
#endif



#include "MG32x02z_DRV.h"
#include "MG32x02z_GPL.h"



void GPL_Init(void);



#ifdef __cplusplus
}
#endif

#endif

