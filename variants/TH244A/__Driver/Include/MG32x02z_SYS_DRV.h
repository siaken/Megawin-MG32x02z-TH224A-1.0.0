/**
 *******************************************************************************
 *
 * @file        MG32x02z_SYS_DRV.h
 *
 * @brief       This is the C code format driver head file for SYS module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.13
 * @date        2021/03/26
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2021 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 *
 *******************************************************************************
 * @par 		Disclaimer 
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

#ifndef _MG32x02z_SYS_DRV_H
/*!< _MG32x02z_SYS_DRV_H */ 
#define _MG32x02z_SYS_DRV_H 



#include "MG32x02z__Common_DRV.h"
#include "MG32x02z_SYS.h"


#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

/**
 * @name    Function announce
 *
 */ 
///@{  
void SYS_ITEA_Cmd (FunctionalState NewState);
uint32_t SYS_GetChipMID (void);
uint8_t SYS_ReadGeneralReg (void);
void SYS_WriteGeneralReg (uint8_t SYS_Value);

#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
uint32_t SYS_ReadBackupReg (void);
void SYS_WriteBackupReg (uint32_t SYS_Value);
#endif
///@}


#ifdef __cplusplus
}
#endif // __cplusplus

#endif  //_MG32x02z_SYS_DRV_H

