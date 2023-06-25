/**
 ******************************************************************************
 * @file        MG32x02z_EMB_MID.h
 * @brief       Header file of EMB MID module.
 * @par         Project
 *              MG32x02z
 * @version     V2.54
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
#ifndef _MG32x02z_EMB_MID_H
#define _MG32x02z_EMB_MID_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MG32x02z_Common_MID.h"
#include "MG32x02z_CSC_MID.h"
#include "MG32x02z_DMA_MID.h"
#include "MG32x02z_EMB.h"

/* Exported types ------------------------------------------------------------*/

/** @name EMB_Exported_typedef EMB Exported Types
 * @{
 */
/**
 ******************************************************************************
 * @struct EMB_BANK_Typedef
 * @brief  EMB bank base address
 ******************************************************************************
 */
#define EMB_BANK_Typedef    EMB_Struct  /*!< EMB bank base address                                                               */

/**
 ******************************************************************************
 * @struct EMB_InitTypeDef
 * @brief  EMB Initial Configuration Structure definition
 ******************************************************************************
 */
typedef struct{
    uint32_t DeviceAccess;              /*!< ASynchronous or Synchronous The Access in the selected device by the EMB.
                                             This parameter can be a value of EMB_Device_Access                                  */

    uint32_t WriteSignal;               /*!< Toggle or Low the Write signal, valid for Memory write access.
                                             This parameter can be a value of EMB_Write_Signal                                   */

    uint32_t ReadSignal;                /*!< Toggle or Low the Read signal, valid for Memory read access.
                                             This parameter can be a value of EMB_Read_Signal                                    */

    uint32_t DataAddressMux;            /*!< Specifies whether the address and data values are
                                             multiplexed on the data bus or not.
                                             This parameter can be a value of EMB_Data_Address_Bus_Multiplexing                  */

    uint32_t DataAddressMuxMode;        /*!< Specifies whether the address and data values are
                                             multiplexed on the Data and Address Bus Multiplexing.
                                             This parameter can be a value of EMB_Data_Address_Bus_Multiplexing_Mode             */

    uint32_t AddressRange;              /*!< Addressing Range 16 or 24 or 30 Bits the Access in the selected device by the EMB.
                                             This parameter can be a value of EMB_Address_Range                                  */

    uint32_t WriteAccess;               /*!< Enables or disables the write Access in the selected device by the EMB.
                                             This parameter can be a value of EMB_Write_Access                                   */

#if defined(MG32_3RD)
    uint32_t DeviceDataWidth;           /*!< Specifies the external memory device width.
                                             This parameter can be a value of EMB_Device_Data_Bus_Width                          */

    uint32_t AddressMAM1;               /*!< This parameter can be a value of EMB_Address_MAM1                                   */

    uint32_t WriteByteAccess;           /*!< This parameter can be a value of EMB_Write_Byte_Access                              */
#endif
}EMB_InitTypeDef;                       /*!<                                                                                     */

/**
 ******************************************************************************
 * @struct EMB_Extended_TypeDef
 * @brief  EMB handle Structure definition
 ******************************************************************************
 */
typedef struct{
  #if defined(MG32_3RD)
    uint32_t MADBusByteSwap;            /*!< This parameter can be a value of EMB_MAD_Bus_Byte_Swap                              */
    uint32_t MADBusReverse;             /*!< This parameter can be a value of EMB_MAD_Bus_Reverse                                */
  #endif
    uint32_t MABusReverse;              /*!< This parameter can be a value of EMB_MA_Bus_Reverse                                 */
    uint32_t MCLK_Inverse;              /*!< This parameter can be a value of EMB_MCLK_Inverse                                   */
    uint32_t MALE2_Inverse;             /*!< This parameter can be a value of EMB_MALE2_Inverse                                  */
    uint32_t MALE_Inverse;              /*!< This parameter can be a value of EMB_MALE_Inverse                                   */
    uint32_t MCE_Inverse;               /*!< This parameter can be a value of EMB_MCE_Inverse                                    */
}EMB_Extended_TypeDef;

/**
 ******************************************************************************
 * @struct EMB_HandleTypeDef
 * @brief  EMB handle Structure definition
 ******************************************************************************
 */
