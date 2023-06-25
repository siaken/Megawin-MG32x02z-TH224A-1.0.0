/**
 ******************************************************************************
 *
 * @file        MG32x02z_RTC_MID.H
 *
 * @brief       This file provides firmware functions to manage the following 
 *              functionalities of the RTC peripheral:
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.02
 * @date        2022/06/29
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2020 MegaWin Technology Co., Ltd.
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

#ifndef _MG32x02z_RTC_MID_H

/*!< _MG32x02z_RTC_DRV_H */ 
#define _MG32x02z_RTC_MID_H

#include "MG32x02z.h"
#include "MG32x02z_Common_MID.h"
#include "MG32x02z_RTC.h"
#include "MG32x02z_SYS.h"
#include "MG32x02z__ExtraStruct.h"

/**
 * @name    RTC_Status_Definition
 *          RTC Status Definition
 */ 
///@{
#define RTC_STA_RCRF    RTC_STA_RCRF_mask_w             /*!< RTC Reload and Capture Flag Definition */
#define RTC_STA_TOF     RTC_STA_TOF_mask_w              /*!< RTC Overflow Flag Definition */
#define RTC_STA_TSF     RTC_STA_TSF_mask_w              /*!< RTC Time Stamp Flag Definition */
#define RTC_STA_PCF     RTC_STA_PCF_mask_w              /*!< RTC Perriodic Flag Definition */
#define RTC_STA_ALMF    RTC_STA_ALMF_mask_w             /*!< RTC Alarm Flag Definition */
#define RTC_STA_PM      0x01U                           /*!< RTC Calendar AM(24hr) and PM Status,0:AM(24hr),1:PM */
///@}

/**
 * @name    RTC_Interrupt_Definition
 *          RTC Interrupt Definition
 */ 
///@{
#define RTC_IT_RCR      RTC_INT_RCR_IE_mask_w           /*!< RTC Reload and Capture Interrupt bit Definition */
#define RTC_IT_TIE      RTC_INT_TIE_mask_w              /*!< RTC Overflow Interrupt bit Definition */
#define RTC_IT_TS       RTC_INT_TS_IE_mask_w            /*!< RTC Time Stamp Interrupt bit Definition */
#define RTC_IT_PC       RTC_INT_PC_IE_mask_w            /*!< RTC Periodic Interrupt bit Definition */
#define RTC_IT_ALM      RTC_INT_ALM_IE_mask_w           /*!< RTC Alarm Interrupt bit Definition */
#define RTC_IT_IEA      RTC_INT_IEA_mask_w              /*!< RTC ALL Interrupt Function bit Definition */
///@}

/**
 * @name    RTC_Clock_Definition
 *          RTC Clock Definition
 */ 
///@{
#define RTC_CLK_PDIV        RTC_CLK_CK_PDIV_mask_w      /*!< RTC prescaler control definition */
#define RTC_CLK_PDIV_1      RTC_CLK_CK_PDIV_div1_w      /*!< RTC prescaler divid 1 definition */
#define RTC_CLK_PDIV_4096   RTC_CLK_CK_PDIV_div4096_w   /*!< RTC prescaler divid 4096 definition*/
#define RTC_CLK_DIV         RTC_CLK_CK_DIV_mask_w       /*!< RTC divider definition */
#define RTC_CLK_DIV_1       RTC_CLK_CK_DIV_div1_w       /*!< RTC divider div 1 definition */
#define RTC_CLK_DIV_2       RTC_CLK_CK_DIV_div2_w       /*!< RTC divider div 2 definition */
#define RTC_CLK_DIV_4       RTC_CLK_CK_DIV_div4_w       /*!< RTC divider div 4 definition */
#define RTC_CLK_DIV_8       RTC_CLK_CK_DIV_div8_w       /*!< RTC divider div 8 definition */
#define RTC_CLK_SEL         RTC_CLK_CK_SEL_mask_w       /*!< RTC clock source select definition */
#define RTC_CLK_LS          RTC_CLK_CK_SEL_ck_ls_w      /*!< RTC clock source from ILRCO definition */
#define RTC_CLK_UT          RTC_CLK_CK_SEL_ck_ut_w      /*!< RTC clock source from UT definition */
#define RTC_CLK_APB         RTC_CLK_CK_SEL_ck_apb_w     /*!< RTC clock source from APB definition */
#define RTC_CLK_TM01_TRGO   RTC_CLK_CK_SEL_tm01_trgo_w  /*!< RTC clock source from TM01_TRGO definition */
///@}

/**
 * @name    RTC_Key_Definition
 *          RTC Key Definition
 */ 
///@{
#define RTC_LOCK        0x712A0000UL                    /*!< RTC lock enable definition */
#define RTC_PROTECT     0x00000000UL                    /*!< RTC register read / write protect enable definition */
#define RTC_UNPROTECT   0x0000A217UL                    /*!< RTC register read / write protect disable definition */
///@}

/**
 * @name    RTC_CR0_Definition
 *          RTC CR0 Definition
 */
