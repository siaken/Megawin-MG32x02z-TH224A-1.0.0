/**
 *******************************************************************************
 *
 * @file        MG32x02z_PW_DRV.H
 *
 * @brief       This is the C code format driver head file for PW module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.25
 * @date        2022/09/14
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2021 Megawin Technology Co., Ltd.
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
 
 
#include "MG32x02z__Common_DRV.h"
#include "MG32x02z_PW.h"


#ifndef _MG32x02z_PW_DRV_H
/*!< _MG32x02z_PW_DRV_H */ 
#define _MG32x02z_PW_DRV_H


/*! @name 
*/
/* @{ */ 
#define PW_PORF     PW_STA_PORF_mask_w                          /*!< Power-On reset status flag */
#define PW_BOD0F    PW_STA_BOD0F_mask_w                         /*!< Brown-Out detect BOD0 status flag  */
#define PW_BOD1F    PW_STA_BOD1F_mask_w                         /*!< Brown-Out detect BOD1 interrupt flag */
#if defined(PW_STA_BOD2F_mask_w)
#define PW_BOD2F    PW_STA_BOD2F_mask_w                         /*!< Brown-Out detect BOD2 interrupt flag */
#endif
#define PW_WKF      PW_STA_WKF_mask_w                           /*!< System received wakeup event flag */
#if (!defined(PW_STA_BOD2F_mask_w))
#define PW_ALLF     PW_PORF | PW_BOD0F | PW_BOD1F | PW_WKF              /*!< All event and interrupt flag */
#endif
#if (defined(PW_STA_BOD2F_mask_w))
#define PW_ALLF     PW_PORF | PW_BOD0F | PW_BOD1F | PW_BOD2F | PW_WKF   /*!< All event and interrupt flag */
#endif

#define PW_INT_WK       PW_INT_WK_IE_mask_w         /*!< System received wakeup event interrupt enable bit */
#if (defined(PW_INT_BOD2_IE_mask_w))
#define PW_INT_BOD2     PW_INT_BOD2_IE_mask_w       /*!< BOD2 interrupt enable */
#endif
#define PW_INT_BOD1     PW_INT_BOD1_IE_mask_w       /*!< BOD1 interrupt enable */
#define PW_INT_BOD0     PW_INT_BOD0_IE_mask_w       /*!< BOD0 interrupt enable */
/* @} */



#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

/*! @enum   PW_WakeUpDly_TypeDef
    @brief  MCU wake up delay selection
*/ 
typedef enum
{   
    PW_WK_15us      = 0,    /*!< Wakeup delay time 15us */
    PW_WK_45us      = 1,    /*!< Wakeup delay time 45us */
    PW_WK_75us      = 2,    /*!< Wakeup delay time 65us */
    PW_WK_135us     = 3     /*!< Wakeup delay time 135us */
}PW_WakeUpDly_TypeDef;



/*! @enum   PW_WakeUpMode_TypeDef
    @brief  MCU wakeup mode selection
*/
typedef enum
{
    PW_Normal_SleepMode = 0,    /*!< Wakeup from normal SLEEP mode */
    PW_LowPower_SleepMode = 1   /*!< Wakeup from low power SLEEP mode */
}PW_WakeUpMode_TypeDef;


/*! @enum   PW_BOD1_TH_TypeDef
    @brief  BOD1 detect voltage threshold select
*/ 
typedef enum
{   
    PW_BOD1_2V0     = 0,    /*!< BOD1 detect voltage is 2.0V */
    PW_BOD1_2V4     = 1,    /*!< BOD1 detect voltage is 2.4V */
    PW_BOD1_3V7     = 2,    /*!< BOD1 detect voltage is 3.7V */
    PW_BOD1_4V2     = 3     /*!< BOD1 detect voltage is 4.2V */
}PW_BOD1_TH_TypeDef;


/*! @enum   PW_BODx_TRGS_TypeDef
    @brief  BODx Interrupt trigger selection.
*/
typedef enum
{   
    PW_BODx_Reserved    = 0,    /*!< BODx not interrupt trigger */
    PW_BODx_RisingEdge  = 1,    /*!< BODx interrupt trigger at rising edge */
    PW_BODx_FallingEdge = 2,    /*!< BODx interrupt trigger at falling edge */
    PW_BODx_DualEdge    = 3     /*!< BODx interrupt trigger at rising edge and falling edge  */
}PW_BODx_TRGS_TypeDef;


