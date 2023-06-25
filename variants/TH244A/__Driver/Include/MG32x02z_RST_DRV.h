/**
 *******************************************************************************
 *
 * @file        MG32x02z_RST_DRV.H
 *
 * @brief       This is the C code format driver head file for RST module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.20
 * @date        2022/09/14
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2021 Megawin Technology Co., Ltd.
 *              All rights reserved.
 *
 *******************************************************************************
 * @par     Disclaimer 
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
#include "MG32x02z_RST.h"


#ifndef _MG32x02z_RST_DRV_H
/*!< _MG32x02z_RST_DRV_H */ 
#define _MG32x02z_RST_DRV_H


/*! @name   RST module 
*/
/* @{ */ 
#define RST_PORF        RST_STA_PORF_mask_w     /*!< Power-on reset flag */
#define RST_SWF         RST_STA_SWF_mask_w      /*!< Software forced reset flag */
#define RST_EXF         RST_STA_EXF_mask_w      /*!< External input reset flag */
#define RST_CPUF        RST_STA_CPUF_mask_w     /*!< CPU SYSRESETREQ bit system reset flag */
#define RST_BOD0F       RST_STA_BOD0F_mask_w    /*!< BOD0 reset flag */
#define RST_BOD1F       RST_STA_BOD1F_mask_w    /*!< BOD1 reset flag */
#if (defined(RST_STA_BOD2F_mask_w))
#define RST_BOD2F       RST_STA_BOD2F_mask_w    /*!< BOD2 reset flag */
#endif
#define RST_LPMF        RST_STA_LPMF_mask_w     /*!< Low power mode reset flag */
#define RST_CSCF        RST_STA_CSCF_mask_w     /*!< CSC missing clock detect reset flag */
#define RST_MEMF        RST_STA_MEMF_mask_w     /*!< Flash memory read/write/erase error reset flag */
#define RST_IWDTF       RST_STA_IWDTF_mask_w    /*!< IWDT reset flag */
#define RST_WWDTF       RST_STA_WWDTF_mask_w    /*!< WWDT reset flag */
#define RST_ADCF        RST_STA_ADCF_mask_w     /*!< ADC analog voltage watch-dog reset flag */
#if (defined(RST_STA_CMP0F_mask_w))
#define RST_CMP0F       RST_STA_CMP0F_mask_w    /*!< Comparator CMP0 threshold comparison reset flag */
#define RST_CMP1F       RST_STA_CMP1F_mask_w    /*!< Comparator CMP1 threshold comparison reset flag */
#endif
#if (defined(RST_STA_CMP2F_mask_w))
#define RST_CMP2F       RST_STA_CMP2F_mask_w    /*!< Comparator CMP2 threshold comparison reset flag */
#define RST_CMP3F       RST_STA_CMP3F_mask_w    /*!< Comparator CMP3 threshold comparison reset flag */
#endif
#define RST_WRF         RST_STA_WRF_mask_w      /*!< Warm reset flag */
#define RST_CRF         RST_STA_CRF_mask_w      /*!< Cold reset flag */
#define RST_ALLF        0xC00F3D7F
/* @} */


