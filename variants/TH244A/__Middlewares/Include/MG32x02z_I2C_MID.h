/**
 ******************************************************************************
 * @file        MG32x02z_I2C_MID.h
 * @brief       Header file of I2C MID module.
 * @par         Project
 *              MG32x02z
 * @version     V1.12
 * @date        2021/04/21
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2020 megawin Technology Co., Ltd.
 *              All rights reserved.
 ******************************************************************************
 * @par         Disclaimer 
 *      The Demo software is provided "AS IS"  without any warranty, either 
 *      expressed or implied, including, but not limited to, the implied warranties 
 *      of merchantability and fitness for a particular purpose.  The author will 
 *      not be liable for any special, incidental, consequential or indirect 
 *      damages due to loss of data or any other reason. 
 *      These statements agree with the world wide and local dictated laws about 
 *      authorship and violence against these laws. 
 ******************************************************************************
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MG32x02z_I2C_MID_H
#define _MG32x02z_I2C_MID_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MG32x02z_Common_MID.h"
#include "MG32x02z_CSC_MID.h"
#include "MG32x02z_DMA_MID.h"
#include "MG32x02z_I2C.h"

#define USE_MID_I2C_REGISTER_CALLBACKS      0
/** @name I2C I2C 
 * @brief I2C MID module driver
 * @{
 */

/* Exported types ------------------------------------------------------------*/
/**
 ******************************************************************************
 * @struct I2C_InitTypeDef
 * @brief  I2C Initial Configuration Structure definition
 ******************************************************************************
 */
typedef struct __attribute__((packed)) {

    uint32_t Timing;              /*!< Specifies the I2C_TIMINGR_register value.
                                    This parameter calculated by referring to I2C initialization
                                           section in Reference manual */

    uint32_t OwnAddress1;         /*!< Specifies the first device own address.
                                    This parameter can be a 7-bit address. */

#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
    uint32_t OwnAddress1Masks;    /*!< Specifies the acknowledge mask address second device own address
                                    This parameter can be a value of reference I2C_OWN_ADDRESS1_MASKS */
#endif

    uint32_t DualAddressMode;     /*!< Specifies if dual addressing mode is selected.
                                    This parameter can be a value of reference I2C_DUAL_ADDRESSING_MODE */

    uint32_t OwnAddress2;         /*!< Specifies the second device own address if dual addressing mode is selected
                                    This parameter can be a 7-bit address. */

    uint32_t GeneralCallMode;     /*!< Specifies if general call mode is selected.
                                    This parameter can be a value of reference I2C_GENERAL_CALL_ADDRESSING_MODE */

}I2C_InitTypeDef;

/**
 ******************************************************************************
 * @name MID_I2C_ModeTypeDef 
 * @brief  MID Mode structure definition
 *        @arg Bit7 Master Transmit Data NACK not Error
 *        @arg Bit[9:8] Master Trnasfer End Type, Repeat Start or Stop, 0:None / 01:RepeatStart / 10:Stop / 11:Stop and Start
 *        @arg Bit[11:10] Operating Mode, 00:None / 01:Master / 10:Slave / MEM
 *        @arg Bit12 Slave Transmit Data transfer use DMA
 *        @arg Bit13 Slave Receive Data transfer use DMA
 *        @arg Bit14 Master Receive Data transfer use DMA
 *        @arg Bit15 Master Transmit Data transfer use DMA
 ******************************************************************************
 */
// typedef enum __attribute__((packed)) {
#define MID_I2C_MODE_NONE                               0x0000UL /*!< No I2C communication on going                         */
#define MID_I2C_MODE_NACKNext                           0x0080UL /*!< I2C NACK Bypasss                                      */
#define MID_I2C_MODE_MASK                               0x0300UL /*!< I2C Transfer End Type, Stop or Start                  */
#define MID_I2C_MODE_STOPSTART                          0x0300UL /*!< I2C Transfer End Type, Stop or Start                  */
#define MID_I2C_MODE_RREPEATSTART                       0x0100UL /*!< I2C Transfer End Type, Repeat Start                   */
#define MID_I2C_MODE_STOP                               0x0200UL /*!< I2C Transfer End Type, Stop                           */
#define MID_I2C_MODE_MASTER                             0x0400UL /*!< I2C communication is in Master Mode                   */
#define MID_I2C_MODE_MASTER_NONE                        0x0000UL /*!<                                                       */
#define MID_I2C_MODE_MASTER_RREPEATSTART                0x0500UL /*!<                                                       */
#define MID_I2C_MODE_MASTER_STOP                        0x0600UL /*!<                                                       */
#define MID_I2C_MODE_SLAVE                              0x0800UL /*!< I2C communication is in Slave Mode                    */
#define MID_I2C_MODE_MEM                                0x0C00UL /*!< I2C communication is in Memory Mode                   */
#define MID_I2C_MODE_DMA_MTX                            0x8000UL /*!< I2C Master Transmit communication use DMA             */
#define MID_I2C_MODE_DMA_MRX                            0x4000UL /*!< I2C Master Receive communication use DMA              */
#define MID_I2C_MODE_DMA_SRX                            0x2000UL /*!< I2C Slave Transmit communication use DMA              */
#define MID_I2C_MODE_DMA_STX                            0x1000UL /*!< I2C Slave Receive communication use DMA               */
#define MID_I2C_MODE_MASTER_TRANSMIT_DMA_STOP           0x8600UL /*!<                                                       */
#define MID_I2C_MODE_MASTER_TRANSMIT_DMA_RREPEATSTART   0x8500UL /*!<                                                       */
#define MID_I2C_MODE_MASTER_RECEIVE_DMA_STOP            0x4600UL /*!<                                                       */
#define MID_I2C_MODE_MASTER_RECEIVE_DMA_RREPEATSTART    0x4500UL /*!<                                                       */
#define MID_I2C_MODE_SLAVE_TRANSMIT_DMA                 0x2800UL /*!<                                                       */
#define MID_I2C_MODE_SLAVE_RECEIVE_DMA                  0x1800UL /*!<                                                       */
// }MID_I2C_ModeTypeDef;

/**
 ******************************************************************************
 * @name MID_I2C_StateTypeDef
 * @brief  MID State structure definition
 *        @arg Bit0 Intrinsic process state
 *        @arg Bit1 Tx state, 0:Ready (no Tx operation ongoing), 1:Busy (Tx operation ongoing).
 *        @arg Bit2 Rx state, 0:Ready (no Tx operation ongoing), 1:Busy (Rx operation ongoing)
 *        @arg Bit3 Address Listen Mode is ongoing
 *        @arg Bit4 Error information
 *        @arg Bit5 Reserved
 *        @arg Bit6 Abort user request ongoing
 *        @arg Bit7 Peripheral initialization status
 ******************************************************************************
 */
