

/**
 ******************************************************************************
 *
 * @file        MG32x02z_EXIC_DRV.H
 *
 * @brief       This file contains all the functions prototypes for the EXIC
 *              firmware library.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.14
 * @date        2022/09/16
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

#ifndef __MG32x02z_EXIC_DRV_H
#define __MG32x02z_EXIC_DRV_H


#include "MG32x02z__Common_DRV.h"
#include "MG32x02z__ExtraStruct.h"
#include "MG32x02z_EXIC.h" 



///@{

#define EXIC_PA_IT          EXIC_INT_PA_IEA_mask_w                                      /*!< External trigger interrupt flag Control Definitions */
#define EXIC_PB_IT          EXIC_INT_PB_IEA_mask_w                                      /*!< External trigger interrupt flag Control Definitions */
#define EXIC_PC_IT          EXIC_INT_PC_IEA_mask_w                                      /*!< External trigger interrupt flag Control Definitions */
#define EXIC_PD_IT          EXIC_INT_PD_IEA_mask_w                                      /*!< External trigger interrupt flag Control Definitions */
#if defined(EXIC_PE_Base)
#define EXIC_PE_IT          EXIC_INT_PE_IEA_mask_w                                      /*!< External trigger interrupt flag Control Definitions */ 
#endif

#define EXIC_PX_AF          EXIC_STA_PA_AF_mask_b0              /*!< Byte of PX_AF mask */                
#define EXIC_PX_OF          EXIC_STA_PA_OF_mask_b0              /*!< Byte of PX_OF mask */                  
#define EXIC_PX_ITF_Mask    (EXIC_PX_AF | EXIC_PX_OF)           /*!< Byte of EXIC PX interrupt flag mask */
#define EXIC_PX_ITF_Shift   4

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

#define EXIC_ID_ADR_Base    0x50000060
#define EXIC_ID_MAX         32



/**
 *******************************************************************************
 * @brief  Read interrupt source-0 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID0_SOURCE()           (EXIC->SRC0.B[0])      /*!< Get Interrupt 0  identity.*/    
/**
 *******************************************************************************
 * @brief  Read interrupt source-1 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID1_SOURCE()           (EXIC->SRC0.B[1])      /*!< Get Interrupt 1  identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-2 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID2_SOURCE()           (EXIC->SRC0.B[2])      /*!< Get Interrupt 2  identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-3 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID3_SOURCE()           (EXIC->SRC0.B[3])      /*!< Get Interrupt 3  identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-4 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID4_SOURCE()           (EXIC->SRC1.B[0])      /*!< Get Interrupt 4  identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-5 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID5_SOURCE()           (EXIC->SRC1.B[1])      /*!< Get Interrupt 5  identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-6 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID6_SOURCE()           (EXIC->SRC1.B[2])      /*!< Get Interrupt 6  identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-7 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID7_SOURCE()           (EXIC->SRC1.B[3])      /*!< Get Interrupt 7  identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-8 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID8_SOURCE()           (EXIC->SRC2.B[0])      /*!< Get Interrupt 8  identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-9 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID9_SOURCE()           (EXIC->SRC2.B[1])      /*!< Get Interrupt 9  identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-10 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID10_SOURCE()          (EXIC->SRC2.B[2])      /*!< Get Interrupt 10 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-11 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID11_SOURCE()          (EXIC->SRC2.B[3])      /*!< Get Interrupt 11 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-12 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID12_SOURCE()          (EXIC->SRC3.B[0])      /*!< Get Interrupt 12 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-13 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID13_SOURCE()          (EXIC->SRC3.B[1])      /*!< Get Interrupt 13 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-14 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID14_SOURCE()          (EXIC->SRC3.B[2])      /*!< Get Interrupt 14 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-15 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID15_SOURCE()          (EXIC->SRC3.B[3])      /*!< Get Interrupt 15 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-16 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID16_SOURCE()          (EXIC->SRC4.B[0])      /*!< Get Interrupt 16 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-17 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID17_SOURCE()          (EXIC->SRC4.B[1])      /*!< Get Interrupt 17 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-18 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID18_SOURCE()          (EXIC->SRC4.B[2])      /*!< Get Interrupt 18 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-19 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID19_SOURCE()          (EXIC->SRC4.B[3])      /*!< Get Interrupt 19 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-20 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID20_SOURCE()          (EXIC->SRC5.B[0])      /*!< Get Interrupt 20 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-21 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID21_SOURCE()          (EXIC->SRC5.B[1])      /*!< Get Interrupt 21 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-22 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID22_SOURCE()          (EXIC->SRC5.B[2])      /*!< Get Interrupt 22 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-23 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID23_SOURCE()          (EXIC->SRC5.B[3])      /*!< Get Interrupt 23 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-24 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID24_SOURCE()          (EXIC->SRC6.B[0])      /*!< Get Interrupt 24 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-25 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID25_SOURCE()          (EXIC->SRC6.B[1])      /*!< Get Interrupt 25 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-26 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID26_SOURCE()          (EXIC->SRC6.B[2])      /*!< Get Interrupt 26 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-27 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID27_SOURCE()          (EXIC->SRC6.B[3])      /*!< Get Interrupt 27 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-28 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID28_SOURCE()          (EXIC->SRC7.B[0])      /*!< Get Interrupt 28 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-29 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID29_SOURCE()          (EXIC->SRC7.B[1])      /*!< Get Interrupt 29 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-30 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID30_SOURCE()          (EXIC->SRC7.B[2])      /*!< Get Interrupt 30 identity.*/
