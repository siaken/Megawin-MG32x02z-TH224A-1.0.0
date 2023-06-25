/**
 *******************************************************************************
 *
 * @file        MG32x02z_SPI_DRV.h
 *
 * @brief       This is the C code format driver head file for SPI module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.23
 * @date        2022/09/14
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2020 Megawin Technology Co., Ltd.
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
 
#include "MG32x02z__Common_DRV.h"
#include "MG32x02z_SPI.h"
#include "MG32x02z_GPIO.h"


#ifndef _MG32x02z_SPI_DRV_H
/*!< _MG32x02z_SPI_DRV_H */ 
#define _MG32x02z_SPI_DRV_H


/*! @name 
*/
/* @{ */ 
#define SPI_BUSYF   SPI_STA_BUSYF_mask_w    /*!< SPIx data transfer busy flag */
#define SPI_IDLF    SPI_STA_IDLF_mask_w     /*!< SPIx slave mode NSS idle detect flag */
#define SPI_TCF     SPI_STA_TCF_mask_w      /*!< SPIx transmission complete flag */
#define SPI_RXDF    SPI_STA_RXDF_mask_w     /*!< SPIx received data byte number is different from previous received data byte number for SPI0_RDAT register */
#define SPI_RXF     SPI_STA_RXF_mask_w      /*!< SPIx receive data buffer level high flag */
#define SPI_TXF     SPI_STA_TXF_mask_w      /*!< SPIx transmit data buffer level low flag */
#define SPI_MODF    SPI_STA_MODF_mask_w     /*!< SPIx mode detect fault flag */
#define SPI_WEF     SPI_STA_WEF_mask_w      /*!< SPIx slave mode write error flag */
#define SPI_ROVRF   SPI_STA_ROVRF_mask_w    /*!< SPIx receive overrun flag */
#define SPI_TUDRF   SPI_STA_TUDRF_mask_w    /*!< SPIx slave mode transmit underrun flag */
#if (defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH))
#define SPI_IDL_STA SPI_STA_IDL_STA_mask_w  /*!< SPIx master/slave mode NSS idle detect state*/
#endif
#define SPI_ALLF    SPI_IDLF | SPI_TCF | SPI_RXF | SPI_TXF | SPI_MODF | SPI_WEF | SPI_ROVRF | SPI_TUDRF /*!< All event and interrupt flag */
#define SPI_INT_IDL     SPI_INT_IDL_IE_mask_w   /*!< SPIx slave mode NSS idle detect interrupt enable */
#define SPI_INT_TC      SPI_INT_TC_IE_mask_w    /*!< SPIx transmission complete interrupt enable */
#define SPI_INT_RX      SPI_INT_RX_IE_mask_w    /*!< SPIx Receive data register not empty interrupt enable */
#define SPI_INT_TX      SPI_INT_TX_IE_mask_w    /*!< SPIx TX buffer underflow the threshold SPI0_TX_TH Interrupt enable */
#define SPI_INT_MODF    SPI_INT_MODF_IE_mask_w  /*!< SPIx mode detect fault interrupt enable */
#define SPI_INT_WE      SPI_INT_WE_IE_mask_w    /*!< SPIx slave mode write error interrupt enable */
#define SPI_INT_ROVR    SPI_INT_ROVR_IE_mask_w  /*!< SPIx RX buffer receive overrun interrupt enable */
#define SPI_INT_TUDR    SPI_INT_TUDR_IE_mask_w  /*!< SPIx TX buffer transmit underrun interrupt enable */

/* @} */


