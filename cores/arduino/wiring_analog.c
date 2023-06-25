/*
 Copyright (c) 2011 Arduino.  All right reserved.

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
#include "adc.h"
#include "pwm.h"

#include "wiring_analog.h"

#ifdef __cplusplus
extern "C" {
#endif

static int s_readResolution    = ADC_RESOLUTION;
static int s_writeResolution   = DACC_RESOLUTION;

void analogReadInit() 
{
    switch( s_readResolution )
    {
        case 12:
        case 10:
        case 8:
            break;
        default:
            s_readResolution = 8; 
            break;
    }

    adc_read_init( s_readResolution,  g_AnalogReference );
}



void analogReadResolution(int res) 
{
    switch( res )
    {
        case 12:
        case 10:
        case 8:
            s_readResolution = res;
            break;
        default:
            s_readResolution = 8; 
            break;
    }
    adc_read_SetResolution( s_readResolution );
}



static inline uint32_t mapResolution(uint32_t value, uint32_t from, uint32_t to) 
{
    uint32_t OutValue = value;
    if (from == to)
    {
        OutValue = value;
    }
    else if (from > to)
    {
        OutValue = (value >> (from-to));
    }
    else
    {
        OutValue = (value << (to-from));
    }

/*
    if( OutValue < 0  )
    {
        OutValue = 0;
    }
*/
    if( OutValue >= (uint32_t)(1<<to)  )
    {
        OutValue =  ((1<<to)-1);
    }
    
    return OutValue;
}



//perform the read operation on the selected analog pin.
//the initialization of the analog PIN is done through this function
uint32_t analogRead(uint32_t ulPin)
{
    uint32_t ulValue = 0;
    
    Pin_Struct*  pPinx;		
    GPIO_InitTypeDef GPIOX;


    if(ulPin>MAX_DIGITAL_IOS)
    {
        return -1;
    }

    if(g_APinDescription[ulPin].ADCChannel == NB_ADC_CHANNEL_MANAGED ) 
    {
        return -1;
    }

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

    //pinMode(ulPin, INPUT);

    ulValue = adc_read_value( ulPin );

    //ulValue = mapResolution(  ulValue,   s_readResolution,  ADC_RESOLUTION );

    return ulValue;
}



void analogWriteResolution(int res)
{
    switch( res )
    {
        case 12:
        case 10:
        case 8:
            s_writeResolution = res;
            break;
        default:
            s_writeResolution = 12; 
            break;
    }

    dac_write_SetResolution( s_writeResolution );
}

void analogOutputInit(void)
{
    switch( s_writeResolution )
    {
        case 12:
        case 10:
        case 8:
            break;
        default:
            s_writeResolution = 12; 
            break;
    }
    dac_write_init( s_writeResolution );
}




void analogReference( eAnalogReference ulMode )
{
    g_AnalogReference = ulMode;

    adc_read_init( s_readResolution,  g_AnalogReference );
}

/*
void analogWriteFrequency(uint32_t ulPin,  uint32_t freq)
{
    if( freq < 300 )
    {
        freq = 300;
    }
    else if( freq > 5000 )
    {
        freq = 5000;
    }
    
    pwm_setFrequency(  ulPin,  freq );
}
*/



/*
int DEG_printHex(  uint32_t uc_data   );
int DEG_printDec(  uint32_t uc_data   );
int DEG_print(  char* str   );
*/
// Right now, PWM output only works on the pins with
// hardware support.  These are defined in the appropriate
// variant.cpp file.  For the rest of the pins, we default
// to digital output.
void analogWrite(uint32_t ulPin, uint32_t ulValue)
{
    uint32_t attr = 0;
    uint32_t datacmp = (1<<(s_writeResolution));
    
    if( ulPin>MAX_DIGITAL_IOS ) 
    {
        return;
    }

    attr = g_APinDescription[ulPin].mode;
    if((attr & PIN_ATTR_DAC) == PIN_ATTR_DAC)
    {
        //ulValue = mapResolution(ulValue, DACC_RESOLUTION,  s_writeResolution );
        if( ulValue >= (uint32_t)(1<<s_writeResolution)  )
        {
            ulValue =  ((1<<s_writeResolution)-1);
        }

        #if 0
        if( ulValue != 0 )
        {
            dac_write_value( ulPin,  ulValue );
        }
        else
        {
            dac_stop(  ulPin  );
            pinMode( ulPin, OUTPUT );
            digitalWrite( ulPin, LOW );
        }
        #else
        dac_write_value( ulPin,  ulValue );
        #endif
        
    }
    else if(  (attr & PIN_ATTR_PWM) == PIN_ATTR_PWM  )
    {
        if(   ulValue == 0 )
        {
            pwm_stop(  ulPin  );
            pinMode(ulPin, OUTPUT);
            digitalWrite(ulPin, LOW);
        }
        else 
        {
            ulValue = ulValue%PWM_MAX_DUTY_CYCLE;
            if( ulValue != 0 )
            {
                pwm_start(  ulPin,   
                            PWM_MAX_DUTY_CYCLE, 
                            ulValue,   1 );
            }
            else
            {
                pwm_stop(  ulPin  );
                pinMode(ulPin, OUTPUT);
                digitalWrite(ulPin, HIGH);
            }
        }
    }
    else
    {
        //ulValue = mapResolution(ulValue,   PWM_RESOLUTION,   s_writeResolution);
        if ( ulValue < (datacmp/2) ) 
        {
            pinMode(ulPin, OUTPUT);
            digitalWrite(ulPin, LOW);
        }
        else
        {
            pinMode(ulPin, OUTPUT);
            digitalWrite(ulPin, HIGH);
        }
    }
}






#ifdef __cplusplus
}
#endif
