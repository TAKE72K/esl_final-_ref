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
#define BPORT1_AB_SCL_POFFSET           0x0
#define BPORT1_AB_SCL                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SCL_POFFSET)
#define BPORT1_AB_SCL_LOCK              0x1
#define BPORT1_AB_SCL_LOCK_GET(_v)      (_v & 0x1)

#define BPORT1_AB_SLCR_LOCK_POFFSET     0x4
#define BPORT1_AB_SLCR_LOCK             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SLCR_LOCK_POFFSET)

#define BPORT1_AB_SLCR_UNLOCK_POFFSET   0x8
#define BPORT1_AB_SLCR_UNLOCK           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SLCR_UNLOCK_POFFSET)

#define BPORT1_AB_SLCR_LOCKSTA_POFFSET  0xc
#define BPORT1_AB_SLCR_LOCKSTA          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SLCR_LOCKSTA_POFFSET)

#define BPORT1_AB_ARM_PLL_CTRL_POFFSET  0x100
#define BPORT1_AB_ARM_PLL_CTRL          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ARM_PLL_CTRL_POFFSET)
#define BPORT1_AB_ARM_PLL_CTRL_PLL_FDIV  (0x7f << 12)
#define BPORT1_AB_ARM_PLL_CTRL_PLL_FDIV_GET(_v)  ((_v >> 12) & 0x7f)
#define BPORT1_AB_ARM_PLL_CTRL_PLL_BYPASS_FORCE  (0x1 << 4)
#define BPORT1_AB_ARM_PLL_CTRL_PLL_BYPASS_FORCE_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_ARM_PLL_CTRL_PLL_BYPASS_QUAL  (0x1 << 3)
#define BPORT1_AB_ARM_PLL_CTRL_PLL_BYPASS_QUAL_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_ARM_PLL_CTRL_PLL_PWRDWN  (0x1 << 1)
#define BPORT1_AB_ARM_PLL_CTRL_PLL_PWRDWN_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_ARM_PLL_CTRL_PLL_RESET  0x1
#define BPORT1_AB_ARM_PLL_CTRL_PLL_RESET_GET(_v)  (_v & 0x1)

#define BPORT1_AB_DDR_PLL_CTRL_POFFSET  0x104
#define BPORT1_AB_DDR_PLL_CTRL          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DDR_PLL_CTRL_POFFSET)

#define BPORT1_AB_IO_PLL_CTRL_POFFSET   0x108
#define BPORT1_AB_IO_PLL_CTRL           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IO_PLL_CTRL_POFFSET)

#define BPORT1_AB_PLL_STATUS_POFFSET    0x10c
#define BPORT1_AB_PLL_STATUS            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PLL_STATUS_POFFSET)

#define BPORT1_AB_ARM_PLL_CFG_POFFSET   0x110
#define BPORT1_AB_ARM_PLL_CFG           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ARM_PLL_CFG_POFFSET)
#define BPORT1_AB_ARM_PLL_CFG_LOC_CNT   (0x3ff << 12)
#define BPORT1_AB_ARM_PLL_CFG_LOC_CNT_GET(_v)  ((_v >> 12) & 0x3ff)
#define BPORT1_AB_ARM_PLL_CFG_PLL_CP    (0xf << 8)
#define BPORT1_AB_ARM_PLL_CFG_PLL_CP_GET(_v)  ((_v >> 8) & 0xf)
#define BPORT1_AB_ARM_PLL_CFG_PLL_RES   (0xf << 4)
#define BPORT1_AB_ARM_PLL_CFG_PLL_RES_GET(_v)  ((_v >> 4) & 0xf)

#define BPORT1_AB_DDR_PLL_CFG_POFFSET   0x114
#define BPORT1_AB_DDR_PLL_CFG           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DDR_PLL_CFG_POFFSET)

#define BPORT1_AB_IO_PLL_CFG_POFFSET    0x118
#define BPORT1_AB_IO_PLL_CFG            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IO_PLL_CFG_POFFSET)