///@{
#define RTC_TF_WPEN         RTC_CR0_TF_WPEN_mask_w      /*!< RTC over flow wake up enable definition */
#define RTC_PC_WPEN         RTC_CR0_PC_WPEN_mask_w      /*!< RTC periodic wake up enable definition */
#define RTC_ALM_WPEN        RTC_CR0_ALM_WPEN_mask_w     /*!< RTC alarm wake up enable definition */
#define RTC_OUT_LCK         RTC_CR0_OUT_LCK_mask_w      /*!< RTC output signal initial state control definition */
#define RTC_TS_TRGS         RTC_CR0_TS_TRGS_mask_w      /*!< RTC time stamp trigger edge select definition */
#define RTC_TS_TRGS_0       0x00001000UL                /*!< RTC time stamp trigger edge select bit[0] */
#define RTC_TS_TRGS_1       0x00002000UL                /*!< RTC time stamp trigger edge select bit[1] */
#define RTC_OUT_SEL         RTC_CR0_OUT_SEL_mask_w      /*!< RTC output signal select definition */
#define RTC_OUT_SEL_0       0x00000100UL                /*!< RTC output signal select bit[0] */
#define RTC_OUT_SEL_1       0x00000200UL                /*!< RTC output signal select bit[1] */
#define RTC_OUT_ALM         RTC_CR0_OUT_SEL_alm_w       /*!< RTC output signal from alarm definition */
#define RTC_OUT_PC          RTC_CR0_OUT_SEL_pc_w        /*!< RTC output signal from periodic definition */
#define RTC_OUT_TS          RTC_CR0_OUT_SEL_ts_w        /*!< RTC output signal from time stamp defintion */
#define RTC_OUT_TO          RTC_CR0_OUT_SEL_to_w        /*!< RTC output signal from RTC overflow definition */
#define RTC_RCR_MDS         RTC_CR0_RCR_MDS_mask_w      /*!< RTC capture and reload mode select definition*/
#define RTC_RCR_MDS_0       0x00000010UL                /*!< RTC capture and reload mode select bit[0] */
#define RTC_RCR_MDS_1       0x00000020UL                /*!< RTC capture and reload mode select bit[1]*/
#define RTC_DIRECT_CAP      RTC_CR0_RCR_MDS_directly_capture_w  /*!< RTC direct capture mode definition */
#define RTC_DELAY_CAP       RTC_CR0_RCR_MDS_delayed_capture_w   /*!< RTC delay capture mode definition */
#define RTC_FORCE_RELOAD    RTC_CR0_RCR_MDS_forced_reload_w     /*!< RTC force reload definition */
#define RTC_AUTO_RELOAD     RTC_CR0_RCR_MDS_auto_reload_w       /*!< RTC auto reload definition */
#define RTC_ALM_ENABLE      RTC_CR0_ALM_EN_mask_w               /*!< RTC alarm funtion control definition*/
#define RTC_ENABLE          RTC_CR0_EN_mask_w                   /*!< RTC function control definition */
#define RTC_FMT             0x01U                               /*!< RTC Time Format Control bit */
#define RTC_HOURFORMAT_12   1U                                  /*!< RTC Hour Format Select 12 Hour */
#define RTC_HOURFORMAT_24   0U                                  /*!< RTC Hour Format Select 24 Hour */
///@}

/**
 * @name    RTC_START_Definition
 * @brief   RTC START Definition
 */ 
///@{
#define RTC_RC_START    RTC_CR1_RC_START_mask_w         /*!< RTC timer counter reload and software capture start enable definition */
///@}

/**
 * @name    Masks_Definition
 *          Masks Definition
 */ 
///@{
#define RTC_CR0_Mask        0x000B3333                  /*!< RTC CR0 reserve bit definition */
#define RTC_TIMEOUT_VALUE   1000U                       /*!< RTC timeout definition */
#define RTC_INIT_MASK       0xFFFFFFFF                  /*!< RTC register write test value definition */
///@}

/**
 * @enum    MID_RTC_StateTypeDef
 * @brief   MID RTC State Definition
 */ 
typedef enum
{
  MID_RTC_STATE_RESET             = 0x00U,  /*!< RTC not yet initialized or disabled */
  MID_RTC_STATE_READY             = 0x01U,  /*!< RTC initialized and ready for use   */
  MID_RTC_STATE_BUSY              = 0x02U,  /*!< RTC process is ongoing              */     
  MID_RTC_STATE_TIMEOUT           = 0x03U,  /*!< RTC timeout state                   */  
  MID_RTC_STATE_ERROR             = 0x04U,  /*!< RTC error state                     */      
  isLeapYear                      = 0x05U,  /*!< Leap year definition */
  noLeapYear                      = 0x06U   /*!< Not leap year definition */
}MID_RTC_StateTypeDef;

/** 
 * @enum        Month_TypeDef
 * @brief       Declare month 
 */        
typedef enum
{
    January,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
}Month_TypeDef;

/** 
 * @enum        Weekend_TypeDef
 * @brief       Declare weekend 
 */        
typedef enum
{
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
}Weekend_TypeDef;

