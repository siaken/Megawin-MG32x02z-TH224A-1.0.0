

 /**
 ******************************************************************************
 *
 * @file        MG32x02z_GPIO_MID.h
 * @brief       The code GPIO middleware H file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.01
 * @date        2021/05/04
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 * 
 ******************************************************************************* 
 * @par Disclaimer
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
 
#ifndef __MG32x02z_GPIO_MID_H

#define __MG32x02z_GPIO_MID_H


#include "MG32x02z_Common_MID.h"
#include "MG32x02z_GPIO.h" 


/*! @name Read / Write / Toggle  Pin register
*/
///@{
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
///@}

/*! @name GPIO_pins_define  GPIO pins define
*/
///@{
#define GPIO_Pin_0                ((uint16_t)0x0001)  /*!< Pin 0 selected    */
#define GPIO_Pin_1                ((uint16_t)0x0002)  /*!< Pin 1 selected    */
#define GPIO_Pin_2                ((uint16_t)0x0004)  /*!< Pin 2 selected    */
#define GPIO_Pin_3                ((uint16_t)0x0008)  /*!< Pin 3 selected    */
#define GPIO_Pin_4                ((uint16_t)0x0010)  /*!< Pin 4 selected    */
#define GPIO_Pin_5                ((uint16_t)0x0020)  /*!< Pin 5 selected    */
#define GPIO_Pin_6                ((uint16_t)0x0040)  /*!< Pin 6 selected    */
#define GPIO_Pin_7                ((uint16_t)0x0080)  /*!< Pin 7 selected    */
#define GPIO_Pin_8                ((uint16_t)0x0100)  /*!< Pin 8 selected    */
#define GPIO_Pin_9                ((uint16_t)0x0200)  /*!< Pin 9 selected    */
#define GPIO_Pin_10               ((uint16_t)0x0400)  /*!< Pin 10 selected   */
#define GPIO_Pin_11               ((uint16_t)0x0800)  /*!< Pin 11 selected   */
#define GPIO_Pin_12               ((uint16_t)0x1000)  /*!< Pin 12 selected   */
#define GPIO_Pin_13               ((uint16_t)0x2000)  /*!< Pin 13 selected   */
#define GPIO_Pin_14               ((uint16_t)0x4000)  /*!< Pin 14 selected   */
#define GPIO_Pin_15               ((uint16_t)0x8000)  /*!< Pin 15 selected   */
#define GPIO_Pin_All              ((uint16_t)0xFFFF)  /*!< All pins selected */
///@}


/*! @name GPIO_mode_define  GPIO mode define
*/
///@{
#define GPIO_MODE_DIGITAL_I       0x00000003               /*!< Digital input */
#define GPIO_MODE_PUSHPULL_O      0x00000002               /*!< Push pull output */
#define GPIO_MODE_OPENDRAIN_O     0x00000001               /*!< Open drain output */
#define GPIO_MODE_QUASI_IO        0x00000004               /*!< Quasi-bidirection output*/
#define GPIO_MODE_ANALOG_IO       0x00000000               /*!< Analog IO */

///@}

/*! @name GPIO_pull_define  GPIO pull define
*/
///@{
#define GPIO_NOPULLUP             0                        /*!< Pull up resister disable*/
#define GPIO_PULLUP               0x00000020               /*!< Pull up resister enable*/      

///@}


/*! @name GPIO_speed_define  GPIO speed define
*/
///@{
#define GPIO_SPEED_LOW             0                        /*!< Output high speed mode disable*/
#define GPIO_SPEED_HIGH            0x00000008               /*!< Output high speed mode enable*/
///@}


/*! @name GPIO_inverse_define  GPIO input inverse define
*/
///@{
#define GPIO_INVERSE_DISABLE       0                        /*!< input inverse disable*/
#define GPIO_INVERSE_ENABLE        0x00000080               /*!< input inverse enable*/
///@}

/*! @name GPIO_OUTDrive_define  Pin output drive strength control options
*/
///@{
#define GPIO_OUTDRIVE_LEVEL0       0x00000000               /*!< Drive strength-Full*/
#define GPIO_OUTDRIVE_LEVEL1       0x00000100               /*!< Drive strength-1/2*/
#define GPIO_OUTDRIVE_LEVEL2       0x00000200               /*!< Drive strength 1/4*/
#define GPIO_OUTDRIVE_LEVEL3       0x00000300               /*!< Drive strength-1/8*/ 