#define BPORT1_AB_ARM_CLK_CTRL_POFFSET  0x120
#define BPORT1_AB_ARM_CLK_CTRL          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ARM_CLK_CTRL_POFFSET)
#define BPORT1_AB_ARM_CLK_CTRL_CPU_PERICLKACT  (0x1 << 28)
#define BPORT1_AB_ARM_CLK_CTRL_CPU_PERICLKACT_GET(_v)  ((_v >> 28) & 0x1)
#define BPORT1_AB_ARM_CLK_CTRL_CPU_1XCLKACT  (0x1 << 27)
#define BPORT1_AB_ARM_CLK_CTRL_CPU_1XCLKACT_GET(_v)  ((_v >> 27) & 0x1)
#define BPORT1_AB_ARM_CLK_CTRL_CPU_2XCLKACT  (0x1 << 26)
#define BPORT1_AB_ARM_CLK_CTRL_CPU_2XCLKACT_GET(_v)  ((_v >> 26) & 0x1)
#define BPORT1_AB_ARM_CLK_CTRL_CPU_6OR3XCLKACT  (0x1 << 25)
#define BPORT1_AB_ARM_CLK_CTRL_CPU_6OR3XCLKACT_GET(_v)  ((_v >> 25) & 0x1)
#define BPORT1_AB_ARM_CLK_CTRL_CPU_4OR4XCLKACT  (0x1 << 24)
#define BPORT1_AB_ARM_CLK_CTRL_CPU_4OR4XCLKACT_GET(_v)  ((_v >> 24) & 0x1)
#define BPORT1_AB_ARM_CLK_CTRL_DIVISOR  (0x3f << 8)
#define BPORT1_AB_ARM_CLK_CTRL_DIVISOR_GET(_v)  ((_v >> 8) & 0x3f)
#define BPORT1_AB_ARM_CLK_CTRL_SRCSEL   (0x3 << 4)
#define BPORT1_AB_ARM_CLK_CTRL_SRCSEL_GET(_v)  ((_v >> 4) & 0x3)

#define BPORT1_AB_DDR_CLK_CTRL_POFFSET  0x124
#define BPORT1_AB_DDR_CLK_CTRL          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DDR_CLK_CTRL_POFFSET)

#define BPORT1_AB_DCI_CLK_CTRL_POFFSET  0x128
#define BPORT1_AB_DCI_CLK_CTRL          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DCI_CLK_CTRL_POFFSET)

#define BPORT1_AB_APER_CLK_CTRL_POFFSET  0x12c
#define BPORT1_AB_APER_CLK_CTRL         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_APER_CLK_CTRL_POFFSET)

#define BPORT1_AB_USB0_CLK_CTRL_POFFSET  0x130
#define BPORT1_AB_USB0_CLK_CTRL         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB0_CLK_CTRL_POFFSET)

#define BPORT1_AB_USB1_CLK_CTRL_POFFSET  0x134
#define BPORT1_AB_USB1_CLK_CTRL         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB1_CLK_CTRL_POFFSET)

#define BPORT1_AB_GEM0_RCLK_CTRL_POFFSET  0x138
#define BPORT1_AB_GEM0_RCLK_CTRL        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GEM0_RCLK_CTRL_POFFSET)

#define BPORT1_AB_GEM1_RCLK_CTRL_POFFSET  0x13c
#define BPORT1_AB_GEM1_RCLK_CTRL        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GEM1_RCLK_CTRL_POFFSET)

#define BPORT1_AB_GEM0_CLK_CTRL_POFFSET  0x140
#define BPORT1_AB_GEM0_CLK_CTRL         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GEM0_CLK_CTRL_POFFSET)

#define BPORT1_AB_GEM1_CLK_CTRL_POFFSET  0x144
#define BPORT1_AB_GEM1_CLK_CTRL         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GEM1_CLK_CTRL_POFFSET)

#define BPORT1_AB_SMC_CLK_CTRL_POFFSET  0x148
#define BPORT1_AB_SMC_CLK_CTRL          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SMC_CLK_CTRL_POFFSET)

#define BPORT1_AB_LQSPI_CLK_CTRL_POFFSET  0x14c
#define BPORT1_AB_LQSPI_CLK_CTRL        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LQSPI_CLK_CTRL_POFFSET)

#define BPORT1_AB_SDIO_CLK_CTRL_POFFSET  0x150
#define BPORT1_AB_SDIO_CLK_CTRL         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SDIO_CLK_CTRL_POFFSET)

#define BPORT1_AB_UART_CLK_CTRL_POFFSET  0x154
#define BPORT1_AB_UART_CLK_CTRL         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UART_CLK_CTRL_POFFSET)

#define BPORT1_AB_SPI_CLK_CTRL_POFFSET  0x158
#define BPORT1_AB_SPI_CLK_CTRL          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SPI_CLK_CTRL_POFFSET)

#define BPORT1_AB_CAN_CLK_CTRL_POFFSET  0x15c
#define BPORT1_AB_CAN_CLK_CTRL          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CAN_CLK_CTRL_POFFSET)

#define BPORT1_AB_CAN_MIOCLK_CTRL_POFFSET  0x160
#define BPORT1_AB_CAN_MIOCLK_CTRL       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CAN_MIOCLK_CTRL_POFFSET)

#define BPORT1_AB_DBG_CLK_CTRL_POFFSET  0x164
#define BPORT1_AB_DBG_CLK_CTRL          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DBG_CLK_CTRL_POFFSET)

#define BPORT1_AB_PCAP_CLK_CTRL_POFFSET  0x168
#define BPORT1_AB_PCAP_CLK_CTRL         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PCAP_CLK_CTRL_POFFSET)

