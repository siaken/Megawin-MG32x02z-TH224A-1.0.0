/**
 ******************************************************************************
 *
 * @file        MG32x02z_PW_MID.h
 *
 * @brief       This is the C code format middleware head file for PW module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.05
 * @date        2022/09/14
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2020 Megawin Technology Co., Ltd.
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
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "MG32x02z.h"
#include "MG32x02z_PW.h"
#include "MG32x02z_CONF_MID.h" 


#ifndef _MG32x02z_PW_MID_H
/*!< _MG32x02z_PW_MID_H */ 
#define _MG32x02z_PW_MID_H


/*! @struct PW_BODxTypeDef
    @brief  BODx initialization struct
*/ 
typedef struct
{
    uint8_t     BODx_TRIGGER;           /*!< BOD1/2 Interrupt trigger selection     */
    uint8_t     BODx_THRESHOLD;         /*!< BOD1 detect voltage threshold select   */
} PW_BODxTypeDef;


/**
 * @name PW_BODx_Configure
 *      PW BODx configure
 */ 
//!@{
#define PW_BOD1_TH_MASK         PW_CR0_BOD1_TH_mask_w       /*!< BOD1 threshold mask    */
#define PW_BOD1_TRG_MASK        PW_CR0_BOD1_TRGS_mask_w     /*!< BOD1 trigger mask      */
#if defined(PW_CR0_BOD2_TRGS_mask_w)  
#define PW_BOD2_TRG_MASK        PW_CR0_BOD2_TRGS_mask_w     /*!< BOD2 trigger mask      */
#endif
#define PW_BOD1_TH_2V0          0x00000000                  /*!< BOD1 threshold 2.0V    */
#define PW_BOD1_TH_2V4          0x00000001                  /*!< BOD1 threshold 2.4V    */
#define PW_BOD1_TH_3V7          0x00000002                  /*!< BOD1 threshold 3.7V    */
#define PW_BOD1_TH_4V2          0x00000003                  /*!< BOD1 threshold 4.2V    */
#define PW_BODx_TRG_RESERVED    0x00000000                  /*!< BODx resered           */
#define PW_BODx_TRG_RISING      0x00000001                  /*!< BODx rising edge       */
#define PW_BODx_TRG_FALLING     0x00000002                  /*!< BODx falling edge      */
#define PW_BODx_TRG_DUAL        0x00000003                  /*!< BODx Dual-edge         */
//!@}


/**
 * @name PW_Interrupt_definition
 *      PW Interrupt Definition
 */
//!@{
#define PW_IT_IEA               PW_INT_IEA_mask_w           /*!< PW interrupt all enable                        */
#define PW_IT_BOD0              PW_INT_BOD0_IE_mask_w       /*!< BOD0 brown-out detection interrupt enable      */
#define PW_IT_BOD1              PW_INT_BOD1_IE_mask_w       /*!< BOD1 brown-out detection interrupt enable      */
#if defined(PW_INT_BOD2_IE_mask_w)
#define PW_IT_BOD2              PW_INT_BOD2_IE_mask_w       /*!< BOD2 brown-out detection interrupt enable      */
#endif
#define PW_IT_WK                PW_INT_WK_IE_mask_w         /*!< System received wakeup event interrupt enable  */
//!@}


/**
 * @name PW_Flags_definition
 *      PW Flags Definition
 */
//!@{
#define PW_FLAG_PORF            PW_STA_PORF_mask_w          /*!< Power-On reset status flag                 */
#define PW_FLAG_BOD0F           PW_STA_BOD0F_mask_w         /*!< BOD0 brown-out detection interrupt flag    */
#define PW_FLAG_BOD1F           PW_STA_BOD1F_mask_w         /*!< BOD1 brown-out detection interrupt flag    */
#if defined(PW_STA_BOD2F_mask_w)                                               
#define PW_FLAG_BOD2F           PW_STA_BOD2F_mask_w         /*!< BOD2 brown-out detection interrupt flag    */
#endif
#define PW_FLAG_WKF             PW_STA_WKF_mask_w           /*!< System received wakeup event flag          */
//!@}

/** 
 * @name PW_SLEEP_mode_entry 
 *      PW SLEEP mode entry
 */
