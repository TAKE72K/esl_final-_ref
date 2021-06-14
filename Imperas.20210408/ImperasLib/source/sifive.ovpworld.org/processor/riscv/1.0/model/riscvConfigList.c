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

// model header files
#include "riscvConfig.h"
#include "riscvVariant.h"
#include "riscvVMConstants.h"

// extension header files
#include "sifiveConfig.h"
#include "sifiveVariant.h"

//
// Specify variant-specific documentation
//
#define SPECIFIC_DOC(_NAME) (const char *[]){_NAME, 0}

//
// Mandatory extension configuration macro
// - _VARIANT = 0 => No custom extension behavior
//
#define SIFIVE_EXTENSION(_VARIANT) \
    .extensionConfigs = (riscvExtConfigCP[]){ \
        &(const riscvExtConfig){ \
            .id       = SIFIVE_OVP_CONFIG_ID, \
            .userData = &(const sifiveConfig){ \
                .variant = _VARIANT, \
            } \
        }, \
        0 \
    }

// Silicon revision 21G1
// adds Zba Zbb to 2 and 7 cores (version unknown, set to latest with reference)
//        .bitmanip_version   = RVBV_0_93,
//        .bitmanip_absent    = ~(RVBS_Zba|RVBS_Zbb),
// adds Zfh half precision floating point to all cores with floating point
//        .riscvFP16Ver = RVFP16_IEEE754,

