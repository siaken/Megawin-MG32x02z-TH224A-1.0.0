/**
 ******************************************************************************
 *
 * @file        MG32x02z_DAC_MID.h
 *
 * @brief       This file provides firmware functions to manage the following 
 *              functionalities of the DAC peripheral:
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.01
 * @date        2020/07/03
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

#include "MG32x02z.h"
#if defined(MG32_1ST) || defined(MG32_3RD)

#ifndef _MG32x02z_DAC_MID_H

/*!< _MG32x02z_DAC_DRV_H */ 
#define _MG32x02z_DAC_MID_H

#include "MG32x02z_Common_MID.h"
#include "MG32x02z_DAC.h"
#include "MG32x02z_DMA_MID.h"

/**
 * @name	DAC_Error_Code 
 *   		DAC Error Code
 */ 
//!@{
#define MID_DAC_ERROR_NONE                      0x00    /*!< No error. */
#define MID_DAC_ERROR_DMAUNDERRUN               0x01    /*!< DAC channel DMA underrun error. */
#define MID_DAC_ERROR_DMA                       0x02    /*!< DAC Analog input negative channel select common pin PB0. */
//!@}                                           

/**
 * @name	DAC_Data_align 
 *   		DAC data alignment
 */ 
//!@{
#if defined(MG32_3RD)
#define DAC_ALIGN_12B_R                         DAC_CR0_RES0_SEL_12_bit_w | DAC_CR0_ALIGN0_SEL_right_w  /*!< DAC Analog input 12bit with right justified.   */
#define DAC_ALIGN_12B_L                         DAC_CR0_RES0_SEL_12_bit_w | DAC_CR0_ALIGN0_SEL_left_w   /*!< DAC Analog input 12bit with left justified.    */
#endif
#define DAC_ALIGN_10B_R                         DAC_CR0_RES0_SEL_10_bit_w | DAC_CR0_ALIGN0_SEL_right_w  /*!< DAC Analog input 10bit with right justified.   */
#define DAC_ALIGN_10B_L                         DAC_CR0_RES0_SEL_10_bit_w | DAC_CR0_ALIGN0_SEL_left_w   /*!< DAC Analog input 10bit with left justified.    */
#define DAC_ALIGN_8B_R                          DAC_CR0_RES0_SEL_8_bit_w | DAC_CR0_ALIGN0_SEL_right_w   /*!< DAC Analog input 8bit with right justified.    */
#define DAC_ALIGN_8B_L                          DAC_CR0_RES0_SEL_8_bit_w | DAC_CR0_ALIGN0_SEL_left_w    /*!< DAC Analog input 8bit with left justified.     */
//!@}

/**
 * @name	DAC_flags_definition
 *   		DAC flags definition
 */ 
//!@{
#define DAC_FLAG_READY                          DAC_STA_RDY0F_happened_w        /*!< DAC ready flag to update new data to data register. */
#define DAC_FLAG_UNDERRUN                       DAC_STA_UDR0F_happened_w        /*!< DAC conversion underrun event flag.  */
//!@}

/**
 * @name	DAC_IT_definition  
 *   		DAC IT definition
 */ 
//!@{
#define DAC_IT_READY                            DAC_INT_RDY0_IE_enable_w        /*!< DAC ready to update new data to data register interrupt enable. */
#define DAC_IT_UNDERRUN                         DAC_INT_UDR0_IE_enable_w        /*!< DAC conversion underrun event interrupt enable. */
//!@}

/**
 * @name	DAC_TriggerSource
 *   		DAC Trigger Source
 */ 
//!@{
#define DAC_TRIGGERSOURCE_WRITE_DAT0            (DAC_CR0_START0_SEL_wdat_w)     /*!< Write DAC_DAT0 register to update DAC output. */
#define DAC_TRIGGERSOURCE_PIN                   (DAC_CR0_START0_SEL_pin_w)      /*!< DAC_TRG external trigger pin to update. */
#define DAC_TRIGGERSOURCE_CMP0_OUT              (DAC_CR0_START0_SEL_cmp0_w)     /*!< CMP0_OUT update event. */
#define DAC_TRIGGERSOURCE_TM00_TRGO             (DAC_CR0_START0_SEL_tm00_w)     /*!< TM00_TRGO update event. */
#define DAC_TRIGGERSOURCE_TM01_TRGO             (DAC_CR0_START0_SEL_tm01_w)     /*!< TM01_TRGO update event. */
#define DAC_TRIGGERSOURCE_TM10_TRGO             (DAC_CR0_START0_SEL_tm10_w)     /*!< TM10_TRGO update event. */
#define DAC_TRIGGERSOURCE_ITR6                  (DAC_CR0_START0_SEL_itr6_w)     /*!< ITR6 update event. */
#define DAC_TRIGGERSOURCE_ITR7                  (DAC_CR0_START0_SEL_itr7_w)     /*!< ITR7 update event. */
//!@}