///@}


/*! @name GPIO_FilterDivider_define  Pin output drive strength control options
*/
///@{
#define GPIO_FILTERDIVIDER_BYPASS   0x00000000              /*!< input bypass filter*/
#define GPIO_FILTERDIVIDER_1        0x00000400              /*!< input filter clock divided by 1*/
#define GPIO_FILTERDIVIDER_4        0x00000800              /*!< input filter clock divided by 4*/
#define GPIO_FILTERDIVIDER_16       0x00000C00              /*!< input filter clock divided by 16*/  

///@}


/*! @name GPIO_FilterSource_define  Port input deglitch filter clock source control options.
*/
///@{
#define GPIO_FLTSOURCE_AHB          0                        /*!< Filter clock source from AHB.*/ 
#define GPIO_FLTSOURCE_AHB_DIV8     1                        /*!< Filter clock source from AHB/8.*/ 
#define GPIO_FLTSOURCE_ILRCO        2                        /*!< Filter clock source from ILRCO.*/ 
#define GPIO_FLTSOURCE_TM00_TRGO    3                        /*!< Filter clock source from TM00_TRGO.*/ 
#define GPIO_FLTSOURCE_CK_UT        4                        /*!< Filter clock source from CK_UT.*/ 

///@}



/** 
 * @struct	PIN_InitTypeDef
 * @brief	Pin relationship control member.
 */
typedef struct	
{
    uint32_t                    Pin;                        /*!< Specifies the GPIO pins to be configured. 
                                                                 This parameter can be any value of GPIO_pins_define*/ 
    uint32_t                    Mode;                       /*!< Specifies the operating mode for the selected pins
                                                                 This parameter can be a value of GPIO_mode_define. */ 
    uint32_t                    Pull;                       /*!< Specifies the Pull-up activation for the selected pins 
                                                                 This parameter can be a value of GPIO_pull_define. */ 
    uint32_t                    Speed;                      /*!< Specifies the speed for the selected pins. 
                                                                 This parameter can be a value of GPIO_speed_define*/ 
    uint32_t                    Inverse;                    /*!< Specifies the input inverse for the selected pins
                                                                 This parameter can be a value of GPIO_inverse_define. */ 
    uint32_t                    OUTDrive;                   /*!< Specifies the output drive strength for the selected pins
                                                                 This parameter can be a value of GPIO_OUTDrive_define. */   
    uint32_t                    FilterDivider;              /*!< Specifies the input filter divider control for the selected pins
                                                                 This parameter can be a value of GPIO_FilterDivider_define. */ 
    uint32_t                    Alternate;                  /*!< Pin alternate function select. 
                                                                 This parameter can be a value of 0 ~ 15 (0 = GPIO , 
                                                                 the other value refer to relationship data */       
}GPIO_InitTypeDef;



/*! @name GPIO macro
*/
///@{

/**
 *******************************************************************************
 * @brief      Read port status .
 * @param[in]  "__HANDLE__"  : (GPIOA ~ GPIOE).
 * @return     No
 * @par        Example
 * @code
         Tmp = __DRV_GPIO_READ( GPIOA);     // Read GPIOA status to Tmp.
 * @endcode
 *******************************************************************************
 */

#define __DRV_GPIO_READ( __HANDLE__)   ((__HANDLE__)->IN.W)

#if defined(GPIOA_Base)

/**
 *******************************************************************************
 * @brief      Read PortA status .
 * @return     No
 * @par        Example
 * @code
         Tmp = __DRV_GPIOA_READ();     // Read GPIOA status to Tmp.
 * @endcode
 *******************************************************************************
 */
#define __DRV_GPIOA_READ()             (GPIOA->IN.W)

#endif
#if defined(GPIOB_Base)

/**
 *******************************************************************************
 * @brief      Read PortB status .
 * @return     No
 * @par        Example
 * @code
         Tmp = __DRV_GPIOB_READ();     // Read GPIOB status to Tmp.
 * @endcode
 *******************************************************************************
 */

#define __DRV_GPIOB_READ()             (GPIOB->IN.W)

