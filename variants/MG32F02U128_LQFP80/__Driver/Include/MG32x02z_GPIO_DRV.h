

/**
 ******************************************************************************
 *
 * @file        MG32x02z_GPIO_DRV.H
 *
 * @brief       This file contains all the functions prototypes for the GPIO
 *              firmware library.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.13
 * @date        2022/03/25
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
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
 
#ifndef __MG32x02z_GPIO_DRV_H
#define __MG32x02z_GPIO_DRV_H 
 
#include "MG32x02z__Common_DRV.h"
#include "MG32x02z_GPIO.h" 
 
 
/*! @name 
*/
/* @{ */
#define PX_Pin_0                ((uint16_t)0x0001)  /*!< Pin 0 selected    */
#define PX_Pin_1                ((uint16_t)0x0002)  /*!< Pin 1 selected    */
#define PX_Pin_2                ((uint16_t)0x0004)  /*!< Pin 2 selected    */
#define PX_Pin_3                ((uint16_t)0x0008)  /*!< Pin 3 selected    */
#define PX_Pin_4                ((uint16_t)0x0010)  /*!< Pin 4 selected    */
#define PX_Pin_5                ((uint16_t)0x0020)  /*!< Pin 5 selected    */
#define PX_Pin_6                ((uint16_t)0x0040)  /*!< Pin 6 selected    */
#define PX_Pin_7                ((uint16_t)0x0080)  /*!< Pin 7 selected    */
#define PX_Pin_8                ((uint16_t)0x0100)  /*!< Pin 8 selected    */
#define PX_Pin_9                ((uint16_t)0x0200)  /*!< Pin 9 selected    */
#define PX_Pin_10               ((uint16_t)0x0400)  /*!< Pin 10 selected   */
#define PX_Pin_11               ((uint16_t)0x0800)  /*!< Pin 11 selected   */
#define PX_Pin_12               ((uint16_t)0x1000)  /*!< Pin 12 selected   */
#define PX_Pin_13               ((uint16_t)0x2000)  /*!< Pin 13 selected   */
#define PX_Pin_14               ((uint16_t)0x4000)  /*!< Pin 14 selected   */
#define PX_Pin_15               ((uint16_t)0x8000)  /*!< Pin 15 selected   */
#define PX_Pin_All              ((uint16_t)0xFFFF)  /*!< All pins selected */

#define GPIO_PIN_MASK              ((uint32_t)0x0000FFFF) /* PIN mask for assert test */
/* @} */

/*! @name 
*/
/* @{ */ 
#define PX(GPIOX,PinNum)        *((volatile uint8_t*)((uint32_t)GPIOX + PinNum + 0x10))    /*!< GPIOX pin (PinNum) read /write */


#if defined(GPIOA_Base)
    #if defined(PA_CR0_default)
        #define PA0                     PX(GPIOA_Base,0)            /*!< PA0 read / write */
    #endif
    #if defined(PA_CR1_default)
        #define PA1                     PX(GPIOA_Base,1)            /*!< PA1 read / write */
    #endif
    #if defined(PA_CR2_default)
        #define PA2                     PX(GPIOA_Base,2)            /*!< PA2 read / write */
    #endif
    #if defined(PA_CR3_default)
        #define PA3                     PX(GPIOA_Base,3)            /*!< PA3 read / write */
    #endif
    #if defined(PA_CR4_default)
        #define PA4                     PX(GPIOA_Base,4)            /*!< PA4 read / write */
    #endif
    #if defined(PA_CR5_default)
        #define PA5                     PX(GPIOA_Base,5)            /*!< PA5 read / write */
    #endif
    #if defined(PA_CR6_default)
        #define PA6                     PX(GPIOA_Base,6)            /*!< PA6 read / write */
    #endif
    #if defined(PA_CR7_default)
        #define PA7                     PX(GPIOA_Base,7)            /*!< PA7 read / write */
    #endif
    #if defined(PA_CR8_default)
        #define PA8                     PX(GPIOA_Base,8)            /*!< PA8 read / write */
    #endif
    #if defined(PA_CR9_default)
        #define PA9                     PX(GPIOA_Base,9)            /*!< PA9 read / write */
    #endif
    #if defined(PA_CR10_default)
        #define PA10                    PX(GPIOA_Base,10)           /*!< PA10 read / write */
    #endif
    #if defined(PA_CR11_default)
        #define PA11                    PX(GPIOA_Base,11)           /*!< PA11 read / write */
    #endif
    #if defined(PA_CR12_default)
        #define PA12                    PX(GPIOA_Base,12)           /*!< PA12 read / write */
    #endif
    #if defined(PA_CR13_default)
        #define PA13                    PX(GPIOA_Base,13)           /*!< PA13 read / write */
    #endif
    #if defined(PA_CR14_default)
        #define PA14                    PX(GPIOA_Base,14)           /*!< PA14 read / write */
    #endif
    #if defined(PA_CR15_default)
        #define PA15                    PX(GPIOA_Base,15)           /*!< PA15 read / write */
    #endif
