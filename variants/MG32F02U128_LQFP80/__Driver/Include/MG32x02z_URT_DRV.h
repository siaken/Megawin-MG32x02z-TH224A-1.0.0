




/**
 ******************************************************************************
 *
 * @file        MG32x02z_URT_DRV.H
 *
 * @brief       This file contains all the functions prototypes for the URT
 *              firmware library.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.19
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
 
#ifndef _MG32x02z_URT_DRV_H
 
#define _MG32x02z_URT_DRV_H
 
#include "MG32x02z.h" 
#include "MG32x02z__Common_DRV.h" 
#include "MG32x02z_URT.h"


///@{
#define URT_IT_CALTMO    URT_STA_CALTMOF_mask_w     /*!< Baud rate calibration sync field receive time out interrupt. */
#define URT_IT_BKTMO     URT_STA_BKTMOF_mask_w      /*!< Break receive time out interrupt. */
#define URT_IT_IDTMO     URT_STA_IDTMOF_mask_w      /*!< Idle state time out interrupt. */
#define URT_IT_RXTMO     URT_STA_RXTMOF_mask_w      /*!< Receive time out interrupt. */
#if defined(URT_STA_TUDRF_mask_w)
#define URT_IT_TUDR      URT_STA_TUDRF_mask_w       /*!< URT SPI Slave mode transmit underrun interrupt.*/
#endif
#define URT_IT_TXE       URT_STA_TXEF_mask_w        /*!< TX error detect interrupt. */
#define URT_IT_ROVR      URT_STA_ROVRF_mask_w       /*!< Receive overrun error interrupt. */
#define URT_IT_NCE       URT_STA_NCEF_mask_w        /*!< Receive noised character error detect interrupt. */
#define URT_IT_FE        URT_STA_FEF_mask_w         /*!< Receive frame error detect interrupt. */
#define URT_IT_PE        URT_STA_PEF_mask_w         /*!< Receive parity error detect interrupt. */
#define URT_IT_CTS       URT_STA_CTSF_mask_w        /*!< CTS change detect interrupt. */
#define URT_IT_IDL       URT_STA_IDLF_mask_w        /*!< RX idle line detect interrupt. */
#define URT_IT_BK        URT_STA_BKF_mask_w         /*!< Break condition detect interrupt. */
#define URT_IT_CALC      URT_STA_CALCF_mask_w       /*!< Auto baudrate calibration complete interrupt. */
#define URT_IT_TMO       URT_STA_TMOF_mask_w        /*!< Timeout timer timeout interrupt. */
#define URT_IT_BRT       URT_STA_BRTF_mask_w        /*!< Baud rate generator timer timeout interrupt. */
#define URT_IT_SADR      URT_STA_SADRF_mask_w       /*!< Slave address matched interrupt. */
#define URT_IT_TX        URT_STA_TXF_mask_w         /*!< Transmit data register empty interrupt. */
#define URT_IT_RX        URT_STA_RXF_mask_w         /*!< Receive data register not empty interrupt. */
#define URT_IT_LS        URT_STA_LSF_mask_w         /*!< URT line status relationship interrupt. */
#define URT_IT_ERR       URT_STA_ERRF_mask_w        /*!< URT error relationship interrupt. */
#define URT_IT_TC        URT_STA_TCF_mask_w         /*!< Transmission complete interrupt.(shadow buffer , data register , shift buffer empty) */
#define URT_IT_UG        URT_STA_UGF_mask_w         /*!< URT genernal event relationship interrupt. */
#define URT_IT_Mask      0x7BF73CDE                 /*!< Compare URT interrupt setting range. */


#define URT_EVENT_RXDF    URT_STA_RXDF_mask_w       /*!< URT received data byte number is different from previous received data byte number for URT_RDAT */
#define URT_EVENT_RHF     URT_STA_RHF_mask_w        /*!< URT received hold flag. */
#define URT_EVENT_IRBUSYF URT_STA2_IR_BUSYF_mask_w  /*!< URT IrDa data received busy flag. */
#define URT_EVENT_BKBF    URT_STA2_BKBF_mask_w      /*!< URT send break busy flag. */
#define URT_EVENT_NCF     URT_STA2_NCF_mask_w       /*!< URT receive noised character flag. */
#define URT_EVENT_RXBUSYF URT_STA2_BUSYF_mask_w     /*!< URT RX busy flag. */

#if defined(URT_STA_CALOVF_mask_w)
    #define URT_EVENT_CALOVF    URT_STA_CALOVF_mask_w   /*!<The event flag is that result of calibration is overflow baudrate generator counter.*/
#endif
#if defined(URT_STA_CALUDF_mask_w)
    #define URT_EVENT_CALUDF    URT_STA_CALUDF_mask_w   /*!<The event flag is that result of calibration is underflow baudrate generator counter.*/
#endif
///@}


///@{
#define URT_ExitMute_IdleDetect         URT_MUTE_MUTE_AEX2_enable_b2  /*!<URT auto exit mute mode definitions*/ 
#define URT_ExitMute_BreakDetect        URT_MUTE_MUTE_AEX1_enable_b2  /*!<URT auto exit mute mode definitions*/ 
#define URT_ExitMute_AddressMatch       URT_MUTE_MUTE_AEX0_enable_b2  /*!<URT auto exit mute mode definitions*/ 

