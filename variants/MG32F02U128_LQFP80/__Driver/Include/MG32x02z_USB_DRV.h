



/**
 ******************************************************************************
 *
 * @file        MG32x02z_USB_DRV.H
 *
 * @brief       This file contains all the functions prototypes for the USB
 *              firmware library.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.02
 * @date        2022/09/13
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************
 * @par 		Disclaimer 
 *		The Demo software is provided "AS IS"  without any warranty, either 
 *		expressed or implied, including, but not limited to, the implied warranties 
 *		of merchantability and fitness for a particular purpose.  The author will 
 *		not be liable for any special, incidental, consequential or indirect 
 *		damages due to loss of data or any other reason. 
 *		These statements agree with the world wide and local dictated laws about 
 *		authorship and violence against these laws. 
 ******************************************************************************
 ******************************************************************************
 */
 
#ifndef _MG32x02z_USB_DRV_H
 
#define _MG32x02z_USB_DRV_H
 

 
#include "MG32x02z.h"
#include "MG32x02z_USB.h"
#include "MG32x02z__Common_DRV.h"
#include "MG32x02z__ExtraStruct.h"


/**
 * @name USB_REG_CTR : USB Register Control Relationship.
 *             
 */ 

///@{

#define USB_SET_BIT(REG,BIT)                    ((REG) = (REG) | (BIT))                                                          /*!< Set bit of the USB register .*/
#define USB_CLEAR_BIT(REG,BIT)                  ((REG) = (REG) & (~BIT))                                                         /*!< Clear bit of the USB register.*/
#define USB_WRITE_REG(REG,VAL)                  (REG) = (VAL)                                                                    /*!< Write the USB register.*/
#define USB_MODIFY_REG(REG,CLEARMSK,SETMSK)     USB_WRITE_REG((REG) , (((USB_READ_REG(REG) & (~(CLEARMSK))) | SETMSK)))          /*!< Modify bits of the USB register.*/
                                                                                                                                 
#define USB_READ_BIT(REG,BIT)                   ((REG) & (BIT))                                                                  /*!< Read the bit status of the USB register.*/
#define USB_READ_REG(REG)                       (REG)                                                                            /*!< Read the USB register.*/


#define USB_EPTXSEQ_SHIFT_B3                    4                                                                                /*!< TX sequence control bit shift.*/
#define USB_EPRXSEQ_SHIFT_B2                    4                                                                                /*!< RX sequence control bit shift.*/
///@}


/**
 * @name USB_IT_STA : USB Interrupt Relationship flag.
 *             
 */ 

///@{

#define USB_IT_BUS              USB_STA_BUSF_mask_w                              /*!<USB bus event global interrupt.*/
    #define USB_IT_BUS_SUSF         USB_STA_SUSF_mask_w                          /*!<USB bus suspend event detect interrupt.*/
    #define USB_IT_BUS_RSMF         USB_STA_RSMF_mask_w                          /*!<USB bus resum event detect interrupt.*/
    #define USB_IT_BUS_RSTF         USB_STA_RSTF_mask_w                          /*!<USB bus reset event detect interrupt.*/
    #define USB_IT_BUS_RWKF         USB_STA_RWKF_mask_w                          /*!<The interrupt is IC wakeup by USB bus reset.*/
    #define USB_IT_BUS_SE1F         USB_STA_SE1F_mask_w                          /*!<USB bus SE1 event detect interrupt.*/

#define USB_IT_ERR              USB_STA_ERRF_mask_w                              /*!<USB bus error global interrupt.*/
    #define USB_IT_ERR_OVR          USB_STA_OVRF_mask_w                          /*!<USB packet memory overrun interrupt.*/
    #define USB_IT_ERR_SETUP        USB_STA_SETUPF_mask_w                        /*!<USB wrong SETUP data received interrupt.*/ 
    #define USB_IT_ERR_NORS         USB_STA_NORSF_mask_w                         /*!<USB host no response error interrupt.*/
    #define USB_IT_ERR_BST          USB_STA_BSTF_mask_w                          /*!<USB bit stuffing error interrupt.*/
    #define USB_IT_ERR_CRC          USB_STA_CRCF_mask_w                          /*!<USB CRC error interrupt.*/
                     
#define USB_IT_EP0              USB_STA_EP0F_mask_w                              /*!<USB endpoint-0 global interrupt.*/
#define USB_IT_EP1              USB_STA_EP1F_mask_w                              /*!<USB endpoint-1 global interrupt.*/ 
#define USB_IT_EP2              USB_STA_EP2F_mask_w                              /*!<USB endpoint-2 global interrupt.*/
#define USB_IT_EP3              USB_STA_EP3F_mask_w                              /*!<USB endpoint-3 global interrupt.*/
#define USB_IT_EP4              USB_STA_EP4F_mask_w                              /*!<USB endpoint-4 global interrupt.*/
#define USB_IT_EP5              USB_STA_EP5F_mask_w                              /*!<USB endpoint-5 global interrupt.*/
#define USB_IT_EP6              USB_STA_EP6F_mask_w                              /*!<USB endpoint-6 global interrupt.*/
#define USB_IT_EP7              USB_STA_EP7F_mask_w                              /*!<USB endpoint-7 global interrupt.*/

#define USB_IT_SOF              USB_STA_SOF_mask_w                               /*!<USB host SOF received interrupt.*/
#define USB_IT_ESOF             USB_STA_ESOF_mask_w                              /*!<USB expected start of frame interrupt.*/
#define USB_IT_LPM              USB_STA_LPMF_mask_w                              /*!<USB LPM L1 state request interrupt.*/             
                             
#define USB_IT_MASK             0x8FFFFFFE                                       /*!<USB all interrupt mask.*/

///@}


/**
 * @name USB_EP0_SETUP_STATUS : EP0 Receive SETUP Relationship Event Flag.
 *             
 */ 

///@{

#define USB_EP0_SETUP           USB_EP0CR0_SETUP0F_mask_b1                        /*!< USB_EP0 is receiving SETUP transaction.*/
#define USB_EP0_EDOVW           USB_EP0CR0_EDOVW0F_mask_b1                        /*!< USB_EP0 was complete received  SETUP transaction.*/
#define USB_EP0_STOVW           USB_EP0CR0_STOVW0F_mask_b1                        /*!< USB_EP0 received SETUP transaction flag.*/

///@}



/**
 * @name USB_EP_FLAG : The define is endpoint register relationship flag.
 *             
 */ 

///@{

#define USB_EP_FLAG_ALL         (USB_EP1CR0_TXSTL1F_mask_h1 | USB_EP1CR0_TXNAK1F_mask_h1 | USB_EP1CR0_TXD1F_mask_h1 |  USB_EP1CR0_ISOTXE1F_mask_h1| \
                                 USB_EP1CR0_RXSTL1F_mask_h1 | USB_EP1CR0_RXNAK1F_mask_h1 | USB_EP1CR0_RXD1F_mask_h1 |  USB_EP1CR0_ISOOVW1F_mask_h1)             /*!< Endpoint all relationship interrupt.*/

