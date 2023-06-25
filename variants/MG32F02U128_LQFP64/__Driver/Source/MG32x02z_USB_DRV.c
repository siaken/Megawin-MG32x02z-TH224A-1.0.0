

 /**
 ******************************************************************************
 *
 * @file        MG32x02z_USB_DRV.c
 * @brief       The demo code USB middleware C file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.02
 * @date        2022/07/20
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

/* Includes ------------------------------------------------------------------*/
#include "MG32x02z_USB_DRV.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void USB_SetEndpointBlockOf2Byte(USB_EP_Struct* EPX , uint8_t EP_BLSIZE);
static void USB_SetEndpointBlockOf32Byte(USB_EP_Struct* EPX , uint32_t EP_BLSIZE);


/* Exported functions --------------------------------------------------------*/


/**
 * @name   USB Transceiver Relationship Control
 *             
 */ 
///@{

 /**
 *******************************************************************************
 * @brief	    USB transceiver control
 * @details     
 * @param[in]   USB_XCVR_EN:
 *  @arg\b      DISABLE: Disable USB transceiver.
 *  @arg\b      ENABLE : Enable USB transceiver.
 * @return      
 * @exception   No
 * @note        
 * @par         Example
 * @code
       USB_Transceiver_Cmd( ENABLE)                // Enable USB transceiver.
 * @endcode
 *******************************************************************************
 */
void USB_Transceiver_Cmd(FunctionalState USB_XCVR_EN)
{
    USB_MODIFY_REG(USB->CR0.B[0] , USB_CR0_XTR_EN_mask_b0 , ( USB_CR0_XTR_EN_mask_b0 * USB_XCVR_EN));
}
 /**
 *******************************************************************************
 * @brief	    USB internal V33 LDO control.
 * @details     
 * @param[in]   V33_EN
 *  @arg\b      DISABLE: The V33 LDO output is disabled.
 *  @arg\b      ENABLE : The V33 LDO output is enabled.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
       USB_V33_Cmd( ENABLE)                         // Enable the V33 LDO output.
 * @endcode
 *******************************************************************************
 */
void USB_V33_Cmd(FunctionalState V33_EN)
{
    USB_MODIFY_REG(USB->CR0.B[0] , USB_CR0_V33_EN_mask_b0 , (USB_CR0_V33_EN_mask_b0 * V33_EN));
}

 /**
 *******************************************************************************
 * @brief	   USB V33 LDO output short to VDD Control.
 * @details    
 * @param[in]  V33_to_VDD_EN 
 *  @arg\b     DISABLE: The V33 LDO output will be not short to VDD power.
 *  @arg\b     ENABLE : The V33 LDO output will be short to VDD power.
 * @return      
 * @exception  NO 
 * @note 
 * @par        Example
 * @code
       USB_V33toVDD_Cmd( DISABLE)                  // The VDD and V33 no short.
 * @endcode
 *******************************************************************************
 */
void USB_V33toVDD_Cmd(FunctionalState V33_to_VDD_EN)
{
    USB_MODIFY_REG(USB->CR0.B[0] , USB_CR0_V33_VDD_mask_b0 , (V33_to_VDD_EN * USB_CR0_V33_VDD_mask_b0));
}

 /**
 *******************************************************************************
 * @brief	   USB function enable / disable bit.
 * @details    
 * @param[in]  USB_REG_EN
 *  @arg\b     DISABLE : USB function disable.
 *  @arg\b     ENABLE  : USB function enable.
 * @return     
 * @exception  No
 * @note 
 * @par        Example
 * @code
       USB_Function_Cmd( ENABLE);                     // USB function enable.
 * @endcode
 *******************************************************************************
 */
void USB_Function_Cmd(FunctionalState  USB_REG_EN)
{
    USB_MODIFY_REG(USB->CR0.B[0] , USB_CR0_EN_mask_b0 , (USB_CR0_EN_mask_b0 * USB_REG_EN));
}
 /**
 *******************************************************************************
 * @brief	    USB transceiver / V33 / function enable / Disable.
 * @details     
 * @param[in]   USB_EN
 *  @arg\b      DISABLE : Disable USB transceiver , V33 and USB funciton.
 *  @arg\b      ENABLE  : Enable USB transceiver , V33 and USB function.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
       USB_Cmd( ENABLE);                             // Enable USB transceiver , V33 and USB function.
 * @endcode
 *******************************************************************************
 */
void USB_Cmd(FunctionalState USB_EN)
{
    USB_MODIFY_REG(USB->CR0.B[0] , (USB_CR0_EN_mask_b0 | USB_CR0_XTR_EN_mask_b0 | USB_CR0_V33_EN_mask_b0) ,
                  ((USB_CR0_EN_mask_b0 | USB_CR0_XTR_EN_mask_b0 | USB_CR0_V33_EN_mask_b0) * USB_EN));
}

/**
 *******************************************************************************
 * @brief	    USB DP/DM output drive strength select.
 * @details     
 * @param[in]   USB_OCD
 *  @arg\b      USBOCD_DPLVL0_DMLVL0 : DP strength is normal       / DM strength is normal .
 *  @arg\b      USBOCD_DPLVL0_DMLVL1 : DP strength is normal       / DM strength is normal * 1.1.
 *  @arg\b      USBOCD_DPLVL1_DMLVL0 : DP strength is normal * 1.1 / DM strength is normal.
 *  @arg\b      USBOCD_DPLVL1_DMLVL1 : DP strength is normal * 1.1 / DM strength is normal * 1.1.
 * @return      
 * @exception   No
 * @note        
 * @par         Example
 * @code
       USB_DriveStrength_Select(USBOCD_DPLVL0_DMLVL0);    // DP and DM strength is Normal.
 * @endcode
 *******************************************************************************
 */
void USB_DriveStrength_Select( USB_OUTDrive_Typedef USB_OCD)
{
    USB_MODIFY_REG(USB->CR0.B[2] , (USB_CR0_DP_ODC_mask_b2 | USB_CR0_DM_ODC_mask_b2) , USB_OCD);
}

/**
 *******************************************************************************
 * @brief	    USB DP / DM internal pull-low resistance control.
 * @details     In normal no use the function.
 * @param[in]   USB_PD_TYPE:
 *  @arg\b      USB_DP_DIS_DM_DIS : DP pull-low resistance disable /DM pull-low resistance disable. 
 *  @arg\b      USB_DP_DIS_DM_PD  : DP pull-low resistance disable /DM pull-low resistance enable. 
 *  @arg\b      USB_DP_PD_DM_DIS  : DP pull-low resistance enable  /DM pull-low resistance disable.
 *  @arg\b      USB_DP_PD_DM_PD   : DP pull-low resistance enable  /DM pull-low resistance enable. 
 * @return      
 * @exception   No
 * @note        
 * @par         Example
 * @code
       USB_PDResistorMode_Select(USB_DP_DIS_DM_DIS);       // DP and DM pull-low resistance disable.
 * @endcode
 *******************************************************************************
 */
void USB_PDResistorMode_Select(USB_PDResistorMode_TypeDef USB_PD_TYPE)
{
    USB_MODIFY_REG(USB->CR0.B[2] , (USB_CR0_DP_PD_mask_b2 | USB_CR0_DM_PD_mask_b2 | USB_CR0_DM_PD2_mask_b2), USB_PD_TYPE);
}

/**
 *******************************************************************************
 * @brief	    USB DP pull-high resistance mode select.
 * @details     
 * @param[in]   PUR_MODE:
 *  @arg\b      USBPUR_FIX_NO_AUTO   :  
 *      \n                              1. DP pull up resister always enable.
 *      \n                              2. Value of pull-up resister is always 1.2K ohm.
 *  @arg\b      USBPUR_FIX_AUTO      :  
 *      \n                              1. DP pull up resister auto disable in output low. 
 *      \n                              2. Value of pull-up resister is always 1.2K ohm.
 *  @arg\b      USBPUR_SWITCH_NO_AUTO:  
 *      \n                              1. DP pull up resister always enable.
 *      \n                              2. Value of pull-up resister is different between ( SE0 , J State (1.2Kohm) ) and K state (2.4 kohm).
 *  @arg\b      USBPUR_SWITCH_AUTO   : 
 *      \n                              1. DP pull up resister auto disable in output low. 
 *      \n                              2. Value of pull-up resister is different between ( SE0 , J State (1.2Kohm) ) and K state (2.4 kohm).
 * @return      
 * @exception   No
 * @note        
 * @par         Example
 * @code
       USB_PUResistorMode_Select(USBPUR_FIX_NO_AUTO);               // 1. DP pull up resister always enable and Value of pull-up resister is always 1.2K ohm.
 * @endcode
 *******************************************************************************
 */
void USB_PUResistorMode_Select( USB_PUResistorMode_TypeDef  PUR_MODE)
{
    USB_MODIFY_REG( USB->CR0.B[2] , (USB_CR0_DPU_AUTO_mask_b2 | USB_CR0_DPU_MDS_mask_b2) , PUR_MODE);
}

/**
 *******************************************************************************
 * @brief	    When USB enable and enter STOP mode LVR status select.
 * @details     
 * @param[in]   USB_STOP_MODE
 *  @arg\b      USB_STOP_LVR_DISABLE: LVR disable when USB enable and enter STOP mode.
 *  @arg\b      USB_STOP_LVR_ENABLE : LVR enable when USB enable and enter STOP mode.
 * @return      
 * @exception   No
 * @note        
 * @par         Example
 * @code
       USB_LVRModeInSTOP_Select(USB_STOP_LVR_DISABLE);              // LVR disable when USB enable and enter STOP mode.
 * @endcode
 *******************************************************************************
 */
void USB_LVRModeInSTOP_Select( USB_STOPMode_TypeDef  USB_STOP_MODE)
{
    USB_MODIFY_REG( USB->CR0.B[1] , USB_CR0_STP_LVR_mask_b1 , USB_STOP_MODE);
    
}

///@}


/**
 * @name   USB Bus Relationship Control
 *             
 */ 
///@{

/**
 *******************************************************************************
 * @brief	    Read USB bus status now.
 * @details          
 * @return      USB Bus status information.
 *     \n       Bit 7 : USB Bus K state.
 *     \n       Bit 6 : USB Bus J state.
 *     \n       Bit 5 : USB Bus SE1 state.
 *     \n       Bit 4 : USB Bus SE0 state.
 *     \n       Bit 3 : DP status.
 *     \n       Bit 2 : DM status.
 *     \n       Bit 0 : USB different input status ( internal signal).
 * @exception   No
 * @note        
 *******************************************************************************
 */
uint8_t USB_GetBusStatus(void)
{
    return(USB_READ_REG(USB->STA2.B[0]));
}

/**
 *******************************************************************************
 * @brief	    To read some usb bus state whether happen or not. 
 * @details     
 * @param[in]   USB_EVENT
 *  @arg\b      USB_BUS_K_STA  : USB bus K state.
 *  @arg\b      USB_BUS_J_STA  : USB bus J state.
 *  @arg\b      USB_BUS_SE1_STA: USB bus SE1 state.
 *  @arg\b      USB_BUS_SE0_STA: USB bus SE0 state.
 *  @arg\b      USB_BUS_DM_STA : USB DM H status.
 *  @arg\b      USB_BUS_DP_STA : USB DP H status.
 *  @arg\b      USB_BUS_DI_STA : USB bus different input status H. 
 * @return      
 * @exception   No
 * @note        
 * @par         Example
 * @code
        USB_GetBusEventStatus2(USB_BUS_K_STA);         // Read USB Bus whether K state or not.
 * @endcode
 *******************************************************************************
 */
