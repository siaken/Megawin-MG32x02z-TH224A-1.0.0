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
#include "dac.h"
#include "variant.h"

#ifdef MG32F02U128
#include "MG32x02z_DAC_MID.h"
#endif

/* Private variables ---------------------------------------------------------*/
typedef struct
{
    uint32_t                pin;
    uint16_t                pinAFS;
    uint16_t                padding;
    DAC_HandleTypeDef       mDAC;
    uint32_t                cfgflag;
}dac_config_str;

#define  DACPIN_AFS_CFG(a, num, afs)      .pin=MCU_##a##num, .pinAFS=a##num##_AFS_##afs


#ifdef MG32F02U128
#define    NB_DAC_CHANNELS     1

dac_config_str   dac_cfg[NB_DAC_CHANNELS] = 
{
    {
        DACPIN_AFS_CFG(PB, 2, GPB2),
        .mDAC=
        {
            .Instance = DAC,
            .Init =
            {
                .TriggerConverionSrc   = DAC_TRIGGERSOURCE_WRITE_DAT0,
                .TriggerConverionEdge  = DAC_DUAL_EDGE_UPDATE, 
                .DataAlign  = DAC_ALIGN_12B_R,
                #if defined(MG32_1ST)
                .OutputLevel           = DAC_OUTPUTCURRENT_MODE0,
                #endif
                .InteruptMode          = DAC_IT_READY,
            }
        },
        .cfgflag = 0,
    },
};
#endif

static uint16_t DAC_InitCfg( uint32_t Resolution )
{  
    int i;
    
#ifdef MG32F02U128
    for( i = 0; i<NB_DAC_CHANNELS; i++ )
    {
        dac_cfg[i].mDAC.Instance                   = DAC;
        dac_cfg[i].mDAC.Init.TriggerConverionSrc   = DAC_TRIGGERSOURCE_WRITE_DAT0;
        dac_cfg[i].mDAC.Init.TriggerConverionEdge  = DAC_DUAL_EDGE_UPDATE; 


        switch( Resolution )
        {
            case 12:
                dac_cfg[i].mDAC.Init.DataAlign  = DAC_ALIGN_12B_R;
                break;
            case 10:
                dac_cfg[i].mDAC.Init.DataAlign  = DAC_ALIGN_10B_R;
                break;
            case 8:
                dac_cfg[i].mDAC.Init.DataAlign  = DAC_ALIGN_8B_R;
                break;
            default:
                dac_cfg[i].mDAC.Init.DataAlign  = DAC_ALIGN_12B_R;
                break;
        }

        #if defined(MG32_1ST)
        dac_cfg[i].mDAC.Init.OutputLevel           = DAC_OUTPUTCURRENT_MODE0;      // DAC output ~0.5mA 
        #endif
        dac_cfg[i].mDAC.Init.InteruptMode          = DAC_IT_READY;                 // DAC will trigger INT when READY flag happened.
        
        MID_DAC_Init( &(dac_cfg[i].mDAC) );
        dac_cfg[i].cfgflag = 0;
    }
#endif

    return 0;
}


uint16_t dac_write_init( uint32_t Resolution )
{
    return DAC_InitCfg( Resolution );
}



uint16_t dac_write_SetResolution( uint32_t Resolution )
{
    return DAC_InitCfg( Resolution );
}


static int8_t get_dac_instance( uint32_t pin )
{
    int8_t i;

    for(i = 0; i < NB_DAC_CHANNELS; i++) 
    {
        if( ( dac_cfg[i].pin == pin) ) 
        {
            return i;
        }
    }
    return -1;
}

uint16_t dac_write_value( uint32_t ulPin,  uint32_t Data )
{
    int8_t idx = -1;
    
    Pin_Struct*  pPinx;		
    GPIO_InitTypeDef GPIOX;

    idx = get_dac_instance( ulPin );
    if( ( idx >= NB_DAC_CHANNELS ) ||(idx < 0 ) )
    {
        return  (uint16_t)-1;
    }
    
    if( dac_cfg[idx].cfgflag == 0 )
    {
        GPIOX.Mode = GPIO_MODE_ANALOG_IO;       //GPIO_MODE_ANALOG_IO
        GPIOX.Pull = GPIO_NOPULLUP;
        GPIOX.Pin            = g_APinDescription[ulPin].GioPin;
        GPIOX.Speed          = GPIO_SPEED_HIGH;
        GPIOX.OUTDrive       = GPIO_OUTDRIVE_LEVEL0;
        GPIOX.FilterDivider  = GPIO_FILTERDIVIDER_BYPASS;
        GPIOX.Inverse        = GPIO_INVERSE_DISABLE;
        GPIOX.Alternate      = g_APinDescription[ulPin].AFS;
        pPinx = __GetPinxx_byGPIOx( g_APinDescription[ulPin].ulPort,    g_APinDescription[ulPin].PinNum );
        MID_GPIO_Pin_Init(  pPinx,  &GPIOX);

        dac_cfg[idx].cfgflag = 1;
    }

    MID_DAC_SetValue( &(dac_cfg[idx].mDAC), Data);
    MID_DAC_Start( &(dac_cfg[idx].mDAC) );
    return 0;
}

uint16_t dac_stop(  uint32_t ulPin )
{
    int8_t idx = -1;
    idx = get_dac_instance( ulPin );
    if( ( idx >= NB_DAC_CHANNELS ) ||(idx < 0 ) )
    {
        return (uint16_t)-1;
    }

    MID_DAC_Stop( &(dac_cfg[idx].mDAC) );
    return 0;
}


uint16_t dac_Deinit ( )
{
    int8_t i;


    for(i = 0; i < NB_DAC_CHANNELS; i++) 
    {
        MID_DAC_Stop( &(dac_cfg[i].mDAC) );
        MID_DAC_DeInit( &(dac_cfg[i].mDAC) );
    }
    return 0;
}
