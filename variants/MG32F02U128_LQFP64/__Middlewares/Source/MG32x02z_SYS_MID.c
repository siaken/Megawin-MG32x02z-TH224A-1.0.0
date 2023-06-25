/**
 *******************************************************************************
 *
 * @file        MG32x02z_SYS_MID.c
 *
 * @brief       This is the C code format middleware file for SYS module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.02
 * @date        2022/01/05
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
#include "MG32x02z_SYS_MID.h" 


/**
 *******************************************************************************
 * @brief       Get chip body
 * @details  
 * @return      Chip_ID
 *  @arg\b          MG32F02A132_ID
 *  @arg\b          MG32F02A072_ID
 *  @arg\b          MA862_ID
 *  @arg\b          MG32F02A032_ID
 *  @arg\b          MG32F02U128_ID
 *  @arg\b          MG32F02U064_ID
 *  @arg\b          MG32F02A128_ID
 *  @arg\b          MG32F02A064_ID
 *  @arg\b          MG32F02V032_ID
 *  @arg\b          CHIP_BODY_ID_WRONG
 * @note
 * @par         Example
 * @code
    if(MID_SYS_GetChipBody() == CHIP_BODY_ID_WRONG)
 * @endcode
 *******************************************************************************
 */
uint16_t MID_SYS_GetChipBody (void)
{
    uint32_t CHIP_ID = SYS->MID.W & 0x00FFFFFF;
    uint16_t CHIP_BODY = 0x0000;



    CHIP_BODY = ChipBodyNumber;
    do
    {   // Check CHIP BODY match
        if(SYS_CHIP_BODY_TABLE[CHIP_BODY] == CHIP_ID)
            break;
        CHIP_BODY --;
    }while(CHIP_BODY!= 0xFF);

    return CHIP_BODY;
}






