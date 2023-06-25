
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
 
 /*
#define __DRV_I2C_SCLS_EN(__HANDLE__)                           ((__HANDLE__)->Instance->CR0.W &= (~I2C_CR0_SCLS_DIS_mask_w))
#define __DRV_I2C_SCLS_DIS(__HANDLE__)                           ((__HANDLE__)->Instance->CR0.W |= I2C_CR0_SCLS_DIS_mask_w)


#define __DRV_I2C_SFBD_DIS(__HANDLE__)                           ((__HANDLE__)->Instance->CR0.W &= (~I2C_CR0_SFBD_EN_mask_w))
#define __DRV_I2C_SFBD_EN(__HANDLE__)                           ((__HANDLE__)->Instance->CR0.W |= I2C_CR0_SFBD_EN_mask_w)


#define __DRV_I2C_TMO_MDS(__HANDLE__)                          ((__HANDLE__)->Instance->TMOUT.MBIT.TMO_MDS = 1)

*/



#include "Arduino.h"
#include "variant.h"
#include "twi.h"
#include "MG32x02z_I2C_MID.h"
#include "MG32x02z_CSC_MID.h"
#include "MG32x02z_ADC_MID.h"
#include "MG32x02z_RST_MID.h"
#include "MG32x02z_Common_MID.h"
#include "MG32x02z_cortex_MID.h"
#include "MG32x02z_EXIC.h"
#include "MG32x02z_DRV.h"


