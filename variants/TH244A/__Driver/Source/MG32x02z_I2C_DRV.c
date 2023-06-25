/**
 ******************************************************************************
 *
 * @file        MG32x02z_I2C_DRV.c
 *
 * @brief       This is the C code format driver file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V2.11
 * @date        2021/09/07
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************
 * @par         Disclaimer 
 *      The Demo software is provided "AS IS" without any warranty, either
 *      expressed or implied, including, but not limited to, the implied warranties
 *      of merchantability and fitness for a particular purpose.  The author will
 *      not be liable for any special, incidental, consequential or indirect
 *      damages due to loss of data or any other reason.
 *      These statements agree with the world wide and local dictated laws about
 *      authorship and violence against these laws.
 ******************************************************************************
 ******************************************************************************
 */



#include "MG32x02z_I2C_DRV.h"



/**
 * @name    Clock
 *          Clock Setting
 */
///@{

/**
 *******************************************************************************
 * @brief       I2C Clock Source Config
 * @details     I2C internal clock CK_I2C source select.
 *              
 * @param[in]   I2Cx : where x can be 0 and 1 to select the I2C peripheral.
 * @param[in]   Select : I2C internal clock CK_I2C source.
 *   @arg\b     I2C_ClockSource_PROC : (Default)
 *   @arg\b     I2C_ClockSource_TM00_TROG : 
 * @return      No
 * @exception   None
 * @note        
 * @par         Example
 * @code        
                I2C_SetClockSource(I2C0, I2C_CLK_SRC_PROC);
                I2C_SetClockSource(I2C0, I2C_CLK_SRC_TM00_TROG);
                I2C_SetClockSource(I2C1, I2C_CLK_SRC_PROC);
                I2C_SetClockSource(I2C1, I2C_CLK_SRC_TM00_TROG);
 * @endcode     
 * @par         Modify
 *              void I2C_SetClockSource(I2C_Struct* I2Cx, uint8_t Select);
 *******************************************************************************
 */
void I2C_SetClockSource(I2C_Struct* I2Cx, uint8_t Select)
{
    I2Cx->CLK.B[1] = ((I2Cx->CLK.B[1] & (~I2C_CLK_SRC_MASK)) | Select);
}



/**
 *******************************************************************************
 * @brief       I2C Set Clock Devider
 * @details     I2C internal clock CK_I2C_INT prescaler. 
 *              The value range 0~7 is indicated divider 1~8.
 *              
 * @param[in]   I2Cx : where x can be 0 and 1 to select the I2C peripheral.
 * @param[in]   Select : 
 *   @arg\b     I2C_CLK_PSC_0 : (Default)
 *   @arg\b     I2C_CLK_PSC_1 :
 *   @arg\b     I2C_CLK_PSC_2 :
 *   @arg\b     I2C_CLK_PSC_3 :
 *   @arg\b     I2C_CLK_PSC_4 :
 *   @arg\b     I2C_CLK_PSC_5 :
 *   @arg\b     I2C_CLK_PSC_6 :
 *   @arg\b     I2C_CLK_PSC_7 :
 * @return      No
 * @exception   None
 * @note        
 * @par         Example
 * @code        
                I2C_SetClockPrescaler(I2C0, I2C_CLK_PSC_1);
                I2C_SetClockPrescaler(I2C0, I2C_CLK_PSC_4);
                I2C_SetClockPrescaler(I2C0, I2C_CLK_PSC_5);
                I2C_SetClockPrescaler(I2C0, I2C_CLK_PSC_8);
                I2C_SetClockPrescaler(I2C1, I2C_CLK_PSC_1);
                I2C_SetClockPrescaler(I2C1, I2C_CLK_PSC_4);
                I2C_SetClockPrescaler(I2C1, I2C_CLK_PSC_5);
                I2C_SetClockPrescaler(I2C1, I2C_CLK_PSC_8);
 * @endcode     
 * @par         Modify
 *              void I2C_SetClockPrescaler(I2C_Struct* I2Cx, uint8_t Select);
 *******************************************************************************
 */
void I2C_SetClockPrescaler(I2C_Struct* I2Cx, uint8_t Select)
{
    I2Cx->CLK.B[1] = ((I2Cx->CLK.B[1] & (~I2C_CLK_PSC_MASK)) | Select);
}



/**
 *******************************************************************************
 * @brief       I2C Set Clock Devider
 * @details     I2C internal clock CK_I2C_INT input divider.
 *              CK_I2C_INT frequency = (I2C_CK_PSC+1) * (I2C_CK_DIV)
 *              
 * @param[in]   I2Cx : where x can be 0 and 1 to select the I2C peripheral.
 * @param[in]   Select : 
 *   @arg\b     I2C_CLK_DIV_1 : (Default)
 *   @arg\b     I2C_CLK_DIV_2 : 
 *   @arg\b     I2C_CLK_DIV_4 : 
 *   @arg\b     I2C_CLK_DIV_8 : 
 *   @arg\b     I2C_CLK_DIV_16 : No support MG32F02A132/072
 *   @arg\b     I2C_CLK_DIV_32 : No support MG32F02A132/072
 *   @arg\b     I2C_CLK_DIV_64 : No support MG32F02A132/072
 *   @arg\b     I2C_CLK_DIV_128 : No support MG32F02A132/072
 * @return      No
 * @exception   None
 * @note        
 * @par         Example
 * @code        
                I2C_SetClockDivider(I2C0, I2C_CLK_DIV_1);
                I2C_SetClockDivider(I2C0, I2C_CLK_DIV_4);
                I2C_SetClockDivider(I2C0, I2C_CLK_DIV_8);
                I2C_SetClockDivider(I2C0, I2C_CLK_DIV_16);
                I2C_SetClockDivider(I2C1, I2C_CLK_DIV_1);
                I2C_SetClockDivider(I2C1, I2C_CLK_DIV_4);
                I2C_SetClockDivider(I2C1, I2C_CLK_DIV_8);
                I2C_SetClockDivider(I2C1, I2C_CLK_DIV_16);
 * @endcode     
 * @par         Modify
 *              void I2C_SetClockDivider(I2C_Struct* I2Cx, uint8_t Select);
 *******************************************************************************
 */
void I2C_SetClockDivider(I2C_Struct* I2Cx, uint8_t Select)
{
    I2Cx->CLK.B[0] = (I2Cx->CLK.B[0] & (~I2C_CLK_DIV_MASK)) | (Select & I2C_CLK_DIV_MASK);
}



/**
 *******************************************************************************
 * @brief       Set SCL High cycle Time
 * @details     I2C SCL high cycle time by CK_I2C_INT clock time.
 *              It write setting value for master mode. 
 *              (SCL High time = START hold time = STOP setup time)
 *              
 * @param[in]   I2Cx : where x can be 0 and 1 to select the I2C peripheral.
 * @param[in]   HighTime : address value 0 ~ 31. (Default 5).
 * @return      No
 * @exception   None
 * @note        
 * @par         Example
 * @code        
                I2C_SetSCLHighTime(I2C0, 5);
                I2C_SetSCLHighTime(I2C1, 5);
                I2C_SetSCLHighTime(I2C0, 15);
                I2C_SetSCLHighTime(I2C1, 15);
 * @endcode     
 * @par         Modify
 *              void I2C_SetSCLHighTime(I2C_Struct* I2Cx, uint8_t HighTime);
 *******************************************************************************
 */
