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

// prefix for messages from this extension
#define CPU_PREFIX "OPENHW"

// VMI area includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"

// base model header files
#include "riscvMessage.h"
#include "riscvStructure.h"
#include "riscvMode.h"

////////////////////////////////////////////////////////////////////////////////
// EXTENSION CSR IDENTIFIERS
////////////////////////////////////////////////////////////////////////////////

typedef enum extCSRIdE {

    // Machine mode CSRs
    XCSR_ID (mtval),        // 0x343
    XCSR_ID (mcycle),       // 0xB00
    XCSR_ID (minstret),     // 0xB02
    XCSR_ID (mcycleh),      // 0xB80
    XCSR_ID (minstreth),    // 0xB82

    // User mode CSRs
    XCSR_ID (cycle),        // 0xC00
    XCSR_ID (instret),      // 0xC02
    XCSR_ID (cycleh),       // 0xC80
    XCSR_ID (instreth),     // 0xC82

    // keep last (used to define size of the enumeration)
    XCSR_ID (LAST)

} extCSRId;

////////////////////////////////////////////////////////////////////////////////
// EXTENSION OBJECT
////////////////////////////////////////////////////////////////////////////////

typedef struct vmiosObjectS {

    // Info for associated processor
    riscvP     riscv;

    // extension CSR info
    riscvCSRAttrs csrs[XCSR_ID(LAST)];   // extension CSR definitions

    // extension callbacks
    riscvExtCB extCB;

    // Debug
    Uns32 diagnostic;

} vmiosObject;

////////////////////////////////////////////////////////////////////////////////
// EXTENSION PARAMETERS
////////////////////////////////////////////////////////////////////////////////

typedef struct paramValuesS {

    VMI_BOOL_PARAM(debug);

} paramValues, *paramValuesP;


////////////////////////////////////////////////////////////////////////////////
// RESET NOTIFIER
////////////////////////////////////////////////////////////////////////////////

//
// Reset implementation-specific CSRs
//
static RISCV_RESET_NOTIFIER_FN(CSRReset) {

    riscv->cb.writeBaseCSR(riscv, CSR_ID(mcountinhibit), 0xd);

    // tdata1 initialization
    // https://core-v-docs-verif-strat.readthedocs.io/projects/cv32e40p_um/en/latest/control_status_registers.html
    //
    riscvTriggerP trigger = riscv->triggers;

    // initialise read-only fields
    trigger->tdata1UP.type   = 2;       // Address/Data match trigger
    trigger->tdata1UP.dmode  = 1;       // Only debug mode can write tdata registers
    trigger->tdata1UP.action = 1;       // Enter debug mode on match
    trigger->tdata1UP.modes  = 1<<3;    // Match in M-Mode

    // apply tdata1 reset
    riscv->cb.writeBaseCSR(riscv, CSR_ID(tdata1), 0x0);
}

////////////////////////////////////////////////////////////////////////////////
// EXTENSION CSRS
////////////////////////////////////////////////////////////////////////////////

static RISCV_CSR_READFN(illegalR) {

    if(!riscv->artifactAccess) {
        riscv->cb.illegalInstruction(riscv);
    }

    return 0;
}

static RISCV_CSR_WRITEFN(illegalW) {

    if(!riscv->artifactAccess) {
        riscv->cb.illegalInstruction(riscv);
    }

    return 0;
}

