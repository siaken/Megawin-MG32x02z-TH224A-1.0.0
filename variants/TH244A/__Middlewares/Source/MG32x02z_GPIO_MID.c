


 /**
 ******************************************************************************
 *
 * @file        MG32x02z_GPIO_MID.c
 * @brief       The code GPIO middleware C file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.01
 * @date        2022/06/15
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 * 
 ******************************************************************************* 
 * @par Disclaimer
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
 
 
 
#include "MG32x02z_GPIO_MID.h"
#include "MG32x02z_CFG.h"
 
 
 
/**
 *******************************************************************************
 * @brief	    Initialize the PINX peripheral according to the specified parameters 
 *     \n       in the GPIOPin_Init.
 * @details     
 * @param[in]   PINX      : where x can be ( PINA(0) ~ PINE(15) ) to select the Pin peripheral. 
 * @param[in]   PIN_Init  : pointer to a GPIO_InitTypeDef structure that contains
 *       \n                 the configuration information for the specified GPIO
 *       \n                 peripheral. 
 *   @arg\b     Mode : 
 *       \n     - GPIO_MODE_DIGITAL_I  : Digital input
 *       \n     - GPIO_MODE_PUSHPULL_O : Push pull output.
 *       \n     - GPIO_MODE_OPENDRAIN_O: Open drain output.
 *       \n     - GPIO_MODE_QUASI_IO   : Quasi-bidirection output.
 *       \n     - GPIO_MODE_ANALOG_IO  : Analog IO.
 *   @arg\b     Pull :
 *       \n     - GPIO_NOPULLUP: Pull up resister disable.
 *       \n     - GPIO_PULLUP  : Pull up resister enable.
 *   @arg\b     Speed :
 *       \n     - GPIO_SPEED_LOW  : Output high speed mode disable.
 *       \n     - GPIO_SPEED_HIGH : Output high speed mode enable.
 *   @arg\b     Inverse :
 *       \n     - GPIO_INVERSE_DISABLE : input inverse disable.
 *       \n     - GPIO_INVERSE_ENABLE  : input inverse enable.
 *   @arg\b     OUTDrive :
 *       \n     - GPIO_OUTDRIVE_LEVEL0 : Drive strength-Full
 *       \n     - GPIO_OUTDRIVE_LEVEL1 : Drive strength-1/2   (no any pin have the setting)
 *       \n     - GPIO_OUTDRIVE_LEVEL2 : Drive strength 1/4
 *       \n     - GPIO_OUTDRIVE_LEVEL3 : Drive strength-1/8   (No any pin have the setting)
 *   @arg\b     FilterDivider :
 *       \n     - GPIO_FILTERDIVIDER_BYPASS : input bypass filterASS0
 *       \n     - GPIO_FILTERDIVIDER_1      : input filter clock divided by 1.
 *       \n     - GPIO_FILTERDIVIDER_4      : input filter clock divided by 4.
 *       \n     - GPIO_FILTERDIVIDER_16     : input filter clock divided by 16.
 *   @arg\b     Alternate : (refer to datasheet)
 * @return      
 * @exception   No
 * @note        No
 * @par         Example
 * @code
    GPIO_InitTypeDef    GPIOX;
 
    GPIOX.Mode          = GPIO_MODE_QUASI_IO;
    GPIOX.Pull          = GPIO_PULLUP;
    GPIOX.Speed         = GPIO_SPEED_LOW;
    GPIOX.Inverse       = GPIO_INVERSE_DISABLE;
    GPIOX.OUTDrive      = GPIO_OUTDRIVE_LEVEL0;
    GPIOX.FilterDivider = GPIO_FILTERDIVIDER_BYPASS;
    GPIOX.Alternate     = 0;                            // 0 = GPIO mode.
    MID_GPIO_Pin_Init( PINC(10),&GPIOX); 
 * @endcode      
 *******************************************************************************
 */
