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
//                          Thu Jul 18 15:30:56 2019
//
////////////////////////////////////////////////////////////////////////////////

#include "tlm.h"
#include "tlm/tlmModule.hpp"
#include "tlm/tlmDecoder.hpp"
#include "tlm/tlmMemory.hpp"
#include "ovpworld.org/processor/or1k/1.0/tlm/processor.igen.hpp"
#include "national.ovpworld.org/peripheral/16550/1.0/tlm/pse.igen.hpp"


using namespace sc_core;
////////////////////////////////////////////////////////////////////////////////
//                              uclinux_or1k_tlm2 Class
////////////////////////////////////////////////////////////////////////////////

class uclinux_or1k_tlm2 : public sc_module {

  public:
    uclinux_or1k_tlm2 (sc_module_name name);

    tlmRam                mem1;
    tlmRam                mem2;
    tlmModule             Platform;
    tlmDecoder            bus1;
    or1k                  cpu1;
    _16550                uart1;

    params paramsForuclinux_or1k_tlm2() {
        params p;
        p.set("verbose", true);
        p.set("stoponcontrolc", true);
        return p;
    }

    params paramsForcpu1() {
        params p;
        return p;
    }

    params paramsForuart1() {
        params p;

        Uns32 portNumber;

        // get the port number to start server
        char *envPortNum = getenv("PORTNUM");
        if (envPortNum == NULL) {
            p.set("console", (bool)1);
        } else {
            portNumber = atoi(envPortNum);
            p.set("portnum", portNumber);
        }
        p.set("finishOnDisconnect", (bool)1);
        return p;
    }
}; /* uclinux_or1k_tlm2 */

////////////////////////////////////////////////////////////////////////////////
//                           uclinux_or1k_tlm2 Constructor
////////////////////////////////////////////////////////////////////////////////

uclinux_or1k_tlm2::uclinux_or1k_tlm2 (sc_module_name name)
    : sc_module (name)
    , mem1 (Platform, "mem1", 0x8fffffff)
    , mem2 (Platform, "mem2", 0x6ffffff7)
    , Platform ("", paramsForuclinux_or1k_tlm2())
    , bus1(Platform, "bus1", 2, 3)
    , cpu1 ( Platform, "cpu1", paramsForcpu1(), 32, 32)
    , uart1 (Platform, "uart1", paramsForuart1())
{

    // bus1 masters
    bus1.connect(cpu1.INSTRUCTION);
    bus1.connect(cpu1.DATA);

    // bus1 slaves
    bus1.connect(uart1.bport1, 0x90000000, 0x90000007); // Peripheral  (0)
    bus1.connect(mem1.sp1,0x0, 0x8fffffff); // Memory (1)
    bus1.connect(mem2.sp1,0x90000008, 0xffffffff); // Memory (2)

    // Net connections
    uart1.intOut(cpu1.intr2);

}

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int sc_main (int argc, char *argv[]) {
    session s;

    const char *app      = "linux_sh.or32";

    parser p("uclinux_or1k_tlm2", OP_AC_ALL);
    if(!p.parse(argc, (const char **)argv)) {
        return 1;
    }

    if(p.used("variant")){
        opMessage("E", "uclinux_or1k_tlm2", "Argument '--variant' should not be specified. The variant is defined by the processor TLM interface file used to build the TLM platform");
        return 1;
    }

    cout << "Constructing." << endl;

    uclinux_or1k_tlm2 uclinux_or1k_tlm2 ("top");

    uclinux_or1k_tlm2.uart1.diagnosticLevelSet(1);  // Set diagnostic level for Uart

    if(!p.used("program")){
        opMessage("I", "uclinux_or1k_tlm2", "Loading default application program %s", app);
        if (!uclinux_or1k_tlm2.cpu1.applicationLoad(app, OP_LDR_VERBOSE | OP_LDR_SET_START, 0)) {
            opMessage("E", "uclinux_or1k_tlm2", "Failed to load application program %s", app);
            return 1;
        }
    }

    cout << "Starting sc_main." << endl;

    sc_start();
    return 0;
}