/*! @name 
*/
/* @{ */ 
#if (defined(RST_CR0_PE_DIS1_mask_w))
#define RST_PE_DIS1     RST_CR0_PE_DIS1_mask_w  /*!< Warm reset disable for PE[9:8] pins */
#endif
#if (defined(RST_CR0_PE_DIS0_mask_w))
#define RST_PE_DIS0     RST_CR0_PE_DIS0_mask_w  /*!< Warm reset disable for PE[3:0] pins */
#endif
#define RST_PD_DIS1     RST_CR0_PD_DIS1_mask_w  /*!< Warm reset disable for PD[11:8] pins */
#define RST_PD_DIS0     RST_CR0_PD_DIS0_mask_w  /*!< Warm reset disable for PD[3:0] pins */
#if (defined(RST_CR0_PC_DIS1_mask_w))
#define RST_PC_DIS1     RST_CR0_PC_DIS1_mask_w  /*!< Warm reset disable for PC[11:8] pins */
#endif
#if (defined(RST_CR0_PC_DIS0_mask_w))
#define RST_PC_DIS0     RST_CR0_PC_DIS0_mask_w  /*!< Warm reset disable for PC[3:0] pins */
#endif
#define RST_PB_DIS1     RST_CR0_PB_DIS1_mask_w  /*!< Warm reset disable for PB[11:8] pins */
#define RST_PB_DIS0     RST_CR0_PB_DIS0_mask_w  /*!< Warm reset disable for PB[3:0] pins */
#define RST_PA_DIS1     RST_CR0_PA_DIS1_mask_w  /*!< Warm reset disable for PA[11:8] pins */
#define RST_PA_DIS0     RST_CR0_PA_DIS0_mask_w  /*!< Warm reset disable for PA[3:0] pins */
/* @} */


/*! @name 
*/
/* @{ */ 
#define RST_SW_CE       RST_CE_SW_CE_mask_w     /*!< Software forced cold reset enable */
#define RST_EX_CE       RST_CE_EX_CE_mask_w     /*!< External input cold reset enable */
#define RST_CPU_CE      RST_CE_CPU_CE_mask_w    /*!< CPU SYSRESETREQ bit forced cold reset enable */
#define RST_BOD0_CE     RST_CE_BOD0_CE_mask_w   /*!< BOD0 cold reset enable */
#define RST_BOD1_CE     RST_CE_BOD1_CE_mask_w   /*!< BOD1 cold reset enable */
#if (defined(RST_CE_BOD2_CE_mask_w))
#define RST_BOD2_CE     RST_CE_BOD2_CE_mask_w   /*!< BOD2 cold reset enable */
#endif
#define RST_LPM_CE      RST_CE_LPM_CE_mask_w    /*!< Low power STOP mode cold reset enable */
#define RST_CSC_CE      RST_CE_CSC_CE_mask_w    /*!< CSC missing clock detect cold reset enable */
#define RST_MEM_CE      RST_CE_MEM_CE_mask_w    /*!< Flash memory read/write/erase error cold reset enable */
#define RST_IWDT_CE     RST_CE_IWDT_CE_mask_w   /*!< IWDT cold reset enable */
#define RST_WWDT_CE     RST_CE_WWDT_CE_mask_w   /*!< WWDT cold reset enable */
#define RST_ADC_CE      RST_CE_ADC_CE_mask_w    /*!< ADC analog voltage watch-dog cold reset enable */
#if (defined(RST_CE_CMP0_CE_mask_w))
#define RST_CMP0_CE     RST_CE_CMP0_CE_mask_w   /*!< Comparator CMP0 threshold comparison cold reset enable */
#define RST_CMP1_CE     RST_CE_CMP1_CE_mask_w   /*!< Comparator CMP1 threshold comparison cold reset enable */
#endif
#if (defined(RST_CE_CMP2_CE_mask_w))
#define RST_CMP2_CE     RST_CE_CMP2_CE_mask_w   /*!< Comparator CMP2 threshold comparison cold reset enable */
#define RST_CMP3_CE     RST_CE_CMP3_CE_mask_w   /*!< Comparator CMP3 threshold comparison cold reset enable */
#endif
/* @} */


