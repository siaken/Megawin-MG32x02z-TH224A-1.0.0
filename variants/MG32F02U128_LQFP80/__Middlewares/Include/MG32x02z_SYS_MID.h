/**
 *******************************************************************************
 *
 * @file        MG32x02z_SYS_MID.h
 *
 * @brief       This is the h code format middleware file for SYS module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.03
 * @date        2022/01/04
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
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "MG32x02z.h"
#include "MG32x02z_SYS.h"
#include "MG32x02z_CONF_MID.h" 


#ifndef _MG32x02z_SYS_MID_H
/*!< _MG32x02z_SYS_MID_H */ 
#define _MG32x02z_SYS_MID_H


static uint32_t SYS_CHIP_BODY_TABLE[9] = {0x0005C008, 0x0005C000, 0x0004C001, 0x0005C010, 0x0005C020, 0x0005C021, 0x0005C028, 0x0005C029, 0x0005C017};

#define ChipBodyNumber          8       /*!< ChipBodyNumber = SYS_CHIP_BODY_TABLE - 1 */
#define MG32F02A132_ID          0x0000  /*!< MG32F02A132 ID     */
#define MG32F02A072_ID          0x0001  /*!< MG32F02A072 ID     */
#define MA862_ID                0x0002  /*!< MA862 ID           */
#define MG32F02A032_ID          0x0003  /*!< MG32F02A032 ID     */
#define MG32F02U128_ID          0x0004  /*!< MG32F02U128 ID     */
#define MG32F02U064_ID          0x0005  /*!< MG32F02U064 ID     */
#define MG32F02A128_ID          0x0006  /*!< MG32F02A128 ID     */
#define MG32F02A064_ID          0x0007  /*!< MG32F02A064 ID     */
#define MG32F02V032_ID          0x0008  /*!< MG32F02V032 ID     */
#define CHIP_BODY_ID_WRONG      0xFFFF  /*!< Chip body ID wrong */


/**
 * @name SYS_Interrupt_definition
 *      SYS Interrupt Definition
 */
//!@{
#define SYS_IT_IEA               SYS_INT_IEA_mask_w           /*!< SYS interrupt all enable */
//!@}


/**
 *******************************************************************************
 * @brief       Enable the specified SYS interrupts.
 * @details  
 * @param[in]   "__INTERRUPT__" specifies the interrupt source to enable.
 *              This parameter can be one of the following values:
 *  @arg\b          SYS_IT_IEA: System interrupt all enable
 *                  (RTC/IWDT/MEM/CSC/PW/APB/EMB)
 * @return      None
 * @note
 * @par         Example
 * @code
    __DRV_SYS_ENABLE_IT(SYS_IT_IEA);
 * @endcode
 *******************************************************************************
 */
#define __DRV_SYS_ENABLE_IT(__INTERRUPT__)  SET_BIT(SYS->INT.W, (__INTERRUPT__))


/**
 *******************************************************************************
 * @brief       Disable the specified SYS interrupts.
 * @details  
 * @param[in]   "__INTERRUPT__" specifies the interrupt source to enable.
 *              This parameter can be one of the following values:
 *  @arg\b          SYS_IT_IEA: System interrupt all enable
 *                  (RTC/IWDT/MEM/CSC/PW/APB/EMB)
 * @return      None
 * @note
 * @par         Example
 * @code
    __DRV_SYS_DISABLE_IT(SYS_IT_IEA);
 * @endcode
 *******************************************************************************
 */
#define __DRV_SYS_DISABLE_IT(__INTERRUPT__)  CLEAR_BIT(SYS->INT.W, (__INTERRUPT__))


#if defined(SYS_BKP0_BKP0_mask_w) 
#define __DRV_SYS_READ_BKP0              SYS->BKP0.W                         /*!< Read SYS_BKP0 */
#define __DRV_SYS_WRITE_BKP0(__VALUE__)  WRITE_REG(SYS->BKP0.W, __VALUE__)   /*!< Write SYS_BKP0 */
#endif


/**
 * @name    Function announce
 * @brief   SYS 
 */ 
//@{
uint16_t MID_SYS_GetChipBody (void);
//@}

#endif


