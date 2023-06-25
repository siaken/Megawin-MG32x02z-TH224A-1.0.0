/**
 *******************************************************************************
 *
 * @file        MG32x02z_SPI_DRV.c
 *
 * @brief       This is the C code format driver file for SPI module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.27
 * @date        2022/03/18
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2021 Megawin Technology Co., Ltd.
 *              All rights reserved.
 *
 *******************************************************************************
 * @par         Disclaimer 
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

#include "MG32x02z_SPI_DRV.h"


/**
 * @name    DeInit
 *
 */ 
///@{
/**
 *******************************************************************************
 * @brief       SPIx Power on default initial
 * @details  
 * @return
 * @note
 * @par         Example
 * @code
    SPI_DeInit(SPI0);
 * @endcode
 *******************************************************************************
 */
void SPI_DeInit (SPI_Struct* SPIx)
{
    SPIx->CR0.W = 0x00000000;
    SPIx->STA.W = 0x00000FD8;
    SPIx->INT.W = 0x00000000;
    SPIx->CLK.W = 0x00000000;
    SPIx->CR1.W = 0x00000000;
    SPIx->CR2.W = 0x03000100;
}
///@} 


/**
 * @name    Clock
 *
 */ 
///@{
/**
 *******************************************************************************
 * @brief       SPIx internal clock CK_SPI0 source select
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0
 * @param[in]   SPI_CLKS:
 * 	@arg\b          SPI_CK_SPIx_PR
 * 	@arg\b          SPI_TM00_TRGO
 * @return
 * @note        
 * @par         Example
 * @code
    SPI_Clock_Select(SPI0, SPI_CK_SPIx_PR);
 * @endcode
 *******************************************************************************
 */
void SPI_Clock_Select (SPI_Struct* SPIx, SPI_CLKS_Enum SPI_CLKS)
{
    SPIx->CLK.MBIT.CK_SEL = SPI_CLKS;
}

/**
 *******************************************************************************
 * @brief       SPI0 process clock CK_SPI0_PR input divider. 
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0.
 * @param[in]   SPI_PDIVS:
 * 	@arg\b          SPI_PDIV_1.
 * 	@arg\b          SPI_PDIV_2.
 * 	@arg\b          SPI_PDIV_4.
 * 	@arg\b          SPI_PDIV_8.
 * @return
 * @note
 * @par         Example
 * @code
    SPI_PreDivider_Select(SPI0, SPI_PDIV_1);
 * @endcode
 *******************************************************************************
 */
void SPI_PreDivider_Select (SPI_Struct* SPIx, SPI_PDIV_Enum SPI_PDIVS)
{
    SPIx->CLK.MBIT.CK_PDIV = SPI_PDIVS;
}

/**
 *******************************************************************************
 * @brief                    SPIx internal clock CK_SPI0_INT prescaler.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0.
 * @param[in]   SPI_PSCS:
 * 	@arg\b          SPI_PSC_1.
 * 	@arg\b          SPI_PSC_2.
 * 	@arg\b          SPI_PSC_3.
 * 	@arg\b          SPI_PSC_4.
 * 	@arg\b          SPI_PSC_5.
 * 	@arg\b          SPI_PSC_6.
 * 	@arg\b          SPI_PSC_7.
 * 	@arg\b          SPI_PSC_8.
 * @return
 * @note
 * @par         Example
 * @code
    SPI_Prescaler_Select(SPI0, SPI_PSC_1);
 * @endcode
 *******************************************************************************
 */
void SPI_Prescaler_Select (SPI_Struct* SPIx, SPI_PSC_Enum SPI_PSCS)
{
    SPIx->CLK.MBIT.CK_PSC = SPI_PSCS;
} 

/**
 *******************************************************************************
 * @brief       SPIx internal clock CK_SPI0_INT input divider.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0.
 * @param[in]   SPI_DIVS:
 * 	@arg\b          SPI_DIV_2.
 * 	@arg\b          SPI_DIV_4.
 * 	@arg\b          SPI_DIV_8.
 * 	@arg\b          SPI_DIV_16.
 * @return
 * @note
 * @par         Example
 * @code
    SPI_Divider_Select(SPI0, SPI_DIV_2);
 * @endcode
 *******************************************************************************
 */
void SPI_Divider_Select (SPI_Struct* SPIx, SPI_DIV_Enum SPI_DIVS)
{
    SPIx->CLK.MBIT.CK_DIV = SPI_DIVS;
}

#if (defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH))
/**
 *******************************************************************************
 * @brief       SPIx set clock toggle
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0.
 * @return
 * @note        Only support master mode
 * @par         Example
 * @code
    SPI_SetClockToggle(SPI0);
 * @endcode
 *******************************************************************************
 */
void SPI_TriggerClockToggle (SPI_Struct* SPIx)
{
    SPIx->CR2.MBIT.CKO_TOG = 1;
}
#endif

#if (defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH))
/**
 *******************************************************************************
 * @brief       SPIx transfer rate selection
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0.
 * @param[in]   SPI_TRS:
 * 	@arg\b          SPI_StandardTransferRate
 * 	@arg\b          SPI_DualTransferRate
 * @return
 * @note        Only support clock mode 0 of master mode.
 * @par         Example
 * @code
    SPI_DualTransferRate_Select(SPI0, SPI_StandardTransferRate);
 * @endcode
 *******************************************************************************
 */
//Dual transfer rate mode enable bit for SPI master mode
void SPI_DualTransferRate_Select (SPI_Struct* SPIx, TRS_Enum SPI_TRS)
{
    SPIx->CR2.MBIT.DTR_EN = SPI_TRS;
}
#endif

