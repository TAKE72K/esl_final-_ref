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

class m16c_r8c : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        p.set("variant", "r8c");
        return p;
    }

    params paramsForProc() {
        params p;
        p.set("variant", "r8c");
        return p;
    }

    const char *getModel() {
        const char *vlnv = opVLNVString (NULL, "posedgesoft.ovpworld.org", "processor", "m16c", "1.0", OP_PROCESSOR, 1);
        if(!vlnv) {
            opMessage("F", "TLM_FFM", "Failed to find model posedgesoft.ovpworld.org/processor/m16c/1.0");
        }
        return vlnv;
    }

  public:
    tlmBusMasterPort     INSTRUCTION;
    tlmBusMasterPort     DATA;
    tlmNetInputPort      reset;
    tlmNetInputPort      nmi;
    tlmNetInputPort      int_per;
    tlmNetOutputPort     int_ack;

    m16c_r8c(tlmModule &parent, sc_module_name name)
    : tlmProcessor(parent, getModel(), name, paramsForProc())
    , INSTRUCTION (parent, this, "INSTRUCTION", 32)
    , DATA (parent, this, "DATA", 32)
    , reset(parent, this, "reset")
    , nmi(parent, this, "nmi")
    , int_per(parent, this, "int_per")
    , int_ack(parent, this, "int_ack")
    {
    }

    m16c_r8c(tlmModule &parent, sc_module_name name, params p, Uns32 INSTRUCTIONWidth=32, Uns32 DATAWidth=32)
    : tlmProcessor(parent, getModel(), name, paramsForProc(p))
    , INSTRUCTION (parent, this, "INSTRUCTION", INSTRUCTIONWidth)
    , DATA (parent, this, "DATA", DATAWidth)
    , reset(parent, this, "reset")
    , nmi(parent, this, "nmi")
    , int_per(parent, this, "int_per")
    , int_ack(parent, this, "int_ack")
    {
    }

    void before_end_of_elaboration() {
        DATA.bindIfNotBound();
    }

    void dmi(bool on) {
        INSTRUCTION.dmi(on);
        DATA.dmi(on);
    }
}; /* class m16c_r8c */

