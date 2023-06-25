/**
 ******************************************************************************
 *
 * @file        MG32x02z_GPL_DRV.c
 *
 * @brief       This is the C code format driver file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.16
 * @date        2021/07/13
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************
 * @par         Disclaimer 
 *      The Demo software is provided "AS IS"  without any warranty, either 
 *      expressed or implied, including, but not limited to, the implied warranties 
 *      of merchantability and fitness for a particular purpose.  The author will 
 *      not be liable for any special, incidental, consequential or indirect 
 *      damages due to loss of data or any other reason. 
 *      These statements agree with the world wide and local dictated laws about 
 *      authorship and violence against these laws. 
 ******************************************************************************
 ******************************************************************************
 */ 



#include "MG32x02z_GPL_DRV.h"



/**
 * @name    Parity
 *          Parity Setting 
 */ 
///@{

/**
 *******************************************************************************
 * @brief       GPL_ParityCheck_Select.
 * @details
 *              
 * @param[in]   Parity
 *  @arg\b      GPL_PARITY_EVEN
 *  @arg\b      GPL_PARITY_ODD
 * @return      None
 * @exception   None
 * @note        
 * @par         Example
 * @code
                GPL_ParityCheck_Select(GPL_PARITY_EVEN);
                GPL_ParityCheck_Select(GPL_PARITY_ODD);
 * @endcode
 * @par         Modify
 *              void GPL_ParityCheck_Select(uint32_t PARITY)
 *******************************************************************************
 */
void GPL_ParityCheck_Select(uint32_t Parity)
{
    GPL->CR0.W = (GPL->CR0.W & (~GPL_PARITY_MASK)) | Parity;
}



/**
 *******************************************************************************
 * @brief       GPL_GetParityCheckWord.
 * @details
 *              
 * @return      uint8_t
 * @return      0 : Parity Check equal
 * @return      1 : Parity Check not equal
 * @exception   None
 * @note        
 * @par         Example
 * @code
                if(GPL_GetParityCheckWord() == 0)
                if(GPL_GetParityCheckWord() != 1)
                while(GPL_GetParityCheckWord() == 0)
                while(GPL_GetParityCheckWord() != 1)
 * @endcode
 * @par         Modify
 *              uint8_t GPL_GetParityCheckWord(void)
 *******************************************************************************
 */
uint8_t GPL_GetParityCheckWord(uint32_t Data)
{
    GPL->DIN.W = Data;
    if((GPL->STA.W & GPL_FLAG_PARITY32) == 0)
        return 0;
    else
        return 1;
}



/**
 *******************************************************************************
 * @brief       GPL Get Parity Check HalfWord.
 * @details
 *              
 * @param[in]   Data : 
 * @param[in]   HalfWordX : 
 *  @arg\b      0 : Low HalfWord
 *  @arg\b      1 : High HalfWord
 * @return      uint8_t
 * @return      0 : Parity Check equal
 * @return      1 : Parity Check not equal
 * @exception   None
 * @note        
 * @par         Example
 * @code
                if(GPL_GetParityCheckHalfWord(0) == 0)
                if(GPL_GetParityCheckHalfWord(0) != 0)
                if(GPL_GetParityCheckHalfWord(1) == 0)
                if(GPL_GetParityCheckHalfWord(1) != 0)
                while(GPL_GetParityCheckHalfWord(0) == 0)
                while(GPL_GetParityCheckHalfWord(0) != 0)
                while(GPL_GetParityCheckHalfWord(1) == 0)
                while(GPL_GetParityCheckHalfWord(1) != 0)
 * @endcode
 * @par         Modify
 *              uint8_t GPL_GetParityCheckHalfWord(uint8_t HalfWordX)
 *******************************************************************************
 */
uint8_t GPL_GetParityCheckHalfWord(uint32_t Data, uint16_t HalfWordX)
{
    GPL->DIN.W = Data;
    if(HalfWordX == 0x00)
    {
        if((GPL->STA.W & GPL_FLAG_PARITY16_LOW) == 0)
            return 0;
        else
            return 1;
    }

    if(HalfWordX == 0x01)
    {
        if((GPL->STA.W & GPL_FLAG_PARITY16_HIGH) == 0)
            return 0;
        else
            return 1;
    }
    return 1;
}



