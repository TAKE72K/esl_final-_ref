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


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                           Imperas/OVP Development
//                          Wed Jul 17 14:32:43 2019
//
////////////////////////////////////////////////////////////////////////////////

#include "tlm.h"
#include "tlm/tlmModule.hpp"
#include "tlm/tlmDecoder.hpp"
#include "tlm/tlmMemory.hpp"
#include "mips.ovpworld.org/processor/mips32_r1r5/1.0/tlm/mips32_r1r5_74Kc.igen.hpp"


using namespace sc_core;
////////////////////////////////////////////////////////////////////////////////
//                    multicore2_mips32_tlm2 Class
////////////////////////////////////////////////////////////////////////////////

class multicore2_mips32_tlm2 : public sc_module {

  public:
    multicore2_mips32_tlm2 (sc_module_name name);

    tlmRam                ram_sh;
    tlmRam                ram_10;
    tlmRam                ram_11;
    tlmRam                ram_20;
    tlmRam                ram_21;
    tlmModule             Platform;
    tlmDecoder            bus_sh;
    tlmDecoder            bus0;
    tlmDecoder            bus1;
    mips32_r1r5_74Kc      cpu1;
    mips32_r1r5_74Kc      cpu2;

    params paramsForPlatform() {
        params p;
        p.set(OP_FP_VERBOSE, true);
        p.set(OP_FP_STOPONCONTROLC, true);
        return p;
    }

    params paramsForcpu1() {
        params p;
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }

    params paramsForcpu2() {
        params p;
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }
}; /* multicore2_mips32_tlm2 */

////////////////////////////////////////////////////////////////////////////////
//                 multicore2_mips32_tlm2 Constructor
////////////////////////////////////////////////////////////////////////////////

multicore2_mips32_tlm2::multicore2_mips32_tlm2 (sc_module_name name)
    : sc_module (name)
    , ram_sh (Platform, "ram_sh", 0xfff)
    , ram_10 (Platform, "ram_10", 0x17ffff)
    , ram_11 (Platform, "ram_11", 0xfffff)
    , ram_20 (Platform, "ram_20", 0x17ffff)
    , ram_21 (Platform, "ram_21", 0xfffff)
    , Platform ("", paramsForPlatform())
    , bus_sh(Platform, "bus_sh", 2, 1)
    , bus0(Platform, "bus0", 2, 3)
    , bus1(Platform, "bus1", 2, 3)
    , cpu1 ( Platform, "cpu1", paramsForcpu1(), 32, 32)
    , cpu2 ( Platform, "cpu2", paramsForcpu2(), 32, 32)
{

    // bus_sh slaves
    bus_sh.connect(ram_sh.sp1,0x0, 0xfff); // Memory (0)

    // bus0 masters
    bus0.connect(cpu1.INSTRUCTION);
    bus0.connect(cpu1.DATA);

    // bus0 slaves
    bus0.connect(ram_10.sp1,0xfe80000, 0xfffffff); // Memory (0)
    bus0.connect(ram_11.sp1,0x20000, 0x11ffff); // Memory (1)
    bus0.connect(bus_sh, 0x0, 0xfff, 0x0); // Bridge (2)

    // bus1 masters
    bus1.connect(cpu2.INSTRUCTION);
    bus1.connect(cpu2.DATA);

    // bus1 slaves
    bus1.connect(ram_20.sp1,0xfe80000, 0xfffffff); // Memory (0)
    bus1.connect(ram_21.sp1,0x20000, 0x11ffff); // Memory (1)
    bus1.connect(bus_sh, 0x0, 0xfff, 0x0); // Bridge (2)
}

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int sc_main (int argc, char *argv[]) {
    session s;

    parser p("multicore2_mips32_tlm2", OP_AC_ALL);
    if(!p.parse(argc, (const char **)argv)) {
        return 1;
    }
    if(!p.used("program")){
        opMessage("E", "multicore2_mips32_tlm2", "Argument '--program' must be specified to load application program");
        return 1;
    }
    if(p.used("variant")){
        opMessage("E", "multicore2_mips32_tlm2", "Argument '--variant' should not be specified. The variant is defined by the processor TLM interface file included in the build of the TLM platform");
        return 1;
    }

    multicore2_mips32_tlm2 multicore2_mips32_tlm2 ("top");

    sc_start();

    cout << "Finished sc_main." << endl;
    return 0;
}

