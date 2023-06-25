/**
 ******************************************************************************
 *
 * @file        MG32x02z_MEM_DRV.c
 *
 * @brief       This is the C code format driver file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.17
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



#include "MG32x02z_MEM_DRV.h"



/** 
 * @name    Flag
 *          Memory Access Status Flag 
 */ 
///@{

/**
 *******************************************************************************
 * @brief       MEM Get All Flag Status
 * @details
 *              Flag Memory Access Status
 * @return      Flag State is 32Bits Value. 
 * @return      - MEM_FLAG_FBUSYF : Busy Flag in Bit0
 * @return      - MEM_FLAG_EOPF : End of Process Flag in Bit1
 * @return      - MEM_FLAG_IAEF : Code Execution Illegal Address Detect Flag in Bit1
 * @return      - MEM_FLAG_WPEF : Flash Memory Write Protect Error Flag
 * @return      - MEM_FLAG_RPEF : Flash Momory Read Protect Error Flag
 * @return      - MEM_FLAG_IAPSEF : IAP Size Setting Error Flag
 * @exception   None
 * @note        
 * @par         Example
 * @code
                lTemp32 = MEM_GetAllFlagStatus();
                while((MEM_GetAllFlagStatus() & (MEM_FLAG_EOPF | MEM_FLAG_IAEF | MEM_FLAG_WPEF | MEM_FLAG_RPEF)) == 0); // Wait Flash Access End
                if((MEM_GetAllFlagStatus() & (MEM_FLAG_IAEF | MEM_FLAG_WPEF | MEM_FLAG_RPEF)) != 0) // Check Flash Access Error
 * @endcode 
 * @par         Modify
 *              uint32_t MEM_GetAllFlagStatus(void)
 *******************************************************************************
 */
uint32_t MEM_GetAllFlagStatus(void)
{
    return(MEM->STA.W);
}



/**
 *******************************************************************************
 * @brief       Get Flag Status
 * @details     Flag Memory Access Status
 *             
 * @param[in]   MEM_FLAG
 *  @arg\b      - MEM_FLAG_FBUSYF : Busy Flag in Bit0
 *  @arg\b      - MEM_FLAG_EOPF : End of Process Flag in Bit1
 *  @arg\b      - MEM_FLAG_IAEF : Code Execution Illegal Address Detect Flag in Bit1
 *  @arg\b      - MEM_FLAG_WPEF : Flash Memory Write Protect Error Flag
 *  @arg\b      - MEM_FLAG_RPEF : Flash Momory Read Protect Error Flag
 *  @arg\b      - MEM_FLAG_IAPSEF : IAP Size Setting Error Flag
 * @return      Flag Status is 32Bits Value. 
 * @return      - DRV_Success :
 * @return      - DRV_Failure :
 * @exception   None
 * @note        
 * @par         Example
 * @code
                lTemp32 = MEM_GetFlagStatus(MEM_FLAG_EOPF | MEM_FLAG_IAEF | MEM_FLAG_WPEF | MEM_FLAG_RPEF);
                while((MEM_GetFlagStatus(MEM_FLAG_EOPF | MEM_FLAG_IAEF | MEM_FLAG_WPEF | MEM_FLAG_RPEF)) == DRV_Success); // Wait Flash Access End
                if((MEM_GetFlagStatus(MEM_FLAG_IAEF | MEM_FLAG_WPEF | MEM_FLAG_RPEF)) == DRV_Success) // Flash Access Error UnHappened
                if((MEM_GetFlagStatus(MEM_FLAG_IAEF | MEM_FLAG_WPEF | MEM_FLAG_RPEF)) == DRV_Failure) // Flash Access Error Happened
 * @endcode 
 * @par         Modify
 *              DRV_Return MEM_GetFlagStatus(uint32_t MEM_FLAG)
 *******************************************************************************
 */
DRV_Return MEM_GetFlagStatus(uint32_t MEM_FLAG)
{
    if((MEM->STA.W & MEM_FLAG) == MEM_FLAG)
        return DRV_True;
    else
        return DRV_False;
}



/**
 *******************************************************************************
 * @brief       Clear Flag Status
 * @details
 *
 * @param[in]   MEM_FLAG : MEM Flag
 *  @arg\b      - MEM_FLAG_FBUSYF : Busy Flag, HardWare Auto Set and Clear
 *  @arg\b      - MEM_FLAG_EOPF : End of Process Flag
 *  @arg\b      - MEM_FLAG_IAEF : Code Execution Illegal Address Detect Flag
 *  @arg\b      - MEM_FLAG_WPEF : Flash Memory Write Protect Error Flag
 *  @arg\b      - MEM_FLAG_RPEF : Flash Momory Read Protect Error Flag
 *  @arg\b      - MEM_FLAG_IAPSEF : IAP Size Setting Error Flag
 * @return		
 * @exception   None
 * @note        
 * @par         Example
 * @code
                MEM_ClearFlag(MEM_FLAG_EOPF);
                MEM_ClearFlag(MEM_FLAG_IAEF | MEM_FLAG_WPEF | MEM_FLAG_RPEF);
                MEM_ClearFlag(MEM_FLAG_EOPF | MEM_FLAG_IAEF | MEM_FLAG_WPEF | MEM_FLAG_RPEF | MEM_FLAG_IAPSEF);
 * @endcode 
 * @par         Modify
 *              void MEM_ClearFlag(uint32_t MEM_FLAG)
 *******************************************************************************
 */
void MEM_ClearFlag(uint32_t MEM_FLAG)
{
    MEM->STA.W = MEM_FLAG;
}

///@}



/**
 * @name	MEM Control
 *          
 */ 
///@{

/**
 *******************************************************************************
 * @brief       Controller Memory Control Function Enable.
 * @details
 *
 * @param[in]   State
 *  @arg\b     	ENABLE          : Function Enable
 *  @arg\b     	DISABLE         : Function Disable
 * @return		
 * @exception   None
 * @note        
 * @par         Example
 * @code
                MEM_Cmd(ENABLE);
                MEM_Cmd(DISABLE);
 * @endcode
 * @par         Modify
 *              void MEM_Cmd(FunctionalState State)
 *******************************************************************************
 */
void MEM_Cmd(FunctionalState State)
{
    UnProtectModuleReg(MEMprotect);
    if(State == ENABLE)
        MEM->CR0.B[0] |= MEM_CR0_EN_mask_b0;
    else
        MEM->CR0.B[0] &= ~MEM_CR0_EN_mask_b0;
    ProtectModuleReg(MEMprotect);
}

///@}