/**
 * @name	DAC_TriggerEdge_Def
 *   		DAC trigger edge definition
 */ 
//!@{
#define DAC_DISABLE_UPDATE                      DAC_CR0_TRG0_SEL_disable_w      /*!< Disable trigger event to DAC update. (except WDAT)  */
#define DAC_RISING_EDGE_UPDATE                  DAC_CR0_TRG0_SEL_rising_edge_w  /*!< Rising edge of trigger to update. */
#define DAC_FALLING_EDGE_UPDATE                 DAC_CR0_TRG0_SEL_falling_edge_w /*!< Falling edge of trigger to update. */
#define DAC_DUAL_EDGE_UPDATE                    DAC_CR0_TRG0_SEL_dual_edge_w    /*!< Dual edge of trigger to update. */
//!@}

#if defined(MG32_1ST)
/**
 * @name	DAC_OutputLevel
 *   		DAC output level
 */ 
//!@{
#define DAC_OUTPUTCURRENT_MODE0                 DAC_CR0_CMOD0_SEL_m0_w          /*!< Mode0: Output ~0.5mA on PB2. */
#define DAC_OUTPUTCURRENT_MODE1                 DAC_CR0_CMOD0_SEL_m1_w          /*!< Mode1: Output ~1mA on PB2. */
#define DAC_OUTPUTCURRENT_MODE2                 DAC_CR0_CMOD0_SEL_m2_w          /*!< Mode2: Output ~2mA on PB2. */
//!@}
#endif


/** 
 * @enum		MID_DAC_StateTypeDef
 * @brief		MID DAC State definition 
 */        
typedef enum 
{
    MID_DAC_STATE_RESET             = (0x00000000U),   /*!< DAC not yet initialized or disabled.             */
    MID_DAC_STATE_READY             = (0x00000001U),   /*!< DAC initialized and ready for use.               */
    MID_DAC_STATE_BUSY              = (0x00000011U),   /*!< DAC internal processing is ongoing.              */
    MID_DAC_STATE_TIMEOUT           = (0x00000002U),   /*!< DAC timeout state.                               */
    MID_DAC_STATE_ERROR             = (0x00000012U)    /*!< DAC error state.                                 */
}MID_DAC_StateTypeDef;


/** 
 * @struct  DAC_InitStructDef
 * @brief   Structure definition of DAC initialization and regular group 
 */        
typedef struct __attribute__((packed))
{ 
                                             
  uint32_t TriggerConverionSrc;   /*!< Selects the external event used to trigger the conversion start of regular group.
                                       This parameter can be a value of reference DAC_TriggerSource. */
                                       
  uint32_t TriggerConverionEdge;  /*!< Selects the external trigger edge of regular group.
                                       This parameter can be a value of reference DAC_TriggerEdge_Def. */
                                                                              
  uint32_t DataAlign;             /*!< Specifies whether the ADC data  alignment is left or right.  
                                       This parameter can be a value of reference DAC_Data_align */

#if defined(MG32_1ST)
  uint32_t OutputLevel;           /*!< DAC output current mode select.
                                       This parameter can be a value of reference DAC_OutputLevel. */
#endif
    
  uint32_t InteruptMode;          /*!< Selects the interrupt mode of the comparator (interrupt mode).
                                       This parameter can be a value of reference DAC_IT_definition. */

}DAC_InitStructDef;


/** 
 * @struct  DAC_HandleTypeDef
 * @brief   DAC handle Structure definition  
 */        
typedef struct __attribute__((packed))
{
    DAC_Struct                  *Instance;      /*!< Register base address */
                        
    DAC_InitStructDef           Init;           /*!< DAC required parameters */
                                            
    MID_LockTypeDef             Lock;           /*!< DAC locking object */
                    
    __IO MID_DAC_StateTypeDef   State;          /*!< DAC communication state 
                                                     This parameter can be a value of reference MID_DAC_StateTypeDef  */ 
                                                 
    DMA_HandleTypeDef           *DMA_Handle;    /*!< Pointer DMA handler */  

    __IO uint32_t               ErrorCode;      /*!< DAC Error code */    
                    
}DAC_HandleTypeDef;





