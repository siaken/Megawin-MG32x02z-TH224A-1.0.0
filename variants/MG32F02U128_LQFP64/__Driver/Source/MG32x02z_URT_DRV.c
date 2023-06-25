

 /**
 ******************************************************************************
 *
 * @file        MG32x02z_URT_DRV.c
 * @brief       The code is URT driver C file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.23
 * @date        2022/03/17
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

 

#include "MG32x02z_URT_DRV.h"



/**
 * @name	Interrupt And Event
 *             
 */ 
///@{
/**
 *******************************************************************************
 * @brief	    URT local interrupt enable or disable.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_IT: (The device support which interrupt refer to the device spec , please)
 *  @arg\b      URT_IT_CALTMO : Baud rate calibration sync field receive time out.
 *  @arg\b      URT_IT_BKTMO  : Break receive time out.
 *  @arg\b      URT_IT_IDTMO  : Idle state time out.
 *  @arg\b      URT_IT_RXTMO  : Receive time out.
 *  @arg\b      URT_IT_TUDR   : URT SPI slave mode transmit underrun.
 *  @arg\b      URT_IT_TXE    : TX error detect.
 *  @arg\b      URT_IT_ROVR   : Receive overrun error.
 *  @arg\b      URT_IT_NCE    : Receive noised character error detect.
 *  @arg\b      URT_IT_FE     : Receive frame error detect.
 *  @arg\b      URT_IT_PE     : Receive parity error detect.
 *  @arg\b      URT_IT_CTS    : CTS change detect.
 *  @arg\b      URT_IT_IDL    : RX idle line detect.
 *  @arg\b      URT_IT_BK     : Break condition detect.
 *  @arg\b      URT_IT_CALC   : Auto baudrate calibration complete.
 *  @arg\b      URT_IT_TMO    : Timeout timer timeout.
 *  @arg\b      URT_IT_BRT    : Baud rate generator timer timeout.
 *  @arg\b      URT_IT_SADR   : Slave address matched.
 *  @arg\b      URT_IT_TX     : Transmit data register empty.
 *  @arg\b      URT_IT_RX     : Receive data register not empty.
 *  @arg\b      URT_IT_LS     : URT line status relationship interrupt.
 *  @arg\b      URT_IT_ERR    : URT error relationship interrupt.
 *  @arg\b      URT_IT_TC     : Transmission complete.(shadow buffer , data register , shift buffer empty)
 *  @arg\b      URT_IT_UG     : URT genernal event relationship interrupt.
 * @param[in]   URT_IT_State:
 * 	@arg\b      ENABLE : Enable interrupt of URT_IT.
 *  @arg\b      DISABLE: Disable interrupt of URT_IT.
 * @return          
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_IT_Config(URT0, (URT_IT_TC | URT_IT_TX | URT_IT_RX) , ENABLE);
    
    or
    
    URT_IT_Config(URT0, 0x000000C4 , ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_IT_Config( URT_Struct* URTX , uint32_t URT_IT, FunctionalState URT_IT_State)
{

    URTX->INT.W = (( URTX->INT.W & (~URT_IT) ) | ( URT_IT * URT_IT_State));
}


/**
 *******************************************************************************
 * @brief	    Read URTx interrupt enable register. 
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      URTX interrupt enable register value.
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetITStatus(URT0);
 * @endcode
 *******************************************************************************
 */
uint32_t URT_GetITStatus(URT_Struct* URTX)
{
    return(URTX->INT.W);
}


/**
 *******************************************************************************
 * @brief	    URTx global all interrupt event are enable or disable control.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_ITEA_State:
 * 	@arg\b      ENABLE : Enable URTX global all interrupt event. 
 *  @arg\b      DISABLE: Disable URTX global all interrupt event.
 * @return       
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_ITEA_Cmd(URT0,ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_ITEA_Cmd( URT_Struct* URTX , FunctionalState URT_ITEA_State)
{
    URTX->INT.W =  ((URTX->INT.W & (~URT_INT_IEA_mask_w)) | (URT_INT_IEA_mask_w * URT_ITEA_State));
}


/**
 *******************************************************************************
 * @brief	    Read all URTx interrupt flag. 
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      URTX all interrupt flag.
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetITAllFlagStatus(URT0);
 * @endcode
 *******************************************************************************
 */
uint32_t URT_GetITAllFlagStatus( URT_Struct* URTX)
{
    uint32_t tmp;
    
    tmp = URTX->STA.W;
    tmp = tmp & (~(URT_EVENT_RXDF | URT_EVENT_RHF));
    
    
    return(tmp);
}


/**
 *******************************************************************************
 * @brief	    Read single URTx interrupt flag. 
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_ITFlag: (The device support which flag refer to the device spec , please)
 *  @arg\b      URT_IT_CALTMO : Baud rate calibration sync field receive time out.
 *  @arg\b      URT_IT_BKTMO  : Break receive time out.
 *  @arg\b      URT_IT_IDTMO  : Idle state time out.
 *  @arg\b      URT_IT_RXTMO  : Receive time out.
 *  @arg\b      URT_IT_TUDR   : URT SPI slave mode transmit underrun.
 *  @arg\b      URT_IT_TXE    : TX error detect.
 *  @arg\b      URT_IT_ROVR   : Receive overrun error.
 *  @arg\b      URT_IT_NCE    : Receive noised character error detect.
 *  @arg\b      URT_IT_FE     : Receive frame error detect.
 *  @arg\b      URT_IT_PE     : Receive parity error detect.
 *  @arg\b      URT_IT_CTS    : CTS change detect.
 *  @arg\b      URT_IT_IDL    : RX idle line detect.
 *  @arg\b      URT_IT_BK     : Break condition detect.
 *  @arg\b      URT_IT_CALC   : Auto baudrate calibration complete.
 *  @arg\b      URT_IT_TMO    : Timeout timer timeout.
 *  @arg\b      URT_IT_BRT    : Baud rate generator timer timeout.
 *  @arg\b      URT_IT_SADR   : Slave address matched.
 *  @arg\b      URT_IT_TX     : Transmit data register empty.
 *  @arg\b      URT_IT_RX     : Receive data register not empty.
 *  @arg\b      URT_IT_LS     : URT line status relationship interrupt.
 *  @arg\b      URT_IT_ERR    : URT error relationship interrupt.
 *  @arg\b      URT_IT_TC     : Transmission complete.(shadow buffer , data register , shift buffer empty)
 *  @arg\b      URT_IT_UG     : URT genernal event relationship interrupt.
 * @return      Single interrupt flag whether  happened or not.
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetITSingleFlagStatus(URT0, URT_IT_RX);
 * @endcode
 *******************************************************************************
 */
DRV_Return URT_GetITSingleFlagStatus( URT_Struct* URTX , uint32_t URT_ITFlag)
{
   
    if((URT_ITFlag & (~((uint32_t)URT_IT_Mask)))!=0)              /*!< URT_ITFlag value over range */
    {
        return(DRV_UnHappened);
    }
    if((URTX->STA.W & URT_ITFlag)==0)
    {
        return(DRV_UnHappened);
    }
    return(DRV_Happened);    
}


/**
 *******************************************************************************
 * @brief	    Clear URTx interrupt flag. 
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_ITFlag: (The device support which flag refer to the device spec , please)
 *  @arg\b      URT_IT_CALTMO : Baud rate calibration sync field receive time out.
 *  @arg\b      URT_IT_BKTMO  : Break receive time out.
 *  @arg\b      URT_IT_IDTMO  : Idle state time out.
 *  @arg\b      URT_IT_RXTMO  : Receive time out.
 *  @arg\b      URT_IT_TUDR   : URT SPI slave mode transmit underrun.
 *  @arg\b      URT_IT_TXE    : TX error detect.
 *  @arg\b      URT_IT_ROVR   : Receive overrun error.
 *  @arg\b      URT_IT_NCE    : Receive noised character error detect.
 *  @arg\b      URT_IT_FE     : Receive frame error detect.
 *  @arg\b      URT_IT_PE     : Receive parity error detect.
 *  @arg\b      URT_IT_CTS    : CTS change detect.
 *  @arg\b      URT_IT_IDL    : RX idle line detect.
 *  @arg\b      URT_IT_BK     : Break condition detect.
 *  @arg\b      URT_IT_CALC   : Auto baudrate calibration complete.
 *  @arg\b      URT_IT_TMO    : Timeout timer timeout.
 *  @arg\b      URT_IT_BRT    : Baud rate generator timer timeout.
 *  @arg\b      URT_IT_SADR   : Slave address matched.
 *  @arg\b      URT_IT_TX     : Transmit data register empty.
 *  @arg\b      URT_IT_RX     : Receive data register not empty.
 *  @arg\b      URT_IT_LS     : URT line status relationship interrupt.
 *  @arg\b      URT_IT_ERR    : URT error relationship interrupt.
 *  @arg\b      URT_IT_TC     : Transmission complete.(shadow buffer , data register , shift buffer empty)
 *  @arg\b      URT_IT_UG     : URT genernal event relationship interrupt.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_ClearITFlag(URT0, (URT_IT_TX | URT_IT_TC) );
    
    or
    
    URT_ClearITFlag(URT0, 0x00000084 );
 * @endcode
 *******************************************************************************
 */
void URT_ClearITFlag( URT_Struct* URTX , uint32_t URT_ITFlag)
{
    URTX->STA.W = URT_ITFlag & (~(URT_EVENT_RXDF|URT_EVENT_RHF));
    
}

/**
 *******************************************************************************
 * @brief	    Read URTX RXDF event flag. 
 * @details     
 *  @arg\b      1. RXDF (receive data byte number is different from previous received data byte number.)
 *  @arg\b      2. First data load to data register the flag is set after IC initial.
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      RXDF event flag status.
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetRxDifferentFlag(URT0);
 * @endcode
 *******************************************************************************
 */
DRV_Return URT_GetRxDifferentFlag( URT_Struct* URTX)
{
    if((URTX->STA.W & URT_EVENT_RXDF)==0)
    {
        return(DRV_UnHappened);
    }
    return(DRV_Happened);
}

/**
 *******************************************************************************
 * @brief	    Read URTX receive hold event flag. 
 * @details     In the condition the shift buffer is held and do not load data 
 *      \n      to shadow buffer until the flag is cleared.
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      URTX receive hold event flag status.
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetRxHoldFlag(URT0);
 * @endcode
 *******************************************************************************
 */
DRV_Return URT_GetRxHoldFlag( URT_Struct* URTX)
{
    if((URTX->STA.W & URT_EVENT_RHF)==0)
    {
        return(DRV_UnHappened);
    }
    return(DRV_Happened);
}


/**
 *******************************************************************************
 * @brief	    Clear URTX receive hold event flag. 
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_ClearRxHoldFlag(URT0);
 * @endcode
 *******************************************************************************
 */
void URT_ClearRxHoldFlag( URT_Struct* URTX)
{
    URTX->STA.W = URT_EVENT_RHF;
}

/**
 *******************************************************************************
 * @brief	    Read URTX IrDa data receive busy event flag. 
 * @details     When detect IrDa signal ,the flag is set and clear after no IrDa signal detect.
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      IrDa data receive busy event flag status.
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetIrDaBusyFlag(URT0);
 * @endcode
 *******************************************************************************
 */
DRV_Return URT_GetIrDaBusyFlag( URT_Struct* URTX)
{
    if((URTX->STA2.W & URT_EVENT_IRBUSYF)==0)
    {
        return(DRV_UnHappened);
    }
    return(DRV_Happened);
}

/**
 *******************************************************************************
 * @brief	    Read send break busy flag.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      Break busy event flag status.
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetBreakBusyFlag(URT0);
 * @endcode
 *******************************************************************************
 */
