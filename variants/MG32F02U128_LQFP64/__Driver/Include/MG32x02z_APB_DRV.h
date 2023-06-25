/**
 ******************************************************************************
 *
 * @file        MG32x02z_APB_DRV.h
 *
 * @brief       This file contains all the functions prototypes for the APB
 *              firmware library.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.18
 * @date        2020/03/13
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
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
#ifndef __MG32x02z_APB_DRV_H
#define __MG32x02z_APB_DRV_H
//#define _MG32x02z_APB_DRV_H_VER 0.01



#include "MG32x02z__Common_DRV.h"
#include "MG32x02z_APB.h"
#include "MG32x02z__ExtraStruct.h"



/**
 * @brief  	simple define
 *
 */ 

/** @brief OBMx unlock for update initial state */
#define APB_OBMx_unlocked           ((uint8_t)0x20)      /*!< Bit Value =(1):Un-Locked of 8it */
/** @brief OBMx initial to '1' state */
#define APB_OBMx_initial_1          ((uint8_t)0x10)      /*!< Bit Value =(1):Un-Locked of 8it */
/** @brief OBMx initial to '0' state */
#define APB_OBMx_initial_0          ((uint8_t)0x00)      /*!< Bit Value =(1):Un-Locked of 8it */

/** @brief APB Enable TM36 2nd Timer/Counter */
#define APB_TM36_EN2                APB_CR1_TM36_EN2_enable_w
/** @brief APB Enable TM26 2nd Timer/Counter */
#define APB_TM26_EN2                APB_CR1_TM26_EN2_enable_w
/** @brief APB Enable TM20 2nd Timer/Counter */
#define APB_TM20_EN2                APB_CR1_TM20_EN2_enable_w
/** @brief APB Enable TM16 2nd Timer/Counter */
#define APB_TM16_EN2                APB_CR1_TM16_EN2_enable_w
/** @brief APB Enable TM10 2nd Timer/Counter */
#define APB_TM10_EN2                APB_CR1_TM10_EN2_enable_w
/** @brief APB Enable TM01 2nd Timer/Counter */
#define APB_TM01_EN2                APB_CR1_TM01_EN2_enable_w
/** @brief APB Enable TM00 2nd Timer/Counter */
#define APB_TM00_EN2                APB_CR1_TM00_EN2_enable_w

/** @brief APB Enable TM36 main Timer/Counter */
#define APB_TM36_EN                 APB_CR1_TM36_EN_enable_w
/** @brief APB Enable TM26 main Timer/Counter */
#define APB_TM26_EN                 APB_CR1_TM26_EN_enable_w
/** @brief APB Enable TM20 main Timer/Counter */
#define APB_TM20_EN                 APB_CR1_TM20_EN_enable_w
/** @brief APB Enable TM16 main Timer/Counter */
#define APB_TM16_EN                 APB_CR1_TM16_EN_enable_w
/** @brief APB Enable TM10 main Timer/Counter */
#define APB_TM10_EN                 APB_CR1_TM10_EN_enable_w
/** @brief APB Enable TM01 main Timer/Counter */
#define APB_TM01_EN                 APB_CR1_TM01_EN_enable_w
/** @brief APB Enable TM00 main Timer/Counter */
#define APB_TM00_EN                 APB_CR1_TM00_EN_enable_w

/** @brief OBM1F trigger event flag */
#define APB_OBM1F                   APB_STA_OBM1F_happened_w
/** @brief OBM1 interrupt enable bit */
#define APB_OBM1_IE                 APB_INT_OBM1_IE_enable_w

#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
/** @brief OBM0F trigger event flag */
#define APB_OBM0F                   APB_STA_OBM0F_happened_w
/** @brief OBM0 interrupt enable bit */
#define APB_OBM0_IE                 APB_INT_OBM0_IE_enable_w
#endif

#if defined(MG32_3RD) || defined(MG32_4TH)
/** @brief NCO0 adder overflow event flag */
#define APB_NCO0F                   APB_STA_NCO0F_happened_w
/** @brief NCO0 interrupt control bit */
#define APB_NCO0_IE                 APB_INT_NCO0_IE_enable_w
#endif

#if defined(MG32_1ST)
/** 
 * @enum		APB_TimerITR6SrcDef
 * @brief		declare ITR6 source
 */        
typedef enum 
{
    ITR6_TM00_TRGO=0,   /*!< TM00's TRGO signal */
    ITR6_TM10_TRGO=1,   /*!< TM10's TRGO signal */
    ITR6_TM20_TRGO=2,   /*!< TM20's TRGO signal */
    ITR6_TM36_TRGO=3,   /*!< TM36's TRGO signal */
    ITR6_INT_PB=4,      /*!< INT_PB signal */
    ITR6_URT1_TMO=5,    /*!< URT1's TMO signal */
    ITR6_URT2_BRO=6,    /*!< URT2's BRO signal */
    ITR6_URT2_TMO=7     /*!< URT2's TMO signal */
} APB_TimerITR6SrcDef;


/** 
 * @enum		APB_TimerITR7SrcDef
 * @brief		declare ITR7 source
 */        
