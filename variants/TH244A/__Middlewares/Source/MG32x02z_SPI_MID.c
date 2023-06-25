/**
 *******************************************************************************
 *
 * @file        MG32x02z_SPI_MID.c
 *
 * @brief       This is the C code format middleware file for SPI module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.09
 * @date        2022/07/04
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



#include "MG32x02z_SPI_MID.h"
#include "MG32x02z_CSC_MID.h"
#include "MG32x02z_CSC_Init.h"

extern  uint32_t SystemCoreClock;    /*!< System Clock Frequency (Core Clock)*/
//#define SystemCoreClock CONF_CK_APB_FREQ
#define SPI_DEFAULT_TIMEOUT 100U


static void SPI_2linesRxISR_8BIT(struct tag_SPI_HandleTypeDef *mSPI);
static void SPI_2linesTxISR_8BIT(struct tag_SPI_HandleTypeDef *mSPI);
static void SPI_2linesRxISR_16BIT(struct tag_SPI_HandleTypeDef *mSPI);
static void SPI_2linesTxISR_16BIT(struct tag_SPI_HandleTypeDef *mSPI);
static void SPI_2linesRxISR_32BIT(struct tag_SPI_HandleTypeDef *mSPI);
static void SPI_2linesTxISR_32BIT(struct tag_SPI_HandleTypeDef *mSPI);

static void SPI_RxISR_8BIT(struct tag_SPI_HandleTypeDef *mSPI);
static void SPI_RxISR_16BIT(struct tag_SPI_HandleTypeDef *mSPI);
static void SPI_RxISR_32BIT(struct tag_SPI_HandleTypeDef *mSPI);
static void SPI_TxISR_8BIT(struct tag_SPI_HandleTypeDef *mSPI);
static void SPI_TxISR_16BIT(struct tag_SPI_HandleTypeDef *mSPI);
static void SPI_TxISR_32BIT(struct tag_SPI_HandleTypeDef *mSPI);

static void SPI_DMAReceiveCplt(DMA_HandleTypeDef *mDMA);
static void SPI_DMATransmitReceiveCplt(DMA_HandleTypeDef *mDMA);
static void SPI_DMAHalfTransmitCplt(DMA_HandleTypeDef *mDMA);
static void SPI_DMAHalfReceiveCplt(DMA_HandleTypeDef *mDMA);
static void SPI_DMAHalfTransmitReceiveCplt(DMA_HandleTypeDef *mDMA);

static void SPI_DMAAbortOnError(DMA_HandleTypeDef *mdma);
static void SPI_DMATxAbortCallback(DMA_HandleTypeDef *mdma);
static void SPI_DMARxAbortCallback(DMA_HandleTypeDef *mdma);

static MID_StatusTypeDef SPI_WaitFlagStateUntilTimeout(SPI_HandleTypeDef *mSPI, uint32_t Flag, uint32_t State, uint32_t Timeout, uint32_t Tickstart);
static MID_StatusTypeDef SPI_WaitFifoStateUntilTimeout(SPI_HandleTypeDef *mSPI, uint32_t Fifo, uint32_t State, uint32_t Timeout, uint32_t Tickstart);
static MID_StatusTypeDef SPI_EndRxTxTransaction(SPI_HandleTypeDef *mSPI, uint32_t Timeout, uint32_t Tickstart);
static MID_StatusTypeDef SPI_EndRxTransaction(SPI_HandleTypeDef *mSPI,  uint32_t Timeout, uint32_t Tickstart);

static void SPI_CloseRxTx_ISR(SPI_HandleTypeDef *mSPI);
static void SPI_CloseRx_ISR(SPI_HandleTypeDef *mSPI);
static void SPI_CloseTx_ISR(SPI_HandleTypeDef *mSPI);
static void SPI_AbortRx_ISR(SPI_HandleTypeDef *mSPI);
static void SPI_AbortTx_ISR(SPI_HandleTypeDef *mSPI);

static void SPI_DMAError(DMA_HandleTypeDef *mDMA);


/**
 * @name SPI_MODE_TABLE
 *      SPI mode table
 */
//!@{
static uint32_t SPI_MODE_TABLE[24] = {0x00, 0x00,                                                                                               /*!< [0x00 ~ 0x01] Reserved */
                                      (SPI_CR0_MDS_slave_w | SPI_CR0_NSSO_EN_disable_w | SPI_CR0_NSSI_EN_enable_w | SPI_CR0_NSSI_SEL_nss_w),    /*!< [0x02] SPI_MODE_SLAVE_NSS */ 
                                      0x00, 0x00, 0x00,                                                                                         /*!< [0x03 ~ 0x05] Reserved */
                                      (SPI_CR0_MDS_slave_w | SPI_CR0_NSSO_EN_disable_w | SPI_CR0_NSSI_EN_disable_w),                            /*!< [0x06] SPI_MODE_SLAVE */
                                      (SPI_CR0_MDS_slave_w | SPI_CR0_NSSO_EN_disable_w | SPI_CR0_NSSI_EN_enable_w | SPI_CR0_NSSI_SEL_nssi_w),   /*!< [0x07] SPI_MODE_SLAVE_NSSI */
                                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                           /*!< [0x08 ~ 0x0F] Reserved */
                                      (SPI_CR0_MDS_master_w | SPI_CR0_NSSO_EN_disable_w | SPI_CR0_NSSI_EN_disable_w),                           /*!< [0x10] SPI_MODE_MASTER */
                                      (SPI_CR0_MDS_master_w | SPI_CR0_NSSO_EN_enable_w | SPI_CR0_NSSI_EN_disable_w),                            /*!< [0x11] SPI_MODE_MASTER_NSS */
                                      0x00,                                                                                                     /*!< [0x12] Reserved */
                                      (SPI_CR0_MDS_master_w | SPI_CR0_NSSO_EN_disable_w | SPI_CR0_NSSI_EN_enable_w | SPI_CR0_NSSI_SEL_nss_w),   /*!< [0x13] SPI_MODE_MASTER_MODF_AT_NSS */
                                      (SPI_CR0_MDS_master_w | SPI_CR0_NSSO_EN_disable_w | SPI_CR0_NSSI_EN_enable_w | SPI_CR0_NSSI_SEL_nssi_w),  /*!< [0x14] SPI_MODE_MASTER_MODF_AT_NSSI */
                                      (SPI_CR0_MDS_master_w | SPI_CR0_NSSO_EN_enable_w | SPI_CR0_NSSI_EN_enable_w | SPI_CR0_NSSI_SEL_nssi_w),   /*!< [0x15] SPI_MODE_MASTER_NSS_MODF */
                                      0x00, 0x00};                                                                                              /*!< [0x16 ~ 0x17] Reserved */
//!@}

             

/**
 * @name SPI_CLOCK_TABLE
 *      SPI clock table
 */
//!@{ 
static uint32_t SPI_CLKDIV_TABLE[10] = {(SPI_CLK_CK_DIV_div2_w | 0x00000000 | SPI_CLK_CK_PDIV_div1_w),      /*!< Clock divider 2    */
                                        (SPI_CLK_CK_DIV_div4_w | 0x00000000 | SPI_CLK_CK_PDIV_div1_w),      /*!< Clock divider 4    */
                                        (SPI_CLK_CK_DIV_div8_w | 0x00000000 | SPI_CLK_CK_PDIV_div1_w),      /*!< Clock divider 8    */
                                        (SPI_CLK_CK_DIV_div16_w | 0x00000000 | SPI_CLK_CK_PDIV_div1_w),     /*!< Clock divider 16   */
                                        (SPI_CLK_CK_DIV_div16_w | 0x00000100 | SPI_CLK_CK_PDIV_div1_w),     /*!< Clock divider 32   */
                                        (SPI_CLK_CK_DIV_div16_w | 0x00000300 | SPI_CLK_CK_PDIV_div1_w),     /*!< Clock divider 64   */
                                        (SPI_CLK_CK_DIV_div16_w | 0x00000700 | SPI_CLK_CK_PDIV_div1_w),     /*!< Clock divider 128  */
                                        (SPI_CLK_CK_DIV_div16_w | 0x00000700 | SPI_CLK_CK_PDIV_div2_w),     /*!< Clock divider 256  */
                                        (SPI_CLK_CK_DIV_div16_w | 0x00000700 | SPI_CLK_CK_PDIV_div4_w),     /*!< Clock divider 512  */
                                        (SPI_CLK_CK_DIV_div16_w | 0x00000700 | SPI_CLK_CK_PDIV_div8_w)};    /*!< Clock divider 1024 */
//!@}

/**
 * @name    Initial/Deinitial TM with SPI_HandleTypeDef
 *
 */
///@{
/**
 *******************************************************************************
 * @brief       Initialize the SPI peripheral..
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      MID status
 * @note
 * @par         Example
 * @code
    SPI_HandleTypeDef mSPI0;
 
    mSPI0.Instance = SPI_SPI0;
    mSPI0.Init.Mode = SPI_MODE_MASTER;
    mSPI0.Init.DataLine = SPI_STANDARD_SPI;
    mSPI0.Init.DataSize = SPI_DATASIZE_8BIT;
    mSPI0.Init.CLKPolarity = SPI_POLARITY_LOW;
    mSPI0.Init.CLKPhase = SPI_PHASE_1EDGE;
    mSPI0.Init.NSS = SPI_NSS_HARDWARE;
    mSPI0.Init.ClockDivider = SPI_CLOCKDIVIDER_2;
    mSPI0.Init.FirstBit = SPI_FIRSTBIT_MSB;
    mSPI0.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
    mSPI0.Init.Swap = SPI_SWAP_DISABLE;
    mSPI0.Init.IdleDataOut = SPI_IDLE_DATA_OUT_TRISTATE;
    
    // Support MG32F02U128/U064/A128/A064 and MG32F02V032
    mSPI0.Init.SlaveClockInputControl = SPI_SLV_ClockSynchronous;
    
    // Support MG32F02V032
    mSPI0.Init.SlaveTransmitTimingControl = SPI_SLV_TransmitTiming_Normal;    
    
    MID_SPI_Init(&mSPI0);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_SPI_Init(SPI_HandleTypeDef *mSPI)
{
    uint32_t frxth;
    uint32_t index;

    //=========================================================================
    // Check the SPI handle allocation
    if (mSPI == NULL)
    {
        return MID_ERROR;
    }

    //=========================================================================
    // Check the parameters
    assert_param(IS_SPI_ALL_INSTANCE(mSPI->Instance));
    assert_param(IS_SPI_MODE(mSPI->Init.Mode));
    assert_param(IS_SPI_DIRECTION(mSPI->Init.Direction));
    assert_param(IS_SPI_DATASIZE(mSPI->Init.DataSize));
    assert_param(IS_SPI_NSS(mSPI->Init.NSS));
    assert_param(IS_SPI_NSSP(mSPI->Init.NSSPMode));
    assert_param(IS_SPI_BAUDRATE_PRESCALER(mSPI->Init.ClockDivider));
    assert_param(IS_SPI_FIRST_BIT(mSPI->Init.FirstBit));
    assert_param(IS_SPI_TIMODE(mSPI->Init.TIMode));

    //=========================================================================
    //SPI or URT register define.
    mSPI->REG_TYPE = (uint32_t)(&mSPI->Instance->STA.W);
    index          = mSPI->REG_TYPE & MID_SPI_INDEX_MASK;
    mSPI->REG_TYPE = mSPI->REG_TYPE & MID_SPI_MASK;

    // When SPI state is reset
    if (mSPI->State == MID_SPI_STATE_RESET)
    {
        // Allocate lock resource and initialize it
        mSPI->Lock = MID_UNLOCKED;
        // Init the low level hardware : GPIO, CLOCK, NVIC...
        MID_SPI_MspInit(mSPI);
    }

    // Set SPI state is busy
    mSPI->State = MID_SPI_STATE_BUSY;
    
    //=========================================================================
    // Disable the selected SPI peripheral
    CLEAR_BIT(mSPI->Instance->CR0.W , SPI_CR0_EN_mask_w);

    //=========================================================================
    // When selection moduel is SPI
    if(mSPI->REG_TYPE == MID_SPI_SPI)
    {
        //=========================================================================
        // Align by default the rs fifo threshold on the data size
        frxth = (SPI_RXBUF_THRESHOLD_1BYTE & sSPI_RXBUF_THRESHOLD);
        if ((mSPI->Init.DataSize > SPI_DATASIZE_8BIT) && (mSPI->Init.DataSize <= SPI_DATASIZE_16BIT))
        {
          frxth = (SPI_RXBUF_THRESHOLD_2BYTE & sSPI_RXBUF_THRESHOLD);
        }
        if ((mSPI->Init.DataSize > SPI_DATASIZE_16BIT) && (mSPI->Init.DataSize <= SPI_DATASIZE_24BIT))
        {
          frxth = (SPI_RXBUF_THRESHOLD_3BYTE & sSPI_RXBUF_THRESHOLD);
        }
        if(mSPI->Init.DataSize > SPI_DATASIZE_24BIT)
        {
            frxth = (SPI_RXBUF_THRESHOLD_4BYTE & sSPI_RXBUF_THRESHOLD);
        }
        
        /*----------------------- SPIx Configuration ---------------------*/
        /* Configure : SPI Mode, Communication Mode, Clock polarity and phase, NSS management,
        Communication speed mode First bit  */
        /* Not support SSM and CRC.... */
        //=========================================================================
        //Init:
        //    - 1. Clock divider.
        //    - 2. Mode, CLKPolarity, NSS, CLKPhase and FirstBit
        //    - 3. NSS pulse time
        //    - 4. Data lines and data size, NSS software in/out state and RX threshold
        //    - 5. Map flag and IRQ to SPI
        //    - 6. RX shadow buffer level relationship register define.
        //--------------------------------------------------------------------
        mSPI->Instance->CLK.W = SPI_CLKDIV_TABLE [mSPI->Init.ClockDivider] | 
                                SPI_CLK_CK_SEL_proc_w;
        
        //--------------------------------------------------------------------
            mSPI->Instance->CR0.W = SPI_MODE_TABLE [mSPI->Init.Mode] | 
                                ((mSPI->Init.CLKPolarity) ) | 
                                ((mSPI->Init.CLKPhase) ) | 
                                (mSPI->Init.FirstBit << 3) | 
                                ((mSPI->Init.NSS << 11) & SPI_CR0_NSS_SWEN_mask_w) |
                                ((mSPI->Init.NSSPMode << 14) & SPI_CR0_NSS_PEN_mask_w);
#if (defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH))
        #if defined(SPI_CR0_DOUT_IDL_mask_w)
        mSPI->Instance->CR0.W |= SPI_CR0_DMA_MDS_enable_w | 
                                 mSPI->Init.Swap | 
                                 (mSPI->Init.IdleDataOut & ( SPI_CR0_DOUT_MDS_mask_w | SPI_CR0_DOUT_IDL_mask_w));
        #else
        mSPI->Instance->CR0.W |= SPI_CR0_DMA_MDS_enable_w | 
                                 mSPI->Init.Swap | 
                                 (mSPI->Init.IdleDataOut & ( SPI_CR0_DOUT_MDS_mask_w ));
        #endif
#endif

#if (defined(MG32_3RD) || defined(MG32_4TH))
        mSPI->Instance->CR0.W |= (mSPI->Init.SlaveClockInputControl || 
                                  mSPI->Init.SlaveTransmitTimingControl);
#endif

        //--------------------------------------------------------------------
#if (defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)) 
        mSPI->Instance->CR1.W = (mSPI->Init.NSSPMode << 15) & SPI_CR1_NSS_IDT_mask_w;
