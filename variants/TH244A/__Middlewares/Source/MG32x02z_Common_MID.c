/**
 ******************************************************************************
 *
 * @file        MG32x02z_Common_MID.c
 * @brief       MID COMMON driver.
 *              This is the common part of the Middleware initialization.
 * @par         Project
 *              MG32x02z
 * @version     V1.01
 * @date        2020/09/18
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2019 Megawin Technology Co., Ltd.
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
 @verbatim
 ==============================================================================
                    ##### How to use this driver #####
 ==============================================================================
   [..]
   The common MID driver contains a set of generic and common APIs that can be
   used by the PPP peripheral drivers and the user to start using the MID. 
   [..]
   The MID contains two APIs categories:
        (+) MID Initialization and de-initialization functions
        (+) MID Control functions

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
 *   3. Neither the name of megawin Technology Co., Ltd. nor the names of its
 *      contributors may be used to endorse or promote products derived from this 
 *      software without specific prior written permission.
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

extern uint32_t MID_CSC_GetCK_AHBFreq(void);

/** @name  MG32x02z_Common_MID_Driver
  * @{
  */

/** @name  MID MID
  * @brief MID module driver.
  * @{
  */

// #ifdef MID_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/** @name  MID_Private_Macros MID Private Macros
  * @{
  */
/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @name  MID_Private_Variables MID Private Variables
  * @{
  */
__IO uint32_t  uwTick = 0;
/**
  * @}
  */
/* Private function prototypes -----------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/

/** @name  MID_Exported_Functions MID Exported Functions
  * @{
  */

/** @name  MID_Exported_Functions_Group1 Initialization and de-initialization Functions 
  * @brief Initialization and de-initialization functions
  *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
   [..]  This section provides functions allowing to:
      (+) Initializes the Flash interface, the NVIC allocation and initial clock 
          configuration. It initializes the source of time base also when timeout 
          is needed and the backup domain when enabled.
      (+) de-Initializes common part of the MID.
      (+) Configure The time base source to have 1ms time base with a dedicated 
          Tick interrupt priority. 
        (++) Systick timer is used by default as source of time base, but user 
             can eventually implement his proper time base source (a general purpose 
             timer for example or other time source), keeping in mind that Time base 
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
             handled in milliseconds basis.
        (++) Time base configuration function (MID_InitTick ()) is called automatically 
             at the beginning of the program after reset by MID_Init() or at any time 
             when clock is configured, by MID_CSC_ClockConfig(). 
        (++) Source of time base is configured  to generate interrupts at regular 
             time intervals. Care must be taken if MID_Delay() is called from a 
             peripheral ISR process, the Tick interrupt line must have higher priority 
            (numerically lower) than the peripheral interrupt. Otherwise the caller 
            ISR process will be blocked. 
       (++) functions affecting time base configurations are declared as __Weak  
             to make  override possible  in case of other  implementations in user file.
 
@endverbatim
  * @{
  */

/**
 *******************************************************************************
 * @brief       This function configures the Flash prefetch,
 *              Configures time base source, NVIC and Low level hardware
 * @return      MID status
 * @exception   None
 * @note        This function is called at the beginning of program after reset and before 
 *              the clock configuration
 * @note        The time base configuration is based on IHRCO clock when exiting from Reset.
 *              Once done, time base tick start incrementing.
 *              In the default implementation,Systick is used as source of time base.
 *              The tick variable is incremented each 1ms in its ISR.
 * @par         Example
 * @code
                MID_Init();
 * @endcode     
 * @par         Modify
 *              MID_StatusTypeDef MID_Init(void)
 *******************************************************************************
  */
MID_StatusTypeDef MID_Init(void)
{
    /* Use systick as time base source and configure 1ms tick (default clock after Reset is HSI) */
    MID_InitTick(TICK_INT_PRIORITY);

    /* Init the low level hardware */
    MID_MspInit();

    /* Return function status */
    return MID_OK;
}

/**
 *******************************************************************************
 * @brief       This function de-Initializes common part of the MID and stops the source
 *              of time base.
 * @return      MID status
 * @exception   None
 * @note        This function is optional.
 * @par         Example
 * @code
                MID_DeInit();
 * @endcode     
 * @par         Modify
 *              MID_StatusTypeDef MID_DeInit(void)
 *******************************************************************************
  */
MID_StatusTypeDef MID_DeInit(void)
{
    /* Reset of all peripherals */

    /* De-Init the low level hardware */
    MID_MspDeInit();

    /* Return function status */
    return MID_OK;
}

/**
 *******************************************************************************
 * @brief       Initializes the MSP.
 * @return      None
 * @exception   None
 * @note        None
 * @par         Example
 * @code
                MID_MspInit();
 * @endcode     
 * @par         Modify
 *              __weak void MID_MspInit(void)
 *******************************************************************************
 */
__weak void MID_MspInit(void)
{
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_MspInit could be implemented in the user file
     */
}

/**
 *******************************************************************************
 * @brief       DeInitializes the MSP.
 * @return      None
 * @exception   None
 * @note        None
 * @par         Example
 * @code
                MID_MspDeInit();
 * @endcode     
 * @par         Modify
 *              __weak void MID_MspDeInit(void)
 *******************************************************************************
  */
__weak void MID_MspDeInit(void)
{
    /* NOTE : This function Should not be modified, when the callback is needed,
              the MID_MspDeInit could be implemented in the user file
     */
}

/**
 *******************************************************************************
 * @brief       This function configures the source of the time base. 
 *              The time source is configured  to have 1ms time base with a dedicated 
 *              Tick interrupt priority.
 * @param       TickPriority Tick interrupt priority.
 * @return      MID status
 * @exception   None
 * @note        This function is called  automatically at the beginning of program after
 *              reset by MID_Init() or at any time when clock is reconfigured  by MID_CSC_ClockConfig().
 * @note        In the default implementation, SysTick timer is the source of time base.
 *              It is used to generate interrupts at regular time intervals.
 *              Care must be taken if MID_Delay() is called from a peripheral ISR process,
 *              The the SysTick interrupt must have higher priority (numerically lower)
 *              than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
 *              The function is declared as __Weak  to be overwritten  in case of other
 *              implementation  in user file.
 * @par         Example
 * @code
                MID_InitTick(0U);
                MID_InitTick(1U);
                MID_InitTick(2U);
                MID_InitTick(3U);
 * @endcode     
 * @par         Modify
 *              __weak MID_StatusTypeDef MID_InitTick(uint32_t TickPriority)
 *******************************************************************************
  */
__weak MID_StatusTypeDef MID_InitTick(uint32_t TickPriority)
{
    /*Configure the SysTick to have interrupt in 1ms time basis*/
    MID_SYSTICK_Config(MID_CSC_GetCK_AHBFreq()/1000U);
   
    /*Configure the SysTick IRQ priority */
    MID_NVIC_SetPriority(SysTick_IRQn, TickPriority);

     /* Return function status */
    return MID_OK;
}

/**
  * @}
  */

/** @name  MID_Exported_Functions_Group2 MID Control functions 
  * @brief MID Control functions
  *
@verbatim
 ===============================================================================
                      ##### MID Control functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Provide a tick value in millisecond
      (+) Provide a blocking delay in millisecond
      (+) Suspend the time base source interrupt
      (+) Resume the time base source interrupt
      (+) Get the MID API driver version
      (+) Get the device identifier
      (+) Get the device revision identifier
      (+) Module Pro
      (+) Module UnPro
      (+) Get ther Module Pro State
@endverbatim
  * @{
  */

/**
 *******************************************************************************
 * @brief       This function is called to increment  a global variable "uwTick"
 *              used as application time base.
 * @return      None
 * @exception   None
 * @note        In the default implementation, this variable is incremented each 1ms
 *              in Systick ISR.
 * @note        This function is declared as __weak to be overwritten in case of other
 *              implementations in user file.
 * @par         Example
 * @code
                void MID_IncTick();
 * @endcode     
 * @par         Modify
 *              __weak void MID_IncTick(void)
 *******************************************************************************
  */
__weak void MID_IncTick(void)
{
    uwTick++;
}

/**
 *******************************************************************************
 * @brief       This function is called to clear a global variable "MID_uwTick"
 *              used as application time base.
 * @retval      None
 * @exception   None
 *******************************************************************************
 */
void MID_ClearTick(void)
{
    uwTick = 0;
}

/**
 *******************************************************************************
 * @brief       Provides a tick value in millisecond.
 * @return      tick value
 * @exception   None
 * @note        This function is declared as __weak  to be overwritten  in case of other
 *              implementations in user file.
 * @code
                void MID_GetTick();
 * @endcode     
 * @par         Modify
 *              __weak void MID_GetTick(void)
 *******************************************************************************
  */
__weak uint32_t MID_GetTick(void)
{
    return uwTick;
}

/**
 *******************************************************************************
 * @brief       This function provides accurate delay (in milliseconds) based 
 *              on variable incremented.
 * @param[in]   Delay specifies the delay time length, in milliseconds.
 * @return      None
 * @exception   None
 * @note        In the default implementation , SysTick timer is the source of time base.
 *              It is used to generate interrupts at regular time intervals where uwTick
 *              is incremented.
 * @note        ThiS function is declared as __weak to be overwritten in case of other
 *              implementations in user file.
 * @par         Example
 * @code
                MID_Delay(500); // 500 Systick
 * @endcode     
 * @par         Modify
 *              __weak void MID_Delay(__IO uint32_t Delay)
 *******************************************************************************
  */
__weak void MID_Delay(__IO uint32_t Delay)
{
    uint32_t tickstart = MID_GetTick();
    uint32_t wait = Delay;
  
    /* Add a period to guarantee minimum wait */
    if (wait < MID_MAX_DELAY)
    {
       wait++;
    }
  
    while((MID_GetTick() - tickstart) < wait)
    {
    }
}

/**
 *******************************************************************************
 * @brief       Suspend Tick increment.
 * @return      None
 * @exception   None
 * @note        In the default implementation , SysTick timer is the source of time base. It is
 *              used to generate interrupts at regular time intervals. Once MID_SuspendTick()
 *              is called, the the SysTick interrupt will be disabled and so Tick increment 
 *              is suspended.
 * @note        This function is declared as __weak to be overwritten in case of other
 *              implementations in user file.
 * @par         Example
 * @code
                MID_SuspendTick();
 * @endcode     
 * @par         Modify
 *              __weak void MID_SuspendTick(void)
 *******************************************************************************
  */
__weak void MID_SuspendTick(void)
{
    /* Disable SysTick Interrupt */
    SysTick->CTRL &= SysTick_CTRL_TICKINT_Msk;
}

/**
 *******************************************************************************
 * @brief       Resume Tick increment.
 * @return      None
 * @exception   None
 * @note        In the default implementation , SysTick timer is the source of time base. It is
 *              used to generate interrupts at regular time intervals. Once MID_ResumeTick()
 *              is called, the the SysTick interrupt will be enabled and so Tick increment 
 *              is resumed.
 * @note        This function is declared as __weak  to be overwritten  in case of other
 *              implementations in user file.
 * @par         Example
 * @code
                MID_ResumeTick();
 * @endcode     
 * @par         Modify
 *              __weak void MID_ResumeTick(void)
 *******************************************************************************
  */
__weak void MID_ResumeTick(void)
{
    /* Enable SysTick Interrupt */
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
}



/**
 *******************************************************************************
 * @brief       Protect Module Register
 * @details     
 * @param       Module
 *      @arg    RSTmodule
 *      @arg    CSCmodule
 *      @arg    PWmodule
 *      @arg    MEMmodule
 *      @arg    MEM2module
 *      @arg    CFGmodule
 *      @arg    IWDTmodule
 *      @arg    WWDTmodule
 *      @arg    RTCmodule
 * @return      MID Status
 * @exception   None
 * @note        None
 * @par         Example
 * @code
                ProtectModuleReg(RSTmodule);
                ProtectModuleReg(CSCmodule);
                ProtectModuleReg(PWmodule);
                ProtectModuleReg(MEMmodule);
                ProtectModuleReg(MEM2module);
                ProtectModuleReg(CFGmodule);
                ProtectModuleReg(IWDTmodule);
                ProtectModuleReg(WWDTmodule);
                ProtectModuleReg(RTCmodule);
 * @endcode     
 * @par         Modify
 *              MID_StatusTypeDef MID_ProtectModuleReg(MID_ProtectTypeDef Module)
 *******************************************************************************
 */
MID_StatusTypeDef MID_ProtectModuleReg(MID_ProtectTypeDef Module)
{
    *(uint16_t*)Module = 0x0000;

    if(*(uint16_t*)Module == 0)
        return(MID_OK);
    else
        return(MID_ERROR);
}

/**
 *******************************************************************************
 * @brief       UnProtect Module Register
 * @details     
 * @param       Module
 *      @arg    RSTmodule
 *      @arg    CSCmodule
 *      @arg    PWmodule
 *      @arg    MEMmodule
 *      @arg    MEM2module
 *      @arg    CFGmodule
 *      @arg    IWDTmodule
 *      @arg    WWDTmodule
 *      @arg    RTCmodule
 * @return      MID StatusTypeDef
 * @exception   None
 * @note        None
 * @par         Example
 * @code
                MID_UnProtectModuleReg(RSTmodule);
                MID_UnProtectModuleReg(CSCmodule);
                MID_UnProtectModuleReg(PWmodule);
                MID_UnProtectModuleReg(MEMmodule);
                MID_UnProtectModuleReg(MEM2module);
                MID_UnProtectModuleReg(CFGmodule);
                MID_UnProtectModuleReg(IWDTmodule);
                MID_UnProtectModuleReg(WWDTmodule);
                MID_UnProtectModuleReg(RTCmodule);
 * @endcode     
 * @par         Modify
 *              MID_StatusTypeDef MID_UnProtectModuleReg(MID_ProtectTypeDef Module)
 *******************************************************************************
 */
MID_StatusTypeDef MID_UnProtectModuleReg(MID_ProtectTypeDef Module)
{
    *(uint16_t*)Module = 0xA217;

    if(*(uint16_t*)Module == 0)
        return(MID_OK);
    else
        return(MID_ERROR);
}



/**
  * @}
  */

/**
  * @}
  */

//#endif /* MID_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************** (C) COPYRIGHT megawin Technology Co., Ltd. *****END OF FILE****/