/**
 * @name	Wait Time
 *          Internal Flash Memory Read Time Wait
 */ 
///@{

/**
 *******************************************************************************
 * @brief       Internal Flash Access Time Wait State Setting
 *
 * @details
 *      \n      SysClk 0MHz ~ 24MHz Set ZeroWait
 *      \n      SysClk 24MHz ~ 48MHz Set OneWait
 * @param[in]   MEM_FWAIT
 *  @arg\b      MEM_FWAIT_ZERO   : Less than or equal to 24MHz (bold font)
 *  @arg\b      MEM_FWAIT_ONE    : Greater than 24 MHz and less than or equal to 50 MHz (bold font)
 *  @arg\b      MEM_FWAIT_TWO    : Greater than 50 MHz and less than or equal to 75 MHz (bold font)
 * @return      
 * @exception   None
 * @note  
 * @par         Example
 * @code
                MEM_SetFlashWaitState(MEM_FWAIT_ZERO); 
                MEM_SetFlashWaitState(MEM_FWAIT_ONE); 
 * @endcode
 * @par         Modify
 *              void MEM_SetFlashWaitState(iROMWaitTime WaitState)
 *******************************************************************************
 */
void MEM_SetFlashWaitState(uint32_t MEM_FWAIT)
{  
    UnProtectModuleReg(MEMprotect);
    MEM->CR0.W = (MEM->CR0.W & (~MEM_CR0_FWAIT_mask_w)) | MEM_FWAIT;
    ProtectModuleReg(MEMprotect);
}

///@}



/**
 * @name	Interrupt
 *          Interrupt Enable or Disable Select Setting 
 */ 
///@{

/**
 *******************************************************************************
 * @brief       MEM Initerrupt Cmd
 * @details
 *
 * @param[in]   MEM_IT : Interrupt Enable
 *  @arg\b 	    MEM_INT_RPIE : Flash memory read protect error interrupt enable.
 *  @arg\b 	    MEM_INT_WPIE : Flash memory write protect error interrupt enable.
 *  @arg\b 	    MEM_INT_IAIE : Memory code execution illegal address error interrupt enable.
 *  @arg\b      MEM_INT_EOPIE : Flash memory end of processing interrupt enable.
 * @param[in]   State
 *  @arg\b     	Enable          : Interrupt Enable
 *  @arg\b     	Disable         : Interrupt Disable
 * @return      
 * @exception   None
 * @note        
 * @par         Example
 * @code
                MEM_IT_Cmd(MEM_INT_IAIE, ENABLE);
                MEM_IT_Cmd(MEM_INT_IAIE, DISABLE);
                MEM_IT_Cmd((MEM_INT_IAIE | MEM_INT_RPIE), ENABLE);
                MEM_IT_Cmd((MEM_INT_IAIE | MEM_INT_RPIE), DISABLE);
                MEM_IT_Cmd((MEM_INT_EOPIE | MEM_INT_WPIE), ENABLE); // Flash Write Access
                MEM_IT_Cmd((MEM_INT_EOPIE | MEM_INT_WPIE), DISABLE); // Flash Write Access
                MEM_IT_Cmd((MEM_INT_EOPIE | MEM_INT_IAIE | MEM_INT_WPIE | MEM_INT_RPIE), ENABLE);
                MEM_IT_Cmd((MEM_INT_EOPIE | MEM_INT_IAIE | MEM_INT_WPIE | MEM_INT_RPIE), DISABLE);
 * @endcode
 * @par         Modify
 *              void MEM_IT_Cmd(uint32_t MEM_IT, FunctionalState State)
 *******************************************************************************
 */
void MEM_IT_Cmd(uint32_t MEM_IT, FunctionalState State)
{	
    UnProtectModuleReg(MEMprotect);
	if(State==DISABLE)
		MEM->INT.W &= (~MEM_IT);
	else
		MEM->INT.W |= MEM_IT;
    ProtectModuleReg(MEMprotect);
}



/**
 *******************************************************************************
 * @brief       Controller Memory interrupt all enable.
 * @details
 *
 * @param[in]   State
 *  @arg\b     	Enable          : Function Enable
 *  @arg\b     	Disable         : Function Disable
 * @return		
 * @exception   None
 * @note        
 * @par         Example
 * @code
                MEM_ITEA_Cmd(ENABLE);
                MEM_ITEA_Cmd(DISABLE);
 * @endcode
 * @par         Modify
 *              void MEM_ITEA_Cmd(FunctionalState State)
 *******************************************************************************
 */
void MEM_ITEA_Cmd(FunctionalState State)
{
    UnProtectModuleReg(MEMprotect);
    if(State == ENABLE)
        MEM->INT.B[0] |= MEM_INT_IEA_mask_b0;
    else
        MEM->INT.B[0] &= ~MEM_INT_IEA_mask_b0;
    ProtectModuleReg(MEMprotect);
}

///@}



/**
 * @name	Error Reset
 *          Enable or Disable Access Error Reset
 */ 
///@{

/**
 *******************************************************************************
 * @brief       MEM Error Reset Command
 * @details
 *
 * @param[in]   Reset : 
 *  @arg\b      MEM_RST_RPRE : Flash memory read protect error detect reset enable.
 *  @arg\b      MEM_RST_WPRE : Flash memory write protect error detect reset enable.
 *  @arg\b      MEM_RST_IARE : Memory code execution illegal address detect reset enable.
 * @param[in]   State : 
 *  @arg\b      ENABLE :
 *  @arg\b      DISABLE :
 * @return      
 * @exception   None
 * @note        
 * @par         Example
 * @code
                MEM_ErrorReset_Cmd(MEM_RST_IARE, ENABLE);
                MEM_ErrorReset_Cmd(MEM_RST_IARE, DISABLE);
                MEM_ErrorReset_Cmd((MEM_RST_IARE | MEM_RST_WPRE), ENABLE);
                MEM_ErrorReset_Cmd((MEM_RST_IARE | MEM_RST_WPRE), DISABLE);
                MEM_ErrorReset_Cmd((MEM_RST_IARE | MEM_RST_WPRE | MEM_RST_RPRE), ENABLE);
                MEM_ErrorReset_Cmd((MEM_RST_IARE | MEM_RST_WPRE | MEM_RST_RPRE), DISABLE);
 * @endcode
 * @par         Modify
 *              void MEM_ErrorReset_Cmd(uint32_t Reset, FunctionalState State)
 *******************************************************************************
 */