DRV_Return URT_GetBreakBusyFlag( URT_Struct* URTX)
{
    if((URTX->STA2.W & URT_EVENT_BKBF)==0)
    {
        return(DRV_UnHappened);
    }
    return(DRV_Happened);   
    
}


/**
 *******************************************************************************
 * @brief	    Read RX busy flag.
 * @details     When detect valid start bit, the flag is set and clear after stop bit.
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      RX busy event flag status.
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetRxBusyFlag(URT0);
 * @endcode
 *******************************************************************************
 */
DRV_Return URT_GetRxBusyFlag( URT_Struct* URTX)
{
    if((URTX->STA2.W & URT_EVENT_RXBUSYF) ==0)
    {
        return(DRV_UnHappened);
    }
    return(DRV_Happened);
}

/**
 *******************************************************************************
 * @brief	    Read Receive noised character event flag.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      Receive noised character event flag status.
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetRxNoiseFlag(URT0);
 * @endcode
 *******************************************************************************
 */
DRV_Return URT_GetRxNoiseFlag( URT_Struct* URTX)
{
    if((URTX->STA2.W & URT_EVENT_NCF)==0)
    {
        return(DRV_UnHappened);
    }
    return(DRV_Happened);
    
    
}
///@}


/**
 * @name	Mode
 *   		
 */ 
///@{
/**
 *******************************************************************************
 * @brief	    URT data character configuration.
 * @details     1. URT4 ~ URT7 the following parameter have to same.
 *      \n         - URT_TX_DataLength / URT_RX_DataLength
 *      \n         - URT_TX_StopBits / URT_RX_StopBit
 *      \n      2  URT4 ~ URT7 the following parameter's the some option is linkage.
 *      \n         - URT_RX_Parity is sure URT_Parity_No if URT_TX_Parity is URT_Parity_No.            
 *      \n      3. URT4 ~ URT7 the follwoing parameter can't option.
 *      \n         - URT_TX_DataOrder / URT_RX_DataOrder     : TX / RX data order only LSB.
 *      \n         - URT_TX_DataInverse / URT_RX_DataInverse : It can't data inverse.
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_InitStruct:
 *  @arg\b      URT_TX_DataLength / URT_RX_DataLength:
 *      \n      -URT_DataLength_8: Data length is 8 bit.
 *      \n      -URT_DataLength_7: Data length is 7 bit.
 *  @arg\b      URT_TX_DataOrder / URT_RX_DataOrder:
 *      \n      -URT_DataTyped_LSB: Data order is LSB.
 *      \n      -URT_DataTyped_MSB: Data order is MSB.
 *  @arg\b      URT_TX_Parity / URT_RX_Parity:
 *      \n      -URT_Parity_No   : No parity bit.
 *      \n      -URT_Parity_Even : Parity bit is even.
 *      \n      -URT_Parity_Odd  : Parity bit is odd.
 *      \n      -URT_Parity_All_H: Parity bit always is H.
 *      \n      -URT_Parity_All_L: Parity bit always is L.
 *  @arg\b      URT_TX_StopBits / URT_RX_StopBit:
 *      \n      -URT_StopBits_1_0: Stop bit is 1 bit.
 *      \n      -URT_StopBits_2_0: Stop bit is 2 bit.
 *  @arg\b      URT_TX_DataInverse / URT_RX_DataInverse:
 *      \n      -DISABLE: Data bit no inverse.
 *      \n      -ENABLE : Data bit inverse.
 * @return      No
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_Data_TypeDef URT_Datastruct;
    
    URT_Datastruct.URT_TX_DataLength = URT_DataLength_8;
    URT_Datastruct.URT_RX_DataLength = URT_DataLength_8;
    URT_Datastruct.URT_TX_DataOrder  = URT_DataTyped_LSB;
    URT_Datastruct.URT_RX_DataOrder  = URT_DataTyped_LSB;
    URT_Datastruct.URT_TX_Parity     = URT_Parity_No;
    URT_Datastruct.URT_RX_Parity     = URT_Parity_No;
    URT_Datastruct.URT_TX_StopBits   = URT_StopBits_1_0;
    URT_Datastruct.URT_RX_StopBits   = URT_StopBits_1_0;
    URT_Datastruct.URT_TX_DataInverse= DISABLE;
    URT_Datastruct.URT_RX_DataInverse= DISABLE;
    URT_DataCharacter_Config(URT0,&URT_Datastruct);    
 * @endcode
 *******************************************************************************
 */
void URT_DataCharacter_Config( URT_Struct* URTX, URT_Data_TypeDef* URT_InitStruct)
{
    uint8_t tmp;
    
    URTX->CR1.B[2] = (((uint8_t)URT_InitStruct->URT_TX_DataLength) | 
                      ((uint8_t)URT_InitStruct->URT_TX_DataOrder)  | 
                      ((uint8_t)URT_InitStruct->URT_TX_Parity)     | 
                      ((uint8_t)URT_InitStruct->URT_TX_StopBits));
    
    URTX->CR1.B[0] = (((uint8_t)URT_InitStruct->URT_RX_DataLength) | 
                      ((uint8_t)URT_InitStruct->URT_RX_DataOrder)  | 
                      ((uint8_t)URT_InitStruct->URT_RX_Parity)     | 
                      ((uint8_t)URT_InitStruct->URT_RX_StopBits));

    tmp = URTX->CR4.B[0] & (~(URT_CR4_RDAT_INV_mask_b0|URT_CR4_TDAT_INV_mask_b0));
    
    tmp = tmp | ((((uint8_t)URT_InitStruct->URT_RX_DataInverse) * URT_CR4_RDAT_INV_mask_b0) | (((uint8_t)URT_InitStruct->URT_TX_DataInverse)*URT_CR4_TDAT_INV_mask_b0));
    
    
    URTX->CR4.B[0] = tmp;
    
    
}

 /**
 *******************************************************************************
 * @brief       URT mode select.
 * @details  
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_MDS: 
 *	@arg\b      URT_URT_mode : URT mode.
 *	@arg\b		URT_SYNC_mode: Synchronous/shift register mode.
 *	@arg\b		URT_IDLE_mode: Idle line mode for multi processor.
 *	@arg\b		URT_ADR_mode : Address bit mode for multi processor.
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
    URT_Mode_Select( URT0 , URT_URT_mode);
 * @endcode
 *******************************************************************************
 */
void URT_Mode_Select( URT_Struct* URTX , URT_Mode_TypeDef URT_MDS)
{    
    URTX->CR0.W = (URTX->CR0.W & (~URT_CR0_MDS_mask_w) ) | URT_MDS; 
    
    if(URT_MDS == URT_ADR_mode || URT_MDS == URT_IDLE_mode)
    {
        URTX->MUTE.W = URTX->MUTE.W | URT_MUTE_MUTE_EN_mask_w;
    }
    else
    {
        URTX->MUTE.W = URTX->MUTE.W & (~URT_MUTE_MUTE_EN_mask_w);
    }
}

/**
 *******************************************************************************
 * @brief	    URT data line select.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_DAT_LINE:  
 *  @arg\b      URT_DataLine_2: 2-line seqarated.
 *  @arg\b      URT_DataLine_1: 1-line bidirectional.
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
    URT_DataLine_Select(URT0,URT_DataLine_2);
 * @endcode
 *******************************************************************************
 */
void URT_DataLine_Select( URT_Struct* URTX, URT_DataLine_TypeDef URT_DAT_LINE)
{   
    URTX->CR0.W = ((URTX->CR0.W & (~URT_CR0_DAT_LINE_mask_w)) | URT_DAT_LINE);
}

/**
 *******************************************************************************
 * @brief	    URT half-duplex mode enable or disable.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_HDX_EN:  
 *  @arg\b      DISABLE: URT half-duplex mode disable.
 *  @arg\b      ENABLE : URT half-duplex mode enable.
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
    URT_HalfDuplexMode_Cmd(URT0,ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_HalfDuplexMode_Cmd( URT_Struct* URTX, FunctionalState URT_HDX_EN)
{
 
    URTX->CR0.W = ((URTX->CR0.W & (~URT_CR0_HDX_EN_mask_w)) | ( URT_CR0_HDX_EN_mask_w * URT_HDX_EN));
}


/**
 *******************************************************************************
 * @brief	    URT loop back mode enable or disable.
 * @details     When enable, the received input is taken from transmitted 
 *              output to replace from input pin.
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_LBM_EN:  
 *  @arg\b      DISABLE: Disable loop back mode.
 *  @arg\b      ENABLE : Enable loop back mode ( RX->TX , CTS->RTS)
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
    URT_LoopBackMode_Cmd(URT0,ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_LoopBackMode_Cmd( URT_Struct* URTX , FunctionalState URT_LBM_EN)
{
     
    URTX->CR0.W = ((URTX->CR0.W & (~URT_CR0_LBM_EN_mask_w)) | ( URT_CR0_LBM_EN_mask_w * URT_LBM_EN));
    
}
/**
 *******************************************************************************
 * @brief	    URT TX function enable or disable.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_TX_EN:  
 *  @arg\b      DISABLE: URT TX function disable.
 *  @arg\b      ENABLE : URT TX function enable.
 * @return      No
 * @exception   No
 * @note
 * @par         Example
 * @code
    URT_TX_Cmd(URT0,ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_TX_Cmd( URT_Struct* URTX , FunctionalState URT_TX_EN)
{    
    URTX->CR2.W = (( URTX->CR2.W & (~URT_CR2_TX_EN_mask_w)) | (URT_CR2_TX_EN_mask_w * URT_TX_EN));
}

/**
 *******************************************************************************
 * @brief	    URT RX function enable or disable.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_RX_EN:  
 *  @arg\b      DISABLE: URT RX function disable.
 *  @arg\b      ENABLE : URT RX function enable.
 * @return      No
 * @exception   No
 * @note
 * @par         Example
 * @code
    URT_RX_Cmd(URT0,ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_RX_Cmd( URT_Struct* URTX , FunctionalState URT_RX_EN)
{    
    URTX->CR2.W = (( URTX->CR2.W & (~URT_CR2_RX_EN_mask_w)) | (URT_CR2_RX_EN_mask_w * URT_RX_EN));
}

/**
 *******************************************************************************
 * @brief	    URT RX input signal inverse enable or disable.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_RX_INV:  
 *  @arg\b      DISABLE: Disable RX input signal inverse.
 *  @arg\b      ENABLE : Enable RX input signal inverse.
 * @return      No
 * @exception   No
 * @note
 * @par         Example
 * @code
    URT_RXInverse_Cmd(URT0,ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_RXInverse_Cmd(URT_Struct* URTX , FunctionalState URT_RX_INV)
{
    URTX->CR0.W = (( URTX->CR0.W & (~URT_CR0_RX_INV_mask_w)) | ( URT_CR0_RX_INV_mask_w * URT_RX_INV));
}

/**
 *******************************************************************************
 * @brief	    URT TX output signal inverse enable or disable.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_TX_INV:  
 *  @arg\b      DISABLE: Disable TX input signal inverse.
 *  @arg\b      ENABLE : Enable TX input signal inverse.
 * @return      No
 * @exception   No
 * @note
 * @par         Example
 * @code
    URT_TXInverse_Cmd(URT0,ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_TXInverse_Cmd( URT_Struct* URTX , FunctionalState URT_TX_INV)
{
    URTX->CR0.W = (( URTX->CR0.W & (~URT_CR0_TX_INV_mask_w)) | (URT_CR0_TX_INV_mask_w * URT_TX_INV));
}



/**
 *******************************************************************************
 * @brief	    To select URT receive whether noise data or not.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_NCHAR_DIS:  
 *  @arg\b      DISABLE: Accept noised character.
 *  @arg\b      ENABLE : Skip noise character.
 * @return      No
 * @exception   No
 * @note
 * @par         Example
 * @code
    URT_NoiseDataSkip_Cmd(URT0,ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_NoiseDataSkip_Cmd(URT_Struct* URTX, FunctionalState URT_NCHAR_DIS)
{
    URTX->CR0.W = (( URTX->CR0.W & (~URT_CR0_NCHAR_DIS_mask_w)) | (URT_CR0_NCHAR_DIS_mask_w * URT_NCHAR_DIS));
    
    
}



/**
 *******************************************************************************
 * @brief	    URT function enable or disable.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_EN:  
 *  @arg\b      DISABLE: URT function disable.
 *  @arg\b      ENABLE : URT function enable.
 * @return      No
 * @exception   No
 * @note
 * @par         Example
 * @code
    URT_Cmd(URT0,ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_Cmd( URT_Struct*  URTX, FunctionalState URT_EN) 
{
    URTX->CR0.W = ((URTX->CR0.W & (~URT_CR0_EN_mask_w)) | (URT_CR0_EN_mask_w * URT_EN));
}

///@}





/**
 * @name	Clock
 *   		
 */ 
