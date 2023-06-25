/**
 ******************************************************************************
 *
 * @file        MG32x02z_CMP_MID.h
 *
 * @brief       This file provides firmware functions to manage the following 
 *              functionalities of the CMP peripheral:
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.03
 * @date        2021/04/07
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

#include "MG32x02z.h"
#if defined(MG32_1ST) || defined(MG32_2ND) || defined(MG32_3RD)

#ifndef _MG32x02z_CMP_MID_H

/*!< _MG32x02z_CMP_DRV_H */ 
#define _MG32x02z_CMP_MID_H

#include "MG32x02z_Common_MID.h"
#include "MG32x02z_CMP.h"
#include "MG32x02z__ExtraStruct.h"

/**
 * @name    CMP_InvertingInput
 *          CMP InvertingInput
 */ 
//!@{
#define CMP_INVERTINGINPUT_IVREF                CMP_CR0_AC0_NMUX_ivref_w        /*!< CMP0 Analog input negative channel select internal Vref from R-ladder. */
#define CMP_INVERTINGINPUT_IO0                  CMP_CR0_AC0_NMUX_cmp0_i0_w      /*!< CMP0 Analog input negative channel select CMP0(PA8)/CMP1(PA10). */
#define CMP_INVERTINGINPUT_IO1                  CMP_CR0_AC0_NMUX_cmp0_i1_w      /*!< CMP0 Analog input negative channel select CMP0(PA9)/CMP1(PA11). */
#define CMP_INVERTINGINPUT_COMMONIO0            CMP_CR0_AC0_NMUX_cmp_c0_w       /*!< CMP0 Analog input negative channel select common pin PB0. */
#define CMP_INVERTINGINPUT_COMMONIO1            CMP_CR0_AC0_NMUX_cmp_c1_w       /*!< CMP0 Analog input negative channel select common pin PB1. */
#define CMP_INVERTINGINPUT_LDO                  CMP_CR0_AC0_NMUX_ldo_core_w     /*!< CMP0 Analog input negative channel select main LDO (VR0). */
//!@}

/**
 * @name    CMP_NonInvertingInput
 *          CMP NonInvertingInput
 */ 
//!@{
#define CMP_NONINVERTINGINPUT_IVREF             CMP_CR0_AC0_PMUX_ivref_w        /*!< CMP0 Analog input positive channel select internal Vref from R-ladder. */
#define CMP_NONINVERTINGINPUT_IO0               CMP_CR0_AC0_PMUX_cmp0_i0_w      /*!< CMP0 Analog input positive channel select CMP0(PA8)/CMP1(PA10). */
#define CMP_NONINVERTINGINPUT_IO1               CMP_CR0_AC0_PMUX_cmp0_i1_w      /*!< CMP0 Analog input positive channel select CMP0(PA9)/CMP1(PA11). */
#define CMP_NONINVERTINGINPUT_COMMONIO0         CMP_CR0_AC0_PMUX_cmp_c0_w       /*!< CMP0 Analog input positive channel select common pin PB0. */
#define CMP_NONINVERTINGINPUT_COMMONIO1         CMP_CR0_AC0_PMUX_cmp_c1_w       /*!< CMP0 Analog input positive channel select common pin PB1. */
#define CMP_NONINVERTINGINPUT_LDO               CMP_CR0_AC0_PMUX_ldo_core_w     /*!< CMP0 Analog input positive channel select main LDO (VR0). */
//!@}

/**
 * @name    CMP_ComparatorPolarity
 *          CMP Comparator Polarity
 */ 
//!@{
#define CMP_POSITIVE_POLARITY                   (0x00000000U)                   /*!< CMP Positive polarity output control */
#define CMP_NEGATIVE_POLARITY                   CMP_CR0_AC0_INV_negative_w      /*!< CMP Negative polarity output control */
//!@}

/**
 * @name    CMP_OutputPolarity
 *          CMP OutputPolarity
 */ 
//!@{
#define CMP_OUTPUTPOL_NONINVERTED               (0x00000000U)                   /*!< CMP output on GPIO isn't inverted */
#define CMP_OUTPUTPOL_INVERTED                  CMP_CR0_AC0_PINV_enable_w       /*!< CMP output on GPIO is inverted  */
//!@}