//
// CSR table
//
static const extCSRAttrs csrs[XCSR_ID(LAST)] = {

    //            name           num    arch         extension attrs    description                          rCB       rwCB wCB

    // Machine Model CSRs
    XCSR_ATTR_P__(mtval,         0x343, 0,           0,        0,0,0,0, "Machine Trap Value",                0,        0,   0),

    XCSR_ATTR_P__(mcycle,        0xB00, 0,           0,        0,0,0,0, "Machine Cycle Counter",             0,        0,   0),
    XCSR_ATTR_P__(minstret,      0xB02, 0,           0,        0,0,0,0, "Machine Instructions Retired",      0,        0,   0),
    XCSR_ATTR_P__(mcycleh,       0xB80, ISA_XLEN_32, 0,        0,0,0,0, "Machine Cycle Counter High",        0,        0,   0),
    XCSR_ATTR_P__(minstreth,     0xB82, ISA_XLEN_32, 0,        0,0,0,0, "Machine Instructions Retired High", 0,        0,   0),

    // User Model CSRs
    XCSR_ATTR_P__(cycle,         0xC00, 0,           0,        0,0,0,0, "User Cycle Counter",                illegalR, 0,   illegalW),
    XCSR_ATTR_P__(instret,       0xC02, 0,           0,        0,0,0,0, "User Instructions Retired",         illegalR, 0,   illegalW),
    XCSR_ATTR_P__(cycleh,        0xC80, ISA_XLEN_32, 0,        0,0,0,0, "User Cycle Counter High",           illegalR, 0,   illegalW),
    XCSR_ATTR_P__(instreth,      0xC82, ISA_XLEN_32, 0,        0,0,0,0, "User Instructions Retired High",    illegalR, 0,   illegalW),

};

//
// Initialize CSR registers
//
static void addCSRsCSRInit(vmiosObjectP object) {

    riscvP   riscv = object->riscv;
    extCSRId id;

    // register each CSR with the base model using the newCSR interface function
    for(id=0; id<XCSR_ID(LAST); id++) {

        extCSRAttrsCP  src = &csrs[id];
        riscvCSRAttrs *dst = &object->csrs[id];

        riscv->cb.newCSR(dst, &src->baseAttrs, riscv, object);
    }

    //
    // DCSR
    //
    // mask out unimplemented bits in dcsr
    riscv->csrMask.dcsr.u32.fields.stopcount = 0;
    riscv->csrMask.dcsr.u32.fields.stoptime  = 0;
    riscv->csrMask.dcsr.u32.fields.mprven    = 0;
    riscv->csrMask.dcsr.u32.fields.nmip      = 0;

    // mask out readonly bits in dcsr
    riscv->csrMask.dcsr.u32.fields.cause     = 0;
    riscv->csrMask.dcsr.u32.fields.prv       = 0; // Changed in RTL from RW->RO

    // debug ver 4
    riscv->csr.dcsr.u32.fields.xdebugver     = 4;
}


////////////////////////////////////////////////////////////////////////////////
// INTERCEPT PARAMETERS
////////////////////////////////////////////////////////////////////////////////

//
// Define formals
//
static vmiParameter formals[] = {
    VMI_BOOL_PARAM_SPEC(paramValues,debug,0,0),
    VMI_END_PARAM
};

//
// Iterate formals
//
static VMIOS_PARAM_SPEC_FN(getParamSpecs) {
    if(!prev) {
        return formals;
    } else {
        prev++;
        if (prev->name) {
            return prev;
        } else {
            return 0;
        }
    }
}

//
// Return size of parameter structure
//
static VMIOS_PARAM_TABLE_SIZE_FN(getParamTableSize) {
    return sizeof(paramValues);
}


////////////////////////////////////////////////////////////////////////////////
// EXTENSION CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(extensionConstructor) {

    riscvP riscv = (riscvP)processor;

    paramValuesP params = parameterValues;
    if(params->debug) {
        object->diagnostic = 1;
    }

    object->riscv = riscv;

    // prepare client data
    object->extCB.clientData    = object;
    object->extCB.resetNotifier = CSRReset;

    // register extension with base model using unique ID
    riscv->cb.registerExtCB(riscv, &object->extCB, 0);

    // initialize CSRs
    addCSRsCSRInit(object);

    // perform initial CSR reset
    CSRReset(riscv, object);
}


////////////////////////////////////////////////////////////////////////////////
// EXTENSION ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString = VMI_VERSION,           // version string
    .modelType     = VMI_INTERCEPT_LIBRARY, // type
    .packageName   = "OpenHW",              // description
    .objectSize    = sizeof(vmiosObject),   // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB = extensionConstructor,  // object constructor

    ////////////////////////////////////////////////////////////////////////
    // PARAMETER CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    .paramSpecsCB     = getParamSpecs,          // iterate parameter declarations
    .paramValueSizeCB = getParamTableSize,      // get parameter table size

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts    = {{0}}
};