//!@{
#define PW_SLEEPENTRY_WFI              ((uint8_t)0x01U)     /*!< Select sleep WFI   */
#define PW_SLEEPENTRY_WFE              ((uint8_t)0x02U)     /*!< Select sleep WFE   */
//!@}


/** 
 * @name PW_STOP_mode_entry 
 *      PW STOP mode entry
 */
//!@{
#define PW_STOPENTRY_WFI               ((uint8_t)0x01U)     /*!< Select stop WFI    */
#define PW_STOPENTRY_WFE               ((uint8_t)0x02U)     /*!< Select stop WFE    */
//!@}


/**
 * @name Check_PW_Entry_Mode_Parameter
 *      Check PW entry mode parameter
 */
//!@{
#define IS_PW_SLEEP_ENTRY(ENTRY) (((ENTRY) == PW_SLEEPENTRY_WFI) || ((ENTRY) == PW_SLEEPENTRY_WFE))
#define IS_PW_STOP_ENTRY(ENTRY) (((ENTRY) == PW_STOPENTRY_WFI) || ((ENTRY) == PW_STOPENTRY_WFE))
//!@}


/**
 * @name PW_WAKEUP_DELAY_SELECT
 *      PW wakeup delay select
 */
//!@{
#define PW_WAKEUP_DLEAY_DT0                 PW_CR0_WKSTP_DSEL_dt0_b2                        /*!< PW STOP mode wakeup delay DT0 (45 ~ 60us)      */
#define PW_WAKEUP_DLEAY_DT1                 PW_CR0_WKSTP_DSEL_dt1_b2                        /*!< PW STOP mode wakeup delay DT1 (60 ~ 75us)      */
#define PW_WAKEUP_DLEAY_DT2                 PW_CR0_WKSTP_DSEL_dt2_b2                        /*!< PW STOP mode wakeup delay DT2 (90 ~ 105us)     */
#define PW_WAKEUP_DLEAY_DT3                 PW_CR0_WKSTP_DSEL_dt3_b2                        /*!< PW STOP mode wakeup delay DT3 (150 ~ 165us)    */
//!@}


#define __DRV_PW_ENABLE_SLEEPONEXIT()       SET_BIT(SCB->SCR, SCB_SCR_SLEEPONEXIT_Msk)      /*!< Set SLEEPONEXIT bit of Cortex System Control Register      */
#define __DRV_PW_DISABLE_SLEEPONEXIT()      CLEAR_BIT(SCB->SCR, SCB_SCR_SLEEPONEXIT_Msk)    /*!< Clear SLEEPONEXIT bit of Cortex System Control Register    */
#define __DRV_PW_ENABLE_BOD1()              SET_BIT(PW->CR0.W, PW_CR0_BOD1_EN_mask_w)       /*!< Enable BOD1    */
#define __DRV_PW_DISABLE_BOD1()             CLEAR_BIT(PW->CR0.W, PW_CR0_BOD1_EN_mask_w)     /*!< Disable BOD1   */
#define __DRV_PW_ENANLE_VBUF()              SET_BIT(PW->CR0.W, PW_CR0_IVR_EN_mask_w)        /*!< Enable VBUF    */
#define __DRV_PW_DISANLE_VBUF()             CLEAR_BIT(PW->CR0.W, PW_CR0_IVR_EN_mask_w)      /*!< Disable VBUF   */


#if defined(PW_CR0_BOD2_EN_mask_w)
#define __DRV_PW_ENABLE_BOD2()              SET_BIT(PW->CR0.W, (PW_CR0_BOD2_EN_mask_w))     /*!< Enable BOD2    */
#define __DRV_PW_DISABLE_BOD2()             CLEAR_BIT(PW->CR0.W, (PW_CR0_BOD2_EN_mask_w))   /*!< Disable BOD2   */
#endif


/**
 * @name PW_SLEEP_Mode_Power_On_Control
 *      PW SLEEP mode power on contrl
 */