//typedef enum{
#define MID_I2C_STATE_RESET             0x00UL         /*!< Peripheral is not yet Initialized                     */
#define MID_I2C_STATE_BUSY              0x01UL         /*!< An internal process is ongoing                        */
#define MID_I2C_STATE_BUSY_TX           0x83UL         /*!< Data Transmission process is ongoing                  */
#define MID_I2C_STATE_BUSY_RX           0x85UL         /*!< Data Reception process is ongoing                     */
#define MID_I2C_STATE_TX                0x02UL         /*!< Address Data Transmission process is ongoing          */
#define MID_I2C_STATE_RX                0x04UL         /*!< Address Data Reception process is ongoing             */
#define MID_I2C_STATE_ABORT             0x08UL         /*!< Abort user request ongoing                            */
#define MID_I2C_STATE_ERROR             0x10UL         /*!< Error                                                 */
#define MID_I2C_STATE_ERROR_TX          0x92UL         /*!< Address Data Transmission process is ongoing          */
#define MID_I2C_STATE_ERROR_RX          0x94UL         /*!< Address Data Transmission process is ongoing          */
#define MID_I2C_STATE_LISTEN            0x20UL         /*!< Address Listen Mode is ongoing                        */
//#define  MID_I2C_STATE_LISTEN_TX        0xA2UL         /*!< Address Listen Mode and Data Transmission process is ongoing */
//#define  MID_I2C_STATE_LISTEN_RX        0xA4UL         /*!< Address Listen Mode and Data Reception process is ongoing */
#define MID_I2C_STATE_READY             0x80UL         /*!< Peripheral Initialized and ready for use              */
//#define  MID_I2C_STATE_TIMEOUT          0x40UL         /*!< Timeout state                                         */
//}MID_I2C_StateTypeDef;

/**
 ******************************************************************************
 * @enum MID_I2C_ErrorTypeDef
 * @brief  I2C Error Code definition
 *        @arg Bit0 Bus error
 *        @arg Bit1 ArbitrationLost error
 *        @arg Bit2 ACKF NACK error
 *        @arg Bit3 Over error
 *        @arg Bit4 DMA transfer error
 *        @arg Bit5 Timeout error
 *        @arg Bit6 DMA Parameter Error
 *        @arg Bit7 Invalid Callback error
 *        @arg Bit8 Invalid Parameters error
 ******************************************************************************
 */
typedef enum __attribute__((packed)) {
    MID_I2C_ERROR_NONE                = 0x0000U,        /*!< No error                                              */
    MID_I2C_ERROR_BERR                = 0x0001U,        /*!< BERR error                                            */
    MID_I2C_ERROR_ARLO                = 0x0002U,        /*!< ARLO error                                            */
    MID_I2C_ERROR_NACKF               = 0x0004U,        /*!< ACKF NACK error                                       */
    MID_I2C_ERROR_UNDER               = 0x0004U,        /*!< Under Issue                                       */
    MID_I2C_ERROR_OVR                 = 0x0008U,        /*!< OVR error                                             */
    MID_I2C_ERROR_DMACH               = 0x0010U,        /*!< DMA transfer error                                    */
    MID_I2C_ERROR_TIMEOUT             = 0x0020U,        /*!< Timeout error                                         */
    MID_I2C_ERROR_DMA_PARAM           = 0x0040U,        /*!< DMA Paramter error                                    */
  #if (USE_MID_I2C_REGISTER_CALLBACKS == 1)
    MID_I2C_ERROR_INVALID_CALLBACK    = 0x0080U,        /*!< Invalid Callback error */
  #endif /* USE_MID_I2C_REGISTER_CALLBACKS */
    MID_I2C_ERROR_INVALID_PARAM       = 0x0100U,        /*!< Invalid Parameters error */
}MID_I2C_ErrorTypeDef;

/**
 ******************************************************************************
 * @struct I2C_HandleTypeDef
 * @brief  I2C handle Structure definition
 ******************************************************************************
 */
typedef struct __attribute__((packed)) tag_I2C_HandleTypeDef{

    I2C_Struct                *Instance;            /*!< I2C registers base address                            */

    I2C_InitTypeDef            Init;                /*!< I2C communication parameters                          */

    __IO uint8_t              *pBuffPtr;            /*!< Pointer to I2C transfer buffer                        */

    __IO uint16_t              DevAddress;          /*!< I2C Target Device Address                             */

    __IO uint32_t              XferSize;            /*!< I2C transfer size                                     */

    __IO uint32_t              XferCount;           /*!< I2C transfer counter                                  */

    MID_StatusTypeDef(*XferISR)(struct tag_I2C_HandleTypeDef *mI2C, uint32_t ITFlags, uint32_t ITSources);
                                                    /*!< I2C transfer IRQ handler function pointer             */

    DMA_HandleTypeDef         *hdmatx;              /*!< I2C Tx DMA handle parameters                          */

    DMA_HandleTypeDef         *hdmarx;              /*!< I2C Rx DMA handle parameters                          */

    MID_LockTypeDef            Lock;                /*!< I2C locking object                                    */

    __IO uint32_t              Mode;                /*!< I2C communication mode refer to  MID_I2C_ModeTypeDef  */

    __IO uint32_t              State;               /*!< I2C communication state refer to MID_I2C_StateTypeDef */

    __IO uint32_t              ErrorCode;           /*!< I2C Error Code @ref MID_I2C_ErrorTypeDef              */
}I2C_HandleTypeDef; /*!< __I2C_HandleTypeDef */

/* Exported constants --------------------------------------------------------*/

/**
 ******************************************************************************
 * @name    I2C_DUAL_ADDRESSING_MODE I2C Dual Addressing Mode
 * @{
 ******************************************************************************
 */
#define I2C_DUALADDRESS_DISABLE         (0x00000000U)                           /*!< Dual Addressing Disable    */
#define I2C_DUALADDRESS_ENABLE          I2C_CR0_SADR2_EN_mask_w                 /*!< Dual Addressing Enable     */
/** @} */

#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
/**
 * @name    I2C_OWN_ADDRESS1_MASKS 
 *              I2C Own Address1 Masks
 * @{
 */
