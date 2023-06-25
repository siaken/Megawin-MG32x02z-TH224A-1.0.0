
/**
 ******************************************************************************
 *
 * @file        MG32x02z_EXIC_DRV.c
 * @brief       The code is EXIC driver C file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.15
 * @date        2022/03/25
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 * 
 ******************************************************************************* 
 * @par Disclaimer
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
 
 
 


#include "MG32x02z_EXIC_DRV.h"



/**
 * @name	Mode
 *   		Triggle event of external interrupt set relationship driver.
 */ 
///@{
/**
 *******************************************************************************
 * @brief       External interrupt pin edge/level trigger event select.
 * @details  
 * @param[in]   EXIC_PX:
 * @param[in]   EXIC_PX_TRGS: 
 *  @arg\b      EXIC_Pin:
 *  @arg\b      EXIC_TRGS_Mode :
 *      \n      -No_UpData_Flag:
 *      \n      -Level         :
 *      \n      -Edge          :
 *      \n      -Dual_edge     :
 * @return      DRV_Return    
 *  @arg\b      DRV_Failure  : EXIC TRGS source is fail.
 *  @arg\b      DRV_Success  : Configuration is success. 
 * @exception   No   
 * @note        Falling / Rising edge or H / L level is setted by PINX_Inverse of GPIO_PinMode_Config.
 * @par         Example
 * @code
    EXIC_TRGSTypeDef EXIC_TRGS;
    
    EXIC_TRGS.EXIC_Pin = EXIC_TRGS_PIN0 | EXIC_TRGS_PIN1 | EXIC_TRGS_PIN2;
    EXIC_TRGS.EXIC_TRGS_Mode = Edge;
    EXIC_PxTriggerMode_Select(EXIC_PA,&EXIC_TRGS);
 * @endcode
 *******************************************************************************
 */
DRV_Return EXIC_PxTriggerMode_Select(EXIC_PX_Struct* EXIC_PX ,EXIC_TRGSTypeDef* EXIC_PX_TRGS )
{
    uint32_t Tmp;
    
    if((EXIC_PX_TRGS->EXIC_Pin & (uint32_t) (~EXIC_TRGS_ALL))!=0)
    {
        return(DRV_Failure);
    }
    
    Tmp = EXIC_PX->TRGS.W;
    Tmp = Tmp & (~((EXIC_PX_TRGS->EXIC_Pin) * Dual_edge));
    Tmp = Tmp | ((EXIC_PX_TRGS->EXIC_Pin) * (EXIC_PX_TRGS->EXIC_TRGS_Mode));
    EXIC_PX->TRGS.W = Tmp;
    return(DRV_Success);
}


/**
 *******************************************************************************
 * @brief       External interrupt Pinx of PX AND mask bit x.
 * @details  
 * @param[in]   EXIC_PX: Select EXIC Port
 * @param[in]   EXIC_MSK_PIN: Need to compare pin.
 * @return         
 * @exception   No   
 * @note        0 : don't care pin , 1 : need to compare pin.
 * @par         Example
 * @code
    EXIC_PxTriggerAndMask_Select(EXIC_PA, (EXIC_PX_PIN0 | EXIC_PX_PIN1)); or EXIC_PxTriggerAndMask_Select(EXIC_PA , 0x0003);
 * @endcode
 *******************************************************************************
 */
void EXIC_PxTriggerAndMask_Select(EXIC_PX_Struct* EXIC_PX , uint16_t  EXIC_MSK_PIN)
{
    EXIC_PX->MSK.H[1] = EXIC_MSK_PIN;
}


/**
 *******************************************************************************
 * @brief       External interrupt Pinx of PX OR mask bit x. 
 * @details  
 * @param[in]   EXIC_PX: Select EXIC Port
 * @param[in]   EXIC_MSK_PIN: Need to compare pin. 
 * @return      
 * @exception   No   
 * @note
 * @par         Example
 * @code
    EXIC_PxTriggerOrMask_Select(EXIC_PA, (EXIC_PX_PIN0 | EXIC_PX_PIN1));  or EXIC_PxTriggerOrMask_Select(EXIC_PA,0x0003);
 * @endcode
 *******************************************************************************
 */
void EXIC_PxTriggerOrMask_Select(EXIC_PX_Struct* EXIC_PX , uint16_t  EXIC_MSK_PIN)
{
    EXIC_PX->MSK.H[0] = EXIC_MSK_PIN;
}



