/**
 ******************************************************************************
 *
 * @file        MG32x02z_ADC_MID.h
 *
 * @brief       This file provides firmware functions to manage the following 
 *              functionalities of the ADC peripheral:
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.06
 * @date        2022/01/07
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2016 MegaWin Technology Co., Ltd.
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

#ifndef _MG32x02z_ADC_MID_H

/*!< _MG32x02z_ADC_DRV_H */ 
#define _MG32x02z_ADC_MID_H

#include "MG32x02z.h"
#include "MG32x02z_Common_MID.h"
#include "MG32x02z_ADC.h"
#include "MG32x02z_DMA_MID.h"
#include "MG32x02z_CFG_MID.h"
#include "MG32x02z_PW_MID.h"


/**
 * @name	ADC_ClockConfig
 *   		ADC ClockPrescaler
 */ 
//!@{
#define ADC_CLOCKPROC_DIV1          ADC_CLK_CK_SEL2_ck_adc_w + ADC_CLK_CK_DIV_div1_w    /*!<  ADC clock=CK_PROC+Divider 1 */
#define ADC_CLOCKPROC_DIV2          ADC_CLK_CK_SEL2_ck_adc_w + ADC_CLK_CK_DIV_div2_w    /*!<  ADC clock=CK_PROC+Divider 2 */
#define ADC_CLOCKPROC_DIV4          ADC_CLK_CK_SEL2_ck_adc_w + ADC_CLK_CK_DIV_div4_w    /*!<  ADC clock=CK_PROC+Divider 4 */
#define ADC_CLOCKPROC_DIV16         ADC_CLK_CK_SEL2_ck_adc_w + ADC_CLK_CK_DIV_div16_w   /*!<  ADC clock=CK_PROC+Divider 16 */
#define ADC_CLOCKPLL_DIV2           ADC_CLK_CK_SEL2_ck_pll_w + ADC_CLK_CK_DIV2_div2_w   /*!<  ADC clock=CK_PLL+Divider 2 */
#define ADC_CLOCKPLL_DIV4           ADC_CLK_CK_SEL2_ck_pll_w + ADC_CLK_CK_DIV2_div4_w   /*!<  ADC clock=CK_PLL+Divider 4 */
#define ADC_CLOCKPLL_DIV5           ADC_CLK_CK_SEL2_ck_pll_w + ADC_CLK_CK_DIV2_div5_w   /*!<  ADC clock=CK_PLL+Divider 5 */
#define ADC_CLOCKPLL_DIV6           ADC_CLK_CK_SEL2_ck_pll_w + ADC_CLK_CK_DIV2_div6_w   /*!<  ADC clock=CK_PLL+Divider 6 */
#define ADC_TM00UPDATE_DIV2         ADC_CLK_CK_SEL2_tm00_trgo_w                         /*!<  ADC clock=TM00_TRGO/2 */
#define ADC_TM01UPDATE_DIV2         ADC_CLK_CK_SEL2_tm01_trgo_w                         /*!<  ADC clock=TM01_TRGO/2 */
//!@}

/**
 * @name	ADC_Resolution
 *   		ADC conversion resolution select
 */ 
//!@{
#define ADC_RESOLUTION_12B          ADC_CR0_RES_SEL_12_bit_w        /*!<  ADC 12-bit resolution */
#define ADC_RESOLUTION_10B          ADC_CR0_RES_SEL_10_bit_w        /*!<  ADC 10-bit resolution */
#define ADC_RESOLUTION_8B           ADC_CR0_RES_SEL_8_bit_w         /*!<  ADC 8-bit resolution */
//!@}

/**
 * @name	ADC_Data_align
 *   		ADC data align Right/Left justified
 */ 
//!@{
#define ADC_DATAALIGN_RIGHT         ADC_CR1_ALIGN_SEL_right_w       /*!<  Right (Right alignment)  */
#define ADC_DATAALIGN_LEFT          ADC_CR1_ALIGN_SEL_left_w        /*!<  Left (Left alignment)  */
//!@}

/**
 * @name	ADC_Conversion_mode
 *   		ADC Conversion mode select
 */ 
//!@{
#define ADC_ONESHOT                 ADC_START_CONV_MDS_one_w + ADC_START_TRG_CONT_disable_w     /*!< Trigger once and conversion once */
#define ADC_REPITIVE_CHANNEL        ADC_START_CONV_MDS_one_w + ADC_START_TRG_CONT_enable_w      /*!< Trigger once and repeat convesion one channel */
#define ADC_SCAN_MANUAL             ADC_START_CONV_MDS_scan_w + ADC_START_TRG_CONT_disable_w    /*!< Manual trigger conversion */
#define ADC_SCAN_AUTO               ADC_START_CONV_MDS_scan_w + ADC_START_TRG_CONT_enable_w     /*!< Trigger once and auto scan mask channel */ 
#define ADC_LOOP_AUTO               ADC_START_CONV_MDS_loop_w                                   /*!< Conversion loop mode */
//!@}

/**
 * @name	ADC_Wait_ReadData
 *   		ADC wait treat conversion data
 */ 
//!@{
#define ADC_WAIT_READ_DATA          ADC_CR0_WAIT_EN_enable_w        /*!< ADC must read data then ADC will convert next channel */
#define ADC_CONTINUE_NEXT           ADC_CR0_WAIT_EN_disable_w       /*!< ADC convert next channel than ADC will assert OVRF */
//!@}

#if defined(MG32_1ST) || defined(MG32_3RD) || defined(MG32_4TH)
/**
 * @name	ADC_Auto_Off
 *   		ADC save power option
 */ 
//!@{
#define ADC_SAVE_POWER              ADC_CR0_AUTOFF_EN_enable_w      /*!< ADC is automatically powered off except during active conversion phase. */
#define ADC_NORMAL_POWER            ADC_CR0_AUTOFF_EN_disable_w     /*!< ADC keep normal power. */
//!@}

#if defined(MG32_3RD) || defined(MG32_4TH)
/**
 * @name	ADC_SCNT_CLK_DIV
 *   		ADC power-on start up counter clock divider.
 */ 
//!@{
#define ADC_SCNT_CLK_DIV1           ADC_CLK_CK_SDIV_div1_w      /*!< ADC SCNT internal clock divider (DIV1) */
#define ADC_SCNT_CLK_DIV4           ADC_CLK_CK_SDIV_div4_w      /*!< ADC SCNT internal clock divider (DIV4) */
#define ADC_SCNT_CLK_DIV16          ADC_CLK_CK_SDIV_div16_w     /*!< ADC SCNT internal clock divider (DIV16) */
#define ADC_SCNT_CLK_DIV32          ADC_CLK_CK_SDIV_div32_w     /*!< ADC SCNT internal clock divider (DIV32) */
//!@}
#endif
#endif

#if defined(MG32_1ST) || defined(MG32_3RD)  
/**
 * @name	ADC_Trigger_Conversion_Source
 *   		ADC trigger converion source
 */ 
//!@{
#define ADC_SOFTWARE_START          ADC_START_START_SEL_sw_w        /*!< ADC Trigger Conversion: Software start setting. */
#define ADC_TM00_TRGO_TRIGGER       ADC_START_START_SEL_tm00_w      /*!< ADC Trigger Conversion: TM00_TRGO output. */
#define ADC_TRIGGER_PIN             ADC_START_START_SEL_pin_w       /*!< ADC Trigger Conversion: ADC_TRG pin. */
#define ADC_CMP0_OUT_TRIGGER        ADC_START_START_SEL_cmp0_w      /*!< ADC Trigger Conversion: CMP0 output. */
#define ADC_CMP1_OUT_TRIGGER        ADC_START_START_SEL_cmp1_w      /*!< ADC Trigger Conversion: CMP1 output. */
#define ADC_TM01_TRGO_TRIGGER       ADC_START_START_SEL_tm01_w      /*!< ADC Trigger Conversion: TM01_TRGO output. */
#define ADC_TM20_TRGO_TRIGGER       ADC_START_START_SEL_tm20_w      /*!< ADC Trigger Conversion: TM20_TRGO output. */
#define ADC_TM36_TRGO_TRIGGER       ADC_START_START_SEL_tm36_w      /*!< ADC Trigger Conversion: TM36_TRGO output. */
//!@}
#endif  

#if defined(MG32_2ND)
/**
 * @name	ADC_Trigger_Conversion_Source
 *   		ADC trigger converion source
 */ 
//!@{
#define ADC_SOFTWARE_START          ADC_START_START_SEL_sw_w        /*!< ADC Trigger Conversion: Software start setting. */
#define ADC_TM00_TRGO_TRIGGER       ADC_START_START_SEL_tm00_w      /*!< ADC Trigger Conversion: TM00_TRGO output. */
#define ADC_TRIGGER_PIN             ADC_START_START_SEL_pin_w       /*!< ADC Trigger Conversion: ADC_TRG pin. */
#define ADC_CMP0_OUT_TRIGGER        ADC_START_START_SEL_cmp0_w      /*!< ADC Trigger Conversion: CMP0 output. */
#define ADC_CMP1_OUT_TRIGGER        ADC_START_START_SEL_cmp1_w      /*!< ADC Trigger Conversion: CMP1 output. */
#define ADC_TM01_TRGO_TRIGGER       ADC_START_START_SEL_tm01_w      /*!< ADC Trigger Conversion: TM01_TRGO output. */
#define ADC_TM36_TRGO_TRIGGER       ADC_START_START_SEL_tm36_w      /*!< ADC Trigger Conversion: TM36_TRGO output. */
//!@}
#endif  

#if defined(MG32_4TH)
/**
 * @name	ADC_Trigger_Conversion_Source
 *   		ADC trigger converion source
 */ 
