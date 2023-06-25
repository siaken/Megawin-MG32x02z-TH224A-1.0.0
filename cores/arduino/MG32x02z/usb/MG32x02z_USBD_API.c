


 /**
 ******************************************************************************
 *
 * @file        USBD_Core.c
 * @brief       The USBD core Code's c file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.05
 * @date        2022/08/19
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
#include "MG32x02z.h"
#include "MG32x02z_USBD_API.h"


//#include "MG32x02z_USBD_MouseDescriptor.h"

/* Wizard menu ---------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define USB_EP_REG_SHIFT       0
#define USB_EP_IT_SHIFT        8



/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static const uint8_t  EPn_ID_Table[8]          = {                    0 , MG_USB_EP1_ADDRESS    , MG_USB_EP2_ADDRESS    , MG_USB_EP3_ADDRESS    , MG_USB_EP4_ADDRESS    , MG_USB_EP5_ADDRESS    , MG_USB_EP6_ADDRESS    , MG_USB_EP7_ADDRESS    };
static const uint16_t EPn_RXSIZE_TABLE[8]      = {MG_USB_EP0_SRAM_RXSIZE, MG_USB_EP1_SRAM_RXSIZE, MG_USB_EP2_SRAM_RXSIZE, MG_USB_EP3_SRAM_RXSIZE, MG_USB_EP4_SRAM_RXSIZE, MG_USB_EP5_SRAM_RXSIZE, MG_USB_EP6_SRAM_RXSIZE, MG_USB_EP7_SRAM_RXSIZE};
static const uint16_t EPn_RXSRAM_TABLE[8]      = {USB_EP0_SRAM_RXADR    , USB_EP1_SRAM_RXADR    , USB_EP2_SRAM_RXADR    , USB_EP3_SRAM_RXADR    , USB_EP4_SRAM_RXADR    , USB_EP5_SRAM_RXADR    , USB_EP6_SRAM_RXADR    , USB_EP7_SRAM_RXADR}   ;
static const uint16_t EPn_TXSRAM_TABLE[8]      = {USB_EP0_SRAM_TXADR    , USB_EP1_SRAM_TXADR    , USB_EP2_SRAM_TXADR    , USB_EP3_SRAM_TXADR    , USB_EP4_SRAM_TXADR    , USB_EP5_SRAM_TXADR    , USB_EP6_SRAM_TXADR    , USB_EP7_SRAM_TXADR}   ;
static const uint8_t  EPn_InitaStatus_TABLE[8] = {MG_USB_EP0_STATUS     , MG_USB_EP1_STATUS     , MG_USB_EP2_STATUS     , MG_USB_EP3_STATUS     , MG_USB_EP4_STATUS     , MG_USB_EP5_STATUS     , MG_USB_EP6_STATUS     , MG_USB_EP7_STATUS     };

static uint32_t USB_EP_TABLE[16] = {USB_EP0_Base , USB_EP1_Base , USB_EP2_Base , USB_EP3_Base , USB_EP4_Base , USB_EP5_Base , USB_EP6_Base , USB_EP7_Base,
                                    USB_IT_EP0   , USB_IT_EP1   , USB_IT_EP2   , USB_IT_EP3   , USB_IT_EP4   , USB_IT_EP5   , USB_IT_EP6   , USB_IT_EP7  };

USBCTR_TypeDef Ep0;
/* Private function prototypes -----------------------------------------------*/ 
void USB_IRQHandler(void);
         
static void API_USBD_Endpoint0_ReadData( void );                                      
static void API_USBD_Get_Status( void );                                      
static void API_USBD_ClearFeature( void );
static void API_USBD_SetFeature( void );
static void API_USBD_GetDescriptor( void );
static void API_USBD_SetConfiguration( void );
static void API_USBD_SetInterface( void );
static void API_USBD_GetInterface( void );
static void API_USBD_ControlRead( void );
static void API_USBD_StandardRequest( void );  
static void API_USBD_ClassRequest( void );
static void API_USBD_ControlWrite( void );
                                      
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* External vairables --------------------------------------------------------*/

                        
USBState_TypeDef  g_UsbEP1Ctr = 
{
    .Status = USBA_Status_Idle,
    .IdleRate = 0,
    .Protocol = 1,
    
    .mHID0_ReportLength = 0,
    .mHID1_ReportLength = 0,
    .pUSB_INTERFACE0_HID_REPORT = NULL,
    .pUSB_INTERFACE1_HID_REPORT = NULL,


    .pUSB_DEVICE_DESCRIPTOR = NULL,
    .pUSB_CONFIGURATION_DESCRIPTOR = NULL,
    .pUSB_STRING_DESCRIPTOR = NULL,

    #if MF_STRING == 1                                          
    .pManufacturer_Descriptor = NULL,
    #endif      
    #if PD_STRING == 1                                          
    .pProduct_Descriptor = NULL,
    #endif   
    #if SN_STRING == 1                                          
    .pSerialNumber_Descriptor = NULL,
    #endif 
    #if MG_USB_LPM_EN == 1                                      
    .pUSB_BOS_DESCRIPTOR = NULL,
    .pUSB_EXT_DESCRIPTOR = NULL,
    #endif
};
                                      
/**
 *******************************************************************************
 * @brief	   USB IRQ handler
 * @details     
 * @exception  No
 * @note                     
 *******************************************************************************
 */
void USB_IRQHandler(void)
{
   API_USBD_IRQ();   
}
/**
 *******************************************************************************
 * @brief	    USB function inital.
 * @details         
 * @exception   No
 * @note                    
 *******************************************************************************
 */  