/**
 *******************************************************************************
 * @brief       GPL Get Parity Check Low HalfWord.
 * @details
 *              
 * @return      uint8_t
 * @return      0 : Parity Check equal
 * @return      1 : Parity Check not equal
 * @exception   None
 * @note        
 * @par         Example
 * @code
                if(GPL_Flag_PAR_HalfWordLow() == 0)
                if(GPL_Flag_PAR_HalfWordLow() != 0)
                while(GPL_Flag_PAR_HalfWordLow() == 0)
                while(GPL_Flag_PAR_HalfWordLow() != 0)
 * @endcode
 * @par         Modify
 *              uint8_t GPL_GetParityCheckHalfWord_Low(void)
 *******************************************************************************
 */
uint8_t GPL_GetParityCheckHalfWord_Low(uint32_t Data)
{
    GPL->DIN.W = Data;
    if((GPL->STA.W & GPL_FLAG_PARITY16_LOW) == 0)
        return 0;
    else
        return 1;
}



/**
 *******************************************************************************
 * @brief       GPL Get Parity Check High HalfWord.
 * @details
 *              
 * @return      uint8_t
 * @return      0 : Parity Check equal
 * @return      1 : Parity Check not equal
 * @exception   None
 * @note        
 * @par         Example
 * @code
                if(GPL_GetParityCheckHalfWord_High() == 0)
                if(GPL_GetParityCheckHalfWord_High() != 0)
                while(GPL_GetParityCheckHalfWord_High() == 0)
                while(GPL_GetParityCheckHalfWord_High() != 0)
 * @endcode
 * @par         Modify
 *              uint8_t GPL_GetParityCheckHalfWord_High(void)
 *******************************************************************************
 */
uint8_t GPL_GetParityCheckHalfWord_High(uint32_t Data)
{
    GPL->DIN.W = Data;
    if((GPL->STA.W & GPL_FLAG_PARITY16_HIGH) == 0)
        return 0;
    else
        return 1;
}



/**
 *******************************************************************************
* @brief        GPL_Get Parity Check Byte0.
 * @details
 *              
 * @return      uint8_t
 * @return      0 : Parity Check equal
 * @return      1 : Parity Check not equal
 * @exception   None
 * @note        
 * @par         Example
 * @code
                if(GPL_GetParityCheckByte_0 == 0)
                if(GPL_GetParityCheckByte_0 != 0)
                while(GPL_GetParityCheckByte_0 == 0)
                while(GPL_GetParityCheckByte_0 != 0)
 * @endcode
 * @par         Modify
 *              uint8_t GPL_GetParityCheckByte_0(void)
 *******************************************************************************
 */
uint8_t GPL_GetParityCheckByte_0(uint32_t Data)
{
    GPL->DIN.W = Data;
    if((GPL->STA.W & GPL_FLAG_PARITY8_BYTE_0) == 0)
        return 0;
    else
        return 1;
}



/**
 *******************************************************************************
* @brief        GPL_Get Parity Check Byte1.
 * @details
 *              
 * @return      uint8_t
 * @return      0 : Parity Check equal
 * @return      1 : Parity Check not equal
 * @exception   None
 * @note        
 * @par         Example
 * @code
                if(GPL_GetParityCheckByte_1 == 0)
                if(GPL_GetParityCheckByte_1 != 0)
                while(GPL_GetParityCheckByte_1 == 0)
                while(GPL_GetParityCheckByte_1 != 0)
 * @endcode
 * @par         Modify
 *              uint8_t GPL_GetParityCheckByte_1(void)
 *******************************************************************************
 */
uint8_t GPL_GetParityCheckByte_1(uint32_t Data)
{
    GPL->DIN.W = Data;
    if((GPL->STA.W & GPL_FLAG_PARITY8_BYTE_1) == 0)
        return 0;
    else
        return 1;
}



