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

#pragma once

// basic number types
#include "hostapi/impTypes.h"

// model header files
#include "riscvRegisterTypes.h"
#include "riscvTypes.h"
#include "riscvTypeRefs.h"
#include "riscvVariant.h"


//
// This enumerates generic instructions
//
typedef enum riscvITypeE {

    // move pseudo-instructions (register and constant source)
    RV_IT_MV_R,
    RV_IT_MV_C,

    // base R-type instructions
    RV_IT_ADD_R,
    RV_IT_AND_R,
    RV_IT_OR_R,
    RV_IT_SLL_R,
    RV_IT_SLT_R,
    RV_IT_SLTU_R,
    RV_IT_SRA_R,
    RV_IT_SRL_R,
    RV_IT_SUB_R,
    RV_IT_XOR_R,

    // M-extension R-type instructions
    RV_IT_DIV_R,
    RV_IT_DIVU_R,
    RV_IT_MUL_R,
    RV_IT_MULH_R,
    RV_IT_MULHSU_R,
    RV_IT_MULHU_R,
    RV_IT_REM_R,
    RV_IT_REMU_R,

    // base I-type instructions
    RV_IT_ADDI_I,
    RV_IT_ANDI_I,
    RV_IT_JALR_I,
    RV_IT_ORI_I,
    RV_IT_SLTI_I,
    RV_IT_SLTIU_I,
    RV_IT_SLLI_I,
    RV_IT_SRAI_I,
    RV_IT_SRLI_I,
    RV_IT_XORI_I,

    // base I-type instructions for load and store
    RV_IT_L_I,
    RV_IT_S_I,

    // base I-type instructions for CSR access (register)
    RV_IT_CSRR_I,

    // base I-type instructions for CSR access (constant)
    RV_IT_CSRRI_I,

    // miscellaneous system I-type instructions
    RV_IT_EBREAK_I,
    RV_IT_ECALL_I,
    RV_IT_FENCEI_I,
    RV_IT_MRET_I,
    RV_IT_SRET_I,
    RV_IT_URET_I,
    RV_IT_DRET_I,
    RV_IT_WFI_I,

    // system fence I-type instruction
    RV_IT_FENCE_I,

    // system fence R-type instructions
    RV_IT_SFENCE_VMA_R,
    RV_IT_HFENCE_VVMA_R,
    RV_IT_HFENCE_GVMA_R,

    // base U-type instructions
    RV_IT_AUIPC_U,
    RV_IT_LUI_U,

    // base B-type instructions
    RV_IT_BEQ_B,
    RV_IT_BGE_B,
    RV_IT_BGEU_B,
    RV_IT_BLT_B,
    RV_IT_BLTU_B,
    RV_IT_BNE_B,

    // base J-type instructions
    RV_IT_JAL_J,

    // A-extension R-type instructions
    RV_IT_AMOADD_R,
    RV_IT_AMOAND_R,
    RV_IT_AMOMAX_R,
    RV_IT_AMOMAXU_R,
    RV_IT_AMOMIN_R,
    RV_IT_AMOMINU_R,
    RV_IT_AMOOR_R,
    RV_IT_AMOSWAP_R,
    RV_IT_AMOXOR_R,
    RV_IT_LR_R,
    RV_IT_SC_R,

    // F-extension and D-extension R-type instructions
    RV_IT_FMV_R,
    RV_IT_FABS_R,
    RV_IT_FADD_R,
    RV_IT_FCLASS_R,
    RV_IT_FCVT_R,
    RV_IT_FDIV_R,
    RV_IT_FEQ_R,
    RV_IT_FLE_R,
    RV_IT_FLT_R,
    RV_IT_FMAX_R,
    RV_IT_FMIN_R,
    RV_IT_FMUL_R,
    RV_IT_FNEG_R,
    RV_IT_FSGNJ_R,
    RV_IT_FSGNJN_R,
    RV_IT_FSGNJX_R,
    RV_IT_FSQRT_R,
    RV_IT_FSUB_R,

    // F-extension and D-extension R4-type instructions
    RV_IT_FMADD_R4,
    RV_IT_FMSUB_R4,
    RV_IT_FNMADD_R4,
    RV_IT_FNMSUB_R4,

    // X-extension instructions
    RV_IT_CUSTOM,

    // B-extension R-type instructions
    RV_IT_ANDN_R,
    RV_IT_ORN_R,
    RV_IT_XNOR_R,
    RV_IT_SLO_R,
    RV_IT_SRO_R,
    RV_IT_ROL_R,
    RV_IT_ROR_R,
    RV_IT_SBCLR_R,
    RV_IT_SBSET_R,
    RV_IT_SBINV_R,
    RV_IT_SBEXT_R,
    RV_IT_GORC_R,
    RV_IT_GREV_R,
    RV_IT_CLZ_R,
    RV_IT_CTZ_R,
    RV_IT_PCNT_R,
    RV_IT_SEXT_R,
    RV_IT_CRC32_R,
    RV_IT_CRC32C_R,
    RV_IT_CLMUL_R,
    RV_IT_CLMULR_R,
    RV_IT_CLMULH_R,
    RV_IT_MIN_R,
    RV_IT_MAX_R,
    RV_IT_MINU_R,
    RV_IT_MAXU_R,
    RV_IT_SHFL_R,
    RV_IT_UNSHFL_R,
    RV_IT_BDEP_R,
    RV_IT_BEXT_R,
    RV_IT_PACK_R,
    RV_IT_PACKH_R,
    RV_IT_PACKU_R,
    RV_IT_PACKW_R,
    RV_IT_PACKUW_R,
    RV_IT_ZEXT32_H_R,
    RV_IT_ZEXT64_H_R,
    RV_IT_BMATFLIP_R,
    RV_IT_BMATOR_R,
    RV_IT_BMATXOR_R,
    RV_IT_BFP_R,
    RV_IT_ADDWU_R,
    RV_IT_SUBWU_R,
    RV_IT_ADDU_W_R,
    RV_IT_SUBU_W_R,
    RV_IT_SHADD_R,
    RV_IT_XPERM_R,

    // B-extension I-type instructions
    RV_IT_SLOI_I,
    RV_IT_SROI_I,
    RV_IT_RORI_I,
    RV_IT_SBCLRI_I,
    RV_IT_SBSETI_I,
    RV_IT_SBINVI_I,
    RV_IT_SBEXTI_I,
    RV_IT_GORCI_I,
    RV_IT_ORCB_I,
    RV_IT_ORC16_I,
    RV_IT_GREVI_I,
    RV_IT_REV8_I,
    RV_IT_REV_I,
    RV_IT_SHFLI_I,
    RV_IT_UNSHFLI_I,
    RV_IT_ADDIWU_I,
    RV_IT_SLLIU_W_I,

    // B-extension R4-type instructions
    RV_IT_CMIX_R4,
    RV_IT_CMOV_R4,
    RV_IT_FSL_R4,
    RV_IT_FSR_R4,

    // B-extension R3I-type instructions
    RV_IT_FSRI_R3I,

    // H-extension R-type instructions for load
    RV_IT_HLV_R,

    // H-extension R-type instructions for load-as-if-execute
    RV_IT_HLVX_R,

    // H-extension S-type instructions for store
    RV_IT_HSV_R,

    // K-extension R-type LUT instructions
    RV_IT_LUT4LO_R,
    RV_IT_LUT4HI_R,
    RV_IT_LUT4_R,

    // K-extension R-type SAES32 instructions
    RV_IT_SAES32_ENCSM_R,
    RV_IT_SAES32_ENCS_R,
    RV_IT_SAES32_DECSM_R,
    RV_IT_SAES32_DECS_R,

    // K-extension R-type SSM3/SSM4 instructions
    RV_IT_SSM3_P0_R,
    RV_IT_SSM3_P1_R,
    RV_IT_SSM4_ED_R,
    RV_IT_SSM4_KS_R,

    // K-extension R-type SAES64 instructions
    RV_IT_SAES64_KS1_R,
    RV_IT_SAES64_KS2_R,
    RV_IT_SAES64_IMIX_R,
    RV_IT_SAES64_ENCSM_R,
    RV_IT_SAES64_ENCS_R,
    RV_IT_SAES64_DECSM_R,
    RV_IT_SAES64_DECS_R,

    // K-extension R-type SSHA256 instructions
    RV_IT_SSHA256_SIG0_R,
    RV_IT_SSHA256_SIG1_R,
    RV_IT_SSHA256_SUM0_R,
    RV_IT_SSHA256_SUM1_R,

    // K-extension R-type SSHA512 instructions
    RV_IT_SSHA512_SIG0L_R,
    RV_IT_SSHA512_SIG0H_R,
    RV_IT_SSHA512_SIG1L_R,
    RV_IT_SSHA512_SIG1H_R,
    RV_IT_SSHA512_SUM0R_R,
    RV_IT_SSHA512_SUM1R_R,
    RV_IT_SSHA512_SIG0_R,
    RV_IT_SSHA512_SIG1_R,
    RV_IT_SSHA512_SUM0_R,
    RV_IT_SSHA512_SUM1_R,

    // K-extension I-type POLLENTROPY instruction
    RV_IT_POLLENTROPY_I,

    // V-extension R-type instructions
    RV_IT_VSETVL_R,

    // V-extension I-type instructions
    RV_IT_VSETVL_I,

    // V-extension load/store instructions
    RV_IT_VL_I,
    RV_IT_VLS_I,
    RV_IT_VLX_I,
    RV_IT_VS_I,
    RV_IT_VSS_I,
    RV_IT_VSX_I,

    // V-extension AMO operations (Zvamo)
    RV_IT_VAMOADD_R,
    RV_IT_VAMOAND_R,
    RV_IT_VAMOMAX_R,
    RV_IT_VAMOMAXU_R,
    RV_IT_VAMOMIN_R,
    RV_IT_VAMOMINU_R,
    RV_IT_VAMOOR_R,
    RV_IT_VAMOSWAP_R,
    RV_IT_VAMOXOR_R,

    // V-extension IVV/IVX-type common instructions
    RV_IT_VMERGE_VR,
    RV_IT_VADD_VR,
    RV_IT_VSUB_VR,
    RV_IT_VRSUB_VR,
    RV_IT_VMINU_VR,
    RV_IT_VMIN_VR,
    RV_IT_VMAXU_VR,
    RV_IT_VMAX_VR,
    RV_IT_VAND_VR,
    RV_IT_VOR_VR,
    RV_IT_VXOR_VR,
    RV_IT_VADC_VR,
    RV_IT_VMADC_VR,
    RV_IT_VSBC_VR,
    RV_IT_VMSBC_VR,
    RV_IT_VSLL_VR,
    RV_IT_VSRL_VR,
    RV_IT_VSRA_VR,
    RV_IT_VNSRL_VR,
    RV_IT_VNSRA_VR,
    RV_IT_VSEQ_VR,
    RV_IT_VSNE_VR,
    RV_IT_VSLTU_VR,
    RV_IT_VSLT_VR,
    RV_IT_VSLEU_VR,
    RV_IT_VSLE_VR,
    RV_IT_VSGTU_VR,
    RV_IT_VSGT_VR,
    RV_IT_VRGATHER_VR,
    RV_IT_VSLIDEUP_VR,
    RV_IT_VSLIDEDOWN_VR,
    RV_IT_VSADDU_VR,
    RV_IT_VSADD_VR,
    RV_IT_VSSUBU_VR,
    RV_IT_VSSUB_VR,
    RV_IT_VAADDU_VR,
    RV_IT_VAADD_VR,
    RV_IT_VASUBU_VR,
    RV_IT_VASUB_VR,
    RV_IT_VSMUL_VR,
    RV_IT_VWSMACCU_VR,
    RV_IT_VWSMACC_VR,
    RV_IT_VWSMACCSU_VR,
    RV_IT_VWSMACCUS_VR,
    RV_IT_VSSRL_VR,
    RV_IT_VSSRA_VR,
    RV_IT_VNCLIPU_VR,
    RV_IT_VNCLIP_VR,

    // V-extension MVV/MVX-type common instructions
    RV_IT_VDIVU_VR,
    RV_IT_VDIV_VR,
    RV_IT_VREMU_VR,
    RV_IT_VREM_VR,
    RV_IT_VMUL_VR,
    RV_IT_VMULHU_VR,
    RV_IT_VMULHSU_VR,
    RV_IT_VMULH_VR,
    RV_IT_VWMULU_VR,
    RV_IT_VWMULSU_VR,
    RV_IT_VWMUL_VR,
    RV_IT_VWADDU_VR,
    RV_IT_VWADD_VR,
    RV_IT_VWSUBU_VR,
    RV_IT_VWSUB_VR,
    RV_IT_VWADDU_WR,
    RV_IT_VWADD_WR,
    RV_IT_VWSUBU_WR,
    RV_IT_VWSUB_WR,
    RV_IT_VMADD_VR,
    RV_IT_VNMSUB_VR,
    RV_IT_VMACC_VR,
    RV_IT_VNMSAC_VR,
    RV_IT_VWMACCU_VR,
    RV_IT_VWMACC_VR,
    RV_IT_VWMACCSU_VR,
    RV_IT_VWMACCUS_VR,
    RV_IT_VQMACCU_VR,
    RV_IT_VQMACC_VR,
    RV_IT_VQMACCSU_VR,
    RV_IT_VQMACCUS_VR,

    // V-extension IVV-type instructions
    RV_IT_VWREDSUMU_VS,
    RV_IT_VWREDSUM_VS,
    RV_IT_VDOTU_VV,
    RV_IT_VDOT_VV,

    // V-extension FVV/FVF-type common instructions
    RV_IT_VFMERGE_VR,
    RV_IT_VFADD_VR,
    RV_IT_VFSUB_VR,
    RV_IT_VFRSUB_VR,
    RV_IT_VFMUL_VR,
    RV_IT_VFDIV_VR,
    RV_IT_VFRDIV_VR,
    RV_IT_VFWADD_VR,
    RV_IT_VFWSUB_VR,
    RV_IT_VFWADD_WR,
    RV_IT_VFWSUB_WR,
    RV_IT_VFWMUL_VR,
    RV_IT_VFMADD_VR,
    RV_IT_VFNMADD_VR,
    RV_IT_VFMSUB_VR,
    RV_IT_VFNMSUB_VR,
    RV_IT_VFMACC_VR,
    RV_IT_VFNMACC_VR,
    RV_IT_VFMSAC_VR,
    RV_IT_VFNMSAC_VR,
    RV_IT_VFWMACC_VR,
    RV_IT_VFWNMACC_VR,
    RV_IT_VFWMSAC_VR,
    RV_IT_VFWNMSAC_VR,
    RV_IT_VFMIN_VR,
    RV_IT_VFMAX_VR,
    RV_IT_VFSGNJ_VR,
    RV_IT_VFSGNJN_VR,
    RV_IT_VFSGNJX_VR,
    RV_IT_VFORD_VR,
    RV_IT_VFEQ_VR,
    RV_IT_VFNE_VR,
    RV_IT_VFLE_VR,
    RV_IT_VFLT_VR,
    RV_IT_VFGE_VR,
    RV_IT_VFGT_VR,

    // V-extension FVV-type instructions
    RV_IT_VFREDSUM_VS,
    RV_IT_VFREDOSUM_VS,
    RV_IT_VFREDMIN_VS,
    RV_IT_VFREDMAX_VS,
    RV_IT_VFMV_F_S,
    RV_IT_VFCVT_XUF_V,
    RV_IT_VFCVT_XF_V,
    RV_IT_VFCVT_FXU_V,
    RV_IT_VFCVT_FX_V,
    RV_IT_VFWCVT_XUF_V,
    RV_IT_VFWCVT_XF_V,
    RV_IT_VFWCVT_FXU_V,
    RV_IT_VFWCVT_FX_V,
    RV_IT_VFWCVT_FF_V,
    RV_IT_VFNCVT_XUF_V,
    RV_IT_VFNCVT_XF_V,
    RV_IT_VFNCVT_FXU_V,
    RV_IT_VFNCVT_FX_V,
    RV_IT_VFNCVT_FF_V,
    RV_IT_VFSQRT_V,
    RV_IT_VFRSQRTE7_V,
    RV_IT_VFRECE7_V,
    RV_IT_VFCLASS_V,
    RV_IT_VFWREDSUM_VS,
    RV_IT_VFWREDOSUM_VS,
    RV_IT_VFDOT_VV,

    // V-extension MVV-type instructions
    RV_IT_VREDSUM_VS,
    RV_IT_VREDAND_VS,
    RV_IT_VREDOR_VS,
    RV_IT_VREDXOR_VS,
    RV_IT_VREDMINU_VS,
    RV_IT_VREDMIN_VS,
    RV_IT_VREDMAXU_VS,
    RV_IT_VREDMAX_VS,
    RV_IT_VEXT_X_V,
    RV_IT_VPOPC_M,
    RV_IT_VFIRST_M,
    RV_IT_VMSBF_M,
    RV_IT_VMSOF_M,
    RV_IT_VMSIF_M,
    RV_IT_VIOTA_M,
    RV_IT_VID_V,
    RV_IT_VCOMPRESS_VM,
    RV_IT_VMANDNOT_MM,
    RV_IT_VMAND_MM,
    RV_IT_VMOR_MM,
    RV_IT_VMXOR_MM,
    RV_IT_VMORNOT_MM,
    RV_IT_VMNAND_MM,
    RV_IT_VMNOR_MM,
    RV_IT_VMXNOR_MM,

    // V-extension IVI-type instructions
    RV_IT_VADD_VI,
    RV_IT_VRSUB_VI,
    RV_IT_VAND_VI,
    RV_IT_VOR_VI,
    RV_IT_VXOR_VI,
    RV_IT_VRGATHER_VI,
    RV_IT_VSLIDEUP_VI,
    RV_IT_VSLIDEDOWN_VI,
    RV_IT_VADC_VI,
    RV_IT_VMADC_VI,
    RV_IT_VMERGE_VI,
    RV_IT_VSEQ_VI,
    RV_IT_VSNE_VI,
    RV_IT_VSLEU_VI,
    RV_IT_VSLE_VI,
    RV_IT_VSGTU_VI,
    RV_IT_VSGT_VI,
    RV_IT_VSADDU_VI,
    RV_IT_VSADD_VI,
    RV_IT_VAADD_VI,
    RV_IT_VSLL_VI,
    RV_IT_VMVR_VI,
    RV_IT_VSRL_VI,
    RV_IT_VSRA_VI,
    RV_IT_VSSRL_VI,
    RV_IT_VSSRA_VI,
    RV_IT_VNSRL_VI,
    RV_IT_VNSRA_VI,
    RV_IT_VNCLIPU_VI,
    RV_IT_VNCLIP_VI,

    // V-extension FVF-type instructions
    RV_IT_VFMV_S_F,
    RV_IT_VFSLIDE1UP_VF,
    RV_IT_VFSLIDE1DOWN_VF,

    // V-extension MVX-type instructions
    RV_IT_VMV_S_X,
    RV_IT_VSLIDE1UP_VX,
    RV_IT_VSLIDE1DOWN_VX,
    RV_IT_VZEXT_V,
    RV_IT_VSEXT_V,

    // KEEP LAST
    RV_IT_LAST

} riscvIType;

