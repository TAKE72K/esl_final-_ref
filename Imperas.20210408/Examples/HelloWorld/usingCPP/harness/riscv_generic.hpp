/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */



#include "op/op.hpp"

class riscv : public processor {

  public:
     riscv (module &parent, const char *name, params p)
         : processor(parent, opVLNVString(0,"riscv.ovpworld.org", "processor", "riscv", "1.0", OP_PROCESSOR, 1), name, p) {
     }

};