/**
 * @name    CMP_Hysteresis
 *          CMP Hysteresis
 */ 
//!@{
#define CMP_HYSTERESIS_NONE                     (0x00000000U)                   /*!< No hysteresis */
#define CMP_HYSTERESIS_LOW                      CMP_CR0_AC0_HYS_lvl1_w          /*!< Hysteresis level low */
//!@}


/**
 * @name    CMP_Mode
 *          CMP Mode
 */ 
/* Please refer to the electrical characteristics in the device datasheet for
   the power consumption values */
//!@{
#define CMP_MODE_HIGHSPEED                      (0x00000000U)                   /*!< High Speed */
#define CMP_MODE_LOWPOWER                       CMP_CR0_AC0_RES_10us_w          /*!< Low power mode */
//!@}

/**
 * @name    CMP_TriggerMode
 *          CMP TriggerMode
 */ 
//!@{
#define CMP_TRIGGERMODE_NONE                    (0x00000000U)                                           /*!< No External Interrupt trigger detection */
#define CMP_TRIGGERMODE_IT_RISING               (CMP_INT_AC0_RIE_enable_w)                              /*!< External Interrupt Mode with Rising edge trigger detection */
#define CMP_TRIGGERMODE_IT_FALLING              (CMP_INT_AC0_FIE_enable_w)                              /*!< External Interrupt Mode with Falling edge trigger detection */
#define CMP_TRIGGERMODE_IT_RISING_FALLING       (CMP_INT_AC0_RIE_enable_w | CMP_INT_AC0_FIE_enable_w)   /*!< External Interrupt Mode with Rising/Falling edge trigger detection */
#define CMP_TRIGGERMODE_EVENT_RISING            (CMP_STA_AC0_RF_happened_w)                             /*!< Event Mode with Rising edge trigger detection */
#define CMP_TRIGGERMODE_EVENT_FALLING           (CMP_STA_AC0_FF_happened_w)                             /*!< Event Mode with Falling edge trigger detection */
#define CMP_TRIGGERMODE_EVENT_RISING_FALLING    (CMP_STA_AC0_RF_happened_w | CMP_STA_AC0_FF_happened_w) /*!< Event Mode with Rising/Falling edge trigger detection */
//!@}

/**
 * @name    CMP_OutputSynchronizeFilter
 *          CMP Output Synchronize Filter
 */ 
//!@{
#define CMP_SYNCHRONIZE_BYPASS                  CMP_CR0_AC0_FSEL_bypass_w       /*!< Bypass */
#define CMP_SYNCHRONIZE_CMPCLOCK                CMP_CR0_AC0_FSEL_cmp_ck_w       /*!< Synchronize Filter clock from CMP_CK */
#define CMP_SYNCHRONIZE_TM00TRGO                CMP_CR0_AC0_FSEL_tm00_trgo_w    /*!< Synchronize Filter clock from TM00_TRGO */
#define CMP_SYNCHRONIZE_TM01TRGO                CMP_CR0_AC0_FSEL_tm01_trgo_w    /*!< Synchronize Filter clock from TM01_TRGO */
//!@}


/**
 * @name    CMP_SynchronizeFilterDivider
 *          CMP Synchronize Filter clock Divider
 */ 
//!@{
#define CMP_SYNCHRONIZE_DIV1                    CMP_CR0_AC0_FDIV_div1_w         /*!< divided by 1 */
#define CMP_SYNCHRONIZE_DIV2                    CMP_CR0_AC0_FDIV_div2_w         /*!< divided by 2 */
#define CMP_SYNCHRONIZE_DIV4                    CMP_CR0_AC0_FDIV_div4_w         /*!< divided by 4 */
#define CMP_SYNCHRONIZE_DIV8                    CMP_CR0_AC0_FDIV_div8_w         /*!< divided by 8 */
//!@}


/** 
 * @struct  CMP_InitStructDef
 * @brief   Structure definition of CMP initialization and regular group 
 */        
