/*
  Copyright (c) 2022 megawin Technology Co., Ltd. All rights reserved.

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
/*
 * SPI Master library for arduino.
 */

#ifndef _SPI_H_
#define _SPI_H_



#include "variant.h"
#include <stdio.h>
#include "MG32x02z_SPI_MID.h"


// SPI_HAS_TRANSACTION means SPI has
//   - beginTransaction()
//   - endTransaction()
//   - usingInterrupt()
//   - SPISetting(clock, bitOrder, dataMode)
#define SPI_HAS_TRANSACTION 1

// SPI_HAS_EXTENDED_CS_PIN_HANDLING means SPI has automatic
// CS pin handling and provides the following methods:
//   - begin(pin)
//   - end(pin)
//   - setBitOrder(pin, bitorder)
//   - setDataMode(pin, datamode)
//   - setClockDivider(pin, clockdiv)
//   - transfer(pin, data, SPI_LAST/SPI_CONTINUE)
//   - beginTransaction(pin, SPISettings settings) (if transactions are available)
#define SPI_HAS_EXTENDED_CS_PIN_HANDLING 1

// For compatibility with sketches designed for AVR @ 16 MHz
// need to go from 64MHz to 16 (/4)
// New programs should use SPI.beginTransaction to set the SPI clock

#define SPI_CLOCK_DIV2	 2
#define SPI_CLOCK_DIV4	 4
#define SPI_CLOCK_DIV8	 8
#define SPI_CLOCK_DIV16	 16
#define SPI_CLOCK_DIV32	 32
#define SPI_CLOCK_DIV64	 64
#define SPI_CLOCK_DIV128 128


extern uint32_t SystemCoreClock;


#define SPI_SPEED_CLOCK_DIV2_MHZ    ((uint32_t)(SystemCoreClock/2))
#define SPI_SPEED_CLOCK_DIV4_MHZ    ((uint32_t)(SystemCoreClock/4))
#define SPI_SPEED_CLOCK_DIV8_MHZ    ((uint32_t)(SystemCoreClock/8))
#define SPI_SPEED_CLOCK_DIV16_MHZ   ((uint32_t)(SystemCoreClock/16))
#define SPI_SPEED_CLOCK_DIV32_MHZ   ((uint32_t)(SystemCoreClock/32))
#define SPI_SPEED_CLOCK_DIV64_MHZ   ((uint32_t)(SystemCoreClock/64))
#define SPI_SPEED_CLOCK_DIV128_MHZ  ((uint32_t)(SystemCoreClock/128))
#define SPI_SPEED_CLOCK_DIV256_MHZ  ((uint32_t)(SystemCoreClock/256))


//Mode          Clock Polarity (CPOL)   Clock Phase (CPHA)
//SPI_MODE0             0                     0
//SPI_MODE1             0                     1
//SPI_MODE2             1                     0
//SPI_MODE3             1                     1
#define SPI_MODE0    0x00
#define SPI_MODE1    0x01
#define SPI_MODE2    0x02
#define SPI_MODE3    0x03

enum SPITransferMode
{
    SPI_CONTINUE,
    SPI_LAST
};

class SPISettings
{
public:
    SPISettings(uint32_t clock, BitOrder bitOrder, uint8_t dataMode);
    SPISettings();    //4000000Hz

public:
    uint32_t           m_ulPin;

private:
    SPI_InitTypeDef    m_spiInit;

friend class SPIClass;
};



class SPIClass 
{
public:
    SPIClass();

    SPIClass( MID_SPI_Struct  *Instance );
    SPIClass( MID_SPI_Struct  *Instance,  
              uint32_t  pin_CLK,   uint32_t  pin_MISO,   uint32_t  pin_MOSI,
              uint32_t  pin_NSS = -1,   uint8_t   isMaster = 1 );
    
    // Transfer functions
    byte transfer(uint32_t pin_cs, uint8_t _data, SPITransferMode _mode = SPI_LAST);
    uint16_t transfer16(uint32_t pin_cs, uint16_t _data, SPITransferMode _mode = SPI_LAST);
    void transfer(uint32_t pin_cs, void *_buf, size_t _count, SPITransferMode _mode = SPI_LAST);


    // Transfer functions on default pin BOARD_SPI_DEFAULT_SS
    byte transfer(uint8_t _data, SPITransferMode _mode = SPI_LAST)
    {
        return transfer(BOARD_SPI_OWN_SS, _data, _mode);
    }

    uint16_t transfer16(uint16_t _data, SPITransferMode _mode = SPI_LAST)
    {
        return transfer16(BOARD_SPI_OWN_SS, _data, _mode);
    }

    void transfer(void *_buf, size_t _count, SPITransferMode _mode = SPI_LAST)
    {
        transfer(BOARD_SPI_OWN_SS, _buf, _count, _mode);
    }

    // Transaction Functions
    void usingInterrupt(uint8_t interruptNumber);

    void beginTransaction(SPISettings settings)
    {
        beginTransaction(BOARD_SPI_OWN_SS, settings);
    }

    void beginTransaction(uint32_t pin_cs, SPISettings settings);
    void endTransaction(void);

    // SPI Configuration methods
    void attachInterrupt(void);
    void detachInterrupt(void);

    void begin(void);
    void end(void);

    // Attach/Detach pin to/from SPI controller
    void begin(uint32_t pin_cs);
    void end(uint32_t pin_cs);

    // These methods sets a parameter on a single pin
    void setBitOrder(uint32_t pin_cs, BitOrder bitOrder);
    void setDataMode(uint32_t pin_cs, uint8_t _mode);
    void setClock(uint32_t pin_cs, uint32_t clock);
    void setClockDivider(uint32_t pin_cs, uint8_t _divider);

    // These methods sets the same parameters but on default pin BOARD_SPI_OWN_SS
    void setBitOrder(BitOrder _order)
    {
        setBitOrder(BOARD_SPI_OWN_SS, _order);
    };

    void setDataMode(uint8_t _mode) 
    { 
        setDataMode(BOARD_SPI_OWN_SS, _mode); 
    };

    void setClockDivider(uint8_t _div)
    { 
        setClockDivider(BOARD_SPI_OWN_SS, _div); 
    };

private:
    void setInit();
    void pinInit();

  
public:
    uint16_t     m_pin_CLK;
    uint16_t     m_pin_MISO;
    uint16_t     m_pin_MOSI;
    uint16_t     m_pin_NSS;

private:
    SPISettings        m_spiSettings;

    SPI_HandleTypeDef  m_SPI;
    uint32_t           m_isMaster;
    uint32_t           m_active_flg;
};

#if SPI_INTERFACES_COUNT > 0
extern SPIClass SPI;
#endif





#endif