void MID_GPIO_Pin_Init( Pin_Struct* PINX , GPIO_InitTypeDef* PIN_Init)
{
	PINX->CR.W = (PIN_Init->Mode           | PIN_Init->Speed        | 
				  PIN_Init->Pull           | PIN_Init->Inverse      |
	              PIN_Init->OUTDrive       | PIN_Init->FilterDivider|
	              (PIN_Init->Alternate<<12)| PX_CR_LCK_mask_w);        
}
/**
 *******************************************************************************
 * @brief	    Initialize the IOMx peripheral according to the specified parameters 
 *     \n       in the GPIO_Init.
 * @details     
 * @param[in]   IOMx      : where x can be ( A..E) to select the GPIO peripheral. 
 * @param[in]   GPIO_Init : pointer to a GPIO_InitTypeDef structure that contains
 *       \n                 the configuration information for the specified GPIO
 *       \n                 peripheral.
 *   @arg\b     Pin  : (GPIO_Pin_0 ~ GPIO_Pin_15 ).
 *   @arg\b     Mode : 
 *       \n     - GPIO_MODE_DIGITAL_I  : Digital input
 *       \n     - GPIO_MODE_PUSHPULL_O : Push pull output.
 *       \n     - GPIO_MODE_OPENDRAIN_O: Open drain output.
 *       \n     - GPIO_MODE_QUASI_IO   : Quasi-bidirection output.
 *       \n     - GPIO_MODE_ANALOG_IO  : Analog IO.
 *   @arg\b     Pull :
 *       \n     - GPIO_NOPULLUP: Pull up resister disable.
 *       \n     - GPIO_PULLUP  : Pull up resister enable.
 *   @arg\b     Speed :
 *       \n     - GPIO_SPEED_LOW  : Output high speed mode disable.
 *       \n     - GPIO_SPEED_HIGH : Output high speed mode enable.
 *   @arg\b     Inverse :
 *       \n     - GPIO_INVERSE_DISABLE : input inverse disable.
 *       \n     - GPIO_INVERSE_ENABLE  : input inverse enable.
 *   @arg\b     OUTDrive :
 *       \n     - GPIO_OUTDRIVE_LEVEL0 : Drive strength-Full
 *       \n     - GPIO_OUTDRIVE_LEVEL1 : Drive strength-1/2   (no any pin have the setting)
 *       \n     - GPIO_OUTDRIVE_LEVEL2 : Drive strength 1/4
 *       \n     - GPIO_OUTDRIVE_LEVEL3 : Drive strength-1/8   (No any pin have the setting)
 *   @arg\b     FilterDivider :
 *       \n     - GPIO_FILTERDIVIDER_BYPASS : input bypass filterASS0
 *       \n     - GPIO_FILTERDIVIDER_1      : input filter clock divided by 1.
 *       \n     - GPIO_FILTERDIVIDER_4      : input filter clock divided by 4.
 *       \n     - GPIO_FILTERDIVIDER_16     : input filter clock divided by 16.
 *   @arg\b     Alternate : (refer to datasheet)
 * @return      
 * @exception   No
 * @note        No
 * @par         Example
 * @code
    GPIO_InitTypeDef    GPIOX;
 
    GPIOX.Pin           = ( GPIO_Pin_0 | GPIO_Pin_11);
    GPIOX.Mode          = GPIO_MODE_QUASI_IO;
    GPIOX.Pull          = GPIO_PULLUP;
    GPIOX.Speed         = GPIO_SPEED_LOW;
    GPIOX.Inverse       = GPIO_INVERSE_DISABLE;
    GPIOX.OUTDrive      = GPIO_OUTDRIVE_LEVEL0;
    GPIOX.FilterDivider = GPIO_FILTERDIVIDER_BYPASS;
    GPIOX.Alternate     = 0;                          // 0 = GPIO mode.
    MID_GPIO_Init( IOMC ,&GPIOX);  
 * @endcode  
 *******************************************************************************
 */
