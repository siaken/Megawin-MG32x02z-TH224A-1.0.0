/**
 *******************************************************************************
 *
 * @file        MG32x02z_IWDT_DRV.h
 *
 * @brief       This is the C code format driver head file for the IWDT module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.11
 * @date        2022/05/10
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2018 Megawin Technology Co., Ltd.
 *              All rights reserved.
 *
 *******************************************************************************
 * @par 		Disclaimer 
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
 
#include "MG32x02z__Common_DRV.h"
#include "MG32x02z_IWDT.h"

#ifndef _MG32x02z_IWDT_DRV_H
/*!< _MG32x02z_IWDT_DRV_H */ 
#define _MG32x02z_IWDT_DRV_H

 
/*! @name 
*/
/* @{ */ 
#define IWDT_EW1_WPEN    IWDT_CR0_EW1_WPEN_mask_w   /*!< IWDT detect IWDT_EW1F flag wakeup from STOP mode enable bit */
#define IWDT_EW0_WPEN    IWDT_CR0_EW0_WPEN_mask_w   /*!< IWDT detect IWDT_EW0F flag wakeup from STOP mode enable bit */
#define IWDT_TF_WPEN     IWDT_CR0_TF_WPEN_mask_w    /*!< IWDT detect IWDT_TF flag wakeup from STOP mode enable bit */

                
#define IWDT_EW1F   IWDT_STA_EW1F_mask_w                /*!< IWDT early wakeup-1 flag */
#define IWDT_EW0F   IWDT_STA_EW0F_mask_w                /*!< IWDT early wakeup-0 flag */
#define IWDT_TF     IWDT_STA_TF_mask_w                  /*!< IWDT timer timeout interrupt flag */
#define IWDT_ALLF   (IWDT_EW1F | IWDT_EW0F | IWDT_TF)   /*!< IWDT all flag */

#define IWDT_INT_EW1    IWDT_INT_EW1_IE_mask_w  /*!< IWDT early wakeup-1 interrupt enable */
#define IWDT_INT_EW0    IWDT_INT_EW0_IE_mask_w  /*!< IWDT early wakeup-0 interrupt enable */
#define IWDT_INT_TF     IWDT_INT_TIE_mask_w     /*!< IWDT timer timeout interrupt enable */
/* @} */

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

/*! @enum   IWDT_DIVS_TypeDef
    @brief  IWDT clcok divider selection.
*/
typedef enum   
{
    IWDT_DIV_1       = 0,   /*!< Select clock divided by 1 */
    IWDT_DIV_2       = 1,   /*!< Select clock divided by 2 */
    IWDT_DIV_4       = 2,   /*!< Select clock divided by 4 */
    IWDT_DIV_8       = 3,   /*!< Select clock divided by 8 */
    IWDT_DIV_16      = 4,   /*!< Select clock divided by 16 */
    IWDT_DIV_32      = 5,   /*!< Select clock divided by 32 */
    IWDT_DIV_64      = 6,   /*!< Select clock divided by 64 */
    IWDT_DIV_128     = 7,   /*!< Select clock divided by 128 */
    IWDT_DIV_256     = 8,   /*!< Select clock divided by 256 */
    IWDT_DIV_512     = 9,   /*!< Select clock divided by 512 */
    IWDT_DIV_1024    = 10,  /*!< Select clock divided by 1024 */
    IWDT_DIV_2048    = 11,  /*!< Select clock divided by 2048 */
    IWDT_DIV_4096    = 12   /*!< Select clock divided by 4096 */
}IWDT_DIVS_TypeDef;
                

/**
 * @name	Function announce
 *
 */ 
void IWDT_Divider_Select (IWDT_DIVS_TypeDef IWDT_DIVS);

uint8_t IWDT_GetCounter (void);
void IWDT_RefreshCounter (void);

void IWDT_StopModeWakeUpEvent_Config (uint32_t IWDT_WK, FunctionalState NewState);

void IWDT_Cmd (FunctionalState NewState);

uint32_t IWDT_GetAllFlagStatus (void);
DRV_Return IWDT_GetSingleFlagStatus (uint32_t IWDT_ITSrc);
void IWDT_ClearFlag (uint32_t IWDT_ITSrc);
void IWDT_IT_Config (uint32_t IWDT_ITSrc, FunctionalState NewState);


#ifdef __cplusplus
}
#endif // __cplusplus
 
#endif  //_MG32x02z_IWDT_DRV_H