///@{

/**
 *******************************************************************************
 * @brief	    URT baudrate generator configuration.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_BRGStruct:
 *  @arg\b      URT_InternalClockSource (The following option refer to the device spec , please)
 *      \n      -URT_BDClock_PROC       :
 *      \n      -URT_BDClock_LS         :
 *      \n      -URT_BDClock_Timer00TRGO:
 *      \n      -URT_BDClock_EXT        : (The option MG32F02A132 / MG32F02A072 no support)
 *      \n      -URT_BDClock_NCO0_P0    : (The option MG32F02A132 / MG32F02A072 / MG32F02A032 no support)
 *  @arg\b      URT_BaudRateMode
 *      \n      -URT_BDMode_Separated :
 *      \n      -URT_BDMode_Combined  :
 *  @arg\b      URT_BRCounterClock_TypeDef
 *  @arg\b      URT_PrescalerCounterReload :
 *  @arg\b      URT_BaudRateCounterReload  :
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_BRG_TypeDef URT_BRGStruct;
    
    URT_BRGStruct.URT_InternalClockSource = URT_BDClock_PROC;
    URT_BRGStruct.URT_BaudRateMode = URT_BDMode_Separated;
    URT_BRGStruct.URT_BaudRateCounterReload = 214;
    URT_BRGStruct.URT_PrescalerCounterReload = 14;
    URT_BaudRateGenerator_Config(URT0,&URT_BRGStruct);    
 * @endcode
 *******************************************************************************
 */
void URT_BaudRateGenerator_Config( URT_Struct* URTX , URT_BRG_TypeDef* URT_BRGStruct)
{
    URTX->CLK.W = ((URTX->CLK.W & (~(URT_CLK_CK_SEL_mask_w| URT_CLK_BR_MDS_mask_w))) | 
                  (((uint32_t)URT_BRGStruct->URT_BaudRateMode)         | 
                   ((uint32_t)URT_BRGStruct->URT_InternalClockSource)));
    URTX->RLR.B[0] = URT_BRGStruct->URT_BaudRateCounterReload;
    URTX->RLR.B[1] = URT_BRGStruct->URT_PrescalerCounterReload;
}

/**
 *******************************************************************************
 * @brief	    URT select baudrate generator mode.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_BD_MDS:
 *  @arg\b      URT_BDMode_Separated  : Separated PSC and CNT counters for UART baudrate generator.
 *  @arg\b      URT_BDMode_Combined   : Combine to a linear counter for general using timer.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_BaudRateGeneratorMode_Select(URT0 , URT_BDMode_Separated);
 * @endcode
 *******************************************************************************
 */
void URT_BaudRateGeneratorMode_Select( URT_Struct* URTX , URT_BDMode_TypeDef URT_BD_MDS)
{ 
    URTX->CLK.W = (( URTX->CLK.W & (~URT_CLK_BR_MDS_mask_w)) | URT_BD_MDS);
    
}

/**
 *******************************************************************************
 * @brief	    URT select baudrate generator clock source.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_CK_SEL:
 *  @arg\b      URT_BDClock_PROC        : CK_URT0_PR process clock from CSC.
 *  @arg\b      URT_BDClock_LS          : 
 *  @arg\b      URT_BDClock_Timer00TRGO : Timer00 TRGO.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_BaudRateGeneratorClock_Select(URT0 , URT_BDClock_PROC);
 * @endcode
 *******************************************************************************
 */
void URT_BaudRateGeneratorClock_Select( URT_Struct* URTX , URT_BDClock_TypeDef URT_CK_SEL)
{
    URTX->CLK.W = (( URTX->CLK.W & (~URT_CLK_CK_SEL_mask_w)) | URT_CK_SEL);
}

#if defined(URT_CLK_BR_CKS_mask_w)
/**
 *******************************************************************************
 * @brief	    URT baudrate counter clock source select.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_BR_CKS:
 *  @arg\b      URT_BRCountClock_PSC        : Clock prescaler output.
 *  @arg\b      URT_BRCountClock_CK_URT     : UART internal clock input.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_BaudRateCounterClockSource_Select(URT0 , URT_BRCountClock_PSC);
 * @endcode
 *******************************************************************************
 */
void URT_BaudRateCounterClockSource_Select( URT_Struct* URTX , URT_BRCounterClock_TypeDef URT_BR_CKS)
{
    URTX->CLK.W = (( URTX->CLK.W & (~URT_CLK_BR_CKS_mask_w)) | URT_BR_CKS);
}
#endif

/**
 *******************************************************************************
 * @brief	    Get URT baud rate generator prescaler reload register.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      Baud rate generator prescaler reload register value.
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetBaudRateGeneratorPreReload( URT0);
 * @endcode
 *******************************************************************************
 */
uint8_t URT_GetBaudRateGeneratorPreReload( URT_Struct* URTX)
{
    return(URTX->RLR.B[1]);
}

/**
 *******************************************************************************
 * @brief	    Get URT baud rate generator counter reload register.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      Baud rate generator counter reload register value.
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetBaudRateGeneratorCountReload( URT0);
 * @endcode
 *******************************************************************************
 */
uint8_t URT_GetBaudRateGeneratorCountReload( URT_Struct* URTX)
{
    return(URTX->RLR.B[0]);
}


/**
 *******************************************************************************
 * @brief	    Get URT baud rate generator prescaler register.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      Baud rate generator prescaler count register value .
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetBaudRateGeneratorPre( URT0);
 * @endcode
 *******************************************************************************
 */
uint8_t URT_GetBaudRateGeneratorPre( URT_Struct* URTX)
{
    return(URTX->CNT.B[1]);
}

/**
 *******************************************************************************
 * @brief	    Get URT baud-rate clock counter value.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      Baud rate generator count register value .
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetBaudRateGeneratorCount( URT0);
 * @endcode
 *******************************************************************************
 */
uint8_t URT_GetBaudRateGeneratorCount( URT_Struct* URTX)
{
    return(URTX->CNT.B[0]);
}

/**
 *******************************************************************************
 * @brief	    URT baudrate generator enable or disable .
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_BR_EN:
 *  @arg\b      DISABLE  : Disable baudrate generator.
 *  @arg\b      ENABLE   : Enable baudrate generator.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_BaudRateGenerator_Cmd(URT0 , ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_BaudRateGenerator_Cmd( URT_Struct* URTX , FunctionalState URT_BR_EN)
{
    URTX->CLK.W = (( URTX->CLK.W & (~URT_CLK_BR_EN_mask_w)) | (URT_CLK_BR_EN_mask_w * URT_BR_EN));
}

/**
 *******************************************************************************
 * @brief	    URTX_CLK clock source select.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_CLK_CKS:
 *  @arg\b      URT_CK_OUT : Signal from clock output divider.
 *  @arg\b      URT_CK_SC  : Signal from clock input prescaler.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_CLKSignalSource_Select(URT0 , URT_CK_SC);
 * @endcode
 *******************************************************************************
 */
void URT_CLKSignalSource_Select( URT_Struct* URTX , URT_CLKSource_TypeDef URT_CLK_CKS)
{
    URTX->CLK.W = ((URTX->CLK.W & (~ URT_CLK_CLK_CKS_mask_w)) | URT_CLK_CKS);
}

/**
 *******************************************************************************
 * @brief	    URTX_CLK signal output enable or disable.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_CLK_EN:
 *  @arg\b      DISABLE  : URT_CLK signal disable.
 *  @arg\b      ENABLE   : URT_CLK signal enable.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_CLKSignal_Cmd(URT0 , ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_CLKSignal_Cmd( URT_Struct* URTX , FunctionalState URT_CLK_EN)
{
    URTX->CLK.W = (( URTX->CLK.W & (~URT_CLK_CLK_EN_mask_w)) | ( URT_CLK_CLK_EN_mask_w * URT_CLK_EN));
}



/**
 *******************************************************************************
 * @brief	    URT baudrate timer timerout signal output state.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_BRO_STA:
 *  @arg\b      CLR : URTX_BRO is logical 0.
 *  @arg\b      SET : URTX_BRO is logical 1.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_CtrlBROSignalStatus_SW(URT0 , SET);
 * @endcode
 *******************************************************************************
 */
void URT_CtrlBROSignalStatus_SW( URT_Struct* URTX , BitAction URT_BRO_STA)
{    
    URTX->CLK.W = (( (URTX->CLK.W & (~URT_CLK_BRO_STA_mask_w)) | URT_CLK_BRO_LCK_mask_w) | ( URT_CLK_BRO_STA_mask_w * URT_BRO_STA));
}

/**
 *******************************************************************************
 * @brief	    URTX PSC clock output signal state.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_CKO_STA:
 *  @arg\b      CLR : URT_CLK is logical 0.
 *  @arg\b      SET : URT_CLK is logical 1.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_CtrlCLKSignalStatus_SW(URT0 , SET);
 * @endcode
 *******************************************************************************
 */
void URT_CtrlCLKSignalStatus_SW( URT_Struct* URTX , BitAction URT_CKO_STA)
{ 
    URTX->CLK.W = ((( URTX->CLK.W & (~URT_CLK_CKO_STA_mask_w)) | URT_CLK_CKO_LCK_mask_w) | (URT_CLK_CKO_STA_mask_w * URT_CKO_STA));
}


/**
 *******************************************************************************
 * @brief	    URT select TX clock source.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_TX_CKS:
 *  @arg\b      URT_TXClock_Internal   : URT TX clock source from baudrate genertor.
 *  @arg\b      URT_TXClock_Timer01TRGO: URT TX clock source from timer01 TRGO.
 *  @arg\b      URT_TXClock_Timer10TRGO: URT TX clock source from timer10 TRGO.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_TXClockSource_Select(URT0 , URT_TXClock_Internal);
 * @endcode
 *******************************************************************************
 */
void URT_TXClockSource_Select( URT_Struct* URTX , URT_TXClock_TypeDef URT_TX_CKS)
{
    URTX->CLK.W = (( URTX->CLK.W & (~URT_CLK_TX_CKS_mask_w)) | URT_TX_CKS);
}


/**
 *******************************************************************************
 * @brief	    URT select RX clock source.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_RX_CKS:
 *  @arg\b      URT_RXClock_Internal   : URT TX clock source from baudrate genertor.
 *  @arg\b      URT_RXClock_Timer01TRGO: URT TX clock source from timer01 TRGO.
 *  @arg\b      URT_RXClock_Timer10TRGO: URT TX clock source from timer10 TRGO.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_RXClockSource_Select(URT0 , URT_RXClock_Internal);
 * @endcode
 *******************************************************************************
 */
