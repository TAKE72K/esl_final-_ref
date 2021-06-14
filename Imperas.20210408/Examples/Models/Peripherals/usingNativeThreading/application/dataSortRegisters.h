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

//////////////////////// Registers for DATASORT Controller based on ARM PL081 ////////////////////////////

#ifndef DATASORT_REGISTERS_H
#define DATASORT_REGISTERS_H

// number of peripherals used (may be overridden from compiler command line)
#ifndef PERIPHERALS
#define PERIPHERALS              2
#endif

// The random data can be generated by the application or peripheral
#define APPLICATIONGENERATESDATA       0

// base of peripherals
#define DATASORTSPBASE                 0x80000000

// size of peripheral port address space
#define DATASORTSPSIZE                 0x1000

// Offsets into the Peripheral Windows
#define DATASORTSP_AB8_START          (0x0)
#define DATASORTSP_AB32CH0_SRCADDR    (0x100)
#define DATASORTSP_AB32CH0_DATASIZE   (0x104)

#endif