#define URT_EnterMute_idleDetect        URT_MUTE_MUTE_AEN1_enable_b1  /*!<URT auto enter mute mode definitions*/ 
#define URT_EnterMute_AddressUnmatch    URT_MUTE_MUTE_AEN0_enable_b1  /*!<URT auto enter mute mode definitions*/ 
///@}


///@{
//#define 

///@}


///@{
/*! @enum   URT_STOP_TypeDef
    @brief  URT stop bit select definitions.
*/
typedef enum
{
    #if defined(URT_CR1_RXSTP_LEN_0_5bit_w)
        URT_StopBits_0_5  = 0x00,                                         /*!< URT stop bit is 0.5bit. */ 
    #endif
    
	URT_StopBits_1_0  = 0x40,                                             /*!< URT stop bit is 1bit.   */
    
    #if defined(URT_CR1_RXSTP_LEN_1_5bit_w)
        URT_StopBits_1_5  = 0x80,                                         /*!< URT stop bit is 1.5bit. */    
    #endif
    
	URT_StopBits_2_0  = 0xC0                                              /*!< URT stop bit is 2bit.   */
    
}URT_STOP_TypeDef;

/*! @enum   URT_DataOrder_TypeDef
    @brief  URT data order select definitions.
*/ 
typedef enum
{
	URT_DataTyped_LSB    = 0x00,       /*!< URT data order is LSB */
	URT_DataTyped_MSB    = 0x20        /*!< URT data order is MSB */
}URT_DataOrder_TypeDef;

/*! @enum   URT_Parity_TypeDef
    @brief  URT parity bit select definitions.
*/ 
typedef enum 
{
   	URT_Parity_No		= 0x00,        /*!< URT no parity bit. */
	URT_Parity_Even	    = 0x04,        /*!< URT parity bit is even. */   
	URT_Parity_Odd 	    = 0x0C,        /*!< URT parity bit is oddd. */
	URT_Parity_All_H	= 0x1C,        /*!< URT parity bit always is H.*/
	URT_Parity_All_L	= 0x14         /*!< URT parity bit always is L.*/
}URT_Parity_TypeDef;

/*! @enum   URT_DataLength_TypeDef
    @brief  URT data length select definitions.
*/ 
typedef enum
{
	URT_DataLength_8      = 0x00,      /*!< URT data length is 8 bit. */ 
    URT_DataLength_7      = 0x01       /*!< URT data length is 7 bit. */
}URT_DataLength_TypeDef;


/*! @enum   URT_Mode_TypeDef
    @brief  URT mode configuration
*/
typedef enum
{
	URT_URT_mode     = URT_CR0_MDS_uart_w,        /*!< Uart mode*/
	URT_SYNC_mode    = URT_CR0_MDS_sync_w,        /*!< Synchronous/Shift-Register mode*/
	URT_IDLE_mode    = URT_CR0_MDS_idle_w,        /*!< Idle-line mode for multi-processor*/
	URT_ADR_mode     = URT_CR0_MDS_adr_w          /*!< Address-bit mode for multi-processor*/
}URT_Mode_TypeDef;


#if defined(URT_CR0_SYNC_MDS_mask_w)
/*! @enum   URT_SYNCMode_TypeDef
    @brief  URT SYNC mode configuration
*/
typedef enum
{
    URT_SYNC_MASTER    = URT_CR0_SYNC_MDS_master_w,
    URT_SYNC_SLAVE     = URT_CR0_SYNC_MDS_slave_w
}URT_SYNCMode_TypeDef;
#endif

/*! @enum   URT_DataLine_TypeDef
    @brief  Data line select definitions.
*/
typedef enum
{
    URT_DataLine_2     =  URT_CR0_DAT_LINE_2_b0,         /*!< URT Data line is 2-line.*/
    URT_DataLine_1     =  URT_CR0_DAT_LINE_1_b0          /*!< URT Data line is 1-line.*/
}URT_DataLine_TypeDef;
///@}



///@{
/*! @enum   URT_BDMode_TypeDef
    @brief  URT Baud rate generator mode select definitions.
*/ 
typedef enum
{
    URT_BDMode_Separated    =   URT_CLK_BR_MDS_separated_w,    /*!< Pre counter and baudrate counter relationship is separated */
    URT_BDMode_Combined     =   URT_CLK_BR_MDS_combined_w      /*!< Pre counter and baudrate counter relationship is combined*/
}URT_BDMode_TypeDef;

/*! @enum   URT_BDClock_TypeDef
    @brief  URT Baud rate generator clock source select definitions.
*/ 
typedef enum
{
    URT_BDClock_PROC         =  URT_CLK_CK_SEL_proc_w,                                               /*!< URT baud rate generator clock source from PROC. */
    URT_BDClock_LS           =  URT_CLK_CK_SEL_ck_ls_w,                                              /*!< URT baud rate generator clock source from LS. */
    
    #if defined(URT_CLK_CK_SEL_ext_clk_w)
        URT_BDClock_EXT      =  URT_CLK_CK_SEL_ext_clk_w,                                            /*!< URT baud rate generator clock source from External pin*/
    #endif
    
    #if defined(URT_CLK_CK_SEL_nco0_p0_w)
        URT_BDClock_NCO0_P0  =  URT_CLK_CK_SEL_nco0_p0_w,                                            /*!< URT baud rate generator clock source from NCO0_P0*/
    #endif
    
    URT_BDClock_Timer00TRGO  =  URT_CLK_CK_SEL_tm00_trgo_w                                           /*!< URT baud rate generator clock source from TRGO. */ 
    
}URT_BDClock_TypeDef;