#define USB_EP_FLAG_ISOTXEF         USB_EP1CR0_ISOTXE1F_mask_h1                                                                                                 /*!< The flag is the endpoint register isochronous transmit data empty loss error. ( USB_EP0 no the flag).*/
#define USB_EP_FLAG_TXSTALL         USB_EP1CR0_TXSTL1F_mask_h1                                                                                                  /*!< The flag is the endpoint register send STALL in IN  transfer.*/
#define USB_EP_FLAG_TXNAK           USB_EP1CR0_TXNAK1F_mask_h1                                                                                                  /*!< The flag is the endpoint register send NAK   in IN  transfer.*/
#define USB_EP_FLAG_TXDONE          USB_EP1CR0_TXD1F_mask_h1                                                                                                    /*!< The flag is the endpoint register trasmission done.*/
#define USB_EP_FLAG_RXISOOVW        USB_EP1CR0_ISOOVW1F_mask_h1                                                                                                 /*!< The flag is the endpoint register isochronous receive data overwrite error. ( USB_EP0 no the flag).*/
#define USB_EP_FLAG_RXSTALL         USB_EP1CR0_RXSTL1F_mask_h1                                                                                                  /*!< The flag is the endpoint register send STALL in OUT transfer.*/
#define USB_EP_FLAG_RXNAK           USB_EP1CR0_RXNAK1F_mask_h1                                                                                                  /*!< The flag is the endpoint register send NAK   in OUT transfer.*/
#define USB_EP_FLAG_RXDONE          USB_EP1CR0_RXD1F_mask_h1                                                                                                    /*!< The flag is the endpoint register receive data done.*/
#define USB_EP_FLAG_DBUFFER_RXDONE  (USB_EP1CR0_RXD1F_mask_h1 | USB_EP1CR0_TXD1F_mask_h1)                                                                       /*!< The flag is the endpoint register recevie data done and two buffer is full in double buffer mode.*/
#define USB_EP_FLAG_DBUFFER0_RXDONE USB_EP1CR0_RXD1F_mask_h1                                                                                                    /*!< The flag is the endpoint register receive data done and buffer0 is full in double buffer mode.*/
#define USB_EP_FLAG_DBUFFER1_RXDONE USB_EP1CR0_TXD1F_mask_h1                                                                                                    /*!< The flag is the endpoint register receive data done and buffer1 is full in double buffer mode.*/
#define USB_EP_FLAG_DBUFFER_TXDONE  (USB_EP1CR0_RXD1F_mask_h1 | USB_EP1CR0_TXD1F_mask_h1)                                                                       /*!< The flag is the endpoint register transmission done and two buffer is empty in double buffer mode.*/
#define USB_EP_FLAG_DBUFFER0_TXDONE USB_EP1CR0_RXD1F_mask_h1                                                                                                    /*!< The flag is the endpoint register transmission done and buffer0 is empty in double buffer mode.*/
#define USB_EP_FLAG_DBUFFER1_TXDONE USB_EP1CR0_TXD1F_mask_h1                                                                                                    /*!< The flag is the endpoint register transmission done and buffer1 is empty in double buffer mode.*/ 

///@}

/**
 * @name USB_EP_FLAG_IE : The define is endpoint register relationship flag and interrupt enable.
 *             
 */ 

///@{

#define USB_EP_ITFLAG_ALLMSK          0xFFFF00FF                                                                                                                 /*!< The function relationship bit mask.*/
#define USB_EP_ITFLAG_TXSTALL         (USB_EP1CR0_TXSTL1F_mask_w | USB_EP1CR0_TXSTL1_IE_mask_w  )                                                                /*!< The status is that endpoint register send STALL in IN transfer and the interrupt enable.*/
#define USB_EP_ITFLAG_TXNAK           (USB_EP1CR0_TXNAK1F_mask_w | USB_EP1CR0_TXNAK1_IE_mask_w  )                                                                /*!< The status is that endpoint register send NAK in IN transfer and the interrupt enable.*/
#define USB_EP_ITFLAG_TXDONE          (USB_EP1CR0_TXD1F_mask_w   | USB_EP1CR0_TXD1_IE_mask_w    )                                                                /*!< The status is that endpoint register transmission done and the interrupt enable.*/
#define USB_EP_ITFLAG_RXSTALL         (USB_EP1CR0_RXSTL1F_mask_w | USB_EP1CR0_RXSTL1_IE_mask_w  )                                                                /*!< The status is that endpoint register send STALL in OUT transfer and the interrupt enable.*/
#define USB_EP_ITFLAG_RXNAK           (USB_EP1CR0_RXNAK1F_mask_w | USB_EP1CR0_RXNAK1_IE_mask_w  )                                                                /*!< The status is that endpoint register send NAK in OUT transfer and the interupt enable.*/
#define USB_EP_ITFLAG_RXDONE          (USB_EP1CR0_RXD1F_mask_w   | USB_EP1CR0_RXD1_IE_mask_w    )                                                                /*!< The status is that endpoint register receive data done and the interrupt enable.*/
#define USB_EP_ITFLAG_DBUFFER_RXDONE  (USB_EP1CR0_TXD1F_mask_w   | USB_EP1CR0_RXD1F_mask_w | USB_EP1CR0_TXD1_IE_mask_w | USB_EP1CR0_RXD1_IE_mask_w)              /*!< The status is that endpoint register buffer0 and buffere1 receive data done and the interrupt enable.*/
#define USB_EP_ITFLAG_DBUFFER0_RXDONE (USB_EP1CR0_RXD1F_mask_w   | USB_EP1CR0_RXD1_IE_mask_w    )                                                                /*!< The status is that endpoint register buffer0 receive data done and the interrupt enable.*/
#define USB_EP_ITFLAG_DBUFFER1_RXDONE (USB_EP1CR0_TXD1F_mask_w   | USB_EP1CR0_TXD1_IE_mask_w    )                                                                /*!< The status is that endpoint register buffer1 receive data done and the interrupt enable.*/
#define USB_EP_ITFLAG_DBUFFER_TXDONE  (USB_EP1CR0_TXD1F_mask_w   | USB_EP1CR0_RXD1F_mask_w | USB_EP1CR0_TXD1_IE_mask_w | USB_EP1CR0_RXD1_IE_mask_w)              /*!< The status is that endpoint register buffer0 and buffer1 transmission data done and the interrupt enable.*/
#define USB_EP_ITFLAG_DBUFFER0_TXDONE (USB_EP1CR0_RXD1F_mask_w   | USB_EP1CR0_RXD1_IE_mask_w    )                                                                /*!< The status is that endpoint register buffer0 transmission data done and the the interrupt enable.*/
#define USB_EP_ITFLAG_DBUFFER1_TXDONE (USB_EP1CR0_TXD1F_mask_w   | USB_EP1CR0_TXD1_IE_mask_w    )                                                                /*!< The status is that endpoint register buffer1 transmission data done and the the interrupt enable.*/

///@}    
    
/**
 * @name USB_EP_IE : 
 *             
 */ 

