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
 * I2C library for arduino.
 */
#ifndef _WIRE_H_
#define _WIRE_H_


#include "Stream.h"
#include "Arduino.h"
#include <inttypes.h>
#include "Stream.h"
#include "twi.h"
#include "Print.h"
#include "MG32x02z_I2C_MID.h"
#include "MG32x02z_CSC_MID.h"

#define BUFFER_LENGTH 32

#define MASTER_ADDRESS  0x33
#define SLAVE_ADDRESS   0x55


class TwoWire : public Stream
{
public:
    uint32_t         m_MaseterAddr;
    uint32_t         m_SlaveAddr;

    void setMaseterAddr( uint8_t MasterAddress );
    void setSlaveAddr( uint8_t SlaveAddress );


public:
    TwoWire( i2c_instance_e i2c_instance );
    TwoWire( i2c_instance_e i2c_instance, uint32_t  scl_pin,  uint32_t  sda_pin);


private:
//    I2C_HandleTypeDef       mI2C;
//    i2c_t           m_I2C;

    i2c_instance_e   m_i2c_instance;
    uint32_t         m_scl_pin;
    uint32_t         m_sda_pin;

    
    uint8_t rxBuffer[BUFFER_LENGTH];
    uint8_t rxBufferIndex;
    uint8_t rxBufferLength;

    uint8_t txAddress;
    uint8_t txBuffer[BUFFER_LENGTH];
    uint8_t txBufferIndex;
    uint8_t txBufferLength;

    uint8_t transmitting;

    uint8_t ownAddress;
    bool    master;
    

    void (*user_onRequest)(void);
    void (*user_onReceive)(int);
    static void onRequestService( i2c_instance_e );
    static void onReceiveService( i2c_instance_e , uint8_t*, int);

public:
    void begin( );
    void begin( uint8_t address );
    void begin(int address );
    
    
    void begin( uint32_t  scl_pin,  uint32_t  sda_pin);
    void begin(uint8_t address, uint32_t  scl_pin,  uint32_t  sda_pin);
    void begin(int address, uint32_t  scl_pin,  uint32_t  sda_pin);
 
    void end();
    void setClock(uint32_t);
    void beginTransmission(uint8_t);
    void beginTransmission(int);
    uint8_t endTransmission(void);
    uint8_t endTransmission(uint8_t);
    uint8_t requestFrom(uint8_t, uint8_t);
    uint8_t requestFrom(uint8_t, uint8_t, uint8_t);
    uint8_t requestFrom(uint8_t, uint8_t, uint32_t, uint8_t, uint8_t);
    uint8_t requestFrom(int, int);
    uint8_t requestFrom(int, int, int);
    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *data);
    virtual size_t write(const uint8_t *, size_t);
    virtual int available(void);
    virtual int read(void);
    virtual int peek(void);
    virtual void flush(void);
    void onReceive( void (*)(int) );
    void onRequest( void (*)(void) );

    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
    using  Print::write;


};


extern TwoWire Wire;


#if !defined(MG32_2ND)
extern TwoWire Wire1;
#endif


#endif