typedef struct{
    EMB_BANK_Typedef *Instance;            /*!< Defines the B                                                                    */

    EMB_InitTypeDef Init;                  /*!< EMB access configuration                                                         */

    EMB_Extended_TypeDef Extended;         /*!< EMB Extended configuration                                                       */

    uint32_t CLKPrescaler;                 /*!< Defines the period of MCLK clock output signal, expressed in number of
                                                CK_APB cycles. This parameter can be a value between Min_Data = 1 and Max_Data = 8.
                                                @note This parameter is used for connect device accesses.                        */

    uint32_t AddressSetupTime;             /*!< Defines the number of MCLK cycles to configure
                                                the duration of the address setup time.
                                                This parameter can be a value between Min_Data = 0 and Max_Data = 1.             */

    uint32_t AddressPulseTime;             /*!< Defines the number of MCLK cycles to configure
                                                the address Pulse width time.
                                                This parameter can be a value between Min_Data = 1 and Max_Data = 16.            */

    uint32_t AddressHoldTime;              /*!< Defines the number of MCLK cycles to configure
                                                the duration of the address hold time.
                                                This parameter can be a value between Min_Data = 0 and Max_Data = 1.             */

    uint32_t DataSetupTime;                /*!< Defines the number of MCLK cycles to configure
                                                the duration of the data setup time.
                                                This parameter can be a value between Min_Data = 0 and Max_Data = 1              */

    uint32_t DataAccessTime;               /*!< Defines the number of MCLK cycles to configure
                                                the duration of the data write or read access time.
                                                This parameter can be a value between Min_Data = 1 and Max_Data = 16.            */

    uint32_t DataHoldTime;                 /*!< Defines the number of MCLK cycles to configure
                                                the duration of the data hold time.
                                                This parameter can be a value between Min_Data = 0 and Max_Data = 1.             */

    uint32_t IdleTime;                     /*!< Defines the number of MCLK cycles to configure
                                                the between two successive time.
                                                This parameter can be a value between Min_Data = 0 and Max_Data = 3.             */
}EMB_HandleTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @name EMB_Exported_Constants EMB Exported Constants
 * @{
 */

/** @name EMB_Controller EMB Controller
 * @{
 */

/** @name EMB_Bank EMB Bank
 * @{
 */
#define EMB_BANK0                               EMB                         /*!< EMB registers base address                      */
/**
 * @}
 */

/** @name EMB_Device_Access EMB Device Access ASynchronous / Synchronous
 * @{
 */
#define EMB_DEVICE_ACCESS_ASYNCHRONOUS          EMB_CR0_SYNC_EN_async_w     /*!< EMB asynchronous transaction                    */
#define EMB_DEVICE_ACCESS_SYNCHRONOUS           EMB_CR0_SYNC_EN_sync_w      /*!< EMB synchronous transaction                     */
/**
 * @}
 */

/** @name EMB_Write_Signal EMB Write Signal
* @{
 */
#define EMB_WRITE_SIGNAL_TOGGLE                 EMB_CR0_WE_CTL_toggle_w     /*!< TOGGLE : high-to-low change                     */
#define EMB_WRITE_SIGNAL_LOW                    EMB_CR0_WE_CTL_low_w        /*!< LOW : drive low during write access             */
/**
 * @}
 */

/** @name EMB_Read_Signal EMB Read Signal
* @{
 */
#define EMB_READ_SIGNAL_TOGGLE                  EMB_CR0_OE_CTL_toggle_w     /*!< TOGGLE : high-to-low change                     */
#define EMB_READ_SIGNAL_LOW                     EMB_CR0_OE_CTL_low_w        /*!< LOW : drive low during write access             */
/**
 * @}
 */

/** @name EMB_Data_Address_Bus_Multiplexing EMB Data Address Bus Multiplexing
 * @{
 */
#define EMB_DATA_ADDRESS_MUX_ENABLE             EMB_CR0_BUS_MDS_multiplex_w /*!< Multiplex                                       */
#define EMB_DATA_ADDRESS_MUX_DISABLE            EMB_CR0_BUS_MDS_separated_w /*!< Separated                                       */
/**
 * @}
 */

/** @name EMB_Data_Address_Bus_Multiplexing_Mode EMB Data Address Bus Multiplexing Mode
 * @{
 */
#define EMB_DATA_ADDRESS_MULTIPLEX_1ALE         EMB_CR0_ADR_TWO_disable_w   /*!< EMB two address phase timing mode DISABLE       */
#define EMB_DATA_ADDRESS_MULTIPLEX_2ALE         EMB_CR0_ADR_TWO_enable_w    /*!< EMB two address phase timing mode ENABLE        */
/**
 * @}
 */

/** @name EMB_Address_Range EMB Address Rang
* @{
 */
#define EMB_ADDRESS_RANGE_16BIT                 EMB_CR0_ADR_SEL_16bit_w     /*!< 16bit : 17bit if EMB_MAM1_EN is enabled         */
#define EMB_ADDRESS_RANGE_24BIT                 EMB_CR0_ADR_SEL_24bit_w     /*!< 24bit : 25bit if EMB_MAM1_EN is enabled         */
#define EMB_ADDRESS_RANGE_30BIT                 EMB_CR0_ADR_SEL_30bit_w     /*!< 30bit                                           */
/**
 * @}
 */

/** @name EMB_Write_Access EMB Write Access Enable / Disable
 * @{
 */
#define EMC_WRITE_ACCESS_DISABLE                EMB_CR0_WEN_disable_w       /*!< EMB write access DISABLE                        */
#define EMC_WRITE_ACCESS_ENABLE                 EMB_CR0_WEN_enable_w        /*!< EMB write access ENABLE                         */
/**
 * @}
 */

#if defined(MG32_3RD)
/** @name EMB_Device_Data_Bus_Width EMB Device Data Bus Width
 * @{
 */
#define EMB_DEVICE_DATA_BUS_WIDTH_8             EMB_CR0_BUS_DSIZE_8_bit_w   /*!< i80 8-Bits                                      */
#define EMB_DEVICE_DATA_BUS_WIDTH_16            EMB_CR0_BUS_DSIZE_16_bit_w  /*!< i80 16-Bits                                     */
/**
 * @}
 */

/** @name EMB_Address_MAM1 EMB address A-1 output Enable / Disable
* @{
 */
#define EMB_ADDRESS_MAM1_SIGNAL_DISABLE         EMB_CR0_MAM1_EN_disable_w   /*!< Disable                                         */
#define EMB_ADDRESS_MAM1_SIGNAL_ENABLE          EMB_CR0_MAM1_EN_enable_w    /*!< Enable                                          */
/**
 * @}
 */


/** @name EMB_Write_Byte_Access EMB Write Byte Access Enable / Disable
* @{
 */
#define EMB_WRITE_BYTE_ACCESS_DISABLE           EMB_CR0_BW_EN_disable_w     /*!< Disable                                         */
#define EMB_WRITE_BYTE_ACCESS_ENABLE            EMB_CR0_BW_EN_enable_w      /*!< Enable                                          */
/**
 * @}
 */

/** @name EMB_MAD_Bus_Byte_Swap EMB Address Data Bus Byte Swap Enable / Disable
* @{
 */
#define EMB_MAD_BYTE_SWAP_DISABLE               EMB_CR1_MAD_BSWAP_disable_w /*!< Disable                                         */
#define EMB_MAD_BYTE_SWAP_ENABLE                EMB_CR1_MAD_BSWAP_enable_w  /*!< Enable                                          */
/**
 * @}
 */

/** @name EMB_MAD_Bus_Reverse EMB Address Data Bus Reverse Enable / Disable
* @{
 */
#define EMB_MAD_REVERSE_DISABLE                 EMB_CR1_MAD_SWAP_disable_w  /*!< Disable                                         */
#define EMB_MAD_REVERSE_ENABLE                  EMB_CR1_MAD_SWAP_enable_w   /*!< Enable                                          */
/**
 * @}
 */
#endif

/** @name EMB_MA_Bus_Reverse EMB Address Bus Reverse Enable / Disable
* @{
 */
#define EMB_MA_REVERSE_DISABLE                  EMB_CR1_MA_SWAP_disable_w   /*!< Disable                                         */
#define EMB_MA_REVERSE_ENABLE                   EMB_CR1_MA_SWAP_enable_w    /*!< Enable                                          */
/**
 * @}
 */

/** @name EMB_MCLK_Inverse EMB MCLK Inverse Enable / Disable
* @{
 */
#define EMB_MCLK_INVERSE_DISABLE                EMB_CR1_CLK_INV_disable_w   /*!< Disable                                         */
#define EMB_MCLK_INVERSE_ENABLE                 EMB_CR1_CLK_INV_enable_w    /*!< Enable                                          */
/**
 * @}
 */

/** @name EMB_MALE2_Inverse EMB MALE2 Inverse Enable / Disable
* @{
 */
#define EMB_MALE2_INVERSE_DISABLE               EMB_CR1_ALE2_INV_disable_w  /*!< Disable                                         */
#define EMB_MALE2_INVERSE_ENABLE                EMB_CR1_ALE2_INV_enable_w   /*!< Enable                                          */
/**
 * @}
 */

/** @name EMB_MALE_Inverse EMB MALE Inverse Enable / Disable
* @{
 */
#define EMB_MALE_INVERSE_DISABLE                EMB_CR1_ALE_INV_disable_w   /*!< Disable                                         */
#define EMB_MALE_INVERSE_ENABLE                 EMB_CR1_ALE_INV_enable_w    /*!< Enable                                          */
/**
 * @}
 */

/** @name EMB_MCE_Inverse EMB MCE Inverse Enable / Disable
* @{
 */
#define EMB_MCE_INVERSE_DISABLE                 EMB_CR1_CE_INV_disable_w    /*!< Disable                                         */
#define EMB_MCE_INVERSE_ENABLE                  EMB_CR1_CE_INV_enable_w     /*!< Enable                                          */
/**
 * @}
 */

/** @name EMB_Interrupt_definition EMB Interrupt definition
 * @{
 */
#define EMB_IT_IEA                              EMB_INT_IEA_mask_w          /*!< EMB controller interrupt all enable.            */
#define EMB_IT_WPE                              EMB_INT_WPE_IE_mask_w       /*!< EMB bus write-protect error detect interrupt.   */

#if defined(MG32_3RD)
#define EMB_IT_BWE                              EMB_INT_BWE_IE_mask_w       /*!< EMB bus byte-write error detect interrupt.      */
#define EMB_IT_IAE                              EMB_INT_IAE_IE_mask_w       /*!< EMB bus access illegal address error detection interrupt. */
#endif
/**
 * @}
 */

/** @name EMB_Flag_definition EMB Flag definition
 * @{
 */
#define EMB_FLAG_BUSY                           EMB_STA_BUSYF_mask_w        /*!< EMB write/read access busy                      */
#define EMB_FLAG_WPE                            EMB_STA_WPEF_mask_w         /*!< EMB bus write-protect error detect              */
#if defined(MG32_3RD)
#define EMB_FLAG_BWE                            EMB_STA_BWEF_mask_w         /*!< EMB bus byte-write error                        */
#define EMB_FLAG_IAE                            EMB_STA_IAEF_mask_w         /*!< EMB bus access illegal address error detection  */
#endif
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/* Exported macros -----------------------------------------------------------*/
/** @name EMB_Private_Macros EMB Private Macros
 * @{
 */
/** @name EMB_Macros EMB Macros
 * @brief macros to handle device enable/disable and read/write operations
 * @{
 */

/**
 ******************************************************************************
 * @brief  Enable the device access.
 * @param  "__HANDLE__" EMB Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->CR0.W |= EMB_CR0_EN_mask_w)

/**
 ******************************************************************************
 * @brief  Disable the device access.
 * @param  "__HANDLE__" EMB Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->CR0.W &= (~EMB_CR0_EN_mask_w))

/**
 ******************************************************************************
 * @brief  Enable the device interrupt.
 * @param  "__HANDLE__" EMB Instance
 * @param  "__INTERRUPT__" EMB_interrupt
 *         This parameter can be any combination of the following values:
 *            @arg EMB_IT_IEA : Interrupt all enable or disable.
 *            @arg EMB_IT_WPE : Write-protect error.
 *            @arg EMB_IT_BWE : Byte-write error .
 *            @arg EMB_IT_IAE : Interrupt illegal address error.
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_ENABLE_IT(__HANDLE__, __INTERRUPT__)  ((__HANDLE__)->Instance->INT.W |= (__INTERRUPT__))

/**
 ******************************************************************************
 * @brief  Disable the device interrupt.
 * @param  "__HANDLE__" EMB Instance
 * @param  "__INTERRUPT__" EMB_interrupt
 *         This parameter can be any combination of the following values:
 *            @arg EMB_IT_IEA : Interrupt all enable or disable.
 *            @arg EMB_IT_WPE : Write-protect error.
 *            @arg EMB_IT_BWE : Byte-write error .
 *            @arg EMB_IT_IAE : Interrupt illegal address error.
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_DISABLE_IT(__HANDLE__, __INTERRUPT__)  ((__HANDLE__)->Instance->INT.W &= ~(__INTERRUPT__))

/**
 ******************************************************************************
 * @brief  Check whether the specified I2C interrupt source is enabled or not.
 * @param  "__HANDLE__" specifies the I2C Handle.
 * @param  "__INTERRUPT__" specifies the I2C interrupt source to check.
 *          This parameter can be one of the following values:
 *            @arg EMB_IT_IEA : Interrupt all enable or disable.
 *            @arg EMB_IT_WPE : Write-protect error.
 *            @arg EMB_IT_BWE : Byte-write error .
 *            @arg EMB_IT_IAE : Interrupt illegal address error.
 * @return The new state of __INTERRUPT__ (SET or RESET).
 ******************************************************************************
 */
#define __DRV_EMB_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)  ((((__HANDLE__)->Instance->INT.W & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/**
 ******************************************************************************
 * @brief  Get flag status of the device.
 * @param  "__HANDLE__" EMB_Instance
 * @param  "__FLAG__"     EMB_flag
 *         This parameter can be any combination of the following values:
 *            @arg EMB_FLAG_BUSY: Interrupt rising edge flag.
 *            @arg EMB_FLAG_WPE: Interrupt level edge flag.
 *            @arg EMB_FLAG_BWE: Interrupt falling edge flag.
 *            @arg EMB_FLAG_IAE: FIFO empty flag.
 * @retval The state of FLAG (SET or CLR).
 ******************************************************************************
 */
#define __DRV_EMB_GET_FLAG(__HANDLE__, __FLAG__)  (((__HANDLE__)->SR &(__FLAG__)) == (__FLAG__))

/**
 ******************************************************************************
 * @brief  Clear flag status of the device.
 * @param  "__HANDLE__"   EMB_Instance
 * @param  "__FLAG__"     EMB_flag
 *         This parameter can be any combination of the following values:
 *            @arg EMB_FLAG_BUSY: Interrupt rising edge flag.
 *            @arg EMB_FLAG_WPE: Interrupt level edge flag.
 *            @arg EMB_FLAG_BWE: Interrupt falling edge flag.
 *            @arg EMB_FLAG_IAE: FIFO empty flag.
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_CLEAR_FLAG(__HANDLE__, __FLAG__)  ((__HANDLE__)->SR &= ~(__FLAG__))

#if defined(MG32_3RD)
/**
 ******************************************************************************
 * @brief  EMB MAD[15:8] and MAD[7:0] signals byte swap enable.
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_MAD_BYTE_SWAP_ENABLE(__HANDLE__)  ((__HANDLE__)->Instance->CR1.W |= EMB_CR0_EN_mask_w)

/**
 ******************************************************************************
 * @brief  EMB MAD[15:8] and MAD[7:0] signals byte swap disable.
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_MAD_BYTE_SWAP_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->CR1.W &= (~EMB_CR0_EN_mask_w))

/**
 ******************************************************************************
 * @brief  EMB MAD[15:0] signals reverse enable.
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_MAD_REVERSE_ENABLE(__HANDLE__)    ((__HANDLE__)->Instance->CR1.W |= EMB_CR1_CE_SWO_mask_w)

/**
 ******************************************************************************
 * @brief  EMB MAD[15:0] signals reverse disable.
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_MAD_REVERSE_DISABLE(__HANDLE__)   ((__HANDLE__)->Instance->CR1.W &= (~EMB_CR1_CE_SWO_mask_w))

#endif

/**
 ******************************************************************************
 * @brief  EMB MA[15:0] signals reverse enable.
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_MA_REVERSE_ENABLE(__HANDLE__)     ((__HANDLE__)->Instance->CR1.W |= EMB_CR1_MA_SWAP_mask_w)

/**
 ******************************************************************************
 * @brief  EMB MA[15:0] signals reverse disable.
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_MA_REVERSE_DISABLE(__HANDLE__)    ((__HANDLE__)->Instance->CR1.W &= (~EMB_CR1_MA_SWAP_mask_w))

/**
 ******************************************************************************
 * @brief  EMB MCE signal output software control enable
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_CE_SWCTL_ENABLE(__HANDLE__)       ((__HANDLE__)->Instance->CR1.W |= EMB_CR1_CE_SWEN_mask_w)

/**
 ******************************************************************************
 * @brief  EMB MCE signal output software control disable
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_CE_SWCTL_DISABLE(__HANDLE__)      ((__HANDLE__)->Instance->CR1.W &= (~EMB_CR1_CE_SWEN_mask_w))

/**
 ******************************************************************************
 * @brief  EMB MCE signal software control output logic-high
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_CE_SW_SET(__HANDLE__)             ((__HANDLE__)->Instance->CR1.W |= EMB_CR1_CE_SWO_mask_w)

/**
 ******************************************************************************
 * @brief  EMB MCE signal software control output logic-low
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_CE_SW_CLR(__HANDLE__)             ((__HANDLE__)->Instance->CR1.W &= (~EMB_CR1_CE_SWO_mask_w))

/**
 ******************************************************************************
 * @brief  EMB MALE signal output software control enable
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_ALE_SWCTL_ENABLE(__HANDLE__)      ((__HANDLE__)->Instance->CR1.W |= EMB_CR1_ALE_SWEN_mask_w)

/**
 ******************************************************************************
 * @brief  EMB MALE signal output software control disable
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_ALE_SWCTL_DISABLE(__HANDLE__)     ((__HANDLE__)->Instance->CR1.W &= (~EMB_CR1_ALE_SWEN_mask_w))

/**
 ******************************************************************************
 * @brief  EMB MALE signal software control output logic-high
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_ALE_SW_SET(__HANDLE__)            ((__HANDLE__)->Instance->CR1.W |= EMB_CR1_ALE_SWO_mask_w)

/**
 ******************************************************************************
 * @brief  EMB MALE signal software control output logic-low
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_ALE_SW_CLR(__HANDLE__)            ((__HANDLE__)->Instance->CR1.W &= (~EMB_CR1_ALE_SWO_mask_w))

/**
 ******************************************************************************
 * @brief  EMB MALE2 signal output software control enable
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_ALE2_SWCTL_ENABLE(__HANDLE__)     ((__HANDLE__)->Instance->CR1.W |= EMB_CR1_ALE2_SWEN_mask_w)

/**
 ******************************************************************************
 * @brief  EMB MALE2 signal output software control disable
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_ALE2_SWCTL_DISABLE(__HANDLE__)    ((__HANDLE__)->Instance->CR1.W &= (~EMB_CR1_ALE2_SWEN_mask_w))

/**
 ******************************************************************************
 * @brief  EMB MALE2 signal software control output logic-high
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_ALE2_SW_SET(__HANDLE__)           ((__HANDLE__)->Instance->CR1.W |= EMB_CR1_ALE2_SWO_mask_w)

/**
 ******************************************************************************
 * @brief  EMB MALE2 signal software control output logic-low
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_ALE2_SW_CLR(__HANDLE__)           ((__HANDLE__)->Instance->CR1.W &= (~EMB_CR1_ALE2_SWO_mask_w))

/**
 ******************************************************************************
 * @brief  EMB BW0 signal output software control enable
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_BW0_SWCTL_ENABLE(__HANDLE__)      ((__HANDLE__)->Instance->CR1.W |= EMB_CR1_BW0_SWEN_mask_w)

/**
 ******************************************************************************
 * @brief  EMB BW0 signal output software control disable
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_BW0_SWCTL_DISABLE(__HANDLE__)     ((__HANDLE__)->Instance->CR1.W &= (~EMB_CR1_BW0_SWEN_mask_w))

/**
 ******************************************************************************
 * @brief  EMB BW0 signal software control output logic-high
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_BW0_SW_SET(__HANDLE__)            ((__HANDLE__)->Instance->CR1.W |= EMB_CR1_BW0_SWO_mask_w)

/**
 ******************************************************************************
 * @brief  EMB BW0 signal software control output logic-low
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_BW0_SW_CLR(__HANDLE__)            ((__HANDLE__)->Instance->CR1.W &= (~EMB_CR1_BW0_SWO_mask_w))

/**
 ******************************************************************************
 * @brief  EMB BW1 signal output software control enable
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_BW1_SWCTL_ENABLE(__HANDLE__)      ((__HANDLE__)->Instance->CR1.W |= EMB_CR1_BW1_SWEN_mask_w)

/**
 ******************************************************************************
 * @brief  EMB BW1 signal output software control disable
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_BW1_SWCTL_DISABLE(__HANDLE__)     ((__HANDLE__)->Instance->CR1.W &= (~EMB_CR1_BW1_SWEN_mask_w))

/**
 ******************************************************************************
 * @brief  EMB BW1 signal software control output logic-high
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_BW1_SW_SET(__HANDLE__)            ((__HANDLE__)->Instance->CR1.W |= EMB_CR1_BW1_SWO_mask_w)

/**
 ******************************************************************************
 * @brief  EMB BW1 signal software control output logic-low
 * @param  "__HANDLE__" EMB_Instance
 * @retval None
 ******************************************************************************
 */
#define __DRV_EMB_BW1_SW_CLR(__HANDLE__)            ((__HANDLE__)->Instance->CR1.W &= (~EMB_CR1_BW1_SWO_mask_w))

/**
 * @}
 */

/**
 * @}
 */

/* Exported variables --------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @name EMB_Functions EMB Exported Functions
 *  @{
 */

/** @name EMB_Functions_Group1 Initialization/de-initialization functions
  *  @{
  */
#define EMB_Init    MID_EMB_Init
#define EMB_DeInit  MID_EMB_DeInit
MID_StatusTypeDef MID_EMB_Init(EMB_HandleTypeDef *mEMB);
MID_StatusTypeDef MID_EMB_DeInit(EMB_HandleTypeDef *mEMB);
void MID_EMB_MspInit(EMB_HandleTypeDef* mEMB);
void MID_EMB_MspDeInit(EMB_HandleTypeDef* mEMB);
/**
 * @}
 */

/** @name EMB_Functions_Group2 EMB Control functions
 *  @{
 */
#define EMB_WriteOperation_Enable   MID_EMB_WriteOperation_Enable
#define EMB_WriteOperation_Disable  MID_EMB_WriteOperation_Disable
MID_StatusTypeDef MID_EMB_WriteOperation_Enable(EMB_HandleTypeDef *mEMB);
MID_StatusTypeDef MID_EMB_WriteOperation_Disable(EMB_HandleTypeDef *mEMB);
/**
 * @}
 */

/**
 ******************************************************************************
 * @name EMB_IRQ_Handler_and_Callbacks 
 *       IRQ Handler and Callbacks
 * @{
 ******************************************************************************
 */
/******* I2C IRQHandler and Callbacks used in non blocking modes (Interrupt) */
void MID_EMB_IRQHandler(EMB_HandleTypeDef *mEMB);

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

#define IS_EMB_DEVICE(__SYNC__)  (((__SYNC__) == EMB_DEVICE_ACCESS_ASYNCHRONOUS) || \
                                  ((__SYNC__) == EMB_DEVICE_ACCESS_SYNCHRONOUS))            /*!< Device_Access Parameter check   */