void API_USBD_Inital(void)
{
    USB_EP_Struct*  USB_EPX;
    uint8_t         USB_InitTmp;
    
    USB_Cmd(ENABLE);
    
    NVIC_DisableIRQ(USB_IRQn);
    USB_ITEA_Cmd(DISABLE);
 

    g_UsbEP1Ctr.Status = USBA_Status_Idle;
    g_UsbEP1Ctr.IdleRate = 0;
    g_UsbEP1Ctr.Protocol = 1;
 
    //=====================================================
    //EP0 config
    
    USB_TriggerEndpointRst(USB_EP0 , EP_RST_TX_RX);
    
    USB_SetEndpointStatus(USB_EP0, EP_RX_STALL_TX_STALL);  
    USB_EndpintIT_Config( USB_EP0 , (USB_EP_IE_TXDONE | USB_EP_IE_RXDONE) , ENABLE);
    

    USB_SetEndpointRXDataAddress(USB_EP0, EPn_RXSRAM_TABLE[0]);             
    USB_SetEndpointTXDataAddress(USB_EP0, EPn_TXSRAM_TABLE[0]);                
    
    USB_SetEndpointRXBlock(USB_EP0,64);
    
    //====================================================
    //EP1 ~ EP7 config
    for(USB_InitTmp=1;USB_InitTmp<8;USB_InitTmp++)
    {
        USB_EPX = ((USB_EP_Struct*)USB_EP_TABLE[ USB_EP_REG_SHIFT + USB_InitTmp]);

        //-----------------------------------------------------------------
        //Defeault Inital 
        USB_TriggerEndpointRst(USB_EPX , EP_RST_TX_RX);
        USB_SetEndpointStatus(USB_EPX, EP_RX_DISABLE_TX_DISABLE);
        USB_EndpintIT_Config( USB_EPX , USB_EP_IE_ALL, DISABLE); 

        //-----------------------------------------------------------------
        //Set buffer relationship control.
        USB_SetEndpointRXDataAddress(USB_EPX, EPn_RXSRAM_TABLE[USB_InitTmp]);              /*!<Set SRAM address that USB_EPX_RX start save address. */
        USB_SetEndpointTXDataAddress(USB_EPX, EPn_TXSRAM_TABLE[USB_InitTmp]);              /*!<Set SRAM address that USB_EPX_TX start send address..*/

        if(EPn_RXSIZE_TABLE[USB_InitTmp] != 0)        
        {
            USB_SetEndpointRXBlock(USB_EPX,EPn_RXSIZE_TABLE[USB_InitTmp]);  
        }
        
        if(EPn_InitaStatus_TABLE[USB_InitTmp] & MG_USB_DBUF_MSK)
        {
            USB_EndpointDoubleBufferMode_Cmd(USB_EPX,ENABLE);
        }
        else
        {
            USB_EndpointDoubleBufferMode_Cmd(USB_EPX,DISABLE);
        }
        //-----------------------------------------------------------------
        //Set Endpoint Address
        USB_SetEndpointAddress(USB_EPX, EPn_ID_Table[USB_InitTmp] ); 
        
        //-----------------------------------------------------------------
        //Set Endpoint Mode.
        switch(( EPn_InitaStatus_TABLE[USB_InitTmp] & MG_USB_MODE_MASK))
        {
            case MG_USB_MODE_RX_ISO_TX_BKINT:
                                               USB_EndpointMode_Select(USB_EPX , EP_RX_ISO_TX_BKINT);
                                               break;
            case MG_USB_MODE_RX_BKINT_TX_ISO:
                                               USB_EndpointMode_Select(USB_EPX , EP_RX_BKINT_TX_ISO);
                                               break;
            case MG_USB_MODE_RX_TX_ISO:
                                               USB_EndpointMode_Select(USB_EPX , EP_RX_ISO_TX_ISO);
                                               break;
            case MG_USB_MODE_RX_TX_BKINT:
            default:
                                               USB_EndpointMode_Select(USB_EPX , EP_RX_BKINT_TX_BKINT);
                                               break;
        }
    }
    //===================================================
    //USB LPM Receive Disable
    USB_LPMhandshakeMode_Select(USB_LPM_DISABLE);
    //===================================================
    //USB Interrupt Config
    #if MG_USB_LPM_EN == 1
        USB_IT_Config(( USB_IT_EP0 | USB_IT_BUS | USB_IT_BUS_SUSF | USB_IT_BUS_RSTF | USB_IT_BUS_RSMF | USB_IT_LPM) , ENABLE);
    #else
        USB_IT_Config(( USB_IT_EP0 | USB_IT_BUS | USB_IT_BUS_SUSF | USB_IT_BUS_RSTF | USB_IT_BUS_RSMF) , ENABLE);      
    #endif
    USB_ITEA_Cmd(ENABLE);
    NVIC_EnableIRQ(USB_IRQn);
    
    //====================================================
    //USB module event wakeup from STOP mode enable.
    UnProtectModuleReg(PWprotect);
    PW_PeriphSTOPModeContinuous_Config(PW_STPPO_USB,ENABLE);
    PW_PeriphSTOPModeWakeUp_Config(PW_WKSTP_USB,ENABLE);
    ProtectModuleReg(PWprotect);

    //====================================================
    //Control Parameter inital.
    Ep0.USBStatus          = USB_STATUS_DEFAULT;
    Ep0.ConfigurationValue = 0;
    //=====================================================
    //USB Connect to Bus (Enable DP pull-up R
    USB_Connect_Cmd(ENABLE);
 
}
/**
 *******************************************************************************
 * @brief	    Read data from RX SRAM of the endpoint.
 * @details     
 * @param[in]   EPX      : ( USB_EP0 ~ USB_EP7) Select control which endpoint register.
 * @param[in]   bRBuffer : The pointer is save data  buffer.
 * @param[in]   bRXShift : Starting receive data byte from RX SRAM of the endpoint.
 * @param[in]   bRXCnt   : Total receive data size.
 * @return      
 * @exception   No
 * @note        RX SRAM address of the endpoint have to set.
 *******************************************************************************
 */ 
void API_USBD_ReadEndpointData( USB_EP_Struct* EPX, uint8_t *bRBuffer , uint32_t bRXShift , uint32_t bRXCnt)
{
    uint8_t  USB_REP_Tmp;
    uint8_t *USB_EP_RAM;
    
    USB_EP_RAM = (uint8_t*)((0x30000000 + EPX->RX.H[0] + bRXShift));
    
    for( USB_REP_Tmp = 0; USB_REP_Tmp <bRXCnt ; USB_REP_Tmp ++)
    {
        bRBuffer[USB_REP_Tmp] =  USB_EP_RAM[USB_REP_Tmp];
    }
}
/**
 *******************************************************************************
 * @brief	    Write data to TX SRAM of the endpoint.
 * @details     
 * @param[in]   EPX      : ( USB_EP0 ~ USB_EP7) Select control which endpoint register.
 * @param[in]   btBuffer : The pointer is data source.
 * @param[in]   bTXShift : Write address is that shift address from the TX start SRAM address.
 * @param[in]   bTXCnt   : Write total data size.
 * @return      
 * @exception   No
 * @note        TX SRAM address of the endpoint have to set.              
 *******************************************************************************
 */ 
void API_USBD_WriteEndpointData( USB_EP_Struct* EPX, uint8_t __I *btBuffer , uint32_t bTXShift , uint8_t bTXCnt )
{ 
    uint8_t bEPTX_Tmp;
    uint8_t *USB_EP_RAM;
  
    USB_EP_RAM = (uint8_t*)(0x30000000 + EPX->TX.H[0] + bTXShift);
    
    
    for ( bEPTX_Tmp=0 ; bEPTX_Tmp<bTXCnt ; bEPTX_Tmp++ ) 
    {
        USB_EP_RAM[bEPTX_Tmp] = btBuffer[bEPTX_Tmp];
    }
}
/**
 *******************************************************************************
 * @brief	    Write a constant value to TX SRAM of the endpoint.
 * @details 
 * @param[in]   EPX      : ( USB_EP0 ~ USB_EP7) Select control which endpoint register.
 * @param[in]   ConstData: Constant value.
 * @param[in]   cTXShift : Write address is that shift address from the TX start SRAM address.
 * @param[in]   cTXCnt   : Write total data size.
 * @return      
 * @exception   No
 * @note        TX SRAM address of the endpoint have to set.              
 *******************************************************************************
 */ 
