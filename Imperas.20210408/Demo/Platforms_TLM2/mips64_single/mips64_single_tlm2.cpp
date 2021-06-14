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
//                          Fri Jul 19 11:08:39 2019
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
#include "ovp_mips64_r1r5_5KEc.igen.hpp"
#include "mips_mips64_r1r5_5KEc.igen.hpp"


using namespace sc_core;
////////////////////////////////////////////////////////////////////////////////
//                      mips64_single_tlm2 Class
////////////////////////////////////////////////////////////////////////////////

class mips64_single_tlm2 : public sc_module {

  public:
    mips64_single_tlm2 (sc_module_name name);

    tlmRam                program1;
    tlmRam                stack1;
    tlmModule             Platform;
    tlmDecoder            bus;
    ovp_mips64_r1r5_5KEc  *ovp_cpu;
    mips_mips64_r1r5_5KEc *mips_cpu;

    params paramsForPlatform() {
        params p;
        p.set(OP_FP_VERBOSE, true);
        p.set(OP_FP_STOPONCONTROLC, true);
        return p;
    }

    params paramsForcpu() {
        params p;
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "big");
        return p;
    }
}; /* mips64_single_tlm2 */

////////////////////////////////////////////////////////////////////////////////
//                   mips64_single_tlm2 Constructor
////////////////////////////////////////////////////////////////////////////////

mips64_single_tlm2::mips64_single_tlm2 (sc_module_name name)
    : sc_module (name)
    , program1 (Platform, "program1", 0xfffff)
    , stack1 (Platform, "stack1", 0xfffff)
    , Platform ("", paramsForPlatform())
    , bus(Platform, "bus", 2, 2)
{
//    , cpu ( Platform, "cpu", paramsForcpu(), 36, 36)

    bool defaultVendor = false;
    // select model to load based upon simulator
    char *runtime = getenv("IMPERAS_RUNTIME");
    // Are we running OVPsim or Imperas? If so use mips.ovpworld.org
    if(!runtime || !strcmp(runtime, "OVPsim") || !strcmp(runtime, "CpuManager")) {
        ;   // use default vendor
        const char *model = opVLNVString (NULL, "mips.ovpworld.org", "processor", "mips64_r1r5", "1.0", OP_PROCESSOR, False);
        // Check model exists, otherwise revert to other
        if(!model) defaultVendor = true;
    } else {
        const char *model = opVLNVString (NULL, "mips.com", "processor", "mips64_r1r5", "1.0", OP_PROCESSOR, False);
        // Check model exists, otherwise revert to other
        if(model) defaultVendor = true;
    }

    if (defaultVendor) {
        mips_cpu = new mips_mips64_r1r5_5KEc ( Platform, "cpu", paramsForcpu(), 36, 36);
        ovp_cpu  = 0;
    } else {
        mips_cpu = 0;
        ovp_cpu  = new ovp_mips64_r1r5_5KEc ( Platform, "cpu", paramsForcpu(), 36, 36);
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
    bus.connect(stack1.sp1,0xff00000, 0xfffffff); // Memory (1)
}

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int sc_main (int argc, char *argv[]) {
    session s;

    parser p("mips64_single_tlm2", OP_AC_ALL);
    if(!p.parse(argc, (const char **)argv)) {
        return 1;
    }
    if(!p.used("program")){
        opMessage("E", "mips64_single_tlm2", "Argument '--program' must be specified to load application program");
        return 1;
    }
    if(p.used("variant")){
        opMessage("E", "mips64_single_tlm2", "Argument '--variant' should not be specified. The variant is defined by the processor TLM interface file included in the build of the TLM platform");
        return 1;
    }

    mips64_single_tlm2 mips64_single_tlm2 ("top");

    sc_start();

    cout << "Finished sc_main." << endl;
    return 0;
}