/**
 *******************************************************************************
* @brief        GPL_Get Parity Check Byte2.
 * @details
 *              
 * @return      uint8_t
 * @return      0 : Parity Check equal
 * @return      1 : Parity Check not equal
 * @exception   None
 * @note        
 * @par         Example
 * @code
                if(GPL_GetParityCheckByte_2 == 0)
                if(GPL_GetParityCheckByte_2 != 0)
                while(GPL_GetParityCheckByte_2 == 0)
                while(GPL_GetParityCheckByte_2 != 0)
 * @endcode
 * @par         Modify
 *              uint8_t GPL_GetParityCheckByte_2(void)
 *******************************************************************************
 */
uint8_t GPL_GetParityCheckByte_2(uint32_t Data)
{
    GPL->DIN.W = Data;
    if((GPL->STA.W & GPL_FLAG_PARITY8_BYTE_2) == 0)
        return 0;
    else
        return 1;
}



/**
 *******************************************************************************
* @brief        GPL_Get Parity Check Byte3.
 * @details
 *              
 * @return      uint8_t
 * @return      0 : Parity Check equal
 * @return      1 : Parity Check not equal
 * @exception   None
 * @note        
 * @par         Example
 * @code
                if(GPL_GetParityCheckByte_3 == 0)
                if(GPL_GetParityCheckByte_3 != 0)
                while(GPL_GetParityCheckByte_3 == 0)
                while(GPL_GetParityCheckByte_3 != 0)
 * @endcode
 * @par         Modify
 *              uint8_t GPL_GetParityCheckByte_3(void)
 *******************************************************************************
 */
uint8_t GPL_GetParityCheckByte_3(uint32_t Data)
{
    GPL->DIN.W = Data;
    if((GPL->STA.W & GPL_FLAG_PARITY8_BYTE_3) == 0)
        return 0;
    else
        return 1;
}



/**
 *******************************************************************************
* @brief       GPL_GetParityCheckByte.
 * @details
 * @param[in]   Data :
 * @param[in]   ByteX : 
 *  @arg\b      0 : Byte 0
 *  @arg\b      1 : Byte 1
 *  @arg\b      2 : Byte 2
 *  @arg\b      3 : Byte 3
 * @return      uint8_t
 * @return      0 : Parity Check equal
 * @return      1 : Parity Check not equal
 * @exception   None
 * @note        
 * @par         Example
 * @code
                if(GPL_GetParityCheckByte(0) == 0)
                if(GPL_GetParityCheckByte(0) != 0)
                if(GPL_GetParityCheckByte(1) == 0)
                if(GPL_GetParityCheckByte(1) != 0)
                if(GPL_GetParityCheckByte(2) == 0)
                if(GPL_GetParityCheckByte(2) != 0)
                if(GPL_GetParityCheckByte(3) == 0)
                if(GPL_GetParityCheckByte(3) != 0)
                while(GPL_GetParityCheckByte(0) == 0)
                while(GPL_GetParityCheckByte(0) != 0)
                while(GPL_GetParityCheckByte(1) == 0)
                while(GPL_GetParityCheckByte(1) != 0)
                while(GPL_GetParityCheckByte(2) == 0)
                while(GPL_GetParityCheckByte(2) != 0)
                while(GPL_GetParityCheckByte(3) == 0)
                while(GPL_GetParityCheckByte(3) != 0)
 * @endcode
 * @par         Modify
 *              uint8_t GPL_GetParityCheckByte(uint32_t Data, uint8_t ByteX)
 *******************************************************************************
 */
uint8_t GPL_GetParityCheckByte(uint32_t Data, uint8_t ByteX)
{
    GPL->DIN.W = Data;
    switch(ByteX){
        case 0:
            if((GPL->STA.W & GPL_FLAG_PARITY8_BYTE_0) == 0)
                return 0;
            else
                return 1;

        case 1:
            if((GPL->STA.W & GPL_FLAG_PARITY8_BYTE_1) == 0)
                return 0;
            else
                return 1;

        case 2:
            if((GPL->STA.W & GPL_FLAG_PARITY8_BYTE_2) == 0)
                return 0;
            else
                return 1;

        case 3:
            if((GPL->STA.W & GPL_FLAG_PARITY8_BYTE_3) == 0)
                return 0;
            else
                return 1;

        default:
            return 1;
    }
}