/**
 *******************************************************************************
 * @brief       Select match or umatch (AND) to set PX AND interrupt flag.
 * @details  
 * @param[in]   EXIC_PX_IT: Select EXIC Port
 * @param[in]   PX_unMatch_Cmd: 
 *  @arg\b      DISABLE: When match (AND) event happen to set PX AND interrupt flag.
 *  @arg\b      ENABLE: When unmatch (AND) event happen to set PX AND interrupt flag.
 * @return      
 * @exception   No   
 * @note
 * @par         Example
 * @code
    EXIC_PxTriggerAndUnmatch_Cmd( ( EXIC_PA_IT | EXIC_PB_IT) , ENABLE);
 * @endcode
 *******************************************************************************
 */
void EXIC_PxTriggerAndUnmatch_Cmd(uint32_t EXIC_PX_IT, FunctionalState PX_unMatch_Cmd)
{
    if(PX_unMatch_Cmd==ENABLE)
    {
        EXIC->CR0.B[3] = EXIC->CR0.B[3] | (uint8_t) EXIC_PX_IT;
    }
    else
    {
        EXIC->CR0.B[3] = EXIC->CR0.B[3] & ((uint8_t) (~EXIC_PX_IT));
    }
}



///@}



/**
 * @name	Interrupt And Event.
 *   		Interrupt and event relationship driver.
 */ 
///@{
/**
 *******************************************************************************
 * @brief       EXIC port external interrupt all enable.
 * @details  
 * @param[in]   EXIC_PX_IT:
 * 	@arg\b		EXIC_PA_IT: EXIC port PA external interrupt.  
 *  @arg\b      EXIC_PB_IT: EXIC port PB external interrupt. 
 *  @arg\b      EXIC_PC_IT: EXIC port PC external interrupt.    
 *  @arg\b      EXIC_PD_IT: EXIC port PD external interrupt. 
 * @param[in]   EXIC_IT_State:
 *  @arg\b		ENABLE : Enable interrupt of EXIC_PX.
 *  @arg\b      DISABLE: Disable interrupt of EXIC_PX.
 * @return      
 * @exception   No   
 * @note
 * @par         Example
 * @code
    EXIC_PxTriggerITEA_Cmd((EXIC_PA_IT | EXIC_PB_IT) , ENABLE);
 * @endcode
 *******************************************************************************
 */
void EXIC_PxTriggerITEA_Cmd(uint32_t EXIC_PX_IT, FunctionalState EXIC_IT_State)
{    
    if(EXIC_IT_State==ENABLE)
    {
        EXIC->INT.W = EXIC->INT.W | EXIC_PX_IT;
    }
    else
    {
        EXIC->INT.W = EXIC->INT.W & (~EXIC_PX_IT);
    }
} 

/**
 *******************************************************************************
 * @brief       Read EXIC PX input interrupt pending flag.
 * @details  
 * @param[in]   EXIC_PX:
 * 	@arg\b		EXIC_PA: Read EXIC PA input interrupt pending flag.  
 *  @arg\b      EXIC_PB: Read EXIC PB input interrupt pending flag.  
 *  @arg\b      EXIC_PC: Read EXIC PC input interrupt pending flag.     
 *  @arg\b      EXIC_PD: Read EXIC PD input interrupt pending flag.  
 * @return      EXIC_PX_PF status.
 * @exception   No   
 * @note
 * @par         Example
 * @code
    tmp = EXIC_GetPxAllTriggerEventFlagStatus(EXIC_PA);
 * @endcode
 *******************************************************************************
 */
uint32_t EXIC_GetPxAllTriggerEventFlagStatus(EXIC_PX_Struct* EXIC_PX)
{
    return(EXIC_PX->PF.W);
}

/**
 *******************************************************************************
 * @brief       Read EXIC PX input flag.
 * @details  
 * @param[in]   EXIC_PX_ITFlag:
 * 	@arg\b		EXIC_PA_ITF: Read EXIC PA input interrupt flag.  
 *  @arg\b      EXIC_PB_ITF: Read EXIC PB input interrupt flag.  
 *  @arg\b      EXIC_PC_ITF: Read EXIC PC input interrupt flag.     
 *  @arg\b      EXIC_PD_ITF: Read EXIC PD input interrupt flag.  
 * @return      EXIC_PX (EXIC_PA or EXIC_PB or EXIC_PC or EXIC_PD) all interrupt flag.
 * @exception   No   
 * @note
 * @par         Example
 * @code
    tmp = EXIC_GetPxAllTriggerITFlagStatus(EXIC_PA_ITF);
 * @endcode
 *******************************************************************************
 */
