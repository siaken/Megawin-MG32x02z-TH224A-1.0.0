/**
 ******************************************************************************
 *
 * @file        MG32x02z_TM_DRV.h
 *
 * @brief       This file contains all the functions prototypes for the TM 
 *              firmware library.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.25
 * @date        2021/02/26
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2016 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************
 * @par 		Disclaimer 
 *		The Demo software is provided "AS IS"  without any warranty, either 
 *		expressed or implied, including, but not limited to, the implied warranties 
 *		of merchantability and fitness for a particular purpose.  The author will 
 *		not be liable for any special, incidental, consequential or indirect 
 *		damages due to loss of data or any other reason. 
 *		These statements agree with the world wide and local dictated laws about 
 *		authorship and violence against these laws. 
 ******************************************************************************
 ******************************************************************************
 */ 
#ifndef _MG32x02z_TM_DRV_H

/*!< _MG32x02z_TM_DRV_H */ 
#define _MG32x02z_TM_DRV_H

#include "MG32x02z__Common_DRV.h"
#include "MG32x02z_TM.h"


/**
 * @brief  	simple define
 *
 */ 
#define TM_CKO_unLock   TM_CKO_CKO_LCK_un_locked_b0         /*!< for CKO unlock bit of Byte */    
#define TM_CKO_State    TM_CKO_CKO_STA_1_b0                 /*!< for CKO state bit of Byte */  

#define TM_OS0_unLock   TM_OSCR_OS0_LCK_un_locked_b0        /*!< for OS0 unlock bit of Byte */    
#define TM_OS0_State    TM_OSCR_OS0_STA_1_b0                /*!< for OS0 state bit of Byte */    
#define TM_OS0H_unLock  TM_OSCR_OS0H_LCK_un_locked_b1       /*!< for OS0H unlock bit of Byte */    
#define TM_OS0H_State   TM_OSCR_OS0H_STA_1_b1               /*!< for OS0H state bit of Byte */    

#define TM_OS1_unLock   TM_OSCR_OS1_LCK_un_locked_b0        /*!< for OS1 unlock bit of Byte */    
#define TM_OS1_State    TM_OSCR_OS1_STA_1_b0                /*!< for OS1 state bit of Byte */    
#define TM_OS1H_unLock  TM_OSCR_OS1H_LCK_un_locked_b1       /*!< for OS1H unlock bit of Byte */    
#define TM_OS1H_State   TM_OSCR_OS1H_STA_1_b1               /*!< for OS1H state bit of Byte */    

#define TM_OS2_unLock   TM_OSCR_OS2_LCK_un_locked_b0        /*!< for OS2 unlock bit of Byte */    
#define TM_OS2_State    TM_OSCR_OS2_STA_1_b0                /*!< for OS2 state bit of Byte */    
#define TM_OS2H_unLock  TM_OSCR_OS2H_LCK_un_locked_b1       /*!< for OS2H unlock bit of Byte */    
#define TM_OS2H_State   TM_OSCR_OS2H_STA_1_b1               /*!< for OS2H state bit of Byte */    

#define TM_OS3_unLock   TM_OSCR_OS3_LCK_un_locked_b0        /*!< for OS3 unlock bit of Byte */    
#define TM_OS3_State    TM_OSCR_OS3_STA_1_b0                /*!< for OS3 state bit of Byte */    
#define TM_OS3H_unLock  TM_OSCR_OS3H_LCK_un_locked_b1       /*!< for OS3H unlock bit of Byte */    
#define TM_OS3H_State   TM_OSCR_OS3H_STA_1_b1               /*!< for OS3H state bit of Byte */    

/**
 * @brief  	simple define
 *
 */ 
#define IC0     TMx_InputMUX_Pin							/*!< IC0 the same as TMx_InputMUX_Pin */
#define IC1     TMx_InputMUX_ITR                            /*!< CKO the same as TMx_InputMUX_ITR */
#define IC2     TMx_InputMUX_Select2                        /*!< CKO the same as TMx_InputMUX_Select2 */
#define IC3     TMx_InputMUX_Select3                        /*!< CKO the same as TMx_InputMUX_Select3 */


#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

/** 
 * @enum		TM_ClockSourceDef
 * @brief		declare Timer clock from internal or external 
 */        
typedef enum 
{ 
    TM_CK_INT=0,                            /*!< Timer clock source from internal clock CK_PROC (CK_SYS/CK_APB or CK_LS) */
    TM_CK_EXT                               /*!< Timer clock source from external clock (ETR/ITRx/IN0/IN1) */
} TM_ClockSourceDef;

/** 
 * @enum		TM_INTClockDivDef
 * @brief		declare Timer clock from internal or external 
 */        
typedef enum 
{ 
    TM_IntDIV1=0,                           /*!< Timer internal clock divider (DIV1) */
    TM_IntDIV2,                             /*!< Timer internal clock divider (DIV2) */
    TM_IntDIV4,                             /*!< Timer internal clock divider (DIV4) */
    TM_IntDIV8                              /*!< Timer internal clock divider (DIV8) */
} TM_INTClockDivDef;

/** 
 * @enum		TM_DTClockDivDef
 * @brief		Timer internal dead time clock CK_DTG divider
 */        
typedef enum 
{ 
    TM_DTDIV1=0,                            /*!< Timer internal dead time clock divider (DIV1) */
    TM_DTDIV2,                              /*!< Timer internal dead time clock divider (DIV2) */
    TM_DTDIV4,                              /*!< Timer internal dead time clock divider (DIV4) */
    TM_DTDIV8                               /*!< Timer internal dead time clock divider (DIV8) */
} TM_DTClockDivDef;

