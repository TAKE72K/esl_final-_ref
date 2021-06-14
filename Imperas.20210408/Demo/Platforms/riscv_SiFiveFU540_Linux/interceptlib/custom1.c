/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */

// standard includes
#include <stdio.h>

// VMI area includes
#include "vmi/vmiCxt.h"
#include "vmi/vmiDbg.h"
#include "vmi/vmiDecode.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiMt.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiDoc.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiVersion.h"

#define CPU_PREFIX "custom1"

// Four Chacha20 acceleration instructions (one for each rotate distance) are added to encode the
// XOR and ROTATE parts of the quarter rounds.
// •   QR1: dst = (src1 ^ src2) <<< 16
// •   QR2: dst = (src1 ^ src2) <<< 12
// •   QR3: dst = (src1 ^ src2) <<< 8
// •   QR4: dst = (src1 ^ src2) <<< 7
//
// opcode [6:0] = 00 010 11
// func3[14:12] = 1,2,3,4 (QR1-4)
//

#define RISCV_GPR_NUM    32
#define RISCV_INSTR_BITS 32
#define RISCV_REG_BITS   64

//
// Field extraction macros
//
#define WIDTH(_W, _ARG) ((_ARG) & ((1<<(_W))-1))
#define RD(_I)     WIDTH(5,(_I)>>7)
#define RS1(_I)    WIDTH(5,(_I)>>15)
#define RS2(_I)    WIDTH(5,(_I)>>20)

////////////////////////////////////////////////////////////////////////////////
// TYPES
////////////////////////////////////////////////////////////////////////////////

typedef struct vmiosObjectS {

    // handles for the RISCV GPRs
    vmiRegInfoCP riscvRegs[RISCV_GPR_NUM];

    // 32-bit temporaries
    Uns64 rs1, rs2, tmp;

    // enhanced instruction decode table
    vmidDecodeTableP table;

} vmiosObject;


////////////////////////////////////////////////////////////////////////////////
// ENHANCED DECODER
////////////////////////////////////////////////////////////////////////////////

//
// This macro adds a decode table entry for a specific instruction class
//
#define DECODE_ENTRY(_PRIORITY, _NAME, _FMT) \
    vmidNewEntryFmtBin(     \
        table,              \
        #_NAME,             \
        RISCV_EIT_##_NAME,   \
        _FMT,               \
        _PRIORITY           \
    )

//
// Enhanced nstruction type enumeration
//
typedef enum riscvEnhancedInstrTypeE {

    // custom instruction
    RISCV_EIT_CHACHA20QR1,
    RISCV_EIT_CHACHA20QR2,
    RISCV_EIT_CHACHA20QR3,
    RISCV_EIT_CHACHA20QR4,

    // KEEP LAST: for sizing the array
    RISCV_EIT_LAST

} riscvEnhancedInstrType;

//
// Create the RISCV decode table
//
static vmidDecodeTableP createDecodeTable(void) {

    vmidDecodeTableP table = vmidNewDecodeTable(RISCV_INSTR_BITS, RISCV_EIT_LAST);

    // R-Type instruction in custom-0 encoding space:
    // opcode [6:0]  = 00 010 11
    // funct3[14:12] = 0,1,2,3 (QR1-4)
    // funct7[31:25] = 0000000
    // rs1[19:15]
    // rs2[24:20]
    // rd[11:7]

    // handle custom instruction
    DECODE_ENTRY(0, CHACHA20QR1, "|0000000..........000.....0001011|");
    DECODE_ENTRY(0, CHACHA20QR2, "|0000000..........001.....0001011|");
    DECODE_ENTRY(0, CHACHA20QR3, "|0000000..........010.....0001011|");
    DECODE_ENTRY(0, CHACHA20QR4, "|0000000..........011.....0001011|");

    return table;
}

