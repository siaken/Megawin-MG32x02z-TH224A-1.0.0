

 /**
 ******************************************************************************
 *
 * @file        MG32x02z_EXIC_MID.h
 * @brief       The code EXIC middleware H file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.03
 * @date        2022/06/15
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
  
#ifndef __MG32x02z_EXIC_MID_H
 
#define __MG32x02z_EXIC_MID_H
 
 
 
#include "MG32x02z_Common_MID.h"
#include "MG32x02z_EXIC.h"
#include "MG32x02z__ExtraStruct.h"
 
 
/*! @name EXIC_PORT  : Port of external input interrupt.  
*/
///@{
#define EXIC_PORTA          0      /*!< Use PortA.*/
#define EXIC_PORTB          1      /*!< Use PortB.*/
#define EXIC_PORTC          2      /*!< Use PortC.*/
#define EXIC_PORTD          3      /*!< Use PortD.*/
#if defined(EXIC_PD_Base)                   
#define EXIC_PORTE          4      /*!< Use PortE.*/
#endif
///@}

/*! @name EXIC_PORT  : Port of external input interrupt.  
*/
///@{
#define EXIC_PX_AF          EXIC_STA_PA_AF_mask_b0              /*!< External interrupt Port AND path interrupt flag. */                
#define EXIC_PX_OF          EXIC_STA_PA_OF_mask_b0              /*!< External interrupt Port OR path interrupt flag.*/       
#define EXIC_PX_ITF_MASK    EXIC_PX_AF | EXIC_PX_OF             /*!< Byte of EXIC PX interrupt flag mask */
#define EXIC_PX_ITF_SHIFT   4                                   /*!< Between the port flag and the other port flag shift bit in EXIC_STA.*/
#define EXIC_PX_IEA_MASK    0x1F                                /*!< The port all flag mask in EXIC_STA.*/
///@}


 

/*! @name EXIC_PX_PIN pin  : External trigger pin control definition
*/
///@{
#define EXIC_PX_PIN0        0x0001          /*!< External trigger Pin Control Definitions */
#define EXIC_PX_PIN1        0x0002          /*!< External trigger Pin Control Definitions */
#define EXIC_PX_PIN2        0x0004          /*!< External trigger Pin Control Definitions */
#define EXIC_PX_PIN3        0x0008          /*!< External trigger Pin Control Definitions */
#define EXIC_PX_PIN4        0x0010          /*!< External trigger Pin Control Definitions */
#define EXIC_PX_PIN5        0x0020          /*!< External trigger Pin Control Definitions */
#define EXIC_PX_PIN6        0x0040          /*!< External trigger Pin Control Definitions */
#define EXIC_PX_PIN7        0x0080          /*!< External trigger Pin Control Definitions */
#define EXIC_PX_PIN8        0x0100          /*!< External trigger Pin Control Definitions */
#define EXIC_PX_PIN9        0x0200          /*!< External trigger Pin Control Definitions */
#define EXIC_PX_PIN10       0x0400          /*!< External trigger Pin Control Definitions */
#define EXIC_PX_PIN11       0x0800          /*!< External trigger Pin Control Definitions */
#define EXIC_PX_PIN12       0x1000          /*!< External trigger Pin Control Definitions */
#define EXIC_PX_PIN13       0x2000          /*!< External trigger Pin Control Definitions */
#define EXIC_PX_PIN14       0x4000          /*!< External trigger Pin Control Definitions */
#define EXIC_PX_PIN15       0x8000          /*!< External trigger Pin Control Definitions */
#define EXIC_PX_AllPIN      0xFFFF          /*!< External trigger Pin Control Definitions */
///@}

