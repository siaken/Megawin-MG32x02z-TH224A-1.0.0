/**
 ******************************************************************************
 *
 * @file        MG32x02z_APX_MID.h
 *
 * @brief       This file provides firmware functions to manage the following 
 *              functionalities of the APX peripheral:
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.04
 * @date        2022/03/17
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

#ifndef _MG32x02z_APX_MID_H

/*!< _MG32x02z_APX_DRV_H */ 
#define _MG32x02z_APX_MID_H

#include "MG32x02z.h"
#include "MG32x02z_Common_MID.h"
#include "MG32x02z_APX.h"
#include "MG32x02z__ExtraStruct.h"
/**
 * @name	CCLx_MUX0_Input
 *   	    CCLx MUX0 input signal
 */ 
//!@{
#define CCLx_MUX0_DISABLE                       APX_CCL01_CCL0_MUX0_disable_w   /*!< Disable CCL IN0 input Mux. */
#define CCLx_MUX0_IN1                           APX_CCL01_CCL0_MUX0_in01_w      /*!< CCL IN0 input MUX select CCLn_SEQ signal. */
#define CCLx_MUX0_IN2                           APX_CCL01_CCL0_MUX0_in02_w      /*!< CCL IN0 input MUX select CCLn_AO signal. */
#define CCLx_MUX0_IN3                           APX_CCL01_CCL0_MUX0_in03_w      /*!< CCL IN0 input MUX select PB11 signal. */
#define CCLx_MUX0_IN4                           APX_CCL01_CCL0_MUX0_in04_w      /*!< CCL IN0 input MUX select PA8 signal. */
#define CCLx_MUX0_IN5                           APX_CCL01_CCL0_MUX0_in05_w      /*!< CCL IN0 input MUX select PB0 signal. */
#define CCLx_MUX0_IN6                           APX_CCL01_CCL0_MUX0_in05_w      /*!< CCL IN0 input MUX select PB8 signal. */
#define CCLx_MUX0_IN7                           APX_CCL01_CCL0_MUX0_in07_w      /*!< CCL IN0 input MUX select PE0 signal. */
#define CCLx_MUX0_IN8                           APX_CCL01_CCL0_MUX0_in08_w      /*!< CCL IN0 input MUX select CMP0_OUT signal. */
#define CCLx_MUX0_IN9                           APX_CCL01_CCL0_MUX0_in09_w      /*!< CCL IN0 input MUX select URT0_TX signal. */
#define CCLx_MUX0_INA                           APX_CCL01_CCL0_MUX0_in0A_w      /*!< CCL IN0 input MUX select SPI0_MOSI signal. */
#define CCLx_MUX0_INB                           APX_CCL01_CCL0_MUX0_in0B_w      /*!< CCL IN0 input MUX select TM36_OC00 signal. */
#define CCLx_MUX0_INC                           APX_CCL01_CCL0_MUX0_in0C_w      /*!< CCL IN0 input MUX select TM26_OC00 signal. */
#define CCLx_MUX0_IND                           APX_CCL01_CCL0_MUX0_in0D_w      /*!< CCL IN0 input MUX select CCL_I0 signal. */
#define CCLx_MUX0_INE                           APX_CCL01_CCL0_MUX0_in0E_w      /*!< CCL IN0 input MUX select OBM_P0 signal. */
//!@}

/**
 * @name	CCLx_MUX1_Input
 *   	    CCLx MUX1 input signal
 */ 