void API_USBD_WriteEndpointConstData( USB_EP_Struct* EPX, uint8_t ConstData , uint32_t cTXShift , uint8_t cTXCnt )
{ 
    uint8_t cEPTX_Tmp;
    uint8_t *USB_EP_RAM;
  
    USB_EP_RAM = (uint8_t*)(0x30000000 + EPX->TX.H[0] + cTXShift);
    
    for ( cEPTX_Tmp=0 ; cEPTX_Tmp < cTXCnt ; cEPTX_Tmp++ ) 
    {
        USB_EP_RAM[cEPTX_Tmp] = ConstData;
    }
}    
/**
 *******************************************************************************
 * @brief	   Write a byte to TX SRAM of the endpoint. 
 * @details     
 * @param[in]   EPX      : ( USB_EP0 ~ USB_EP7) Select control which endpoint register.
 * @param[in]   sData    : Write data.
 * @param[in]   shift    : Write address is that shift address from the TX start SRAM address.
 * @return      
 * @exception   No
 * @note        TX SRAM address of the endpoint have to set.               
 *******************************************************************************
 */ 
void API_USBD_WriteEndpointSingleData( USB_EP_Struct* EPX, uint8_t sData , uint8_t shift)
{
    uint8_t *USB_EP_RAM;
    
    USB_EP_RAM = (uint8_t*)(0x30000000 + EPX->TX.H[0]);
    
    USB_EP_RAM[shift] = sData;
}
/**
 *******************************************************************************
 * @brief	   EP0 receiving data.
 * @details     
 * @return      
 * @exception  No 
 * @note            
 *******************************************************************************
 */ 
static void API_USBD_Endpoint0_ReadData( void )
{ 
    uint16_t BLen, tmp;
    
    //==============================================================================
    //Recing SETUP token.
    tmp = __DRV_USB_GETSETUP_STATUS();
    if ( tmp & ( USB_EP0_STOVW | USB_EP0_EDOVW ))                  // Setup Token
    { 
        Ep0.DataStage = SETUPSTAGE;
        while(1)
        { 
            tmp = __DRV_USB_GETSETUP_STATUS();
            
            do{ 
                tmp = __DRV_USB_GETSETUP_STATUS();
            }while(tmp & USB_EP0_STOVW);                           // waiting STOVE = 0

            do{                                        
                tmp = __DRV_USB_GETSETUP_STATUS();         
            }while(!( tmp & USB_EP0_EDOVW ));                      // waiting EDOVW = 1                                        


            __DRV_USB_CLEAR_EDOVW();
            USB_ClearEndpointFlag(USB_EP0,USB_EP_FLAG_RXDONE);

            BLen = USB_GetEndpointRXSize(USB_EP0);
                                         
            API_USBD_ReadEndpointData(USB_EP0 , Ep0.RxTx , 0 , BLen);

            tmp = __DRV_USB_GETSETUP_STATUS();
            if (!(tmp & ( USB_EP0_STOVW | USB_EP0_EDOVW )))
                break;
        }

        USB_SetEndpointStatus(USB_EP0, EP_RX_VALID_TX_NAK);
        __DRV_USB_CLEAR_RXSETUP();

        Ep0.All = BLen;                                             
        
    }
    //=============================================================================
    //Receing data.
    else                                                                                      
    {
        BLen    = USB_GetEndpointRXSize(USB_EP0);
        Ep0.All = Ep0.All - BLen;
        
        API_USBD_ReadEndpointData( USB_EP0, Ep0.RxTx , 0 , BLen);
        USB_SetEndpointStatus(USB_EP0, EP_RX_VALID);
        
        Ep0.DataStage = STATUSSTAGE;
        USB_SetEndpointStatus(USB_EP0, EP_RX_STALL_TX_STALL);
    }                              
}
/**
 *******************************************************************************
 * @brief	   This request returns status for the specified recipient. 
 * @details     
 * @return      
 * @exception  No
 * @note                 
 *******************************************************************************
 */ 
static void API_USBD_Get_Status( void )
{ 
    uint8_t   tmp;
    uint16_t  USB_Status;
     
    Ep0.All = 2;                                                                                                          // Only 2 byte transfer to the host
                                                                                                                          
    Ep0.RxTx[1] = 0;                                                                                                      
    switch( Ep0.RxTx[0] & 0x03 )                                                                                          // Request Type ( Reserve low 2 bit )
    {                                                                                                                     
        case DEVICEREQUEST:                                                                                               
                              if ( (Ep0.USBStatus & USB_STATUS_RWEN_MASK) == USB_STATUS_RWEN_ENABLE )                     // Check Remote wakeup enabled or not
                              {                                                                                           
                                   Ep0.RxTx[0] = 0x02;                                                                    // Return Function Remove Wake-up Enable
                              }                                                                                           
                              else                                                                                        
                              {                                                                                           
                                   Ep0.RxTx[0] = 0x00;                                                                    // Return Function Remove Wake-up Disable                                                     
                              }
                              break;                                                                     
        case ENDPOINTREQUEST:  
                              tmp = (Ep0.RxTx[4] & 0x0F);

                              switch(tmp)
                              {
                                  case 1:
                                          USB_Status = USB_GetEndpointStatus(USB_EP1);
                                          break;
                                  default:
                                          USB_Status = 0;
                                          break;
                              }
                              if((USB_Status & USB_EP0CR1_TXSTL0_mask_h1) || (USB_Status & USB_EP0CR1_RXSTL0_mask_h1))
                              {
                                  Ep0.RxTx[0] = 0x01;                                                                     // if EndPoint Rx/Tx STAL then set EndPoint Halt
                              }
                              else
                              {
                                  Ep0.RxTx[0] = 0x00;                                                                     // else seting this EndPoint Avaliable for Rx/Tx 
                              }
                              
                              break;
        case INTERFACEREQUEST: 
        default:              
                              USB_SetEndpointStatus(USB_EP0, EP_RX_STALL_TX_STALL);
                              break; 
    }
} 


/**
 *******************************************************************************
 * @brief	    Clear Feature.
 * @details     This request is used to clear or disable a specific feature.
 * @return      
 * @exception   No
 * @note                   
 *******************************************************************************
 */ 
static void API_USBD_ClearFeature( void )
{ 
    switch( Ep0.RxTx[0] & 0x03 )                                                                     // Request Type ( Reserve low 2 bit )
    { 
        case DEVICEREQUEST:    if ( Ep0.RxTx[2] == DEVICE_REMOTE_WAKEUP )
                               {
                                   Ep0.USBStatus &= (uint32_t)(~USB_STATUS_RWEN_MASK);               // Disable the Device Remote Wakeup function
                               }
                               else
                               {   
                                   USB_SetEndpointStatus(USB_EP0, EP_RX_STALL_TX_STALL);
                               }
                               break;                                                       
        case ENDPOINTREQUEST:                                                                        // Disable Endpoint Halt.
                               if ( Ep0.RxTx[2] == ENDPOINT_HALT )
                               { 
                                   switch((Ep0.RxTx[4] & 0x0F))
                                   {
                                       case 1:
                                               USB_TriggerEndpointRst(USB_EP1,EP_RST_TX_RX);
                                               USB_SetEndpointINSequenceBit(USB_EP1,0);
                                               USB_SetEndpointOUTSequenceBit(USB_EP1,0);
                                               USB_SetEndpointStatus(USB_EP1, EP_RX_DISABLE_TX_NAK);
                                               break;
                                       default:
                                               break;
                                   }
                               }
                               else
                               { 
                                   USB_SetEndpointStatus(USB_EP0, EP_RX_STALL_TX_STALL);
                               }
                               break;
        case INTERFACEREQUEST: 
        default:               
                               USB_SetEndpointStatus(USB_EP0, EP_RX_STALL_TX_STALL);
                               break;
    }
}
/**
 *******************************************************************************
 * @brief	    Set feature.
 * @details     This request is used to set or enable a specific feature
 * @return      
 * @exception   No
 * @note                     
 *******************************************************************************
 */
