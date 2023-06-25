

/**
 ******************************************************************************
 *
 * @file        MG32x02z_GPIO_DRV.c
 * @brief       The code is GPIO driver C file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.12
 * @date        2021/09/07
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



#include "MG32x02z_GPIO_DRV.h"


/**
 * @name	Mode
 *   		GPIO mode relationship configuration.
 */ 
///@{
/**
 *******************************************************************************
 * @brief       Single PIN configuration.
 * @details  
 * @param[in]   PINX:  
 * @param[in]   PINX_InitStruct:
 *  @arg\b      PINX_Pin: (PX_Pin_0 ~ PX_Pin_15).
 *  @arg\b      PINX_Mode:
 *      \n      -PINX_Mode_Analog_IO
 *      \n      -PINX_Mode_OpenDrain_O:
 *      \n      -PINX_Mode_PushPull_O:
 *      \n      -PINX_Mode_Digital_I:
 *      \n      -PINX_Mode_Quasi_IO:
 *  @arg\b      PINX_Speed:  (for PC0 ~ PC3 , PD0 ~ PD3 only)
 *      \n      -PINX_Speed_Low:
 *      \n      -PINX_Speed_High:
 *  @arg\b      PINX_PUResistant:
 *      \n      -PINX_PUResistant_Disable:
 *      \n      -PINX_PUResistant_Enable:
 *  @arg\b      PINX_Inverse:
 *      \n      -PINX_Inverse_Disable:
 *      \n      -PINX_Inverse_Enable:
 *  @arg\b      PINX_OUTDrive:
 *      \n      -PINX_OUTDrive_Level0:
 *      \n      -PINX_OUTDrive_Level1: (for PE0 ~ PE3 only )
 *      \n      -PINX_OUTDrive_Level2:
 *      \n      -PINX_OUTDrive_Level3: (for PE0 ~ PE3 only )
 *  @arg\b      PINX_FilterDivider
 *      \n      -PINX_FilterDivider_Bypass:
 *      \n      -PINX_FilterDivider_1:
 *      \n      -PINX_FilterDivider_4:
 *      \n      -PINX_FilterDivider_16:
 *  @arg\b      PINX_Alternate_Function: 
 *      \n      -GPIO is 0
 *      \n      -Reset function is 1 (for PC6 only)
 *      \n      -OCD function is 1 (for PC4 , PC5 only)
 *      \n      -XTAL function is 5 (for PC13 , PC14 only)
 *      \n      -The other function refer to datasheet.
 * @return      
 * @exception   No
 * @note        
 * @par         Example
 * @code
    PIN_InitTypeDef PINX_InitStruct;
 
    PINX_InitStruct.PINX_Mode				= PINX_Mode_OpenDrain_O;
    PINX_InitStruct.PINX_PUResistant        = PINX_PUResistant_Enable;
    PINX_InitStruct.PINX_Speed              = PINX_Speed_Low;
    PINX_InitStruct.PINX_OUTDrive           = PINX_OUTDrive_Level0;
    PINX_InitStruct.PINX_FilterDivider      = PINX_FilterDivider_Bypass;
    PINX_InitStruct.PINX_Inverse            = PINX_Inverse_Disable;
    PINX_InitStruct.PINX_Alternate_Function = 0;
    GPIO_PinMode_Config(PINB(10),&PINX_InitStruct);
  * @endcode
 *******************************************************************************
 */
void GPIO_PinMode_Config(Pin_Struct* PINX , PIN_InitTypeDef* PINX_InitStruct)
{
    PINX->CR.W = (uint32_t)(PINX_InitStruct->PINX_Mode)                   | 
                 (uint32_t)(PINX_InitStruct->PINX_Speed)                  | 
                 (uint32_t)(PINX_InitStruct->PINX_PUResistant)            | 
                 (uint32_t)(PINX_InitStruct->PINX_Inverse)                |
                 (uint32_t)(PINX_InitStruct->PINX_OUTDrive)               | 
                 (uint32_t)(PINX_InitStruct->PINX_FilterDivider)          |
                 (uint32_t)(PINX_InitStruct->PINX_Alternate_Function<<12) |
                 (uint32_t)(PX_CR_LCK_mask_w);
                 
}

