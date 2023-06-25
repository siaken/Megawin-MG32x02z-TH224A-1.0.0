/**
 ******************************************************************************
 *
 * @file        MG32x02z_cortex_MID.c
 * @brief       CORTEX HAL module driver.
 *              This file provides firmware functions to manage the following
 *              functionalities of the CORTEX:
 *               + Initialization and de-initialization functions
 *               + Peripheral Control functions
 * @par         Project
 *              MG32x02z
 * @version     V1.00
 * @date        2019/09/25
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2019 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************
 * @par         Disclaimer 
 *              The Demo software is provided "AS IS"  without any warranty, either
 *              expressed or implied, including, but not limited to, the implied warranties
 *              of merchantability and fitness for a particular purpose.  The author will
 *              not be liable for any special, incidental, consequential or indirect
 *              damages due to loss of data or any other reason.
 *              These statements agree with the world wide and local dictated laws about
 *              authorship and violence against these laws.
 ******************************************************************************
 *  @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================

    [..]
    *** How to configure Interrupts using CORTEX MID driver ***
    ===========================================================
    [..]
    This section provides functions allowing to configure the NVIC interrupts (IRQ).
    The Cortex-M0 exceptions are managed by CMSIS functions.
      (#) Enable and Configure the priority of the selected IRQ Channels.
             The priority can be 0..3. 

        -@- Lower priority values gives higher priority.
        -@- Priority Order:
            (#@) Lowest priority.
            (#@) Lowest hardware priority (IRQn position).

      (#)  Configure the priority of the selected IRQ Channels using MID_NVIC_SetPriority()

      (#)  Enable the selected IRQ Channels using MID_NVIC_EnableIRQ()

      -@-  Negative value of IRQn_Type are not allowed.


    [..]
    *** How to configure Systick using CORTEX MID driver ***
    ========================================================
    [..]
    Setup SysTick Timer for time base. 

   (+) The MID_SYSTICK_Config()function calls the SysTick_Config() function which
       is a CMSIS function that:
        (++) Configures the SysTick Reload register with value passed as function parameter.
        (++) Configures the SysTick IRQ priority to the lowest value (0x03).
        (++) Resets the SysTick Counter register.
        (++) Configures the SysTick Counter clock source to be Core Clock Source (HCLK).
        (++) Enables the SysTick Interrupt.
        (++) Starts the SysTick Counter.
    
   (+) You can change the SysTick Clock source to be HCLK_Div8 by calling the macro
       MID_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8) just after the
       MID_SYSTICK_Config() function call. The MID_SYSTICK_CLKSourceConfig() macro is defined
       inside the MG32x02z_cortex_MID.h file.

   (+) You can change the SysTick IRQ priority by calling the
       MID_NVIC_SetPriority(SysTick_IRQn,...) function just after the MID_SYSTICK_Config() function
       call. The MID_NVIC_SetPriority() call the NVIC_SetPriority() function which is a CMSIS function.

   (+) To adjust the SysTick time base, use the following formula:

       Reload Value = SysTick Counter Clock (Hz) x  Desired Time base (s)
       (++) Reload Value is the parameter to be passed for MID_SYSTICK_Config() function
       (++) Reload Value should not exceed 0xFFFFFF

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2019 megawin Technology Co., Ltd.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of megawin Technology Co., Ltd. nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SMIDL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "MG32x02z_Common_MID.h"

/** @name  MG32x02z_Common_MID
  * @{
  */

/** @name  CORTEX CORTEX
  * @brief CORTEX CORTEX MID module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @name  CORTEX_Exported_Functions CORTEX Exported Functions
  * @{
  */


/** @name  CORTEX_Exported_Functions_Group1 Initialization and de-initialization functions 
 *  @brief Initialization and Configuration functions
 *
@verbatim
  ==============================================================================
              ##### Initialization and de-initialization functions #####
  ==============================================================================
    [..]
      This section provides the CORTEX MID driver functions allowing to configure Interrupts
      Systick functionalities 

@endverbatim
  * @{
  */

/**
 *******************************************************************************
 * @brief       Sets the priority of an interrupt.
 * @param[in]   IRQn External interrupt number .
 *              This parameter can be an enumerator of IRQn_Type enumeration
 *              (For the complete MG32 Devices IRQ Channels list, please refer to MG32x02z.h file)
 * @param[in]   PreemptPriority The preemption priority for the IRQn channel.
 *              This parameter can be a value between 0 and 3.
 *              A lower priority value indicates a higher priority
 * @return      None
 * @exception   None
 * @note        None
 * @par         Modify
 *              void MID_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority)
 *******************************************************************************
 */
void MID_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority)
{ 
    /* Check the parameters */
    assert_param(IS_NVIC_PREEMPTION_PRIORITY(PreemptPriority));
    NVIC_SetPriority(IRQn,PreemptPriority);
}