DRV_Return USB_GetBusEventStatus2(USB_BusEventState_TypeDef USB_EVENT)
{
    if((USB->STA2.B[0] & USB_EVENT)==0)
    {
        return(DRV_UnHappened);
    }
    else
    {
        return(DRV_Happened);
    }
}
/**
 *******************************************************************************
 * @brief	    Read USB DP and DM status at the same time.
 * @details     
 * @return      [ DM : DP ] status.
 *       \n     0 :  DP = L , DM = L
 *       \n     1 :  DP = H , DM = L
 *       \n     2 :  DP = L , DM = H
 *       \n     3 :  DP = H , DM = H
 * @exception   
 * @note        
 *******************************************************************************
 */
uint8_t USB_GetDPDMStatus(void)
{
    return( ( USB_READ_REG(USB->STA2.B[0]) & (USB_STA2_DMI_STA_mask_b0 | USB_STA2_DPI_STA_mask_b0)) >> USB_STA2_DPI_STA_shift_b0);
    
}

/**
 *******************************************************************************
 * @brief	   USB DP pull-up resistance whether enable or not.
 * @details     
 * @param[in]   USB_PUR_CMD 
 *  @arg\b      DISABLE : Disable USB DP pull-up resistance.
 *  @arg\b      ENABLE  : Enable USB DM pull-up resistance.
 * @return      
 * @exception   No
 * @note        
 * @par         Example
 * @code
       USB_Connect_Cmd( ENABLE);                   // USB connect.
 * @endcode
 *******************************************************************************
 */
void USB_Connect_Cmd(FunctionalState USB_PUR_CMD)
{
    USB_MODIFY_REG( USB->CR0.B[2] , USB_CR0_DPU_EN_mask_b2 , (USB_CR0_DPU_EN_enable_b2 * USB_PUR_CMD));
}

/**
 *******************************************************************************
 * @brief	    Set the USB device addresss
 * @details     
 * @param[in]   USB_ADR = 1 ~ 127.
 * @return      
 * @exception   No
 * @note        
 * @par         Example
 * @code
       USB_SetAddress(48);                          // The USB device address is 48.
 * @endcode
 *******************************************************************************
 */
void USB_SetAddress(uint8_t USB_ADR)
{
    USB_WRITE_REG(USB->CR1.B[0] , USB_ADR);
}

/**
 *******************************************************************************
 * @brief	   Set USB remote wakeup signal timing.
 * @details     
 * @param[in]  USB_RWK_DSEL 
 *  @arg\b     USB_RemoteWakeup_6ms  : 6   ms
 *  @arg\b     USB_RemoteWakeup_3ms  : 3   ms
 *  @arg\b     USB_RemoteWakeup_110us: 110 us
 *  @arg\b     USB_RemoteWakeup_55us : 55  us
 * @return      
 * @exception  No
 * @note        
 * @par        Example
 * @code
       USB_SetRemoteWakeupTime();
 * @endcode
 *******************************************************************************
 */
void USB_SetRemoteWakeupTime( USB_RemoteWakeupTime_TypeDef USB_RWK_DSEL)
{
    USB_MODIFY_REG( USB->CR0.B[0] , USB_CR0_RWK_DSEL_mask_b0 , USB_RWK_DSEL);
}

/**
 *******************************************************************************
 * @brief	   Trigger hardware to send remote wakeup signal.
 * @details        
 * @exception  No
 * @note        
 *******************************************************************************
 */
void USB_TriggerRemoteWakeup(void)
{
    USB_MODIFY_REG(USB->CR0.B[1] , (USB_CR0_RWK_MDS_mask_b1 | USB_CR0_RWK_TRG_mask_b1) , (USB_CR0_RWK_MDS_hardware_b1 | USB_CR0_RWK_TRG_start_b1));
}

/**
 *******************************************************************************
 * @brief	   Use software to control remote wakeup enable or disable.
 * @details     
 * @param[in]  RWK_SW_EN
 *  @arg\b     DISABLE:Disable software control remote wakeup signal.
 *  @arg\b     ENABLE: Enable software control remote wakeup signal.      
 * @return      
 * @exception  No 
 * @note        
 * @par        Example
 * @code
       USB_SoftwareControlRemoteWakeup_Cmd( ENABLE);                      // Enable software control remote wakeup signal.
 * @endcode
 *******************************************************************************
 */
void USB_SoftwareControlRemoteWakeup_Cmd( FunctionalState RWK_SW_EN)
{
    USB_MODIFY_REG( USB->CR0.B[1] , USB_CR0_RWK_MDS_mask_b1 , ( RWK_SW_EN * USB_CR0_RWK_MDS_software_b1));
}

/**
 *******************************************************************************
 * @brief	    Software control remote wakeup.
 * @details     
 * @param[in]   RWK_SW
 *  @arg\b      SET   : Start remote wakeup.
 *  @arg\b      CLR   : Stop remote wakeup.   
 * @return      
 * @exception   No
 * @note        
 * @par         Example
 * @code
       USB_SetRemoteWakeup_SW( SET )                                      // Remote wakeup start.

       // Delay 6ms

       USB_SetRemoteWakeup_SW( CLR )                                      // Remote wakeup stop.

 * @endcode
 *******************************************************************************
 */
void USB_SetRemoteWakeup_SW( BitAction RWK_SW)
{                             
    USB_MODIFY_REG( USB->CR0.B[1] , USB_CR0_RWK_TRG_mask_b1 , (USB_CR0_RWK_TRG_start_b1 * RWK_SW) );
}

/**
 *******************************************************************************
 * @brief	    USB suspend signal detect mode select.
 * @details     
 * @param[in]   USB_SUS_MODE
 *  @arg\b      USB_SUS_JSTATE        : Detect J state.
 *  @arg\b      USB_SUS_J_OR_SE1STATE : Detect J state or SE1 state.
 * @return      
 * @exception   No
 * @note        
 * @par         Example
 * @code
       USB_SuspendSignalMode_Select( USB_SUS_JSTATE);                      
 * @endcode
 *******************************************************************************
 */
void USB_SuspendSignalMode_Select( USB_SUSMDS_TypeDef USB_SUS_MODE)
{
    USB_MODIFY_REG( USB->CR0.B[0] , USB_CR0_SUS_MDS_mask_b0 , USB_SUS_MODE);
}

/**
 *******************************************************************************
 * @brief	    USB no responese for endpoint 0 IN / OUT enable.
 * @details     
 * @param[in]   NORS_EN 
 *  @arg\b      DISABLE : USB will send ACK/NAK/STALL packet in IN / OUT transaction.
 *  @arg\b      ENABLE  : USB will not send ACK / NAK / STALL packet in IN / OUT transaction.    
 * @return      
 * @exception   No
 * @note        
 * @par         Example
 * @code
       USB_NoResponse_Cmd(ENABLE);                            // USB will not send ACK / NAK / STALL packet in IN / OUT transaction. 
 * @endcode
 *******************************************************************************
 */
void USB_NoResponse_Cmd( FunctionalState NORS_EN)
{
    USB_MODIFY_REG( USB->CR0.B[1] , USB_CR0_NORS_EN_mask_b1 , (USB_CR0_NORS_EN_enable_b1 * NORS_EN));

}
/**
 *******************************************************************************
 * @brief	   Get USB frame number.
 * @details           
 * @return     Now USB frame number.
 * @exception   
 * @note        
 *******************************************************************************
 */
uint16_t USB_GetFrameNumber(void)
{
    return( USB_READ_REG(USB->STA2.H[1]));
}

///@}


/**
 * @name   USB Endpoint Relationship Control
 *             
 */ 
///@{
 /**
 *******************************************************************************
 * @brief	   Set the endpoint register RX / TX status in normal mode.
 * @details     
 * @param[in]  EPX
 *      \n     ( USB_EP0 ~ USB_EP7)     : Select control which endpoint register.
 * @param[in]  EP_STATUS:
 *  @arg\b     EP_RX_DISABLE            : The endpoint RX function disable. 
 *  @arg\b     EP_RX_DISABLE_TX_DISABLE : The endpoint RX / TX function disable
 *  @arg\b     EP_RX_DISABLE_TX_NAK     : The endpoint RX function disable and sending NAK in following IN transfers.
 *  @arg\b     EP_RX_DISABLE_TX_STALL   : The endpoint RX function disable and sending STALL in following IN transfers.
 *  @arg\b     EP_RX_DISABLE_TX_VALID   : The endpoint RX function disable and sending DATA in next IN transfer.
 *  @arg\b     EP_RX_NAK                : The endpoint will sending NAK in following OUT transfers.
 *  @arg\b     EP_RX_NAK_TX_DISABLE     : The endpoint will sending NAK in following OUT transfers and TX function disable.
 *  @arg\b     EP_RX_NAK_TX_NAK         : The endpoint will sending NAK in following OUT / IN transfers 
 *  @arg\b     EP_RX_NAK_TX_STALL       : The endpoint will sending NAK in following OUT transfers and sending STALL in following IN transfers.
 *  @arg\b     EP_RX_NAK_TX_VALID       : The endpoint will sending NAK in following OUT transfers and sending DATA in next IN transfer.
 *  @arg\b     EP_RX_STALL              : The endpoint will sending STALL in following OUT transfers.
 *  @arg\b     EP_RX_STALL_TX_DISABLE   : The endpoint will sending STALL in following OUT transfers and TX function disable.
 *  @arg\b     EP_RX_STALL_TX_NAK       : The endpoint will sending STALL in following OUT transfers and sending NAK in following IN transfers.
 *  @arg\b     EP_RX_STALL_TX_STALL     : The endpoint will sending STALL in following OUT / IN transfers.
 *  @arg\b     EP_RX_STALL_TX_VALID     : The endpoint will sending STALL in following OUT transfers and sending DATA in next IN transfer.
 *  @arg\b     EP_RX_VALID              : The endpoint will sending ACK / receiving data in next OUT transfer.
 *  @arg\b     EP_RX_VALID_TX_DISABLE   : The endpoint will sending ACK / receiving data in next OUT transfer and TX function disable.
 *  @arg\b     EP_RX_VALID_TX_NAK       : The endpoint will sending ACK / receiving data in next OUT transfer and sending NAK in following IN transfers.
 *  @arg\b     EP_RX_VALID_TX_STALL     : The endpoint will sending ACK / receiving data in next OUT transfer and sending STALL in following IN transfers.
 *  @arg\b     EP_RX_VALID_TX_VALID     : The endpoint will sending ACK / receiving data in next OUT transfer and sending DATA in next IN transfer.
 *  @arg\b     EP_TX_DISABLE            : The endpoint TX function disable.
 *  @arg\b     EP_TX_NAK                : The endpoint will sending NAK in following IN transfers.
 *  @arg\b     EP_TX_STALL              : The endpoint will sending STALL in following IN transfers.
 *  @arg\b     EP_TX_VALID              : The endpoint will sending DATA in next IN transfer.
 * @return      
 * @exception  No 
 * @note       
 * @par        Example
 * @code
       USB_SetEndpointStatus( USB_EP1 , EP_RX_STALL);          // USB_EP1 send STALL in following OUT transaction.
       
       USB_SetEndpointStatus( USB_EP1 , EP_TX_STALL);          // USB_EP1 send STALL in following IN / OUT transaction.
       
 * @endcode
 *******************************************************************************
 */
