/**
 *******************************************************************************
 *
 * @file        MG32x02z_CSC_MID.c
 *
 * @brief       This is the C code format middleware file for CSC module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.06
 * @date        2022/06/22
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


/* Includes ------------------------------------------------------------------*/
#include "MG32x02z_CSC_MID.h"


/**
 * @name    Initialization and de-initialization functions
 *
 */ 
///@{
/**
 *******************************************************************************
 * @brief       Resets the CSC clock configuration to the default reset state.
 * @note        The default reset state of the clock configuration is given below:
 *                - system clock source is CK_IHRCO or CK_ILRCO
 *                - PLL OFF
 *                - When CK_LS not use CK_XOSC or CK_EXT, disable both
 *                - CK_AHB, CK_APB prescaler set to 1
 *                - MCD ON
 *                - ICKO OFF
 *                - All interrupts disabled
 * @note        This function doesn't modify the configuration of the
 *                - Peripheral clocks  
 *                - CK_ILRCO, CK_LS and RTC clocks 
 * @details  
 * @return
 * @note
 * @par         Example
 * @code
    MID_CSC_DeInit ();
 * @endcode
 *******************************************************************************
 */
void MID_CSC_DeInit (void)
{

    // Unprotect CSC reigster
    CSC->KEY.H[0] = 0xA217;
    
    // When CK_HS default setting CK_IHRCO
#if defined(MG321ST) 
    // When CK_HS default setting CK_IHRCO
    if((CFG->OR05.W & CFG_OR05_HS_SEL_mask_w) == CFG_OR05_HS_SEL_ihrco_w)
    {   
        // When IHRCO disable
        if((CSC->CR0.W & CSC_CR0_IHRCO_EN_mask_w) == CSC_CR0_IHRCO_EN_disable_w)
        {
            // Clear IHRCOF
            CSC->STA.W = CSC_STA_IHRCOF_mask_w;
            // Enable IHRCO
            CSC->CR0.W |= CSC_CR0_IHRCO_EN_enable_w;
            // Waiting IHRCOF happened
            while((CSC->STA.W & CSC_STA_IHRCOF_mask_w)== CSC_STA_IHRCOF_normal_w);
            // Clear IHRCOF
            CSC->STA.W = CSC_STA_IHRCOF_mask_w;
        }
    }
#endif

#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
    // When CK_HS default setting CK_IHRCO
    if((CFG->OR05.W & CFG_OR05_HS_SEL_mask_w) == CFG_OR05_HS_SEL_ihrco_w)
    {
        // When IHRCO_STA not ready
        if((CSC->STA.W & CSC_STA_IHRCO_STA_mask_w) == CSC_STA_IHRCO_STA_unready_w)
        {
            // Clear IHRCOF
            CSC->STA.W = CSC_STA_IHRCOF_mask_w;
            // Enable IHRCO
            CSC->CR0.W |= CSC_CR0_IHRCO_EN_enable_w;
            // Waiting IHRCOF happened
            while((CSC->STA.W & CSC_STA_IHRCO_STA_mask_w)== CSC_STA_IHRCO_STA_unready_w);
            // Clear IHRCOF
            CSC->STA.W = CSC_STA_IHRCOF_mask_w;
        }
    }
#endif     
    
    
    
    // MCD ON
    CSC->CR0.W &= ~CSC_CR0_MCD_DIS_mask_w;
    // ICKO OFF
    CSC->CKO.W &= ~CSC_CKO_CKO_EN_mask_w;
    // All interrupts disabled
    CSC->INT.W = 0x00000000;
    // Peripheral clocks not modify
    // CK_AHB, CK_APB prescaler set to 1.
    CSC->DIV.W &= ~(CSC_DIV_APB_DIV_mask_w | CSC_DIV_AHB_DIV_mask_w);  
    
    
    // system clock source is CK_IHRCO or CK_ILRCO
#if defined(MG32_1ST) 
    // When CK_MAIN switch to CK_HS
    if((CSC->CR0.W & CSC_CR0_MAIN_SEL_mask_w) != CSC_CR0_MAIN_SEL_ck_hs_w)
    {    
        // CK_MIN = CK_HS
        CSC->CR0.W &= ~CSC_CR0_MAIN_SEL_mask_w;
        /* Delay 200us */
    }
    
    // When CK_HS default source CK_IHRCO
    if((CFG->OR05.W & CFG_OR05_HS_SEL_mask_w) == CFG_OR05_HS_SEL_ihrco_w)
    {
        // When CK_HS not CK_IHRCO
        if((CSC->CR0.W & CSC_CR0_HS_SEL_mask_w) != CSC_CR0_HS_SEL_ihrco_w)
        {   
            // CSC CK_HS = CK_IHRCO
            CSC->CR0.W &= ~CSC_CR0_HS_SEL_mask_w;
            /* Delay 200us */
        }
    }
    // When CK_HS default source CK_ILRCO
    else
    {
        // When CK_HS not CK_ILRCO
        if((CSC->CR0.W & CSC_CR0_HS_SEL_mask_w) != CSC_CR0_HS_SEL_ilrco_w)
        {
            // CSC CK_HS = CK_ILRCO
            CSC->CR0.W = (CSC->CR0.W & ~CSC_CR0_HS_SEL_mask_w) | CSC_CR0_HS_SEL_ilrco_w;
            /* Delay 200us */
        }
    }
#endif
    
#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
    // Wh// When CK_MAIN switch to CK_HS
    if((CSC->CR0.W & CSC_CR0_MAIN_SEL_mask_w) != CSC_CR0_MAIN_SEL_ck_hs_w)
    { 
        // CK_MIN = CK_HS
        CSC->CR0.W &= ~CSC_CR0_MAIN_SEL_mask_w;
        // Wait CK_MAIN to CK_HS
        while((CSC->STA.W & CSC_STA_MAIN_STA_mask_w) != CSC_STA_MAIN_STA_ck_hs_w);
    }
    
    // When CK_HS default source CK_IHRCO
    if((CFG->OR05.W & CFG_OR05_HS_SEL_mask_w) == CFG_OR05_HS_SEL_ihrco_w)
    {
        // When CK_HS not CK_IHRCO
        if((CSC->CR0.W & CSC_CR0_HS_SEL_mask_w) != CSC_CR0_HS_SEL_ihrco_w)
        {   
            // CSC CK_HS = CK_IHRCO
            CSC->CR0.W &= ~CSC_CR0_HS_SEL_mask_w;
            // Waitting CK_HS = CK_IHRCO
            while((CSC->STA.W & CSC_STA_HS_STA_mask_w) != CSC_STA_HS_STA_ihrco_w);
            
        }
    }
    // When CK_HS default source CK_ILRCO
    else
    {
        // When CK_HS not CK_ILRCO
        if((CSC->CR0.W & CSC_CR0_HS_SEL_mask_w) != CSC_CR0_HS_SEL_ilrco_w)
        {
            // CSC CK_HS = CK_IHRCO
            CSC->CR0.W = (CSC->CR0.W & ~CSC_CR0_HS_SEL_mask_w) | CSC_CR0_HS_SEL_ilrco_w;
            // Waitting CK_HS = CK_ILRCO
            while((CSC->STA.W & CSC_STA_HS_STA_mask_w) != CSC_STA_HS_STA_ilrco_w);
        }
    }
#endif
    // Disable PLL
    CSC->CR0.W &= ~CSC_CR0_PLL_EN_mask_w;
    CSC->DIV.W = CSC->DIV.W & ~(CSC_DIV_PLLI_DIV_mask_w | CSC_DIV_PLLO_DIV_mask_w);
    
    // CK_ILRCO, CK_LS, CK_UT and RTC clock not modify 
    if((CSC->CR0.W & CSC_CR0_LS_SEL_mask_w) == CSC_CR0_LS_SEL_ilrco_w)
    {
        // CK_XOSC OFF
        IOMC->CR13.W &= ~PX_CR_AFS_mask_w;
        IOMC->CR14.W &= ~PX_CR_AFS_mask_w;
    }

    // Protect CSC reigster
    CSC->KEY.H[0] = 0x0000;
}
///@}