//!@{
#if defined(PW_CR1_SLP_CMP0_mask_w)
#define __DRV_PW_CMP0_SLEEP_MODE_POWER_ON_ENABLE()      PW->CR1.W |= PW_CR1_SLP_CMP0_mask_w     /*!< Analog comparator CMP0 power-on configuration after enter SLEEP mode   */
#define __DRV_PW_CMP1_SLEEP_MODE_POWER_ON_ENABLE()      PW->CR1.W |= PW_CR1_SLP_CMP1_mask_w     /*!< Analog comparator CMP1 power-on configuration after enter SLEEP mode   */
#endif
#if defined(PW_CR1_SLP_CMP2_mask_w)
#define __DRV_PW_CMP2_SLEEP_MODE_POWER_ON_ENABLE()      PW->CR1.W |= PW_CR1_SLP_CMP2_mask_w     /*!< Analog comparator CMP2 power-on configuration after enter SLEEP mode   */
#define __DRV_PW_CMP3_SLEEP_MODE_POWER_ON_ENABLE()      PW->CR1.W |= PW_CR1_SLP_CMP3_mask_w     /*!< Analog comparator CMP3 power-on configuration after enter SLEEP mode   */
#endif
#if (defined(USB_TYPE))
#define __DRV_PW_USB_SLEEP_MODE_POWER_ON_ENABLE()       PW->CR1.W |= PW_CR1_SLP_USB_mask_w      /*!< USB0 power-on configuration after enter SLEEP mode                     */
#endif
#if defined(PW_CR1_SLP_CMP0_mask_w)
#define __DRV_PW_CMP0_SLEEP_MODE_POWER_ON_DISABLE()     PW->CR1.W &= ~PW_CR1_SLP_CMP0_mask_w    /*!< Analog comparator CMP0 power-on configuration after enter SLEEP mode   */
#define __DRV_PW_CMP1_SLEEP_MODE_POWER_ON_DISABLE()     PW->CR1.W &= ~PW_CR1_SLP_CMP1_mask_w    /*!< Analog comparator CMP1 power-on configuration after enter SLEEP mode   */
#endif
#if defined(PW_CR1_SLP_CMP2_mask_w)
#define __DRV_PW_CMP2_SLEEP_MODE_POWER_ON_DISABLE()     PW->CR1.W &= ~PW_CR1_SLP_CMP2_mask_w    /*!< Analog comparator CMP2 power-on configuration after enter SLEEP mode   */
#define __DRV_PW_CMP3_SLEEP_MODE_POWER_ON_DISABLE()     PW->CR1.W &= ~PW_CR1_SLP_CMP3_mask_w    /*!< Analog comparator CMP3 power-on configuration after enter SLEEP mode   */
#endif
#if (defined(USB_TYPE))
#define __DRV_PW_USB_SLEEP_MODE_POWER_ON_DISABLE()      PW->CR1.W &= ~PW_CR1_SLP_USB_mask_w     /*!< USB0 power-on configuration after enter SLEEP mode                     */
#endif
//!@}


/**
 * @name PW_STOP_Mode_Power_On_Control
 *      PW STOP mode power on contrl
 */
//!@{
#if defined(PW_CR1_STP_CMP0_mask_w)
#define __DRV_PW_CMP0_STOP_MODE_POWER_ON_ENABLE()       PW->CR1.W |= PW_CR1_STP_CMP0_mask_w     /*!< Analog comparator CMP0 power-on configuration after enter STOP mode    */
#define __DRV_PW_CMP1_STOP_MODE_POWER_ON_ENABLE()       PW->CR1.W |= PW_CR1_STP_CMP1_mask_w     /*!< Analog comparator CMP1 power-on configuration after enter STOP mode    */
#endif
#if defined(PW_CR1_STP_CMP2_mask_w)
#define __DRV_PW_CMP2_STOP_MODE_POWER_ON_ENABLE()       PW->CR1.W |= PW_CR1_STP_CMP2_mask_w     /*!< Analog comparator CMP2 power-on configuration after enter STOP mode    */
#define __DRV_PW_CMP3_STOP_MODE_POWER_ON_ENABLE()       PW->CR1.W |= PW_CR1_STP_CMP3_mask_w     /*!< Analog comparator CMP3 power-on configuration after enter STOP mode    */
#endif
#if (defined(USB_TYPE))
#define __DRV_PW_USB_STOP_MODE_POWER_ON_ENABLE()        PW->CR1.W |= PW_CR1_STP_USB_mask_w      /*!< USB0 power-on configuration after enter STOP mode                      */
#endif
#define __DRV_PW_POR_STOP_MODE_POWER_ON_ENABLE()        PW->CR1.W |= PW_CR1_STP_POR_mask_w      /*!< POR power-on configuration after enter STOP mode                       */
#define __DRV_PW_BOD0_STOP_MODE_POWER_ON_ENABLE()       PW->CR1.W |= PW_CR1_STP_BOD0_mask_w     /*!< BOD0 power-on configuration after enter STOP mode                      */
#define __DRV_PW_BOD1_STOP_MODE_POWER_ON_ENABLE()       PW->CR1.W |= PW_CR1_STP_BOD1_mask_w     /*!< BOD1 power-on configuration after enter STOP mode                      */
#if defined(PW_CR1_STP_BOD2_mask_w)
#define __DRV_PW_BOD2_STOP_MODE_POWER_ON_ENABLE()       PW->CR1.W |= PW_CR1_STP_BOD2_mask_w     /*!< BOD2 power-on configuration after enter STOP mode                      */
#endif

