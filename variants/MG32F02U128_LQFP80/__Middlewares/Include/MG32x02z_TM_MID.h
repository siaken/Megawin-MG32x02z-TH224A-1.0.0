/**
 ******************************************************************************
 *
 * @file        MG32x02z_TM_MID.h
 *
 * @brief       This file provides firmware functions to manage the following
 *              functionalities of the TM peripheral:
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.06
 * @date        2021/01/27
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2016 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 *
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

#ifndef _MG32x02z_TM_MID_H

/*!< _MG32x02z_TM_DRV_H */
#define _MG32x02z_TM_MID_H

#include "MG32x02z.h"
#include "MG32x02z_Common_MID.h"
#include "MG32x02z_TM.h"
#include "MG32x02z_DMA_MID.h"



/**
 * @name	TM_Interrupt_definition
 *   		TM Interrupt Definition
 */ 
//!@{
#define TM_IT_CC0                   TM_INT_CC0_IE_enable_w      /*!< TM CC0 interrupt.                              */
#define TM_IT_CC1                   TM_INT_CC1_IE_enable_w      /*!< TM CC1 interrupt.                              */
#define TM_IT_CC2                   TM_INT_CC2_IE_enable_w      /*!< TM CC2 interrupt.                              */
#define TM_IT_CC3                   TM_INT_CC3_IE_enable_w      /*!< TM CC3 interrupt.                              */
#define TM_IT_UPDATE                TM_INT_TIE_enable_w         /*!< TM main counter interrupt.                     */
#define TM_IT_UPDATE2               TM_INT_TIE2_enable_w        /*!< TM prescaler interrupt.                        */
#define TM_IT_BREAK                 TM_INT_BKIE_enable_w        /*!< TM break event interrupt.                      */
#define TM_IT_EXTERNAL              TM_INT_EXIE_enable_w        /*!< TM external trigger interrupt.                 */
#define TM_IT_QEI_DIRCHANGE         TM_INT_DIRC_IE_enable_w     /*!< TM QEI change direction interrupt.             */
#define TM_IT_QEI_INDEX             TM_INT_IDX_IE_enable_w      /*!< TM QEI reset index interrupt.                  */
#define TM_IT_QEI_ERROR             TM_INT_QPE_IE_enable_w      /*!< TM QEI error interrupt.                        */
#if defined(MG32_3RD)
#define TM_IT_ONEPULSE              TM_INT_RTU_IE_enable_w      /*!< Repetition timer underflow interrupt enable.   */
#endif
//!@}

/**
 * @name	TM_Flag_definition
 *   		TM Flag Definition
 */ 
//!@{
#define TM_FLAG_CC0A                TM_STA_CF0A_happened_w      /*!< TM CC0A flag.                                  */
#define TM_FLAG_CC1A                TM_STA_CF1A_happened_w      /*!< TM CC1A flag.                                  */
#define TM_FLAG_CC2A                TM_STA_CF2A_happened_w      /*!< TM CC2A flag.                                  */
#define TM_FLAG_CC3A                TM_STA_CF3A_happened_w      /*!< TM CC3A flag.                                  */
#define TM_FLAG_CC0B                TM_STA_CF0B_happened_w      /*!< TM CC0B flag.                                  */
#define TM_FLAG_CC1B                TM_STA_CF1B_happened_w      /*!< TM CC1B flag.                                  */
#define TM_FLAG_CC2B                TM_STA_CF2B_happened_w      /*!< TM CC2B flag.                                  */
#define TM_FLAG_CC3B                TM_STA_CF3B_happened_w      /*!< TM CC3B flag.                                  */
#define TM_FLAG_UPDATE_UP           TM_STA_TOF_happened_w       /*!< TM main counter overflow flag.                 */
#define TM_FLAG_UPDATE_DOWN         TM_STA_TUF_happened_w       /*!< TM main counter undefflow flag.                */
#define TM_FLAG_UPDATE2_UP          TM_STA_TOF2_happened_w      /*!< TM prescaler counter overflow flag.            */
#define TM_FLAG_UPDATE2_DOWN        TM_STA_TUF2_happened_w      /*!< TM prescaler counter undefflow flag.           */
#define TM_FLAG_BREAK               TM_STA_BKF_happened_w       /*!< TM break event flag.                           */
#define TM_FLAG_EXTERNAL            TM_STA_EXF_happened_w       /*!< TM external trigger event flag.                */
#define TM_FLAG_QEI_DIRCHANGE       TM_STA_DIRCF_happened_w     /*!< TM QEI change direction flag.                  */
#define TM_FLAG_QEI_INDEX           TM_STA_IDXF_happened_w      /*!< TM QEI reset index flag.                       */
#define TM_FLAG_QEI_ERROR           TM_STA_QPEF_happened_w      /*!< TM QEI error flag.                             */
#define TM_FLAG_DIRECTION           TM_STA_DIRF_down_counting_w /*!< TM QEI count down flag.                        */
#if defined(MG32_3RD)      
#define TM_FLAG_ONEPULSE            TM_STA_RTUF_happened_w      /*!< TM Repetition timer underflow flag.            */
#endif
//!@}

/**
 * @name	TM_Event_Groupdef
 *   		TM Event Group Definition
 */ 
//!@{
#define TM_EVENT_UPDATE             (TM_FLAG_UPDATE_UP | TM_FLAG_UPDATE_DOWN)       /*!< TM main counter event (overflow or underflow).     */
#define TM_EVENT_UPDATE2            (TM_FLAG_UPDATE2_UP | TM_FLAG_UPDATE2_DOWN)     /*!< TM prescaler counter event (overflow or underflow).*/
#define TM_EVENT_CH0                (TM_FLAG_CC0A | TM_FLAG_CC0B)                   /*!< TM channel0 IC/OC event.                           */
#define TM_EVENT_CH1                (TM_FLAG_CC1A | TM_FLAG_CC1B)                   /*!< TM channel1 IC/OC event.                           */
#define TM_EVENT_CH2                (TM_FLAG_CC2A | TM_FLAG_CC2B)                   /*!< TM channel2 IC/OC event.                           */
#define TM_EVENT_CH3                (TM_FLAG_CC3A | TM_FLAG_CC3B)                   /*!< TM channel3 IC/OC event.                           */
#define TM_EVENT_QEI                (TM_FLAG_QEI_DIRCHANGE | TM_FLAG_QEI_INDEX | TM_FLAG_QEI_ERROR) /*!< TM QEI event (DIRC/IDX/QPE).       */
#define TM_EVENT_ONEPULSE           (TM_FLAG_ONEPULSE)                              /*!< TM Repetition timer underflow event.               */
//!@}


/** 
 * @enum        MID_TM_ChannelSelectDef
 * @brief       declare Timer channel selection
 */        
typedef enum __attribute__((packed)) 
{
    MID_TM_Channel0=0,                                          /*!< Specifies the TM Channel0.                     */
    MID_TM_Channel1=1,                                          /*!< Specifies the TM Channel1.                     */
    MID_TM_Channel2=2,                                          /*!< Specifies the TM Channel2.                     */
    MID_TM_Channel3=3,                                          /*!< Specifies the TM Channel3.                     */
    MID_TM_Channel_ALL,                                         /*!< Specifies the TM channels.                     */
    MID_TM_ACTIVE_CHANNEL_CLEARED                               /*!< All active channels cleared.                   */
} MID_TM_ChannelSelectDef;

/**
 * @enum        MID_TM_StateTypeDef
 * @brief       MID State structures definition
 */
typedef enum __attribute__((packed))  
{
    MID_TM_STATE_BUSY,                                          /*!< An internal process is running.                */
    MID_TM_STATE_READY,                                         /*!< Peripheral Initialized and ready for use.      */
    MID_TM_STATE_RESET                                          /*!< DMA not yet initialized or disabled.           */
} MID_TM_StateTypeDef;

/**
 * @name	TM_CounterMode
 *   		TM Counter Mode
 */ 
//!@{
#define TM_CASCADE_UP               (0x0000U)                   /*!< TM main+prescaler all up count in cascade mode.        */
#define TM_SEPARATE_UP              (0x0010U)                   /*!< TM main+prescaler all up count in separate mode.       */
#define TM_FULLCOUNTER_UP           (0x0020U)                   /*!< TM main+prescaler all up count in full counter mode.   */
#define TM_CASCADE_DOWN             (0x0000U)                   /*!< TM main+prescaler all down count in cascade mode.      */
#define TM_SEPARATE_DOWN            (0x00D0U)                   /*!< TM main+prescaler all down count in separate mode.     */
#define TM_FULLCOUNTER_DOWN         (0x00E0U)                   /*!< TM main+prescaler all down count in full counter mode. */
//!@}

/**
 * @name	TM_ClockSource
 *   		TM Clock Source 
 */ 
//!@{
#define TM_MainCounter_InteralClock (TM_CLK_CKS_SEL_ck_int_w)    /*!< TM main counter clock from internal clock.            */
#define TM_MainCounter_ExteralClock (TM_CLK_CKS_SEL_ck_ext_w)    /*!< TM main counter clock from external clock.            */
#define TM_Prescaler_InteralClock   (TM_CLK_CKS2_SEL_ck_int_w)   /*!< TM prescaler counter clock from internal clock.       */
#define TM_Prescaler_ExteralClock   (TM_CLK_CKS2_SEL_ck_ext_w)   /*!< TM prescaler counter clock from external clock.       */
    
#define TM_INTERNAL_CLOCK           (TM_MainCounter_InteralClock | TM_Prescaler_InteralClock)   /*!< TM main+prescaler clock from internal clock. */  
#define TM_EXTERNAL_CLOCK           (TM_MainCounter_ExteralClock | TM_Prescaler_ExteralClock)   /*!< TM main+prescaler clock from external clock. */  
//!@}

/**
 * @name	TM_InterClockSource
 *   		TM internal clock Source 
 */ 
//!@{
#define TM_INTERNALCLOCK_PROC       (TM_CLK_CKI_SEL_proc_w)     /*!< TM internal clock from CK_PROC.                        */
#define TM_INTERNALCLOCK_ILRCO      (TM_CLK_CKI_SEL_ck_ls_w)    /*!< TM internal clock from CK_LS.                          */
//!@}

/**
 * @name	TM_ExterClockSource
 *   		TM internal clock Source 
 */ 
//!@{
#define TM_EXTERNAL_ETR             (TM_CLK_CKE_SEL_etr_w)                          /*!< TM external clock from ETR pin.                        */
#define TM_EXTERNAL_IN0             (TM_CLK_CKE_SEL_in0_w)                          /*!< TM external clock from IN0.                            */
#define TM_EXTERNAL_IN1             (TM_CLK_CKE_SEL_in1_w)                          /*!< TM external clock from IN1.                            */
#define TM_EXTERNAL_ITR0            (TM_CLK_CKE_SEL_itr_w | TM_TRG_ITR_MUX_itr0_w)  /*!< TM external clock from ITR0 (reference funcion table). */
#define TM_EXTERNAL_ITR1            (TM_CLK_CKE_SEL_itr_w | TM_TRG_ITR_MUX_itr1_w)  /*!< TM external clock from ITR1 (reference funcion table). */
#define TM_EXTERNAL_ITR2            (TM_CLK_CKE_SEL_itr_w | TM_TRG_ITR_MUX_itr2_w)  /*!< TM external clock from ITR2 (reference funcion table). */
#define TM_EXTERNAL_ITR3            (TM_CLK_CKE_SEL_itr_w | TM_TRG_ITR_MUX_itr3_w)  /*!< TM external clock from ITR3 (reference funcion table). */
#define TM_EXTERNAL_ITR4            (TM_CLK_CKE_SEL_itr_w | TM_TRG_ITR_MUX_itr4_w)  /*!< TM external clock from ITR4 (reference funcion table). */
#define TM_EXTERNAL_ITR5            (TM_CLK_CKE_SEL_itr_w | TM_TRG_ITR_MUX_itr5_w)  /*!< TM external clock from ITR5 (reference funcion table). */
#define TM_EXTERNAL_ITR6            (TM_CLK_CKE_SEL_itr_w | TM_TRG_ITR_MUX_itr6_w)  /*!< TM external clock from ITR6 (reference funcion table). */
#define TM_EXTERNAL_ITR7            (TM_CLK_CKE_SEL_itr_w | TM_TRG_ITR_MUX_itr7_w)  /*!< TM external clock from ITR7 (reference funcion table). */
//!@}

/**
 * @name	TM_ClockDivision
 *   		TM Clock Division
 */ 
//!@{
#define TM_INTERNALCLOCK_DIVDER_DIV1    (0x0000U)               /*!< TM internal clock divide 1.                            */
#define TM_INTERNALCLOCK_DIVDER_DIV2    (0x1000U)               /*!< TM internal clock divide 2.                            */
#define TM_INTERNALCLOCK_DIVDER_DIV4    (0x2000U)               /*!< TM internal clock divide 4.                            */
#define TM_INTERNALCLOCK_DIVDER_DIV8    (0x3000U)               /*!< TM internal clock divide 8.                            */
//!@}       
        
