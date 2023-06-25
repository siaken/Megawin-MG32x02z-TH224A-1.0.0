/**
 **************************************************
 *
 * @file        RTC.h
 * @brief       PRTC.h header file
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Megawin
 ***************************************************/
#ifndef  _RTC_H_
#define  _RTC_H_

#include "Arduino.h"


#ifdef __cplusplus
 extern "C" {

#include "MG32x02z_DRV.h"
#include "MG32x02z_RTC_MID.h"

}
#endif


class MG32x02z_RTC
{
public:
    MG32x02z_RTC();

    void begin();

    void  setTime(uint8_t hour, uint8_t minute, uint8_t sec);
    void  setDate(uint8_t day, uint8_t month, uint16_t yr);
    void  setDate(uint8_t weekday, uint8_t day, uint8_t month, uint16_t yr);
    void  readTime();

    void  enableAlarm(); 
    void  onAlarm(   void (*function)(void) ); 
    void  setAlarm( uint8_t alarm_second, uint8_t alarm_minute, uint8_t alarm_hour, uint8_t alarm_day );
    void  readAlarm();

    void  reset();

    /* read RTC times */
    uint8_t  getSecond();
    uint8_t  getMinute();
    uint8_t  getHour();
    uint8_t  getDay();
    uint8_t  getWeekday();
    uint8_t  getMonth();
    uint16_t getYear();

    /* read alarm times */ // if return = 99, no alarm
    uint8_t getAlarmSecond();
    uint8_t getAlarmMinute();
    uint8_t getAlarmHour();
    uint8_t getAlarmDay();
    //uint8_t getAlarmWeekday();

public:
    void (*user_onAlarm)(void);
    void onAlarmService();

private:
    RTC_HandleTypeDef*   m_RTC;


    /* alarm */
    uint8_t m_alarm_second;
    uint8_t m_alarm_minute;
    uint8_t m_alarm_hour;
    uint8_t m_alarm_day;
    //uint8_t m_alarm_weekday;
};


extern MG32x02z_RTC   Rtc;
#endif