/**
 * @struct  RTC_InitTypeDef
 * @brief   MID RTC Initial Struct Definition
 */ 
typedef struct __attribute__ ((packed))
{
    uint32_t RTC_STA;           /*!< RTC even flag read register */
    
    
    uint32_t RTC_INT;           /*!< RTC IT enable , disable control register */
    
    
    uint32_t RTC_RLR;           /*!< RTC time counter reload value register */
    
    
    uint32_t RTC_ALM;           /*!< RTC alarm compare value register */
    
    
    uint32_t Init_Year;         /*!< Record the initial year */
    
    
    uint8_t Init_Month;         /*!< Reord the initial month */
    
    
    uint8_t Init_Date;          /*!< Record the initial Date */
    
    
    uint8_t Init_Hours;         /*!< Record the initial hours */
    
    
    uint8_t Init_Minutes;       /*!< Record the initial minute */
    
    
    uint8_t Init_Seconds;       /*!< Record the initial second */
    
    
    uint8_t HourFormat;         /*!< Specifies the RTC Hour Format.
                                 This parameter can be a value of RTC_Hour_Formats */
    
    
    uint8_t RTC_CK_PDIV;        /*!< RTC prescaler divider register */
    
    
    uint8_t RTC_CK_DIV;         /*!< RTC divider register */
    
    
    uint8_t RTC_CK_SEL;         /*!< RTC clock source select */
    
    
}RTC_InitTypeDef;

/**
 * @struct  RTC_TimeTypeDef  
 * @brief   RTC Time Structure Definition  
 */ 
typedef struct __attribute__ ((packed))
{
    uint32_t SubSeconds;     /*!< Specifies the RTC_SSR RTC Sub Second register content.
                                 This parameter corresponds to a time unit range between [0-1] Second
                                 with [1 Sec / SecondFraction +1] granularity */
    
    uint32_t SecondFraction;  /*!< Specifies the range or granularity of Sub Second register content
                                 corresponding to Synchronous pre-scaler factor value (PREDIV_S)
                                 This parameter corresponds to a time unit range between [0-1] Second
                                 with [1 Sec / SecondFraction +1] granularity.
                                 This field will be used only by HAL_RTC_GetTime function */
    
    uint32_t DayLightSaving;  /*!< Specifies RTC_DayLightSaveOperation: the value of hour adjustment.
                                 This parameter can be a value of RTC_DayLightSaving_Definitions */
    
    uint32_t StoreOperation;  /*!< Specifies RTC_StoreOperation value to be written in the BCK bit 
                                 in CR register to store the operation.
                                 This parameter can be a value of RTC_StoreOperation_Definitions */
    
    uint8_t Hours;            /*!< Specifies the RTC Time Hour.
                                 This parameter must be a number between Min_Data = 0 and Max_Data = 12 if the RTC_HourFormat_12 is selected.
                                 This parameter must be a number between Min_Data = 0 and Max_Data = 23 if the RTC_HourFormat_24 is selected  */
    
    
    uint8_t Minutes;          /*!< Specifies the RTC Time Minutes.
                                 This parameter must be a number between Min_Data = 0 and Max_Data = 59 */
    
    
    uint8_t Seconds;          /*!< Specifies the RTC Time Seconds.
                                 This parameter must be a number between Min_Data = 0 and Max_Data = 59 */
    
    
    uint8_t TimeFormat;       /*!< Specifies the RTC AM/PM Time.
                                 This parameter can be a value of RTC_AM_PM_Definitions */
    
    
}RTC_TimeTypeDef;

/**
 * @struct  RTC_DateTypeDef  
 * @brief   RTC Date Structure Definition  
 */ 
typedef struct __attribute__ ((packed))
{
    uint32_t Year;          /*!< Specifies the RTC Date Year.
                                This parameter must be a number between Min_Data = 0 and Max_Data = 99 */
    
    
    uint8_t WeekDay;        /*!< Specifies the RTC Date WeekDay.
                                This parameter can be a value of RTC_WeekDay_Definitions */
    
    
    uint8_t Month;          /*!< Specifies the RTC Date Month (in BCD format).
                                This parameter can be a value of RTC_Month_Date_Definitions */
    
    
    uint8_t Date;           /*!< Specifies the RTC Date.
                                This parameter must be a number between Min_Data = 1 and Max_Data = 31 */
    
    
}RTC_DateTypeDef;

/**
 * @struct  RTC_AlarmTypeDef
 * @brief   MID RTC Alarm Struct Definition
 */ 