/**     
 * @name	TM_Channel_Mode     
 *   		TM Channel Mode Select      
 */        
//!@{       
#define TM_CH_Disable               (0x0000U)                   /*!< Disable channel function.                              */
#define TM_CH_InputCapture          (0x0001U)                   /*!< TM channel function set in input capture mode.         */
#define TM_CH_16bit_OutputCompare   (0x0002U)                   /*!< TM channel function set in 16bit output compare mode.  */
#define TM_CH_8bitx2_OutputCompare  (0x0003U)                   /*!< TM channel function set in 8bitx2 output compare mode. */
#define TM_CH_16bit_PWM             (0x0004U)                   /*!< TM channel function set in 16bit PWM mode.             */
#define TM_CH_8bitx2_PWM            (0x0005U)                   /*!< TM channel function set in 8bitx2 PWM mode.            */
#define TM_CH_16bit_PWM_COMPLEMENT  (0x0006U)                   /*!< TM channel function set in 16bit PWM mode with deadtime control. */
#define TM_CH_8bitx2_PWM_COMPLEMENT (0x0007U)                   /*!< TM channel function set in 8bitx2 PWM mode with deadtime control. */
#define TM_ALLCH_PWMMode            (0x4444U)                   /*!< TM all channel function set in 16bit PWM mode.         */
//!@}


/** 
 * @struct  TM_Base_InitTypeDef
 * @brief   TM Time Base Init structure definition
 */ 
typedef struct __attribute__((packed))
{
    uint32_t TM_CounterMode;        /*!< Specifies the counter mode.
                                         This parameter can be a value of Cascade/Separate/Full_Counter with Up/Down count */
        
    uint16_t TM_Prescaler;          /*!< Specifies the prescaler value used to divide the TM clock.
                                         This parameter can be a number between 0x0000 and 0xFFFF
                                         PS: TM00 & TM01 only 8 bits (0x00~0xFF) */
        
    uint16_t TM_Period;             /*!< Specifies the period value to be loaded into the active Auto-Reload
                                         Register at the next update event.This parameter must be a number
                                         between 0x0000 and 0xFFFF.
                                         PS: TM00 & TM01 only 8 bits (0x00~0xFF) */
    
} TM_Base_InitTypeDef;

/** 
 * @struct  TM_ClockConfigTypeDef
 * @brief   TM Clock Configuration Handle Structure definition
 */ 
typedef struct __attribute__((packed))
{
    uint32_t TM_ClockSource;            /*!< Specifies the main/prescaler clock source from Internal/External clock.
                                             This parameter can be a value of reference TM_ClockSource */
    
    uint32_t TM_InternalClockSource;    /*!< Specifies the internal clock source.
                                             This parameter can be a value of reference TM_InterClockSource */
    
    uint32_t TM_INTClockDivision;       /*!< Specifies the clock division.
                                             This parameter can be a value of reference TM_ClockDivision */
    
    uint32_t TM_ExternalClockSource;    /*!< Specifies the external clock source.
                                             This parameter can be a value of reference TM_ExterClockSource */    
} TM_ClockConfigTypeDef;


/** 
 * @struct  TM_HandleTypeDef
 * @brief   TM's timebase/procedure control
 */ 
typedef struct __attribute__((packed))
{
    TM_Struct*              Instance;   /*!< Register base address. e.g TM00, TM01 ... TM36 */
        
    TM_Base_InitTypeDef     Init;       /*!< TM Time Base required parameters */
        
    MID_TM_ChannelSelectDef Channel;    /*!< Active channel  */
        
    DMA_HandleTypeDef       *hDMA[4];   /*!< DMA Handlers array
                                             This array is accessed by a reference TM_DMA_Handle_index */
         
    MID_LockTypeDef         Lock;       /*!< Locking object */
        
    MID_TM_StateTypeDef     State;      /*!< TM operation state  */

} TM_HandleTypeDef;



/**
 * @name	TM_Output_Compare_Polarity
 *   		TM Output Compare Polarity
 */ 
//!@{
#define TM_OCPOLARITY_HIGH          (0x0000U)                   /*!< Normal output OCx.                             */
#define TM_OCPOLARITY_LOW           (0x0001U)                   /*!< Invert TM OCx output.                          */
//!@}

/**
 * @name	TM_Output_Compare_N_Polarity
 *   		TM Complementary Output Compare Polarity
 */ 
//!@{
#define TM_OCNPOLARITY_HIGH         (0x0000U)                   /*!< Normal output OCxN.                            */
#define TM_OCNPOLARITY_LOW          (0x0100U)                   /*!< Invert TM OCxN output.                         */
//!@}   
    
/** 
 * @name	TM_Output_Compare_H_Polarity    
 *   		TM Complementary Output Compare Polarity    
 */     
//!@{   
#define TM_OCHPOLARITY_HIGH         (0x0000U)                   /*!< Normal output OCxH.                            */
#define TM_OCHPOLARITY_LOW          (0x0010U)                   /*!< Invert TM OCxH output.                         */
//!@}   
    
/** 
 * @name	TM_Output_Compare_Idle_State    
 *   		TM Output Compare Idle State    
 */     
//!@{   
#define TM_OCIDLESTATE_SET          (0x01000000U)               /*!< TM OCx output 'H' in idle mode.                */
#define TM_OCIDLESTATE_RESET        (0x00000000U)               /*!< TM OCx output 'L' in idle mode.                */
//!@}   
    
/** 
 * @name	TM_Output_Compare_N_Idle_State  
 *   		TM Complementary Output Compare Idle State  
 */     
//!@{   
#define TM_OCNIDLESTATE_SET         (0x10000000U)               /*!< TM OCxN output 'H' in idle mode.               */
#define TM_OCNIDLESTATE_RESET       (0x00000000U)               /*!< TM OCxN output 'L' in idle mode.               */
//!@}   
    
/** 
 * @name	TM_Output_Compare_H_Idle_State  
 *   		TM Output Compare H Idle State  
 */     
//!@{   
#define TM_OCHIDLESTATE_SET         (0x00000100U)               /*!< TM OCxH output 'H' in idle mode.               */     
#define TM_OCHIDLESTATE_RESET       (0x00000000U)               /*!< TM OCxH output 'L' in idle mode.               */  
//!@}   
    
/** 
 * @name	TM_DMA_Handle_index 
 *   		TM DMA Handle Index 
 */     
//!@{   
#define TM_DMA_ID_CC0               ((uint16_t) 0x0U)           /*!< Index of the DMA handle used for Compare 0 DMA requests. */
#define TM_DMA_ID_CC1               ((uint16_t) 0x1U)           /*!< Index of the DMA handle used for Compare 1 DMA requests. */
#define TM_DMA_ID_CC2               ((uint16_t) 0x2U)           /*!< Index of the DMA handle used for Compare 2 DMA requests. */
#define TM_DMA_ID_CC3               ((uint16_t) 0x3U)           /*!< Index of the DMA handle used for Capture 3 DMA requests. */
//!@}

/**
 * @name	TM_DMA_Channel_Enable
 *   		TM DMA channel enable
 */ 
//!@{
#if defined(MG32_1ST) || defined(MG32_2ND) || defined(MG32_3RD)
#define TM_DMA_CH0_OC               TM_CCMDS_DMA_CC0E_enable_w  /*!< Enable TM36 channel0 with DMA access (PWM/OC). */
#define TM_DMA_CH1_OC               TM_CCMDS_DMA_CC1E_enable_w  /*!< Enable TM36 channel1 with DMA access (PWM/OC). */
#define TM_DMA_CH2_OC               TM_CCMDS_DMA_CC2E_enable_w  /*!< Enable TM36 channel2 with DMA access (PWM/OC). */
#define TM_DMA_CH3_IC               TM_CCMDS_DMA_CC3E_enable_w  /*!< Enable TM36 channel3 with DMA access (IC).     */
#endif
#if defined(MG32_4TH)
#define TM_DMA_CH0_OC               TM_CCMDS_DMA_CC0E_enable_w  /*!< Enable TM36 channel0 with DMA access (PWM/OC). */
#define TM_DMA_CH1_OC               TM_CCMDS_DMA_CC1E_enable_w  /*!< Enable TM36 channel1 with DMA access (PWM/OC). */
#define TM_DMA_CH2_OC               TM_CCMDS_DMA_CC2E_enable_w  /*!< Enable TM36 channel2 with DMA access (PWM/OC). */
#define TM_DMA_CH2_IC               TM_CCMDS_DMA_IC2E_enable_w  /*!< Enable TM36 channel2 with DMA access (IC).     */
#define TM_DMA_CH3_IC               TM_CCMDS_DMA_IC3E_enable_w  /*!< Enable TM36 channel3 with DMA access (IC).     */
#endif
//!@}



/** 
 * @struct  TM_OC_InitTypeDef
 * @brief   TM Output Compare Configuration Structure definition
 */ 
typedef struct __attribute__((packed))
{
    uint32_t OCMode;                /*!< Specifies the TM mode.
                                         This parameter can be a value of reference TM_Channel_Mode */
                            
    uint16_t Pulse;                 /*!< Specifies the pulse value to be loaded into the Capture Compare Register.
                                         This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF */
                            
    uint32_t OCPolarity;            /*!< Specifies the output polarity.
                                         This parameter can be a value of reference TM_Output_Compare_Polarity */
                            
    uint32_t OCNPolarity;           /*!< Specifies the complementary output polarity.
                                         This parameter can be a value of reference TM_Output_Compare_N_Polarity */
                            
    uint32_t OCHPolarity;           /*!< Specifies the output polarity.
                                         This parameter can be a value of reference TM_Output_Compare_H_Polarity */
                            
    uint32_t OCIdleState;           /*!< Specifies the TM Output Compare pin state during Idle state.
                                         This parameter can be a value of reference TM_Output_Compare_Idle_State */
                            
    uint32_t OCNIdleState;          /*!< Specifies the TM Output Compare pin state during Idle state.
                                         This parameter can be a value of reference TM_Output_Compare_N_Idle_State */
                            
    uint32_t OCHIdleState;          /*!< Specifies the TM Output Compare pin state during Idle state.
                                         This parameter can be a value of reference TM_Output_Compare_H_Idle_State */
        
} TM_OC_InitTypeDef;


/**
 * @name	TM_Input_Capture_Polarity
 *   		TM Input Capture Polarity
 */ 
//!@{
#define TM_ICPOLARITY_DISABLE       TM_ICCR_IC0_TRGS_disable_w      /*!< Disable input capture.                     */
#define TM_ICPOLARITY_RISING        TM_ICCR_IC0_TRGS_rising_edge_w  /*!< TM accept rising edge event to capture.    */
#define TM_ICPOLARITY_FALLING       TM_ICCR_IC0_TRGS_falling_edge_w /*!< TM accept falling edge event to capture.   */
#define TM_ICPOLARITY_DUALEDGE      TM_ICCR_IC0_TRGS_dual_edge_w    /*!< TM accept dual edge event to capture.      */
//!@}

/**
 * @name	TM_Input_Capture_Selection
 *   		TM Input Capture Selection
 */ 
//!@{
#define MID_TM_INPUTMUX_PIN         TM_ICCR_IC0_MUX_ic00_w         /*!< TM channel input source from pin.                                       */
#define MID_TM_INPUTMUX_ITR         TM_ICCR_IC0_MUX_ic01_w         /*!< TM channel input source from ITR.                                       */
#define MID_TM_INPUTMUX_LINE2       TM_ICCR_IC0_MUX_ic02_w         /*!< TM channel input source from Line2 (please reference function table).   */
#define MID_TM_INPUTMUX_LINE3       TM_ICCR_IC0_MUX_ic03_w         /*!< TM channel input source from Line3 (please reference function table).   */
//!@}


/**
 * @name	TM_IC_DataMode
 *   		TM Input Capture Data Mode
 */ 
//!@{
#define MID_TM_IC_OVERWRITTEN       TM_CR1_OVR0_MDS_overwritten_w   /*!< Overwritten (Overwritten by new data).     */
#define MID_TM_IC_KEEPDATA          TM_CR1_OVR0_MDS_keep_w          /*!< Keep (Preserved old data).                 */
//!@}

/** 
 * @struct  TM_IC_InitTypeDef
 * @brief   TM Input Capture Configuration Structure definition
 */ 
typedef struct __attribute__((packed))
{
    uint32_t ICPolarity;            /*!< Specifies the active edge of the input signal.
                                         This parameter can be a value of reference TM_Input_Capture_Polarity */
                    
    uint32_t ICSelection;           /*!< Specifies the input.
                                         This parameter can be a value of reference TM_Input_Capture_Selection */

    uint32_t ICDataMode;            /*!< Specifies the input.
                                         This parameter can be a value of reference TM_IC_DataMode */

} TM_IC_InitTypeDef;


/**
 * @name	TM_Slave_Mode
 *   		TM Slave Mode
 */ 
