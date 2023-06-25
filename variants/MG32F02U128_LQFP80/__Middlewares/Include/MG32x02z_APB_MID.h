/**
 ******************************************************************************
 *
 * @file        MG32x02z_APB_MID.h
 *
 * @brief       This file provides firmware functions to manage the following 
 *              functionalities of the APB peripheral:
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.09
 * @date        2022/01/21
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
 ******************************************************************************
 */ 

#ifndef _MG32x02z_APB_MID_H

/*!< _MG32x02z_APB_DRV_H */ 
#define _MG32x02z_APB_MID_H

#include "MG32x02z.h"
#include "MG32x02z_Common_MID.h"
#include "MG32x02z_APB.h"
#include "MG32x02z_SYS.h"
#include "MG32x02z__ExtraStruct.h"


#if defined(MG32_1ST) || defined(MG32_3RD)
/**
 * @name	APB_Timer_Macro_Enable
 *   		APB Timer (EN+EN2) enable
 */ 
///@{  
#define APB_TM00_MACRO      APB_CR1_TM00_EN_enable_w + APB_CR1_TM00_EN2_enable_w    /*!<  TM00_EN + TM00_EN2.   */
#define APB_TM01_MACRO      APB_CR1_TM01_EN_enable_w + APB_CR1_TM01_EN2_enable_w    /*!<  TM01_EN + TM01_EN2.   */
#define APB_TM10_MACRO      APB_CR1_TM10_EN_enable_w + APB_CR1_TM10_EN2_enable_w    /*!<  TM10_EN + TM10_EN2.   */
#define APB_TM16_MACRO      APB_CR1_TM16_EN_enable_w + APB_CR1_TM16_EN2_enable_w    /*!<  TM16_EN + TM16_EN2.   */
#define APB_TM20_MACRO      APB_CR1_TM20_EN_enable_w + APB_CR1_TM20_EN2_enable_w    /*!<  TM20_EN + TM20_EN2.   */
#define APB_TM26_MACRO      APB_CR1_TM26_EN_enable_w + APB_CR1_TM26_EN2_enable_w    /*!<  TM26_EN + TM26_EN2.   */
#define APB_TM36_MACRO      APB_CR1_TM36_EN_enable_w + APB_CR1_TM36_EN2_enable_w    /*!<  TM36_EN + TM36_EN2.   */
///@}

/**
 * @name	APB_Timer_Prescaler_Enable
 *   		APB Timer Prescaler (ENABLE) enable
 */ 
///@{  
#define APB_TM00_PRESCALER_ENABLE   APB_CR1_TM00_EN2_enable_w   /*!<  TM00_EN2 (PRESCALER Counter). */
#define APB_TM01_PRESCALER_ENABLE   APB_CR1_TM01_EN2_enable_w   /*!<  TM01_EN2 (PRESCALER Counter). */
#define APB_TM10_PRESCALER_ENABLE   APB_CR1_TM10_EN2_enable_w   /*!<  TM10_EN2 (PRESCALER Counter). */
#define APB_TM16_PRESCALER_ENABLE   APB_CR1_TM16_EN2_enable_w   /*!<  TM16_EN2 (PRESCALER Counter). */
#define APB_TM20_PRESCALER_ENABLE   APB_CR1_TM20_EN2_enable_w   /*!<  TM20_EN2 (PRESCALER Counter). */
#define APB_TM26_PRESCALER_ENABLE   APB_CR1_TM26_EN2_enable_w   /*!<  TM26_EN2 (PRESCALER Counter). */
#define APB_TM36_PRESCALER_ENABLE   APB_CR1_TM36_EN2_enable_w   /*!<  TM36_EN2 (PRESCALER Counter). */
///@}

/**
 * @name	APB_Timer_Main_Enable
 *   		APB Timer (ENABLE) enable
 */ 
///@{  
#define APB_TM00_MAIN_ENABLE        APB_CR1_TM00_EN_enable_w    /*!<  TM00_EN (Main Counter).   */
#define APB_TM01_MAIN_ENABLE        APB_CR1_TM01_EN_enable_w    /*!<  TM01_EN (Main Counter).   */
#define APB_TM10_MAIN_ENABLE        APB_CR1_TM10_EN_enable_w    /*!<  TM10_EN (Main Counter).   */
#define APB_TM16_MAIN_ENABLE        APB_CR1_TM16_EN_enable_w    /*!<  TM16_EN (Main Counter).   */
#define APB_TM20_MAIN_ENABLE        APB_CR1_TM20_EN_enable_w    /*!<  TM20_EN (Main Counter).   */
#define APB_TM26_MAIN_ENABLE        APB_CR1_TM26_EN_enable_w    /*!<  TM26_EN (Main Counter).   */
#define APB_TM36_MAIN_ENABLE        APB_CR1_TM36_EN_enable_w    /*!<  TM36_EN (Main Counter).   */
///@}
#endif

#if defined(MG32_2ND)
/**
 * @name	APB_Timer_Macro_Enable
 *   		APB Timer (EN+EN2) enable
 */ 
///@{  
#define APB_TM00_MACRO      APB_CR1_TM00_EN_enable_w + APB_CR1_TM00_EN2_enable_w    /*!<  TM00_EN + TM00_EN2.   */
#define APB_TM01_MACRO      APB_CR1_TM01_EN_enable_w + APB_CR1_TM01_EN2_enable_w    /*!<  TM01_EN + TM01_EN2.   */
#define APB_TM10_MACRO      APB_CR1_TM10_EN_enable_w + APB_CR1_TM10_EN2_enable_w    /*!<  TM10_EN + TM10_EN2.   */
#define APB_TM16_MACRO      APB_CR1_TM16_EN_enable_w + APB_CR1_TM16_EN2_enable_w    /*!<  TM16_EN + TM16_EN2.   */
#define APB_TM36_MACRO      APB_CR1_TM36_EN_enable_w + APB_CR1_TM36_EN2_enable_w    /*!<  TM36_EN + TM36_EN2.   */
///@}

/**
 * @name	APB_Timer_Prescaler_Enable
 *   		APB Timer Prescaler (ENABLE) enable
 */ 
///@{  
#define APB_TM00_PRESCALER_ENABLE   APB_CR1_TM00_EN2_enable_w   /*!<  TM00_EN2 (PRESCALER Counter). */
#define APB_TM01_PRESCALER_ENABLE   APB_CR1_TM01_EN2_enable_w   /*!<  TM01_EN2 (PRESCALER Counter). */
#define APB_TM10_PRESCALER_ENABLE   APB_CR1_TM10_EN2_enable_w   /*!<  TM10_EN2 (PRESCALER Counter). */
#define APB_TM16_PRESCALER_ENABLE   APB_CR1_TM16_EN2_enable_w   /*!<  TM16_EN2 (PRESCALER Counter). */
#define APB_TM36_PRESCALER_ENABLE   APB_CR1_TM36_EN2_enable_w   /*!<  TM36_EN2 (PRESCALER Counter). */
///@}

/**
 * @name	APB_Timer_Main_Enable
 *   		APB Timer (ENABLE) enable
 */ 
///@{  
#define APB_TM00_MAIN_ENABLE        APB_CR1_TM00_EN_enable_w    /*!<  TM00_EN (Main Counter).       */
#define APB_TM01_MAIN_ENABLE        APB_CR1_TM01_EN_enable_w    /*!<  TM01_EN (Main Counter).       */
#define APB_TM10_MAIN_ENABLE        APB_CR1_TM10_EN_enable_w    /*!<  TM10_EN (Main Counter).       */
#define APB_TM16_MAIN_ENABLE        APB_CR1_TM16_EN_enable_w    /*!<  TM16_EN (Main Counter).       */
#define APB_TM36_MAIN_ENABLE        APB_CR1_TM36_EN_enable_w    /*!<  TM36_EN (Main Counter).       */
///@}
#endif

#if defined(MG32_4TH)
/**
 * @name	APB_Timer_Macro_Enable
 *   		APB Timer (EN+EN2) enable
 */ 
///@{  
#define APB_TM00_MACRO      APB_CR1_TM00_EN_enable_w + APB_CR1_TM00_EN2_enable_w    /*!<  TM00_EN + TM00_EN2.   */
#define APB_TM01_MACRO      APB_CR1_TM01_EN_enable_w + APB_CR1_TM01_EN2_enable_w    /*!<  TM01_EN + TM01_EN2.   */
#define APB_TM10_MACRO      APB_CR1_TM10_EN_enable_w + APB_CR1_TM10_EN2_enable_w    /*!<  TM10_EN + TM10_EN2.   */
#define APB_TM16_MACRO      APB_CR1_TM16_EN_enable_w + APB_CR1_TM16_EN2_enable_w    /*!<  TM16_EN + TM16_EN2.   */
#define APB_TM20_MACRO      APB_CR1_TM20_EN_enable_w + APB_CR1_TM20_EN2_enable_w    /*!<  TM20_EN + TM20_EN2.   */
#define APB_TM36_MACRO      APB_CR1_TM36_EN_enable_w + APB_CR1_TM36_EN2_enable_w    /*!<  TM36_EN + TM36_EN2.   */
///@}

/**
 * @name	APB_Timer_Prescaler_Enable
 *   		APB Timer Prescaler (ENABLE) enable
 */ 
///@{  
#define APB_TM00_PRESCALER_ENABLE   APB_CR1_TM00_EN2_enable_w   /*!<  TM00_EN2 (PRESCALER Counter). */
#define APB_TM01_PRESCALER_ENABLE   APB_CR1_TM01_EN2_enable_w   /*!<  TM01_EN2 (PRESCALER Counter). */
#define APB_TM10_PRESCALER_ENABLE   APB_CR1_TM10_EN2_enable_w   /*!<  TM10_EN2 (PRESCALER Counter). */
#define APB_TM16_PRESCALER_ENABLE   APB_CR1_TM16_EN2_enable_w   /*!<  TM16_EN2 (PRESCALER Counter). */
#define APB_TM20_PRESCALER_ENABLE   APB_CR1_TM20_EN2_enable_w   /*!<  TM20_EN2 (PRESCALER Counter). */
#define APB_TM36_PRESCALER_ENABLE   APB_CR1_TM36_EN2_enable_w   /*!<  TM36_EN2 (PRESCALER Counter). */
///@}

/**
 * @name	APB_Timer_Main_Enable
 *   		APB Timer (ENABLE) enable
 */ 
///@{  
#define APB_TM00_MAIN_ENABLE        APB_CR1_TM00_EN_enable_w    /*!<  TM00_EN (Main Counter).   */
#define APB_TM01_MAIN_ENABLE        APB_CR1_TM01_EN_enable_w    /*!<  TM01_EN (Main Counter).   */
#define APB_TM10_MAIN_ENABLE        APB_CR1_TM10_EN_enable_w    /*!<  TM10_EN (Main Counter).   */
#define APB_TM16_MAIN_ENABLE        APB_CR1_TM16_EN_enable_w    /*!<  TM16_EN (Main Counter).   */
#define APB_TM20_MAIN_ENABLE        APB_CR1_TM20_EN_enable_w    /*!<  TM20_EN (Main Counter).   */
#define APB_TM36_MAIN_ENABLE        APB_CR1_TM36_EN_enable_w    /*!<  TM36_EN (Main Counter).   */
///@}
#endif



#if defined(MG32_1ST)
/**
 * @name	APB_ITR6_MUX
 *   		ITR6 source configuration
 */ 
