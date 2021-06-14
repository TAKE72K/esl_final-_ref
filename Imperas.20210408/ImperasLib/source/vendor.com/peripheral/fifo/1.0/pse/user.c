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

#include "pse.igen.h"

// Delay in uSecs for fifos to delay between actions
// (equivalent to 5000 instructions)
// Simulator quantum should be less than this in order to
// see delay time rather than delay to end of quantum
#define FIFO_READ_DELAY  50
#define FIFO_WRITE_DELAY 50


// Source text (A.A. Milne)
const char *text =
        "\n"
        "\"It's snowing still,\" said Eeyore gloomily.\n"
        "\"So it is.\"\n"
        "\"And freezing.\"\n";


static void reportFIFO(ppmConnInfoP info) {
    bhmMessage("I", "FIFO", "FIFO state:\n");
    bhmPrintf("  inputs    : %u\n", info->inputs);
    bhmPrintf("  outputs   : %u\n", info->outputs);
    bhmPrintf("  words     : %u\n", info->words);
    bhmPrintf("  bits      : %u\n", info->bits);
    bhmPrintf("  filled    : %u\n", info->numFilled);
    bhmPrintf("  empty     : %u\n", info->numEmpty);
    bhmPrintf("\n");
}

//
// Write one character to the FIFO
//
static void writeToFifo(
    ppmConnOutputHandle fifo,
    bhmEventHandle      fifoEvent,
    Uns32               c
) {
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", "WR", "Writing character '%c' (0x%x)\n", c, c);
    }

    while(!ppmConnPut(fifo, &c)) {

        // Fifo is full - wait for event and then try again
        if (PSE_DIAG_HIGH) {
            bhmMessage("I", "WR", "FifoOut full - waiting for event");
        }

        bhmWaitEvent(fifoEvent);

        if (PSE_DIAG_HIGH) {
            bhmMessage("I", "WR", "Event triggered on FifoOut");
        }

        // Model finite speed of FIFO
        bhmWaitDelay(FIFO_WRITE_DELAY);
    }
}

static void writeThread(void *user) {

    ppmConnOutputHandle fifo = user;
    Uns32               i    = 0;
    Uns32               c;
    ppmConnInfo         info;

    ppmConnGetOutputInfo(fifo, &info);
    reportFIFO(&info);

    bhmMessage("I", "WR", "----------------\n");
    bhmMessage("I", "WR", "WRITER starting\n");
    bhmMessage("I", "WR", "----------------\n");

    // Create and register an event for fifo output activity
    bhmEventHandle fifoEvent = bhmCreateEvent();
    ppmRegisterConnOutputEvent(fifo, fifoEvent);

    // Write text to output fifo port
    // then write NULL to terminate
    while((c=text[i++])) {
        writeToFifo(fifo, fifoEvent, c);
    }
    writeToFifo(fifo, fifoEvent, 0);
}

//
// Read one character from the FIFO
//
static Uns32 readFromFifo(
    ppmConnInputHandle fifo,
    bhmEventHandle fifoEvent
) {
    Uns32 c;
    while(!ppmConnGet(fifo, &c, False)) {

        // Fifo is empty - wait for event and then try again
        if (PSE_DIAG_HIGH) {
            bhmMessage("I", "RD", "FifoIn empty - waiting for event\n");
        }

        bhmWaitEvent(fifoEvent);

        if (PSE_DIAG_HIGH) {
            bhmMessage("I", "RD", "Event triggered on FifoIn\n");
        }

        // Model finite speed of FIFO
        bhmWaitDelay(FIFO_READ_DELAY);
    }
    return c;
}

static void readThread(void *user) {

    ppmConnInputHandle fifo = user;
    ppmConnInfo        info;

    bhmMessage("I", "RD", "----------------\n");
    bhmMessage("I", "RD", "READER thread starting\n");
    bhmMessage("I", "RD", "----------------\n");

    ppmConnGetInputInfo(fifo, &info);
    reportFIFO(&info);

    // Create and register an event for fifo input activity
    bhmEventHandle fifoEvent = bhmCreateEvent();
    ppmRegisterConnInputEvent(fifo, fifoEvent);

    // Read from input fifo port and echo to stdout
    // until NULL character received
    Uns32 c;
    while((c=readFromFifo(fifo, fifoEvent))) {
        if (PSE_DIAG_HIGH) {
            bhmMessage("I", "RD", "Character '%c' (0x%x) read\n", c, c);
        } else {
            bhmPrintf("%c", c);
        }
    }
}

PPM_CONSTRUCTOR_CB(constructor) {

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_START_OF_SIMULATION));

    if (!handles.fifoPortOut && !handles.fifoPortIn){
        bhmMessage("E", "WRD", "Connected as neither reader or writer\n");
    }

    if(handles.fifoPortIn) {

        // If the FIFO input port is connected in the platform
        // then the simulator makes the fifPortIn handle non-zero.
        // In this case the model takes data from the FIFO and prints it on standard output.
        bhmCreateThread(readThread, handles.fifoPortIn, "FifoIn", 0);
    }

    if (handles.fifoPortOut) {

        // If the FIFO output port is connected in the platform then the simulator makes the
        // handle non-zero.
        // In this case the model writes data to the FIFO.
        bhmCreateThread(writeThread, handles.fifoPortOut, "FifoOut", 0);
    }
}

PPM_DESTRUCTOR_CB(destructor) {
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}



