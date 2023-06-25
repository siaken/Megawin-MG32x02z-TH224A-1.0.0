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

#ifndef _UART_CLASS_
#define _UART_CLASS_

//#include "variant.h"
#include "HardwareSerial.h"
#include "chip.h"
#include "uart.h"

#ifdef __cplusplus

#ifdef SERIAL_BUFFER_SIZE
#undef SERIAL_BUFFER_SIZE
#endif

#define SERIAL_BUFFER_SIZE  256

class Uart : public  HardwareSerial
{
public:
  	//Uart(uart_id_e uart_id);
    Uart( );
    Uart( URT_HandleTypeDef *uartdef);
    Uart( URT_HandleTypeDef *uartdef,  uint16_t  RxPin,  uint16_t  TxPin,  IRQn_Type  irqn);

    void begin( unsigned long baudRate );
    
    int begin(  uint16_t   ArdRxPin,      uint16_t   ArdTxPin,   unsigned long baudRate);
    int begin(  URT_HandleTypeDef        *uartdef,
                uint16_t   ArdRxPin,      uint16_t   ArdTxPin,
                IRQn_Type      irqn,      unsigned long baudRate);

    void end(void);
    int available(void);
    int availableForWrite(void);
    int peek(void);
    int read(void);
    void flush(void);
    size_t write(uint8_t data);
    using Print::write; // pull in write(str) and write(buf, size) from Print

    int printHex(uint32_t uc_data );
    int printDec(uint32_t uc_data );

    void IrqTransHandler(void);
    void IrqRecvHandler(void);

    operator bool() { return true; }

    //serialEvent() doesn’t work on the board
/*
private:
    int SetPin( URT_HandleTypeDef *uartdef,
                uint16_t   ArdRxPin,       uint16_t   ArdTxPin  );
*/
private:
        URT_HandleTypeDef    *m_usart_typedef;
        IRQn_Type             m_irqtype;

        uint16_t              m_tx_pin;
        uint16_t              m_tx_pinAFS;
        uint16_t              m_rx_pin;
        uint16_t              m_rx_pinAFS;

        uint8_t   m_rxpData[SERIAL_BUFFER_SIZE];
        uint32_t  m_rxData_Count;
        uint8_t   m_rxBegin;
        uint8_t   m_rxEnd;

        uint8_t   m_txBuffer[SERIAL_BUFFER_SIZE];
        uint32_t  m_txData_Count;
        uint8_t   m_txBegin;
        uint8_t   m_txEnd;
        uint8_t   m_txflag;
        
        uint8_t   m_rxdata[4];
        uint8_t   m_txdata[4];
};


extern URT_HandleTypeDef        mURT0;
extern URT_HandleTypeDef        mURT1;
extern URT_HandleTypeDef        mURT2;
extern URT_HandleTypeDef        mURT3;
extern URT_HandleTypeDef        mURT4;
extern URT_HandleTypeDef        mURT5;
extern URT_HandleTypeDef        mURT6;
extern URT_HandleTypeDef        mURT7;

#endif

#ifdef __cplusplus
 extern "C" {
#endif

size_t uart_write( uart_id_e uart_id, uint8_t data );


int DEG_printHex(  uint32_t uc_data   );
int DEG_printDec(  uint32_t uc_data   );
int DEG_print(  char* str   );


#ifdef __cplusplus
}
#endif



#ifdef __cplusplus

extern Uart Serial0;
extern Uart Serial1;
extern Uart Serial2;
extern Uart Serial4;
extern Uart Serial5;
extern Uart Serial6;
extern Uart Serial7;

#endif



#endif // _UART_CLASS_

