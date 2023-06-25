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

#include "Arduino.h"
#include "SPI.h"
#include "spi_com.h"

SPISettings::SPISettings(uint32_t clock, BitOrder bitOrder, uint8_t dataMode)
{
    m_spiInit.NSSPMode  = SPI_NSS_PULSE_DISABLE;
    m_spiInit.NSS       = SPI_NSS_HARDWARE;
    m_spiInit.DataLine  = SPI_STANDARD_SPI;
    m_spiInit.DataSize  = SPI_DATASIZE_8BIT;

    if(clock >= SPI_SPEED_CLOCK_DIV2_MHZ)
    {
        m_spiInit.ClockDivider = SPI_CLOCKDIVIDER_2;
    }
    else if (clock >= SPI_SPEED_CLOCK_DIV4_MHZ) 
    {
        m_spiInit.ClockDivider = SPI_CLOCKDIVIDER_4;
    }
    else if (clock >= SPI_SPEED_CLOCK_DIV8_MHZ)
    {
        m_spiInit.ClockDivider = SPI_CLOCKDIVIDER_8;
    }
    else if (clock >= SPI_SPEED_CLOCK_DIV16_MHZ) 
    {
        m_spiInit.ClockDivider = SPI_CLOCKDIVIDER_16;
    }
    else if (clock >= SPI_SPEED_CLOCK_DIV32_MHZ)
    {
        m_spiInit.ClockDivider = SPI_CLOCKDIVIDER_32;
    } 
    else if (clock >= SPI_SPEED_CLOCK_DIV64_MHZ)
    {
        m_spiInit.ClockDivider = SPI_CLOCKDIVIDER_64;
    }
    else if (clock >= SPI_SPEED_CLOCK_DIV128_MHZ)
    {
        m_spiInit.ClockDivider = SPI_CLOCKDIVIDER_128;
    } 
    else
    {
        m_spiInit.ClockDivider = SPI_CLOCKDIVIDER_256;
    }

    m_spiInit.FirstBit = bitOrder;

    switch (dataMode)
    {
        case SPI_MODE0:
            //SPI_MODE_0
            m_spiInit.CLKPolarity = SPI_POLARITY_LOW;
            m_spiInit.CLKPhase    = SPI_PHASE_1EDGE;
            break;
        case SPI_MODE1:
            //SPI_MODE_1
            m_spiInit.CLKPolarity = SPI_POLARITY_LOW;
            m_spiInit.CLKPhase    = SPI_PHASE_2EDGE;
            
            break;
        case SPI_MODE2:
            //SPI_MODE_2
            m_spiInit.CLKPolarity = SPI_POLARITY_HIGH;
            m_spiInit.CLKPhase    = SPI_PHASE_1EDGE;
            break;
        case SPI_MODE3:
            //SPI_MODE_3
            m_spiInit.CLKPolarity = SPI_POLARITY_HIGH;
            m_spiInit.CLKPhase    = SPI_PHASE_2EDGE;
            break;
        default:
            //SPI_MODE_0
            m_spiInit.CLKPolarity = SPI_POLARITY_LOW;
            m_spiInit.CLKPhase    = SPI_PHASE_1EDGE;
            break;
    }

    m_ulPin = -1;
}

//  SPI_PHASE_1EDGE  0
//Mode          Clock Polarity (CPOL)   Clock Phase (CPHA)
//SPI_MODE0             0                     0
//SPI_MODE1             0                     1
//SPI_MODE2             1                     0
//SPI_MODE3             1                     1

SPISettings::SPISettings()
{
    m_spiInit.NSSPMode     = SPI_NSS_PULSE_DISABLE;
    m_spiInit.NSS          = SPI_NSS_HARDWARE;
    m_spiInit.DataLine     = SPI_STANDARD_SPI;
    m_spiInit.DataSize     = SPI_DATASIZE_8BIT;
    m_spiInit.ClockDivider = SPI_CLOCKDIVIDER_2;
    m_spiInit.FirstBit     = MSBFIRST;

    m_spiInit.CLKPolarity = SPI_POLARITY_LOW;
    m_spiInit.CLKPhase    = SPI_PHASE_1EDGE;

    m_ulPin = -1;
}



