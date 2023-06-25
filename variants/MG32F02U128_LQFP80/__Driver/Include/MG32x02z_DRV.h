/**
 ******************************************************************************
 *
 * @file        MG32x02z_DRV.h
 *
 * @brief       This is the C Code Include format example file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.23
 * @date        2022/08/25
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

#ifndef _MG32x02z_DRV_H
#define _MG32x02z_DRV_H
#define _MG32x02z_DRV_H_VER                            2.20           /*!<MG32x02z Driver ver.*/



#include "MG32x02z_ADC_DRV.h"
#include "MG32x02z_APB_DRV.h"
#include "MG32x02z_CFG_DRV.h"
#include "MG32x02z_CMP_DRV.h"
#include "MG32x02z_CSC_DRV.h"
#include "MG32x02z_EXIC_DRV.h"
#include "MG32x02z_GPIO_DRV.h"
#include "MG32x02z_GPL_DRV.h"
#include "MG32x02z_I2C_DRV.h"
#include "MG32x02z_IWDT_DRV.h"
#include "MG32x02z_MEM_DRV.h"
#include "MG32x02z_PW_DRV.h"
#include "MG32x02z_RST_DRV.h"
#include "MG32x02z_SPI_DRV.h"
#include "MG32x02z_SYS_DRV.h"
#include "MG32x02z_TM_DRV.h"
#include "MG32x02z_URT_DRV.h"
#include "MG32x02z_WWDT_DRV.h"
#include "MG32x02z_DMA_DRV.h"
#include "MG32x02z_RTC_DRV.h"
#include "MG32x02z_CM0_DRV.h"

#if defined(MG32_1ST) || defined(MG32_3RD)
#include "MG32x02z_EMB_DRV.h"
#include "MG32x02z_DAC_DRV.h"
#endif

#if defined(MG32_3RD) || defined(MG32_4TH)
#include "MG32x02z_APX_DRV.h"
#endif

#if defined(USB_TYPE)
#include "MG32x02z_USB_DRV.h"
#endif



#endif

