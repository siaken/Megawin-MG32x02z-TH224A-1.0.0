/**
 *******************************************************************************
 *
 * @file        MG32x02z_CSC_DRV.c
 *
 * @brief       This is the C code format driver file for CSC module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.25
 * @date        2021/08/11
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
 
#include "MG32x02z_CSC_DRV.h"



/**
 * @name    Clock Source
 *  
 */ 
///@{
/**
 *******************************************************************************
 * @brief  	    Enable or disable IHRCO circuit.
 * @details  
 * @param[in]   NewState:
 *  @arg\b          ENABLE.
 *  @arg\b          DISABLE.
 * @return
 * @note
 * @par         Example
 * @code
    CSC_IHRCO_Cmd(ENABLE);
 * @endcode
 *******************************************************************************
 */
void CSC_IHRCO_Cmd (FunctionalState NewState)
{
    uint8_t   Reg;
    
    Reg = CSC->CR0.B[0];
    
    if(NewState != DISABLE)
    {
        Reg |= CSC_CR0_IHRCO_EN_mask_b0;
    }
    else
    {
        Reg &= ~CSC_CR0_IHRCO_EN_mask_b0;
    }
    
    CSC->CR0.B[0] = Reg;
}

/**
 *******************************************************************************
 * @brief  	    CK_IHRCO clock source selction.
 * @details  
 * @param[in]   Freq:
 *  @arg\b          IHRCO_12MHz.
 *  @arg\b          IHRCO_11M0592Hz.
 * @return
 * @note
 * @par         Example
 * @code
    CSC_IHRCO_Select(IHRCO_12MHz);
 * @endcode
 *******************************************************************************
 */
void CSC_IHRCO_Select (CSC_IHRCO_TypeDef Freq)
{
    uint8_t   Reg;
    
    Reg = CSC->CR0.B[2];
    
    if(Freq != IHRCO_12MHz)
    {
        Reg |= CSC_CR0_IHRCO_SEL_mask_b2;
    }
    else
    {
        Reg &= ~CSC_CR0_IHRCO_SEL_mask_b2;
    }
    
    CSC->CR0.B[2] = Reg;
}	

/**
 *******************************************************************************
 * @brief       Enable or disable XOSC circuit.
 * @details  
 * @param[in]   NewState:
 *  @arg\b          ENABLE.
 *  @arg\b          DISABLE.
 * @return
 * @note
 * @par         Example
 * @code
    CSC_XOSC_Cmd(ENABLE);
 * @endcode
 *******************************************************************************
 */
void CSC_XOSC_Cmd (FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        GPIO_PinFunction_Select(PINC(13), 1);
        GPIO_PinFunction_Select(PINC(14), 1);
    }
    else
    {
        GPIO_PinFunction_Select(PINC(13), 0);
        GPIO_PinFunction_Select(PINC(14), 0);
    }
}

/**
 *******************************************************************************
 * @brief       CK_XOSC gain selction.
 * @details  
 * @param[in]   CSC_XoscGain:
 *  @arg\b          Gain_Low(for 32KHz crystal).
 *  @arg\b          Gain_Medium
 *  @arg\b          Gain_Lowest(for 32KHz crystal).
 * @return
 * @note
 * @par         Example
 * @code
    CSC_XOSCGain_Select(Gain_Lowest);
 * @endcode
 *******************************************************************************
 */
void CSC_XOSCGain_Select (CSC_XOSC_GN_TypeDef CSC_XoscGain)
{
    uint8_t   Reg;
    
    Reg = CSC->PLL.B[2];
    Reg &= ~CSC_PLL_XOSC_GN_mask_b2;
    Reg |= CSC_XoscGain;
    CSC->PLL.B[2] = Reg;
}

/**
 *******************************************************************************
 * @brief       CK_ST clock source selection
 * @details  
 * @param[in]   CSC_CK_ST_SEL:
 *  @arg\b          ST_HCLK_DIV_8.
 *  @arg\b          ST_CK_LS_DIV_2.
 * @return  
 * @note
 * @par         Example
 * @code
    CSC_CK_ST_Select(ST_CK_LS_DIV_2);
 * @endcode
 *******************************************************************************
 */
void CSC_CK_ST_Select (CSC_ST_SEL_TypeDef CSC_CK_ST_SEL)
{
    uint8_t   Reg;
    
    Reg = CSC->CR0.B[2];
    Reg &= ~CSC_CR0_ST_SEL_mask_b2;
    Reg |= CSC_CK_ST_SEL;
    CSC->CR0.B[2] = Reg;
}

/**
 *******************************************************************************
 * @brief       CK_MAIN clock source selection
 * @details  
 * @param[in]   CSC_CK_MAIN_SEL:
 *  @arg\b          MAIN_CK_HS.
 *  @arg\b          MAIN_CK_PLLI.
 *  @arg\b          MAIN_CK_PLLO
 * @return      None    
 * @note
 * @par         Example
 * @code
    CSC_CK_MAIN_Select(MAIN_CK_HS);
 * @endcode
 *******************************************************************************
 */
void CSC_CK_MAIN_Select (CSC_MAIN_SEL_TypeDef CSC_CK_MAIN_SEL)
{
    uint8_t   Reg;
    
    Reg = CSC->CR0.B[1];
    Reg &= ~CSC_CR0_MAIN_SEL_mask_b1;
    Reg |= CSC_CK_MAIN_SEL;
    CSC->CR0.B[1] = Reg;  
}    