/**
 * @name    Initialization and de-initialization functions
 *  
 */ 
///@{
/**
 *******************************************************************************
 * @brief       MID CSC enable MCD
 * @details  
 * @param[in]   CSC_MCSSelect
 * 	@arg\b          MID_CSC_MCD_125us
 * 	@arg\b          MID_CSC_MCD_250us
 * 	@arg\b          MID_CSC_MCD_500us
 * 	@arg\b          MID_CSC_MCD_1ms
 * @return
 * @note
 * @par         Example
 * @code
    MID_CSC_EnableMCD(MID_CSC_MCD_125us);
 * @endcode
 *******************************************************************************
 */ 
void MID_CSC_EnableMCD (MID_CSC_MCD_SEL_TypeDef CSC_MCSSelect)
{
    CSC->CR0.W = (CSC->CR0.W & ~(MID_CSC_MCD_SEL_MASK | MID_CSC_MCD_DIS_MASK)) | (CSC_MCSSelect | MID_CSC_MCD_DIS_EN);
}
  

/**
 *******************************************************************************
 * @brief       MID CSC disable MCD
 * @details  
 * @return
 * @note
 * @par         Example
 * @code
    MID_CSC_DisableMCD();
 * @endcode
 *******************************************************************************
 */
void MID_CSC_DisableMCD (void)
{
    // Disable MCD fucntion
    CSC->CR0.W |=  MID_CSC_MCD_DIS_DIS;
}


/**
 *******************************************************************************
 * @brief       MID CSC ICKO Config
 * @details  
 * @param[in]   CSC_ICKOSource
 * 	@arg\b          MID_CSC_ICKO_CK_MAIN
 * 	@arg\b          MID_CSC_ICKO_CK_AHB
 * 	@arg\b          MID_CSC_ICKO_CK_APB
 * 	@arg\b          MID_CSC_ICKO_CK_HS
 * 	@arg\b          MID_CSC_ICKO_CK_LS
 * 	@arg\b          MID_CSC_ICKO_CK_XOSC
 * @param[in]   CSC_ICKODiv
 * 	@arg\b          MID_CSC_ICKO_DIV_1
 * 	@arg\b          MID_CSC_ICKO_DIV_2
 * 	@arg\b          MID_CSC_ICKO_DIV_4
 * 	@arg\b          MID_CSC_ICKO_DIV_8
 * @return
 * @note
 * @par         Example
 * @code
    MID_CSC_ICKOConfig(MID_CSC_ICKO_CK_MAIN, MID_CSC_ICKO_DIV_8);
 * @endcode
 *******************************************************************************
 */
void MID_CSC_ICKOConfig(MID_CSC_ICKO_Source_TypeDef CSC_ICKOSource, MID_CSC_ICKO_Div_TypeDef CSC_ICKODiv)
{
    // Check the parameters
    // Configure the MCO1 pin in alternate function mode
    IOMC->CR0.W = PX_CR_IOM_ppo_w | 
                  PX_CR_PU_disable_w | 
                  PX_CR_HS_enable_w | 
                  PX_CR_ODC_level0_w |
                  PX_CR_FDIV_bypass_w | 
                  PX_CR_INV_disable_w | 
                  PX_CR_AFS_af1_w;

    // Configure the ICKO clock source, divider
    CSC->CKO.W = (CSC->CKO.W & ~
                 (uint32_t)(MID_CSC_ICKO_CKO_SEL_MASK | MID_CSC_ICKO_DIV_MASK | MID_CSC_ICKO_EN_MASK)) | 
                 ((uint32_t)CSC_ICKOSource | 
                  (uint32_t)CSC_ICKODiv | 
                  (uint32_t)CSC_CKO_CKO_EN_enable_w);
}
///@}


/**
 * @name    CSC Get system and peripherals clocks frequency functions
 *
 */ 
///@{
/**
 *******************************************************************************
 * @brief       CSC get CK_IHRCO frequency
 * @details  
 * @return      Frequency:
 * 	@arg\b          0 (IHRCO disable).
 * 	@arg\b          12000000.
 * 	@arg\b          11059200.
 * @note
 * @par         Example
 * @code
    IHRCO_Frequency = MID_CSC_GetCK_IHRCOFreq();
 * @endcode
 *******************************************************************************
 */
uint32_t MID_CSC_GetCK_IHRCOFreq(void)
{
    // When IHRCO disable
    if((CSC->CR0.W & CSC_CR0_IHRCO_EN_mask_w) == 0)
        return 0;

    // When CK_IHRCO select IHRCO0
    if((CSC->CR0.W & CSC_IHRCO_SELECT) == 0)
        return 12000000UL; 
    // When CK_IHRCO select IHRCO1
    else
        return 11059200UL;
}


/**
 *******************************************************************************
 * @brief       CSC get CK_HS frequency
 * @details  
* @return       Frequency:
 * 	@arg\b          0 ("Enter XOSC Or External Clock Frequency" value wrong at MG32x02z_CSC_Init.h).
 * 	@arg\b          1 ~ n.
 * @note
 * @par         Example
 * @code
    CK_HS_Frequency = MID_CSC_GetCK_HSFreq();
 * @endcode
 *******************************************************************************
 */
uint32_t MID_CSC_GetCK_HSFreq(void)
{

    // When CK_HS = IHRCO
    if((CSC->CR0.W & CSC_CR0_HS_SEL_mask_w) == CSC_CR0_HS_SEL_ihrco_w)
    {
        // When IHRCO disable
        if((CSC->CR0.W & CSC_CR0_IHRCO_EN_mask_w) == 0)
            return 0;
        // When IHRCO select 12MHz
        if((CSC->CR0.W & CSC_CR0_IHRCO_SEL_mask_w) == 0)
            return 12000000UL;
        // WHen IHRCO select 11.0592MHz
        else
            return 11059200UL;
    }
    // When CK_HS = CK_XOSC
    else if((CSC->CR0.W & CSC_CR0_HS_SEL_mask_w) == CSC_CR0_HS_SEL_xosc_w)
    {
        return CONF_XOSC_EXTCK_FREQ;
    }
    // When CK_HS = CK_ILRCO
    else if((CSC->CR0.W & CSC_CR0_HS_SEL_mask_w) == CSC_CR0_HS_SEL_ilrco_w)
    {
        return ILRCO_VALUE;
    }
    // When CK_HS = CK_EXT
    else if((CSC->CR0.W & CSC_CR0_HS_SEL_mask_w) == CSC_CR0_HS_SEL_ck_ext_w)
    {
        return CONF_XOSC_EXTCK_FREQ;
    }
    // When get CK_HS failure
    return 0;
}