/**
 *******************************************************************************
 * @brief       Enables a device specific interrupt in the NVIC interrupt controller.
 * @param       IRQn External interrupt number.
 *              This parameter can be an enumerator of IRQn_Type enumeration
 *              (For the complete MG32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (MG32x02z.h))
 * @return      None
 * @exception   None
 * @note        To configure interrupts priority correctly, the NVIC_PriorityGroupConfig()
 *              function should be called before.
 * @par         Modify
 *              void MID_NVIC_EnableIRQ(IRQn_Type IRQn)
 *******************************************************************************
 */
void MID_NVIC_EnableIRQ(IRQn_Type IRQn)
{
    /* Check the parameters */
    assert_param(IS_NVIC_DEVICE_IRQ(IRQn));
  
    /* Enable interrupt */
    NVIC_EnableIRQ(IRQn);
}



/**
 *******************************************************************************
 * @brief       Disables a device specific interrupt in the NVIC interrupt controller.
 * @param       IRQn External interrupt number.
 *              This parameter can be an enumerator of IRQn_Type enumeration
 *              (For the complete MG32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (MG32x02z.h))
 * @return      None
 * @exception   None
 * @note        None
 * @par         Modify
 *              void MID_NVIC_DisableIRQ(IRQn_Type IRQn)
 *******************************************************************************
 */
void MID_NVIC_DisableIRQ(IRQn_Type IRQn)
{
    /* Check the parameters */
    assert_param(IS_NVIC_DEVICE_IRQ(IRQn));
  
    /* Disable interrupt */
    NVIC_DisableIRQ(IRQn);
}



/**
 *******************************************************************************
 * @brief       Initiates a system reset request to reset the MCU.
 * @return      None
 * @exception   None
 * @note        None
 * @par         Example
 * @code
                MID_NVIC_SystemReset();
 * @endcode     
 * @par         Modify
 *              void MID_NVIC_SystemReset(void)
 *******************************************************************************
 */
void MID_NVIC_SystemReset(void)
{
    /* System Reset */
    NVIC_SystemReset();
}


/**
 *******************************************************************************
 * @brief       Initializes the System Timer and its interrupt, and starts the System Tick Timer.
 *              Counter is in free running mode to generate periodic interrupts.
 * @param[in]   TicksNumb Specifies the ticks Number of ticks between two interrupts.
 * @return      status:  - 0  Function succeeded.
 *                       - 1  Function failed.
 * @exception   None
 * @note        None
 * @par         Modify
 *              uint32_t MID_SYSTICK_Config(uint32_t TicksNumb)
 *******************************************************************************
 */
uint32_t MID_SYSTICK_Config(uint32_t TicksNumb)
{
    return SysTick_Config(TicksNumb);
}

/**
  * @}
  */



/** @name  CORTEX_Exported_Functions_Group2 Peripheral Control functions 
 *  @brief Cortex control functions
 *
@verbatim
  ==============================================================================
                      ##### Peripheral Control functions #####
  ==============================================================================
    [..]
      This subsection provides a set of functions allowing to control the CORTEX
      (NVIC, SYSTICK) functionalities.


@endverbatim
  * @{
  */

/**
 *******************************************************************************
 * @brief       Gets the priority of an interrupt.
 * @param[in]   IRQn External interrupt number.
 *              This parameter can be an enumerator of IRQn_Type enumeration
 *              (For the complete MG32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (MG32x02z.h))
 * @return      Interrupt Priority.
 *              Value is aligned automatically to the implemented priority bits of the microcontroller.
 * @exception   None
 * @note        None
 * @par         Example
 * @code
                if(MID_GetREVID() == 0x00U);
 * @endcode     
 * @par         Modify
 *              uint32_t MID_NVIC_GetPriority(IRQn_Type IRQn)
 *******************************************************************************
 */
uint32_t MID_NVIC_GetPriority(IRQn_Type IRQn)
{
    /* Get priority for Cortex-M system or device specific interrupts */
    return NVIC_GetPriority(IRQn);
}



/**
 *******************************************************************************
 * @brief       Sets Pending bit of an external interrupt.
 * @param       IRQn External interrupt number
 *              This parameter can be an enumerator of IRQn_Type enumeration
 *              (For the complete MG32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (MG32x02z.h))
 * @return      None
 * @exception   None
 * @note        None
 * @par         Modify
 *              void MID_NVIC_SetPendingIRQ(IRQn_Type IRQn)
 *******************************************************************************
 */
void MID_NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
    /* Check the parameters */
    assert_param(IS_NVIC_DEVICE_IRQ(IRQn));
  
    /* Set interrupt pending */
    NVIC_SetPendingIRQ(IRQn);
}



/**
 *******************************************************************************
 * @brief       Gets Pending Interrupt (reads the pending register in the NVIC
 *              and returns the pending bit for the specified interrupt).
 * @param[in]   IRQn External interrupt number.
 *              This parameter can be an enumerator of IRQn_Type enumeration
 *              (For the complete MG32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (MG32x02z.h))
 * @return      status: - 0  Interrupt status is not pending.
 *                      - 1  Interrupt status is pending.
 * @exception   None
 * @note        None
 * @par         Modify
 *              uint32_t MID_NVIC_GetPendingIRQ(IRQn_Type IRQn)
 *******************************************************************************
 */