/**
 *******************************************************************************
 * @brief       PIN configuration in the same port.
 * @details  
 * @param[in]   IOMX : X is port (A ~ E).
 * @param[in]   PINX_InitStruct:
 *  @arg\b      PINX_Pin: (PX_Pin_0 ~ PX_Pin_15).
 *  @arg\b      PINX_Mode:
 *      \n      -PINX_Mode_Analog_IO
 *      \n      -PINX_Mode_OpenDrain_O:
 *      \n      -PINX_Mode_PushPull_O:
 *      \n      -PINX_Mode_Digital_I:
 *      \n      -PINX_Mode_Quasi_IO:
 *  @arg\b      PINX_Speed:  (for PC0 ~ PC3 , PD0 ~ PD3 only)
 *      \n      -PINX_Speed_Low:
 *      \n      -PINX_Speed_High:
 *  @arg\b      PINX_PUResistant:
 *      \n      -PINX_PUResistant_Disable:
 *      \n      -PINX_PUResistant_Enable:
 *  @arg\b      PINX_Inverse:
 *      \n      -PINX_Inverse_Disable:
 *      \n      -PINX_Inverse_Enable:
 *  @arg\b      PINX_OUTDrive:
 *      \n      -PINX_OUTDrive_Level0:
 *      \n      -PINX_OUTDrive_Level1: (for PE0 ~ PE3 only )
 *      \n      -PINX_OUTDrive_Level2:
 *      \n      -PINX_OUTDrive_Level3: (for PE0 ~ PE3 only )
 *  @arg\b      PINX_FilterDivider
 *      \n      -PINX_FilterDivider_Bypass:
 *      \n      -PINX_FilterDivider_1:
 *      \n      -PINX_FilterDivider_4:
 *      \n      -PINX_FilterDivider_16:
 *  @arg\b      PINX_Alternate_Function: 
 *      \n      -GPIO is 0
 *      \n      -Reset function is 1 (for PC6 only)
 *      \n      -OCD function is 1 (for PC4 , PC5 only)
 *      \n      -XTAL function is 5 (for PC13 , PC14 only)
 *      \n      -The other function refer to datasheet.
 * @return      
 * @exception   No 
 * @note        
 * @par         Examplt
 * @code
    PIN_InitTypeDef PINX_InitStruct;
 
    PINX_InitStruct.PINX_Pin                = (PX_Pin_0 | PX_Pin_1);
    PINX_InitStruct.PINX_Mode				= PINX_Mode_OpenDrain_O;
    PINX_InitStruct.PINX_PUResistant        = PINX_PUResistant_Enable;
    PINX_InitStruct.PINX_Speed              = PINX_Speed_Low;
    PINX_InitStruct.PINX_OUTDrive           = PINX_OUTDrive_Level0;
    PINX_InitStruct.PINX_FilterDivider      = PINX_FilterDivider_Bypass;
    PINX_InitStruct.PINX_Inverse            = PINX_Inverse_Disable;
    PINX_InitStruct.PINX_Alternate_Function = 0;
    GPIO_PortMode_Config(IOMA,&PINX_InitStruct);
  * @endcode
 *******************************************************************************
 */
void GPIO_PortMode_Config(IOM_Struct* IOMX, PIN_InitTypeDef* PINX_InitStruct)
{
	uint32_t pin_pos = 0 , nowpin = 0x00000001;
    uint32_t set_pin = PINX_InitStruct->PINX_Pin;
    
    while(set_pin!=0)
    {
        if((PINX_InitStruct->PINX_Pin & nowpin)==nowpin)
		{
            *((volatile uint32_t*)((uint32_t)IOMX + 0x04*pin_pos)) = (uint32_t)(PINX_InitStruct->PINX_Mode)                   |
                                                                     (uint32_t)(PINX_InitStruct->PINX_Speed)                  |
                                                                     (uint32_t)(PINX_InitStruct->PINX_PUResistant)            |
                                                                     (uint32_t)(PINX_InitStruct->PINX_Inverse)                |
                                                                     (uint32_t)(PINX_InitStruct->PINX_OUTDrive)               |
                                                                     (uint32_t)(PINX_InitStruct->PINX_FilterDivider)          |
                                                                     (uint32_t)(PINX_InitStruct->PINX_Alternate_Function<<12) |
                                                                     (uint32_t)(PX_CR_LCK_mask_w);

            set_pin = set_pin & (~nowpin);
        }
        pin_pos = pin_pos + 1;
        nowpin = nowpin << 1;
    }
}



/**
 *******************************************************************************
 * @brief       Pin mode control.
 * @details  
 * @param[in]   PINX: 
 * @param[in]   Pin_Mode:
 *  @arg\b      PINX_Mode_Analog_IO:
 *  @arg\b      PINX_Mode_OpenDrain_O:
 *  @arg\b      PINX_Mode_PushPull_O:
 *  @arg\b      PINX_Mode_Digital_I:
 *  @arg\b      PINX_Mode_Quasi_IO:
 * @return      
 * @exception   No  
 * @note        
 * @par         Example
 * @code
    GPIO_PinMode_Select(PINA(0),PINX_Mode_OpenDrain_O);
 * @endcode
 *******************************************************************************
 */
void GPIO_PinMode_Select(Pin_Struct* PINX , PINX_Mode_TypeDef Pin_Mode)
{
    PINX->CR.W = PINX->CR.W & (~PX_CR_IOM_mask_w);
    PINX->CR.W = PINX->CR.MBIT.IOM | Pin_Mode;
}