/*! @name EXIC_PX_PINTRG  : Select pins to set trigger mode definition.
*/
///@{ 
#define EXIC_TRGS_PIN0      0x00000001      /*!< External trigger mode of pin Control Definitions */
#define EXIC_TRGS_PIN1      0x00000004      /*!< External trigger mode of pin Control Definitions */
#define EXIC_TRGS_PIN2      0x00000010      /*!< External trigger mode of pin Control Definitions */
#define EXIC_TRGS_PIN3      0x00000040      /*!< External trigger mode of pin Control Definitions */
#define EXIC_TRGS_PIN4      0x00000100      /*!< External trigger mode of pin Control Definitions */
#define EXIC_TRGS_PIN5      0x00000400      /*!< External trigger mode of pin Control Definitions */
#define EXIC_TRGS_PIN6      0x00001000      /*!< External trigger mode of pin Control Definitions */
#define EXIC_TRGS_PIN7      0x00004000      /*!< External trigger mode of pin Control Definitions */
#define EXIC_TRGS_PIN8      0x00010000      /*!< External trigger mode of pin Control Definitions */
#define EXIC_TRGS_PIN9      0x00040000      /*!< External trigger mode of pin Control Definitions */
#define EXIC_TRGS_PIN10     0x00100000      /*!< External trigger mode of pin Control Definitions */
#define EXIC_TRGS_PIN11     0x00400000      /*!< External trigger mode of pin Control Definitions */
#define EXIC_TRGS_PIN12     0x01000000      /*!< External trigger mode of pin Control Definitions */
#define EXIC_TRGS_PIN13     0x04000000      /*!< External trigger mode of pin Control Definitions */
#define EXIC_TRGS_PIN14     0x10000000      /*!< External trigger mode of pin Control Definitions */
#define EXIC_TRGS_PIN15     0x40000000      /*!< External trigger mode of pin Control Definitions */
#define EXIC_TRGS_ALL       0x55555555      /*!< External trigger mode of pin Control Definitions */

