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
#include "shell.h"

#include "MG32x02z.h"
#include "system_MG32x02z.h"
#include "MG32x02z_CSC_Init.h"
#include "MG32x02z_GPIO_MID.h"
#include "MG32x02z_EXIC_MID.h"
#include "MG32x02z_EXIC_DRV.h"
#include "interrupt.h"
#include "variant.h"



#ifdef __cplusplus
 extern "C" {
#endif

/****************************************************************/
int Do_ListCmd(MG32_Shell* pShell,  int argc, char** argv );
int CMD_EnShellMode(MG32_Shell* pShell,  int argc, char** argv );
int CMD_EnShellEchoMode(MG32_Shell* pShell,  int argc, char** argv );
int CMD_Reset(MG32_Shell* pShell,  int argc, char** argv );
/****************************************************************/

int CMD_Testmode(MG32_Shell* pShell,  int argc, char** argv );

#ifdef __cplusplus
}
#endif


MG32_Shell::MG32_Shell()
{
    m_UartHandle = NULL;
    m_LineCnt = 0;
    memset(  &m_CmdBuf[0], 0, sizeof(m_CmdBuf) );

    m_argc = 0;
    memset(  &m_argv[0], 0, sizeof(m_argv) );

    m_ShellMode = 1;
    m_ShellEchoMode = 0;
        
    memset(  &m_Command[0], 0, sizeof(m_Command) );
    
    RegistCmd( (char*)"======System command================================================", NULL );
    RegistCmd( (char*)"ls",               Do_ListCmd );
    RegistCmd( (char*)"LS",               Do_ListCmd );
    RegistCmd( (char*)"reboot",           CMD_Reset );
    RegistCmd( (char*)"REBOOT",           CMD_Reset );

    RegistCmd( (char*)"shellmode",        CMD_EnShellMode );
    RegistCmd( (char*)"echomode",         CMD_EnShellEchoMode );

    RegistCmd( (char*)"========User command================================================", NULL );


}

MG32_Shell::~MG32_Shell()
{
    m_UartHandle = NULL;
    m_LineCnt = 0;
    memset(  &m_CmdBuf[0], 0, sizeof(m_CmdBuf) );

    m_argc = 0;
    memset(  &m_argv[0], 0, sizeof(m_argv) );

    m_ShellMode = 0;
    m_ShellEchoMode = 0;
}

int  MG32_Shell::begin()
{
    if( m_UartHandle == NULL )
    {
        return begin(  &Serial  );
    }
    else 
    {
        return begin(  m_UartHandle  );
    }
}

int  MG32_Shell::begin( Uart* pUartHandle )
{
    m_ShellMode = 1;
    return Init( pUartHandle );
}


int  MG32_Shell::Init( Uart* pUartHandle )
{
	unsigned int i;

    m_UartHandle = pUartHandle;

    m_ShellMode = 1;
    m_ShellEchoMode = 1;

    m_LineCnt = 0;
    for( i=0; i<MAX_CMD_CNT; i++ )
    {
    	m_CmdBuf[i] = 0;
	}
    m_argc = 0;
    for( i=0; i < (MAX_CMD_CNT/4); i++ )
    {
    	m_argv[i] = 0;
	}
	
	output(0,  (char*)"\r\nMegawin->" );
    return 0;
}



int MG32_Shell::RegistCmd( char* CmdStr,  F_Command*   Fun )
{
    int i;
    
    if( NULL == CmdStr )
    {
        return -1;
    }

    for(i=0; i<MAX_COMMAND_NUM;  i++)
    {
        if( 0 == m_Command[i].CfgFlg )
        {
            m_Command[i].CfgFlg      = 1;
            m_Command[i].CmdStr      = CmdStr;
            m_Command[i].Fun         = Fun;
            break;
        }
    }
    return 0;
}



/****************************************************************/
int Do_ListCmd(MG32_Shell* pShell,  int argc, char** argv )
{
	unsigned int i;
	
	pShell = pShell;
	argc = argc;
	argv = argv;

	for (i = 0; i < (sizeof(pShell->m_Command) / sizeof(ST_COMMAND_FUN)); i++)
	{
		if( (NULL != pShell->m_Command[i].CmdStr)
		 && (0 != strlen(pShell->m_Command[i].CmdStr))  )
		{
		    pShell->output(0, (char*)"\r\n    " );
		    pShell->output(0, pShell->m_Command[i].CmdStr );
		}
	}

	pShell->output(0, (char*)"\r\n    " );
	pShell->output(0, (char*)"====================================================================" );
	pShell->output(0,  (char*)"\r\n");
	return 0;
}