void USB_SetEndpointStatus( USB_EP_Struct * EPX , USB_EPStatus_TypeDef EP_STATUS)
{
    USB_WRITE_REG(EPX->CR1.H[1] , EP_STATUS);
}

 /**
 *******************************************************************************
 * @brief	   Get endpoint register setting of status.
 * @details      
 * @param[in]  EPX
 *      \n     ( USB_EP0 ~ USB_EP7)     : Select control which endpoint register.
 * @return     The return value is :
 *    \n       EP_RX_DISABLE            : The endpoint RX function disable. 
 *    \n       EP_RX_DISABLE_TX_DISABLE : The endpoint RX / TX function disable
 *    \n       EP_RX_DISABLE_TX_NAK     : The endpoint RX function disable and sending NAK in following IN transfers.
 *    \n       EP_RX_DISABLE_TX_STALL   : The endpoint RX function disable and sending STALL in following IN transfers.
 *    \n       EP_RX_DISABLE_TX_VALID   : The endpoint RX function disable and sending DATA in next IN transfer.
 *    \n       EP_RX_NAK                : The endpoint will sending NAK in following OUT transfers.
 *    \n       EP_RX_NAK_TX_DISABLE     : The endpoint will sending NAK in following OUT transfers and TX function disable.
 *    \n       EP_RX_NAK_TX_NAK         : The endpoint will sending NAK in following OUT / IN transfers 
 *    \n       EP_RX_NAK_TX_STALL       : The endpoint will sending NAK in following OUT transfers and sending STALL in following IN transfers.
 *    \n       EP_RX_NAK_TX_VALID       : The endpoint will sending NAK in following OUT transfers and sending DATA in next IN transfer.
 *    \n       EP_RX_STALL              : The endpoint will sending STALL in following OUT transfers.
 *    \n       EP_RX_STALL_TX_DISABLE   : The endpoint will sending STALL in following OUT transfers and TX function disable.
 *    \n       EP_RX_STALL_TX_NAK       : The endpoint will sending STALL in following OUT transfers and sending NAK in following IN transfers.
 *    \n       EP_RX_STALL_TX_STALL     : The endpoint will sending STALL in following OUT / IN transfers.
 *    \n       EP_RX_STALL_TX_VALID     : The endpoint will sending STALL in following OUT transfers and sending DATA in next IN transfer.
 *    \n       EP_RX_VALID              : The endpoint will sending ACK / receiving data in next OUT transfer.
 *    \n       EP_RX_VALID_TX_DISABLE   : The endpoint will sending ACK / receiving data in next OUT transfer and TX function disable.
 *    \n       EP_RX_VALID_TX_NAK       : The endpoint will sending ACK / receiving data in next OUT transfer and sending NAK in following IN transfers.
 *    \n       EP_RX_VALID_TX_STALL     : The endpoint will sending ACK / receiving data in next OUT transfer and sending STALL in following IN transfers.
 *    \n       EP_RX_VALID_TX_VALID     : The endpoint will sending ACK / receiving data in next OUT transfer and sending DATA in next IN transfer.
 *    \n       EP_TX_DISABLE            : The endpoint TX function disable.
 *    \n       EP_TX_NAK                : The endpoint will sending NAK in following IN transfers.
 *    \n       EP_TX_STALL              : The endpoint will sending STALL in following IN transfers.
 *    \n       EP_TX_VALID              : The endpoint will sending DATA in next IN transfer.
 * @exception   
 * @note 
 * @par        Example
 * @code
       if(USB_GetEndpointStatus( USB_EP1) == ( USB_EP_TXNAK_MASK | USB_EP_RXNAK_MASK))      //Judge USB_EP1 RX / TX status whether NAK status or not. 
       {
           // To do......
       }
 * @endcode
 *******************************************************************************
 */
uint16_t USB_GetEndpointStatus( USB_EP_Struct* EPX) 
{
    return(USB_READ_BIT(EPX->CR1.H[1] , (USB_EP_TXSTATUS_MASK | USB_EP_RXSTATUS_MASK)));
}

 /**
 *******************************************************************************
 * @brief	   Set the endpoint register RX / TX status in double buffer mode.
 * @details  
 * @param[in]  EPX
 *      \n     ( USB_EP0 ~ USB_EP7)     : Select control which endpoint register.
 * @param[in]  EPDB_STATUS 
 *   @arg\b    EP_DB_DISABLE        :  Double buffer mode status change to TX / RX disable.
 *   @arg\b    EP_DB_RX_STALL       :  Double buffer mode status change to RX STALL.
 *   @arg\b    EP_DB_TX_STALL       :  Double buffer mode status change to TX STALL.
 *   @arg\b    EP_DB_RXBUFALL_NAK   :  All buffer status of double buffer mode is keeping in RX NAK.
 *   @arg\b    EP_DB_RXBUF0_NAK     :  Buffer0 status of double buffer mode is keeping in RX NAK.
 *   @arg\b    EP_DB_RXBUF1_NAK     :  Buffer1 status of double buffer mode is keeping in RX NAK.
 *   @arg\b    EP_DB_TXBUFALL_NAK   :  All buffer status of double buffer mode is keep in TX NAK.
 *   @arg\b    EP_DB_TXBUF0_NAK     :  Buffer0 status of double buffer mode is keep in TX NAK.
 *   @arg\b    EP_DB_TXBUF1_NAK     :  Buffer1 status of double buffer mode is keep in TX NAK.
 *   @arg\b    EP_DB_RXBUFALL_VALID :  All buffer status of double buffer mode change to ready receive new data .
 *   @arg\b    EP_DB_RXBUF0_VALID   :  Buffer0 status of double buffer mode change to ready receive new data .
 *   @arg\b    EP_DB_RXBUF1_VALID   :  Buffer1 status of double buffer mode change to ready receive new data .
 *   @arg\b    EP_DB_TXBUFALL_VALID :  All buffer status of double buffer mode change to ready send data.
 *   @arg\b    EP_DB_TXBUF0_VALID   :  Buffer0 status of double buffer mode change to ready send data.
 *   @arg\b    EP_DB_TXBUF1_VALID   :  Buffer1 status of double buffer mode change to ready send data.
 * @return      
 * @exception   
 * @note 
 * @par         Example
 *******************************************************************************
 */
void USB_SetDoubleBufferEndpointStatus( USB_EP_Struct * EPX , USB_EPDBStatus_TypeDef EPDB_STATUS)
{
    USB_WRITE_REG(EPX->CR1.H[1] , EPDB_STATUS);   
}

 /**
 *******************************************************************************
 * @brief	   Set the USB receive sequence number of the endpoint register.
 * @details 
 * @param[in]  EPX
 *      \n     ( USB_EP0 ~ USB_EP7)     : Select control which endpoint register.
 * @param[in]  RXSEQ : ( 0 or 1)        : Set sequence number of next OUT transaction.  
 * @return      
 * @exception  No
 * @note 
 * @par        Example
 * @code
       USB_SetEndpointOUTSequenceBit( USB_EP1 , 0);           // Set sequence number of next OUT transaction = 0
 * @endcode
 *******************************************************************************
 */
void USB_SetEndpointOUTSequenceBit( USB_EP_Struct* EPX , uint8_t RXSEQ)
{
    USB_WRITE_REG(EPX->CR1.B[2], ((RXSEQ * USB_EP0CR1_RXSEQ0_mask_b2) | USB_EP1CR1_RXS_LCK1_mask_b2));
}

 /**
 *******************************************************************************
 * @brief	   Set the USB transmit sequence number of the endpoint register.
 * @details     
 * @param[in]  EPX
 *      \n     ( USB_EP0 ~ USB_EP7)     : Select control which endpoint register.
 * @param[in]  TXSEQ : ( 0 or 1)        : Set sequence number of next IN transaction.       
 * @return      
 * @exception  No
 * @note 
 * @par        Example
 * @code
       USB_SetEndpointINSequenceBit( USB_EP1 , 0);           // Set sequence number of next IN transaction = 0
 * @endcode
 *******************************************************************************
 */
void USB_SetEndpointINSequenceBit( USB_EP_Struct* EPX , uint8_t TXSEQ)
{
    USB_WRITE_REG(EPX->CR1.B[3], ((TXSEQ * USB_EP0CR1_TXSEQ0_mask_b3) | USB_EP1CR1_TXS_LCK1_mask_b3));
    
}
 /**
 *******************************************************************************
 * @brief	   Get the USB receive sequence number of the endpoint register.
 * @details     
 * @param[in]  EPX
 *      \n     ( USB_EP0 ~ USB_EP7)     : Select control which endpoint register.     
 * @return     Sequence number of next OUT transaction.
 * @exception  No
 * @note 
 *******************************************************************************
 */
uint8_t USB_GetEndpointOUTSequenceBit( USB_EP_Struct* EPX)
{
    return(((EPX->CR1.B[2] >> USB_EPRXSEQ_SHIFT_B2) & USB_EP0CR1_TXSEQ0_mask_b3));
}

 /**
 *******************************************************************************
 * @brief	   Get the USB transmit sequence number of the endpoint register.
 * @details     
 * @param[in]  EPX
 *      \n     ( USB_EP0 ~ USB_EP7)     : Select control which endpoint register.     
 * @return     Sequence number of next IN transaction.
 * @exception  No
 * @note 
 *******************************************************************************
 */
uint8_t USB_GetEndpointINSequenceBit( USB_EP_Struct* EPX)
{
    return(((EPX->CR1.B[3] >> USB_EPRXSEQ_SHIFT_B2) & USB_EP0CR1_RXSEQ0_mask_w));
}

 /**
 *******************************************************************************
 * @brief	   Set the endpoint number of the endpoint register.
 * @details   
 * @param[in]  EPX
 *      \n     ( USB_EP1 ~ USB_EP7)     : Select control which endpoint register. 
 * @param[in]  EPX_ID : ( 1 ~ 16)   
 * @return      
 * @exception  No
 * @note       USB_EP0 always service Endpoint 0.
 * @par        Example
 * @code
       USB_SetEndpointAddress( USB_EP1 , 7);                             // The USB_EP1 register service Endpoint 7.
 * @endcode
 *******************************************************************************
 */
