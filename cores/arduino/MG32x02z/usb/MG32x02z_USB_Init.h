

/**
 ******************************************************************************
 *
 * @file        MG32x02Z_USB_Init.h
 * @brief       The USB Init's h file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.04
 * @date        2022/08/09
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

#ifndef _MG32X02Z_USB_INIT_H
#define _MG32X02Z_USB_INIT_H


// <<< Use Configuration Wizard in Context Menu >>>

//<h> Hardware Setting

    #define MG_USB_SRAM_ADR          0
    #define MG_USB_SRAM_TOTAL_SIZE   512
    
    #define MG_USB_EPRX_MSK          0x04
    #define MG_USB_EPRX_ISO_MSK      0x01
    #define MG_USB_EPTX_MSK          0x40
    #define MG_USB_EPTX_ISO_MSK      0x10
    #define MG_USB_DBUF_MSK          0x80
    
    #define MG_USB_MODE_MASK              (MG_USB_EPRX_ISO_MSK | MG_USB_EPTX_ISO_MSK)
    #define MG_USB_MODE_RX_TX_BKINT        0
    #define MG_USB_MODE_RX_ISO_TX_BKINT    MG_USB_EPRX_ISO_MSK
    #define MG_USB_MODE_RX_BKINT_TX_ISO    MG_USB_EPTX_ISO_MSK 
    #define MG_USB_MODE_RX_TX_ISO         (MG_USB_EPRX_ISO_MSK | MG_USB_EPTX_ISO_MSK)
     
    #define MG_USBEP_OPEN_MASK           (MG_USB_DBUF_MSK | MG_USB_EPTX_MSK | MG_USB_EPRX_MSK) 
    #define MG_USBEP_RX_OPEN              MG_USB_EPRX_MSK
    #define MG_USBEP_TX_OPEN              MG_USB_EPTX_MSK
    #define MG_USBEP_RX_TX_OPEN          (MG_USB_EPRX_MSK | MG_USB_EPTX_MSK)
    #define MG_USBEP_DB_RX_OPEN          (MG_USB_DBUF_MSK | MG_USB_EPRX_MSK)
    #define MG_USBEP_DB_TX_OPEN          (MG_USB_DBUF_MSK | MG_USB_EPTX_MSK)
    
    
    //================================================================================================================
    //Endpoint 0 
    //<o0> Endpoint 0 Data Size <1-64>
    //<i> The allowable maximum control transfer data payload sizes 
    //<i> for full-speed devices is 8, 16, 32, or 64 bytes.
    
    #define MG_USB_EP0_DSIZE         64
    
    #define MG_USB_EP0_STATUS        0x44
    #define MG_USB_EP0_SRAM_RXSIZE   MG_USB_EP0_DSIZE
    #define MG_USB_EP0_SRAM_TXSIZE   MG_USB_EP0_DSIZE
    #define MG_USB_EP0_SRAM_SIZE     ( MG_USB_EP0_SRAM_RXSIZE + MG_USB_EP0_SRAM_TXSIZE)
    
    //================================================================================================================
    //Endpoint 1
    //<e0> Endpoint 1 Enable
        //<o1> Endpoint Mode is <0x04=> OUT Interrupt / Bulk Normal buffer mode. 
        //                      <0x44=> OUT Interrupt / Bulk Normal buffer mode , IN Interrupt / Bulk Normal buffer mode.
        //                      <0x54=> OUT Interrupt / Bulk Normal buffer mode , IN Isochronous Normal buffer mode.
        //                      <0x84=> OUT Interrupt / Bulk Double buffer mode.    
        //                      <0x05=> OUT Isochronous Normal buffer mode.
        //                      <0x45=> OUT Isochronous Normal buffer mode and , Interrupt / Bulk Normal buffer mode.
        //                      <0x55=> OUT Isochronous Normal buffer mode and , Isochronous Normal buffer mode.
        //                      <0x85=> OUT Isochronous Double buffer mode.
        //                      <0x40=> IN Interrupt / Bulk Normal buffer mode.
        //                      <0x50=> IN Isochronous Normal buffer mode.    
        //                      <0xC0=> IN Interrupt / Bulk Double buffer mode.
        //                      <0xD0=> IN Isochronous Double buffer mode.
        //<o2> Endpoint Address is ( 1 - 15) <1-15> 
        //<o3> Endpoint Data RX size ( 0-512 ) <0-512>
        //<o4> Endpoint Data TX size ( 0-512 ) <0-512>
    //</e>
    #define MG_USB_EP1_EN         1
    #define MG_USB_EP1_MDS        0x40
    #define MG_USB_EP1_ADDRESS    1
    #define MG_USB_EP1RX_DSIZE    0
    #define MG_USB_EP1TX_DSIZE    8
    
    #if MG_USB_EP1_EN == 0
        #define MG_USB_EP1_STATUS        0
        #define MG_USB_EP1_SRAM_RXSIZE   0
        #define MG_USB_EP1_SRAM_TXSIZE   0
        #define MG_USB_EP1_TXADDRESS     0
        #define MG_USB_EP1_RXADDRESS     0
    #else
        #define MG_USB_EP1_STATUS        MG_USB_EP1_MDS
        #if (( MG_USB_EP1_MDS & MG_USB_DBUF_MSK) == 0)
            #if ((MG_USB_EP1_MDS & MG_USB_EPRX_MSK) == MG_USB_EPRX_MSK)
                #define MG_USB_EP1_SRAM_RXSIZE    MG_USB_EP1RX_DSIZE
                #define MG_USB_EP1_RXADDRESS      (0x0001 << MG_USB_EP1_ADDRESS)
            #else
                #define MG_USB_EP1_SRAM_RXSIZE    0 
                #define MG_USB_EP1_RXADDRESS      0
            #endif
            #if ((MG_USB_EP1_MDS & MG_USB_EPTX_MSK) == MG_USB_EPTX_MSK)
                #define MG_USB_EP1_SRAM_TXSIZE    MG_USB_EP1TX_DSIZE
                #define MG_USB_EP1_TXADDRESS      (0x0001 << MG_USB_EP1_ADDRESS)
            #else
                #define MG_USB_EP1_SRAM_TXSIZE    0
                #define MG_USB_EP1_TXADDRESS      0
            #endif
        #else
            #if ((MG_USB_EP1_MDS & MG_USB_EPRX_MSK) == MG_USB_EPRX_MSK)
                #define MG_USB_EP1_SRAM_RXSIZE    MG_USB_EP1RX_DSIZE
                #define MG_USB_EP1_SRAM_TXSIZE    MG_USB_EP1RX_DSIZE
                #define MG_USB_EP1_RXADDRESS      (0x0001 << MG_USB_EP1_ADDRESS)
                #define MG_USB_EP1_TXADDRESS      0
            #else
                #define MG_USB_EP1_SRAM_RXSIZE    MG_USB_EP1TX_DSIZE
                #define MG_USB_EP1_SRAM_TXSIZE    MG_USB_EP1TX_DSIZE
                #define MG_USB_EP1_RXADDRESS      0
                #define MG_USB_EP1_TXADDRESS      (0x0001 << MG_USB_EP1_ADDRESS)
            #endif
        #endif
    #endif
    
    #define MG_USB_EP1_SRAM_SIZE     ( MG_USB_EP1_SRAM_RXSIZE + MG_USB_EP1_SRAM_TXSIZE)
    
    //================================================================================================================
    //Endpoint 2
    //<e0> Endpoint 2 Enable
        //<o1> Endpoint Mode is <0x04=> OUT Interrupt / Bulk Normal buffer mode. 
        //                      <0x44=> OUT Interrupt / Bulk Normal buffer mode , IN Interrupt / Bulk Normal buffer mode.
        //                      <0x54=> OUT Interrupt / Bulk Normal buffer mode , IN Isochronous Normal buffer mode.
        //                      <0x84=> OUT Interrupt / Bulk Double buffer mode.    
        //                      <0x05=> OUT Isochronous Normal buffer mode.
        //                      <0x45=> OUT Isochronous Normal buffer mode and , IN Interrupt / Bulk Normal buffer mode.
        //                      <0x55=> OUT Isochronous Normal buffer mode and , IN Isochronous Normal buffer mode.
        //                      <0x85=> OUT Isochronous Double buffer mode.
        //                      <0x40=> IN Interrupt / Bulk Normal buffer mode.
        //                      <0x50=> IN Isochronous Normal buffer mode.    
        //                      <0xC0=> IN Interrupt / Bulk Double buffer mode.
        //                      <0xD0=> IN Isochronous Double buffer mode.
        //<o2> Endpoint Address is ( 1 - 15) <1-15> 
        //<o3> Endpoint Data RX size ( 0-512 ) <0-512>
        //<o4> Endpoint Data TX size ( 0-512 ) <0-512>
    //</e>
    #define MG_USB_EP2_EN         0
    #define MG_USB_EP2_MDS        0x40
    #define MG_USB_EP2_ADDRESS    2
    #define MG_USB_EP2RX_DSIZE    0
    #define MG_USB_EP2TX_DSIZE    8
    
    #if MG_USB_EP2_EN == 0
        #define MG_USB_EP2_STATUS        0
        #define MG_USB_EP2_SRAM_RXSIZE   0
        #define MG_USB_EP2_SRAM_TXSIZE   0
        #define MG_USB_EP2_TXADDRESS     0
        #define MG_USB_EP2_RXADDRESS     0
    #else
        #define MG_USB_EP2_STATUS        MG_USB_EP2_MDS
        #if (( MG_USB_EP2_MDS & MG_USB_DBUF_MSK) == 0)
            #if ((MG_USB_EP2_MDS & MG_USB_EPRX_MSK) == MG_USB_EPRX_MSK)
                #define MG_USB_EP2_SRAM_RXSIZE    MG_USB_EP2RX_DSIZE
                #define MG_USB_EP2_RXADDRESS      (0x0001 << MG_USB_EP2_ADDRESS)
            #else
                #define MG_USB_EP2_SRAM_RXSIZE    0 
                #define MG_USB_EP2_RXADDRESS      0
            #endif
            #if ((MG_USB_EP2_MDS & MG_USB_EPTX_MSK) == MG_USB_EPTX_MSK)
                #define MG_USB_EP2_SRAM_TXSIZE    MG_USB_EP2TX_DSIZE
                #define MG_USB_EP2_TXADDRESS      (0x0001 << MG_USB_EP2_ADDRESS)
            #else
                #define MG_USB_EP2_SRAM_TXSIZE    0
                #define MG_USB_EP2_TXADDRESS      0
            #endif
        #else
            #if ((MG_USB_EP2_MDS & MG_USB_EPRX_MSK) == MG_USB_EPRX_MSK)
                #define MG_USB_EP2_SRAM_RXSIZE    MG_USB_EP2RX_DSIZE
                #define MG_USB_EP2_SRAM_TXSIZE    MG_USB_EP2RX_DSIZE
                #define MG_USB_EP2_RXADDRESS      (0x0001 << MG_USB_EP2_ADDRESS)
                #define MG_USB_EP2_TXADDRESS      0
            #else
                #define MG_USB_EP2_SRAM_RXSIZE    MG_USB_EP2TX_DSIZE
                #define MG_USB_EP2_SRAM_TXSIZE    MG_USB_EP2TX_DSIZE
                #define MG_USB_EP2_RXADDRESS      0
                #define MG_USB_EP2_TXADDRESS      (0x0001 << MG_USB_EP2_ADDRESS)
            #endif
        #endif
    #endif
    
    #define MG_USB_EP2_SRAM_SIZE     ( MG_USB_EP2_SRAM_RXSIZE + MG_USB_EP2_SRAM_TXSIZE)
    
    
    //================================================================================================================
    //Endpoint 3
    //<e0> Endpoint 3 Enable
        //<o1> Endpoint Mode is <0x04=> OUT Interrupt / Bulk Normal buffer mode. 
        //                      <0x44=> OUT Interrupt / Bulk Normal buffer mode , IN Interrupt / Bulk Normal buffer mode.
        //                      <0x54=> OUT Interrupt / Bulk Normal buffer mode , IN Isochronous Normal buffer mode.
        //                      <0x84=> OUT Interrupt / Bulk Double buffer mode.    
        //                      <0x05=> OUT Isochronous Normal buffer mode.
        //                      <0x45=> OUT Isochronous Normal buffer mode and , IN Interrupt / Bulk Normal buffer mode.
        //                      <0x55=> OUT Isochronous Normal buffer mode and , IN Isochronous Normal buffer mode.
        //                      <0x85=> OUT Isochronous Double buffer mode.
        //                      <0x40=> IN Interrupt / Bulk Normal buffer mode.
        //                      <0x50=> IN Isochronous Normal buffer mode.    
        //                      <0xC0=> IN Interrupt / Bulk Double buffer mode.
        //                      <0xD0=> IN Isochronous Double buffer mode.
        //<o2> Endpoint Address is ( 1 - 15) <1-15> 
        //<o3> Endpoint Data RX size ( 0-512 ) <0-512>
        //<o4> Endpoint Data TX size ( 0-512 ) <0-512>
    //</e>
    #define MG_USB_EP3_EN         0
    #define MG_USB_EP3_MDS        0x04
    #define MG_USB_EP3_ADDRESS    3
    #define MG_USB_EP3RX_DSIZE    0
    #define MG_USB_EP3TX_DSIZE    0
    
    #if MG_USB_EP3_EN == 0
        #define MG_USB_EP3_STATUS        0
        #define MG_USB_EP3_SRAM_RXSIZE   0
        #define MG_USB_EP3_SRAM_TXSIZE   0
        #define MG_USB_EP3_TXADDRESS     0
        #define MG_USB_EP3_RXADDRESS     0
    #else
        #define MG_USB_EP3_STATUS        MG_USB_EP3_MDS
    
        #if (( MG_USB_EP3_MDS & MG_USB_DBUF_MSK) == 0)
            #if ((MG_USB_EP3_MDS & MG_USB_EPRX_MSK) == MG_USB_EPRX_MSK)
                #define MG_USB_EP3_SRAM_RXSIZE    MG_USB_EP3RX_DSIZE
                #define MG_USB_EP3_RXADDRESS      (0x0001 << MG_USB_EP3_ADDRESS)
            #else
                #define MG_USB_EP3_SRAM_RXSIZE    0 
                #define MG_USB_EP3_RXADDRESS      0
            #endif
            #if ((MG_USB_EP3_MDS & MG_USB_EPTX_MSK) == MG_USB_EPTX_MSK)
                #define MG_USB_EP3_SRAM_TXSIZE    MG_USB_EP3TX_DSIZE
                #define MG_USB_EP3_TXADDRESS      (0x0001 << MG_USB_EP3_ADDRESS)
            #else
                #define MG_USB_EP3_SRAM_TXSIZE    0
                #define MG_USB_EP3_TXADDRESS      0
            #endif
        #else
            #if ((MG_USB_EP3_MDS & MG_USB_EPRX_MSK) == MG_USB_EPRX_MSK)
                #define MG_USB_EP3_SRAM_RXSIZE    MG_USB_EP3RX_DSIZE
                #define MG_USB_EP3_SRAM_TXSIZE    MG_USB_EP3RX_DSIZE
                #define MG_USB_EP3_RXADDRESS      (0x0001 << MG_USB_EP3_ADDRESS)
                #define MG_USB_EP3_TXADDRESS      0
            #else
                #define MG_USB_EP3_SRAM_RXSIZE    MG_USB_EP3TX_DSIZE
                #define MG_USB_EP3_SRAM_TXSIZE    MG_USB_EP3TX_DSIZE
                #define MG_USB_EP3_RXADDRESS      0
                #define MG_USB_EP3_TXADDRESS      (0x0001 << MG_USB_EP3_ADDRESS)
            #endif
        #endif
    #endif
    
    #define MG_USB_EP3_SRAM_SIZE     ( MG_USB_EP3_SRAM_RXSIZE + MG_USB_EP3_SRAM_TXSIZE)
    
    //================================================================================================================
    //Endpoint 4
    //<e0> Endpoint 4 Enable
        //<o1> Endpoint Mode is <0x04=> OUT Interrupt / Bulk Normal buffer mode. 
        //                      <0x44=> OUT Interrupt / Bulk Normal buffer mode , IN Interrupt / Bulk Normal buffer mode.
        //                      <0x54=> OUT Interrupt / Bulk Normal buffer mode , IN Isochronous Normal buffer mode.
        //                      <0x84=> OUT Interrupt / Bulk Double buffer mode.    
        //                      <0x05=> OUT Isochronous Normal buffer mode.
        //                      <0x45=> OUT Isochronous Normal buffer mode and , IN Interrupt / Bulk Normal buffer mode.
        //                      <0x55=> OUT Isochronous Normal buffer mode and , IN Isochronous Normal buffer mode.
        //                      <0x85=> OUT Isochronous Double buffer mode.
        //                      <0x40=> IN Interrupt / Bulk Normal buffer mode.
        //                      <0x50=> IN Isochronous Normal buffer mode.    
        //                      <0xC0=> IN Interrupt / Bulk Double buffer mode.
        //                      <0xD0=> IN Isochronous Double buffer mode.
        //<o2> Endpoint Address is ( 1 - 15) <1-15> 
        //<o3> Endpoint Data RX size ( 0-512 ) <0-512>
        //<o4> Endpoint Data TX size ( 0-512 ) <0-512>
    //</e>
    #define MG_USB_EP4_EN         0
    #define MG_USB_EP4_MDS        0x04
    #define MG_USB_EP4_ADDRESS    4
    #define MG_USB_EP4RX_DSIZE    0
    #define MG_USB_EP4TX_DSIZE    0
    
    #if MG_USB_EP4_EN == 0
        #define MG_USB_EP4_STATUS        0    
        #define MG_USB_EP4_SRAM_RXSIZE   0
        #define MG_USB_EP4_SRAM_TXSIZE   0
        #define MG_USB_EP4_TXADDRESS     0
        #define MG_USB_EP4_RXADDRESS     0
    #else
        #define MG_USB_EP4_STATUS        MG_USB_EP4_MDS
    
        #if (( MG_USB_EP4_MDS & MG_USB_DBUF_MSK) == 0)
            #if ((MG_USB_EP4_MDS & MG_USB_EPRX_MSK) == MG_USB_EPRX_MSK)
                #define MG_USB_EP4_SRAM_RXSIZE    MG_USB_EP4RX_DSIZE
                #define MG_USB_EP4_RXADDRESS      (0x0001 << MG_USB_EP4_ADDRESS)
            #else
                #define MG_USB_EP4_SRAM_RXSIZE    0 
                #define MG_USB_EP4_RXADDRESS      0
            #endif
            #if ((MG_USB_EP4_MDS & MG_USB_EPTX_MSK) == MG_USB_EPTX_MSK)
                #define MG_USB_EP4_SRAM_TXSIZE    MG_USB_EP4TX_DSIZE
                #define MG_USB_EP4_TXADDRESS      (0x0001 << MG_USB_EP4_ADDRESS)
            #else
                #define MG_USB_EP4_SRAM_TXSIZE    0
                #define MG_USB_EP4_TXADDRESS      0
            #endif
        #else
            #if ((MG_USB_EP4_MDS & MG_USB_EPRX_MSK) == MG_USB_EPRX_MSK)
                #define MG_USB_EP4_SRAM_RXSIZE    MG_USB_EP4RX_DSIZE
                #define MG_USB_EP4_SRAM_TXSIZE    MG_USB_EP4RX_DSIZE
                #define MG_USB_EP4_RXADDRESS      (0x0001 << MG_USB_EP4_ADDRESS)
                #define MG_USB_EP4_TXADDRESS      0
            #else
                #define MG_USB_EP4_SRAM_RXSIZE    MG_USB_EP4TX_DSIZE
                #define MG_USB_EP4_SRAM_TXSIZE    MG_USB_EP4TX_DSIZE
                #define MG_USB_EP4_RXADDRESS      0
                #define MG_USB_EP4_TXADDRESS      (0x0001 << MG_USB_EP4_ADDRESS)
            #endif
        #endif
    #endif
    
    #define MG_USB_EP4_SRAM_SIZE     ( MG_USB_EP4_SRAM_RXSIZE + MG_USB_EP4_SRAM_TXSIZE)
    
    //================================================================================================================
    //Endpoint 5
    //<e0> Endpoint 5 Enable
        //<o1> Endpoint Mode is <0x04=> OUT Interrupt / Bulk Normal buffer mode. 
        //                      <0x44=> OUT Interrupt / Bulk Normal buffer mode , IN Interrupt / Bulk Normal buffer mode.
        //                      <0x54=> OUT Interrupt / Bulk Normal buffer mode , IN Isochronous Normal buffer mode.
        //                      <0x84=> OUT Interrupt / Bulk Double buffer mode.    
        //                      <0x05=> OUT Isochronous Normal buffer mode.
        //                      <0x45=> OUT Isochronous Normal buffer mode and , IN Interrupt / Bulk Normal buffer mode.
        //                      <0x55=> OUT Isochronous Normal buffer mode and , IN Isochronous Normal buffer mode.
        //                      <0x85=> OUT Isochronous Double buffer mode.
        //                      <0x40=> IN Interrupt / Bulk Normal buffer mode.
        //                      <0x50=> IN Isochronous Normal buffer mode.    
        //                      <0xC0=> IN Interrupt / Bulk Double buffer mode.
        //                      <0xD0=> IN Isochronous Double buffer mode.
        //<o2> Endpoint Address is ( 1 - 15) <1-15> 
        //<o3> Endpoint Data RX size ( 0-512 ) <0-512>
        //<o4> Endpoint Data TX size ( 0-512 ) <0-512>
    //</e>
    #define MG_USB_EP5_EN         0
    #define MG_USB_EP5_MDS        0x04
    #define MG_USB_EP5_ADDRESS    5
    #define MG_USB_EP5RX_DSIZE    0
    #define MG_USB_EP5TX_DSIZE    0
    
    #if MG_USB_EP5_EN == 0
        #define MG_USB_EP5_STATUS        0
        #define MG_USB_EP5_SRAM_RXSIZE   0
        #define MG_USB_EP5_SRAM_TXSIZE   0
        #define MG_USB_EP5_TXADDRESS     0
        #define MG_USB_EP5_RXADDRESS     0
    #else
        #define MG_USB_EP5_STATUS        MG_USB_EP5_MDS
    
        #if (( MG_USB_EP5_MDS & MG_USB_DBUF_MSK) == 0)
            #if ((MG_USB_EP5_MDS & MG_USB_EPRX_MSK) == MG_USB_EPRX_MSK)
                #define MG_USB_EP5_SRAM_RXSIZE    MG_USB_EP5RX_DSIZE
                #define MG_USB_EP5_RXADDRESS      (0x0001 << MG_USB_EP5_ADDRESS)
            #else
                #define MG_USB_EP5_SRAM_RXSIZE    0 
                #define MG_USB_EP5_RXADDRESS      0
            #endif
            #if ((MG_USB_EP5_MDS & MG_USB_EPTX_MSK) == MG_USB_EPTX_MSK)
                #define MG_USB_EP5_SRAM_TXSIZE    MG_USB_EP5TX_DSIZE
                #define MG_USB_EP5_TXADDRESS      (0x0001 << MG_USB_EP5_ADDRESS)
            #else
                #define MG_USB_EP5_SRAM_TXSIZE    0
                #define MG_USB_EP5_TXADDRESS      0
            #endif
        #else
            #if ((MG_USB_EP5_MDS & MG_USB_EPRX_MSK) == MG_USB_EPRX_MSK)
                #define MG_USB_EP5_SRAM_RXSIZE    MG_USB_EP5RX_DSIZE
                #define MG_USB_EP5_SRAM_TXSIZE    MG_USB_EP5RX_DSIZE
                #define MG_USB_EP5_RXADDRESS      (0x0001 << MG_USB_EP5_ADDRESS)
                #define MG_USB_EP5_TXADDRESS      0
            #else
                #define MG_USB_EP5_SRAM_RXSIZE    MG_USB_EP5TX_DSIZE
                #define MG_USB_EP5_SRAM_TXSIZE    MG_USB_EP5TX_DSIZE
                #define MG_USB_EP5_RXADDRESS      0
                #define MG_USB_EP5_TXADDRESS      (0x0001 << MG_USB_EP5_ADDRESS)
            #endif
        #endif
    #endif
    
    #define MG_USB_EP5_SRAM_SIZE     ( MG_USB_EP5_SRAM_RXSIZE + MG_USB_EP5_SRAM_TXSIZE)
    
    //================================================================================================================
    //Endpoint 6
    //<e0> Endpoint 6 Enable
        //<o1> Endpoint Mode is <0x04=> OUT Interrupt / Bulk Normal buffer mode. 
        //                      <0x44=> OUT Interrupt / Bulk Normal buffer mode , IN Interrupt / Bulk Normal buffer mode.
        //                      <0x54=> OUT Interrupt / Bulk Normal buffer mode , IN Isochronous Normal buffer mode.
        //                      <0x84=> OUT Interrupt / Bulk Double buffer mode.    
        //                      <0x05=> OUT Isochronous Normal buffer mode.
        //                      <0x45=> OUT Isochronous Normal buffer mode and , IN Interrupt / Bulk Normal buffer mode.
        //                      <0x55=> OUT Isochronous Normal buffer mode and , IN Isochronous Normal buffer mode.
        //                      <0x85=> OUT Isochronous Double buffer mode.
        //                      <0x40=> IN Interrupt / Bulk Normal buffer mode.
        //                      <0x50=> IN Isochronous Normal buffer mode.    
        //                      <0xC0=> IN Interrupt / Bulk Double buffer mode.
        //                      <0xD0=> IN Isochronous Double buffer mode.
        //<o2> Endpoint Address is ( 1 - 15) <1-15> 
        //<o3> Endpoint Data RX size ( 0-512 ) <0-512>
        //<o4> Endpoint Data TX size ( 0-512 ) <0-512>
    //</e>
    #define MG_USB_EP6_EN         0
    #define MG_USB_EP6_MDS        0x04
    #define MG_USB_EP6_ADDRESS    6
    #define MG_USB_EP6RX_DSIZE    0
    #define MG_USB_EP6TX_DSIZE    0
    
    #if MG_USB_EP6_EN == 0
        #define MG_USB_EP6_STATUS        0
        #define MG_USB_EP6_SRAM_RXSIZE   0
        #define MG_USB_EP6_SRAM_TXSIZE   0
        #define MG_USB_EP6_TXADDRESS     0
        #define MG_USB_EP6_RXADDRESS     0
    #else
        #define MG_USB_EP6_STATUS        MG_USB_EP6_MDS
        
        #if (( MG_USB_EP6_MDS & MG_USB_DBUF_MSK) == 0)
            #if ((MG_USB_EP6_MDS & MG_USB_EPRX_MSK) == MG_USB_EPRX_MSK)
                #define MG_USB_EP6_SRAM_RXSIZE    MG_USB_EP6RX_DSIZE
                #define MG_USB_EP6_RXADDRESS      (0x0001 << MG_USB_EP6_ADDRESS)
            #else
                #define MG_USB_EP6_SRAM_RXSIZE    0 
                #define MG_USB_EP6_RXADDRESS      0
            #endif
            #if ((MG_USB_EP6_MDS & MG_USB_EPTX_MSK) == MG_USB_EPTX_MSK)
                #define MG_USB_EP6_SRAM_TXSIZE    MG_USB_EP6TX_DSIZE
                #define MG_USB_EP6_TXADDRESS      (0x0001 << MG_USB_EP6_ADDRESS)
            #else
                #define MG_USB_EP6_SRAM_TXSIZE    0
                #define MG_USB_EP6_TXADDRESS      0
            #endif
        #else
            #if ((MG_USB_EP6_MDS & MG_USB_EPRX_MSK) == MG_USB_EPRX_MSK)
                #define MG_USB_EP6_SRAM_RXSIZE    MG_USB_EP6RX_DSIZE
                #define MG_USB_EP6_SRAM_TXSIZE    MG_USB_EP6RX_DSIZE
                #define MG_USB_EP6_RXADDRESS      (0x0001 << MG_USB_EP6_ADDRESS)
                #define MG_USB_EP6_TXADDRESS      0
            #else
                #define MG_USB_EP6_SRAM_RXSIZE    MG_USB_EP6TX_DSIZE
                #define MG_USB_EP6_SRAM_TXSIZE    MG_USB_EP6TX_DSIZE
                #define MG_USB_EP6_RXADDRESS      0
                #define MG_USB_EP6_TXADDRESS      (0x0001 << MG_USB_EP6_ADDRESS)
            #endif
        #endif
    #endif
    
    #define MG_USB_EP6_SRAM_SIZE     ( MG_USB_EP6_SRAM_RXSIZE + MG_USB_EP6_SRAM_TXSIZE)
    
    //================================================================================================================
    //Endpoint 7
    //<e0> Endpoint 7 Enable
        //<o1> Endpoint Mode is <0x04=> OUT Interrupt / Bulk Normal buffer mode. 
        //                      <0x44=> OUT Interrupt / Bulk Normal buffer mode , IN Interrupt / Bulk Normal buffer mode.
        //                      <0x54=> OUT Interrupt / Bulk Normal buffer mode , IN Isochronous Normal buffer mode.
        //                      <0x84=> OUT Interrupt / Bulk Double buffer mode.    
        //                      <0x05=> OUT Isochronous Normal buffer mode.
        //                      <0x45=> OUT Isochronous Normal buffer mode and , IN Interrupt / Bulk Normal buffer mode.
        //                      <0x55=> OUT Isochronous Normal buffer mode and , IN Isochronous Normal buffer mode.
        //                      <0x85=> OUT Isochronous Double buffer mode.
        //                      <0x40=> IN Interrupt / Bulk Normal buffer mode.
        //                      <0x50=> IN Isochronous Normal buffer mode.    
        //                      <0xC0=> IN Interrupt / Bulk Double buffer mode.
        //                      <0xD0=> IN Isochronous Double buffer mode.
        //<o2> Endpoint Address is ( 1 - 15) <1-15> 
        //<o3> Endpoint Data RX size ( 0-512 ) <0-512>
        //<o4> Endpoint Data TX size ( 0-512 ) <0-512>
    //</e>
    #define MG_USB_EP7_EN         0
    #define MG_USB_EP7_MDS        0x04
    #define MG_USB_EP7_ADDRESS    7
    #define MG_USB_EP7RX_DSIZE    0
    #define MG_USB_EP7TX_DSIZE    0
    
    #if MG_USB_EP7_EN == 0
        #define MG_USB_EP7_STATUS        0
        #define MG_USB_EP7_SRAM_RXSIZE   0
        #define MG_USB_EP7_SRAM_TXSIZE   0
        #define MG_USB_EP7_TXADDRESS     0
        #define MG_USB_EP7_RXADDRESS     0
    #else
        #define MG_USB_EP7_STATUS        MG_USB_EP7_MDS
    
        #if (( MG_USB_EP7_MDS & MG_USB_DBUF_MSK) == 0)
            #if ((MG_USB_EP7_MDS & MG_USB_EPRX_MSK) == MG_USB_EPRX_MSK)
                #define MG_USB_EP7_SRAM_RXSIZE    MG_USB_EP7RX_DSIZE
                #define MG_USB_EP7_RXADDRESS      (0x0001 << MG_USB_EP7_ADDRESS)
            #else
                #define MG_USB_EP7_SRAM_RXSIZE    0 
                #define MG_USB_EP7_RXADDRESS      0
            #endif
            #if ((MG_USB_EP7_MDS & MG_USB_EPTX_MSK) == MG_USB_EPTX_MSK)
                #define MG_USB_EP7_SRAM_TXSIZE    MG_USB_EP7TX_DSIZE
                #define MG_USB_EP7_TXADDRESS      (0x0001 << MG_USB_EP7_ADDRESS)
            #else
                #define MG_USB_EP7_SRAM_TXSIZE    0
                #define MG_USB_EP7_TXADDRESS      0
            #endif
        #else
            #if ((MG_USB_EP7_MDS & MG_USB_EPRX_MSK) == MG_USB_EPRX_MSK)
                #define MG_USB_EP7_SRAM_RXSIZE    MG_USB_EP7RX_DSIZE
                #define MG_USB_EP7_SRAM_TXSIZE    MG_USB_EP7RX_DSIZE
                #define MG_USB_EP7_RXADDRESS      (0x0001 << MG_USB_EP7_ADDRESS)
                #define MG_USB_EP7_TXADDRESS      0
            #else
                #define MG_USB_EP7_SRAM_RXSIZE    MG_USB_EP7TX_DSIZE
                #define MG_USB_EP7_SRAM_TXSIZE    MG_USB_EP7TX_DSIZE
                #define MG_USB_EP7_RXADDRESS      0
                #define MG_USB_EP7_TXADDRESS      (0x0001 << MG_USB_EP7_ADDRESS)
            #endif
        #endif
    #endif
    
    #define MG_USB_EP7_SRAM_SIZE     ( MG_USB_EP7_SRAM_RXSIZE + MG_USB_EP7_SRAM_TXSIZE)
    
    //================================================================================================================
    //The other function.
    //<q0> Enable LPM
    #define MG_USB_LPM_EN   0
    
//</h>

//<h> USB Descriptor
    //<h> Device Descriptor
        //<o0> USB specification release number<0x0000-0xFFFF>
        //<i> 0x0110 = USB 1.1
        //<i> 0x0200 = USB 2.0
        //<i> 0x0210 = USB 2.1
        #define dcdUSB                       0x0110
        //<o0> Device Class <0x00=> Use class code info from Interface Descriptors
				//                  <0x02=> Communications and CDC Control
				//                  
				#define bDeviceClass                 0x00
				//<o0> Subclass  <0x00-0xFF>
				#define bDeviceSubClass              0x00
				//<o0> Protocol  <0x00-0xFF>
				#define bDeviceProtocol              0x00
        
        //<o0> Vendor ID   (0x0000 ~ 0xFFFF) < 0x0000-0xFFFF>
        //#define USB_VID                      0x0E6A
        //<o0> Product ID (0x0000 ~ 0xFFFF) < 0x0000-0xFFFF>
        //#define USB_PID                      0x032F
        //<o0> Device release number (0x0000 ~ 0xFFFF) <0x0000-0xFFFF>
        #define USB_DID                      0x0100
        
        //<e0> Enable string descriptor describing manufacturer.
        #define MF_STRING                    1
        #define MF_STRING_INDEX              ( MF_STRING * MF_STRING)
            //<s> Manufacturer string descriptor.
            #define MANUFACTURER_DESCRIPTOR  "Megawin Technology Inc."
        //</e>
        
        
        //<e0> Enable string descriptor describing product.
        #define PD_STRING                     1
        #define PD_STRING_INDEX               (( MF_STRING + PD_STRING) * PD_STRING)
            //<s> Product string descriptor.
            #define PRODUCT_DESCRIPTOR        "Sample Mouse"
        //</e>
        
        //<e0> Enable string descriptor describing the device's serial number.
        #define SN_STRING                      1
        #define SN_STRING_INDEX                ((MF_STRING + PD_STRING + SN_STRING) * SN_STRING)
            //<s> Serial Number descriptor.
            #define SERIALNUMBER_DESCRIPTOR   "123456"
        //</e>
    //</h>
    //<h> Configuration Descriptor
        //<q0.6> Self-Powered
        //<q0.5> Support Remote-Wakeup
        //<o1> Maximum power consumption of the USB device (2 ~ 510) mA <2-510>
        #define USB_bmAttributes      0xA0
        #define USB_bMaxPower         500
    //</h>

//</h>


// <<< end of Configuration section >>> 






#define MG_USB_SRAM_USBTOTAL_SIZE   (MG_USB_EP0_SRAM_SIZE + MG_USB_EP1_SRAM_SIZE + MG_USB_EP2_SRAM_SIZE + MG_USB_EP3_SRAM_SIZE + \
                                     MG_USB_EP4_SRAM_SIZE + MG_USB_EP5_SRAM_SIZE + MG_USB_EP6_SRAM_SIZE + MG_USB_EP7_SRAM_SIZE) 


#if MG_USB_SRAM_USBTOTAL_SIZE > MG_USB_SRAM_TOTAL_SIZE
    #error MG32x02z_USB_Init.h total use usb sram size over.
#endif

#define USB_EP0_SRAM_RXADR   MG_USB_SRAM_ADR    
#define USB_EP0_SRAM_TXADR   (USB_EP0_SRAM_RXADR +  MG_USB_EP0_SRAM_RXSIZE)

#define USB_EP1_SRAM_RXADR   (USB_EP0_SRAM_TXADR + MG_USB_EP0_SRAM_TXSIZE)
#define USB_EP1_SRAM_TXADR   (USB_EP1_SRAM_RXADR + MG_USB_EP1_SRAM_RXSIZE)

#define USB_EP2_SRAM_RXADR   (USB_EP1_SRAM_TXADR + MG_USB_EP1_SRAM_TXSIZE)
#define USB_EP2_SRAM_TXADR   (USB_EP2_SRAM_RXADR + MG_USB_EP2_SRAM_RXSIZE)

#define USB_EP3_SRAM_RXADR   (USB_EP2_SRAM_TXADR + MG_USB_EP2_SRAM_TXSIZE)
#define USB_EP3_SRAM_TXADR   (USB_EP3_SRAM_RXADR + MG_USB_EP3_SRAM_RXSIZE)

#define USB_EP4_SRAM_RXADR   (USB_EP3_SRAM_TXADR + MG_USB_EP3_SRAM_TXSIZE)
#define USB_EP4_SRAM_TXADR   (USB_EP4_SRAM_RXADR + MG_USB_EP4_SRAM_RXSIZE)

#define USB_EP5_SRAM_RXADR   (USB_EP4_SRAM_TXADR + MG_USB_EP4_SRAM_TXSIZE)
#define USB_EP5_SRAM_TXADR   (USB_EP5_SRAM_RXADR + MG_USB_EP5_SRAM_RXSIZE)

#define USB_EP6_SRAM_RXADR   (USB_EP5_SRAM_TXADR + MG_USB_EP5_SRAM_TXSIZE)
#define USB_EP6_SRAM_TXADR   (USB_EP6_SRAM_RXADR + MG_USB_EP6_SRAM_RXSIZE)

#define USB_EP7_SRAM_RXADR   (USB_EP6_SRAM_TXADR + MG_USB_EP6_SRAM_TXSIZE)
#define USB_EP7_SRAM_TXADR   (USB_EP7_SRAM_RXADR + MG_USB_EP7_SRAM_RXSIZE)


#define MG_USB_EP2_TXADDRESS_CMP    MG_USB_EP1_TXADDRESS
#define MG_USB_EP3_TXADDRESS_CMP   (MG_USB_EP1_TXADDRESS | MG_USB_EP2_TXADDRESS)
#define MG_USB_EP4_TXADDRESS_CMP   (MG_USB_EP1_TXADDRESS | MG_USB_EP2_TXADDRESS | MG_USB_EP3_TXADDRESS )
#define MG_USB_EP5_TXADDRESS_CMP   (MG_USB_EP1_TXADDRESS | MG_USB_EP2_TXADDRESS | MG_USB_EP3_TXADDRESS | MG_USB_EP4_TXADDRESS)
#define MG_USB_EP6_TXADDRESS_CMP   (MG_USB_EP1_TXADDRESS | MG_USB_EP2_TXADDRESS | MG_USB_EP3_TXADDRESS | MG_USB_EP4_TXADDRESS | MG_USB_EP5_TXADDRESS)
#define MG_USB_EP7_TXADDRESS_CMP   (MG_USB_EP1_TXADDRESS | MG_USB_EP2_TXADDRESS | MG_USB_EP3_TXADDRESS | MG_USB_EP4_TXADDRESS | MG_USB_EP5_TXADDRESS | MG_USB_EP6_TXADDRESS)


#define MG_USB_EP2_RXADDRESS_CMP    MG_USB_EP1_RXADDRESS
#define MG_USB_EP3_RXADDRESS_CMP   (MG_USB_EP1_RXADDRESS | MG_USB_EP2_RXADDRESS)
#define MG_USB_EP4_RXADDRESS_CMP   (MG_USB_EP1_RXADDRESS | MG_USB_EP2_RXADDRESS | MG_USB_EP3_RXADDRESS )
#define MG_USB_EP5_RXADDRESS_CMP   (MG_USB_EP1_RXADDRESS | MG_USB_EP2_RXADDRESS | MG_USB_EP3_RXADDRESS | MG_USB_EP4_RXADDRESS)
#define MG_USB_EP6_RXADDRESS_CMP   (MG_USB_EP1_RXADDRESS | MG_USB_EP2_RXADDRESS | MG_USB_EP3_RXADDRESS | MG_USB_EP4_RXADDRESS | MG_USB_EP5_RXADDRESS)
#define MG_USB_EP7_RXADDRESS_CMP   (MG_USB_EP1_RXADDRESS | MG_USB_EP2_RXADDRESS | MG_USB_EP3_RXADDRESS | MG_USB_EP4_RXADDRESS | MG_USB_EP5_RXADDRESS | MG_USB_EP6_RXADDRESS)



#if ( MG_USB_EP2_TXADDRESS_CMP & MG_USB_EP2_TXADDRESS)
    #error MG32x02z_USB_Init.h Endpoint TX Address Conflict.
#endif
#if ( MG_USB_EP3_TXADDRESS_CMP & MG_USB_EP3_TXADDRESS)
    #error MG32x02z_USB_Init.h Endpoint TX Address Conflict.
#endif
#if ( MG_USB_EP4_TXADDRESS_CMP & MG_USB_EP4_TXADDRESS)
    #error MG32x02z_USB_Init.h Endpoint TX Address Conflict.
#endif
#if ( MG_USB_EP5_TXADDRESS_CMP & MG_USB_EP5_TXADDRESS)
    #error MG32x02z_USB_Init.h Endpoint TX Address Conflict.
#endif
#if ( MG_USB_EP6_TXADDRESS_CMP & MG_USB_EP6_TXADDRESS)
    #error MG32x02z_USB_Init.h Endpoint TX Address Conflict.
#endif
#if ( MG_USB_EP7_TXADDRESS_CMP & MG_USB_EP7_TXADDRESS)
    #error MG32x02z_USB_Init.h Endpoint TX Address Conflict.
#endif

#if ( MG_USB_EP2_RXADDRESS_CMP & MG_USB_EP2_RXADDRESS)
    #error MG32x02z_USB_Init.h Endpoint TX Address Conflict.
#endif
#if ( MG_USB_EP3_RXADDRESS_CMP & MG_USB_EP3_RXADDRESS)
    #error MG32x02z_USB_Init.h Endpoint TX Address Conflict.
#endif
#if ( MG_USB_EP4_RXADDRESS_CMP & MG_USB_EP4_RXADDRESS)
    #error MG32x02z_USB_Init.h Endpoint TX Address Conflict.
#endif
#if ( MG_USB_EP5_RXADDRESS_CMP & MG_USB_EP5_RXADDRESS)
    #error MG32x02z_USB_Init.h Endpoint TX Address Conflict.
#endif
#if ( MG_USB_EP6_RXADDRESS_CMP & MG_USB_EP6_RXADDRESS)
    #error MG32x02z_USB_Init.h Endpoint TX Address Conflict.
#endif
#if ( MG_USB_EP7_RXADDRESS_CMP & MG_USB_EP7_RXADDRESS)
    #error MG32x02z_USB_Init.h Endpoint TX Address Conflict.
#endif



#endif