/**
 *******************************************************************************
 * @brief       Enable or disable pin output high speed.
 * @details  
 * @param[in]   PINX: 
 * @param[in]   Pin_HSMode: (only PC0 ~ PC3 , PD0 ~ PD3)
 *  @arg\b      DISABLE: Output high speed disable.
 *  @arg\b      ENABLE:  Output high speed enable.
 * @return      
 * @exception   No 
 * @note        
 * @par         Example
 * @code
    GPIO_PinHighSpeedMode_Cmd(PINA(0),ENABLE);
 * @endcode
 *******************************************************************************
 */
void GPIO_PinHighSpeedMode_Cmd(Pin_Struct* PINX , FunctionalState Pin_HSMode)
{
    PINX->CR.MBIT.HS = Pin_HSMode;
}
/**
 *******************************************************************************
 * @brief       Enable or disable internal pull up resister.
 * @details  
 * @param[in]   PINX:  
 * @param[in]   Pin_PUR:
 *  @arg\b      DISABLE: Internal pull up resister disable.
 *  @arg\b      ENABLE:  Internal pull up resister enable.
 * @return      
 * @exception   No 
 * @note        
 * @par         Example
 * @code
    GPIO_PinPUResister_Cmd(PINA(0),ENABLE);
 * @endcode
 *******************************************************************************
 */
void GPIO_PinPUResister_Cmd(Pin_Struct* PINX , FunctionalState Pin_PUR)
{
    PINX->CR.MBIT.PU = Pin_PUR;
}
/**
 *******************************************************************************
 * @brief       Enable or disable input inverse.
 * @details  
 * @param[in]   PINX:  
 * @param[in]   Pin_INV:
 *  @arg\b      DISABLE: Input inverse disable.
 *  @arg\b      ENABLE:  Input inverse enable.
 * @return      
 * @exception   No   
 * @note        
 * @par         Example
 * @code
    GPIO_PinInverse_Cmd(PINA(0),ENABLE);
 * @endcode
 *******************************************************************************
 */
void GPIO_PinInverse_Cmd(Pin_Struct* PINX, FunctionalState Pin_INV)
{
    PINX->CR.MBIT.INV = Pin_INV;
}
/**
 *******************************************************************************
 * @brief       Select output drive strength.
 * @details  
 * @param[in]   PINX:  
 * @param[in]   Pin_ODC:
 *  @arg\b      PINX_OUTDrive_Level0: 
 *  @arg\b      PINX_OUTDrive_Level1: (only PE0 ~ PE3)
 *  @arg\b      PINX_OUTDrive_Level2: 
 *  @arg\b      PINX_OUTDrive_Level3: (only PE0 ~ PE3)
 * @return      
 * @exception   No  
 * @note        
 * @par         Example
 * @code
    GPIO_PinOutputDrive_Select(PINA(0),PINX_OUTDrive_Level0);
 * @endcode
 *******************************************************************************
 */
void GPIO_PinOutputDrive_Select(Pin_Struct* PINX , PINX_OUTDrive_Typedef Pin_ODC)
{
    PINX->CR.W = PINX->CR.W & (~PX_CR_ODC_mask_w);
    PINX->CR.W = PINX->CR.W | Pin_ODC;
}
/**
 *******************************************************************************
 * @brief       Select input filter divider.
 * @details  
 * @param[in]   PINX:  
 * @param[in]   Pin_FDIV:
 *  @arg\b      PINX_FilterDivider_Bypass: No filter.
 *  @arg\b      PINX_FilterDivider_1: 1 filter clock.
 *  @arg\b      PINX_FilterDivider_4: 4 filter clock.
 *  @arg\b      PINX_FilterDivider_16: 16 filter clock. 
 * @return      
 * @exception   No   
 * @note        
 * @par         Example
 * @code
    GPIO_PinInFilterDivider_Select(PINA(0),PINX_FilterDivider_Bypass);
 * @endcode
 *******************************************************************************
 */
void GPIO_PinInFilterDivider_Select(Pin_Struct* PINX , PINX_FilterDiver_Typedef Pin_FDIV)
{
    PINX->CR.W = PINX->CR.W & (~PX_CR_FDIV_mask_w);
    PINX->CR.W = PINX->CR.W | Pin_FDIV;
}
/**
 *******************************************************************************
 * @brief       Select pin alternate function.
 * @details  
 * @param[in]   PINX: 
 * @param[in]   Pin_Func: (please to refer datasheet.)
 *  @arg\b      0: GPIO.
 *  @arg\b      The_other_value: refer to datasheet. 
 * @return      
 * @exception   No   
 * @note        
 * @par         Example
 * @code
    GPIO_PinFunction_Select(PINA(0),0);
 * @endcode
 *******************************************************************************
 */