/**
 *******************************************************************************
 * @brief       CK_HS clock source selection
 * @details  
 * @param[in]   CSC_CK_HS_SEL:
 *  @arg\b          HS_CK_IHRCO.
 *  @arg\b          HS_CK_XOSC.
 *  @arg\b          HS_CK_ILRCO
 *  @arg\b          HS_CK_EXT
 * @return
 * @note
 * @par         Example
 * @code
    CSC_CK_HS_Select(HS_CK_IHRCO);
 * @endcode
 *******************************************************************************
 */
void CSC_CK_HS_Select (CSC_HS_SEL_TypeDef CSC_CK_HS_SEL)
{
    uint8_t   Reg;
    
    Reg = CSC->CR0.B[1];
    Reg &= ~CSC_CR0_HS_SEL_mask_b1;
    Reg |= CSC_CK_HS_SEL;
    CSC->CR0.B[1] = Reg;
}

/**
 *******************************************************************************
 * @brief       CK_LS clock source selection
 * @details  
 * @param[in]   CSC_CK_LS_SEL:
 *  @arg\b          LS_CK_ILRCO.
 *  @arg\b          LS_CK_XOSC.
 *  @arg\b          LS_CK_EXT
 * @return
 * @note
 * @par         Example
 * @code
    CSC_CK_LS_Select(LS_CK_ILRCO);
 * @endcode
 *******************************************************************************
 */
void CSC_CK_LS_Select (CSC_LS_SEL_TypeDef CSC_CK_LS_SEL)
{
    uint8_t   Reg;
    
    Reg = CSC->CR0.B[1];
    Reg &= ~CSC_CR0_LS_SEL_mask_b1;
    Reg |= CSC_CK_LS_SEL;
    CSC->CR0.B[1] = Reg;   
}   

#if defined(MG32_3RD) || defined(MG32_4TH) 
/**
 *******************************************************************************
 * @brief       CK_HS2 clock source selection
 * @details  
 * @param[in]   CSC_CK_HS2_SEL:
 * 	@arg\b          HS_CK_IHRCO.
 * 	@arg\b          HS_CK_XOSC.
 * 	@arg\b          HS_CK_EXT
 * @return
 * @note
 * @par         Example
 * @code
    CSC_CK_HS2_Select(HS_CK_IHRCO);
 * @endcode
 *******************************************************************************
 */
void CSC_CK_HS2_Select (CSC_HS_SEL_TypeDef CSC_CK_HS2_SEL)
{
    uint8_t   Reg;
    
    
    Reg = CSC->CR0.B[1];
    Reg &= ~CSC_CR0_HS2_SEL_mask_b1;
    Reg |= (CSC_CK_HS2_SEL << 2);
    CSC->CR0.B[1] = Reg;
}
#endif
///@}


/**
 * @name    PLL
 *
 */ 
///@{
/**
 *******************************************************************************
 * @brief       PLL function config.
 * @details  
 * @param[in]   CSC_PLL_CFG
 *  @arg\b          InputDivider: Pll intout clock divider.
 *          \n  -PLLI_DIV_1.
 *          \n          -PLLI_DIV_2.
 *          \n          -PLLI_DIV_4.
 *          \n          -PLLI_DIV_6.
 *  @arg\b      Multiplication:
 *          \n          -PLLIx16: PLLI clock x 16 
 *          \n          -PLLIx24: PLLI clock x 24
 *          \n          -PLLI_CLKx4: PLLI clock x 4
 *          \n          ...
 *          \n          -PLLI_CLKx48: PLLI clock x 32
 *  @arg\b          OutputDivider:
 *          \n          -PLLO_DIV_1
 *          \n          -PLLO_DIV_2
 *          \n          -PLLO_DIV_3
 *          \n          -PLLO_DIV_4
 *  @arg\b          PLLInputClockSelect
 *                      -PLLI_SEL_HS
 *                      -PLLI_SEL_HS2
 * @return
 * @note
 * @par         Example 1
 * @code
    // For MG32F02A132/A072/A032 and MA862
    CSC_PLL_TypeDef CSC_PLL_Init;
    
    CSC_PLL_Init.InputDivider = PLLI_DIV_2;
    CSC_PLL_Init.Multiplication = PLLIx16;
    CSC_PLL_Init.OutputDivider = PLLO_DIV_4;
    CSC_PLL_Config(&CSC_PLL_Init);
 * @endcode
 * @par         Example 2
 * @code
    // For MG32F02A128/A064/U128/U064
    CSC_PLL_TypeDef CSC_PLL_Init;
    
    CSC_PLL_Init.InputDivider = PLLI_DIV_2;
    CSC_PLL_Init.Multiplication = PLLI_CLKx16;
    CSC_PLL_Init.OutputDivider = PLLO_DIV_4;
    CSC_PLL_Init.PLLInputClockSelect = PLLI_SEL_HS;
    CSC_PLL_Config(&CSC_PLL_Init);
 * @endcode
 *******************************************************************************
 */
