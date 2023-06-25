/**
 *******************************************************************************
 *
 * @file        MG32x02z_CSC_DRV.h
 *
 * @brief       This is the C code format driver head file for CSC module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.26
 * @date        2022/03/29
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2021 Megawin Technology Co., Ltd.
 *              All rights reserved.
 *
 *******************************************************************************
 * @par         Disclaimer 
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
#include "MG32x02z_GPIO_DRV.h"
#include "MG32x02z_CSC.h"


#ifndef _MG32x02z_CSC_DRV_H
/*!< _MG32x02z_CSC_DRV_H */ 
#define _MG32x02z_CSC_DRV_H

/*! @name 
*/
/* @{ */ 
#define CSC_XOSCF       CSC_STA_XOSCF_mask_w                                            /*!< XOSC clock stable and ready detect flag */
#define CSC_ILRCOF      CSC_STA_ILRCOF_mask_w                                           /*!< ILRCO clock stable and ready detect flag */
#define CSC_IHRCOF      CSC_STA_IHRCOF_mask_w                                           /*!< IHRCO clock stable and ready detect flag */
#define CSC_PLLF        CSC_STA_PLLF_mask_w                                             /*!< PLL clock stable and ready detect flag */
#define CSC_MCDF        CSC_STA_MCDF_mask_w                                             /*!< XOSC missing clock detect failure event flag */
#define CSC_ALLF        CSC_XOSCF | CSC_ILRCOF | CSC_IHRCOF | CSC_PLLF | CSC_MCDF       /*!< All event and interrupt flag */

#define CSC_PLL_STA         CSC_STA_PLL_STA_mask_w      /*!< Select clock source PLL */
#define CSC_IHRCO_STA       CSC_STA_IHRCO_STA_mask_w    /*!< Select clock source IHRCO */
#define CSC_ILRCO_STA       CSC_STA_ILRCO_STA_mask_w    /*!< Select clock source ILRCO */
#define CSC_XOSC_STA        CSC_STA_XOSC_STA_mask_w     /*!< Select clock source XOSC */
#if defined(MG32_3RD) || defined(MG32_4TH)
#define CSC_PLL_LOCKF       CSC_STA_PLL_LOCKF_mask_w    /*!< Select clock source PLL lock */
#endif

#define CSC_INT_XOSC        CSC_INT_XOSC_IE_mask_w      /*!< XOSC clock stable interrupt */
#define CSC_INT_ILRCO       CSC_INT_ILRCO_IE_mask_w     /*!< ILRCO clock stable interrupt */
#define CSC_INT_IHRCO       CSC_INT_IHRCO_IE_mask_w     /*!< IHRCO clock stable interrupt */
#define CSC_INT_PLL         CSC_INT_PLL_IE_mask_w       /*!< PLL clock stable interrupt */
#define CSC_INT_MCD         CSC_INT_MCD_IE_mask_w       /*!< XOSC missing clock detect failure event interrupt */
/* @} */

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

/*! @enum   CSC_PeriphOnMode_TypeDef
    @brief  peripheral on mode configuration.
*/
#if defined(MG32_1ST)
typedef enum
{   
    CSC_ON_PortA    = 0,    /*!< IO Port A clock source */
    CSC_ON_PortB    = 1,    /*!< IO Port B clock source */
    CSC_ON_PortC    = 2,    /*!< IO Port C clock source */
    CSC_ON_PortD    = 3,    /*!< IO Port D clock source */
    CSC_ON_PortE    = 4,    /*!< IO Port E clock source */
    CSC_ON_GPL      = 8,    /*!< GPL clock source */
    CSC_ON_EMB      = 12,   /*!< External memory bus clock source */
    CSC_ON_DMA      = 15,   /*!< DMA clock source */
    CSC_ON_ADC0     = 32,   /*!< ADC module clock source */
    CSC_ON_CMP      = 34,   /*!< CMP module clock source */
    CSC_ON_DAC      = 35,   /*!< DAC module clock source */
    CSC_ON_RTC      = 37,   /*!< RTC module clock source */
    CSC_ON_IWDT     = 38,   /*!< IWDT module clock source */
    CSC_ON_WWDT     = 39,   /*!< WWDT module clock source */
    CSC_ON_I2C0     = 40,   /*!< I2C0 module clock source */
    CSC_ON_I2C1     = 41,   /*!< I2C1 module clock source */
    CSC_ON_SPI0     = 44,   /*!< SPI0 module clock source */
    CSC_ON_UART0    = 48,   /*!< UART0 module clock source */
    CSC_ON_UART1    = 49,   /*!< UART1 module clock source */
    CSC_ON_UART2    = 50,   /*!< UART2 module clock source */
    CSC_ON_UART3    = 51,   /*!< UART3 module clock source */
    CSC_ON_TM00     = 64,   /*!< TM00 module clock source */
    CSC_ON_TM01     = 65,   /*!< TM01 module clock source */
    CSC_ON_TM10     = 68,   /*!< TM10 module clock source */
    CSC_ON_TM16     = 71,   /*!< TM16 module clock source */
    CSC_ON_TM20     = 72,   /*!< TM20 module clock source */
    CSC_ON_TM26     = 75,   /*!< TM26 module clock source */
    CSC_ON_TM36     = 79    /*!< TM36 module clock source */
}CSC_PeriphOnMode_TypeDef;
#endif

