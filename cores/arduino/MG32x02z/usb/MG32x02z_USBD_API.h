

 /**
 ******************************************************************************
 *
 * @file        USBD_Core.h
 * @brief       The USBD core Code's h file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.01
 * @date        2022/01/12
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


#ifndef _USB_REG_H
#define _USB_REG_H


#include "MG32x02z.h"
#include "MG32x02z__ExtraStruct.h"
#include "MG32x02z_PW_DRV.h"
#include "MG32x02z_SYS_DRV.h"
#include "MG32x02z_MEM_DRV.h"
#include "MG32x02z_USB_DRV.h"
#include "MG32x02z_USB_Init.h"

/**
 * @name	============== Data type  ==============
 *   		
 */ 
///@{

#ifdef __cplusplus
extern "C" {
#endif


/*Mouse Status*/
#define USBA_Status_Idle                0x00                       /*!< Mouse state is idle*/
#define USBA_Status_Init                0x80                       /*!< Mouse state is initializing.*/
#define USBA_Status_UpdateReport        0x40                       /*!< Mouse update data to host.*/
#define USBA_Status_BNTReportChange     0x01                       /*!< Mouse button data of report change.*/
#define USBA_Status_SensorReportChange  0x02                       /*!< Mouse sensor data of report change.*/
#define USBA_Status_WheelReportChange   0x04                       /*!< Mouse wheel data of report change.*/

#define USBA_Status_ReportChange        (USBA_Status_BNTReportChange    | \
                                         USBA_Status_SensorReportChange | \
                                         USBA_Status_WheelReportChange)           /*Mouse report data change mask*/


#define    HIBYTE( V1 )     ((uint8_t)((V1) >> 8))                           /*!<Get high byte (8 ~ 15 bit) of 16 bit data.*/
#define    LOBYTE( V1 )     ((uint8_t)((V1) & 0xFF))                         /*!<Get low byte (8 ~ 15 bit) of 16 bit data.*/

///@}

/**
 * @name	============== USB protocal Relationship ==============
 *   		
 */ 
#define FKB_TOTALFUNCTION    0x14


#define    HID_REPORT_LENGTH sizeof(HID_REPORT)

#define    EP0_PACKET_SIZE       64                                       /*!< Maximum packet size for EP0.*/
#define    EP1_PACKET_SIZE        8                                       /*!< Maximum packet size for EP1.*/
#define    EP2_PACKET_SIZE        8                                       /*!< Maximum packet size for EP2.*/

#define USB_CONFIGURATION_DESC_SIZE        9          /*!< USB Configuration descriptor data size. */
#define USB_INTERFACE_DESC_SIZE            9          /*!< USB Interface descriptor data size. */
#define USB_HID_DESC_SIZE                  9          /*!< USB HID descriptor data size. */
#define USB_ENDPOINT_DESC_SIZE             7          /*!< USB Endpoint descriptor data size. */


 
 
///@{    
//------------------------------------------------
//Standard Request Code ( bRequest)
#define    GET_STATUS          0                                              /*!< This request returns status for the specified recipient.*/
#define    CLEAR_FRATURE       1                                              /*!< This request is used to clear or disable a specific feature.*/
#define    SET_FEATURE         3                                              /*!< This request is used to set or enable a specific feature.*/
#define	   SET_ADDRESS         5                                              /*!< This request sets the device address for all future device accesses.*/
#define    GET_DESCRIPTOR      6                                              /*!< This request returns the specified descriptor if the descriptor exists.*/
#define    SET_DESCRIPTOR      7                                              /*!< This request is iptional and may be used to update existing descriptors or new descriptors may be added.*/
#define    GET_CONFIGURATION   8                                              /*!< This request returns the current device configuration value.*/
#define    SET_CONFIGURATION   9                                              /*!< This request sets the device configuration.*/
#define    GET_INTERFACE       10                                             /*!< This request returns the selected alternate setting for the specified interface.*/
#define    SET_INTERFACE       11                                             /*!< The request allows the host to select an alternate setting for the specified interface.*/
#define    SYNCH_FRAME         12                                             /*!< The request is used to set and then report an endpoint's synchronization frame.*/
//------------------------------------------------
// HID Request Codes
#define    GET_REPORT          0x01                                           /*!< The GET_REPORT request allows the host to receive a report via the Control pipe.*/
#define    GET_IDLE            0x02                                           /*!< The GET_IDLE request reads the current idle rate for a particular input report.*/
#define    GET_PROTOCOL        0x03                                           /*!< The GET_PROTOCOL request reads which protocol is currently active.*/
#define    SET_REPORT          0x09                                           /*!< The SET_REPORT request allows the host to send a report to the device, possibly setting the state of input
                                                                                   , output , or feature controls.*/