#if defined(MG32_3RD) || defined(MG32_4TH)
/**
 *******************************************************************************
 * @brief       CSC get CK_HS2 frequency
 * @details  
* @return       Frequency:
 * 	@arg\b          0 ("Enter XOSC Or External Clock Frequency" value wrong at MG32x02z_CSC_Init.h).
 * 	@arg\b          1 ~ n.
 * @note
 * @par         Example
 * @code
    CK_HS_Frequency = MID_CSC_GetCK_HS2Freq();
 * @endcode
 *******************************************************************************
 */
uint32_t MID_CSC_GetCK_HS2Freq(void)
{

    // When CK_HS = IHRCO
    if((CSC->CR0.W & CSC_CR0_HS2_SEL_mask_w) == CSC_CR0_HS2_SEL_ihrco_w)
    {
        // When IHRCO disable
        if((CSC->CR0.W & CSC_CR0_IHRCO_EN_mask_w) == 0)
            return 0;
        // When IHRCO select 12MHz
        if((CSC->CR0.W & CSC_CR0_IHRCO_SEL_mask_w) == 0)
            return 12000000UL;
        // WHen IHRCO select 11.0592MHz
        else
            return 11059200UL;
    }
    // When CK_HS = CK_XOSC
    else if((CSC->CR0.W & CSC_CR0_HS2_SEL_mask_w) == CSC_CR0_HS2_SEL_xosc_w)
    {
        return CONF_XOSC_EXTCK_FREQ;
    }
    // When CK_HS = CK_EXT
    else if((CSC->CR0.W & CSC_CR0_HS2_SEL_mask_w) == CSC_CR0_HS2_SEL_ck_ext_w)
    {
        return CONF_XOSC_EXTCK_FREQ;
    }
    // When get CK_HS failure
    return 0;
}
#endif


/**
 *******************************************************************************
 * @brief       CSC get CK_PLLO frequency
 * @details  
 * @return      Frequency:
 * 	@arg\b          0 (PLL disable).
 *  @arg\b          10000000 ~ n.
 * @note
 * @par         Example
 * @code
    CK_PLLO_Frequency = MID_CSC_GetCK_PLLOFreq();
 * @endcode
 *******************************************************************************
 */
uint32_t MID_CSC_GetCK_PLLOFreq(void)
{   
    volatile uint32_t iTemp;

    
    // When CSC PLL disable
    if((CSC->CR0.W & CSC_CR0_PLL_EN_mask_w) == 0)
        return 0;
    
  #if defined(MG32_1ST) || defined(MG32_2ND)
    // When CK_HS frequency
    iTemp = MID_CSC_GetCK_HSFreq();
  #endif
    
  #if defined(MG32_3RD) || defined(MG32_4TH)
    // When CK_HS frequency 
    if((CSC->PLL.W & CSC_PLL_PLLI_SEL_mask_w) == CSC_PLL_PLLI_SEL_ck_hs_w)
        iTemp = MID_CSC_GetCK_HSFreq();
    // When CK_HS2 frequency 
    else
        iTemp = MID_CSC_GetCK_HS2Freq();
  #endif

    // When CK_PLLI = CK_HS /1
//    if((CSC->DIV.W & CSC_DIV_PLLI_DIV_mask_w) == CSC_DIV_PLLI_DIV_div1_w) 
//        __NOP();
    // When CK_PLLI = CK_HS /2
    if((CSC->DIV.W & CSC_DIV_PLLI_DIV_mask_w) == CSC_DIV_PLLI_DIV_div2_w) 
        iTemp = iTemp / 2;
    // When CK_PLLI = CK_HS /4
    if((CSC->DIV.W & CSC_DIV_PLLI_DIV_mask_w) == CSC_DIV_PLLI_DIV_div4_w) 
        iTemp = iTemp / 4;
    // When CK_PLLI = CK_HS /6
    if((CSC->DIV.W & CSC_DIV_PLLI_DIV_mask_w) == CSC_DIV_PLLI_DIV_div6_w) 
        iTemp = iTemp / 6;

    #if defined(MG32_1ST) || defined(MG32_2ND)
    // When CK_PLL = CK_PLLI * 16
    if((CSC->PLL.W & CSC_PLL_PLL_MUL_mask_w) == CSC_PLL_PLL_MUL_16_w) 
        iTemp = iTemp * 16;
    // When CK_PLL = CK_PLLI * 24
    if((CSC->PLL.W & CSC_PLL_PLL_MUL_mask_w) == CSC_PLL_PLL_MUL_24_w) 
        iTemp = iTemp * 24;
    #endif
    
    #if defined(MG32_3RD) || defined(MG32_4TH)
    iTemp = iTemp * (CSC->PLL.MBIT.PLL_MULX + 1);
    #endif

    // When CK_PLLO = CK_PLL /1
//    if((CSC->DIV.W & CSC_DIV_PLLO_DIV_mask_w) == CSC_DIV_PLLO_DIV_div1_w) 
//        __NOP();
    // When CK_PLLO = CK_PLL /2
    if((CSC->DIV.W & CSC_DIV_PLLO_DIV_mask_w) == CSC_DIV_PLLO_DIV_div2_w) 
        iTemp = iTemp / 2;
    // When CK_PLLO = CK_PLL /3
    if((CSC->DIV.W & CSC_DIV_PLLO_DIV_mask_w) == CSC_DIV_PLLO_DIV_div3_w) 
        iTemp = iTemp / 3;
    // When CK_PLLO = CK_PLL /4
    if((CSC->DIV.W & CSC_DIV_PLLO_DIV_mask_w) == CSC_DIV_PLLO_DIV_div4_w) 
        iTemp = iTemp / 4;

    // Return frequency
    return iTemp;
}



/**
 *******************************************************************************
 * @brief       CSC get CK_MAIN frequency
 * @details  
 * @return      Frequency:
 *  @arg\b          1 ~ n.
 * @note
 * @par         Example
 * @code
    CK_MAIN_Frequency = MID_CSC_GetCK_MAINFreq();
 * @endcode
 *******************************************************************************
 */
