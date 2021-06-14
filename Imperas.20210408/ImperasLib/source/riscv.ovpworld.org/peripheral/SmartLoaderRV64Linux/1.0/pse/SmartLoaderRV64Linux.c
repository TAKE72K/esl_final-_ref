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

//
// Smart loader peripheral model for Linux:
//   Loads the device tree blob and provides boot code to call Linux
//
//   This peripheral takes the place of the Boot monitor and U-Boot functions
//
#include <riscv.ovpworld.org/peripheral/SmartLoaderRV64Linux/1.0/pse/pse.igen.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "fdt_imp_util.h"

#define PREFIX "SMARTLOADER_LINUX"

// Default to RV64
#ifndef RISCV_XLEN
#define RISCV_XLEN 64
#endif

#define FNSIZE 256

struct riscv_boot_info {
    Addr   bootAddr;          // address in simulated memory called from generated boot code
    char   bootImage[FNSIZE]; // name of boot image file to load
    Addr   slBootAddr;        // address in simulated memory of generated boot code and dtb
    char   dtbFn[FNSIZE];     // name of device tree blob file to load
    Uns32 *bootCode;          // Boot Loader code to use
    Uns32  bootSize;          // Size of boot code
    Uns32  bootDtbOffset;     // Offset into bootcode to place DTB address
    Uns32  bootAddrOffset;    // Offset into bootcode to place boot entry address
    Addr   memBase;           // address of main memory
    Addr   memSize;           // size of main memory
    Bool   memSet;            // memory base and size specified
};

// Structure to hold configuration info, initialized with defaults
static struct riscv_boot_info config = {
    .bootAddr       = 0x80000000ULL,
    .slBootAddr     =     0x1000ULL,
    .bootCode       = NULL,
    .bootSize       = 0,
    .bootDtbOffset  = -1,
    .bootAddrOffset = -1,
    .memSet         = False,
};

//
// bootloader for BBL.  Set registers to values expected by BBL and jump to BBL file entry
//
static Uns32 bblBootLoader[] = {
        0x00000297,                  /* auipc  t0, 0 */
        0xf1402573,                  /* csrr   a0, mhartid  */
#if RISCV_XLEN == 32
        0x0182a583,                  /* lw     a1, 24(t0) # dtb  addr */
        0x0202a283,                  /* lw     t0, 32(t0) # boot addr */
#elif RISCV_XLEN == 64
        0x0182b583,                  /* ld     a1, 24(t0) # dtb  addr */
        0x0202b283,                  /* ld     t0, 32(t0) # boot addr */
#else
#error "Invalid RISCV_XLEN value"
#endif
        0x00028067,                  /*     jr     t0 */
        0x00000000,                  /* Doubleword align */

    // fdt:       .quad 0  //  Fill with PA of FDT
    0x0, 0x0,

    // bootaddr:  .quad 0  //  Fill with PA of kernel entry
    0x0, 0x0,
};

// Indexes for the address entries to be filled in
#define BBL_BOOT_ENTRIES (sizeof(bblBootLoader)/sizeof(bblBootLoader[0]))
#define ENTRIES_PER_UNS64 (sizeof(Uns64)/sizeof(bblBootLoader[0]))
#define BBL_BOOT_FDT   (BBL_BOOT_ENTRIES - (2*ENTRIES_PER_UNS64))
#define BBL_BOOT_ADDR  (BBL_BOOT_ENTRIES - (1*ENTRIES_PER_UNS64))

// ***************************************************************

#define BYTES_PER_ACCESS  128
#ifndef O_BINARY
#define O_BINARY 0
#endif