typedef enum 
{
    ITR7_TM01_TRGO=0,   /*!< TM01's TRGO signal */
    ITR7_TM16_TRGO=1,   /*!< TM16's TRGO signal */
    ITR7_TM26_TRGO=2,   /*!< TM26's TRGO signal */
    ITR7_ADC0_OUT=3,    /*!< ADC0_OUT signal */
    ITR7_INT_PD=4,      /*!< INT_PD signal */
    ITR7_URT1_BRO=5,    /*!< URT1's BRO signal */
    ITR7_URT3_BRO=6,    /*!< URT3's BRO signal */
    ITR7_URT3_TMO=7,    /*!< URT3's TMO signal */
    ITR7_ICKO_INT=8,    /*!< ICKO interrupt event */
    ITR7_RTC_OUT=9,     /*!< RTC Output signal */
    ITR7_TM36_XOR=10    /*!< TM36 XOR gate output signal */
} APB_TimerITR7SrcDef;
#endif

#if defined(MG32_2ND)
/** 
 * @enum		APB_TimerITR6SrcDef
 * @brief		declare ITR6 source
 */        
typedef enum 
{
    ITR6_TM00_TRGO=0,   /*!< TM00's TRGO signal */
    ITR6_TM10_TRGO=1,   /*!< TM10's TRGO signal */
    ITR6_TM36_TRGO=3,   /*!< TM36's TRGO signal */
    ITR6_INT_PB=4,      /*!< INT_PB signal */
    ITR6_URT1_TMO=5     /*!< URT1's TMO signal */
} APB_TimerITR6SrcDef;


/** 
 * @enum		APB_TimerITR7SrcDef
 * @brief		declare ITR7 source
 */        
typedef enum 
{
    ITR7_TM01_TRGO=0,   /*!< TM01's TRGO signal */
    ITR7_TM16_TRGO=1,   /*!< TM16's TRGO signal */
    ITR7_ADC0_OUT=3,    /*!< ADC0_OUT signal */
    ITR7_INT_PD=4,      /*!< INT_PD signal */
    ITR7_URT1_BRO=5,    /*!< URT1's BRO signal */
    ITR7_ICKO_INT=8,    /*!< ICKO interrupt event */
    ITR7_RTC_OUT=9,     /*!< RTC Output signal */
    ITR7_TM36_XOR=10    /*!< TM36 XOR gate output signal */
} APB_TimerITR7SrcDef;
#endif

#if defined(MG32_3RD)
/** 
 * @enum		APB_TimerITR6SrcDef
 * @brief		declare ITR6 source
 */        
typedef enum 
{
    ITR6_TM00_TRGO=0,   /*!< TM00's TRGO signal */
    ITR6_TM10_TRGO=1,   /*!< TM10's TRGO signal */
    ITR6_TM20_TRGO=2,   /*!< TM20's TRGO signal */
    ITR6_TM36_TRGO=3,   /*!< TM36's TRGO signal */
    ITR6_INT_PB=4,      /*!< INT_PB signal */
    ITR6_URT1_TMO=5,    /*!< URT1's TMO signal */
    ITR6_URT2_BRO=6,    /*!< URT2's BRO signal */
    ITR6_URT2_TMO=7     /*!< URT2's TMO signal */
} APB_TimerITR6SrcDef;


/** 
 * @enum		APB_TimerITR7SrcDef
 * @brief		declare ITR7 source
 */        
typedef enum 
{
    ITR7_TM01_TRGO=0,   /*!< TM01's TRGO signal */
    ITR7_TM16_TRGO=1,   /*!< TM16's TRGO signal */
    ITR7_TM26_TRGO=2,   /*!< TM26's TRGO signal */
    ITR7_ADC0_OUT=3,    /*!< ADC0_OUT signal */
    ITR7_INT_PD=4,      /*!< INT_PD signal */
    ITR7_URT1_BRO=5,    /*!< URT1's BRO signal */
    ITR7_ICKO_INT=8,    /*!< ICKO interrupt event */
    ITR7_RTC_OUT=9,     /*!< RTC Output signal */
    ITR7_TM36_XOR=10,   /*!< TM36 XOR gate output signal */
    ITR7_NCO0_OUT=11    /*!< NCO0_OUT output signal */
} APB_TimerITR7SrcDef;
#endif

#if defined(MG32_4TH)
/** 
 * @enum		APB_TimerITR6SrcDef
 * @brief		declare ITR6 source
 */        
typedef enum 
{
    ITR6_TM00_TRGO=0,   /*!< TM00's TRGO signal */
    ITR6_TM10_TRGO=1,   /*!< TM10's TRGO signal */
    ITR6_TM20_TRGO=2,   /*!< TM20's TRGO signal */
    ITR6_TM36_TRGO=3,   /*!< TM36's TRGO signal */
    ITR6_INT_PB=4,      /*!< INT_PB signal */
    ITR6_URT1_TMO=5     /*!< URT1's TMO signal */
} APB_TimerITR6SrcDef;


/** 
 * @enum		APB_TimerITR7SrcDef
 * @brief		declare ITR7 source
 */        
typedef enum 
{
    ITR7_TM01_TRGO=0,   /*!< TM01's TRGO signal */
    ITR7_TM16_TRGO=1,   /*!< TM16's TRGO signal */
    ITR7_ADC0_OUT=3,    /*!< ADC0_OUT signal */
    ITR7_INT_PD=4,      /*!< INT_PD signal */
    ITR7_URT1_BRO=5,    /*!< URT1's BRO signal */
    ITR7_ICKO_INT=8,    /*!< ICKO interrupt event */
    ITR7_RTC_OUT=9,     /*!< RTC Output signal */
    ITR7_TM36_XOR=10,   /*!< TM36 XOR gate output signal */
    ITR7_NCO0_OUT=11    /*!< NCO0_OUT output signal */
} APB_TimerITR7SrcDef;
#endif


