

 /**
 ******************************************************************************
 *
 * @file        MG32x02z_EXIC_MID.c
 * @brief       The code EXIC middleware C file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.05
 * @date        2022/06/15
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
 
 
 
#include "MG32x02z_EXIC_MID.h"


/**
 *******************************************************************************
 * @brief	    External interrupt port AND path singal inverse control.
 * @details     
 * @param[in]   MEXIC_PX    : EXIC handle. 
 * @return      No.
 * @exception   No
 * @note        Use AND_UnMatch of MEXIC_PX to control.
 *******************************************************************************
 */
void MID_EXIC_PxTriggerAndUnmatch_Cmd( EXIC_HandleTypeDef* MEXIC_PX )
{
    if(MEXIC_PX->AND_UnMatch==ENABLE)
    {
        EXIC->CR0.B[3] |= (0x01 << MEXIC_PX->EXIC_Port);
    }
    else
    {
        EXIC->CR0.B[3] &= (~(0x01 << MEXIC_PX->EXIC_Port));
    }
}
/**
 *******************************************************************************
 * @brief	    External interrupt Port AND mask select.
 * @details     
 * @param[in]   MEXIC_PX    : EXIC handle.  
 * @return      No.
 * @exception   No
 * @note        Use AND_Mask of MEXIC_PX to control.
 *******************************************************************************
 */
void MID_EXIC_PxTriggerAndMask_Select( EXIC_HandleTypeDef* MEXIC_PX )
{
    MEXIC_PX->Instance->MSK.H[1] = MEXIC_PX->AND_Mask;
}

/**
 *******************************************************************************
 * @brief	    External interrupt Port OR mask select.
 * @details     
 * @param[in]   MEXIC_PX    : EXIC handle.  
 * @return      No.
 * @exception   No
 * @note        Use OR_Mask of MEXIC_PX to control.
 *******************************************************************************
 */
void MID_EXIC_PxTriggerOrMask_Select( EXIC_HandleTypeDef* MEXIC_PX)
{
    MEXIC_PX->Instance->MSK.H[0] = MEXIC_PX->OR_Mask;
}