//!@{
#define ADC_SOFTWARE_START          ADC_START_START_SEL_sw_w        /*!< ADC Trigger Conversion: Software start setting. */
#define ADC_TM00_TRGO_TRIGGER       ADC_START_START_SEL_tm00_w      /*!< ADC Trigger Conversion: TM00_TRGO output. */
#define ADC_TRIGGER_PIN             ADC_START_START_SEL_pin_w       /*!< ADC Trigger Conversion: ADC_TRG pin. */
#define ADC_TM01_TRGO_TRIGGER       ADC_START_START_SEL_tm01_w      /*!< ADC Trigger Conversion: TM01_TRGO output. */
#define ADC_TM20_TRGO_TRIGGER       ADC_START_START_SEL_tm20_w      /*!< ADC Trigger Conversion: TM20_TRGO output. */
#define ADC_TM36_TRGO_TRIGGER       ADC_START_START_SEL_tm36_w      /*!< ADC Trigger Conversion: TM36_TRGO output. */
//!@}
#endif  

/**
 * @name	ADC_Trigger_Edge
 *   		ADC trigger converion edge selct
 */ 
//!@{
#define ADC_TRIGCONVEDGE_NONE       ADC_START_TRG_SEL_disable_w         /*!< Disable external trigger sourceg. */
#define ADC_TRIGCONVEDGE_RISING     ADC_START_TRG_SEL_rising_edge_w     /*!< Accept rising edge of external trigger. */
#define ADC_TRIGCONVEDGE_FALLING    ADC_START_TRG_SEL_falling_edge_w    /*!< Accept fallinf edge of external trigger. */
#define ADC_TRIGCONVEDGE_DUALEDGE   ADC_START_TRG_SEL_dual_edge_w       /*!< Accept dual edge of external trigger. */
//!@}

/**
 * @name	ADC_Overrun
 *   		ADC Overrun mode config
 */ 
//!@{
#define ADC_ACCEPT_OVERRUN          ADC_CR1_OVR_MDS_overwritten_w       /*!< Overwritten by new data */
#define ADC_PRESERVED_DATA          ADC_CR1_OVR_MDS_keep_w              /*!< Preserved old date */
//!@}


/**
 * @name	ADC_Conversion_Type
 *   		ADC conversion type
 */ 
//!@{
#define ADC_CONV_SINGLE             0                                   /*!< Single-End mode */
#if defined(MG32_1ST)                  
#define ADC_CONV_DIFFERENT          ADC_CR0_MDS_differential_w          /*!< Different mode */
#endif
//!@}


/**
 * @name	PGA_Command_Type
 *   		PGA Command type
 */ 
//!@{
#define PGA_ENABLE                  ADC_ANA_PGA_EN_enable_w             /*!< Enable ADC PGA */
#define PGA_DISABLE                 ADC_ANA_PGA_EN_disable_w            /*!< Disable ADC PGA */
//!@}



/** 
 * @struct  ADC_InitStructDef
 * @brief   AStructure definition of ADC initialization and regular group 
 */        
typedef struct __attribute__((packed))
{ 
    uint32_t ADCConType;            /*!< Select ADC Conversion type .
                                        This parameter can be a value of reference ADC_Conversion_Type. */
    
    uint32_t ADCClock;              /*!< Select ADC clock source (synchronous clock derived from APB clock or asynchronous clock derived from ADC dedicated HSI RC oscillator 14MHz) and clock prescaler.
                                        This parameter can be a value of reference ADC_ClockConfig. */
    
    uint32_t Resolution;            /*!< Configures the ADC resolution. 
                                        This parameter can be a value of reference ADC_Resolution */
    
    uint32_t DataAlign;             /*!< Specifies whether the ADC data  alignment is left or right.  
                                        This parameter can be a value of reference ADC_Data_align */
    
    uint32_t ConversionMode;        /*!< Configures the sequencer of regular group.
                                        This parameter can be associated to parameter 'DiscontinuousConvMode' to have main sequence subdivided in successive parts.
                                        Sequencer is automatically enabled if several channels are set:
                                        If only 1 channel is set: Conversion is performed in single mode.
                                        If several channels are set:  Conversions are performed in sequence mode (ranks defined by each channel number: channel 0 fixed on rank 0, channel 1 fixed on rank1, ...).
                                                                    Scan direction can be set to forward (from channel 0 to channel 18) or backward (from channel 18 to channel 0).
                                        This parameter can be a value of reference ADC_Conversion_mode */
    
    uint32_t LowPowerAutoWait;      /*!< Selects the dynamic low power Auto Delay: new conversion start only when the previous
                                        conversion (for regular group) has been treated by user software, using function MID_ADC_GetValue().
                                        This feature automatically adapts the ADC conversions trigs to the speed of the system that reads the data. Moreover, this avoids risk of overrun for low frequency applications. 
                                        This parameter can be a value of reference ADC_Wait_ReadData */
                                            
#if defined(MG32_1ST) || defined(MG32_3RD) || defined(MG32_4TH)
    uint32_t LowPowerAutoPowerOff;  /*!< Selects the auto-off mode: the ADC automatically powers-off after a conversion and automatically wakes-up when a new conversion is triggered (with startup time between trigger and start of sampling).
                                       This feature can be combined with automatic wait mode (parameter 'LowPowerAutoWait').
                                       This parameter can be a value of reference ADC_Auto_Off */
                                       
    uint32_t PowerupTimerDIV;       /*!< Select ADC power-on start up counter clock divider. (Only support MG32_3RD and MG32_4TH)
                                       This parameter can be a value of reference ADC_SCNT_CLK_DIV */ 

    uint32_t PowerupTimerCNT;       /*!< Select ADC power-on start up counter. (Only support MG32_3RD and MG32_4TH)
                                        This parameter can be set to 0~15. */
#endif
    
    uint32_t TriggerConverionSrc;   /*!< Selects the external event used to trigger the conversion start of regular group.
                                        If set to ADC_SOFTWARE_START, external triggers are disabled.
                                        This parameter can be a value of reference ADC_Trigger_Conversion_Source */
                                        
    uint32_t TriggerConverionEdge;  /*!< Selects the external trigger edge of regular group.
                                        If trigger is set to ADC_SOFTWARE_START, this parameter is discarded.
                                        This parameter can be a value of reference ADC_Trigger_Edge */
                                                                                
    uint32_t Overrun;               /*!< Select the behaviour in case of overrun: data preserved or overwritten 
                                        This parameter has an effect on regular group only, including in DMA mode.
                                        This parameter can be a value of reference ADC_Overrun */
                                        
    uint32_t ExtendSamplingTime;    /*!< Extend sampling time value in conversion state.
                                        This parameter can be set to 0~255 (Unit: ADC clock cycles). */
                                        
    uint32_t PGACmd;                /*!< ADC input buffer and PGA enable bit. (Only support MG32_1ST, MG32_2ND and MG32_3RD)
                                        This parameter can be PGA_ENABLE or PGA_DISABLE. */                
                                       
    uint32_t PGAGain;               /*!< ADC input PGA gain adjust bits. Gain range is 1 ~ 4. (Only support MG32_1ST, MG32_2ND and MG32_3RD) 
                                        ADC Gain is equal : (1+(ADC0_GAIN_PGA*3)/(63+(63-ADC0_GAIN_PGA)*3)) */                
                                       
}ADC_InitStructDef;


/**
 * @name	ADC_Interrupt_definition
 *   		ADC Interrupt Definition
 */ 
//!@{
#define ADC_IT_ESMP                 ADC_INT_ESMP_IE_enable_w            /*!< ADC interrupt of ESMP */
#define ADC_IT_E1CNV                ADC_INT_E1CNV_IE_enable_w           /*!< ADC interrupt of E1CNV */
#define ADC_IT_ESCNV                ADC_INT_ESCNV_IE_enable_w           /*!< ADC interrupt of ESCNV */
#define ADC_IT_OVR                  ADC_INT_OVR_IE_enable_w             /*!< ADC interrupt of OVR */
#define ADC_IT_WDL                  ADC_INT_WDL_IE_enable_w             /*!< ADC interrupt of WDL */
#define ADC_IT_WDI                  ADC_INT_WDI_IE_enable_w             /*!< ADC interrupt of WDI */
#define ADC_IT_WDH                  ADC_INT_WDH_IE_enable_w             /*!< ADC interrupt of WDH */
#define ADC_IT_SUMO                 ADC_INT_SUMO_IE_enable_w            /*!< ADC interrupt of SUMO */
#define ADC_IT_SUMC                 ADC_INT_SUMC_IE_enable_w            /*!< ADC interrupt of SUMC */
#define ADC_IT_SUMOVR               ADC_INT_SUMOVR_IE_enable_w          /*!< ADC interrupt of SUMOVR */
#define ADC_IT_CONVERSION	        (ADC_IT_E1CNV | ADC_IT_ESCNV)       /*!< ADC conversioned (E1CNV/ESCNV) */
#define ADC_IT_AWD				    (ADC_IT_WDL | ADC_IT_WDI | ADC_IT_WDH)  /*!< ADC window detect interrupt(WDL/WDI/WDH) */
#define ADC_IT_SUM				    (ADC_IT_SUMO | ADC_IT_SUMC | ADC_IT_SUMOVR) /*!< ADC accumulation interrupt(SUMO/SUMC/SUMOVR) */
//!@}


/**
 * @name	ADC_Flag_definition
 *   		ADC Flag Definition
 */ 