//!@{
#define CCLx_MUX1_DISABLE                       APX_CCL01_CCL0_MUX1_disable_w   /*!< Disable CCL IN1 input Mux. */
#define CCLx_MUX1_IN1                           APX_CCL01_CCL0_MUX1_in01_w      /*!< CCL IN1 input MUX select CCLn_SEQ signal. */
#define CCLx_MUX1_IN2                           APX_CCL01_CCL0_MUX1_in02_w      /*!< CCL IN1 input MUX select CCLn_AO signal. */
#define CCLx_MUX1_IN3                           APX_CCL01_CCL0_MUX1_in03_w      /*!< CCL IN1 input MUX select PB3 signal. */
#define CCLx_MUX1_IN4                           APX_CCL01_CCL0_MUX1_in04_w      /*!< CCL IN1 input MUX select PA9 signal. */
#define CCLx_MUX1_IN5                           APX_CCL01_CCL0_MUX1_in05_w      /*!< CCL IN1 input MUX select PB1 signal. */
#define CCLx_MUX1_IN6                           APX_CCL01_CCL0_MUX1_in05_w      /*!< CCL IN1 input MUX select PB9 signal. */
#define CCLx_MUX1_IN7                           APX_CCL01_CCL0_MUX1_in07_w      /*!< CCL IN1 input MUX select PE1 signal. */
#define CCLx_MUX1_IN8                           APX_CCL01_CCL0_MUX1_in08_w      /*!< CCL IN1 input MUX select CMP1_OUT signal. */
#define CCLx_MUX1_IN9                           APX_CCL01_CCL0_MUX1_in09_w      /*!< CCL IN1 input MUX select URT1_TX signal. */
#define CCLx_MUX1_INA                           APX_CCL01_CCL0_MUX1_in0A_w      /*!< CCL IN1 input MUX select SPI0_MISO signal. */
#define CCLx_MUX1_INB                           APX_CCL01_CCL0_MUX1_in0B_w      /*!< CCL IN1 input MUX select TM36_OC10 signal. */
#define CCLx_MUX1_INC                           APX_CCL01_CCL0_MUX1_in0C_w      /*!< CCL IN1 input MUX select TM26_OC10 signal. */
#define CCLx_MUX1_IND                           APX_CCL01_CCL0_MUX1_in0D_w      /*!< CCL IN1 input MUX select CCL_I1 signal. */
#define CCLx_MUX1_INE                           APX_CCL01_CCL0_MUX1_in0E_w      /*!< CCL IN1 input MUX select OBM_I0 signal. */
//!@}


/**
 * @name	CCLx_MUX2_Input
 *   	    CCLx MUX2 input signal
 */ 
//!@{
#define CCLx_MUX2_DISABLE                       APX_CCL01_CCL0_MUX2_disable_w   /*!< Disable CCL IN2 input Mux. */
#define CCLx_MUX2_IN1                           APX_CCL01_CCL0_MUX2_in01_w      /*!< CCL IN2 input MUX select CCLn_SEQ signal. */
#define CCLx_MUX2_IN2                           APX_CCL01_CCL0_MUX2_in02_w      /*!< CCL IN2 input MUX select CCLn_AO signal. */
#define CCLx_MUX2_IN3                           APX_CCL01_CCL0_MUX2_in03_w      /*!< CCL IN2 input MUX select PC1 signal. */
#define CCLx_MUX2_IN4                           APX_CCL01_CCL0_MUX2_in04_w      /*!< CCL IN2 input MUX select PA10 signal. */
#define CCLx_MUX2_IN5                           APX_CCL01_CCL0_MUX2_in05_w      /*!< CCL IN2 input MUX select PB2 signal. */
#define CCLx_MUX2_IN6                           APX_CCL01_CCL0_MUX2_in05_w      /*!< CCL IN2 input MUX select PB10 signal. */
#define CCLx_MUX2_IN7                           APX_CCL01_CCL0_MUX2_in07_w      /*!< CCL IN2 input MUX select PE2 signal. */
#define CCLx_MUX2_IN8                           APX_CCL01_CCL0_MUX2_in08_w      /*!< CCL IN2 input MUX select ADC0_OUT signal. */
#define CCLx_MUX2_IN9                           APX_CCL01_CCL0_MUX2_in09_w      /*!< CCL IN2 input MUX select URT4_TX signal. */
#define CCLx_MUX2_INA                           APX_CCL01_CCL0_MUX2_in0A_w      /*!< CCL IN2 input MUX select SPI0_CLK signal. */
#define CCLx_MUX2_INB                           APX_CCL01_CCL0_MUX2_in0B_w      /*!< CCL IN2 input MUX select TM36_OC2 signal. */
#define CCLx_MUX2_INC                           APX_CCL01_CCL0_MUX2_in0C_w      /*!< CCL IN2 input MUX select TM20_OC00 signal. */
#define CCLx_MUX2_IND                           APX_CCL01_CCL0_MUX2_in0D_w      /*!< CCL IN2 input MUX select CCL_P0 signal. */
#define CCLx_MUX2_INE                           APX_CCL01_CCL0_MUX2_in0E_w      /*!< CCL IN2 input MUX select OBM_I1 signal. */
//!@}
/**
 * @name	CCL_OutputPolarity
 *   	    CCL OutputPolarity
 */ 
