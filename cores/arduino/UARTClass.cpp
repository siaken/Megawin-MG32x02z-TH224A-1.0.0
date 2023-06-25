/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "UARTClass.h"
#include "Arduino.h"

#include "MG32x02z_GPIO_MID.h"
#include "MG32x02z_CFG.h"



typedef struct
{
    uint32_t                pin;
    uint16_t                pinAFS;
    uint16_t                padding;
    URT_HandleTypeDef       *pURT;
}Uart_config_str;

#define  URTPIN_AFS_CFG(a, num, Ur, dr)      {.pin= (MCU_##a##num), .pinAFS=a##num##_AFS_##Ur##_##dr,  .padding=0,  .pURT=&m##Ur }

#ifdef    MG32F02U128
#define   NB_UART_CFG     63
static const Uart_config_str  uar_cfg[NB_UART_CFG] = 
{
    URTPIN_AFS_CFG(PA,8,URT4,TX ),
    URTPIN_AFS_CFG(PA,9,URT5,TX),
    URTPIN_AFS_CFG(PA,10,URT4,RX),
    URTPIN_AFS_CFG(PA,11,URT5,RX ),
    URTPIN_AFS_CFG(PA,12,URT6,TX),
    URTPIN_AFS_CFG(PA,13,URT6,RX ),
    URTPIN_AFS_CFG(PA,14,URT7,TX ),
    URTPIN_AFS_CFG(PA,15,URT7,RX ),
    URTPIN_AFS_CFG(PB,0,URT6,TX ),
    URTPIN_AFS_CFG(PB,1,URT1,RX),
    URTPIN_AFS_CFG(PB,1,URT6,RX),
    URTPIN_AFS_CFG(PB,2,URT0,TX),
    URTPIN_AFS_CFG(PB,2,URT7,TX ),
    URTPIN_AFS_CFG(PB,2,URT2,TX),
    URTPIN_AFS_CFG(PB,3,URT0,RX),
    URTPIN_AFS_CFG(PB,3,URT7,RX ),
    URTPIN_AFS_CFG(PB,3,URT2,RX),
    URTPIN_AFS_CFG(PB,3,URT1,TX),
    URTPIN_AFS_CFG(PB,6,URT2,TX ),
    URTPIN_AFS_CFG(PB,7,URT2,RX ),
    URTPIN_AFS_CFG(PB,8,URT0,TX),
    URTPIN_AFS_CFG(PB,8,URT4,TX),
    URTPIN_AFS_CFG(PB,9,URT0,RX),
    URTPIN_AFS_CFG(PB,9,URT4,RX),
    URTPIN_AFS_CFG(PB,10,URT1,TX),
    URTPIN_AFS_CFG(PB,11,URT1,RX),
    URTPIN_AFS_CFG(PB,12,URT5,TX),
    URTPIN_AFS_CFG(PB,13, URT4,RX),
    URTPIN_AFS_CFG(PB,14,URT4,TX),
    URTPIN_AFS_CFG(PB,15,URT5,RX),
    URTPIN_AFS_CFG(PC,0,URT5,TX),
    URTPIN_AFS_CFG(PC,1,URT0,RX),
    URTPIN_AFS_CFG(PC,1,URT5,RX),
    URTPIN_AFS_CFG(PC,4,URT0,RX),
    URTPIN_AFS_CFG(PC,4,URT1,RX),
    URTPIN_AFS_CFG(PC,4,URT6,RX),
    URTPIN_AFS_CFG(PC,5,URT0,TX),
    URTPIN_AFS_CFG(PC,5,URT1,TX),
    URTPIN_AFS_CFG(PC,5,URT6,TX),
    URTPIN_AFS_CFG(PC,8, URT1,TX),
    URTPIN_AFS_CFG(PC,8,URT6,TX ),
    URTPIN_AFS_CFG(PC,9,URT1,RX),
    URTPIN_AFS_CFG(PC,9,URT6,RX),
    URTPIN_AFS_CFG(PC,10,URT0,TX),
    URTPIN_AFS_CFG(PC,10,URT1,TX),
    URTPIN_AFS_CFG(PC,10,URT2,TX),
    URTPIN_AFS_CFG(PC,10,URT7,TX),
    URTPIN_AFS_CFG(PC,11,URT0,RX),
    URTPIN_AFS_CFG(PC,11,URT1,RX),
    URTPIN_AFS_CFG(PC,11,URT2,RX),
    URTPIN_AFS_CFG(PC,11,URT7,RX ),
    URTPIN_AFS_CFG(PC,13,URT2,RX),
    URTPIN_AFS_CFG(PC,13,URT6,RX),
    URTPIN_AFS_CFG(PC,14, URT2,TX),
    URTPIN_AFS_CFG(PC,14,URT6,TX),
    URTPIN_AFS_CFG(PD,2,URT2,TX),
    URTPIN_AFS_CFG(PD,3,URT2,RX),
    URTPIN_AFS_CFG(PA,0,URT4,TX ),
    URTPIN_AFS_CFG(PA,1,URT4,RX),
    URTPIN_AFS_CFG(PA,2,URT5,TX),
    URTPIN_AFS_CFG(PA,3,URT5,RX),
    URTPIN_AFS_CFG(PA,4,URT0,TX),
    URTPIN_AFS_CFG(PA,5,URT0,RX),
};

