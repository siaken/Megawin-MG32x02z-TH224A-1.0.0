

 /**
 ******************************************************************************
 *
 * @file        MG32x02z_URT_MID.c
 * @brief       The demo code URT middleware C file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.06
 * @date        2022/06/23
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
 
 

#include "MG32x02z_URT_MID.h"

static void ifun_URT_EndTxTransfer( URT_HandleTypeDef* MURT);
static void ifun_URT_EndRxTransfer( URT_HandleTypeDef* MURT);
static void ifun_URT_DMATransmitCplt(DMA_HandleTypeDef *MDMA);
static void ifun_URT_DMAReceiveCplt( DMA_HandleTypeDef *MDMA);
static void ifun_URT_DMATxHalfCplt( DMA_HandleTypeDef *MDMA);
static void ifun_URT_DMARxHalfCplt( DMA_HandleTypeDef *MDMA);
static void ifun_URT_DMAError( DMA_HandleTypeDef *MDMA);
static void ifun_URT_DMATxAbortCallback(DMA_HandleTypeDef *MDMA);
static void ifun_URT_DMARxAbortCallback(DMA_HandleTypeDef *MDMA);
static void ifun_URT_DMATxOnlyAbortCallback(DMA_HandleTypeDef *MDMA);
static void ifun_URT_DMARxOnlyAbortCallback(DMA_HandleTypeDef *MDMA);
MID_StatusTypeDef ifun_URT_Transmit_IT( URT_HandleTypeDef* MURT);
MID_StatusTypeDef ifun_URT_EndTransmit_IT( URT_HandleTypeDef* MURT);
static MID_StatusTypeDef ifun_URT_Receive_IT( URT_HandleTypeDef * MURT);
void ifun_URT_DMAAbortOnError(DMA_HandleTypeDef *MDMA);


/**
 * @name    URT initialization and configuration function.
 *             
 */ 
///@{

/**
 *******************************************************************************
 * @brief	    Initialize the URT mode according to the specified parameters in 
 *      \n      the URT_HandleTypeDef and initialize the associated handle.
 * @details     
 * @param[in]   MURT : URT handle.
 * @return      MID status.
 * @exception   No
 * @note        No
 * @par         Example
 * @code
       URT_HandleTypeDef MID_URT0;
   
       MID_URT0.Instance                     =  URT0;
       MID_URT0.Init.BaudRate                =  115200;                            
       MID_URT0.Init.WordLength              =  UART_WORDLENGTH_8B;
       MID_URT0.Init.HWFlowCtrl              =  URT_HWCONTROL_NONE;
       MID_URT0.Init.Mode                    =  URT_TX_RX;
       MID_URT0.Init.OneBitSampling          =  URT_ONEBIT_SAMPLE_THREE;
       MID_URT0.Init.Parity                  =  URT_PARITY_NO;
       MID_URT0.Init.StopBits                =  URT_STOPBIT_1_0;  
       MID_URT0.AdvancedInit.AdvFeatureInit  = URT_ADVFEATURE_NO_INIT;
       
       MID_URT_Init( &MID_URT0);
 * @endcode
 *******************************************************************************
 */
MID_StatusTypeDef MID_URT_Init( URT_HandleTypeDef* MURT)
{
    //===========================================================
    //Check the URT handle allocation.
    if(MURT == NULL)                                                                                                                  
    {
        return(MID_FAILURE);
    }
    //============================================================
    //Check URT register address
    MURT->TxTransferCountMax = 1;
    
    switch((uint32_t)(&MURT->Instance->STA.W))
    {
        case URT0_Base:
        #if defined(URT1_Base)
        case URT1_Base:
        #endif
        #if defined(URT2_Base)    
        case URT2_Base:
        #endif   
        #if defined(URT3_Base)
        case URT3_Base:
        #endif                
                               MURT->TxTransferCountMax = 4;
                               break;
        #if defined(URT4_Base)
        case URT4_Base:
                               break;
        #endif
        #if defined(URT5_Base)
        case URT5_Base:
                               break;
        #endif
        #if defined(URT6_Base)
        case URT6_Base:
                               break;
        #endif
        #if defined(URT7_Base)
        case URT7_Base:
                               break;
        #endif
        default: 
                               return(MID_FAILURE);
    }
    
    //===========================================================                    
    if(MURT->gState == MID_URT_STATE_RESET)                                                
    {
        //-------------------------------------------
        //Allocate lock resource and initialize it.
        MURT->Lock = MID_UnLocked;
        
        //-------------------------------------------
        //Inital the low level hardware:
        //    * GPIO 
        //    * CLCOK         
        MID_URT_MspInit(MURT);                                                      
    }

    MURT->gState = MID_URT_STATE_BUSY;
    
    
    //===========================================================                           
    //Disable the peripheral
    __MID_URT_DISABLE(MURT);                                                                         
    
    //===========================================================                        
    //Set the URT communication parameters.
    if(MID_URT_SetConfig(MURT) == MID_FAILURE)                                                       
    {
        return(MID_FAILURE);
    }
    
    if(MURT->AdvancedInit.AdvFeatureInit != URT_ADVFEATURE_NO_INIT)                
    {
        MID_URT_AdvFeatureConfig(MURT);
    }
    
    //===========================================================                         
    //In asynchronous mode, the following bits must be kept cleared and setted.
    //    * CLK_EN bit be cleared in the URT_CLK register.
    //    * IrDA mode enable (IR_EN) be cleared in the URT_IRDA register.    
    //    * Be setted URT mode (MDS) to normal URT function in the URT_CR0 register. 
    //    * Half-duplex selection (HDX_EN) be cleared in the URT_CR0 register.
    //    * Data line select 2-lines (DAT_LINE) in the URT_CR0 register.     
    CLEAR_BIT(MURT->Instance->CLK.W,URT_CLK_CLK_EN_mask_w);
    CLEAR_BIT(MURT->Instance->IRDA.W,URT_IRDA_IR_EN_mask_w);
    URT_MODIFY_REG(MURT->Instance->CR0.W , (URT_CR0_MDS_mask_w | URT_CR0_HDX_EN_mask_w |URT_CR0_DAT_LINE_mask_w) , \
                                           (URT_CR0_MDS_uart_w | URT_CR0_HDX_EN_disable_w | URT_CR0_DAT_LINE_2_w));
    CLEAR_BIT( MURT->Instance->MUTE.W , URT_MUTE_MUTE_EN_mask_w);
    
   
    //===========================================================
    //Clear TX / RX Buffer
    SET_BIT( MURT->Instance->CR4.W , ( URT_CR4_TDAT_CLR_mask_w  | URT_CR4_RDAT_CLR_mask_w));
    #if defined(MG32_1ST)
        URT_CLEAR_BIT( MURT->Instance->MUTE.B[0] , URT_MUTE_MUTE_EN_enable_b0);
    #endif
    //=========================================================== 
    //-Clear All flag.
    //-Interrupt IE control 
    __DRV_URT_CLEAR_FLAG( MURT , (URT_FLAG_TC  | URT_FLAG_RX   | URT_FLAG_ERR | URT_FLAG_PE | URT_FLAG_FE | \
                                  URT_FLAG_NCE | URT_FLAG_ROVR | URT_FLAG_RHF));                                                                          
    WRITE_REG( MURT->Instance->INT.W , (URT_IT_PE | URT_IT_FE | URT_IT_NCE | URT_IT_ROVR | URT_ITEA));    
    
    
    

    //===========================================================                            
    //Enable the peripheral.
    __MID_URT_ENABLE(MURT);
    
    //===========================================================                            
    //TEACK and / or REACK to check before moving MURT->gState and 
    //MURT->RxState to Ready.    
    return(MID_URT_CheckIdleState(MURT));
}