#if defined(PW_CR1_STP_CMP0_mask_w)
#define __DRV_PW_CMP0_STOP_MODE_POWER_ON_DISABLE()      PW->CR1.W &= ~PW_CR1_STP_CMP0_mask_w    /*!< Analog comparator CMP0 power-on configuration after enter STOP mode    */
#define __DRV_PW_CMP1_STOP_MODE_POWER_ON_DISABLE()      PW->CR1.W &= ~PW_CR1_STP_CMP1_mask_w    /*!< Analog comparator CMP1 power-on configuration after enter STOP mode    */
#endif
#if defined(PW_CR1_STP_CMP2_mask_w)
#define __DRV_PW_CMP2_STOP_MODE_POWER_ON_DISABLE()      PW->CR1.W &= ~PW_CR1_STP_CMP2_mask_w    /*!< Analog comparator CMP2 power-on configuration after enter STOP mode    */
#define __DRV_PW_CMP3_STOP_MODE_POWER_ON_DISABLE()      PW->CR1.W &= ~PW_CR1_STP_CMP3_mask_w    /*!< Analog comparator CMP3 power-on configuration after enter STOP mode    */
#endif
#if (defined(USB_TYPE))
#define __DRV_PW_USB_STOP_MODE_POWER_ON_DISABLE()       PW->CR1.W &= ~PW_CR1_STP_USB_mask_w     /*!< USB0 power-on configuration after enter STOP mode                      */
#endif
#define __DRV_PW_POR_STOP_MODE_POWER_ON_DISABLE()       PW->CR1.W &= ~PW_CR1_STP_POR_mask_w     /*!< POR power-on configuration after enter STOP mode                       */
#define __DRV_PW_BOD0_STOP_MODE_POWER_ON_DISABLE()      PW->CR1.W &= ~PW_CR1_STP_BOD0_mask_w    /*!< BOD0 power-on configuration after enter STOP mode                      */
#define __DRV_PW_BOD1_STOP_MODE_POWER_ON_DISABLE()      PW->CR1.W &= ~PW_CR1_STP_BOD1_mask_w    /*!< BOD1 power-on configuration after enter STOP mode                      */
#if defined(PW_CR1_STP_BOD2_mask_w)
#define __DRV_PW_BOD2_STOP_MODE_POWER_ON_DISABLE()      PW->CR1.W &= ~PW_CR1_STP_BOD2_mask_w    /*!< BOD2 power-on configuration after enter STOP mode                      */
#endif
//!@}


/**
 * @name PW_STOP_Mode_Power_On_Control
 *      PW STOP mode power on contrl
 */
