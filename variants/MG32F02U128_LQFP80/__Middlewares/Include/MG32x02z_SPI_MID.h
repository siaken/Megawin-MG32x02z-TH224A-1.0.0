/**
 ******************************************************************************
 *
 * @file        MG32x02z_SPI_MID.h
 *
 * @brief       This is the C code format middleware head file for SPI module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.07
 * @date        2022/07/04
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2020 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************
 * @par         Disclaimer 
 * The Demo software is provided "AS IS" without any warranty, either 
 * expressed or implied, including, but not limited to, the implied warranties 
 * of merchantability and fitness for a particular purpose. The author will 
 * not be liable for any special, incidental, consequential or indirect 
 * damages due to loss of data or any other reason. 
 * These statements agree with the world wide and local dictated laws about 
 * authorship and violence against these laws. 
 ******************************************************************************
 ******************************************************************************
 */ 
#include "MG32x02z_Common_MID.h"
#include "MG32x02z_SPI.h"
#include "MG32x02z_URT.h"
#include "MG32x02z_GPL.h"
#include "MG32x02z_GPIO.h"
#include "MG32x02z__ExtraStruct.h"
#include "MG32x02z_DMA_MID.h"


#ifndef _MG32x02z_SPI_MID_H
/*!< _MG32x02z_SPI_MID_H */ 
#define _MG32x02z_SPI_MID_H

#ifdef __cplusplus
extern "C" {
#endif

/*! @struct MID_SPI_Struct
    @brief  MID SPI & SPI mode of URT common use register struct
*/ 
typedef struct
{
    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
    }STA;

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
    }INT;

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
    }CLK;                              

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
    }STA2;                           // Here New .......
    
    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
    }CR0;                              

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
    }CR1;                               

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];

    }CR2;                              

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];

    }CR3;                              // Here New .......
    
    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];

    }CR4;                              // Here New .......
    
    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];

    }RLR;                              // Here New .......
    
    __I uint32_t  RESERVED1[2];        // Here change .....

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];

    }RDAT;                              

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];

    }TDAT;                              

    union
    {
        __IO  uint32_t  W;
        __IO  uint16_t  H[2];
        __IO  uint8_t   B[4];
    }TDAT3;                             

}MID_SPI_Struct;



#define SPI0_Base                       ((uint32_t)0x53000000)              /*!< SPI Control Module-0   */
#define SPI_SPI0                        ((MID_SPI_Struct*) SPI0_Base)       /*!< SPI0 module            */ 
#define SPI_URT0                        ((MID_SPI_Struct*) URT0_Base)       /*!< URT0 module            */ 
#define SPI_URT1                        ((MID_SPI_Struct*) URT1_Base)       /*!< URT1 module            */
#if defined(URT2_Base)
#define SPI_URT2                        ((MID_SPI_Struct*) URT2_Base)       /*!< URT0 module            */ 
#endif
#if defined(URT3_Base)
#define SPI_URT3                        ((MID_SPI_Struct*) URT3_Base)       /*!< URT1 module            */  
#endif

#define MID_SPI_MASK                    0xFF000000                          /*!< SPIx module mask       */
#define MID_SPI_URT                     0x52000000                          /*!< URTx module address    */
#define MID_SPI_SPI                     0x53000000                          /*!< SPIx module address    */
#define MID_SPI_INDEX_MASK              0x000F0000                          /*!< SPIx module mask       */

#define MID_SPI_INDEX_URT0              0x00000000                          /*!< URT index0 if REG_TYPE = URT TYPE*/
#define MID_SPI_INDEX_URT1              0x00010000                          /*!< URT index1 if REG_TYPE = URT TYPE*/
#define MID_SPI_INDEX_URT2              0x00020000                          /*!< URT index2 if REG_TYPE = URT TYPE*/
#define MID_SPI_INDEX_URT3              0x00030000                          /*!< URT index3 if REG_TYPE = URT TYPE*/

/** 
 * @enum    MID_SPI_StateTypeDef
 * @brief   MID SPI State structure definition
 */  
typedef enum
{
    MID_SPI_STATE_RESET      = 0x00U,   /*!< Peripheral not Initialized                          */
    MID_SPI_STATE_READY      = 0x01U,   /*!< Peripheral Initialized and ready for use            */
    MID_SPI_STATE_BUSY       = 0x02U,   /*!< an internal process is ongoing                      */
    MID_SPI_STATE_BUSY_TX    = 0x03U,   /*!< Data Transmission process is ongoing                */
    MID_SPI_STATE_BUSY_RX    = 0x04U,   /*!< Data Reception process is ongoing                   */
    MID_SPI_STATE_BUSY_TX_RX = 0x05U,   /*!< Data Transmission and Reception process is ongoing  */
    MID_SPI_STATE_ERROR      = 0x06U,   /*!< SPI error state                                     */
    MID_SPI_STATE_ABORT      = 0x07U    /*!< SPI abort is ongoing                                */
}MID_SPI_StateTypeDef;


/*! @struct SPI_InitTypeDef
    @brief  SPI initialization struct
*/ 
typedef struct __attribute__((packed))
{
    uint32_t Mode;              /*!< SPIx_MDS, SPIx_NSSO_EN and SPIx_NSSI_EN.
                                     This parameter can be a value of reference SPI_Mode */

    uint32_t DataLine;          /*!< SPI data line number select. 
                                     This parameter can be a value of reference SPI_DataLine */
    
    uint32_t DataSize;          /*!< SPI transfer data frame bit size from 4-bit to 32-bit. 
                                     This parameter can be a value of reference SPI_Data_Size */

    uint32_t CLKPolarity;       /*!< SPI clock polarity select.
                                     This parameter can be a value of reference SPI_Clock_Polarity */  

    uint32_t CLKPhase;          /*!< SPI clock phase select. 
                                     This parameter can be a value of reference SPI_Clock_Phase */
    
    uint32_t NSS;               /*!< SPI NSS and NSSI pin hardware/software control.
                                     This parameter can be a value of reference  SPI_NSS_NSSI_Control */
                                     
    uint32_t ClockDivider;      /*!< SPI clock devider 2^N.
                                     This parameter can be a value of reference SPI_Clock_Divider */

    uint32_t FirstBit;          /*!< SPI data order MSB/LSB. 
                                     This parameter can be a value of reference SPI_MSB_LSB_transmission */
    
    uint32_t NSSPMode;          /*!< SPI single master mode NSS pulse none/1T/2T. 
                                     This parameter can be a value of reference SPI_NSSP_Mode */

    uint32_t Swap;              /*!< SPI I/O SPI_MOSI,SPI_MISO signals swap.
                                     This Parameter can be a value of reference SPI_SWAP */

    uint32_t IdleDataOut;       /*!< SPI idle data output mode and state control. 
                                     This Parameter can be a value of reference SPI_IdleDataOutControl */

    uint32_t SlaveClockInputControl;        /*!< SPI standard slave mode clock input asynchronous function control.
                                                 This Parameter can be a value of reference SPI_SLV_CLK_CTL */
    
    uint32_t SlaveTransmitTimingControl;    /*!< SPI slave mode data transmit timing control. 
                                                 This Parameter can be a value of reference SPI_SLV_TX_CTL */


}SPI_InitTypeDef;


