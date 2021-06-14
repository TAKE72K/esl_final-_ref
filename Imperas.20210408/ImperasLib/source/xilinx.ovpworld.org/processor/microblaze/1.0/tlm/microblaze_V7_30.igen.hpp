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
//                             Version 20210408.0
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "tlm/tlmProcessor.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"

using namespace sc_core;
using namespace cw;

class microblaze_V7_30 : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        p.set("variant", "V7_30");
        return p;
    }

    params paramsForProc() {
        params p;
        p.set("variant", "V7_30");
        return p;
    }

    const char *getModel() {
        const char *vlnv = opVLNVString (NULL, "xilinx.ovpworld.org", "processor", "microblaze", "1.0", OP_PROCESSOR, 1);
        if(!vlnv) {
            opMessage("F", "TLM_FFM", "Failed to find model xilinx.ovpworld.org/processor/microblaze/1.0");
        }
        return vlnv;
    }

  public:
    tlmBusMasterPort     INSTRUCTION;
    tlmBusMasterPort     DATA;
    tlmNetInputPort      Interrupt;
    tlmNetInputPort      Reset;
    tlmNetInputPort      MB_Reset;
    tlmNetInputPort      Ext_BRK;
    tlmNetInputPort      Ext_NM_BRK;

    microblaze_V7_30(tlmModule &parent, sc_module_name name)
    : tlmProcessor(parent, getModel(), name, paramsForProc())
    , INSTRUCTION (parent, this, "INSTRUCTION", 32)
    , DATA (parent, this, "DATA", 32)
    , Interrupt(parent, this, "Interrupt")
    , Reset(parent, this, "Reset")
    , MB_Reset(parent, this, "MB_Reset")
    , Ext_BRK(parent, this, "Ext_BRK")
    , Ext_NM_BRK(parent, this, "Ext_NM_BRK")
    {
    }

    microblaze_V7_30(tlmModule &parent, sc_module_name name, params p, Uns32 INSTRUCTIONWidth=32, Uns32 DATAWidth=32)
    : tlmProcessor(parent, getModel(), name, paramsForProc(p))
    , INSTRUCTION (parent, this, "INSTRUCTION", INSTRUCTIONWidth)
    , DATA (parent, this, "DATA", DATAWidth)
    , Interrupt(parent, this, "Interrupt")
    , Reset(parent, this, "Reset")
    , MB_Reset(parent, this, "MB_Reset")
    , Ext_BRK(parent, this, "Ext_BRK")
    , Ext_NM_BRK(parent, this, "Ext_NM_BRK")
    {
    }

    void before_end_of_elaboration() {
        DATA.bindIfNotBound();
    }

    void dmi(bool on) {
        INSTRUCTION.dmi(on);
        DATA.dmi(on);
    }
}; /* class microblaze_V7_30 */