void CSC_PLL_Config (CSC_PLL_TypeDef* CSC_PLL_CFG)
{
    uint16_t   Reg;

#if defined(MG32_1ST) || defined(MG32_2ND)
    Reg = CSC->PLL.H[0];                    // PLL MUL config
    Reg &= ~CSC_PLL_PLL_MUL_mask_h0;
    Reg |= CSC_PLL_CFG->Multiplication;
    CSC->PLL.H[0] = Reg;
    
    Reg = CSC->DIV.B[0];    // PLL0 DIV and PLL1 DIV config
    Reg &= ~(CSC_DIV_PLLO_DIV_mask_b0 | 
             CSC_DIV_PLLI_DIV_mask_b0); 
    
    Reg |= (uint8_t)(CSC_PLL_CFG->InputDivider) | 
           (uint8_t)(CSC_PLL_CFG->OutputDivider);
    
    CSC->DIV.B[0] = (uint8_t)(Reg);
#endif
    
#if defined(MG32_3RD) || defined(MG32_4TH)
    // PLL MUL config
    Reg = CSC->PLL.H[0];    
    Reg &= ~(CSC_PLL_PLL_MULX_mask_h0 |
             CSC_PLL_PLL_MUL_mask_h0 |
             CSC_PLL_PLL_VCOS_mask_h0 |
             CSC_PLL_PLL_LDEN_mask_h0 |
             CSC_PLL_PLLI_SEL_mask_h0 |
             CSC_PLL_PLL_MDS_mask_h0
            );
    Reg |= (CSC_PLL_CFG->Multiplication | 
            CSC_PLL_PLL_VCOS_low_h0 |
            CSC_PLL_PLL_LDEN_disable_h0 |
            CSC_PLL_CFG->PLLInputClockSelect | 
            CSC_PLL_PLL_MDS_mulx_h0
           );
    CSC->PLL.H[0] = Reg;
    
    // When PLLI select CK_HS
    if(CSC_PLL_CFG->PLLInputClockSelect == PLLI_SEL_HS)
    {
        while((CSC->STA.B[1] & CSC_STA_PLLI_STA_ck_hs_b1) == 0);
    }
    // When PLLI select CK_HS2
    else
    {
        while((CSC->STA.B[1] & CSC_STA_PLLI_STA_ck_hs2_b1) == 0);
    }
    
    // PLL0 DIV and PLL1 DIV config
    Reg = CSC->DIV.B[0];    
    Reg &= ~(CSC_DIV_PLLO_DIV_mask_b0 | 
             CSC_DIV_PLLI_DIV_mask_b0
            ); 
    Reg |= (uint8_t)(CSC_PLL_CFG->InputDivider) | 
           (uint8_t)(CSC_PLL_CFG->OutputDivider);
    CSC->DIV.B[0] = (uint8_t) (Reg);
#endif
}


/**
 *******************************************************************************
 * @brief       Enable or disable PLL function.
 * @details  
 * @param[in]   NewState:
 * 	@arg\b          ENABLE.
 * 	@arg\b          DISABLE.
 * @return
 * @note
 * @par         Example
 * @code
    CSC_PLL_Cmd(ENABLE);
 * @endcode
 *******************************************************************************
 */
void CSC_PLL_Cmd (FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        CSC->CR0.B[0] |= CSC_CR0_PLL_EN_mask_b0;
    }
    else
    {
        CSC->CR0.B[0] &= ~CSC_CR0_PLL_EN_mask_b0;
    }
}
///@}


/**
 * @name    Clock Divider
 *
 */ 
///@{
/**
 *******************************************************************************
 * @brief       CK_APB clock devider selection
 * @details  
 * @param[in]   CSC_CK_APB_DIVS:
 *  @arg\b          APB_DIV_1.
 *  @arg\b          APB_DIV_2.
 *  @arg\b          APB_DIV_4.
 *  @arg\b          APB_DIV_8.
 *  @arg\b          APB_DIV_16.
 * @return
 * @note
 * @par         Example
 * @code
    CSC_CK_APB_Divider_Select(APB_DIV_1);
 * @endcode
 *******************************************************************************
 */
void CSC_CK_APB_Divider_Select (CSC_APB_DIV_TypeDef CSC_CK_APB_DIVS)
{   
    uint8_t   Reg;
    
    Reg = CSC->DIV.B[2];
    Reg &= ~CSC_DIV_APB_DIV_mask_b2;
    Reg |= CSC_CK_APB_DIVS;
    CSC->DIV.B[2] = Reg;
}

/**
 *******************************************************************************
 * @brief       CK_UT clock devider selection
 * @details  
 * @param[in]   CSC_CK_UT_DIVS:
 *  @arg\b          UT_DIV_8.
 *  @arg\b          UT_DIV_16.
 *  @arg\b          UT_DIV_32.
 *  @arg\b          UT_DIV_128.
 * @return
 * @note
 * @par         Example
 * @code
    CSC_CK_UT_Divider_Select(UT_DIV_8);
 * @endcode
 *******************************************************************************
 */
void CSC_CK_UT_Divider_Select (CSC_UT_DIV_TypeDef CSC_CK_UT_DIVS)	
{
    uint8_t   Reg;
    
    Reg = CSC->DIV.B[3];
    Reg &= ~CSC_DIV_UT_DIV_mask_b3;
    Reg |= CSC_CK_UT_DIVS;
    CSC->DIV.B[3] = Reg;
}

/**
 *******************************************************************************
 * @brief       CK_AHB clock devider selection
 * @details  
 * @param[in]   CSC_CK_AHB_DIVS:
 *  @arg\b          AHB_DIV_1.
 *  @arg\b          AHB_DIV_2.
 *  @arg\b          AHB_DIV_4.
 *  @arg\b          AHB_DIV_8.
 *  @arg\b          AHB_DIV_16.
 *  @arg\b          AHB_DIV_32
 *  @arg\b          AHB_DIV_64
 *  @arg\b          AHB_DIV_128
 *  @arg\b          AHB_DIV_256
 *  @arg\b          AHB_DIV_512
 * @return
 * @note
 * @par         Example
 * @code
    CSC_CK_AHB_Divider_Select(AHB_DIV_1);
 * @endcode
 *******************************************************************************
 */
void CSC_CK_AHB_Divider_Select (CSC_AHB_DIV_TypeDef CSC_CK_AHB_DIVS)		
{
    uint8_t   Reg;
    
    Reg = CSC->DIV.B[1];
    Reg &= ~CSC_DIV_AHB_DIV_mask_b1;
    Reg |= CSC_CK_AHB_DIVS;
    CSC->DIV.B[1] = Reg;
}
///@}


/**
 * @name    ICKO
 *
 */ 