#endif



Uart::Uart(void)
{
    m_usart_typedef = NULL;
    m_irqtype = URT4x_IRQn;

    m_tx_pin = ((uint16_t)-1);
    m_rx_pin = ((uint16_t)-1);

    m_tx_pinAFS = ((uint16_t)-1);
    m_rx_pinAFS = ((uint16_t)-1);
            
    m_rxData_Count = 0;
    m_rxBegin = 0;
    m_rxEnd   = 0;

    m_txData_Count = 0;
    m_txBegin = 0;
    m_txEnd   = 0;
}

Uart::Uart( URT_HandleTypeDef *uartdef)
{
    m_usart_typedef = uartdef;
    m_irqtype = URT4x_IRQn;
    
    m_tx_pin = ((uint16_t)-1);
    m_rx_pin = ((uint16_t)-1);

    m_tx_pinAFS = ((uint16_t)-1);
    m_rx_pinAFS = ((uint16_t)-1);

    m_rxData_Count = 0;
    m_rxBegin = 0;
    m_rxEnd   = 0;

    m_txData_Count = 0;
    m_txBegin = 0;
    m_txEnd   = 0;
}

Uart::Uart( URT_HandleTypeDef *uartdef,  uint16_t  RxPin,  uint16_t  TxPin,  IRQn_Type  irqn)
{
    m_usart_typedef = uartdef;
    m_irqtype = irqn;
    
    m_tx_pin = TxPin;
    m_rx_pin = RxPin;

    m_tx_pinAFS = ((uint16_t)-1);
    m_rx_pinAFS = ((uint16_t)-1);

    m_rxData_Count = 0;
    m_rxBegin = 0;
    m_rxEnd   = 0;

    m_txData_Count = 0;
    m_txBegin = 0;
    m_txEnd   = 0;
}


int Uart::begin(  uint16_t   ArdRxPin,      uint16_t   ArdTxPin,   unsigned long baudRate)
{  
    return begin( m_usart_typedef,
                  ArdRxPin,       ArdTxPin,
                  m_irqtype,      baudRate  );
} 