///@{                                                                                                                                                             
#define USB_EP_IE_TXSTALL           USB_EP1CR0_TXSTL1_IE_mask_b0                                                                                                  /*!< The interrupt is the Endpoint register send STALL in IN  transfer.*/
#define USB_EP_IE_TXNAK             USB_EP1CR0_TXNAK1_IE_mask_b0                                                                                                  /*!< The interrupt is the Endpoint register send NAK   in IN  transfer.*/
#define USB_EP_IE_TXDONE            USB_EP1CR0_TXD1_IE_mask_b0                                                                                                    /*!< The interrupt is the Endpoint register trasmission done.*/
#define USB_EP_IE_RXSTALL           USB_EP1CR0_RXSTL1_IE_mask_b0                                                                                                  /*!< The interrupt is the Endpoint register send STALL in OUT transfer.*/
#define USB_EP_IE_RXNAK             USB_EP1CR0_RXNAK1_IE_mask_b0                                                                                                  /*!< The interrupt is the Endpoint register send NAK   in OUT transfer.*/
#define USB_EP_IE_RXDONE            USB_EP1CR0_RXD1_IE_mask_b0                                                                                                    /*!< The interrupt is the Endpoint register receive data done.*/
#define USB_EP_IE_DBUFFER_RXDONE    (USB_EP1CR0_TXD1_IE_mask_b0 | USB_EP1CR0_RXD1_IE_mask_b0)                                                                     /*!< The interrupt is the Endpoint register receive data done.*/
#define USB_EP_IE_DBUFFER_TXDONE    (USB_EP1CR0_TXD1_IE_mask_b0 | USB_EP1CR0_RXD1_IE_mask_b0)                                                                     /*!< The interrupt is the Endpoint register trasmission done.*/
#define USB_EP_IE_ALL               (USB_EP_IE_TXSTALL  |  USB_EP_IE_TXNAK | USB_EP_IE_TXDONE | USB_EP_IE_RXSTALL  |  USB_EP_IE_RXNAK | USB_EP_IE_RXDONE)         /*!< The Endpoint register all interrupt.*/
                                     

///@}

/**
 * @name USB_EP_STATUS : Endpoint status relationship define in Endpoint buffer mode is " normal " mode 
 *             
 */ 

///@{

#define USB_EP_TXSTATUS_MASK          (USB_EP0CR1_TXEN0_mask_h1    | USB_EP0CR1_TXSTL0_mask_h1    | USB_EP0CR1_TXMC0_mask_h1)                    /*!< The control mask is that all TX status relationship control bit.*/
#define USB_EP_TXDISABLE_MASK         (USB_EP0CR1_TXEN0_disable_h1 | USB_EP0CR1_TXSTL0_disable_h1 | USB_EP0CR1_TXMC0_no_h1)                      /*!< The control mask is that TX status is disable.*/
#define USB_EP_TXNAK_MASK             (USB_EP0CR1_TXEN0_enable_h1  | USB_EP0CR1_TXSTL0_disable_h1 | USB_EP0CR1_TXMC0_no_h1)                      /*!< The control mask is that TX status is NAK.*/
#define USB_EP_TXSTALL_MASK           (USB_EP0CR1_TXEN0_enable_h1  | USB_EP0CR1_TXSTL0_enable_h1  | USB_EP0CR1_TXMC0_no_h1)                      /*!< The control mask is that TX status is STALL.*/
#define USB_EP_TXVALID_MASK           (USB_EP0CR1_TXEN0_enable_h1  | USB_EP0CR1_TXSTL0_disable_h1 | USB_EP0CR1_TXMC0_complete_h1)                /*!< The control mask is that TX status is data ready to send .*/
                                                                                                                                                 
#define USB_EP_RXSTATUS_MASK          (USB_EP0CR1_RXEN0_mask_h1    | USB_EP0CR1_RXSTL0_mask_h1    | USB_EP0CR1_RXMC0_mask_h1)                    /*!< The control mask is that all RX status relationship control bit .*/
#define USB_EP_RXDISABLE_MASK         (USB_EP0CR1_RXEN0_disable_h1 | USB_EP0CR1_RXSTL0_disable_h1 | USB_EP0CR1_RXMC0_no_h1)                      /*!< The control mask is that RX status is disable .*/
#define USB_EP_RXNAK_MASK             (USB_EP0CR1_RXEN0_enable_h1  | USB_EP0CR1_RXSTL0_disable_h1 | USB_EP0CR1_RXMC0_no_h1)                      /*!< The control mask is that RX status is NAK .*/
#define USB_EP_RXSTALL_MASK           (USB_EP0CR1_RXEN0_enable_h1  | USB_EP0CR1_RXSTL0_enable_h1  | USB_EP0CR1_RXMC0_no_h1)                      /*!< The control mask is that RX status is STALL .*/
#define USB_EP_RXVALID_MASK           (USB_EP0CR1_RXEN0_enable_h1  | USB_EP0CR1_RXSTL0_disable_h1 | USB_EP0CR1_RXMC0_complete_h1)                /*!< The control mask is that RX status is ready to receive new data .*/


