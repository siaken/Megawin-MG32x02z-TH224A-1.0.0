


 /**
 ******************************************************************************
 *
 * @file        USBD_DSC.c
 * @brief       The USBD Descriptor's c file.
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


#include "MG32x02z_USBD_API.h"
#include "MG32x02z_USBD_KeyDescriptor.h"
#include "MG32x02z_USB_Init.h"


#define KB_FUNHID_ID_FKB         1          /*!< HID Multimedia ID.*/
#define KB_FUNHID_ID_SYSTEM      2          /*!< HID System power control ID.*/

#define USB_CONFIGURATION_TOTAOL_INTERFACE  2                                                                                    /*!< Total interface in the configuration.*/

#define USB_CONFIGURATION_DESC_TOTAOSIZE   ((USB_CONFIGURATION_DESC_SIZE * 1) +  \
                                            (USB_INTERFACE_DESC_SIZE + USB_HID_DESC_SIZE + USB_ENDPOINT_DESC_SIZE * 1) +\
                                            (USB_INTERFACE_DESC_SIZE + USB_HID_DESC_SIZE + USB_ENDPOINT_DESC_SIZE * 1))          /*!< The configuration descriptor total size.*/
                                      

   

/**
 ***************************************************************************************************************
  * @fn       	HID REPORT 
  * @param    	
  * @return      
  * @details    	
 ***************************************************************************************************************
 */   
const uint8_t Key_USB_INTERFACE0_HID_REPORT[]=  
{  
    0x05,0x01,                         // Usage Page (Generic Desktop)
    0x09,0x06,                         // Usage (Keyboard)
    0xA1,0x01,                         // Collection (Application)
    0x05,0x07,                         //     Usage Page (Keyboard/Keypad Keys)
    
    //====================================================================
    //Modify : 1 byte
    0x15,0x00,                         //     Logical Minimum (0)
    0x25,0x01,                         //     Logical Maximum (1)    
    0x19,0xE0,                         //     Usage Minimum (224)
    0x29,0xE7,                         //     Usage Maximum (231)
    0x75,0x01,                         //     Report Size (1)
    0x95,0x08,                         //     Report Count (8)
    0x81,0x02,                         //     Input (Data, Variable, Absolute)
    
    //====================================================================
    // Reserved : 1 Byte //
    0x95,0x01,                         //     Report Count (1)
    0x75,0x08,                         //     Report Size (8)
    0x81,0x01,                         //     Input (Constant)
    
    //====================================================================
    //LED Status : 1 Byte (SETUP OUT)
    0x95,0x03,                         //     Report Count (3)
    0x75,0x01,                         //     Report Size (1)
    0x05,0x08,                         //     Usage Page (LED)
    0x19,0x01,                         //     Usage Minimum (1)
    0x29,0x03,                         //     Usage Maximum (3)
    0x91,0x02,                         //     Output (Data, Variable, Absolute)
                                              
    0x95,0x05,                         //     Report Count (5)
    0x75,0x01,                         //     Report Size (1)
    0x91,0x01,                         //     Output (Constant)
    
    //====================================================================
    // Normal Key : 6 Bytes 
    0x95,0x06,                         //     Report Count (6)
    0x75,0x08,                         //     Report Size (8)
    0x15,0x00,                         //     Logical Minimum (0)
    0x26,0xFF,0x00,                    //     Logical Maximum (255)
    0x05,0x07,                         //     Usage Page (Keyboard/Keypad Keys)
    0x19,0x00,                         //     Usage Minimum (0)
    0x2A,0xFF,0x00,                    //     Usage Maximum (255)
    0x81,0x00,                         //     Input (Data, Array, Absolute)
    
    0xC0                               // End Collection (Application)  
};