typedef struct __attribute__((packed))
{ 
    uint32_t InvertingInput;        /*!< Selects the inverting input of the comparator.
                                         This parameter can be a value of reference CMP_InvertingInput. */
        
    uint32_t NonInvertingInput;     /*!< Selects the non inverting input of the comparator.
                                         This parameter can be a value of reference CMP_NonInvertingInput. */
        
    uint32_t ComparatorPol;         /*!< Selects the polarity of the comparator.
                                         This parameter can be a value of reference CMP_ComparatorPolarity. */
        
    uint32_t OutputPol;             /*!< Selects the output polarity of the comparator. (Pin)
                                         This parameter can be a value of reference CMP_OutputPolarity. */
        
#if defined(MG32_2ND) || defined(MG32_3RD)
    uint32_t Hysteresis;            /*!< Selects the hysteresis voltage of the comparator. 
                                         This parameter can be a value of reference CMP_Hysteresis. */
#endif
                                             
    uint32_t Mode;                  /*!< Selects the operating comsumption mode of the comparator to adjust the speed/consumption.
                                         This parameter can be a value of reference CMP_Mode. */
    
    uint32_t TriggerMode;           /*!< Selects the trigger mode of the comparator (interrupt mode).
                                         This parameter can be a value of reference CMP_TriggerMode. */
                                        
    uint32_t OutputSync;            /*!< Analog comparator output signal select with synchronized filter.
                                         When selects the signal with 3-clock filter except Bypass selection, the comparator output will filter 3 clocks 
                                         by the filter clock which is divided by the CMP_ACX_FDIV from the following selection clock source.
                                         This parameter can be a value of reference CMP_OutputSynchronizeFilter. */
    
    uint32_t SyncFilterDIV;         /*!< Analog comparator output synchronized filter divider.
                                         This parameter can be a value of reference CMP_SynchronizeFilterDivider. */
                                           

}CMP_InitStructDef;


/** 
 * @struct  CMP_IntVrefStructDef
 * @brief   CMP internal VREF  
 */        
typedef struct __attribute__((packed))
{ 
    uint32_t IntVREF0_Level;        /*!< Internal VREF0 (R-ladder) selection apply for Comparator-0.
                                         This parameter can be a value of 0~63  (0:Disable). */
                                        
    uint32_t IntVREF1_Level;        /*!< Internal VREF0 (R-ladder) selection apply for Comparator-1~3.
                                         This parameter can be a value of 0~63  (0:Disable). */
                                        
} CMP_IntVrefStructDef;

/** 
 * @enum        MID_CMP_StateTypeDef
 * @brief       MID CMP State definition 
 */        
typedef enum 
{
    MID_CMP_STATE_RESET             = (0x00000000U),   /*!< CMP not yet initialized or disabled.             */
    MID_CMP_STATE_READY             = (0x00000001U),   /*!< CMP initialized and ready for use.               */
    MID_CMP_STATE_READY_LOCKED      = (0x00000011U),   /*!< CMP initialized but the configuration is locked. */
    MID_CMP_STATE_BUSY              = (0x00000002U),   /*!< CMP is running.                                  */
    MID_CMP_STATE_BUSY_LOCKED       = (0x00000012U)    /*!< CMP is running and the configuration is locked.  */
}MID_CMP_StateTypeDef;


/** 
 * @struct  CMP_HandleTypeDef
 * @brief   CMP handle Structure definition  
 */        
typedef struct __attribute__((packed))
{
    CMPAC_Struct            *Instance;      /*!< Register base address */
                        
    CMP_InitStructDef       Init;           /*!< CMP required parameters */
        
    CMP_IntVrefStructDef    IntVref;        /*!< Internal VREF required parameters */
                                            
    MID_LockTypeDef         Lock;           /*!< CMP locking object */
                        
    __IO uint32_t           State;          /*!< CMP communication state 
                                                This parameter can be a value of reference MID_CMP_StateTypeDef  */ 
                    
}CMP_HandleTypeDef;



/**
 * @name    CMP_Flag_definition
 *          CMP Flag Definition
 */ 