int Uart::begin(  URT_HandleTypeDef *uartdef,
                  uint16_t   ArdRxPin,       uint16_t   ArdTxPin,
                  IRQn_Type      irqn,       unsigned long baudRate  )
{
    Pin_Struct*  pPinx;		
    GPIO_InitTypeDef PINX_InitStruct;

    uint32_t  i;

    uint16_t  Tx_pinAFS = -1;
    uint16_t  Rx_pinAFS = -1;

    if( uartdef != NULL ) 
    {
        m_usart_typedef = uartdef;
    }

    if( m_usart_typedef == NULL ) 
    {
        return -1;
    }

    m_irqtype = irqn;

    m_rxData_Count = 0;
    m_rxBegin = 0;
    m_rxEnd   = 0;

    m_txData_Count = 0;
    m_txBegin = 0;
    m_txEnd   = 0;

    if( ( ArdRxPin >= MAX_DIGITAL_IOS )  )
    {
        ArdRxPin =  m_rx_pin;
    }

    if( ( ArdTxPin >= MAX_DIGITAL_IOS )  )
    {
        ArdTxPin =  m_tx_pin;
    }

    if( ( ArdTxPin < MAX_DIGITAL_IOS )  )
    {
         for( i=0; i<NB_UART_CFG; i++  )
        {
            if(  ( uar_cfg[i].pin == ArdTxPin )  && (uartdef == uar_cfg[i].pURT)  )
            {
                Tx_pinAFS = uar_cfg[i].pinAFS;
                break;
            }
        }

        if( i==NB_UART_CFG )
        {
            Tx_pinAFS = (uint16_t)-1;
        }
        else
        {
            m_tx_pin    = ArdTxPin;
            m_tx_pinAFS = Tx_pinAFS;
        }
    }

    if( ( ArdRxPin < MAX_DIGITAL_IOS )  )
    {
        for( i=0; i<NB_UART_CFG; i++  )
        {
            if(  ( uar_cfg[i].pin == ArdRxPin )  && (uartdef == uar_cfg[i].pURT)  )
            {
                Rx_pinAFS = uar_cfg[i].pinAFS;
                break;
            }
        }
        if( i==NB_UART_CFG )
        {
            Rx_pinAFS = ((uint16_t)-1);
        }
        else
        {
            m_rx_pin    = ArdRxPin;
            m_rx_pinAFS = Rx_pinAFS;
        }
    } 

    //GPIO Inital :   PINX_Alternate_Function
    PINX_InitStruct.Speed          = GPIO_SPEED_LOW;
    PINX_InitStruct.OUTDrive       = GPIO_OUTDRIVE_LEVEL0;
    PINX_InitStruct.FilterDivider  = GPIO_FILTERDIVIDER_BYPASS;
    PINX_InitStruct.Inverse        = GPIO_INVERSE_DISABLE;

    ///cfg rx pin
    if(  ( m_rx_pinAFS != ((uint16_t)-1) )  
      && ( m_rx_pin < MAX_DIGITAL_IOS)   )
    {
        PINX_InitStruct.Mode		      = GPIO_MODE_DIGITAL_I;
        PINX_InitStruct.Pull          = GPIO_NOPULLUP;
        PINX_InitStruct.Alternate     = m_rx_pinAFS;
        pPinx = __GetPinxx_byGPIOx( g_APinDescription[m_rx_pin].ulPort,  g_APinDescription[m_rx_pin].PinNum );
        MID_GPIO_Pin_Init(  pPinx,  &PINX_InitStruct);
    }

    if(  ( m_tx_pinAFS != ((uint16_t)-1) ) 
      && ( m_tx_pin < MAX_DIGITAL_IOS)  )
    {
        ///cfg tx pin
        PINX_InitStruct.Mode	         = GPIO_MODE_PUSHPULL_O;
        PINX_InitStruct.Pull           = GPIO_NOPULLUP;
        PINX_InitStruct.Alternate      = m_tx_pinAFS;
        pPinx = __GetPinxx_byGPIOx( g_APinDescription[m_tx_pin].ulPort, g_APinDescription[m_tx_pin].PinNum );
        MID_GPIO_Pin_Init( pPinx, &PINX_InitStruct);
    } 

    m_txflag = 0;
    
    NVIC_DisableIRQ( m_irqtype );
    m_usart_typedef->Init.BaudRate = baudRate;

    MID_URT_Init( m_usart_typedef );

    m_rxData_Count = 0;
    m_rxBegin = 0;
    m_rxEnd   = 0;

    m_txData_Count = 0;
    m_txBegin = 0;
    m_txEnd   = 0;

    NVIC_SetPriority( m_irqtype,   3);
    //==============================================================================
    //Enable NVIC IRQ :
    NVIC_EnableIRQ( m_irqtype );

    flush();

    MID_URT_Receive_IT( m_usart_typedef,  &m_rxdata[0], 1 );

    return 0;
}