//!@{
#define ADC_FLAG_ESMP               ADC_STA_ESMPF_happened_w            /*!< ADC flag of ESMP */
#define ADC_FLAG_E1CNV              ADC_STA_E1CNVF_happened_w           /*!< ADC flag of E1CNV */
#define ADC_FLAG_ESCNV              ADC_STA_ESCNVF_happened_w           /*!< ADC flag of ESCNV */
#define ADC_FLAG_OVR                ADC_STA_OVRF_happened_w             /*!< ADC flag of OVR */
#define ADC_FLAG_WDL                ADC_STA_WDLF_happened_w             /*!< ADC flag of WDL */
#define ADC_FLAG_WDI                ADC_STA_WDIF_happened_w             /*!< ADC flag of WDI */
#define ADC_FLAG_WDH                ADC_STA_WDHF_happened_w             /*!< ADC flag of WDH */
#if defined(MG32_1ST)
#define ADC_FLAG_SUM_UNDER          ADC_STA_SUMUF_happened_w            /*!< ADC flag of SUMU */
#endif
#define ADC_FLAG_SUM_OVER           ADC_STA_SUMOF_happened_w            /*!< ADC flag of SUMO */
#define ADC_FLAG_SUM_COMPLETE       ADC_STA_SUMCF_happened_w            /*!< ADC flag of SUMC */
#define ADC_FLAG_SUM_OVR            ADC_STA_SUMOVRF_happened_w          /*!< ADC flag of SUMOVR */
#define ADC_FLAG_AWD				(ADC_FLAG_WDL | ADC_FLAG_WDI | ADC_FLAG_WDH)    /*!< ADC window detect flag (WDL/WDI/WDH) */
#if defined(MG32_1ST)
#define ADC_FLAG_SUM				(ADC_FLAG_SUM_OVER | ADC_FLAG_SUM_COMPLETE | ADC_FLAG_SUM_OVR | ADC_FLAG_SUM_UNDER)    /*!< ADC SUM flag (OVRF/CF/OF) */
#else
#define ADC_FLAG_SUM				(ADC_FLAG_SUM_OVER | ADC_FLAG_SUM_COMPLETE | ADC_FLAG_SUM_OVR)    /*!< ADC SUM flag (OVRF/CF/OF) */
#endif
//!@}


#if defined(MG32_1ST)
/**
 * @name	ADC_channels
 *   		ADC channel Definition
 */ 
//!@{
#define ADC_CHANNEL_0               ADC_START_CH_SEL_ext_w + (0U << 8)      /*!< External Pin: PA0 */
#define ADC_CHANNEL_1               ADC_START_CH_SEL_ext_w + (1U << 8)      /*!< External Pin: PA1 */
#define ADC_CHANNEL_2               ADC_START_CH_SEL_ext_w + (2U << 8)      /*!< External Pin: PA2 */
#define ADC_CHANNEL_3               ADC_START_CH_SEL_ext_w + (3U << 8)      /*!< External Pin: PA3 */
#define ADC_CHANNEL_4               ADC_START_CH_SEL_ext_w + (4U << 8)      /*!< External Pin: PA4 */
#define ADC_CHANNEL_5               ADC_START_CH_SEL_ext_w + (5U << 8)      /*!< External Pin: PA5 */
#define ADC_CHANNEL_6               ADC_START_CH_SEL_ext_w + (6U << 8)      /*!< External Pin: PA6 */
#define ADC_CHANNEL_7               ADC_START_CH_SEL_ext_w + (7U << 8)      /*!< External Pin: PA7 */
#define ADC_CHANNEL_8               ADC_START_CH_SEL_ext_w + (8U << 8)      /*!< External Pin: PA8 */
#define ADC_CHANNEL_9               ADC_START_CH_SEL_ext_w + (9U << 8)      /*!< External Pin: PA9 */
#define ADC_CHANNEL_10              ADC_START_CH_SEL_ext_w + (10U << 8)     /*!< External Pin: PA10 */
#define ADC_CHANNEL_11              ADC_START_CH_SEL_ext_w + (11U << 8)     /*!< External Pin: PA11 */
#define ADC_CHANNEL_12              ADC_START_CH_SEL_ext_w + (12U << 8)     /*!< External Pin: PA12 */
#define ADC_CHANNEL_13              ADC_START_CH_SEL_ext_w + (13U << 8)     /*!< External Pin: PA13 */
#define ADC_CHANNEL_14              ADC_START_CH_SEL_ext_w + (14U << 8)     /*!< External Pin: PA14 */
#define ADC_CHANNEL_15              ADC_START_CH_SEL_ext_w + (15U << 8)     /*!< External Pin: PA15 */
#define ADC_CHANNEL_16              ADC_START_CH_SEL_int_w + (00U << 8)     /*!< VSSA */
#define ADC_CHANNEL_17              ADC_START_CH_SEL_int_w + (01U << 8)     /*!< IVREF */
#define ADC_CHANNEL_18              ADC_START_CH_SEL_int_w + (02U << 8)     /*!< DAC_P0 */
#define ADC_CHANNEL_19              ADC_START_CH_SEL_int_w + (03U << 8)     /*!< VBUF 1.4V */
//!@}
#endif


#if defined(MG32_2ND)
/**
 * @name	ADC_channels
 *   		ADC channel Definition
 */ 
//!@{
#define ADC_CHANNEL_0               ADC_START_CH_SEL_ext_w + (0U << 8)      /*!< External Pin: PA0 */
#define ADC_CHANNEL_1               ADC_START_CH_SEL_ext_w + (1U << 8)      /*!< External Pin: PA1 */
#define ADC_CHANNEL_2               ADC_START_CH_SEL_ext_w + (2U << 8)      /*!< External Pin: PA2 */
#define ADC_CHANNEL_3               ADC_START_CH_SEL_ext_w + (3U << 8)      /*!< External Pin: PA3 */
#define ADC_CHANNEL_8               ADC_START_CH_SEL_ext_w + (8U << 8)      /*!< External Pin: PA8 */
#define ADC_CHANNEL_9               ADC_START_CH_SEL_ext_w + (9U << 8)      /*!< External Pin: PA9 */
#define ADC_CHANNEL_10              ADC_START_CH_SEL_ext_w + (10U << 8)     /*!< External Pin: PA10 */
#define ADC_CHANNEL_11              ADC_START_CH_SEL_ext_w + (11U << 8)     /*!< External Pin: PA11 */
#define ADC_CHANNEL_12              ADC_START_CH_SEL_ext_w + (12U << 8)     /*!< External Pin: PA12 */
#define ADC_CHANNEL_13              ADC_START_CH_SEL_ext_w + (13U << 8)     /*!< External Pin: PA13 */
#define ADC_CHANNEL_14              ADC_START_CH_SEL_ext_w + (14U << 8)     /*!< External Pin: PA14 */
#define ADC_CHANNEL_15              ADC_START_CH_SEL_ext_w + (15U << 8)     /*!< External Pin: PA15 */
#define ADC_CHANNEL_16              ADC_START_CH_SEL_int_w + (00U << 8)     /*!< VSSA */
#define ADC_CHANNEL_17              ADC_START_CH_SEL_int_w + (01U << 8)     /*!< IVREF */
#define ADC_CHANNEL_19              ADC_START_CH_SEL_int_w + (03U << 8)     /*!< VBUF 1.4V */
#define ADC_CHANNEL_24              ADC_START_CH_SEL_int_w + (08U << 8)     /*!< LDO VR0  */
//!@}
#endif


#if defined(MG32_3RD)
/**
 * @name	ADC_channels
 *   		ADC channel Definition
 */ 
//!@{
#define ADC_CHANNEL_0               ADC_START_CH_SEL_ext_w + (0U << 8)      /*!< External Pin: PA0 */
#define ADC_CHANNEL_1               ADC_START_CH_SEL_ext_w + (1U << 8)      /*!< External Pin: PA1 */
#define ADC_CHANNEL_2               ADC_START_CH_SEL_ext_w + (2U << 8)      /*!< External Pin: PA2 */
#define ADC_CHANNEL_3               ADC_START_CH_SEL_ext_w + (3U << 8)      /*!< External Pin: PA3 */
#define ADC_CHANNEL_4               ADC_START_CH_SEL_ext_w + (4U << 8)      /*!< External Pin: PA4 */
#define ADC_CHANNEL_5               ADC_START_CH_SEL_ext_w + (5U << 8)      /*!< External Pin: PA5 */
#define ADC_CHANNEL_6               ADC_START_CH_SEL_ext_w + (6U << 8)      /*!< External Pin: PA6 */
#define ADC_CHANNEL_7               ADC_START_CH_SEL_ext_w + (7U << 8)      /*!< External Pin: PA7 */
#define ADC_CHANNEL_8               ADC_START_CH_SEL_ext_w + (8U << 8)      /*!< External Pin: PA8 */
#define ADC_CHANNEL_9               ADC_START_CH_SEL_ext_w + (9U << 8)      /*!< External Pin: PA9 */
#define ADC_CHANNEL_10              ADC_START_CH_SEL_ext_w + (10U << 8)     /*!< External Pin: PA10 */
#define ADC_CHANNEL_11              ADC_START_CH_SEL_ext_w + (11U << 8)     /*!< External Pin: PA11 */
#define ADC_CHANNEL_12              ADC_START_CH_SEL_ext_w + (12U << 8)     /*!< External Pin: PA12 */
#define ADC_CHANNEL_13              ADC_START_CH_SEL_ext_w + (13U << 8)     /*!< External Pin: PA13 */
#define ADC_CHANNEL_14              ADC_START_CH_SEL_ext_w + (14U << 8)     /*!< External Pin: PA14 */
#define ADC_CHANNEL_15              ADC_START_CH_SEL_ext_w + (15U << 8)     /*!< External Pin: PA15 */
#define ADC_CHANNEL_16              ADC_START_CH_SEL_int_w + (00U << 8)     /*!< VSSA */
#define ADC_CHANNEL_18              ADC_START_CH_SEL_int_w + (02U << 8)     /*!< DAC_P0 */
#define ADC_CHANNEL_19              ADC_START_CH_SEL_int_w + (03U << 8)     /*!< VBUF 1.4V */
#define ADC_CHANNEL_24              ADC_START_CH_SEL_int_w + (08U << 8)     /*!< LDO VR0  */
#define ADC_CHANNEL_25              ADC_START_CH_SEL_int_w + (09U << 8)     /*!< Temperature sensor (TSO) */
#define ADC_CHANNEL_26              ADC_START_CH_SEL_int_w + (10U << 8)     /*!< 1/2 VDD */
#define ADC_CHANNEL_27              ADC_START_CH_SEL_int_w + (11U << 8)     /*!< VPG */
#define ADC_CHANNEL_28              ADC_START_CH_SEL_int_w + (12U << 8)     /*!< V33 */
//!@}
#endif