#if defined(MG32_2ND)
typedef enum
{   
    CSC_ON_PortA    = 0,    /*!< IO Port A clock source */
    CSC_ON_PortB    = 1,    /*!< IO Port B clock source */
    CSC_ON_PortC    = 2,    /*!< IO Port C clock source */
    CSC_ON_PortD    = 3,    /*!< IO Port D clock source */
    CSC_ON_GPL      = 8,    /*!< GPL clock source */
    CSC_ON_DMA      = 15,   /*!< DMA clock source */
    CSC_ON_ADC0     = 32,   /*!< ADC module clock source */
    CSC_ON_CMP      = 34,   /*!< CMP module clock source */
    CSC_ON_RTC      = 37,   /*!< RTC module clock source */
    CSC_ON_IWDT     = 38,   /*!< IWDT module clock source */
    CSC_ON_WWDT     = 39,   /*!< WWDT module clock source */
    CSC_ON_I2C0     = 40,   /*!< I2C0 module clock source */
    CSC_ON_SPI0     = 44,   /*!< SPI0 module clock source */
    CSC_ON_UART0    = 48,   /*!< UART0 module clock source */
    CSC_ON_UART1    = 49,   /*!< UART1 module clock source */
    CSC_ON_TM00     = 64,   /*!< TM00 module clock source */
    CSC_ON_TM01     = 65,   /*!< TM01 module clock source */
    CSC_ON_TM10     = 68,   /*!< TM10 module clock source */
    CSC_ON_TM16     = 71,   /*!< TM16 module clock source */
    CSC_ON_TM36     = 79    /*!< TM36 module clock source */
}CSC_PeriphOnMode_TypeDef;
#endif

#if defined(MG32_3RD)
typedef enum
{   
    CSC_ON_PortA    = 0,    /*!< IO Port A clock source */
    CSC_ON_PortB    = 1,    /*!< IO Port B clock source */
    CSC_ON_PortC    = 2,    /*!< IO Port C clock source */
    CSC_ON_PortD    = 3,    /*!< IO Port D clock source */
    CSC_ON_PortE    = 4,    /*!< IO Port E clock source */
    CSC_ON_GPL      = 8,    /*!< GPL clock source */
    CSC_ON_EMB      = 12,   /*!< External memory bus clock source */
    CSC_ON_DMA      = 15,   /*!< DMA clock source */
    CSC_ON_ADC0     = 32,   /*!< ADC module clock source */
    CSC_ON_CMP      = 34,   /*!< CMP module clock source */
    CSC_ON_DAC      = 35,   /*!< DAC module clock source */
    CSC_ON_RTC      = 37,   /*!< RTC module clock source */
    CSC_ON_IWDT     = 38,   /*!< IWDT module clock source */
    CSC_ON_WWDT     = 39,   /*!< WWDT module clock source */
    CSC_ON_I2C0     = 40,   /*!< I2C0 module clock source */
    CSC_ON_I2C1     = 41,   /*!< I2C1 module clock source */
    CSC_ON_SPI0     = 44,   /*!< SPI0 module clock source */
    CSC_ON_UART0    = 48,   /*!< UART0 module clock source */
    CSC_ON_UART1    = 49,   /*!< UART1 module clock source */
    CSC_ON_UART2    = 50,   /*!< UART2 module clock source */
    CSC_ON_UART4    = 52,   /*!< UART4 module clock source */
    CSC_ON_UART5    = 53,   /*!< UART5 module clock source */
    CSC_ON_UART6    = 54,   /*!< UART6 module clock source */
    CSC_ON_UART7    = 55,   /*!< UART7 module clock source */
    CSC_ON_USB      = 60,   /*!< USB module clock source */
    CSC_ON_APX      = 61,   /*!< APX module clock source */
    CSC_ON_TM00     = 64,   /*!< TM00 module clock source */
    CSC_ON_TM01     = 65,   /*!< TM01 module clock source */
    CSC_ON_TM10     = 68,   /*!< TM10 module clock source */
    CSC_ON_TM16     = 71,   /*!< TM16 module clock source */
    CSC_ON_TM20     = 72,   /*!< TM20 module clock source */
    CSC_ON_TM26     = 75,   /*!< TM26 module clock source */
    CSC_ON_TM36     = 79    /*!< TM36 module clock source */
}CSC_PeriphOnMode_TypeDef;
#endif

#if defined(MG32_4TH)
typedef enum
{   
    CSC_ON_PortA    = 0,    /*!< IO Port A clock source */  
    CSC_ON_PortB    = 1,    /*!< IO Port B clock source */
    CSC_ON_PortC    = 2,    /*!< IO Port C clock source */  
    CSC_ON_PortD    = 3,    /*!< IO Port D clock source */
    CSC_ON_GPL      = 8,    /*!< GPL clock source */
    CSC_ON_DMA      = 15,   /*!< DMA clock source */
    CSC_ON_ADC0     = 32,   /*!< ADC module clock source */
    CSC_ON_RTC      = 37,   /*!< RTC module clock source */
    CSC_ON_IWDT     = 38,   /*!< IWDT module clock source */
    CSC_ON_WWDT     = 39,   /*!< WWDT module clock source */
    CSC_ON_I2C0     = 40,   /*!< I2C0 module clock source */
    CSC_ON_I2C1     = 41,   /*!< I2C1 module clock source */
    CSC_ON_SPI0     = 44,   /*!< SPI0 module clock source */
    CSC_ON_UART0    = 48,   /*!< UART0 module clock source */
    CSC_ON_UART1    = 49,   /*!< UART1 module clock source */
    CSC_ON_UART4    = 52,   /*!< UART4 module clock source */
    CSC_ON_APX      = 61,   /*!< APX module clock source */
    CSC_ON_TM00     = 64,   /*!< TM00 module clock source */
    CSC_ON_TM01     = 65,   /*!< TM01 module clock source */
    CSC_ON_TM10     = 68,   /*!< TM10 module clock source */
    CSC_ON_TM16     = 71,   /*!< TM16 module clock source */
    CSC_ON_TM20     = 72,   /*!< TM20 module clock source */
    CSC_ON_TM36     = 79    /*!< TM36 module clock source */
}CSC_PeriphOnMode_TypeDef;
#endif


