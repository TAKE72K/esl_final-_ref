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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

// VMI area includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiVersion.h"

/*
 * Modified test mechanism to exit on execution of instruction at label write_tohost
 * may need to further enhance to see what is written to host ?
 */

#define PREFIX "SIGNATURE_DUMP"

// The Spike signature defines a 16 byte or 4 byte (default) line length
#define SIGNATURE_LINE_LENGTH_DEFAULT   16
#define SIGNATURE_LINE_LENGTH_ALTERNATE  4

#define RISCV_GPR_NUM 32
#define RISCV_BITS    32

// Possible result registers used for checking test pass/fail
#define GP_REG_NUMBER  3
#define A0_REG_NUMBER 10
#define T3_REG_NUMBER 28

#define UNUSED __attribute__((unused))
typedef struct vmiosObjectS {

    vmiRegInfoCP gp, a0, t3;    // VMI register information, extracted at start

    FILE *sigFP;                // Signature file

    struct {
        Uns32 ResultReg;        // Index of the register holding the result, for tests
        Bool  checkResultReg;   // Set when result register checking enabled

        char *SignatureFile;    // name of the file into which the signature is written
        Addr  startAddress;     // the start address in memory for the signature
        Uns32 bytes;            // the number of bytes for the signature
        Bool  writeAtEnd;       // write the signature file at end of simulation
        Uns32 granularity;      // granularity of line in signature file
    } params;

    Bool passed;                // flag holding exit status for the test

} vmiosObject;

/////////////////// Array of formal parameter specifications ///////////////////
///////////////////// Formal Parameter Variables structure /////////////////////

// Define the attributes value structure
typedef struct paramValuesS {
    VMI_UNS32_PARAM(ResultReg);
    VMI_STRING_PARAM(SignatureFile);
    VMI_BOOL_PARAM(SignatureAtEnd);
    VMI_UNS32_PARAM(SignatureGranularity);
    VMI_UNS32_PARAM(StartAddress);
    VMI_STRING_PARAM(StartSymbol);
    VMI_UNS32_PARAM(EndAddress);
    VMI_STRING_PARAM(EndSymbol);
    VMI_UNS32_PARAM(ByteCount);
} paramValues, *paramValuesP;

//
// Define formals
//
static vmiParameter formals[] = {
    // t3 x[28]
    // gp x[3]
    // a0 x[10]
    VMI_UNS32_PARAM_SPEC(paramValues,   ResultReg,      28, 0, 31,                 "Result Register for RISCV.org Conformance Test. 3=GP, 10=A0 or 28=T3 (default)"),
    // specify the file name to turn on signature generation
    VMI_STRING_PARAM_SPEC(paramValues,  SignatureFile,          0,                 "Name of the signature file"),
    // information on how to find memory area to dump
    VMI_BOOL_PARAM_SPEC(paramValues,    SignatureAtEnd,         0,                 "Generate a Signature file at the end of simulation "
                                                                                   "(default to generate on detection of call to write_tohost())"),
    VMI_UNS32_PARAM_SPEC(paramValues,   SignatureGranularity,   SIGNATURE_LINE_LENGTH_DEFAULT,
                                                                SIGNATURE_LINE_LENGTH_ALTERNATE,
                                                                SIGNATURE_LINE_LENGTH_DEFAULT,
                                                                "Granularity of signature file (supports default 16 or 4 bytes)"),
    VMI_UNS32_PARAM_SPEC(paramValues,   StartAddress,           0,  0,  -1,        "Address of the Start Symbol"),
    VMI_STRING_PARAM_SPEC(paramValues,  StartSymbol,            "begin_signature", "Name of the Start Symbol"),
    VMI_UNS32_PARAM_SPEC(paramValues,   EndAddress,             0,  0,  -1,        "Address of the End Symbol"),
    VMI_STRING_PARAM_SPEC(paramValues,  EndSymbol,              "end_signature",   "Name of the End Symbol"),
    VMI_UNS32_PARAM_SPEC(paramValues,   ByteCount,              SIGNATURE_LINE_LENGTH_DEFAULT,  SIGNATURE_LINE_LENGTH_DEFAULT, 4096, "Size of region in bytes (must be granularity sizebyte blocks)"),
    VMI_END_PARAM
};

//
// Iterate formals
//
static VMIOS_PARAM_SPEC_FN(getParamSpecs) {
    if(!prev) {
        prev = formals;
    } else {
        prev++;
    }
    return prev->name ? prev : 0;
}

//
// Return size of parameter structure
//
static VMIOS_PARAM_TABLE_SIZE_FN(getParamTableSize) {
    return sizeof(paramValues);
}

