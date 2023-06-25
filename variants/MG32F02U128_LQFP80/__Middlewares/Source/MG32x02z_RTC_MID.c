/**
 ******************************************************************************
 *
 * @file        MG32x02z_RTC_MID.c
 *
 * @brief       RTC middleware module driver.
 *              This file provides firmware functions to manage the following 
 *              functionalities of the Independent Watchdog (RTC) peripheral:
 *              Initialization and Start functions
 * @par         Project
 *              MG32x02z
 * @version     V1.01
 * @date        2020/04/29
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2020 Megawin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************
 * @par Disclaimer 
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


#include "MG32x02z_RTC_MID.h"

/**
* @name    Initial/Deinitial RTC with RTC_HandleTypeDef
*
*/
///@{
/**
 *******************************************************************************
 * @brief       Initial the RTC according to the specified parameters 
 *              in the RTC_InitTypeDef structure and initialize the associate handle.
 * @param[in]   mRTC : pointer to a RTC_HandleTypeDef
 * @return      MID_StatusTypeDef
 * @note
 * @par         Example
 * @code
    mRTC.Instance = RTC;
    mRTC.Init.RTC_CK_SEL = RTC_CLK_LS;         //RTC clock source select
    mRTC.Init.RTC_RLR = 0x00000000;             //RTC reload register set 0~0xFFFFFFFE, 0xFFFFFFFF  forbidden.
    mRTC.Init.HourFormat = RTC_HOURFORMAT_12;
    
    mRTC.sTime.Seconds = 58U;
    mRTC.sTime.Minutes = 59U;
    mRTC.sTime.Hours = 23U;
    
    mRTC.sDate.Date = 29U;
    mRTC.sDate.Month = February;
    mRTC.sDate.Year = 2020U;
    
    MID_RTC_Init(&mRTC);
    
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_RTC_Init(RTC_HandleTypeDef *mRTC)
{
    /* Check the RTC peripheral state */
    if(mRTC==NULL)
    {
        return MID_ERROR;
    }
    
    if(mRTC->State == MID_RTC_STATE_RESET)
    {
        /* Allocate lock resource and initialize it */
        mRTC->Lock = MID_UNLOCKED;
        
        /* Initialize RTC MSP */
        MID_RTC_MspInit(mRTC);
    }
    
    mRTC->State = MID_RTC_STATE_BUSY;
    
    /* RTC Calendar Initial Value Check */
    if(MID_RTC_CalendarValueCheck(mRTC)==MID_FAILURE)
    {
         return MID_FAILURE;
    }
    
    /* Enable the write protection for RTC registers */
    __DRV_RTC_WRITEPROTECT_DISABLE(mRTC);
    if(RTC_EnterInitMode(mRTC) != MID_OK)
    {
        /* Enable RTC Register Write Protect */
        __DRV_RTC_WRITEPROTECT_ENABLE(mRTC);
        /* Set RTC State */
        mRTC->State = MID_RTC_STATE_ERROR;
        return MID_ERROR;
    }
    else
    {
        if(mRTC->Init.RTC_CK_DIV != RTC_CLK_DIV_8)
        {
            mRTC->Init.RTC_CK_DIV = RTC_CLK_DIV_8;
        }
        
        if(mRTC->Init.RTC_CK_PDIV != RTC_CLK_PDIV_4096)
        {
            mRTC->Init.RTC_CK_PDIV = RTC_CLK_PDIV_4096;
        }
        
        /* RTC clock set */
        __DRV_RTC_DIVID_SEL(mRTC , mRTC->Init.RTC_CK_DIV);
        __DRV_RTC_PDIVID_SEL(mRTC , mRTC->Init.RTC_CK_PDIV);
        __DRV_RTC_CLOCK_SEL(mRTC , mRTC->Init.RTC_CK_SEL);
        __DRV_RTC_ENABLE_IT(mRTC , mRTC->Init.RTC_INT);     /* RTC interrupt enable. */
        
        /* RTC counter value set */
        MID_RTC_SetTime(mRTC, mRTC->Init.RTC_RLR);
        /* RTC function enable */
        __DRV_RTC_ENABLE(mRTC);
    }
    /* Enable RTC Register Write Protect */
    __DRV_RTC_WRITEPROTECT_ENABLE(mRTC);
    
    return MID_OK;
}

