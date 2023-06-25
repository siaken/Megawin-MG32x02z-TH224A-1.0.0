
/**
 ******************************************************************************
 *
 ******************************************************************************
 * @file    digital_io.c
 * @author  cuij
 * @version V1.0.0
 * @date    11-11-2022
 * @brief   The  code is that use adapted to Arduino interface
 *
 * @par         Project
 *              MG32x02z
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2022 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 * 
 ******************************************************************************* 
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2022 megawin Technology Co., Ltd.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
 *******************************************************************************
 */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup 
  * @{
  */

/** @addtogroup 
  * @{
  */
#include "MG32x02z.h"
#include "MG32x02z_GPIO.h"
#include "system_MG32x02z.h"
#include "hw_config.h"
#include "variant.h"

#ifdef __cplusplus
 extern "C" {
#endif
/**
  * @}
  */

/** @addtogroup 
  * @{
  */

/**
  * @}
  */

/** @addtogroup 
  * @{
  */
/**
  * @}
  */

/** @addtogroup 
  * @{
  */

/**
  * @}
  */

/** @addtogroup 
  * @{
  */

/**
  * @}
  */

/** @addtogroup 
  * @{
  */

/**
  * @}
  */





/**
 *******************************************************************************
 * @brief	    GPIO Init code.
 * @param  port : one of the gpio port
 * @param  pin : one of the gpio pin
 * @param  mode : one of the gpio mode (cf hal_gpio.h)
 * @param  pull : one of the pullup/down mode (cf hal_gpio.h) 
 * @return      
 * @exception   No
 * @note        No
 *******************************************************************************
 */
void digital_io_init(GPIO_Struct  *port, uint32_t pinNum,  uint32_t afs,  uint32_t mode, uint32_t pull)
{
    //IOM_Struct*         IOMx;
    Pin_Struct*         Pinxs;
    GPIO_InitTypeDef    GPIOX;
    //uint32_t            SMP_GPIO_Delay;
    //uint32_t            GPIO_Status;
    //uint8_t             PIN_Status;
    uint32_t         pin;
    pin = ((uint16_t)0x0001<<pinNum);
    

    //Use port inital.
    GPIOX.Pin           = pin;

    GPIOX.Mode          = mode;
    GPIOX.Pull          = pull; 
    GPIOX.Speed         = GPIO_SPEED_LOW;                        // Output speed no high speed mode.
    GPIOX.Inverse       = GPIO_INVERSE_DISABLE;                  // Disable input inverse.
    GPIOX.OUTDrive      = GPIO_OUTDRIVE_LEVEL0;                  // Output drive strength is level0
    GPIOX.FilterDivider = GPIO_FILTERDIVIDER_BYPASS;             // Disable input filter.
    GPIOX.Alternate     = afs;                                   // The pins alternate function is GPIO


    //===============================================================
    //Use port inital
    //IOMx = __GetIOMx_byGPIOx( port );
    //if( NULL == IOMx )
    //{
    //    retrun;
    //}
    //MID_GPIO_Init( IOMx ,&GPIOX); 

    //===============================================================
    //Use pin inital
    Pinxs = __GetPinxx_byGPIOx( port, pinNum );
    if( NULL != Pinxs )
    {
 //       MID_GPIO_Init( IOMx ,&GPIOX); 
        MID_GPIO_Pin_Init( Pinxs , &GPIOX);
    }  


}




/**
  * @brief  This function set a value to an IO
  * @param  port : one of the gpio port
  * @param  pin : one of the gpio pin
  * @param  val : 0 to set to low, any other value to set to high
  * @retval None
  */
void digital_io_write(GPIO_Struct  *port, uint32_t pinNum, uint32_t val)
{
    
    uint32_t         pin;
    pin = ((uint16_t)0x0001<<pinNum);
    if(val)
    {
        GPIO_SetPortBit(port, pin);
    }
    else
    {
        GPIO_ClearPortBit(port, pin);
    }
}


extern void printHex( uint16_t aa ) ;

/**
  * @brief  This function set a value to an IO
  * @param  port : one of the gpio port
  * @param  pin : one of the gpio pin
  * @retval The pin state (LOW or HIGH)
  */
uint32_t digital_io_read(GPIO_Struct  *port, uint32_t pinNum)
{
    uint16_t         GPIO_Status;
    uint32_t         pin;
    
    pin = ((uint16_t)0x0001<<pinNum);

    GPIO_Status = GPIO_ReadPort( port ); 

    return ((uint32_t) (GPIO_Status & pin) );
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif

/*********COPYRIGHT(c) 2022 megawin Technology Co., Ltd *****END OF FILE****/