/** 
 * @enum		TM_ExternalClockSourceDef
 * @brief		declare Timer external clock source 
 */        
typedef enum 
{ 
    TM_CKETR=0,                             /*!< Timer external clock from (ETR) */
    TM_CKITR,                               /*!< Timer external clock from (ITR0~7) */
    TM_CKIN0,                               /*!< Timer external clock from (IN0) */
    TM_CKIN1                                /*!< Timer external clock from (IN1) */
} TM_ExternalClockSourceDef;

/** 
 * @enum		TM_ITRSourceDef
 * @brief		declare ITRx source 
 */        
typedef enum 
{ 
    ITR0,                                   /*!< ITR0 : reference FuncTable what's declare */
    ITR1,                                   /*!< ITR1 */
    ITR2,                                   /*!< ITR2 */
    ITR3,                                   /*!< ITR3 */
    ITR4,                                   /*!< ITR4 */
    ITR5,                                   /*!< ITR5 */
    ITR6,                                   /*!< ITR6 */
    ITR7                                    /*!< ITR7 */
} TM_ITRSourceDef;

/** 
 * @enum		TM_CounterModeDef
 * @brief		declare Timer main counter/prescaler mode  
 */        
typedef enum 
{ 
    Cascade=0,                              /*!< 16/8-bit counter with 16/8-bit prescaler Mode (TM0x is 8bit)*/  
    Separate,                               /*!< Separated two 16/8-bit counters Mode  (TM0x is 8bit)*/
    Full_Counter                            /*!< 32/16-bit counter Mode  (TM0x is 16bit)*/
} TM_CounterModeDef;

/** 
 * @enum		TM_CounterResetGateSW_Def
 * @brief		select Reset or Gate action to main counter  
 */        
typedef enum 
{ 
    ResetCounter=0x10,                      /*!< reset main counter by software */
    GatingCounter=0x40                      /*!< gating main counter by software */
} TM_CounterResetGateSW_Def;

/** 
 * @enum		TM_PrescalerResetGateSW_Def
 * @brief		select Reset or Gate action to prescaler counter  
 */        
typedef enum 
{ 
    ResetPrescaler=0x20,                    /*!< reset prescaler counter by software */        
    GatingPrescaler=0x80                    /*!< reset prescaler counter by software */ 
} TM_PrescalerResetGateSW_Def;


/** 
 * @enum		TM_TRGITrgSourceDef
 * @brief		config TRGI source path  
 */        
typedef enum 
{ 
    TRGI_ETR=0,                             /*!< TRGI from ETR */ 
    TRGI_ITR,                               /*!< TRGI from ITR(0~7) - reference FuncTable */
    TRGI_IN0,                               /*!< TRGI from IN0 */
    TRGI_IN1                                /*!< TRGI from IN1 */
} TM_TRGITrgSourceDef;

/** 
 * @enum		TM_DirectionDef
 * @brief		declare Timer counting direction bit
 */        
typedef enum 
{ 
    TM_UpCount=0,                           /*!< Up Counting */
    TM_DownCount                            /*!< Down Counting */
} TM_DirectionDef;

/** 
 * @enum		TM_TRGIModeDef
 * @brief		(TRGI) Timer trigger input mode select
 */        
typedef enum 
{ 
    TRGI_NoOP,                              /*!< No operation - default */
    TRGI_StartupRising,                     /*!< startup counter when TRGI rising edge */
    TRGI_ResetRising,                       /*!< reset counter when TRGI rising edge */
    TRGI_GATE_High,                         /*!< gating counter when TRGI in high level */
    TRGI_Rest_DualEdge,                     /*!< reset counter when TRGI rising or falling (dual) edge */
    TRGI_StartupFalling,                    /*!< startup counter when TRGI falling edge */
    TRGI_ResetFalling,                      /*!< reset counter when TRGI falling edge */
    TRGI_GATE_Low                           /*!< gating counter when TRGI in low level */
} TM_TRGIModeDef;

#if defined(MG32_1ST) || defined(MG32_2ND) || defined(MG32_3RD)
/** 
 * @enum		TM_INTClockSrcDef
 * @brief		Timer input clock CK_TM36 source select.
 */        
typedef enum 
{ 
    TM_PROC=0,                              /*!< CK_TMxx_PR process clock from CSC (CK_AHB/CK_APB) */
    TM_CK_LS=2                              /*!< CK_LS from (XOSC/ILRCO/ECKI) */    
} TM_INTClockSrcDef;
#endif

#if defined(MG32_4TH)
/** 
 * @enum		TM_INTClockSrcDef
 * @brief		Timer input clock CK_TM36 source select.
 */        
typedef enum 
{ 
    TM_PROC=0,                              /*!< CK_TMxx_PR process clock from CSC (CK_AHB/CK_APB) */
    TM_CK_PLL=1,                            /*!< CK_PLL from CK_PLL. */    
    TM_CK_LS=2                              /*!< CK_LS from (XOSC/ILRCO/ECKI) */    
} TM_INTClockSrcDef;
#endif

/** 
 * @enum		TM_UEVSrcDef
 * @brief		Timer input clock CK_TM36 source select.
 */        
typedef enum 
{ 
    UEV_All,                                /*!< output all UEV pulses (overflow and underflow) */
    UEV_TOF,                                /*!< output timer overflow pulses */    
    UEV_UDF                                 /*!< output timer underflow pulses */    
} TM_UEVSrcDef;

/** 
 * @enum		TM_TRGOSrcDef
 * @brief		Timer trigger output mode select
 */    
