/**
 ******************************************************************************
 *
 * @file        MG32x02z_RTC_Init.h
 *
 * @brief       This file is used to configure RTC setting.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.02
 * @date        2021/08/11 17:55 (H File Generated Date)
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
 #include "MG32x02z__Common_DRV.h"
 #include "MG32x02z_RTC.h"
 
 #ifndef _MG32x02z_RTC_INIT_H
 /*!< _MG32x02z_RTC_INIT_H */ 
 #define _MG32x02z_RTC_INIT_H
 


/*!< MG32x02z_RTC_Init define */
#define MG32_Protect 0xA217
#define MG32_UnProtect 0x217A

 
 
 
 //*** <<< Use Configuration Wizard in Context Menu >>> ***
 //<e4.0> RTC Enable
 //<i> RTC module configure.(ENABLE/DISABLE)
 
 //<o> RTC_Count_Value 0~0xFFFFFFFE(0~4294967294) <0-0xFFFFFFFE>
 #define CONF_RTC_RLR 0xFFFFFFF1
 
 //<o> RTC alarm compared value. 0~0xFFFFFFFE(0~4294967294) <0-0xFFFFFFFE>
 #define CONF_RTC_ALM 0xFFFFF000
 
 //<h> RTC Input Clock Tree Configuration
 //<o.2..3> RTC_CK_SEL <0=> CK_LS <1=> CK_UT <2=> CK_APB <3=> TM01_TRGO
 //<i> RTC input clock CK_RTC source selects.
 
 //<o.4..5> RTC_CK_DIV <0=> DIV1 <1=> DIV2 <2=> DIV4 <3=> DIV8
 //<i> RTC internal clock CK_RTC_INT input divider.
 
 //<o.7> RTC_CK_PDIV <0=> DIV4096 <1=> DIV1
 //<i> RTC internal clock CK_RTC_INT input pre-divider.
 //</h>
 #define CONF_RTC_CLK_SEL 0x00000080
 
 //<h> RTC Interrupt Configuration
 //<i> Used with IRQ handler, or enable RTC NVIC by self.
 //<e0.0> RTC_IEA
 //<i> RTC all interrupts enable.
 //<q.1> RTC_ALM_IE
 //<i> RTC alarm matched interrupt enable.
 //<q.2> RTC_PC_IE
 //<i> RTC periodic interrupt enable.
 //<q.3> RTC_TS_IE
 //<i> RTC time stamp interrupt enable.
 //<q.4> RTC_TIE
 //<i> RTC time overflow/underflow interrupt enable.
 //<q.5> RTC_RCR_IE
 //<i> RTC_RCR register reload, software capture or RTC_ALM register value update allowed interrupt enable.
 //</e>
 //</h>
 #define CONF_RTC_INT_CON 0x00000000
 
 //<h> RTC Wake Up Configuration
 //<q.16> RTC_ALM_WPEN
 //<i> RTC detect RTC_ALMF flag wakeup from STOP mode enable bit.
 //<q.17> RTC_PC_WPEN
 //<i> RTC detect RTC_PCF flag wakeup from STOP mode enable bit.
 //<q.19> RTC_TF_WPEN
 //<i> RTC detect RTC_TOF flag wakeup from STOP mode enable bit.
 //</h>
 
 //<h> RTC Output Configuration
 //<e.15> RTC Output State Control
 //<i> RTC_OUT output signal initial state control.
 //<i> When locked, disables the register bit write access.
 //<i> Hardware auto clear after register write access.
 //<o.14> RTC Output Initial State Select <0=> Level Low <1=> Level High
 //</e>
 //<o.8..9> RTC_OUT_SEL <0=> ALM : Alarm compare output event <1=> PC : CK_RTC_INT periodic clock signal <2=> TS : Time stamp trigger event <3=> TO : Timer overflow signal toggle output
 //</h>
 
 //<o.12..13> RTC Time Stamp Trigger Edge Select <0=> Disable <1=> Rising Edge <2=> Falling Edge <3=> Daul-Edge
 
 //<q.1> RTC Alarm Enable
 //</e>
 #define CONF_RTC_CR0_CON 0x00000301
 
 //*** <<< end of configuration section >>>    ***  

/**
 * @name    Function announce
 *   
 */
///@{  
void RTC_Init(void);
///@}

#endif      // _MG32x02z_RTC_INIT_H