uint32_t MID_CSC_GetCK_MAINFreq(void)
{
    volatile uint32_t iTemp;

    
    // When CK_MAIN = CK_HS
    if((CSC->CR0.W & CSC_CR0_MAIN_SEL_mask_w) == CSC_CR0_MAIN_SEL_ck_hs_w)
        return MID_CSC_GetCK_HSFreq();
    
    // When CK_MAIN = CK_PLLI
    if((CSC->CR0.W & CSC_CR0_MAIN_SEL_mask_w) == CSC_CR0_MAIN_SEL_ck_plli_w)
    {
        // Get CK_HS frequency
        iTemp = MID_CSC_GetCK_HSFreq();
        // When CK_PLLI = CK_HS /2
        if((CSC->DIV.W & CSC_DIV_PLLI_DIV_mask_w) == CSC_DIV_PLLI_DIV_div2_w) 
            iTemp = iTemp / 2;
        // When CK_PLLI = CK_HS /4
        if((CSC->DIV.W & CSC_DIV_PLLI_DIV_mask_w) == CSC_DIV_PLLI_DIV_div4_w) 
            iTemp = iTemp / 4;
        // When CK_PLLI = CK_HS /6
        if((CSC->DIV.W & CSC_DIV_PLLI_DIV_mask_w) == CSC_DIV_PLLI_DIV_div6_w) 
            iTemp = iTemp / 6;

        // Return frequency
        return iTemp;
    }

    // When CK_MAIN = CK_PLLO
    if((CSC->CR0.W & CSC_CR0_MAIN_SEL_mask_w) == CSC_CR0_MAIN_SEL_ck_pllo_w)
        // Return CK_PLLO frequency 
        return MID_CSC_GetCK_PLLOFreq();

    // When get CK_MAIN failure
    return 0;
}


#if defined(USB_TYPE)
/**
 *******************************************************************************
 * @brief       CSC get CK_USB frequency
 * @details  
 * @return      Frequency:
 *  @arg\b          1 ~ n.
 * @note
 * @par         Example
 * @code
    CK_USB_Frequency = MID_CSC_GetCK_USBFreq();
 * @endcode
 *******************************************************************************
 */
uint32_t MID_CSC_GetCK_USBFreq (void)
{
    volatile uint32_t iTemp;

    
    // When CSC PLL disable
    if((CSC->CR0.W & CSC_CR0_PLL_EN_mask_w) == 0)
        return 0;
    
  #if defined(MG32_1ST) || defined(MG32_2ND)
    // When CK_HS frequency
    iTemp = MID_CSC_GetCK_HSFreq();
  #endif
    
  #if defined(MG32_3RD) || defined(MG32_4TH)
    // When CK_HS frequency 
    if((CSC->PLL.W & CSC_PLL_PLLI_SEL_mask_w) == CSC_PLL_PLLI_SEL_ck_hs_w)
        iTemp = MID_CSC_GetCK_HSFreq();
    // When CK_HS2 frequency 
    else
        iTemp = MID_CSC_GetCK_HS2Freq();
  #endif

    // When CK_PLLI = CK_HS /1
//    if((CSC->DIV.W & CSC_DIV_PLLI_DIV_mask_w) == CSC_DIV_PLLI_DIV_div1_w) 
//        __NOP();
    // When CK_PLLI = CK_HS /2
    if((CSC->DIV.W & CSC_DIV_PLLI_DIV_mask_w) == CSC_DIV_PLLI_DIV_div2_w) 
        iTemp = iTemp / 2;
    // When CK_PLLI = CK_HS /4
    if((CSC->DIV.W & CSC_DIV_PLLI_DIV_mask_w) == CSC_DIV_PLLI_DIV_div4_w) 
        iTemp = iTemp / 4;
    // When CK_PLLI = CK_HS /6
    if((CSC->DIV.W & CSC_DIV_PLLI_DIV_mask_w) == CSC_DIV_PLLI_DIV_div6_w) 
        iTemp = iTemp / 6;
    
    
    // When CK_PLL = CK_PLLI * (PLL_MULX + 1)
    iTemp = iTemp * (CSC->PLL.MBIT.PLL_MULX + 1);


    // When CK_USB = CK_PLL /1
//    if((CSC->DIV.W & CSC_DIV_USB_DIV_mask_w) == CSC_DIV_USB_DIV_div1_w) 
//        __NOP();
    // When CK_PLLO = CK_PLL /2
    if((CSC->DIV.W & CSC_DIV_USB_DIV_mask_w) == CSC_DIV_USB_DIV_div2_w) 
        iTemp = iTemp / 2;
    // When CK_PLLO = CK_PLL /3
    if((CSC->DIV.W & CSC_DIV_USB_DIV_mask_w) == CSC_DIV_USB_DIV_div3_w) 
        iTemp = iTemp / 3;
    // When CK_PLLO = CK_PLL /4
    if((CSC->DIV.W & CSC_DIV_USB_DIV_mask_w) == CSC_DIV_USB_DIV_div4_w) 
        iTemp = iTemp / 4;

    // Return frequency
    return iTemp;
}
#endif


/**
 *******************************************************************************
 * @brief       CSC get CK_APB frequency
 * @details  
 * @return      Frequency:
 *  @arg\b          1 ~ n.
 * @note
 * @par         Example
 * @code
    CK_APB_Frequency = MID_CSC_GetCK_APBFreq();
 * @endcode
 *******************************************************************************
 */
uint32_t MID_CSC_GetCK_APBFreq(void)
{
    volatile uint32_t iTemp32;
    
        
    // Get CK_MAIN frequency and divider APB
    iTemp32 = MID_CSC_GetCK_MAINFreq() >> CSC->DIV.MBIT.APB_DIV;
    // Return CK_APB frequency
    return iTemp32;
}


/**
 *******************************************************************************
 * @brief       CSC get CK_AHB frequency
 * @details  
 * @return      Frequency:
 *  @arg\b          1 ~ n.
 * @note
 * @par         Example
 * @code
    CK_AHB_Frequency = MID_CSC_GetCK_AHBFreq();
 * @endcode
 *******************************************************************************
 */
uint32_t MID_CSC_GetCK_AHBFreq(void)
{
    volatile uint32_t iTemp32;
    
    
    // Get CK_APB and divider AHB_DIV
    iTemp32 = MID_CSC_GetCK_APBFreq() >> CSC->DIV.MBIT.AHB_DIV;
    // Return CK_APB frequency
    return iTemp32;
}


/**
 *******************************************************************************
 * @brief       CSC get CK_LS frequency
 * @details  
 * @return      Frequency:
 * 	@arg\b          0 ("Enter XOSC Or External Clock Frequency" value wrong at MG32x02z_CSC_Init.h).
 *  @arg\b          1 ~ n.
 * @note
 * @par         Example
 * @code
    CK_LS_Frequency = MID_CSC_GetCK_LSFreq();
 * @endcode
 *******************************************************************************
 */
uint32_t MID_CSC_GetCK_LSFreq(void)
{
    // When CK_LS = CK_XOSC
    if((CSC->CR0.W & CSC_CR0_LS_SEL_mask_w) == CSC_CR0_LS_SEL_xosc_w)
    {
        return CONF_XOSC_EXTCK_FREQ;
    }
    // When CK_LS = CK_ILRCO
    else if((CSC->CR0.W & CSC_CR0_LS_SEL_mask_w) == CSC_CR0_LS_SEL_ilrco_w)
    {
        return ILRCO_VALUE;
    }
    // When CK_LS = CK_EXT
    else if((CSC->CR0.W & CSC_CR0_LS_SEL_mask_w) == CSC_CR0_LS_SEL_ck_ext_w)
    {
        return CONF_XOSC_EXTCK_FREQ;
    }
    // When get CK_LS failure
    return 0;
}