///@{  
/**
 *******************************************************************************
 * @brief       ICKO Clock Source Select
 * @details  
 * @param[in]   ICKO_CKS_SEL:
 *  @arg\b          ICKO_CK_MAIN.
 *  @arg\b          ICKO_CK_AHB.
 *  @arg\b          ICKO_CK_APB.
 *  @arg\b          ICKO_CK_HS.
 *  @arg\b          ICKO_CK_LS.
 *  @arg\b          ICKO_CK_XOSC.
 * @return      None
 * @exception   None
 * @note
 * @par         Example
 * @code
    CSC_ICKO_ClockSource_Select(ICKO_CK_HS);
 * @endcode
 *******************************************************************************
 */
void CSC_ICKO_ClockSource_Select (CSC_CKO_SEL_TypeDef ICKO_CKS_SEL)
{
    uint8_t   Reg;
    
    Reg = CSC->CKO.B[0];
    Reg &= ~CSC_CKO_CKO_SEL_mask_b0;
    Reg |= ICKO_CKS_SEL;
    CSC->CKO.B[0] = Reg;
}

/**
 *******************************************************************************
 * @brief       ICKO devider selection
 * @details  
 * @param[in]   CSC_ICKO_DIVS:
 *  @arg\b          ICKO_DIV_1.
 *  @arg\b          ICKO_DIV_2.
 *  @arg\b          ICKO_DIV_4.
 *  @arg\b          ICKO_DIV_8.
 * @return
 * @note
 * @par         Example
 * @code
    CSC_ICKO_Divider_Select(ICKO_DIV_8);
 * @endcode
 *******************************************************************************
 */
void CSC_ICKO_Divider_Select (CSC_CKO_DIV_TypeDef CSC_ICKO_DIVS)
{
    uint8_t   Reg;
    
    Reg = CSC->CKO.B[0];
    Reg &= ~CSC_CKO_CKO_DIV_mask_b0;
    Reg |= CSC_ICKO_DIVS;
    CSC->CKO.B[0] = Reg;
}

/**
 *******************************************************************************
 * @brief       Enable or disable IKCO function.
 * @details  
 * @param[in]   NewState:
 *  @arg\b          ENABLE.
 *  @arg\b          DISABLE.
 * @return
 * @note        
 * @par         Example
 * @code
    CSC_ICKO_Cmd(ENABLE);
 * @endcode
 *******************************************************************************
 */
void CSC_ICKO_Cmd (FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        CSC->CKO.MBIT.CKO_EN = SET;
    }
    else
    {
        CSC->CKO.MBIT.CKO_EN = CLR;
    }
}
///@}


/**
 * @name    Miss Clock Detect
 *
 */ 
///@{
/**
 *******************************************************************************
 * @brief       Missing Clock Detection Duration Select
 * @details  
 * @param[in]   CSC_MCDDuration:
 *  @arg\b          MCD_Duration_125us.
 *  @arg\b          MCD_Duration_250us.
 *  @arg\b          MCD_Duration_500us.
 *  @arg\b          MCD_Duration_1ms.
 * @return
 * @note
 * @par         Example
 * @code
    CSC_MissingClockDetectionDuration_Select(MCD_Duration_1ms);
 * @endcode
 *******************************************************************************
 */
void CSC_MissingClockDetectionDuration_Select (CSC_MCD_SEL_TypeDef CSC_MCDDuration)
{
    uint8_t   Reg;
    
    Reg = CSC->CR0.B[2];
    Reg &= 0x3F;
    Reg |= CSC_MCDDuration;
    CSC->CR0.B[2] = Reg;
}

/**
 *******************************************************************************
 * @brief       Enable or disable Missing clock detection.
 * @details  
 * @param[in]   NewState:
 * 	@arg\b          ENABLE.
 * 	@arg\b          DISABLE.
 * @return
 * @note
 * @par         Example
 * @code
    CSC_MissingClockDetection_Cmd(ENABLE);
 * @endcode
 *******************************************************************************
 */
void CSC_MissingClockDetection_Cmd (FunctionalState NewState)
{
    uint8_t   Reg;
    
    Reg = CSC->CR0.B[0];
    
    if(NewState != DISABLE)
    {
        Reg &= ~CSC_CR0_MCD_DIS_mask_b0;
    }
    else
    {
        Reg |= CSC_CR0_MCD_DIS_mask_b0;
    }
    
    CSC->CR0.B[0] = Reg;
}
///@}


/**
 * @name    Peripheral Clock Source & Clock Mode
 *
 */ 
///@{
/**
 *******************************************************************************
 * @brief       Periph clock source config.
 * @details  
 * @param[in]   CSC_Periph:
 *  @arg\b          CSC_ADC0_CKS
 *  @arg\b          CSC_CMP_CKS
 *  @arg\b          CSC_DAC_CKS (Support MG32F02A132/A072/A128/A064/U128/U064)
 *  @arg\b          CSC_APX_CKS
 *  @arg\b          CSC_I2C0_CKS
 *  @arg\b          CSC_I2C1_CKS (Support MG32F02A132/A072/A128/A064/U128/U064)
 *  @arg\b          CSC_SPI0_CKS
 *  @arg\b          CSC_UART0_CKS
 *  @arg\b          CSC_UART1_CKS
 *  @arg\b          CSC_UART2_CKS (Support MG32F02A132/A072/A128/A064/U128/U064)
 *  @arg\b          CSC_UART3_CKS (Support MG32F02A132/A072)
 *  @arg\b          CSC_UART4_CKS (Support MG32F02A128/A064/U128/U064)
 *  @arg\b          CSC_UART5_CKS (Support MG32F02A128/A064/U128/U064)
 *  @arg\b          CSC_UART6_CKS (Support MG32F02A128/A064/U128/U064)
 *  @arg\b          CSC_UART7_CKS (Support MG32F02A128/A064/U128/U064)
 *  @arg\b          CSC_TM00_CKS
 *  @arg\b          CSC_TM01_CKS
 *  @arg\b          CSC_TM10_CKS
 *  @arg\b          CSC_TM16_CKS
 *  @arg\b          CSC_TM20_CKS (Support MG32F02A132/A072/A128/A064/U128/U064)
 *  @arg\b          CSC_TM26_CKS (Support MG32F02A132/A072/A128/A064/U128/U064)
 *  @arg\b          CSC_TM36_CKS
 * @param[in]   CSC_CKS:
 *  @arg\b          CK_APB
 *  @arg\b          CK_AHB
 * @note
 * @par         Example
 * @code
    CSC_PeriphProcessClockSource_Config(CSC_CMP_CKS, CK_APB);
 * @endcode
 *******************************************************************************
 */
