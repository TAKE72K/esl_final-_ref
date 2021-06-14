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

// VMI header files
#include "vmi/vmiDoc.h"

// base model header files
#include "riscvConfig.h"
#include "riscvVariant.h"

//
// Emit common restrictions
//
static void restrictionsCommon(riscvP riscv, vmiDocNodeP node) {

}

//
// Emit N-variant restrictions
//
static RV_DOC_FN(restrictCV32E20) {
    restrictionsCommon(riscv, node);
}

static RV_DOC_FN(restrictCV32E40P) {
    restrictionsCommon(riscv, node);
    vmidocAddText(
        node,
        "Certain custom features of the CV32E40P are unimplemented. "
        "The following Registers are unimplemented: "
        "PCCRs, MIEX, MIPX, PCER, PCMR, HWLP "
        "PRIVLV. "
        "The Custom instructions are unimplemented "
    );
}

static RV_DOC_FN(restrictCV32E40S) {
    restrictionsCommon(riscv, node);
    vmidocAddText(
        node,
        "THIS IS A STARTING POINT AS THE SPECS DEVELOP "
        "More detail to be added once confirmed "
        "Awaiting information for: "
        "PMA (bespoke model requiring specification), "
        "Zce, "
        "ePMP, "
        "Bus Error."
    );
}

static RV_DOC_FN(restrictCV32E40X) {
    restrictionsCommon(riscv, node);
    vmidocAddText(
        node,
        "THIS IS A STARTING POINT AS THE SPECS DEVELOP "
        "More detail to be added once confirmed "
        "Awaiting information for: "
        "PMA (bespoke model requiring specification), "
        "Zce, "
        "Bus Error, "
        "ISA_B (exists in other models, to be added when ratified), "
        "ISA_P (exists in other models, to be added when ratified)."
    );
}

static RV_DOC_FN(restrictCV32A6) {
    restrictionsCommon(riscv, node);
    vmidocAddText(
        node,
        "THIS IS A STARTING POINT AS THE SPECS DEVELOP "
        "More detail to be added once confirmed "
    );
}

static RV_DOC_FN(restrictCV64A6) {
    restrictionsCommon(riscv, node);
    vmidocAddText(
        node,
        "THIS IS A STARTING POINT AS THE SPECS DEVELOP "
        "More detail to be added once confirmed "
    );
}

//
// Defined extensions (null-terminated list)
//
static riscvExtConfigCP openHWExtensions[] = {

    // OpenHW extension configuration (currently empty)
    &(const riscvExtConfig){
        .id       = 0,
        .userData = 0
    },

    0 // KEEP LAST: terminator
};