static void API_USBD_SetFeature( void )
{ 

    switch( Ep0.RxTx[0] & 0x03 )                                                                      // Request Type ( Reserve low 2 bit )
    { 
        case DEVICEREQUEST:    
                               if ( Ep0.RxTx[2] == DEVICE_REMOTE_WAKEUP )
                               {
                                   Ep0.USBStatus |= USB_STATUS_RWEN_MASK;                             // Endpoint the Device Remote Wakeup function
                               }
                               else
                               { 
                                   USB_SetEndpointStatus(USB_EP0, EP_RX_STALL_TX_STALL);
                               }
                               break;                                                                 // Enable Endpoint Halt.
        case ENDPOINTREQUEST:                                                 
                               if ( Ep0.RxTx[2] == ENDPOINT_HALT )
                               { 
                                   switch((Ep0.RxTx[4] & 0x0F))
                                   {
                                       case 1:
                                               USB_SetEndpointStatus(USB_EP1, EP_RX_STALL_TX_STALL);
                                               break;
                                       default:
                                               break;
                                   }
                               }
                               else
                               { 
                                   USB_SetEndpointStatus(USB_EP0, EP_RX_STALL_TX_STALL);
                               }
                               break;
        case INTERFACEREQUEST: 
        default:               
                               USB_SetEndpointStatus(USB_EP0, EP_RX_STALL_TX_STALL); 
                               break; 
    }
}  

/**
 *******************************************************************************
 * @brief	   Get Descriptor. 
 * @details    This request returns the specified descriptor if the descriptor exists.
 * @return      
 * @exception  No
 * @note                     
 *******************************************************************************
 */
static void API_USBD_GetDescriptor( void )
{ 
    ctype WLen;
  
    WLen.W  = 0;                                  
    Ep0.All = (uint32_t)((Ep0.RxTx[7] << 8) + Ep0.RxTx[6]);

    //=======================================================================================
    //Descriptor Type : High byte of the wValue field.
    switch( Ep0.RxTx[3] )	
    { 
        //------------------------------------------------------------------------------------------------
        //Device Descriptor :
        case DEVICE_DESCRIPTOR:       
                                      Ep0.Buf   = g_UsbEP1Ctr.pUSB_DEVICE_DESCRIPTOR;
                                      WLen.B[0] = Ep0.Buf[0];
                                      break;
        //------------------------------------------------------------------------------------------------
        //Configuration Descriptor :
        case CONFIGURATION_DESCRIPTOR: 
                                      //------------------------------------------------------------------
                                      //*. Descriptor Index : Low byte of the wValue field.
                                      //*. The sample only one configuration.
                                      Ep0.Buf   = g_UsbEP1Ctr.pUSB_CONFIGURATION_DESCRIPTOR;
                                      WLen.B[1] = Ep0.Buf[3];
                                      WLen.B[0] = Ep0.Buf[2];
                                      break;
        //------------------------------------------------------------------------------------------------
        //String Descriptor :
        case STRING_DESCRIPTOR:        
                                      //------------------------------------------------------------------
                                      //*. Descriptor Index : Low byte of the wValue field.
                                      WLen.B[0] = 0;
                                      switch( Ep0.RxTx[2] )
                                      { 
                                          case 0:  
                                                   Ep0.Buf   = g_UsbEP1Ctr.pUSB_STRING_DESCRIPTOR;
                                                   WLen.B[0] = Ep0.Buf[0]; 
                                                   break;
                                          //-------------------------------------------------------------
                                          //* Index define refer to device descriptor.
                                          //    1.iManufacture Index  = 0x01
                                          //    2.iProduct Index      = 0x02
                                          //    3.iSerialNumber Index = 0x03 
                                          case 1:  
                                                   #if MF_STRING_INDEX == 1
                                                       if ( g_UsbEP1Ctr.pUSB_DEVICE_DESCRIPTOR[14] )
                                                       {
                                                           Ep0.DataStage = DATASTAGE_STRING0;
                                                           Ep0.Buf = g_UsbEP1Ctr.pManufacturer_Descriptor;
                                                           WLen.B[0] = MFS_LEN;
                                                           break;
                                                       }
                                                   #elif PD_STRING_INDEX == 1
                                                       if ( g_UsbEP1Ctr.pUSB_DEVICE_DESCRIPTOR[15] )
                                                       {
                                                           Ep0.DataStage = DATASTAGE_STRING0;
                                                           Ep0.Buf       = g_UsbEP1Ctr.pProduct_Descriptor;
                                                           WLen.B[0]     = PDS_LEN;
                                                           break;
                                                       }
                                                   #elif SN_STRING_INDEX == 1
                                                       if ( g_UsbEP1Ctr.pUSB_DEVICE_DESCRIPTOR[16] )
                                                       {
                                                           Ep0.DataStage = DATASTAGE_STRING0;
                                                           Ep0.Buf       = g_UsbEP1Ctr.pSerialNumber_Descriptor;
                                                           WLen.B[0]     = SNS_LEN;
                                                           break;
                                                       }
                                                   #endif
                                                   
                                                    
                                                   Ep0.DataStage = STATUSSTAGE;       
                                                   
                                                   break;
                                          case 2:  
                                                   #if PD_STRING_INDEX == 2
                                                       if ( g_UsbEP1Ctr.pUSB_DEVICE_DESCRIPTOR[15] )
                                                       {
                                                           Ep0.DataStage = DATASTAGE_STRING0;
                                                           Ep0.Buf       = g_UsbEP1Ctr.pProduct_Descriptor;
                                                           WLen.B[0]     = PDS_LEN;
                                                           break;
                                                       }
                                                   #elif SN_STRING_INDEX == 2
                                                       if ( g_UsbEP1Ctr.pUSB_DEVICE_DESCRIPTOR[16] )
                                                       {
                                                           Ep0.DataStage = DATASTAGE_STRING0;
                                                           Ep0.Buf       = g_UsbEP1Ctr.pSerialNumber_Descriptor;
                                                           WLen.B[0]     = SNS_LEN;
                                                           break;
                                                       }
                                                   #endif
                                                   
                                                    
                                                   Ep0.DataStage = STATUSSTAGE;       
                                                   
                                                   break;
                                          case 3:  
                                                   #if SN_STRING_INDEX == 3
                                                       if ( g_UsbEP1Ctr.pUSB_DEVICE_DESCRIPTOR[16] )
                                                       {
                                                           Ep0.DataStage = DATASTAGE_STRING0;
                                                           Ep0.Buf       = g_UsbEP1Ctr.pSerialNumber_Descriptor;
                                                           WLen.B[0]     = SNS_LEN;
                                                           break;
                                                       }
                                                   #endif
                                                   
                                                   Ep0.DataStage = STATUSSTAGE;       
                                                   
                                                   break;
                                          default: 
                                                   Ep0.DataStage = STATUSSTAGE;
                                                   break;
                                    }
                                    Ep0.Tmp = WLen.B[0];
                                    break;
        //------------------------------------------------------------------------------------------------
        //HID Descriptor.
        case HID_DESCRIPTOR:           
                                    switch( Ep0.RxTx[4])
                                    {
                                        case 0:             
                                                Ep0.Buf = &g_UsbEP1Ctr.pUSB_CONFIGURATION_DESCRIPTOR[USB_CONFIGURATION_DESC_SIZE +  USB_INTERFACE_DESC_SIZE] ;
                                                break;
                                        default:
                                                Ep0.DataStage = STATUSSTAGE;
                                                break;                                            
                                    }
                                    WLen.B[0] = Ep0.Buf[0];
                                    break;
        //-------------------------------------------------------------------------------------------------
        //HID Report.
        case HID_REPORT:                   
                                    switch( Ep0.RxTx[4])    
                                    {
                                        case 0:
                                                Ep0.Buf   = g_UsbEP1Ctr.pUSB_INTERFACE0_HID_REPORT;
                                                WLen.B[0] = LOBYTE(g_UsbEP1Ctr.mHID0_ReportLength);
      	                                        WLen.B[1] = HIBYTE(g_UsbEP1Ctr.mHID0_ReportLength);
                                                break;
                                        default:
                                                Ep0.DataStage = STATUSSTAGE;
                                                break;
                                    }
    	                            
    	                            break;
        //-------------------------------------------------------------------------------------------------
        //BOS Descriptor.
        #if MG_USB_LPM_EN == 1
        case BOS_DESCRIPTOR:
                                    Ep0.Buf = (uint8_t*)&USB_BOS_DESCRIPTOR;
                                    WLen.B[0] = Ep0.Buf[2];
                                    break;
        #endif
    	default:                      
                                    Ep0.DataStage = STATUSSTAGE;
                                    break;
    }
    if ( Ep0.All > WLen.W )
    {
        Ep0.All = WLen.W;
    }
}
/**
 *******************************************************************************
 * @brief	   Set Configuration 
 * @details    This request sets the device configuration.
 * @return      
 * @exception  No 
 * @note       The sample code only support one configuration.          
 *******************************************************************************
 */                              
