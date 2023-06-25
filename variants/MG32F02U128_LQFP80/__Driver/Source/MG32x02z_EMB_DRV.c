/**
 ******************************************************************************
 *
 * @file        MG32x02z_EMB_DRV.c
 *
 * @brief       This is the C code format driver file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V2.23
 * @date        2021/09/07
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************
 * @par 		Disclaimer 
 *		The Demo software is provided "AS IS"  without any warranty, either 
 *		expressed or implied, including, but not limited to, the implied warranties 
 *		of merchantability and fitness for a particular purpose.  The author will 
 *		not be liable for any special, incidental, consequential or indirect 
 *		damages due to loss of data or any other reason. 
 *		These statements agree with the world wide and local dictated laws about 
 *		authorship and violence against these laws. 
 ******************************************************************************
 ******************************************************************************
 */ 



#include "MG32x02z_EMB_DRV.h"



/**
 * @name	Mode
 *   		EMB mode relationship driver.
 */ 
///@{

/**
 *******************************************************************************
 * @brief	    EMB function enable.
 * @details     
 * @param[in]   EMB_EN:  
 *  @arg\b      DISABLE: EMB control disable.
 *  @arg\b      ENABLE : EMB control enable.
 * @return      No
 * @exception   No
 * @note
 * @par         Example
 * @code
    EMB_Cmd(ENABLE);
 * @endcode
 *******************************************************************************
 */
__INLINE void EMB_Cmd(FunctionalState EMB_EN)
{
    EMB->CR0.MBIT.EN = EMB_EN;
}



#if defined(MG32_1ST)
/**
 *******************************************************************************
 * @brief       EMB synchronous transaction enable.
 * @details     
 * @param[in]   EMB_SYNC_Cmd:  
 *  @arg\b      DISABLE: Asynchonous access.
 *  @arg\b      ENABLE : Synchronous access.
 * @return      No
 * @exception   No
 * @note
 * @par         Example
 * @code
    EMB_Synchonous_Cmd(ENABLE);
 * @endcode
 *******************************************************************************
 */
__INLINE void EMB_Synchonous_Cmd(FunctionalState EMB_SYNC_Cmd)
{
    EMB->CR0.MBIT.SYNC_EN = EMB_SYNC_Cmd;
}
#endif



/**
 *******************************************************************************
 * @brief       EMB Address and Data Bus Mode Config.
 * @details     
 * @param[in]   EMB_AddressDataMode:  
 *  @arg\b      EMB_AddressBit: EMB address bit select.
 *      \n      -EMB_AddressBit_16  : EMB address is 16 bits.
 *      \n      -EMB_AddressBit_24  : EMB address is 24 bits.
 *      \n      -EMB_AddressBit_30  : EMB address is 30 bits.
 *  @arg\b      EMB_BusMode:    EMB bus address and data bus mode select.
 *      \n      -EMB_BUS_Multiplex  : 
 *      \n      -EMB_BUS_Separated  : 
 *  @arg\b      EMB_ALE2_EN: EMB two address phase timing mode enable or disable select.
 *      \n      -EMB_ALE2_DISABLE   : Disable. (If EMB_BusMode = EMB_BUS_Separated will be no address phase)
 *      \n      -EMB_ALE2_ENABLE    : Enable.  (If EMB_BusMode = EMB_BUS_Multiplex will be two address phase)
 *  @arg\b      EMB_ALE2Mode:
 *      \n      -EMB_ALE2Mode_ALE2  : 2nd phase address latch enable.
 *      \n      -EMB_ALE2Mode_ALE   : Same as ALE timing.
 * @return      No
 * @exception   No
 * @note
 * @par         Example
 * @code
    EMB_AddressDataTypeDef  EMB_AddressDataMode;
    
    EMB_AddressDataMode.EMB_AddressBit = EMB_AddressBit_16;
    EMB_AddressDataMode.EMB_BusMode = EMB_BUS_Multiplex;
    EMB_AddressDataMode.EMB_ALE2_EN = EMB_ALE2_ENABLE;
    EMB_AddressDataMode.EMB_ALE2Mode = EMB_ALE2Mode_ALE2;
    EMB_AddressDataBusMode_Config(&EMB_AddressDataMode);
    
                        or
    EMB_AddressDataTypeDef  EMB_AddressDataMode;
    
    EMB_AddressDataMode.EMB_AddressBit = EMB_AddressBit_16;
    EMB_AddressDataMode.EMB_BusMode = EMB_BUS_Multiplex;
    EMB_AddressDataMode.EMB_ALE2_EN = EMB_ALE2_DISABLE;
    EMB_AddressDataBusMode_Config(&EMB_AddressDataMode);    
 * @endcode
 *******************************************************************************
 */