/*! @enum   CSC_PeriphSleepMode_TypeDef
    @brief  peripheral sleep mode configuration.
*/
#if defined(MG32_1ST)
typedef enum
{   
    CSC_SLP_ADC0    = 32,   /*!< ADC module clock in SLEEP mode */
    CSC_SLP_CMP     = 34,   /*!< CMP module clock in SLEEP mode */
    CSC_SLP_DAC     = 35,   /*!< DAC module clock in SLEEP mode */
    CSC_SLP_RTC     = 37,   /*!< RTC module clock in SLEEP mode */
    CSC_SLP_IWDT    = 38,   /*!< IWDT module clock in SLEEP mode */
    CSC_SLP_WWDT    = 39,   /*!< WWDT module clock in SLEEP mode */
    CSC_SLP_I2C0    = 40,   /*!< I2C0 module clock in SLEEP mode */
    CSC_SLP_I2C1    = 41,   /*!< I2C1 module clock in SLEEP mode */
    CSC_SLP_SPI0    = 44,   /*!< SPI0 module clock in SLEEP mode */
    CSC_SLP_UART0   = 48,   /*!< UART0 module clock in SLEEP mode */
    CSC_SLP_UART1   = 49,   /*!< UART1 module clock in SLEEP mode */
    CSC_SLP_UART2   = 50,   /*!< UART2 module clock in SLEEP mode */
    CSC_SLP_UART3   = 51,   /*!< UART3 module clock in SLEEP mode */
    CSC_SLP_TM00    = 64,   /*!< TM00 module clock in SLEEP mode */
    CSC_SLP_TM01    = 65,   /*!< TM01 module clock in SLEEP mode */
    CSC_SLP_TM10    = 68,   /*!< TM10 module clock in SLEEP mode */
    CSC_SLP_TM16    = 71,   /*!< TM16 module clock in SLEEP mode */
    CSC_SLP_TM20    = 72,   /*!< TM20 module clock in SLEEP mode */
    CSC_SLP_TM26    = 75,   /*!< TM26 module clock in SLEEP mode */
    CSC_SLP_TM36    = 79,   /*!< TM36 module clock in SLEEP mode */
    CSC_SLP_EMB     = 94,   /*!< EMB module clock in SLEEP mode */
}CSC_PeriphSleepMode_TypeDef;
#endif

#if defined(MG32_2ND)
typedef enum
{   
    CSC_SLP_ADC0    = 32,   /*!< ADC module clock in SLEEP mode */
    CSC_SLP_CMP     = 34,   /*!< CMP module clock in SLEEP mode */
    CSC_SLP_RTC     = 37,   /*!< RTC module clock in SLEEP mode */
    CSC_SLP_IWDT    = 38,   /*!< IWDT module clock in SLEEP mode */
    CSC_SLP_WWDT    = 39,   /*!< WWDT module clock in SLEEP mode */
    CSC_SLP_I2C0    = 40,   /*!< I2C0 module clock in SLEEP mode */
    CSC_SLP_SPI0    = 44,   /*!< SPI0 module clock in SLEEP mode */
    CSC_SLP_UART0   = 48,   /*!< UART0 module clock in SLEEP mode */
    CSC_SLP_UART1   = 49,   /*!< UART1 module clock in SLEEP mode */
    CSC_SLP_TM00    = 64,   /*!< TM00 module clock in SLEEP mode */
    CSC_SLP_TM01    = 65,   /*!< TM01 module clock in SLEEP mode */
    CSC_SLP_TM10    = 68,   /*!< TM10 module clock in SLEEP mode */
    CSC_SLP_TM16    = 71,   /*!< TM16 module clock in SLEEP mode */
    CSC_SLP_TM36    = 79,   /*!< TM36 module clock in SLEEP mode */
}CSC_PeriphSleepMode_TypeDef;
#endif

#if defined(MG32_3RD)
typedef enum
{   
    CSC_SLP_ADC0    = 32,   /*!< ADC module clock in SLEEP mode */
    CSC_SLP_CMP     = 34,   /*!< CMP module clock in SLEEP mode */
    CSC_SLP_DAC     = 35,   /*!< DAC module clock in SLEEP mode */
    CSC_SLP_RTC     = 37,   /*!< RTC module clock in SLEEP mode */
    CSC_SLP_IWDT    = 38,   /*!< IWDT module clock in SLEEP mode */
    CSC_SLP_WWDT    = 39,   /*!< WWDT module clock in SLEEP mode */
    CSC_SLP_I2C0    = 40,   /*!< I2C0 module clock in SLEEP mode */
    CSC_SLP_I2C1    = 41,   /*!< I2C1 module clock in SLEEP mode */
    CSC_SLP_SPI0    = 44,   /*!< SPI0 module clock in SLEEP mode */
    CSC_SLP_UART0   = 48,   /*!< UART0 module clock in SLEEP mode */
    CSC_SLP_UART1   = 49,   /*!< UART1 module clock in SLEEP mode */
    CSC_SLP_UART2   = 50,   /*!< UART2 module clock in SLEEP mode */
    CSC_SLP_UART4   = 52,   /*!< UART4 module clock in SLEEP mode */
    CSC_SLP_UART5   = 53,   /*!< UART5 module clock in SLEEP mode */
    CSC_SLP_UART6   = 54,   /*!< UART6 module clock in SLEEP mode */
    CSC_SLP_UART7   = 55,   /*!< UART7 module clock in SLEEP mode */
    CSC_SLP_USB     = 60,   /*!< USB module clock in SLEEP mode */
    CSC_SLP_APX     = 61,   /*!< APX module clock in SLEEP mode */
    CSC_SLP_TM00    = 64,   /*!< TM00 module clock in SLEEP mode */
    CSC_SLP_TM01    = 65,   /*!< TM01 module clock in SLEEP mode */
    CSC_SLP_TM10    = 68,   /*!< TM10 module clock in SLEEP mode */
    CSC_SLP_TM16    = 71,   /*!< TM16 module clock in SLEEP mode */
    CSC_SLP_TM20    = 72,   /*!< TM20 module clock in SLEEP mode */
    CSC_SLP_TM26    = 75,   /*!< TM26 module clock in SLEEP mode */
    CSC_SLP_TM36    = 79,   /*!< TM36 module clock in SLEEP mode */
    CSC_SLP_SRAM    = 88,   /*!< SRAM module clock in SLEEP mode */
    CSC_SLP_FLASH   = 89,   /*!< FLASH module clock in SLEEP mode */
    CSC_SLP_DMA     = 93,   /*!< DMA module clock in SLEEP mode */
    CSC_SLP_EMB     = 94,   /*!< EMB module clock in SLEEP mode */
}CSC_PeriphSleepMode_TypeDef;
#endif