//
// Decode an extended instruction at the indicated address, or return
// RISCV_EIT_LAST if this is not an extended instruction.
// If an extended instruction, return the opcode in the byref instruction argument.
// Note: Do not fetch 4 bytes if this is a 2 byte instruction to avoid a fetch
//       error when there is a 2 byte instruction at the end of a memory region
//
static riscvEnhancedInstrType getInstrType(
    vmiosObjectP  object,
    vmiProcessorP processor,
    Addr          thisPC,
    Uns32         *instruction
) {

    riscvEnhancedInstrType type  = RISCV_EIT_LAST;
    Uns32                  bytes = vmirtInstructionBytes(processor, thisPC);

    if (bytes == 4) {
        *instruction = vmicxtFetch4Byte(processor, thisPC);
        type = vmidDecode(object->table, *instruction);
    }

    return type;
}

static const char *map[32] = {
    [0]  = "zero",
    [1]  = "ra",
    [2]  = "sp",
    [3]  = "gp",
    [4]  = "tp",
    [5]  = "t0",
    [6]  = "t1",
    [7]  = "t2",
    [8]  = "s0",
    [9]  = "s1",
    [10] = "a0",
    [11] = "a1",
    [12] = "a2",
    [13] = "a3",
    [14] = "a4",
    [15] = "a5",
    [16] = "a6",
    [17] = "a7",
    [18] = "s2",
    [19] = "s3",
    [20] = "s4",
    [21] = "s5",
    [22] = "s6",
    [23] = "s7",
    [24] = "s8",
    [25] = "s9",
    [26] = "s10",
    [27] = "s11",
    [28] = "t3",
    [29] = "t4",
    [30] = "t5",
    [31] = "t6",
};

////////////////////////////////////////////////////////////////////////////////
// DOCUMENTATION
////////////////////////////////////////////////////////////////////////////////

//
// Add documentation for ChaCha20 instructions
//
static void docChaCha20(
    vmiDocNodeP insts,
    const char *opcode,
    const char *decode,
    const char *desc
) {
    vmiDocNodeP inst = vmidocAddFields(insts, opcode, 32);

    // fields
    vmidocAddField(inst, "Custom0 0001011",     0, 7);
    vmidocAddField(inst, "Rd",                  7, 5);
    vmidocAddField(inst, decode,               12, 3);
    vmidocAddField(inst, "Rs1",                15, 5);
    vmidocAddField(inst, "Rs2",                20, 5);
    vmidocAddField(inst, "0000000",            25, 7);

    // description
    vmidocAddText(inst, desc);
}

//
// Add documentation for Custom instructions
//
VMIOS_DOC_FN(extensionDoc) {

    vmiDocNodeP custom = vmidocAddSection(0, "Instruction Extensions");

    // description
    vmidocAddText(
        custom,
        "RISCV processors may add various custom extensions to the basic "
        "RISC-V architecture. "
        "This processor has been extended, using an extension library, "
        "to add several instruction using the Custom0 opcode."
    );
    vmiDocNodeP insts = vmidocAddSection(
        custom, "Custom Instructions"
    );

    vmidocAddText(
        insts,
        "This model includes Four Chacha20 acceleration instructions "
        "(one for each rotate distance) are added to encode the XOR "
        "and ROTATE parts of the quarter rounds.");

    docChaCha20(insts, "chacha20qr1", "000 (QR1)", "dst = (src1 ^ src2) <<< 16");
    docChaCha20(insts, "chacha20qr2", "001 (QR2)", "dst = (src1 ^ src2) <<< 12");
    docChaCha20(insts, "chacha20qr3", "010 (QR3)", "dst = (src1 ^ src2) <<<  8");
    docChaCha20(insts, "chacha20qr4", "011 (QR4)", "dst = (src1 ^ src2) <<<  7");

    vmidocProcessor(processor, custom);
}

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(constructor) {

    Uns32 i;

    // get handles to the RISCV GPRs
    for(i=0; i<RISCV_GPR_NUM; i++) {
        object->riscvRegs[i] = vmiosGetRegDesc(processor, map[i]);
    }

    // create enhanced instruction decoder
    object->table = createDecodeTable();

}

////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION OF ENHANCED EXCHANGE INSTRUCTION
////////////////////////////////////////////////////////////////////////////////