void CSC_PeriphProcessClockSource_Config (CSC_CKS_TypeDef CSC_Periph, CSC_CKSS_TypeDef CSC_CKS)
{
    uint32_t  Reg;
    
    Reg = 0x00000001;
    
    if(CSC_Periph < 32)                             // CKS0 Config
    {
        Reg = Reg << CSC_Periph;
        if(CSC_CKS == CK_APB)
        {
            CSC->CKS0.W &= ~Reg;
        }
        else
        {
            CSC->CKS0.W |= Reg;
        }
    }
    
    if((CSC_Periph >= 32) & (CSC_Periph < 64))      // CKS1 Config
    {
        CSC_Periph -= 32;
        Reg = Reg << CSC_Periph;
        
        if(CSC_CKS == CK_APB)
        {
            CSC->CKS1.W &= ~Reg;
        }
        else
        {
            CSC->CKS1.W |= Reg;
        }
    }
    
    if(CSC_Periph >= 64)                            // CKS0 Config
    {   
        CSC_Periph -= 64;
        Reg = Reg << CSC_Periph;
        
        if(CSC_CKS == CK_APB)
        {
            CSC->CKS2.W &= ~Reg;
        }
        else
        {
            CSC->CKS2.W |= Reg;
        }
    }
}

/**
 *******************************************************************************
 * @brief       Enable or disable AHB and APB Periph clock.
 * @details  
 * @param[in]   CSC_Periph:
 *  @arg\b          CSC_ON_PortA
 *  @arg\b          CSC_ON_PortB
 *  @arg\b          CSC_ON_PortC
 *  @arg\b          CSC_ON_PortD
 *  @arg\b          CSC_ON_PortE
 *  @arg\b          CSC_ON_GPL
 *  @arg\b          CSC_ON_EMB
 *  @arg\b          CSC_ON_DMA
 *  @arg\b          CSC_ON_ADC0
 *  @arg\b          CSC_ON_CMP
 *  @arg\b          CSC_ON_DAC (Support MG32F02A132/A072/A128/A064/U128/U064)
 *  @arg\b          CSC_ON_RTC
 *  @arg\b          CSC_ON_IWDT
 *  @arg\b          CSC_ON_WWDT
 *  @arg\b          CSC_ON_I2C0
 *  @arg\b          CSC_ON_I2C1 (Support MG32F02A132/A072/A128/A064/U128/U064)
 *  @arg\b          CSC_ON_SPI0
 *  @arg\b          CSC_ON_UART0
 *  @arg\b          CSC_ON_UART1
 *  @arg\b          CSC_ON_UART2 (Support MG32F02A132/A072/A128/A064/U128/U064)   
 *  @arg\b          CSC_ON_UART3 (Support MG32F02A132/A072)
 *  @arg\b          CSC_ON_UART4 (Support MG32F02A128/A064/U128/U064)
 *  @arg\b          CSC_ON_UART5 (Support MG32F02A128/A064/U128/U064)
 *  @arg\b          CSC_ON_UART6 (Support MG32F02A128/A064/U128/U064)
 *  @arg\b          CSC_ON_UART7 (Support MG32F02A128/A064/U128/U064)
 *  @arg\b          CSC_ON_USB (Support MG32F02A128/A064/U128/U064)
 *  @arg\b          CSC_ON_APX (Support MG32F02A128/A064/U128/U064)
 *  @arg\b          CSC_ON_TM00 
 *  @arg\b          CSC_ON_TM01
 *  @arg\b          CSC_ON_TM10
 *  @arg\b          CSC_ON_TM16
 *  @arg\b          CSC_ON_TM20 (Support MG32F02A132/A072/A128/A064/U128/U064)
 *  @arg\b          CSC_ON_TM26 (Support MG32F02A132/A072/A128/A064/U128/U064)
 *  @arg\b          CSC_ON_TM36
 * @param[in]   NewState:
 *  @arg\b          ENABLE.
 *  @arg\b          DISABLE.
 * @return
 * @note
 * @par         Example
 * @code
    CSC_PeriphONModeClock_Config(CSC_ON_PortC, ENABLE);
 * @endcode
 *******************************************************************************
 */