#endif

#if defined(GPIOB_Base)
    #if defined(PB_CR0_default)
        #define PB0                     PX(GPIOB_Base,0)            /*!< PB0 read / write */
    #endif
    #if defined(PB_CR1_default)
        #define PB1                     PX(GPIOB_Base,1)            /*!< PB1 read / write */
    #endif    
    #if defined(PB_CR2_default)
        #define PB2                     PX(GPIOB_Base,2)            /*!< PB2 read / write */
    #endif
    #if defined(PB_CR3_default)
        #define PB3                     PX(GPIOB_Base,3)            /*!< PB3 read / write */
    #endif
    #if defined(PB_CR4_default)
        #define PB4                     PX(GPIOB_Base,4)            /*!< PB4 read / write */
    #endif
    #if defined(PB_CR5_default)
        #define PB5                     PX(GPIOB_Base,5)            /*!< PB5 read / write */
    #endif
    #if defined(PB_CR6_default)
        #define PB6                     PX(GPIOB_Base,6)            /*!< PB6 read / write */
    #endif
    #if defined(PB_CR7_default)
        #define PB7                     PX(GPIOB_Base,7)            /*!< PB7 read / write */
    #endif
    #if defined(PB_CR8_default)
        #define PB8                     PX(GPIOB_Base,8)            /*!< PB8 read / write */
    #endif
    #if defined(PB_CR9_default)
        #define PB9                     PX(GPIOB_Base,9)            /*!< PB9 read / write */
    #endif
    #if defined(PB_CR10_default)
        #define PB10                    PX(GPIOB_Base,10)           /*!< PB10 read / write */
    #endif
    #if defined(PB_CR11_default)
        #define PB11                    PX(GPIOB_Base,11)           /*!< PB11 read / write */
    #endif
    #if defined(PB_CR12_default)
        #define PB12                    PX(GPIOB_Base,12)           /*!< PB12 read / write */
    #endif
    #if defined(PB_CR13_default)
        #define PB13                    PX(GPIOB_Base,13)           /*!< PB13 read / write */
    #endif
    #if defined(PB_CR14_default)
        #define PB14                    PX(GPIOB_Base,14)           /*!< PB14 read / write */
    #endif
    #if defined(PB_CR15_default)
        #define PB15                    PX(GPIOB_Base,15)           /*!< PB15 read / write */
    #endif
#endif

