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

// model header files
#include "andesConfig.h"
#include "andesVariant.h"

// base model header files
#include "riscvConfig.h"
#include "riscvVariant.h"


//
// Emit common restrictions
//
static void restrictionsCommon(riscvP riscv, vmiDocNodeP node) {

    vmidocAddText(
        node,
        "Andes-specific cache, local memory and ECC behavior is not yet "
        "implemented, except for CSR state."
    );

    vmidocAddText(
        node,
        "Andes Performance and Code Dense instructions and associated CSR "
        "state are implemented, but the EXEC.IT instruction supports in-memory "
        "table mode using the uitb CSR only (not hardwired mode)."
    );

    vmidocAddText(
        node,
        "PMP and PMA accesses that any-byte match but do not all-byte match "
        "are broken into separate smaller accesses that follow all-byte match "
        "rules."
    );
}

//
// Emit N-variant restrictions
//
static RV_DOC_FN(restrictionsN) {
    restrictionsCommon(riscv, node);
}

//
// Emit A-variant restrictions
//
static RV_DOC_FN(restrictionsA) {

    vmidocAddText(
        node,
        "This variant is under development. It includes Supervisor mode and "
        "associated standard RISC-V features, but some Andes-specific CSRs "
        "are not yet implemented."
    );

    restrictionsCommon(riscv, node);
}

//
// N25 variant documentation
//
static const char *specificDocsN25[] = {
    "---- AndesCore_N25_DS130_V1.0 DS130-10",
    "---- AndeStar V5 Architecture and CSR Definitions (UM164-1515, 2020-05-08)",
    0
};

//
// NX25 variant documentation
//
static const char *specificDocsNX25[] = {
    "---- AndesCore_NX25_DS131_V1.0 DS131-10",
    "---- AndeStar V5 Architecture and CSR Definitions (UM164-1515, 2020-05-08)",
    0
};

//
// A25 variant documentation
//
static const char *specificDocsA25[] = {
    "---- AndesCore_A25_DS141_V1.1 DS141-11",
    "---- AndeStar V5 Architecture and CSR Definitions (UM164-1515, 2020-05-08)",
    0
};

//
// AX25 variant documentation
//
static const char *specificDocsAX25[] = {
    "---- AndesCore_AX25_DS142_V1.1 DS142-11",
    "---- AndeStar V5 Architecture and CSR Definitions (UM164-1515, 2020-05-08)",
    0
};

//
// Common Andes variant configuration
//
#define ANDES_COMMON_CONFIG(_NAME, _ARCH, _NUMHARTS) \
    .name             = _NAME,                          \
    .arch             = _ARCH,                          \
    .numHarts         = _NUMHARTS,                      \
    .archMask         = RV_ARCH_MASK_DEFAULT,           \
    .user_version     = RVUV_2_2,                       \
    .priv_version     = RVPV_1_10,                      \
    .tval_ii_code     = True,                           \
    .counteren_mask   = 0x7f,                           \
    .trigger_num      = 4,                              \
    .tinfo            = 0x3d, /* types 0, 2, 3, 4, 5 */ \
    .mcontext_bits    = ((_ARCH)&RV64) ? 13 : 6,        \
    .scontext_bits    = ((_ARCH)&RV64) ? 34 : 16,       \
    .mvalue_bits      = ((_ARCH)&RV64) ? 13 : 6,        \
    .svalue_bits      = ((_ARCH)&RV64) ? 34 : 16,       \
    .mcontrol_maskmax = 63

