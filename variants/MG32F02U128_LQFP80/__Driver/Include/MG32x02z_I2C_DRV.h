/**
 ******************************************************************************
 *
 * @file        MG32x02z_I2C_DRV.h
 *
 * @brief       This is the C code format driver head file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V2.22
 * @date        2021/09/07
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************
 * @par         Disclaimer 
 *      The Demo software is provided "AS IS"  without any warranty, either 
 *      expressed or implied, including, but not limited to, the implied warranties 
 *      of merchantability and fitness for a particular purpose.  The author will 
 *      not be liable for any special, incidental, consequential or indirect 
 *      damages due to loss of data or any other reason. 
 *      These statements agree with the world wide and local dictated laws about 
 *      authorship and violence against these laws. 
 ******************************************************************************
 ******************************************************************************
 */



#ifndef __MG32x02z_I2C_DRV_H
#define __MG32x02z_I2C_DRV_H
//#define _MG32x02z_I2C_DRV_H_VER                            2.21

#include "MG32x02z__Common_DRV.h"
#include "MG32x02z_I2C.h"



/**
 * @name    Clock 
 *          Clock Definition
 */
///@{

/** @brief  I2C internal clock CK_I2C source select.
  */
#define I2C_CLK_SRC_MASK                I2C_CLK_CK_SEL_mask_b0
#define I2C_CLK_SRC_PROC                I2C_CLK_CK_SEL_proc_b0          /* CK_I2C0_PR process clock from CSC */
#define I2C_CLK_SRC_TM00_TROG           I2C_CLK_CK_SEL_tm00_trgo_b0



/** @brief  I2C internal clock CK_I2C_INT prescaler. The value range 0~7 is indicated divider 1~8.
  */
#define I2C_CLK_PSC_MASK                ((uint8_t)I2C_CLK_CK_PSC_mask_b1)
#define I2C_CLK_PSC_1                   ((uint8_t)0x00U)
#define I2C_CLK_PSC_2                   ((uint8_t)0x01U)
#define I2C_CLK_PSC_3                   ((uint8_t)0x02U)
#define I2C_CLK_PSC_4                   ((uint8_t)0x03U)
#define I2C_CLK_PSC_5                   ((uint8_t)0x04U)
#define I2C_CLK_PSC_6                   ((uint8_t)0x05U)
#define I2C_CLK_PSC_7                   ((uint8_t)0x06U)
#define I2C_CLK_PSC_8                   ((uint8_t)0x07U)



/** @brief  I2C internal clock CK_I2C_INT input divider.
  */
#define I2C_CLK_DIV_MASK                I2C_CLK_CK_DIV_mask_b0
#define I2C_CLK_DIV_SHIFT               0x04U
#define I2C_CLK_DIV_1                   I2C_CLK_CK_DIV_div1_b0
#define I2C_CLK_DIV_2                   I2C_CLK_CK_DIV_div2_b0
#define I2C_CLK_DIV_4                   I2C_CLK_CK_DIV_div4_b0
#define I2C_CLK_DIV_8                   I2C_CLK_CK_DIV_div8_b0
#define I2C_CLK_DIV_16                  I2C_CLK_CK_DIV_div16_b0
#define I2C_CLK_DIV_32                  I2C_CLK_CK_DIV_div32_b0
#define I2C_CLK_DIV_64                  I2C_CLK_CK_DIV_div64_b0
#define I2C_CLK_DIV_128                 I2C_CLK_CK_DIV_div128_b0



/** @brief  I2C SCL high cycle time by CK_I2C_INT clock time.
            It write setting value for master mode. 
            (SCL High time = START hold time = STOP setup time)
  */
#define I2C_SCL_HT_MASK                 I2C_CR1_HT_mask_w
#define I2C_SCL_HT_SHIFT                8



/** @brief  I2C SCL low cycle time by CK_I2C_INT clock time.
            It write setting value for master mode. 
            (SCL Low time = START setup time = Bus free time between STOP and START)
  */
#define I2C_SCL_LT_MASK                 I2C_CR1_LT_mask_w
#define I2C_SCL_LT_SHIFT                0



/** @brief  I2C pre-drive time select for both SCL and SDA by CK_I2C clock time.
  */
#define I2C_PDRV_MASK                   I2C_CR0_PDRV_SEL_mask_b1
#define I2C_PDRV_0T                     I2C_CR0_PDRV_SEL_0t_b1
#define I2C_PDRV_1T                     I2C_CR0_PDRV_SEL_1t_b1
#define I2C_PDRV_2T                     I2C_CR0_PDRV_SEL_2t_b1
#define I2C_PDRV_3T                     I2C_CR0_PDRV_SEL_3t_b1

///@}



/**
 * @name    I2C Operation.
 *          I2C Operation Mode.
 */
///@{

/** @brief  I2C Operation mode select.
  */
#define I2C_MDS_MASK                    I2C_CR0_MDS_mask_b0
#define I2C_MDS_I2C                     I2C_CR0_MDS_i2c_b0                      /* I2C : Single/Multi-Master/ Slave mode */



/** @brief  I2C Slave Address
  */