static void API_USBD_SetConfiguration( void )
{ 
    USB_EP_Struct*  USB_EPX;
    uint8_t         USBConfig_Tmp;
    
    Ep0.ConfigurationValue =  Ep0.RxTx[2];
    
    if( Ep0.ConfigurationValue  == 1)
    { 
        for( USBConfig_Tmp = 1; USBConfig_Tmp < 8; USBConfig_Tmp ++)
        {
            USB_EPX = ((USB_EP_Struct*)USB_EP_TABLE[ USB_EP_REG_SHIFT + USBConfig_Tmp]);
            USB_IT_Config( USB_EP_TABLE[ USB_EP_IT_SHIFT + USBConfig_Tmp] ,ENABLE);

            switch( (EPn_InitaStatus_TABLE[USBConfig_Tmp] & MG_USBEP_OPEN_MASK) )
            {
                case MG_USBEP_RX_OPEN:
                                         USB_EndpintIT_Config( USB_EPX , (USB_EP_IE_RXDONE) , ENABLE); 
                                         USB_SetEndpointStatus(USB_EPX , EP_RX_VALID); 
                                         break;
                case MG_USBEP_TX_OPEN: 
                                         USB_EndpintIT_Config( USB_EPX , (USB_EP_IE_TXDONE) , ENABLE); 
                                         USB_SetEndpointStatus(USB_EPX , EP_TX_NAK);
                                         break;
                case MG_USBEP_RX_TX_OPEN:
                                         USB_EndpintIT_Config( USB_EPX , (USB_EP_IE_TXDONE | USB_EP_IE_RXDONE) , ENABLE); 
                                         USB_SetEndpointStatus(USB_EPX , EP_RX_VALID_TX_NAK);
                                         break;
                case MG_USBEP_DB_RX_OPEN:
                                         USB_EndpintIT_Config( USB_EPX , (USB_EP_IE_DBUFFER_RXDONE) , ENABLE); 
                                         USB_SetDoubleBufferEndpointStatus(USB_EPX , EP_DB_RXBUFALL_VALID);
                                         break;
                case MG_USBEP_DB_TX_OPEN:
                                         USB_EndpintIT_Config( USB_EPX , (USB_EP_IE_DBUFFER_TXDONE) , ENABLE); 
                                         USB_SetDoubleBufferEndpointStatus(USB_EPX,EP_DB_TXBUFALL_NAK);
                                         break;
                default:
                                         USB_EndpintIT_Config( USB_EPX , (USB_EP_IE_TXDONE | USB_EP_IE_RXDONE) , DISABLE); 
                                         USB_IT_Config( USB_EP_TABLE[ USB_EP_IT_SHIFT + USBConfig_Tmp] ,DISABLE);
                                         USB_SetEndpointStatus(USB_EPX , EP_RX_DISABLE_TX_DISABLE);
                                         break;     
            }
        }
        //======================================================
        //LPM Control.
        #if MG_USB_LPM_EN == 1
            USB_LPMhandshakeMode_Select(USB_LPM_ACK);
        #endif
        //======================================================
        //USB enumeration PASS
        Ep0.USBStatus |= USB_STATUS_EMULATION_OK;                             // Emulation Flow pass

    }
    else
    {
        USB_SetEndpointStatus(USB_EP1 , EP_RX_DISABLE_TX_DISABLE);
        USB_SetEndpointStatus(USB_EP2 , EP_RX_DISABLE_TX_DISABLE);
        USB_SetEndpointStatus(USB_EP3 , EP_RX_DISABLE_TX_DISABLE);
        USB_SetEndpointStatus(USB_EP4 , EP_RX_DISABLE_TX_DISABLE);
        USB_SetEndpointStatus(USB_EP5 , EP_RX_DISABLE_TX_DISABLE);
        USB_SetEndpointStatus(USB_EP6 , EP_RX_DISABLE_TX_DISABLE);
        USB_SetEndpointStatus(USB_EP7 , EP_RX_DISABLE_TX_DISABLE);
        
        
    }
    USB_SetEndpointTXSize(USB_EP0, 0);
    USB_SetEndpointStatus(USB_EP0, EP_TX_VALID);                              // USB will return ACK immediately when receive IN transaction
}


/**
 *******************************************************************************
 * @brief	    Set Interface.
 * @details     
 * @return      
 * @exception   No
 * @note                      
 *******************************************************************************
 */
static void API_USBD_SetInterface( void )
{ 
    switch( Ep0.RxTx[4] )
    { 
        case 0:         
                 if ( Ep0.RxTx[2] > 0 )                                          
                 {
                     USB_SetEndpointStatus(USB_EP0, EP_RX_STALL_TX_STALL);        
                 }
                 else
                 { 
                     USB_SetEndpointTXSize(USB_EP0, 0);
                     USB_SetEndpointStatus(USB_EP0, EP_TX_VALID);
                 }
                 break;
        default: 
                 USB_SetEndpointStatus(USB_EP0, EP_RX_STALL_TX_STALL);            
                 break;
    }
}

/**
 *******************************************************************************
 * @brief	    Get Interface.
 * @details     
 * @return      
 * @exception   No
 * @note                    
 *******************************************************************************
 */