#if defined(MG32_4TH)
/**
 * @name	ADC_channels
 *   		ADC channel Definition
 */ 
//!@{
#define ADC_CHANNEL_0               ADC_START_CH_SEL_ext_w + (0U << 8)      /*!< External Pin: PA0 */
#define ADC_CHANNEL_1               ADC_START_CH_SEL_ext_w + (1U << 8)      /*!< External Pin: PA1 */
#define ADC_CHANNEL_2               ADC_START_CH_SEL_ext_w + (2U << 8)      /*!< External Pin: PA2 */
#define ADC_CHANNEL_3               ADC_START_CH_SEL_ext_w + (3U << 8)      /*!< External Pin: PA3 */
#define ADC_CHANNEL_8               ADC_START_CH_SEL_ext_w + (8U << 8)      /*!< External Pin: PA8 */
#define ADC_CHANNEL_9               ADC_START_CH_SEL_ext_w + (9U << 8)      /*!< External Pin: PA9 */
#define ADC_CHANNEL_10              ADC_START_CH_SEL_ext_w + (10U << 8)     /*!< External Pin: PA10 */
#define ADC_CHANNEL_11              ADC_START_CH_SEL_ext_w + (11U << 8)     /*!< External Pin: PA11 */
#define ADC_CHANNEL_16              ADC_START_CH_SEL_int_w + (00U << 8)     /*!< VSSA */
#define ADC_CHANNEL_19              ADC_START_CH_SEL_int_w + (03U << 8)     /*!< VBUF 1.4V */
#define ADC_CHANNEL_20              ADC_START_CH_SEL_int_w + (08U << 8)     /*!< LDO VR0  */
#define ADC_CHANNEL_24              ADC_START_CH_SEL_int_w + (09U << 8)     /*!< Temperature sensor (TSO) */
//!@}
#endif


#if defined(MG32_1ST) || defined(MG32_3RD)
/**
 * @name	ADC_regular_sequence
 *   		ADC regular scan/loop sequence 
 */ 
//!@{
#define ADC_ScanCHANNEL_0           ADC_MSK_CH_MSK0_mask_h0                 /*!< Scan/Loop Channel indicate : Channel 0 */
#define ADC_ScanCHANNEL_1           ADC_MSK_CH_MSK1_mask_h0                 /*!< Scan/Loop Channel indicate : Channel 1 */
#define ADC_ScanCHANNEL_2           ADC_MSK_CH_MSK2_mask_h0                 /*!< Scan/Loop Channel indicate : Channel 2 */
#define ADC_ScanCHANNEL_3           ADC_MSK_CH_MSK3_mask_h0                 /*!< Scan/Loop Channel indicate : Channel 3 */
#define ADC_ScanCHANNEL_4           ADC_MSK_CH_MSK4_mask_h0                 /*!< Scan/Loop Channel indicate : Channel 4 */
#define ADC_ScanCHANNEL_5           ADC_MSK_CH_MSK5_mask_h0                 /*!< Scan/Loop Channel indicate : Channel 5 */
#define ADC_ScanCHANNEL_6           ADC_MSK_CH_MSK6_mask_h0                 /*!< Scan/Loop Channel indicate : Channel 6 */
#define ADC_ScanCHANNEL_7           ADC_MSK_CH_MSK7_mask_h0                 /*!< Scan/Loop Channel indicate : Channel 7 */
#define ADC_ScanCHANNEL_8           ADC_MSK_CH_MSK8_mask_h0                 /*!< Scan/Loop Channel indicate : Channel 8 */
#define ADC_ScanCHANNEL_9           ADC_MSK_CH_MSK9_mask_h0                 /*!< Scan/Loop Channel indicate : Channel 9 */
#define ADC_ScanCHANNEL_10          ADC_MSK_CH_MSK10_mask_h0                /*!< Scan/Loop Channel indicate : Channel 10 */
#define ADC_ScanCHANNEL_11          ADC_MSK_CH_MSK11_mask_h0                /*!< Scan/Loop Channel indicate : Channel 11 */
#define ADC_ScanCHANNEL_12          ADC_MSK_CH_MSK12_mask_h0                /*!< Scan/Loop Channel indicate : Channel 12 */
#define ADC_ScanCHANNEL_13          ADC_MSK_CH_MSK13_mask_h0                /*!< Scan/Loop Channel indicate : Channel 13 */
#define ADC_ScanCHANNEL_14          ADC_MSK_CH_MSK14_mask_h0                /*!< Scan/Loop Channel indicate : Channel 14 */
#define ADC_ScanCHANNEL_15          ADC_MSK_CH_MSK15_mask_h0                /*!< Scan/Loop Channel indicate : Channel 15 */
//!@}
#endif

#if defined(MG32_2ND)
/**
 * @name	ADC_regular_sequence
 *   		ADC regular scan/loop sequence 
 */ 
//!@{
#define ADC_ScanCHANNEL_0           ADC_MSK_CH_MSK0_mask_h0                 /*!< Scan/Loop Channel indicate : Channel 0 */
#define ADC_ScanCHANNEL_1           ADC_MSK_CH_MSK1_mask_h0                 /*!< Scan/Loop Channel indicate : Channel 1 */
#define ADC_ScanCHANNEL_2           ADC_MSK_CH_MSK2_mask_h0                 /*!< Scan/Loop Channel indicate : Channel 2 */
#define ADC_ScanCHANNEL_3           ADC_MSK_CH_MSK3_mask_h0                 /*!< Scan/Loop Channel indicate : Channel 3 */
#define ADC_ScanCHANNEL_8           ADC_MSK_CH_MSK8_mask_h0                 /*!< Scan/Loop Channel indicate : Channel 8 */
#define ADC_ScanCHANNEL_9           ADC_MSK_CH_MSK9_mask_h0                 /*!< Scan/Loop Channel indicate : Channel 9 */
#define ADC_ScanCHANNEL_10          ADC_MSK_CH_MSK10_mask_h0                /*!< Scan/Loop Channel indicate : Channel 10 */
#define ADC_ScanCHANNEL_11          ADC_MSK_CH_MSK11_mask_h0                /*!< Scan/Loop Channel indicate : Channel 11 */
#define ADC_ScanCHANNEL_12          ADC_MSK_CH_MSK12_mask_h0                /*!< Scan/Loop Channel indicate : Channel 12 */
#define ADC_ScanCHANNEL_13          ADC_MSK_CH_MSK13_mask_h0                /*!< Scan/Loop Channel indicate : Channel 13 */
#define ADC_ScanCHANNEL_14          ADC_MSK_CH_MSK14_mask_h0                /*!< Scan/Loop Channel indicate : Channel 14 */
#define ADC_ScanCHANNEL_15          ADC_MSK_CH_MSK15_mask_h0                /*!< Scan/Loop Channel indicate : Channel 15 */
//!@}
#endif


#if defined(MG32_4TH)
/**
 * @name	ADC_regular_sequence
 *   		ADC regular scan/loop sequence 
 */ 
//!@{
#define ADC_ScanCHANNEL_0           ADC_MSK_CH_MSK0_mask_h0                 /*!< Scan/Loop Channel indicate : Channel 0 */
#define ADC_ScanCHANNEL_1           ADC_MSK_CH_MSK1_mask_h0                 /*!< Scan/Loop Channel indicate : Channel 1 */
#define ADC_ScanCHANNEL_2           ADC_MSK_CH_MSK2_mask_h0                 /*!< Scan/Loop Channel indicate : Channel 2 */
#define ADC_ScanCHANNEL_3           ADC_MSK_CH_MSK3_mask_h0                 /*!< Scan/Loop Channel indicate : Channel 3 */
#define ADC_ScanCHANNEL_8           ADC_MSK_CH_MSK8_mask_h0                 /*!< Scan/Loop Channel indicate : Channel 8 */
#define ADC_ScanCHANNEL_9           ADC_MSK_CH_MSK9_mask_h0                 /*!< Scan/Loop Channel indicate : Channel 9 */
#define ADC_ScanCHANNEL_10          ADC_MSK_CH_MSK10_mask_h0                /*!< Scan/Loop Channel indicate : Channel 10 */
#define ADC_ScanCHANNEL_11          ADC_MSK_CH_MSK11_mask_h0                /*!< Scan/Loop Channel indicate : Channel 11 */
//!@}
#endif


/** 
 * @struct  ADC_ChannelConfTypeDef
 * @brief   Structure definition of ADC one-shot or scan/loop channel group
 */        
typedef struct __attribute__((packed)) 
{ 
    uint32_t Channel;                   /*!< Specifies the channel to configure into ADC regular group.
                                             This parameter can be a value of reference ADC_channels
                                             Note: Depending on devices, some channels may not be available on package pins. Refer to device datasheet for channels availability. */
        
    uint32_t SequenceChannelMUX;        /*!< Specifies the sequence channel in the regular group sequencer 
                                            This parameter can be a value of reference ADC_regular_sequence.
                                            Note: This function only support external channel scan/loop channel mux. 
                                            Note: If SequenceChannelMUX=(ADC_ScanCHANNEL_1 | ADC_ScanCHANNEL_9 | ADC_ScanCHANNEL_15) then ADC will start convert with channel1, 9 and channel 15.*/
                                        
} ADC_ChannelConfTypeDef;
    

/** 
 * @struct  ADC_HandleTypeDef
 * @brief   ADC handle Structure definition  
 */        
typedef struct __attribute__((packed))
{
    ADC_Struct          *Instance;      /*!< Register base address */
                    
    ADC_InitStructDef   Init;           /*!< ADC required parameters */
                    
    DMA_HandleTypeDef   *DMA_Handle;    /*!< Pointer DMA Handler */
                    
    MID_LockTypeDef     Lock;           /*!< ADC locking object */
                    
    __IO uint32_t       State;          /*!< ADC communication state (bitmap of ADC states) */
                    
    __IO uint32_t       ErrorCode;      /*!< ADC Error code */

}ADC_HandleTypeDef;


