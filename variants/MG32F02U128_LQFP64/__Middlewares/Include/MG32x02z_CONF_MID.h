 /**
 ******************************************************************************
 *
 * @file        MG32x02z_CONF_MID.h
 * @brief       Header file of Configuration MID module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.00
 * @date        2019/10/22
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
 *              All rights reserved.
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
 * DISCLAIMED. IN NO EVENT SMID_L THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MG32x02z_CONF_MID_H
#define _MG32x02z_CONF_MID_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* ########################## XTAL/IHRCO Values adaptation ##################### */
/**
  * @brief Adjust the value of External Clock Input Speed (EXTCK) used in your application.
  *        This value is used by the RCC MID_ module to compute the system frequency
  *        (when EXTCK is used as system clock source, directly or through the PLL).  
  */
#if !defined  (EXTCK_VALUE) 
  #define EXTCK_VALUE    ((uint32_t)12000000) /*!< Value of the External Input Clock Speed in Hz */
#endif /* EXTCK_VALUE */

/**
  * @brief Adjust the value of External High Speed oscillator (XTAL) used in your application.
  *        This value is used by the RCC MID_ module to compute the system frequency
  *        (when XTAL is used as system clock source, directly or through the PLL).  
  */
#if !defined  (XTAL_VALUE) 
  #define XTAL_VALUE    ((uint32_t)12000000) /*!< Value of the External oscillator in Hz */
#endif /* XTAL_VALUE */

/**
  * @brief In the following line adjust the External High Speed oscillator (XTAL) Startup 
  *        Timeout value 
  */
#if !defined  (XTAL_STARTUP_TIMEOUT)
  #define XTAL_STARTUP_TIMEOUT    ((uint32_t)100)   /*!< Time out for XTAL start up, in ms */
#endif /* XTAL_STARTUP_TIMEOUT */

/**
  * @brief Internal High Speed oscillator (IHRCO) value.
  *        This value is used by the RCC MID_ module to compute the system frequency
  *        (when IHRCO is used as system clock source, directly or through the PLL). 
  */
#if !defined  (IHRCO_VALUE)
  #define IHRCO_VALUE    ((uint32_t)12000000) /*!< Value of the Internal oscillator in Hz*/
#endif /* IHRCO_VALUE */

/**
  * @brief In the following line adjust the Internal High Speed oscillator (IHRCO) Startup 
  *        Timeout value 
  */
#if !defined  (IHRCO_STARTUP_TIMEOUT) 
 #define IHRCO_STARTUP_TIMEOUT   ((uint32_t)5000) /*!< Time out for IHRCO start up */
#endif /* IHRCO_STARTUP_TIMEOUT */  

/**
  * @brief Internal Low Speed oscillator (ILRCO) value.
  */
#if !defined  (ILRCO_VALUE) 
 #define ILRCO_VALUE  ((uint32_t)32000)    
#endif /* ILRCO_VALUE */                      /*!< Value of the Internal Low Speed oscillator in Hz
                                                   The real value may vary depending on the variations
                                                   in voltage and temperature.  */

/* Tip: To avoid modifying this file each time you need to use different XTAL,
   ===  you can define the XTAL value in your toolchain compiler preprocessor. */

/* ########################### System Configuration ######################### */
/**
  * @brief This is the MID_ system configuration section
  */     
#define  VDD_VALUE                    ((uint32_t)5000) /*!< Value of VDD in mv */           
#define  TICK_INT_PRIORITY            ((uint32_t)0)    /*!< tick interrupt priority (lowest by default)  */            
                                                       /*  Warning: Must be set to higher priority for MID_Delay()  */
                                                       /*  and MID_GetTick() usage under interrupt context          */
#define  USE_RTOS                       0              /*!< Application the RTOS */
//#define  INSTRUCTION_CACHE_ENABLE     0
//#define  DATA_CACHE_ENABLE            0
/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        MID_ drivers code
  */
/* #define USE_FULL_ASSERT   1U */



/* Includes ------------------------------------------------------------------*/



/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT
/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function
  *         which reports the name of the source file and the source
  *         line number of the call that failed. 
  *         If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0U : assert_failed((char *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(char* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */    
    
#ifdef __cplusplus
}
#endif

#endif /* __MG32x02z_CONF_MID_H */

/************** (C) COPYRIGHT megawin Technology Co., Ltd. *****END OF FILE****/