#if defined(MG32_1ST)
/** 
 * @enum		BKS0SrcDef
 * @brief		declare BKS0 source
 */        
typedef enum 
{
    BKS0_Logic_1=0,     /*!< Output '1' state */
    BKS0_ADC0_OUT=3,    /*!< ADC0_OUT signal state */
    BKS0_TM00_TRGO=4,   /*!< TM00's TRGO signal */
    BKS0_TM10_TRGO=5,   /*!< TM10's TRGO signal */
    BKS0_TM20_OC00=8,   /*!< TM20's OC00 output state  */
    BKS0_TM36_OC2=9,    /*!< TM36's OC2 output state */
    BKS0_CMP0_OUT=10,   /*!< CMP0's output state  */
    BKS0_URT0_TX=12,    /*!< URT0's TX signal */
    BKS0_URT2_TX=13,    /*!< URT2's TX signal */
    BKS0_URT0_RX=14,    /*!< URT0's RX signal */
    BKS0_URT2_RX=15     /*!< URT2's RX signal */
} BKS0SrcDef;

/** 
 * @enum		BKS1SrcDef
 * @brief		declare BKS1 source
 */        
typedef enum 
{
    BKS1_Logic_1=0,     /*!< Output '1' state */
    BKS1_TM01_TRGO=4,   /*!< TM01's TRGO signal */
    BKS1_TM26_TRGO=6,   /*!< TM26's TRGO signal */
    BKS1_TM20_OC10=8,   /*!< TM20's OC10 output state  */
    BKS1_TM36_OC3=9,    /*!< TM36's OC3 output state */
    BKS1_CMP1_OUT=10,   /*!< CMP1's output state  */
    BKS1_URT1_TX=12,    /*!< URT1's TX signal */
    BKS1_URT3_TX=13,    /*!< URT3's TX signal */
    BKS1_URT1_RX=14,    /*!< URT1's RX signal */
    BKS1_URT3_RX=15     /*!< URT3's RX signal */
} BKS1SrcDef;

/** 
 * @enum		BKS2SrcDef
 * @brief		declare BKS2 source
 */        
typedef enum 
{
    BKS2_Logic_1=0,     /*!< Output '1' state */
    BKS2_SPI0_MOSI=3,   /*!< SPI0's MOSI output state */
    BKS2_TM36_TRGO=6,   /*!< TM36's TRGO signal */
    BKS2_CMP2_OUT=10,   /*!< CMP2's output state  */
    BKS2_CMP3_OUT=11,   /*!< CMP3's output state  */
    BKS2_URT2_BRO=12,   /*!< URT2's BRO signal */
    BKS2_URT2_TMO=13,   /*!< URT2's TMO signal */
    BKS2_URT3_BRO=14,   /*!< URT3's BRO signal */
    BKS2_URT3_TMO=15    /*!< URT3's TM0 signal */
} BKS2SrcDef;
#endif

#if defined(MG32_2ND)
/** 
 * @enum		BKS0SrcDef
 * @brief		declare BKS0 source
 */        
typedef enum 
{
    BKS0_Logic_1=0,     /*!< Output '1' state */
    BKS0_INT_PA=1,      /*!< INT_PA signal state */
    BKS0_INT_PC=2,      /*!< INT_PC signal state */
    BKS0_ADC0_OUT=3,    /*!< ADC0_OUT signal state */
    BKS0_TM00_TRGO=4,   /*!< TM00's TRGO signal */
    BKS0_TM10_TRGO=5,   /*!< TM10's TRGO signal */
    BKS0_TM36_OC2=9,    /*!< TM36's OC2 output state */
    BKS0_CMP0_OUT=10,   /*!< CMP0's output state  */
    BKS0_URT0_TX=12,    /*!< URT0's TX signal */
    BKS0_URT0_RX=14     /*!< URT0's RX signal */
} BKS0SrcDef;

/** 
 * @enum		BKS1SrcDef
 * @brief		declare BKS1 source
 */        
typedef enum 
{
    BKS1_Logic_1=0,     /*!< Output '1' state */
    BKS1_INT_PB=1,      /*!< INT_PB signal state */
    BKS1_INT_PD=2,      /*!< INT_PD signal state */
    BKS1_INT_BOD1=3,    /*!< BOD1 signal state */
    BKS1_TM01_TRGO=4,   /*!< TM01's TRGO signal */
    BKS1_TM16_TRGO=5,   /*!< TM16's TRGO signal */
    BKS1_TM36_OC3=9,    /*!< TM36's OC3 output state */
    BKS1_CMP1_OUT=10,   /*!< CMP1's output state  */
    BKS1_URT1_TX=12,    /*!< URT1's TX signal */
    BKS1_URT1_RX=14     /*!< URT1's RX signal */
} BKS1SrcDef;

/** 
 * @enum		BKS2SrcDef
 * @brief		declare BKS2 source
 */        
typedef enum 
{
    BKS2_Logic_1=0,     /*!< Output '1' state */
    BKS2_SPI0_MOSI=3,   /*!< SPI0's MOSI output state */
    BKS2_TM36_TRGO=6    /*!< TM36's TRGO signal */
} BKS2SrcDef;
#endif

#if defined(MG32_3RD)
/** 
 * @enum		BKS0SrcDef
 * @brief		declare BKS0 source
 */        