/**
 *******************************************************************************
 * @brief	    Initialize the half-duplex mode according to the specified
 *       \n     paameters in the URT_HandleTypeDef and creates the associated
 *       \n     handle.
 * @details     
 * @param[in]   MURT : URT handle.
 * @return      MID status.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
MID_StatusTypeDef MID_URT_HalfDuplex_Init( URT_HandleTypeDef* MURT)
{
    //===========================================================
    //Check the URT handle allocation.
    if(MURT == NULL)                                                                                                                  
    {
        return(MID_FAILURE);
    }
    //============================================================
    //Check URT register address
    MURT->TxTransferCountMax = 4;
    switch((uint32_t)(&MURT->Instance->STA.W))
    {
        case URT0_Base:
        #if defined(URT1_Base)
        case URT1_Base:
        #endif
        #if defined(URT2_Base) 
        case URT2_Base:
        #endif   
        #if defined(URT3_Base)
        case URT3_Base:
        #endif           
                       break;
        default: 
                       return(MID_FAILURE);
    }
    //===========================================================    
    if(MURT->gState == MID_URT_STATE_RESET)                                                
    {
        //-------------------------------------------
        //Allocate lock resource and initialize it.
        MURT->Lock = MID_UnLocked;
        
        //-------------------------------------------
        //Inital the low level hardware:
        //    * GPIO 
        //    * CLCOK         
        MID_URT_MspInit(MURT);                                                      
    }

    MURT->gState = MID_URT_STATE_BUSY;
     
    
    //===========================================================                           
    //Disable the peripheral
    __MID_URT_DISABLE(MURT);                                                                         
 
    //===========================================================                        
    //Set the URT communication parameters.
    if(MID_URT_SetConfig(MURT) == MID_FAILURE)                                                       
    {
        return(MID_FAILURE);
    }
    
    if(MURT->AdvancedInit.AdvFeatureInit != URT_ADVFEATURE_NO_INIT)                
    {
        MID_URT_AdvFeatureConfig(MURT);
    }
    //===========================================================                         
    //* In half-duplex mode, the following bits must be kept cleared and setted.
    //    * CLK_EN bit be cleared in the URT_CLK register.
    //    * IrDA mode enable (IR_EN) be cleared in the URT_IRDA register.    
    //    * Be setted URT mode (MDS) to normal URT function in the URT_CR0 register. 
    //    * Half-duplex selection (HDX_EN) be cleared in the URT_CR0 register.
    //    * Data line select 2-lines (DAT_LINE) in the URT_CR0 register.     
    CLEAR_BIT(MURT->Instance->CLK.W,URT_CLK_CLK_EN_mask_w);
    CLEAR_BIT(MURT->Instance->IRDA.W,URT_IRDA_IR_EN_mask_w);
    URT_MODIFY_REG(MURT->Instance->CR0.W , (URT_CR0_MDS_mask_w | URT_CR0_HDX_EN_mask_w |URT_CR0_DAT_LINE_mask_w) , (URT_CR0_MDS_uart_w | URT_CR0_HDX_EN_enable_w | URT_CR0_DAT_LINE_1_w));
    CLEAR_BIT( MURT->Instance->MUTE.W , URT_MUTE_MUTE_EN_mask_w);
    
    //===========================================================
    //Clear TX / RX Buffer
    SET_BIT( MURT->Instance->CR4.W , ( URT_CR4_TDAT_CLR_mask_w  | URT_CR4_RDAT_CLR_mask_w));
    #if defined(MG32_1ST)
        URT_CLEAR_BIT( MURT->Instance->MUTE.B[0] , URT_MUTE_MUTE_EN_enable_b0);
    #endif
    //=========================================================== 
    //-Clear All flag.
    //-Interrupt IE control 
    __DRV_URT_CLEAR_FLAG( MURT , (URT_FLAG_TC  | URT_FLAG_RX   | URT_FLAG_ERR | URT_FLAG_PE | URT_FLAG_FE | \
                                  URT_FLAG_NCE | URT_FLAG_ROVR | URT_FLAG_RHF));
    WRITE_REG( MURT->Instance->INT.W , (URT_IT_PE | URT_IT_FE | URT_IT_NCE | URT_IT_ROVR | URT_ITEA));      
    
    //===========================================================                            
    //Enable the peripheral.
    __MID_URT_ENABLE(MURT);
    
    //===========================================================                            
    //TEACK and/or REACK to check before moving MURT->gState and 
    //MURT->RxState to Ready.
    return(MID_URT_CheckIdleState(MURT));
    
}


/**
 *******************************************************************************
 * @brief	    Initalize the multiprocessor mode according to the specified
 *       \n     parameters in the URT_HandleTypeDef and initialize the 
 *       \n     associated handle.
 * @details     
 * @param[in]   MURT         : URT handle.
 * @param[in]   Address      : URT node address.
 * @param[in]   AddressMsk   : URT addresss compare bit.
 * @param[in]   gAddressState: Enable or Disable multi-processor global slave address.             
 *       \n     - URT_GLOBAL_ADDRESS_DISABLE  : Disable global slave address.
 *       \n     - URT_GLOBAL_ADDRESS_ENABLE   : Enable global slave address.
 * @return      MID status.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
MID_StatusTypeDef MID_URT_MultiProcessor_Init( URT_HandleTypeDef* MURT , uint8_t Address, uint8_t AddressMsk , uint8_t gAddressState)
{
    //===========================================================    
    //Check the URT handle allocation.
    if(MURT == NULL)                                                                                                                  
     {
         return(MID_FAILURE);
     }
     //============================================================
     //Check URT register address
     MURT->TxTransferCountMax = 4;
     switch((uint32_t)(&MURT->Instance->STA.W))
     {
         case URT0_Base:
        #if defined(URT1_Base)
        case URT1_Base:
        #endif
        #if defined(URT2_Base) 
        case URT2_Base:
        #endif   
        #if defined(URT3_Base)
        case URT3_Base:
        #endif           
                       break;
        default: 
                        return(MID_FAILURE);
     }
     //===========================================================                    
     if(MURT->gState == MID_URT_STATE_RESET)                                                
     {
         //-------------------------------------------
         //Allocate lock resource and initialize it.
         MURT->Lock = MID_UnLocked;
         
         //-------------------------------------------
         //Inital the low level hardware:
         //    * GPIO 
         //    * CLCOK         
         MID_URT_MspInit(MURT);                                                      
     }

     MURT->gState = MID_URT_STATE_BUSY;
     
     
    //===========================================================                           
    //Disable the peripheral
    __MID_URT_DISABLE(MURT);                                                                         
 
    //===========================================================                        
    //Set the URT communication parameters.
    if(MID_URT_SetConfig(MURT) == MID_FAILURE)                                                       
    {
        return(MID_FAILURE);
    }
    
    if(MURT->AdvancedInit.AdvFeatureInit != URT_ADVFEATURE_NO_INIT)                
    {
        MID_URT_AdvFeatureConfig(MURT);
    }
    //===========================================================                         
    //* In multiprocessor mode, the following bits must be kept cleared and setted.
    //    * CLK_EN bit be cleared in the URT_CLK register.
    //    * IrDA mode enable (IR_EN) be cleared in the URT_IRDA register.    
    //    * Be setted URT mode (MDS) to normal URT function in the URT_CR0 register. 
    //    * Half-duplex selection (HDX_EN) be cleared in the URT_CR0 register.
    //    * Data line select 2-lines (DAT_LINE) in the URT_CR0 register.     
    CLEAR_BIT(MURT->Instance->CLK.W,URT_CLK_CLK_EN_mask_w);
    CLEAR_BIT(MURT->Instance->IRDA.W,URT_IRDA_IR_EN_mask_w);
    URT_MODIFY_REG(MURT->Instance->CR0.W , (URT_CR0_MDS_mask_w | URT_CR0_HDX_EN_mask_w |URT_CR0_DAT_LINE_mask_w) , (URT_CR0_MDS_adr_w | URT_CR0_HDX_EN_disable_w | URT_CR0_DAT_LINE_2_w));
    SET_BIT( MURT->Instance->MUTE.W , URT_MUTE_MUTE_EN_mask_w);
    
    //==========================================================
    //Set the URT address node and address compare bit mask.
    
    #if defined(MG32_1ST)
        if( MURT->Init.WordLength == UART_WORDLENGTH_7B)
        {
            URT_WRITE_REG( MURT->Instance->SADR.B[0] , (uint8_t)(Address<<1));
            URT_WRITE_REG( MURT->Instance->SADR.B[1] , (uint8_t)(AddressMsk<<1));
        }
        else
        {
            URT_WRITE_REG(MURT->Instance->SADR.H[0], (uint16_t)((AddressMsk << 8) | Address));
        }
        URT_MODIFY_REG( MURT->Instance->CR0.B[0], URT_CR0_GSA_EN_mask_b0 , gAddressState);
        URT_SET_BIT( MURT->Instance->MUTE.B[0] , URT_MUTE_MUTE_EN_enable_b0);
    #else
        URT_WRITE_REG(MURT->Instance->SADR.H[0], (uint16_t)((AddressMsk << 8) | Address));
        URT_MODIFY_REG( MURT->Instance->CR0.B[0], URT_CR0_GSA_EN_mask_b0 , gAddressState);
    #endif

    //===========================================================
    //Clear TX / RX Buffer
    SET_BIT( MURT->Instance->CR4.W , ( URT_CR4_TDAT_CLR_mask_w  | URT_CR4_RDAT_CLR_mask_w));
    
    //=========================================================== 
    //-Clear All flag.
    //-Interrupt IE control 
    __DRV_URT_CLEAR_FLAG( MURT, (URT_FLAG_TC  | URT_FLAG_RX   | URT_FLAG_ERR | URT_FLAG_PE | URT_FLAG_FE | \
                                 URT_FLAG_NCE | URT_FLAG_ROVR | URT_FLAG_RHF));                                    
    WRITE_REG( MURT->Instance->INT.W , (URT_IT_PE | URT_IT_FE | URT_IT_NCE | URT_IT_ROVR | URT_ITEA));     
    
    //===========================================================                            
    //Enable the peripheral.
    __MID_URT_ENABLE(MURT);
    
    //===========================================================                            
    //TEACK and / or REACK to check before moving MURT->gState
    //and MURT->RxState to Ready.
    return(MID_URT_CheckIdleState(MURT));
}


/**
 *******************************************************************************
 * @brief	    Initialize the RS485 enable feature according to the specified
 *              parameters in the URT_InitTypeDef and creates the associated handle.
 * @details     
 * @param[in]   MURT          : URT handle. 
 * @param[in]   URT_DE_POLARITY : Control DE signal wether inverse or not.
 *  @arg\b      - MID_URT_DE_POLARITY_LOW : DE signal is active low. 
 *  @arg\b      - MID_URT_DE_POLARITY_HIGH: DE signal is active high.
 * @param[in]   URT_DE_GT    : Enable assertion time & deassertion time.
 *      \n                     Assertion time - between the activation of the DE signal
 *      \n                                      and the beginning of the start bit. 
 *      \n                     Deassertion time - between the end of the last stop bit,
 *      \n                                      and the de-activation of the DE signal.
 *  @arg\b      - MID_URT_DEGUARDTIME_1_4 : DE guard time is 1/4 bit time.
 *  @arg\b      - MID_URT_DEGUARDTIME_1_2 : DE guard time is 1/2 bit time.
 *  @arg\b      - MID_URT_DEGUARDTIME_1   : DE guard time is 1 bit time. 
 *  @arg\b      - MID_URT_DEGUARDTIME_2   : DE guard time is 2 bit time. 
 * @return      MID state.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
MID_StatusTypeDef MID_URT_RS485_Init( URT_HandleTypeDef *MURT, uint32_t URT_DE_POLARITY , uint32_t URT_DE_GT)
{
    //=========================================================
    //Check the URT handle allocation.
    if(MURT== NULL)
    {
        return( MID_ERROR);
    }
    //============================================================
    //Check URT register address
    MURT->TxTransferCountMax = 4;
    switch((uint32_t)(&MURT->Instance->STA.W))
    {
        case URT0_Base:
        #if defined(URT1_Base)
        case URT1_Base:
        #endif
        #if defined(URT2_Base) 
        case URT2_Base:
        #endif   
        #if defined(URT3_Base)
        case URT3_Base:
        #endif           
                       break;
        default: 
                       return(MID_FAILURE);
    }
    //=========================================================
    if(MURT->gState == MID_URT_STATE_RESET)
    {
        //------------------------------------------------------
        //Allocate lock resource and initialize it.
        MURT->Lock = MID_UNLOCKED;
        //------------------------------------------------------
        //Init the low level hardware : (exsample for GPIO , CLOCK ......)
        MID_URT_MspInit(MURT);
    }


    MURT->gState = MID_URT_STATE_BUSY;
    
    //=========================================================
    // Disable the Peripheral
    __MID_URT_DISABLE(MURT);
    
    //========================================================
    //Set the UART Communication parameters.
    if( MID_URT_SetConfig( MURT) == MID_ERROR)
    {
        return(MID_ERROR);
    }
    if(MURT->AdvancedInit.AdvFeatureInit != URT_ADVFEATURE_NO_INIT)
    {
        MID_URT_AdvFeatureConfig( MURT);
    }
    
    //========================================================
    //Set : 
    //    1. Enable the DE mode  
    //    2. Set the DE polarity.
    //    3. Set the DE guard time.
    MODIFY_REG( MURT->Instance->CR0.W , ( URT_DEGUARDTIME_MASK | URT_DE_POLARITY_MASK) , ( URT_DE_POLARITY | URT_DE_GT));
    //===========================================================
    //Clear TX / RX Buffer
    SET_BIT( MURT->Instance->CR4.W , ( URT_CR4_TDAT_CLR_mask_w  | URT_CR4_RDAT_CLR_mask_w));
    #if defined(MG32_1ST)
        URT_CLEAR_BIT( MURT->Instance->MUTE.B[0] , URT_MUTE_MUTE_EN_enable_b0);
    #endif
    //=========================================================== 
    //-Clear All flag.
    //-Interrupt IE control  
    __DRV_URT_CLEAR_FLAG( MURT , (URT_FLAG_TC  | URT_FLAG_RX   | URT_FLAG_ERR | URT_FLAG_PE | URT_FLAG_FE | \
                                  URT_FLAG_NCE | URT_FLAG_ROVR | URT_FLAG_RHF));
    WRITE_REG( MURT->Instance->INT.W , (URT_IT_PE | URT_IT_FE | URT_IT_NCE | URT_IT_ROVR | URT_ITEA));     
    
    //========================================================
    //Enable the peripheral
    __MID_URT_ENABLE(MURT);
    
    //========================================================
    //MURT->gState and MURT->RxState to Ready.
    return(MID_URT_CheckIdleState(MURT));
}



/**
 *******************************************************************************
 * @brief	    DeInitialize the URT peripheral.
 * @details     
 * @param[in]   MURT : URT handle.
 * @return      MID status.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
MID_StatusTypeDef MID_URT_DeInit( URT_HandleTypeDef* MURT )
{
    //===========================================================    
    //Check the URT handle allocation.
    if(MURT == NULL)
    {
        return(MID_FAILURE);
    }
    //============================================================
    //Check URT register address
    switch((uint32_t)(&MURT->Instance->STA.W))
    {
        case URT0_Base:
        #if defined(URT1_Base)
        case URT1_Base:
        #endif
        #if defined(URT2_Base) 
        case URT2_Base:
        #endif   
        #if defined(URT3_Base)
        case URT3_Base:
        #endif           
        #if defined(URT4_Base)
        case URT4_Base:
        #endif           
        #if defined(URT5_Base)
        case URT5_Base:
        #endif           
        #if defined(URT6_Base)
        case URT6_Base:
        #endif           
        #if defined(URT7_Base)
        case URT7_Base:
        #endif           
                       break;
        default: 
                       return(MID_FAILURE);
    }

    MURT->gState = MID_URT_STATE_BUSY;
    
    //===========================================================    
    //Disable the peripheral.
    __MID_URT_DISABLE(MURT);
    
    MURT->Instance->STA.W = 0xFFFFFFFF;
    MURT->Instance->INT.W = 0;
    MURT->Instance->CLK.W = 0;
    MURT->Instance->CR0.W = 0;
    MURT->Instance->CR1.W = 0;
    MURT->Instance->CR2.W = 0;
    MURT->Instance->CR3.W = 0;
    MURT->Instance->CR4.W = (URT_CR4_RDAT_CLR_enable_w | URT_CR4_TDAT_CLR_enable_w);
    //===========================================================    
    //DeInit the low level hardware.
    MID_URT_MspDeInit(MURT);

    MURT->ErrorCode = MID_URT_ERROR_NONE;
    MURT->gState    = MID_URT_STATE_RESET;
    MURT->RxState   = MID_URT_STATE_RESET;
    
    //===========================================================
    //Process Unlock.
    __MID_UNLOCK(MURT);
    
    
    return(MID_SUCCESS);
}

/**
 *******************************************************************************
 * @brief	    Initalize the URT MSP.
 * @details     
 * @param[in]   MURT : URT handle.   
 * @return      No
 * @exception   No
 * @note        No
 *******************************************************************************
 */
__WEAK void MID_URT_MspInit(URT_HandleTypeDef* MURT)
{
    //===========================================================
    //Prevent unsed argument(s) compilation warning
    UNUSED(MURT);
    
    //===========================================================
    //Note : This function should not be modified , when the callback is needed,
    //       the MID_URT_MspInit can be implemented in the user file.
    
}

/**
 *******************************************************************************
 * @brief	    DeInitalize the URT MSP.
 * @details     
 * @param[in]   MURT : URT handle.   
 * @return      No
 * @exception   No
 * @note        No
 *******************************************************************************
 */
__WEAK void MID_URT_MspDeInit(URT_HandleTypeDef* MURT)
{
    //===========================================================
    //Prevent unsed argument(s) compilation warning
    UNUSED(MURT);
    
    //===========================================================
    //Note : This function should not be modified , when the callback is needed,
    //       the MID_URT_MspDeInit can be implemented in the user file.
    
}


///@}



/**
 * @name    URT Transmit / Receive functions.
 *             
 */ 
///@{

