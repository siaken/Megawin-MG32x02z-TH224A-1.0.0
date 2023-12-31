/*
  main.cpp - Main loop for Arduino sketches
  Copyright (c) 2023 megawin Technology Co..  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#define ARDUINO_MAIN
#include "Arduino.h"
#include "MG32x02z_ChipInit.h"
#include "MG32x02z_URT_MID.h"
#include "MG32x02z_CSC_Init.h"

#include "shell.h"


MG32_Shell  DebugShell;
extern Uart UartSerial_0;

#ifdef __cplusplus
 extern "C" {
#endif



//#include "MG32x02z_USB_DRV.h"

int fputc(int ch, FILE *f __attribute__((unused)));

#if 1
// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated objects that need HAL may fail.
__attribute__((constructor(101))) void premain()
{
    // Required by FreeRTOS, see http://www.freertos.org/RTOS-Cortex-M3-M4.html
#ifdef NVIC_PRIORITYGROUP_4
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
#endif
#if (__CORTEX_M == 0x07U)
    // Defined in CMSIS core_cm7.h
#ifndef I_CACHE_DISABLED
    SCB_EnableICache();
#endif
#ifndef D_CACHE_DISABLED
    SCB_EnableDCache();
#endif
#endif

    init();
}

#endif


// Weak empty variant initialization function.
// May be redefined by variant files.

// Initialize C library
extern "C" void __libc_init_array(void);

extern "C"  void Usb_StateHandler(void);

/*
 * \brief Main entry point of Arduino application
 */
int main()
{
    init();

    __libc_init_array();

    initVariant();

    MID_Delay(1);

#if defined(USBCON)
//    USBDevice.init();
//    USBDevice.attach();
#endif

    setup();

    //DebugShell.Init( &Serial );


    for (;;) 
    {
        DebugShell.Run();
        
        Usb_StateHandler();

#if defined(CORE_CALLBACK)
        CoreCallback();
#endif

        loop();

        if (serialEventRun)
        {
            serialEventRun();   
        }

    }

    return 0;
}



#ifdef __cplusplus
}
#endif