///@}



/**
 * @name    Inverse
 *          Inverse Enable / Disable
 */ 
///@{

/**
 *******************************************************************************
 * @brief       GPL_Inverse_Cmd.
 * @details
 *              
 * @param[in]   State
 *  @arg\b      ENABLE
 *  @arg\b      DISABLE
 * @return      None
 * @exception   None
 * @note        
 * @par         Example
 * @code
                GPL_Inverse_Cmd(ENABLE);
                GPL_Inverse_Cmd(DISABLE);
 * @endcode
 * @par         Modify
 *              void GPL_Inverse_Cmd(FunctionalState State)
 *******************************************************************************
 */
void GPL_Inverse_Cmd(FunctionalState State)
{
    if(State == ENABLE)
        GPL->CR0.W |= GPL_INVERSE_MASK;
    else
        GPL->CR0.W &= (~GPL_INVERSE_MASK);
}
///@}



/**
 * @name    Order
 *          Order Setting
 */ 
///@{

/**
 *******************************************************************************
 * @brief       GPL_ByteOrderChange_Cmd.
 * @details
 *              
 * @param[in]   State
 *  @arg\b      ENABLE
 *  @arg\b      DISABLE
 * @return      None
 * @exception   None
 * @note        
 * @par         Example
 * @code
                GPL_ByteOrderChange_Cmd(ENABLE);
                GPL_ByteOrderChange_Cmd(DISABLE);
 * @endcode
 * @par         Modify
 *              void GPL_ByteOrderChange_Cmd(FunctionalState State)
 *******************************************************************************
 */
void GPL_ByteOrderChange_Cmd(FunctionalState State)
{
    if(State == ENABLE)
        GPL->CR0.W |= GPL_BYTE_ORDER_CHANGE_MASK;
    else
        GPL->CR0.W &= ~GPL_BYTE_ORDER_CHANGE_MASK;
}



#if !defined(MG32_1ST)
/**
 *******************************************************************************
 * @brief       GPL_16BitsByteOrderChange_Cmd.
 * @details
 *              
 * @param[in]   State
 *  @arg\b      ENABLE
 *  @arg\b      DISABLE
 * @return      None
 * @exception   None
 * @note
 *              Function Not Support Device(s):
 *    \n            1. MG32F02A132
 *    \n            2. MG32F02A072
 *    \n            3. MA862
 *
 *      Function Support Device(s):
 *    \n            1. MG32F02A032
 *    \n            2. .....
 * @par         Example
 * @code
                GPL_16BitsByteOrderChange_Cmd(ENABLE);
                GPL_16BitsByteOrderChange_Cmd(DISABLE);
 * @endcode
 * @par         Modify
 *              void GPL_16BitsByteOrderChange_Cmd(FunctionalState State)
 *******************************************************************************
 */
void GPL_16BitsByteOrderChange_Cmd(FunctionalState State)
{
    if(State == ENABLE)
        GPL->CR0.W |= GPL_CR0_BEND16_EN_mask_w;
    else
        GPL->CR0.W &= ~GPL_CR0_BEND16_EN_mask_w;
}
#endif


/**
 *******************************************************************************
 * @brief       GPL_BeforeBitOrderChange_Select.
 * @details
 *              
 * @param[in]   Select
 *  @arg\b      GPL_BEFORE_BIT_ORDER_DISABLE
 *  @arg\b      GPL_BEFORE_BIT_ORDER_8BITS
 *  @arg\b      GPL_BEFORE_BIT_ORDER_16BITS
 *  @arg\b      GPL_BEFORE_BIT_ORDER_32BITS
 * @return      None
 * @exception   None
 * @note        
 * @par         Example
 * @code
                GPL_BeforeBitOrderChange_Select(GPL_BEFORE_BIT_ORDER_DISABLE);
                GPL_BeforeBitOrderChange_Select(GPL_BEFORE_BIT_ORDER_8BITS);
                GPL_BeforeBitOrderChange_Select(GPL_BEFORE_BIT_ORDER_16BITS);
                GPL_BeforeBitOrderChange_Select(GPL_BEFORE_BIT_ORDER_32BITS);
 * @endcode
 * @par         Modify
 *              void GPL_BeforeBitOrderChange_Select(uint32_t PARITY)
 *******************************************************************************
 */
void GPL_BeforeBitOrderChange_Select(uint32_t Select)
{
    GPL->CR0.W = (GPL->CR0.W & (~GPL_BEFORE_BIT_ORDER_MASK)) | Select;
}



/**
 *******************************************************************************
 * @brief       GPL_AfterBitOrderChange_Select.
 * @details
 *              
 * @param[in]   Select
 *  @arg\b      GPL_AFTER_BIT_ORDER_DISABLE
 *  @arg\b      GPL_AFTER_BIT_ORDER_8BITS
 *  @arg\b      GPL_AFTER_BIT_ORDER_16BITS
 *  @arg\b      GPL_AFTER_BIT_ORDER_32BITS
 * @return      None
 * @exception   None
 * @note        
 * @par         Example
 * @code
                GPL_AfterBitOrderChange_Select(GPL_AFTER_BIT_ORDER_DISABLE);
                GPL_AfterBitOrderChange_Select(GPL_AFTER_BIT_ORDER_8BITS);
                GPL_AfterBitOrderChange_Select(GPL_AFTER_BIT_ORDER_16BITS);
                GPL_AfterBitOrderChange_Select(GPL_AFTER_BIT_ORDER_32BITS);
 * @endcode
 * @par         Modify
 *              void GPL_AfterBitOrderChange_Select(uint32_t Select)
 *******************************************************************************
 */
void GPL_AfterBitOrderChange_Select(uint32_t Select)
{
    GPL->CR1.W = (GPL->CR1.W & (~GPL_AFTER_BIT_ORDER_MASK)) | Select;
}

///@}



/**
 * @name    CRC
 *          CRC Setting
 */ 
///@{
/**
 *******************************************************************************
 * @brief       GPL_CRC_Mode_Select.
 * @details
 *              
 * @param[in]   Select
 *  @arg\b      GPL_CRC_MODE_CCITT16
 *  @arg\b      GPL_CRC_MODE_CRC8
 *  @arg\b      GPL_CRC_MODE_CRC16
 *  @arg\b      GPL_CRC_MODE_CRC32
 * @return      None
 * @exception   None
 * @note        
 * @par         Example
 * @code
                GPL_CRC_Mode_Select(GPL_CRC_MODE_CCITT16);
                GPL_CRC_Mode_Select(GPL_CRC_MODE_CRC8);
                GPL_CRC_Mode_Select(GPL_CRC_MODE_CRC16);
                GPL_CRC_Mode_Select(GPL_CRC_MODE_CRC32);
 * @endcode
 * @par         Modify
 *              void GPL_CRC_Mode_Select(uint32_t Select)
 *******************************************************************************
 */
void GPL_CRC_Mode_Select(uint32_t Select)
{
    GPL->CR1.W = (GPL->CR1.W & (~GPL_CRC_MODE_MASK)) | Select;
}



/**
 *******************************************************************************
 * @brief       GPL_CRC_Data_Size_Select.
 * @details
 *              
 * @param[in]   Select
 *  @arg\b      GPL_CRC_DATA_SIZE_8BITS
 *  @arg\b      GPL_CRC_DATA_SIZE_16BITS
 *  @arg\b      GPL_CRC_DATA_SIZE_32BITS
 * @return      None
 * @exception   None
 * @note        
 * @par         Example
 * @code
                GPL_CRC_Data_Size_Select(GPL_CRC_DATA_SIZE_8BITS);
                GPL_CRC_Data_Size_Select(GPL_CRC_DATA_SIZE_16BITS);
                GPL_CRC_Data_Size_Select(GPL_CRC_DATA_SIZE_32BITS);
 * @endcode
 * @par         Modify
 *              void GPL_CRC_Data_Size_Select(uint32_t Select)
 *******************************************************************************
 */
