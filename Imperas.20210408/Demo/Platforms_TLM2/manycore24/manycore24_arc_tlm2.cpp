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
//                          Fri Jul 12 16:14:50 2019
//
////////////////////////////////////////////////////////////////////////////////

#include "tlm.h"
#include "tlm/tlmModule.hpp"
#include "tlm/tlmDecoder.hpp"
#include "tlm/tlmMemory.hpp"
#include "arc.ovpworld.org/processor/arc/1.0/tlm/arc_700.igen.hpp"


using namespace sc_core;
////////////////////////////////////////////////////////////////////////////////
//                      manycore24_arc_tlm2 Class
////////////////////////////////////////////////////////////////////////////////

class manycore24_arc_tlm2 : public sc_module {

  public:
    manycore24_arc_tlm2 (sc_module_name name);

    tlmRam                ram00;
    tlmRam                ram01;
    tlmRam                ram10;
    tlmRam                ram11;
    tlmRam                ram20;
    tlmRam                ram21;
    tlmRam                ram30;
    tlmRam                ram31;
    tlmRam                ram40;
    tlmRam                ram41;
    tlmRam                ram50;
    tlmRam                ram51;
    tlmRam                ram60;
    tlmRam                ram61;
    tlmRam                ram70;
    tlmRam                ram71;
    tlmRam                ram80;
    tlmRam                ram81;
    tlmRam                ram90;
    tlmRam                ram91;
    tlmRam                ram100;
    tlmRam                ram101;
    tlmRam                ram110;
    tlmRam                ram111;
    tlmRam                ram120;
    tlmRam                ram121;
    tlmRam                ram130;
    tlmRam                ram131;
    tlmRam                ram140;
    tlmRam                ram141;
    tlmRam                ram150;
    tlmRam                ram151;
    tlmRam                ram160;
    tlmRam                ram161;
    tlmRam                ram170;
    tlmRam                ram171;
    tlmRam                ram180;
    tlmRam                ram181;
    tlmRam                ram190;
    tlmRam                ram191;
    tlmRam                ram200;
    tlmRam                ram201;
    tlmRam                ram210;
    tlmRam                ram211;
    tlmRam                ram220;
    tlmRam                ram221;
    tlmRam                ram230;
    tlmRam                ram231;

    tlmModule             Platform;
    tlmDecoder            bus0;
    tlmDecoder            bus1;
    tlmDecoder            bus2;
    tlmDecoder            bus3;
    tlmDecoder            bus4;
    tlmDecoder            bus5;
    tlmDecoder            bus6;
    tlmDecoder            bus7;
    tlmDecoder            bus8;
    tlmDecoder            bus9;
    tlmDecoder            bus10;
    tlmDecoder            bus11;
    tlmDecoder            bus12;
    tlmDecoder            bus13;
    tlmDecoder            bus14;
    tlmDecoder            bus15;
    tlmDecoder            bus16;
    tlmDecoder            bus17;
    tlmDecoder            bus18;
    tlmDecoder            bus19;
    tlmDecoder            bus20;
    tlmDecoder            bus21;
    tlmDecoder            bus22;
    tlmDecoder            bus23;

    arc_700               cpu0;
    arc_700               cpu1;
    arc_700               cpu2;
    arc_700               cpu3;
    arc_700               cpu4;
    arc_700               cpu5;
    arc_700               cpu6;
    arc_700               cpu7;
    arc_700               cpu8;
    arc_700               cpu9;
    arc_700               cpu10;
    arc_700               cpu11;
    arc_700               cpu12;
    arc_700               cpu13;
    arc_700               cpu14;
    arc_700               cpu15;
    arc_700               cpu16;
    arc_700               cpu17;
    arc_700               cpu18;
    arc_700               cpu19;
    arc_700               cpu20;
    arc_700               cpu21;
    arc_700               cpu22;
    arc_700               cpu23;

    params paramsForPlatform() {
        params p;
        p.set(OP_FP_VERBOSE, true);
        p.set(OP_FP_STOPONCONTROLC, true);
        return p;
    }

    params paramsForcpu0() {
        params p;
        p.set("format", "metaware");
        p.set("end-on-halt", (bool)1);
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }

    params paramsForcpu1() {
        params p;
        p.set("format", "metaware");
        p.set("end-on-halt", (bool)1);
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }

    params paramsForcpu2() {
        params p;
        p.set("format", "metaware");
        p.set("end-on-halt", (bool)1);
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }

    params paramsForcpu3() {
        params p;
        p.set("format", "metaware");
        p.set("end-on-halt", (bool)1);
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }

    params paramsForcpu4() {
        params p;
        p.set("format", "metaware");
        p.set("end-on-halt", (bool)1);
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }

    params paramsForcpu5() {
        params p;
        p.set("format", "metaware");
        p.set("end-on-halt", (bool)1);
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }

    params paramsForcpu6() {
        params p;
        p.set("format", "metaware");
        p.set("end-on-halt", (bool)1);
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }

    params paramsForcpu7() {
        params p;
        p.set("format", "metaware");
        p.set("end-on-halt", (bool)1);
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }

    params paramsForcpu8() {
        params p;
        p.set("format", "metaware");
        p.set("end-on-halt", (bool)1);
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }

    params paramsForcpu9() {
        params p;
        p.set("format", "metaware");
        p.set("end-on-halt", (bool)1);
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }

    params paramsForcpu10() {
        params p;
        p.set("format", "metaware");
        p.set("end-on-halt", (bool)1);
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }

    params paramsForcpu11() {
        params p;
        p.set("format", "metaware");
        p.set("end-on-halt", (bool)1);
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }

    params paramsForcpu12() {
        params p;
        p.set("format", "metaware");
        p.set("end-on-halt", (bool)1);
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }

    params paramsForcpu13() {
        params p;
        p.set("format", "metaware");
        p.set("end-on-halt", (bool)1);
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }

    params paramsForcpu14() {
        params p;
        p.set("format", "metaware");
        p.set("end-on-halt", (bool)1);
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }

    params paramsForcpu15() {
        params p;
        p.set("format", "metaware");
        p.set("end-on-halt", (bool)1);
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }

    params paramsForcpu16() {
        params p;
        p.set("format", "metaware");
        p.set("end-on-halt", (bool)1);
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }

    params paramsForcpu17() {
        params p;
        p.set("format", "metaware");
        p.set("end-on-halt", (bool)1);
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }

    params paramsForcpu18() {
        params p;
        p.set("format", "metaware");
        p.set("end-on-halt", (bool)1);
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }

    params paramsForcpu19() {
        params p;
        p.set("format", "metaware");
        p.set("end-on-halt", (bool)1);
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }

    params paramsForcpu20() {
        params p;
        p.set("format", "metaware");
        p.set("end-on-halt", (bool)1);
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }

    params paramsForcpu21() {
        params p;
        p.set("format", "metaware");
        p.set("end-on-halt", (bool)1);
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }

    params paramsForcpu22() {
        params p;
        p.set("format", "metaware");
        p.set("end-on-halt", (bool)1);
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }

    params paramsForcpu23() {
        params p;
        p.set("format", "metaware");
        p.set("end-on-halt", (bool)1);
        p.set(OP_FP_DEFAULTSEMIHOST, true);
        p.set(OP_FP_ENDIAN, "little");
        return p;
    }
}; /* manycore24_arc_tlm2 */

////////////////////////////////////////////////////////////////////////////////
//                   manycore24_arc_tlm2 Constructor
////////////////////////////////////////////////////////////////////////////////