#if (defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH))
/**
 *******************************************************************************
 * @brief       SPIx slave mode high speed function enable
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0.
 * @param[in]   NewState:
 * 	@arg\b          DISABLE
 * 	@arg\b          ENABLE
 * @return
 * @note        Only support Slave mode
 * @par         Example
 * @code
    SPI_SlaveHighSpeed_Cmd(SPI0, DISABLE);
 * @endcode
 *******************************************************************************
 */
void SPI_SlaveHighSpeed_Cmd (SPI_Struct* SPIx, FunctionalState NewState)
{
    SPIx->CR0.MBIT.HS_EN = NewState;
}
#endif
///@} 
 

/**
 * @name    Mode & NSS
 *
 */ 
///@{
/**
 *******************************************************************************
 * @brief       SPIx mode and nss selection
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0.
 * @param[in]   SPI_MNS:
 * 	@arg\b          SPI_Master.
 * 	@arg\b          SPI_MasterWithNss.
 * 	@arg\b          SPI_MasterWithMODF.
 * 	@arg\b          SPI_MasterWithNssAndMODF.
 * 	@arg\b          SPI_Slave.
 * 	@arg\b          SPI_SlaveWithNss.
 * @return
 * @note
 * @par         Example
 * @code
    SPI_ModeAndNss_Select(SPI0, SPI_Master);
 * @endcode
 *******************************************************************************
 */
void SPI_ModeAndNss_Select (SPI_Struct* SPIx, MODNSS_Enum SPI_MNS)
{
    SPIx->CR0.W &= (uint32_t) (~0x00000330);
    SPIx->CR0.W |= SPI_MNS;
}

/**
 *******************************************************************************
 * @brief       SPIx function select when master mode fault detect.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0.
 * @param[in]   SPI_MODFS:
 * 	@arg\b          SPI_DisableSPI.
 * 	@arg\b          SPI_SwitchToSlave.
 * @return
 * @note
 * @par         Example
 * @code
    SPI_ModfHappenedAction_Select(SPI0, SPI_SwitchToSlave);
 * @endcode
 *******************************************************************************
 */
void SPI_ModfHappenedAction_Select (SPI_Struct* SPIx, MODF_Enum SPI_MODFS)
{
    SPIx->CR0.MBIT.MODF_SEL = SPI_MODFS;
}

/**
 *******************************************************************************
 * @brief       SPIx pin select for NSS input signal.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0.
 * @param[in]   SPI_NSSIS:
 * 	@arg\b          SPI_NssPin.
 * 	@arg\b          SPI_NssiPin.
 * @return          
 * @note
 * @par         Example
 * @code
    SPI_NSSInputSignal_Select(SPI0, SPI_NssPin);
 * @endcode
 *******************************************************************************
 */ 
void SPI_NSSInputSignal_Select (SPI_Struct* SPIx, NSSI_Enum SPI_NSSIS)
{
    SPIx->CR0.MBIT.NSSI_SEL = SPI_NSSIS;
}

/**
 *******************************************************************************
 * @brief       SPIx single master mode NSS pulse enable .
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0.
 * @param[in]   NewState:
 * 	@arg\b          DISABLE.
 * 	@arg\b          ENABLE.
 * @return
 * @note
 * @par         Example
 * @code
    SPI_SingleMasterModeNssPulse_Cmd(SPI0, DISABLE);
 * @endcode
 *******************************************************************************
 */
void SPI_SingleMasterModeNssPulse_Cmd (SPI_Struct* SPIx, FunctionalState NewState)
{
#if (defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH))
    // For Version B
    SPIx->CR0.MBIT.NSS_PEN = NewState;
#elif (defined(MG32_1ST))
    // For Version A
    SPIx->CR0.MBIT.NSS_PEN = (NewState | 1);
#endif
}

/**
 *******************************************************************************
 * @brief       SPIx NSS input signal inverse enable.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0
 * @param[in]   NewState:
 * 	@arg\b          DISABLE
 * 	@arg\b          ENABLE
 * @return
 * @note
 * @par         Example
 * @code
    SPI_NssInputInverse_Cmd(SPI0, DISABLE);
 * @endcode
 *******************************************************************************
 */
void SPI_NssInputInverse_Cmd (SPI_Struct* SPIx, FunctionalState NewState)
{
    SPIx->CR0.MBIT.NSSI_INV = NewState;
}
 
/**
 *******************************************************************************
 * @brief       SPIx NSS output signal inverse enable.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0.
 * @param[in]   NewState:
 * 	@arg\b          DISABLE.
 * 	@arg\b          ENABLE.
 * @return
 * @note
 * @par         Example
 * @code
    SPI_NssOutputInverse_Cmd(SPI0, DISABLE);
 * @endcode
 *******************************************************************************
 */
void SPI_NssOutputInverse_Cmd (SPI_Struct* SPIx, FunctionalState NewState)
{
    SPIx->CR0.MBIT.NSSO_INV = NewState;
}
 
/**
 *******************************************************************************
 * @brief       SPI0 NSS signal input/output use software control bit enable..
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0
 * @param[in]   NewState:
 * 	@arg\b          DISABLE
 * 	@arg\b          ENABLE
 * @return
 * @note
 * @par         Example
 * @code
    SPI_NssInputOutputSoftwareControl_Cmd(SPI0, DISABLE);
 * @endcode
 *******************************************************************************
 */