void GPL_CRC_Data_Size_Select(uint32_t Select)
{
    GPL->CR1.W = (GPL->CR1.W & (~GPL_CRC_DATA_SIZE_MASK)) | Select;
}



/**
 *******************************************************************************
 * @brief       GPL_CRC_Set Initial Value.
 * @details
 *              
 * @param[in]   InitialValue
 *  @arg\b      Any Unsigned Value. max 0xFFFFFFFF.
 * @return      None
 * @exception   None
 * @note        
 * @par         Example
 * @code
                GPL_CRC_SetInitValue(0x12345678);
 * @endcode
 * @par         Modify
 *              void GPL_CRC_SetInitValue(uint32_t Value)
 *******************************************************************************
 */
void GPL_CRC_SetInitValue(uint32_t InitialValue)
{
    GPL->CRCINIT.W = InitialValue;
}



/**
 *******************************************************************************
 * @brief       GPL_CRC_Cmd.
 * @details
 *              
 * @param[in]   State
 *  @arg\b      ENABLE  :
 *  @arg\b      DISABLE :
 * @return      None
 * @exception   None
 * @note        
 * @par         Example
 * @code
                GPL_CRC_Cmd(ENABLE);
                GPL_CRC_Cmd(DISABLE);
 * @endcode
 * @par         Modify
 *              void GPL_CRC_Cmd(uint32_t PARITY)
 *******************************************************************************
 */
void GPL_CRC_Cmd(FunctionalState State)
{
    if(State == ENABLE)
        GPL->CR1.W |= GPL_CRC_MASK;
    else
        GPL->CR1.W &= ~GPL_CRC_MASK;
}

///@}



/**
 * @name    GPL DMA
 *          DMA Enable / Disable
 */ 
///@{

/**
 *******************************************************************************
 * @brief       GPL_DMA_Cmd.
 * @details
 *              
 * @param[in]   State
 *  @arg\b      ENABLE
 *  @arg\b      DISABLE
 * @return      None
 * @exception   None
 * @note        
 * @par         Example
 * @code
                GPL_DMA_Cmd(ENABLE);
                GPL_DMA_Cmd(DISABLE);
 * @endcode
 * @par         Modify
 *              void GPL_DMA_Cmd(FunctionalState State)
 *******************************************************************************
 */
void GPL_DMA_Cmd(FunctionalState State)
{
    if(State == ENABLE)
        GPL->CR0.B[3] |= GPL_DMA_MASK;
    else
        GPL->CR0.B[3] &= ~GPL_DMA_MASK;
}
///@}



/**
 * @name    Data Input and Calculation Results Output.
 *          
 */ 
///@{

/**
 *******************************************************************************
 * @brief       GPL_DataInput.
 * @details
 *              
 * @param[in]   Data :
 *  @arg\b      Any Unsigned Value. max 0xFFFFFFFF.
 * @return      None
 * @exception   None
 * @note        
 * @par         Example
 * @code
                GPL_DataInput(GPL_PARITY_ODD);
 * @endcode
 * @par         Modify
 *              void GPL_DataInput(uint32_t Value)
 *******************************************************************************
 */
void GPL_DataInput(uint32_t Data)
{
    GPL->DIN.W = Data;
}



/**
 *******************************************************************************
 * @brief       GPL_GetOutputData.
 * @details
 *              
 * @return      uint32_t Value : Calculation results
 * @exception   None
 * @note        
 * @par         Example
 * @code
                uint8_t temp8 = GPL_GetOutputData();
                uint16_t temp16 = (uint16_t)GPL_GetOutputData();
                uint32_t temp32 = (uint32_t)GPL_GetOutputData();
 * @endcode
 * @par         Modify
 *              uint32_t GPL_GetOutputData(void)
 *******************************************************************************
 */