typedef enum 
{ 
    TRGO_RST,                               /*!< output TRGO from main counter's reset event */
    TRGO_EN,                                /*!< output TRGO when main counter running state */    
    TRGO_UEV,                               /*!< output TRGO when main counter has Update event */    
    TRGO_TOF,                               /*!< output TRGO (TOF flag state) */    
    TRGO_TUF,                               /*!< output TRGO (TUF flag state) */    
    TRGO_EN2,                               /*!< output TRGO when prescaler counter running */      
    TRGO_TOF2,                              /*!< output TRGO (TOF2 flag state) */    
    TRGO_TMx_DIR,                           /*!< output TRGO (Main Timer direction event) */    
    TRGO_UEV2,                              /*!< output TRGO when main counter has Update event */
    TRGO_SW,                                /*!< output TRGO by sofware */     
    TRGO_OS0,                               /*!< output TRGO (channel-0 output state) */    
    TRGO_OS1,                               /*!< output TRGO (channel-1 output state) */    
    TRGO_OS2,                               /*!< output TRGO (channel-2 output state) */    
    TRGO_OS3,                               /*!< output TRGO (channel-3 output state) */    
    TRGO_TRGI,                              /*!< output TRGI state */    
    TRGO_POE                                /*!< output TRGO (preload signal) */    
} TM_TRGOSrcDef;


/** 
 * @enum		TM_ICxMuxDef
 * @brief		config channelx input source
 */    
typedef enum 
{ 
    TMx_InputMUX_Pin,                       /*!< channel-n input trigger source from Pin */ 
    TMx_InputMUX_ITR,                       /*!< channel-n input trigger source from ITR mux */ 
    TMx_InputMUX_Line2,                     /*!< channel-n input trigger source from line2 */
    TMx_InputMUX_Line3                      /*!< channel-n input trigger source from line3 */
} TM_ICxMuxDef;


/** 
 * @enum		TM_ICxTrgDef
 * @brief		config ICx trigger event for capture data
 */    
typedef enum 
{
    IC_Disable,                             /*!< disable capture data */
    IC_RisingEdge,                          /*!< Rising edge capture data */
    IC_FallingEdge,                         /*!< Falling edge capture data */
    IC_DualEdge                             /*!< dual edge to capture data */
} TM_ICxTrgDef;


/** 
 * @enum		TM_CKOSrcDef
 * @brief		select Clock out source (Main or Prescaler counter)
 */    
typedef enum 
{
    PrescalerCKO,                           /*!< Rising edge capture data */
    MainCKO                                 /*!< disable capture data */
} TM_CKOSrcDef;

/** 
 * @enum		TM_BKExtSrcDef
 * @brief		Declare External Trigger source for Break function
 */    
typedef enum 
{
    TMBK_ExtPin=0x01,                       /*!< TM36 Break External trigger pin */
    TMBK_BOD1=0x02,                         /*!< TM36 Break External trigger event from BOD1 event */
    TMBK_INTPB=0x04,                        /*!< TM36 Break External trigger event from INT_PB */
    TMBK_ADC0OUT=0x08,                      /*!< TM36 Break External trigger event from ADC0_OUT (Window detect) */
    TMBK_COMP0OUT=0x10,                     /*!< TM36 Break External trigger event from Comparator0 output */
    TMBK_COMP1OUT=0x20,                     /*!< TM36 Break External trigger event from Comparator1 output */
    TMBK_COMP2OUT=0x40,                     /*!< TM36 Break External trigger event from Comparator2 output */
    TMBK_COMP3OUT=0x80                      /*!< TM36 Break External trigger event from Comparator3 output */
} TM_BKExtSrcDef;


/** 
 * @enum		TM_BKIntSrcDef
 * @brief		Declare Internal Trigger source for Break function
 */    
typedef enum 
{
    TMBK_ClockFailure=0x01,                 /*!< Clock failure event */
    TMBK_CPULOCKUP=0x04                     /*!< CPU LOCKUP */
} TM_BKIntSrcDef;

/** 
 * @enum		TM_BKModeDef
 * @brief		Declare Break mode
 */    
typedef enum 
{
    TM_Latch,                               /*!< Break mode : Latch mode */
    TM_CycleByCycle                         /*!< Break mode : Cycke-by-Cycle mode */
} TM_BKModeDef;

/** 
 * @enum		TM_BKPinModeDef
 * @brief		select pin output mode when Break happended
 */    
typedef enum 
{
    TM_BKStop,                              /*!< output Break Stop state (default) */
    TM_BKHold                               /*!< hold in current state  */
} TM_BKPinModeDef;

/** 
 * @enum		TM_PreloadEventSourceDef
 * @brief		Enable or Disable preload event source (XOR/INT_PB/INT_PD)
 */    
typedef enum 
{
    TM_Preload_XOR=0x01,                    /*!< Preload event from XOR-gate */
    TM_Preload_INT_PB=0x02,                 /*!< Preload event from INT_PB  */
    TM_Preload_INT_PD=0x04                  /*!< Preload event from INT_PD  */
} TM_PreloadEventSourceDef;

/** 
 * @enum		TM_OC0x3chDef
 * @brief		declare next output channel of OC0 when preload event happended
 */    
typedef enum 
{
    TM_POC00=0x01,                          /*!< select OC00 */
    TM_POC01=0x02,                          /*!< select OC01 */
    TM_POC02=0x04,                          /*!< select OC02  */
    TM_POC0_Disable=0x00                    /*!< disable preload output */
} TM_OC0x3chDef;


/** 
 * @enum		TM_OC1x3chDef
 * @brief		declare next output channel of OC1 when preload event happended
 */    
typedef enum 
{
    TM_POC10=0x10,                          /*!< select OC10 */
    TM_POC11=0x20,                          /*!< select OC11 */
    TM_POC12=0x40,                          /*!< select OC12 */
    TM_POC1_Disable=0x00                    /*!< disable preload output */
} TM_OC1x3chDef;


