
/*
  Mouse.h

  Copyright (c) 2023, Magawin
  Original code (pre-library): Copyright (c) 2011, Peter Barrett

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef   _MOUSE_H_
#define   _MOUSE_H_


#include <Arduino.h>

#if !defined(USBCON)   // || !defined(USBD_USE_HID_COMPOSITE)

#error "USB HID not enabled! Select 'HID' in the 'Tools->USB interface' menu."

#else

//================================================================================
#include "MG32x02z_USBD_API.h"



/*Report */
#define Mouse_BIOS_ReportSize           3        /*!< Mouse report size in BIOS*/
#define Mouse_BIOS_Report_Button        0        /*!< Mouse report byte0 is button in BIOS.*/
#define Mouse_BIOS_Report_X             1        /*!< Mouse report byte1 is Sensor_X in BIOS.*/
#define Mouse_BIOS_Report_Y             2        /*!< Mouse report byte2 is Sensor_X in BIOS.*/

#define Mosue_ReportSize                6        /*!< Mouse report size .*/
#define Mouse_Report_Button             0        /*!< Mouse report byte0 is Button.*/
#define Mouse_Report_X_L                1        /*!< Mouse report byte1 is Sensor_X low byte.*/
#define Mouse_Report_X_H                2        /*!< Mouse report byte2 is Sensor_X high byte.*/
#define Mouse_Report_Y_L                3        /*!< Mouse report byte3 is Sensor_Y low byte.*/
#define Mouse_Report_Y_H                4        /*!< Mouse report byte4 is Sensor_Y high byte.*/
#define Mouse_Report_Wheel              5        /*!< Mouse report byte5 is wheel data.*/


///@} 

/**
 * @name  typedef
 */
///@{
 
 
/*! @struct MouseReport_TypeDef
    @brief  Mouse report format
*/  
typedef struct
{
    union 
    {
        uint16_t H;
        uint8_t  B[2];
    }X_Axis;                                   /*!< Sensor X data.*/
    
    union 
    {
        uint16_t H;
        uint8_t  B[2];
    }Y_Axis;                                   /*!< Sensor Y data.*/
     
    union
    {
        uint8_t B;
        struct
        {
            uint8_t L_Button    :1;            /*!< Left     button.*/
            uint8_t R_Button    :1;            /*!< Right    button.*/
            uint8_t M_Button    :1;            /*!< Middle   button.*/
            uint8_t BW_Button   :1;            /*!< Backward button.*/
            uint8_t FW_Button   :1;            /*!< forward  button.*/
            uint8_t             :3;            /*!< reserve.*/
        }MBIT;
    }Button;
    
    int8_t Wheel;                              /*!< Wheel data.*/
    
}MouseReport_TypeDef;    
 
 
/*! @struct MouseCTR_TypeDef
    @brief  Mouse control struct
*/  
typedef struct 
{
    uint8_t             Status;              
    uint8_t             IdleRate;
    uint8_t             Protocol;
    
    uint8_t             BaseCount;
    
    MouseReport_TypeDef ReportDataTmp;                      
    uint8_t             ReportData[Mosue_ReportSize];       
    
}MouseCTR_TypeDef;



//================================================================================
/*USB*/
#define USER_Mouse_EPn                        USB_EP1    /*!< mouse use endpoint*/

//================================================================================
//  Mouse


#define MOUSE_LEFT      1
#define MOUSE_RIGHT     2
#define MOUSE_MIDDLE    4
#define MOUSE_ALL (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE)

class Mouse_
{
private:
//    uint8_t     m_buttons;
    USB_EP_Struct*    m_EPX;
    MouseCTR_TypeDef  m_Mouse_CTR;

/*
    uint32_t    m_pinB_L;
    uint32_t    m_pinB_R;
    uint32_t    m_pinB_M;
    uint32_t    m_pinB_BW;
    uint32_t    m_pinB_FW;
*/

private:
    void buttons(uint8_t b);
    void Parameter_DeInit(void);
    void MouseReport(void);
    
public:
    Mouse_(USB_EP_Struct*  EPX);

    void begin(void);
/*
    void begin( uint32_t  pinB_L,   uint32_t  pinB_R = -1,  uint32_t  pinB_M = -1,
                uint32_t  pinB_BW = -1,  uint32_t  pinB_FW = -1   );
*/

    void end(void);
    void click(uint8_t b = MOUSE_LEFT);
    void move(signed char x, signed char y, signed char wheel = 0);
    void press(uint8_t b = MOUSE_LEFT);   // press LEFT by default
    void release(uint8_t b = MOUSE_LEFT); // release LEFT by default
    bool isPressed(uint8_t b = MOUSE_LEFT); // check LEFT by default
};


extern Mouse_ Mouse;




#endif


#endif