//!@{
#define CCL_OUTPUTPOL_NONINVERTED               (0x00000000U)                   /*!< CCL output on GPIO isn't inverted. */
#define CCL_OUTPUTPOL_INVERTED                  APX_CCL00_CCL0_INV_enable_w     /*!< CCL output on GPIO is inverted. */
//!@}

/**
 * @name	CCL_SQIN_Def
 *   	    CCL SQIN input
 */ 
//!@{
#define CCL_SQIN_0                              APX_CCL00_CCL0_SQIN_0_w         /*!< CCL sequential logic input is '0'. */
#define CCL_SQIN_1                              APX_CCL00_CCL0_SQIN_1_w         /*!< CCL sequential logic input is '1'. */
#define CCL_SQIN_CCL_S1                         APX_CCL00_CCL0_SQIN_ccl_s1_w    /*!< CCL sequential logic input is from CCL_S1 (only for CCL0). */
//!@}

/**
 * @name	CCL_ClockDivision
 *          CCL Clock Division
 */ 
//!@{
#define CCL_INTERNALCLOCK_DIV1                  APX_CCL00_CCL0_DIV_div1_w       /*!< CCL internal clock divide 1. */
#define CCL_INTERNALCLOCK_DIV2                  APX_CCL00_CCL0_DIV_div2_w       /*!< CCL internal clock divide 2. */
#define CCL_INTERNALCLOCK_DIV4                  APX_CCL00_CCL0_DIV_div4_w       /*!< CCL internal clock divide 4. */
#define CCL_INTERNALCLOCK_DIV8                  APX_CCL00_CCL0_DIV_div8_w       /*!< CCL internal clock divide 8. */
//!@}

/**
 * @name	CCL_SQLogicModeSel
 *   	    CCL sequential logic mode select.
 */ 
//!@{
#define CCL_SQSEL_DISABLE                       APX_CCL00_CCL0_SQSEL_disable_w  /*!< Disable SQSEL effect. */
#define CCL_SQSEL_D_FLIPFLOP                    APX_CCL00_CCL0_SQSEL_dff_w      /*!< DFF : D flip flop. */
#define CCL_SQSEL_JK_FLIPFLOP                   APX_CCL00_CCL0_SQSEL_jk_w       /*!< JK : JK flip flop. */
#define CCL_SQSEL_D_LATCH                       APX_CCL00_CCL0_SQSEL_dlh_w      /*!< DLH : D latch. */
#define CCL_SQSEL_RS_LATCH                      APX_CCL00_CCL0_SQSEL_rs_w       /*!< RS : RS latch. */
//!@}

/**
 * @name	CCL_Edge_Detector_Mode
 *   		CCL edge detector mode
 */ 
//!@{
#define CCL_DISABLE_DETECTOR                    APX_CCL00_CCL0_EDSEL_disable_w  /*!< Disable edge detect. */
#define CCL_DETECT_RISING                       APX_CCL00_CCL0_EDSEL_rising_w   /*!< CCL detect rising edge. */
#define CCL_DETECT_FALLING                      APX_CCL00_CCL0_EDSEL_falling_w  /*!< CCL detect falling edge. */
#define CCL_DETECT_DUALEDGE                     APX_CCL00_CCL0_EDSEL_dual_edge_w /*!< CCL detect dual edge. */
//!@}

/**
 * @name	CCL_OutputSynchronizeFilter
 *   		CCL Output Synchronize Filter
 */ 
