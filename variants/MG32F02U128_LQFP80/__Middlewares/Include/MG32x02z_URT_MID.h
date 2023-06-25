


 /**
 ******************************************************************************
 *
 * @file        MG32x02z_URT_MID.h
 * @brief       The demo code URT middleware H file.
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
 
 
#ifndef __MG32x02z_URT_MID_H
 
#define __MG32x02z_URT_MID_H 
 
 
#include "MG32x02z.h"
#include "MG32x02z_URT.h"
#include "MG32x02z_Common_MID.h"
#include "MG32x02z_DMA_MID.h"
#include "MG32x02z_CSC_MID.h"


#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

/**
 * @name	URT middleware interrupt relationship define.
 *   		
 */ 
///@{
#define URT_IT_CALTMO    URT_STA_CALTMOF_mask_w     /*!< Baud rate calibration sync field receive time out interrupt. */
#define URT_IT_BKTMO     URT_STA_BKTMOF_mask_w      /*!< Break receive time out interrupt. */
#define URT_IT_IDTMO     URT_STA_IDTMOF_mask_w      /*!< Idle state time out interrupt. */
#define URT_IT_RXTMO     URT_STA_RXTMOF_mask_w      /*!< Receive time out interrupt. */
#define URT_IT_TXE       URT_STA_TXEF_mask_w        /*!< TX error detect interrupt. */
#define URT_IT_ROVR      URT_STA_ROVRF_mask_w       /*!< Receive overrun error interrupt. */
#define URT_IT_NCE       URT_STA_NCEF_mask_w        /*!< Receive noised character error detect interrupt. */
#define URT_IT_FE        URT_STA_FEF_mask_w         /*!< Receive frame error detect interrupt. */
#define URT_IT_PE        URT_STA_PEF_mask_w         /*!< Receive parity error detect interrupt. */
#define URT_IT_CTS       URT_STA_CTSF_mask_w        /*!< CTS change detect interrupt. */
#define URT_IT_IDL       URT_STA_IDLF_mask_w        /*!< RX idle line detect interrupt. */
#define URT_IT_BK        URT_STA_BKF_mask_w         /*!< Break condition detect interrupt. */
#define URT_IT_CALC      URT_STA_CALCF_mask_w       /*!< Auto baudrate calibration complete interrupt. */
#define URT_IT_TMO       URT_STA_TMOF_mask_w        /*!< Timeout timer timeout interrupt. */
#define URT_IT_BRT       URT_STA_BRTF_mask_w        /*!< Baud rate generator timer timeout interrupt. */
#define URT_IT_SADR      URT_STA_SADRF_mask_w       /*!< Slave address matched interrupt. */
#define URT_IT_TX        URT_STA_TXF_mask_w         /*!< Transmit data register empty interrupt. */
#define URT_IT_RX        URT_STA_RXF_mask_w         /*!< Receive data register not empty interrupt. */
#define URT_IT_LS        URT_STA_LSF_mask_w         /*!< URT line status relationship interrupt. */
#define URT_IT_ERR       URT_STA_ERRF_mask_w        /*!< URT error relationship interrupt. */
#define URT_IT_TC        URT_STA_TCF_mask_w         /*!< Transmission complete interrupt.(shadow buffer , data register , shift buffer empty) */
#define URT_IT_UG        URT_STA_UGF_mask_w         /*!< URT genernal event relationship interrupt. */

#define URT_ITEA         URT_INT_IEA_mask_w         /*!< URT interrupt all enable.*/


///@}

/**
 * @name	URT middleware flag relationship define.
 *   		
 */ 
///@{
#define URT_FLAG_CALTMO    URT_STA_CALTMOF_mask_w     /*!< Baud rate calibration sync field receive time out flag. */
#define URT_FLAG_BKTMO     URT_STA_BKTMOF_mask_w      /*!< Break receive time out flag. */
#define URT_FLAG_IDTMO     URT_STA_IDTMOF_mask_w      /*!< Idle state time out flag. */
#define URT_FLAG_RXTMO     URT_STA_RXTMOF_mask_w      /*!< Receive time out flag. */
#define URT_FLAG_TXE       URT_STA_TXEF_mask_w        /*!< TX error detect flag. */
#define URT_FLAG_ROVR      URT_STA_ROVRF_mask_w       /*!< Receive overrun error flag. */
#define URT_FLAG_NCE       URT_STA_NCEF_mask_w        /*!< Receive noised character error detect flag. */
#define URT_FLAG_FE        URT_STA_FEF_mask_w         /*!< Receive frame error detect flag. */
#define URT_FLAG_PE        URT_STA_PEF_mask_w         /*!< Receive parity error detect flag. */
#define URT_FLAG_CTS       URT_STA_CTSF_mask_w        /*!< CTS change detect flag. */
#define URT_FLAG_IDL       URT_STA_IDLF_mask_w        /*!< RX idle line detect flag. */
#define URT_FLAG_BK        URT_STA_BKF_mask_w         /*!< Break condition detect flag. */
#if defined(URT_STA_CALOVF_mask_w) && defined(URT_STA_CALUDF_mask_w)
#define MID_URT_FLAG_CALOVF    URT_STA_CALOVF_mask_w      /*!<Auto baud-rate calibration overflow status flag.*/
#define MID_URT_FLAG_CALUDF    URT_STA_CALUDF_mask_w      /*!<Auto baud-rate calibration underflow status flag.*/
#endif
#define URT_FLAG_CALC      URT_STA_CALCF_mask_w       /*!< Auto baudrate calibration complete flag. */
#define URT_FLAG_TMO       URT_STA_TMOF_mask_w        /*!< Timeout timer timeout flag. */
#define URT_FLAG_BRT       URT_STA_BRTF_mask_w        /*!< Baud rate generator timer timeout flag. */
#define URT_FLAG_SADR      URT_STA_SADRF_mask_w       /*!< Slave address matched flag. */
#define URT_FLAG_TX        URT_STA_TXF_mask_w         /*!< Transmit data register empty flag. */
#define URT_FLAG_RX        URT_STA_RXF_mask_w         /*!< Receive data register not empty flag. */
#define URT_FLAG_LS        URT_STA_LSF_mask_w         /*!< URT line status relationship flag. */
#define URT_FLAG_ERR       URT_STA_ERRF_mask_w        /*!< URT error relationship flag. */
#define URT_FLAG_TC        URT_STA_TCF_mask_w         /*!< Transmission complete flag.(shadow buffer , data register , shift buffer empty) */
#define URT_FLAG_UG        URT_STA_UGF_mask_w         /*!< URT genernal event relationship flag. */
#define URT_FLAG_RHF       URT_STA_RHF_mask_w         /*!< URT Receive Hold flag.*/

///@}

/**
 * @name	URT control relationship register mask
 *   		
 */ 

///@{

