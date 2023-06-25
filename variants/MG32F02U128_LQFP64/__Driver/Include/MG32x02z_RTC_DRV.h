/**
 *******************************************************************************
 *
 * @file        MG32x02z_RTC_DRV.h
 *
 * @brief       This is the C code format driver head file for the RTC module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.11
 * @date        2018/05/30
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2018 Megawin Technology Co., Ltd.
 *              All rights reserved.
 *
 *******************************************************************************
 * @par 		Disclaimer 
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
#include "MG32x02z__Common_DRV.h"
#include "MG32x02z_RTC.h"

#ifndef _MG32x02z_RTC_DRV_H
/*!< _MG32x02z_RTC_DRV_H */ 
#define _MG32x02z_RTC_DRV_H


/*! @name 
*/
/* @{ */ 
#define RTC_RCRF    RTC_STA_RCRF_mask_w     /*!< RTC_RCR register reload finished, software capture finished or RTC_ALM register value update allowed flag */
#define RTC_TOF     RTC_STA_TOF_mask_w      /*!< RTC timer overflow interrupt flag */
#define RTC_TSF     RTC_STA_TSF_mask_w      /*!< RTC time stamp interrupt flag */
#define RTC_PCF     RTC_STA_PCF_mask_w      /*!< RTC periodic interrupt flag */
#define RTC_ALMF    RTC_STA_ALMF_mask_w     /*!< RTC alarm matched interrupt flag */
#define RTC_ALLF    (RTC_RCRF | RTC_TOF | RTC_TSF | RTC_PCF | RTC_ALMF)     /*!< RTC all flag */

#define RTC_INT_RCR     RTC_INT_RCR_IE_mask_w   /*!< RTC_RCR register reload finished, software capture finished or RTC_ALM register value update allowed interrupt enable */
#define RTC_INT_TO      RTC_INT_TIE_mask_w      /*!< RTC timer overflow/underflow interrupt enable */
#define RTC_INT_TS      RTC_INT_TS_IE_mask_w    /*!< RTC time stamp interrupt enable */
#define RTC_INT_PC      RTC_INT_PC_IE_mask_w    /*!< RTC periodic interrupt enable */
#define RTC_INT_ALM     RTC_INT_ALM_IE_mask_w   /*!< RTC alarm matched interrupt enable */

#define RTC_TF_WPEN     RTC_CR0_TF_WPEN_mask_w      /*!< RTC detect RTC_TOF flag wakeup from STOP mode enable bit */
#define RTC_PC_WPEN     RTC_CR0_PC_WPEN_mask_w      /*!< RTC detect RTC_PCF flag wakeup from STOP mode enable bit */
#define RTC_ALM_WPEN    RTC_CR0_ALM_WPEN_mask_w     /*!< RTC detect RTC_ALMF flag wakeup from STOP mode enable bit */

#define RTC_OUT_UNLOCK  RTC_CR0_OUT_LCK_mask_b1     /*!< RTC_OUT output signal initial state control */
#define RTC_OUT_MASK    RTC_CR0_OUT_STA_mask_b1     /*!< RTC_OUT output signal initial state */

#define RTC_START       RTC_CR1_RC_START_mask_b0    /*!< RTC timer counter reload and software capture start enable */
#define RTC_ALM_EN      RTC_CR0_ALM_EN_mask_b0      /*!< RTC Alarm enable bit */
#define RTC_CR0_EN      RTC_CR0_EN_mask_b0          /*!< RTC function enable bit */

/* @} */


#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

/*! @enum   RTC_CLKS_TypeDef
    @brief  RTC input clock CK_RTC source select 
*/
typedef enum   
{
    RTC_CK_LS       = 0,    /*!< RTC input clock CK_RTC source select CK_LS */
    RTC_CK_UT       = 1,    /*!< RTC input clock CK_RTC source select CK_UT */
    RTC_CK_APB      = 2,    /*!< RTC input clock CK_RTC source select CK_APB */
    RTC_TM01_TRGO   = 3     /*!< RTC input clock CK_RTC source select TM01_TRGO */
    
}RTC_CLKS_TypeDef;


/*! @enum   RTC_PDIVS_TypeDef
    @brief  RTC internal clock CK_RTC_INT input pre-divider
*/
typedef enum   
{
    RTC_PDIV_4096   = 0,    /*!< RTC internal clock CK_RTC_INT input pre-divider divided by 4096 */
    RTC_PDIV_1      = 1     /*!< RTC internal clock CK_RTC_INT input pre-divider divided by 1 */
}RTC_PDIVS_TypeDef;