#if defined(GPIOC_Base)
    #if defined(PC_CR0_default)
        #define PC0                     PX(GPIOC_Base,0)            /*!< PC0 read / write */
    #endif
    #if defined(PC_CR1_default)
        #define PC1                     PX(GPIOC_Base,1)            /*!< PC1 read / write */
    #endif
    #if defined(PC_CR2_default)
        #define PC2                     PX(GPIOC_Base,2)            /*!< PC2 read / write */
    #endif
    #if defined(PC_CR3_default)
        #define PC3                     PX(GPIOC_Base,3)            /*!< PC3 read / write */
    #endif
    #if defined(PC_CR4_default)
        #define PC4                     PX(GPIOC_Base,4)            /*!< PC4 read / write */
    #endif
    #if defined(PC_CR5_default)
        #define PC5                     PX(GPIOC_Base,5)            /*!< PC5 read / write */
    #endif
    #if defined(PC_CR6_default)
        #define PC6                     PX(GPIOC_Base,6)            /*!< PC6 read / write */
    #endif
    #if defined(PC_CR7_default)
        #define PC7                     PX(GPIOC_Base,7)            /*!< PC7 read / write */
    #endif
    #if defined(PC_CR8_default)
        #define PC8                     PX(GPIOC_Base,8)            /*!< PC8 read / write */
    #endif
    #if defined(PC_CR9_default)
        #define PC9                     PX(GPIOC_Base,9)            /*!< PC9 read / write */
    #endif
    #if defined(PC_CR10_default)
        #define PC10                    PX(GPIOC_Base,10)           /*!< PC10 read / write */
    #endif
    #if defined(PC_CR11_default)
        #define PC11                    PX(GPIOC_Base,11)           /*!< PC11 read / write */
    #endif
    #if defined(PC_CR12_default)
        #define PC12                    PX(GPIOC_Base,12)           /*!< PC12 read / write */
    #endif
    #if defined(PC_CR13_default)
        #define PC13                    PX(GPIOC_Base,13)           /*!< PC13 read / write */
    #endif
    #if defined(PC_CR14_default)
        #define PC14                    PX(GPIOC_Base,14)           /*!< PC14 read / write */
    #endif
    #if defined(PC_CR15_default)
        #define PC15                    PX(GPIOC_Base,15)           /*!< PC15 read / write */
    #endif
#endif

#if defined(GPIOD_Base)
    #if defined(PD_CR0_default)
        #define PD0                     PX(GPIOD_Base,0)            /*!< PD0 read / write */
    #endif
    #if defined(PD_CR1_default)
        #define PD1                     PX(GPIOD_Base,1)            /*!< PD1 read / write */
    #endif
    #if defined(PD_CR2_default)
        #define PD2                     PX(GPIOD_Base,2)            /*!< PD2 read / write */
    #endif
    #if defined(PD_CR3_default)
        #define PD3                     PX(GPIOD_Base,3)            /*!< PD3 read / write */
    #endif
    #if defined(PD_CR4_default)
        #define PD4                     PX(GPIOD_Base,4)            /*!< PD4 read / write */
    #endif
    #if defined(PD_CR5_default)
        #define PD5                     PX(GPIOD_Base,5)            /*!< PD5 read / write */
    #endif
    #if defined(PD_CR6_default)
        #define PD6                     PX(GPIOD_Base,6)            /*!< PD6 read / write */
    #endif
    #if defined(PD_CR7_default)
        #define PD7                     PX(GPIOD_Base,7)            /*!< PD7 read / write */
    #endif
    #if defined(PD_CR8_default)
        #define PD8                     PX(GPIOD_Base,8)            /*!< PD8 read / write */
    #endif
    #if defined(PD_CR9_default)
        #define PD9                     PX(GPIOD_Base,9)            /*!< PD9 read / write */
    #endif
    #if defined(PD_CR10_default)
        #define PD10                    PX(GPIOD_Base,10)           /*!< PD10 read / write */
    #endif
    #if defined(PD_CR11_default)
        #define PD11                    PX(GPIOD_Base,11)           /*!< PD11 read / write */
    #endif
    #if defined(PD_CR12_default)
        #define PD12                    PX(GPIOD_Base,12)           /*!< PD12 read / write */
    #endif
    #if defined(PD_CR13_default)
        #define PD13                    PX(GPIOD_Base,13)           /*!< PD13 read / write */
    #endif
    #if defined(PD_CR14_default)
        #define PD14                    PX(GPIOD_Base,14)           /*!< PD14 read / write */
    #endif
    #if defined(PD_CR15_default)
        #define PD15                    PX(GPIOD_Base,15)           /*!< PD15 read / write */
    #endif
#endif