//
// Write to simulated memory
//
static Bool writeSimMemory(
    const char *name,
    Addr        addr,
    Uns32       size,
    void       *data
) {

    if (PSE_DIAG_MEDIUM) {
        bhmMessage(
            "I", PREFIX,
            "Writing %s (%d bytes at 0x%08llx)",
            name, size, addr
        );
    }

    if (!ppmWriteAddressSpace(handles.mport, addr, size, data)) {

        bhmMessage(
            "E", PREFIX,
            "Failed trying to write %s (%d bytes at 0x%08llx)",
            name, size, addr
        );
        return False;

    }

    return True;

}

//
// Load the file at the indicated address
// Returns number of bytes loaded or 0 if an error
//
static Uns32 load_image(char *name, const char *filename, Uns32 addr) {

    Int32 fd = open(filename, O_RDONLY | O_BINARY);

    if (fd < 0) {
        bhmMessage("E", PREFIX, "Cannot open %s image file %s", name, filename);
        return 0;
    }

    // Get the size of the file
    Int32 size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    // Copy the file to simulated memory
    Uns32 bytes = size;
    Uns32 dest  = addr;
    char  buff[BYTES_PER_ACCESS];
    while (bytes) {

        Uns32 thisAccess = (bytes > BYTES_PER_ACCESS) ? BYTES_PER_ACCESS : bytes;

        thisAccess = read(fd, buff, thisAccess);

        if (!ppmWriteAddressSpace(handles.mport, dest, thisAccess, buff)){

            bhmMessage(
                "E", PREFIX,
                "Unable to write %s image file %s to simulated memory: failed at 0x%08x",
                name, filename, dest
            );

            close(fd);
            return 0;

        }

        dest  += thisAccess;
        bytes -= thisAccess;

    }

    close(fd);

    if(PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX, "%s image file %s loaded (%u bytes @ 0x%08x)", name, filename, size, addr);
    }

    return size;
}

static Bool setAddrParameter(char *name, Addr *val) {

    Addr attrVal;

    if (bhmUns64ParamValue(name, &attrVal)) {
        *val = attrVal;
        if (PSE_DIAG_LOW) {
            bhmMessage("I", PREFIX, "%s: set to 0x%08llx", name, *val);
        }
        return True;
    } else if (PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX, "%s: using default value 0x%08llx", name, *val);
    }
    return False;
}

static Bool setStringParameter(char *name, char *str, Uns32 size) {

    if (bhmStringParamValue(name, str, size)) {
        if (PSE_DIAG_LOW) {
            bhmMessage("I", PREFIX, "%s: set to '%s'", name, str);
        }
        return True;
    }
    return False;
}

//
// Align pointer to the indicated byte boundary
//
static inline Addr alignPointer(Addr ptr, Uns32 align) {
    Addr mask = align - 1;
    return (ptr + mask) & ~mask;
}

static Bool setBootConvention() {

    char convention[32];

    if (!bhmStringParamValue("bootconvention", convention, sizeof(convention))) {
        // if not specified, default to bbl
        strcpy(convention, "bbl");
    }

    if (strcmp(convention, "bbl") == 0) {

        // Set boot loader values for the BBL boot code
        config.bootCode       = bblBootLoader;
        config.bootSize       = sizeof(bblBootLoader);
        config.bootDtbOffset  = BBL_BOOT_FDT;
        config.bootAddrOffset = BBL_BOOT_ADDR;

    } else {

        bhmMessage(
            "E", PREFIX"_IBC",
            "Invalid bootconvention parameter value '%s'. Permitted values are: 'bbl'",
            convention
        );
        return False;

    }

    return True;

}

//
// Access all attributes to inhibit unused warning messages
//
static void touchParameters() {

    Uns64 dummy;
    char dummyStr[4];

    bhmUns64ParamValue ("slbootaddr",    &dummy);
    bhmUns64ParamValue ("bootaddr",      &dummy);
    bhmUns64ParamValue ("membase",       &dummy);
    bhmUns64ParamValue ("memsize",       &dummy);
    bhmStringParamValue("bootimage",      dummyStr, sizeof(dummyStr));
    bhmStringParamValue("command",        dummyStr, sizeof(dummyStr));
    bhmStringParamValue("append",         dummyStr, sizeof(dummyStr));
    bhmStringParamValue("dtb",            dummyStr, sizeof(dummyStr));
    bhmStringParamValue("bootconvention", dummyStr, sizeof(dummyStr));

}

