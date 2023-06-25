/**
 ******************************************************************************
 * @file     system_MG32x02z.h
 * @brief    CMSIS Cortex-M# Device Peripheral Access Layer Source File for
 *           Device MG32x02z
 * @version  V1.00
 * @date      2021/09/06
 *
 * @note
 *
 ******************************************************************************
 * Copyright (c) 2012 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------
 */

#ifndef _system_MG32x02z_H
#define _system_MG32x02z_H

#include "stddef.h"
#include "stdio.h"
#include "string.h"

#include "MG32x02z.h"
#include "MG32x02z_GPIO.h"
#include "MG32x02z_TM.h"
#include "MG32x02z_URT.h"

#include "MG32x02z_GPIO_MID.h"
#include "MG32x02z_TM_MID.h"
#include "MG32x02z_URT_MID.h"

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
/* ToDo: add here your necessary defines for device initialization
         following is an example for different system frequencies             */
#define __IHRCO           (12000000UL)    /* On-Chip Internal frequency       */
#define __XTAL            (12000000UL)    /* Oscillator frequency             */
#define __ECKI            (12000000UL)    /* External Clock frequency         */
#define __SYS_OSC_CLK     (   __IHRCO)    /* Main oscillator frequency        */
#define __SYSTEM_CLOCK    (   __IHRCO)

/**
 *************************************************
 *  Chip definitions
 *************************************************
 */
//// Chip Generation
//#if defined(MG32F02A132) || defined(MG32F02A072) || defined(MA862)
//  #define MG32_1ST
//#elif defined(MG32F02A032)
//  #define MG32_2ND
//#elif defined(MG32F02A128) || defined(MG32F02U128) || defined(MG32F02A064) || defined(MG32F02U064)
//  #define MG32_3RD
//#elif defined(MG32F02V032)
//  #define MG32_4TH
//#endif

//#if defined(MG32F02U128) || defined(MG32F02U064)
//  #define USB_TYPE    1
//#else
//  #define USB_TYPE    0
//#endif



typedef enum 
{
  HAL_OK       = 0x00,
  HAL_ERROR    = 0x01,
  HAL_BUSY     = 0x02,
  HAL_TIMEOUT  = 0x03
} HAL_StatusTypeDef;

    
void SystemCoreClockUpdate(void);
void SystemInit (void);
void HardFault_Handler_C(unsigned int * hardfault_args, unsigned lr_value) __attribute__((noreturn));

/*----------------------------------------------------------------------------*/
/*                       End of file system_MG32x02z.h                        */
/*----------------------------------------------------------------------------*/
#endif