/**
 *******************************************************************************
 * @brief	    Send an amount of data in blocking mode.
 * @details     
 * @param[in]   MURT    : URT handle. 
 * @param[in]   pDATA   : Pointer to data buffer.
 * @param[in]   SIZE    : Size Amout of data to be sent.
 * @param[in]   TIMEOUT : Timeout duration.
 * @return      MID status.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
MID_StatusTypeDef MID_URT_Transmit(URT_HandleTypeDef* MURT, uint8_t *pDATA, uint16_t SIZE , uint32_t TIMEOUT)
{
    uint32_t tickstart = 0;
    
    //===========================================================
    //Check that a TX process is not already on going.
    if(MURT->gState == MID_URT_STATE_READY)
    {
        if((pDATA == NULL) || (SIZE == 0))
        {
            return( MID_ERROR);
        }
    
        //===========================================================
        //Process locked
        __MID_LOCK(MURT);

        MURT->ErrorCode = MID_URT_ERROR_NONE;
        MURT->gState    = MID_URT_STATE_BUSY_TX;
        
        //===========================================================
        //Inital tickstart for timeout managment
        tickstart = MID_GetTick();
        
        MURT->TxTransferSize  = SIZE;
        MURT->TxTransferCount = SIZE;

        while(MURT->TxTransferCount >0)
        {
            MURT->TxTransferCount = MURT->TxTransferCount - 1;
            
            MURT->Instance->TDAT.B[0] = (*pDATA++);
            
            if(MID_URT_WaitOnFlagUntilTimeout( MURT, URT_IT_TX, CLR, tickstart, TIMEOUT) != MID_OK)
            {
                return( MID_TIMEOUT);
            }
        }
        if(MID_URT_WaitOnFlagUntilTimeout( MURT, URT_IT_TC, CLR, tickstart, TIMEOUT) != MID_OK)
        {
            return(MID_TIMEOUT);
        }

        //===========================================================
        //At end of TX process.
        MURT->gState = MID_URT_STATE_READY;
        
        //===========================================================
        //Process Unlocked.
        __MID_UNLOCK(MURT);
        
        
        return(MID_OK);
    }
    else
    {
        return(MID_BUSY);
    }
}

/**
 *******************************************************************************
 * @brief	    Receive an amount of data in blocking mode.
 * @details     
 * @param[in]   MURT    : URT handle. 
 * @param[in]   pDATA   : Pointer to data buffer.
 * @param[in]   SIZE    : Size Amout of data to be sent.
 * @param[in]   TIMEOUT : Timeout duration.
 * @return      MID status.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
MID_StatusTypeDef MID_URT_Receive(URT_HandleTypeDef* MURT, uint8_t* pDATA, uint16_t SIZE , uint32_t TIMEOUT)
{
    uint32_t  tickstart = 0;

    if(MURT->RxState == MID_URT_STATE_READY)
    {
        //===========================================================
        //Check that a Rx process is not already on going.
        if((pDATA == NULL) || (SIZE == 0))
        {
            return( MID_ERROR);
        }
        
        //===========================================================
        //Process Locked
        __MID_LOCK(MURT);
        
        MURT->ErrorCode = MID_URT_ERROR_NONE;
        MURT->RxState   = MID_URT_STATE_BUSY_RX;
        
        //===========================================================
        //Init tickstart for timeout managment
        tickstart = MID_GetTick();
        
        MURT->RxTransferSize  = SIZE;
        MURT->RxTransferCount = SIZE; 
        SET_BIT(MURT->Instance->STA.W, (URT_FLAG_RHF | URT_FLAG_FE | URT_FLAG_PE | URT_FLAG_NCE | URT_FLAG_ROVR));
        
        //===========================================================
        //As long as data have to be received.
        while(MURT->RxTransferCount >0)
        {
            MURT->RxTransferCount = MURT->RxTransferCount - 1;
            
            if(MID_URT_WaitOnFlagUntilTimeout(MURT, URT_IT_RX, CLR, tickstart, TIMEOUT)!= MID_OK)
            {
                return(MID_TIMEOUT);
            }
            #if defined(MG32_1ST)
                if( MURT->Init.WordLength == UART_WORDLENGTH_8B)
                {
                    *pDATA++ = (uint8_t)(MURT->Instance->RDAT.B[0]);
                }
                else
                {
                    *pDATA++ = ((uint8_t)(MURT->Instance->RDAT.B[0]) & 0x7F);
                }
            #else
                *pDATA++ = (uint8_t)(MURT->Instance->RDAT.B[0]);
            #endif
        }
      
        //===========================================================
        //At end of RX process.
        MURT->RxState = MID_URT_STATE_READY;
        
        //===========================================================
        //Process Unlocked
        __MID_UNLOCK(MURT);
        
        return(MID_OK);
    }
    else
    {
        return(MID_BUSY);
    }
}
/**
 *******************************************************************************
 * @brief	    Send an amount of data in interrupt mode.
 * @details     
 * @param[in]   MURT    : URT handle. 
 * @param[in]   pDATA   : Pointer to data buffer.
 * @param[in]   SIZE    : Size Amout of data to be sent.
 * @return      MID status.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
MID_StatusTypeDef MID_URT_Transmit_IT( URT_HandleTypeDef* MURT , uint8_t* pDATA , uint16_t SIZE) 
{
    if( MURT->gState == MID_URT_STATE_READY)
    {
        if(( MURT == NULL) || ( SIZE == 0U ))
        {
            return( MID_ERROR);
        }

        __MID_LOCK(MURT);                                                  // Process Locked 
        
        MURT->pTxBuffPtr      = pDATA;
        MURT->TxTransferSize  = SIZE;
        MURT->TxTransferCount = SIZE;        

        MURT->ErrorCode = MID_URT_ERROR_NONE;
        MURT->gState    = MID_URT_STATE_BUSY_TX;
        
        __MID_UNLOCK(MURT);                                                // Process Unlocked
        
        //=======================================================
        //Send One byte Data.
        
        MURT->Instance->TDAT.B[0] = pDATA[0];
        MURT->pTxBuffPtr          = MURT->pTxBuffPtr + 1;
        MURT->TxTransferCount     = MURT->TxTransferCount - 1;
        //=======================================================
        //Enable :
        //    1. Transmit Data Register Empty interrupt.
        //    2. URT interrupt master switch.
        SET_BIT( MURT->Instance->INT.W , ( URT_INT_TX_IE_mask_w ));
        
        return( MID_OK);     
    }
    else
    {

        uint32_t MID_URTIRQ_Flag;
        //===========================================================
        //Check that a TX process is not already ongoing
        MID_URTIRQ_Flag = (READ_REG( MURT->Instance->STA.W)) & (READ_REG( MURT->Instance->INT.W));
        if( ( ( MID_URTIRQ_Flag & URT_IT_TC)!=0 )
         || ( ( MID_URTIRQ_Flag & URT_IT_TX)!=0 ) )
        {
            ifun_URT_EndTransmit_IT( MURT);

            __DRV_URT_CLEAR_FLAG( MURT , URT_IT_TX );
            __DRV_URT_CLEAR_FLAG( MURT , URT_IT_TC );
        }
        MID_Delay(2);
        return( MID_BUSY);
    }
}

/**
 *******************************************************************************
 * @brief	    Receive an amount of data in interrupt mode.
 * @details     
 * @param[in]   MURT    : URT handle. 
 * @param[in]   pDATA   : Pointer to data buffer.
 * @param[in]   SIZE    : amount of data to be received.
 * @return      MID status.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
MID_StatusTypeDef MID_URT_Receive_IT( URT_HandleTypeDef* MURT, uint8_t *pDATA, uint16_t SIZE)
{
    if( MURT->RxState == MID_URT_STATE_READY)
    {
        if((pDATA == NULL) || (SIZE == 0))
        {
            return( MID_ERROR);
        }
        
        __MID_LOCK(MURT);                                                                                                         // Process Locked 
        
        MURT->pRXBuffPtr      = pDATA;
        MURT->RxTransferSize  = SIZE;
        MURT->RxTransferCount = SIZE;        
        
        
        MURT->ErrorCode = MID_URT_ERROR_NONE;
        MURT->RxState   = MID_URT_STATE_BUSY_RX;
        
        SET_BIT(MURT->Instance->STA.W, (URT_FLAG_RHF | URT_FLAG_FE | URT_FLAG_PE | URT_FLAG_NCE | URT_FLAG_ROVR));
        __MID_UNLOCK(MURT);                                                                                                       // Process Unlocked
        
        //===============================================================
        //Enable 
        //    1. Enable the URT Error Interrupt : (Frame error , noise error , overrun error)
        //    2. the URT parity error interrupt .
        //    3. the URT data register not empty interrupt.
        SET_BIT( MURT->Instance->INT.W , (URT_IT_ERR | URT_IT_RX ));
        
        return(MID_OK);
    }
    else
    {
        return(MID_BUSY);
    }
}

/**
 *******************************************************************************
 * @brief	    Send an amount of data in DMA mode.
 * @details     
 * @param[in]   MURT    : URT handle. 
 * @param[in]   pDATA   : Pointer to data buffer.
 * @param[in]   SIZE    : amount of data to be received.
 * @return      MID status.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
MID_StatusTypeDef MID_URT_Transmit_DMA( URT_HandleTypeDef *MURT, uint8_t *pDATA, uint16_t SIZE)
{
    //===============================================================
    //Check that TX process is not already on going.
    if(MURT->gState == MID_URT_STATE_READY)   
    {
        if((pDATA == NULL) || (SIZE == 0U))
        {
            return(MID_ERROR);
        }
        
        //===============================================================
        //Process Locked 
        __MID_LOCK(MURT);
        
        //===============================================================
        MURT->pTxBuffPtr      = pDATA;
        MURT->TxTransferSize  = SIZE;
        MURT->TxTransferCount = SIZE;

        MURT->ErrorCode       = MID_URT_ERROR_NONE;
        MURT->gState          = MID_URT_STATE_BUSY_TX;
        
        //===============================================================
        //Set the UART DMA transfer complete callback.
        MURT->mDMA_TX->XferCpltCallback = ifun_URT_DMATransmitCplt;
        
        //===============================================================
        //Set the UART DMA Half transfer complete callback
        MURT->mDMA_TX->XferHalfCpltCallback = ifun_URT_DMATxHalfCplt;
        
        //===============================================================
        //Set the DMA error callback 
        MURT->mDMA_TX->XferErrorCallback    = ifun_URT_DMAError;
        
        //===============================================================
        //Set the DMA abort callback
        MURT->mDMA_TX->XferAbortCallback    = NULL;
        
        //===============================================================
        //Enable the URT transmit DMA channel.
        MID_DMA_Start_IT(MURT->mDMA_TX, (uint32_t)MURT->pTxBuffPtr, (uint32_t)&MURT->Instance->TDAT.W, SIZE);
        
        //==============================================================
        //Clear the TC flag 
        __DRV_URT_CLEAR_FLAG(MURT , URT_IT_TC);
        
        //===============================================================
        //Process UnLocked 
        __MID_UNLOCK(MURT);
        
        //===============================================================
        //Enable the DMA transfer for transmit request 
        CLEAR_BIT( MURT->Instance->CR2.W , URT_CR2_TX_EN_mask_w);
        SET_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_TXEN_mask_w);
        SET_BIT( MURT->Instance->CR2.W , URT_CR2_TX_EN_mask_w);
        
        return( MID_OK);
    }
    else
    {
        return( MID_BUSY);
    }
}

/**
 *******************************************************************************
 * @brief	    Receive an amount of data in DMA mode.
 * @details     
 * @param[in]   MURT    : URT handle. 
 * @param[in]   pDATA   : Pointer to data buffer.
 * @param[in]   SIZE    : amount of data to be received.
 * @return      MID status.
 * @exception   No
 * @note        In MG32F02A132 / 072 if the application could change WordLength from 8bit to 7bit 
 *              bit7 of data will keep bit7 status of 8 bit data.  
 *******************************************************************************
 */
MID_StatusTypeDef MID_URT_Receive_DMA( URT_HandleTypeDef *MURT , uint8_t *pDATA , uint16_t SIZE)
{
    //===============================================================
    //Check that RX process is not already on going.
    if( MURT->RxState == MID_URT_STATE_READY)
    {
        if(( pDATA == NULL) || (SIZE == 0U))
        {
            return( MID_ERROR);
        }
        
        //===============================================================
        //Process Locked 
        __MID_LOCK(MURT);
        
        //===============================================================
        MURT->pRXBuffPtr      = pDATA;
        MURT->RxTransferSize  = SIZE;
        
        MURT->ErrorCode       = MID_URT_ERROR_NONE;
        MURT->RxState         = MID_URT_STATE_BUSY_RX;
        
        SET_BIT(MURT->Instance->CR4.W, URT_CR4_RDAT_CLR_mask_w);
        SET_BIT(MURT->Instance->STA.W, (URT_FLAG_RHF | URT_FLAG_RX | URT_FLAG_FE | URT_FLAG_PE | URT_FLAG_NCE | URT_FLAG_ROVR));
        //===============================================================
        //Set the UART DMA receive complete callback
        MURT->mDMA_RX->XferCpltCallback     = ifun_URT_DMAReceiveCplt;
        
        //===============================================================
        //Set the UART DMA Half receive complete callback
        MURT->mDMA_RX->XferHalfCpltCallback = ifun_URT_DMARxHalfCplt; 
        
        //===============================================================
        //Set the DMA error callback
        MURT->mDMA_RX->XferErrorCallback = ifun_URT_DMAError;
        
        //===============================================================
        //Set the DMA abort callback
        MURT->mDMA_RX->XferAbortCallback = NULL;
        
        //===============================================================
        //Enable the DMA channel
        MID_DMA_Start_IT( MURT->mDMA_RX , (uint32_t)&MURT->Instance->RDAT.W, (uint32_t)MURT->pRXBuffPtr, SIZE);
        
        //===============================================================
        //Process UnLocked 
        __MID_UNLOCK(MURT);
        
        //===============================================================
        //Enable the URT error interrupt ( PE , FE , NE , ROV)
        SET_BIT( MURT->Instance->INT.W , (URT_IT_ERR));
        
        //===============================================================
        //Enable the DMA transfer for the receiver request.
        CLEAR_BIT( MURT->Instance->CR2.W , URT_CR2_RX_EN_mask_w);
        SET_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_RXEN_mask_w);
        SET_BIT( MURT->Instance->CR2.W , URT_CR2_RX_EN_mask_w);
        
        return( MID_OK);
    }
    else
    {
        return( MID_BUSY);
    }
}