void SPIClass::setInit()
{
    if( m_isMaster != 0 )
    {
        m_spiSettings.m_spiInit.Mode      = SPI_MODE_MASTER;
    }
    else
    {
        m_spiSettings.m_spiInit.Mode      = SPI_MODE_SLAVE_NSS;
    }

    m_SPI.Init.Mode          = m_spiSettings.m_spiInit.Mode;
    m_SPI.Init.NSSPMode      = m_spiSettings.m_spiInit.NSSPMode;
    m_SPI.Init.NSS           = m_spiSettings.m_spiInit.NSS;
    m_SPI.Init.DataLine      = m_spiSettings.m_spiInit.DataLine;
    m_SPI.Init.DataSize      = m_spiSettings.m_spiInit.DataSize;
    m_SPI.Init.ClockDivider  = m_spiSettings.m_spiInit.ClockDivider;
    
    if(m_spiSettings.m_spiInit.FirstBit == MSBFIRST)
    {
        m_SPI.Init.FirstBit     = SPI_FIRSTBIT_MSB;
    }
    else
    {
        m_SPI.Init.FirstBit     = SPI_FIRSTBIT_LSB;
    }

    m_SPI.Init.CLKPolarity   = m_spiSettings.m_spiInit.CLKPolarity;
    m_SPI.Init.CLKPhase      = m_spiSettings.m_spiInit.CLKPhase;

    m_spiSettings.m_ulPin = m_pin_NSS;
    
    m_active_flg = 0;
}



