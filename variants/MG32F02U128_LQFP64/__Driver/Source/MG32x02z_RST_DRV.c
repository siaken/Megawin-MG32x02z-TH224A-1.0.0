/**
 ******************************************************************************
 *
 * @file        MG32x02z_RST_DRV.c
 *
 * @brief       This is the C code format driver file for RST module.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.16
 * @date        2022/08/25
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2021 Megawin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************
 * @par         Disclaimer 
 * The Demo software is provided "AS IS" without any warranty, either 
 * expressed or implied, including, but not limited to, the implied warranties 
 * of merchantability and fitness for a particular purpose. The author will 
 * not be liable for any special, incidental, consequential or indirect 
 * damages due to loss of data or any other reason. 
 * These statements agree with the world wide and local dictated laws about 
 * authorship and violence against these laws. 
 ******************************************************************************
 *******************************************************************************
 */ 

#include "MG32x02z_RST_DRV.h"


/**
 * @name    Reset Flag
 *  
 */
///@{
/**
 *******************************************************************************
 * @brief       Get all flag status
 * @details  
 * @return      RST status flag
 * @note
 * @par         Example
 * @code
    Status = RST_GetAllFlagStatus ();
 * @endcode
 *******************************************************************************
 */
uint32_t RST_GetAllFlagStatus (void)
{
    return RST_Base->STA.W;
}

/**
 *******************************************************************************
 * @brief       Get one flag status
 * @details  
 * @param[in]   RST_FLAG:
 * 	@arg\b          RST_PORF 
 * 	@arg\b          RST_SWF  
 * 	@arg\b          RST_EXF  
 * 	@arg\b          RST_CPUF 
 * 	@arg\b          RST_BOD0F
 * 	@arg\b          RST_BOD1F
 * 	@arg\b          RST_BOD2F (U128, U064, A128 and A064 Support)
 * 	@arg\b          RST_LPMF 
 * 	@arg\b          RST_CSCF 
 * 	@arg\b          RST_MEMF 
 * 	@arg\b          RST_IWDTF
 * 	@arg\b          RST_WWDTF
 * 	@arg\b          RST_ADCF 
 * 	@arg\b          RST_CMP0F
 * 	@arg\b          RST_CMP1F
 * 	@arg\b          RST_CMP2F (A132 and A072 Support)
 * 	@arg\b          RST_CMP3F (A132 and A072 Support)
 * 	@arg\b          RST_WRF  
 * 	@arg\b          RST_CRF  
 * @return      Return RST XXX flag status.
 * 	@arg\b          DRV_UnHappened
 * 	@arg\b          DRV_Happened
 * @note
 * @par         Example
 * @code
    Status = RST_GetSingleFlagStatus ();
 * @endcode
 *******************************************************************************
 */
