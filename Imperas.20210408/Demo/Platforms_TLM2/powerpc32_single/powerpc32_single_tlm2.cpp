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
//                             Version 20190716.0
//
////////////////////////////////////////////////////////////////////////////////

#include "tlm.h"
#include "tlm/tlmModule.hpp"
#include "tlm/tlmDecoder.hpp"
#include "tlm/tlmMemory.hpp"
#include "power.ovpworld.org/processor/powerpc32/1.0/tlm/powerpc32_mpc82x.igen.hpp"


using namespace sc_core;
////////////////////////////////////////////////////////////////////////////////
//                     powerpc32_single_tlm2 Class
////////////////////////////////////////////////////////////////////////////////

class powerpc32_single_tlm2 : public sc_module {

  public:
    powerpc32_single_tlm2 (sc_module_name name);

    tlmRam                ram1;
    tlmRam                ram2;
    tlmRam                ram3;
    tlmModule             Platform;
    tlmDecoder            bus;
    powerpc32_mpc82x      cpu1;

    params paramsForSim() {
        params p;
        p.set(OP_FP_VERBOSE, true);
        return p;
    }

    params paramsForcpu1() {
        params p;
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        return p;
    }
}; /* powerpc32_single_tlm2 */

////////////////////////////////////////////////////////////////////////////////
//                  powerpc32_single_tlm2 Constructor
////////////////////////////////////////////////////////////////////////////////

powerpc32_single_tlm2::powerpc32_single_tlm2 (sc_module_name name)
    : sc_module (name)
    , ram1 (Platform, "ram1", 0xfffff)
    , ram2 (Platform, "ram2", 0xffff)
    , ram3 (Platform, "ram3", 0xfffff)
    , Platform ("", paramsForSim())
    , bus(Platform, "bus", 2, 3)
    , cpu1 ( Platform, "cpu1", paramsForcpu1(), 32, 32)
{

    // bus masters
    bus.connect(cpu1.INSTRUCTION);
    bus.connect(cpu1.DATA);

    // bus slaves
    bus.connect(ram1.sp1,0x10000000, 0x100fffff); // Memory (0)
    bus.connect(ram2.sp1,0xffff0000, 0xffffffff); // Memory (1)
    bus.connect(ram3.sp1,0x0, 0xfffff); // Memory (2)
}

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int sc_main (int argc, char *argv[]) {
    session s;

    parser p("powerpc32_single_tlm2", OP_AC_ALL);
    if(!p.parse(argc, (const char **)argv)) {
        return 1;
    }
    if(!p.used("program")){
        opMessage("E", "powerpc32_single_tlm2", "Argument '--program' must be specified to load application program");
        return 1;
    }
    if(p.used("variant")){
        opMessage("E", "powerpc32_single_tlm2", "Argument '--variant' should not be specified. The variant is defined by the processor TLM interface file included in the build of the TLM platform");
        return 1;
    }

    powerpc32_single_tlm2 powerpc32_single_tlm2 ("powerpc32_single_tlm2");

    sc_start();

    cout << "Finished sc_main." << endl;
    return 0;
}