/*! @struct SPI_HandleTypeDef
    @brief  SPI handle Structure definition
*/ 
typedef struct __attribute__((packed)) tag_SPI_HandleTypeDef
{
    MID_SPI_Struct           *Instance;       /*!< SPIx/USPIx registers base address        */

    SPI_InitTypeDef           Init;           /*!< SPIx/URTx communication parameters       */

    uint32_t                  REG_TYPE;       /*!< SPIx/URTx module start address           */
    
    union  __attribute__((packed))  
    {
        __IO  uint32_t* point32;
        __IO  uint16_t* point16;
        __IO  uint8_t*  point8;
    }pTxBuffPtr;                              /*!< Pointer to SPI Tx transfer Buffer        */
    
    uint32_t                  TxXferSize;     /*!< SPIx/URTx Tx Transfer size               */

    __IO uint32_t             TxXferCount;    /*!< SPIx/URTx Tx Transfer Counter            */

    union __attribute__((packed))  
    {
        __IO  uint32_t* point32;
        __IO  uint16_t* point16;
        __IO  uint8_t*  point8;
    }pRxBuffPtr; 
    
    uint32_t                  RxXferSize;     /*!< SPIx/URTx Rx Transfer size               */
    
    __IO uint32_t             RxXferCount;    /*!< SPIx/URTx Rx Transfer Counter            */

    uint32_t                  CRCSize;        /*!< SPIx/URTx CRC size used for the transfer */ 

    void (*RxISR)(struct tag_SPI_HandleTypeDef *mSPI);  /*!< function pointer on Rx ISR     */    

    void (*TxISR)(struct tag_SPI_HandleTypeDef *mSPI);  /*!< function pointer on Tx ISR     */    

    DMA_HandleTypeDef         *mDMATX;        /*!< SPIxUSPIx Tx DMA Handle parameters       */

    DMA_HandleTypeDef         *mDMARX;        /*!< SPI/URTx Rx DMA Handle parameters        */
  
    uint8_t                   SPI_IRQ;        /*!< SPI/URTx IRQ index                       */
    uint32_t                  SPI_FLAG_TUDRF; /*!< SPI/URTx TUDRF flag                      */
    uint32_t                  SPI_FLAG_ROVRF; /*!< SPI/URTx ROVRF flag                      */
    uint32_t                  SPI_FLAG_ERROR; /*!< SPI/URTx ERROR flag                      */
    uint32_t                  SPI_FLAG_IDLF;  /*!< SPI/URTx IDLE flag                       */
    uint32_t                  SPI_FLAG_TCF;   /*!< SPI/URTx TCF flag                        */
    uint8_t      __IO         *RX_TH;         /*!< SPI/URTx RX buffer threshold             */
    uint8_t      __IO         *RXTX_LVL;      /*!< SPI/URTx RX and TX buffer level          */
    uint8_t      __IO         *RXTX_CLR;      /*!< SPI/URTx RX and TX buffer clear          */
    uint8_t      __IO         *RNUM;          /*!< SPI/URTx RNUM receive number             */

    MID_LockTypeDef           Lock;           /*!< Locking object                           */

    __IO MID_SPI_StateTypeDef State;          /*!< SPI/URTx communication state             */

    __IO uint32_t             ErrorCode;      /*!< SPI/URTx Error code                      */
  
    uint8_t                   TxRxStartEvent; /*!< SPI/URTx confirm 1st transmit/receve event   */

}SPI_HandleTypeDef;



/*! @struct PointStruct
    @brief  Point Structure definition
*/ 
typedef struct
{
    union  
    {
        __IO  uint32_t* point32;
        __IO  uint16_t* point16;
        __IO  uint8_t*  point8;
    }ptr;
} PointStruct;


/**
 * @name SPI_Error_Code 
 *      SPI Error Code
 */ 
//!@{
#define MID_SPI_ERROR_NONE              (0x00000000U)   /*!< No error                               */
#define MID_SPI_ERROR_MOD               (0x00000001U)   /*!< MODF error                             */
#define MID_SPI_ERROR_CRC               (0x00000002U)   /*!< CRC error                              */
#define MID_SPI_ERROR_OVR               (0x00000004U)   /*!< ROVRF error                            */
#define MID_SPI_ERROR_WE                (0x00000008U)   /*!< WEF error                              */
#define MID_SPI_ERROR_DMA               (0x00000010U)   /*!< DMA transfer error                     */
#define MID_SPI_ERROR_FLAG              (0x00000020U)   /*!< Error on RXNE/TXE/BSY/FTLVL/FRLVL Flag */
#define MID_SPI_ERROR_ABORT             (0x00000040U)   /*!< Error during SPI Abort procedure       */
#define MID_SPI_ERROR_URD               (0x00000080U)   /*!< TUDRF error                            */
//!@}


/**
 * @name SPI_Mode
 *      SPI mode
 */
//!@{ 
#define SPI_MODE_MASTER                 0x10    /*!< SPIx/URTx master without NSS output                                        */
#define SPI_MODE_MASTER_NSS             0x11    /*!< SPIx/URTx master with NSS output                                           */
#define SPI_MODE_SLAVE_NSS              0x02    /*!< SPIx/URTx slave with NSS input from SPIx_NSS pin                           */
#define SPI_MODE_MASTER_MODF_AT_NSS     0x13    /*!< SPIx slave with NSS input from SPIx_NSS pin                                */
#define SPI_MODE_MASTER_MODF_AT_NSSI    0x14    /*!< SPIx master without NSS output and with MODF function using SPIx_NSS pin   */
#define SPI_MODE_MASTER_NSS_MODF        0x15    /*!< SPIx master without NSS output and with MODF function using SPIx_NSSI pin  */
#define SPI_MODE_SLAVE                  0x06    /*!< SPIx slave without NSS input                                               */
#define SPI_MODE_SLAVE_NSSI             0x07    /*!< SPIx slave with NSS input from SPIx_NSSI pin                               */
#define SPI_MDS_MASK                    0x10    /*!< SPIx/URTx mode check mask                                                  */
//!@}

                         
/**
 * @name SPI_Mode for URTx
 *      SPI Mode for URTx 
 */