typedef enum 
{
    BKS0_Logic_1=0,     /*!< Output '1' state */
    BKS0_INT_PA=1,      /*!< INT_PA signal state */
    BKS0_INT_PC=2,      /*!< INT_PC signal state */
    BKS0_ADC0_OUT=3,    /*!< ADC0_OUT signal state */
    BKS0_TM00_TRGO=4,   /*!< TM00's TRGO signal */
    BKS0_TM10_TRGO=5,   /*!< TM10's TRGO signal */
    BKS0_TM20_TRGO=6,   /*!< TM20's TRGO output state  */
    BKS0_CCL_P0=7,      /*!< CCL_P0 output state  */
    BKS0_TM20_OC00=8,   /*!< TM20's OC00 output state  */
    BKS0_TM36_OC2=9,    /*!< TM36's OC2 output state */
    BKS0_CMP0_OUT=10,   /*!< CMP0's output state  */
    BKS0_URT0_TX=12,    /*!< URT0's TX signal */
    BKS0_URT2_TX=13,    /*!< URT2's TX signal */
    BKS0_URT0_RX=14,    /*!< URT0's RX signal */
    BKS0_URT2_RX=15     /*!< URT2's RX signal */
} BKS0SrcDef;

/** 
 * @enum		BKS1SrcDef
 * @brief		declare BKS1 source
 */        
typedef enum 
{
    BKS1_Logic_1=0,     /*!< Output '1' state */
    BKS1_INT_PB=1,      /*!< INT_PB signal state */
    BKS1_INT_PD=2,      /*!< INT_PD signal state */
    BKS1_INT_BOD1=3,    /*!< BOD1 signal state */
    BKS1_TM01_TRGO=4,   /*!< TM01's TRGO signal */
    BKS1_TM16_TRGO=5,   /*!< TM16's TRGO signal */
    BKS1_TM26_TRGO=6,   /*!< TM26's TRGO signal */
    BKS1_CCL_P1=7,      /*!< CCL_P1 output state  */
    BKS1_TM20_OC10=8,   /*!< TM20's OC10 output state  */
    BKS1_TM36_OC3=9,    /*!< TM36's OC3 output state */
    BKS1_CMP1_OUT=10,   /*!< CMP1's output state  */
    BKS1_URT1_TX=12,    /*!< URT1's TX signal */
    BKS1_URT1_RX=14     /*!< URT1's RX signal */
} BKS1SrcDef;

/** 
 * @enum		BKS2SrcDef
 * @brief		declare BKS2 source
 */        
typedef enum 
{
    BKS2_Logic_1=0,     /*!< Output '1' state */
    BKS2_INT_PE=1,      /*!< INT_PE signal state */
    BKS2_SPI0_MOSI=3,   /*!< SPI0's MOSI output state */
    BKS2_TM36_TRGO=6,   /*!< TM36's TRGO signal */
    BKS2_URT2_BRO=12,   /*!< URT2's BRO signal */
    BKS2_URT2_TMO=13    /*!< URT2's TMO signal */
} BKS2SrcDef;
#endif

#if defined(MG32_4TH)
/** 
 * @enum		BKS0SrcDef
 * @brief		declare BKS0 source
 */        
typedef enum 
{
    BKS0_Logic_1=0,     /*!< Output '1' state */
    BKS0_INT_PA=1,      /*!< INT_PA signal state */
    BKS0_INT_PC=2,      /*!< INT_PC signal state */
    BKS0_ADC0_OUT=3,    /*!< ADC0_OUT signal state */
    BKS0_TM00_TRGO=4,   /*!< TM00's TRGO signal */
    BKS0_TM10_TRGO=5,   /*!< TM10's TRGO signal */
    BKS0_TM20_TRGO=6,   /*!< TM20's TRGO output state  */
    BKS0_CCL_P0=7,      /*!< CCL_P0 output state  */
    BKS0_TM20_OC00=8,   /*!< TM20's OC00 output state  */
    BKS0_TM36_OC2=9,    /*!< TM36's OC2 output state */
    BKS0_URT0_TX=12,    /*!< URT0's TX signal */
    BKS0_URT0_RX=14     /*!< URT0's RX signal */
} BKS0SrcDef;

/** 
 * @enum		BKS1SrcDef
 * @brief		declare BKS1 source
 */        
typedef enum 
{
    BKS1_Logic_1=0,     /*!< Output '1' state */
    BKS1_INT_PB=1,      /*!< INT_PB signal state */
    BKS1_INT_PD=2,      /*!< INT_PD signal state */
    BKS1_INT_BOD1=3,    /*!< BOD1 signal state */
    BKS1_TM01_TRGO=4,   /*!< TM01's TRGO signal */
    BKS1_TM16_TRGO=5,   /*!< TM16's TRGO signal */
    BKS1_CCL_P1=7,      /*!< CCL_P1 output state  */
    BKS1_TM20_OC10=8,   /*!< TM20's OC10 output state  */
    BKS1_TM36_OC3=9,    /*!< TM36's OC3 output state */
    BKS1_URT1_TX=12,    /*!< URT1's TX signal */
    BKS1_URT1_RX=14     /*!< URT1's RX signal */
} BKS1SrcDef;

/** 
 * @enum		BKS2SrcDef
 * @brief		declare BKS2 source
 */        
typedef enum 
{
    BKS2_Logic_1=0,     /*!< Output '1' state */
    BKS2_SPI0_MOSI=3,   /*!< SPI0's MOSI output state */
    BKS2_TM36_TRGO=6    /*!< TM36's TRGO signal */
} BKS2SrcDef;
#endif

#if defined(MG32_1ST)
/** 
 * @enum		IRCLKSrcDef
 * @brief		declare IRCLK source
 */        
