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
#include "xilinx.ovpworld.org/processor/microblaze/1.0/tlm/microblaze_V8_20.igen.hpp"


using namespace sc_core;
////////////////////////////////////////////////////////////////////////////////
//                    BareMetalMicroblazeSingle_TLM2 Class
////////////////////////////////////////////////////////////////////////////////

class BareMetalMicroblazeSingle_TLM2 : public sc_module {

  public:
    BareMetalMicroblazeSingle_TLM2 (sc_module_name name);

    tlmRam                ram1;
    tlmRam                ram2;
    tlmModule             Platform;
    tlmDecoder            bus;
    microblaze_V8_20      cpu1;

    params paramsForPlatform() {
        params p;
        p.set(OP_FP_VERBOSE, true);
        p.set(OP_FP_STOPONCONTROLC, true);
        return p;
    }

    params paramsForcpu1() {
        params p;
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        return p;
    }
}; /* BareMetalMicroblazeSingle_TLM2 */

////////////////////////////////////////////////////////////////////////////////
//                 BareMetalMicroblazeSingle_TLM2 Constructor
////////////////////////////////////////////////////////////////////////////////

BareMetalMicroblazeSingle_TLM2::BareMetalMicroblazeSingle_TLM2 (sc_module_name name)
    : sc_module (name)
    , ram1 (Platform, "ram1", 0x7ffff)
    , ram2 (Platform, "ram2", 0xfffff)
    , Platform ("", paramsForPlatform())
    , bus(Platform, "bus", 2, 2)
    , cpu1 ( Platform, "cpu1", paramsForcpu1(), 32, 32)
{

    // bus masters
    bus.connect(cpu1.INSTRUCTION);
    bus.connect(cpu1.DATA);

    // bus slaves
    bus.connect(ram1.sp1,0x0, 0x7ffff); // Memory (0)
    bus.connect(ram2.sp1,0x200000, 0x2fffff); // Memory (1)
}

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int sc_main (int argc, char *argv[]) {
    session s;

    parser p("BareMetalMicroblazeSingle_TLM2", OP_AC_ALL);
    if(!p.parse(argc, (const char **)argv)) {
        return 1;
    }
    if(!p.used("program")){
        opMessage("E", "BareMetalMicroblazeSingle_TLM2", "Argument '--program' must be specified to load application program");
        return 1;
    }
    if(p.used("variant")){
        opMessage("E", "BareMetalMicroblazeSingle_TLM2", "Argument '--variant' should not be specified. The variant is defined by the processor TLM interface file included in the build of the TLM platform");
        return 1;
    }

    BareMetalMicroblazeSingle_TLM2 BareMetalMicroblazeSingle_TLM2 ("BareMetalMicroblazeSingle_TLM2");

    sc_start();

    cout << "Finished sc_main." << endl;
    return 0;
}