/**
 *******************************************************************************
 * @brief       RTC Calendar Value Check
 * @param[in]   mRTC : pointer to a RTC_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
MID_StatusTypeDef MID_RTC_CalendarValueCheck(RTC_HandleTypeDef *mRTC)
{
    /* RTC Month Value Check */
    if(mRTC->sDate.Month>December)
    {
        return  MID_FAILURE;
    }
    /* RTC Days Value Check */
    if(mRTC->sDate.Date == 0U)
    {
        if(mRTC->sDate.Date>31U)
        {
            return MID_FAILURE;
        }
    }
    /* RTC Hour Value Check */
    if(mRTC->sTime.Hours>23U)
    {
        return MID_FAILURE;
    }
    /* RTC Minute Value Check */
    if(mRTC->sTime.Minutes>59U)
    {
        return MID_FAILURE;
    }
    /* RTC Second Value Check */
    if(mRTC->sTime.Seconds>59U)
    {
        return MID_FAILURE;
    }
    
    return MID_OK;
}

/**
 *******************************************************************************
 * @brief       Initialize the RTC MSP
 * @param[in]   mRTC : pointer to a RTC_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_RTC_MspInit(RTC_HandleTypeDef* mRTC)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mRTC);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RTC_MspInit could be implemented in the user file
   */ 
}

/**
 *******************************************************************************
 * @brief       Deinitialize the RTC MSP
 * @param[in]   mRTC : pointer to a RTC_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
__weak void MID_RTC_MspDeInit(RTC_HandleTypeDef* mRTC)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mRTC);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RTC_MspDeInit could be implemented in the user file
   */ 
}

/**
 *******************************************************************************
 * @brief       RTC Private Functions
 * @param[in]   mRTC : pointer to a RTC_HandleTypeDef
 * @return      return MID_OK
 *******************************************************************************
 */
MID_StatusTypeDef RTC_EnterInitMode(RTC_HandleTypeDef *mRTC)
{
    uint32_t tickstart = 0U;
    
    /* Check if the Initialization mode is set */
    if(mRTC->Instance->CR0.W != SET)
    {
        mRTC->Instance->CR0.W = (uint32_t)RTC_INIT_MASK;
        
        tickstart = MID_GetTick();
        
        while((mRTC->Instance->CR0.W & RTC_CR0_Mask) != RTC_CR0_Mask)
        {
            if((MID_GetTick()-tickstart)>RTC_TIMEOUT_VALUE)
            {
                 return MID_TIMEOUT;
            }
        }
    }
    
    return MID_OK;
}
///@}

/**
* @name    RTC Reload & Capture Mode 
*
*/
///@{
/**
 *******************************************************************************
 * @brief       Set RTC Time
 * @param[in]   mRTC : pointer to a RTC_HandleTypeDef
 * @param[in]   RTC_RLR : 0 ~ 0xFFFFFFFE. (0xFFFFFFFF for bidden.)
 * @return      return MID_OK
 *******************************************************************************
 */
MID_StatusTypeDef MID_RTC_SetTime(RTC_HandleTypeDef *mRTC, uint32_t RTC_RLR)
{
    mRTC->Instance->RLR.W = RTC_RLR;
    /* Force reload RLR register value to counter */
    __DRV_RTC_RCR_MDS_SEL(mRTC , RTC_FORCE_RELOAD);
    __DRV_RTC_START_EN(mRTC);
    while(__DRV_RTC_GET_FLAG(mRTC, RTC_STA_RCRF)== 0U);
    __DRV_RTC_CLEAR_FLAG(mRTC , RTC_STA_RCRF);
    /* RTC Auto Reload Mode Set */
    __DRV_RTC_RCR_MDS_SEL(mRTC , RTC_AUTO_RELOAD);
    __DRV_RTC_START_EN(mRTC);
    __DRV_RTC_CLEAR_FLAG(mRTC , RTC_STA_RCRF);
    
    mRTC->Init.Init_Year = mRTC->sDate.Year;
    mRTC->Init.Init_Month = mRTC->sDate.Month;
    mRTC->Init.Init_Date = mRTC->sDate.Date;
    mRTC->Init.Init_Hours = mRTC->sTime.Hours;
    mRTC->Init.Init_Minutes = mRTC->sTime.Minutes;
    mRTC->Init.Init_Seconds = mRTC->sTime.Seconds;
    
    return MID_OK;
}
///@}