#define IS_EMB_WRITE_SIGNAL(__SIGNAL__)  (((__SIGNAL__) == EMB_WRITE_SIGNAL_TOGGLE) || \
                                          ((__SIGNAL__) == EMB_WRITE_SIGNAL_LOW))           /*!< WRITE_SIGNAL Parameter check    */

#define IS_EMB_READ_SIGNAL(__SIGNAL__)  (((__SIGNAL__) == EMB_READ_SIGNAL_TOGGLE) || \
                                         ((__SIGNAL__) == EMB_READ_SIGNAL_LOW))             /*!< READ_SIGNAL Parameter check     */

#define IS_EMB_MUX(__MUX__)  (((__MUX__) == EMB_DATA_ADDRESS_MUX_ENABLE) || \
                              ((__MUX__) == EMB_DATA_ADDRESS_MUX_DISABLE))                  /*!< MAD MUX Parameter check         */

#define IS_EMB_MUX_MODE(__MUXMODE__)  (((__MUXMODE__) == EMB_DATA_ADDRESS_MULTIPLEX_1ALE) || \
                                       ((__MUXMODE__) == EMB_DATA_ADDRESS_MULTIPLEX_2ALE))  /*!< MAD MUX_MODE Parameter check    */

#define IS_EMB_WRITE(__WRITE__)  (((__MUXMODE__) == EMC_WRITE_ACCESS_DISABLE) || \
                                  ((__MUXMODE__) == EMC_WRITE_ACCESS_ENABLE))               /*!< Write acccess Parameter check   */

