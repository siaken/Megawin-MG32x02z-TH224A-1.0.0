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
#include "pwm.h"
#include "dac.h"

#ifdef __cplusplus
 extern "C" {
#endif
/*
void dac_stop( GPIO_Struct  *port, uint32_t pin )
{
    ;
}

void pwm_start( GPIO_Struct  *port, uint32_t pin, uint32_t clock_freq,
                uint32_t period, uint32_t value, uint8_t do_init )
{
    ;
}
void pwm_stop( GPIO_Struct  *port, uint32_t pin )
{
    ;
}
*/

extern void pinMode( uint32_t ulPin, uint32_t ulMode )
{
    //not a valid pin
    if(ulPin >= MAX_DIGITAL_IOS) 
    {
        return ;
    }

    // If the pin that support PWM or DAC output, we need to turn it off
    if(g_APinDescription[ulPin].configured == false )
    {
        if((g_APinDescription[ulPin].mode & PIN_ATTR_PWM) == PIN_ATTR_PWM)
        {
            pwm_stop(  ulPin  );
        } 
        else if((g_APinDescription[ulPin].mode & PIN_ATTR_DAC) == PIN_ATTR_DAC)
        {
            dac_stop(  ulPin );
        }

    }

    switch ( ulMode )
    {
        case INPUT:
            digital_io_init(g_APinDescription[ulPin].ulPort,
                            g_APinDescription[ulPin].PinNum,
                            #ifdef    MG32F02U128
                            AFS0, // g_APinDescription[ulPin].AFS, 
                            #endif 
                            GPIO_MODE_DIGITAL_I, GPIO_NOPULLUP);
            break;
        case INPUT_PULLUP:
            
            digital_io_init(g_APinDescription[ulPin].ulPort,
                            g_APinDescription[ulPin].PinNum,
                            #ifdef    MG32F02U128
                            AFS0, // g_APinDescription[ulPin].AFS, 
                            #endif 
                            GPIO_MODE_DIGITAL_I, GPIO_PULLUP);
            break;
        case INPUT_PULLDOWN:
            digital_io_init(g_APinDescription[ulPin].ulPort,
                            g_APinDescription[ulPin].PinNum,
                            #ifdef    MG32F02U128
                            AFS0, // g_APinDescription[ulPin].AFS, 
                            #endif 
                            GPIO_MODE_DIGITAL_I, GPIO_NOPULLUP);
            break;
        case OUTPUT:
            digital_io_init(g_APinDescription[ulPin].ulPort,
                            g_APinDescription[ulPin].PinNum,
                            #ifdef    MG32F02U128
                            AFS0, // g_APinDescription[ulPin].AFS, 
                            #endif 
                            GPIO_MODE_PUSHPULL_O, GPIO_PULLUP);
            break;
        default:
            break;
    }
    
    g_APinDescription[ulPin].configured = true;
}

extern void digitalWrite( uint32_t ulPin, uint32_t ulVal )
{
    //not a valid pin
    if( ulPin >= MAX_DIGITAL_IOS )
    {
        return ;
    }

    if(g_APinDescription[ulPin].configured == true)
    {
        digital_io_write( g_APinDescription[ulPin].ulPort,
                          g_APinDescription[ulPin].PinNum,
                          ulVal );
    }
}


extern int digitalRead( uint32_t ulPin )
{
    uint32_t level = 0;
    
    //not a valid pin
    if( ulPin  >= MAX_DIGITAL_IOS )
    {
        return -1;
    }

    if(g_APinDescription[ulPin].configured == true)
    {
        level = digital_io_read(  g_APinDescription[ulPin].ulPort,
                                  g_APinDescription[ulPin].PinNum   );
    }

    if(level)
    {
        return HIGH;
    }
    else
    {
        return LOW;
    }
}

#ifdef __cplusplus
}
#endif