//!@{
#define APX_DISABLE_SYNCHRONIZE                 APX_CCL00_CCL0_FTSEL_disable_w  /*!< Disable filter function. */
#define APX_SYNCHRONIZE_CLOCK                   APX_CCL00_CCL0_FTSEL_sync_w     /*!< Synchronizer enabled. */
#define APX_FILTER_ENABLE                       APX_CCL00_CCL0_FTSEL_filter_w   /*!< Enable Filter. */
//!@}

/**
 * @name	CCL_TruthTableDef
 *   		CCL Truth table define
 */ 
//!@{
#define MID_APX_3IN_AND                         0x80                            /*!< Run truth table with 3-input "AND". */
#define MID_APX_3IN_NAND                        0x7F                            /*!< Run truth table with 3-input "NAND". */
#define MID_APX_3IN_OR                          0xFE                            /*!< Run truth table with 3-input "OR". */
#define MID_APX_3IN_NOR                         0x01                            /*!< Run truth table with 3-input "NOR". */
#define MID_APX_3IN_XOR                         0x96                            /*!< Run truth table with 3-input "XOR". */
#define MID_APX_3IN_XNOR                        0x69                            /*!< Run truth table with 3-input "XNOR". */
#define MID_APX_2IN_AND                         0x08                            /*!< Run truth table with 2-input "AND". *[IN2] mask. */
#define MID_APX_2IN_NAND                        0x07                            /*!< Run truth table with 2-input "NAND". *[IN2] mask. */
#define MID_APX_2IN_OR                          0x0E                            /*!< Run truth table with 2-input "OR". *[IN2] mask. */
#define MID_APX_2IN_NOR                         0x01                            /*!< Run truth table with 2-input "NOR". *[IN2] mask. */
#define MID_APX_2IN_XOR                         0x06                            /*!< Run truth table with 2-input "XOR". *[IN2] mask. */
#define MID_APX_2IN_XNOR                        0x09                            /*!< Run truth table with 2-input "XNOR". *[IN2] mask. */
#define MID_APX_IN0_NOT                         0x55                            /*!< Run truth table with "NOT" IN0. */
#define MID_APX_IN1_NOT                         0x33                            /*!< Run truth table with "NOT" IN1. */
#define MID_APX_IN2_NOT                         0x0F                            /*!< Run truth table with "NOT" IN2. */
//!@}


/**
 * @enum        MID_CCL_StateTypeDef
 * @brief       MID State structures definition
 */
typedef enum
{
    MID_CCL_STATE_BUSY,             /*!< An internal process is running */
    MID_CCL_STATE_READY,            /*!< Peripheral Initialized and ready for use */
    MID_CCL_STATE_RESET             /*!< Reset peripheral state for use */
} MID_CCL_StateTypeDef;

/**
 * @enum        CCL_OuputStateTypeDef
 * @brief       CCL Ouput State structures definition
 */
typedef enum
{
    CCL_OUTPUTLEVEL_LOW = 0,        /*!< Peripheral Initialized and ready for use */
    CCL_OUTPUTLEVEL_HIGH = 1        /*!< An internal process is running */
} CCL_OuputStateTypeDef;


/** 
 * @struct  CCL_HandleTypeDef
 * @brief   Structure definition of CCL initialization and regular group 
 */        
typedef struct __attribute__((packed))
{ 
    CCL_Struct* Instance;           /*!< Register base address. e.g CCL0 or CCL1 */
        
    uint32_t TruthTable;            /*!< Declare the truth table of the CCL.
                                         This parameter can be a value of reference CCL_TruthTableDef. */
        
    uint32_t CCL_INTClockDivision;  /*!< Specifies the clock division.
                                         This parameter can be a value of reference CCL_ClockDivision */
    
    uint32_t MUX0Input;             /*!< Selects the CCLx MUX0 input. This parameter can be a value of reference CCLx_MUX0_Input. */
        
    uint32_t MUX1Input;             /*!< Selects the CCLx MUX1 input. This parameter can be a value of reference CCLx_MUX1_Input. */
        
    uint32_t MUX2Input;             /*!< Selects the CCLx MUX2 input. This parameter can be a value of reference CCLx_MUX2_Input. */
        
    uint32_t CCL_SQIN;              /*!< Selects the CCL sequential logic input.
                                         This parameter can be a value of reference CCL_SQIN_Def. */
                                        
    uint32_t SEQMode;               /*!< CCL sequential logic mode select.
                                         This parameter can be a value of reference CCL_SQLogicModeSel. */
    
    uint32_t EdgeDetectMode;        /*!< CCL edge detector mode select. 
                                         This parameter can be a value of reference CCL_Edge_Detector_Mode. */
    
    uint32_t OutputSync;            /*!< CCL output synchronized filter function.
                                         This parameter can be a value of reference CCL_OutputSynchronizeFilter. */

    uint32_t OutputPol;             /*!< Selects the inverting output of the CCL.
                                         This parameter can be a value of reference CCL_OutputPolarity. */
         
    MID_LockTypeDef Lock;           /*!< Locking object */
        
    MID_CCL_StateTypeDef State;     /*!< CCL operation state  */

}CCL_HandleTypeDef;