#define IS_EMB_MA_REVERSE(__REVERSE__)  (((__REVERSE__) == EMB_MA_REVERSE_DISABLE) || \
                                         ((__REVERSE__) == EMB_MA_REVERSE_ENABLE))          /*!< MA Bus Reverse Parameter check  */

#define IS_EMB_MCLK_INVERSE(__INVERSE__)  (((__INVERSE__) == EMB_MCLK_INVERSE_DISABLE) || \
                                           ((__INVERSE__) == EMB_MCLK_INVERSE_ENABLE))      /*!< MCLK_INVERSE Parameter check    */

#define IS_EMB_MALE2_INVERSE(__INVERSE__)  (((__INVERSE__) <= EMB_MALE2_INVERSE_DISABLE) || \
                                            ((__INVERSE__) <= EMB_MALE2_INVERSE_ENABLE))    /*!< MALE2_INVERSE Parameter check   */

#define IS_EMB_MALE_INVERSE(__INVERSE__)  (((__INVERSE__) > EMB_MALE_INVERSE_DISABLE) || \
                                           ((__INVERSE__) > EMB_MALE_INVERSE_ENABLE))       /*!< MALE_INVERSE Parameter check    */

#define IS_EMB_MCE_INVERSE(__INVERSE__)  (((__INVERSE__) <= EMB_MCE_INVERSE_DISABLE) || \
                                          ((__INVERSE__) <= EMB_MCE_INVERSE_ENABLE))        /*!< MALE_INVERSE Parameter check    */