#define I2C_SADR_0                      I2C_CR0_GC_EN_mask_w                    /* I2C general call address 0x00 recognized */
#define I2C_SADR_1                      I2C_CR0_SADR_EN_mask_w                  /* I2C slave mode main slave address detect. */
#define I2C_SADR_2                      I2C_CR0_SADR2_EN_mask_w                 /* I2C slave mode 2nd slave address detect. */

///@}



/**
 * @name    Interript & Flag
 *          Interript & Flag definition
 */
///@{

/** @brief  Flag definition 
  */
#define I2C_FLAG_BUSYF                  I2C_STA_BUSYF_mask_w                    /* I2C busy flag. (set and clear by hardware) */
#define I2C_FLAG_EVENTF                 I2C_STA_EVENTF_mask_w                   /* I2C status event interrupt Flag. (set by hardware , clear by software setting 1)*/
#define I2C_FLAG_BUFF                   I2C_STA_BUFF_mask_w                     /* I2C buffer mode event flag. (set by hardware , clear by software setting 1)*/
#define I2C_FLAG_ERRF                   I2C_STA_ERRF_mask_w                     /* I2C error interrupt flag. for invalid no ack, bus arbitration lost, bus error or data overrun error. */
#define I2C_FLAG_TMOUTF                 I2C_STA_TMOUTF_mask_w                   /* I2C time-out detect flag. (set and clear by hardware)*/
#define I2C_FLAG_RXF                    I2C_STA_RXF_mask_w                      /* I2C Receive data register not empty. (set by hardware and clear by hardware or software writing 1) This bit is cleared when I2C_DAT is read or this flag set to 1 by software.*/
#define I2C_FLAG_TXF                    I2C_STA_TXF_mask_w                      /* I2C Transmit data register empty.  (set by hardware and clear by hardware or software writing 1) This bit is cleared when I2C_DAT is written or this flag set to 1 by software. The flag is set after I2C reset or Idle state.*/
#define I2C_FLAG_RSTRF                  I2C_STA_RSTRF_mask_w                    /* I2C repeat start asserted flag. (set by hardware and clear by software writing 1)*/
#define I2C_FLAG_STOPF                  I2C_STA_STOPF_mask_w                    /* I2C stop detection flag. (set by hardware and clear by software writing 1)*/
#define I2C_FLAG_CNTF                   I2C_STA_CNTF_mask_w                     /* I2C buffer count I2C0_BUF_CNT empty status.  (set by hardware and clear by software writing 1 or I2C_BUF_CNT written)*/
#define I2C_FLAG_ERRCF                  I2C_STA_ERRCF_mask_w                    /* I2C master mode NACK error flag and state control bit. (set by hardware and clear by software writing 1 or hardware auto clear during START/STOP state) This bit is asserted if occurs NACK during slave-address cycle or data cycle of receive access.*/
#define I2C_FLAG_SADRF                  I2C_STA_SADRF_mask_w                    /* I2C slave mode slave address matched flag. This flag is also asserted for master mode if transmit mode slave address unmatched or received mode slave address asserted. When wakeup from STOP mode by detection matched slave address, user needs to clear this bit to disable the clock stretching and releases clock signal for external master. (set by hardware and clear by software writing 1)*/
#define I2C_FLAG_SLAF                   I2C_STA_SLAF_mask_w                     /* I2C slave mode detection status. It set by Slave address matched condition and clear by Start/Stop conditions.*/
#define I2C_FLAG_MSTF                   I2C_STA_MSTF_mask_w                     /* I2C master mode detection status. It set by Start command and clear by Stop state.*/
#define I2C_FLAG_RWF                    I2C_STA_RWF_mask_w                      /* I2C read or write transfer direction status. It always update at slave address r/w state.*/
#define I2C_FLAG_TSCF                   I2C_STA_TSCF_mask_w                     /* I2C shadow buffer transfer complete flag. (set by hardware and clear by hardware or software writing 1)*/
#define I2C_FLAG_TXRF                   I2C_STA_TXRF_mask_w                     /* I2C transmit data register remained status.  (set and clear by hardware) When occurs bus NACK error and I2C_NACKF is asserted, this bit is used to check the data register contain whether has remain data when master STOP and calculate the corrected total transfer count by I2C_ACNT. It is cleared in slave address matched state and updated after last byte NACK state.*/
#define I2C_FLAG_ROVRF                  I2C_STA_ROVRF_mask_w                    /* I2C data buffer receive overrun error flag. Under the conditions, slave mode enables data buffer mode and clock stretching is disabled. When the data buffer is overrun, this bit is set and interrupt is generated if I2C_ERR_IE is enabled. Also, the I2C_ERRF is set. (set by hardware and clear by software writing 1)*/
#define I2C_FLAG_TOVRF                  I2C_STA_TOVRF_mask_w                    /* I2C data buffer transmit underrun error flag. Under the conditions, slave mode enables data buffer mode and clock stretching is disabled. When the data buffer is underrun, this bit is set and interrupt is generated if I2C_ERR_IE is enabled. Also, the I2C_ERRF is set. (set by hardware and clear by software writing 1)*/
#define I2C_FLAG_NACKF                  I2C_STA_NACKF_mask_w                    /* I2C Not Acknowledge received error flag. (set by hardware and clear by software writing 1)*/ 
#define I2C_FLAG_ALOSF                  I2C_STA_ALOSF_mask_w                    /* I2C bus arbitration lost error flag. (set by hardware and clear by software writing 1)*/
#define I2C_FLAG_BERRF                  I2C_STA_BERRF_mask_w                    /* I2C bus error flag for invalid Stop/Start state. (set by hardware and clear by software writing 1)*/
#if defined(MG32_1ST)
  #define I2C_FLAG_STPSTRF              0                                       /* I2C Bus Stop or Bus Start detection flag. (set by hardware and clear by software writing 1)*/
  #define I2C_FLAG_WUPF                 0                                       /* I2C wakeup from STOP mode flag. set by hardware and clear by software writing 1)*/ 