/**
* @name    RTC Delayed Capture Mode 
*
*/
///@{
/**
 *******************************************************************************
 * @brief       Get RTC Current Count Value.
 * @param[in]   mRTC : pointer to a RTC_HandleTypeDef
 * @return      return MID_OK
 *******************************************************************************
 */
MID_StatusTypeDef MID_RTC_GetTime(RTC_HandleTypeDef *mRTC)
{
    uint32_t RTC_CNT0, RTC_CNT1;
    
    __DRV_RTC_WRITEPROTECT_DISABLE(mRTC);
    __DRV_RTC_RCR_MDS_SEL(mRTC , RTC_DIRECT_CAP);
    __DRV_RTC_START_EN(mRTC);
    __NOP();__NOP();__NOP();__NOP();__NOP();
    __DRV_RTC_CLEAR_FLAG(mRTC , RTC_STA_RCRF);
    RTC_CNT0 = RTC->CAP.W;
    
    __DRV_RTC_START_EN(mRTC);
    __NOP();__NOP();__NOP();__NOP();__NOP();
    __DRV_RTC_CLEAR_FLAG(mRTC , RTC_STA_RCRF);
    RTC_CNT1 = RTC->CAP.W;
    
    while(RTC_CNT0!=RTC_CNT1)
    {
        __DRV_RTC_START_EN(mRTC);
        __NOP();__NOP();__NOP();__NOP();__NOP();
        __DRV_RTC_CLEAR_FLAG(mRTC , RTC_STA_RCRF);
        RTC_CNT0 = __DRV_RTC_GetCaputreReg(mRTC);
        
        __DRV_RTC_START_EN(mRTC);
        __NOP();__NOP();__NOP();__NOP();__NOP();
        __DRV_RTC_CLEAR_FLAG(mRTC , RTC_STA_RCRF);
        RTC_CNT1 = __DRV_RTC_GetCaputreReg(mRTC);
    }
    
    mRTC->sDate.Year = mRTC->Init.Init_Year;
    mRTC->sDate.Month = mRTC->Init.Init_Month;
    mRTC->sDate.Date = mRTC->Init.Init_Date;
    mRTC->sTime.Hours = mRTC->Init.Init_Hours;
    mRTC->sTime.Minutes = mRTC->Init.Init_Minutes;
    mRTC->sTime.Seconds = mRTC->Init.Init_Seconds;
    
    
    MID_RTC_Capture_Convert(mRTC, RTC_CNT0);
    MID_RTC_GetWeekend(mRTC);
    
    __DRV_RTC_RCR_MDS_SEL(mRTC , RTC_AUTO_RELOAD);
    __DRV_RTC_START_EN(mRTC);
    __NOP();__NOP();__NOP();__NOP();__NOP();
    __DRV_RTC_CLEAR_FLAG(mRTC , RTC_STA_RCRF);
    
    __DRV_RTC_WRITEPROTECT_ENABLE(mRTC);
    return MID_OK;
}
///@}

/**
* @name    RTC Alarm Set 
*
*/
///@{
/**
 *******************************************************************************
 * @brief       Set RTC Alarm Compare.
 * @param[in]   mRTC : pointer to a RTC_HandleTypeDef
 * @param[in]   mALARM : Set alarm value by date, hour, minute and second
 * @return      return MID_OK
 *******************************************************************************
 */