static void API_USBD_GetInterface( void )
{ 
    Ep0.All = 1;
    switch( Ep0.RxTx[4] )
    { 
        case 0:         
                 Ep0.RxTx[0] = 0;                                                 // For Interface1 ( HID )
                 break;
        default: 
                 USB_SetEndpointStatus(USB_EP0, EP_RX_STALL_TX_STALL);            // Set Rx/Tx STAL 
                 break;
    }
}

/**
 *******************************************************************************
 * @brief	   Control USB EP0 Transmit (Host EP0 IN).
 * @details     
 * @return      
 * @exception  No 
 * @note                     
 *******************************************************************************
 */
static void API_USBD_ControlRead( void )                                           // Host In , USB Out ( Only for EP0 )
{ 
    uint8_t USB_CtrlRdBLen;
    
    if ( Ep0.DataStage == DATASTAGE )                                             // In DATASTAGE we should move Data to TXFIFO
    { 
        if ( Ep0.All > MG_USB_EP0_DSIZE )
        {
            USB_CtrlRdBLen = MG_USB_EP0_DSIZE;
        }
        else
        {
            USB_CtrlRdBLen = (uint8_t)Ep0.All;
    	}
        API_USBD_WriteEndpointData( USB_EP0 , Ep0.Buf , 0 , USB_CtrlRdBLen );

        USB_SetEndpointTXSize(USB_EP0, USB_CtrlRdBLen);
        USB_SetEndpointStatus(USB_EP0, EP_TX_VALID);                               // USB will return ACK immediately when receive IN transaction
        Ep0.All -= USB_CtrlRdBLen;                                                 // Calculated the Remain Data size
        Ep0.Buf += USB_CtrlRdBLen;                                                 // Move Buffer Address in Right position
    }
    else if(Ep0.DataStage == DATASTAGE_GRP)
    {
        if ( Ep0.All > MG_USB_EP0_DSIZE )
        {
            USB_CtrlRdBLen = MG_USB_EP0_DSIZE;
        }
        else
        {
            USB_CtrlRdBLen = (uint8_t)Ep0.All;
        }
      	API_USBD_WriteEndpointData( USB_EP0 , Ep0.Buf , 0 , USB_CtrlRdBLen );
        
        USB_SetEndpointTXSize(USB_EP0,USB_CtrlRdBLen);                              // Set this byte will Trigger USB to Transmit Data to the Host   
        USB_SetEndpointStatus(USB_EP0, EP_TX_VALID);                                // USB will return ACK immediately when receive IN transaction        
        Ep0.All -= USB_CtrlRdBLen;                                                  // Calculated the Remain Data size
        Ep0.Buf += USB_CtrlRdBLen;                                                  // Move Buffer Address in Right position
        
    }
    else if(Ep0.DataStage == DATASTAGE_STRING0)
    {
        Ep0.DataStage  = DATASTAGE_STRING1;
        
        API_USBD_WriteEndpointData( USB_EP0 , &Ep0.Tmp , 0 , 1 );
        Ep0.Tmp        = STRING_DESCRIPTOR;
        API_USBD_WriteEndpointData( USB_EP0 , &Ep0.Tmp , 1 , 1 );
        USB_CtrlRdBLen = 2;
        Ep0.All        = Ep0.All - 2;
        
        Ep0.Tmp        = 0;
        
        while( (USB_CtrlRdBLen < MG_USB_EP0_DSIZE) && (Ep0.All!=0))
        {
            if( ( USB_CtrlRdBLen % 2)==0)
            {
                API_USBD_WriteEndpointData( USB_EP0 , Ep0.Buf , USB_CtrlRdBLen , 1 );
                Ep0.Buf += 1;
            }
            else
            {
                API_USBD_WriteEndpointData( USB_EP0 , &Ep0.Tmp , USB_CtrlRdBLen , 1 );
            }
            
            Ep0.All -= 1;
            USB_CtrlRdBLen = USB_CtrlRdBLen + 1;
        }

        USB_SetEndpointTXSize(USB_EP0, USB_CtrlRdBLen);
        USB_SetEndpointStatus(USB_EP0, EP_TX_VALID);                                                                          
    }
    else if(Ep0.DataStage == DATASTAGE_STRING1)
    {
        USB_CtrlRdBLen = 0;
        Ep0.Tmp        = 0;
        
        while( (USB_CtrlRdBLen < MG_USB_EP0_DSIZE) && (Ep0.All!=0))
        {
            if( ( USB_CtrlRdBLen % 2)==0)
            {
                API_USBD_WriteEndpointData( USB_EP0 , Ep0.Buf , USB_CtrlRdBLen , 1 );
                Ep0.Buf += 1;
            }
            else
            {
                API_USBD_WriteEndpointData( USB_EP0 , &Ep0.Tmp , USB_CtrlRdBLen , 1 );
            }
            
            Ep0.All -= 1;
            USB_CtrlRdBLen = USB_CtrlRdBLen + 1;
        }

        USB_SetEndpointTXSize(USB_EP0, USB_CtrlRdBLen);
        USB_SetEndpointStatus(USB_EP0, EP_TX_VALID);
    }
    else
    { 
        USB_SetEndpointStatus(USB_EP0, EP_RX_STALL_TX_STALL);                       // Set Rx/Tx STAL 
        if ( Ep0.DataStage == SETADDRESS )                                          // Different from other STATUSSTAGE(importent)
        { 
            __DRV_USB_SETADDRESS(Ep0.Tmp);
        }
    }
}

/**
 *******************************************************************************
 * @brief	   USB standard request.
 * @details     
 * @return      
 * @exception  No  
 * @note                     
 *******************************************************************************
 */