//!@{
#define TM_SLAVEMODE_DISABLE                TM_TRG_TRGI_MDS_no_operation_w + TM_TRG_TRGI2_MDS_no_operation_w    /*!< No function when TM external trigger happened in slave mode.   */
#define TM_SLAVEMODE_TRIGGER_RISINGEDGE     TM_TRG_TRGI_MDS_trigger_r_w + TM_TRG_TRGI2_MDS_trigger_r_w          /*!< TM start count when rising edge event happened in slave mode.  */
#define TM_SLAVEMODE_RESET_RISINGEDGE       TM_TRG_TRGI_MDS_reset_r_w + TM_TRG_TRGI2_MDS_reset_r_w              /*!< TM reset count when rising edge event happened in slave mode.  */
#define TM_SLAVEMODE_GATED_HIGHLEVEL        TM_TRG_TRGI_MDS_gate_h_w + TM_TRG_TRGI2_MDS_gate_h_w                /*!< TM gating counter when high level state in slave mode.         */
#define TM_SLAVEMODE_RESET_DUALEDGE         TM_TRG_TRGI_MDS_reset_w + TM_TRG_TRGI2_MDS_reset_w                  /*!< TM reset counter when dual edge event happened in slave mode.  */
#define TM_SLAVEMODE_TRIGGER_FALLINGEDGE    TM_TRG_TRGI_MDS_trigger_f_w + TM_TRG_TRGI2_MDS_trigger_f_w          /*!< TM start count when falling edge event happened in slave mode. */
#define TM_SLAVEMODE_RESET_FALLINGEDGE      TM_TRG_TRGI_MDS_reset_f_w + TM_TRG_TRGI2_MDS_reset_f_w              /*!< TM start count when falling edge event happened in slave mode. */
#define TM_SLAVEMODE_GATED_LOWLEVEL         TM_TRG_TRGI_MDS_gate_l_w + TM_TRG_TRGI2_MDS_gate_l_w                /*!< TM gating count when low level state in slave mode.            */
//!@}

/**
 * @name	TM_Trigger_Selection
 *   		TM Trigger Selection
 */ 
//!@{
#define TM_TS_ETR                   TM_TRG_TRG_MUX_etr_w                            /*!< TM external trigger from ETR pin.                          */
#define TM_TS_ITR0                  TM_TRG_TRG_MUX_itr_w + TM_TRG_ITR_MUX_itr0_w    /*!< TM external trigger from ITR0 (reference funcion table).   */
#define TM_TS_ITR1                  TM_TRG_TRG_MUX_itr_w + TM_TRG_ITR_MUX_itr1_w    /*!< TM external trigger from ITR1 (reference funcion table).   */
#define TM_TS_ITR2                  TM_TRG_TRG_MUX_itr_w + TM_TRG_ITR_MUX_itr2_w    /*!< TM external trigger from ITR2 (reference funcion table).   */
#define TM_TS_ITR3                  TM_TRG_TRG_MUX_itr_w + TM_TRG_ITR_MUX_itr3_w    /*!< TM external trigger from ITR3 (reference funcion table).   */
#define TM_TS_ITR4                  TM_TRG_TRG_MUX_itr_w + TM_TRG_ITR_MUX_itr4_w    /*!< TM external trigger from ITR4 (reference funcion table).   */
#define TM_TS_ITR5                  TM_TRG_TRG_MUX_itr_w + TM_TRG_ITR_MUX_itr5_w    /*!< TM external trigger from ITR5 (reference funcion table).   */
#define TM_TS_ITR6                  TM_TRG_TRG_MUX_itr_w + TM_TRG_ITR_MUX_itr6_w    /*!< TM external trigger from ITR6 (reference funcion table).   */
#define TM_TS_ITR7                  TM_TRG_TRG_MUX_itr_w + TM_TRG_ITR_MUX_itr7_w    /*!< TM external trigger from ITR7 (reference funcion table).   */
#define TM_TS_IN0                   TM_TRG_TRG_MUX_in0_w                            /*!< TM external trigger from IN0.                              */
#define TM_TS_IN1                   TM_TRG_TRG_MUX_in1_w                            /*!< TM external trigger from IN1.                              */
//!@}

/** 
 * @struct  TM_SlaveConfigTypeDef
 * @brief   TM Slave configuration Structure definition                             
 */                                                                                
typedef struct __attribute__((packed))
{
    uint32_t  SlaveMode;            /*!< Slave mode selection
                                         This parameter can be a value of reference TM_Slave_Mode */
    uint32_t  InputTrigger;         /*!< Input Trigger source
                                         This parameter can be a value of reference TM_Trigger_Selection */
        
} TM_SlaveConfigTypeDef;


/**
 * @name	TM_Encoder_ModeDef
 *   		TM Encoder Mode definition
 */ 
//!@{
//! defgroup TM_Encoder_Mode TM Encoder Mode
#define TM_ENCODERDISABLE           TM_TRG_QEI_MDS_no_operation_w   /*!< Disable TM QEI function.                   */
#define TM_ENCODERMODE_IN0POS       TM_TRG_QEI_MDS_in0pos_w         /*!< Set TM QEI with IN0POS mode.               */
#define TM_ENCODERMODE_IN0NEG       TM_TRG_QEI_MDS_in0neg_w         /*!< Set TM QEI with IN0NEG mode.               */
#if defined(MG32_2ND) || defined(MG32_3RD)              
#define TM_ENCODERMODE_IN0TRG       TM_TRG_QEI_MDS_in0trg_w         /*!< Set TM QEI with IN0TRG mode.               */
#define TM_ENCODERMODE_IN1TRG       TM_TRG_QEI_MDS_in1trg_w         /*!< Set TM QEI with IN1TRG mode.               */
#endif      
#define TM_ENCODERMODE_BOTHEDGE     TM_TRG_QEI_MDS_both_w           /*!< Set TM QEI with BOTH mode.                 */    
//!@}

/**
 * @name	TM_Encoder_ResetMode
 *   		TM Encode Reset Enable/Disable and Reset IDX
 */ 
//!@{
#define TM_ENCODER_RESET_DISABLE    TM_TRG_IDX_EN_disable_w                         /*!< Disable QEI reset function.                                */ 
#define TM_ENCODER_RESET_1T2        TM_TRG_IDX_EN_enable_w + TM_TRG_IDX_MDS_1t2_w   /*!< QEI reset when QEI state between 1 & 2 and IDX happened.   */
#define TM_ENCODER_RESET_2T3        TM_TRG_IDX_EN_enable_w + TM_TRG_IDX_MDS_2t3_w   /*!< QEI reset when QEI state between 2 & 3 and IDX happened.   */
#define TM_ENCODER_RESET_3T4        TM_TRG_IDX_EN_enable_w + TM_TRG_IDX_MDS_3t4_w   /*!< QEI reset when QEI state between 3 & 4 and IDX happened.   */
#define TM_ENCODER_RESET_4T1        TM_TRG_IDX_EN_enable_w + TM_TRG_IDX_MDS_4t1_w   /*!< QEI reset when QEI state between 4 & 1 and IDX happened.   */
//!@}

/**
 * @name	TM_Encoder_Direction_Polarity
 *   		TM Encoder direction polarity
 */ 
//!@{
#define TM_ENCODER_DIRECTION_NORMAL     TM_CR0_DIR_INV_normal_w     /*!< Normal QEI direction.                      */         
#define TM_ENCODER_DIRECTION_INVERT     TM_CR0_DIR_INV_inverted_w   /*!< Invert QEI direction.                      */
//!@}

/**
 * @name	TM_Break_Channel_Switch_Mode
 *   		TM break channel switch mode
 */ 
//!@{
#define MID_BREAK_HOLD_STATE        (TM_BS_BK0_CTL_hold_w | TM_BS_BK1_CTL_hold_w | TM_BS_BK2_CTL_hold_w | TM_BS_BK3_CTL_hold_w) /*!< Output hold state when break event happened. */ 
#define MID_BREAK_STOP_STATE        (TM_BS_BK0_CTL_stop_w | TM_BS_BK1_CTL_stop_w | TM_BS_BK2_CTL_stop_w | TM_BS_BK3_CTL_stop_w) /*!< Output stop state when break event happened. */ 
//!@}

/**
 * @name	TM_Break_Input_enable_disable
 *   		TM Break Input Enable Disable
 */ 
//!@{
#define TM_BREAK_ENABLE             (TM_BS_BK_EN_enable_w | TM_BS_BK_EN3_enable_w)  /*!< Enable TM36 break function.            */
#define TM_BREAK_DISABLE            (0x0000U)                                       /*!< Disable TM36 break function (Default). */
//!@}


/**
 * @name	TM_Break_Mode
 *   		TM Break mode
 */ 
//!@{
#define TM_BK_CYCLE_BY_CYCLE        (TM_BS_BK_MDS_cycle_by_cycle_w) /*!< Set TM36 break function with cycle-by-cycle mode.  */
#define TM_BK_LATCH                 (TM_BS_BK_MDS_latch_mode_w)     /*!< Set TM36 break function with latch mode.           */
//!@}


/**
 * @name	MID_TM_CKDTG_DividerDef
 *   		Timer internal dead time CK_DTG divider
 */ 
//!@{
#define MID_TM_CKDTG_DIV1           TM_CLK_DTG_DIV_div1_w       /*!< TM36 dead time clock divide 1.                 */
#define MID_TM_CKDTG_DIV2           TM_CLK_DTG_DIV_div2_w       /*!< TM36 dead time clock divide 2.                 */
#define MID_TM_CKDTG_DIV4           TM_CLK_DTG_DIV_div4_w       /*!< TM36 dead time clock divide 4.                 */
#define MID_TM_CKDTG_DIV8           TM_CLK_DTG_DIV_div8_w       /*!< TM36 dead time clock divide 8.                 */
//!@}


/**
 * @name	MID_TM_BreakSourceDef
 *   		Timer Break Source
 */ 
//!@{
#define MID_BK_ExtPin               TM_BS_BKE_EN0_enable_w      /*!< TM36 Break External trigger pin.                           */
#define MID_BK_BOD1                 TM_BS_BKE_EN1_enable_w      /*!< TM36 Break External trigger event from BOD1 event.         */
#define MID_BK_INTPB                TM_BS_BKE_EN2_enable_w      /*!< TM36 Break External trigger event from INT_PB.             */
#define MID_BK_ADC0OUT              TM_BS_BKE_EN3_enable_w      /*!< TM36 Break External trigger event from ADC0_OUT (Window detect). */
#define MID_BK_COMP0OUT             TM_BS_BKE_EN4_enable_w      /*!< TM36 Break External trigger event from Comparator0 output. */
#define MID_BK_COMP1OUT             TM_BS_BKE_EN5_enable_w      /*!< TM36 Break External trigger event from Comparator1 output. */
#define MID_BK_COMP2OUT             TM_BS_BKE_EN6_enable_w      /*!< TM36 Break External trigger event from Comparator2 output. */
#define MID_BK_COMP3OUT             TM_BS_BKE_EN7_enable_w      /*!< TM36 Break External trigger event from Comparator3 output. */
#define MID_BK_ClockFailure         TM_BS_BKI_EN0_enable_w      /*!< Clock failure event.                                       */
#define MID_BK_CPULOCKUP            TM_BS_BKI_EN2_enable_w      /*!< CPU LOCKUP.                                                */
//!@}


/** 
 * @struct  TM_BreakDeadTimeConfigTypeDef
 * @brief   TM Break and Dead time configuration Structure definition  
 */ 
typedef struct __attribute__((packed))
{
  uint32_t BreakCHxOutputMode;      /*!< TM channel output switch control when break event happened.
                                         This parameter can be a value of reference TM_Break_Channel_Switch_Mode */
                    
  uint32_t BreakMode;                /*!< TM dead Time 
                                          This parameter can be a value of reference TM_Break_Mode (TM_BK_CYCLE_BY_CYCLE or TM_BK_LATCH)  */
                    
  uint32_t DeatTimeClockDivision;   /*!< Specifies the clock division.
                                         This parameter can be a value of reference MID_TM_CKDTG_DividerDef */
                    
  uint32_t DeadTime;                 /*!< TM dead Time 
                                          This parameter can be a number between Min_Data = 0x00 and Max_Data = 0xFF */
                    
  uint32_t BreakSourceSel;           /*!< TM dead Time 
                                          This parameter can be a value of reference MID_TM_BreakSourceDef */
} TM_BreakDeadTimeConfigTypeDef;


/**
 * @name	TM_Master_Mode_Selection
 *   		TM Master Mode Selection
 */ 