void MEM_ErrorReset_Cmd(uint32_t Reset, FunctionalState State)
{
    UnProtectModuleReg(MEMprotect);
    if(State == ENABLE)
        MEM->INT.W |= Reset;    
    else
        MEM->INT.W &= ~Reset;
    ProtectModuleReg(MEMprotect);
}

///@}



/**
 * @name	Error HardFault
 *          Enable or Disable Access Error HardFault
 */ 
///@{

/**
 *******************************************************************************
 * @brief       Flash memory data access error HardFault Enable / Disable
 * @details     When memory data write error has happened and MEM_WPE_IE / 
 *              MEM_WPE_RE are disabled, it will induce HardFault if this bit is enable.
 * @param[in]   State
 *  @arg\b      Enable
 *  @arg\b      Disable
 * @return      
 * @exception   None
 * @note        
 * @par         Example  
 * @code
                MEM_ErrorHardFault_Cmd(ENABLE);   
                MEM_ErrorHardFault_Cmd(DISABLE); 
 * @endcode
 * @par         Modify
 *              void MEM_ErrorHardFault_Cmd(FunctionalState State)
 *******************************************************************************
 */
void MEM_ErrorHardFault_Cmd(FunctionalState State)
{
    UnProtectModuleReg(MEMprotect);
    if(State == ENABLE)
        MEM->CR0.W |= MEM_CR0_HF_EN_mask_w;
    else
        MEM->CR0.W &= ~MEM_CR0_HF_EN_mask_w;
    ProtectModuleReg(MEMprotect);
}


///@}



/** 
 * @name    Flash Write of CPU Hold
 *
 */ 
///@{

/**
 *******************************************************************************
 * @brief       Controller Write Internal Flash Memory CPU Hold. 
 * @details
 *
 * @param[in]   State
 *  @arg\b     	ENABLE          : Function Enable
 *  @arg\b     	DISABLE         : Function Disable
 * @return		
 * @exception   None
 * @note        
 * @par         Example
 * @code
                MEM_WriteFlashHold_Cmd(ENABLE) Default;
                MEM_WriteFlashHold_Cmd(DISABLE);
 * @endcode
 * @par         Modify
 *              void MEM_WriteFlashHold_Cmd(FunctionalState State)
 *******************************************************************************
 */
void MEM_WriteFlashHold_Cmd(FunctionalState State)
{
    UnProtectModuleReg(MEMprotect);
    if(State == ENABLE)
        MEM->CR0.B[0] &= ~MEM_CR0_HOLD_mask_b0;
    else
        MEM->CR0.B[0] |= MEM_CR0_HOLD_mask_b0;
    ProtectModuleReg(MEMprotect);
}

///@}



/**
 * @name	Access Config
 *          Access Space Setting 
 */ 
///@{

/**
 *******************************************************************************
 * @brief       Get All Flash Access Config
 * @details
 *              
 * @return      uint32_t  :
 * @return      MEM_ACCESS_AP_WRITE    : AP memory write enable.
 * @return      MEM_ACCESS_IAP_EXECUTE : IAP data memory code execution function enable.
 * @return      MEM_ACCESS_IAP_WRITE   : IAP memory write enable.
 * @return      MEM_ACCESS_ISP_READ    : ISP memory read enable, Only On ISP mode enable this. 
 * @return      MEM_ACCESS_ISP_WRITE   : ISP memory write enable, Only On ISP mode enable this. 
 * @return      MEM_ACCESS_ISPD_READ   : ISPD memory read enable, Only On ISP mode enable this. 
 * @return      MEM_ACCESS_ISPD_WRITE  : ISPD memory write enable, Only On ISP mode enable this.
 * @exception   None
 * @note        
 * @par         Example
 * @code
                if((MEM_GetAllAccessConfig() & MEM_ACCESS_IAP_EXECUTE) == MEM_ACCESS_IAP_EXECUTE)
                if((MEM_GetAllAccessConfig() & MEM_ACCESS_IAP_WRITE) == MEM_ACCESS_IAP_WRITE)
                if((MEM_GetAllAccessConfig() & (MEM_ACCESS_AP_WRITE | MEM_ACCESS_IAP_WRITE)) == (MEM_ACCESS_AP_WRITE | MEM_ACCESS_IAP_WRITE))
                if((MEM_GetAllAccessConfig() & (MEM_ACCESS_ISPD_WRITE | MEM_ACCESS_ISPD_READ)) == (MEM_ACCESS_ISPD_WRITE | MEM_ACCESS_ISPD_READ))
                if((MEM_GetAllAccessConfig() & (MEM_ACCESS_AP_WRITE | MEM_ACCESS_IAP_WRITE | MEM_ACCESS_ISPD_WRITE | MEM_ACCESS_ISPD_READ)) == (MEM_ACCESS_AP_WRITE | MEM_ACCESS_IAP_WRITE | MEM_ACCESS_ISPD_WRITE | MEM_ACCESS_ISPD_READ))
                if((MEM_GetAllAccessConfig() & (MEM_ACCESS_ISP_READ | MEM_ACCESS_ISP_WRITE | MEM_ACCESS_ISPD_READ)) == (MEM_ACCESS_ISP_READ | MEM_ACCESS_ISP_WRITE | MEM_ACCESS_ISPD_READ))
 * @endcode
 * @par         Modify
 *              uint32_t MEM_GetAllAccessConfig(void)
 *******************************************************************************
 */
uint32_t MEM_GetAllAccessState(void)
{
    return(MEM->CR1.W & (MEM_ACCESS_AP_WRITE | 
                         MEM_ACCESS_IAP_WRITE | 
                         MEM_ACCESS_ISPD_READ |  
                         MEM_ACCESS_ISPD_WRITE | 
                         MEM_ACCESS_ISP_READ | 
                         MEM_ACCESS_ISP_WRITE | 
                         MEM_ACCESS_IAP_EXECUTE));
}