#if defined(URT_CLK_BR_CKS_mask_w)
/*! @enum   URT_BRCounterClock_TypeDef
    @brief  UART baud-rate timer clock source select.
*/ 
typedef enum
{
    URT_BRCountClock_PSC     = URT_CLK_BR_CKS_psc_w,                           /*!< URT baud-rate timer clock source from clock prescaler output.*/                          
    URT_BRCountClock_CK_URT  = URT_CLK_BR_CKS_ck_urtx_w                        /*!< URT baud-rate timer clock source from URT internal clock input.*/
}URT_BRCounterClock_TypeDef;

#endif


/*! @enum   URT_CLKSource_TypeDef
    @brief  URT URT_CLK output clock source
*/
typedef enum
{
    URT_CK_OUT 	    =	URT_CLK_CLK_CKS_out_w,                                 /*!< URT_CLK output clock source from CK_URTx_OUT*/
	URT_CK_SC		=	URT_CLK_CLK_CKS_sc_w                                   /*!< URT_CLK output clock source from CK_URTx_SC */
}URT_CLKSource_TypeDef;


/*! @enum  URT_TXClock_TypeDef
    @brief URT TX clock source select definitions.
*/
typedef enum
{
    URT_TXClock_Internal     =  URT_CLK_TX_CKS_internal_w,                    /*!< URT TX clock source from Baudrate generator. */
    URT_TXClock_Timer01TRGO  =  URT_CLK_TX_CKS_tm01_trgo_w,                   /*!< URT TX clock source from Timer01 TRGO. */
    #if defined(URT_CLK_TX_CKS_ext_clk_w)
        URT_TXClock_EXT      =  URT_CLK_TX_CKS_ext_clk_w,                     /*!< URT TX clock source from external pin. */
    #endif
    URT_TXClock_Timer10TRGO  =  URT_CLK_TX_CKS_tm10_trgo_w                    /*!< URT TX clock source from Timer10 TRGO. */
}URT_TXClock_TypeDef;


/*! @enum  URT_RXClock_TypeDef
    @brief URT RX clock source select definitions.
*/
typedef enum
{
    URT_RXClock_Internal     =  URT_CLK_RX_CKS_internal_w,                     /*!< URT RX clock source from Baudrate generator. */
    URT_RXClock_Timer01TRGO  =  URT_CLK_RX_CKS_tm01_trgo_w,                    /*!< URT RX clock source from Timer01 TRGO. */
    #if defined(URT_CLK_RX_CKS_ext_clk_w)
        URT_RXClock_EXT      =  URT_CLK_RX_CKS_ext_clk_w,                      /*!< URT TX clock source from external pin. */
    #endif
    URT_RXClock_Timer10TRGO  =  URT_CLK_RX_CKS_tm10_trgo_w                     /*!< URT RX clock source from Timer10 TRGO. */   
}URT_RXClock_TypeDef;


/*! @enum   URT_RXSMP_TypeDef
    @brief  URT RX oversample time mode
*/
typedef enum
{
	URT_RXSMP_3TIME		= URT_CR0_OS_MDS_three_w,                 /*!< URT RX data oversampling majority vote from 3 sample bits method. */               
	URT_RXSMP_1TIME		= URT_CR0_OS_MDS_one_w                    /*!< URT RX data oversampling majority vote from one sample bit method and noise free.*/
}URT_RXSMP_TypeDef;


///@}


///@{


/*! @enum   URT_TMOMDS_TypeDef
    @brief  URT timerout timer mode source select definitions.
*/
typedef enum
{
   URT_TMOMDS_URT     = URT_TMOUT_TMO_MDS_uart_w,       /*!< Timeout timer mode is URT mode ( URT detect timeout using) */
   URT_TMOMDS_General = URT_TMOUT_TMO_MDS_general_w     /*!< Timeout timer mode is general mode ( General timer using )*/
}URT_TMOMDS_TypeDef; 


/*! @enum   URT_TMOCLK_TypeDef
    @brief  URT timerout timer clock source select definitions.
*/
typedef enum
{
	URT_TMOCLK_BitTime  = URT_TMOUT_TMO_CKS_uart_w,      /*!< Timeout timer clock source is from RX baudrate.*/
	URT_TMOCLK_CK_URTX  = URT_TMOUT_TMO_CKS_input_w,     /*!< Timeout timer clock source is from URT function clock source*/
	URT_TMOCLK_Noise    = URT_TMOUT_TMO_CKS_noise_w      /*!< Timeout timer clock source is from Noise detect time.*/
}URT_TMOCLK_TypeDef;

///@}



///@{