#ifdef __cplusplus
 extern "C" {
#endif

#ifdef  MG32F02U128
/*
PA8 
I2C0_SCL,
PA8_AFS_I2C0_SCL
PA9
I2C1_SCL,
PA9_AFS_I2C1_SCL
PA10
I2C0_SDA
PA10_AFS_I2C0_SDA
PA11
I2C1_SDA,
PA11_AFS_I2C1_SDA

PB0
I2C1_SCL,
PB0_AFS_I2C1_SCL
PB1
I2C1_SDA,
PB1_AFS_I2C1_SDA

PB2
I2C0_SDA,
PB2_AFS_I2C0_SDA
PB3
I2C0_SCL,
PB3_AFS_I2C0_SCL

PC0
I2C0_SCL,
PC0_AFS_I2C0_SCL
PC1
I2C0_SDA,
PC1_AFS_I2C0_SDA

PC4
I2C0_SCL,
PC4_AFS_I2C0_SCL
PC5
I2C0_SDA,
PC5_AFS_I2C0_SDA

PC8
I2C0_SCL,
PC8_AFS_I2C0_SCL
PC9
I2C0_SDA,
PC9_AFS_I2C0_SDA

PC10
I2C1_SCL,
PC10_AFS_I2C1_SCL
PC11
I2C1_SDA,
PC11_AFS_I2C1_SDA
*/


#define I2C0_PIN_REUSE     6
#define I2C1_PIN_REUSE     3



#define  TWTPIN_AFS_CFG(a, num, afs)      .arduino_id=((uint16_t)MCU_##a##num), .AFS=a##num##_AFS_##afs

twiPinDescription   pin_i2c0_scl[I2C0_PIN_REUSE] = 
{
  {  TWTPIN_AFS_CFG(PA, 8, I2C0_SCL) },
  {  TWTPIN_AFS_CFG(PB, 3, I2C0_SCL) },
  {  TWTPIN_AFS_CFG(PB, 10, I2C0_SCL) },
  {  TWTPIN_AFS_CFG(PC, 0, I2C0_SCL) },
  {  TWTPIN_AFS_CFG(PC, 4, I2C0_SCL) },
  {  TWTPIN_AFS_CFG(PC, 8, I2C0_SCL) },
};


twiPinDescription   pin_i2c0_sda[I2C0_PIN_REUSE] = 
{
  {  TWTPIN_AFS_CFG(PA, 10,  I2C0_SDA) },
  {  TWTPIN_AFS_CFG(PB, 2,   I2C0_SDA) },
  {  TWTPIN_AFS_CFG(PB, 11,  I2C0_SDA) },
  {  TWTPIN_AFS_CFG(PC, 1,   I2C0_SDA) },
  {  TWTPIN_AFS_CFG(PC, 5,   I2C0_SDA) },
  {  TWTPIN_AFS_CFG(PC, 9,   I2C0_SDA) },
};


twiPinDescription   pin_i2c1_scl[I2C1_PIN_REUSE] = 
{
  {  TWTPIN_AFS_CFG(PA, 9,   I2C1_SCL) },
  {  TWTPIN_AFS_CFG(PB, 0,   I2C1_SCL) },
  {  TWTPIN_AFS_CFG(PC, 10,  I2C1_SCL) },
};




twiPinDescription   pin_i2c1_sda[I2C1_PIN_REUSE] = 
{
  {  TWTPIN_AFS_CFG(PA, 11,  I2C1_SDA) },
  {  TWTPIN_AFS_CFG(PB, 1,   I2C1_SDA) },
  {  TWTPIN_AFS_CFG(PC, 11,  I2C1_SDA) },

};

#endif





void i2c0_clk_enable(void)      { __DRV_CSC_I2C0_CLK_ENABLE();    }
void i2c0_scl_clk_enable(void)  { __DRV_CSC_GPIOB_CLK_ENABLE();   }
void i2c0_sda_clk_enable(void)  { __DRV_CSC_GPIOB_CLK_ENABLE();   }
void i2c0_clk_disable(void)     { __DRV_CSC_I2C0_CLK_DISABLE();   }
void i2c0_scl_clk_disable(void) { __DRV_CSC_GPIOB_CLK_DISABLE();  }
void i2c0_sda_clk_disable(void) { __DRV_CSC_GPIOB_CLK_DISABLE();  }
void i2c0_force_reset(void)     { __DRV_RST_I2C0_FORCE_RESET();   }
void i2c0_release_reset(void)   { __DRV_RST_I2C0_RELEASE_RESET(); }



void i2c1_clk_enable(void)      { __DRV_CSC_I2C1_CLK_ENABLE();    }
void i2c1_scl_clk_enable(void)  { __DRV_CSC_GPIOB_CLK_ENABLE();   }
void i2c1_sda_clk_enable(void)  { __DRV_CSC_GPIOB_CLK_ENABLE();   }
void i2c1_clk_disable(void)     { __DRV_CSC_I2C1_CLK_DISABLE();   }
void i2c1_scl_clk_disable(void) { __DRV_CSC_GPIOA_CLK_DISABLE(); __DRV_CSC_GPIOB_CLK_DISABLE();  }
void i2c1_sda_clk_disable(void) { __DRV_CSC_GPIOB_CLK_DISABLE();  }
void i2c1_force_reset(void)     { __DRV_RST_I2C1_FORCE_RESET();   }
void i2c1_release_reset(void)   { __DRV_RST_I2C1_RELEASE_RESET(); }  

#ifdef  MG32F02U128
i2c_t  g_i2c_init_info[NB_I2C_INSTANCES] =
{
    {
        .init_done = 0,
        .i2c_instance = I2C0,
        .irq = I2C0_IRQn,
        .i2c_clock_init = i2c0_clk_enable,
        .i2c_scl_clock_init = i2c0_scl_clk_enable,
        .i2c_sda_clock_init = i2c0_sda_clk_enable,
        .i2c_clock_deinit = i2c0_clk_disable,
        .i2c_scl_clock_deinit = i2c0_scl_clk_disable,
        .i2c_sda_clock_deinit = i2c0_sda_clk_disable,
        .i2c_force_reset   = i2c0_force_reset,
        .i2c_release_reset = i2c0_release_reset,

        .sdaReuseTable = pin_i2c0_sda,
        .sda_reuse = I2C0_PIN_REUSE,
        .sda_pin = MCU_PA10,
        .sclReuseTable = pin_i2c0_scl,
        .scl_reuse = I2C0_PIN_REUSE,
        .scl_pin = MCU_PA8,
        
        .i2c_onSlaveReceive = NULL,
        .i2c_onSlaveTransmit = NULL,
        .i2cTxBufferSize = 0,
        .i2cRxBufferSize = 0,
        .slaveMode        = SLAVE_MODE_RECEIVE
    },


    {
        .init_done = 0,
        .i2c_instance = I2C1,
        .irq = I2Cx_IRQn,
        .i2c_clock_init = i2c1_clk_enable,
        .i2c_scl_clock_init = i2c1_scl_clk_enable,
        .i2c_sda_clock_init = i2c1_sda_clk_enable,
        .i2c_clock_deinit = i2c1_clk_disable,
        .i2c_scl_clock_deinit = i2c1_scl_clk_disable,
        .i2c_sda_clock_deinit = i2c1_sda_clk_disable,
        .i2c_force_reset = i2c1_force_reset,
        .i2c_release_reset = i2c1_release_reset,

        .sdaReuseTable = pin_i2c1_sda,
        .sda_reuse = I2C1_PIN_REUSE,
        .sda_pin   = MCU_PA11,
        .sclReuseTable = pin_i2c1_scl,
        .scl_reuse = I2C1_PIN_REUSE,
        .scl_pin   = MCU_PA9,

        .i2c_onSlaveReceive = NULL,
        .i2c_onSlaveTransmit = NULL,
        .i2cTxBufferSize = 0,
        .i2cRxBufferSize = 0,
        .slaveMode        = SLAVE_MODE_RECEIVE
    },
};
#endif


extern MID_StatusTypeDef I2C_Slave_ISR_IT(struct tag_I2C_HandleTypeDef *mI2C, uint32_t ITFlags, uint32_t ITSources);

uint32_t i2c_findpin( twiPinDescription *table,  uint32_t cnt,  uint32_t pin )
{
    uint32_t i = -1;

    for(i=0; i<cnt; i++)
    {
        if( pin == table[i].arduino_id )
        {
            return i;
        }
    }

    return ((uint32_t)-1);
}

/**
  * @brief  Checks if target device is ready for communication
  * @param  i2c_id : i2c instance to use
  * @param  devAddr: specifies the address of the device.
  * @param  trials : Number of trials.
  * @retval status
  */
i2c_instance_e i2c_InstanceToId(I2C_HandleTypeDef *hi2c)
{
    int i = 0;

    for(i=0;i<NB_I2C_INSTANCES;i++)
    {
        if( hi2c == &g_i2c_init_info[i].i2c_handle )
        {
            return i;
        }
    }

    return NB_I2C_INSTANCES;
}


/*
static I2C_HandleTypeDef       mI2C0;
static I2C_HandleTypeDef       mI2C1;
*/



/**
  * @brief  Initialize and setup GPIO and I2C peripheral
  * @param  i2c_id : i2c instance to use
  * @param  timing : one of the i2c_timing_e
  * @param  addressingMode : I2C_ADDRESSINGMODE_7BIT or I2C_ADDRESSINGMODE_10BIT
  * @param  ownAddress : device address
  * @param  master : set to 1 to choose the master mode
  * @retval none
  */
void i2c_custom_init( i2c_instance_e i2c_id, 
                      uint32_t  scl_pin,    uint32_t  sda_pin,
                      uint32_t  timing,     uint32_t ownAddress,  uint8_t master )
{
    uint32_t  idx_scl;
    uint32_t  idx_sda;
    Pin_Struct*  pPinx;		
    GPIO_InitTypeDef GPIOX;

    if( I2C_0 == i2c_id )
    {
        //==Set I2C0 Clock
        UnProtectModuleReg(CSCprotect);
        CSC_PeriphProcessClockSource_Config(CSC_I2C0_CKS, CK_APB);
        CSC_PeriphOnModeClock_Config(CSC_ON_I2C0, ENABLE);					  // Enable IIC0 module clock
        CSC_PeriphOnModeClock_Config(CSC_ON_PortB, ENABLE);					  // Enable PortB module clock
        ProtectModuleReg(CSCprotect);
    }
    
    if( I2C_1 == i2c_id )
    {
        //==Set I2C1 Clock
        UnProtectModuleReg(CSCprotect);
        CSC_PeriphProcessClockSource_Config(CSC_I2C1_CKS, CK_APB);
        CSC_PeriphOnModeClock_Config(CSC_ON_I2C1, ENABLE);					  // Enable IIC0 module clock
        CSC_PeriphOnModeClock_Config(CSC_ON_PortC, ENABLE);					  // Enable PortB module clock
        ProtectModuleReg(CSCprotect);
    }

    if( i2c_id >= NB_I2C_INSTANCES )
    {
        return;
    }

    //if( g_i2c_init_info[i2c_id].init_done == 0 )    //允许重新配置
    {
        g_i2c_init_info[i2c_id].i2c_scl_clock_init();
        g_i2c_init_info[i2c_id].i2c_sda_clock_init();

        idx_scl = i2c_findpin( g_i2c_init_info[i2c_id].sclReuseTable,  g_i2c_init_info[i2c_id].scl_reuse,  scl_pin );
        if( idx_scl == ((uint32_t)-1) )
        {
            return;
        }

        idx_sda = i2c_findpin( g_i2c_init_info[i2c_id].sdaReuseTable,  g_i2c_init_info[i2c_id].sda_reuse,  sda_pin );
        if( idx_scl == ((uint32_t)-1) )
        {
            return;
        }

        g_i2c_init_info[i2c_id].scl_pin  = scl_pin;
        g_i2c_init_info[i2c_id].sda_pin  = sda_pin;

        //SCL
        GPIOX.Mode = GPIO_MODE_OPENDRAIN_O;
        GPIOX.Pull = GPIO_PULLUP;

        GPIOX.Pin            = g_APinDescription[scl_pin].GioPin;
        GPIOX.Speed          = GPIO_SPEED_HIGH;
        GPIOX.OUTDrive       = GPIO_OUTDRIVE_LEVEL0;
        GPIOX.FilterDivider  = GPIO_FILTERDIVIDER_BYPASS;
        GPIOX.Inverse        = GPIO_INVERSE_DISABLE;
        GPIOX.Alternate      = g_i2c_init_info[i2c_id].sclReuseTable[idx_scl].AFS;
        pPinx = __GetPinxx_byGPIOx( g_APinDescription[scl_pin].ulPort, g_APinDescription[scl_pin].PinNum );
        MID_GPIO_Pin_Init(  pPinx,  &GPIOX);

        //SDA
        GPIOX.Mode = GPIO_MODE_OPENDRAIN_O;
        GPIOX.Pull = GPIO_NOPULLUP;

        GPIOX.Pin            = g_APinDescription[sda_pin].GioPin;
        GPIOX.Speed          = GPIO_SPEED_HIGH;
        GPIOX.OUTDrive       = GPIO_OUTDRIVE_LEVEL0;
        GPIOX.FilterDivider  = GPIO_FILTERDIVIDER_BYPASS;
        GPIOX.Inverse        = GPIO_INVERSE_DISABLE;
        GPIOX.Alternate      = g_i2c_init_info[i2c_id].sdaReuseTable[idx_sda].AFS;
        pPinx = __GetPinxx_byGPIOx( g_APinDescription[sda_pin].ulPort, g_APinDescription[sda_pin].PinNum );
        MID_GPIO_Pin_Init(  pPinx,  &GPIOX);

        g_i2c_init_info[i2c_id].i2c_handle.Instance = g_i2c_init_info[i2c_id].i2c_instance;
        g_i2c_init_info[i2c_id].i2c_handle.Init.Timing = MID_I2C_GetInitTiming(&(g_i2c_init_info[i2c_id].i2c_handle), timing);

        g_i2c_init_info[i2c_id].i2c_handle.Init.OwnAddress1 = ownAddress;
        #if !defined(MG32_1ST)
            g_i2c_init_info[i2c_id].i2c_handle.Init.OwnAddress1Masks = I2C_OA1_NOMASK;
        #endif
        g_i2c_init_info[i2c_id].i2c_handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;

        g_i2c_init_info[i2c_id].i2c_handle.Init.OwnAddress2 = 0x23;
        g_i2c_init_info[i2c_id].i2c_handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;

        //starting I2C
        g_i2c_init_info[i2c_id].i2c_clock_init();
        g_i2c_init_info[i2c_id].i2c_force_reset();
        g_i2c_init_info[i2c_id].i2c_release_reset();

        if(master == 0) 
        {
            NVIC_SetPriority( g_i2c_init_info[i2c_id].irq,   1);
            NVIC_EnableIRQ( g_i2c_init_info[i2c_id].irq );
        }

        MID_I2C_Init( &(g_i2c_init_info[i2c_id].i2c_handle) );

        MID_I2CEx_ConfigPreDriveTime( &(g_i2c_init_info[i2c_id].i2c_handle), I2C_PDT_1T);

        g_i2c_init_info[i2c_id].init_done  = 1;
    }
}


/**
  * @brief  Default init and setup GPIO and I2C peripheral
  * @param  i2c_id : i2c instance to use
  * @retval none
*/
/*
void i2c_init( i2c_instance_e i2c_id,
               uint32_t  scl_pin,    uint32_t  sda_pin )
{
    i2c_custom_init( i2c_id,
                     scl_pin,  sda_pin,
                     100000,   0x33,    1);
}
*/


void i2c_deinit( i2c_instance_e i2c_id )
{
    if( i2c_id >= NB_I2C_INSTANCES )
    {
        return;
    }

    if(g_i2c_init_info[i2c_id].init_done == 1)
    {
        g_i2c_init_info[i2c_id].i2c_scl_clock_deinit();
        g_i2c_init_info[i2c_id].i2c_sda_clock_deinit();
        g_i2c_init_info[i2c_id].i2c_clock_deinit();

        NVIC_DisableIRQ( g_i2c_init_info[i2c_id].irq );

        MID_I2C_DeInit( &g_i2c_init_info[i2c_id].i2c_handle );

        g_i2c_init_info[i2c_id].init_done = 0;
    }
}

void i2c_setTiming( i2c_instance_e i2c_id , uint32_t frequency )
{
    if( i2c_id >= NB_I2C_INSTANCES )
    {
        return;
    }

    if(g_i2c_init_info[i2c_id].init_done == 1)
    {
        MID_I2CEx_DisableWakeUp(&g_i2c_init_info[i2c_id].i2c_handle);

        g_i2c_init_info[i2c_id].i2c_handle.Init.Timing = MID_I2C_GetInitTiming(&(g_i2c_init_info[i2c_id].i2c_handle), frequency);

        MID_I2C_Init(&g_i2c_init_info[i2c_id].i2c_handle);

        MID_I2CEx_DisableWakeUp( &g_i2c_init_info[i2c_id].i2c_handle );
    }
}


/**
  * @brief  Write bytes to master
  * @param  i2c_id : i2c instance to use
  * @param  data: pointer to data to be write
  * @param  size: number of bytes to be write.
  * @retval none
  */
void i2c_slave_write_IT(i2c_instance_e i2c_id, uint8_t *data, uint8_t size)
{
    int i = 0;
    
    if(  (g_i2c_init_info[i2c_id].i2cTxBufferSize + size) > I2C_TXRX_BUFFER_SIZE )
    {
        size = I2C_TXRX_BUFFER_SIZE - g_i2c_init_info[i2c_id].i2cTxBufferSize;
    }

/*
    uint8_t Str = g_i2c_init_info[i2c_id].i2cTxBufferSize;
    if( Str < I2C_TXRX_BUFFER_SIZE )
    {
        if( (Str + size) >= I2C_TXRX_BUFFER_SIZE )
        {
            size = I2C_TXRX_BUFFER_SIZE - Str;
        }
    }
    else
    {
        g_i2c_init_info[i2c_id].i2cTxBufferSize = I2C_TXRX_BUFFER_SIZE;
        Str = I2C_TXRX_BUFFER_SIZE;
        size = 0;
        return
    }
*/

    if(g_i2c_init_info[i2c_id].init_done == 1) 
    {
        // Check the communication status
        for(i = 0; i < size; i++)
        {
            g_i2c_init_info[i2c_id].i2cTxBuffer[ (g_i2c_init_info[i2c_id].i2cTxBufferSize + i) ] = *(data+i);
        }
        
        g_i2c_init_info[i2c_id].i2cTxBufferSize =  g_i2c_init_info[i2c_id].i2cTxBufferSize + size;
    }
}



/**
  * @brief  read bytes in master mode at a given address
  * @param  i2c_id : i2c instance to use
  * @param  dev_address: specifies the address of the device.
  * @param  data: pointer to data to be read
  * @param  size: number of bytes to be read.
  * @retval read status
  */
i2c_status_e i2c_master_read(i2c_instance_e i2c_id, uint8_t dev_address,
                              uint8_t *data, uint8_t size)
{
    i2c_status_e ret = I2C_ERROR;

// __DRV_I2C_SCLS_EN( &(g_i2c_init_info[i2c_id].i2c_handle) );

    if(g_i2c_init_info[i2c_id].init_done == 1) {

    if( MID_I2C_Master_Receive( &(g_i2c_init_info[i2c_id].i2c_handle),   dev_address, data, size,
                                I2C_TIMEOUT_TICK) == MID_OK )
    {
        ret = I2C_OK;
    }

    }
    return ret;
}

/**
  * @brief  Write bytes at a given address
  * @param  i2c_id : i2c instance to use
  * @param  dev_address: specifies the address of the device.
  * @param  data: pointer to data to be write
  * @param  size: number of bytes to be write.
  * @retval read status
  */
i2c_status_e i2c_master_write( i2c_instance_e i2c_id, uint8_t dev_address,
                               uint8_t *data,         uint8_t size )
{
    i2c_status_e ret = I2C_ERROR;
    MID_StatusTypeDef status = MID_OK;

    if( i2c_id >= NB_I2C_INSTANCES )
    {
        return ret;
    }
  
    if(g_i2c_init_info[i2c_id].init_done == 1)
    {
        // Check the communication status
        status = MID_I2C_Master_Transmit( &(g_i2c_init_info[i2c_id].i2c_handle), dev_address,
                                          data,    size,     I2C_TIMEOUT_TICK  );
        if(status == MID_OK)
        {
            ret = I2C_OK;
        }
        else if(status == MID_TIMEOUT)
        {
            ret = I2C_TIMEOUT;
        }
        else
        {
            ret = I2C_ERROR;
        }
    }

    return ret;
}




/**
  * @brief  Checks if target device is ready for communication
  * @param  i2c_id : i2c instance to use
  * @param  devAddr: specifies the address of the device.
  * @param  trials : Number of trials.
  * @retval status
  */
i2c_status_e i2c_IsDeviceReady( i2c_instance_e i2c_id, uint8_t devAddr,
                                uint32_t trials)
{
    i2c_status_e ret = HAL_OK;
    if( MID_I2C_IsDeviceReady( &(g_i2c_init_info[i2c_id].i2c_handle), devAddr,
                                trials, I2C_TIMEOUT_TICK)!=MID_OK) 
    {
        ret = I2C_BUSY;
    }
    return ret;
}






/** @brief  sets function called before a slave read operation
  * @param  i2c_id : i2c instance to use
  * @param  function: callback function to use
  * @retval None
  */

void i2c_attachSlaveRxEvent( i2c_instance_e i2c_id, void (*function)(i2c_instance_e, uint8_t*, int) )
{
    if(g_i2c_init_info[i2c_id].init_done == 1)
    {
        g_i2c_init_info[i2c_id].i2c_onSlaveReceive = function;

        g_i2c_init_info[ i2c_id ].slaveMode = SLAVE_MODE_RECEIVE;
        
//======================================20230509=============================================================================================
        /* Disable All Interrupt */
        __DRV_I2C_DISABLE_IT( &(g_i2c_init_info[i2c_id].i2c_handle),   I2C_IT_ERR | I2C_IT_BUF | I2C_IT_EVENT); // Disable Interrupt

        /* Clear I2C Flag */
        __DRV_I2C_CLEAR_FLAG( &(g_i2c_init_info[i2c_id].i2c_handle), (I2C_FLAG_NACK | I2C_FLAG_ALOS | I2C_FLAG_BERR | I2C_FLAG_ROVR | I2C_FLAG_TOVR | I2C_FLAG_STOP | I2C_FLAG_RSTR));

        g_i2c_init_info[i2c_id].i2c_handle.ErrorCode = MID_I2C_ERROR_NONE;
        g_i2c_init_info[i2c_id].i2c_handle.State |= MID_I2C_STATE_BUSY_RX;
        g_i2c_init_info[i2c_id].i2c_handle.Mode   = MID_I2C_MODE_SLAVE;

        g_i2c_init_info[i2c_id].i2cRxBufferSize = 0;

        g_i2c_init_info[i2c_id].i2c_handle.DevAddress = 0;
        g_i2c_init_info[i2c_id].i2c_handle.pBuffPtr = g_i2c_init_info[i2c_id].i2cRxBuffer;
        g_i2c_init_info[i2c_id].i2c_handle.XferSize = I2C_TXRX_BUFFER_SIZE;
        g_i2c_init_info[i2c_id].i2c_handle.XferCount = 0;
        /* Enable Address Acknowledge */
        g_i2c_init_info[i2c_id].i2c_handle.Instance->CR0.W |= ( I2C_CR0_SADR_EN_mask_w
                                                              | g_i2c_init_info[i2c_id].i2c_handle.Init.DualAddressMode
                                                              | g_i2c_init_info[i2c_id].i2c_handle.Init.GeneralCallMode );
        
//===================================================================================================================================

        __DRV_I2C_STA_STO_AA_001( &(g_i2c_init_info[i2c_id].i2c_handle) );
        g_i2c_init_info[i2c_id].i2c_handle.State |= MID_I2C_STATE_LISTEN;
        g_i2c_init_info[i2c_id].i2c_handle.XferISR = I2C_Slave_ISR_IT;

        __DRV_I2C_ENABLE_IT( &(g_i2c_init_info[i2c_id].i2c_handle),   I2C_IT_ERR |I2C_IT_IEA|I2C_IT_EVENT| I2C_IT_BUF );
        
        
        MID_I2C_Slave_Receive_IT(  &(g_i2c_init_info[i2c_id].i2c_handle), 
                                   g_i2c_init_info[i2c_id].i2cRxBuffer,      I2C_TXRX_BUFFER_SIZE   );

    }
}




/** @brief  sets function called before a slave write operation
  * @param  i2c_id : i2c instance to use
  * @param  function: callback function to use
  * @retval None
  */
void i2c_attachSlaveTxEvent(i2c_instance_e i2c_id, void (*function)(i2c_instance_e) )
{
    if(g_i2c_init_info[i2c_id].init_done == 1)
    {
        g_i2c_init_info[i2c_id].i2c_onSlaveTransmit = function;
        g_i2c_init_info[ i2c_id ].slaveMode = SLAVE_MODE_RECEIVE;

//======================================20230509=============================================================================================
        /* Disable All Interrupt */
        __DRV_I2C_DISABLE_IT( &(g_i2c_init_info[i2c_id].i2c_handle),   I2C_IT_ERR | I2C_IT_BUF | I2C_IT_EVENT); // Disable Interrupt

        /* Clear I2C Flag */
        __DRV_I2C_CLEAR_FLAG( &(g_i2c_init_info[i2c_id].i2c_handle), (I2C_FLAG_NACK | I2C_FLAG_ALOS | I2C_FLAG_BERR | I2C_FLAG_ROVR | I2C_FLAG_TOVR | I2C_FLAG_STOP | I2C_FLAG_RSTR));

        g_i2c_init_info[i2c_id].i2c_handle.ErrorCode = MID_I2C_ERROR_NONE;
        g_i2c_init_info[i2c_id].i2c_handle.State |= MID_I2C_STATE_BUSY_RX;
        g_i2c_init_info[i2c_id].i2c_handle.Mode   = MID_I2C_MODE_SLAVE;

        g_i2c_init_info[i2c_id].i2cRxBufferSize = 0;

        g_i2c_init_info[i2c_id].i2c_handle.DevAddress = 0;
        g_i2c_init_info[i2c_id].i2c_handle.pBuffPtr = g_i2c_init_info[i2c_id].i2cRxBuffer;
        g_i2c_init_info[i2c_id].i2c_handle.XferSize = I2C_TXRX_BUFFER_SIZE;
        g_i2c_init_info[i2c_id].i2c_handle.XferCount = 0;
        /* Enable Address Acknowledge */
        g_i2c_init_info[i2c_id].i2c_handle.Instance->CR0.W |= ( I2C_CR0_SADR_EN_mask_w
                                                              | g_i2c_init_info[i2c_id].i2c_handle.Init.DualAddressMode
                                                              | g_i2c_init_info[i2c_id].i2c_handle.Init.GeneralCallMode );
        
//===================================================================================================================================
        __DRV_I2C_STA_STO_AA_001( &(g_i2c_init_info[i2c_id].i2c_handle) );
        g_i2c_init_info[i2c_id].i2c_handle.State |= MID_I2C_STATE_LISTEN;
        g_i2c_init_info[i2c_id].i2c_handle.XferISR = I2C_Slave_ISR_IT;
        __DRV_I2C_ENABLE_IT( &(g_i2c_init_info[i2c_id].i2c_handle),  I2C_IT_ERR | I2C_IT_IEA|I2C_IT_EVENT| I2C_IT_BUF );




        MID_I2C_Slave_Receive_IT(  &(g_i2c_init_info[i2c_id].i2c_handle), 
                                   g_i2c_init_info[i2c_id].i2cRxBuffer,      I2C_TXRX_BUFFER_SIZE   );

    }
}


/**
  * @brief  Slave Address Match callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  TransferDirection: Master request Transfer Direction (Write/Read), value of @ref I2C_XferOptions_definition
  * @param  AddrMatchCode: Address Match Code
  * @retval None
  */
extern MID_StatusTypeDef I2C_BytemodeSlaveEventHandle(I2C_HandleTypeDef *mI2C);
void MID_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
    i2c_instance_e i2c_id;
    
    i2c_id = i2c_InstanceToId(hi2c);
    if( i2c_id >= NB_I2C_INSTANCES )
    {
        return;
    }

    if(AddrMatchCode == hi2c->Init.OwnAddress1)
    {
        if(TransferDirection == I2C_DIRECTION_TRANSMIT)
        {
            if(g_i2c_init_info[ i2c_id ].i2c_onSlaveTransmit != NULL)
            {
                g_i2c_init_info[ i2c_id ].i2c_onSlaveTransmit( i2c_id );
            }

            //在中断中执行发送
            // Disable All Interrupt
            __DRV_I2C_DISABLE_IT(hi2c, I2C_IT_ERR | I2C_IT_BUF | I2C_IT_EVENT); // Disable Interrupt
            __DRV_I2C_CLEAR_FLAG(hi2c, (I2C_FLAG_NACK | I2C_FLAG_ALOS | I2C_FLAG_BERR | I2C_FLAG_ROVR | I2C_FLAG_TOVR | I2C_FLAG_STOP | I2C_FLAG_RSTR));

            hi2c->ErrorCode = MID_I2C_ERROR_NONE;
            
            hi2c->State = MID_I2C_STATE_BUSY_TX;
            hi2c->Mode = MID_I2C_MODE_SLAVE;

            /* Prepare transfer parameters */
            hi2c->DevAddress = 0;
            hi2c->pBuffPtr = g_i2c_init_info[i2c_id].i2cTxBuffer;
            hi2c->XferSize = g_i2c_init_info[i2c_id].i2cTxBufferSize;
            hi2c->XferCount = 0;
            hi2c->XferISR = I2C_Slave_ISR_IT;
            /* Enable Address Acknowledge */
            hi2c->Instance->CR0.W |= (I2C_CR0_SADR_EN_mask_w | hi2c->Init.DualAddressMode | hi2c->Init.GeneralCallMode);
            __DRV_I2C_STA_STO_AA_001(hi2c);
            __DRV_I2C_ENABLE_IT(hi2c, (I2C_IT_IEA | I2C_IT_EVENT | I2C_IT_BUF)); // Enable Interrupt

            //写数据模式---上位机
            g_i2c_init_info[ i2c_id ].i2cTxBufferSize = 0;
            g_i2c_init_info[ i2c_id ].slaveMode = SLAVE_MODE_TRANSMIT;
        }
        else
        {
            hi2c->DevAddress = 0;
            hi2c->pBuffPtr = g_i2c_init_info[ i2c_id ].i2cRxBuffer;
            hi2c->XferSize = I2C_TXRX_BUFFER_SIZE;
            hi2c->XferCount = 0;
            Set_STA_STO_AA_001( hi2c->Instance );


            //读数据模式---上位机
            g_i2c_init_info[ i2c_id ].i2cRxBufferSize = 0;
            g_i2c_init_info[ i2c_id ].slaveMode = SLAVE_MODE_RECEIVE;
          

       }
    }
}