void SPI_NssInputOutputSoftwareControl_Cmd (SPI_Struct* SPIx, FunctionalState NewState)
{
    #if (defined(MG32_1ST))
        SPIx->CR0.MBIT.NSS_SWEN = NewState;
    #endif
    #if (defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH))
        SPIx->CR0.MBIT.NSS_SWEN = NewState;
        SPIx->CR0.MBIT.NSSI_SWEN = NewState;
    #endif
}

#if (defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH))
/**
 *******************************************************************************
 * @brief       SPIx NSS input software control
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0.
 * @param[in]   NewState:
 * 	@arg\b          DISABLE
 * 	@arg\b          ENABLE
 * @return
 * @note
 * @par         Example
 * @code
    SPI_NssInputSoftwareControl_Cmd(SPI0, DISABLE);
 * @endcode
 *******************************************************************************
 */
void SPI_NssInputSoftwareControl_Cmd (SPI_Struct* SPIx, FunctionalState NewState)
{
    SPIx->CR0.MBIT.NSSI_SWEN = NewState;
}
#endif

#if (defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH))
 /**
 *******************************************************************************
 * @brief       SPIx NSS output software control
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0.
 * @param[in]   NewState:
 * 	@arg\b          DISABLE
 * 	@arg\b          ENABLE
 * @return
 * @note
 * @par         Example
 * @code
    SPI_NssOutputSoftwareControl_Cmd(SPI0, DISABLE);
 * @endcode
 *******************************************************************************
*/   
void SPI_NssOutputSoftwareControl_Cmd (SPI_Struct* SPIx, FunctionalState NewState)
{
    SPIx->CR0.MBIT.NSS_SWEN = NewState;
}
#endif
 
/**
 *******************************************************************************
 * @brief       SPIx this bit is used as NSS signal input status bit
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0.
 * @return      DRV_Return
 * 	@arg\b          DRV_Low
 * 	@arg\b          DRV_High
 * @note
 * @par         Example
 * @code
    NSS_Status = SPI_GetNSSInputStatust(SPI0);
 * @endcode
 *******************************************************************************
 */
DRV_Return SPI_GetNSSInputStatust (SPI_Struct* SPIx)
{
    DRV_Return bitstatus = DRV_Low;
    
    if(SPIx->CR2.MBIT.NSS_SWI != 0)
    {
        bitstatus = DRV_High;
    }
    return bitstatus;
}

/**
 *******************************************************************************
 * @brief       SPIx this bit is control as NSS signal input status.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0.
 * @param[in]       NSSIState
 * 	@arg\b          0.
 * 	@arg\b          1.
 * @note        Modify when SPI_NssInputOutputSoftwareControl_Cmd(ENABLE);
 * @par         Example
 * @code
    SPI_NSSInputStatusControl_SW(SPI0, 0);
 * @endcode
 *******************************************************************************
 */
void SPI_NSSInputStatusControl_SW (SPI_Struct* SPIx, uint8_t NSSIState)
{
    SPIx->CR2.MBIT.NSS_SWI = NSSIState;
}

/**
 *******************************************************************************
 * @brief       SPIx this bit is control as NSS signal output status.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0.
 * @param[in]   NewStatus:
 * 	@arg\b          0.
 * 	@arg\b          1.
 * @return
 * @note        Modify when SPI_NssInputOutputSoftwareControl_Cmd(ENABLE);
 * @par         Example
 * @code
    SPI_NSSOutputStatusControl_SW(SPI0, 1);
 * @endcode
 *******************************************************************************
 */
void SPI_NSSOutputStatusControl_SW (SPI_Struct* SPIx, uint8_t NewStatus)
{
    SPIx->CR2.MBIT.NSS_SWO = NewStatus;
}

/**
 *******************************************************************************
 * @brief       SPIx function enable bit.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0.
 * @param[in]   NewState:
 * 	@arg\b          DISABLE.
 * 	@arg\b          ENABLE.
 * @note
 * @par         Example
 * @code
    SPI_Cmd(SPI0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void SPI_Cmd(SPI_Struct* SPIx, FunctionalState NewState)
{
    SPIx->CR0.MBIT.EN = NewState;
}

#if (defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH))
/**
 *******************************************************************************
 * @brief  	    SPIx master NSS idle time selection
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @param[in]   SPI_IDTS:
 * 	@arg\b		    SPI_IDT_1T.
 * 	@arg\b		    SPI_IDT_2T.
 * @note        Only support master.
 * @par         Example
 * @code
    SPI_NssIdleTime_Select(SPI0, SPI_IDT_1T);
 * @endcode
 *******************************************************************************
 */
void SPI_NssIdleTime_Select (SPI_Struct* SPIx, IDT_Enum SPI_IDTS)
{
    SPIx->CR1.MBIT.NSS_IDT = SPI_IDTS;
}
#endif
///@} 


/**
 * @name    Timing
 *
 */ 
///@{
/**
 *******************************************************************************
 * @brief       SPIx clock phase selection.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0.
 * @param[in]   SPI_CPHAS:
 * 	@arg\b          SPI_LeadingEdge.
 *  @arg\b          SPI_TrailingEdge.
 * @return
 * @note
 * @par         Example
 * @code
    SPI_ClockPhase_Select(SPI0, SPI_LeadingEdge);
 * @endcode
 *******************************************************************************
 */
void SPI_ClockPhase_Select (SPI_Struct* SPIx, CPHA_Enum SPI_CPHAS)
{
    SPIx->CR0.MBIT.CPHA = SPI_CPHAS;
}