//!@{ 
#if defined(MG32_3RD) || defined(MG32_4TH)
    #define uSPI_MODE_MASK             (URT_CR0_DE_GT_mask_h0 | URT_CR0_DE_INV_mask_h0 | URT_CR0_DE_EN_mask_h0 | URT_CR0_TX_INV_mask_h0 | \
                                        URT_CR0_RX_INV_mask_h0 | URT_CR0_GSA_EN_mask_h0 | URT_CR0_MDS_mask_h0 | URT_CR0_DAT_LINE_mask_h0 | \
                                        URT_CR0_HDX_EN_mask_h0 | URT_CR0_OS_MDS_mask_h0 | URT_CR0_SYNC_MDS_mask_h0)                             /*!< URTx mode mask */
    #define uSPI_MODE_MASTER_NSS       (URT_CR0_MDS_sync_h0 | URT_CR0_SYNC_MDS_master_h0)                                                       /*!< URTx master with NSS */
    #define uSPI_MODE_SLAVE_NSS        (URT_CR0_MDS_sync_h0 | URT_CR0_SYNC_MDS_slave_h0)                                                        /*!< URTx slave with NSS */
#endif
#if defined(MG32_1ST) || defined(MG32_2ND)
    #define uSPI_MODE_MASK             (URT_CR0_DE_GT_mask_h0 | URT_CR0_DE_INV_mask_h0 | URT_CR0_DE_EN_mask_h0 | URT_CR0_TX_INV_mask_h0 | \
                                        URT_CR0_RX_INV_mask_h0 | URT_CR0_GSA_EN_mask_h0 | URT_CR0_MDS_mask_h0 | URT_CR0_DAT_LINE_mask_h0 | \
                                        URT_CR0_HDX_EN_mask_h0 | URT_CR0_OS_MDS_mask_h0)                                                        /*!< URTx mode mask */
    #define uSPI_MODE_MASTER_NSS        URT_CR0_MDS_sync_h0                                                                                     /*!< URTx master with NSS */
#endif
//!@}


/**
 * @name SPI_DataLine 
 *      SPI Direction Mode
 */
//!@{ 
#define SPI_STANDARD_SPI                0x00000000  /*!< SPI_DIRECTION_2LINES                                           */
#define SPI_1LINE                       0x00000001  /*!< 1-line bidirectional~ SPI0_MOSI                                */
#define SPI_2LINES                      0x00000002  /*!< 2-lines bidirectional~ SPI0_D0(MOSI), SPI0_D1(MISO)            */
#define SPI_4LINES                      0x00000003  /*!< 4-lines bidirectional~ SPI0_D0 ~ SPI0_D3                       */
#define SPI_4LINES_DUPLICATE            0x00000004  /*!< 8-lines TX~ SPI0_D0 ~ SPI0_D3 with duplicate SPI0_D4 ~ SPI0_D7 */
#define SPI_8LINES                      0x00000005  /*!< 8-lines bidirectional~ SPI0_D0 ~ SPI0_D7                       */
//!@}


/**
 * @name SPI_Direction 
 *      SPI Direction Select
 */
//!@{ 
#define SPI_XLINES_BDIR_OUT             SPI_CR2_BDIR_OE_disable_w   /*!< Transfer bidirectional output  */
#define SPI_XLINES_BDIR_IN              SPI_CR2_BDIR_OE_enable_w    /*!< Transfer bidirectional input   */
//!@}


/**
 * @name SPI_Data_Size 
 *      SPI Data Size
 */
//!@{
#define SPI_DATASIZE_4BIT               (0x00000004U)   /*!< Data size 4 bit    */
#define SPI_DATASIZE_5BIT               (0x00000005U)   /*!< Data size 5 bit    */
#define SPI_DATASIZE_6BIT               (0x00000006U)   /*!< Data size 6 bit    */
#define SPI_DATASIZE_7BIT               (0x00000007U)   /*!< Data size 7 bit    */
#define SPI_DATASIZE_8BIT               (0x00000008U)   /*!< Data size 8 bit    */
#define SPI_DATASIZE_9BIT               (0x00000009U)   /*!< Data size 9 bit    */
#define SPI_DATASIZE_10BIT              (0x0000000AU)   /*!< Data size 10 bit   */
#define SPI_DATASIZE_11BIT              (0x0000000BU)   /*!< Data size 11 bit   */
#define SPI_DATASIZE_12BIT              (0x0000000CU)   /*!< Data size 12 bit   */
#define SPI_DATASIZE_13BIT              (0x0000000DU)   /*!< Data size 13 bit   */
#define SPI_DATASIZE_14BIT              (0x0000000EU)   /*!< Data size 14 bit   */
#define SPI_DATASIZE_15BIT              (0x0000000FU)   /*!< Data size 15 bit   */
#define SPI_DATASIZE_16BIT              (0x00000010U)   /*!< Data size 16 bit   */
#define SPI_DATASIZE_17BIT              (0x00000011U)   /*!< Data size 17 bit   */
#define SPI_DATASIZE_18BIT              (0x00000012U)   /*!< Data size 18 bit   */
#define SPI_DATASIZE_19BIT              (0x00000013U)   /*!< Data size 19 bit   */
#define SPI_DATASIZE_20BIT              (0x00000014U)   /*!< Data size 20 bit   */
#define SPI_DATASIZE_21BIT              (0x00000015U)   /*!< Data size 21 bit   */
#define SPI_DATASIZE_22BIT              (0x00000016U)   /*!< Data size 22 bit   */
#define SPI_DATASIZE_23BIT              (0x00000017U)   /*!< Data size 23 bit   */
#define SPI_DATASIZE_24BIT              (0x00000018U)   /*!< Data size 24 bit   */
#define SPI_DATASIZE_25BIT              (0x00000019U)   /*!< Data size 25 bit   */
#define SPI_DATASIZE_26BIT              (0x0000001AU)   /*!< Data size 26 bit   */
#define SPI_DATASIZE_27BIT              (0x0000001BU)   /*!< Data size 27 bit   */
#define SPI_DATASIZE_28BIT              (0x0000001CU)   /*!< Data size 28 bit   */
#define SPI_DATASIZE_29BIT              (0x0000001DU)   /*!< Data size 29 bit   */
#define SPI_DATASIZE_30BIT              (0x0000001EU)   /*!< Data size 30 bit   */
#define SPI_DATASIZE_31BIT              (0x0000001FU)   /*!< Data size 31 bit   */
#define SPI_DATASIZE_32BIT              (0x00000020U)   /*!< Data size 32 bit   */
//!@}


/**
 * @name SPI_Clock_Polarity 
 *      SPI Clock Polarity
 */
