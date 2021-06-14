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

#include <stdio.h>

// Imperas header files
#include "hostapi/impAlloc.h"

// VMI header files
#include "vmi/vmiAttrs.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiTypes.h"

// model header files
#include "or1kExceptions.h"
#include "or1kStructure.h"
#include "or1kFunctions.h"
#include "or1kView.h"
#include "or1kParameters.h"

//
// Return number of members of an array
//
#define NUM_MEMBERS(_A) (sizeof(_A)/sizeof((_A)[0]))


////////////////////////////////////////////////////////////////////////////////
// NET PORTS
////////////////////////////////////////////////////////////////////////////////

//
// Template net port list
//
const static vmiNetPort netPorts[] = {
    {"reset", vmi_NP_INPUT, (void*)0,   or1kExternalReset    },
    {"intr0", vmi_NP_INPUT, (void*)1,   or1kExternalInterrupt},
    {"intr1", vmi_NP_INPUT, (void*)2,   or1kExternalInterrupt},
    {"intr2", vmi_NP_INPUT, (void*)4,   or1kExternalInterrupt},
    {"intr3", vmi_NP_INPUT, (void*)8,   or1kExternalInterrupt},
    {"intr4", vmi_NP_INPUT, (void*)16,  or1kExternalInterrupt},
    {"intr5", vmi_NP_INPUT, (void*)32,  or1kExternalInterrupt},
    {"intr6", vmi_NP_INPUT, (void*)64,  or1kExternalInterrupt},
    {"intr7", vmi_NP_INPUT, (void*)128, or1kExternalInterrupt},
};

//
// Get the number of processor net ports (reset port plus external
// interrupts)
//
static Uns32 getNumNetPorts(or1kP or1k) {
    return 1 + or1k->numExtInts;
}

//
// Allocate net port specifications
//
static void newNetPorts(or1kP or1k) {

    Uns32 numNetPorts = getNumNetPorts(or1k);
    Uns32 i;

    or1k->netPorts = STYPE_CALLOC_N(vmiNetPort, numNetPorts);

    for(i=0; i<numNetPorts; i++) {
        or1k->netPorts[i] = netPorts[i];
    }
}

//
// Free net port specifications
//
static void freeNetPorts(or1kP or1k) {

    if(or1k->netPorts) {
        STYPE_FREE(or1k->netPorts);
        or1k->netPorts = 0;
    }
}

//
// Get the next net port
//
VMI_NET_PORT_SPECS_FN(or1kGetNetPortSpec) {

    or1kP or1k = (or1kP)processor;

    if(!prev) {

        // first port
        return or1k->netPorts;

    } else {

        // port other than the first
        Uns32 numNetPorts = getNumNetPorts(or1k);
        Uns32 prevIndex   = (prev-or1k->netPorts);
        Uns32 thisIndex   = prevIndex+1;

        return (thisIndex<numNetPorts) ? &or1k->netPorts[thisIndex] : 0;
    }
}


////////////////////////////////////////////////////////////////////////////////
// BUS PORTS
////////////////////////////////////////////////////////////////////////////////

//
// Template bus port list
//
const static vmiBusPort busPorts[] = {
    {"INSTRUCTION", vmi_BP_MASTER, vmi_DOM_CODE, {32,32}, 1},
    {"DATA"       , vmi_BP_MASTER, vmi_DOM_DATA, {32,32}, 0},
};

//
// Allocate bus port specifications
//
static void newBusPorts(or1kP or1k) {

    Uns32 i;

    or1k->busPorts = STYPE_CALLOC_N(vmiBusPort, NUM_MEMBERS(busPorts));

    for(i=0; i<NUM_MEMBERS(busPorts); i++) {
        or1k->busPorts[i] = busPorts[i];
    }
}

//
// Free bus port specifications
//
static void freeBusPorts(or1kP or1k) {

    if(or1k->busPorts) {
        STYPE_FREE(or1k->busPorts);
        or1k->busPorts = 0;
    }
}

//
// Get the next bus port
//
VMI_BUS_PORT_SPECS_FN(or1kGetBusPortSpec) {

    or1kP or1k = (or1kP)processor;

    if(!prev) {

        // first port
        return or1k->busPorts;

    } else {

        // port other than the first
        Uns32 prevIndex = (prev-or1k->busPorts);
        Uns32 thisIndex = prevIndex+1;

        return (thisIndex<NUM_MEMBERS(busPorts)) ? &or1k->busPorts[thisIndex] : 0;
    }
}