///@{  
#define APB_ITR6_TM00_TRGO          APB_CR2_ITR6_MUX_trg0_w     /*!<  ITR6 signal from TM00_TRGO.   */
#define APB_ITR6_TM10_TRGO          APB_CR2_ITR6_MUX_trg1_w     /*!<  ITR6 signal from TM10_TRGO.   */
#define APB_ITR6_TM20_TRGO          APB_CR2_ITR6_MUX_trg2_w     /*!<  ITR6 signal from TM20_TRGO.   */
#define APB_ITR6_TM36_TRGO          APB_CR2_ITR6_MUX_trg3_w     /*!<  ITR6 signal from TM36_TRGO.   */
#define APB_ITR6_INT_PB             APB_CR2_ITR6_MUX_trg4_w     /*!<  ITR6 signal from INT_PB.      */
#define APB_ITR6_URT1_TMO           APB_CR2_ITR6_MUX_trg5_w     /*!<  ITR6 signal from URT1_TMO.    */
#define APB_ITR6_URT2_BRO           APB_CR2_ITR6_MUX_trg6_w     /*!<  ITR6 signal from URT2_BRO.    */
#define APB_ITR6_URT2_TMO           APB_CR2_ITR6_MUX_trg7_w     /*!<  ITR6 signal from URT2_TMO.    */
///@}

/**
 * @name	APB_ITR7_MUX
 *   		ITR7 source configuration
 */ 
///@{  
#define APB_ITR7_TM01_TRGO          APB_CR2_ITR7_MUX_trg0_w     /*!<  ITR7 signal from TM01_TRGO.   */
#define APB_ITR7_TM16_TRGO          APB_CR2_ITR7_MUX_trg1_w     /*!<  ITR7 signal from TM16_TRGO.   */
#define APB_ITR7_TM26_TRGO          APB_CR2_ITR7_MUX_trg2_w     /*!<  ITR7 signal from TM26_TRGO.   */
#define APB_ITR7_ADC0_OUT           APB_CR2_ITR7_MUX_trg3_w     /*!<  ITR7 signal from ADC0_OUT.    */
#define APB_ITR7_INT_PD             APB_CR2_ITR7_MUX_trg4_w     /*!<  ITR7 signal from INT_PD.      */
#define APB_ITR7_URT1_BRO           APB_CR2_ITR7_MUX_trg5_w     /*!<  ITR7 signal from URT1_BRO.    */
#define APB_ITR7_URT3_BRO           APB_CR2_ITR7_MUX_trg6_w     /*!<  ITR7 signal from URT3_BRO.    */
#define APB_ITR7_URT3_TMO           APB_CR2_ITR7_MUX_trg7_w     /*!<  ITR7 signal from URT3_TMO.    */
#define APB_ITR7_ICKO               APB_CR2_ITR7_MUX_trg8_w     /*!<  ITR7 signal from ICKO.        */
#define APB_ITR7_RTC_OUT            APB_CR2_ITR7_MUX_trg9_w     /*!<  ITR7 signal from RTC_OUT.     */
#define APB_ITR7_TM36_XOR           APB_CR2_ITR7_MUX_trg10_w    /*!<  ITR7 signal from TM36_XOR.    */
///@}
#endif

#if defined(MG32_2ND)
/**
 * @name	APB_ITR6_MUX
 *   		ITR6 source configuration
 */ 
///@{  
#define APB_ITR6_TM00_TRGO          APB_CR2_ITR6_MUX_trg0_w     /*!<  ITR6 signal from TM00_TRGO.   */
#define APB_ITR6_TM10_TRGO          APB_CR2_ITR6_MUX_trg1_w     /*!<  ITR6 signal from TM10_TRGO.   */
#define APB_ITR6_TM36_TRGO          APB_CR2_ITR6_MUX_trg3_w     /*!<  ITR6 signal from TM36_TRGO.   */
#define APB_ITR6_INT_PB             APB_CR2_ITR6_MUX_trg4_w     /*!<  ITR6 signal from INT_PB.      */
#define APB_ITR6_URT1_TMO           APB_CR2_ITR6_MUX_trg5_w     /*!<  ITR6 signal from URT1_TMO.    */
///@}

/**
 * @name	APB_ITR7_MUX
 *   		ITR7 source configuration
 */ 
///@{  
#define APB_ITR7_TM01_TRGO          APB_CR2_ITR7_MUX_trg0_w     /*!<  ITR7 signal from TM01_TRGO.   */
#define APB_ITR7_TM16_TRGO          APB_CR2_ITR7_MUX_trg1_w     /*!<  ITR7 signal from TM16_TRGO.   */
#define APB_ITR7_ADC0_OUT           APB_CR2_ITR7_MUX_trg3_w     /*!<  ITR7 signal from ADC0_OUT.    */
#define APB_ITR7_INT_PD             APB_CR2_ITR7_MUX_trg4_w     /*!<  ITR7 signal from INT_PD.      */
#define APB_ITR7_URT1_BRO           APB_CR2_ITR7_MUX_trg5_w     /*!<  ITR7 signal from URT1_BRO.    */
#define APB_ITR7_ICKO               APB_CR2_ITR7_MUX_trg8_w     /*!<  ITR7 signal from ICKO.        */
#define APB_ITR7_RTC_OUT            APB_CR2_ITR7_MUX_trg9_w     /*!<  ITR7 signal from RTC_OUT.     */
#define APB_ITR7_TM36_XOR           APB_CR2_ITR7_MUX_trg10_w    /*!<  ITR7 signal from TM36_XOR.    */
///@}
#endif

#if defined(MG32_3RD)
/**
 * @name	APB_ITR6_MUX
 *   		ITR6 source configuration
 */ 
///@{  
#define APB_ITR6_TM00_TRGO          APB_CR2_ITR6_MUX_trg0_w     /*!<  ITR6 signal from TM00_TRGO.   */
#define APB_ITR6_TM10_TRGO          APB_CR2_ITR6_MUX_trg1_w     /*!<  ITR6 signal from TM10_TRGO.   */
#define APB_ITR6_TM20_TRGO          APB_CR2_ITR6_MUX_trg2_w     /*!<  ITR6 signal from TM20_TRGO.   */
#define APB_ITR6_TM36_TRGO          APB_CR2_ITR6_MUX_trg3_w     /*!<  ITR6 signal from TM36_TRGO.   */
#define APB_ITR6_INT_PB             APB_CR2_ITR6_MUX_trg4_w     /*!<  ITR6 signal from INT_PB.      */
#define APB_ITR6_URT1_TMO           APB_CR2_ITR6_MUX_trg5_w     /*!<  ITR6 signal from URT1_TMO.    */
#define APB_ITR6_URT2_BRO           APB_CR2_ITR6_MUX_trg6_w     /*!<  ITR6 signal from URT2_BRO.    */
#define APB_ITR6_URT2_TMO           APB_CR2_ITR6_MUX_trg7_w     /*!<  ITR6 signal from URT2_TMO.    */
///@}

/**
 * @name	APB_ITR7_MUX
 *   		ITR7 source configuration
 */ 
///@{  
#define APB_ITR7_TM01_TRGO          APB_CR2_ITR7_MUX_trg0_w     /*!<  ITR7 signal from TM01_TRGO.   */
#define APB_ITR7_TM16_TRGO          APB_CR2_ITR7_MUX_trg1_w     /*!<  ITR7 signal from TM16_TRGO.   */
#define APB_ITR7_TM26_TRGO          APB_CR2_ITR7_MUX_trg2_w     /*!<  ITR7 signal from TM26_TRGO.   */
#define APB_ITR7_ADC0_OUT           APB_CR2_ITR7_MUX_trg3_w     /*!<  ITR7 signal from ADC0_OUT.    */
#define APB_ITR7_INT_PD             APB_CR2_ITR7_MUX_trg4_w     /*!<  ITR7 signal from INT_PD.      */
#define APB_ITR7_URT1_BRO           APB_CR2_ITR7_MUX_trg5_w     /*!<  ITR7 signal from URT1_BRO.    */
#define APB_ITR7_URT3_BRO           APB_CR2_ITR7_MUX_trg6_w     /*!<  ITR7 signal from URT3_BRO.    */
#define APB_ITR7_URT3_TMO           APB_CR2_ITR7_MUX_trg7_w     /*!<  ITR7 signal from URT3_TMO.    */
#define APB_ITR7_ICKO               APB_CR2_ITR7_MUX_trg8_w     /*!<  ITR7 signal from ICKO.        */
#define APB_ITR7_RTC_OUT            APB_CR2_ITR7_MUX_trg9_w     /*!<  ITR7 signal from RTC_OUT.     */
#define APB_ITR7_TM36_XOR           APB_CR2_ITR7_MUX_trg10_w    /*!<  ITR7 signal from TM36_XOR.    */
#define APB_ITR7_NCO_P0             APB_CR2_ITR7_MUX_trg11_w    /*!<  ITR7 signal from NCO_P0.      */
///@}
#endif

#if defined(MG32_4TH)
/**
 * @name	APB_ITR6_MUX
 *   		ITR6 source configuration
 */ 
///@{  
#define APB_ITR6_TM00_TRGO          APB_CR2_ITR6_MUX_trg0_w     /*!<  ITR6 signal from TM00_TRGO.   */
#define APB_ITR6_TM10_TRGO          APB_CR2_ITR6_MUX_trg1_w     /*!<  ITR6 signal from TM10_TRGO.   */
#define APB_ITR6_TM20_TRGO          APB_CR2_ITR6_MUX_trg2_w     /*!<  ITR6 signal from TM20_TRGO.   */
#define APB_ITR6_TM36_TRGO          APB_CR2_ITR6_MUX_trg3_w     /*!<  ITR6 signal from TM36_TRGO.   */
#define APB_ITR6_INT_PB             APB_CR2_ITR6_MUX_trg4_w     /*!<  ITR6 signal from INT_PB.      */
#define APB_ITR6_URT1_TMO           APB_CR2_ITR6_MUX_trg5_w     /*!<  ITR6 signal from URT1_TMO.    */
///@}

/**
 * @name	APB_ITR7_MUX
 *   		ITR7 source configuration
 */ 
///@{  
#define APB_ITR7_TM01_TRGO          APB_CR2_ITR7_MUX_trg0_w     /*!<  ITR7 signal from TM01_TRGO.   */
#define APB_ITR7_TM16_TRGO          APB_CR2_ITR7_MUX_trg1_w     /*!<  ITR7 signal from TM16_TRGO.   */
#define APB_ITR7_ADC0_OUT           APB_CR2_ITR7_MUX_trg3_w     /*!<  ITR7 signal from ADC0_OUT.    */
#define APB_ITR7_INT_PD             APB_CR2_ITR7_MUX_trg4_w     /*!<  ITR7 signal from INT_PD.      */
#define APB_ITR7_URT1_BRO           APB_CR2_ITR7_MUX_trg5_w     /*!<  ITR7 signal from URT1_BRO.    */
#define APB_ITR7_ICKO               APB_CR2_ITR7_MUX_trg8_w     /*!<  ITR7 signal from ICKO.        */
#define APB_ITR7_RTC_OUT            APB_CR2_ITR7_MUX_trg9_w     /*!<  ITR7 signal from RTC_OUT.     */
#define APB_ITR7_TM36_XOR           APB_CR2_ITR7_MUX_trg10_w    /*!<  ITR7 signal from TM36_XOR.    */
#define APB_ITR7_NCO_P0             APB_CR2_ITR7_MUX_trg11_w    /*!<  ITR7 signal from NCO_P0.      */
///@}
#endif


/**
 * @name	APB_Interrupt_definition
 *   		APB Interrupt Definition
 */ 
///@{  
#if !defined(MG32_1ST)
#define APB_IT_OBM0                 APB_INT_OBM0_IE_enable_w    /*!< OBM0 interrupt.    */
#endif                  
#define APB_IT_OBM1                 APB_INT_OBM1_IE_enable_w    /*!< OBM1 interrupt.    */
#if defined(MG32_3RD) || defined(MG32_4TH)
#define APB_IT_NCO                  APB_INT_NCO0_IE_enable_w    /*!< NCO interrupt.     */
#endif
///@}                                                       


/**
 * @name	APB_Flag_definition
 *   		APB Flag Definition
 */ 