manycore24_arc_tlm2::manycore24_arc_tlm2 (sc_module_name name)
    : sc_module (name)
    , ram00 (Platform, "ram00", 0xffffff)
    , ram01 (Platform, "ram01", 0xffff)
    , ram10 (Platform, "ram10", 0xffffff)
    , ram11 (Platform, "ram11", 0xffff)
    , ram20 (Platform, "ram20", 0xffffff)
    , ram21 (Platform, "ram21", 0xffff)
    , ram30 (Platform, "ram30", 0xffffff)
    , ram31 (Platform, "ram31", 0xffff)
    , ram40 (Platform, "ram40", 0xffffff)
    , ram41 (Platform, "ram41", 0xffff)
    , ram50 (Platform, "ram50", 0xffffff)
    , ram51 (Platform, "ram51", 0xffff)
    , ram60 (Platform, "ram60", 0xffffff)
    , ram61 (Platform, "ram61", 0xffff)
    , ram70 (Platform, "ram70", 0xffffff)
    , ram71 (Platform, "ram71", 0xffff)
    , ram80 (Platform, "ram80", 0xffffff)
    , ram81 (Platform, "ram81", 0xffff)
    , ram90 (Platform, "ram90", 0xffffff)
    , ram91 (Platform, "ram91", 0xffff)
    , ram100 (Platform, "ram100", 0xffffff)
    , ram101 (Platform, "ram101", 0xffff)
    , ram110 (Platform, "ram110", 0xffffff)
    , ram111 (Platform, "ram111", 0xffff)
    , ram120 (Platform, "ram120", 0xffffff)
    , ram121 (Platform, "ram121", 0xffff)
    , ram130 (Platform, "ram130", 0xffffff)
    , ram131 (Platform, "ram131", 0xffff)
    , ram140 (Platform, "ram140", 0xffffff)
    , ram141 (Platform, "ram141", 0xffff)
    , ram150 (Platform, "ram150", 0xffffff)
    , ram151 (Platform, "ram151", 0xffff)
    , ram160 (Platform, "ram160", 0xffffff)
    , ram161 (Platform, "ram161", 0xffff)
    , ram170 (Platform, "ram170", 0xffffff)
    , ram171 (Platform, "ram171", 0xffff)
    , ram180 (Platform, "ram180", 0xffffff)
    , ram181 (Platform, "ram181", 0xffff)
    , ram190 (Platform, "ram190", 0xffffff)
    , ram191 (Platform, "ram191", 0xffff)
    , ram200 (Platform, "ram200", 0xffffff)
    , ram201 (Platform, "ram201", 0xffff)
    , ram210 (Platform, "ram210", 0xffffff)
    , ram211 (Platform, "ram211", 0xffff)
    , ram220 (Platform, "ram220", 0xffffff)
    , ram221 (Platform, "ram221", 0xffff)
    , ram230 (Platform, "ram230", 0xffffff)
    , ram231 (Platform, "ram231", 0xffff)
    , Platform ("", paramsForPlatform())
    , bus0(Platform, "bus0", 2, 2)
    , bus1(Platform, "bus1", 2, 2)
    , bus2(Platform, "bus2", 2, 2)
    , bus3(Platform, "bus3", 2, 2)
    , bus4(Platform, "bus4", 2, 2)
    , bus5(Platform, "bus5", 2, 2)
    , bus6(Platform, "bus6", 2, 2)
    , bus7(Platform, "bus7", 2, 2)
    , bus8(Platform, "bus8", 2, 2)
    , bus9(Platform, "bus9", 2, 2)
    , bus10(Platform, "bus10", 2, 2)
    , bus11(Platform, "bus11", 2, 2)
    , bus12(Platform, "bus12", 2, 2)
    , bus13(Platform, "bus13", 2, 2)
    , bus14(Platform, "bus14", 2, 2)
    , bus15(Platform, "bus15", 2, 2)
    , bus16(Platform, "bus16", 2, 2)
    , bus17(Platform, "bus17", 2, 2)
    , bus18(Platform, "bus18", 2, 2)
    , bus19(Platform, "bus19", 2, 2)
    , bus20(Platform, "bus20", 2, 2)
    , bus21(Platform, "bus21", 2, 2)
    , bus22(Platform, "bus22", 2, 2)
    , bus23(Platform, "bus23", 2, 2)
    , cpu0 ( Platform, "cpu0", paramsForcpu0(), 32, 32)
    , cpu1 ( Platform, "cpu1", paramsForcpu1(), 32, 32)
    , cpu2 ( Platform, "cpu2", paramsForcpu2(), 32, 32)
    , cpu3 ( Platform, "cpu3", paramsForcpu3(), 32, 32)
    , cpu4 ( Platform, "cpu4", paramsForcpu4(), 32, 32)
    , cpu5 ( Platform, "cpu5", paramsForcpu5(), 32, 32)
    , cpu6 ( Platform, "cpu6", paramsForcpu6(), 32, 32)
    , cpu7 ( Platform, "cpu7", paramsForcpu7(), 32, 32)
    , cpu8 ( Platform, "cpu8", paramsForcpu8(), 32, 32)
    , cpu9 ( Platform, "cpu9", paramsForcpu9(), 32, 32)
    , cpu10 ( Platform, "cpu10", paramsForcpu10(), 32, 32)
    , cpu11 ( Platform, "cpu11", paramsForcpu11(), 32, 32)
    , cpu12 ( Platform, "cpu12", paramsForcpu12(), 32, 32)
    , cpu13 ( Platform, "cpu13", paramsForcpu13(), 32, 32)
    , cpu14 ( Platform, "cpu14", paramsForcpu14(), 32, 32)
    , cpu15 ( Platform, "cpu15", paramsForcpu15(), 32, 32)
    , cpu16 ( Platform, "cpu16", paramsForcpu16(), 32, 32)
    , cpu17 ( Platform, "cpu17", paramsForcpu17(), 32, 32)
    , cpu18 ( Platform, "cpu18", paramsForcpu18(), 32, 32)
    , cpu19 ( Platform, "cpu19", paramsForcpu19(), 32, 32)
    , cpu20 ( Platform, "cpu20", paramsForcpu20(), 32, 32)
    , cpu21 ( Platform, "cpu21", paramsForcpu21(), 32, 32)
    , cpu22 ( Platform, "cpu22", paramsForcpu22(), 32, 32)
    , cpu23 ( Platform, "cpu23", paramsForcpu23(), 32, 32)
{

    // bus0 masters
    bus0.connect(cpu0.INSTRUCTION);
    bus0.connect(cpu0.DATA);

    // bus0 slaves
    bus0.connect(ram00.sp1,0x0, 0xffffff); // Memory (0)
    bus0.connect(ram01.sp1,0xffff0000, 0xffffffff); // Memory (1)

    // bus1 masters
    bus1.connect(cpu1.INSTRUCTION);
    bus1.connect(cpu1.DATA);

    // bus1 slaves
    bus1.connect(ram10.sp1,0x0, 0xffffff); // Memory (0)
    bus1.connect(ram11.sp1,0xffff0000, 0xffffffff); // Memory (1)

    // bus2 masters
    bus2.connect(cpu2.INSTRUCTION);
    bus2.connect(cpu2.DATA);

    // bus2 slaves
    bus2.connect(ram20.sp1,0x0, 0xffffff); // Memory (0)
    bus2.connect(ram21.sp1,0xffff0000, 0xffffffff); // Memory (1)

    // bus3 masters
    bus3.connect(cpu3.INSTRUCTION);
    bus3.connect(cpu3.DATA);

    // bus3 slaves
    bus3.connect(ram30.sp1,0x0, 0xffffff); // Memory (0)
    bus3.connect(ram31.sp1,0xffff0000, 0xffffffff); // Memory (1)

    // bus4 masters
    bus4.connect(cpu4.INSTRUCTION);
    bus4.connect(cpu4.DATA);

    // bus4 slaves
    bus4.connect(ram40.sp1,0x0, 0xffffff); // Memory (0)
    bus4.connect(ram41.sp1,0xffff0000, 0xffffffff); // Memory (1)

    // bus5 masters
    bus5.connect(cpu5.INSTRUCTION);
    bus5.connect(cpu5.DATA);

    // bus5 slaves
    bus5.connect(ram50.sp1,0x0, 0xffffff); // Memory (0)
    bus5.connect(ram51.sp1,0xffff0000, 0xffffffff); // Memory (1)

    // bus6 masters
    bus6.connect(cpu6.INSTRUCTION);
    bus6.connect(cpu6.DATA);

    // bus6 slaves
    bus6.connect(ram60.sp1,0x0, 0xffffff); // Memory (0)
    bus6.connect(ram61.sp1,0xffff0000, 0xffffffff); // Memory (1)

    // bus7 masters
    bus7.connect(cpu7.INSTRUCTION);
    bus7.connect(cpu7.DATA);

    // bus7 slaves
    bus7.connect(ram70.sp1,0x0, 0xffffff); // Memory (0)
    bus7.connect(ram71.sp1,0xffff0000, 0xffffffff); // Memory (1)

    // bus8 masters
    bus8.connect(cpu8.INSTRUCTION);
    bus8.connect(cpu8.DATA);

    // bus8 slaves
    bus8.connect(ram80.sp1,0x0, 0xffffff); // Memory (0)
    bus8.connect(ram81.sp1,0xffff0000, 0xffffffff); // Memory (1)

    // bus9 masters
    bus9.connect(cpu9.INSTRUCTION);
    bus9.connect(cpu9.DATA);

    // bus9 slaves
    bus9.connect(ram90.sp1,0x0, 0xffffff); // Memory (0)
    bus9.connect(ram91.sp1,0xffff0000, 0xffffffff); // Memory (1)

    // bus10 masters
    bus10.connect(cpu10.INSTRUCTION);
    bus10.connect(cpu10.DATA);

    // bus10 slaves
    bus10.connect(ram100.sp1,0x0, 0xffffff); // Memory (0)
    bus10.connect(ram101.sp1,0xffff0000, 0xffffffff); // Memory (1)

    // bus11 masters
    bus11.connect(cpu11.INSTRUCTION);
    bus11.connect(cpu11.DATA);

    // bus11 slaves
    bus11.connect(ram110.sp1,0x0, 0xffffff); // Memory (0)
    bus11.connect(ram111.sp1,0xffff0000, 0xffffffff); // Memory (1)

    // bus12 masters
    bus12.connect(cpu12.INSTRUCTION);
    bus12.connect(cpu12.DATA);

    // bus12 slaves
    bus12.connect(ram120.sp1,0x0, 0xffffff); // Memory (0)
    bus12.connect(ram121.sp1,0xffff0000, 0xffffffff); // Memory (1)

    // bus13 masters
    bus13.connect(cpu13.INSTRUCTION);
    bus13.connect(cpu13.DATA);

    // bus13 slaves
    bus13.connect(ram130.sp1,0x0, 0xffffff); // Memory (0)
    bus13.connect(ram131.sp1,0xffff0000, 0xffffffff); // Memory (1)

    // bus14 masters
    bus14.connect(cpu14.INSTRUCTION);
    bus14.connect(cpu14.DATA);

    // bus14 slaves
    bus14.connect(ram140.sp1,0x0, 0xffffff); // Memory (0)
    bus14.connect(ram141.sp1,0xffff0000, 0xffffffff); // Memory (1)

    // bus15 masters
    bus15.connect(cpu15.INSTRUCTION);
    bus15.connect(cpu15.DATA);

    // bus15 slaves
    bus15.connect(ram150.sp1,0x0, 0xffffff); // Memory (0)
    bus15.connect(ram151.sp1,0xffff0000, 0xffffffff); // Memory (1)

    // bus16 masters
    bus16.connect(cpu16.INSTRUCTION);
    bus16.connect(cpu16.DATA);

    // bus16 slaves
    bus16.connect(ram160.sp1,0x0, 0xffffff); // Memory (0)
    bus16.connect(ram161.sp1,0xffff0000, 0xffffffff); // Memory (1)

    // bus17 masters
    bus17.connect(cpu17.INSTRUCTION);
    bus17.connect(cpu17.DATA);

    // bus17 slaves
    bus17.connect(ram170.sp1,0x0, 0xffffff); // Memory (0)
    bus17.connect(ram171.sp1,0xffff0000, 0xffffffff); // Memory (1)

    // bus18 masters
    bus18.connect(cpu18.INSTRUCTION);
    bus18.connect(cpu18.DATA);

    // bus18 slaves
    bus18.connect(ram180.sp1,0x0, 0xffffff); // Memory (0)
    bus18.connect(ram181.sp1,0xffff0000, 0xffffffff); // Memory (1)

    // bus19 masters
    bus19.connect(cpu19.INSTRUCTION);
    bus19.connect(cpu19.DATA);

    // bus19 slaves
    bus19.connect(ram190.sp1,0x0, 0xffffff); // Memory (0)
    bus19.connect(ram191.sp1,0xffff0000, 0xffffffff); // Memory (1)

    // bus20 masters
    bus20.connect(cpu20.INSTRUCTION);
    bus20.connect(cpu20.DATA);

    // bus20 slaves
    bus20.connect(ram200.sp1,0x0, 0xffffff); // Memory (0)
    bus20.connect(ram201.sp1,0xffff0000, 0xffffffff); // Memory (1)

    // bus21 masters
    bus21.connect(cpu21.INSTRUCTION);
    bus21.connect(cpu21.DATA);

    // bus21 slaves
    bus21.connect(ram210.sp1,0x0, 0xffffff); // Memory (0)
    bus21.connect(ram211.sp1,0xffff0000, 0xffffffff); // Memory (1)

    // bus22 masters
    bus22.connect(cpu22.INSTRUCTION);
    bus22.connect(cpu22.DATA);

    // bus22 slaves
    bus22.connect(ram220.sp1,0x0, 0xffffff); // Memory (0)
    bus22.connect(ram221.sp1,0xffff0000, 0xffffffff); // Memory (1)

    // bus23 masters
    bus23.connect(cpu23.INSTRUCTION);
    bus23.connect(cpu23.DATA);

    // bus23 slaves
    bus23.connect(ram230.sp1,0x0, 0xffffff); // Memory (0)
    bus23.connect(ram231.sp1,0xffff0000, 0xffffffff); // Memory (1)
}

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int sc_main (int argc, char *argv[]) {
    session s;
    parser p("manycore24_arc_tlm2", OP_AC_ALL);
    if(!p.parse(argc, (const char **)argv)) {
        return 1;
    }
    if(!p.used("program")){
        opMessage("E", "manycore24_arc_tlm2", "Argument '--program' must be specified to load application program");
        return 1;
    }
    if(p.used("variant")){
        opMessage("E", "manycore24_arc_tlm2", "Argument '--variant' should not be specified. The variant is defined by the processor TLM interface file included in the build of the TLM platform");
        return 1;
    }

    manycore24_arc_tlm2 manycore24_arc_tlm2 ("top");

    sc_start();

    cout << "Finished sc_main." << endl;
    return 0;
}