/** 
 * @enum		CHFMDef
 * @brief		declare function mode of channel x
 */    
typedef enum 
{
    TM_NoOperation,                         /*!< No operation */
    TM_InputCapture,                        /*!< 16 bit input capture */
    TM_OutputCompare,                       /*!< 16 bit output compare */
    TM_8bitx2OutputCompare,                 /*!< 8bitx2 output compare */
    TM_16bitPWM,                            /*!< 16bit PWM */
    TM_8bitx2PWM,                           /*!< 8bitx2 PWM */
    TM_16bitPWMDTG,                         /*!< 16bit PWM with Dead Time control */
    TM_8bitx2PWMDTG                         /*!< 8bitx2 PWM with Dead Time control */
} CHFMDef;

/** 
 * @enum		ReloadTimeDef
 * @brief		Reload simultaneously to prevent glitch 
 */    
typedef enum 
{
    TM_SimultaneouslyReload,                /*!< simultaneously reload from CCxB to CCxA when counter overflow */
    TM_StopReload                           /*!< stop reload from CCxB to CCxA when counter overflow */
} ReloadTimeDef;

/** 
 * @enum		OverWriteCmd
 * @brief		Overwrite or keep data 
 */    
typedef enum 
{
    TM_OverWrite,                           /*!< Overwritten by new data */
    TM_Keep                                 /*!< Preserved old data */
} OverWriteCmd;

/** 
 * @enum		AlignMode
 * @brief		Edge or Central align for PWM mode 
 */    
typedef enum 
{
    TM_EdgeAlign,                           /*!< Edge Left Align */
    TM_CenterAlign                          /*!< Center-Align */
} AlignMode;


#if defined(MG32_3RD)
/** 
 * @enum		TM_RCNTClockDef
 * @brief		Timer repetition counter clock source definition
 */    
typedef enum 
{
    TM_RCNT_CKMAIN,                         /*!< Clock input from Main timer overflow/underflow */
    TM_RCNT_CKCKO                           /*!< Clock input from CK_CKOM */
} TM_RCNTClockDef;
#endif


#if defined(MG32_4TH)
/** 
 * @enum		TM_RCNTClockDef
 * @brief		Timer repetition counter clock source definition
 */    
typedef enum 
{
    TM_RCNT_CKMAIN,                         /*!< Clock input from Main timer overflow/underflow */
    TM_RCNT_CKCKO,                          /*!< Clock input from CK_CKOM */
    TM_RCNT_TC                              /*!< Clock input from CK_TC */
} TM_RCNTClockDef;
#endif

/** 
 * @enum		EXUDMDSDef
 * @brief		QEI mode: special count mode - dpeend IN0/IN1 (please reference function table) 
 */    
typedef enum 
{
    TM_NoEXUD,                              /*!< No operation (up/down control by TM36_DIR) */
    TM_IN0POS,                              /*!< TMxx_IN0 positive (high level up count, low level down count) */
    TM_IN0NEG,                              /*!< TMxx_IN0 negative (low level up count, high level down count) */
#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
    TM_IN0TRG,                              /*!< TMxx_IN0 trigger (edge depending on TMxx_IN1 level) */
    TM_IN1TRG,                              /*!< TMxx_IN1 trigger (edge depending on TMxx_IN0 level) */
#endif                  
    TM_BOTH                                 /*!< Both TMxx_IN0 and TM36_IN1 edge */
} EXUDMDSDef;

/** 
 * @enum		TM_QEIResetIndexDef
 * @brief		QEI mode: special count mode - dpeend IN0/IN1 (please reference function table) 
 */    
typedef enum 
{
    TM_S1toS2,                              /*!< reset main counter between QEI state 1 and state 2 */
    TM_S2toS3,                              /*!< reset main counter between QEI state 2 and state 3 */
    TM_S3toS4,                              /*!< reset main counter between QEI state 3 and state 4 */
    TM_S4toS1                               /*!< reset main counter between QEI state 4 and state 1 */
} TM_QEIResetIndexDef;



/*! @struct TM_TimeBaseInitTypeDef
    @brief  TM Time Base Init structure definition
*/ 
typedef struct {				
    TM_CounterModeDef TM_CounterMode;	    /*!< Specifies the counter mode.  
                                                This parameter can be a value of Cascade/Separate/Full_Counter */	

    TM_DirectionDef TM_MainClockDirection;  /*!< Specifies the main clock count direction (TM_UpCount/TM_DownCount) */	

    TM_DirectionDef TM_2ndClockDirection;   /*!< Specifies the 2nd clock count direction (TM_UpCount/TM_DownCount) */	

    TM_ClockSourceDef TM_MainClockSource;   /*!< Specifies the main clock source.  
                                                This parameter can be a value of TM_CK_INT or TM_CK_EXT */	

    TM_ClockSourceDef TM_2ndClockSource;    /*!< Specifies the 2nd clock source.  
                                                This parameter can be a value of TM_CK_INT or TM_CK_EXT */	

    TM_INTClockDivDef TM_IntClockDivision;  /*!< Specifies the interrnal clock division. */
	
    uint16_t TM_Prescaler;			        /*!< Specifies the prescaler value used to divide the TM clock. 
                                                This parameter can be a number between 0x0000 and 0xFFFF 
											    PS: TM00 & TM01 only 8 bits (0x00~0xFF) */	

    uint16_t TM_Period;			            /*!< Specifies the period value to be loaded into the active Auto-Reload
                                                Register at the next update event.This parameter must be a number 
                                                between 0x0000 and 0xFFFF.  
											    PS: TM00 & TM01 only 8 bits (0x00~0xFF) */	

} TM_TimeBaseInitTypeDef;				