#ifdef __cplusplus
extern "C"{
#endif // __cplusplus


/*! @enum   SPI_CLKS_Enum
    @brief  SPIx internal clock CK_SPIx source selection.
*/
typedef enum
{
    SPI_CK_SPIx_PR      = 0,    /*!< PROC : CK_SPI0_PR process clock from CSC */
    SPI_TM00_TRGO       = 2     /*!< TM00_TRGO */
}SPI_CLKS_Enum;


/*! @enum   SPI_PDIV_Enum
    @brief  SPIx process clock CK_SPIx_PR input divide selection.
*/
typedef enum
{
    SPI_PDIV_1      = 0,    /* divided by 1 */
    SPI_PDIV_2      = 1,    /* divided by 2 */
    SPI_PDIV_4      = 2,    /* divided by 4 */
    SPI_PDIV_8      = 3     /* divided by 8 */
}SPI_PDIV_Enum;


/*! @enum   SPI_PSC_Enum
    @brief  SPIx internal clock CK_SPIx_INT prescaler selection.
*/
typedef enum
{
    SPI_PSC_1       = 0,    /* divided 1 */
    SPI_PSC_2       = 1,    /* divided 2 */
    SPI_PSC_3       = 2,    /* divided 3 */
    SPI_PSC_4       = 3,    /* divided 4 */
    SPI_PSC_5       = 4,    /* divided 5 */
    SPI_PSC_6       = 5,    /* divided 6 */
    SPI_PSC_7       = 6,    /* divided 7 */
    SPI_PSC_8       = 7     /* divided 8 */
}SPI_PSC_Enum;
   

/*! @enum   SPI_DIV_Enum
    @brief  SPIx internal clock CK_SPIx_INT input divider selection.
*/
typedef enum
{
    SPI_DIV_2      = 0,    /* divided by 2 */
    SPI_DIV_4      = 1,    /* divided by 4 */
    SPI_DIV_8      = 2,    /* divided by 8 */
    SPI_DIV_16     = 3     /* divided by 16 */
}SPI_DIV_Enum;


/*! @enum   TRS_Enum
    @brief  SPIx transfer rate selection
*/
typedef enum
{
    SPI_StandardTransferRate    = 0,    /*!< Standard transfer rate */
    SPI_DualTransferRate        = 1     /*!< Dual transfer rate */
} TRS_Enum;


/*! @enum   MODNSS_Enum
    @brief  SPIx mode and NSS inputp/output selection.
*/
typedef enum
{
    SPI_Master                  = 0x00000010,   /* Master without NSS output */
    SPI_MasterWithNss           = 0x00000110,   /* Master with NSS output */
    SPI_MasterWithMODF          = 0x00000210,   /* Master without NSS output and with MODF function */
    SPI_MasterWithNssAndMODF    = 0x00000310,   /* Master with NSS output and with MODF function */
    SPI_Slave                   = 0x00000000,   /* Slave without NSS intput */
    SPI_SlaveWithNss            = 0x00000200    /* Slave with NSS intput */
} MODNSS_Enum;



/*! @enum   MODF_Enum
    @brief  SPIx function select when master mode fault detect.
*/
typedef enum
{
    SPI_DisableSPI      = 0,    /* SPI disable */
    SPI_SwitchToSlave   = 1     /* Switch to slave */
} MODF_Enum;



/*! @enum   NSSI_Enum
    @brief  SPI0 pin select for NSS input signal.
*/
typedef enum
{
    SPI_NssPin  = 0,    /* SPI0_NSS pin */ 
    SPI_NssiPin = 1     /* SPI0_NSSI pin */
} NSSI_Enum;


/*! @enum   CPHA_Enum
    @brief  SPI clock phase selection.
*/
typedef enum
{
    SPI_LeadingEdge     = 0,    /* Leading edge */
    SPI_TrailingEdge    = 1     /* Trailing edge */
} CPHA_Enum;


/*! @enum   CPOL_Enum 
    @brief  SPI clock polarity selection.
*/
typedef enum
{
    SPI_Low     = 0,    /* Low */
    SPI_High    = 1     /* High */
} CPOL_Enum;


/*! @enum   RNUM_Enum
    @brief  SPI set RNUM data 
*/
typedef enum
{
    SPI_RNUM_0Byte  = 0,    /* 0-byte */
    SPI_RNUM_1Byte  = 1,    /* 1-byte */
    SPI_RNUM_2Byte  = 2,    /* 2-byte */
    SPI_RNUM_3Byte  = 3,    /* 3-byte */
    SPI_RNUM_4Byte  = 4     /* 4-byte */
} RNUM_Enum;


/*! @enum   Byte_Enum
    @brief  Transmit bytes number selection.
*/
typedef enum
{
    SPI_1Byte   = 0,    /* Transmit 1byte */
    SPI_2Byte   = 1,    /* Transmit 2byte */
    SPI_3Byte   = 2,    /* Transmit 3byte */
    SPI_4Byte   = 3     /* Transmit 4byte */
} Byte_Enum;


/*! @enum   DSIZE_Enum
    @brief  SPI transfer data frame bit size from 4-bit to 32-bit.
*/
typedef enum
{
    SPI_4bits   = 4,    /**/
    SPI_5bits   = 5, 
    SPI_6bits   = 6,     
    SPI_7bits   = 7,     
    SPI_8bits   = 8,     
    SPI_9bits   = 9,     
    SPI_10bits  = 10,     
    SPI_11bits  = 11,     
    SPI_12bits  = 12,     
    SPI_13bits  = 13, 
    SPI_14bits  = 14,     
    SPI_15bits  = 15,     
    SPI_16bits  = 16,     
    SPI_17bits  = 17,     
    SPI_18bits  = 18,     
    SPI_19bits  = 19,     
    SPI_20bits  = 20,  
    SPI_21bits  = 21, 
    SPI_22bits  = 22,     
    SPI_23bits  = 23,     
    SPI_24bits  = 24,     
    SPI_25bits  = 25,     
    SPI_26bits  = 26,     
    SPI_27bits  = 27,     
    SPI_28bits  = 28,  
    SPI_29bits  = 29, 
    SPI_30bits  = 30,     
    SPI_31bits  = 31,     
    SPI_32bits  = 0   
} DSIZE_Enum;


/*! @enum   DATALINE_Enum
    @brief  SPI data line number selection.
*/
typedef enum
{
    SPI_Standard            = 0,    /* 2-lines separated~ standard SPI mode */
    SPI_1LineBidirection    = 1,    /* 1-line Bidirectional~ SPI0_MOSI */
    SPI_2LinesBidirection   = 2,    /* 2-lines Bidirectional~ SPI0_D0(MOSI), SPI0_D1(MISO) */
    SPI_4LinesBidirection   = 3,    /* 4-lines Bidirectional~ SPI0_D0 ~ SPI0_D3 */
#if (defined(MG32_1ST) || defined(MG32_3RD))
    SPI_4LinesDuplicate     = 4,    /* 8-lines TX~ SPI0_D0 ~ SPI0_D3 with duplicate SPI0_D4 ~ SPI0_D7 */
    SPI_8LinesBidirection   = 5     /* 8-lines Bidirectional~ SPI0_D0 ~ SPI0_D7 */
#endif
} DATALINE_Enum;


/*! @enum   CKOMUX_Enum
    @brief  SPI CLK output signal selection.
*/
typedef enum
{
    SPI_Clock       = 0,    /* SPI clock */
#if (defined(MG32_1ST) || defined(MG32_3RD))
    EMB_MweSignal   = 1,    /* EMB MWE signal */
    EMB_MoeSignal   = 2,    /* EMB MOE signal */
#endif
    TM10_CKOSignal  = 3,    /* TM10_CKO */
#if (defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH))
    TM20_CKOSignal  = 5,    /* TM20_CKO */
#endif
    TM16_CKOSignal  = 4     /* TM16_CKO */
} CKOMUX_Enum;


/*! @enum   SPI_FBS_Enum
    @brief  SPI data order first bit selection.
*/
typedef enum
{
    SPI_MSB     = 0,    /*!< Trsamit and receive first bit is MSB */
    SPI_LSB     = 1     /*!< Trsamit and receive first bit is LSB */
}SPI_FBS_Enum;


/*! @enum   SPI_BDIR_Enum
    @brief  SPIx transfer bidirection select.
*/
typedef enum
{
    SPI_BDIR_IN     = 0,    /*!< Transfer bidirectional input */
    SPI_BDIR_OUT    = 1     /*!< Transfer bidirectional output */
}SPI_BDIR_Enum;


/*! @enum   IDT_Enum
    @brief  SPIx master NSS idle time selection
*/
typedef enum
{
    SPI_IDT_1T  = 0,    /*!< Master NSS idle time 1T */
    SPI_IDT_2T  = 1     /*!< Master NSS idle time 2T */
}IDT_Enum;

/*! @enum   DOUT_MDS_Enum
    @brief  SPIx idle state data mode selection
*/
typedef enum
{
    SPI_OutputWithTristate = 0, /*!< Output with tristate */
    SPI_OutputWithDriving  = 1  /*!< Output with driving */
}DOUT_MDS_Enum;

/*! @enum   DOUT_IDL_Enum
    @brief  SPI idle state data output selection
*/
typedef enum
{
    SPI_DOUT_IDL_LastBit = 0,   /*!< Data output idle last bit */
    SPI_DOUT_IDL_0       = 2,   /*!< Data output idle 0 */
    SPI_DOUT_IDL_1       = 3    /*!< Data output idle 1 */
}DOUT_IDL_Enum;


/*! @name
*/       
/* @{ */ 


/**
 * @name    Function announce
 *
 */ 
///@{  
void SPI_DeInit (SPI_Struct* SPIx);

void SPI_Clock_Select (SPI_Struct* SPIx, SPI_CLKS_Enum SPI_CLKS);
void SPI_PreDivider_Select (SPI_Struct* SPIx, SPI_PDIV_Enum SPI_PDIVS);
void SPI_Prescaler_Select (SPI_Struct* SPIx, SPI_PSC_Enum SPI_PSCS);
void SPI_Divider_Select (SPI_Struct* SPIx, SPI_DIV_Enum SPI_DIVS);

void SPI_ModeAndNss_Select (SPI_Struct* SPIx, MODNSS_Enum SPI_MNS);
void SPI_ModfHappenedAction_Select (SPI_Struct* SPIx, MODF_Enum SPI_MODFS);

void SPI_NSSInputSignal_Select (SPI_Struct* SPIx, NSSI_Enum SPI_NSSIS);
void SPI_SingleMasterModeNssPulse_Cmd (SPI_Struct* SPIx, FunctionalState NewState);
void SPI_NssInputInverse_Cmd (SPI_Struct* SPIx, FunctionalState NewState);
void SPI_NssOutputInverse_Cmd (SPI_Struct* SPIx, FunctionalState NewState);
void SPI_NssInputOutputSoftwareControl_Cmd (SPI_Struct* SPIx, FunctionalState NewState);
     
void SPI_NSSInputStatusControl_SW (SPI_Struct* SPIx, uint8_t NewStatus);
DRV_Return SPI_GetNSSInputStatust (SPI_Struct* SPIx);
void SPI_NSSOutputStatusControl_SW (SPI_Struct* SPIx, uint8_t NewStatus);
void SPI_Cmd(SPI_Struct* SPIx, FunctionalState NewState);

void SPI_ClockPhase_Select (SPI_Struct* SPIx, CPHA_Enum SPI_CPHAS);
void SPI_ClockPolarity_Select (SPI_Struct* SPIx, CPOL_Enum SPI_CPOLS);
void SPI_FirstBit_Select (SPI_Struct* SPIx, SPI_FBS_Enum SPI_FBS);

uint8_t SPI_GetRxShadowBufferLevel (SPI_Struct* SPIx);
void SPI_ClearRxData (SPI_Struct* SPIx);
uint8_t SPI_GetDataBufferReceivedBytes (SPI_Struct* SPIx);
void SPI_SetDataBufferReceivedBytes (SPI_Struct* SPIx, RNUM_Enum SPI_RNUMS);
void SPI_ClearTxData (SPI_Struct* SPIx);
uint8_t SPI_GetTxShadowBufferLevel (SPI_Struct* SPIx);
uint32_t SPI_GetRxData (SPI_Struct* SPIx);
void SPI_SetTxData (SPI_Struct* SPIx, Byte_Enum SPI_Byte, uint32_t SPI_DAT);
uint32_t SPI_GetTxData (SPI_Struct* SPIx);
void SPI_SlaveModeReceivedThreshold_Select (SPI_Struct* SPIx, Byte_Enum SPI_RxTH);

void SPI_DataSize_Select (SPI_Struct* SPIx, DSIZE_Enum SPI_DSIZES);
void SPI_DataLine_Select (SPI_Struct* SPIx, DATALINE_Enum SPI_LINES);
void SPI_DataLineOutput_Cmd (SPI_Struct* SPIx, FunctionalState NewState);
void SPI_SendCopyMode_Cmd (SPI_Struct* SPIx, FunctionalState NewState);
void SPI_BidirectionalOutput_Cmd (SPI_Struct* SPIx, FunctionalState NewState);
void SPI_TransferBidirection_Select (SPI_Struct* SPIx, SPI_BDIR_Enum BDIR_SEL);
void SPI_MosiMisoSignalSwap_Cmd (SPI_Struct* SPIx, FunctionalState NewState);
#if (defined(MG32_3RD))
void SPI_D03D47SignalSwap_Cmd (SPI_Struct* SPIx, FunctionalState NewState);
#endif
void SPI_LoopBackMode_Cmd (SPI_Struct* SPIx, FunctionalState NewState);
void SPI_ClockOutputSignal_Select (SPI_Struct* SPIx, CKOMUX_Enum SPI_CKOS);

void SPI_TXDMA_Cmd (SPI_Struct* SPIx, FunctionalState NewState);
void SPI_RXDMA_Cmd (SPI_Struct* SPIx, FunctionalState NewState);
void SPI_RXDMAPreCatch_Cmd (SPI_Struct* SPIx, FunctionalState NewState);

uint32_t SPI_GetAllFlagStatus (SPI_Struct* SPIx);
DRV_Return SPI_GetSingleFlagStatus (SPI_Struct* SPIx, uint32_t SPI_Flag);
void SPI_ClearFlag (SPI_Struct* SPIx, uint32_t SPI_Flag);
void SPI_IT_Config (SPI_Struct* SPIx, uint32_t SPI_INTS, FunctionalState NewState);
uint32_t SPI_GetITStatus (SPI_Struct* SPIx);
void SPI_ITEA_Cmd (SPI_Struct* SPIx, FunctionalState NewState);

#if (defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH))
void SPI_DualTransferRate_Select (SPI_Struct* SPIx, TRS_Enum SPI_TRS);
void SPI_NssIdleTime_Select (SPI_Struct* SPIx, IDT_Enum SPI_IDTS);
void SPI_SlaveAutoFullDuplex_Cmd (SPI_Struct* SPIx, FunctionalState NewState);
void SPI_IdleStateDataMode_Select (SPI_Struct* SPIx, DOUT_MDS_Enum SPI_DOMDS);
void SPI_NssInputSoftwareControl_Cmd (SPI_Struct* SPIx, FunctionalState NewState);
void SPI_TriggerClockToggle (SPI_Struct* SPIx);
void SPI_SlaveHighSpeed_Cmd (SPI_Struct* SPIx, FunctionalState NewState);
void SPI_NssOutputSoftwareControl_Cmd (SPI_Struct* SPIx, FunctionalState NewState);
void SPI_SlaveSendDataDirectUpdate_Cmd (SPI_Struct* SPIx, FunctionalState NewState);
void SPI_SlaveDataReadShadowBufferTriggerToUpload_Cmd (SPI_Struct* SPIx, FunctionalState NewState);
#endif

#if (defined(MG32_3RD) || defined(MG32_4TH))
void SPI_MasterRXSamplingNextHalfClockEdge_Cmd (SPI_Struct* SPIx, FunctionalState NewState);
void SPI_SlaveAsynchronous_Cmd (SPI_Struct* SPIx, FunctionalState NewState);
void SPI_MasterDataOutIdleState_Select (SPI_Struct* SPIx, DOUT_IDL_Enum IdleState);
#endif

#if (defined(MG32_4TH))
void SPI_SlaveDataTimingPrevious_Cmd (SPI_Struct* SPIx, FunctionalState NewState);
#endif


///@}


#ifdef __cplusplus
}
#endif // __cplusplus

#endif  //_MG32x02z_SPI_DRV_H