/*! @enum  USB_EPStatus_TypeDef
    @brief USB endpoint status control in no double buffer mode.
*/ 
typedef enum
{ 
    EP_RX_DISABLE            = ( USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP_RXDISABLE_MASK)  ,                                                                 /*!< RX status change to DISABLE.*/
    EP_RX_DISABLE_TX_DISABLE = ( USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP_RXDISABLE_MASK)  | ( USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP_TXDISABLE_MASK) ,       /*!< RX status change to DISABLE and TX status change to DISABLE.*/
    EP_RX_DISABLE_TX_NAK     = ( USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP_RXDISABLE_MASK)  | ( USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP_TXNAK_MASK    ) ,       /*!< RX status change to DISABLE and TX status change to NAK.*/
    EP_RX_DISABLE_TX_STALL   = ( USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP_RXDISABLE_MASK)  | ( USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP_TXSTALL_MASK  ) ,       /*!< RX status change to DISABLE and TX status change to STALL.*/
    EP_RX_DISABLE_TX_VALID   = ( USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP_RXDISABLE_MASK)  | ( USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP_TXVALID_MASK  ) ,       /*!< RX status change to DISABLE and TX status change to ready send data.*/
                                                                                                                                                          
    EP_RX_NAK                = ( USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP_RXNAK_MASK    )  ,                                                                 /*!< RX status keep in NAK .*/
    EP_RX_NAK_TX_DISABLE     = ( USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP_RXNAK_MASK    )  | ( USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP_TXDISABLE_MASK) ,       /*!< RX status keep in NAK and TX status change to DISABLE.*/
    EP_RX_NAK_TX_NAK         = ( USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP_RXNAK_MASK    )  | ( USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP_TXNAK_MASK    ) ,       /*!< RX status keep in NAK and TX status change to NAK.*/
    EP_RX_NAK_TX_STALL       = ( USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP_RXNAK_MASK    )  | ( USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP_TXSTALL_MASK  ) ,       /*!< RX status keep in NAK and TX status change to STALL.*/
    EP_RX_NAK_TX_VALID       = ( USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP_RXNAK_MASK    )  | ( USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP_TXVALID_MASK  ) ,       /*!< RX status keep in NAK and TX status change to ready send data.*/
                                                                                                                                                         
    EP_RX_STALL              = ( USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP_RXSTALL_MASK  )  ,                                                                 /*!< RX status change to STALL .*/
    EP_RX_STALL_TX_DISABLE   = ( USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP_RXSTALL_MASK  )  | ( USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP_TXDISABLE_MASK) ,       /*!< RX status change to STALL and TX status change to DISABLE.*/
    EP_RX_STALL_TX_NAK       = ( USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP_RXSTALL_MASK  )  | ( USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP_TXNAK_MASK    ) ,       /*!< RX status change to STALL and TX status change to NAK.*/
    EP_RX_STALL_TX_STALL     = ( USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP_RXSTALL_MASK  )  | ( USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP_TXSTALL_MASK  ) ,       /*!< RX status change to STALL and TX status change to STALL.*/
    EP_RX_STALL_TX_VALID     = ( USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP_RXSTALL_MASK  )  | ( USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP_TXVALID_MASK  ) ,       /*!< RX status change to STALL and TX status change to ready send data.*/
                                                                                                                                                          
    EP_RX_VALID              = ( USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP_RXVALID_MASK  )  ,                                                                 /*!< RX status change to ready receive new data.*/
    EP_RX_VALID_TX_DISABLE   = ( USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP_RXVALID_MASK  )  | ( USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP_TXDISABLE_MASK) ,       /*!< RX status change to ready receive new data and TX status change to DISABLE .*/
    EP_RX_VALID_TX_NAK       = ( USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP_RXVALID_MASK  )  | ( USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP_TXNAK_MASK    ) ,       /*!< RX status change to ready receive new data and TX status change to NAK.*/
    EP_RX_VALID_TX_STALL     = ( USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP_RXVALID_MASK  )  | ( USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP_TXSTALL_MASK  ) ,       /*!< RX status change to ready receive new data and TX status change to STALL.*/
    EP_RX_VALID_TX_VALID     = ( USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP_RXVALID_MASK  )  | ( USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP_TXVALID_MASK  ) ,       /*!< RX status change to ready receive new data and TX status change to ready send data.*/
                                                                                                                                                        
    EP_TX_DISABLE            = ( USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP_TXDISABLE_MASK),                                                                   /*!< TX status change to DISABLE.*/
    EP_TX_NAK                = ( USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP_TXNAK_MASK    ),                                                                   /*!< TX status change to NAK.*/
    EP_TX_STALL              = ( USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP_TXSTALL_MASK  ),                                                                   /*!< TX status change to STALL.*/
    EP_TX_VALID              = ( USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP_TXVALID_MASK  )                                                                    /*!< TX status change to ready to send data.*/
    
}USB_EPStatus_TypeDef;


///@}

/**
 * @name USB_EP_STATUS : Endpoint status relationship define in Endpoint buffer mode is " double buffer "  mode 
 *             
 */ 

///@{

#define USB_EPDB_STATUS_MASK          (USB_EP0CR1_TXMC0_mask_h1 | USB_EP0CR1_TXSTL0_mask_h1 | USB_EP0CR1_TXEN0_mask_h1 |  \
                                       USB_EP0CR1_RXMC0_mask_h1 | USB_EP0CR1_RXSTL0_mask_h1 | USB_EP0CR1_RXEN0_mask_h1)                                                        /*!< The control mask is that all double buffer relationship control bit .*/
#define USB_EPDB_DISABLE_MASK         (USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP0CR1_RXEN0_disable_h1  | USB_EP0CR1_RXSTL0_disable_h1 | USB_EP0CR1_RXMC0_no_h1 | \
                                       USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP0CR1_TXEN0_disable_h1  | USB_EP0CR1_TXSTL0_disable_h1 | USB_EP0CR1_TXMC0_no_h1)                    /*!< The control mask is that double buffer channel (TX / RX) disable .*/
#define USB_EPDB_TXBUFALL_NAK_MASK    (USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP0CR1_TXEN0_enable_h1   | USB_EP0CR1_TXSTL0_disable_h1 | USB_EP0CR1_TXMC0_no_h1 | \
                                       USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP0CR1_RXEN0_disable_h1  | USB_EP0CR1_RXSTL0_disable_h1 | USB_EP0CR1_RXMC0_no_h1)                    /*!< The control mask is that double buffer is TX type and all buffer is NAK status .*/

#define USB_EPDB_TXBUF0_NAK_MASK      (USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP0CR1_RXEN0_disable_h1  | USB_EP0CR1_RXSTL0_disable_h1 | USB_EP0CR1_RXMC0_no_h1)                    /*!< The control mask is that double buffer is TX type and buffer0 is NAK status.*/

#define USB_EPDB_TXBUF1_NAK_MASK      (USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP0CR1_TXEN0_enable_h1   | USB_EP0CR1_TXSTL0_disable_h1 | USB_EP0CR1_TXMC0_no_h1)                    /*!< The control mask is that double buffer is TX type and buffer1 is NAK status.*/


#define USB_EPDB_RXBUFALL_NAK_MASK    (USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP0CR1_TXEN0_disable_h1  | USB_EP0CR1_TXSTL0_disable_h1 | USB_EP0CR1_TXMC0_no_h1 | \
                                       USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP0CR1_RXEN0_enable_h1   | USB_EP0CR1_RXSTL0_disable_h1 | USB_EP0CR1_RXMC0_no_h1)                    /*!< The control mask is that double buffer is RX type and all buffer is NAK status .*/
                                       
#define USB_EPDB_RXBUF0_NAK_MASK      (USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP0CR1_RXEN0_enable_h1   | USB_EP0CR1_RXSTL0_disable_h1 | USB_EP0CR1_RXMC0_no_h1)                    /*!< The control mask is that double buffer is RX type and buffer0 is NAK status.*/

#define USB_EPDB_RXBUF1_NAK_MASK      (USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP0CR1_TXEN0_disable_h1  | USB_EP0CR1_TXSTL0_disable_h1 | USB_EP0CR1_TXMC0_no_h1)                    /*!< The control mask is that double buffer is RX type and buffer1 is NAK status.*/


#define USB_EPDB_RXBUFALL_VALID_MASK  (USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP0CR1_RXEN0_enable_h1   | USB_EP0CR1_RXSTL0_disable_h1 | USB_EP0CR1_RXMC0_complete_h1 | \
                                       USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP0CR1_TXEN0_disable_h1  | USB_EP0CR1_TXSTL0_disable_h1 | USB_EP0CR1_TXMC0_complete_h1 )             /*!< The control mask is that double buffer is RX type and all buffer ready receive new data.*/
                                       
#define USB_EPDB_RXBUF0_VALID_MASK    (USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP0CR1_RXEN0_enable_h1   | USB_EP0CR1_RXSTL0_disable_h1 | USB_EP0CR1_RXMC0_complete_h1)              /*!< The control mask is that double buffer is RX type and buffer0 ready receive new data. */

#define USB_EPDB_RXBUF1_VALID_MASK    (USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP0CR1_TXEN0_disable_h1  | USB_EP0CR1_TXSTL0_disable_h1 | USB_EP0CR1_TXMC0_complete_h1)              /*!< The control mask is that double buffer is RX type and buffer1 ready receive new data.*/             
                                       