/**
 * @name	ADC_analog_watchdog_mode
 *   		ADC analog watchdog mode
 */ 
//!@{
#define ADC_ANALOGWATCHDOG_NONE             ADC_CR1_WIND_EN_disable_w                               /*!< Disable window detect function */
#define ADC_ANALOGWATCHDOG_SINGLE_REG       ADC_CR1_WIND_EN_enable_w + ADC_CR1_WIND_MDS_single_w    /*!< Window detect function for single channel */
#define ADC_ANALOGWATCHDOG_ALL_REG          ADC_CR1_WIND_EN_enable_w + ADC_CR1_WIND_MDS_all_w       /*!< Window detect function apply any channel */
//!@}

/**
 * @name	ADC_WatchdogDataLimit
 *   		ADC analog watchdog data output when data outside the threshold
 */ 
//!@{
#define ADC_ANALOGWATCHDOG_KEEP_DATA        ADC_CR0_LIM_MDS_no_operation_w              /*!< Accept conversion data even it outside threshold */        
#define ADC_ANALOGWATCHDOG_SKIP_DATA        ADC_CR0_LIM_MDS_skip_w                      /*!< Skip conversion data when it outside threshold */
#define ADC_ANALOGWATCHDOG_CLAMP_THRESHOLD  ADC_CR0_LIM_MDS_clamp_w                     /*!< Clamp conversion data when it outside threshold */
//!@}


/** 
 * @struct  ADC_AnalogWDGConfTypeDef
 * @brief   ADC analog watchdog Define
 */        
typedef struct __attribute__((packed))
{
  uint32_t WatchdogMode;      /*!< Configures the ADC analog watchdog mode: single/all/none channels.
                                   This parameter can be a value of reference ADC_analog_watchdog_mode. */
    
  uint32_t Channel;           /*!< Selects which ADC channel to monitor by analog watchdog.
                                   This parameter has an effect only if parameter 'WatchdogMode' is configured on single channel. Only 1 channel can be monitored.
                                   This parameter can be a value of reference ADC_channels. (Support channel 0~15 Only. No matter external or internal channel.) */
    
  uint32_t ITMode;            /*!< Specifies whether the analog watchdog is configured in interrupt or polling mode.
                                   This parameter can be set to ADC_IT_WDL, ADC_IT_WDI or ADC_IT_WDH */
    
  uint32_t HighThreshold;     /*!< Configures the ADC analog watchdog High threshold value.
                                   Depending of ADC resolution selected (12, 10 or 8 bits), this parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF, 0x3FF or 0xFF respectively. */
    
  uint32_t LowThreshold;      /*!< Configures the ADC analog watchdog High threshold value.
                                   Depending of ADC resolution selected (12, 10 or 8 bits), this parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF, 0x3FF or 0xFF respectively. */
    
  uint32_t WatchdogDataLimit; /*!< Selects which ADC data output mode if it outside the threshokd.
                                   This parameter can be a value of reference ADC_WatchdogDataLimit.  */
}ADC_AnalogWDGConfTypeDef;


/** 
 * @enum		MID_ADC_StateTypeDef
 * @brief		MID ADC State definition 
 */        
typedef enum __attribute__((packed)) 
{
    MID_ADC_STATE_RESET             = 0x00U,    /*!< Peripheral not yet initialized or disabled  */
    MID_ADC_STATE_READY             = 0x01U,    /*!< Peripheral Initialized and ready for use    */
    MID_ADC_STATE_BUSY_INTERNAL     = 0x02U,    /*!< An internal process is ongoing              */
    MID_ADC_STATE_TIMEOUT           = 0x03U,    /*!< Timeout state                               */
    MID_ADC_STATE_AWD1              = 0x04U,    /*!< Out-of-window occurrence of analog watchdog 1  */ 
	MID_ADC_STATE_REG_OVR			= 0x05U,    /*!< ADC occurred overrun event                  */
	MID_ADC_STATE_REG_BUSY			= 0x06U     /*!< A conversion on group regular is ongoing or 
                                                     can occur (either by continuous mode,
                                                     external trigger, low power auto power-on,
                                                     multimode ADC master control) */
}MID_ADC_StateTypeDef;


/** 
 * @enum		ADC_Error_Code
 * @brief		ADC Error Code definition 
 */        
typedef enum __attribute__((packed)) 
{
    MID_ADC_ERROR_NONE              = 0x00U,    /*!< Peripheral not yet initialized or disabled  */
    MID_ADC_ERROR_INTERNAL          = 0x01U,    /*!< An internal process is ongoing              */
    MID_ADC_ERROR_OVR               = 0x02U,    /*!< Peripheral Initialized and ready for use    */
    MID_ADC_ERROR_DMA               = 0x03U,    /*!< Timeout state                               */
    MID_ADC_STATE_ERROR_DMA         = 0X04U     /*!< DMA error occurrence                        */
}ADC_Error_Code;


/**
 * @name	ADC_Event_type
 *   		ADC Event type
 */ 
//!@{
#define ADC_CONVERSAION_EVENT       (ADC_FLAG_E1CNV | ADC_FLAG_ESCNV)                                   /*!< ADC conversioned event */
#define ADC_AWD_EVENT               (ADC_FLAG_WDL | ADC_FLAG_WDI | ADC_FLAG_WDH)                        /*!< ADC Analog watchdog event */
#define ADC_SUM_EVENT               (ADC_FLAG_SUM_OVER | ADC_FLAG_SUM_COMPLETE | ADC_FLAG_SUM_OVR)      /*!< ADC SUM event */
#define ADC_OVR_EVENT               (ADC_STA_OVRF_mask_w)                                               /*!< ADC overrun event */
//!@}


/**
 * @name	ADC_Accumulation_mode
 *   		ADC Accumulation Mode
 */ 
//!@{
#define ADC_ACCUMULATE_DECLARE_SUMCH    (ADC_CR1_SUM_MDS_single_w)      /*!< SUM0_Channel selection channel data is accumulated into ADC0_SUM0 */
#define ADC_ACCUMULATE_ALL_DATA         (ADC_CR1_SUM_MDS_all_w)         /*!< ADC accumulate any convert data into sum0 channel */
//!@}


/**
 * @name	ADC_SUM_Overrun
 *   		ADC SUM DATA Overrun mode config
 */ 
//!@{
#define ADC_SUM_ACCEPT_OVERRUN          ADC_CR1_SOVR_MDS_overwritten_w  /*!< Overwritten by new data */
#define ADC_SUM_PRESERVED_DATA          ADC_CR1_SOVR_MDS_keep_w         /*!< Preserved old date */
//!@}

/**
 * @name	ADC_SUMx_channels
 *   		Assign ADC SUM0/1/2 channel 
 */ 
//!@{
#define ADC_SUMx_CHANNEL0               (0x0U)                  /*!< Channel indicate for accumulation : Channel 0 */     
#define ADC_SUMx_CHANNEL1               (0x1U)                  /*!< Channel indicate for accumulation : Channel 1 */
#define ADC_SUMx_CHANNEL2               (0x2U)                  /*!< Channel indicate for accumulation : Channel 2 */
#define ADC_SUMx_CHANNEL3               (0x3U)                  /*!< Channel indicate for accumulation : Channel 3 */
#define ADC_SUMx_CHANNEL4               (0x4U)                  /*!< Channel indicate for accumulation : Channel 4 */
#define ADC_SUMx_CHANNEL5               (0x5U)                  /*!< Channel indicate for accumulation : Channel 5 */
#define ADC_SUMx_CHANNEL6               (0x6U)                  /*!< Channel indicate for accumulation : Channel 6 */
#define ADC_SUMx_CHANNEL7               (0x7U)                  /*!< Channel indicate for accumulation : Channel 7 */
#define ADC_SUMx_CHANNEL8               (0x8U)                  /*!< Channel indicate for accumulation : Channel 8 */
#define ADC_SUMx_CHANNEL9               (0x9U)                  /*!< Channel indicate for accumulation : Channel 9 */
#define ADC_SUMx_CHANNEL10              (0xAU)                  /*!< Channel indicate for accumulation : Channel 10 */
#define ADC_SUMx_CHANNEL11              (0xBU)                  /*!< Channel indicate for accumulation : Channel 11 */
#define ADC_SUMx_CHANNEL12              (0xCU)                  /*!< Channel indicate for accumulation : Channel 12 */
#define ADC_SUMx_CHANNEL13              (0xDU)                  /*!< Channel indicate for accumulation : Channel 13 */
#define ADC_SUMx_CHANNEL14              (0xEU)                  /*!< Channel indicate for accumulation : Channel 14 */
#define ADC_SUMx_CHANNEL15              (0xFU)                  /*!< Channel indicate for accumulation : Channel 15 */
//!@} 


/** 
 * @struct  ADC_AccumulateConfDef
 * @brief   ADC Accumulate Config Define
 */        
typedef struct __attribute__((packed))
{
    uint32_t AccumulationMode;      /*!< Configures the ADC analog watchdog mode: single/all/none channels.
                                        This parameter can be a value of reference ADC_Accumulation_mode. */
    
    uint32_t SUM0_Channel;          /*!< Selects which ADC channel to accumulation by SUM0.
                                        This parameter can be a value of reference ADC_SUMx_channels. (Support channel 0~15 Only. No matter external or internal channel.) */
        
    uint32_t SUM1_Channel;          /*!< Selects which ADC channel to accumulation by SUM1.
                                        This parameter has an effect only if parameter 'WatchdogMode' is configured on single channel. Only 1 channel can be monitored.
                                        This parameter can be a value of reference ADC_SUMx_channels. (Support channel 0~15 Only. No matter external or internal channel.) */
        
    uint32_t SUM2_Channel;          /*!< Selects which ADC channel to accumulation by SUM2.
                                        This parameter can be a value of reference ADC_SUMx_channels. (Support channel 0~15 Only. No matter external or internal channel.) */
    
    uint32_t SUM0_Init;             /*!< Initial SUM0 for accumulation. */
        
    uint32_t SUM1_Init;             /*!< Initial SUM1 for accumulation. */
        
    uint32_t SUM2_Init;             /*!< Initial SUM2 for accumulation. */
    
    uint32_t ITMode;                /*!< Specifies whether the accumulate is configured in interrupt or polling mode.
                                        This parameter can be set to ADC_IT_SUMO, ADC_IT_SUMC or ADC_IT_SUMOVR */
    
    uint32_t AccumulateNumber;      /*!< Specifies whether the the number of accumulation.
                                        This parameter can be set between 0 to 63 */
    
    uint32_t SOverrun;              /*!< Select the behaviour in case of overrun: data preserved or overwritten 
                                       This parameter can be a value of reference ADC_SUM_Overrun for SUM0/1/2 data */
                                       
}ADC_AccumulateConfDef;