#if defined(MG32_4TH)
typedef enum
{   
    CSC_SLP_ADC0    = 32,   /*!< ADC module clock in SLEEP mode */
    CSC_SLP_RTC     = 37,   /*!< RTC module clock in SLEEP mode */
    CSC_SLP_IWDT    = 38,   /*!< IWDT module clock in SLEEP mode */
    CSC_SLP_WWDT    = 39,   /*!< WWDT module clock in SLEEP mode */
    CSC_SLP_I2C0    = 40,   /*!< I2C0 module clock in SLEEP mode */
    CSC_SLP_I2C1    = 41,   /*!< I2C1 module clock in SLEEP mode */
    CSC_SLP_SPI0    = 44,   /*!< SPI0 module clock in SLEEP mode */
    CSC_SLP_UART0   = 48,   /*!< UART0 module clock in SLEEP mode */
    CSC_SLP_UART1   = 49,   /*!< UART1 module clock in SLEEP mode */
    CSC_SLP_UART4   = 52,   /*!< UART4 module clock in SLEEP mode */
    CSC_SLP_APX     = 61,   /*!< APX module clock in SLEEP mode */
    CSC_SLP_TM00    = 64,   /*!< TM00 module clock in SLEEP mode */
    CSC_SLP_TM01    = 65,   /*!< TM01 module clock in SLEEP mode */
    CSC_SLP_TM10    = 68,   /*!< TM10 module clock in SLEEP mode */
    CSC_SLP_TM16    = 71,   /*!< TM16 module clock in SLEEP mode */
    CSC_SLP_TM20    = 72,   /*!< TM20 module clock in SLEEP mode */
    CSC_SLP_TM36    = 79,   /*!< TM36 module clock in SLEEP mode */
    CSC_SLP_SRAM    = 88,   /*!< SRAM module clock in SLEEP mode */
    CSC_SLP_FLASH   = 89,   /*!< FLASH module clock in SLEEP mode */
    CSC_SLP_DMA     = 93,   /*!< DMA module clock in SLEEP mode */
}CSC_PeriphSleepMode_TypeDef;
#endif


/*! @enum   CSC_PeriphStopMode_TypeDef
    @brief  peripheral stop mode configuration.
*/
typedef enum
{   
    CSC_STP_RTC     = 37,   /*!< RTC module clock in STOP mode */
    CSC_STP_IWDT    = 38,   /*!< IWDT module clock in STOP mode */
}CSC_PeriphStopMode_TypeDef;


/*! @enum   CSC_CKS_TypeDef
    @brief  CSC peripheral selection.
*/
#if defined(MG32_1ST)
typedef enum
{
    CSC_ADC0_CKS    = 0,    /*!< ADC0 process clock source */
    CSC_CMP_CKS     = 4,    /*!< CMP process clock source */
    CSC_DAC_CKS     = 5,    /*!< DAC process clock source */
    CSC_I2C0_CKS    = 32,   /*!< I2C0 process clock source */
    CSC_I2C1_CKS    = 34,   /*!< I2C1 process clock source */
    CSC_SPI0_CKS    = 40,   /*!< SPI0 process clock source */
    CSC_UART0_CKS   = 48,   /*!< UART0 process clock source */
    CSC_UART1_CKS   = 50,   /*!< UART1 process clock source */
    CSC_UART2_CKS   = 52,   /*!< UART2 process clock source */
    CSC_UART3_CKS   = 54,   /*!< UART3 process clock source */
    CSC_TM00_CKS    = 64,   /*!< TM01 process clock source */
    CSC_TM01_CKS    = 66,   /*!< TM10 process clock source */
    CSC_TM10_CKS    = 72,   /*!< TM16 process clock source */
    CSC_TM16_CKS    = 78,   /*!< TM20 process clock source */
    CSC_TM20_CKS    = 80,   /*!< TM26 process clock source */
    CSC_TM26_CKS    = 86,   /*!< TM36 process clock source */
    CSC_TM36_CKS    = 94,   /*!< ADC0 process clock source */
}CSC_CKS_TypeDef;
#endif

#if defined(MG32_2ND)
typedef enum
{
    CSC_ADC0_CKS    = 0,    /*!< ADC0 process clock source */
    CSC_CMP_CKS     = 4,    /*!< CMP process clock source */
    CSC_I2C0_CKS    = 32,   /*!< I2C0 process clock source */
    CSC_SPI0_CKS    = 40,   /*!< SPI0 process clock source */
    CSC_UART0_CKS   = 48,   /*!< UART0 process clock source */
    CSC_UART1_CKS   = 50,   /*!< UART1 process clock source */
    CSC_TM00_CKS    = 64,   /*!< TM01 process clock source */
    CSC_TM01_CKS    = 66,   /*!< TM10 process clock source */
    CSC_TM10_CKS    = 72,   /*!< TM16 process clock source */
    CSC_TM16_CKS    = 78,   /*!< TM20 process clock source */
    CSC_TM36_CKS    = 94,   /*!< ADC0 process clock source */
}CSC_CKS_TypeDef;
#endif

