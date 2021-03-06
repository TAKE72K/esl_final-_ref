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

// MODEL IO:
//    Master Port rocount
//    Slave Port bport1

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class ring_oscillator : public tlmPeripheral
{
  private:
    const char *getModel() {
        const char *vlnv = opVLNVString (NULL, "safepower.ovpworld.org", "peripheral", "ring_oscillator", "1.0", OP_PERIPHERAL, 1);
        if(!vlnv) {
            opMessage("F", "TLM_FFM", "Failed to find model safepower.ovpworld.org/peripheral/ring_oscillator/1.0");
        }
        return vlnv;
    }

  public:
    tlmBusSlavePort bport1;
    tlmBusMasterPort       rocount;

    ring_oscillator(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , bport1(parent, this, "bport1", 0x1000) // static
        , rocount(parent, this, "rocount", 2)
    {
    }

    ring_oscillator(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , bport1(parent, this, "bport1", 0x1000) // static
        , rocount(parent, this, "rocount", 2)
    {
    }

    void before_end_of_elaboration() {
        rocount.bindIfNotBound();
    }
}; /* class ring_oscillator */

