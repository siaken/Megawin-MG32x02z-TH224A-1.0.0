/**
 *******************************************************************************
 *
 * @file        MG32x02z_CFG_DRV.c
 *
 * @brief       This is the C code format driver file for CFG module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.15
 * @date        2021/01/22
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2021 Megawin Technology Co., Ltd.
 *              All rights reserved.
 *
 *******************************************************************************
 * @par         Disclaimer 
 * The Demo software is provided "AS IS"  without any warranty, either 
 * expressed or implied, including, but not limited to, the implied warranties 
 * of merchantability and fitness for a particular purpose.  The author will 
 * not be liable for any special, incidental, consequential or indirect 
 * damages due to loss of data or any other reason. 
 * These statements agree with the world wide and local dictated laws about 
 * authorship and violence against these laws. 
 *******************************************************************************
 *******************************************************************************
 */ 
 
#include "MG32x02z_CFG_DRV.h"


#if defined(MG32_1ST)
/**
 * @name    ADC Reference
 *
 */ 
///@{ 
/**
 *******************************************************************************
 * @brief       Get ADC0 reference voltage top level
 * @details  
 * @return      Return ADC reference Top
 * 	@arg\b          0~63
 * @note
 * @par         Example
 * @code
    ADC_Top = CFG_GetADC0RefTop();
 * @endcode
 *******************************************************************************
 */
uint8_t CFG_GetADC0RefTop (void)
{
    return (CFG->OR15.B[3] & ADC_RefTopMask);
}


/**
 *******************************************************************************
 * @brief       Set ADC0 reference voltage top level
 * @details  
 * @param[in]   ADC_REFT:
 *  @arg\b          0~63.
 * @return
 * @note
 * @par         Example
 * @code
    ADC_Top = 32;
    CFG_SetADC0RefTop(ADC_Top);
 * @endcode
 *******************************************************************************
 */
void CFG_SetADC0RefTop (uint8_t ADC_REFT)
{
    CFG->OR15.B[3] = (ADC_REFT & ADC_RefTopMask);
}


/**
 *******************************************************************************
 * @brief       Get ADC0 reference voltage Middle level
 * @details  
 * @return      Return ADC reference Middle	
 * 	@arg\b          0~63
 * @note
 * @par         Example
 * @code
    ADC_Middle = CFG_GetADC0RefMiddle();
 * @endcode
 *******************************************************************************
 */
uint8_t CFG_GetADC0RefMiddle (void)
{
    return (CFG->OR15.B[2] & ADC_RefMiddleMask);
}


/**
 *******************************************************************************
 * @brief       Set ADC0 reference voltage Middle level
 * @details  
 * @param[in]   ADC_REFM:
 *  @arg\b          0~63.
 * @return
 * @note
 * @par         Example
 * @code
    ADC_Middle = 32;
    CFG_SetADC0RefMiddle(ADC_Middle);
 * @endcode
 *******************************************************************************
 */
void CFG_SetADC0RefMiddle (uint8_t ADC_REFM)
{
    CFG->OR15.B[2] = (ADC_REFM & ADC_RefMiddleMask);
}


/**
 *******************************************************************************
 * @brief       Get ADC0 reference voltage Bottom level
 * @details  
 * @return      Return ADC reference Bottom	
 *  @arg\b          0~63
 * @note
 * @par         Example
 * @code
    ADC_Bottom = CFG_GetADC0RefBottom();
 * @endcode
 *******************************************************************************
 */
uint8_t CFG_GetADC0RefBottom (void)
{
    return (CFG->OR15.B[1] & ADC_RefBottomMask);
}


/**
 *******************************************************************************
 * @brief       Set ADC0 reference voltage Bottom level
 * @details  
 * @param[in]   ADC_REFB:
 *  @arg\b          0~63.
 * @return
 * @note
 * @par         Example
 * @code
    ADC_Bottom = 32;
    CFG_SetADC0RefBottom(ADC_Bottom);
 * @endcode
 *******************************************************************************
 */
void CFG_SetADC0RefBottom (uint8_t ADC_REFB)
{
    CFG->OR15.B[1] = (ADC_REFB & ADC_RefBottomMask);
}
///@}
#endif



/**
 * @name    Temp calibration
 *
 */ 
///@{
///@}






