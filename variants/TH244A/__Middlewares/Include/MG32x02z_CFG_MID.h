/**
 *******************************************************************************
 *
 * @file        MG32x02z_CFG_MID.h
 *
 * @brief       This is the h code format middleware file for SYS module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.02
 * @date        2021/03/26
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2020 Megawin Technology Co., Ltd.
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
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "MG32x02z.h"
#include "MG32x02z_CFG.h"
#include "MG32x02z_CONF_MID.h" 


#ifndef _MG32x02z_SYS_MID_H
/*!< _MG32x02z_SYS_MID_H */ 
#define _MG32x02z_SYS_MID_H

#if defined(MG32_1ST)
#define __DRV_CFG_READ_ADCREFBOTTOM()           CFG->OR15.B[1]
#define __DRV_CFG_READ_ADCREFMIDDLE()           CFG->OR15.B[2]
#define __DRV_CFG_READ_ADCREFTOP()              CFG->OR15.B[3]
#endif
#if defined(MG32_3RD) || defined(MG32_4TH)
#define __DRV_CFG_READ_ADCOFFSET()              CFG->OR17.B[3]
#endif

#if defined(MG32_1ST)
#define __DRV_CFG_WRITE_ADCREFBOTTOM(__VALUE__) (CFG->OR15.B[1] = (__VALUE__))
#define __DRV_CFG_WRITE_ADCREFMIDDLE(__VALUE__) (CFG->OR15.B[2] = (__VALUE__))
#define __DRV_CFG_WRITE_ADCREFTOP(__VALUE__)    (CFG->OR15.B[3] = (__VALUE__))
#endif
#if defined(MG32_3RD) || defined(MG32_4TH)
#define __DRV_CFG_WRITE_ADCOFFSET(__VAlue__)    (CFG->OR17.B[3] = (__VALUE__))
#endif

#endif


