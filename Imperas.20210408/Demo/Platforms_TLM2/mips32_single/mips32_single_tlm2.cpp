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
//                          Fri Jul 19 09:53:58 2019
//
////////////////////////////////////////////////////////////////////////////////

// This file declares sc_main and functions to be implemented by the user.
// This file will not be overwritten by subsequent igen runs
// unless --overwrite is specified.
// To conditionally set model attributes, use
// opOverride("instance-path", "<value>");

#include "tlm.h"
#include "tlm/tlmModule.hpp"
#include "tlm/tlmDecoder.hpp"
#include "tlm/tlmMemory.hpp"
#include "mips_mips32_r1r5_74Kc.igen.hpp"
#include "ovp_mips32_r1r5_74Kc.igen.hpp"

using namespace sc_core;
////////////////////////////////////////////////////////////////////////////////
//                      mips32_single_tlm2 Class
////////////////////////////////////////////////////////////////////////////////

class mips32_single_tlm2 : public sc_module {

  public:
    mips32_single_tlm2 (sc_module_name name);

    tlmRam                program1;
    tlmRam                stack1;
    tlmRam                stack2;
    tlmRam                stack3;
    tlmRam                high_mem1;
    tlmRam                high_mem2;
    tlmModule             Platform;
    tlmDecoder            bus;
    ovp_mips32_r1r5_74Kc  *ovp_cpu;
    mips_mips32_r1r5_74Kc *mips_cpu;

    params paramsForPlatform() {
        params p;
        p.set(OP_FP_VERBOSE, true);
        p.set(OP_FP_STOPONCONTROLC, true);
        return p;
    }

    params paramsForcpu() {
        params p;
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }
}; /* mips32_single_tlm2 */

////////////////////////////////////////////////////////////////////////////////
//                   mips32_single_tlm2 Constructor
////////////////////////////////////////////////////////////////////////////////

mips32_single_tlm2::mips32_single_tlm2 (sc_module_name name)
    : sc_module (name)
    , program1 (Platform, "program1", 0xfffff)
    , stack1 (Platform, "stack1", 0xfffff)
    , stack2 (Platform, "stack2", 0xfffff)
    , stack3 (Platform, "stack3", 0xffff)
    , high_mem1 (Platform, "high_mem1", 0xfffff)
    , high_mem2 (Platform, "high_mem2", 0x17ffff)
    , Platform ("", paramsForPlatform())
    , bus(Platform, "bus", 2, 6)
{
//    , cpu ( Platform, "cpu", paramsForcpu(), 32, 32)

    bool defaultVendor = false;
    // select model to load based upon simulator
    char *runtime = getenv("IMPERAS_RUNTIME");
    // Are we running OVPsim or Imperas? If so use mips.ovpworld.org
    if(!runtime || !strcmp(runtime, "OVPsim") || !strcmp(runtime, "CpuManager")) {
        ;   // use default vendor
        const char *model = opVLNVString (NULL, "mips.ovpworld.org", "processor", "mips32_r1r5", "1.0", OP_PROCESSOR, False);
        // Check model exists, otherwise revert to other
        if(!model) defaultVendor = true;
    } else {
        const char *model = opVLNVString (NULL, "mips.com", "processor", "mips32_r1r5", "1.0", OP_PROCESSOR, False);
        // Check model exists, otherwise revert to other
        if(model) defaultVendor = true;
    }

    if (defaultVendor) {
        mips_cpu = new mips_mips32_r1r5_74Kc ( Platform, "cpu", paramsForcpu(), 32, 32);
        ovp_cpu  = 0;
    } else {
        mips_cpu = 0;
        ovp_cpu  = new ovp_mips32_r1r5_74Kc ( Platform, "cpu", paramsForcpu(), 32, 32);
    }

    // bus masters
    if (defaultVendor) {
        bus.connect(mips_cpu->INSTRUCTION);
        bus.connect(mips_cpu->DATA);
    } else {
        bus.connect(ovp_cpu->INSTRUCTION);
        bus.connect(ovp_cpu->DATA);
    }

    // bus slaves
    bus.connect(program1.sp1,0x0, 0xfffff); // Memory (0)
    bus.connect(stack1.sp1,0x500000, 0x5fffff); // Memory (1)
    bus.connect(stack2.sp1,0x100000, 0x1fffff); // Memory (2)
    bus.connect(stack3.sp1,0x7fff0000, 0x7fffffff); // Memory (3)
    bus.connect(high_mem1.sp1,0x40000000, 0x400fffff); // Memory (4)
    bus.connect(high_mem2.sp1,0xfe80000, 0xfffffff); // Memory (5)
}

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int sc_main (int argc, char *argv[]) {
    session s;

    parser p("mips32_single_tlm2", OP_AC_ALL);
    if(!p.parse(argc, (const char **)argv)) {
        return 1;
    }
    if(!p.used("program")){
        opMessage("E", "mips32_single_tlm2", "Argument '--program' must be specified to load application program");
        return 1;
    }
    if(p.used("variant")){
        opMessage("E", "mips32_single_tlm2", "Argument '--variant' should not be specified. The variant is defined by the processor TLM interface file included in the build of the TLM platform");
        return 1;
    }

    mips32_single_tlm2 mips32_single_tlm2 ("top");

    sc_start();

    cout << "Finished sc_main." << endl;
    return 0;
}