#define    SET_IDLE            0x0A                                           /*!< The SET_IDLE request silences a particular report on the Interrupt IN pipe until a new event occurs or the
                                                                                   specified amount of time passes.*/
#define    SET_PROTOCOL        0x0B                                           /*!< The SET_PROTOCOL switches between the boot protocol and the report protocol.*/

//------------------------------------------------
//Request Data transfer direction of bmRequestType
#define    GET_REQUEST         0x80                                           /*!< Device to Host.*/
#define    SET_REQUEST         0x00                                           /*!< Host to Device.*/

//------------------------------------------------
//Type of bmRequestType 
#define    REQUEST_TYPE_MASK    0x60                                          /*!< Request Type Mask.*/
#define    STANDARD_REQUEST     0x00                                          /*!< Standard Request Type.*/
#define    CLASS_REQUEST        0x20                                          /*!< Class Request Type.*/
#define    VENDOR_REQUEST       0x40                                          /*!< Vendor Request Type.*/

//------------------------------------------------
//Recipient of bmRequestType 
#define    DEVICEREQUEST        0x00                                          /*!< Device.*/
#define    INTERFACEREQUEST     0x01                                          /*!< Interface.*/
#define    ENDPOINTREQUEST      0x02                                          /*!< Endpoint.*/

//-------------------------------------------------
//Feature Selectors in Standard Feature Selectors
#define    DEVICE_REMOTE_WAKEUP 0x01                                          /*!< Device Remote wakeup.*/
#define    ENDPOINT_HALT        0x00                                          /*!< Endpoint Halt.*/

//------------------------------------------------
//Descriptor Type in Standard Request Code                                                            
#define    DEVICE_DESCRIPTOR           0x01                                   /*!<Device Descriptor.*/
#define    CONFIGURATION_DESCRIPTOR    0x02                                   /*!<Configuration Descriptor.*/
#define    STRING_DESCRIPTOR           0x03                                   /*!<String Descriptor.*/
#define    INTERFACE_DESCRIPTOR        0x04                                   /*!<Interface Descriptor.*/
#define    ENDPOINT_DESCRIPTOR         0x05                                   /*!<Endpoint Descriptor.*/
#define    DEVICE_QUALIFIER_DESCRIPTOR 0x06                                   /*!<Device Qualifier Descriptor.*/
#define    BOS_DESCRIPTOR              0x0F                                   /*!<Binary Device Object Store(BOS) Descriptor.*/
#define    DEVICE_CAPABILTY_DESCRIPTOR 0x10                                   /*!<Device Capablity Descriptor.*/

//------------------------------------------------
//Descriptor Type in Class Request Code ( HID)
#define    HID_DESCRIPTOR              0x21                                   /*!< Class Descriptor : HID.*/
#define    HID_REPORT                  0x22                                   /*!< Class Descriptor : Report.*/
#define    HID_PHYSICAL_DESCRIPTOR     0x23                                   /*!< Class Descriptor : Physical descriptor.*/

//------------------------------------------------
//Direction of bEndpointAddress in Endpoint Descriptor.
#define USB_EP_OUT                              0x00                          /*!< OUT Endpoint.*/
#define USB_EP_IN                               0x80                          /*!< IN Endpoint.*/

//------------------------------------------------
//The endpoint number of bEndpointAddress in Endpoint Descriptor.
#define USB_EP_0                                0x00                          /*!< Endpoint number is 0.*/
#define USB_EP_1                                0x01                          /*!< Endpoint number is 1.*/
#define USB_EP_2                                0x02                          /*!< Endpoint number is 2.*/
#define USB_EP_3                                0x03                          /*!< Endpoint number is 3.*/
#define USB_EP_4                                0x04                          /*!< Endpoint number is 4.*/
#define USB_EP_5                                0x05                          /*!< Endpoint number is 5.*/
#define USB_EP_6                                0x06                          /*!< Endpoint number is 6.*/
#define USB_EP_7                                0x07                          /*!< Endpoint number is 7.*/
#define USB_EP_8                                0x08                          /*!< Endpoint number is 8.*/
#define USB_EP_9                                0x09                          /*!< Endpoint number is 9.*/
#define USB_EP_10                               0x0A                          /*!< Endpoint number is 10.*/
#define USB_EP_11                               0x0B                          /*!< Endpoint number is 11.*/
#define USB_EP_12                               0x0C                          /*!< Endpoint number is 12.*/
#define USB_EP_13                               0x0D                          /*!< Endpoint number is 13.*/
#define USB_EP_14                               0x0E                          /*!< Endpoint number is 14.*/
#define USB_EP_15                               0x0F                          /*!< Endpoint number is 15.*/