/*! @name 
*/
/* @{ */ 
#define RST_SW_WE       RST_WE_SW_WE_mask_w     /*!< Software forced warm reset enable */
#define RST_EX_WE       RST_WE_EX_WE_mask_w     /*!< External input warm reset enable */
#define RST_CPU_WE      RST_WE_CPU_WE_mask_w    /*!< CPU SYSRESETREQ bit forced warm reset enable */
#define RST_BOD0_WE     RST_WE_BOD0_WE_mask_w   /*!< BOD0 warm reset enable */
#define RST_BOD1_WE     RST_WE_BOD1_WE_mask_w   /*!< BOD1 warm reset enable */
#if (defined(RST_WE_BOD2_WE_mask_w))
#define RST_BOD2_WE     RST_WE_BOD2_WE_mask_w   /*!< BOD2 warm reset enable */ 
#endif
#define RST_LPM_WE      RST_WE_LPM_WE_mask_w    /*!< Low power STOP mode warm reset enable */
#define RST_CSC_WE      RST_WE_CSC_WE_mask_w    /*!< CSC missing clock detect warm reset enable */
#define RST_MEM_WE      RST_WE_MEM_WE_mask_w    /*!< Flash memory read/write/erase error warm reset enable */
#define RST_IWDT_WE     RST_WE_IWDT_WE_mask_w   /*!< IWDT warm reset enable */
#define RST_WWDT_WE     RST_WE_WWDT_WE_mask_w   /*!< WWDT warm reset enable */
#define RST_ADC_WE      RST_WE_ADC_WE_mask_w    /*!< ADC analog voltage watch-dog warm reset enable */
#if (defined(RST_WE_CMP0_WE_mask_w))
#define RST_CMP0_WE     RST_WE_CMP0_WE_mask_w   /*!< Comparator CMP0 threshold comparison warm reset enable */
#define RST_CMP1_WE     RST_WE_CMP1_WE_mask_w   /*!< Comparator CMP1 threshold comparison warm reset enable */
#endif
#if (defined(RST_WE_CMP2_WE_mask_w))
#define RST_CMP2_WE     RST_WE_CMP2_WE_mask_w   /*!< Comparator CMP2 threshold comparison warm reset enable */
#define RST_CMP3_WE     RST_WE_CMP3_WE_mask_w   /*!< Comparator CMP3 threshold comparison warm reset enable */
#endif
/* @} */


#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