#define IS_EMB_PRESCALER(__PRESCALER__)  ((__PRESCALER__) > 0U) && ((__PRESCALER__) <= 8U)) /*!< PRESCALER Parameter check       */

#define IS_EMB_DATA_SETUP_TIME(__TIME__)  ((__TIME__) <= 1U)                                /*!< DATA_SETUP_TIME Parameter check */

#define IS_EMB_DATA_ACCESS_TIME(__TIME__)  ((__TIME__) > 0U) && ((__TIME__) <= 16U))        /*!< DATA_ACCESS_TIME Parameter check */

#define IS_EMB_DATA_HOLD_TIME(__TIME__)  ((__TIME__) <= 1U)                                 /*!< DATA_HOLD_TIME Parameter check  */

#define IS_EMB_ADDRESS_SETUP_TIME(__TIME__)  ((__TIME__) <= 1U)                             /*!< ADDRESS_SETUP_TIME Parameter check */

#define IS_EMB_ADDRESS_PLUSE_TIME(__TIME__)  ((__TIME__) > 0U) && ((__TIME__) <= 8U))       /*!< ADDRESS_PLUSE_TIME Parameter check */

#define IS_EMB_ADDRESS_HOLD_TIME(__TIME__)  ((__TIME__) <= 1U)                              /*!< ADDRESS_HOLD_TIME Parameter check */