#define I2C_OA1_NOMASK                  ((uint8_t)0xFEU)                        /*!<                            */
#define I2C_OA1_MASK01                  ((uint8_t)0xFCU)                        /*!<                            */
#define I2C_OA1_MASK02                  ((uint8_t)0xF8U)                        /*!<                            */
#define I2C_OA1_MASK03                  ((uint8_t)0xF0U)                        /*!<                            */
#define I2C_OA1_MASK04                  ((uint8_t)0xE0U)                        /*!<                            */
#define I2C_OA1_MASK05                  ((uint8_t)0xC0U)                        /*!<                            */
#define I2C_OA1_MASK06                  ((uint8_t)0x80U)                        /*!<                            */
#define I2C_OA1_MASK07                  ((uint8_t)0x00U)                        /*!<                            */
/** @} */
#endif

/**
 ******************************************************************************
 * @name    I2C_GENERAL_CALL_ADDRESSING_MODE I2C General Call Addressing Mode
 * @{
 ******************************************************************************
 */
#define I2C_GENERALCALL_DISABLE         (0x00000000U)                           /*!< General Call Disable       */
#define I2C_GENERALCALL_ENABLE          I2C_CR0_GC_EN_mask_w                    /*!< General Call Enable        */
/** @} */

/**
 * @name    I2C_MEMORY_ADDRESS_SIZE I2C Memory Address Size
 * @{
 */
#define I2C_MEMADD_SIZE_8BIT            (0x00000001U)                           /*!< Memory Address 8Bit        */
#define I2C_MEMADD_SIZE_16BIT           (0x00000002U)                           /*!< Memory Address 16Bit       */
/** @} */

/**
  * @name   I2C_XFERDIRECTION I2C Transfer Direction Master Point of View
  * @{
  */
#define I2C_DIRECTION_TRANSMIT          (0x00000000U)                           /*!< Transmiter                 */
#define I2C_DIRECTION_RECEIVE           (0x00000001U)                           /*!< Receive                    */
/** @} */

/**
 * @name    I2C_Interrupt_configuration_definition I2C Interrupt configuration definition
 * @brief       I2C Interrupt definition
 *              Elements values convention: 0xXXXXXXXX
 *                  - XXXXXXXX  : Interrupt control mask
 * @{
 */
#define I2C_IT_IEA                      I2C_INT_IEA_mask_w                      /*!< I2C All Interupt           */
#define I2C_IT_EVENT                    I2C_INT_EVENT_IE_mask_w                 /*!< Event Interrupt            */
#define I2C_IT_ERR                      I2C_INT_ERR_IE_mask_w                   /*!< Error Interrupt            */
#define I2C_IT_TMOUT                    I2C_INT_TMOUT_IE_mask_w                 /*!< TimeOut Counter Interrupt  */
#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
  #define I2C_IT_STPSTR                 I2C_INT_STPSTR_IE_mask_w                /*!< Bus Start or Stop Interrupt */
#endif
/** @} */

/**
 * @name    I2C_Flag_definition I2C Flag definition
 * @{
 */
#define I2C_FLAG_BUSY                   I2C_STA_BUSYF_mask_w                    /*!< Busy                       */

#define I2C_FLAG_EVENT                  I2C_STA_EVENTF_mask_w                   /*!< Event                      */

#define I2C_FLAG_BUF                    I2C_STA_BUFF_mask_w                     /*!< BUFF                       */
#define I2C_FLAG_RX                     I2C_STA_RXF_mask_w                      /*!< Receiv buffer full.        */
#define I2C_FLAG_TX                     I2C_STA_TXF_mask_w                      /*!< Transmit buffer empty.     */
#define I2C_FLAG_RSTR                   I2C_STA_RSTRF_mask_w                    /*!< Bus Repeat Start.          */
#define I2C_FLAG_STOP                   I2C_STA_STOPF_mask_w                    /*!< Bus Stop.                  */
#define I2C_FLAG_STPSTR                 I2C_STA_STPSTRF_mask_w                  /*!< Bus Start or Stop          */
#define I2C_FLAG_SADR                   I2C_STA_SADRF_mask_w                    /*!< Master address match / unmatch, Slave address match. */

#define I2C_FLAG_ERR                    I2C_STA_ERRF_mask_w                     /*!< AError                     */
#define I2C_FLAG_BERR                   I2C_STA_BERRF_mask_w                    /*!< Bus Error.                 */
#define I2C_FLAG_ALOS                   I2C_STA_ALOSF_mask_w                    /*!< Arbitration Lost Error     */
#define I2C_FLAG_NACK                   I2C_STA_NACKF_mask_w                    /*!< Not Acknowledge Error      */
#define I2C_FLAG_TOVR                   I2C_STA_TOVRF_mask_w                    /*!< with Stretching disable and Slave Transmit Buffer under. */
#define I2C_FLAG_ROVR                   I2C_STA_ROVRF_mask_w                    /*!< with Stretching disable and Slave Receive Buffer Over. */

#define I2C_FLAG_TMOUT                  I2C_STA_TMOUTF_mask_w                   /*!< Timeout Count              */


#define I2C_FLAG_RW                     I2C_STA_RWF_mask_w                      /*!< 0: MT / SR / SRGC          */
                                                                                /*   1: MR / ST                 */
#define I2C_FLAG_MST                    I2C_STA_MSTF_mask_w                     /*!< Master Mode                */
#define I2C_FLAG_SLA                    I2C_STA_SLAF_mask_w                     /*!< Slave Mode                 */
#define I2C_FLAG_TXR                    I2C_STA_TXRF_mask_w                     /*!< Showdown Buffer            */
#define I2C_FLAG_CNT                    I2C_STA_CNTF_mask_w                     /*!< Buffer Counter             */
#define I2C_FLAG_TSC                    I2C_STA_TSCF_mask_w                     /*!< Shift Buffer               */

#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
  #define I2C_FLAG_WUP                    I2C_STA_WUPF_mask_w                   /*!< Stop Wake-Up               */
#endif
/** @} */

/* Exported macros -----------------------------------------------------------*/
/**
 ******************************************************************************
 * @brief Reset I2C handle state.
 * @param[in]  "__HANDLE__" specifies the I2C Handle.
 * @return None
 ******************************************************************************
 */
#define __DRV_I2C_RESET_HANDLE_STATE(__HANDLE__)                ((__HANDLE__)->State = MID_I2C_STATE_RESET) /*!< State Reset                */