///@} 
 
 /*! @name EXIC_TRG_MODE  : External pin trigger event mode definition.
*/
///@{ 
#define EXIC_TRIGGER_MASK            0x03    /*!< External trigger mode mask.*/
#define EXIC_TRIGGER_NONE            0x00    /*!< No external trigger mode.*/
#define EXIC_TRIGGER_LEVEL           0x01    /*!< Level trigger mode.*/
#define EXIC_TRIGGER_EDGE            0x02    /*!< Edge trigger mode.*/ 
#define EXIC_TRIGGER_DUAL_EDGE       0x03    /*!< Dual edge trigger mode.*/ 
///@} 
 
 /*! @name EXIC_INTERRUPT : To control external pin input interrupt enable or disable.
*/
///@{  
#define EXIC_INTERRUPT_DISABLE      0x00 
#define EXIC_INTERRUPT_ENABLE       0x01  
///@} 
 
 
#if defined(EXIC_CR0_NMI_SEL_mask_w) && defined(EXIC_CR0_NMI_MUX_mask_w)
 /*! @name EXIC_NMI_SOURCE : Trigger NMI source definition.
*/
///@{  
#define MID_EXIC_NMI_WWDT       (0x00000000 | EXIC_CR0_NMI_SEL_mask_w)    /*!< Trigger NMI source from WWDT */
#define MID_EXIC_NMI_SYS        (0x00000400 | EXIC_CR0_NMI_SEL_mask_w)    /*!< Trigger NMI source from SYS */
#define MID_EXIC_NMI_EXIN0      (0x00000C00 | EXIC_CR0_NMI_SEL_mask_w)    /*!< Trigger NMI source from EXINT0 */
#define MID_EXIC_NMI_EXIN1      (0x00001000 | EXIC_CR0_NMI_SEL_mask_w)    /*!< Trigger NMI source from EXINT1 */
#define MID_EXIC_NMI_EXIN2      (0x00001400 | EXIC_CR0_NMI_SEL_mask_w)    /*!< Trigger NMI source from EXINT2 */
#define MID_EXIC_NMI_EXIN3      (0x00001800 | EXIC_CR0_NMI_SEL_mask_w)    /*!< Trigger NMI source from EXINT3 */
#define MID_EXIC_NMI_COMP       (0x00001C00 | EXIC_CR0_NMI_SEL_mask_w)    /*!< Trigger NMI source from COMP */
#define MID_EXIC_NMI_DMA        (0x00002000 | EXIC_CR0_NMI_SEL_mask_w)    /*!< Trigger NMI source from DMA */
#define MID_EXIC_NMI_ADC        (0x00002800 | EXIC_CR0_NMI_SEL_mask_w)    /*!< Trigger NMI source from ADC */
#define MID_EXIC_NMI_DAC        (0x00002C00 | EXIC_CR0_NMI_SEL_mask_w)    /*!< Trigger NMI source from DAC */
#define MID_EXIC_NMI_TM00       (0x00003000 | EXIC_CR0_NMI_SEL_mask_w)    /*!< Trigger NMI source from TM00 */
#define MID_EXIC_NMI_TM10       (0x00003400 | EXIC_CR0_NMI_SEL_mask_w)    /*!< Trigger NMI source from TM10 */
#define MID_EXIC_NMI_TM16       (0x00003800 | EXIC_CR0_NMI_SEL_mask_w)    /*!< Trigger NMI source from TM16 */
#define MID_EXIC_NMI_TM20       (0x00003C00 | EXIC_CR0_NMI_SEL_mask_w)    /*!< Trigger NMI source from TM20 */
#define MID_EXIC_NMI_TM26       (0x00004000 | EXIC_CR0_NMI_SEL_mask_w)    /*!< Trigger NMI source from TM26 */
#define MID_EXIC_NMI_TM36       (0x00004400 | EXIC_CR0_NMI_SEL_mask_w)    /*!< Trigger NMI source from TM36 */
#define MID_EXIC_NMI_URT0       (0x00005000 | EXIC_CR0_NMI_SEL_mask_w)    /*!< Trigger NMI source from URT0 */
#define MID_EXIC_NMI_URT123     (0x00005400 | EXIC_CR0_NMI_SEL_mask_w)    /*!< Trigger NMI source from URT123 */
#define MID_EXIC_NMI_SPI0       (0x00006000 | EXIC_CR0_NMI_SEL_mask_w)    /*!< Trigger NMI source from SPI0 */
#define MID_EXIC_NMI_I2C0       (0x00007000 | EXIC_CR0_NMI_SEL_mask_w)    /*!< Trigger NMI source from I2C0 */
#define MID_EXIC_NMI_I2Cx       (0x00007400 | EXIC_CR0_NMI_SEL_mask_w)    /*!< Trigger NMI source from I2Cx */
#define MID_EXIC_NMI_NMI        (0x00000000                          )
///@}  
#endif
 
 
/*! @struct  EXIC_HandleTypeDef
    @brief   EXIC Pin trigger handle Structure definition.
*/
typedef struct __attribute__((packed))
{
    EXIC_PX_Struct          *Instance;          /*!< EXIC pin input interrupt register basic address*/
    uint8_t                 EXIC_Port;          /*!< Define the struct use which external input port.
                                                     This parameter only reference use so not need to set (ref to EXIC_PORT*/
    uint16_t                AND_Mask;           /*!< External interrupt Port AND mask bit.*/
    FunctionalState         AND_UnMatch;        /*!< Decide to wether enable no match AND result to trigger interrupt or not. */
    uint16_t                OR_Mask;            /*!< External interrupt Port OR mask bit.*/
    uint8_t                 Interrupt;          /*!< Decide to wether enable external pin interrupt or not.
                                                     This parameter can be a value of EXIC_INTERRUPT*/
    MID_LockTypeDef         Lock;               /*!< Locking object.*/
}EXIC_HandleTypeDef; 
 
 
 /*! @name EXIC macro
*/
///@{

/**
 *******************************************************************************
 * @brief  Read interrupt source-0 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID0_SOURCE()           (EXIC->SRC0.B[0])      /*!< Get Interrupt 0  identity.*/    