// Public Methods //////////////////////////////////////////////////////////////
void Uart::begin(unsigned long baudRate)
{
TestReg_push( 0x10000001 );
    begin( m_usart_typedef,
           m_rx_pin,        m_tx_pin,
           m_irqtype,       baudRate  );
    return;
}



void Uart::end( void )
{
    if( NULL == m_usart_typedef )
    {
        return;
    }
    
    //MID_URT_Abort( m_usart_typedef );
    //MID_URT_Abort_IT( m_usart_typedef );   
    NVIC_DisableIRQ( m_irqtype );

  	m_rxData_Count = 0;
    m_rxBegin = 0;
    m_rxEnd   = 0;

    m_txData_Count = 0;
    m_txBegin = 0;
    m_txEnd   = 0;
}

int Uart::available( void )
{
    //return the amount of data available
    return m_rxData_Count;
}


int Uart::availableForWrite( void )
{
    MID_URT_StateTypeDef state;
    
    if( NULL == m_usart_typedef )
    {
        return -1;
    }
    
    
    //return the amount of data available
    state = MID_URT_GetState( m_usart_typedef );
    return (state & MID_URT_STATE_READY);
}

int Uart::peek( void )
{
    int8_t data = -1;
    
    if( NULL == m_usart_typedef )
    {
        return -1;
    }
    

    if( m_rxData_Count > 0)
    {
        data = m_rxpData[ m_rxBegin ];
    }
    return data;
}

/////===============================================================
int Uart::read( void )
{
    int8_t data = -1;

    if( NULL == m_usart_typedef )
    {
        return -1;
    }

    NVIC_DisableIRQ( m_irqtype );
    if( m_rxData_Count > 0)
    {
        data = m_rxpData[ m_rxBegin ];
        m_rxBegin++;

        m_rxBegin = (m_rxBegin % SERIAL_BUFFER_SIZE);
        m_rxData_Count--;
    }
    else
    {
        m_rxBegin = m_rxEnd;
        m_rxData_Count = 0;
    }
    NVIC_EnableIRQ( m_irqtype );


    return data;
}

void Uart::flush( void )
{
    if( NULL == m_usart_typedef )
    {
        return;
    }

//    MID_URT_Abort_IT( m_usart_typedef );

    NVIC_DisableIRQ( m_irqtype );
    m_rxData_Count = 0;
    m_rxBegin = 0;
    m_rxEnd   = 0;

    m_txData_Count = 0;
    m_txBegin = 0;
    m_txEnd   = 0;

    NVIC_EnableIRQ( m_irqtype );
}

size_t Uart::write( uint8_t uc_data )
{
    __IO MID_URT_StateTypeDef  TxState;

    if( NULL == m_usart_typedef )
    {
        return 0;
    }
    
    m_txdata[0] = uc_data;

    do
    {
        NVIC_DisableIRQ( m_irqtype );
        TxState = m_usart_typedef->gState;
        MID_URT_Transmit_IT( m_usart_typedef, &m_txdata[0],   1 );
        NVIC_EnableIRQ( m_irqtype );

    }
    while( TxState != MID_URT_STATE_READY );

    return 1;
}