/**
 *******************************************************************************
 * @brief       CSC get CK_UT frequency
 * @details  
 * @return      Frequency:
 *  @arg\b          1 ~ n.
 * @note
 * @par         Example
 * @code
    CK_UT_Frequency = MID_CSC_GetCK_UTFreq();
 * @endcode
 *******************************************************************************
 */
uint32_t MID_CSC_GetCK_UTFreq(void)
{
    // When CK_UT = CK_ILRCO /32
    if((CSC->DIV.W & CSC_DIV_UT_DIV_mask_w) == CSC_DIV_UT_DIV_div32_w)
    {
        return ILRCO_VALUE / 32;
    }
    // When CK_UT = CK_ILRCO /8
    else if((CSC->DIV.W & CSC_DIV_UT_DIV_mask_w) == CSC_DIV_UT_DIV_div8_w)
    {
        return ILRCO_VALUE / 8;
    }
    // When CK_UT = CK_ILRCO /16
    else if((CSC->DIV.W & CSC_DIV_UT_DIV_mask_w) == CSC_DIV_UT_DIV_div16_w)
    {
        return ILRCO_VALUE / 16;
    }
    // When CK_UT = CK_ILRCO /128
    else if((CSC->DIV.W & CSC_DIV_UT_DIV_mask_w) == CSC_DIV_UT_DIV_div128_w)
    {
        return ILRCO_VALUE / 128;
    }
    // When Get CK_UT failure
    return 0;
}


/**
 *******************************************************************************
 * @brief       CSC get CK_UT frequency
 * @details  
 * @param[in]   Module:
 * 	@arg\b      MID_CSC_CK_PR_CORE.
 *  @arg\b      MID_CSC_CK_PR_DMA.  
 *  @arg\b      MID_CSC_CK_PR_USB.  
 *  @arg\b      MID_CSC_CK_PR_MEM.  
 *  @arg\b      MID_CSC_CK_PR_EMB.  
 *  @arg\b      MID_CSC_CK_PR_GPL.  
 *  @arg\b      MID_CSC_CK_PR_GPIOA.
 *  @arg\b      MID_CSC_CK_PR_GPIOB.
 *  @arg\b      MID_CSC_CK_PR_GPIOC.
 *  @arg\b      MID_CSC_CK_PR_GPIOD.
 *  @arg\b      MID_CSC_CK_PR_GPIOE.
 *  @arg\b      MID_CSC_CK_PR_GPIOF.
 *  @arg\b      MID_CSC_CK_PR_GPIOG.
 *  @arg\b      MID_CSC_CK_PR_GPIOH.
 *  @arg\b      MID_CSC_CK_PR_CMP.  
 *  @arg\b      MID_CSC_CK_PR_CMP0. 
 *  @arg\b      MID_CSC_CK_PR_CMP1.
 *  @arg\b      MID_CSC_CK_PR_ADC.  
 *  @arg\b      MID_CSC_CK_PR_ADC0. 
 *  @arg\b      MID_CSC_CK_PR_ADC1. 
 *  @arg\b      MID_CSC_CK_PR_DAC.  
 *  @arg\b      MID_CSC_CK_PR_DAC0. 
 *  @arg\b      MID_CSC_CK_PR_DAC1. 
 *  @arg\b      MID_CSC_CK_PR_IWDT. 
 *  @arg\b      MID_CSC_CK_PR_WWDT. 
 *  @arg\b      MID_CSC_CK_PR_RTC.  
 *  @arg\b      MID_CSC_CK_PR_TM00. 
 *  @arg\b      MID_CSC_CK_PR_TM01. 
 *  @arg\b      MID_CSC_CK_PR_TM10. 
 *  @arg\b      MID_CSC_CK_PR_TM16. 
 *  @arg\b      MID_CSC_CK_PR_TM20. 
 *  @arg\b      MID_CSC_CK_PR_TM26. 
 *  @arg\b      MID_CSC_CK_PR_TM36. 
 *  @arg\b      MID_CSC_CK_PR_URT0. 
 *  @arg\b      MID_CSC_CK_PR_URT1. 
 *  @arg\b      MID_CSC_CK_PR_URT2. 
 *  @arg\b      MID_CSC_CK_PR_URT3. 
 *  @arg\b      MID_CSC_CK_PR_SPI0. 
 *  @arg\b      MID_CSC_CK_PR_SPI1. 
 *  @arg\b      MID_CSC_CK_PR_SPI2. 
 *  @arg\b      MID_CSC_CK_PR_SPI3. 
 *  @arg\b      MID_CSC_CK_PR_I2C0. 
 *  @arg\b      MID_CSC_CK_PR_I2C1. 
 *  @arg\b      MID_CSC_CK_PR_I2C2. 
 *  @arg\b      MID_CSC_CK_PR_I2C3. 
 * @return      Frequency
 *  @arg\b          0 (Module is disabled).
 *  @arg\b          1 ~ n.
 * @note
 * @par         Example
 * @code
    CK_UT_Frequency = MID_CSC_GetCK_PRFreq(MID_CSC_CK_PR_GPIOA);
 * @endcode
 *******************************************************************************
 */