///@{  
#if defined(MG32_1ST)
#define APB_FLAG_OBM1               APB_STA_OBM1F_happened_w    /*!< OBM1 flag. */
#endif                                                          
#if defined(MG32_2ND)
#define APB_FLAG_OBM0               APB_STA_OBM0F_happened_w    /*!< OBM0 flag. */
#define APB_FLAG_OBM1               APB_STA_OBM1F_happened_w    /*!< OBM1 flag. */
#endif                                                          
#if defined(MG32_3RD) || defined(MG32_4TH)
#define APB_FLAG_OBM0               APB_STA_OBM0F_happened_w    /*!< OBM0 flag. */
#define APB_FLAG_OBM1               APB_STA_OBM1F_happened_w    /*!< OBM1 flag. */
#define APB_FLAG_NCO                APB_STA_NCO0F_happened_w    /*!< NCO flag.  */
#endif
///@}


#if defined(MG32_1ST)
/**
 * @name    APB_OBMx_BKS0Def
 *          OBMx APB_BKS0 source
 */ 
///@{  
#define APB_BKS0_LOGIC_1            APB_OBM10_OBM1_BKS0_bk0_w   /*!< Output '1' state.          */
#define APB_BKS0_ADC0_OUT           APB_OBM10_OBM1_BKS0_bk3_w   /*!< ADC0_OUT signal state.     */
#define APB_BKS0_TM00_TRGO          APB_OBM10_OBM1_BKS0_bk4_w   /*!< TM00's TRGO signal.        */
#define APB_BKS0_TM10_TRGO          APB_OBM10_OBM1_BKS0_bk5_w   /*!< TM10's TRGO signal.        */
#define APB_BKS0_TM20_OC00          APB_OBM10_OBM1_BKS0_bk8_w   /*!< TM20's OC00 output state . */
#define APB_BKS0_TM36_OC2           APB_OBM10_OBM1_BKS0_bk9_w   /*!< TM36's OC2 output state.   */
#define APB_BKS0_CMP0_OUT           APB_OBM10_OBM1_BKS0_bk10_w  /*!< CMP0's output state .      */
#define APB_BKS0_URT0_TX            APB_OBM10_OBM1_BKS0_bk12_w  /*!< URT0's TX signal.          */
#define APB_BKS0_URT2_TX            APB_OBM10_OBM1_BKS0_bk13_w  /*!< URT2's TX signal.          */
#define APB_BKS0_URT0_RX            APB_OBM10_OBM1_BKS0_bk14_w  /*!< URT0's RX signal.          */
#define APB_BKS0_URT2_RX            APB_OBM10_OBM1_BKS0_bk15_w  /*!< URT2's RX signal.          */
///@}

/**
 * @name    APB_OBMx_BKS1Def
 *          OBMx APB_BKS1 source
 */ 
///@{  
#define APB_BKS1_LOGIC_1            APB_OBM10_OBM1_BKS1_bk0_w   /*!< Output '1' state.          */
#define APB_BKS1_TM01_TRGO          APB_OBM10_OBM1_BKS1_bk4_w   /*!< TM01's TRGO signal.        */
#define APB_BKS1_TM26_TRGO          APB_OBM10_OBM1_BKS1_bk6_w   /*!< TM26's TRGO signal.        */
#define APB_BKS1_TM20_OC10          APB_OBM10_OBM1_BKS1_bk8_w   /*!< TM20's OC10 output state . */
#define APB_BKS1_TM36_OC3           APB_OBM10_OBM1_BKS1_bk9_w   /*!< TM36's OC3 output state.   */
#define APB_BKS1_CMP1_OUT           APB_OBM10_OBM1_BKS1_bk10_w  /*!< CMP1's output state .      */
#define APB_BKS1_URT1_TX            APB_OBM10_OBM1_BKS1_bk12_w  /*!< URT1's TX signal.          */
#define APB_BKS1_URT3_TX            APB_OBM10_OBM1_BKS1_bk13_w  /*!< URT3's TX signal.          */
#define APB_BKS1_URT1_RX            APB_OBM10_OBM1_BKS1_bk14_w  /*!< URT1's RX signal.          */
#define APB_BKS1_URT3_RX            APB_OBM10_OBM1_BKS1_bk15_w  /*!< URT3's RX signal.          */
///@}

/**
 * @name    APB_OBMx_BKS2Def
 *          OBMx APB_BKS2 source
 */ 
///@{  
#define APB_BKS2_LOGIC_1            APB_OBM10_OBM1_BKS2_bk0_w   /*!< Output '1' state.          */
#define APB_BKS2_SPI0_MOSI          APB_OBM10_OBM1_BKS2_bk3_w   /*!< SPI0's MOSI output state.  */
#define APB_BKS2_TM36_TRGO          APB_OBM10_OBM1_BKS2_bk6_w   /*!< TM36's TRGO signal.        */
#define APB_BKS2_CMP2_OUT           APB_OBM10_OBM1_BKS2_bk10_w  /*!< CMP2's output state .      */
#define APB_BKS2_CMP3_OUT           APB_OBM10_OBM1_BKS2_bk11_w  /*!< CMP3's output state .      */
#define APB_BKS2_URT2_BRO           APB_OBM10_OBM1_BKS2_bk12_w  /*!< URT2's BRO signal.         */
#define APB_BKS2_URT2_TMO           APB_OBM10_OBM1_BKS2_bk13_w  /*!< URT2's TMO signal.         */
#define APB_BKS2_URT3_BRO           APB_OBM10_OBM1_BKS2_bk14_w  /*!< URT3's BRO signal.         */
#define APB_BKS2_URT3_TMO           APB_OBM10_OBM1_BKS2_bk15_w  /*!< URT3's TM0 signal.         */
///@}
#endif    

#if defined(MG32_2ND)
/**
 * @name    APB_OBMx_BKS0Def
 *          OBMx APB_BKS0 source
 */ 
///@{  
#define APB_BKS0_LOGIC_1            APB_OBM10_OBM1_BKS0_bk0_w   /*!< Output '1' state.          */
#define APB_BKS0_INT_PA             APB_OBM10_OBM1_BKS0_bk1_w   /*!< INT_PA signal state.       */
#define APB_BKS0_INT_PC             APB_OBM10_OBM1_BKS0_bk2_w   /*!< INT_PC signal state.       */
#define APB_BKS0_ADC0_OUT           APB_OBM10_OBM1_BKS0_bk3_w   /*!< ADC0_OUT signal state.     */
#define APB_BKS0_TM00_TRGO          APB_OBM10_OBM1_BKS0_bk4_w   /*!< TM00's TRGO signal.        */
#define APB_BKS0_TM10_TRGO          APB_OBM10_OBM1_BKS0_bk5_w   /*!< TM10's TRGO signal.        */
#define APB_BKS0_TM36_OC2           APB_OBM10_OBM1_BKS0_bk9_w   /*!< TM36's OC2 output state.   */
#define APB_BKS0_CMP0_OUT           APB_OBM10_OBM1_BKS0_bk10_w  /*!< CMP0's output state .      */
#define APB_BKS0_URT0_TX            APB_OBM10_OBM1_BKS0_bk12_w  /*!< URT0's TX signal.          */
#define APB_BKS0_URT0_RX            APB_OBM10_OBM1_BKS0_bk14_w  /*!< URT0's RX signal.          */
///@}

/**
 * @name    APB_OBMx_BKS1Def
 *          OBMx APB_BKS1 source
 */ 
///@{  
#define APB_BKS1_LOGIC_1            APB_OBM10_OBM1_BKS1_bk0_w   /*!< Output '1' state.          */
#define APB_BKS1_INT_PB             APB_OBM10_OBM1_BKS1_bk1_w   /*!< INT_PB signal state.       */
#define APB_BKS1_INT_PD             APB_OBM10_OBM1_BKS1_bk2_w   /*!< INT_PD signal state.       */
#define APB_BKS1_INT_BOD1           APB_OBM10_OBM1_BKS1_bk3_w   /*!< BOD1 signal state.         */
#define APB_BKS1_TM01_TRGO          APB_OBM10_OBM1_BKS1_bk4_w   /*!< TM01's TRGO signal.        */
#define APB_BKS1_TM16_TRGO          APB_OBM10_OBM1_BKS1_bk5_w   /*!< TM16's TRGO signal.        */
#define APB_BKS1_TM36_OC3           APB_OBM10_OBM1_BKS1_bk9_w   /*!< TM36's OC3 output state.   */
#define APB_BKS1_CMP1_OUT           APB_OBM10_OBM1_BKS1_bk10_w  /*!< CMP1's output state .      */
#define APB_BKS1_URT1_TX            APB_OBM10_OBM1_BKS1_bk12_w  /*!< URT1's TX signal.          */
#define APB_BKS1_URT1_RX            APB_OBM10_OBM1_BKS1_bk14_w  /*!< URT1's RX signal.          */
///@}

/**
 * @name    APB_OBMx_BKS2Def
 *          OBMx APB_BKS2 source
 */ 
///@{  
#define APB_BKS2_LOGIC_1            APB_OBM10_OBM1_BKS2_bk0_w   /*!< Output '1' state.          */
#define APB_BKS2_SPI0_MOSI          APB_OBM10_OBM1_BKS2_bk3_w   /*!< SPI0's MOSI output state.  */
#define APB_BKS2_TM36_TRGO          APB_OBM10_OBM1_BKS2_bk6_w   /*!< TM36's TRGO signal.        */
///@}
#endif   

#if defined(MG32_3RD)
/**
 * @name    APB_OBMx_BKS0Def
 *          OBMx APB_BKS0 source
 */ 
///@{  
#define APB_BKS0_LOGIC_1            APB_OBM10_OBM1_BKS0_bk0_w   /*!< Output '1' state.          */
#define APB_BKS0_INT_PA             APB_OBM10_OBM1_BKS0_bk1_w   /*!< INT_PA signal state.       */
#define APB_BKS0_INT_PC             APB_OBM10_OBM1_BKS0_bk2_w   /*!< INT_PC signal state.       */
#define APB_BKS0_ADC0_OUT           APB_OBM10_OBM1_BKS0_bk3_w   /*!< ADC0_OUT signal state.     */
#define APB_BKS0_TM00_TRGO          APB_OBM10_OBM1_BKS0_bk4_w   /*!< TM00's TRGO signal.        */
#define APB_BKS0_TM10_TRGO          APB_OBM10_OBM1_BKS0_bk5_w   /*!< TM10's TRGO signal.        */
#define APB_BKS0_TM20_TRGO          APB_OBM10_OBM1_BKS0_bk6_w   /*!< TM20's TRGO output state . */
#define APB_BKS0_CCL_P0             APB_OBM10_OBM1_BKS0_bk7_w   /*!< CCL_P0 output state.       */
#define APB_BKS0_TM20_OC00          APB_OBM10_OBM1_BKS0_bk8_w   /*!< TM20's OC00 output state . */
#define APB_BKS0_TM36_OC2           APB_OBM10_OBM1_BKS0_bk9_w   /*!< TM36's OC2 output state.   */
#define APB_BKS0_CMP0_OUT           APB_OBM10_OBM1_BKS0_bk10_w  /*!< CMP0's output state.       */
#define APB_BKS0_URT0_TX            APB_OBM10_OBM1_BKS0_bk12_w  /*!< URT0's TX signal.          */
#define APB_BKS0_URT2_TX            APB_OBM10_OBM1_BKS0_bk13_w  /*!< URT2's TX signal.          */
#define APB_BKS0_URT0_RX            APB_OBM10_OBM1_BKS0_bk14_w  /*!< URT0's RX signal.          */
#define APB_BKS0_URT2_RX            APB_OBM10_OBM1_BKS0_bk15_w  /*!< URT2's RX signal.          */
///@}

/**
 * @name    APB_OBMx_BKS1Def
 *          OBMx APB_BKS1 source
 */ 