////////////////////////////////////////////////////////////////////////////////
// SAVE/RESTORE INTERFACE
////////////////////////////////////////////////////////////////////////////////

//
// OR1K processor state save
//
VMI_SAVE_STATE_FN(or1kSaveStateCB) {

    or1kP or1k = (or1kP)processor;

    switch(phase) {

        case SRT_BEGIN:
            // start of save/restore process
            or1k->inSaveRestore = True;
            break;

        case SRT_BEGIN_CORE:
            // start of individual core
            break;

        case SRT_END_CORE:
            // end of individual core: save fields not covered by debug register
            // interface
            VMIRT_SAVE_FIELD(cxt, or1k, TTCRSetCount);
            VMIRT_SAVE_FIELD(cxt, or1k, timerRunning);
            VMIRT_SAVE_FIELD(cxt, or1k, resetInput);
            VMIRT_SAVE_FIELD(cxt, or1k, reset);
            break;

        case SRT_END:
            // end of save/restore process
            or1k->inSaveRestore = False;
            break;

        default:
            // not reached
            VMI_ABORT("unimplemented case"); // LCOV_EXCL_LINE
            break;
    }
}

//
// OR1K processor state restore
//
VMI_RESTORE_STATE_FN(or1kRestoreStateCB) {

    or1kP or1k = (or1kP)processor;

    switch(phase) {

        case SRT_BEGIN:
            // start of save/restore process
            or1k->inSaveRestore = True;
            break;

        case SRT_BEGIN_CORE:
            // start of individual core
            break;

        case SRT_END_CORE:
            // end of individual core: save fields not covered by debug register
            // interface
            VMIRT_RESTORE_FIELD(cxt, or1k, TTCRSetCount);
            VMIRT_RESTORE_FIELD(cxt, or1k, timerRunning);
            VMIRT_RESTORE_FIELD(cxt, or1k, resetInput);
            VMIRT_RESTORE_FIELD(cxt, or1k, reset);
            // take any pending interrupt before the next instruction
            or1kInterruptNext(or1k);
            break;

        case SRT_END:
            // end of save/restore process
            or1k->inSaveRestore = False;
            break;

        default:
            // not reached
            VMI_ABORT("unimplemented case"); // LCOV_EXCL_LINE
            break;
    }
}


////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR AND DESTRUCTOR
////////////////////////////////////////////////////////////////////////////////

//
// OR1K processor constructor
//
VMI_CONSTRUCTOR_FN(or1kConstructor) {

    or1kP            or1k   = (or1kP)processor;
    or1kParamValuesP params = parameterValues;
    Uns32 i;

    // copy parameters to the model instance
    or1k->numExtInts = params->extinterrupts;
    or1k->noisy      = params->verbose;

    // initialise general purpose registers
    for(i=2; i<OR1K_REGS; i++) {
        or1k->regs[i] = 0xdeadbeef;
    }

    // initialise status registers SR, ESR, EPCR and EEAR
    or1k->SR   = SPR_SR_FO | SPR_SR_SM;
    or1k->ESR  = 0xdeadbeef;
    or1k->EPC  = 0xdeadbeef;
    or1k->EEAR = 0xdeadbeef;

    // create net port specifications
    newNetPorts(or1k);

    // create bus port specifications
    newBusPorts(or1k);

    // create the processor view
    or1kCreateView(or1k);

    // open a log file and report or not
    if (params->extintlogfile) {
        or1k->logFile = fopen(params->extintlogfile, "w");
        if (params->verbose) {
            if (or1k->logFile) {
                vmiPrintf("Opened log file '%s'\n", params->extintlogfile);
            } else {
                vmiPrintf("Failed to open log file '%s'\n", params->extintlogfile);
            }
        }
    }
}

//
// OR1K processor destructor
//
VMI_DESTRUCTOR_FN(or1kDestructor) {

    or1kP or1k = (or1kP)processor;

    // close log file if required
    if(or1k->logFile) {
        fprintf(or1k->logFile, "Finished\n");
        fclose(or1k->logFile);
    }

    // free net port specifications
    freeNetPorts(or1k);

    // free bus port specifications
    freeBusPorts(or1k);
}