void URT_RXClockSource_Select( URT_Struct* URTX , URT_RXClock_TypeDef URT_RX_CKS)
{   
    URTX->CLK.W = (( URTX->CLK.W & (~URT_CLK_RX_CKS_mask_w)) | URT_RX_CKS);
}


/**
 *******************************************************************************
 * @brief	    URT TX data oversampling samples select.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_TXOS_NUM:
 *  @arg\b      (0 ~ 31)
 *      \n      -In SC and SPI mode the valid value is from 1 to 31 for oversampling number from 2 to 32.
 *      \n      -The other mode the valid value is from 7 to 31 for oversampling number from  8 to 32.
 * @return      DRV_Return:
 *  @arg\b      DRV_Failure : URT TX oversampling setting fail.
 *  @arg\b      DRV_Success : URT TX oversampling setting success.
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_TXOverSamplingSampleNumber_Select( URT0, 7);
 * @endcode
 *******************************************************************************
 */
DRV_Return URT_TXOverSamplingSampleNumber_Select( URT_Struct* URTX , uint8_t URT_TXOS_NUM)
{
    if(URT_TXOS_NUM>31)
    {
        return(DRV_Failure);
    }
    URTX->CR1.B[3] = URT_TXOS_NUM;
    return(DRV_Success);
}


/**
 *******************************************************************************
 * @brief	    URT RX data oversampling samples select.
 * @details     1. URT4 - URT7 the function no effect.
 *      \n      2. URT4 - URT7 RX oversampling samples select the same as TX oversampling 
 *     \n          samples select.
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_RXOS_NUM:
 *  @arg\b      (0 ~ 31)
 *      \n      -The valid value is from 7 to 31 for oversampling samples from 8 to 32.
 * @return      DRV_Return:
 *  @arg\b      DRV_Failure : URT RX oversampling setting fail.
 *  @arg\b      DRV_Success : URT RX oversampling setting success.
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_RXOverSamplingSampleNumber_Select( URT0, 7);
 * @endcode
 *******************************************************************************
 */
DRV_Return URT_RXOverSamplingSampleNumber_Select( URT_Struct* URTX , uint8_t URT_RXOS_NUM)
{
    if(URT_RXOS_NUM>31)
    {
        return(DRV_Failure);
    }
    URTX->CR1.B[1] = URT_RXOS_NUM;
    return(DRV_Success);
}    


/**
 *******************************************************************************
 * @brief	    URT RX data oversampling majority vote select.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_OS_MDS:
 *  @arg\b      URT_RXSMP_3TIME: Three sample bits method.
 *  @arg\b      URT_RXSMP_1TIME: One sample bit method and noise free.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_RXOverSamplingMode_Select( URT0, URT_RXSMP_3TIME);
 * @endcode
 *******************************************************************************
 */
void URT_RXOverSamplingMode_Select( URT_Struct* URTX , URT_RXSMP_TypeDef URT_OS_MDS)
{
    URTX->CR0.W = (( URTX->CR0.W & (~URT_CR0_OS_MDS_mask_w)) | URT_OS_MDS);
}

///@}





/**
 * @name  Timerout Timer
          Timerout timer relationship driver.
 */
///@{


/**
 *******************************************************************************
 * @brief	    URT Timeout timer function enable or disable.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_TMO_EN:  
 *  @arg\b      DISABLE: URT timeout timer function disable.
 *  @arg\b      ENABLE : URT timeout timer function enable.
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
    URT_TimeroutTimer_Cmd(URT0,ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_TimeroutTimer_Cmd( URT_Struct* URTX , FunctionalState URT_TMO_EN)
{ 
    URTX->TMOUT.W = (( URTX->TMOUT.W & (~URT_TMOUT_TMO_EN_mask_w)) | (URT_TMOUT_TMO_EN_mask_w * URT_TMO_EN));
}

/**
 *******************************************************************************
 * @brief	    URT timeout timer reset.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
    URT_TriggerTimeoutTimerRst_SW(URT0);
 * @endcode
 *******************************************************************************
 */
void URT_TriggerTimeoutTimerRst_SW( URT_Struct* URTX )
{    
    URTX->TMOUT.W = (URTX->TMOUT.W | URT_TMOUT_TMO_RST_mask_w);
}


/**
 *******************************************************************************
 * @brief	    URT Timeout timer mode select.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_TMO_MDS:  
 *  @arg\b      URT_TMOMDS_URT     : Timeout timer mode is URT mode. ( URT detect timeout using)
 *  @arg\b      URT_TMOMDS_General : Timeout timer mode is general mode. ( General timer using )
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
    URT_TimeoutMode_Select( URT0, URT_TMOMDS_URT);
 * @endcode
 *******************************************************************************
 */
void URT_TimeoutMode_Select( URT_Struct* URTX , URT_TMOMDS_TypeDef URT_TMO_MDS)
{
    URTX->TMOUT.W = (( URTX->TMOUT.W & (~URT_TMOUT_TMO_MDS_mask_w)) | URT_TMO_MDS);
}

/**
 *******************************************************************************
 * @brief	    URT Timeout timer clock source select.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_TMO_CKS:  
 *  @arg\b      URT_TMOCLK_BitTime : URT BIT clock.
 *  @arg\b      URT_TMOCLK_CK_URTX : URT clock input.
 *  @arg\b      URT_TMOCLK_Noise   : Noise (Noise bit receive event)
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
    URT_TimeoutTimerClockSource_Select(URT0,URT_TMOCLK_BitTime);
 * @endcode
 *******************************************************************************
 */
void URT_TimeoutTimerClockSource_Select( URT_Struct* URTX , URT_TMOCLK_TypeDef URT_TMO_CKS)
{
    URTX->TMOUT.W = (( URTX->TMOUT.W & (~URT_TMOUT_TMO_CKS_mask_w)) | URT_TMO_CKS); 
}



/**
 *******************************************************************************
 * @brief	    URT idle line detect threshold value by using receive bit time.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_DET_IDLE: (0 ~ 255)
 *  @arg\b      The value (0 ~ 255) indicates (1 ~ 256) bit time.
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
    URT_IdleDetect_Select(URT0 , 48);
 * @endcode
 *******************************************************************************
 */
void URT_IdleDetect_Select( URT_Struct* URTX , uint8_t URT_DET_IDLE)
{
    URTX->CR3.B[1] = URT_DET_IDLE;
}


/**
 *******************************************************************************
 * @brief	    URT Idle timerout detect.
 * @details     1.When enable the function have to enable Timeout timer and Timeout
 *                timer mode is no general mode.
 *      \n      2.The detect starting after STOP bit of the last character.
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_IDTMO_EN:
 *  @arg\b      DISABLE: Disable idle timeout detect.
 *  @arg\b      ENABLE : Enable idle timeout detect.
 * @param[in]   URT_IDTMO_TH: (0 ~ 65535)
 *  @arg\b      The value : It is 0 ~ 65535 timeout timer clock.
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
    URT_IdleTimeoutDetect_Config(URT0 , ENABLE , 65535);
    
    or 
    
    URT_IdleTimeoutDetect_Config(URT0 , DISABLE , XX);        // XX : it can to write any value , beacse it don't care in disable. 

 * @endcode
 *******************************************************************************
 */
void URT_IdleTimeoutDetect_Config( URT_Struct* URTX , FunctionalState URT_IDTMO_EN , uint16_t URT_IDTMO_TH)
{ 
    if(URT_IDTMO_EN == DISABLE)
    {
        URTX->TMOUT.W = URTX->TMOUT.W & (~URT_TMOUT_IDTMO_EN_mask_w);
        return;
    }
    URTX->TMOUT2.H[0] = URT_IDTMO_TH;
    URTX->TMOUT.W = URTX->TMOUT.W | (URT_TMOUT_IDTMO_EN_mask_w);
}

/**
 *******************************************************************************
 * @brief	    URT RX timeout detect.
 * @details     1.When enable the function have to enable Timeout timer and Timeout
 *                timer mode is no general mode.
 *      \n      2.The detect starting after STOP bit of the last character.
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_RXTMO_EN:
 *  @arg\b      DISABLE: Disable RX timeout detect.
 *  @arg\b      ENABLE : Enable RX timeout detect.
 * @param[in]   URT_RXTMO_TH: (0 ~ 255)
 *  @arg\b      The value: Indicates ( value + 1) * 8 timeout timer clock.
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
    URT_RXTimeoutDetect_Config(URT0 , ENABLE , 255);
    
    or 
    
    URT_RXTimeoutDetect_Config(URT0 , DISABLE , XX);        // XX : it can to write any value , beacse it don't care in disable. 

 * @endcode
 *******************************************************************************
 */
void URT_RXTimeoutDetect_Config( URT_Struct* URTX , FunctionalState URT_RXTMO_EN , uint8_t URT_RXTMO_TH)
{
    if(URT_RXTMO_EN == DISABLE)
    { 
        URTX->TMOUT.W = URTX->TMOUT.W & (~URT_TMOUT_RXTMO_EN_mask_w);
        return;
    }
    URTX->TMOUT.B[2] = URT_RXTMO_TH;
    URTX->TMOUT.W = URTX->TMOUT.W | URT_TMOUT_RXTMO_EN_mask_w;
    
    
}


/**
 *******************************************************************************
 * @brief	    URT break timeout detect.
 * @details     1.When enable the function have to enable Timeout timer and Timeout
 *                timer mode is no general mode.
 *      \n      2.The detect starting after URT_BKF bit asserting( Hardware detect 
 *                break character.)
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_BKTMO_EN:
 *  @arg\b      DISABLE: Disable break timeout detect.
 *  @arg\b      ENABLE : Enable break timeout detect.
 * @param[in]   URT_BKTMO_TH: (0 ~ 15)
 *  @arg\b      The value: Indicates (URT_BKTMO_TH + 1) timeout timer clock.
 * @return    
 *  @arg\b      DRV_Failure: URT_BKTMO_TH value over range.
 *  @arg\b      DRV_Success: Break timeout detect configure success.
 * @exception   No
 * @note
 * @par         Example
 * @code
    URT_BreakTimeoutDetect_Config(URT0 , ENABLE , 15);
    
    or 
    
    URT_BreakTimeoutDetect_Config(URT0 , DISABLE , XX);        // XX : it can to write any value , beacse it don't care in disable. 

 * @endcode
 *******************************************************************************
 */
DRV_Return URT_BreakTimeoutDetect_Config( URT_Struct* URTX , FunctionalState URT_BKTMO_EN , uint8_t URT_BKTMO_TH)
{
    if(URT_BKTMO_EN == DISABLE)
    {
        URTX->TMOUT.W = URTX->TMOUT.W & (~URT_TMOUT_BKTMO_EN_mask_w);
        return(DRV_Success);
    }
    if(URT_BKTMO_TH > 15)
    {
        return(DRV_Failure);
    }    
    URTX->TMOUT.W = (((URTX->TMOUT.W & (~URT_TMOUT_BKTMO_TH_mask_w)) | URT_TMOUT_BKTMO_EN_mask_w) | (((uint32_t)URT_BKTMO_TH) << URT_TMOUT_BKTMO_TH_shift_w));
    return(DRV_Success);
}