const uint8_t Key_USB_INTERFACE1_HID_REPORT[] = 
{
    //====================================================================
    //Multimedia
    0x05,0x0C,                         // usage page ( Consumer Devices )
    0x09,0x01,                         // usage ( Consumer Control )
    0xA1,0x01,                         // Collection ( Application )
 
    0x85,KB_FUNHID_ID_FKB,             //     Report ID (1)
    0x15,0x00,                         //     Logical_Minimum (0)
    0x25,0x01,                         //     Logical_Maximum 
    0x75,0x01,                         //     Report Size (1)    
    0x95,0x14,                         //     Report Count(20)
    //---------------------------------------------------------------------
    //Multimedia mapping table
    
    0x09,0xB6,                         //     USAGE(Previous Track )
                                       
    0x09,0xB5,                         //     USAGE( Next Track )
                                       
    0x09,0xB7,                         //     USAGE(Stop)
                                       
    0x09,0xCD,                         //     USAGE(Play/Pause)
                                       
    0x09,0xE9,                         //     USAGE(Volume Up)
                                       
    0x09,0xEA,                         //     USAGE(Volume Down)
                                       
    0x09,0xB3,                         //     USAGE(Fast Forward)
                                       
    0x09,0xB4,                         //     USAGE(Rewind)
                                       
    0x09,0xE2,                         //     USAGE(Mute)
                                       
    0x0A,0x94,0x01,                    //     USAGE(Call MyComputer)
                                       
    0x0A,0x92,0x01,                    //     USAGE(Call Caculator)
                                       
    0x0A,0x83,0x01,                    //     USAGE(Call Media Play )
                                       
    0x0A,0x23,0x02,                    //     USAGE(Call http://www.)
                                       
    0x0A,0x8A,0x01,                    //     USAGE(Call E-Mail)
                                       
    0x0A,0x2A,0x02,                    //     USAGE(Call MyFavorite)
                                       
    0x0A,0x21,0x02,                    //     USAGE(Call Search)
                                       
    0x0A,0x24,0x02,                    //     USAGE(Call Previous Page)
                                       
    0x0A,0x25,0x02,                    //     USAGE(Call Next Page)
                                       
    0x0A,0x26,0x02,                    //     USAGE(Call WebStop)
                                       
    0x0A,0x27,0x02,                    //     USAGE(Call WebRefresh)
    
    0x81,0x02,                         //     Input (Data , Var, Abs)
    
    0x75,0x01,                         //     Report Size (1)    
    0x95,0x04,                         //     Report Count(4)
    0x81,0x03,                         //     Input (Cnst,Var, Abs)
    
    0xC0,                              // End Collection
    //====================================================================
    //System power control
    0x05, 0x01,                        // Usage Page(Generic Desktop)
    0x09, 0x80,                        // Usage (System Conterol)
    0xA1, 0x01,                        // Collection (Application)
    0x85, KB_FUNHID_ID_SYSTEM,         //     Report ID (2)
    0x19, 0x81,                        //     Usage Minimum (0x81)
    0x29, 0x83,                        //     Usage Maximum (0x83)
    0x15, 0x00,                        //     Logical Minimum (Use Bit Map)
    0x25, 0x01,                        //     Logical Maximum (1)
    0x75, 0x01,                        //     Report Size (1 Bit)
    0x95, 0x03,                        //     Report Count(3)(Use Num Setting)
    0x81, 0x02,                        //     Input(Data , Varialbe, Absolute, No Wrap , Linear , Preferred State , No Null Position, Non Volatile, Bit Field) 
    0x95, 0x05,                        //     Report Count(5)(Const Num Setting)
    0x81, 0x01,                        //     Input(Constant , Array , Absolute , No Wrap, Linear , Preferred State , No Null Postion , Non Volatile, Bit Field)
    0xc0,                              // End Collection
};


#define    Key_HID0_HID_REPORT_LENGTH sizeof(Key_USB_INTERFACE0_HID_REPORT)       /*!< USB HID0 Descriptor data size.*/
#define    Key_HID1_HID_REPORT_LENGTH sizeof(Key_USB_INTERFACE1_HID_REPORT)       /*!< USB HID1 Descriptor data size.*/


const uint16_t Key_HID0_ReportLength = Key_HID0_HID_REPORT_LENGTH;
const uint16_t Key_HID1_ReportLength = Key_HID1_HID_REPORT_LENGTH;