typedef struct __attribute__ ((packed))
{
    RTC_TimeTypeDef AlarmTime;     /*!< Specifies the RTC Alarm Time members */
    
    
    uint32_t AlarmMask;            /*!< Specifies the RTC Alarm Masks.
                                      This parameter can be a value of RTC_AlarmMask_Definitions */
    
    
    uint32_t AlarmSubSecondMask;   /*!< Specifies the RTC Alarm SubSeconds Masks.
                                      This parameter can be a value of RTC_Alarm_Sub_Seconds_Masks_Definitions */                                   
    
    
    uint32_t AlarmDateWeekDaySel;  /*!< Specifies the RTC Alarm is on Date or WeekDay.
                                     This parameter can be a value of RTC_AlarmDateWeekDay_Definitions */
    
    
    uint32_t Alarm;                /*!< Specifies the alarm .
                                      This parameter can be a value of RTC_Alarms_Definitions */
    
    
    uint32_t AlarmDateWeekDay;      /*!< Specifies the RTC Alarm Date/WeekDay.
                                      If the Alarm Date is selected, this parameter must be set to a value in the 1-31 range.
                                      If the Alarm WeekDay is selected, this parameter can be a value of RTC_WeekDay_Definitions */
    
    
}RTC_AlarmTypeDef;


/**
 * @struct  RTC_HandleTypeDef
 * @brief   MID RTC Handle Struct Definition
 */ 
typedef struct __attribute__ ((packed))
{
    RTC_Struct                 *Instance;  /*!< Register base address    */
    
    
    RTC_InitTypeDef             Init;      /*!< RTC required parameters  */ 
    
    
    MID_LockTypeDef             Lock;      /*!< RTC locking object       */
    
    
    RTC_DateTypeDef             sDate;     /*!< RTC date register definition */
    
    
    RTC_TimeTypeDef             sTime;     /*!< RTC time register definition */
    
    
    __IO MID_RTC_StateTypeDef   State;     /*!< Time communication state */
    
    
}RTC_HandleTypeDef;


/**
 *******************************************************************************
 * @brief  RTC Lock State Control
 * @param  "__HANDLE__"  RTC handle
 * @par     Example
 * @code
   __DRV_RTC_LOCK(mRTC);      //RTC state lock
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_LOCK(__HANDLE__)                                          \
                                do{                                         \
                                    if((__HANDLE__)->Lock == MID_Locked)    \
                                        return MID_BUSY;                    \
                                    else                                    \
                                        (__HANDLE__)->Lock = MID_Locked;    \
                                }while(0)
///@}

/**
 *******************************************************************************
 * @brief  RTC Unlock State Control
 * @param  "__HANDLE__"  RTC handle
 * @par     Example
 * @code
   __DRV_RTC_UNLOCK(mRTC);    //RTC state unlock
 * @endcode
 * @retval None
 ******************************************************************************* */
///@{
#define __DRV_RTC_UNLOCK(__HANDLE__)                                        \
                                do{                                         \
                                    (__HANDLE__)->Lock = MID_UnLocked;      \
                                }while(0)
///@}

