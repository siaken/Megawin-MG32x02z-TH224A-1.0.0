/**
 ******************************************************************************
 *
 * @file        MG32x02z_MEM_MID.c
 * @brief       MEM MID module driver.
 *              This file provides firmware functions to manage the following 
 *              functionalities of the internal MEM memory:
 *               + Program operations functions
 *               + Memory Control functions 
 *               + Peripheral State functions
 * @par         Project
 *              MG32x02z
 * @version     V1.00
 * @date        2020/12/22
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2020 megawin Technology Co., Ltd.
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
                       ##### MEM peripheral features #####
 ==============================================================================
 [..] The MEM Flash memory interface manages CPU AHB I-Code and D-Code accesses 
      to the MEM memory. It implements the erase and program MEM memory operations 
      and the read and write protection mechanisms.

 [..] The MEM memory interface accelerates code execution with a system of instruction
     prefetch. 

 [..] The MEM main features are:
     (+) MEM memory read operations
     (+) MEM memory program/erase operations
     (+) Read / write protections
     (+) Warm reset, boot from AP / ISP / SRAM
     (+) IAP Space Access Control


                    ##### How to use this driver #####
 ==============================================================================
 [..]                             
     This driver provides functions and macros to configure and program the MEM 
     Flash of all MG32x02A devices.
   
     (#) MEM Flash Memory I/O Programming functions: this group includes all needed
         functions to erase and program the main memory:
       (++) Lock and Unlock the MEM Flash interface
       (++) Erase function: Erase page, erase all pages
       (++) Program functions: half word, word and doubleword

 [..] In addition to these function, this driver includes a set of macros allowing
      to handle the following operations:
     (+) Set/Get the MEM Flash Read WAIT TIME
     (+) Monitor the MEM flags status

 @endverbatim
 ****************************************************************************** 
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "MG32x02z_MEM_MID.h"

/** @name MG32x02A_MID_Driver
  * @{
  */


/** @defgroup MEM MEM MID module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup MEM_Private_Constants MEM Private Constants
  * @{
  */
/**
  * @}
  */

/* Private macro ---------------------------- ---------------------------------*/
/** @defgroup MEM_Private_Macros MEM Private Macros
  * @{
  */
 