/**
 ******************************************************************************
 * @brief  Slave Tx Transfer completed callback.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @retval None
 ******************************************************************************
 */
__weak void MID_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *mI2C)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mI2C);

  /* NOTE : This function should not be modified, when the callback is needed,
            the MID_I2C_SlaveTxCpltCallback could be implemented in the user file
  */
}

/**
 ******************************************************************************
 * @brief  Slave Rx Transfer completed callback.
 * @param  mI2C: Pointer to a I2C_HandleTypeDef structure that contains
 *               the configuration information for the specified I2C.
 * @retval None
 ******************************************************************************
 */
void MID_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *mI2C)
{
     //地址正确了进入这里
    uint8_t nbData = 0;

    i2c_instance_e i2c_id;
    
    i2c_id = i2c_InstanceToId( mI2C );
    if( i2c_id >= NB_I2C_INSTANCES )
    {
        return;
    }

    if( (g_i2c_init_info[ i2c_id ].i2c_onSlaveReceive != NULL) 
     && (g_i2c_init_info[ i2c_id ].slaveMode == SLAVE_MODE_RECEIVE) )
    {
        //nbData = I2C_TXRX_BUFFER_SIZE - g_i2c_init_info[ i2c_id ].i2c_handle.XferSize;
        
        if( mI2C->XferCount < I2C_TXRX_BUFFER_SIZE)
        {
            nbData = g_i2c_init_info[ i2c_id ].i2c_handle.XferCount;
        }
        else
        {
            nbData = I2C_TXRX_BUFFER_SIZE;
        }
        g_i2c_init_info[ i2c_id ].i2c_handle.XferCount = 0;

        if(nbData != 0)
        {
            if ( NULL != g_i2c_init_info[ i2c_id ].i2c_onSlaveReceive )
            {
                g_i2c_init_info[ i2c_id ].i2c_onSlaveReceive(  i2c_id,  g_i2c_init_info[i2c_id].i2cRxBuffer,  nbData );
            }
        }
    }
}