void SPIClass::pinInit()
{
    Pin_Struct*  pPinx;		
    GPIO_InitTypeDef GPIOX;

    int i;

    uint16_t afsSCLK = g_APinDescription[m_pin_CLK].AFS;
    uint16_t afsMISO = g_APinDescription[m_pin_MISO].AFS;
    uint16_t afsMOSI = g_APinDescription[m_pin_MOSI].AFS;
    //uint16_t afsSS = g_APinDescription[m_pin_NSS].AFS;

    if( m_SPI.Instance == SPI_SPI0 )
    {
        for( i=0; i<SPI0_PIN_REUSE; i++ )
        {
            if( SPI0_PinCfg.psSCLK[i].arduino_id == m_pin_CLK )
            {
                afsSCLK = SPI0_PinCfg.psSCLK[i].AFS;
            }

            if( SPI0_PinCfg.psMISO[i].arduino_id == m_pin_MISO )
            {
                afsMISO = SPI0_PinCfg.psMISO[i].AFS;
            }

            if( SPI0_PinCfg.psMOSI[i].arduino_id == m_pin_MOSI )
            {
                afsMOSI = SPI0_PinCfg.psMOSI[i].AFS;
            }
            
/*
            if( m_isMaster != 0 )
            {
                if( SPI0_PinCfg.psSS[i].arduino_id == m_pin_NSS )
                {
                    afsSS = SPI0_PinCfg.psSS[i].AFS;
                }
            }
            else
            {
                if( SPI0_PinCfg.psSSI[i].arduino_id == m_pin_NSS )
                {
                    afsSS = SPI0_PinCfg.psSSI[i].AFS;
                }
            }
*/
        }

        GPIOX.Pull = GPIO_PULLUP;
        GPIOX.Speed          = GPIO_SPEED_HIGH;
        GPIOX.OUTDrive       = GPIO_OUTDRIVE_LEVEL0;
        GPIOX.FilterDivider  = GPIO_FILTERDIVIDER_BYPASS;
        GPIOX.Inverse        = GPIO_INVERSE_DISABLE;
        if( m_isMaster != 0 )
        {
            //1. Master MOSI Pin
            //    (1).MG32x02z_GPIO_Init.h(Configuration Wizard)
            //    (2).GPIO port initial is 0xFFFF
            //    (3).Pin3 mode is PPO (Push pull output)
            //    (4).Pin3 pull-up resister Enable
            //    (5).Pin3 function SPI0_MOSI
            GPIOX.Mode = GPIO_MODE_PUSHPULL_O;
        }
        else
        {
            //1. Slave MOSI Pin
            //    (1).MG32x02z_GPIO_Init.h(Configuration Wizard)
            //    (2).GPIO port initial is 0xFFFF
            //    (3).Pin3 mode is DIN (Data input)
            //    (4).Pin3 pull-up resister Enable
            //    (5).Pin3 function SPI0_MOSI
            GPIOX.Mode = GPIO_MODE_DIGITAL_I;
        }
        GPIOX.Pin            = g_APinDescription[m_pin_MOSI].GioPin;
        GPIOX.Alternate      = afsMOSI;
        pPinx = __GetPinxx_byGPIOx( g_APinDescription[m_pin_MOSI].ulPort, g_APinDescription[m_pin_MOSI].PinNum );
        MID_GPIO_Pin_Init(  pPinx,  &GPIOX);

        if( m_isMaster != 0 )
        {
            //2. Master MISO Pin
            //    (1).MG32x02z_GPIO_Init.h(Configuration Wizard)
            //    (2).GPIO port initial is 0xFFFF
            //    (3).Pin1 mode is DIN (Data input)
            //    (4).Pin1 pull-up resister Enable
            //    (5).Pin1 function SPI0_MISO
            GPIOX.Mode = GPIO_MODE_DIGITAL_I ;
        }
        else
        {
            //2. Slave MISO Pin
            //    (1).MG32x02z_GPIO_Init.h(Configuration Wizard)
            //    (2).GPIO port initial is 0xFFFF
            //    (3).Pin1 mode is PPO (Push pull output)
            //    (4).Pin1 pull-up resister Enable
            //    (5).Pin1 function SPI0_MISO
            GPIOX.Mode = GPIO_MODE_PUSHPULL_O ;
        }
        GPIOX.Pin            = g_APinDescription[m_pin_MISO].GioPin;
        GPIOX.Alternate      = afsMISO;
        pPinx = __GetPinxx_byGPIOx( g_APinDescription[m_pin_MISO].ulPort, g_APinDescription[m_pin_MISO].PinNum );
        MID_GPIO_Pin_Init(  pPinx,  &GPIOX);


        if( m_isMaster != 0 )
        {
            //3. Master SPICLK Pin
            //    (1).MG32x02z_GPIO_Init.h(Configuration Wizard)
            //    (2).GPIO port initial is 0xFFFF
            //    (3).Pin2 mode is PPO (Push pull output)
            //    (4).Pin2 pull-up resister Enable
            //    (5).Pin2 function SPI0_CLK
            GPIOX.Mode = GPIO_MODE_PUSHPULL_O;
        }
        else
        {
            //3. Slave SPICLK Pin
            //    (1).MG32x02z_GPIO_Init.h(Configuration Wizard)
            //    (2).GPIO port initial is 0xFFFF
            //    (3).Pin2 mode is DIN (Data input)
            //    (4).Pin2 pull-up resister Enable
            //    (5).Pin2 function SPI0_CLK
            GPIOX.Mode = GPIO_MODE_DIGITAL_I;
        }
        GPIOX.Pin            = g_APinDescription[m_pin_CLK].GioPin;
        GPIOX.Alternate      = afsSCLK;
        pPinx = __GetPinxx_byGPIOx( g_APinDescription[m_pin_CLK].ulPort, g_APinDescription[m_pin_CLK].PinNum );
        MID_GPIO_Pin_Init(  pPinx,  &GPIOX);
 
        //4. NSS Pin
        //    (1).MG32x02z_GPIO_Init.h(Configuration Wizard)->Use GPIOB->Pin10
        //    (2).GPIO port initial is 0xFFFF
        //    (3).Pin0 mode is PPO (Push pull output)
        //    (4).Pin0 pull-up resister Enable
        //    (5).Pin0 function GPB0
        if( m_isMaster != 0 )
        {
            pinMode( m_pin_NSS, OUTPUT);
            digitalWrite( m_pin_NSS, HIGH);
        }
        else
        {
            pinMode( m_pin_NSS, INPUT);
        }
    }
}