#define USB_EPDB_TXBUFALL_VALID_MASK  (USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP0CR1_RXEN0_disable_h1  | USB_EP0CR1_RXSTL0_disable_h1 | USB_EP0CR1_RXMC0_complete_h1 | \
                                       USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP0CR1_TXEN0_enable_h1  | USB_EP0CR1_TXSTL0_disable_h1 | USB_EP0CR1_TXMC0_complete_h1)               /*!< The control mask is that double buffer is TX type and all buffer ready send data.*/      
                                       
#define USB_EPDB_TXBUF0_VALID_MASK    (USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP0CR1_RXEN0_disable_h1  | USB_EP0CR1_RXSTL0_disable_h1 | USB_EP0CR1_RXMC0_complete_h1)              /*!< The control mask is that doubel buffer is TX type and buffer0 ready send data.*/ 

#define USB_EPDB_TXBUF1_VALID_MASK    (USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP0CR1_TXEN0_enable_h1  | USB_EP0CR1_TXSTL0_disable_h1 | USB_EP0CR1_TXMC0_complete_h1)               /*!< The control mask is that double buffer is TX type and buffer1 ready send data.*/

#define USB_EPDB_TXSTALL_MASK         (USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP0CR1_TXEN0_enable_h1   | USB_EP0CR1_TXSTL0_enable_h1  | USB_EP0CR1_TXMC0_no_h1 | \
                                       USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP0CR1_RXEN0_disable_h1  | USB_EP0CR1_RXSTL0_disable_h1 | USB_EP0CR1_RXMC0_no_h1)                    /*!< The control mask is that double buffer is TX type and STALL status.*/ 
#define USB_EPDB_RXSTALL_MASK         (USB_EP0CR1_TXSA_LCK0_mask_h1 | USB_EP0CR1_TXEN0_disable_h1  | USB_EP0CR1_TXSTL0_disable_h1 | USB_EP0CR1_TXMC0_no_h1 | \
                                       USB_EP0CR1_RXSA_LCK0_mask_h1 | USB_EP0CR1_RXEN0_enable_h1   | USB_EP0CR1_RXSTL0_enable_h1  | USB_EP0CR1_RXMC0_no_h1)                    /*!< The control mask is that double buffer is RX type and STALL status.*/



/*! @enum  USB_EPDBStatus_TypeDef
    @brief USB endpoint status control in double buffer mode.
*/ 
typedef enum
{ 
    EP_DB_DISABLE            = USB_EPDB_DISABLE_MASK,                                              /*!< Double buffer mode status change to TX / RX disable.*/
    EP_DB_RX_STALL           = USB_EPDB_RXSTALL_MASK,                                              /*!< Double buffer mode status change to RX STALL.*/
    EP_DB_TX_STALL           = USB_EPDB_TXSTALL_MASK,                                              /*!< Double buffer mode status change to TX STALL.*/

    EP_DB_RXBUFALL_NAK       = USB_EPDB_RXBUFALL_NAK_MASK,                                         /*!< All buffer status of double buffer mode is keeping in RX NAK.*/
    EP_DB_RXBUF0_NAK         = USB_EPDB_RXBUF0_NAK_MASK,                                           /*!< Buffer0 status of double buffer mode is keeping in RX NAK.*/
    EP_DB_RXBUF1_NAK         = USB_EPDB_RXBUF1_NAK_MASK,                                           /*!< Buffer1 status of double buffer mode is keeping in RX NAK.*/
                                                                                                   
    EP_DB_TXBUFALL_NAK       = USB_EPDB_TXBUFALL_NAK_MASK,                                         /*!< All buffer status of double buffer mode is keep in TX NAK.*/
    EP_DB_TXBUF0_NAK         = USB_EPDB_TXBUF0_NAK_MASK,                                           /*!< Buffer0 status of double buffer mode is keep in TX NAK.*/
    EP_DB_TXBUF1_NAK         = USB_EPDB_TXBUF1_NAK_MASK,                                           /*!< Buffer1 status of double buffer mode is keep in TX NAK.*/
    
    EP_DB_RXBUFALL_VALID     = USB_EPDB_RXBUFALL_VALID_MASK,                                       /*!< All buffer status of double buffer mode change to ready receive new data .*/
    EP_DB_RXBUF0_VALID       = USB_EPDB_RXBUF0_VALID_MASK,                                         /*!< Buffer0 status of double buffer mode change to ready receive new data .*/  
    EP_DB_RXBUF1_VALID       = USB_EPDB_RXBUF1_VALID_MASK,                                         /*!< Buffer1 status of double buffer mode change to ready receive new data .*/
    
    EP_DB_TXBUFALL_VALID     = USB_EPDB_TXBUFALL_VALID_MASK,                                       /*!< All buffer status of double buffer mode change to ready send data.*/
    EP_DB_TXBUF0_VALID       = USB_EPDB_TXBUF0_VALID_MASK,                                         /*!< Buffer0 status of double buffer mode change to ready send data.*/
    EP_DB_TXBUF1_VALID       = USB_EPDB_TXBUF1_VALID_MASK                                          /*!< Buffer1 status of double buffer mode change to ready send data.*/
    
}USB_EPDBStatus_TypeDef;


///@}


/*! @enum  USB_EPMode_TypeDef
    @brief 
*/ 

typedef enum
{
    EP_RX_BKINT          = USB_EP1CR1_RXTYPE1_bkint_b0,                                             /*!< The endpoint register type is RX bulk / interrupt.*/
    EP_TX_BKINT          = USB_EP1CR1_TXTYPE1_bkint_b0,                                             /*!< The endpoint register type is TX bulk / interrupt.*/
    EP_RX_BKINT_TX_BKINT = USB_EP1CR1_RXTYPE1_bkint_b0 | USB_EP1CR1_TXTYPE1_bkint_b0,               /*!< The endpoint register type is RX bulk / interrupt and TX bulk / interrupt.*/
    EP_RX_BKINT_TX_ISO   = USB_EP1CR1_RXTYPE1_bkint_b0 | USB_EP1CR1_TXTYPE1_iso_b0,                 /*!< The endpoint register type is RX bulk / interrupt and TX isochronous.*/
                                                                                                    
    EP_RX_ISO            = USB_EP1CR1_RXTYPE1_iso_b0,                                               /*!< The endpoint register type is RX isochronous.*/
    EP_TX_ISO            = USB_EP1CR1_TXTYPE1_iso_b0,                                               /*!< The endpoint register type is TX isochronous.*/
    EP_RX_ISO_TX_BKINT   = USB_EP1CR1_RXTYPE1_iso_b0 | USB_EP1CR1_TXTYPE1_bkint_b0,                 /*!< The endpoint register type is RX isochronous and TX bulk / interrupt.*/
    EP_RX_ISO_TX_ISO     = USB_EP1CR1_RXTYPE1_iso_b0 | USB_EP1CR1_TXTYPE1_iso_b0                    /*!< The endpoint register type is RX isochronous and TX isochronous.*/

}USB_EPMode_TypeDef;