#define BPORT1_AB_TOPSW_CLK_CTRL_POFFSET  0x16c
#define BPORT1_AB_TOPSW_CLK_CTRL        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TOPSW_CLK_CTRL_POFFSET)

#define BPORT1_AB_FPGA0_CLK_CTRL_POFFSET  0x170
#define BPORT1_AB_FPGA0_CLK_CTRL        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FPGA0_CLK_CTRL_POFFSET)

#define BPORT1_AB_FPGA0_THR_CTRL_POFFSET  0x174
#define BPORT1_AB_FPGA0_THR_CTRL        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FPGA0_THR_CTRL_POFFSET)

#define BPORT1_AB_FPGA0_THR_CNT_POFFSET  0x178
#define BPORT1_AB_FPGA0_THR_CNT         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FPGA0_THR_CNT_POFFSET)

#define BPORT1_AB_FPGA0_THR_STA_POFFSET  0x17c
#define BPORT1_AB_FPGA0_THR_STA         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FPGA0_THR_STA_POFFSET)

#define BPORT1_AB_FPGA1_CLK_CTRL_POFFSET  0x180
#define BPORT1_AB_FPGA1_CLK_CTRL        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FPGA1_CLK_CTRL_POFFSET)

#define BPORT1_AB_FPGA1_THR_CTRL_POFFSET  0x184
#define BPORT1_AB_FPGA1_THR_CTRL        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FPGA1_THR_CTRL_POFFSET)

#define BPORT1_AB_FPGA1_THR_CNT_POFFSET  0x188
#define BPORT1_AB_FPGA1_THR_CNT         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FPGA1_THR_CNT_POFFSET)

#define BPORT1_AB_FPGA1_THR_STA_POFFSET  0x18c
#define BPORT1_AB_FPGA1_THR_STA         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FPGA1_THR_STA_POFFSET)

#define BPORT1_AB_FPGA2_CLK_CTRL_POFFSET  0x190
#define BPORT1_AB_FPGA2_CLK_CTRL        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FPGA2_CLK_CTRL_POFFSET)

#define BPORT1_AB_FPGA2_THR_CTRL_POFFSET  0x194
#define BPORT1_AB_FPGA2_THR_CTRL        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FPGA2_THR_CTRL_POFFSET)

#define BPORT1_AB_FPGA2_THR_CNT_POFFSET  0x198
#define BPORT1_AB_FPGA2_THR_CNT         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FPGA2_THR_CNT_POFFSET)

#define BPORT1_AB_FPGA2_THR_STA_POFFSET  0x19c
#define BPORT1_AB_FPGA2_THR_STA         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FPGA2_THR_STA_POFFSET)

#define BPORT1_AB_FPGA3_CLK_CTRL_POFFSET  0x1a0
#define BPORT1_AB_FPGA3_CLK_CTRL        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FPGA3_CLK_CTRL_POFFSET)

#define BPORT1_AB_FPGA3_THR_CTRL_POFFSET  0x1a4
#define BPORT1_AB_FPGA3_THR_CTRL        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FPGA3_THR_CTRL_POFFSET)

#define BPORT1_AB_FPGA3_THR_CNT_POFFSET  0x1a8
#define BPORT1_AB_FPGA3_THR_CNT         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FPGA3_THR_CNT_POFFSET)

#define BPORT1_AB_FPGA3_THR_STA_POFFSET  0x1ac
#define BPORT1_AB_FPGA3_THR_STA         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FPGA3_THR_STA_POFFSET)

#define BPORT1_AB_CLK_621_TRUE_POFFSET  0x1c4
#define BPORT1_AB_CLK_621_TRUE          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CLK_621_TRUE_POFFSET)
#define BPORT1_AB_CLK_621_TRUE_CLK_621  0x1
#define BPORT1_AB_CLK_621_TRUE_CLK_621_GET(_v)  (_v & 0x1)

#define BPORT1_AB_PSS_RST_CTRL_POFFSET  0x200
#define BPORT1_AB_PSS_RST_CTRL          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PSS_RST_CTRL_POFFSET)

#define BPORT1_AB_DDR_RST_CTRL_POFFSET  0x204
#define BPORT1_AB_DDR_RST_CTRL          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DDR_RST_CTRL_POFFSET)

#define BPORT1_AB_TOPSW_RST_CTRL_POFFSET  0x208
#define BPORT1_AB_TOPSW_RST_CTRL        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TOPSW_RST_CTRL_POFFSET)

#define BPORT1_AB_DMAC_RST_CTRL_POFFSET  0x20c
#define BPORT1_AB_DMAC_RST_CTRL         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DMAC_RST_CTRL_POFFSET)

#define BPORT1_AB_USB_RST_CTRL_POFFSET  0x210
#define BPORT1_AB_USB_RST_CTRL          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_RST_CTRL_POFFSET)