/**
 *******************************************************************************
 * @brief	    Pause the DMA Transfer.
 * @details     
 * @param[in]   MURT    : URT handle. 
 * @return      MID status.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
MID_StatusTypeDef MID_URT_DMAPause( URT_HandleTypeDef *MURT)
{
    //===============================================================
    //Process Locked 
    __MID_LOCK(MURT);
    
    if((MURT->gState == MID_URT_STATE_BUSY_TX) &&
        READ_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_TXEN_mask_w)!=0)
    {
        //-----------------------------------------------------------
        //Disable the URT DMA TX request.
        CLEAR_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_TXEN_mask_w);
    }
    if((MURT->gState == MID_URT_STATE_BUSY_RX) &&
        READ_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_RXEN_mask_w)!=0)
    {
        //-----------------------------------------------------------
        //Disable PE & ERR interrupt.
        CLEAR_BIT( MURT->Instance->INT.W , (URT_IT_PE | URT_IT_ERR));
        
        //-----------------------------------------------------------
        //Disable the URT DMA RX request.
        CLEAR_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_RXEN_mask_w);
    }
    
    //===============================================================
    //Process UnLocked 
    __MID_UNLOCK(MURT);
    
    return( MID_OK);
}

/**
 *******************************************************************************
 * @brief	    Resume the DMA Transfer.
 * @details     
 * @param[in]   MURT    : URT handle. 
 * @return      MID status.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
MID_StatusTypeDef MID_URT_DMAResume( URT_HandleTypeDef *MURT)
{
    //===============================================================
    //Process Locked 
    __MID_LOCK(MURT);
    
    if( MURT->gState == MID_URT_STATE_BUSY_TX)
    {
        //===============================================================
        //Enable the URT DMA TX request
        CLEAR_BIT( MURT->Instance->CR2.W , URT_CR2_TX_EN_mask_w);
        SET_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_TXEN_mask_w);
        SET_BIT( MURT->Instance->CR2.W , URT_CR2_TX_EN_mask_w);
    }
    if( MURT->RxState == MID_URT_STATE_BUSY_RX)
    {
        //===============================================================
        //Clear the Overrun flag and RX hold flag 
        //before resuming the Rx transfer
        __DRV_URT_CLEAR_FLAG( MURT , (URT_FLAG_ROVR | URT_FLAG_RHF));

        //===============================================================
        //Reenable PE and ERR interrupt
        SET_BIT( MURT->Instance->INT.W , (URT_IT_ERR));
        
        //===============================================================
        //Enable the URT DMA RX request
        SET_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_RXEN_mask_w);
    }
    
    
    //===============================================================
    //Process UnLocked 
    __MID_UNLOCK(MURT);
    
    return( MID_OK);
}
/**
 *******************************************************************************
 * @brief	    Stop the DMA Transfer
 * @details     
 * @param[in]   MURT    : URT handle. 
 * @return      MID status.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
MID_StatusTypeDef MID_URT_DMAStop( URT_HandleTypeDef *MURT)
{
    //===============================================================
    //This lock in  not implemented on this function to allow the user
    //application to call the MID URT function uneder callbcks 
    //MID_URT_RxHalfCpltCallback:
    //indeed , when MID_DMA_Abort() is called , the DMA Tx / Rx transfer or
    //half transfer complete interrupt is generated if the DMA transfer 
    //interruption occurs at the middle or at the end of the stream and the
    //corresponding call back is executed.
    
    //-----------------------------------------------------------
    //Stop UART DMA Tx request if on going
    if( READ_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_TXEN_mask_w)!=0)
    {
        CLEAR_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_TXEN_mask_w);
        
        //-----------------------------------------------------------
        //Abort the URT DMA Tx channel
        if(MURT->mDMA_TX != NULL)
        {
            MID_DMA_Abort(MURT->mDMA_TX);
        }            
        
        ifun_URT_EndTxTransfer(MURT);
    }
    //-----------------------------------------------------------
    //Stop UART DMA Rx request if on going  
    if( READ_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_RXEN_mask_w)!=0)
    {
        CLEAR_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_RXEN_mask_w);
        
        //-----------------------------------------------------------
        //Abort the URT DMA RX channel
        if(MURT->mDMA_RX != NULL)
        {
            MID_DMA_Abort(MURT->mDMA_RX);
        }
        
        ifun_URT_EndTxTransfer(MURT);
    }
    
    return( MID_OK);
}

/**
 *******************************************************************************
 * @brief	    Abort on going transfers (blocking mode).
 * @details     
 * @param[in]   MURT    : URT handle. 
 * @return      MID status.
 * @exception   No
 * @note        This procedure could be used for aborting any on going transfer
 *    \n        started in Interrupt or DMA mode.
 *    \n        This procedure performs following operations:
 *    \n        - Disable UART Interrupt (TX and RX).
 *    \n        - Disable the DMA transfer in the peripheral register.
 *    \n        - Abort DMA transfer by calling MID_DMA_Abort.
 *    \n        - Set handle state to READY
 *******************************************************************************
 */
MID_StatusTypeDef MID_URT_Abort( URT_HandleTypeDef *MURT)
{
    //===============================================================
    //Disable interrupt: (TX , TC, RX, PE, ERR  interrupts
    CLEAR_BIT( MURT->Instance->INT.W , (URT_IT_TX | URT_IT_TC | URT_IT_RX | URT_IT_ERR));
    
    //===============================================================
    //Disable the UART DMA TX request if enable.
    if( READ_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_TXEN_mask_w)!=0)
    {
        CLEAR_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_TXEN_mask_w);
        //-----------------------------------------------------------
        //Abort the URT DMA TX channel
        if( MURT->mDMA_TX != NULL)
        {
            //-----------------------------------------------------------
            //Set the UART DMA Abort callback to Null.
            //No call back execution at end of DMA abort procedure
            MURT->mDMA_TX->XferAbortCallback = NULL;
            
            MID_DMA_Abort(MURT->mDMA_TX);
        }
    }
    //===============================================================
    //Disable the UART DMA RX request if enable.
    if( READ_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_RXEN_mask_w)!=0)
    {
        CLEAR_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_RXEN_mask_w);
        //-----------------------------------------------------------
        //Abort the UART DMA Rx channel 
        if( MURT->mDMA_RX != NULL)
        {
            //-----------------------------------------------------------
            //Set the UART DMA Abort callback to Null.
            //No call back execution at end of DMA abort procedure
            MURT->mDMA_RX->XferAbortCallback = NULL;
            
            MID_DMA_Abort(MURT->mDMA_RX);
        }
    }
    //===============================================================
    //Reset Tx and Rx transfer counters.
    MURT->TxTransferCount = 0;
    MURT->RxTransferCount = 0;
    
    //===============================================================
    //Clear the error flags ( ROVR , NCE , PE , FE)
    __DRV_URT_CLEAR_FLAG( MURT, (URT_IT_ROVR | URT_IT_NCE | URT_IT_PE | URT_IT_FE));
    
    //===============================================================
    //Restore RxState & gState to Ready.
    MURT->gState  = MID_URT_STATE_READY;
    MURT->RxState = MID_URT_STATE_READY;
    
    //===============================================================
    //Reset Handle ErrorCode to No Error
    MURT->ErrorCode = MID_URT_ERROR_NONE;
    
    
    return( MID_OK);
}

/**
 *******************************************************************************
 * @brief	    Abort ongoing Transmit transfer (blocking mode) .
 * @details     
 * @param[in]   MURT    : URT handle. 
 * @return      MID status.
 * @exception   No
 * @note        This procedure could be used for aborting any ongoing Tx transfer 
 *    \n        started in Interrupt or DMA mode.
 *    \n        This procedure performs following operations :
 *    \n        - Disable UART Interrupts (Tx)
 *    \n        - Disable the DMA transfer in the peripheral register (if enabled)
 *    \n        - Abort DMA transfer by calling HAL_DMA_Abort
 *    \n        - Set handle state to READY
 *******************************************************************************
 */
MID_StatusTypeDef MID_URT_AbortTransmit( URT_HandleTypeDef *MURT)
{
    //===============================================================
    //Disable TC and TX interrupt
    CLEAR_BIT( MURT->Instance->INT.W , (URT_IT_TC | URT_IT_TX));
    
    //===============================================================
    //Disable the URT DMA Tx request if enabled
    if( READ_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_TXEN_mask_w)!=0)
    {
        CLEAR_BIT( MURT->Instance->CR3.W , URT_CR0_DMA_TXEN_mask_w);
        
        //-----------------------------------------------------------
        //Abort the UART DMA TX channel
        if( MURT->mDMA_TX != NULL)
        {
            //-----------------------------------------------------------
            //Set the URT DMA Abort callback to Null.
            //No call back execution at end of DMA abort procedure.
            MURT->mDMA_TX->XferAbortCallback = NULL;
            
            MID_DMA_Abort(MURT->mDMA_TX);
        }
    }
    
    //===============================================================
    //Reset TX transfer counter.
    MURT->TxTransferCount = 0U;
    
    //===============================================================
    //Restore gState to READY.
    MURT->gState = MID_URT_STATE_READY;
    
    
    return( MID_OK);
}

/**
 *******************************************************************************
 * @brief	    Abort ongoing Receive transfer (blocking mode).
 * @details     
 * @param[in]   MURT    : URT handle. 
 * @return      MID status.
 * @exception   No
 * @note        This procedure could be used for aborting any on going Rx transfer 
 *    \n        started in Interrupt or DMA mode.
 *    \n        This procedure performs following operations :
 *    \n        - Disable UART Interrupts (Rx)
 *    \n        - Disable the DMA transfer in the peripheral register (if enabled)
 *    \n        - Abort DMA transfer by calling HAL_DMA_Abort.
 *    \n        - Set handle State to READY
 *******************************************************************************
 */
MID_StatusTypeDef MID_URT_AbortReceive( URT_HandleTypeDef * MURT)
{
    //===============================================================
    //Disable  ERR (PE , FE , NE , ROV) , RX interrupt
    CLEAR_BIT( MURT->Instance->INT.W , (URT_IT_RX | URT_IT_ERR));

    //===============================================================
    //Disable the UART DMA Rx request if enabled.
    if( READ_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_RXEN_mask_w)!=0)
    {
        CLEAR_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_RXEN_mask_w);
        
        //-----------------------------------------------------------
        //Abort the UART DMA Rx channel
        if( MURT->mDMA_RX != NULL)
        {
            //-----------------------------------------------------------
            //Set the UART DMA Abort callback to Null.
            //No call back execution at end of DMA abort procedure
            MURT->mDMA_RX->XferAbortCallback = NULL;
            
            MID_DMA_Abort( MURT->mDMA_RX);
        }
    }
    
    //===============================================================
    //Reset Rx transfer counter.
    MURT->RxTransferCount = 0U;
    
    //===============================================================
    //Clear the Error flags.
    __DRV_URT_CLEAR_FLAG( MURT , (URT_IT_ROVR | URT_IT_NCE | URT_IT_FE | URT_IT_PE | URT_IT_ERR));
    
    //===============================================================
    //Reset RxState to Ready.
    MURT->RxState = MID_URT_STATE_READY;
    
    
    return( MID_OK);
}


/**
 *******************************************************************************
 * @brief	    Abort ongoing transfers (Interrupt mode).
 * @details     
 * @param[in]   MURT    : URT handle. 
 * @return      MID status.
 * @exception   No
 * @note        This procedure could be used for aborting any on going transfer 
 *    \n        started in Interrupt or DMA mode.
 *    \n        This procedure performs following operations :
 *    \n        - Disable UART Interrupts (Tx and Rx).
 *    \n        - Disable the DMA transfer in the peripheral register (if enabled).
 *    \n        - Abort DMA transfer by calling HAL_DMA_Abort_IT (in case of transfer in DMA mode).
 *    \n        - Set handle State to READY.
 *    \n        - At abort completion, call user abort complete callback.
 *******************************************************************************
 */