MID_StatusTypeDef MID_RTC_SetAlarm(RTC_HandleTypeDef *mRTC, RTC_AlarmTypeDef *mALARM)
{
    uint8_t stmp = 0,wdcnt = 0;
    uint32_t tmpreg = 0, htmp = 0, mtmp = 0, dtmp = 0;
    
    mRTC->State = MID_RTC_STATE_BUSY;
    
    /* Alarm week day check */
    if(mALARM->AlarmDateWeekDaySel==1U)
    {
        if(mALARM->AlarmDateWeekDay > mRTC->sDate.WeekDay)
            dtmp = (mALARM->AlarmDateWeekDay - mRTC->sDate.WeekDay);
        
        else
        {
            for(wdcnt = 1;wdcnt<7;wdcnt++)
            {
                dtmp = mRTC->sDate.WeekDay + wdcnt;
                if(dtmp > 6)
                {
                   dtmp = dtmp-7; 
                }
                if(dtmp == mALARM->AlarmDateWeekDay)
                {
                    dtmp = wdcnt;
                    break;
                }
            }
        }
    }
    
    /* Alarm Date Check */
    if(mALARM->AlarmDateWeekDaySel == 0U)
    {
        if(mALARM->AlarmDateWeekDay > mRTC->sDate.Date)
        {
        
            dtmp = mALARM->AlarmDateWeekDay - mRTC->sDate.Date;
        }
    }
    
    /* Alarm Hour Check */
    if(mALARM->AlarmTime.Hours > mRTC->sTime.Hours)
        htmp += (mALARM->AlarmTime.Hours - mRTC->sTime.Hours);
    else
        htmp -= (mRTC->sTime.Hours - mALARM->AlarmTime.Hours);
    
    /* Alarm Minute Check */
    if(mALARM->AlarmTime.Minutes > mRTC->sTime.Minutes)
        mtmp += (mALARM->AlarmTime.Minutes - mRTC->sTime.Minutes);
    else
    {
        if(mALARM->AlarmTime.Minutes < mRTC->sTime.Minutes)
        {
            htmp = htmp - 1;
            mtmp = (mtmp+60);
            mtmp = (mtmp -(mRTC->sTime.Minutes - mALARM->AlarmTime.Minutes));
        }
        else
            mtmp = 0;
    }
    
    /* Alarm Second Check */
    if(mALARM->AlarmTime.Seconds > mRTC->sTime.Seconds)
        stmp = mALARM->AlarmTime.Seconds - mRTC->sTime.Seconds;
    else
    {
        if(mALARM->AlarmTime.Seconds < mRTC->sTime.Seconds)
        {
            mtmp = mtmp - 1;
            stmp = stmp + 60;
            stmp = (stmp-(mRTC->sTime.Seconds - mALARM->AlarmTime.Seconds));
        }
        else
            stmp = 0;
    }
    
    tmpreg = stmp+(mtmp*60)+(htmp*3600)+(dtmp*86400);
    
    __DRV_RTC_ALARM_SET(mRTC, tmpreg);
    
    mRTC->State = MID_RTC_STATE_READY;
    
    return MID_OK;
}

/**
 *******************************************************************************
 * @brief       Set RTC Alarm Interrupt Set.
 * @param[in]   mRTC : pointer to a RTC_HandleTypeDef
 * @return      return MID_OK
 *******************************************************************************
 */
MID_StatusTypeDef MID_RTC_SetAlarm_IT(RTC_HandleTypeDef *mRTC)
{
    __DRV_RTC_LOCK(mRTC);
    mRTC->State = MID_RTC_STATE_BUSY;
    
    __DRV_RTC_WRITEPROTECT_DISABLE(mRTC);
    
    /* RTC alarm interrupt enable */
    __DRV_RTC_ALARM_ENABLE(mRTC);
    __DRV_RTC_ENABLE_IT(mRTC , RTC_IT_ALM);
    
    __DRV_RTC_WRITEPROTECT_ENABLE(mRTC);
    
    mRTC->State = MID_RTC_STATE_READY;
    __DRV_RTC_UNLOCK(mRTC);
    return MID_OK;
}
///@}

/**
* @name    RTC Interrupt Request
*
*/
///@{
/**
 *******************************************************************************
 * @brief       Handle RTC interrupt request
 * @param[in]   mRTC : pointer to a RTC_HandleTypeDef
 * @return      return MID_OK
 *******************************************************************************
 */