typedef enum 
{
    IRCLK_Logic_0=0,	/*!< Output '0' state */
    IRCLK_TM00_CKO=1,   /*!< TM00's CKO signal */
    IRCLK_TM01_CKO=2,   /*!< TM01's CKO signal */
    IRCLK_TM10_CKO=3,   /*!< TM10's CKO signal */
    IRCLK_TM16_TRGO=4,  /*!< TM16's TRGO signal */
    IRCLK_URT1_TMO=5,   /*!< URT1's TMO signal */
    IRCLK_URT2_TMO=6,   /*!< URT2's TMO signal */
    IRCLK_URT3_TMO=7    /*!< URT3's TMO signal */
} IRCLKSrcDef;

/** 
 * @enum		IRDATSrcDef
 * @brief		declare IRDAT source
 */        
typedef enum 
{
    IRDAT_Logic_0=0,	/*!< Output '0' state */
    IRDAT_TM20_TRGO=1,  /*!< TM20's CKO signal */
    IRDAT_TM26_TRGO=2,  /*!< TM26's CKO signal */
    IRDAT_TM36_TRGO=3,  /*!< TM36's CKO signal */
    IRDAT_SPI0_MOSI=4,  /*!< SPIO's MOSI signal */
    IRDAT_URT1_TX=5,    /*!< URT1's TX signal */
    IRDAT_URT2_TX=6,    /*!< URT2's TX signal */
    IRDAT_URT3_TX=7     /*!< URT3's TX signal */
} IRDATSrcDef;
#endif

#if defined(MG32_2ND)
/** 
 * @enum		IRCLKSrcDef
 * @brief		declare IRCLK source
 */        
typedef enum 
{
    IRCLK_Logic_0=0,	/*!< Output '0' state */
    IRCLK_TM00_CKO=1,   /*!< TM00's CKO signal */
    IRCLK_TM01_CKO=2,   /*!< TM01's CKO signal */
    IRCLK_TM10_CKO=3,   /*!< TM10's CKO signal */
    IRCLK_TM16_TRGO=4,  /*!< TM16's TRGO signal */
    IRCLK_URT1_TMO=5    /*!< URT1's TMO signal */
} IRCLKSrcDef;

/** 
 * @enum		IRDATSrcDef
 * @brief		declare IRDAT source
 */        
typedef enum 
{
    IRDAT_Logic_0=0,	/*!< Output '0' state */
    IRDAT_TM36_TRGO=3,  /*!< TM36's CKO signal */
    IRDAT_SPI0_MOSI=4,  /*!< SPIO's MOSI signal */
    IRDAT_URT1_TX=5     /*!< URT1's TX signal */
} IRDATSrcDef;
#endif

#if defined(MG32_3RD)
/** 
 * @enum		IRCLKSrcDef
 * @brief		declare IRCLK source
 */        
typedef enum 
{
    IRCLK_Logic_0=0,	/*!< Output '0' state */
    IRCLK_TM00_CKO=1,   /*!< TM00's CKO signal */
    IRCLK_TM01_CKO=2,   /*!< TM01's CKO signal */
    IRCLK_TM10_CKO=3,   /*!< TM10's CKO signal */
    IRCLK_TM16_TRGO=4,  /*!< TM16's TRGO signal */
    IRCLK_URT1_TMO=5,   /*!< URT1's TMO signal */
    IRCLK_URT2_TMO=6    /*!< URT2's TMO signal */
} IRCLKSrcDef;

/** 
 * @enum		IRDATSrcDef
 * @brief		declare IRDAT source
 */        
typedef enum 
{
    IRDAT_Logic_0=0,	/*!< Output '0' state */
    IRDAT_TM20_TRGO=1,  /*!< TM20's CKO signal */
    IRDAT_TM26_TRGO=2,  /*!< TM26's CKO signal */
    IRDAT_TM36_TRGO=3,  /*!< TM36's CKO signal */
    IRDAT_SPI0_MOSI=4,  /*!< SPIO's MOSI signal */
    IRDAT_URT1_TX=5,    /*!< URT1's TX signal */
    IRDAT_URT2_TX=6     /*!< URT2's TX signal */
} IRDATSrcDef;
#endif

#if defined(MG32_4TH)
/** 
 * @enum		IRCLKSrcDef
 * @brief		declare IRCLK source
 */        
typedef enum 
{
    IRCLK_Logic_0=0,	/*!< Output '0' state */
    IRCLK_TM00_CKO=1,   /*!< TM00's CKO signal */
    IRCLK_TM01_CKO=2,   /*!< TM01's CKO signal */
    IRCLK_TM10_CKO=3,   /*!< TM10's CKO signal */
    IRCLK_TM16_TRGO=4,  /*!< TM16's TRGO signal */
    IRCLK_URT1_TMO=5    /*!< URT1's TMO signal */
} IRCLKSrcDef;

/** 
 * @enum		IRDATSrcDef
 * @brief		declare IRDAT source
 */        
typedef enum 
{
    IRDAT_Logic_0=0,	/*!< Output '0' state */
    IRDAT_TM20_TRGO=1,  /*!< TM20's CKO signal */
    IRDAT_TM36_TRGO=3,  /*!< TM36's CKO signal */
    IRDAT_SPI0_MOSI=4,  /*!< SPIO's MOSI signal */
    IRDAT_URT1_TX=5     /*!< URT1's TX signal */
} IRDATSrcDef;
#endif