/**
 *******************************************************************************
 * @brief       SPIx clock polarity selection.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0.
 * @param[in]   SPI_CPOLS:
 * 	@arg\b          SPI_Low.
 *  @arg\b          SPI_High.
 * @return
 * @note
 * @par         Example
 * @code
    SPI_ClockPolarity_Select(SPI0, SPI_Low);
 * @endcode
 *******************************************************************************
 */
void SPI_ClockPolarity_Select (SPI_Struct* SPIx, CPOL_Enum SPI_CPOLS)
{
    SPIx->CR0.MBIT.CPOL = SPI_CPOLS;
}

/**
 *******************************************************************************
 * @brief       SPIx data order first bit select.
 * @details     
 * @param[in]   SPIx:
 * 	@arg\b          SPI0.
 * @param[in]   SPI_FBS:
 * 	@arg\b          SPI_MSB.
 * 	@arg\b          SPI_LSB.
 * @return
 * @note
 * @par         Example
 * @code
    SPI_FirstBit_Select(SPI0, SPI_MSB);
 * @endcode
 *******************************************************************************
 */ 
void SPI_FirstBit_Select (SPI_Struct* SPIx, SPI_FBS_Enum SPI_FBS)
{
    SPIx->CR0.MBIT.LSB_EN = SPI_FBS;
}
///@} 
 

/**
 * @name    Buffer
 *
 */ 
///@{
/**
 *******************************************************************************
 * @brief       SPIx data buffer received level indications
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0.
 * @return      uint8_t
 * 	@arg\b          0 ~ 4.
 * @note
 * @par         Example
 * @code
    RxShadowBuffer = SPI_GetRxShadowBufferLevel(SPI0);
 * @endcode
 *******************************************************************************
 */
uint8_t SPI_GetRxShadowBufferLevel (SPI_Struct* SPIx)
{
    return SPIx->STA.MBIT.RX_LVL;
}

/**
 *******************************************************************************
 * @brief       SPIx received data clear enable
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0.
 * @return
 * @note
 * @par         Example
 * @code
    SPI_ClearRxData(SPI0);
 * @endcode
 *******************************************************************************
 */
void SPI_ClearRxData (SPI_Struct* SPIx)
{
    SPIx->CR1.MBIT.RDAT_CLR = 1;
}
 
/**
 *******************************************************************************
 * @brief       SPIx get RNUM data.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0.
 * @return      uint8_t
 * 	@arg\b          0 ~ 4.
 * @note
 * @par         Example
 * @code
    SPI_RNUM = SPI_GetDataBufferReceivedBytes(SPI0);
 * @endcode
 *******************************************************************************
 */
uint8_t SPI_GetDataBufferReceivedBytes (SPI_Struct* SPIx)
{
    return SPIx->STA.MBIT.RNUM;
}
 
/**
 *******************************************************************************
 * @brief       SPIx set RNUM data.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0.
 * @param[in]   SPI_RNUMS:
 * 	@arg\b          SPI_RNUM_0Byte
 * 	@arg\b          SPI_RNUM_1Byte
 * 	@arg\b          SPI_RNUM_2Byte
 * 	@arg\b          SPI_RNUM_3Byte
 * 	@arg\b          SPI_RNUM_4Byte
 * @return
 * @note        SPI received data buffer high threshold for slave mode. 
 * @par         Example
 * @code
    SPI_SetDataBufferReceivedBytes(SPI0, SPI_RNUM_4Byte);
 * @endcode
 *******************************************************************************
 */
void SPI_SetDataBufferReceivedBytes (SPI_Struct* SPIx, RNUM_Enum SPI_RNUMS)
{
    SPIx->STA.MBIT.RNUM = SPI_RNUMS;
}

/**
 *******************************************************************************
 * @brief       SPIx transmitted data clear enable.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @return	    	
 * @note
 * @par         Example
 * @code
    SPI_ClearTxData(SPI0);
 * @endcode
 *******************************************************************************
 */
void SPI_ClearTxData (SPI_Struct* SPIx)
{
    SPIx->CR1.MBIT.TDAT_CLR = 1;
}
 
/**
 *******************************************************************************
 * @brief  	    SPIx data buffer transmission remained level indications.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @return	    uint8_t
 * 	@arg\b			0 ~ 4.
 * @note
 * @par         Example
 * @code
    TxShadowBuffer =  SPI_GetTxShadowBufferLevel(SPI0);
 * @endcode
 *******************************************************************************
 */
uint8_t SPI_GetTxShadowBufferLevel (SPI_Struct* SPIx)
{
    return SPIx->STA.MBIT.TX_LVL;
}
 
/**
 *******************************************************************************
 * @brief  	    SPIx received data register.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @return	    uint32_t
 * 	@arg\b			0x00000000 ~ 0xFFFFFFFF.
 * @note        read not all 0 for non-updated byte(s) by SPI0_RX_TH setting
 * @par         Example
 * @code
    Data = SPI_GetRxData(SPI0);
 * @endcode
 *******************************************************************************
 */
uint32_t SPI_GetRxData (SPI_Struct* SPIx)
{
    return SPIx->RDAT.W;
} 
 
/**
 *******************************************************************************
 * @brief  	    SPIx transmitted data register.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @param[in]   SPI_Byte:
 * 	@arg\b		    SPI_1Byte.
 * 	@arg\b		    SPI_2Byte.
 * 	@arg\b		    SPI_3Byte.
 * 	@arg\b		    SPI_4Byte.
 * @param[in]   SPI_DAT:
 * 	@arg\b		    uint32_t;
 * @return	    	
 * @note
 * @par         Example
 * @code
    SPI_SetTxData(SPI0, SPI_3Byte, 0x012345);
 * @endcode
 *******************************************************************************
 */