//
// Defined configurations
//
static const riscvConfig configList[] = {
    {
        .name                = "CV32E20",
        .arch                = RV32I|ISA_C|ISA_M,
        .archMask            = 0x0,         // misa is read-only
        .archFixed           = ~(ISA_C|ISA_E|ISA_M), // C,E,M bit can be changed by parameter
        .user_version        = RVUV_2_3,    // User version 2.3
        .priv_version        = RVPV_1_11,   // Privileged version 1.11
        .dbg_version         = RVDBG_0_13_2,// Debug version 0.13.2

        // local interrupts
        .local_int_num       = 16,          // Number of local interrupts

        // Add debug module (defaults)
        .debug_mode          = RVDM_VECTOR, // DM implemented as vector
        .debug_address       = 0x1A110800,  // debug vector address
        .dexc_address        = 0x1A111000,  // debug exception address
        .debug_eret_mode     = RVDRM_JUMP,  // *RET in Debug mode behavior

        // trigger module
        .trigger_num         = 1,           // number of implemented triggers
        .tinfo               = 0x00000004,  // tinfo default value
        .mcontext_undefined  = False,       // mcontext is defined
        .scontext_undefined  = False,       // scontext is defined
        .tcontrol_undefined  = True,        // tcontrol is undefined
        .mcontext_bits       = 0,           // implemented bits in mcontext
        .scontext_bits       = 0,           // implemented bits in scontext
        .no_hit              = True,        // tdata1.hit is unimplemented

        // instret and cycle counters are defined in base model
        // these are not in RTL and behaviour implemented in extension
        // only mcycle and minstret are accessible
        .instret_undefined   = False,       // instret CSR is defined
        .cycle_undefined     = False,       // cycle CSR is defined

        .time_undefined      = True,        // time CSR is undefined
        .PMP_undefined       = True,        // PMP registers are undefined

        .counteren_mask      = -1,          // all counters are present
        .mcounteren_present  = True,        // mcounteren is present

        .ecode_mask          = 0x0000001F,  // Only valid WLRL bits

        .tval_ii_code        = True,
        .tval_zero           = True,        // [smu]tval are always zero
        .unaligned           = True,        // unaligned accesses are allowed

        .restrictionsCB      = restrictCV32E20,
        .extensionConfigs    = openHWExtensions,

        .enable_CSR_bus      = True,        // enable external CSR bus

        .csr = {
            .mvendorid = {u32 : {bits   : 0x0602}},
            .marchid   = {u32 : {bits   : 0x4}},
            .mimpid    = {u32 : {bits   : 0x0}},
            .mtvec     = {u32 : {fields : {MODE:1}}},
            .mstatus   = {u32 : {fields : {MPP:3}}},
        },
        .csrMask = {
            .mtvec     = {u32 : {bits   : 0xFFFFFF01}},
            .tdata1    = {u32 : {bits   : 0x00000004}},
        },
    },

    {
        .name                = "CV32E40P",
        .arch                = RV32I|ISA_C|ISA_M|ISA_X,
        .archMask            = 0x0,         // misa is read-only
        .archFixed           = ~(ISA_X),    // only X bit can be changed by parameter
        .user_version        = RVUV_2_3,    // User version 2.3
        .priv_version        = RVPV_1_11,   // Privileged version 1.11
        .dbg_version         = RVDBG_0_13_2,// Debug version 0.13.2

        // local interrupts
        .local_int_num       = 16,          // Number of local interrupts

        // Add debug module (defaults)
        .debug_mode          = RVDM_VECTOR, // DM implemented as vector
        .debug_address       = 0x1A110800,  // debug vector address
        .dexc_address        = 0x1A111000,  // debug exception address
        .debug_eret_mode     = RVDRM_JUMP,  // *RET in Debug mode behavior

        // trigger module
        .trigger_num         = 1,           // number of implemented triggers
        .tinfo               = 0x00000004,  // tinfo default value
        .mcontext_undefined  = False,       // mcontext is defined
        .scontext_undefined  = False,       // scontext is defined
        .tcontrol_undefined  = True,        // tcontrol is undefined
        .mcontext_bits       = 0,           // implemented bits in mcontext
        .scontext_bits       = 0,           // implemented bits in scontext
        .no_hit              = True,        // tdata1.hit is unimplemented

        // instret and cycle counters are defined in base model
        // these are not in RTL and behaviour implemented in extension
        // only mcycle and minstret are accessible
        .instret_undefined   = False,       // instret CSR is defined
        .cycle_undefined     = False,       // cycle CSR is defined

        .time_undefined      = True,        // time CSR is undefined
        .PMP_undefined       = True,        // PMP registers are undefined

        .counteren_mask      = -1,          // all counters are present
        .mcounteren_present  = True,        // mcounteren is present

        .ecode_mask          = 0x0000001F,  // Only valid WLRL bits

        .tval_ii_code        = True,
        .tval_zero           = True,        // [smu]tval are always zero
        .unaligned           = True,        // unaligned accesses are allowed

        .restrictionsCB      = restrictCV32E40P,
        .extensionConfigs    = openHWExtensions,

        .enable_CSR_bus      = True,        // enable external CSR bus

        .csr = {
            .mvendorid = {u32 : {bits   : 0x0602}},
            .marchid   = {u32 : {bits   : 0x4}},
            .mimpid    = {u32 : {bits   : 0x0}},
            .mtvec     = {u32 : {fields : {MODE:1}}},
            .mstatus   = {u32 : {fields : {MPP:3}}},
        },
        .csrMask = {
            .mtvec     = {u32 : {bits   : 0xFFFFFF01}},
            .tdata1    = {u32 : {bits   : 0x00000004}},
        },
    },

    {
        .name                = "CV32E40Pv2",
        .arch                = RV32I|ISA_C|ISA_F|ISA_M|ISA_X,
        .archMask            = 0x0,         // misa is read-only
        .archFixed           = ~(ISA_X),    // only X bit can be changed by parameter
        .user_version        = RVUV_2_3,    // User version 2.3
        .priv_version        = RVPV_1_11,   // Privileged version 1.11
        .dbg_version         = RVDBG_0_13_2,// Debug version 0.13.2

        // local interrupts
        .local_int_num       = 16,          // Number of local interrupts

        // Add debug module (defaults)
        .debug_mode          = RVDM_VECTOR, // DM implemented as vector
        .debug_address       = 0x1A110800,  // debug vector address
        .dexc_address        = 0x1A111000,  // debug exception address
        .debug_eret_mode     = RVDRM_JUMP,  // *RET in Debug mode behavior

        // trigger module
        .trigger_num         = 1,           // number of implemented triggers
        .tinfo               = 0x00000004,  // tinfo default value
        .mcontext_undefined  = False,       // mcontext is defined
        .scontext_undefined  = False,       // scontext is defined
        .tcontrol_undefined  = True,        // tcontrol is undefined
        .mcontext_bits       = 0,           // implemented bits in mcontext
        .scontext_bits       = 0,           // implemented bits in scontext
        .no_hit              = True,        // tdata1.hit is unimplemented

        // instret and cycle counters are defined in base model
        // these are not in RTL and behaviour implemented in extension
        // only mcycle and minstret are accessible
        .instret_undefined   = False,       // instret CSR is defined
        .cycle_undefined     = False,       // cycle CSR is defined

        .time_undefined      = True,        // time CSR is undefined
        .PMP_undefined       = True,        // PMP registers are undefined

        .counteren_mask      = -1,          // all counters are present
        .mcounteren_present  = True,        // mcounteren is present

        .ecode_mask          = 0x0000001F,  // Only valid WLRL bits

        .tval_ii_code        = True,
        .tval_zero           = True,        // [smu]tval are always zero
        .unaligned           = True,        // unaligned accesses are allowed

        .restrictionsCB      = restrictCV32E40P,
        .extensionConfigs    = openHWExtensions,

        .enable_CSR_bus      = True,        // enable external CSR bus

        .csr = {
            .mvendorid = {u32 : {bits   : 0x0602}},
            .marchid   = {u32 : {bits   : 0x4}},
            .mimpid    = {u32 : {bits   : 0x0}},
            .mtvec     = {u32 : {fields : {MODE:1}}},
            .mstatus   = {u32 : {fields : {MPP:3}}},
        },
        .csrMask = {
            .mtvec     = {u32 : {bits   : 0xFFFFFF01}},
            .tdata1    = {u32 : {bits   : 0x00000004}},
        },
    },

    //
    // TBD add (in Limitations to be added when spec available and stable)
    //   PMA (bespoke model require spec)
    //   Zce
    //   ePMP
    //   Bus Error
    //
    {
        .name                = "CV32E40S",
        .arch                = RV32I|ISA_C|ISA_M|ISA_U,
        .archMask            = 0x0,         // misa is read-only
        .archFixed           = ~(0),        // no bit can be changed by parameter
        .user_version        = RVUV_2_3,    // User version 2.3
        .priv_version        = RVPV_1_11,   // Privileged version 1.11
        .dbg_version         = RVDBG_0_13_2,// Debug version 0.13.2

        // local interrupts
        .local_int_num       = 16,          // Number of local interrupts

        // Add debug module (defaults)
        .debug_mode          = RVDM_VECTOR, // DM implemented as vector
        .debug_address       = 0x1A110800,  // debug vector address
        .dexc_address        = 0x1A111000,  // debug exception address
        .debug_eret_mode     = RVDRM_JUMP,  // *RET in Debug mode behavior

        // trigger module
        .trigger_num         = 1,           // number of implemented triggers
        .tinfo               = 0x00000004,  // tinfo default value
        .mcontext_undefined  = False,       // mcontext is defined
        .scontext_undefined  = False,       // scontext is defined
        .tcontrol_undefined  = True,        // tcontrol is undefined
        .mcontext_bits       = 0,           // implemented bits in mcontext
        .scontext_bits       = 0,           // implemented bits in scontext
        .no_hit              = True,        // tdata1.hit is unimplemented

        // instret and cycle counters are defined in base model
        // these are not in RTL and behaviour implemented in extension
        // only mcycle and minstret are accessible
        .instret_undefined   = False,       // instret CSR is defined
        .cycle_undefined     = False,       // cycle CSR is defined

        .time_undefined      = True,        // time CSR is undefined
        .PMP_undefined       = True,        // PMP registers are undefined

        .counteren_mask      = -1,          // all counters are present
        .mcounteren_present  = True,        // mcounteren is present

        .ecode_mask          = 0x0000001F,  // Only valid WLRL bits

        .tval_ii_code        = True,
        .tval_zero           = True,        // [smu]tval are always zero
        .unaligned           = True,        // unaligned accesses are allowed

        .restrictionsCB      = restrictCV32E40S,
        .extensionConfigs    = openHWExtensions,

        .enable_CSR_bus      = True,        // enable external CSR bus

        .csr = {
            .mvendorid = {u32 : {bits   : 0x0602}},
            .marchid   = {u32 : {bits   : 0x4}},
            .mimpid    = {u32 : {bits   : 0x0}},
            .mtvec     = {u32 : {fields : {MODE:1}}},
            .mstatus   = {u32 : {fields : {MPP:3}}},
        },
        .csrMask = {
            .mtvec     = {u32 : {bits   : 0xFFFFFF01}},
            .tdata1    = {u32 : {bits   : 0x00000004}},
        },
    },

    //
    // TBD add (in Limitations to be added when spec available and stable)
    //   PMA (bespoke model require spec)
    //    typedef struct packed {
    //      logic [31:0] word_addr_low;
    //      logic [31:0] word_addr_high;
    //      logic        main;
    //      logic        bufferable;
    //      logic        cacheable;
    //      logic        atomic;
    //    } pma_region_t;
    //    main
    //
    //   Zce
    //   Adds exceptions 1 and 24
    //       1 - Instruction Access Fault (misaligned Address)
    //      24 - Instruction Bus Fault (custom)
    //   ISA_B (exists in other models) added when ratified
    //   ISA_P ..
    //
    {
        .name                = "CV32E40X",
        .arch                = RV32I|ISA_A|ISA_C|ISA_M|ISA_X,
        .archMask            = 0x0,         // misa is read-only
        .archFixed           = ~(0),        // no bit can be changed by parameter
        .user_version        = RVUV_2_3,    // User version 2.3
        .priv_version        = RVPV_1_11,   // Privileged version 1.11
        .dbg_version         = RVDBG_0_13_2,// Debug version 0.13.2

        // local interrupts
        .local_int_num       = 16,          // Number of local interrupts

        // Add debug module (defaults)
        .debug_mode          = RVDM_VECTOR, // DM implemented as vector
        .debug_address       = 0x1A110800,  // debug vector address
        .dexc_address        = 0x1A111000,  // debug exception address
        .debug_eret_mode     = RVDRM_JUMP,  // *RET in Debug mode behavior

        // trigger module
        .trigger_num         = 1,           // number of implemented triggers
        .tinfo               = 0x00000004,  // tinfo default value
        .mcontext_undefined  = False,       // mcontext is defined
        .scontext_undefined  = False,       // scontext is defined
        .tcontrol_undefined  = True,        // tcontrol is undefined
        .mcontext_bits       = 0,           // implemented bits in mcontext
        .scontext_bits       = 0,           // implemented bits in scontext
        .no_hit              = True,        // tdata1.hit is unimplemented

        // instret and cycle counters are defined in base model
        // these are not in RTL and behaviour implemented in extension
        // only mcycle and minstret are accessible
        .instret_undefined   = False,       // instret CSR is defined
        .cycle_undefined     = False,       // cycle CSR is defined

        .time_undefined      = True,        // time CSR is undefined
        .PMP_undefined       = True,        // PMP registers are undefined

        .counteren_mask      = -1,          // all counters are present
        .mcounteren_present  = True,        // mcounteren is present

        .ecode_mask          = 0x0000001F,  // Only valid WLRL bits

        .tval_ii_code        = True,
        .tval_zero           = True,        // [smu]tval are always zero
        .unaligned           = True,        // unaligned accesses are allowed

        .restrictionsCB      = restrictCV32E40X,
        .extensionConfigs    = openHWExtensions,

        .enable_CSR_bus      = True,        // enable external CSR bus

        .csr = {
            .mvendorid = {u32 : {bits   : 0x0602}},
            .marchid   = {u32 : {bits   : 0x14}},
            .mimpid    = {u32 : {bits   : 0x0}},
            .mtvec     = {u32 : {fields : {MODE:1}}},
            .mstatus   = {u32 : {fields : {MPP:3}}},
        },
        .csrMask = {
            .mtvec     = {u32 : {bits   : 0xFFFFFF01}},
            .tdata1    = {u32 : {bits   : 0x00000004}},
        },
    },

    {
        .name                = "CV32A6",
        .arch                = RV32I|ISA_A|ISA_C|ISA_M|ISA_S|ISA_U,
        .archMask            = 0x0,         // misa is read-only
        .archFixed           = ~(0),        // no bit can be changed by parameter
        .user_version        = RVUV_2_3,    // User version 2.3
        .priv_version        = RVPV_1_10,   // Privileged version 1.10
        .dbg_version         = RVDBG_0_13_2,// Debug version 0.13.2 (TODO: spec says 0.13)

        .restrictionsCB      = restrictCV32A6,
    },
    {
        .name                = "CV64A6",
        .arch                = RV64I|ISA_A|ISA_C|ISA_M|ISA_S|ISA_U,
        .archMask            = 0x0,         // misa is read-only
        .archFixed           = ~(0),        // no bit can be changed by parameter
        .user_version        = RVUV_2_3,    // User version 2.3
        .priv_version        = RVPV_1_10,   // Privileged version 1.10
        .dbg_version         = RVDBG_0_13_2,// Debug version 0.13.2 (TODO: spec says 0.13)

        .restrictionsCB      = restrictCV64A6,
    },

    {0} // null terminator
};

//
// This returns the supported configuration list
//
riscvConfigCP riscvGetConfigList(riscvP riscv) {
    return configList;
}