void EMB_AddressDataBusMode_Config( EMB_AddressDataTypeDef* EMB_AddressDataMode)
{
    EMB->CR0.W = EMB->CR0.W & (~(EMB_CR0_BUS_MDS_mask_w | 
                                 EMB_CR0_ADR_SEL_mask_w | 
                                 EMB_CR0_ADR_TWO_mask_w | 
                                 EMB_CR0_ALE2_MDS_mask_w |
                                 0));
    EMB->CR0.W = EMB->CR0.W                                         | 
                 (uint32_t) (EMB_AddressDataMode->EMB_AddressBit)   | 
                 (uint32_t) (EMB_AddressDataMode->EMB_BusMode)      |
                 (uint32_t) (EMB_AddressDataMode->EMB_ALE2_EN)      | 
                 (uint32_t) (EMB_AddressDataMode->EMB_ALE2Mode)     |
                 (uint32_t) (0x00000100);
}



/**
 *******************************************************************************
 * @brief       EMB write mode select.
 * @details     
 * @param[in]   EMB_WriteMode:  
 *  @arg\b      EMB_Write_Disable   : EMB write disable. 
 *  @arg\b      EMB_Write_Enable    : EMB write enable.
 * @return      No
 * @exception   No
 * @note
 * @par         Example
 * @code
    EMB_WriteMode_Select(EMB_Write_Enable);
 * @endcode
 *******************************************************************************
 */
void EMB_WriteMode_Select(EMB_WriteMode_TypeDef EMB_WriteMode)
{
    uint32_t tmp;
    
    tmp = (EMB->CR0.W  & (~(EMB_CR0_WEN_mask_w)));
    tmp = tmp | EMB_WriteMode;
    EMB->CR0.W = EMB->CR0.W | tmp;
}
///@}


/**
 * @name    Access Time
 *          EMB access time relationship driver.
 */ 
///@{
/**
 *******************************************************************************
 * @brief       EMB access control time state
 * @details     
 * @param[in]   EMB_TimeState:
 *  @arg\b      EMB_ALES: EMB SRAM/NOR bus ALE/ALE2 setup time.
 *      \n      -(EMB_ALES_0MCLK ~ EMB_ALES_1MCLK)
 *  @arg\b      EMB_ALEW: EMB SRAM/NOR bus ALE/ALE2 pulse width.
 *      \n      -(EMB_ALEW_1MCLK ~ EMB_ALEW_4MCLK)
 *  @arg\b      EMB_ALEH: EMB SRAM/NOR bus ALE/ALE2 hold time.
 *      \n      -(EMB_ALEH_0MCLK ~ EMB_ALEH_1MCLK)
 *  @arg\b      EMB_ACCS: SRAM/NOR bus data access setup time.
 *      \n      -(EMB_ACCS_0MCLK ~ EMB_ACCS_1MCLK)
 *  @arg\b      EMB_ACCW: SRAM/NOR bus data access time.
 *      \n      -(EMB_ACCW_1MCLK ~ EMB_ACCW_16MCLK)
 *  @arg\b      EMB_ACCH: SRAM/NOR bus data access hold time.
 *      \n      -(EMB_ACCH_0MCLK ~ EMB_ACCH_1MCLK)
 * @return      No
 * @exception   No
 * @note
 * @par         Example
 * @code
    EMB_TimeStateTypeDef EMB_TimeState;

    EMB_TimeState.EMB_ALES = EMB_ALES_0MCLK;
    EMB_TimeState.EMB_ALEW = EMB_ALEW_1MCLK;
    EMB_TimeState.EMB_ALEH = EMB_ALEH_1MCLK;
    EMB_TimeState.EMB_ACCS = EMB_ACCS_0MCLK;
    EMB_TimeState.EMB_ACCW = EMB_ACCW_1MCLK;
    EMB_TimeState.EMB_ACCH = EMB_ACCH_1MCLK;
    EMB_AccessTime_Config(&EMB_TimeState);    
    
 * @endcode
 *******************************************************************************
 */
__INLINE void EMB_AccessTime_Config(EMB_TimeStateTypeDef* EMB_TimeState)
{
    EMB->CR2.W = (uint32_t) (EMB_TimeState->EMB_ACCH) | 
                 (uint32_t) (EMB_TimeState->EMB_ACCS) | 
                 (uint32_t) (EMB_TimeState->EMB_ACCW) | 
                 (uint32_t) (EMB_TimeState->EMB_ALES) | 
                 (uint32_t) (EMB_TimeState->EMB_ALEH) |
                 (uint32_t) (EMB_TimeState->EMB_ALEW) | 
                 (uint32_t) (0);
}


///@}





/**
 * @name	Interrupt And Event
 *   		Interrupt & event of EMB relationship driver.
 */ 
///@{
/**
 *******************************************************************************
 * @brief       EMB local interrupt enable or disable.
 * @details     
 * @param[in]   EMB_IT:
 * 	@arg\b      EMB_WPE         : EMB bus write protect error detect. 
 *  @arg\b      EMB_BWE         : EMB bus byte write eorror detect.
 * @param[in]   EMB_IT_State
 *  @arg\b      ENABLE          : Enable interrupt of EMB_IT.
 *  @arg\b      DISABLE         : Disable interrupt of EMB_IT.
 * @exception   No
 * @note
 * @par         Example
 * @code
    EMB_IT_Cmd((EMB_WPE | EMB_BWE) , ENABLE);
 * @endcode
 *******************************************************************************
 */
void EMB_IT_Cmd(uint32_t EMB_IT, FunctionalState EMB_IT_State)
{
    if(EMB_IT_State==DISABLE)
	{
        EMB->INT.W &=  (~EMB_IT);
	}
	else
	{
		EMB->INT.W |= EMB_IT;
	}
}

/**
 *******************************************************************************
 * @brief	    EMB interrupts all enable or disable.
 * @details     
 * @param[in]   EMB_ITEA_State:
 * 	@arg\b      ENABLE : EMB interrupt all enable.
 *  @arg\b      DISABLE: EMB interrupt all disable.
 * @return      No	    
 * @exception   No
 * @note 
 * @par         Example
 * @code
    EMB_ITEA_Cmd(ENABLE);
 * @endcode
 *******************************************************************************
 */
__INLINE void EMB_ITEA_Cmd(FunctionalState EMB_ITEA_State)
{
     EMB->INT.MBIT.IEA = EMB_ITEA_State;
}
 
/**
 *******************************************************************************
 * @brief	    Get EMB flag.
 * @details     
 * @param[in]   EMB_Flag:
 * 	@arg\b      EMB_WPE : EMB bus write protect error detect flag.
 *  @arg\b      EMB_BWE : EMB bus byte write error flag.
 *  @arg\b      EMB_BUSY: EMB write/read access busy flag.
 * @return      	    
 * @exception   No
 * @note    
 * @par         Example
 * @code
    EMB_GetSingleFlagStatus(EMB_WPE);
 * @endcode
 *******************************************************************************
 */ 
DRV_Return EMB_GetSingleFlagStatus(uint32_t EMB_Flag)
{
    if((EMB->STA.W & EMB_Flag)!=EMB_Flag)
    {
        return(DRV_UnHappened);
    }
    else
    {
        return(DRV_Happened);
    }
}

/**
 *******************************************************************************
 * @brief	    Get EMB  all flag.
 * @details     
 * @return      All EMB flag status.	    
 * @exception   No
 * @note  
 * @par         Example
 * @code
    EMB_GetAllFlagStatus();
 * @endcode
 *******************************************************************************
 */ 
__INLINE uint32_t EMB_GetAllFlagStatus(void)
{
    return(EMB->STA.W);
}


/**
 *******************************************************************************
 * @brief	    Get EMB flag.
 * @details     
 * @param[in]   EMB_Flag:
 * 	@arg\b      EMB_WPE : EMB bus write protect error detect flag.
 *  @arg\b      EMB_BWE : EMB bus byte write error flag.
 * @return      No	    
 * @exception   No
 * @note    
 * @par         Example
 * @code
    EMB_ClearFlag(EMB_WPE|EMB_BWE);
 * @endcode
 *******************************************************************************
 */ 
__INLINE void EMB_ClearFlag(uint32_t EMB_Flag)
{
    EMB->STA.W = EMB_Flag;

}

///@}



/**
 * @name	Signal Control
 *   		EMB output signal control relationship driver.
 */ 
///@{
/**
 *******************************************************************************
 * @brief       EMB Signal swap enable or disable.
 * @details     
 * @param[in]   EMB_SWAPSignal:
 * 	@arg\b      EMB_MAD_BSWP    : EMB MAD[15:8] and MAD[7:0] signals byte swap.  
 *  @arg\b      EMB_MAD_SWP     : MAD[15:0] signal msb/lsb swap.
 *  @arg\b      EMB_MA_SWP      : MA[15:0] signal msb/lsb swap.
 * @param[in]   EMB_SWAPSignal_Status
 *  @arg\b      ENABLE          : EMB signal swap enable.
 *  @arg\b      DISABLE         : EMB signal swap disable.
 * @return      DRV_Return:
 *  @arg\b      DRV_Failure     : EMB_SWAPSignal source is fail.
 *  @arg\b      DRV_Success     : Configuration is success. 
 * @exception   No
 * @note
 * @par         Example
 * @code
    EMB_SignalSWAP_Cmd((EMB_MAD_BSWP | EMB_MAD_SWP | EMB_MA_SWP) , ENABLE);
 * @endcode
 *******************************************************************************
 */
DRV_Return EMB_SignalSWAP_Cmd(uint32_t EMB_SWAPSignal , FunctionalState EMB_SWAPSignal_Status)
{
    if((EMB_SWAPSignal & (~EMB_CMP_BSWP))!=0)
    {
        return(DRV_Failure);
    }

    if(EMB_SWAPSignal_Status==ENABLE)
    {
        EMB->CR1.W |=EMB_SWAPSignal;
    }
    else
    {
        EMB->CR1.W &= (~EMB_SWAPSignal);
    }
    return(DRV_Success);
} 

/**
 *******************************************************************************
 * @brief       EMB Signal inverse enable or disable.
 * @details     
 * @param[in]   EMD_InverseSignal:
 * 	@arg\b      EMB_CLK_INV     : MCLK clock output inverse
 *  @arg\b      EMB_ALE2_INV    : MALE2 output inverse 
 *  @arg\b      EMB_ALE_INV     : MALE output inverse
 *  @arg\b      EMB_CE_INV      : MCE output inverse
 * @param[in]   EMB_InverseSignal_Status
 *  @arg\b      ENABLE          : EMB signal inverse enable.
 *  @arg\b      DISABLE         : EMB signal inverse disable.
 * @return      
 *  @arg\b      DRV_Failure     : EMD_InverseSignal source is fail.
 *  @arg\b      DRV_Success     : Configuration is success. 
 * @exception   No
 * @note
 * @par         Example
 * @code
    EMB_SignalInverse_Cmd((EMB_CLK_INV | EMB_ALE2_INV | EMB_ALE_INV) , ENABLE);
 * @endcode
 *******************************************************************************
 */
DRV_Return EMB_SignalInverse_Cmd(uint32_t EMD_InverseSignal , FunctionalState EMB_InverseSignal_Status)
{
    if((EMD_InverseSignal & (~EMB_CMP_INV))!=0)
    {
        return(DRV_Failure);
    }    
    
    if(EMB_InverseSignal_Status == ENABLE)
    {
        EMB->CR1.W |= EMD_InverseSignal;
    }
    else
    {
        EMB->CR1.W &= (~EMD_InverseSignal);
    }
    return(DRV_Success);
}
/**
 *******************************************************************************
 * @brief	    EMB signal software control output enable or disable
 * @details     
 * @param[in]   EMB_SWSignal
 *  @arg\b      EMB_BW1_SWEN    : 
 *  @arg\b      EMB_BW0_SWEN    :
 *  @arg\b      EMB_ALE2_SWEN   :
 *  @arg\b      EMB_ALE_SWEN    :
 *  @arg\b      EMB_CE_SWEN     :
 * @param[in]   EMB_SignalSW_Status:
 * 	@arg\b      ENABLE  : EMB signal software control output enable.
 *  @arg\b      DISABLE : EMB signal software control output disable.
 * @return      
 *  @arg\b      DRV_Failure     : EMB_SWSignal source is fail.
 *  @arg\b      DRV_Success     : Configuration is success. 
 * @exception   No
 * @note
 * @par         Example
 * @code
    EMB_SignalSW_Cmd((EMB_BW1_SWEN | EMB_BW0_SWEN | EMB_ALE2_SWEN) , ENABLE);
 * @endcode
 *******************************************************************************
 */