void CSC_PeriphONModeClock_Config (CSC_PeriphOnMode_TypeDef CSC_Periph, FunctionalState NewState)
{
    uint32_t  Reg;

    if(CSC_Periph < 32)                         // AHB Periph config
    {
        Reg = (0x00000001 <<  CSC_Periph);
        
        if(NewState != DISABLE)
        {
            CSC->AHB.W |= Reg;
        }
        else
        {
            CSC->AHB.W &= ~Reg;
        }
    }
    
    if((32 <= CSC_Periph) & (CSC_Periph < 64))  // APB0 Periph config
    {
        Reg = (0x00000001 << (CSC_Periph - 32));
        if(NewState != DISABLE)
        {
            CSC->APB0.W |= Reg;
        }
        else
        {
            CSC->APB0.W &= ~Reg;
        }
    }
    
    if((64 <= CSC_Periph) & (CSC_Periph < 96))  // APB1 Periph config
    {
        Reg = (0x00000001 << (CSC_Periph - 64));
        
        if(NewState != DISABLE)
        {
            CSC->APB1.W |= Reg;
        }
        else
        {
            CSC->APB1.W &= ~Reg;
        }
    }
}		

/**
 *******************************************************************************
 * @brief       Enable or disable SLEEP mode AHB and APB Periph clock.
 * @details  
 * @param[in]   CSC_Periph:
 *  @arg\b          CSC_SLP_ADC0
 *  @arg\b          CSC_SLP_CMP 
 *  @arg\b          CSC_SLP_DAC (Support MG32F02A132/A072/A128/A064/U128/U064)
 *  @arg\b          CSC_SLP_RTC 
 *  @arg\b          CSC_SLP_IWDT 
 *  @arg\b          CSC_SLP_WWDT 
 *  @arg\b          CSC_SLP_I2C0 
 *  @arg\b          CSC_SLP_I2C1 (Support MG32F02A132/A072/A128/A064/U128/U064)
 *  @arg\b          CSC_SLP_SPI0 
 *  @arg\b          CSC_SLP_UART0
 *  @arg\b          CSC_SLP_UART1
 *  @arg\b          CSC_SLP_UART2 (Support MG32F02A132/A072/A128/A064/U128/U064)
 *  @arg\b          CSC_SLP_UART3 (Support MG32F02A132/A072)
 *  @arg\b          CSC_SLP_UART4 (Support MG32F02A128/A064/U128/U064)
 *  @arg\b          CSC_SLP_UART5 (Support MG32F02A128/A064/U128/U064)
 *  @arg\b          CSC_SLP_UART6 (Support MG32F02A128/A064/U128/U064)
 *  @arg\b          CSC_SLP_UART7 (Support MG32F02A128/A064/U128/U064)
 *  @arg\b          CSC_SLP_USB (Support MG32F02A128/A064/U128/U064)
 *  @arg\b          CSC_SLP_APX (Support MG32F02A128/A064/U128/U064)
 *  @arg\b          CSC_SLP_TM00 
 *  @arg\b          CSC_SLP_TM01 
 *  @arg\b          CSC_SLP_TM10 
 *  @arg\b          CSC_SLP_TM16 
 *  @arg\b          CSC_SLP_TM20 (Support MG32F02A132/A072/A128/A064/U128/U064)
 *  @arg\b          CSC_SLP_TM26 (Support MG32F02A132/A072/A128/A064/U128/U064)
 *  @arg\b          CSC_SLP_TM36 
 *  @arg\b          CSC_SLP_SRAM (Support MG32F02A128/A064/U128/U064)
 *  @arg\b          CSC_SLP_FLASH (Support MG32F02A128/A064/U128/U064)
 *  @arg\b          CSC_SLP_DMA (Support MG32F02A128/A064/U128/U064)
 *  @arg\b          CSC_SLP_EMB (Support MG32F02A132/A072/A128/A064/U128/U064)
 * @param[in]   NewState:
 *  @arg\b          ENABLE.
 *  @arg\b          DISABLE.
 * @return
 * @note
 * @par         Example
 * @code
    CSC_PeriphSLEEPModeClock_Config(CSC_SLP_SPI0, ENABLE);
 * @endcode
 *******************************************************************************
 */
void CSC_PeriphSLEEPModeClock_Config (CSC_PeriphSleepMode_TypeDef CSC_Periph, FunctionalState NewState)
{
    uint32_t  Reg;
    
    if((32 <= CSC_Periph) & (CSC_Periph < 64))  // APB0 Periph config
    {
        Reg = (0x00000001 << (CSC_Periph - 32));
        if(NewState != DISABLE)
        {
            CSC->SLP0.W |= Reg;
        }
        else
        {
            CSC->SLP0.W &= ~Reg;
        }
    }
    
    if((64 <= CSC_Periph) & (CSC_Periph < 96))  // APB1 Periph config
    {
        Reg = (0x00000001 << (CSC_Periph - 64));
        
        if(NewState != DISABLE)
        {
            CSC->SLP1.W |= Reg;
        }
        else
        {
            CSC->SLP1.W &= ~Reg;
        }
    }
}			

/**
 *******************************************************************************
 * @brief       Enable or disable STOP mode AHB and APB Periph clock.
 * @details  
 * @param[in]   CSC_Periph:
 *  @arg\b          CSC_STP_RTC.         
 *  @arg\b          CSC_STP_IWDT. 
 * @param[in]   NewState:
 *  @arg\b          ENABLE.
 *  @arg\b          DISABLE.
 * @return
 * @note
 * @par         Example
 * @code
    CSC_PeriphSTOPModeClock_Config(CSC_STP_IWDT, ENABLE);
 * @endcode
 *******************************************************************************
 */
void CSC_PeriphSTOPModeClock_Config (CSC_PeriphStopMode_TypeDef CSC_Periph, FunctionalState NewState)
{
    uint32_t  Reg;
    
    Reg = (0x00000001 << (CSC_Periph - 32));
    if(NewState != DISABLE)
    {
        CSC->STP0.W |= Reg;
    }
    else
    {
        CSC->STP0.W &= ~Reg;
    }
}
///@}


/**
 * @name    Interrupt
 *
 */ 
