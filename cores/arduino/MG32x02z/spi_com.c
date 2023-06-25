

#include "spi_com.h"


#ifdef  MG32F02U128


extern spiPinDescription   SCLK_spi0PinDescription[ SPI0_PIN_REUSE ];
extern spiPinDescription   MISO_spi0PinDescription[ SPI0_PIN_REUSE ];
extern spiPinDescription   MOSI_spi0PinDescription[ SPI0_PIN_REUSE ];
extern spiPinDescription   SS_spi0PinDescription[ SPI0_PIN_REUSE ];
extern spiPinDescription   SSI_spi0PinDescription[ SPI0_PIN_REUSE ];


SPI_CfgSt  SPI0_PinCfg = 
{
    .psSCLK  = &SCLK_spi0PinDescription[0],
    .psMISO  = &MISO_spi0PinDescription[0],
    .psMOSI  = &MOSI_spi0PinDescription[0],
    .psSS    = &SS_spi0PinDescription[0],
    .psSSI   = &SSI_spi0PinDescription[0],
};





#define  SPIPIN_AFS_CFG(a, num, afs)        {  .arduino_id=MCU_##a##num, .AFS=a##num##_AFS_##afs, }

#define  SPIPIN_AFS_CFG_NULL               { .arduino_id=((uint16_t)-1),  .AFS=0, }

spiPinDescription   SCLK_spi0PinDescription[ SPI0_PIN_REUSE ] =
{
    SPIPIN_AFS_CFG( PA,  10, SPI0_CLK ),
    SPIPIN_AFS_CFG( PB,  2,  SPI0_CLK ),
    SPIPIN_AFS_CFG( PD,  8,  SPI0_CLK ),
    SPIPIN_AFS_CFG_NULL, //SPIPIN_AFS_CFG( PD,  12, SPI0_CLK ),
    SPIPIN_AFS_CFG_NULL, //SPIPIN_AFS_CFG( PE,  2,  SPI0_CLK ),
    SPIPIN_AFS_CFG_NULL, 
};

spiPinDescription   MISO_spi0PinDescription[ SPI0_PIN_REUSE ] =
{
    SPIPIN_AFS_CFG( PA,  9, SPI0_MISO ),
    SPIPIN_AFS_CFG( PB,  1, SPI0_MISO ),
    SPIPIN_AFS_CFG( PD,  3, SPI0_MISO ),
    SPIPIN_AFS_CFG( PD,  7, SPI0_MISO ),
    SPIPIN_AFS_CFG_NULL, //SPIPIN_AFS_CFG( PE,  1, SPI0_MISO ),
    SPIPIN_AFS_CFG_NULL, 
};


spiPinDescription   MOSI_spi0PinDescription[ SPI0_PIN_REUSE ] =
{
    SPIPIN_AFS_CFG( PA,  11, SPI0_MOSI ),
    SPIPIN_AFS_CFG( PB,  3,  SPI0_MOSI ),
    SPIPIN_AFS_CFG( PD,  2,  SPI0_MOSI ),
    SPIPIN_AFS_CFG( PD,  10, SPI0_MOSI ),
    SPIPIN_AFS_CFG_NULL, //SPIPIN_AFS_CFG( PE,  3,  SPI0_MOSI ),
    SPIPIN_AFS_CFG_NULL, 
};


spiPinDescription   SS_spi0PinDescription[ SPI0_PIN_REUSE ] =
{
    SPIPIN_AFS_CFG( PA,  8,  SPI0_NSS ),
    SPIPIN_AFS_CFG( PB,  0,  SPI0_NSS ),
    SPIPIN_AFS_CFG( PD,  0,  SPI0_NSS ),
    SPIPIN_AFS_CFG( PD,  9,  SPI0_NSS ),
    SPIPIN_AFS_CFG( PD,  11, SPI0_NSS ),
    SPIPIN_AFS_CFG_NULL, //SPIPIN_AFS_CFG( PE,  0,  SPI0_NSS ),
};



spiPinDescription   SSI_spi0PinDescription[ SPI0_PIN_REUSE ] =
{
    SPIPIN_AFS_CFG( PB,  6,   SPI0_NSSI ),
    SPIPIN_AFS_CFG( PB,  10,  SPI0_NSSI ),
    SPIPIN_AFS_CFG( PD,  9,   SPI0_NSSI ),
    SPIPIN_AFS_CFG_NULL, 
    SPIPIN_AFS_CFG_NULL, 
    SPIPIN_AFS_CFG_NULL, 

};


#endif






