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

////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                             Version 20210408.0
//
////////////////////////////////////////////////////////////////////////////////

#define UNUSED   __attribute__((unused))

// instantiate module components
static OP_CONSTRUCT_FN(instantiateComponents) {

    optDocNodeP doc1_node = opModuleDocSectionAdd(mi, "Licensing");
    opDocTextAdd(doc1_node, "Open Source Apache 2.0");
    optDocNodeP doc_11_node = opModuleDocSectionAdd(mi, "Description");
    opDocTextAdd(doc_11_node, "Example platform to instance RISCV RV32I processor core with extensions M and SU. Peripherals and memory address layout to boot pre-compiled FreeRTOS operating system.");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_21_node, "https://github.com/RISCV-on-Microsemi-FPGA/FreeRTOS/tree/master/FreeRTOS_on_Mi-V_Processor");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_31_node, "Created to executed the specific software");


    // Bus bus0

    optBusP bus0_b = opBusNew(mi, "bus0", 32, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP eip_n = opNetNew(mi, "eip", 0, 0);
    optNetP MTimerInterrupt_n = opNetNew(mi, "MTimerInterrupt", 0, 0);
    optNetP MSWInterrupt_n = opNetNew(mi, "MSWInterrupt", 0, 0);

    // Processor cpu0

    const char *cpu0_path = opVLNVString(
        0, // use the default VLNV path
        "riscv.ovpworld.org",
        "processor",
        "riscv",
        "1.0",
        OP_PROCESSOR,
        1   // report errors
    );

    opProcessorNew(
        mi,
        cpu0_path,
        "cpu0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "INSTRUCTION"),
                OP_BUS_CONNECT(bus0_b, "DATA")
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(eip_n, "MExternalInterrupt"),
                OP_NET_CONNECT(MTimerInterrupt_n, "MTimerInterrupt"),
                OP_NET_CONNECT(MSWInterrupt_n, "MSWInterrupt")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_DOUBLE_SET("mips", 50)
            ,OP_PARAM_ENUM_SET("variant", "RVB32I")
            ,OP_PARAM_STRING_SET("add_Extensions", "MSU")
        )
    );


    // Memory nvram

    opMemoryNew(
        mi,
        "nvram",
        OP_PRIV_RWX,
        (0x6003ffffULL) - (0x60000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x60000000ULL, .addrHi=0x6003ffffULL)
            )
        ),
        0
    );

    // Memory ddr

    opMemoryNew(
        mi,
        "ddr",
        OP_PRIV_RWX,
        (0x8fffffffULL) - (0x80000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x80000000ULL, .addrHi=0x8fffffffULL)
            )
        ),
        0
    );

    // PSE uart0

    const char *uart0_path = opVLNVString(
        0, // use the default VLNV path
        "microsemi.ovpworld.org",
        "peripheral",
        "CoreUARTapb",
        "1.0",
        OP_PERIPHERAL,
        1   // report errors
    );

    opPeripheralNew(
        mi,
        uart0_path,
        "uart0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "port0", .slave=1, .addrLo=0x70001000ULL, .addrHi=0x70001017ULL)
            )
        ),
        0
    );

    // PSE plic0

    const char *plic0_path = opVLNVString(
        0, // use the default VLNV path
        "riscv.ovpworld.org",
        "peripheral",
        "PLIC",
        "1.0",
        OP_PERIPHERAL,
        1   // report errors
    );

    opPeripheralNew(
        mi,
        plic0_path,
        "plic0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "port0", .slave=1, .addrLo=0x40000000ULL, .addrHi=0x43ffffffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(eip_n, "irqT0")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("num_sources", 256)
            ,OP_PARAM_UNS32_SET("num_targets", 1)
        )
    );

    // PSE prci0

    const char *prci0_path = opVLNVString(
        0, // use the default VLNV path
        "riscv.ovpworld.org",
        "peripheral",
        "CLINT",
        "1.0",
        OP_PERIPHERAL,
        1   // report errors
    );

    opPeripheralNew(
        mi,
        prci0_path,
        "prci0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "port0", .slave=1, .addrLo=0x44000000ULL, .addrHi=0x4400bfffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(MTimerInterrupt_n, "MTimerInterrupt0"),
                OP_NET_CONNECT(MSWInterrupt_n, "MSWInterrupt0")
            )
        ),
        OP_PARAMS(
             OP_PARAM_DOUBLE_SET("clockMHz", 1.0)
        )
    );

}

optModuleAttr modelAttrs = {
    .versionString        = OP_VERSION,
    .type                 = OP_MODULE,
    .name                 = MODULE_NAME,
    .objectSize           = sizeof(optModuleObject),
    .releaseStatus        = OP_OVP,
    .purpose              = OP_PP_MODULE,
    .visibility           = OP_VISIBLE,
    .vlnv          = {
        .vendor  = "imperas.ovpworld.org",
        .library = "module",
        .name    = "RiscvRV32FreeRTOS",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};