///@{  
#define APB_BKS1_LOGIC_1            APB_OBM10_OBM1_BKS1_bk0_w   /*!< Output '1' state.          */
#define APB_BKS1_INT_PB             APB_OBM10_OBM1_BKS1_bk1_w   /*!< INT_PB signal state.       */
#define APB_BKS1_INT_PD             APB_OBM10_OBM1_BKS1_bk2_w   /*!< INT_PD signal state.       */
#define APB_BKS1_INT_BOD1           APB_OBM10_OBM1_BKS1_bk3_w   /*!< BOD1 signal state.         */
#define APB_BKS1_TM01_TRGO          APB_OBM10_OBM1_BKS1_bk4_w   /*!< TM01's TRGO signal.        */
#define APB_BKS1_TM16_TRGO          APB_OBM10_OBM1_BKS1_bk5_w   /*!< TM16's TRGO signal.        */
#define APB_BKS1_TM26_TRGO          APB_OBM10_OBM1_BKS1_bk6_w   /*!< TM26's TRGO signal.        */
#define APB_BKS1_CCL_P1             APB_OBM10_OBM1_BKS1_bk7_w   /*!< CCL_P1 output state.       */
#define APB_BKS1_TM20_OC10          APB_OBM10_OBM1_BKS1_bk8_w   /*!< TM20's OC10 output state . */
#define APB_BKS1_TM36_OC3           APB_OBM10_OBM1_BKS1_bk9_w   /*!< TM36's OC3 output state.   */
#define APB_BKS1_CMP1_OUT           APB_OBM10_OBM1_BKS1_bk10_w  /*!< CMP1's output state .      */
#define APB_BKS1_URT1_TX            APB_OBM10_OBM1_BKS1_bk12_w  /*!< URT1's TX signal.          */
#define APB_BKS1_URT1_RX            APB_OBM10_OBM1_BKS1_bk14_w  /*!< URT1's RX signal.          */
///@}

/**
 * @name    APB_OBMx_BKS2Def
 *          OBMx APB_BKS2 source
 */ 
///@{  
#define APB_BKS2_LOGIC_1            APB_OBM10_OBM1_BKS2_bk0_w   /*!< Output '1' state.          */
#define APB_BKS2_INT_PE             APB_OBM10_OBM1_BKS2_bk1_w   /*!< INT_PE signal state.       */
#define APB_BKS2_SPI0_MOSI          APB_OBM10_OBM1_BKS2_bk3_w   /*!< SPI0's MOSI output state.  */
#define APB_BKS2_TM36_TRGO          APB_OBM10_OBM1_BKS2_bk6_w   /*!< TM36's TRGO signal.        */
#define APB_BKS2_URT2_BRO           APB_OBM10_OBM1_BKS2_bk12_w  /*!< URT2's BRO signal.         */
#define APB_BKS2_URT2_TMO           APB_OBM10_OBM1_BKS2_bk13_w  /*!< URT2's TMO signal.         */
///@}
#endif    

#if defined(MG32_4TH)
/**
 * @name    APB_OBMx_BKS0Def
 *          OBMx APB_BKS0 source
 */ 
///@{  
#define APB_BKS0_LOGIC_1            APB_OBM10_OBM1_BKS0_bk0_w   /*!< Output '1' state.          */
#define APB_BKS0_INT_PA             APB_OBM10_OBM1_BKS0_bk1_w   /*!< INT_PA signal state.       */
#define APB_BKS0_INT_PC             APB_OBM10_OBM1_BKS0_bk2_w   /*!< INT_PC signal state.       */
#define APB_BKS0_ADC0_OUT           APB_OBM10_OBM1_BKS0_bk3_w   /*!< ADC0_OUT signal state.     */
#define APB_BKS0_TM00_TRGO          APB_OBM10_OBM1_BKS0_bk4_w   /*!< TM00's TRGO signal.        */
#define APB_BKS0_TM10_TRGO          APB_OBM10_OBM1_BKS0_bk5_w   /*!< TM10's TRGO signal.        */
#define APB_BKS0_TM20_TRGO          APB_OBM10_OBM1_BKS0_bk6_w   /*!< TM20's TRGO output state . */
#define APB_BKS0_CCL_P0             APB_OBM10_OBM1_BKS0_bk7_w   /*!< CCL_P0 output state.       */
#define APB_BKS0_TM20_OC00          APB_OBM10_OBM1_BKS0_bk8_w   /*!< TM20's OC00 output state . */
#define APB_BKS0_TM36_OC2           APB_OBM10_OBM1_BKS0_bk9_w   /*!< TM36's OC2 output state.   */
#define APB_BKS0_URT0_TX            APB_OBM10_OBM1_BKS0_bk12_w  /*!< URT0's TX signal.          */
#define APB_BKS0_URT0_RX            APB_OBM10_OBM1_BKS0_bk14_w  /*!< URT0's RX signal.          */
///@}

/**
 * @name    APB_OBMx_BKS1Def
 *          OBMx APB_BKS1 source
 */ 
///@{  
#define APB_BKS1_LOGIC_1            APB_OBM10_OBM1_BKS1_bk0_w   /*!< Output '1' state.          */
#define APB_BKS1_INT_PB             APB_OBM10_OBM1_BKS1_bk1_w   /*!< INT_PB signal state.       */
#define APB_BKS1_INT_PD             APB_OBM10_OBM1_BKS1_bk2_w   /*!< INT_PD signal state.       */
#define APB_BKS1_INT_BOD1           APB_OBM10_OBM1_BKS1_bk3_w   /*!< BOD1 signal state.         */
#define APB_BKS1_TM01_TRGO          APB_OBM10_OBM1_BKS1_bk4_w   /*!< TM01's TRGO signal.        */
#define APB_BKS1_TM16_TRGO          APB_OBM10_OBM1_BKS1_bk5_w   /*!< TM16's TRGO signal.        */
#define APB_BKS1_CCL_P1             APB_OBM10_OBM1_BKS1_bk7_w   /*!< CCL_P1 output state.       */
#define APB_BKS1_TM20_OC10          APB_OBM10_OBM1_BKS1_bk8_w   /*!< TM20's OC10 output state . */
#define APB_BKS1_TM36_OC3           APB_OBM10_OBM1_BKS1_bk9_w   /*!< TM36's OC3 output state.   */
#define APB_BKS1_URT1_TX            APB_OBM10_OBM1_BKS1_bk12_w  /*!< URT1's TX signal.          */
#define APB_BKS1_URT1_RX            APB_OBM10_OBM1_BKS1_bk14_w  /*!< URT1's RX signal.          */
///@}

/**
 * @name    APB_OBMx_BKS2Def
 *          OBMx APB_BKS2 source
 */ 
///@{  
#define APB_BKS2_LOGIC_1            APB_OBM10_OBM1_BKS2_bk0_w   /*!< Output '1' state.          */
#define APB_BKS2_SPI0_MOSI          APB_OBM10_OBM1_BKS2_bk3_w   /*!< SPI0's MOSI output state.  */
#define APB_BKS2_TM36_TRGO          APB_OBM10_OBM1_BKS2_bk6_w   /*!< TM36's TRGO signal.        */
///@}
#endif    
 



/**
 * @name    APB_OBMx_BKS0_Polarity
 *          APB OBMx BKS0 Polarity
 */ 
///@{  
#define APB_OBM_BKS0_HIGH           APB_OBM10_OBM1_BKN0_enable_w    /*!< Invert BKS0.   */
#define APB_OBM_BKS0_LOW            APB_OBM10_OBM1_BKN0_disable_w   /*!< Normal BKS0.   */
///@}

/**
 * @name    APB_OBMx_BKS1_Polarity
 *          APB OBMx BKS1 Polarity
 */ 
///@{  
#define APB_OBM_BKS1_HIGH           APB_OBM10_OBM1_BKN1_enable_w    /*!< Invert BKS1.   */
#define APB_OBM_BKS1_LOW            APB_OBM10_OBM1_BKN1_disable_w   /*!< Normal BKS1.   */
///@}

/**
 * @name    APB_OBMx_BKS2_Polarity
 *          APB OBMx BKS2 Polarity
 */ 
///@{  
#define APB_OBM_BKS2_HIGH           APB_OBM10_OBM1_BKN2_enable_w     /*!< Invert BKS2.  */
#define APB_OBM_BKS2_LOW            APB_OBM10_OBM1_BKN2_disable_w    /*!< Normal BKS2.  */
///@}


/**
 * @name    APB_Output_Channel0_Polarity
 *          APB Output Channel-0 Polarity
 */ 
///@{  
#define APB_OBM_CH0_HIGH            APB_OBM11_OBM1_INV0_enable_w    /*!< Invert Output MUX0.    */
#define APB_OBM_CH0_LOW             APB_OBM11_OBM1_INV0_disable_w   /*!< Normal Output MUX0.    */
///@}

/**
 * @name    APB_Output_Channel1_Polarity
 *          APB Output Channel-1 Polarity
 */ 
///@{  
#define APB_OBM_CH1_HIGH            APB_OBM11_OBM1_INV1_enable_w    /*!< Invert Output MUX1.    */
#define APB_OBM_CH1_LOW             APB_OBM11_OBM1_INV1_disable_w   /*!< Normal Output MUX1.    */
///@}

/**
 * @name    APB_Output_Pin_Polarity
 *          APB Output Pin Polarity
 */ 
///@{  
#define APB_OBM_PIN_HIGH            APB_OBM11_OBM1_POL_enable_w     /*!< Invert Output channel. */
#define APB_OBM_PIN_LOW             APB_OBM11_OBM1_POL_disable_w    /*!< Normal Output channel. */
///@}

/**
 * @name    APB_OBMx_InitialState_Def
 *          APB OBMx initial STA state definition
 */ 
///@{  
#define APB_OBM_INITSTA_HIGH        (APB_OBM10_OBM1_LCK_un_locked_w | APB_OBM10_OBM1_STA_1_w)   /*!< OBMx set switch initial state to 1.  */
#define APB_OBM_INITSTA_LOW         (APB_OBM10_OBM1_LCK_un_locked_w | APB_OBM10_OBM1_STA_0_w)   /*!< OBMx set switch initial state to 0.  */
///@}

#if defined(MG32_1ST)
/**
 * @name    APB_Output_Channel0_SrcDef
 *          OBMx Output channel0 source definition
 */ 
///@{  
#define APB_CH0_LOGIC_0             APB_OBM11_OBM1_MUX0_sr0_w   /*!< Output '1' state.          */
#define APB_CH0_INT_PA              APB_OBM11_OBM1_MUX0_sr1_w   /*!< INT_PA signal state.       */
#define APB_CH0_INT_PC              APB_OBM11_OBM1_MUX0_sr2_w   /*!< INT_PC signal state.       */
#define APB_CH0_TM00_CKO            APB_OBM11_OBM1_MUX0_sr4_w   /*!< TM00's CKO signal.         */
#define APB_CH0_TM10_CKO            APB_OBM11_OBM1_MUX0_sr5_w   /*!< TM10's CKO signal.         */
#define APB_CH0_TM20_CKO            APB_OBM11_OBM1_MUX0_sr6_w   /*!< TM10's CKO signal.         */
#define APB_CH0_TM36_CKO            APB_OBM11_OBM1_MUX0_sr7_w   /*!< TM36's CKO output state.   */
#define APB_CH0_TM20_OC00           APB_OBM11_OBM1_MUX0_sr8_w   /*!< TM20's OC00 output state.  */
#define APB_CH0_TM36_OC00           APB_OBM11_OBM1_MUX0_sr9_w   /*!< TM36's OC00 output state.  */
#define APB_CH0_TM36_OC2            APB_OBM11_OBM1_MUX0_sr10_w  /*!< TM36's OC2 output statel.  */
#define APB_CH0_OBM_I0              APB_OBM11_OBM1_MUX0_sr12_w  /*!< BOMx_I0 pin state.         */
#define APB_CH0_OBM_ITR6            APB_OBM11_OBM1_MUX0_sr13_w  /*!< ITR6 signal.               */
///@}   

