


 /**
 ******************************************************************************
 *
 * @file        USBD_DSC.h
 * @brief       The USBD Descriptor's h file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.02
 * @date        2022/08/10
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 * 
 ******************************************************************************* 
 * @par Disclaimer
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


#ifndef _USB_DSC_H
#define _USB_DSC_H

#include "MG32x02z.h"
#include "MG32x02z_USB_Init.h"





extern const uint16_t Key_HID0_ReportLength;
extern const uint16_t Key_HID1_ReportLength;

 
extern const uint8_t Key_USB_INTERFACE0_HID_REPORT[];              /*!< HID report of interface0.*/
extern const uint8_t Key_USB_INTERFACE1_HID_REPORT[];              /*!< HID report of interface1.*/

extern const uint8_t Key_USB_DEVICE_DESCRIPTOR[];                  /*!< Device Descriptor.*/
extern const uint8_t Key_USB_CONFIGURATION_DESCRIPTOR[];           /*!< Configuration Descriptor.*/
extern const uint8_t Key_USB_STRING_DESCRIPTOR[];                  /*!< String descriptor.*/

#if MF_STRING == 1
//#define MFS_LEN (sizeof(MANUFACTURER_DESCRIPTOR)*2    )        /*!< Manufacture descriptor size.*/

extern  const uint8_t Key_Manufacturer_Descriptor[];               /*!< Manufacture string descriptor.*/

#endif


#if PD_STRING == 1
#define PDS_LEN (sizeof(PRODUCT_DESCRIPTOR)*2)                 /*!< Product descriptor size.*/

extern const uint8_t Key_Product_Descriptor[];                     /*!< Product string descriptor.*/

#endif

#if SN_STRING == 1

#define SNS_LEN (sizeof(SERIALNUMBER_DESCRIPTOR)*2)            /*!< Serial number descriptor size.*/
extern const uint8_t Key_SerialNumber_Descriptor[];                /*!< Serial number string descriptor.*/
#endif

#if MG_USB_LPM_EN == 1
extern const uint8_t Key_USB_BOS_DESCRIPTOR[];                     /*!< BOS descriptor.*/
extern const uint8_t Key_USB_EXT_DESCRIPTOR[];                     /*!< Device capabilty descriptor.*/
#endif

#endif
