void SPI_SetTxData (SPI_Struct* SPIx, Byte_Enum SPI_Byte, uint32_t SPI_DAT)
{
    switch(SPI_Byte)
    {
        case SPI_1Byte: 
            SPIx->TDAT.B[0] = (uint8_t) SPI_DAT;
        break;
        
        case SPI_2Byte: 
            SPIx->TDAT.H[0] = (uint16_t) SPI_DAT;
        break;
        
        case SPI_3Byte: 
            SPIx->TDAT3.W = (uint32_t) SPI_DAT;
        break;
        
        case SPI_4Byte: 
            SPIx->TDAT.W = (uint32_t) SPI_DAT;
        break;
    }
}
 
/**
 *******************************************************************************
 * @brief  	    SPIx get transmitted data register.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @return	    uint32_t
 * 	@arg\b			0x00000000 ~ 0xFFFFFFFF.
 * @note
 * @par         Example
 * @code
    Data = SPI_GetTxData(SPI0);
 * @endcode
 *******************************************************************************
 */
uint32_t SPI_GetTxData (SPI_Struct* SPIx)
{
    return SPIx->TDAT.W;
}
 
/**
 *******************************************************************************
 * @brief  	    SPIx received data buffer high threshold for slave mode selection. 
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @param[in]   SPI_RxTH:
 * 	@arg\b		    SPI_1Byte.
 * 	@arg\b		    SPI_2Byte.
 * 	@arg\b		    SPI_3Byte.
 * 	@arg\b		    SPI_4Byte.
 * @return	    	
 * @note        Modify when SPI is slave.
 * @par         Example
 * @code
    SPI_SlaveModeReceivedThreshold_Select(SPI0, SPI_2Byte);
 * @endcode
 *******************************************************************************
 */
void SPI_SlaveModeReceivedThreshold_Select (SPI_Struct* SPIx, Byte_Enum SPI_RxTH)
{
    SPIx->CR2.MBIT.RX_TH = SPI_RxTH;
}
///@} 

 
/**
 * @name    Data Mode
 *
 */
///@{
/**
 *******************************************************************************
 * @brief  	    SPIx data size select
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0
 * @param[in]   SPI_DSIZES:
 * 	@arg\b		    SPI_4bits.
 * 	@arg\b	         ...
 * 	@arg\b		    SPI_32bits.
 * @return	    	
 * @note
 * @par         Example
 * @code
    SPI_DataSize_Select(SPI0, SPI_8bits);
 * @endcode
 *******************************************************************************
 */
void SPI_DataSize_Select (SPI_Struct* SPIx, DSIZE_Enum SPI_DSIZES)
{
    SPIx->CR2.MBIT.DSIZE = SPI_DSIZES;
}

/**
 *******************************************************************************
 * @brief  	    SPIx data line number select.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @param[in]   SPI_LINES:
 * 	@arg\b          SPI_Standard
 * 	@arg\b          SPI_1LineBidirection
 * 	@arg\b          SPI_2LinesBidirection
 * 	@arg\b          SPI_4LinesBidirection
 * 	@arg\b          SPI_4LinesDuplicate
 * 	@arg\b          SPI_8LinesBidirection
 * @return	    	
 * @note
 * @par         Example
 * @code
    SPI_DataLine_Select(SPI0, SPI_Standard);
 * @endcode
 *******************************************************************************
 */
void SPI_DataLine_Select (SPI_Struct* SPIx, DATALINE_Enum SPI_LINES)
{
    SPIx->CR2.MBIT.DAT_LINE = SPI_LINES;
}  

/**
 *******************************************************************************
 * @brief  	    SPIx data line output disable.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @param[in]   NewState:
 * 	@arg\b		    DISABLE.
 * 	@arg\b		    ENABLE.
 * @return	    	
 * @note
 * @par         Example
 * @code
    SPI_DataLineOutput_Cmd(SPI0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void SPI_DataLineOutput_Cmd (SPI_Struct* SPIx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        SPIx->CR2.MBIT.TX_DIS = 0;
    }
    else
    {
        SPIx->CR2.MBIT.TX_DIS = 1;
    }
}

/**
 *******************************************************************************
 * @brief  	    SPIx data transfer copy mode enable.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @param[in]   NewState:
 * 	@arg\b		    DISABLE.
 * 	@arg\b		    ENABLE.
 * @return	    	
 * @note        Support data line is 1-line, 2-lines and 4-lines.
 * @par         Example
 * @code
    SPI_SendCopyMode_Cmd(SPI0, DISABLE);
 * @endcode
 *******************************************************************************
 */
void SPI_SendCopyMode_Cmd (SPI_Struct* SPIx, FunctionalState NewState)
{
    SPIx->CR2.MBIT.COPY_EN = NewState;
    
#if defined(MG32_1ST)
    SPIx->CR2.MBIT.COPY_EN = DISABLE;
#endif
}