#else
  #define I2C_FLAG_STPSTRF              I2C_STA_STPSTRF_mask_w                  /* I2C Bus Stop or Bus Start detection flag. (set by hardware and clear by software writing 1)*/
  #define I2C_FLAG_WUPF                 I2C_STA_WUPF_mask_w                     /* I2C wakeup from STOP mode flag. set by hardware and clear by software writing 1)*/ 
#endif



/** @brief  Interrup Enable Definition
  */
#define I2C_IT_IEA                      I2C_INT_IEA_mask_w                      /* I2C interrupt all enable. When disables, the I2C global all interrupt event are disabled. When enables, the related event interrupt enable bit is to enable or disable the interrupt. */
#define I2C_IT_TMOUT                    I2C_INT_TMOUT_IE_mask_w                 /* I2C timeout error interrupt enable. */
#define I2C_IT_EVENT                    I2C_INT_EVENT_IE_mask_w                 /* I2C status event interrupt enable. */
#define I2C_IT_ERR                      I2C_INT_ERR_IE_mask_w                   /* I2C no ack error, bus arbitration lost, bus error or data overrun interrupt enable. */
#define I2C_IT_BUF                      I2C_INT_BUF_IE_mask_w                   /* I2C buffer mode event Interrupt enable. When enables, it will generate the interrupt if the flag of I2C_RXF, I2C_TXF, I2C_RSTRF, I2C_STOPF or I2C_SADRF is set. */
#if defined(MG32_1ST)
  #define I2C_IT_STPSTR                 0                                       /* I2C Stop or Start detection interrupt enable. */
  #define I2C_IT_WUP                    0                                       /* I2C wakeup from STOP mode interrupt enable on slave address matched. */
#else
  #define I2C_IT_STPSTR                 I2C_INT_STPSTR_IE_mask_w                /* I2C Stop or Start detection interrupt enable. */
  #define I2C_IT_WUP                    I2C_INT_WUP_IE_mask_w                   /* I2C wakeup from STOP mode interrupt enable on slave address matched. */
#endif
///@}



/**
 * @name    TimeOut Config
 *          TimeOut Config
 */
///@{

/** @brief  TimeOut Count Clock Source
  */

#define I2C_TMO_CKS_MASK                I2C_CLK_TMO_CKS_mask_w
#define I2C_TMO_CKS_CK_UT               I2C_CLK_TMO_CKS_ck_ut_w
#define I2C_TMO_CKS_DIV64               I2C_CLK_TMO_CKS_div64_w


/** @brief  TimeOut Mode sELECT
  */

#define I2C_TMO_MDS_MASK                I2C_TMOUT_TMO_MDS_mask_w
#define I2C_TMO_MDS_SCL_LOW             I2C_TMOUT_TMO_MDS_scl_low_w
#define I2C_TMO_MDS_SDA_SCL_HIGH        I2C_TMOUT_TMO_MDS_scl_sda_high_w
#define I2C_TMO_MDS_GENERAL             I2C_TMOUT_TMO_MDS_general_w

///@}



/**
 * @name    Start / Stop / Acknowledge Enable / Disable.
 *          Start / Stop / Acknowledge Enable / Disable.
 */
///@{

/** @brief  Start / Stop / Acknowledge Enable / Disable.
    @retval None
  */