void MID_RTC_IRQHandler(RTC_HandleTypeDef *mRTC)
{
    /* Get RTC Reload and Capture interrupt source enable status */
    if(__DRV_RTC_GET_FLAG(mRTC , RTC_IT_RCR) != 0U)
    {
        /* RTC RCR Callback */
        MID_RTC_RCRCallback(mRTC);
        
        /* Clear the reload and capture interrupt peding bit */
        __DRV_RTC_CLEAR_FLAG(mRTC , RTC_IT_RCR);
    }
    /* Get RTC Overflow interrupt source enable status */
    if(__DRV_RTC_GET_FLAG(mRTC , RTC_IT_TIE) != 0U)
    {
        /* RTC Overflow Callback */
        MID_RTC_TFCallback(mRTC);
        
        /* Clear the overflow interrupt pending bit */
        __DRV_RTC_CLEAR_FLAG(mRTC , RTC_IT_TIE);
    }
    /* Get RTC Time Stamp interrupt source enable status */
    if(__DRV_RTC_GET_FLAG(mRTC , RTC_IT_TS) != 0U)
    {
        /* RTC Time Stamp Callback */
        MID_RTC_TSCallback(mRTC);
        
        /* Clear the time stamp interrupt peding bit */
        __DRV_RTC_CLEAR_FLAG(mRTC , RTC_IT_TS);
    }
    /* Get RTC Periodic interrupt source enable status */
    if(__DRV_RTC_GET_FLAG(mRTC , RTC_IT_PC) != 0U)
    {
         /* RTC Periodic Callback */
        MID_RTC_PCCallback(mRTC);
        
        /* Clear the Periodic interrupt peding bit */
        __DRV_RTC_CLEAR_FLAG(mRTC , RTC_IT_PC);
    }
    /* Get RTC Alarm interrup source enable status */
    if(__DRV_RTC_GET_FLAG(mRTC , RTC_IT_ALM) != 0U)
    {
         /* RTC Alarm Callbacl */
        MID_RTC_AlarmCallback(mRTC);
        
        /* Clear the alarm interrupt peding bit */
        __DRV_RTC_CLEAR_FLAG(mRTC , RTC_IT_ALM);
    }
    
}
///@}

/**
* @name    RTC Call Back Function
*
*/
///@{
/**
 *******************************************************************************
 * @brief       RTC capture and reload callback.
 * @param[in]   mRTC : pointer to a RTC_HandleTypeDef
 * @return      return MID_OK
 *******************************************************************************
 */
__weak void MID_RTC_RCRCallback(RTC_HandleTypeDef *mRTC)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mRTC);

    /* NOTE : This function should not be modified, when the callback is needed,
       the HAL_RTC_AlarmAEventCallback could be implemented in the user file
    */
}

/**
 *******************************************************************************
 * @brief       RTC overflow callback.
 * @param[in]   mRTC : pointer to a RTC_HandleTypeDef
 * @return      return MID_OK
 *******************************************************************************
 */
__weak void MID_RTC_TFCallback(RTC_HandleTypeDef *mRTC)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mRTC);

    /* NOTE : This function should not be modified, when the callback is needed,
       the HAL_RTC_AlarmAEventCallback could be implemented in the user file
    */
}

/**
 *******************************************************************************
 * @brief       RTC time stamp callback.
 * @param[in]   mRTC : pointer to a RTC_HandleTypeDef
 * @return      return MID_OK
 *******************************************************************************
 */
__weak void MID_RTC_TSCallback(RTC_HandleTypeDef *mRTC)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mRTC);

    /* NOTE : This function should not be modified, when the callback is needed,
       the HAL_RTC_AlarmAEventCallback could be implemented in the user file
    */
}

/**
 *******************************************************************************
 * @brief       RTC periodic callback.
 * @param[in]   mRTC : pointer to a RTC_HandleTypeDef
 * @return      return MID_OK
 *******************************************************************************
 */
__weak void MID_RTC_PCCallback(RTC_HandleTypeDef *mRTC)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mRTC);

    /* NOTE : This function should not be modified, when the callback is needed,
       the HAL_RTC_AlarmAEventCallback could be implemented in the user file
    */
}

/**
 *******************************************************************************
 * @brief       RTC alarm callback.
 * @param[in]   mRTC : pointer to a RTC_HandleTypeDef
 * @return      return MID_OK
 *******************************************************************************
 */
__weak void MID_RTC_AlarmCallback(RTC_HandleTypeDef *mRTC)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(mRTC);

    /* NOTE : This function should not be modified, when the callback is needed,
       the HAL_RTC_AlarmAEventCallback could be implemented in the user file
    */
}
///@}

