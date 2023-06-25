/**
 ******************************************************************************
 *
 ******************************************************************************
 * @file    interrupt.c
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


/* Includes ------------------------------------------------------------------*/
#include "MG32x02z.h"
#include "system_MG32x02z.h"
#include "MG32x02z_CSC_Init.h"
#include "MG32x02z_GPIO_MID.h"
#include "MG32x02z_EXIC_MID.h"
#include "MG32x02z_EXIC_DRV.h"
//#include "hw_config.h"
#include "interrupt.h"
#include "variant.h"

#ifdef __cplusplus
 extern "C" {
#endif
/**
  * @}
  */


/**
  * @}
  */
#define NB_EXTCI   (16)


/** @addtogroup 
  * @{
  */

/* Wizard menu ---------------------------------------------------------------*/



/* Private typedef -----------------------------------------------------------*/

typedef struct
{
    uint32_t         arduino_id;
    uint32_t         exic_trgs;
    void (*callback)(void);
    uint32_t         mode;
    uint32_t         configured;
}gpio_irq_conf_str;





/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static gpio_irq_conf_str gpioExic_irq_conf[ NB_EXTCI ] = {
    0
};



/* Private function prototypes -----------------------------------------------*/
//void EXINT0_IRQHandler(void);
void Megawin_EXIC_Init(void);

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* External vairables --------------------------------------------------------*/
extern EXIC_HandleTypeDef  mEXIC_PA;
extern EXIC_HandleTypeDef  mEXIC_PB;
extern EXIC_HandleTypeDef  mEXIC_PC;
extern EXIC_HandleTypeDef  mEXIC_PD;

#if defined(EXIC_PE_Base)
extern EXIC_HandleTypeDef  mEXIC_PE;
#endif


/**
 *******************************************************************************
 * @brief	    External interrupt AND path happen callback.
 * @details     
 * @param[in]   MEXIC_PX   : EXIC_PORT handle.
 * @return      No.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
__WEAK void MID_EXIC_AFCallback( EXIC_HandleTypeDef* MEXIC_PX)
{
    uint16_t  AdrIdx;
    uint16_t i;
    uint16_t pEXIC_AF;

    EXIC_HandleTypeDef *ptEXIC;
    
    pEXIC_AF = (uint16_t)__DRV_EXIC_GET_PINTRIGGER_EVENTFLAG( MEXIC_PX );

    MID_EXIC_ClearITFlag( MEXIC_PX , pEXIC_AF );
    if(  0 == (MEXIC_PX->AND_Mask & pEXIC_AF)  )
    {
        return;
    }

    for(i=0; i< (sizeof(gpioExic_irq_conf)/sizeof(gpio_irq_conf_str));  i++ )
    {
        if( 0 == gpioExic_irq_conf[i].configured  )
        {
            continue;
        }

        AdrIdx = gpioExic_irq_conf[i].arduino_id;
        ptEXIC = __GetEXICx_byGPIOx( g_APinDescription[AdrIdx].ulPort ) ;

        if( ( 0 != gpioExic_irq_conf[i].configured  )
          &&( MEXIC_PX == ptEXIC  )
          &&(  0 != (pEXIC_AF & g_APinDescription[AdrIdx].GioPin) ) )
        {
            if( ( NULL != gpioExic_irq_conf[i].callback )  )
            {
                gpioExic_irq_conf[i].callback(  );
            }
        }
    }

    __DRV_EXIC_CLEAR_PINTRIGGER_EVENTFLAG( MEXIC_PX, pEXIC_AF );         
    MID_EXIC_ClearITFlag( MEXIC_PX , pEXIC_AF );
}

/**
 *******************************************************************************
 * @brief	    External interrupt OR path happen callback.
 * @details     
 * @param[in]   MEXIC_PX   : EXIC_PORT handle. 
 * @return      No.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
__WEAK void MID_EXIC_OFCallback( EXIC_HandleTypeDef* MEXIC_PX )
{

    uint16_t  AdrIdx;
    uint16_t i;
    uint16_t pEXIC_PF;
    EXIC_HandleTypeDef *ptEXIC;


    pEXIC_PF = (uint16_t)__DRV_EXIC_GET_PINTRIGGER_EVENTFLAG( MEXIC_PX );
    __DRV_EXIC_CLEAR_PINTRIGGER_EVENTFLAG( MEXIC_PX, pEXIC_PF );    
    if(  0 == (MEXIC_PX->OR_Mask & pEXIC_PF)  )
    {
        return;
    }

    for(i=0; i< (sizeof(gpioExic_irq_conf)/sizeof(gpio_irq_conf_str));  i++ )
    {
        if( 0 == gpioExic_irq_conf[i].configured  )
        {
            continue;
        }
        
        AdrIdx = gpioExic_irq_conf[i].arduino_id;
        ptEXIC = __GetEXICx_byGPIOx( g_APinDescription[AdrIdx].ulPort ) ;

        if( ( MEXIC_PX == ptEXIC  )
        	&&(  0 != (pEXIC_PF & g_APinDescription[AdrIdx].GioPin) ) )
        {
            if( ( NULL != gpioExic_irq_conf[i].callback )  )
            {
                gpioExic_irq_conf[i].callback(  );
            }
            MID_EXIC_ClearITFlag( MEXIC_PX , g_APinDescription[AdrIdx].GioPin );
        }
    }

    __DRV_EXIC_CLEAR_PINTRIGGER_EVENTFLAG( MEXIC_PX, pEXIC_PF );         
    MID_EXIC_ClearITFlag( MEXIC_PX , pEXIC_PF );
}


/**
 ********************************************************************************
 * @brief	    This function mapping the port to IRQn
 * @param port: one of the gpio port
 * @return      IRQn_Type
 * @exceptBion  No
 * @note        No
 ********************************************************************************
 */
static IRQn_Type  getIrqn_byPort( GPIO_Struct *port )
{
	  switch( (uint32_t)port )
	  {
	  	    case (uint32_t)GPIOA:
	  	      return ( EXINT0_IRQn );
	  	    	break;
	  	    	
	  	    case (uint32_t)GPIOB:
	  	      return ( EXINT1_IRQn );
	  	    	break;
	  	    	
	  	    case (uint32_t)GPIOC:
	  	      return ( EXINT2_IRQn );
	  	    	break;

	  	    case (uint32_t)GPIOD:
	  	      return ( EXINT3_IRQn );
	  	    	break;
	  	    	
#if defined(EXIC_PE_Base)
	  	    case (uint32_t)GPIOE:
	  	      return ( EXINT3_IRQn );
	  	    	break;
#endif
	  	    default:
	  	    	return  (IRQn_Type)(-1);
	  	    	break;
	  }
	  
	  return  (IRQn_Type)(0);
}
 
/**
********************************************************************************
* @brief	    This function enable the interruption on the selected port
* @param port: one of the gpio port
* @return      None
* @exceptBion  No
* @note        No
********************************************************************************
*/
void megawin_ExicInterruptEnablePort( GPIO_Struct *port )
{
    IRQn_Type irqnT;

    irqnT  = getIrqn_byPort ( port );
    MID_NVIC_EnableIRQ( irqnT );
}

/**
 ********************************************************************************
 * @brief	      This function set the interruption by one configured pin struct  
 * @param idx:  configned struct index
 * @return      None
 * @exceptBion  No
 * @note        No
 ********************************************************************************
 */
static void  megawin_PinInterruptSet(  uint16_t  ExcIdx )
{
    uint32_t it_mode;
        
    Pin_Struct*  pPinx;	
    uint16_t  AdrIdx;
    GPIO_InitTypeDef    PINX_InitStruct;

    EXIC_HandleTypeDef *ptEXIC;
    
    AdrIdx = gpioExic_irq_conf[ExcIdx].arduino_id;
    ptEXIC   = __GetEXICx_byGPIOx( g_APinDescription[AdrIdx].ulPort ) ;


    // Set AND mask = 0x03 ( If Px0 & Px1 trigger event happen at the same time , into interrupt. 
    //This code use or mode
    //ptEXIC->AND_Mask    = (ptEXIC->AND_Mask | g_APinDescription[AdrIdx].GioPin ); 

    // Set OR mask.
    ptEXIC->OR_Mask     = (ptEXIC->OR_Mask | g_APinDescription[AdrIdx].GioPin ); 
    

    PINX_InitStruct.Pin            = ptEXIC->OR_Mask;
    PINX_InitStruct.Mode           = GPIO_MODE_OPENDRAIN_O;
    PINX_InitStruct.Pull           = GPIO_PULLUP;
    PINX_InitStruct.Speed          = GPIO_SPEED_LOW;
    PINX_InitStruct.OUTDrive       = GPIO_OUTDRIVE_LEVEL0;
    PINX_InitStruct.FilterDivider  = GPIO_FILTERDIVIDER_BYPASS;
    
    
    PINX_InitStruct.Inverse        = GPIO_INVERSE_DISABLE;

    //这里没有使用电平模式
    switch( gpioExic_irq_conf[ExcIdx].mode )
    {
        case CHANGE :
            it_mode = EXIC_TRIGGER_DUAL_EDGE;
            break;

        case FALLING :
        case LOW :
            it_mode = EXIC_TRIGGER_EDGE;
            break;
            
        case RISING :
        case HIGH :
            it_mode = EXIC_TRIGGER_EDGE;
            PINX_InitStruct.Inverse   = GPIO_INVERSE_ENABLE;
            break;
            
        default:
            it_mode = EXIC_TRIGGER_DUAL_EDGE;
            break;
    }


    //这里必须为0
//    PINX_InitStruct.Alternate      = g_APinDescription[AdrIdx].afs;
    PINX_InitStruct.Alternate      = 0;

    if( ((uint32_t)-1) == gpioExic_irq_conf[ExcIdx].arduino_id )
    {
        return;
    }
    
    AdrIdx = gpioExic_irq_conf[ExcIdx].arduino_id;
    if( NULL == g_APinDescription[AdrIdx].ulPort )
    {
        return;
    }

    pPinx = __GetPinxx_byGPIOx( g_APinDescription[AdrIdx].ulPort, g_APinDescription[AdrIdx].PinNum );
    MID_GPIO_Pin_Init( pPinx , &PINX_InitStruct );
    MID_EXIC_PxTrigger_Init( ptEXIC );

    //==============================================================================
    //GPIO Trigger event Inital :
    MID_EXIC_PxTriggerMode_Config( ptEXIC,  gpioExic_irq_conf[ExcIdx].exic_trgs,  it_mode ); 
    
    gpioExic_irq_conf[ExcIdx].configured = 1;

    //==============================================================================
    //Enable NVIC IRQ :
    //You can :
    //    1. Tick IRQ handler checkbox of MG32x02z_ChipInit_Wizard and Tick Enable EXINT0 NVIC of
    //       MG32x02z_IRQ_Handler in Run-Time Environment.
    //    or    
    //    2. Use NVIC_EnableIRQ() to enable.
    //   MID_NVIC_SetPriority( gpioExic_irq_conf[i].irqnb,  0x00 );   //be called by ChipInit() in MG32x02z_ChipInit.c
    MID_NVIC_EnableIRQ( g_APinDescription[AdrIdx].IO_irqnb );
}
 

/**
 ********************************************************************************
 * @brief	    This function set the interruption on the selected port/pin 
 * @param port: one of the gpio port
 * @param pin : one of the gpio pin
 * @param callback: callback function
 * @param mode : interruption mode
 * @return      None
 * @exceptBion  No
 * @note        No
 ********************************************************************************
 */
void megawin_ExicInterruptSet(  uint16_t  AdrIdx,  void (*callback)(void),    uint32_t mode)
{
    uint16_t i;

    uint16_t pinNum;

    pinNum = g_APinDescription[AdrIdx].PinNum;

    //first  search， Have any configured pin.
    for(i=0; i< (sizeof(gpioExic_irq_conf)/sizeof(gpio_irq_conf_str));  i++ )
    {
        if( ( 0 != gpioExic_irq_conf[i].configured  )
         && (AdrIdx == gpioExic_irq_conf[i].arduino_id) )
        {
        	  gpioExic_irq_conf[i].callback = callback;
        	  gpioExic_irq_conf[i].exic_trgs = (0x00000001 << (pinNum*2));
        	  gpioExic_irq_conf[i].mode     = mode;
        	  megawin_PinInterruptSet( i );
        	  gpioExic_irq_conf[i].configured = 1;
        	  return;
        }
    }
    
    //find blank item to config
    for(i=0; i< (sizeof(gpioExic_irq_conf)/sizeof(gpio_irq_conf_str));  i++ )
    {
        if( ( 0 == gpioExic_irq_conf[i].configured  ) )
        {
            gpioExic_irq_conf[i].arduino_id = AdrIdx;
            gpioExic_irq_conf[i].callback = callback;
            gpioExic_irq_conf[i].exic_trgs = (0x00000001 << (pinNum*2));
            gpioExic_irq_conf[i].mode     = mode;

            megawin_PinInterruptSet( i );
            gpioExic_irq_conf[i].configured = 1;
            break;
        }
    }
}
/**
 ********************************************************************************
 * @brief	    This function disable the interruption on the selected port/pin
 * @param port: one of the gpio port
 * @param pin : one of the gpio pin
 * @return      None
 * @exceptBion  No
 * @note        No
 ********************************************************************************
 */
void megawin_ExicInterruptDisable(  uint16_t  AdrIdx  )
{
    uint16_t i;
    
    EXIC_HandleTypeDef *ptEXIC;

   
    ptEXIC   = __GetEXICx_byGPIOx( g_APinDescription[AdrIdx].ulPort ) ;
    ptEXIC->OR_Mask  = (ptEXIC->OR_Mask & (~g_APinDescription[AdrIdx].GioPin) );
    ptEXIC->AND_Mask = (ptEXIC->AND_Mask & (~g_APinDescription[AdrIdx].GioPin) );

    if( 0 == ptEXIC->OR_Mask )
    {
        MID_NVIC_DisableIRQ( g_APinDescription[AdrIdx].IO_irqnb );
    }

    for(i=0; i< (sizeof(gpioExic_irq_conf)/sizeof(gpio_irq_conf_str));  i++ )
    {
        if( 0 != gpioExic_irq_conf[i].configured )
        {
            if( AdrIdx == gpioExic_irq_conf[i].arduino_id  )
            {
                gpioExic_irq_conf[i].configured = 0;
            }
        }
    }
}



/**
 *******************************************************************************
 * @brief	    EXIC Init code.
 * @details     
 * @return      
 * @exception   No
 * @note        No
 *******************************************************************************
 */
void Megawin_EXIC_Init(void)
{
    uint16_t  i;
    
    NVIC_DisableIRQ ( EXINT0_IRQn );
    NVIC_DisableIRQ ( EXINT1_IRQn );
    NVIC_DisableIRQ ( EXINT2_IRQn );
    NVIC_DisableIRQ ( EXINT3_IRQn );    
    
    mEXIC_PA.Instance    = EXIC_PA;
    mEXIC_PA.AND_Mask    = 0x0000;                  // clear AND mask. 
    mEXIC_PA.OR_Mask     = 0x0000;                  // clear OR mask. 
    mEXIC_PA.AND_UnMatch = DISABLE;                 // Disable AND flag status inverse. 
    mEXIC_PA.Interrupt   = EXIC_INTERRUPT_ENABLE;   // Enable Interrupt.
    
    mEXIC_PB.Instance    = EXIC_PB;
    mEXIC_PB.AND_Mask    = 0x0000;                  // clear AND mask. 
    mEXIC_PB.OR_Mask     = 0x0000;                  // clear OR mask. 
    mEXIC_PB.AND_UnMatch = DISABLE;                 // Disable AND flag status inverse. 
    mEXIC_PB.Interrupt   = EXIC_INTERRUPT_ENABLE;   // Enable Interrupt.

    mEXIC_PC.Instance    = EXIC_PC;    
    mEXIC_PC.AND_Mask    = 0x0000;                  // clear AND mask. 
    mEXIC_PC.OR_Mask     = 0x0000;                  // clear OR mask. 
    mEXIC_PC.AND_UnMatch = DISABLE;                 // Disable AND flag status inverse. 
    mEXIC_PC.Interrupt   = EXIC_INTERRUPT_ENABLE;   // Enable Interrupt.

    mEXIC_PD.Instance    = EXIC_PD;
    mEXIC_PD.AND_Mask    = 0x0000;                  // clear AND mask. 
    mEXIC_PD.OR_Mask     = 0x0000;                  // clear OR mask. 
    mEXIC_PD.AND_UnMatch = DISABLE;                 // Disable AND flag status inverse. 
    mEXIC_PD.Interrupt   = EXIC_INTERRUPT_ENABLE;   // Enable Interrupt.

    #if defined(EXIC_PE_Base)
    mEXIC_PE.Instance    = EXIC_PE;
    mEXIC_PE.AND_Mask    = 0x0000;                  // clear AND mask. 
    mEXIC_PE.OR_Mask     = 0x0000;                  // clear OR mask. 
    mEXIC_PE.AND_UnMatch = DISABLE;                 // Disable AND flag status inverse. 
    mEXIC_PE.Interrupt   = EXIC_INTERRUPT_ENABLE;   // Enable Interrupt.
    #endif


    //==============================================================================
    //GPIO Trigger event Inital :
    for(i=0; i<  NB_EXTCI;  i++ )
    {
        gpioExic_irq_conf[i].arduino_id = -1;
        gpioExic_irq_conf[i].exic_trgs  = 0;
        gpioExic_irq_conf[i].callback = NULL;
        gpioExic_irq_conf[i].mode = EXIC_TRIGGER_EDGE;
        gpioExic_irq_conf[i].configured = 0;
    }
}


#ifdef __cplusplus
}
#endif



/*********COPYRIGHT(c) 2022 megawin Technology Co., Ltd *****END OF FILE****/