//!@{
#define	TM_TRGO_RESET               (TM_TRG_TRGO_MDS_mask_w)    /*!< TM TRGO source from reset event.               */
#define	TM_TRGO_ENABLE              (TM_TRG_TRGO_MDS_en_w)      /*!< TM TRGO source from main counter enable state. */
#define	TM_TRGO_UPDATE              (TM_TRG_TRGO_MDS_uev_w)     /*!< TM TRGO source from update event.              */
#define	TM_TRGO_UPDATE_UPFLAG       (TM_TRG_TRGO_MDS_tof_w)     /*!< TM TRGO source from overflow flag state.       */
#define	TM_TRGO_UPDATE_DOWNFLAG     (TM_TRG_TRGO_MDS_tuf_w)     /*!< TM TRGO source from underflow flag state.      */
#define	TM_TRGO_ENABLE2             (TM_TRG_TRGO_MDS_en2_w)     /*!< TM TRGO source from prescaler counter enable state. */
#define	TM_TRGO_UPDATE_UPFLAG2      (TM_TRG_TRGO_MDS_tof2_w)    /*!< TM TRGO source from prescaler overflow flag state. */
#define	TM_TRGO_DIRECTION           (TM_TRG_TRGO_MDS_dir_w)     /*!< TM TRGO source from direction state.           */
#define	TM_TRGO_UPDATE2             (TM_TRG_TRGO_MDS_uev2_w)    /*!< TM TRGO source from prescaler update event.    */
#define	TM_TRGO_SOFTWARE            (TM_TRG_TRGO_MDS_sw_w)      /*!< TM TRGO source from software control state.    */
#define	TM_TRGO_OC0                 (TM_TRG_TRGO_MDS_os0_w)     /*!< TM TRGO source from OC0 state.                 */
#define	TM_TRGO_OC1                 (TM_TRG_TRGO_MDS_os1_w)     /*!< TM TRGO source from OC1 state.                 */
#define	TM_TRGO_OC2                 (TM_TRG_TRGO_MDS_os2_w)     /*!< TM TRGO source from OC2 state.                 */
#define	TM_TRGO_OC3                 (TM_TRG_TRGO_MDS_os3_w)     /*!< TM TRGO source from OC3 state.                 */
#define	TM_TRGO_TRGI                (TM_TRG_TRGO_MDS_trgi_w)    /*!< TM TRGO source from TRGI.                      */
#define	TM_TRGO_PRELOAD             (TM_TRG_TRGO_MDS_poe_w)     /*!< TM TRGO source from preload event.             */
//!@}

/**
 * @name	TM_Master_Output_Polarity
 *   		TM Master output polarity
 */ 
//!@{
#define TM_MASTEROUTPUT_BYPASS      (TM_TRG_TRGO_INV_disable_w) /*!< Notmal output TM TRGO.                         */
#define TM_MASTEROUTPUT_INVERT      (TM_TRG_TRGO_INV_enable_w)  /*!< Invert TM TRGO.                                */
//!@}


/**
 * @name	TM_TRGO_Update_Control
 *   		TM TRGO Update event source/control
 */ 
//!@{
#define TM_UPDATE_DISABLE           (0xFFFFFFFF)                /*!< Disable TM update event.                       */
#define TM_UPDATE_BOTH              (TM_TRG_UEV_SEL_all_w)      /*!< Accept TM update event (Overflow or underflow). */
#define TM_UPDATE_OVERFLOW          (TM_TRG_UEV_SEL_tof_w)      /*!< Accept TM overflow event.                      */
#define TM_UPDATE_UNDERFLOW         (TM_TRG_UEV_SEL_udf_w)      /*!< Accept TM underflow event.                     */
//!@}


/** 
 * @struct  TM_MasterConfigTypeDef
 * @brief   TM Master configuration Structure definition  
 */ 
typedef struct __attribute__((packed)) {
    uint32_t MasterOutputTrigger;   /*!< Trigger output (TRGO) selection 
                                         This parameter can be a value of reference TM_Master_Mode_Selection */ 
        
    uint32_t MasterOutputPolarity;  /*!< Specifies the polarity of the output signal.
                                         This parameter can be a value of reference TM_Master_Output_Polarity */
            
    uint32_t MasterUpdateEvent;     /*!< Source selection of TM_TRGO_UPDATE
                                         This parameter can be a value of reference TM_TRGO_Update_Control */ 
    
}TM_MasterConfigTypeDef;


/** 
 * @struct TM_Encoder_InitTypeDef
 * @brief  TM Encoder Configuration Structure definition
 */ 
typedef struct __attribute__((packed))
{
    uint32_t EncoderMode;           /*!< Specifies the QEI mode.
                                         This parameter can be a value of reference TM_Encoder_Mode */
                
    uint32_t EncoderReset;          /*!< Specifies the index of the input signal.
                                         This parameter can be a value of reference TM_Encoder_ResetMode */
                
    uint32_t EncoderDirection;      /*!< Specifies the active direction of the input signal.
                                         This parameter can be a value of reference TM_Encoder_Direction_Polarity */
                
    uint32_t IC0Selection;          /*!< Specifies the input of channel0.
                                         This parameter can be a value of reference TM_Input_Capture_Selection */
                
    uint32_t IC1Selection;          /*!< Specifies the input of channel1.
                                         This parameter can be a value of reference TM_Input_Capture_Selection */
    
} TM_Encoder_InitTypeDef;

/**
 * @name	TM_Event_Source
 *   		TM Event Source
 */ 
//!@{
#define TM_EVENTSOURCE_CC0A         0x0U                        /*!< Software generate CC0A event.                  */
#define TM_EVENTSOURCE_CC0B         0x1U                        /*!< Software generate CC0B event.                  */
#define TM_EVENTSOURCE_CC1A         0x2U                        /*!< Software generate CC1A event.                  */
#define TM_EVENTSOURCE_CC1B         0x3U                        /*!< Software generate CC1B event.                  */
#define TM_EVENTSOURCE_CC2A         0x4U                        /*!< Software generate CC2A event.                  */
#define TM_EVENTSOURCE_CC2B         0x5U                        /*!< Software generate CC2B event.                  */
#define TM_EVENTSOURCE_CC3A         0x6U                        /*!< Software generate CC3A event.                  */
#define TM_EVENTSOURCE_CC3B         0x7U                        /*!< Software generate CC3B event.                  */
#define TM_EVENTSOURCE_TRIGGER      0x8U                        /*!< Software generate external trigger event.      */
#define TM_EVENTSOURCE_BREAK        TM_BS_BKSW_EN_enable_w      /*!< Software generate break event.                 */
//!@}

/**
 * @name	TM_PreLoad_CH0
 *   		TM preload channel0 control
 */ 
//!@{
#define TM_PRELOADOC00_ENABLE       (TM_OCCR1_OC0_POE0_mask_b2) /*!< Channel0-0 preload control (enable output).    */
#define TM_PRELOADOC01_ENABLE       (TM_OCCR1_OC0_POE1_mask_b2) /*!< Channel0-1 preload control (enable output).    */
#define TM_PRELOADOC02_ENABLE       (TM_OCCR1_OC0_POE2_mask_b2) /*!< Channel0-2 preload control (enable output).    */
#define TM_PRELOADOC0_ALL_ENABLE    (TM_PRELOADOC00_ENABLE | TM_PRELOADOC01_ENABLE | TM_PRELOADOC02_ENABLE) /*!< Channel0-0/1/2 preload control (all enable output). */
//!@}

/**
 * @name	TM_PreLoad_CH1
 *   		TM preload channel1 control
 */ 
//!@{
#define TM_PRELOADOC10_ENABLE       (TM_OCCR1_OC1_POE0_mask_b2) /*!< Channel1-0 preload control (enable output).    */
#define TM_PRELOADOC11_ENABLE       (TM_OCCR1_OC1_POE1_mask_b2) /*!< Channel1-1 preload control (enable output).    */
#define TM_PRELOADOC12_ENABLE       (TM_OCCR1_OC1_POE2_mask_b2) /*!< Channel1-2 preload control (enable output).    */
#define TM_PRELOADOC1_ALL_ENABLE    (TM_PRELOADOC10_ENABLE | TM_PRELOADOC11_ENABLE | TM_PRELOADOC12_ENABLE) /*!< Channel1-0/1/2 preload control (all enable output). */
//!@}

/**
 * @name	TM_PreLoad_CH0
 *   		TM preload channel0 control
 */ 
//!@{
#define TM_PRELOAD_3XOR             (TM_OCCR1_POE_EN0_enable_w) /*!< Preload control signal event from 3-XOR.       */
#define TM_PRELOAD_INTPB            (TM_OCCR1_POE_EN1_enable_w) /*!< Preload control signal event from INT-PB.      */
#define TM_PRELOAD_INTPD            (TM_OCCR1_POE_EN2_enable_w) /*!< Preload control signal event from INT-PD.      */
//!@}

/**
 * @name	TM_One_Pulse_Mode
 *   		TM One Pulse Mode
 */ 
//!@{
#define TM_OPMODE_SINGLE            (TM_CR0_ASTOP_EN_enable_w)                              /*!< Only generate One-plus.    */
#define TM_OPMODE_REPETITIVE        (TM_CR0_ASTOP_EN_enable_w | TM_CR0_ACLEAR_EN_enable_w)  /*!< REPETITIVE generate plus.  */
//!@}

/**
 * @name	TM_Software_Break_state
 *   		Software control break state
 */ 
//!@{
#define TM_SOFTWARE_ENABLE_BREAK    (TM_BS_BKSW_EN_enable_w)    /*!< Enable software break state.                   */
#define TM_SOFTWARE_DISABLE_BREAK   (TM_SOFTWARE_ENABLE_BREAK)  /*!< Disable software break state.                  */
//!@}

/**
 * @name	TM_DMAUpdateTiming
 *   		Software control break state
 */ 
//!@{
#define TM_UPDATEG_EVENT_TIMING     (TM_CCMDS_DMA_OMDS_uev_w)   /*!< Every TM main counter update event 
                                                                     will update OC/PWM's channel-X compare-B.      */
#define TM_ITR_EVENT_TIMING         (TM_CCMDS_DMA_OMDS_itr_w)   /*!< Both UEV (update event) and ITR input event 
                                                                     has occurred then trigger DMA to update.       */
//!@}

/**
 * @name	TM_CKO_InitialState
 *   		TM Clockout initial state
 */ 
//!@{
#define TM_CKOINIT_RESET            (TM_CKO_CKO_STA_0_w)        /*!< TM CKO initial state is 0 (Output 0).          */
#define TM_CKOINIT_SET              (TM_CKO_CKO_STA_1_w)        /*!< TM CKO initial state is 1 (Output 1).          */
//!@}

/**
 * @name	TM_CKO_Source
 *   		TM Clockout clock source definit
 */ 
//!@{
#define TM_CKOSOURCE_PRESCALER      (TM_CKO_CKO_SEL_2nd_w)      /*!< TM CKO clock source from prescaler counter overflow/underflow. */
#define TM_CKOSOURCE_MAIN           (TM_CKO_CKO_SEL_main_w)     /*!< TM CKO clock source from main counter overflow/underflow.      */
//!@}


/** 
 * @struct  TM_CKOConfigTypeDef
 * @brief   TM clockout Configuration Structure definition
 */ 
typedef struct
{
    uint32_t CKOInitState;          /*!< Specifies the timer CKO output signal initial state. 
                                         This parameter can be a value of reference TM_CKO_InitialState. */
                    
    uint32_t CKOSource;             /*!< Specifies the timer clock out source event.
                                         This parameter can be a value of reference TM_CKO_Source. */

    uint32_t CKOCmd;                /*!< Specifies the timer clockout function.
                                         This parameter can be: ENABLE or DISABLE. */

} TM_CKOConfigTypeDef;


#if defined(MG32_3RD)

/**
 * @name	TM_RCNT_ClockSource
 *   		TM RCNT clock source definit
 */ 
//!@{
#define TM_RCNT_MAIN_EVENT          (TM_CLK_RC_CKS_main_w)                          /*!< TM RCNT clock source from main counter overflow/underflow.             */
#define TM_RCNT_CKO_MAIN_EVENT      (TM_CLK_RC_CKS_cko_w | TM_CKO_CKO_SEL_main_w)   /*!< TM RCNT clock source from CKO's main counter overflow/underflow.       */
#define TM_RCNT_CKO_PRESCALER_EVENT (TM_CLK_RC_CKS_cko_w | TM_CKO_CKO_SEL_2nd_w)    /*!< TM RCNT clock source from CKO's prescaler counter overflow/underflow.  */
//!@}


/** 
 * @struct  TM_RCNTConfigTypeDef
 * @brief   TM RCNT Configuration Structure definition
 */ 
typedef struct __attribute__((packed))
{
    uint32_t RCNTClkSrc;            /*!< Specifies the timer's RCNT clock source event.
                                         This parameter can be a value of reference TM_RCNT_ClockSource. */
                    
    uint8_t  RCNTCounter;           /*!< Specifies the RCNT counter value. RCNT is normal downcount.
                                         This parameter can be a number between 0x00 and 0xFF. */

    uint8_t  RCNTReload;            /*!< Specifies the RCNT reload value. Used to reload RCNT when RCNT underflow.
                                         This parameter can be a number between 0x00 and 0xFF. */

} TM_RCNTConfigTypeDef;

#endif

/**
 * @name	TM_SOFTWARE_TRGOSTATE
 *   		Timer software control TRGO state
 */ 
//!@{
#define TM_SWTRGO_HIGH              (TM_TRG_TRGO_SW_1_w)        /*!< Timer control TRGO output 1.                   */
#define TM_SWTRGO_LOW               (TM_TRG_TRGO_SW_0_w)        /*!< Timer control TRGO output 0.                   */
//!@}