/**
 *******************************************************************************
 * @brief	    External interrupt pin trigger event configuration.
 * @details     
 * @param[in]   MEXIC_PX     : EXIC_PORT handle. 
 * @param[in]   EXIC_PIN     : Interrupt flag. This parameter can be any combination
 *                             of the following values.
 *              - EXIC_TRGS_PIN0  : pin0  of the port.
 *              - EXIC_TRGS_PIN1  : pin1  of the port.
 *              - EXIC_TRGS_PIN2  : pin2  of the port.
 *              - EXIC_TRGS_PIN3  : pin3  of the port.
 *              - EXIC_TRGS_PIN4  : pin4  of the port.
 *              - EXIC_TRGS_PIN5  : pin5  of the port.
 *              - EXIC_TRGS_PIN6  : pin6  of the port.
 *              - EXIC_TRGS_PIN7  : pin7  of the port.
 *              - EXIC_TRGS_PIN8  : pin8  of the port.
 *              - EXIC_TRGS_PIN9  : pin9  of the port.
 *              - EXIC_TRGS_PIN10 : pin10 of the port.
 *              - EXIC_TRGS_PIN11 : pin11 of the port.
 *              - EXIC_TRGS_PIN12 : pin12 of the port.
 *              - EXIC_TRGS_PIN13 : pin13 of the port.
 *              - EXIC_TRGS_PIN14 : pin14 of the port.
 *              - EXIC_TRGS_PIN15 : pin15 of the port.
 *              - EXIC_TRGS_AllPIN: All pins of the port.
 * @param[in]   EXIC_TRG_MDS : specifies the external trigger event.
 *                             This parameter can be one of the following values.
 *              - EXIC_TRIGGER_NONE     : No external trigger mode.
 *              - EXIC_TRIGGER_LEVEL    : Level trigger mode.
 *              - EXIC_TRIGGER_EDGE     : Edge trigger mode.
 *              - EXIC_TRIGGER_DUAL_EDGE: Dual edge trigger mode.
 * @return      No.
 * @exception   No
 * @note        Falling / Rising edge or H / L level is setted by GPIO input inverse control.
 *      \n      Disable input inverse : low level / falling edge.
 *      \n      Enable input inverse  : high level / rising edge.
 * @par         Example
 * @code
     EXIC_HandleTypeDef   EXIC_PORTX;
 
     EXIC_PORT.Instance    = EXIC_PA;             // EXIC_PORTX is PortA input interrupt handle.       //Before using this function this parameter have to declare.
     
     MID_EXIC_PxTriggerMode_Config( &EXIC_PORT, ( EXIC_TRGS_PIN0 | EXIC_TRGS_PIN1 | EXIC_TRGS_PIN2 | EXIC_TRGS_PIN3 | EXIC_TRGS_PIN4 |  \
                                                  EXIC_TRGS_PIN5 | EXIC_TRGS_PIN6 | EXIC_TRGS_PIN7), EXIC_TRIGGER_DUAL_EDGE);       // PA0 , PA1 , PA2 , PA3 , PA4 , PA5 , PA6 , PA7 is dual edge mode.
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_EXIC_PxTriggerMode_Config(EXIC_HandleTypeDef* MEXIC_PX ,uint32_t EXIC_PIN , uint32_t EXIC_TRG_MDS )
{
    uint32_t mEXIC_TRG_Tmp;
    
    if( (MEXIC_PX == NULL) || ((EXIC_PIN & ((uint32_t)(~EXIC_TRGS_ALL)))!=0))
    {
        return(MID_FAILURE);
    }
    
    mEXIC_TRG_Tmp              = MEXIC_PX->Instance->TRGS.W;
    mEXIC_TRG_Tmp              = mEXIC_TRG_Tmp & (~(EXIC_PIN * EXIC_TRIGGER_MASK));
    mEXIC_TRG_Tmp              = mEXIC_TRG_Tmp | (EXIC_PIN * EXIC_TRG_MDS);
    MEXIC_PX->Instance->TRGS.W = mEXIC_TRG_Tmp;
    
    return(MID_SUCCESS);
}
/**
 *******************************************************************************
 * @brief	    Clear external interrupt Port interrupt flag.
 * @details     
 * @param[in]   MEXIC_PX   : EXIC_PORT handle. 
 * @param[in]   ITFlag     : Interrupt flag. This parameter can be any combination
 *                           of the following values.
 *              - EXIC_PX_AF : External interrupt Port AND path interrupt flag.
 *              - EXIC_PX_OF : External interrupt Port OR path interrupt flag.
 * @return      
 * @exception   No
 * @note        No
 *******************************************************************************
 */
void MID_EXIC_ClearITFlag( EXIC_HandleTypeDef* MEXIC_PX , uint32_t ITFlag)
{
    EXIC->STA.W = (ITFlag << (MEXIC_PX->EXIC_Port*EXIC_PX_ITF_SHIFT));
}