#define __I2C_PreSet_ASSERT_ACKNOWLEDGE_CLR(I2Cx__)   (I2Cx__)->CR2.B[0] = (((I2Cx__)->CR2.B[0]& ~I2C_CR2_AA_mask_b0) | (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_AA_LCK_mask_b0))
#define __I2C_PreSet_ASSERT_ACKNOWLEDGE_SET(I2Cx__)   (I2Cx__)->CR2.B[0] = ((I2Cx__)->CR2.B[0] | (I2C_CR2_AA_mask_b0 | I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_AA_LCK_mask_b0))
#define __I2C_Set_ASSERT_ACKNOWLEDGE_CLR(I2Cx__)      (I2Cx__)->CR2.B[0] = (((I2Cx__)->CR2.B[0]& ~(I2C_CR2_AA_mask_b0 | I2C_CR2_CMD_TC_mask_b0)) | I2C_CR2_AA_LCK_mask_b0)
#define __I2C_Set_ASSERT_ACKNOWLEDGE_SET(I2Cx__)      (I2Cx__)->CR2.B[0] = (((I2Cx__)->CR2.B[0]& ~I2C_CR2_CMD_TC_mask_b0) | (I2C_CR2_AA_mask_b0 | I2C_CR2_AA_LCK_mask_b0))
#define __I2C_PAA_0                             __I2C_PreSet_ASSERT_ACKNOWLEDGE_CLR 
#define __I2C_PAA_1                             __I2C_PreSet_ASSERT_ACKNOWLEDGE_SET
#define __I2C_AA_0                              __I2C_Set_ASSERT_ACKNOWLEDGE_CLR
#define __I2C_AA_1                              __I2C_Set_ASSERT_ACKNOWLEDGE_SET
#define PreSet_ASSERT_ACKNOWLEDGE_CLR(I2Cx__)   (I2Cx__)->CR2.B[0] = (((I2Cx__)->CR2.B[0]& ~I2C_CR2_AA_mask_b0) | (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_AA_LCK_mask_b0))
#define PreSet_ASSERT_ACKNOWLEDGE_SET(I2Cx__)   (I2Cx__)->CR2.B[0] = ((I2Cx__)->CR2.B[0] | (I2C_CR2_AA_mask_b0 | I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_AA_LCK_mask_b0))
#define Set_ASSERT_ACKNOWLEDGE_CLR(I2Cx__)      (I2Cx__)->CR2.B[0] = (((I2Cx__)->CR2.B[0]& ~(I2C_CR2_AA_mask_b0 | I2C_CR2_CMD_TC_mask_b0)) | I2C_CR2_AA_LCK_mask_b0)
#define Set_ASSERT_ACKNOWLEDGE_SET(I2Cx__)      (I2Cx__)->CR2.B[0] = (((I2Cx__)->CR2.B[0]& ~I2C_CR2_CMD_TC_mask_b0) | (I2C_CR2_AA_mask_b0 | I2C_CR2_AA_LCK_mask_b0))
#define PAA_0                                   PreSet_ASSERT_ACKNOWLEDGE_CLR 
#define PAA_1                                   PreSet_ASSERT_ACKNOWLEDGE_SET
#define AA_0                                    Set_ASSERT_ACKNOWLEDGE_CLR
#define AA_1                                    Set_ASSERT_ACKNOWLEDGE_SET

#define __I2C_PreSet_START_CLR(I2Cx__)          (I2Cx__)->CR2.B[0] = (((I2Cx__)->CR2.B[0]& ~I2C_CR2_STA_mask_b0) | (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0))
#define __I2C_PreSet_START_SET(I2Cx__)          (I2Cx__)->CR2.B[0] = ((I2Cx__)->CR2.B[0] | (I2C_CR2_STA_mask_b0 | I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0))
#define __I2C_Set_START_CLR(I2Cx__)             (I2Cx__)->CR2.B[0] = (((I2Cx__)->CR2.B[0]& ~(I2C_CR2_STA_mask_b0 | I2C_CR2_CMD_TC_mask_b0)) | I2C_CR2_STA_LCK_mask_b0)
#define __I2C_Set_START_SET(I2Cx__)             (I2Cx__)->CR2.B[0] = (((I2Cx__)->CR2.B[0]& ~I2C_CR2_CMD_TC_mask_b0) | (I2C_CR2_STA_mask_b0 | I2C_CR2_STA_LCK_mask_b0))
#define __I2C_PSTA_0                            __I2C_PreSet_START_CLR
#define __I2C_PSTA_1                            __I2C_PreSet_START_SET
#define __I2C_STA_0                             __I2C_Set_START_CLR
#define __I2C_STA_1                             __I2C_Set_START_SET
#define PreSet_START_CLR(I2Cx__)                (I2Cx__)->CR2.B[0] = (((I2Cx__)->CR2.B[0]& ~I2C_CR2_STA_mask_b0) | (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0))
#define PreSet_START_SET(I2Cx__)                (I2Cx__)->CR2.B[0] = ((I2Cx__)->CR2.B[0] | (I2C_CR2_STA_mask_b0 | I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0))
#define Set_START_CLR(I2Cx__)                   (I2Cx__)->CR2.B[0] = (((I2Cx__)->CR2.B[0]& ~(I2C_CR2_STA_mask_b0 | I2C_CR2_CMD_TC_mask_b0)) | I2C_CR2_STA_LCK_mask_b0)
#define Set_START_SET(I2Cx__)                   (I2Cx__)->CR2.B[0] = (((I2Cx__)->CR2.B[0]& ~I2C_CR2_CMD_TC_mask_b0) | (I2C_CR2_STA_mask_b0 | I2C_CR2_STA_LCK_mask_b0))
#define PSTA_0                                  PreSet_START_CLR
#define PSTA_1                                  PreSet_START_SET
#define STA_0                                   Set_START_CLR
#define STA_1                                   Set_START_SET