MID_StatusTypeDef MID_URT_Abort_IT( URT_HandleTypeDef *MURT)
{
    BitAction Abortcplt = SET;
    
    //===============================================================
    //Disable interrupts
    CLEAR_BIT( MURT->Instance->INT.W , (URT_IT_TC | URT_IT_RX | URT_IT_TX | URT_IT_ERR));
    
    //===============================================================
    //If DMA Tx and / or DMA Rx handles are associated to URT handle,
    //DMA abort complete callbacks should be initialised before any
    //call to DMA abort functions
    
    //-----------------------------------------------------------
    //DMA TX Handle is valid
    if(MURT->mDMA_TX != NULL)
    {
        //-----------------------------------------------------------
        //Set DMA abort complete callback if UART DMA Tx request if
        //enabled. Otherwise , set it to NULL
        if( READ_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_TXEN_mask_w)!=0)
        {
            MURT->mDMA_TX->XferAbortCallback = ifun_URT_DMATxAbortCallback;
        }
        else
        {
            MURT->mDMA_TX->XferAbortCallback = NULL;
        }
    }
    //-----------------------------------------------------------
    //DMA RX Handle is valid
    if( MURT->mDMA_RX != NULL)
    {
        //-----------------------------------------------------------
        //Set DMA Abort Complete callback if UART DMA RX request if 
        //enable. otherwise, set it to NULL.
        if( READ_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_RXEN_mask_w)!=0)
        {
            MURT->mDMA_RX->XferAbortCallback = ifun_URT_DMARxAbortCallback;
        }
        else
        {
            MURT->mDMA_RX->XferAbortCallback = NULL;
        }
    }
    
    //===============================================================
    // Disable the URT DMA Tx request if enabled 
    if( READ_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_TXEN_mask_w)!=0)
    {
        //-----------------------------------------------------------
        //Disable DMA Tx at URT level
        CLEAR_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_TXEN_mask_w);
        
        //----------------------------------------------------------
        //Abort the UART DMA Tx channel : use non blocking DMA Abort
        //callback
        if(MURT->mDMA_TX != NULL)
        {
            //-----------------------------------------------------------
            //UART Tx DMA Abort callback has already been initialised:
            //    will lead to call MID_URT_AbortCpltCallback() at 
            //    end of DMA abort procedure.
            if( MID_DMA_Abort_IT(MURT->mDMA_TX) != MID_OK)
            {
                MURT->mDMA_TX->XferAbortCallback = NULL;
            }
            else
            {
                Abortcplt = CLR;    
            }
        }
    }
    
    //===============================================================
    // Disable the URT DMA Rx request if enabled
    if( READ_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_RXEN_mask_w)!=0)
    {
        //-----------------------------------------------------------
        //Disable DMA RX at UART level
        CLEAR_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_RXEN_mask_w);
        
        //-----------------------------------------------------------
        //Abort the URT DMA Rx channel : use non blocking DMA Abort callback.
        if( MURT->mDMA_RX != NULL)
        {
            //-----------------------------------------------------------
            //UART Rx DMA Abort callback has already been initialised:
            //    will lead to call MID_URT_AbortCpltCallback() at end
            //    of DMA abort procedure.
            if( MID_DMA_Abort_IT(MURT->mDMA_RX) != MID_OK)
            {
                MURT->mDMA_RX->XferAbortCallback = NULL;
                Abortcplt = SET;
            }
            else
            {
                Abortcplt = CLR;
            }
        }
    }
    
    //===============================================================
    //If no DMA abort complete callback execution is required -> 
    //call user abort complete callback.
    if(Abortcplt == SET)
    {
        //-----------------------------------------------------------
        //Reset Tx and Rx transfer counters
        MURT->TxTransferCount = 0;
        MURT->RxTransferCount = 0;
        
        //-----------------------------------------------------------
        //Reset errorCode
        MURT->ErrorCode = MID_URT_ERROR_NONE;
        
        //-----------------------------------------------------------
        //Clear the error flags 
        __DRV_URT_CLEAR_FLAG( MURT , (URT_IT_ROVR | URT_IT_NCE | URT_IT_PE | URT_IT_FE));
        
        //-----------------------------------------------------------
        //Restore gState and RxState to READY.
        MURT->gState  = MID_URT_STATE_READY;
        MURT->RxState = MID_URT_STATE_READY;

        //-----------------------------------------------------------
        //As no DMA to be aborted, call directly user Abort 
        //complete callback.
        MID_URT_AbortCpltCallback(MURT);
    }
    
    return(MID_OK);
}

/**
 *******************************************************************************
 * @brief	    Abort ongoing Transmit transfer (Interrupt mode).
 * @details     
 * @param[in]   MURT    : URT handle. 
 * @return      MID status.
 * @exception   No
 * @note        This procedure could be used for aborting any ongoing Tx transfer 
 *    \n        started in Interrupt or DMA mode.
 *    \n        This procedure performs following operations :
 *    \n        - Disable UART Interrupts (Tx)
 *    \n        - Disable the DMA transfer in the peripheral register (if enabled).
 *    \n        - Abort DMA transfer by calling HAL_DMA_Abort_IT (in case of transfer in DMA mode).
 *    \n        - Set handle State to READY
 *    \n        - At abort completion, call user abort complete callback
 *******************************************************************************
 */
MID_StatusTypeDef MID_URT_AbortTransmit_IT( URT_HandleTypeDef *MURT)
{
    //===============================================================
    //Disable interrupts
    CLEAR_BIT(MURT->Instance->INT.W , ( URT_IT_TC | URT_IT_TX));
    //===============================================================
    //Disable the UART DMA Tx request if enabled
    if( READ_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_TXEN_mask_w)!=0)
    {
        CLEAR_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_TXEN_mask_w);
        //-----------------------------------------------------------
        if(MURT->mDMA_TX != NULL)
        {
            //-----------------------------------------------------------
            //Set the UART DMA Abort callback:
            //    will lead to call MID_URT_AbortCpltCallback() at end
            //    of DMA abort procedure.
            MURT->mDMA_TX->XferAbortCallback = ifun_URT_DMATxOnlyAbortCallback;
            
            //-----------------------------------------------------------
            //Abort DMA TX
            if( MID_DMA_Abort_IT( MURT->mDMA_TX) != MID_OK)
            {
                //-----------------------------------------------------------
                //Call Directly MURT->mDMA_TX->XferAbortCallback function
                //in case of error.
                MURT->mDMA_TX->XferAbortCallback( MURT->mDMA_TX);
            }
        }
        else
        {
            //-----------------------------------------------------------
            //Reset TX transfer counter.
            MURT->TxTransferCount = 0;
            
            //-----------------------------------------------------------
            //Restore gStatus to Ready.
            MURT->gState = MID_URT_STATE_READY;
            
            //-----------------------------------------------------------
            //As no DMA to be aborted , call directly user abort complete
            //callback.
            MID_URT_AbortTransmitCpltCallback(MURT);
        }
    }
    else
    {
        //===============================================================
        //Reset Tx transfer counter
        MURT->TxTransferCount = 0;
        //===============================================================
        //Restore gState to ready
        MURT->gState = MID_URT_STATE_READY;
        //===============================================================
        //As no DMA to be aborted, call directly user abort complete callback
        MID_URT_AbortTransmitCpltCallback(MURT);
    }
    return( MID_OK);
}
/**
 *******************************************************************************
 * @brief	    Abort on going Receive transfer (Interrupt mode).
 * @details     
 * @param[in]   MURT    : URT handle. 
 * @return      MID status.
 * @exception   No
 * @note        This procedure could be used for aborting any ongoing Rx transfer
 *    \n        started in Interrupt or DMA mode.
 *    \n        This procedure performs following operations :
 *    \n        - Disable UART Interrupts (Rx)
 *    \n        - Disable the DMA transfer in the peripheral register (if enabled)
 *    \n        - Abort DMA transfer by calling HAL_DMA_Abort_IT (in case of transfer in DMA mode)
 *    \n        - Set handle State to READY
 *    \n        - At abort completion, call user abort complete callback
 * @note        This procedure is executed in Interrupt mode, meaning that abort procedure could be
 *    \n        considered as completed only when user abort complete callback is executed
 *    \n        (not when exiting function).
*******************************************************************************
 */
MID_StatusTypeDef MID_URT_AbortReceive_IT( URT_HandleTypeDef *MURT)
{
    //===============================================================
    //Disable ERR (Frame error , noise error , overrun error) interrupt.
    CLEAR_BIT( MURT->Instance->INT.W , ( URT_IT_RX | URT_IT_ERR));
    
    //===============================================================
    //Disable the URT DMA Rx request if enabled.
    if( READ_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_RXEN_mask_w)!=0)
    {
        CLEAR_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_RXEN_mask_w);
        
        //-----------------------------------------------------------
        //Abort the UART DMA Rx channel : use non blocking DMA
        //abort callback
        if(MURT->mDMA_RX != NULL)
        {
            //-----------------------------------------------------------
            //Set the UART DMA abort callback : 
            //    will lead to call MID_URT_AbortCpltCallback() at end of DMA
            //    abort procedure.
            MURT->mDMA_RX->XferAbortCallback = ifun_URT_DMARxOnlyAbortCallback;
            
            //-----------------------------------------------------------
            //Abort DMA RX
            if(MID_DMA_Abort_IT(MURT->mDMA_RX) != MID_OK)
            {
                //-----------------------------------------------------------
                //Call directly MURT->mDMA_RX->XferAbortCallback
                //function in case of error.
                MURT->mDMA_RX->XferAbortCallback( MURT->mDMA_RX);
            }
        }
        else
        {
            //-----------------------------------------------------------
            //Reset Rx transfer counter
            MURT->RxTransferCount = 0;
            //-----------------------------------------------------------
            //Clear the Error flags 
            __DRV_URT_CLEAR_FLAG( MURT , ( URT_IT_ROVR | URT_IT_NCE | URT_IT_PE | URT_IT_FE));
            
            
            //-----------------------------------------------------------
            //Restore RxState to Ready.
            MURT->RxState = MID_URT_STATE_READY;
            //-----------------------------------------------------------
            //As no DMA to be aborted, call directly user abort complete
            //callback.
            MID_URT_AbortReceiveCpltCallback( MURT);
        }            
    }
    else
    {
        //===============================================================
        //Reset Rx transfer counter
        MURT->RxTransferCount = 0;
        //===============================================================
        //Clear the error flags 
        __DRV_URT_CLEAR_FLAG( MURT , (URT_IT_ROVR | URT_IT_NCE | URT_IT_PE | URT_IT_FE));
        
        //===============================================================
        //Restore RxState to Ready
        MURT->RxState = MID_URT_STATE_READY;
        //===============================================================
        //As no DMA to be aborted , call directly user abort complete
        //callback.
        MID_URT_AbortReceiveCpltCallback(MURT);
    }
    return( MID_OK);
}
/**
 *******************************************************************************
 * @brief	    Handle UART interrupt request.
 * @details     
 * @param[in]   MURT       :  DMA handle. 
 * @return      No.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
void MID_URT_IRQHandler( URT_HandleTypeDef* MURT )
{
    uint32_t MID_URTIRQ_Flag;

    MID_URTIRQ_Flag = (READ_REG( MURT->Instance->STA.W)) & (READ_REG( MURT->Instance->INT.W));
    //===============================================================
    //If no error occur
    if((MID_URTIRQ_Flag & URT_IT_ERR) == 0)
    {
        if((MID_URTIRQ_Flag & URT_IT_RX)!=0)
        {
            ifun_URT_Receive_IT(MURT);
            
            __DRV_URT_CLEAR_FLAG( MURT , URT_IT_RX );
        }
    }
    
    if( ( ( MID_URTIRQ_Flag & URT_IT_TC)!=0 )
     || ( ( MID_URTIRQ_Flag & URT_IT_TX)!=0 ) )
    {
        ifun_URT_EndTransmit_IT( MURT);

        __DRV_URT_CLEAR_FLAG( MURT , URT_IT_TX );
        __DRV_URT_CLEAR_FLAG( MURT , URT_IT_TC );
    }


    __DRV_URT_CLEAR_FLAG( MURT , URT_IT_ERR );
    __DRV_URT_CLEAR_FLAG( MURT , URT_IT_RX );
    __DRV_URT_CLEAR_FLAG( MURT , URT_FLAG_ERR );
    __DRV_URT_CLEAR_FLAG( MURT , ( URT_FLAG_ERR | URT_FLAG_PE | URT_FLAG_FE | \
                                  URT_FLAG_NCE | URT_FLAG_ROVR | URT_FLAG_RHF));  


/*
    //===============================================================
    //If some error occur.
    if( ( MID_URTIRQ_Flag & URT_IT_ERR)!=0)
    {
        //---------------------------------------------------------------
        //URT parity error interrupt occurred
        if((MID_URTIRQ_Flag & URT_IT_PE) !=0)
        {
            __DRV_URT_CLEAR_FLAG( MURT , URT_IT_PE);
            
            MURT->ErrorCode = MURT->ErrorCode | MID_URT_ERROR_PE;            
        }  
        //---------------------------------------------------------------
        //URT frame error interrupt occurred
        if((MID_URTIRQ_Flag & URT_IT_FE) !=0)
        {
            __DRV_URT_CLEAR_FLAG( MURT , URT_IT_FE);
            
            MURT->ErrorCode = MURT->ErrorCode | MID_URT_ERROR_FE;            
        }
        //---------------------------------------------------------------
        //URT noise error interrupt occurred
        if((MID_URTIRQ_Flag & URT_IT_NCE) !=0)
        {
            __DRV_URT_CLEAR_FLAG( MURT , URT_IT_NCE);
            
            MURT->ErrorCode = MURT->ErrorCode | MID_URT_ERROR_NE;            
        }
        //---------------------------------------------------------------
        //URT over-run interrupt occurred
        if((MID_URTIRQ_Flag & URT_IT_ROVR) !=0)
        {
            __DRV_URT_CLEAR_FLAG( MURT , URT_IT_ROVR);
            
            MURT->ErrorCode = MURT->ErrorCode | MID_URT_ERROR_ORE;            
        }

        //===============================================================
        //Call URT Error call back function if need be
        if( MURT->ErrorCode != MID_URT_ERROR_NONE)
        {
            //---------------------------------------------------------------
            //Block error : transfer is aborted
            //Set the URT state ready to be able to start again the process,
            //Disable RX Interrupts, and disable Rx DMA request, if on going
            ifun_URT_EndRxTransfer(MURT);
            
            //---------------------------------------------------------------
            //URT in mode Receiver.
            if( (MID_URTIRQ_Flag & URT_IT_RX)!=0)
            {
                ifun_URT_Receive_IT(MURT);
            }
            //===============================================================
            //If overrun error occurs , or if any error occurs in 
            //DMA mode reception, consider error as blocking.
            
            //---------------------------------------------------------------
            //Disable the URT DMA RX request if enabled
            if( READ_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_RXEN_mask_w)!=0)
            {

                CLEAR_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_RXEN_mask_w);
                
                //---------------------------------------------------------------
                //Abort the URT DMA Rx channel.
                if( MURT->mDMA_RX != NULL)
                {
                    //---------------------------------------------------------------
                    //Set the URT DMA abort callback :
                    //will lead to call MID_URT_ErrorCallback() at end of
                    //DMA abort procedure
                    MURT->mDMA_RX->XferAbortCallback = ifun_URT_DMAAbortOnError;
                    
                    //---------------------------------------------------------------
                    //Abort DMA RX
                    if( MID_DMA_Abort_IT( MURT->mDMA_RX) != MID_OK)
                    {

                        //---------------------------------------------------------------
                        //Call directly MURT->mDMA_RX->XferAbortCallback 
                        //function in case of error.
                        MURT->mDMA_RX->XferAbortCallback( MURT->mDMA_RX);        
                    }
                }
                else
                {
                    //---------------------------------------------------------------
                    //Call user error callback
                    MID_URT_ErrorCallback(MURT);
                }
            }
            else
            {
                //---------------------------------------------------------------
                //Call user error calback.
                MID_URT_ErrorCallback(MURT);
            }
        }
    }
*/
/*
    //==============================================================
    //URT in mode Transmitter 
    if((MID_URTIRQ_Flag & URT_IT_TX)!=0 )
    {
        ifun_URT_Transmit_IT( MURT);
        
        __DRV_URT_CLEAR_FLAG( MURT , URT_IT_TX );
        __DRV_URT_CLEAR_FLAG( MURT , URT_IT_TC );
        //return;
    }
*/
/*
    if( ( ( MID_URTIRQ_Flag & URT_IT_TC)!=0 )
     || ( ( MID_URTIRQ_Flag & URT_IT_TX)!=0 ) )
    {
        ifun_URT_EndTransmit_IT( MURT);

        __DRV_URT_CLEAR_FLAG( MURT , URT_IT_TX );
        __DRV_URT_CLEAR_FLAG( MURT , URT_IT_TC );
    }
*/
//    __DRV_URT_CLEAR_FLAG( MURT , MID_URTIRQ_Flag);

}
/**
 *******************************************************************************
 * @brief	    Tx Transfer completed callback.
 * @details     
 * @param[in]   MURT       : URT handle. 
 * @return      No.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
#if 0
__WEAK void MID_URT_TxCpltCallback(URT_HandleTypeDef *MURT)
{
    //=========================================================
    //Prevent unused argument(s) compilation warning
    UNUSED( MURT);
    
    //=========================================================
    //NOTE : This function should not be modified , when the
    //       callback is needed, the MID_URT_TxCpltCallback can
    //       be implemented in the user file.
}
#endif
/**
 *******************************************************************************
 * @brief	    Tx Half Transfer completed callback.
 * @details     
 * @param[in]   MURT       : URT handle. 
 * @return      No.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
__WEAK void MID_URT_TxHalfCpltCallback( URT_HandleTypeDef* MURT)
{
    //=========================================================
    //Prevent unused argument(s) compilation warning
    UNUSED( MURT);
    
    //=========================================================
    //NOTE : This function should not be modified , when the
    //       callback is needed, the MID_URT_TxHalfCpltCallback
    //        can be implemented in the user file.    
}
/**
 *******************************************************************************
 * @brief	    Rx Receive completed callback.
 * @details     
 * @param[in]   MURT       : URT handle. 
 * @return      No.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
#if 0
__WEAK void MID_URT_RxCpltCallback( URT_HandleTypeDef *MURT)
{
    //=========================================================
    // Prevent unused argument(s) compilation warning 
    UNUSED( MURT);
    
    //=========================================================
    //NOTE : This function should not be modifyed, when the 
    //       callback is needed, the MID_URT_RxCpltCallback 
    //       can be implemented in the user file.
}
#endif
/**
 *******************************************************************************
 * @brief	    Rx Half Receive completed callback.
 * @details     
 * @param[in]   MURT       : URT handle. 
 * @return      No.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
__WEAK void MID_URT_RxHalfCpltCallback( URT_HandleTypeDef *MURT)
{
    //=========================================================
    // Prevent unused argument(s) compilation warning 
    UNUSED( MURT);
    
    //=========================================================
    //NOTE : This function should not be modifyed, when the 
    //       callback is needed, the MID_URT_RxCpltCallback 
    //       can be implemented in the user file.
}
/**
 *******************************************************************************
 * @brief	    URT error callback.
 * @details     
 * @param[in]   MURT       : URT handle. 
 * @return      No.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
__WEAK void MID_URT_ErrorCallback( URT_HandleTypeDef *MURT)
{
    //=========================================================
    //Prevent unused argument compilation warning
    UNUSED(MURT);
    
    //=========================================================
    //NOTE : This function should not be modified , when the 
    //       callback is needed, the MID_URT_ErrorCallback can
    //       be implemented in the user file.    
}

/**
 *******************************************************************************
 * @brief	    UART Abort Complete callback.
 * @details     
 * @param[in]   MURT       : URT handle. 
 * @return      No.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
__WEAK void MID_URT_AbortCpltCallback( URT_HandleTypeDef *MURT)
{           
    //=========================================================
    //Prevent unusesd argument compilation warning.
    UNUSED(MURT);
    
    //=========================================================
    //NOTE : This function should not be modified, when the
    //       callback is needed, the MID_URT_AbortCpltCallback
    //       can be implemented in user file.
    
}

/**
 *******************************************************************************
 * @brief	    UART Abort Complete callback.
 * @details     
 * @param[in]   MURT       : URT handle. 
 * @return      No.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
__WEAK void MID_URT_AbortTransmitCpltCallback( URT_HandleTypeDef* MURT)
{
    //=========================================================
    //Prevent unused argument compilation warning.
    UNUSED(MURT);
    
    //=========================================================
    //Note : This function should not be modified, when the callback 
    //       is needed, the MID_URT_AbortTransmitCpltCallback can 
    //       be implemented in the user file.
    
}

/**
 *******************************************************************************
 * @brief	    UART Abort Receive Complete callback.
 * @details     
 * @param[in]   MURT       : URT handle. 
 * @return      No.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
__WEAK void MID_URT_AbortReceiveCpltCallback( URT_HandleTypeDef* MURT)
{
    //=========================================================
    //Prevent unused argument compilcation warning
    UNUSED(MURT);
    
    //=========================================================
    //Note : This function should not be modified, when th callback
    //       is needed, the MID_URT_AbortReceiveCpltCallback can
    //       be implemented in the user file.
    
}

///@}

/**
 * @name    URT Control function.
 *             
 */ 