/**
 * @name	APX_Event_Groupdef
 *   		APX Event Group Definition
 */ 
//!@{
#define APX_CCL1_FLAG                           APX_STA_CCL1F_happened_w        /*!< CCL-1 output low-to-high detect flag. */    
#define APX_CCL0_FLAG                           APX_STA_CCL0F_happened_w        /*!< CCL-0 output low-to-high detect flag. */    
//!@}


/**
 * @name	APX_Interrupt_definition
 *   		APX Interrupt Definition
 */ 
//!@{
#define APX_IT_CCL1                             APX_INT_CCL1_IE_enable_w        /*!< CCL-1 output low-to-high detect interrupt enable. */
#define APX_IT_CCL0                             APX_INT_CCL0_IE_enable_w        /*!< CCL-0 output low-to-high detect interrupt enable. */
//!@}






/**
 *******************************************************************************
 * @brief       Enable the specified CCLx.
 * @param[in]   "__HANDLE__" : pointer to a CCL handle.
 * @return		None
 *******************************************************************************
 */
#define __DRV_APX_CCL_ENABLE(__HANDLE__)                                            \
    (((__HANDLE__)->Instance->CCLx0.W) |= APX_CCL00_CCL0_EN_enable_w)                 

/**
 *******************************************************************************
 * @brief       Disable the specified CCLx.
 * @param[in]   "__HANDLE__" : pointer to a CCL handle.
 * @return		None
 *******************************************************************************
 */
#define __DRV_APX_CCL_DISABLE(__HANDLE__)                                           \
    (((__HANDLE__)->Instance->CCLx0.W) &= ~APX_CCL00_CCL0_EN_enable_w)                 

/**
 *******************************************************************************
 * @brief       Config CCLx output invert function.
 * @param[in]   "__HANDLE__" : pointer to a CCL handle.
 * @param[in]   "__INV__" : specifies CCL_OutputPolarity selection
 *  @arg\b      CCL_OUTPUTPOL_NONINVERTED : CCL output on GPIO isn't inverted.
 *  @arg\b      CCL_OUTPUTPOL_INVERTED : CCL output on GPIO is inverted.
 * @return		None
 *******************************************************************************
 */
#define __DRV_APX_CCL_OUT_INV(__HANDLE__,__INV__)                                   \
    (((__HANDLE__)->Instance->CCLx0.W) &= ~APX_CCL00_CCL0_INV_mask_w);              \
    (((__HANDLE__)->Instance->CCLx0.W) |= (__INV__))                                  

/**
 *******************************************************************************
 * @brief       Config CCLx sequential logic mode.
 * @param[in]   "__HANDLE__" : pointer to a CCL handle.
 * @param[in]   "__SQMODE__" : specifies CCL_SQLogicModeSel selection
 *  @arg\b      CCL_SQSEL_DISABLE : Disable SQSEL effect.
 *  @arg\b      CCL_SQSEL_D_FLIPFLOP : D flip flop.
 *  @arg\b      CCL_SQSEL_JK_FLIPFLOP : JK flip flop.
 *  @arg\b      CCL_SQSEL_D_LATCH : D latch.
 *  @arg\b      CCL_SQSEL_RS_LATCH : RS latch.
 * @return		None
 *******************************************************************************
 */