/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup MEM_Private_Variables MEM Private Variables
  * @{
  */

static MEM_ProcessTypeDef mMEM;   /*!< Variables used for Erase pages under interruption */

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup MEM_Private_Functions MEM Private Functions
  * @{
  */

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/
/** @defgroup MEM_Exported_Functions MEM Exported Functions
  * @{
  */
  
/** @defgroup MEM_Exported_Functions_Group1 Programming operation functions 
  * @brief   Programming operation functions 
  *
  * @verbatim
  * @endverbatim
  * @{
  */

/**
 *******************************************************************************
 * @brief       Program word at a specified AP / IAP / ISPD address
 *
 * @note        If an erase and a program operations are requested simultaneously,    
 *              the erase operation is performed before the program one.
 *  
 * @note        MEM Flash should be previously erased before new programmation
 *
 * @param[in]   Address : Specifie the address to be programmed.
 * @param[in]   Data : Specifie the data to be programmed
 * 
 * @return      MID_StatusTypeDef MID Status
 * @exception   None
 * @note        
 * @par         Example
 * @code
 *              
 * @endcode
 * @par         Modify
 *              MID_StatusTypeDef MID_MEM_FlashProgram(uint32_t Address, uint32_t Data)
 *******************************************************************************
  */
MID_StatusTypeDef MID_MEM_FlashProgram(uint32_t Address, uint32_t Data)
{
    MID_StatusTypeDef status = MID_OK;

    /* Process Locked */
    __MID_LOCK(&mMEM);

    /* Check the parameters */
    assert_param(IS_MEM_PROGRAM_ADDRESS(Address));

    /* Check IHRCO is Enable */
    if(MID_CSC_GetCK_IHRCOFreq() == 0)
    {
        mMEM.ErrorCode |= MEM_ERROR_IHRCO;
        return MID_ERROR;
    }

    /* Check Program on Word Address */
    if((Address & 0x00000003) != 0)
        return MID_ERROR;

    /* Wait for last operation to be completed */
    status = MID_MEM_WaitForLastOperation(MEM_TIMEOUT_VALUE);

    if(status == MID_OK)
    {
        /* MEM Register Write UnProtect*/
        __MID_MEM_UNPROTECT();

        /* MEM Flash Write Enable */
        __MID_MEM_ENABLE();

        /* MEM Flash Write Access Space Enable */
        __MID_MEM_ACCESS_ENABLE(MEM_ACCESS_IAP_WRITE | MEM_ACCESS_AP_WRITE | MEM_ACCESS_ISPD_WRITE);

        /* MEM Flash Write Mode Config */
        __MID_MEM_SET_WRITE_MODE(MEM_WRITE_MODE_PROGRAM);

        /* MEM Flash Write Sequence Key Single or Multiple*/
        __MID_MEM_SET_SINGLE_WRITE_SEQUENCE();

        // Mem Flag Clear.
        __MID_MEM_CLEAR_FLAG(MEM_FLAG_EOP | MEM_FLAG_WRE);
        __ISB();

        *(uint32_t *)Address = Data;

        /* MEM Register Write Protect*/
        __MID_MEM_UNPROTECT();

        /* MEM Flash Write Mode Config */
        __MID_MEM_SET_WRITE_MODE(MEM_WRITE_MODE_STANBY);

        /* MEM Flash Write Access Space Disable */
        __MID_MEM_ACCESS_DISABLE(MEM_ACCESS_IAP_WRITE | MEM_ACCESS_AP_WRITE | MEM_ACCESS_ISPD_WRITE);

        /* Wait for last operation to be completed */
        status = MID_MEM_WaitForLastOperation(MEM_TIMEOUT_VALUE);

        /* If the program operation is completed, disable the PG Bit */
        __MID_MEM_DISABLE();

        /* MEM Register Write Protect*/
        __MID_MEM_PROTECT();
    }

    /* Process Unlocked */
    __MID_UNLOCK(&mMEM);

    return status;
}



/**
 *******************************************************************************
 * @brief       Erase the specified AP / IAP / ISPD Flash memory page Erase
 * @param       PageAddress MEM Flash page to erase
 *              The value of this parameter depend on device used within the same series
 * @return      MID_StatusTypeDef MID Status
 * @exception   None
 * @note        
 * @par         Example
 * @code
 *              MID_MEM_FlashPageErase(0x1A000000UL); // IAP Start Address
 *              MID_MEM_FlashPageErase(0x1FF00000UL); // ISPD Start Address
 *              MID_MEM_FlashPageErase(0x18000000UL); // Not Boot from AP, AP Start Address
 * @endcode
 * @par         Modify
 *              MID_StatusTypeDef MID_MEM_FlashPageErase(uint32_t PageAddress)
 *******************************************************************************
 */
MID_StatusTypeDef MID_MEM_FlashPageErase(uint32_t PageAddress)
{
    MID_StatusTypeDef status = MID_ERROR;

    /* Check the parameters */
    assert_param(IS_MEM_PROGRAM_ADDRESS(Address));

    /* Process Locked */
    __MID_LOCK(&mMEM);

    /* Clean the error context */
    mMEM.ErrorCode = MEM_ERROR_NONE;

    /* Check IHRCO is Enable */
    if(MID_CSC_GetCK_IHRCOFreq() == 0)
        return MID_ERROR;

    /* Check Program on Page Address */
  #if defined(MG32_1ST) || defined(MG32_2ND)
    if((PageAddress & 0x000003FF) != 0)
        return MID_ERROR;
  #elif defined(MG32_3RD) || defined(MG32_4TH)
    if((PageAddress & 0x000001FF) != 0)
        return MID_ERROR;
  #endif

    /* Wait for last operation to be completed */
    status = MID_MEM_WaitForLastOperation(MEM_TIMEOUT_VALUE);

    if(status == MID_OK)
    {
        /* MEM Register Write UnProtect*/
        __MID_MEM_UNPROTECT();

        /* MEM Flash Write Enable */
        __MID_MEM_ENABLE();

        /* MEM Flash Write Access Space Enable */
        __MID_MEM_ACCESS_ENABLE(MEM_ACCESS_IAP_WRITE | MEM_ACCESS_AP_WRITE | MEM_ACCESS_ISPD_WRITE);

        /* MEM Flash Write Mode Config */
        __MID_MEM_SET_WRITE_MODE(MEM_WRITE_MODE_PAGEERASE);

        /* MEM Flash Write Sequence Key Single or Multiple*/
        __MID_MEM_SET_SINGLE_WRITE_SEQUENCE();

        /* Mem Flag Clear */
        __MID_MEM_CLEAR_FLAG(MEM_FLAG_EOP | MEM_FLAG_WRE);
        __ISB();

        /* MEM Flash Access Page Erase */
        *(uint32_t *)PageAddress = 0xFFFFFFFF;

        /* MEM Register Write UnProtect*/
        __MID_MEM_UNPROTECT();

        /* MEM Flash Write Mode Config */
        __MID_MEM_SET_WRITE_MODE(MEM_WRITE_MODE_STANBY);

        /* MEM Flash Write Access Space Disable */
        __MID_MEM_ACCESS_DISABLE(MEM_ACCESS_IAP_WRITE | MEM_ACCESS_AP_WRITE | MEM_ACCESS_ISPD_WRITE);

        /* Wait for last operation to be completed */
        status = MID_MEM_WaitForLastOperation(MEM_TIMEOUT_VALUE);

        /* If the program operation is completed, disable the PG Bit */
        __MID_MEM_DISABLE();

        /* MEM Register Write Protect*/
        __MID_MEM_PROTECT();
    }

    /* Process Unlocked */
    __MID_UNLOCK(&mMEM);

    return status;
}

/**
  * @}
  */



/** @defgroup    MEM_Exported_Functions_Group2 Peripheral Control functions 
 *  @brief   management functions 
 *
@verbatim   
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to control the MEM 
    memory operations.

@endverbatim
  * @{
  */

/**
 *******************************************************************************
 * @brief       Unlock the MEM control register access
 * @return      MID Status
 * @exception   None
 * @note        
 * @par         Example
 * @code
 *              MID_MEM_Unlock();
 * @endcode
 * @par         Modify
 *              MID_StatusTypeDef MID_MEM_Unlock(void)
 *******************************************************************************
 */
MID_StatusTypeDef MID_MEM_Unlock(void)
{
    MID_StatusTypeDef status = MID_OK;

    if(MEM->KEY.H[0] != 0)
    {
        /* Authorize the MEM Registers access */
        MEM->KEY.H[0] = 0xA217;

        /* Verify Flash is unlocked */
        if(MEM->KEY.H[0] != 0)
        {
            status = MID_ERROR;
        }
    }
    return status;
}



/**
 *******************************************************************************
 * @brief       Locks the MEM control register access
 * @return      MID Status
 * @exception   None
 * @note        
 * @par         Example
 * @code
 *              MID_MEM_Lock();
 * @endcode
 * @par         Modify
 *              MID_StatusTypeDef MID_MEM_Lock(void)
 *******************************************************************************
 */
MID_StatusTypeDef MID_MEM_Lock(void)
{
    /* Set the LOCK Bit to lock the MEM Registers access */
    MEM->KEY.H[0] = 0x0000U;
    return MID_OK;
}


/**
 *******************************************************************************
 * @brief       Config MEM IAP Flash Size 
 * @details
 *              IAP memory size select. Value 0 indicates the IAP memory size 0K-byte.
 *              Value 1 indicates the IAP memory size 1K-byte. 
 *              This register write access is no effect when MEM_IAP_AEN=0.
 *              (The default value is loaded from CFG OR after Warm reset.)
 * @param[in]   Size IAP Flash Space Size
 *  @arg\b      0K ~ N Byte : with the Flash Page Size.
 * @return      MID_StatusTypeDef MID Status
 *              MID_OK : Set Successful
 *              MID_ERROR : IAP Size Lock or Size Over
 * @exception   None
 * @note        
 * @par         Example
 * @code
 *              MID_MEM_ConfigIAPSize(1024);    // IAP Size 1KByte
 *              MID_MEM_ConfigIAPSize(2048);    // IAP Size 2KByte
 *              MID_MEM_ConfigIAPSize(3072);    // IAP Size 3KByte
 *              MID_MEM_ConfigIAPSize(4096);    // IAP Size 4KByte
 *              MID_MEM_ConfigIAPSize(5120);    // IAP Size 5KByte
 *              MID_MEM_ConfigIAPSize(6144);    // IAP Size 6KByte
 *              MID_MEM_ConfigIAPSize(7168);    // IAP Size 7KByte
 *              MID_MEM_ConfigIAPSize(8192);    // IAP Size 8KByte
 * @endcode
 * @par         Modify
 *              MID_StatusTypeDef MID_MEM_ConfigIAPSize(uint32_t Size)
 *******************************************************************************
 */
MID_StatusTypeDef MID_MEM_ConfigIAPSize(uint32_t Size)
{
    uint32_t lTemp = MEM->IAPSZ.W;

    /* Check IAP_Size_Lock */
    if(MEM->CR0.MBIT.IAP_AEN == 0)
        return MID_ERROR;

    /* Check Config Size Alignment Page Size */
    if((Size & MEM_FLASH_PAGE_SIZE) != 0)
        return MID_ERROR;

    /* MEM Register Write UnProtect*/
    __MID_MEM_UNPROTECT();

    /* Write IAP Size*/
    MEM->IAPSZ.W = Size >> 2;

    /* MEM Register Write Protect*/
    __MID_MEM_PROTECT();

    // check IAP Space is Over Device Flash Size?
    if(__MID_MEM_GET_FLAG(MEM_FLAG_IAPSE) != 0)
    {
        /* MEM Register Write UnProtect*/
        __MID_MEM_UNPROTECT();

        /* Restore IAP Original Config */
        MEM->IAPSZ.W = lTemp;

        /* MEM Register Write Protect*/
        __MID_MEM_PROTECT();
        return MID_ERROR;
    }
    else
        return MID_OK;
}


/**
 *******************************************************************************
 * @brief       Lock IAP Flash Size 
 * @details
 *              IAP memory size MEM_IAP_SIZE register access disable.
 *              This only able to Lock.
 *              That is on effect to Lock
 *              Disable : Register access Lock
 *              Enable(Default) : Register access UnLock.
 * @return      MID_StatusTypeDef MID Status
 *              MID_OK :    Set Successful
 * @exception   None
 * @note        
 * @par         Example
 * @code
 *              MID_MEM_IAPSizeLock();
 * @endcode
 * @par         Modify
 *              MID_StatusTypeDef MID_MEM_IAPSizeLock(void)
 *******************************************************************************
 */
MID_StatusTypeDef MID_MEM_IAPSizeLock(void)
{
    /* MEM Register Write UnProtect*/
    __MID_MEM_UNPROTECT();

    /* MEM Disable IAP Size Config Function */
    MEM->CR0.MBIT.IAP_AEN = 0;

    /* MEM Register Write Protect*/
    __MID_MEM_PROTECT();

    return MID_OK;
}


/**
 *******************************************************************************
 * @brief       Get IAP Lock Status 
 * @details
 *              IAP memory size MEM_IAP_SIZE register access status.
 *              This only able to Lock.
 *              That is on effect to Lock
 *              Disable : Register access Lock
 *              Enable : Register access UnLock(Default).
 * @return      FunctionalState Functional Status
 *              DISABLE : IAP Size Lock
 *              ENABLE : IAP Size UnLock(Default).
 * @exception   None
 * @note        
 * @par         Example
 * @code
 *              if(MID_MEM_GetIAPSizeLockState == ENABLE)
 *              if(MID_MEM_GetIAPSizeLockState == DISABLE)
 * @endcode
 * @par         Modify
 *              FunctionalState MID_MEM_GetIAPSizeLockState(void)
 *******************************************************************************
 */
FunctionalState MID_MEM_GetIAPSizeLockState(void)
{
    if(MEM->CR0.MBIT.IAP_AEN == 0)
        return ENABLE;
    else
        return DISABLE;
}


/**
 *******************************************************************************
 * @brief       Disable IAP Code Execute
 * @details
 *              Flash IAP data memory code execution function disable.
 *              Enable (Default)
 *              Disable
 * @return      MID_StatusTypeDef MID Status
 *              MID_OK : Set Successful
 * @exception   None
 * @note        
 * @par         Example
 * @code
 *              MID_MEM_IAPExecuteDisable();
 * @endcode
 * @par         Modify
 *              MID_StatusTypeDef MID_MEM_IAPExecuteDisable(void)
 *******************************************************************************
 */
MID_StatusTypeDef MID_MEM_IAPExecuteDisable(void)
{
    /* MEM Register Write UnProtect*/
    __MID_MEM_UNPROTECT();

    /* MEM Disable IAP Execute Code Function */
    MEM->CR1.MBIT.IAP_EXEC = 0;

    /* MEM Register Write Protect*/
    __MID_MEM_PROTECT();

    return MID_OK;
}


/**
 *******************************************************************************
 * @brief       Get IAP Code Execute Status 
 * @details
 *              Flash IAP data memory code execution function status.
 *              Enable (Default)
 *              Disable
 * @return      FunctionalState Functional Status
 *              DISABLE : IAP Code Execute Disable
 *              ENABLE(Default) : IAP Code Execute.
 * @exception   None
 * @note        
 * @par         Example
 * @code
 *              if(MID_MEM_GetIAPExecuteState == ENABLE)
 *              if(MID_MEM_GetIAPExecuteState == DISABLE)
 * @endcode
 * @par         Modify
 *              FunctionalState MID_MEM_GetIAPCodeExecuteState(void)
 *******************************************************************************
 */
FunctionalState MID_MEM_GetIAPExecuteState(void)
{
    if(MEM->CR1.MBIT.IAP_EXEC == 0)
        return ENABLE;
    else
        return DISABLE;
}


/**
 *******************************************************************************
 * @brief       System Warm Reset Boot from AP Flash
 * @details
 * @return      None
 * @exception   None
 * @note        
 * @par         Example
 * @code
 *              MID_MEM_WarmReset_toAP();
 * @endcode
 * @par         Modify
 *              void MID_MEM_WarmResettoAP(void)
 *******************************************************************************
 */
void MID_MEM_WarmResettoAP(void)
{
    /* RST Register Write UnProtect*/
    RST_Base->KEY.H[0] = 0xA217;         // 20-Byte

    /* SofrWare and CPU Cool Reset Disable */
    RST_Base->CE.W &= ~(RST_CE_SW_CE_mask_w | RST_CE_CPU_CE_mask_w);

    /* SofrWare and CPU warm Reset Enable */
    RST_Base->WE.B[0] |= (RST_WE_SW_WE_mask_w | RST_WE_CPU_WE_mask_w);

    /* RST Register Write Protect*/
    RST_Base->KEY.H[0] = 0;

    /* MEM Register Write UnProtect*/
    __MID_MEM_UNPROTECT();

    /* Set Boot From AP Flash */
    MEM->CR0.B[2] = ((MEM->CR0.B[2] & (~MEM_CR0_BOOT_MS_mask_b2)) | MEM_CR0_BOOT_MS_application_flash_b2);

    /* MEM Register Write UnProtect*/
    __MID_MEM_PROTECT();

    /* Initiates a system reset request to reset the MCU */
    __NVIC_SystemReset();

    __ISB();
    //while(1);
}


/**
 *******************************************************************************
 * @brief       System Warm Reset Boot from ISP Flash
 * @details
 * @return      None
 * @exception   None
 * @note        
 * @par         Example
 * @code
 *              MID_MEM_WarmReset_toISP();
 * @endcode
 * @par         Modify
 *              void MID_MEM_WarmResettoISP(void)
 *******************************************************************************
 */
void MID_MEM_WarmResettoISP(void)
{
    /* RST Register Write UnProtect*/
    RST_Base->KEY.H[0] = 0xA217;         // 20-Byte

    /* SofrWare and CPU Cool Reset Disable */
    RST_Base->CE.W &= ~(RST_CE_SW_CE_mask_w | RST_CE_CPU_CE_mask_w);

    /* SofrWare and CPU warm Reset Enable */
    RST_Base->WE.B[0] |= (RST_WE_SW_WE_mask_w | RST_WE_CPU_WE_mask_w);

    /* RST Register Write Protect*/
    RST_Base->KEY.H[0] = 0;

    /* MEM Register Write UnProtect*/
    __MID_MEM_UNPROTECT();

    /* Set Boot From ISP Flash */
    MEM->CR0.B[2] = ((MEM->CR0.B[2] & (~MEM_CR0_BOOT_MS_mask_b2)) | MEM_CR0_BOOT_MS_boot_flash_b2);

    /* MEM Register Write UnProtect*/
    __MID_MEM_PROTECT();

    /* Initiates a system reset request to reset the MCU */
    __NVIC_SystemReset();

    __ISB();
    //while(1);
}


/**
 *******************************************************************************
 * @brief       System Warm Reset Boot from SRAM
 * @details
 * @return      None
 * @exception   None
 * @note        
 * @par         Example
 * @code
 *              MID_MEM_WarmReset_toSRAM();
 * @endcode
 * @par         Modify
 *              void MID_MEM_WarmResettoSRAM(void)
 *******************************************************************************
 */
void MID_MEM_WarmResettoSRAM(void)
{
    /* RST Register Write UnProtect*/
    RST_Base->KEY.H[0] = 0xA217;         // 20-Byte

    /* SofrWare and CPU Cool Reset Disable */
    RST_Base->CE.W &= ~(RST_CE_SW_CE_mask_w | RST_CE_CPU_CE_mask_w);

    /* SofrWare and CPU warm Reset Enable */
    RST_Base->WE.B[0] |= (RST_WE_SW_WE_mask_w | RST_WE_CPU_WE_mask_w);

    /* RST Register Write Protect*/
    RST_Base->KEY.H[0] = 0;

    /* MEM Register Write UnProtect*/
    __MID_MEM_UNPROTECT();

    /* Set Boot From SRAM Memory */
    MEM->CR0.B[2] = ((MEM->CR0.B[2] & (~MEM_CR0_BOOT_MS_mask_b2)) | MEM_CR0_BOOT_MS_embedded_sram_b2);

    /* MEM Register Write UnProtect*/
    __MID_MEM_PROTECT();

    /* Initiates a system reset request to reset the MCU */
    __NVIC_SystemReset();

    __ISB();
    //while(1);
}

/**
 ******************************************************************************
 * @brief  This function handles MEM interrupt request.
 * @retval None
 ******************************************************************************
 */
void MID_MEM_IRQHandler(void)
{
    MID_MEM_ITHandlerCallback();
}

/**
 ******************************************************************************
 * @brief  MEM of interrupt Handler callback.
 * @retval None
 ******************************************************************************
 */
__weak void MID_MEM_ITHandlerCallback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the MID_MEM_InterruptHandlerCallback could be implemented in the user file
   */
}

/**
  * @}
  */



/** @defgroup  MEM_Exported_Functions_Group3 Peripheral errors functions 
 *  @brief Peripheral errors functions 
 *
@verbatim
 ===============================================================================
                      ##### Peripheral Errors functions #####
 ===============================================================================  
    [..]
    This subsection permit to get in run-time errors of  the MEM peripheral.

@endverbatim
  * @{
  */

/**
 *******************************************************************************
 * @brief       Get the specific MEM error flag.
 * @details
 * @return      MEM_Error_Codes The returned value can be:
 *
 * @exception   None
 * @note        
 * @par         Example
 * @code
 *              MID_MEM_GetError();
 * @endcode
 * @par         Modify
 *              uint32_t MID_MEM_GetError(void)
 *******************************************************************************
 */
uint32_t MID_MEM_GetError(void)
{
   return mMEM.ErrorCode;
}

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup  MEM_Private_Functions MEM Private Functions
 * @{
 */

/**
 *******************************************************************************
 * @brief       Wait for a MEM operation to complete.
 * @param[in]   Timeout  maximum flash operation timeout
 * @retval      MID Status
 * @exception   None
 * @note        
 * @par         Example
 * @code
 *              MID_MEM_WaitForLastOperation(MEM_TIMEOUT_VALUE);
 * @endcode
 * @par         Modify
 *              MID_StatusTypeDef MID_MEM_WaitForLastOperation(uint32_t Timeout)
 *******************************************************************************
 */
MID_StatusTypeDef MID_MEM_WaitForLastOperation(uint32_t Timeout)
{
  /* Wait for the MEM operation to complete by polling on BUSY flag to be reset.
     Even if the MEM operation fails, the BUSY flag will be reset and an error
     flag will be set */

    uint32_t tickstart = MID_GetTick();

    while(__MID_MEM_GET_FLAG(MEM_FLAG_BUSY)) 
    { 
        if (Timeout != MID_MAX_DELAY)
        {
            if((Timeout == 0U) || ((MID_GetTick() - tickstart) > Timeout))
            {
                return MID_TIMEOUT;
            }
        }
    }

    /* Check MEM End of Operation flag  */
    if (__MID_MEM_GET_FLAG(MEM_FLAG_EOP) != 0)
    {
        /* Clear MEM End of Operation pending bit */
        __MID_MEM_CLEAR_FLAG(MEM_FLAG_EOP);
    }

    if(__MID_MEM_GET_FLAG(MEM_FLAG_WRE) != 0)
    {
        /*Save the error code*/
        mMEM.ErrorCode |= MEM_ERROR_WR;

        /* Clear MEM End of Operation pending bit */
        __MID_MEM_CLEAR_FLAG(MEM_FLAG_WRE);
        return MID_ERROR;
    }

    /* There is no error flag set */
    return MID_OK;
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

/************** (C) COPYRIGHT megawin Technology Co., Ltd. *****END OF FILE****/