/*! @enum  USB_EPRST_TypeDef
    @brief 
*/ 

typedef enum
{
    EP_RST_TX            = USB_EP0CR0_TXRST0_enable_b1,                                              /*!< Reset TX block in the endpoint register.*/
    EP_RST_RX            = USB_EP0CR0_RXRST0_enable_b1,                                              /*!< Reset RX block in the endpoint register.*/
    EP_RST_TX_RX         = USB_EP0CR0_TXRST0_enable_b1 | USB_EP0CR0_RXRST0_enable_b1,                /*!< Reset TX / RX blocks in the endpoint register.*/
    EP_RST_DB            = USB_EP0CR0_TXRST0_enable_b1 | USB_EP0CR0_RXRST0_enable_b1                 /*!< Reset Double buffer block in the endpoint register.*/
}USB_EPRST_TypeDef;



/*! @enum  USB_BusEventState_TypeDef
    @brief 
*/ 
typedef enum
{
    USB_BUS_K_STA      = USB_STA2_K_STA_mask_b0   ,                                                  /*!< USB bus K state.*/
    USB_BUS_J_STA      = USB_STA2_J_STA_mask_b0   ,                                                  /*!< USB bus J state.*/
    USB_BUS_SE1_STA    = USB_STA2_SE1_STA_mask_b0 ,                                                  /*!< USB bus SE1 state.*/
    USB_BUS_SE0_STA    = USB_STA2_SE0_STA_mask_b0 ,                                                  /*!< USB bus SE0 state.*/
    USB_BUS_DM_STA     = USB_STA2_DMI_STA_mask_b0 ,                                                  /*!< USB bus DM > VIH state.*/
    USB_BUS_DP_STA     = USB_STA2_DPI_STA_mask_b0 ,                                                  /*!< USB bus DP > VIH state.*/
    USB_BUS_DI_STA     = USB_STA2_DI_STA_mask_b0                                                     /*!< USB bus Differential is 1.*/
}USB_BusEventState_TypeDef;



/*! @enum  USB_EPMode_TypeDef
    @brief 
*/ 
typedef enum
{
    USB_RemoteWakeup_6ms     = USB_CR0_RWK_DSEL_dt0_b0,                                              /*!< Remotewakeup signal is 6ms in remotewake signal is controled by hardware.*/
    USB_RemoteWakeup_3ms     = USB_CR0_RWK_DSEL_dt1_b0,                                              /*!< Remotewakeup signal is 3ms in remotewake signal is controled by hardware.*/
    USB_RemoteWakeup_110us   = USB_CR0_RWK_DSEL_dt2_b0,                                              /*!< Remotewakeup signal is 110us im remotewake signal is controled by hardware.*/
    USB_RemoteWakeup_55us    = USB_CR0_RWK_DSEL_dt3_b0                                               /*!< Remotewakeup signal is 55us in remotewake signal is controled by hardware.*/
}USB_RemoteWakeupTime_TypeDef;



/*! @enum  USB_OUTDrive_Typedef
    @brief DP and DM output drive strength select. 
*/
typedef enum
{
    USBOCD_DPLVL0_DMLVL0 = USB_CR0_DP_ODC_level0_b2 | USB_CR0_DM_ODC_level0_b2,                       /*!< DP output drive strength is normal and DM output drive strength is normal .*/
    USBOCD_DPLVL0_DMLVL1 = USB_CR0_DP_ODC_level0_b2 | USB_CR0_DM_ODC_level1_b2,                       /*!< DP output drive strength is normal and DM output drive strength is (normal * 1.1).*/
    USBOCD_DPLVL1_DMLVL0 = USB_CR0_DP_ODC_level1_b2 | USB_CR0_DM_ODC_level0_b2,                       /*!< DP output drive strength is (normal * 1.1) and DM output drive strength is normal.*/
    USBOCD_DPLVL1_DMLVL1 = USB_CR0_DP_ODC_level1_b2 | USB_CR0_DM_ODC_level1_b2                        /*!< DP output drive strength is (normal * 1.1) and DM output drive strength is (normal * 1.1).*/
}USB_OUTDrive_Typedef;



/*! @enum  USB_PDResistorMode_TypeDef
    @brief USB DP / DM pull-down control
*/
typedef enum
{
    USB_DP_DIS_DM_DIS   = USB_CR0_DP_PD_disable_b2 | USB_CR0_DM_PD_disable_b2,                          /*!< DP : pull-down (DP_PD) = Disable , DM : pull-down (DM_PD)  = Disable.*/
    USB_DP_DIS_DM_PD    = USB_CR0_DP_PD_disable_b2 | USB_CR0_DM_PD_enable_b2,                           /*!< DP : pull-down (DP_PD) = Disable , DM : pull-down (DM_PD)  = Enable.*/
    USB_DP_PD_DM_DIS    = USB_CR0_DP_PD_enable_b2  | USB_CR0_DM_PD_disable_b2,                          /*!< DP : pull-down (DP_PD) = Enable  , DM : pull-down (DM_PD)  = Disable.*/
    USB_DP_PD_DM_PD     = USB_CR0_DP_PD_enable_b2  | USB_CR0_DM_PD_enable_b2                            /*!< DP : pull-down (DP_PD) = Enable  , DM : pull-down (DM_PD)  = Enable.*/    
}USB_PDResistorMode_TypeDef;


/*! @enum  USB_PUResistorMode_TypeDef
    @brief USB DP pull-up resistance mode control.
*/
typedef enum
{
    USBPUR_FIX_NO_AUTO    =  USB_CR0_DPU_MDS_fix_b2     | USB_CR0_DPU_AUTO_disable_b2 ,                  /*!< DP pull up resister always enable and value of pull-up resister is always 1.2K ohm. */
    USBPUR_FIX_AUTO       =  USB_CR0_DPU_MDS_fix_b2     | USB_CR0_DPU_AUTO_enable_b2  ,                  /*!< DP pull up resister auto disable in output low and value of pull-up resister is always 1.2K ohm.*/
    USBPUR_SWITCH_NO_AUTO =  USB_CR0_DPU_MDS_switch_b2  | USB_CR0_DPU_AUTO_disable_b2 ,                  /*!< DP pull up resister always enable and value of pull-up resister is different between ( SE0 , J State (1.2Kohm) ) and K state (2.4 kohm).*/
    USBPUR_SWITCH_AUTO    =  USB_CR0_DPU_MDS_switch_b2  | USB_CR0_DPU_AUTO_enable_b2                     /*!< DP pull up resister auto disable in output low and value of pull-up resister is different between ( SE0 , J State (1.2Kohm) ) and K state (2.4 kohm).*/
}USB_PUResistorMode_TypeDef;
                



/*! @enum  USB_LPMHandShake_TypeDef
    @brief 
*/
typedef enum
{                                                                                                        /*!< When receiving Host LPM request USB device send ACK..*/
    USB_LPM_ACK     =  ( USB_CR1_LPM_EN_enable_b2 | USB_CR1_LPM_ACK_ack_b2) ,                            /*!< When receiving Host LPM request USB device send NYET.*/
    USB_LPM_NYET    =  ( USB_CR1_LPM_EN_enable_b2 | USB_CR1_LPM_ACK_nyet_b2),                            /*!< When receiving Host LPM request USB device no reflect.*/
    USB_LPM_DISABLE =  ( USB_CR1_LPM_EN_disable_b2)                                                       
}USB_LPMHandShake_TypeDef;