SPIClass::SPIClass()
{
    m_SPI.Instance      = SPI_SPI0;
    
    m_pin_CLK  = SCK;
    m_pin_MISO = MISO;
    m_pin_MOSI = MOSI;
    m_pin_NSS  = SS;
    
    m_isMaster = 1;

    setInit();
    m_active_flg = 0;
}

SPIClass::SPIClass( MID_SPI_Struct  *Instance )
{
    m_SPI.Instance = Instance;
    
    m_pin_NSS  = SS; 
    m_pin_MOSI = MOSI; 
    m_pin_MISO = MISO; 
    m_pin_CLK  = SCK; 

    m_isMaster = 1;

    setInit();
    m_active_flg = 0;
}

SPIClass::SPIClass( MID_SPI_Struct  *Instance,  
              uint32_t  pin_CLK,   uint32_t  pin_MISO,   uint32_t  pin_MOSI,
              uint32_t  pin_NSS,   uint8_t   isMaster )
{
    m_SPI.Instance      = Instance;
    
    m_pin_CLK  = pin_CLK;
    m_pin_MISO = pin_MISO;
    m_pin_MOSI = pin_MOSI;
    m_pin_NSS  = pin_NSS;

    m_isMaster = isMaster;


    setInit();
    m_active_flg = 0;
}


byte SPIClass::transfer(uint32_t pin_cs, uint8_t _data, SPITransferMode _mode )
{
    uint8_t rx_buffer = 0;

    if( (pin_cs >= MAX_DIGITAL_IOS) ) 
    {
        return  rx_buffer;
    }
    
    if( 0 == m_active_flg ) 
    {
        //重新配置需要设置cs电平
        pinMode( pin_cs, OUTPUT);
        digitalWrite( pin_cs, HIGH);
        setInit();
        pinInit();

        MID_SPI_Init( &(m_SPI) );
        m_active_flg = 1;
    }

    pinMode( pin_cs, OUTPUT);
    digitalWrite( pin_cs, LOW);

    MID_SPI_TransmitReceive( &(m_SPI), &_data, &rx_buffer, sizeof(uint8_t), 100000 );

    if( (_mode == SPI_LAST) )
    {
        digitalWrite(pin_cs, HIGH);
    }
    return rx_buffer;
}

uint16_t SPIClass::transfer16(uint32_t pin_cs, uint16_t _data, SPITransferMode _mode)
{
    uint16_t rx_buffer = 0;

    if( (pin_cs >= MAX_DIGITAL_IOS) ) 
    {
        return  rx_buffer;
    }

    if( 0 == m_active_flg ) 
    {
        //重新配置需要设置cs电平
        pinMode( pin_cs, OUTPUT);
        digitalWrite( pin_cs, HIGH);
        setInit();
        pinInit();

        MID_SPI_Init( &m_SPI );
        m_active_flg = 1;
    }
    pinMode( pin_cs, OUTPUT);
    digitalWrite( pin_cs, LOW);

    MID_SPI_TransmitReceive( &(m_SPI),(uint8_t *)&_data, (uint8_t *)&rx_buffer, sizeof(uint16_t), 10000 );

    if( (_mode == SPI_LAST) )
    {
        digitalWrite(pin_cs, HIGH);
    }
    return rx_buffer;
}

void SPIClass::transfer(uint32_t pin_cs, void *_buf, size_t _count, SPITransferMode _mode)
{
    if( (NULL== _buf) || (0==_count) )
    {
        return;
    }

    if( (pin_cs >= MAX_DIGITAL_IOS) ) 
    {
        return;
    }
    
    if( 0 == m_active_flg ) 
    {
        //重新配置需要设置cs电平
        pinMode( pin_cs, OUTPUT);
        digitalWrite( pin_cs, HIGH);
        setInit();
        pinInit();

        MID_SPI_Init( ( &m_SPI ) );
        m_active_flg = 1;
    }

    pinMode( pin_cs, OUTPUT);
    digitalWrite( pin_cs, LOW);

    MID_SPI_Transmit( &(m_SPI), (uint8_t *)_buf, _count, 10000000 );

    if( (_mode == SPI_LAST) )
    {
        digitalWrite(pin_cs, HIGH);
    }
}