void USB_SetEndpointAddress( USB_EP_Struct  *EPX , uint8_t EPX_ID)
{
    USB_MODIFY_REG(EPX->CR1.B[0] , USB_EP1CR1_EPADR1_mask_b0, EPX_ID);
}

 /**
 *******************************************************************************
 * @brief	   Get the endpoint register's relationship flag.
 * @details     
 * @param[in]  EPX
 *      \n     ( USB_EP0 ~ USB_EP7)     : Select control which endpoint register.      
 * @return     The return value is :
 *      \n     Bit 1  : USB_EP_FLAG_RXNAK           : The flag is the EPX send NAK   in OUT transfer. 
 *      \n     Bit 2  : USB_EP_FLAG_RXSTALL         : The flag is the EPX send STALL in OUT transfer.
 *      \n     Bit 3  : USB_EP_FLAG_RXISOOVW        : The flag is the EPX isochronous receive data overwrite error. (USB_EP0 no the flag)
 *      \n     Bit 10 : USB_EP_FLAG_TXNAK           : The flag is the EPX send NAK   in IN  transfer.
 *      \n     Bit 11 : USB_EP_FLAG_TXSTALL         : The flag is the EPX send STALL in IN  transfer.
 *      \n     Bit 12 : USB_EP_FLAG_ISOTXEF         : The flag is the EPX isochronous transmit data empty loss error. (USB_EP0 no the flag)
 *      \n     1. The EPX buffer mode is normal :
 *      \n         Bit 0: USB_EP_FLAG_RXDONE          : The flag is the EPX receive data done.
 *      \n         Bit 8: USB_EP_FLAG_TXDONE          : The flag is the EPX trasmission done.
 *      \n     2. The EPX buffer mode is RX double buffer mode : ( USB_EP0 no double buffer mode)
 *      \n         Bit 0: USB_EP_FLAG_DBUFFER0_RXDONE : The flag is the EPX receive data done and buffer0 is full in double buffer mode.
 *      \n         Bit 8: USB_EP_FLAG_DBUFFER1_RXDONE : The flag is the EPX receive data done and buffer1 is full in double buffer mode.
 *      \n     3. The EPX buffer mode is TX double buffer mode : ( USB_EP0 no double buffer mode)
 *      \n         Bit 0: USB_EP_FLAG_DBUFFER0_TXDONE : The flag is the EXP transmission done and buffer0 is empty in double buffer mode.
 *      \n         Bit 8: USB_EP_FLAG_DBUFFER1_TXDONE : The flag is the EPX transmission done and buffer1 is empty in double buffer mode.
 * @exception   
 * @note 
 * @par        Example
 * @code
       if( USB_GetEndpointFlagStatus( USB_EP7) & USB_EP_FLAG_TXDONE)      // Judge USB_EP7 register whether transmission done or not.
       {
           // To do......
       }
 * @endcode
 *******************************************************************************
 */
uint16_t USB_GetEndpointFlagStatus( USB_EP_Struct* EPX)
{
    return(USB_READ_REG(EPX->CR0.H[1]));
}

 /**
 *******************************************************************************
 * @brief	   Get the endpoint register's relationship flag status and interrupt enable status.
 * @details     
 * @param[in]  EPX
 *      \n     ( USB_EP0 ~ USB_EP7)     : Select control which endpoint register.      
 * @return     The return value is :   
 *      \n     (Bit 17 | Bit 1)  :  USB_EP_ITFLAG_RXNAK   : The status is that EPX send NAK in OUT transfer and the interupt enable.
 *      \n     (Bit 18 | Bit 2)  :  USB_EP_ITFLAG_RXSTALL : The status is that EPX send STALL in OUT transfer and the interrupt enable.
 *      \n     (Bit 25 | Bit 4)  :  USB_EP_ITFLAG_TXNAK   : The status is that EPX send NAK in IN transfer and the interrupt enable.
 *      \n     (Bit 26 | Bit 5)  :  USB_EP_ITFLAG_TXSTALL : The status is that EPX send STALL in IN transfer and the interrupt enable.
 *      \n     1. The EPX buffer mode is normal :
 *      \n         (Bit 16 | Bit 0) :                  USB_EP_ITFLAG_RXDONE     : The status is that EPX receive data done and the interrupt enable.
 *      \n         (Bit 24 | Bit 3) :                  USB_EP_ITFLAG_TXDONE     : The status is that EPX transmission done and the interrupt enable.
 *      \n     2. The EPX buffer mode is RX double buffer mode : ( USB_EP0 no double buffer mode)
 *      \n         (Bit 24 | Bit 16 | Bit 3 | Bit 0) : USB_EP_ITFLAG_DBUFFER_RXDONE : The stuatus is that EPX buffer0 and buffere1 receive data done and the interrupt enable.
 *      \n         (Bit 16 | Bit 0) :                  USB_EP_ITFLAG_DBUFFER0_RXDNE : The status is that EPX buffer0 receive data done and the interrupt enable. 
 *      \n         (Bit 24 | Bit 3) :                  USB_EP_ITFLAG_DBUFFER1_RXDNE : The status is that EPX buffer1 receive data done and the interrupt enable. 
 *      \n     3. The EPX buffer mode is TX double buffer mode : ( USB_EP0 no double buffer mode)
 *      \n         (Bit 24 | Bit 16 | Bit 3 | Bit 0) : USB_EP_ITFLAG_DBUFFER_TXDONE  : The status is that EPX buffer0 and buffer1 transmission data done and the interrupt enable. 
 *      \n         (Bit 16 | Bit 0) :                  USB_EP_ITFLAG_DBUFFER0_TXDONE : The status is that EPX buffer0 transmission data done and the the interrupt enable. 
 *      \n         (Bit 24 | Bit 3) :                  USB_EP_ITFLAG_DBUFFER1_TXDONE : The status is that EPX buffer1 transmission data done and the the interrupt enable.  
 * @exception   
 * @note 
 * @par        Example
 * @code
       if( USB_GetEndpointFlagStatus( USB_EP7) & USB_EP_ITFLAG_TXDONE)      // Judge USB_EP7 register whether transmission done and transmission done interrupt enable or not.
       {
           // To do......
       }
 * @endcode
 *******************************************************************************
 */
uint32_t USB_GetEndpointITFlagStatus( USB_EP_Struct* EPX)
{
    return((USB_READ_REG(EPX->CR0.W) & USB_EP_ITFLAG_ALLMSK));
}

 /**
 *******************************************************************************
 * @brief	   Clear Endpoint register relationship flag. 
 * @details   
 * @param[in]  EPX
 *      \n     ( USB_EP0 ~ USB_EP7)     : Select control which endpoint register.  
 * @param[in]  EPX_CLR_FLAG :  Specifies the clear register flag.
 *      \n                     This parameter can be any of the following values.
 *  @arg\b     USB_EP_FLAG_ISOTXEF         : The flag is the EPX isochronous transmit data empty loss error. ( USB_EP0 no the flag)
 *  @arg\b     USB_EP_FLAG_TXSTALL         : The flag is the EPX send STALL in IN  transfer.
 *  @arg\b     USB_EP_FLAG_TXNAK           : The flag is the EPX send NAK   in IN  transfer.
 *  @arg\b     USB_EP_FLAG_TXDONE          : The flag is the EPX trasmission done.
 *  @arg\b     USB_EP_FLAG_RXISOOVW        : The flag is the EPX isochronous receive data overwrite error. ( USB_EP0 no the flag).
 *  @arg\b     USB_EP_FLAG_RXSTALL         : The flag is the EPX send STALL in OUT transfer.
 *  @arg\b     USB_EP_FLAG_RXNAK           : The flag is the EPX send NAK   in OUT transfer. 
 *  @arg\b     USB_EP_FLAG_RXDONE          : The flag is the EPX receive data done.
 *  @arg\b     USB_EP_FLAG_DBUFFER_RXDONE  : The flag is the EPX recevie data done and two buffer is full in double buffer mode.
 *  @arg\b     USB_EP_FLAG_DBUFFER0_RXDONE : The flag is the EPX receive data done and buffer0 is full in double buffer mode.
 *  @arg\b     USB_EP_FLAG_DBUFFER1_RXDONE : The flag is the EPX receive data done and buffer1 is full in double buffer mode.
 *  @arg\b     USB_EP_FLAG_DBUFFER_TXDONE  : The flag is the EPX transmission done and two buffer is empty in double buffer mode.
 *  @arg\b     USB_EP_FLAG_DBUFFER0_TXDONE : The flag is the EXP transmission done and buffer0 is empty in double buffer mode.
 *  @arg\b     USB_EP_FLAG_DBUFFER1_TXDONE : The flag is the EPX transmission done and buffer1 is empty in double buffer mode.
 * @return      
 * @exception   
 * @note 
 * @par        Example
 * @code
       USB_ClearEndpointFlag( USB_EP2 , USB_EP_FLAG_TXDONE);              // Clear USB_EP2 register transmission done flag.
 * @endcode
 *******************************************************************************
 */
void USB_ClearEndpointFlag( USB_EP_Struct* EPX , uint16_t EPX_CLR_FLAG)
{
    USB_WRITE_REG( EPX->CR0.H[1] , EPX_CLR_FLAG);
}

 /**
 *******************************************************************************
 * @brief	    Get USB_EP0 receing SETUP status.
 * @details        
 * @return      The return value have :
 *      \n      Bit0 : USB_EP0_STOVW - USB_EP0 is receiving SETUP transaction.
 *      \n      Bit1 : USB_EP0_EDOVW - USB_EP0 was complete received  SETUP transaction.
 *      \n      Bit2 : USB_EP0_SETUP - USB_EP0 received SETUP transaction flag.
 * @exception   
 * @note 
 *******************************************************************************
 */
uint8_t USB_GetSETUPStatus(void)
{
    return(__DRV_USB_GETSETUP_STATUS());
}

 /**
 *******************************************************************************
 * @brief	   Clear USB_EP0 received SETUP relationship flag.
 * @details     
 * @param[in]   SETUP_STATUS :
 *      \n      Bit0 : USB_EP0_STOVW - USB_EP0 is receiving SETUP transaction (The bit auto clear when USB_EP0_EDOVW = 1).
 *      \n      Bit1 : USB_EP0_EDOVW - USB_EP0 was complete received  SETUP transaction.
 *      \n      Bit2 : USB_EP0_SETUP - USB_EP0 received SETUP transaction flag.
 * @exception  No
 * @note 
 *******************************************************************************
 */
void USB_ClearSETUPStatus(uint8_t SETUP_STATUS)
{
    USB_WRITE_REG(USB_EP0->CR0.B[1],SETUP_STATUS);
}

/**
 *******************************************************************************
 * @brief	   Configurate Endpoint register relationship interrupt setting.
 * @details   
 * @param[in]  EPX
 *      \n     ( USB_EP0 ~ USB_EP7)     : Select control which endpoint register.  
 * @param[in]  EP_IT_TYPE :
 *      \n     Bit1 :  USB_EP_IE_RXNAK   : The interrupt is the EPX send NAK   in OUT transfer. 
 *      \n     Bit2 :  USB_EP_IE_RXSTALL : The interrupt is the EPX send STALL in OUT transfer.
 *      \n     Bit4 :  USB_EP_IE_TXNAK   : The interrupt is the EPX send NAK   in IN  transfer.
 *      \n     Bit5 :  USB_EP_IE_TXSTALL : The interrupt is the EPX send STALL in IN  transfer.
 *      \n     1. The EPX buffer mode is normal :
 *      \n         Bit0 : USB_EP_IE_RXDONE         : The interrupt is the EPX receive data done.
 *      \n         Bit3 : USB_EP_IE_TXDONE         : The interrupt is the EPX trasmission done.
 *      \n     2. The EPX buffer mode is RX double buffer mode :
 *      \n         Bit0 : USB_EP_IE_DBUFFER_RXDONE : The interrupt is the EPX receive data done.
 *      \n     3. The EPX buffer mode is TX double buffer mode :
 *      \n         Bit3 : USB_EP_IE_DBUFFER_TXDONE : The interrupt is the EPX trasmission done.
 * @param[in]  EPX_IT_EN
 *  @arg\b     DISABLE : Disable EP_IT_TYPE interrupt of EPX.
 *  @arg\b     ENABLE  : Enable EP_IT_TYPE interrupt of EPX. 
 * @return      
 * @exception  No
 * @note 
 * @par        Example
 * @code
       USB_EndpintIT_Config(USB_EP0 , ( USB_EP_IE_RXDONE | USB_EP_IE_TXDONE) , ENABLE);    // Enable EP0 tranmission done and receiving done interrupt.
 * @endcode
 *******************************************************************************
 */