/**
 *******************************************************************************
 * @brief	    DeInitialize the external interrupt port peripheral.
 * @details     
 * @param[in]   MEXIC_PX   : EXIC_PORT handle. 
 * @return      No.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
MID_StatusTypeDef MID_EXIC_DeInit( EXIC_HandleTypeDef* MEXIC_PX )
{
    if( MEXIC_PX == NULL)
    {
        return(MID_FAILURE);
    }
    
    //===========================================================    
    //Disable the peripheral.
    switch( ((uint32_t)(&(MEXIC_PX->Instance->PF.W))))
    {
        case EXIC_PA_Base:
        case EXIC_PB_Base:
        case EXIC_PC_Base:
        case EXIC_PD_Base:
        #if defined(EXIC_PE_Base)
        case EXIC_PE_Base:
        #endif
                          MID_EXIC_ClearITFlag(MEXIC_PX , ( EXIC_PX_AF | EXIC_PX_OF)); 
                          CLEAR_BIT( EXIC->INT.B[0] , ( EXIC_INTERRUPT_ENABLE << MEXIC_PX->EXIC_Port)); 
                          break;
        default:
                          return(MID_FAILURE);
    }
    
    MEXIC_PX->Instance->MSK.W  = 0;
    MEXIC_PX->Instance->PF.W   = 0x0000FFFF;
    MEXIC_PX->Instance->TRGS.W = 0;
    //===========================================================    
    //DeInit the low level hardware.
    MID_EXIC_MspDeInit(MEXIC_PX);
    
    
    //===========================================================
    //Process Unlock.
    __MID_UNLOCK(MEXIC_PX);
    
    
    
    return(MID_SUCCESS);
}
/**
 *******************************************************************************
 * @brief	    Initialize the EXIC external pin input interrupt according to the
 *     \n       specified parameters in the EXIC_HandleTypeDef and initialize the 
 *     \n       associated handle.
 * @details     
 * @param[in]   MEXIC_PX   : EXIC_PORT handle. 
 * @return      MID status.
 * @exception   No
 * @note        No
 * @par         Example
 * @code
     EXIC_HandleTypeDef   EXIC_PORTX;
 
     EXIC_PORT.Instance = EXIC_PB;                 // EXIC_PORTX is PortB input interrupt handle.
     KB_ROW.AND_Mask    = 0x0300;                  // It is similar to KBI . 
                                                   // The parameter = 0x0300 represent that to trigger AND flag when PB8 and PB9 trigger event happen at same time. 
     KB_ROW.AND_UnMatch = DISABLE;                 // ENABLE = AND flag is setted by PB8 & PB9 no trgger happen  
     KB_ROW.Interrupt   = EXIC_INTERRUPT_ENABLE;   // ENABLE the port exic interrupt or disable.
     KB_ROW.OR_Mask     = 0x0003;                  // It is similar to INTn
                                                   // The parameter = 0x0003 represent that to trigger OR flag when any PB8 or PB9 trigger event happen. 
     MID_EXIC_PxTrigger_Init( &EXIC_PORTX);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_EXIC_PxTrigger_Init( EXIC_HandleTypeDef* MEXIC_PX)
{
    //===========================================================
    //Check the EXIC handle allocation.
    if(MEXIC_PX == NULL)
    {
        return(MID_FAILURE);
    }
    //============================================================
    //Check EXIC register address and define EXIC_STA flag shift
    switch((uint32_t)(&MEXIC_PX->Instance->PF.W))
    {
        case EXIC_PA_Base:
                          MEXIC_PX->EXIC_Port = EXIC_PORTA;
                          break;
        case EXIC_PB_Base:
                          MEXIC_PX->EXIC_Port = EXIC_PORTB;
                          break;
        case EXIC_PC_Base:
                          MEXIC_PX->EXIC_Port = EXIC_PORTC;
                          break;
        case EXIC_PD_Base:
                          MEXIC_PX->EXIC_Port = EXIC_PORTD;
                          break;
        #if defined(EXIC_PE_Base)
        case EXIC_PE_Base:
                          MEXIC_PX->EXIC_Port = EXIC_PORTE;
                          break;
        #endif
        default:
                          return(MID_FAILURE);
    } 
    //===========================================================
    //Allocate lock resource and initialize it.
    MEXIC_PX->Lock = MID_UnLocked;
    
    //----------------------------------------------------------
    //Inital the low level hardware
    MID_EXIC_MspInit(MEXIC_PX);
    
    //==========================================================
    //External interrupt OR & AND control
    MID_EXIC_PxTriggerAndUnmatch_Cmd( MEXIC_PX);
    MEXIC_PX->Instance->MSK.H[1] = MEXIC_PX->AND_Mask;
    MEXIC_PX->Instance->MSK.H[0] = MEXIC_PX->OR_Mask;

    //==========================================================
    //Clear All flag 
    //Interrupt IE Control
    if(MEXIC_PX->Interrupt > 1)
    {
        return(MID_FAILURE); 
    }
    __DRV_EXIC_CLEAR_PINTRIGGER_EVENTFLAG( MEXIC_PX , EXIC_PX_AllPIN);                                                         // Clear EXIC_Px_PF
    MID_EXIC_ClearITFlag(MEXIC_PX , ( EXIC_PX_AF | EXIC_PX_OF));                                                               // Clear EXIC_PX_AF & EXIC_PX_OF 
    MODIFY_REG( EXIC->INT.B[0] , (uint8_t)(1 << MEXIC_PX->EXIC_Port) , (uint8_t)( MEXIC_PX->Interrupt << MEXIC_PX->EXIC_Port));   
    
    return(MID_SUCCESS);
}
/**
 *******************************************************************************
 * @brief	    DeInitalize the EXIC MSP.
 * @details     
 * @param[in]   MEXIC_PX   : EXIC_PORT handle.  
 * @return      No
 * @exception   No
 * @note        No
 *******************************************************************************
 */