//
// Generate the signature file
//
static void signature (
    vmiProcessorP processor,
    vmiosObjectP  object
) {

    // Generate Signature
    if(object->params.SignatureFile) {
        // Open signature file if not already open
        if (!object->sigFP && !(object->sigFP = fopen(object->params.SignatureFile, "w+"))) {
            vmiMessage("E", PREFIX, "Failed to open '%s' for writing", object->params.SignatureFile );
            return;
        }
        memDomainP domain = vmirtGetProcessorDataDomain(processor);
        Int32 i,j;
        // NOTE:
        //   This conforms to the format generated by Spike
        //   Each line is 16 bytes in the format
        //   word 3 | word 2 | word 1 | word 0

        for (i=0;i<object->params.bytes;i+=object->params.granularity) {
            for (j=object->params.granularity-4;j>=0;j-=4) {
                Uns32 buffer;
                vmirtReadNByteDomain(domain, (object->params.startAddress+i+j), &buffer, 4, 0, 0);
                vmiPrintf("%08x", buffer);
                if(object->sigFP) fprintf(object->sigFP, "%08x", buffer);
            }
            vmiPrintf("\n");
            if(object->sigFP) fprintf(object->sigFP, "\n");
        }
        fclose(object->sigFP);
    }
}

static void exit_status (Bool passed) {
    if (passed) {
        vmiPrintf("Test PASSED\n");
    } else {
        vmiPrintf("Test FAILED\n");
    }
}

//
// Function intercepts to determine end of simulation
//
static VMIOS_INTERCEPT_FN(write_tohostCB) {
    vmiMessage("I", PREFIX, "Intercept 'write_tohost'. Generate Signature file");
    signature(processor, object);
    if(object->params.checkResultReg){
        exit_status(object->passed);
    }
    vmirtFinish(1);
}

static VMIOS_INTERCEPT_FN(terminateCB) {
    if(object->params.checkResultReg){
        exit_status(object->passed);
    }
    vmirtFinish(1);
}

//
// Check args and print PASSED if OK
//
static VMIOS_INTERCEPT_FN(riscvECALL) {
    Uns64 rr;   // result register content
    switch(object->params.ResultReg) {
    case GP_REG_NUMBER:
        vmiosRegRead(processor, object->gp, &rr);
        break;
    case A0_REG_NUMBER:
        vmiosRegRead(processor, object->a0, &rr);
        break;
    case T3_REG_NUMBER:
        vmiosRegRead(processor, object->t3, &rr);
        break;
    }

    rr = (Uns32)rr;

    if (rr == 0x1) {
        object->passed = True;
    } else {
        object->passed = False;
    }
}

static VMIOS_MORPH_FN(riscvMorph) {
    if(!object->params.checkResultReg) {
        return 0;
    }

    const char *disass = vmirtDisassemble(processor, thisPC, DSA_UNCOOKED);

    if (!strncmp(disass, "ecall", strlen("ecall"))) {
        *opaque = False;
        return riscvECALL;
    }

    return 0;
}

