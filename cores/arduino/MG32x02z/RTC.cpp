/**
 **************************************************
 *
 * @file        RTC.cpp
 * @brief       MG32x02z RTC module driver source cpp file
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     @ Zvonimir Haramustek for soldered.com
 ***************************************************/
#include "RTC.h"

#ifdef __cplusplus
extern "C" {

#include "MG32x02z_RTC_MID.h"

}
#endif


RTC_HandleTypeDef   mRTC;

/**
 * @brief       Main constructor
 */
MG32x02z_RTC::MG32x02z_RTC(void)
{
    m_RTC = &mRTC;
  
    m_RTC->Instance        = RTC;
    m_RTC->Init.RTC_CK_SEL = RTC_CLK_LS;     //RTC clock source select
    m_RTC->Init.RTC_RLR    = 0x00000000;     //RTC reload register set 0~0xFFFFFFFE, 0xFFFFFFFF forbidden.

    m_RTC->sTime.Seconds = 2;
    m_RTC->sTime.Minutes = 0;
    m_RTC->sTime.Hours   = 0;
    
    m_RTC->sDate.Date      = 1;
    m_RTC->sDate.Month     = January;
    m_RTC->sDate.Year      = 2023;
    m_RTC->sDate.WeekDay   = Sunday;
    m_RTC->Init.HourFormat = RTC_HOURFORMAT_24;      /*!< Date hours format set.(0 = 24hr, 1 = 12hr) */


    m_alarm_second   = 0;
    m_alarm_minute   = 0;
    m_alarm_hour     = 0;
    m_alarm_day      = 0;

    //m_alarm_weekday  = 0;
}


/*
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
*/


/**
 * @brief                   Initialize communication
 */
void MG32x02z_RTC::begin()
{
    // make sure :
    
    //===Set CSC init====
    //MG32x02z_CSC_Init.h(Configuration Wizard)
    //CK_LS clock can from ILRCO or external XTAL(One second time domain, use 32.768kHz XTAL please, then enable XTAL in MG32x02z_CSC_Init)
    //If change RTC_RLR will changed RTC count time range suggest write 0x00000000
    //Can select RTC_HOURFORMAT_12 or RTC_HOURFORMAT_24
    // ------------------------------------------------------------------------
    // 1.Initial RTC. 
    // ------------------------------------------------------------------------
    m_RTC->Instance = RTC;
    m_RTC->Init.RTC_CK_SEL = RTC_CLK_LS;          //RTC clock source select
    m_RTC->Init.RTC_RLR = 0x00000000;             //RTC reload register set 0~0xFFFFFFFE, 0xFFFFFFFF forbidden.
    
    // ------------------------------------------------------------------------
    // 1.Initial calendar date. 
    // ------------------------------------------------------------------------
    m_RTC->sTime.Seconds = 2;
    m_RTC->sTime.Minutes = 0;
    m_RTC->sTime.Hours   = 0;
    
    m_RTC->sDate.Date      = 1;
    m_RTC->sDate.Month     = January;
    m_RTC->sDate.Year      = 2023;
    m_RTC->sDate.WeekDay   = Sunday;

    m_RTC->Init.HourFormat = RTC_HOURFORMAT_24;      /*!< Date hours format set.(0 = 24hr, 1 = 12hr) */

    MID_RTC_Init(  m_RTC );
    MID_RTC_GetTime( m_RTC );
}

void MG32x02z_RTC::setTime(uint8_t hour, uint8_t minute, uint8_t sec)
{
    //先获取最新的值
    MID_RTC_GetTime( m_RTC );
    
    
    m_RTC->sDate.Month     = m_RTC->sDate.Month - 1;

/*
    if( sec < 0 )
    {
        sec = 0;
    }
    else 
*/
    if( sec >  60 )
    {
        sec = 60;
    }

/*
    if( minute < 0 )
    {
        minute = 0;
    }
    else
*/
    if( minute >  60 )
    {
        minute = 60;
    }

/*
    if( hour < 0 )
    {
        hour = 0;
    }
    else
*/
    if( hour > 24 )
    {
        hour = 0;
    }

    //设置的时间值
    m_RTC->sTime.Seconds = sec;
    m_RTC->sTime.Minutes = minute;
    m_RTC->sTime.Hours   = hour;
    m_RTC->Init.RTC_RLR  = 0x00000000;

    MID_RTC_Init( m_RTC );
}

void MG32x02z_RTC::setDate(uint8_t day, uint8_t month, uint16_t yr)
{
    setDate(0, day, month, yr);
}