void I2C_SetSCLHighTime(I2C_Struct* I2Cx, uint8_t HighTime)
{
    I2Cx->CR1.B[1] = HighTime;
}



/**
 *******************************************************************************
 * @brief       Set SCL Low cycle Time
 * @details     I2C SCL low cycle time by CK_I2C_INT clock time.
 *              It write setting value for master mode. 
 *              (SCL Low time = START setup time = Bus free time between STOP
 *              and START)
 *              
 * @param[in]   I2Cx : where x can be 0 and 1 to select the I2C peripheral.
 * @param[in]   LowTime : address value 0 ~ 31. (Default 4).
 * @return      No
 * @exception   None
 * @note        
 * @par         Example
 * @code        
                I2C_SetSCLLowTime(I2C0, 4);
                I2C_SetSCLLowTime(I2C1, 4);
                I2C_SetSCLLowTime(I2C0, 15);
                I2C_SetSCLLowTime(I2C1, 15);
 * @endcode     
 * @par         Modify
 *              void I2C_SetSCLLowTime(I2C_Struct* I2Cx, uint8_t LowTime);
 *******************************************************************************
 */
void I2C_SetSCLLowTime(I2C_Struct* I2Cx, uint8_t LowTime)
{
    I2Cx->CR1.B[0] = LowTime;
}



/**
 *******************************************************************************
 * @brief       I2C Set PreDrive Time
 * @details     I2C pre-drive time select for both SCL and SDA by CK_I2C clock
 *              time.
 *              
 * @param[in]   I2Cx : where x can be 0 and 1 to select the I2C peripheral.
 * @param[in]   Select : 
 *   @arg\b     I2C_PDRV_0T : 0t CK_I2C Ckcok (disable pre-drive) (Default)
 *   @arg\b     I2C_PDRV_1T : 1t CK_I2C Ckcok 
 *   @arg\b     I2C_PDRV_2T : 2t CK_I2C Ckcok 
 *   @arg\b     I2C_PDRV_3T : 3t CK_I2C Ckcok 
 * @return      No
 * @exception   None
 * @note        
 * @par         Example
 * @code        
                I2C_SetPreDriveTime(I2C0, I2C_PDRV_0T);
                I2C_SetPreDriveTime(I2C0, I2C_PDRV_1T);
                I2C_SetPreDriveTime(I2C0, I2C_PDRV_2T);
                I2C_SetPreDriveTime(I2C0, I2C_PDRV_3T);
                I2C_SetPreDriveTime(I2C1, I2C_PDRV_0T);
                I2C_SetPreDriveTime(I2C1, I2C_PDRV_1T);
                I2C_SetPreDriveTime(I2C1, I2C_PDRV_2T);
                I2C_SetPreDriveTime(I2C1, I2C_PDRV_3T);
 * @endcode     
 * @par         Modify
 *              void I2C_SetPreDriveTime(I2C_Struct* I2Cx, uint32_t Select);
 *******************************************************************************
 */
void I2C_SetPreDriveTime(I2C_Struct* I2Cx, uint32_t Select)
{
    I2Cx->CR0.B[1] = (I2Cx->CR0.B[1] & (~I2C_PDRV_MASK)) | (Select & I2C_PDRV_MASK);
}

///@}



/**
 * @name    Mode
 *          Operation Mode Setting
 */ 
///@{

/**
 *******************************************************************************
 * @brief       I2C general call address 0x00 recognized Enable / Disable.
 * @details     I2C general call address 0x00 recognized Enable / Disable.
 *              
 * @param[in]   I2Cx : where x can be 0 and 1 to select the I2C peripheral.
 * @param[in]   State : 
 *   @arg\b     ENABLE : 
 *   @arg\b     DISABLE : 
 * @return      No
 * @exception   None
 * @note        
 * @par         Example
 * @code        
                I2C_GeneralCallAddress_Cmd(I2C0, ENABLE);
                I2C_GeneralCallAddress_Cmd(I2C0, DISABLE);
                I2C_GeneralCallAddress_Cmd(I2C1, ENABLE);
                I2C_GeneralCallAddress_Cmd(I2C1, DISABLE);
 * @endcode     
 * @par         Modify
 *              void I2C_GeneralCallAddress_Cmd(I2C_Struct* I2Cx, FunctionalState State);
 *******************************************************************************
 */
void I2C_GeneralCallAddress_Cmd(I2C_Struct* I2Cx, FunctionalState State)
{
    if(State == ENABLE)
        I2Cx->CR0.B[0] |= I2C_CR0_GC_EN_enable_b0;
    else
        I2Cx->CR0.B[0] &= (~I2C_CR0_GC_EN_mask_b0);
}



/**
 *******************************************************************************
 * @brief       I2C Slave Address Detect Enable / Disable
 * @details     I2C slave mode slave address detect enable.
 *              When enables , the I2C slave address I2C_SADR is not allowed to
 *              be updated.
 *              
 * @param[in]   I2Cx : where x can be 0 and 1 to select the I2C peripheral.
 * @param[in]   I2C_SADRx : where x can be 1 and 2 to select the I2C Slave Address.
 *   @arg\b     I2C_SADR_0 : Slave Address Detect general call address 0x00  Enable / Disable.
 *   @arg\b     I2C_SADR_1 : Slave Address Detect SADR Enable / Disable.
 *   @arg\b     I2C_SADR_2 : Slave Address Detect SADR2 Enable / Disable.
 * @param[in]   State : 
 *   @arg\b     ENABLE : Slave Address Detect Enable
 *   @arg\b     DISABLE : Slave Address Detect Disable. (Default)
 * @return      No
 * @exception   None
 * @note        
 * @par         Example
 * @code        
                I2C_SlaveAddressDetect_Cmd(I2C0, I2C_SADR_0, ENABLE);
                I2C_SlaveAddressDetect_Cmd(I2C0, I2C_SADR_0, DISABLE);
                I2C_SlaveAddressDetect_Cmd(I2C0, I2C_SADR_1, ENABLE);
                I2C_SlaveAddressDetect_Cmd(I2C0, I2C_SADR_1, DISABLE);
                I2C_SlaveAddressDetect_Cmd(I2C0, I2C_SADR_2, ENABLE);
                I2C_SlaveAddressDetect_Cmd(I2C0, I2C_SADR_2, DISABLE);
                I2C_SlaveAddressDetect_Cmd(I2C0, (I2C_SADR_0 | I2C_SADR_1), ENABLE);
                I2C_SlaveAddressDetect_Cmd(I2C0, (I2C_SADR_0 | I2C_SADR_1), DISABLE);
                I2C_SlaveAddressDetect_Cmd(I2C0, (I2C_SADR_0 | I2C_SADR_1 | I2C_SADR_2), ENABLE);
                I2C_SlaveAddressDetect_Cmd(I2C0, (I2C_SADR_0 | I2C_SADR_1 | I2C_SADR_2), DISABLE);
 * @endcode     
 * @par         Modify
 *              void I2C_2ndSlaveAddress_Cmd(I2C_Struct* I2Cx, FunctionalState State);
 *******************************************************************************
 */