#endif
#if defined(GPIOC_Base)

/**
 *******************************************************************************
 * @brief      Read PortC status .
 * @return     No
 * @par        Example
 * @code
         Tmp = __DRV_GPIOC_READ();     // Read GPIOC status to Tmp.
 * @endcode
 *******************************************************************************
 */

#define __DRV_GPIOC_READ()            (GPIOC->IN.W)

#endif
#if defined(GPIOD_Base)

/**
 *******************************************************************************
 * @brief      Read PortD status .
 * @return     No
 * @par        Example
 * @code
         Tmp = __DRV_GPIOD_READ();     // Read GPIOD status to Tmp.
 * @endcode
 *******************************************************************************
 */
  
#define __DRV_GPIOD_READ()            (GPIOD->IN.W)

#endif
#if defined(GPIOE_Base)

/**
 *******************************************************************************
 * @brief      Read PortE status .
 * @return     No
 * @par        Example
 * @code
         Tmp = __DRV_GPIOE_READ();     // Read GPIOE status to Tmp.
 * @endcode
 *******************************************************************************
 */
  
#define __DRV_GPIOE_READ()            (GPIOE->IN.W)

#endif


/**
 *******************************************************************************
 * @brief      Write port status.
 * @param[in]  "__HANDLE__"     : (GPIOA ~ GPIOE).
 * @param[in]  "__PORTSTATUS__" : Designate port status.
 * @return     No
 * @par        Example
 * @code
         __DRV_GPIO_WRITE(GPIOA , 0x0408);     // Write PortA status = 0x0408; 
 * @endcode
 *******************************************************************************
 */
#define __DRV_GPIO_WRITE(__HANDLE__ , __PORTSTATUS__)   ((__HANDLE__)->OUT.W = (__PORTSTATUS__)) 


#if defined(GPIOA_Base)
/**
 *******************************************************************************
 * @brief      Write PortA status.
 * @param[in]  "__PORTSTATUS__" : Designate port status.
 * @return     No
 * @par        Example
 * @code
         __DRV_GPIOA_WRITE(GPIOA , 0x0408);     // Write PortA status = 0x0408; 
 * @endcode
 *******************************************************************************
 */
  
#define __DRV_GPIOA_WRITE( __PORTSTATUS__)        ( GPIOA->OUT.W =  (__PORTSTATUS__))

#endif

#if defined(GPIOB_Base)
/**
 *******************************************************************************
 * @brief      Write PortB status.
 * @param[in]  "__PORTSTATUS__" : Designate port status.
 * @return     No
 * @par        Example
 * @code
         __DRV_GPIOB_WRITE(0x0408);     // Write PortB status = 0x0408; 
 * @endcode
 *******************************************************************************
 */
  
#define __DRV_GPIOB_WRITE( __PORTSTATUS__)        ( GPIOB->OUT.W =  (__PORTSTATUS__))

#endif

#if defined(GPIOC_Base)
/**
 *******************************************************************************
 * @brief      Write PortC status.
 * @param[in]  "__PORTSTATUS__" : Designate port status.
 * @return     No
 * @par        Example
 * @code
         __DRV_GPIOC_WRITE(0x0408);     // Write PortC status = 0x0408; 
 * @endcode
 *******************************************************************************
 */
  
#define __DRV_GPIOC_WRITE( __PORTSTATUS__)        ( GPIOC->OUT.W =  (__PORTSTATUS__))

#endif

#if defined(GPIOD_Base)
/**
 *******************************************************************************
 * @brief      Write PortD status.
 * @param[in]  "__PORTSTATUS__" : Designate port status.
 * @return     No
 * @par        Example
 * @code
         __DRV_GPIOD_WRITE(0x0408);     // Write PortD status = 0x0408; 
 * @endcode
 *******************************************************************************
 */
  
#define __DRV_GPIOD_WRITE( __PORTSTATUS__)        ( GPIOD->OUT.W =  (__PORTSTATUS__))

#endif

#if defined(GPIOE_Base)
/**
 *******************************************************************************
 * @brief      Write PortE status.
 * @param[in]  "__PORTSTATUS__" : Designate port status.
 * @return     No
 * @par        Example
 * @code
         __DRV_GPIOE_WRITE(0x0408);     // Write PortE status = 0x0408; 
 * @endcode
 *******************************************************************************
 */
  