//!@{
#define SPI_POLARITY_LOW                (0x00000000)    /*!< SPIx/URTx idle clock low   */
#define SPI_POLARITY_HIGH               (0x00000002)    /*!< SPIx/URTx idle clock high  */
//!@}


/**
 * @name SPI_Clock_Phase 
 *      SPI Clock Phase
 */
//!@{ 
#define SPI_PHASE_1EDGE                 (0x00000000)    /*!< SPIx/URTx leading edge get data   */
#define SPI_PHASE_2EDGE                 (0x00000004)    /*!< SPIx/URTx trailing edae get data  */
//!@}


/**
 * @name SPI_NSS_NSSI_Control 
 *      SPI NSS NSSI pin HW/SW control
 */
//!@{
#define SPI_NSS_HARDWARE                (0x00000000)    /*!< NSS output by HW       */
#define SPI_NSS_SOFTWARE                (0x00000001)    /*!< NSS output by SW & HW  */
#define SPI_NSSI_HARDWARE               (0x00000000)    /*!< NSSI output by HW      */
#define SPI_NSSI_SOFTWARE               (0x00000002)    /*!< NSSI input by SW       */
//!@}


/**
 * @name SPI_NSSP_Mode 
 *      SPI NSS Pulse Mode
 */
//!@{
#define SPI_NSS_PULSE_DISABLE           (0x00000000)    /*!< Disable NSS output pulse       */
#define SPI_NSS_PULSE_1T                (0x00000001)    /*!< NSS output pulse 1 SPI clock   */
#define SPI_NSS_PULSE_2T                (0x00000003)    /*!< NSS output pulse 2 SPI clock   */
//!@}


/**
 * @name SPI_SWAP
 *      SPI swap MOSI and MISO
 */
//!@{
#define SPI_SWAP_DISABLE                (0x00000000)    /*!< SPI I/O SPI_MOSI,SPI_MISO signals swap disable */
#define SPI_SWAP_ENABLE                 (0x00000080)    /*!< SPI I/O SPI_MOSI,SPI_MISO signals swap         */
//!@}


/**
 * @name SPI_IdleDataOutControl
 *      SPI swap MOSI and MISO
 */
//!@{
#define SPI_IDLE_DATA_OUT_TRISTATE          (0x00000000)    /*!< SPI output mode tristate                           */
#define SPI_IDLE_DATA_OUT_DRIVING_LASTBIT   (0x00020000)    /*!< SPI output mode driving, data output list data bit */
#define SPI_IDLE_DATA_OUT_DRIVING_0         (0x000A0000)    /*!< SPI output mode driving, data output 0             */
#define SPI_IDLE_DATA_OUT_DRIVING_1         (0x000E0000)    /*!< SPI output mode driving, data output 1             */
//!@}


/**
 * @name SPI_Clock_Divider
 *      SPI Clock divier
 */
//!@{
#define SPI_CLOCKDIVIDER_2              (0x00000000)    /*!< (CK_SPIx_PR/CK_URTx) /2    */
#define SPI_CLOCKDIVIDER_4              (0x00000001)    /*!< (CK_SPIx_PR/CK_URTx) /4    */
#define SPI_CLOCKDIVIDER_8              (0x00000002)    /*!< (CK_SPIx_PR/CK_URTx) /8    */
#define SPI_CLOCKDIVIDER_16             (0x00000003)    /*!< (CK_SPIx_PR/CK_URTx) /16   */
#define SPI_CLOCKDIVIDER_32             (0x00000004)    /*!< (CK_SPIx_PR/CK_URTx) /32   */
#define SPI_CLOCKDIVIDER_64             (0x00000005)    /*!< (CK_SPIx_PR/CK_URTx) /62   */
#define SPI_CLOCKDIVIDER_128            (0x00000006)    /*!< (CK_SPIx_PR/CK_URTx) /128  */
#define SPI_CLOCKDIVIDER_256            (0x00000007)    /*!< (CK_SPIx_PR/CK_URTx) /256  */
#define SPI_CLOCKDIVIDER_512            (0x00000008)    /*!< (CK_SPIx_PR/CK_URTx) /512  */
#define SPI_CLOCKDIVIDER_1024           (0x00000009)    /*!< (CK_SPIx_PR/CK_URTx) /1024 */
//!@}
  




/**
 * @name SPI_MSB_LSB_transmission
 *      SPI MSB LSB Transmission
 */
//!@{
#define SPI_FIRSTBIT_MSB                (0x00000000)    /*!< SPIx/URTx transmit first bit MSB */
#define SPI_FIRSTBIT_LSB                (0x00000001)    /*!< SPIx/URTx transmit first bit LSB */
//!@}


/**
 * @name SPI_Interrupt_definition
 *      SPI Interrupt Definition
 */
//!@{
#define SPI_IT_IEA                      SPI_INT_IEA_mask_w      /*!< SPIx interrupt all enable                                          */
#define SPI_IT_IDLF                     SPI_INT_IDL_IE_mask_w   /*!< SPIx slave mode NSS idle detect interrupt enable                   */
#define SPI_IT_TCF                      SPI_INT_TC_IE_mask_w    /*!< SPIx transmission complete interrupt enable                        */
#define SPI_IT_TXF                      SPI_INT_TX_IE_mask_w    /*!< SPI TX buffer underflow the threshold SPI0_TX_TH Interrupt enable  */
#define SPI_IT_RXF                      SPI_INT_RX_IE_mask_w    /*!< SPI Receive data register not empty interrupt enable               */
#define SPI_IT_MODF                     SPI_INT_MODF_IE_mask_w  /*!< SPI mode detect fault interrupt enable                             */
#define SPI_IT_WEF                      SPI_INT_WE_IE_mask_w    /*!< SPI slave mode write error interrupt enable                        */
#define SPI_IT_ROVRF                    SPI_INT_ROVR_IE_mask_w  /*!< SPI RX buffer receive overrun interrupt enable                     */
#define SPI_IT_TUDRF                    SPI_INT_TUDR_IE_mask_w  /*!< SPI TX buffer transmit underrun interrupt enable                   */
#define SPI_IT_ERR                      (SPI_IT_MODF | SPI_IT_WEF | SPI_IT_ROVRF | SPI_IT_TUDRF)    /*!< SPI error flag                 */
//!@}


/**
 * @name SPI_Flags_definition
 *      SPI Flags Definition
 */
//!@{
#define SPI_FLAG_BUSYF                  SPI_STA_BUSYF_mask_w    /*!< SPI data transfer busy flag                    */
#define SPI_FLAG_RXDF                   SPI_STA_RXDF_mask_w     /*!< SPI received data byte number is different from 
                                                                     previous received data byte number for SPI0_RDAT 
                                                                     register                                       */
