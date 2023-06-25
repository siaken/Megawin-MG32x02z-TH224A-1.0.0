

/**
 ******************************************************************************
 *
 * @file        MG32x02z_EXIC_Init.c
 * @brief       The EXIC Init C file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.14
 * @date        2022/08/03
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



#include "MG32x02z_ChipInit.h"


#include "MG32x02z__Common_DRV.h"
#include MG32x02z_EXIC_FILENAME

#define EXIC_Px_MSK_AM_mask_w       0xFFFF0000                              /*!<Detect And Mask whether be setted or not */


/**
 *******************************************************************************
 * @brief	    
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */

void EXIC_Init(void)
{   
    //==============================================================================
    // EXINT0 Initial
    #if defined(CONF_ExicPAInit_EN)
        #if CONF_ExicPAInit_EN == 1
            #if CONF_ExicPAInit_Mask !=0
                EXIC->PA_TRGS.W =  ((CONF_ExicPAInit_Mask | (CONF_ExicPAInit_Mask >> 1))  &  CONF_ExicPAInit_Mode);  
                #if CONF_ExicPAInit_AINV == 1 &&   ((CONF_ExicPAInit_AndOrMask & EXIC_Px_MSK_AM_mask_w)!=0)
                    EXIC->CR0.W = EXIC->CR0.W | EXIC_CR0_PA_AINV_mask_w;
                #endif
            #endif
            #if CONF_ExicPAInit_AndOrMask !=0 
                EXIC->PA_MSK.W = CONF_ExicPAInit_AndOrMask;
            #endif
            
            EXIC_PA->PF.W = 0xFFFF;   
            EXIC->STA.W   = ( EXIC_STA_PA_OF_mask_w | EXIC_STA_PA_AF_mask_w);
             
            #if CONF_ExicPAInit_INT == 1
                EXIC->INT.W = EXIC->INT.W | EXIC_INT_PA_IEA_mask_w;
            #else
                EXIC->INT.W = EXIC->INT.W & (~EXIC_INT_PA_IEA_mask_w);
            #endif
        #endif
    #endif
    //==============================================================================    
    // EXINT1 Initial
    #if defined(CONF_ExicPBInit_EN)
        #if CONF_ExicPBInit_EN == 1
            #if CONF_ExicPBInit_Mask !=0
                EXIC->PB_TRGS.W =  ((CONF_ExicPBInit_Mask | (CONF_ExicPBInit_Mask >> 1))  &  CONF_ExicPBInit_Mode);
                #if CONF_ExicPBInit_AINV == 1 &&   ((CONF_ExicPBInit_AndOrMask & EXIC_Px_MSK_AM_mask_w)!=0)
                    EXIC->CR0.W = EXIC->CR0.W | EXIC_CR0_PB_AINV_mask_w;
                #endif                  
            #endif
            #if CONF_ExicPBInit_AndOrMask !=0 
                EXIC->PB_MSK.W = CONF_ExicPBInit_AndOrMask;
            #endif
            
            EXIC_PB->PF.W = 0xFFFF;
            EXIC->STA.W   = ( EXIC_STA_PB_OF_mask_w | EXIC_STA_PB_AF_mask_w);
             
            #if CONF_ExicPBInit_INT == 1
                EXIC->INT.W = EXIC->INT.W | EXIC_INT_PB_IEA_mask_w;
            #else 
                EXIC->INT.W = EXIC->INT.W & (~EXIC_INT_PB_IEA_mask_w);
            #endif
        #endif      
    #endif
    //==============================================================================
    // EXINT2 Initial
    #if defined(CONF_ExicPCInit_EN)
        #if CONF_ExicPCInit_EN == 1
            #if CONF_ExicPCInit_Mask !=0
                EXIC->PC_TRGS.W =  ((CONF_ExicPCInit_Mask | (CONF_ExicPCInit_Mask >> 1))  &  CONF_ExicPCInit_Mode);
                #if CONF_ExicPCInit_AINV == 1 &&   ((CONF_ExicPCInit_AndOrMask & EXIC_Px_MSK_AM_mask_w)!=0)
                    EXIC->CR0.W = EXIC->CR0.W | EXIC_CR0_PC_AINV_mask_w;
                #endif        
            #endif
            #if CONF_ExicPCInit_AndOrMask !=0 
                EXIC->PC_MSK.W = CONF_ExicPCInit_AndOrMask;
            #endif
            
            EXIC_PC->PF.W = 0xFFFF;
            EXIC->STA.W   = ( EXIC_STA_PC_OF_mask_w | EXIC_STA_PC_AF_mask_w);
             
            
            #if CONF_ExicPCInit_INT == 1
                EXIC->INT.W = EXIC->INT.W | EXIC_INT_PC_IEA_mask_w;
            #else
                EXIC->INT.W = EXIC->INT.W & (~EXIC_INT_PC_IEA_mask_w);
            #endif
        #endif        
    #endif    
    //==============================================================================
    // EXINT3 Initial
    #if defined(CONF_ExicPDInit_EN)
        #if CONF_ExicPDInit_EN == 1
            #if CONF_ExicPDInit_Mask !=0
                EXIC->PD_TRGS.W =  ((CONF_ExicPDInit_Mask | (CONF_ExicPDInit_Mask >> 1))  &  CONF_ExicPDInit_Mode);  
                #if CONF_ExicPDInit_AINV == 1 &&   ((CONF_ExicPDInit_AndOrMask & EXIC_Px_MSK_AM_mask_w)!=0)
                    EXIC->CR0.W = EXIC->CR0.W | EXIC_CR0_PD_AINV_mask_w;
                #endif
            #endif
            #if CONF_ExicPDInit_AndOrMask !=0 
                EXIC->PD_MSK.W = CONF_ExicPDInit_AndOrMask;
            #endif
            
            EXIC_PD->PF.W = 0xFFFF;
            EXIC->STA.W   = ( EXIC_STA_PD_OF_mask_w | EXIC_STA_PD_AF_mask_w);
            
            #if CONF_ExicPDInit_INT == 1
                EXIC->INT.W = EXIC->INT.W | EXIC_INT_PD_IEA_mask_w;
            #else
                EXIC->INT.W = EXIC->INT.W & (~EXIC_INT_PD_IEA_mask_w);
            #endif         
        #endif       
    #endif    
    //==============================================================================
    // EXINT4 Initial
    #if defined(CONF_ExicPEInit_EN)
        #if CONF_ExicPEInit_EN == 1 
            #if CONF_ExicPEInit_Mask !=0
                EXIC->PE_TRGS.W =  ((CONF_ExicPEInit_Mask | (CONF_ExicPEInit_Mask >> 1))  &  CONF_ExicPEInit_Mode);  
                #if CONF_ExicPEInit_AINV == 1 &&   ((CONF_ExicPEInit_AndOrMask & EXIC_Px_MSK_AM_mask_w)!=0)
                    EXIC->CR0.W = EXIC->CR0.W | EXIC_CR0_PE_AINV_mask_w;
                #endif
            #endif
            #if CONF_ExicPEInit_AndOrMask !=0 
                EXIC->PE_MSK.W = CONF_ExicPEInit_AndOrMask;
            #endif
            
            EXIC_PE->PF.W = 0xFFFF;
            EXIC->STA.W   = ( EXIC_STA_PE_OF_mask_w | EXIC_STA_PE_AF_mask_w);
            
            #if CONF_ExicPEInit_INT == 1
                EXIC->INT.W = EXIC->INT.W | EXIC_INT_PE_IEA_mask_w;
            #else
                EXIC->INT.W = EXIC->INT.W & (~EXIC_INT_PE_IEA_mask_w);
            #endif
        #endif               
    #endif
    //==============================================================================
    // 1. RXEV Initial
    // 2. NMI Initial
    #if defined(MG32x02z_ExicRXEV_EN) && defined(MG32x02z_ExicNMI_SEL)
        EXIC->CR0.B[1] = ( MG32x02z_ExicRXEV_EN | MG32x02z_ExicNMI_SEL);
    #endif
     
}