/**
 *******************************************************************************
 * @brief       Software enable break state.
 * @param[in]   "__HANDLE__" : pointer to a TM_HandleTypeDef.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_SOFTWARE_ENABLE_BREAK(__HANDLE__)  \
    ((__HANDLE__)->Instance->BS.W |= (TM_SOFTWARE_ENABLE_BREAK))

/**
 *******************************************************************************
 * @brief       Software disable break state.
 * @param[in]   "__HANDLE__" : pointer to a TM_HandleTypeDef.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_SOFTWARE_DISABLE_BREAK(__HANDLE__) \
    ((__HANDLE__)->Instance->BS.W &= (~(TM_SOFTWARE_DISABLE_BREAK)))

/**
 *******************************************************************************
 * @brief       Sets the TM break mode.
 * @param[in]   "__HANDLE__" : specifies the TM Handle.
 * @param[in]   "__BKMODE__ specifies the Break Mode.
 *  @arg\b      TM_BK_CYCLE_BY_CYCLE : Cycle by cycle mode.
 *  @arg\b      TM_BK_LATCH : Latch mode.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_SET_BREAK_MODE(__HANDLE__, __BKMODE__)             \
        ((__HANDLE__)->Instance->BS.W &= ~(TM_BS_BK_MDS_mask_w));   \
        ((__HANDLE__)->Instance->BS.W |= (__BKMODE__))


/**
 *******************************************************************************
 * @brief       Enables the specified TM Break Source.
 * @param[in]   "__HANDLE__" : pointer to a TM_HandleTypeDef.
 * @param[in]   "__BKSRC__" : specifies the TM break source to enable.
 *  @arg\b      MID_BK_ExtPin : TM36 Break External trigger pin.
 *  @arg\b      MID_BK_BOD1 : TM36 Break External trigger event from BOD1 event.
 *  @arg\b      MID_BK_INTPB : TM36 Break External trigger event from INT_PB.
 *  @arg\b      MID_BK_ADC0OUT : TM36 Break External trigger event from ADC0_OUT (Window detect).
 *  @arg\b      MID_BK_COMP0OUT : Break External trigger event from Comparator0 output.
 *  @arg\b      MID_BK_COMP1OUT : Break External trigger event from Comparator0 output.
 *  @arg\b      MID_BK_COMP2OUT : Break External trigger event from Comparator0 output.
 *  @arg\b      MID_BK_COMP3OUT : Break External trigger event from Comparator0 output.
 *  @arg\b      MID_BK_ClockFailure : Clock failure event.
 *  @arg\b      MID_BK_CPULOCKUP : CPU LOCKUP.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_ENABLE_BREAKSOURCE(__HANDLE__, __BKSRC__)  \
    ((__HANDLE__)->Instance->BS.W |= (__BKSRC__))

/**
 *******************************************************************************
 * @brief       Disables the specified TM Break Source.
 * @param[in]   "__HANDLE__" : pointer to a TM_HandleTypeDef.
 * @param[in]   "__BKSRC__" : specifies the TM break source to disable.
 *  @arg\b      MID_BK_ExtPin : TM36 Break External trigger pin.
 *  @arg\b      MID_BK_BOD1 : TM36 Break External trigger event from BOD1 event.
 *  @arg\b      MID_BK_INTPB : TM36 Break External trigger event from INT_PB.
 *  @arg\b      MID_BK_ADC0OUT : TM36 Break External trigger event from ADC0_OUT (Window detect).
 *  @arg\b      MID_BK_COMP0OUT : Break External trigger event from Comparator0 output.
 *  @arg\b      MID_BK_COMP1OUT : Break External trigger event from Comparator0 output.
 *  @arg\b      MID_BK_COMP2OUT : Break External trigger event from Comparator0 output.
 *  @arg\b      MID_BK_COMP3OUT : Break External trigger event from Comparator0 output.
 *  @arg\b      MID_BK_ClockFailure : Clock failure event.
 *  @arg\b      MID_BK_CPULOCKUP : CPU LOCKUP.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_DISABLE_BREAKSOURCE(__HANDLE__, __BKSRC__) \
    ((__HANDLE__)->Instance->BS.W &= ~(__BKSRC__))

/**
 *******************************************************************************
 * @brief       Enables the break function on PWM output channel.
 * @param[in]   "__HANDLE__" : pointer to a TM_HandleTypeDef.
 * @return      None.
 * @note        Break function uses only with TM36.
 *******************************************************************************
 */
#define __DRV_TM_ENABLE_BREAK(__HANDLE__)   \
    ((__HANDLE__)->Instance->BS.W |= (TM_BREAK_ENABLE))

/**
 *******************************************************************************
 * @brief       Disables the break function on PWM output channel.
 * @param[in]   "__HANDLE__" : pointer to a TM_HandleTypeDef.
 * @return      None.
 * @note        Break function uses only with TM36.
 *******************************************************************************
 */
#define __DRV_TM_DISABLE_BREAK(__HANDLE__)  \
    ((__HANDLE__)->Instance->BS.W &= ~(TM_BREAK_ENABLE))

/**
 *******************************************************************************
 * @brief       Disables the specified TM interrupt.
 * @param[in]   "__HANDLE__" : pointer to a TM_HandleTypeDef.
 * @param[in]   "__INTERRUPT__" : specifies the TM interrupt source to enable.
 *  @arg\b      TM_IT_CC0 : Capture/Compare 0 interrupt.
 *  @arg\b      TM_IT_CC1 : Capture/Compare 1 interrupt.
 *  @arg\b      TM_IT_CC2 : Capture/Compare 2 interrupt.
 *  @arg\b      TM_IT_CC3 : Capture/Compare 3 interrupt.
 *  @arg\b      TM_IT_UPDATE : Main Counter update interrupt.
 *  @arg\b      TM_IT_UPDATE2 : Prescaler Counter update interrupt.
 *  @arg\b      TM_IT_BREAK : Break interrupt.
 *  @arg\b      TM_IT_EXTERNAL : External Trigger interrupt.
 *  @arg\b      TM_IT_QEI_DIRC : QEI direction change interrupt.
 *  @arg\b      TM_IT_QEI_INDEX : QEI Index interrupt.
 *  @arg\b      TM_IT_QEI_ERROR : QEI Error Position interrupt.
 *  @arg\b      TM_IT_ONEPULSE : Repetition timer underflow interrupt enable.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_DISABLE_IT(__HANDLE__, __INTERRUPT__)  \
    ((__HANDLE__)->Instance->INT.W &= ~(__INTERRUPT__))


/**
 *******************************************************************************
 * @brief       Reset TM handle state.
 * @param[in]   "__HANDLE__" : specifies the TM Handle.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_RESET_HANDLE_STATE(__HANDLE__) \
    ((__HANDLE__)->State = MID_TM_STATE_RESET)

/**
 *******************************************************************************
 * @brief       Enable the TM peripheral.
 * @param[in]   "__HANDLE__" : pointer to a TM_HandleTypeDef.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_ENABLE(__HANDLE__) \
    ((__HANDLE__)->Instance->CR0.W |= TM_CR0_EN_enable_w | TM_CR0_EN2_enable_w)

/**
 *******************************************************************************
 * @brief       Disable the TM peripheral.
 * @param[in]   "__HANDLE__" : pointer to a TM_HandleTypeDef.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_DISABLE(__HANDLE__)                        \
    do{                                                     \
        if((__HANDLE__)->Instance->CCMDS.H[0] == 0x0000)    \
        { \
            (__HANDLE__)->Instance->CR0.W &= ~(TM_CR0_EN_enable_w | TM_CR0_EN2_enable_w); \
        } \
    }while (0)

/**
 *******************************************************************************
 * @brief       Enables the specified TM interrupt.
 * @param[in]   "__HANDLE__" : pointer to a TM_HandleTypeDef.
 * @param[in]   "__INTERRUPT__" : specifies the TM interrupt source to enable.
 *  @arg\b      TM_IT_CC0 : Capture/Compare 0 interrupt.
 *  @arg\b      TM_IT_CC1 : Capture/Compare 1 interrupt.
 *  @arg\b      TM_IT_CC2 : Capture/Compare 2 interrupt.
 *  @arg\b      TM_IT_CC3 : Capture/Compare 3 interrupt.
 *  @arg\b      TM_IT_UPDATE : Main Counter update interrupt.
 *  @arg\b      TM_IT_UPDATE2 : Prescaler Counter update interrupt.
 *  @arg\b      TM_IT_BREAK : Break interrupt.
 *  @arg\b      TM_IT_EXTERNAL : External Trigger interrupt.
 *  @arg\b      TM_IT_QEI_DIRC : QEI direction change interrupt.
 *  @arg\b      TM_IT_QEI_INDEX : QEI Index interrupt.
 *  @arg\b      TM_IT_QEI_ERROR : QEI Error Position interrupt.
 *  @arg\b      TM_IT_ONEPULSE : Repetition timer underflow interrupt enable.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_ENABLE_IT(__HANDLE__, __INTERRUPT__)   \
    ((__HANDLE__)->Instance->INT.W |= (uint32_t)(__INTERRUPT__))

/**
 *******************************************************************************
 * @brief       Checks whether the specified TM interrupt has occurred or not.
 * @param[in]   "__HANDLE__" : pointer to a TM_HandleTypeDef.
 * @param[in]   "__INTERRUPT__" : specifies the TM interrupt source to enable.
 *  @arg\b      TM_IT_CC0 : Capture/Compare 0 interrupt.
 *  @arg\b      TM_IT_CC1 : Capture/Compare 1 interrupt.
 *  @arg\b      TM_IT_CC2 : Capture/Compare 2 interrupt.
 *  @arg\b      TM_IT_CC3 : Capture/Compare 3 interrupt.
 *  @arg\b      TM_IT_UPDATE : Main Counter update interrupt.
 *  @arg\b      TM_IT_UPDATE2 : Prescaler Counter update interrupt.
 *  @arg\b      TM_IT_BREAK : Break interrupt.
 *  @arg\b      TM_IT_EXTERNAL : External Trigger interrupt.
 *  @arg\b      TM_IT_QEI_DIRC : QEI direction change interrupt.
 *  @arg\b      TM_IT_QEI_INDEX : QEI Index interrupt.
 *  @arg\b      TM_IT_QEI_ERROR : QEI Error Position interrupt.
 *  @arg\b      TM_IT_ONEPULSE : Repetition timer underflow interrupt enable.
 * @return		The state of EVENT (SET or RESET).
 *******************************************************************************
 */
#define __DRV_TM_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)   \
    (((__HANDLE__)->Instance->INT.W & (uint32_t)(__INTERRUPT__)) == (uint32_t)(__INTERRUPT__))


/**
 *******************************************************************************
 * @brief       Enables the specified TM All interrupt.
 * @param[in]   "__HANDLE__" : pointer to a TM_HandleTypeDef.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_ENABLE_ITEA(__HANDLE__)    \
    ((__HANDLE__)->Instance->INT.W |= TM_INT_IEA_enable_w)

/**
 *******************************************************************************
 * @brief       Disables the specified TM All interrupt.
 * @param[in]   "__HANDLE__" : pointer to a TM_HandleTypeDef.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_DISABLE_ITEA(__HANDLE__)               \
    do{                                                 \
        if((__HANDLE__)->Instance->INT.W != 0x00000000) \
        { \
            ((__HANDLE__)->Instance->INT.W &= ~TM_INT_IEA_enable_w); \
        } \
    }while (0)
    

/**
 *******************************************************************************
 * @brief       Enables the specified DMA request.
 * @param[in]   "__HANDLE__" : specifies the TM Handle.
 * @param[in]   "__DMA__" : specifies the TM DMA request to enable.
 *  @arg\b      TM_DMA_CH0_OC.
 *  @arg\b      TM_DMA_CH1_OC.
 *  @arg\b      TM_DMA_CH2_OC.
 *  @arg\b      TM_DMA_CH3_IC.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_ENABLE_DMA(__HANDLE__, __DMA__)    \
    ((__HANDLE__)->Instance->CCMDS.W |= (uint32_t)(__DMA__))

/**
 *******************************************************************************
 * @brief       Disables the specified DMA request.
 * @param[in]   "__HANDLE__" : specifies the TM Handle.
 * @param[in]   "__DMA__" : specifies the TM DMA request to enable.
 *  @arg\b      TM_DMA_CH0_OC.
 *  @arg\b      TM_DMA_CH1_OC.
 *  @arg\b      TM_DMA_CH2_OC.
 *  @arg\b      TM_DMA_CH3_IC.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_DISABLE_DMA(__HANDLE__, __DMA__)   \
    ((__HANDLE__)->Instance->CCMDS.W &= (uint32_t)(~(__DMA__)))

/**
 *******************************************************************************
 * @brief       Get the TM interrupt pending bits.
 * @param[in]   "__HANDLE__" : specifies the TM Handle.
 * @param[in]   "__FLAG__" : specifies the TM interrupt flag to clear.
 *  @arg\b      TM_FLAG_CC0A : Capture/Compare-A 0 interrupt pending bit.
 *  @arg\b      TM_FLAG_CC1A : Capture/Compare-A 1 interrupt pending bit.
 *  @arg\b      TM_FLAG_CC2A : Capture/Compare-A 2 interrupt pending bit.
 *  @arg\b      TM_FLAG_CC3A : Capture/Compare-A 3 interrupt pending bit.
 *  @arg\b      TM_FLAG_CC0B : Capture/Compare-B 0 interrupt pending bit.
 *  @arg\b      TM_FLAG_CC1B : Capture/Compare-B 1 interrupt pending bit.
 *  @arg\b      TM_FLAG_CC2B : Capture/Compare-B 2 interrupt pending bit.
 *  @arg\b      TM_FLAG_CC3B : Capture/Compare-B 3 interrupt pending bit.
 *  @arg\b      TM_FLAG_UPDATE_UP : Main counter overflow interrupt pending bit.
 *  @arg\b      TM_FLAG_UPDATE_DOWN : Main counter underflow interrupt pending bit.
 *  @arg\b      TM_FLAG_UPDATE2_UP : Prescaler counter overflow interrupt pending bit.
 *  @arg\b      TM_FLAG_UPDATE2_DOWN : Prescaler counter underflow interrupt pending bit.
 *  @arg\b      TM_FLAG_BREAK : TM receive break interrupt pending bit.
 *  @arg\b      TM_FLAG_EXTERNAL : TM receive external trigger interrupt pending bit.
 *  @arg\b      TM_FLAG_QEI_DIRCHANGE : QEI change directiuon interrupt pending bit.
 *  @arg\b      TM_FLAG_QEI_INDEX : QEI index signal interrupt pending bit.
 *  @arg\b      TM_FLAG_QEI_ERROR : QEI error interrupt pending bit.
 *  @arg\b      TM_FLAG_DIRECTION : TM counter direction state.
 *  @arg\b      TM_FLAG_ONEPULSE : TM Repetition timer underflow flag.
 * @return      The state of FLAG (SET or RESET).
 *******************************************************************************
 */