void SPIClass::usingInterrupt(uint8_t interruptNumber)
{
  //Not implemented
  interruptNumber = interruptNumber;
}



void SPIClass::beginTransaction(uint32_t pin_cs, SPISettings settings)
{
    m_spiSettings.m_ulPin = pin_cs;
    memcpy( &(m_spiSettings), &settings, sizeof(SPISettings) );

    setInit();
    pinInit();

    //重新配置需要设置cs电平
    pinMode( pin_cs, OUTPUT );
    digitalWrite( pin_cs, HIGH);

    MID_SPI_Init( &(m_SPI) );
    m_active_flg = 1;

}

void SPIClass::endTransaction(void)
{
    m_active_flg = 0;
}

/**
  * @brief  Not implemented.
  */
void SPIClass::attachInterrupt(void)
{
    //Not implemented.
    ;
}

/**
  * @brief  Not implemented.
  */
void SPIClass::detachInterrupt(void)
{
    //Not implemented.
    ;
}



void SPIClass::begin(void)
{
    begin(BOARD_SPI_OWN_SS);
}


void SPIClass::end(void)
{
    MID_SPI_DeInit( &(m_SPI) );
    m_active_flg = 0;
}


void SPIClass::begin(uint32_t pin_cs)
{
    if( (pin_cs >= MAX_DIGITAL_IOS) ) 
    {
        return;
    }

    setInit();
    pinInit();

    pinMode( pin_cs, OUTPUT);
    digitalWrite( pin_cs, HIGH);

    MID_SPI_Init( &(m_SPI) );
    m_active_flg = 1;


#if __has_include("WiFi.h")
// Wait wifi shield initialization.
// Should be better to do in SpiDrv::begin() of WiFi library but it seems
// there is no more update on this library as shield is retired.
delay(2000);
#endif

}


void SPIClass::end(uint32_t pin_cs)
{
    pin_cs = pin_cs;
    end();
}



void SPIClass::setBitOrder(uint32_t pin_cs, BitOrder bitOrder)
{
    if( (pin_cs >= MAX_DIGITAL_IOS) ) 
    {
        return;
    }
    
    m_spiSettings.m_spiInit.FirstBit = bitOrder;

    setInit();
    pinInit();
    
    pinMode( pin_cs, OUTPUT);
    digitalWrite( pin_cs, HIGH);

    MID_SPI_Init( &(m_SPI) );
    m_active_flg = 1;
}


void SPIClass::setDataMode(uint32_t pin_cs, uint8_t _mode)
{
    if( (pin_cs >= MAX_DIGITAL_IOS) ) 
    {
        return;
    }
    
    switch (_mode)
    {
        case SPI_MODE0:
            //SPI_MODE_0
            m_spiSettings.m_spiInit.CLKPolarity = SPI_POLARITY_LOW;
            m_spiSettings.m_spiInit.CLKPhase    = SPI_PHASE_1EDGE;
            break;
        case SPI_MODE1:
            //SPI_MODE_1
            m_spiSettings.m_spiInit.CLKPolarity = SPI_POLARITY_LOW;
            m_spiSettings.m_spiInit.CLKPhase    = SPI_PHASE_2EDGE;
            
            break;
        case SPI_MODE2:
            //SPI_MODE_2
            m_spiSettings.m_spiInit.CLKPolarity = SPI_POLARITY_HIGH;
            m_spiSettings.m_spiInit.CLKPhase    = SPI_PHASE_1EDGE;
            break;
        case SPI_MODE3:
            //SPI_MODE_3
            m_spiSettings.m_spiInit.CLKPolarity = SPI_POLARITY_HIGH;
            m_spiSettings.m_spiInit.CLKPhase    = SPI_PHASE_2EDGE;
            break;
        default:
            //SPI_MODE_0
            m_spiSettings.m_spiInit.CLKPolarity = SPI_POLARITY_LOW;
            m_spiSettings.m_spiInit.CLKPhase = SPI_PHASE_1EDGE;
            break;
    }

    setInit();
    pinInit();
    
    pinMode( pin_cs, OUTPUT);
    digitalWrite( pin_cs, HIGH);

    MID_SPI_Init( &(m_SPI) );
    m_active_flg = 1;
}