DRV_Return RST_GetSingleFlagStatus (uint32_t RST_FLAG)                      
{                                                                           
    DRV_Return bitstatus = DRV_Normal;
    
    if ((RST_Base->STA.W & RST_FLAG) != (uint32_t)CLR)
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
 * @brief  	    Clear flag status
 * @details  
 * @param[in]   RST_FLAG:
 * 	@arg\b			RST_PORF 
 * 	@arg\b			RST_SWF  
 * 	@arg\b			RST_EXF  
 * 	@arg\b			RST_CPUF 
 * 	@arg\b			RST_BOD0F
 * 	@arg\b			RST_BOD1F
 * 	@arg\b			RST_BOD2F (U128, U064, A128 and A064 Support)
 * 	@arg\b			RST_LPMF 
 * 	@arg\b			RST_CSCF 
 * 	@arg\b			RST_MEMF 
 * 	@arg\b			RST_IWDTF
 * 	@arg\b			RST_WWDTF
 * 	@arg\b			RST_ADCF 
 * 	@arg\b			RST_CMP0F
 * 	@arg\b			RST_CMP1F
 * 	@arg\b			RST_CMP2F (A132 and A072 Support)
 * 	@arg\b			RST_CMP3F (A132 and A072 Support)
 * 	@arg\b			RST_WRF  
 * 	@arg\b			RST_CRF  
 * 	@arg\b			RST_ALLF 
 * @return      
 * @note
 * @par         Example
 * @code
    RST_ClearFlag (RST_PORF | RST_SWF);
 * @endcode
 *******************************************************************************
 */
void RST_ClearFlag (uint32_t RST_FLAG)
{
    RST_Base->STA.W = RST_FLAG;
}
///@}


/**
 * @name    Warm Reaet & Cold Reset
 *
 */ 
///@{
/**
 *******************************************************************************
 * @brief       Cold reset source config
 * @details  
 * @param[in]   RST_CRS:
 * 	@arg\b          RST_SW_CE.
 * 	@arg\b          RST_EX_CE.
 * 	@arg\b          RST_CPU_CE.
 * 	@arg\b          RST_BOD0_CE.
 * 	@arg\b          RST_BOD1_CE.
 * 	@arg\b          RST_BOD2_CE. (U128, U064, A128 and A064 Support)
 * 	@arg\b          RST_LPM_CE.
 * 	@arg\b          RST_CSC_CE.
 * 	@arg\b          RST_MEM_CE.
 * 	@arg\b          RST_IWDT_CE.
 * 	@arg\b          RST_WWDT_CE.
 * 	@arg\b          RST_ADC_CE .
 * 	@arg\b          RST_CMP0_CE.
 * 	@arg\b          RST_CMP1_CE.
 * 	@arg\b          RST_CMP2_CE. (A132 and A072 Support)
 * 	@arg\b          RST_CMP3_CE. (A132 and A072 Support)
 * @param[in]   NewState
 * 	@arg\b          ENABLE.
 * 	@arg\b          DISABLE.
 * @return
 * @note
 * @par         Example
 * @code
    RST_CRstSource_Config((RST_SW_CE | RST_EX_CE), ENABLE);
 * @endcode
 *******************************************************************************
 */
void RST_CRstSource_Config (uint32_t RST_CRS, FunctionalState NewState) 
{
    uint32_t  Reg_32;
    
    Reg_32 = RST_Base->CE.W;
    
    // When NewState is ENABLE
    if(NewState != DISABLE)
    {
        Reg_32 |= RST_CRS;
    }

    // When NewState is DISABLE
    else
    {
        Reg_32 &= ~RST_CRS;
    }
    
    RST_Base->CE.W = Reg_32;
}

/**
 *******************************************************************************
 * @brief       Warm reset source config
 * @details  
 * @param[in]   RST_WRS:
 * 	@arg\b          RST_SW_WE.
 * 	@arg\b          RST_EX_WE.
 * 	@arg\b          RST_CPU_WE.
 * 	@arg\b          RST_BOD0_WE.
 * 	@arg\b          RST_BOD1_WE. 
 * 	@arg\b          RST_BOD2_WE. (U128, U064, A128 and A064 Support)
 * 	@arg\b          RST_LPM_WE.
 * 	@arg\b          RST_CSC_WE.
 * 	@arg\b          RST_MEM_WE.
 * 	@arg\b          RST_IWDT_WE.
 * 	@arg\b          RST_WWDT_WE.
 * 	@arg\b          RST_ADC_WE.
 * 	@arg\b          RST_CMP0_WE.
 * 	@arg\b          RST_CMP1_WE.
 * 	@arg\b          RST_CMP2_WE. (A132 and A072 Support)
 * 	@arg\b          RST_CMP3_WE. (A132 and A072 Support)
 * @param[in]   NewState
 * 	@arg\b          ENABLE.
 * 	@arg\b          DISABLE.
 * @return
 * @note
 * @par         Example
 * @code
    RST_WRstSource_Config((RTC_SW_WE | RTC_EX_WE), ENABLE);
 * @endcode
 *******************************************************************************
 */
void RST_WRstSource_Config (uint32_t RST_WRS, FunctionalState NewState) 
{
    uint32_t  Reg_32;
    
    Reg_32 = RST_Base->WE.W;
    
    // When NewState is ENABLE
    if(NewState != DISABLE)
    {
        Reg_32 |= RST_WRS;
    }

    // When NewState is DISABLE
    else
    {
        Reg_32 &= ~RST_WRS;
    }
    
    RST_Base->WE.W = Reg_32;
}
///@}


/**
 * @name    Pins Warm Reset
 *
 */ 
///@{
/**
 *******************************************************************************
 * @brief       Warm reset GPIO lock mode and status
 * @details  
 * @param[in]   RST_Px_DISx:
 * 	@arg\b          RST_PA_DIS0
 * 	@arg\b          RST_PA_DIS1
 * 	@arg\b          RST_PB_DIS0
 * 	@arg\b          RST_PB_DIS1
 * 	@arg\b          RST_PC_DIS0
 * 	@arg\b          RST_PC_DIS1
 * 	@arg\b          RST_PD_DIS0
 * 	@arg\b          RST_PD_DIS1
 * 	@arg\b          RST_PE_DIS0
 * 	@arg\b          RST_PE_DIS1
 * @param[in]   NewState:
 * 	@arg\b          ENABLE
 * 	@arg\b          DISABLE
 * @return
 * @note
 * @par         Example
 * @code
    RST_WRstGPIOLock_Config ((RST_PA_DIS0 | RST_PA_DIS1), ENABLE);
 * @endcode
 *******************************************************************************
 */
void RST_WRstGPIOLock_Config (uint32_t RST_Px_DISx, FunctionalState NewState)
{
    uint32_t  Reg;
    
    Reg = RST_Base->CR0.W;
    
    if(NewState == DISABLE)
    {
        Reg &= ~RST_Px_DISx; 
    }
    else
    {
        Reg |= RST_Px_DISx;
    }
    
    RST_Base->CR0.W = Reg;
    
}
///@}


/**
 * @name    Force Reset Peripheral
 *
 */ 
///@{
/**
 *******************************************************************************
 * @brief       xxx module software force reset config
 * @details  
 * @param[in]   ForceReset:
 * 	@arg\b          RST_FR_IOPA
 * 	@arg\b          RST_FR_IOPB
 * 	@arg\b          RST_FR_IOPC
 * 	@arg\b          RST_FR_IOPD
 * 	@arg\b          RST_FR_IOPE (A132/A072/A128/A064/U128/U064)
 * 	@arg\b          RST_FR_GPL 
 * 	@arg\b          RST_FR_EMB (A132/A072/A128/A064/U128/U064)
 * 	@arg\b          RST_FR_ADC0
 * 	@arg\b          RST_FR_CMP 
 * 	@arg\b          RST_FR_DAC (A132/A072/A128/A064/U128/U064)
 * 	@arg\b          RST_FR_RTC 
 * 	@arg\b          RST_FR_IWDT
 * 	@arg\b          RST_FR_WWDT
 * 	@arg\b          RST_FR_I2C0 (A132/A072/A128/A064/U128/U064)
 * 	@arg\b          RST_FR_I2C1
 * 	@arg\b          RST_FR_SPI0
 * 	@arg\b          RST_FR_URT0
 * 	@arg\b          RST_FR_URT1
 * 	@arg\b          RST_FR_URT2 (A132/A072/A128/A064/U128/U064)
 * 	@arg\b          RST_FR_URT3 (A132/A072)
 * 	@arg\b          RST_FR_URT4 (A128/A064/U128/U064)
 * 	@arg\b          RST_FR_URT5 (A128/A064/U128/U064)
 * 	@arg\b          RST_FR_URT6 (A128/A064/U128/U064)
 * 	@arg\b          RST_FR_URT7 (A128/A064/U128/U064)
 * 	@arg\b          RST_FR_TM00
 * 	@arg\b          RST_FR_TM01
 * 	@arg\b          RST_FR_TM10
 * 	@arg\b          RST_FR_TM16
 * 	@arg\b          RST_FR_TM20 (A132/A072/A128/A064/U128/U064)
 * 	@arg\b          RST_FR_TM26 (A132/A072/A128/A064/U128/U064)
 * 	@arg\b          RST_FR_TM36
 * @param[in]   NewState:
 * 	@arg\b          ENABLE
 * 	@arg\b          DISABLE
 * @return
 * @note
 * @par         Example
 * @code
    RST_ForceRstPeriph_SW (RST_FR_IOPA, ENABLE);
 * @endcode
 *******************************************************************************
 */
void RST_ForceRstPeriph_SW (RST_SoftForceReset_Type ForceReset, FunctionalState NewState)
{
    uint32_t  Reg;

    if(ForceReset < 32)
    {
        Reg = (0x00000001 << ForceReset);
        
        if(NewState != DISABLE)
        {
            RST_Base->AHB.W |= Reg;
        }
        else
        {
            RST_Base->AHB.W &= ~Reg;
        }
    }
    
    if((32 <=ForceReset) & (ForceReset < 64))
    {
        Reg = (0x00000001 << (ForceReset & 0x1F));
        
        if(NewState != DISABLE)
        {
            RST_Base->APB0.W |= Reg;
        }
        else
        {
            RST_Base->APB0.W &= ~Reg;
        }
    }
    
    if((64 <=ForceReset) & (ForceReset < 96))
    {
        Reg = (0x00000001 << (ForceReset & 0x1F));
        
        if(NewState != DISABLE)
        {
            RST_Base->APB1.W |= Reg;
        }
        else
        {
            RST_Base->APB1.W &= ~Reg;
        }
    }
}
///@}


/**
 * @name    Others
 *  
 */ 
///@{
/**
 *******************************************************************************
 * @brief       Software reset trigger
 * @details  
 * @param[in]   NewState:
 *  @arg\b          ENABLE 
 *  @arg\b          DISABLE  
 * @return      
 * @note
 * @par         Example
 * @code
    RST_TriggerSystemRst_SW (ENABLE);
 * @endcode
 *******************************************************************************
 */
void RST_TriggerSystemRst_SW (FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        RST_Base->CR0.B[0] |= RST_CR0_SW_EN_mask_b0;
    }
    else
    {
        RST_Base->CR0.B[0] &= ~RST_CR0_SW_EN_mask_b0;
    }
}