static void API_USBD_StandardRequest( void )
{ 
   if( Ep0.RxTx[0] & GET_REQUEST)
   {
       switch( Ep0.RxTx[1] )                                                                    // Request Code
       { 
           case GET_DESCRIPTOR:    
                                   Ep0.DataStage = DATASTAGE;
                                   API_USBD_GetDescriptor();
                                   API_USBD_ControlRead();
                                   break;
           case GET_CONFIGURATION: 
                                   Ep0.DataStage = DATASTAGE;
                                   Ep0.RxTx[0] = Ep0.ConfigurationValue;                        // This value get from SET_CONFIGURATION transaction
                                   Ep0.All = 1;                                                 // Only 1 byte transfer to the host
                                   API_USBD_ControlRead();
                                   break;
           case GET_STATUS:       
                                   Ep0.DataStage = DATASTAGE;
                                   API_USBD_Get_Status();
                                   API_USBD_ControlRead();
                                   break;
           case GET_INTERFACE:     
                                   Ep0.DataStage = DATASTAGE;
                                   API_USBD_GetInterface();
                                   API_USBD_ControlRead();
                                   break;
           case SYNCH_FRAME:       
                                   Ep0.DataStage = STATUSSTAGE;
                                   USB_SetEndpointTXSize(USB_EP0, 0);
                                   USB_SetEndpointStatus(USB_EP0, EP_TX_VALID);                 // USB will return ACK immediately when receive IN transaction
                                   Ep0.All = 0;
                                   break;
           default:                
                                   USB_SetEndpointStatus(USB_EP0, EP_RX_STALL_TX_STALL);        // Set Rx/Tx STAL 
                                   break;         
       }
   }
   else
   {
       switch( Ep0.RxTx[1] )                                                                    // Request Code
       { 
           case SET_ADDRESS:       
                                   Ep0.DataStage = SETADDRESS;                                  // Different from other STATUSSTAGE
                                   Ep0.Tmp = Ep0.RxTx[2];
                                   USB_SetEndpointTXSize(USB_EP0, 0);
                                   USB_SetEndpointStatus(USB_EP0, EP_TX_VALID);                 // USB will return ACK immediately when receive IN transaction
                                   break;
           case SET_CONFIGURATION: 
                                   Ep0.DataStage = STATUSSTAGE;
                                   API_USBD_SetConfiguration();                                     
                                   break;
           case CLEAR_FRATURE:		
                                   Ep0.DataStage = STATUSSTAGE;  
                                   API_USBD_ClearFeature();
                                   USB_SetEndpointTXSize(USB_EP0, 0);
                                   USB_SetEndpointStatus(USB_EP0, EP_TX_VALID);                 // USB will return ACK immediately when receive IN transaction
                                   break;
           case SET_FEATURE:       
                                   Ep0.DataStage = STATUSSTAGE;
                                   API_USBD_SetFeature();
                                   USB_SetEndpointTXSize(USB_EP0, 0);
                                   USB_SetEndpointStatus(USB_EP0, EP_TX_VALID);                 // USB will return ACK immediately when receive IN transaction
                                   break;
           case SET_INTERFACE:     
                                   Ep0.DataStage = STATUSSTAGE;
                                   API_USBD_SetInterface();
                                   break;
           case SET_DESCRIPTOR:
           default:                
                                   USB_SetEndpointStatus(USB_EP0, EP_RX_STALL_TX_STALL);        // Set Rx/Tx STAL 
                                   break;         
       }
   }
}
/**
 *******************************************************************************
 * @brief	   USB Class Request 
 * @details     
 * @return      
 * @exception  No 
 * @note                     
 *******************************************************************************
 */
static void API_USBD_ClassRequest( void )
{ 
    
    if( Ep0.RxTx[0] & GET_REQUEST)
    {
        switch( Ep0.RxTx[1])  
        {
            case GET_IDLE:     
                              Ep0.DataStage = DATASTAGE;
                              //Ep0.RxTx[0]   = Mouse_CTR.IdleRate;
                              Ep0.RxTx[0]   = g_UsbEP1Ctr.IdleRate;
                              Ep0.All = 1;
                              break;
            case GET_PROTOCOL: 
                              Ep0.DataStage = DATASTAGE;
                              //Ep0.RxTx[0]   = Mouse_CTR.Protocol;
                              Ep0.RxTx[0]   = g_UsbEP1Ctr.Protocol;
                              Ep0.All = 1;
                              break;
            case GET_REPORT:   
                              Ep0.DataStage  = DATASTAGE;
                              Ep0.All = 1;
                              break; 
            default:
                              Ep0.DataStage = STATUSSTAGE;
                              break;
        }
        API_USBD_ControlRead();
    }
    else
    {
        switch( Ep0.RxTx[1])  
        {
            case SET_IDLE:     
                               Ep0.DataStage = STATUSSTAGE;
                               //Mouse_CTR.IdleRate = Ep0.RxTx[3];
                               g_UsbEP1Ctr.IdleRate = Ep0.RxTx[3];
                               USB_SetEndpointTXSize(USB_EP0, 0);
                               USB_SetEndpointStatus(USB_EP0, EP_TX_VALID);
                               break;
            case SET_PROTOCOL: 
                               Ep0.DataStage = STATUSSTAGE;
                               //Mouse_CTR.Protocol = Ep0.RxTx[2];
                               g_UsbEP1Ctr.Protocol = Ep0.RxTx[2];
                               USB_SetEndpointTXSize(USB_EP0, 0);
                               USB_SetEndpointStatus(USB_EP0, EP_TX_VALID);
                               break;
            case SET_REPORT:   
                               Ep0.DataStage = STATUSSTAGE;
                               USB_SetEndpointStatus(USB_EP0, EP_RX_STALL_TX_STALL); 
                      
                               Ep0.All = Ep0.RxTx[7];
                               Ep0.All <<= 8;
                               Ep0.All += Ep0.RxTx[6];
                               break;
            default:           
                               Ep0.DataStage = STATUSSTAGE;
                               USB_SetEndpointStatus(USB_EP0, EP_RX_STALL_TX_STALL);       
                               break; 
        }
    }
}
/**
 *******************************************************************************
 * @brief	   USB EP0 handle for receive data or SETUP. 
 * @details     
 * @return      
 * @exception  No 
 * @note                      
 *******************************************************************************
 */
static void API_USBD_ControlWrite( void )                                                        // Host Out , USB In ( Only for EPO )
{                                                                                                                                                                       
    Ep0.Buf = Ep0.RxTx;                                                                   // Move Buffer address to RxTx[8] array , Use for USB_CtrlRd();
    API_USBD_Endpoint0_ReadData();                                                        // Move Rx Data to RxTxBuf buffer
    if ( Ep0.DataStage == SETUPSTAGE )                                                        
    {	                                                                                  
        Ep0.All = 0;                                                                      
        switch( Ep0.RxTx[0] & REQUEST_TYPE_MASK )                                         // Request Type
        {
            case STANDARD_REQUEST: 
                                   API_USBD_StandardRequest();
                                   break;
            case CLASS_REQUEST:    
                                   API_USBD_ClassRequest();
                                   break;
            default:               
                                   USB_SetEndpointStatus(USB_EP0, EP_RX_STALL_TX_STALL);   // Set Rx/Tx STAL 
                                   break;                       
        }
    }    
}


/**
 *******************************************************************************
 * @brief	   USB interrupt handle function.
 * @details     
 * @return      
 * @exception  No 
 * @note                     
 *******************************************************************************
 */

