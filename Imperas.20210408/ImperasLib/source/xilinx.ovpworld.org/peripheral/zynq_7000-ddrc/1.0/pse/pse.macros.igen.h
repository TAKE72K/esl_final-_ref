/*
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                             Version 20210408.0
//
////////////////////////////////////////////////////////////////////////////////

#ifndef PSE_MACROS_IGEN_H
#define PSE_MACROS_IGEN_H               

// Before including this file in the application, define the indicated macros
// to fix the base address of each slave port.

// Set the macro 'BPORT1' to the base of port 'bport1'
#ifndef BPORT1
#error BPORT1 is undefined. It needs to be set to the port base address
#endif


#define BPORT1_AB_POFFSET               0x0
#define BPORT1_AB_DDRC_CTRL_POFFSET     0x0
#define BPORT1_AB_DDRC_CTRL             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DDRC_CTRL_POFFSET)

#define BPORT1_AB_TWO_RANK_CFG_POFFSET  0x4
#define BPORT1_AB_TWO_RANK_CFG          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TWO_RANK_CFG_POFFSET)

#define BPORT1_AB_HPR_REG_POFFSET       0x8
#define BPORT1_AB_HPR_REG               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HPR_REG_POFFSET)

#define BPORT1_AB_LPR_REG_POFFSET       0xc
#define BPORT1_AB_LPR_REG               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LPR_REG_POFFSET)

#define BPORT1_AB_WR_REG_POFFSET        0x10
#define BPORT1_AB_WR_REG                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WR_REG_POFFSET)

#define BPORT1_AB_DRAM_PARAM_REG0_POFFSET  0x14
#define BPORT1_AB_DRAM_PARAM_REG0       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DRAM_PARAM_REG0_POFFSET)

#define BPORT1_AB_DRAM_PARAM_REG1_POFFSET  0x18
#define BPORT1_AB_DRAM_PARAM_REG1       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DRAM_PARAM_REG1_POFFSET)

#define BPORT1_AB_DRAM_PARAM_REG2_POFFSET  0x1c
#define BPORT1_AB_DRAM_PARAM_REG2       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DRAM_PARAM_REG2_POFFSET)

#define BPORT1_AB_DRAM_PARAM_REG3_POFFSET  0x20
#define BPORT1_AB_DRAM_PARAM_REG3       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DRAM_PARAM_REG3_POFFSET)

#define BPORT1_AB_DRAM_PARAM_REG4_POFFSET  0x24
#define BPORT1_AB_DRAM_PARAM_REG4       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DRAM_PARAM_REG4_POFFSET)

#define BPORT1_AB_DRAM_INIT_PARAM_POFFSET  0x28
#define BPORT1_AB_DRAM_INIT_PARAM       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DRAM_INIT_PARAM_POFFSET)

#define BPORT1_AB_DRAM_EMR_REG_POFFSET  0x2c
#define BPORT1_AB_DRAM_EMR_REG          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DRAM_EMR_REG_POFFSET)

#define BPORT1_AB_DRAM_EMR_MR_REG_POFFSET  0x30
#define BPORT1_AB_DRAM_EMR_MR_REG       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DRAM_EMR_MR_REG_POFFSET)

#define BPORT1_AB_DRAM_BURST8_RDWR_POFFSET  0x34
#define BPORT1_AB_DRAM_BURST8_RDWR      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DRAM_BURST8_RDWR_POFFSET)

#define BPORT1_AB_DRAM_DISABLE_DQ_POFFSET  0x38
#define BPORT1_AB_DRAM_DISABLE_DQ       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DRAM_DISABLE_DQ_POFFSET)

#define BPORT1_AB_DRAM_ADDR_MAP_BANK_POFFSET  0x3c
#define BPORT1_AB_DRAM_ADDR_MAP_BANK    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DRAM_ADDR_MAP_BANK_POFFSET)

#define BPORT1_AB_DRAM_ADDR_MAP_COL_POFFSET  0x40
#define BPORT1_AB_DRAM_ADDR_MAP_COL     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DRAM_ADDR_MAP_COL_POFFSET)

#define BPORT1_AB_DRAM_ADDR_MAP_ROW_POFFSET  0x44
#define BPORT1_AB_DRAM_ADDR_MAP_ROW     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DRAM_ADDR_MAP_ROW_POFFSET)

#define BPORT1_AB_DRAM_ODT_REG_POFFSET  0x48
#define BPORT1_AB_DRAM_ODT_REG          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DRAM_ODT_REG_POFFSET)

#define BPORT1_AB_PHY_DBG_REG_POFFSET   0x4c
#define BPORT1_AB_PHY_DBG_REG           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_DBG_REG_POFFSET)

#define BPORT1_AB_PHY_CMD_TIMEOUT_RDDATA_CPT_POFFSET  0x50
#define BPORT1_AB_PHY_CMD_TIMEOUT_RDDATA_CPT  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_CMD_TIMEOUT_RDDATA_CPT_POFFSET)

#define BPORT1_AB_MODE_STS_REG_POFFSET  0x54
#define BPORT1_AB_MODE_STS_REG          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MODE_STS_REG_POFFSET)

#define BPORT1_AB_DLL_CALIB_POFFSET     0x58
#define BPORT1_AB_DLL_CALIB             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DLL_CALIB_POFFSET)

#define BPORT1_AB_ODT_DELAY_HOLD_POFFSET  0x5c
#define BPORT1_AB_ODT_DELAY_HOLD        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ODT_DELAY_HOLD_POFFSET)

#define BPORT1_AB_CTRL_REG1_POFFSET     0x60
#define BPORT1_AB_CTRL_REG1             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CTRL_REG1_POFFSET)

#define BPORT1_AB_CTRL_REG2_POFFSET     0x64
#define BPORT1_AB_CTRL_REG2             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CTRL_REG2_POFFSET)

#define BPORT1_AB_CTRL_REG3_POFFSET     0x68
#define BPORT1_AB_CTRL_REG3             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CTRL_REG3_POFFSET)

#define BPORT1_AB_CTRL_REG4_POFFSET     0x6c
#define BPORT1_AB_CTRL_REG4             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CTRL_REG4_POFFSET)

#define BPORT1_AB_CTRL_REG5_POFFSET     0x78
#define BPORT1_AB_CTRL_REG5             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CTRL_REG5_POFFSET)

#define BPORT1_AB_CTRL_REG6_POFFSET     0x7c
#define BPORT1_AB_CTRL_REG6             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CTRL_REG6_POFFSET)

#define BPORT1_AB_CHE_REFRESH_TIMER01_POFFSET  0xa0
#define BPORT1_AB_CHE_REFRESH_TIMER01   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CHE_REFRESH_TIMER01_POFFSET)

#define BPORT1_AB_CHE_T_ZQ_POFFSET      0xa4
#define BPORT1_AB_CHE_T_ZQ              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CHE_T_ZQ_POFFSET)

#define BPORT1_AB_CHE_T_ZQ_SHORT_INTERVAL_REG_POFFSET  0xa8
#define BPORT1_AB_CHE_T_ZQ_SHORT_INTERVAL_REG  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CHE_T_ZQ_SHORT_INTERVAL_REG_POFFSET)

#define BPORT1_AB_DEEP_PWRDWN_REG_POFFSET  0xac
#define BPORT1_AB_DEEP_PWRDWN_REG       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DEEP_PWRDWN_REG_POFFSET)

#define BPORT1_AB_REG_2C_POFFSET        0xb0
#define BPORT1_AB_REG_2C                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG_2C_POFFSET)

#define BPORT1_AB_REG_2D_POFFSET        0xb4
#define BPORT1_AB_REG_2D                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG_2D_POFFSET)

#define BPORT1_AB_DFI_TIMING_POFFSET    0xb8
#define BPORT1_AB_DFI_TIMING            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DFI_TIMING_POFFSET)

#define BPORT1_AB_CHE_ECC_CONTROL_REG_OFFSET_POFFSET  0xc4
#define BPORT1_AB_CHE_ECC_CONTROL_REG_OFFSET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CHE_ECC_CONTROL_REG_OFFSET_POFFSET)

#define BPORT1_AB_CHE_CORR_ECC_LOG_REG_OFFSET_POFFSET  0xc8
#define BPORT1_AB_CHE_CORR_ECC_LOG_REG_OFFSET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CHE_CORR_ECC_LOG_REG_OFFSET_POFFSET)

#define BPORT1_AB_CHE_CORR_ECC_ADDR_REG_OFFSET_POFFSET  0xcc
#define BPORT1_AB_CHE_CORR_ECC_ADDR_REG_OFFSET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CHE_CORR_ECC_ADDR_REG_OFFSET_POFFSET)

#define BPORT1_AB_CHE_CORR_ECC_DATA_31_0_REG_OFFSET_POFFSET  0xd0
#define BPORT1_AB_CHE_CORR_ECC_DATA_31_0_REG_OFFSET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CHE_CORR_ECC_DATA_31_0_REG_OFFSET_POFFSET)

#define BPORT1_AB_CHE_CORR_ECC_DATA_63_32_REG_OFFSET_POFFSET  0xd4
#define BPORT1_AB_CHE_CORR_ECC_DATA_63_32_REG_OFFSET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CHE_CORR_ECC_DATA_63_32_REG_OFFSET_POFFSET)

#define BPORT1_AB_CHE_CORR_ECC_DATA_71_64_REG_OFFSET_POFFSET  0xd8
#define BPORT1_AB_CHE_CORR_ECC_DATA_71_64_REG_OFFSET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CHE_CORR_ECC_DATA_71_64_REG_OFFSET_POFFSET)

#define BPORT1_AB_CHE_UNCORR_ECC_LOG_REG_OFFSET_POFFSET  0xdc
#define BPORT1_AB_CHE_UNCORR_ECC_LOG_REG_OFFSET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CHE_UNCORR_ECC_LOG_REG_OFFSET_POFFSET)

#define BPORT1_AB_CHE_UNCORR_ECC_ADDR_REG_OFFSET_POFFSET  0xe0
#define BPORT1_AB_CHE_UNCORR_ECC_ADDR_REG_OFFSET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CHE_UNCORR_ECC_ADDR_REG_OFFSET_POFFSET)

#define BPORT1_AB_CHE_UNCORR_ECC_DATA_31_0_REG_OFFSET_POFFSET  0xe4
#define BPORT1_AB_CHE_UNCORR_ECC_DATA_31_0_REG_OFFSET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CHE_UNCORR_ECC_DATA_31_0_REG_OFFSET_POFFSET)

#define BPORT1_AB_CHE_UNCORR_ECC_DATA_63_32_REG_OFFSET_POFFSET  0xe8
#define BPORT1_AB_CHE_UNCORR_ECC_DATA_63_32_REG_OFFSET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CHE_UNCORR_ECC_DATA_63_32_REG_OFFSET_POFFSET)

#define BPORT1_AB_CHE_UNCORR_ECC_DATA_71_64_REG_OFFSET_POFFSET  0xec
#define BPORT1_AB_CHE_UNCORR_ECC_DATA_71_64_REG_OFFSET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CHE_UNCORR_ECC_DATA_71_64_REG_OFFSET_POFFSET)

#define BPORT1_AB_CHE_ECC_STATS_REG_OFFSET_POFFSET  0xf0
#define BPORT1_AB_CHE_ECC_STATS_REG_OFFSET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CHE_ECC_STATS_REG_OFFSET_POFFSET)

#define BPORT1_AB_ECC_SCRUB_POFFSET     0xf4
#define BPORT1_AB_ECC_SCRUB             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ECC_SCRUB_POFFSET)

#define BPORT1_AB_CHE_ECC_CORR_BIT_MASK_31_0_REG_OFFSET_POFFSET  0xf8
#define BPORT1_AB_CHE_ECC_CORR_BIT_MASK_31_0_REG_OFFSET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CHE_ECC_CORR_BIT_MASK_31_0_REG_OFFSET_POFFSET)

#define BPORT1_AB_CHE_ECC_CORR_BIT_MASK_63_32_REG_OFFSET_POFFSET  0xfc
#define BPORT1_AB_CHE_ECC_CORR_BIT_MASK_63_32_REG_OFFSET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CHE_ECC_CORR_BIT_MASK_63_32_REG_OFFSET_POFFSET)

#define BPORT1_AB_PHY_RCVR_ENABLE_POFFSET  0x114
#define BPORT1_AB_PHY_RCVR_ENABLE       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_RCVR_ENABLE_POFFSET)

#define BPORT1_AB_PHY_CONFIG0_POFFSET   0x118
#define BPORT1_AB_PHY_CONFIG0           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_CONFIG0_POFFSET)

#define BPORT1_AB_PHY_CONFIG1_POFFSET   0x11c
#define BPORT1_AB_PHY_CONFIG1           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_CONFIG1_POFFSET)

#define BPORT1_AB_PHY_CONFIG2_POFFSET   0x120
#define BPORT1_AB_PHY_CONFIG2           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_CONFIG2_POFFSET)

#define BPORT1_AB_PHY_CONFIG3_POFFSET   0x124
#define BPORT1_AB_PHY_CONFIG3           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_CONFIG3_POFFSET)

#define BPORT1_AB_PHY_INIT_RATIO0_POFFSET  0x12c
#define BPORT1_AB_PHY_INIT_RATIO0       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_INIT_RATIO0_POFFSET)

#define BPORT1_AB_PHY_INIT_RATIO1_POFFSET  0x130
#define BPORT1_AB_PHY_INIT_RATIO1       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_INIT_RATIO1_POFFSET)

#define BPORT1_AB_PHY_INIT_RATIO2_POFFSET  0x134
#define BPORT1_AB_PHY_INIT_RATIO2       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_INIT_RATIO2_POFFSET)

#define BPORT1_AB_PHY_INIT_RATIO3_POFFSET  0x138
#define BPORT1_AB_PHY_INIT_RATIO3       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_INIT_RATIO3_POFFSET)

#define BPORT1_AB_PHY_RD_DQS_CFG0_POFFSET  0x140
#define BPORT1_AB_PHY_RD_DQS_CFG0       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_RD_DQS_CFG0_POFFSET)

#define BPORT1_AB_PHY_RD_DQS_CFG1_POFFSET  0x144
#define BPORT1_AB_PHY_RD_DQS_CFG1       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_RD_DQS_CFG1_POFFSET)

#define BPORT1_AB_PHY_RD_DQS_CFG2_POFFSET  0x148
#define BPORT1_AB_PHY_RD_DQS_CFG2       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_RD_DQS_CFG2_POFFSET)

#define BPORT1_AB_PHY_RD_DQS_CFG3_POFFSET  0x14c
#define BPORT1_AB_PHY_RD_DQS_CFG3       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_RD_DQS_CFG3_POFFSET)

#define BPORT1_AB_PHY_WR_DQS_CFG0_POFFSET  0x154
#define BPORT1_AB_PHY_WR_DQS_CFG0       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_WR_DQS_CFG0_POFFSET)

#define BPORT1_AB_PHY_WR_DQS_CFG1_POFFSET  0x158
#define BPORT1_AB_PHY_WR_DQS_CFG1       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_WR_DQS_CFG1_POFFSET)

#define BPORT1_AB_PHY_WR_DQS_CFG2_POFFSET  0x15c
#define BPORT1_AB_PHY_WR_DQS_CFG2       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_WR_DQS_CFG2_POFFSET)

#define BPORT1_AB_PHY_WR_DQS_CFG3_POFFSET  0x160
#define BPORT1_AB_PHY_WR_DQS_CFG3       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_WR_DQS_CFG3_POFFSET)

#define BPORT1_AB_PHY_WE_CFG0_POFFSET   0x168
#define BPORT1_AB_PHY_WE_CFG0           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_WE_CFG0_POFFSET)

#define BPORT1_AB_PHY_WE_CFG1_POFFSET   0x16c
#define BPORT1_AB_PHY_WE_CFG1           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_WE_CFG1_POFFSET)

#define BPORT1_AB_PHY_WE_CFG2_POFFSET   0x170
#define BPORT1_AB_PHY_WE_CFG2           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_WE_CFG2_POFFSET)

#define BPORT1_AB_PHY_WE_CFG3_POFFSET   0x174
#define BPORT1_AB_PHY_WE_CFG3           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_WE_CFG3_POFFSET)

#define BPORT1_AB_WR_DATA_SLV0_POFFSET  0x17c
#define BPORT1_AB_WR_DATA_SLV0          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WR_DATA_SLV0_POFFSET)

#define BPORT1_AB_WR_DATA_SLV1_POFFSET  0x180
#define BPORT1_AB_WR_DATA_SLV1          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WR_DATA_SLV1_POFFSET)

#define BPORT1_AB_WR_DATA_SLV2_POFFSET  0x184
#define BPORT1_AB_WR_DATA_SLV2          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WR_DATA_SLV2_POFFSET)

#define BPORT1_AB_WR_DATA_SLV3_POFFSET  0x188
#define BPORT1_AB_WR_DATA_SLV3          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WR_DATA_SLV3_POFFSET)

#define BPORT1_AB_REG_64_POFFSET        0x190
#define BPORT1_AB_REG_64                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG_64_POFFSET)

#define BPORT1_AB_REG_65_POFFSET        0x194
#define BPORT1_AB_REG_65                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG_65_POFFSET)

#define BPORT1_AB_REG69_6A0_POFFSET     0x1a4
#define BPORT1_AB_REG69_6A0             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG69_6A0_POFFSET)

#define BPORT1_AB_REG69_6A1_POFFSET     0x1a8
#define BPORT1_AB_REG69_6A1             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG69_6A1_POFFSET)

#define BPORT1_AB_REG6C_6D2_POFFSET     0x1b0
#define BPORT1_AB_REG6C_6D2             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG6C_6D2_POFFSET)

#define BPORT1_AB_REG6C_6D3_POFFSET     0x1b4
#define BPORT1_AB_REG6C_6D3             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG6C_6D3_POFFSET)

#define BPORT1_AB_REG6E_710_POFFSET     0x1b8
#define BPORT1_AB_REG6E_710             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG6E_710_POFFSET)

#define BPORT1_AB_REG6E_711_POFFSET     0x1bc
#define BPORT1_AB_REG6E_711             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG6E_711_POFFSET)

#define BPORT1_AB_REG6E_712_POFFSET     0x1c0
#define BPORT1_AB_REG6E_712             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG6E_712_POFFSET)

#define BPORT1_AB_REG6E_713_POFFSET     0x1c4
#define BPORT1_AB_REG6E_713             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG6E_713_POFFSET)

#define BPORT1_AB_PHY_DLL_STS0_POFFSET  0x1cc
#define BPORT1_AB_PHY_DLL_STS0          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_DLL_STS0_POFFSET)

#define BPORT1_AB_PHY_DLL_STS1_POFFSET  0x1d0
#define BPORT1_AB_PHY_DLL_STS1          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_DLL_STS1_POFFSET)

#define BPORT1_AB_PHY_DLL_STS2_POFFSET  0x1d4
#define BPORT1_AB_PHY_DLL_STS2          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_DLL_STS2_POFFSET)

#define BPORT1_AB_PHY_DLL_STS3_POFFSET  0x1d8
#define BPORT1_AB_PHY_DLL_STS3          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_DLL_STS3_POFFSET)

#define BPORT1_AB_DLL_LOCK_STS_POFFSET  0x1e0
#define BPORT1_AB_DLL_LOCK_STS          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DLL_LOCK_STS_POFFSET)

#define BPORT1_AB_PHY_CTRL_STS_POFFSET  0x1e4
#define BPORT1_AB_PHY_CTRL_STS          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_CTRL_STS_POFFSET)

#define BPORT1_AB_PHY_CTRL_STS_REG2_POFFSET  0x1e8
#define BPORT1_AB_PHY_CTRL_STS_REG2     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_CTRL_STS_REG2_POFFSET)

#define BPORT1_AB_AXI_ID_POFFSET        0x200
#define BPORT1_AB_AXI_ID                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AXI_ID_POFFSET)

#define BPORT1_AB_AXI_PRIORITY_WR_PORT0_POFFSET  0x208
#define BPORT1_AB_AXI_PRIORITY_WR_PORT0  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AXI_PRIORITY_WR_PORT0_POFFSET)

#define BPORT1_AB_AXI_PRIORITY_WR_PORT1_POFFSET  0x20c
#define BPORT1_AB_AXI_PRIORITY_WR_PORT1  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AXI_PRIORITY_WR_PORT1_POFFSET)

#define BPORT1_AB_AXI_PRIORITY_WR_PORT2_POFFSET  0x210
#define BPORT1_AB_AXI_PRIORITY_WR_PORT2  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AXI_PRIORITY_WR_PORT2_POFFSET)

#define BPORT1_AB_AXI_PRIORITY_WR_PORT3_POFFSET  0x214
#define BPORT1_AB_AXI_PRIORITY_WR_PORT3  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AXI_PRIORITY_WR_PORT3_POFFSET)

#define BPORT1_AB_AXI_PRIORITY_RD_PORT0_POFFSET  0x218
#define BPORT1_AB_AXI_PRIORITY_RD_PORT0  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AXI_PRIORITY_RD_PORT0_POFFSET)

#define BPORT1_AB_AXI_PRIORITY_RD_PORT1_POFFSET  0x21c
#define BPORT1_AB_AXI_PRIORITY_RD_PORT1  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AXI_PRIORITY_RD_PORT1_POFFSET)

#define BPORT1_AB_AXI_PRIORITY_RD_PORT2_POFFSET  0x220
#define BPORT1_AB_AXI_PRIORITY_RD_PORT2  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AXI_PRIORITY_RD_PORT2_POFFSET)

#define BPORT1_AB_AXI_PRIORITY_RD_PORT3_POFFSET  0x224
#define BPORT1_AB_AXI_PRIORITY_RD_PORT3  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AXI_PRIORITY_RD_PORT3_POFFSET)

#define BPORT1_AB_EXCL_ACCESS_CFG0_POFFSET  0x294
#define BPORT1_AB_EXCL_ACCESS_CFG0      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EXCL_ACCESS_CFG0_POFFSET)

#define BPORT1_AB_EXCL_ACCESS_CFG1_POFFSET  0x298
#define BPORT1_AB_EXCL_ACCESS_CFG1      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EXCL_ACCESS_CFG1_POFFSET)

#define BPORT1_AB_EXCL_ACCESS_CFG2_POFFSET  0x29c
#define BPORT1_AB_EXCL_ACCESS_CFG2      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EXCL_ACCESS_CFG2_POFFSET)

#define BPORT1_AB_EXCL_ACCESS_CFG3_POFFSET  0x2a0
#define BPORT1_AB_EXCL_ACCESS_CFG3      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EXCL_ACCESS_CFG3_POFFSET)

#define BPORT1_AB_MODE_REG_READ_POFFSET  0x2a4
#define BPORT1_AB_MODE_REG_READ         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MODE_REG_READ_POFFSET)

#define BPORT1_AB_LPDDR_CTRL0_POFFSET   0x2a8
#define BPORT1_AB_LPDDR_CTRL0           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LPDDR_CTRL0_POFFSET)

#define BPORT1_AB_LPDDR_CTRL1_POFFSET   0x2ac
#define BPORT1_AB_LPDDR_CTRL1           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LPDDR_CTRL1_POFFSET)

#define BPORT1_AB_LPDDR_CTRL2_POFFSET   0x2b0
#define BPORT1_AB_LPDDR_CTRL2           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LPDDR_CTRL2_POFFSET)

#define BPORT1_AB_LPDDR_CTRL3_POFFSET   0x2b4
#define BPORT1_AB_LPDDR_CTRL3           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LPDDR_CTRL3_POFFSET)

#define BPORT1_AB_BUFFER_POFFSET        0x0
#define BPORT1_AB_BUFFER                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BUFFER_POFFSET)
#define BPORT1_AB_BUFFER_BYTES          0x1000


#endif