#if defined(MG32_3RD) || defined(MG32_4TH)
/**
 * @name	ADC_Conversion_Time
 *   		ADC minimum conversion time select
 */ 
//!@{
#define ADC_FAST_CONVERSION             (ADC_ANA_CONV_TIME_24adck_w)    /*!< 24ADCK : 24 ADC sampleing clock. */     
#define ADC_NORMAL_CONVERSION           (ADC_ANA_CONV_TIME_30adck_w)    /*!< 30ADCK : 30 ADC sampleing clock. */
//!@} 


/**
 * @name	ADC_SampleClockPhase_Select
 *   		ADC sampling clock phase delay select.
 */ 
//!@{
#define ADC_CLOCK_PHASE0                (ADC_CLK_CK_DLY_no_w)           /*!< Bypass.                            */     
#define ADC_CLOCK_PHASE1                (ADC_CLK_CK_DLY_dly_w)          /*!< One step delay.                    */     
#define ADC_CLOCK_PHASE2                (ADC_CLK_CK_DLY_inv_w)          /*!< Clock invert.                      */     
#define ADC_CLOCK_PHASE3                (ADC_CLK_CK_DLY_idly_w)         /*!< Clock invert with one step delay.  */     
//!@} 
#endif



#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
/**
 * @name	ADC_OperationBias_Select
 *   		ADC operation bias current definition
 */ 
//!@{
#define ADC_OP_BIAS_LVL0                (ADC_ANA_BIAS_lvl0_w)           /*!< LVL0 : Lowest current.     */     
#define ADC_OP_BIAS_LVL1                (ADC_ANA_BIAS_lvl1_w)           /*!< LVL1 : Lower current.      */
#define ADC_OP_BIAS_LVL2                (ADC_ANA_BIAS_lvl2_w)           /*!< LVL2 : Higher current.     */
#define ADC_OP_BIAS_LVL3                (ADC_ANA_BIAS_lvl3_w)           /*!< LVL3 : Highest current.    */ 
//!@} 
#endif


/**
 *******************************************************************************
 * @brief       Enable the ADC peripheral
 * @param[in]   "__HANDLE__" : pointer to a ADC_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
#define __DRV_ADC_ENABLE(__HANDLE__)                                           \
  ((__HANDLE__)->Instance->CR0.W |= ADC_CR0_EN_enable_w)


/**
 *******************************************************************************
 * @brief       Disable the ADC peripheral
 * @param[in]   "__HANDLE__" : pointer to a ADC_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
#define __DRV_ADC_DISABLE(__HANDLE__)                                           \
  ((__HANDLE__)->Instance->CR0.W &= ~ADC_CR0_EN_enable_w)


/**
 *******************************************************************************
 * @brief       Enables the specified ADC interrupt.
 * @param[in]   "__HANDLE__" : pointer to a ADC_HandleTypeDef
 * @param[in]   "__INTERRUPT__" : specifies the ADC interrupt source to enable.
 *  @arg\b	    ADC_IT_ESMP : Sampling end interrupt.
 *  @arg\b	    ADC_IT_E1CNV : One-time conversion end interrupt
 *  @arg\b	    ADC_IT_ESCNV : Channel scan conversion end interrupt
 *  @arg\b	    ADC_IT_OVR : Conversion overrun event interrupt
 *	@arg\b	    ADC_IT_WDL : Voltage window detect outside low event interrupt 
 *	@arg\b	    ADC_IT_WDI : voltage window detect inside event interrupt 
 *	@arg\b	    ADC_IT_WDH : Voltage window detect outside high event interrupt 
 *	@arg\b	    ADC_IT_SUMO : Sum-0,1,2 accumulation overflow or underflow interrupt 
 *	@arg\b	    ADC_IT_SUMC : Sum-0,1,2 accumulation complete interrupt 
 *	@arg\b	    ADC_IT_SUMOVR : Sum-0,1,2 overrun event interrupt
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_ADC_ENABLE_IT(&ADC_Handle,ADC_IT_UPDATE);
 * @endcode
 *******************************************************************************
 */
#define __DRV_ADC_ENABLE_IT(__HANDLE__, __INTERRUPT__)    ((__HANDLE__)->Instance->INT.W |= (__INTERRUPT__))


/**
 *******************************************************************************
 * @brief       Disables the specified ADC interrupt.
 * @param[in]   "__HANDLE__" : pointer to a ADC_HandleTypeDef
 * @param[in]   "__INTERRUPT__" : specifies the ADC interrupt source to enable.
 *  @arg\b	    ADC_IT_ESMP : Sampling end interrupt.
 *  @arg\b	    ADC_IT_E1CNV : One-time conversion end interrupt
 *  @arg\b	    ADC_IT_ESCNV : Channel scan conversion end interrupt
 *  @arg\b	    ADC_IT_OVR : Conversion overrun event interrupt
 *	@arg\b	    ADC_IT_WDL : Voltage window detect outside low event interrupt 
 *	@arg\b	    ADC_IT_WDI : Voltage window detect inside event interrupt 
 *	@arg\b	    ADC_IT_WDH : Voltage window detect outside high event interrupt 
 *	@arg\b	    ADC_IT_SUMO : Sum-0,1,2 accumulation overflow or underflow interrupt 
 *	@arg\b	    ADC_IT_SUMC : Sum-0,1,2 accumulation complete interrupt 
 *	@arg\b	    ADC_IT_SUMOVR : Sum-0,1,2 overrun event interrupt
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_ADC_DISABLE_IT(&mADC,ADC_IT_CC0);
 * @endcode
 *******************************************************************************
 */
#define __DRV_ADC_DISABLE_IT(__HANDLE__, __INTERRUPT__)    ((__HANDLE__)->Instance->INT.W &= ~(__INTERRUPT__))


/**
 *******************************************************************************
 * @brief       Checks whether the specified ADC interrupt has occurred or not.
 * @param[in]   "__HANDLE__" : pointer to a ADC_HandleTypeDef
 * @param[in]   "__INTERRUPT__ : specifies the ADC interrupt source to enable.
 *  @arg\b	    ADC_IT_ESMP : Sampling end interrupt.
 *  @arg\b	    ADC_IT_E1CNV : One-time conversion end interrupt
 *  @arg\b	    ADC_IT_ESCNV : Channel scan conversion end interrupt
 *  @arg\b	    ADC_IT_OVR : Conversion overrun event interrupt
 *	@arg\b	    ADC_IT_WDL : Voltage window detect outside low event interrupt 
 *	@arg\b	    ADC_IT_WDI : Voltage window detect inside event interrupt 
 *	@arg\b	    ADC_IT_WDH : Voltage window detect outside high event interrupt 
 *	@arg\b	    ADC_IT_SUMO : Sum-0,1,2 accumulation overflow or underflow interrupt 
 *	@arg\b	    ADC_IT_SUMC : Sum-0,1,2 accumulation complete interrupt 
 *	@arg\b	    ADC_IT_SUMOVR : Sum-0,1,2 overrun event interrupt
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_ADC_GET_IT_SOURCE(&ADC_Handle, ADC_IT_SUMC);
 * @endcode
 *******************************************************************************
 */
#define __DRV_ADC_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->Instance->INT.W & (__INTERRUPT__)) == (__INTERRUPT__)) ? ENABLE : DISABLE)

/**
 *******************************************************************************
 * @brief       Checks whether the specified ADC interrupt has occurred or not.
 * @param[in]   "__HANDLE__": specifies the ADC Handle.
 * @param[in]   "__INTEVENT__" : specifies the ADC interrupt flag to clear.
 *  @arg\b	    ADC_IT_CONVERSION : ADC conversioned interrupt group (E1CNV/ESCNV).     
 *  @arg\b	    ADC_IT_AWD : AWD interrupt group (WDH/WDI/WDL).     
 *  @arg\b	    ADC_IT_SUM : SUM interrupt group (Overrun/Complete/Overflow).      
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_ADC_GET_IT_EVENT(&ADC_Handle, ADC_SUM_EVENT);
 * @endcode
 *******************************************************************************
 */
#define __DRV_ADC_GET_IT_EVENT(__HANDLE__,__INTEVENT__)      (((__HANDLE__)->Instance->INT.W & (__INTEVENT__)) != (0U))


/**
 *******************************************************************************
 * @brief       Enables the specified ADC All interrupt.
 * @param[in]   "__HANDLE__" : pointer to a ADC_HandleTypeDef
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_ADC_ENABLE_ITEA(&mADC);
 * @endcode
 *******************************************************************************
 */
#define __DRV_ADC_ENABLE_ITEA(__HANDLE__)    ((__HANDLE__)->Instance->INT.W |= ADC_INT_IEA_enable_w)

/**
 *******************************************************************************
 * @brief       Disables the specified ADC All interrupt.
 * @param[in]   "__HANDLE__" : pointer to a ADC_HandleTypeDef
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_ADC_DISABLE_ITEA(&mADC);
 * @endcode
 *******************************************************************************
 */
#define __DRV_ADC_DISABLE_ITEA(__HANDLE__)    ((__HANDLE__)->Instance->INT.W &= ~ADC_INT_IEA_enable_w)