void I2C_SlaveAddressDetect_Cmd(I2C_Struct* I2Cx, uint8_t I2C_SADRx, FunctionalState State)
{
    if(State == ENABLE)
        I2Cx->CR0.B[0] |= I2C_SADRx;
    else
        I2Cx->CR0.B[0] &= (~I2C_SADRx);
}



/**
 *******************************************************************************
 * @brief       Set Slave Address
 * @details     I2C slave mode slave address detection request address value.
 *              Address 0x00 ~ 0x7F.
 *              
 * @param[in]   I2Cx : where x can be 0 and 1 to select the I2C peripheral.
 * @param[in]   I2C_SADRx : where x can be 1 and 2 to select the I2C Slave Address.
 *   @arg\b     I2C_SADR_0 : Slave Address Detect general call address 0x00  Enable / Disable.
 *   @arg\b     I2C_SADR_1 : Slave Address Detect SADR Enable / Disable.
 *   @arg\b     I2C_SADR_2 : Slave Address Detect SADR2 Enable / Disable.
 * @param[in]   Address : address value 0x00 ~ 0xFE. (Default 0x00).
 * @return      No
 * @exception   None
 * @note        
 * @par         Example
 * @code        
                I2C_SetSlaveAddress(I2C0, I2C_SADR_1, SlaveAddress);
                I2C_SetSlaveAddress(I2C0, I2C_SADR_2, SlaveAddress2);
                I2C_SetSlaveAddress(I2C1, I2C_SADR_1, SlaveAddress);
                I2C_SetSlaveAddress(I2C1, I2C_SADR_2, SlaveAddress2);
 * @endcode     
 * @par         Modify
 *              void I2C_SetSlaveAddress(I2C_Struct* I2Cx, uint8_t I2C_SADRx, uint8_t Address);
 *******************************************************************************
 */
void I2C_SetSlaveAddress(I2C_Struct* I2Cx, uint8_t I2C_SADRx, uint8_t Address)
{
    if(I2C_SADRx == I2C_SADR_1)
        I2Cx->SADR.B[0] = Address;

    if(I2C_SADRx == I2C_SADR_2)
        I2Cx->SADR.B[1] = Address;
}



#if !defined(MG32_1ST)
/**
 *******************************************************************************
 * @brief       Set Own Slave Address1 Mask
 * @details     I2C slave mode slave address detection request address value.
 *              Address 0x00 ~ 0xFE. Bit0 Don't Care.
 *              
 * @param[in]   I2Cx : where x can be 0 and 1 to select the I2C peripheral.
 * @param[in]   I2C_SlaveAddress1Mask : Mask value 0x00 ~ 0xFE. (Default 0xFE).
 * @return      No
 * @exception   None
 * @note        
 *              Function Not Support Device
 *     \n       MG32F02A132 Not Support
 *     \n       MG32F02A072 Not Support
 *     \n       MA862 Not Support
 * @par         Example
 * @code        
                I2C_SetSlaveAddress1Mask(I2C0, 0xFE); // Compare Address Bit All 
                I2C_SetSlaveAddress1Mask(I2C1, 0xFE); // Compare Address Bit All 
 * @endcode     
 * @par         Modify
 *              void I2C_SetSlaveAddress1Mask(I2C_Struct* I2Cx, uint8_t I2C_SlaveAddress1Mask);
 *******************************************************************************
 */
void I2C_SetSlaveAddress1Mask(I2C_Struct* I2Cx, uint8_t I2C_SlaveAddress1Mask) 
{
    I2Cx->MASK.B[0] = I2C_SlaveAddress1Mask;
}
#endif



/**
 *******************************************************************************
 * @brief       Get Slave Address
 * @details     I2C slave mode slave address detection request address value.
 *              Address 0x00 ~ 0x7F.
 *              
 * @param[in]   I2Cx : where x can be 0 and 1 to select the I2C peripheral.
 * @param[in]   I2C_SADRx : where x can be 1 and 2 to select the I2C Slave Address.
 *   @arg\b     I2C_SADR_0 : Slave Address Detect general call address 0x00  Enable / Disable.
 *   @arg\b     I2C_SADR_1 : Slave Address Detect SADR Enable / Disable.
 *   @arg\b     I2C_SADR_2 : Slave Address Detect SADR2 Enable / Disable.
 * @return      uint8_t : Address. address value 0x00 ~ 0xFE. bit0 always "0".
 * @exception   None
 * @note        
 * @par         Example
 * @code        
                uint8_t AddrTemp = I2C_GetSlaveAddress(I2C0, I2C_SADR_0);
                uint8_t AddrTemp = I2C_GetSlaveAddress(I2C0, I2C_SADR_1);
                uint8_t AddrTemp = I2C_GetSlaveAddress(I2C0, I2C_SADR_2);
                uint8_t AddrTemp = I2C_GetSlaveAddress(I2C1, I2C_SADR_0);
                uint8_t AddrTemp = I2C_GetSlaveAddress(I2C1, I2C_SADR_1);
                uint8_t AddrTemp = I2C_GetSlaveAddress(I2C1, I2C_SADR_2);
 * @endcode     
 * @par         Modify
 *              uint8_t I2C_GetSlaveAddress(I2C_Struct* I2Cx, uint8_t I2C_SADRx);
 *******************************************************************************
 */
uint8_t I2C_GetSlaveAddress(I2C_Struct* I2Cx, uint8_t I2C_SADRx)
{
    if(I2C_SADRx == I2C_SADR_0)
        return 0x00;

    if(I2C_SADRx == I2C_SADR_1)
        return (I2Cx->SADR.B[0] & 0xFE);

    if(I2C_SADRx == I2C_SADR_2)
        return (I2Cx->SADR.B[1] & 0xFE);

    return 0xFF;
}



/**
 *******************************************************************************
 * @brief       Controller I2C Function Enable.
 * @details     I2C function enable bit. 
 *              When disables, the I2C_SCL and I2C_SDA pin state are switched 
 *              to data port state.
 *              
 * @param[in]   I2Cx : where x can be 0 and 1 to select the I2C peripheral.
 * @param[in]   State
 *  @arg\b      ENABLE          : Function Enable.
 *  @arg\b      DISABLE         : Function Disable. (Default)
 * @return      No
 * @exception   None
 * @note        
 * @par         Example
 * @code
                I2C_Cmd(I2C0, ENABLE);
                I2C_Cmd(I2C0, DISABLE);
                I2C_Cmd(I2C1, ENABLE);
                I2C_Cmd(I2C1, DISABLE);
 * @endcode     
 * @par         Modify
 *              void I2C_Cmd(I2C_Struct* I2Cx, FunctionalState State);
 *******************************************************************************
 */
void I2C_Cmd(I2C_Struct* I2Cx, FunctionalState State)
{
    if(State == ENABLE)
        I2Cx->CR0.B[0] |= I2C_CR0_EN_enable_b0;
    else
        I2Cx->CR0.B[0] &= (~I2C_CR0_EN_mask_b0);
}