//
// Defined configurations
//
static const riscvConfig configList[] = {

    {
        .name            = "E20",
        .arch            = RV32IMC,
        .archMask        = ~(ISA_XLEN_ANY|ISA_E|ISA_I|ISA_U),
        .archFixed       = ~(ISA_A|ISA_E|ISA_F|ISA_U),
        .user_version    = RVUV_2_3,
        .priv_version    = RVPV_1_11,
        .specificDocs    = SPECIFIC_DOC("SiFive E20 Manual v19.05"),
        .PMP_registers   = 0,
        .tval_ii_code    = True,
        .local_int_num   = 16,
        .time_undefined  = True,
        .lr_sc_grain     = 64,
        .tvec_align      = 64,
        .d_requires_f    = True,
        .mstatus_fs_mode = RVFS_ALWAYS_DIRTY,
        .ecode_mask      = 0x1f,
        .counteren_mask  = -1,
        SIFIVE_EXTENSION(0)
    },

    {
        .name            = "E21",
        .arch            = ISA_U|RV32IMAC,
        .archMask        = ~(ISA_XLEN_ANY|ISA_E|ISA_I|ISA_S|ISA_U),
        .archFixed       = ~(ISA_E|ISA_F),
        .user_version    = RVUV_2_3,
        .priv_version    = RVPV_1_11,
        .specificDocs    = SPECIFIC_DOC("SiFive E21 Manual v19.05"),
        .PMP_registers   = 8,
        .tval_ii_code    = True,
        .local_int_num   = 16,
        .time_undefined  = True,
        .lr_sc_grain     = 64,
        .tvec_align      = 64,
        .d_requires_f    = True,
        .mstatus_fs_mode = RVFS_ALWAYS_DIRTY,
        .ecode_mask      = 0x1f,
        .counteren_mask  = -1,
        SIFIVE_EXTENSION(0)
    },

    {
        .name            = "E24",
        .arch            = ISA_U|ISA_F|RV32IMAC,
        .archMask        = ~(ISA_XLEN_ANY|ISA_E|ISA_I|ISA_S|ISA_U),
        .archFixed       = ~(ISA_E),
        .user_version    = RVUV_2_3,
        .priv_version    = RVPV_1_11,
        .specificDocs    = SPECIFIC_DOC("SiFive E24 Manual v19.05"),
        .PMP_registers   = 8,
        .tval_ii_code    = True,
        .local_int_num   = 16,
        .time_undefined  = True,
        .lr_sc_grain     = 64,
        .tvec_align      = 64,
        .d_requires_f    = True,
        .mstatus_fs_mode = RVFS_ALWAYS_DIRTY,
        .ecode_mask      = 0x1f,
        .counteren_mask  = -1,
        SIFIVE_EXTENSION(0)
    },

    {
        .name            = "E31",
        .arch            = ISA_U|RV32IMAC,
        .archMask        = ~(ISA_XLEN_ANY|ISA_E|ISA_I|ISA_S|ISA_U),
        .archFixed       = ~(ISA_D|ISA_E|ISA_F),
        .user_version    = RVUV_2_3,
        .priv_version    = RVPV_1_11,
        .specificDocs    = SPECIFIC_DOC("SiFive E31 Coreplex Manual v1p2"),
        .PMP_registers   = 8,
        .tval_ii_code    = True,
        .local_int_num   = 16,
        .time_undefined  = True,
        .lr_sc_grain     = 64,
        .tvec_align      = 64,
        .d_requires_f    = True,
        .mstatus_fs_mode = RVFS_ALWAYS_DIRTY,
        .numHarts        = 1,  // override with numHarts parameter
        .ecode_mask      = 0x1f,
        .counteren_mask  = -1,
        SIFIVE_EXTENSION(0)
    },

    {
        .name            = "E34",
        .arch            = ISA_U|ISA_F|RV32IMAC,
        .archMask        = ~(ISA_XLEN_ANY|ISA_E|ISA_I|ISA_S|ISA_U),
        .archFixed       = ~(ISA_D|ISA_E),
        .user_version    = RVUV_2_3,
        .priv_version    = RVPV_1_11,
        .specificDocs    = SPECIFIC_DOC("SiFive E34 Manual v19.05"),
        .PMP_registers   = 8,
        .tval_ii_code    = True,
        .local_int_num   = 16,
        .time_undefined  = True,
        .lr_sc_grain     = 64,
        .tvec_align      = 64,
        .d_requires_f    = True,
        .mstatus_fs_mode = RVFS_ALWAYS_DIRTY,
        .numHarts        = 1,  // override with numHarts parameter
        .ecode_mask      = 0x1f,
        .counteren_mask  = -1,
        SIFIVE_EXTENSION(0)
    },

    {
        .name            = "E76",
        .arch            = ISA_U|ISA_F|RV32IMAC,
        .archMask        = ~(ISA_XLEN_ANY|ISA_E|ISA_I|ISA_S|ISA_U),
        .archFixed       = ~(ISA_D|ISA_E),
        .user_version    = RVUV_2_3,
        .priv_version    = RVPV_1_11,
        .specificDocs    = SPECIFIC_DOC("SiFive E76 Manual v19.05"),
        .PMP_registers   = 8,
        .tval_ii_code    = True,
        .local_int_num   = 16,
        .time_undefined  = True,
        .lr_sc_grain     = 64,
        .tvec_align      = 64,
        .d_requires_f    = True,
        .mstatus_fs_mode = RVFS_ALWAYS_DIRTY,
        .numHarts        = 1,  // override with numHarts parameter
        .ecode_mask      = 0x1f,
        .counteren_mask  = -1,
        SIFIVE_EXTENSION(S5V_FDCP|S5V_CFLUSH),
    },

    {
        .name            = "E51",
        .arch            = ISA_U|RV64IMAC,
        .archMask        = ~(ISA_XLEN_ANY|ISA_E|ISA_I|ISA_S|ISA_U),
        .archFixed       = ~(ISA_D|ISA_F),
        .user_version    = RVUV_2_3,
        .priv_version    = RVPV_1_11,
        .specificDocs    = SPECIFIC_DOC("SiFive E51 Core Complex Manual v1p2"),
        .PMP_registers   = 8,
        .tval_ii_code    = True,
        .local_int_num   = 16,
        .time_undefined  = True,
        .lr_sc_grain     = 64,
        .tvec_align      = 64,
        .d_requires_f    = True,
        .mstatus_fs_mode = RVFS_ALWAYS_DIRTY,
        .numHarts        = 1,  // override with numHarts parameter
        .ecode_mask      = 0x1f,
        .counteren_mask  = -1,
        .csrMask = {
            .mtvec = {u64 : {bits : 0x0000003fffffffffULL}},
        },
        SIFIVE_EXTENSION(0)
    },

    {
        .name            = "S21",
        .arch            = ISA_U|RV64IMAC,
        .archMask        = ~(ISA_XLEN_ANY|ISA_I|ISA_U),
        .archFixed       = ~(ISA_F|ISA_S),
        .user_version    = RVUV_2_3,
        .priv_version    = RVPV_1_11,
        .specificDocs    = SPECIFIC_DOC("SiFive S21 Manual v19.05"),
        .PMP_registers   = 8,
        .tval_ii_code    = True,
        .local_int_num   = 16,
        .time_undefined  = True,
        .lr_sc_grain     = 64,
        .tvec_align      = 64,
        .d_requires_f    = True,
        .mstatus_fs_mode = RVFS_ALWAYS_DIRTY,
        .numHarts        = 1,  // override with numHarts parameter
        .ecode_mask      = 0x1f,
        .counteren_mask  = -1,
        .csrMask = {
            .mtvec = {u64 : {bits : 0x0000003fffffffffULL}},
        },
        SIFIVE_EXTENSION(0)
    },

    {
        .name            = "S51",
        .arch            = ISA_U|RV64IMAC,
        .archMask        = ~(ISA_XLEN_ANY|ISA_I|ISA_U),
        .archFixed       = ~(ISA_D|ISA_F),
        .user_version    = RVUV_2_3,
        .priv_version    = RVPV_1_11,
        .specificDocs    = SPECIFIC_DOC("SiFive S51 (E51) Core Complex Manual v2p0"),
        .PMP_registers   = 8,
        .tval_ii_code    = True,
        .local_int_num   = 16,
        .time_undefined  = True,
        .lr_sc_grain     = 64,
        .tvec_align      = 64,
        .d_requires_f    = True,
        .mstatus_fs_mode = RVFS_ALWAYS_DIRTY,
        .numHarts        = 1,  // override with numHarts parameter
        .ecode_mask      = 0x1f,
        .counteren_mask  = -1,
        .csrMask = {
            .mtvec = {u64 : {bits : 0x0000003fffffffffULL}},
        },
        SIFIVE_EXTENSION(S5V_BPM|S5V_FDCP|S5V_CEASE)
    },

    {
        .name            = "S54",
        .arch            = ISA_U|RV64GC,
        .archMask        = ~(ISA_XLEN_ANY|ISA_I|ISA_U),
        .archFixed       = ~(0),
        .user_version    = RVUV_2_3,
        .priv_version    = RVPV_1_11,
        .specificDocs    = SPECIFIC_DOC("SiFive S54 Manual v19.05"),
        .PMP_registers   = 8,
        .tval_ii_code    = True,
        .local_int_num   = 16,
        .time_undefined  = True,
        .lr_sc_grain     = 64,
        .tvec_align      = 64,
        .d_requires_f    = True,
        .mstatus_fs_mode = RVFS_ALWAYS_DIRTY,
        .numHarts        = 1,  // override with numHarts parameter
        .ecode_mask      = 0x1f,
        .counteren_mask  = -1,
        .csrMask = {
            .mtvec = {u64 : {bits : 0x0000003fffffffffULL}},
        },
        SIFIVE_EXTENSION(0)
    },

    {
        .name            = "S76",
        .arch            = ISA_U|RV64GC,
        .archMask        = ~(ISA_XLEN_ANY|ISA_I|ISA_U),
        .archFixed       = ~(0),
        .user_version    = RVUV_2_3,
        .priv_version    = RVPV_1_11,
        .specificDocs    = SPECIFIC_DOC("SiFive S76 Manual v19.05"),
        .PMP_registers   = 8,
        .tval_ii_code    = True,
        .local_int_num   = 16,
        .time_undefined  = True,
        .lr_sc_grain     = 64,
        .tvec_align      = 64,
        .d_requires_f    = True,
        .mstatus_fs_mode = RVFS_ALWAYS_DIRTY,
        .numHarts        = 1,  // override with numHarts parameter
        .ecode_mask      = 0x1f,
        .counteren_mask  = -1,
        .csrMask = {
            .mtvec = {u64 : {bits : 0x0000003fffffffffULL}},
        },
        SIFIVE_EXTENSION(S5V_FDCP|S5V_CFLUSH),
    },

    {
        .name            = "U54",
        .arch            = ISA_U|ISA_S|RV64GC,
        .archMask        = ~(ISA_XLEN_ANY|ISA_I|ISA_S|ISA_U),
        .archFixed       = ~(0),
        .user_version    = RVUV_2_3,
        .priv_version    = RVPV_1_11,
        .specificDocs    = SPECIFIC_DOC("SiFive U54-MC Core Complex Manual v1p0"),
        .PMP_registers   = 8,
        .tval_ii_code    = True,
        .local_int_num   = 48,
        .time_undefined  = True,
        .lr_sc_grain     = 64,
        .tvec_align      = 64,
        .d_requires_f    = True,
        .mstatus_fs_mode = RVFS_ALWAYS_DIRTY,
        .numHarts        = 1,  // override with numHarts parameter
        .Sv_modes        = RISCV_VMM_SV39,
        .ecode_mask      = 0x1f,
        .counteren_mask  = -1,
        .csrMask = {
            .mtvec = {u64 : {bits : 0x0000003fffffffffULL}},
            .stvec = {u64 : {bits : 0xffffffffffffffffULL}},
        },
        SIFIVE_EXTENSION(S5V_BPM|S5V_FDCP|S5V_CFLUSH|S5V_CEASE)
    },

    {
        .name            = "U74",
        .arch            = ISA_U|ISA_S|RV64GC,
        .archMask        = ~(ISA_XLEN_ANY|ISA_I|ISA_S|ISA_U),
        .archFixed       = ~(0),
        .user_version    = RVUV_2_3,
        .priv_version    = RVPV_1_11,
        .specificDocs    = SPECIFIC_DOC("SiFive U74 Manual v19.05"),
        .PMP_registers   = 8,
        .tval_ii_code    = True,
        .local_int_num   = 48,
        .time_undefined  = True,
        .lr_sc_grain     = 64,
        .tvec_align      = 64,
        .d_requires_f    = True,
        .mstatus_fs_mode = RVFS_ALWAYS_DIRTY,
        .numHarts        = 1,  // override with numHarts parameter
        .Sv_modes        = RISCV_VMM_SV39,
        .ecode_mask      = 0x1f,
        .counteren_mask  = -1,
        .csrMask = {
            .mtvec = {u64 : {bits : 0x0000003fffffffffULL}},
            .stvec = {u64 : {bits : 0xffffffffffffffffULL}},
        },
        SIFIVE_EXTENSION(S5V_BPM|S5V_FDCP|S5V_CFLUSH|S5V_CEASE),
    },

    {0} // null terminator
};

//
// This returns the supported configuration list
//
riscvConfigCP riscvGetConfigList(riscvP riscv) {
    return configList;
}