void MG32x02z_RTC::setDate(uint8_t weekday, uint8_t day, uint8_t month, uint16_t yr)
{
    weekday = weekday;
    //先获取最新的值
    MID_RTC_GetTime( m_RTC );

    if( yr < 2020 )
    {
        yr = 2020;
    }

    if( day < 1 )
    {
        day = 1;
    }
    else if( day >  31 )
    {
        day = 31;
    }

    month = month - 1;
/*
    if( month < January )
    {
        month = January;
    }
    else
*/
    if( month > December )
    {
        month = January;
    }

    //设置的日期值
    m_RTC->sDate.Date      = day;
    m_RTC->sDate.Month     = month;
    m_RTC->sDate.Year      = yr;
    

    //后续readTime会被更新
    //m_RTC->sDate.WeekDay   = weekday;
    m_RTC->Init.RTC_RLR    = 0x00000000;

    MID_RTC_Init( m_RTC );

//    MID_RTC_SetTime( m_RTC,  m_RTC->Init.RTC_RLR );
}

void MG32x02z_RTC::readTime()
{
    MID_RTC_GetTime( m_RTC );
}

/* read RTC times */
uint8_t  MG32x02z_RTC::getSecond()
{
    MID_RTC_GetTime( m_RTC );
    return m_RTC->sTime.Seconds;
}
uint8_t  MG32x02z_RTC::getMinute()
{
    MID_RTC_GetTime( m_RTC );
    return m_RTC->sTime.Minutes;
}
uint8_t  MG32x02z_RTC::getHour()
{
    MID_RTC_GetTime( m_RTC );
    return m_RTC->sTime.Hours;
}

uint8_t  MG32x02z_RTC::getDay()
{
    MID_RTC_GetTime( m_RTC );
    return m_RTC->sDate.Date;
}
uint8_t  MG32x02z_RTC::getWeekday()
{
    MID_RTC_GetTime( m_RTC );
    return m_RTC->sDate.WeekDay;
}
uint8_t  MG32x02z_RTC::getMonth()
{
    MID_RTC_GetTime( m_RTC );
    return m_RTC->sDate.Month;
}
uint16_t MG32x02z_RTC::getYear()
{
    MID_RTC_GetTime( m_RTC );
    return m_RTC->sDate.Year;
}

// called on setAlarm_IT()
void  MG32x02z_RTC::enableAlarm()
{
    RTC_AlarmTypeDef  mALARM;
    mALARM.AlarmDateWeekDaySel = 0;
    mALARM.AlarmDateWeekDaySel    = m_alarm_day;
    
    mALARM.AlarmTime.Hours   = m_alarm_hour;
    mALARM.AlarmTime.Minutes = m_alarm_minute;
    mALARM.AlarmTime.Seconds = m_alarm_second;
    
    MID_RTC_SetAlarm( m_RTC,  &mALARM );

    if( user_onAlarm != NULL )
    {
        MID_RTC_SetAlarm_IT( m_RTC );
    }
}

void MG32x02z_RTC::onAlarmService()
{
    if( user_onAlarm != NULL )
    {
        user_onAlarm();
    }
}

void  MG32x02z_RTC::onAlarm(   void (*function)(void) )
{
    user_onAlarm = function;
}
/**
 *******************************************************************************
 * @brief       RTC alarm callback.
 * @param[in]   mRTC : pointer to a RTC_HandleTypeDef
 * @return      return MID_OK
 *******************************************************************************
 */
extern MG32x02z_RTC Rtc;
void MID_RTC_AlarmCallback(RTC_HandleTypeDef *pmRTC)
{
    if( pmRTC == &mRTC)
    {
        Rtc.onAlarmService();
    }
}


void  MG32x02z_RTC::setAlarm(  uint8_t alarm_second, uint8_t alarm_minute, uint8_t alarm_hour, uint8_t alarm_day  )
{
    MID_RTC_GetTime( m_RTC );

    m_alarm_second = alarm_second;
    m_alarm_minute = alarm_minute;
    m_alarm_hour   = alarm_hour;
    m_alarm_day    = alarm_day;
    
    enableAlarm( );
}

void  MG32x02z_RTC::readAlarm()
{
  uint32_t   uAlarmCompareValue;
  uAlarmCompareValue =  RTC_GetAlarmCompareValue();

  m_alarm_day  = (uAlarmCompareValue/86400);
  m_alarm_hour = (uAlarmCompareValue - m_alarm_day*86400)/3600;

  m_alarm_minute = (uAlarmCompareValue - m_alarm_day*86400 - m_alarm_hour*3600)/60;
  m_alarm_second = (uAlarmCompareValue - m_alarm_day*86400 - m_alarm_hour*3600- m_alarm_minute*60);
}


uint8_t MG32x02z_RTC::getAlarmSecond()
{
    readAlarm();
    return m_alarm_second;
}
uint8_t MG32x02z_RTC::getAlarmMinute()
{
    readAlarm();
    return m_alarm_minute;
}
uint8_t MG32x02z_RTC::getAlarmHour()
{
    readAlarm();
    return m_alarm_hour;
}
uint8_t MG32x02z_RTC::getAlarmDay()
{
    readAlarm();
    return m_alarm_day;
}
/*
uint8_t MG32x02z_RTC::getAlarmWeekday()
{
    readAlarm();
    return m_alarm_weekday;
}
*/




MG32x02z_RTC   Rtc;