#if defined(MG32_3RD)
typedef enum
{
    CSC_ADC0_CKS    = 0,    /*!< ADC0 process clock source */
    CSC_CMP_CKS     = 4,    /*!< CMP process clock source */
    CSC_DAC_CKS     = 5,    /*!< DAC process clock source */
    CSC_APX_CKS     = 10,   /*!< APX process clock source */
    CSC_I2C0_CKS    = 32,   /*!< I2C0 process clock source */
    CSC_I2C1_CKS    = 34,   /*!< I2C1 process clock source */
    CSC_SPI0_CKS    = 40,   /*!< SPI0 process clock source */
    CSC_UART0_CKS   = 48,   /*!< UART0 process clock source */
    CSC_UART1_CKS   = 50,   /*!< UART1 process clock source */
    CSC_UART2_CKS   = 52,   /*!< UART2 process clock source */
    CSC_UART4_CKS   = 56,   /*!< UART4 process clock source */
    CSC_UART5_CKS   = 58,   /*!< UART5 process clock source */
    CSC_UART6_CKS   = 60,   /*!< UART6 process clock source */
    CSC_UART7_CKS   = 62,   /*!< UART7 process clock source */
    CSC_TM00_CKS    = 64,   /*!< TM01 process clock source */
    CSC_TM01_CKS    = 66,   /*!< TM10 process clock source */
    CSC_TM10_CKS    = 72,   /*!< TM16 process clock source */
    CSC_TM16_CKS    = 78,   /*!< TM20 process clock source */
    CSC_TM20_CKS    = 80,   /*!< TM26 process clock source */
    CSC_TM26_CKS    = 86,   /*!< TM36 process clock source */
    CSC_TM36_CKS    = 94,   /*!< ADC0 process clock source */
}CSC_CKS_TypeDef;
#endif

#if defined(MG32_4TH)
typedef enum
{
    CSC_ADC0_CKS    = 0,    /*!< ADC0 process clock source */
    CSC_APX_CKS     = 10,   /*!< APX process clock source */
    CSC_I2C0_CKS    = 32,   /*!< I2C0 process clock source */
    CSC_I2C1_CKS    = 34,   /*!< I2C1 process clock source */
    CSC_SPI0_CKS    = 40,   /*!< SPI0 process clock source */
    CSC_UART0_CKS   = 48,   /*!< UART0 process clock source */
    CSC_UART1_CKS   = 50,   /*!< UART1 process clock source */
    CSC_UART4_CKS   = 56,   /*!< UART4 process clock source */
    CSC_TM00_CKS    = 64,   /*!< TM01 process clock source */
    CSC_TM01_CKS    = 66,   /*!< TM10 process clock source */
    CSC_TM10_CKS    = 72,   /*!< TM16 process clock source */
    CSC_TM16_CKS    = 78,   /*!< TM20 process clock source */
    CSC_TM20_CKS    = 80,   /*!< TM26 process clock source */
    CSC_TM36_CKS    = 94,   /*!< ADC0 process clock source */
}CSC_CKS_TypeDef;
#endif


/*! @enum   CSC_CKSS_TypeDef
    @brief  CSC peripheral clock source selection.
*/
typedef enum
{
    CK_APB      = 0,    /*!< Peripheral clock source select CK_APB */
    CK_AHB      = 1     /*!< Peripheral clock source select CK_AHB */
}CSC_CKSS_TypeDef;


#if defined(MG32_3RD)
/*! @enum   CSC_USB_CKSS_TypeDef
    @brief  CSC USB clock source selection.
*/
typedef enum
{
    CK_PLL      = CSC_CKS0_USB_CKS_ck_pll_b1,   /*!< Peripheral clock source select CK_PLL */
    CK_SYS      = CSC_CKS0_USB_CKS_ck_sys_b1    /*!< Peripheral clock source select CK_SYS */
}CSC_USB_CKSS_TypeDef;
#endif


/*! @enum   CSC_IHRCO_TypeDef
    @brief  CSC IHRCO clock source selection.
*/
typedef enum
{
    IHRCO_12MHz     = 0,    /*!< Select IHECO clock select 12MHz */
    IHRCO_11M0592Hz = 1     /*!< Select IHECO clock select 11.0952MHz */
}CSC_IHRCO_TypeDef;


/*! @enum   CSC_XOSC_GN_TypeDef
    @brief  CSC XTAL gain selection.
*/
typedef enum
{
    Gain_Low            = 0x00,     /*!< Select XOSC gain low for 32.768K */
    Gain_Medium         = 0x01,     /*!< Select XOSC gain medium */
    Gain_Lowest         = 0x02,     /*!< Select XOSC gain lowest for 32.768K */
}CSC_XOSC_GN_TypeDef;


