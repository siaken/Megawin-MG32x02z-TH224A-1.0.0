/**
 ******************************************************************************
 *
 * @file        MG32x02z__Common_DRV.c
 *
 * @brief       This is the C code format driver file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.11
 * @date        2021/04/21
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
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
 ******************************************************************************
 */



#include "MG32x02z__Common_DRV.h"




/** @defgroup DRV_Private_Variables DRV Private Variables
  * @{
  */
#if defined(IRQHandler_Middleware_Level_)
#else
  __IO uint32_t static uwTick;
#endif
/**
  * @}
  */



/**
 *******************************************************************************
 * @brief       This function configures the source of the time base. 
 *              The time source is configured  to have 1ms time base with a dedicated 
 *              Tick interrupt priority.
 * @note        This function is called  automatically at the beginning of program after
 *              reset by Init() or at any time when clock is reconfigured  by CSC_Init(). 
 * @note        In the default implementation, SysTick timer is the source of time base. 
 *              It is used to generate interrupts at regular time intervals. 
 *              Care must be taken if Delay() is called from a peripheral ISR process, 
 *              The the SysTick interrupt must have higher priority (numerically lower) 
 *              than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
 *              The function is declared as __Weak  to be overwritten  in case of other
 *              implementation  in user file.
 * @param       TickClock : Tick operation clock
 * @param       TickPriority: Tick interrupt priority.
 * @retval      DRV Return
 *******************************************************************************
 */
#if defined(IRQHandler_Middleware_Level_)
#else
__weak DRV_Return InitTick(uint32_t TickClock, uint32_t TickPriority)
{
    /*Configure the SysTick to have interrupt in 1ms time basis*/
    // __STATIC_INLINE uint32_t SysTick_Config(uint32_t ticks)
    SysTick_Config(TickClock/1000U);

    /*Configure the SysTick IRQ priority */
    //__STATIC_INLINE void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
    NVIC_SetPriority(SysTick_IRQn, TickPriority);

    /* Return function status */
    return DRV_Success;
}
#endif



/**
 *******************************************************************************
 * @brief       This function is called to increment  a global variable "uwTick"
 *              used as application time base.
 * @note        In the default implementation, this variable is incremented each 1ms
 *              in Systick ISR.
 * @note        This function is declared as __weak to be overwritten in case of other 
 *              implementations in user file.
 * @retval      None
 *******************************************************************************
 */
#if defined(IRQHandler_Middleware_Level_)
#else
__weak void IncTick(void)
{
  uwTick++;
}
#endif



/**
 *******************************************************************************
 * @brief       Provides a tick value in millisecond.
 * @note        This function is declared as __weak  to be overwritten  in case of other 
 *              implementations in user file.
 * @retval      tick value
 *******************************************************************************
 */
#if defined(IRQHandler_Middleware_Level_)
#else
__weak uint32_t GetTick(void)
{
  return uwTick;
}
#endif



/**
 *******************************************************************************
 * @brief       This function provides accurate delay (in milliseconds) based 
 *              on variable incremented.
 * @note        In the default implementation , SysTick timer is the source of time base.
 *              It is used to generate interrupts at regular time intervals where uwTick
 *              is incremented.
 * @note        ThiS function is declared as __weak to be overwritten in case of other
 *              implementations in user file.
 * @param[in]   DelayTime: specifies the delay time length, in milliseconds.
 * @retval      None
 *******************************************************************************
 */
#if defined(IRQHandler_Middleware_Level_)
#else
__weak void Delay(__IO uint32_t DelayTime)
{
    uint32_t tickstart = GetTick();
    uint32_t wait = DelayTime;
  
    /* Add a period to guarantee minimum wait */
    if (wait < 0xFFFFFFFF)
    {
        wait++;
    }
  
    while((GetTick() - tickstart) < wait)
    {
    }
}
#endif



/**
 *******************************************************************************
 * @brief       Suspend Tick increment.
 * @note        In the default implementation , SysTick timer is the source of time base. It is
 *              used to generate interrupts at regular time intervals. Once HAL_SuspendTick()
 *              is called, the the SysTick interrupt will be disabled and so Tick increment 
 *              is suspended.
 * @note        This function is declared as __weak to be overwritten in case of other
 *              implementations in user file.
 * @retval      None
 *******************************************************************************
 */
#if defined(IRQHandler_Middleware_Level_)
#else
__weak void SuspendTick(void)

{
    /* Disable SysTick Interrupt */
    SysTick->CTRL &= (~SysTick_CTRL_TICKINT_Msk);
}
#endif



