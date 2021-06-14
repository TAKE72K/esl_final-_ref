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

////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                             Version 20210408.0
//
////////////////////////////////////////////////////////////////////////////////

// This file constructs the platform.
// This file should NOT need to be edited.

#include "tlm/tlmMemory.hpp"
#include "tlm/tlmDecoder.hpp"
#include "riscv.ovpworld.org/processor/riscv/1.0/tlm/riscv_RVB32I.igen.hpp"
#include "microsemi.ovpworld.org/peripheral/CoreUARTapb/1.0/tlm/pse.igen.hpp"
#include "riscv.ovpworld.org/peripheral/PLIC/1.0/tlm/pse.igen.hpp"
#include "riscv.ovpworld.org/peripheral/CLINT/1.0/tlm/pse.igen.hpp"


using namespace sc_core;
////////////////////////////////////////////////////////////////////////////////
//                           RiscvRV32FreeRTOS Class
////////////////////////////////////////////////////////////////////////////////

class RiscvRV32FreeRTOS : public sc_module {

  public:
    RiscvRV32FreeRTOS (sc_module_name name);

    tlmRam                nvram;
    tlmRam                ddr;
    tlmModule             Platform;
    tlmDecoder            bus0;
    riscv_RVB32I          cpu0;
    CoreUARTapb           uart0;
    PLIC                  plic0;
    CLINT                 prci0;


    params paramsForRiscvRV32FreeRTOS() {
        params p;
        p.set("stoponcontrolc", true);
        return p;
    }

    params paramsForcpu0() {
        params p;
        p.set("add_Extensions", "MSU");
        p.set("simulateexceptions", true);
        p.set("mips", (double)50);
        return p;
    }

    params paramsForplic0() {
        params p;
        p.set("num_sources", (Uns32)256);
        p.set("num_targets", (Uns32)1);
        return p;
    }

    params paramsForprci0() {
        params p;
        p.set("clockMHz", (double)1.0);
        return p;
    }
}; /* RiscvRV32FreeRTOS */

////////////////////////////////////////////////////////////////////////////////
//                        RiscvRV32FreeRTOS Constructor
////////////////////////////////////////////////////////////////////////////////

RiscvRV32FreeRTOS::RiscvRV32FreeRTOS (sc_module_name name)
    : sc_module (name)
    , nvram (Platform, "nvram", 0x3ffff)
    , ddr (Platform, "ddr", 0xfffffff)
    , Platform ("", paramsForRiscvRV32FreeRTOS())
    , bus0(Platform, "bus0", 2, 5)
    , cpu0 ( Platform, "cpu0", paramsForcpu0(), 32, 32)
    , uart0 (Platform, "uart0")
    , plic0 (Platform, "plic0", paramsForplic0())
    , prci0 (Platform, "prci0", paramsForprci0())
{

    // bus0 masters
    bus0.connect(cpu0.INSTRUCTION);
    bus0.connect(cpu0.DATA);

    // bus0 slaves
    bus0.connect(uart0.port0, 0x70001000, 0x70001017); // Peripheral  (0)
    bus0.connect(plic0.port0, 0x40000000, 0x43ffffff); // Peripheral  (1)
    bus0.connect(prci0.port0, 0x44000000, 0x4400bfff); // Peripheral  (2)
    bus0.connect(nvram.sp1,0x60000000, 0x6003ffff); // Memory (3)
    bus0.connect(ddr.sp1,0x80000000, 0x8fffffff); // Memory (4)

    // Net connections
    plic0.irqT0(cpu0.MExternalInterrupt);
    prci0.MTimerInterrupt0(cpu0.MTimerInterrupt);
    prci0.MSWInterrupt0(cpu0.MSWInterrupt);

}