//!@{
#define __DRV_BOD0_STOP_MODE_WAKRUP_ENABLE()    PW->WKSTP0.W |= PW_WKSTP0_WKSTP_BOD0_mask_w     /*!< BOD0 voltage detection wakeup from STOP mode enable                    */
#define __DRV_BOD1_STOP_MODE_WAKRUP_ENABLE()    PW->WKSTP0.W |= PW_WKSTP0_WKSTP_BOD1_mask_w     /*!< BOD1 voltage detection wakeup from STOP mode enable                    */
#if defined(PW_WKSTP0_WKSTP_BOD2_mask_w)
#define __DRV_BOD2_STOP_MODE_WAKRUP_ENABLE()    PW->WKSTP0.W |= PW_WKSTP0_WKSTP_BOD2_mask_w     /*!< BOD1 voltage detection wakeup from STOP mode enable                    */
#endif
#if defined(PW_WKSTP0_WKSTP_CMP0_mask_w)
#define __DRV_CMP0_STOP_MODE_WAKRUP_ENABLE()    PW->WKSTP0.W |= PW_WKSTP0_WKSTP_CMP0_mask_w     /*!< Analog comparator CMP0 voltage detection wakeup from STOP mode enable  */
#define __DRV_CMP1_STOP_MODE_WAKRUP_ENABLE()    PW->WKSTP0.W |= PW_WKSTP0_WKSTP_CMP1_mask_w     /*!< Analog comparator CMP1 voltage detection wakeup from STOP mode enable  */
#endif
#if defined(PW_WKSTP0_WKSTP_CMP2_mask_w)
#define __DRV_CMP2_STOP_MODE_WAKRUP_ENABLE()    PW->WKSTP0.W |= PW_WKSTP0_WKSTP_CMP2_mask_w     /*!< Analog comparator CMP2 voltage detection wakeup from STOP mode enable  */
#define __DRV_CMP3_STOP_MODE_WAKRUP_ENABLE()    PW->WKSTP0.W |= PW_WKSTP0_WKSTP_CMP3_mask_w     /*!< Analog comparator CMP3 voltage detection wakeup from STOP mode enable  */
#endif
#if (defined(USB_TYPE))
#define __DRV_USB_STOP_MODE_WAKRUP_ENABLE()     PW->WKSTP0.W |= PW_WKSTP0_WKSTP_USB_mask_w      /*!< USB0 module event wakeup from STOP mode enable                         */
#endif
#define __DRV_RTC_STOP_MODE_WAKRUP_ENABLE()     PW->WKSTP1.W |= PW_WKSTP1_WKSTP_RTC_mask_w      /*!< RTC module events wakeup from STOP mode enable                         */
#define __DRV_IWDT_STOP_MODE_WAKRUP_ENABLE()    PW->WKSTP1.W |= PW_WKSTP1_WKSTP_IWDT_mask_w     /*!< IWDT module events wakeup from STOP mode enable                        */
#define __DRV_I2C0_STOP_MODE_WAKRUP_ENABLE()    PW->WKSTP1.W |= PW_WKSTP1_WKSTP_I2C0_mask_w     /*!< I2C0 slave address detection event wakeup from STOP mode enable        */
#if defined(PW_WKSTP1_WKSTP_I2C1_mask_w)
#define __DRV_I2C1_STOP_MODE_WAKRUP_ENABLE()    PW->WKSTP1.W |= PW_WKSTP1_WKSTP_I2C1_mask_w     /*!< I2C1 slave address detection event wakeup from STOP mode enabl         */
#endif