/** 
 * @enum		TM_ITSrc
 * @brief		TMx interrupt enable source  
 */    
typedef enum 
{
#if defined(MG32_4TH)
    TMx_IDC_IE  =   TM_INT_IDC_IE_enable_w, /*!< Input duty capture complete interrupt enable. */
#endif
#if defined(MG32_3RD) || defined(MG32_4TH)
    TMx_RTU_IE   =   TM_INT_RTU_IE_enable_w, /*!< Repetition timer underflow interrupt enable. */
#endif
    TMx_QPE_IE  =   TM_INT_QPE_IE_enable_w, /*!< Main Timer QEI phase state transition error detect interrupt enable. */
    TMx_IDX_IE  =   TM_INT_IDX_IE_enable_w, /*!< Main Timer QEI external index signal input active detect interrupt enable. */
    TMx_DIRC_IE =   TM_INT_DIRC_IE_enable_w,/*!< Main Timer up/down counting direction change interrupt enable . */
    TMx_CC3_IE  =   TM_INT_CC3_IE_enable_w, /*!< Timer IC3/OC3 interrupt enable. */
    TMx_CC2_IE  =   TM_INT_CC2_IE_enable_w, /*!< Timer IC2/OC2 interrupt enable. */
    TMx_CC1_IE  =   TM_INT_CC1_IE_enable_w, /*!< Timer IC1/OC1 interrupt enable. */
    TMx_CC0_IE  =   TM_INT_CC0_IE_enable_w, /*!< Timer IC0/OC0 interrupt enable. */
    TMx_TIE2_IE =   TM_INT_TIE2_enable_w,   /*!< 2nd Timer overflow/underflow interrupt enable. */
    TMx_TIE_IE  =   TM_INT_TIE_enable_w,    /*!< Timer overflow/underflow interrupt enable. */
    TMx_EXIE    =   TM_INT_EXIE_enable_w,   /*!< Timer external trigger interrupt enable. */
    TMx_BKIE    =   TM_INT_BKIE_enable_w,   /*!< Timer break input interrupt enable. */
    TMx_IEA     =   TM_INT_IEA_enable_w     /*!< Timer interrupt all enable. When disables, 
                                                 the timer global all interrupt event are disabled. */
} TM_ITSrc;


/** 
 * @enum		TM_ITSTAFlag
 * @brief		TMx status flag 
 */    
typedef enum 
{
#if defined(MG32_4TH)
    TMx_IDCF    =   TM_STA_IDCF_happened_w, /*!< Input duty capture complete flag. */
#endif
#if defined(MG32_3RD) || defined(MG32_4TH)
    TMx_RTUF    =   TM_STA_RTUF_happened_w, /*!< Repetition timer underflow flag. */
#endif
    TMx_QPEF    =   TM_STA_QPEF_happened_w, /*!< Main Timer QEI phase state transition error detect flag. */
    TMx_IDXF    =   TM_STA_IDXF_happened_w, /*!< Main Timer QEI external index signal input active detect. */
    TMx_DIRCF   =   TM_STA_DIRCF_happened_w,/*!< Main Timer up/down counting direction change flag. */
    TMx_CF3B    =   TM_STA_CF3B_happened_w, /*!< Timer IC3 falling edge flag/OC3 event sub flag. */
    TMx_CF2B    =   TM_STA_CF2B_happened_w, /*!< Timer IC2 falling edge flag/OC2 event sub flag. */
    TMx_CF1B    =   TM_STA_CF1B_happened_w, /*!< Timer IC1 falling edge flag/OC1 event sub flag. */
    TMx_CF0B    =   TM_STA_CF0B_happened_w, /*!< Timer IC0 falling edge flag/OC0 event sub flag. */
    TMx_CF3A    =   TM_STA_CF3A_happened_w, /*!< Timer IC3 rising edge flag/OC3 event main flag. */
    TMx_CF2A    =   TM_STA_CF2A_happened_w, /*!< Timer IC2 rising edge flag/OC2 event main flag. */
    TMx_CF1A    =   TM_STA_CF1A_happened_w, /*!< Timer IC1 rising edge flag/OC1 event main flag. */
    TMx_CF0A    =   TM_STA_CF0A_happened_w, /*!< Timer IC0 rising edge flag/OC0 event main flag. */
    TMx_TUF2    =   TM_STA_TUF2_happened_w, /*!< 2nd Timer underflow flag. */
    TMx_TUF     =   TM_STA_TUF_happened_w,  /*!< Main Timer underflow flag. */
    TMx_TOF2    =   TM_STA_TOF2_happened_w, /*!< 2nd Timer overflow flag. */
    TMx_TOF     =   TM_STA_TOF_happened_w,  /*!< Main Timer overflow flag. */
    TMx_EXF     =   TM_STA_EXF_happened_w,  /*!< Timer external trigger flag. */
    TMx_BKF     =   TM_STA_BKF_happened_w,  /*!< Timer break input flag. */
    TMx_DIRF    =   TM_STA_DIRF_down_counting_w     /*!< Main Timer up/down counting flag. */
} TM_ITSTAFlag;

#if defined(MG32_1ST) || defined(MG32_2ND) || defined(MG32_3RD)
/** 
 * @enum		DMA_TMChannelSrc
 * @brief		DMA access TM channel 0/1/2 (Compare/PWM) or channel3 (Input Capture) 
 */    
typedef enum 
{
    TMx_DMA_IC3 =   TM_CCMDS_DMA_CC3E_enable_w, /*!< Direct memory access enable for IC3 */
    TMx_DMA_OC2 =   TM_CCMDS_DMA_CC2E_enable_w, /*!< Direct memory access enable for OC2 */
    TMx_DMA_OC1 =   TM_CCMDS_DMA_CC1E_enable_w, /*!< Direct memory access enable for OC1 */
    TMx_DMA_OC0 =   TM_CCMDS_DMA_CC0E_enable_w  /*!< Direct memory access enable for OC0 */
} DMA_TMChannelSrc;
#endif