#if defined(MG32_1ST)
#define IS_EMB_RANGE(__RANGE__)  (((__RANGE__) == EMB_ADDRESS_RANGE_16BIT) || \
                                  ((__RANGE__) == EMB_ADDRESS_RANGE_24BIT))                 /*!< addressing range Parameter check */
#endif

#if defined(MG32_3RD)
#define IS_EMB_RANGE(__RANGE__)  (((__RANGE__) == EMB_ADDRESS_RANGE_16BIT) || \
                                  ((__RANGE__) == EMB_ADDRESS_RANGE_24BIT) || \
                                  ((__RANGE__) == EMB_ADDRESS_RANGE_30BIT))                 /*!< addressing range Parameter check */

#define IS_EMB_BYTE_WRITE(__BYTEWRITE__)  (((__BYTEWRITE__) == EMB_WRITE_BYTE_ACCESS_DISABLE) || \
                                           ((__BYTEWRITE__) == EMB_WRITE_BYTE_ACCESS_ENABLE))   /*!< BYTE_WRITE Parameter check  */

#define IS_EMB_DEVICE_DATA_WIDTH(__WIDTH__)  (((__WIDTH__) == EMB_DEVICE_DATA_BUS_WIDTH_8)  || \
                                              ((__WIDTH__) == EMB_DEVICE_DATA_BUS_WIDTH_16))    /*!< DEVICE_DATA_WIDTH Parameter check */