///@{
/**
 *******************************************************************************
 * @brief       Get all intterupt source status.
 * @details    
 * @return      Return CSC status register value.
 * @note
 * @par         Example
 * @code
    Status = CSC_GetAllFlagStatus();
 * @endcode
 *******************************************************************************
 */
uint32_t CSC_GetAllFlagStatus (void)
{
    return CSC->STA.W;
}

#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
/**
 *******************************************************************************
 * @brief       Get clock soure ready state
 * @details  
 * @param[in]   CLK_SEL:
 *  @arg\b          CSC_PLL_STA.
 *  @arg\b          CSC_IHRCO_STA.       
 *  @arg\b          CSC_ILRCO_STA.     
 *  @arg\b          CSC_XOSC_STA.
 * @note
 * @par         Example
 * @code
    if(CSC_GetClockSourceState(CSC_IHRCO_STA) == DRV_Ready)
    {
        //To do......
    }
 * @endcode
 *******************************************************************************
 */
DRV_Return CSC_GetClockSourceState (uint32_t CLK_SEL)
{
    if((CSC->STA.W & CLK_SEL) == 0)
        return DRV_Unready;
    else
        return DRV_Ready;
}
#endif

#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
/**
 *******************************************************************************
 * @brief       Get MAIN MUX swtich state
 * @details  
 * @param[in]   MAIN_MUX_STA:
 *  @arg\b          MAIN_MUX_HS
 *  @arg\b          MAIN_MUX_PLLI
 *  @arg\b          MAIN_MUX_PLLO
 * @return      DRV_Return: Rerutn status. 
 *  @arg\b          DRV_Completed
 *  @arg\b          DRV_Busy
 * @return
 * @note
 * @par         Example
 * @code
    while(CSC_GetMainSwitchState(MAIN_MUX_HS) == DRV_Busy);
    
 * @endcode
 *******************************************************************************
 */
DRV_Return CSC_GetMainSwitchState (CSC_MAIN_MUX_STA_TypeDef MAIN_MUX_STA)
{
    if(CSC->STA.MBIT.MAIN_STA == MAIN_MUX_STA)
        return DRV_Completed;
    else
        return DRV_Busy;
}
#endif

#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
/**
 *******************************************************************************
 * @brief       Get HS MUX swtich state
 * @details  
 * @param[in]   HS_MUX_STA:
 *  @arg\b          HS_MUX_IHRCO
 *  @arg\b          HS_MUX_XOSC
 *  @arg\b          HS_MUX_ILRCO
 *  @arg\b          HS_MUX_CK_EXT
 * @return      DRV_Return: Rerutn status. 
 *  @arg\b          DRV_Completed
 *  @arg\b          DRV_Busy
 * @return
 * @note
 * @par         Example
 * @code
    while(CSC_GetHsSwitchState(HS_MUX_IHRCO) == DRV_Busy);
 * @endcode
 *******************************************************************************
 */
DRV_Return CSC_GetHsSwitchState (CSC_HS_MUX_STA_TypeDef HS_MUX_STA)
{
    if(CSC->STA.MBIT.HS_STA == HS_MUX_STA)
        return DRV_Completed;
    else
        return DRV_Busy;
}
#endif

#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
/**
 *******************************************************************************
 * @brief       Get LS MUX swtich state
 * @details  
 * @param[in]   LS_MUX_STA:
 *  @arg\b          LS_MUX_XOSC
 *  @arg\b          LS_MUX_ILRCO
 *  @arg\b          LS_MUX_CK_EXT
 * @return      DRV_Return: Rerutn status. 
 *  @arg\b          DRV_Completed
 *  @arg\b          DRV_Busy
 * @return
 * @note
 * @par         Example
 * @code
    while(CSC_GetLsSwitchSState(LS_MUX_ILRCO) == DRV_Busy);
 * @endcode
 *******************************************************************************
 */
DRV_Return CSC_GetLsSwitchState (CSC_LS_MUX_STA_TypeDef LS_MUX_STA)
{
    if(CSC->STA.MBIT.LS_STA == LS_MUX_STA)
        return DRV_Completed;
    else
        return DRV_Busy;
}
#endif

#if defined(MG32_3RD) || defined(MG32_4TH)
/**
 *******************************************************************************
 * @brief       Get HS2 MUX swtich state
 * @details  
 * @param[in]   HS2_MUX_STA:
 *  @arg\b          HS_MUX_IHRCO
 *  @arg\b          HS_MUX_XOSC
 *  @arg\b          HS_MUX_CK_EXT
 * @return      DRV_Return: Rerutn status. 
 *  @arg\b          DRV_Completed
 *  @arg\b          DRV_Busy
 * @return
 * @note
 * @par         Example
 * @code
    while(CSC_GetHS2SwitchState(HS_MUX_IHRCO) == DRV_Busy);
 * @endcode
 *******************************************************************************
 */
DRV_Return CSC_GetHS2SwitchState (CSC_HS_MUX_STA_TypeDef HS2_MUX_STA)
{
    if(CSC->STA.MBIT.HS2_STA == HS2_MUX_STA)
        return DRV_Completed;
    else
        return DRV_Busy;
}

/**
 *******************************************************************************
 * @brief       Get PLLI MUX swtich state
 * @details  
 * @param[in]   PLLI_MUX_STA:
 *  @arg\b          PLLI_MUX_HS
 *  @arg\b          PLLI_MUX_HS2
 * @return      DRV_Return: Rerutn status. 
 *  @arg\b          DRV_Completed
 *  @arg\b          DRV_Busy
 * @return
 * @note
 * @par         Example
 * @code
    while(CSC_GetPLLISwitchState(PLLI_MUX_HS) == DRV_Busy);
 * @endcode
 *******************************************************************************
 */