/**
 ******************************************************************************
 * @brief  Enable the specified I2C interrupt.
 * @param  "__HANDLE__" specifies the I2C Handle.
 * @param  "__INTERRUPT__" specifies the interrupt source to enable.
 *        This parameter can be one of the following values:
 *           @arg I2C_IT_IEA    All I2C interrupt enable
 *           @arg I2C_IT_EVENT  Transfer complete interrupt enable
 *           @arg I2C_IT_ERR    Errors interrupt enable
 *           @arg I2C_IT_TMOUT  TimeOut interrupt eanble
 *           @arg I2C_IT_WUP    MCU STOP Mode detection interrupt enable
 *           @arg I2C_IT_STPSTR START / STOP detection interrupt enable
 * @return None
 ******************************************************************************
 */
#define __DRV_I2C_ENABLE_IT(__HANDLE__, __INTERRUPT__)          ((__HANDLE__)->Instance->INT.W |= (__INTERRUPT__))  /*!<                            */

/**
 ******************************************************************************
 * @brief  Disable the specified I2C interrupt.
 * @param  "__HANDLE__" specifies the I2C Handle.
 * @param  "__INTERRUPT__" specifies the interrupt source to disable.
 *        This parameter can be one of the following values:
 *            @arg I2C_IT_IEA    All I2C interrupt enable
 *            @arg I2C_IT_EVENT  Transfer complete interrupt enable
 *            @arg I2C_IT_ERR    Errors interrupt enable
 *            @arg I2C_IT_TMOUT  TimeOut interrupt eanble
 *            @arg I2C_IT_WUP    MCU STOP Mode detection interrupt enable
 *            @arg I2C_IT_STPSTR START / STOP detection interrupt enable
 * @return None
 ******************************************************************************
 */
#define __DRV_I2C_DISABLE_IT(__HANDLE__, __INTERRUPT__)         ((__HANDLE__)->Instance->INT.W &= (~(__INTERRUPT__)))   /*!<                            */

/**
 ******************************************************************************
 * @brief  Check whether the specified I2C interrupt source is enabled or not.
 * @param  "__HANDLE__" specifies the I2C Handle.
 * @param  "__INTERRUPT__" specifies the I2C interrupt source to check.
 *          This parameter can be one of the following values:
 *            @arg I2C_IT_IEA    All I2C interrupt enable
 *            @arg I2C_IT_EVENT  Transfer complete interrupt enable
 *            @arg I2C_IT_ERR    Errors interrupt enable
 *            @arg I2C_IT_TMOUT  TimeOut interrupt eanble
 *            @arg I2C_IT_WUP    MCU STOP Mode detection interrupt enable
 *            @arg I2C_IT_STPSTR START / STOP detection interrupt enable
 * @return The new state of __INTERRUPT__ (SET or RESET).
 ******************************************************************************
 */
#define __DRV_I2C_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)      ((((__HANDLE__)->Instance->INT.W & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET) /*!<                            */

/**
 ******************************************************************************
 * @brief  Check whether the specified I2C flag is set or not.
 * @param  "__HANDLE__" specifies the I2C Handle.
 * @param  "__FLAG__" specifies the flag to check.
 *        This parameter can be one of the following values:
 *            @arg I2C_FLAG_EVENT   Byte Mode status event interrupt Flag.
 *            @arg I2C_FLAG_BUF     Buffer mode event flag.
 *            @arg I2C_FLAG_RX      Receive data register not empty
 *            @arg I2C_FLAG_TX      Transmit data register empty 
 *            @arg I2C_FLAG_RSTR    Output Repeat start asserted flag
 *            @arg I2C_FLAG_STOP    Output Stop detection flag
 *            @arg I2C_FLAG_SADR    Address matched / unmatched
 *            @arg I2C_FLAG_ERR     Error interrupt
 *            @arg I2C_FLAG_BERR    Bus error flag for invalid Stop/Start state
 *            @arg I2C_FLAG_ALOS    Bus arbitration lost
 *            @arg I2C_FLAG_NACK    Not Acknowledge received error
 *            @arg I2C_FLAG_TOVR    Transmit underrun
 *            @arg I2C_FLAG_ROVR    Receive overrun
 *            @arg I2C_FLAG_TMOUT   Time-out detect
 *            @arg I2C_FLAG_BUSY    I2C HW Busy
 *            @arg I2C_FLAG_RW      Read or write transfer direction status
 *            @arg I2C_FLAG_MST     Master mode detection status
 *            @arg I2C_FLAG_SLA     Slave address matched condition and clear by Start/Stop conditions.
 *            @arg I2C_FLAG_TXR     Transmit data register empty.
 *            @arg I2C_FLAG_CNT     Count I2C0_BUF_CNT empty status.
 *            @arg I2C_FLAG_TSC     Shadow buffer transfer complete flag.
 *            @arg I2C_FLAG_WUP     Wakeup from STOP mode flag.
 *            @arg I2C_FLAG_STPSTR  Stop or Start detection flag.
 * @return The new state of __FLAG__ (SET or RESET).
 ******************************************************************************
 */
#define __DRV_I2C_GET_FLAG(__HANDLE__, __FLAG__) (((((__HANDLE__)->Instance->STA.W) & (__FLAG__)) == (__FLAG__)) ? SET : CLR)   /*!<                            */

/**
 ******************************************************************************
 * @brief  Clear the I2C pending flags which are cleared by writing 1 in a specific bit.
 * @param  "__HANDLE__" specifies the I2C Handle.
 * @param  "__FLAG__" specifies the flag to clear.
 *          This parameter can be any combination of the following values:
 *            @arg I2C_FLAG_EVENT   Byte Mode status event interrupt Flag.
 *            @arg I2C_FLAG_BUF     Buffer mode event flag.
 *            @arg I2C_FLAG_RX      Receive data register not empty
 *            @arg I2C_FLAG_TX      Transmit data register empty 
 *            @arg I2C_FLAG_RSTR    Output Repeat start asserted flag
 *            @arg I2C_FLAG_STOP    Output Stop detection flag
 *            @arg I2C_FLAG_SADR    Address matched / unmatched
 *            @arg I2C_FLAG_ERR     Error interrupt
 *            @arg I2C_FLAG_BERR    Bus error flag for invalid Stop/Start state
 *            @arg I2C_FLAG_ALOS    Bus arbitration lost
 *            @arg I2C_FLAG_NACK    Not Acknowledge received error
 *            @arg I2C_FLAG_TOVR    Transmit underrun
 *            @arg I2C_FLAG_ROVR    Receive overrun
 *            @arg I2C_FLAG_TMOUT   Time-out detect
 *            @arg I2C_FLAG_BUSY    I2C HW Busy
 *            @arg I2C_FLAG_RW      Read or write transfer direction status
 *            @arg I2C_FLAG_MST     Master mode detection status
 *            @arg I2C_FLAG_SLA     Slave address matched condition and clear by Start/Stop conditions.
 *            @arg I2C_FLAG_TXR     Transmit data register empty.
 *            @arg I2C_FLAG_CNT     Count I2C0_BUF_CNT empty status.
 *            @arg I2C_FLAG_TSC     Shadow buffer transfer complete flag.
 *            @arg I2C_FLAG_WUP     Wakeup from STOP mode flag.
 *            @arg I2C_FLAG_STPSTR  Stop or Start detection flag.
 * @return None
 ******************************************************************************
 */