#define BPORT1_AB_GEM_RST_CTRL_POFFSET  0x214
#define BPORT1_AB_GEM_RST_CTRL          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GEM_RST_CTRL_POFFSET)

#define BPORT1_AB_SDIO_RST_CTRL_POFFSET  0x218
#define BPORT1_AB_SDIO_RST_CTRL         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SDIO_RST_CTRL_POFFSET)

#define BPORT1_AB_SPI_RST_CTRL_POFFSET  0x21c
#define BPORT1_AB_SPI_RST_CTRL          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SPI_RST_CTRL_POFFSET)

#define BPORT1_AB_CAN_RST_CTRL_POFFSET  0x220
#define BPORT1_AB_CAN_RST_CTRL          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CAN_RST_CTRL_POFFSET)

#define BPORT1_AB_I2C_RST_CTRL_POFFSET  0x224
#define BPORT1_AB_I2C_RST_CTRL          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_I2C_RST_CTRL_POFFSET)

#define BPORT1_AB_UART_RST_CTRL_POFFSET  0x228
#define BPORT1_AB_UART_RST_CTRL         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UART_RST_CTRL_POFFSET)

#define BPORT1_AB_GPIO_RST_CTRL_POFFSET  0x22c
#define BPORT1_AB_GPIO_RST_CTRL         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPIO_RST_CTRL_POFFSET)

#define BPORT1_AB_LQSPI_RST_CTRL_POFFSET  0x230
#define BPORT1_AB_LQSPI_RST_CTRL        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LQSPI_RST_CTRL_POFFSET)

#define BPORT1_AB_SMC_RST_CTRL_POFFSET  0x234
#define BPORT1_AB_SMC_RST_CTRL          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SMC_RST_CTRL_POFFSET)

#define BPORT1_AB_OCM_RST_CTRL_POFFSET  0x238
#define BPORT1_AB_OCM_RST_CTRL          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_OCM_RST_CTRL_POFFSET)

#define BPORT1_AB_FPGA_RST_CTRL_POFFSET  0x240
#define BPORT1_AB_FPGA_RST_CTRL         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FPGA_RST_CTRL_POFFSET)

#define BPORT1_AB_A9_CPU_RST_CTRL_POFFSET  0x244
#define BPORT1_AB_A9_CPU_RST_CTRL       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_A9_CPU_RST_CTRL_POFFSET)
#define BPORT1_AB_A9_CPU_RST_CTRL_PERI_RST  (0x1 << 8)
#define BPORT1_AB_A9_CPU_RST_CTRL_PERI_RST_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_A9_CPU_RST_CTRL_A9_CLKSTOP1  (0x1 << 5)
#define BPORT1_AB_A9_CPU_RST_CTRL_A9_CLKSTOP1_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_A9_CPU_RST_CTRL_A9_CLKSTOP0  (0x1 << 4)
#define BPORT1_AB_A9_CPU_RST_CTRL_A9_CLKSTOP0_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_A9_CPU_RST_CTRL_A9_RST1  (0x1 << 1)
#define BPORT1_AB_A9_CPU_RST_CTRL_A9_RST1_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_A9_CPU_RST_CTRL_A9_RST0  0x1
#define BPORT1_AB_A9_CPU_RST_CTRL_A9_RST0_GET(_v)  (_v & 0x1)

#define BPORT1_AB_RS_AWDT_CTRL_POFFSET  0x24c
#define BPORT1_AB_RS_AWDT_CTRL          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RS_AWDT_CTRL_POFFSET)

#define BPORT1_AB_REBOOT_STATUS_POFFSET  0x258
#define BPORT1_AB_REBOOT_STATUS         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REBOOT_STATUS_POFFSET)

#define BPORT1_AB_BOOT_MODE_POFFSET     0x25c
#define BPORT1_AB_BOOT_MODE             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BOOT_MODE_POFFSET)

#define BPORT1_AB_APU_CTRL_POFFSET      0x300
#define BPORT1_AB_APU_CTRL              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_APU_CTRL_POFFSET)

#define BPORT1_AB_WDT_CLK_SEL_POFFSET   0x304
#define BPORT1_AB_WDT_CLK_SEL           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WDT_CLK_SEL_POFFSET)

#define BPORT1_AB_TZ_OCM_RAM0_POFFSET   0x400
#define BPORT1_AB_TZ_OCM_RAM0           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TZ_OCM_RAM0_POFFSET)

#define BPORT1_AB_TZ_OCM_RAM1_POFFSET   0x404
#define BPORT1_AB_TZ_OCM_RAM1           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TZ_OCM_RAM1_POFFSET)

#define BPORT1_AB_TZ_OCM_POFFSET        0x408
#define BPORT1_AB_TZ_OCM                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TZ_OCM_POFFSET)