/*! @enum   URT_RXTH_TypeDef
    @brief  URT RX shadow buffer threshold byte number select definitions.
*/
typedef enum
{
    URT_RXTH_1BYTE   =  URT_CR0_RX_TH_1byte_w,       /*!< URT RX shadow buffer threshold is 1 byte */
    URT_RXTH_2BYTE   =  URT_CR0_RX_TH_2byte_w,       /*!< URT RX shadow buffer threshold is 2 byte */
    URT_RXTH_3BYTE   =  URT_CR0_RX_TH_3byte_w,       /*!< URT RX shadow buffer threshold is 3 byte */
    URT_RXTH_4BYTE   =  URT_CR0_RX_TH_4byte_w        /*!< URT RX shadow buffer threshold is 4 byte */
}URT_RXTH_TypeDef;


/*! @enum   URT_RCAP_TypeDef
    @brief  URT capture status bit select definitions.
*/
typedef enum
{
    URT_RCAP_ADR    =   URT_RCAP_RCAP_ADR_mask_w,      /*!< Capture address bit value.*/    
    URT_RCAP_PAR    =   URT_RCAP_RCAP_PAR_mask_w,      /*!< Capture parity bit value.*/
    URT_RCAP_STP    =   URT_RCAP_RCAP_STP_mask_w       /*!< Capture stop bit value.*/
}URT_RCAP_TypeDef;


/*! @enum   URT_SBUFBit_TypeDef
    @brief  URT shift buffer status bit select definitions.
*/
typedef enum
{
    URT_SBUF_ADR    =   URT_STA2_ADR_mask_w,          /*!< Shift buffer address bit.*/
    URT_SBUF_PAR    =   URT_STA2_PAR_mask_w           /*!< Shift buffer parity bit.*/
}URT_SBUFBit_TypeDef;


/*! @enum   URT_DEGT_TypeDef
    @brief  URT DE signal output guard time select definitions.
*/
typedef enum
{
    URT_DEGT_1_4  =  URT_CR0_DE_GT_1_4_w,              /*!< DE guard time is 1/4 bit time.*/
    URT_DEGT_1_2  =  URT_CR0_DE_GT_1_2_w,              /*!< DE guard time is 1/2 bit time.*/
    URT_DEGT_1    =  URT_CR0_DE_GT_1_w,                /*!< DE guard time is 1 bit time.*/
    URT_DEGT_2    =  URT_CR0_DE_GT_2_w                 /*!< DE guard time is 2 bit time.*/
}URT_DEGT_TypeDef;


/*! @enum    URT_IDLEMOde_TypeDef
    @brief   URT idle line detect management mode select definitions.
*/
typedef enum
{
    URT_IDLEMode_No   =  URT_CR0_IDL_MDS_no_w,         /*!< No operation.*/
    URT_IDLEMode_Load =  URT_CR0_IDL_MDS_load_w        /*!< Force to load shadow buffer.*/
}URT_IDLEMOde_TypeDef;

///@}


///@{

/*! @enum   URT_CPHA_TypeDef
    @brief  SYNC mode sampling type select definitions.
*/
typedef enum
{
    URT_CPHA0_LeadEdge  =   URT_CR3_CPHA_leading_edge_w ,        /*!< Sampling on leading edge. */
    URT_CPHA1_TrailEdge =   URT_CR3_CPHA_trailing_edge_w         /*!< Sampling on trailing edge. */

}URT_CPHA_TypeDef;

/*! @enum   URT_CPOL_TypeDef
    @brief  SYNC mode clock polarity type select definitions.
*/
typedef enum
{
    URT_CPOL0_Low     = URT_CR3_CPOL_low_w,             /*!< clock is low in idle state. */
    URT_CPOL1_High    = URT_CR3_CPOL_high_w             /*!< clock is high in idle state.*/
}URT_CPOL_TypeDef;


#if defined(URT_CR2_DOUT_MDS_mask_w)
/*! @enum  URT_MOSIIdleStatus_TypeDef
    @brief URT's SPI Master Mode MOSI Stauts control in bus idle.
*/
typedef enum
{
    URT_mSPI_MOSI_Idle_Tristate       =  (URT_CR2_DOUT_MDS_disable_b3| URT_CR2_DOUT_IDL_lbit_b3),         /*!< MOSI IDLE status is tristate in SPI master mode.     */
    URT_mSPI_MOSI_Idle_LastBit        =  (URT_CR2_DOUT_MDS_enable_b3 | URT_CR2_DOUT_IDL_lbit_b3),         /*!< MOSI IDLE status is keeping last status value in SPI master mode. */
    URT_mSPI_MOSI_Idle_Low            =  (URT_CR2_DOUT_MDS_enable_b3 | URT_CR2_DOUT_IDL_0_b3),            /*!< MOSI IDLE status is high in SPI master mode.*/
    URT_mSPI_MOSI_Idle_High           =  (URT_CR2_DOUT_MDS_enable_b3 | URT_CR2_DOUT_IDL_1_b3)             /*!< MOSI IDLE status is low in SPI master mode.*/
}URT_MOSIIdleStatus_TypeDef;
#endif
///@}

///@{
/*! @enum    URT_CALMode_TypeDef
    @brief   URT auto calibration mode select definitions.
*/

typedef enum
{
    URT_CALMode_Start = URT_CAL_CAL_MDS_start_w,         /*!< Measure the start bit.*/
    URT_CALMode_Edge  = URT_CAL_CAL_MDS_edge_w           /*!< Measure start falling edge to next falling edge.*/
}URT_CALMode_TypeDef;