#define SPI_FLAG_RXF                    SPI_STA_RXF_mask_w      /*!< SPI receive data register not empty            */
#define SPI_FLAG_TXF                    SPI_STA_TXF_mask_w      /*!< SPI transmit data register empty flag          */
#define SPI_FLAG_MODF                   SPI_STA_MODF_mask_w     /*!< SPI mode detect fault flag                     */
#define SPI_FLAG_WEF                    SPI_STA_WEF_mask_w      /*!< SPI slave mode write error flag                */

#define SPI_FLAG_RXLVL                  SPI_STA_RX_LVL_mask_b2  /*!< SPI data buffer received level indications     */
#define SPI_FLAG_TXLVL                  SPI_STA_TX_LVL_mask_b2  /*!< SPI data buffer transmission remained level 
                                                                     indications */
#define SPI_FLAG_RNUM                   SPI_STA_RNUM_mask_w     /*!< SPI received data byte number when data shadow 
                                                                     buffer last transfer to SPI0_RDAT register     */
//!@}


/**
 * @name SPI_Transmission_Buffer_Status_Level
 *      SPI Transmission Buffer Status Level
 */
//!@{
#define SPI_TXLVL_EMPTY                 (SPI_STA_TX_LVL_0_w)    /*!< SPIx TX shadow buffer empty    */
#define SPI_TXLVL_1BYTE                 (SPI_STA_TX_LVL_1_w)    /*!< SPIx TX shadow buffer 1 byte   */
#define SPI_TXLVL_2BYTE                 (SPI_STA_TX_LVL_2_w)    /*!< SPIx TX shadow buffer 2 bytes  */
#define SPI_TXLVL_3BYTE                 (SPI_STA_TX_LVL_3_w)    /*!< SPIx TX shadow buffer 3 bytes  */
#define SPI_TXLVL_4BYTE                 (SPI_STA_TX_LVL_4_w)    /*!< SPIx TX shadow buffer 4 bytes  */
//!@}


/**
 * @name SPI_Reception_Buffer_Status_Level
 *      SPI Reception Buffer Status Level
 */
//!@{
#define SPI_RXLVL_EMPTY                 (SPI_STA_RX_LVL_0_w)    /*!< SPIx RX shadow buffer empty    */
#define SPI_RXLVL_1BYTE                 (SPI_STA_RX_LVL_1_w)    /*!< SPIx RX shadow buffer 1 byte   */
#define SPI_RXLVL_2BYTE                 (SPI_STA_RX_LVL_2_w)    /*!< SPIx RX shadow buffer 2 bytes  */
#define SPI_RXLVL_3BYTE                 (SPI_STA_RX_LVL_3_w)    /*!< SPIx RX shadow buffer 3 bytes  */
#define SPI_RXLVL_4BYTE                 (SPI_STA_RX_LVL_4_w)    /*!< SPIx RX shadow buffer 4 bytes  */
//!@}



/**
 * @name SPIx_URTx_DMA_Request
 *      SPIx/URTx DMA TX/RX Request.
 */
#define SPI_DMA_TXEN                    SPI_CR0_DMA_TXEN_mask_w     /*!<SPI DMA TX request.*/
#define SPI_DMA_RXEN                    SPI_CR0_DMA_RXEN_mask_w     /*!<SPI DMA RX request.*/


/**
 * @name SPIx_URTx_DMA mask relationship.
 */
#define MID_DMA_SPI_READ_MASK           0x000F                        /*!<SPI DMA read mask.*/
#define MID_DMA_SPI_READ_MINID          MID_DMA_URT0_READ             /*!<SPI DMA Read source MIN ID.*/
#define MID_DMA_SPI_READ_MAXID          MID_DMA_SPI0_READ             /*!<SPI DMA Read source MAX ID.*/
#define MID_DMA_SPI_WRITE_MASK          0x0F00                        /*!<SPI DMA write mask*/
#define MID_DMA_SPI_WRITE_MINID         MID_DMA_URT0_WRITE            /*!<SPI DMA write destination MIN ID.*/
#define MID_DMA_SPI_WRITE_MAXID         MID_DMA_SPI0_WRITE            /*!<SPI DMA write destination MAX ID.*/


/**
 * @name SPIx_URTx_Reception_Buffer_Status_Level
 *      SPIx/URTx Reception Buffer Status Level
 */
//!@{ 
#define sSPI_RXBUF_THRESHOLD            SPI_CR2_RX_TH_mask_w    /*!< SPIx RX buffer mask    */
#define uSPI_RXBUF_THRESHOLD            URT_CR0_RX_TH_mask_w    /*!< URTx RX buffer mask   */

#define SPI_RXBUF_THRESHOLD_1BYTE       (SPI_CR2_RX_TH_1_byte_w | URT_CR0_RX_TH_1byte_w)    /*!< SPIx/URTx RX shadow buffer 1 byte     */
#define SPI_RXBUF_THRESHOLD_2BYTE       (SPI_CR2_RX_TH_2_byte_w | URT_CR0_RX_TH_2byte_w)    /*!< SPIx/URTx RX shadow buffer 2 bytes    */
#define SPI_RXBUF_THRESHOLD_3BYTE       (SPI_CR2_RX_TH_3_byte_w | URT_CR0_RX_TH_3byte_w)    /*!< SPIx/URTx RX shadow buffer 3 bytes    */
#define SPI_RXBUF_THRESHOLD_4BYTE       (SPI_CR2_RX_TH_4_byte_w | URT_CR0_RX_TH_4byte_w)    /*!< SPIx/URTx RX shadow buffer 4 bytes    */
//!@}


/**
 * @name SPI_Data_Line_Check
 *      SPI Data Line Check
 */
//!@{ 
#define IS_SPI_DATALINES_STANDARD_SPI(MODE) ((MODE) == SPI_STANDARD_SPI)        /*!< Check SPIx mode        */
//!@}


/**
 * @name Check_Data_Buffer_Alignment
 *      Check Data Buffer Alignment
 */
//!@{
#define IS_SPI_16BIT_ALIGNED_ADDRESS(DATA)  (((uint32_t)(DATA) % 2U) == 0U)     /*!< Check 16bit alignment  */
#define IS_SPI_32BIT_ALIGNED_ADDRESS(DATA)  (((uint32_t)(DATA) % 4U) == 0U)     /*!< Check 32bit alignment  */
//!@}


