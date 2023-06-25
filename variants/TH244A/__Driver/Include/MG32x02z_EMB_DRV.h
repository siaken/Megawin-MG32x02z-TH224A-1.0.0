/**
 ******************************************************************************
 *
 * @file        MG32x02z_EMB_DRV.h
 *
 * @brief       This is the C code format driver head file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V2.23
 * @date        2021/09/07
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
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



#ifndef __MG32x02z_EMB_DRV_H
#define __MG32x02z_EMB_DRV_H
//#define _MG32x02z_EMB_DRV_H_VER                            0.01



/* Includes ------------------------------------------------------------------*/
     
#include "MG32x02z__Common_DRV.h" 
#include "MG32x02z_EMB.h"

#define EMB_IT_CmdCmp   EMB_WPE | EMB_BWE               /*!< EMB control interrupt driver compare definitions.    */
#define EMB_IT_FlagCmp  EMB_WPE | EMB_BWE | EMB_BUSY    /*!< EMB read / write flag relationship driver compare definitions   */
#define EMB_WPE         EMB_STA_WPEF_mask_w             /*!< EMB WPE interrupt / flag relationship control member    */
#define EMB_BUSY        EMB_STA_BUSYF_mask_w            /*!< EMB Busy flag relationship control member */

 
#define EMB_CMP_SWEN    EMB_BW1_SWEN | EMB_BW0_SWEN | EMB_ALE2_SWEN | EMB_ALE_SWEN | EMB_CE_SWEN /*!< Compare EMB software control enable / disable member definitions */ 
#define EMB_BW1_SWEN    EMB_CR1_BW1_SWEN_mask_w     /*!< EMB software control enable/disable member definitions */
#define EMB_BW0_SWEN    EMB_CR1_BW0_SWEN_mask_w     /*!< EMB software control enable/disable member definitions */
#define EMB_ALE2_SWEN   EMB_CR1_ALE2_SWEN_mask_w    /*!< EMB software control enable/disable member definitions */
#define EMB_ALE_SWEN    EMB_CR1_ALE_SWEN_mask_w     /*!< EMB software control enable/disable member definitions */
#define EMB_CE_SWEN     EMB_CR1_CE_SWEN_mask_w      /*!< EMB software control enable/disable member definitions */
 
#define EMB_CMP_SWO     EMB_BW1_SWO | EMB_BW0_SWO | EMB_ALE2_SWO | EMB_ALE_SWO | EMB_CE_SWO /*!< Compare EMB software control member definitions */ 
#define EMB_BW1_SWO     EMB_CR1_BW1_SWO_mask_w      /*!< EMB software control member definitions */
#define EMB_BW0_SWO     EMB_CR1_BW0_SWO_mask_w      /*!< EMB software control member definitions */
#define EMB_ALE2_SWO    EMB_CR1_ALE2_SWO_mask_w     /*!< EMB software control member definitions */
#define EMB_ALE_SWO     EMB_CR1_ALE_SWO_mask_w      /*!< EMB software control member definitions */
#define EMB_CE_SWO      EMB_CR1_CE_SWO_mask_w       /*!< EMB software control member definitions */
 
#define EMB_CMP_BSWP    EMB_MA_SWP                  /*!< Compare EMB Signal swap enable / disable member definitions */
#define EMB_MA_SWP      EMB_CR1_MA_SWAP_mask_w      /*!< EMB signal swap enable/disable member defineitions */