#define __DRV_TM_GET_FLAG(__HANDLE__,__FLAG__)  \
    (((__HANDLE__)->Instance->STA.W & (uint32_t)(__FLAG__)) == (uint32_t)(__FLAG__))

/**
 *******************************************************************************
 * @brief       Get the TM event interrupt pending bits.
 * @param[in]   "__HANDLE__" : specifies the TM Handle.
 * @param[in]   "__EVENT__" : specifies the TM interrupt flag to clear.
 *  @arg\b      TM_EVENT_UPDATE. 
 *  @arg\b      TM_EVENT_UPDATE2.
 *  @arg\b      TM_EVENT_CH0.    
 *  @arg\b      TM_EVENT_CH1.    
 *  @arg\b      TM_EVENT_CH2.    
 *  @arg\b      TM_EVENT_CH3.    
 *  @arg\b      TM_EVENT_QEI.    
 *  @arg\b      TM_EVENT_ONEPULSE.    
 * @return      The state of FLAG (SET or RESET).
 *******************************************************************************
 */
#define __DRV_TM_GET_EVENT(__HANDLE__,__EVENT__)  \
    (((__HANDLE__)->Instance->STA.W & (uint32_t)(__EVENT__)) != (0))

/**
 *******************************************************************************
 * @brief       Clear the TM interrupt pending bits.
 * @param[in]   "__HANDLE__" : specifies the TM Handle.
 * @param[in]   "__FLAG__" : specifies the TM interrupt flag to clear.
 *  @arg\b      TM_FLAG_CC0A : Capture/Compare-A 0 interrupt pending bit.
 *  @arg\b      TM_FLAG_CC1A : Capture/Compare-A 1 interrupt pending bit.
 *  @arg\b      TM_FLAG_CC2A : Capture/Compare-A 2 interrupt pending bit.
 *  @arg\b      TM_FLAG_CC3A : Capture/Compare-A 3 interrupt pending bit.
 *  @arg\b      TM_FLAG_CC0B : Capture/Compare-B 0 interrupt pending bit.
 *  @arg\b      TM_FLAG_CC1B : Capture/Compare-B 1 interrupt pending bit.
 *  @arg\b      TM_FLAG_CC2B : Capture/Compare-B 2 interrupt pending bit.
 *  @arg\b      TM_FLAG_CC3B : Capture/Compare-B 3 interrupt pending bit.
 *  @arg\b      TM_FLAG_UPDATE_UP : Main counter overflow interrupt pending bit.
 *  @arg\b      TM_FLAG_UPDATE_DOWN : Main counter underflow interrupt pending bit.
 *  @arg\b      TM_FLAG_UPDATE2_UP : Prescaler counter overflow interrupt pending bit.
 *  @arg\b      TM_FLAG_UPDATE2_DOWN : Prescaler counter underflow interrupt pending bit.
 *  @arg\b      TM_FLAG_BREAK : TM receive break interrupt pending bit.
 *  @arg\b      TM_FLAG_EXTERNAL : TM receive external trigger interrupt pending bit.
 *  @arg\b      TM_FLAG_QEI_DIRCHANGE : QEI change directiuon interrupt pending bit.
 *  @arg\b      TM_FLAG_QEI_INDEX : QEI index signal interrupt pending bit.
 *  @arg\b      TM_FLAG_QEI_ERROR : QEI error interrupt pending bit.
 *  @arg\b      TM_FLAG_DIRECTION : TM counter direction state.
 *  @arg\b      TM_FLAG_ONEPULSE : TM Repetition timer underflow flag.
 * @return      None
 *******************************************************************************
 */
#define __DRV_TM_CLEAR_FLAG(__HANDLE__,__FLAG__)    \
    ((__HANDLE__)->Instance->STA.W = (uint32_t)(__FLAG__))


/**
 *******************************************************************************
 * @brief       Sets the TM active prescaler register value on update event.
 * @param[in]   "__HANDLE__" : specifies the TM Handle.
 * @param[in]   "__PRESC__" : specifies the active prescaler register new value.
 * @return      None
 *******************************************************************************
 */
#define __DRV_TM_SET_PRESCALER(__HANDLE__, __PRESC__)   \
    ((__HANDLE__)->Instance->PSCNT.W = (uint32_t)(__PRESC__))

/**
 *******************************************************************************
 * @brief       Sets the TM Capture Compare Register value on run time without
 *              calling another TMe ConfigChannel function.t.
 * @param[in]   "__HANDLE__" : specifies the TM Handle.
 * @param[in]   "__CHANNEL__" : TM Channels to be configured.
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @param[in]   "__COMPARE__ specifies the Capture Compare register new value.
 * @return      None
 *******************************************************************************
 */
#define __DRV_TM_SET_COMPARE(__HANDLE__, __CHANNEL__, __COMPARE__) \
    (*(__IO uint32_t *)(&((__HANDLE__)->Instance->CC0A.W) + (__CHANNEL__ << 1)) = (uint32_t)(__COMPARE__))

/**
 *******************************************************************************
 * @brief       Sets the TM Capture Compare Register-B value on run time without
 *              calling another TMe ConfigChannel function.t.
 * @param[in]   "__HANDLE__" : specifies the TM Handle.
 * @param[in]   "__CHANNEL__" TM Channels to be configured.
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @param[in]   "__COMPARE__" : specifies the Capture Compare register new value.
 * @return      None
 *******************************************************************************
 */
#define __DRV_TM_SET_COMPARE_B(__HANDLE__, __CHANNEL__, __COMPARE__) \
    (*(__IO uint32_t *)(&((__HANDLE__)->Instance->CC0B.W) + (__CHANNEL__ << 1)) = (uint32_t)(__COMPARE__))


/**
 *******************************************************************************
 * @brief       Gets the TM Capture Compare Register value on run time
 * @param[in]   "__HANDLE__" : specifies the TM Handle.
 * @param[in]   "__CHANNEL__" : TM Channels to be configured.
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt
 * @return      16-bit value of the capture/compare register
 *******************************************************************************
 */
#define __DRV_TM_GET_COMPARE(__HANDLE__, __CHANNEL__) \
    (*(__IO uint32_t *)(&((__HANDLE__)->Instance->CC0A.W) + (uint32_t)(__CHANNEL__ << 1)))

/**
 *******************************************************************************
 * @brief       Gets the TM Capture Compare Register-B value on run time
 * @param[in]   "__HANDLE__" : specifies the TM Handle.
 * @param[in]   "__CHANNEL__" : TM Channels to be configured.
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt.
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt.
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt.
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt.
 * @return      16-bit value of the capture/compare register.
 *******************************************************************************
 */
#define __DRV_TM_GET_COMPARE_B(__HANDLE__, __CHANNEL__) \
    (*(__IO uint32_t *)(&((__HANDLE__)->Instance->CC0B.W) + (uint32_t)(__CHANNEL__ << 1)))


/**
 *******************************************************************************
 * @brief       Sets the TM Counter Register value on run time.
 * @param[in]   "__HANDLE__" : specifies the TM Handle.
 * @param[in]   "__COUNTER__" : specifies the Counter register new value.
 * @return      None
 *******************************************************************************
 */
#define __DRV_TM_SET_COUNTER(__HANDLE__, __COUNTER__)   \
    ((__HANDLE__)->Instance->CNT.W = (uint32_t)(__COUNTER__))

/**
 *******************************************************************************
 * @brief       Gets the TM Counter Register value on run time.
 * @param[in]   "__HANDLE__" : specifies the TM Handle.
 * @return      8-bit or 16-bit value of the timer counter register (TMx_CNT).
 *******************************************************************************
 */
#define __DRV_TM_GET_COUNTER(__HANDLE__)    \
    ((__HANDLE__)->Instance->CNT.W)

/**
 *******************************************************************************
 * @brief       Sets the TM Autoreload Register value on runTMe without calling
 *              another time any Init function.
 * @param[in]   "__HANDLE__" : specifies the TM Handle.
 * @param[in]   "__AUTORELOAD__" : specifies the Counter register new value.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_SET_AUTORELOAD(__HANDLE__, __AUTORELOAD__) \
    (__HANDLE__)->Instance->ARR.W = (uint32_t)(__AUTORELOAD__);       \
    (__HANDLE__)->Init.TM_Period = (uint16_t)(__AUTORELOAD__)

/**
 *******************************************************************************
 * @brief       Gets the TM Autoreload Register value on run time.
 * @param[in]   "__HANDLE__" : specifies the TM Handle.
 * @return      8-bit or 16-bit value of the timer counter register (TMx_ARR).
 *******************************************************************************
 */
#define __DRV_TM_GET_AUTORELOAD(__HANDLE__) \
    ((__HANDLE__)->Instance->ARR.W)

/**
 *******************************************************************************
 * @brief       Sets the TM Clock Division value on run time without calling
 *              another initial function.
 * @param[in]   "__HANDLE__" : specifies the TM Handle.
 * @param[in]   "__CKD__" : specifies the clock division value.
 *              This parameter can be one of the following value:
 *  @arg\b      TM_INTERNALCLOCK_DIVDER_DIV1: tDTS=tCK_INT.
 *  @arg\b      TM_INTERNALCLOCK_DIVDER_DIV2: tDTS=2*tCK_INT.
 *  @arg\b      TM_INTERNALCLOCK_DIVDER_DIV4: tDTS=4*tCK_INT.
 *  @arg\b      TM_INTERNALCLOCK_DIVDER_DIV8: tDTS=8*tCK_INT.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_SET_CLOCKDIVISION(__HANDLE__, __CKD__) \
    (__HANDLE__)->Instance->CLK.W &= (uint32_t)(~(0x00003000U));    \
    ((__HANDLE__)->Instance->CLK.W |= (uint32_t)(__CKD__))
    

/**
 *******************************************************************************
 * @brief       Gets the TM Clock Division value on run time.
 * @param[in]   "__HANDLE__" : specifies the TM Handle.
 * @return      The clock division can be one of the following values:
 *  @arg\b      TM_INTERNALCLOCK_DIVDER_DIV1: tDTS=tCK_INT.
 *  @arg\b      TM_INTERNALCLOCK_DIVDER_DIV2: tDTS=2*tCK_INT.
 *  @arg\b      TM_INTERNALCLOCK_DIVDER_DIV4: tDTS=4*tCK_INT.
 *  @arg\b      TM_INTERNALCLOCK_DIVDER_DIV8: tDTS=8*tCK_INT.
 * @return      The state of FLAG (TM_INTERNALCLOCK_DIVDER_DIV1~8).
 *******************************************************************************
 */
#define __DRV_TM_GET_CLOCKDIVISION(__HANDLE__)  \
    ((__HANDLE__)->Instance->CLK.W & (uint32_t)(0x3000))
    