/**
 *******************************************************************************
 * @brief  	    SPIx data line bidirectional output enable.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @param[in]   NewState:
 * 	@arg\b		    DISABLE.
 * 	@arg\b		    ENABLE.
 * @return	    	
 * @note        Support data line is 1-line, 2-lines and 4-lines.
 * @par         Example
 * @code
    SPI_BidirectionalOutput_Cmd(SPI0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void SPI_BidirectionalOutput_Cmd (SPI_Struct* SPIx, FunctionalState NewState)
{ 
    SPIx->CR2.MBIT.BDIR_OE = NewState;
    
#if (defined(MG32_1ST))
    if(NewState != DISABLE)
    {
        if(PIND(2)->CR.MBIT.AFS == 7)
        {
            PIND(2)->CR.MBIT.IOM = 2;
        }
    }
    else
    {
        if(PIND(2)->CR.MBIT.AFS == 7)
        {
            PIND(2)->CR.MBIT.IOM = 3;
        }
    }
#endif
}

/**
 *******************************************************************************
 * @brief  	    SPIx transfer bidirection select input/output.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @param[in]   BDIR_SEL:
 * 	@arg\b		    SPI_BDIR_IN.
 * 	@arg\b		    SPI_BDIR_OUT.
 * @return	    	
 * @note        Support 1-line, 2-lines, 4-lines, 
 * @par         Example
 * @code
    SPI_TransferBidirection_Select (SPI0, SPI_BDIR_OUT);
 * @endcode
 *******************************************************************************
 */
void SPI_TransferBidirection_Select (SPI_Struct* SPIx, SPI_BDIR_Enum BDIR_SEL)
{
    
    SPIx->CR2.MBIT.BDIR_OE = BDIR_SEL;

#if (defined(MG32_1ST))    
    if(BDIR_SEL == SPI_BDIR_OUT)
    {
        if(PIND(2)->CR.MBIT.AFS == 7)
        {
            PIND(2)->CR.MBIT.IOM = 2;
        }
    }
    else
    {
        if(PIND(2)->CR.MBIT.AFS == 7)
        {
            PIND(2)->CR.MBIT.IOM = 3;
        }
    }
#endif
}

/**
 *******************************************************************************
 * @brief  	    SPIx I/O SPIx_MOSI,SPIx_MISO signals swap enable 
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @param[in]   NewState:
 * 	@arg\b		    DISABLE.
 * 	@arg\b		    ENABLE.
 * @return	    	
 * @note
 * @par         Example
 * @code
    SPI_MosiMisoSignalSwap_Cmd(SPI0, DISABLE);
 * @endcode
 *******************************************************************************
 */
void SPI_MosiMisoSignalSwap_Cmd (SPI_Struct* SPIx, FunctionalState NewState)
{
    SPIx->CR0.MBIT.IO_SWP = NewState;
}

#if (defined(MG32_3RD))
/**
 *******************************************************************************
 * @brief  	    SPIx I/O D0~3 and D4~7 signals swap enable 
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @param[in]   NewState:
 * 	@arg\b		    DISABLE.
 * 	@arg\b		    ENABLE.
 * @return	    	
 * @note
 * @par         Example
 * @code
    SPI_D03D47SignalSwap_Cmd(SPI0, DISABLE);
 * @endcode
 *******************************************************************************
 */
void SPI_D03D47SignalSwap_Cmd (SPI_Struct* SPIx, FunctionalState NewState)
{
    SPIx->CR0.MBIT.IO_SWP2 = NewState;
}
#endif
 
/**
 *******************************************************************************
 * @brief  	    SPIx Loop back mode enable bit.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @param[in]   NewState:
 * 	@arg\b		    DISABLE.
 * 	@arg\b		    ENABLE.
 * @return	    	
 * @note
 * @par         Example
 * @code
    SPI_LoopBackMode_Cmd(SPI0, DISABLE);
 * @endcode
 *******************************************************************************
 */
void SPI_LoopBackMode_Cmd (SPI_Struct* SPIx, FunctionalState NewState)
{
    SPIx->CR0.MBIT.LBM_EN = NewState;
}
 
/**
 *******************************************************************************
 * @brief  	    SPIx_CLK output signal select.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b          SPI0.
 * @param[in]   SPI_CKOS:
 * 	@arg\b          SPI_Clock.
 * 	@arg\b          EMB_MweSignal.
 * 	@arg\b          EMB_OeSignal.
 * 	@arg\b          TM10_CKOSignal.
 * 	@arg\b          TM16_CKOSignal.
 * 	@arg\b          TM20_CKOSignal.
 * @return  
 * @note
 * @par         Example
 * @code
    SPI_ClockOutputSignal_Select(SPI0, SPI_Clock);
 * @endcode
 *******************************************************************************
 */
void SPI_ClockOutputSignal_Select (SPI_Struct* SPIx, CKOMUX_Enum SPI_CKOS)
{
    SPIx->CR2.MBIT.CKO_MUX = SPI_CKOS;
}

#if (defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH))
/**
 *******************************************************************************
 * @brief  	    SPIx idle state data mode selection.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @param[in]   SPI_DOMDS:
 * 	@arg\b		    SPI_OutputWithTristate.
 * 	@arg\b		    SPI_OutputWithDriving.
 * @return	    	
 * @note
 * @par         Example
 * @code
    SPI_IdleStateDataMode_Select(SPI0, SPI_OutputWithTristate);
 * @endcode
 *******************************************************************************
 */
void SPI_IdleStateDataMode_Select (SPI_Struct* SPIx, DOUT_MDS_Enum SPI_DOMDS)
{
    SPIx->CR0.MBIT.DOUT_MDS = SPI_DOMDS;
}
#endif