int CMD_EnShellMode(MG32_Shell* pShell,  int argc, char** argv )
{
	
	pShell = pShell;
	argc = argc;
	argv = argv;
	
	pShell->m_ShellMode = !pShell->m_ShellMode;
	return 0;
}

int CMD_EnShellEchoMode(MG32_Shell* pShell,  int argc, char** argv )
{
	
	pShell = pShell;
	argc = argc;
	argv = argv;
	
	pShell->m_ShellEchoMode = !pShell->m_ShellEchoMode;
	return 0;
}

int CMD_Reset(MG32_Shell* pShell,  int argc, char** argv )
{
	
	pShell = pShell;
	argc = argc;
	argv = argv;
	
	
	
    RST_CRstSource_Config(RST_SW_CE, ENABLE);
    RST_TriggerSystemRst_SW ( ENABLE );
    
    //设置一个等待时间，给上位机准备
    delay(1000);
    __NVIC_SystemReset();
    
	return 0;
}





/****************************************************************/


int MG32_Shell::output(int outputLevel,  char* pstr)
{
    if( NULL == m_UartHandle )
    {
        return -1;
    }

    if( m_ShellMode == 0 )
    {
        return -1;
    }

    if( (m_ShellEchoMode != 0 )
      &&(m_ShellEchoMode >= outputLevel) )
    {
        m_UartHandle->print( pstr );
    }

    return 0;
}

int MG32_Shell::Run()
{
	volatile unsigned long InData;

    if( NULL == m_UartHandle )
    {
        return -1;
    }
    
    if( m_ShellMode == 0 )
    {
        return -1;
    }

	InData = m_UartHandle->read();
	if( InData != (unsigned long)-1 )
    {
        Shell_Command( InData );
    }

    return 0;
}