//
// Check if smartLoader parameters indicate it is used
//
static Bool smartLoaderUsed() {

    Bool used = False;
    Bool disable;
    bhmBoolParamValue("disable", &disable);

    if (!disable) {

        char dummyStr[FNSIZE];

        // Presence of these parameters indicates smart loader has something to load
        used = bhmStringParamValue("bootimage", dummyStr, sizeof(dummyStr))
             | bhmStringParamValue("dtb",       dummyStr, sizeof(dummyStr));

    }

    return used;
}

PPM_CONSTRUCTOR_CB(constructor) {

    bhmEventHandle started  = bhmGetSystemEvent(BHM_SE_START_OF_SIMULATION);
    bhmWaitEvent(started);

    periphConstructor();

    if (!smartLoaderUsed()) {

        bhmMessage("W", PREFIX"_SLD", "Linux Smart Loader Disabled");
        touchParameters();

    } else {

        // Set the boot convention to be used
        if (!setBootConvention()) {

            // Error if boot convention not set - message issued by call
            touchParameters();

        } else {

            // Override defaults with any attributes set from platform
            setAddrParameter("slbootaddr", &config.slBootAddr);
            setAddrParameter("bootaddr",   &config.bootAddr);

            if (setAddrParameter("membase", &config.memBase) &&
                setAddrParameter("memsize", &config.memSize)) {
                config.memSet = True;
            }

            // get address for dtb - follows bootloader, aligned to 32 bytes
            Addr dtbAddr = alignPointer(config.slBootAddr + config.bootSize, 32);

            //
            // Read dtb file into host memory and add any additional settings to the fdt
            //
            if (!setStringParameter("dtb", config.dtbFn, sizeof(config.dtbFn))) {

                bhmMessage("E", PREFIX"_MDF", "dtb file name must be specified using the dtb parameter");
                touchParameters();

            } else {

                void *fdt = fdtReadDTB(config.dtbFn);

                if (fdt) {

                    // set command line info in fdt
                    char cmdLine[1024] = "";
                    char append[512] = "";
                    setStringParameter("command", cmdLine, sizeof(cmdLine));
                    setStringParameter("append",  append, sizeof(append));
                    if (*append) {
                        Uns32 len = strlen(cmdLine);
                        snprintf(cmdLine+len, sizeof(cmdLine)-len, " %s", append);
                    }
                    fdtSetCommandLine(fdt, cmdLine);

                    if (config.memSet) {
                        fdtSetMemory(fdt, config.memBase, config.memSize);
                    }

                    if (PSE_DIAG_HIGH) {
                        fdtPrint(fdt);
                    }

                    // Copy fdt to simulated memory
                    writeSimMemory("dtb", dtbAddr, fdt_totalsize(fdt), fdt);

                }
            }

            if (config.bootCode) {
                if (config.bootDtbOffset != -1) {
                    *(Uns64 *)(config.bootCode+config.bootDtbOffset)  = dtbAddr;
                }
                if (config.bootAddrOffset != -1) {
                    *(Uns64 *)(config.bootCode+config.bootAddrOffset) = config.bootAddr;
                }

                // Write bootloader to beginning of simulated memory after setting addresses
                writeSimMemory("bootloader", config.slBootAddr, config.bootSize, config.bootCode);
            }

            // Copy bootimage file to bootaddr location if specified
            if (setStringParameter("bootimage", config.bootImage, sizeof(config.bootImage))) {
                load_image("boot", config.bootImage, config.bootAddr);
            }
        }
    }

    // No longer used so close it
    ppmCloseAddressSpace(handles.mport);

}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