uint32_t MID_CSC_GetCK_PRFreq(uint32_t Module)
{
    uint32_t lTemp32 = 0;
    
    switch (Module)
    {   // When select CORE
        case MID_CSC_CK_PR_CORE:
        // When select DMA
            __NOP();
            break;
        case MID_CSC_CK_PR_DMA:
        // When select MEM
            __NOP();
            break;
        case MID_CSC_CK_PR_MEM:
            lTemp32 = MID_CSC_GetCK_AHBFreq();
            break;

      #if defined(CSC_AHB_EMB_EN_mask_w)
        // When select EMB
        case MID_CSC_CK_PR_EMB:
            // When EMB clock enable
            if((CSC->AHB.W & CSC_AHB_EMB_EN_mask_w) != 0)
                lTemp32 = MID_CSC_GetCK_AHBFreq();
            break;
      #endif
        // When select GPL
        case MID_CSC_CK_PR_GPL:
            // When GPL clock enable
            if((CSC->AHB.W & CSC_AHB_GPL_EN_mask_w) != 0)
                lTemp32 = MID_CSC_GetCK_AHBFreq();
            break;

      #if defined(USB_TYPE)
        // When select GPL
        case MID_CSC_CK_PR_USB:
            // When USB clock elable    
            lTemp32 = MID_CSC_GetCK_USBFreq();
            break;
      #endif

        // When select GPIOA
        case MID_CSC_CK_PR_GPIOA:
            // When GPIOA clock enable
            if((CSC->AHB.W & CSC_AHB_IOPA_EN_mask_w) != 0)
                lTemp32 = MID_CSC_GetCK_AHBFreq();
            break;

        // When select GPIOB
        case MID_CSC_CK_PR_GPIOB:
            // When GPIOB clock enable
            if((CSC->AHB.W & CSC_AHB_IOPB_EN_mask_w) != 0)
                lTemp32 = MID_CSC_GetCK_AHBFreq();
            break;

        // When select GPIOC
        case MID_CSC_CK_PR_GPIOC:
            // When GPIOC clock enable
            if((CSC->AHB.W & CSC_AHB_IOPC_EN_mask_w) != 0)
                lTemp32 = MID_CSC_GetCK_AHBFreq();
            break;

      #if defined(CSC_AHB_IOPD_EN_mask_w)
        // When select GPIOD
        case MID_CSC_CK_PR_GPIOD:
            // When GPIOD clock enable
            if((CSC->AHB.W & CSC_AHB_IOPD_EN_mask_w) != 0)
                lTemp32 = MID_CSC_GetCK_AHBFreq();
            break;
      #endif

      #if defined(CSC_AHB_IOPE_EN_mask_w)
        // When select GPIOE
        case MID_CSC_CK_PR_GPIOE:
            // When GPIOE clock enable
            if((CSC->AHB.W & CSC_AHB_IOPE_EN_mask_w) != 0)
                lTemp32 = MID_CSC_GetCK_AHBFreq();
            break;
      #endif

      #if defined(CSC_AHB_IOPF_EN_mask_w)
        // When select GPIOF
        case MID_CSC_CK_PR_GPIOF:
            // When GPIOF clock enable
            if((CSC->AHB.W & CSC_AHB_IOPF_EN_mask_w) != 0)
                lTemp32 = MID_CSC_GetCK_AHBFreq();
            break;
      #endif

      #if defined(CSC_AHB_IOPG_EN_mask_w)
        // When select GPIOG
        case MID_CSC_CK_PR_GPIOG:
            // When GPIOG clock enable
            if((CSC->AHB.W & CSC_AHB_IOPG_EN_mask_w) != 0)
                lTemp32 = MID_CSC_GetCK_AHBFreq();
            break;
      #endif

      #if defined(CSC_AHB_IOPH_EN_mask_w)
        // When select GPIOH
        case MID_CSC_CK_PR_GPIOH:
            // When GPIOH clock enable
            if((CSC->AHB.W & CSC_AHB_IOPH_EN_mask_w) != 0)
                lTemp32 = MID_CSC_GetCK_AHBFreq();
            break;
      #endif

      #if defined(CSC_APB0_CMP_EN_mask_w)
        // When select CMP
        case MID_CSC_CK_PR_CMP:
            // When CMP clock enable
            if((CSC->APB0.W & CSC_APB0_CMP_EN_mask_w) != 0)
            {   // When CMP clock select APB
                if((CSC->CKS0.W & CSC_CKS0_CMP_CKS_mask_w) == 0)
                    lTemp32 = MID_CSC_GetCK_APBFreq();
                // When CMP clock select AHB
                else
                    lTemp32 = MID_CSC_GetCK_AHBFreq();
            }
            break;
      #endif

        // When select ADC
        case MID_CSC_CK_PR_ADC0:
            // When ADC clock enable
            if((CSC->APB0.W & CSC_APB0_ADC0_EN_mask_w) != 0)
            {
                // When ADC clock select APB
                if((CSC->CKS0.W & CSC_CKS0_ADC0_CKS_mask_w) == 0)
                    lTemp32 = MID_CSC_GetCK_APBFreq();
                // When ADC clock select AHB
                else
                    lTemp32 = MID_CSC_GetCK_AHBFreq();
            }
            break;

      #if defined(CSC_APB0_DAC_EN_mask_w)
        // When select DAC
        case MID_CSC_CK_PR_DAC:
            if((CSC->APB0.W & CSC_APB0_DAC_EN_mask_w) != 0)
            {
                // When DAC clock select APB
                if((CSC->CKS0.W & CSC_CKS0_DAC_CKS_mask_w) == 0)
                    lTemp32 = MID_CSC_GetCK_APBFreq();
                // When DAC clock select AHB
                else
                    lTemp32 = MID_CSC_GetCK_AHBFreq();
            }
            break;
      #endif

        // When select IWDT
        case MID_CSC_CK_PR_IWDT:
            // When WWDT clock enable
            if((CSC->APB0.W & CSC_APB0_IWDT_EN_mask_w) != 0)
                lTemp32 = MID_CSC_GetCK_APBFreq();
            break;
            
        // When select WWDT
        case MID_CSC_CK_PR_WWDT:
            // When WWDT clock enable
            if((CSC->APB0.W & CSC_APB0_WWDT_EN_mask_w) != 0)
                lTemp32 = MID_CSC_GetCK_APBFreq();
            break;

        // When select RTC
        case MID_CSC_CK_PR_RTC:
            // When RTC clock enable
            if((CSC->APB0.W & CSC_APB0_RTC_EN_mask_w) != 0)
                lTemp32 = MID_CSC_GetCK_APBFreq();
            break;
            
      #if defined(CSC_APB0_APX_EN_mask_w)
        // When select APX
        case MID_CSC_CK_PR_APX:
            if((CSC->APB0.W & CSC_APB0_APX_EN_mask_w) != 0)
            {
                if((CSC->CKS0.W & CSC_CKS0_APX_CKS_mask_w) == 0)
                    lTemp32 = MID_CSC_GetCK_APBFreq();
                else
                    lTemp32 = MID_CSC_GetCK_AHBFreq();
            }
            break;
      #endif
            
        // When select TM00
        case MID_CSC_CK_PR_TM00:
            // When TM00 clock enable
            if((CSC->APB1.W & CSC_APB1_TM00_EN_mask_w) != 0)
            {   // When TM00 clock select APB
                if((CSC->CKS2.W & CSC_CKS2_TM00_CKS_mask_w) == 0)
                    lTemp32 = MID_CSC_GetCK_APBFreq();
                // When TM00 clock select AHB
                else
                    lTemp32 = MID_CSC_GetCK_AHBFreq();
            }
            break;

        // When select TM01
        case MID_CSC_CK_PR_TM01:
            // When TM01 clock enable
            if((CSC->APB1.W & CSC_APB1_TM01_EN_mask_w) != 0)
            {   // When TM01 clock select APB
                if((CSC->CKS2.W & CSC_CKS2_TM01_CKS_mask_w) == 0)
                    lTemp32 = MID_CSC_GetCK_APBFreq();
                // When TM01 clock select AHB
                else
                    lTemp32 = MID_CSC_GetCK_AHBFreq();
            }
            break;
            
        // When select TM10
        case MID_CSC_CK_PR_TM10:
            // When TM10 clock enable
            if((CSC->APB1.W & CSC_APB1_TM10_EN_mask_w) != 0)
            {   // When TM10 clock select APB
                if((CSC->CKS2.W & CSC_CKS2_TM10_CKS_mask_w) == 0)
                    lTemp32 = MID_CSC_GetCK_APBFreq();
                // When TM10 clock select AHB
                else
                    lTemp32 = MID_CSC_GetCK_AHBFreq();
            }
            break;

        // When select TM16
        case MID_CSC_CK_PR_TM16:
            // When TM16 clock enable
            if((CSC->APB1.W & CSC_APB1_TM16_EN_mask_w) != 0)
            {   // When TM16 clock select APB
                if((CSC->CKS2.W & CSC_CKS2_TM16_CKS_mask_w) == 0)
                    lTemp32 = MID_CSC_GetCK_APBFreq();
                // When TM16 clock select AHB
                else
                    lTemp32 = MID_CSC_GetCK_AHBFreq();
            }
            break;
      #if defined(CSC_APB1_TM20_EN_mask_w)
        // When select TM20
        case MID_CSC_CK_PR_TM20:
            // When TM20 clock enable
            if((CSC->APB1.W & CSC_APB1_TM20_EN_mask_w) != 0)
            {   // When TM20 clock select APB
                if((CSC->CKS2.W & CSC_CKS2_TM20_CKS_mask_w) == 0)
                    lTemp32 = MID_CSC_GetCK_APBFreq();
                // When TM20 clock select AHB
                else
                    lTemp32 = MID_CSC_GetCK_AHBFreq();
            }
            break;
      #endif
            
      #if defined(CSC_APB1_TM26_EN_mask_w)
        // When select TM26
        case MID_CSC_CK_PR_TM26:
            // When TM26 clock enable
            if((CSC->APB1.W & CSC_APB1_TM26_EN_mask_w) != 0)
            {   // When TM26 clock select APB
                if((CSC->CKS2.W & CSC_CKS2_TM26_CKS_mask_w) == 0)
                    lTemp32 = MID_CSC_GetCK_APBFreq();
                // When TM26 clock select AHB
                else
                    lTemp32 = MID_CSC_GetCK_AHBFreq();
            }
            break;
      #endif
      
        // When select TM36
        case MID_CSC_CK_PR_TM36:
            // When TM36 clock enable
            if((CSC->APB1.W & CSC_APB1_TM36_EN_mask_w) != 0)
            {   // When TM36 clock select APB
                if((CSC->CKS2.W & CSC_CKS2_TM36_CKS_mask_w) == 0)
                    lTemp32 = MID_CSC_GetCK_APBFreq();
                // When TM36 clock select AHB
                else
                    lTemp32 = MID_CSC_GetCK_AHBFreq();
            }
            break;

        // When select URT0
        case MID_CSC_CK_PR_URT0:  
            // When URT0 clock enable            
            if((CSC->APB0.W & CSC_APB0_URT0_EN_mask_w) != 0)
            {   // When URT0 clock select APB
                if((CSC->CKS1.W & CSC_CKS1_URT0_CKS_mask_w) == 0)
                    lTemp32 = MID_CSC_GetCK_APBFreq();
                // When URT0 clock select AHB
                else
                    lTemp32 = MID_CSC_GetCK_AHBFreq();
            }
            break;

        // When select URT1
        case MID_CSC_CK_PR_URT1:   
            // When URT1 clock enable  
            if((CSC->APB0.W & CSC_APB0_URT1_EN_mask_w) != 0)
            {   // When URT1 clock select APB
                if((CSC->CKS1.W & CSC_CKS1_URT1_CKS_mask_w) == 0)
                    lTemp32 = MID_CSC_GetCK_APBFreq();
                // When URT1 clock select AHB
                else
                    lTemp32 = MID_CSC_GetCK_AHBFreq();
            }
            break;

      #if defined(CSC_APB0_URT2_EN_mask_w)
        // When select URT2
        case MID_CSC_CK_PR_URT2:  
            // When URT2 clock enable  
            if((CSC->APB0.W & CSC_APB0_URT2_EN_mask_w) != 0)
            {   // When URT2 clock select APB
                if((CSC->CKS1.W & CSC_CKS1_URT2_CKS_mask_w) == 0)
                    lTemp32 = MID_CSC_GetCK_APBFreq();
                // When URT2 clock select AHB
                else
                    lTemp32 = MID_CSC_GetCK_AHBFreq();
            }
            break;
      #endif

      #if defined(CSC_APB0_URT3_EN_mask_w)
        // When select URT3
        case MID_CSC_CK_PR_URT3:   
            // When URT3 clock enable  
            if((CSC->APB0.W & CSC_APB0_URT3_EN_mask_w) != 0)
            {   // When URT3 clock select APB
                if((CSC->CKS1.W & CSC_CKS1_URT3_CKS_mask_w) == 0)
                    lTemp32 = MID_CSC_GetCK_APBFreq();
                // When URT3 clock select AHB
                else
                    lTemp32 = MID_CSC_GetCK_AHBFreq();
            }
            break;
      #endif
      
      #if defined(CSC_APB0_URT4_EN_mask_w)
        // When select URT4
        case MID_CSC_CK_PR_URT4:   
            // When URT4 clock enable  
            if((CSC->APB0.W & CSC_APB0_URT4_EN_mask_w) != 0)
            {   // When URT4 clock select APB
                if((CSC->CKS1.W & CSC_CKS1_URT4_CKS_mask_w) == 0)
                    lTemp32 = MID_CSC_GetCK_APBFreq();
                // When URT4 clock select AHB
                else
                    lTemp32 = MID_CSC_GetCK_AHBFreq();
            }
            break;
      #endif
            
            #if defined(CSC_APB0_URT5_EN_mask_w)
        // When select URT5
        case MID_CSC_CK_PR_URT5:   
            // When URT5 clock enable  
            if((CSC->APB0.W & CSC_APB0_URT5_EN_mask_w) != 0)
            {   // When URT5 clock select APB
                if((CSC->CKS1.W & CSC_CKS1_URT5_CKS_mask_w) == 0)
                    lTemp32 = MID_CSC_GetCK_APBFreq();
                // When URT5 clock select AHB
                else
                    lTemp32 = MID_CSC_GetCK_AHBFreq();
            }
            break;
      #endif
            
            #if defined(CSC_APB0_URT6_EN_mask_w)
        // When select URT6
        case MID_CSC_CK_PR_URT6:   
            // When URT6 clock enable  
            if((CSC->APB0.W & CSC_APB0_URT6_EN_mask_w) != 0)
            {   // When URT6 clock select APB
                if((CSC->CKS1.W & CSC_CKS1_URT6_CKS_mask_w) == 0)
                    lTemp32 = MID_CSC_GetCK_APBFreq();
                // When URT6 clock select AHB
                else
                    lTemp32 = MID_CSC_GetCK_AHBFreq();
            }
            break;
      #endif
            
            #if defined(CSC_APB0_URT7_EN_mask_w)
        // When select URT7
        case MID_CSC_CK_PR_URT7:   
            // When URT7 clock enable  
            if((CSC->APB0.W & CSC_APB0_URT7_EN_mask_w) != 0)
            {   // When URT7 clock select APB
                if((CSC->CKS1.W & CSC_CKS1_URT7_CKS_mask_w) == 0)
                    lTemp32 = MID_CSC_GetCK_APBFreq();
                // When URT7 clock select AHB
                else
                    lTemp32 = MID_CSC_GetCK_AHBFreq();
            }
            break;
      #endif

        // When select SPI0
        case MID_CSC_CK_PR_SPI0:     
            // When SPI0 clock enable  
            if((CSC->APB0.W & CSC_APB0_SPI0_EN_mask_w) != 0)
            {   // When SPI0 clock select APB
                if((CSC->CKS1.W & CSC_CKS1_SPI0_CKS_mask_w) == 0)
                    lTemp32 = MID_CSC_GetCK_APBFreq();
                // When SPI0 clock select AHB
                else
                    lTemp32 = MID_CSC_GetCK_AHBFreq();
            }
            break;

      #if defined(CSC_APB0_SPI1_EN_mask_w)
        // When select SPI1
        case MID_CSC_CK_PR_SPI1:    
            // When SPI1 clock enable
            if((CSC->APB0.W & CSC_APB0_SPI1_EN_mask_w) != 0)
            {   // When SPI1 clock select APB
                if((CSC->CKS1.W & CSC_CKS1_SPI1_CKS_mask_w) == 0)
                    lTemp32 = MID_CSC_GetCK_APBFreq();
                // When SPI1 clock select AHB
                else
                    lTemp32 = MID_CSC_GetCK_AHBFreq();
            }
            break;
      #endif

        // When select I2C0
        case MID_CSC_CK_PR_I2C0:   
            // When I2C0 clock enable
            if((CSC->APB0.W & CSC_APB0_I2C0_EN_mask_w) != 0)
            {   // When I2C0 clock select APB
                if((CSC->CKS1.W & CSC_CKS1_I2C0_CKS_mask_w) == 0)
                    lTemp32 = MID_CSC_GetCK_APBFreq();
                // When I2C0 clock select AHB
                else
                    lTemp32 = MID_CSC_GetCK_AHBFreq();
            }
            break;

    #if defined(CSC_APB0_I2C1_EN_mask_w)
        // When select I2C1
        case MID_CSC_CK_PR_I2C1:  
         
            // When I2C1 clock enable
            if((CSC->APB0.W & CSC_APB0_I2C1_EN_mask_w) != 0)
            {   // When I2C1 clock select APB
                if((CSC->CKS1.W & CSC_CKS1_I2C1_CKS_mask_w) == 0)
                    lTemp32 = MID_CSC_GetCK_APBFreq();
                // When I2C1 clock select AHB
                else
                    lTemp32 = MID_CSC_GetCK_AHBFreq();
            }
            
            break;
     #endif

      #if defined(CSC_APB0_I2C2_EN_mask_w)
        // When select I2C2
        case MID_CSC_CK_PR_I2C2:   
            // When I2C2 clock enable
            if((CSC->APB0.W & CSC_APB0_I2C3_EN_mask_w) != 0)
            {   // When I2C2 clock select APB
                if((CSC->CKS1.W & CSC_CKS1_I2C3_CKS_mask_w) == 0)
                    lTemp32 = MID_CSC_GetCK_APBFreq();
                // When I2C2 clock select AHB
                else
                    lTemp32 = MID_CSC_GetCK_AHBFreq();
            }
            break;
      #endif

      #if defined(CSC_APB0_I2C3_EN_mask_w)
        // When select I2C3
        case MID_CSC_CK_PR_I2C3:   
            // When I2C3 clock enable
            if((CSC->APB0.W & CSC_APB0_I2C3_EN_mask_w) != 0)
            {   // When I2C3 clock select APB
                if((CSC->CKS1.W & CSC_CKS1_I2C3_CKS_mask_w) == 0)
                    lTemp32 = MID_CSC_GetCK_APBFreq();
                // When I2C3 clock select AHB
                else
                    lTemp32 = MID_CSC_GetCK_AHBFreq();
            }
            break;
      #endif
      default:
              return(0);
    }
    return lTemp32;
}
///@}