/**
 *******************************************************************************
 * @brief       Get Flash Access Config
 * @details     
 *              
 * @param[in]   MEM_ACCESS
 *  @arg\b      MEM_ACCESS_AP_WRITE    : AP memory write enable.
 *  @arg\b      MEM_ACCESS_IAP_EXECUTE : IAP data memory code execution function enable.
 *  @arg\b      MEM_ACCESS_IAP_WRITE   : IAP memory write enable.
 *  @arg\b      MEM_ACCESS_ISP_READ    : ISP memory read enable, Only On ISP mode enable this. 
 *  @arg\b      MEM_ACCESS_ISP_WRITE   : ISP memory write enable, Only On ISP mode enable this. 
 *  @arg\b      MEM_ACCESS_ISPD_READ   : ISPD memory read enable, Only On ISP mode enable this. 
 *  @arg\b      MEM_ACCESS_ISPD_WRITE  : ISPD memory write enable, Only On ISP mode enable this. 
 * @return      DRV_Success
 * @return      DRV_Failure
 * @exception   None
 * @note        
 * @par         Example
 * @code
                if(MEM_GetAccessConfig(MEM_ACCESS_IAP_EXECUTE) == DRV_ACCESS_Success) // Flash IAP data memory code execution function
                if(MEM_GetAccessConfig(MEM_ACCESS_IAP_WRITE) == DRV_ACCESS_Success)
                if(MEM_GetAccessConfig(MEM_ACCESS_AP_WRITE | MEM_ACCESS_IAP_WRITE) == DRV_Success)
                if(MEM_GetAccessConfig(MEM_ACCESS_ISPD_WRITE | MEM_ACCESS_ISPD_READ) == DRV_Success) // ISP Mode
                if(MEM_GetAccessConfig(MEM_ACCESS_AP_WRITE | MEM_ACCESS_IAP_WRITE | MEM_ACCESS_ISPD_WRITE | MEM_ACCESS_ISPD_READ) == DRV_Success) //ISP Mode
                if(MEM_GetAccessConfig(MEM_ACCESS_ISP_READ | MEM_ACCESS_ISP_WRITE | MEM_ACCESS_ISPD_READ)) //ISP Mode Enable Warm-Reset to AP Mode or SRAM Mode
 * @endcode
 * @par         Modify
 *              DRV_Return MEM_GetAccessConfig(uint32_t MEM_ACCESS);
 *******************************************************************************
 */
DRV_Return MEM_GetAccessState(uint32_t MEM_ACCESS)
{
	if((MEM->CR1.W & MEM_ACCESS) == MEM_ACCESS)
	{
		return DRV_Success;
	}
	else
	{
		return DRV_Failure;
	}
}



/**
 *******************************************************************************
 * @brief       Flash Access Config
 * @details     
 *
 * @param[in]   MEM_ACCESS
 *  @arg\b      MEM_ACCESS_AP_WRITE    : AP memory write enable.
 *  @arg\b      MEM_ACCESS_IAP_EXECUTE : IAP data memory code execution function enable.
 *  @arg\b      MEM_ACCESS_IAP_WRITE   : IAP memory write enable.
 *  @arg\b      MEM_ACCESS_ISP_READ    : ISP memory read enable, Only On ISP mode enable this. 
 *  @arg\b      MEM_ACCESS_ISP_WRITE   : ISP memory write enable, Only On ISP mode enable this. 
 *  @arg\b      MEM_ACCESS_ISPD_READ   : ISPD memory read enable, Only On ISP mode enable this. 
 *  @arg\b      MEM_ACCESS_ISPD_WRITE  : ISPD memory write enable, Only On ISP mode enable this.  
 * @param[in]   State
 *  @arg\b      Enable          : Function Enable
 *  @arg\b      Disable         : Function Disable
 * @return      
 * @exception   None
 * @note        
 * @par         Example
 * @code
                MEM_Access_Cmd(MEM_ACCESS_IAP_EXECUTE, ENABLE) // Flash IAP data memory code execution function
                MEM_Access_Cmd(MEM_ACCESS_IAP_WRITE, ENABLE);
                MEM_Access_Cmd((MEM_ACCESS_AP_WRITE | MEM_ACCESS_IAP_WRITE), ENABLE);
                MEM_Access_Cmd((MEM_ACCESS_ISPD_READ | MEM_ACCESS_ISPD_WRITE), ENABLE); // ISP Mode
                MEM_Access_Cmd((MEM_ACCESS_AP_WRITE | MEM_ACCESS_IAP_WRITE | MEM_ACCESS_ISPD_WRITE | MEM_ACCESS_ISPD_READ), ENABLE); //ISP Mode
                MEM_Access_Cmd((MEM_ACCESS_ISP_READ | MEM_ACCESS_ISP_WRITE | MEM_ACCESS_ISPD_READ), ENABLE); //ISP Mode Enable Warm-Reset to AP Mode or SRAM Mode
 * @endcode
 * @par         Modify
 *              void MEM_Access_Cmd(uint32_t MEM_ACCESS, FunctionalState State)
 *******************************************************************************
 */
void MEM_Access_Cmd(uint32_t MEM_ACCESS, FunctionalState State)
{
    UnProtectModuleReg(MEMprotect);
	if(State==ENABLE)
	{
		MEM->CR1.W |= MEM_ACCESS;
	}
	else
	{
		MEM->CR1.W &= (~MEM_ACCESS);
	}
    ProtectModuleReg(MEMprotect);
}

///@}



/** 
 * @name    MEM Flash Read, Write and Execute Access
 *
 */ 
///@{

/**
 *******************************************************************************
 * @brief       Flash Write Access Mode Config
 * @details     Flash Page Erase
 *      \n      Flash Word Program
 * @param[in]   AccessMode
 *  @arg\b      None          : None Opration.
 *  @arg\b      APErase       : AP Flash Page Erase.
 *  @arg\b      APProgram     : AP Flash Word Program.
 *  @arg\b      IAPErase      : IAP Flash Page Erase.
 *  @arg\b      IAPProgram    : IAP Flash Word Program.
 *  @arg\b      ISPDErase     : ISPD Flash Page Erase.
 *  @arg\b      ISPDProgram   : ISPD Flash Word Program.
 *  @arg\b      ISPErase      : ISP Flash Page Erase.
 *  @arg\b      ISPProgram    : ISP Flash Word Program.
 * @return      
 * @exception   None
 * @note        
 * @par         Example
 * @code
                MEM_SetWriteMode(None);
                MEM_SetWriteMode(APErase);
                MEM_SetWriteMode(APProgram);
                MEM_SetWriteMode(IAPErase);
                MEM_SetWriteMode(IAPProgram);
                MEM_SetWriteMode(ISPDErase);
                MEM_SetWriteMode(ISPDProgram);
                MEM_SetWriteMode(ISPErase);
                MEM_SetWriteMode(ISPProgram);
 * @endcode
 * @par         Modify
 *              void MEM_SetWriteMode(MEMAccessMode AccessMode)
 *******************************************************************************
 */
void MEM_SetWriteMode(MEMAccessMode AccessMode)
{
    UnProtectModuleReg(MEMprotect);
    MEM->CR0.MBIT.MDS = (uint8_t) AccessMode;
    ProtectModuleReg(MEMprotect);
}

///@}