void GPIO_PinFunction_Select(Pin_Struct* PINX , uint8_t Pin_Func)
{
    uint32_t tmp;

    tmp = PINX->CR.W & (~PX_CR_AFS_mask_w);
    tmp = tmp | (uint32_t) (Pin_Func << 12) | PX_CR_LCK_mask_w;
    PINX->CR.W = tmp;
    
}

/**
 *******************************************************************************
 * @brief       Read port status function.
 * @details  
 * @param[in]   IOMX: (IOMA ~ IOME)
 * @param[in]   FCKS:
 *  @arg\b      GPIO_FT_CLK_AHB     : AHB.
 *  @arg\b      GPIO_FT_CLK_AHB_DIV8: AHB / 8.
 *  @arg\b      GPIO_FT_CLK_ILRCO   : ILRCO.
 *  @arg\b      GPIO_FT_TM00_TRGO   : Timer00 overflow
 *  @arg\b      GPIO_FT_CK_UT       : CK_UT.
 * @return      
 * @exception   No 
 * @note        
 * @par         Example
 * @code
    GPIO_PortFilterClockSource_Select(IOMA,GPIO_FT_CLK_AHB);
 * @endcode
 *******************************************************************************
 */
void GPIO_PortFilterClockSource_Select(IOM_Struct* IOMX , PortFilterCLK_Typedef FCKS)
{
    IOMX->FLT.MBIT.FCKS = FCKS;
    
}


///@}


/**
 * @name	Read / Write
 *   		Pin or Port read / write relationship function.
 */ 
///@{
/**
 *******************************************************************************
 * @brief       Write port function.
 * @details  
 * @param[in]   GPIOX: (GPIOA ~ GPIOE).
 * @param[in]   Port_Status: (0x0000 ~ 0xFFFF).
 * @return      
 * @exception   No  
 * @note        
 * @par         Example
 * @code
    GPIO_WritePort(GPIOA,0x0000);
 * @endcode
 *******************************************************************************
 */
void GPIO_WritePort(GPIO_Struct* GPIOX, uint16_t Port_Status)
{
	GPIOX->OUT.W = Port_Status;	
}	


/**
 *******************************************************************************
 * @brief       Read port status function.
 * @details  
 * @param[in]   GPIOX: (GPIOA ~ GPIOE).
 * @return      Port status.
 * @exception   No  
 * @note        
 * @par         Example
 * @code
    GPIO_ReadPort(GPIOA);
 * @endcode
 *******************************************************************************
 */
uint16_t GPIO_ReadPort(GPIO_Struct* GPIOX)
{
    return(GPIOX->IN.H[0]);
}




/**
 *******************************************************************************
 * @brief       Set designate bits of port.
 * @details  
 * @param[in]   GPIOX: (GPIOA ~ GPIOE).
 * @param[in]   Set_Pin:
 * @return      
 * @exception   No 
 * @note        
 * @par         Example
 * @code
    GPIO_SetPortBit(GPIOA,(PX_Pin_0|PX_Pin_1);
 * @endcode
 *******************************************************************************
 */
void GPIO_SetPortBit(GPIO_Struct* GPIOX , uint16_t Set_Pin)
{
    GPIOX->SC.H[0] = Set_Pin;
}

/**
 *******************************************************************************
 * @brief       Clear designate bit of port.
 * @details  
 * @param[in]   GPIOX: (GPIOA ~ GPIOE).
 * @param[in]   Clear_Pin:
 * @return      
 * @exception   No  
 * @note        
 * @par         Example
 * @code
    GPIO_ClearPortBit(GPIOA,(PX_Pin_0|PX_Pin_1);
 * @endcode
 *******************************************************************************
 */
void GPIO_ClearPortBit(GPIO_Struct* GPIOX , uint16_t Clear_Pin)
{
    GPIOX->SC.H[1] = Clear_Pin;
}


/**
 *******************************************************************************
 * @brief       Clear and set designate bit of port at the same time.
 * @details  
 * @param[in]   GPIOX: (GPIOA ~ GPIOE).
 * @param[in]   Set_Pin: designate set pin in GPIOX
 * @param[in]   Clr_Pin: designate clear pin in GPIOX
 * @return      
 * @exception   No  
 * @note        If the same pin is set and clr , set is priority. 
 * @par         Example
 * @code
    GPIO_SetClearPortBit(GPIOA,PX_Pin_0,PX_Pin_1);
 * @endcode
 *******************************************************************************
 */

void GPIO_SetClearPortBit(GPIO_Struct* GPIOX, uint16_t Set_Pin , uint16_t Clr_Pin)
{
    
    GPIOX->SC.W =  (((uint32_t)(Clr_Pin<<16) & 0xFFFF0000) | Set_Pin);
    
}

///@}








