#define __I2C_PreSet_STOP_CLR(I2Cx__)           (I2Cx__)->CR2.B[0] = (((I2Cx__)->CR2.B[0]& ~I2C_CR2_STO_mask_b0) | (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STO_LCK_mask_b0))
#define __I2C_PreSet_STOP_SET(I2Cx__)           (I2Cx__)->CR2.B[0] = ((I2Cx__)->CR2.B[0] | (I2C_CR2_STO_mask_b0 | I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STO_LCK_mask_b0))
#define __I2C_Set_STOP_CLR(I2Cx__)              (I2Cx__)->CR2.B[0] = (((I2Cx__)->CR2.B[0]& ~(I2C_CR2_STO_mask_b0 | I2C_CR2_CMD_TC_mask_b0)) | I2C_CR2_STO_LCK_mask_b0)
#define __I2C_Set_STOP_SET(I2Cx__)              (I2Cx__)->CR2.B[0] = (((I2Cx__)->CR2.B[0]& ~I2C_CR2_CMD_TC_mask_b0) | (I2C_CR2_STO_mask_b0 | I2C_CR2_STO_LCK_mask_b0))
#define __I2C_PSTO_0                            __I2C_PreSet_STOP_CLR
#define __I2C_PSTO_1                            __I2C_PreSet_STOP_SET
#define __I2C_STO_0                             __I2C_Set_STOP_CLR
#define __I2C_STO_1                             __I2C_Set_STOP_SET
#define PreSet_STOP_CLR(I2Cx__)                 (I2Cx__)->CR2.B[0] = (((I2Cx__)->CR2.B[0]& ~I2C_CR2_STO_mask_b0) | (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STO_LCK_mask_b0))
#define PreSet_STOP_SET(I2Cx__)                 (I2Cx__)->CR2.B[0] = ((I2Cx__)->CR2.B[0] | (I2C_CR2_STO_mask_b0 | I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STO_LCK_mask_b0))
#define Set_STOP_CLR(I2Cx__)                    (I2Cx__)->CR2.B[0] = (((I2Cx__)->CR2.B[0]& ~(I2C_CR2_STO_mask_b0 | I2C_CR2_CMD_TC_mask_b0)) | I2C_CR2_STO_LCK_mask_b0)
#define Set_STOP_SET(I2Cx__)                    (I2Cx__)->CR2.B[0] = (((I2Cx__)->CR2.B[0]& ~I2C_CR2_CMD_TC_mask_b0) | (I2C_CR2_STO_mask_b0 | I2C_CR2_STO_LCK_mask_b0))
#define PSTO_0                                  PreSet_STOP_CLR
#define PSTO_1                                  PreSet_STOP_SET
#define STO_0                                   Set_STOP_CLR
#define STO_1                                   Set_STOP_SET

#define __I2C_PreSet_STA_STO_AA_111(I2Cx__)     ((I2Cx__)->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STA_mask_b0 | I2C_CR2_STO_mask_b0 | I2C_CR2_AA_mask_b0))
#define __I2C_PreSet_STA_STO_AA_110(I2Cx__)     ((I2Cx__)->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STA_mask_b0 | I2C_CR2_STO_mask_b0))
#define __I2C_PreSet_STA_STO_AA_101(I2Cx__)     ((I2Cx__)->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STA_mask_b0 | I2C_CR2_AA_mask_b0))
#define __I2C_PreSet_STA_STO_AA_100(I2Cx__)     ((I2Cx__)->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STA_mask_b0))
#define __I2C_PreSet_STA_STO_AA_011(I2Cx__)     ((I2Cx__)->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STO_mask_b0 | I2C_CR2_AA_mask_b0))
#define __I2C_PreSet_STA_STO_AA_010(I2Cx__)     ((I2Cx__)->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STO_mask_b0))
#define __I2C_PreSet_STA_STO_AA_001(I2Cx__)     ((I2Cx__)->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_AA_mask_b0))
#define __I2C_PreSet_STA_STO_AA_000(I2Cx__)     ((I2Cx__)->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0))

#define PreSet_STA_STO_AA_111(I2Cx__)           ((I2Cx__)->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STA_mask_b0 | I2C_CR2_STO_mask_b0 | I2C_CR2_AA_mask_b0))
#define PreSet_STA_STO_AA_110(I2Cx__)           ((I2Cx__)->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STA_mask_b0 | I2C_CR2_STO_mask_b0))
#define PreSet_STA_STO_AA_101(I2Cx__)           ((I2Cx__)->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STA_mask_b0 | I2C_CR2_AA_mask_b0))
#define PreSet_STA_STO_AA_100(I2Cx__)           ((I2Cx__)->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STA_mask_b0))
#define PreSet_STA_STO_AA_011(I2Cx__)           ((I2Cx__)->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STO_mask_b0 | I2C_CR2_AA_mask_b0))
#define PreSet_STA_STO_AA_010(I2Cx__)           ((I2Cx__)->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STO_mask_b0))
#define PreSet_STA_STO_AA_001(I2Cx__)           ((I2Cx__)->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_AA_mask_b0))
#define PreSet_STA_STO_AA_000(I2Cx__)           ((I2Cx__)->CR2.B[0] = (I2C_CR2_CMD_TC_mask_b0 | I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0))

#define PAction_111                             PreSet_STA_STO_AA_111
#define PAction_110                             PreSet_STA_STO_AA_110
#define PAction_101                             PreSet_STA_STO_AA_101
#define PAction_100                             PreSet_STA_STO_AA_100
#define PAction_011                             PreSet_STA_STO_AA_011
#define PAction_010                             PreSet_STA_STO_AA_010
#define PAction_001                             PreSet_STA_STO_AA_001
#define PAction_000                             PreSet_STA_STO_AA_000