/*! @enum   PW_LowPowerLdo_TypeDef
    @brief  Low power LDO level selection
*/
typedef enum
{   
    PW_LV0      = 0,    /*!< Low power LDO is Lowest level */
    PW_LV1      = 1,    /*!< Low power LDO is the same PW_LV2 */
    PW_LV2      = 2,    /*!< Low power LDO is the same PW_LV1 */
    PW_LV3      = 3     /*!< Low power LDO is highest level */
}PW_LowPowerLdo_TypeDef;


/*! @enum   PW_LDOMode_TypeDef
    @brief  Core voltage LDO mode selection.
*/
typedef enum
{   
    PW_Normal_LDO   = 0,    /*!< Core voltage LDO mode select normal LDO */
    PW_LowPower_LDO = 1     /*!< Core voltage LDO mode select low power LDO */
}PW_LDOMode_TypeDef;


/*! @enum   PW_WKSTP_Periph_TypeDef
    @brief  Peripheral event wakeup from STOP mode configure.
*/
typedef enum
{   
    PW_WKSTP_BOD0   = 4,    /*!< BOD0 voltage detection wakeup from STOP mode */
    PW_WKSTP_BOD1   = 5,    /*!< BOD1 voltage detection wakeup from STOP mode */
#if (defined(PW_WKSTP0_WKSTP_BOD2_mask_w))
    PW_WKSTP_BOD2   = 6,    /*!< BOD2 voltage detection wakeup from STOP mode */
#endif
#if (defined(PW_WKSTP0_WKSTP_CMP0_mask_w))
    PW_WKSTP_CMP0   = 16,   /*!< CMP0 voltage detection wakeup from STOP mode */
#endif
#if (defined(PW_WKSTP0_WKSTP_CMP1_mask_w))
    PW_WKSTP_CMP1   = 17,   /*!< CMP1 voltage detection wakeup from STOP mode */
#endif
#if (defined(PW_WKSTP0_WKSTP_CMP2_mask_w))
    PW_WKSTP_CMP2   = 18,   /*!< CMP2 voltage detection wakeup from STOP mode */
#endif
#if (defined(PW_WKSTP0_WKSTP_CMP2_mask_w))
    PW_WKSTP_CMP3   = 19,   /*!< CMP3 voltage detection wakeup from STOP mode */
#endif 
#if (defined(USB_TYPE))
    PW_WKSTP_USB    = 24,   /*!< USB module event wakeup from STOP mode */
#endif
    PW_WKSTP_I2C0   = 40,   /*!< I2C0 module event wakeup from STOP mode */
#if (defined(PW_WKSTP1_WKSTP_I2C0_mask_w) && defined(PW_WKSTP1_WKSTP_I2C1_mask_w))
    PW_WKSTP_I2C1   = 41,    /*!< I2C1 module event wakeup from STOP mode */
#endif
    PW_WKSTP_RTC    = 37,   /*!< RTC module event wakeup from STOP mode */
    PW_WKSTP_IWDT   = 38   /*!< IWDT module event wakeup from STOP mode */
}PW_WKSTP_Periph_TypeDef;


/*! @enum   PW_STP_Periph_TypeDef
    @brief  Peripheral stop mode continuous run configure.
*/
typedef enum
{
    PW_STPPO_POR    = PW_CR1_STP_POR_mask_w,    /*!< POR power-on configuration after enter STOP mode */
    PW_STPPO_BOD0   = PW_CR1_STP_BOD0_mask_w,   /*!< BOD0 power-on configuration after enter STOP mode */
#if (defined(PW_CR1_STP_BOD2_mask_w))
    PW_STPPO_BOD2   = PW_CR1_STP_BOD2_mask_w,   /*!< BOD2 power-on configuration after enter STOP mode */
#endif
#if (defined(PW_CR1_STP_CMP0_mask_w))
    PW_STPPO_CMP0   = PW_CR1_STP_CMP0_mask_w,   /*!< CMP0 power-on configuration after enter STOP mode */
#endif
#if (defined(PW_CR1_STP_CMP1_mask_w))
    PW_STPPO_CMP1   = PW_CR1_STP_CMP1_mask_w,   /*!< CMP1 power-on configuration after enter STOP mode */
#endif
#if (defined(PW_CR1_STP_CMP2_mask_w))
    PW_STPPO_CMP2   = PW_CR1_STP_CMP2_mask_w,   /*!< CMP2 power-on configuration after enter STOP mode */
#endif
#if (defined(PW_CR1_STP_CMP3_mask_w))
    PW_STPPO_CMP3   = PW_CR1_STP_CMP3_mask_w,   /*!< CMP3 power-on configuration after enter STOP mode */
#endif
#if (defined(USB_TYPE))
    PW_STPPO_USB    = PW_CR1_STP_USB_mask_w,    /*!< USB power-on configuration after enter STOP mode */
#endif
    PW_STPPO_BOD1   = PW_CR1_STP_BOD1_mask_w    /*!< BOD1 power-on configuration after enter STOP mode */
}PW_STP_Periph_TypeDef;