uint8_t EXIC_GetPxAllTriggerITFlagStatus( EXIC_ITFlag_Typdef EXIC_PX_ITFlag)
{
    uint16_t Tmp;
    
    Tmp = EXIC->STA.H[0];
    Tmp = EXIC->STA.H[0] >> (EXIC_PX_ITF_Shift * EXIC_PX_ITFlag);
    Tmp = Tmp & EXIC_PX_ITF_Mask;
    return (uint8_t) (Tmp);
}

/**
 *******************************************************************************
 * @brief       Read EXIC Pin of PX input interrupt pending flag.
 * @details  
 * @param[in]   EXIC_PX: Want to read input interrupt pending flag of EXIC_PX.
 * 	@arg\b		EXIC_PA: Read EXIC pin of PA input interrupt pending flag.  
 *  @arg\b      EXIC_PB: Read EXIC pin of PB input interrupt pending flag.  
 *  @arg\b      EXIC_PC: Read EXIC pin of PC input interrupt pending flag.     
 *  @arg\b      EXIC_PD: Read EXIC pin of PD input interrupt pending flag. 
 * @param[in]   EXIC_Pin_PF: Want to read input interrupt pending flag of EXIC_Pin.
 *  @arg\b      (EXIC_PX_PIN0 ~ EXIC_PX_PIN15).
 * @return      EXIC_PX_PF status.
 * @exception   No   
 * @note        Only read one pin's PF status.
 * @par         Example
 * @code
    tmp = EXIC_GetPinxTriggerEventSingleFlagStatus(EXIC_PA , EXIC_PX_PIN15);
 * @endcode
 *******************************************************************************
 */
