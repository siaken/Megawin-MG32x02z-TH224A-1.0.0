/*
  Copyright (c) 2023 megawin Technology Co., Ltd. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Arduino.h"
#include "adc.h"
#include "variant.h"
#include "wiring_analog.h"


#ifdef MG32F02U128
#include "MG32x02z_ADC_MID.h"
#include "MG32x02z_ADC_DRV.h"
#endif

/* Private variables ---------------------------------------------------------*/
static   ADC_HandleTypeDef   mADC;

eAnalogReference  g_AnalogReference = AR_DEFAULT;


static uint16_t ADC_InitCfg( uint32_t Resolution,    eAnalogReference ARef  )
{
    g_AnalogReference = ARef;
    
#ifdef MG32F02U128
    MID_UnProtectModuleReg(PWmodule);
    __DRV_PW_ENANLE_VBUF();
    MID_ProtectModuleReg(PWmodule);
    
    // for VBUF 1.4V settling time
    MID_Delay(1);

    mADC.Instance                   = ADC0;                     // for ADC0
    mADC.Init.ADCConType            = ADC_CONV_SINGLE;          // Single-end type
    mADC.Init.ADCClock              = ADC_CLOCKPROC_DIV16;      // ADC_Clock = ADC_PROC/16 

#ifdef  MG32F02U128
    switch( g_AnalogReference )
    {
        case AR_INTERNAL:           //2.4V 
            ADC_IVR24_Cmd( ADC0, ENABLE );
            ADC_TopRefernce_Select(ADC0, ADC_INT_VR24);
            break;


        case AR_DEFAULT:        //VREF+
        case AR_EXTERNAL:
        default:
            ADC_TopRefernce_Select(ADC0, ADC_VREF_Pin);
            break;
    }
#endif
    

    // ADC conversion resolution
    switch( Resolution )
    {
        case 12:
            mADC.Init.Resolution = ADC_RESOLUTION_12B; 
            break;
        case 10:
            mADC.Init.Resolution = ADC_RESOLUTION_10B; 
            break;
        case 8:
            mADC.Init.Resolution = ADC_RESOLUTION_8B; 
            break;
        default:
            mADC.Init.Resolution = ADC_RESOLUTION_8B; 
            break;
    }

    mADC.Init.DataAlign             = ADC_DATAALIGN_RIGHT;      // ADC data is Right-justified
    mADC.Init.ConversionMode        = ADC_ONESHOT;              // ADC One-Shot mode to converion 
    mADC.Init.LowPowerAutoWait      = ADC_CONTINUE_NEXT;        // ADC will replace the older conversion data (WAIT_EN for scan/loop mode)
    mADC.Init.TriggerConverionSrc   = ADC_SOFTWARE_START;       // ADC trigger event from software command
    mADC.Init.TriggerConverionEdge  = ADC_TRIGCONVEDGE_NONE;    // ADC convert signal from external trigger event edge select
    mADC.Init.Overrun               = ADC_ACCEPT_OVERRUN;       // It will overrun the conversion data   
    mADC.Init.ExtendSamplingTime    = 0;                       // Extend time of 'Sample & Hold' of ADC conversion state (0 ADC_Clock)
    mADC.Init.PGACmd                = PGA_DISABLE;              // Disable ADC PGA
    mADC.Init.PGAGain               = 0;                        // PGA Gain=x1, ADC Gain is equal : (1+(ADC0_GAIN_PGA*3)/(63+(63-ADC0_GAIN_PGA)*3))
    
    MID_ADC_Init(&mADC);
        
    // for ADC settling time
    MID_Delay(1);
#endif

    
    return 0;
}

uint16_t adc_read_init( uint32_t Resolution,   eAnalogReference ARef  )
{
    g_AnalogReference = ARef;
    return ADC_InitCfg( Resolution,  g_AnalogReference );
}



uint16_t adc_read_SetResolution( uint32_t Resolution )
{
    return ADC_InitCfg( Resolution,  g_AnalogReference  );
}

uint16_t adc_read_value( uint32_t ulPin )
{

    ADC_ChannelConfTypeDef      ADCCh;
//    __IO uint32_t VddVoltage;
    __IO uint16_t CalVal = -1;


#ifdef MG32F02U128
    // ------------------------------------------------------------------------
    //Select ADC convert channels.
    // ------------------------------------------------------------------------
    if( NB_ADC_CHANNEL_MANAGED ==  g_APinDescription[ulPin].ADCChannel)
    {
        return -1;
    }
    
    ADCCh.Channel                   = g_APinDescription[ulPin].ADCChannel;   
    MID_ADC_ConfigChannel(&mADC, &ADCCh);
    
    // ------------------------------------------------------------------------
    // Trigger ADC convert. (for ADC_ONESHOT mode)
    // ------------------------------------------------------------------------
    MID_ADC_Start(&mADC);
    
    // poll ADC flag within 10ms
    MID_ADC_PollForConversion(&mADC, 10);
    
    CalVal = (uint16_t) MID_ADC_GetValue(&mADC);
//    VddVoltage = (uint32_t) (140 * 4096) ;
//    VddVoltage = VddVoltage / CalVal ;
//      return (uint16_t) VddVoltage;



#endif
    return CalVal;
}