#define URT_INIT_CR1_MSK         ((uint32_t)(URT_CR1_TXSTP_LEN_mask_w | URT_CR1_TXPAR_STK_mask_w | URT_CR1_TXPAR_POL_mask_w | URT_CR1_TXPAR_EN_mask_w | URT_CR1_TXDSIZE_mask_w | \
                                             URT_CR1_RXSTP_LEN_mask_w | URT_CR1_RXPAR_STK_mask_w | URT_CR1_RXPAR_POL_mask_w | URT_CR1_RXPAR_EN_mask_w | URT_CR1_RXDSIZE_mask_w ))    /*!< To define URT data length , parity mode , stop bit register mask.*/

#define URT_INIT_MODE_MSK        ((uint32_t)(URT_CR2_RX_EN_mask_w | URT_CR2_TX_EN_mask_w))                                                                                           /*!< To define control URT (RX / TX)  (enable / disable) register mask.*/  
#define URT_INIT_HWFLOWCTRL_MSK  ((uint32_t)(URT_HFC_RTS_INV_mask_w | URT_HFC_CTS_INV_mask_w | URT_HFC_RTS_EN_mask_w | URT_HFC_CTS_EN_mask_w))                                       /*!< To define URT hardware flow control relationship register mask .*/

///@}


/**
 * @name	MID_URT_DEGT : Control URT DE guard time 
 *   		
 */ 

///@{
#define URT_DEGUARDTIME_MASK             ( URT_CR0_DE_EN_mask_w | URT_CR0_DE_GT_mask_w)    /*!< DE guard time control mask.*/
#define URT_DEGUARDTIME_1_4              ( URT_CR0_DE_EN_enable_w | URT_CR0_DE_GT_1_4_w)   /*!< DE guard time is 1/4 bit time.*/
#define URT_DEGUARDTIME_1_2              ( URT_CR0_DE_EN_enable_w | URT_CR0_DE_GT_1_2_w)   /*!< DE guard time is 1/2 bit time.*/
#define URT_DEGUARDTIME_1                ( URT_CR0_DE_EN_enable_w | URT_CR0_DE_GT_1_w)     /*!< DE guard time is 1 bit time.*/
#define URT_DEGUARDTIME_2                ( URT_CR0_DE_EN_enable_w | URT_CR0_DE_GT_2_w)     /*!< DE guard time is 2 bit time.*/

///@}


/**
 * @name	MID_URT_DEGT : Control URT DE guard time 
 *   		
 */ 

///@{
#define URT_DE_POLARITY_MASK      URT_CR0_DE_INV_mask_w                             /*!< DE polarity control mask.*/
#define URT_DE_POLARITY_LOW       URT_CR0_DE_INV_disable_w                          /*!< DE signal is avtive low.*/
#define URT_DE_POLARITY_HIGH      URT_CR0_DE_INV_enable_w                           /*!< DE signal is avtive high.*/

///@}

/**
 * @name	URT_Advanced_Features_Initialization_Type
 *   		
 */ 
///@{
#define URT_ADVFEATURE_NO_INIT                  0x00000000      /*!< Define Advfeature relationship control : No advfeature control.*/
#define URT_ADVFEATURE_TXINVERT_INIT            0x00000001      /*!< Define advfeature relationship control : TX signal inverse.*/
#define URT_ADVFEATURE_RXINVERT_INIT            0x00000002      /*!< Define advfeature relationship control : RX signal inverse*/
#define URT_ADVFEATURE_TXDATAINVERT_INIT        0x00000004      /*!< Define advfeature relationship control : TX data inverse.*/
#define URT_ADVFEATURE_RXDATAINVERT_INIT        0x00000008      /*!< Define advfeature relationship control : RX data inverse.*/
#define URT_ADVFEATURE_SWAP_INIT                0x00000010      /*!< Define advfeature relationship control : RX / TX  & CTS / RTS pin swap.*/
#define URT_ADVFEATURE_AUTOBAUDRATE_INIT        0x00000040      /*!< Define advfeature relationship control : Auto baudrate setting*/
#define URT_ADVFEATURE_TXMSBFIRST_INIT          0x00000080      /*!< Define advfeature relationship control : TX data bit is MSB / LSB.*/
#define URT_ADVFEATURE_RXMSBFIRST_INIT          0x00000100      /*!< Define advfeature relationship control : RX data bit is MSB / LSB.*/

///@}


/**
 * @name	URT_Error  - Define URT Error.
 *   		
 */ 
///@{
#define MID_URT_ERROR_NONE                       0x00000000          /*!< No Error.*/
#define MID_URT_ERROR_PE                         0x00000001          /*!< Parity Error.*/
#define MID_URT_ERROR_NE                         0x00000002          /*!< Noise Error.*/
#define MID_URT_ERROR_FE                         0x00000004          /*!< Frame Error.*/
#define MID_URT_ERROR_ORE                        0x00000008          /*!< Overrun Error.*/
#define MID_URT_ERROR_DMA                        0x00000010          /*!< DMA transfer Error.*/
#define MID_URT_ERROR_BUSY                       0x00000020          /*!< Busy Error.*/

///@}



/**
 * @name	URT Register control.
 *   		
 */ 
///@{
#define URT_SET_BIT(REG,BIT)                    SET_BIT(REG, BIT)                 /*!< Set the bit status of URT register to 1.*/
#define URT_READ_BIT(REG,BIT)                   READ_BIT(REG, BIT)                /*!< Read the bit statue of URT register.*/
#define URT_CLEAR_BIT(REG,BIT)                  CLEAR_BIT(REG, BIT)               /*!< Clear the bit status of the URT register to 0.*/
#define URT_READ_REG(REG)                       READ_REG(REG)                     /*!< Read the URT register.*/
#define URT_WRITE_REG(REG,VAL)                  WRITE_REG(REG, VAL)               /*!< Write the URT register.*/
#define URT_MODIFY_REG(REG, CLEARMSK , SETMSK)  MODIFY_REG(REG, CLEARMSK, SETMSK) /*!< Modify the function status of URT register to any value .*/


#define MID_URT_IS_BIT_SET(REG,BIT)             (((REG) & (BIT))!=NONE)           /*!<Judge the function of URT register whether is true or not.*/
#define MID_URT_IS_BIT_CLR(REG,BIT)             (((REG) & (BIT))==NONE)           /*!<Judge the function of URT register whether is false or not.*/



#ifdef URT0_Base
    #define __MID_URT0_CLK_ENABLE                  CSC->APB0.B[3] = CSC->APB0.B[2] | CSC_APB0_URT0_EN_mask_b2             /*! Enable URT0 clock .*/
#endif                                                                                                                    
#ifdef URT1_Base                                                                                                          
    #define __MID_URT1_CLK_ENABLE                  CSC->APB0.B[3] = CSC->APB0.B[2] | CSC_APB0_URT1_EN_mask_b2             /*! Enable URT1 clock .*/
#endif                                                                                                                    
#ifdef URT2_Base                                                                                                          
    #define __MID_URT2_CLK_ENABLE                  CSC->APB0.B[3] = CSC->APB0.B[2] | CSC_APB0_URT2_EN_mask_b2             /*! Enable URT2 clock .*/
#endif                                                                                                                    
#ifdef URT3_Base                                                                                                          
    #define __MID_URT3_CLK_ENABLE                  CSC->APB0.B[3] = CSC->APB0.B[2] | CSC_APB0_URT3_EN_mask_b2             /*! Enable URT3 clock .*/
