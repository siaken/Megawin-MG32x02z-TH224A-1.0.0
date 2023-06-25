/**
 *******************************************************************************
 *
 * @file        MG32x02z_SYS_DRV.c
 *
 * @brief       This is the C code format driver file for SYS module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.14
 * @date        2021/03/26
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2021 Megawin Technology Co., Ltd.
 *              All rights reserved.
 *
 *******************************************************************************
 * @par         Disclaimer
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
#include "MG32x02z_SYS_DRV.h"


/**
 * @name    Interrupt
 *
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief       Enable/Disable SYS all interrupt 
 * @details  
 * @param[in]   NewState:
 *  @arg\b          ENABLE.
 *  @arg\b          DISABLE.
 * @return
 * @note
 * @par         Example
 * @code
    SYS_ITEA_Cmd(ENABLE);
 * @endcode
 *******************************************************************************
 */
void SYS_ITEA_Cmd (FunctionalState NewState)
{
    if(NewState != DISABLE)
    {    
        SYS->INT.B[0] = 0x01; 
    }
    else
    {
        SYS->INT.B[0] = 0x00;
    }
}
///@}


/**
 * @name    Chip Manufacture Identification
 *
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief       Get chip manufacture identification code
 * @details  
 * @return      Return MID value
 * @note
 * @par         Example
 * @code
    ID = SYS_GetChipMID();
 * @endcode
 *******************************************************************************
 */
uint32_t SYS_GetChipMID (void)
{
    return SYS->MID.W;
}

///@}


/**
 * @name    Others
 *
 */ 
///@{
/**
 *******************************************************************************
 * @brief       Read SYS general purpose data register bits
 * @details  
 * @return      Return General purpose value
 * @note
 * @par         Example
 * @code
    Register = SYS_ReadGeneralReg();
 * @endcode
 *******************************************************************************
 */
uint8_t SYS_ReadGeneralReg (void)
{
    return SYS->CR0.B[2];
}

/**
 *******************************************************************************
 * @brief       Write SYS general purpose data register bits
 * @details  
 * @param[in]   SYS_Value:
 *  @arg\b          0~255.
 * @return
 * @note
 * @par         Example
 * @code
    SYS_WriteGeneralReg(0x55);
 * @endcode
 *******************************************************************************
 */
void SYS_WriteGeneralReg (uint8_t SYS_Value)
{
    SYS->CR0.B[2] = SYS_Value;
}

#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
/**
 *******************************************************************************
 * @brief       Read SYS backup register
 * @details  
 * @return      Return backup register value
 * @note
 * @par         Example
 * @code
    Register = SYS_ReadBackupReg();
 * @endcode
 *******************************************************************************
 */
uint32_t SYS_ReadBackupReg (void)
{
    return SYS->BKP0.W;
}

/**
 *******************************************************************************
 * @brief       Write SYS backup register
 * @details  
 * @param[in]   SYS_Value:
 * 	@arg\b          32bit register.
 * @return
 * @note
 * @par         Example
 * @code
    SYS_WriteBackupReg(0x01234567);
 * @endcode
 *******************************************************************************
 */
void SYS_WriteBackupReg (uint32_t SYS_Value)
{
    SYS->BKP0.W = SYS_Value;
}
#endif

///@}


