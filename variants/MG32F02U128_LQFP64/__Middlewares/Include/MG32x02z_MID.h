/**
 ******************************************************************************
 * @file    MG32x02z_MID.h
 * @author  MCD Application Team
 * @brief   MID module driver.
 *          This is the common part of the MID initialization
 * @version V1.03
 * @date    2022/03/07
 *
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2019 megawin Technology Co., Ltd.</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of megawin Technology Co., Ltd. nor the names of its
 *      contributors may be used to endorse or promote products derived from this
 *      software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SMIDL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 ******************************************************************************
 */ 


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MG32x02z_MID_H
#define _MG32x02z_MID_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/**
  * @brief Include module's header file 
  */
// ------------------------------------------------------------------------
#include "MG32x02z_ADC_MID.h"
#include "MG32x02z_APB_MID.h"
#include "MG32x02z_DMA_MID.h"
#include "MG32x02z_TM_MID.h"
#include "MG32x02z_RTC_MID.h"
#include "MG32x02z_IWDT_MID.h"
#include "MG32x02z_WWDT_MID.h"
#include "MG32x02z_URT_MID.h"
#include "MG32x02z_SPI_MID.h"
#include "MG32x02z_EXIC_MID.h"
#include "MG32x02z_PW_MID.h"
#include "MG32x02z_I2C_MID.h"
#include "MG32x02z_I2C_MID_ex.h"
#include "MG32x02z_MEM_MID.h"
#include "MG32x02z_CSC_MID.h"
#include "MG32x02z_GPIO_MID.h"
#include "MG32x02z_CFG_MID.h"
#include "MG32x02z_Common_MID.h"
#include "MG32x02z_CONF_MID.h"
#include "MG32x02z_cortex_MID.h"
#include "MG32x02z_GPL_MID.h"
#include "MG32x02z_RST_MID.h"
#include "MG32x02z_SYS_MID.h"

// ------------------------------------------------------------------------
#if !defined(MG32_4TH)
    #include "MG32x02z_CMP_MID.h"
#endif
// ------------------------------------------------------------------------
#if defined(MG32_1ST) || defined(MG32_3RD)
    #include "MG32x02z_DAC_MID.h"
#endif
// ------------------------------------------------------------------------
#if defined(MG32_1ST) || defined(MG32_3RD)
    #include "MG32x02z_EMB_MID.h"
#endif
// ------------------------------------------------------------------------
#if defined(MG32_3RD) || defined(MG32_4TH) 
    #include "MG32x02z_APX_MID.h"
#endif



/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  MID Status structures definition  
  */  



#ifdef __cplusplus
}
#endif

#endif /* __MG32x02z_MID */



/************** (C) COPYRIGHT megawin Technology Co., Ltd. *****END OF FILE****/