#if (defined(PW_CR1_SLP_CMP0_mask_w))
/*! @enum   PW_SLP_Periph_TypeDef
    @brief  Peripheral sleep mode continuous run configure.
*/
typedef enum
{   
#if (defined(PW_CR1_SLP_CMP1_mask_w))
    PW_SLPPO_CMP1   = PW_CR1_SLP_CMP1_mask_w,   /*!< CMP1 power-on configuration after enter SLEEP mode */
#endif
#if (defined(PW_CR1_SLP_CMP2_mask_w))
    PW_SLPPO_CMP2   = PW_CR1_SLP_CMP2_mask_w,   /*!< CMP2 power-on configuration after enter SLEEP mode */
#endif
#if (defined(PW_CR1_SLP_CMP3_mask_w))
    PW_SLPPO_CMP3   = PW_CR1_SLP_CMP3_mask_w,   /*!< CMP3 power-on configuration after enter SLEEP mode */
#endif
#if (defined(USB_TYPE))
    PW_SLPPO_USB    = PW_CR1_SLP_USB_mask_w,    /*!< USB power-on configuration after enter SLEEP mode */
#endif
    PW_SLPPO_CMP0   = PW_CR1_SLP_CMP0_mask_w,   /*!< CMP0 power-on configuration after enter SLEEP mode */
}PW_SLP_Periph_TypeDef;
#endif

/** @name   Function rename
 *       
 */ 
#define PW_PeriphStopModeWakeUp_Config      PW_PeriphSTOPModeWakeUp_Config
#define PW_StopModeLDO_Select               PW_STOPModeLDO_Select
#define PW_OnModeLDO_Select                 PW_ONModeLDO_Select
#define PW_PeriphStopModeContinuous_Config  PW_PeriphSTOPModeContinuous_Config
#define PW_PeriphSleepModeContinuous_Config PW_PeriphSLEEPModeContinuous_Config

/**
 * @name	Function announce
 *
 */ 
///@{  
uint32_t PW_GetAllFlagStatus (void);
DRV_Return PW_GetSingleFlagStatus (uint32_t PW_ITSrc);
void PW_ClearFlag (uint32_t PW_ITSrc);
void PW_IT_Config (uint32_t PW_ITSrc, FunctionalState NewState);
uint32_t PW_GetITStatus (void);
void PW_ITEA_Cmd (FunctionalState NewState);

void PW_PeriphSTOPModeWakeUp_Config (PW_WKSTP_Periph_TypeDef WKSTP_Periph, FunctionalState NewState);
void PW_WakeUpDelay_Select (PW_WakeUpDly_TypeDef WakeUpDly);
#if defined(PW_CR0_WKSLP_MDS_mask_w)
void PW_WakeUpMode_Select (PW_WakeUpMode_TypeDef WakeUpModeSelect);
#endif
DRV_Return PW_GetWakeUpMode (void);

void PW_BOD1Threshold_Select (PW_BOD1_TH_TypeDef BOD1_TH);
void PW_BOD1Trigger_Select (PW_BODx_TRGS_TypeDef BOD1_TRGS);
void PW_BOD1_Cmd (FunctionalState NewState);
void PW_BOD0_Cmd (FunctionalState NewState);
DRV_Return PW_GetBod1Status (void);
#if defined(PW_CR0_BOD2_EN_mask_w) 
void PW_BOD2Trigger_Select (PW_BODx_TRGS_TypeDef BOD2_TRGS);
void PW_BOD2_Cmd (FunctionalState NewState);
DRV_Return PW_GetBod2Status (void);
#endif

void PW_VoltageBuffer (FunctionalState NewState);
void PW_STOPModeLDO_Select (PW_LDOMode_TypeDef LdoSelect);
void PW_ONModeLDO_Select (PW_LDOMode_TypeDef LdoSelect);

void PW_PeriphSTOPModeContinuous_Config (PW_STP_Periph_TypeDef STP_Periph,FunctionalState NewState);
#if defined(PW_CR1_SLP_CMP0_mask_w)
void PW_PeriphSLEEPModeContinuous_Config (PW_SLP_Periph_TypeDef SLP_Periph, FunctionalState NewState);
#endif
///@}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif  //_MG32x02z_PW_DRV_H