DRV_Return EMB_SignalSW_Cmd(uint32_t EMB_SWSignal ,FunctionalState EMB_SignalSW_Status)
{
    if((EMB_SWSignal & (~EMB_CMP_SWEN))!=0)
    {
        return(DRV_Failure);
    }
    if(EMB_SignalSW_Status==ENABLE)
    {
        EMB->CR1.W |= EMB_SWSignal;
    }
    else
    {
        EMB->CR1.W &= (~EMB_SWSignal);
    }
    return(DRV_Success);
}


/**
 *******************************************************************************
 * @brief	    Software control EMB signal.
 * @details     
 * @param[in]   EMB_SWSignal
 *  @arg\b      EMB_BW1_SWO     : 
 *  @arg\b      EMB_BW0_SWO     :
 *  @arg\b      EMB_ALE2_SWO    :
 *  @arg\b      EMB_ALE_SWO     :
 *  @arg\b      EMB_CE_SWO      :
 * @param[in]   EMB_SWSingal_Status:
 * 	@arg\b      SET : EMB signal output 1.
 *  @arg\b      CLR : EMB signal output 0.
 * @return      
 *  @arg\b      DRV_Failure     : EMB_SWSignal source is fail.
 *  @arg\b      DRV_Success     : Configuration is success. 
 * @exception   No
 * @note
 * @par         Example
 * @code
    EMB_SendSignalStatus_SW((EMB_BW1_SWO | EMB_BW0_SWO | EMB_ALE2_SWO) , SET);
 * @endcode
 *******************************************************************************
 */
DRV_Return EMB_SendSignalStatus_SW(uint32_t EMB_SWSignal ,BitAction EMB_SWSingal_Status)
{
    if((EMB_SWSignal & (~EMB_CMP_SWO))!=0)
    {
        return(DRV_Failure);
    }

    if(EMB_SWSingal_Status==SET)
    {
        EMB->CR1.W |= EMB_SWSignal;
    }
    else
    {
        EMB->CR1.W &= (~EMB_SWSignal);
    }
    return(DRV_Success);
}




/**
 *******************************************************************************
 * @brief	    MWE output signal select.
 * @details     
 * @param[in]   EMB_MWE: 
 *  @arg\b      EMB_MWE_WE  : EMB write enable signal.
 *  @arg\b      EMB_MWE_TM10: TM10 CKO.
 *  @arg\b      EMB_MWE_TM16: TM16 CKO.
 *  @arg\b      EMB_MWE_TM20: TM20 CKO.
 * @return      No
 * @exception   No
 * @note
 * @par         Example
 * @code
    EMB_MWESignal_Select(EMB_MWE_WE);
 * @endcode
 *******************************************************************************
 */
__INLINE void EMB_MWESignal_Select(EMB_MWE_TypeDef EMB_MWE)
{
    EMB->CR1.MBIT.WE_MUX = EMB_MWE;
}


/**
 *******************************************************************************
 * @brief	    MDE output signal select.
 * @details     
 * @param[in]   EMB_MOE: 
 *  @arg\b      EMB_MWE_OE  : EMB output enable signal.
 *  @arg\b      EMB_MWE_TM10: TM10 CKO.
 *  @arg\b      EMB_MWE_TM16: TM16 CKO.
 *  @arg\b      EMB_MWE_TM20: TM20 CKO.
 * @return      No
 * @exception   No
 * @note
 * @par         Example
 * @code
    EMB_MOESignal_Select(EMB_MOE_OE);
 * @endcode
 *******************************************************************************
 */
__INLINE void EMB_MOESignal_Select(EMB_MOE_TypeDef EMB_MOE)
{
    EMB->CR1.MBIT.OE_MUX = EMB_MOE;
}