#endif
        //--------------------------------------------------------------------
        mSPI->Instance->CR2.W = ((mSPI->Init.DataLine) << 4) | 
                               ((mSPI->Init.DataSize) << 16) |
                               frxth;
        //--------------------------------------------------------------------
        mSPI->SPI_FLAG_TUDRF = SPI_INT_TUDR_IE_mask_w;
        mSPI->SPI_FLAG_ROVRF = SPI_STA_ROVRF_mask_w;
        mSPI->SPI_FLAG_ERROR = (SPI_FLAG_MODF | SPI_FLAG_WEF | SPI_STA_ROVRF_mask_w | SPI_STA_TUDRF_mask_w);
        mSPI->SPI_FLAG_IDLF  = SPI_STA_IDLF_mask_w;
        mSPI->SPI_FLAG_TCF   = SPI_STA_TCF_mask_w;
        mSPI->SPI_IRQ        = SPI0_IRQn;

        //--------------------------------------------------------------------
        mSPI->RX_TH  = &(mSPI->Instance->CR2.B[1]);
        mSPI->RXTX_LVL = &(mSPI->Instance->STA.B[2]);
        mSPI->RXTX_CLR = &(mSPI->Instance->CR1.B[0]);
        mSPI->RNUM     = &(mSPI->Instance->STA.B[3]);
    }
    // When selection moduel is SPI mode of URTx
    else if(mSPI->REG_TYPE == MID_SPI_URT)
    {
        //=========================================================================
        // Align by default the rs fifo threshold on the data size
        if(mSPI->Init.DataSize != SPI_DATASIZE_8BIT)
        {
            return( MID_ERROR );
        }
        frxth = (SPI_RXBUF_THRESHOLD_4BYTE & uSPI_RXBUF_THRESHOLD);
        
        /*----------------------- SPIx Configuration ---------------------*/
        /* Configure : SPI Mode, Communication Mode, Clock polarity and phase, NSS management,
        Communication speed mode First bit  */
        /* Not support SSM and CRC.... */
        //=========================================================================
        //Init:
        //    - 1. Clock divider.
        //    - 2. Mode
        //    - 3. CLKPolarity & CLKPhase
        //    - 4. FirstBit
        //    - 5. NSS software output : if use URT , only need NSS AFS of pin 
        //                               no to enable.
        //---------------------------------------------------------------------
        //Set : 
        //    - 1. MODE 
        //    - 2. line 
        //    - 3. Clock divider.
        // When data lines parameter error
        if(mSPI->Init.DataLine!=SPI_STANDARD_SPI)
        {
            return MID_ERROR;
        }

        CLEAR_BIT( mSPI->Instance->CR2.W , URT_CR2_NSS_SWEN_mask_w);                                                                                       // NSS output software control disable.
        //---------------------------------------------------------------------
        switch(mSPI->Init.Mode)
        {
            case SPI_MODE_MASTER:
            case SPI_MODE_MASTER_NSS:
                                     MODIFY_REG( mSPI->Instance->CR0.H[0] , uSPI_MODE_MASK , uSPI_MODE_MASTER_NSS);                                        // URT mode is SYNC master mode.
                                     WRITE_REG( mSPI->Instance->CLK.W, ( URT_CLK_CLK_EN_enable_w | URT_CLK_BR_EN_enable_w | URT_CLK_BR_MDS_combined_w));   // 1. Baud-rate clock source from CK_URT_PSC
                                                                                                                                                           // 2. Baud-rate generator mode is combined mode.
                                                                                                                                                           // 3. Baud-rate generator enable.
                                                                                                                                                           // 4. CLK signal output enable and CLK signal is SPICLK.
                                                                                                                                                           // 5. TX / RX clock source from baud-rate generator.
                                                                                                                                                           // 6. SPICLK output pin is URT_CLK.
            
                                     mSPI->Instance->CR1.B[1] = mSPI->Instance->CR1.B[3] = 1;                                                              // Set RX / TX baud-rate.
                                     mSPI->Instance->RLR.H[0] = (uint16_t) (( 1 << mSPI->Init.ClockDivider)-1);

                                     
                                     //---------------------------------------------------------------------
                                     //Set SPI MOSI idle status : 
                                     //    1. In MG32F02A132 , MG32F02A072 , MA862 , MG32F02A032
                                     //       MOSI status always H in in MOSI is idle status.
                                     #if (defined(MG32_3RD) || defined(MG32_4TH))
                                          MODIFY_REG( mSPI->Instance->CR2.W , (URT_CR2_DOUT_IDL_mask_w | URT_CR2_DOUT_MDS_mask_w) , ((mSPI->Init.IdleDataOut << 8) & (URT_CR2_DOUT_IDL_mask_w | URT_CR2_DOUT_MDS_mask_w)));
                                     #endif                             
                                     #if (defined(MG32_1ST) || defined(MG32_2ND))
                                         if(mSPI->Init.IdleDataOut != SPI_IDLE_DATA_OUT_DRIVING_1) 
                                         {
                                             return MID_ERROR;
                                         }
                                     #endif
                                     break;
            #if (defined(MG32_3RD) || defined(MG32_4TH))
            case SPI_MODE_SLAVE_NSS:
                                     MODIFY_REG( mSPI->Instance->CR0.H[0] , uSPI_MODE_MASK , uSPI_MODE_SLAVE_NSS);                                           //URT mode is SYNC slave mode. 
            
                                     WRITE_REG( mSPI->Instance->CLK.W, ( URT_CLK_CLK_EN_disable_w | URT_CLK_BR_EN_enable_w | URT_CLK_BR_MDS_combined_w |     //1. Baud-rate generator clock source form CK_URT_PSC
                                                                         URT_CLK_TX_CKS_ext_clk_w | URT_CLK_RX_CKS_ext_clk_w));                              //2. Baud-rate generator mode is combined mode.
                                                                                                                                                             //3. Baud-rate generator enable.
                                                                                                                                                             //4. CLK signal output disable
                                                                                                                                                             //5. TX / RX clock source form URT_CLK input.
                                                                                                                                                             //6. SPICLK input pin is URT_CLK.
            
                                     mSPI->Instance->CR1.B[1] = mSPI->Instance->CR1.B[3] = 2;                                                                //Set RX / TX baud-rate is CK_URT_PSC / 3
                                     mSPI->Instance->RLR.H[0] = 0;
            
                                     
                                     WRITE_REG( mSPI->Instance->CR2.W , URT_CR2_NSSI_EN_enable_w);                                                            //1. NSSI function enable.
                                                                                                                                                              //2. TX / RX disable.
                                     break;
            #endif
            default:
                                     return MID_ERROR;
        }
        
        //---------------------------------------------------------------------
        //CLKPolarity & CLKPhase
        MODIFY_REG( mSPI->Instance->CR3.W , (URT_CR3_CPOL_mask_w    | URT_CR3_CPHA_mask_w) , 
                                            (mSPI->Init.CLKPolarity | mSPI->Init.CLKPhase));
        //--------------------------------------------------------------------
        //Set : 
        //    - First bit.
        //    - Data size = 8bit.
        if(mSPI->Init.FirstBit==SPI_FIRSTBIT_MSB)
        {
            mSPI->Instance->CR1.B[0] = ( URT_CR1_RXDSIZE_8bit_b0 | URT_CR1_RXPAR_EN_disable_b0 | URT_CR1_RXMSB_EN_enable_b0 | URT_CR1_RXSTP_LEN_1bit_b0);
        }
        else
        {
            mSPI->Instance->CR1.B[0] = ( URT_CR1_RXDSIZE_8bit_b0 | URT_CR1_RXPAR_EN_disable_b0 | URT_CR1_RXMSB_EN_disable_b0 | URT_CR1_RXSTP_LEN_1bit_b0);
        }
        mSPI->Instance->CR1.B[2] = mSPI->Instance->CR1.B[0] ;
        //--------------------------------------------------------------------
        //Enable TX / RX
        SET_BIT(mSPI->Instance->CR2.W , (URT_CR2_RX_EN_mask_w | URT_CR2_TX_EN_mask_w));
        
        //--------------------------------------------------------------------
        /*Map flag and IRQ to URT.*/
        #if (defined(MG32_3RD) || defined(MG32_4TH))
            mSPI->SPI_FLAG_TUDRF = URT_STA_TUDRF_mask_w;
            mSPI->SPI_FLAG_ROVRF = URT_STA_ROVRF_mask_w;
            mSPI->SPI_FLAG_ERROR = (URT_STA_ROVRF_mask_w | URT_STA_TUDRF_mask_w | URT_STA_ERRF_mask_w);
        #else
            mSPI->SPI_FLAG_TUDRF = 0;
            mSPI->SPI_FLAG_ROVRF = 0;
            mSPI->SPI_FLAG_ERROR = 0;
        #endif
        mSPI->SPI_FLAG_IDLF  = 0;
        mSPI->SPI_FLAG_TCF   = URT_STA_TCF_mask_w;
        
        switch(index)
        {
            case MID_SPI_INDEX_URT0:
                                       mSPI->SPI_IRQ        = URT0_IRQn;
                                       break;
            case MID_SPI_INDEX_URT1:
            #if ( defined(MG32_1ST) | defined(MG32_3RD))
            case MID_SPI_INDEX_URT2:
            #endif
            #if defined(MG32_1ST)
            case MID_SPI_INDEX_URT3:                
            #endif
                                       mSPI->SPI_IRQ        = URT123_IRQn;
                                       break;
            default:
                                       return MID_ERROR;
        }

        //--------------------------------------------------------------------
        //RX shadow buffer level register define.
        mSPI->RX_TH    = &(mSPI->Instance->CR0.B[2]);
        mSPI->RXTX_LVL = &(mSPI->Instance->STA2.B[3]);
        mSPI->RXTX_CLR = &(mSPI->Instance->CR4.B[0]);
        mSPI->RNUM     = &(mSPI->Instance->CR4.B[1]);
        
        //=========================================================================
        // Pin Relationship Control
        MODIFY_REG( mSPI->Instance->CR0.W , URT_CR0_IO_SWP_mask_w , ((mSPI->Init.Swap << 1) & URT_CR0_IO_SWP_mask_w));
    }
    // When initial module is others
    else
    {
        return( MID_ERROR);
    }
    
    
    //=========================================================================
    // Enable NVIC of module
    NVIC_EnableIRQ((IRQn_Type) mSPI->SPI_IRQ);
    
    //=========================================================================
    // Update ErrorCode and module state
    mSPI->ErrorCode = MID_SPI_ERROR_NONE;
    mSPI->State     = MID_SPI_STATE_READY;
    
    //=========================================================================
    // Enable moudle
    SET_BIT( mSPI->Instance->CR0.W , SPI_CR0_EN_mask_w);
    
    return MID_OK;
}


/**
 *******************************************************************************
 * @brief       De-Initialize the SPI peripheral.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      MID status
 * @note
 * @par         Example
 * @code
    MID_SPI_DeInit(&mSPI0);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_SPI_DeInit(SPI_HandleTypeDef *mSPI)
{
    // Check the SPI handle allocation
    if (mSPI == NULL)
    {
        return MID_ERROR;
    }

    mSPI->State = MID_SPI_STATE_BUSY;

    // Disable the SPI/URTx Peripheral 
    __MID_SPI_DISABLE(mSPI);

    // DeInit the low level hardware: GPIO, CLOCK, NVIC... */
    MID_SPI_MspDeInit(mSPI);

    mSPI->ErrorCode = MID_SPI_ERROR_NONE;
    mSPI->State = MID_SPI_STATE_RESET;

    // Release Lock
    __MID_UNLOCK(mSPI);

    return MID_OK;
}


/**
 *******************************************************************************
 * @brief       Initialize the SPI MSP(MCU Support Package).
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      None
 * @note
 * @par         Example
 * @code
    MID_SPI_MspInit(&mSPI0);
 * @endcode
 *******************************************************************************
 */
__weak void MID_SPI_MspInit(SPI_HandleTypeDef *mSPI)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mSPI);

  /* NOTE : This function should not be modified, when the callback is needed,
            the MID_SPI_MspInit should be implemented in the user file
   */
  // Get CK_AHB clock frequency.
  SystemCoreClock = MID_CSC_GetCK_AHBFreq();
}


/**
 *******************************************************************************
 * @brief       De-Initialize the SPI MSP.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      None
 * @note
 * @par         Example
 * @code
    MID_SPI_MspDeInit(&mSPI0);
 * @endcode
 *******************************************************************************
 */
__weak void MID_SPI_MspDeInit(SPI_HandleTypeDef *mSPI)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mSPI);

  /* NOTE : This function should not be modified, when the callback is needed,
            the MID_SPI_MspDeInit should be implemented in the user file
   */
}
///@}


/**
 * @name    Initial/Deinitial TM with SPI_HandleTypeDef
 *
 */
///@{
/**
 *******************************************************************************
 * @brief       Transmit an amount of data in blocking mode.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @param[in]   pData pointer to data buffer
 * @param[in]   Size amount of data to be sent
 * @param[in]   Timeout Timeout duration
 * @return      MID status
 * @note
 * @par         Example
 * @code
    MID_SPI_Transmit(&mSPI0, &BUF8[0], 63, 0xf0000000);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_SPI_Transmit(SPI_HandleTypeDef *mSPI, uint8_t *pData, uint32_t Size, uint32_t Timeout)
{
    uint32_t    tickstart = 0U;
    MID_StatusTypeDef errorcode = MID_OK;
    PointStruct     Point;

    
    
    Point.ptr.point8 = pData;
    // In this case, 32-bit access is performed on data source, Chcek Data is 32-bit aligned addrees
    if ((mSPI->Init.DataSize > SPI_DATASIZE_16BIT) || 
        ((Size > 1U) && (mSPI->Init.DataSize > SPI_DATASIZE_8BIT) && (mSPI->Init.DataSize <= SPI_DATASIZE_16BIT)) ||
        ((Size > 3U) && (mSPI->Init.DataSize <= SPI_DATASIZE_8BIT)))
    {   // Check 32 bit access address aligned
        assert_param(IS_SPI_32BIT_ALIGNED_ADDRESS(Point.ptr.point8));
    }
    else
    {   // Check 16 bit access address aligned
        if((mSPI->Init.DataSize > SPI_DATASIZE_8BIT) || 
          ((Size > 1U) && (mSPI->Init.DataSize <= SPI_DATASIZE_8BIT)))
        {   // Check 16 bit access address aligned
            assert_param(IS_SPI_32BIT_ALIGNED_ADDRESS(Point.ptr.point8));
        }
    }

    // Process Locked
    __MID_LOCK(mSPI);

    // Init tickstart for timeout management
    tickstart = MID_GetTick();

    if (mSPI->State != MID_SPI_STATE_READY)
    {
        errorcode = MID_BUSY;
        goto error;
    }

    if ((Point.ptr.point8 == NULL) || (Size == 0U))
    {
        errorcode = MID_ERROR;
        goto error;
    }

    // Set the transaction information
    mSPI->State       = MID_SPI_STATE_BUSY_TX;
    mSPI->ErrorCode   = MID_SPI_ERROR_NONE;
    mSPI->pTxBuffPtr.point8  = Point.ptr.point8;
    mSPI->TxXferSize  = Size;
    mSPI->TxXferCount = Size;

    // Init field not used in handle to zero
    mSPI->pRxBuffPtr.point8  = (uint8_t *)NULL;
    mSPI->RxXferSize  = 0U;
    mSPI->RxXferCount = 0U;
    mSPI->TxISR       = NULL;
    mSPI->RxISR       = NULL;
    
    /* Disable all interrupt */
    mSPI->Instance->INT.W = 0;

    // Check if the SPI is already enabled
    if( (mSPI->Instance->CR0.W & SPI_CR0_EN_mask_w) == 0)
    {
        // Enable peripheral
        SET_BIT( mSPI->Instance->CR0.W , SPI_CR0_EN_mask_w);
    }

    /* Transmit data in 17 ~ 32 Bit mode */
    if(mSPI->Init.DataSize > SPI_DATASIZE_16BIT)
    {
        // When TxXferCount != 0
        if(mSPI->TxXferCount > 0x00U)
        {
            mSPI->Instance->TDAT.W = *(Point.ptr.point32++);
//            pData += sizeof(uint32_t);
            mSPI->TxXferCount--;
        }
        
        // Transmit data in 17 ~ 32 Bit mode
        while(mSPI->TxXferCount > 0U)
        {
            // Wait until TXE flag is set to send data
            if(( mSPI->Instance->STA.W & SPI_STA_TXF_mask_w)!=0)
            {
                mSPI->Instance->TDAT.W = *(Point.ptr.point32++);
                mSPI->TxXferCount--;
            }
            else
            {
                // Timeout management
                if ((Timeout == 0U) || ((Timeout != MID_MAX_DELAY) && ((MID_GetTick() - tickstart) >=  Timeout)))
                {
                    errorcode = MID_TIMEOUT;
                    goto error;
                }
            }
        }
    }
    /* Transmit data less 17 Bit mode */
    else
    {   /* Transmit data in 9 ~ 16 Bit mode */
        if(mSPI->Init.DataSize > SPI_DATASIZE_8BIT)
        {
            // When transmit > 1 
            if(mSPI->TxXferCount > 0x01U)
            {
                // Write on the data register in packing mode
                mSPI->Instance->TDAT.W = *(Point.ptr.point32++);
                // Address index +2
                // Sub TX counter
                mSPI->TxXferCount -= 0x02U;
            }
            // When transmit == 1
            else
            {
                // Write on the data register in packing mode
                mSPI->Instance->TDAT.H[0] = *(Point.ptr.point16++);
                // Address index +1
                // Sub TX counter
                mSPI->TxXferCount -= 0x01U;
            }
            
            // When transmit not complete
            while(mSPI->TxXferCount > 0x00U)
            {   // When TDAT empty
                if(( mSPI->Instance->STA.W & SPI_STA_TXF_mask_w)!=0)
                {   // When transmit 32 bit
                    if(mSPI->TxXferCount > 0x01U)
                    {
                        // Write on the data register in packing mode
                        mSPI->Instance->TDAT.W = *(Point.ptr.point32++);
                        // Address index +2
                        // Sub TX counter
                        mSPI->TxXferCount -= 0x02U;
                    }
                    // When transmit 16 bit
                    else
                    {
                        // Write on the data register in packing mode
                        mSPI->Instance->TDAT.H[0] = *(Point.ptr.point16++);
                        // Address index +1
                        // Sub TX counter
                        mSPI->TxXferCount -= 0x01U;
                    }
                }
                else
                {
                    // Timeout management
                    if ((Timeout == 0U) || ((Timeout != MID_MAX_DELAY) && ((MID_GetTick() - tickstart) >=  Timeout)))
                    {
                        errorcode = MID_TIMEOUT;
                        goto error;
                    }
                }
            }
        }
        
        /* Transmit data in 4 ~ 8 Bit mode */
        else
        {   // Transmit 4 bytes
            if(mSPI->TxXferCount > 0x03U)
            {
                // Write on the data register in packing mode
                mSPI->Instance->TDAT.W = *(Point.ptr.point32++);                
                // Address index +4
                // Sub TX counter
                mSPI->TxXferCount -= 0x04U;
            }
            // Transmit 2 bytes
            else if(mSPI->TxXferCount > 0x01U)
            {
                // Write on the data register in packing mode
                mSPI->Instance->TDAT.H[0] = *(Point.ptr.point16++);
                // Address index +2
                // Sub TX counter
                mSPI->TxXferCount -= 0x02U;
            }
            // Transmit 1 bytes
            else
            {
                // Write on the data register in packing mode
                mSPI->Instance->TDAT.B[0] = *(Point.ptr.point8++);
                // Address index +1
                // Sub TX counter
                mSPI->TxXferCount -= 0x01U;
            }
            // When transmit not complete
            while (mSPI->TxXferCount > 0U)
            {

                if(( mSPI->Instance->STA.W & SPI_STA_TXF_mask_w)!=0)
                {   // Transmit 4 bytes
                    if(mSPI->TxXferCount > 0x03U)
                    {
                        // Write on the data register in packing mode
                        mSPI->Instance->TDAT.W = *(Point.ptr.point32++);
                        // Address index +4
                        // Sub TX counter
                        mSPI->TxXferCount -= 0x04U;
                    }
                    // Transmit 2 bytes
                    else if(mSPI->TxXferCount > 0x01U)
                    {
                        // Write on the data register in packing mode
                        mSPI->Instance->TDAT.H[0] = *(Point.ptr.point16++);
                        // Address index +2
                        // Sub TX counter
                        mSPI->TxXferCount -= 0x02U;
                    }
                    // Transmit 1 bytes
                    else
                    {
                        // Write on the data register in packing mode
                        mSPI->Instance->TDAT.B[0] = *(Point.ptr.point8++);
                        // Address index +1
                        // Sub TX counter
                        mSPI->TxXferCount -= 0x01U;
                    }
                }
                else
                {
                    // Timeout management
                    if ((Timeout == 0U) || ((Timeout != MID_MAX_DELAY) && ((MID_GetTick() - tickstart) >=  Timeout)))
                    {
                        errorcode = MID_TIMEOUT;
                        goto error;
                    }
                }

            }
        }
    }

    /* Check the end of the transaction */
    if (SPI_EndRxTxTransaction(mSPI, Timeout, tickstart) != MID_OK)
    {
        mSPI->ErrorCode = MID_SPI_ERROR_FLAG;
    }

    /* Clear overrun flag in 2 Lines communication mode because received is not read */
    if (mSPI->Init.DataLine == SPI_STANDARD_SPI)
    {
        __MID_SPI_CLEAR_ROVRFFLAG(mSPI);
    }

    if (mSPI->ErrorCode != MID_SPI_ERROR_NONE)
    {
        errorcode = MID_ERROR;
    }

error:
    mSPI->State = MID_SPI_STATE_READY;
    /* Process Unlocked */
    __MID_UNLOCK(mSPI);
    return errorcode;
}