/**
 *******************************************************************************
 * @brief       WWDT warm reset mask
 * @details  
 * @param[in]   NewState:
 *  @arg\b          ENABLE (WWDT module can not reset by warm reset.) 
 *  @arg\b          DISABLE (WWDT module reset by warm reset.) 
 * @return      
 * @note
 * @par         Example
 * @code
    RST_WWDTWRstMask_Cmd (ENABLE);
 * @endcode
 *******************************************************************************
 */
void RST_WWDTWRstMask_Cmd (FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        RST_Base->CR0.B[3] |= RST_CR0_WWDT_WDIS_mask_b3;
    }
    else
    {
        RST_Base->CR0.B[3] &= ~RST_CR0_WWDT_WDIS_mask_b3;
    }
}

#if (defined(USB_TYPE))
/**
 *******************************************************************************
 * @brief       USB reset mode select
 * @details  
 * @param[in]   RST_USBResetMode:
 * 	@arg\b          RST_USB_ResetMode_All 
 * 	@arg\b          RST_USB_ResetMode_LV1 
 * @return      
 * @note
 * @par         Example
 * @code
    RST_USBRstMode_Select (RST_USB_ResetMode_All);
 * @endcode
 *******************************************************************************
 */
void RST_USBRstMode_Select (RST_USBResetMode_Type RST_USBResetMode)
{
    RST_Base->CR0.MBIT.USB_RCTL = RST_USBResetMode;
}
#endif
///@}