#if defined(MG32_4TH)
/** 
 * @enum		DMA_TMChannelSrc
 * @brief		DMA access TM channel 0/1/2 (Compare/PWM) or channel3 (Input Capture) 
 */    
typedef enum 
{
    TMx_DMA_IC3 =   (int) TM_CCMDS_DMA_IC3E_enable_w, /*!< Direct memory access enable for IC3 */
    TMx_DMA_IC2 =   TM_CCMDS_DMA_IC2E_enable_w, /*!< Direct memory access enable for IC3 */
    TMx_DMA_OC2 =   TM_CCMDS_DMA_CC2E_enable_w, /*!< Direct memory access enable for OC2 */
    TMx_DMA_OC1 =   TM_CCMDS_DMA_CC1E_enable_w, /*!< Direct memory access enable for OC1 */
    TMx_DMA_OC0 =   TM_CCMDS_DMA_CC0E_enable_w  /*!< Direct memory access enable for OC0 */
} DMA_TMChannelSrc;
#endif




/** 
 * @enum		DMA_UpdateEventSel
 * @brief		Config DMA request of TMx 
 */    
typedef enum 
{
    TM_UpdateEvent_TOF,                     /*!< DMA request is asserted at TOF active */
    TM_Update_TOF_ITR                       /*!< DMA request is asserted at both TOF active and ITR input signal */
} DMA_UpdateEventSel;



									 
									 


/**
 * @name	Function announce
 *   		
 */ 

///@{
void TM_DeInit(TM_Struct *TMx);
///@}

///@{
void TM_TimeBaseStruct_Init(TM_TimeBaseInitTypeDef *TM_TMBaseInitStruct);
void TM_TimeBase_Init(TM_Struct *TMx, TM_TimeBaseInitTypeDef *TM_TMBaseInitStruct);
///@}

///@{
void TM_InternalClockSource_Select(TM_Struct* TMx, TM_INTClockSrcDef INTClockSrc);
void TM_SetInternalClockDivider(TM_Struct* TMx, TM_INTClockDivDef INTClockSrc);
void TM_CounterClock_Select(TM_Struct* TMx, TM_ClockSourceDef TMClockSelect);
void TM_PrescalerClock_Select(TM_Struct* TMx, TM_ClockSourceDef TMClockSelect);
void TM_ExternalClock_Select(TM_Struct* TMx, TM_ExternalClockSourceDef TMExtClockSelect);
void TM_ITRx_Select(TM_Struct* TMx, TM_ITRSourceDef TM_ITRSource);
///@}

///@{
void TM_TimerMode_Select(TM_Struct* TMx, TM_CounterModeDef TM_TimerMode);
///@}

///@{
void TM_SetCounterDirection(TM_Struct* TMx, TM_DirectionDef DIR);
uint16_t TM_GetCounter(TM_Struct* TMx);
void TM_Counter_Config(TM_Struct* TMx, uint16_t TM_Counter, uint16_t TM_CounterReload);
void TM_Counter_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_Counter_SW(TM_Struct* TMx, TM_CounterResetGateSW_Def CMode, FunctionalState NewState);
///@}

///@{
void TM_SetPrescalerDirection(TM_Struct* TMx, TM_DirectionDef DIR);
uint16_t TM_GetPrescaler(TM_Struct* TMx);
void TM_Prescaler_Config(TM_Struct* TMx, uint16_t TM_Prescaler, uint16_t TM_PrescalerReload);
void TM_Prescaler_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_Prescaler_SW(TM_Struct* TMx, TM_PrescalerResetGateSW_Def CMode, FunctionalState NewState);
///@}

///@{
void TM_Timer_Cmd(TM_Struct* TMx, FunctionalState NewState);
///@}

///@{
void TM_GatePrescaler_SW(TM_Struct* TMx,FunctionalState NewState);
void TM_GateCounter_SW(TM_Struct* TMx,FunctionalState NewState);
void TM_ResetPrescaler_SW(TM_Struct* TMx,FunctionalState NewState);
void TM_ResetCounter_SW(TM_Struct* TMx,FunctionalState NewState);
void TM_TriggerSource_Select(TM_Struct* TMx, TM_TRGITrgSourceDef TRGISel);
void TM_TRGICounter_Select(TM_Struct* TMx, TM_TRGIModeDef TRGIMDS);
void TM_TRGIPrescaler_Select(TM_Struct* TMx, TM_TRGIModeDef TRGIMDS);
void TM_UEV_Config(TM_Struct* TMx, TM_UEVSrcDef UEVCon);
void TM_TRGOOut_SW(TM_Struct* TMx, FunctionalState NewState);
void TM_TRGO_Select(TM_Struct* TMx, TM_TRGOSrcDef TM_TRGOCon );
void TM_InverseTRGO_Cmd(TM_Struct* TMx, FunctionalState NewState);
///@}

///@{
void TM_IN0Source_Select(TM_Struct* TMx, TM_ICxMuxDef TM_ICxSrc);
void TM_IN0TriggerEvent_Select(TM_Struct* TMx, TM_ICxTrgDef TM_ICxTrg);
void TM_IN1Source_Select(TM_Struct* TMx, TM_ICxMuxDef TM_ICxSrc);
void TM_IN1TriggerEvent_Select(TM_Struct* TMx, TM_ICxTrgDef TM_ICxTrg);
void TM_IN2Source_Select(TM_Struct* TMx, TM_ICxMuxDef TM_ICxSrc);
void TM_IN2TriggerEvent_Select(TM_Struct* TMx, TM_ICxTrgDef TM_ICxTrg);
void TM_IN3Source_Select(TM_Struct* TMx, TM_ICxMuxDef TM_ICxSrc);
void TM_IN3TriggerEvent_Select(TM_Struct* TMx, TM_ICxTrgDef TM_ICxTrg);
///@}