/*! @enum   USB_SUSMDS_TypeDef
    @brief  USB suspend signal detect mode control.
*/
typedef enum
{
    USB_SUS_JSTATE        =  USB_CR0_SUS_MDS_js_b0,                                                      /*!< Detect J state.*/
    USB_SUS_J_OR_SE1STATE =  USB_CR0_SUS_MDS_both_b0                                                     /*!< Detect J state or SE1 state.*/
}USB_SUSMDS_TypeDef;


/*! @enum   USB_STOPMode_TypeDef
    @brief 
*/
typedef enum
{
    USB_STOP_LVR_DISABLE = USB_CR0_STP_LVR_disable_b1,                                                    /*!< LVR disable when USB enable and enter STOP mode.*/
    USB_STOP_LVR_ENABLE  = USB_CR0_STP_LVR_enable_b1                                                      /*!< LVR enable when USB enable and enter STOP mode.*/
}USB_STOPMode_TypeDef;


/*! @enum   USB_DMARXSEL_TypeDef
    @brief 
*/
typedef enum
{
    USB_DMA_RXSEL0_DISABLE  = USB_CR2_DMA_RXSEL0_disable_b0,                                              /*!< No Enable the USB RX DMA.*/
    USB_DMA_RXSEL0_EP3      = USB_CR2_DMA_RXSEL0_ep3_b0,                                                  /*!< USB DMA RX source from USB_EP3 RX.*/
    USB_DMA_RXSEL0_EP4      = USB_CR2_DMA_RXSEL0_ep4_b0                                                   /*!< USB DMA RX source from USB_EP4 RX.*/
}USB_DMARXSEL_TypeDef;


/*! @enum   USB_DMATXSEL_TypeDef
    @brief 
*/
typedef enum
{
    USB_DMA_TXSEL0_DISABLE  = USB_CR2_DMA_TXSEL0_disable_b0,                                              /*!< No Enable the USB TX DMA.*/  
    USB_DMA_TXSEL0_EP3      = USB_CR2_DMA_TXSEL0_ep3_b0,                                                  /*!< USB DMA TX destination to USB_EP3 TX.*/  
    USB_DMA_TXSEL0_EP4      = USB_CR2_DMA_TXSEL0_ep4_b0                                                   /*!< USB DMA TX destination to USB_EP4 TX.*/  
}USB_DMATXSEL_TypeDef;



/*! @name USB macro Relationship 
*/
///@{

 /**
 *******************************************************************************
 * @brief	   Get USB_EP0 receing SETUP status.
 * @details 
 * @return     The return value have :
 *      \n     Bit0 : USB_EP0_STOVW - USB_EP0 is receiving SETUP transaction.
 *      \n     Bit1 : USB_EP0_EDOVW - USB_EP0 was complete received  SETUP transaction.
 *      \n     Bit2 : USB_EP0_SETUP - USB_EP0 received SETUP transaction flag.    
 * @exception  No
 * @note 
 *******************************************************************************
 */
#define __DRV_USB_GETSETUP_STATUS()           (USB_READ_REG(USB_EP0->CR0.B[1]))               

 /**
 *******************************************************************************
 * @brief	   Clear event status that USB_EP0 was complete received  SETUP transaction.
 * @details   
 * @exception  No
 * @note 
 *******************************************************************************
 */

#define __DRV_USB_CLEAR_EDOVW()               (USB_WRITE_REG(USB_EP0->CR0.B[1], USB_EP0_EDOVW)) 
 /**
 *******************************************************************************
 * @brief	   Clear event flag that USB_EP0 received SETUP transaction.
 * @details 
 * @exception  No
 * @note 
 *******************************************************************************
 */
#define __DRV_USB_CLEAR_RXSETUP()             (USB_WRITE_REG(USB_EP0->CR0.B[1], USB_EP0_SETUP))      
 /**
 *******************************************************************************
 * @brief	   Set the USB device addresss.
 * @details   
 * @exception  No
 * @note 
 *******************************************************************************
 */
#define __DRV_USB_SETADDRESS(__ADR__)         USB_WRITE_REG(USB->CR1.B[0] , (__ADR__))                                    
 /**
 *******************************************************************************
 * @brief	   USB connect function.
 * @details 
 * @exception  No
 * @note 
 *******************************************************************************
 */
#define __DRV_USB_CONNECT()                    USB_MODIFY_REG(USB->CR0.B[2] , USB_CR0_DPU_EN_mask_b2 , USB_CR0_DPU_EN_enable_b2)
 /**
 *******************************************************************************
 * @brief	   USB disconnect .
 * @details 
 * @exception  No
 * @note 
 *******************************************************************************
 */
#define __DRV_USB_DISCONNECT()                 USB_MODIFY_REG(USB->CR0.B[2] , USB_CR0_DPU_EN_mask_b2 , USB_CR0_DPU_EN_disable_b2)

 /**
 *******************************************************************************
 * @brief	   Get USB bus status.
 * @details 
 * @return     The read value is :
 *       \n    USB_BUS_K_STA  : USB bus is K state now.  
 *       \n    USB_BUS_J_STA  : USB bus is J state now.
 *       \n    USB_BUS_SE0_STA: USB bus is SE0 state now.
 *       \n    USB_BUS_SE1_STA: USB bus is SE1 state now.
 * @exception  No
 * @note 
 *******************************************************************************
 */
#define __DRV_USB_GETBUS_STATUS()              (USB_READ_BIT( USB->STA2.B[0] , (USB_STA2_K_STA_mask_b0 | USB_STA2_J_STA_mask_b0 | USB_STA2_SE1_STA_mask_b0 | USB_STA2_SE0_STA_mask_b0 | USB_STA2_DMI_STA_mask_b0 | USB_STA2_DPI_STA_mask_b0)))
    #define USB_BUS_K_STA                          (USB_STA2_K_STA_mask_b0   | USB_STA2_DMI_STA_mask_b0)
    #define USB_BUS_J_STA                          (USB_STA2_J_STA_mask_b0   | USB_STA2_DPI_STA_mask_b0 )
    #define USB_BUS_SE0_STA                        (USB_STA2_SE0_STA_mask_b0 )
    #define USB_BUS_SE1_STA                        (USB_STA2_SE1_STA_mask_b0 | USB_STA2_DPI_STA_mask_b0 | USB_STA2_DMI_STA_mask_b0 )

 /**
 *******************************************************************************
 * @brief	   Get USB Frame Number.
 * @details 
 * @return     USB frame number. (11-bit)
 * @exception  No
 * @note 
 *******************************************************************************
 */
#define __DRV_USB_GETFRAMENUMBER()             (USB_READ_BIT( USB->STA2.H[1], USB_STA2_FNUM_mask_h1))



///@} 

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

/**
 * @name USB function declare.
 *             
 */ 