/*! @enum   CSC_MCD_SEL_TypeDef
    @brief  CSC MCD duration time selection.
*/
typedef enum
{
    MCD_Duration_125us      = 0x00,     /*!< Select MCD Duration 125us */
    MCD_Duration_250us      = 0x40,     /*!< Select MCD Duration 250us */
    MCD_Duration_500us      = 0x80,     /*!< Select MCD Duration 500us */
    MCD_Duration_1ms        = 0xC0      /*!< Select MCD Duration 1ms */
}CSC_MCD_SEL_TypeDef;
  
  
/*! @enum   CSC_PLL_MUL_TypeDef
    @brief  CSC PLL Multiplication selection.
*/
typedef enum
{
    PLLIx16         = 0x0000,   /*!< Select PLL input clock x 16 */
    PLLIx24         = 0x0100,   /*!< Select PLL input clock x 24 */
#if defined(MG32_3RD) || defined(MG32_4TH) 
    PLLI_CLKx4      = 0x0600,   /*!< Select PLL input clock x 04 */
    PLLI_CLKx5      = 0x0800,   /*!< Select PLL input clock x 05 */
    PLLI_CLKx6      = 0x0A00,   /*!< Select PLL input clock x 06 */
    PLLI_CLKx7      = 0x0C00,   /*!< Select PLL input clock x 07 */
    PLLI_CLKx8      = 0x0E00,   /*!< Select PLL input clock x 08 */
    PLLI_CLKx9      = 0x1000,   /*!< Select PLL input clock x 09 */
    PLLI_CLKx10     = 0x1200,   /*!< Select PLL input clock x 10 */
    PLLI_CLKx11     = 0x1400,   /*!< Select PLL input clock x 11 */
    PLLI_CLKx12     = 0x1600,   /*!< Select PLL input clock x 12 */
    PLLI_CLKx13     = 0x1800,   /*!< Select PLL input clock x 13 */
    PLLI_CLKx14     = 0x1A00,   /*!< Select PLL input clock x 14 */
    PLLI_CLKx15     = 0x1C00,   /*!< Select PLL input clock x 15 */
    PLLI_CLKx16     = 0x1E00,   /*!< Select PLL input clock x 16 */
    PLLI_CLKx17     = 0x2000,   /*!< Select PLL input clock x 17 */
    PLLI_CLKx18     = 0x2200,   /*!< Select PLL input clock x 18 */
    PLLI_CLKx19     = 0x2400,   /*!< Select PLL input clock x 19 */
    PLLI_CLKx20     = 0x2600,   /*!< Select PLL input clock x 20 */
    PLLI_CLKx21     = 0x2800,   /*!< Select PLL input clock x 21 */
    PLLI_CLKx22     = 0x2A00,   /*!< Select PLL input clock x 22 */
    PLLI_CLKx23     = 0x2C00,   /*!< Select PLL input clock x 23 */
    PLLI_CLKx24     = 0x2E00,   /*!< Select PLL input clock x 24 */
    PLLI_CLKx25     = 0x3000,   /*!< Select PLL input clock x 25 */
    PLLI_CLKx26     = 0x3200,   /*!< Select PLL input clock x 26 */
    PLLI_CLKx27     = 0x3400,   /*!< Select PLL input clock x 27 */
    PLLI_CLKx28     = 0x3600,   /*!< Select PLL input clock x 28 */
    PLLI_CLKx29     = 0x3800,   /*!< Select PLL input clock x 29 */
    PLLI_CLKx30     = 0x3A00,   /*!< Select PLL input clock x 30 */
    PLLI_CLKx31     = 0x3C00,   /*!< Select PLL input clock x 31 */
    PLLI_CLKx32     = 0x3E00,   /*!< Select PLL input clock x 32 */
#endif
}CSC_PLL_MUL_TypeDef;
      
  
/*! @enum   CSC_PLLI_DIV_TypeDef
    @brief  CSC PLL input divider selection.
*/      
typedef enum
{
    PLLI_DIV_1      = 0x00,     /*!< Select PLL input clock divided by 1 */
    PLLI_DIV_2      = 0x01,     /*!< Select PLL input clock divided by 2 */
    PLLI_DIV_4      = 0x02,     /*!< Select PLL input clock divided by 4 */
    PLLI_DIV_6      = 0x03      /*!< Select PLL input clock divided by 6 */
}CSC_PLLI_DIV_TypeDef;


/*! @enum   CSC_PLLO_DIV_TypeDef
    @brief  CSC PLL output divider selection.
*/     
typedef enum
{
    PLLO_DIV_1      = 0x30,     /*!< Select PLL output clock divided by 1 */
    PLLO_DIV_2      = 0x20,     /*!< Select PLL output clock divided by 2 */
    PLLO_DIV_3      = 0x10,     /*!< Select PLL output clock divided by 3 */
    PLLO_DIV_4      = 0x00      /*!< Select PLL output clock divided by 4 */
}CSC_PLLO_DIV_TypeDef;






/*! @enum   CSC_PLLI_SEL_TypeDef
    @brief  CSC PLL input clock source select
*/
typedef enum
{
    PLLI_SEL_HS         = 0x0000,   /*!<Select PLL input CK_HS */
    PLLI_SEL_HS2        = 0x0002    /*!<Select PLL input CK_HS2 */
}CSC_PLLI_SEL_TypeDef;



/*! @enum   CSC_ST_SEL_TypeDef
    @brief  CSC CK_ST clock source selection.
*/  
typedef enum
{
    ST_HCLK_DIV_8       = 0x00,     /*!< Select clock source HCLK divided by 8 */
    ST_CK_LS_DIV_2      = 0x01      /*!< Select clock source CK_LS divided by 2 */
}CSC_ST_SEL_TypeDef;


/*! @enum   CSC_MAIN_SEL_TypeDef
    @brief  CSC CK_MAIN clock sourcr selection.
*/  
typedef enum
{
    MAIN_CK_HS       = 0x00,     /*!< Select clock source CK_HS */
    MAIN_CK_PLLI     = 0x40,     /*!< Select clock source CK_HS */
    MAIN_CK_PLLO     = 0x80      /*!< Select clock source CK_HS */
}CSC_MAIN_SEL_TypeDef;


/*! @enum   CSC_HS_SEL_TypeDef
    @brief  CSC CK_HS clock sourcr selection.
*/ 
typedef enum
{
    HS_CK_IHRCO     = 0x00,     /*!< Select clock source CK_IHRCO */
    HS_CK_XOSC      = 0x04,     /*!< Select clock source CK_XOSC */
    HS_CK_ILRCO     = 0x08,     /*!< Select clock source CK_ILRCO */
    HS_CK_EXT       = 0x0C      /*!< Select clock source CK_EXT */
}CSC_HS_SEL_TypeDef;


/*! @enum   CSC_LS_SEL_TypeDef
    @brief  CSC CK_LS clock sourcr selection.
*/ 
typedef enum
{
    LS_CK_XOSC      = 0x01,     /*!< Select clock source CK_ILECO */
    LS_CK_ILRCO     = 0x02,     /*!< Select clock source CK_ILECO */
    LS_CK_EXT       = 0x03      /*!< Select clock source  */
}CSC_LS_SEL_TypeDef;