//!@{
#define CMP_CMP0_FLAG_RISING        CMP_STA_AC0_RF_happened_w                       /*!< CMP0 flag of Rising event flag */
#define CMP_CMP0_FLAG_FALLING       CMP_STA_AC0_FF_happened_w                       /*!< CMP0 flag of Falling event flag */
#define CMP_CMP0_FLAG_ALL			(CMP_CMP0_FLAG_RISING | CMP_CMP0_FLAG_FALLING)  /*!< CMP0 happened rising and falling event */
#define CMP_CMP1_FLAG_RISING        CMP_STA_AC1_RF_happened_w                       /*!< CMP1 flag of Rising event flag */
#define CMP_CMP1_FLAG_FALLING       CMP_STA_AC1_FF_happened_w                       /*!< CMP1 flag of Falling event flag */
#define CMP_CMP1_FLAG_ALL			(CMP_CMP1_FLAG_RISING | CMP_CMP1_FLAG_FALLING)  /*!< CMP1 happened rising and falling event */
#if defined(MG32_1ST)
    #define CMP_CMP2_FLAG_RISING        CMP_STA_AC2_RF_happened_w                       /*!< CMP2 flag of Rising event flag */
    #define CMP_CMP2_FLAG_FALLING       CMP_STA_AC2_FF_happened_w                       /*!< CMP2 flag of Falling event flag */
    #define CMP_CMP2_FLAG_ALL			(CMP_CMP2_FLAG_RISING | CMP_CMP2_FLAG_FALLING)  /*!< CMP2 happened rising and falling event */
    #define CMP_CMP3_FLAG_RISING        CMP_STA_AC3_RF_happened_w                       /*!< CMP3 flag of Rising event flag */
    #define CMP_CMP3_FLAG_FALLING       CMP_STA_AC3_FF_happened_w                       /*!< CMP3 flag of Falling event flag */
    #define CMP_CMP3_FLAG_ALL			(CMP_CMP3_FLAG_RISING | CMP_CMP3_FLAG_FALLING)  /*!< CMP3 happened rising and falling event */
#endif
//!@}

/**
 * @name    CMP_OutputLevel
 *          CMP Output Level
 */ 
//!@{
#define CMP_OUTPUTLEVEL_LOW                     (0x00000000U)                   /*!< If the comparator polarity is CMP_POSITIVE_POLARITY:
                                                                                     - Comparator output is low when the non-inverting input is at a lower
                                                                                       voltage than the inverting input
                                                                                 */
#define CMP_OUTPUTLEVEL_HIGH                    CMP_STA_AC0_S_mask_w            /*!< If the comparator polarity is CMP_POSITIVE_POLARITY:
                                                                                     - Comparator output is low when the non-inverting input is at a higher
                                                                                       voltage than the inverting input
                                                                                 */
//!@}



/**
 *******************************************************************************
 * @brief       Reset CMP handle state
 * @param[in]   "__HANDLE__ : pointer to a CMP handle.
 * @return      None
 *******************************************************************************
 */
#define __DRV_CMP_RESET_HANDLE_STATE(__HANDLE__)                                \
  ((__HANDLE__)->State = MID_CMP_STATE_RESET)


/**
 *******************************************************************************
 * @brief       Enable the specified comparator.
 * @param[in]   "__HANDLE__ : pointer to a CMP_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
#define __DRV_CMP_ENABLE(__HANDLE__)                                            \
    ((__HANDLE__)->Instance->CR.W |= CMP_CR0_AC0_EN_enable_w)                   \

/**
 *******************************************************************************
 * @brief       Disable the specified comparator.
 * @param[in]   "__HANDLE__ : pointer to a CMP_HandleTypeDef
 * @return      None
 *******************************************************************************
 */
#define __DRV_CMP_DISABLE(__HANDLE__)                                           \
    ((__HANDLE__)->Instance->CR.W &= ~CMP_CR0_AC0_EN_enable_w)                  \


/**
 *******************************************************************************
 * @brief       Enables the specified CMP All interrupt.
 * @return      None
 * @note 
 * @par         Example
 * @code
    __DRV_CMP_ENABLE_ITEA();
 * @endcode
 *******************************************************************************
 */
#define __DRV_CMP_ENABLE_ITEA()    (CMP->INT.W |= CMP_INT_IEA_enable_w)

/**
 *******************************************************************************
 * @brief       Disables the specified CMP All interrupt.
 * @return      None
 * @note 
 * @par         Example
 * @code
    __DRV_CMP_ENABLE_ITEA();
 * @endcode
 *******************************************************************************
 */
#define __DRV_CMP_DISABLE_ITEA()    (CMP->INT.W &= ~CMP_INT_IEA_enable_w)