#define EMB_CMP_INV     EMB_CLK_INV|EMB_ALE2_INV|EMB_ALE_INV|EMB_CE_INV /*!< Compare EMB Signal inverse enable / disable member definitions */
#define EMB_CLK_INV     EMB_CR1_CLK_INV_mask_w      /*!< EMB signal inverse enable/disable member defineitions */
#define EMB_ALE2_INV    EMB_CR1_ALE2_INV_mask_w     /*!< EMB signal inverse enable/disable member defineitions */
#define EMB_ALE_INV     EMB_CR1_ALE_INV_mask_w      /*!< EMB signal inverse enable/disable member defineitions */
#define EMB_CE_INV      EMB_CR1_CE_INV_mask_w       /*!< EMB signal inverse enable/disable member defineitions */
 
 
#ifdef __cplusplus
extern "C" {
#endif

/*! @enum   EMB_MWE_TypeDef
    @brief  MWE output signal select definitions.
*/ 
typedef enum 
{
    EMB_MWE_WE      =   0,      /*!< MWE output signal from WE */
    EMB_MWE_TM10    =   1,      /*!< MWE output signal from Timer10 */
    EMB_MWE_TM16    =   2,      /*!< MWE output signal from Timer16 */
    EMB_MWE_TM20    =   3       /*!< MWE output signal from Timer20 */
}EMB_MWE_TypeDef;

/*! @enum   EMB_MOE_TypeDef
    @brief  MDE output signal select definitions.
*/ 
typedef enum
{
    EMB_MOE_OE      =   0,      /*!< MWE output signal from OE */
    EMB_MOE_TM10    =   1,      /*!< MWE output signal from Timer10 */
    EMB_MOE_TM16    =   2,      /*!< MWE output signal from Timer16 */
    EMB_MOE_TM20    =   3       /*!< MWE output signal from Timer20 */
}EMB_MOE_TypeDef;

/*! @enum   EMB_ALES_TypeDef
    @brief  ALE/ALE2 setup time select definitions.
*/ 
typedef enum
{
    EMB_ALES_0MCLK  =   0x00000000,     /*!< ALE/ALE2 setup time is 0 MCLK */
    EMB_ALES_1MCLK  =   0x00000001      /*!< ALE/ALE2 setup time is 1 MCLK */
}EMB_ALES_TypeDef; 
 
/*! @enum   EMB_ALEW_TypeDef
    @brief  ALE/ALE2 plus width select definitions.
*/ 
typedef enum
{
    EMB_ALEW_1MCLK  =   0x00000000,     /*!< ALE/ALE2 plus width is 1 MCLK */
    EMB_ALEW_2MCLK  =   0x00000010,     /*!< ALE/ALE2 plus width is 2 MCLK */     
    EMB_ALEW_3MCLK  =   0x00000020,     /*!< ALE/ALE2 plus width is 3 MCLK */
    EMB_ALEW_4MCLK  =   0x00000030      /*!< ALE/ALE2 plus width is 4 MCLK */
}EMB_ALEW_TypeDef;

/*! @enum   EMB_ALEH_TypeDef
    @brief  ALE/ALE2 hold time select definitions.
*/ 
typedef enum
{
    EMB_ALEH_0MCLK  =   0x00000000,     /*!< ALE/ALE2 hold time is 0 MCLK */
    EMB_ALEH_1MCLK  =   0x00000100      /*!< ALE/ALE2 hold time is 1 MCLK */
    
}EMB_ALEH_TypeDef;

/*! @enum   EMB_ACCS_TypeDef
    @brief  Data access setup time select definitions.
*/ 
typedef enum
{
    EMB_ACCS_0MCLK  =   0x00000000,     /*!< Data access setup time is 0 MCLK */
    EMB_ACCS_1MCLK  =   0x00001000      /*!< Data access setup time is 1 MCLK */
    
}EMB_ACCS_TypeDef;

/*! @enum   EMB_ACCW_TypeDef
    @brief  Data access time select definitions.
*/ 
typedef enum
{
    EMB_ACCW_1MCLK   =   0x00000000,    /*!< Data access time is 1 MCLK */
    EMB_ACCW_2MCLK   =   0x00010000,    /*!< Data access time is 2 MCLK */
    EMB_ACCW_3MCLK   =   0x00020000,    /*!< Data access time is 3 MCLK */
    EMB_ACCW_4MCLK   =   0x00030000,    /*!< Data access time is 4 MCLK */
    EMB_ACCW_5MCLK   =   0x00040000,    /*!< Data access time is 5 MCLK */
    EMB_ACCW_6MCLK   =   0x00050000,    /*!< Data access time is 6 MCLK */
    EMB_ACCW_7MCLK   =   0x00060000,    /*!< Data access time is 7 MCLK */
    EMB_ACCW_8MCLK   =   0x00070000,    /*!< Data access time is 8 MCLK */
    EMB_ACCW_9MCLK   =   0x00080000,    /*!< Data access time is 9 MCLK */
    EMB_ACCW_10MCLK  =   0x00090000,    /*!< Data access time is 10 MCLK */
    EMB_ACCW_11MCLK  =   0x000A0000,    /*!< Data access time is 11 MCLK */
    EMB_ACCW_12MCLK  =   0x000B0000,    /*!< Data access time is 12 MCLK */
    EMB_ACCW_13MCLK  =   0x000C0000,    /*!< Data access time is 13 MCLK */
    EMB_ACCW_14MCLK  =   0x000D0000,    /*!< Data access time is 14 MCLK */
    EMB_ACCW_15MCLK  =   0x000E0000,    /*!< Data access time is 15 MCLK */
    EMB_ACCW_16MCLK  =   0x000F0000,    /*!< Data access time is 16 MCLK */
}EMB_ACCW_TypeDef;

/*! @enum   EMB_ACCH_TypeDef
    @brief  Data access hold time select definitions.
*/ 
typedef enum
{   
    EMB_ACCH_0MCLK  =   0x00000000,     /*!< Data access hold time is 0 MCLK. */
    EMB_ACCH_1MCLK  =   0x00100000      /*!< Data access hold time is 1 MCLK. */
    
}EMB_ACCH_TypeDef;

/*! @enum   EMB_MCLK_TypeDef
    @brief  EMB output clock MCK prescaler select definitions.
*/ 
typedef enum
{
    EMB_PREMCLK_1   =   0,      /*!< MCK prescaler is 1 */
    EMB_PREMCLK_2   =   1,      /*!< MCK prescaler is 2 */
    EMB_PREMCLK_3   =   2,      /*!< MCK prescaler is 3 */
    EMB_PREMCLK_4   =   3,      /*!< MCK prescaler is 4 */
    EMB_PREMCLK_5   =   4,      /*!< MCK prescaler is 5 */
    EMB_PREMCLK_6   =   5,      /*!< MCK prescaler is 6 */
    EMB_PREMCLK_7   =   7       /*!< MCK prescaler is 7 */
}EMB_MCLK_TypeDef;

/*! @enum   EMB_RWSignalMode_TypeDef
    @brief  EMB read / write signal mode select definitions.
*/ 
typedef enum
{
    EMB_TOGGLE = 0,             /*!< Read / write signal is high to low change. */
    EMB_LOW = 1                 /*!< Read / Write signal is low during read / write access.*/
}EMB_RWSignalMode_TypeDef;

/*! @enum   EMB_CEMode_TypeDef
    @brief  CE pin output signal select definitions.
*/
typedef enum
{
    EMB_CE   =   0,             /*!< CE pin output signal is CE. */
    EMB_ALE  =   1,             /*!< CE pin output signal is ALE. */             
    EMB_ALE2 =   2              /*!< CE pin output signal is ALE2. */
}EMB_CEMode_TypeDef;

/*! @enum   EMB_ADRBIT_TypeDef
    @brief  Address signal bit select definitions.
*/
typedef enum
{
    EMB_AddressBit_16 =   EMB_CR0_ADR_SEL_16bit_w,  /*!< Address is 16 bit.*/
    EMB_AddressBit_24 =   EMB_CR0_ADR_SEL_24bit_w,  /*!< Address is 24 bit.*/
    EMB_AddressBit_30 =   EMB_CR0_ADR_SEL_30bit_w,  /*!< Address is 30 bit.*/
}EMB_ADRBIT_TypeDef;

/*! @enum   EMB_BusMode_TypeDef
    @brief  Address signal and data signal mode select definitions.
*/
typedef enum
{
    EMB_BUS_Multiplex = EMB_CR0_BUS_MDS_multiplex_w,    /*!< Address signal and data signal is multiplex. */
    EMB_BUS_Separated = EMB_CR0_BUS_MDS_separated_w     /*!< Address signal and data signal is sep */
}EMB_BusMode_TypeDef;

/*! @enum   EMB_ALE2Cmd_TypeDef
    @brief  EMB two address phase timing mode enable or disable select definitions.
*/
typedef enum
{
    EMB_ALE2_DISABLE = EMB_CR0_ADR_TWO_disable_w,   /*!< EMB two address phase timing mode disable. */
    EMB_ALE2_ENABLE = EMB_CR0_ADR_TWO_enable_w,     /*!< EMB two address phase timing mode disable. */
}EMB_ALE2Cmd_TypeDef;


/*! @enum  EMB_ALE2Mode_TypeDef
    @brief ALE2 mode select definitions.
*/
typedef enum
{
    EMB_ALE2Mode_ALE2 = EMB_CR0_ALE2_MDS_ale2_w,    /*!< 2nd phase address latch enable*/
    EMB_ALE2Mode_ALE = EMB_CR0_ALE2_MDS_ale_w       /*!< same as ALE timing.*/
}EMB_ALE2Mode_TypeDef;


/*! @enum   EMB_WriteMode_TypeDef
    @brief  EMB write mode select definitions.
*/
typedef enum
{
    EMB_Write_Disable       =   EMB_CR0_WEN_disable_w,    /*!< EMB write is diable.*/
    EMB_Write_Enable        =   EMB_CR0_WEN_enable_w,    /*!< EMB write is enable.*/  
}EMB_WriteMode_TypeDef;


/*! @enum   EMB_MA1OutputPin_TypeDef
    @brief  EMB MA1 signal output pin select definitions.
*/
typedef enum
{
    EMB_MA1_NoOutput        =   0,      /*!<No output MA1 signal. */
    EMB_MA1_OutputToMAD15   =   1,      /*!<MA1 output pin is MAD15. */
    EMB_MA1_OutputToBW1     =   2,      /*!<MA1 output pin is BW1. */
    EMB_MA1_OutputToALE2    =   3,      /*!<MA1 output pin is ALE2. */
}EMB_MA1OutputPin_TypeDef;


/*! @struct EMB_TimeStateTypeDef
    @brief  EMB access control time state member.
*/ 
 typedef struct __attribute__((packed))
{
    EMB_ALES_TypeDef EMB_ALES;   /*!< ALE/ALE2 setup time*/
    EMB_ALEW_TypeDef EMB_ALEW;   /*!< ALE/ALE2 plus width*/
    EMB_ALEH_TypeDef EMB_ALEH;   /*!< ALE/ALE2 hold time*/
    EMB_ACCS_TypeDef EMB_ACCS;   /*!< Data access setup time*/
    EMB_ACCW_TypeDef EMB_ACCW;   /*!< Data access time*/
    EMB_ACCH_TypeDef EMB_ACCH;   /*!< Data access hold time*/
}EMB_TimeStateTypeDef;
 

/*! @struct EMB_AddressDataTypeDef
    @brief  EMB address and data control member.
*/
typedef struct __attribute__((packed))
{
    EMB_ADRBIT_TypeDef      EMB_AddressBit;     /*!< EMB address bit select. */
    EMB_BusMode_TypeDef     EMB_BusMode;        /*!< EMB address and data bus mode select.*/      
    EMB_ALE2Cmd_TypeDef     EMB_ALE2_EN;        /*!< EMB ALE2 control */
    EMB_ALE2Mode_TypeDef    EMB_ALE2Mode;       /*!< EMB ALE2 mode control if ALE2 select.*/
}EMB_AddressDataTypeDef;



void EMB_Cmd(FunctionalState EMB_EN);

#if defined(MG32_1ST)
void EMB_Synchonous_Cmd(FunctionalState EMB_SYNC_Cmd);
#endif

void EMB_AddressDataBusMode_Config( EMB_AddressDataTypeDef* EMB_AddressDataMode);
void EMB_WriteMode_Select(EMB_WriteMode_TypeDef EMB_WriteMode);

void EMB_AccessTime_Config(EMB_TimeStateTypeDef* EMB_TimeState);

void EMB_IT_Cmd(uint32_t EMB_IT, FunctionalState EMB_IT_State);
void EMB_ITEA_Cmd(FunctionalState EMB_ITEA_State);
DRV_Return EMB_GetSingleFlagStatus(uint32_t EMB_Flag);
uint32_t EMB_GetAllFlagStatus(void);
void EMB_ClearFlag(uint32_t EMB_Flag);

DRV_Return EMB_SignalSWAP_Cmd(uint32_t EMB_SWAPSignal , FunctionalState EMB_SWAPSignal_Status);
DRV_Return EMB_SignalInverse_Cmd(uint32_t EMD_InverseSignal , FunctionalState EMB_InverseSignal_Status);
DRV_Return EMB_SignalSW_Cmd(uint32_t EMB_SWSignal ,FunctionalState EMB_SignalSW_Status);
DRV_Return EMB_SendSignalStatus_SW(uint32_t EMB_SWSignal ,BitAction EMB_SWSingal_Status);
void EMB_MWESignal_Select(EMB_MWE_TypeDef EMB_MWE);
void EMB_MOESignal_Select(EMB_MOE_TypeDef EMB_MOE);
void EMB_MCLKPreescaler_Select(EMB_MCLK_TypeDef EMB_MCLK);
void EMB_WESignalMode_Select(EMB_RWSignalMode_TypeDef EMB_WE);
void EMB_OESignalMode_Select(EMB_RWSignalMode_TypeDef EMB_OE);
void EMB_CEMode_Select(EMB_CEMode_TypeDef EMB_CE);
void EMB_MA1SignalOutputPin_Select(EMB_MA1OutputPin_TypeDef EMB_MA1_PIN);

void EMB_DMA_Cmd( FunctionalState EMB_DMAState);



#ifdef __cplusplus
}
#endif

#endif


