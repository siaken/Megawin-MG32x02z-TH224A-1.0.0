/**
 ******************************************************************************
 *
 * @file        MG32x02z_CMP_DRV.h
 *
 * @brief       This file contains all the functions prototypes for the CMP 
 *              firmware library.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.18
 * @date        2021/02/08
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

#ifndef _MG32x02z_CMP_DRV_H

/*!< _MG32x02z_CMP_DRV_H */ 
#define _MG32x02z_CMP_DRV_H


#include "MG32x02z__Common_DRV.h"

#if defined(MG32_1ST) || defined(MG32_2ND) || defined(MG32_3RD)

#include "MG32x02z_CMP.h"
#include "MG32x02z__ExtraStruct.h"


/** @brief AC0 RisingEdge_IE Rising edge interrupt Enable */
#define AC0_RisingEdge_IE       CMP_INT_AC0_RIE_enable_w   
/** @brief AC0 FallingEdge_IE Falling edge interrupt Enable */
#define AC0_FallingEdge_IE      CMP_INT_AC0_FIE_enable_w     

/** @brief AC1 RisingEdge_IE Rising edge interrupt Enable */
#define AC1_RisingEdge_IE       CMP_INT_AC1_RIE_enable_w   
/** @brief AC1 FallingEdge_IE Falling edge interrupt Enable */
#define AC1_FallingEdge_IE      CMP_INT_AC1_FIE_enable_w     

#if defined(MG32_1ST)
/** @brief AC2 RisingEdge_IE Rising edge interrupt Enable */
#define AC2_RisingEdge_IE       CMP_INT_AC2_RIE_enable_w   
/** @brief AC2 FallingEdge_IE Falling edge interrupt Enable */
#define AC2_FallingEdge_IE      CMP_INT_AC2_FIE_enable_w     

/** @brief AC3 RisingEdge_IE Rising edge interrupt Enable */
#define AC3_RisingEdge_IE       CMP_INT_AC3_RIE_enable_w   
/** @brief AC3 FallingEdge_IE Falling edge interrupt Enable */
#define AC3_FallingEdge_IE      CMP_INT_AC3_FIE_enable_w   
#endif  

/** @brief RisingEdge_Flag Rising edge flag */
#define AC0_RisingEdge_Flag     CMP_STA_AC0_RF_happened_w    
/** @brief FallingEdge_Flag  Falling edge flag */
#define AC0_FallingEdge_Flag    CMP_STA_AC0_FF_happened_w    

/** @brief RisingEdge_Flag Rising edge flag */
#define AC1_RisingEdge_Flag      CMP_STA_AC1_RF_happened_w    
/** @brief FallingEdge_Flag  Falling edge flag */
#define AC1_FallingEdge_Flag    CMP_STA_AC1_FF_happened_w    

#if defined(MG32_1ST)
/** @brief RisingEdge_Flag Rising edge flag */
#define AC2_RisingEdge_Flag      CMP_STA_AC2_RF_happened_w    
/** @brief FallingEdge_Flag  Falling edge flag */
#define AC2_FallingEdge_Flag    CMP_STA_AC2_FF_happened_w    

/** @brief RisingEdge_Flag Rising edge flag */
#define AC3_RisingEdge_Flag      CMP_STA_AC3_RF_happened_w    
/** @brief FallingEdge_Flag  Falling edge flag */
#define AC3_FallingEdge_Flag    CMP_STA_AC3_FF_happened_w    
#endif  

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus


/** 
 * @enum		CMP_PowerLevelDef
 * @brief		declare comparator response ability 
 */        
typedef enum 
{ 
    CMP_Normal,             /*!< response time ~ 200ns */
    CMP_Slow                /*!< response time 5~10us */
} CMP_PowerLevelDef;

/** 
 * @enum		CMP_SynchClockSrcDef
 * @brief		declare comparator synchronized clock source 
 */        
typedef enum 
{ 
    CMP_ByPass,             /*!< bypass (no schronized)*/
    CMP_CMPCK,              /*!< synchronized clock from CMP_PROC */
    CMP_TM00_TRGO,          /*!< synchronized clock from TM00 TRGO */
    CMP_TM01_TRGO           /*!< synchronized clock from TM01 TRGO */
} CMP_SynchClockSrcDef;


/** 
 * @enum		CMP_SYNCHClockDivDef
 * @brief		declare CMP synchronized filter clock divided 
 */        
typedef enum 
{ 
    CMP_SFDIV1=0,           /*!< CMP synchronized filter clock divider (DIV1) */
    CMP_SFDIV2,             /*!< CMP synchronized filter clock divider (DIV2) */
    CMP_SFDIV4,             /*!< CMP synchronized filter clock divider (DIV4) */
    CMP_SFDIV8              /*!< CMP synchronized filter clock divider (DIV8) */
} CMP_SYNCHClockDivDef;


/** 
 * @enum		CMP_OutputPolarityDef
 * @brief		declare CMP output polarity (inverse) 
 */        
typedef enum 
{ 
    CMP_PositivePolarity,   /*!< PI > NI => Out='+' */
    CMP_NegativePolarity    /*!< PI > NI => Out='-' */
} CMP_OutputPolarityDef;