/**
 *******************************************************************************
 * @brief	    URT calibration timeout detect.
 * @details     1.When enable the function have to enable Timeout timer and Timeout
 *                timer mode is no general mode.
 *              2.The detect starting after starting to detect SYNC.
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_CALTMO_EN:
 *  @arg\b      DISABLE: Disable calibration timeout detect.
 *  @arg\b      ENABLE : Enable calibration timeout detect.
 * @param[in]   URT_CALTMO_TH: (0 ~ 15)
 *  @arg\b      0              : Indicate 0xFF timeout timer clock.
 *  @arg\b      The other value: Indicates (URT_CALTMO_TH * 0x10) timeout timer clock.
 * @return    
 *  @arg\b      DRV_Failure: URT_CALTMO_TH value over range.
 *  @arg\b      DRV_Success: Calibration timeout detect configure success.
 * @exception   No
 * @note
 * @par         Example
 * @code
    URT_CalibrationTimeoutDetect_Config(URT0 , ENABLE , 15);
    
    or 
    
    URT_CalibrationTimeoutDetect_Config(URT0 , DISABLE , XX);        // XX : it can to write any value , beacse it don't care in disable. 

 * @endcode
 *******************************************************************************
 */
DRV_Return URT_CalibrationTimeoutDetect_Config( URT_Struct* URTX , FunctionalState URT_CALTMO_EN , uint8_t URT_CALTMO_TH)
{
    if(URT_CALTMO_EN == DISABLE)
    {
        URTX->TMOUT.W = URTX->TMOUT.W & (~URT_TMOUT_CALTMO_EN_mask_w);
        return(DRV_Success);
    }
    if(URT_CALTMO_TH > 15)
    {
        return(DRV_Failure);
    }    
    URTX->TMOUT.W = ((( URTX->TMOUT.W & (~URT_TMOUT_CALTMO_TH_mask_w)) | URT_TMOUT_CALTMO_EN_mask_w) | (((uint32_t)URT_CALTMO_TH) << URT_TMOUT_CALTMO_TH_shift_w));
    return(DRV_Success);
}



/**
 *******************************************************************************
 * @brief	    URTX URT_TMO output signal state control.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_TMO_STA:
 *  @arg\b      CLR : URT_TMO output signal is logical 0.
 *  @arg\b      SET : URT_TMO output signal is logical 1.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_CtrlTMOSignalStatus_SW(URT0 , SET);
 * @endcode
 *******************************************************************************
 */
void URT_CtrlTMOSignalStatus_SW( URT_Struct* URTX , BitAction URT_TMO_STA) 
{


    URTX->TMOUT.W = ((URTX->TMOUT.W & (~URT_TMOUT_TMO_STA_mask_w)) | URT_TMOUT_TMO_LCK_mask_w) | (URT_TMOUT_TMO_STA_mask_w * URT_TMO_STA);

}

/**
 *******************************************************************************
 * @brief	    URTX get timeout timer counter value.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      Timeout timer counter value.
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetTimeoutTimerCounter(URT0);
 * @endcode
 *******************************************************************************
 */
uint16_t URT_GetTimeoutTimerCounter( URT_Struct* URTX)
{
    return(URTX->TMOUT2.H[1]);
}

/**
 *******************************************************************************
 * @brief	    URTX set timeout timer counter value.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_TMO_CNT: Set timeout timer counter value.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_SetTimeoutTimerCounter(URT0,65535);
 * @endcode
 *******************************************************************************
 */
void URT_SetTimeoutTimerCounter( URT_Struct* URTX, uint16_t URT_TMO_CNT)
{
    URTX->TMOUT2.H[1] = URT_TMO_CNT;
}



/**
 *******************************************************************************
 * @brief	    URTX get timeout timer reload value.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      Timeout timer reload value.
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetTimeoutTimerReload(URT0);
 * @endcode
 *******************************************************************************
 */
uint16_t URT_GetTimeoutTimerReload( URT_Struct* URTX)
{
    return(URTX->TMOUT2.H[0]);
}

/**
 *******************************************************************************
 * @brief	    URTX Set timeout timer compare value.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_TMO_RELOAD: Set timeout timer compare value if timerout timer mode is general mode.
 * @return      
 * @exception   No
 * @note        To use in timerout timer mode is general mode.
 * @par         Example
 * @code
    URT_SetTimeoutTimerCompare(URT0,65535);
 * @endcode
 *******************************************************************************
 */
void URT_SetTimeoutTimerCompare( URT_Struct* URTX, uint16_t URT_TMO_RELOAD)
{
    URTX->TMOUT2.H[0] = URT_TMO_RELOAD;
}
///@}










/**
 * @name Data Control
         URT data control relationship driver.
 */
///@{




/**
 *******************************************************************************
 * @brief	    Get URTX TX shadow buffer remained data byte number.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      Transmission shadow buffer remained level.
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetTXShadowBufferLevel(URT0);
 * @endcode
 *******************************************************************************
 */
uint8_t URT_GetTXShadowBufferLevel( URT_Struct* URTX)
{
    return(URTX->STA2.MBIT.TX_LVL);
}

/**
 *******************************************************************************
 * @brief       Get URTX RX shadow buffer level now.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      Receive shadow buffer level.
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetRXShadowBufferLevel(URT0);
 * @endcode
 *******************************************************************************
 */
uint8_t URT_GetRXShadowBufferLevel( URT_Struct* URTX)
{
    return(URTX->STA2.MBIT.RX_LVL);
}


/**
 *******************************************************************************
 * @brief       URT TX data clear.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_ClearTXData(URT0);
 * @endcode
 *******************************************************************************
 */
void URT_ClearTXData( URT_Struct* URTX)
{
    URTX->CR4.W = URTX->CR4.W | URT_CR4_TDAT_CLR_mask_w;
}


/**
 *******************************************************************************
 * @brief       URT RX data clear.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_ClearRXData(URT0);
 * @endcode
 *******************************************************************************
 */
void URT_ClearRXData( URT_Struct* URTX)
{
    URTX->CR4.W = URTX->CR4.W | URT_CR4_RDAT_CLR_mask_w;
}



/**
 *******************************************************************************
 * @brief	    Get URTX TX data register remained data byte number.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetTXDataRegLevel(URT0);
 * @endcode
 *******************************************************************************
 */
uint8_t URT_GetTXDataRegLevel( URT_Struct* URTX)
{
    return(URTX->CR4.MBIT.TNUM);
}


/**
 *******************************************************************************
 * @brief       URT shadow buffer threshold select.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_RX_TH:
 *  @arg\b      URT_RXTH_1BYTE : 1 byte
 *  @arg\b      URT_RXTH_2BYTE : 2 byte
 *  @arg\b      URT_RXTH_3BYTE : 3 byte
 *  @arg\b      URT_RXTH_4BYTE : 4 byte
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_RXShadowBufferThreshold_Select( URT0, URT_RXTH_4BYTE);
 * @endcode
 *******************************************************************************
 */
void URT_RXShadowBufferThreshold_Select( URT_Struct* URTX , URT_RXTH_TypeDef URT_RX_TH)
{
    URTX->CR0.W = (( URTX->CR0.W & (~URT_CR0_RX_TH_mask_w)) | URT_RX_TH);    
}


/**
 *******************************************************************************
 * @brief       Get URTX RX shadow buffer load to data register data byte number.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      Data register have data byte number now.
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetRXDataRegLevel(URT0);
 * @endcode
 *******************************************************************************
 */
uint8_t URT_GetRXDataRegLevel( URT_Struct* URTX)
{
    return(URTX->CR4.MBIT.RNUM);
}


/**
 *******************************************************************************
 * @brief	    URTX get received data register.
 * @details     read the register will clear RXF.
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      Receive data.
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetRXData(URT0);
 * @endcode
 *******************************************************************************
 */
uint32_t URT_GetRXData( URT_Struct* URTX)
{
    return(URTX->RDAT.W);
}

/**
 *******************************************************************************
 * @brief	    Get URTX capture data 
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      Capture data.
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetRXData(URT0);
 * @endcode
 *******************************************************************************
 */
uint8_t URT_GetCaptureData( URT_Struct* URTX)
{
    return(URTX->RCAP.B[0]);
}

/**
 *******************************************************************************
 * @brief	    Get URTX capture status bit value.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_RCAP:
 *  @arg\b      URT_RCAP_ADR : capture address bit value.
 *  @arg\b      URT_RCAP_PAR : capture parity bit value.
 *  @arg\b      URT_RCAP_STP : capture stop bit value.
 * @return      Capture status bit value.
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetCaptureStatusBit( URT0, URT_RCAP_PAR);
 * @endcode
 *******************************************************************************
 */
uint8_t URT_GetCaptureStatusBit( URT_Struct* URTX , URT_RCAP_TypeDef URT_RCAP)
{
    if((URTX->RCAP.W & URT_RCAP)==0)
    {
        return(0); 
    }
    return(1);
}

/**
 *******************************************************************************
 * @brief	    Get URTX RX shift buffer status bit value.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_SBF_StatusBit:
 *  @arg\b      URT_SBUF_ADR : Shift buffer address bit value.
 *  @arg\b      URT_SBUF_PAR : Shift buffer parity bit value.
 * @return      RX shift buffer status bit value.
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetRXShiftBufferStatusBit( URT0, URT_SBUF_PAR);
 * @endcode
 *******************************************************************************
 */
uint8_t URT_GetRXShiftBufferStatusBit( URT_Struct* URTX , URT_SBUFBit_TypeDef URT_SBF_StatusBit)
{
    if((URTX->STA2.W & URT_SBF_StatusBit)==0)
    {
        return(0);
    }
    return(1);
}

/**
 *******************************************************************************
 * @brief	    Get URTX TX shift buffer data. 
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      TX shift buffer data.
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetTXShiftBufferData(URT0);
 * @endcode
 *******************************************************************************
 */
uint8_t URT_GetTXShiftBufferData( URT_Struct* URTX)
{
    return(URTX->SBUF.B[1]);
}

/**
 *******************************************************************************
 * @brief	    Get URTX RX shift buffer data. 
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      RX shift buffer data.
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetRXShiftBufferData(URT0);
 * @endcode
 *******************************************************************************
 */
uint8_t URT_GetRXShiftBufferData( URT_Struct* URTX)
{
    return(URTX->SBUF.B[0]);    
}



/**
 *******************************************************************************
 * @brief	    URTX RTS hardware flow control enable / disable.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_RTS_EN:
 *  @arg\b      DISABLE  : Disable RTS hardware flow control.
 *  @arg\b      ENABLE   : Enable RTS hardware flow control.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_RTS_Cmd(URT0 , ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_RTS_Cmd( URT_Struct* URTX, FunctionalState  URT_RTS_EN) 
{
    URTX->HFC.W = (( URTX->HFC.W & (~URT_HFC_RTS_EN_mask_w)) | (URT_HFC_RTS_EN_mask_w * URT_RTS_EN));
}

/**
 *******************************************************************************
 * @brief	    URTX RTS signal inverse enable / disable.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_RTS_INV:
 *  @arg\b      DISABLE  : Disable RTS signal inverse disable.
 *  @arg\b      ENABLE   : Enable RTS signal inverse enable.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_RTSInverse_Cmd(URT0 , ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_RTSInverse_Cmd( URT_Struct* URTX, FunctionalState URT_RTS_INV)
{    
    URTX->HFC.W = (( URTX->HFC.W & (~URT_HFC_RTS_INV_mask_w)) | (URT_HFC_RTS_INV_mask_w * URT_RTS_INV));
}



/**
 *******************************************************************************
 * @brief	    URTX RTS output control data bit by software.
 * @details     The driver is no effect when URT_RTS_Cmd function enable.
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_RTS_OUT:
 *  @arg\b      CLR  : RTS output logical 0.
 *  @arg\b      SET  : RTS output logical 1.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_CtrlRTS_SW(URT0 , SET);
 * @endcode
 *******************************************************************************
 */