/*! @enum   CSC_APB_DIV_TypeDef
    @brief  CSC CK_APV clock divider selection.
*/ 
typedef enum
{
    APB_DIV_1       = 0x00,     /*!< Select clock source divided by 1 */
    APB_DIV_2       = 0x01,     /*!< Select clock source divided by 2 */
    APB_DIV_4       = 0x02,     /*!< Select clock source divided by 4 */
    APB_DIV_8       = 0x03,     /*!< Select clock source divided by 8 */
    APB_DIV_16      = 0x04      /*!< Select clock source divided by 16 */
}CSC_APB_DIV_TypeDef;


/*! @enum   CSC_UT_DIV_TypeDef
    @brief  CSC CK_UT clock divider selection.
*/ 
typedef enum
{
    UT_DIV_8        = 0x04,     /*!< Select clock source divided by 8 */
    UT_DIV_16       = 0x08,     /*!< Select clock source divided by 16 */
    UT_DIV_32       = 0x00,     /*!< Select clock source divided by 32 */
    UT_DIV_128      = 0x0C      /*!< Select clock source divided by 128 */
}CSC_UT_DIV_TypeDef;


/*! @enum   CSC_AHB_DIV_TypeDef
    @brief  CSC CK_AHB clock divider selection. 
*/ 
typedef enum
{
    AHB_DIV_1       = 0x00,     /*!< Select clock source divided by 1 */
    AHB_DIV_2       = 0x01,     /*!< Select clock source divided by 2 */
    AHB_DIV_4       = 0x02,     /*!< Select clock source divided by 4 */
    AHB_DIV_8       = 0x03,     /*!< Select clock source divided by 8 */
    AHB_DIV_16      = 0x04,     /*!< Select clock source divided by 16 */
    AHB_DIV_32      = 0x05,     /*!< Select clock source divided by 32 */
    AHB_DIV_64      = 0x06,     /*!< Select clock source divided by 64 */
    AHB_DIV_128     = 0x07,     /*!< Select clock source divided by 128 */
    AHB_DIV_256     = 0x08,     /*!< Select clock source divided by 256 */
    AHB_DIV_512     = 0x09,     /*!< Select clock source divided by 512 */
}CSC_AHB_DIV_TypeDef;


#if defined(MG32_3RD) 
/*! @enum   CSC_USB_SIE_DIV_TypeDef
    @brief  CSC CK_APV clock divider selection.
*/ 
typedef enum
{
    USB_SIE_DIV_1       = 0x00,     /*!< Select USB SIE divided by 1 */
    USB_SIE_DIV_2       = 0x10,     /*!< Select USB SIE divided by 2 */
    USB_SIE_DIV_3       = 0x20,     /*!< Select USB SIE divided by 3 */
    USB_SIE_DIV_4       = 0x30      /*!< Select USB SIE divided by 4 */
}CSC_USB_SIE_DIV_TypeDef;
#endif


/*! @enum   CSC_CKO_SEL_TypeDef
    @brief  CSC ICKO clock source selection.
*/ 
typedef enum
{
    ICKO_CK_MAIN    = 0x00,     /*!< Select clock source CK_MAIN */
    ICKO_CK_AHB     = 0x10,     /*!< Select clock source CK_AHB */
    ICKO_CK_APB     = 0x20,     /*!< Select clock source CK_APB */
    ICKO_CK_HS      = 0x30,     /*!< Select clock source CK_HS */
    ICKO_CK_LS      = 0x40,     /*!< Select clock source CK_LS */
    ICKO_CK_XOSC    = 0x50      /*!< Select clock source CK_XOSC */
}CSC_CKO_SEL_TypeDef;


/*! @enum   CSC_CKO_DIV_TypeDef
    @brief  CSC ICKO clock divider selection.
*/ 
typedef enum
{
    ICKO_DIV_1      = 0x00,     /*!< Select clock source divided by 1 */
    ICKO_DIV_2      = 0x04,     /*!< Select clock source divided by 2 */
    ICKO_DIV_4      = 0x08,     /*!< Select clock source divided by 4 */
    ICKO_DIV_8      = 0x0C      /*!< Select clock source divided by 8 */
}CSC_CKO_DIV_TypeDef;


/*! @enum   CSC_MAIN_MUX_STA_TypeDef
    @brief  CSC clock MAIN MUX state
*/ 
typedef enum
{
    MAIN_MUX_HS     = 0x01,     /*!< MAIN MUX check HS */
    MAIN_MUX_PLLI   = 0x02,     /*!< MAIN MUX check PLLI */
    MAIN_MUX_PLLO   = 0x04      /*!< MAIN MUX check PLLO */
}CSC_MAIN_MUX_STA_TypeDef;


/*! @enum   CSC_HS_MUX_STA_TypeDef
    @brief  CSC clock HS MUX state
*/ 
typedef enum
{
    HS_MUX_IHRCO    = 0x01,     /*!< HS MUX check IHRCO */
    HS_MUX_XOSC     = 0x02,     /*!< HS MUX check XOSC */
    HS_MUX_ILRCO    = 0x04,     /*!< HS MUX check ILRCO */
    HS_MUX_CK_EXT   = 0x08      /*!< HS MUX check CK_EXT */
}CSC_HS_MUX_STA_TypeDef;


/*! @enum   CSC_LS_MUX_STA_TypeDef
    @brief  CSC clock LS MUX state
*/ 
typedef enum
{
    LS_MUX_XOSC     = 0x02,     /*!< LS MUX check XOSC */
    LS_MUX_ILRCO    = 0x04,     /*!< LS MUX check ILRCO */
    LS_MUX_CK_EXT   = 0x08      /*!< LS MUX check CK_EXT */
}CSC_LS_MUX_STA_TypeDef;


/*! @enum   CSC_PLLI_MUX_STA_TypeDef
    @brief  CSC PLLI MUX state
*/ 
typedef enum
{
    PLLI_MUX_HS     = 0x01,     /*!< LS MUX check HS */
    PLLI_MUX_HS2    = 0x02,     /*!< LS MUX check HS2 */

}CSC_PLLI_MUX_STA_TypeDef;