/**
 *******************************************************************************
 * @brief       Receive an amount of data in blocking mode.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @param[in]   pData pointer to data buffer
 * @param[in]   Size amount of data to be received
 * @param[in]   Timeout Timeout duration
 * @return      MID status
 * @note
 * @par         Example
 * @code
    MID_SPI_Receive(&mSPI0, &BUF8[0], 63, 0xf0000000);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_SPI_Receive(SPI_HandleTypeDef *mSPI, uint8_t *pData, uint32_t Size, uint32_t Timeout)
{
    uint32_t tickstart = 0U;
    MID_StatusTypeDef errorcode = MID_OK;
    PointStruct     Point;


    
    Point.ptr.point8 = pData;
    // In this case, 32-bit access is performed on data source, Chcek Data is 32-bit aligned addrees
    if ((mSPI->Init.DataSize > SPI_DATASIZE_16BIT) || 
        ((Size > 1U) && (mSPI->Init.DataSize > SPI_DATASIZE_8BIT) && (mSPI->Init.DataSize <= SPI_DATASIZE_16BIT)) ||
        ((Size > 3U) && (mSPI->Init.DataSize <= SPI_DATASIZE_8BIT)))
    {   // Check 32 bit access address aligned
        assert_param(IS_SPI_32BIT_ALIGNED_ADDRESS(Point.ptr.point8));
    }
    else
    {   // Check 16 bit access address aligned
        if((mSPI->Init.DataSize > SPI_DATASIZE_8BIT) || ((Size > 1U) && (mSPI->Init.DataSize <= SPI_DATASIZE_8BIT)))
        {   // Check 16 bit access address aligned

        }
    }
    
    // When SPI is master and stnadard SPI
    if(((mSPI->Init.Mode & SPI_MDS_MASK) == SPI_MDS_MASK) && (mSPI->Init.DataLine == SPI_STANDARD_SPI))
    { 
        /* Call transmit-receive function to send Dummy data on Tx line and generate clock on CLK line */
        return MID_SPI_TransmitReceive(mSPI, pData, pData, Size, Timeout);
    }

    /* Process Locked */
    __MID_LOCK(mSPI);

    /* Init tickstart for timeout management */
    tickstart = MID_GetTick();

    if(mSPI->State != MID_SPI_STATE_READY)
    {
        errorcode = MID_BUSY;
        goto error;
    }

    if((Point.ptr.point8 == NULL) || (Size == 0U))
    {
        errorcode = MID_ERROR;
        goto error;
    }

    /* Set the transaction information */
    mSPI->State       = MID_SPI_STATE_BUSY_RX;
    mSPI->ErrorCode   = MID_SPI_ERROR_NONE;
    mSPI->pRxBuffPtr.point8 = Point.ptr.point8;
    mSPI->RxXferSize  = Size;
    mSPI->RxXferCount = Size;

    /*Init field not used in handle to zero */
    mSPI->pTxBuffPtr.point8  = (uint8_t *)NULL;
    mSPI->TxXferSize  = 0U;
    mSPI->TxXferCount = 0U;
    mSPI->RxISR       = NULL;
    mSPI->TxISR       = NULL;

    // Check if the SPI is already enabled
    if( (mSPI->Instance->CR0.W & SPI_CR0_EN_mask_w) == 0)
    {
        // Enable SPI
        __MID_SPI_ENABLE(mSPI);
    }
    
    /* Set the Rx Fifo threshold */
    // Set RX_TH = 1 bytes
    *mSPI->RX_TH = 0;
    
    // Set RX_TH = 2 bytes, Data size = 9bit ~ 16bit
    if((mSPI->Init.DataSize > SPI_DATASIZE_8BIT) && (mSPI->Init.DataSize <= SPI_DATASIZE_16BIT)) 
    {
        *mSPI->RX_TH = 1;
    }

    // Set RX_TH = 3 bytes, Data size = 17bit ~ 24bit
    if((mSPI->Init.DataSize > SPI_DATASIZE_16BIT) && (mSPI->Init.DataSize <= SPI_DATASIZE_24BIT)) 
    {
        *mSPI->RX_TH = 2;
    }
    
    // Set RX_TH = 4 bytes, Data size = 25bit ~ 32bit
    if(mSPI->Init.DataSize > SPI_DATASIZE_24BIT)
    {
        *mSPI->RX_TH = 3;
    }

    // When data size 4 ~ 8 Bit 
    if(mSPI->Init.DataSize <= SPI_DATASIZE_8BIT)
    {                         
        // Transfer loop         
        while(mSPI->RxXferCount > 0U)
        {
            // Check the RXF flag
            if(__MID_SPI_GET_FLAG(mSPI, SPI_FLAG_RXF))
            {
                // read the received data
                (* Point.ptr.point8++) = *(__IO uint8_t *)&mSPI->Instance->RDAT.B[0];
                mSPI->RxXferCount--;
            }
            else
            {
                // Timeout management
                if((Timeout == 0U) || ((Timeout != MID_MAX_DELAY) && ((MID_GetTick() - tickstart) >=  Timeout)))
                {
                    errorcode = MID_TIMEOUT;
                    goto error;
                }
            }
        }
    }

    // Receive data in 9 ~ 16 Bit mode
    if((mSPI->Init.DataSize > SPI_DATASIZE_8BIT) && (mSPI->Init.DataSize <= SPI_DATASIZE_16BIT)) 
    {
        // Transfer loop
        while(mSPI->RxXferCount > 0U)
        {
            // Check the RXNE flag
            if(__MID_SPI_GET_FLAG(mSPI, SPI_FLAG_RXF))
            {
                *(Point.ptr.point16++) = mSPI->Instance->RDAT.H[0];
                mSPI->RxXferCount--;
            }
            else
            {
                // Timeout management
                if((Timeout == 0U) || ((Timeout != MID_MAX_DELAY) && ((MID_GetTick() - tickstart) >=  Timeout)))
                {
                    errorcode = MID_TIMEOUT;
                    goto error;
                }
            }
        }
    }
    
    // Receive data in 17 ~ 24 Bit mode
    if((mSPI->Init.DataSize > SPI_DATASIZE_16BIT) && (mSPI->Init.DataSize <= SPI_DATASIZE_24BIT)) 
    {
        // Transfer loop
        while(mSPI->RxXferCount > 0U)
        {
            // Check the RXNE flag
            if(__MID_SPI_GET_FLAG(mSPI, SPI_FLAG_RXF))
            {
                *(Point.ptr.point32++) = mSPI->Instance->RDAT.W;
                mSPI->RxXferCount--;
            }
            else
            {
                // Timeout management
                if((Timeout == 0U) || ((Timeout != MID_MAX_DELAY) && ((MID_GetTick() - tickstart) >=  Timeout)))
                {
                    errorcode = MID_TIMEOUT;
                    goto error;
                }
            }
        }
    }
    
    // Receive data in 25 ~ 32 Bit mode
    if(mSPI->Init.DataSize > SPI_DATASIZE_24BIT)
    {
        // Transfer loop
        while(mSPI->RxXferCount > 0U)
        {
            // Check the RXNE flag
            if(__MID_SPI_GET_FLAG(mSPI, SPI_FLAG_RXF))
            {
                *(Point.ptr.point32++) = mSPI->Instance->RDAT.W;
                mSPI->RxXferCount--;
            }
            else
            {
                // Timeout management
                if((Timeout == 0U) || ((Timeout != MID_MAX_DELAY) && ((MID_GetTick() - tickstart) >=  Timeout)))
                {
                    errorcode = MID_TIMEOUT;
                    goto error;
                }
            }
        }
    }
    
    /* Check the end of the transaction */
    if(SPI_EndRxTransaction(mSPI, Timeout, tickstart) != MID_OK)
    {
        mSPI->ErrorCode = MID_SPI_ERROR_FLAG;
    }

    // When SPI/URTx moudle error happened
    if(mSPI->ErrorCode != MID_SPI_ERROR_NONE)
    {
        errorcode = MID_ERROR;
    }

error :
    mSPI->State = MID_SPI_STATE_READY;
    __MID_UNLOCK(mSPI);
    return errorcode;
}


/**
 *******************************************************************************
 * @brief       Transmit and Receive an amount of data in blocking mode.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @param[in]   pTxData pointer to transmission data buffer
 * @param[in]   pRxData pointer to reception data buffer
 * @param[in]   Size amount of data to be sent and received
 * @param[in]   Timeout Timeout duration
 * @return      MID status
 * @note
 * @par         Example
 * @code
    return MID_SPI_TransmitReceive(mSPI, pData, pData, Size, Timeout);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_SPI_TransmitReceive(SPI_HandleTypeDef *mSPI, uint8_t *pTxData, uint8_t *pRxData, uint32_t Size, uint32_t Timeout)
{
    uint32_t tmp = 0U;
    uint32_t tickstart = 0U;
    uint32_t txallowed = 1U;                // Variable used to alternate Rx and Tx during transfer
    MID_StatusTypeDef errorcode = MID_OK;
    uint8_t  rxloadbyte;
    PointStruct     TX_Point;
    PointStruct     RX_Point;
    
    TX_Point.ptr.point8 = pTxData;
    RX_Point.ptr.point8 = pRxData;
    /* Check pRxData address match */
    // In this case, 32-bit access is performed on data source, Chcek Data is 32-bit aligned addrees
    if ((mSPI->Init.DataSize > SPI_DATASIZE_16BIT) || 
        ((Size > 1U) && (mSPI->Init.DataSize > SPI_DATASIZE_8BIT) && (mSPI->Init.DataSize <= SPI_DATASIZE_16BIT)) ||
        ((Size > 3U) && (mSPI->Init.DataSize <= SPI_DATASIZE_8BIT)))
    {   // Check 32 bit access address aligned
        assert_param(IS_SPI_32BIT_ALIGNED_ADDRESS(pData));
    }
    else
    {   // Check 16 bit access address aligned
        if((mSPI->Init.DataSize > SPI_DATASIZE_8BIT) || ((Size > 1U) && (mSPI->Init.DataSize <= SPI_DATASIZE_8BIT)))
        {   // Check 16 bit access address aligned
            assert_param(IS_SPI_16BIT_ALIGNED_ADDRESS(pData));
        }
    }

    /* Check Direction parameter */
    assert_param(IS_SPI_DATALINES_STANDARD_SPI(mSPI->Init.DataLine));

    /* Process Locked */
    __MID_LOCK(mSPI);

    /* Init tickstart for timeout management*/
    tickstart = MID_GetTick();

    tmp  = mSPI->State;

    if(!((tmp == MID_SPI_STATE_READY) || \
      (((mSPI->Init.Mode & SPI_MDS_MASK) != 0) && (mSPI->Init.DataLine == SPI_STANDARD_SPI) && (tmp == MID_SPI_STATE_BUSY_RX))))
    {
        errorcode = MID_BUSY;
        goto error;
    }

    if ((TX_Point.ptr.point8 == NULL) || (RX_Point.ptr.point8 == NULL) || (Size == 0U))
    {
        errorcode = MID_ERROR;
        goto error;
    }

    /* Don't overwrite in case of MID_SPI_STATE_BUSY_RX */
    if (mSPI->State != MID_SPI_STATE_BUSY_RX)
    {
        mSPI->State = MID_SPI_STATE_BUSY_TX_RX;
    }

    /* Set the transaction information */
    mSPI->ErrorCode   = MID_SPI_ERROR_NONE;
    mSPI->pRxBuffPtr.point8  = RX_Point.ptr.point8;
    mSPI->RxXferCount = Size;
    mSPI->RxXferSize  = Size;
    mSPI->pTxBuffPtr.point8  = TX_Point.ptr.point8;
    mSPI->TxXferCount = Size;
    mSPI->TxXferSize  = Size;

    /*Init field not used in handle to zero */
    mSPI->RxISR       = NULL;
    mSPI->TxISR       = NULL;

    /* Check if the SPI is already enabled */
    if((mSPI->Instance->CR0.W & SPI_CR0_EN_mask_w )== 0)
    {
        // Enable SPI peripheral
        __MID_SPI_ENABLE(mSPI);
    }
    
    /* Set the Rx Fifo threshold */
    // For slave mode RX_TH setting
    {
        // Set RX_TH = 1 bytes
        *mSPI->RX_TH = 0;

        // Set RX_TH = 2 bytes
        // Data size = 9bit ~ 16bit
        // Data size = 4bit ~ 8bit and RxXferCount > 1
        if(((mSPI->Init.DataSize > SPI_DATASIZE_8BIT) && (mSPI->Init.DataSize <= SPI_DATASIZE_16BIT)) || \
          ((mSPI->Init.DataSize <= SPI_DATASIZE_8BIT) && (mSPI->RxXferCount > 1U)))
        {
            
            *mSPI->RX_TH = 1;
        }
        
        // Set RX_TH = 3 bytes
        // Data size = 17bit ~ 24bit
        // Data size = 4bit ~ 8bit and RxXferCount > 2
        if(((mSPI->Init.DataSize > SPI_DATASIZE_16BIT) && (mSPI->Init.DataSize <= SPI_DATASIZE_24BIT)) || \
           ((mSPI->Init.DataSize <= SPI_DATASIZE_8BIT) && (mSPI->RxXferCount > 2U)))
        {
            *mSPI->RX_TH = 2;
        }
        
        // Set RX_TH = 4 bytes
        // Data size = 25bit ~ 32bit
        // Data size = 9bit ~ 16bit and RxXferCount > 1
        // Data size = 4bit ~ 8bit and RxXferCount > 3
        if((mSPI->Init.DataSize > SPI_DATASIZE_24BIT) || \
           ((mSPI->Init.DataSize > SPI_DATASIZE_8BIT) && (mSPI->Init.DataSize <= SPI_DATASIZE_16BIT) && (mSPI->RxXferCount > 2U)) || \
           ((mSPI->Init.DataSize <= SPI_DATASIZE_8BIT) && (mSPI->RxXferCount > 3U)))
        {
            *mSPI->RX_TH = 3;
        }
    }

    /* Transmit and Receive data in 17 ~ 32 Bit mode */
    if (mSPI->Init.DataSize > SPI_DATASIZE_16BIT)
    {
        if(mSPI->Instance != NULL)
        {
            mSPI->Instance->TDAT.W = *(TX_Point.ptr.point32++);
//            pTxData += sizeof(uint32_t);
            mSPI->TxXferCount --;
        }
        /* Next Data is a Transmission (Tx). Tx is allowed */
        txallowed = 1;
        
        while ((mSPI->TxXferCount > 0U) || (mSPI->RxXferCount > 0U))
        {
            // Check TXF flag. When transmit count >0 and TX buffer empty
            if (txallowed && (mSPI->TxXferCount > 0U) && (__MID_SPI_GET_FLAG(mSPI, SPI_FLAG_TXF)))
            {
                mSPI->Instance->TDAT.W = *(TX_Point.ptr.point32++);
                mSPI->TxXferCount--;
                
                /* Next Data is a reception (Rx). Tx not allowed */
                txallowed = 0U;
            }
            
            // Check RXF flag. When receive count > 0 and RX buffer not empty 
            if ((mSPI->RxXferCount > 0U) && (__MID_SPI_GET_FLAG(mSPI, SPI_FLAG_RXF)))
            {
                *(RX_Point.ptr.point32++) = mSPI->Instance->RDAT.W;
                mSPI->RxXferCount--;
                
                /* Next Data is a Transmission (Tx). Tx is allowed */
                txallowed = 1U;
            }
            
            // Check not timeout
            if ((Timeout != MID_MAX_DELAY) && ((MID_GetTick() - tickstart) >=  Timeout))
            {
                errorcode = MID_TIMEOUT;
                goto error;
            }
        }
    }
    
    /* Transmit and Receive data in 8 ~ 16 Bit mode */
    else 
    {
        if (mSPI->Init.DataSize > SPI_DATASIZE_8BIT)
        {
            if(mSPI->TxXferCount != 0x00U)
            {
                // When data length > 1
                if(mSPI->TxXferCount > 0x01U)
                {
                    mSPI->Instance->TDAT.W = *(TX_Point.ptr.point32++);
                    mSPI->TxXferCount -= 2U;
                    
                }
                // When data length <= 1
                else
                {
                    mSPI->Instance->TDAT.H[0] = *(TX_Point.ptr.point16++);
                    mSPI->TxXferCount--;
                }
                /* Next Data is a Transmission (Tx). Tx is allowed */
                txallowed = 1;
            }
            
            // When transmit completet or receive complete
            while ((mSPI->TxXferCount > 0U) || (mSPI->RxXferCount > 0U))
            {
                // Check TXF flag. When transmit count >0 and TX buffer empty
                if (txallowed && (mSPI->TxXferCount > 0U) && (__MID_SPI_GET_FLAG(mSPI, SPI_FLAG_TXF)))
                {
                    // When data length > 1
                    if(mSPI->TxXferCount > 0x01U)
                    {
                        mSPI->Instance->TDAT.W = *(TX_Point.ptr.point32++);
                        mSPI->TxXferCount -= 2U;
                    }
                    // When data length <= 1
                    else
                    {
                        mSPI->Instance->TDAT.H[0] = *(TX_Point.ptr.point16++);
                        mSPI->TxXferCount--;
                    }
                    /* Next Data is a reception (Rx). Tx not allowed */
                    txallowed = 0U;
                }

                // Check RXF flag. When receive count > 0 and RX buffer not empty 
                if ((mSPI->RxXferCount > 0U) && (__MID_SPI_GET_FLAG(mSPI, SPI_FLAG_RXF)))
                {  
                    rxloadbyte = (*mSPI->RNUM) & SPI_STA_RNUM_mask_b3;
                    
                    // When data length > 1
                    if( rxloadbyte == 4)
                    {
                        *(RX_Point.ptr.point32++) = mSPI->Instance->RDAT.W;
                        mSPI->RxXferCount -= 2U;
                    }
                    // When data length <= 1
                    else
                    {
                        *(RX_Point.ptr.point16++) = mSPI->Instance->RDAT.H[0];
                        mSPI->RxXferCount--;
                    }
                    
                    /* Next Data is a Transmission (Tx). Tx is allowed */
                    txallowed = 1U;
                }
                
                if ((Timeout != MID_MAX_DELAY) && ((MID_GetTick() - tickstart) >=  Timeout))
                {
                    errorcode = MID_TIMEOUT;
                    goto error;
                }
            }
        }
        /* Transmit and Receive data in 4 ~ 8 Bit mode */
        else
        {
            // When TX trasmitdata not empty
            if (mSPI->TxXferCount != 0x00U)
            {   
                // When TX buffer count > 3
                if (mSPI->TxXferCount > 3U)
                {
                    mSPI->Instance->TDAT.W = *(TX_Point.ptr.point32++);
                    mSPI->TxXferCount -= 4U;
                }
                
                // When TX buffer count > 1
                else if (mSPI->TxXferCount > 1U)
                {
                    mSPI->Instance->TDAT.H[0] = *(TX_Point.ptr.point16++);
                    mSPI->TxXferCount -= 2U;
                }
                
                // When TX buffer count == 1
                else
                {
                    *(__IO uint8_t *)&mSPI->Instance->TDAT.B[0] = (*TX_Point.ptr.point8++);
                    mSPI->TxXferCount--;
                }
                /* Next Data is a Transmission (Tx). Tx is allowed */
                txallowed = 1;
            }
            
            // When trasmitdata data not empty > 0 or receive data not empty
            while ((mSPI->TxXferCount > 0U) || (mSPI->RxXferCount > 0U))
            {
                // Check TXF flag. When transmit count >0 and TX buffer empty
                if(txallowed && (mSPI->TxXferCount > 0U) && (__MID_SPI_GET_FLAG(mSPI, SPI_FLAG_TXF)))
                {
                    // When TX data count > 3
                    if (mSPI->TxXferCount > 3U)
                    {
                        mSPI->Instance->TDAT.W = *(TX_Point.ptr.point32++);
                        mSPI->TxXferCount -= 4U;
                    }
                    else
                    {   
                        // When TX data count > 1
                        if (mSPI->TxXferCount > 1U)
                        {
                            mSPI->Instance->TDAT.H[0] = *(TX_Point.ptr.point16++);
                            mSPI->TxXferCount -= 2U;
                        }
                        
                        // When TX data count > 0
                        else
                        {
                            *(__IO uint8_t *)&mSPI->Instance->TDAT.B[0] = (*TX_Point.ptr.point8++);
                            mSPI->TxXferCount--;
                        }
                    }

                    /* Next Data is a reception (Rx). Tx not allowed */
                    txallowed = 0U;
                }

                // When RX buffer count > 0 and RDAT not empty
                if((mSPI->RxXferCount > 0U) && (__MID_SPI_GET_FLAG(mSPI, SPI_FLAG_RXF)))
                {   
                    rxloadbyte = (*mSPI->RNUM) & SPI_STA_RNUM_mask_b3;
                    
                    if( rxloadbyte == 4U)
                    {
                        *(RX_Point.ptr.point32) = mSPI->Instance->RDAT.W;       
                    }
                    else if( rxloadbyte == 3u)
                    {
                        tmp = mSPI->Instance->RDAT.W;
                        
                        *(RX_Point.ptr.point8)        = (uint8_t)tmp;
                        *(RX_Point.ptr.point8 + 1)  = (uint8_t)(tmp>>8);
                        *(RX_Point.ptr.point8 + 2)  = (uint8_t)(tmp>>16);
                    }
                    else if( rxloadbyte == 2U)
                    {
                        *(RX_Point.ptr.point16) = mSPI->Instance->RDAT.H[0];
                    }
                    else
                    {
                        *(RX_Point.ptr.point8) =  mSPI->Instance->RDAT.B[0];
                    }
                    
                    RX_Point.ptr.point8           += rxloadbyte;
                    mSPI->RxXferCount -= rxloadbyte;
                        
                    if( mSPI->RxXferCount!= 0 && mSPI->RxXferCount < 4U && mSPI->REG_TYPE == MID_SPI_SPI)
                    {
                        *mSPI->RX_TH = ((mSPI->RxXferCount - 1) & SPI_CR2_RX_TH_mask_b1);
                    }
                    
                    /* Next Data is a Transmission (Tx). Tx is allowed */
                    txallowed = 1U;
                }
                
                if ((Timeout != MID_MAX_DELAY) && ((MID_GetTick() - tickstart) >=  Timeout))
                {
                    errorcode = MID_TIMEOUT;
                    goto error;
                }
            }
        }
    }
    
    /* Check the end of the transaction */
    if (SPI_EndRxTxTransaction(mSPI, Timeout, tickstart) != MID_OK)
    {
        mSPI->ErrorCode = MID_SPI_ERROR_FLAG;
    }

    // When SPI/URTx moudle error happened
    if (mSPI->ErrorCode != MID_SPI_ERROR_NONE)
    {
        errorcode = MID_ERROR;
    }

error :
    mSPI->State = MID_SPI_STATE_READY;
    __MID_UNLOCK(mSPI);
    return errorcode;
}