#define __DRV_APX_CCL_SET_SQSEL(__HANDLE__,__SQMODE__)                              \
    (((__HANDLE__)->Instance->CCLx0.W) &= ~APX_CCL00_CCL0_SQSEL_mask_w);            \
    (((__HANDLE__)->Instance->CCLx0.W) |= (__SQMODE__))                                  

/**
 *******************************************************************************
 * @brief       Config CCLx edge detect function.
 * @param[in]   "__HANDLE__" : pointer to a CCL handle.
 * @param[in]   "__EDGEMODE__" : specifies CCL_Edge_Detector_Mode selection
 *  @arg\b      CCL_DISABLE_DETECTOR : Disable edge detect.
 *  @arg\b      CCL_DETECT_RISING : CCL detect rising edge.
 *  @arg\b      CCL_DETECT_FALLING : CCL detect falling edge.
 *  @arg\b      CCL_DETECT_DUALEDGE : CCL detect dual edge.
 * @return		None
 *******************************************************************************
 */
#define __DRV_APX_CCL_SET_EDSEL(__HANDLE__,__EDGEMODE__)                            \
    (((__HANDLE__)->Instance->CCLx0.W) &= ~APX_CCL00_CCL0_EDSEL_mask_w);            \
    (((__HANDLE__)->Instance->CCLx0.W) |= (__EDGEMODE__))                                  

/**
 *******************************************************************************
 * @brief       Config CCL_Sx state mode.
 * @param[in]   "__HANDLE__" : pointer to a CCL handle.
 * @param[in]   "__CCLSX__" : specifies CCL_Edge_Detector_Mode selection
 *  @arg\b      CCL_SQIN_0 : CCL sequential logic input is '0'.
 *  @arg\b      CCL_SQIN_1 : CCL sequential logic input is '1'.
 *  @arg\b      CCL_SQIN_CCL_S1 :  CCL sequential logic input is from CCL_S1 (only for CCL0).
 * @return		None
 *******************************************************************************
 */
#define __DRV_APX_CCL_SET_CCLSX(__HANDLE__,__CCLSX__)                               \
    (((__HANDLE__)->Instance->CCLx0.W) &= ~APX_CCL00_CCL0_SQIN_mask_w);             \
    (((__HANDLE__)->Instance->CCLx0.W) |= (__CCLSX__))                                  


/**
 *******************************************************************************
 * @brief       Config CCL clock filter function.
 * @param[in]   "__HANDLE__" : pointer to a CCL handle.
 * @param[in]   "__SYNC__" : specifies CCL_OutputSynchronizeFilter selection
 *  @arg\b      APX_DISABLE_SYNCHRONIZE : Disable filter function.
 *  @arg\b      APX_SYNCHRONIZE_CLOCK : Synchronizer enabled.
 *  @arg\b      APX_FILTER_ENABLE : Filter enable.
 * @return		None
 *******************************************************************************
 */
#define __DRV_APX_CCL_SET_SYNC(__HANDLE__,__SYNC__)                                 \
    (((__HANDLE__)->Instance->CCLx0.W) &= ~APX_CCL00_CCL0_FTSEL_mask_w);            \
    (((__HANDLE__)->Instance->CCLx0.W) |= (__SYNC__))                                  



/**
 *******************************************************************************
 * @brief       Reset CCL handle state
 * @param[in]   "__HANDLE__" : pointer to a CCL handle.
 * @return		None
 *******************************************************************************
 */
#define __DRV_APX_RESET_HANDLE_STATE(__HANDLE__)                                    \
  ((__HANDLE__)->State = MID_CCL_STATE_READY)

/**
 *******************************************************************************
 * @brief       Enables the specified APX All interrupt.
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_APX_ENABLE_ITEA();
 * @endcode
 *******************************************************************************
 */
#define __DRV_APX_ENABLE_ITEA()    (APX->INT.W |= APX_INT_IEA_enable_w)

/**
 *******************************************************************************
 * @brief       Disables the specified APX All interrupt.
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_APX_ENABLE_ITEA();
 * @endcode
 *******************************************************************************
 */