#endif

#ifdef URT0_Base
    #define __MID_URT0_CLK_DISABLE                 CSC->APB0.B[3] = CSC->APB0.B[2] & (~ CSC_APB0_URT0_EN_mask_b2)     /*! Disable URT0 clock.*/ 
#endif
#ifdef URT1_Base
    #define __MID_URT1_CLK_DISABLE                 CSC->APB0.B[3] = CSC->APB0.B[2] & (~ CSC_APB0_URT1_EN_mask_b2)     /*! Disable URT1 clock.*/
#endif
#ifdef URT2_Base
    #define __MID_URT2_CLK_DISABLE                 CSC->APB0.B[3] = CSC->APB0.B[2] & (~ CSC_APB0_URT2_EN_mask_b2)     /*! Disable URT2 clock.*/
#endif
#ifdef URT3_Base
    #define __MID_URT3_CLK_DISABLE                 CSC->APB0.B[3] = CSC->APB0.B[2] & (~ CSC_APB0_URT3_EN_mask_b2)     /*! Disable URT3 clock.*/
#endif



#define __MID_URT_DISABLE(__HANDLE__)              URT_CLEAR_BIT((__HANDLE__)->Instance->CR0.W , URT_CR0_EN_mask_w)       /*! Disable URT function */
#define __MID_URT_ENABLE(__HANDLE__)               URT_SET_BIT((__HANDLE__)->Instance->CR0.W , URT_CR0_EN_mask_w)         /*! Enable URT function */

#define __MID_URT_GET_FLAG(__HANDLE__, __FLAG__)   (((__HANDLE__)->Instance->STA.W & (__FLAG__)) == (__FLAG__))           /*! Get URT flag.*/

///@}



/**
 * @name	Get URT clock frequence.
 *   		
 */ 

///@{
#ifdef URT0_Base
    #define __MID_URT0_GETCLOCKSOURCE()          ((uint16_t)(URT_READ_BIT(CSC->CKS1.H[1],CSC_CKS1_URT0_CKS_mask_h1)))      /*! Get URT0 clock source */ 
#endif
#ifdef URT1_Base
    #define __MID_URT1_GETCLOCKSOURCE()          ((uint16_t)(URT_READ_BIT(CSC->CKS1.H[1],CSC_CKS1_URT1_CKS_mask_h1)))      /*! Get URT1 clock surce */
#endif
#ifdef URT2_Base
    #define __MID_URT2_GETCLOCKSOURCE()          ((uint16_t)(URT_READ_BIT(CSC->CKS1.H[1],CSC_CKS1_URT2_CKS_mask_h1)))      /*! Get URT2 clock source */
#endif
#ifdef URT3_Base
    #define __MID_URT3_GETCLOCKSOURCE()          ((uint16_t)(URT_READ_BIT(CSC->CKS1.H[1],CSC_CKS1_URT3_CKS_mask_h1)))      /*! Get URT3 clock source */
#endif


                                                                             
///@}

        
        
/**
 * @name	Middleware relationship enum
 *   		
 */         
///@{
        
/*! @enum   URT_InitHWFlowCtrl_TypeDef
    @brief  URT hardware flow control.
*/
typedef enum
{
    URT_HWCONTROL_NONE            = URT_HFC_RTS_EN_disable_w |  URT_HFC_RTS_INV_disable_w | URT_HFC_CTS_EN_disable_w | URT_HFC_CTS_EN_disable_w,     /*!< No hardwar control.*/
    URT_HWCONTROL_nRTS            = URT_HFC_RTS_EN_enable_w  |  URT_HFC_RTS_INV_disable_w | URT_HFC_CTS_EN_disable_w | URT_HFC_CTS_EN_disable_w,     /*!< RTS pin = 0 - Reguest to send.*/
    URT_HWCONTROL_RTS             = URT_HFC_RTS_EN_enable_w  |  URT_HFC_RTS_INV_enable_w  | URT_HFC_CTS_EN_disable_w | URT_HFC_CTS_EN_disable_w,     /*!< RTS pin = 1 - Reguest to send.*/
    URT_HWCONTROL_CTS             = URT_HFC_RTS_EN_disable_w |  URT_HFC_RTS_INV_disable_w | URT_HFC_CTS_EN_enable_w  | URT_HFC_CTS_EN_disable_w,     /*!< CTS pin = 0 - Clear to send.*/
    URT_HWCONTROL_nCTS            = URT_HFC_RTS_EN_disable_w |  URT_HFC_RTS_INV_disable_w | URT_HFC_CTS_EN_enable_w  | URT_HFC_CTS_EN_enable_w,      /*!< CTS pin = 1 - Clear to send.*/
    URT_HWCONTROL_nRTS_CTS        = URT_HFC_RTS_EN_enable_w  |  URT_HFC_RTS_INV_disable_w | URT_HFC_CTS_EN_enable_w  | URT_HFC_CTS_EN_disable_w,     /*!< RTS pin = 0 - Reguest to send , CTS pin = 1 - Clear to send.*/
    URT_HWCONTROL_RTS_CTS         = URT_HFC_RTS_EN_enable_w  |  URT_HFC_RTS_INV_enable_w  | URT_HFC_CTS_EN_enable_w  | URT_HFC_CTS_EN_disable_w,     /*!< RTS pin = 1 - Reguest to send , CTS pin = 1 - Clear to send.*/
    URT_HWCONTROL_nRTS_nCTS       = URT_HFC_RTS_EN_enable_w  |  URT_HFC_RTS_INV_disable_w | URT_HFC_CTS_EN_enable_w  | URT_HFC_CTS_EN_enable_w,      /*!< RTS pin = 0 - Reguest to send , CTS pin = 0 - Clear to send.*/
    URT_HWCONTORL_RTS_nCTS        = URT_HFC_RTS_EN_enable_w  |  URT_HFC_RTS_INV_enable_w  | URT_HFC_CTS_EN_enable_w  | URT_HFC_CTS_EN_enable_w,      /*!< RTS pin = 1 - Reguest to send , CTS pin = 0 - Clear to send.*/
}URT_InitHWFlowCtrl_TypeDef;


/*! @enum   URT_BitSamplingMode_TypeDef
    @brief  URT one bit sampling method.
*/
typedef enum
{
    URT_ONEBIT_SAMPLE_SINGLE      = URT_CR0_OS_MDS_one_b0,                            /*!< One-bit sampling one time.*/
    URT_ONEBIT_SAMPLE_THREE       = URT_CR0_OS_MDS_three_b0,                          /*!<.One-bit sampling thress times.*/
}URT_BitSamplingMode_TypeDef;


/*! @enum   URT_InitMode_TypeDef
    @brief  URT transfer mode.
*/
typedef enum
{
    URT_RX      =  URT_CR2_TX_EN_disable_w | URT_CR2_RX_EN_enable_w,                  /*!< RX mode.*/
    URT_TX      =  URT_CR2_TX_EN_enable_w  | URT_CR2_RX_EN_disable_w,                 /*!< TX mode.*/
    URT_TX_RX   =  URT_CR2_TX_EN_enable_w  | URT_CR2_RX_EN_enable_w,                  /*!< RX and TX mode.*/
}URT_InitMode_TypeDef;