void USB_EndpintIT_Config( USB_EP_Struct* EPX , uint8_t EP_IT_TYPE , FunctionalState  EPX_IT_EN)
{
    USB_MODIFY_REG(EPX->CR0.B[0] , EP_IT_TYPE , (EP_IT_TYPE * EPX_IT_EN));
}

/**
 *******************************************************************************
 * @brief	   Get the endpoint register receive data size.
 * @details     
 * @param[in]  EPX
 *      \n     ( USB_EP0 ~ USB_EP7)     : Select control which endpoint register.      
 * @return     The EPx receive data size.
 * @exception  No
 * @note 
 *******************************************************************************
 */
uint16_t USB_GetEndpointRXSize(USB_EP_Struct* EPX)
{
    return(USB_READ_REG(EPX->RX.H[1]));
}

/**
 *******************************************************************************
 * @brief	   Set the endpoint register trasmit data size in next IN transfer.
 * @details 
 * @param[in]  EPX
 *      \n     ( USB_EP0 ~ USB_EP7)     : Select control which endpoint register.  
 * @param[in]  EP_TXCNT : The EPX transmit data size (bytes) in next IN transfer.
 * @return      
 * @exception  No
 * @note 
 * @par        Example
 * @code
       USB_SetEndpointTXSize( USB_EP2 , 64);                         // USB_EP2 transmit data size is 64 bytes in next IN transfer. 
 * @endcode
 *******************************************************************************
 */
void USB_SetEndpointTXSize(USB_EP_Struct* EPX , uint16_t EP_TXCNT)
{
    USB_WRITE_REG(EPX->TX.H[1],EP_TXCNT);
}

/**
 *******************************************************************************
 * @brief	   Set the endpoint buffer1 transmit data size. 
 * @details    The function use in the endpoint register is double buffer mode.
 * @param[in]  EPX
 *      \n     ( USB_EP1 ~ USB_EP7)     : Select control which endpoint register.  
 * @param[in]  EPDBUF1_TXCNT : The EPX's buffer1 transmit data size.    
 * @return      
 * @exception  No
 * @note 
 * @par        Example
 * @code
       USB_SetEndpointDoubleBuffer1TXSize( USB_EP2 , 32);            // Buffer1 of USB_EP2 data size is 32 bytes.
 * @endcode
 *******************************************************************************
 */
void USB_SetEndpointDoubleBuffer1TXSize(USB_EP_Struct* EPX , uint16_t EPDBUF1_TXCNT)
{
    USB_WRITE_REG(EPX->TX.H[1],EPDBUF1_TXCNT);
}

/**
 *******************************************************************************
 * @brief	   Set the endpoint buffer0 transmit data size. 
 * @details    The function use in the endpoint register is double buffer mode.
 * @param[in]  EPX
 *      \n     ( USB_EP1 ~ USB_EP7)     : Select control which endpoint register.  
 * @param[in]  EPDBUF0_TXCNT : The EPX's buffer0 transmit data size.    
 * @return      
 * @exception  No
 * @note 
 * @par        Example
 * @code
       USB_SetEndpointDoubleBuffer0TXSize( USB_EP2 , 32);            // Buffer0 of USB_EP2 data size is 32 bytes.
 * @endcode
 *******************************************************************************
 */
void USB_SetEndpointDoubleBuffer0TXSize(USB_EP_Struct* EPX , uint16_t EPDBUF0_TXCNT)
{
    USB_WRITE_REG(EPX->RX.H[1],EPDBUF0_TXCNT);
}


/**
 *******************************************************************************
 * @brief	    To get receive data of the endpoint register.
 * @details     
 * @param[in]   EPX :
 *      \n      ( USB_EP0 ~ USB_EP7): Select control which endpoint register.      
 * @param[in]   Buffer              : RX buffer of the register to destination peripheral.
 * @param[in]   Release_RXMemory    : After read the data control whether release the RX memory to read next data or not.
 * @return      Read data byte in the time.
 * @exception   
 * @note 
 * @par         Example
 * @code
       USB_EPX_Read_Byte = USB_GetEndpointRXData( USB_EP1 , &USB_EP1_RXBUF[0] , DISABLE);   // Read USB_EP1 RX data to USB_EP1_RXBUF and no release USB_EP1 RX memory to read next data.

       OR

       USB_EPX_Read_Byte = USB_GetEndpointRXData( USB_EP1 , &USB_EP1_RXBUF[0] , ENABLE);    // Read USB_EP1 RX data to USB_EP1_RXBUF and release USB_EP1 RX memory to read next data.
 * @endcode
 *******************************************************************************
 */
uint32_t USB_GetEndpointRXData( USB_EP_Struct* EPX, uint8_t *Buffer, FunctionalState Release_RXMemory )
{
    uint32_t USB_RXDataTmp;
    uint32_t USBRX_BLen;
    uint8_t  *USB_EP_SRAM;
    
    USBRX_BLen = USB_READ_REG(EPX->RX.H[1]);

    USB_EP_SRAM = (uint8_t*)(0x30000000 + USB_READ_REG( EPX->RX.H[0]));
    
    for( USB_RXDataTmp = 0; USB_RXDataTmp < USBRX_BLen ; USB_RXDataTmp ++)
    {
        Buffer[USB_RXDataTmp] =  USB_EP_SRAM[USB_RXDataTmp];
    }
    
    if( Release_RXMemory == ENABLE)
    {
        USB_WRITE_REG( EPX->CR1.H[1] ,  EP_RX_VALID);
    }
    else
    {
        USB_WRITE_REG( EPX->CR1.H[1] ,  EP_RX_NAK);
    }
    
    return( USBRX_BLen);
}

/**
 *******************************************************************************
 * @brief	    To get receive data of the endpoint register in double buffer mode.
 * @details     
 * @param[in]   EPX :
 *      \n      ( USB_EP1 ~ USB_EP7)     : Select control which endpoint register. 
 *      \n                                 (USB_EP0 no double buffer mode).
 * @param[in]   Buffer : RX buffer of the register to destination peripheral.
 * @return      Read data byte in the time.
 * @exception   No
 * @note 
 *******************************************************************************
 */
uint32_t USB_GetEndpointDoubleBufferRXData( USB_EP_Struct* EPX, uint8_t *Buffer )
{
    uint32_t USBRXDB_DataTmp;
    uint32_t USBRXDB_BLen;
    uint8_t  *USB_EPDB_SRAM;   
    
    switch( (USB_READ_REG(EPX->CR1.H[1]) & ( USB_EP1CR1_RXSEQ1_mask_h1 | USB_EP1CR1_RXMC1_mask_h1 | USB_EP1CR1_TXMC1_mask_h1)))
    {
        case 0:
        case ( USB_EP1CR1_RXSEQ1_mask_h1 | USB_EP1CR1_TXMC1_mask_h1):
                                                                     USBRXDB_BLen  = USB_READ_REG( EPX->RX.H[1]);
                                                                     USB_EPDB_SRAM = (uint8_t*)(0x30000000 + USB_READ_REG( EPX->RX.H[0]));
                                                                     for( USBRXDB_DataTmp = 0; USBRXDB_DataTmp < USBRXDB_BLen; USBRXDB_DataTmp++)
                                                                     {
                                                                         Buffer[USBRXDB_DataTmp] = USB_EPDB_SRAM[ USBRXDB_DataTmp];
                                                                     }
                                                                     USB_WRITE_REG( EPX->CR1.H[1] ,  USB_EPDB_RXBUF0_VALID_MASK);
                                                                     break;
        case ( USB_EP1CR1_RXSEQ1_mask_h1):
        case ( USB_EP1CR1_RXMC1_mask_h1):
                                                                     USBRXDB_BLen  = USB_READ_REG( EPX->TX.H[1] ) ;
                                                                     USB_EPDB_SRAM = (uint8_t*)(0x30000000 + USB_READ_REG( EPX->TX.H[0]));
                                                                     for( USBRXDB_DataTmp = 0; USBRXDB_DataTmp < USBRXDB_BLen; USBRXDB_DataTmp++)
                                                                     {
                                                                         Buffer[USBRXDB_DataTmp] = USB_EPDB_SRAM[ USBRXDB_DataTmp];
                                                                     }
                                                                     USB_WRITE_REG( EPX->CR1.H[1] ,  USB_EPDB_RXBUF1_VALID_MASK);                  
                                                                     break;
        default:
                                                                     return(0);           
    }
    return(USBRXDB_BLen);
}

/**
 *******************************************************************************
 * @brief	  To set transmit data of the endpoint register.
 * @details 
 * @param[in] EPX :
 *      \n    ( USB_EP0 ~ USB_EP7)     : Select control which endpoint register.  
 * @param[in] Buffer :  The pointer is transmit data source.
 * @param[in] TX_CNT :  The count is transmit data size.
 * @exception No
 * @note      
 * @par       Example
 * @code
       USB_SetEndpointTXData( USB_EP1 , &USB_EP1_TXBUF[0] , 64);      // USB_EP1 send 64 byte and data source from USB_EP1_TXBUF.
 * @endcode               
 *******************************************************************************
 */ 
void USB_SetEndpointTXData( USB_EP_Struct* EPX, __I uint8_t *Buffer , uint32_t TX_CNT )
{ 
    uint32_t USB_TXDataTmp;
    uint8_t  *USB_EP_SRAM;
  

    USB_EP_SRAM = (uint8_t*)(0x30000000 + ( USB_READ_REG( EPX->TX.H[0]) ));
    
    for ( USB_TXDataTmp=0 ; USB_TXDataTmp<TX_CNT ; USB_TXDataTmp++ ) 
    {
        USB_EP_SRAM[USB_TXDataTmp] = Buffer[USB_TXDataTmp];
    }
    
    USB_WRITE_REG(EPX->TX.H[1],(uint16_t)TX_CNT);                             // Set this byte will Trigger USB to Transmit Data to the Host 
    USB_WRITE_REG( EPX->CR1.H[1] ,  EP_TX_VALID);                             // USB will return ACK immediately when receive IN transaction   
    
}