/**
 *******************************************************************************
 * @brief       Transmit an amount of data in non-blocking mode with Interrupt.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @param[in]   pData pointer to data buffer
 * @param[in]   Size amount of data to be sent
 * @return      MID status
 * @note
 * @par         Example
 * @code
    MID_SPI_Transmit_IT (&mSPI0, &BUF8[0], 63);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_SPI_Transmit_IT(SPI_HandleTypeDef *mSPI, uint8_t *pData, uint32_t Size)
{
    MID_StatusTypeDef errorcode = MID_OK;

    
    // In this case, 32-bit access is performed on data source, Chcek Data is 32-bit aligned addrees
    if ((mSPI->Init.DataSize > SPI_DATASIZE_16BIT) || 
        ((Size > 1U) && (mSPI->Init.DataSize > SPI_DATASIZE_8BIT) && (mSPI->Init.DataSize <= SPI_DATASIZE_16BIT)) ||
        ((Size > 3U) && (mSPI->Init.DataSize <= SPI_DATASIZE_8BIT)))
    {   // Check 32 bit access address aligned
        assert_param(IS_SPI_32BIT_ALIGNED_ADDRESS(pTxData));
    }
    else
    {   // Check 16 bit access address aligned
        if((mSPI->Init.DataSize > SPI_DATASIZE_8BIT) || ((Size > 1U) && (mSPI->Init.DataSize <= SPI_DATASIZE_8BIT)))
        {   // Check 16 bit access address aligned
            assert_param(IS_SPI_16BIT_ALIGNED_ADDRESS(pTxData));
        }
    }

    /* Process Locked */
    __MID_LOCK(mSPI);

    // When transfer data not index or SPI data size is 0 bytes
    if ((pData == NULL) || (Size == 0U))
    {
        errorcode = MID_ERROR;
        goto error;
    }

    if (mSPI->State != MID_SPI_STATE_READY)
    {
        errorcode = MID_BUSY;
        goto error;
    }

    /* Set the transaction information */
    mSPI->State             = MID_SPI_STATE_BUSY_TX;
    mSPI->ErrorCode         = MID_SPI_ERROR_NONE;
    mSPI->pTxBuffPtr.point8 = (uint8_t *)pData;
    mSPI->TxXferSize        = Size;
    mSPI->TxXferCount       = Size;

    /* Init field not used in handle to zero */
    mSPI->pRxBuffPtr.point8 = (uint8_t *)NULL;
    mSPI->RxXferSize        = 0U;
    mSPI->RxXferCount       = 0U;
    mSPI->RxISR             = NULL;

    /* Set the function for IT treatment */
    // When data sizes > 16 bit
    if(mSPI->Init.DataSize > SPI_DATASIZE_16BIT)
    {
        mSPI->TxISR = SPI_TxISR_32BIT;
    }
    else
    {   // When data sizes > 8 bit
        if(mSPI->Init.DataSize > SPI_DATASIZE_8BIT)
        {
            mSPI->TxISR = SPI_TxISR_16BIT;
        }
        // When data sizes <= 8 bit
        else
        {
            mSPI->TxISR = SPI_TxISR_8BIT;
        }
    }

    /* Check if the SPI is already enabled */
    if((mSPI->Instance->CR0.W & SPI_CR0_EN_mask_w )== 0)
    {
        // Enable SPI peripheral
        __MID_SPI_ENABLE(mSPI);
    }
    
    
    /* Enable TXE and ERR interrupt */
#if (defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH))
    mSPI->TxRxStartEvent = 1;
#endif
    __MID_SPI_CLEAR_TXDATA(mSPI);
    __MID_SPI_ENABLE_IT(mSPI, (SPI_IT_TXF | mSPI->SPI_FLAG_TUDRF | SPI_IT_MODF | SPI_IT_WEF | SPI_IT_IEA));

    // Trigger SPI intterupt
#if (defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH))
    if(mSPI->REG_TYPE == MID_SPI_SPI)
        __NVIC_SetPendingIRQ((IRQn_Type) mSPI->SPI_IRQ);
#endif
    
error :
    __MID_UNLOCK(mSPI);
    return errorcode;
}


/**
 *******************************************************************************
 * @brief       Receive an amount of data in non-blocking mode with Interrupt.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @param[in]   pData pointer to data buffer
 * @param[in]   Size amount of data to be received
 * @return      MID status
 * @note
 * @par         Example
 * @code
    MID_SPI_Receive_IT (&mSPI0, &BUF8[0], 63);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_SPI_Receive_IT(SPI_HandleTypeDef *mSPI, uint8_t *pData, uint32_t Size)
{
    MID_StatusTypeDef errorcode = MID_OK;



    // In this case, 32-bit access is performed on data source, Chcek Data is 32-bit aligned addrees
    if ((mSPI->Init.DataSize > SPI_DATASIZE_16BIT) || 
        ((Size > 1U) && (mSPI->Init.DataSize > SPI_DATASIZE_8BIT) && (mSPI->Init.DataSize <= SPI_DATASIZE_16BIT)) ||
        ((Size > 3U) && (mSPI->Init.DataSize <= SPI_DATASIZE_8BIT)))
    {   // Check 32 bit access address aligned
        assert_param(IS_SPI_32BIT_ALIGNED_ADDRESS(pRxData));
    }
    else
    {   // Check 16 bit access address aligned
        if((mSPI->Init.DataSize > SPI_DATASIZE_8BIT) || ((Size > 1U) && (mSPI->Init.DataSize <= SPI_DATASIZE_8BIT)))
        {   // Check 16 bit access address aligned
            assert_param(IS_SPI_16BIT_ALIGNED_ADDRESS(pRxData));
        }
    }

    // When data line is standard SPI and master 
    if ((mSPI->Init.DataLine == SPI_STANDARD_SPI) && ((mSPI->Init.Mode & SPI_MDS_MASK) != 0))
    {
        mSPI->State = MID_SPI_STATE_BUSY_RX;
        /* Call transmit-receive function to send Dummy data on Tx line and generate clock on CLK line */
        return MID_SPI_TransmitReceive_IT(mSPI, pData, pData, Size);
    }

    /* Process Locked */
    __MID_LOCK(mSPI);

    if (mSPI->State != MID_SPI_STATE_READY)
    {
        errorcode = MID_BUSY;
        goto error;
    }

    if ((pData == NULL) || (Size == 0U))
    {
        errorcode = MID_ERROR;
        goto error;
    }

    /* Set the transaction information */
    mSPI->State       = MID_SPI_STATE_BUSY_RX;
    mSPI->ErrorCode   = MID_SPI_ERROR_NONE;
    mSPI->pRxBuffPtr.point8  = (uint8_t *)pData;
    mSPI->RxXferSize  = Size;
    mSPI->RxXferCount = Size;

    /* Init field not used in handle to zero */
    mSPI->pTxBuffPtr.point8  = (uint8_t *)NULL;
    mSPI->TxXferSize  = 0U;
    mSPI->TxXferCount = 0U;
    mSPI->TxISR       = NULL;

    /* Note : The SPI must be enabled after unlocking current process
              to avoid the risk of SPI interrupt handle execution before current
              process unlock */

    /* Check if the SPI is already enabled */
    if((mSPI->Instance->CR0.W & SPI_CR0_EN_mask_w)==0)
    {
        /* Enable SPI peripheral */
        __MID_SPI_ENABLE(mSPI);
    }
    
    /* Check the data size to adapt Rx threshold and the set the function for IT treatment */
    // For slave mode RX_TH setting
    {
    // Set Data size <= 8bit
    if(mSPI->Init.DataSize <= SPI_DATASIZE_8BIT)
    {
        // Set IT RX 
        mSPI->RxISR = SPI_RxISR_8BIT;
        if(Size >= 4) 
            *mSPI->RX_TH = 3;
        else 
            *mSPI->RX_TH = (uint8_t) Size - 1;
    }

    // Set Data size = 9bit ~ 16bit
    else if(mSPI->Init.DataSize <= SPI_DATASIZE_16BIT)
    {
        // Set IT RX
        mSPI->RxISR = SPI_RxISR_16BIT;
        if(Size >= 2)
            *mSPI->RX_TH = 3;
        else
            *mSPI->RX_TH = 1;
    }

    // Set Data size = 17bit ~ 24bit 
    else if(mSPI->Init.DataSize <= SPI_DATASIZE_24BIT) 
    {
        *mSPI->RX_TH = 2;
        mSPI->RxISR = SPI_RxISR_32BIT;
    }

    // Set Data size = 25bit ~ 32bit 
    else if(mSPI->Init.DataSize > SPI_DATASIZE_24BIT) 
    {
        *mSPI->RX_TH = 3;
        mSPI->RxISR = SPI_RxISR_32BIT;
    }
    }

    /* Enable TXE and ERR interrupt */
    // When module is master mode
    if((mSPI->Init.Mode & SPI_MDS_MASK)!=0)
        __MID_SPI_ENABLE_IT(mSPI, (SPI_IT_RXF | mSPI->SPI_FLAG_ERROR | SPI_IT_IEA));
    // When module is slave mode
    else 
        __MID_SPI_ENABLE_IT(mSPI, (SPI_IT_RXF | SPI_IT_MODF | SPI_IT_WEF | mSPI->SPI_FLAG_ROVRF | SPI_IT_IEA));

    SPI0->CR1.MBIT.RDAT_CLR = 1;
    SPI0->CR1.MBIT.TDAT_CLR = 1;

error :
    /* Process Unlocked */
    __MID_UNLOCK(mSPI);
    return errorcode;
}


/**
 *******************************************************************************
 * @brief       Transmit and Receive an amount of data in non-blocking mode with Interrupt.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @param[in]   pTxData pointer to transmission data buffer
 * @param[in]   pRxData pointer to reception data buffer
 * @param[in]   Size amount of data to be sent and received
 * @return      MID status
 * @note
 * @par         Example
 * @code
    MID_SPI_TransmitReceive_IT(&mSPI0, &BUF8[0], &BUF8[0], 63);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_SPI_TransmitReceive_IT(SPI_HandleTypeDef *mSPI, uint8_t *pTxData, uint8_t *pRxData, uint32_t Size)
{
//    uint32_t tmp = 0U;
    MID_StatusTypeDef errorcode = MID_OK;



    // In this case, 32-bit access is performed on data source, Chcek Data is 32-bit aligned addrees
    if ((mSPI->Init.DataSize > SPI_DATASIZE_16BIT) || 
        ((Size > 1U) && (mSPI->Init.DataSize > SPI_DATASIZE_8BIT) && (mSPI->Init.DataSize <= SPI_DATASIZE_16BIT)) ||
        ((Size > 3U) && (mSPI->Init.DataSize <= SPI_DATASIZE_8BIT)))
    {   // Check 32 bit access address aligned
        assert_param(IS_SPI_32BIT_ALIGNED_ADDRESS(pTxData));
        assert_param(IS_SPI_32BIT_ALIGNED_ADDRESS(pRxData));
    }
    else
    {   // Check 16 bit access address aligned
        if((mSPI->Init.DataSize > SPI_DATASIZE_8BIT) || ((Size > 1U) && (mSPI->Init.DataSize <= SPI_DATASIZE_8BIT)))
        {   // Check 16 bit access address aligned
            assert_param(IS_SPI_16BIT_ALIGNED_ADDRESS(pTxData));
            assert_param(IS_SPI_16BIT_ALIGNED_ADDRESS(pRxData));
        }
    }

    /* Check Direction parameter */
    assert_param(IS_SPI_DIRECTION_2LINES(mSPI->Init.Direction));

    /* Process locked */
    __MID_LOCK(mSPI);

//    tmp  = mSPI->State;

    if ((pTxData == NULL) || (pRxData == NULL) || (Size == 0U))
    {
        errorcode = MID_ERROR;
        goto error;
    }

    /* Don't overwrite in case of MID_SPI_STATE_BUSY_RX */
    if (mSPI->State != MID_SPI_STATE_BUSY_RX)
    {
        mSPI->State = MID_SPI_STATE_BUSY_TX_RX;
    }

    /* Set the transaction information */
    mSPI->ErrorCode   = MID_SPI_ERROR_NONE;
    mSPI->pTxBuffPtr.point8  = (uint8_t *)pTxData;
    mSPI->TxXferSize  = Size;
    mSPI->TxXferCount = Size;
    mSPI->pRxBuffPtr.point8  = (uint8_t *)pRxData;
    mSPI->RxXferSize  = Size;
    mSPI->RxXferCount = Size;

    /* Check if the SPI is already enabled */
    if((mSPI->Instance->CR0.W & SPI_CR0_EN_mask_w)==0)
    {
        /* Enable SPI peripheral */
        __MID_SPI_ENABLE(mSPI);
    }

    /* Set the function for IT treatment */
    // When data size > 16bit
    if (mSPI->Init.DataSize > SPI_DATASIZE_16BIT)
    {
        mSPI->RxISR     = SPI_2linesRxISR_32BIT;
        mSPI->TxISR     = SPI_2linesTxISR_32BIT;
    }
    else
    {   // When data size <= 16bit and data size > 8bit 
        if(mSPI->Init.DataSize > SPI_DATASIZE_8BIT)
        {
            mSPI->RxISR     = SPI_2linesRxISR_16BIT;
            mSPI->TxISR     = SPI_2linesTxISR_16BIT;
        }
        // When data size <= 8bit
        else
        {
            mSPI->RxISR     = SPI_2linesRxISR_8BIT;
            mSPI->TxISR     = SPI_2linesTxISR_8BIT;
        }
    }


    /* Set the Rx Fifo threshold */
    // For slave mode RX_TH setting
    
    // Set RX_TH = 1 bytes
    *mSPI->RX_TH = 0;
        
    // Set RX_TH = 2 bytes
    // Data size = 9bit ~ 16bit
    // Data size = 4bit ~ 8bit and RxXferCount > 1
    if(((mSPI->Init.DataSize > SPI_DATASIZE_8BIT) && (mSPI->Init.DataSize <= SPI_DATASIZE_16BIT)) || \
      ((mSPI->Init.DataSize <= SPI_DATASIZE_8BIT) && (mSPI->RxXferCount > 1U)))
    {
        *mSPI->RX_TH = 1;
    }

    // Set RX_TH = 3 bytes
    // Data size = 17bit ~ 24bit
    // Data size = 4bit ~ 8bit and RxXferCount > 2
    if(((mSPI->Init.DataSize > SPI_DATASIZE_16BIT) && (mSPI->Init.DataSize <= SPI_DATASIZE_24BIT)) || \
       ((mSPI->Init.DataSize <= SPI_DATASIZE_8BIT) && (mSPI->RxXferCount > 2U)))
    {
        *mSPI->RX_TH = 2;
    }

    // Set RX_TH = 4 bytes
    // Data size = 25bit ~ 32bit
    // Data size = 9bit ~ 16bit and RxXferCount > 1
    // Data size = 4bit ~ 8bit and RxXferCount > 3
    if((mSPI->Init.DataSize > SPI_DATASIZE_24BIT) || \
       ((mSPI->Init.DataSize > SPI_DATASIZE_8BIT) && (mSPI->Init.DataSize <= SPI_DATASIZE_16BIT) && (mSPI->RxXferCount > 2U)) || \
       ((mSPI->Init.DataSize <= SPI_DATASIZE_8BIT) && (mSPI->RxXferCount > 3U)))
    {
        *mSPI->RX_TH = 3;
    }
    


    /* Enable TXE, RXNE and ERR interrupt */
    mSPI->TxRxStartEvent = 1;
    __MID_SPI_CLEAR_RXTXDATA(mSPI);
    __MID_SPI_ENABLE_IT(mSPI, (SPI_IT_TXF | mSPI->SPI_FLAG_TCF | SPI_IT_RXF | mSPI->SPI_FLAG_ERROR | SPI_IT_IEA));

    // Trigger SPI intterupt
#if (defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH))
    if(mSPI->REG_TYPE == MID_SPI_SPI)
        __NVIC_SetPendingIRQ((IRQn_Type) mSPI->SPI_IRQ);
#endif

error :
    /* Process Unlocked */
    __MID_UNLOCK(mSPI);
    return errorcode;
}


/**
 *******************************************************************************
 * @brief       Transmit an amount of data in non-blocking mode with DMA.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @param[in]   pData pointer to data buffer
 * @param[in]   Size amount of data to be sent
 * @return      MID status
 * @note
 * @par         Example
 * @code
    MID_SPI_Transmit_DMA(&uSPI0, &TST_TXData_Table[0] , 48);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_SPI_Transmit_DMA(SPI_HandleTypeDef *mSPI,  uint8_t *pData, uint32_t Size)
{ 
    // When DMA is ready
    if(mSPI->State == MID_SPI_STATE_READY)
    {
        // When parameter "pData" and Size not zero.
        if((pData == NULL) || (Size == 0U))
        {
            return(MID_ERROR);
        }
        
        //Process Locked 
        __MID_LOCK(mSPI);
        
        // Change DMA peripheral state
        mSPI->pTxBuffPtr.point8 = pData;
        mSPI->TxXferSize = Size;
        mSPI->TxXferCount = Size;
        
        mSPI->ErrorCode = MID_SPI_ERROR_NONE;
        mSPI->State = MID_SPI_STATE_BUSY_TX;
        
        //Set the mSPI DMA transfer complete callback.
        mSPI->mDMATX->XferCpltCallback = SPI_DMATransmitCplt;
        
        //Set the UART DMA Half transfer complete callback
        mSPI->mDMATX->XferHalfCpltCallback = SPI_DMAHalfTransmitCplt;
        
        //Set the DMA error callback 
        mSPI->mDMATX->XferErrorCallback = SPI_DMAError;
        
        //Set the DMA abort callback
        mSPI->mDMATX->XferAbortCallback = NULL;

        /* Configure the source, destination address and the data length */
        if(mSPI->REG_TYPE == MID_SPI_SPI)
        {
            mSPI->Instance->CR0.B[3] |= SPI_CR0_DMA_TXEN_mask_b3;
        }
        else
        {
            mSPI->Instance->CR2.B[0] &= (~URT_CR2_TX_EN_mask_b0);
            mSPI->Instance->CR0.B[3] |= SPI_CR0_DMA_TXEN_mask_b3;
            mSPI->Instance->CR2.B[0] |= URT_CR2_TX_EN_mask_b0;
        }

        MID_DMA_Start_IT(mSPI->mDMATX, (uint32_t) mSPI->pTxBuffPtr.point8, (uint32_t)&mSPI->Instance->TDAT.W, Size);

        return(MID_BUSY);
    }
    else
    {
        /* Remain BUSY */
        return(MID_BUSY);
    }  
}


/**
 *******************************************************************************
 * @brief       Receive an amount of data in non-blocking mode with DMA.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @param[in]   pData pointer to data buffer
 * @param[in]   Size amount of data to be sent
 * @return      MID status
 * @note
 * @par         Example
 * @code
    MID_SPI_Receive_DMA(&uSPI0, &TST_RXData_Table[0] , 48);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_SPI_Receive_DMA(SPI_HandleTypeDef *mSPI, uint8_t *pData, uint32_t Size)
{
    // When DMA is ready
    if(mSPI->State == MID_SPI_STATE_READY)
    {
        if((pData == NULL) || (Size == 0U))
        {
            return(MID_ERROR);
        }
        
        //Process Locked 
        __MID_LOCK(mSPI);
        
        // Change DMA peripheral state
        mSPI->pRxBuffPtr.point8 = pData;
        mSPI->RxXferSize = Size;
        mSPI->RxXferCount = Size;
        
        mSPI->ErrorCode = MID_SPI_ERROR_NONE;
        mSPI->State = MID_SPI_STATE_BUSY_RX;
        
        //Set the mSPI DMA transfer complete callback.
        mSPI->mDMARX->XferCpltCallback = SPI_DMAReceiveCplt;
        
        //Set the UART DMA Half transfer complete callback
        mSPI->mDMARX->XferHalfCpltCallback = SPI_DMAHalfReceiveCplt;
        
        //Set the DMA error callback 
        mSPI->mDMARX->XferErrorCallback = SPI_DMAError;
        
        //Set the DMA abort callback
        mSPI->mDMARX->XferAbortCallback = NULL;
                                                                            
        /* Configure the source, destination address and the data length */
        MID_DMA_Start_IT(mSPI->mDMARX, (uint32_t)&mSPI->Instance->RDAT.W, (uint32_t) mSPI->pRxBuffPtr.point8, Size);
        
        if(mSPI->REG_TYPE == MID_SPI_SPI)
        {
            mSPI->Instance->CR0.B[3] |= SPI_CR0_DMA_RXEN_mask_b3;
        }
        else
        {
            mSPI->Instance->CR2.B[0] &=(~(URT_CR2_RX_EN_mask_b0 | URT_CR2_TX_EN_mask_b0));
            mSPI->Instance->CR0.B[3] |= SPI_CR0_DMA_RXEN_mask_b3;
            mSPI->Instance->CR2.B[0] |= (URT_CR2_RX_EN_mask_b0 | URT_CR2_TX_EN_mask_b0);
        }
        
        return(MID_BUSY);
    }
    else
    {
        /* Remain BUSY */
        return(MID_BUSY);
    }
}