void URT_CtrlRTS_SW( URT_Struct* URTX , BitAction URT_RTS_OUT)
{   
    URTX->HFC.W = (( URTX->HFC.W & (~URT_HFC_RTS_OUT_mask_w)) | ( URT_HFC_RTS_OUT_mask_w * URT_RTS_OUT)); 
}

/**
 *******************************************************************************
 * @brief	    URTX CTS hardware flow control enable / disable.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_CTS_EN:
 *  @arg\b      DISABLE  : Disable CTS hardware flow control.
 *  @arg\b      ENABLE   : Enable CTS hardware flow control.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_CTS_Cmd(URT0 , ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_CTS_Cmd( URT_Struct* URTX, FunctionalState URT_CTS_EN)
{
    URTX->HFC.W = (( URTX->HFC.W & (~URT_HFC_CTS_EN_mask_w)) | ( URT_HFC_CTS_EN_mask_w * URT_CTS_EN));
}


/**
 *******************************************************************************
 * @brief	    Get URTX CTS line status.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      
 *  @arg\b      DRV_Logic0: CTS line status is logic 0
 *  @arg\b      DRV_Logic1: CTS line status is logic 1
 * @exception   No
 * @note 
 * @par         Example
 * @code
    tmp = URT_GetCTSLineStatus(URT0);
 * @endcode
 *******************************************************************************
 */
DRV_Return URT_GetCTSLineStatus( URT_Struct* URTX)
{
    uint32_t tmp;
    
    tmp = URTX->STA2.W;
    if( (tmp & URT_STA2_CTS_mask_w) == 0)
    {
        return(DRV_Logic0);
    }
    return(DRV_Logic1);
}

/**
 *******************************************************************************
 * @brief	    URTX CTS signal inverse enable / disable.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_CTS_INV:
 *  @arg\b      DISABLE  : Disable CTS signal inverse disable.
 *  @arg\b      ENABLE   : Enable CTS signal inverse enable.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_CTSInverse_Cmd(URT0 , ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_CTSInverse_Cmd( URT_Struct* URTX , FunctionalState URT_CTS_INV)
{    
    URTX->HFC.W = (( URTX->HFC.W & (~URT_HFC_CTS_INV_mask_w)) | ( URT_HFC_CTS_INV_mask_w * URT_CTS_INV));   
}


/**
 *******************************************************************************
 * @brief	    URTX DE signal output enable / disable.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_DE_EN:
 *  @arg\b      DISABLE  : Disable DE signal output.
 *  @arg\b      ENABLE   : Enable DE signal output.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_DE_Cmd(URT0 , ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_DE_Cmd( URT_Struct* URTX , FunctionalState URT_DE_EN)
{    
    URTX->CR0.W = (( URTX->CR0.W & (~URT_CR0_DE_EN_mask_w)) | (URT_CR0_DE_EN_mask_w * URT_DE_EN));
}

/**
 *******************************************************************************
 * @brief	    URTX DE signal inverse output enable / disable.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_DE_INV:
 *  @arg\b      DISABLE  : Disable DE signal inverse output.
 *  @arg\b      ENABLE   : Enable DE signal inverse output.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_DEInverse_Cmd(URT0 , ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_DEInverse_Cmd( URT_Struct* URTX , FunctionalState URT_DE_INV)
{    
    URTX->CR0.W = (( URTX->CR0.W & (~URT_CR0_DE_INV_mask_w)) | (URT_CR0_DE_INV_mask_w * URT_DE_INV));
}


/**
 *******************************************************************************
 * @brief	    URTX DE guard time .
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_DE_GT:
 *  @arg\b      URT_DEGT_1_4 : DE guard time is 1/4 bit time.
 *  @arg\b      URT_DEGT_1_2 : DE guard time is 1/2 bit time.
 *  @arg\b      URT_DEGT_1   : DE guard time is 1 bit time. 
 *  @arg\b      URT_DEGT_2   : DE guard time is 2 bit time.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_DEGuardTime_Select(URT0 , URT_DEGT_1);
 * @endcode
 *******************************************************************************
 */
void URT_DEGuardTime_Select( URT_Struct* URTX , URT_DEGT_TypeDef URT_DE_GT)
{
    URTX->CR0.W = (( URTX->CR0.W & (~URT_CR0_DE_GT_mask_w)) | URT_DE_GT);
}


/**
 *******************************************************************************
 * @brief	    URTX idle line detect management mode select.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_IDL_MDS:
 *  @arg\b      URT_IDLEMode_No   : No operation when detecting idle line. 
 *  @arg\b      URT_IDLEMode_Load : Force to load shadow buffer when detecting idle line.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_IdlehandleMode_Select(URT0,URT_IDLEMode_Load);
 * @endcode
 *******************************************************************************
 */
void URT_IdlehandleMode_Select( URT_Struct* URTX , URT_IDLEMOde_TypeDef URT_IDL_MDS)
{

    URTX->CR0.W = ((URTX->CR0.W & (~URT_CR0_IDL_MDS_mask_w)) | URT_IDL_MDS);
}


/**
 *******************************************************************************
 * @brief	    URT transmitter halt enable / disable.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_TX_HALT:
 *  @arg\b      DISABLE : TX halt disable.
 *  @arg\b      ENABLE  : TX halt enable.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_TXHalt_Cmd(URT0 , ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_TXHalt_Cmd(URT_Struct* URTX , FunctionalState URT_TX_HALT)
{
    URTX->CR2.W = ((URTX->CR2.W & (~URT_CR2_TX_HALT_mask_w)) | (URT_CR2_TX_HALT_mask_w * URT_TX_HALT));
}
///@}




/**
 *******************************************************************************
 * @brief	    URT transmitter halt enable / disable.
 * @details     TX guard time between adjacent characters' transmission in 
 *              the unit of bit time.
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_TXGT_LEN: 
 *  @arg\b      (0 ~ 255) : Guard time() is 0 ~ 255 bit time. 
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_TXGuardTime_Select(URT0 , 48);
 * @endcode
 *******************************************************************************
 */
void URT_TXGuardTime_Select( URT_Struct* URTX , uint8_t URT_TXGT_LEN)
{
    URTX->CR3.B[2] = URT_TXGT_LEN;
}



/**
 *******************************************************************************
 * @brief	    URT transfer data .
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   Data_len: Transfer data byte.
 * @param[in]   URT_TDAT: Transfer data.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_SetTXData(URT0 , 1 , 0x48);
 * @endcode
 *******************************************************************************
 */
DRV_Return URT_SetTXData( URT_Struct* URTX , uint8_t Data_len , uint32_t URT_TDAT)
{
    switch(Data_len)
    {
        case 1:
                 URTX->TDAT.B[0] = (uint8_t) URT_TDAT;
                 break;
        case 2:
                 URTX->TDAT.H[0] = (uint16_t) URT_TDAT;
                 break;
        case 3:
                 URTX->TDAT3.W = URT_TDAT;
                 break;
        case 4:
                 URTX->TDAT.W = URT_TDAT;
                 break;
        default:
                 return(DRV_Failure);
    }
    return(DRV_Success);
}

/**
 * @name   SYNC Mode  
           SYNC mode relationship driver.
 */
///@{


/**
 *******************************************************************************
 * @brief	    URT data sampling mode select in SYNC mode. 
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_CPHA:
 *  @arg\b      URT_CPHA0_LeadEdge : Sampling on leading edge.
 *  @arg\b      URT_CPHA1_TrailEdge: Sampling on trailing edge.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_CPHAMode_Select( URT0, URT_CPHA0_LeadEdge);
 * @endcode
 *******************************************************************************
 */
void URT_CPHAMode_Select( URT_Struct* URTX , URT_CPHA_TypeDef URT_CPHA)
{   
    URTX->CR3.W = (( URTX->CR3.W & (~URT_CR3_CPHA_mask_w)) | URT_CPHA);   
}



/**
 *******************************************************************************
 * @brief	    URT clock polarity type select in SYNC mode.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_CPOL:
 *  @arg\b      URT_CPOL0_Low : Clock state is low in idle state.
 *  @arg\b      URT_CPOL1_High: Clock state is high in idle state.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_CPOLMode_Select( URT0, URT_CPOL0_Low);
 * @endcode
 *******************************************************************************
 */
void URT_CPOLMode_Select( URT_Struct* URTX, URT_CPOL_TypeDef URT_CPOL)
{   
    URTX->CR3.W = ((URTX->CR3.W  & (~URT_CR3_CPOL_mask_w)) | URT_CPOL);      
}

/**
 *******************************************************************************
 * @brief	    URT NSS output signal inverse disable / enable.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_NSS_INV:
 *  @arg\b      DISABLE: Disable NSS output signal inverse. 
 *  @arg\b      ENABLE : Enable NSS output signal inverse.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_NssInverse_Cmd( URT0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_NssInverse_Cmd( URT_Struct* URTX , FunctionalState URT_NSS_INV)
{   
    #if defined(URT_CR2_NSSI_INV_mask_w)
        URTX->CR2.W = (( URTX->CR2.W & (~(URT_CR2_NSS_INV_mask_w | URT_CR2_NSSI_INV_mask_w))) | ( (URT_CR2_NSS_INV_mask_w | URT_CR2_NSSI_INV_mask_w) * URT_NSS_INV));   
    #else
        URTX->CR2.W = (( URTX->CR2.W & (~(URT_CR2_NSS_INV_mask_w))) | ( (URT_CR2_NSS_INV_mask_w) * URT_NSS_INV)); 
    #endif 
}



/**
 *******************************************************************************
 * @brief	    URT NSS signal software control disable / enable.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_NSS_SWEN:
 *  @arg\b      DISABLE: NSS signal output controled by hardware.
 *  @arg\b      ENABLE : NSS signal output controled by software.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_NssSW_Cmd( URT0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_NssSW_Cmd( URT_Struct* URTX , FunctionalState URT_NSS_SWEN)
{
    URTX->CR2.W = (( URTX->CR2.W & (~URT_CR2_NSS_SWEN_mask_w)) | ( URT_CR2_NSS_SWEN_mask_w * URT_NSS_SWEN));
}


/**
 *******************************************************************************
 * @brief	    URT NSS signal software output control.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_NSS_SWO:
 *  @arg\b      CLR: NSS output logical 0.. 
 *  @arg\b      SET: NSS output logical 1.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_CtrlNSS_SW( URT0, SET);
 * @endcode
 *******************************************************************************
 */
void URT_CtrlNSS_SW( URT_Struct* URTX , BitAction URT_NSS_SWO)
{ 
    URTX->CR2.W = (( URTX->CR2.W & (~URT_CR2_NSS_SWO_mask_w)) | ( URT_CR2_NSS_SWO_mask_w * URT_NSS_SWO));
}

#if defined(URT_CR2_NSSI_EN_mask_w)
 /**
 *******************************************************************************
 * @brief       URT's NSSI function control in SPI slave mode.
 * @details  
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_NSSI_EN: 
 *	@arg\b      DISABLE : Disable NSSI function.
 *	@arg\b		ENABLE  : Enable NSSI function.
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
    URT_NssInput_Cmd( URT0 , ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_NssInput_Cmd( URT_Struct* URTX, FunctionalState URT_NSSI_EN)
{
    URTX->CR2.W = ((URTX->CR2.W & (~URT_CR2_NSSI_EN_mask_w)) | ( URT_CR2_NSSI_EN_mask_w * URT_NSSI_EN));
}
#endif

#if defined(URT_CR2_DOUT_MDS_mask_w)
 /**
 *******************************************************************************
 * @brief       Control URT SPI Master Mode MOSI Pin status in Bus is idle. 
 * @details  
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_MOSI_IDLESTATUS: 
 *	@arg\b      URT_mSPI_MOSI_Idle_Tristate : MOSI idle status is tristate.
 *	@arg\b		URT_mSPI_MOSI_Idle_LastBit  : MOSI idle status is last bit.
 *  @arg\b      URT_mSPI_MOSI_Idle_Low      : MOSI idle is Low.
 *  @arg\b      URT_mSPI_MOSI_Idle_High     : MOSI idle is High.
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
    URT_SPIMasterDataOutputIdleStatus_Select( URT0 , URT_mSPI_MOSI_Idle_LastBit);
 * @endcode
 *******************************************************************************
 */