/**
* @name    Deactivate RTC Alarm
*
*/
///@{
/**
 *******************************************************************************
 * @brief       Deactivate RTC Alarm
 * @param[in]   mRTC : pointer to a RTC_HandleTypeDef
 * @return      return MID_OK
 *******************************************************************************
 */
MID_StatusTypeDef MID_RTC_DeactivateAlarm(RTC_HandleTypeDef *mRTC)
{
    uint32_t starttick = 0U;
    /* Process Lock */
    __DRV_RTC_LOCK(mRTC);
    mRTC->State = MID_RTC_STATE_BUSY;
    
    __DRV_RTC_WRITEPROTECT_DISABLE(mRTC);
    /* RTC Alarm Function and Interrupt Disable */
    __DRV_RTC_ALARM_DISABLE(mRTC);
    __DRV_RTC_DISABLE_IT(mRTC , RTC_IT_ALM);
    __DRV_RTC_CLEAR_FLAG(mRTC , RTC_STA_ALMF);          /* Clear RTC Alarm Event Flag */
    
    while(__DRV_RTC_GET_FLAG(mRTC, RTC_STA_ALMF)==MID_RTC_STATE_RESET)
    {
        if(MID_GetTick()-starttick>RTC_TIMEOUT_VALUE)
        {
            mRTC->State = MID_RTC_STATE_TIMEOUT;
            
            __DRV_RTC_UNLOCK(mRTC);
            
            return MID_TIMEOUT;
        }
    }
    
    __DRV_RTC_WRITEPROTECT_ENABLE(mRTC);
    /* Process Unlock */
    mRTC->State = MID_RTC_STATE_READY;
    
    return MID_OK;
}
///@}

/**
* @name    Get RTC Status
*
*/
///@{
/**
 *******************************************************************************
 * @brief       Get RTC Even State.
 * @param[in]   mRTC : pointer to a RTC_HandleTypeDef
 * @return      retrun mRTC->State
 *******************************************************************************
 */
uint32_t MID_RTC_GetState(RTC_HandleTypeDef *mRTC)
{
    /* Return RTC handle state */
    return mRTC->State;
}
///@}

/**
* @name    RTC Calendar Function
*
*/
///@{
/**
 *******************************************************************************
 * @brief       MID_RTC_Capture Register Convert
 * @param[in]   mRTC : pointer to a RTC_HandleTypeDef
 * @param[in]   RTC_CAP : RTC counter value
 * @return      retrun mRTC->State
 *******************************************************************************
 */