#define __I2C_Set_STA_STO_AA_111(I2Cx__)        ((I2Cx__)->CR2.B[0] = (I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STA_mask_b0 | I2C_CR2_STO_mask_b0 | I2C_CR2_AA_mask_b0))
#define __I2C_Set_STA_STO_AA_110(I2Cx__)        ((I2Cx__)->CR2.B[0] = (I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STA_mask_b0 | I2C_CR2_STO_mask_b0))
#define __I2C_Set_STA_STO_AA_101(I2Cx__)        ((I2Cx__)->CR2.B[0] = (I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STA_mask_b0 | I2C_CR2_AA_mask_b0))
#define __I2C_Set_STA_STO_AA_100(I2Cx__)        ((I2Cx__)->CR2.B[0] = (I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STA_mask_b0))
#define __I2C_Set_STA_STO_AA_011(I2Cx__)        ((I2Cx__)->CR2.B[0] = (I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STO_mask_b0 | I2C_CR2_AA_mask_b0))
#define __I2C_Set_STA_STO_AA_010(I2Cx__)        ((I2Cx__)->CR2.B[0] = (I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STO_mask_b0))
#define __I2C_Set_STA_STO_AA_001(I2Cx__)        ((I2Cx__)->CR2.B[0] = (I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_AA_mask_b0))
#define __I2C_Set_STA_STO_AA_000(I2Cx__)        ((I2Cx__)->CR2.B[0] = (I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0))

#define Set_STA_STO_AA_111(I2Cx__)              ((I2Cx__)->CR2.B[0] = (I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STA_mask_b0 | I2C_CR2_STO_mask_b0 | I2C_CR2_AA_mask_b0))
#define Set_STA_STO_AA_110(I2Cx__)              ((I2Cx__)->CR2.B[0] = (I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STA_mask_b0 | I2C_CR2_STO_mask_b0))
#define Set_STA_STO_AA_101(I2Cx__)              ((I2Cx__)->CR2.B[0] = (I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STA_mask_b0 | I2C_CR2_AA_mask_b0))
#define Set_STA_STO_AA_100(I2Cx__)              ((I2Cx__)->CR2.B[0] = (I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STA_mask_b0))
#define Set_STA_STO_AA_011(I2Cx__)              ((I2Cx__)->CR2.B[0] = (I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STO_mask_b0 | I2C_CR2_AA_mask_b0))
#define Set_STA_STO_AA_010(I2Cx__)              ((I2Cx__)->CR2.B[0] = (I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_STO_mask_b0))
#define Set_STA_STO_AA_001(I2Cx__)              ((I2Cx__)->CR2.B[0] = (I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0 | I2C_CR2_AA_mask_b0))
#define Set_STA_STO_AA_000(I2Cx__)              ((I2Cx__)->CR2.B[0] = (I2C_CR2_STA_LCK_mask_b0 | I2C_CR2_STO_LCK_mask_b0 | I2C_CR2_AA_LCK_mask_b0))

#define Action_111                              Set_STA_STO_AA_111
#define Action_110                              Set_STA_STO_AA_110
#define Action_101                              Set_STA_STO_AA_101
#define Action_100                              Set_STA_STO_AA_100
#define Action_011                              Set_STA_STO_AA_011
#define Action_010                              Set_STA_STO_AA_010
#define Action_001                              Set_STA_STO_AA_001
#define Action_000                              Set_STA_STO_AA_000

#define __I2C_WaitSTOClear(I2Cx__)              while(((I2Cx__)->CR2.B[0] & I2C_CR2_STO_mask_b0) != 0)
///@}