#define __DRV_GPIOE_WRITE( __PORTSTATUS__)        ( GPIOE->OUT.W =  (__PORTSTATUS__))

#endif

/**
 *******************************************************************************
 * @brief      Set designate bits of Port ( the other pins no change status).
 * @param[in]  "__HANDLE__" : (GPIOA ~ GPIOE).
 * @param[in]  "__SETPIN__" : designate set pin in GPIOX
 *     \n                     This parameter can be any value of GPIO_pins_define. 
 * @return     No
 * @par        Example
 * @code
       __DRV_GPIO_SET_BIT( GPIOB , (GPIO_Pin_0 | GPIO_Pin_15));     // set PB0  and PB15
 * @endcode
 *******************************************************************************
 */
#define __DRV_GPIO_SET_BIT( __HANDLE__, __SETPIN__ ) ((__HANDLE__)->SC.H[0] = (__SETPIN__))


#if defined(GPIOA_Base)

/**
 *******************************************************************************
 * @brief      Set designate bits of PortA ( the other pins no change status).
 * @param[in]  "__SETPIN__" :designate set pin in GPIOA
 *     \n                    This parameter can be any value of GPIO_pins_define. 
 * @return     No
 * @par        Example
 * @code
       __DRV_GPIOA_SET_BIT( (GPIO_Pin_0 | GPIO_Pin_15));     // set PA0  and PA15
 * @endcode
 *******************************************************************************
 */
#define __DRV_GPIOA_SET_BIT(__SETPIN__)   (GPIOA->SC.H[0] = (__SETPIN__))

#endif

#if defined(GPIOB_Base)

/**
 *******************************************************************************
 * @brief      Set designate bits of PortB ( the other pins no change status).
 * @param[in]  "__SETPIN__" :designate set pin in GPIOB
 *     \n                    This parameter can be any value of GPIO_pins_define. 
 * @return     No
 * @par        Example
 * @code
       __DRV_GPIOB_SET_BIT( (GPIO_Pin_0 | GPIO_Pin_15));     // set PB0  and PB15
 * @endcode
 *******************************************************************************
 */
#define __DRV_GPIOB_SET_BIT(__SETPIN__)   (GPIOB->SC.H[0] = (__SETPIN__))

#endif


#if defined(GPIOC_Base)

/**
 *******************************************************************************
 * @brief      Set designate bits of PortC ( the other pins no change status).
 * @param[in]  "__SETPIN__" :designate set pin in GPIOC
 *     \n                    This parameter can be any value of GPIO_pins_define. 
 * @return     No
 * @par        Example
 * @code
       __DRV_GPIOC_SET_BIT( (GPIO_Pin_0 | GPIO_Pin_15));     // set PC0  and PC15
 * @endcode
 *******************************************************************************
 */
#define __DRV_GPIOC_SET_BIT(__SETPIN__)   (GPIOC->SC.H[0] = (__SETPIN__))

#endif

#if defined(GPIOD_Base)

/**
 *******************************************************************************
 * @brief      Set designate bits of PortD ( the other pins no change status).
 * @param[in]  "__SETPIN__" : designate set pin in GPIOD
 *     \n                     This parameter can be any value of GPIO_pins_define. 
 * @return     No
 * @par        Example
 * @code
       __DRV_GPIOD_SET_BIT( (GPIO_Pin_0 | GPIO_Pin_15));     // set PD0  and PD15
 * @endcode
 *******************************************************************************
 */
#define __DRV_GPIOD_SET_BIT(__SETPIN__)   (GPIOD->SC.H[0] = (__SETPIN__))

#endif

#if defined(GPIOE_Base)

/**
 *******************************************************************************
 * @brief      Set designate bits of PortE ( the other pins no change status).
 * @param[in]  "__SETPIN__" : designate set pin in GPIOE
 *     \n                     This parameter can be any value of GPIO_pins_define. 
 * @return     No
 * @par    Example
 * @code
       __DRV_GPIOE_SET_BIT( (GPIO_Pin_0 | GPIO_Pin_15));     // set PE0  and PE15
 * @endcode
 *******************************************************************************
 */
