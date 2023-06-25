/**
 *******************************************************************************
 *
 * @file        MG32x02z_ADC_Init.c
 *
 * @brief       The ADC initial code C file
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.02
 * @date        2022/10/04
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
#include "MG32x02z_ADC_Init.h"


/**
 *******************************************************************************
 * @brief  	    Initialized ADC module.
 * @param[in]   None
 * @return      None
 *******************************************************************************
 */
void ADC_Init (void)
{
    uint16_t    SettleTime;
        
    /* ADC00 initial wizard */
    ADC0->CLK.W     = CONF_ADC_CLK;
    ADC0->WINDTH.W  = CONF_ADC_WINDTH; 
    ADC0->CR0.W     = CONF_ADC_CR0 | ADC_CR0_EN_enable_w;  
    ADC0->CR1.W     = CONF_ADC_CR1;  
    ADC0->MSK.W     = CONF_ADC_MSK;  
    ADC0->START.W   = CONF_ADC_START;
    ADC0->ANA.W     = CONF_ADC_ANA;  
    ADC0->GAIN.W    = CONF_ADC_GAIN; 
    ADC0->SUM0.W    = CONF_ADC_SUM0;
    ADC0->SUM1.W    = CONF_ADC_SUM1;
    ADC0->SUM2.W    = CONF_ADC_SUM2;
    
    
    // ADC Settle time (needs ~5us)
    for (SettleTime=0; SettleTime<250; SettleTime++);
    
    // ADC calibration 
    ADC_StartCalibration(ADC0, ENABLE); 

    // PGA calibration
    #if CONF_ADC_ANA_PGA_EN!=0
		ADC_PGAOffsetCalibration_Cmd(ADC0, ENABLE);
    #endif
   
    // Set ADC interrupt register
    #if defined(CONF_ADC_INT)
    ADC0->INT.W = CONF_ADC_INT;
    #endif
		
}