/** 
 * @name    AP / IAP / ISPD Write 
 *
 */ 
///@{

/**
 *******************************************************************************
 * @brief       Write UnProtect Sequential Key
 * @details     
 * @param[in]   SKEY
 *  @arg\b      APSingleSKey 	: AP Space Single Page Erase or Single Word Program
 *  @arg\b      APMultipleSKey: AP Space Multiple Page Erase or Multiple Word Program
 *  @arg\b      IAPSingleSKey : IAP Space Single Page Erase or Single Word Program
 *  @arg\b      IAPMultipleSKey : IAP Space Multiple Page Erase or Multiple Word Program
 *  @arg\b      ISPDSingleSKey : ISPD Space Single Page Erase or Single Word Program
 *  @arg\b      ISPDMultipleSKey : ISPD Space Multiple Page Erase or Multiple Word Program
 *  @arg\b      ISPSingleSKey : ISP Space Single Page Erase or Single Word Program
 *  @arg\b      ISPMultipleSKey : ISP Space Multiple Page Erase or Multiple Word Program
 * @return      
 * @exception   None
 * @note        
 * @par         Example
 * @code
                MEM_SetWriteUnProtect(IAPSingleSKey); // IAP Space Single Page Erase or Single Word Program
                MEM_SetWriteUnProtect(IAPMultipleSKey); // IAP Space Multiple Page Erase or Multiple Word Program
                MEM_SetWriteUnProtect(APSingleSKey); // AP Space Single Page Erase or Single Word Program
                MEM_SetWriteUnProtect(APMultipleSKey); // AP Space Multiple Page Erase or Multiple Word Program
                MEM_SetWriteUnProtect(ISPDSingleSKey); // ISPD Space Single Page Erase or Single Word Program
                MEM_SetWriteUnProtect(ISPDMultipleSKey); // ISPD Space Multiple Page Erase or Multiple Word Program
                MEM_SetWriteUnProtect(ISPSingleSKey); // ISP Space Single Page Erase or Single Word Program
                MEM_SetWriteUnProtect(ISPMultipleSKey); // ISP Space Multiple Page Erase or Multiple Word Program
 * @endcode
 * @par         Modify
 *              void MEM_SetWriteUnProtect(UnProtectSKey SKEY)
 *******************************************************************************
 */
void MEM_SetWriteUnProtect(UnProtectSKey SKEY)
{
    switch(SKEY)
    {
        case NoneSKey:
            MEM->SKEY.MBIT.SKEY = 0x00;
            MEM->SKEY.MBIT.SKEY = 0x00;
            MEM->SKEY.MBIT.SKEY2 = 0x0000;
            MEM->SKEY.MBIT.SKEY2 = 0x0000;
            break;

        case APSingleSKey:
        case APMultipleSKey:
            MEM->SKEY.MBIT.SKEY = 0x46;
            MEM->SKEY.MBIT.SKEY = (uint8_t) SKEY;
            break;

        case ISPSingleSKey:
        case ISPMultipleSKey:
            MEM->SKEY.MBIT.SKEY2 = 0x9867;
            MEM->SKEY.MBIT.SKEY2 = SKEY;
            break;
    }
}



/**
 *******************************************************************************
 * @brief       MEM Flash Single Page Erase Command
 * @details     
 * @return		
 * @exception   None
 * @note        
 * @par         Example
 * @code
                MEM_SetSinglePageEraseUnProtect();
 * @endcode
 * @par         Modify
 *              void MEM_SetSinglePageEraseUnProtect(void)
 *******************************************************************************
 */
void MEM_SetSinglePageEraseUnProtect(void)
{
    __MEM_UnProtect();
    __MEM_SetWriteMode(Erase);
    __MEM_SingleWriteUnProtect();
    __MEM_Protect();
}



/**
 *******************************************************************************
 * @brief       MEM Flash Multiple Page Erase Command
 * @details     
 * @return		
 * @exception   None
 * @note        
 * @par         Example
 * @code
                MEM_SetMultiplePageEraseUnProtect();
 * @endcode
 * @par         Modify
 *              void MEM_SetMultiplePageEraseUnProtect(void)
 *******************************************************************************
 */
void MEM_SetMultiplePageEraseUnProtect(void)
{
    __MEM_UnProtect();
    __MEM_SetWriteMode(Erase);
    __MEM_MultipleWriteUnProtect();
    __MEM_Protect();
}



/**
 *******************************************************************************
 * @brief       MEM Flash Single Program Command
 * @details     
 * @return		
 * @exception   None
 * @note        
 * @par         Example
 * @code
                MEM_SetSingleProgramUnProtect();
 * @endcode
 * @par         Modify
 *              void MEM_SetSingleProgramUnProtect(void)
 *******************************************************************************
 */
void MEM_SetSingleProgramUnProtect(void)
{
    __MEM_UnProtect();
    __MEM_SetWriteMode(Program);
    __MEM_SingleWriteUnProtect();
    __MEM_Protect();
}



/**
 *******************************************************************************
 * @brief       MEM Flash Multiple Program Command
 * @details     By AP / IAP / ISPD
 * @return		
 * @exception   None
 * @note        
 * @par         Example
 * @code
                MEM_SetMultipleProgramUnProtect();
 * @endcode
 * @par         Modify
 *              void MEM_SetMultipleProgramUnProtect(void)
 *******************************************************************************
 */
void MEM_SetMultipleProgramUnProtect(void)
{
    __MEM_UnProtect();
    __MEM_SetWriteMode(Program);
    __MEM_MultipleWriteUnProtect();
    __MEM_Protect();
}

///@}



/**
 *******************************************************************************
 * @brief       Flash Multiple Write Protect
 * @details     By AP / IAP / ISPD
 * @return		
 * @exception   None
 * @note        
 * @par         Example
 * @code        
                MEM_SetMultipleWriteProtect();
 * @endcode
 * @par         Modify
 *              void MEM_SetMultipleWriteProtect(void)
 *******************************************************************************
 */
void MEM_SetMultipleWriteProtect(void)
{
    __MEM_UnProtect();
    __MEM_UnProtect2();
    __MEM_MultipleWriteProtect();
    __MEM_Protect2();
    __MEM_Protect();
}



/** 
 * @name    AP Memory Write
 *
 */ 
///@{

