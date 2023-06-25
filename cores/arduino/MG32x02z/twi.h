
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

#ifndef __TWI_H__
#define __TWI_H__


#include "Arduino.h"
#include <inttypes.h>
//#include "Stream.h"
#include "MG32x02z_I2C_MID.h"
#include "MG32x02z_CSC_MID.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @brief I2C timout in tick unit
#define I2C_TIMEOUT_TICK        500

#define I2C_TXRX_BUFFER_SIZE    32

#define SLAVE_MODE_TRANSMIT     0
#define SLAVE_MODE_RECEIVE      1



typedef enum
{
    I2C_0 = 0,
    I2C_1 = 1,
    NB_I2C_INSTANCES = 2
}i2c_instance_e;



typedef struct _twiPinDescription
{
    uint16_t        arduino_id;
    uint16_t        AFS;
} twiPinDescription;



typedef enum
{
    I2C_OK = 0,
    I2C_TIMEOUT = 1,
    I2C_ERROR = 2,
    I2C_BUSY = 3
}i2c_status_e;




typedef struct i2c_s i2c_t;
struct i2c_s
{
    uint8_t              init_done;
    I2C_HandleTypeDef    i2c_handle;
    I2C_Struct           *i2c_instance;
    IRQn_Type            irq;

    void (*i2c_clock_init)(void);
    void (*i2c_scl_clock_init)(void);
    void (*i2c_sda_clock_init)(void);
    void (*i2c_clock_deinit)(void);
    void (*i2c_scl_clock_deinit)(void);
    void (*i2c_sda_clock_deinit)(void);
    void (*i2c_force_reset)(void);
    void (*i2c_release_reset)(void);

    uint32_t sda_reuse;
    twiPinDescription   *sdaReuseTable;
    uint32_t sda_pin;
    uint32_t scl_reuse;
    twiPinDescription   *sclReuseTable;
    uint32_t scl_pin;

    void (*i2c_onSlaveReceive)(  i2c_instance_e, uint8_t *, int);
    void (*i2c_onSlaveTransmit)( i2c_instance_e );

    uint8_t i2cTxBuffer[I2C_TXRX_BUFFER_SIZE];
    uint8_t i2cTxBufferSize;

    uint8_t i2cRxBuffer[I2C_TXRX_BUFFER_SIZE];
    uint8_t i2cRxBufferSize;

    uint8_t slaveMode;             //slave =0;
};



///@brief I2C state




/*
void i2c_init( i2c_instance_e i2c_id,
               uint32_t  scl_pin,    uint32_t  sda_pin );
*/

void i2c_custom_init( i2c_instance_e i2c_id, 
                      uint32_t  scl_pin,    uint32_t  sda_pin,
                      uint32_t  timing,     uint32_t ownAddress,  uint8_t master );

                    
void i2c_deinit( i2c_instance_e i2c_id );

void i2c_setTiming( i2c_instance_e i2c_id , uint32_t frequency );

i2c_status_e i2c_master_write( i2c_instance_e i2c_id, uint8_t dev_address,
                               uint8_t *data,                uint8_t size );
void i2c_slave_write_IT( i2c_instance_e i2c_id, uint8_t *data, uint8_t size);

i2c_status_e i2c_master_read( i2c_instance_e i2c_id, uint8_t dev_address,
                              uint8_t *data,                uint8_t size );

i2c_status_e i2c_IsDeviceReady( i2c_instance_e i2c_id, uint8_t devAddr,
                                uint32_t trials);


void i2c_attachSlaveRxEvent( i2c_instance_e i2c_id, void (*function)( i2c_instance_e, uint8_t*, int) );
void i2c_attachSlaveTxEvent( i2c_instance_e i2c_id, void (*function)( i2c_instance_e) );


extern i2c_t  g_i2c_init_info[NB_I2C_INSTANCES];




extern i2c_t  g_i2c_init_info[NB_I2C_INSTANCES];

#ifdef __cplusplus
}
#endif


#endif