///@{

// To do......

///@}


/**
 * @name    URT Peripheral State and Error functions
 *             
 */ 
///@{


/**
 *******************************************************************************
 * @brief	    Return the UART handle state.
 * @details     
 * @param[in]   MURT       : pointer to a URT_HandleTypeDef structure that
 *        \n                 contains the configuration information for the
 *        \n                 specified URT. 
 * @return      MID State
 * @exception   No
 * @note        No
 *******************************************************************************
 */
MID_URT_StateTypeDef MID_URT_GetState( URT_HandleTypeDef* MURT)
{
    uint8_t MID_URTGetStateTmp1;
    uint8_t MID_URTGetStateTmp2;
    
    MID_URTGetStateTmp1 = MURT->gState;
    MID_URTGetStateTmp2 = MURT->RxState;
    
    return((MID_URT_StateTypeDef)( MID_URTGetStateTmp1 | MID_URTGetStateTmp2));
}

/**
 *******************************************************************************
 * @brief	    Return the UART handle error code.
 * @details     
 * @param[in]   MURT       : Pointer to a URT_HandleTypeDef structure that 
 *       \n                  contains the configuration information for the 
 *       \n                  specified UART.
 * @return      UART Error Code.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
uint32_t MID_URT_GetError( URT_HandleTypeDef* MURT)
{
    return( MURT->ErrorCode);
}


///@}



/**
 * @name    URT private functions
 *             
 */ 
///@{

/**
 *******************************************************************************
 * @brief	    Get freq of URT clock source.
 * @details     
 * @param[in]   MURT : URT handle.
 * @return      MID status.
 * @exception   No
 * @note        The only use in URT baudrate generator clock source use PROC.
 *******************************************************************************
 */
uint32_t MID_URT_GetBRGClocksource( URT_HandleTypeDef* MURT)
{
    uint32_t CSC_URT_SHIFT;
    uint16_t CSC_URT_CMP = 0x0001;
    
    CSC_URT_SHIFT = ((((uint32_t)(&MURT->Instance->STA.W)) & 0x000F0000)>>16);
    CSC_URT_CMP   = (uint16_t)(0x0001 << ( CSC_URT_SHIFT * 2));
    
    if(( CSC->CKS1.H[1] & CSC_URT_CMP) == 0)
    {
        return( MID_CSC_GetCK_APBFreq()); 
    }
    else
    {
        return(MID_CSC_GetCK_AHBFreq()); 
    }
}
/**
 *******************************************************************************
 * @brief	    URT Private Function.
 * @details     
 * @param[in]   MURT : URT handle.
 * @return      MID status.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
MID_StatusTypeDef MID_URT_SetConfig(URT_HandleTypeDef* MURT)
{
    uint32_t   Tmp; 
    uint32_t   TXRXOversampling = 8;
    uint32_t   URT_CLKFreq;
    
    uint32_t   OVSMP;
    uint32_t   REM;
    uint32_t   BST_SOL;
    
    //===========================================================
    //* Configure:
    //    * Set Data length according to MURT->Ini.DataLength value.
    //    * Set pairty bit according to MURT->Init.Parity value.
    //    * Set Stop bit according to MURT->Init.StopBits value.
    
    URT_MODIFY_REG( MURT->Instance->CR1.W , URT_INIT_CR1_MSK ,  
                    (((uint32_t)MURT->Init.WordLength) | ((uint32_t)(MURT->Init.Parity)) | ((uint32_t)MURT->Init.StopBits)));
    

    
    //===========================================================
    //* Set TX_EN and RX_EN bits according to MURT->Init.Mode.
    URT_MODIFY_REG( MURT->Instance->CR2.W , URT_INIT_MODE_MSK ,  MURT->Init.Mode );
    
    //===========================================================
    //* Configure
    //    * URT hardware flow control : (according to MURT->Init.HWFlowCtrl value) 
    //        * CTS:
    //        * RTS:
    URT_MODIFY_REG( MURT->Instance->HFC.W , URT_INIT_HWFLOWCTRL_MSK , MURT->Init.HWFlowCtrl);
    
    //===========================================================
    //* Configure one-bit sampling method.
    URT_MODIFY_REG( MURT->Instance->CR0.B[0], URT_CR0_OS_MDS_mask_b0, MURT->Init.OneBitSampling);
    
    //===========================================================
    //* URT baudrate configuration.
    
    //-----------------------------------------------------------
    //* Operation setting parameters.
    URT_CLKFreq = MID_URT_GetBRGClocksource( MURT);            
    
    
    Tmp = (URT_CLKFreq / MURT->Init.BaudRate);
    if(Tmp<8)
    {
        return(MID_FAILURE);
    }
    else if((URT_CLKFreq % MURT->Init.BaudRate)>4)
    {
        Tmp = Tmp + 1;
    } 
    
    BST_SOL = 0;
    for(OVSMP=8;OVSMP<32;OVSMP++)
    {
        REM = Tmp % OVSMP;
        if(REM==0)
        {
            if((Tmp / OVSMP) < 4096)
            {
                TXRXOversampling = OVSMP;
                break;
            }
        }
        else 
        {
           if(REM==1 && OVSMP>15)
           {
               TXRXOversampling = OVSMP;
               BST_SOL          = 48;
           }
           REM = OVSMP - REM;
           if(REM > BST_SOL || REM==BST_SOL)
           {
               BST_SOL = REM;
               TXRXOversampling = OVSMP;               
           }
        }
    }
    //-----------------------------------------------------------
    //* Baud-Rate configure.
    //    * Set RX/TX baudrate from Baud-Rate Generator (BRG)
    //    * BRG clock source from CK_URT_PR (The URT module clock source)
    //    * Set BRG reload data.
    //    * Set TX / RX oversampling.
    //    * Set BRG mode to Combined mode and enable BRG.
    CLEAR_BIT(MURT->Instance->CLK.W , (URT_CLK_TX_CKS_mask_w| URT_CLK_RX_CKS_mask_w | URT_CLK_CK_SEL_mask_w));
    
    Tmp = Tmp / (TXRXOversampling);
    if(Tmp>4096)
    {
        return(MID_FAILURE);
    }
    
    URT_WRITE_REG(MURT->Instance->RLR.H[0], ((uint16_t)(Tmp - 1)));
    
    TXRXOversampling = TXRXOversampling - 1;
    URT_WRITE_REG(MURT->Instance->CR1.B[3] , (uint8_t)TXRXOversampling);
    URT_WRITE_REG(MURT->Instance->CR1.B[1] , (uint8_t)TXRXOversampling);
    
    SET_BIT(MURT->Instance->CLK.W, (URT_CLK_BR_MDS_mask_w | URT_CLK_BR_EN_mask_w));
    
    
    return(MID_SUCCESS);
}

/**
 *******************************************************************************
 * @brief	    Configure the URT peripheral advanced features.
 * @details     
 * @param[in]   MURT : URT handle.
 * @return      No
 * @exception   No
 * @note        No
 *******************************************************************************
 */