//
// Emit code implementing exchange instruction
//
static void emitChaCha20(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Uns32         instruction,
    Uns32         rotl
) {

    // extract instruction fields
    Uns32 rd  = RD(instruction);
    Uns32 rs1 = RS1(instruction);
    Uns32 rs2 = RS2(instruction);

    vmiReg reg_rs1 = vmimtGetExtReg(processor,  &object->rs1);
    vmiReg reg_rs2 = vmimtGetExtReg(processor,  &object->rs2);
    vmiReg reg_tmp = vmimtGetExtTemp(processor, &object->tmp);

    vmimtGetR(processor, RISCV_REG_BITS, reg_rs1, object->riscvRegs[rs1]);
    vmimtGetR(processor, RISCV_REG_BITS, reg_rs2, object->riscvRegs[rs2]);
    vmimtBinopRRR(32, vmi_XOR, reg_tmp, reg_rs1, reg_rs2, 0);
    vmimtBinopRC(32, vmi_ROL, reg_tmp, rotl, 0);

    vmimtSetR(processor, RISCV_REG_BITS, object->riscvRegs[rd], reg_tmp);
}

//
// Morpher callback implementing ChaCha20 instructions
//
static VMIOS_MORPH_FN(doMorph) {

    // decode the instruction to get the type
    Uns32 instruction;
    riscvEnhancedInstrType type = getInstrType(object, processor, thisPC, &instruction);

    *opaque = True;
    if(type==RISCV_EIT_CHACHA20QR1) {
        emitChaCha20(processor, object, instruction, 16);

    } else if (type==RISCV_EIT_CHACHA20QR2) {
        emitChaCha20(processor, object, instruction, 12);

    } else if (type==RISCV_EIT_CHACHA20QR3) {
        emitChaCha20(processor, object, instruction, 8);

    } else if (type==RISCV_EIT_CHACHA20QR4) {
        emitChaCha20(processor, object, instruction, 7);

    } else {
        *opaque = False;
    }

    // no intercept callback specified
    return 0;
}

//
// Disassembler callback disassembling ChaCha20 instructions
//
static VMIOS_DISASSEMBLE_FN(doDisass) {

    // decode the instruction to get the type
    Uns32                  instruction = vmicxtFetch4Byte(processor, thisPC);
    riscvEnhancedInstrType type        = vmidDecode(object->table, instruction);

    if (type != RISCV_EIT_LAST) {
        static char buffer[256];

        // extract instruction fields
        Uns32 rd  = RD(instruction);
        Uns32 rs1 = RS1(instruction);
        Uns32 rs2 = RS2(instruction);

        if(type==RISCV_EIT_CHACHA20QR1) {
            sprintf(buffer, "%-8s %s,%s,%s", "chacha20qr1", map[rd], map[rs1], map[rs2]);
            return buffer;

        } else if (type==RISCV_EIT_CHACHA20QR2) {
            sprintf(buffer, "%-8s %s,%s,%s", "chacha20qr2", map[rd], map[rs1], map[rs2]);
            return buffer;

        } else if (type==RISCV_EIT_CHACHA20QR3) {
            sprintf(buffer, "%-8s %s,%s,%s", "chacha20qr3", map[rd], map[rs1], map[rs2]);
            return buffer;

        } else if (type==RISCV_EIT_CHACHA20QR4) {
            sprintf(buffer, "%-8s %s,%s,%s", "chacha20qr4", map[rd], map[rs1], map[rs2]);
            return buffer;

        } else {
            VMI_ABORT("Invalid decode");
        }
    }

    // instruction not enhanced ChaCha20
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// INTERCEPT ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString = VMI_VERSION,           // version string
    .modelType     = VMI_INTERCEPT_LIBRARY, // type
    .packageName   = "ChaCha20",            // description
    .objectSize    = sizeof(vmiosObject),   // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB = constructor,           // object constructor
    .docCB         = extensionDoc,          // doc constructor

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB       = doMorph,               // instruction morph callback
    .disCB         = doDisass,              // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts    = {{0}}
};