#define __DRV_I2C_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->STA.W = (__FLAG__))

/**
 ******************************************************************************
 * @brief  Enable the specified I2C peripheral.
 * @param  "__HANDLE__" specifies the I2C Handle.
 * @return None
 ******************************************************************************
 */
#define __DRV_I2C_ENABLE(__HANDLE__)                            ((__HANDLE__)->Instance->CR0.W |= I2C_CR0_EN_mask_w)

/**
 ******************************************************************************
 * @brief  Disable the specified I2C peripheral.
 * @param  "__HANDLE__" specifies the I2C Handle.
 * @return None
 ******************************************************************************
 */
#define __DRV_I2C_DISABLE(__HANDLE__)                           ((__HANDLE__)->Instance->CR0.W &= (~I2C_CR0_EN_mask_w))

/**
 ******************************************************************************
 * @brief  Generate a Non-Acknowledge I2C peripheral in Master and Slave mode.
 * @param  "__HANDLE__": specifies the I2C Handle.
 * @return None
 * @{
 ******************************************************************************
 */
#define __DRV_I2C_GENERATE_NACK(__HANDLE__)                     ((__HANDLE__)->Instance->CR2.B[0] = (((__HANDLE__)->Instance->CR2.B[0] & ~I2C_CR2_AA_mask_b0) | I2C_CR2_AA_LCK_mask_b0))    /*!< Non-Acknowledge            */
#define __DRV_I2C_AA_0(__HANDLE__)                              ((__HANDLE__)->Instance->CR2.B[0] = I2C_CR2_AA_LCK_mask_b0)                                                                 /*!< Non-Acknowledge            */
#define __DRV_I2C_AA_1(__HANDLE__)                              ((__HANDLE__)->Instance->CR2.B[0] = (I2C_CR2_AA_mask_b0 | I2C_CR2_AA_LCK_mask_b0))                                          /*!< Acknowledge                */
#define __DRV_I2C_PAA_0(__HANDLE__)                             ((__HANDLE__)->Instance->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_AA_LCK_mask_b0))                                      /*!< Set Pre Non-Acknowledge    */
#define __DRV_I2C_PAA_1(__HANDLE__)                             ((__HANDLE__)->Instance->CR2.B[0] = (I2C_CR2_AA_mask_b0 | I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_AA_LCK_mask_b0))                 /*!< Set Pre Acknowledge        */
/** @} */

/**
 ******************************************************************************
 * @brief  Generate a Bus Start I2C peripheral in Master mode.
 * @param  "__HANDLE__": specifies the I2C Handle.
 * @return None
 * @{
 ******************************************************************************
 */
#define __DRV_I2C_STA_0(__HANDLE__)                             ((__HANDLE__)->Instance->CR2.B[0] = I2C_CR2_STA_LCK_mask_b0)                                                               /*!< Clear Bus START Bit        */
#define __DRV_I2C_STA_1(__HANDLE__)                             ((__HANDLE__)->Instance->CR2.B[0] = (I2C_CR2_STA_mask_b0 | I2C_CR2_STA_LCK_mask_b0))                                       /*!< Set Bus START Bit          */
#define __DRV_I2C_PSTA_0(__HANDLE__)                            ((__HANDLE__)->Instance->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0))                                    /*!< Clear Bus START Pre Bit    */
#define __DRV_I2C_PSTA_1(__HANDLE__)                            ((__HANDLE__)->Instance->CR2.B[0] = (I2C_CR2_STA_mask_b0 | I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0))              /*!< Set Bus START Pre Bit      */
/** @} */

/**
 ******************************************************************************
 * @brief  Generate a Bus Stop I2C peripheral in Master mode.
 * @param  "__HANDLE__": specifies the I2C Handle.
 * @return None
 * @{
 ******************************************************************************
 */
#define __DRV_I2C_GENERATE_STOP(__HANDLE__)                     ((__HANDLE__)->Instance->CR2.B[0] = (((__HANDLE__)->Instance->CR2.B[0] & ~I2C_CR2_STO_mask_b0) | I2C_CR2_STO_LCK_mask_b0)) /*!< Set Bus STOP Bit          */
#define __DRV_I2C_STO_0(__HANDLE__)                             ((__HANDLE__)->Instance->CR2.B[0] = I2C_CR2_STO_LCK_mask_b0)                                                               /*!< Clear Bus STOP Bit        */
#define __DRV_I2C_STO_1(__HANDLE__)                             ((__HANDLE__)->Instance->CR2.B[0] = (I2C_CR2_STO_mask_b0 | I2C_CR2_STO_LCK_mask_b0))                                       /*!< Set Bus STOP Bit          */
#define __DRV_I2C_PSTO_0(__HANDLE__)                            ((__HANDLE__)->Instance->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STO_LCK_mask_b0))                                    /*!< Clear Bus STOP Pre Bit    */
#define __DRV_I2C_PSTO_1(__HANDLE__)                            ((__HANDLE__)->Instance->CR2.B[0] = (I2C_CR2_STO_mask_b0 | I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STO_LCK_mask_b0))              /*!< Set Bus STOP Pre Bit      */
/** @} */

/**
 ******************************************************************************
 * @brief  Generate a Bus Start / STOP  / NACK, I2C peripheral in Slave or Master mode.
 * @param  "__HANDLE__": specifies the I2C Handle.
 * @return None
 * @{
 ******************************************************************************
 */