/**
 *************************************************************************************************************
 * @fn       	DEVICE Descriptor  relationship 
 * @param    	No
 * @return      No
 * @details    	//-----------------USB 2.0------------------------------
				0: 		bLength 			Number		Size of this descriptor in bytes
				1: 		bDescriptorType		Constant	DEVICE Descriptor Type
				2,3: 	bcdUSB		    	BCD			USB specification release number in Binary-coded Decimal.
														This field identifies the release of the USB specification with
														which the device and its descriptors are compliant
				4:		bDeviceClass		Class		Class code:
														(1) If this field is reset to zero, each interface within a configuration 
															specifies its own class information and the various inerfaces operate
															independently
														(2) If this field is set to a value between 1 and 0xFE, the device supports 
															different class specifications on different interfaces and the 
															interfaces may not operate independently. This value identifies the 
															class definition used for the aggregate interfaces
														(3) If this field is set to 0xFF, the device class is vendor-specific
				5:      bDeviceSubClass 	Subclass	Subclass code
														(1) These codes are qualified by the value of the bDeviceClass field
														(2) If the bDeviceClass field is reset zero this field must alse be reset
															to zero.
														(3) If the bDeviceClass field is not set to 0xFF, all values are reserved 
															for assignment by the USB-IF.
				6:		bDeviceProtocol		Protocol    Protocol code
														(1) These codes are qualified by the value of the bDeviceSubClass fields.
															and the bDeviceSubClass field.
														(2) If a device supports class-specific protocols on a device basis  as 
															opposed to an interface basis, this code identifies the protocols 
															that the device uses as defined by the specification of the device class.
														(3) If this field is reset to zero, the device does not use class-specific 
															protocols on a device basis. However, it may use class-specific 
															protocols on an interface basis
														(4) If this field is set to 0xFF, the device uses a vendor-specific
															protocol on a device basis.
				7:		bMaxPacketSize0 	Number  	Maximum packet size for endpoint zero(only 8,16,32,or 64 are valid)
				8,9:    idVendor        	ID			VendorID(assigned by the USB-IF)
				10,11:  idProduct       	ID			Product ID(assigned by the manufacturer)
				12,13:  bcdDevice			BCD			Device release number in binary coded decimal
				14:     iManufacturer   	Index		Index of string descriptor describing manufacturer
				15:     iProduct        	Index 		Index of string descriptor describing product
				16:     iSerialNumber   	Index 		Index of string descriptor describing the device's serial number
				17:     bNumConfigurations	Number      Number of possible configurations
 **************************************************************************************************************
 */ 
const uint8_t Key_USB_DEVICE_DESCRIPTOR[]=
{ 
    0x12,                                        // 0:  bLength
    DEVICE_DESCRIPTOR,                           // 1:  bDescriptorType (0x01 = Device)
    LOBYTE( dcdUSB ),                            //     bcdUSB(LSB)
    HIBYTE( dcdUSB ),                            //     bcdUSB(MSB)
    bDeviceClass,                                // 4:  bDeviceClass
    bDeviceSubClass,                             // 5:  bDevice SubClass
    bDeviceProtocol,                             // 6:  bDeviceProtocol
    MG_USB_EP0_DSIZE,                            // 7:  bMaxPacketSize
    LOBYTE( USB_VID ),                           // 8:  idVendor(LSB)
    HIBYTE( USB_VID ),                           //     idVendor(MSB)
    LOBYTE( USB_PID ),                           // 10: idProduct(LSB)
    HIBYTE( USB_PID ),                           //     idProduct(MSB)
    LOBYTE( USB_DID ),                           // 12: bcdDevice(LSB)
    HIBYTE( USB_DID ),                           //     bcdDevice(MSB)
    
    MF_STRING_INDEX,                             // 14: iManufacture (String Index)
    
    PD_STRING_INDEX,                             // 15: iProduct     (String Index) 
    
    SN_STRING_INDEX,                             // 16: iSerialNumber(String Index)
    
    0x01                                         // 17: bNumConfigurations
};

/**
 ***************************************************************************************************************
 * @fn       	Configuartion Descriptor  relationship 
 * @param    	
 * @return      
 * @details    	
 ***************************************************************************************************************
 */  
