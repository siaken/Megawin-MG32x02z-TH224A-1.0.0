/*
  Copyright (c) 2011-2012 Arduino.  All right reserved.

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

#include "WInterrupts.h"

#include "MG32x02z.h"
#include "system_MG32x02z.h"
#include "MG32x02z_CSC_Init.h"
#include "MG32x02z_GPIO_MID.h"
#include "MG32x02z_EXIC_MID.h"
#include "MG32x02z_EXIC_DRV.h"

#include "interrupt.h"

#ifdef __cplusplus
extern "C" {
#endif

//This is the list of the digital IOs configured
PinDescription g_intPinConfigured[MAX_DIGITAL_IOS];


void attachInterrupt(uint32_t pin, void (*callback)(void), uint32_t mode)
{

    //not a valid pin
    if(pin>MAX_DIGITAL_IOS) 
    {
        return ;
    }

/*
    //find the pin.
    for(i = 0; i < PINS_COUNT; i++)
    {
        if(g_intPinConfigured[i].arduino_id == pin)
        {
            g_intPinConfigured[i] = g_APinDescription[pin];
            g_intPinConfigured[i].configured = true;
            break;
        }
    }
*/


    megawin_ExicInterruptSet( pin, callback,  mode );

}

void detachInterrupt(uint32_t pin)
{
    //not a valid pin
    if(pin>MAX_DIGITAL_IOS)
    {
        return ;
    }
/*
    //find the pin.
    for(i = 0; i < PINS_COUNT; i++)
    {
        if(g_intPinConfigured[i].arduino_id == pin)
        {
            g_intPinConfigured[pin] = g_APinDescription[i];
            g_intPinConfigured[pin].configured = false;
            break;
        }
    }
*/
    megawin_ExicInterruptDisable(  pin );
}