/**
 *******************************************************************************
 * @brief	  To set transmit data of the endpoint register in double buffer.
 * @details 
 * @param[in] EPX :
 *      \n    ( USB_EP1 ~ USB_EP7)     : Select control which endpoint register.
 *      \n                               (USB_EP0 no double buffer mode)
 * @param[in] Buffer :  The pointer is transmit data source.
 * @param[in] Cnt    :  The count is transmit data size.
 * @exception No
 * @return    DRV_Busy or DRV_Success (  Double buffer is full or Write double buffer success )
 * @note      
 * @par       Example
 * @code
       USB_SetEndpointDoubleBufferTXData( USB_EP1 , &USB_EP1_TXDBUF[0] , 64);      // USB_EP1 send 64 byte and data source from USB_EP1_TXDBUF.           
 * @endcode  
 *******************************************************************************
 */ 
DRV_Return USB_SetEndpointDoubleBufferTXData( USB_EP_Struct* EPX, uint8_t *Buffer , uint32_t Cnt )
{
    uint32_t USBTXDB_DataTmp;
    uint8_t  *USB_EPDB_SRAM;   
    
    switch( (USB_READ_REG(EPX->CR1.H[1]) & ( USB_EP1CR1_TXSEQ1_mask_h1 | USB_EP1CR1_RXMC1_mask_h1 | USB_EP1CR1_TXMC1_mask_h1)))
    {
        case 0:
        case ( USB_EP1CR1_TXSEQ1_mask_h1 | USB_EP1CR1_TXMC1_mask_h1):
                                                                     USB_WRITE_REG ( EPX->RX.H[1] , (uint16_t)Cnt);
                                                                     USB_EPDB_SRAM = (uint8_t*)(0x30000000 + USB_READ_REG( EPX->RX.H[0]));
                                                                     for( USBTXDB_DataTmp = 0; USBTXDB_DataTmp < Cnt; USBTXDB_DataTmp++)
                                                                     {
                                                                         USB_EPDB_SRAM[ USBTXDB_DataTmp] = Buffer[USBTXDB_DataTmp];
                                                                     }
                                                                     USB_WRITE_REG( EPX->CR1.H[1] ,  USB_EPDB_TXBUF0_VALID_MASK);
                                                                     break;
        case USB_EP1CR1_TXMC1_mask_h1:
        case USB_EP1CR1_TXSEQ1_mask_h1:
                                                                     USB_WRITE_REG ( EPX->TX.H[1] , (uint16_t)Cnt);
                                                                     USB_EPDB_SRAM = (uint8_t*)(0x30000000 + USB_READ_REG( EPX->TX.H[0]));
                                                                     for( USBTXDB_DataTmp = 0; USBTXDB_DataTmp < Cnt; USBTXDB_DataTmp++)
                                                                     {
                                                                         USB_EPDB_SRAM[ USBTXDB_DataTmp] = Buffer[USBTXDB_DataTmp];   
                                                                     }
                                                                     USB_WRITE_REG( EPX->CR1.H[1] ,  USB_EPDB_TXBUF1_VALID_MASK);
                                                                     break;
        default:        
                                                                     return(DRV_Busy);
    }
    
    return(DRV_Success);
}

/**
 *******************************************************************************
 * @brief	   Set the endpoint register receive max size.
 * @details    The function is use in receiving memory block size mode is 2byte mode.
 * @param[in]  EPX
 *      \n     ( USB_EP0 ~ USB_EP7)     : Select control which endpoint register.
 * @param[in]  EP_BLSIZE : EPX could receive max data size. ( 2 ~ 62 bytes)     
 * @return      
 * @exception  No
 * @note       The function only use for USB_SetEndpointRXBlock function.
 *******************************************************************************
 */ 
static void USB_SetEndpointBlockOf2Byte(USB_EP_Struct* EPX , uint8_t EP_BLSIZE)
{
    uint8_t RXBlockOf2 ;
    
    RXBlockOf2 = EP_BLSIZE >> 1;
    
    if((EP_BLSIZE & 0x01)!=0)
    {
        RXBlockOf2 = RXBlockOf2 + 1;
    }
    
    USB_MODIFY_REG(EPX->CR1.B[1], (USB_EP0CR1_BLSIZE0_mask_b1 | USB_EP0CR1_BLNUM0_mask_b1) , RXBlockOf2);
}
/**
 *******************************************************************************
 * @brief	   Set the endpoint register receive max size.
 * @details    The function is use in receiving memory block size mode is 32byte mode.
 * @param[in]  EPX
 *      \n     ( USB_EP0 ~ USB_EP7)     : Select control which endpoint register.
 * @param[in]  EP_BLSIZE : EPX could receive max data size. ( 32 ~  1024 bytes)     
 * @return      
 * @exception  No
 * @note       The function only use for USB_SetEndpointRXBlock function.
 *******************************************************************************
 */  
static void USB_SetEndpointBlockOf32Byte(USB_EP_Struct* EPX , uint32_t EP_BLSIZE)
{
    uint32_t RXBlockOf32 ;
    
    RXBlockOf32 = EP_BLSIZE >> 5;
    
    if((RXBlockOf32 & 0x1F)!=0)
    {
        RXBlockOf32 = RXBlockOf32 - 1;
    }
   
    USB_MODIFY_REG(EPX->CR1.B[1], (USB_EP0CR1_BLSIZE0_mask_b1 | USB_EP0CR1_BLNUM0_mask_b1) , ((uint8_t)RXBlockOf32 | USB_EP0CR1_BLSIZE0_mask_b1));
}

/**
 *******************************************************************************
 * @brief	   Set the endpoint register receive max size.
 * @details  
 * @param[in]  EPX
 *      \n     ( USB_EP0 ~ USB_EP7)     : Select control which endpoint register.
 * @param[in]  EP_BLSIZE : EPX could receive max data size. ( 2 ~ 1024 bytes)        
 * @return      
 * @exception  No  
 * @note 
 * @par        Example
 * @code
       USB_SetEndpointRXBlock( USB_EP1 , 64);                  // The USB_EP1 receive max data size is 64 bytes.
 * @endcode
 *******************************************************************************
 */ 
void USB_SetEndpointRXBlock(USB_EP_Struct* EPX , uint32_t EP_BLSIZE)
{
    if(EP_BLSIZE>62)
    {
        USB_SetEndpointBlockOf32Byte(EPX,EP_BLSIZE);
    }
    else 
    {
        USB_SetEndpointBlockOf2Byte(EPX,(uint8_t)EP_BLSIZE);
    } 
}
/**
 *******************************************************************************
 * @brief	   Set the endpoint register transmit buffer start address.
 * @details  
 * @param[in]  EPX
 *      \n     ( USB_EP0 ~ USB_EP7)     : Select control which endpoint register.
 * @param[in]  EPTXDATA_ADR : The EPX transmit buffer start address.   
 * @return      
 * @exception  No
 * @note       " Please conside the USB SRAM size and the EPX could transmit max data size. "
 * @par        Example
 * @code
       USB_SetEndpointTXDataAddress( USB_EP0 , 0);             // The USB_EP0 transmit buffer start address is 0x0000 of USB SRAM.
 * @endcode
 *******************************************************************************
 */ 
void USB_SetEndpointTXDataAddress(USB_EP_Struct* EPX , uint16_t EPTXDATA_ADR)
{
    USB_WRITE_REG(EPX->TX.H[0] , (EPTXDATA_ADR & 0xFFFC));
}

/**
 *******************************************************************************
 * @brief	   Set the endpoint register receive buffer start address.
 * @details    
 * @param[in]  EPX
 *      \n     ( USB_EP0 ~ USB_EP7)     : Select control which endpoint register.
 * @param[in]  EPRXDATA_ADR : The EPX receive buffer start address.        
 * @return      
 * @exception  No
 * @note       1. Please conside the USB SRAM size and the EPX could receive max data size.
 *     \n      2. The function will word align for address.
 * @par        Example
 * @code
       USB_SetEndpointRXDataAddress( USB_EP0 , 64);             // The USB_EP0 transmit buffer start address is 0x0040 of USB SRAM.
 * @endcode
 *******************************************************************************
 */
void USB_SetEndpointRXDataAddress(USB_EP_Struct* EPX , uint16_t EPRXDATA_ADR)
{
    USB_WRITE_REG( EPX->RX.H[0] , ( EPRXDATA_ADR & 0xFFFC));
}

/**
 *******************************************************************************
 * @brief	   Set buffer0 start address of the endpoint register when the 
 *     \n      endpoint register is double buffer mode.
 * @details    
 * @param[in]  EPX
 *     \n      ( USB_EP0 ~ USB_EP7) : Select control which endpoint register.
 * @param[in]  EPDB_BUF0_ADR        : The EPX receive buffer start address.        
 * @return      
 * @exception  No
 * @note       1. Please conside the USB SRAM size and the EPX could receive max data size. 
 *    \n       2. The function will word align for address.
 * @par        Example
 * @code
       USB_SetEndpointDoubleBuffer0Address( USB_EP0 , 64);             // The USB_EP0 transmit buffer0 start address is 0x0040 of USB SRAM.
 * @endcode
 *******************************************************************************
 */
void USB_SetEndpointDoubleBuffer0Address( USB_EP_Struct* EPX, uint16_t EPDB_BUF0_ADR)
{
    USB_WRITE_REG( EPX->RX.H[0] , (EPDB_BUF0_ADR & 0xFFFC));
}

/**
 *******************************************************************************
 * @brief	   Set buffer0 start address of the endpoint register when the 
 *     \n      endpoint register is double buffer mode.
 * @details    
 * @param[in]  EPX
 *     \n      ( USB_EP0 ~ USB_EP7) : Select control which endpoint register.
 * @param[in]  EPDB_BUF0_ADR        : The EPX receive buffer start address.        
 * @return      
 * @exception  No
 * @note       1. Please conside the USB SRAM size and the EPX could receive max data size. 
 *    \n       2. The function will word align for address.
 * @par        Example
 * @code
       USB_SetEndpointDoubleBuffer0Address( USB_EP0 , 64);             // The USB_EP0 transmit buffer0 start address is 0x0040 of USB SRAM.
 * @endcode
 *******************************************************************************
 */
void USB_SetEndpointDoubleBuffer1Address( USB_EP_Struct* EPX, uint16_t EPDB_BUF0_ADR)
{
    USB_WRITE_REG( EPX->TX.H[0] , (EPDB_BUF0_ADR & 0xFFFC));
}

/**
 *******************************************************************************
 * @brief	   Read the endpoint register transmit buffer start address
 * @details     
 * @param[in]  EPX
 *      \n     ( USB_EP0 ~ USB_EP7)     : Select control which endpoint register.       
 * @return     The EPX transmit buffer start address. 
 * @exception  No
 * @note 
 *******************************************************************************
 */ 
uint16_t USB_GetEndpointTXDataAddress(USB_EP_Struct* EPX)
{
    
    return(USB_READ_REG( EPX->TX.H[0]));
}
/**
 *******************************************************************************
 * @brief	   Read the endpoint register receive buffer start address
 * @details     
 * @param[in]  EPX
 *      \n     ( USB_EP0 ~ USB_EP7)     : Select control which endpoint register.       
 * @return     The EPX receive buffer start address. 
 * @exception  No
 * @note 
 *******************************************************************************
 */ 
uint16_t USB_GetEndpointRXDataAddress(USB_EP_Struct* EPX)
{
    
    return(USB_READ_REG( EPX->RX.H[0]));
}