#define BPORT1_AB_TZ_DDR_RAM_POFFSET    0x430
#define BPORT1_AB_TZ_DDR_RAM            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TZ_DDR_RAM_POFFSET)

#define BPORT1_AB_TZ_DMA_NS_POFFSET     0x440
#define BPORT1_AB_TZ_DMA_NS             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TZ_DMA_NS_POFFSET)

#define BPORT1_AB_TZ_DMA_IRQ_NS_POFFSET  0x444
#define BPORT1_AB_TZ_DMA_IRQ_NS         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TZ_DMA_IRQ_NS_POFFSET)

#define BPORT1_AB_TZ_DMA_PERIPH_NS_POFFSET  0x448
#define BPORT1_AB_TZ_DMA_PERIPH_NS      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TZ_DMA_PERIPH_NS_POFFSET)

#define BPORT1_AB_TZ_GEM_POFFSET        0x450
#define BPORT1_AB_TZ_GEM                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TZ_GEM_POFFSET)

#define BPORT1_AB_TZ_SDIO_POFFSET       0x454
#define BPORT1_AB_TZ_SDIO               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TZ_SDIO_POFFSET)

#define BPORT1_AB_TZ_USB_POFFSET        0x458
#define BPORT1_AB_TZ_USB                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TZ_USB_POFFSET)

#define BPORT1_AB_TZ_FPGA_M_POFFSET     0x484
#define BPORT1_AB_TZ_FPGA_M             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TZ_FPGA_M_POFFSET)

#define BPORT1_AB_TZ_FPGA_AFI_POFFSET   0x488
#define BPORT1_AB_TZ_FPGA_AFI           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TZ_FPGA_AFI_POFFSET)

#define BPORT1_AB_PSS_IDCODE_POFFSET    0x530
#define BPORT1_AB_PSS_IDCODE            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PSS_IDCODE_POFFSET)
#define BPORT1_AB_PSS_IDCODE_REV        (0xf << 28)
#define BPORT1_AB_PSS_IDCODE_REV_GET(_v)  ((_v >> 28) & 0xf)
#define BPORT1_AB_PSS_IDCODE_FAM        (0x7f << 21)
#define BPORT1_AB_PSS_IDCODE_FAM_GET(_v)  ((_v >> 21) & 0x7f)
#define BPORT1_AB_PSS_IDCODE_SUB        (0xf << 17)
#define BPORT1_AB_PSS_IDCODE_SUB_GET(_v)  ((_v >> 17) & 0xf)
#define BPORT1_AB_PSS_IDCODE_DEV        (0x1f << 12)
#define BPORT1_AB_PSS_IDCODE_DEV_GET(_v)  ((_v >> 12) & 0x1f)
#define BPORT1_AB_PSS_IDCODE_MAN        (0x7ff << 1)
#define BPORT1_AB_PSS_IDCODE_MAN_GET(_v)  ((_v >> 1) & 0x7ff)

#define BPORT1_AB_DDR_URGENT_POFFSET    0x600
#define BPORT1_AB_DDR_URGENT            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DDR_URGENT_POFFSET)

#define BPORT1_AB_DDR_CAL_START_POFFSET  0x60c
#define BPORT1_AB_DDR_CAL_START         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DDR_CAL_START_POFFSET)

#define BPORT1_AB_DDR_REF_START_POFFSET  0x614
#define BPORT1_AB_DDR_REF_START         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DDR_REF_START_POFFSET)

#define BPORT1_AB_DDR_CMD_STA_POFFSET   0x618
#define BPORT1_AB_DDR_CMD_STA           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DDR_CMD_STA_POFFSET)

#define BPORT1_AB_DDR_URGENT_SEL_POFFSET  0x61c
#define BPORT1_AB_DDR_URGENT_SEL        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DDR_URGENT_SEL_POFFSET)

#define BPORT1_AB_DDR_DFI_STATUS_POFFSET  0x620
#define BPORT1_AB_DDR_DFI_STATUS        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DDR_DFI_STATUS_POFFSET)

#define BPORT1_AB_MIO_PIN_00_POFFSET    0x700
#define BPORT1_AB_MIO_PIN_00            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_00_POFFSET)

#define BPORT1_AB_MIO_PIN_01_POFFSET    0x704
#define BPORT1_AB_MIO_PIN_01            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_01_POFFSET)

#define BPORT1_AB_MIO_PIN_02_POFFSET    0x708
#define BPORT1_AB_MIO_PIN_02            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_02_POFFSET)

#define BPORT1_AB_MIO_PIN_03_POFFSET    0x70c
#define BPORT1_AB_MIO_PIN_03            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_03_POFFSET)

#define BPORT1_AB_MIO_PIN_04_POFFSET    0x710
#define BPORT1_AB_MIO_PIN_04            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_04_POFFSET)

#define BPORT1_AB_MIO_PIN_05_POFFSET    0x714
#define BPORT1_AB_MIO_PIN_05            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_05_POFFSET)