#define IS_EMB_MAM1_SIGNAL(__MAM1__)  (((__MAM1__) == EMB_ADDRESS_MAM1_SIGNAL_DISABLE) || \
                                       ((__MAM1__) == EMB_ADDRESS_MAM1_SIGNAL_ENABLE))      /*!< MAM1_SIGNAL Parameter check     */

#define IS_EMB_MAD_BYTE_REVERSE(__REVERSE__)  (((__REVERSE__) == EMB_MAD_BYTE_SWAP_DISABLE) || \
                                               ((__REVERSE__) == EMB_MAD_BYTE_SWAP_ENABLE)) /*!< MAD_BYTE_REVERSE Parameter check */

#define IS_EMB_MAD_REVERSE(__REVERSE__)  (((__REVERSE__) == EMB_MAD_REVERSE_DISABLE) || \
                                          ((__REVERSE__) == EMB_MA_REVERSE_ENABLE))         /*!< MAD_REVERSE Parameter check     */

#define IS_EMB_IDLE_TIME(__TIME__)  ((__TIME__) > 0U) && ((__TIME__) <= 3U))                /*!< IDLE_TIME Parameter check       */
#endif

/**
 * @}
 */

/* Private Functions ---------------------------------------------------------*/
#if defined(MG32_1ST) || defined(MG32_3RD)
void MID_EMB_WriteProtectCallback(EMB_HandleTypeDef *mEMB);
#endif

#if defined(MG32_3RD)
void MID_EMB_ByteWriteProtectCallback(EMB_HandleTypeDef *mEMB);
void MID_EMB_IllegalAddressCallback(EMB_HandleTypeDef *mEMB);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _MG32x02z_EMB_MID_H */


