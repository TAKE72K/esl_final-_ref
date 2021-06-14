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
#include <string.h>
#include <stdlib.h>

#include "op/op.h"

#define PLATFORM_NAME "platform"

//
// Simulation main loop
//
static Bool simulate(optProcessorP processor, Uns64 instructions) {

    optStopReason stopReason = opProcessorSimulate(processor, instructions);

    switch(stopReason) {

       case OP_SR_SCHED:
           // hit the scheduler limit
           return True;

       case OP_SR_EXIT:
           // processor has exited
           return False;

       case OP_SR_FINISH:
           // simulation must end
           return False;

       default:
           opPrintf("unexpected stopReason %u\n", stopReason);
           return False;
    }
}

//
// Report AxPROT for the processor access
//
static void reportAxPROT(
    optProcessorP processor,
    Bool          isFetch,
    optRegP       transactPL,
    Addr          address
) {
    // take action only for non-artifact accesses
    if(processor) {

        Bool isNS = (address & 0x10000000000ULL) && True;
        Uns32 PL;

        opProcessorRegRead(processor, transactPL, &PL);
        opPrintf("    AxPROT=%u%u%u VA=0x"FMT_640Nx"\n", !isFetch, isNS, PL, address);
    }
}

//
// Watch callbacks for memory accesses
//
static OP_MONITOR_FN(watchRead)  {reportAxPROT(processor, False, userData, addr);}
static OP_MONITOR_FN(watchWrite) {reportAxPROT(processor, False, userData, addr);}
static OP_MONITOR_FN(watchFetch) {reportAxPROT(processor, True,  userData, addr);}

//
// Main simulation routine
//
int main(int argc, char ** argv) {

    // initialize CpuManager
    opSessionInit(OP_VERSION);

    // Command line parser
    optCmdParserP parser = opCmdParserNew(PLATFORM_NAME, OP_AC_ALL);

    opCmdParseArgs(parser, (Uns32)argc, (const char **)argv);

    // Check program has been specified
    if(!opCmdArgUsed(parser, "program")){
        opMessage("E", PLATFORM_NAME"_PE", "Please ensure that -program <Application ELF> is specified");
        return 1;
    }

    optParamP paramsSim = NULL;
    paramsSim = opParamBoolSet(paramsSim, OP_FP_STOPONCONTROLC, True);
    paramsSim = opParamBoolSet(paramsSim, OP_FP_VERBOSE,        True);

    optModuleP  mr = opRootModuleNew (NULL, PLATFORM_NAME, paramsSim);

    // create bus
    optBusP busPhys = opBusNew(mr, "busPhys", 40, 0, 0);
    optBusP busNS   = opBusNew(mr, "busNS",   41, 0, 0);

    // create and connect physical memory
    opMemoryNew(
            mr,
            "memory",
            OP_PRIV_RWX,
            0xffffffffffULL,
            OP_CONNECTIONS(
                OP_BUS_CONNECTIONS(
                    OP_BUS_CONNECT(busPhys, "sp1", .slave=1, .addrLo=0x00000000000ULL, .addrHi=0xffffffffffULL)
                )
            ),
            0
            );

    // create aliases
    opBridgeNew(
            mr,
            "secure",
            OP_CONNECTIONS(
                OP_BUS_CONNECTIONS(
                    OP_BUS_CONNECT(busNS,     "sp1", .slave=1, .addrLo=0x00000000000ULL, .addrHi=0xffffffffffULL),
                    OP_BUS_CONNECT(busPhys,   "mp1",           .addrLo=0x00000000000ULL, .addrHi=0xffffffffffULL)
                )
            ),
            0
    );
    opBridgeNew(
            mr,
            "non-secure",
            OP_CONNECTIONS(
                OP_BUS_CONNECTIONS(
                    OP_BUS_CONNECT(busNS,     "sp1", .slave=1, .addrLo=0x10000000000ULL, .addrHi=0x1ffffffffffULL),
                    OP_BUS_CONNECT(busPhys,   "mp1",           .addrLo=0x00000000000ULL, .addrHi=0x0ffffffffffULL)
                )
            ),
            0
    );

    // set up processor instance parameters
    optParamP paramsCpu = NULL;
    paramsCpu = opParamEndianSet(paramsCpu, OP_FP_ENDIAN, OP_ENDIAN_LITTLE);
    paramsCpu = opParamEnumSet(paramsCpu, "variant", "Cortex-A9UP");
    paramsCpu = opParamBoolSet(paramsCpu, OP_FP_SIMULATEEXCEPTIONS, True);
    paramsCpu = opParamBoolSet(paramsCpu, OP_FP_TRACE,              True);

    // create a processor and connect to bus
    const char *model    =
        opVLNVString(NULL, "arm.ovpworld.org", "processor",    "arm",         "1.0", OP_PROCESSOR, 0);

    optProcessorP cpu_c = opProcessorNew(
        mr,
        model,
        "cpu1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busNS, "INSTRUCTION"),
                OP_BUS_CONNECT(busNS, "DATA")
            )
        ),
        paramsCpu
    );

    // Add the extension library to detect exit()
    const char *extension =
        opVLNVString(NULL, "ovpworld.org",     "modelSupport", "imperasExit", "1.0", OP_EXTENSION, 0);

    opProcessorExtensionNew(cpu_c, extension, "imperasExit", 0);

    // get register descriptor for transactPL register
    optRegP transactPL = opProcessorRegByName(cpu_c, "transactPL");

    // add callbacks to monitor the accesses
    opBusReadMonitorAdd(busNS, NULL, 0x00000000000ULL, 0x1ffffffffffULL, watchRead,  transactPL);
    opBusWriteMonitorAdd(busNS, NULL, 0x00000000000ULL, 0x1ffffffffffULL, watchWrite, transactPL);
    opBusFetchMonitorAdd(busNS, NULL, 0x00000000000ULL, 0x1ffffffffffULL, watchFetch, transactPL);

    // run processor
    simulate(cpu_c, 20000);

    opSessionTerminate();


    return (opErrors() ? 1 : 0);    // check for errors
}