/**
 *******************************************************************************
 * @brief       Sets the TM Capture x input polarity on run time.
 * @param[in]   "__HANDLE__" : specifies the TM Handle.
 * @param[in]   "__CHANNEL__" : TM Channels to be configured.
 *  @arg\b      MID_TM_Channel0 : Capture/Compare 0 interrupt.
 *  @arg\b      MID_TM_Channel1 : Capture/Compare 1 interrupt.
 *  @arg\b      MID_TM_Channel2 : Capture/Compare 2 interrupt.
 *  @arg\b      MID_TM_Channel3 : Capture/Compare 3 interrupt.
 * @param[in]   "__POLARITY__" : Polarity for ICx source.
 *  @arg\b      TM_ICPOLARITY_DISABLE : Disable input catpure trigger.
 *  @arg\b      TM_ICPOLARITY_RISING : Accept external rising edge trigger.
 *  @arg\b      TM_ICPOLARITY_FALLING : Accept external falling edge trigger.
 *  @arg\b      TM_ICPOLARITY_DUALEDGE : Accept external dual edge trigger.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_SET_CAPTUREPOLARITY(__HANDLE__,__CHANNEL__,__POLARITY__)           \
    ((__HANDLE__)->Instance->ICCR.W &= ~(TM_ICCR_IC0_TRGS_mask_w << (__CHANNEL__)));  \
    ((__HANDLE__)->Instance->ICCR.W &= ~((__POLARITY__) << (__CHANNEL__)))


/**
 *******************************************************************************
 * @brief       Enables the specified TM PWM with Central-Align.
 * @param[in]   "__HANDLE__" : pointer to a TM_HandleTypeDef.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_ENABLE_PWM_CENTRAL(__HANDLE__)   \
    ((__HANDLE__)->Instance->PWM.W |= TM_PWM_PWM_MDS_center_aligned_w)

/**
 *******************************************************************************
 * @brief       Disables the specified TM PWM with Central-Align.
 * @param[in]   "__HANDLE__" : pointer to a TM_HandleTypeDef.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_DISABLE_PWM_CENTRAL(__HANDLE__)   \
    ((__HANDLE__)->Instance->PWM.W &= ~TM_PWM_PWM_MDS_mask_w)

/**
 *******************************************************************************
 * @brief       Reset TM timer depend on counter direction.
 * @param[in]   "__HANDLE__" : pointer to a TM_HandleTypeDef.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_RESET_TIMER(__HANDLE__) \
    ((__HANDLE__)->Instance->TRG.W |= (TM_TRG_RST2_SW_enable_w | TM_TRG_RST_SW_enable_w)); \
    ((__HANDLE__)->Instance->TRG.W &= ~(TM_TRG_RST2_SW_enable_w | TM_TRG_RST_SW_enable_w))


/**
 *******************************************************************************
 * @brief       Set OC0x & OC1x the output state when Preload trigger event happened.
 * @param[in]   "__HANDLE__" : pointer to a TM_HandleTypeDef.
 * @param[in]   "__PRELOADOUTPUT__" : specifies the TM_PreLoad_CH0 & TM_PreLoad_CH1.
 *  @arg\b      TM_PRELOADOC00_ENABLE : It will replace OC00 output control.
 *  @arg\b      TM_PRELOADOC01_ENABLE : It will replace OC01 output control.
 *  @arg\b      TM_PRELOADOC02_ENABLE : It will replace OC02 output control.
 *  @arg\b      TM_PRELOADOC10_ENABLE : It will replace OC10 output control.
 *  @arg\b      TM_PRELOADOC11_ENABLE : It will replace OC11 output control.
 *  @arg\b      TM_PRELOADOC12_ENABLE : It will replace OC12 output control.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_SET_PRELOAD_OUTPUT(__HANDLE__, __PRELOADOUTPUT__)  \
    ((__HANDLE__)->Instance->OCCR1.B[2] = (uint8_t) (__PRELOADOUTPUT__))


/**
 *******************************************************************************
 * @brief       Software output enable preload function.
 * @param[in]   "__HANDLE__" : pointer to a TM_HandleTypeDef.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_SOFTWARE_PRELOAD(__HANDLE__)   \
    ((__HANDLE__)->Instance->OCCR1.W |= TM_OCCR1_POE_SW_enable_w)


/**
 *******************************************************************************
 * @brief       Enable preload trigger source.
 * @param[in]   "__HANDLE__" : pointer to a TM_HandleTypeDef.
 * @param[in]   "__PRELOADTRGSOURCE__" : specifies the TM_PreloadTrgSource.
 *  @arg\b      TM_PRELOAD_3XOR : Preload trigger source from 3-line XOR.
 *  @arg\b      TM_PRELOAD_INTPB : It will replace OC01 output control.
 *  @arg\b      TM_PRELOAD_INTPD : It will replace OC02 output control.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_ENABLE_PRELOAD(__HANDLE__, __PRELOADTRGSOURCE__)         \
            ((__HANDLE__)->Instance->OCCR1.W |= (uint32_t) (__PRELOADTRGSOURCE__))


/**
 *******************************************************************************
 * @brief       Disable preload trigger source.
 * @param[in]   "__HANDLE__" : pointer to a TM_HandleTypeDef.
 * @param[in]   "__PRELOADTRGSOURCE__" : specifies the TM_PreloadTrgSource.
 *  @arg\b      TM_PRELOAD_3XOR : Preload trigger source from 3-line XOR.
 *  @arg\b      TM_PRELOAD_INTPB : It will replace OC01 output control.
 *  @arg\b      TM_PRELOAD_INTPD : It will replace OC02 output control.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_DISABLE_PRELOAD(__HANDLE__, __PRELOADTRGSOURCE__)      \
            ((__HANDLE__)->Instance->OCCR1.W &= (uint32_t) (~(__PRELOADTRGSOURCE__)))


/**
 *******************************************************************************
 * @brief       Set DMA update timing.
 * @param[in]   "__HANDLE__" : pointer to a TM_HandleTypeDef
 * @param[in]   "__UPLOADTIMING__" : specifies the TM_DMAUpdateTiming.
 *  @arg\b      TM_UPDATEG_EVENT_TIMING : Every TM main counter update 
 *              event will update OC/PWM's channel-X compare-B.
 *  @arg\b      TM_ITR_EVENT_TIMING : Both UEV (update event) and ITR input event 
 *              has occurred then trigger DMA to update.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_SET_DMA_UPLOAD_TIMING(__HANDLE__, __UPLOADTIMING__)            \
            ((__HANDLE__)->Instance->CCMDS.W &= ~(TM_CCMDS_DMA_OMDS_mask_w));   \
            ((__HANDLE__)->Instance->CCMDS.W |= (uint32_t) (__UPLOADTIMING__))


/**
 *******************************************************************************
 * @brief       Software control Timer TRGO state.
 * @param[in]   "__HANDLE__" : pointer to a TM_HandleTypeDef
 * @param[in]   "__TRGOSTATE__" : specifies the TM_SOFTWARE_TRGOSTATE.
 *  @arg\b      TM_SWTRGO_HIGH : Timer TRGO will output high state.
 *  @arg\b      TM_SWTRGO_LOW : Timer TRGO will output low state.
 * @return      None.
 *******************************************************************************
 */
#define __DRV_TM_SOFTWARE_TRGO(__HANDLE__, __TRGOSTATE__)                       \
            ((__HANDLE__)->Instance->TRG.W = ((__HANDLE__)->Instance->TRG.W & ~(TM_TRG_TRGO_SW_mask_w)) | (uint32_t) (__TRGOSTATE__))







/**
 * @name    Function announce
 * @brief   Time base initial/Deinitial`
 */
///@{
MID_StatusTypeDef MID_TM_Base_Init(TM_HandleTypeDef* mTM);
MID_StatusTypeDef MID_TM_Base_DeInit(TM_HandleTypeDef* mTM);
void MID_TM_Base_MspInit(TM_HandleTypeDef* mTM);
void MID_TM_Base_MspDeInit(TM_HandleTypeDef* mTM);
/* Blocking mode: Polling */
MID_StatusTypeDef MID_TM_Base_Start(TM_HandleTypeDef* mTM);
MID_StatusTypeDef MID_TM_Base_Stop(TM_HandleTypeDef* mTM);
/* Non-Blocking mode: Interrupt */
MID_StatusTypeDef MID_TM_Base_Start_IT(TM_HandleTypeDef* mTM);
MID_StatusTypeDef MID_TM_Base_Stop_IT(TM_HandleTypeDef* mTM);
/* Non-Blocking mode: DMA (no support)*/
///@}

/**
 * @name    Function announce
 * @brief   Timer 16bit Output Compare functions
 */
///@{
MID_StatusTypeDef MID_TM_OC_Init(TM_HandleTypeDef* mTM);
MID_StatusTypeDef MID_TM_OC_DeInit(TM_HandleTypeDef* mTM);
void MID_TM_OC_MspInit(TM_HandleTypeDef* mTM);
void MID_TM_OC_MspDeInit(TM_HandleTypeDef* mTM);
/* Blocking mode: Polling */
MID_StatusTypeDef MID_TM_OC_Start(TM_HandleTypeDef* mTM, uint32_t Channel);
MID_StatusTypeDef MID_TM_OC_Stop(TM_HandleTypeDef* mTM, uint32_t Channel);
/* Non-Blocking mode: Interrupt */
MID_StatusTypeDef MID_TM_OC_Start_IT(TM_HandleTypeDef* mTM, uint32_t Channel);
MID_StatusTypeDef MID_TM_OC_Stop_IT(TM_HandleTypeDef* mTM, uint32_t Channel);
/* Non-Blocking mode: DMA */
MID_StatusTypeDef MID_TM_OC_Start_DMA(TM_HandleTypeDef* mTM, uint32_t Channel, uint32_t* pData, uint16_t Length);
MID_StatusTypeDef MID_TM_OC_Stop_DMA(TM_HandleTypeDef* mTM, uint32_t Channel);
///@}

/**
 * @name    Function announce
 * @brief   Timer 8bitx2 Output Compare functions
 */
///@{
MID_StatusTypeDef MID_TM_8Bx2OC_Init(TM_HandleTypeDef* mTM);
MID_StatusTypeDef MID_TM_8Bx2OC_DeInit(TM_HandleTypeDef* mTM);
void MID_TM_8Bx2OC_MspInit(TM_HandleTypeDef* mTM);
void MID_TM_8Bx2OC_MspDeInit(TM_HandleTypeDef* mTM);
/* Blocking mode: Polling */
MID_StatusTypeDef MID_TM_8Bx2OC_Start(TM_HandleTypeDef* mTM, uint32_t Channel);
MID_StatusTypeDef MID_TM_8Bx2OC_Stop(TM_HandleTypeDef* mTM, uint32_t Channel);
/* Non-Blocking mode: Interrupt */
MID_StatusTypeDef MID_TM_8Bx2OC_Start_IT(TM_HandleTypeDef* mTM, uint32_t Channel);
MID_StatusTypeDef MID_TM_8Bx2OC_Stop_IT(TM_HandleTypeDef* mTM, uint32_t Channel);
/* Non-Blocking mode: DMA */
MID_StatusTypeDef MID_TM_8Bx2OC_Start_DMA(TM_HandleTypeDef* mTM, uint32_t Channel, uint32_t* pData, uint16_t Length);
MID_StatusTypeDef MID_TM_8Bx2OC_Stop_DMA(TM_HandleTypeDef* mTM, uint32_t Channel);
///@}

/**
 * @name    Function announce
 * @brief   Timer 16 bit PWM functions
 */
///@{
MID_StatusTypeDef MID_TM_PWM_Init(TM_HandleTypeDef* mTM);
MID_StatusTypeDef MID_TM_PWM_DeInit(TM_HandleTypeDef* mTM);
void MID_TM_PWM_MspInit(TM_HandleTypeDef* mTM);
void MID_TM_PWM_MspDeInit(TM_HandleTypeDef* mTM);
/* Blocking mode: Polling */
MID_StatusTypeDef MID_TM_PWM_Start(TM_HandleTypeDef* mTM, uint32_t Channel);
MID_StatusTypeDef MID_TM_PWM_Stop(TM_HandleTypeDef* mTM, uint32_t Channel);
/* Non-Blocking mode: Interrupt */
MID_StatusTypeDef MID_TM_PWM_Start_IT(TM_HandleTypeDef* mTM, uint32_t Channel);
MID_StatusTypeDef MID_TM_PWM_Stop_IT(TM_HandleTypeDef* mTM, uint32_t Channel);
/* Non-Blocking mode: DMA */
MID_StatusTypeDef MID_TM_PWM_Start_DMA(TM_HandleTypeDef* mTM, uint32_t Channel, uint32_t* pData, uint16_t Length);
MID_StatusTypeDef MID_TM_PWM_Stop_DMA(TM_HandleTypeDef* mTM, uint32_t Channel);
///@}


/**
 * @name    Function announce
 * @brief   Timer 8bitx2 bit PWM functions
 */