/**
 *******************************************************************************
 * @brief       Enable the specified SPI interrupts.
 * @details  
 * @param[in]   "__HANDLE__" specifies the SPI Handle.
 *              This parameter can be SPI0/URT0/URT1/URT2/URT3.
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @param[in]   "__INTERRUPT__" specifies the interrupt source to enable.
 *              This parameter can be one of the following values:
 *  @arg\b          SPI_IT_ERR: Error interrupt enable (SPI_IT_MODF | SPI_WEF | mSPI->SPI_FLAG_TUDRF | mSPI->SPI_FLAG_ROVRF)
 *  @arg\b          mSPI->SPI_FLAG_TUDRF: SPI TX buffer transmit underrun interrupt enable
 *  @arg\b          mSPI->SPI_FLAG_ROVRF: SPI RX buffer receive overrun interrupt enable
 *  @arg\b          SPI_IT_WEF: SPI slave mode write error interrupt enable
 *  @arg\b          SPI_IT_MODF: SPI mode detect fault interrupt enable
 *  @arg\b          SPI_IT_TXF: TDAT empty interrupt enable
 *  @arg\b          SPI_IT_RXF: RDAT buffer not empty interrupt enable
 *  @arg\b          mSPI->SPI_FLAG_TCF: SPI transmission complete interrupt enable
 *  @arg\b          mSPI->SPI_FLAG_IDLF: SPI slave mode NSS idle detect interrupt enable
 *  @arg\b          SPI_IT_IEA: SPI interrupt all enable
 * @return      None
 * @note
 * @par         Example
 * @code
    __MID_SPI_ENABLE_IT(mSPI, (SPI_IT_RXF | mSPI->SPI_FLAG_ERROR | SPI_IT_IEA));
 * @endcode
 *******************************************************************************
 */
#define __MID_SPI_ENABLE_IT(__HANDLE__, __INTERRUPT__)   SET_BIT((__HANDLE__)->Instance->INT.W, (__INTERRUPT__))


/**
 *******************************************************************************
 * @brief       Disable the specified SPI interrupts.
 * @details  
 * @param[in]   "__HANDLE__" specifies the SPI Handle.
 *              This parameter can be SPI0/URT0/URT1/URT2/URT3.
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @param[in]   "__INTERRUPT__" specifies the interrupt source to enable.
 *              This parameter can be one of the following values:
 *  @arg\b          SPI_IT_ERR: Error interrupt enable (SPI_IT_MODF | SPI_WEF | mSPI->SPI_FLAG_TUDRF | mSPI->SPI_FLAG_ROVRF)
 *  @arg\b          mSPI->SPI_FLAG_TUDRF: SPI TX buffer transmit underrun interrupt enable
 *  @arg\b          mSPI->SPI_FLAG_ROVRF: SPI RX buffer receive overrun interrupt enable
 *  @arg\b          SPI_IT_WEF: SPI slave mode write error interrupt enable
 *  @arg\b          SPI_IT_MODF: SPI mode detect fault interrupt enable
 *  @arg\b          SPI_IT_TXF: TDAT empty interrupt enable
 *  @arg\b          SPI_IT_RXF: RDAT buffer not empty interrupt enable
 *  @arg\b          mSPI->SPI_FLAG_TCF: SPI transmission complete interrupt enable
 *  @arg\b          mSPI->SPI_FLAG_IDLF: SPI slave mode NSS idle detect interrupt enable
 *  @arg\b          SPI_IT_IEA: SPI interrupt all enable
 * @return      None
 * @note
 * @par         Example
 * @code
    __MID_SPI_DISABLE_IT(mSPI, (SPI_IT_TXF | mSPI->SPI_FLAG_TCF | mSPI->SPI_FLAG_ERROR));
 * @endcode
 *******************************************************************************
 */
#define __MID_SPI_DISABLE_IT(__HANDLE__, __INTERRUPT__)  CLEAR_BIT((__HANDLE__)->Instance->INT.W, (__INTERRUPT__))


/**
 *******************************************************************************
 * @brief       Check whether the specified SPI interrupt source is enabled or not.
 * @details  
 * @param[in]   "__HANDLE__" specifies the SPI Handle.
 *              This parameter can be SPI0/URT0/URT1/URT2/URT3.
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @param[in]   "__INTERRUPT__" specifies the interrupt source to enable.
 *              This parameter can be one of the following values:
 *  @arg\b          SPI_IT_ERR: Error interrupt enable (SPI_IT_MODF | SPI_WEF | mSPI->SPI_FLAG_TUDRF | mSPI->SPI_FLAG_ROVRF)
 *  @arg\b          mSPI->SPI_FLAG_TUDRF: SPI TX buffer transmit underrun interrupt enable
 *  @arg\b          mSPI->SPI_FLAG_ROVRF: SPI RX buffer receive overrun interrupt enable
 *  @arg\b          SPI_IT_WEF: SPI slave mode write error interrupt enable
 *  @arg\b          SPI_IT_MODF: SPI mode detect fault interrupt enable
 *  @arg\b          SPI_IT_TXF: TDAT empty interrupt enable
 *  @arg\b          SPI_IT_RXF: RDAT buffer not empty interrupt enable
 *  @arg\b          mSPI->SPI_FLAG_TCF: SPI transmission complete interrupt enable
 *  @arg\b          mSPI->SPI_FLAG_IDLF: SPI slave mode NSS idle detect interrupt enable
 *  @arg\b          SPI_IT_IEA: SPI interrupt all enable
 * @return      The new state of __IT__ (SET or CLR).
 * @note
 * @par         Example
 * @code
    if(__MID_SPI_GET_IT_SOURCE(mSPI, SPI_IT_TXF))
 * @endcode
 *******************************************************************************
 */
#define __MID_SPI_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->Instance->INT.W & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : CLR)


/**
 *******************************************************************************
 * @brief       Check whether the specified SPI flag is set or not.
 * @details  
 * @param[in]   "__HANDLE__" specifies the SPI Handle.
 *              This parameter can be SPI0/URT0/URT1/URT2/URT3.
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @param[in]   "__FLAG__" specifies the flag to check.
 *              This parameter can be one of the following values:
 *  @arg\b          mSPI->SPI_FLAG_TUDRF: SPI slave mode transmit underrun flag
 *  @arg\b          mSPI->SPI_FLAG_ROVRF: SPI receive overrun flag
 *  @arg\b          SPI_FLAG_WEF: SPI slave mode write error flag
 *  @arg\b          SPI_FLAG_MODF: SPI mode detect fault flag
 *  @arg\b          SPI_FLAG_TXF: SPI transmit data register empty flag
 *  @arg\b          SPI_FLAG_RXF: SPI receive data register not empty
 *  @arg\b          SPI_FLAG_RXDF: SPI received data byte number is different from previous 
 *                  received data byte number for SPI0_RDAT register.
 *  @arg\b          mSPI->SPI_FLAG_TCF: SPI transmission complete flag
 *  @arg\b          mSPI->SPI_FLAG_IDLF: SPI slave mode NSS idle detect flag
 *  @arg\b          SPI_FLAG_BUSYF: SPI data transfer busy flag

 * @return      The new state of __IT__ (SET or CLR).
 * @note
 * @par         Example
 * @code
    if(__MID_SPI_GET_FLAG(mSPI, SPI_FLAG_RXF))
 * @endcode
 *******************************************************************************
 */