/**
 *******************************************************************************
 * @brief       Flash AP memory write enable / disable.
 * @details     
 * @param[in]	State         : Enable / Disable
 *  @arg\b      ENABLE        : AP Flash Page Erase.
 *  @arg\b      DISABLE       : AP Flash Word Program.
 * @return      DRV_Success   : Set Write Enable Successful
 * @return      DRV_Failure   : Set Write Enable Failure
 * @exception   None
 * @note        
 * @par         Example
 * @code
                MEM_APWrite_Cmd(ENABLE); // AP Flash Write Page Erase and Program Enable
                MEM_APWrite_Cmd(DISABLE); // AP Flash Write Page Erase and Program Disable
 * @endcode
 * @par         Modify
 *              DRV_Return MEM_APWrite_Cmd(FunctionalState State)
 *******************************************************************************
 */
DRV_Return MEM_APWrite_Cmd(FunctionalState State)
{
    __MEM_UnProtect();
    __MEM_Enable();

    if(State == ENABLE)
    {
        __MEM_Access_Enable(MEM_ACCESS_AP_WRITE);

        if((__MEM_GetAccessState(MEM_ACCESS_AP_WRITE)) == CLR)
        {
            __MEM_Protect();
            return DRV_Failure;
        }
    }
    else
    {
        __MEM_Access_Disable(MEM_ACCESS_AP_WRITE);
    }
    __MEM_Protect();
    return DRV_Success;
}

///@}



/** 
 * @name    IAP Memory Size
 *
 */ 
///@{

/**
 *******************************************************************************
 * @brief       Get IAP Size
 * @details
 *
 * @return      uint32_t    :   IAP Memory Size (uint32_t)
 * @exception   None
 * @note        
 * @par         Example
 * @code
                gIAPSize = MEM_GetIAPSize();
 * @endcode
 * @par         Modify
 *              uint32_t MEM_GetIAPSize(void)
 *******************************************************************************
 */
uint32_t MEM_GetIAPSize(void)
{
    return ((uint32_t)(MEM->IAPSZ.H[0] << 2));
}



/**
 *******************************************************************************
 * @brief       Modify IAP Size 
 * @details
 *              Modify IAP memory size on MEM_IAP_SIZE register.
 *              This bit is only able to write value 1.
 *              That is on effect to write value 0. 
 *              (The register is loaded from CFG OR only after cold reset.)
 * @param[in]   IAPSize
 *  @arg\b      0K ~ N Byte : Step 1K.
 * @return      DRV_Failure : IAP Size Lock or Size Over
 * @return      DRV_Success : Set Successful
 * @exception   None
 * @note        
 * @par         Example
 * @code
                MEM_SetIAPSize(1024);  IAP Size 1KByte
                MEM_SetIAPSize(2048);  IAP Size 2KByte
                MEM_SetIAPSize(3072);  IAP Size 3KByte
                MEM_SetIAPSize(4096);  IAP Size 4KByte
                MEM_SetIAPSize(5120);  IAP Size 5KByte
                MEM_SetIAPSize(6144);  IAP Size 6KByte
                MEM_SetIAPSize(7168);  IAP Size 7KByte
                MEM_SetIAPSize(8192);  IAP Size 8KByte
 * @endcode
 * @par         Modify
 *              DRV_Return MEM_SetIAPSize(uint32_t MemSize)
 *******************************************************************************
 */
DRV_Return MEM_SetIAPSize(uint32_t IAPSize)
{
    uint32_t lTemp = (IAPSize >> 2);
    uint32_t lRegIAPSZ = MEM->IAPSZ.W;

    if(MEM->CR0.MBIT.IAP_AEN == 0)
        return (DRV_Failure);

  #if defined(MG32_1ST) || defined(MG32_2ND)
    if((IAPSize % 1024) != 0)
    {
        lTemp += 0x100;
    }
  #endif
  #if defined(MG32_3RD) || defined(MG32_4TH)
    if((IAPSize % 512) != 0)
    {
        lTemp += 0x100;
    }
  #endif
    MEM_ClearFlag(MEM_FLAG_IAPSEF);

    UnProtectModuleReg(MEMprotect);
    MEM->IAPSZ.W = lTemp;
    ProtectModuleReg(MEMprotect);

    if(MEM_GetFlagStatus(MEM_FLAG_IAPSEF) || (MEM_GetIAPSize() != (lTemp << 2)))
    {
        UnProtectModuleReg(MEMprotect);
        MEM->IAPSZ.W = lRegIAPSZ;
        ProtectModuleReg(MEMprotect);
        return (DRV_Failure);
    }
    return (DRV_Success);
}



/**
 *******************************************************************************
 * @brief       IAP Size Register Lock
 * @details
 *              IAP memory size MEM_IAP_SIZE register access disable.
 *              This bit is only able to write value 1.
 *              That is on effect to write value 0. 
 *              (The register is loaded from CFG OR only after cold reset.)
 * @return      DRV_Failure : Set Fail
 * @return      DRV_Success : Set Successful
 * @exception   None
 * @note        
 * @par         Example
 * @code
                MEM_SetIAPSizeLock();
                lTemp = MEM_SetIAPSizeLock();
                if(MEM_SetIAPSizeLock() != SUCCESS)
 * @endcode
 * @par         Modify
 *              DRV_Return MEM_SetIAPSizeLock(void)
 *******************************************************************************
 */
DRV_Return MEM_SetIAPSizeLock(void)
{
    UnProtectModuleReg(MEMprotect);
    MEM->CR0.MBIT.IAP_AEN = 0;
    ProtectModuleReg(MEMprotect);
    
    if(MEM->CR0.MBIT.IAP_AEN != 0)
        return (DRV_Failure);

    return (DRV_Success);
}

///@}



/** 
 * @name    IAP Code Execute
 *
 */ 
///@{

/**
 *******************************************************************************
 * @brief       Flash IAP data memory code execution function enable / disable.
 * @details     
 * @param[in]	State
 *  @arg\b      ENABLE : IAP Run Code
 *  @arg\b      DISABLE : IAP Data Mode
 * @return      DRV_Return
 *  @retval     DRV_Failure     : Set IAP code execution Failure
 *  @retval     DRV_Success     : Set IAP code execution Success
 * @exception   None
 * @note        
 * @par         Example
 * @code
                MEM_IAPExecuteCode_Cmd(ENABLE); // IAP Space Code Execute Function Enable
                MEM_IAPExecuteCode_Cmd(DISABLE); // IAP Space Code Execute Function Disable
 * @endcode
 * @par         Modify
 *              DRV_Return MEM_IAPExecuteCode_Cmd(FunctionalState State)
 *******************************************************************************
 */