/**
 * @name    APB_Output_Channel1_SrcDef
 *          OBMx Output channel1 source definition
 */ 
///@{  
#define APB_CH1_LOGIC_0             APB_OBM11_OBM1_MUX1_sr0_w   /*!< Output '1' state.          */
#define APB_CH1_INT_PB              APB_OBM11_OBM1_MUX1_sr1_w   /*!< INT_PB signal state.       */
#define APB_CH1_INT_PD              APB_OBM11_OBM1_MUX1_sr2_w   /*!< INT_PD signal state.       */
#define APB_CH1_TM01_CKO            APB_OBM11_OBM1_MUX1_sr4_w   /*!< TM01's CKO signal.         */
#define APB_CH1_TM16_CKO            APB_OBM11_OBM1_MUX1_sr5_w   /*!< TM16's CKO signal.         */
#define APB_CH1_TM26_CKO            APB_OBM11_OBM1_MUX1_sr6_w   /*!< TM26's CKO output state.  */
#define APB_CH1_TM20_OC01           APB_OBM11_OBM1_MUX1_sr8_w   /*!< TM20's OC01 output state.  */
#define APB_CH1_TM36_OC01           APB_OBM11_OBM1_MUX1_sr9_w   /*!< TM36's OC01 output state.  */
#define APB_CH1_TM36_OC3            APB_OBM11_OBM1_MUX1_sr10_w  /*!< TM36's OC3 output state .  */
#define APB_CH1_OBM_I1              APB_OBM11_OBM1_MUX1_sr12_w  /*!< BOMx_I1 pin state.         */
#define APB_CH1_OBM_ITR7            APB_OBM11_OBM1_MUX1_sr13_w  /*!< ITR7 signal.               */
#define APB_CH1_OBM_ICKO            APB_OBM11_OBM1_MUX1_sr14_w  /*!< ICKO signal.               */
///@}
#endif

#if defined(MG32_2ND)
/**
 * @name    APB_Output_Channel0_SrcDef
 *          OBMx Output channel0 source definition
 */ 
///@{  
#define APB_CH0_LOGIC_0             APB_OBM11_OBM1_MUX0_sr0_w   /*!< Output '1' state.          */
#define APB_CH0_INT_PA              APB_OBM11_OBM1_MUX0_sr1_w   /*!< INT_PA signal state.       */
#define APB_CH0_INT_PC              APB_OBM11_OBM1_MUX0_sr2_w   /*!< INT_PC signal state.       */
#define APB_CH0_TM00_CKO            APB_OBM11_OBM1_MUX0_sr4_w   /*!< TM00's CKO signal.         */
#define APB_CH0_TM10_CKO            APB_OBM11_OBM1_MUX0_sr5_w   /*!< TM10's CKO signal.         */
#define APB_CH0_TM36_CKO            APB_OBM11_OBM1_MUX0_sr7_w   /*!< TM36's CKO output state.   */
#define APB_CH0_TM36_OC00           APB_OBM11_OBM1_MUX0_sr9_w   /*!< TM36's OC00 output state.  */
#define APB_CH0_TM36_OC2            APB_OBM11_OBM1_MUX0_sr10_w  /*!< TM36's OC2 output statel.  */
#define APB_CH0_OBM_I0              APB_OBM11_OBM1_MUX0_sr12_w  /*!< BOMx_I0 pin state.         */
#define APB_CH0_OBM_ITR6            APB_OBM11_OBM1_MUX0_sr13_w  /*!< ITR6 signal.               */
///@}   

/**
 * @name    APB_Output_Channel1_SrcDef
 *          OBMx Output channel1 source definition
 */ 
///@{  
#define APB_CH1_LOGIC_0             APB_OBM11_OBM1_MUX1_sr0_w   /*!< Output '1' state.          */
#define APB_CH1_INT_PB              APB_OBM11_OBM1_MUX1_sr1_w   /*!< INT_PB signal state.       */
#define APB_CH1_INT_PD              APB_OBM11_OBM1_MUX1_sr2_w   /*!< INT_PD signal state.       */
#define APB_CH1_TM01_CKO            APB_OBM11_OBM1_MUX1_sr4_w   /*!< TM01's CKO signal.         */
#define APB_CH1_TM16_CKO            APB_OBM11_OBM1_MUX1_sr5_w   /*!< TM16's CKO signal.         */
#define APB_CH1_TM36_OC01           APB_OBM11_OBM1_MUX1_sr9_w   /*!< TM36's OC01 output state.  */
#define APB_CH1_TM36_OC3            APB_OBM11_OBM1_MUX1_sr10_w  /*!< TM36's OC3 output state .  */
#define APB_CH1_OBM_I1              APB_OBM11_OBM1_MUX1_sr12_w  /*!< BOMx_I1 pin state.         */
#define APB_CH1_OBM_ITR7            APB_OBM11_OBM1_MUX1_sr13_w  /*!< ITR7 signal.               */
#define APB_CH1_OBM_ICKO            APB_OBM11_OBM1_MUX1_sr14_w  /*!< ICKO signal.               */
///@}
#endif    
 
#if defined(MG32_3RD)
/**
 * @name    APB_Output_Channel0_SrcDef
 *          OBMx Output channel0 source definition
 */ 
///@{  
#define APB_CH0_LOGIC_0             APB_OBM11_OBM1_MUX0_sr0_w   /*!< Output '1' state.          */
#define APB_CH0_INT_PA              APB_OBM11_OBM1_MUX0_sr1_w   /*!< INT_PA signal state.       */
#define APB_CH0_INT_PC              APB_OBM11_OBM1_MUX0_sr2_w   /*!< INT_PC signal state.       */
#define APB_CH0_INT_PE              APB_OBM11_OBM1_MUX0_sr3_w   /*!< INT_PE signal state.       */
#define APB_CH0_TM00_CKO            APB_OBM11_OBM1_MUX0_sr4_w   /*!< TM00's CKO signal.         */
#define APB_CH0_TM10_CKO            APB_OBM11_OBM1_MUX0_sr5_w   /*!< TM10's CKO signal.         */
#define APB_CH0_TM20_CKO            APB_OBM11_OBM1_MUX0_sr6_w   /*!< TM10's CKO signal.         */
#define APB_CH0_TM36_CKO            APB_OBM11_OBM1_MUX0_sr7_w   /*!< TM36's CKO output state.   */
#define APB_CH0_TM20_OC00           APB_OBM11_OBM1_MUX0_sr8_w   /*!< TM20's OC00 output state.  */
#define APB_CH0_TM36_OC00           APB_OBM11_OBM1_MUX0_sr9_w   /*!< TM36's OC00 output state.  */
#define APB_CH0_TM36_OC2            APB_OBM11_OBM1_MUX0_sr10_w  /*!< TM36's OC2 output statel.  */
#define APB_CH0_OBM_I0              APB_OBM11_OBM1_MUX0_sr12_w  /*!< BOMx_I0 pin state.         */
#define APB_CH0_OBM_ITR6            APB_OBM11_OBM1_MUX0_sr13_w  /*!< ITR6 signal.               */
///@}   

/**
 * @name    APB_Output_Channel1_SrcDef
 *          OBMx Output channel1 source definition
 */ 
///@{  
#define APB_CH1_LOGIC_0             APB_OBM11_OBM1_MUX1_sr0_w   /*!< Output '1' state.          */
#define APB_CH1_INT_PB              APB_OBM11_OBM1_MUX1_sr1_w   /*!< INT_PB signal state.       */
#define APB_CH1_INT_PD              APB_OBM11_OBM1_MUX1_sr2_w   /*!< INT_PD signal state.       */
#define APB_CH1_TM01_CKO            APB_OBM11_OBM1_MUX1_sr4_w   /*!< TM01's CKO signal.         */
#define APB_CH1_TM16_CKO            APB_OBM11_OBM1_MUX1_sr5_w   /*!< TM16's CKO signal.         */
#define APB_CH1_TM26_CKO            APB_OBM11_OBM1_MUX1_sr6_w   /*!< TM26's CKO output state.  */
#define APB_CH1_TM20_OC01           APB_OBM11_OBM1_MUX1_sr8_w   /*!< TM20's OC01 output state.  */
#define APB_CH1_TM36_OC01           APB_OBM11_OBM1_MUX1_sr9_w   /*!< TM36's OC01 output state.  */
#define APB_CH1_TM36_OC3            APB_OBM11_OBM1_MUX1_sr10_w  /*!< TM36's OC3 output state .  */
#define APB_CH1_OBM_I1              APB_OBM11_OBM1_MUX1_sr12_w  /*!< BOMx_I1 pin state.         */
#define APB_CH1_OBM_ITR7            APB_OBM11_OBM1_MUX1_sr13_w  /*!< ITR7 signal.               */
#define APB_CH1_OBM_ICKO            APB_OBM11_OBM1_MUX1_sr14_w  /*!< ICKO signal.               */
///@}
#endif    

#if defined(MG32_4TH)
/**
 * @name    APB_Output_Channel0_SrcDef
 *          OBMx Output channel0 source definition
 */ 
///@{  
#define APB_CH0_LOGIC_0             APB_OBM11_OBM1_MUX0_sr0_w   /*!< Output '1' state.          */
#define APB_CH0_INT_PA              APB_OBM11_OBM1_MUX0_sr1_w   /*!< INT_PA signal state.       */
#define APB_CH0_INT_PC              APB_OBM11_OBM1_MUX0_sr2_w   /*!< INT_PC signal state.       */
#define APB_CH0_TM00_CKO            APB_OBM11_OBM1_MUX0_sr4_w   /*!< TM00's CKO signal.         */
#define APB_CH0_TM10_CKO            APB_OBM11_OBM1_MUX0_sr5_w   /*!< TM10's CKO signal.         */
#define APB_CH0_TM20_CKO            APB_OBM11_OBM1_MUX0_sr6_w   /*!< TM10's CKO signal.         */
#define APB_CH0_TM36_CKO            APB_OBM11_OBM1_MUX0_sr7_w   /*!< TM36's CKO output state.   */
#define APB_CH0_TM20_OC00           APB_OBM11_OBM1_MUX0_sr8_w   /*!< TM20's OC00 output state.  */
#define APB_CH0_TM36_OC00           APB_OBM11_OBM1_MUX0_sr9_w   /*!< TM36's OC00 output state.  */
#define APB_CH0_TM36_OC2            APB_OBM11_OBM1_MUX0_sr10_w  /*!< TM36's OC2 output statel.  */
#define APB_CH0_OBM_I0              APB_OBM11_OBM1_MUX0_sr12_w  /*!< BOMx_I0 pin state.         */
#define APB_CH0_OBM_ITR6            APB_OBM11_OBM1_MUX0_sr13_w  /*!< ITR6 signal.               */
///@}   

/**
 * @name    APB_Output_Channel1_SrcDef
 *          OBMx Output channel1 source definition
 */ 
