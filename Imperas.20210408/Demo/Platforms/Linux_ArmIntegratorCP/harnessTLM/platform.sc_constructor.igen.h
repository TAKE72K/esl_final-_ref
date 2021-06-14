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
#include "arm.ovpworld.org/processor/arm/1.0/tlm/arm_Cortex-A9UP.igen.hpp"
#include "arm.ovpworld.org/peripheral/CoreModule9x6/1.0/tlm/pse.igen.hpp"
#include "arm.ovpworld.org/peripheral/IntICP/1.01/tlm/pse.igen.hpp"
#include "smsc.ovpworld.org/peripheral/LAN9118/1.0/tlm/pse.igen.hpp"
#include "arm.ovpworld.org/peripheral/IcpCounterTimer/1.0/tlm/pse.igen.hpp"
#include "arm.ovpworld.org/peripheral/IcpControl/1.0/tlm/pse.igen.hpp"
#include "arm.ovpworld.org/peripheral/DebugLedAndDipSwitch/1.0/tlm/pse.igen.hpp"
#include "arm.ovpworld.org/peripheral/KbPL050/1.0/tlm/pse.igen.hpp"
#include "arm.ovpworld.org/peripheral/RtcPL031/1.0/tlm/pse.igen.hpp"
#include "arm.ovpworld.org/peripheral/UartPL011/1.0/tlm/pse.igen.hpp"
#include "arm.ovpworld.org/peripheral/MmciPL181/1.0/tlm/pse.igen.hpp"
#include "arm.ovpworld.org/peripheral/LcdPL110/1.0/tlm/pse.igen.hpp"
#include "arm.ovpworld.org/peripheral/SmartLoaderArmLinux/1.0/tlm/pse.igen.hpp"


using namespace sc_core;
////////////////////////////////////////////////////////////////////////////////
//                            ArmIntegratorCP Class
////////////////////////////////////////////////////////////////////////////////

class ArmIntegratorCP : public sc_module {

  public:
    ArmIntegratorCP (sc_module_name name);

    tlmRam                ram1;
    tlmRam                ambaDummy;
    tlmModule             Platform;
    tlmDecoder            bus1;
    tlmDecoder            membus;
    arm_Cortex_A9UP       cpu;
    CoreModule9x6         cm;
    IntICP                pic1;
    IntICP                pic2;
    LAN9118               ethlan;
    IcpCounterTimer       pit;
    IcpControl            icp;
    DebugLedAndDipSwitch  ld1;
    KbPL050               kb1;
    KbPL050               ms1;
    RtcPL031              rtc;
    UartPL011             uart1;
    UartPL011             uart2;
    MmciPL181             mmci;
    LcdPL110              lcd;
    SmartLoaderArmLinux   smartLoader;


    params paramsForArmIntegratorCP() {
        params p;
        p.set("stoponcontrolc", true);
        return p;
    }

    params paramsForcpu() {
        params p;
        p.set("compatibility", "ISA");
        p.set("showHiddenRegs", true);
        p.set("simulateexceptions", true);
        p.set("enableimperasintercepts", true);
        p.set("endian", "little");
        p.set("mips", (double)200.0);
        return p;
    }

    params paramsForkb1() {
        params p;
        p.set("isMouse", true);
        p.set("grabDisable", true);
        return p;
    }

    params paramsForms1() {
        params p;
        p.set("isMouse", true);
        p.set("grabDisable", true);
        return p;
    }

    params paramsForuart1() {
        params p;
        p.set("variant", "ARM");
        p.set("outfile", "uart1.log");
        p.set("finishOnDisconnect", true);
        return p;
    }

    params paramsForuart2() {
        params p;
        p.set("variant", "ARM");
        p.set("outfile", "uart2.log");
        p.set("finishOnDisconnect", true);
        return p;
    }

    params paramsForlcd() {
        params p;
        p.set("busOffset", (Uns32)0x80000000);
        p.set("scanDelay", (Uns32)50000);
        return p;
    }
}; /* ArmIntegratorCP */

