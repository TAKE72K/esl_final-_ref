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

#include <string.h>
#include <stdlib.h>

#include "op/op.h"

//
// This is the callback, called once per installed command
// when iterating the processor commands using opProcessorCommandIterAll
//
static OP_COMMAND_FN(printCommand) {
    opPrintf("Command %s\n", opObjectHierName(command));
}

//
// Main
//
int main(int argc, const char *argv[]) {
    opSessionInit(OP_VERSION);

    opCmdParseStd (argv[0], OP_AC_ALL, argc, argv);

    optModuleP mr = opRootModuleNew(0, 0, 0);
    optModuleP mi = opModuleNew(mr, "module", "u1", 0, 0);

    opRootModulePreSimulate(mr);

    // get processor, assumes only a single processor
    optProcessorP processor = opProcessorNext(mi, NULL);

    // Run the processor for 100 instructions
    opProcessorSimulate(processor, 100);

    // Call a command that had been created in a processor model
    // Pointer to the call command result string. This could be any string
    const char *result;

    opPrintf("\nCall Model Commands\n\n");

    // Setup command for reading MIPS COP0 registers
    const char* cmdToExecute = "u1/cpu1/mipsCOP0";
    optCommandP cmd = opObjectByName(mr,
                                     cmdToExecute,
                                     OP_COMMAND_EN).Command;
    if(!cmd)
        opMessage("F", "harness", "Command '%s' not found", cmdToExecute);

    // Setup calling arguments to read COP0 'Config' register
    const char *cmd1Argv[] = {"mipsCOP0", "-register", "16", "-select", "0"};
    result = opCommandCall( cmd,
                            5,
                            cmd1Argv);

    opPrintf("\nCall Command result '%s'\n", result);

    // Setup calling arguments to read COP0 'PrId' register
    const char *cmd2Argv[] = {"mipsCOP0", "-register", "15", "-select", "0"};

    result = opCommandCall( cmd,
                            5,
                            cmd2Argv);

    opPrintf("\nCall Command result '%s'\n", result);

    opPrintf("\nDiscover installed commands\n");

    // iterates over all commands on all processor instances
    opModuleCommandsShow(mi);

    const char *procName = "cpu1";
    opPrintf("Commands for %s\n", procName);
    optProcessorP proc = opObjectByName(mi, procName, OP_PROCESSOR_EN).Processor;

    // iterates over all commands on this processor instance
    opProcessorCommandIterAll(proc, printCommand, 0);

    opPrintf("\nComplete Simulation\n\n");

    // run simulation to completion
    opRootModuleSimulate(mr);

    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}