/**
 *******************************************************************************
 * @brief  Read interrupt source-1 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID1_SOURCE()           (EXIC->SRC0.B[1])      /*!< Get Interrupt 1  identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-2 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID2_SOURCE()           (EXIC->SRC0.B[2])      /*!< Get Interrupt 2  identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-3 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID3_SOURCE()           (EXIC->SRC0.B[3])      /*!< Get Interrupt 3  identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-4 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID4_SOURCE()           (EXIC->SRC1.B[0])      /*!< Get Interrupt 4  identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-5 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID5_SOURCE()           (EXIC->SRC1.B[1])      /*!< Get Interrupt 5  identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-6 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID6_SOURCE()           (EXIC->SRC1.B[2])      /*!< Get Interrupt 6  identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-7 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID7_SOURCE()           (EXIC->SRC1.B[3])      /*!< Get Interrupt 7  identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-8 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID8_SOURCE()           (EXIC->SRC2.B[0])      /*!< Get Interrupt 8  identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-9 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID9_SOURCE()           (EXIC->SRC2.B[1])      /*!< Get Interrupt 9  identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-10 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID10_SOURCE()          (EXIC->SRC2.B[2])      /*!< Get Interrupt 10 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-11 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID11_SOURCE()          (EXIC->SRC2.B[3])      /*!< Get Interrupt 11 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-12 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID12_SOURCE()          (EXIC->SRC3.B[0])      /*!< Get Interrupt 12 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-13 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID13_SOURCE()          (EXIC->SRC3.B[1])      /*!< Get Interrupt 13 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-14 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID14_SOURCE()          (EXIC->SRC3.B[2])      /*!< Get Interrupt 14 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-15 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID15_SOURCE()          (EXIC->SRC3.B[3])      /*!< Get Interrupt 15 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-16 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID16_SOURCE()          (EXIC->SRC4.B[0])      /*!< Get Interrupt 16 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-17 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID17_SOURCE()          (EXIC->SRC4.B[1])      /*!< Get Interrupt 17 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-18 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID18_SOURCE()          (EXIC->SRC4.B[2])      /*!< Get Interrupt 18 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-19 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID19_SOURCE()          (EXIC->SRC4.B[3])      /*!< Get Interrupt 19 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-20 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID20_SOURCE()          (EXIC->SRC5.B[0])      /*!< Get Interrupt 20 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-21 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID21_SOURCE()          (EXIC->SRC5.B[1])      /*!< Get Interrupt 21 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-22 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID22_SOURCE()          (EXIC->SRC5.B[2])      /*!< Get Interrupt 22 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-23 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID23_SOURCE()          (EXIC->SRC5.B[3])      /*!< Get Interrupt 23 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-24 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID24_SOURCE()          (EXIC->SRC6.B[0])      /*!< Get Interrupt 24 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-25 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID25_SOURCE()          (EXIC->SRC6.B[1])      /*!< Get Interrupt 25 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-26 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID26_SOURCE()          (EXIC->SRC6.B[2])      /*!< Get Interrupt 26 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-27 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID27_SOURCE()          (EXIC->SRC6.B[3])      /*!< Get Interrupt 27 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-28 identity.
 * @note
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID28_SOURCE()          (EXIC->SRC7.B[0])      /*!< Get Interrupt 28 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-29 identity.
 * @note   
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID29_SOURCE()          (EXIC->SRC7.B[1])      /*!< Get Interrupt 29 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-30 identity.
 * @note   
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID30_SOURCE()          (EXIC->SRC7.B[2])      /*!< Get Interrupt 30 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-31 identity.
 * @note   
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID31_SOURCE()          (EXIC->SRC7.B[3])      /*!< Get Interrupt 31 identity.*/