/**
 *******************************************************************************
 * @brief       Resume Tick increment.
 * @note        In the default implementation , SysTick timer is the source of time base. It is
 *              used to generate interrupts at regular time intervals. Once HAL_ResumeTick()
 *              is called, the the SysTick interrupt will be enabled and so Tick increment 
 *              is resumed.
 * @note        This function is declared as __weak  to be overwritten  in case of other
 *              implementations in user file.
 * @retval      None
 *******************************************************************************
 */
#if defined(IRQHandler_Middleware_Level_)
#else
__weak void ResumeTick(void)
{
    /* Enable SysTick Interrupt */
    SysTick->CTRL |= (SysTick_CTRL_TICKINT_Msk);
}
#endif



/**
 *******************************************************************************
 * @brief       Protect Module Register
 * @details     
 * @param       Module
 *      @arg    RSTprotect
 *      @arg    CSCprotect
 *      @arg    PWprotect
 *      @arg    MEMprotect
 *      @arg    MEMsprotect
 *      @arg    CFGprotect
 *      @arg    IWDTprotect
 *      @arg    WWDTprotect
 *      @arg    RTCprotect
 * @return      DRV_Success
 * @return      DRV_Failure
 * @exception   None
 * @note        None
 * @par         Example
 * @code
                ProtectModuleReg(RSTprotect);
                ProtectModuleReg(CSCprotect);
                ProtectModuleReg(PWprotect);
                ProtectModuleReg(MEMprotect);
                ProtectModuleReg(MEMsprotect);
                ProtectModuleReg(CFGprotect);
                ProtectModuleReg(IWDTprotect);
                ProtectModuleReg(WWDTprotect);
                ProtectModuleReg(RTCprotect);
 * @endcode     
 * @par         Modify
 *              DRV_Return ProtectModuleReg(Lock_Type Module)
 *******************************************************************************
 */
DRV_Return ProtectModuleReg(Protect_Type Module)
{
    *(uint16_t*)Module = 0x0000;

    if(*(uint16_t*)Module == 0)
        return(DRV_Failure);
    else
        return(DRV_Success);
}

/**
 *******************************************************************************
 * @brief       UnProtect Module Register
 * @details     
 * @param       Module
 *      @arg    RSTprotect
 *      @arg    CSCprotect
 *      @arg    PWprotect
 *      @arg    MEMprotect
 *      @arg    MEMsprotect
 *      @arg    CFGprotect
 *      @arg    IWDTprotect
 *      @arg    WWDTprotect
 *      @arg    RTCprotect
 * @return      DRV_Success
 * @return      DRV_Failure
 * @exception   None
 * @note        None
 * @par         Example
 * @code
                UnProtectModuleReg(RSTprotect);
                UnProtectModuleReg(CSCprotect);
                UnProtectModuleReg(PWprotect);
                UnProtectModuleReg(MEMprotect);
                UnProtectModuleReg(MEMsprotect);
                UnProtectModuleReg(CFGprotect);
                UnProtectModuleReg(IWDTprotect);
                UnProtectModuleReg(WWDTprotect);
                UnProtectModuleReg(RTCprotect);
 * @endcode     
 * @par         Modify
 *              DRV_Return UnProtectModuleReg(Lock_Type Module)
 *******************************************************************************
 */
DRV_Return UnProtectModuleReg(Protect_Type Module)
{
    *(uint16_t*)Module = 0xA217;

    if(*(uint16_t*)Module == 0)
        return(DRV_Success);
    else
        return(DRV_Failure);
}

/**
 *******************************************************************************
 * @brief       Lock Module Register
 * @details     
 * @param[in]   Module
 *      @arg    RSTLock : Reset Module Lock
 *      @arg    CFGLock : CFG Module Lock
 *      @arg    IWDTLock : IWDT Module Lock
 *      @arg    RTCLock : RTC Module Lock
 * @return      DRV_Return
 *  @retval     DRV_Success : Lock Success
 *  @retval     DRV_Failure : Lock Failure
 * @exception   None
 * @note        None
 * @par         Example
 * @code
                LockModuleReg(RSTLock);
                LockModuleReg(IWDTLock);
                LockModuleReg(RTCLock);
 * @endcode     
 * @par         Modify
 *              DRV_Return LockModuleReg(Lock_Type Module)
 *******************************************************************************
 */
DRV_Return LockModuleReg(Lock_Type Module)
{
    *(uint16_t*)Module = 0x712A;

    if(*(uint16_t*)Module == 0)
        return(DRV_Failure);
    else
        return(DRV_Success);
}



/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/



