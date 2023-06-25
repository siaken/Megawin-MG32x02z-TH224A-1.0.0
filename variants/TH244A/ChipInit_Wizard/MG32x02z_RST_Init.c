/**
 *******************************************************************************
 *
 * @file        MG32x02z_RST_Init.c
 *
 * @brief       The RST Init C file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.10
 * @date        2018/01/31
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2018 Megawin Technology Co., Ltd.
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

#include "MG32x02z_RST_Init.h"



/**
 ******************************************************************************
 *
 * @struct      RST_InitConfig[]
 *              RST initial configuration array
 *
 ******************************************************************************
 */
//*** <<< Use Configuration Wizard in Context Menu >>> ***
static const unsigned int CONF_RST_InitConfig[] =
{
//  <h> Configure RST Module
    
//      <h> IO State Kept After Warm Reset
//          <q3.8>  PA[3:0] pins
//          <q3.9>  PA[11:8] pins
//          <q3.10> PB[3:0] pins
//          <q3.11> PB[11:8] pins
//          <q3.12> PC[3:0] pins
//          <q3.13> PC[11:8] pins
//          <q3.14> PD[3:0] pins
//          <q3.15> PD[11:8] pins
//          <q3.16> PE[3:0] pins
//              <i> Support MG32F02A132/A128/A072/A064/U128/U064
//          <q3.17> PE[9:8] pins
//              <i> Support MG32F02A132/A128/A072/A064/U128/U064
//      </h>
    
//      <h> Cold Reset Source Configuration
//          <q4.1>  Software Reset
//          <q4.2>  External Reset Pin
//          <q4.3>  CPU SYSRESETREQ Bit
//          <q4.4>  BOD0
//          <q4.5>  BOD1
//          <q4.7>  BOD2
//              <i> Support MG32F02U128/U064/A128/A064/V032
//          <q4.6>  Low Power STOP Mode
//          <q4.8>  CSC Missing Clock Detect
//          <q4.10> Flash Memory Read/Write/Erase Error
//          <q4.11> IWDT
//          <q4.12> WWDT
//          <q4.13> ADC Analog Voltage Watch-Dog 
//          <q4.16> Comparator CMP0
//              <i> Support MG32F02A132/A128/A072/A064/A032/U128/U064
//          <q4.17> Comparator CMP1
//              <i> Support MG32F02A132/A128/A072/A064/A032/U128/U064
//          <q4.18> Comparator CMP2
//              <i> Support MG32F02A132/A072
//          <q4.19> Comparator CMP3
//              <i> Support MG32F02A132/A072
//      </h>

//      <h> Warm Reset Source Configuration
//          <q5.1>  Software Reset
//          <q5.2>  External Reset Pin
//          <q5.3>  CPU SYSRESETREQ Bit
//          <q5.4>  BOD0
//          <q5.5>  BOD1
//          <q5.7>  BOD2
//              <i> Support MG32F02U128/U064/A128/A064/V032
//          <q5.6>  Low Power STOP Mode
//          <q5.8>  CSC Missing Clock Detect
//          <q5.10> Flash Memory Read/Write/Erase Error
//          <q5.11> IWDT
//          <q5.12> WWDT
//          <q5.13> ADC Analog Voltage Watch-Dog 
//          <q5.16> Comparator CMP0
//              <i> Support MG32F02A132/A128/A072/A064/A032/U128/U064
//          <q5.17> Comparator CMP1
//              <i> Support MG32F02A132/A128/A072/A064/A032/U128/U064
//          <q5.18> Comparator CMP2
//              <i> Support MG32F02A132/A072
//          <q5.19> Comparator CMP3
//              <i> Support MG32F02A132/A072
//      </h>

//      <h> Module Reset Action Configureation
//          <h> USB Module
//              <i> Support MG32F02U128/U064
//          <o3.25> USB Module Reset Control <0=> All, USB Reset Level-0
//                                           <1=> LV1, USB Reset Level-1
//          </h>
//      </h>


//  </h>

//*** <<< end of configuration section >>>    ***

0x00000000, // RST_STA 0 not use  0xC0000001
0x00000000, // RST_INT 1 not use
0x00000000, // RST_KEY 2 not use  0x00000001
0x00000000, // RST_CR0 3     0x00000000
0x00FFFFFF, // RST_CE 4      0x00000004
0x0000000E, // RST_WE 5      0x0000000E
0x00000000, // RST_AHB 6     0x00000000
0x00000000, // RST_APB0 7    0x00000000
0x00000000, // RST_APB1 8    0x00000000
};



/**
 *******************************************************************************
 * @brief  	    initialized RST module.
 * @details  
 * @return	    None	
 * @note
 * @par         Example
 * @code
    RST_Init ();
 * @endcode
 *******************************************************************************
 */
void RST_Init (void)
{

    RST_Base->KEY.MBIT.KEY = 0xA217;         // Unprotest RST module register

    RST_Base->CR0.W = CONF_RST_InitConfig[3];
    RST_Base->CE.W = CONF_RST_InitConfig[4];
    RST_Base->WE.W = CONF_RST_InitConfig[5];
    RST_Base->AHB.W = CONF_RST_InitConfig[6];
    RST_Base->APB0.W = CONF_RST_InitConfig[7];
    RST_Base->APB1.W = CONF_RST_InitConfig[8];

    RST_Base->KEY.MBIT.KEY = 0x0000;         // Protest RST module register

}