/** 
 * @enum		OBMxFilterTypedef
 * @brief		config OBMx with clock filter function
 */        
typedef enum
{
    OBMx_FilterDisable, /*!< Disable clock filter */
    OBMx_APBCLKx3,      /*!< filter clock by APB clock x 3 */
    OBMx_APBCLKx24,     /*!< filter clock by APB clock x 8 x 3 */
    OBMx_TM00_TRGOx3    /*!< filter clock by TM00 TRGO x 3 */
} OBMxFilterTypedef;

/** 
 * @enum		OBMxOperateModeTypedef
 * @brief		config OBMx operation mode
 */        
typedef enum
{
    OBMx_LevelSwitch=0,         /*!< operate in AND mode */
    OBMx_ClearByFallingEdge=1,  /*!< accept falling edge to clear initial state */
    OBMx_SetByFallingEdge=2,    /*!< accept falling edge to set initial state */    
    OBMx_DualEdgeSwitch=3       /*!< accept falling edge to toggle initial state */
} OBMxOperateModeTypedef;

#if defined(MG32_1ST)
/** 
 * @enum		OBMxChannel0TypeDef
 * @brief		config OBMx channel 0 source
 */        
typedef enum
{
    OBMxCH0_Logic_0=0,          /*!< Output '0' state */
    OBMxCH0_INT_PA=1,           /*!< Output INT_PA state */
    OBMxCH0_INT_PC=2,           /*!< Output INT_PC state */
    OBMxCH0_TM00_CKO=4,         /*!< Output TM00_CKO state */
    OBMxCH0_TM10_CKO=5,         /*!< Output TM10_CKO state */
    OBMxCH0_TM20_CKO=6,         /*!< Output TM20_CKO state */
    OBMxCH0_TM36_CKO=7,         /*!< Output TM36_CKO state */
    OBMxCH0_TM20_OC00=8,        /*!< Output TM20_OC00 state */
    OBMxCH0_TM36_OC00=9,        /*!< Output TM36_OC00 state */
    OBMxCH0_TM36_OC2=10,        /*!< Output TM20_OC2 state */
    OBMxCH0_OBM_I0=12,          /*!< Output OBMx Break Signal Input channel 0 state */
    OBMxCH0_ITR6=13             /*!< Output ITR6 state */
} OBMxChannel0TypeDef;

/** 
 * @enum		OBMxChannel1TypeDef
 * @brief		config OBMx channel 1 source
 */        
typedef enum
{
    OBMxCH1_Logic_0=0,          /*!< Output '0' state */
    OBMxCH1_INT_PB=1,           /*!< Output INT_PB state */
    OBMxCH1_INT_PD=2,           /*!< Output INT_PD state */
    OBMxCH1_TM01_CKO=4,         /*!< Output TM01_CKO state */
    OBMxCH1_TM16_CKO=5,         /*!< Output TM16_CKO state */
    OBMxCH1_TM26_CKO=6,         /*!< Output TM26_CKO state */
    OBMxCH1_TM20_OC01=8,        /*!< Output TM20_OC01 state */
    OBMxCH1_TM36_OC01=9,        /*!< Output TM36_OC01 state */
    OBMxCH1_TM36_OC3=10,        /*!< Output TM20_OC3 state */
    OBMxCH1_OBM_I1=12,          /*!< Output OBMx Break Signal Input channel 1 state */
    OBMxCH1_ITR7=13,            /*!< Output ITR7 state */
    OBMxCH1_ICKO_INT=14         /*!< Output ICKO_INT state */
} OBMxChannel1TypeDef;
#endif

#if defined(MG32_2ND)
/** 
 * @enum		OBMxChannel0TypeDef
 * @brief		config OBMx channel 0 source
 */        
typedef enum
{
    OBMxCH0_Logic_0=0,          /*!< Output '0' state */
    OBMxCH0_INT_PA=1,           /*!< Output INT_PA state */
    OBMxCH0_INT_PC=2,           /*!< Output INT_PC state */
    OBMxCH0_TM00_CKO=4,         /*!< Output TM00_CKO state */
    OBMxCH0_TM10_CKO=5,         /*!< Output TM10_CKO state */
    OBMxCH0_TM36_CKO=7,         /*!< Output TM36_CKO state */
    OBMxCH0_TM36_OC00=9,        /*!< Output TM36_OC00 state */
    OBMxCH0_TM36_OC2=10,        /*!< Output TM20_OC2 state */
    OBMxCH0_OBM_I0=12,          /*!< Output OBMx Break Signal Input channel 0 state */
    OBMxCH0_ITR6=13             /*!< Output ITR6 state */
} OBMxChannel0TypeDef;

/** 
 * @enum		OBMxChannel1TypeDef
 * @brief		config OBMx channel 1 source
 */        
typedef enum
{
    OBMxCH1_Logic_0=0,          /*!< Output '0' state */
    OBMxCH1_INT_PB=1,           /*!< Output INT_PB state */
    OBMxCH1_INT_PD=2,           /*!< Output INT_PD state */
    OBMxCH1_TM01_CKO=4,         /*!< Output TM01_CKO state */
    OBMxCH1_TM16_CKO=5,         /*!< Output TM16_CKO state */
    OBMxCH1_TM36_OC01=9,        /*!< Output TM36_OC01 state */
    OBMxCH1_TM36_OC3=10,        /*!< Output TM20_OC3 state */
    OBMxCH1_OBM_I1=12,          /*!< Output OBMx Break Signal Input channel 1 state */
    OBMxCH1_ITR7=13,            /*!< Output ITR7 state */
    OBMxCH1_ICKO_INT=14         /*!< Output ICKO_INT state */
} OBMxChannel1TypeDef;
#endif