/**
 *******************************************************************************
 * @brief       Clear the CMP interrupt pending bits.
 * @param[in]   "__FLAG__" : specifies the CMP interrupt flag to clear.
 *  @arg\b      CMP_CMP0_FLAG_RISING : CMP0 detect riging edge event.     
 *  @arg\b      CMP_CMP0_FLAG_FALLING : CMP0 detect falling edge event.     
 *  @arg\b      CMP_CMP0_FLAG_ALL : CMP0 detect riging and falling edge event.       
 *  @arg\b      CMP_CMP1_FLAG_RISING : CMP1 detect riging edge event.     
 *  @arg\b      CMP_CMP1_FLAG_FALLING : CMP1 detect falling edge event.     
 *  @arg\b      CMP_CMP1_FLAG_ALL : CMP1 detect riging and falling edge event.       
 *  @arg\b      CMP_CMP2_FLAG_RISING : CMP2 detect riging edge event.     
 *  @arg\b      CMP_CMP2_FLAG_FALLING : CMP2 detect falling edge event.     
 *  @arg\b      CMP_CMP2_FLAG_ALL : CMP2 detect riging and falling edge event.       
 *  @arg\b      CMP_CMP3_FLAG_RISING : CMP3 detect riging edge event.     
 *  @arg\b      CMP_CMP3_FLAG_FALLING : CMP3 detect falling edge event.     
 *  @arg\b      CMP_CMP3_FLAG_ALL : CMP3 detect riging and falling edge event.       
 * @return      None
 * @note 
 * @par         Example
 * @code
    __DRV_CMP_CLEAR_FLAG(CMP_CMP0_FLAG_RISING);
 * @endcode
 *******************************************************************************
 */
#define __DRV_CMP_CLEAR_FLAG(__FLAG__)                                          \
    ((CMP)->STA.W = (__FLAG__))

/**
 *******************************************************************************
 * @brief       Get the CMP interrupt pending bits.
 * @param[in]   "__FLAG__ : specifies the CMP interrupt flag to clear.
 *  @arg\b      CMP_CMP0_FLAG_RISING : CMP0 detect riging edge event.     
 *  @arg\b      CMP_CMP0_FLAG_FALLING : CMP0 detect falling edge event.     
 *  @arg\b      CMP_CMP0_FLAG_ALL : CMP0 detect riging and falling edge event.       
 *  @arg\b      CMP_CMP1_FLAG_RISING : CMP1 detect riging edge event.     
 *  @arg\b      CMP_CMP1_FLAG_FALLING : CMP1 detect falling edge event.     
 *  @arg\b      CMP_CMP1_FLAG_ALL : CMP1 detect riging and falling edge event.       
 *  @arg\b      CMP_CMP2_FLAG_RISING : CMP2 detect riging edge event.     
 *  @arg\b      CMP_CMP2_FLAG_FALLING : CMP2 detect falling edge event.     
 *  @arg\b      CMP_CMP2_FLAG_ALL : CMP2 detect riging and falling edge event.       
 *  @arg\b      CMP_CMP3_FLAG_RISING : CMP3 detect riging edge event.     
 *  @arg\b      CMP_CMP3_FLAG_FALLING : CMP3 detect falling edge event.     
 *  @arg\b      CMP_CMP3_FLAG_ALL : CMP3 detect riging and falling edge event.       
 * @return      The state of FLAG (SET or RESET).
 * @note 
 * @par         Example
 * @code
    ReturnState = __DRV_CMP_GET_FLAG(CMP_CMP0_FLAG_ALL);
 * @endcode
 *******************************************************************************
 */
#define __DRV_CMP_GET_FLAG(__FLAG__)                                            \
    (((CMP)->STA.W & (__FLAG__)) == (__FLAG__))

/**
 *******************************************************************************
 * @brief       Select the CMP Inverting Input pin bits.
 * @param[in]   "__HANDLE__ : pointer to a CMP handle.
 * @param[in]   "__INVPIN__" : specifies the CMP interrupt flag to clear.
 *  @arg\b      CMP_INVERTINGINPUT_IVREF : input channel select internal Vref from R-ladder. 
 *  @arg\b      CMP_INVERTINGINPUT_IO0 : input channel select CMP0(PA8)/CMP1(PA10). 
 *  @arg\b      CMP_INVERTINGINPUT_IO1 : input channel select CMP0(PA8)/CMP1(PA10).       
 *  @arg\b      CMP_INVERTINGINPUT_COMMONIO0 : input channel select PB0.   
 *  @arg\b      CMP_INVERTINGINPUT_COMMONIO1 : input channel select PB1.
 *  @arg\b      CMP_INVERTINGINPUT_LDO : input channel select  main LDO (VR0).     
 * @return      None
 * @note 
 * @par         Example
 * @code
    __DRV_CMP_NMUX_PIN(mCMP, CMP_INVERTINGINPUT_IO0);
 * @endcode
 *******************************************************************************
 */