///@{
MID_StatusTypeDef MID_TM_8Bx2PWM_Init(TM_HandleTypeDef* mTM);
MID_StatusTypeDef MID_TM_8Bx2PWM_DeInit(TM_HandleTypeDef* mTM);
void MID_TM_8Bx2PWM_MspInit(TM_HandleTypeDef* mTM);
void MID_TM_8Bx2PWM_MspDeInit(TM_HandleTypeDef* mTM);
/* Blocking mode: Polling */
MID_StatusTypeDef MID_TM_8Bx2PWM_Start(TM_HandleTypeDef* mTM, uint32_t Channel);
MID_StatusTypeDef MID_TM_8Bx2PWM_Stop(TM_HandleTypeDef* mTM, uint32_t Channel);
/* Non-Blocking mode: Interrupt */
MID_StatusTypeDef MID_TM_8Bx2PWM_Start_IT(TM_HandleTypeDef* mTM, uint32_t Channel);
MID_StatusTypeDef MID_TM_8Bx2PWM_Stop_IT(TM_HandleTypeDef* mTM, uint32_t Channel);
/* Non-Blocking mode: DMA */
MID_StatusTypeDef MID_TM_8Bx2PWM_Start_DMA(TM_HandleTypeDef* mTM, uint32_t Channel, uint32_t* pData, uint16_t Length);
MID_StatusTypeDef MID_TM_8Bx2PWM_Stop_DMA(TM_HandleTypeDef* mTM, uint32_t Channel);
///@}


/**
 * @name    Function announce
 * @brief   Timer 16 bit PWM with Dead-Time functions
 */
///@{
MID_StatusTypeDef MID_TM_PWM_DTG_Init(TM_HandleTypeDef* mTM);
MID_StatusTypeDef MID_TM_PWM_DTG_DeInit(TM_HandleTypeDef* mTM);
void MID_TM_PWM_DTG_MspInit(TM_HandleTypeDef* mTM);
void MID_TM_PWM_DTG_MspDeInit(TM_HandleTypeDef* mTM);
/* Blocking mode: Polling */
MID_StatusTypeDef MID_TM_PWM_DTG_Start(TM_HandleTypeDef* mTM, uint32_t Channel);
MID_StatusTypeDef MID_TM_PWM_DTG_Stop(TM_HandleTypeDef* mTM, uint32_t Channel);
/* Non-Blocking mode: Interrupt */
MID_StatusTypeDef MID_TM_PWM_DTG_Start_IT(TM_HandleTypeDef* mTM, uint32_t Channel);
MID_StatusTypeDef MID_TM_PWM_DTG_Stop_IT(TM_HandleTypeDef* mTM, uint32_t Channel);
/* Non-Blocking mode: DMA */
MID_StatusTypeDef MID_TM_PWM_DTG_Start_DMA(TM_HandleTypeDef* mTM, uint32_t Channel, uint32_t* pData, uint16_t Length);
MID_StatusTypeDef MID_TM_PWM_DTG_Stop_DMA(TM_HandleTypeDef* mTM, uint32_t Channel);
///@}

/**
 * @name    Function announce
 * @brief   Timer 8bitx2 bit PWM with Dead-Time functions
 */
///@{
MID_StatusTypeDef MID_TM_8Bx2PWM_DTG_Init(TM_HandleTypeDef* mTM);
MID_StatusTypeDef MID_TM_8Bx2PWM_DTG_DeInit(TM_HandleTypeDef* mTM);
void MID_TM_8Bx2PWM_DTG_MspInit(TM_HandleTypeDef* mTM);
void MID_TM_8Bx2PWM_DTG_MspDeInit(TM_HandleTypeDef* mTM);
/* Blocking mode: Polling */
MID_StatusTypeDef MID_TM_8Bx2PWM_DTG_Start(TM_HandleTypeDef* mTM, uint32_t Channel);
MID_StatusTypeDef MID_TM_8Bx2PWM_DTG_Stop(TM_HandleTypeDef* mTM, uint32_t Channel);
/* Non-Blocking mode: Interrupt */
MID_StatusTypeDef MID_TM_8Bx2PWM_DTG_Start_IT(TM_HandleTypeDef* mTM, uint32_t Channel);
MID_StatusTypeDef MID_TM_8Bx2PWM_DTG_Stop_IT(TM_HandleTypeDef* mTM, uint32_t Channel);
/* Non-Blocking mode: DMA */
MID_StatusTypeDef MID_TM_8Bx2PWM_DTG_Start_DMA(TM_HandleTypeDef* mTM, uint32_t Channel, uint32_t* pData, uint16_t Length);
MID_StatusTypeDef MID_TM_8Bx2PWM_DTG_Stop_DMA(TM_HandleTypeDef* mTM, uint32_t Channel);
///@}


/**
 * @name    Function announce
 * @brief   Timer Input Capture functions
 */
///@{
MID_StatusTypeDef MID_TM_IC_Init(TM_HandleTypeDef* mTM);
MID_StatusTypeDef MID_TM_IC_DeInit(TM_HandleTypeDef* mTM);
void MID_TM_IC_MspInit(TM_HandleTypeDef* mTM);
void MID_TM_IC_MspDeInit(TM_HandleTypeDef* mTM);
/* Blocking mode: Polling */
MID_StatusTypeDef MID_TM_IC_Start(TM_HandleTypeDef* mTM, uint32_t Channel);
MID_StatusTypeDef MID_TM_IC_Stop(TM_HandleTypeDef* mTM, uint32_t Channel);
/* Non-Blocking mode: Interrupt */
MID_StatusTypeDef MID_TM_IC_Start_IT(TM_HandleTypeDef* mTM, uint32_t Channel);
MID_StatusTypeDef MID_TM_IC_Stop_IT(TM_HandleTypeDef* mTM, uint32_t Channel);
/* Non-Blocking mode: DMA */
MID_StatusTypeDef MID_TM_IC_Start_DMA(TM_HandleTypeDef* mTM, uint32_t Channel, uint32_t* pData, uint16_t Length);
MID_StatusTypeDef MID_TM_IC_Stop_DMA(TM_HandleTypeDef* mTM, uint32_t Channel);
///@}


/**
 * @name    Function announce
 * @brief   Timer One-plus functions (for MG32F02A128/U128/A064/U064)
 */
///@{
#if defined(MG32_3RD)
MID_StatusTypeDef MID_TM_OnePulse_Init(TM_HandleTypeDef *mTM, TM_RCNTConfigTypeDef* sRCNTConfig);
MID_StatusTypeDef MID_TM_OnePulse_DeInit(TM_HandleTypeDef* mTM);
void MID_TM_OnePulse_MspInit(TM_HandleTypeDef *mTM);
void MID_TM_OnePulse_MspDeInit(TM_HandleTypeDef* mTM);
/* Blocking mode: Polling */
MID_StatusTypeDef MID_TM_OnePulse_Start(TM_HandleTypeDef* mTMX);
MID_StatusTypeDef MID_TM_OnePulse_Stop(TM_HandleTypeDef* mTM);
/* Non-Blocking mode: Interrupt */
MID_StatusTypeDef MID_TM_OnePulse_Start_IT(TM_HandleTypeDef* mTM);
MID_StatusTypeDef MID_TM_OnePulse_Stop_IT(TM_HandleTypeDef* mTM);
#endif
///@}



/**
 * @name    Function announce
 * @brief   Timer Encoder functions
 */
///@{
MID_StatusTypeDef MID_TM_Encoder_Init(TM_HandleTypeDef* mTM);
MID_StatusTypeDef MID_TM_Encoder_DeInit(TM_HandleTypeDef* mTM);
void MID_TM_Encoder_MspInit(TM_HandleTypeDef* mTM);
void MID_TM_Encoder_MspDeInit(TM_HandleTypeDef* mTM);
/* Blocking mode: Polling */
MID_StatusTypeDef MID_TM_Encoder_Start(TM_HandleTypeDef* mTM,  TM_Encoder_InitTypeDef* sConfig);
MID_StatusTypeDef MID_TM_Encoder_Stop(TM_HandleTypeDef* mTM);
/* Non-Blocking mode: Interrupt */
MID_StatusTypeDef MID_TM_Encoder_Start_IT(TM_HandleTypeDef* mTM, TM_Encoder_InitTypeDef* sConfig, uint32_t ITSrc);
MID_StatusTypeDef MID_TM_Encoder_Stop_IT(TM_HandleTypeDef* mTM, uint32_t ITSrc);
///@}


/**
 * @name    Function announce
 * @brief   addtogroup TM_Exported_Functions_Group7
 */
///@{
MID_TM_StateTypeDef MID_TM_Base_GetState(TM_HandleTypeDef* mTM);
MID_TM_StateTypeDef MID_TM_OC_GetState(TM_HandleTypeDef* mTM);
MID_TM_StateTypeDef MID_TM_PWM_GetState(TM_HandleTypeDef* mTM);
MID_TM_StateTypeDef MID_TM_IC_GetState(TM_HandleTypeDef* mTM);
MID_TM_StateTypeDef MID_TM_Encoder_GetState(TM_HandleTypeDef* mTM);
#if defined(MG32_3RD)
MID_TM_StateTypeDef MID_TM_OnePulse_GetState(TM_HandleTypeDef* mTM);
#endif
///@}


/**
 * @name    Function announce
 * @brief   addtogroup TM_Exported_Functions_Group8
 */
///@{
void MID_TM_OC_Struct_Init(TM_OC_InitTypeDef* sConfig);
MID_StatusTypeDef MID_TM_OC_ConfigChannel(TM_HandleTypeDef* mTM, TM_OC_InitTypeDef* sConfig, uint32_t Channel);
MID_StatusTypeDef MID_TM_IC_ConfigChannel(TM_HandleTypeDef* mTM, TM_IC_InitTypeDef* sConfig, uint32_t Channel);
MID_StatusTypeDef MID_TM_PWM_ConfigChannel(TM_HandleTypeDef* mTM, TM_OC_InitTypeDef* sConfig, uint32_t Channel);
MID_StatusTypeDef MID_TM_GenerateEvent(TM_HandleTypeDef* mTM, uint32_t EventSource);
MID_StatusTypeDef MID_TM_ConfigClockSource(TM_HandleTypeDef* mTM, TM_ClockConfigTypeDef * sClockSourceConfig);
MID_StatusTypeDef MID_TM_MasterConfigSynchronization(TM_HandleTypeDef* mTM, TM_MasterConfigTypeDef * sMasterConfig);
MID_StatusTypeDef MID_TM_ConfigBreakDeadTime(TM_HandleTypeDef* mTM, TM_BreakDeadTimeConfigTypeDef *sBreakDeadTimeConfig);
MID_StatusTypeDef MID_TM_SlaveConfigSynchronization(TM_HandleTypeDef* mTM, TM_SlaveConfigTypeDef* sSlaveConfig);
MID_StatusTypeDef MID_TM_SlaveConfigSynchronization_IT(TM_HandleTypeDef* mTM, TM_SlaveConfigTypeDef* sSlaveConfig);
MID_StatusTypeDef MID_TM_ClockOut(TM_HandleTypeDef* mTM, TM_CKOConfigTypeDef* sClockConfig);
uint32_t MID_TM_ReadCapturedValue(TM_HandleTypeDef *mTM, uint32_t Channel);
///@}

/**
 * @name    Function announce
 * @brief   Callback in non blocking modes (Interrupt and DMA)
 */
///@{
void TM_DMAError(DMA_HandleTypeDef* hDMA);
void TM_DMADelayPulseCplt(DMA_HandleTypeDef* hDMA);
void TM_DMACaptureCplt(DMA_HandleTypeDef* hDMA);
///@}


/**
 * @name    Function announce
 * @brief   Callback in non blocking modes (Interrupt and DMA)
 */
///@{
void MID_TM_IRQHandler(TM_HandleTypeDef* mTM);
void MID_TM_PeriodElapsedCallback(TM_HandleTypeDef* mTM);
void MID_TM_OC_DelayElapsedCallback(TM_HandleTypeDef* mTM);
void MID_TM_IC_CaptureCallback(TM_HandleTypeDef* mTM);
void MID_TM_PWM_PulseFinishedCallback(TM_HandleTypeDef* mTM);
void MID_TM_TriggerCallback(TM_HandleTypeDef* mTM);
void MID_TM_ErrorCallback(TM_HandleTypeDef* mTM);
void MID_TM_BreakCallback(TM_HandleTypeDef* mTM);
void MID_TM_QEI_DIRCHANGECallback(TM_HandleTypeDef* mTM);
void MID_TM_QEI_INDEXCallback(TM_HandleTypeDef* mTM);
void MID_TM_QEI_ErrorCallback(TM_HandleTypeDef* mTM);
void MID_TM_OnePulseCallback(TM_HandleTypeDef* mTM);
///@}


/**
 * @name    Function announce
 * @brief   addtogroup TM_Private_Functions
 */
///@{
void TM_Base_SetConfig(TM_Struct* TMx, TM_Base_InitTypeDef* Structure);
void TM_CCxChannelCmd(TM_Struct* TMx, uint32_t Channel, uint32_t ChannelMode);
void MID_TM_OC_SetDeadTimeDivider(TM_HandleTypeDef* mTM,  uint32_t DeadTimeDivider);
void MID_TM_OC_SetDeadTime(TM_HandleTypeDef* mTM,  uint32_t DeadTime);
///@}

#endif