const uint8_t Key_USB_CONFIGURATION_DESCRIPTOR[] = 
{ 
    0x09,                                        // 0:  bLength
    CONFIGURATION_DESCRIPTOR,                    // 1:  bDescriptorType (0x02 = configuration )
    LOBYTE( USB_CONFIGURATION_DESC_TOTAOSIZE ),  // 2:  wTotalLength(LSB)(All Descriptor ,
    HIBYTE( USB_CONFIGURATION_DESC_TOTAOSIZE ),  // 3:  wTotalLength(MSB)(Exclude "String")
    USB_CONFIGURATION_TOTAOL_INTERFACE,          // 4:  bNumInterface
    0x01,                                        // 5:  bConfigurationValue
    0x00,                                        // 6:  iConfiguration (String Index)
    USB_bmAttributes,                            // 7:  bmAttributes (Bus power & Remote wakeup)
                                                 //     D7:      Reserved (Set to one)
                                                 //     D6:      Self Powered
                                                 //     D5:      Remote Wakeup
                                                 //     D4..0:   Reserved (Reset to 0)
    (USB_bMaxPower/2),                           // 8:  Power    
    
    
    //=================================================================================
    // Interface 0 Descriptor 
    0x09,                                        // 0:  bLength
    INTERFACE_DESCRIPTOR,                        // 1:  bDescriptorType
    0x00,                                        // 2:  bInterfaceNumber
    0x00,                                        // 3:  bAlternateSetting
    0x01,                                        // 4:  bNumEndpoints
    0x03,                                        // 5:  bInterfaceClass
    0x01,                                        // 6:  bInterfaceSubClass
    0x01,                                        // 7:  bInterfaceProtocol
    0x00,                                        // 8:  iInterface         (String Index)
    
        //=================================================================================
        // HID Descriptor
        0x09,                                        // 0:  bLength
        HID_DESCRIPTOR,                              // 1:  bDescriptorType (0x22 = HID)
        0x10,                                        // 2:  bcdHIDClassL
        0x01,                                        // 3:  bcdHIDClassH
        0x00,                                        // 4:  Hardware Target Country
        0x01,                                        // 5:  Number of HID class descriptor to follow
        0x22,                                        // 6:  Report descriptor type
        LOBYTE( Key_HID0_HID_REPORT_LENGTH ),            // 7:  Total length of Report descriptor L
        HIBYTE( Key_HID0_HID_REPORT_LENGTH ),            // 8:  Total length of Report descriptor H
        //=================================================================================
        // Endpoint Descriptro
        0x07,           				                     // 0:  bLength
        ENDPOINT_DESCRIPTOR,       		                     // 1:  bDescriptorType
        (USB_EP_IN | USB_EP_1),      	                     // 2:  bEndpointerAddress
                   					                         //      D7:     Direction(0:OUT, 1:IN)
                   					                         //      D6..4:  Reserved (reset to 0)
                    				                         //      D3..0:  Endpoint Number(0000-1111)
        (USB_EP_INTERRUPT | USB_EP_NO_SYNC | USB_EP_DATA),   // 3:  bmAttributes
                    				                         //      D7..2:  Reserved (reset to 0)
                    				                         //      D1..0:  Transfer Type(00:Control,01:Bulk,02:Iso,03:Int)
        LOBYTE(EP1_PACKET_SIZE),       				         // 4:  wPacketSize(LSB)
        HIBYTE(EP1_PACKET_SIZE),       				         //     wPacketSize(MSB)
        0x01,        				                         // 6:  bInterval (Unit 1ms)
                    				                         //      Isochronous Endpoint: 01
                    				                         //      Interrupt Endpoint: 01-ff  
    //=================================================================================
    // Interface 1 Descriptor                                                              
    0x09,                                        // 0:  bLength
    INTERFACE_DESCRIPTOR,                        // 1:  bDescriptorType ( 0x04 = Interface) 
    0x01,                                        // 2:  bInterfaceNumber
    0x00,                                        // 3:  bAlternateSetting
    0x01,                                        // 4:  bNumEndpoints
    0x03,                                        // 5:  bInterfaceClass
    0x00,                                        // 6:  bInterfaceSubClass
    0x00,                                        // 7:  bInterfaceProtocol
    0x00,                                        // 8:  iInterface         (String Index)                 
    
        //=================================================================================
        // HID Descriptor
        0x09,                                        // 0:  bLength
        HID_DESCRIPTOR,                              // 1:  bDescriptorType
        0x11,                                        // 2:  bcdHIDClassL
        0x01,                                        // 3:  bcdHIDClassH
        0x00,                                        // 4:  Hardware Target Country
        0x01,                                        // 5:  Number of HID class descriptor to follow
        0x22,                                        // 6:  Report descriptor type
        LOBYTE( Key_HID1_HID_REPORT_LENGTH ),            // 7:  Total length of Report descriptor L
        HIBYTE( Key_HID1_HID_REPORT_LENGTH ),            // 8:  Total length of Report descriptor H
        
        //=================================================================================
        // Endpoint Descriptor
        0x07,           				                     // 0:  bLength
        ENDPOINT_DESCRIPTOR,       		                     // 1:  bDescriptorType
        (USB_EP_IN | USB_EP_2),      	                     // 2:  bEndpointerAddress
                   					                         //      D7:     Direction(0:OUT, 1:IN)
                   					                         //      D6..4:  Reserved (reset to 0)
                    				                         //      D3..0:  Endpoint Number(0000-1111)
        (USB_EP_INTERRUPT | USB_EP_NO_SYNC | USB_EP_DATA),   // 3:  bmAttributes
                    				                         //      D7..2:  Reserved (reset to 0)
                    				                         //      D1..0:  Transfer Type(00:Control,01:Bulk,02:Iso,03:Int)
        LOBYTE(EP2_PACKET_SIZE),       				         // 4:  wPacketSize(LSB)
        HIBYTE(EP2_PACKET_SIZE),       				         //     wPacketSize(MSB)
        0x01,        				                         // 6:  bInterval (Unit 1ms)
                    				                         //      Isochronous Endpoint: 01
                    				                         //      Interrupt Endpoint: 01-ff 
};