void API_USBD_IRQ( void )
{ 
    uint32_t        USBIRQ_Status;
    uint32_t        URBEPIRQ_Status1;
    uint8_t         USBIRQ_Tmp;

    //=========================================================================
    //Get USB Interrupt Flag
    USBIRQ_Status       =  USB_GetITAllFlagStatus();

    //=========================================================================
    //USB Bus event handle
    if((USBIRQ_Status & USB_IT_BUS)!=0 )                                                      
    { 
        //---------------------------------------------------------------------
        //Detect Bus Suspend 
        if((USBIRQ_Status & USB_IT_BUS_SUSF)==USB_IT_BUS_SUSF)                                 
        {
            USB_ClearITFlag(USB_IT_BUS_SUSF | USB_IT_BUS);
            
            Ep0.USBStatus |= USB_STATUS_BUS_SUSPEND;
            
            // To do......
        }
        else
        { 
            //---------------------------------------------------------------------
            //Detect Bus Reset.
            if((USBIRQ_Status & USB_IT_BUS_RSTF)==USB_IT_BUS_RSTF)                                
            { 
                USB_ClearITFlag(USB_IT_BUS_RSTF);
                USBIRQ_Tmp = 0x80;

                while( USBIRQ_Tmp  < 228)                                  /*!< By changing the parameter (128 ~ 255) to modify Reset debounce. */
                {
                    if(__DRV_USB_GETBUS_STATUS() & USB_BUS_SE0_STA)
                    {
                        USBIRQ_Tmp = USBIRQ_Tmp + 1;
                    }
                    else
                    {
                        USBIRQ_Tmp = 0;
                        break;
                    }                        
                }
                if( USBIRQ_Tmp != 0)
                {
                    //API_Mouse_Init();
                    API_USBD_Inital();
                    
                    Ep0.USBStatus |= USB_STATUS_BUS_RESET;
                    // To do......
                }
            }
            //---------------------------------------------------------------------
            //Detect Bus Resume 
            else if((USBIRQ_Status & USB_IT_BUS_RSMF)==USB_IT_BUS_RSMF)                         
            { 
                USB_ClearITFlag(USB_IT_BUS_RSMF);
                
                Ep0.USBStatus |= USB_STATUS_BUS_RESUME;
                // To do......
            } 
            //---------------------------------------------------------------------
            //Detect USB bus change in STOP mode
            else if((USBIRQ_Status & USB_IT_BUS_RWKF) == USB_IT_BUS_RWKF)
            {
                USB_ClearITFlag(USB_IT_BUS_RWKF);
                USB_IT_Config( USB_IT_BUS_RWKF , DISABLE);
             
                Ep0.USBStatus |= USB_STATUS_BUS_BUSEVENT_WAKEUP;                
                // To do......
            }                
        }
    }
    //=========================================================================
    //ACK response to LPM
    #if MG_USB_LPM_EN == 1
        if( USBIRQ_Status & USB_IT_LPM)
        {
            Ep0.LPM_BLE = USB_GetLPMBESL();
            
            if(USB_GetLPMbRemoteWake()!=0)
            {
                Ep0.USBStatus |= USB_STATUS_RWEN_MASK;
            }
            else
            {
                Ep0.USBStatus &= (~USB_STATUS_RWEN_MASK);
            }
            Ep0.USBStatus = Ep0.USBStatus | USB_STATUS_BUS_SUSPEND;
            
            USB_ClearITFlag(USB_IT_LPM);
        }
    #endif
    //=========================================================================
    //Endpoint handle.
    else  
    {   
        //=====================================================================
        //Endpoint 1 TX (for mouse)
        if((USBIRQ_Status & USB_IT_EP1)==USB_IT_EP1)
        {
            USB_ClearEndpointFlag(USB_EP1,USB_EP_FLAG_TXDONE);
            
            //Mouse_CTR.Status &= (~USBA_Status_UpdateReport);
            g_UsbEP1Ctr.Status &= (~USBA_Status_UpdateReport);
        }
        //=====================================================================
        //Endpoint 2 control (for Keyboard MultiMedia)
        if((USBIRQ_Status & USB_IT_EP2)==USB_IT_EP2)
        {
            USB_ClearEndpointFlag(USB_EP2 , USB_EP_FLAG_TXDONE);

            g_UsbEP1Ctr.Status &= (~USBA_Status_UpdateReport); 
        }
        //=====================================================================
        //Endpoint 0 control
        if((USBIRQ_Status & USB_IT_EP0)==USB_IT_EP0)
        {
            URBEPIRQ_Status1 = USB_GetEndpointFlagStatus(USB_EP0);
            
            if((URBEPIRQ_Status1 & USB_EP_FLAG_TXDONE)==USB_EP_FLAG_TXDONE)
            {
                USB_ClearEndpointFlag(USB_EP0,USB_EP_FLAG_TXDONE);
                API_USBD_ControlRead();
            }
            else if((URBEPIRQ_Status1 & USB_EP_FLAG_RXDONE)==USB_EP_FLAG_RXDONE)
            {
                USB_ClearEndpointFlag(USB_EP0,USB_EP_FLAG_RXDONE);
                API_USBD_ControlWrite();
            }
        }
    }	  
}





/**
 *******************************************************************************
 * @brief	   USB state handler.  
 * @details     
 * @return      
 * @exception  No 
 * @note
 *******************************************************************************
 */
void Usb_StateHandler(void)
{
    uint32_t USBHandlerStateTmp;
    
    USBHandlerStateTmp = ( Ep0.USBStatus & USB_STATUS_BUS_MASK);
    
    /*USB Flow function*/
    if(USBHandlerStateTmp!=0)
    {
        switch( USBHandlerStateTmp)
        {
            //============================================================================================
            // During handling the ohter functions USB bus happen suspend status. 
            case USB_STATUS_BUS_SUSPEND:
                Ep0.USBStatus = Ep0.USBStatus & ((uint32_t)(~USB_STATUS_BUS_SUSPEND));
                //-------------------------------------------------------------------------
                //If host allow remote wakeup enable the other external wakeup signal.
                if(( Ep0.USBStatus & USB_STATUS_RWEN_MASK) == USB_STATUS_RWEN_ENABLE)
                {
                    //API_Mouse_WakeupIT_Cmd(ENABLE);

                    //To do......
                }
                USB_IT_Config( USB_IT_BUS_RWKF , ENABLE);               /*!< Enable USB Bus event wakeup interrupt in STOP mode.*/ 
                //STOP_WFI();
                //API_Mouse_Parameter_DeInit();
                break;
                
            //============================================================================================
            //Detect USB Bus no supsend in STOP mode.            
            case USB_STATUS_BUS_BUSEVENT_WAKEUP:
                Ep0.USBStatus = Ep0.USBStatus & ((uint32_t)(~USB_STATUS_BUS_BUSEVENT_WAKEUP));

                // To do......
                break;
            //============================================================================================
            //During handling the other functions extern wakeup signal happen.
            case USB_STATUS_BUS_EXTIEVENT_WAKEUP:
                Ep0.USBStatus = Ep0.USBStatus & ((uint32_t)(~USB_STATUS_BUS_EXTIEVENT_WAKEUP));
                //-------------------------------------------------------------------------
                //If host allow remote wakeup send remote wakeup signal to host.
                USB_TriggerRemoteWakeup();
                break;                                                       
            //============================================================================================
            //During handling the ohter functions USB bus happen suspend and resume status.
            case ( USB_STATUS_BUS_SUSPEND | USB_STATUS_BUS_RESUME):
                Ep0.USBStatus = Ep0.USBStatus & ((uint32_t)(~USB_STATUS_BUS_SUSPEND)); 
                break;
            //============================================================================================
            //During handling the ohter function USB bus happen resume status.
            case (USB_STATUS_BUS_BUSEVENT_WAKEUP | USB_STATUS_BUS_RESUME):
            case (USB_STATUS_BUS_RESUME):
                Ep0.USBStatus = Ep0.USBStatus & ((uint32_t)(~(USB_STATUS_BUS_BUSEVENT_WAKEUP | USB_STATUS_BUS_RESUME)));
                break;
            
            //============================================================================================
            case (USB_STATUS_BUS_BUSEVENT_WAKEUP | USB_STATUS_BUS_RESET):
            case USB_STATUS_BUS_RESET:
                Ep0.USBStatus = Ep0.USBStatus & ((uint32_t)(~(USB_STATUS_BUS_BUSEVENT_WAKEUP | USB_STATUS_BUS_RESET)));
                // To do...

                break;
            default:                                                      
                // To do...

                break;
        }
        Ep0.USBStatus = Ep0.USBStatus & (~USBHandlerStateTmp);
    }
}