#define __DRV_I2C_PSTA_PSTO_PAA_111(__HANDLE__)                 ((__HANDLE__)->Instance->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STA_mask_b0 | I2C_CR2_STO_mask_b0 | I2C_CR2_AA_mask_b0))     /*!< Synchronize Set and Clear Bus-Start / Bus-Stop / Acknowledge pre Bit */
#define __DRV_I2C_PSTA_PSTO_PAA_110(__HANDLE__)                 ((__HANDLE__)->Instance->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STA_mask_b0 | I2C_CR2_STO_mask_b0))                          /*!< Synchronize Set and Clear Bus-Start / Bus-Stop / Acknowledge pre Bit */
#define __DRV_I2C_PSTA_PSTO_PAA_101(__HANDLE__)                 ((__HANDLE__)->Instance->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STA_mask_b0 | I2C_CR2_AA_mask_b0))                           /*!< Synchronize Set and Clear Bus-Start / Bus-Stop / Acknowledge pre Bit */
#define __DRV_I2C_PSTA_PSTO_PAA_100(__HANDLE__)                 ((__HANDLE__)->Instance->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STA_mask_b0))                                                /*!< Synchronize Set and Clear Bus-Start / Bus-Stop / Acknowledge pre Bit */
#define __DRV_I2C_PSTA_PSTO_PAA_011(__HANDLE__)                 ((__HANDLE__)->Instance->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STO_mask_b0 | I2C_CR2_AA_mask_b0))                           /*!< Synchronize Set and Clear Bus-Start / Bus-Stop / Acknowledge pre Bit */
#define __DRV_I2C_PSTA_PSTO_PAA_010(__HANDLE__)                 ((__HANDLE__)->Instance->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STO_mask_b0))                                                /*!< Synchronize Set and Clear Bus-Start / Bus-Stop / Acknowledge pre Bit */
#define __DRV_I2C_PSTA_PSTO_PAA_001(__HANDLE__)                 ((__HANDLE__)->Instance->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_AA_mask_b0))                                                 /*!< Synchronize Set and Clear Bus-Start / Bus-Stop / Acknowledge pre Bit */
#define __DRV_I2C_PSTA_PSTO_PAA_000(__HANDLE__)                 ((__HANDLE__)->Instance->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0))                                                                      /*!< Synchronize Set and Clear Bus-Start / Bus-Stop / Acknowledge pre Bit */

#define __DRV_I2C_STA_STO_AA_111(__HANDLE__)                    ((__HANDLE__)->Instance->CR2.B[0] = (I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STA_mask_b0 | I2C_CR2_STO_mask_b0 | I2C_CR2_AA_mask_b0))                              /*!< Synchronize Set and Clear Bus-Start / Bus-Stop / Acknowledge Bit */
#define __DRV_I2C_STA_STO_AA_110(__HANDLE__)                    ((__HANDLE__)->Instance->CR2.B[0] = (I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STA_mask_b0 | I2C_CR2_STO_mask_b0))                                                   /*!< Synchronize Set and Clear Bus-Start / Bus-Stop / Acknowledge Bit */
#define __DRV_I2C_STA_STO_AA_101(__HANDLE__)                    ((__HANDLE__)->Instance->CR2.B[0] = (I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STA_mask_b0 | I2C_CR2_AA_mask_b0))                                                    /*!< Synchronize Set and Clear Bus-Start / Bus-Stop / Acknowledge Bit */
#define __DRV_I2C_STA_STO_AA_100(__HANDLE__)                    ((__HANDLE__)->Instance->CR2.B[0] = (I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STA_mask_b0))                                                                         /*!< Synchronize Set and Clear Bus-Start / Bus-Stop / Acknowledge Bit */
#define __DRV_I2C_STA_STO_AA_011(__HANDLE__)                    ((__HANDLE__)->Instance->CR2.B[0] = (I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STO_mask_b0 | I2C_CR2_AA_mask_b0))                                                    /*!< Synchronize Set and Clear Bus-Start / Bus-Stop / Acknowledge Bit */
#define __DRV_I2C_STA_STO_AA_010(__HANDLE__)                    ((__HANDLE__)->Instance->CR2.B[0] = (I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STO_mask_b0))                                                                         /*!< Synchronize Set and Clear Bus-Start / Bus-Stop / Acknowledge Bit */
#define __DRV_I2C_STA_STO_AA_001(__HANDLE__)                    ((__HANDLE__)->Instance->CR2.B[0] = (I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_AA_mask_b0))                                                                          /*!< Synchronize Set and Clear Bus-Start / Bus-Stop / Acknowledge Bit */
#define __DRV_I2C_STA_STO_AA_000(__HANDLE__)                    ((__HANDLE__)->Instance->CR2.B[0] = (I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0))                                                                                               /*!< Synchronize Set and Clear Bus-Start / Bus-Stop / Acknowledge Bit */
/** @} */

/**
 ******************************************************************************
 * @brief  Other Control, I2C peripheral in Slave or Master mode.
 * @param  "__HANDLE__": specifies the I2C Handle.
 * @return None
 * @{
 ******************************************************************************
 */
#define __DRV_I2C_WAIT_BusSTOP(__HANDLE__)                      while(((__HANDLE__)->Instance->CR2.B[0] & I2C_CR2_STO_mask_b0) != 0)        /*!< Master Mode Wait Output Bus-Stop */
#define __DRV_I2C_WAIT_EVENT_FLAG(__HANDLE__)                   while(((__HANDLE__)->Instance->STA2.B[1] & I2C_STA2_EVENTF2_mask_b1) == 0)  /*!< Polling Event Flag Set */
#define __DRV_I2C_CLEAR_EVENT_FLAG(__HANDLE__)                  ((__HANDLE__)->Instance->STA2.B[1] = I2C_STA2_EVENTF2_mask_b1)              /*!< Clear Event Flag Set */
#define __DRV_I2C_GET_EVENTCODE(__HANDLE__)                     ((__HANDLE__)->Instance->STA2.B[0] & 0xF8)                                  /*!< Get Event State Code */

#define __DRV_I2C_WRITE_SBUF(__HANDLE__, __DATA__)              ((__HANDLE__)->Instance->SBUF.B[0] = (__DATA__))                            /*!< Write Shift Buffer */
#define __DRV_I2C_READ_SBUF(__HANDLE__)                         ((__HANDLE__)->Instance->SBUF.B[0])                                         /*!< Read Shift Buffer */

#define I2C_GET_ADDR_MATCH(__HANDLE__)            (((__HANDLE__)->Instance->SAC & 0xF8) >> 16U)                                             /*!< Get Match Own Address */
#define I2C_GET_OWN_ADDRESS1(__HANDLE__)          ((__HANDLE__)->Instance->OAR1 & I2C_OAR1_OA1)                                             /*!< Get Own Address1 */
#define I2C_GET_OWN_ADDRESS2(__HANDLE__)          ((__HANDLE__)->Instance->OAR2 & I2C_OAR2_OA2)                                             /*!< Get Own Address2 */

