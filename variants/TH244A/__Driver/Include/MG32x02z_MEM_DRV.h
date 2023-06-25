/**
 ******************************************************************************
 *
 * @file        MG32x02z_MEM_DRV.h
 *
 * @brief       This is the C code format driver head file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.16
 * @date        2020/10/20
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



#ifndef __MG32x02z_MEM_DRV_H
#define __MG32x02z_MEM_DRV_H
//#define __MG32x02z_MEM_DRV_H_VER                            0.01



#include "MG32x02z__Common_DRV.h"
#include "MG32x02z_MEM.h"
#include "MG32x02z_CFG.h"

/*===============================================================
 *	By MEM Define
 *==============================================================*/
/**
 * @name	Flash Memory Reset Enable
 *   		Flash Memory Reset Enable
 */ 
///@{ 
#define MEM_RST_RPRE            MEM_INT_RPE_RE_mask_w   /*!<    */
#define MEM_RST_WPRE            MEM_INT_WPE_RE_mask_w   /*!<    */
#define MEM_RST_IARE            MEM_INT_IAE_RE_mask_w   /*!<    */
///@}

/**
 * @name	Flash Memory Interrupt Enable
 *   		Flash Memory Interrupt Enable
 */ 
///@{ 
#define MEM_IT_RPIE             MEM_INT_RPE_IE_mask_w   /*!<    */
#define MEM_IT_WPIE             MEM_INT_WPE_IE_mask_w   /*!<    */
#define MEM_IT_IAIE             MEM_INT_IAE_IE_mask_w   /*!<    */
#define MEM_IT_EOPIE            MEM_INT_EOP_IE_mask_w   /*!<    */
#define MEM_IT_IEA              MEM_INT_IEA_mask_w      /*!<    */
///@}

/**
 * @name    StateFlag
 *          Flag State 
 */ 
///@{  
#define MEM_FLAG_IAPSEF         MEM_STA_IAPSEF_mask_w   /*!<    */
#define MEM_FLAG_RPEF           MEM_STA_RPEF_mask_w     /*!<    */
#define MEM_FLAG_WPEF           MEM_STA_WPEF_mask_w     /*!<    */
#define MEM_FLAG_IAEF           MEM_STA_IAEF_mask_w     /*!<    */
#define MEM_FLAG_EOPF           MEM_STA_EOPF_mask_w     /*!<    */
#define MEM_FLAG_FBUSYF         MEM_STA_FBUSYF_mask_w   /*!<    */
///@}

/**
 * @name	MEM_CMD
 *   		Flash Read Write Enable
 */ 
///@{  
#define MEM_ACCESS_AP_WRITE         MEM_CR1_AP_WEN_mask_w   /*!<    */
#define MEM_ACCESS_IAP_EXECUTE      MEM_CR1_IAP_EXEC_mask_w /*!<    */
#define MEM_ACCESS_IAP_WRITE        MEM_CR1_IAP_WEN_mask_w  /*!<    */
#define MEM_ACCESS_ISPD_READ        MEM_CR1_ISPD_REN_mask_w /*!<    */
#define MEM_ACCESS_ISPD_WRITE       MEM_CR1_ISPD_WEN_mask_w /*!<    */
#define MEM_ACCESS_ISP_READ         MEM_CR1_ISP_REN_mask_w  /*!<    */
#define MEM_ACCESS_ISP_WRITE        MEM_CR1_ISP_WEN_mask_w  /*!<    */

///@}

/**
 * @name	Flash Wait Time
 *   		Flash Access Time, Flash Wait State
 */ 
///@{ 
#define MEM_FWAIT_ZERO   MEM_CR0_FWAIT_zero_w    /*!< 0Hz > Sysclk >= 25MHz */
#define MEM_FWAIT_ONE    MEM_CR0_FWAIT_one_w     /*!< 25MHz > Sysclk >= 50MHz */
#define MEM_FWAIT_TWO    MEM_CR0_FWAIT_two_w     /*!< 50MHz > Sysclk >= 75MHz */

///@}

/**
 * @name	Boot Select
 *   		Flash Access Time, Flash Wait State
 */ 
///@{ 
#define MEM_BOOT_MASK   MEM_CR0_BOOT_MS_mask_w
#define MEM_BOOT_AP     MEM_CR0_BOOT_MS_application_flash_w     /*!<    */
#define MEM_BOOT_ISP    MEM_CR0_BOOT_MS_boot_flash_w            /*!<    */
#define MEM_BOOT_SRAM   MEM_CR0_BOOT_MS_embedded_sram_w         /*!<    */

