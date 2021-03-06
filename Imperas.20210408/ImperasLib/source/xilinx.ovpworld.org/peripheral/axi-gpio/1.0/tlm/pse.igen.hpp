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
//    Slave Port sp1
//    Net output  gpio_out;
//    Net input  gpio_in;
//    Net output  gpio2_out;
//    Net input  gpio2_in;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class axi_gpio : public tlmPeripheral
{
  private:
    const char *getModel() {
        const char *vlnv = opVLNVString (NULL, "xilinx.ovpworld.org", "peripheral", "axi-gpio", "1.0", OP_PERIPHERAL, 1);
        if(!vlnv) {
            opMessage("F", "TLM_FFM", "Failed to find model xilinx.ovpworld.org/peripheral/axi-gpio/1.0");
        }
        return vlnv;
    }

  public:
    tlmBusSlavePort sp1;
    tlmNetOutputPort gpio_out;
    tlmNetInputPort gpio_in;
    tlmNetOutputPort gpio2_out;
    tlmNetInputPort gpio2_in;

    axi_gpio(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , sp1(parent, this, "sp1", 0x200) // static
        , gpio_out(parent, this, "gpio_out")
        , gpio_in(parent, this, "gpio_in")
        , gpio2_out(parent, this, "gpio2_out")
        , gpio2_in(parent, this, "gpio2_in")
    {
    }

    axi_gpio(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , sp1(parent, this, "sp1", 0x200) // static
        , gpio_out(parent, this, "gpio_out")
        , gpio_in(parent, this, "gpio_in")
        , gpio2_out(parent, this, "gpio2_out")
        , gpio2_in(parent, this, "gpio2_in")
    {
    }

}; /* class axi_gpio */