/*! @enum   URT_WordLength_TypeDef
    @brief  URT data length select definitions.
*/
typedef enum
{
    UART_WORDLENGTH_8B =  (URT_CR1_TXDSIZE_8bit_w | URT_CR1_RXDSIZE_8bit_w),            /*!< URT data length is 8 bit. */ 
    UART_WORDLENGTH_7B =  (URT_CR1_TXDSIZE_7bit_w | URT_CR1_RXDSIZE_7bit_w)             /*!< URT data length is 7 bit. */
}URT_WordLength_TypeDef;



/*! @enum   URT_StopBit_TypeDef
    @brief  URT stop bit select definitions.
*/
typedef enum
{
    URT_STOPBIT_0_5 =      (URT_CR1_TXSTP_LEN_0_5bit_w | URT_CR1_RXSTP_LEN_0_5bit_w),                            /*!< URT stop bit is 0.5bit.   */
    URT_STOPBIT_1_0 =      (URT_CR1_TXSTP_LEN_1bit_w | URT_CR1_RXSTP_LEN_1bit_w),                                /*!< URT stop bit is 1bit.   */
    URT_STOPBIT_2_0 =      (URT_CR1_TXSTP_LEN_2bit_w | URT_CR1_RXSTP_LEN_2bit_w),                                /*!< URT stop bit is 2bit.   */
    #if defined(MG32_2ND) || defined(MG32_3RD)                                       
        URT_STOPBIT_1_5 =  (URT_CR1_TXSTP_LEN_1_5bit_w | URT_CR1_RXSTP_LEN_1_5bit_w)                             /*!< URT stop bit is 1.5bit.   */
    #endif
}URT_StopBit_TypeDef;


/*! @enum   URT_PARITY_TypeDef
    @brief  URT parity bit select definitions.
*/
typedef enum
{
    URT_PARITY_NO    = (URT_CR1_TXPAR_EN_disable_w | URT_CR1_RXPAR_EN_disable_w),                                /*!< URT no parity bit. */
    URT_PARITY_EVEN  = (URT_CR1_TXPAR_EN_enable_w  | URT_CR1_TXPAR_STK_disable_w |  URT_CR1_TXPAR_POL_even_w |   /*!< URT parity bit is even. */
                        URT_CR1_RXPAR_EN_enable_w  | URT_CR1_RXPAR_STK_disable_w |  URT_CR1_RXPAR_POL_even_w),
    URT_PARITY_ODD   = (URT_CR1_TXPAR_EN_enable_w  | URT_CR1_TXPAR_STK_disable_w |  URT_CR1_TXPAR_POL_odd_w |    /*!< URT parity bit is oddd. */
                        URT_CR1_RXPAR_EN_enable_w  | URT_CR1_RXPAR_STK_disable_w |  URT_CR1_RXPAR_POL_odd_w),
    URT_PARITY_ALL_H = (URT_CR1_TXPAR_EN_enable_w  | URT_CR1_TXPAR_STK_enable_w  |  URT_CR1_TXPAR_POL_odd_w |    /*!< URT parity bit always is H.*/
                        URT_CR1_RXPAR_EN_enable_w  | URT_CR1_RXPAR_STK_enable_w  |  URT_CR1_RXPAR_POL_odd_w),
    URT_PARITY_ALL_L = (URT_CR1_TXPAR_EN_enable_w  | URT_CR1_TXPAR_STK_enable_w  |  URT_CR1_TXPAR_POL_even_w |   /*!< URT parity bit always is L.*/
                        URT_CR1_RXPAR_EN_enable_w  | URT_CR1_RXPAR_STK_enable_w  |  URT_CR1_RXPAR_POL_even_w),
}URT_PARITY_TypeDef;


/*! @enum   MID_URT_StateTypeDef
    @brief  MID URT STATE Structures definition.
*/
typedef enum
{
    MID_URT_STATE_RESET             = 0x00,             /*!< Peripheral is not initialized
                                                             Value is allowed for gState and RxState*/         
    MID_URT_STATE_READY             = 0x20,             /*!< Peripheral Initialized and ready for use
                                                             Value is allowed for gState and RxState*/
    MID_URT_STATE_BUSY              = 0x24,             /*!< An internal process is on going
                                                             Value is allowed for gState only*/
    MID_URT_STATE_BUSY_TX           = 0x21,             /*!< Data Transmission process is on going
                                                             Value is allowed for gState only*/
    MID_URT_STATE_BUSY_RX           = 0x22,             /*!< Data Reception process is on going
                                                             Value is allowed for RxState only*/
    MID_URT_STATE_TIMEOUT           = 0x40,             /*!< Timeout State
                                                             Value is allowed for gState only*/
    MID_URT_STATE_ERROR             = 0xE0,             /*!< Error 
                                                             Value is allowed for gState only*/
}MID_URT_StateTypeDef;


/*! @enum   URT_ADVFEATURE_TXINV_TYPE
    @brief  URT advanced feature TX pin active level inversion.
*/
typedef enum
{
    URT_ADVFEATURE_TXINV_DISABLE = URT_CR0_TX_INV_disable_w,                  /*!< TX pin active level inversion disable.*/ 
    URT_ADVFEATURE_TXINV_ENABLE  = URT_CR0_TX_INV_enable_w,                   /*!< TX pin active level inversion enable.*/
}URT_ADVFEATURE_TXINV_TYPE;


/*! @enum   URT_ADVFEATURE_RXINV_TYPE
    @brief  URT advanced feature RX pin active level inversion.
*/
typedef enum
{
    URT_ADVFEATURE_RXINV_DISABLE = URT_CR0_RX_INV_disable_w,                  /*!< RX pin active level inversion disable.*/
    URT_ADVFEATURE_RXINV_ENABLE  = URT_CR0_RX_INV_enable_w,                   /*!< RX pin active level inversion enable.*/
}URT_ADVFEATURE_RXINV_TYPE;


/*! @enum   URT_ADVFEATURE_TXDATAINV_TYPE
    @brief  URT advanced feature binary TX data inversion.
*/
typedef enum
{
    URT_ADVFEATURE_TXDATAINV_DISABLE = URT_CR4_TDAT_INV_disable_w,            /*!< Binary TX data inversion disable.*/
    URT_ADVFEATURE_TXDATAINV_ENABLE  = URT_CR4_TDAT_INV_enable_w              /*!< Binary TX data inversion enable.*/
}URT_ADVFEATURE_TXDATAINV_TYPE;


/*! @enum   URT_ADVFEATURE_RXDATAINV_TYPE
    @brief  URT advanced feature binary RX data inversion. 
*/
typedef enum
{
    URT_ADVFEATURE_RXDATAINV_DISABLE = URT_CR4_RDAT_INV_disable_w,            /*!< Binary RX data inversion disable.*/
    URT_ADVFEATURE_RXDATAINV_ENABLE  = URT_CR4_RDAT_INV_enable_w              /*!< Binary RX data inversion enable.*/
}URT_ADVFEATURE_RXDATAINV_TYPE;