/**
 *******************************************************************************
 * @brief  Software NMI trigger bit.
 * @note   
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_NMI_TRIGGER_SW             (EXIC->CR0.B[0] |= EXIC_CR0_NMI_SW_mask_b0)

/**
 *******************************************************************************
 * @brief  RXEV enable
 * @note   
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_RXEV_ENABLE()                                          SET_BIT(EXIC->CR0.B[1] ,  EXIC_CR0_EM_RXEV_mask_b1)

/**
 *******************************************************************************
 * @brief  RXEV enable
 * @note   
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_RXEV_DISABLE()                                         CLEAR_BIT( EXIC->CR0.B[1] , EXIC_CR0_EM_RXEV_mask_b1)

/**
 *******************************************************************************
 * @brief  NMI enable
 * @note   
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_NMI_ENABLE()                                           SET_BIT(EXIC->CR0.B[1] , EXIC_CR0_EM_NMI_mask_b1)

/**
 *******************************************************************************
 * @brief  NMI disable
 * @note   
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_NMI_DISABLE()                                          CLEAR_BIT( EXIC->CR0.B[1] , EXIC_CR0_EM_NMI_mask_b1);

#if defined(EXIC_CR0_NMI_SEL_mask_w) && defined(EXIC_CR0_NMI_MUX_mask_w)
/**
 *******************************************************************************
 * @brief     Write PortB status.
 * @param[in] "__SOURCE__" : Trigger NMI interrupt source.
 *     \n                    This parameter can be one of the following value:
 *              @arg MID_EXIC_NMI_WWDT      : Trigger NMI source from WWDT 
 *              @arg MID_EXIC_NMI_SYS       : Trigger NMI source from SYS 
 *              @arg MID_EXIC_NMI_EXIN0     : Trigger NMI source from EXINT0 
 *              @arg MID_EXIC_NMI_EXIN1     : Trigger NMI source from EXINT1 
 *              @arg MID_EXIC_NMI_EXIN2     : Trigger NMI source from EXINT2 
 *              @arg MID_EXIC_NMI_EXIN3     : Trigger NMI source from EXINT3 
 *              @arg MID_EXIC_NMI_COMP      : Trigger NMI source from COMP 
 *              @arg MID_EXIC_NMI_DMA       : Trigger NMI source from DMA 
 *              @arg MID_EXIC_NMI_ADC       : Trigger NMI source from ADC 
 *              @arg MID_EXIC_NMI_DAC       : Trigger NMI source from DAC 
 *              @arg MID_EXIC_NMI_TM00      : Trigger NMI source from TM00 
 *              @arg MID_EXIC_NMI_TM10      : Trigger NMI source from TM10 
 *              @arg MID_EXIC_NMI_TM16      : Trigger NMI source from TM16 
 *              @arg MID_EXIC_NMI_TM20      : Trigger NMI source from TM20 
 *              @arg MID_EXIC_NMI_TM26      : Trigger NMI source from TM26 
 *              @arg MID_EXIC_NMI_TM36      : Trigger NMI source from TM36 
 *              @arg MID_EXIC_NMI_URT0      : Trigger NMI source from URT0 
 *              @arg MID_EXIC_NMI_URT123    : Trigger NMI source from URT123 
 *              @arg MID_EXIC_NMI_SPI0      : Trigger NMI source from SPI0 
 *              @arg MID_EXIC_NMI_I2C0      : Trigger NMI source from I2C0 
 *              @arg MID_EXIC_NMI_I2Cx      : Trigger NMI source from I2Cx 
 *              @arg MID_EXIC_NMI_NMI       : Trigger NMI source from NMI pin.
 * @return No
 * @par    Example
 * @code
       __DRV_EXIC_NMI_SOURCE_SELECT(MID_EXIC_NMI_TM10);
 * @endcode
 *******************************************************************************
 */
#define __DRV_EXIC_NMI_SOURCE_SELECT(__SOURCE__)                          MODIFY_REG( EXIC->CR0.W , (EXIC_CR0_NMI_SEL_mask_w | EXIC_CR0_NMI_MUX_mask_w) , (__SOURCE__))
#endif 