/**
 *******************************************************************************
 * @brief       Clear the ADC interrupt pending bits.
 * @param[in]   "__HANDLE__": specifies the ADC Handle.
 * @param[in]   "__FLAG__" : specifies the ADC interrupt flag to clear.
 *  @arg\b	    ADC_FLAG_ESMP : Sampling end flag.     
 *  @arg\b	    ADC_FLAG_E1CNV : One-time conversion end flag.      
 *  @arg\b	    ADC_FLAG_ESCNV : Channel scan conversion end flag.    
 *  @arg\b	    ADC_FLAG_OVR : Conversion overrun event flag.        
 *  @arg\b	    ADC_FLAG_WDL : Voltage window detect outside low event flag.        
 *  @arg\b	    ADC_FLAG_WDI : Voltage window detect inside event flag.        
 *  @arg\b	    ADC_FLAG_WDH : Voltage window detect outside high event flag.        
 *  @arg\b	    ADC_FLAG_SUM_UNDER : Sum-0,1,2 accumulation underflow flag.
 *  @arg\b	    ADC_FLAG_SUM_OVER : Sum-0,1,2 accumulation overflow flag.
 *  @arg\b	    ADC_FLAG_SUM_COMPLETE : Sum-0,1,2 accumulation complete flag.
 *  @arg\b	    ADC_FLAG_SUM_OVR : Sum-0,1,2 overrun event flag.    
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_ADC_CLEAR_FLAG(&ADC_Handle, ADC_FLAG_E1CNV);
 * @endcode
 *******************************************************************************
 */
#define __DRV_ADC_CLEAR_FLAG(__HANDLE__,__FLAG__)     ((__HANDLE__)->Instance->STA.W = (__FLAG__))

/**
 *******************************************************************************
 * @brief       Get the ADC interrupt pending bits.
 * @param[in]   "__HANDLE__": specifies the ADC Handle.
 * @param[in]   "__FLAG__" : specifies the ADC interrupt flag to clear.
 *  @arg\b	    ADC_FLAG_ESMP : Sampling end flag.     
 *  @arg\b	    ADC_FLAG_E1CNV : One-time conversion end flag.      
 *  @arg\b	    ADC_FLAG_ESCNV : Channel scan conversion end flag.    
 *  @arg\b	    ADC_FLAG_OVR : Conversion overrun event flag.        
 *  @arg\b	    ADC_FLAG_WDL : Voltage window detect outside low event flag.        
 *  @arg\b	    ADC_FLAG_WDI : Voltage window detect inside event flag.        
 *  @arg\b	    ADC_FLAG_WDH : Voltage window detect outside high event flag.        
 *  @arg\b	    ADC_FLAG_SUM_UNDER : Sum-0,1,2 accumulation underflow flag.
 *  @arg\b	    ADC_FLAG_SUM_OVER : Sum-0,1,2 accumulation overflow flag.
 *  @arg\b	    ADC_FLAG_SUM_COMPLETE : Sum-0,1,2 accumulation complete flag.
 *  @arg\b	    ADC_FLAG_SUM_OVR : Sum-0,1,2 overrun event flag.    
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_ADC_GET_FLAG(&ADC_Handle, ADC_FLAG_WDI);
 * @endcode
 *******************************************************************************
 */
#define __DRV_ADC_GET_FLAG(__HANDLE__,__FLAG__)      (((__HANDLE__)->Instance->STA.W & (__FLAG__)) == (__FLAG__))

/**
 *******************************************************************************
 * @brief       Get the ADC any interrupt pending bits.
 * @param[in]   "__HANDLE__": specifies the ADC Handle.
 * @param[in]   "__FLAG__" : specifies the ADC interrupt flag to clear.
 *  @arg\b	    ADC_CONVERSION_EVENT : ADC conversioned event (E1CNV/ESCNV).     
 *  @arg\b	    ADC_AWD_EVENT : AWD event (WDH/WDI/WDL).     
 *  @arg\b	    ADC_SUM_EVENT : SUM event (Overrun/Complete/Overflow).      
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_ADC_GET_EVENT(&ADC_Handle, ADC_FLAG_WDI);
 * @endcode
 *******************************************************************************
 */
#define __DRV_ADC_GET_EVENT(__HANDLE__,__FLAG__)      (((__HANDLE__)->Instance->STA.W & (__FLAG__)) != (0U))

/**
 *******************************************************************************
 * @brief       Clear ADC error code.
 * @param[in]   "__HANDLE__": specifies the ADC Handle.
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_ADC_CLEAR_ERRORCODE(&ADC_Handle);
 * @endcode
 *******************************************************************************
 */
#define __DRV_ADC_CLEAR_ERRORCODE(__HANDLE__)         ((__HANDLE__)->ErrorCode = (MID_ADC_ERROR_NONE))


/**
 *******************************************************************************
 * @brief       Enables the specified DMA request.
 * @param[in]   "__HANDLE__": specifies the mADC Handle.
 * @return		None
 *******************************************************************************
 */
#define __DRV_ADC_ENABLE_DMA(__HANDLE__)      ((__HANDLE__)->Instance->CR0.W |= (ADC_CR0_DMA_EN_enable_w))

/**
 *******************************************************************************
 * @brief       Disables the specified DMA request.
 * @param[in]   "__HANDLE__": specifies the mADC Handle.
 * @return		None
 *******************************************************************************
 */
#define __DRV_ADC_DISABLE_DMA(__HANDLE__)     ((__HANDLE__)->Instance->CR0.W &= ~(ADC_CR0_DMA_EN_enable_w))


#if defined(MG32_2ND) || defined(MG32_3RD)
/**
 *******************************************************************************
 * @brief       Select ADC 16bit data size (only conversion data) to DMA channel.
 * @param[in]   "__HANDLE__": specifies the mADC Handle.
 * @return		None
 *******************************************************************************
 */
#define __DRV_ADC_DMA16BIT(__HANDLE__)      ((__HANDLE__)->Instance->CR0.W |= (ADC_CR0_DMA_DSIZE_16bit_w))

/**
 *******************************************************************************
 * @brief       Select ADC 32bit data size (include Ch, flag, conversion data) to DMA channel.
 * @param[in]   "__HANDLE__": specifies the mADC Handle.
 * @return		None
 *******************************************************************************
 */
#define __DRV_ADC_DMA32BIT(__HANDLE__)     ((__HANDLE__)->Instance->CR0.W &= ~(ADC_CR0_DMA_DSIZE_16bit_w))
#endif


/**
 *******************************************************************************
 * @brief       Configure the channel number into channel selection register
 * @param[in]   "__HANDLE__": specifies the ADC Handle.
 * @param[in]   "__CHANEL__": ADC Channel.
 *  @arg\b	    ADC_CHANNEL_0 : External channel select 0
 *  @arg\b	    ADC_CHANNEL_1 : External channel select 1
 *  @arg\b	    ADC_CHANNEL_2 : External channel select 2
 *  @arg\b	    ADC_CHANNEL_3 : External channel select 3
 *  @arg\b	    ADC_CHANNEL_4 : External channel select 4       
 *  @arg\b	    ADC_CHANNEL_5 : External channel select 5  
 *  @arg\b	    ADC_CHANNEL_6 : External channel select 6        
 *  @arg\b	    ADC_CHANNEL_7 : External channel select 7
 *  @arg\b	    ADC_CHANNEL_8 : External channel select 8
 *  @arg\b	    ADC_CHANNEL_9 : External channel select 9
 *  @arg\b	    ADC_CHANNEL_10 :External channel select 10
 *  @arg\b	    ADC_CHANNEL_11 :External channel select 11
 *  @arg\b	    ADC_CHANNEL_12 :External channel select 12
 *  @arg\b	    ADC_CHANNEL_13 :External channel select 13
 *  @arg\b	    ADC_CHANNEL_14 :External channel select 14
 *  @arg\b	    ADC_CHANNEL_15 :External channel select 15
 *  @arg\b	    ADC_CHANNEL_16 :Internal channel select 16 (VSSA)
 *  @arg\b	    ADC_CHANNEL_17 :Internal channel select 17 (IVREF)
 *  @arg\b	    ADC_CHANNEL_18 :Internal channel select 18 (DAC_P0)
 *  @arg\b	    ADC_CHANNEL_19 :Internal channel select 18 (VBUF 1.4V)
 * @return		None
 *******************************************************************************
 */
#define __DRV_ADC_CHSELR_CHANNEL(__HANDLE__,__CHANEL__)                                          \
            ((__HANDLE__)->Instance->START.W &= ~(ADC_START_CH_SEL_mask_w | ADC_START_CH_MUX_mask_w));  \
            ((__HANDLE__)->Instance->START.W |= (__CHANEL__))

/**
 *******************************************************************************
 * @brief       Configure the channel number into channel selection register
 * @param[in]   "__HANDLE__": specifies the ADC Handle.
 * @param[in]   "__SCANCHANNEL__": ADC Channel.
 *  @arg\b	    ADC_ScanCHANNEL_0 : Scan/Loop channel select 0
 *  @arg\b	    ADC_ScanCHANNEL_1 : Scan/Loop channel select 1
 *  @arg\b	    ADC_ScanCHANNEL_2 : Scan/Loop channel select 2
 *  @arg\b	    ADC_ScanCHANNEL_3 : Scan/Loop channel select 3
 *  @arg\b	    ADC_ScanCHANNEL_4 : Scan/Loop channel select 4       
 *  @arg\b	    ADC_ScanCHANNEL_5 : Scan/Loop channel select 5  
 *  @arg\b	    ADC_ScanCHANNEL_6 : Scan/Loop channel select 6        
 *  @arg\b	    ADC_ScanCHANNEL_7 : Scan/Loop channel select 7
 *  @arg\b	    ADC_ScanCHANNEL_8 : Scan/Loop channel select 8
 *  @arg\b	    ADC_ScanCHANNEL_9 : Scan/Loop channel select 9
 *  @arg\b	    ADC_ScanCHANNEL_10 : Scan/Loop channel select 10
 *  @arg\b	    ADC_ScanCHANNEL_11 : Scan/Loop channel select 11
 *  @arg\b	    ADC_ScanCHANNEL_12 : Scan/Loop channel select 12
 *  @arg\b	    ADC_ScanCHANNEL_13 : Scan/Loop channel select 13
 *  @arg\b	    ADC_ScanCHANNEL_14 : Scan/Loop channel select 14
 *  @arg\b	    ADC_ScanCHANNEL_15 : Scan/Loop channel select 15
 * @return		None
 * @note        Depend External/Internal channel select
 *******************************************************************************
 */