///@{
void TM_ClockOutSource_Select(TM_Struct* TMx, TM_CKOSrcDef TM_CKOSel);
void TM_ClockOut_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_CKOOutputState_Init(TM_Struct* TMx, BitAction PinState);
///@}

///@{
void TM_InverseOC0z_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_OC0zOutputState_Init(TM_Struct* TMx, BitAction PinState);
void TM_OC0zBreakStopState_Init(TM_Struct* TMx, BitAction BKPinState);
void TM_OC0zOutput_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_OC00Output_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_OC01Output_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_OC02Output_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_InverseOC0N_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_OC0NOutput_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_OC0NBreakStopState_Init(TM_Struct* TMx, BitAction BKPinState);
void TM_InverseOC0H_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_OC0HOutputState_Init(TM_Struct* TMx, BitAction PinState);
///@}

///@{
void TM_InverseOC1z_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_OC1zOutputState_Init(TM_Struct* TMx, BitAction PinState);
void TM_OC1zBreakStopState_Init(TM_Struct* TMx, BitAction BKPinState);
void TM_OC1zOutput_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_OC10Output_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_OC11Output_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_OC12Output_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_InverseOC1N_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_OC1NOutput_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_OC1NBreakStopState_Init(TM_Struct* TMx, BitAction BKPinState);
void TM_InverseOC1H_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_OC1HOutputState_Init(TM_Struct* TMx, BitAction PinState);
///@}

///@{
void TM_InverseOC2_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_OC2OutputState_Init(TM_Struct* TMx, BitAction PinState);
void TM_OC2BreakStopState_Init(TM_Struct* TMx, BitAction BKPinState);
void TM_OC2Output_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_InverseOC2N_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_OC2NOutput_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_OC2NBreakStopState_Init(TM_Struct* TMx, BitAction BKPinState);
void TM_InverseOC2H_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_OC2HOutputState_Init(TM_Struct* TMx, BitAction PinState);
///@}

///@{
void TM_InverseOC3_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_OC3OutputState_Init(TM_Struct* TMx, BitAction PinState);
void TM_OC3BreakStopState_Init(TM_Struct* TMx, BitAction BKPinState);
void TM_OC3Output_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_InverseOC3H_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_OC3HOutputState_Init(TM_Struct* TMx, BitAction PinState);
///@}

///@{
void TM_ExternalBreakEvent_Config(TM_Struct* TMx, TM_BKExtSrcDef BKSrc, FunctionalState NewState);
void TM_InternalBreakEvent_Config(TM_Struct* TMx, TM_BKIntSrcDef BKSrc, FunctionalState NewState);
void TM_BreakTrigger_SW(TM_Struct* TMx, FunctionalState NewState);
void TM_BreakCH3_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_BreakCH012_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_BreakMode_Select(TM_Struct* TMx, TM_BKModeDef BKMode);
void TM_OC0BreakControl_Select(TM_Struct* TMx, TM_BKPinModeDef BKPinMode);
void TM_OC1BreakControl_Select(TM_Struct* TMx, TM_BKPinModeDef BKPinMode);
void TM_OC2BreakControl_Select(TM_Struct* TMx, TM_BKPinModeDef BKPinMode);
void TM_OC3BreakControl_Select(TM_Struct* TMx, TM_BKPinModeDef BKPinMode);
///@}

///@{
void TM_PreloadEventSource_Config(TM_Struct* TMx, uint8_t PreLoad, FunctionalState NewState);
void TM_PreloadActive_SW(TM_Struct* TMx, FunctionalState NewState);
void TM_PreloadOC0z_Config(TM_Struct* TMx, uint8_t TM_OC0z3ch);
void TM_PreloadOC1z_Config(TM_Struct* TMx, uint8_t TM_OC1z3ch);
///@}

///@{
void TM_CH0Function_Config(TM_Struct* TMx, CHFMDef CHFuncMds);
void TM_CH1Function_Config(TM_Struct* TMx, CHFMDef CHFuncMds);
void TM_CH2Function_Config(TM_Struct* TMx, CHFMDef CHFuncMds);
void TM_CH3Function_Config(TM_Struct* TMx, CHFMDef CHFuncMds);
///@}

#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
///@{
    void TM_OutputDelayMode_Cmd(TM_Struct* TMx, FunctionalState NewState);
///@}
#endif

///@{
uint32_t TM_GetIC0Value(TM_Struct* TMx);
uint32_t TM_GetIC1Value(TM_Struct* TMx);
uint32_t TM_GetIC2Value(TM_Struct* TMx);
uint32_t TM_GetIC3Value(TM_Struct* TMx);
///@}

///@{
void TM_IC0OverWritten_Cmd(TM_Struct* TMx, OverWriteCmd NewState);
void TM_IC1OverWritten_Cmd(TM_Struct* TMx, OverWriteCmd NewState);
void TM_IC2OverWritten_Cmd(TM_Struct* TMx, OverWriteCmd NewState);
void TM_IC3OverWritten_Cmd(TM_Struct* TMx, OverWriteCmd NewState);
///@}