///@{  
#define APB_CH1_LOGIC_0             APB_OBM11_OBM1_MUX1_sr0_w   /*!< Output '1' state.          */
#define APB_CH1_INT_PB              APB_OBM11_OBM1_MUX1_sr1_w   /*!< INT_PB signal state.       */
#define APB_CH1_INT_PD              APB_OBM11_OBM1_MUX1_sr2_w   /*!< INT_PD signal state.       */
#define APB_CH1_TM01_CKO            APB_OBM11_OBM1_MUX1_sr4_w   /*!< TM01's CKO signal.         */
#define APB_CH1_TM16_CKO            APB_OBM11_OBM1_MUX1_sr5_w   /*!< TM16's CKO signal.         */
#define APB_CH1_TM20_OC01           APB_OBM11_OBM1_MUX1_sr8_w   /*!< TM20's OC01 output state.  */
#define APB_CH1_TM36_OC01           APB_OBM11_OBM1_MUX1_sr9_w   /*!< TM36's OC01 output state.  */
#define APB_CH1_TM36_OC3            APB_OBM11_OBM1_MUX1_sr10_w  /*!< TM36's OC3 output state .  */
#define APB_CH1_OBM_I1              APB_OBM11_OBM1_MUX1_sr12_w  /*!< BOMx_I1 pin state.         */
#define APB_CH1_OBM_ITR7            APB_OBM11_OBM1_MUX1_sr13_w  /*!< ITR7 signal.               */
#define APB_CH1_OBM_ICKO            APB_OBM11_OBM1_MUX1_sr14_w  /*!< ICKO signal.               */
///@}
#endif    


/**
 * @name    APB_OBMx_OP_ModeDef
 *          APB OBMx operation mode definition
 */ 
///@{  
#define APB_OBM_AND                 APB_OBM10_OBM1_MDS_and_w        /*!< AND signal of all break channels' output.          */
#define APB_OBM_CLR                 APB_OBM10_OBM1_MDS_clr_w        /*!< STA bit is cleared by falling edge of OR signal.   */
#define APB_OBM_SET                 APB_OBM10_OBM1_MDS_set_w        /*!< STA bit is set by falling edge of OR signal.       */
#define APB_OBM_TOGGLE              APB_OBM10_OBM1_MDS_toggle_w     /*!< STA bit is toggle by falling edge of OR signal.    */
///@}

/**
 * @name    OBMx_OutputSynchronizeFilter
 *          OBMx Output Synchronize Filter
 */ 
//!@{
#define OBM_SYNCHRONIZE_BYPASS      APB_OBM11_OBM1_FCKS_disable_w   /*!< Bypass : Disable Synchronize.                      */
#define OBM_SYNCHRONIZE_APBCLK      APB_OBM11_OBM1_FCKS_apb_w       /*!< Synchronize Filter clock from APB clock.           */
#define OBM_SYNCHRONIZE_APBCLK_DIV8 APB_OBM11_OBM1_FCKS_apb_div8_w  /*!< Synchronize Filter clock from (APB clock)/8.       */
#define OBM_SYNCHRONIZE_TM00TRGO    APB_OBM11_OBM1_FCKS_tm00_trgo_w /*!< Synchronize Filter clock from TM01_TRGO.           */
//!@}


/**
 * @name    APB_IRDAT_MuxDef
 *          APB IR data mux definition
 */ 
///@{  
#define APB_IRDAT0_LOW              APB_CR0_IRDAT_MUX_dat0_w    /*!< IRDAT_MUX select 0.            */
#define APB_IRDAT1_TM20_TRGO        APB_CR0_IRDAT_MUX_dat1_w    /*!< IRDAT_MUX select TM20_TRGO.    */
#if defined(MG32_1ST) || defined(MG32_3RD) || defined(MG32_4TH)
#define APB_IRDAT2_TM26_TRGO        APB_CR0_IRDAT_MUX_dat2_w    /*!< IRDAT_MUX select TM26_TRGO.    */
#endif
#define APB_IRDAT3_TM36_TRGO        APB_CR0_IRDAT_MUX_dat3_w    /*!< IRDAT_MUX select TM36_TRGO.    */
#define APB_IRDAT4_SPI0_MOSI        APB_CR0_IRDAT_MUX_dat4_w    /*!< IRDAT_MUX select SPI0_MOSI.    */
#define APB_IRDAT5_URT1_TX          APB_CR0_IRDAT_MUX_dat5_w    /*!< IRDAT_MUX select URT1_TX.      */
#if defined(MG32_1ST) || defined(MG32_2ND) || defined(MG32_3RD)
#define APB_IRDAT6_URT2_TX          APB_CR0_IRDAT_MUX_dat6_w    /*!< IRDAT_MUX select URT2_TX.      */
#endif
#if defined(MG32_1ST)
#define APB_IRDAT7_URT3_TX          APB_CR0_IRDAT_MUX_dat7_w    /*!< IRDAT_MUX select URT3_TX.      */
#endif
///@}


/**
 * @name    APB_IRDAT_Invert_Polarity
 *          APB IRDAT invert polarity
 */ 
///@{  
#define APB_IRDAT_INV               APB_CR0_IRDAT_INV_enable_w  /*!< Invert Output of IRDAT.        */
#define APB_IRDAT_NOINV             APB_CR0_IRDAT_INV_disable_w /*!< Normal Output of IRDAT.        */
///@}


/**
 * @name    APB_IRCLK_MuxDef
 *          APB IR clock mux definition
 */ 
///@{  
#define APB_IRCLK0_LOW              APB_CR0_IRCLK_MUX_clk0_w    /*!< IRCLK_MUX select 0.            */
#define APB_IRCLK1_TM00_CKO         APB_CR0_IRCLK_MUX_clk1_w    /*!< IRCLK_MUX select TM00_CKO.     */
#define APB_IRCLK2_TM01_CKO         APB_CR0_IRCLK_MUX_clk2_w    /*!< IRCLK_MUX select TM01_CKO.     */
#define APB_IRCLK3_TM10_CKO         APB_CR0_IRCLK_MUX_clk3_w    /*!< IRCLK_MUX select TM10_CKO.     */
#define APB_IRCLK4_TM16_TRGO        APB_CR0_IRCLK_MUX_clk4_w    /*!< IRCLK_MUX select TM16_TRGO.    */
#define APB_IRCLK5_URT1_TMO         APB_CR0_IRCLK_MUX_clk5_w    /*!< IRCLK_MUX select URT1_TMO.     */
#if defined(MG32_1ST) || defined(MG32_2ND) || defined(MG32_3RD)
#define APB_IRCLK6_URT2_TMO         APB_CR0_IRCLK_MUX_clk6_w    /*!< IRCLK_MUX select URT2_TMO.     */
#endif
#if defined(MG32_1ST)
#define APB_IRCLK7_URT3_TMO         APB_CR0_IRCLK_MUX_clk7_w    /*!< IRCLK_MUX select URT3_TMO.     */
#endif
///@}

/**
 * @name    OBM_SwitchSignalStatus
 *          OBM switch signal status
 */ 
//!@{
#define OBM_SWITCHSTATUS_LOW        (0x00000000U)               /*!< OBM switch signal status is 'Low'.     */
#define OBM_SWITCHSTATUS_HIGH       (0x00000001U)               /*!< OBM switch signal status is 'High'.    */
//!@}

/**
 * @name    APB_IRCLK_Invert_Polarity
 *          APB IRCLK invert polarity
 */ 
///@{  
#define APB_IRCLK_INV               APB_CR0_IRCLK_INV_enable_w  /*!< Invert Output of IRCLK.    */
#define APB_IRCLK_NOINV             APB_CR0_IRCLK_INV_disable_w /*!< Normal Output of IRCLK.    */
///@}


/** 
 * @enum        MID_APB_StateTypeDef
 * @brief       MID APB State definition 
 */        
typedef enum 
{
    MID_APB_STATE_RESET             = (0x00000000U),   /*!< APB not yet initialized or disabled.             */
    MID_APB_STATE_READY             = (0x00000001U),   /*!< APB initialized and ready for use.               */
    MID_APB_STATE_READY_LOCKED      = (0x00000011U),   /*!< APB initialized but the configuration is locked. */
    MID_APB_STATE_BUSY              = (0x00000002U),   /*!< APB is running.                                  */
    MID_APB_STATE_BUSY_LOCKED       = (0x00000012U)    /*!< APB is running and the configuration is locked.  */
} MID_APB_StateTypeDef;


/** 
 * @struct  APB_OBMxInitStructDef
 * @brief   Structure definition of OBM initialization and regular group
 */        
typedef struct __attribute__((packed))
{ 
    uint32_t OBMxMode;                  /*!< Select APB OBMx operation mode.
                                            This parameter can be a value of reference APB_OBMx_OP_ModeDef. */

    uint32_t BKS0Src;                   /*!< Select APB OBMx Break Source 0 input .
                                            This parameter can be a value of reference APB_OBMx_BKS0Def. */
                
    uint32_t BKS0Polarity;              /*!< Specifies the output polarity.
                                            This parameter can be a value of reference APB_OBMx_BKS0_Polarity */
            
    uint32_t BKS1Src;                   /*!< Select APB OBMx Break Source 0 input .
                                            This parameter can be a value of reference APB_OBMx_BKS1Def. */
                
    uint32_t BKS1Polarity;              /*!< Specifies the output polarity.
                                            This parameter can be a value of reference APB_OBMx_BKS1_Polarity */
            
    uint32_t BKS2Src;                   /*!< Select APB OBMx Break Source 0 input .
                                            This parameter can be a value of reference APB_OBMx_BKS2Def. */
                
    uint32_t BKS2Polarity;              /*!< Specifies the output polarity.
                                            This parameter can be a value of reference APB_OBMx_BKS2_Polarity */
            
    uint32_t OutChannel0Src;            /*!< Select APB OBMx Output channel-0 Source 0 input .
                                            This parameter can be a value of reference APB_Output_Channel0_SrcDef. */
                
    uint32_t OutChannel0Polarity;       /*!< Specifies the output polarity.
                                            This parameter can be a value of reference APB_Output_Channel0_Polarity */
            
    uint32_t OutChannel1Src;            /*!< Select APB OBMx Output channel-0 Source 0 input .
                                            This parameter can be a value of reference APB_Output_Channel1_SrcDef. */
                
    uint32_t OutChannel1Polarity;       /*!< Specifies the output polarity.
                                            This parameter can be a value of reference APB_Output_Channel1_Polarity */
            
    uint32_t OBMxOutPolarity;           /*!< Specifies the output polarity.
                                            This parameter can be a value of reference APB_Output_Pin_Polarity */

    uint32_t SyncFilter;                /*!< Analog OBMx output synchronized filter divider.
                                            This parameter can be a value of reference OBMx_OutputSynchronizeFilter. */
                                       
    uint32_t InitSTAState;              /*!< Analog OBMx Initial state.
                                            This parameter can be a value of reference APB_OBMx_InitialState_Def. */
                                       
} APB_OBMxInitStructDef;


/** 
 * @struct  MID_OBMx_HandleTypeDef
 * @brief   OBMx Handler typedef definition
 */        
typedef struct __attribute__((packed))
{ 
    OBM_Struct              *Instance;  /*!< Register base address. e.g OBM1 */
        
    APB_OBMxInitStructDef   Init;       /*!< TM Time Base required parameters */
        
    MID_LockTypeDef         Lock;       /*!< Locking object */
        
    MID_APB_StateTypeDef    State;      /*!< APB operation state  */
    
} MID_OBMx_HandleTypeDef;

/**
 * @name    OBM_OutputLevel
 *          OBM Output Level
 */ 
//!@{
#define OBM_OUTPUTLEVEL_LOW             (0x00000000U)               /*!< OBMx output '0' state. */
#define OBM_OUTPUTLEVEL_HIGH            (0x00000001U)               /*!< OBMx output '1' state. */
//!@}


#if defined(MG32_3RD) || defined(MG32_4TH)

/**
 * @name    NCO_OutputLevel
 *          NCO Output Level
 */ 
//!@{
#define NCO_OUTPUTLEVEL_LOW             (0x00000000U)               /*!< NCO output '0' state.  */
#define NCO_OUTPUTLEVEL_HIGH            (0x00000001U)               /*!< NCO output '1' state.  */
//!@}

/**
 * @name    NCO_Clock_Source
 *          NCO clock source
 */ 