/**
 *******************************************************************************
 * @brief       Reset DAC handle state
 * @param[in]   "__HANDLE__ : pointer to a DAC handle.
 * @return		None
 *******************************************************************************
 */
#define __DRV_DAC_RESET_HANDLE_STATE(__HANDLE__)                                \
  ((__HANDLE__)->State = MID_DAC_STATE_RESET)


/**
 *******************************************************************************
 * @brief       Enable the DAC and output DAT0 code.
 * @param[in]   "__HANDLE__ : pointer to a DAC_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
#define __DRV_DAC_ENABLE(__HANDLE__)                                            \
    ((__HANDLE__)->Instance->CR0.W |= DAC_CR0_DA0_EN_enable_w)                  

/**
 *******************************************************************************
 * @brief       Disable the DAC.
 * @param[in]   "__HANDLE__ : pointer to a DAC_HandleTypeDef
 * @return		None
 *******************************************************************************
 */
#define __DRV_DAC_DISABLE(__HANDLE__)                                           \
    ((__HANDLE__)->Instance->CR0.W &= ~DAC_CR0_DA0_EN_enable_w)                  


/**
 *******************************************************************************
 * @brief       Enables the specified DAC All interrupt.
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_DAC_ENABLE_ITEA();
 * @endcode
 *******************************************************************************
 */
#define __DRV_DAC_ENABLE_ITEA()    (DAC->INT.W |= DAC_INT_IEA_enable_w)

/**
 *******************************************************************************
 * @brief       Disables the specified DAC All interrupt.
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_DAC_ENABLE_ITEA();
 * @endcode
 *******************************************************************************
 */
#define __DRV_DAC_DISABLE_ITEA()    (DAC->INT.W &= ~DAC_INT_IEA_enable_w)

/**
 *******************************************************************************
 * @brief       Enables the specified DAC interrupt.
 * @param[in]   "__HANDLE__ : pointer to a DAC_HandleTypeDef
 * @param[in]   "__INTERRUPT__ : specifies the DAC interrupt source to enable.
 *  @arg\b	    DAC_IT_READY : DAC ready to update new data to data register interrupt enable.
 *  @arg\b	    DAC_IT_UNDERRUN : DAC conversion underrun event interrupt enable.
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_DAC_ENABLE_IT(&DAC_Handle,DAC_IT_READY);
 * @endcode
 *******************************************************************************
 */                                                                             
#define __DRV_DAC_ENABLE_IT(__HANDLE__, __INTERRUPT__)                          \
    ((__HANDLE__)->Instance->INT.W |= (__INTERRUPT__))

/**
 *******************************************************************************
 * @brief       Disables the specified DAC interrupt.
 * @param[in]   "__HANDLE__ : pointer to a DAC_HandleTypeDef
 * @param[in]   "__INTERRUPT__ : specifies the DAC interrupt source to enable.
 *  @arg\b	    DAC_IT_READY : DAC ready to update new data to data register interrupt enable.
 *  @arg\b	    DAC_IT_UNDERRUN : DAC conversion underrun event interrupt enable.
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_DAC_DISABLE_IT(&mDAC,DAC_IT_READY);
 * @endcode
 *******************************************************************************
 */
#define __DRV_DAC_DISABLE_IT(__HANDLE__, __INTERRUPT__)                         \
    ((__HANDLE__)->Instance->INT.W &= ~(__INTERRUPT__))

/**
 *******************************************************************************
 * @brief       Check whether the specified DAC interrupt source is enabled or not.
 * @param[in]   "__HANDLE__ : pointer to a DAC_HandleTypeDef
 * @param[in]   "__INTERRUPT__" : specifies the DAC interrupt source to check.
 *  @arg\b	    DAC_IT_READY : DAC ready to update new data to data register interrupt enable.
 *  @arg\b	    DAC_IT_UNDERRUN : DAC conversion underrun event interrupt enable.
 * @return		State of interruption (SET or RESET)
 * @note 
 * @par         Example
 * @code
    __DRV_DAC_GET_IT_SOURCE(&mDAC,DAC_IT_UNDERRUN);
 * @endcode
 *******************************************************************************
 */
#define __DRV_DAC_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)                      \
    (((__HANDLE__)->Instance->INT.W & (__INTERRUPT__)) == (__INTERRUPT__))