///@{
void TM_RisingCaptureIC0_SW(TM_Struct* TMx, FunctionalState NewState);
void TM_RisingCaptureIC1_SW(TM_Struct* TMx, FunctionalState NewState);
void TM_RisingCaptureIC2_SW(TM_Struct* TMx, FunctionalState NewState);
void TM_RisingCaptureIC3_SW(TM_Struct* TMx, FunctionalState NewState);
void TM_FallingCaptureIC0_SW(TM_Struct* TMx, FunctionalState NewState);
void TM_FallingCaptureIC1_SW(TM_Struct* TMx, FunctionalState NewState);
void TM_FallingCaptureIC2_SW(TM_Struct* TMx, FunctionalState NewState);
void TM_FallingCaptureIC3_SW(TM_Struct* TMx, FunctionalState NewState);
///@}

///@{
uint16_t TM_GetCC0A(TM_Struct* TMx);
uint16_t TM_GetCC1A(TM_Struct* TMx);
uint16_t TM_GetCC2A(TM_Struct* TMx);
uint16_t TM_GetCC3A(TM_Struct* TMx);
uint16_t TM_GetCC0B(TM_Struct* TMx);
uint16_t TM_GetCC1B(TM_Struct* TMx);
uint16_t TM_GetCC2B(TM_Struct* TMx);
uint16_t TM_GetCC3B(TM_Struct* TMx);
///@}

///@{
void TM_SetCC0A(TM_Struct* TMx,uint16_t HfWDat);
void TM_SetCC1A(TM_Struct* TMx,uint16_t HfWDat);
void TM_SetCC2A(TM_Struct* TMx,uint16_t HfWDat);
void TM_SetCC3A(TM_Struct* TMx,uint16_t HfWDat);
void TM_SetCC0B(TM_Struct* TMx,uint16_t HfWDat);
void TM_SetCC1B(TM_Struct* TMx,uint16_t HfWDat);
void TM_SetCC2B(TM_Struct* TMx,uint16_t HfWDat);
void TM_SetCC3B(TM_Struct* TMx,uint16_t HfWDat);
///@}

///@{
void TM_GenerateCF0A_SW(TM_Struct* TMx, FunctionalState NewState);
void TM_GenerateCF1A_SW(TM_Struct* TMx, FunctionalState NewState);
void TM_GenerateCF2A_SW(TM_Struct* TMx, FunctionalState NewState);
void TM_GenerateCF3A_SW(TM_Struct* TMx, FunctionalState NewState);
void TM_GenerateCF0B_SW(TM_Struct* TMx, FunctionalState NewState);
void TM_GenerateCF1B_SW(TM_Struct* TMx, FunctionalState NewState);
void TM_GenerateCF2B_SW(TM_Struct* TMx, FunctionalState NewState);
void TM_GenerateCF3B_SW(TM_Struct* TMx, FunctionalState NewState);
///@}

///@{
void TM_ReloadFromCCxB_Cmd(TM_Struct* TMx, ReloadTimeDef NewState);
///@}

///@{
void TM_AlignmentMode_Select(TM_Struct* TMx, AlignMode AMode);
///@}

///@{
void TM_QEI_Select(TM_Struct* TMx, EXUDMDSDef EXUDMds);
void TM_QEIReset_Cmd(TM_Struct* TMx,FunctionalState NewState);
void TM_QEIResetIDX_Select(TM_Struct* TMx,TM_QEIResetIndexDef TM_IDXSel);
void TM_InverseQEIDirection(TM_Struct* TMx,FunctionalState NewState);
///@}

///@{
void TM_AutoStop_Cmd(TM_Struct* TMx, FunctionalState NewState);
#if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
    void TM_RepeatAutoStopMode_Cmd(TM_Struct* TMx, FunctionalState NewState);
#endif
#if defined(MG32_3RD) || defined(MG32_4TH)
    void TM_RepetitionCounter_Cmd(TM_Struct* TMx, FunctionalState NewState);
    void TM_ControlPWM_Cmd(TM_Struct* TMx, FunctionalState NewState);
    void TM_RepetitionCounter_Config(TM_Struct* TMx, uint8_t TM_RCounter, uint8_t TM_RCounterReload);
    void TM_RepetitionCounterClock_Select(TM_Struct* TMx, TM_RCNTClockDef RCNTClockSrc);
#endif
///@}

///@{
void TM_SetDeadZoneClockDivider(TM_Struct* TMx, TM_DTClockDivDef DTClockDiv);
void TM_SetDeadTime(TM_Struct* TMx, uint8_t DTTime);
///@}

#if defined(MG32_4TH)
///@{
void TM_DutyCapture_Cmd(TM_Struct* TMx, FunctionalState NewState);
///@}
#endif

///@{
void TM_IT_Config(TM_Struct* TMx, uint32_t TM_ITSrc, FunctionalState NewState);
void TM_ITEA_Cmd(TM_Struct* TMx, FunctionalState NewState);
DRV_Return TM_GetSingleFlagStatus(TM_Struct* TMx, uint32_t TM_ITSTAFlag);
uint32_t TM_GetAllFlagStatus(TM_Struct* TMx);
void TM_ClearFlag(TM_Struct* TMx, uint32_t TM_ITSrc);
///@}

///@{
void TM_ExtTRGI_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_InverseExtTRGI_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_ExtTRGI2UEV_Cmd(TM_Struct* TMx, FunctionalState NewState);
void TM_ForceUpdate_SW(TM_Struct* TMx, FunctionalState NewState);
void TM_UEV_Cmd(TM_Struct* TMx, FunctionalState NewState);
///@}

///@{
void TM_DMAChannel_Cmd(TM_Struct* TMx, uint32_t DMA_TMChannelSrc, FunctionalState NewState);
void TM_DMAUpdateMode_Select(TM_Struct* TMx, DMA_UpdateEventSel TM_UpdateEvent);
///@}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif


