/**
 ******************************************************************************
 *
 * @file        MG32x02z_RST_MID.h
 *
 * @brief       This is the C code format middleware head file for RST module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.03
 * @date        2022/09/22
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
#include "MG32x02z_RST.h"
#include "MG32x02z_CONF_MID.h" 


#ifndef _MG32x02z_RST_MID_H
/*!< _MG32x02z_RST_MID_H */ 
#define _MG32x02z_RST_MID_H


#ifdef __cplusplus
 extern "C" {
#endif

/**
 * @name RST_Flags_definition
 *      RST Flags Definition
 */
//!@{
#define RST_FLAG_PORF           RST_STA_PORF_mask_w         /*!< Power-on reset flag                                                    */
#define RST_FLAG_SWF            RST_STA_SWF_mask_w          /*!< Software forced reset flag                                             */
#define RST_FLAG_EXF            RST_STA_EXF_mask_w          /*!< External input reset flag                                              */
#define RST_FLAG_CPUF           RST_STA_CPUF_mask_w         /*!< CPU SYSRESETREQ bit system reset flag                                  */
#define RST_FLAG_BOD0F          RST_STA_BOD0F_mask_w        /*!< BOD0 reset flag                                                        */
#define RST_FLAG_BOD1F          RST_STA_BOD1F_mask_w        /*!< BOD1 reset flag                                                        */
#define RST_FLAG_LPMF           RST_STA_LPMF_mask_w         /*!< Low power mode reset flag                                              */
#if defined(RST_STA_BOD2F_mask_w)
#define RST_FLAG_BOD2F          RST_STA_BOD2F_mask_w        /*!< BOD2 reset flag                                                        */
#endif
#define RST_FLAG_CSCF           RST_STA_CSCF_mask_w         /*!< CSC missing clock detect reset flag                                    */
#define RST_FLAG_MEMF           RST_STA_MEMF_mask_w         /*!< Flash memory read/write protect or illegal address error reset flag    */
#define RST_FLAG_IWDTF          RST_STA_IWDTF_mask_w        /*!< IWDT reset flag                                                        */
#define RST_FLAG_WWDTF          RST_STA_WWDTF_mask_w        /*!< WWDT reset flag                                                        */
#define RST_FLAG_ADCF           RST_STA_ADCF_mask_w         /*!< ADC analog voltage watch-dog reset flag                                */
#if defined(RST_STA_CMP0F_mask_w)
#define RST_FLAG_CMP0F          RST_STA_CMP0F_mask_w        /*!< Comparator CMP0 threshold comparison reset flag                        */
#define RST_FLAG_CMP1F          RST_STA_CMP1F_mask_w        /*!< Comparator CMP1 threshold comparison reset flag                        */
#endif
#if defined(RST_STA_CMP2F_mask_w)
#define RST_FLAG_CMP2F          RST_STA_CMP2F_mask_w        /*!< Comparator CMP2 threshold comparison reset flag                        */
#define RST_FLAG_CMP3F          RST_STA_CMP3F_mask_w        /*!< Comparator CMP3 threshold comparison reset flag                        */
#endif
#define RST_FLAG_WRF            RST_STA_WRF_mask_w          /*!< Warm reset flag                                                        */
#define RST_FLAG_CRF            RST_STA_CRF_mask_w          /*!< Cold reset flag                                                        */
//!@}


#define __DRV_RST_TRIGGER_SWRESET() SET_BIT(RST_Base->STA.W, RST_CR0_SW_EN_mask_w)    /*!< System software forced reset enable for whole chip reset   */


/**
 *******************************************************************************
 * @brief       Check whether the specified RST flag is set or not.
 * @details  
 * @param[in]   "__FLAG__" specifies the flag to check.
 *              This parameter can be one of the following values:
 *  @arg\b          RST_FLAG_PORF: Power-on reset flag
 *  @arg\b          RST_FLAG_SWF: Software forced reset flag
 *  @arg\b          RST_FLAG_EXF: External input reset flag
 *  @arg\b          RST_FLAG_CPUF: CPU SYSRESETREQ bit system reset flag
 *  @arg\b          RST_FLAG_BOD0F: BOD0 reset flag
 *  @arg\b          RST_FLAG_BOD1F: BOD1 reset flag
 *  @arg\b          RST_FLAG_LPMF: Low power mode reset flag
 *  @arg\b          RST_FLAG_BOD2F: BOD2 reset flag
 *  @arg\b          RST_FLAG_CSCF: CSC missing clock detect reset flag
 *  @arg\b          RST_FLAG_MEMF: Flash memory read/write protect or illegal address error reset flag
 *  @arg\b          RST_FLAG_IWDTF: IWDT reset flag
 *  @arg\b          RST_FLAG_WWDTF: WWDT reset flag
 *  @arg\b          RST_FLAG_ADCF: ADC analog voltage watch-dog reset flag
 *  @arg\b          RST_FLAG_CMP0F: Comparator CMP0 threshold comparison reset flag
 *  @arg\b          RST_FLAG_CMP1F: Comparator CMP1 threshold comparison reset flag
 *  @arg\b          RST_FLAG_CMP2F: Comparator CMP2 threshold comparison reset flag
 *  @arg\b          RST_FLAG_CMP3F: Comparator CMP3 threshold comparison reset flag
 *  @arg\b          RST_FLAG_WRF: Warm reset flag
 *  @arg\b          RST_FLAG_CRF: Cold reset flag
 * @return      The new state of __IT__ (SET or CLR).
 * @note
 * @par         Example
 * @code
    if(__DRV_RST_GET_FLAG(RST_FLAG_CSCF))
 * @endcode
 *******************************************************************************
 */
#define __DRV_RST_GET_FLAG(__FLAG__) (((RST_Base->STA.W) & (__FLAG__)) == (__FLAG__))


/**
 *******************************************************************************
 * @brief       Clear RST flag
 * @details  
 * @param[in]   "__FLAG__" specifies the flag to check.
 *              This parameter can be one of the following values:
 *  @arg\b          RST_FLAG_PORF: Power-on reset flag
 *  @arg\b          RST_FLAG_SWF: Software forced reset flag
 *  @arg\b          RST_FLAG_EXF: External input reset flag
 *  @arg\b          RST_FLAG_CPUF: CPU SYSRESETREQ bit system reset flag
 *  @arg\b          RST_FLAG_BOD0F: BOD0 reset flag
 *  @arg\b          RST_FLAG_BOD1F: BOD1 reset flag
 *  @arg\b          RST_FLAG_LPMF: Low power mode reset flag
 *  @arg\b          RST_FLAG_BOD2F: BOD2 reset flag
 *  @arg\b          RST_FLAG_CSCF: CSC missing clock detect reset flag
 *  @arg\b          RST_FLAG_MEMF: Flash memory read/write protect or illegal address error reset flag
 *  @arg\b          RST_FLAG_IWDTF: IWDT reset flag
 *  @arg\b          RST_FLAG_WWDTF: WWDT reset flag
 *  @arg\b          RST_FLAG_ADCF: ADC analog voltage watch-dog reset flag
 *  @arg\b          RST_FLAG_CMP0F: Comparator CMP0 threshold comparison reset flag
 *  @arg\b          RST_FLAG_CMP1F: Comparator CMP1 threshold comparison reset flag
 *  @arg\b          RST_FLAG_CMP2F: Comparator CMP2 threshold comparison reset flag
 *  @arg\b          RST_FLAG_CMP3F: Comparator CMP3 threshold comparison reset flag
 *  @arg\b          RST_FLAG_WRF: Warm reset flag
 *  @arg\b          RST_FLAG_CRF: Cold reset flag
 * @return      None
 * @note
 * @par         Example
 * @code
    __DRV_RST_CLEAR_FLAG(RST_FLAG_CSCF);
 * @endcode
 *******************************************************************************
 */
#define __DRV_RST_CLEAR_FLAG(__FLAG__) ((RST_Base->STA.W) = __FLAG__)


/**
 * @name RST_Periphery_Cold_Reset_Enable_Disable
 *      RST Periphery Cold Reset Enable/Disable
 */
//!@{
#define __DRV_RST_SW_COLD_RESET_ENABLE()        RST_Base->CE.W |= RST_CE_SW_CE_mask_w        /*!< Software forced Cold reset enable                                          */
#define __DRV_RST_EX_COLD_RESET_ENABLE()        RST_Base->CE.W |= RST_CE_EX_CE_mask_w        /*!< External input Cold reset enable                                           */
#define __DRV_RST_CPU_COLD_RESET_ENABLE()       RST_Base->CE.W |= RST_CE_CPU_CE_mask_w       /*!< CPU SYSRESETREQ bit forced Cold reset enable                               */
#define __DRV_RST_BOD0_COLD_RESET_ENABLE()      RST_Base->CE.W |= RST_CE_BOD0_CE_mask_w      /*!< BOD0 Cold reset enable                                                     */
#define __DRV_RST_BOD1_COLD_RESET_ENABLE()      RST_Base->CE.W |= RST_CE_BOD1_CE_mask_w      /*!< BOD1 Cold reset enable                                                     */
#if defined(RST_CE_BOD2_CE_mask_w)
#define __DRV_RST_BOD2_COLD_RESET_ENABLE()      RST_Base->CE.W |= RST_CE_BOD2_CE_mask_w      /*!< BOD2 Cold reset enable                                                     */
#endif
#define __DRV_RST_LPM_COLD_RESET_ENABLE()       RST_Base->CE.W |= RST_CE_LPM_CE_mask_w       /*!< Low power STOP mode Cold reset enable                                      */
#define __DRV_RST_CSC_COLD_RESET_ENABLE()       RST_Base->CE.W |= RST_CE_CSC_CE_mask_w       /*!< CSC missing clock detect Cold reset enable                                 */
#define __DRV_RST_MEM_COLD_RESET_ENABLE()       RST_Base->CE.W |= RST_CE_MEM_CE_mask_w       /*!< Flash memory read/write protect or illegal address error Cold reset enable */
#define __DRV_RST_IWDT_COLD_RESET_ENABLE()      RST_Base->CE.W |= RST_CE_IWDT_CE_mask_w      /*!< IWDT Cold reset enable                                                     */
#define __DRV_RST_WWDT_COLD_RESET_ENABLE()      RST_Base->CE.W |= RST_CE_WWDT_CE_mask_w      /*!< WWDT Cold reset enable                                                     */
#define __DRV_RST_ADC_COLD_RESET_ENABLE()       RST_Base->CE.W |= RST_CE_ADC_CE_mask_w       /*!< ADC analog voltage watch-dog Cold reset enable                             */
#if defined(RST_CE_CMP0_CE_mask_w)
#define __DRV_RST_CMP0_COLD_RESET_ENABLE()      RST_Base->CE.W |= RST_CE_CMP0_CE_mask_w      /*!< Comparator CMP0 threshold comparison Cold reset enable                     */
#define __DRV_RST_CMP1_COLD_RESET_ENABLE()      RST_Base->CE.W |= RST_CE_CMP1_CE_mask_w      /*!< Comparator CMP1 threshold comparison Cold reset enable                     */
#endif
#if defined(RST_CE_CMP2_CE_mask_w)
#define __DRV_RST_CMP2_COLD_RESET_ENABLE()      RST_Base->CE.W |= RST_CE_CMP2_CE_mask_w      /*!< Comparator CMP2 threshold comparison Cold reset enable                     */
#define __DRV_RST_CMP3_COLD_RESET_ENABLE()      RST_Base->CE.W |= RST_CE_CMP3_CE_mask_w      /*!< Comparator CMP3 threshold comparison Cold reset enable                     */
#endif


#define __DRV_RST_SW_COLD_RESET_DISABLE()       RST_Base->CE.W &= ~RST_CE_SW_CE_mask_w        /*!< Software forced Cold reset disable                                            */
#define __DRV_RST_EX_COLD_RESET_DISABLE()       RST_Base->CE.W &= ~RST_CE_EX_CE_mask_w        /*!< External input Cold reset disable                                             */
#define __DRV_RST_CPU_COLD_RESET_DISABLE()      RST_Base->CE.W &= ~RST_CE_CPU_CE_mask_w       /*!< CPU SYSRESETREQ bit forced Cold reset disable                                 */
#define __DRV_RST_BOD0_COLD_RESET_DISABLE()     RST_Base->CE.W &= ~RST_CE_BOD0_CE_mask_w      /*!< BOD0 Cold reset disable                                                       */
#define __DRV_RST_BOD1_COLD_RESET_DISABLE()     RST_Base->CE.W &= ~RST_CE_BOD1_CE_mask_w      /*!< BOD1 Cold reset disable                                                       */
                                                                                                                                                                    
#define __DRV_RST_BOD2_COLD_RESET_DISABLE()     RST_Base->CE.W &= ~RST_CE_BOD2_CE_mask_w      /*!< BOD2 Cold reset disable                                                       */
                                                                                                                                                                   
#define __DRV_RST_LPM_COLD_RESET_DISABLE()      RST_Base->CE.W &= ~RST_CE_LPM_CE_mask_w       /*!< Low power STOP mode Cold reset disable                                        */
#define __DRV_RST_CSC_COLD_RESET_DISABLE()      RST_Base->CE.W &= ~RST_CE_CSC_CE_mask_w       /*!< CSC missing clock detect Cold reset disable                                   */
#define __DRV_RST_MEM_COLD_RESET_DISABLE()      RST_Base->CE.W &= ~RST_CE_MEM_CE_mask_w       /*!< Flash memory read/write protect or illegal address error Cold reset disable   */
#define __DRV_RST_IWDT_COLD_RESET_DISABLE()     RST_Base->CE.W &= ~RST_CE_IWDT_CE_mask_w      /*!< IWDT Cold reset disable                                                       */
#define __DRV_RST_WWDT_COLD_RESET_DISABLE()     RST_Base->CE.W &= ~RST_CE_WWDT_CE_mask_w      /*!< WWDT Cold reset disable                                                       */
#define __DRV_RST_ADC_COLD_RESET_DISABLE()      RST_Base->CE.W &= ~RST_CE_ADC_CE_mask_w       /*!< ADC analog voltage watch-dog Cold reset disable                               */
#if defined(RST_CE_CMP0_CE_mask_w)
#define __DRV_RST_CMP0_COLD_RESET_DISABLE()     RST_Base->CE.W &= ~RST_CE_CMP0_CE_mask_w      /*!< Comparator CMP0 threshold comparison Cold reset disable                       */
#define __DRV_RST_CMP1_COLD_RESET_DISABLE()     RST_Base->CE.W &= ~RST_CE_CMP1_CE_mask_w      /*!< Comparator CMP1 threshold comparison Cold reset disable                       */
#endif
#if defined(RST_CE_CMP2_CE_mask_w)                                                                                                                                                                   
#define __DRV_RST_CMP2_COLD_RESET_DISABLE()     RST_Base->CE.W &= ~RST_CE_CMP2_CE_mask_w      /*!< Comparator CMP2 threshold comparison Cold reset disable                       */
#define __DRV_RST_CMP3_COLD_RESET_DISABLE()     RST_Base->CE.W &= ~RST_CE_CMP3_CE_mask_w      /*!< Comparator CMP3 threshold comparison Cold reset disable                       */
#endif
//!@}


/**
 * @name RST_Periphery_Warm_Reset_Enable_Disable
 *      RST Periphery Warm Reset Enable/Disable
 */
//!@{
#define __DRV_RST_SW_WARM_RESET_ENABLE()        RST_Base->WE.W |= RST_WE_SW_WE_mask_w        /*!< Software forced Warm reset enable                                          */
#define __DRV_RST_EX_WARM_RESET_ENABLE()        RST_Base->WE.W |= RST_WE_EX_WE_mask_w        /*!< External input Warm reset enable                                           */
#define __DRV_RST_CPU_WARM_RESET_ENABLE()       RST_Base->WE.W |= RST_WE_CPU_WE_mask_w       /*!< CPU SYSRESETREQ bit forced Warm reset enable                               */
#define __DRV_RST_BOD0_WARM_RESET_ENABLE()      RST_Base->WE.W |= RST_WE_BOD0_WE_mask_w      /*!< BOD0 Warm reset enable                                                     */
#define __DRV_RST_BOD1_WARM_RESET_ENABLE()      RST_Base->WE.W |= RST_WE_BOD1_WE_mask_w      /*!< BOD1 Warm reset enable                                                     */
#if defined(RST_WE_BOD2_WE_mask_w)
#define __DRV_RST_BOD2_WARM_RESET_ENABLE()      RST_Base->WE.W |= RST_WE_BOD2_WE_mask_w      /*!< BOD2 Warm reset enable                                                     */
#endif
#define __DRV_RST_LPM_WARM_RESET_ENABLE()       RST_Base->WE.W |= RST_WE_LPM_WE_mask_w       /*!< Low power STOP mode Warm reset enable                                      */
#define __DRV_RST_CSC_WARM_RESET_ENABLE()       RST_Base->WE.W |= RST_WE_CSC_WE_mask_w       /*!< CSC missing clock detect Warm reset enable                                 */
#define __DRV_RST_MEM_WARM_RESET_ENABLE()       RST_Base->WE.W |= RST_WE_MEM_WE_mask_w       /*!< Flash memory read/write protect or illegal address error Warm reset enable */
#define __DRV_RST_IWDT_WARM_RESET_ENABLE()      RST_Base->WE.W |= RST_WE_IWDT_WE_mask_w      /*!< IWDT Warm reset enable                                                     */
#define __DRV_RST_WWDT_WARM_RESET_ENABLE()      RST_Base->WE.W |= RST_WE_WWDT_WE_mask_w      /*!< WWDT Warm reset enable                                                     */
#define __DRV_RST_ADC_WARM_RESET_ENABLE()       RST_Base->WE.W |= RST_WE_ADC_WE_mask_w       /*!< ADC analog voltage watch-dog Warm reset enable                             */
#if defined(RST_WE_CMP0_WE_mask_w)
#define __DRV_RST_CMP0_WARM_RESET_ENABLE()      RST_Base->WE.W |= RST_WE_CMP0_WE_mask_w      /*!< Comparator CMP0 threshold comparison Warm reset enable                     */
#define __DRV_RST_CMP1_WARM_RESET_ENABLE()      RST_Base->WE.W |= RST_WE_CMP1_WE_mask_w      /*!< Comparator CMP1 threshold comparison Warm reset enable                     */
#endif
#if defined(RST_WE_CMP2_WE_mask_w)
#define __DRV_RST_CMP2_WARM_RESET_ENABLE()      RST_Base->WE.W |= RST_WE_CMP2_WE_mask_w      /*!< Comparator CMP2 threshold comparison Warm reset enable                     */
#define __DRV_RST_CMP3_WARM_RESET_ENABLE()      RST_Base->WE.W |= RST_WE_CMP3_WE_mask_w      /*!< Comparator CMP3 threshold comparison Warm reset enable                     */
#endif 


#define __DRV_RST_SW_WARM_RESET_DISABLE()       RST_Base->WE.W &= ~RST_WE_SW_WE_mask_w        /*!< Software forced Warm reset disable                                            */
#define __DRV_RST_EX_WARM_RESET_DISABLE()       RST_Base->WE.W &= ~RST_WE_EX_WE_mask_w        /*!< External input Warm reset disable                                             */
#define __DRV_RST_CPU_WARM_RESET_DISABLE()      RST_Base->WE.W &= ~RST_WE_CPU_WE_mask_w       /*!< CPU SYSRESETREQ bit forced Warm reset disable                                 */
#define __DRV_RST_BOD0_WARM_RESET_DISABLE()     RST_Base->WE.W &= ~RST_WE_BOD0_WE_mask_w      /*!< BOD0 Warm reset disable                                                       */
#define __DRV_RST_BOD1_WARM_RESET_DISABLE()     RST_Base->WE.W &= ~RST_WE_BOD1_WE_mask_w      /*!< BOD1 Warm reset disable                                                       */
#if defined(RST_WE_BOD2_WE_mask_w)
#define __DRV_RST_BOD2_WARM_RESET_DISABLE()     RST_Base->WE.W &= ~RST_WE_BOD2_WE_mask_w      /*!< BOD2 Warm reset disable                                                       */
#endif
#define __DRV_RST_LPM_WARM_RESET_DISABLE()      RST_Base->WE.W &= ~RST_WE_LPM_WE_mask_w       /*!< Low power STOP mode Warm reset disable                                        */
#define __DRV_RST_CSC_WARM_RESET_DISABLE()      RST_Base->WE.W &= ~RST_WE_CSC_WE_mask_w       /*!< CSC missing clock detect Warm reset disable                                   */
#define __DRV_RST_MEM_WARM_RESET_DISABLE()      RST_Base->WE.W &= ~RST_WE_MEM_WE_mask_w       /*!< Flash memory read/write protect or illegal address error Warm reset disable   */
#define __DRV_RST_IWDT_WARM_RESET_DISABLE()     RST_Base->WE.W &= ~RST_WE_IWDT_WE_mask_w      /*!< IWDT Warm reset disable                                                       */
#define __DRV_RST_WWDT_WARM_RESET_DISABLE()     RST_Base->WE.W &= ~RST_WE_WWDT_WE_mask_w      /*!< WWDT Warm reset disable                                                       */
#define __DRV_RST_ADC_WARM_RESET_DISABLE()      RST_Base->WE.W &= ~RST_WE_ADC_WE_mask_w       /*!< ADC analog voltage watch-dog Warm reset disable                               */
#if defined(RST_WE_CMP0_WE_mask_w)
#define __DRV_RST_CMP0_WARM_RESET_DISABLE()     RST_Base->WE.W &= ~RST_WE_CMP0_WE_mask_w      /*!< Comparator CMP0 threshold comparison Warm reset disable                       */
#define __DRV_RST_CMP1_WARM_RESET_DISABLE()     RST_Base->WE.W &= ~RST_WE_CMP1_WE_mask_w      /*!< Comparator CMP1 threshold comparison Warm reset disable                       */
#endif
#if defined(RST_WE_CMP2_WE_mask_w)
#define __DRV_RST_CMP2_WARM_RESET_DISABLE()     RST_Base->WE.W &= ~RST_WE_CMP2_WE_mask_w      /*!< Comparator CMP2 threshold comparison Warm reset disable                       */
#define __DRV_RST_CMP3_WARM_RESET_DISABLE()     RST_Base->WE.W &= ~RST_WE_CMP3_WE_mask_w      /*!< Comparator CMP3 threshold comparison Warm reset disable                       */
#endif
//!@}


/**
 * @name RST_Periphery_Force_Reset
 *      RST Periphery Force Reset
 */
//!@{
#define __DRV_RST_IOPA_FORCE_RESET()        RST_Base->AHB.W |= RST_AHB_IOPA_EN_mask_w    /*!< System software forced reset enable for IO Port-A */
#define __DRV_RST_IOPB_FORCE_RESET()        RST_Base->AHB.W |= RST_AHB_IOPB_EN_mask_w    /*!< System software forced reset enable for IO Port-B */
#define __DRV_RST_IOPC_FORCE_RESET()        RST_Base->AHB.W |= RST_AHB_IOPC_EN_mask_w    /*!< System software forced reset enable for IO Port-C */
#define __DRV_RST_IOPD_FORCE_RESET()        RST_Base->AHB.W |= RST_AHB_IOPD_EN_mask_w    /*!< System software forced reset enable for IO Port-D */
#if defined(RST_AHB_IOPE_EN_mask_w)
#define __DRV_RST_IOPE_FORCE_RESET()        RST_Base->AHB.W |= RST_AHB_IOPE_EN_mask_w    /*!< System software forced reset enable for IO Port-E */
#endif
#define __DRV_RST_GPL_FORCE_RESET()         RST_Base->AHB.W |= RST_AHB_GPL_EN_mask_w     /*!< System software forced reset enable for GPL module */
#if defined(RST_AHB_EMB_EN_mask_w)
#define __DRV_RST_EMB_FORCE_RESET()         RST_Base->AHB.W |= RST_AHB_EMB_EN_mask_w     /*!< System software forced reset enable for EMB module */
#endif                
#define __DRV_RST_ADC0_FORCE_RESET()        RST_Base->APB0.W |= RST_APB0_ADC0_EN_mask_w  /*!< System software forced reset enable for ADC0 module */
#if defined(RST_APB0_CMP_EN_mask_w)
#define __DRV_RST_CMP_FORCE_RESET()         RST_Base->APB0.W |= RST_APB0_CMP_EN_mask_w   /*!< System software forced reset enable for CMP module*/
#endif
#if defined(RST_APB0_DAC_EN_mask_w)
#define __DRV_RST_DAC_FORCE_RESET()         RST_Base->APB0.W |= RST_APB0_DAC_EN_mask_w   /*!< System software forced reset enable for DAC module*/
#endif
#define __DRV_RST_RTC_FORCE_RESET()         RST_Base->APB0.W |= RST_APB0_RTC_EN_mask_w   /*!< System software forced reset enable for RTC module*/
#define __DRV_RST_IWDT_FORCE_RESET()        RST_Base->APB0.W |= RST_APB0_IWDT_EN_mask_w  /*!< System software forced reset enable for IWDT module*/
#define __DRV_RST_WWDT_FORCE_RESET()        RST_Base->APB0.W |= RST_APB0_WWDT_EN_mask_w  /*!< System software forced reset enable for WWDT module*/
#define __DRV_RST_I2C0_FORCE_RESET()        RST_Base->APB0.W |= RST_APB0_I2C0_EN_mask_w  /*!< System software forced reset enable for I2C0 module*/
#if defined(RST_APB0_I2C1_EN_mask_w)
#define __DRV_RST_I2C1_FORCE_RESET()        RST_Base->APB0.W |= RST_APB0_I2C1_EN_mask_w  /*!< System software forced reset enable for I2C1 module*/
#endif
#define __DRV_RST_SPI0_FORCE_RESET()        RST_Base->APB0.W |= RST_APB0_SPI0_EN_mask_w  /*!< System software forced reset enable for SPI0 module*/
#define __DRV_RST_URT0_FORCE_RESET()        RST_Base->APB0.W |= RST_APB0_URT0_EN_mask_w  /*!< System software forced reset enable for URT0 module*/
#define __DRV_RST_URT1_FORCE_RESET()        RST_Base->APB0.W |= RST_APB0_URT1_EN_mask_w  /*!< System software forced reset enable for URT1 module*/
#if defined(RST_APB0_URT2_EN_mask_w)
#define __DRV_RST_URT2_FORCE_RESET()        RST_Base->APB0.W |= RST_APB0_URT2_EN_mask_w  /*!< System software forced reset enable for URT2 module*/
#endif
#if defined(RST_APB0_URT3_EN_mask_w)
#define __DRV_RST_URT3_FORCE_RESET()        RST_Base->APB0.W |= RST_APB0_URT3_EN_mask_w  /*!< System software forced reset enable for URT3 module*/
#endif
#if defined(RST_APB0_URT4_EN_mask_w)
#define __DRV_RST_URT4_FORCE_RESET()        RST_Base->APB0.W |= RST_APB0_URT4_EN_mask_w  /*!< System software forced reset enable for URT4 module*/
#endif
#if defined(RST_APB0_URT5_EN_mask_w)
#define __DRV_RST_URT5_FORCE_RESET()        RST_Base->APB0.W |= RST_APB0_URT5_EN_mask_w  /*!< System software forced reset enable for URT5 module*/
#define __DRV_RST_URT6_FORCE_RESET()        RST_Base->APB0.W |= RST_APB0_URT6_EN_mask_w  /*!< System software forced reset enable for URT6 module*/
#define __DRV_RST_URT7_FORCE_RESET()        RST_Base->APB0.W |= RST_APB0_URT7_EN_mask_w  /*!< System software forced reset enable for URT7 module*/
#endif
#if (defined(USB_TYPE))
#define __DRV_RST_USB_FORCE_RESET()         RST_Base->APB0.W |= RST_APB0_USB_EN_mask_w   /*!< System software forced reset enable for USB module*/
#endif
#if defined(RST_APB0_APX_EN_mask_w)
#define __DRV_RST_APX_FORCE_RESET()         RST_Base->APB0.W |= RST_APB0_APX_EN_mask_w   /*!< System software forced reset enable for APX module*/
#endif            
                                            
#define __DRV_RST_TM00_FORCE_RESET()        RST_Base->APB1.W |= RST_APB1_TM00_EN_mask_w  /*!< System software forced reset enable for TM00 module*/
#define __DRV_RST_TM01_FORCE_RESET()        RST_Base->APB1.W |= RST_APB1_TM01_EN_mask_w  /*!< System software forced reset enable for TM01 module*/
#define __DRV_RST_TM10_FORCE_RESET()        RST_Base->APB1.W |= RST_APB1_TM10_EN_mask_w  /*!< System software forced reset enable for TM10 module*/
#define __DRV_RST_TM16_FORCE_RESET()        RST_Base->APB1.W |= RST_APB1_TM16_EN_mask_w  /*!< System software forced reset enable for TM16 module*/
#if defined(RST_APB1_TM20_EN_mask_w)
#define __DRV_RST_TM20_FORCE_RESET()        RST_Base->APB1.W |= RST_APB1_TM20_EN_mask_w  /*!< System software forced reset enable for TM20 module*/
#endif
#if defined(RST_APB1_TM26_EN_mask_w)
#define __DRV_RST_TM26_FORCE_RESET()        RST_Base->APB1.W |= RST_APB1_TM26_EN_mask_w  /*!< System software forced reset enable for TM26 module*/
#endif
#define __DRV_RST_TM36_FORCE_RESET()        RST_Base->APB1.W |= RST_APB1_TM36_EN_mask_w  /*!< System software forced reset enable for TM36 module*/


#define __DRV_RST_IOPA_RELEASE_RESET()      RST_Base->AHB.W &= ~RST_AHB_IOPA_EN_mask_w       /*!< System software release reset enable for IO Port-A */
#define __DRV_RST_IOPB_RELEASE_RESET()      RST_Base->AHB.W &= ~RST_AHB_IOPB_EN_mask_w       /*!< System software release reset enable for IO Port-B */
#define __DRV_RST_IOPC_RELEASE_RESET()      RST_Base->AHB.W &= ~RST_AHB_IOPC_EN_mask_w       /*!< System software release reset enable for IO Port-C */
#define __DRV_RST_IOPD_RELEASE_RESET()      RST_Base->AHB.W &= ~RST_AHB_IOPD_EN_mask_w       /*!< System software release reset enable for IO Port-D */
#if defined(RST_AHB_IOPE_EN_mask_w)
#define __DRV_RST_IOPE_RELEASE_RESET()      RST_Base->AHB.W &= ~RST_AHB_IOPE_EN_mask_w       /*!< System software release reset enable for IO Port-E */
#endif
#define __DRV_RST_GPL_RELEASE_RESET()       RST_Base->AHB.W &= ~RST_AHB_GPL_EN_mask_w        /*!< System software release reset enable for GPL module */
#if defined(RST_AHB_EMB_EN_mask_w)
#define __DRV_RST_EMB_RELEASE_RESET()       RST_Base->AHB.W &= ~RST_AHB_EMB_EN_mask_w        /*!< System software release reset enable for EMB module */
#endif
#define __DRV_RST_ADC0_RELEASE_RESET()      RST_Base->APB0.W &= ~RST_APB0_ADC0_EN_mask_w     /*!< System software release reset enable for ADC0 module */
#define __DRV_RST_CMP_RELEASE_RESET()       RST_Base->APB0.W &= ~RST_APB0_CMP_EN_mask_w      /*!< System software release reset enable for CMP module*/
#if defined(RST_APB0_DAC_EN_mask_w)
#define __DRV_RST_DAC_RELEASE_RESET()       RST_Base->APB0.W &= ~RST_APB0_DAC_EN_mask_w      /*!< System software release reset enable for DAC module*/
#endif
#define __DRV_RST_RTC_RELEASE_RESET()       RST_Base->APB0.W &= ~RST_APB0_RTC_EN_mask_w      /*!< System software release reset enable for RTC module*/
#define __DRV_RST_IWDT_RELEASE_RESET()      RST_Base->APB0.W &= ~RST_APB0_IWDT_EN_mask_w     /*!< System software release reset enable for IWDT module*/
#define __DRV_RST_WWDT_RELEASE_RESET()      RST_Base->APB0.W &= ~RST_APB0_WWDT_EN_mask_w     /*!< System software release reset enable for WWDT module*/
#define __DRV_RST_I2C0_RELEASE_RESET()      RST_Base->APB0.W &= ~RST_APB0_I2C0_EN_mask_w     /*!< System software release reset enable for I2C0 module*/
#if defined(RST_APB0_I2C1_EN_mask_w)
#define __DRV_RST_I2C1_RELEASE_RESET()      RST_Base->APB0.W &= ~RST_APB0_I2C1_EN_mask_w     /*!< System software release reset enable for I2C1 module*/
#endif
#define __DRV_RST_SPI0_RELEASE_RESET()      RST_Base->APB0.W &= ~RST_APB0_SPI0_EN_mask_w     /*!< System software release reset enable for SPI0 module*/
#define __DRV_RST_URT0_RELEASE_RESET()      RST_Base->APB0.W &= ~RST_APB0_URT0_EN_mask_w     /*!< System software release reset enable for URT0 module*/
#define __DRV_RST_URT1_RELEASE_RESET()      RST_Base->APB0.W &= ~RST_APB0_URT1_EN_mask_w     /*!< System software release reset enable for URT1 module*/
#if defined(RST_APB0_URT2_EN_mask_w)
#define __DRV_RST_URT2_RELEASE_RESET()      RST_Base->APB0.W &= ~RST_APB0_URT2_EN_mask_w     /*!< System software release reset enable for URT2 module*/
#endif
#if defined(RST_APB0_URT3_EN_mask_w)
#define __DRV_RST_URT3_RELEASE_RESET()      RST_Base->APB0.W &= ~RST_APB0_URT3_EN_mask_w     /*!< System software release reset enable for URT3 module*/
#endif
#if defined(RST_APB0_URT4_EN_mask_w)
#define __DRV_RST_URT4_RELEASE_RESET()      RST_Base->APB0.W &= ~RST_APB0_URT4_EN_mask_w     /*!< System software release reset enable for URT4 module*/
#endif
#if defined(RST_APB0_URT5_EN_mask_w)
#define __DRV_RST_URT5_RELEASE_RESET()      RST_Base->APB0.W &= ~RST_APB0_URT5_EN_mask_w     /*!< System software release reset enable for URT5 module*/
#define __DRV_RST_URT6_RELEASE_RESET()      RST_Base->APB0.W &= ~RST_APB0_URT6_EN_mask_w     /*!< System software release reset enable for URT6 module*/
#define __DRV_RST_URT7_RELEASE_RESET()      RST_Base->APB0.W &= ~RST_APB0_URT7_EN_mask_w     /*!< System software release reset enable for URT7 module*/
#endif
#if (defined(USB_TYPE))
#define __DRV_RST_USB_RELEASE_RESET()       RST_Base->APB0.W &= ~RST_APB0_USB_EN_mask_w      /*!< System software release reset enable for USB module*/
#endif
#if defined(RST_APB0_APX_EN_mask_w)
#define __DRV_RST_APX_RELEASE_RESET()       RST_Base->APB0.W &= ~RST_APB0_APX_EN_mask_w      /*!< System software release reset enable for APX module*/
#endif
#define __DRV_RST_TM00_RELEASE_RESET()      RST_Base->APB1.W &= ~RST_APB1_TM00_EN_mask_w     /*!< System software release reset enable for TM00 module*/
#define __DRV_RST_TM01_RELEASE_RESET()      RST_Base->APB1.W &= ~RST_APB1_TM01_EN_mask_w     /*!< System software release reset enable for TM01 module*/
#define __DRV_RST_TM10_RELEASE_RESET()      RST_Base->APB1.W &= ~RST_APB1_TM10_EN_mask_w     /*!< System software release reset enable for TM10 module*/
#define __DRV_RST_TM16_RELEASE_RESET()      RST_Base->APB1.W &= ~RST_APB1_TM16_EN_mask_w     /*!< System software release reset enable for TM16 module*/
#if defined(RST_APB1_TM20_EN_mask_w)
#define __DRV_RST_TM20_RELEASE_RESET()      RST_Base->APB1.W &= ~RST_APB1_TM20_EN_mask_w     /*!< System software release reset enable for TM20 module*/
#endif
#if defined(RST_APB1_TM26_EN_mask_w)
#define __DRV_RST_TM26_RELEASE_RESET()      RST_Base->APB1.W &= ~RST_APB1_TM26_EN_mask_w     /*!< System software release reset enable for TM26 module*/
#endif
#define __DRV_RST_TM36_RELEASE_RESET()      RST_Base->APB1.W &= ~RST_APB1_TM36_EN_mask_w     /*!< System software release reset enable for TM36 module*/
//!@}


/**
 * @name RST_Port_WaceReset_Disable_Enable
 *      RST Port WaceReset Disable/Enable
 */
//!@{
#define __DRV_RST_PA0_MODE_STATE_WARM_RESET_DISABLE()   RST_Base->CR0.W |= RST_CR0_PA_DIS0_mask_w    /*!< Warm reset disable for PA[3:0] pins    */
#define __DRV_RST_PA1_MODE_STATE_WARM_RESET_DISABLE()   RST_Base->CR0.W |= RST_CR0_PA_DIS1_mask_w    /*!< Warm reset disable for PA[11:8] pins   */
#define __DRV_RST_PB0_MODE_STATE_WARM_RESET_DISABLE()   RST_Base->CR0.W |= RST_CR0_PB_DIS0_mask_w    /*!< Warm reset disable for PB[3:0] pins    */
#define __DRV_RST_PB1_MODE_STATE_WARM_RESET_DISABLE()   RST_Base->CR0.W |= RST_CR0_PB_DIS1_mask_w    /*!< Warm reset disable for PB[11:8] pins   */
#if defined(RST_CR0_PC_DIS0_mask_w)
#define __DRV_RST_PC0_MODE_STATE_WARM_RESET_DISABLE()   RST_Base->CR0.W |= RST_CR0_PC_DIS0_mask_w    /*!< Warm reset disable for PC[3:0] pins    */
#define __DRV_RST_PC1_MODE_STATE_WARM_RESET_DISABLE()   RST_Base->CR0.W |= RST_CR0_PC_DIS1_mask_w    /*!< Warm reset disable for PC[11:8] pins   */
#endif
#define __DRV_RST_PD0_MODE_STATE_WARM_RESET_DISABLE()   RST_Base->CR0.W |= RST_CR0_PD_DIS0_mask_w    /*!< Warm reset disable for PD[3:0] pins    */
#define __DRV_RST_PD1_MODE_STATE_WARM_RESET_DISABLE()   RST_Base->CR0.W |= RST_CR0_PD_DIS1_mask_w    /*!< Warm reset disable for PD[11:8] pins   */
#if defined(RST_CR0_PE_DIS0_mask_w)
#define __DRV_RST_PE0_MODE_STATE_WARM_RESET_DISABLE()   RST_Base->CR0.W |= RST_CR0_PE_DIS0_mask_w    /*!< Warm reset disable for PE[3:0] pins    */
#define __DRV_RST_PE1_MODE_STATE_WARM_RESET_DISABLE()   RST_Base->CR0.W |= RST_CR0_PE_DIS1_mask_w    /*!< Warm reset disable for PE[9:8] pins    */
#endif

#define __DRV_RST_PA0_MODE_STATE_WARM_RESET_ENABLE()   RST_Base->CR0.W &= ~RST_CR0_PA_DIS0_mask_w    /*!< Warm reset enable for PA[3:0] pins    */
#define __DRV_RST_PA1_MODE_STATE_WARM_RESET_ENABLE()   RST_Base->CR0.W &= ~RST_CR0_PA_DIS1_mask_w    /*!< Warm reset enable for PA[11:8] pins   */
#define __DRV_RST_PB0_MODE_STATE_WARM_RESET_ENABLE()   RST_Base->CR0.W &= ~RST_CR0_PB_DIS0_mask_w    /*!< Warm reset enable for PB[3:0] pins    */
#define __DRV_RST_PB1_MODE_STATE_WARM_RESET_ENABLE()   RST_Base->CR0.W &= ~RST_CR0_PB_DIS1_mask_w    /*!< Warm reset enable for PB[11:8] pins   */
#if defined(RST_CR0_PC_DIS0_mask_w)
#define __DRV_RST_PC0_MODE_STATE_WARM_RESET_ENABLE()   RST_Base->CR0.W &= ~RST_CR0_PC_DIS0_mask_w    /*!< Warm reset enable for PC[3:0] pins    */
#define __DRV_RST_PC1_MODE_STATE_WARM_RESET_ENABLE()   RST_Base->CR0.W &= ~RST_CR0_PC_DIS1_mask_w    /*!< Warm reset enable for PC[11:8] pins   */
#endif
#define __DRV_RST_PD0_MODE_STATE_WARM_RESET_ENABLE()   RST_Base->CR0.W &= ~RST_CR0_PD_DIS0_mask_w    /*!< Warm reset enable for PD[3:0] pins    */
#define __DRV_RST_PD1_MODE_STATE_WARM_RESET_ENABLE()   RST_Base->CR0.W &= ~RST_CR0_PD_DIS1_mask_w    /*!< Warm reset enable for PD[11:8] pins   */
#if defined(RST_CR0_PE_DIS0_mask_w)
#define __DRV_RST_PE0_MODE_STATE_WARM_RESET_ENABLE()   RST_Base->CR0.W &= ~RST_CR0_PE_DIS0_mask_w    /*!< Warm reset enable for PE[3:0] pins    */
#define __DRV_RST_PE1_MODE_STATE_WARM_RESET_ENABLE()   RST_Base->CR0.W &= ~RST_CR0_PE_DIS1_mask_w    /*!< Warm reset enable for PE[9:8] pins    */
#endif
//!@}

/**
 * @name RST_WWDT_WaceReset_Disable_Enable
 *      RST WWDT WaceReset Disable/Enable
 */
//!@{
#define __DRV_RST_WWDT_MODUEL_WARM_RESET_DISABLE()     RST_Base->CR0.W |= RST_CR0_WWDT_WDIS_mask_w       /*!< WWDT module Warm reset disable */
#define __DRV_RST_WWDT_MODUEL_WARM_RESET_ENABLE()      RST_Base->CR0.W &= ~RST_CR0_WWDT_WDIS_mask_w      /*!< WWDT module Warm reset enable  */
//!@}


/**
 * @name RST_Port_WaceReset_Disable_Enable
 *      RST Port WaceReset Disable/Enable
 */
//!@{
#if (defined(USB_TYPE))
#define __DRV_RST_USB_LEVEL0_RESET()        RST_Base->CR0.W &= ~RST_CR0_USB_RCTL_mask_w      /*!< USB module reset control Level 0 */
#define __DRV_RST_USB_LEVEL1_RESET()        RST_Base->CR0.W |= RST_CR0_USB_RCTL_mask_w       /*!< USB module reset control Level 1 */
#endif
//!@}



#ifdef __cplusplus
}
#endif

#endif