//
// This is used to categorize acquire/release semantics
//
typedef enum riscvAQRLDescE {

    RV_AQRL_NA,     // no acquire/release specification
    RV_AQRL_RL,     // release
    RV_AQRL_AQ,     // acquire
    RV_AQRL_AQRL,   // acquire and release

} riscvAQRLDesc;

//
// This is used to categorize fence semantics
//
typedef enum riscvFenceDescE {

    RV_FENCE_NA   = 0x0,    // no fence
    RV_FENCE_W    = 0x1,    // write fence
    RV_FENCE_R    = 0x2,    // read fence
    RV_FENCE_O    = 0x4,    // output fence
    RV_FENCE_I    = 0x8,    // input fence
    RV_FENCE_IOWR = RV_FENCE_I|RV_FENCE_O|RV_FENCE_R|RV_FENCE_W

} riscvFenceDesc;

//
// This is used to categorize CSR update semantics
//
typedef enum riscvCSRUDescE {

    RV_CSR_NA,      // no update semantics
    RV_CSR_RW,      // read/write
    RV_CSR_RS,      // read/set
    RV_CSR_RC,      // read/clear

} riscvCSRUDesc;

//
// This is used to categorize vector instructions
//
typedef enum riscvVITypeE {

    RV_VIT_NA,      // not a vector instruction
    RV_VIT_V,       // instruction type .v
    RV_VIT_W,       // instruction type .w
    RV_VIT_VV,      // instruction type .vv
    RV_VIT_VI,      // instruction type .vi
    RV_VIT_VX,      // instruction type .vx
    RV_VIT_WV,      // instruction type .wv
    RV_VIT_WI,      // instruction type .wi
    RV_VIT_WX,      // instruction type .wx
    RV_VIT_VF,      // instruction type .vf
    RV_VIT_WF,      // instruction type .wf
    RV_VIT_VS,      // instruction type .vs
    RV_VIT_M,       // instruction type .m
    RV_VIT_MM,      // instruction type .mm
    RV_VIT_VM,      // instruction type .vm
    RV_VIT_VVM,     // instruction type .vvm
    RV_VIT_VXM,     // instruction type .vxm
    RV_VIT_VIM,     // instruction type .vim
    RV_VIT_VFM,     // instruction type .vfm
    RV_VIT_VN,      // instruction type .v/.w (version-dependent)
    RV_VIT_VVN,     // instruction type .vv/.wv (version-dependent)
    RV_VIT_VIN,     // instruction type .vi/.wi (version-dependent)
    RV_VIT_VXN,     // instruction type .vx/.wx (version-dependent)
    RV_VIT_V_V,     // instruction type .v.v
    RV_VIT_LAST     // KEEP LAST: for sizing

} riscvVIType;