////////////////////////////////////////////////////////////////////////////////
//                         ArmIntegratorCP Constructor
////////////////////////////////////////////////////////////////////////////////

ArmIntegratorCP::ArmIntegratorCP (sc_module_name name)
    : sc_module (name)
    , ram1 (Platform, "ram1", 0x7ffffff)
    , ambaDummy (Platform, "ambaDummy", 0xfff)
    , Platform ("", paramsForArmIntegratorCP())
    , bus1(Platform, "bus1", 3, 17)
    , membus(Platform, "membus", 2, 2)
    , cpu ( Platform, "cpu", paramsForcpu(), 32, 32)
    , cm (Platform, "cm")
    , pic1 (Platform, "pic1")
    , pic2 (Platform, "pic2")
    , ethlan (Platform, "ethlan")
    , pit (Platform, "pit")
    , icp (Platform, "icp")
    , ld1 (Platform, "ld1")
    , kb1 (Platform, "kb1", paramsForkb1())
    , ms1 (Platform, "ms1", paramsForms1())
    , rtc (Platform, "rtc")
    , uart1 (Platform, "uart1", paramsForuart1())
    , uart2 (Platform, "uart2", paramsForuart2())
    , mmci (Platform, "mmci")
    , lcd (Platform, "lcd", paramsForlcd())
    , smartLoader (Platform, "smartLoader")
{

    // bus1 masters
    bus1.connect(cpu.INSTRUCTION);
    bus1.connect(cpu.DATA);
    bus1.connect(smartLoader.mport);

    // bus1 slaves
    bus1.connect(cm.bport1, 0x10000000, 0x10000fff); // Peripheral  (0)
    bus1.connect(pic1.bport1, 0x14000000, 0x14000fff); // Peripheral  (1)
    bus1.connect(pic2.bport1, 0xca000000, 0xca000fff); // Peripheral  (2)
    bus1.connect(ethlan.bport1, 0xc8000000, 0xc8000fff); // Peripheral  (3)
    bus1.connect(pit.bport1, 0x13000000, 0x13000fff); // Peripheral  (4)
    bus1.connect(icp.bport1, 0xcb000000, 0xcb00000f); // Peripheral  (5)
    bus1.connect(ld1.bport1, 0x1a000000, 0x1a000fff); // Peripheral  (6)
    bus1.connect(kb1.bport1, 0x18000000, 0x18000fff); // Peripheral  (7)
    bus1.connect(ms1.bport1, 0x19000000, 0x19000fff); // Peripheral  (8)
    bus1.connect(rtc.bport1, 0x15000000, 0x15000fff); // Peripheral  (9)
    bus1.connect(uart1.bport1, 0x16000000, 0x16000fff); // Peripheral  (10)
    bus1.connect(uart2.bport1, 0x17000000, 0x17000fff); // Peripheral  (11)
    bus1.connect(mmci.bport1, 0x1c000000, 0x1c000fff); // Peripheral  (12)
    bus1.connect(lcd.bport1, 0xc0000000, 0xc0000fff); // Peripheral  (13)
    bus1.connect(ambaDummy.sp1,0x1d000000, 0x1d000fff); // Memory (14)
    bus1.connect(membus, 0x0, 0x7ffffff, 0x0); // Bridge (15)
    bus1.connect(membus, 0x80000000, 0x87ffffff, 0x0); // Bridge (16)

    // membus slaves
    membus.connect(lcd.memory); // Dynamic peripheral (0)
    membus.connect(ram1.sp1,0x0, 0x7ffffff); // Memory (1)

    // Net connections
    pic1.irq(cpu.irq);
    pic1.fiq(cpu.fiq);
    uart1.irq(pic1.ir1);
    uart2.irq(pic1.ir2);
    kb1.irq(pic1.ir3);
    ms1.irq(pic1.ir4);
    pit.irq0(pic1.ir5);
    pit.irq1(pic1.ir6);
    pit.irq2(pic1.ir7);
    rtc.irq(pic1.ir8);
    mmci.irq0(pic1.ir23);
    mmci.irq1(pic1.ir24);

}