#define BPORT1_AB_MIO_PIN_06_POFFSET    0x718
#define BPORT1_AB_MIO_PIN_06            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_06_POFFSET)

#define BPORT1_AB_MIO_PIN_07_POFFSET    0x71c
#define BPORT1_AB_MIO_PIN_07            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_07_POFFSET)

#define BPORT1_AB_MIO_PIN_08_POFFSET    0x720
#define BPORT1_AB_MIO_PIN_08            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_08_POFFSET)

#define BPORT1_AB_MIO_PIN_09_POFFSET    0x724
#define BPORT1_AB_MIO_PIN_09            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_09_POFFSET)

#define BPORT1_AB_MIO_PIN_10_POFFSET    0x728
#define BPORT1_AB_MIO_PIN_10            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_10_POFFSET)

#define BPORT1_AB_MIO_PIN_11_POFFSET    0x72c
#define BPORT1_AB_MIO_PIN_11            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_11_POFFSET)

#define BPORT1_AB_MIO_PIN_12_POFFSET    0x730
#define BPORT1_AB_MIO_PIN_12            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_12_POFFSET)

#define BPORT1_AB_MIO_PIN_13_POFFSET    0x734
#define BPORT1_AB_MIO_PIN_13            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_13_POFFSET)

#define BPORT1_AB_MIO_PIN_14_POFFSET    0x738
#define BPORT1_AB_MIO_PIN_14            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_14_POFFSET)

#define BPORT1_AB_MIO_PIN_15_POFFSET    0x73c
#define BPORT1_AB_MIO_PIN_15            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_15_POFFSET)

#define BPORT1_AB_MIO_PIN_16_POFFSET    0x740
#define BPORT1_AB_MIO_PIN_16            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_16_POFFSET)

#define BPORT1_AB_MIO_PIN_17_POFFSET    0x744
#define BPORT1_AB_MIO_PIN_17            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_17_POFFSET)

#define BPORT1_AB_MIO_PIN_18_POFFSET    0x748
#define BPORT1_AB_MIO_PIN_18            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_18_POFFSET)

#define BPORT1_AB_MIO_PIN_19_POFFSET    0x74c
#define BPORT1_AB_MIO_PIN_19            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_19_POFFSET)

#define BPORT1_AB_MIO_PIN_20_POFFSET    0x750
#define BPORT1_AB_MIO_PIN_20            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_20_POFFSET)

#define BPORT1_AB_MIO_PIN_21_POFFSET    0x754
#define BPORT1_AB_MIO_PIN_21            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_21_POFFSET)

#define BPORT1_AB_MIO_PIN_22_POFFSET    0x758
#define BPORT1_AB_MIO_PIN_22            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_22_POFFSET)

#define BPORT1_AB_MIO_PIN_23_POFFSET    0x75c
#define BPORT1_AB_MIO_PIN_23            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_23_POFFSET)

#define BPORT1_AB_MIO_PIN_24_POFFSET    0x760
#define BPORT1_AB_MIO_PIN_24            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_24_POFFSET)

#define BPORT1_AB_MIO_PIN_25_POFFSET    0x764
#define BPORT1_AB_MIO_PIN_25            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_25_POFFSET)

#define BPORT1_AB_MIO_PIN_26_POFFSET    0x768
#define BPORT1_AB_MIO_PIN_26            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_26_POFFSET)

#define BPORT1_AB_MIO_PIN_27_POFFSET    0x76c
#define BPORT1_AB_MIO_PIN_27            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_27_POFFSET)

#define BPORT1_AB_MIO_PIN_28_POFFSET    0x770
#define BPORT1_AB_MIO_PIN_28            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_28_POFFSET)

#define BPORT1_AB_MIO_PIN_29_POFFSET    0x774
#define BPORT1_AB_MIO_PIN_29            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_29_POFFSET)

#define BPORT1_AB_MIO_PIN_30_POFFSET    0x778
#define BPORT1_AB_MIO_PIN_30            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_30_POFFSET)

#define BPORT1_AB_MIO_PIN_31_POFFSET    0x77c
#define BPORT1_AB_MIO_PIN_31            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_31_POFFSET)

#define BPORT1_AB_MIO_PIN_32_POFFSET    0x780
#define BPORT1_AB_MIO_PIN_32            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_32_POFFSET)

#define BPORT1_AB_MIO_PIN_33_POFFSET    0x784
#define BPORT1_AB_MIO_PIN_33            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_33_POFFSET)

#define BPORT1_AB_MIO_PIN_34_POFFSET    0x788
#define BPORT1_AB_MIO_PIN_34            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_34_POFFSET)

#define BPORT1_AB_MIO_PIN_35_POFFSET    0x78c
#define BPORT1_AB_MIO_PIN_35            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_35_POFFSET)