/*! @enum    URT_ExtraBK_TypeDef
    @brief   URT extra break bit select definitions.
*/
typedef enum
{
    URT_ExtraBK_1BIT   =  URT_CR3_DET_BK_1bit_w,           /*!< Extra break bit is 1 bit.*/          
    URT_ExtraBK_3BIT   =  URT_CR3_DET_BK_3bit_w            /*!< Extra break bit is 3 bit.*/
}URT_ExtraBK_TypeDef;
///@}

///@{

/*! @enum   URT_IrDAPulse_TypeDef
    @brief  IrDa output pulse width configuration.
*/
typedef enum
{
	URT_IrDATra_1			=	0,                          /*!< IrDa output pulse width is  1 / URTX_TXOS_NUM. */
	URT_IrDATra_2			=	1,                          /*!< IrDa output pulse width is  2 / URTX_TXOS_NUM. */                 
	URT_IrDATra_3			=	2,                          /*!< IrDa output pulse width is  3 / URTX_TXOS_NUM. */
	URT_IrDATra_4			=	3,                          /*!< IrDa output pulse width is  4 / URTX_TXOS_NUM. */
	URT_IrDATra_5			=	4,                          /*!< IrDa output pulse width is  5 / URTX_TXOS_NUM. */
	URT_IrDATra_6			=	5,                          /*!< IrDa output pulse width is  6 / URTX_TXOS_NUM. */
	URT_IrDATra_7			=	6,                          /*!< IrDa output pulse width is  7 / URTX_TXOS_NUM. */
	URT_IrDATra_8			=	7,                          /*!< IrDa output pulse width is  8 / URTX_TXOS_NUM. */
	URT_IrDATra_9			=	8,                          /*!< IrDa output pulse width is  9 / URTX_TXOS_NUM. */
	URT_IrDATra_10			=	9,                          /*!< IrDa output pulse width is  10 / URTX_TXOS_NUM. */
	URT_IrDATra_11			=	10,                         /*!< IrDa output pulse width is  11 / URTX_TXOS_NUM. */
	URT_IrDATra_12			=	11,                         /*!< IrDa output pulse width is  12 / URTX_TXOS_NUM. */
	URT_IrDATra_13			=	12,                         /*!< IrDa output pulse width is  13 / URTX_TXOS_NUM. */
	URT_IrDATra_14			=	13,                         /*!< IrDa output pulse width is  14 / URTX_TXOS_NUM. */
	URT_IrDATra_15			=	14,                         /*!< IrDa output pulse width is  15 / URTX_TXOS_NUM. */
	URT_IrDATra_16_			=	15                          /*!< IrDa output pulse width is  16 / URTX_TXOS_NUM. */
}URT_IrDAPulse_TypeDef;
///@}


///@{

/*! @enum  URT_RXPERetryMode_TypeDef
    @brief RX parity error retry time select definitions.
*/
typedef enum
{
    URT_RXPERetry_Disable   =  URT_SC_RXE_MDS_disable_w,  /*!< RX no auto retry when detecting parity error.*/   
    URT_RXPERetry_Limited   =  URT_SC_RXE_MDS_enable_w,   /*!< RX limited time auto retry when detecting party error.*/
    URT_RXPERetry_Unlimited =  URT_SC_RXE_MDS_auto_w      /*!< RX alway auto retry unless recceiving parity correct character.*/
}URT_RXPERetryMode_TypeDef;

/*! @enum   URT_RXErrorSignal_TypeDef
    @brief  URT error signal length select definitions.
*/
typedef enum
{
    URT_RXErrorSignal_1BIT = URT_SC_RXE_LEN_1bit_w,      /*!< URT RX parity error detect and NACK transmission 1 bit time length.*/
    URT_RXErrorSignal_2BIT = URT_SC_RXE_LEN_2bit_w       /*!< URT RX parity error detect and NACK transmission 2 bit time length.*/
}URT_RXErrorSignal_TypeDef;


/*! @param  URT_RXPERetryTime_TypeDef
    @brief  URT RX parity error auto retry time select definitions.
*/
typedef enum
{
    URT_RXPERetry_0 =   (0 << URT_SC_RXE_NUM_shift_w),   /*!< No auto retry.*/
    URT_RXPERetry_1 =   (1 << URT_SC_RXE_NUM_shift_w),   /*!< Auto retry 1 time.*/
    URT_RXPERetry_2 =   (2 << URT_SC_RXE_NUM_shift_w),   /*!< Auto retry 2 times.*/
    URT_RXPERetry_3 =   (3 << URT_SC_RXE_NUM_shift_w),   /*!< Auto retry 3 times.*/
    URT_RXPERetry_4 =   (4 << URT_SC_RXE_NUM_shift_w),   /*!< Auto retry 4 times.*/
    URT_RXPERetry_5 =   (5 << URT_SC_RXE_NUM_shift_w),   /*!< Auto retry 5 times.*/
    URT_RXPERetry_6 =   (6 << URT_SC_RXE_NUM_shift_w),   /*!< Auto retry 6 times.*/
    URT_RXPERetry_7 =   (7 << URT_SC_RXE_NUM_shift_w)    /*!< Auto retry 7 times.*/
}URT_RXPERetryTime_TypeDef;


/*! @param  URT_TXErrorReSendTime_TypeDef
    @brief  URT TX auto resend time select definitions.
*/
typedef enum
{
    URT_TXErrorResend_0 = (0 << URT_SC_TXE_NUM_shift_w),  /*!< No auto resend. */
    URT_TXErrorResend_1 = (1 << URT_SC_TXE_NUM_shift_w),  /*!< Auto resend 1 time.*/
    URT_TXErrorResend_2 = (2 << URT_SC_TXE_NUM_shift_w),  /*!< Auto resend 2 times.*/
    URT_TXErrorResend_3 = (3 << URT_SC_TXE_NUM_shift_w),  /*!< Auto resend 3 times.*/
    URT_TXErrorResend_4 = (4 << URT_SC_TXE_NUM_shift_w),  /*!< Auto resend 4 times.*/
    URT_TXErrorResend_5 = (5 << URT_SC_TXE_NUM_shift_w),  /*!< Auto resend 5 times.*/
    URT_TXErrorResend_6 = (6 << URT_SC_TXE_NUM_shift_w),  /*!< Auto resend 6 times.*/
    URT_TXErrorResend_7 = (7 << URT_SC_TXE_NUM_shift_w)   /*!< Auto resend 7 times.*/
}URT_TXErrorReSendTime_TypeDef;


/*! @enum  URT_TXErrorMode_TypeDef
    @brief URT TX error detect mode select definitions.
*/
typedef enum
{ 
    URT_TXErrorDetect_Disable       = URT_SC_TXE_MDS_disable_w,  /*!< TX error detect disable */
    URT_TXErrorDetect_ErrorSignal   = URT_SC_TXE_MDS_chk_low_w,  /*!< TX error detect mode is that check low in stop bit.*/
    URT_TXErrorDetect_TX            = URT_SC_TXE_MDS_chk_tx_w    /*!< TX error detect mode is that TX detect*/
}URT_TXErrorMode_TypeDef;
///@}


#if defined(URT_CLK_ECK_CKS_mask_w)
/*! @enum  URT_ExternalClockMux_TypeDef
    @brief URT external clock input pin select definitions.
*/
typedef enum
{
    URT_ExternalClockInput_CLK      = URT_CLK_ECK_CKS_clk_w,
    URT_ExternalClockInput_RX       = URT_CLK_ECK_CKS_rx_w
}URT_ExternalClockMux_TypeDef;
#endif


/*! @struct URT_Data_TypeDef
    @brief  URT data character configuration.
*/ 
typedef struct
{
    URT_DataLength_TypeDef  URT_TX_DataLength;  /*!< URT TX data length select. */ 
    URT_DataLength_TypeDef  URT_RX_DataLength;	/*!< URT RX data length select. */
    URT_DataOrder_TypeDef   URT_TX_DataOrder;   /*!< URT TX data order select. */
    URT_DataOrder_TypeDef   URT_RX_DataOrder;   /*!< URT RX data order select. */
    URT_STOP_TypeDef        URT_TX_StopBits;    /*!< URT TX stop bit select. */
    URT_STOP_TypeDef        URT_RX_StopBits;	/*!< URT RX stop bit select. */
    URT_Parity_TypeDef      URT_TX_Parity;      /*!< URT TX parity mode select. */
    URT_Parity_TypeDef      URT_RX_Parity;      /*!< URT RX parity mode select. */
    FunctionalState         URT_TX_DataInverse; /*!< URT TX Data inverse enable or disable*/
    FunctionalState         URT_RX_DataInverse; /*!< URT RX Data inverse enable or disable*/
}URT_Data_TypeDef;


/*! @struct URT_BRG_TypeDef
    @brief  URT baudrate generator configuration.
*/ 
typedef struct __attribute__((packed))
{
	URT_BDClock_TypeDef		       URT_InternalClockSource;        /*!< Baud rate generator clock source select. */
	URT_BDMode_TypeDef	           URT_BaudRateMode;               /*!< Baud rate generator counter mode select. */
	uint8_t				  	       URT_PrescalerCounterReload;     /*!< Prescaler counter reload value. */
	uint8_t				  	       URT_BaudRateCounterReload;      /*!< Baud rate counter reload value. */
}URT_BRG_TypeDef;


/*! @struct URT_IrDA_TypeDef
    @brief  URT IrDa mode configuration.
*/ 
typedef struct
{
    URT_IrDAPulse_TypeDef        URT_IrDaPulseWidth;         /*!< IrDa output pulse select. */
}URT_IrDA_TypeDef;


/*! @struct URT_RXParityError_TypeDef
    @brief  URT RX parity error relationship configuration.
*/
typedef struct
{
    URT_RXPERetryMode_TypeDef    URT_RXPERetryMode;         /*!< RX parity error auto retry mode select. */
    URT_RXErrorSignal_TypeDef    URT_RXErrorSignal;         /*!< RX error signal length select.*/
    URT_RXPERetryTime_TypeDef    URT_RXPERetryTime;         /*!< RX auto retry time select when auto retry mode is limited time auto retry.*/
}URT_RXParityError_TypeDef;


#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