/*! @enum   URT_ADVFEATURE_SWAP_TYPE
    @brief  URT advanced feature RX & TX pins swap.
*/
typedef enum
{
    URT_ADVFEATURE_TXRXSWAP_DISABLE = URT_CR0_IO_SWP_disable_w,                /*!< TX/RX pins swap disable.*/
    URT_ADVFEATURE_TXRXSWAP_ENABLE  = URT_CR0_IO_SWP_enable_w,                 /*!< TX/RX pins swap enable.*/
}URT_ADVFEATURE_SWAP_TYPE;


/*! @enum   URT_ADVFEATURE_AUTOBR_TypeDef
    @brief  URT Advanced Feature Auto BaudRate Enable.
*/
typedef enum
{
    URT_ADVFEATURE_AUTOBAUDRATE_DISABLE = URT_CAL_CAL_AUTO_disable_b0,        /*!< RX auto baud rate detection disable.*/
    URT_ADVFEATURE_AUTOBAUDRATE_ENABLE  = URT_CAL_CAL_AUTO_enable_b0,         /*!< RX auto baud rate detection enable. */ 
}URT_ADVFEATURE_AUTOBR_TypeDef;


/*! @enum   URT_ADVFEATURE_AUTOBRMODE_TypeDef
    @brief  URT Advanced Feature auto baud rate mode.
*/
typedef enum
{
    URT_ADVFEATURE_AUTOBAUDRATE_ONSTARTBIT    = URT_CAL_CAL_MDS_start_b0,     /*!< Auto baud rate detection on start bit.*/
    URT_ADVFEATURE_AUTOBAUDRATE_ONFALLINGEDGE = URT_CAL_CAL_MDS_edge_b0,      /*!<.Auto baud rate detection on start falling edge to next falling edge.*/
}URT_ADVFEATURE_AUTOBRMODE_TypeDef;


/*! @enum   URT_ADVFEATURE_DataOrder_TypeDef
    @brief  URT data order select definitions.
*/ 
typedef enum
{
	URT_ADVFEATURE_LSBFIRST    = 0x00,                                        /*!< URT data order is LSB */
	URT_ADVFEATURE_MSBFIRST    = 0x20                                         /*!< URT data order is MSB */
}URT_ADVFEATURE_DataOrder_TypeDef;


///@}

/*! @name GPIO_pull_define  GPIO pull define
*/
///@{
#define URT_GLOBAL_ADDRESS_DISABLE   ( 0 << URT_CR0_GSA_EN_shift_b0)          /*!< Disable global slave address.*/
#define URT_GLOBAL_ADDRESS_ENABLE    ( 1 << URT_CR0_GSA_EN_shift_b0)          /*!< Enable global slave address.*/

///@}

/**
 * @name	Middleware relationship structure
 *   		
 */         
///@{


/*! @struct  URT_InitTypeDef
    @brief   URT Init structure definition.
*/  
typedef struct __attribute__((packed))
{
    uint32_t                          BaudRate;                  /*!< This member configures the URT communication baud-rate.*/
                                                                 
    URT_WordLength_TypeDef            WordLength;                /*!< Specifies the number of data bits transmitted or received in a frame.*/
                                                                 
    URT_StopBit_TypeDef               StopBits;                  /*!< Specifies the number of stop bits transmitted.*/
                                                                    
    URT_PARITY_TypeDef                Parity;                    /*!< Specifies the parity mode.*/
                                                                 
    URT_InitMode_TypeDef              Mode;                      /*!< Specifies whether the Receive or Transmit mode is enable or disable .*/
                                                                 
    URT_InitHWFlowCtrl_TypeDef        HWFlowCtrl;                /*!< Specifies whether the hardware flow control mode is enabled or disabled.*/
                                                                 
    URT_BitSamplingMode_TypeDef       OneBitSampling;            /*!< Specifies whether a single sample or thress samples' majority vote is selected.*/
    
}URT_InitTypeDef;
 


/*! @struct  URT_AdvFeatureInitTypeDef
    @brief   URT advanced features initalization structure definition.
*/
typedef struct __attribute__((packed))
{
    uint32_t                            AdvFeatureInit;       /*!< 1. Specifies which advanced URT features is initialized.
                                                                   2. Several Advanced Features may be initialized at the same time.
                                                                   3. This parameter can be a value of URT_Advanced_Features_Initialization_Type.*/
    URT_ADVFEATURE_TXINV_TYPE           TxPinLevelInvert;     /*!< Specifies whether the TX pin active level is inverted. */
    URT_ADVFEATURE_RXINV_TYPE           RxPinLevelInvert;     /*!< Specifies whether the RX pin active level is inverted. */
    
    URT_ADVFEATURE_TXDATAINV_TYPE       TXDataInvert;         /*!< Specifies whether TX data are inverted. */
    URT_ADVFEATURE_RXDATAINV_TYPE       RXDataInvert;         /*!< Specifies whether RX data are inverted. */
    
    URT_ADVFEATURE_SWAP_TYPE            Swap;                 /*!< Specifies whether TX and RX pins are swapped.*/
                                                               
    URT_ADVFEATURE_AUTOBR_TypeDef       AutoBaudRateEnable;   /*!< Specifies whether auto Baud-rate detection is enable.*/
                                      
    URT_ADVFEATURE_AUTOBRMODE_TypeDef   AutoBaudRateMode;     /*!< If auto Baud-rate detection is enabled, specifies how the rate detection is carried out.*/
                                      
    URT_ADVFEATURE_DataOrder_TypeDef    TXMSBFirst;           /*!< Specifies whether MSB is sent first on URT_TX line.*/ 
                                      
    URT_ADVFEATURE_DataOrder_TypeDef    RXMSBFirst;           /*!< Specifies whether MSB is sent first on URT_RX line.*/ 
    
}URT_AdvFeatureInitTypeDef;



/*! @struct  URT_HandleTypeDef
    @brief   URT handle Structure definition.
*/
typedef struct __attribute__((packed))
{
         URT_Struct                 *Instance;               /*!< URT register basic address */
                                                                 
         URT_InitTypeDef            Init;                    /*!< URT communication parameters*/
                                                                 
         URT_AdvFeatureInitTypeDef  AdvancedInit;            /*!< URT advanced features initialization parameters*/
                                                                 
         uint8_t                    *pTxBuffPtr;             /*!< Pointer to URT TX transfer buffer.*/
                                                             
         uint16_t                   TxTransferSize;          /*!< URT TX transfer size.*/
                                                             
    __IO uint16_t                   TxTransferCount;         /*!< URT TX transfer counter. */
                                                           
         uint8_t                    TxTransferCountMax;      /*!< URT TX transfer Max size in once.*/
    
         uint8_t                    *pRXBuffPtr;             /*!< Pointer to URT RX transfer buffer.*/
                                                             
         uint16_t                   RxTransferSize;          /*!< URT RX transfer size.*/
                                                             
    __IO uint16_t                   RxTransferCount;         /*!< URT RX transfer counter.*/
                                            
         DMA_HandleTypeDef          *mDMA_TX;                /*!< URT TX DMA Handle parameter*/
    
         DMA_HandleTypeDef          *mDMA_RX;                /*!< URT RX DMA Handle parameter*/
    
         MID_LockTypeDef            Lock;                    /*!< Locking object. */
                                                             
    __IO MID_URT_StateTypeDef       gState;                  /*!< URT state information related to global handle management
                                                                      and also related to TX operations.*/
                                                                 
    __IO MID_URT_StateTypeDef       RxState;                 /*!< URT state information related to RX operations.*/

    __IO uint32_t                   ErrorCode;               /*!< URT Error Code.
                                                                  This parameter can be a value of reference to  URT_Error.*/
    
}URT_HandleTypeDef;