#if defined(GPIOE_Base)
    #if defined(PE_CR0_default)
        #define PE0                     PX(GPIOE_Base,0)            /*!< PE0 read / write */
    #endif
    #if defined(PE_CR1_default)
        #define PE1                     PX(GPIOE_Base,1)            /*!< PE1 read / write */
    #endif
    #if defined(PE_CR2_default)
        #define PE2                     PX(GPIOE_Base,2)            /*!< PE2 read / write */
    #endif
    #if defined(PE_CR3_default)
        #define PE3                     PX(GPIOE_Base,3)            /*!< PE3 read / write */
    #endif
    #if defined(PE_CR4_default)
        #define PE4                     PX(GPIOE_Base,4)            /*!< PE4 read / write */
    #endif
    #if defined(PE_CR5_default)
        #define PE5                     PX(GPIOE_Base,5)            /*!< PE5 read / write */
    #endif
    #if defined(PE_CR6_default)
        #define PE6                     PX(GPIOE_Base,6)            /*!< PE6 read / write */
    #endif
    #if defined(PE_CR7_default)
        #define PE7                     PX(GPIOE_Base,7)            /*!< PE7 read / write */
    #endif
    #if defined(PE_CR8_default)
        #define PE8                     PX(GPIOE_Base,8)            /*!< PE8 read / write */
    #endif
    #if defined(PE_CR9_default)
        #define PE9                     PX(GPIOE_Base,9)            /*!< PE9 read / write */
    #endif
    #if defined(PE_CR10_default)
        #define PE10                    PX(GPIOE_Base,10)           /*!< PE10 read / write */
    #endif
    #if defined(PE_CR11_default)
        #define PE11                    PX(GPIOE_Base,11)           /*!< PE11 read / write */
    #endif
    #if defined(PE_CR12_default)
        #define PE12                    PX(GPIOE_Base,12)           /*!< PE12 read / write */
    #endif
    #if defined(PE_CR13_default)
        #define PE13                    PX(GPIOE_Base,13)           /*!< PE13 read / write */
    #endif
    #if defined(PE_CR14_default)
        #define PE14                    PX(GPIOE_Base,14)           /*!< PE14 read / write */
    #endif
    #if defined(PE_CR15_default)
        #define PE15                    PX(GPIOE_Base,15)           /*!< PE15 read / write */
    #endif
#endif

/* @} */ 
 
 
 #ifdef __cplusplus