/**
 *******************************************************************************
 * @brief       Transmit and Receive an amount of data in non-blocking mode with DMA.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @param[in]   pTxData pointer to TX data buffer
 * @param[in]   pRxData pointer to RX data buffer
 * @param[in]   Size amount of data to be sent
 * @return      MID status
 * @note
 * @par         Example
 * @code
    MID_SPI_TransmitReceive_DMA(&uSPI0, &TST_TXData_Table[0], &TST_RXData_Table[0] , 48);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *mSPI, uint8_t *pTxData, uint8_t *pRxData,
                                              uint32_t Size)
{
    // When DMA is ready
    if(mSPI->State == MID_SPI_STATE_READY)
    {
        // When parameter "pTxData", "pRxData" and Size not zero.
        if((pTxData == NULL) || (pRxData == NULL) || (Size == 0U))
        {
            return(MID_ERROR);
        }
        
        //Process Locked 
        __MID_LOCK(mSPI);
        
        // Change DMA peripheral state
        mSPI->pRxBuffPtr.point8 = pRxData;
        mSPI->RxXferSize = Size;
        mSPI->RxXferCount = Size;
        
        mSPI->pTxBuffPtr.point8 = pTxData;
        mSPI->TxXferSize = Size;
        mSPI->TxXferCount = Size;
        
        mSPI->ErrorCode = MID_SPI_ERROR_NONE;
        mSPI->State = MID_SPI_STATE_BUSY_TX_RX;
        
        
        //Set the mSPI DMA transfer complete callback.
        mSPI->mDMARX->XferCpltCallback = SPI_DMATransmitReceiveCplt;
        //Set the UART DMA Half transfer complete callback
        mSPI->mDMARX->XferHalfCpltCallback = SPI_DMAHalfTransmitReceiveCplt;
        //Set the DMA error callback 
        mSPI->mDMARX->XferErrorCallback = SPI_DMAError;
        //Set the DMA abort callback
        mSPI->mDMARX->XferAbortCallback = NULL;
        
        //Set the mSPI DMA transfer complete callback.
        mSPI->mDMATX->XferCpltCallback = SPI_DMATransmitReceiveCplt;
        //Set the UART DMA Half transfer complete callback
        mSPI->mDMATX->XferHalfCpltCallback = SPI_DMAHalfTransmitReceiveCplt;
        //Set the DMA error callback 
        mSPI->mDMATX->XferErrorCallback = SPI_DMAError;
        //Set the DMA abort callback
        mSPI->mDMATX->XferAbortCallback = NULL;

        /* Configure the source, destination address and the data length */
        MID_DMA_Start_IT(mSPI->mDMARX, (uint32_t)&mSPI->Instance->RDAT.W, (uint32_t) mSPI->pRxBuffPtr.point8, Size);
        MID_DMA_Start_IT(mSPI->mDMATX, (uint32_t) mSPI->pTxBuffPtr.point8, (uint32_t)&mSPI->Instance->TDAT.W, Size);
        
        if(mSPI->REG_TYPE == MID_SPI_SPI)
        {
            mSPI->Instance->CR0.B[3] |= (SPI_CR0_DMA_TXEN_mask_b3 | SPI_CR0_DMA_RXEN_mask_b3);
        }
        else
        {
            mSPI->Instance->CR2.B[0] &= (~(URT_CR2_RX_EN_mask_b0 | URT_CR2_TX_EN_mask_b0));
            mSPI->Instance->CR0.B[3] |= (SPI_CR0_DMA_TXEN_mask_b3 | SPI_CR0_DMA_RXEN_mask_b3);
            mSPI->Instance->CR2.B[0] |= ( URT_CR2_RX_EN_mask_b0 | URT_CR2_TX_EN_mask_b0);
        }

        return(MID_BUSY);
    }
    else
    {
        /* Remain BUSY */
        return(MID_BUSY);
    }  
}


/**
 *******************************************************************************
 * @brief       DMA SPI half transmit process complete callback.
 * @details  
 * @param[in]   mDMA:
 *  @arg\b          mDMA pointer to a DMA_HandleTypeDef structure that contains
 *                  the configuration information for the specified DMA module.
 * @note
 * @par         Example
 * @code
    mSPI->mDMATX->XferHalfCpltCallback = SPI_DMAHalfTransmitCplt;
 * @endcode
 *******************************************************************************
 */
static void SPI_DMAHalfTransmitCplt(DMA_HandleTypeDef *mDMA)
{
    SPI_HandleTypeDef *mSPI = mDMA->Parent;

    MID_SPI_TxHalfCpltCallback(mSPI);
}


/**
 *******************************************************************************
 * @brief       DMA SPI half receive process complete callback.
 * @details  
 * @param[in]   mDMA:
 *  @arg\b          mDMA pointer to a DMA_HandleTypeDef structure that contains
 *                  the configuration information for the specified DMA module.
 * @note
 * @par         Example
 * @code
    mSPI->mDMARX->XferHalfCpltCallback = SPI_DMAHalfReceiveCplt;
 * @endcode
 *******************************************************************************
 */
static void SPI_DMAHalfReceiveCplt(DMA_HandleTypeDef *mDMA)
{
    SPI_HandleTypeDef *mSPI = mDMA->Parent;

  MID_SPI_RxHalfCpltCallback(mSPI);
}


/**
 *******************************************************************************
 * @brief       DMA SPI half transmit receive process complete callback.
 * @details  
 * @param[in]   mDMA:
 *  @arg\b          mDMA pointer to a DMA_HandleTypeDef structure that contains
 *                  the configuration information for the specified DMA module.
 * @note
 * @par         Example
 * @code
    mSPI->mDMARX->XferHalfCpltCallback = SPI_DMAHalfTransmitReceiveCplt;
 * @endcode
 *******************************************************************************
 */
static void SPI_DMAHalfTransmitReceiveCplt(DMA_HandleTypeDef *mDMA)
{
    SPI_HandleTypeDef *mSPI = mDMA->Parent;

  MID_SPI_TxRxHalfCpltCallback(mSPI);
}


/**
 *******************************************************************************
 * @brief       DMA SPI communication error callback.
 * @details  
 * @param[in]   mDMA:
 *  @arg\b          mDMA pointer to a DMA_HandleTypeDef structure that contains
 *                  the configuration information for the specified DMA module.
 * @note
 * @par         Example
 * @code
    mSPI->mDMATX->XferErrorCallback = SPI_DMAError;
 * @endcode
 *******************************************************************************
 */
static void SPI_DMAError(DMA_HandleTypeDef *mDMA)
{
    SPI_HandleTypeDef *mSPI = mDMA->Parent;

    /* Stop the disable DMA transfer on SPI side */
    CLEAR_BIT(mSPI->Instance->CR0.B[3], SPI_CR0_DMA_TXEN_mask_b3 | SPI_CR0_DMA_RXEN_mask_b3);

    SET_BIT(mSPI->ErrorCode, MID_SPI_ERROR_DMA);
    mSPI->State = MID_SPI_STATE_READY;
    MID_SPI_ErrorCallback(mSPI);
}


/**
 *******************************************************************************
 * @brief       Abort ongoing transfer (blocking mode).
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      MID status
 * @note   This procedure could be used for aborting any ongoing transfer (Tx and Rx),
 *         started in Interrupt or DMA mode.
 *         This procedure performs following operations :
 *           - Disable SPI Interrupts (depending of transfer direction)
 *           - Disable the DMA transfer in the peripheral register (if enabled)
 *           - Abort DMA transfer by calling HAL_DMA_Abort (in case of transfer in DMA mode)
 *           - Set handle State to READY
 * @note   This procedure is executed in blocking mode : when exiting function, Abort is considered as completed.
 * @par         Example
 * @code
    return MID_SPI_Abort(&mSPI0);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_SPI_Abort(SPI_HandleTypeDef *mSPI)
{
    MID_StatusTypeDef errorcode;
    __IO uint32_t count, resetcount;

    
    
    /* Initialized local variable  */
    errorcode = MID_OK;
    resetcount = SPI_DEFAULT_TIMEOUT * (SystemCoreClock / 24U / 1000U);
    count = resetcount;

    /* Disable TXEIE, RXNEIE and ERRIE(mode fault event, overrun error, TI frame error) interrupts */
    if((mSPI->Instance->INT.W & SPI_IT_TXF) != 0)
    {
        mSPI->TxISR = SPI_AbortTx_ISR;
        /* Wait MID_SPI_STATE_ABORT state */
        do
        {
            if (count-- == 0U)
            {
                SET_BIT(mSPI->ErrorCode, MID_SPI_ERROR_ABORT);
                break;
            }
        }
        while (mSPI->State != MID_SPI_STATE_ABORT);
        /* Reset Timeout Counter */
        count = resetcount;
    }

    if((mSPI->Instance->INT.W & SPI_IT_RXF) != 0)
    {
        mSPI->RxISR = SPI_AbortRx_ISR;
        /* Wait MID_SPI_STATE_ABORT state */
        do
        {
            if (count-- == 0U)
            {
                SET_BIT(mSPI->ErrorCode, MID_SPI_ERROR_ABORT);
                break;
            }
        }
        while (mSPI->State != MID_SPI_STATE_ABORT);
        /* Reset Timeout Counter */
        count = resetcount;
    }

    /* Clear ERRIE interrupts in case of DMA Mode */
    CLEAR_BIT(mSPI->Instance->INT.W, SPI_IT_ERR);

    /* Disable the SPI DMA Tx or SPI DMA Rx request if enabled */
    if(((mSPI->Instance->CR0.W & SPI_CR0_DMA_TXEN_mask_w) != 0) || 
       ((mSPI->Instance->CR0.W & SPI_CR0_DMA_RXEN_mask_w) != 0))
    {
        /* Abort the SPI DMA Tx Stream/Channel : use blocking DMA Abort API (no callback) */
        if (mSPI->mDMATX != NULL)
        {
            /* Set the SPI DMA Abort callback :
            will lead to call MID_SPI_AbortCpltCallback() at end of DMA abort procedure */
            mSPI->mDMATX->XferAbortCallback = NULL;

            /* Abort DMA Tx Handle linked to SPI Peripheral */
            if (MID_DMA_Abort(mSPI->mDMATX) != MID_OK)
            {
                mSPI->ErrorCode = MID_SPI_ERROR_ABORT;
            }

            /* Disable Tx DMA Request */
            CLEAR_BIT(mSPI->Instance->CR0.W, (SPI_CR0_DMA_TXEN_mask_w));

            if (SPI_EndRxTxTransaction(mSPI, SPI_DEFAULT_TIMEOUT, MID_GetTick()) != MID_OK)
            {
                mSPI->ErrorCode = MID_SPI_ERROR_ABORT;
            }

            /* Disable SPI Peripheral */
            __MID_SPI_DISABLE(mSPI);

            /* Empty the FRLVL fifo */
            if (SPI_WaitFifoStateUntilTimeout(mSPI, SPI_FLAG_RXLVL, SPI_RXLVL_EMPTY, SPI_DEFAULT_TIMEOUT, MID_GetTick()) != MID_OK)
            {
                mSPI->ErrorCode = MID_SPI_ERROR_ABORT;
            }
        }
        
        /* Abort the SPI DMA Rx Stream/Channel : use blocking DMA Abort API (no callback) */
        if (mSPI->mDMARX != NULL)
        {
            /* Set the SPI DMA Abort callback :
            will lead to call MID_SPI_AbortCpltCallback() at end of DMA abort procedure */
            mSPI->mDMARX->XferAbortCallback = NULL;

            /* Abort DMA Rx Handle linked to SPI Peripheral */
            if (MID_DMA_Abort(mSPI->mDMARX) != MID_OK)
            {
                mSPI->ErrorCode = MID_SPI_ERROR_ABORT;
            }

            /* Disable peripheral */
            __MID_SPI_DISABLE(mSPI);

            /* Control the BSY flag */
            if (SPI_WaitFlagStateUntilTimeout(mSPI, SPI_FLAG_BUSYF, CLR, SPI_DEFAULT_TIMEOUT, MID_GetTick()) != MID_OK)
            {
                mSPI->ErrorCode = MID_SPI_ERROR_ABORT;
            }

          /* Empty the FRLVL fifo */
            if (SPI_WaitFifoStateUntilTimeout(mSPI, SPI_FLAG_RXLVL, SPI_RXLVL_EMPTY, SPI_DEFAULT_TIMEOUT, MID_GetTick()) != MID_OK)
            {
                mSPI->ErrorCode = MID_SPI_ERROR_ABORT;
            }

            /* Disable Rx DMA Request */
            CLEAR_BIT(mSPI->Instance->CR0.W, (SPI_CR0_DMA_RXEN_mask_w));
        }
    }
    /* Reset Tx and Rx transfer counters */
    mSPI->RxXferCount = 0U;
    mSPI->TxXferCount = 0U;

    /* Check error during Abort procedure */
    if (mSPI->ErrorCode == MID_SPI_ERROR_ABORT)
    {
        /* return MID_Error in case of error during Abort procedure */
        errorcode = MID_ERROR;
    }
    else
    {
        /* Reset errorCode */
        mSPI->ErrorCode = MID_SPI_ERROR_NONE;
    }

    /* Clear the Error flags in the SR register */
    __MID_SPI_CLEAR_ROVRFFLAG(mSPI);
    __MID_SPI_CLEAR_WEFFLAG(mSPI);

    /* Restore mSPI->state to ready */
    mSPI->State = MID_SPI_STATE_READY;

    return errorcode;
}


/**
 *******************************************************************************
 * @brief       Abort ongoing transfer (Interrupt mode)..
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      MID status
 * @note   This procedure could be used for aborting any ongoing transfer (Tx and Rx),
 *         started in Interrupt or DMA mode.
 *         This procedure performs following operations :
 *           - Disable SPI Interrupts (depending of transfer direction)
 *           - Disable the DMA transfer in the peripheral register (if enabled)
 *           - Abort DMA transfer by calling HAL_DMA_Abort_IT (in case of transfer in DMA mode)
 *           - Set handle State to READY
 *           - At abort completion, call user abort complete callback
 * @note   This procedure is executed in Interrupt mode, meaning that abort procedure could be
 *         considered as completed only when user abort complete callback is executed (not when exiting function).
 * @par         Example
 * @code
    return MID_SPI_Abort_IT(&mSPI0);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_SPI_Abort_IT(SPI_HandleTypeDef *mSPI)
{
    MID_StatusTypeDef errorcode;
    uint32_t abortcplt ;
    __IO uint32_t count, resetcount;

    /* Initialized local variable  */
    errorcode = MID_OK;
    abortcplt = 1U;
    resetcount = SPI_DEFAULT_TIMEOUT * (SystemCoreClock / 24U / 1000U);
    count = resetcount;

    /* Change Rx and Tx Irq Handler to Disable TXEIE, RXNEIE and ERRIE interrupts */
    if((mSPI->Instance->INT.W & SPI_IT_TCF) != 0)
    {
        mSPI->TxISR = SPI_AbortTx_ISR;
        /* Wait MID_SPI_STATE_ABORT state */
        do
        {
            if (count-- == 0U)
            {
                SET_BIT(mSPI->ErrorCode, MID_SPI_ERROR_ABORT);
                break;
            }
        }
        while (mSPI->State != MID_SPI_STATE_ABORT);
        /* Reset Timeout Counter */
        count = resetcount;
    }

    if ((mSPI->Instance->INT.W & SPI_IT_RXF) != 0)
    {
        mSPI->RxISR = SPI_AbortRx_ISR;
        /* Wait MID_SPI_STATE_ABORT state */
        do
        {
            if (count-- == 0U)
            {
                SET_BIT(mSPI->ErrorCode, MID_SPI_ERROR_ABORT);
                break;
            }
        }
        while (mSPI->State != MID_SPI_STATE_ABORT);
        /* Reset Timeout Counter */
        count = resetcount;
    }

    /* Clear ERRIE interrupts in case of DMA Mode */
    mSPI->Instance->INT.W &= ~SPI_IT_ERR;


    /* If DMA Tx and/or DMA Rx Handles are associated to SPI Handle, DMA Abort complete callbacks should be initialised
       before any call to DMA Abort functions */
    /* DMA Tx Handle is valid */
    if (mSPI->mDMATX != NULL)
    {
        /* Set DMA Abort Complete callback if UART DMA Tx request if enabled.
        Otherwise, set it to NULL */
        if((mSPI->Instance->CR0.W & SPI_CR0_DMA_TXEN_mask_w) != 0)
        {
            mSPI->mDMATX->XferAbortCallback = SPI_DMATxAbortCallback;
        }
        else
        {
            mSPI->mDMATX->XferAbortCallback = NULL;
        }
    }
    
    /* DMA Rx Handle is valid */
    if (mSPI->mDMARX != NULL)
    {
        /* Set DMA Abort Complete callback if UART DMA Rx request if enabled.
           Otherwise, set it to NULL */
        if((mSPI->Instance->CR0.W & SPI_CR0_DMA_RXEN_mask_w) != 0)
        {
            mSPI->mDMARX->XferAbortCallback = SPI_DMARxAbortCallback;
        }
        else
        {
            mSPI->mDMARX->XferAbortCallback = NULL;
        }
    }

    /* Disable the SPI DMA Tx or the SPI Rx request if enabled */
    if(((mSPI->Instance->CR0.W & SPI_CR0_DMA_TXEN_mask_w) != 0) && 
       ((mSPI->Instance->CR0.W & SPI_CR0_DMA_RXEN_mask_w) != 0))
    {
        /* Abort the SPI DMA Tx Stream/Channel */
        if (mSPI->mDMATX != NULL)
        {
            /* Abort DMA Tx Handle linked to SPI Peripheral */
            if (MID_DMA_Abort_IT(mSPI->mDMATX) != MID_OK)
            {
                mSPI->mDMATX->XferAbortCallback = NULL;
                mSPI->ErrorCode = MID_SPI_ERROR_ABORT;
            }
            else
            {
                abortcplt = 0U;
            }
        }
        
        /* Abort the SPI DMA Rx Stream/Channel */
        if (mSPI->mDMARX != NULL)
        {
            /* Abort DMA Rx Handle linked to SPI Peripheral */
            if (MID_DMA_Abort_IT(mSPI->mDMARX) !=  MID_OK)
            {
                mSPI->mDMARX->XferAbortCallback = NULL;
                mSPI->ErrorCode = MID_SPI_ERROR_ABORT;
                abortcplt = 1U;
            }
            else
            {
                abortcplt = 0U;
            }
        }
    }

    /* Disable the SPI DMA Tx or the SPI Rx request if enabled */
    if ((mSPI->Instance->CR0.W & SPI_CR0_DMA_TXEN_mask_w) != 0)
    {
        /* Abort the SPI DMA Tx Stream/Channel */
        if (mSPI->mDMATX != NULL)
        {
            /* Abort DMA Tx Handle linked to SPI Peripheral */
            if (MID_DMA_Abort_IT(mSPI->mDMATX) != MID_OK)
            {
                mSPI->mDMATX->XferAbortCallback = NULL;
                mSPI->ErrorCode = MID_SPI_ERROR_ABORT;
            }
            else
            {
                abortcplt = 0U;
            }
        }
    }
    /* Disable the SPI DMA Tx or the SPI Rx request if enabled */
    if ((mSPI->Instance->CR0.W & SPI_CR0_DMA_RXEN_mask_w) != 0)
    {
        /* Abort the SPI DMA Rx Stream/Channel */
        if (mSPI->mDMARX != NULL)
        {
            /* Abort DMA Rx Handle linked to SPI Peripheral */
            if (MID_DMA_Abort_IT(mSPI->mDMARX) !=  MID_OK)
            {
                mSPI->mDMARX->XferAbortCallback = NULL;
                mSPI->ErrorCode = MID_SPI_ERROR_ABORT;
            }
            else
            {
                abortcplt = 0U;
            }
        }
    }

    if (abortcplt == 1U)
    {
        /* Reset Tx and Rx transfer counters */
        mSPI->RxXferCount = 0U;
        mSPI->TxXferCount = 0U;

        /* Check error during Abort procedure */
        if (mSPI->ErrorCode == MID_SPI_ERROR_ABORT)
        {
            /* return MID_Error in case of error during Abort procedure */
            errorcode = MID_ERROR;
        }
        else
        {
            /* Reset errorCode */
            mSPI->ErrorCode = MID_SPI_ERROR_NONE;
        }

        /* Clear the Error flags in the SR register */
        __MID_SPI_CLEAR_ROVRFFLAG(mSPI);
        __MID_SPI_CLEAR_WEFFLAG(mSPI);

        /* Restore mSPI->State to Ready */
        mSPI->State = MID_SPI_STATE_READY;

        /* As no DMA to be aborted, call directly user Abort complete callback */
        MID_SPI_AbortCpltCallback(mSPI);
    }

    return errorcode;
}