#if (defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH))
/**
 *******************************************************************************
 * @brief  	    SPI auto full duplex data mode enable.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @param[in]   NewState:
 * 	@arg\b		    ENABLE.
 * 	@arg\b		    DISABLE.
 * @return	    	
 * @note        When this bit is enables and NSS input is changed from inactive 
 *              to active, the SPI0_DAT_LINE will auto force to 0 and change to
 *              full duplex standared SPI mode.
 * @par         Example
 * @code
    SPI_SlaveAutoFullDuplex_Cmd(SPI0, DISABLE);
 * @endcode
 *******************************************************************************
 */
void SPI_SlaveAutoFullDuplex_Cmd (SPI_Struct* SPIx, FunctionalState NewState)
{
    SPIx->CR0.MBIT.ADPX_EN = NewState;
}
#endif

#if (defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH))
/**
 *******************************************************************************
 * @brief  	    SPI slave mode transmitted data directly update enable
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @param[in]   NewState:
 * 	@arg\b		    ENABLE.
 * 	@arg\b		    DISABLE.
 * @return	    	
 * @note        
 * @par         Example
 * @code
    SPI_SlaveTransmittedDataDirectUpdate_Cmd(SPI0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void SPI_SlaveSendDataDirectUpdate_Cmd (SPI_Struct* SPIx, FunctionalState NewState)
{
    SPIx->CR2.MBIT.TXUPD_EN = NewState;
}
#endif

#if (defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH))
/**
 *******************************************************************************
 * @brief  	    SPI slave mode data read shadow buffer trigger to upload enable
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @param[in]   NewState:
 * 	@arg\b		    ENABLE.
 * 	@arg\b		    DISABLE.
 * @return	    	
 * @note        
 * @par         Example
 * @code
    SPI_SlaveDataReadShadowBufferTriggerToUpload_Cmd(SPI0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void SPI_SlaveDataReadShadowBufferTriggerToUpload_Cmd (SPI_Struct* SPIx, FunctionalState NewState)
{
    SPIx->CR2.MBIT.RSB_TRG = NewState;
}

#if defined(MG32_4TH)
/**
 *******************************************************************************
 * @brief  	    SPI slave mode data transmit timing control
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @param[in]   NewState:
 * 	@arg\b		    ENABLE.
 * 	@arg\b		    DISABLE.
 * @return	    	
 * @note        
 * @par         Example
 * @code
    SPI_SlaveDataTimingPrevious_Cmd(SPI0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void SPI_SlaveDataTimingPrevious_Cmd (SPI_Struct* SPIx, FunctionalState NewState)
{
    SPIx->CR0.MBIT.TX_CTL = NewState;
}
#endif


#endif
///@}


/**
 * @name	DMA
 *   		
 */
///@{
/**
 *******************************************************************************
 * @brief  	    Direct memory access enable to transmit.
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @param[in]   NewState:
 * 	@arg\b		    DISABLE.
 * 	@arg\b		    ENABLE.
 * @return	    	
 * @note
 * @par         Example
 * @code
    SPI_TXDMA_Cmd(SPI0, DISABLE);
 * @endcode
 *******************************************************************************
 */
void SPI_TXDMA_Cmd (SPI_Struct* SPIx, FunctionalState NewState)
{
    SPIx->CR0.MBIT.DMA_TXEN = NewState;
} 

/**
 *******************************************************************************
 * @brief  	    Direct memory access enable to receive. 
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @param[in]   NewState:
 * 	@arg\b		    DISABLE.
 * 	@arg\b		    ENABLE.
 * @return	    	
 * @note
 * @par         Example
 * @code
    SPI_RXDMA_Cmd(SPI0, DISABLE);
 * @endcode
 *******************************************************************************
 */
void SPI_RXDMA_Cmd (SPI_Struct* SPIx, FunctionalState NewState)
{
    SPIx->CR0.MBIT.DMA_RXEN = NewState;
}

#if (defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH))
/**
 *******************************************************************************
 * @brief  	    Direct memory access enable to do pre-catch one data for 
 *              receive mode. 
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @param[in]   NewState:
 * 	@arg\b		    DISABLE.
 * 	@arg\b		    ENABLE.
 * @return	    	
 * @note
 * @par         Example
 * @code
    SPI_RXDMAPreCatch_Cmd(SPI0, DISABLE);
 * @endcode
 *******************************************************************************
 */
void SPI_RXDMAPreCatch_Cmd (SPI_Struct* SPIx, FunctionalState NewState)
{
    SPIx->CR0.MBIT.DMA_MDS = NewState;
}   
#endif
///@}
 

/**
 * @name	Interrupt
 *   		
 */
///@{
/**
 *******************************************************************************
 * @brief  	    SPIx get all flag data
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @return	    uint32_t	
 * @note
 * @par         Example
 * @code
    AllFlag = SPI_GetAllFlagStatus(SPI0);
 * @endcode
 *******************************************************************************
 */
uint32_t SPI_GetAllFlagStatus (SPI_Struct* SPIx)
{
    return (SPIx->STA.W & 0x0000FFFF);
}

/**
 *******************************************************************************
 * @brief  	    SPIx get single flag status
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @param[in]   SPI_Flag
 * 	@arg\b			SPI_BSYF
 * 	@arg\b			SPI_IDLF
 * 	@arg\b			SPI_TCF
 * 	@arg\b			SPI_RXDF
 * 	@arg\b			SPI_RXF
 * 	@arg\b			SPI_TXF
 * 	@arg\b			SPI_MODF
 * 	@arg\b			SPI_WEF
 * 	@arg\b			SPI_ROVRF
 * 	@arg\b			SPI_TUDRF
 *  @arg\b          SPI_IDL_STA
 * @return      DRV_Return
 * 	@arg\b			DRV_Normal
 * 	@arg\b			DRV_Happened
 * @note
 * @par         Example
 * @code
    SPI_GetSingleFlagStatus(SPI0, SPI_TXF);
 * @endcode
 *******************************************************************************
 */