#define __DRV_BOD0_STOP_MODE_WAKRUP_DISABLE()   PW->WKSTP0.W &= ~PW_WKSTP0_WKSTP_BOD0_mask_w    /*!< BOD0 voltage detection wakeup from STOP mode enable                    */
#define __DRV_BOD1_STOP_MODE_WAKRUP_DISABLE()   PW->WKSTP0.W &= ~PW_WKSTP0_WKSTP_BOD1_mask_w    /*!< BOD1 voltage detection wakeup from STOP mode enable                    */
#if defined(PW_WKSTP0_WKSTP_BOD2_mask_w)
#define __DRV_BOD2_STOP_MODE_WAKRUP_DISABLE()   PW->WKSTP0.W &= ~PW_WKSTP0_WKSTP_BOD2_mask_w    /*!< BOD1 voltage detection wakeup from STOP mode enable                    */
#endif
#if defined(PW_WKSTP0_WKSTP_CMP0_mask_w)
#define __DRV_CMP0_STOP_MODE_WAKRUP_DISABLE()   PW->WKSTP0.W &= ~PW_WKSTP0_WKSTP_CMP0_mask_w    /*!< Analog comparator CMP0 voltage detection wakeup from STOP mode enable  */
#define __DRV_CMP1_STOP_MODE_WAKRUP_DISABLE()   PW->WKSTP0.W &= ~PW_WKSTP0_WKSTP_CMP1_mask_w    /*!< Analog comparator CMP1 voltage detection wakeup from STOP mode enable  */
#endif
#if defined(PW_WKSTP0_WKSTP_CMP2_mask_w)
#define __DRV_CMP2_STOP_MODE_WAKRUP_DISABLE()   PW->WKSTP0.W &= ~PW_WKSTP0_WKSTP_CMP2_mask_w    /*!< Analog comparator CMP2 voltage detection wakeup from STOP mode enable  */
#define __DRV_CMP3_STOP_MODE_WAKRUP_DISABLE()   PW->WKSTP0.W &= ~PW_WKSTP0_WKSTP_CMP3_mask_w    /*!< Analog comparator CMP3 voltage detection wakeup from STOP mode enable  */
#endif
#if (defined(USB_TYPE))
#define __DRV_USB_STOP_MODE_WAKRUP_DISABLE()    PW->WKSTP0.W &= ~PW_WKSTP0_WKSTP_USB_mask_w     /*!< USB0 module event wakeup from STOP mode enable                         */
#endif
#define __DRV_RTC_STOP_MODE_WAKRUP_DISABLE()    PW->WKSTP1.W &= ~PW_WKSTP1_WKSTP_RTC_mask_w     /*!< RTC module events wakeup from STOP mode enable                         */
#define __DRV_IWDT_STOP_MODE_WAKRUP_DISABLE()   PW->WKSTP1.W &= ~PW_WKSTP1_WKSTP_IWDT_mask_w    /*!< IWDT module events wakeup from STOP mode enable                        */
#define __DRV_I2C0_STOP_MODE_WAKRUP_DISABLE()   PW->WKSTP1.W &= ~PW_WKSTP1_WKSTP_I2C0_mask_w    /*!< I2C0 slave address detection event wakeup from STOP mode enable        */
#if defined(PW_WKSTP1_WKSTP_I2C1_mask_w)
#define __DRV_I2C1_STOP_MODE_WAKRUP_DISABLE()   PW->WKSTP1.W &= ~PW_WKSTP1_WKSTP_I2C1_mask_w    /*!< I2C1 slave address detection event wakeup from STOP mode enabl         */
#endif
//!@}


/**
 *******************************************************************************
 * @brief       Enable the specified PW interrupts.
 * @details  
 * @param[in]   "__INTERRUPT__" specifies the interrupt source to enable.
 *              This parameter can be one of the following values:
 *  @arg\b          PW_IT_WK: System received wakeup event interrupt enable
 *  @arg\b          PW_IT_BOD2: BOD2 brown-out detection interrupt enable
 *  @arg\b          PW_IT_BOD1: BOD1 brown-out detection interrupt enable
 *  @arg\b          PW_IT_BOD0: BOD0 brown-out detection interrupt enable
 *  @arg\b          PW_IT_IEA: PW interrupt all enable
 * @return      None
 * @note
 * @par         Example
 * @code
    __MID_PW_ENABLE_IT(PW_IT_WK | PW_IT_BOD1 | PW_IT_BOD0 | PW_IT_IEA);
 * @endcode
 *******************************************************************************
 */
#define __DRV_PW_ENABLE_IT(__INTERRUPT__)  SET_BIT(PW->INT.W, (__INTERRUPT__))


/**
 *******************************************************************************
 * @brief       Disable the specified PW interrupts.
 * @details  
 * @param[in]   "__INTERRUPT__" specifies the interrupt source to enable.
 *              This parameter can be one of the following values:
 *  @arg\b          PW_IT_WK: System received wakeup event interrupt enable
 *  @arg\b          PW_IT_BOD2: BOD2 brown-out detection interrupt enable
 *  @arg\b          PW_IT_BOD1: BOD1 brown-out detection interrupt enable
 *  @arg\b          PW_IT_BOD0: BOD0 brown-out detection interrupt enable
 *  @arg\b          PW_IT_IEA: PW interrupt all enable
 * @return      None
 * @note
 * @par         Example
 * @code
    __MID_PW_DISABLE_IT(PW_IT_WK | PW_IT_BOD1 | PW_IT_BOD0 | PW_IT_IEA);
 * @endcode
 *******************************************************************************
 */