//
// Defined configurations
//
static const riscvConfig configList[] = {

    {
        ANDES_COMMON_CONFIG(
            "N25",
            ISA_U|RV32IMAC|ISA_X,
            0
        ),
        .csr = {
            .mvendorid   = {u32 : {bits   : 0x31e}},
            .marchid     = {u32 : {bits   : 0x10000025}},
            .mimpid      = {u32 : {bits   : 0x20}},
            .mstatus     = {u32 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsN25,
        .restrictionsCB  = restrictionsN,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .csr = {
                        .mmsc_cfg = {
                            u32 : {
                                fields : {
                                    ECD   :1,
                                    EV5MPE:1,
                                    HSP   :1,
                                    PFT   :1,
                                    PMNDS :1
                                }
                            }
                        },
                    },
                    .csrMask = {
                        .milmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                        .mdlmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                    }
                }
            },

            0   // KEEP LAST: terminator
        }
    },
    {
        ANDES_COMMON_CONFIG(
            "NX25",
            ISA_U|RV64IMAC|ISA_X,
            0
        ),
        .csr = {
            .mvendorid   = {u64 : {bits   : 0x31e}},
            .marchid     = {u64 : {bits   : 0x1000000000008025ULL}},
            .mimpid      = {u64 : {bits   : 0x10}},
            .mstatus     = {u64 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsNX25,
        .restrictionsCB  = restrictionsN,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .csr = {
                        .mmsc_cfg = {
                            u32 : {
                                fields : {
                                    ECD   :1,
                                    EV5MPE:1,
                                    HSP   :1,
                                    PFT   :1,
                                    PMNDS :1
                                }
                            }
                        },
                    },
                    .csrMask = {
                        .milmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                        .mdlmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                    }
                }
            },

            0   // KEEP LAST: terminator
        }
    },
    {
        ANDES_COMMON_CONFIG(
            "N25F",
            ISA_U|RV32IMAC|ISA_X|ISA_F|ISA_D,
            0
        ),
        .csr = {
            .mvendorid   = {u32 : {bits   : 0x31e}},
            .marchid     = {u32 : {bits   : 0x10000025}},
            .mimpid      = {u32 : {bits   : 0x20}},
            .mstatus     = {u32 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsN25,
        .restrictionsCB  = restrictionsN,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .csr = {
                        .mmsc_cfg = {
                            u32 : {
                                fields : {
                                    ECD   :1,
                                    EV5MPE:1,
                                    HSP   :1,
                                    PFT   :1,
                                    EFHW  :0,
                                    PMNDS :1
                                }
                            }
                        },
                    },
                    .csrMask = {
                        .milmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                        .mdlmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                    }
                }
            },

            0   // KEEP LAST: terminator
        }
    },
    {
        ANDES_COMMON_CONFIG(
            "NX25F",
            ISA_U|RV64IMAC|ISA_X|ISA_F|ISA_D,
            0
        ),
        .csr = {
            .mvendorid   = {u64 : {bits   : 0x31e}},
            .marchid     = {u64 : {bits   : 0x1000000000008025ULL}},
            .mimpid      = {u64 : {bits   : 0x10}},
            .mstatus     = {u64 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsNX25,
        .restrictionsCB  = restrictionsN,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .csr = {
                        .mmsc_cfg = {
                            u32 : {
                                fields : {
                                    ECD   :1,
                                    EV5MPE:1,
                                    HSP   :1,
                                    PFT   :1,
                                    EFHW  :0,
                                    PMNDS :1
                                }
                            }
                        },
                    },
                    .csrMask = {
                        .milmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                        .mdlmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                    }
                }
            },

            0   // KEEP LAST: terminator
        }
    },
    {
        ANDES_COMMON_CONFIG(
            "A25",
            ISA_U|ISA_S|RV32IMAC|ISA_X,
            RV_NUMHARTS_0
        ),
        .csr = {
            .mvendorid   = {u32 : {bits   : 0x31e}},
            .marchid     = {u32 : {bits   : 0x10000a25}},
            .mimpid      = {u32 : {bits   : 0x20}},
            .mstatus     = {u32 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsA25,
        .restrictionsCB  = restrictionsA,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .csr = {
                        .mmsc_cfg = {
                            u32 : {
                                fields : {
                                    ECD   :1,
                                    EV5MPE:1,
                                    HSP   :1,
                                    PFT   :1,
                                    PMNDS :1
                                }
                            }
                        },
                    },
                    .csrMask = {
                        .milmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                        .mdlmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                    }
                }
            },

            0   // KEEP LAST: terminator
        }
    },
    {
        ANDES_COMMON_CONFIG(
            "AX25",
            ISA_U|ISA_S|RV64IMAC|ISA_X,
            RV_NUMHARTS_0
        ),
        .csr = {
            .mvendorid   = {u64 : {bits   : 0x31e}},
            .marchid     = {u64 : {bits   : 0x1000000000008a25ULL}},
            .mimpid      = {u64 : {bits   : 0x10}},
            .mstatus     = {u64 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsAX25,
        .restrictionsCB  = restrictionsA,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .csr = {
                        .mmsc_cfg = {
                            u32 : {
                                fields : {
                                    ECD   :1,
                                    EV5MPE:1,
                                    HSP   :1,
                                    PFT   :1,
                                    PMNDS :1
                                }
                            }
                        },
                    },
                    .csrMask = {
                        .milmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                        .mdlmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                    }
                }
            },

            0   // KEEP LAST: terminator
        }
    },
    {
        ANDES_COMMON_CONFIG(
            "A25F",
            ISA_U|ISA_S|RV32IMAC|ISA_X|ISA_F|ISA_D,
            RV_NUMHARTS_0
        ),
        .csr = {
            .mvendorid   = {u32 : {bits   : 0x31e}},
            .marchid     = {u32 : {bits   : 0x10000a25}},
            .mimpid      = {u32 : {bits   : 0x20}},
            .mstatus     = {u32 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsA25,
        .restrictionsCB  = restrictionsA,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .csr = {
                        .mmsc_cfg = {
                            u32 : {
                                fields : {
                                    ECD   :1,
                                    EV5MPE:1,
                                    HSP   :1,
                                    PFT   :1,
                                    EFHW  :0,
                                    PMNDS :1
                                }
                            }
                        },
                    },
                    .csrMask = {
                        .milmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                        .mdlmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                    }
                }
            },

            0   // KEEP LAST: terminator
        }
    },
    {
        ANDES_COMMON_CONFIG(
            "AX25F",
            ISA_U|ISA_S|RV64IMAC|ISA_X|ISA_F|ISA_D,
            RV_NUMHARTS_0
        ),
        .csr = {
            .mvendorid   = {u64 : {bits   : 0x31e}},
            .marchid     = {u64 : {bits   : 0x1000000000008a25ULL}},
            .mimpid      = {u64 : {bits   : 0x10}},
            .mstatus     = {u64 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsAX25,
        .restrictionsCB  = restrictionsA,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .csr = {
                        .mmsc_cfg = {
                             u32 : {
                                 fields : {
                                     ECD   :1,
                                     EV5MPE:1,
                                     HSP   :1,
                                     PFT   :1,
                                     EFHW  :0,
                                     PMNDS :1
                                 }
                             }
                        },
                    },
                    .csrMask = {
                        .milmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                        .mdlmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                    }
                }
            },

            0   // KEEP LAST: terminator
        }
    },

    {0} // null terminator
};

//
// This returns the supported configuration list
//
riscvConfigCP riscvGetConfigList(riscvP riscv) {
    return configList;
}