/**
 *******************************************************************************
 * @brief       Handle SPI interrupt request.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    MID_SPI_IRQHandler(&mSPI0);
 * @endcode
 *******************************************************************************
 */
void MID_SPI_IRQHandler(SPI_HandleTypeDef *mSPI)
{
    uint32_t itsource = mSPI->Instance->INT.W;
    uint32_t itflag   = mSPI->Instance->STA.W;
    uint32_t itieflag = (itsource & itflag);
    
    
    
    /* SPI in mode Receiver ----------------------------------------------------*/
    if (((itflag & mSPI->SPI_FLAG_ROVRF) == CLR) && ((itieflag & SPI_IT_RXF) != CLR))
    {
        mSPI->RxISR(mSPI);
        return;
    }

    /* SPI in mode Transmitter -------------------------------------------------*/
    // When TCF/TXF/1st transmit data.
    if((itieflag & (mSPI->SPI_FLAG_TCF | SPI_IT_TXF)) != CLR)
    {
#if (defined(MG32_1ST))
        if((*(mSPI->RXTX_LVL) & SPI_FLAG_TXLVL) == 0)
        {
#endif
        mSPI->TxISR(mSPI);
#if (defined(MG32_1ST))
        }
#endif
        return;
    }
    else if (mSPI->TxRxStartEvent != CLR)
    {
        mSPI->TxRxStartEvent = 0;
        mSPI->TxISR(mSPI);
        return;
    }
 
    /* SPI in Error Treatment --------------------------------------------------*/
    if((itflag & itsource & (SPI_IT_MODF | SPI_IT_WEF | SPI_IT_ROVRF | SPI_IT_TUDRF)) != CLR)
    {
        /* SPI Overrun error interrupt occurred ----------------------------------*/
        if(((itflag & mSPI->SPI_FLAG_ROVRF) != CLR) && ((itsource & SPI_IT_ROVRF) != CLR))
        {          
            if (mSPI->State != MID_SPI_STATE_BUSY_TX)
            {
                SET_BIT(mSPI->ErrorCode, MID_SPI_ERROR_OVR);
                __MID_SPI_CLEAR_ROVRFFLAG(mSPI);  
            }
            else
            {
                __MID_SPI_CLEAR_ROVRFFLAG(mSPI);  
                return;
            }
        }
        
        /* SPI Underrun error interrupt occurred ---------------------------------*/
        if(((itflag & mSPI->SPI_FLAG_TUDRF) != CLR) && ((itsource & SPI_IT_TUDRF) != CLR))
        {
            if(mSPI->State != MID_SPI_STATE_BUSY_TX)
            {
                SET_BIT(mSPI->ErrorCode, MID_SPI_ERROR_OVR);
                __MID_SPI_CLEAR_TUDRFFLAG(mSPI);    
            }
            else
            {
                __MID_SPI_CLEAR_TUDRFFLAG(mSPI);    
                return;
            }
        }

        /* SPI Mode Fault error interrupt occurred -------------------------------*/
        if(((itflag & SPI_FLAG_MODF) != CLR) && ((itsource & SPI_IT_MODF) != CLR))
        {
            SET_BIT(mSPI->ErrorCode, MID_SPI_ERROR_MOD);
            __MID_SPI_CLEAR_MODFFLAG(mSPI);     
        }

        /* SPI Frame error interrupt occurred ------------------------------------*/
        if(((itflag & SPI_FLAG_WEF) != CLR) && ((itsource & SPI_IT_WEF) != CLR))
        {
            SET_BIT(mSPI->ErrorCode, MID_SPI_ERROR_WE);
            __MID_SPI_CLEAR_WEFFLAG(mSPI);
        }

        if (mSPI->ErrorCode != MID_SPI_ERROR_NONE)
        {
            
            /* Disable all interrupts */
            __MID_SPI_DISABLE_IT(mSPI, SPI_IT_RXF | SPI_IT_TCF | SPI_IT_ERR);

            mSPI->State = MID_SPI_STATE_READY;
            /* Disable the SPI DMA requests if enabled */
            if(((mSPI->Instance->CR0.W & SPI_CR0_DMA_TXEN_mask_w) != CLR) || 
               ((mSPI->Instance->CR0.W & SPI_CR0_DMA_RXEN_mask_w) != CLR))
            {
                mSPI->Instance->CR0.W &= ~(SPI_CR0_DMA_TXEN_mask_w | 
                                           SPI_CR0_DMA_RXEN_mask_w);

                /* Abort the SPI DMA Rx channel */
                if (mSPI->mDMARX != NULL)
                {
                    /* Set the SPI DMA Abort callback :
                    will lead to call MID_SPI_ErrorCallback() at end of DMA abort procedure */
                    mSPI->mDMARX->XferAbortCallback = SPI_DMAAbortOnError;
                    MID_DMA_Abort_IT(mSPI->mDMARX);   
                }
                /* Abort the SPI DMA Tx channel */
                if (mSPI->mDMATX != NULL)
                {
                    /* Set the SPI DMA Abort callback :
                    will lead to call MID_SPI_ErrorCallback() at end of DMA abort procedure */
                    mSPI->mDMATX->XferAbortCallback = SPI_DMAAbortOnError;
                    MID_DMA_Abort_IT(mSPI->mDMATX);   
                }
            }
            else
            {
                /* Call user error callback */
                MID_SPI_ErrorCallback(mSPI);
            }
        }

    return;
    }
}


/**
 *******************************************************************************
 * @brief       Tx Transfer completed callback.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    MID_SPI_TxCpltCallback(mSPI);
 * @endcode
 *******************************************************************************
 */
__weak void MID_SPI_TxCpltCallback(SPI_HandleTypeDef *mSPI)
{
    UNUSED(mSPI);
    // To do ...
}


/**
 *******************************************************************************
 * @brief       Rx Transfer completed callback.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    MID_SPI_RxCpltCallback(mSPI);
 * @endcode
 *******************************************************************************
 */
__weak void MID_SPI_RxCpltCallback(SPI_HandleTypeDef *mSPI)
{
    UNUSED(mSPI);
    // To do ...
}


/**
 *******************************************************************************
 * @brief       Tx and Rx Transfer completed callback.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    MID_SPI_TxRxCpltCallback(mSPI);
 * @endcode
 *******************************************************************************
 */
__weak void MID_SPI_TxRxCpltCallback(SPI_HandleTypeDef *mSPI)
{
    UNUSED(mSPI);
    // To do ...
}


/**
 *******************************************************************************
 * @brief       Tx MID Transfer completed callback.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    MID_SPI_TxMIDCpltCallback(mSPI);
 * @endcode
 *******************************************************************************
 */
__weak void MID_SPI_TxHalfCpltCallback(SPI_HandleTypeDef *mSPI)
{
    UNUSED(mSPI);
    // To do ...
}


/**
 *******************************************************************************
 * @brief       Rx MID Transfer completed callback.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    MID_SPI_RxMIDCpltCallback(mSPI);
 * @endcode
 *******************************************************************************
 */
__weak void MID_SPI_RxHalfCpltCallback(SPI_HandleTypeDef *mSPI)
{
    UNUSED(mSPI);
    // To do ...
}


/**
 *******************************************************************************
 * @brief       Tx and Rx MID Transfer callback.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    MID_SPI_TxRxMIDCpltCallback(mSPI);
 * @endcode
 *******************************************************************************
 */
__weak void MID_SPI_TxRxHalfCpltCallback(SPI_HandleTypeDef *mSPI)
{
    UNUSED(mSPI);
    // To do ...
}


/**
 *******************************************************************************
 * @brief       SPI error callback.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    MID_SPI_ErrorCallback(mSPI);
 * @endcode
 *******************************************************************************
 */
__weak void MID_SPI_ErrorCallback(SPI_HandleTypeDef *mSPI)
{
    UNUSED(mSPI);
    // To do ...
}


/**
 *******************************************************************************
 * @brief       SPI Abort Complete callback.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    MID_SPI_AbortCpltCallback(mSPI);
 * @endcode
 *******************************************************************************
 */
__weak void MID_SPI_AbortCpltCallback(SPI_HandleTypeDef *mSPI)
{
    UNUSED(mSPI);
    // To do ...
}


/**
 *******************************************************************************
 * @brief       DMA SPI transmit process complete callback.
 * @details  
 * @param[in]   mDMA:
 *  @arg\b          mDMA pointer to a DMA_HandleTypeDef structure that contains 
 *                  the configuration information for the specified DMA module.
 * @return      none
 * @note
 * @par         Example
 * @code
    mSPI->mDMATX->XferCpltCallback = SPI_DMATransmitCplt;
 * @endcode
 *******************************************************************************
 */
void SPI_DMATransmitCplt(DMA_HandleTypeDef *mDMA)
{
    SPI_HandleTypeDef *mSPI = mDMA->Parent;
    uint32_t tickstart = 0U;



    /* Init tickstart for timeout managment*/
    tickstart = MID_GetTick();

    /* Disable ERR interrupt */
    __MID_SPI_DISABLE_IT(mSPI, SPI_IT_ERR);

    /* Disable Tx DMA Request */
//    CLEAR_BIT(mSPI->Instance->CR0.B[3], SPI_CR0_DMA_TXEN_mask_b3);

    /* Check the end of the transaction */
    if (SPI_EndRxTxTransaction(mSPI, SPI_DEFAULT_TIMEOUT, tickstart) != MID_OK)
    {
        SET_BIT(mSPI->ErrorCode, MID_SPI_ERROR_FLAG);
    }

    /* Clear overrun flag in 2 Lines communication mode because received data is not read */
    if (mSPI->Init.DataLine == SPI_STANDARD_SPI)
    {
        __MID_SPI_CLEAR_ROVRFFLAG(mSPI);
    }

    mSPI->TxXferCount = 0U;
    mSPI->State = MID_SPI_STATE_READY;

    if (mSPI->ErrorCode != MID_SPI_ERROR_NONE)
    {
        MID_SPI_ErrorCallback(mSPI);
        return;
    }

    __MID_UNLOCK(mSPI);
    
    
    MID_SPI_TxCpltCallback(mSPI);
}


/**
 *******************************************************************************
 * @brief       DMA SPI receive process complete callback.
 * @details  
 * @param[in]   mDMA:
 *  @arg\b          mDMA pointer to a DMA_HandleTypeDef structure that contains 
 *                  the configuration information for the specified DMA module.
 * @return      none
 * @note
 * @par         Example
 * @code
    mSPI->mDMATX->XferCpltCallback = SPI_DMAReceiveCplt;
 * @endcode
 *******************************************************************************
 */
static void SPI_DMAReceiveCplt(DMA_HandleTypeDef *mDMA)
{
    SPI_HandleTypeDef *mSPI = mDMA->Parent;


    /* Disable ERR interrupt */
    __MID_SPI_DISABLE_IT(mSPI, SPI_IT_ERR);

    // Disable Rx/Tx DMA Request (done by default to handle the case master rx direction 2 lines) */
//    CLEAR_BIT(mSPI->Instance->CR0.B[3], SPI_CR0_DMA_TXEN_mask_b3 | SPI_CR0_DMA_RXEN_mask_b3);

    mSPI->RxXferCount = 0U;
    mSPI->State = MID_SPI_STATE_READY;


    if (mSPI->ErrorCode != MID_SPI_ERROR_NONE)
    {
        MID_SPI_ErrorCallback(mSPI);
        return;
    }
    __MID_UNLOCK(mSPI);

    MID_SPI_RxCpltCallback(mSPI);
}


/**
 *******************************************************************************
 * @brief       DMA SPI transmit receive process complete callback.
 * @details  
 * @param[in]   mDMA:
 *  @arg\b          mDMA pointer to a DMA_HandleTypeDef structure that contains 
 *                  the configuration information for the specified DMA module.
 * @return      none
 * @note
 * @par         Example
 * @code
    mSPI->mDMATX->XferCpltCallback = SPI_DMATransmitReceiveCplt;
 * @endcode
 *******************************************************************************
 */
static void SPI_DMATransmitReceiveCplt(DMA_HandleTypeDef *mDMA)
{
    SPI_HandleTypeDef *mSPI = mDMA->Parent;
    uint32_t           tickstart = 0U;
         
    // Init tickstart for timeout management
    tickstart = MID_GetTick();

    // Disable ERR interrupt
    __MID_SPI_DISABLE_IT(mSPI, SPI_IT_ERR);

    if((mDMA->Init.SrcPeri & MID_DMA_SPI_READ_MASK) > (MID_DMA_SPI_READ_MINID - 1))
    {
        if( (mDMA->Init.SrcPeri & MID_DMA_SPI_READ_MASK) < (MID_DMA_SPI_READ_MAXID + 1))
        {
            mSPI->RxXferCount      = 0U;
            *mSPI->RXTX_CLR       |= ( SPI_CR1_RDAT_CLR_mask_b0 | URT_CR4_RDAT_CLR_mask_b0);
            
            /* Disable Rx/Tx DMA Request */
//            CLEAR_BIT(mSPI->Instance->CR0.B[3], SPI_CR0_DMA_RXEN_mask_b3);
            
            // When RXF happened or RXLVL not empty
            while( (mSPI->Instance->STA.W & SPI_FLAG_RXF) || ((*(mSPI->RXTX_LVL)) & SPI_FLAG_RXLVL)!=0)
            {
                // When RX shadow buffer not empty
                if( mSPI->RxXferCount!=0)
                {
                    // Receive data in 32 Bit mode
                    if(mSPI->Init.DataSize > SPI_DATASIZE_16BIT)
                    {
                        *(mSPI->pRxBuffPtr.point32) = mSPI->Instance->RDAT.W;
                        mSPI->pRxBuffPtr.point8 += sizeof(uint32_t);
                        mSPI->RxXferCount--;
                    }
                    // Receive data in 16 Bit mode
                    else if (mSPI->Init.DataSize > SPI_DATASIZE_8BIT)
                    {
                        *(mSPI->pRxBuffPtr.point16) = mSPI->Instance->RDAT.H[0];
                        mSPI->pRxBuffPtr.point8 += sizeof(uint16_t);
                        mSPI->RxXferCount--;
                    }
                    // Receive data in 8 Bit mode
                    else 
                    {
                        (*mSPI->pRxBuffPtr.point8) = mSPI->Instance->RDAT.B[0];
                        mSPI->pRxBuffPtr.point8 += sizeof(uint8_t);
                        mSPI->RxXferCount--;
                    }
                }
                else
                {
                    __MID_SPI_CLEAR_RXDATA(mSPI);
                }
            }            
            
            // Clear error flag
            if(mSPI->REG_TYPE == MID_SPI_SPI)
                WRITE_REG(mSPI->Instance->STA.W , (mSPI->SPI_FLAG_ROVRF | mSPI->SPI_FLAG_TUDRF | SPI_FLAG_MODF | SPI_FLAG_WEF | mSPI->SPI_FLAG_IDLF));
            if(mSPI->REG_TYPE == MID_SPI_URT)
                WRITE_REG(mSPI->Instance->STA.W , (mSPI->SPI_FLAG_ROVRF | mSPI->SPI_FLAG_TUDRF));
            
            // When status is DMA TX RX
            if(mSPI->State == MID_SPI_STATE_BUSY_TX_RX)
            {
                mSPI->State = MID_SPI_STATE_BUSY_TX;
            }
            // When status is DMA RX
            else if(mSPI->State == MID_SPI_STATE_BUSY_RX)
            {
                mSPI->State = MID_SPI_STATE_READY;
            }
        }
    }
        
    if((mDMA->Init.DesPeri & MID_DMA_SPI_WRITE_MASK) > ( MID_DMA_SPI_WRITE_MINID - 1))
    {
        if((mDMA->Init.DesPeri & MID_DMA_SPI_WRITE_MASK) < ( MID_DMA_SPI_WRITE_MAXID + 1))
        {
            mSPI->TxXferCount = 0U;
            
            /* Disable Rx/Tx DMA Request */
//            CLEAR_BIT(mSPI->Instance->CR0.B[3], SPI_CR0_DMA_TXEN_mask_b3);
            
            // Control if the TX fifo is empty
            if(SPI_WaitFlagStateUntilTimeout( mSPI, mSPI->SPI_FLAG_TCF, mSPI->SPI_FLAG_TCF , SPI_DEFAULT_TIMEOUT , tickstart) != MID_OK)
            {
                SET_BIT(mSPI->ErrorCode, MID_SPI_ERROR_FLAG);
            }
            else
            {   // Clear flag SPI TCF and TXF
                WRITE_REG(mSPI->Instance->STA.W , (mSPI->SPI_FLAG_TCF | SPI_FLAG_TXF));
            }
            
            // When status is DMA TX RX
            if(mSPI->State == MID_SPI_STATE_BUSY_TX_RX)
            {
                mSPI->State = MID_SPI_STATE_BUSY_RX;
            }
            // When status is DMA TX
            else if(mSPI->State == MID_SPI_STATE_BUSY_TX)
            {
                mSPI->State = MID_SPI_STATE_READY;
            }
        }
    }
    
    
//    // Check the end of the transaction
//    if (SPI_EndRxTxTransaction(mSPI, SPI_DEFAULT_TIMEOUT, tickstart) != MID_OK)
//    {
//        SET_BIT(mSPI->ErrorCode, MID_SPI_ERROR_FLAG);
//    }
    // Check transmit and receive is complete and unlock mSPI
    if((mSPI->Instance->CR0.W & (SPI_CR0_DMA_TXEN_mask_w | SPI_CR0_DMA_RXEN_mask_w)) == 0x00000000)
    {
        __MID_UNLOCK(mSPI);
    }

    

    if (mSPI->ErrorCode != MID_SPI_ERROR_NONE)
    {
        MID_SPI_ErrorCallback(mSPI);
        return;
    }

    MID_SPI_TxRxCpltCallback(mSPI);
}


/**
 *******************************************************************************
 * @brief       DMA SPI Tx communication abort callback, when initiated by user
 *              (To be called at end of DMA Tx Abort procedure following user abort request).
 * @details  
 * @param[in]   mdma: mDMA DMA handle. 
 * @return      none
 * @note
 * @par         Example
 * @code
    mSPI->mDMATX->XferAbortCallback = SPI_DMATxAbortCallback;
 * @endcode
 *******************************************************************************
 */
static void SPI_DMATxAbortCallback(DMA_HandleTypeDef *mdma)
{
    SPI_HandleTypeDef *mSPI = (SPI_HandleTypeDef *)((DMA_HandleTypeDef *)mdma)->Parent;

    mSPI->mDMATX->XferAbortCallback = NULL;

    /* Disable Tx DMA Request */
    CLEAR_BIT(mSPI->Instance->CR0.W, SPI_CR0_DMA_TXEN_mask_w);

    if (SPI_EndRxTxTransaction(mSPI, SPI_DEFAULT_TIMEOUT, MID_GetTick()) != MID_OK)
    {
        mSPI->ErrorCode = MID_SPI_ERROR_ABORT;
    }

    /* Disable SPI Peripheral */
    __MID_SPI_DISABLE(mSPI);

    /* Empty the FRLVL fifo */
    if (SPI_WaitFifoStateUntilTimeout(mSPI, SPI_FLAG_RXLVL, SPI_RXLVL_EMPTY, SPI_DEFAULT_TIMEOUT, MID_GetTick()) != MID_OK)
    {
        mSPI->ErrorCode = MID_SPI_ERROR_ABORT;
    }

    /* Check if an Abort process is still ongoing */
    if (mSPI->mDMARX != NULL)
    {
        if (mSPI->mDMARX->XferAbortCallback != NULL)
        {
            return;
        }
    }

    /* No Abort process still ongoing : All DMA Stream/Channel are aborted, call user Abort Complete callback */
    mSPI->RxXferCount = 0U;
    mSPI->TxXferCount = 0U;

    /* Check no error during Abort procedure */
    if (mSPI->ErrorCode != MID_SPI_ERROR_ABORT)
    {
        /* Reset errorCode */
        mSPI->ErrorCode = MID_SPI_ERROR_NONE;
    }

    /* Clear the Error flags in the SR register */
    __MID_SPI_CLEAR_ROVRFFLAG(mSPI);
    __MID_SPI_CLEAR_WEFFLAG(mSPI);

    /* Restore mSPI->State to Ready */
    mSPI->State  = MID_SPI_STATE_READY;

    /* Call user Abort complete callback */
    MID_SPI_AbortCpltCallback(mSPI);
}