__WEAK void MID_EXIC_MspDeInit(EXIC_HandleTypeDef* MEXIC_PX)
{
    //===========================================================
    //Prevent unsed argument(s) compilation warning
    UNUSED(MEXIC_PX);
    
    //===========================================================
    //Note : This function should not be modified , when the callback is needed,
    //       the MID_URT_MspDeInit can be implemented in the user file.
    
}
/**
 *******************************************************************************
 * @brief	    Initalize the EXIC MSP.
 * @details     
 * @param[in]   MEXIC_PX   : EXIC_PORT handle. 
 * @return      No.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
__WEAK void MID_EXIC_MspInit( EXIC_HandleTypeDef* MEXIC_PX)
{
    //===========================================================
    //Prevent unsed argument(s) compilation warning
    UNUSED(MEXIC_PX);
    
    //===========================================================
    //Note : This function should not be modified , when the callback is needed,
    //       the MID_URT_MspInit can be implemented in the user file.
    
}

#if 0
/**
 *******************************************************************************
 * @brief	    External interrupt AND path happen callback.
 * @details     
 * @param[in]   MEXIC_PX   : EXIC_PORT handle.
 * @return      No.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
__WEAK void MID_EXIC_AFCallback( EXIC_HandleTypeDef* MEXIC_PX)
{
    //=========================================================
    //Prevent unused argument compilation warning.
    UNUSED(MEXIC_PX);
    
    //=========================================================
    //1. Use MID_EXIC_ClearITFlag() function to clear PX_OF :
    //   exsample : MID_EXIC_ClearITFlag(MEXIC_PX , EXIC_PX_AF);
    //
    //1. Use __DRV_EXIC_GET_PINTRIGGER_EVENTFLAG( MEXIC_PX->Instance) 
    //   to get pin input interrupt pending flag.
    //
    //2. Use __DRV_EXIC_CLEAR_PINTRIGGER_EVENTFLAG( MEXIC_PX->Instance , EXIC_PX_PIN0)
    //   to clear pin input interrupt pending flag.
    //
    //3. Know trigger port from MEXIC_PX->EXIC_Port parameter.
    
    //=========================================================
    //Note : This function should not be modified, when the callback 
    //       is needed, the MID_URT_AbortTransmitCpltCallback can 
    //       be implemented in the user file.
}
#endif

#if 0
/**
 *******************************************************************************
 * @brief	    External interrupt OR path happen callback.
 * @details     
 * @param[in]   MEXIC_PX   : EXIC_PORT handle. 
 * @return      No.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
__WEAK void MID_EXIC_OFCallback( EXIC_HandleTypeDef* MEXIC_PX )
{
    //=========================================================
    //Prevent unused argument compilation warning.
    UNUSED(MEXIC_PX);
    
    //=========================================================
    //1. Use MID_EXIC_ClearITFlag() function to clear PX_OF :
    //   exsample : MID_EXIC_ClearITFlag(MEXIC_PX , EXIC_PX_OF);
    //
    //2. Use __DRV_EXIC_GET_PINTRIGGER_EVENTFLAG( MEXIC_PX->Instance) 
    //   to get pin input interrupt pending flag.
    //
    //3. Use __DRV_EXIC_CLEAR_PINTRIGGER_EVENTFLAG( MEXIC_PX->Instance , EXIC_PX_PIN0)
    //   to clear pin input interrupt pending flag.
    //
    //4. Know trigger port from MEXIC_PX->EXIC_Port parameter.
    
    //=========================================================
    //Note : This function should not be modified, when the callback 
    //       is needed, the MID_URT_AbortTransmitCpltCallback can 
    //       be implemented in the user file.
}
#endif

/**
 *******************************************************************************
 * @brief	    Handle External pin input interrupt request.
 * @details     
 * @param[in]   MEXIC_PX   : EXIC_PORT handle. 
 * @return      No.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
void MID_EXIC_IRQHandler( EXIC_HandleTypeDef* MEXIC_PX)
{
    uint32_t MID_EXICIRQ_Flag;

    MID_EXICIRQ_Flag = ((EXIC->STA.W >> (MEXIC_PX->EXIC_Port*EXIC_PX_ITF_SHIFT) ) & ( EXIC_PX_ITF_MASK));

    if( MID_EXICIRQ_Flag & EXIC_PX_AF)
    {
        MID_EXIC_AFCallback(MEXIC_PX);
        
    }
    if( MID_EXICIRQ_Flag & EXIC_PX_OF)
    {
        MID_EXIC_OFCallback(MEXIC_PX);
        
    }
}























