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

// This file constructs the platform.
// This file should NOT need to be edited.

#include "tlm/tlmMemory.hpp"
#include "tlm/tlmDecoder.hpp"
#include "mips.ovpworld.org/processor/mips32_r1r5/1.0/tlm/mips32_r1r5_34Kc.igen.hpp"
#include "mips.ovpworld.org/peripheral/SmartLoaderLinux/1.0/tlm/pse.igen.hpp"
#include "marvell.ovpworld.org/peripheral/GT6412x/1.0/tlm/pse.igen.hpp"
#include "intel.ovpworld.org/peripheral/82371EB/1.0/tlm/pse.igen.hpp"
#include "intel.ovpworld.org/peripheral/PciIDE/1.0/tlm/pse.igen.hpp"
#include "intel.ovpworld.org/peripheral/PciPM/1.0/tlm/pse.igen.hpp"
#include "amd.ovpworld.org/peripheral/79C970/1.0/tlm/pse.igen.hpp"
#include "intel.ovpworld.org/peripheral/8259A/1.0/tlm/pse.igen.hpp"
#include "ovpworld.org/peripheral/DynamicBridge/1.0/tlm/pse.igen.hpp"
#include "ovpworld.org/peripheral/SerInt/1.0/tlm/pse.igen.hpp"
#include "cirrus.ovpworld.org/peripheral/GD5446/1.0/tlm/pse.igen.hpp"
#include "intel.ovpworld.org/peripheral/Ps2Control/1.0/tlm/pse.igen.hpp"
#include "intel.ovpworld.org/peripheral/8253/1.0/tlm/pse.igen.hpp"
#include "motorola.ovpworld.org/peripheral/MC146818/1.0/tlm/pse.igen.hpp"
#include "national.ovpworld.org/peripheral/16550/1.0/tlm/pse.igen.hpp"
#include "intel.ovpworld.org/peripheral/82077AA/1.0/tlm/pse.igen.hpp"
#include "mips.ovpworld.org/peripheral/16450C/1.0/tlm/pse.igen.hpp"
#include "mips.ovpworld.org/peripheral/MaltaFPGA/1.0/tlm/pse.igen.hpp"
#include "ovpworld.org/peripheral/Alpha2x16Display/1.0/tlm/pse.igen.hpp"


using namespace sc_core;
////////////////////////////////////////////////////////////////////////////////
//                               MipsMalta Class
////////////////////////////////////////////////////////////////////////////////

class MipsMalta : public sc_module {

  public:
    MipsMalta (sc_module_name name);

    tlmRam                Core_Board_SDRAM;
    tlmRam                Core_Board_SDRAM2;
    tlmRam                Monitor_Flash;
    tlmRam                vgaMemRegion;
    tlmModule             Platform;
    tlmDecoder            bus1;
    tlmDecoder            busPCI;
    tlmDecoder            busPCIReMap;
    tlmDecoder            PCIconfigBus;
    tlmDecoder            PCIackBus;
    tlmDecoder            cascadeBus;
    tlmDecoder            flashBus;
    mips32_r1r5_34Kc      mipsle1;
    SmartLoaderLinux      Core_Board_SDRAM_promInit;
    GT6412x               sysControl;
    _82371EB              PIIX4;
    PciIDE                PIIX4_IDE;
    PciPM                 PCI_PM;
    _79C970               PCI_NET;
    _8259A                intCtrlMaster;
    DynamicBridge         pciBrD_intCtrlMaster_io;
    DynamicBridge         pciBrD_intCtrlMaster_elcr;
    _8259A                intCtrlSlave;
    DynamicBridge         pciBrD_intCtrlSlave_io;
    DynamicBridge         pciBrD_intCtrlSlave_elcr;
    SerInt                __SUPERIO_REG_;
    DynamicBridge         pciBrD__SUPERIO_REG__bport1;
    GD5446                vga;
    DynamicBridge         pciBrD_vga_config;
    Ps2Control            ps2if;
    DynamicBridge         pciBrD_ps2if_config;
    _8253                 pit;
    DynamicBridge         pciBrD_pit_bport1;
    MC146818              rtc;
    DynamicBridge         pciBrD_rtc_busPort;
    _16550                uartTTY0;
    DynamicBridge         pciBrD_uartTTY0_bport1;
    _16550                uartTTY1;
    DynamicBridge         pciBrD_uartTTY1_bport1;
    _82077AA              fd0;
    DynamicBridge         pciBrD_fd0_bport1;
    _16450C               uartCBUS;
    MaltaFPGA             maltaFpga;
    Alpha2x16Display      alphaDisplay;
    DynamicBridge         pciBrD_alphaDisplay_busPort;