/**
 *******************************************************************************
 * @brief  RTC Function Protect
 * @param  "__HANDLE__"  RTC handle
 * @par     Example
 * @code
   __DRV_RTC_WRITEPROTECT_ENABLE(mRTC);     //RTC module register protect
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_WRITEPROTECT_ENABLE(__HANDLE__)                                           \
                                do{                                                         \
                                    (__HANDLE__)->Instance->KEY.W = RTC_PROTECT;            \
                                }while(0)
///@}

/**
 *******************************************************************************
 * @brief  RTC Function  Unprotect
 * @param  "__HANDLE__"  RTC handle
 * @par     Example
 * @code
   __DRV_RTC_WRITEPROTECT_DISABLE(mRTC);    //RTC module register unprotect
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_WRITEPROTECT_DISABLE(__HANDLE__)                                              \
                                do{                                                             \
                                    (__HANDLE__)->Instance->KEY.W &= ~RTC_KEY_KEY_mask_w;       \
                                    (__HANDLE__)->Instance->KEY.W |= RTC_UNPROTECT;             \
                                }while(0)
///@}

/**
 *******************************************************************************
 * @brief  RTC Module Lock Cintrol
 * @param  "__HANDLE__"  RTC handle
 * @par    Example
 * @code    
   __DRV_RTC_LOCK_ENABLE(mRTC);          //RTC module register lock(Unlock by cold reset)
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_LOCK_ENABLE(__HANDLE__)    (_HADNLE_)->Instance->KEY.W &= ~RTC_KEY_LOCK_mask_w; \
                                             (_HADNLE_)->Instance->KEY.W |= 0x712A0000UL
///@}

/**
 *******************************************************************************
 * @brief  Reset RTC handle state
 * @param  "__HANDLE__"  RTC handle
 * @par     Example
 * @code
   __DRV_RTC_RESET_HANDLE_STATE(mRTC);     //Clear all RTC handle state
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_RESET_HANDLE_STATE(__HANDLE__)  ((__HANDLE__)->Instance->STA.W = MID_RTC_STATE_RESET)
///@}

/**
 *******************************************************************************
 * @brief  Get the selected flag status.
 * @param  "__HANDLE__"  RTC handle
 * @param  "__FLAG__"  RTC flag
 * @arg\b  RTC_STA_RCRF.
 * @arg\b  RTC_STA_TOF.
 * @arg\b  RTC_STA_TSF.
 * @arg\b  RTC_STA_PCF.
 * @arg\b  RTC_STA_ALMF.
 * @par    Example
 * @code   
   __DRV_RTC_GET_FLAG(mRTC , RTC_STA_RCR);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_GET_FLAG(__HANDLE__ , __FLAG__)    ((((__HANDLE__)->Instance->STA.W) & (__FLAG__)) == (__FLAG__))
///@}

/**
 *******************************************************************************
 * @brief  Claer RTC pending flag.
 * @param  "__HANDLE__"  RTC handle
 * @param  "__FLAG__"  RTC flag
 * @arg\b  RTC_STA_RCRF.
 * @arg\b  RTC_STA_TOF.
 * @arg\b  RTC_STA_TSF.
 * @arg\b  RTC_STA_PCF.
 * @arg\b  RTC_STA_ALMF.
 * @par    Example
 * @code   
   __DRV_RTC_CLEAR_FLAG(mRTC , (RTC_STA_ALMF|RTC_STA_PCF));
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_CLEAR_FLAG(__HANDLE__ , __FLAG__)     ((__HANDLE__)->Instance->STA.W = (__FLAG__))
///@}

/**
 *******************************************************************************
 * @brief  RTC divider select
 * @param  "__HANDLE__"  RTC handle
 * @param  "__DIV__"  RTC Divider
 * @arg\b    RTC_CLK_DIV_1
 * @arg\b    RTC_CLK_DIV_2
 * @arg\b    RTC_CLK_DIV_4
 * @arg\b    RTC_CLK_DIV_8
 * @par     Example
 * @code    
   __DRV_RTC_DIVIDER_SEL(mRTC , RTC_CLK_DIV_1);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_DIVID_SEL(__HANDLE__ , __DIV__)   (__HANDLE__)->Instance->CLK.W &= ~(RTC_CLK_DIV);    \
                                                    (__HANDLE__)->Instance->CLK.W |= (__DIV__)
///@}

/**
 *******************************************************************************
 * @brief  RTC prescaler divider select
 * @param  "__HANDLE__"  RTC handle
 * @param  "__PDIV__"  RTC Prescaler Divider
 * @arg\b    RTC_CLK_PDIV_1
 * @arg\b    RTC_CLK_PDIV_4096
 * @par     Example
 * @code    
   __DRV_RTC_DIVIDER_SEL(mRTC , RTC_CLK_PDIV_1);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_PDIVID_SEL(__HANDLE__ , __PDIV__) (__HANDLE__)->Instance->CLK.W &= ~(RTC_CLK_PDIV);   \
                                                    (__HANDLE__)->Instance->CLK.W |= (__PDIV__)
///@}

/**
 *******************************************************************************
 * @brief  RTC clock source select
 * @param  "__HANDLE__"  RTC handle
 * @param  "__CLOCK__"  RTC Clock source
 * @arg\b    RTC_CLK_LS
 * @arg\b    RTC_CLK_UT
 * @arg\b    RTC_CLK_APB
 * @arg\b    RTC_CLK_TM01_TRGO
 * @par     Example
 * @code    
   __DRV_RTC_CLOCK_SEL(mRTC , RTC_CLK_LS);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_CLOCK_SEL(__HANDLE__ , __CLOCK__) (__HANDLE__)->Instance->CLK.W &= ~(RTC_CLK_SEL);        \
                                                    (__HANDLE__)->Instance->CLK.W |= (__CLOCK__)
///@}

/**
 *******************************************************************************
 * @brief  RTC time counter compare value set.
 * @param  "__HANDLE__"  RTC handle
 * @param  "__VAL__"  ALARM value
 * @par    Example
 * @code    
   __DRV_ALM_SET(mRTC,tmpreg);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_ALARM_SET(__HANDLE__, __VAL__) ((__HANDLE__)->Instance->ALM.W = (__VAL__))
///@}

/**
 *******************************************************************************
 * @brief  RTC time counter reload value set.
 * @param  "__HANDLE__"  RTC handle
 * @param  "__VARIABLE__"  RTC handle
 * @par    Example
 * @code   
   __DRV_RLR_SET(mRTC);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_RELOAD_SET(__HANDLE__ , __VARIABLE__) ((__HANDLE__)->Instance->RLR.W = (__VARIABLE__))
///@}

/**
 *******************************************************************************
 * @brief  Enable specified RTC all interrupt
 * @param  "__HANDLE__"  RTC handle
 * @par    Example
 * @code    
   __DRV_RTC_ENABLE_ITEA(mRTC);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_ENABLE_ITEA(__HANDLE__) ((__HANDLE__)->Instance->INT.W |= RTC_IT_IEA)
///@}

/**
 *******************************************************************************
 * @brief  Disable specified RTC all interrupt
 * @param  "__HANDLE__"  RTC handle
 * @par    Example
 * @code    
   __DRV_RTC_DISABLE_ITEA(mRTC);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_DISABLE_ITEA(__HANDLE__) ((__HANDLE__)->Instance->INT.W &= ~RTC_IT_IEA)
///@}

/**
 *******************************************************************************
 * @brief  Enable RTC interrupt.
 * @param  "__HANDLE__"  RTC handle
 * @param  "__INTERRUPT__"  RTC Interrupt
 * @arg\b    RTC_IT_RCR
 * @arg\b    RTC_IT_TIE
 * @arg\b    RTC_IT_TS
 * @arg\b    RTC_IT_PC
 * @arg\b    RTC_IT_ALM
 * @par    Example
 * @code    
   __DRV_RTC_ENABLE_IT(mRTC , (RTC_IT_TS|RTC_IT_ALM));
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_ENABLE_IT(__HANDLE__ , __INTERRUPT__)  ((__HANDLE__)->Instance->INT.W = (__INTERRUPT__ | RTC_IT_IEA))
///@}

/**
 *******************************************************************************
 * @brief  Enable RTC interrupt.
 * @param  "__HANDLE__"  RTC handle
 * @param  "__INTERRUPT__"  RTC Interrupt
 * @arg\b    RTC_IT_RCR
 * @arg\b    RTC_IT_TIE
 * @arg\b    RTC_IT_TS
 * @arg\b    RTC_IT_PC
 * @arg\b    RTC_IT_ALM
 * @par    Example
 * @code    
   __DRV_RTC_ENABLE_IT(mRTC , (RTC_IT_IEA|RTC_IT_ALM));
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_DISABLE_IT(__HANDLE__ , __INTERRUPT__)    ((__HANDLE__)->Instance->INT.W &= ~(__INTERRUPT__ | RTC_IT_IEA))
///@}

/**
 *******************************************************************************
 * @brief  RTC time stamp interrupt enable
 * @param  "__HANDLE__"  RTC handle
 * @par    Example
 * @code    
   __DRV_RTC_TIME_STAMP_ENABLE_IT(mRTC);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_TIME_STAMP_ENABLE_IT(__HANDLE__)    ((__HANDLE__)->Instance->INT.W |= RTC_IT_TS)
///@}

/**
 *******************************************************************************
 * @brief  RTC time stamp rising edge trigger.
 * @param  "__HANDLE__"  RTC handle
 * @par    Example
 * @code    
   __DRV_RTC_STAMP_ENABLE_RISING_EDGE(mRTC);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_STAMP_ENABLE_RISING_EDGE(__HANDLE__)    (__HANDLE__)->Instance->CR0.W &= ~(RTC_TS_TRGS);    \
                                                          (__HANDLE__)->Instance->CR0.W |= RTC_TS_TRGS_0
///@}

/**
 *******************************************************************************
 * @brief  RTC time stamp falling edge trigger.
 * @param  "__HANDLE__"  RTC handle
 * @par    Example
 * @code    
   __DRV_RTC_STAMP_ENABLE_FALLING_EDGE(mRTC);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_STAMP_ENABLE_FALLING_EDGE(__HANDLE__)    (__HANDLE__)->Instance->CR0>W &= ~(RTC_TS_TRGS);    \
                                                           (__HANDLE__)->Instance->CR0.W |= RTC_TS_TRGS_1
///@}

/**
 *******************************************************************************
 * @brief  RTC time stamp Daul edge trigger.
 * @param  "__HANDLE__"  RTC handle
 * @par    Example
 * @code    
   __DRV_RTC_STAMP_ENABLE_FALLING_EDGE(mRTC);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_STAMP_ENABLE_DAUL_EDGE(__HANDLE__)    (__HANDLE__)->Instance->CR0>W &= ~(RTC_TS_TRGS);    \
                                                        (__HANDLE__)->Instance->CR0.W |= (RTC_TS_TRGS_0|RTC_TS_TRGS_1)
///@}
  
/**
 *******************************************************************************
 * @brief  RTC reload and start capture enable
 * @param  "__HANDLE__"  RTC handle
 * @par    Example
 * @code    
   __DRV_RTC_START_EN(mRTC);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_START_EN(__HANDLE__)    ((__HANDLE__)->Instance->CR1.W = 0x01U)
///@}

/**
 *******************************************************************************
 * @brief  RTC reload and start capture no effect
 * @param  "__HANDLE__"  RTC handle
 * @par    Example
 * @code    
   __DRV_RTC_START_NOEFFECT(mRTC);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_START_NOEFFECT(__HANDLE__)  ((__HANDLE__)->Instance->CR1.W = 0x00U)
///@}

/**
 *******************************************************************************
 * @brief  RTC Function enable
 * @param  "__HANDLE__"  RTC handle
 * @par    Example
 * @code    
   __DRV_RTC_ENABLE(mRTC);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_ENABLE(__HANDLE__)  ((__HANDLE__)->Instance->CR0.MBIT.EN = 1)
///@}

/**
 *******************************************************************************
 * @brief  RTC Function disable
 * @param  "__HANDLE__"  RTC handle
 * @par    Example
 * @code    
   __DRV_RTC_ENABLE(mRTC);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->CR0.MBIT.EN = 0)
///@}

/**
 *******************************************************************************
 * @brief  RTC alarm enable
 * @param  "__HANDLE__"  RTC handle
 * @par    Example
 * @code    
   __DRV_RTC_ENABLE(mRTC);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_ALARM_ENABLE(__HANDLE__)  ((__HANDLE__)->Instance->CR0.MBIT.ALM_EN = 1)
///@}

/**
 *******************************************************************************
 * @brief  RTC alarm disable
 * @param  "__HANDLE__"  RTC handle
 * @par    Example
 * @code    
   __DRV_RTC_ENABLE(mRTC);
 * @endcode
 * @retval None 
 *******************************************************************************
 */
