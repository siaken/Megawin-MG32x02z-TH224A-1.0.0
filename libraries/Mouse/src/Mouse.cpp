
/*
  Mouse.cpp

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

#include "Mouse.h"
#include "MG32x02z.h"
#include "MG32x02z_USBD_API.h"
#include "MG32x02z_USBD_MouseDescriptor.h"

#if defined(USBCON)
//#include "usbd_hid_composite_if.h"

//================================================================================
//================================================================================
//  Mouse

Mouse_::Mouse_(USB_EP_Struct*  EPX)
{
    m_EPX = EPX;
    Parameter_DeInit();
    m_Mouse_CTR.Status = USBA_Status_Idle;
}

void Mouse_::Parameter_DeInit(void)
{
    uint8_t i;
    
    m_Mouse_CTR.IdleRate            = 0;
    m_Mouse_CTR.Protocol            = 1;
    
    m_Mouse_CTR.ReportDataTmp.Button.B = 0;
    m_Mouse_CTR.ReportDataTmp.X_Axis.H = 0;
    m_Mouse_CTR.ReportDataTmp.Y_Axis.H = 0;
    m_Mouse_CTR.ReportDataTmp.Wheel    = 0;
    for( i = 0; 
         i < Mosue_ReportSize;
         i++ )
    {
        m_Mouse_CTR.ReportData[i] = 0;
    }

    m_Mouse_CTR.BaseCount           = 0;
}



void Mouse_::begin(void)
{
    __DRV_USB_DISCONNECT();
    delay(500);
    
  
    /*Mouse status */
    m_Mouse_CTR.Status = USBA_Status_Init;


    g_UsbEP1Ctr.Status = USBA_Status_Idle,
    g_UsbEP1Ctr.IdleRate = 0,
    g_UsbEP1Ctr.Protocol = m_Mouse_CTR.Protocol ;

    g_UsbEP1Ctr.mHID0_ReportLength = Mouse_HID0_ReportLength,
    g_UsbEP1Ctr.mHID1_ReportLength = 0,
    g_UsbEP1Ctr.pUSB_INTERFACE0_HID_REPORT = Mouse_USB_INTERFACE0_HID_REPORT,
    g_UsbEP1Ctr.pUSB_INTERFACE1_HID_REPORT = NULL,


    g_UsbEP1Ctr.pUSB_DEVICE_DESCRIPTOR = Mouse_USB_DEVICE_DESCRIPTOR,
    g_UsbEP1Ctr.pUSB_CONFIGURATION_DESCRIPTOR = Mouse_USB_CONFIGURATION_DESCRIPTOR,
    g_UsbEP1Ctr.pUSB_STRING_DESCRIPTOR = Mouse_USB_STRING_DESCRIPTOR,

    #if MF_STRING == 1                                          
    g_UsbEP1Ctr.pManufacturer_Descriptor = Mouse_Manufacturer_Descriptor,
    #endif      
    #if PD_STRING == 1                                          
    g_UsbEP1Ctr.pProduct_Descriptor = Mouse_Product_Descriptor,
    #endif   
    #if SN_STRING == 1                                          
    g_UsbEP1Ctr.pSerialNumber_Descriptor = Mouse_SerialNumber_Descriptor,
    #endif 
    #if MG_USB_LPM_EN == 1                                      
    g_UsbEP1Ctr.pUSB_BOS_DESCRIPTOR = Mouse_USB_BOS_DESCRIPTOR,
    g_UsbEP1Ctr.pUSB_EXT_DESCRIPTOR = Mouse_USB_EXT_DESCRIPTOR,
    #endif



    __DRV_USB_CONNECT();

    /*USB inital*/
    API_USBD_Inital(); 
    
    /*Parameter inital*/
    Parameter_DeInit();


    
    /*Mouse status */
    m_Mouse_CTR.Status = USBA_Status_Idle;
}


void Mouse_::end(void)
{
    Parameter_DeInit();
    __DRV_USB_DISCONNECT();
}

void Mouse_::click(uint8_t b)
{
  press( b);
  delay(30);
  release( b);
}