//!@{
#define NCO_CLOCK_IHRCO                 APB_NCO00_NCO0_CKS_ck_ihrco_w   /*!< NCO clock from CK_IHRCO.       */
#define NCO_CLOCK_PLL                   APB_NCO00_NCO0_CKS_ck_pll_w     /*!< NCO clock from CK_PLL.         */
#define NCO_CLOCK_APB                   APB_NCO00_NCO0_CKS_ck_apb_w     /*!< NCO clock from CK_APB.         */
#define NCO_CLOCK_LS                    APB_NCO00_NCO0_CKS_ck_ls_w      /*!< NCO clock from CK_LS.          */
#define NCO_CLOCK_TM00_TRGO             APB_NCO00_NCO0_CKS_tm00_trgo_w  /*!< NCO clock from TM00_TRGO.      */
#define NCO_CLOCK_NCO_CK0               APB_NCO00_NCO0_CKS_nco_ck0_w    /*!< NCO clock from NCO_CK0 pin.    */
//!@}

/**
 * @name    NCO_OutputModeLevel
 *          NCO Output Mode
 */ 
//!@{
#define NCO_OUTPUT_FDC                  (0x00000000U)                   /*!< FDC : fixed duty cycle mode.   */
#define NCO_OUTPUT_PFM                  APB_NCO00_NCO0_MDS_pfm_w        /*!< PFM : pulse frequency mode.    */
//!@}

/**
 * @name    NCO_OutputPolarity
 *          NCO OutputPolarity
 */ 
//!@{
#define NCO_OUTPUTPOL_NONINVERTED       (0x00000000U)                   /*!< NCO output on GPIO isn't inverted. */
#define NCO_OUTPUTPOL_INVERTED          APB_NCO00_NCO0_INV_enable_w     /*!< NCO output on GPIO is inverted.    */
//!@}

/**
 * @name    NCO_PFM_Width_Sel
 *          NCO PFM mode output pulse width select.
 */ 
//!@{
#define NCO_PFM_WIDTH_1CLOCK            APB_NCO01_NCO0_PWS_ck1_w        /*!< 1 CK_NCOn clock period.    */
#define NCO_PFM_WIDTH_2CLOCK            APB_NCO01_NCO0_PWS_ck2_w        /*!< 2 CK_NCOn clock period.    */
#define NCO_PFM_WIDTH_4CLOCK            APB_NCO01_NCO0_PWS_ck4_w        /*!< 4 CK_NCOn clock period.    */
#define NCO_PFM_WIDTH_8CLOCK            APB_NCO01_NCO0_PWS_ck8_w        /*!< 8 CK_NCOn clock period.    */
#define NCO_PFM_WIDTH_16CLOCK           APB_NCO01_NCO0_PWS_ck16_w       /*!< 16 CK_NCOn clock period.   */
#define NCO_PFM_WIDTH_32CLOCK           APB_NCO01_NCO0_PWS_ck32_w       /*!< 32 CK_NCOn clock period.   */
#define NCO_PFM_WIDTH_64CLOCK           APB_NCO01_NCO0_PWS_ck64_w       /*!< 64 CK_NCOn clock period.   */
#define NCO_PFM_WIDTH_128CLOCK          APB_NCO01_NCO0_PWS_ck128_w      /*!< 128 CK_NCOn clock period.  */
//!@}

#endif





/**
 *******************************************************************************
 * @brief       Config APB ITR6 MUX.
 * @param[in]   "__MUX__" : specifies the APB timer to enable.
 *  @arg\b	    APB_ITR6_TM00_TRGO : Enable TM00_TRGO.
 *  @arg\b	    APB_ITR6_TM10_TRGO : Enable TM10_TRGO.
 *  @arg\b	    APB_ITR6_TM20_TRGO : Enable TM20_TRGO.
 *  @arg\b	    APB_ITR6_TM36_TRGO : Enable TM36_TRGO.
 *  @arg\b	    APB_ITR6_INT_PB    : Enable INT_PB.
 *  @arg\b	    APB_ITR6_URT1_TMO  : Enable URT1_TMO.
 *  @arg\b	    APB_ITR6_URT2_BRO  : Enable URT2_BRO.
 *  @arg\b	    APB_ITR6_URT2_TMO  : Enable URT2_TMO.
 * @return		None
 *******************************************************************************
 */
#define __DRV_APB_ITR6_ENABLE(__MUX__)                                          \
        (APB->CR2.W = (APB->CR2.W & ~(APB_CR2_ITR6_MUX_mask_w)) | (__MUX__))     

/**
 *******************************************************************************
 * @brief       Config APB ITR7 MUX.
 * @param[in]   "__MUX__" : specifies the APB timer to enable.
 *  @arg\b      APB_ITR7_TM01_TRGO : Enable TM01_TRGO.
 *  @arg\b      APB_ITR7_TM16_TRGO : Enable TM16_TRGO.
 *  @arg\b      APB_ITR7_TM26_TRGO : Enable TM26_TRGO.
 *  @arg\b      APB_ITR7_ADC0_OUT  : Enable ADC0_OUT.
 *  @arg\b      APB_ITR7_INT_PD    : Enable INT_PD.
 *  @arg\b      APB_ITR7_URT1_BRO  : Enable URT1_BRO.
 *  @arg\b      APB_ITR7_URT3_BRO  : Enable URT3_BRO.
 *  @arg\b      APB_ITR7_URT3_TMO  : Enable URT3_TMO.
 *  @arg\b      APB_ITR7_ICKO      : Enable ICKO.
 *  @arg\b      APB_ITR7_RTC_OUT   : Enable RTC_OUT.
 *  @arg\b      APB_ITR7_TM36_XOR  : Enable TM36_XOR.
 *  @arg\b      APB_ITR7_NCO_P0    : Enable NCO_P0.
 * @return      None
 *******************************************************************************
 */
#define __DRV_APB_ITR7_ENABLE(__MUX__)                                          \
        (APB->CR2.W = (APB->CR2.W & ~(APB_CR2_ITR7_MUX_mask_w)) | (__MUX__))     

/**
 *******************************************************************************
 * @brief       Enable the Timer peripheral.
 * @param[in]   "__TIMER__" : specifies the APB timer to enable.
 *  @arg\b      APB_TM00_MACRO : Enable TM00 (EN+EN2).
 *  @arg\b      APB_TM01_MACRO : Enable TM01 (EN+EN2).
 *  @arg\b      APB_TM10_MACRO : Enable TM10 (EN+EN2).
 *  @arg\b      APB_TM16_MACRO : Enable TM16 (EN+EN2).
 *  @arg\b      APB_TM20_MACRO : Enable TM20 (EN+EN2).
 *  @arg\b      APB_TM26_MACRO : Enable TM26 (EN+EN2).
 *  @arg\b      APB_TM36_MACRO : Enable TM36 (EN+EN2).
 * @return      None
 *******************************************************************************
 */
#define __DRV_APB_TIMER_ENABLE(__TIMER__)                                       \
        (APB->CR1.W = __TIMER__)


/**
 *******************************************************************************
 * @brief       Enable the Timer's main counter.
 * @param[in]   "__TIMER__" : specifies the APB timer's main counter to enable.
 *  @arg\b      APB_TM00_MAIN_ENABLE : Enable TM00 (EN).
 *  @arg\b      APB_TM01_MAIN_ENABLE : Enable TM01 (EN).
 *  @arg\b      APB_TM10_MAIN_ENABLE : Enable TM10 (EN).
 *  @arg\b      APB_TM16_MAIN_ENABLE : Enable TM16 (EN).
 *  @arg\b      APB_TM20_MAIN_ENABLE : Enable TM20 (EN).
 *  @arg\b      APB_TM26_MAIN_ENABLE : Enable TM26 (EN).
 *  @arg\b      APB_TM36_MAIN_ENABLE : Enable TM36 (EN).
 * @return      None
 *******************************************************************************
 */
#define __DRV_APB_MAIN_ENABLE(__TIMER__)                                        \
        (APB->CR1.W = __TIMER__)


/**
 *******************************************************************************
 * @brief       Enable the Timer's prescaler counter.
 * @param[in]   "__TIMER__" : specifies the APB timer's prescaler counter to enable.
 *  @arg\b      APB_TM00_PRESCALER_ENABL : Enable TM00 (EN2).
 *  @arg\b      APB_TM01_PRESCALER_ENABL : Enable TM01 (EN2).
 *  @arg\b      APB_TM10_PRESCALER_ENABL : Enable TM10 (EN2).
 *  @arg\b      APB_TM16_PRESCALER_ENABL : Enable TM16 (EN2).
 *  @arg\b      APB_TM20_PRESCALER_ENABL : Enable TM20 (EN2).
 *  @arg\b      APB_TM26_PRESCALER_ENABL : Enable TM26 (EN2).
 *  @arg\b      APB_TM36_PRESCALER_ENABL : Enable TM36 (EN2).
 * @return      None
 *******************************************************************************
 */
#define __DRV_APB_PRESCALER_ENABLE(__TIMER__)                                   \
        (APB->CR1.W = __TIMER__)

/**
 *******************************************************************************
 * @brief       IR data output selection.
 * @param[in]   "__IRDATSRC__" : specifies the APB IR data source.
 *  @arg\b      APB_IRDAT0_LOW : IR data keep 0 output.
 *  @arg\b      APB_IRDAT1_TM20_TRGO : IR data from TM20_TRGO output.
 *  @arg\b      APB_IRDAT2_TM26_TRGO : IR data from TM26_TRGO output.
 *  @arg\b      APB_IRDAT3_TM36_TRGO : IR data from TM36_TRGO output.
 *  @arg\b      APB_IRDAT4_SPI0_MOSI : IR data from SPI0_MOSI output.
 *  @arg\b      APB_IRDAT5_URT1_TX : IR data from URT1_TX output.
 *  @arg\b      APB_IRDAT6_URT2_TX : IR data from URT2_TX output.
 *  @arg\b      APB_IRDAT7_URT3_TX : IR data from URT3_TX output.
 * @return      None
 *******************************************************************************
 */
#define __DRV_APB_IRDAT(__IRDATSRC__)                                           \
    (APB->CR0.W = (APB->CR0.W & ~(APB_CR0_IRDAT_MUX_mask_w)) | (__IRDATSRC__))                                 

/**
 *******************************************************************************
 * @brief       Invert or Normal IRDAT output.
 * @param[in]   "__IRDATInvert__" : specifies the IRDAT invert.
 *  @arg\b      APB_IRDAT_INV : Invert Output of IRDAT.
 *  @arg\b      APB_IRDAT_NOINV : Normal Output of IRDAT.
 * @return      None
 *******************************************************************************
 */
#define __DRV_APB_IRDAT_INVERT(__IRDATInvert__)                                 \
    (APB->CR0.W = (APB->CR0.W & ~(APB_IRDAT_INV)) | (__IRDATInvert__))                                 

/**
 *******************************************************************************
 * @brief       IR clock source selection.
 * @param[in]   "__IRCLKSRC__" : specifies the APB IR clock source.
 *  @arg\b      APB_IRCLK0_LOW : IR clock keep 0 output.
 *  @arg\b      APB_IRCLK1_TM00_CKO : IR clock from TM00_CKO output.
 *  @arg\b      APB_IRCLK2_TM01_CKO : IR clock from TM01_CKO output.
 *  @arg\b      APB_IRCLK3_TM10_CKO : IR clock from TM10_CKO output.
 *  @arg\b      APB_IRCLK4_TM16_TRGO :IR clock from TM16_CKO output.
 *  @arg\b      APB_IRCLK5_URT1_TMO : IR clock from URT1_TMO output.
 *  @arg\b      APB_IRCLK6_URT2_TMO : IR clock from URT2_TMO output.
 *  @arg\b      APB_IRCLK7_URT3_TMO : IR clock from URT3_TMO output.
 * @return      None
 *******************************************************************************
 */
#define __DRV_APB_IRCLK(__IRCLKSRC__)                                           \
    (APB->CR0.W = (APB->CR0.W & ~(APB_CR0_IRCLK_MUX_mask_w)) | (__IRCLKSRC__))                                 