void MID_GPIO_Init( IOM_Struct* IOMx , GPIO_InitTypeDef *GPIO_Init)
{
	uint32_t pin_pos = 0; 
    uint32_t nowpin  = 0x00000001;
    uint32_t set_pin = GPIO_Init->Pin;
    
    while(set_pin!=0)
    {
        if((GPIO_Init->Pin & nowpin)==nowpin)
		{
            *((volatile uint32_t*)((uint32_t)IOMx + 0x04*pin_pos)) =    (GPIO_Init->Mode           | GPIO_Init->Speed        | 
																	     GPIO_Init->Pull           | GPIO_Init->Inverse      |
																	     GPIO_Init->OUTDrive       | GPIO_Init->FilterDivider|
																	    (GPIO_Init->Alternate<<12) | PX_CR_LCK_mask_w);
            set_pin = set_pin & (~nowpin);
        }
        pin_pos = pin_pos + 1;
        nowpin = nowpin << 1;
    }    
}
 /**
 *******************************************************************************
 * @brief	    De-initializes the GPIOx peripheral registers to their default 
 *     \n       reset values.
 * @details     
 * @param[in]   IOMx    : where x can be ( A..E) to select the GPIO peripheral. 
 * @param[in]   GPIO_Pin: specifies the port bit to be written.
 *     \n                 This parameter can be any balue of GPIO_pins_define
 * @return      MID status.
 * @exception   No
 * @note        No
 *******************************************************************************
 */ 
void MID_GPIO_DeInit( IOM_Struct* IOMx , uint32_t GPIO_Pin)
{
    uint32_t pin_pos = 0; 
    uint32_t nowpin  = 0x00000001;
    uint32_t set_pin = GPIO_Pin;
    uint32_t PINDeVaule;
    
    if( ((uint32_t)&IOMx->CR0.W) == IOMC_Base)
    {
        while(set_pin!=0)
        {
            if((GPIO_Pin & nowpin)==nowpin)
            {
                #if defined(CFG_OR05_PC_IOM_mask_w)
                    if((CFG->OR05.W & CFG_OR05_PC_IOM_mask_w) == CFG_OR05_PC_IOM_qb_w)
                    {
                        PINDeVaule = (PX_CR_LCK_mask_w | PX_CR_IOM_qb_w);
                    }
                    else
                    {
                        PINDeVaule = (PX_CR_LCK_mask_w | PX_CR_IOM_aio_w);
                    }
                #else
                    PINDeVaule = (PX_CR_LCK_mask_w | PX_CR_PU_enable_w | PX_CR_IOM_qb_w);
                #endif

                switch( nowpin)
                {
                    /*SWCLK , SWDIO*/
                    case GPIO_Pin_4:
                    case GPIO_Pin_5:
                                     PINDeVaule = (PX_CR_LCK_mask_w | PX_CR_PU_enable_w | PX_CR_IOM_qb_w);
                                     if((CFG->OR05.W & CFG_OR05_SWD_PIN_mask_w) ==  CFG_OR05_SWD_PIN_enable_w)
                                     {
                                         PINDeVaule = PINDeVaule | ( 1 << 12 );
                                     }
                                     break;
                    /*RSTN*/
                    case GPIO_Pin_6:
                                     PINDeVaule = (PX_CR_LCK_mask_w | PX_CR_PU_enable_w | PX_CR_IOM_qb_w);
                                     if((CFG->OR05.W & CFG_OR05_EXRST_PIN_mask_w) ==  CFG_OR05_EXRST_PIN_enable_w)
                                     {
                                         PINDeVaule = PINDeVaule | ( 1 << 12 );
                                     }
                                     break;
                    /*XIN , XOUT*/
                    case GPIO_Pin_13:
                    case GPIO_Pin_14:
                                     if((CFG->OR05.W & CFG_OR05_XOSC_EN_mask_w) ==  CFG_OR05_XOSC_EN_enable_w)
                                     {
                                         PINDeVaule = PINDeVaule | ( 1 << 12 );
                                     }
                                     break;
                    default:
                                     break;
                }
                
                *((volatile uint32_t*)((uint32_t)IOMx + 0x04*pin_pos)) =    PINDeVaule;
                
                set_pin = set_pin & (~nowpin);
            }
            pin_pos = pin_pos + 1;
            nowpin = nowpin << 1;
        }
    }
    else
    {
        while(set_pin!=0)
        {
            if((GPIO_Pin & nowpin)==nowpin)
	    	{
                *((volatile uint32_t*)((uint32_t)IOMx + 0x04*pin_pos)) =    0x00000000;
                set_pin = set_pin & (~nowpin);
            }
            pin_pos = pin_pos + 1;
            nowpin = nowpin << 1;
        }
    }
}