void Mouse_::MouseReport(void)
{
    int16_t API_Mouse_ReportHandlerTmp;
    
    /*Judge Mouse report whether change or not.*/
    if( (m_Mouse_CTR.Status & USBA_Status_ReportChange)==0)
    {
        return;
    }

    m_Mouse_CTR.Protocol = g_UsbEP1Ctr.Protocol;
    if((Ep0.USBStatus & USB_STATUS_EMULATION_MASK)==USB_STATUS_EMULATION_OK)
    {
        m_Mouse_CTR.Status  = USBA_Status_UpdateReport;
        
        if(m_Mouse_CTR.Protocol == 1)
        {  
            m_Mouse_CTR.ReportData[Mouse_Report_Button] = m_Mouse_CTR.ReportDataTmp.Button.B;
            m_Mouse_CTR.ReportData[Mouse_Report_X_L]    = m_Mouse_CTR.ReportDataTmp.X_Axis.B[0];
            m_Mouse_CTR.ReportData[Mouse_Report_X_H]    = m_Mouse_CTR.ReportDataTmp.X_Axis.B[1];
            m_Mouse_CTR.ReportData[Mouse_Report_Y_L]    = m_Mouse_CTR.ReportDataTmp.Y_Axis.B[0];
            m_Mouse_CTR.ReportData[Mouse_Report_Y_H]    = m_Mouse_CTR.ReportDataTmp.Y_Axis.B[1];
            m_Mouse_CTR.ReportData[Mouse_Report_Wheel]  = (uint8_t)m_Mouse_CTR.ReportDataTmp.Wheel; 

            USB_SetEndpointTXData( m_EPX , &m_Mouse_CTR.ReportData[0], Mosue_ReportSize);
            
        }
        else
        {
            m_Mouse_CTR.ReportData[Mouse_BIOS_Report_Button] = m_Mouse_CTR.ReportDataTmp.Button.B;
            
            API_Mouse_ReportHandlerTmp = (int16_t)m_Mouse_CTR.ReportDataTmp.X_Axis.H;
            
            if( API_Mouse_ReportHandlerTmp > 127)
            {
                m_Mouse_CTR.ReportData[Mouse_BIOS_Report_X] = 0x7F;
            }
            else if( API_Mouse_ReportHandlerTmp < -127)
            {
                m_Mouse_CTR.ReportData[Mouse_BIOS_Report_X] = 0x81;
            }
            else
            {
                m_Mouse_CTR.ReportData[Mouse_BIOS_Report_X] = m_Mouse_CTR.ReportDataTmp.X_Axis.B[0];
            }
            
            API_Mouse_ReportHandlerTmp = (int16_t)m_Mouse_CTR.ReportDataTmp.Y_Axis.H;
            
            if( API_Mouse_ReportHandlerTmp > 127)
            {
                m_Mouse_CTR.ReportData[Mouse_BIOS_Report_Y] = 0x7F;
            }
            else if( API_Mouse_ReportHandlerTmp < -127)
            {
                m_Mouse_CTR.ReportData[Mouse_BIOS_Report_Y] = 0x81;
            }
            else
            {
                m_Mouse_CTR.ReportData[Mouse_BIOS_Report_Y] = m_Mouse_CTR.ReportDataTmp.Y_Axis.B[0];
            }
            
            USB_SetEndpointTXData( m_EPX , &m_Mouse_CTR.ReportData[0], Mouse_BIOS_ReportSize);
        }
        m_Mouse_CTR.ReportDataTmp.Wheel             = 0;
    }
}

void Mouse_::move(signed char x, signed char y, signed char wheel)
{
    m_Mouse_CTR.ReportDataTmp.X_Axis.H =  x;
    m_Mouse_CTR.ReportDataTmp.Y_Axis.H =  y;
    m_Mouse_CTR.ReportDataTmp.Wheel    =  wheel;
    m_Mouse_CTR.Status |= USBA_Status_WheelReportChange;
  
    MouseReport();
}

void Mouse_::buttons(uint8_t b)
{
    if (b != m_Mouse_CTR.ReportDataTmp.Button.B ) 
    {
        m_Mouse_CTR.ReportDataTmp.Button.B = b;
        m_Mouse_CTR.Status |= USBA_Status_BNTReportChange;
        move(0, 0, 0);
    }
}

void Mouse_::press(uint8_t b)
{
    buttons( m_Mouse_CTR.ReportDataTmp.Button.B | b );
}

void Mouse_::release(uint8_t b)
{
    buttons( m_Mouse_CTR.ReportDataTmp.Button.B & ~b);
}

bool Mouse_::isPressed(uint8_t b)
{
    if ((b & m_Mouse_CTR.ReportDataTmp.Button.B) > 0) 
    {
        return true;
    }
    return false;
}

Mouse_ Mouse(USER_Mouse_EPn);

#endif




