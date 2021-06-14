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

#ifndef MULTICORE2_H
#define MULTICORE2_H

// number of values to transfer
#define NUM_VALUES 35

// status
#define DONE        0
#define AVAILABLE   1
#define FINISH      2

// shared memory location
#define SHAREDMEMORYADDRESS 0x80000000

// common shared structure
typedef struct commonDataS {
    volatile int flag;
    volatile int fibres;
} commonDataT, *commonDataP;

commonDataP sharedMemP = (commonDataP) SHAREDMEMORYADDRESS;

#endif