#define BPORT1_AB_MIO_PIN_36_POFFSET    0x790
#define BPORT1_AB_MIO_PIN_36            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_36_POFFSET)

#define BPORT1_AB_MIO_PIN_37_POFFSET    0x794
#define BPORT1_AB_MIO_PIN_37            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_37_POFFSET)

#define BPORT1_AB_MIO_PIN_38_POFFSET    0x798
#define BPORT1_AB_MIO_PIN_38            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_38_POFFSET)

#define BPORT1_AB_MIO_PIN_39_POFFSET    0x79c
#define BPORT1_AB_MIO_PIN_39            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_39_POFFSET)

#define BPORT1_AB_MIO_PIN_40_POFFSET    0x7a0
#define BPORT1_AB_MIO_PIN_40            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_40_POFFSET)

#define BPORT1_AB_MIO_PIN_41_POFFSET    0x7a4
#define BPORT1_AB_MIO_PIN_41            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_41_POFFSET)

#define BPORT1_AB_MIO_PIN_42_POFFSET    0x7a8
#define BPORT1_AB_MIO_PIN_42            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_42_POFFSET)

#define BPORT1_AB_MIO_PIN_43_POFFSET    0x7ac
#define BPORT1_AB_MIO_PIN_43            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_43_POFFSET)

#define BPORT1_AB_MIO_PIN_44_POFFSET    0x7b0
#define BPORT1_AB_MIO_PIN_44            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_44_POFFSET)

#define BPORT1_AB_MIO_PIN_45_POFFSET    0x7b4
#define BPORT1_AB_MIO_PIN_45            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_45_POFFSET)

#define BPORT1_AB_MIO_PIN_46_POFFSET    0x7b8
#define BPORT1_AB_MIO_PIN_46            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_46_POFFSET)

#define BPORT1_AB_MIO_PIN_47_POFFSET    0x7bc
#define BPORT1_AB_MIO_PIN_47            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_47_POFFSET)

#define BPORT1_AB_MIO_PIN_48_POFFSET    0x7c0
#define BPORT1_AB_MIO_PIN_48            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_48_POFFSET)

#define BPORT1_AB_MIO_PIN_49_POFFSET    0x7c4
#define BPORT1_AB_MIO_PIN_49            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_49_POFFSET)

#define BPORT1_AB_MIO_PIN_50_POFFSET    0x7c8
#define BPORT1_AB_MIO_PIN_50            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_50_POFFSET)

#define BPORT1_AB_MIO_PIN_51_POFFSET    0x7cc
#define BPORT1_AB_MIO_PIN_51            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_51_POFFSET)

#define BPORT1_AB_MIO_PIN_52_POFFSET    0x7d0
#define BPORT1_AB_MIO_PIN_52            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_52_POFFSET)

#define BPORT1_AB_MIO_PIN_53_POFFSET    0x7d4
#define BPORT1_AB_MIO_PIN_53            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_PIN_53_POFFSET)

#define BPORT1_AB_MIO_LOOPBACK_POFFSET  0x804
#define BPORT1_AB_MIO_LOOPBACK          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_LOOPBACK_POFFSET)

#define BPORT1_AB_MIO_MST_TRI0_POFFSET  0x80c
#define BPORT1_AB_MIO_MST_TRI0          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_MST_TRI0_POFFSET)

#define BPORT1_AB_MIO_MST_TRI1_POFFSET  0x810
#define BPORT1_AB_MIO_MST_TRI1          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIO_MST_TRI1_POFFSET)

#define BPORT1_AB_SD0_WP_CD_SEL_POFFSET  0x830
#define BPORT1_AB_SD0_WP_CD_SEL         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SD0_WP_CD_SEL_POFFSET)

#define BPORT1_AB_SD1_WP_CD_SEL_POFFSET  0x834
#define BPORT1_AB_SD1_WP_CD_SEL         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SD1_WP_CD_SEL_POFFSET)

#define BPORT1_AB_LVL_SHFTR_EN_POFFSET  0x900
#define BPORT1_AB_LVL_SHFTR_EN          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LVL_SHFTR_EN_POFFSET)

#define BPORT1_AB_OCM_CFG_POFFSET       0x910
#define BPORT1_AB_OCM_CFG               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_OCM_CFG_POFFSET)
#define BPORT1_AB_OCM_CFG_OCM3          (0x1 << 3)
#define BPORT1_AB_OCM_CFG_OCM3_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_OCM_CFG_OCM2          (0x1 << 2)
#define BPORT1_AB_OCM_CFG_OCM2_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_OCM_CFG_OCM1          (0x1 << 1)
#define BPORT1_AB_OCM_CFG_OCM1_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_OCM_CFG_OCM0          0x1
#define BPORT1_AB_OCM_CFG_OCM0_GET(_v)  (_v & 0x1)