#if defined(MG32_3RD)
/** 
 * @enum		OBMxChannel0TypeDef
 * @brief		config OBMx channel 0 source
 */        
typedef enum
{
    OBMxCH0_Logic_0=0,          /*!< Output '0' state */
    OBMxCH0_INT_PA=1,           /*!< Output INT_PA state */
    OBMxCH0_INT_PC=2,           /*!< Output INT_PC state */
    OBMxCH0_INT_PE=3,           /*!< Output INT_PE state */
    OBMxCH0_TM00_CKO=4,         /*!< Output TM00_CKO state */
    OBMxCH0_TM10_CKO=5,         /*!< Output TM10_CKO state */
    OBMxCH0_TM20_CKO=6,         /*!< Output TM20_CKO state */
    OBMxCH0_TM36_CKO=7,         /*!< Output TM36_CKO state */
    OBMxCH0_TM20_OC00=8,        /*!< Output TM20_OC00 state */
    OBMxCH0_TM36_OC00=9,        /*!< Output TM36_OC00 state */
    OBMxCH0_TM36_OC2=10,        /*!< Output TM20_OC2 state */
    OBMxCH0_OBM_I0=12,          /*!< Output OBMx Break Signal Input channel 0 state */
    OBMxCH0_ITR6=13             /*!< Output ITR6 state */
} OBMxChannel0TypeDef;

/** 
 * @enum		OBMxChannel1TypeDef
 * @brief		config OBMx channel 1 source
 */        
typedef enum
{
    OBMxCH1_Logic_0=0,          /*!< Output '0' state */
    OBMxCH1_INT_PB=1,           /*!< Output INT_PB state */
    OBMxCH1_INT_PD=2,           /*!< Output INT_PD state */
    OBMxCH1_TM01_CKO=4,         /*!< Output TM01_CKO state */
    OBMxCH1_TM16_CKO=5,         /*!< Output TM16_CKO state */
    OBMxCH1_TM26_CKO=6,         /*!< Output TM26_CKO state */
    OBMxCH1_TM20_OC01=8,        /*!< Output TM20_OC01 state */
    OBMxCH1_TM36_OC01=9,        /*!< Output TM36_OC01 state */
    OBMxCH1_TM36_OC3=10,        /*!< Output TM20_OC3 state */
    OBMxCH1_OBM_I1=12,          /*!< Output OBMx Break Signal Input channel 1 state */
    OBMxCH1_ITR7=13,            /*!< Output ITR7 state */
    OBMxCH1_ICKO_INT=14         /*!< Output ICKO_INT state */
} OBMxChannel1TypeDef;
#endif

#if defined(MG32_4TH)
/** 
 * @enum		OBMxChannel0TypeDef
 * @brief		config OBMx channel 0 source
 */        
typedef enum
{
    OBMxCH0_Logic_0=0,          /*!< Output '0' state */
    OBMxCH0_INT_PA=1,           /*!< Output INT_PA state */
    OBMxCH0_INT_PC=2,           /*!< Output INT_PC state */
    OBMxCH0_TM00_CKO=4,         /*!< Output TM00_CKO state */
    OBMxCH0_TM10_CKO=5,         /*!< Output TM10_CKO state */
    OBMxCH0_TM20_CKO=6,         /*!< Output TM20_CKO state */
    OBMxCH0_TM36_CKO=7,         /*!< Output TM36_CKO state */
    OBMxCH0_TM20_OC00=8,        /*!< Output TM20_OC00 state */
    OBMxCH0_TM36_OC00=9,        /*!< Output TM36_OC00 state */
    OBMxCH0_TM36_OC2=10,        /*!< Output TM20_OC2 state */
    OBMxCH0_OBM_I0=12,          /*!< Output OBMx Break Signal Input channel 0 state */
    OBMxCH0_ITR6=13             /*!< Output ITR6 state */
} OBMxChannel0TypeDef;

/** 
 * @enum		OBMxChannel1TypeDef
 * @brief		config OBMx channel 1 source
 */        
typedef enum
{
    OBMxCH1_Logic_0=0,          /*!< Output '0' state */
    OBMxCH1_INT_PB=1,           /*!< Output INT_PB state */
    OBMxCH1_INT_PD=2,           /*!< Output INT_PD state */
    OBMxCH1_TM01_CKO=4,         /*!< Output TM01_CKO state */
    OBMxCH1_TM16_CKO=5,         /*!< Output TM16_CKO state */
    OBMxCH1_TM20_OC01=8,        /*!< Output TM20_OC01 state */
    OBMxCH1_TM36_OC01=9,        /*!< Output TM36_OC01 state */
    OBMxCH1_TM36_OC3=10,        /*!< Output TM20_OC3 state */
    OBMxCH1_OBM_I1=12,          /*!< Output OBMx Break Signal Input channel 1 state */
    OBMxCH1_ITR7=13,            /*!< Output ITR7 state */
    OBMxCH1_ICKO_INT=14         /*!< Output ICKO_INT state */
} OBMxChannel1TypeDef;
#endif


#if defined(MG32_3RD) || defined(MG32_4TH)
/** 
 * @enum		APB_NCOInputClockSrcDef
 * @brief		APB NCO input clock Source Definition
 */        
