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


// VMI header files
#include "vmi/vmiMessage.h"
#include "vmi/vmiMt.h"
#include "vmi/vmiRt.h"

// model header files
#include "or1kDecode.h"
#include "or1kFunctions.h"
#include "or1kStructure.h"

//
// Define pointer to or1kMorphAttr type
//
typedef const struct or1kMorphAttrS *or1kMorphAttrCP;

//
// Define pointer to or1kMorphState type
//
typedef struct or1kMorphStateS *or1kMorphStateP;

//
// Morpher callback type
//
#define OR1K_MORPH_FN(_NAME) void _NAME(or1kMorphStateP state)
typedef OR1K_MORPH_FN((*or1kMorphFn));

//
// This structure provides supplementary information required to translate code
// for an instruction
//
typedef struct or1kMorphAttrS {
    or1kMorphFn morphCB;    // function to translate one instruction
} or1kMorphAttr;

//
// This structure holds state for a single instruction as it is translated
//
typedef struct or1kMorphStateS {
    or1kInstructionInfo info;        // instruction description (from decoder)
    or1kMorphAttrCP     attrs;       // instruction attributes
    or1kP               or1k;        // current processor
} or1kMorphState;

//
// Emit code for a OR1K nop instruction
//
static OR1K_MORPH_FN(morphNOP) {
    // no action for a NOP
}

////////////////////////////////////////////////////////////////////////////////
// MORPHER DISPATCH TABLE
////////////////////////////////////////////////////////////////////////////////

//
// OR1K morpher dispatch table
//
const or1kMorphAttr or1kMorphTable[OR1K_IT_LAST+1] = {

    // handle arithmetic instructions (second argument constant)
    [OR1K_IT_ADDI]  = {morphCB:morphNOP},
    [OR1K_IT_ADDIC] = {morphCB:morphNOP},
    [OR1K_IT_ANDI]  = {morphCB:morphNOP},
    [OR1K_IT_ORI]   = {morphCB:morphNOP},
    [OR1K_IT_XORI]  = {morphCB:morphNOP},
    [OR1K_IT_MULI]  = {morphCB:morphNOP},
};

//
// Called for an unimplemented instruction
//
static void unimplemented(
    vmiProcessorP processor,
    Uns32         thisPC,
    Uns32         instruction
) {
    // report that unimplemented instruction was encountered
    vmiPrintf(
        "CPU '%s' 0x%08x:0x%08x *** undecoded instruction: exiting ***\n",
        vmirtProcessorName(processor),
        thisPC,
        instruction
    );

    // exit the CPU
    vmirtExit(processor);
}

//
// Default morpher callback
//
static OR1K_MORPH_FN(emitUnimplemented) {

    vmimtArgProcessor();
    vmimtArgUns32((Uns32)state->info.thisPC);
    vmimtArgUns32(state->info.instruction);
    vmimtCall((vmiCallFn)unimplemented);
}

//
// Create code for the OR1K instruction at the simulated address referenced
// by 'thisPC'.
//
VMI_MORPH_FN(or1kMorphInstruction) {

    or1kP          or1k  = (or1kP)processor;
    or1kMorphState state = {{0}};

    // decode instruction
    or1kDecode(or1k, thisPC, &state.info);

    // get morpher attributes for the decoded instruction and initialize other
    // state fields
    state.attrs = &or1kMorphTable[state.info.type];
    state.or1k  = or1k;

    if(state.attrs->morphCB) {
        // translate the instruction
        state.attrs->morphCB(&state);
    } else {
        // here if no translation callback specified
        emitUnimplemented(&state);
    }
}