#ifdef __cplusplus
 extern "C" {
#endif

/**
 * @name    Clcok Control
 *          Operation Clock Setting
 */
///@{

#define __I2C_SetClockSource(I2Cx__, I2C_CLK_SRC)   ((I2Cx__)->CLK.B[0] = ((((I2Cx__)->CLK.B[0]) & (~I2C_CLK_CK_SEL_mask_b0)) | ((uint8_t)I2C_CLK_SRC)))
void I2C_SetClockSource(I2C_Struct* I2Cx, uint8_t Select);

#define __I2C_SetClockPrescaler(I2Cx__, I2C_CLK_PSC__)    ((I2Cx__)->CLK.B[1] = (((I2Cx__)->CLK.B[1] & (~I2C_CLK_PSC_MASK)) | ((uint8_t)I2C_CLK_PSC__)))
void I2C_SetClockPrescaler(I2C_Struct* I2Cx, uint8_t Select);

#define __I2C_SetClockDivider(I2Cx__, I2C_CLK_DIV)  ((I2Cx__)->CLK.B[0] = ((((I2Cx__)->CLK.B[0]) & (~I2C_CLK_CK_DIV_mask_b0)) | ((uint8_t)I2C_CLK_DIV)))
void I2C_SetClockDivider(I2C_Struct* I2Cx, uint8_t Select);

#define __I2C_SetSCLHighTime(I2Cx__, HighTime__)    ((I2Cx__)->CR1.B[1] = ((uint8_t)HighTime__))
void I2C_SetSCLHighTime(I2C_Struct* I2Cx, uint8_t HighTime);

#define __I2C_SetSCLLowTime(I2Cx__, LowTime__)     ((I2Cx__)->CR1.B[0] = ((uint8_t)LowTime__))
void I2C_SetSCLLowTime(I2C_Struct* I2Cx, uint8_t LowTime);

#define __I2C_SetPreDriveTime(I2Cx__, I2C_PDRV)     ((I2Cx__)->CR0.W) = (((I2Cx__)->CR0.W & I2C_PDRV_MASK) | I2C_PDRV)
void I2C_SetPreDriveTime(I2C_Struct* I2Cx, uint32_t Select);
///@}


/**
 * @name    Mode
 *          Operation Mode Setting
 */
///@{
#define __I2C_GeneralCallAddress_Enable(I2Cx__)     (I2Cx__)->CR0.W |= I2C_CR0_GC_EN_mask_w
#define __I2C_GeneralCallAddress_Disable(I2Cx__)    (I2Cx__)->CR0.W &= (~I2C_CR0_GC_EN_mask_w)
void I2C_GeneralCallAddress_Cmd(I2C_Struct* I2Cx, FunctionalState State);

#define __I2C_SlaveAddressDetect_Enable(I2Cx__, SADRx__)    (I2Cx__)->CR0.W |= (SADRx__)
#define __I2C_SlaveAddressDetect_Disable(I2Cx__, SADRx__)   (I2Cx__)->CR0.W &= (~(SADRx__))
void I2C_SlaveAddressDetect_Cmd(I2C_Struct* I2Cx, uint8_t I2C_SADRx, FunctionalState State);

#define __I2C_SetSlaveAddress(I2Cx__, SADR__)   (I2Cx__)->SADR.W = (SADR__)
#define __I2C_SetSlaveAddress1(I2Cx__, SADR__)  (I2Cx__)->SADR.B[0] = (SADR__)
#define __I2C_SetSlaveAddress2(I2Cx__, SADR__)  (I2Cx__)->SADR.B[1] = (SADR__)
void I2C_SetSlaveAddress(I2C_Struct* I2Cx, uint8_t I2C_SADRx, uint8_t Address);

#if !defined(MG32_1ST)
  #define __I2C_SetSlaveAddress1Mask(__I2Cx__, __MASK__)    (__I2Cx__)->MASK.B[0] = (__MASK__)
  void I2C_SetSlaveAddress1Mask(I2C_Struct* I2Cx, uint8_t I2C_SlaveAddress1Mask);
#endif

uint8_t I2C_GetSlaveAddress(I2C_Struct* I2Cx, uint8_t I2C_SADRx);

#define __I2C_Enable(I2Cx__)                    ((I2Cx__)->CR0.B[0] |= I2C_CR0_EN_mask_b0)
#define __I2C_Disable(I2Cx__)                   ((I2Cx__)->CR0.B[0] &= (~I2C_CR0_EN_mask_b0))
#define __I2C_GetEnableStatus(I2Cx__)           (((I2Cx__)->CR0.B[0] & I2C_CR0_EN_mask_b0)?ENABLE:DISABLE)
void I2C_Cmd(I2C_Struct* I2Cx, FunctionalState State);
///@}



/**
 * @name    DMA
 *          Operation Mode Setting
 */
///@{
#define __I2C_TXDMA_Enable(I2Cx__)              ((I2Cx__)->CR0.B[3] |= I2C_CR0_DMA_TXEN_mask_b3)
#define __I2C_TXDMA_Disable(I2Cx__)             ((I2Cx__)->CR0.B[3] &= ~I2C_CR0_DMA_TXEN_mask_b3)
void I2C_TXDMA_Cmd( I2C_Struct* I2Cx, FunctionalState State);


#define __I2C_RXDMA_Enable(I2Cx__)              ((I2Cx__)->CR0.B[3] |= I2C_CR0_DMA_RXEN_mask_b3)
#define __I2C_RXDMA_Disable(I2Cx__)             ((I2Cx__)->CR0.B[3] &= ~I2C_CR0_DMA_RXEN_mask_b3)
void I2C_RXDMA_Cmd(I2C_Struct* I2Cx, FunctionalState State);
///@}



/**
 * @name    Interript & Event
 *          Interript and Event
 */
///@{
#define __I2C_IT_Enable(I2Cx__, I2C_ITSrc__)    ((I2Cx__)->INT.W |= (I2C_ITSrc__))
#define __I2C_IT_Disable(I2Cx__, I2C_ITSrc__)   ((I2Cx__)->INT.W &= (~(I2C_ITSrc__)))
void I2C_IT_Config(I2C_Struct* I2Cx, uint32_t I2C_ITSrc, FunctionalState State);
#define  I2C_IT_Cmd     I2C_IT_Config

#define __I2C_ITEA_Enable(I2Cx__)               ((I2Cx__)->INT.B[0] |= I2C_CR0_EN_enable_b0)
#define __I2C_ITEA_Disable(I2Cx__)              ((I2Cx__)->INT.B[0] &= (~I2C_CR0_EN_enable_b0))
void I2C_ITEA_Cmd(I2C_Struct* I2Cx, FunctionalState State);

#define __I2C_GetITSource(I2Cx__)               ((I2Cx__)->INT.W)
uint32_t I2C_GetITSource(I2C_Struct* I2Cx);

#define __I2C_GetAllFlagStatus(I2Cx__)          ((I2Cx__)->STA.W)
uint32_t I2C_GetAllFlagStatus(I2C_Struct* I2Cx);

#define __I2C_GetFlagStatus(I2Cx__, I2C_FLAG__) ((((I2Cx__)->STA.W & (I2C_FLAG__)) == (I2C_FLAG__))? SET : CLR)
DRV_Return I2C_GetFlagStatus(I2C_Struct* I2Cx, uint32_t I2C_FLAG);

#define __I2C_ClearFlag(I2Cx__, I2C_FLAG__)     ((I2Cx__)->STA.W = (I2C_FLAG__))
void I2C_ClearFlag(I2C_Struct* I2Cx, uint32_t I2C_FLAG);



#define __I2C_GetEventCode(I2Cx__)              ((I2Cx__)->STA2.B[0] & 0xF8)
#define __I2C_GetStatusCode(I2Cx__)             ((I2Cx__)->STA2.B[0] & 0xF8)
uint8_t I2C_GetEventCode(I2C_Struct* I2Cx);
#define I2C_GetStatusCode                       I2C_GetEventCode

#define __I2C_GetEventFlag(I2Cx__)              ((I2Cx__)->STA2.B[1] & I2C_STA2_EVENTF2_mask_b1)
#define __I2C_GetStateFlag(I2Cx__)              ((I2Cx__)->STA2.B[1] & I2C_STA2_EVENTF2_mask_b1)
DRV_Return I2C_GetEventFlag(I2C_Struct* I2Cx);

#define __I2C_ClearEventFlag(I2Cx__)            ((I2Cx__)->STA2.B[1] = I2C_STA2_EVENTF2_mask_b1)
#define __I2C_ClearStateFlag(I2Cx__)            ((I2Cx__)->STA2.B[1] = I2C_STA2_EVENTF2_mask_b1)
void I2C_ClearEventFlag(I2C_Struct* I2Cx);

#define __I2C_WaitEventFlag(I2Cx__)             while(((I2Cx__)->STA2.B[1] & I2C_STA2_EVENTF2_mask_b1) == 0)

///@}



/**
 * @name    Data transmission
 *          Data transmission
 */
///@{

#define __I2C_GetSlaveMatchAddress(I2Cx__)      ((I2Cx__)->SAC.B[0])
uint8_t I2C_GetSlaveMatchAddress(I2C_Struct* I2Cx);

//#define __I2C_WriteTxData(I2C__, TxData__, TxDataLenth__)   ((I2Cx__)->CR2.B[1] = (TxDataLenth__)); ((I2Cx__)->DAT.W = (TxData__))
//#define __I2C_SendData(I2Cx__, TxData__, TxDataLenth__)     ((I2Cx__)->CR2.B[1] = (TxDataLenth__)); ((I2Cx__)->DAT.W = (TxData__))
#define __I2C_WriteTxSBUF(I2Cx__, TxData__)     ((I2Cx__)->SBUF.B[0] = (TxData__))
#define __I2C_SendSBUF(I2Cx__, TxData__)        ((I2Cx__)->SBUF.B[0] = (TxData__))
void I2C_SendSBUF(I2C_Struct* I2Cx, uint8_t TxData);
#define I2C_SendTxData                          I2C_SendSBUF

//#define __I2C_ReadRxData(I2C__)                 ((I2Cx__)->DAT.W)
//#define __I2C_ReceiveData(I2Cx__)               ((I2Cx__)->DAT.W)
#define __I2C_ReadRxSBUF(I2Cx__)                ((I2Cx__)->SBUF.B[0])
#define __I2C_ReceiveSBUF(I2Cx__)               ((I2Cx__)->SBUF.B[0])
uint8_t I2C_ReceiveSBUF(I2C_Struct* I2Cx);
#define I2C_ReceiveRxData                       I2C_ReceiveSBUF

///@}



/**
 * @name    TimeOut
 *          TimeOut
 */
///@{

#define __I2C_SetTimeOutClockSource(I2Cx__, I2C_TMO_CKS__)      ((I2Cx__)->CLK.W = ((((I2Cx__)->CLK.W) & (~I2C_TMO_CKS_MASK)) | (I2C_TMO_CKS__)))

#define __I2C_SetTimeOutCount(I2Cx__, I2C_TMO_CNT__)            ((I2Cx__)->TMOUT.B[1] = (I2C_TMO_CNT__))

#define __I2C_SetTimeOutDetectionMode(I2Cx__, I2C_TMO_MDS__)    ((I2Cx__)->TMOUT.W = ((((I2Cx__)->TMOUT.W) & (~I2C_TMO_MDS_MASK)) | (I2C_TMO_MDS__)))

#define __I2C_TMO_Enable(I2Cx__)                                ((I2Cx__)->TMOUT.W |= I2C_TMOUT_TMO_EN_mask_w)
#define __I2C_TMO_Disable(I2Cx__)                               ((I2Cx__)->TMOUT.W &= (~I2C_TMOUT_TMO_EN_mask_w))

///@}



#ifdef __cplusplus
}
#endif

#endif