MID_StatusTypeDef MID_RTC_Capture_Convert(RTC_HandleTypeDef *mRTC, uint32_t RTC_CAP)
{
    uint64_t TempC = 0U;
    const uint8_t MonthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const uint8_t MonthMap[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,11, 12};
    uint8_t MaxDayOfMonth;
    
    /* Addition base time */
    TempC = (uint32_t)(mRTC->sTime.Hours * 3600);
    TempC += (uint32_t) (mRTC->sTime.Minutes * 60);
    TempC += (uint8_t)  (mRTC->sTime.Seconds);
    
    RTC_CAP += TempC;
    
    /* Convert to Second, Minute, Hour */
    mRTC->sTime.Seconds = RTC_CAP % 60;
    mRTC->sTime.Minutes = ((RTC_CAP/60)%60); 
    mRTC->sTime.Hours   = (RTC_CAP/3600)%24;
    
    if((mRTC->Init.HourFormat&RTC_FMT)==RTC_FMT)
    {
        if((mRTC->sTime.Hours)>=12U)
        {
            mRTC->sTime.TimeFormat = RTC_STA_PM;
            if(mRTC->sTime.Hours>12)
                mRTC->sTime.Hours = mRTC->sTime.Hours-12U;
        }
        else
            mRTC->sTime.TimeFormat &= ~RTC_STA_PM;
        
        if(mRTC->sTime.Hours==0U)
                mRTC->sTime.Hours = 12U;
    }
    
    /* Fill Date, Month, Year */
    TempC = RTC_CAP / 86400;
    
    MaxDayOfMonth = MonthDays[mRTC->sDate.Month];
    if(mRTC->sDate.Month == February)
    {
        if(MID_RTC_LeapYearCheck(mRTC)==isLeapYear)
        {
            MaxDayOfMonth = 29;
        }
    }
    
    if(TempC>MaxDayOfMonth)
    {
        TempC -= (MaxDayOfMonth - mRTC->sDate.Date);
        mRTC->sDate.Month++;
        
        if(mRTC->sDate.Month>December)
        {
            mRTC->sDate.Month = January;
            mRTC->sDate.Year++;
        }
        
        /* Year */
        while(TempC>365)
        {
            if(MID_RTC_LeapYearCheck(mRTC)==isLeapYear)
            {
                TempC -= 366;
            }
            else
            {
                TempC -= 365;
            }
            
            mRTC->sDate.Year++;
        }
        /* Month */
        while(TempC>MaxDayOfMonth)
        {
            switch(mRTC->sDate.Month)
            {
                case    January:
                    
                case    February:
                                if(MID_RTC_LeapYearCheck(mRTC)==isLeapYear)
                                    TempC -= 29;
                                else
                                    TempC -= 28;
                                break;
                case March:
                case May:
                case July:
                case August:
                case October:
                case December:
                                TempC -= 31;
                                break;
                
                case April:
                case June:
                case September:
                case November:
                                TempC -= 30;
                                break;
                default:
                                break;
            }
            mRTC->sDate.Month++;
            
            if(mRTC->sDate.Month>December)
            {
                mRTC->sDate.Month = January;
                mRTC->sDate.Year++;
            }
            
            MaxDayOfMonth = MonthDays[mRTC->sDate.Month];
            
            if(mRTC->sDate.Month == February)
            {
                if(MID_RTC_LeapYearCheck(mRTC)==isLeapYear)
                    MaxDayOfMonth = 29;
            }
        }
        
        mRTC->sDate.Date = (uint8_t)TempC;
    }
    
    else
    {
        mRTC->sDate.Date += TempC;
        
        if(mRTC->sDate.Date > MaxDayOfMonth)
        {
            mRTC->sDate.Date -= MaxDayOfMonth;
            mRTC->sDate.Month++;
            
            if(mRTC->sDate.Month>December)
            {
                mRTC->sDate.Month = January;
                mRTC->sDate.Year++;
            }
        }
    }
    
    mRTC->sDate.Month = MonthMap[mRTC->sDate.Month];
    
    return MID_OK;
}

/**
 *******************************************************************************
 * @brief       Leap Year Check
 * @param[in]   mRTC : pointer to a RTC_HandleTypeDef
 * @return      retrun isLeapYear / noLeapYear
 *******************************************************************************
 */
MID_RTC_StateTypeDef MID_RTC_LeapYearCheck(RTC_HandleTypeDef *mRTC)
{
    if ( ( mRTC->sDate.Year % 4 == 0 && mRTC->sDate.Year % 100 != 0 ) || ( mRTC->sDate.Year % 400 == 0 ) )
        return isLeapYear;

    return noLeapYear;
}

/**
 *******************************************************************************
 * @brief       Get Weekend
 * @param[in]   mRTC : pointer to a RTC_HandleTypeDef
 * @return      Non
 *******************************************************************************
 */
uint32_t MID_RTC_GetWeekend(RTC_HandleTypeDef *mRTC)
{
    uint8_t  M, D;
    uint32_t C, Y;
    const   uint8_t MonthWeekendTable[] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
    
    C = (mRTC->sDate.Year/100);
    Y = (mRTC->sDate.Year%100);
    M = MonthWeekendTable[mRTC->sDate.Month];
    D = (mRTC->sDate.Date % 7);
    
    /* Calendar Century Factor */
    C = 2 * (3 - (C %4));
    
    /* Calendar Year Factor */
    Y = ((Y %28) + ((Y %28) /4)) %7;
    
    if(MID_RTC_LeapYearCheck(mRTC)==isLeapYear)
    {
        if((mRTC->sDate.Month==February)||(mRTC->sDate.Month==February))
            Y--;
    }
    
    /* Calendar Weekend */
    mRTC->sDate.WeekDay = (Weekend_TypeDef) ((C+Y+M+D)%7);
    
    return mRTC->sDate.WeekDay;
}
///@}