/**
 *******************************************************************************
 * @brief  Read interrupt source-31 identity.
 * @return No
 *******************************************************************************
 */
#define __DRV_EXIC_GET_ID31_SOURCE()          (EXIC->SRC7.B[3])      /*!< Get Interrupt 31 identity.*/




///@}


#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

/*! @enum   EXIC_TRGSMode_Typedef
    @brief  External pin edge / level trigger event select definitions.
*/
typedef enum
{
	No_UpData_Flag  =   0,                  /*!< No external trgger function */
    Level           =   1,                  /*!< External trigger event is level*/ 
    Edge            =   2,                  /*!< External trigger event is edge*/
    Dual_edge       =   3                   /*!< External trigger event is dual edge*/
}EXIC_TRGSMode_Typedef;                              


/*! @enum   EXIC_ITFlag_Typdef
    @brief  Read / Clear interrupt flag of Port select definitions.
*/
typedef enum
{
    EXIC_PA_ITF    = 0,                     /*!< PortA*/                                               
    EXIC_PB_ITF    = 1,                     /*!< PortB*/
    EXIC_PC_ITF    = 2,                     /*!< PortC*/                        
    #if defined(EXIC_PE_Base)
        EXIC_PD_ITF    = 3,                 /*!< PortD*/
        EXIC_PE_ITF    = 4                  /*!< PortE*/
    #else
        EXIC_PD_ITF    = 3                  /*!< PortD*/
    #endif
}EXIC_ITFlag_Typdef;


#if defined(EXIC_CR0_NMI_SEL_mask_w) && defined(EXIC_CR0_NMI_MUX_mask_w)
/** 
 * @enum	EXIC_NMIMUX_Typedef
 * @brief	Control NIM trigger source select.
 */
typedef enum
{
    EXIC_NMI_WWDT       = 0x00000000 | EXIC_CR0_NMI_SEL_mask_w,    /*!< Trigger NMI source from WWDT */
    EXIC_NMI_SYS        = 0x00000400 | EXIC_CR0_NMI_SEL_mask_w,    /*!< Trigger NMI source from SYS */
    EXIC_NMI_EXIN0      = 0x00000C00 | EXIC_CR0_NMI_SEL_mask_w,    /*!< Trigger NMI source from EXINT0 */
    EXIC_NMI_EXIN1      = 0x00001000 | EXIC_CR0_NMI_SEL_mask_w,    /*!< Trigger NMI source from EXINT1 */
    EXIC_NMI_EXIN2      = 0x00001400 | EXIC_CR0_NMI_SEL_mask_w,    /*!< Trigger NMI source from EXINT2 */
    EXIC_NMI_EXIN3      = 0x00001800 | EXIC_CR0_NMI_SEL_mask_w,    /*!< Trigger NMI source from EXINT3 */
    EXIC_NMI_COMP       = 0x00001C00 | EXIC_CR0_NMI_SEL_mask_w,    /*!< Trigger NMI source from COMP */
    EXIC_NMI_DMA        = 0x00002000 | EXIC_CR0_NMI_SEL_mask_w,    /*!< Trigger NMI source from DMA */
    EXIC_NMI_ADC        = 0x00002800 | EXIC_CR0_NMI_SEL_mask_w,    /*!< Trigger NMI source from ADC */
    EXIC_NMI_DAC        = 0x00002C00 | EXIC_CR0_NMI_SEL_mask_w,    /*!< Trigger NMI source from DAC */
    EXIC_NMI_TM00       = 0x00003000 | EXIC_CR0_NMI_SEL_mask_w,    /*!< Trigger NMI source from TM00 */
    EXIC_NMI_TM10       = 0x00003400 | EXIC_CR0_NMI_SEL_mask_w,    /*!< Trigger NMI source from TM10 */
    EXIC_NMI_TM16       = 0x00003800 | EXIC_CR0_NMI_SEL_mask_w,    /*!< Trigger NMI source from TM16 */
    EXIC_NMI_TM20       = 0x00003C00 | EXIC_CR0_NMI_SEL_mask_w,    /*!< Trigger NMI source from TM20 */
    EXIC_NMI_TM26       = 0x00004000 | EXIC_CR0_NMI_SEL_mask_w,    /*!< Trigger NMI source from TM26 */
    EXIC_NMI_TM36       = 0x00004400 | EXIC_CR0_NMI_SEL_mask_w,    /*!< Trigger NMI source from TM36 */
    EXIC_NMI_URT0       = 0x00005000 | EXIC_CR0_NMI_SEL_mask_w,    /*!< Trigger NMI source from URT0 */
    EXIC_NMI_URT123     = 0x00005400 | EXIC_CR0_NMI_SEL_mask_w,    /*!< Trigger NMI source from URT123 */
    EXIC_NMI_SPI0       = 0x00006000 | EXIC_CR0_NMI_SEL_mask_w,    /*!< Trigger NMI source from SPI0 */
    EXIC_NMI_I2C0       = 0x00007000 | EXIC_CR0_NMI_SEL_mask_w,    /*!< Trigger NMI source from I2C0 */
    EXIC_NMI_I2Cx       = 0x00007400 | EXIC_CR0_NMI_SEL_mask_w,    /*!< Trigger NMI source from I2Cx */
    EXIC_NMI_NMI        = 0x00000000
}EXIC_NMIMUX_Typedef;
#endif