/**
 ***************************************************************************************************************
 * @fn       	STRING Descriptor  relationship 
 * @param    	
 * @return      
 * @details    	//-----------------USB 2.0------------------------------
				0:		bLength				Number		Size of this descriptor in bytes
				1:		bDescriptorType		Constant	STRING Descriptor Type
				2:		wLANGID[0]          Number      LANGID code zero
				...
				N		wLANGID[N]          Number      LANGID code x
***************************************************************************************************************
 */ 
const uint8_t Key_USB_STRING_DESCRIPTOR[] = 
{
	0x04,										// 0: Computed byt subtraction two from the value of the first byte of the descriptor
	STRING_DESCRIPTOR,							// 1: Descriptor Type
	0x09,										// 2:
	0x04    
};


//-----MANUFACTURER(UNICODE) in String Descriptor-----//
#if MF_STRING == 1
const uint8_t Key_Manufacturer_Descriptor[] = 
{
    MANUFACTURER_DESCRIPTOR,
};
#endif

//-----PRODUCT(UNICODE) in String Descriptor-----//
#if PD_STRING == 1
const uint8_t Key_Product_Descriptor[] = 
{ 
    PRODUCT_DESCRIPTOR
};
#endif


//-----Serial Number in String Descriptor-----//
#if SN_STRING == 1
const uint8_t Key_SerialNumber_Descriptor[] = 
{ 
    SERIALNUMBER_DESCRIPTOR
};
#endif

/**
***************************************************************************************************************
 * @fn       	BOS Descriptor  relationship
 * @param    	
 * @return      
 * @details    	//-----------------USB 3.0------------------------------
				0:		bLength				Number		Size of this descriptor
				1:		bDescriptorType		Constant	Descriptor type: BOS.
				2.3:	wTotalLength        Number      Length of this descriptor and all of its sub descriptors.
				4:		bNumDeviceCaps      Number      The number of separate device capability descritpor in the
                                                        BOS.
 * @Note        Refer to Section 7.4.1 of the Gertified Wireless USB Specification.
***************************************************************************************************************
 */ 
#if MG_USB_LPM_EN == 1
const uint8_t Key_USB_BOS_DESCRIPTOR[]=
{
    0x05,                                        // 0:  bLength
    BOS_DESCRIPTOR,                              // 1:  bDescriptorType ( 0x0F = BOS) 
    0x0C,                                        // 2:  wTotalLength
    0x00,                                        //   
    0x01,                                        // 4:  bNumDeviceCaps
    
};
/**
***************************************************************************************************************
 * @fn       	USB Device Capabilities - USB2.0 Extension Descriptor. (LPM) 
 * @param    	
 * @return      
 * @details    	//-----------------USB 2.0------------------------------
				0:		bLength				Number		Size of this descriptor
				1:		bDescriptorType		Constant	Descriptor type: DEVICE CAPABLITY Type.
				2:	    bInterfaceNumber    Constant    Capability type : USB2.0 EXTENSION (02H)
                31:0:   bAlternateSetting	Bitmap      Bitmap encoding of supported device level features.
                                                        A Value of one in a bit location indicate a feature is 
                                                        supported ; a value of zero indicates it is no supported.
                                                        Encodings are:
                                                        
                                                        Bit      Encoding
                                                        ---      --------
                                                        0        Reserved .Must be set to zero.
                                                        1        LPM. A value of one in this bit location indicates
                                                                 that this device supports the Link Power Management
                                                                 protocol.
                                                        2        BSEL and Alternate HIRD Supported.
                                                        31:3     Reserved.
***************************************************************************************************************
 */ 
const uint8_t Key_USB_EXT_DESCRIPTOR[] = 
{
    0x07,
    DEVICE_CAPABILTY_DESCRIPTOR,                   
    0x02,
    0x06,
    0x00,
    0x00,
    0x00,
};
#endif