static
VMIOS_CONSTRUCTOR_FN(constructor)
{
    // Read configuration parameters
    paramValuesP params = parameterValues;

    if(SETBIT(params->ResultReg)) {
        object->params.ResultReg = params->ResultReg;
    
        // Only intercept ecall and check result reg if specified
        object->params.checkResultReg = True;

        // Obtain register information
        object->gp = vmiosGetRegDesc(processor, "gp");
        object->a0 = vmiosGetRegDesc(processor, "a0");
        object->t3 = vmiosGetRegDesc(processor, "t3");

        switch(object->params.ResultReg) {
            case GP_REG_NUMBER:
            case A0_REG_NUMBER:
            case T3_REG_NUMBER:
                break;
            default:
                vmiMessage("W", PREFIX, "Ignored Result register %d. Use %d, %d or %d (default)",
                                    object->params.ResultReg,
                                    GP_REG_NUMBER, A0_REG_NUMBER, T3_REG_NUMBER);
                object->params.ResultReg = T3_REG_NUMBER;
                break;
        }
    }

    object->params.SignatureFile = params->SignatureFile;
    object->params.writeAtEnd    = params->SignatureAtEnd;
    object->params.granularity   = params->SignatureGranularity;

    if(object->params.SignatureFile) {
        // Determine the start address and size

        vmiSymbolCP begin      = NULL;
        vmiSymbolCP end        = NULL;
        Addr        beginAddr  = (Addr)params->StartAddress;
        Addr        endAddr    = (Addr)params->EndAddress;
        Bool        ok         = True;

        // If the start address is not specified, see if the start symbol exists and use this address
        if(!params->SETBIT(StartAddress)) {
            if((begin = vmirtGetSymbolByName(processor, params->StartSymbol))){
                beginAddr = vmirtGetSymbolAddr(begin);
                vmiMessage("I", PREFIX, "Found Symbol '%s' in application at 0x" FMT_Ax, params->StartSymbol, beginAddr);
            } else ok = False;
        }

        // If the end address is not specified, see if the end symbol exists and use this address
        if(!params->SETBIT(EndAddress) && !params->SETBIT(ByteCount)) {
            if((end = vmirtGetSymbolByName(processor, params->EndSymbol))){
                endAddr = vmirtGetSymbolAddr(end);
                vmiMessage("I", PREFIX, "Found Symbol '%s' in application at 0x" FMT_Ax, params->EndSymbol, endAddr);
            } else ok = False;
        }

        // Calculate byte count for signature
        if(params->SETBIT(ByteCount)) {
            object->params.bytes = params->ByteCount;
        } else if (beginAddr < endAddr) {
            object->params.bytes = (Uns32)(endAddr - beginAddr);
        } else {
            object->params.bytes = (Uns32)(beginAddr - endAddr);
        }

        // The signature format is created using a 16 byte line length
        // reduce size to smaller 16 byte boundary so that only data within
        // the signature memory is included (anything outside may be variable from run to run)
        if((object->params.granularity != SIGNATURE_LINE_LENGTH_ALTERNATE) &&
           (object->params.granularity != SIGNATURE_LINE_LENGTH_DEFAULT)) {
            vmiMessage("W", PREFIX, "Signature File Granularity %u not valid. "
                                    "May be %u or %u byte blocks. "
                                    "Setting to default %u bytes",
                                    object->params.granularity,
                                    SIGNATURE_LINE_LENGTH_ALTERNATE,
                                    SIGNATURE_LINE_LENGTH_DEFAULT,
                                    SIGNATURE_LINE_LENGTH_DEFAULT);

            object->params.granularity = SIGNATURE_LINE_LENGTH_DEFAULT;
        }

        if (object->params.bytes % object->params.granularity) {
            Uns32 newBytes = (object->params.bytes - (object->params.granularity-1)) & ~object->params.granularity;
//            Uns32 newBytes = (object->params.bytes - (object->params.bytes % object->params.granularity));
            vmiMessage("W", PREFIX, "Signature File format must be granularity byte blocks,"
                                    " reducing signature size %d to %d bytes",
                                        object->params.bytes, newBytes);
            object->params.bytes = newBytes;
        }

        object->params.startAddress = beginAddr;

        if(object->params.bytes && ok) {
            vmiMessage("I", PREFIX, "Signature File enabled, file '%s'.",
                                        object->params.SignatureFile);

            vmiMessage("I", PREFIX, "Extracting signature from 0x" FMT_Ax " size %d bytes",
                                        object->params.startAddress, object->params.bytes);
            if(begin)
                vmiMessage("I", PREFIX, "Symbol '%s' at 0x" FMT_Ax,
                        params->StartSymbol, beginAddr);
            if(end)
                vmiMessage("I", PREFIX, "Symbol '%s' at 0x" FMT_Ax,
                        params->EndSymbol, endAddr);

        } else {
            // disable
            object->params.SignatureFile = NULL;
            vmiMessage("W", PREFIX, "Signature File configuration failed - disabled");
            if(!begin && !params->SETBIT(StartAddress))
                vmiMessage("I", PREFIX, "  Start symbol '%s' not found,"
                                        " change symbol name or specify StartAddress",
                                        params->StartSymbol);
            if(!end   && !params->SETBIT(EndAddress) && !params->SETBIT(ByteCount))
                vmiMessage("I", PREFIX, "  End symbol '%s' not found,"
                                        " change symbol name or specify EndAddress or BytesCount",
                                        params->EndSymbol);
            if(!object->params.bytes)
                vmiMessage("I", PREFIX, "  Size is zero");
        }
    }
}

static
VMIOS_DESTRUCTOR_FN(destructor)
{

    // Generate Signature file at end of simulation, unless already written
    if (object->params.writeAtEnd) {
        if(object->sigFP) {
            vmiMessage("I", PREFIX, "Destructor. Signature file already generated (ignore SignatureAtEnd)");
        } else {
            vmiMessage("I", PREFIX, "Destructor. Generate Signature file");
            signature(processor, object);
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
// INTERCEPT ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString  = VMI_VERSION,                // version string (THIS MUST BE FIRST)
    .modelType      = VMI_INTERCEPT_LIBRARY,      // type
    .packageName    = "signatureDump",            // description
    .objectSize     = sizeof(vmiosObject),        // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {
        .vendor  = "riscv.ovpworld.org",
        .library = "intercept",
        .name    = "signatureDump",
        .version = "1.0"
    },

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB  = constructor,                // object constructor
    .destructorCB   = destructor,                 // object destructor

    ////////////////////////////////////////////////////////////////////////
    // PARAMETER CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    .paramSpecsCB     = getParamSpecs,          // iterate parameter declarations
    .paramValueSizeCB = getParamTableSize,      // get parameter table size

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB        = riscvMorph,                 // morph callback

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts = {
        // -------------------   ----------- ------ -----------------
        // Name                  Address     Opaque Callback
        // -------------------   ----------- ------ -----------------
        { "write_tohost",        0,          False, write_tohostCB    },
        { "terminate",           0,          False, terminateCB       },
        {0}
    }
};