/**
 *******************************************************************************
 * @brief       This function handles the MCD, XOSC, IHRCO, ILRCO and PLL 
 *              interrupt request.
 * @details  
 * @return      None
 * @note
 * @par         Example
 * @code
    MID_CSC_IRQHandler();
 * @endcode
 *******************************************************************************
 */
void MID_CSC_IRQHandler (void)
{
    uint32_t itsource = CSC->INT.W & ~CSC_INT_IEA_mask_w;
    uint32_t itflag   = CSC->STA.W;
    uint32_t itieflag   = (itsource & itflag);
    
    
                                                                                
    /* When MCD happened  ----------------------------------------------------*/
    if((itieflag & CSC_FLAG_MCDF) != CLR)
    {
        // Clear MCDF flag
        __DRV_CSC_CLEAR_FLAG(CSC_FLAG_MCDF);
        MID_CSC_MCDCallback();
        return;
    }
    
    /* When XOSC stable happened  ------------------------------------------- */
    if((itieflag & CSC_FLAG_XOSCF) != CLR)
    {
        // Clear XOSCF flag
        __DRV_CSC_CLEAR_FLAG(CSC_FLAG_XOSCF);
        MID_CSC_XOSCCallback();
        return;
    }
 
    /* When IHRCO stable happened --------------------------------------------*/
    if((itieflag & CSC_FLAG_IHRCOF) != CLR)
    {
        // Clear IHRCOF flag
        __DRV_CSC_CLEAR_FLAG(CSC_FLAG_IHRCOF);
        MID_CSC_IHRCOCallback();
        return;
    }

    /* When PLL stable happened ----------------------------------------------*/
    if((itieflag & CSC_FLAG_PLLF) != CLR)
    {
        // Clear PLLF flag
        __DRV_CSC_CLEAR_FLAG(CSC_FLAG_PLLF);
        MID_CSC_PLLCallback();
        return;
    }
    
    /* When ILRCO stable happened  -------------------------------------------*/
    if((itieflag & CSC_FLAG_ILRCOF) != CLR)
    {
        // Clear ILRCOF flag
        __DRV_CSC_CLEAR_FLAG(CSC_FLAG_ILRCOF);
        MID_CSC_ILRCOCallback();
        return;
    }
}