#define __DRV_GPIOE_SET_BIT(__SETPIN__)   (GPIOE->SC.H[0] = (__SETPIN__))

#endif

/**
 *******************************************************************************
 * @brief      Clear designate bit of port ( the other pins no change status).
 * @param[in]  "__HANDLE__"   : (GPIOA ~ GPIOE).
 * @param[in]  "__CLEARPIN__" : designate clear pin in GPIOX
 *     \n                       This parameter can be any value of GPIO_pins_define. 
 * @return     No
 * @par        Example
 * @code
       __DRV_GPIO_CLEAR_BIT( GPIOA , (GPIO_Pin_11 | GPIO_Pin_10));   // Clear PA11 and PA10
 * @endcode
 *******************************************************************************
 */
#define __DRV_GPIO_CLEAR_BIT( __HANDLE__, __CLEARPIN__ ) ((__HANDLE__)->SC.H[1] = (__CLEARPIN__))


#if defined(GPIOA_Base)

/**
 *******************************************************************************
 * @brief      Clear designate bit of PortA ( the other pins no change status).
 * @param[in]  "__CLEARPIN__" : designate clear pin in GPIOA
 *     \n                       This parameter can be any value of GPIO_pins_define. 
 * @return     No
 * @par        Example
 * @code
       __DRV_GPIOA_CLEAR_BIT( (GPIO_Pin_11 | GPIO_Pin_10));   // Clear PA11 and PA10
 * @endcode
 *******************************************************************************
 */
#define __DRV_GPIOA_CLEAR_BIT( __CLEARPIN__ ) (GPIOA->SC.H[1] = (__CLEARPIN__))

#endif

#if defined(GPIOB_Base)

/**
 *******************************************************************************
 * @brief      Clear designate bit of PortB ( the other pins no change status).
 * @param[in]  "__CLEARPIN__" : designate clear pin in GPIOB
 *     \n                       This parameter can be any value of @ref GPIO_pins_define. 
 * @return     No
 * @par        Example
 * @code
       __DRV_GPIOB_CLEAR_BIT( (GPIO_Pin_11 | GPIO_Pin_10));   // Clear PB11 and PB10
 * @endcode
 *******************************************************************************
 */
#define __DRV_GPIOB_CLEAR_BIT( __CLEARPIN__ ) (GPIOB->SC.H[1] = (__CLEARPIN__))

#endif

#if defined(GPIOC_Base)

/**
 *******************************************************************************
 * @brief      Clear designate bit of PortC ( the other pins no change status).
 * @param[in]  "__CLEARPIN__" : designate clear pin in GPIOC
 *     \n                       This parameter can be any value of GPIO_pins_define. 
 * @return     No
 * @par        Example
 * @code
       __DRV_GPIOC_CLEAR_BIT( (GPIO_Pin_11 | GPIO_Pin_10));   // Clear PC11 and PC10
 * @endcode
 *******************************************************************************
 */
#define __DRV_GPIOC_CLEAR_BIT( __CLEARPIN__ ) (GPIOC->SC.H[1] = (__CLEARPIN__))

#endif

#if defined(GPIOD_Base)

/**
 *******************************************************************************
 * @brief      Clear designate bit of PortD ( the other pins no change status).
 * @param[in]  "__CLEARPIN__" : designate clear pin in GPIOD
 *     \n                   This parameter can be any value of GPIO_pins_define. 
 * @return     No
 * @par        Example
 * @code
       __DRV_GPIOD_CLEAR_BIT( (GPIO_Pin_11 | GPIO_Pin_10));   // Clear PD11 and PD10
 * @endcode
 *******************************************************************************
 */
#define __DRV_GPIOD_CLEAR_BIT( __CLEARPIN__ ) (GPIOD->SC.H[1] = (__CLEARPIN__))

#endif

#if defined(GPIOE_Base)

/**
 *******************************************************************************
 * @brief      Clear designate bit of PortE ( the other pins no change status).
 * @param[in]  "__CLEARPIN__" : designate clear pin in GPIOE
 *     \n                       This parameter can be any value of GPIO_pins_define. 
 * @return     No
 * @par        Example
 * @code
       __DRV_GPIOE_CLEAR_BIT( (GPIO_Pin_11 | GPIO_Pin_10));   // Clear PE11 and PE10
 * @endcode
 *******************************************************************************
 */
