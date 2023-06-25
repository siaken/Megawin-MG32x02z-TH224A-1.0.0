

#ifndef   _SPI_COM_H_
#define   _SPI_COM_H_


#include "Arduino.h"
#include "variant.h"

typedef struct _spiPinDescription
{
    uint16_t          arduino_id;
    uint16_t          AFS;
    //MID_SPI_Struct   *Instance;
} spiPinDescription;

//SPI 

#define   SPI0_PIN_REUSE    6


typedef struct _SPI_PinCfgSt
{
    spiPinDescription  *psSCLK;
    spiPinDescription  *psMISO;
    spiPinDescription  *psMOSI;
    spiPinDescription  *psSS;
    spiPinDescription  *psSSI;
}SPI_CfgSt;

extern SPI_CfgSt  SPI0_PinCfg;



#endif