/**
 *******************************************************************************
 * @brief      Get the specified EXIC event flag ( EXIC pin input interrupt pending flag)
 * @param[in]  "__HANDLE__": specifies the EXIC Handle.
 * @retval     None
 *******************************************************************************
 */
#define __DRV_EXIC_GET_PINTRIGGER_EVENTFLAG(__HANDLE__)                 ((__HANDLE__)->Instance->PF.W)


/**
 *******************************************************************************
 * @brief     Clear the specified EXIC event flag ( external pin input interrupt pending flag)
 * @param[in] "__HANDLE__": specifies the EXIC Handle.
 * @param     "__CLRFLAG__": specifies the external pin input interrupt pending flag to clear.
 *             This parameter can be one of the following values:
 *               @arg EXIC_PX_PIN0  : pin0  of the port.
 *               @arg EXIC_PX_PIN1  : pin1  of the port.
 *               @arg EXIC_PX_PIN2  : pin2  of the port.
 *               @arg EXIC_PX_PIN3  : pin3  of the port.
 *               @arg EXIC_PX_PIN4  : pin4  of the port.
 *               @arg EXIC_PX_PIN5  : pin5  of the port.
 *               @arg EXIC_PX_PIN6  : pin6  of the port.
 *               @arg EXIC_PX_PIN7  : pin7  of the port.
 *               @arg EXIC_PX_PIN8  : pin8  of the port.
 *               @arg EXIC_PX_PIN9  : pin9  of the port.
 *               @arg EXIC_PX_PIN10 : pin10 of the port.
 *               @arg EXIC_PX_PIN11 : pin11 of the port.
 *               @arg EXIC_PX_PIN12 : pin12 of the port.
 *               @arg EXIC_PX_PIN13 : pin13 of the port.
 *               @arg EXIC_PX_PIN14 : pin14 of the port.
 *               @arg EXIC_PX_PIN15 : pin15 of the port.
 *               @arg EXIC_PX_AllPIN: All pins of the port.
 * @retval    None
 *******************************************************************************
 */
#define __DRV_EXIC_CLEAR_PINTRIGGER_EVENTFLAG(__HANDLE__ , __CLRFLAG__) (((__HANDLE__)->Instance->PF.W) = (__CLRFLAG__))   


///@}



 /*! @name Function declare
*/
///@{ 
void MID_EXIC_PxTriggerAndUnmatch_Cmd( EXIC_HandleTypeDef* MEXIC_PX );
void MID_EXIC_PxTriggerAndMask_Select( EXIC_HandleTypeDef* MEXIC_PX );
void MID_EXIC_PxTriggerOrMask_Select( EXIC_HandleTypeDef* MEXIC_PX);
MID_StatusTypeDef MID_EXIC_PxTriggerMode_Config(EXIC_HandleTypeDef* MEXIC_PX ,uint32_t EXIC_PIN , uint32_t EXIC_TRG_MDS );
void MID_EXIC_ClearITFlag( EXIC_HandleTypeDef* MEXIC_PX , uint32_t ITFlag);

MID_StatusTypeDef MID_EXIC_DeInit( EXIC_HandleTypeDef* MEXIC_PX );
MID_StatusTypeDef MID_EXIC_PxTrigger_Init( EXIC_HandleTypeDef* MEXIC_PX);

void MID_EXIC_MspDeInit(EXIC_HandleTypeDef* MEXIC_PX);
void MID_EXIC_MspInit( EXIC_HandleTypeDef* MEXIC_PX);
void MID_EXIC_AFCallback( EXIC_HandleTypeDef* MEXIC_PX);
void MID_EXIC_OFCallback( EXIC_HandleTypeDef* MEXIC_PX );
    
void MID_EXIC_IRQHandler( EXIC_HandleTypeDef* MEXIC_PX);
///@} 




#endif
 
 
 
 
 