///@}



/**
 * @name   DMA
           I2C DMA relationship driver.
 */
///@{

/**
 *******************************************************************************
 * @brief       I2C DMA TX function disable or enable.
 * @details     
 * @param[in]   I2Cx:
 *  @arg\b      I2C0: I2C0 relationship control.
 *  @arg\b      I2C1: I2C1 relationship control.
 * @param[in]   State:
 *  @arg\b      DISABLE: Disable DMA TX function.
 *  @arg\b      ENABLE : Enable DMA TX function.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
                I2C_TXDMA_Cmd( I2C0, ENABLE);
                I2C_TXDMA_Cmd( I2C1, ENABLE);
                I2C_TXDMA_Cmd( I2C0, DISABLE);
                I2C_TXDMA_Cmd( I2C1, DISABLE);
 * @endcode
 * @par         Modify
 *              void I2C_TXDMA_Cmd(I2C_Struct* I2Cx, FunctionalState State)
 *******************************************************************************
 */
void I2C_TXDMA_Cmd(I2C_Struct* I2Cx, FunctionalState State)
{
    if(State == ENABLE)
        I2Cx->CR0.B[3] |= I2C_CR0_DMA_TXEN_mask_b3;
    else
        I2Cx->CR0.B[3] &= ~I2C_CR0_DMA_TXEN_mask_b3;
}



/**
 *******************************************************************************
 * @brief       I2C DMA RX function disable or enable.
 * @details     
 * @param[in]   I2Cx:
 *  @arg\b      I2C0: I2C0 relationship control.
 *  @arg\b      I2C1: I2C1 relationship control.
 * @param[in]   State:
 *  @arg\b      DISABLE: Disable DMA RX function.
 *  @arg\b      ENABLE : Enable DMA RX function.
 * @return      
 * @exception   No
 * @note 
 * @par         Example
 * @code
                I2C_RXDMA_Cmd(I2C0, ENABLE);
                I2C_RXDMA_Cmd(I2C1, ENABLE);
                I2C_RXDMA_Cmd(I2C0, DISABLE);
                I2C_RXDMA_Cmd(I2C1, DISABLE);
 * @endcode
 * @par         Modify
 *              void I2C_RXDMA_Cmd(I2C_Struct* I2Cx, FunctionalState State)
 *******************************************************************************
 */
void I2C_RXDMA_Cmd(I2C_Struct* I2Cx, FunctionalState State)
{
    if(State == ENABLE)
        I2Cx->CR0.B[3] |= I2C_CR0_DMA_RXEN_mask_b3;
    else
        I2Cx->CR0.B[3] &= (~I2C_CR0_DMA_RXEN_mask_b3);
}

///@}



/**
 * @name    Interript & Event
 *          Interript and Event
 */
///@{

/**
 *******************************************************************************
 * @brief       I2C Interrupt Config
 *
 *              I2C Interrupt Config
 * @details     I2C Interrupt Config
 * @param[in]   I2Cx            : where x can be 0 and 1 to select the I2C peripheral.
 * @param[in]   I2C_ITSrc       : Interrupt Source
 *   @arg\b     I2C_IT_IEA      : I2C0 interrupt all enable.
 *   @arg\b     I2C_IT_TMOUT    : I2C timeout error interrupt enable.
 *   @arg\b     I2C_IT_STPSTR   : I2C Stop or Start detection interrupt enable.
 *   @arg\b     I2C_IT_EVENT    : I2C status event interrupt enable.
 *   @arg\b     I2C_IT_BUF      : I2C buffer mode event Interrupt enable.
 *   @arg\b     I2C_IT_ERR      : I2C no ack error, bus arbitration lost, bus error or data overrun interrupt enable.
 * @param[in]   State           : 
 *   @arg\b     ENABLE          : Slave Address Detect Enable
 *   @arg\b     DISABLE         : Slave Address Detect Disable. (Default)
 * @par         Refer
 *              ???????
 *      \n      global_var1     : global var1 ???
 * @return      No
 * @exception   None
 * @note        
 * @par         Example
 * @code
                I2C_IT_Config(I2C0, I2C_IT_EVENT, ENABLE);
                I2C_IT_Config(I2C0, I2C_IT_EVENT, DISABLE);
                I2C_IT_Config(I2C0, (I2C_IT_EVENT | I2C_IT_TMOUT), ENABLE);
                I2C_IT_Config(I2C0, (I2C_IT_EVENT | I2C_IT_TMOUT), DISABLE);
                I2C_IT_Config(I2C0, (I2C_IT_BUF | I2C_IT_ERR), ENABLE);
                I2C_IT_Config(I2C0, (I2C_IT_BUF | I2C_IT_ERR), DISABLE);
                I2C_IT_Config(I2C0, (I2C_IT_BUF | I2C_IT_ERR | I2C_IT_TMOUT), ENABLE);
                I2C_IT_Config(I2C0, (I2C_IT_BUF | I2C_IT_ERR | I2C_IT_TMOUT), DISABLE);
                I2C_IT_Config(I2C1, I2C_IT_TMOUT, ENABLE);
                I2C_IT_Config(I2C1, I2C_IT_TMOUT, DISABLE);
 * @endcode
 * @par         Modify
 *              void I2C_IT_Config(I2C_Struct* I2Cx, uint32_t I2C_ITSrc, FunctionalState State)
 *******************************************************************************
 */
void I2C_IT_Config(I2C_Struct* I2Cx, uint32_t I2C_ITSrc, FunctionalState State)
{
    if(State == ENABLE)
        I2Cx->INT.W |= I2C_ITSrc;
    else
        I2Cx->INT.W &= (~I2C_ITSrc);
}



/**
 *******************************************************************************
 * @brief       I2C Interrupt Enable / Disable
 *
 *              I2C Interrupt Enable / Disable
 * @details     I2C Interrupt Enable / Disable
 * @param[in]   I2Cx : where x can be 0 and 1 to select the I2C peripheral.
 * @param[in]   State : 
 *   @arg\b     ENABLE : Slave Address Detect Enable
 *   @arg\b     DISABLE : Slave Address Detect Disable. (Default)
 * @return      No
 * @exception   None
 * @note        None
 * @par         Example
 * @code
                I2C_ITEA_Cmd(I2C0, ENABLE);
                I2C_ITEA_Cmd(I2C0, DISABLE);
                I2C_ITEA_Cmd(I2C1, ENABLE);
                I2C_ITEA_Cmd(I2C1, DISABLE);
 * @endcode
 * @par         Modify
 *              void I2C_ITEA_Cmd(I2C_Struct* I2Cx, FunctionalState State);
 *******************************************************************************
 */
void I2C_ITEA_Cmd(I2C_Struct* I2Cx, FunctionalState State)
{
    if(State == ENABLE)
        I2Cx->INT.B[0] |= I2C_CR0_EN_enable_b0;
    else
        I2Cx->INT.B[0] &= ~I2C_CR0_EN_mask_b0;
}