void MG32_Shell::Shell_Command(unsigned char InData)
{
	unsigned int k;
	unsigned int i;
	unsigned int Cmdcnt = 0;

    if( ((0x00 == InData) || (0xFF == InData))  )
    {
		m_LineCnt = 0;
		for( i=0; i<MAX_CMD_CNT; i++ )
		{
			//确保在任何时候都能有'\0'
			m_CmdBuf[i] = 0;
		}
		m_argc = 0;
		for( i=0; i < (MAX_CMD_CNT/4); i++ )
		{
			m_argv[i] = 0;
		}
		return;
    }


    if(m_LineCnt >= MAX_CMD_CNT)
    {
    	//清除并退出
		m_LineCnt = 0;
	    for( i=0; i<MAX_CMD_CNT; i++ )
	    {
	    	//确保在任何时候都能有'\0'
	    	m_CmdBuf[i] = 0;
		}
	    m_argc = 0;
	    for( i=0; i < (MAX_CMD_CNT/4); i++ )
	    {
	    	m_argv[i] = 0;
		}

        output(0,  (char*)"\r\nEnter command too long!\r\n" );
	    if( 0 != m_ShellMode )
	    {
	        output(0,  (char*)"\r\nMegawin->" );
	    }
		return;
    }

    if( ((0x0A == InData) || (0x0D == InData))  )
    {
    	//进入本逻辑内部，必须执行，或者清零，因此不必考虑重入状态问题

        //只要收到回车，就去执行
        //第一步，解析命令
        m_CmdBuf[m_LineCnt] = 0;

        //去掉左侧的无效字符（值去第一个，剩下的由循环来做）
        for(k=0;  (k<m_LineCnt); k++)
        {
            if( (m_CmdBuf[k] >= 0x21) &&  (m_CmdBuf[k] <= 0x7e) )
            {
                break;
            }

            if( m_CmdBuf[k] == 0 )
            {
            	//没有有效命令
    			m_LineCnt = 0;
    		    for( i=0; i<MAX_CMD_CNT; i++ )
    		    {
    		    	//确保在任何时候都能有'\0'
    		    	m_CmdBuf[i] = 0;
    			}
    		    m_argc = 0;
    		    for( i=0; i < (MAX_CMD_CNT/4); i++ )
    		    {
    		    	m_argv[i] = 0;
    			}

    		    //下一个命令 引导
    		    if( 0 != m_ShellMode )
    		    {
	                output(0,  (char*)"\r\nMegawin->" );
    		    }
    			return;
            }
        }

        if( k== m_LineCnt)
        {
        	//没有有效命令
			m_LineCnt = 0;
		    for( i=0; i<MAX_CMD_CNT; i++ )
		    {
		    	//确保在任何时候都能有'\0'
		    	m_CmdBuf[i] = 0;
			}
		    m_argc = 0;
		    for( i=0; i < (MAX_CMD_CNT/4); i++ )
		    {
		    	m_argv[i] = 0;
			}

		    //下一个命令 引导
		    if( 0 != m_ShellMode )
		    {
	            output(0,  (char*)"\r\nMegawin->" );
		    }
			return;
        }

		m_argv[0] = &(m_CmdBuf[k]);
        m_argc = 1;

        //有命令，且左侧一个字符已经被处理
	    for( i=k+1; i<m_LineCnt; i++ )
	    {
	    	if( m_CmdBuf[i] == 0 )
	    	{
	    		break;
	    	}
	    	//确保在任何时候都能有'\0'
	    	else if( (m_CmdBuf[i] >= 0x21) &&  (m_CmdBuf[i] <= 0x7e) )
	    	{
		    	if( (m_CmdBuf[i-1] == 0)  )
		    	{
					m_argv[m_argc] = &(m_CmdBuf[i]);
		            m_argc++;
		    	}
	    	}
	    	else
	    	{
	    		m_CmdBuf[i] = 0;
	    	}
		}

		//第二步，查找符合的命令去执行
	    if( (NULL != m_argv[0]) &&  (0 != m_argv[0][0]) )
	    {
			for (i = 0; i < (sizeof(m_Command) / sizeof(ST_COMMAND_FUN)); i++)
			{
				if( 0 == strcmp( (const char*)m_argv[0], m_Command[i].CmdStr ) )
				{
					if( 0 != m_Command[i].Fun )
					{
						//回显
						if( m_ShellEchoMode != 0 )
						{
	                        output(0,  (char*)"\r\n" );
						}

						m_Command[i].Fun(this,  m_argc,  (char**)m_argv );
						Cmdcnt++;
					}
				}
			}
	    }

		//第三步，执行完成后清楚命令行操作
	    if( Cmdcnt == 0 )
	    {
            output(0,  (char*)"\r\nBad command!" );
            output(0,  (char*)"\r\n" );
			for (i = 0; i < m_argc; i++)
			{
				output(0, (char*)m_argv[i]);
		        output(0, (char*)" ");
			}
	        output(0, (char*)"\r\n");
	    }

		m_LineCnt = 0;
	    for( i=0; i<MAX_CMD_CNT; i++ )
	    {
	    	//确保在任何时候都能有'\0'
	    	m_CmdBuf[i] = 0;
		}
	    m_argc = 0;
	    for( i=0; i < (MAX_CMD_CNT/4); i++ )
	    {
	    	m_argv[i] = 0;
		}

	    //下一个命令 引导
	    if( 0 != m_ShellMode )
	    {
		    output(0, (char*)"\r\nMegawin->");
	    }
    }
    else if(0x08 == InData)
    {
    	if( 0 < m_LineCnt )
    	{
			m_LineCnt--;
			//回显
			if( m_ShellEchoMode != 0 )
			{
                output(0, (char*)"\b \b");
			}
			m_CmdBuf[m_LineCnt] = 0;
    	}
    	else
    	{
    		m_LineCnt = 0;
    	    for( i=0; i<MAX_CMD_CNT; i++ )
    	    {
    	    	//确保在任何时候都能有'\0'
    	    	m_CmdBuf[i] = 0;
    		}
    	    m_argc = 0;
    	    for( i=0; i < (MAX_CMD_CNT/4); i++ )
    	    {
    	    	m_argv[i] = 0;
    		}
    	    //不需要补充输出引导符
    	}
    }
	else if ((InData >= 0x20) && (InData <= 0x7F))
	{
		m_CmdBuf[m_LineCnt] = InData;
		m_LineCnt++;
		//回显
		if( m_ShellEchoMode != 0 )
		{
		    if(NULL != m_UartHandle)
		    {
                m_UartHandle->write(InData);
		    }
		}
	}
}