/**
 *******************************************************************************
 * @brief       DMA SPI Rx communication abort callback, when initiated by user
 *              (To be called at end of DMA Rx Abort procedure following user abort request).
 * @details  
 * @param[in]   mdma: mDMA DMA handle. 
 * @return      none
 * @note
 * @par         Example
 * @code
    mSPI->mDMARX->XferAbortCallback = SPI_DMARxAbortCallback;
 * @endcode
 *******************************************************************************
 */
static void SPI_DMARxAbortCallback(DMA_HandleTypeDef *mdma)
{
  SPI_HandleTypeDef *mSPI = (SPI_HandleTypeDef *)((DMA_HandleTypeDef *)mdma)->Parent;

  /* Disable SPI Peripheral */
  __MID_SPI_DISABLE(mSPI);

  mSPI->mDMARX->XferAbortCallback = NULL;

  /* Disable Rx DMA Request */
  CLEAR_BIT(mSPI->Instance->CR0.W, SPI_CR0_DMA_RXEN_mask_w);

  /* Control the BSY flag */
  if (SPI_WaitFlagStateUntilTimeout(mSPI, SPI_FLAG_BUSYF, CLR, SPI_DEFAULT_TIMEOUT, MID_GetTick()) != MID_OK)
  {
    mSPI->ErrorCode = MID_SPI_ERROR_ABORT;
  }

  /* Empty the FRLVL fifo */
  if (SPI_WaitFifoStateUntilTimeout(mSPI, SPI_FLAG_RXLVL, SPI_RXLVL_EMPTY, SPI_DEFAULT_TIMEOUT, MID_GetTick()) != MID_OK)
  {
    mSPI->ErrorCode = MID_SPI_ERROR_ABORT;
  }

  /* Check if an Abort process is still ongoing */
  if (mSPI->mDMATX != NULL)
  {
    if (mSPI->mDMATX->XferAbortCallback != NULL)
    {
      return;
    }
  }

  /* No Abort process still ongoing : All DMA Stream/Channel are aborted, call user Abort Complete callback */
  mSPI->RxXferCount = 0U;
  mSPI->TxXferCount = 0U;

  /* Check no error during Abort procedure */
  if (mSPI->ErrorCode != MID_SPI_ERROR_ABORT)
  {
    /* Reset errorCode */
    mSPI->ErrorCode = MID_SPI_ERROR_NONE;
  }

  /* Clear the Error flags in the SR register */
  __MID_SPI_CLEAR_ROVRFFLAG(mSPI);
  __MID_SPI_CLEAR_WEFFLAG(mSPI);

  /* Restore mSPI->State to Ready */
  mSPI->State  = MID_SPI_STATE_READY;

  /* Call user Abort complete callback */
  MID_SPI_AbortCpltCallback(mSPI);
}


/**
 *******************************************************************************
 * @brief       DMA SPI communication abort callback, when initiated by HAL services on Error
 *              (To be called at end of DMA Abort procedure following error occurrence).
 * @details  
 * @param[in]   mdma: mDMA DMA handle. 
 * @return      none
 * @note
 * @par         Example
 * @code
    mSPI->mDMARX->XferAbortCallback = SPI_DMAAbortOnError;
 * @endcode
 *******************************************************************************
 */
static void SPI_DMAAbortOnError(DMA_HandleTypeDef *mdma)
{
    SPI_HandleTypeDef *mSPI = (SPI_HandleTypeDef *)((DMA_HandleTypeDef *)mdma)->Parent;
    mSPI->RxXferCount = 0U;
    mSPI->TxXferCount = 0U;

    MID_SPI_ErrorCallback(mSPI);
}


/**
 *******************************************************************************
 * @brief       Handle standard SPI 2 lines data size 4~8 bit RX and TX 
 *              interrupt mode.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    mSPI->RxISR = SPI_2linesRxISR_8BIT;
 * @endcode
 *******************************************************************************
 */
static void SPI_2linesRxISR_8BIT(struct tag_SPI_HandleTypeDef *mSPI)
{
    ctype    SPI_2linesRXISR_8BIT_Tmp;
    uint8_t  SPI_2linesRXISR_8BIT_RXNUM;

    
    SPI_2linesRXISR_8BIT_RXNUM = (*mSPI->RNUM) & SPI_STA_RNUM_mask_b3;
    
    
    if( SPI_2linesRXISR_8BIT_RXNUM == 4)
    {
        *(mSPI->pRxBuffPtr.point32) = mSPI->Instance->RDAT.W;
    }
    else if( SPI_2linesRXISR_8BIT_RXNUM == 3)
    {
        SPI_2linesRXISR_8BIT_Tmp.W = mSPI->Instance->RDAT.W;
        
        *(mSPI->pRxBuffPtr.point8)     = SPI_2linesRXISR_8BIT_Tmp.B[0];
        *((mSPI->pRxBuffPtr.point8+1)) = SPI_2linesRXISR_8BIT_Tmp.B[1];
        *((mSPI->pRxBuffPtr.point8+2)) = SPI_2linesRXISR_8BIT_Tmp.B[2]; 
    }
    else if( SPI_2linesRXISR_8BIT_RXNUM == 2)
    {
        *(mSPI->pRxBuffPtr.point16) = mSPI->Instance->RDAT.H[0];
    }
    else
    {
        *(mSPI->pRxBuffPtr.point8) = mSPI->Instance->RDAT.B[0];
    }

    mSPI->pRxBuffPtr.point8  += SPI_2linesRXISR_8BIT_RXNUM;
    mSPI->RxXferCount -= SPI_2linesRXISR_8BIT_RXNUM;
    
    
    // Check end of the reception
    if (mSPI->RxXferCount == 0U)
    {
        // Disable RXF  and ERR interrupt
        __MID_SPI_DISABLE_IT(mSPI, SPI_IT_RXF | mSPI->SPI_FLAG_ERROR);
        // Check the end of the transmission
        if (mSPI->TxXferCount == 0U)
        {
            SPI_CloseRxTx_ISR(mSPI);
        }
    }
    else if(mSPI->RxXferCount < 4U && mSPI->REG_TYPE == MID_SPI_SPI)
    {
        *mSPI->RX_TH = (uint8_t)(mSPI->RxXferCount - 1);
    }
}
/**
 *******************************************************************************
 * @brief       Handle standard SPI 2 lines data size 4~8 bit RX and TX 
 *              interrupt mode.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    mSPI->TxISR = SPI_2linesTxISR_8BIT;
 * @endcode
 *******************************************************************************
 */
static void SPI_2linesTxISR_8BIT(struct tag_SPI_HandleTypeDef *mSPI)
{
    // Transmit data in packing Bit mode > 4 bytes
    if (mSPI->TxXferCount > 3)
    {   // Set 4 8 bit data
        mSPI->Instance->TDAT.W = *(mSPI->pTxBuffPtr.point32);
        mSPI->pTxBuffPtr.point8 += sizeof(uint32_t);
        mSPI->TxXferCount -= 4U;
    }
    
    // Transmit data in packing Bit mode => 2 bytes
    else if (mSPI->TxXferCount > 1)
    {   // Set 2 8 bit data
        mSPI->Instance->TDAT.H[0] = *(mSPI->pTxBuffPtr.point16);
        mSPI->pTxBuffPtr.point8 += sizeof(uint16_t);
        mSPI->TxXferCount -= 2U;
    }
    // Transmit data in packing Bit mode = 1 bytes
    else if (mSPI->TxXferCount == 1)
    {   // Set 8 bit data
        *(__IO uint8_t *)&mSPI->Instance->TDAT.B[0] = (*mSPI->pTxBuffPtr.point8++);
        mSPI->TxXferCount--;
    }
    
    // Check the end of the transmission
    if (mSPI->TxXferCount == 0U)
    {
        // Disable TXF and TCF interrupt
        __MID_SPI_DISABLE_IT(mSPI, mSPI->SPI_FLAG_TCF | SPI_IT_TXF);

        // Check the end of the reception.
        if (mSPI->RxXferCount == 0U)
        {
            SPI_CloseRxTx_ISR(mSPI);
        }
    }
}


/**
 *******************************************************************************
 * @brief       Handle standard SPI 2 lines data size 9~16 bit RX and TX 
 *              interrupt mode.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    mSPI->RxISR = SPI_2linesRxISR_16BIT;
 * @endcode
 *******************************************************************************
 */
static void SPI_2linesRxISR_16BIT(struct tag_SPI_HandleTypeDef *mSPI)
{
    uint8_t  SPI_2linesRXISR_16BIT_RXNUM;

    
    SPI_2linesRXISR_16BIT_RXNUM = (*mSPI->RNUM) & SPI_STA_RNUM_mask_b3;
    
    
    // When receive size >= 2
    if( SPI_2linesRXISR_16BIT_RXNUM == 4)
    {
        // Get 2 16 bit data
        *(mSPI->pRxBuffPtr.point32) = mSPI->Instance->RDAT.W;
        mSPI->pRxBuffPtr.point8 += sizeof(uint32_t);
        mSPI->RxXferCount -= 2;
        
        if (mSPI->RxXferCount == 1)
        {
            // set fiforxthresold according the reception data length: 16bit
            *mSPI->RX_TH = 1;
        }
        
    }
    else
    {
        // Get 16 bit data
        *(mSPI->pRxBuffPtr.point16) = mSPI->Instance->RDAT.H[0];
        mSPI->pRxBuffPtr.point8 += sizeof(uint16_t);
        mSPI->RxXferCount--;
        
    }
    
    // Check the end of the reception
    if (mSPI->RxXferCount == 0)
    {
        // Disable RXF and ERR interrupt
        __MID_SPI_DISABLE_IT(mSPI, SPI_IT_RXF | mSPI->SPI_FLAG_ERROR);

        // Check the end of the transmission
        if (mSPI->TxXferCount == 0U)
        {
            SPI_CloseRxTx_ISR(mSPI);
        }
    }
}


/**
 *******************************************************************************
 * @brief       Handle standard SPI 2 lines data size 9~16 bit RX and TX 
 *              interrupt mode.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    mSPI->TxISR = SPI_2linesTxISR_16BIT;
 * @endcode
 *******************************************************************************
 */
static void SPI_2linesTxISR_16BIT(struct tag_SPI_HandleTypeDef *mSPI)
{
    // When Tx count >= 2
    if (mSPI->TxXferCount > 1)
    {   // Set 2 16 bit data
        mSPI->Instance->TDAT.W = *(mSPI->pTxBuffPtr.point32);
        mSPI->pTxBuffPtr.point8 += sizeof(uint32_t);
        mSPI->TxXferCount -= 2;
    }
    // When Tx count = 1
    else if (mSPI->TxXferCount == 1)
    {   // Set 16 bit data
        mSPI->Instance->TDAT.H[0] = *(mSPI->pTxBuffPtr.point16);
        mSPI->pTxBuffPtr.point8 += sizeof(uint16_t);
        mSPI->TxXferCount--;
    }
    
    // Check the end of the transmission
    if (mSPI->TxXferCount == 0)
    {
        // Disable TXF and TCF interrupt
        __MID_SPI_DISABLE_IT(mSPI, mSPI->SPI_FLAG_TCF | SPI_IT_TXF);

        // Check the end of the reception.
        if (mSPI->RxXferCount == 0)
        {
            SPI_CloseRxTx_ISR(mSPI);
        }
    }
}


/**
 *******************************************************************************
 * @brief       Handle standard SPI 2 lines data size 17~32 bit RX and TX 
 *              interrupt mode.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    mSPI->RxISR = SPI_2linesRxISR_32BIT;
 * @endcode
 *******************************************************************************
 */
static void SPI_2linesRxISR_32BIT(struct tag_SPI_HandleTypeDef *mSPI)
{
    // Get 32 bit RX data
    *(mSPI->pRxBuffPtr.point32) = mSPI->Instance->RDAT.W;
    mSPI->pRxBuffPtr.point8 += sizeof(uint32_t);
    mSPI->RxXferCount--;

    // Check the end of the reception.
    if (mSPI->RxXferCount == 0U)
    {
        // Disable RXF and ERR interrupt
        __MID_SPI_DISABLE_IT(mSPI, SPI_IT_RXF | mSPI->SPI_FLAG_ERROR);

        // Check the end of the transmission
        if (mSPI->TxXferCount == 0U)
        {
            SPI_CloseRxTx_ISR(mSPI);
        }
    }
}


/**
 *******************************************************************************
 * @brief       Handle standard SPI 2 lines data size 17~32 bit RX and TX 
 *              interrupt mode.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    mSPI->TxISR = SPI_2linesTxISR_32BIT;
 * @endcode
 *******************************************************************************
 */
static void SPI_2linesTxISR_32BIT(struct tag_SPI_HandleTypeDef *mSPI)
{
    // Set 32 bit TX data
    mSPI->Instance->TDAT.W = *(mSPI->pTxBuffPtr.point32++);
    mSPI->TxXferCount--;

    // Check the end of the transmission
    if (mSPI->TxXferCount == 0U)
    {
        // Disable TXE and TCF interrupt
        __MID_SPI_DISABLE_IT(mSPI, mSPI->SPI_FLAG_TCF | SPI_IT_TXF);
        
        // Check the end of the reception.
        if (mSPI->RxXferCount == 0U)
        {
            SPI_CloseRxTx_ISR(mSPI);
        }
    }
}


/**
 *******************************************************************************
 * @brief       Handle size 4~8 bit RX interrupt mode.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    mSPI->RxISR = SPI_RxISR_8BIT;
 * @endcode
 *******************************************************************************
 */
static void SPI_RxISR_8BIT(struct tag_SPI_HandleTypeDef *mSPI)
{
    uint8_t SPI_RxISR_8BIT_RXNUM;
    ctype   SPI_RxISR_8BIT_Tmp;
    
    
    
    SPI_RxISR_8BIT_RXNUM = (*mSPI->RNUM & SPI_STA_RNUM_mask_b3);

    if( SPI_RxISR_8BIT_RXNUM == 4)
    {
        *(mSPI->pRxBuffPtr.point32) = mSPI->Instance->RDAT.W;
    }
    else if( SPI_RxISR_8BIT_RXNUM == 3)
    {
        SPI_RxISR_8BIT_Tmp.W = mSPI->Instance->RDAT.W;
        
        *(mSPI->pRxBuffPtr.point8)      = (uint8_t) SPI_RxISR_8BIT_Tmp.B[0];
        *(mSPI->pRxBuffPtr.point8 + 1)  = (uint8_t) SPI_RxISR_8BIT_Tmp.B[1];
        *(mSPI->pRxBuffPtr.point8 + 2)  = (uint8_t) SPI_RxISR_8BIT_Tmp.B[2];
    }
    else if( SPI_RxISR_8BIT_RXNUM == 2)
    {
        *(mSPI->pRxBuffPtr.point16) = mSPI->Instance->RDAT.H[0];
    }
    else
    {
        *(mSPI->pRxBuffPtr.point8) = mSPI->Instance->RDAT.B[0];        
    }
    
    
    mSPI->pRxBuffPtr.point8  += SPI_RxISR_8BIT_RXNUM;
    mSPI->RxXferCount -= SPI_RxISR_8BIT_RXNUM;
    
    if (mSPI->RxXferCount == 0U)
    {
        SPI_CloseRx_ISR(mSPI);
    }
    else if( mSPI->RxXferCount < 4U && mSPI->REG_TYPE == MID_SPI_SPI)
    {
        *mSPI->RX_TH = (uint8_t)(mSPI->RxXferCount - 1);
    }
}

/**
 *******************************************************************************
 * @brief       Handle size 9~16 bit RX interrupt mode.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    mSPI->RxISR = SPI_RxISR_16BIT;
 * @endcode
 *******************************************************************************
 */
static void SPI_RxISR_16BIT(struct tag_SPI_HandleTypeDef *mSPI)
{
    uint8_t SPI_RxISR_16BIT_RXNUM;
    
    
    SPI_RxISR_16BIT_RXNUM = (*mSPI->RNUM & SPI_STA_RNUM_mask_b3);
    
    
    if( SPI_RxISR_16BIT_RXNUM == 4)
    {
        *(mSPI->pRxBuffPtr.point32) = mSPI->Instance->RDAT.W;
    }
    else if( SPI_RxISR_16BIT_RXNUM == 2)
    {
        *(mSPI->pRxBuffPtr.point16) = mSPI->Instance->RDAT.H[0];
    }
    else if( SPI_RxISR_16BIT_RXNUM == 3)
    {
        *(mSPI->pRxBuffPtr.point16) = mSPI->Instance->RDAT.H[0];        /* Debug???? */
        
        SPI_RxISR_16BIT_RXNUM = 2;
    }
    else
    {
        SPI_RxISR_16BIT_RXNUM = 0;
    }
    
    mSPI->pRxBuffPtr.point8  += SPI_RxISR_16BIT_RXNUM;
    mSPI->RxXferCount -= SPI_RxISR_16BIT_RXNUM;
    
    // Check the end of the reception.
    if (mSPI->RxXferCount == 0U)
    {
        SPI_CloseRx_ISR(mSPI);
    }
    else if(mSPI->RxXferCount <= 1) 
    {
        // Modify RX_TH
        MODIFY_REG( *mSPI->RNUM , SPI_STA_RNUM_mask_b3 , 1);
    }
}


/**
 *******************************************************************************
 * @brief       Handle size 17~32 bit RX interrupt mode.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    mSPI->RxISR = SPI_RxISR_32BIT;
 * @endcode
 *******************************************************************************
 */
static void SPI_RxISR_32BIT(struct tag_SPI_HandleTypeDef *mSPI)
{
    // Get 32 bit data
    *(mSPI->pRxBuffPtr.point32) = mSPI->Instance->RDAT.W;
    mSPI->pRxBuffPtr.point32 += sizeof(uint32_t);

    // RxCferCount --
    mSPI->RxXferCount--;

    // Check the end of the reception.
    if (mSPI->RxXferCount == 0U)
    {
        SPI_CloseRx_ISR(mSPI);
    }
}


/**
 *******************************************************************************
 * @brief       Handle size 4~8 bit TX interrupt mode.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    mSPI->TxISR = SPI_TxISR_8BIT;
 * @endcode
 *******************************************************************************
 */
static void SPI_TxISR_8BIT(struct tag_SPI_HandleTypeDef *mSPI)
{
    
    // Check the end of the transmission
    if (mSPI->TxXferCount == 0U)
    {
        SPI_CloseTx_ISR(mSPI);
    }
    
    // When Tx count >= 4
    if(mSPI->TxXferCount > 3)
    {
        mSPI->Instance->TDAT.W = *(mSPI->pTxBuffPtr.point32);
        mSPI->pTxBuffPtr.point8 += sizeof(uint32_t);
        mSPI->TxXferCount -= 4;
    }
    // When Tx count >= 2 ~ 3
    else if(mSPI->TxXferCount > 1)
    {
        mSPI->Instance->TDAT.H[0] = (uint16_t) *(mSPI->pTxBuffPtr.point16);
        mSPI->pTxBuffPtr.point8 += sizeof(uint16_t);
        mSPI->TxXferCount -= 2;
    }
    // When Tx count >= 1
    else if(mSPI->TxXferCount > 0)
    {
        mSPI->Instance->TDAT.B[0] = (*mSPI->pTxBuffPtr.point8++);
        mSPI->TxXferCount--;
    }
}