    params paramsForMipsMalta() {
        params p;
        p.set("stoponcontrolc", true);
        return p;
    }

    params paramsFormipsle1() {
        params p;
        p.set("vectoredinterrupt", true);
        p.set("config1MMUSizeM1", (Uns32)63);
        p.set("simulateexceptions", true);
        p.set("endian", "little");
        p.set("mips", (double)100.0);
        return p;
    }

    params paramsForPIIX4() {
        params p;
        p.set("PCIslot", (Uns32)10);
        return p;
    }

    params paramsForPIIX4_IDE() {
        params p;
        p.set("PCIslot", (Uns32)10);
        p.set("PCIfunction", (Uns32)1);
        return p;
    }

    params paramsForPCI_PM() {
        params p;
        p.set("PCIslot", (Uns32)10);
        p.set("PCIfunction", (Uns32)3);
        return p;
    }

    params paramsForPCI_NET() {
        params p;
        p.set("PCIslot", (Uns32)11);
        p.set("PCIfunction", (Uns32)0);
        return p;
    }

    params paramsForintCtrlMaster() {
        params p;
        p.set("spen", "master");
        return p;
    }

    params paramsForpciBrD_intCtrlMaster_io() {
        params p;
        p.set("spLoAddress", (Uns64)402653216ULL);
        p.set("mpLoAddress", (Uns64)402653216ULL);
        p.set("portSize", (Uns64)2ULL);
        p.set("enableBridge", true);
        return p;
    }

    params paramsForpciBrD_intCtrlMaster_elcr() {
        params p;
        p.set("spLoAddress", (Uns64)402654416ULL);
        p.set("mpLoAddress", (Uns64)402654416ULL);
        p.set("portSize", (Uns64)1ULL);
        p.set("enableBridge", true);
        return p;
    }

    params paramsForintCtrlSlave() {
        params p;
        p.set("spen", "slave");
        return p;
    }

    params paramsForpciBrD_intCtrlSlave_io() {
        params p;
        p.set("spLoAddress", (Uns64)402653344ULL);
        p.set("mpLoAddress", (Uns64)402653344ULL);
        p.set("portSize", (Uns64)2ULL);
        p.set("enableBridge", true);
        return p;
    }

    params paramsForpciBrD_intCtrlSlave_elcr() {
        params p;
        p.set("spLoAddress", (Uns64)402654417ULL);
        p.set("mpLoAddress", (Uns64)402654417ULL);
        p.set("portSize", (Uns64)1ULL);
        p.set("enableBridge", true);
        return p;
    }

    params paramsForpciBrD__SUPERIO_REG__bport1() {
        params p;
        p.set("spLoAddress", (Uns64)402653360ULL);
        p.set("mpLoAddress", (Uns64)402653360ULL);
        p.set("portSize", (Uns64)4ULL);
        p.set("enableBridge", true);
        return p;
    }

    params paramsForvga() {
        params p;
        p.set("scanDelay", (Uns32)50000);
        p.set("PCIslot", (Uns32)18);
        p.set("title", "Imperas MIPS32 Malta");
        return p;
    }

    params paramsForpciBrD_vga_config() {
        params p;
        p.set("spLoAddress", (Uns64)402654128ULL);
        p.set("mpLoAddress", (Uns64)402654128ULL);
        p.set("portSize", (Uns64)48ULL);
        p.set("enableBridge", true);
        return p;
    }