///@}


/**
 * @name	Exported macros
 *   		
 */ 
///@{
/**
 *******************************************************************************
 * @brief  Reset UART handle states.
 * @param  "__HANDLE__": UART handle.
 * @retval None
 *******************************************************************************
 */
#define __DRV_URT_RESET_HANDLE_STATE(__HANDLE__) do{                                               \
                                                     (__HANDLE__)->gState = MID_URT_STATE_RESET;   \
                                                     (__HANDLE__)->RxState = MID_URT_STATE_RESET;  \
                                                 }while(0)

/**
 *******************************************************************************                                                 
 * @brief  Flush the UART Data registers.
 * @param  "__HANDLE__": specifies the UART Handle.
 * @retval None
 *******************************************************************************
 */
#define __DRV_URT_FLUSH_DRREGISTER(__HANDLE__)   SET_BIT((__HANDLE__)->Instance->CR4.B[0] , (URT_CR4_RDAT_CLR_mask_b0 | URT_CR4_TDAT_CLR_mask_b0))

                                                 
/**
 *******************************************************************************   
 * @brief  Clear the specified UART flag.
 * @param  "__HANDLE__": specifies the UART Handle.
 * @param  "__FLAG__": specifies the flag to check.
 *          This parameter can be any combination of the following values:
 *            @arg URT_FLAG_CALTMO    : Baud rate calibration sync field receive time out flag. 
 *            @arg URT_FLAG_BKTMO     : Break receive time out flag. 
 *            @arg URT_FLAG_IDTMO     : Idle state time out flag. 
 *            @arg URT_FLAG_RXTMO     : Receive time out flag. 
 *            @arg URT_FLAG_TXE       : TX error detect flag. 
 *            @arg URT_FLAG_ROVR      : Receive overrun error flag. 
 *            @arg URT_FLAG_NCE       : Receive noised character error detect flag.
 *            @arg URT_FLAG_FE        : Receive frame error detect flag. 
 *            @arg URT_FLAG_PE        : Receive parity error detect flag. 
 *            @arg URT_FLAG_CTS       : CTS change detect flag. 
 *            @arg URT_FLAG_IDL       : RX idle line detect flag. 
 *            @arg URT_FLAG_BK        : Break condition detect flag. 
 *            @arg URT_FLAG_CALOVF    : Auto baud-rate calibration overflow status flag (MG32F02A072 & MG32F02A132 no support). 
 *            @arg URT_FLAG_CALUDF    : Auto baud-rate calibration underflow status flag (MG32F02A072 & MG32F02A132 no support).
 *            @arg URT_FLAG_CALC      : Auto baudrate calibration complete flag. 
 *            @arg URT_FLAG_TMO       : Timeout timer timeout flag. 
 *            @arg URT_FLAG_BRT       : Baud rate generator timer timeout flag. 
 *            @arg URT_FLAG_SADR      : Slave address matched flag. 
 *            @arg URT_FLAG_TX        : Transmit data register empty flag. 
 *            @arg URT_FLAG_RX        : Receive data register not empty flag. 
 *            @arg URT_FLAG_LS        : URT line status relationship flag. 
 *            @arg URT_FLAG_ERR       : URT error relationship flag. 
 *            @arg URT_FLAG_TC        : Transmission complete flag.(shadow buffer , data register , shift buffer empty) 
 *            @arg URT_FLAG_UG        : URT genernal event relationship flag. 
 *            @arg URT_FLAG_RHF       : URT Receive Hold flag (no interrupt flag and hold receive data into rx shadow buffer if RHF = 1).
 * @retval None.
 */                                                 
                                                                                      
#define __DRV_URT_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->STA.W = (__FLAG__))                                                 
 
 /**
 *******************************************************************************   
 * @brief   Check whether the specified UART flag is set or not.
 * @param  "__HANDLE__": specifies the UART Handle.
 * @param  "__FLAG__": specifies the flag to check.
 *          This parameter can be any combination of the following values:
 *            @arg URT_FLAG_CALTMO    : Baud rate calibration sync field receive time out flag. 
 *            @arg URT_FLAG_BKTMO     : Break receive time out flag. 
 *            @arg URT_FLAG_IDTMO     : Idle state time out flag. 
 *            @arg URT_FLAG_RXTMO     : Receive time out flag. 
 *            @arg URT_FLAG_TXE       : TX error detect flag. 
 *            @arg URT_FLAG_ROVR      : Receive overrun error flag. 
 *            @arg URT_FLAG_NCE       : Receive noised character error detect flag.
 *            @arg URT_FLAG_FE        : Receive frame error detect flag. 
 *            @arg URT_FLAG_PE        : Receive parity error detect flag. 
 *            @arg URT_FLAG_CTS       : CTS change detect flag. 
 *            @arg URT_FLAG_IDL       : RX idle line detect flag. 
 *            @arg URT_FLAG_BK        : Break condition detect flag. 
 *            @arg URT_FLAG_CALOVF    : Auto baud-rate calibration overflow status flag (MG32F02A072 & MG32F02A132 no support). 
 *            @arg URT_FLAG_CALUDF    : Auto baud-rate calibration underflow status flag (MG32F02A072 & MG32F02A132 no support).
 *            @arg URT_FLAG_CALC      : Auto baudrate calibration complete flag. 
 *            @arg URT_FLAG_TMO       : Timeout timer timeout flag. 
 *            @arg URT_FLAG_BRT       : Baud rate generator timer timeout flag. 
 *            @arg URT_FLAG_SADR      : Slave address matched flag. 
 *            @arg URT_FLAG_TX        : Transmit data register empty flag. 
 *            @arg URT_FLAG_RX        : Receive data register not empty flag. 
 *            @arg URT_FLAG_LS        : URT line status relationship flag. 
 *            @arg URT_FLAG_ERR       : URT error relationship flag. 
 *            @arg URT_FLAG_TC        : Transmission complete flag.(shadow buffer , data register , shift buffer empty) 
 *            @arg URT_FLAG_UG        : URT genernal event relationship flag. 
 *            @arg URT_FLAG_RHF       : URT Receive Hold flag (no interrupt flag and hold receive data into rx shadow buffer if RHF = 1).
 * @retval None.
 */ 
 