extern "C"{
#endif // __cplusplus

/*! @enum   PINX_Mode_TypeDef
    @brief  Pin IO mode control options .
*/ 
typedef enum
{
	PINX_Mode_Analog_IO     = 0x00000000,               /*!< Analog IO */
	PINX_Mode_OpenDrain_O   = 0x00000001,               /*!< Open drain output */
	PINX_Mode_PushPull_O    = 0x00000002,               /*!< Push pull output */
	PINX_Mode_Digital_I     = 0x00000003,               /*!< Digital input */
	PINX_Mode_Quasi_IO      = 0x00000004                /*!< Quasi-bidirection output*/
}PINX_Mode_TypeDef;


/*! @enum   PINX_Speed_Typedef
    @brief  Pin output high speed control options .
*/
typedef enum
{
	PINX_Speed_Low     = 0,                             /*!< Output high speed mode disable*/
	PINX_Speed_High    = 0x00000008                     /*!< Output high speed mode enable*/
}PINX_Speed_Typedef;


/*! @enum   PINX_PUResistant_Typedef
    @brief  Pin pull up resister control options .
*/
typedef enum
{
	PINX_PUResistant_Disable = 0,                       /*!< Pull up resister disable*/
	PINX_PUResistant_Enable  = 0x00000020               /*!< Pull up resister enable*/
}PINX_PUResistant_Typedef;


/*! @enum   PINX_Inverse_Typedef
    @brief  Pin input inverse control options .
*/
typedef enum
{
	PINX_Inverse_Disable  = 0,                          /*!< input inverse disable*/
	PINX_Inverse_Enable   = 0x00000080                  /*!< input inverse enable*/
}PINX_Inverse_Typedef;


/*! @enum   PINX_OUTDrive_Typedef
    @brief  Pin output drive strength control options .
*/
typedef enum
{
	PINX_OUTDrive_Level0 = PX_CR_ODC_level0_w,                  /*!< Drive strength-Full*/
    PINX_OUTDrive_Level1 = PX_CR_ODC_level1_w,                  /*!< Drive strength-1/2*/
    PINX_OUTDrive_Level2 = PX_CR_ODC_level2_w,                  /*!< Drive strength 1/4*/
      
#if defined(MG32_4TH)
    PINX_OUTDrive_Level3 = PX_CR_ODC_level3_w,                  /*!< Drive strength-1/8*/ 
    PINX_OUTDrive_Level4 = PX_CR_ODC_level4_w                   /*!< Drive strength-Full*2*/
#else
    PINX_OUTDrive_Level3 = PX_CR_ODC_level3_w                   /*!< Drive strength-1/8*/     
#endif   
}PINX_OUTDrive_Typedef;


/*! @enum   PINX_FilterDiver_Typedef
    @brief  Pin input deglitch filter clock divider control options .
*/
typedef enum
{
	PINX_FilterDivider_Bypass = 0x00000000,             /*!< input bypass filter*/
	PINX_FilterDivider_1      = 0x00000400,             /*!< input filter clock divided by 1*/
	PINX_FilterDivider_4      = 0x00000800,             /*!< input filter clock divided by 4*/
	PINX_FilterDivider_16     = 0x00000C00 	            /*!< input filter clock divided by 16*/
}PINX_FilterDiver_Typedef;


/*! @enum   PortFilterCLK_Typedef
    @brief  Port input deglitch filter clock source control options .
*/
typedef enum
{
    GPIO_FT_CLK_AHB         =   0,                   /*!< Filter clock source from AHB*/         
    GPIO_FT_CLK_AHB_DIV8    =   1,                   /*!< Filter clock source from AHB/8*/
    GPIO_FT_CLK_ILRCO       =   2,                   /*!< Filter clock source from ILRCO*/
    GPIO_FT_TM00_TRGO       =   3,                   /*!< Filter clock source from TM00_TRGO*/
    GPIO_FT_CK_UT           =   4                    /*!< Filter clock source from CK_UT*/
}PortFilterCLK_Typedef; 


/** 
 * @struct	PIN_InitTypeDef
 * @brief	Pin relationship control member.
 */
typedef struct __attribute__((packed))	
{
	uint32_t                  	PINX_Pin;                       /*!<Configuration Pin. */ 
	PINX_Mode_TypeDef			PINX_Mode;                      /*!<Pin mode select. */ 
    PINX_Speed_Typedef 		  	PINX_Speed;                     /*!<Pin output high speed mode control. */ 
	PINX_PUResistant_Typedef    PINX_PUResistant;               /*!<Pin pull up resistant control. */ 
	PINX_Inverse_Typedef        PINX_Inverse;                   /*!<Pin input inverse control. */ 
    PINX_OUTDrive_Typedef       PINX_OUTDrive;                  /*!<Pin output drive strength control. */ 
	PINX_FilterDiver_Typedef    PINX_FilterDivider;             /*!<Pin input filter divider control. */ 
	uint32_t  				  	PINX_Alternate_Function;        /*!<Pin alternate function select. */ 
}PIN_InitTypeDef;
 
 
 

void GPIO_PinMode_Config(Pin_Struct* PINX , PIN_InitTypeDef* PINX_InitStruct);
void GPIO_PortMode_Config(IOM_Struct* IOMX, PIN_InitTypeDef* PINX_InitStruct);
void GPIO_PinMode_Select(Pin_Struct* PINX , PINX_Mode_TypeDef Pin_Mode);
void GPIO_PinHighSpeedMode_Cmd(Pin_Struct* PINX , FunctionalState Pin_HSMode);
void GPIO_PinPUResister_Cmd(Pin_Struct* PINX , FunctionalState Pin_PUR);
void GPIO_PinInverse_Cmd(Pin_Struct* PINX, FunctionalState Pin_INV);
void GPIO_PinOutputDrive_Select(Pin_Struct* PINX , PINX_OUTDrive_Typedef Pin_ODC);
void GPIO_PinInFilterDivider_Select(Pin_Struct* PINX , PINX_FilterDiver_Typedef Pin_FDIV);
void GPIO_PinFunction_Select(Pin_Struct* PINX , uint8_t Pin_Func);
void GPIO_PortFilterClockSource_Select(IOM_Struct* IOMX , PortFilterCLK_Typedef FCKS);
void GPIO_WritePort(GPIO_Struct* GPIOX, uint16_t Port_Status);
uint16_t GPIO_ReadPort(GPIO_Struct* GPIOX);
void GPIO_SetPortBit(GPIO_Struct* GPIOX , uint16_t Set_Pin);
void GPIO_ClearPortBit(GPIO_Struct* GPIOX , uint16_t Clear_Pin);
void GPIO_SetClearPortBit(GPIO_Struct* GPIOX, uint16_t Set_Pin , uint16_t Clr_Pin);


#ifdef __cplusplus
}
#endif // __cplusplus


#endif





 