/**
 *******************************************************************************
 * @brief       Clear the DAC interrupt pending bits.
 * @param[in]   "__HANDLE__" : pointer to a ADC_HandleTypeDef
 * @param[in]   "__FLAG__" : specifies the DAC interrupt flag to clear.
 *  @arg\b	    DAC_FLAG_READY : DAC ready flag to update new data.     
 *  @arg\b	    DAC_FLAG_UNDERRUN : DAC conversion underrun.     
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_DAC_CLEAR_FLAG(DAC_FLAG_READY);
 * @endcode
 *******************************************************************************
 */
#define __DRV_DAC_CLEAR_FLAG(__HANDLE__,__FLAG__)                               \
    ((__HANDLE__)->Instance->STA.W = (__FLAG__))

/**
 *******************************************************************************
 * @brief       Get the DAC interrupt pending bits.
 * @param[in]   "__HANDLE__" : pointer to a ADC_HandleTypeDef
 * @param[in]   "__FLAG__ : specifies the DAC interrupt flag to clear.
 *  @arg\b	    DAC_FLAG_READY : DAC ready flag to update new data.     
 *  @arg\b	    DAC_FLAG_UNDERRUN : DAC conversion underrun.     
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_DAC_GET_FLAG(DAC_FLAG_READY);
 * @endcode
 *******************************************************************************
 */
#define __DRV_DAC_GET_FLAG(__HANDLE__,__FLAG__)                                 \
    (((__HANDLE__)->Instance->STA.W & (__FLAG__)) == (__FLAG__))

/**
 *******************************************************************************
 * @brief       Enables the specified DMA request.
 * @param[in]   "__HANDLE__": specifies the mDAC Handle.
 * @return		None
 *******************************************************************************
 */
#define __DRV_DAC_ENABLE_DMA(__HANDLE__)      ((__HANDLE__)->Instance->CR0.W |= (DAC_CR0_DMA_EN_enable_w))

/**
 *******************************************************************************
 * @brief       Disables the specified DMA request.
 * @param[in]   "__HANDLE__": specifies the mDAC Handle.
 * @return		None
 *******************************************************************************
 */
#define __DRV_DAC_DISABLE_DMA(__HANDLE__)     ((__HANDLE__)->Instance->CR0.W &= ~(DAC_CR0_DMA_EN_enable_w))







/**
 * @name    Function announce
 * @brief   DAC base initial/Deinitial
 */ 
///@{

/* Initialization and de-initialization functions  ****************************/
MID_StatusTypeDef MID_DAC_Init(DAC_HandleTypeDef* mDAC);
MID_StatusTypeDef MID_DAC_DeInit(DAC_HandleTypeDef *mDAC);
void MID_DAC_MspInit(DAC_HandleTypeDef* mDAC);
void MID_DAC_MspDeInit(DAC_HandleTypeDef* mDAC);

/* IO operation functions *****************************************************/
MID_StatusTypeDef MID_DAC_Start(DAC_HandleTypeDef* mDAC);
MID_StatusTypeDef MID_DAC_Stop(DAC_HandleTypeDef* mDAC);
MID_StatusTypeDef MID_DAC_Start_IT(DAC_HandleTypeDef* mDAC);
MID_StatusTypeDef MID_DAC_Stop_IT(DAC_HandleTypeDef* mDAC);
MID_StatusTypeDef MID_DAC_Start_DMA(DAC_HandleTypeDef* mDAC, uint32_t* pData, uint32_t Length);
MID_StatusTypeDef MID_DAC_Stop_DMA(DAC_HandleTypeDef* mDAC);
///@}


/**
 * @name    Function announce
 * @brief   addtogroup DAC_Exported_Functions_Group
 */ 
///@{
void MID_DAC_IRQHandler(DAC_HandleTypeDef* mDAC);
MID_StatusTypeDef MID_DAC_SetValue(DAC_HandleTypeDef* mDAC, uint32_t Data);
void MID_DAC_ReadyCallback(DAC_HandleTypeDef* mDAC);
void MID_DAC_ConvCpltCallback(DAC_HandleTypeDef* mDAC);
void MID_DAC_ConvHalfCpltCallback(DAC_HandleTypeDef* mDAC);
void MID_DAC_ErrorCallback(DAC_HandleTypeDef *mDAC);
void MID_DAC_DMAUnderrunCallback(DAC_HandleTypeDef *mDAC);

/* Callback in Interrupt mode */
uint32_t MID_DAC_GetValue(DAC_HandleTypeDef *mDAC);
MID_DAC_StateTypeDef MID_DAC_GetState(DAC_HandleTypeDef* mDAC);
uint32_t MID_DAC_GetError(DAC_HandleTypeDef* mDAC);

///@}



#endif
#endif