#define __DRV_GPIOE_CLEAR_BIT( __CLEARPIN__ ) (GPIOE->SC.H[1] = (__CLEARPIN__))

#endif



/**
 *******************************************************************************
 * @brief      Clear and set designate bit of port at the same time ( the other pins no change status).
 * @param[in]  "__HANDLE__"  : (GPIOA ~ GPIOE).
 * @param[in]  "__SETPIN__"  : designate set pin in GPIOX
 *     \n                      This parameter can be any value of GPIO_pins_define.
 * @param[in]  "__CLEARPIN__": designate clear pin in GPIOX
 *     \n                      This parameter can be any value of GPIO_pins_define.
 * @return     No
 * @par        Example
 * @code
       __DRV_GPIO_SETCLEAR_BIT( GPIOA ,(GPIO_Pin_0 | GPIO_Pin_15), (GPIO_Pin_5 | GPIO_Pin_10));
 * @endcode
 *******************************************************************************
 */
#define __DRV_GPIO_SETCLEAR_BIT( __HANDLE__ , __SETPIN__ , __CLEARPIN__) ( ((__HANDLE__)->SC.W) = ((((__CLEARPIN__)<<16) & 0xFFFF0000) | __SETPIN__))


#if defined(GPIOA_Base)

/**
 *******************************************************************************
 * @brief      Clear and set designate bit of PortA at the same time ( the other pins no change status).
 * @param[in]  "__SETPIN__"  : designate set pin in GPIOA
 *     \n                      This parameter can be any value of GPIO_pins_define.
 * @param[in]  "__CLEARPIN__": designate clear pin in GPIOA
 *     \n                      This parameter can be any value of GPIO_pins_define.
 * @return     No
 * @par        Example
 * @code
       __DRV_GPIOA_SETCLEAR_BIT( (GPIO_Pin_0 | GPIO_Pin_15), (GPIO_Pin_5 | GPIO_Pin_10));     // Set PA10 & PA15   , Clear PA5 & PA10
 * @endcode
 *******************************************************************************
 */
#define __DRV_GPIOA_SETCLEAR_BIT( __SETPIN__ , __CLEARPIN__) ( (GPIOA->SC.W) = ((((__CLEARPIN__)<<16) & 0xFFFF0000) | __SETPIN__))

#endif

#if defined(GPIOB_Base)

/**
 *******************************************************************************
 * @brief      Clear and set designate bit of PortB at the same time ( the other pins no change status).
 * @param[in]  "__SETPIN__"  : designate set pin in GPIOB
 *     \n                      This parameter can be any value of GPIO_pins_define.
 * @param[in]  "__CLEARPIN__": designate clear pin in GPIOB
 *     \n                      This parameter can be any value of GPIO_pins_define.
 * @return     No
 * @par        Example
 * @code
       __DRV_GPIOB_SETCLEAR_BIT( (GPIO_Pin_0 | GPIO_Pin_15), (GPIO_Pin_5 | GPIO_Pin_10));     // Set PB10 & PB15   , Clear PB5 & PB10
 * @endcode
 *******************************************************************************
 */
#define __DRV_GPIOB_SETCLEAR_BIT( __SETPIN__ , __CLEARPIN__) ( (GPIOB->SC.W) = ((((__CLEARPIN__)<<16) & 0xFFFF0000) | __SETPIN__))

#endif

#if defined(GPIOC_Base)

/**
 *******************************************************************************
 * @brief      Clear and set designate bit of PortC at the same time ( the other pins no change status).
 * @param[in]  "__SETPIN__"  : designate set pin in GPIOC
 *     \n                      This parameter can be any value of GPIO_pins_define.
 * @param[in]  "__CLEARPIN__": designate clear pin in GPIOC
 *     \n                      This parameter can be any value of GPIO_pins_define.
 * @return     No
 * @par        Example
 * @code
       __DRV_GPIOC_SETCLEAR_BIT( (GPIO_Pin_0 | GPIO_Pin_15), (GPIO_Pin_5 | GPIO_Pin_10));     // Set PC10 & PC15   , Clear PC5 & PC10
 * @endcode
 *******************************************************************************
 */