#define I2C_MEM_ADD_MSB(__ADDRESS__)              ((uint8_t)((uint16_t)(((uint16_t)((__ADDRESS__) & (uint16_t)(0xFF00U))) >> 8U)))          /*!< Memory Address MSB First */
#define I2C_MEM_ADD_LSB(__ADDRESS__)              ((uint8_t)((uint16_t)((__ADDRESS__) & (uint16_t)(0x00FFU))))                              /*!< Memory Address LSB First */
/** @} */

/* Include I2C HAL Extended module */
#include "MG32x02z_I2C_MID_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @name   I2C_Exported_Functions I2C Exported Functions
 * @{
 */

/**
 ******************************************************************************
 * @name    I2C_Exported_Functions_Group1 Initialization and de-initialization functions
 * @{
 ******************************************************************************
 */
/* Initialization and de-initialization functions******************************/
uint32_t MID_I2C_GetInitTiming(I2C_HandleTypeDef *mI2C, uint32_t SCLClock);
MID_StatusTypeDef MID_I2C_Init(I2C_HandleTypeDef *mI2C);
// MID_StatusTypeDef MID_I2C_DeInit (I2C_HandleTypeDef *mI2C);
void MID_I2C_MspInit(I2C_HandleTypeDef *mI2C);
void MID_I2C_MspDeInit(I2C_HandleTypeDef *mI2C);
/**
 * @}
 */

/**
 ******************************************************************************
 * @name    I2C_Exported_Functions_Group2 Input and Output operation functions
 * @{
 ******************************************************************************
 */
/* IO operation functions ****************************************************/
 /******* Blocking mode: Polling */
MID_StatusTypeDef MID_I2C_IsDeviceReady(I2C_HandleTypeDef *mI2C, uint16_t DevAddress, uint32_t Trials, uint32_t Timeout);
MID_StatusTypeDef MID_I2C_Master_Transmit(I2C_HandleTypeDef *mI2C, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
MID_StatusTypeDef MID_I2C_Master_Transmit_RepeatStart(I2C_HandleTypeDef *mI2C, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
MID_StatusTypeDef MID_I2C_Master_Receive(I2C_HandleTypeDef *mI2C, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
MID_StatusTypeDef MID_I2C_Slave_Transmit(I2C_HandleTypeDef *mI2C, uint8_t *pData, uint16_t Size, uint32_t Timeout);
MID_StatusTypeDef MID_I2C_Slave_Receive(I2C_HandleTypeDef *mI2C, uint8_t *pData, uint16_t Size, uint32_t Timeout);
MID_StatusTypeDef MID_I2C_Mem_Write(I2C_HandleTypeDef *mI2C, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
MID_StatusTypeDef MID_I2C_Mem_Read(I2C_HandleTypeDef *mI2C, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);

 /******* Non-Blocking mode: Interrupt */
MID_StatusTypeDef MID_I2C_Master_Transmit_IT(I2C_HandleTypeDef *mI2C, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
MID_StatusTypeDef MID_I2C_Master_Transmit_RepeatStart_IT(I2C_HandleTypeDef *mI2C, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
MID_StatusTypeDef MID_I2C_Master_Receive_IT(I2C_HandleTypeDef *mI2C, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
MID_StatusTypeDef MID_I2C_Slave_Transmit_IT(I2C_HandleTypeDef *mI2C, uint8_t *pData, uint16_t Size);
MID_StatusTypeDef MID_I2C_Slave_Receive_IT(I2C_HandleTypeDef *mI2C, uint8_t *pData, uint16_t Size);
MID_StatusTypeDef MID_I2C_Mem_Write_IT(I2C_HandleTypeDef *mI2C, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
MID_StatusTypeDef MID_I2C_Mem_Read_IT(I2C_HandleTypeDef *mI2C, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);


/**
 * @}
 */

/**
 ******************************************************************************
 * @name    I2C_IRQ_Handler_and_Callbacks 
 *              IRQ Handler and Callbacks
 * @{
 ******************************************************************************
 */
/******* I2C IRQHandler and Callbacks used in non blocking modes (Interrupt and DMA) */
void MID_I2C_IRQHandler(I2C_HandleTypeDef *mI2C);
void MID_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *mI2C);
void MID_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *mI2C);
void MID_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *mI2C);
void MID_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *mI2C);
void MID_I2C_AddrCallback(I2C_HandleTypeDef *mI2C, uint8_t TransferDirection, uint16_t AddrMatchCode);
void MID_I2C_ErrorCallback(I2C_HandleTypeDef *mI2C);
/**
 * @}
 */

/**
 ******************************************************************************
 * @name    I2C_Exported_Functions_Group3 Peripheral State, Mode and Error functions
 * @{
 ******************************************************************************
 */
/* Peripheral State, Mode and Error functions *********************************/
uint32_t MID_I2C_GetMode(I2C_HandleTypeDef *mI2C);
uint32_t MID_I2C_GetState(I2C_HandleTypeDef *mI2C);
uint32_t MID_I2C_GetError(I2C_HandleTypeDef *mI2C);

/**
 * @}
 */

/** 
 * @}
 */

/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/

/**
 * @brief  Parameter check
 * @{
 */
/****************************** I2C Instances *********************************/
#if defined(MG32_1ST) || defined(MG32_3RD) || defined(MG32_4TH)
  #define IS_I2C_ALL_INSTANCE(INSTANCE) (((INSTANCE) == I2C0) || \
                                         ((INSTANCE) == I2C1))
#elif defined(MG32_2ND)
  #define IS_I2C_ALL_INSTANCE(INSTANCE) ((INSTANCE) == I2C0)
#endif

/****************** I2C Instances : wakeup capability from stop modes *********/
#if defined(MG32_2ND)
  #define IS_I2C_WAKEUP_FROMSTOP_INSTANCE(INSTANCE) ((INSTANCE) == I2C0)
#elif defined(MG32_3RD) || defined(MG32_4TH)
  #define IS_I2C_WAKEUP_FROMSTOP_INSTANCE(INSTANCE) (((INSTANCE) == I2C0) || \
                                                     ((INSTANCE) == I2C1))
#endif

#define IS_I2C_ADDRESSING_MODE(MODE)    ((MODE) == I2C_ADDRESSINGMODE_7BIT)

#define IS_I2C_DUAL_ADDRESS(ADDRESS)    (((ADDRESS) == I2C_DUALADDRESS_DISABLE) || \
                                         ((ADDRESS) == I2C_DUALADDRESS_ENABLE)) /*!< DUAL_ADDRESS Parameter check */

#define IS_I2C_OWN_ADDRESS1_MASK(MASK)  (((MASK) == I2C_OA1_NOMASK)  || \
                                         ((MASK) == I2C_OA1_MASK01) || \
                                         ((MASK) == I2C_OA1_MASK02) || \
                                         ((MASK) == I2C_OA1_MASK03) || \
                                         ((MASK) == I2C_OA1_MASK04) || \
                                         ((MASK) == I2C_OA1_MASK05) || \
                                         ((MASK) == I2C_OA1_MASK06) || \
                                         ((MASK) == I2C_OA1_MASK07))            /*!< OWN_ADDRESS1 Parameter check */

#define IS_I2C_GENERAL_CALL(CALL)       (((CALL) == I2C_GENERALCALL_DISABLE) || \
                                         ((CALL) == I2C_GENERALCALL_ENABLE))    /*!< GENERAL_CALL Parameter check */