    params paramsForps2if() {
        params p;
        p.set("pollPeriod", (Uns32)50000);
        p.set("grabDisable", true);
        return p;
    }

    params paramsForpciBrD_ps2if_config() {
        params p;
        p.set("spLoAddress", (Uns64)402653280ULL);
        p.set("mpLoAddress", (Uns64)402653280ULL);
        p.set("portSize", (Uns64)8ULL);
        p.set("enableBridge", true);
        return p;
    }

    params paramsForpciBrD_pit_bport1() {
        params p;
        p.set("spLoAddress", (Uns64)402653248ULL);
        p.set("mpLoAddress", (Uns64)402653248ULL);
        p.set("portSize", (Uns64)4ULL);
        p.set("enableBridge", true);
        return p;
    }

    params paramsForpciBrD_rtc_busPort() {
        params p;
        p.set("spLoAddress", (Uns64)402653296ULL);
        p.set("mpLoAddress", (Uns64)402653296ULL);
        p.set("portSize", (Uns64)2ULL);
        p.set("enableBridge", true);
        return p;
    }

    params paramsForuartTTY0() {
        params p;
        p.set("outfile", "uartTTY0.log");
        p.set("finishOnDisconnect", true);
        return p;
    }

    params paramsForpciBrD_uartTTY0_bport1() {
        params p;
        p.set("spLoAddress", (Uns64)402654200ULL);
        p.set("mpLoAddress", (Uns64)402654200ULL);
        p.set("portSize", (Uns64)8ULL);
        p.set("enableBridge", true);
        return p;
    }

    params paramsForuartTTY1() {
        params p;
        p.set("outfile", "uartTTY1.log");
        p.set("finishOnDisconnect", true);
        return p;
    }

    params paramsForpciBrD_uartTTY1_bport1() {
        params p;
        p.set("spLoAddress", (Uns64)402653944ULL);
        p.set("mpLoAddress", (Uns64)402653944ULL);
        p.set("portSize", (Uns64)8ULL);
        p.set("enableBridge", true);
        return p;
    }

    params paramsForpciBrD_fd0_bport1() {
        params p;
        p.set("spLoAddress", (Uns64)402654192ULL);
        p.set("mpLoAddress", (Uns64)402654192ULL);
        p.set("portSize", (Uns64)8ULL);
        p.set("enableBridge", true);
        return p;
    }

    params paramsForuartCBUS() {
        params p;
        p.set("outfile", "uartCBUS.log");
        return p;
    }

    params paramsFormaltaFpga() {
        params p;
        p.set("stoponsoftreset", true);
        return p;
    }

    params paramsForpciBrD_alphaDisplay_busPort() {
        params p;
        p.set("spLoAddress", (Uns64)402653440ULL);
        p.set("mpLoAddress", (Uns64)402653440ULL);
        p.set("portSize", (Uns64)4ULL);
        p.set("enableBridge", true);
        return p;
    }
}; /* MipsMalta */

////////////////////////////////////////////////////////////////////////////////
//                            MipsMalta Constructor
////////////////////////////////////////////////////////////////////////////////