#define __DRV_APX_DISABLE_ITEA()    (APX->INT.W &= ~APX_INT_IEA_enable_w)




/**
 *******************************************************************************
 * @brief       Clear the APX interrupt pending bits.
 * @param[in]   "__FLAG__" : specifies the APX interrupt flag to clear.
 *  @arg\b	    APX_CCL1_FLAG : CCL1 output low-to-high detect flag.
 *  @arg\b	    APX_CCL0_FLAG : CCL0 output low-to-high detect flag.
 * @return		None
 * @note 
 * @par         Example
 * @code
    __DRV_APX_CLEAR_FLAG(APX_CCL0_FLAG);
 * @endcode
 *******************************************************************************
 */
#define __DRV_APX_CLEAR_FLAG(__FLAG__)                                              \
    ((APX->STA.W) = (__FLAG__))

/**
 *******************************************************************************
 * @brief       Get the APX interrupt pending bits.
 * @param[in]   "__FLAG__ : specifies the APX interrupt flag to clear.
 *  @arg\b	    APX_CCL1_FLAG : CCL1 output low-to-high detect flag.
 *  @arg\b	    APX_CCL0_FLAG : CCL0 output low-to-high detect flag.
 * @return		The state of EVENT (SET or RESET).
 * @note 
 * @par         Example
 * @code
    if(__DRV_APX_GET_FLAG(APX_CCL0_FLAG) == SET)
    {
        // to do ...
    }
 * @endcode
 *******************************************************************************
 */
#define __DRV_APX_GET_FLAG(__FLAG__)                                                \
    ((APX->STA.W & (__FLAG__)) == (__FLAG__))


/**
 *******************************************************************************
 * @brief       Enables the specified APX interrupt.
 * @param[in]   "__INTERRUPT__" : specifies the APX interrupt source to enable.
 *  @arg\b      APX_IT_CCL1 : CCL-1 output low-to-high detect interrupt enable.
 *  @arg\b      APX_IT_CCL0 : CCL-0 output low-to-high detect interrupt enable.
 * @return      None
 * @note 
 * @par         Example
 * @code
    __DRV_APX_ENABLE_IT(APX_IT_CCL0);
 * @endcode
 *******************************************************************************
 */
#define __DRV_APX_ENABLE_IT(__INTERRUPT__)                                          \
    ((APX->INT.W) |= (__INTERRUPT__))

/**
 *******************************************************************************
 * @brief       Checks whether the specified APX interrupt has occurred or not.
 * @param[in]   "__INTERRUPT__" : specifies the APX interrupt source to enable.
 *  @arg\b      APX_IT_CCL1 : CCL-1 output low-to-high detect interrupt enable.
 *  @arg\b      APX_IT_CCL0 : CCL-0 output low-to-high detect interrupt enable.
 * @return		The state of EVENT (SET or RESET)
 * @note 
 * @par         Example
 * @code
    if(__DRV_APX_GET_IT_SOURCE(APX_IT_CCL1) == SET)
    {
        // to do ...
    }
 * @endcode
 *******************************************************************************
 */
#define __DRV_APX_GET_IT_SOURCE(__INTERRUPT__)                                      \
    ((APX->INT.W & (__INTERRUPT__)) == (__INTERRUPT__))


/**
 *******************************************************************************
 * @brief       Disables the specified APX interrupt.
 * @param[in]   "__INTERRUPT__" : specifies the TM interrupt source to enable.
 *  @arg\b      APX_IT_CCL1 : CCL-1 output low-to-high detect interrupt enable.
 *  @arg\b      APX_IT_CCL0 : CCL-0 output low-to-high detect interrupt enable.
 * @return      None
 * @note 
 * @par         Example
 * @code
    __DRV_APX_DISABLE_IT(APX_IT_CCL1);
 * @endcode
 *******************************************************************************
 */
#define __DRV_APX_DISABLE_IT(__INTERRUPT__)                                         \
    ((APX->INT.W) &= ~(__INTERRUPT__))