#define __DRV_GPIOC_SETCLEAR_BIT( __SETPIN__ , __CLEARPIN__) ( (GPIOC->SC.W) = ((((__CLEARPIN__)<<16) & 0xFFFF0000) | __SETPIN__))

#endif


#if defined(GPIOD_Base)

/**
 *******************************************************************************
 * @brief      Clear and set designate bit of PortD at the same time ( the other pins no change status).
 * @param[in]  "__SETPIN__"  : designate set pin in GPIOD
 *     \n                      This parameter can be any value of GPIO_pins_define.
 * @param[in]  "__CLEARPIN__": designate clear pin in GPIOD
 *     \n                      This parameter can be any value of GPIO_pins_define.
 * @return     No
 * @par        Example
 * @code
       __DRV_GPIOD_SETCLEAR_BIT( (GPIO_Pin_0 | GPIO_Pin_15), (GPIO_Pin_5 | GPIO_Pin_10));     // Set PD10 & PD15   , Clear PD5 & PD10
 * @endcode
 *******************************************************************************
 */
#define __DRV_GPIOD_SETCLEAR_BIT( __SETPIN__ , __CLEARPIN__) ( (GPIOD->SC.W) = ((((__CLEARPIN__)<<16) & 0xFFFF0000) | __SETPIN__))

#endif


/**
 *******************************************************************************
 * @brief      GPIO Filter Clock Source Select 
 * @param[in]  "__HANDLE__" : (IOMA ~ IOME).
 * @param[in]  "__FCKS__"   : Input deglitch filter clock source select .
 *               @arg GPIO_FLTSOURCE_AHB       : Filter clock source from AHB.
 *               @arg GPIO_FLTSOURCE_AHB_DIV8  : Filter clock source from AHB/8.
 *               @arg GPIO_FLTSOURCE_ILRCO     : Filter clock source from ILRCO.
 *               @arg GPIO_FLTSOURCE_TM00_TRGO : Filter clock source from TM00_TRGO.
 *               @arg GPIO_FLTSOURCE_CK_UT     : Filter clock source from CK_UT.
 * @return     No
 * @note       A port share the filter clock source. 
 * @par        Example
 * @code 
       __DRV_GPIO_FILTERCLOCK_SELECT( IOMB , GPIO_FLTSOURCE_AHB);    // GPIOB input filter source from CK_AHB
 * @endcode
 *******************************************************************************
 */
#define __DRV_GPIO_FILTERCLOCK_SELECT( __HANDLE__ , __FCKS__)   ((__HANDLE__)->FLT.B[0] = (__FCKS__)) 

/**
 *******************************************************************************
 * @brief      GPIO Filter Divider Select 
 * @param[in]  "__HANDLE__" : (PINA ~ PINE).
 * @param[in]  "__FDIV__"   : Filter divider select .
 *               @arg GPIO_FILTERDIVIDER_BYPASS : Filter clock source bypass
 *               @arg GPIO_FILTERDIVIDER_1      : Filter clock source DIV1
 *               @arg GPIO_FILTERDIVIDER_4      : Filter clock source DIV4
 *               @arg GPIO_FILTERDIVIDER_16     : Filter clock source DIV16
 * @return     No
 * @note       Pin select filter divider
 * @par        Example
 * @code 
       __DRV_GPIO_FILTERCLOCK_SELECT( IOMB(0) , GPIO_FILTERDIVIDER_4);    // GPIOB input filter divider select
 * @endcode
 *******************************************************************************
 */
#define __DRV_GPIO_FILTERDIVIDER_SELECT(__HANDLE__,__FDIV__)    (__HANDLE__)->CR.W = (((__HANDLE__)->CR.W&~PX_CR_FDIV_mask_w) | (__FDIV__))

///@}





#ifdef __cplusplus
extern "C" {
#endif

/*! @name GPIO Function.
*/
///@{
void MID_GPIO_Pin_Init( Pin_Struct* PINX , GPIO_InitTypeDef* PIN_Init);
void MID_GPIO_Init( IOM_Struct* IOMx , GPIO_InitTypeDef* GPIO_Init);
void MID_GPIO_DeInit( IOM_Struct* IOMx , uint32_t GPIO_Pin);

///@}

#ifdef __cplusplus
}
#endif

#endif

















