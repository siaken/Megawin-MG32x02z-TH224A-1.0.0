/**
 *******************************************************************************
 *
 * @file        MG32x02z_CFG_DRV.h
 *
 * @brief       This is the C code format driver head file for CFG module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.13
 * @date        2021/01/22
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2020 Megawin Technology Co., Ltd.
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

#include "MG32x02z__Common_DRV.h"
#include "MG32x02z_CFG.h"


/*! @name 
*/
/* @{ */ 
#define ADC_RefTopMask          CFG_OR15_ADC0_REFT_mask_b3      /*!<  */	
#define ADC_RefMiddleMask       CFG_OR15_ADC0_REFM_mask_b2      /*!<  */
#define ADC_RefBottomMask       CFG_OR15_ADC0_REFB_mask_b1      /*!<  */

#define CFG_TempHighCalMask      CFG_OR16_TEMP_CAL1_mask_h1      /*!<  */
#define CFG_TempLowCalMask      CFG_OR16_TEMP_CAL0_mask_h0      /*!<  */

#define CFG_PNDF        CFG_TST0_PNDF_mask_w        /*!<  */
#define CFG_DBLVRF      CFG_TST0_DBLVRF_mask_w      /*!<  */
#define CFG_LVRF0       CFG_TST0_LVRF0_mask_w       /*!<  */
#define CFG_DPORF       CFG_TST0_DPORF_mask_w       /*!<  */
#define CFG_POF2        CFG_TST0_POF2_mask_w        /*!<  */
#define CFG_POF1        CFG_TST0_POF1_mask_w        /*!<  */
#define CFG_POF0        CFG_TST0_POF0_mask_w        /*!<  */
#define CFG_ALLF        CFG_PNDF | CFG_DBLVRF | CFG_LVRF0 | CFG_DPORF | CFG_DPORF | CFG_POF2 | CFG_POF1 | CFG_POF0      /*!<  */

/* @} */


#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

/**
 * @name    Function announce
 *
 */ 
///@{
#if defined(MG32_1ST)
uint8_t CFG_GetADC0RefTop (void);
void CFG_SetADC0RefTop (uint8_t ADC_REFT);
uint8_t CFG_GetADC0RefMiddle (void);
void CFG_SetADC0RefMiddle (uint8_t ADC_REFM);
uint8_t CFG_GetADC0RefBottom (void);
void CFG_SetADC0RefBottom (uint8_t ADC_REFB);
#endif


uint32_t CFG_GetAllFlagStatus (void);
DRV_Return CFG_GetSingleFlagStatus (uint32_t CFG_ITSrc);
void CFG_ClearFlag (uint32_t CFG_ITSrc);
///@}

#ifdef __cplusplus
}
#endif // __cplusplus