#if defined(APX_CR0_ASB0_ENX_mask_w)
#ifndef __MG32x02z_APX_DRV_H
/**
 *******************************************************************************
 * @brief       Set ASB Channel0 output data.
 * @param[in]   "__DATA__" : 8bit data for ASB channel0.
 * @return		  None
 *******************************************************************************
 */
#define __DRV_APX_ASBChannel0SendData(__DATA__)                APX->ASBDAT.B[0] = (uint8_t)(__DATA__)

/**
 *******************************************************************************
 * @brief       Set ASB Channel1 output data.
 * @param[in]   "__DATA__" : 8bit data for ASB channel1.
 * @return		  None
 *******************************************************************************
 */
#define __DRV_APX_ASBChannel1SendData(__DATA__)                APX->ASBDAT.B[1] = (uint8_t)(__DATA__)

/**
 *******************************************************************************
 * @brief       Set ASB Channel2 output data.
 * @param[in]   "__DATA__" : 8bit data for ASB channel2.
 * @return		  None
 *******************************************************************************
 */
#define __DRV_APX_ASBChannel2SendData(__DATA__)                APX->ASBDAT.B[2] = (uint8_t)(__DATA__)

/**
 *******************************************************************************
 * @brief       Set ASB Channel3 output data.
 * @param[in]   "__DATA__" : 8bit data for ASB channel3.
 * @return		  None
 *******************************************************************************
 */
#define __DRV_APX_ASBChannel3SendData(__DATA__)                APX->ASBDAT.B[3] = (uint8_t)(__DATA__)

/**
 *******************************************************************************
 * @brief       Set ASB Channel0 & Channel1 output data.
 * @param[in]   "__DATA__" : 16bit data for ASB Channel0 and Channel1.
 *              LSB for Channel0.
 *              MSB for Channel1.
 * @return		  None
 *******************************************************************************
 */
#define __DRV_APX_ASBChannel01SendData(__DATA__)               APX->ASBDAT.H[0] = (uint16_t)(__DATA__)   

/**
 *******************************************************************************
 * @brief       Set ASB Channel2 & Channel3 output data.
 * @param[in]   "__DATA__" : 16bit data for ASB Channel2 and Channel3.
 *              LSB for Channel2.
 *              MSB for Channel3.
 * @return		  None
 *******************************************************************************
 */
#define __DRV_APX_ASBChannel23SendData(__DATA__)               APX->ASBDAT.H[1] = (uint16_t)(__DATA__)    
///@}
#endif
#endif


/**
 * @name    Function announce
 * @brief   APX CCL base initial/Deinitial	
 */ 
///@{
/* Initialization and de-initialization functions  ****************************/
MID_StatusTypeDef MID_APX_CCL_Init(CCL_HandleTypeDef* mCCL);
MID_StatusTypeDef MID_APX_CCL_DeInit(CCL_HandleTypeDef* mCCL);
void MID_APX_CCL_MspInit(CCL_HandleTypeDef* mCCL);
void MID_APX_CCL_MspDeInit(CCL_HandleTypeDef* mCCL);

/* IO operation functions *****************************************************/
MID_StatusTypeDef MID_APX_CCL_Start(CCL_HandleTypeDef* mCCL);
MID_StatusTypeDef MID_APX_CCL_Stop(CCL_HandleTypeDef* mCCL);
MID_StatusTypeDef MID_APX_CCL_Start_IT(CCL_HandleTypeDef* mCCL);
MID_StatusTypeDef MID_APX_CCL_Stop_IT(CCL_HandleTypeDef* mCCL);
void MID_APX_CCL_IRQHandler(CCL_HandleTypeDef* mCCL);
///@}


/**
 * @name    Function announce
 * @brief   addtogroup APX_Exported_Functions_Group
 */ 
///@{
uint32_t MID_APX_CCL_GetOutputLevel(CCL_HandleTypeDef* mCCL);
/* Callback in Interrupt mode */
void MID_APX_CCL0_TriggerCallback(CCL_HandleTypeDef* mCCL);
void MID_APX_CCL1_TriggerCallback(CCL_HandleTypeDef* mCCL);
/* Get state */
uint32_t MID_APX_CCL_GetState(CCL_HandleTypeDef* mCCL);
///@}



#endif
