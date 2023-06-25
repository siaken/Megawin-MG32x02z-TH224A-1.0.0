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
#ifndef  _SHELL_H_
#define  _SHELL_H_

#include "syscalls.h"
#include "uart.h"
#include "UARTClass.h"

#define MAX_CMD_CNT    256


#define  MAX_COMMAND_NUM      32

#ifdef __cplusplus

class  MG32_Shell;

typedef int F_Command( MG32_Shell* pShell,  int argc, char** argv );
typedef struct _ST_COMMAND_FUN 
{
    uint32_t         CfgFlg;
    char*            CmdStr;
    F_Command*       Fun;
} ST_COMMAND_FUN;


class  MG32_Shell
{
    
public:
    MG32_Shell();
    ~MG32_Shell();
    
    int  begin();
    int  begin( Uart* pUartHandle );
    int  Init( Uart* pUartHandle );
    void Shell_Command(unsigned char InData);

    int  Run();

    int  output(int outputLevel,  char* pstr);



    int  RegistCmd( char* CmdStr,  F_Command*  Fun );
    
public:
    Uart*            m_UartHandle;
    
private:
    uint16_t   m_LineCnt;
    uint8_t    m_CmdBuf[MAX_CMD_CNT+1];

    uint16_t   m_argc;
    uint8_t*   m_argv[MAX_CMD_CNT/4];

    
public:
    ST_COMMAND_FUN   m_Command[ MAX_COMMAND_NUM ];


    uint16_t   m_ShellMode;
    uint16_t   m_ShellEchoMode;

};


extern MG32_Shell  DebugShell;

#endif

#endif