void URT_SPIMasterDataOutputIdleStatus_Select( URT_Struct* URTX , URT_MOSIIdleStatus_TypeDef URT_MOSI_IDLESTATUS)
{
    URTX->CR2.B[3] = ((URTX->CR2.B[3] & (~(URT_CR2_DOUT_IDL_mask_b3 | URT_CR2_DOUT_MDS_mask_b3))) | URT_MOSI_IDLESTATUS);
}
#endif

#if defined(URT_CR0_SYNC_MDS_mask_w)
 /**
 *******************************************************************************
 * @brief       URT SYNC mode select.
 * @details  
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_SYNC_MDS: 
 *	@arg\b      URT_URT_mode : URT mode.
 *	@arg\b		URT_SYNC_MASTER: Synchronous/shift Maseter mode
 *	@arg\b		URT_SYNC_SLAVE : Synchronous/shift Slave mode
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
    URT_SYNCMode_Select( URT0 , URT_SYNC_MASTER);
 * @endcode
 *******************************************************************************
 */
void URT_SYNCMode_Select( URT_Struct* URTX , URT_SYNCMode_TypeDef URT_SYNC_MDS)
{
    MODIFY_REG( URTX->CR0.W , URT_CR0_SYNC_MDS_mask_w , URT_SYNC_MDS);
}
#endif
///@}





/**
 * @name   Address Mode  
           Address mode relationship driver.
 */
///@{

/**
 *******************************************************************************
 * @brief	    URTX multi-processor slave address mask setting. 
 * @details     Zero in this result is considered as don't care.
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_SA_MSK: (0x00 ~ 0xFF)
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_SetSlaveAddressMask( URT0, 0xF0);
 * @endcode
 *******************************************************************************
 */
void URT_SetSlaveAddressMask( URT_Struct* URTX , uint8_t URT_SA_MSK)
{
    URTX->SADR.B[1] = URT_SA_MSK;
}

/**
 *******************************************************************************
 * @brief	    URTX multi-processor mode received slave address.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_SA_RX: (0x00 ~ 0xFF)
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_SetSlaveAddress( URT0, 0x68);
 * @endcode
 *******************************************************************************
 */
void URT_SetSlaveAddress( URT_Struct* URTX , uint8_t URT_SA_RX)
{ 
    URTX->SADR.B[0] = URT_SA_RX;
}

/**
 *******************************************************************************
 * @brief	    URT0 multi-processor global slave address enable or disable.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_GSA_EN:
 *  @arg\b      DISABLE: Multi-processor global slave address disable.
 *  @arg\b      ENABLE : Multi-porcessor global slave address enable.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_GlobalAddress_Cmd( URT0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_GlobalAddress_Cmd( URT_Struct* URTX , FunctionalState URT_GSA_EN)
{
    URTX->CR0.W = (URTX->CR0.W & (~URT_CR0_GSA_EN_mask_w)) | (URT_CR0_GSA_EN_mask_w*URT_GSA_EN);
}
/**
 *******************************************************************************
 * @brief	    URT Send break signal.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_ADR_TX: Send Address value.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_SendAddress( URT0 , 0x68 ); 
 * @endcode
 *******************************************************************************
 */
void URT_SendAddress( URT_Struct* URTX , uint8_t URT_ADR_TX)
{
    URTX->CR2.W = URTX->CR2.W | URT_CR2_ADR_TX_mask_w;
    URTX->TDAT.B[0] = URT_ADR_TX;
}

///@}









/**
 * @name   Break & SYNC  
           
 */
///@{


/**
 *******************************************************************************
 * @brief	    URT auto baud rate calibration mode select.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_CAL_MDS:
 *  @arg\b      URT_CALMode_Start: Measure the start bit.
 *  @arg\b      URT_CALMode_Edge : Measure start falling edge to next falling edge.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_CalibrationMode_Select( URT0, URT_CALMode_Start);
 * @endcode
 *******************************************************************************
 */
void URT_CalibrationMode_Select( URT_Struct* URTX , URT_CALMode_TypeDef URT_CAL_MDS)
{
    URTX->CAL.W = (( URTX->CAL.W & (~URT_CAL_CAL_MDS_mask_w)) | URT_CAL_MDS);
}


/**
 *******************************************************************************
 * @brief	    URT auto baudrate calibration enable .
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_CAL_AUTO:
 *  @arg\b      DISABLE: Disable auto baudrate calibration.
 *  @arg\b      ENABLE : Enable auto baudrate calibration.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_AutoCalibration_Cmd( URT0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_AutoCalibration_Cmd( URT_Struct* URTX , FunctionalState URT_CAL_AUTO)
{
    URTX->CAL.W = (( URTX->CAL.W & (~URT_CAL_CAL_AUTO_mask_w)) | (URT_CAL_CAL_AUTO_mask_w * URT_CAL_AUTO));
}


/**
 *******************************************************************************
 * @brief	    URT baudrate calibration enable .
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_CAL_EN:
 *  @arg\b      DISABLE: Disable baudrate calibration.
 *  @arg\b      ENABLE : Enable baudrate calibration.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_Calibration_SW( URT0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_Calibration_SW( URT_Struct* URTX , FunctionalState URT_CAL_EN)
{
    URTX->CAL.W = (( URTX->CAL.W & (~URT_CAL_CAL_EN_mask_w)) | (URT_CAL_CAL_EN_mask_w * URT_CAL_EN));
}


/**
 *******************************************************************************
 * @brief	    After URT baudrate calibration complete hold receive data enable or disable.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_CALC_HE:
 *  @arg\b      DISABLE: No hold data from shift buffer to shadow buffer after calibration.
 *  @arg\b      ENABLE : Hold data from shift buffer to shadow buffer after calibration.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_CalibrationCompleteDataHold_Cmd( URT0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_CalibrationCompleteDataHold_Cmd( URT_Struct* URTX , FunctionalState URT_CALC_HE)
{
    URTX->CAL.W = (( URTX->CAL.W & (~URT_CAL_CALC_HE_mask_w)) | ( URT_CAL_CALC_HE_mask_w * URT_CALC_HE));
}


/**
 *******************************************************************************
 * @brief	    URT extra break bit select.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_DET_BK:
 *  @arg\b      URT_ExtraBK_1BIT: Extra break bit is 1 bit.
 *  @arg\b      URT_ExtraBK_3BIT: Extra break bit is 3 bit.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_ExtraBreakBit_Select( URT0, URT_ExtraBK_3BIT);
 * @endcode
 *******************************************************************************
 */
void URT_ExtraBreakBit_Select( URT_Struct* URTX , URT_ExtraBK_TypeDef URT_DET_BK)
{
    URTX->CR3.W = ((URTX->CR3.W & (~URT_CR3_DET_BK_mask_w)) | URT_DET_BK);
}

/**
 *******************************************************************************
 * @brief	    URT Send break signal.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_SendBreak( URT0 );
 * @endcode
 *******************************************************************************
 */
void URT_SendBreak( URT_Struct* URTX)
{
    URTX->CR2.W = URTX->CR2.W | URT_CR2_BK_TX_mask_w;
    URTX->TDAT.B[0] = 0x48;
}



#if defined(URT_STA_CALOVF_mask_w) && defined(URT_STA_CALUDF_mask_w)
/**
 *******************************************************************************
 * @brief	    Get URT auto baud-rate calibration result.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @return      DRV_Success   : Calibration success.
 * @return      DRV_OverFlow  : Overflow baudrate generator counter.
 * @return      DRV_UnderFlow : Underflow baudrate generator counter.
 * @exception   No
 * @note 
 * @par         Example
 * @code
       DRV_Return URT_CAL_Result;
       
       URT_CAL_Result = URT_GetCalibrationResult(URT0);
 * @endcode
 *******************************************************************************
 */
DRV_Return URT_GetCalibrationResult(URT_Struct* URTX)
{
    uint32_t Tmp;
    
    Tmp = URTX->STA.W & (URT_EVENT_CALOVF|URT_EVENT_CALUDF);
    URTX->STA.W = URTX->STA.W | (URT_STA_CALOVF_mask_w | URT_STA_CALUDF_mask_w);
     
    if(Tmp==URT_EVENT_CALOVF)
    {
        return(DRV_OverFlow);
    }
    else if(Tmp==URT_EVENT_CALUDF)
    {
        return(DRV_UnderFlow);
    }
    
    return(DRV_Success);
}


#endif



///@}




/**
 * @name   DMA 
           URT DMA relationship driver.
 */
///@{


/**
 *******************************************************************************
 * @brief	    URT DMA TX function disable or enable.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_DMA_TXEN:
 *  @arg\b      DISABLE: Disable DMA TX function.
 *  @arg\b      ENABLE : Enable DMA TX function.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_TXDMA_Cmd( URT0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_TXDMA_Cmd( URT_Struct* URTX, FunctionalState URT_DMA_TXEN)
{
    if((URTX->CR2.W & URT_CR2_TX_EN_mask_w) !=0)
    {
        URTX->CR2.W = URTX->CR2.W & (~URT_CR2_TX_EN_mask_w);
        if(URT_DMA_TXEN==ENABLE)
        {
            URTX->CR0.W = URTX->CR0.W | URT_CR0_DMA_TXEN_mask_w;
        }
        else
        {
            URTX->CR0.W = URTX->CR0.W & (~URT_CR0_DMA_TXEN_mask_w); 
        }
        URTX->CR2.W = URTX->CR2.W | URT_CR2_TX_EN_mask_w;
    }
    else
    {
        if(URT_DMA_TXEN==ENABLE)
        {
            URTX->CR0.W = URTX->CR0.W | URT_CR0_DMA_TXEN_mask_w;
        }
        else
        {
            URTX->CR0.W = URTX->CR0.W & (~URT_CR0_DMA_TXEN_mask_w); 
        }
    }
}
    
/**
 *******************************************************************************
 * @brief	    URT DMA RX function disable or enable.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_DMA_RXEN:
 *  @arg\b      DISABLE: Disable DMA RX function.
 *  @arg\b      ENABLE : Enable DMA RX function.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_RXDMA_Cmd( URT0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_RXDMA_Cmd( URT_Struct* URTX , FunctionalState URT_DMA_RXEN)
{
    if((URTX->CR2.W & URT_CR2_RX_EN_mask_w) !=0)
    {
        URTX->CR2.W = URTX->CR2.W & (~URT_CR2_RX_EN_mask_w);
        if(URT_DMA_RXEN==ENABLE)
        {
            URTX->CR0.W = URTX->CR0.W | URT_CR0_DMA_RXEN_mask_w;
        }
        else
        {
            URTX->CR0.W = URTX->CR0.W & (~URT_CR0_DMA_RXEN_mask_w);   
        }
        URTX->CR2.W = URTX->CR2.W | URT_CR2_RX_EN_mask_w;
    }
    else
    {
        if(URT_DMA_RXEN==ENABLE)
        {
            URTX->CR0.W = URTX->CR0.W | URT_CR0_DMA_RXEN_mask_w;
        }
        else
        {
            URTX->CR0.W = URTX->CR0.W & (~URT_CR0_DMA_RXEN_mask_w);   
        }
    }    
}

    
/**
 *******************************************************************************
 * @brief	    URT auto disable DMA (TX and RX) when detect break signal 
 *              function disable or enable.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_DDTX_EN:
 *  @arg\b      DISABLE: Disable the function , auto disable DMA (TX/RX) when detect break signal.
 *  @arg\b      ENABLE : Enable the function , auto disable DMA (TX/RX) when detect break signal.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_BreakDisableDMA_Cmd( URT0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_BreakDisableDMA_Cmd( URT_Struct* URTX , FunctionalState URT_DDTX_EN)
{
    URTX->CR0.W = (( URTX->CR0.W & (~URT_CR0_DDTX_EN_mask_w)) | (URT_CR0_DDTX_EN_mask_w * URT_DDTX_EN));
}
///@}



/**
 * @name   IrDA 
           IrDA relationship driver.
 */