//------------------------------------------------
//Transfer Type of bmAttributes in Endpoint Descriptor.
#define USB_EP_CONTROL                          0x00                          /*!< Transfer Type is Control.*/
#define USB_EP_ISOCHRONOUS                      0x01                          /*!< Transfer Type is Isochronous.*/
#define USB_EP_BULK                             0x02                          /*!< Transfer Type is Bulk.*/
#define USB_EP_INTERRUPT                        0x03                          /*!< Transfer Type is Interrupt.*/

//------------------------------------------------
//Synchronization Type of bmAttributes in Endpoint Descriptor.
#define USB_EP_NO_SYNC                          0x00                          /*!< Synchronization Type is No Synchronization Type.*/              
#define USB_EP_ASYNC                            0x04                          /*!< Synchronization Type is Asynchronous.*/
#define USB_EP_ADAPTIVE                         0x08                          /*!< Synchronization Type is Adaptive.*/
#define USB_EP_SYNC                             0x0C                          /*!< Synchronization Type is Synchronous.*/

//------------------------------------------------
//Usage Type of bmAttributes in Endpoint Descriptor.
#define USB_EP_DATA                             0x00                          /*!< Usage Type is data endpoint. */
#define USB_EP_FEEDBACK                         0x10                          /*!< Usage Type is feedback endpoint.*/
#define USB_EP_IMPLICIT                         0x20                          /*!< Usage Type is implicit feedback data endpoint.*/
///@}    
    
    
/**
 * @name	========= USB Software Status Control Relationship==============
 *   		
 */ 
///@{     

 /*! @struct USBCTR_TypeDef
    @brief   USB software control and Endpoint0 relationship struct.
*/ 
typedef struct __attribute__((packed))
{
        uint32_t    USBStatus;                             /*!< USB software status.*/
        uint8_t     KeyIRQFlag;                            /*!< Key interrupt flag.*/
        uint8_t     DataStage;                             /*!< Index the next transaction are DATASTAGE or STATUSSTAGE.*/
        uint8_t     RxTx[EP0_PACKET_SIZE];                 /*!< For Rx/Tx FIFO.*/
  __I   uint8_t     *Buf;                                  /*!< USB Rx Buffer Address , Maybe addressing to ROM address.*/
        uint32_t    All;                                   /*!< Transmit All size in byte.*/
        uint8_t     Tmp;					               /*!< Store some data for Next transaction( SET_ADDRESS/SET_CONFIGURATION/..).*/
        uint8_t     ConfigurationValue;                    /*!< Host set configuration value.*/
#if MG_USB_LPM_EN == 1
        uint8_t     LPM_BLE;                               /*!< LPM BLE setting from Host.*/
#endif
}USBCTR_TypeDef;                                        

//------------------------------------------------
// USBStatus Control Relationship Define.
#define    USB_STATUS_DEFAULT                           0x00000000            /*!<USB software status default value.*/
#define    USB_STATUS_EMULATION_MASK                    0x80000000            /*!<Emulation status mask of USB software status .*/
    #define    USB_STATUS_EMULATION_OK                            0x80000000  /*!<Emulation status of USB software status is success.*/
    #define    USB_STATUS_EMULATION_NO                            0x00000000  /*!<Emulation status of USB software status is not yet successful.*/
#define    USB_STATUS_RWEN_MASK                         0x40000000            /*!<Remote wakeup function mask of USB software status.*/
    #define    USB_STATUS_RWEN_ENABLE                             0x40000000  /*!<Remote wakeup enable.*/
    #define    USB_STATUS_RWEN_DISABLE                            0x00000000  /*!<Remote wakeup disable.*/