MipsMalta::MipsMalta (sc_module_name name)
    : sc_module (name)
    , Core_Board_SDRAM (Platform, "Core_Board_SDRAM", 0xfffffff)
    , Core_Board_SDRAM2 (Platform, "Core_Board_SDRAM2", 0x3fffffff)
    , Monitor_Flash (Platform, "Monitor_Flash", 0x3fffff)
    , vgaMemRegion (Platform, "vgaMemRegion", 0x1ffff)
    , Platform ("", paramsForMipsMalta())
    , bus1(Platform, "bus1", 5, 11)
    , busPCI(Platform, "busPCI", 3, 20)
    , busPCIReMap(Platform, "busPCIReMap", 13, 13)
    , PCIconfigBus(Platform, "PCIconfigBus", 1, 6)
    , PCIackBus(Platform, "PCIackBus", 1, 1)
    , cascadeBus(Platform, "cascadeBus", 1, 1)
    , flashBus(Platform, "flashBus", 3, 1)
    , mipsle1 ( Platform, "mipsle1", paramsFormipsle1(), 32, 32)
    , Core_Board_SDRAM_promInit (Platform, "Core_Board_SDRAM_promInit")
    , sysControl (Platform, "sysControl")
    , PIIX4 (Platform, "PIIX4", paramsForPIIX4())
    , PIIX4_IDE (Platform, "PIIX4_IDE", paramsForPIIX4_IDE())
    , PCI_PM (Platform, "PCI_PM", paramsForPCI_PM())
    , PCI_NET (Platform, "PCI_NET", paramsForPCI_NET())
    , intCtrlMaster (Platform, "intCtrlMaster", paramsForintCtrlMaster())
    , pciBrD_intCtrlMaster_io (Platform, "pciBrD_intCtrlMaster_io", paramsForpciBrD_intCtrlMaster_io())
    , pciBrD_intCtrlMaster_elcr (Platform, "pciBrD_intCtrlMaster_elcr", paramsForpciBrD_intCtrlMaster_elcr())
    , intCtrlSlave (Platform, "intCtrlSlave", paramsForintCtrlSlave())
    , pciBrD_intCtrlSlave_io (Platform, "pciBrD_intCtrlSlave_io", paramsForpciBrD_intCtrlSlave_io())
    , pciBrD_intCtrlSlave_elcr (Platform, "pciBrD_intCtrlSlave_elcr", paramsForpciBrD_intCtrlSlave_elcr())
    , __SUPERIO_REG_ (Platform, "__SUPERIO_REG_")
    , pciBrD__SUPERIO_REG__bport1 (Platform, "pciBrD__SUPERIO_REG__bport1", paramsForpciBrD__SUPERIO_REG__bport1())
    , vga (Platform, "vga", paramsForvga())
    , pciBrD_vga_config (Platform, "pciBrD_vga_config", paramsForpciBrD_vga_config())
    , ps2if (Platform, "ps2if", paramsForps2if())
    , pciBrD_ps2if_config (Platform, "pciBrD_ps2if_config", paramsForpciBrD_ps2if_config())
    , pit (Platform, "pit")
    , pciBrD_pit_bport1 (Platform, "pciBrD_pit_bport1", paramsForpciBrD_pit_bport1())
    , rtc (Platform, "rtc")
    , pciBrD_rtc_busPort (Platform, "pciBrD_rtc_busPort", paramsForpciBrD_rtc_busPort())
    , uartTTY0 (Platform, "uartTTY0", paramsForuartTTY0())
    , pciBrD_uartTTY0_bport1 (Platform, "pciBrD_uartTTY0_bport1", paramsForpciBrD_uartTTY0_bport1())
    , uartTTY1 (Platform, "uartTTY1", paramsForuartTTY1())
    , pciBrD_uartTTY1_bport1 (Platform, "pciBrD_uartTTY1_bport1", paramsForpciBrD_uartTTY1_bport1())
    , fd0 (Platform, "fd0")
    , pciBrD_fd0_bport1 (Platform, "pciBrD_fd0_bport1", paramsForpciBrD_fd0_bport1())
    , uartCBUS (Platform, "uartCBUS", paramsForuartCBUS())
    , maltaFpga (Platform, "maltaFpga", paramsFormaltaFpga())
    , alphaDisplay (Platform, "alphaDisplay")
    , pciBrD_alphaDisplay_busPort (Platform, "pciBrD_alphaDisplay_busPort", paramsForpciBrD_alphaDisplay_busPort())
{

    // bus1 masters
    bus1.connect(mipsle1.INSTRUCTION);
    bus1.connect(mipsle1.DATA);
    bus1.connect(Core_Board_SDRAM_promInit.mport);

    // bus1 slaves
    bus1.connect(Core_Board_SDRAM_promInit.idport, 0x1fc00010, 0x1fc00013); // Peripheral  (0)
    bus1.connect(uartCBUS.bport1, 0x1f000900, 0x1f00093f); // Peripheral  (1)
    bus1.connect(maltaFpga.busPort1, 0x1f000000, 0x1f0008ff); // Peripheral  (2)
    bus1.connect(maltaFpga.busPort2, 0x1f000a00, 0x1f000fff); // Peripheral  (3)
    bus1.connect(Core_Board_SDRAM.sp1,0x0, 0xfffffff); // Memory (4)
    bus1.connect(Core_Board_SDRAM2.sp1,0x20000000, 0x5fffffff); // Memory (5)
    bus1.connect(busPCI, 0x10000000, 0x1bffffff, 0x10000000); // Bridge (6)
    bus1.connect(flashBus, 0x1e000000, 0x1e3fffff, 0x1e000000); // Bridge (7)
    bus1.connect(flashBus, 0x1fc00000, 0x1fc0000f, 0x1e000000); // Bridge (8)
    bus1.connect(flashBus, 0x1fc00014, 0x1fffffff, 0x1e000014); // Bridge (9)
    bus1.connect(bus1, 0x80000000, 0xffffffff, 0x0); // Bridge (10)

    // busPCI masters
    busPCI.connect(PIIX4_IDE.dmaPort);
    busPCI.connect(PCI_NET.dmaPort);

    // busPCI slaves
    busPCI.connect(sysControl.busPort); // Dynamic peripheral (0)
    busPCI.connect(PIIX4_IDE.busPort); // Dynamic peripheral (1)
    busPCI.connect(PCI_PM.busPort); // Dynamic peripheral (2)
    busPCI.connect(PCI_NET.busPort); // Dynamic peripheral (3)
    busPCI.connect(pciBrD_intCtrlMaster_io.sp); // Dynamic peripheral (4)
    busPCI.connect(pciBrD_intCtrlMaster_elcr.sp); // Dynamic peripheral (5)
    busPCI.connect(pciBrD_intCtrlSlave_io.sp); // Dynamic peripheral (6)
    busPCI.connect(pciBrD_intCtrlSlave_elcr.sp); // Dynamic peripheral (7)
    busPCI.connect(pciBrD__SUPERIO_REG__bport1.sp); // Dynamic peripheral (8)
    busPCI.connect(vga.memory); // Dynamic peripheral (9)
    busPCI.connect(pciBrD_vga_config.sp); // Dynamic peripheral (10)
    busPCI.connect(pciBrD_ps2if_config.sp); // Dynamic peripheral (11)
    busPCI.connect(pciBrD_pit_bport1.sp); // Dynamic peripheral (12)
    busPCI.connect(pciBrD_rtc_busPort.sp); // Dynamic peripheral (13)
    busPCI.connect(pciBrD_uartTTY0_bport1.sp); // Dynamic peripheral (14)
    busPCI.connect(pciBrD_uartTTY1_bport1.sp); // Dynamic peripheral (15)
    busPCI.connect(pciBrD_fd0_bport1.sp); // Dynamic peripheral (16)
    busPCI.connect(pciBrD_alphaDisplay_busPort.sp); // Dynamic peripheral (17)
    busPCI.connect(vgaMemRegion.sp1,0x100a0000, 0x100bffff); // Memory (18)
    busPCI.connect(bus1, 0x0, 0xfffffff, 0x0); // Bridge (19)

    // busPCIReMap masters
    busPCIReMap.connect(pciBrD_intCtrlMaster_io.mp);
    busPCIReMap.connect(pciBrD_intCtrlMaster_elcr.mp);
    busPCIReMap.connect(pciBrD_intCtrlSlave_io.mp);
    busPCIReMap.connect(pciBrD_intCtrlSlave_elcr.mp);
    busPCIReMap.connect(pciBrD__SUPERIO_REG__bport1.mp);
    busPCIReMap.connect(pciBrD_vga_config.mp);
    busPCIReMap.connect(pciBrD_ps2if_config.mp);
    busPCIReMap.connect(pciBrD_pit_bport1.mp);
    busPCIReMap.connect(pciBrD_rtc_busPort.mp);
    busPCIReMap.connect(pciBrD_uartTTY0_bport1.mp);
    busPCIReMap.connect(pciBrD_uartTTY1_bport1.mp);
    busPCIReMap.connect(pciBrD_fd0_bport1.mp);
    busPCIReMap.connect(pciBrD_alphaDisplay_busPort.mp);

    // busPCIReMap slaves
    busPCIReMap.connect(intCtrlMaster.io, 0x18000020, 0x18000021); // Peripheral  (0)
    busPCIReMap.connect(intCtrlMaster.elcr, 0x180004d0, 0x180004d0); // Peripheral  (1)
    busPCIReMap.connect(intCtrlSlave.io, 0x180000a0, 0x180000a1); // Peripheral  (2)
    busPCIReMap.connect(intCtrlSlave.elcr, 0x180004d1, 0x180004d1); // Peripheral  (3)
    busPCIReMap.connect(__SUPERIO_REG_.bport1, 0x180000b0, 0x180000b3); // Peripheral  (4)
    busPCIReMap.connect(vga.config, 0x180003b0, 0x180003df); // Peripheral  (5)
    busPCIReMap.connect(ps2if.config, 0x18000060, 0x18000067); // Peripheral  (6)
    busPCIReMap.connect(pit.bport1, 0x18000040, 0x18000043); // Peripheral  (7)
    busPCIReMap.connect(rtc.busPort, 0x18000070, 0x18000071); // Peripheral  (8)
    busPCIReMap.connect(uartTTY0.bport1, 0x180003f8, 0x180003ff); // Peripheral  (9)
    busPCIReMap.connect(uartTTY1.bport1, 0x180002f8, 0x180002ff); // Peripheral  (10)
    busPCIReMap.connect(fd0.bport1, 0x180003f0, 0x180003f7); // Peripheral  (11)
    busPCIReMap.connect(alphaDisplay.busPort, 0x18000100, 0x18000103); // Peripheral  (12)

    // PCIconfigBus masters
    PCIconfigBus.connect(sysControl.PCIconfigM);

    // PCIconfigBus slaves
    PCIconfigBus.connect(sysControl.PCIconfig); // Dynamic peripheral (0)
    PCIconfigBus.connect(PIIX4.PCIconfig); // Dynamic peripheral (1)
    PCIconfigBus.connect(PIIX4_IDE.PCIconfig); // Dynamic peripheral (2)
    PCIconfigBus.connect(PCI_PM.PCIconfig); // Dynamic peripheral (3)
    PCIconfigBus.connect(PCI_NET.PCIconfig); // Dynamic peripheral (4)
    PCIconfigBus.connect(vga.PCIconfig); // Dynamic peripheral (5)

    // PCIackBus masters
    PCIackBus.connect(sysControl.PCIackM);

    // PCIackBus slaves
    PCIackBus.connect(intCtrlMaster.PCIackS, 0x0, 0x0); // Peripheral  (0)

    // cascadeBus masters
    cascadeBus.connect(intCtrlMaster.cascade);

    // cascadeBus slaves
    cascadeBus.connect(intCtrlSlave.PCIackS, 0x2, 0x2); // Peripheral  (0)

    // flashBus slaves
    flashBus.connect(Monitor_Flash.sp1,0x1e000000, 0x1e3fffff); // Memory (0)

    // Net connections
    ps2if.kbdInterrupt(intCtrlMaster.ir1);
    uartTTY1.intOut(intCtrlMaster.ir3);
    uartTTY0.intOut(intCtrlMaster.ir4);
    rtc.timerInt(intCtrlSlave.ir0);
    PCI_NET.intOut0(intCtrlSlave.ir2);
    ps2if.mouseInterrupt(intCtrlSlave.ir4);
    PIIX4_IDE.intOut0(intCtrlSlave.ir6);
    PIIX4_IDE.intOut1(intCtrlSlave.ir7);
    intCtrlMaster.intp(mipsle1.hwint0);
    intCtrlSlave.intp(intCtrlMaster.ir2);

}