///@{
void URT_IT_Config( URT_Struct*  , uint32_t , FunctionalState );
void URT_ITEA_Cmd( URT_Struct*  , FunctionalState );
uint32_t URT_GetITAllFlagStatus( URT_Struct* );
DRV_Return URT_GetITSingleFlagStatus( URT_Struct*  , uint32_t );
void URT_ClearITFlag( URT_Struct*  , uint32_t );
DRV_Return URT_GetRxDifferentFlag( URT_Struct* );
DRV_Return URT_GetRxHoldFlag( URT_Struct* );
void URT_ClearRxHoldFlag( URT_Struct* );
DRV_Return URT_GetIrDaBusyFlag( URT_Struct* );
DRV_Return URT_GetBreakBusyFlag( URT_Struct* );
DRV_Return URT_GetRxBusyFlag( URT_Struct* );
DRV_Return URT_GetRxNoiseFlag( URT_Struct* );
uint32_t URT_GetITStatus(URT_Struct* URTX);
///@}


///@{
void URT_DataCharacter_Config( URT_Struct* , URT_Data_TypeDef* );
void URT_Mode_Select( URT_Struct*  , URT_Mode_TypeDef );
void URT_DataLine_Select( URT_Struct* , URT_DataLine_TypeDef );
void URT_HalfDuplexMode_Cmd( URT_Struct* , FunctionalState );
void URT_LoopBackMode_Cmd( URT_Struct*  , FunctionalState );
void URT_TX_Cmd( URT_Struct*  , FunctionalState );
void URT_RX_Cmd( URT_Struct*  , FunctionalState );
void URT_RXInverse_Cmd(URT_Struct*  , FunctionalState );
void URT_TXInverse_Cmd( URT_Struct*  , FunctionalState );
void URT_NoiseDataSkip_Cmd(URT_Struct* , FunctionalState );
void URT_Cmd( URT_Struct*  , FunctionalState );
///@}



///@{
void URT_BaudRateGenerator_Config( URT_Struct*  , URT_BRG_TypeDef* );
void URT_BaudRateGeneratorMode_Select( URT_Struct*  , URT_BDMode_TypeDef );
void URT_BaudRateGeneratorClock_Select( URT_Struct*  , URT_BDClock_TypeDef );

#if defined(URT_CLK_BR_CKS_mask_w)
void URT_BaudRateCounterClockSource_Select( URT_Struct* , URT_BRCounterClock_TypeDef );
#endif

uint8_t URT_GetBaudRateGeneratorPreReload( URT_Struct* );
uint8_t URT_GetBaudRateGeneratorCountReload( URT_Struct* );
uint8_t URT_GetBaudRateGeneratorPre( URT_Struct* );
uint8_t URT_GetBaudRateGeneratorCount( URT_Struct* );

void URT_BaudRateGenerator_Cmd( URT_Struct*  , FunctionalState );
void URT_CLKSignalSource_Select( URT_Struct*  , URT_CLKSource_TypeDef );
void URT_CLKSignal_Cmd( URT_Struct*  , FunctionalState );
void URT_CtrlBROSignalStatus_SW( URT_Struct*  , BitAction );
void URT_CtrlCLKSignalStatus_SW( URT_Struct*  , BitAction );
void URT_TXClockSource_Select( URT_Struct*  , URT_TXClock_TypeDef );
void URT_RXClockSource_Select( URT_Struct*  , URT_RXClock_TypeDef );
DRV_Return URT_TXOverSamplingSampleNumber_Select( URT_Struct*  , uint8_t );
DRV_Return URT_RXOverSamplingSampleNumber_Select( URT_Struct*  , uint8_t );
void URT_RXOverSamplingMode_Select( URT_Struct*  , URT_RXSMP_TypeDef );

///@}


///@{
void URT_TimeroutTimer_Cmd( URT_Struct*  , FunctionalState );
void URT_TriggerTimeoutTimerRst_SW( URT_Struct*  );
void URT_TimeoutMode_Select( URT_Struct*  , URT_TMOMDS_TypeDef );
void URT_TimeoutTimerClockSource_Select( URT_Struct*  , URT_TMOCLK_TypeDef );
void URT_IdleDetect_Select( URT_Struct*  , uint8_t );
void URT_IdleTimeoutDetect_Config( URT_Struct*  , FunctionalState  , uint16_t );
void URT_RXTimeoutDetect_Config( URT_Struct*  , FunctionalState  , uint8_t );
DRV_Return URT_BreakTimeoutDetect_Config( URT_Struct*  , FunctionalState  , uint8_t );
DRV_Return URT_CalibrationTimeoutDetect_Config( URT_Struct*  , FunctionalState  , uint8_t );
void URT_CtrlTMOSignalStatus_SW( URT_Struct*  , BitAction );
uint16_t URT_GetTimeoutTimerCounter( URT_Struct* );
void URT_SetTimeoutTimerCounter( URT_Struct* , uint16_t );
uint16_t URT_GetTimeoutTimerReload( URT_Struct* );
void URT_SetTimeoutTimerCompare( URT_Struct* , uint16_t);
///@}