/*! @enum   RTC_DIVS_TypeDef
    @brief  RTC internal clock CK_RTC_INT input divider
*/
typedef enum   
{
    RTC_DIV_1   = 0,    /*!< RTC internal clock CK_RTC_INT input divider divided by 1 */
    RTC_DIV_2   = 1,    /*!< RTC internal clock CK_RTC_INT input divider divided by 2 */
    RTC_DIV_4   = 2,    /*!< RTC internal clock CK_RTC_INT input divider divided by 4 */
    RTC_DIV_8   = 3,    /*!< RTC internal clock CK_RTC_INT input divider divided by 8 */
}RTC_DIVS_TypeDef;


/*! @enum   RTC_TS_TRGS_TypeDef
    @brief  RTC time stamp trigger edge select.
*/
typedef enum   
{
    RTC_TS_TRGS_Disable        = 0,     /*!< RTC time stamp trigger edge select disable */
    RTC_TS_TRGS_RisingEdge     = 1,     /*!< RTC time stamp trigger edge select rising edge */
    RTC_TS_TRGS_FallingEdge    = 2,     /*!< RTC time stamp trigger edge select falling edge */
    RTC_TS_TRGS_DualEdge       = 3      /*!< RTC time stamp trigger edge select dual edge */
}RTC_TS_TRGS_TypeDef;


/*! @enum   RTC_RCR_MODS_TypeDef
    @brief  RTC_RCR register control mode select.
*/
typedef enum   
{
    RTC_RCR_MOD_DirectlyCapture    = 0,    /*!< RTC_RCR register control mode select directly capture */
    RTC_RCR_MOD_DelayedCapture     = 1,    /*!< RTC_RCR register control mode select delay capture */
    RTC_RCR_MOD_ForceReload        = 2,    /*!< RTC_RCR register control mode select forced reload */
    RTC_RCR_MOD_AutoReload         = 3     /*!< RTC_RCR register control mode select auto reload */
}RTC_RCR_MODS_TypeDef;


/*! @enum   RTC_OUTS_TypeDef
    @brief  RTC signal ourput source select.
*/
typedef enum
{
    RTC_ALM     = 0,    /*!< RTC output signal select ALM */
    RTC_PC      = 1,    /*!< RTC output signal select PC */
    RTC_TS      = 2,    /*!< RTC output signal select TS */
    RTC_TO      = 3     /*!< RTC output signal select TO */
}RTC_OUTS_TypeDef;

/**
 * @name	Function announce
 *
 */ 
///@{  
void RTC_CLK_Select (RTC_CLKS_TypeDef RTC_CLKS);
void RTC_PreDivider_Select (RTC_PDIVS_TypeDef RTC_PDIV);
void RTC_Divider_Select (RTC_DIVS_TypeDef RTC_DIV);

uint32_t RTC_GetAlarmCompareValue (void);
void RTC_SetAlarmCompareValue (uint32_t RTC_ALM);
void RTC_Alarm_Cmd (FunctionalState NewState);
DRV_Return RTC_GetAlarmState (void);

uint32_t RTC_GetReloadReg (void);
uint32_t RTC_GetCaptureReg (void);
void RTC_SetReloadReg (uint32_t RTC_RCR);

void RTC_Cmd (FunctionalState NewState);
void RTC_RCR_Mode_Select (RTC_RCR_MODS_TypeDef RTC_MODS);

void RTC_StopModeWakeUpEvent_Config (uint32_t RTC_WK, FunctionalState NewState);
void RTC_OutputSignal_Select (RTC_OUTS_TypeDef RTC_OUTS);
void RTC_InitOutputSignalState_Cmd (FunctionalState NewState);

void RTC_TriggerStamp_Select (RTC_TS_TRGS_TypeDef RTC_TSS);
void RTC_TriggerStamp_SW (void);

uint32_t RTC_GetAllFlagStatus (void);
DRV_Return RTC_GetSingleFlagStatus (uint32_t RTC_Flag);
void RTC_ClearFlag (uint32_t RTC_Flag);
void RTC_IT_Config (uint32_t RTC_INT, FunctionalState NewState);
void RTC_ITEA_Cmd (FunctionalState NewState);
///@}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif  //_MG32x02z_RTC_DRV_H