uint32_t MID_NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
    /* Check the parameters */
    assert_param(IS_NVIC_DEVICE_IRQ(IRQn));
  
    /* Return 1 if pending else 0 */
    return NVIC_GetPendingIRQ(IRQn);
}



/**
 *******************************************************************************
 * @brief       Clears the pending bit of an external interrupt.
 * @param       IRQn External interrupt number.
 *              This parameter can be an enumerator of IRQn_Type enumeration
 *              (For the complete MG32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (MG32x02z.h))
 * @return      None
 * @exception   None
 * @note        None
 * @par         Modify
 *              void MID_NVIC_ClearPendingIRQ(IRQn_Type IRQn)
 *******************************************************************************
 */
void MID_NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
    /* Check the parameters */
    assert_param(IS_NVIC_DEVICE_IRQ(IRQn));
  
    /* Clear pending interrupt */
    NVIC_ClearPendingIRQ(IRQn);
}



/**
 *******************************************************************************
 * @brief       Enable SysTick Interrupt .
 * @details
 * @return      None
 * @exception   None
 * @note        
 * @par         Example
 * @code
                MID_SYSTICK_EnableIRQ();
 * @endcode
 * @par         Modify
 *              void MID_SYSTICK_EnableIRQ(void)
 *******************************************************************************
 */
void MID_SYSTICK_EnableIRQ(void)
{
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
}



/**
 *******************************************************************************
 * @brief       Disable SysTick Interrupt.
 * @details
 * @return      None
 * @exception   None
 * @note        
 * @par         Example
 * @code
                MID_SYSTICK_DisableIRQ();
 * @endcode
 * @par         Modify
 *              void MID_SYSTICK_DisableIRQ(void)
 *******************************************************************************
 */
void MID_SYSTICK_DisableIRQ(void)
{
    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
}



/**
 *******************************************************************************
 * @brief       Get SysTick Current Value.
 * @details
 *              
 * @return      SysTick Current Value from SYST_CVR Register. 
 * @exception   None
 * @note        
 * @par         Example
 * @code
                lTemp32 = MID_SYSTICK_GetCurrentValue();
 * @endcode
 * @par         Modify
 *              uint32_t MID_SYSTICK_GetCurrentValue(void)
 *******************************************************************************
 */
uint32_t MID_SYSTICK_GetCurrentValue(void)
{
    return SysTick->VAL;
}



/**
 *******************************************************************************
 * @brief       Configures the SysTick clock source.
 * @param       CLKSource specifies the SysTick clock source.
 *              This parameter can be one of the following values:
 *                  @arg SYSTICK_CLKSOURCE_HCLK_DIV8: AHB clock divided by 8 selected as SysTick clock source.
 *                  @arg SYSTICK_CLKSOURCE_HCLK: AHB clock selected as SysTick clock source.
 * @return      None
 * @exception   None
 * @note        None
 * @par         Modify
 *              void MID_SYSTICK_CLKSourceConfig(uint32_t CLKSource)
 *******************************************************************************
 */
void MID_SYSTICK_CLKSourceConfig(uint32_t CLKSource)
{
    /* Check the parameters */
    assert_param(IS_SYSTICK_CLK_SOURCE(CLKSource));
    if (CLKSource == SYSTICK_CLKSOURCE_HCLK)
    {
        SysTick->CTRL |= SYSTICK_CLKSOURCE_HCLK;
    }
    else
    {
        SysTick->CTRL &= ~SYSTICK_CLKSOURCE_HCLK;
    }
}



/**
 *******************************************************************************
 * @brief       This function handles SYSTICK interrupt request.
 * @return      None
 * @exception   None
 * @note        None
 * @par         Example
 * @code
                MID_SYSTICK_IRQHandler()
 * @endcode     
 * @par         Modify
 *              void MID_SYSTICK_IRQHandler(void)
 *******************************************************************************
 */
void MID_SYSTICK_IRQHandler(void)
{
    MID_SYSTICK_Callback();
}



/**
  * @brief  SYSTICK callback.
  * @retval None
 *******************************************************************************
 * @brief       SYSTICK callback.
 * @return      None
 * @exception   None
 * @note        None
 * @par         Example
 * @code
                MID_SYSTICK_Callback();
 * @endcode     
 * @par         Modify
 *              __weak void MID_SYSTICK_Callback(void)
 *******************************************************************************
 
 */
__weak void MID_SYSTICK_Callback(void)
{
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_SYSTICK_Callback could be implemented in the user file
    */
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

/**
  * @}
  */

/************** (C) COPYRIGHT megawin Technology Co., Ltd. *****END OF FILE****/


