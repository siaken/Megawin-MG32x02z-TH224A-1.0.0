/**
 ******************************************************************************
 *
 * @file        MG32x02z_CSC_MID.H
 *
 * @brief       This is the C code format middleware head file for CSC module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.05
 * @date        2022/07/07
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2021 MegaWin Technology Co., Ltd.
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
 
 
#include "MG32x02z_Common_MID.h"
#include "MG32x02z_GPIO.h"
#include "MG32x02z_CSC.h"
#include "MG32x02z_CSC_Init.h"
#include "MG32x02z_CFG.h"

#ifndef __MG32x02z_CSC_MID_H
/*!< _MG32x02z_CSC_MID_H */
#define __MG32x02z_CSC_MID_H

#ifdef __cplusplus
extern "C" {
#endif

/*! @name 
*/
//!@{ 
#define CSC_IHRCO_SELECT            CSC_CR0_IHRCO_SEL_mask_w    /*!< CK_IHRCO select mask */
#define CSC_IHRCO_SELECT_12000000   CSC_CR0_IHRCO_SEL_12_w      /*!< CK_IHTCO select 12MHz */
#define CSC_IHRCO_SELECT_11059200   CSC_CR0_IHRCO_SEL_11_w      /*!< CK_IHRCO select 11.0592MHz */
#define ILRCO_VALUE                 ((uint32_t)32000)           /*!< CK_ILRCO frequency */

#define MID_CSC_ICKO_CKO_SEL_MASK   CSC_CKO_CKO_SEL_mask_w      /*!< ICKO select mask */
#define MID_CSC_ICKO_DIV_MASK       CSC_CKO_CKO_DIV_mask_w      /*!< ICKO divider mask */
#define MID_CSC_ICKO_EN_MASK        CSC_CKO_CKO_EN_mask_w       /*!< ICKO enable mask */

#define MID_CSC_MCD_SEL_MASK        CSC_CR0_MCD_SEL_mask_w      /*!< MCD select mask */
#define MID_CSC_MCD_DIS_MASK        CSC_CR0_MCD_DIS_mask_w      /*!< MCD disable mask */
#define MID_CSC_MCD_DIS_EN          CSC_CR0_MCD_DIS_enable_w    /*!< MCD enable */
#define MID_CSC_MCD_DIS_DIS         CSC_CR0_MCD_DIS_disable_w   /*!< MCD disable */
//!@}


/*! @enum   MID_CSC_ICKO_Source_TypeDef
    @brief  ICKO source select
*/
typedef enum
{
    MID_CSC_ICKO_CK_MAIN    = CSC_CKO_CKO_SEL_ck_main_w,    /*!< Select clock source CK_MAIN */
    MID_CSC_ICKO_CK_AHB     = CSC_CKO_CKO_SEL_ck_ahb_w,     /*!< Select clock source CK_AHB */
    MID_CSC_ICKO_CK_APB     = CSC_CKO_CKO_SEL_ck_apb_w,     /*!< Select clock source CK_APB */
    MID_CSC_ICKO_CK_HS      = CSC_CKO_CKO_SEL_ck_hs_w,      /*!< Select clock source CK_HS */
    MID_CSC_ICKO_CK_LS      = CSC_CKO_CKO_SEL_ck_ls_w,      /*!< Select clock source CK_LS */
    MID_CSC_ICKO_CK_XOSC    = CSC_CKO_CKO_SEL_ck_xosc_w     /*!< Select clock source CK_XOSC */
}MID_CSC_ICKO_Source_TypeDef;


/*! @enum   MID_CSC_ICKO_Div_TypeDef
    @brief  ICKO divider select
*/
typedef enum
{
    MID_CSC_ICKO_DIV_1      = CSC_CKO_CKO_DIV_div1_w,       /*!< Select clock source divided by 1 */
    MID_CSC_ICKO_DIV_2      = CSC_CKO_CKO_DIV_div2_w,       /*!< Select clock source divided by 2 */
    MID_CSC_ICKO_DIV_4      = CSC_CKO_CKO_DIV_div4_w,       /*!< Select clock source divided by 4 */
    MID_CSC_ICKO_DIV_8      = CSC_CKO_CKO_DIV_div8_w        /*!< Select clock source divided by 8 */
}MID_CSC_ICKO_Div_TypeDef;


/*! @enum   MID_CSC_MCD_SEL_TypeDef
    @brief  MCD duration select.
*/
typedef enum
{
    MID_CSC_MCD_125us  = CSC_CR0_MCD_SEL_125us_w,   /*!< Miss clock detection 125us */
    MID_CSC_MCD_250us  = CSC_CR0_MCD_SEL_250us_w,   /*!< Miss clock detection 250us */
    MID_CSC_MCD_500us  = CSC_CR0_MCD_SEL_500us_w,   /*!< Miss clock detection 500us */
    MID_CSC_MCD_1ms    = CSC_CR0_MCD_SEL_1ms_w,     /*!< Miss clock detection 1ms */
}MID_CSC_MCD_SEL_TypeDef;


/*! @name   MID_CSC_CK_PR_TypeDef
    @brief  Peripheral clock source selection.
*/
#define MID_CSC_CK_PR_CORE     0x00U    /*!< Core is in CSC CK_PR Freq */
#define MID_CSC_CK_PR_DMA      0x08U    /*!< DMA is in CSC CK_PR Freq */
#if defined(USB_TYPE)
    #define MID_CSC_CK_PR_USB      0x10U    /*!< USB is in CSC CK_PR Freq */
#endif
#define MID_CSC_CK_PR_MEM      0x18U    /*!< MEM is in CSC CK_PR Freq */
#if defined(CSC_AHB_EMB_EN_mask_w)
#define MID_CSC_CK_PR_EMB      0x20U    /*!< EMB is in CSC CK_PR Freq */
    #endif
#define MID_CSC_CK_PR_GPL      0x28U    /*!< GPL is in CSC CK_PR Freq */
#define MID_CSC_CK_PR_GPIOA    0x30U    /*!< GPIOA is in CSC CK_PR Freq */
#define MID_CSC_CK_PR_GPIOB    0x31U    /*!< GPIOB is in CSC CK_PR Freq */
#define MID_CSC_CK_PR_GPIOC    0x32U    /*!< GPIOC is in CSC CK_PR Freq */
#if defined(CSC_AHB_IOPD_EN_mask_w)
    #define MID_CSC_CK_PR_GPIOD    0x33U    /*!< GPIOD is in CSC CK_PR Freq */
#endif
#if defined(CSC_AHB_IOPE_EN_mask_w)
    #define MID_CSC_CK_PR_GPIOE    0x34U    /*!< GPIOE is in CSC CK_PR Freq */
#endif
#if defined(CSC_AHB_IOPF_EN_mask_w)
    #define MID_CSC_CK_PR_GPIOF    0x35U    /*!< GPIOF is in CSC CK_PR Freq */
#endif
#if defined(CSC_AHB_IOPG_EN_mask_w)
    #define MID_CSC_CK_PR_GPIOG    0x36U    /*!< GPIOG is in CSC CK_PR Freq */
#endif
#if defined(CSC_AHB_IOPH_EN_mask_w)
    #def ine MID_CSC_CK_PR_GPIOH    0x37U    /*!< GPIOH is in CSC CK_PR Freq */
#endif
#if defined(CSC_APB0_CMP_EN_mask_w)
    #define MID_CSC_CK_PR_CMP      0x38U    /*!< CMP is in CSC CK_PR Freq */
#endif
//#define MID_CSC_CK_PR_CMP0     0x38U    /*!< CMP is in CSC CK_PR Freq */
//#define MID_CSC_CK_PR_CMP1     0x39U    /*!< CMP is in CSC CK_PR Freq */
//#define MID_CSC_CK_PR_ADC      0x40U    /*!< ADC is in CSC CK_PR Freq */
#define MID_CSC_CK_PR_ADC0     0x40U    /*!< ADC is in CSC CK_PR Freq */
//#define MID_CSC_CK_PR_ADC1     0x41U    /*!< ADC is in CSC CK_PR Freq */
#if defined(CSC_APB0_DAC_EN_mask_w)
    #define MID_CSC_CK_PR_DAC      0x48U    /*!< DAC is in CSC CK_PR Freq */
#endif
//#define MID_CSC_CK_PR_DAC0     0x48U    /*!< DAC is in CSC CK_PR Freq */
//#define MID_CSC_CK_PR_DAC1     0x49U    /*!< DAC is in CSC CK_PR Freq */
#define MID_CSC_CK_PR_IWDT     0x50U    /*!< IWDT is in CSC CK_PR Freq */
#define MID_CSC_CK_PR_WWDT     0x51U    /*!< WWDT is in CSC CK_PR Freq */
#define MID_CSC_CK_PR_RTC      0x58U    /*!< RTC is in CSC CK_PR Freq */
#if defined(CSC_APB0_APX_EN_mask_w)
    #define MID_CSC_CK_PR_APX      0x60U    /*!< APX is in CSC CK_PR Freq */
#endif
#define MID_CSC_CK_PR_TM00     0x80U    /*!< TM00 is in CSC CK_PR Freq */
#define MID_CSC_CK_PR_TM01     0x81U    /*!< TM01 is in CSC CK_PR Freq */
#define MID_CSC_CK_PR_TM10     0x90U    /*!< TM10 is in CSC CK_PR Freq */
#define MID_CSC_CK_PR_TM16     0x96U    /*!< TM16 is in CSC CK_PR Freq */
#if defined(CSC_APB1_TM20_EN_mask_w)
    #define MID_CSC_CK_PR_TM20     0xA0U    /*!< TM20 is in CSC CK_PR Freq */
#endif
#if defined(CSC_APB1_TM26_EN_mask_w)
    #define MID_CSC_CK_PR_TM26     0xA6U    /*!< TM26 is in CSC CK_PR Freq */
#endif
#define MID_CSC_CK_PR_TM36     0xB6U    /*!< TM36 is in CSC CK_PR Freq */
#define MID_CSC_CK_PR_URT0     0xD0U    /*!< URT0 is in CSC CK_PR Freq */
#define MID_CSC_CK_PR_URT1     0xD1U    /*!< URT1 is in CSC CK_PR Freq */
#if defined(CSC_APB0_URT2_EN_mask_w)
    #define MID_CSC_CK_PR_URT2     0xD2U    /*!< URT2 is in CSC CK_PR Freq */
#endif
#if defined(CSC_APB0_URT3_EN_mask_w)
    #define MID_CSC_CK_PR_URT3     0xD3U    /*!< URT3 is in CSC CK_PR Freq */
#endif
#if defined(CSC_APB0_URT4_EN_mask_w)
    #define MID_CSC_CK_PR_URT4     0xD4U    /*!< URT3 is in CSC CK_PR Freq */
#endif
#if defined(CSC_APB0_URT5_EN_mask_w)
    #define MID_CSC_CK_PR_URT5     0xD5U    /*!< URT3 is in CSC CK_PR Freq */
#endif
#if defined(CSC_APB0_URT6_EN_mask_w)
    #define MID_CSC_CK_PR_URT6     0xD6U    /*!< URT3 is in CSC CK_PR Freq */
#endif
#if defined(CSC_APB0_URT7_EN_mask_w)
    #define MID_CSC_CK_PR_URT7     0xD7U    /*!< URT3 is in CSC CK_PR Freq */
#endif
#define MID_CSC_CK_PR_SPI0     0xE0U    /*!< SPI0 is in CSC CK_PR Freq */
#if defined(CSC_APB0_SPI1_EN_mask_w)
    #define MID_CSC_CK_PR_SPI1     0xE1U    /*!< SPI1 is in CSC CK_PR Freq */
#endif
#if defined(CSC_APB0_SPI1_EN_mask_w)
    #define MID_CSC_CK_PR_SPI2     0xE2U    /*!< SPI2 is in CSC CK_PR Freq */
#endif
#if defined(CSC_APB0_SPI1_EN_mask_w)
    #define MID_CSC_CK_PR_SPI3     0xE3U    /*!< SPI3 is in CSC CK_PR Freq */
#endif
#define MID_CSC_CK_PR_I2C0     0xF0U    /*!< I2C0 is in CSC CK_PR Freq */
#if defined(CSC_APB0_I2C1_EN_mask_w)
    #define MID_CSC_CK_PR_I2C1     0xF1U    /*!< I2C1 is in CSC CK_PR Freq */
#endif
#if defined(CSC_APB0_I2C2_EN_mask_w)
    #define MID_CSC_CK_PR_I2C2     0xF2U    /*!< I2C2 is in CSC CK_PR Freq */
#endif
#if defined(CSC_APB0_I2C3_EN_mask_w)
    #define MID_CSC_CK_PR_I2C3     0xF3U    /*!< I2C3 is in CSC CK_PR Freq */
#endif

/**
 * @name CSC_Interrupt_definition
 *      CSC Interrupt Definition
 */
//!@{
#define CSC_IT_IEA              CSC_INT_IEA_mask_w          /*!< CSC interrupt all enable. When disables                    */
#define CSC_IT_XOSC             CSC_INT_XOSC_IE_mask_w      /*!< XOSC clock stable interrupt enable                         */
#define CSC_IT_ILRCO            CSC_INT_ILRCO_IE_mask_w     /*!< ILRCO clock stable interrupt enable                        */
#define CSC_IT_IHRCO            CSC_INT_IHRCO_IE_mask_w     /*!< IHRCO clock stable interrupt enable                        */
#define CSC_IT_PLL              CSC_INT_PLL_IE_mask_w       /*!< PLL clock stable interrupt enable                          */
#define CSC_IT_MCD              CSC_INT_MCD_IE_mask_w       /*!< XOSC missing clock detect failure event interrupt enable   */
//!@}


/**
 * @name CSC_Flag_definition
 *      CSC Flg Definition
 */
//!@{
#if defined(MG32_3RD) || defined(MG32_4TH)
#define CSC_FLAG_PLL_LOCKF      CSC_STA_PLL_LOCKF_mask_w    /*!< PLL clock lock status                          */
#endif
#define CSC_FLAG_XOSCF          CSC_STA_XOSCF_mask_w        /*!< XOSC clock stable and ready detect flag        */ 
#define CSC_FLAG_ILRCOF         CSC_STA_ILRCOF_mask_w       /*!< ILRCO clock stable and ready detect flag       */
#define CSC_FLAG_IHRCOF         CSC_STA_IHRCOF_mask_w       /*!< IHRCO clock stable and ready detect flag       */
#define CSC_FLAG_PLLF           CSC_STA_PLLF_mask_w         /*!< PLL clock stable and ready detect flag         */
#define CSC_FLAG_MCDF           CSC_STA_MCDF_mask_w         /*!< XOSC missing clock detect failure event flag   */
//!@}


/**
 *******************************************************************************
 * @brief       Enable the specified CSC interrupts.
 * @details  
 * @param[in]   "__INTERRUPT__" specifies the interrupt source to enable.
 *              This parameter can be one of the following values:
 *  @arg\b          SYS_IT_IEA: CSC interrupt all enable. When disables
 *  @arg\b          CSC_IT_XOSC: XOSC clock stable interrupt enable
 *  @arg\b          CSC_IT_ILRCO: ILRCO clock stable interrupt enable
 *  @arg\b          CSC_IT_IHRCO: IHRCO clock stable interrupt enable
 *  @arg\b          CSC_IT_PLL: PLL clock stable interrupt enable
 *  @arg\b          CSC_IT_MCD: XOSC missing clock detect failure event interrupt enable
 * @return      None
 * @note
 * @par         Example
 * @code
    __DRV_CSC_ENABLE_IT(CSC_IT_PLL | SYS_IT_IEA);
 * @endcode
 *******************************************************************************
 */
#define __DRV_CSC_ENABLE_IT(__INTERRUPT__)  SET_BIT(CSC->INT.W, (__INTERRUPT__))


/**
 *******************************************************************************
 * @brief       Disable the specified CSC interrupts.
 * @details  
 * @param[in]   "__INTERRUPT__" specifies the interrupt source to enable.
 *              This parameter can be one of the following values:
 *  @arg\b          SYS_IT_IEA: CSC interrupt all enable. When disables
 *  @arg\b          CSC_IT_XOSC: XOSC clock stable interrupt enable
 *  @arg\b          CSC_IT_ILRCO: ILRCO clock stable interrupt enable
 *  @arg\b          CSC_IT_IHRCO: IHRCO clock stable interrupt enable
 *  @arg\b          CSC_IT_PLL: PLL clock stable interrupt enable
 *  @arg\b          CSC_IT_MCD: XOSC missing clock detect failure event interrupt enable
 * @return      None
 * @note
 * @par         Example
 * @code
    __DRV_CSC_DISABLE_IT(CSC_IT_PLL);
 * @endcode
 *******************************************************************************
 */
#define __DRV_CSC_DISABLE_IT(__INTERRUPT__)  CLEAR_BIT(CSC->INT.W, (__INTERRUPT__))


/**
 *******************************************************************************
 * @brief       Check whether the specified CSC flag is set or not.
 * @details  
 * @param[in]   "__FLAG__" specifies the flag to check.
 *              This parameter can be one of the following values:
 *  @arg\b          CSC_FLAG_PLL_LOCKF: PLL clock lock status
 *  @arg\b          CSC_FLAG_XOSCF: XOSC clock stable and ready detect flag
 *  @arg\b          CSC_FLAG_ILRCOF: ILRCO clock stable and ready detect flag
 *  @arg\b          CSC_FLAG_IHRCOF: IHRCO clock stable and ready detect flag
 *  @arg\b          CSC_FLAG_PLLF: PLL clock stable and ready detect flag
 *  @arg\b          CSC_FLAG_MCDF: XOSC missing clock detect failure event flag
 * @return      The new state of __IT__ (SET or CLR).
 * @note
 * @par         Example
 * @code
    if(__DRV_CSC_GET_FLAG(CSC_FLAG_PLL_LOCKF))
 * @endcode
 *******************************************************************************
 */
#define __DRV_CSC_GET_FLAG(__FLAG__) (((CSC->STA.W) & (__FLAG__)) == (__FLAG__))


/**
 *******************************************************************************
 * @brief       Clear CSC flag
 * @details  
 * @param[in]   "__FLAG__" specifies the flag to check.
 *              This parameter can be one of the following values:
 *  @arg\b          CSC_FLAG_PLL_LOCKF: PLL clock lock status
 *  @arg\b          CSC_FLAG_XOSCF: XOSC clock stable and ready detect flag
 *  @arg\b          CSC_FLAG_ILRCOF: ILRCO clock stable and ready detect flag
 *  @arg\b          CSC_FLAG_IHRCOF: IHRCO clock stable and ready detect flag
 *  @arg\b          CSC_FLAG_PLLF: PLL clock stable and ready detect flag
 *  @arg\b          CSC_FLAG_MCDF: XOSC missing clock detect failure event flag
 * @return      The new state of __IT__ (SET or CLR).
 * @note
 * @par         Example
 * @code
    __MID_CSC_CLEAR_FLAG(CSC_FLAG_PLL_LOCKF);
 * @endcode
 *******************************************************************************
 */
#define __DRV_CSC_CLEAR_FLAG(__FLAG__) SET_BIT(CSC->STA.W, (__FLAG__))


/**
 * @name CSC_Periphery_Clock_Enable_Disable
 *      CSC Periphery Clock Enable/Disable
 */
//!@{
#define __DRV_CSC_GPIOA_CLK_ENABLE()    CSC->AHB.W |= CSC_AHB_IOPA_EN_mask_w        /*! GPIOA clock source enable   */
#define __DRV_CSC_GPIOB_CLK_ENABLE()    CSC->AHB.W |= CSC_AHB_IOPB_EN_mask_w        /*! GPIOB clock source enable   */
#define __DRV_CSC_GPIOC_CLK_ENABLE()    CSC->AHB.W |= CSC_AHB_IOPC_EN_mask_w        /*! GPIOC clock source enable   */
#define __DRV_CSC_GPIOD_CLK_ENABLE()    CSC->AHB.W |= CSC_AHB_IOPD_EN_mask_w        /*! GPIOD clock source enable   */
#if defined(MG32_1ST) || defined(MG32_3RD) 
#define __DRV_CSC_GPIOE_CLK_ENABLE()    CSC->AHB.W |= CSC_AHB_IOPE_EN_mask_w        /*! GPIOE clock source enable   */
#endif
#define __DRV_CSC_GPL_CLK_ENABLE()      CSC->AHB.W |= CSC_AHB_GPL_EN_mask_w         /*! GPL clock source enable     */
#if defined(MG32_1ST) || defined(MG32_3RD) 
#define __DRV_CSC_EMB_CLK_ENABLE()      CSC->AHB.W |= CSC_AHB_EMB_EN_mask_w         /*! EMB clock source enable     */
#endif
#define __DRV_CSC_DMA_CLK_ENABLE()      CSC->AHB.W |= CSC_AHB_DMA_EN_mask_w         /*! DMA clock source enable     */
#define __DRV_CSC_ADC0_CLK_ENABLE()     CSC->APB0.W |= CSC_APB0_ADC0_EN_mask_w      /*! ADC0 clock source enable    */
#define __DRV_CSC_CMP_CLK_ENABLE()      CSC->APB0.W |= CSC_APB0_CMP_EN_mask_w       /*! CMP clock source enable     */
#if defined(MG32_1ST) || defined(MG32_3RD) 
#define __DRV_CSC_DAC_CLK_ENABLE()      CSC->APB0.W |= CSC_APB0_DAC_EN_mask_w       /*! DAC clock source enable     */
#endif
#define __DRV_CSC_RTC_CLK_ENABLE()      CSC->APB0.W |= CSC_APB0_RTC_EN_mask_w       /*! RTC clock source enable     */
#define __DRV_CSC_IWDT_CLK_ENABLE()     CSC->APB0.W |= CSC_APB0_IWDT_EN_mask_w      /*! IWDT clock source enable    */
#define __DRV_CSC_WWDT_CLK_ENABLE()     CSC->APB0.W |= CSC_APB0_WWDT_EN_mask_w      /*! WWDT clock source enable    */
#define __DRV_CSC_I2C0_CLK_ENABLE()     CSC->APB0.W |= CSC_APB0_I2C0_EN_mask_w      /*! I2C0 clock source enable    */
#if defined(MG32_1ST) || defined(MG32_3RD) || defined(MG32_4TH)                                                          
#define __DRV_CSC_I2C1_CLK_ENABLE()     CSC->APB0.W |= CSC_APB0_I2C1_EN_mask_w      /*! I2C1 clock source enable    */
#endif                                                                              
#define __DRV_CSC_SPI0_CLK_ENABLE()     CSC->APB0.W |= CSC_APB0_SPI0_EN_mask_w      /*! SPI0 clock source enable    */
#define __DRV_CSC_URT0_CLK_ENABLE()     CSC->APB0.W |= CSC_APB0_URT0_EN_mask_w      /*! URT0 clock source enable    */
#define __DRV_CSC_URT1_CLK_ENABLE()     CSC->APB0.W |= CSC_APB0_URT1_EN_mask_w      /*! URT1 clock source enable    */
#if defined(MG32_1ST) || defined(MG32_3RD)
#define __DRV_CSC_URT2_CLK_ENABLE()     CSC->APB0.W |= CSC_APB0_URT2_EN_mask_w      /*! URT2 clock source enable    */
#endif 
#if defined(MG32_1ST)
#define __DRV_CSC_URT3_CLK_ENABLE()     CSC->APB0.W |= CSC_APB0_URT3_EN_mask_w      /*! URT3 clock source enable    */
#endif
#if defined(MG32_3RD) || defined(MG32_4TH)                                                                        
#define __DRV_CSC_URT4_CLK_ENABLE()     CSC->APB0.W |= CSC_APB0_URT4_EN_mask_w      /*! URT4 clock source enable    */
#endif
#if defined(MG32_3RD)
#define __DRV_CSC_URT5_CLK_ENABLE()     CSC->APB0.W |= CSC_APB0_URT5_EN_mask_w      /*! URT5 clock source enable    */
#define __DRV_CSC_URT6_CLK_ENABLE()     CSC->APB0.W |= CSC_APB0_URT6_EN_mask_w      /*! URT6 clock source enable    */
#define __DRV_CSC_URT7_CLK_ENABLE()     CSC->APB0.W |= CSC_APB0_URT7_EN_mask_w      /*! URT7 clock source enable    */
#define __DRV_CSC_USB_CLK_ENABLE()      CSC->APB0.W |= CSC_APB0_USB_EN_mask_w       /*! USB clock source enable     */
#endif

#if defined(MG32_3RD)||defined(MG32_4TH)
#define __DRV_CSC_APX_CLK_ENABLE()      CSC->APB0.W |= CSC_APB0_APX_EN_mask_w       /*! APX clock source enable     */
#endif

#define __DRV_CSC_TM00_CLK_ENABLE()     CSC->APB1.W |= CSC_APB1_TM00_EN_mask_w      /*! TM00 clock source enable    */
#define __DRV_CSC_TM01_CLK_ENABLE()     CSC->APB1.W |= CSC_APB1_TM01_EN_mask_w      /*! TM01 clock source enable    */
#define __DRV_CSC_TM10_CLK_ENABLE()     CSC->APB1.W |= CSC_APB1_TM10_EN_mask_w      /*! TM10 clock source enable    */
#define __DRV_CSC_TM16_CLK_ENABLE()     CSC->APB1.W |= CSC_APB1_TM16_EN_mask_w      /*! TM16 clock source enable    */
#if defined(MG32_1ST) || defined(MG32_3RD) || defined(MG32_4TH)
#define __DRV_CSC_TM20_CLK_ENABLE()     CSC->APB1.W |= CSC_APB1_TM20_EN_mask_w      /*! TM20 clock source enable    */
#endif
#if defined(MG32_1ST) || defined(MG32_3RD)
#define __DRV_CSC_TM26_CLK_ENABLE()     CSC->APB1.W |= CSC_APB1_TM26_EN_mask_w      /*! TM26 clock source enable    */
#endif
#define __DRV_CSC_TM36_CLK_ENABLE()     CSC->APB1.W |= CSC_APB1_TM36_EN_mask_w      /*! TM36 clock source enable    */

#define __DRV_CSC_GPIOA_CLK_DISABLE()   CSC->AHB.W &= ~CSC_AHB_IOPA_EN_mask_w       /*! GPIOA clock source disable   */
#define __DRV_CSC_GPIOB_CLK_DISABLE()   CSC->AHB.W &= ~CSC_AHB_IOPB_EN_mask_w       /*! GPIOB clock source disable   */
#define __DRV_CSC_GPIOC_CLK_DISABLE()   CSC->AHB.W &= ~CSC_AHB_IOPC_EN_mask_w       /*! GPIOC clock source disable   */
#define __DRV_CSC_GPIOD_CLK_DISABLE()   CSC->AHB.W &= ~CSC_AHB_IOPD_EN_mask_w       /*! GPIOD clock source disable   */
#if defined(MG32_1ST) || defined(MG32_3RD)
#define __DRV_CSC_GPIOE_CLK_DISABLE()   CSC->AHB.W &= ~CSC_AHB_IOPE_EN_mask_w       /*! GPIOE clock source disable   */
#endif
#define __DRV_CSC_GPL_CLK_DISABLE()     CSC->AHB.W &= ~CSC_AHB_GPL_EN_mask_w        /*! GPL clock source disable     */
#if defined(MG32_1ST) || defined(MG32_3RD) 
#define __DRV_CSC_EMB_CLK_DISABLE()     CSC->AHB.W &= ~CSC_AHB_EMB_EN_mask_w        /*! EMB clock source disable     */
#endif
#define __DRV_CSC_DMA_CLK_DISABLE()     CSC->AHB.W &= ~CSC_AHB_DMA_EN_mask_w        /*! DMA clock source disable     */
#define __DRV_CSC_ADC0_CLK_DISABLE()    CSC->APB0.W &= ~CSC_APB0_ADC0_EN_mask_w     /*! ADC0 clock source disable    */
#define __DRV_CSC_CMP_CLK_DISABLE()     CSC->APB0.W &= ~CSC_APB0_CMP_EN_mask_w      /*! CMP clock source disable     */
#if defined(MG32_1ST) || defined(MG32_3RD)
#define __DRV_CSC_DAC_CLK_DISABLE()     CSC->APB0.W &= ~CSC_APB0_DAC_EN_mask_w      /*! DAC clock source disable     */
#endif
#define __DRV_CSC_RTC_CLK_DISABLE()     CSC->APB0.W &= ~CSC_APB0_RTC_EN_mask_w      /*! RTC clock source disable     */
#define __DRV_CSC_IWDT_CLK_DISABLE()    CSC->APB0.W &= ~CSC_APB0_IWDT_EN_mask_w     /*! IWDT clock source disable    */
#define __DRV_CSC_WWDT_CLK_DISABLE()    CSC->APB0.W &= ~CSC_APB0_WWDT_EN_mask_w     /*! WWDT clock source disable    */
#define __DRV_CSC_I2C0_CLK_DISABLE()    CSC->APB0.W &= ~CSC_APB0_I2C0_EN_mask_w     /*! I2C0 clock source disable    */
#if defined(MG32_1ST) || defined(MG32_3RD) || defined(MG32_4TH)
#define __DRV_CSC_I2C1_CLK_DISABLE()    CSC->APB0.W &= ~CSC_APB0_I2C1_EN_mask_w     /*! I2C1 clock source disable    */
#endif
#define __DRV_CSC_SPI0_CLK_DISABLE()    CSC->APB0.W &= ~CSC_APB0_SPI0_EN_mask_w     /*! SPI0 clock source disable    */
#define __DRV_CSC_URT0_CLK_DISABLE()    CSC->APB0.W &= ~CSC_APB0_URT0_EN_mask_w     /*! URT0 clock source disable    */
#define __DRV_CSC_URT1_CLK_DISABLE()    CSC->APB0.W &= ~CSC_APB0_URT1_EN_mask_w     /*! URT1 clock source disable    */
#if defined(MG32_1ST) || defined(MG32_3RD)
#define __DRV_CSC_URT2_CLK_DISABLE()    CSC->APB0.W &= ~CSC_APB0_URT2_EN_mask_w     /*! URT2 clock source disable    */
#endif
#if defined(MG32_1ST) 
#define __DRV_CSC_URT3_CLK_DISABLE()    CSC->APB0.W &= ~CSC_APB0_URT3_EN_mask_w     /*! URT3 clock source disable    */
#endif
#if defined(MG32_3RD) || defined(MG32_4TH)
#define __DRV_CSC_URT4_CLK_DISABLE()    CSC->APB0.W &= ~CSC_APB0_URT4_EN_mask_w     /*! URT4 clock source disable    */
#endif
#if defined(MG32_3RD)
#define __DRV_CSC_URT5_CLK_DISABLE()    CSC->APB0.W &= ~CSC_APB0_URT5_EN_mask_w     /*! URT5 clock source disable    */
#define __DRV_CSC_URT6_CLK_DISABLE()    CSC->APB0.W &= ~CSC_APB0_URT6_EN_mask_w     /*! URT6 clock source disable    */
#define __DRV_CSC_URT7_CLK_DISABLE()    CSC->APB0.W &= ~CSC_APB0_URT7_EN_mask_w     /*! URT7 clock source disable    */
#define __DRV_CSC_USB_CLK_DISABLE()     CSC->APB0.W &= ~CSC_APB0_USB_EN_mask_w      /*! USB clock source disable     */
#endif

#if defined(MG32_3RD)||defined(MG32_4TH)
#define __DRV_CSC_APX_CL K_DISABLE()     CSC->APB0.W &= ~CSC_APB0_APX_EN_mask_w      /*! APX clock source disable     */
#endif

#define __DRV_CSC_TM00_CLK_DISABLE()    CSC->APB1.W &= ~CSC_APB1_TM00_EN_mask_w     /*! TM00 clock source disable    */
#define __DRV_CSC_TM01_CLK_DISABLE()    CSC->APB1.W &= ~CSC_APB1_TM01_EN_mask_w     /*! TM01 clock source disable    */
#define __DRV_CSC_TM10_CLK_DISABLE()    CSC->APB1.W &= ~CSC_APB1_TM10_EN_mask_w     /*! TM10 clock source disable    */
#define __DRV_CSC_TM16_CLK_DISABLE()    CSC->APB1.W &= ~CSC_APB1_TM16_EN_mask_w     /*! TM16 clock source disable    */
#if defined(MG32_1ST) || defined(MG32_3RD) || defined(MG32_4TH)
#define __DRV_CSC_TM20_CLK_DISABLE()    CSC->APB1.W &= ~CSC_APB1_TM20_EN_mask_w     /*! TM20 clock source disable    */
#endif
#if defined(MG32_1ST) || defined(MG32_3RD)
#define __DRV_CSC_TM26_CLK_DISABLE()    CSC->APB1.W &= ~CSC_APB1_TM26_EN_mask_w     /*! TM26 clock source disable    */
#endif
#define __DRV_CSC_TM36_CLK_DISABLE()    CSC->APB1.W &= ~CSC_APB1_TM36_EN_mask_w     /*! TM36 clock source disable    */
//!@}


/**
 * @name CSC_Periphery_SLEEP_Mode_Clock_Enable_Disable
 *      CSC Periphery SLEEP Mode Clock Enable/Disable
 */
//!@{
#define __DRV_CSC_SLP_ADC0_CLK_ENABLE()     CSC->SLP0.W |= CSC_SLP0_SLP_ADC0_mask_w     /*!< ADC module clock enable in SLEEP mode  */
#define __DRV_CSC_SLP_CMP_CLK_ENABLE()      CSC->SLP0.W |= CSC_SLP0_SLP_CMP_mask_w      /*!< CMP module clock enable in SLEEP mode  */
#if defined(MG32_1ST) || defined(MG32_3RD)
#define __DRV_CSC_SLP_DAC_CLK_ENABLE()      CSC->SLP0.W |= CSC_SLP0_SLP_DAC_mask_w      /*!< DAC module clock enable in SLEEP mode  */
#endif
#define __DRV_CSC_SLP_RTC_CLK_ENABLE()      CSC->SLP0.W |= CSC_SLP0_SLP_RTC_mask_w      /*!< RTC module clock enable in SLEEP mode  */
#define __DRV_CSC_SLP_IWDT_CLK_ENABLE()     CSC->SLP0.W |= CSC_SLP0_SLP_IWDT_mask_w     /*!< IWDT module clock enable in SLEEP mode */
#define __DRV_CSC_SLP_WWDT_CLK_ENABLE()     CSC->SLP0.W |= CSC_SLP0_SLP_WWDT_mask_w     /*!< WWDT module clock enable in SLEEP mode */
#define __DRV_CSC_SLP_I2C0_CLK_ENABLE()     CSC->SLP0.W |= CSC_SLP0_SLP_I2C0_mask_w     /*!< I2C0 module clock enable in SLEEP mode */
#if defined(MG32_1ST) || defined(MG32_3RD) || defined(MG32_4TH)
#define __DRV_CSC_SLP_I2C1_CLK_ENABLE()     CSC->SLP0.W |= CSC_SLP0_SLP_I2C1_mask_w     /*!< I2C1 module clock enable in SLEEP mode */
#endif
#define __DRV_CSC_SLP_SPI0_CLK_ENABLE()     CSC->SLP0.W |= CSC_SLP0_SLP_SPI0_mask_w     /*!< SPI0 module clock enable in SLEEP mode */
#define __DRV_CSC_SLP_URT0_CLK_ENABLE()     CSC->SLP0.W |= CSC_SLP0_SLP_URT0_mask_w     /*!< URT0 module clock enable in SLEEP mode */
#define __DRV_CSC_SLP_URT1_CLK_ENABLE()     CSC->SLP0.W |= CSC_SLP0_SLP_URT1_mask_w     /*!< URT1 module clock enable in SLEEP mode */
#if defined(MG32_1ST) || defined(MG32_3RD)
#define __DRV_CSC_SLP_URT2_CLK_ENABLE()     CSC->SLP0.W |= CSC_SLP0_SLP_URT2_mask_w     /*!< URT2 module clock enable in SLEEP mode */
#endif
#if defined(MG32_1ST)
#define __DRV_CSC_SLP_URT3_CLK_ENABLE()     CSC->SLP0.W |= CSC_SLP0_SLP_URT3_mask_w     /*!< URT3 module clock enable in SLEEP mode */
#endif
#if defined(MG32_3RD) || defined(MG32_4TH)
#define __DRV_CSC_SLP_URT4_CLK_ENABLE()     CSC->SLP0.W |= CSC_SLP0_SLP_URT4_mask_w     /*!< URT4 module clock enable in SLEEP mode */
#endif
#if defined(MG32_3RD)
#define __DRV_CSC_SLP_URT5_CLK_ENABLE()     CSC->SLP0.W |= CSC_SLP0_SLP_URT5_mask_w     /*!< URT5 module clock enable in SLEEP mode */
#define __DRV_CSC_SLP_URT6_CLK_ENABLE()     CSC->SLP0.W |= CSC_SLP0_SLP_URT6_mask_w     /*!< URT6 module clock enable in SLEEP mode */
#define __DRV_CSC_SLP_URT7_CLK_ENABLE()     CSC->SLP0.W |= CSC_SLP0_SLP_URT7_mask_w     /*!< URT7 module clock enable in SLEEP mode */
#define __DRV_CSC_SLP_USB_CLK_ENABLE()      CSC->SLP0.W |= CSC_SLP0_SLP_USB_mask_w      /*!< USB module clock enable in SLEEP mode  */
#endif

#if defined(MG32_3RD)||defined(MG32_4TH)
#define __DRV_CSC_SLP_APX_CLK_ENABLE()      CSC->SLP0.W |= CSC_SLP0_SLP_APX_mask_w      /*!< APX module clock enable in SLEEP mode  */
#endif

#define __DRV_CSC_SLP_TM00_CLK_ENABLE()     CSC->SLP0.W |= CSC_SLP1_SLP_TM00_mask_w     /*!< TM00 module clock enable in SLEEP mode */
#define __DRV_CSC_SLP_TM01_CLK_ENABLE()     CSC->SLP0.W |= CSC_SLP1_SLP_TM01_mask_w     /*!< TM01 module clock enable in SLEEP mode */
#define __DRV_CSC_SLP_TM10_CLK_ENABLE()     CSC->SLP0.W |= CSC_SLP1_SLP_TM10_mask_w     /*!< TM10 module clock enable in SLEEP mode */
#define __DRV_CSC_SLP_TM16_CLK_ENABLE()     CSC->SLP0.W |= CSC_SLP1_SLP_TM16_mask_w     /*!< TM16 module clock enable in SLEEP mode */
#if defined(MG32_1ST) || defined(MG32_3RD) || defined(MG32_4TH)
#define __DRV_CSC_SLP_TM20_CLK_ENABLE()     CSC->SLP0.W |= CSC_SLP1_SLP_TM20_mask_w     /*!< TM20 module clock enable in SLEEP mode */
#endif
#if defined(MG32_1ST) || defined(MG32_3RD)
#define __DRV_CSC_SLP_TM26_CLK_ENABLE()     CSC->SLP0.W |= CSC_SLP1_SLP_TM26_mask_w     /*!< TM26 module clock enable in SLEEP mode */
#endif
#define __DRV_CSC_SLP_TM36_CLK_ENABLE()     CSC->SLP0.W |= CSC_SLP1_SLP_TM36_mask_w     /*!< TM36 module clock enable in SLEEP mode */
#if defined(MG32_3RD) || defined(MG32_4TH)
#define __DRV_CSC_SLP_FLASH_CLK_ENABLE()    CSC->SLP0.W |= CSC_SLP1_SLP_FLASH_mask_w    /*!< FLASH module clock enable in SLEEP mode    */
#define __DRV_CSC_SLP_SRAM_CLK_ENABLE()     CSC->SLP0.W |= CSC_SLP1_SLP_SRAM_mask_w     /*!< SRAM module clock enable in SLEEP mode     */
#define __DRV_CSC_SLP_DMA_CLK_ENABLE()      CSC->SLP0.W |= CSC_SLP1_SLP_DMA_mask_w      /*!< DMA module clock enable in SLEEP mode      */
#endif
#if defined(MG32_3RD)
#define __DRV_CSC_SLP_EMB_CLK_ENABLE()      CSC->SLP0.W |= CSC_SLP1_SLP_EMB_mask_w      /*!< EMB module clock enable in SLEEP mode      */   
#endif


#define __DRV_CSC_SLP_ADC0_CLK_DISABLE()     CSC->SLP0.W &= ~CSC_SLP0_SLP_ADC0_mask_w   /*!< ADC module clock disable in SLEEP mode  */
#define __DRV_CSC_SLP_CMP_CLK_DISABLE()      CSC->SLP0.W &= ~CSC_SLP0_SLP_CMP_mask_w    /*!< CMP module clock disable in SLEEP mode  */
#if defined(MG32_1ST) || defined(MG32_3RD)
#define __DRV_CSC_SLP_DAC_CLK_DISABLE()      CSC->SLP0.W &= ~CSC_SLP0_SLP_DAC_mask_w    /*!< DAC module clock disable in SLEEP mode  */
#endif
#define __DRV_CSC_SLP_RTC_CLK_DISABLE()      CSC->SLP0.W &= ~CSC_SLP0_SLP_RTC_mask_w    /*!< RTC module clock disable in SLEEP mode  */
#define __DRV_CSC_SLP_IWDT_CLK_DISABLE()     CSC->SLP0.W &= ~CSC_SLP0_SLP_IWDT_mask_w   /*!< IWDT module clock disable in SLEEP mode */
#define __DRV_CSC_SLP_WWDT_CLK_DISABLE()     CSC->SLP0.W &= ~CSC_SLP0_SLP_WWDT_mask_w   /*!< WWDT module clock disable in SLEEP mode */
#define __DRV_CSC_SLP_I2C0_CLK_DISABLE()     CSC->SLP0.W &= ~CSC_SLP0_SLP_I2C0_mask_w   /*!< I2C0 module clock disable in SLEEP mode */
#if defined(MG32_1ST) || defined(MG32_3RD) || defined(MG32_4TH)
#define __DRV_CSC_SLP_I2C1_CLK_DISABLE()     CSC->SLP0.W &= ~CSC_SLP0_SLP_I2C1_mask_w   /*!< I2C1 module clock disable in SLEEP mode */
#endif
#define __DRV_CSC_SLP_SPI0_CLK_DISABLE()     CSC->SLP0.W &= ~CSC_SLP0_SLP_SPI0_mask_w   /*!< SPI0 module clock disable in SLEEP mode */
#define __DRV_CSC_SLP_URT0_CLK_DISABLE()     CSC->SLP0.W &= ~CSC_SLP0_SLP_URT0_mask_w   /*!< URT0 module clock disable in SLEEP mode */
#define __DRV_CSC_SLP_URT1_CLK_DISABLE()     CSC->SLP0.W &= ~CSC_SLP0_SLP_URT1_mask_w   /*!< URT1 module clock disable in SLEEP mode */
#if defined(MG32_1ST) || defined(MG32_3RD)
#define __DRV_CSC_SLP_URT2_CLK_DISABLE()     CSC->SLP0.W &= ~CSC_SLP0_SLP_URT2_mask_w   /*!< URT2 module clock disable in SLEEP mode */
#endif
#if defined(MG32_1ST)
#define __DRV_CSC_SLP_URT3_CLK_DISABLE()     CSC->SLP0.W &= ~CSC_SLP0_SLP_URT3_mask_w   /*!< URT3 module clock disable in SLEEP mode */
#endif
#if defined(MG32_3RD) || defined(MG32_4TH)
#define __DRV_CSC_SLP_URT4_CLK_DISABLE()     CSC->SLP0.W &= ~CSC_SLP0_SLP_URT4_mask_w   /*!< URT4 module clock disable in SLEEP mode */
#endif
#if defined(MG32_3RD)
#define __DRV_CSC_SLP_URT5_CLK_DISABLE()     CSC->SLP0.W &= ~CSC_SLP0_SLP_URT5_mask_w   /*!< URT5 module clock disable in SLEEP mode */
#define __DRV_CSC_SLP_URT6_CLK_DISABLE()     CSC->SLP0.W &= ~CSC_SLP0_SLP_URT6_mask_w   /*!< URT6 module clock disable in SLEEP mode */
#define __DRV_CSC_SLP_URT7_CLK_DISABLE()     CSC->SLP0.W &= ~CSC_SLP0_SLP_URT7_mask_w   /*!< URT7 module clock disable in SLEEP mode */
#define __DRV_CSC_SLP_USB_CLK_DISABLE()      CSC->SLP0.W &= ~CSC_SLP0_SLP_USB_mask_w    /*!< USB module clock disable in SLEEP mode  */
#endif

#if defined(MG32_3RD)|| defined(MG32_4TH)
#define __DRV_CSC_SLP_APX_CLK_DISABLE()      CSC->SLP0.W &= ~CSC_SLP0_SLP_APX_mask_w    /*!< APX module clock disable in SLEEP mode  */
#endif

#define __DRV_CSC_SLP_TM00_CLK_DISABLE()     CSC->SLP0.W &= ~CSC_SLP1_SLP_TM00_mask_w   /*!< TM00 module clock disable in SLEEP mode */
#define __DRV_CSC_SLP_TM01_CLK_DISABLE()     CSC->SLP0.W &= ~CSC_SLP1_SLP_TM01_mask_w   /*!< TM01 module clock disable in SLEEP mode */
#define __DRV_CSC_SLP_TM10_CLK_DISABLE()     CSC->SLP0.W &= ~CSC_SLP1_SLP_TM10_mask_w   /*!< TM10 module clock disable in SLEEP mode */
#define __DRV_CSC_SLP_TM16_CLK_DISABLE()     CSC->SLP0.W &= ~CSC_SLP1_SLP_TM16_mask_w   /*!< TM16 module clock disable in SLEEP mode */
#if defined(MG32_1ST) || defined(MG32_3RD) || defined(MG32_4TH)
#define __DRV_CSC_SLP_TM20_CLK_DISABLE()     CSC->SLP0.W &= ~CSC_SLP1_SLP_TM20_mask_w   /*!< TM20 module clock disable in SLEEP mode */
#endif
#if defined(MG32_1ST) || defined(MG32_3RD)
#define __DRV_CSC_SLP_TM26_CLK_DISABLE()     CSC->SLP0.W &= ~CSC_SLP1_SLP_TM26_mask_w   /*!< TM26 module clock disable in SLEEP mode */
#endif
#define __DRV_CSC_SLP_TM36_CLK_DISABLE()     CSC->SLP0.W &= ~CSC_SLP1_SLP_TM36_mask_w   /*!< TM36 module clock disable in SLEEP mode */
#if defined(MG32_3RD) || defined(MG32_4TH)
#define __DRV_CSC_SLP_FLASH_CLK_DISABLE()    CSC->SLP0.W &= ~CSC_SLP1_SLP_FLASH_mask_w  /*!< FLASH module clock disable in SLEEP mode    */
#define __DRV_CSC_SLP_SRAM_CLK_DISABLE()     CSC->SLP0.W &= ~CSC_SLP1_SLP_SRAM_mask_w   /*!< SRAM module clock disable in SLEEP mode     */
#define __DRV_CSC_SLP_DMA_CLK_DISABLE()      CSC->SLP0.W &= ~CSC_SLP1_SLP_DMA_mask_w    /*!< DMA module clock disable in SLEEP mode      */
#endif
#if defined(MG32_3RD)
#define __DRV_CSC_SLP_EMB_CLK_DISABLE()      CSC->SLP0.W &= ~CSC_SLP1_SLP_EMB_mask_w    /*!< EMB module clock disable in SLEEP mode      */   
#endif
//!@}


/**
 * @name CSC_Periphery_STOP_Mode_Clock_Enable_Disable
 *      CSC Periphery STOP Mode Clock Enable/Disable
 */
//!@{
#define __DRV_CSC_STP_RTC_CLK_ENABLE()      CSC->STP0.W |= CSC_STP0_STP_RTC_mask_w      /*!< IWDT module clock enable in STOP mode  */
#define __DRV_CSC_STP_IWDT_CLK_ENABLE()     CSC->STP0.W |= CSC_STP0_STP_IWDT_mask_w     /*!< RTC module clock enable in STOP mode   */

#define __DRV_CSC_STP_RTC_CLK_DISABLE()     CSC->STP0.W &= ~CSC_STP0_STP_RTC_mask_w     /*!< IWDT module clock disable in STOP mode */
#define __DRV_CSC_STP_IWDT_CLK_DISABLE()    CSC->STP0.W &= ~CSC_STP0_STP_IWDT_mask_w    /*!< RTC module clock disable in STOP mode  */
//!@}


/**
 * @name CSC_Periphery_Clock_Source_Select
 *      CSC Periphery Clock_Source Select
 */
//!@{
#define __DRV_CSC_ADC0_CKS_CK_APB()     CSC->CKS0.W &= ~CSC_CKS0_ADC0_CKS_mask_w    /*!< ADC0 process clock source CK_APB */
#define __DRV_CSC_CMP_CKS_CK_APB()      CSC->CKS0.W &= ~CSC_CKS0_CMP_CKS_mask_w     /*!< CMP process clock source CK_APB */
#if defined(MG32_1ST) || defined(MG32_3RD)
#define __DRV_CSC_DAC_CKS_CK_APB()      CSC->CKS0.W &= ~CSC_CKS0_DAC_CKS_mask_w     /*!< DAC process clock source CK_APB */
#endif
#if defined(MG32_3RD)|| defined(MG32_4TH)
#define __DRV_CSC_APX_CKS_CK_APB()      CSC->CKS0.W &= ~CSC_CKS0_APX_CKS_mask_w     /*!< APB process clock source CK_APB */
#endif
#define __DRV_CSC_I2C0_CKS_CK_APB()     CSC->CKS1.W &= ~CSC_CKS1_I2C0_CKS_mask_w    /*!< I2C0 process clock source CK_APB */
#if defined(MG32_1ST) || defined(MG32_3RD) || defined(MG32_4TH)
#define __DRV_CSC_I2C1_CKS_CK_APB()     CSC->CKS1.W &= ~CSC_CKS1_I2C1_CKS_mask_w    /*!< I2C1 process clock source CK_APB */
#endif
#define __DRV_CSC_SPI0_CKS_CK_APB()     CSC->CKS1.W &= ~CSC_CKS1_SPI0_CKS_mask_w    /*!< SPI0 process clock source CK_APB */
#define __DRV_CSC_URT0_CKS_CK_APB()     CSC->CKS1.W &= ~CSC_CKS1_URT0_CKS_mask_w    /*!< URT0 process clock source CK_APB */
#define __DRV_CSC_URT1_CKS_CK_APB()     CSC->CKS1.W &= ~CSC_CKS1_URT1_CKS_mask_w    /*!< URT1 process clock source CK_APB */
#if defined(MG32_1ST) || defined(MG32_3RD)
#define __DRV_CSC_URT2_CKS_CK_APB()     CSC->CKS1.W &= ~CSC_CKS1_URT2_CKS_mask_w    /*!< URT2 process clock source CK_APB */
#endif
#if defined(MG32_1ST)
#define __DRV_CSC_URT3_CKS_CK_APB()     CSC->CKS1.W &= ~CSC_CKS1_URT3_CKS_mask_w    /*!< URT3 process clock source CK_APB */
#endif
#if defined(MG32_3RD) || defined(MG32_4TH)
#define __DRV_CSC_URT4_CKS_CK_APB()     CSC->CKS1.W &= ~CSC_CKS1_URT4_CKS_mask_w    /*!< URT4 process clock source CK_APB */
#endif
#if defined(MG32_3RD)
#define __DRV_CSC_URT5_CKS_CK_APB()     CSC->CKS1.W &= ~CSC_CKS1_URT5_CKS_mask_w    /*!< URT5 process clock source CK_APB */
#define __DRV_CSC_URT6_CKS_CK_APB()     CSC->CKS1.W &= ~CSC_CKS1_URT6_CKS_mask_w    /*!< URT6 process clock source CK_APB */
#define __DRV_CSC_URT7_CKS_CK_APB()     CSC->CKS1.W &= ~CSC_CKS1_URT7_CKS_mask_w    /*!< URT7 process clock source CK_APB */
#endif
#define __DRV_CSC_TM00_CKS_CK_APB()     CSC->CKS2.W &= ~CSC_CKS2_TM00_CKS_mask_w    /*!< TM00 process clock source CK_APB */
#define __DRV_CSC_TM01_CKS_CK_APB()     CSC->CKS2.W &= ~CSC_CKS2_TM01_CKS_mask_w    /*!< TM01 process clock source CK_APB */
#define __DRV_CSC_TM10_CKS_CK_APB()     CSC->CKS2.W &= ~CSC_CKS2_TM10_CKS_mask_w    /*!< TM10 process clock source CK_APB */
#define __DRV_CSC_TM16_CKS_CK_APB()     CSC->CKS2.W &= ~CSC_CKS2_TM16_CKS_mask_w    /*!< TM16 process clock source CK_APB */
#if defined(MG32_1ST) || defined(MG32_3RD) || defined(MG32_4TH)
#define __DRV_CSC_TM20_CKS_CK_APB()     CSC->CKS2.W &= ~CSC_CKS2_TM20_CKS_mask_w    /*!< TM20 process clock source CK_APB */
#endif
#if defined(MG32_1ST) || defined(MG32_3RD)
#define __DRV_CSC_TM26_CKS_CK_APB()     CSC->CKS2.W &= ~CSC_CKS2_TM26_CKS_mask_w    /*!< TM26 process clock source CK_APB */
#endif
#define __DRV_CSC_TM36_CKS_CK_APB()     CSC->CKS2.W &= ~CSC_CKS2_TM36_CKS_mask_w    /*!< TM36 process clock source CK_APB */

#define __DRV_CSC_ADC0_CKS_CK_AHB()     CSC->CKS0.W |= CSC_CKS0_ADC0_CKS_mask_w     /*!< ADC0 process clock source CK_AHB */
#define __DRV_CSC_CMP_CKS_CK_AHB()      CSC->CKS0.W |= CSC_CKS0_CMP_CKS_mask_w      /*!< CMP process clock source CK_AHB */
#if defined(MG32_1ST) || defined(MG32_3RD)
#define __DRV_CSC_DAC_CKS_CK_AHB()      CSC->CKS0.W |= CSC_CKS0_DAC_CKS_mask_w      /*!< DAC process clock source CK_AHB */
#endif
#if defined(MG32_3RD) || defined(MG32_4TH)
#define __DRV_CSC_APX_CKS_CK_AHB()      CSC->CKS0.W |= CSC_CKS0_APX_CKS_mask_w      /*!< APB process clock source CK_AHB */
#endif
#define __DRV_CSC_I2C0_CKS_CK_AHB()     CSC->CKS1.W |= CSC_CKS1_I2C0_CKS_mask_w     /*!< I2C0 process clock source CK_AHB */
#if defined(MG32_1ST) || defined(MG32_3RD) || defined(MG32_4TH)
#define __DRV_CSC_I2C1_CKS_CK_AHB()     CSC->CKS1.W |= CSC_CKS1_I2C1_CKS_mask_w     /*!< I2C1 process clock source CK_AHB */
#endif
#define __DRV_CSC_SPI0_CKS_CK_AHB()     CSC->CKS1.W |= CSC_CKS1_SPI0_CKS_mask_w     /*!< SPI0 process clock source CK_AHB */
#define __DRV_CSC_URT0_CKS_CK_AHB()     CSC->CKS1.W |= CSC_CKS1_URT0_CKS_mask_w     /*!< URT0 process clock source CK_AHB */
#define __DRV_CSC_URT1_CKS_CK_AHB()     CSC->CKS1.W |= CSC_CKS1_URT1_CKS_mask_w     /*!< URT1 process clock source CK_AHB */
#if defined(MG32_1ST) || defined(MG32_3RD)
#define __DRV_CSC_URT2_CKS_CK_AHB()     CSC->CKS1.W |= CSC_CKS1_URT2_CKS_mask_w     /*!< URT2 process clock source CK_AHB */
#endif
#if defined(MG32_1ST)
#define __DRV_CSC_URT3_CKS_CK_AHB()     CSC->CKS1.W |= CSC_CKS1_URT3_CKS_mask_w     /*!< URT3 process clock source CK_AHB */
#endif
#if defined(MG32_3RD) || defined(MG32_4TH)
#define __DRV_CSC_URT4_CKS_CK_AHB()     CSC->CKS1.W |= CSC_CKS1_URT4_CKS_mask_w     /*!< URT4 process clock source CK_AHB */
#endif
#if defined(MG32_3RD)
#define __DRV_CSC_URT5_CKS_CK_AHB()     CSC->CKS1.W |= CSC_CKS1_URT5_CKS_mask_w     /*!< URT5 process clock source CK_AHB */
#define __DRV_CSC_URT6_CKS_CK_AHB()     CSC->CKS1.W |= CSC_CKS1_URT6_CKS_mask_w     /*!< URT6 process clock source CK_AHB */
#define __DRV_CSC_URT7_CKS_CK_AHB()     CSC->CKS1.W |= CSC_CKS1_URT7_CKS_mask_w     /*!< URT7 process clock source CK_AHB */
#endif
#define __DRV_CSC_TM00_CKS_CK_AHB()     CSC->CKS2.W |= CSC_CKS2_TM00_CKS_mask_w     /*!< TM00 process clock source CK_AHB */
#define __DRV_CSC_TM01_CKS_CK_AHB()     CSC->CKS2.W |= CSC_CKS2_TM01_CKS_mask_w     /*!< TM01 process clock source CK_AHB */
#define __DRV_CSC_TM10_CKS_CK_AHB()     CSC->CKS2.W |= CSC_CKS2_TM10_CKS_mask_w     /*!< TM10 process clock source CK_AHB */
#define __DRV_CSC_TM16_CKS_CK_AHB()     CSC->CKS2.W |= CSC_CKS2_TM16_CKS_mask_w     /*!< TM16 process clock source CK_AHB */
#if defined(MG32_1ST) || defined(MG32_3RD) || defined(MG32_4TH)
#define __DRV_CSC_TM20_CKS_CK_AHB()     CSC->CKS2.W |= CSC_CKS2_TM20_CKS_mask_w     /*!< TM20 process clock source CK_AHB */
#endif
#if defined(MG32_1ST) || defined(MG32_3RD)
#define __DRV_CSC_TM26_CKS_CK_AHB()     CSC->CKS2.W |= CSC_CKS2_TM26_CKS_mask_w     /*!< TM26 process clock source CK_AHB */
#endif
#define __DRV_CSC_TM36_CKS_CK_AHB()     CSC->CKS2.W |= CSC_CKS2_TM36_CKS_mask_w     /*!< TM36 process clock source CK_AHB */
#if defined(MG32_3RD)
#define __DRV_CSC_USB_CKS_CK_PLL()      CSC->CKS0.W &= ~CSC_CKS0_USB_CKS_mask_w     /*!< USB process clock source CK_PLL */
#define __DRV_CSC_USB_CKS_CK_SYS()      CSC->CKS0.W |= CSC_CKS0_USB_CKS_mask_w      /*!< USB process clock source CK_SYS */
#endif
//!@}



/**
 * @name    Function announce
 *          
 */ 
void MID_CSC_DeInit (void);

void MID_CSC_EnableMCD (MID_CSC_MCD_SEL_TypeDef CSC_MCSSelect);
void MID_CSC_DisableMCD (void);
void MID_CSC_ICKOConfig(MID_CSC_ICKO_Source_TypeDef CSC_ICKOSource, MID_CSC_ICKO_Div_TypeDef CSC_ICKODiv);
void MID_CSC_IRQHandler (void);

void MID_CSC_MCDCallback (void);
void MID_CSC_XOSCCallback (void);
void MID_CSC_IHRCOCallback (void);
void MID_CSC_ILRCOCallback (void);
void MID_CSC_PLLCallback (void);

uint32_t MID_CSC_GetCK_IHRCOFreq(void);
uint32_t MID_CSC_GetCK_HSFreq(void);
#if defined(MG32_3RD) || defined(MG32_4TH)
uint32_t MID_CSC_GetCK_HS2Freq(void);
#endif
uint32_t MID_CSC_GetCK_PLLOFreq(void);
uint32_t MID_CSC_GetCK_MAINFreq(void);
uint32_t MID_CSC_GetCK_APBFreq(void);
uint32_t MID_CSC_GetCK_AHBFreq(void);
uint32_t MID_CSC_GetCK_LSFreq(void);
uint32_t MID_CSC_GetCK_UTFreq(void);
uint32_t MID_CSC_GetCK_PRFreq(uint32_t Module);

#if defined(MG32_3RD)
uint32_t MID_CSC_GetCK_USBFreq (void);
#endif


#ifdef __cplusplus
}
#endif

#endif /* __MG32x02z_CSC_MID_H */