/** 
 * @struct  CSC_PLL_TypeDef
 * @brief   CSC PLL initial structure.
 */
#if defined(MG32_1ST) || defined(MG32_2ND)
typedef struct __attribute__((packed))
{
    CSC_PLLI_DIV_TypeDef    InputDivider;               /*!< PLL input divider: PLLI_DIV_1/2/4/6 */
    CSC_PLL_MUL_TypeDef     Multiplication;             /*!< PLL Multiplication */
    CSC_PLLO_DIV_TypeDef    OutputDivider;              /*!< PLL input divider: PLLO_DIV_1/2/3/4 */
}CSC_PLL_TypeDef;
#endif

#if defined(MG32_3RD) || defined(MG32_4TH)
typedef struct __attribute__((packed))
{
    CSC_PLLI_DIV_TypeDef    InputDivider;               /*!< PLL input divider: PLLI_DIV_1/2/4/6 */
    CSC_PLL_MUL_TypeDef     Multiplication;             /*!< PLL Multiplication */
    CSC_PLLO_DIV_TypeDef    OutputDivider;              /*!< PLL input divider: PLLO_DIV_1/2/3/4 */
    CSC_PLLI_SEL_TypeDef    PLLInputClockSelect;        /*!< PLL input clock source select */
}CSC_PLL_TypeDef;
#endif


/*! @name
*/       
/* @{ */ 
#define CSC_PeriphOnModeClock_Config      CSC_PeriphONModeClock_Config
#define CSC_PeriphSleepModeClock_Config   CSC_PeriphSLEEPModeClock_Config
#define CSC_PeriphStopModeClock_Config    CSC_PeriphSTOPModeClock_Config

/**
 * @name    Function announce
 *
 */ 
void CSC_IHRCO_Cmd (FunctionalState NewState);
void CSC_IHRCO_Select (CSC_IHRCO_TypeDef Freq);
void CSC_XOSC_Cmd (FunctionalState NewState);
void CSC_XOSCGain_Select (CSC_XOSC_GN_TypeDef CSC_XoscGain);
void CSC_CK_ST_Select (CSC_ST_SEL_TypeDef CSC_CK_ST_SEL);
void CSC_CK_MAIN_Select (CSC_MAIN_SEL_TypeDef CSC_CK_MAIN_SEL);
void CSC_CK_HS_Select (CSC_HS_SEL_TypeDef CSC_CK_HS_SEL);
void CSC_CK_HS2_Select (CSC_HS_SEL_TypeDef CSC_CK_HS2_SEL);
void CSC_CK_LS_Select (CSC_LS_SEL_TypeDef CSC_CK_LS_SEL);

void CSC_PLL_Config (CSC_PLL_TypeDef* CSC_PLL_CFG);
void CSC_PLL_Cmd (FunctionalState NewState);

void CSC_CK_APB_Divider_Select (CSC_APB_DIV_TypeDef CSC_CK_APB_DIVS);
void CSC_CK_UT_Divider_Select (CSC_UT_DIV_TypeDef CSC_CK_UT_DIVS);
void CSC_CK_AHB_Divider_Select (CSC_AHB_DIV_TypeDef CSC_CK_AHB_DIVS);

void CSC_ICKO_ClockSource_Select (CSC_CKO_SEL_TypeDef ICKO_CKS_SEL);
void CSC_ICKO_Divider_Select (CSC_CKO_DIV_TypeDef CSC_ICKO_DIVS);
void CSC_ICKO_Cmd (FunctionalState NewState);

void CSC_MissingClockDetectionDuration_Select (CSC_MCD_SEL_TypeDef CSC_MCDDuration);
void CSC_MissingClockDetection_Cmd (FunctionalState NewState);

void CSC_PeriphProcessClockSource_Config (CSC_CKS_TypeDef CSC_Periph, CSC_CKSS_TypeDef CSC_CKS);
void CSC_PeriphONModeClock_Config (CSC_PeriphOnMode_TypeDef CSC_Periph, FunctionalState NewState);
void CSC_PeriphSLEEPModeClock_Config (CSC_PeriphSleepMode_TypeDef CSC_Periph, FunctionalState NewState);
void CSC_PeriphSTOPModeClock_Config (CSC_PeriphStopMode_TypeDef CSC_Periph, FunctionalState NewState);

#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
DRV_Return CSC_GetClockSourceState (uint32_t CLK_SEL);
DRV_Return CSC_GetMainSwitchState (CSC_MAIN_MUX_STA_TypeDef MAIN_MUX_STA);
DRV_Return CSC_GetHsSwitchState (CSC_HS_MUX_STA_TypeDef HS_MUX_STA);
DRV_Return CSC_GetLsSwitchState (CSC_LS_MUX_STA_TypeDef LS_MUX_STA);
#endif

#if defined(MG32_3RD) || defined(MG32_4TH)
DRV_Return CSC_GetHS2SwitchState (CSC_HS_MUX_STA_TypeDef HS2_MUX_STA);
DRV_Return CSC_GetPLLISwitchState (CSC_PLLI_MUX_STA_TypeDef PLLI_MUX_STA);
#endif

#if defined(MG32_3RD)
void CSC_CK_USB_Divider_Select (CSC_USB_SIE_DIV_TypeDef CSC_USB_SIE_DIVS);
void CSC_CK_USB_ClockSource_Select (CSC_USB_CKSS_TypeDef CSC_USB_CKS);
#endif

uint32_t CSC_GetAllFlagStatus (void);
DRV_Return CSC_GetSingleFlagStatus (uint32_t CSC_ITSrc);
void CSC_ClearFlag (uint32_t CSC_ITSrc);
void CSC_IT_Config (uint32_t CSC_ITSrc, FunctionalState NewState);
void CSC_ITEA_Cmd (FunctionalState NewState);

#ifdef __cplusplus
}
#endif // __cplusplus



#endif  // _MG32x02z_CSC_DRV_H