///@{

//======================================================
// USB Transceiver Relationship Control.

void USB_Function_Cmd(FunctionalState  USB_REG_EN);

void USB_Transceiver_Cmd(FunctionalState USB_XCVR_EN);
void USB_DriveStrength_Select( USB_OUTDrive_Typedef USB_OCD);
void USB_PDResistorMode_Select(USB_PDResistorMode_TypeDef USB_PD_TYPE);
void USB_PUResistorMode_Select( USB_PUResistorMode_TypeDef  PUR_MODE);

void USB_V33_Cmd(FunctionalState V33_EN);
void USB_V33toVDD_Cmd(FunctionalState V33_to_VDD_EN);
void USB_LVRModeInSTOP_Select( USB_STOPMode_TypeDef  USB_STOP_MODE);

void USB_Cmd(FunctionalState USB_EN);                                          /*!< The function include V33 , Transceiver and function enable / disable.*/

//======================================================
// USB Bus Relationship Control.

uint8_t USB_GetBusStatus(void);
DRV_Return USB_GetBusEventStatus2(USB_BusEventState_TypeDef USB_EVENT);
uint8_t USB_GetDPDMStatus(void);

void USB_Connect_Cmd(FunctionalState USB_PUR_CMD);
void USB_SetAddress(uint8_t USB_ADR);

void USB_SetRemoteWakeupTime( USB_RemoteWakeupTime_TypeDef USB_RWK_DSEL);
void USB_TriggerRemoteWakeup(void);
void USB_SoftwareControlRemoteWakeup_Cmd( FunctionalState RWK_SW_EN);    
void USB_SetRemoteWakeup_SW( BitAction RWK_SW);

void USB_SuspendSignalMode_Select( USB_SUSMDS_TypeDef USB_SUS_MODE);
void USB_NoResponse_Cmd( FunctionalState NORS_EN);
uint16_t USB_GetFrameNumber(void);

//======================================================
// USB Endpoint Relationship Control.

void USB_ClearSETUPStatus(uint8_t SETUP_STATUS);

void USB_SetEndpointStatus( USB_EP_Struct * EPX , USB_EPStatus_TypeDef EP_STATUS);
void USB_SetDoubleBufferEndpointStatus( USB_EP_Struct * EPX , USB_EPDBStatus_TypeDef EPDB_STATUS);
uint16_t USB_GetEndpointStatus( USB_EP_Struct* EPX) ;

void USB_SetEndpointOUTSequenceBit( USB_EP_Struct* EPX , uint8_t RXSEQ);
void USB_SetEndpointINSequenceBit( USB_EP_Struct* EPX , uint8_t TXSEQ);
uint8_t USB_GetEndpointOUTSequenceBit( USB_EP_Struct* EPX);
uint8_t USB_GetEndpointINSequenceBit( USB_EP_Struct* EPX);

void USB_SetEndpointAddress( USB_EP_Struct  *EPX , uint8_t EPX_ID);

uint16_t USB_GetEndpointFlagStatus( USB_EP_Struct* EPX);
uint32_t USB_GetEndpointITFlagStatus( USB_EP_Struct* EPX);
void USB_ClearEndpointFlag( USB_EP_Struct* EPX , uint16_t EPX_CLR_FLAG);
void USB_EndpintIT_Config( USB_EP_Struct* EPX , uint8_t EP_IT_TYPE , FunctionalState  EPX_IT_EN);

uint8_t USB_GetSETUPStatus(void);
void USB_ClearSetupflag(void);

void USB_EndpointMode_Select(USB_EP_Struct* EPX , USB_EPMode_TypeDef EP_TYPE);
void USB_EndpointDoubleBufferMode_Cmd( USB_EP_Struct* EPX , FunctionalState USB_EP_DBMEN);
void USB_TriggerEndpointRst( USB_EP_Struct* EPX , USB_EPRST_TypeDef EP_RSTYPE);

uint16_t USB_GetEndpointRXSize(USB_EP_Struct* EPX);
void USB_SetEndpointRXBlock(USB_EP_Struct* EPX , uint32_t EP_BLSIZE);

void USB_SetEndpointTXSize(USB_EP_Struct* EPX , uint16_t EP_TXCNT);
void USB_SetEndpointTXDataAddress(USB_EP_Struct* EPX , uint16_t EPTXDATA_ADR);
void USB_SetEndpointRXDataAddress(USB_EP_Struct* EPX , uint16_t EPRXDATA_ADR);
uint16_t USB_GetEndpointTXDataAddress(USB_EP_Struct* EPX);
uint16_t USB_GetEndpointRXDataAddress(USB_EP_Struct* EPX);
uint32_t USB_GetEndpointRXData( USB_EP_Struct* EPX, uint8_t *Buffer, FunctionalState Release_RXMemory );
void USB_SetEndpointTXData( USB_EP_Struct* EPX, __I uint8_t *Buffer , uint32_t Cnt );

//-----------------------------------------------------
//Double Buffer
void USB_SetEndpointDoubleBuffer1TXSize(USB_EP_Struct* EPX , uint16_t EPDBUF1_TXCNT);
void USB_SetEndpointDoubleBuffer0TXSize(USB_EP_Struct* EPX , uint16_t EPDBUF0_TXCNT);
void USB_SetEndpointDoubleBuffer0Address( USB_EP_Struct* EPX, uint16_t EPDB_BUF0_ADR);
void USB_SetEndpointDoubleBuffer1Address( USB_EP_Struct* EPX, uint16_t EPDB_BUF1_ADR);
uint16_t USB_GetEndpointDoubleBuffer0Address( USB_EP_Struct* EPX);
uint16_t USB_GetEndpointDoubleBuffer1Address( USB_EP_Struct* EPX);
uint32_t USB_GetEndpointDoubleBufferRXData( USB_EP_Struct* EPX, uint8_t *Buffer);
DRV_Return USB_SetEndpointDoubleBufferTXData( USB_EP_Struct* EPX, uint8_t *Buffer , uint32_t Cnt );



//======================================================
// USB Interrupt Relationship Control.

void USB_ITEA_Cmd(FunctionalState USB_ITEA_State);
void USB_IT_Config( uint32_t  USB_IT , FunctionalState USB_IT_State);
uint32_t USB_GetITAllFlagStatus(void);
uint32_t USB_GetITIEAllStatus(void);
void USB_ClearITFlag(uint32_t USB_ITFlag);

//======================================================
// USB LPM Relationship Control.

void USB_LPMhandshakeMode_Select( USB_LPMHandShake_TypeDef LPM_STATE);
uint8_t USB_GetLPMBESL(void);
uint8_t USB_GetLPMbRemoteWake(void);

//======================================================
// USB DMA Relationship Control.

void USB_DMARXSEL_Config( uint8_t USB_DMARXSEL_NUM , USB_DMARXSEL_TypeDef USB_DMARXSEL_TYPE);
void USB_DMATXSEL_Config( uint8_t USB_DMATXSEL_NUM , USB_DMATXSEL_TypeDef USB_DMATXSEL_TYPE);



///@}


#ifdef __cplusplus
}
#endif // __cplusplus


#endif