/**
 *******************************************************************************
 * @brief	   Read buffer0 of the endpoint register start address
 * @details     
 * @param[in]  EPX
 *      \n     ( USB_EP1 ~ USB_EP7)     : Select control which endpoint register.
 *      \n     ( USB_EP0 no double buffer mode)
 * @return     The EPX buffer0 start address. 
 * @exception  No
 * @note 
 *******************************************************************************
 */ 
uint16_t USB_GetEndpointDoubleBuffer0Address( USB_EP_Struct* EPX)
{
    return( USB_READ_REG( EPX->RX.H[0]) );
}

/**
 *******************************************************************************
 * @brief	   Read buffer1 of the endpoint register start address
 * @details     
 * @param[in]  EPX
 *      \n     ( USB_EP1 ~ USB_EP7)     : Select control which endpoint register.
 *      \n     ( USB_EP0 no double buffer mode)
 * @return     The EPX buffer1 start address. 
 * @exception  No
 * @note 
 *******************************************************************************
 */ 
uint16_t USB_GetEndpointDoubleBuffer1Address( USB_EP_Struct* EPX)
{
    return( USB_READ_REG( EPX->TX.H[0]) );
}

/**
 *******************************************************************************
 * @brief	   Set the endpoint register transmision mode.
 * @details  
 * @param[in]  EPX
 *      \n     ( USB_EP1 ~ USB_EP7) : Select control which endpoint register. 
 * @param[in]  EP_TYPE 
 *  @arg\b     EP_RX_BKINT          : The EPX is RX interrupt / bulk endpoint type.
 *  @arg\b     EP_TX_BKINT          : The EPX is TX interrupt / bulk endpoint type.
 *  @arg\b     EP_RX_BKINT_TX_BKINT : The EPX is RX interrupt / bulk endpoint type and TX interrupt / bulk endpoint type.
 *  @arg\b     EP_RX_BKINT_TX_ISO   : The EPX is RX interrupt / bulk endpoint type and TX isochronous endpoint type.
 *  @arg\b     EP_RX_ISO            : The EPX is RX isochronous endpoint type.
 *  @arg\b     EP_TX_ISO            : The EPX is RX isochronous endpoint type.
 *  @arg\b     EP_RX_ISO_TX_BKINT   : The EPX is RX isochronous endpoint type and TX interrupt / bulk endpoint type.
 *  @arg\b     EP_RX_ISO_TX_ISO     : The EPX is RX isochronous endpoint type and TX isochronous endpoint type.
 * @return      
 * @exception  No 
 * @note 
 * @par        Example
 * @code
        USB_EndpointMode_Select( USB_EP2 , EP_RX_BKINT)              // USB_EP2 is RX interrupt / bulk endpoint type.
 * @endcode
 *******************************************************************************
 */
void USB_EndpointMode_Select(USB_EP_Struct* EPX , USB_EPMode_TypeDef EP_TYPE)
{
    USB_MODIFY_REG(EPX->CR1.B[0], (USB_EP1CR1_RXTYPE1_mask_b0 | USB_EP1CR1_TXTYPE1_mask_b0) , EP_TYPE); 
}

/**
 *******************************************************************************
 * @brief	   Set the endpoint register buffer mode.
 * @details 
 * @param[in]  EPX
 *      \n     ( USB_EP1 ~ USB_EP7) : Select control which endpoint register. 
 * @param[in]  USB_EP_DBMEN 
 *  @arg\b     DISABLE : The EPX buffer mode is normal mode.
 *  @arg\b     ENABLE  : The EPX buffer mode is double buffer mode.
 * @return     
 * @exception  No 
 * @note       If the EPX is double buffer mode the EPX only support RX or TX.
 * @par        Example
 * @code
       USB_EndpointDoubleBufferMode_Cmd( USB_EP3 , ENABLE)          // USB_EP3 buffer mode is double buffer mode.
 * @endcode
 *******************************************************************************
 */
void USB_EndpointDoubleBufferMode_Cmd( USB_EP_Struct* EPX , FunctionalState USB_EP_DBMEN)
{
    USB_MODIFY_REG( EPX->CR1.B[1] , USB_EP1CR1_DBM1_mask_b1 , (USB_EP1CR1_DBM1_mask_b1 * USB_EP_DBMEN));
}

/**
 *******************************************************************************
 * @brief	   USB endpoint block reset.
 * @details 
 * @param[in]  EPX
 *      \n     ( USB_EP1 ~ USB_EP7) : Select control which endpoint register. 
 * @param[in]  EP_RSTYPE -
 *  @arg\b     EP_RST_TX    : Reset the EPX transmission block.
 *  @arg\b     EP_RST_RX    : Reset the EPX receiving block.
 *  @arg\b     EP_RST_TX_RX : Reset the EPX transmission and receiving block.
 *  @arg\b     EP_RST_DB    : Reset the EPX dobule buffer.
 * @return      
 * @exception  No 
 * @note        
 * @par        Example
 * @code
       USB_TriggerEndpointRst( USB_EP1 , EP_RST_TX_RX);              // Reset USB_EP1 transmission and receiving block.
 * @endcode
 *******************************************************************************
 */
void USB_TriggerEndpointRst( USB_EP_Struct* EPX , USB_EPRST_TypeDef EP_RSTYPE)
{
    USB_SET_BIT( EPX->CR0.B[1] , EP_RSTYPE);
}

///@}

/**
 * @name   USB Interrupt Relationship Control
 *             
 */ 
///@{
/**
 *******************************************************************************
 * @brief	   USB interrupt all enable.
 * @details     
 * @param[in]  USB_ITEA_State :
 *  @arg\b     DISABLE : Disable USB interrupt.
 *  @arg\b     ENABLE  : Enable USB interrupt.
 * @return      
 * @exception  No. 
 * @note       To enable USB Interrupt still need NVIC_EnableIRQ(USB_IRQn);
 * @par        Example
 * @code
       USB_ITEA_Cmd( ENABLE);                      // Enable USB interrupt.
 * @endcode
 *******************************************************************************
 */
void USB_ITEA_Cmd(FunctionalState USB_ITEA_State)
{
    USB_MODIFY_REG( USB->INT.B[0] , USB_INT_IEA_mask_b0 , (USB_INT_IEA_enable_b0 * USB_ITEA_State));
}

/**
 *******************************************************************************
 * @brief	    USB interrupt source control.
 * @details     
 * @param[in]   USB_IT:
 *  @arg\b      Bit1 : USB_IT_BUS      - USB bus event global interrupt.
 *  @arg\b      Bit3 : USB_IT_ERR:     - USB bus error global interrupt.
 *  @arg\b      Bit4 : USB_IT_SOF:     - USB host SOF received interrupt.
 *  @arg\b      Bit5 : USB_IT_ESOF     - USB expected start of frame interrupt.
 *  @arg\b      Bit7 : USB_IT_LPM      - USB LPM L1 state request interrupt.
 *  @arg\b      Bit8 : USB_IT_EP0      - USB endpoint-0 global interrupt.
 *  @arg\b      Bit8 : USB_IT_EP1      - USB endpoint-1 global interrupt.
 *  @arg\b      Bit8 : USB_IT_EP2      - USB endpoint-2 global interrupt.
 *  @arg\b      Bit8 : USB_IT_EP3      - USB endpoint-3 global interrupt.
 *  @arg\b      Bit8 : USB_IT_EP4      - USB endpoint-4 global interrupt.
 *  @arg\b      Bit8 : USB_IT_EP5      - USB endpoint-5 global interrupt.
 *  @arg\b      Bit8 : USB_IT_EP6      - USB endpoint-6 global interrupt.
 *  @arg\b      Bit8 : USB_IT_EP7      - USB endpoint-7 global interrupt.
 *      \n      ====== USB_IT_ERR Source =======
 *  @arg\b      Bit18: USB_IT_ERR_OVR  - USB packet memory overrun interrupt.
 *  @arg\b      Bit19: USB_IT_ERR_SETUP- USB wrong SETUP data received interrupt.
 *  @arg\b      Bit20: USB_IT_ERR_NORS - USB host no response error interrupt. 
 *  @arg\b      Bit21: USB_IT_ERR_BST  - USB bit stuffing error interrupt.
 *  @arg\b      Bit22: USB_IT_ERR_CRC  - USB CRC error interrupt.
 *      \n      ====== USB_IT_BUS Source =======
 *  @arg\b      Bit24: USB_IT_BUS_SUSF - USB bus suspend event detect interrupt.
 *  @arg\b      Bit25: USB_IT_BUS_RSMF - USB bus resum event detect interrupt.
 *  @arg\b      Bit26: USB_IT_BUS_RSTF - USB bus reset event detect interrupt.
 *  @arg\b      Bit27: USB_IT_BUS_RWKF - The interrupt is IC wakeup by USB bus reset.
 *  @arg\b      Bit31: USB_IT_BUS_SE1F - USB bus SE1 event detect interrupt.
 *      \n      ====== USB_IT_EP0 ~ USB_IT_EP7 Source =======
 *      \n      Refer to  USB_EndpintIT_Config() function
 * @param[in]   USB_IT_State :
 *  @arg\b      DISABLE : Disable USB_IT interrupt.
 *  @arg\b      ENABLE  : Enable USB_IT interrupt.
 * @return      
 * @exception   No
 * @note        
 * @par         Example
 * @code
       USB_IT_Config(( USB_IT_EP0 | USB_IT_BUS | USB_IT_BUS_SUSF | USB_IT_BUS_RSTF | USB_IT_BUS_RSMF) , ENABLE);   
 * @endcode
 *******************************************************************************
 */
void USB_IT_Config( uint32_t  USB_IT , FunctionalState USB_IT_State)
{
    USB_MODIFY_REG( USB->INT.W , (USB_IT & USB_IT_MASK) ,((USB_IT & USB_IT_MASK) * USB_IT_State));
}

/**
 *******************************************************************************
 * @brief	   Get USB relationship interrupt event flag.
 * @details          
 * @return     Return value is :
 *     \n      Bit1 : USB_IT_BUS      - USB bus event global flag.
 *     \n      Bit3 : USB_IT_ERR:     - USB bus error global flag.
 *     \n      Bit4 : USB_IT_SOF:     - USB host SOF received flag.
 *     \n      Bit5 : USB_IT_ESOF     - USB expected start of frame flag.
 *     \n      Bit7 : USB_IT_LPM      - USB LPM L1 state request flag.
 *     \n      Bit8 : USB_IT_EP0      - USB endpoint-0 global flag.
 *     \n      Bit8 : USB_IT_EP1      - USB endpoint-1 global flag.
 *     \n      Bit8 : USB_IT_EP2      - USB endpoint-2 global flag.
 *     \n      Bit8 : USB_IT_EP3      - USB endpoint-3 global flag.
 *     \n      Bit8 : USB_IT_EP4      - USB endpoint-4 global flag.
 *     \n      Bit8 : USB_IT_EP5      - USB endpoint-5 global flag.
 *     \n      Bit8 : USB_IT_EP6      - USB endpoint-6 global flag.
 *     \n      Bit8 : USB_IT_EP7      - USB endpoint-7 global flag.
 *     \n      ====== USB_IT_ERR Source =======
 *     \n      Bit18: USB_IT_ERR_OVR  - USB packet memory overrun flag.
 *     \n      Bit19: USB_IT_ERR_SETUP- USB wrong SETUP data received flag.
 *     \n      Bit20: USB_IT_ERR_NORS - USB host no response error flag. 
 *     \n      Bit21: USB_IT_ERR_BST  - USB bit stuffing error flag.
 *     \n      Bit22: USB_IT_ERR_CRC  - USB CRC error flag.
 *     \n      ====== USB_IT_BUS Source =======
 *     \n      Bit24: USB_IT_BUS_SUSF - USB bus suspend event detect flag.
 *     \n      Bit25: USB_IT_BUS_RSMF - USB bus resum event detect flag.
 *     \n      Bit26: USB_IT_BUS_RSTF - USB bus reset event detect flag.
 *     \n      Bit27: USB_IT_BUS_RWKF - The flag is IC wakeup by USB bus reset.
 *     \n      Bit31: USB_IT_BUS_SE1F - USB bus SE1 event detect flag.
 *     \n      ====== USB_IT_EP0 ~ USB_IT_EP7 Source =======
 *     \n      Refer to  USB_GetEndpointFlagStatus() function
 * @exception  No  
 * @note        
 *******************************************************************************
 */