///@{
#define __DRV_RTC_ALARM_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->CR0.MBIT.ALM_EN = 0)
///@}

/**
 *******************************************************************************
 * @brief  RTC Reload and Capture Mode Select
 * @param  "__HANDLE__"  RTC handle
 * @param  "__MDS__"  Capture or reload mode
 * @arg\b    RTC_DIRECT_CAP
 * @arg\b    RTC_DELAY_CAP
 * @arg\b    RTC_FORCE_RELOAD
 * @arg\b    RTC_AUTO_RELOAD
 * @par    Example
 * @code    
   __DRV_RTC_RCR_MDS_SEL(mRTC , RTC_AUTO_RELOAD);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_RCR_MDS_SEL(__HANDLE__ , __MDS__)  (__HANDLE__)->Instance->CR0.W &= ~(RTC_RCR_MDS);        \
                                                     (__HANDLE__)->Instance->CR0.W |= (__MDS__)
///@}

/**
 *******************************************************************************
 * @brief  Wake up by RTC overflow warm reset even enable.
 * @param  "__HANDLE__"  RTC handle
 * @par    Example
 * @code    
   __DRV_RTC_TF_WPEN_ENABLE(mRTC);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_TF_WPEN_ENABLE(__HANDLE__)  ((__HANDLE__)->Instance->CR0.W |= RTC_TF_WPEN)
///@}

/**
 *******************************************************************************
 * @brief  Wake up by RTC overflow warm reset even disable.
 * @param  "__HANDLE__"  RTC handle
 * @par    Example
 * @code    
   __DRV_RTC_TF_WPEN_DISABLE(mRTC);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_TF_WPEN_DISABLE(__HANDLE__)  ((__HANDLE__)->Instance->CR0.W &= ~RTC_TF_WPEN)
///@}

/**
 *******************************************************************************
 * @brief  Wake up by RTC periodic warm reset even enable.
 * @param  "__HANDLE__"  RTC handle
 * @par    Example
 * @code    
   __DRV_RTC_PC_WPEN_ENABLE(mRTC);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_PC_WPEN_ENABLE(__HANDLE__)  ((__HANDLE__)->Instance->CR0.W |= RTC_PC_WPEN)
///@}

/**
 *******************************************************************************
 * @brief  Wake up by RTC periodic warm reset even disable.
 * @param  "__HANDLE__"  RTC handle
 * @par    Example
 * @code    
   __DRV_RTC_PC_WPEN_DISABLE(mRTC);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_PC_WPEN_DISABLE(__HANDLE__)  ((__HANDLE__)->Instance->CR0.W &= ~RTC_PC_WPEN)
///@}

/**
 *******************************************************************************
 * @brief  Wake up by RTC alarm compare warm reset even enable.
 * @param  "__HANDLE__"  RTC handle
 * @par    Example
 * @code    
   __DRV_RTC_PC_WPEN_ENABLE(mRTC);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_ALM_WPEN_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->CR0.W |= RTC_ALM_WPEN)
///@}

/**
 *******************************************************************************
 * @brief  Wake up by RTC alarm compare warm reset even disable.
 * @param  "__HANDLE__"  RTC handle
 * @par    Example
 * @code    
   __DRV_RTC_PC_WPEN_DISABLE(mRTC);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_ALM_WPEN_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->CR0.W &= ~RTC_ALM_WPEN)
///@}

/**
 *******************************************************************************
 * @brief  RTC Get Alarm Value
 * @param  "__HANDLE__"  RTC handle
 * @par    Example
 * @code   
   __DRV_RTC_GETALARM(mRTC);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_GETALARM(__HANDLE__) ((__HANDLE__)->Instance->ALM.W)
///@}

/**
 *******************************************************************************
 * @brief  Wake up by RTC warm reset even disable.
 * @param  "__HANDLE__"  RTC handle
 * @param  "__VARIABLE__"  RTC handle
 * @arg\b    RTC_ALM_WPEN
 * @arg\b    RTC_PC_WPEN
 * @arg\b    RTC_TF_WPEN
 * @par    Example
 * @code   
  __DRV_RTC_PC_WPEN_ENABLE(mRTC , RTC_ALM_WPEN);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_WPEN_DISABLE(__HANDLE__ , __VARIABLE__)                                                        \
                                                        ((__HANDLE__)->Instance->CR0.W &= ~(__VARIABLE__))
///@}

/**
 *******************************************************************************
 * @brief  RTC output signal initial state control enable.
 * @param  "__HANDLE__"  RTC handle
 * @param  "__OUTPUT__"  RTC handle
 * @arg\b  RTC_OUT_ALM
 * @arg\b  RTC_OUT_PC
 * @arg\b  RTC_OUT_TS
 * @arg\b  RTC_OUT_TO
 * @par    Example
 * @code   
   __DRV_RTC_OUT_LCK_ENABLE(mRTC);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_OUT_SEL(__HANDLE__ , __OUTPUT__)  (__HANDLE__)->Instance->CR0.W &= ~RTC_OUT_SEL;    \
                                                    ((__HANDLE__)->Instance->CR0.W |= (__OUTPUT__))
///@}

/**
 *******************************************************************************
 * @brief  RTC output signal initial state control enable.
 * @param  "__HANDLE__"  RTC handle
 * @par    Example
 * @code   
   __DRV_RTC_OUT_LCK_ENABLE(mRTC);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_OUT_LCK_ENABLE(__HANDLE__)  ((__HANDLE__)->Instance->CR0.W |= RTC_OUT_LCK)
///@}

/**
 *******************************************************************************
 * @brief  RTC output signal initial state control disable.
 * @param  "__HANDLE__"  RTC handle
 * @par    Example
 * @code   
   __DRV_RTC_OUT_LCK_DISABLE(mRTC);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_OUT_LCK_DISABLE(__HANDLE__)  ((__HANDLE__)->Instance->CR0.W &= ~RTC_OUT_LCK)
///@}

/**
 *******************************************************************************
 * @brief  RTC output signal initial state.
 * @param  "__HANDLE__"  RTC handle
 * @par    Example
 * @code   
   __DRV_RTC_OUTSTA_HIGH(mRTC);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_OUTSTA_HIGH(__HANDLE__) ((__HANDLE__)->Instance->CR0.W |= RTC_OUT_STA)
///@}

/**
 *******************************************************************************
 * @brief  RTC output signal initial state.
 * @param  "__HANDLE__"  RTC handle
 * @par    Example
 * @code   
   __DRV_RTC_OUTSTA_LOW(mRTC);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_OUTSTA_LOW(__HANDLE__) ((__HANDLE__)->Instance->CR0.W &= ~RTC_OUT_STA)
///@}

/**
 *******************************************************************************
 * @brief  RTC Get Capture Register
 * @param  "__HANDLE__"  RTC handle
 * @par     Example
 * @code    
   REG = __DRV_RTC_DIVIDER_SEL(mRTC);
 * @endcode
 * @retval None
 *******************************************************************************
 */