//
// This is used to categorize CSR update semantics
//
typedef enum riscvWholeDescE {

    RV_WD_NA,       // not a whole register instruction
    RV_WD_LD_ST,    // whole register load/store
    RV_WD_MV,       // whole register move

} riscvWholeDesc;

//
// This defines the maximum number of argument registers
//
#define RV_MAX_AREGS 4

//
// This structure is filled with information extracted from the decoded
// instruction
//
typedef struct riscvInstrInfoS {

    const char       *opcode;           // opcode name
    const char       *format;           // disassembly format string
    riscvAddr         thisPC;           // instruction address
    Uns32             instruction;      // instruction word
    Uns8              bytes;            // instruction size in bytes (2 or 4)
    riscvIType        type;             // instruction type
    riscvArchitecture arch;             // architecture requirements
    riscvVIType       VIType;           // vector instruction type
    Int32             memBits;          // load/store size
    Uns32             eew;              // explicit EEW encoding
    Uns64             c;                // constant value
    riscvRegDesc      r[RV_MAX_AREGS];  // argument registers
    riscvRegDesc      mask;             // mask register
    riscvAQRLDesc     aqrl;             // acquire/release specifier
    riscvFenceDesc    pred;             // predecessor fence
    riscvFenceDesc    succ;             // successor fence
    riscvRMDesc       rm;               // rounding mode
    riscvCSRUDesc     csrUpdate;        // CSR update semantics
    riscvWholeDesc    isWhole;          // is this a whole-register instruction?
    riscvVType        vtype;            // vector type information
    Uns32             csr;              // CSR index
    Uns8              nf;               // nf value
    Uns8              eewDiv;           // explicit EEW divisor
    Uns8              shN;              // shN prefix
    Uns8              explicitType;     // whether types are explicit in opcode
    Bool              explicitW;        // whether 'w' explicit in opcode
    Bool              explicitRM;       // whether rounding explicit in opcode
    Bool              unsExt;           // whether to extend unsigned
    Bool              csrInOp;          // whether to emit CSR as part of opcode
    Bool              isFF;             // is this a first-fault instruction?

} riscvInstrInfo;