///@}


/**
 * @name	Flash Write Mode
 *   		Flash Access Time, Flash Wait State
 */ 
///@{ 
#define MEM_MODE_NONE           0x00000000  /*!<    */
#define MEM_MODE_STANDBY        0x00000000  /*!<    */
#define MEM_MODE_ERASE          0x00000020  /*!<    */
#define MEM_MODE_PROGRAM        0x00000010  /*!<    */
#define MEM_MODE_APERASE        0x00000020  /*!<    */
#define MEM_MODE_APPROGRAM      0x00000010  /*!<    */
#define MEM_MODE_IAPERASE       0x00000020  /*!<    */
#define MEM_MODE_IAPPROGRAM     0x00000010  /*!<    */
#define MEM_MODE_ISPDERASE      0x00000020  /*!<    */
#define MEM_MODE_ISPDPROGRAM    0x00000010  /*!<    */
#define MEM_MODE_ISPERASE       0x00000060  /*!<    */
#define MEM_MODE_ISPPROGRAM     0x00000050  /*!<    */

///@}



/******************************************************************************
*   Enum
******************************************************************************/ 

#ifdef __cplusplus
 extern "C" {
#endif

/**
 * @enum	BootSelect
 *   		Flash Access Time, Flash Wait State
 */ 
///@{ 
typedef enum {
    AP_Space = MEM_CR0_BOOT_MS_application_flash_w,     // 0Hz > Sysclk >= 25MHz
    ISP_Space = MEM_CR0_BOOT_MS_boot_flash_w,           // 25MHz > Sysclk >= 50MHz
    SRAM_Space = MEM_CR0_BOOT_MS_embedded_sram_w        // 50MHz > Sysclk >= 75MHz
}BootSelect;
///@}

/** 
 * @enum		MEMAccessMode
 * @brief		Flash Write Access Mode.
 * 				Some details about the Test class.
 */       
typedef enum {
    None = 0x00000000,
    StandBy = 0x00000000,
    Erase = 0x00000020,
    Program = 0x00000010,
    APErase = 0x00000020,
    APProgram = 0x00000010,
    IAPErase = 0x00000020,
    IAPProgram = 0x00000010,
    ISPDErase = 0x00000020,
    ISPDProgram = 0x00000010,
    ISPErase = 0x00000060,
    ISPProgram = 0x00000050
}MEMAccessMode;

/** 
 * @enum		UnProtectSKey
 * @brief		Single Write Access or Multiple Write sequential key
 *
 */
typedef enum {
    NoneSKey = 0x0000,
    APSingleSKey = 0x46B9,
    APMultipleSKey = 0x46BE,
    IAPSingleSKey = 0x46B9,
    IAPMultipleSKey = 0x46BE,
    ISPDSingleSKey = 0x46B9,
    ISPDMultipleSKey = 0x46BE,
    ISPSingleSKey = 0xB955,
    ISPMultipleSKey = 0xBEAA,
}UnProtectSKey;



/******************************************************************************
*   Struct
******************************************************************************/



/******************************************************************************
*   Function
******************************************************************************/ 


/** 
 * @name    Memory Register Protect and UnProtect
 *
 */ 
///@{

#define __MEM_UnProtect()                       (MEM->KEY.MBIT.KEY = 0xA217)
#define __MEM_Protect()                         (MEM->KEY.MBIT.KEY = 0x0000)
#define __MEM_GetProtectStatus()                (MEM->KEY.MBIT.KEY)



#define __MEM_UnProtect2()                      (MEM->KEY.MBIT.KEY2 = 0xA217)
#define __MEM_Protect2()                        (MEM->KEY.MBIT.KEY2 = 0x0000)
#define __MEM_GetProtect2Status()               (MEM->KEY.MBIT.KEY2)

///@}



/** 
 * @name    Memory Access Status Flag 
 *
 */ 
///@{

#define __MEM_GetAllFlagStatus()                (MEM->STA.W)
uint32_t MEM_GetAllFlagStatus(void);

#define __MEM_GetFlagStatus(MEM_FLAG)           ((((MEM->STA.W) & (MEM_FLAG)) == (MEM_FLAG)) ? SET : CLR)
DRV_Return MEM_GetFlagStatus(uint32_t MEM_FLAG);

#define __MEM_ClearFlag(MEM_FLAG)               (MEM->STA.W = (MEM_FLAG))
void MEM_ClearFlag(uint32_t MEM_FLAG);

///@}



/** 
 * @name    Memory controller enable.
 *
 */ 
///@{

#define __MEM_Enable()                          (MEM->CR0.W |= MEM_CR0_EN_mask_w)
#define __MEM_Disable()                         (MEM->CR0.W &= (~MEM_CR0_EN_mask_w))
void MEM_Cmd(FunctionalState State);

///@}



/** 
 * @name    Flash Read Wait Time
 *
 */ 
///@{

#define __MEM_GetFlashWaitState()               (MEM->CR0.W & MEM_CR0_FWAIT_mask_w)
#define __MEM_SetFlashWaitState(MEM_FWAIT)      (MEM->CR0.W = (MEM->CR0.W & (~MEM_CR0_FWAIT_mask_w)) | (MEM_FWAIT))
void MEM_SetFlashWaitState(uint32_t MEM_FWAIT);

///@}



/** 
 * @name    System Boot Memory
 *
 */ 
///@{

#define __MEM_SetBootSelect(MEM_BOOT)           (MEM->CR0.W = (MEM->CR0.W & (~MEM_BOOT_MASK)) | (MEM_BOOT))
#define __MEM_GetBootSelectState()              (MEM->CR0.W & MEM_CR0_BOOT_MS_mask_w)

///@}



/** 
 * @name    Memory Access Interrupt
 *
 */ 
///@{

#define __MEM_IT_Enable(MEM_IT)                 (MEM->INT.W |= (MEM_IT))
#define __MEM_IT_Disable(MEM_IT)                (MEM->INT.W &= (~(MEM_IT)))
void MEM_IT_Cmd(uint32_t MEM_IT, FunctionalState State);

#define __MEM_ITEA_Enable()                     (MEM->INT.W |= MEM_IT_IEA)
#define __MEM_ITEA_Disable()                    (MEM->INT.W &= (~MEM_IT_IEA))
void MEM_ITEA_Cmd(FunctionalState State);

///@}



/**
 * @name	Error Reset
 *        Enable or Disable Access Error Reset
 */ 
///@{

#define __MEM_GetAllResetSource()               (MEM->INT.W & MEM_RST_MASK)
#define __MEM_GetResetSource(MEM_RST)           (MEM->INT.W & (MEM_RST))
#define __MEM_ErrorReset_Enable(MEM_RST)        (MEM->INT.W |= (MEM_RST))
#define __MEM_ErrorReset_Disable(MEM_RST)       (MEM->INT.W &= (~(MEM_RST)))
void MEM_ErrorReset_Cmd(uint32_t Reset, FunctionalState State);

///@}



/** 
 * @name    Memory Access Error Hard Fault
 *
 */ 
///@{

#define __MEM_GetHardFaultState()               (((MEM->CR0.W & MEM_CR0_HF_EN_mask_w) != 0)? SET : CLR)
#define __MEM_ErrorHardFault_Enable()           (MEM->CR0.W |= MEM_CR0_HF_EN_mask_w)
#define __MEM_ErrorHardFault_Disable()          (MEM->CR0.W &= (~MEM_CR0_HF_EN_mask_w))
void MEM_ErrorHardFault_Cmd(FunctionalState State);

///@}



/** 
 * @name    Flash Write of CPU Hold
 *
 */ 
///@{

#define __MEM_WriteFlashHold_Enable()           (MEM->CR0.W &= (~MEM_CR0_HOLD_mask_w))
#define __MEM_WriteFlashHold_Disable()          (MEM->CR0.W |= MEM_CR0_HOLD_mask_w)
void MEM_WriteFlashHold_Cmd(FunctionalState State);

///@}



/** 
 * @name    MEM Flash Read, Write and Execute Access
 *
 */ 
///@{

#define __MEM_GetAllAccessState                 (MEM->CR1.W & (MEM_ACCESS_AP_WRITE | MEM_ACCESS_IAP_WRITE | MEM_ACCESS_ISPD_READ |  MEM_ACCESS_ISPD_WRITE | MEM_ACCESS_ISP_READ | MEM_ACCESS_ISP_WRITE | MEM_ACCESS_IAP_EXECUTE))
uint32_t MEM_GetAllAccessState(void);

#define __MEM_GetAccessState(MEM_ACCESS)        (((MEM->CR1.W & (MEM_ACCESS)) == (MEM_ACCESS)) ? SET : CLR)
DRV_Return MEM_GetAccessState(uint32_t MEM_ACCESS);

#define __MEM_Access_Enable(MEM_ACCESS)         (MEM->CR1.W |= (MEM_ACCESS))
#define __MEM_Access_Disable(MEM_ACCESS)        (MEM->CR1.W &= (~(MEM_ACCESS)))
void MEM_Access_Cmd(uint32_t MEM_ACCESS, FunctionalState State);

#define __MEM_SetWriteMode(AccessMode)            (MEM->CR0.W = (MEM->CR0.W & (~MEM_CR0_MDS_mask_w)) | (AccessMode))
void MEM_SetWriteMode(MEMAccessMode AccessMode);            

///@}



/** 
 * @name    AP / IAP / ISPD Write 
 *
 */ 
///@{

#define __MEM_GetSequentialKeyStatus()          (MEM->SKEY.B[0])
#define __MEM_SingleWriteUnProtect()            MEM->SKEY.B[0] = 0x46; MEM->SKEY.H[0] = 0xB9
#define __MEM_MultipleWriteUnProtect()          MEM->SKEY.B[0] = 0x46; MEM->SKEY.H[0] = 0xBE
#define __MEM_MultipleWriteProtect()            (MEM->SKEY.B[0] = 0)
void MEM_SetWriteUnProtect(UnProtectSKey SKEY);

void MEM_SetSinglePageEraseUnProtect(void);
void MEM_SetMultiplePageEraseUnProtect(void);
void MEM_SetSingleProgramUnProtect(void);
void MEM_SetMultipleProgramUnProtect(void);
void MEM_SetMultipleWriteProtect(void);

///@}



/** 
 * @name    AP Write
 *
 */ 
///@{

#define __MEM_APWrite_Enable()                  (MEM->CR1.W |= MEM_ACCESS_AP_WRITE)
#define __MEM_APWrite_Disable()                 (MEM->CR1.W &= (~MEM_ACCESS_AP_WRITE))
DRV_Return MEM_APWrite_Cmd(FunctionalState State);

#define MEM_SetAPSinglePageEraseUnProtect       MEM_SetSinglePageEraseUnProtect    /*!< ____ */
#define MEM_SetAPMultiplePageEraseUnProtect     MEM_SetMultiplePageEraseUnProtect  /*!< ____ */
#define MEM_SetAPSingleProgramUnProtect         MEM_SetSingleProgramUnProtect      /*!< ____ */
#define MEM_SetAPMultipleProgramUnProtect       MEM_SetMultipleProgramUnProtect    /*!< ____ */

///@}



/** 
 * @name    IAP Memory Size
 *
 */ 
///@{

#define __MEM_GetIAPSize()                      (MEM->IAPSZ.H[0] << 2)
uint32_t MEM_GetIAPSize(void);

#define __MEM_SetIAPSize(IAPSize)               (MEM->IAPSZ.H[0] = (uint16_t)(IAPSize >> 2))
DRV_Return MEM_SetIAPSize(uint32_t IAPSize);

#define __MEM_GetIAPSizeLockState()             (((MEM->CR0.W & MEM_CR0_IAP_AEN_mask_w) != 0) ? SET : CLR)
#define __MEM_SetIAPSizeLock()                  (MEM->CR0.W &= (~MEM_CR0_IAP_AEN_mask_w))
DRV_Return MEM_SetIAPSizeLock(void);

///@}



/** 
 * @name    IAP Code Execute
 *
 */ 
///@{

#define __MEM_GetIAPExecuteCodeState()          (MEM->CR1.W & MEM_CR1_IAP_EXEC_mask_w)
#define __MEM_IAPExecuteCode_Enable()           (MEM->CR1.W |= MEM_CR1_IAP_EXEC_mask_w)   
#define __MEM_IAPExecuteCode_Disable()          (MEM->CR1.W &= ~ MEM_CR1_IAP_EXEC_mask_w)
DRV_Return MEM_IAPExecuteCode_Cmd(FunctionalState State);

///@}



/** 
 * @name    IAP Write
 *
 */ 
///@{

#define __MEM_IAPWrite_Enable()                 (MEM->CR1.W |= MEM_ACCESS_IAP_WRITE)
#define __MEM_IAPWrite_Disable()                (MEM->CR1.W &= (~MEM_ACCESS_IAP_WRITE))
DRV_Return MEM_IAPWrite_Cmd(FunctionalState State);

#define MEM_SetIAPSinglePageEraseUnProtect      MEM_SetSinglePageEraseUnProtect    /*!< ____ */
#define MEM_SetIAPMultiplePageEraseUnProtect    MEM_SetMultiplePageEraseUnProtect  /*!< ____ */
#define MEM_SetIAPSingleProgramUnProtect        MEM_SetSingleProgramUnProtect      /*!< ____ */
#define MEM_SetIAPMultipleProgramUnProtect      MEM_SetMultipleProgramUnProtect    /*!< ____ */

///@}



/** 
 * @name    ISPD Read and Write
 *
 */ 
///@{

#define __MEM_ISPDRead_Enable()                 (MEM->CR1.W |= MEM_ACCESS_ISPD_READ)
#define __MEM_ISPDRead_Disable()                (MEM->CR1.W &= (~MEM_ACCESS_ISPD_READ))
DRV_Return MEM_ISPDRead_Cmd(FunctionalState State);

#define __MEM_ISPDWrite_Enable()                (MEM->CR1.W |= MEM_ACCESS_ISPD_WRITE)
#define __MEM_ISPDWrite_Disable()               (MEM->CR1.W &= (~MEM_ACCESS_ISPD_WRITE))
DRV_Return MEM_ISPDWrite_Cmd(FunctionalState State);

#define MEM_SetISPDSinglePageEraseUnProtect     MEM_SetSinglePageEraseUnProtect    /*!< ____ */
#define MEM_SetISPDMultiplePageEraseUnProtect   MEM_SetMultiplePageEraseUnProtect  /*!< ____ */
#define MEM_SetISPDSingleProgramUnProtect       MEM_SetSingleProgramUnProtect      /*!< ____ */
#define MEM_SetISPDMultipleProgramUnProtect     MEM_SetMultipleProgramUnProtect    /*!< ____ */

///@}



/** 
 * @name    ISP Read and Write
 *
 */ 
///@{

#define __MEM_GetISPSize()                      (CFG->OR02.B[1])
uint32_t MEM_GetISPSize(void);

#define __MEM_ISPRead_Enable()                  (MEM->CR1.W |= MEM_ACCESS_ISP_READ)
#define __MEM_ISPRead_Disable()                 (MEM->CR1.W &= (~MEM_ACCESS_ISP_READ))
DRV_Return MEM_ISPRead_Cmd(FunctionalState State);

#define __MEM_ISPWrite_Enable()                 (MEM->CR1.W |= MEM_ACCESS_ISP_WRITE)
#define __MEM_ISPWrite_Disable()                (MEM->CR1.W &= (~MEM_ACCESS_ISP_WRITE))
DRV_Return MEM_ISPWrite_Cmd(FunctionalState State);

#define __MEM_GetSequentialKey2Status()         (MEM->SKEY.H[1])
#define __MEM_ISPSingleWriteUnProtect()         MEM->SKEY.H[1] = 0x9867; MEM->SKEY.H[1] = 0xB955
#define __MEM_ISPMultipleWriteUnProtect()       MEM->SKEY.H[1] = 0x9867; MEM->SKEY.H[1] = 0xBEAA
#define __MEM_ISPMultipleWriteProtect()         MEM->SKEY.H[1] = 0x0000

void MEM_SetISPSinglePageEraseUnProtect(void);
void MEM_SetISPMultiplePageEraseUnProtect(void);
void MEM_SetISPSingleProgramUnProtect(void);
void MEM_SetISPMultipleProgramUnProtect(void);
void MEM_SetISPMultipleWriteProtect(void);

///@}



/**
  *****************************************************************************
  * @brief      Memory Write 
  * @param      ADDR__ Write Address, alignment 4-Bytes.
  * @param      VALUE__ Write on 32bits Any Value.
  *
  * @retval     none
  *****************************************************************************
  */
#define MEM_Write(ADDR__, VALUE__)              (*(uint32_t *)((ADDR__) & 0xFFFFFFFC) = ((uint32_t)(VALUE__)))



#ifdef __cplusplus
}
#endif

#endif