/**
 *******************************************************************************
 * @brief       I2C Get IT Source
 *
 *              I2C Get Interrupt Source
 * @details     I2C Get Interrupt Source
 * @param[in]   I2Cx : where x can be 0 and 1 to select the I2C peripheral.
 * @return      uint32_t : 
 * @return      I2C_IT_IEA = I2C0 interrupt all enable.
 * @return      I2C_IT_TMOUT = I2C timeout error interrupt enable.
 * @return      I2C_IT_EVENT = I2C status event interrupt enable.
 * @return      I2C_IT_BUF = I2C buffer mode event Interrupt enable.
 * @return      I2C_IT_ERR = I2C no ack error, bus arbitration lost, bus error or data overrun interrupt enable.
 * @see         
 * @exception   None
 * @note        None
 * @par         Example
 * @code
                if((I2C_GetITSource(I2C0) & I2C_IT_IEA) != 0)
                if((I2C_GetITSource(I2C0) & I2C_IT_IEA) == 0)
                if((I2C_GetITSource(I2C0) & I2C_IT_EVENT) != 0)
                if((I2C_GetITSource(I2C0) & I2C_IT_EVENT) == 0)
                if((I2C_GetITSource(I2C0) & I2C_IT_TMOUT) != 0)
                if((I2C_GetITSource(I2C0) & I2C_IT_TMOUT) == 0)
                if((I2C_GetITSource(I2C1) & I2C_IT_IEA) != 0)
                if((I2C_GetITSource(I2C1) & I2C_IT_IEA) == 0)
                if((I2C_GetITSource(I2C1) & I2C_IT_EVENT) != 0)
                if((I2C_GetITSource(I2C1) & I2C_IT_EVENT) == 0)
                if((I2C_GetITSource(I2C1) & I2C_IT_TMOUT) != 0)
                if((I2C_GetITSource(I2C1) & I2C_IT_TMOUT) == 0)
 * @endcode
 * @par         Modify
 *              uint32_t I2C_GetITSource(I2C_Struct* I2Cx);
 *******************************************************************************
 */
uint32_t I2C_GetITSource(I2C_Struct* I2Cx)
{
    return (I2Cx->INT.W &(I2C_IT_BUF | I2C_IT_ERR | I2C_IT_EVENT | I2C_IT_TMOUT | I2C_IT_STPSTR | I2C_IT_IEA));
}



/**
 *******************************************************************************
 * @brief       I2C Get All Flag Status
 * @details     I2C status event Flag. 
 *              (set by hardware , clear by software setting 1)
 *              using Byte Mode.
 *              
 * @param[in]   I2Cx : where x can be 0 and 1 to select the I2C peripheral.
 * @return      uint32_t : I2C FLAG Status
 * @return      I2C_FLAG_BUSYF : I2C busy flag.
 * @return      I2C_FLAG_EVENTF : I2C status event interrupt Flag.
 * @return      I2C_FLAG_BUFF : I2C buffer mode event flag.
 * @return      I2C_FLAG_ERRF : I2C error interrupt flag.
 * @return      I2C_FLAG_TMOUTF : I2C time-out detect flag.
 * @return      I2C_FLAG_RXF : I2C Receive data register not empty.
 * @return      I2C_FLAG_TXF : I2C Transmit data register empty.
 * @return      I2C_FLAG_RSTRF : I2C repeat start asserted flag.
 * @return      I2C_FLAG_STOPF : I2C stop detection flag.
 * @return      I2C_FLAG_CNTF : I2C buffer count I2C0_BUF_CNT empty status.
 * @return      I2C_FLAG_ERRCF :I2C master mode NACK error flag and state control bit.
 * @return      I2C_FLAG_SADRF : I2C slave mode slave address matched flag.
 * @return      I2C_FLAG_SLAF : I2C slave mode detection status.
 * @return      I2C_FLAG_MSTF : I2C master mode detection status.
 * @return      I2C_FLAG_RWF : I2C read or write transfer direction status.
 * @return      I2C_FLAG_TSCF : I2C shadow buffer transfer complete flag.
 * @return      I2C_FLAG_STPSTRF : I2C Bus Stop or Bus Start detection flag.
 * @return      I2C_FLAG_TXRF : I2C transmit data register remained status.
 * @return      I2C_FLAG_ROVRF : I2C data buffer receive overrun error flag.
 * @return      I2C_FLAG_TOVRF : I2C data buffer transmit underrun error flag.
 * @return      I2C_FLAG_NACKF : I2C Not Acknowledge received error flag.
 * @return      I2C_FLAG_ALOSF : I2C bus arbitration lost error flag.
 * @return      I2C_FLAG_BERRF : I2C bus error flag for invalid Stop/Start state.

 * @exception   None
 * @note        
 * @par         Example
 * @code        
                while((I2C_GetAllFlagStatus(I2C0) & I2C_FLAG_BUSYF) == I2C_FLAG_BUSYF);
                while((I2C_GetAllFlagStatus(I2C0) & I2C_FLAG_EVENTF) == I2C_FLAG_EVENTF);
                if((I2C_GetAllFlagStatus(I2C0) & I2C_FLAG_BUSYF) == I2C_FLAG_BUSYF)
                if((I2C_GetAllFlagStatus(I2C0) & I2C_FLAG_BUFF) == I2C_FLAG_BUFF)
                if((I2C_GetAllFlagStatus(I2C0) & I2C_FLAG_ERRF) == I2C_FLAG_ERRF)
                if((I2C_GetAllFlagStatus(I2C0) & I2C_FLAG_TMOUTF) == I2C_FLAG_TMOUTF)
                if((I2C_GetAllFlagStatus(I2C0) & (I2C_FLAG_BUFF | I2C_FLAG_SADRF)) == (I2C_FLAG_BUFF | I2C_FLAG_SADRF))
                if((I2C_GetAllFlagStatus(I2C0) & (I2C_FLAG_ERRF | I2C_FLAG_ALOSF)) == (I2C_FLAG_ERRF | I2C_FLAG_ALOSF))
                while((I2C_GetAllFlagStatus(I2C1) & I2C_FLAG_BUSYF) == I2C_FLAG_BUSYF);
                while((I2C_GetAllFlagStatus(I2C1) & I2C_FLAG_EVENTF) == I2C_FLAG_EVENTF);
                if((I2C_GetAllFlagStatus(I2C1) & I2C_FLAG_BUSYF) == I2C_FLAG_BUSYF)
                if((I2C_GetAllFlagStatus(I2C1) & I2C_FLAG_BUFF) == I2C_FLAG_BUFF)
                if((I2C_GetAllFlagStatus(I2C1) & I2C_FLAG_ERRF) == I2C_FLAG_ERRF)
                if((I2C_GetAllFlagStatus(I2C1) & I2C_FLAG_TMOUTF) == I2C_FLAG_TMOUTF)
                if((I2C_GetAllFlagStatus(I2C1) & (I2C_FLAG_BUFF | I2C_FLAG_SADRF)) == (I2C_FLAG_BUFF | I2C_FLAG_SADRF))
                if((I2C_GetAllFlagStatus(I2C1) & (I2C_FLAG_ERRF | I2C_FLAG_ALOSF)) == (I2C_FLAG_ERRF | I2C_FLAG_ALOSF))
 * @endcode     
 * @par         Modify
 *              uint32_t I2C_GetAllFlagStatus(I2C_Struct* I2Cx)
 *******************************************************************************
 */