void SPIClass::setClock(uint32_t pin_cs, uint32_t clock)
{
    if( (pin_cs >= MAX_DIGITAL_IOS) ) 
    {
        return;
    }
    
    if(clock >= SPI_SPEED_CLOCK_DIV2_MHZ)
    {
        m_spiSettings.m_spiInit.ClockDivider = SPI_CLOCKDIVIDER_2;
    }
    else if (clock >= SPI_SPEED_CLOCK_DIV4_MHZ) 
    {
        m_spiSettings.m_spiInit.ClockDivider = SPI_CLOCKDIVIDER_4;
    }
    else if (clock >= SPI_SPEED_CLOCK_DIV8_MHZ)
    {
        m_spiSettings.m_spiInit.ClockDivider = SPI_CLOCKDIVIDER_8;
    }
    else if (clock >= SPI_SPEED_CLOCK_DIV16_MHZ) 
    {
        m_spiSettings.m_spiInit.ClockDivider = SPI_CLOCKDIVIDER_16;
    }
    else if (clock >= SPI_SPEED_CLOCK_DIV32_MHZ)
    {
        m_spiSettings.m_spiInit.ClockDivider = SPI_CLOCKDIVIDER_32;
    } 
    else if (clock >= SPI_SPEED_CLOCK_DIV64_MHZ)
    {
        m_spiSettings.m_spiInit.ClockDivider = SPI_CLOCKDIVIDER_64;
    }
    else if (clock >= SPI_SPEED_CLOCK_DIV128_MHZ)
    {
        m_spiSettings.m_spiInit.ClockDivider = SPI_CLOCKDIVIDER_128;
    } 
    else
    {
        m_spiSettings.m_spiInit.ClockDivider = SPI_CLOCKDIVIDER_256;
    }

    setInit();
    pinInit();
    
    pinMode( pin_cs, OUTPUT);
    digitalWrite( pin_cs, HIGH);

    MID_SPI_Init( &(m_SPI) );
    m_active_flg = 1;
}


void SPIClass::setClockDivider(uint32_t pin_cs, uint8_t _divider)
{
    if( (pin_cs >= MAX_DIGITAL_IOS) ) 
    {
        return;
    }
    
    switch(_divider)
    {
        case (SPI_CLOCK_DIV2) :
            m_spiSettings.m_spiInit.ClockDivider = SPI_CLOCKDIVIDER_2;
            break;
        case (SPI_CLOCK_DIV4) :
            m_spiSettings.m_spiInit.ClockDivider = SPI_CLOCKDIVIDER_4;
            break;
        case (SPI_CLOCK_DIV8) :
            m_spiSettings.m_spiInit.ClockDivider = SPI_CLOCKDIVIDER_8;
            break;
        case (SPI_CLOCK_DIV16) :
            m_spiSettings.m_spiInit.ClockDivider = SPI_CLOCKDIVIDER_16;
            break;
        case (SPI_CLOCK_DIV32) :
            m_spiSettings.m_spiInit.ClockDivider = SPI_CLOCKDIVIDER_32;
            break;
        case (SPI_CLOCK_DIV64) :
            m_spiSettings.m_spiInit.ClockDivider = SPI_CLOCKDIVIDER_64;
            break;
        case (SPI_CLOCK_DIV128) :
            m_spiSettings.m_spiInit.ClockDivider = SPI_CLOCKDIVIDER_128;
            break;
        default:
            m_spiSettings.m_spiInit.ClockDivider = SPI_CLOCKDIVIDER_256;
            break;
    }

    setInit();
    pinInit();
    
    pinMode( pin_cs, OUTPUT);
    digitalWrite( pin_cs, HIGH);

    MID_SPI_Init( &(m_SPI) );
    m_active_flg = 1;

}


SPIClass SPI( SPI_SPI0,
              MCU_PD8,   MCU_PD7,  MCU_PD2,  MCU_PD9,
              1  );