#define __DRV_PW_DISABLE_IT(__INTERRUPT__)  CLEAR_BIT(PW->INT.W, (__INTERRUPT__))


/**
 *******************************************************************************
 * @brief       Check whether the specified PW flag is set or not.
 * @details  
 * @param[in]   "__FLAG__" specifies the flag to check.
 *              This parameter can be one of the following values:
 *  @arg\b          PW_FLAG_PORF: Power-On reset status flag
 *  @arg\b          PW_FLAG_BOD0F: BOD0 brown-out detection interrupt flag
 *  @arg\b          PW_FLAG_BOD1F: BOD1 brown-out detection interrupt flag
 *  @arg\b          PW_FLAG_BOD2F: BOD2 brown-out detection interrupt flag
 *  @arg\b          PW_FLAG_WKF: System received wakeup event flag
 * @return      The new state of __IT__ (SET or CLR).
 * @note
 * @par         Example
 * @code
    if(__DRV_PW_GET_FLAG(PW_FLAG_WKF))
 * @endcode
 *******************************************************************************
 */
#define __DRV_PW_GET_FLAG(__FLAG__) (((PW->STA.W) & (__FLAG__)) == (__FLAG__))


/**
 *******************************************************************************
 * @brief       Clear PW flag
 * @details  
 * @param[in]   "__FLAG__" specifies the flag to check.
 *              This parameter can be one of the following values:
 *  @arg\b          PW_FLAG_PORF: Power-On reset status flag
 *  @arg\b          PW_FLAG_BOD0F: BOD0 brown-out detection interrupt flag
 *  @arg\b          PW_FLAG_BOD1F: BOD1 brown-out detection interrupt flag
 *  @arg\b          PW_FLAG_BOD2F: BOD2 brown-out detection interrupt flag
 *  @arg\b          PW_FLAG_WKF: System received wakeup event flag
 * @return      
 * @note
 * @par         Example
 * @code
    __DRV_PW_CLEAR_FLAG(PW_FLAG_PORF);
 * @endcode
 *******************************************************************************
 */
#define __DRV_PW_CLEAR_FLAG(__FLAG__) ((PW->STA.W) = __FLAG__)


/**
 *******************************************************************************
 * @brief       Clear PW flag
 * @details  
 * @param[in]   "__DELAY__" specifies the flag to check.
 *              This parameter can be one of the following values:
 *  @arg\b          PW_WAKEUP_DLEAY_DT0: PW STOP mode wakeup delay DT0 (45 ~ 60us)
 *  @arg\b          PW_WAKEUP_DLEAY_DT1: PW STOP mode wakeup delay DT1 (60 ~ 75us)
 *  @arg\b          PW_WAKEUP_DLEAY_DT2: PW STOP mode wakeup delay DT2 (90 ~ 105us)
 *  @arg\b          PW_WAKEUP_DLEAY_DT3: PW STOP mode wakeup delay DT3 (150 ~ 165us)
 * @return      
 * @note
 * @par         Example
 * @code
    __DRV_PW_CLEAR_FLAG(PW_FLAG_PORF);
 * @endcode
 *******************************************************************************
 */
#define __DRV_PW_WAKEUP_DELAY_SELECT(__DELAY__)  MODIFY_REG(PW->CR0.B[2], PW_CR0_WKSTP_DSEL_mask_b2, __DELAY__)



void MID_PW_DeInit (void);
void MID_PW_EnterSLEEPMode (uint8_t SLEEPEntry);
void MID_PW_EnterSTOPMode (uint8_t STOPEntry);

void MID_PW_EnableSleepOnExit (void);
void MID_PW_DisableSleepOnExit (void);

void MID_PW_ConfigBOD1 (PW_BODxTypeDef *sConfigBOD2);

#if defined(PW_WKSTP0_WKSTP_BOD2_mask_w)
void MID_PW_ConfigBOD2 (PW_BODxTypeDef *sConfigBOD2);
#endif

void MID_PW_IRQHandler (void);

void MID_PW_BOD0Callback (void);
void MID_PW_BOD1Callback (void);
#if defined(PW_WKSTP0_WKSTP_BOD2_mask_w)
void MID_PW_BOD2Callback (void);
#endif
void MID_PW_WKCallback (void);
#endif