#define BPORT1_AB_RESERVED_POFFSET      0xa1c
#define BPORT1_AB_RESERVED              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RESERVED_POFFSET)

#define BPORT1_AB_GPIOB_CTRL_POFFSET    0xb00
#define BPORT1_AB_GPIOB_CTRL            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPIOB_CTRL_POFFSET)

#define BPORT1_AB_GPIOB_CFG_CMOS18_POFFSET  0xb04
#define BPORT1_AB_GPIOB_CFG_CMOS18      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPIOB_CFG_CMOS18_POFFSET)

#define BPORT1_AB_GPIOB_CFG_CMOS25_POFFSET  0xb08
#define BPORT1_AB_GPIOB_CFG_CMOS25      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPIOB_CFG_CMOS25_POFFSET)

#define BPORT1_AB_GPIOB_CFG_CMOS33_POFFSET  0xb0c
#define BPORT1_AB_GPIOB_CFG_CMOS33      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPIOB_CFG_CMOS33_POFFSET)

#define BPORT1_AB_GPIOB_CFG_HSTL_POFFSET  0xb14
#define BPORT1_AB_GPIOB_CFG_HSTL        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPIOB_CFG_HSTL_POFFSET)

#define BPORT1_AB_GPIOB_DRVR_BIAS_CTRL_POFFSET  0xb18
#define BPORT1_AB_GPIOB_DRVR_BIAS_CTRL  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPIOB_DRVR_BIAS_CTRL_POFFSET)

#define BPORT1_AB_DDRIOB_ADDR0_POFFSET  0xb40
#define BPORT1_AB_DDRIOB_ADDR0          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DDRIOB_ADDR0_POFFSET)

#define BPORT1_AB_DDRIOB_ADDR1_POFFSET  0xb44
#define BPORT1_AB_DDRIOB_ADDR1          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DDRIOB_ADDR1_POFFSET)

#define BPORT1_AB_DDRIOB_DATA0_POFFSET  0xb48
#define BPORT1_AB_DDRIOB_DATA0          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DDRIOB_DATA0_POFFSET)

#define BPORT1_AB_DDRIOB_DATA1_POFFSET  0xb4c
#define BPORT1_AB_DDRIOB_DATA1          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DDRIOB_DATA1_POFFSET)

#define BPORT1_AB_DDRIOB_DIFF0_POFFSET  0xb50
#define BPORT1_AB_DDRIOB_DIFF0          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DDRIOB_DIFF0_POFFSET)

#define BPORT1_AB_DDRIOB_DIFF1_POFFSET  0xb54
#define BPORT1_AB_DDRIOB_DIFF1          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DDRIOB_DIFF1_POFFSET)

#define BPORT1_AB_DDRIOB_CLOCK_POFFSET  0xb58
#define BPORT1_AB_DDRIOB_CLOCK          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DDRIOB_CLOCK_POFFSET)

#define BPORT1_AB_DDRIOB_DRIVE_SLEW_ADDR_POFFSET  0xb5c
#define BPORT1_AB_DDRIOB_DRIVE_SLEW_ADDR  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DDRIOB_DRIVE_SLEW_ADDR_POFFSET)

#define BPORT1_AB_DDRIOB_DRIVE_SLEW_DATA_POFFSET  0xb60
#define BPORT1_AB_DDRIOB_DRIVE_SLEW_DATA  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DDRIOB_DRIVE_SLEW_DATA_POFFSET)

#define BPORT1_AB_DDRIOB_DRIVE_SLEW_DIFF_POFFSET  0xb64
#define BPORT1_AB_DDRIOB_DRIVE_SLEW_DIFF  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DDRIOB_DRIVE_SLEW_DIFF_POFFSET)

#define BPORT1_AB_DDRIOB_DRIVE_SLEW_CLOCK_POFFSET  0xb68
#define BPORT1_AB_DDRIOB_DRIVE_SLEW_CLOCK  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DDRIOB_DRIVE_SLEW_CLOCK_POFFSET)

#define BPORT1_AB_DDRIOB_DDR_CTRL_POFFSET  0xb6c
#define BPORT1_AB_DDRIOB_DDR_CTRL       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DDRIOB_DDR_CTRL_POFFSET)

#define BPORT1_AB_DDRIOB_DCI_CTRL_POFFSET  0xb70
#define BPORT1_AB_DDRIOB_DCI_CTRL       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DDRIOB_DCI_CTRL_POFFSET)

#define BPORT1_AB_DDRIOB_DCI_STATUS_POFFSET  0xb74
#define BPORT1_AB_DDRIOB_DCI_STATUS     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DDRIOB_DCI_STATUS_POFFSET)

#define BPORT1_AB_BUFFER_POFFSET        0x0
#define BPORT1_AB_BUFFER                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BUFFER_POFFSET)
#define BPORT1_AB_BUFFER_BYTES          0xc00


#endif