uint32_t GPL_GetOutputData(void)
{
    __ISB();
    return GPL->DOUT.W;
}

///@}



/**
 * @name    Flag
 *          Get and Clear Results Flag 
 */ 
///@{

/**
 *******************************************************************************
 * @brief       GPL Get All Flag Status.
 * @details
 *
 * @return      GPL_FLAG : Calculation results
 * @exception   None
 * @note        
 * @par         Example
 * @code
                uint32_t temp32 = GPL_GetAllFlagStatus(GPL);
                if((GPL_GetAllFlagStatus(GPL) & GPL_FLAG_PARITY32) == GPL_FLAG_PARITY32)
                if((GPL_GetAllFlagStatus(GPL) & GPL_FLAG_PARITY16_ALL) == GPL_FLAG_PARITY16_ALL)
                if((GPL_GetAllFlagStatus(GPL) & GPL_FLAG_PARITY16_LOW) == GPL_FLAG_PARITY16_LOW)
                if((GPL_GetAllFlagStatus(GPL) & GPL_FLAG_PARITY16_HIGH) == GPL_FLAG_PARITY16_HIGH)
                if((GPL_GetAllFlagStatus(GPL) & GPL_FLAG_PARITY8_ALL) == GPL_FLAG_PARITY8_ALL)
                if((GPL_GetAllFlagStatus(GPL) & GPL_FLAG_PARITY8_BYTE_0) == GPL_FLAG_PARITY8_BYTE_0)
                if((GPL_GetAllFlagStatus(GPL) & GPL_FLAG_PARITY8_BYTE_1) == GPL_FLAG_PARITY8_BYTE_1)
                if((GPL_GetAllFlagStatus(GPL) & GPL_FLAG_PARITY8_BYTE_2) == GPL_FLAG_PARITY8_BYTE_2)
                if((GPL_GetAllFlagStatus(GPL) & GPL_FLAG_PARITY8_BYTE_3) == GPL_FLAG_PARITY8_BYTE_3)
 * @endcode
 * @par         Modify
 *              uint32_t GPL_GetAllFlagStatus(void)
 *******************************************************************************
 */
uint32_t GPL_GetAllFlagStatus(void)
{
    return GPL->STA.W;
}



/**
 *******************************************************************************
 * @brief       GPL Get All Flag Status.
 * @details
 *              
 * @param[in]   GPL_FLAG : 
 *  @arg\b      GPL_FLAG_MASK : 
 *  @arg\b      GPL_FLAG_PARITY32 : 
 *  @arg\b      GPL_FLAG_PARITY16_ALL : 
 *  @arg\b      GPL_FLAG_PARITY16_LOW : 
 *  @arg\b      GPL_FLAG_PARITY16_HIGH : 
 *  @arg\b      GPL_FLAG_PARITY8_ALL : 
 *  @arg\b      GPL_FLAG_PARITY8_BYTE_0 : 
 *  @arg\b      GPL_FLAG_PARITY8_BYTE_1 : 
 *  @arg\b      GPL_FLAG_PARITY8_BYTE_2 : 
 *  @arg\b      GPL_FLAG_PARITY8_BYTE_3 : 
 * @return      uint32_t Value : Calculation results
 * @exception   None
 * @note        
 * @par         Example
 * @code
                if(GPL_GetFlagStatus(GPL, GPL_Flag_PAR32) != DRV_True)
                if(GPL_GetFlagStatus(GPL, GPL_Flag_PAR16_0) != DRV_True)
                if(GPL_GetFlagStatus(GPL, GPL_Flag_PAR8_0) != DRV_True)
 * @endcode
 * @par         Modify
 *              DRV_Return GPL_GetFlagStatus(uint32_t GPL_FLAG)
 *******************************************************************************
 */
DRV_Return GPL_GetFlagStatus(uint32_t GPL_FLAG)
{
    if((GPL->STA.W & GPL_FLAG) == GPL_FLAG)
        return DRV_True;
    else
        return DRV_False;
}

///@}


