/**
 ******************************************************************************
 *
 * @file        MG32x02z_WWDT_DRV.h
 *
 * @brief       This is the C code format driver head file for the WWDT module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.11
 * @date        2022/05/10
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************
 * @par 		Disclaimer 
 * The Demo software is provided "AS IS" without any warranty, either 
 * expressed or implied, including, but not limited to, the implied warranties 
 * of merchantability and fitness for a particular purpose. The author will 
 * not be liable for any special, incidental, consequential or indirect 
 * damages due to loss of data or any other reason. 
 * These statements agree with the world wide and local dictated laws about 
 * authorship and violence against these laws. 
 ******************************************************************************
 ******************************************************************************
 */ 
 
#include "MG32x02z__Common_DRV.h"
#include "MG32x02z_WWDT.h"

#ifndef _MG32x02z_WWDT_DRV_H
/*!< _MG32x02z_WWDT_DRV_H */ 
#define _MG32x02z_WWDT_DRV_H


/*! @name 
*/
/* @{ */ 
#define WWDT_RSTW       WWDT_CR0_RSTW_EN_mask_b0    /*!< WWDT reload counter out of window reset generation enable bit */
#define WWDT_RSTF       WWDT_CR0_RSTF_EN_mask_b0    /*!< WWDT timer underflow reset generation enable bit */

#define WWDT_WRNF       WWDT_STA_WRNF_mask_w                /*!< WWDT counter warning flag */
#define WWDT_WINF       WWDT_STA_WINF_mask_w                /*!< WWDT counter refreshing and value over the window compare threshold condition flag  */
#define WWDT_TF         WWDT_STA_TF_mask_w                  /*!< WWDT timer timeout interrupt flag */
#define WWDT_ALLF       (WWDT_WRNF | WWDT_WINF | WWDT_TF)   /*!< WWDT all flag */

#define WWDT_INT_WRN    WWDT_INT_WRN_IE_mask_w      /*!< WWDT counter warning interrupt enable */
#define WWDT_INT_WIN    WWDT_INT_WIN_IE_mask_w      /*!< WWDT counter refreshing and value over the window compare threshold condition interrupt enable */
#define WWDT_INT_TF     WWDT_INT_TIE_mask_w         /*!< WWDT timer timeout interrupt enable */
/* @} */



/*! @enum   WWDT_CLKS_TypeDef
    @brief  WWDT input clock select
*/
typedef enum   
{
    WWDT_CK_APB     = 0,    /*!< WWDT clock source select CK_APB */
    WWDT_CK_UT      = 1     /*!< WWDT clock source select UT */
}WWDT_CLKS_TypeDef;


/*! @enum   WWDT_DIVS_TypeDef
    @brief  WWDT internal clock CK_WWDT_INT input divider
*/
typedef enum
{   
    WWDT_DIV_1      = 0,    /*!< Select clock divided by 1 */
    WWDT_DIV_2      = 1,    /*!< Select clock divided by 2 */
    WWDT_DIV_4      = 2,    /*!< Select clock divided by 4 */
    WWDT_DIV_8      = 3,    /*!< Select clock divided by 8 */
    WWDT_DIV_16     = 4,    /*!< Select clock divided by 16 */
    WWDT_DIV_32     = 5,    /*!< Select clock divided by 32 */
    WWDT_DIV_64     = 6,    /*!< Select clock divided by 64 */
    WWDT_DIV_128    = 7     /*!< Select clock divided by 128 */
}WWDT_DIVS_TypeDef;


/*! @enum   WWDT_PDIVS_TypeDef
    @brief  WWDT internal clock CK_WWDT_INT pre-divider valuer
*/
typedef enum
{
    WWDT_PDIV_1     = 0,    /*!< Select clock pre-divider by 1 */
    WWDT_PDIV_256   = 1     /*!< Select clock pre-divider by 256 */
}WWDT_PDIVS_TypeDef;


#ifdef __cplusplus
extern "C"{
#endif // __cplusplus


/**
 * @name	Function announce
 *
 */ 
void WWDT_CLK_Select(WWDT_CLKS_TypeDef WWDT_CLKS);
void WWDT_DIV_Select (WWDT_DIVS_TypeDef WWDT_DIVS);

void WWDT_PDIV_Select (WWDT_PDIVS_TypeDef WWDT_PDIVS);
void WWDT_Cmd (FunctionalState NewState);

uint16_t WWDT_GetCounter (void);
void WWDT_RefreshCounter (void);
uint16_t WWDT_GetReloadReg (void);
void WWDT_SetReloadReg (uint16_t WWDT_RLR);
uint16_t WWDT_GetWindowThreshold (void);
void WWDT_SetWindowThreshold (uint16_t WWDT_WIN);
uint16_t WWDT_GetWarningThreshold (void);
void WWDT_SetWarningThreshold (uint16_t WWDT_WRN);

void WWDT_RstEvent_Config (uint8_t WWDT_RSTGS, FunctionalState NewState);
uint32_t WWDT_GetAllFlagStatus (void);
DRV_Return WWDT_GetSingleFlagStatus (uint32_t WWDT_ITSrc);
void WWDT_ClearFlag (uint32_t WWDT_ITSrc);
void WWDT_IT_Config (uint32_t WWDT_ITSrc, FunctionalState NewState);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif  //_MG32x02z_WWDT_DRV_H