/**
 *******************************************************************************
 * @brief       Handle size 9~16 bit TX interrupt mode.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    mSPI->TxISR = SPI_TxISR_16BIT;
 * @endcode
 *******************************************************************************
 */
static void SPI_TxISR_16BIT(struct tag_SPI_HandleTypeDef *mSPI)
{
    // Check the end of the transmission
    if (mSPI->TxXferCount == 0U)
    {
        SPI_CloseTx_ISR(mSPI);
    }
    
    // When Tx count >= 2
    if(mSPI->TxXferCount > 1)
    {
        mSPI->Instance->TDAT.W = *(mSPI->pTxBuffPtr.point32++);
        mSPI->TxXferCount -= 2;
    }
    // When Tx count >= 1
    else if(mSPI->TxXferCount > 0)
    {
        mSPI->Instance->TDAT.H[0] = *(mSPI->pTxBuffPtr.point16++);
        mSPI->TxXferCount--;
    }
}


/**
 *******************************************************************************
 * @brief       Handle size 17~32 bit TX interrupt mode.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    mSPI->TxISR = SPI_TxISR_32BIT;
 * @endcode
 *******************************************************************************
 */
static void SPI_TxISR_32BIT(struct tag_SPI_HandleTypeDef *mSPI)
{
    // Check the end of the transmission
    if (mSPI->TxXferCount == 0U)
    {
        SPI_CloseTx_ISR(mSPI);
    }
    
    // When Tx count >= 1
    if(mSPI->TxXferCount > 0)
    {
        /* Transmit data in 32 Bit mode */
        mSPI->Instance->TDAT.W = *(mSPI->pTxBuffPtr.point32++);
        mSPI->TxXferCount--;
    }
}


/**
 *******************************************************************************
 * @brief       Handle SPI Communication Timeout.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @param[in]   Flag SPI flag to check
 * @param[in]   State flag state to check
 * @param[in]   Timeout Timeout duration
 * @param[in]   Tickstart tick start value
 * @return      MID status
 * @note
 * @par         Example
 * @code
    if (SPI_WaitFlagStateUntilTimeout(mSPI, SPI_FLAG_BUSYF, CLR, SPI_DEFAULT_TIMEOUT, MID_GetTick()) != MID_OK)
 * @endcode
 *******************************************************************************
 */
static MID_StatusTypeDef SPI_WaitFlagStateUntilTimeout(SPI_HandleTypeDef *mSPI,         
    uint32_t Flag, uint32_t State __attribute__((unused)), uint32_t Timeout, uint32_t Tickstart)
{
    while (__MID_SPI_GET_FLAG(mSPI, Flag) ==0)
    {
        if (Timeout != MID_MAX_DELAY)
        {
            if ((Timeout == 0U) || ((MID_GetTick() - Tickstart) >= Timeout))
            {
                /* Disable the SPI and reset the CRC: the CRC value should be cleared
                on both master and slave sides in order to resynchronize the master
                and slave for their respective CRC calculation */
                
                // Disable TXE, RXNE and ERR interrupts for the interrupt process
                mSPI->Instance->INT.W = 0x00000000;
                

                mSPI->State = MID_SPI_STATE_READY;
                
                /* Process Unlocked */
                __MID_UNLOCK(mSPI);
                
                return MID_TIMEOUT;
            }
        }
    }

    return MID_OK;
}


/**
 *******************************************************************************
 * @brief       Handle SPI FIFO Communication Timeout
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @param[in]   Fifo Fifo to check
 * @param[in]   State Fifo state to check
 * @param[in]   Timeout Timeout duration
 * @param[in]   Tickstart tick start value
 * @return      MID status
 * @note
 * @par         Example
 * @code
    if (SPI_WaitFifoStateUntilTimeout(mSPI, SPI_FLAG_RXLVL, SPI_RXLVL_EMPTY, SPI_DEFAULT_TIMEOUT, MID_GetTick()) != MID_OK)
 * @endcode
 *******************************************************************************
 */
static MID_StatusTypeDef SPI_WaitFifoStateUntilTimeout(SPI_HandleTypeDef *mSPI, uint32_t Fifo, uint32_t State,
                                                       uint32_t Timeout, uint32_t Tickstart)
{
    __IO uint8_t tmpreg;


    // When RXLVL not empty
    while ((mSPI->Instance->STA.W & Fifo) != State)
    {
        // When RDAT and RX shadow buffer not empty
        if ((Fifo == SPI_FLAG_RXLVL) && (State == SPI_RXLVL_EMPTY))
        {
            // Store TDAT
            tmpreg = *((__IO uint8_t *)&mSPI->Instance->RDAT.W);
            /* To avoid GCC warning */
            UNUSED(tmpreg);
        }
        
        // When timeout not happened)
        if (Timeout != MID_MAX_DELAY)
        {
            // When timeout happened
            if ((Timeout == 0U) || ((MID_GetTick() - Tickstart) >= Timeout))
            {
                // Disable all interrupts for the interrupt process
                mSPI->Instance->INT.W = 0x00000000;

                // When master and not standard SPI
                if (((mSPI->Init.Mode & SPI_MDS_MASK) != 0) && (mSPI->Init.DataLine != SPI_STANDARD_SPI))
                {
                    // Disable SPI peripheral
                    __MID_SPI_DISABLE(mSPI);
                }

                mSPI->State = MID_SPI_STATE_READY;

                /* Process Unlocked */
                __MID_UNLOCK(mSPI);

                
                return MID_TIMEOUT;
            }
        }
    }

  return MID_OK;
}


/**
 *******************************************************************************
 * @brief       Handle the check of the RXTX or TX transaction complete.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @param[in]   Timeout Timeout duration
 * @param[in]   Tickstart tick start value
 * @return      MID status
 * @note
 * @par         Example
 * @code
    if (SPI_EndRxTxTransaction(mSPI, SPI_DEFAULT_TIMEOUT, MID_GetTick()) != MID_OK)
 * @endcode
 *******************************************************************************
 */
static MID_StatusTypeDef SPI_EndRxTxTransaction(SPI_HandleTypeDef *mSPI, uint32_t Timeout, uint32_t Tickstart)
{
    // Control if the TX fifo is empty
    if(SPI_WaitFlagStateUntilTimeout( mSPI, mSPI->SPI_FLAG_TCF, mSPI->SPI_FLAG_TCF , Timeout , Tickstart) != MID_OK)
    {
        SET_BIT(mSPI->ErrorCode, MID_SPI_ERROR_FLAG);
    }
    else
    {   // Clear flag SPI TCF and TXF
        WRITE_REG(mSPI->Instance->STA.W , (mSPI->SPI_FLAG_TCF | SPI_FLAG_TXF));
    }
    
    // When RXF happened or RXLVL not empty
    while( (mSPI->Instance->STA.W & SPI_FLAG_RXF) || ((*(mSPI->RXTX_LVL)) & SPI_FLAG_RXLVL)!=0)
    {
        // When RX shadow buffer not empty
        if( mSPI->RxXferCount!=0)
        {
            // Receive data in 32 Bit mode
            if(mSPI->Init.DataSize > SPI_DATASIZE_16BIT)
            {
                *(mSPI->pRxBuffPtr.point32) = mSPI->Instance->RDAT.W;
                mSPI->pRxBuffPtr.point8 += sizeof(uint32_t);
                mSPI->RxXferCount--;
            }
            // Receive data in 16 Bit mode
            else if (mSPI->Init.DataSize > SPI_DATASIZE_8BIT)
            {
                *(mSPI->pRxBuffPtr.point16) = mSPI->Instance->RDAT.H[0];
                mSPI->pRxBuffPtr.point8 += sizeof(uint16_t);
                mSPI->RxXferCount--;
            }
            // Receive data in 8 Bit mode
            else 
            {
                (*mSPI->pRxBuffPtr.point8) = mSPI->Instance->RDAT.B[0];
                mSPI->pRxBuffPtr.point8 += sizeof(uint8_t);
                mSPI->RxXferCount--;
            }
        }
        else
        {
            __MID_SPI_CLEAR_RXDATA(mSPI);
        }
    }
    
    // Clear error flag
    if(mSPI->REG_TYPE == MID_SPI_SPI)
        WRITE_REG(mSPI->Instance->STA.W , (mSPI->SPI_FLAG_ROVRF | mSPI->SPI_FLAG_TUDRF | SPI_FLAG_MODF | SPI_FLAG_WEF | mSPI->SPI_FLAG_IDLF));
    if(mSPI->REG_TYPE == MID_SPI_URT)
        WRITE_REG(mSPI->Instance->STA.W , (mSPI->SPI_FLAG_ROVRF | mSPI->SPI_FLAG_TUDRF));
    
    return(MID_OK);
}

 
/**
 *******************************************************************************
 * @brief       Handle the check of the RX transaction complete.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @param[in]   Timeout: Timeout duration
 * @param[in]   Tickstart tick start value
 * @return      MID status
 * @note
 * @par         Example
 * @code
    if(SPI_EndRxTransaction(mSPI, Timeout, tickstart) != MID_OK)
 * @endcode
 *******************************************************************************
 */
static MID_StatusTypeDef SPI_EndRxTransaction(SPI_HandleTypeDef *mSPI,  uint32_t Timeout, uint32_t Tickstart)
{
    
    /* Control if the TX fifo is empty */
    // When SPI data lines is standard SPI and X-line data output
    if( mSPI->REG_TYPE == MID_SPI_SPI)
    {
        if(((mSPI->Instance->CR2.B[0] & SPI_CR2_DAT_LINE_mask_b0) == 0) || 
            (mSPI->Instance->CR2.B[0] & SPI_CR2_BDIR_OE_mask_b0) != 0)
        {
            if(SPI_WaitFlagStateUntilTimeout( mSPI, mSPI->SPI_FLAG_TCF, mSPI->SPI_FLAG_TCF , Timeout , Tickstart) != MID_OK)
            {
                SET_BIT(mSPI->ErrorCode, MID_SPI_ERROR_FLAG);
            }
            else
            {
                WRITE_REG(mSPI->Instance->STA.W , (mSPI->SPI_FLAG_TCF | SPI_FLAG_TXF));
            }
        }
    }
    else if( ((mSPI->Init.Mode & SPI_MDS_MASK) == SPI_MODE_MASTER) && (mSPI->Init.DataLine == SPI_STANDARD_SPI) )
    {
        if(SPI_WaitFlagStateUntilTimeout( mSPI, mSPI->SPI_FLAG_TCF, mSPI->SPI_FLAG_TCF , Timeout , Tickstart) != MID_OK)
        {
            SET_BIT(mSPI->ErrorCode, MID_SPI_ERROR_FLAG);
        }
        else
        {
            WRITE_REG(mSPI->Instance->STA.W , (mSPI->SPI_FLAG_TCF | SPI_FLAG_TXF));
        }
    }
    
    while( (mSPI->Instance->STA.W & SPI_FLAG_RXF) || ((*(mSPI->RXTX_LVL)) & SPI_FLAG_RXLVL)!=0)
    {
        if( mSPI->RxXferCount!=0)
        {
            /* Receive data in 32 Bit mode */
            if(mSPI->Init.DataSize > SPI_DATASIZE_16BIT)
            {
                *(mSPI->pRxBuffPtr.point32++) = mSPI->Instance->RDAT.W;
                mSPI->RxXferCount--;                            /* Debug */
            }
            /* Receive data in 16 Bit mode */
            else if (mSPI->Init.DataSize > SPI_DATASIZE_8BIT)
            {
                *(mSPI->pRxBuffPtr.point16++) = mSPI->Instance->RDAT.H[0];
                mSPI->RxXferCount--;                            /* Debug */
            }
            /* Receive data in 16 Bit mode */
            else 
            {
                (*mSPI->pRxBuffPtr.point8++) = mSPI->Instance->RDAT.B[0];
                mSPI->RxXferCount--;
            }
        }
        else if(mSPI->REG_TYPE == MID_SPI_SPI)
        {
            __MID_SPI_CLEAR_RXDATA(mSPI);
        }

    }
    
    // Clear error flag
    if(mSPI->REG_TYPE == MID_SPI_SPI)
        WRITE_REG(mSPI->Instance->STA.W , (mSPI->SPI_FLAG_ROVRF | mSPI->SPI_FLAG_TUDRF | SPI_FLAG_MODF | SPI_FLAG_WEF | mSPI->SPI_FLAG_IDLF));
    if(mSPI->REG_TYPE == MID_SPI_URT)
        WRITE_REG(mSPI->Instance->STA.W , (mSPI->SPI_FLAG_ROVRF | mSPI->SPI_FLAG_TUDRF));
    
    return(MID_OK);
} 


/**
 *******************************************************************************
 * @brief       Handle RX and TX end transaction
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    SPI_CloseRxTx_ISR(mSPI);
 * @endcode
 *******************************************************************************
 */
static void SPI_CloseRxTx_ISR(SPI_HandleTypeDef *mSPI)
{
    uint32_t tickstart = 0U;

    
    // Init tickstart for timeout managment
    tickstart = MID_GetTick();

    // Disable ERR interrupt
    __MID_SPI_DISABLE_IT(mSPI, mSPI->SPI_FLAG_ERROR);

    // Check the end of the transaction
    if (SPI_EndRxTxTransaction(mSPI, SPI_DEFAULT_TIMEOUT, tickstart) != MID_OK)
    {
        SET_BIT(mSPI->ErrorCode, MID_SPI_ERROR_FLAG);
    }

    // When error happened
    if (mSPI->ErrorCode == MID_SPI_ERROR_NONE)
    {   
        // When standard SPI receive
        if (mSPI->State == MID_SPI_STATE_BUSY_RX)
        {
            mSPI->State = MID_SPI_STATE_READY;
            MID_SPI_RxCpltCallback(mSPI);
        }
        // When standard SPI transmit
        else
        {
            mSPI->State = MID_SPI_STATE_READY;
            MID_SPI_TxRxCpltCallback(mSPI);
        }
    }
    // When error not happened
    else
    {
        mSPI->State = MID_SPI_STATE_READY;
        MID_SPI_ErrorCallback(mSPI);
    }
}


/**
 *******************************************************************************
 * @brief       Handle RX end transaction
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    SPI_CloseRx_ISR(mSPI);
 * @endcode
 *******************************************************************************
 */
static void SPI_CloseRx_ISR(SPI_HandleTypeDef *mSPI)
{
    // Disable RXF and ERR interrupt
    __MID_SPI_DISABLE_IT(mSPI, (SPI_IT_RXF | mSPI->SPI_FLAG_ERROR));

    // Check the end of the transaction
    if (SPI_EndRxTransaction(mSPI, SPI_DEFAULT_TIMEOUT, MID_GetTick()) != MID_OK)
    {
        SET_BIT(mSPI->ErrorCode, MID_SPI_ERROR_FLAG);
    }
    mSPI->State = MID_SPI_STATE_READY;

    // When error happened
    if (mSPI->ErrorCode == MID_SPI_ERROR_NONE)
    {
        MID_SPI_RxCpltCallback(mSPI);
    }
    // When error not happened
    else
    {
        MID_SPI_ErrorCallback(mSPI);
    }
}


/**
 *******************************************************************************
 * @brief       Handle TX end transaction
 * @details  
 * @param[in]   mSPI:
 * 	@arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    SPI_CloseTx_ISR(mSPI);
 * @endcode
 *******************************************************************************
 */
static void SPI_CloseTx_ISR(SPI_HandleTypeDef *mSPI)
{
    uint32_t tickstart = 0U;

    // Init tickstart for timeout management
    tickstart = MID_GetTick();

    // Disable TXF, TCF and ERR interrupt
    __MID_SPI_DISABLE_IT(mSPI, (SPI_IT_TXF | mSPI->SPI_FLAG_TCF | mSPI->SPI_FLAG_ERROR));

    // Check the end of the transaction
    if (SPI_EndRxTxTransaction(mSPI, SPI_DEFAULT_TIMEOUT, tickstart) != MID_OK)
    {
        SET_BIT(mSPI->ErrorCode, MID_SPI_ERROR_FLAG);
    }

    // Clear overrun flag in standard SPI communication mode because received is not read
    if (mSPI->Init.DataLine == SPI_STANDARD_SPI)
    {
        __MID_SPI_CLEAR_ROVRFFLAG(mSPI);
    }

    mSPI->State = MID_SPI_STATE_READY;
    // When error happened
    if (mSPI->ErrorCode != MID_SPI_ERROR_NONE)
    {
        MID_SPI_ErrorCallback(mSPI);
    }
    // When error not happened
    else
    {
        MID_SPI_TxCpltCallback(mSPI);
    }
}

 
/**
 *******************************************************************************
 * @brief       Handle abort a Rx transaction.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    mSPI->RxISR = SPI_AbortRx_ISR;
 * @endcode
 *******************************************************************************
 */
static void SPI_AbortRx_ISR(SPI_HandleTypeDef *mSPI)
{
    __IO uint32_t count;

    /* Disable SPI Peripheral */
    __MID_SPI_DISABLE(mSPI);

    count = SPI_DEFAULT_TIMEOUT * (SystemCoreClock / 24U / 1000U);

    /* Disable TXEIE, RXNEIE and ERRIE(mode fault event, overrun error, TI frame error) interrupts */
    mSPI->Instance->INT.W = ~(SPI_IT_TXF | SPI_IT_RXF | SPI_IT_ERR);

    /* Check RXNEIE is disabled */
    do
    {
        if (count-- == 0U)
        {
            SET_BIT(mSPI->ErrorCode, MID_SPI_ERROR_ABORT);
            break;
        }
    }

    while((mSPI->Instance->INT.W & SPI_IT_RXF) != 0);

    /* Control the BSY flag */
    if (SPI_WaitFlagStateUntilTimeout(mSPI, SPI_FLAG_BUSYF, CLR, SPI_DEFAULT_TIMEOUT, MID_GetTick()) != MID_OK)
    {
        mSPI->ErrorCode = MID_SPI_ERROR_ABORT;
    }

    /* Empty the FRLVL fifo */
    if (SPI_WaitFifoStateUntilTimeout(mSPI, SPI_FLAG_RXLVL, SPI_RXLVL_EMPTY, SPI_DEFAULT_TIMEOUT, MID_GetTick()) != MID_OK)
    {
        mSPI->ErrorCode = MID_SPI_ERROR_ABORT;
    }

    mSPI->State = MID_SPI_STATE_ABORT;
}


/**
 *******************************************************************************
 * @brief       Handle abort a Tx or Rx/Tx transaction.
 * @details  
 * @param[in]   mSPI:
 *  @arg\b          mSPI. mSPI pointer to a SPI_HandleTypeDef structure that 
 *                  contains the configuration information for SPI module.
 * @return      none
 * @note
 * @par         Example
 * @code
    mSPI->TxISR = SPI_AbortTx_ISR;
 * @endcode
 *******************************************************************************
 */
static void SPI_AbortTx_ISR(SPI_HandleTypeDef *mSPI)
{
    __IO uint32_t count;

    count = SPI_DEFAULT_TIMEOUT * (SystemCoreClock / 24U / 1000U);

    /* Disable TXEIE, RXEIE and ERRIE interrupts */
    mSPI->Instance->INT.W &= ~(SPI_IT_TXF | SPI_IT_RXF | SPI_IT_ERR);
    
    /* Check TXEIE is disabled */
    do
    {
        if (count-- == 0U)
        {
            SET_BIT(mSPI->ErrorCode, MID_SPI_ERROR_ABORT);
            break;
        }
    }

    while((mSPI->Instance->INT.W & SPI_IT_TXF) != 0);
    
    if (SPI_EndRxTxTransaction(mSPI, SPI_DEFAULT_TIMEOUT, MID_GetTick()) != MID_OK)
    {
        mSPI->ErrorCode = MID_SPI_ERROR_ABORT;
    }

    /* Disable SPI Peripheral */
    __MID_SPI_DISABLE(mSPI);

    /* Empty the FRLVL fifo */
    if (SPI_WaitFifoStateUntilTimeout(mSPI, SPI_FLAG_RXLVL, SPI_RXLVL_EMPTY, SPI_DEFAULT_TIMEOUT, MID_GetTick()) != MID_OK)
    {
        mSPI->ErrorCode = MID_SPI_ERROR_ABORT;
    }

    mSPI->State = MID_SPI_STATE_ABORT;
}
///@}






