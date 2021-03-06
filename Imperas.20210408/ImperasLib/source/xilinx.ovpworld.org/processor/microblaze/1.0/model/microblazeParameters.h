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

#ifndef MICROBLAZE_PARAMETERS_H
#define MICROBLAZE_PARAMETERS_H

#include "vmi/vmiAttrs.h"
#include "vmi/vmiParameters.h"

#include "microblazeTypeRefs.h"

//
// Define the attributes value structure
//
typedef struct microblazeParamValuesS {

    VMI_ENUM_PARAM(variant);
    VMI_BOOL_PARAM(verbose);
    VMI_ENDIAN_PARAM(endian);
    VMI_UNS32_PARAM(C_FAMILY);
    VMI_UNS32_PARAM(C_AREA_OPTIMIZED);
    VMI_UNS32_PARAM(C_INTERCONNECT);
    VMI_UNS32_PARAM(C_ENDIANNESS);
    VMI_UNS32_PARAM(C_FAULT_TOLERANT);
    VMI_UNS32_PARAM(C_ECC_USE_CE_EXCEPTION);
    VMI_UNS32_PARAM(C_PVR);
    VMI_UNS32_PARAM(C_PVR_USER1);
    VMI_UNS32_PARAM(C_PVR_USER2);
    VMI_ENUM_PARAM(C_RESET_MSR);
    VMI_UNS32_PARAM(C_BASE_VECTORS);
    VMI_UNS32_PARAM(C_D_PLB);
    VMI_UNS32_PARAM(C_D_AXI);
    VMI_BOOL_PARAM(C_D_LMB);
    VMI_UNS32_PARAM(C_I_PLB);
    VMI_UNS32_PARAM(C_I_AXI);
    VMI_BOOL_PARAM(C_I_LMB);
    VMI_UNS32_PARAM(C_M_AXI_DP_EXCLUSIVE_ACCESS);
    VMI_UNS32_PARAM(C_M_AXI_DC_EXCLUSIVE_ACCESS);
    VMI_BOOL_PARAM(C_USE_BARREL);
    VMI_BOOL_PARAM(C_USE_DIV);
    VMI_UNS32_PARAM(C_USE_HW_MUL);
    VMI_UNS32_PARAM(C_USE_FPU);
    VMI_BOOL_PARAM(C_USE_MSR_INSTR);
    VMI_BOOL_PARAM(C_USE_PCMP_INSTR);
    VMI_UNS32_PARAM(C_USE_REORDER_INSTR);
    VMI_BOOL_PARAM(C_UNALIGNED_EXCEPTIONS);
    VMI_BOOL_PARAM(C_ILL_OPCODE_EXCEPTION);
    VMI_UNS32_PARAM(C_IPLB_BUS_EXCEPTION);
    VMI_UNS32_PARAM(C_DPLB_BUS_EXCEPTION);
    VMI_UNS32_PARAM(C_M_AXI_I_BUS_EXCEPTION);
    VMI_UNS32_PARAM(C_M_AXI_D_BUS_EXCEPTION);
    VMI_BOOL_PARAM(C_DIV_ZERO_EXCEPTION);
    VMI_BOOL_PARAM(C_FPU_EXCEPTION);
    VMI_BOOL_PARAM(C_OPCODE_0x0_ILLEGAL);
    VMI_BOOL_PARAM(C_FSL_EXCEPTION);
    VMI_UNS32_PARAM(C_USE_STACK_PROTECTION);
    VMI_BOOL_PARAM(C_DEBUG_ENABLED);
    VMI_UNS32_PARAM(C_NUMBER_OF_PC_BRK);
    VMI_UNS32_PARAM(C_NUMBER_OF_RD_ADDR_BRK);
    VMI_UNS32_PARAM(C_NUMBER_OF_WR_ADDR_BRK);
    VMI_UNS32_PARAM(C_INTERRUPT_IS_EDGE);
    VMI_UNS32_PARAM(C_EDGE_IS_POSITIVE);
    VMI_UNS32_PARAM(C_FSL_LINKS);
    VMI_BOOL_PARAM(C_USE_EXTENDED_FSL_INSTR);
    VMI_UNS32_PARAM(C_ICACHE_BASEADDR);
    VMI_UNS32_PARAM(C_ICACHE_HIGHADDR);
    VMI_UNS32_PARAM(C_USE_ICACHE);
    VMI_UNS32_PARAM(C_ALLOW_ICACHE_WR);
    VMI_ENUM_PARAM(C_ICACHE_LINE_LEN);
    VMI_UNS32_PARAM(C_ICACHE_ALWAYS_USED);
    VMI_ENUM_PARAM(C_ICACHE_INTERFACE);
    VMI_UNS32_PARAM(C_ICACHE_FORCE_TAG_LUTRAM);
    VMI_UNS32_PARAM(C_ICACHE_STREAMS);
    VMI_ENUM_PARAM(C_ICACHE_VICTIMS);
    VMI_UNS32_PARAM(C_ICACHE_DATA_WIDTH);
    VMI_UNS32_PARAM(C_ADDR_TAG_BITS);
    VMI_ENUM_PARAM(C_CACHE_BYTE_SIZE);
    VMI_UNS32_PARAM(C_ICACHE_USE_FSL);
    VMI_UNS32_PARAM(C_DCACHE_BASEADDR);
    VMI_UNS32_PARAM(C_DCACHE_HIGHADDR);
    VMI_UNS32_PARAM(C_USE_DCACHE);
    VMI_UNS32_PARAM(C_ALLOW_DCACHE_WR);
    VMI_ENUM_PARAM(C_DCACHE_LINE_LEN);
    VMI_UNS32_PARAM(C_DCACHE_ALWAYS_USED);
    VMI_ENUM_PARAM(C_DCACHE_INTERFACE);
    VMI_UNS32_PARAM(C_DCACHE_FORCE_TAG_LUTRAM);
    VMI_UNS32_PARAM(C_DCACHE_USE_WRITEBACK);
    VMI_ENUM_PARAM(C_DCACHE_VICTIMS);
    VMI_UNS32_PARAM(C_DCACHE_DATA_WIDTH);
    VMI_UNS32_PARAM(C_DCACHE_ADDR_TAG);
    VMI_ENUM_PARAM(C_DCACHE_BYTE_SIZE);
    VMI_UNS32_PARAM(C_DCACHE_USE_FSL);
    VMI_UNS32_PARAM(C_USE_MMU);
    VMI_UNS32_PARAM(C_MMU_DTLB_SIZE);
    VMI_UNS32_PARAM(C_MMU_ITLB_SIZE);
    VMI_UNS32_PARAM(C_MMU_TLB_ACCESS);
    VMI_UNS32_PARAM(C_MMU_ZONES);
    VMI_UNS32_PARAM(C_MMU_PRIVILEGED_INSTR);
    VMI_UNS32_PARAM(C_USE_INTERRUPT);
    VMI_UNS32_PARAM(C_USE_EXT_BRK);
    VMI_UNS32_PARAM(C_USE_EXT_NM_BRK);
    VMI_UNS32_PARAM(C_USE_BRANCH_TARGET_CACHE);
    VMI_UNS32_PARAM(C_BRANCH_TARGET_CACHE_SIZE);
    VMI_UNS32_PARAM(C_STREAM_INTERCONNECT);

} microblazeParamValues, *microblazeParamValuesP;

#endif // MICROBLAZE_PARAMETERS_H