/** 
 * @struct	EXIC_TRGSTypeDef
 * @brief	Control external pin event flag.
 */
typedef struct __attribute__((packed))
{
	uint32_t                  	EXIC_Pin;           /*!< Select external trigger pin.*/
	EXIC_TRGSMode_Typedef       EXIC_TRGS_Mode;     /*!< Select external trigger mode.*/
}EXIC_TRGSTypeDef;





void EXIC_PxTriggerITEA_Cmd(uint32_t EXIC_PX_IT, FunctionalState EXIC_IT_State);
uint32_t EXIC_GetPxAllTriggerEventFlagStatus(EXIC_PX_Struct* EXIC_PX);
uint8_t EXIC_GetPxAllTriggerITFlagStatus( EXIC_ITFlag_Typdef EXIC_PX_ITFlag);
DRV_Return EXIC_GetPinxTriggerEventSingleFlagStatus(EXIC_PX_Struct* EXIC_PX , uint16_t EXIC_Pin_PF);
DRV_Return EXIC_GetPxTriggerAndITFlagStatus( EXIC_ITFlag_Typdef EXIC_PX_ITFlag);
DRV_Return EXIC_GetPxTriggerOrITFlagStatus( EXIC_ITFlag_Typdef EXIC_PX_ITFlag);
void EXIC_ClearPxTriggerEventFlag(EXIC_PX_Struct* EXIC_PX , uint16_t EXIC_Pin_PF);
void EXIC_ClearPxTriggerITFlag( EXIC_ITFlag_Typdef EXIC_PX , uint8_t EXIC_PX_ITFlag);
DRV_Return EXIC_PxTriggerMode_Select(EXIC_PX_Struct* EXIC_PX ,EXIC_TRGSTypeDef* EXIC_PX_TRGS );
void EXIC_PxTriggerAndMask_Select(EXIC_PX_Struct* EXIC_PX , uint16_t  EXIC_MSK_PIN);
void EXIC_PxTriggerOrMask_Select(EXIC_PX_Struct* EXIC_PX , uint16_t  EXIC_MSK_PIN);
void EXIC_PxTriggerAndUnmatch_Cmd(uint32_t EXIC_PX_IT, FunctionalState PX_unMatch_Cmd);
uint8_t EXIC_GetITSourceID(IRQn_Type ITSourceNum);
void EXIC_RXEV_Cmd(FunctionalState RXEV_State);
void EXIC_NMI_Cmd(FunctionalState NMI_State);
void EXIC_NMITrigger_SW(void);
#if defined(EXIC_CR0_NMI_SEL_mask_w) && defined(EXIC_CR0_NMI_MUX_mask_w)
    void EXIC_NMI_Select(EXIC_NMIMUX_Typedef);
#endif


#ifdef __cplusplus
}
#endif // __cplusplus

#endif