DRV_Return CSC_GetPLLISwitchState (CSC_PLLI_MUX_STA_TypeDef PLLI_MUX_STA)
{
    if(CSC->STA.MBIT.PLLI_STA == PLLI_MUX_STA)
        return DRV_Completed;
    else
        return DRV_Busy;
}
#endif

/**
 *******************************************************************************
 * @brief       Get one intterupt source status
 * @details  
 * @param[in]   CSC_ITSrc:
 *  @arg\b          CSC_MCDF.
 *  @arg\b          CSC_PLLF.       
 *  @arg\b          CSC_IHRCOF.     
 *  @arg\b          CSC_ILRCOF.     
 *  @arg\b          CSC_XOSCF.      
 * @return      DRV_Return: Rerutn CSC_ITSrc status. 
 *  @arg\b          DRV_Happened.
 *  @arg\b          DRV_UnHappened.
 * @note
 * @par         Example
 * @code
    Status = CSC_GetSingleFlagStatus(CSC_XOSCF);
 * @endcode
 *******************************************************************************
 */
DRV_Return CSC_GetSingleFlagStatus (uint32_t CSC_ITSrc)
{
    DRV_Return bitstatus = DRV_Normal;
    
    if ((CSC->STA.W & CSC_ITSrc) != (uint32_t)DISABLE)
    {
        bitstatus = DRV_Happened;
    }
    else
    {
        bitstatus = DRV_Normal;
    }
    return  bitstatus;
}

/**
 *******************************************************************************
 * @brief       Clear intterupt source state
 * @details  
 * @param[in]   CSC_ITSrc:
 *  @arg\b          CSC_MCDF.
 *  @arg\b          CSC_PLLF.       
 *  @arg\b          CSC_IHRCOF.     
 *  @arg\b          CSC_ILRCOF.     
 *  @arg\b          CSC_XOSCF.
 *  @arg\b          CSC_ALLF
 * @return
 * @note
 * @par         Example
 * @code
    CSC_ClearFlag(CSC_IHRCOF | CSC_ILRCOF);
 * @endcode
 *******************************************************************************
 */
void CSC_ClearFlag (uint32_t CSC_ITSrc)
{
    CSC->STA.W = CSC_ITSrc;
}

/**
 *******************************************************************************
 * @brief       config interrupt source
 * @details  
 * @param[in]   CSC_ITSrc:
 *  @arg\b          CSC_INT_MCD.
 *  @arg\b          CSC_INT_PLL.
 *  @arg\b          CSC_INT_IHRCO.
 *  @arg\b          CSC_INT_ILRCO.
 *  @arg\b          CSC_INT_XOSC.
 * @param[in]   NewState:
 *  @arg\b          ENABLE.
 *  @arg\b          DISABLE.
 * @return
 * @note
 * @par         Example
 * @code
    CSC_IT_Config((CSC_INT_MCD | CSC_INT_PLL), ENABLE);
 * @endcode
 *******************************************************************************
 */
void CSC_IT_Config (uint32_t CSC_ITSrc, FunctionalState NewState)
{
    uint32_t  Reg;
    
    Reg = CSC->INT.W;
    
    if(NewState != DISABLE)
    {
        Reg |= CSC_ITSrc;
    }
    else
    {
        Reg &= ~CSC_ITSrc;
    }
    CSC->INT.W = Reg;
}

/**
 *******************************************************************************
 * @brief       Enable/Disable all interrupt 
 * @details  
 * @param[in]   NewState:
 *  @arg\b          ENABLE.
 *  @arg\b          DISABLE.
 * @return
 * @note
 * @par         Example
 * @code
    CSC_ITEA_Cmd(ENABLE);
 * @endcode
 *******************************************************************************
 */
void CSC_ITEA_Cmd (FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        CSC->INT.MBIT.IEA = SET;
    }
    else
    {
        CSC->INT.MBIT.IEA = CLR;
    }
}
///@}


/**
 * @name    USB
 *          
 */ 
///@{
#if defined(MG32_3RD)
/**
 *******************************************************************************
 * @brief       USB SIE clock devider selection
 * @details  
 * @param[in]   CSC_USB_SIE_DIVS:
 *  @arg\b          USB_SIE_DIV_1.
 *  @arg\b          USB_SIE_DIV_2.
 *  @arg\b          USB_SIE_DIV_3.
 *  @arg\b          USB_SIE_DIV_4.
 * @return
 * @note
 * @par         Example
 * @code
    CSC_CK_USB_Divider_Select(USB_SIE_DIV_1);
 * @endcode
 *******************************************************************************
 */
void CSC_CK_USB_Divider_Select (CSC_USB_SIE_DIV_TypeDef CSC_USB_SIE_DIVS)
{   
    uint8_t   Reg;
    
    Reg = CSC->DIV.B[2];
    Reg &= ~CSC_DIV_USB_DIV_mask_b2;
    Reg |= CSC_USB_SIE_DIVS;
    CSC->DIV.B[2] = Reg;
}

/**
 *******************************************************************************
 * @brief       CSC USB SIE clock source selection
 * @details  
 * @param[in]   CSC_USB_CKS:
 *  @arg\b          CK_PLL.
 *  @arg\b          CK_SYS.
 * @return
 * @note
 * @par         Example
 * @code
    CSC_CK_USB_ClockSource_Select(CK_PLL);
 * @endcode
 *******************************************************************************
 */
void CSC_CK_USB_ClockSource_Select (CSC_USB_CKSS_TypeDef CSC_USB_CKS)
{
    uint8_t     Reg;
    
    Reg = CSC->CKS0.B[1];
    Reg &= CSC_CKS0_USB_CKS_mask_b1;
    Reg |= CSC_USB_CKS;
    CSC->CKS0.B[1] = Reg;
}
#endif
///@}