uint32_t I2C_GetAllFlagStatus(I2C_Struct* I2Cx)
{

    return(I2Cx->STA.W);

}



/**
 *******************************************************************************
 * @brief       I2C Get Flag
 *
 *              I2C Get Flag
 * @details     I2C Get Flag
 * @param[in]   I2Cx : where x can be 0 and 1 to select the I2C peripheral.
 * @param[in]  	I2C_FLAG : I2C flag
 *  @arg\b      I2C_FLAG_BUSYF : I2C busy flag.
 *  @arg\b      I2C_FLAG_EVENTF : I2C status event interrupt Flag.
 *  @arg\b      I2C_FLAG_BUFF : I2C buffer mode event flag.
 *  @arg\b      I2C_FLAG_ERRF : I2C error interrupt flag.
 *  @arg\b      I2C_FLAG_TMOUTF : I2C time-out detect flag.
 *  @arg\b      I2C_FLAG_RXF : I2C Receive data register not empty.
 *  @arg\b      I2C_FLAG_TXF : I2C Transmit data register empty.
 *  @arg\b      I2C_FLAG_RSTRF : I2C repeat start asserted flag.
 *  @arg\b      I2C_FLAG_STOPF : I2C stop detection flag.
 *  @arg\b      I2C_FLAG_CNTF : I2C buffer count I2C0_BUF_CNT empty status.
 *  @arg\b      I2C_FLAG_ERRCF :I2C master mode NACK error flag and state control bit.
 *  @arg\b      I2C_FLAG_SADRF : I2C slave mode slave address matched flag.
 *  @arg\b      I2C_FLAG_SLAF : I2C slave mode detection status.
 *  @arg\b      I2C_FLAG_MSTF : I2C master mode detection status.
 *  @arg\b      I2C_FLAG_RWF : I2C read or write transfer direction status.
 *  @arg\b      I2C_FLAG_TSCF : I2C shadow buffer transfer complete flag.
 *  @arg\b      I2C_FLAG_STPSTRF : I2C Bus Stop or Bus Start detection flag.
 *  @arg\b      I2C_FLAG_TXRF : I2C transmit data register remained status.
 *  @arg\b      I2C_FLAG_ROVRF : I2C data buffer receive overrun error flag.
 *  @arg\b      I2C_FLAG_TOVRF : I2C data buffer transmit underrun error flag.
 *  @arg\b      I2C_FLAG_NACKF : I2C Not Acknowledge received error flag.
 *  @arg\b      I2C_FLAG_ALOSF : I2C bus arbitration lost error flag.
 *  @arg\b      I2C_FLAG_BERRF : I2C bus error flag for invalid Stop/Start state.
 * @par         None
 *              None ????????
 *      \n      global_var1     : global var1 ???
 * @return      DRV_Return
 * @see         DRV_Success : True
 * @see         DRV_Failure : False 
 * @exception   None
 * @note        None
 * @par         Example
 * @code
                [Example Code here start ...]
                ...
                [Example Code here end   ...]
 * @endcode
 * @par         Modify
 *              DRV_Return I2C_GetFlagStatus(I2C_Struct* I2Cx, uint32_t FlagStatus)
 *******************************************************************************
 */
DRV_Return I2C_GetFlagStatus(I2C_Struct* I2Cx, uint32_t I2C_FLAG)
{
    if((I2Cx->STA.W & I2C_FLAG) == I2C_FLAG)
        return (DRV_Happened);
    else
        return (DRV_UnHappened);
}