void MID_URT_AdvFeatureConfig(URT_HandleTypeDef* MURT)
{
    //===========================================================
    //* If required , Configure
    //    * Set TX signal invert according to MURT->AdvancedInit.TxPinLevelInvert value.
    //    * Set RX signal invert according to MURT->AdvancedInit.RxPinLevelInvert value.
    if(MID_URT_IS_BIT_SET(MURT->AdvancedInit.AdvFeatureInit, URT_ADVFEATURE_TXINVERT_INIT))
    {
        URT_MODIFY_REG(MURT->Instance->CR0.W, URT_CR0_TX_INV_mask_w , MURT->AdvancedInit.TxPinLevelInvert);
    }
    if(MID_URT_IS_BIT_SET(MURT->AdvancedInit.AdvFeatureInit, URT_ADVFEATURE_RXINVERT_INIT))
    {
        URT_MODIFY_REG(MURT->Instance->CR0.W, URT_CR0_RX_INV_mask_w , MURT->AdvancedInit.RxPinLevelInvert);
    }
    //===========================================================
    //* If required , Configure
    //    * Set TX Data bit invert according to MURT->AdvancedInit.TXDataInvert value.
    //    * Set RX Data bit invert according to MURT->AdvancedInit.RXDataInvert value.
    if(MID_URT_IS_BIT_SET(MURT->AdvancedInit.AdvFeatureInit, URT_ADVFEATURE_TXDATAINVERT_INIT))
    {
        URT_MODIFY_REG(MURT->Instance->CR4.W, URT_CR4_TDAT_INV_mask_w , MURT->AdvancedInit.TXDataInvert);
    }
    if(MID_URT_IS_BIT_SET(MURT->AdvancedInit.AdvFeatureInit, URT_ADVFEATURE_RXDATAINVERT_INIT))
    {
        URT_MODIFY_REG(MURT->Instance->CR4.W, URT_CR4_RDAT_INV_mask_w , MURT->AdvancedInit.RXDataInvert);
    }
    //===========================================================
    //* If required , Configure
    //    * Set RX / TX pin swap according to MURT->AdvancedInit.Swap.
    if(MID_URT_IS_BIT_SET(MURT->AdvancedInit.AdvFeatureInit, URT_ADVFEATURE_SWAP_INIT))
    {
        URT_MODIFY_REG(MURT->Instance->CR0.W , URT_CR0_IO_SWP_mask_w , MURT->AdvancedInit.Swap);
    }
    //===========================================================
    //* If required , Configure
    //    * Set Auto baudrate detection scheme.
    if(MID_URT_IS_BIT_SET(MURT->AdvancedInit.AdvFeatureInit, URT_ADVFEATURE_AUTOBAUDRATE_INIT))
    {
        URT_MODIFY_REG(MURT->Instance->CAL.B[0] , (URT_CAL_CAL_AUTO_mask_b0| URT_CAL_CAL_MDS_mask_b0),     \
                       (((uint8_t)MURT->AdvancedInit.AutoBaudRateEnable) | ((uint8_t)MURT->AdvancedInit.AutoBaudRateMode)));
    }
    //===========================================================
    //* Configure
    //    * Set TX data order is MSB according to MURT->AdvancedInit.TXMSBFirst.
    //    * Set RX data order is MSB according to MURT->AdvancedInit.RXMSBFirst.
    if(MID_URT_IS_BIT_SET(MURT->AdvancedInit.AdvFeatureInit, URT_ADVFEATURE_TXMSBFIRST_INIT))
    {
        URT_MODIFY_REG(MURT->Instance->CR1.B[2], URT_CR1_TXMSB_EN_mask_b2 , MURT->AdvancedInit.TXMSBFirst);
    }
    if(MID_URT_IS_BIT_SET(MURT->AdvancedInit.AdvFeatureInit, URT_ADVFEATURE_RXMSBFIRST_INIT))
    {
        URT_MODIFY_REG(MURT->Instance->CR1.B[0], URT_CR1_RXMSB_EN_mask_b0 , MURT->AdvancedInit.RXMSBFirst);
    }
}

/**
 *******************************************************************************
 * @brief	    Check the URT idle state.
 * @details     
 * @param[in]   MURT : URT handle.
 * @return      MID status.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
MID_StatusTypeDef MID_URT_CheckIdleState(URT_HandleTypeDef* MURT)
{
    //===========================================================
    //* Initialize the URT ErrorCode.
    MURT->ErrorCode = MID_URT_ERROR_NONE;
    
    //===========================================================
    //* Initialize the URT State.

    MURT->gState  = MID_URT_STATE_READY;
    MURT->RxState = MID_URT_STATE_READY;
    
    //===========================================================
    //* Process Unlocked.
    __MID_UNLOCK(MURT);
    
    return(MID_SUCCESS);
}


/**
 *******************************************************************************
 * @brief	    Handle URT communication Timeout.
 * @details     
 * @param[in]   MURT       : URT handle. 
 * @param[in]   FLAG       : Flag specifies the URT flag to check.
 * @param[in]   STATUS     : Flag status (SET or CLR).
 * @param[in]   TICK_START : Tick start value.
 * @param[in]   TIMEOUT    : Timeout duration.
 * @return      MID status.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
MID_StatusTypeDef MID_URT_WaitOnFlagUntilTimeout(URT_HandleTypeDef* MURT , uint32_t FLAG , FlagStatus STATUS, uint32_t TICK_START , uint32_t TIMEOUT)
{
    //===========================================================
    //Wait until flag is set.
    while((__MID_URT_GET_FLAG( MURT , FLAG) ? SET : CLR) == STATUS) 
    {
       //===========================================================
       //Check for the Timeout.
       if(TIMEOUT != MID_MAX_DELAY)
       {
           if((TIMEOUT == 0) || ((MID_GetTick() - TICK_START) > TIMEOUT))
           {
               //===========================================================
               //Disable TX_IE , TC_IE , RX_IE , and ERR ( Parity error , Frame error , noise error, overrun error) for the interrupt process
               CLEAR_BIT( MURT->Instance->INT.W , (URT_IT_TX | URT_IT_TC | URT_IT_RX | URT_IT_ERR));

               MURT->gState  = MID_URT_STATE_READY;
               MURT->RxState = MID_URT_STATE_READY;
               
               //===========================================================
               //Process Unlocked.
               __MID_UNLOCK(MURT);
               
               return(MID_TIMEOUT);
           }
       }
    }
    return(MID_OK);
}
/**
 *******************************************************************************
 * @brief	    End on going Tx transfer on UART peripheral 
 *       \n     (following error detection or Transmit completion).
 * @details     
 * @param[in]   MURT       : URT handle. 
 * @return      No
 * @exception   No
 * @note        No
 *******************************************************************************
 */
static void ifun_URT_EndTxTransfer( URT_HandleTypeDef *MURT)
{
    //===============================================================
    //Disable TX_IE and TC_IE interrupt
    CLEAR_BIT( MURT->Instance->INT.W , (URT_IT_TX | URT_IT_TC));

    //===============================================================
    //At end of TX process.
    MURT->gState = MID_URT_STATE_READY;
}
/**
 *******************************************************************************
 * @brief	    End on going Rx transfer on UART peripheral 
 *       \n     (following error detection or Reception completion).
 * @details     
 * @param[in]   MURT       : URT handle. 
 * @return      No
 * @exception   No
 * @note        No
 *******************************************************************************
 */
static void ifun_URT_EndRxTransfer( URT_HandleTypeDef* MURT)
{
    //===============================================================
    //Disable 
    //    1. Enable the URT Error Interrupt : (Frame error , Parity error , Noise error , Overrun error)
    //    2. the URT data register not empty interrupt.
    CLEAR_BIT( MURT->Instance->INT.W , (URT_IT_ERR |  URT_IT_RX));
    
    //===============================================================
    //At end of Rx process, restore MURT->RxState to Ready.
    MURT->RxState = MID_URT_STATE_READY;
    
}

/**
 *******************************************************************************
 * @brief	    DMA UART transmit process complete callback.
 * @details     
 * @param[in]   MDMA       : DMA handle. 
 * @return      No
 * @exception   No
 * @note        No
 *******************************************************************************
 */
static void ifun_URT_DMATransmitCplt( DMA_HandleTypeDef *MDMA )
{
    URT_HandleTypeDef* MURT = (URT_HandleTypeDef*)(MDMA->Parent);
    
    //===============================================================
    //DMA Normal mode
    if( MDMA->Init.LoopMode == DMA_LOOP_DISABLE)
    {
        MURT->TxTransferCount = 0U;
        
        //-----------------------------------------------------------
        //Enable the UART Transmit Complete Interrupt.
        SET_BIT( MURT->Instance->INT.W , URT_IT_TC);
    }
    //
    else
    {
        MID_URT_TxCpltCallback(MURT);
    }
}
/**
 *******************************************************************************
 * @brief	    DMA UART transmit process half complete callback.
 * @details     
 * @param[in]   MDMA       : DMA handle. 
 * @return      No
 * @exception   No
 * @note        No
 *******************************************************************************
 */
static void ifun_URT_DMATxHalfCplt( DMA_HandleTypeDef *MDMA)
{
    URT_HandleTypeDef* MURT = (URT_HandleTypeDef*)(MDMA->Parent);
    
    MID_URT_TxHalfCpltCallback(MURT);
    
}

/**
 *******************************************************************************
 * @brief	    DMA UART receive process complete callback.
 * @details     
 * @param[in]   MDMA       : DMA handle. 
 * @return      No
 * @exception   No
 * @note        No
 *******************************************************************************
 */
static void ifun_URT_DMAReceiveCplt( DMA_HandleTypeDef *MDMA)
{
    URT_HandleTypeDef* MURT = (URT_HandleTypeDef*)(MDMA->Parent);
    
    //===============================================================
    //DMA Normal mode
    if( MDMA->Init.LoopMode == DMA_LOOP_DISABLE)
    {
        MURT->RxTransferCount = 0U;

        //-----------------------------------------------------------
        //Disable error interrupt (parity error , frame error , noise , RX overun.
        CLEAR_BIT( MURT->Instance->INT.W , (URT_IT_ERR));
        
        //-----------------------------------------------------------
        //Disable the DMA transfer for the receiver request
        CLEAR_BIT( MURT->Instance->CR0.W , URT_CR0_DMA_RXEN_mask_w);
        
        //----------------------------------------------------------
        //At end of Rx process 
        MURT->RxState = MID_URT_STATE_READY;
        
    }

    //==========================================
    //Clear the URT data register not empty interrupt flag.
    CLEAR_BIT( MURT->Instance->INT.W , (URT_IT_ERR | URT_IT_RX));
    MID_URT_RxCpltCallback(MURT);
    
}

/**
 *******************************************************************************
 * @brief	    DMA UART receive process half complete callback.
 * @details     
 * @param[in]   MDMA       : DMA handle. 
 * @return      No
 * @exception   No
 * @note        No
 *******************************************************************************
 */
static void ifun_URT_DMARxHalfCplt( DMA_HandleTypeDef *MDMA)
{
    URT_HandleTypeDef*  MURT = (URT_HandleTypeDef*)(MDMA->Parent);
    
    MID_URT_RxHalfCpltCallback( MURT);
}
/**
 *******************************************************************************
 * @brief	    DMA UART communication error callback.
 * @details     
 * @param[in]   MDMA       : DMA handle. 
 * @return      No
 * @exception   No
 * @note        No
 *******************************************************************************
 */
static void ifun_URT_DMAError( DMA_HandleTypeDef *MDMA)
{
    URT_HandleTypeDef* MURT = (URT_HandleTypeDef*)(MDMA->Parent);
    
    if( (MURT->gState == MID_URT_STATE_BUSY_TX) && 
        ( READ_BIT(MURT->Instance->CR0.W , URT_CR0_DMA_TXEN_mask_w)!=0))
    {
        MURT->TxTransferCount = 0;
        ifun_URT_EndTxTransfer(MURT);
    }
    
    if( (MURT->gState == MID_URT_STATE_BUSY_RX) && 
        ( READ_BIT(MURT->Instance->CR0.W , URT_CR0_DMA_RXEN_mask_w)!=0))
    {
        MURT->RxTransferCount = 0;
        ifun_URT_EndRxTransfer(MURT);
    }
    
    MURT->ErrorCode = MURT->ErrorCode | MID_URT_ERROR_DMA;
    MID_URT_ErrorCallback(MURT);
}
/**
 *******************************************************************************
 * @brief	    DMA URT communication abort callback
 *              (To be called at end of DMA Abort procedure).
 * @details     
 * @param[in]   MDMA     : DMA handle. 
 * @return      No.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
void ifun_URT_DMAAbortOnError( DMA_HandleTypeDef *MDMA)
{
    URT_HandleTypeDef*  MURT = (URT_HandleTypeDef*)(MDMA->Parent);
    
    MURT->RxTransferCount = 0;
    MURT->TxTransferCount = 0;
    
    MID_URT_ErrorCallback(MURT);
}
/**
 *******************************************************************************
 * @brief	    DMA UART Tx communication abort callback, when initiated by user
 *       \n     (To be called at end of DMA Tx Abort procedure following user 
 *       \n     abort request).
 * @details     
 * @param[in]   MDMA      : DMA handle. 
 * @return      No.
 * @exception   No
 * @note        When this callback is executed, User abort complete call back is
 *       \n     called only if no abort still on going for Rx DMA handle.
 *******************************************************************************
 */