#define __DRV_URT_GET_FLAG(__HANDLE__,__FLAG__) (((__HANDLE__)->Instance->STA.W & (__FLAG__)) == (__FLAG__)) 
 
/**
 *******************************************************************************   
 * @brief  Enable the specified UART interrupt.
 * @param  "__HANDLE__": specifies the UART Handle.
 * @param  "__INTERRUPT__": specifies the UART interrupt source to enable.
 *          This parameter can be one of the following values:
 *            @arg URT_IT_CALTMO    : Baud rate calibration sync field receive time out interrupt. 
 *            @arg URT_IT_BKTMO     : Break receive time out interrupt. 
 *            @arg URT_IT_IDTMO     : Idle state time out interrupt. 
 *            @arg URT_IT_RXTMO     : Receive time out interrupt. 
 *            @arg URT_IT_TXE       : TX error detect interrupt. 
 *            @arg URT_IT_ROVR      : Receive overrun error interrupt. 
 *            @arg URT_IT_NCE       : Receive noised character error detect interrupt. 
 *            @arg URT_IT_FE        : Receive frame error detect interrupt. 
 *            @arg URT_IT_PE        : Receive parity error detect interrupt. 
 *            @arg URT_IT_CTS       : CTS change detect interrupt. 
 *            @arg URT_IT_IDL       : RX idle line detect interrupt. 
 *            @arg URT_IT_BK        : Break condition detect interrupt. 
 *            @arg URT_IT_CALC      : Auto baudrate calibration complete interrupt. 
 *            @arg URT_IT_TMO       : Timeout timer timeout interrupt. 
 *            @arg URT_IT_BRT       : Baud rate generator timer timeout interrupt. 
 *            @arg URT_IT_SADR      : Slave address matched interrupt. 
 *            @arg URT_IT_TX        : Transmit data register empty interrupt. 
 *            @arg URT_IT_RX        : Receive data register not empty interrupt. 
 *            @arg URT_IT_LS        : URT line status relationship interrupt.
 *            @arg URT_IT_ERR       : URT error relationship interrupt. 
 *            @arg URT_IT_TC        : Transmission complete interrupt.(shadow buffer , data register , shift buffer empty) 
 *            @arg URT_IT_UG        : URT genernal event relationship interrupt. 
 *            @arg URT_ITEA         : URT interrupt all enable.
 * @retval None
 *******************************************************************************
 */
#define __DRV_URT_ENABLE_IT(__HANDLE__ , __INTERRUPT__) ((__HANDLE__)->Instance->INT.W |= (__INTERRUPT__))

/**
 *******************************************************************************
 * @brief  Disable the specified UART interrupt.
 * @param  "__HANDLE__": specifies the UART Handle.
 * @param  "__INTERRUPT__": specifies the UART interrupt source to disable.
 *          This parameter can be one of the following values:
 *            @arg URT_IT_CALTMO    : Baud rate calibration sync field receive time out interrupt. 
 *            @arg URT_IT_BKTMO     : Break receive time out interrupt. 
 *            @arg URT_IT_IDTMO     : Idle state time out interrupt. 
 *            @arg URT_IT_RXTMO     : Receive time out interrupt. 
 *            @arg URT_IT_TXE       : TX error detect interrupt. 
 *            @arg URT_IT_ROVR      : Receive overrun error interrupt. 
 *            @arg URT_IT_NCE       : Receive noised character error detect interrupt. 
 *            @arg URT_IT_FE        : Receive frame error detect interrupt. 
 *            @arg URT_IT_PE        : Receive parity error detect interrupt. 
 *            @arg URT_IT_CTS       : CTS change detect interrupt. 
 *            @arg URT_IT_IDL       : RX idle line detect interrupt. 
 *            @arg URT_IT_BK        : Break condition detect interrupt. 
 *            @arg URT_IT_CALC      : Auto baudrate calibration complete interrupt. 
 *            @arg URT_IT_TMO       : Timeout timer timeout interrupt. 
 *            @arg URT_IT_BRT       : Baud rate generator timer timeout interrupt. 
 *            @arg URT_IT_SADR      : Slave address matched interrupt. 
 *            @arg URT_IT_TX        : Transmit data register empty interrupt. 
 *            @arg URT_IT_RX        : Receive data register not empty interrupt. 
 *            @arg URT_IT_LS        : URT line status relationship interrupt.
 *            @arg URT_IT_ERR       : URT error relationship interrupt. 
 *            @arg URT_IT_TC        : Transmission complete interrupt.(shadow buffer , data register , shift buffer empty) 
 *            @arg URT_IT_UG        : URT genernal event relationship interrupt. 
 *            @arg URT_ITEA         : URT interrupt all enable.
 * @retval None
 *******************************************************************************
 */
#define __DRV_URT_DISABLE_IT(__HANDLE__ , __INTERRUPT__) ((__HANDLE__)->Instance->INT.W &= (~(__INTERRUPT__)))               


/**
 *******************************************************************************
 * @brief   Check whether the specified UART interrupt source is enabled or not.
 * @param  "__HANDLE__": specifies the UART Handle.
 * @param  "__INTERRUPT__": specifies the UART interrupt source to disable.
 *          This parameter can be one of the following values:
 *            @arg URT_IT_CALTMO    : Baud rate calibration sync field receive time out interrupt. 
 *            @arg URT_IT_BKTMO     : Break receive time out interrupt. 
 *            @arg URT_IT_IDTMO     : Idle state time out interrupt. 
 *            @arg URT_IT_RXTMO     : Receive time out interrupt. 
 *            @arg URT_IT_TXE       : TX error detect interrupt. 
 *            @arg URT_IT_ROVR      : Receive overrun error interrupt. 
 *            @arg URT_IT_NCE       : Receive noised character error detect interrupt. 
 *            @arg URT_IT_FE        : Receive frame error detect interrupt. 
 *            @arg URT_IT_PE        : Receive parity error detect interrupt. 
 *            @arg URT_IT_CTS       : CTS change detect interrupt. 
 *            @arg URT_IT_IDL       : RX idle line detect interrupt. 
 *            @arg URT_IT_BK        : Break condition detect interrupt. 
 *            @arg URT_IT_CALC      : Auto baudrate calibration complete interrupt. 
 *            @arg URT_IT_TMO       : Timeout timer timeout interrupt. 
 *            @arg URT_IT_BRT       : Baud rate generator timer timeout interrupt. 
 *            @arg URT_IT_SADR      : Slave address matched interrupt. 
 *            @arg URT_IT_TX        : Transmit data register empty interrupt. 
 *            @arg URT_IT_RX        : Receive data register not empty interrupt. 
 *            @arg URT_IT_LS        : URT line status relationship interrupt.
 *            @arg URT_IT_ERR       : URT error relationship interrupt. 
 *            @arg URT_IT_TC        : Transmission complete interrupt.(shadow buffer , data register , shift buffer empty) 
 *            @arg URT_IT_UG        : URT genernal event relationship interrupt. 
 *            @arg URT_ITEA         : URT interrupt all enable.
 * @retval None
 *******************************************************************************
 */
#define __DRV_URT_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) (((__HANDLE__)->Instance->INT.W & (__INTERRUPT__)) == (__INTERRUPT__)) 