DRV_Return EXIC_GetPinxTriggerEventSingleFlagStatus(EXIC_PX_Struct* EXIC_PX , uint16_t EXIC_Pin_PF)
{
    if((EXIC_PX->PF.H[0]&EXIC_Pin_PF)==0)
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
 * @brief       Read EXIC Pin of PX external input AND interrupt flag.
 * @details  
 * @param[in]   EXIC_PX_ITFlag:
 * 	@arg\b		EXIC_PA_ITF: Read EXIC pin of PA input interrupt AND flag.  
 *  @arg\b      EXIC_PB_ITF: Read EXIC pin of PB input interrupt AND flag.  
 *  @arg\b      EXIC_PC_ITF: Read EXIC pin of PC input interrupt AND flag.     
 *  @arg\b      EXIC_PD_ITF: Read EXIC pin of PD input interrupt AND flag.  
 * @return      EXIC PX AND interrupt flag status.
 * @exception   No   
 * @note        
 * @par         Example
 * @code
    tmp = EXIC_GetPxTriggerAndITFlagStatus(EXIC_PA_ITF);
 * @endcode
 *******************************************************************************
 */
DRV_Return EXIC_GetPxTriggerAndITFlagStatus( EXIC_ITFlag_Typdef EXIC_PX_ITFlag)      
{
    uint32_t PX_AF_CMP;
    
    PX_AF_CMP = EXIC->STA.H[0];
    PX_AF_CMP = EXIC->STA.H[0] >> (EXIC_PX_ITF_Shift * EXIC_PX_ITFlag);
    PX_AF_CMP = PX_AF_CMP & EXIC_PX_AF;
    
    if(PX_AF_CMP==0)
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
 * @brief       Read EXIC Pin of PX external input OR interrupt flag.
 * @details  
 * @param[in]   EXIC_PX_ITFlag:
 * 	@arg\b		EXIC_PA_ITF: Read EXIC pin of PA input interrupt OR flag.  
 *  @arg\b      EXIC_PB_ITF: Read EXIC pin of PB input interrupt OR flag.  
 *  @arg\b      EXIC_PC_ITF: Read EXIC pin of PC input interrupt OR flag.     
 *  @arg\b      EXIC_PD_ITF: Read EXIC pin of PD input interrupt OR flag.  
 * @return      EXIC PX OR interrupt flag status.
 * @exception   No   
 * @note        
 * @par         Example
 * @code
    tmp = EXIC_GetPxTriggerOrITFlagStatus(EXIC_PA_ITF);
 * @endcode
 *******************************************************************************
 */
DRV_Return EXIC_GetPxTriggerOrITFlagStatus( EXIC_ITFlag_Typdef EXIC_PX_ITFlag)    
{
    uint32_t PX_OF_CMP;
    
    PX_OF_CMP = EXIC->STA.H[0];
    PX_OF_CMP = EXIC->STA.H[0] >> (EXIC_PX_ITF_Shift * EXIC_PX_ITFlag);
    PX_OF_CMP = PX_OF_CMP & EXIC_PX_OF;
    
    if(PX_OF_CMP==0)
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
 * @brief       Clear EXIC PX input interrupt pending flag.
 * @details  
 * @param[in]   EXIC_PX:
 * 	@arg\b		EXIC_PA_PF: EXIC PA input interrupt pending flag.  
 *  @arg\b      EXIC_PB_PF: EXIC PB input interrupt pending flag.  
 *  @arg\b      EXIC_PC_PF: EXIC PC input interrupt pending flag.     
 *  @arg\b      EXIC_PD_PF: EXIC PD input interrupt pending flag. 
 * @param[in]   EXIC_Pin_PF: (EXIC_PX_PIN0 ~ EXIC_PX_PIN15 or EXIC_PX_AllPIN ) Want to clear pf of Pin.
 * @return      
 * @exception   No  
 * @note
 * @par         Example
 * @code
    EXIC_ClearPxTriggerEventFlag(EXIC_PA, (EXIC_PX_PIN0 | EXIC_PX_PIN1)); or EXIC_ClearPxTriggerEventFlag(EXIC_PA, 0x0003);                                                                        
 * @endcode
 *******************************************************************************
 */
void EXIC_ClearPxTriggerEventFlag(EXIC_PX_Struct* EXIC_PX , uint16_t EXIC_Pin_PF)
{
    EXIC_PX->PF.H[0] = EXIC_Pin_PF;
}

/**
 *******************************************************************************
 * @brief       Clear EXIC PX input interrupt flag.
 * @details  
 * @param[in]   EXIC_PX:
 * 	@arg\b		EXIC_PA_ITF: EXIC PA input interrupt flag.  
 *  @arg\b      EXIC_PB_ITF: EXIC PB input interrupt flag.  
 *  @arg\b      EXIC_PC_ITF: EXIC PC input interrupt flag.     
 *  @arg\b      EXIC_PD_ITF: EXIC PD input interrupt flag. 
 *  @arg\b      EXIC_PE_ITF: EXIC PE input interrupt flag.
 * @param[in]   EXIC_PX_ITFlag:
 *  @arg\b      EXIC_PX_AF: PX AND path interrupt flag.
 * @exception   No  
 * @note        When clear PX event flag ( PX0_PF ~ PX15_PF ) hardware auto clear PX_OF. 
 * @par         Example
 * @code
    EXIC_ClearPxTriggerITFlag(EXIC_PA_ITF,(EXIC_PX_AF|EXIC_PX_OF));                                                                      
 * @endcode
 *******************************************************************************
 */
void EXIC_ClearPxTriggerITFlag( EXIC_ITFlag_Typdef EXIC_PX , uint8_t EXIC_PX_ITFlag)
{
    uint32_t PX_ITF_CLR;
    
    PX_ITF_CLR = (uint32_t)( EXIC_PX_ITFlag << (EXIC_PX_ITF_Shift * EXIC_PX));
    
    EXIC->STA.W = PX_ITF_CLR;
}


/**
 *******************************************************************************
 * @brief       Get interrupt source-ITSourceNum identify.
 * @details  
 * @param[in]   ITSourceNum: Interrupt source number(except Cortex-M0 Processor Exceptions).
 * @return      Interrupt source-ITSourceNum idelntify.
 * @exception   No   
 * @note
 * @par         Example
 * @code
    tmp = EXIC_GetITSourceID(1);
 * @endcode
 *******************************************************************************
 */
uint8_t EXIC_GetITSourceID(IRQn_Type ITSourceNum)
{
    uint8_t tmp;
    

    tmp = *((volatile uint8_t*)((uint32_t)EXIC_ID_ADR_Base + (uint32_t)ITSourceNum));
    return(tmp);
}

/**
 *******************************************************************************
 * @brief       Interrupt event mask for RXEV.
 * @details  
 * @param[in]   RXEV_State:
 *  @arg\b      DISABLE: Interrupt event mask for RXEV.
 *  @arg\b      ENABLE: Interrupt event no mask for RXEV.
 * @return      
 * @exception   No    
 * @note
 * @par         Example
 * @code
    EXIC_RXEV_Cmd(ENABLE);
 * @endcode
 *******************************************************************************
 */
void EXIC_RXEV_Cmd(FunctionalState RXEV_State)
{
    EXIC->CR0.MBIT.EM_RXEV = RXEV_State;
}



/**
 *******************************************************************************
 * @brief       Interrupt event mask for NMI.
 * @details  
 * @param[in]   NMI_State: 
 *  @arg\b      DISABLE: Interrupt event mask for NMI.
 *  @arg\b      ENABLE : Interrupt event no mask for NMI.
 * @return      
 * @exception   No   
 * @note
 * @par         Example
 * @code
    EXIC_NMI_Cmd(ENABLE);
 * @endcode
 *******************************************************************************
 */
void EXIC_NMI_Cmd(FunctionalState NMI_State)
{
    EXIC->CR0.MBIT.EM_NMI = NMI_State;
}


/**
 *******************************************************************************
 * @brief       Software NMI trigger bit.
 * @details     The bit set by software and clear by hardware. 
 * @return      
 * @exception   No   
 * @note
 * @par         Example
 * @code
    EXIC_NMITrigger_SW();
 * @endcode
 *******************************************************************************
 */
void EXIC_NMITrigger_SW(void)
{
    EXIC->CR0.MBIT.NMI_SW = ENABLE;
}

#if defined(EXIC_CR0_NMI_SEL_mask_w) && defined(EXIC_CR0_NMI_MUX_mask_w)
/**
 *******************************************************************************
 * @brief       NMI trigger source select
 * @details     The bit set by software and clear by hardware. 
 * @param[in]   NMIMUX_SEL: 
 *  @arg\b      EXIC_NMI_WWDT     
 *  @arg\b      EXIC_NMI_SYS      
 *  @arg\b      EXIC_NMI_Reserve0 
 *  @arg\b      EXIC_NMI_EXIN0    
 *  @arg\b      EXIC_NMI_EXIN1    
 *  @arg\b      EXIC_NMI_EXIN2    
 *  @arg\b      EXIC_NMI_EXIN3    
 *  @arg\b      EXIC_NMI_COMP     
 *  @arg\b      EXIC_NMI_DMA      
 *  @arg\b      EXIC_NMI_Reserve1 
 *  @arg\b      EXIC_NMI_ADC      
 *  @arg\b      EXIC_NMI_DAC      
 *  @arg\b      EXIC_NMI_TM00     
 *  @arg\b      EXIC_NMI_TM10     
 *  @arg\b      EXIC_NMI_TM16     
 *  @arg\b      EXIC_NMI_TM20     
 *  @arg\b      EXIC_NMI_TM26     
 *  @arg\b      EXIC_NMI_TM36     
 *  @arg\b      EXIC_NMI_Reserve2 
 *  @arg\b      EXIC_NMI_Reserve3 
 *  @arg\b      EXIC_NMI_URT0     
 *  @arg\b      EXIC_NMI_URT123   
 *  @arg\b      EXIC_NMI_Reserve4 
 *  @arg\b      EXIC_NMI_Reserve5 
 *  @arg\b      EXIC_NMI_SPI0     
 *  @arg\b      EXIC_NMI_Reserve6 
 *  @arg\b      EXIC_NMI_Reserve7 
 *  @arg\b      EXIC_NMI_Reserve8 
 *  @arg\b      EXIC_NMI_I2C0     
 *  @arg\b      EXIC_NMI_I2Cx     
 *  @arg\b      EXIC_NMI_Reserve9 
 *  @arg\b      EXIC_NMI_ReserveA 
 *  @arg\b      EXIC_NMI_NMI 
 * @return      
 * @exception   No   
 * @note
 * @par         Example
 * @code
    EXIC_NMIMUX_SEL(EXIC_NMI_NMI);
 * @endcode
 *******************************************************************************
 */
void EXIC_NMI_Select(EXIC_NMIMUX_Typedef NMIMUX_SEL)
{
    EXIC->CR0.W &= ~(EXIC_CR0_NMI_SEL_mask_w | EXIC_CR0_NMI_MUX_mask_w);
    EXIC->CR0.W |= NMIMUX_SEL;    
}
#endif

///@}




