int Uart::printHex(  uint32_t uc_data   )
{
    int i;
    
    uint8_t u8_data;
    
    for( i=8; i>0; i-- )
    {
        u8_data = ( (uc_data >> ((i-1)*4)) & 0x0000000F);
        if( u8_data>9 )
        {
            write( ('a'+ u8_data -10) );
        }
        else
        {
            write( ('0'+ u8_data) );
        }
    }

    return 0;
}

int Uart::printDec(  uint32_t uc_data   )
{
    int i;
    uint32_t dev = 1; 
    uint32_t writeData = 0; 
    
    for( i=0; (i<16); i++ )
    {
        dev = dev*10;
        if(  (uc_data/dev) == 0  )
        {
            break;
        }
    }
    
    for( i=0; (i<16); i++ )
    {
        dev = dev/10;
        if( dev > 0 )
        {
            writeData = uc_data/dev;
            write( ('0'+ writeData) );

            uc_data   =  uc_data%dev;
        } 
        else
        {
            break;
        }
    }

    return 0;
}


void Uart::IrqTransHandler(void)
{

    m_txData_Count = 0;
    m_txEnd = m_txBegin;


    
    
/*
    if( m_txData_Count > 0  )
    {
        MID_URT_Transmit_IT( m_usart_typedef, &m_txBuffer[m_txEnd] , 1);
        m_txEnd++;
        m_txEnd = m_txEnd % SERIAL_BUFFER_SIZE;
        m_txData_Count--;
    }
    else
    {
        m_txData_Count = 0;
        m_txEnd = m_txBegin;
    }
*/
//    m_txData_Count = 0;
//    m_txEnd = m_txBegin;
}

void Uart::IrqRecvHandler(void)
{
    uint8_t temp;
    temp = m_rxdata[0];
    MID_URT_Receive_IT( m_usart_typedef,  &m_rxdata[0],  1 );

    if( m_rxData_Count < SERIAL_BUFFER_SIZE )
    {
        m_rxpData[ m_rxEnd ] = temp;
        m_rxEnd++;
        m_rxEnd = (m_rxEnd % SERIAL_BUFFER_SIZE);
        m_rxData_Count++;
    }
    else
    {
        m_rxData_Count = SERIAL_BUFFER_SIZE;
    }

    return;
}


extern Uart Serial;
extern Uart Serial1;
extern Uart Serial2;

#if defined(URT3)
extern Uart Serial3;
#endif

extern Uart Serial4;
extern Uart Serial5;
extern Uart Serial6;
extern Uart Serial7;

/**
 *******************************************************************************
 * @brief	 Replace printf fputc function.
 * @details
 * @return
 * @note
 *******************************************************************************
 */
 /*
int fputc(int ch, FILE *f __attribute__((unused)))
{
    DEBUG_URTn->TDAT.B[0] = (uint8_t)ch;
    while((DEBUG_URTn->STA.W & URT_STA_TXF_mask_w)==0);

    return(ch);
}
*/