/**
 *******************************************************************************
 * @brief       Middle CSC MCD call back
 * @details  
 * @return      None
 * @note
 * @par         Example
 * @code
    MID_CSC_MCDCallback();
 * @endcode
 *******************************************************************************
 */
__weak void MID_CSC_MCDCallback (void)
{
    // To do ...
}


/**
 *******************************************************************************
 * @brief       Middle CSC XOSC call back
 * @details  
 * @return      None
 * @note
 * @par         Example
 * @code
    MID_CSC_XOSCCallback();
 * @endcode
 *******************************************************************************
 */
__weak void MID_CSC_XOSCCallback (void)
{
    // To do ...
}


/**
 *******************************************************************************
 * @brief       Middle CSC IHRCO call back
 * @details  
 * @return      None
 * @note
 * @par         Example
 * @code
    MID_CSC_IHRCOCallback();
 * @endcode
 *******************************************************************************
 */
__weak void MID_CSC_IHRCOCallback (void)
{
    // To do ...
}


/**
 *******************************************************************************
 * @brief       Middle CSC ILRCO call back
 * @details  
 * @return      None
 * @note
 * @par         Example
 * @code
    MID_CSC_ILRCOCallback();
 * @endcode
 *******************************************************************************
 */
__weak void MID_CSC_ILRCOCallback (void)
{
    // To do ...
}


/**
 *******************************************************************************
 * @brief       Middle CSC PLL call back
 * @details  
 * @return      None
 * @note
 * @par         Example
 * @code
    MID_CSC_PLLCallback();
 * @endcode
 *******************************************************************************
 */
__weak void MID_CSC_PLLCallback (void)
{
    // To do ...
}