#define __DRV_CMP_NMUX_PIN(__HANDLE__,__INVPIN__)                               \
    ((__HANDLE__)->Instance->CR.W = ((__HANDLE__)->Instance->CR.W & ~(CMP_CR0_AC0_NMUX_mask_w)) | \
    								(__INVPIN__))


/**
 *******************************************************************************
 * @brief       Select CMP Non-Inverting Input pin.
 * @param[in]   "__HANDLE__ : pointer to a CMP handle.
 * @param[in]   "__NONINVPIN__" : specifies the CMP interrupt flag to clear.
 *  @arg\b      CMP_NONINVERTINGINPUT_IVREF : input channel select internal Vref from R-ladder. 
 *  @arg\b      CMP_NONINVERTINGINPUT_IO0 : input channel select CMP0(PA8)/CMP1(PA10). 
 *  @arg\b      CMP_NONINVERTINGINPUT_IO1 : input channel select CMP0(PA8)/CMP1(PA10).       
 *  @arg\b      CMP_NONINVERTINGINPUT_COMMONIO0 : input channel select PB0.   
 *  @arg\b      CMP_NONINVERTINGINPUT_COMMONIO1 : input channel select PB1.
 *  @arg\b      CMP_NONINVERTINGINPUT_LDO : input channel select  main LDO (VR0).     
 * @return      None
 * @note 
 * @par         Example
 * @code
    __DRV_CMP_PMUX_PIN(mCMP, CMP_NONINVERTINGINPUT_COMMONIO0);
 * @endcode
 *******************************************************************************
 */
#define __DRV_CMP_PMUX_PIN(__HANDLE__,__NONINVPIN__)                            \
    ((__HANDLE__)->Instance->CR.W = ((__HANDLE__)->Instance->CR.W & ~(CMP_CR0_AC0_PMUX_mask_w)) | \
    								(__NONINVPIN__))



/**
 * @name    Function announce
 * @brief   CMP base initial/Deinitial	
 */ 
///@{
/* Initialization and de-initialization functions  ****************************/
MID_StatusTypeDef MID_CMP_Init(CMP_HandleTypeDef* mCMP);
MID_StatusTypeDef MID_CMP_DeInit(CMP_HandleTypeDef* mCMP);
void MID_CMP_MspInit(CMP_HandleTypeDef* mCMP);
void MID_CMP_MspDeInit(CMP_HandleTypeDef* mCMP);

/* IO operation functions *****************************************************/
MID_StatusTypeDef MID_CMP_Start(CMP_HandleTypeDef* mCMP);
MID_StatusTypeDef MID_CMP_Stop(CMP_HandleTypeDef* mCMP);
MID_StatusTypeDef MID_CMP_Start_IT(CMP_HandleTypeDef* mCMP);
MID_StatusTypeDef MID_CMP_Stop_IT(CMP_HandleTypeDef* mCMP);
void MID_CMP_IRQHandler(CMP_HandleTypeDef *hcomp);
///@}


/**
 * @name    Function announce
 * @brief   addtogroup CMP_Exported_Functions_Group
 */ 
///@{
uint32_t MID_CMP_GetOutputLevel(CMP_HandleTypeDef *hcomp);
/* Callback in Interrupt mode */
void MID_CMP_TriggerCallbackAC0(CMP_HandleTypeDef* mCMP);
void MID_CMP_TriggerCallbackAC1(CMP_HandleTypeDef* mCMP);
#if defined(MG32_1ST)
void MID_CMP_TriggerCallbackAC2(CMP_HandleTypeDef* mCMP);
void MID_CMP_TriggerCallbackAC3(CMP_HandleTypeDef* mCMP);
#endif
uint32_t MID_CMP_GetState(CMP_HandleTypeDef *hcomp);
///@}



#endif
#endif