#define __MID_SPI_GET_FLAG(__HANDLE__, __FLAG__) ((((__HANDLE__)->Instance->STA.W) & (__FLAG__)) == (__FLAG__))


/**
 *******************************************************************************
 * @brief       Clear the SPI MODF pending flag.
 * @details  
 * @param[in]   "__HANDLE__" specifies the SPI Handle.
 *              This parameter can be SPI0.
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      None
 * @note
 * @par         Example
 * @code
    __MID_SPI_CLEAR_MODFFLAG(mSPI); 
 * @endcode
 *******************************************************************************
 */
#define __MID_SPI_CLEAR_MODFFLAG(__HANDLE__)                            \
    do{                                                                 \
        __IO uint32_t tmpreg_modf = 0x00U;                              \
        tmpreg_modf = (__HANDLE__)->Instance->STA.W;                    \
        SET_BIT((__HANDLE__)->Instance->STA.W, SPI_FLAG_MODF);          \
        CLEAR_BIT((__HANDLE__)->Instance->CR0.W, SPI_CR0_EN_mask_w);    \
        UNUSED(tmpreg_modf);                                            \
    } while(0U)


/**
 *******************************************************************************
 * @brief       Clear the SPI ROVRF pending flag.
 * @details  
 * @param[in]   "__HANDLE__" specifies the SPI Handle.
 *              This parameter can be SPI0/URT0/URT1/URT2/URT3.
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      None
 * @note
 * @par         Example
 * @code
    __MID_SPI_CLEAR_ROVRFFLAG(mSPI); 
 * @endcode
 *******************************************************************************
 */
#define __MID_SPI_CLEAR_ROVRFFLAG(__HANDLE__)                                   \
    do{                                                                         \
        __IO uint32_t tmpreg_ovr = 0x00U;                                       \
        tmpreg_ovr = (__HANDLE__)->Instance->RDAT.W;                            \
        tmpreg_ovr = (__HANDLE__)->Instance->RDAT.W;                            \
        tmpreg_ovr = (__HANDLE__)->Instance->STA.W;                             \
        SET_BIT((__HANDLE__)->Instance->STA.W, (__HANDLE__)->SPI_FLAG_ROVRF);   \
        UNUSED(tmpreg_ovr);                                                     \
    }while(0U)


/**
 *******************************************************************************
 * @brief       Clear the SPI TUDRF pending flag.
 * @details  
 * @param[in]   "__HANDLE__" specifies the SPI Handle.
 *              This parameter can be SPI0/URT0/URT1/URT2/URT3.
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      None
 * @note
 * @par         Example
 * @code
    __MID_SPI_CLEAR_TUDRFFLAG(mSPI); 
 * @endcode
 *******************************************************************************
 */
#define __MID_SPI_CLEAR_TUDRFFLAG(__HANDLE__)                                   \
    do{                                                                         \
        __IO uint32_t tmpreg_ovr = 0x00U;                                       \
        tmpreg_ovr = (__HANDLE__)->Instance->RDAT.W;                            \
        tmpreg_ovr = (__HANDLE__)->Instance->STA.W;                             \
        SET_BIT((__HANDLE__)->Instance->STA.W, (__HANDLE__)->SPI_FLAG_TUDRF);   \
        UNUSED(tmpreg_ovr);                                                     \
    }while(0U)
    

/**
 *******************************************************************************
 * @brief       Clear the SPI WEF pending flag.
 * @details  
 * @param[in]   "__HANDLE__" specifies the SPI Handle.
 *              This parameter can be SPI0.
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      None
 * @note
 * @par         Example
 * @code
    __MID_SPI_CLEAR_WEFFLAG(mSPI); 
 * @endcode
 *******************************************************************************
 */
#define __MID_SPI_CLEAR_WEFFLAG(__HANDLE__)                     \
    do{                                                         \
        __IO uint32_t tmpreg_fre = 0x00U;                       \
        tmpreg_fre = (__HANDLE__)->Instance->STA.W;             \
        SET_BIT((__HANDLE__)->Instance->STA.W, SPI_FLAG_WEF);   \
        UNUSED(tmpreg_fre);                                     \
    }while(0U)


/**
 *******************************************************************************
 * @brief       Enable the SPI peripheral.
 * @details  
 * @param[in]   "__HANDLE__" specifies the SPI Handle.
 *              This parameter can be SPI0/URT0/URT1/URT2/URT3.
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      None
 * @note
 * @par         Example
 * @code
    __MID_SPI_ENABLE(mSPI); 
 * @endcode
 *******************************************************************************
 */
#define __MID_SPI_ENABLE(__HANDLE__)  SET_BIT((__HANDLE__)->Instance->CR0.W, SPI_CR0_EN_mask_w)


/**
 *******************************************************************************
 * @brief       Disable the SPI peripheral.
 * @details  
 * @param[in]   "__HANDLE__" specifies the SPI Handle.
 *              This parameter can be SPI0/URT0/URT1/URT2/URT3.
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      None
 * @note
 * @par         Example
 * @code
    __MID_SPI_DISABLE(mSPI); 
 * @endcode
 *******************************************************************************
 */
#define __MID_SPI_DISABLE(__HANDLE__)  CLEAR_BIT((__HANDLE__)->Instance->CR0.W, SPI_CR0_EN_mask_w)


/**
 *******************************************************************************
 * @brief       Set the SPI transmit-only mode.
 * @details  
 * @param[in]   "__HANDLE__" specifies the SPI Handle.
 *              This parameter can be SPI0.
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      None
 * @note
 * @par         Example
 * @code
    SPI_XLINE_TX(mSPI); 
 * @endcode
 *******************************************************************************
 */
#define SPI_XLINE_TX(__HANDLE__)  SET_BIT((__HANDLE__)->Instance->CR2.W, SPI_CR2_BDIR_OE_mask_w)


/**
 *******************************************************************************
 * @brief       Set the SPI receive-only mode.
 * @details  
 * @param[in]   "__HANDLE__" specifies the SPI Handle.
 *              This parameter can be SPI0.
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      None
 * @note
 * @par         Example
 * @code
    SPI_XLINE_RX(mSPI); 
 * @endcode
 *******************************************************************************
 */
#define SPI_XLINE_RX(__HANDLE__)  CLEAR_BIT((__HANDLE__)->Instance->CR2.W, SPI_CR2_BDIR_OE_mask_w)