DRV_Return MEM_IAPExecuteCode_Cmd(FunctionalState State)
{
    __MEM_UnProtect();
    __MEM_Enable();

    if(State == ENABLE)
    {
        __MEM_Access_Enable(MEM_ACCESS_IAP_EXECUTE);

        if((__MEM_GetAccessState(MEM_ACCESS_IAP_EXECUTE)) == CLR)
        {
            __MEM_Protect();
            return DRV_Failure;
        }
    }
    else
    {
        __MEM_Access_Disable(MEM_ACCESS_IAP_EXECUTE);
    }
    __MEM_Protect();
    return DRV_Success;
}

///@}




/** 
 * @name    IAP Write
 *
 */ 
///@{

/**
 *******************************************************************************
 * @brief       Flash IAP memory write enable / disable.
 * @details     
 * @param[in]	State
 *  @arg\b      ENABLE : IAP Write Enable
 *  @arg\b      DISABLE : IAP Write Disable
 * @return      DRV_Success   : Set Write Enable Successful
 * @return      DRV_Failure   : Set Write Enable Failure
 * @exception   None
 * @note        
 * @par         Example
 * @code
                MEM_IAPWrite_Cmd(ENABLE); // IAP Page Erase and Program Enable
                MEM_IAPWrite_Cmd(DISABLE); // IAP Page Erase and Program Enable
 * @endcode
 * @par         Modify
 *              DRV_Return MEM_IAPWrite_Cmd(FunctionalState State)
 *******************************************************************************
 */
DRV_Return MEM_IAPWrite_Cmd(FunctionalState State)
{
    __MEM_UnProtect();
    __MEM_Enable();

    if(State == ENABLE)
    {
        __MEM_Access_Enable(MEM_ACCESS_IAP_WRITE);

        if((__MEM_GetAccessState(MEM_ACCESS_IAP_WRITE)) == CLR)
        {
            __MEM_Protect();
            return DRV_Failure;
        }
    }
    else
    {
        __MEM_Access_Disable(MEM_ACCESS_IAP_WRITE);
    }
    __MEM_Protect();
    return DRV_Success;
}

///@}




/** 
 * @name    ISPD Read and Write
 *
 */ 
///@{

/**
 *******************************************************************************
 * @brief       Flash ISPD data memory read enable / disable for ISPD program. 
 * @details     This register is only able to set when boots from ISPD mode.
 *              And it can clear or disable for all boot modes.
 * @param[in]	State
 *  @arg\b      ENABLE : ISPD Read Enable
 *  @arg\b      DISABLE : ISPD Write and Read Disable
 * @return      DRV_Success   : Set Read Enable Successful
 * @return      DRV_Failure   : Set Read Enable Failure
 * @exception   This register is only able to change when boots from ISP mode.
 * @note        
 * @par         Example
 * @code
                MEM_ISPDRead_Cmd(ENABLE); // ISPD Flash Space Read Enable
                MEM_ISPDRead_Cmd(DISABLE); // ISPD Flash Space Read and Write Disable
 * @endcode
 * @par         Modify
 *              DRV_Return MEM_ISPDRead_Cmd(FunctionalState State)
 *******************************************************************************
 */
DRV_Return MEM_ISPDRead_Cmd(FunctionalState State)
{
    __MEM_UnProtect();
    __MEM_Enable();

    if(State == ENABLE)
    {
        __MEM_Access_Enable(MEM_ACCESS_ISPD_READ);

        if((__MEM_GetAccessState(MEM_ACCESS_ISPD_READ)) == CLR)
        {
            __MEM_Protect();
            return DRV_Failure;
        }
    }
    else
    {
        __MEM_Access_Disable(MEM_ACCESS_ISPD_READ);
    }
    __MEM_Protect();
    return DRV_Success;
}



/**
 *******************************************************************************
 * @brief       Flash ISP data memory write enable / disable for ISP program. 
 * @details     This register is only able to change when boots from ISP mode.
 * @param[in]	State
 *  @arg\b      ENABLE : ISPD Write and Read Enable
 *  @arg\b      DISABLE : ISPD Write Disable
 * @return      DRV_Success   : Set Write Enable Successful
 * @return      DRV_Failure   : Set Write Enable Failure
 * @exception   This register is only able to change when boots from ISP mode.
 * @note        
 * @par         Example
 * @code
                MEM_ISPDWrite_Cmd(ENABLE); // ISPD Write and Read Enable
                MEM_ISPDWrite_Cmd(DISABLE); // ISPD Write Disable
 * @endcode
 * @par         Modify
 *              DRV_Return MEM_ISPDWrite_Cmd(FunctionalState State)
 *******************************************************************************
 */
DRV_Return MEM_ISPDWrite_Cmd(FunctionalState State)
{
    __MEM_UnProtect();
    __MEM_Enable();

    if(State == ENABLE)
    {
        __MEM_Access_Enable(MEM_ACCESS_ISPD_WRITE);

        if((__MEM_GetAccessState(MEM_ACCESS_ISPD_WRITE)) == CLR)
        {
            __MEM_Protect();
            return DRV_Failure;
        }
    }
    else
    {
        __MEM_Access_Disable(MEM_ACCESS_ISPD_WRITE);
    }
    __MEM_Protect();
    return DRV_Success;
}

///@}



/** 
 * @name    ISP Read and Write
 *
 */ 
///@{

/**
 *******************************************************************************
 * @brief       Get ISP Size
 * @details
 *
 * @return		uint32_t    :   ISP Memory Size (uint32_t)
 * @exception   None
 * @note        
 * @par         Example
 * @code
                gISPSize = MEM_GetISPSize();    
 * @endcode
 * @par         Modify
 *              uint32_t MEM_GetISPSize(void)
 *******************************************************************************
 */
uint32_t MEM_GetISPSize(void)
{
    return ((uint32_t)(CFG->OR02.B[1] * 1024));
}



/**
 *******************************************************************************
 * @brief       Flash ISP Boot memory read enable / disable for AP program. 
 * @details     (This register is protected by MEM_KEY2 register.) 
 *              The ISP flash memory is always reading enabled when CPU is running in ISP program (ISP address space domain). 
 *              This register is only able to set when boots from ISP mode. And it can clear or disable for all boot modes.
 * @param[in]	State
 *  @arg\b      ENABLE      : ISP Read Enable
 *  @arg\b      DISABLE     : ISP Read Disable
 * @return      DRV_Success : Set Read Enable Successful
 * @return      DRV_Failure : Set Read Enable Failure
 * @exception   This register is only able to change when boots from ISP mode.
 *      \n      Operating on Not ISP mode
 * @note        
 * @par         Example
 * @code
                MEM_ISPRead_Cmd(ENABLE); // ISP Flash Write Page Erase and Program, and Read Enable
                MEM_ISPRead_Cmd(DISABLE); // ISP Flash Write Page Erase and Program Disable
 * @endcode
 * @par         Modify
 *              DRV_Return MEM_ISPRead_Cmd(FunctionalState State)
 *******************************************************************************
 */