/**
 *******************************************************************************
 * @brief	    EMB output clock MCK prescaler select.
 * @details     
 * @param[in]   EMB_MCLK: (EMB_PREMCLK_1 ~ EMB_PREMCLK_7).
 * @return      No
 * @exception   No
 * @note
 * @par         Example
 * @code
    EMB_MCLKPreescaler_Select(EMB_PREMCLK_1);
 * @endcode
 *******************************************************************************
 */
__INLINE void EMB_MCLKPreescaler_Select(EMB_MCLK_TypeDef EMB_MCLK)
{
    EMB->CLK.MBIT.CK_PSC = EMB_MCLK;
}


/**
 *******************************************************************************
 * @brief	    MWE control timing select.
 * @details     
 * @param[in]   EMB_WE:  
 *  @arg\b      EMB_TOGGLE: High to low change.
 *  @arg\b      EMB_LOW   : Drive low during read access.
 * @return      No
 * @exception   No
 * @note
 * @par         Example
 * @code
    EMB_WESignalMode_Select(EMB_TOGGLE);
 * @endcode
 *******************************************************************************
 */
__INLINE void EMB_WESignalMode_Select(EMB_RWSignalMode_TypeDef EMB_WE)
{
    EMB->CR0.MBIT.WE_CTL = EMB_WE;
}

/**
 ************** *****************************************************************
 * @brief	    MOE control timing select.
 * @details     
 * @param[in]   EMB_OE:  
 *  @arg\b      EMB_TOGGLE: High to low change.
 *  @arg\b      EMB_LOW   : Drive low during read access.
 * @return      No
 * @exception   No
 * @note
 * @par         Example
 * @code
    EMB_OESignalMode_Select(EMB_TOGGLE);
 * @endcode
 *******************************************************************************
 */
__INLINE void EMB_OESignalMode_Select(EMB_RWSignalMode_TypeDef EMB_OE)
{
    EMB->CR0.MBIT.OE_CTL = EMB_OE;
}


/**
 *******************************************************************************
 * @brief	    MCE signal mode select.
 * @details     
 * @param[in]   EMB_CE:  
 *  @arg\b      EMB_CE: Chip enable signal.
 *  @arg\b      EMB_ALE: Same as ALE timing.
 *  @arg\b      EMB_ALE2: 2nd phase address latch enable.
 * @return      No
 * @exception   No
 * @note
 * @par         Example
 * @code
    EMB_CEMode_Select(EMB_CE);
 * @endcode
 *******************************************************************************
 */
__INLINE void EMB_CEMode_Select(EMB_CEMode_TypeDef EMB_CE)
{
    EMB->CR0.MBIT.CE_MDS = EMB_CE;
}

/**
 *******************************************************************************
 * @brief	    EMB MA1 Signal output pin select.
 * @details     
 * @param[in]   EMB_MA1_PIN:  
 *  @arg\b      EMB_MA1_NoOutput     : No output MA1 signal. 
 *  @arg\b      EMB_MA1_OutputToMAD15: MA1 output pin is MAD15.
 *  @arg\b      EMB_MA1_OutputToBW1  : MA1 output pin is BW1.
 *  @arg\b      EMB_MA1_OutputToALE2 : MA1 output pin is ALE2.
 * @return      No
 * @exception   No
 * @note
 * @par         Example
 * @code
    EMB_MA1SignalOutputPin_Select(EMB_MA1_OutputToMAD15);
 * @endcode
 *******************************************************************************
 */
__INLINE void EMB_MA1SignalOutputPin_Select(EMB_MA1OutputPin_TypeDef EMB_MA1_PIN)
{
    EMB->CR1.MBIT.MAM1_SEL = EMB_MA1_PIN;
}

///@}



/**
 * @name	DMA
 *   		DMA of EMB relationship driver.
 */ 
///@{
/**
 *******************************************************************************
 * @brief       EMB DMA enable or disable.
 * @details     
 * @param[in]   EMB_DMAState
 *  @arg\b      ENABLE : Enable EMB DMA.
 *  @arg\b      DISABLE: Disable EMB DMA.
 * @return      No
 * @exception   No
 * @note
 * @par         Example
 * @code
    EMB_DMA_Cmd(ENABLE);
 * @endcode
 *******************************************************************************
 */
__INLINE void EMB_DMA_Cmd( FunctionalState EMB_DMAState)
{
    EMB->CR0.MBIT.DMA_EN = EMB_DMAState;
}
 
///@}


