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
//    Slave Port bport1
//    Net input  resetNet;
//    Net output  intOut0;
//    Net output  intOut1;
//    Net output  intOut2;
//    Net output  intOut3;
//    Net output  intOut4;
//    Net output  intOut5;
//    Net output  intOut6;
//    Net output  intOut7;
//    Net output  intOut8;
//    Net output  intOut9;
//    Net output  intOut10;
//    Net output  intOut11;
//    Net output  intOut12;
//    Net output  intOut13;
//    Net output  intOut14;
//    Net output  intOut15;
//    Net input  gpioin;
//    Net output  gpioout;
//    Net output  intSW0;
//    Net output  intBTN0;
//    Net output  intSW1;
//    Net output  intBTN1;
//    Net output  intSW2;
//    Net output  intBTN2;
//    Net output  intSW3;
//    Net output  intBTN3;

#pragma once

#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"
using namespace sc_core;
using namespace cw;

class gpio : public tlmPeripheral
{
  private:
    const char *getModel() {
        const char *vlnv = opVLNVString (NULL, "sifive.ovpworld.org", "peripheral", "gpio", "1.0", OP_PERIPHERAL, 1);
        if(!vlnv) {
            opMessage("F", "TLM_FFM", "Failed to find model sifive.ovpworld.org/peripheral/gpio/1.0");
        }
        return vlnv;
    }

  public:
    tlmBusSlavePort bport1;
    tlmNetInputPort resetNet;
    tlmNetOutputPort intOut0;
    tlmNetOutputPort intOut1;
    tlmNetOutputPort intOut2;
    tlmNetOutputPort intOut3;
    tlmNetOutputPort intOut4;
    tlmNetOutputPort intOut5;
    tlmNetOutputPort intOut6;
    tlmNetOutputPort intOut7;
    tlmNetOutputPort intOut8;
    tlmNetOutputPort intOut9;
    tlmNetOutputPort intOut10;
    tlmNetOutputPort intOut11;
    tlmNetOutputPort intOut12;
    tlmNetOutputPort intOut13;
    tlmNetOutputPort intOut14;
    tlmNetOutputPort intOut15;
    tlmNetInputPort gpioin;
    tlmNetOutputPort gpioout;
    tlmNetOutputPort intSW0;
    tlmNetOutputPort intBTN0;
    tlmNetOutputPort intSW1;
    tlmNetOutputPort intBTN1;
    tlmNetOutputPort intSW2;
    tlmNetOutputPort intBTN2;
    tlmNetOutputPort intSW3;
    tlmNetOutputPort intBTN3;

    gpio(tlmModule &parent, sc_module_name name)
        : tlmPeripheral(parent, getModel(), name)
        , bport1(parent, this, "bport1", 0x1000) // static
        , resetNet(parent, this, "resetNet")
        , intOut0(parent, this, "intOut0")
        , intOut1(parent, this, "intOut1")
        , intOut2(parent, this, "intOut2")
        , intOut3(parent, this, "intOut3")
        , intOut4(parent, this, "intOut4")
        , intOut5(parent, this, "intOut5")
        , intOut6(parent, this, "intOut6")
        , intOut7(parent, this, "intOut7")
        , intOut8(parent, this, "intOut8")
        , intOut9(parent, this, "intOut9")
        , intOut10(parent, this, "intOut10")
        , intOut11(parent, this, "intOut11")
        , intOut12(parent, this, "intOut12")
        , intOut13(parent, this, "intOut13")
        , intOut14(parent, this, "intOut14")
        , intOut15(parent, this, "intOut15")
        , gpioin(parent, this, "gpioin")
        , gpioout(parent, this, "gpioout")
        , intSW0(parent, this, "intSW0")
        , intBTN0(parent, this, "intBTN0")
        , intSW1(parent, this, "intSW1")
        , intBTN1(parent, this, "intBTN1")
        , intSW2(parent, this, "intSW2")
        , intBTN2(parent, this, "intBTN2")
        , intSW3(parent, this, "intSW3")
        , intBTN3(parent, this, "intBTN3")
    {
    }

    gpio(tlmModule &parent, sc_module_name name, params p)
        : tlmPeripheral(parent, getModel(), name, p)
        , bport1(parent, this, "bport1", 0x1000) // static
        , resetNet(parent, this, "resetNet")
        , intOut0(parent, this, "intOut0")
        , intOut1(parent, this, "intOut1")
        , intOut2(parent, this, "intOut2")
        , intOut3(parent, this, "intOut3")
        , intOut4(parent, this, "intOut4")
        , intOut5(parent, this, "intOut5")
        , intOut6(parent, this, "intOut6")
        , intOut7(parent, this, "intOut7")
        , intOut8(parent, this, "intOut8")
        , intOut9(parent, this, "intOut9")
        , intOut10(parent, this, "intOut10")
        , intOut11(parent, this, "intOut11")
        , intOut12(parent, this, "intOut12")
        , intOut13(parent, this, "intOut13")
        , intOut14(parent, this, "intOut14")
        , intOut15(parent, this, "intOut15")
        , gpioin(parent, this, "gpioin")
        , gpioout(parent, this, "gpioout")
        , intSW0(parent, this, "intSW0")
        , intBTN0(parent, this, "intBTN0")
        , intSW1(parent, this, "intSW1")
        , intBTN1(parent, this, "intBTN1")
        , intSW2(parent, this, "intSW2")
        , intBTN2(parent, this, "intBTN2")
        , intSW3(parent, this, "intSW3")
        , intBTN3(parent, this, "intBTN3")
    {
    }

}; /* class gpio */