#define IS_I2C_MEMADD_SIZE(SIZE)        (((SIZE) == I2C_MEMADD_SIZE_8BIT) || \
                                         ((SIZE) == I2C_MEMADD_SIZE_16BIT))     /*!< MEMADD_SIZE Parameter check */

#define IS_TRANSFER_MODE(MODE)           ((MODE) == I2C_SOFTEND_MODE)           /*!< TRANSFER_MODE Parameter check */

#define IS_I2C_OWN_ADDRESS1(ADDRESS1)             ((ADDRESS1) <= 0x000000FFU)   /*!< OWN_ADDRESS1 Parameter check */
#define IS_I2C_OWN_ADDRESS2(ADDRESS2)             ((ADDRESS2) <= (uint16_t)0x00FFU)  /*!< OWN_ADDRESS2 Parameter check */

/**
 * @brief  Other I2C peripheral.
 */
#define I2C_TIMING_CLEAR_MASK   ((uint32_t)0xFFFFFFFFU)  /*!< I2C TIMING clear register Mask */
#define I2C_TIMEOUT_BUSY        ((uint32_t)25U)          /*!< 25 ms */
#define I2C_TIMEOUT_FLAG        ((uint32_t)25U)          /*!< 25 ms */

/** @} */

/* Private Functions ---------------------------------------------------------*/

/** @name   I2C_Private_Functions
 * @{
 */
MID_StatusTypeDef MID_I2C_DeInit(I2C_HandleTypeDef *mI2C);

/** 
 * @}
 */

/** 
 * @}
 */




#if 1
/**
 * @brief  I2C Internal define
*/
#define I2C_TIMING_CLEAR_MASK       ((uint32_t)0xFFFFFFFFU)  /*!< I2C TIMING clear register Mask */
#define I2C_TIMEOUT_BUSY            ((uint32_t)25U)          /*!< 25 ms */
#define I2C_TIMEOUT_FLAG            ((uint32_t)25U)          /*!< 25 ms */

/* Private define for reference PreviousState usage */
#define I2C_STATE_MSK               ((uint32_t)((MID_I2C_STATE_BUSY_TX | MID_I2C_STATE_BUSY_RX) & (~MID_I2C_STATE_READY))) /*!< Mask State define, keep only RX and TX bits           */
#define I2C_STATE_NONE              ((uint32_t)(MID_I2C_MODE_NONE))                                                        /*!< Default Value                                         */
#define I2C_STATE_MASTER_BUSY_TX    ((uint32_t)((MID_I2C_STATE_BUSY_TX & I2C_STATE_MSK) | MID_I2C_MODE_MASTER))            /*!< Master Busy TX, combinaison of State LSB and Mode enum */
#define I2C_STATE_MASTER_BUSY_RX    ((uint32_t)((MID_I2C_STATE_BUSY_RX & I2C_STATE_MSK) | MID_I2C_MODE_MASTER))            /*!< Master Busy RX, combinaison of State LSB and Mode enum */
#define I2C_STATE_SLAVE_BUSY_TX     ((uint32_t)((MID_I2C_STATE_BUSY_TX & I2C_STATE_MSK) | MID_I2C_MODE_SLAVE))             /*!< Slave Busy TX, combinaison of State LSB and Mode enum */
#define I2C_STATE_SLAVE_BUSY_RX     ((uint32_t)((MID_I2C_STATE_BUSY_RX & I2C_STATE_MSK) | MID_I2C_MODE_SLAVE))             /*!< Slave Busy RX, combinaison of State LSB and Mode enum */
#define I2C_STATE_MEM_BUSY_TX       ((uint32_t)((MID_I2C_STATE_BUSY_TX & I2C_STATE_MSK) | MID_I2C_MODE_MEM))               /*!< Memory Busy TX, combinaison of State LSB and Mode enum */
#define I2C_STATE_MEM_BUSY_RX       ((uint32_t)((MID_I2C_STATE_BUSY_RX & I2C_STATE_MSK) | MID_I2C_MODE_MEM))               /*!< Memory Busy RX, combinaison of State LSB and Mode enum */

/* Private define to centralize the enable/disable of Interrupts */
#define I2C_IT_BUF                  I2C_INT_BUF_IE_mask_w                                                                  /*!< Using on Buffmode */
/**
 * @}
 */

/* Private macro -------------------------------------------------------------*/
/**
 * @brief       I2C_BUFFMODE_DISABLE
 * @param       "__HANDLE__": specifies the I2C Handle.
 * @return      None
 * @{
 */
#define I2C_BUFFMODE_DISABLE(__HANDLE__)        ((__HANDLE__)->Instance->CR0.B[0] &= ~I2C_CR0_BUF_EN_mask_b0)               /*!< Buffmode disable */
 /** @}
 */

/**
 * @brief       I2C_GET_BUFFMODE_STATE
 * @param       "__HANDLE__": specifies the I2C Handle.
 * @return      FlagStatus
 * @{
 */
#define I2C_GET_BUFFMODE_STATE(__HANDLE__)      ((((__HANDLE__)->Instance->CR0.B[0] & I2C_CR0_BUF_EN_mask_b0) == 0) ? CLR : SET)    /*!< Get BufferMode Register Bit State */
 /** @}
 */

#endif

#ifdef __cplusplus
}
#endif

#endif /* __MG32x02z_I2C_MID_H */

/************** (C) COPYRIGHT megawin Technology Co., Ltd. *****END OF FILE****/