/**
 *******************************************************************************
 * @brief       Flush RX buffer data
 * @details  
 * @param[in]   "__HANDLE__" specifies the SPI Handle.
 *              This parameter can be SPI0/URT0/URT1/URT2/URT3.
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      None
 * @note
 * @par         Example
 * @code
    __MID_SPI_CLEAR_RXDATA(mSPI); 
 * @endcode
 *******************************************************************************
 */
#define __MID_SPI_CLEAR_RXDATA(__HANDLE__)  SET_BIT(*(__HANDLE__)->RXTX_CLR, (SPI_CR1_RDAT_CLR_mask_b0 | URT_CR4_RDAT_CLR_mask_b0))


/**
 *******************************************************************************
 * @brief       Flush TX buffer data
 * @details  
 * @param[in]   "__HANDLE__" specifies the SPI Handle.
 *              This parameter can be SPI0/URT0/URT1/URT2/URT3.
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      None
 * @note
 * @par         Example
 * @code
    __MID_SPI_CLEAR_TXDATA(mSPI); 
 * @endcode
 *******************************************************************************
 */
#define __MID_SPI_CLEAR_TXDATA(__HANDLE__)  SET_BIT(*(__HANDLE__)->RXTX_CLR, (SPI_CR1_TDAT_CLR_mask_b0 | URT_CR4_TDAT_CLR_mask_b0))


/**
 *******************************************************************************
 * @brief       Flush TX / RX buffer data
 * @details  
 * @param[in]   "__HANDLE__" specifies the SPI Handle.
 *              This parameter can be SPI0/URT0/URT1/URT2/URT3.
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      None
 * @note
 * @par         Example
 * @code
    __MID_SPI_CLEAR_RXTXDATA(mSPI); 
 * @endcode
 *******************************************************************************
 */
#define __MID_SPI_CLEAR_RXTXDATA(__HANDLE__) SET_BIT(*(__HANDLE__)->RXTX_CLR, (SPI_CR1_TDAT_CLR_mask_b0 | URT_CR4_TDAT_CLR_mask_b0) |\
                                                                              (SPI_CR1_RDAT_CLR_mask_b0 | URT_CR4_RDAT_CLR_mask_b0))


/**
 *******************************************************************************
 * @brief       Get the SPI status
 * @details  
 * @param[in]   "__HANDLE__" specifies the SPI Handle.
 *              This parameter can be SPI0/URT0/URT1/URT2/URT3.
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      None
 * @note
 * @par         Example
 * @code
    while(__MID_SPI_GET_STATE(mSPI3) != MID_SPI_STATE_READY);
 * @endcode
 *******************************************************************************
 */
#define __MID_SPI_GET_STATE(__HANDLE__)  ((__HANDLE__).State)


/**
 *******************************************************************************
 * @brief       Get the SPI error
 * @details  
 * @param[in]   "__HANDLE__" specifies the SPI Handle.
 *              This parameter can be SPI0/URT0/URT1/URT2/URT3.
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      None
 * @note
 * @par         Example
 * @code
    if(__MID_SPI_GET_ERROR_CODE(mSPI3) == MID_SPI_ERROR_ABORT);
 * @endcode
 *******************************************************************************
 */
#define __MID_SPI_GET_ERROR_CODE(__HANDLE__)  ((__HANDLE__).ErrorCode)


/**
 * @name    Function announce
 * @brief   SPIx/URTx base initial/Deinitial
 */ 
//!@{
MID_StatusTypeDef MID_SPI_DeInit(SPI_HandleTypeDef *mSPI);
MID_StatusTypeDef MID_SPI_Init(SPI_HandleTypeDef *mSPI);
void MID_SPI_MspInit(SPI_HandleTypeDef *mSPI);
void MID_SPI_MspDeInit(SPI_HandleTypeDef *mSPI);
//!@}


/**         
 * @name    Function announce
 * @brief   SPIx/URTx transmit/receive
 */ 
//!@{
MID_StatusTypeDef MID_SPI_Transmit(SPI_HandleTypeDef *mSPI, uint8_t *pData, uint32_t Size, uint32_t Timeout);
MID_StatusTypeDef MID_SPI_Receive(SPI_HandleTypeDef *mSPI, uint8_t *pData, uint32_t Size, uint32_t Timeout);
MID_StatusTypeDef MID_SPI_TransmitReceive(SPI_HandleTypeDef *mSPI, uint8_t *pTxData, uint8_t *pRxData, uint32_t Size, uint32_t Timeout);

MID_StatusTypeDef MID_SPI_Transmit_IT(SPI_HandleTypeDef *mSPI, uint8_t *pData, uint32_t Size);
MID_StatusTypeDef MID_SPI_Receive_IT(SPI_HandleTypeDef *mSPI, uint8_t *pData, uint32_t Size);
MID_StatusTypeDef MID_SPI_TransmitReceive_IT(SPI_HandleTypeDef *mSPI, uint8_t *pTxData, uint8_t *pRxData, uint32_t Size);

MID_StatusTypeDef MID_SPI_Transmit_DMA(SPI_HandleTypeDef *mSPI, uint8_t *pData, uint32_t Size);
MID_StatusTypeDef MID_SPI_Receive_DMA(SPI_HandleTypeDef *mSPI, uint8_t *pData, uint32_t Size); 
MID_StatusTypeDef MID_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *mSPI, uint8_t *pTxData, uint8_t *pRxData,uint32_t Size);


///* Transfer Abort functions */  
MID_StatusTypeDef MID_SPI_Abort(SPI_HandleTypeDef *mSPI);
MID_StatusTypeDef MID_SPI_Abort_IT(SPI_HandleTypeDef *mSPI);

void MID_SPI_IRQHandler(SPI_HandleTypeDef *mSPI);
void MID_SPI_TxCpltCallback(SPI_HandleTypeDef *mSPI);
void MID_SPI_RxCpltCallback(SPI_HandleTypeDef *mSPI);
void MID_SPI_TxRxCpltCallback(SPI_HandleTypeDef *mSPI);
void MID_SPI_TxHalfCpltCallback(SPI_HandleTypeDef *mSPI);
void MID_SPI_RxHalfCpltCallback(SPI_HandleTypeDef *mSPI);
void MID_SPI_TxRxHalfCpltCallback(SPI_HandleTypeDef *mSPI);
void SPI_DMATransmitCplt(DMA_HandleTypeDef *mDMA);

void MID_SPI_ErrorCallback(SPI_HandleTypeDef *mSPI);
void MID_SPI_AbortCpltCallback(SPI_HandleTypeDef *mSPI);



#ifdef __cplusplus
}
#endif

//!@}
/* Peripheral State and Error functions ***************************************/
  
#endif
  
  