DRV_Return SPI_GetSingleFlagStatus (SPI_Struct* SPIx, uint32_t SPI_Flag)
{
    
    DRV_Return bitstatus = DRV_Normal;
    
    if((SPIx->STA.W & SPI_Flag) != 0)
    {
        bitstatus = DRV_Happened; 
    }
    
    return bitstatus;
}
 
/**
 *******************************************************************************
 * @brief  	    SPIx Clear intterupt source state
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0
 * @param[in]   SPI_Flag:
 * 	@arg\b			SPI_BSYF
 * 	@arg\b			SPI_IDLF
 * 	@arg\b			SPI_TCF
 * 	@arg\b			SPI_RXDF
 * 	@arg\b			SPI_RXF
 * 	@arg\b			SPI_TXF
 * 	@arg\b			SPI_MODF
 * 	@arg\b			SPI_WEF
 * 	@arg\b			SPI_ROVRF
 * 	@arg\b			SPI_TUDRF
 * 	@arg\b			SPI_ALLF
 * @return	    	
 * @note
 * @par         Example
 * @code
    SPI_ClearFlag(SPI0, SPI_TXF | SPI_RXF);
 * @endcode
 *******************************************************************************
 */
void SPI_ClearFlag (SPI_Struct* SPIx, uint32_t SPI_Flag)
{
    SPIx->STA.W = SPI_Flag;
}

/**
 *******************************************************************************
 * @brief  	    SPIx config interrupt source
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0
 * @param[in]   SPI_INTS:
 * 	@arg\b			SPI_INT_IDL
 * 	@arg\b			SPI_INT_TC
 * 	@arg\b			SPI_INT_RX
 * 	@arg\b			SPI_INT_TX
 * 	@arg\b			SPI_INT_MODF
 * 	@arg\b			SPI_INT_WE
 * 	@arg\b			SPI_INT_ROVR
 * 	@arg\b			SPI_INT_TUDR
 * @param[in]   NewState
 * 	@arg\b          DISABLE
 * 	@arg\b          ENABLE
 * @return	    	
 * @note
 * @par         Example
 * @code
    SPI_IT_Config(SPI0, SPI_INT_TC | SPI_INT_RX, ENABLE);
 * @endcode
 *******************************************************************************
 */
void SPI_IT_Config (SPI_Struct* SPIx, uint32_t SPI_INTS, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        SPIx->INT.W |= SPI_INTS;
    }
    else
    {
        SPIx->INT.W &= ~SPI_INTS;
    }
}
 
/**
 *******************************************************************************
 * @brief  	    SPIx enable/disable all interrupt 
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @param[in]   NewState:
 * 	@arg\b		    DISABLE.
 * 	@arg\b		    ENABLE.
 * @return	    	
 * @note
 * @par         Example
 * @code
    SPI_ITEA_Cmd(SPI0, DISABLE);
 * @endcode
 *******************************************************************************
 */
void SPI_ITEA_Cmd (SPI_Struct* SPIx, FunctionalState NewState)
{
    SPIx->INT.MBIT.IEA  = NewState;
}
///@}


/**
 * @name	New
 *   		
 */
///@{
#if (defined(MG32_3RD) || defined(MG32_4TH))
/**
 *******************************************************************************
 * @brief  	    SPI master mode data receive sampling next half-clock edge control bit 
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @param[in]   NewState:
 * 	@arg\b		    DISABLE.
 * 	@arg\b		    ENABLE.
 * @return	    	
 * @note
 * @par         Example
 * @code
    SPI_MasterRXSamplingNextHalfClockEdge_Cmd(SPI0, DISABLE);
 * @endcode
 *******************************************************************************
 */
void SPI_MasterRXSamplingNextHalfClockEdge_Cmd (SPI_Struct* SPIx, FunctionalState NewState)
{
    SPIx->CR0.MBIT.RX_CTL = NewState;
}   

/**
 *******************************************************************************
 * @brief  	    SPI standard slave mode clock input asynchronous function enable
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @param[in]   NewState:
 * 	@arg\b		    DISABLE.
 * 	@arg\b		    ENABLE.
 * @return	    	
 * @note
 * @par         Example
 * @code
    SPI_SlaveAsynchronous_Cmd(SPI0, DISABLE);
 * @endcode
 *******************************************************************************
 */
void SPI_SlaveAsynchronous_Cmd (SPI_Struct* SPIx, FunctionalState NewState)
{
    SPIx->CR0.MBIT.ASYNC_EN = NewState;
}   


/**
 *******************************************************************************
 * @brief  	    SPI idle state data output value
 * @details  
 * @param[in]   SPIx:
 * 	@arg\b			SPI0.
 * @param[in]   IdleState:
 * 	@arg\b		    SPI_DOUT_IDL_LastBit.
 * 	@arg\b		    SPI_DOUT_IDL_0.
 * 	@arg\b		    SPI_DOUT_IDL_1.
 * @return	    	
 * @note
 * @par         Example
 * @code
    SPI_MasterDataOutIdleState_Select(SPI0, SPI_DOUT_IDL_0);
 * @endcode
 *******************************************************************************
 */
void SPI_MasterDataOutIdleState_Select (SPI_Struct* SPIx, DOUT_IDL_Enum IdleState)
{
    SPIx->CR0.MBIT.DOUT_IDL = IdleState;

}
#endif
///@}