/**
 *******************************************************************************
 * @brief       I2C Clear Flag
 * @details     I2C status Flag.
 *              
 * @param[in]   I2Cx : where x can be 0 and 1 to select the I2C peripheral.
 * @param[in]   I2C_FLAG : I2C flag
 *  @arg\b      I2C_FLAG_EVENTF : status event interrupt Flag.
 *  @arg\b      I2C_FLAG_TMOUTF : time-out detect flag.
 *  @arg\b      I2C_FLAG_CNTF : buffer count I2C0_BUF_CNT empty status.
 *  @arg\b      I2C_FLAG_STPSTRF : I2C Bus Stop or Bus Start detection flag.
 *  @arg\b      I2C_FLAG_BUFF : buffer mode event flag.
 *  @arg\b      I2C_FLAG_RXF : Receive data register not empty.
 *  @arg\b      I2C_FLAG_TXF : Transmit data register empty.
 *  @arg\b      I2C_FLAG_RSTRF : repeat start asserted flag.
 *  @arg\b      I2C_FLAG_STOPF : stop detection flag.
 *  @arg\b      I2C_FLAG_SADRF : slave mode slave address matched flag.
 *  @arg\b      I2C_FLAG_ERRCF : master mode NACK error flag and state control bit.
 *  @arg\b      I2C_FLAG_ERRF : error interrupt flag.
 *  @arg\b      I2C_FLAG_ROVRF : I2C data buffer receive overrun error flag.
 *  @arg\b      I2C_FLAG_TOVRF : I2C data buffer transmit underrun error flag.
 *  @arg\b      I2C_FLAG_NACKF : I2C Not Acknowledge received error flag.
 *  @arg\b      I2C_FLAG_ALOSF : I2C bus arbitration lost error flag.
 *  @arg\b      I2C_FLAG_BERRF : I2C bus error flag for invalid Stop/Start state.
 * @return      No
 * @exception   None
 * @note        
 * @par         Example
 * @code        
                void I2C_ClearFlag(I2C0, I2C_FLAG_TMOUTF); // Any Mode
                void I2C_ClearFlag(I2C0, I2C_FLAG_STPSTRF); // Any Mode
                void I2C_ClearFlag(I2C0, I2C_FLAG_EVENTF); // Byte Mode
                void I2C_ClearFlag(I2C0, I2C_FLAG_BUFF); // Buffer Mode
                void I2C_ClearFlag(I2C0, (I2C_FLAG_BUFF | I2C_FLAG_SADRF)); // Buffer Mode
                void I2C_ClearFlag(I2C0, (I2C_FLAG_BUFF | I2C_FLAG_SADRF)); // Buffer Mode
                void I2C_ClearFlag(I2C0, (I2C_FLAG_BUFF | I2C_FLAG_RXF)) // Buffer Mode
                void I2C_ClearFlag(I2C0, (I2C_FLAG_BUFF | I2C_FLAG_TXF)); // Buffer Mode
                void I2C_ClearFlag(I2C0, (I2C_FLAG_BUFF | I2C_FLAG_RSTRF)); // Buffer Mode
                void I2C_ClearFlag(I2C0, (I2C_FLAG_BUFF | I2C_FLAG_STOPF)); // Buffer Mode
                void I2C_ClearFlag(I2C0, (I2C_FLAG_BUFF | I2C_FLAG_SADRF | I2C_FLAG_RXF | I2C_FLAG_TXF | I2C_FLAG_RSTRF | I2C_FLAG_STOPF) ); // Buffer Mode  
                void I2C_ClearFlag(I2C0, I2C_FLAG_ERRF); // Buffer Mode  
                void I2C_ClearFlag(I2C0, (I2C_FLAG_ERRF | I2C_FLAG_ERRCF)); // Buffer Mode
                void I2C_ClearFlag(I2C0, (I2C_FLAG_ERRF | I2C_FLAG_ALOSF)) // Buffer Mode
                void I2C_ClearFlag(I2C0, (I2C_FLAG_ERRF | I2C_FLAG_BERRF)); // Buffer Mode
                void I2C_ClearFlag(I2C0, (I2C_FLAG_ERRF | I2C_FLAG_NACKF)); // Buffer Mode
                void I2C_ClearFlag(I2C0, (I2C_FLAG_ERRF | I2C_FLAG_TOVRF)); // Buffer Mode
                void I2C_ClearFlag(I2C0, (I2C_FLAG_ERRF | I2C_FLAG_ROVRF)); // Buffer Mode
                void I2C_ClearFlag(I2C0, (I2C_FLAG_ERRF | I2C_FLAG_ERRCF | I2C_FLAG_ALOSF | I2C_FLAG_BERRF | I2C_FLAG_NACKF | I2C_FLAG_TOVRF | I2C_FLAG_ROVRF)); // Buffer Mode
                void I2C_ClearFlag(I2C1, I2C_FLAG_TMOUTF); // Any Mode
                void I2C_ClearFlag(I2C1, I2C_FLAG_STPSTRF); // Any Mode
                void I2C_ClearFlag(I2C1, I2C_FLAG_EVENTF); // Byte Mode
                void I2C_ClearFlag(I2C1, I2C_FLAG_BUFF); // Buffer Mode
                void I2C_ClearFlag(I2C1, (I2C_FLAG_BUFF | I2C_FLAG_SADRF)); // Buffer Mode
                void I2C_ClearFlag(I2C1, (I2C_FLAG_BUFF | I2C_FLAG_SADRF)); // Buffer Mode
                void I2C_ClearFlag(I2C1, (I2C_FLAG_BUFF | I2C_FLAG_RXF)) // Buffer Mode
                void I2C_ClearFlag(I2C1, (I2C_FLAG_BUFF | I2C_FLAG_TXF)); // Buffer Mode
                void I2C_ClearFlag(I2C1, (I2C_FLAG_BUFF | I2C_FLAG_RSTRF)); // Buffer Mode
                void I2C_ClearFlag(I2C1, (I2C_FLAG_BUFF | I2C_FLAG_STOPF)); // Buffer Mode
                void I2C_ClearFlag(I2C1, (I2C_FLAG_BUFF | I2C_FLAG_SADRF | I2C_FLAG_RXF | I2C_FLAG_TXF | I2C_FLAG_RSTRF | I2C_FLAG_STOPF) ); // Buffer Mode
                void I2C_ClearFlag(I2C1, I2C_FLAG_ERRF); // Buffer Mode
                void I2C_ClearFlag(I2C1, (I2C_FLAG_ERRF | I2C_FLAG_ERRCF)); // Buffer Mode
                void I2C_ClearFlag(I2C1, (I2C_FLAG_ERRF | I2C_FLAG_ALOSF)) // Buffer Mode
                void I2C_ClearFlag(I2C1, (I2C_FLAG_ERRF | I2C_FLAG_BERRF)); // Buffer Mode
                void I2C_ClearFlag(I2C1, (I2C_FLAG_ERRF | I2C_FLAG_NACKF)); // Buffer Mode
                void I2C_ClearFlag(I2C1, (I2C_FLAG_ERRF | I2C_FLAG_TOVRF)); // Buffer Mode
                void I2C_ClearFlag(I2C1, (I2C_FLAG_ERRF | I2C_FLAG_ROVRF)); // Buffer Mode
                void I2C_ClearFlag(I2C1, (I2C_FLAG_ERRF | I2C_FLAG_ERRCF | I2C_FLAG_ALOSF | I2C_FLAG_BERRF | I2C_FLAG_NACKF | I2C_FLAG_TOVRF | I2C_FLAG_ROVRF)); // Buffer Mode
 * @endcode     
 * @par         Modify
 *              void I2C_ClearFlag(I2C_Struct* I2Cx, uint32_t I2C_FLAG)
 *******************************************************************************
 */
void I2C_ClearFlag(I2C_Struct* I2Cx, uint32_t I2C_FLAG)
{
    I2Cx->STA.W = I2C_FLAG;
}



/**
 *******************************************************************************
 * @brief       Get Status Event Code
 * @details     I2C status event code.
 *              
 * @param[in]   I2Cx : where x can be 0 and 1 to select the I2C peripheral.
 * @return      uint8_t : 
 * @see             0x00 : Bus error during MASTER or selected slave modes, due to an illegal START or STOP condition. State 0x00 can also occur when interference causes the I2C block to enter an undefined state.
 * @see             0xF8 : No relevant state information available; Bus is released ; EVENTF = 0 and no interrupt asserted.(Default)
 * @see         Master Tansmit Mode Event
 * @see             0x08 : A START condition has been transmitted.
 * @see             0x10 : A repeated START condition has been transmitted.
 * @see             0x18 : SLA+W has been transmitted; ACK has been received.
 * @see             0x20 : SLA+W has been transmitted; NOT ACK has been received.
 * @see             0x28 : Data byte in DAT has been transmitted; ACK has been received.
 * @see             0x30 : Data byte in DAT has been transmitted; NOT ACK has been received.
 * @see             0x38 : Arbitration lost in SLA+R/W or Data bytes.
 * @see         Master Receiver Mode Event
 * @see             0x08 : A START condition has been transmitted.
 * @see             0x10 : A repeated START condition has been transmitted.
 * @see             0x38 : Arbitration lost in NOT ACK bit.
 * @see             0x40 : SLA+R has been transmitted; ACK has been received.
 * @see             0x48 : SLA+R has been transmitted; NOT ACK has been received.
 * @see             0x50 : Data byte has been received; ACK has been returned.
 * @see             0x58 : Data byte has been received; NOT ACK has been returned.
 * @see         Slave Receiver Mode Event
 * @see             0x60 : Own SLA+W has been received; ACK has been returned.
 * @see             0x68 : Arbitration lost in SLA+R/W as master; Own SLA+W has been received, ACK returned.
 * @see             0x70 : General Call address (0x00) has been received; ACK has been returned.
 * @see             0x78 : Arbitration lost in SLA+R/W as master; General Call address has been received, ACK has been returned.
 * @see             0x80 : Previously addressed with own SLA address; DATA has been received; ACK has been returned.
 * @see             0x88 : Previously addressed with own SLA; DATA byte has been received; NOT ACK has been returned.
 * @see             0x90 : Previously addressed with General Call; DATA byte has been received; ACK has been returned.
 * @see             0x98 : Previously addressed with General Call; DATA byte has been received; NOT ACK has been returned.
 * @see             0xA0 : A STOP condition or condition has been received while still addressed as Slave Receiver or Slave Transmitter.
 * @see         Slave Transmit Mode Event
 * @see             0xA8 : Own SLA+R has been received; ACK has been returned.
 * @see             0xB0 : Arbitration lost in SLA+R/W as master; Own SLA+R has been received, ACK has been returned.
 * @see             0xB8 : Data byte in DAT has been transmitted; ACK has been received.
 * @see             0xC0 : Data byte in DAT has been transmitted; NOT ACK has been received.
 * @see             0xC8 : Last data byte in DAT has been transmitted (AA = 0); ACK has been received.
 * @exception   None
 * @note        
 * @par         Example
 * @code        
                if(I2C_GetEventCode(I2C0))
                switch(I2C_GetEventCode(I2C0))
                if(I2C_GetEventCode(I2C1))
                switch(I2C_GetEventCode(I2C1))
 * @endcode     
 * @par         Modify
 *              uint8_t I2C_GetEventCode(I2C_Struct* I2Cx);
 *******************************************************************************
 */