///@{
uint8_t URT_GetTXShadowBufferLevel( URT_Struct* );
uint8_t URT_GetRXShadowBufferLevel( URT_Struct* );
void URT_ClearTXData( URT_Struct* );
void URT_ClearRXData( URT_Struct* );
uint8_t URT_GetTXDataRegLevel( URT_Struct* );
void URT_RXShadowBufferThreshold_Select( URT_Struct*  , URT_RXTH_TypeDef );
uint8_t URT_GetRXDataRegLevel( URT_Struct* );
uint32_t URT_GetRXData( URT_Struct* );
uint8_t URT_GetCaptureData( URT_Struct* );
uint8_t URT_GetCaptureStatusBit( URT_Struct*  , URT_RCAP_TypeDef );
uint8_t URT_GetRXShiftBufferStatusBit( URT_Struct*  , URT_SBUFBit_TypeDef );
uint8_t URT_GetTXShiftBufferData( URT_Struct* );
uint8_t URT_GetRXShiftBufferData( URT_Struct* );
void URT_RTS_Cmd( URT_Struct* , FunctionalState  );
void URT_RTSInverse_Cmd( URT_Struct* URTX, FunctionalState URT_RTS_INV);
void URT_CtrlRTS_SW( URT_Struct*  , BitAction );
void URT_CTS_Cmd( URT_Struct* , FunctionalState);
DRV_Return URT_GetCTSLineStatus( URT_Struct* );
void URT_CTSInverse_Cmd( URT_Struct*  , FunctionalState );
void URT_DE_Cmd( URT_Struct*  , FunctionalState );
void URT_DEInverse_Cmd( URT_Struct*  , FunctionalState );
void URT_DEGuardTime_Select( URT_Struct*  , URT_DEGT_TypeDef );
void URT_IdlehandleMode_Select( URT_Struct*  , URT_IDLEMOde_TypeDef );
void URT_TXHalt_Cmd(URT_Struct*  , FunctionalState );
void URT_TXGuardTime_Select( URT_Struct*  , uint8_t );
DRV_Return URT_SetTXData( URT_Struct*  , uint8_t  , uint32_t );
///@}



///@{
void URT_CPHAMode_Select( URT_Struct*  , URT_CPHA_TypeDef );
void URT_CPOLMode_Select( URT_Struct* , URT_CPOL_TypeDef );

#if defined(URT_CR0_SYNC_MDS_mask_w)
    void URT_SYNCMode_Select( URT_Struct* URTX , URT_SYNCMode_TypeDef URT_SYNC_MDS);
#endif

#if defined(URT_CR2_NSSI_EN_mask_w)
    void URT_NssInput_Cmd( URT_Struct* , FunctionalState);
#endif
#if defined(URT_CR2_DOUT_MDS_mask_w)
    void URT_SPIMasterDataOutputIdleStatus_Select( URT_Struct* , URT_MOSIIdleStatus_TypeDef);
#endif
void URT_NssInverse_Cmd( URT_Struct*  , FunctionalState );
void URT_NssSW_Cmd( URT_Struct*  , FunctionalState );
void URT_CtrlNSS_SW( URT_Struct*  , BitAction );
///@}



///@{
void URT_SetSlaveAddressMask( URT_Struct*  , uint8_t );
void URT_SetSlaveAddress( URT_Struct*  , uint8_t );
void URT_GlobalAddress_Cmd( URT_Struct*  , FunctionalState );
void URT_SendAddress( URT_Struct*  , uint8_t );
///@}



///@{
void URT_CalibrationMode_Select( URT_Struct*  , URT_CALMode_TypeDef );
void URT_AutoCalibration_Cmd( URT_Struct*  , FunctionalState );
void URT_Calibration_SW( URT_Struct*  , FunctionalState );
void URT_CalibrationCompleteDataHold_Cmd( URT_Struct*  , FunctionalState );
void URT_ExtraBreakBit_Select( URT_Struct*  , URT_ExtraBK_TypeDef );
void URT_SendBreak( URT_Struct* );

#if defined(URT_STA_CALOVF_mask_w) && defined(URT_STA_CALUDF_mask_w)
    DRV_Return URT_GetCalibrationResult(URT_Struct*);
#endif

///@}


///@{
void URT_TXDMA_Cmd( URT_Struct* , FunctionalState );
void URT_RXDMA_Cmd( URT_Struct*  , FunctionalState );
void URT_BreakDisableDMA_Cmd( URT_Struct*  , FunctionalState );
///@}


///@{
void URT_IrDA_Config( URT_Struct*  , URT_IrDA_TypeDef* );
void URT_IrDA_Cmd( URT_Struct*  , FunctionalState );
///@}



///@{
void URT_AutoExitMuteMode_Select( URT_Struct* , uint8_t );
void URT_AutoEnterMuteMode_Select( URT_Struct* , uint8_t );
void URT_Mute_Cmd( URT_Struct*  , FunctionalState );
///@}


///@{
void URT_NoiseCapture_Cmd( URT_Struct*  , FunctionalState );
void URT_NoiseHoldData_Cmd( URT_Struct*  , FunctionalState );
void URT_RXParityError_Config( URT_Struct*  , URT_RXParityError_TypeDef*  );
void URT_TXErrorDetectMode_Select( URT_Struct*  , URT_TXErrorMode_TypeDef );
void URT_TXErrorResendTime_Select( URT_Struct*  , URT_TXErrorReSendTime_TypeDef );

///@}


///@{
void URT_RxTxSwap_Cmd(URT_Struct*, FunctionalState);
#if defined(URT_CLK_ECK_CKS_mask_w)
    void URT_ExternalClockMux_Select(URT_Struct*,  URT_ExternalClockMux_TypeDef);
#endif
///@}


#ifdef __cplusplus
}
#endif // __cplusplus


#endif