uint32_t USB_GetITAllFlagStatus(void)
{
    return( USB_READ_REG(USB->STA.W) & USB_IT_MASK);
}

/**
 *******************************************************************************
 * @brief	    Get USB interrupt enable status.
 * @details         
 * @return      Return value is : ( 0 = Disable , 1 = Enable)
 *      \n      Bit1 : USB_IT_BUS      - USB bus event global interrupt enable status.
 *      \n      Bit3 : USB_IT_ERR:     - USB bus error global interrupt enable status.
 *      \n      Bit4 : USB_IT_SOF:     - USB host SOF received interrupt enable status.
 *      \n      Bit5 : USB_IT_ESOF     - USB expected start of frame interrupt enable status.
 *      \n      Bit7 : USB_IT_LPM      - USB LPM L1 state request interrupt enable status.
 *      \n      Bit8 : USB_IT_EP0      - USB endpoint-0 global interrupt enable status.
 *      \n      Bit8 : USB_IT_EP1      - USB endpoint-1 global interrupt enable status.
 *      \n      Bit8 : USB_IT_EP2      - USB endpoint-2 global interrupt enable status.
 *      \n      Bit8 : USB_IT_EP3      - USB endpoint-3 global interrupt enable status.
 *      \n      Bit8 : USB_IT_EP4      - USB endpoint-4 global interrupt enable status.
 *      \n      Bit8 : USB_IT_EP5      - USB endpoint-5 global interrupt enable status.
 *      \n      Bit8 : USB_IT_EP6      - USB endpoint-6 global interrupt enable status.
 *      \n      Bit8 : USB_IT_EP7      - USB endpoint-7 global interrupt enable status.
 *      \n      ====== USB_IT_ERR Source =======
 *      \n      Bit18: USB_IT_ERR_OVR  - USB packet memory overrun interrupt enable status.
 *      \n      Bit19: USB_IT_ERR_SETUP- USB wrong SETUP data received interrupt enable status.
 *      \n      Bit20: USB_IT_ERR_NORS - USB host no response error interrupt enable status. 
 *      \n      Bit21: USB_IT_ERR_BST  - USB bit stuffing error interrupt enable status.
 *      \n      Bit22: USB_IT_ERR_CRC  - USB CRC error interrupt enable status.
 *      \n      ====== USB_IT_BUS Source =======
 *      \n      Bit24: USB_IT_BUS_SUSF - USB bus suspend event detect interrupt enable status.
 *      \n      Bit25: USB_IT_BUS_RSMF - USB bus resum event detect interrupt enable status.
 *      \n      Bit26: USB_IT_BUS_RSTF - USB bus reset event detect interrupt enable status.
 *      \n      Bit27: USB_IT_BUS_RWKF - The interrupt enable statusis is IC wakeup by USB bus reset.
 *      \n      Bit31: USB_IT_BUS_SE1F - USB bus SE1 event detect interrupt enable status.
 *      \n      ====== USB_IT_EP0 ~ USB_IT_EP7 Source =======
 *      \n      Refer to  USB_GetEndpointITFlagStatus() function 
 * @exception   No
 * @note        
 *******************************************************************************
 */
uint32_t USB_GetITIEAllStatus(void)
{
    return( USB_READ_REG(USB->INT.W) & USB_IT_MASK);
}

/**
 *******************************************************************************
 * @brief	    Clear USB relationship interrupt event flag.
 * @details     
 * @param[in]   USB_ITFlag
 *  @arg\b      Bit4 : USB_IT_SOF:     - USB host SOF received flag.
 *  @arg\b      Bit5 : USB_IT_ESOF     - USB expected start of frame flag.
 *  @arg\b      Bit7 : USB_IT_LPM      - USB LPM L1 state request flag.
 *  @arg\b      ====== USB_IT_ERR Source =======
 *  @arg\b      Bit18: USB_IT_ERR_OVR  - USB packet memory overrun flag.
 *  @arg\b      Bit19: USB_IT_ERR_SETUP- USB wrong SETUP data received flag.
 *  @arg\b      Bit20: USB_IT_ERR_NORS - USB host no response error flag. 
 *  @arg\b      Bit21: USB_IT_ERR_BST  - USB bit stuffing error flag.
 *  @arg\b      Bit22: USB_IT_ERR_CRC  - USB CRC error flag.
 *  @arg\b      ====== USB_IT_BUS Source =======
 *  @arg\b      Bit24: USB_IT_BUS_SUSF - USB bus suspend event detect flag.
 *  @arg\b      Bit25: USB_IT_BUS_RSMF - USB bus resum event detect flag.
 *  @arg\b      Bit26: USB_IT_BUS_RSTF - USB bus reset event detect flag.
 *  @arg\b      Bit27: USB_IT_BUS_RWKF - The flag is IC wakeup by USB bus reset.
 *  @arg\b      Bit31: USB_IT_BUS_SE1F - USB bus SE1 event detect flag.
 *  @arg\b      ====== USB_IT_EP0 ~ USB_IT_EP7 Source =======
 *  @arg\b      Refer to  USB_ClearEndpointFlag() function     
 * @return      
 * @exception   No
 * @note        
 * @par         Example
 * @code
       USB_ClearITFlag( USB_IT_BUS_SUSF );
 * @endcode
 *******************************************************************************
 */
void USB_ClearITFlag(uint32_t USB_ITFlag)
{
    USB_WRITE_REG( USB->STA.W , (USB_ITFlag & USB_IT_MASK));
}

///@}


/**
 * @name    USB LPM Relationship Control
 *             
 */ 

///@{
/**
 *******************************************************************************
 * @brief	    Set USB device handshake for Host LPM request.
 * @details     
 * @param[in]   LPM_STATE -
 *  @arg\b      USB_LPM_ACK : When receiving Host LPM request USB device send ACK. 
 *  @arg\b      USB_LPM_NYET: When receiving Host LPM request USB device send NYET.
 *  @arg\b      USB_LPM_DISABLE : When receiving Host LPM request USB device no reflect.
 * @return      
 * @exception   No
 * @note        
 * @par         Example
 * @code
       USB_LPMhandshakeMode_Select( USB_LPM_ACK);                      // When receiving Host LPM request USB device send ACK.
 * @endcode
 *******************************************************************************
 */
void USB_LPMhandshakeMode_Select( USB_LPMHandShake_TypeDef LPM_STATE)
{
    USB_MODIFY_REG( USB->CR1.B[2] , (USB_CR1_LPM_EN_mask_b2 | USB_CR1_LPM_ACK_mask_b2) , LPM_STATE);
}

/**
 *******************************************************************************
 * @brief	   Get USB LPM BESL value. 
 * @details     
 * @return     LPM BESL value of host send.
 * @exception  No
 * @note        
 *******************************************************************************
 */
uint8_t USB_GetLPMBESL(void)
{
    return(((USB_READ_REG(USB->CR1.B[2]) & USB_CR1_LPM_BESL_mask_b2) >> 4));
}

/**
 *******************************************************************************
 * @brief	    Get USB LPM bRemoteWakeup value.
 * @details       
 * @return      LPM bRemoteWakeup value of host send.   
 * @exception   No
 * @note        
 *******************************************************************************
 */
uint8_t USB_GetLPMbRemoteWake(void)
{
    return(((USB_READ_REG(USB->CR1.B[2]) & USB_CR1_LPM_RWK_mask_b2) >> 2));
}

///@}


/**
 * @name    USB DMA Relationship Control
 *             
 */ 
///@{


/**
 *******************************************************************************
 * @brief	    USB DMA RX source select. 
 * @details     
 * @param[in]   USB_DMARXSEL_NUM : USB DMA RX control number ( Now only 0)
 * @param[in]   USB_DMARXSEL_TYPE 
 *  @arg\b      USB_DMA_RXSEL0_DISABLE : No Enable the USB DMA.
 *  @arg\b      USB_DMA_RXSEL0_EP3     : USB DMA RX source from USB_EP3 RX.
 *  @arg\b      USB_DMA_RXSEL0_EP4     : USB DMA RX source from USB_EP4 RX.
 * @return      
 * @exception   No
 * @note        
 * @par         Example
 * @code
       USB_DMARXSEL_Config( 0 , USB_DMA_RXSEL0_EP3)                 // USB DMA_RX0  data source from USB_EP3 RX.
 * @endcode
 *******************************************************************************
 */
void USB_DMARXSEL_Config( uint8_t USB_DMARXSEL_NUM , USB_DMARXSEL_TypeDef USB_DMARXSEL_TYPE)
{
    USB_MODIFY_REG( USB->CR2.B[USB_DMARXSEL_NUM] , USB_CR2_DMA_RXSEL0_mask_b0, (uint8_t)USB_DMARXSEL_TYPE); 
}

/**
 *******************************************************************************
 * @brief	    USB DMA TX destination select. 
 * @details     
 * @param[in]   USB_DMATXSEL_NUM : USB DMA TX control number ( Now only 0)
 * @param[in]   USB_DMATXSEL_TYPE 
 *  @arg\b      USB_DMA_TXSEL0_DISABLE : No Enable the USB DMA.
 *  @arg\b      USB_DMA_TXSEL0_EP3     : USB DMA TX destination to USB_EP3 TX.
 *  @arg\b      USB_DMA_TXSEL0_EP4     : USB DMA TX destination to USB_EP4 TX.
 * @return      
 * @exception   No
 * @note        
 * @par         Example
 * @code
       USB_DMATXSEL_Config( 0 , USB_DMA_RXSEL0_EP4)                 // USB DMA_TX0  data destine is USB_EP4 TX.
 * @endcode
 *******************************************************************************
 */
void USB_DMATXSEL_Config( uint8_t USB_DMATXSEL_NUM , USB_DMATXSEL_TypeDef USB_DMATXSEL_TYPE)
{
    USB_MODIFY_REG( USB->CR2.B[USB_DMATXSEL_NUM] , USB_CR2_DMA_TXSEL0_mask_b0, (uint8_t)USB_DMATXSEL_TYPE); 
}


///@}