#if defined(MG32_1ST) || defined(MG32_2ND)
/** 
 * @enum		CMP_ACPinInputDef
 * @brief		declare ACz input property 
 */        
typedef enum 
{ 
    CMP_ACzIVREF,           /*!< select internal reference be input */
    CMP_ACz_I0,             /*!< select AC0 input0 be input */
    CMP_ACz_I1,             /*!< select AC0 input1  be input */
    CMP_ACz_CMPC0,          /*!< select CMP common input0 be input */
    CMP_ACz_CMPC1,          /*!< select CMP common input1 be input */
    CMP_ACzLDO              /*!< select LDO be input */
} CMP_ACPinInputDef;
#endif

#if defined(MG32_3RD)
/** 
 * @enum		CMP_ACPinInputDef
 * @brief		declare ACz input property 
 */        
typedef enum 
{ 
    CMP_ACzIVREF,           /*!< select internal reference be input */
    CMP_ACz_I0,             /*!< select AC0 input0 be input */
    CMP_ACz_I1,             /*!< select AC0 input1  be input */
    CMP_ACz_CMPC0,          /*!< select CMP common input0 be input */
    CMP_ACz_CMPC1,          /*!< select CMP common input1 be input */
    CMP_ACzDAC              /*!< select DAC output be input */
} CMP_ACPinInputDef;
#endif

/** 
 * @enum		CMP_HysteresisLevel
 * @brief		declare hysteresis window level
 */        
typedef enum 
{ 
    CMP_DisableHysteresis,  /*!< Disable comparator hysteresis window */
    CMP_HysteresisLevel1    /*!< Config Hysteresis window level1 */
} CMP_HysteresisLevel;


#if defined(MG32_3RD)
/** 
 * @enum		CMP_VrefTopSourceSel
 * @brief		Comparator Vref top source select
 */        
typedef enum 
{ 
    CMP_VrefTop_VDD,        /*!< Disable comparator hysteresis window */
    CMP_VrefTop_VR0         /*!< Config Hysteresis window level1 */
} CMP_VrefTopSourceSel;
#endif


/**
 * @name	Function announce
 *   		
 */ 
///@{  
void CMP_DeInit(void);
///@}

///@{  
void CMP_Cmd(CMPAC_Struct* CMPACx, FunctionalState NewState);
void CMP_Power_Select(CMPAC_Struct* CMPACx, CMP_PowerLevelDef PowerLevelSel);
///@}

///@{  
void CMP_FilterClock_Select(CMPAC_Struct* CMPACx, CMP_SynchClockSrcDef SYNCHClockSrc);
void CMP_FilterClockDivider_Select(CMPAC_Struct* CMPACx, CMP_SYNCHClockDivDef SYNCHClockDiv);
void CMP_InverseOutputPin(CMPAC_Struct* CMPACx, FunctionalState NewState);
void CMP_OutputPolarity_Select(CMPAC_Struct* CMPACx, CMP_OutputPolarityDef OutPorSel);
///@}

///@{  
void CMP_IVREF_Cmd(CMP_Struct* CMPx, FunctionalState NewState);
void CMP_IVREF2_Cmd(CMP_Struct* CMPx, FunctionalState NewState);
DRV_Return CMP_IVREF_Select(CMP_Struct* CMPx, uint8_t RefSel);
DRV_Return CMP_IVREF2_Select(CMP_Struct* CMPx, uint8_t RefSel);
#if defined(MG32_3RD)
void CMP_IVREFTopSource_Select(CMP_Struct* CMPx, CMP_VrefTopSourceSel RefTopSel);
void CMP_IVREF2TopSource_Select(CMP_Struct* CMPx, CMP_VrefTopSourceSel RefTopSel);
#endif
///@}

#if defined(MG32_3RD)
///@{  
void CMP_AC0IVREFOuput_Cmd(CMPAC_Struct* CMPACx, FunctionalState NewState);
void CMP_AC1IVREFOuput_Cmd(CMPAC_Struct* CMPACx, FunctionalState NewState);
#endif
///@}

///@{  
void CMP_PositivePin_Select(CMPAC_Struct* CMPACx, CMP_ACPinInputDef ACzPPin);
void CMP_NegativePin_Select(CMPAC_Struct* CMPACx, CMP_ACPinInputDef ACzNPin);
///@}

#if defined(MG32_2ND) || defined(MG32_3RD)
///@{  
void CMP_SetHysteresisWindow(CMPAC_Struct* CMPACx, CMP_HysteresisLevel ACzPPin);
///@}
#endif
///@{  
void CMP_IT_Config(CMP_Struct* CMPx, uint32_t CMP_ITSrc, FunctionalState NewState);
void CMP_ITEA_Cmd(CMP_Struct* CMPx, FunctionalState NewState);
DRV_Return CMP_GetSingleFlagStatus(CMP_Struct* CMPx, uint32_t CMP_ITSrc);
uint32_t CMP_GetAllFlagStatus(CMP_Struct* CMPx);
void CMP_ClearFlag(CMP_Struct* CMPx, uint32_t CMP_ITSrc);
///@}

///@{  
DRV_Return CMP_GetOutput (CMPAC_Struct* CMPACx);
///@}



#ifdef __cplusplus
}
#endif // __cplusplus

#endif
#endif