#define __DRV_ADC_RQGULAR_CHANNEL(__HANDLE__,__SCANCHANNEL__)                                          \
            ((__HANDLE__)->Instance->MSK.H[0] = (uint16_t)(__SCANCHANNEL__))


/**
 *******************************************************************************
 * @brief       Enable the PGA peripheral
 * @param[in]   "__HANDLE__" : pointer to a ADC_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
#define __DRV_ADC_PGA_ENABLE(__HANDLE__)                                        \
  ((__HANDLE__)->Instance->ANA.W |= ADC_ANA_PGA_EN_enable_w)


/**
 *******************************************************************************
 * @brief       Disable the PGA peripheral
 * @param[in]   "__HANDLE__" : pointer to a ADC_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
#define __DRV_ADC_PGA_DISABLE(__HANDLE__)                                       \
  ((__HANDLE__)->Instance->ANA.W &= ~ADC_ANA_PGA_EN_enable_w)


/**
 *******************************************************************************
 * @brief       Update the PGA offset setting
 * @param[in]   "__HANDLE__" : pointer to a ADC_HandleTypeDef
 * @param[in]   "__OFFT__" : PGA offset setting (0~63).
 * @return		None
 *******************************************************************************
 */
#define __DRV_ADC_PGA_UPDATE_OFFT(__HANDLE__,__OFFT__)                          \
  ((__HANDLE__)->Instance->GAIN.W &= ~ADC_GAIN_OFFT_PGA_mask_w);                \
  ((__HANDLE__)->Instance->GAIN.H[1] |= (__OFFT__))


/**
 *******************************************************************************
 * @brief       Update the PGA gain setting
 * @param[in]   "__HANDLE__" : pointer to a ADC_HandleTypeDef
 * @param[in]   "__GAIN__" : PGA gain setting (0~63).
 *              Gain is equal : (1+(ADC0_GAIN_PGA*3)/(63+(63-ADC0_GAIN_PGA)*3))
 * @return		None
 *******************************************************************************
 */
#define __DRV_ADC_PGA_UPDATE_GAIN(__HANDLE__,__GAIN__)                          \
  ((__HANDLE__)->Instance->GAIN.H[0] = (uint16_t) (__GAIN__))


#if defined(MG32_3RD) || defined(MG32_4TH)
/**
 *******************************************************************************
 * @brief       Config ADC conversion time.
 * @param[in]   "__HANDLE__" : pointer to a ADC_HandleTypeDef
 * @param[in]   "__CONVTIME__" : PGA gain setting (0~63).
 *  @arg\b	    ADC_FAST_CONVERSION : Conversion time ~24 ADC clocks
 *  @arg\b	    ADC_NORMAL_CONVERSION : Conversion time ~30 ADC clocks
 * @return		None
 *******************************************************************************
 */
#define __DRV_ADC_SET_CONVERSTION_TIME(__HANDLE__,__CONVTIME__)                 \
  ((__HANDLE__)->Instance->ANA.W &= ~ADC_ANA_CONV_TIME_mask_w);                 \
  ((__HANDLE__)->Instance->ANA.W |= (__CONVTIME__))


/**
 *******************************************************************************
 * @brief       Config ADC sampling clock phase item select.
 * @param[in]   "__HANDLE__" : pointer to a ADC_HandleTypeDef
 * @param[in]   "__CKPHS__" : PGA gain setting (0~63).
 *  @arg\b	    ADC_CLOCK_PHASE0 : Bypass.                          
 *  @arg\b	    ADC_CLOCK_PHASE1 : One step delay.                  
 *  @arg\b	    ADC_CLOCK_PHASE2 : Clock invert.                    
 *  @arg\b	    ADC_CLOCK_PHASE3 : Clock invert with one step delay.
 * @return		None
 *******************************************************************************
 */
#define __DRV_ADC_SET_CLOCK_PHASE(__HANDLE__,__CKPHS__)                         \
  ((__HANDLE__)->Instance->CLK.W &= ~ADC_CLK_CK_DLY_mask_w);                    \
  ((__HANDLE__)->Instance->CLK.W |= (__CKPHS__))
#endif


#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
/**
 *******************************************************************************
 * @brief       Config ADC conversion time.
 * @param[in]   "__HANDLE__" : pointer to a ADC_HandleTypeDef
 * @param[in]   "__OPBIAS__" : PGA gain setting (0~63).
 *  @arg\b	    ADC_OP_BIAS_LVL0 : LVL0 : Lowest current.      
 *  @arg\b	    ADC_OP_BIAS_LVL1 : LVL1 : Lower current.    
 *  @arg\b	    ADC_OP_BIAS_LVL2 : LVL2 : Higher current.   
 *  @arg\b	    ADC_OP_BIAS_LVL3 : LVL3 : Highest current.  
 * @return		None
 *******************************************************************************
 */
#define __DRV_ADC_SET_OPERATION_CURRENT(__HANDLE__,__OPBIAS__)                  \
  ((__HANDLE__)->Instance->ANA.W &= ~ADC_ANA_BIAS_mask_w);                      \
  ((__HANDLE__)->Instance->ANA.W |= (__OPBIAS__))
#endif


#if defined(MG32_4TH)
/**
 *******************************************************************************
 * @brief       Enable discharge before ADC sample and hold. 
 * @param[in]   "__HANDLE__" : pointer to a ADC_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
#define __DRV_ADC_DISCHARGE_ENABLE(__HANDLE__)                                  \
  ((__HANDLE__)->Instance->ANA.W |= (ADC_ANA_DISCHR_EN_enable_w))


/**
 *******************************************************************************
 * @brief       Disable discharge before ADC sample and hold. 
 * @param[in]   "__HANDLE__" : pointer to a ADC_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
#define __DRV_ADC_DISCHARGE_DISABLE(__HANDLE__)                                 \
  ((__HANDLE__)->Instance->ANA.W &= ~(ADC_ANA_DISCHR_EN_enable_w))

#endif


/**
 * @name    Function announce
 * @brief   ADC base initial/Deinitial	
 */ 
///@{
MID_StatusTypeDef MID_ADC_Init(ADC_HandleTypeDef* mADC);
MID_StatusTypeDef MID_ADC_DeInit(ADC_HandleTypeDef *mADC);
void MID_ADC_MspInit(ADC_HandleTypeDef* mADC);
void MID_ADC_MspDeInit(ADC_HandleTypeDef* mADC);

/* Blocking mode: Polling */
MID_StatusTypeDef MID_ADC_Start(ADC_HandleTypeDef* mADC);
MID_StatusTypeDef MID_ADC_Stop(ADC_HandleTypeDef* mADC);
MID_StatusTypeDef MID_ADC_PollForConversion(ADC_HandleTypeDef* mADC, uint32_t Timeout);
MID_StatusTypeDef MID_ADC_PollForEvent(ADC_HandleTypeDef* mADC, uint32_t EventType, uint32_t Timeout);

/* Non-blocking mode: Interruption */
MID_StatusTypeDef MID_ADC_Start_IT(ADC_HandleTypeDef* mADC);
MID_StatusTypeDef MID_ADC_Stop_IT(ADC_HandleTypeDef* mADC);

/* Non-blocking mode: DMA */
MID_StatusTypeDef MID_ADC_Start_DMA(ADC_HandleTypeDef* mADC, uint32_t* pData, uint32_t Length);
MID_StatusTypeDef MID_ADC_Stop_DMA(ADC_HandleTypeDef* mADC);
///@}


/**
 * @name    Function announce
 * @brief   addtogroup ADC_Exported_Functions_Group
 */ 
///@{
uint32_t MID_ADC_GetValue(ADC_HandleTypeDef* mADC);
uint32_t MID_ADC_GetSUM0Value(ADC_HandleTypeDef* mADC);
uint32_t MID_ADC_GetSUM1Value(ADC_HandleTypeDef* mADC);
uint32_t MID_ADC_GetSUM2Value(ADC_HandleTypeDef* mADC);
void MID_ADC_IRQHandler(ADC_HandleTypeDef* mADC);
void MID_ADC_ConvCpltCallback(ADC_HandleTypeDef* mADC);
void MID_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* mADC);
void MID_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* mADC);
void MID_ADC_ErrorCallback(ADC_HandleTypeDef *mADC);
void MID_ADC_SumCallback(ADC_HandleTypeDef *mADC);
MID_StatusTypeDef MID_ADC_ConfigChannel(ADC_HandleTypeDef* mADC, ADC_ChannelConfTypeDef *ChannelMux);
MID_StatusTypeDef MID_ADC_AnalogWDGConfig(ADC_HandleTypeDef* mADC, ADC_AnalogWDGConfTypeDef* AnalogWDGConfig);
MID_StatusTypeDef MID_ADC_AccumulateConfig(ADC_HandleTypeDef* mADC, ADC_AccumulateConfDef* AccumulateConfig);
uint32_t MID_ADC_GetState(ADC_HandleTypeDef* mADC);
uint32_t MID_ADC_GetError(ADC_HandleTypeDef *mADC);
MID_StatusTypeDef MID_ADC_PGACalibration_Start(ADC_HandleTypeDef* mADC);
MID_StatusTypeDef MID_ADC_VRMCalibration_Start(ADC_HandleTypeDef* mADC, uint8_t VRMV);
MID_StatusTypeDef MID_ADC_Calibration_Start(ADC_HandleTypeDef* mADC);
///@}




#endif