///@{
/**
 *******************************************************************************
 * @brief	    IrDA TX / RX mode configuration.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_IRDA:
 *  @arg\b      URT_IrDaPulseWidth:
 *      \n      -URT_IrDATra_1 : Pulse is 1  CK_URTx_TX clock.
 *      \n      -URT_IrDATra_2 : Pulse is 2  CK_URTx_TX clock.
 *      \n      -URT_IrDATra_3 : Pulse is 3  CK_URTx_TX clock.
 *      \n      -URT_IrDATra_4 : Pulse is 4  CK_URTx_TX clock.
 *      \n      -URT_IrDATra_5 : Pulse is 5  CK_URTx_TX clock.
 *      \n      -URT_IrDATra_6 : Pulse is 6  CK_URTx_TX clock.
 *      \n      -URT_IrDATra_7 : Pulse is 7  CK_URTx_TX clock.
 *      \n      -URT_IrDATra_8 : Pulse is 8  CK_URTx_TX clock.
 *      \n      -URT_IrDATra_9 : Pulse is 9  CK_URTx_TX clock.
 *      \n      -URT_IrDATra_10: Pulse is 10 CK_URTx_TX clock.
 *      \n      -URT_IrDATra_11: Pulse is 11 CK_URTx_TX clock.
 *      \n      -URT_IrDATra_12: Pulse is 12 CK_URTx_TX clock.
 *      \n      -URT_IrDATra_13: Pulse is 13 CK_URTx_TX clock.
 *      \n      -URT_IrDATra_14: Pulse is 14 CK_URTx_TX clock.
 *      \n      -URT_IrDATra_15: Pulse is 15 CK_URTx_TX clock.
 *      \n      -URT_IrDATra_16: Pulse is 16 CK_URTx_TX clock.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_IrDA_TypeDef URT_IRDA;
    
    URT_IRDA.URT_IrDaPulseWidth = URT_IrDATra_9;
    URT_IrDA_Config(URT0,&URT_IRDA);
 * @endcode
 *******************************************************************************
 */
void URT_IrDA_Config( URT_Struct* URTX , URT_IrDA_TypeDef* URT_IRDA)
{

    URTX->IRDA.W = ((URTX->IRDA.W & (~(URT_IRDA_IR_PW_mask_w) )) |
                   ((((uint32_t)URT_IRDA->URT_IrDaPulseWidth) <<8) ));
    
}


/**
 *******************************************************************************
 * @brief	    IrDA encoder / decoder enable or disable.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_IR_EN:
 *  @arg\b      DISABLE: IrDA encoder / decoder disable.     
 *  @arg\b      ENABLE : IrDA encoder / decoder enable.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_IrDA_Cmd(URT0 , ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_IrDA_Cmd( URT_Struct* URTX , FunctionalState URT_IR_EN)
{
    URTX->IRDA.W = (( URTX->IRDA.W & (~URT_IRDA_IR_EN_mask_w )) | ( URT_IRDA_IR_EN_mask_w * URT_IR_EN));
}

///@}






/**
 * @name	Mute 
 *   		Mute relationship driver.
 */ 
///@{

/**
 *******************************************************************************
 * @brief	    URT select automatic exit mute mode.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_ExitMuteMode:
 *  @arg\b      URT_ExitMute_IdleDetect  : When detect idle line URT auto exit mute mode.
 *  @arg\b      URT_ExitMute_BreakDetect : When detect break signal URT auto exit mute mode.
 *  @arg\b      URT_ExitMute_AddressMatch: When address match URT auto exit mute mode.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_AutoExitMuteMode_Select(URT0 , (URT_ExitMute_AddressMatch | URT_ExitMute_IdleDetect) );
 * @endcode
 *******************************************************************************
 */
void URT_AutoExitMuteMode_Select( URT_Struct* URTX, uint8_t URT_ExitMuteMode)
{
    URTX->MUTE.B[2] = URT_ExitMuteMode;
}


/**
 *******************************************************************************
 * @brief	    URT select automatic enter mute mode.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_EnterMuteMode:
 *  @arg\b      URT_EnterMute_idleDetect     : When detect idle line URT auto enter mute mode.
 *  @arg\b      URT_EnterMute_AddressUnmatch : When address unmatch URT auto enter mute mode.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_AutoEnterMuteMode_Select(URT0 , (URT_EnterMute_AddressUnmatch | URT_EnterMute_idleDetect));
 * @endcode
 *******************************************************************************
 */
void URT_AutoEnterMuteMode_Select( URT_Struct* URTX, uint8_t URT_EnterMuteMode)
{ 
    URTX->MUTE.B[1] = URT_EnterMuteMode;
}

/**
 *******************************************************************************
 * @brief	    URT into mute mode or exit mute mode by software.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_Mute_EN:
 *  @arg\b      DISABLE : Disable URT mute function. 
 *  @arg\b      ENABLE  : Enable URT mute function.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_Mute_Cmd(URT0 , ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_Mute_Cmd( URT_Struct* URTX , FunctionalState URT_Mute_EN)
{
    
    URTX->MUTE.W = (( URTX->MUTE.W & (~URT_MUTE_MUTE_EN_mask_w)) | (URT_MUTE_MUTE_EN_mask_w * URT_Mute_EN));
}



///@}


/**
 * @name	Error 
 *   		Error detect and handle.
 */ 
///@{


/**
 *******************************************************************************
 * @brief	    URT RX parity error relationship control.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_RXPE:
 *  @arg\b      URT_RXPERetryMode:
 *      \n      -URT_RXPERetry_Disable  : Disable auto retry when RX parity error.
 *      \n      -URT_RXPERetry_Limited  : Limited time auto retry when RX parity error.  
 *      \n      -URT_RXPERetry_Unlimited: Always auto retry unless receiving parity correct character.
 *  @arg\b      URT_RXErrorSignal:
 *      \n      -URT_RXErrorSignal_1BIT: Error signal is 1 bit.
 *      \n      -URT_RXErrorSignal_2BIT: Error signal is 2 bit.
 *  @arg\b      URT_RXPERetryTime : Auto retry time when retry mode is limited time auto retry.
 *      \n      -( URT_RXPERetry_0 ~ URT_RXPERetry_7) : ( 0 ~ 7 time). 
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_RXParityError_TypeDef   URT_RXPE;

    URT_RXPE.URT_RXPERetryMode = URT_RXPERetry_Limited;
    URT_RXPE.URT_RXErrorSignal = URT_RXErrorSignal_1BIT;
    URT_RXPE.URT_RXPERetryTime = URT_RXPERetry_3;
    URT_RXParityError_Config( URT0 , &URT_RXPE);
 * @endcode
 *******************************************************************************
 */
void URT_RXParityError_Config( URT_Struct* URTX , URT_RXParityError_TypeDef*  URT_RXPE)
{
    URTX->SC.W = (URTX->SC.W & (~(URT_SC_RXE_MDS_mask_w | URT_SC_RXE_LEN_mask_w | URT_SC_RXE_NUM_mask_w))) |  
                 ((uint32_t)URT_RXPE->URT_RXPERetryMode) | 
                 ((uint32_t)URT_RXPE->URT_RXErrorSignal) | 
                 ((uint32_t)URT_RXPE->URT_RXPERetryTime);
}


/**
 *******************************************************************************
 * @brief	    URT TX error detect mode select.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_TXE_MDS:
 *  @arg\b      URT_TXErrorDetect_Disable    : TX error detect disable.
 *  @arg\b      URT_TXErrorDetect_ErrorSignal: Check asserted low by RX device (for SC)
 *  @arg\b      URT_TXErrorDetect_TX         : Check TX data by RX input data (for LIN mode)
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_TXErrorDetectMode_Select(URT0 , URT_TXErrorDetect_ErrorSignal);
 * @endcode
 *******************************************************************************
 */
void URT_TXErrorDetectMode_Select( URT_Struct* URTX , URT_TXErrorMode_TypeDef URT_TXE_MDS)
{
    URTX->SC.W = (URTX->SC.W & (~URT_SC_TXE_MDS_mask_w)) | URT_TXE_MDS;
}


/**
 *******************************************************************************
 * @brief	    URT TX error detect and data resend maximum number.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_TXE_NUM:
 *  @arg\b      URT_TXErrorResend_0                      : Indicates to disable hardware auto resend. 
 *  @arg\b      (URT_TXErrorResend_1~URT_TXErrorResend_7): Resend maximum number for continuous TX error detection.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_TXErrorResendTime_Select(URT0 , URT_TXErrorResend_3);
 * @endcode
 *******************************************************************************
 */
void URT_TXErrorResendTime_Select( URT_Struct* URTX , URT_TXErrorReSendTime_TypeDef URT_TXE_NUM)
{
    URTX->SC.W = (( URTX->SC.W & (~URT_SC_TXE_NUM_mask_w)) | URT_TXE_NUM);
}

///@}



/**
 * @name   Pin Control 
           
 */
///@{
/**
 *******************************************************************************
 * @brief	    URT RX / TX swap enable or disable.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   URT_IO_SWP:
 *  @arg\b      DISABLE : RX / TX swap disable.
 *  @arg\b      ENABLE  : RX / TX swap enable.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
    URT_RxTxSwap_Cmd(URT0 , ENABLE);
 * @endcode
 *******************************************************************************
 */
void URT_RxTxSwap_Cmd(URT_Struct* URTX , FunctionalState URT_IO_SWP)
{
    URTX->CR0.W = (URTX->CR0.W & (~URT_CR0_IO_SWP_mask_w)) | (URT_CR0_IO_SWP_mask_w * URT_IO_SWP);
}


#if defined(URT_CLK_ECK_CKS_mask_w)
/**
 *******************************************************************************
 * @brief	    URT external clock signal multiplexer select.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   ECK_SEL:
 *  @arg\b      URT_ExternalClockInput_CLK : external clock singal IO is URT_CLK pin
 *  @arg\b      URT_ExternalClockInput_RX  : 1. external clock singal IO is URT_RX if TX / RX no swap.
 *      \n                                   2. external clock signal IO is URT_TX if TX / RX swap.
 * @return      
 * @exception   No
 * @note 
 *      \n      1. In MG32F02A032 the function only control external clock singal input.
 * @par         Example
 * @code
    URT_ExternalClockMux_Select(URT0 , URT_ExternalClockInput_CLK);
 * @endcode
 *******************************************************************************
 */
void URT_ExternalClockMux_Select(URT_Struct* URTX,  URT_ExternalClockMux_TypeDef  ECK_SEL)
{
    URTX->CLK.W = ((URTX->CLK.W & (~URT_CLK_ECK_CKS_mask_w)) | ECK_SEL);
}
#endif

///@}

