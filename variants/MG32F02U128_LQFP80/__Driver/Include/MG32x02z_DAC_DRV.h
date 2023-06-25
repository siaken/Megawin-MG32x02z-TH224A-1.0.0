/**
 ******************************************************************************
 *
 * @file        MG32x02z_DAC_DRV.h
 *
 * @brief       This file contains all the functions prototypes for the DAC 
 *              firmware library.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.12
 * @date        2020/03/30
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


#ifndef _MG32x02z_DAC_DRV_H

/*!< _MG32x02z_DAC_DRV_H */ 
#define _MG32x02z_DAC_DRV_H


#include "MG32x02z__Common_DRV.h"

#if defined(MG32_1ST) || defined(MG32_3RD)
#include "MG32x02z_DAC.h"


/** @brief  RisingEdge_IE Rising edge interrupt Enable */
#define Underrun_IE         DAC_INT_UDR0_IE_enable_w   
/** @brief  FallingEdge_IE Falling edge interrupt Enable */
#define Ready_IE            DAC_INT_RDY0_IE_enable_w      
/** @brief  RisingEdge_Flag Rising edge flag */
#define Underrun_Flag       DAC_STA_UDR0F_happened_w    
/** @brief  FallingEdge_Flag  Falling edge flag */
#define Ready_Flag          DAC_STA_RDY0F_happened_w    



#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

/** 
 * @enum		DAC_DataAlignModeDef
 * @brief		config data alignment mode (Right/Left alignment)
 */        
typedef enum 
{ 
    DAC_RightJustified, /*!< Right Justified of DAC conversion data format */
    DAC_LeftJustified   /*!< Left Justified of DAC conversion data format  */
} DAC_DataAlignModeDef;


#if defined(MG32_1ST)
/** 
 * @enum		DAC_ResolutionDef
 * @brief		config data resolution (10/8 bit)
 */        
typedef enum 
{ 
    DAC_10BitData,  /*!< data resolution = 10 bit */
    DAC_8BitData    /*!< data resolution = 8 bit */
} DAC_ResolutionDef;
#endif

#if defined(MG32_3RD)
/** 
 * @enum		DAC_ResolutionDef
 * @brief		config data resolution (12/10/8 bit)
 */        
typedef enum 
{ 
    DAC_12BitData,  /*!< data resolution = 12 bit */
    DAC_10BitData,  /*!< data resolution = 10 bit */
    DAC_8BitData    /*!< data resolution = 8 bit */
} DAC_ResolutionDef;
#endif

/** 
 * @enum		DAC_TriggerSourceDef
 * @brief		DAC0 start control source select
 */        
typedef enum 
{ 
    DAC_SoftWare,       /*!< Software Write data (manual updata data) */
    DAC_TRGPin,         /*!< PIN : DAC0_TRG : DAC external trigger pin */
    DAC_CMP0Out,        /*!< CMP0 : CMP0_OUT */
    DAC_TM00_TRGO,      /*!< TM00 : TM00_TRGO */
    DAC_TM01_TRGO,      /*!< TM01 : TM01_TRGO */
    DAC_TM10_TRGO,      /*!< TM10 : TM10_TRGO */
    DAC_ITR6,           /*!< ITR6 : Trigger source from APB ITR6 signal */
    DAC_ITR7            /*!< ITR7 : Trigger source from APB ITR7 signal */
} DAC_TriggerSourceDef;

/** 
 * @enum		DAC_TriggerEdgeDef
 * @brief		config trigger event to start conversion
 */        
typedef enum 
{ 
    DAC_DisableTrg,         /*!< Disable update */
    DAC_AcceptRisingEdge,   /*!< accept rising edge of  trigger  */
    DAC_AcceptFallingEdge,  /*!< accept falling edge of  trigger  */
    DAC_AcceptDualEdge      /*!< accept dual (rising & falling) edge of  trigger */
} DAC_TriggerEdgeDef;

#if defined(MG32_1ST)
/** 
 * @enum		DAC_CurrentModeDef
 * @brief		config DAC output current 
 */        
typedef enum 
{ 
    DAC_M0=0,           /*!< M0 : ~0.5mA full-scale output current */
    DAC_M1=1,           /*!< M1 : ~1mA full-scale output current */
    DAC_M2=3            /*!< M2 : ~2mA full-scale output current */
} DAC_CurrentModeDef;
#endif




/**
 * @name	Function announce
 *   		
 */ 
///@{  
void DAC_DeInit(DAC_Struct* DACx);
///@}

///@{  
void DAC_Cmd(DAC_Struct* DACx, FunctionalState NewState);
DRV_Return DAC_GetDACState(DAC_Struct* DACx);
///@}

///@{  
#if defined(MG32_1ST)
void DAC_CurrentMode_Select(DAC_Struct* DACx, DAC_CurrentModeDef OutCurr);
#endif
#if defined(MG32_3RD)
void DAC_OutputBuffer_Cmd(DAC_Struct* DACx, FunctionalState NewState);
#endif
///@}

///@{  
uint16_t DAC_GetDAT0(DAC_Struct* DACx);
void DAC_SetDAT0(DAC_Struct* DACx,uint16_t dat);
uint16_t DAC_GetOutput(DAC_Struct* DACx);
///@}

///@{  
void DAC_TriggerSource_Select(DAC_Struct* DACx, DAC_TriggerSourceDef DACTrgSel);
void DAC_TriggerEdge_Select(DAC_Struct* DACx, DAC_TriggerEdgeDef DACEdgeSel);
///@}

///@{  
void DAC_DataAlignment_Select(DAC_Struct* DACx, DAC_DataAlignModeDef AlignMode);
void DAC_DataResolution_Select(DAC_Struct* DACx, DAC_ResolutionDef ResolutionData);
///@}

///@{  
void DAC_IT_Config(DAC_Struct* DACx, uint32_t DAC_ITSrc, FunctionalState NewState);
void DAC_ITEA_Cmd(DAC_Struct* DACx, FunctionalState NewState);
DRV_Return DAC_GetSingleFlagStatus(DAC_Struct* DACx, uint32_t DAC_ITSrc);
uint32_t DAC_GetAllFlagStatus(DAC_Struct* DACx);
void DAC_ClearFlag(DAC_Struct* DACx, uint32_t DAC_ITSrc);
///@}

///@{  
void DAC_DMA_Cmd(DAC_Struct* DACx, FunctionalState NewState);

///@}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif

#endif