size_t uart_write( uart_id_e uart_id, uint8_t data )
{
    
   switch( uart_id )
   {
       case USART0_E:
           Serial.write( data );
           break;
       case USART1_E:
           Serial1.write( data );
           break;
       case USART2_E:
           Serial2.write( data );
           break;
#if defined(URT3)
       case USART3_E:
           Serial3.write( data );
           break;
#endif
       case USART4_E:
           Serial4.write( data );
           break;
       case USART5_E:
           Serial5.write( data );
           break;
       case USART6_E:
           Serial6.write( data );
           break;
       case USART7_E:
           Serial7.write( data );
           break;
       default:
           break;
   }

  return 1;
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
 
void MID_URT_TxCpltCallback(URT_HandleTypeDef *MURT)
{
    if( MURT == &mURT0 )
    {
        Serial.IrqTransHandler();
    }

    if( MURT == &mURT1 )
    {
        Serial1.IrqTransHandler();
    }

    if( MURT == &mURT2 )
    {
        Serial2.IrqTransHandler();
    }
		
#if defined(URT3)
    if( MURT == &mURT3 )
    {
        Serial3.IrqTransHandler();
    }
#endif
		
    if( MURT == &mURT4 )
    {
        Serial4.IrqTransHandler();
    }

    if( MURT == &mURT5 )
    {
        Serial5.IrqTransHandler();
    }

    if( MURT == &mURT6 )
    {
        Serial6.IrqTransHandler();
    }

    if( MURT == &mURT7 )
    {
        Serial7.IrqTransHandler();
    }

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
void MID_URT_RxCpltCallback( URT_HandleTypeDef *MURT)
{
    if( MURT == &mURT0 )
    {
        Serial.IrqRecvHandler();
    }

    if( MURT == &mURT1 )
    {
        Serial1.IrqRecvHandler();
    }

    if( MURT == &mURT2 )
    {
        Serial2.IrqRecvHandler();
    }

#if defined(URT3)
    if( MURT == &mURT3 )
    {
        Serial3.IrqRecvHandler();
    }
#endif

    if( MURT == &mURT4 )
    {
        Serial4.IrqRecvHandler();
    }

    if( MURT == &mURT5 )
    {
        Serial5.IrqRecvHandler();
    }

    if( MURT == &mURT6 )
    {
        Serial6.IrqRecvHandler();
    }

    if( MURT == &mURT7 )
    {
        Serial7.IrqRecvHandler();
    }
}


extern "C" {

int DEG_printHex(  uint32_t uc_data   )
{
    return Serial.printHex(uc_data);
}

int DEG_printDec(  uint32_t uc_data   )
{
    return Serial.printDec(uc_data);
}
int DEG_print(  char* str   )
{
    return Serial.print(str);
}




#define   MAX_REGISTER_CNT        64

uint32_t   g_TRegStrPoint = 0;
uint32_t   g_TRegEndPoint = 0;
uint32_t   g_TRegCnt = 0;

uint32_t   g_TRegister[ MAX_REGISTER_CNT ] = {0};


void TestReg_clear()
{
    uint32_t   i;
    
    g_TRegStrPoint = 0;
    g_TRegEndPoint = 0;
    g_TRegCnt = 0;

    for( i=0;  i<MAX_REGISTER_CNT;  i++ )
    {
        g_TRegister[ (g_TRegStrPoint+i)%MAX_REGISTER_CNT ] = 0;
    }
}

int TestReg_push( uint32_t data )
{
    g_TRegister[ g_TRegEndPoint ] = data;

    g_TRegEndPoint++;
    g_TRegEndPoint = (g_TRegEndPoint % MAX_REGISTER_CNT);
    g_TRegCnt++;

    if( g_TRegCnt >= MAX_REGISTER_CNT  )
    {
        g_TRegStrPoint++;
        g_TRegStrPoint  = (g_TRegStrPoint % MAX_REGISTER_CNT);
    }
    return g_TRegEndPoint;
}

int TestReg_print()
{
    uint32_t   iloop;
    uint32_t   i;

    DEG_print( (char*)"\r\n" );

    DEG_print( (char*)"Register Cnt：");
    DEG_print( (char*)".[");
    DEG_printDec( g_TRegCnt );
    DEG_print( (char*)"].");
    DEG_print( (char*)"\r\n");
        
    DEG_print( (char*)"\r\n" );
    if( MAX_REGISTER_CNT < g_TRegCnt )
    {
        iloop = MAX_REGISTER_CNT;
    }
    else 
    {
        iloop = g_TRegCnt;
    }
    
    for( i=0;  i<iloop;  i++ )
    {
        DEG_print( (char*)"Register ");
        DEG_printDec( i );
        DEG_print( (char*)".[0x");
        DEG_printHex( g_TRegister[ (g_TRegStrPoint+i)%MAX_REGISTER_CNT ] );
        DEG_print( (char*)"].");
        DEG_print( (char*)"\r\n");
    }
    
    DEG_print( (char*)"\r\n");
    
//    g_TRegCnt = 0;

    return g_TRegStrPoint;
}




}