#define    USB_STATUS_BUS_MASK                          0x00FF0000            /*!<USB Bus status mask of USB software status.*/
    #define    USB_STATUS_BUS_ACT                                 0x00000000  /*!<USB Bus Active.*/
    #define    USB_STATUS_BUS_RESET                               0x00010000  /*!<USB Bus Reset.*/
    #define    USB_STATUS_BUS_SUSPEND                             0x00020000  /*!<USB Bus Suspend.*/
    #define    USB_STATUS_BUS_RESUME                              0x00040000  /*!<USB Bus Resume.*/
    #define    USB_STATUS_BUS_EXTIEVENT_WAKEUP                    0x00080000  /*!<External signal wakeup device.*/
    #define    USB_STATUS_BUS_BUSEVENT_WAKEUP                     0x00100000  /*!<Bus event wakeup devic.*/

//------------------------------------------------
// DataStage Control Relationship Define.
#define    SETUPSTAGE          0xF0
#define    DATASTAGE           0x5A
#define    DATASTAGE_SRP       0x5B
#define    DATASTAGE_GRP       0x5C
#define    DATASTAGE_STRING0   0x5D
#define    DATASTAGE_STRING1   0x5E
#define    STATUSSTAGE         0xA5
#define    SETADDRESS          0x55      
   



extern USBCTR_TypeDef Ep0;    
    
    


void API_USBD_Inital(void);    
void API_USBD_IRQ( void );

void API_USBD_WriteEndpointData( USB_EP_Struct* EPX, uint8_t __I *Buffer , uint32_t TXShift , uint8_t Cnt );
void API_USBD_WriteEndpointConstData( USB_EP_Struct* EPX, uint8_t ConstData , uint32_t cTXShift , uint8_t cTXCnt );
void API_USBD_WriteEndpointSingleData( USB_EP_Struct* EPX, uint8_t sData , uint8_t shift);
void API_USBD_ReadEndpointData( USB_EP_Struct* EPX, uint8_t *Buffer , uint32_t RXShift , uint32_t Cnt);

                                                            
#if MF_STRING == 1                                          
#define MFS_LEN (sizeof(MANUFACTURER_DESCRIPTOR)*2)         /*!< Manufacture descriptor size.*/
#endif                                                      

#if PD_STRING == 1
#define PDS_LEN (sizeof(PRODUCT_DESCRIPTOR)*2)              /*!< Product descriptor size.*/
#endif

#if SN_STRING == 1                                          
#define SNS_LEN (sizeof(SERIALNUMBER_DESCRIPTOR)*2)         /*!< Serial number descriptor size.*/
#endif 





typedef struct  
{
    uint8_t             Status;              
    uint8_t             IdleRate;
    uint8_t             Protocol;
    uint8_t             padding;


    uint16_t  mHID0_ReportLength;                    /*!< HID0 report size */
    uint16_t  mHID1_ReportLength;                    /*!< HID0 report size */
    const uint8_t*  pUSB_INTERFACE0_HID_REPORT;           /*!< HID report of interface0.*/
    const uint8_t*  pUSB_INTERFACE1_HID_REPORT;           /*!< HID report of interface0.*/


    const uint8_t*  pUSB_DEVICE_DESCRIPTOR;               /*!< Device Descriptor.*/
    const uint8_t*  pUSB_CONFIGURATION_DESCRIPTOR;        /*!< Configuration Descriptor.*/
    const uint8_t*  pUSB_STRING_DESCRIPTOR;               /*!< String descriptor.*/

    #if MF_STRING == 1                                          
    const uint8_t*  pManufacturer_Descriptor;             /*!< Manufacture string descriptor.*/
    #endif      
    #if PD_STRING == 1                                          
    const uint8_t*  pProduct_Descriptor;                  /*!< Product string descriptor.*/
    #endif   
    #if SN_STRING == 1                                          
    const uint8_t*  pSerialNumber_Descriptor;             /*!< Serial number string descriptor.*/
    #endif 
    #if MG_USB_LPM_EN == 1                                      
    const uint8_t*  pUSB_BOS_DESCRIPTOR;                  /*!< BOS descriptor.*/
    const uint8_t*  pUSB_EXT_DESCRIPTOR;                  /*!< Device capabilty descriptor.*/
    #endif

}USBState_TypeDef;


extern USBState_TypeDef  g_UsbEP1Ctr;





void Usb_StateHandler(void);

///@}    
    
#ifdef __cplusplus
}
#endif

    
#endif   