/**
  * @brief  Master Rx Transfer completed callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
void MID_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    hi2c = hi2c;
}

/**
  * @brief  Listen Complete callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
void MID_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *mI2C)
{
    mI2C= mI2C;
}

/**
  * @brief  I2C error callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
void MID_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
    hi2c=hi2c;
}



#include <Arduino.h>
#if 1
/**
 ******************************************************************************
 * @brief This function handles I2C0 event global interrupt / I2C0 wake-up interrupt through EXTI line 23.
 * @retval None
 ******************************************************************************
 */
void I2C0_IRQHandler(void)
{
    /* USER CODE BEGIN I2C0_IRQn 0 */

    /* USER CODE END I2C0_IRQn 0 */
    MID_I2C_IRQHandler(  &(g_i2c_init_info[I2C_0].i2c_handle) );
    /* USER CODE BEGIN I2C0_IRQn 1 */

    /* USER CODE END I2C0_IRQn 1 */
}
#endif

#if !defined(MG32_2ND)
/**
 ******************************************************************************
 * @brief This function handles I2C1 event global interrupt / I2C1 wake-up interrupt through EXTI line 23.
 * @retval None
 ******************************************************************************
 */
void I2Cx_IRQHandler(void)
{
    /* USER CODE BEGIN I2C1_IRQn 0 */

    /* USER CODE END I2C1_IRQn 0 */
    MID_I2C_IRQHandler(  &(g_i2c_init_info[I2C_1].i2c_handle) );
    /* USER CODE BEGIN I2C1_IRQn 1 */

    /* USER CODE END I2C1_IRQn 1 */
}
#endif


#ifdef __cplusplus
}
#endif