///@{
#define __DRV_RTC_GetCaputreReg(__HANDLE__) ((__HANDLE__)->Instance->CAP.W )
///@}

/**
 * @name    Function announce
 * @brief   RTC base initial/Deinitial
 */ 
///@{
MID_StatusTypeDef MID_RTC_Init(RTC_HandleTypeDef *mRTC);
void MID_RTC_MspInit(RTC_HandleTypeDef* mRTC);
void MID_RTC_MspDeInit(RTC_HandleTypeDef *mRTC);
MID_StatusTypeDef RTC_EnterInitMode(RTC_HandleTypeDef* mRTC);
MID_StatusTypeDef MID_RTC_DeactivateAlarm(RTC_HandleTypeDef* mRTC);
uint32_t MID_RTC_GetState(RTC_HandleTypeDef* mRTC);
MID_StatusTypeDef MID_RTC_SetTime(RTC_HandleTypeDef *mRTC, uint32_t RTC_RLR);
MID_StatusTypeDef MID_RTC_GetTime(RTC_HandleTypeDef* mRTC);
MID_StatusTypeDef MID_RTC_SetAlarm(RTC_HandleTypeDef *mRTC, RTC_AlarmTypeDef *mALARM);
MID_StatusTypeDef MID_RTC_SetAlarm_IT(RTC_HandleTypeDef* mRTC);
MID_StatusTypeDef MID_RTC_CalendarValueCheck(RTC_HandleTypeDef *mRTC);
MID_StatusTypeDef MID_RTC_Capture_Convert(RTC_HandleTypeDef *mRTC, uint32_t RTC_CAP);
MID_RTC_StateTypeDef MID_RTC_LeapYearCheck(RTC_HandleTypeDef *mRTC);
uint32_t MID_RTC_GetWeekend(RTC_HandleTypeDef *mRTC);
///@}

/**
 * @name    RTC Interrupt Callback
 * @brief   Addtogroup RTC Callback
 */ 
///@{
void MID_RTC_IRQHandler(RTC_HandleTypeDef *mRTC);
void MID_RTC_RCRCallback(RTC_HandleTypeDef* mRTC);
void MID_RTC_TFCallback(RTC_HandleTypeDef* mRTC);
void MID_RTC_TSCallback(RTC_HandleTypeDef* mRTC);
void MID_RTC_PCCallback(RTC_HandleTypeDef* mRTC);
void MID_RTC_AlarmCallback(RTC_HandleTypeDef* mRTC);
///@}


#endif  /* _MG32x02z_MID_RTC_H */