DRV_Return MEM_ISPRead_Cmd(FunctionalState State)
{
    __MEM_UnProtect();
    __MEM_Enable();

    if(State == ENABLE)
    {
        __MEM_Access_Enable(MEM_ACCESS_ISP_READ);

        if((__MEM_GetAccessState(MEM_ACCESS_ISP_READ)) == CLR)
        {
            __MEM_Protect();
            return DRV_Failure;
        }
    }
    else
    {
        __MEM_Access_Disable(MEM_ACCESS_ISP_READ);
    }
    __MEM_Protect();
    return DRV_Success;
}



/**
 *******************************************************************************
 * @brief       Flash ISP Boot memory write enable / disable.
 * @details     (This register is protected by MEM_KEY2 register.)  
 *              This register is only able to set when boots from ISP mode. 
 *              And it can clear or disable for all boot modes.
 * @param[in]	State
 *  @arg\b      ENABLE      : ISP Write and Read Enable
 *  @arg\b      DISABLE     : ISP Write Disable
 * @return      DRV_Success : Set Write Enable Successful
 * @return      DRV_Failure : Set Write Enable Failure
 * @exception   This register is only able to change when boots from ISP mode.
 *      \n      Operating on Not ISP mode
 * @note        
 * @par         Example
 * @code
                MEM_ISPWrite_Cmd(ENABLE); // ISP Flash Space Write and Read Enable.
                MEM_ISPWrite_Cmd(DISABLE); // ISP Flash Space Write Disable.
 * @endcode
 * @par         Modify
 *              DRV_Return MEM_ISPWrite_Cmd(FunctionalState State)
 *******************************************************************************
 */
DRV_Return MEM_ISPWrite_Cmd(FunctionalState State)
{
    __MEM_UnProtect();
    __MEM_Enable();

    if(State == ENABLE)
    {
        __MEM_Access_Enable(MEM_ACCESS_ISP_WRITE);

        if((__MEM_GetAccessState(MEM_ACCESS_ISP_WRITE)) == CLR)
        {
            __MEM_Protect();
            return DRV_Failure;
        }
    }
    else
    {
        __MEM_Access_Disable(MEM_ACCESS_ISP_WRITE);
    }
    __MEM_Protect();
    return DRV_Success;
}



/**
 *******************************************************************************
 * @brief       MEM ISP Flash Single Page Erase UnProtect
 * @details     
 * @return		
 * @exception   None
 * @note        
 * @par         Example
 * @code
                MEM_SetISPSinglePageEraseUnProtect();
 * @endcode
 * @par         Modify
 *              void MEM_SetISPSinglePageEraseUnProtect(void)
 *******************************************************************************
 */
void MEM_SetISPSinglePageEraseUnProtect(void)
{
    __MEM_UnProtect();
    __MEM_Access_Enable(MEM_ACCESS_ISP_READ | MEM_ACCESS_ISP_WRITE);
    __MEM_SetWriteMode(ISPErase);
    __MEM_UnProtect2();
    __MEM_ISPSingleWriteUnProtect();
    __MEM_UnProtect2();
    __MEM_Protect();
}



/**
 *******************************************************************************
 * @brief       MEM ISP Flash Multiple Page Erase UnProtect
 * @details     
 * @return		
 * @exception   None
 * @note        
 * @par         Example
 * @code
                MEM_SetISPMultiplePageEraseUnProtect();
 * @endcode
 * @par         Modify
 *              void MEM_SetISPMultiplePageEraseUnProtect(void)
 *******************************************************************************
 */
void MEM_SetISPMultiplePageEraseUnProtect(void)
{
    __MEM_UnProtect();
    __MEM_Access_Enable(MEM_ACCESS_ISP_READ | MEM_ACCESS_ISP_WRITE);
    __MEM_SetWriteMode(ISPErase);
    __MEM_UnProtect2();
    __MEM_ISPMultipleWriteUnProtect();
    __MEM_UnProtect2();
    __MEM_Protect();
}



/**
 *******************************************************************************
 * @brief       ISP Flash Single Program UnProtect
 * @details     
 * @return		
 * @exception   None
 * @note        
 * @par         Example
 * @code
                MEM_SetISPSingleProgramUnProtect();
 * @endcode
 * @par         Modify
 *              void MEM_SetISPSingleProgramUnProtect(void)
 *******************************************************************************
 */
void MEM_SetISPSingleProgramUnProtect(void)
{
    __MEM_UnProtect();
    __MEM_Access_Enable(MEM_ACCESS_ISP_READ | MEM_ACCESS_ISP_WRITE);
    __MEM_SetWriteMode(ISPProgram);
    __MEM_UnProtect2();
    __MEM_ISPSingleWriteUnProtect();
    __MEM_UnProtect2();
    __MEM_Protect();
}

/**
 *******************************************************************************
 * @brief       ISP Flash Multiple Program UnProtect
 * @details     
 * @return		
 * @exception   None
 * @note        
 * @par         Example
 * @code
                MEM_SetISPMultipleProgramUnProtect();
 * @endcode
 * @par         Modify
 *              void MEM_SetISPMultipleProgramUnProtect(void)
 *******************************************************************************
 */
void MEM_SetISPMultipleProgramUnProtect(void)
{
    __MEM_UnProtect();
    __MEM_Access_Enable(MEM_ACCESS_ISP_READ | MEM_ACCESS_ISP_WRITE);
    __MEM_SetWriteMode(ISPProgram);
    __MEM_UnProtect2();
    __MEM_ISPMultipleWriteUnProtect();
    __MEM_Protect2();
    __MEM_Protect();
}



/**
 *******************************************************************************
 * @brief       ISP Flash Multiple Write Protect
 * @details     
 * @return		
 * @exception   None
 * @note        
 * @par         Example
 * @code
                MEM_SetISPMultipleWriteProtect();
 * @endcode
 * @par         Modify
 *              void MEM_SetISPMultipleWriteProtect(void)
 *******************************************************************************
 */
void MEM_SetISPMultipleWriteProtect(void)
{
    __MEM_UnProtect();
    __MEM_UnProtect2();
    __MEM_ISPMultipleWriteProtect();
    __MEM_Protect2();
    __MEM_Protect();
}

///@}