/*! @enum   RST_SoftForceReset_Type
    @brief  RST software force reset
*/ 
typedef enum
{
    RST_FR_IOPA     = 0,    /*!< System software forced reset enable for IO Port-A */
    RST_FR_IOPB     = 1,    /*!< System software forced reset enable for IO Port-B */
    RST_FR_IOPC     = 2,    /*!< System software forced reset enable for IO Port-C */
    RST_FR_IOPD     = 3,    /*!< System software forced reset enable for IO Port-D */
#if (defined(RST_AHB_IOPE_EN_mask_w))
    RST_FR_IOPE     = 4,    /*!< System software forced reset enable for IO Port-E */
#endif
    RST_FR_GPL      = 8,    /*!< System software forced reset enable for GPL module */
#if (defined(RST_AHB_EMB_EN_mask_w))
    RST_FR_EMB      = 12,   /*!< System software forced reset enable for EMB module */
#endif
    RST_FR_ADC0     = 32,   /*!< System software forced reset enable for ADC0 module */
#if (defined(RST_APB0_CMP_EN_mask_w))
    RST_FR_CMP      = 34,   /*!< System software forced reset enable for CMP module */
#endif
#if (defined(RST_APB0_DAC_EN_mask_w))
    RST_FR_DAC      = 35,   /*!< System software forced reset enable for DAC module */
#endif
    RST_FR_RTC      = 37,   /*!< System software forced reset enable for RTC module */
    RST_FR_IWDT     = 38,   /*!< System software forced reset enable for IWDT module  */
    RST_FR_WWDT     = 39,   /*!< System software forced reset enable for WWDT module  */
    RST_FR_I2C0     = 40,   /*!< System software forced reset enable for I2C0 module  */
#if (defined(RST_APB0_I2C1_EN_mask_w))
    RST_FR_I2C1     = 41,   /*!< System software forced reset enable for I2C1 module  */
#endif
    RST_FR_SPI0     = 44,   /*!< System software forced reset enable for SPI0 module  */
    RST_FR_URT0     = 48,   /*!< System software forced reset enable for URT0 module  */
    RST_FR_URT1     = 49,   /*!< System software forced reset enable for URT1 module  */
#if (defined(RST_APB0_URT2_EN_mask_w))
    RST_FR_URT2     = 50,   /*!< System software forced reset enable for URT2 module  */
#endif
#if (defined(RST_APB0_URT3_EN_mask_w))
    RST_FR_URT3     = 51,   /*!< System software forced reset enable for URT3 module  */
#endif
#if (defined(RST_APB0_URT4_EN_mask_w))
    RST_FR_URT4     = 52,   /*!< System software forced reset enable for URT4 module  */
#endif
#if (defined(RST_APB0_URT5_EN_mask_w))
    RST_FR_URT5     = 53,   /*!< System software forced reset enable for URT5 module  */
#endif
#if (defined(RST_APB0_URT6_EN_mask_w))
    RST_FR_URT6     = 54,   /*!< System software forced reset enable for URT6 module  */
#endif
#if (defined(RST_APB0_URT7_EN_mask_w))
    RST_FR_URT7     = 55,   /*!< System software forced reset enable for URT7 module  */
#endif
#if (defined(USB_TYPE))
    RST_FR_USB      = 60,   /*!< System software forced reset enable for USB module  */
#endif
#if (defined(RST_APB0_APX_EN_mask_w))
    RST_FR_APX      = 61,   /*!< System software forced reset enable for APX module  */
#endif
    RST_FR_TM00     = 64,   /*!< System software forced reset enable for TM00 module  */
    RST_FR_TM01     = 65,   /*!< System software forced reset enable for TM01 module  */
    RST_FR_TM10     = 68,   /*!< System software forced reset enable for TM10 module  */
    RST_FR_TM16     = 71,   /*!< System software forced reset enable for TM16 module  */
#if (defined(RST_APB1_TM20_EN_mask_w))
    RST_FR_TM20     = 72,   /*!< System software forced reset enable for TM20 module  */
#endif
#if (defined(RST_APB1_TM26_EN_mask_w))
    RST_FR_TM26     = 75,   /*!< System software forced reset enable for TM26 module  */
#endif
    RST_FR_TM36     = 79    /*!< System software forced reset enable for TM36 module  */
}RST_SoftForceReset_Type;


#if (defined(USB_TYPE))
/*! @enum   RST_USBResetMode_Type
    @brief  
*/ 
typedef enum
{
    RST_USB_ResetMode_All   = 0,    /*!< Chip will auto reset USB all blocks and registers */
    RST_USB_ResetMode_LV1   = 1     /*!< chip will reset all blocks and and registers except 
                                         USB_EN, USB_XTR_EN, USB_V33_EN (V33 LDO) and USB_DPU_EN 
                                         (DP 1.5k pull-up) contro */
}RST_USBResetMode_Type;
#endif

/**
 * @name	Function announce
 *   		
 */ 
///@{  
uint32_t RST_GetAllFlagStatus (void);
DRV_Return RST_GetSingleFlagStatus (uint32_t RST_FLAG) ;
void RST_ClearFlag (uint32_t RST_FLAG);

void RST_CRstSource_Config (uint32_t RST_CRS, FunctionalState NewState);
void RST_WRstSource_Config (uint32_t RST_WRS, FunctionalState NewState) ;

void RST_WRstGPIOLock_Config (uint32_t RST_Px_DISx, FunctionalState NewState);

void RST_ForceRstPeriph_SW (RST_SoftForceReset_Type ForceReset, FunctionalState NewState);

void RST_TriggerSystemRst_SW (FunctionalState NewState);
void RST_WWDTWRstMask_Cmd (FunctionalState NewState);
#if (defined(USB_TYPE))
void RST_USBRstMode_Select (RST_USBResetMode_Type RST_USBResetMode);
#endif
///@}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif  //_MG32x02z_RST_DRV_H