/**
 *******************************************************************************
 * @brief       Invert or Normal IRCLK output.
 * @param[in]   "__IRCLKINVERT__" : specifies the IRCLK invert.
 *  @arg\b      APB_IRCLK_INV :  Invert Output of IRCLK. 
 *  @arg\b      APB_IRCLK_NOINV : Normal Output of IRCLK.
 * @return      None
 *******************************************************************************
 */
#define __DRV_APB_IRCLK_INVERT(__IRCLKINVERT__)                                 \
    (APB->CR0.W = (APB->CR0.W & APB_IRCLK_INV) | (__IRCLKINVERT__))                                 

#if defined(MG32_3RD)
/**
 *******************************************************************************
 * @brief       Enable the NCO.
 * @return      None
 *******************************************************************************
 */
#define __DRV_NCO_ENABLE()                                                      \
  (APB->NCO00.W |= APB_NCO00_NCO0_EN_enable_w)

/**
 *******************************************************************************
 * @brief       Disable the NCO.
 * @return      None
 *******************************************************************************
 */
#define __DRV_NCO_DISABLE()                                                     \
  (APB->NCO00.W &= ~APB_NCO00_NCO0_EN_enable_w)


/**
 *******************************************************************************
 * @brief       Config the NCO clock source.
 * @param[in]   "__CLOCKSRC__" : specifies the NCO clock source
 *  @arg\b      NCO_CLOCK_IHRCO : NCO clock from CK_IHRCO.
 *  @arg\b      NCO_CLOCK_PLL : NCO clock from CK_PLL.
 *  @arg\b      NCO_CLOCK_APB : NCO clock from CL_APB.
 *  @arg\b      NCO_CLOCK_LS : NCO clock from CK_LS.
 *  @arg\b      NCO_CLOCK_TM00_TRGO : NCO clock from TM00_TRGO.
 *  @arg\b      NCO_CLOCK_NCO_CK0 : NCO clock from NCO_CK0.
 * @return      None
 *******************************************************************************
 */
#define __DRV_NCO_CLOCK(__CLOCKSRC__)                                           \
    (APB->NCO00.W = (APB->NCO00.W & ~APB_NCO00_NCO0_CKS_mask_w) | (__CLOCKSRC__))                               


/**
 *******************************************************************************
 * @brief       Config the NCO function mode.
 * @param[in]   "__MODE__" : specifies the NCO operation mode
 *  @arg\b      NCO_OUTPUT_FDC : FDC : fixed duty cycle mode.
 *  @arg\b      NCO_OUTPUT_PFM : PFM : pulse frequency mode.
 * @return      None
 *******************************************************************************
 */
#define __DRV_NCO_FUNCTION_MODE(__MODE__)                                       \
    (APB->NCO00.W = (APB->NCO00.W & ~APB_NCO00_NCO0_MDS_mask_w) | (__MODE__))                               

/**
 *******************************************************************************
 * @brief       Invert or Normal NCO output.
 * @param[in]   "__NCOINV__" : specifies the IRDAT invert.
 *  @arg\b      NCO_OUTPUTPOL_NONINVERTED : NCO output on GPIO isn't inverted.
 *  @arg\b      NCO_OUTPUTPOL_INVERTED : NCO output on GPIO is inverted. 
 * @return      None
 *******************************************************************************
 */
#define __DRV_NCO_INVERT_OUTPUT(__NCOINV__)                                     \
    (APB->NCO00.W = (APB->NCO00.W & ~APB_NCO00_NCO0_INV_mask_w) |  (__NCOINV__))                                 

/**
 *******************************************************************************
 * @brief       Config NCO PFM mode output pulse width select.
 * @param[in]   "__PFMWIDTH__" : specifies the PFM mode pulse width select.
 *  @arg\b      NCO_PFM_WIDTH_1CLOCK : 1 CK_NCOn clock period.
 *  @arg\b      NCO_PFM_WIDTH_2CLOCK : 2 CK_NCOn clock period.
 *  @arg\b      NCO_PFM_WIDTH_4CLOCK : 4 CK_NCOn clock period.
 *  @arg\b      NCO_PFM_WIDTH_8CLOCK : 8 CK_NCOn clock period.
 *  @arg\b      NCO_PFM_WIDTH_16CLOCK : 16 CK_NCOn clock period.
 *  @arg\b      NCO_PFM_WIDTH_32CLOCK : 32 CK_NCOn clock period.
 *  @arg\b      NCO_PFM_WIDTH_64CLOCK : 64 CK_NCOn clock period.
 *  @arg\b      NCO_PFM_WIDTH_128CLOCK : 128 CK_NCOn clock period.
 * @return      None
 *******************************************************************************
 */
#define __DRV_NCO_PFM_WIDTH(__PFMWIDTH__)                                       \
    (APB->NCO01.W = (APB->NCO01.W & ~APB_NCO01_NCO0_PWS_mask_w) | (__PFMWIDTH__))                                 

/**
 *******************************************************************************
 * @brief       Setup NCO adder increment value. (Must small than 2^19)
 * @param[in]   "__ACC__" : specifies the NCO adder increment value.
 * @return      None
 *******************************************************************************
 */
#define __DRV_NCO_INC(__ACC__)                                                  \
    (APB->NCO00.W = (APB->NCO00.W & ~APB_NCO00_NCO0_INC_mask_w) | (__ACC__ & 0x0FFFFF))

/**
 *******************************************************************************
 * @brief       InitialNCO NCO adder accumulator store data.
 * @param[in]   "__INIT__" : specifies the  NCO adder accumulator store data.
 * @return      None
 *******************************************************************************
 */
#define __DRV_NCO_ADDER_INIT(__INIT__)                                          \
    (APB->NCO01.W = (APB->NCO01.W & ~APB_NCO01_NCO0_ACC_mask_w) | (__INIT__ & 0x0FFFFF))

#endif

/**
 *******************************************************************************
 * @brief       Enables the specified APB interrupt.
 * @param[in]   "__INTERRUPT__" : specifies the APB interrupt source to enable.
 *  @arg\b      APB_IT_OBM0 : OBM0 interrupt.
 *  @arg\b      APB_IT_OBM1 : OBM1 interrupt.
 *  @arg\b      APB_IT_NCO : NCO interrupt.
 * @return      None
 *******************************************************************************
 */
#define __DRV_APB_ENABLE_IT(__INTERRUPT__)                                      \
    (APB->INT.W |= (__INTERRUPT__))


/**
 *******************************************************************************
 * @brief       Disables the specified APB interrupt.
 * @param[in]   "__INTERRUPT__" : specifies the APB interrupt source to enable.
 *  @arg\b      APB_IT_OBM0 : OBM0 interrupt.
 *  @arg\b      APB_IT_OBM1 : OBM1 interrupt.
 *  @arg\b      APB_IT_NCO : NCO interrupt.
 * @return      None
 *******************************************************************************
 */
#define __DRV_APB_DISABLE_IT(__INTERRUPT__)                                     \
    (APB->INT.W &= ~(__INTERRUPT__))


/**
 *******************************************************************************
 * @brief       Checks whether the specified APB interrupt has occurred or not.
 * @param[in]   "__INTERRUPT__" : specifies the APB interrupt source to enable.
 *  @arg\b      APB_IT_OBM0 : OBM0 interrupt.
 *  @arg\b      APB_IT_OBM1 : OBM1 interrupt.
 *  @arg\b      APB_IT_NCO : NCO interrupt.
 * @return      None
 *******************************************************************************
 */
#define __DRV_APB_GET_IT_SOURCE(__INTERRUPT__)                                  \
    (((APB->INT.W & (__INTERRUPT__)) == (__INTERRUPT__)) ? ENABLE : DISABLE)

/**
 *******************************************************************************
 * @brief       Enables the specified APB (OBMx) all interrupt.
 * @return      None
 * @note 
 * @par         Example
 * @code
    MID_APB_ENABLE_ITEA();
 * @endcode
 *******************************************************************************
 */
#define __DRV_APB_ENABLE_ITEA()             (APB->INT.W |= APB_INT_IEA_enable_w)

/**
 *******************************************************************************
 * @brief       Disables the specified APB (OBMx) all interrupt.
 * @return      None
 * @note 
 *******************************************************************************
 */
#define __DRV_APB_DISABLE_ITEA()            (APB->INT.W &= ~APB_INT_IEA_enable_w)


/**
 *******************************************************************************
 * @brief       Clear the APB interrupt pending bits.
 * @param[in]   "__FLAG__" : specifies the APB interrupt flag to clear.
 *  @arg\b      APB_FLAG_OBM0 : OBM0 interrupt flag.
 *  @arg\b      APB_FLAG_OBM1 : OBM1 interrupt flag.
 *  @arg\b      APB_FLAG_NCO : NCO interrupt flag.
 * @return      None
 *******************************************************************************
 */
#define __DRV_APB_CLEAR_FLAG(__FLAG__)      (APB->STA.W = (__FLAG__))


/**
 *******************************************************************************
 * @brief       Get the APB interrupt pending bits.
 * @param[in]   "__FLAG__" : specifies the APB interrupt flag to clear.
 *  @arg\b      APB_FLAG_OBM0 : OBM0 interrupt flag.
 *  @arg\b      APB_FLAG_OBM1 : OBM1 interrupt flag.
 *  @arg\b      APB_FLAG_NCO : NCO interrupt flag.
 * @return      None
 *******************************************************************************
 */
#define __DRV_APB_GET_FLAG(__FLAG__)        ((APB->STA.W & (__FLAG__)) == (__FLAG__))





/**
 * @name    Function announce
 * @brief   Time base initial/Deinitial	
 */ 
///@{
MID_StatusTypeDef MID_OBMx_Init(MID_OBMx_HandleTypeDef* hAPB);
MID_StatusTypeDef MID_OBMx_DeInit(MID_OBMx_HandleTypeDef *hAPB);
void MID_OBMx_MspInit(MID_OBMx_HandleTypeDef* hAPB);
void MID_OBMx_MspDeInit(MID_OBMx_HandleTypeDef* hAPB);
///* Blocking mode: Polling */
MID_StatusTypeDef MID_OBMx_Start(MID_OBMx_HandleTypeDef* hAPB);
MID_StatusTypeDef MID_OBMx_Stop(MID_OBMx_HandleTypeDef* hAPB);
///* Non-blocking mode: Interruption */
MID_StatusTypeDef MID_OBMx_Start_IT(MID_OBMx_HandleTypeDef* hAPB);
MID_StatusTypeDef MID_OBMx_Stop_IT(MID_OBMx_HandleTypeDef* hAPB);
///@}


/**
 * @name    Function announce
 * @brief   addtogroup APB_Private_Functions
 */ 
///@{
uint32_t MID_OBMx_GetOutputLevel(MID_OBMx_HandleTypeDef* mOBMx);
void MID_OBMx_IRQHandler(MID_OBMx_HandleTypeDef* mOBMx);
void MID_OBMx_TriggerCallbackOBM0(MID_OBMx_HandleTypeDef* mOBMx);
void MID_OBMx_TriggerCallbackOBM1(MID_OBMx_HandleTypeDef* mOBMx);
uint32_t MID_OBMx_GetSwitchState(MID_OBMx_HandleTypeDef *mOBMx);
MID_StatusTypeDef MID_APB_UpdateSwitchState(MID_OBMx_HandleTypeDef *mOBMx, uint32_t InitState) ;
uint32_t MID_OBMx_GetState(MID_OBMx_HandleTypeDef *mOBMx);
#if defined(MG32_3RD) || defined(MG32_4TH)    
void MID_NCO_IRQHandler(void);
void MID_APB_NCOTriggerCallback(void);
uint32_t MID_NCO_GetOutputState(void);
#endif
///@}

#endif