typedef enum
{
    APB_NCO_IHRCO=0,            /*!< NCO clock from CK_IHRCO */
    APB_NCO_CK_PLL,             /*!< NCO clock from CK_PLL */
    APB_NCO_APB,                /*!< NCO clock from CK_APB */    
    APB_NCO_CK_LS,              /*!< NCO clock from CK_LS */
    APB_NCO_TM00_TRGO,          /*!< NCO clock from TM00_TRGO */
    APB_NCO_CK0                 /*!< NCO clock from NCO_CKI */
} APB_NCOInputClockSrcDef;

/** 
 * @enum		APB_NCOOutputMode
 * @brief		APB NCO Output Mode
 */        
typedef enum
{
    APB_NCO_FDC=0,              /*!< FDC : fixed duty cycle mode */
    APB_NCO_PFM                 /*!< PFM : pulse frequency mode */
} APB_NCOOutputMode;

/** 
 * @enum		APB_NCOPFMWidtrhSelDef
 * @brief		APB NCO PFM Width Select Definition
 */        
typedef enum
{
    APB_PFM_1Clock=0,           /*!< 1 CK_NCOn clock period */
    APB_PFM_2Clock,             /*!< 2 CK_NCOn clock period */
    APB_PFM_4Clock,             /*!< 4 CK_NCOn clock period */
    APB_PFM_8Clock,             /*!< 8 CK_NCOn clock period */
    APB_PFM_16Clock,            /*!< 16 CK_NCOn clock period */
    APB_PFM_32Clock,            /*!< 32 CK_NCOn clock period */
    APB_PFM_64Clock,            /*!< 64 CK_NCOn clock period */
    APB_PFM_128Clock            /*!< 128 CK_NCOn clock period */
} APB_NCOPFMWidtrhSelDef;

#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name	Function announce
 *   		
 */ 
///@{  
void APB_TimerX_Cmd(uint32_t TMxEnBit);
void APB_ITR6_Select(APB_TimerITR6SrcDef ITR6Src);
void APB_ITR7_Select(APB_TimerITR7SrcDef ITR7Src);
///@}

#if defined(MG32_1ST) || defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
///@{
void APB_BreakSourceChannel0_Select(OBM_Struct* OBMx, BKS0SrcDef BKS0Sel);
void APB_BreakSourceChannel1_Select(OBM_Struct* OBMx, BKS1SrcDef BKS1Sel);
void APB_BreakSourceChannel2_Select(OBM_Struct* OBMx, BKS2SrcDef BKS2Sel);
void APB_InverseBKS0_Cmd(OBM_Struct* OBMx, FunctionalState NewState);
void APB_InverseBKS1_Cmd(OBM_Struct* OBMx, FunctionalState NewState);
void APB_InverseBKS2_Cmd(OBM_Struct* OBMx, FunctionalState NewState);
void APB_OBMxOpMode_Select(OBM_Struct* OBMx, OBMxOperateModeTypedef OPMode);
DRV_Return APB_GetOBMxOutputState(OBM_Struct* OBMx);
void APB_InverseOBMxOutput_Cmd(OBM_Struct* OBMx, FunctionalState NewState);
void APB_OutputFilter_Select(OBM_Struct* OBMx, OBMxFilterTypedef FilterClks);
DRV_Return APB_GetOBMxSwitchState(OBM_Struct* OBMx);	
void APB_SetOBMxInitState(OBM_Struct* OBMx, BitAction CurSta);
///@}

///@{
DRV_Return APB_GetOBMxInitState(OBM_Struct* OBMx);	
void APB_OutputChannel0Source_Select(OBM_Struct* OBMx, OBMxChannel0TypeDef OBM0LSSel);
void APB_OutputChannel1Source_Select(OBM_Struct* OBMx, OBMxChannel1TypeDef OBM0HSSel);
void APB_InverseOutputChannel0_Cmd(OBM_Struct* OBMx, FunctionalState NewState);
void APB_InverseOutputChannel1_Cmd(OBM_Struct* OBMx, FunctionalState NewState);
///@}
#endif

///@{
void APB_IRCLK_Select(IRCLKSrcDef IRCLKSel);
void APB_IRDAT_Select(IRDATSrcDef IRDATSel);
void APB_InverseIRCLK_Cmd(FunctionalState NewState);
void APB_InverseIRDAT_Cmd(FunctionalState NewState);
///@}

#if defined(MG32_3RD) || defined(MG32_4TH)
///@{
void APB_NCOClockSource_Select(APB_NCOInputClockSrcDef NCOClkSrc);
void APB_NCOOutputMode_Select(APB_NCOOutputMode NCOOutMode);
void APB_NCOInverseOutput_Cmd(FunctionalState NewState);
void APB_NCO_Cmd(FunctionalState NewState);
void APB_NCOPFMWidth_Select(APB_NCOPFMWidtrhSelDef NCOPFMWidth);
void APB_NCOSetINC(uint32_t NCOINCV);
void APB_NCOSetACC(uint32_t NCOACCV);
DRV_Return APB_NCOGetOutputState(void);
///@}
#endif
///@{
void APB_IT_Config(APB_Struct* APBx, uint32_t ITsrc, FunctionalState NewState);
void APB_ITEA_Cmd(APB_Struct* APBx, FunctionalState NewState);
DRV_Return APB_GetSingleFlagStatus(APB_Struct* APBx, uint32_t ITSrc);
uint32_t APB_GetAllFlagStatus(APB_Struct* APBx);
void APB_ClearFlag(APB_Struct* APBx, uint32_t APB_ITSrc);
///@}

#ifdef __cplusplus
}
#endif

#endif