/**
 *******************************************************************************
 * @brief  Enable UART.
 * @param  "__HANDLE__": specifies the UART Handle.
 * @retval None
 *******************************************************************************
 */
#define __DRV_URT_ENABLE(__HANDLE__)      ((__HANDLE__)->Instance->CR0.W |= URT_CR0_EN_mask_w)

/**
 *******************************************************************************
 * @brief  Disable UART.
 * @param  "__HANDLE__": specifies the UART Handle.
 * @retval None
 *******************************************************************************
 */
#define __DRV_URT_DISABLE(__HANDLE__)      ((__HANDLE__)->Instance->CR0.W &= (~URT_CR0_EN_mask_w))


/**
 *******************************************************************************
 * @brief  URT transmitter halt enable.
 * @param  "__HANDLE__": specifies the UART Handle.
 * @retval None
 *******************************************************************************
 */
#define __DRV_URT_TRANSMITTER_HALT_ENABLE  ((__HANDLE__)->Instance->CR2.B[0] |= (URT_CR2_TX_HALT_mask_b0))

/**
 *******************************************************************************
 * @brief  URT transmitter halt disable.
 * @param  "__HANDLE__": specifies the UART Handle.
 * @retval None
 *******************************************************************************
 */
#define __DRV_URT_TRANSMITTER_HALT_DISABLE  ((__HANDLE__)->Instance->CR2.B[0] &= (~URT_CR2_TX_HALT_mask_b0))




///@}

/**
 * @name	UART Private Variables
 *   		
 */ 
///@{
/**
 *******************************************************************************
 * @brief  To detect URT mode whether is SPI mode or not.  
 * @param  "__HANDLE__": specifies the UART Handle.
 * @retval None
 *******************************************************************************
 */
#define IS_URT_SPIMODE(__HANDLE__)   ((((__HANDLE__)->CR0.B[0] & URT_CR0_MDS_mask_b0) == URT_CR0_MDS_sync_b0) ? SET : CLR)     

///@}



/**
 * @name	Initialization and de-initialization functions
 *   		
 */ 

///@{  
uint32_t MID_URT_GetBRGClocksource( URT_HandleTypeDef* MURT);
MID_StatusTypeDef MID_URT_Init( URT_HandleTypeDef*);
MID_StatusTypeDef MID_URT_HalfDuplex_Init( URT_HandleTypeDef*);
MID_StatusTypeDef MID_URT_MultiProcessor_Init( URT_HandleTypeDef* MURT , uint8_t Address, uint8_t AddressMsk , uint8_t gAddressState);
MID_StatusTypeDef MID_URT_RS485_Init( URT_HandleTypeDef *MURT, uint32_t URT_DE_POLARITY , uint32_t URT_DE_GT);

MID_StatusTypeDef MID_URT_DeInit( URT_HandleTypeDef*);
void MID_URT_MspInit(URT_HandleTypeDef* );
void MID_URT_MspDeInit(URT_HandleTypeDef* );
///@}


/**
 * @name	URT Private Function
 *   		
 */ 

///@{  
void MID_URT_AdvFeatureConfig(URT_HandleTypeDef* );
MID_StatusTypeDef MID_URT_CheckIdleState(URT_HandleTypeDef*);
MID_StatusTypeDef MID_URT_SetConfig(URT_HandleTypeDef* );
MID_StatusTypeDef MID_URT_WaitOnFlagUntilTimeout(URT_HandleTypeDef* , uint32_t , FlagStatus, uint32_t , uint32_t);

///@}


/**
 * @name	IO operation function.
 *   		
 */ 

///@{

MID_StatusTypeDef MID_URT_Transmit(URT_HandleTypeDef* MURT, uint8_t *pDATA, uint16_t SIZE , uint32_t TIMEOUT);
MID_StatusTypeDef MID_URT_Receive(URT_HandleTypeDef* MURT, uint8_t* pDATA, uint16_t SIZE , uint32_t TIMEOUT);
MID_StatusTypeDef MID_URT_Transmit_IT( URT_HandleTypeDef* MURT , uint8_t* pDATA , uint16_t SIZE);
MID_StatusTypeDef MID_URT_Receive_IT( URT_HandleTypeDef* MURT, uint8_t *pDATA, uint16_t SIZE);
MID_StatusTypeDef MID_URT_Transmit_DMA( URT_HandleTypeDef *MURT, uint8_t *pDATA, uint16_t SIZE);
MID_StatusTypeDef MID_URT_Receive_DMA( URT_HandleTypeDef *MURT, uint8_t *pDATA, uint16_t SIZE);

MID_StatusTypeDef MID_URT_DMAPause(URT_HandleTypeDef *huart);
MID_StatusTypeDef MID_URT_DMAResume(URT_HandleTypeDef *huart);
MID_StatusTypeDef MID_URT_DMAStop(URT_HandleTypeDef *huart);


void MID_URT_IRQHandler( URT_HandleTypeDef* MURT);
///@}

/**
 * @name	Transfer Abort function.
 *   		
 */ 
///@{

MID_StatusTypeDef MID_URT_Abort(URT_HandleTypeDef *MURT);
MID_StatusTypeDef MID_URT_AbortTransmit(URT_HandleTypeDef *MURT);
MID_StatusTypeDef MID_URT_AbortReceive(URT_HandleTypeDef *MURT);
MID_StatusTypeDef MID_URT_Abort_IT(URT_HandleTypeDef *MURT);
MID_StatusTypeDef MID_URT_AbortTransmit_IT(URT_HandleTypeDef *MURT);
MID_StatusTypeDef MID_URT_AbortReceive_IT(URT_HandleTypeDef *MURT);   
///@}

/**
 * @name	Peripheral State and Error functions.
 *   		
 */ 
///@{
MID_URT_StateTypeDef MID_URT_GetState( URT_HandleTypeDef* MURT);
uint32_t MID_URT_GetError( URT_HandleTypeDef* MURT);
///@}



/**
 * @name	User call back function.
 *   		
 */ 
///@{
void MID_URT_ErrorCallback( URT_HandleTypeDef *MURT);
void MID_URT_AbortCpltCallback( URT_HandleTypeDef *MURT);
void MID_URT_AbortTransmitCpltCallback( URT_HandleTypeDef* MURT);
void MID_URT_AbortReceiveCpltCallback( URT_HandleTypeDef* MURT);
void MID_URT_TxCpltCallback(URT_HandleTypeDef *MURT);
void MID_URT_TxHalfCpltCallback( URT_HandleTypeDef* MURT);
void MID_URT_RxCpltCallback( URT_HandleTypeDef *MURT);
void MID_URT_RxHalfCpltCallback( URT_HandleTypeDef *MURT);

///@}



/**
 * @name	Exported Function.
 */ 
///@{
MID_StatusTypeDef MID_URT_EnableSleepMode( URT_HandleTypeDef *MURT);
MID_StatusTypeDef MID_URT_DisableSleepMode( URT_HandleTypeDef *MURT);
///@}


#ifdef __cplusplus
}
#endif // __cplusplus

#endif