uint8_t I2C_GetEventCode(I2C_Struct* I2Cx)
{
    return(I2Cx->STA2.B[0] & 0xF8);
}



/**
 *******************************************************************************
 * @brief       I2C Get EVENTF Flag
 * @details     I2C status event Flag.
 *              (set by hardware , clear by software setting 1)
 *              using Byte Mode.
 *              
 * @param[in]   I2Cx : where x can be 0 and 1 to select the I2C peripheral.
 * @return      DRV_Return
 * @see         DRV_Success : True
 * @see         DRV_Failure : False
 * @exception   None
 * @note        
 * @par         Example
 * @code        
                if(I2C_GetEventFlag(I2C0) == DRV_Success)
                while(I2C_GetEventFlag(I2C0) == DRV_Failure);
 * @endcode     
 * @par         Modify
 *              DRV_Return I2C_GetEventFlag(I2C_Struct* I2Cx);
 *******************************************************************************
 */
DRV_Return I2C_GetEventFlag(I2C_Struct* I2Cx)
{
    if((I2Cx->STA2.B[1] & 0x01) != 0)
        return DRV_Success;
    else
        return DRV_Failure;
}



/**
 *******************************************************************************
 * @brief       I2C Clear EVENTF Flag
 * @details     I2C0 status event interrupt Flag.
                (set by hardware , clear by software setting 1)
 *              
 * @param[in]   I2Cx : where x can be 0 and 1 to select the I2C peripheral.
 * @return      No
 * @exception   None
 * @note        
 * @par         Example
 * @code        
                I2C_ClearEventFlag(I2C0);
                I2C_ClearEventFlag(I2C1);
 * @endcode     
 * @par         Modify
 *              void I2C_ClearEventFlag(I2C_Struct* I2Cx);
 *******************************************************************************
 */
void I2C_ClearEventFlag(I2C_Struct* I2Cx)
{
    I2Cx->STA2.B[1] = I2C_STA2_EVENTF2_mask_b1;
}

///@}



/**
 * @name    Data transmission
 *          Data transmission
 */ 
///@{

/**
 *******************************************************************************
 * @brief       Get Slave Match Address
 *
 *              Get Slave Match Address
 * @details     I2C slave mode grabbed slave address code. 
 *              When slave mode, I2C controller will grab the slave address code always.
 * @param[in]   I2Cx : where x can be 0 and 1 to select the I2C peripheral.
 * @return      uint8_t : Macth Slave Address 0 ~ 127
 * @exception   None
 * @note        
 * @par         Example
 * @code
                if(I2C_GetSlaveMatchAddress(I2C0) == I2C_GetSlaveAddress(I2C0, I2C_SADR_0))
                if(I2C_GetSlaveMatchAddress(I2C0) == I2C_GetSlaveAddress(I2C0, I2C_SADR_1))
                if(I2C_GetSlaveMatchAddress(I2C0) == I2C_GetSlaveAddress(I2C0, I2C_SADR_2)))
                while(I2C_GetSlaveMatchAddress(I2C0) == I2C_GetSlaveAddress(I2C0, I2C_SADR_0))
                while(I2C_GetSlaveMatchAddress(I2C0) == I2C_GetSlaveAddress(I2C0, I2C_SADR_1))
                while(I2C_GetSlaveMatchAddress(I2C0) == I2C_GetSlaveAddress(I2C0, I2C_SADR_2))
                if(I2C_GetSlaveMatchAddress(I2C1) == I2C_GetSlaveAddress(I2C1, I2C_SADR_0))
                if(I2C_GetSlaveMatchAddress(I2C1) == I2C_GetSlaveAddress(I2C1, I2C_SADR_1))
                if(I2C_GetSlaveMatchAddress(I2C1) == I2C_GetSlaveAddress(I2C1, I2C_SADR_2))
                while(I2C_GetSlaveMatchAddress(I2C1) == I2C_GetSlaveAddress(I2C0, I2C_SADR_0))
                while(I2C_GetSlaveMatchAddress(I2C1) == I2C_GetSlaveAddress(I2C0, I2C_SADR_1))
                while(I2C_GetSlaveMatchAddress(I2C1) == I2C_GetSlaveAddress(I2C0, I2C_SADR_2))

 * @endcode     
 * @par         Modify
 *              uint8_t I2C_GetSlaveMatchAddress(I2C_Struct* I2Cx)
 *******************************************************************************
 */
uint8_t I2C_GetSlaveMatchAddress(I2C_Struct* I2Cx)
{
    return(I2Cx->SAC.B[0]);
}



/**
 *******************************************************************************
 * @brief       Send SBUF with Byte Mode
 * @details     Write I2C data shift buffer register.
 *              
 * @param[in]   I2Cx : where x can be 0 and 1 to select the I2C peripheral.
 * @param[in]   TxData : Send Byte Data .
 * @return      No
 * @exception   None
 * @note        
 * @par         Example
 * @code        
                I2C_SendTxData(I2C0, TxData);
                I2C_SendTxData(I2C1, TxData);
 * @endcode     
 * @par         Modify
 *              void I2C_SendTxData(I2C_Struct* I2Cx, uint8_t TxData);
 *******************************************************************************
 */
void I2C_SendSBUF(I2C_Struct* I2Cx, uint8_t TxData)
{
    I2Cx->SBUF.B[0] = TxData;
}



/**
 *******************************************************************************
 * @brief       Receive SBUF with Byte Mode
 * @details     Read I2C data shift buffer register.
 *              
 * @param[in]   I2Cx : where x can be 0 and 1 to select the I2C peripheral.
 * @return      uint8_t : Receive Byte Data .
 * @exception   None
 * @note        
 * @par         Example
 * @code        
                uint8_t DataTemp = I2C_ReceiveRxData(I2C0);
                uint8_t DataTemp = I2C_ReceiveRxData(I2C1);
 * @endcode     
 * @par         Modify
 *              uint8_t I2C_ReceiveRxData(I2C_Struct* I2Cx);
 *******************************************************************************
 */
uint8_t I2C_ReceiveSBUF(I2C_Struct* I2Cx)
{
    return(I2Cx->SBUF.B[0]);
}

///@}