static void ifun_URT_DMATxAbortCallback( DMA_HandleTypeDef *MDMA)
{
    URT_HandleTypeDef* MURT = (URT_HandleTypeDef*)(MDMA->Parent);
    
    MURT->mDMA_TX->XferAbortCallback = NULL;

    //============================================================
    //Check if an abort process is still on going.
    if( MURT->mDMA_RX != NULL)
    {
        if(MURT->mDMA_RX->XferAbortCallback != NULL)
        {
            return;
        }
    }
    //============================================================
    //No abort process still on going : All DMA channels are aborted,
    //call user abort complete callback
    MURT->TxTransferCount = 0U;
    MURT->RxTransferCount = 0U;
    
    //============================================================
    //Reset errorCode
    MURT->ErrorCode = MID_URT_ERROR_NONE;
    
    //============================================================
    //Clear the Error flags.
    WRITE_REG( MURT->Instance->STA.W, (URT_IT_ROVR | URT_IT_NCE | URT_IT_PE | URT_IT_FE));

    //============================================================
    //Restore gState and RxState to Ready.
    MURT->gState  = MID_URT_STATE_READY;
    MURT->RxState = MID_URT_STATE_READY; 
    
    //============================================================
    //Call user abort complete callback.
    MID_URT_AbortCpltCallback(MURT);
}

/**
 *******************************************************************************
 * @brief	    DMA UART Rx communication abort callback, when initiated by user
 *       \n     (To be called at end of DMA Rx Abort procedure following user 
 *       \n     abort request).
 * @details     
 * @param[in]   MDMA      : DMA handle. 
 * @return      No.
 * @exception   No
 * @note        When this callback is executed, User Abort complete call back is
 *       \n     called only if no Abort still ongoing for Tx DMA Handle.
 *******************************************************************************
 */
static void ifun_URT_DMARxAbortCallback( DMA_HandleTypeDef *MDMA)
{
    URT_HandleTypeDef* MURT = (URT_HandleTypeDef*)(MDMA->Parent);
    
    MURT->mDMA_RX->XferAbortCallback = NULL;
    
    //============================================================
    //Check if an abort process is still on going.
    if( MURT->mDMA_TX != NULL)
    {
        if(MURT->mDMA_TX->XferAbortCallback != NULL)
        {
            return;
        }
    }
    //============================================================
    //No abort process still on going : All DMA channels are aborted,
    //call user Abort complete callback.
    MURT->TxTransferCount = 0U;
    MURT->RxTransferCount = 0U;
    
    //============================================================
    //Reset errorCode
    MURT->ErrorCode = MID_URT_ERROR_NONE;
    
    //============================================================
    //Clear the error flags 
    __DRV_URT_CLEAR_FLAG( MURT , (URT_IT_ROVR | URT_IT_NCE | URT_IT_PE | URT_IT_FE));

    //============================================================
    //Restore gState and RxState to READY.
    MURT->gState  = MID_URT_STATE_READY;
    MURT->RxState = MID_URT_STATE_READY;
    
    //============================================================
    //Call user abort complete callback
    MID_URT_AbortCpltCallback(MURT);
}

/**
 *******************************************************************************
 * @brief	    DMA UART TX communication abort callback , when initiated by a
 *       \n     call to MID_URT_AbortTransmit_IT (Abort only TX trasfer)
 *       \n     (This callback is executed at end of DMA TX abort procedure following
 *       \n     user abort request, and leads to user Tx abort compete callback
 *       \n     execution.
 * @details     
 * @param[in]   MDMA      : DMA handle. 
 * @return      No.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
static void ifun_URT_DMATxOnlyAbortCallback( DMA_HandleTypeDef* MDMA)
{
    URT_HandleTypeDef* MURT = (URT_HandleTypeDef*)(MDMA->Parent);
    
    MURT->TxTransferCount = 0;

    //============================================================
    //Restore gState to Ready.
    MURT->gState = MID_URT_STATE_READY;
    //============================================================
    //Call user Abort complete callback.
    MID_URT_AbortTransmitCpltCallback(MURT);
}
/**
 *******************************************************************************
 * @brief	    DMA UART Rx communication abort callback, when initiated by user 
 *       \n     by a call to MID_URT_AbortReceive_IT (Abort only Rx transfer)
 *       \n     (This callback is executed at end of DMA Rx Abort procedure 
 *       \n     following user abort request, and leads to user Rx Abort 
 *       \n     Complete callback execution).
 * @details     
 * @param[in]   MDMA      : DMA handle. 
 * @return      No.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
static void ifun_URT_DMARxOnlyAbortCallback( DMA_HandleTypeDef *MDMA)
{
    URT_HandleTypeDef* MURT = (URT_HandleTypeDef*)(MDMA->Parent);
    
    MURT->RxTransferCount = 0;
    
    //============================================================
    //Clear the Error flags
    __DRV_URT_CLEAR_FLAG( MURT ,  ( URT_IT_ROVR | URT_IT_NCE | URT_IT_PE | URT_IT_FE));
    
    //============================================================
    //Restore RxState to Ready.
    MURT->RxState = MID_URT_STATE_READY;
    
    //============================================================
    //Call user abort complete callback
    MID_URT_AbortReceiveCpltCallback(MURT);
}
/**
 *******************************************************************************
 * @brief	    Send an amount of data in interrupt mode.
 * @details     
 * @param[in]   MURT       : URT handle. 
 * @return      MID state.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
MID_StatusTypeDef ifun_URT_Transmit_IT( URT_HandleTypeDef* MURT)
{
    ctype   URT_ITData;
    uint8_t URT_ITCnt = 0;
    
    //============================================================
    //Check that a TX process is on going.
    
    if( MURT->gState == MID_URT_STATE_BUSY_TX)
    {
        //======================================================
        //
        while( MURT->TxTransferCount !=0 && URT_ITCnt < MURT->TxTransferCountMax) 
        {
            URT_ITData.B[URT_ITCnt] =  *(MURT->pTxBuffPtr);
            MURT->pTxBuffPtr        =  MURT->pTxBuffPtr + 1;
            MURT->TxTransferCount   =  MURT->TxTransferCount - 1;
            URT_ITCnt               =  URT_ITCnt + 1;
        }
        //=====================================================
        //Trigge data to transmit.
        switch( URT_ITCnt)
        {
            case 1:      
                    MURT->Instance->TDAT.B[0] =  URT_ITData.B[0];             
                    break;                
            case 2:
                    MURT->Instance->TDAT.H[0] =  URT_ITData.H[0]; 
                    break;
            case 3:
                    MURT->Instance->TDAT3.W   =  URT_ITData.W; 
                    break;
            case 4:
                    MURT->Instance->TDAT.W   =  URT_ITData.W;
                    break;
            case 0:
            default:
                    break;                
        }
        //=========================================================
        //Last data have trigged.
        if(MURT->TxTransferCount == 0)
        {
            //------------------------------------------------------
            //Disable transmit Data Register Empty interrupt.
            CLEAR_BIT( MURT->Instance->INT.W , URT_IT_TX);
            //------------------------------------------------------
            //Enable transmit complete interrupt.
            SET_BIT( MURT->Instance->INT.W , URT_IT_TC);
        }
        return( MID_OK);
    }
    else
    {
        return( MID_BUSY);
    }
}
/**
 *******************************************************************************
 * @brief	    Wrap up transmission in non-blocking mode.
 * @details     
 * @param[in]   MURT       : URT handle. 
 * @return      MID state.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
MID_StatusTypeDef ifun_URT_EndTransmit_IT( URT_HandleTypeDef* MURT)
{
    //=========================================================
    //Disable the URT Transmit Complete Interrupt.
    CLEAR_BIT( MURT->Instance->INT.W , (URT_IT_TX | URT_IT_TC));

    //=========================================================
    //TX process is ended, restore MURT-> gState to Ready.
    MURT->gState = MID_URT_STATE_READY;
    
    MID_URT_TxCpltCallback( MURT);
    
    return( MID_OK);

}

/**
 *******************************************************************************
 * @brief	    Receive an amount of data in interrupt mode.
 * @details     Function is called under interruption only, once
 *              interruptions have been enabled by MID_URT_Receive_IT()
 * @param[in]   MURT       : URT handle. 
 * @return      MID state.
 * @exception   No
 * @note        No
 *******************************************************************************
 */
static MID_StatusTypeDef ifun_URT_Receive_IT( URT_HandleTypeDef * MURT)
{
    ctype     URT_RXITDATA;
    uint8_t   URT_RXITCNT;
    uint8_t   URT_RXITmp;

    //=========================================================
    //Check that a RX process is on going.
    if( MURT->RxState == MID_URT_STATE_BUSY_RX )
    {
        URT_RXITDATA.W = READ_REG( MURT->Instance->RDAT.W);
        URT_RXITCNT    = 1;

        URT_RXITmp = 0;

        if( MURT->RxTransferCount > 0)
        {
            for( URT_RXITmp = 0; URT_RXITmp < URT_RXITCNT; URT_RXITmp++)
            {
                #if defined(MG32_1ST)
                    if( MURT->Init.WordLength == UART_WORDLENGTH_8B)
                    {
                        *MURT->pRXBuffPtr++ = (uint8_t) URT_RXITDATA.B[URT_RXITmp];
                    }
                    else
                    {
                        *MURT->pRXBuffPtr++ = ((uint8_t) URT_RXITDATA.B[URT_RXITmp] & 0x7F);
                    }
                #else
                    *MURT->pRXBuffPtr++ = (uint8_t) URT_RXITDATA.B[URT_RXITmp];
                #endif
            }
        }

        MURT->RxTransferCount = MURT->RxTransferCount  - URT_RXITCNT;
        if( MURT->RxTransferCount == 0)
        {
            //===============================================================
            //Disable 
            //    1. Enable the URT Error Interrupt : (parity error , Frame error , noise error , overrun error)
            //    2. the URT data register not empty interrupt.
            CLEAR_BIT( MURT->Instance->INT.W , (URT_IT_ERR | URT_IT_RX));
            
            //==================================================
            //RX process is completed , restore RXState to Ready
            MURT->RxState = MID_URT_STATE_READY;


            MID_URT_RxCpltCallback(MURT);
            return( MID_OK);
        }
       
        return( MID_OK);
    }
    else
    {
        //==========================================
        //Clear the URT data register not empty interrupt flag.
        CLEAR_BIT( MURT->Instance->INT.W , (URT_IT_ERR | URT_IT_RX));
        return( MID_BUSY);
    }
}

///@}


/**
 * @name    URT Exported Function.
 *             
 */ 
///@{

/**
 *******************************************************************************
 * @brief	    Enable URT Sleep mode
 * @details     
 * @param[in]   MURT       : URT handle. 
 * @return      MID state
 * @exception   No
 * @note        No
 *******************************************************************************
 */
MID_StatusTypeDef MID_URT_EnableSleepMode( URT_HandleTypeDef *MURT)
{
    //========================================================
    // Process locked.
    __MID_LOCK(MURT);
    MURT->gState = MID_URT_STATE_BUSY;
    
    //========================================================
    //Set CSC control
    if(MURT->Instance == URT0)
    {
        SET_BIT( CSC->SLP0.W , CSC_SLP0_SLP_URT0_mask_w);
    }
    #if defined(URT1_Base)
    else if(MURT->Instance == URT1)
    {
        SET_BIT( CSC->SLP0.W , CSC_SLP0_SLP_URT1_mask_w);
    }
    #endif
    #if defined(URT2_Base)
    else if(MURT->Instance == URT2)
    {
        SET_BIT( CSC->SLP0.W , CSC_SLP0_SLP_URT2_mask_w);
    }
    #endif
    #if defined(URT3_Base)
    else if(MURT->Instance == URT3)
    {
        SET_BIT( CSC->SLP0.W , CSC_SLP0_SLP_URT3_mask_w);
    }
    #endif
    else
    {
        return(MID_ERROR);
    }
;
    MURT->gState = MID_URT_STATE_READY;
    //========================================================
    //Process Unlocked.
    __MID_UNLOCK(MURT);
    
    return(MID_OK);
}

/**
 *******************************************************************************
 * @brief	    Enable URT Sleep mode
 * @details     
 * @param[in]   MURT       : URT handle. 
 * @return      MID state
 * @exception   No
 * @note        No
 *******************************************************************************
 */
MID_StatusTypeDef MID_URT_DisableSleepMode( URT_HandleTypeDef *MURT)
{
    //========================================================
    // Process locked.
    __MID_LOCK(MURT);
    MURT->gState = MID_URT_STATE_BUSY;
    
    //========================================================
    //Set CSC control
    if(MURT->Instance == URT0)
    {
        CLEAR_BIT( CSC->SLP0.W , CSC_SLP0_SLP_URT0_mask_w);
    }
    #if defined(URT1_Base)
    else if(MURT->Instance == URT1)
    {
        CLEAR_BIT( CSC->SLP0.W , CSC_SLP0_SLP_URT1_mask_w);
    }
    #endif
    #if defined(URT2_Base)
    else if(MURT->Instance == URT2)
    {
        CLEAR_BIT( CSC->SLP0.W , CSC_SLP0_SLP_URT2_mask_w);
    }
    #endif
    #if defined(URT3_Base)
    else if(MURT->Instance == URT3)
    {
        CLEAR_BIT( CSC->SLP0.W , CSC_SLP0_SLP_URT3_mask_w);
    }
    #endif
    else
    {
        return(MID_ERROR);
    }
    
    MURT->gState = MID_URT_STATE_READY;
    //========================================================
    //Process Unlocked.
    __MID_UNLOCK(MURT);
    
    return(MID_OK);
}


///@}
