/*
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * YOU MAY USE THE SOFTWARE SUBJECT TO THE LICENSE TERMS BELOW
 * PROVIDED THAT YOU ENSURE THAT THIS NOTICE IS REPLICATED UNMODIFIED
 * AND IN ITS ENTIRETY IN ALL DISTRIBUTIONS OF THE SOFTWARE,
 * MODIFIED OR UNMODIFIED, IN SOURCE CODE OR IN BINARY FORM.
 *
 * In respect of all models:
 *   The license shall not be construed as granting a license to create a hardware
 *   implementation of the functionality of the software licensed hereunder.
 *
 * In respect of ARM related models:
 *   The license below extends only for your use of the software for the sole
 *   purpose of designing, developing, analyzing, debugging, testing,
 *   verifying, validating and optimizing software which: (a) (i) is for ARM
 *   based systems; and (ii) does not incorporate the ARM Models or any part
 *   thereof; and (b) such ARM Models may not be used to emulate an ARM based
 *   system to run application software in a production or live environment.
 *
 *   The license does not entitle you to use the ARM models for evaluating
 *   the validity of any ARM patent.
 *
 * The license is non-exclusive, worldwide, non-transferable and revocable.
 *
 * Licensed under an Imperas Modified Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.ovpworld.org/licenses/OVP_MODIFIED_1.1_APACHE_OPEN_SOURCE_LICENSE_2.0.pdf
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

class arm_Cortex_A15MPx3 : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        p.set("variant", "Cortex-A15MPx3");
        return p;
    }

    params paramsForProc() {
        params p;
        p.set("variant", "Cortex-A15MPx3");
        return p;
    }

    const char *getModel() {
        const char *vlnv = opVLNVString (NULL, "arm.ovpworld.org", "processor", "arm", "1.0", OP_PROCESSOR, 1);
        if(!vlnv) {
            opMessage("F", "TLM_FFM", "Failed to find model arm.ovpworld.org/processor/arm/1.0");
        }
        return vlnv;
    }

  public:
    tlmBusMasterPort     INSTRUCTION;
    tlmBusMasterPort     DATA;
    tlmBusMasterPort     GICRegisters;
    tlmNetInputPort      SPI32;
    tlmNetInputPort      SPI33;
    tlmNetInputPort      SPI34;
    tlmNetInputPort      SPI35;
    tlmNetInputPort      SPI36;
    tlmNetInputPort      SPI37;
    tlmNetInputPort      SPI38;
    tlmNetInputPort      SPI39;
    tlmNetInputPort      SPI40;
    tlmNetInputPort      SPI41;
    tlmNetInputPort      SPI42;
    tlmNetInputPort      SPI43;
    tlmNetInputPort      SPI44;
    tlmNetInputPort      SPI45;
    tlmNetInputPort      SPI46;
    tlmNetInputPort      SPI47;
    tlmNetInputPort      SPI48;
    tlmNetInputPort      SPI49;
    tlmNetInputPort      SPI50;
    tlmNetInputPort      SPI51;
    tlmNetInputPort      SPI52;
    tlmNetInputPort      SPI53;
    tlmNetInputPort      SPI54;
    tlmNetInputPort      SPI55;
    tlmNetInputPort      SPI56;
    tlmNetInputPort      SPI57;
    tlmNetInputPort      SPI58;
    tlmNetInputPort      SPI59;
    tlmNetInputPort      SPI60;
    tlmNetInputPort      SPI61;
    tlmNetInputPort      SPI62;
    tlmNetInputPort      SPI63;
    tlmNetInputPort      SPI64;
    tlmNetInputPort      SPI65;
    tlmNetInputPort      SPI66;
    tlmNetInputPort      SPI67;
    tlmNetInputPort      SPI68;
    tlmNetInputPort      SPI69;
    tlmNetInputPort      SPI70;
    tlmNetInputPort      SPI71;
    tlmNetInputPort      SPI72;
    tlmNetInputPort      SPI73;
    tlmNetInputPort      SPI74;
    tlmNetInputPort      SPI75;
    tlmNetInputPort      SPI76;
    tlmNetInputPort      SPI77;
    tlmNetInputPort      SPI78;
    tlmNetInputPort      SPI79;
    tlmNetInputPort      SPI80;
    tlmNetInputPort      SPI81;
    tlmNetInputPort      SPI82;
    tlmNetInputPort      SPI83;
    tlmNetInputPort      SPI84;
    tlmNetInputPort      SPI85;
    tlmNetInputPort      SPI86;
    tlmNetInputPort      SPI87;
    tlmNetInputPort      SPI88;
    tlmNetInputPort      SPI89;
    tlmNetInputPort      SPI90;
    tlmNetInputPort      SPI91;
    tlmNetInputPort      SPI92;
    tlmNetInputPort      SPI93;
    tlmNetInputPort      SPI94;
    tlmNetInputPort      SPI95;
    tlmNetInputPort      SPIVector;
    tlmNetInputPort      periphReset;
    tlmNetInputPort      CFGSDISABLE;
    tlmNetInputPort      EVENTI;
    tlmNetOutputPort     EVENTO;
    tlmNetInputPort      PPI16_CPU0;
    tlmNetInputPort      PPI17_CPU0;
    tlmNetInputPort      PPI18_CPU0;
    tlmNetInputPort      PPI19_CPU0;
    tlmNetInputPort      PPI20_CPU0;
    tlmNetInputPort      PPI21_CPU0;
    tlmNetInputPort      PPI22_CPU0;
    tlmNetInputPort      PPI23_CPU0;
    tlmNetInputPort      PPI24_CPU0;
    tlmNetInputPort      PPI25_CPU0;
    tlmNetInputPort      PPI26_CPU0;
    tlmNetInputPort      PPI27_CPU0;
    tlmNetInputPort      PPI28_CPU0;
    tlmNetInputPort      PPI29_CPU0;
    tlmNetInputPort      PPI30_CPU0;
    tlmNetInputPort      PPI31_CPU0;
    tlmNetOutputPort     CNTVIRQ_CPU0;
    tlmNetOutputPort     CNTPSIRQ_CPU0;
    tlmNetOutputPort     CNTPNSIRQ_CPU0;
    tlmNetOutputPort     CNTPHPIRQ_CPU0;
    tlmNetOutputPort     IRQOUT_CPU0;
    tlmNetOutputPort     FIQOUT_CPU0;
    tlmNetInputPort      CLUSTERIDAFF1;
    tlmNetInputPort      CLUSTERIDAFF2;
    tlmNetInputPort      VINITHI_CPU0;
    tlmNetInputPort      CFGEND_CPU0;
    tlmNetInputPort      CFGTE_CPU0;
    tlmNetInputPort      reset_CPU0;
    tlmNetInputPort      fiq_CPU0;
    tlmNetInputPort      irq_CPU0;
    tlmNetInputPort      sei_CPU0;
    tlmNetInputPort      vfiq_CPU0;
    tlmNetInputPort      virq_CPU0;
    tlmNetInputPort      vsei_CPU0;
    tlmNetInputPort      AXI_SLVERR_CPU0;
    tlmNetInputPort      CP15SDISABLE_CPU0;
    tlmNetInputPort      PPI16_CPU1;
    tlmNetInputPort      PPI17_CPU1;
    tlmNetInputPort      PPI18_CPU1;
    tlmNetInputPort      PPI19_CPU1;
    tlmNetInputPort      PPI20_CPU1;
    tlmNetInputPort      PPI21_CPU1;
    tlmNetInputPort      PPI22_CPU1;
    tlmNetInputPort      PPI23_CPU1;
    tlmNetInputPort      PPI24_CPU1;
    tlmNetInputPort      PPI25_CPU1;
    tlmNetInputPort      PPI26_CPU1;
    tlmNetInputPort      PPI27_CPU1;
    tlmNetInputPort      PPI28_CPU1;
    tlmNetInputPort      PPI29_CPU1;
    tlmNetInputPort      PPI30_CPU1;
    tlmNetInputPort      PPI31_CPU1;
    tlmNetOutputPort     CNTVIRQ_CPU1;
    tlmNetOutputPort     CNTPSIRQ_CPU1;
    tlmNetOutputPort     CNTPNSIRQ_CPU1;
    tlmNetOutputPort     CNTPHPIRQ_CPU1;
    tlmNetOutputPort     IRQOUT_CPU1;
    tlmNetOutputPort     FIQOUT_CPU1;
    tlmNetInputPort      VINITHI_CPU1;
    tlmNetInputPort      CFGEND_CPU1;
    tlmNetInputPort      CFGTE_CPU1;
    tlmNetInputPort      reset_CPU1;
    tlmNetInputPort      fiq_CPU1;
    tlmNetInputPort      irq_CPU1;
    tlmNetInputPort      sei_CPU1;
    tlmNetInputPort      vfiq_CPU1;
    tlmNetInputPort      virq_CPU1;
    tlmNetInputPort      vsei_CPU1;
    tlmNetInputPort      AXI_SLVERR_CPU1;
    tlmNetInputPort      CP15SDISABLE_CPU1;
    tlmNetInputPort      PPI16_CPU2;
    tlmNetInputPort      PPI17_CPU2;
    tlmNetInputPort      PPI18_CPU2;
    tlmNetInputPort      PPI19_CPU2;
    tlmNetInputPort      PPI20_CPU2;
    tlmNetInputPort      PPI21_CPU2;
    tlmNetInputPort      PPI22_CPU2;
    tlmNetInputPort      PPI23_CPU2;
    tlmNetInputPort      PPI24_CPU2;
    tlmNetInputPort      PPI25_CPU2;
    tlmNetInputPort      PPI26_CPU2;
    tlmNetInputPort      PPI27_CPU2;
    tlmNetInputPort      PPI28_CPU2;
    tlmNetInputPort      PPI29_CPU2;
    tlmNetInputPort      PPI30_CPU2;
    tlmNetInputPort      PPI31_CPU2;
    tlmNetOutputPort     CNTVIRQ_CPU2;
    tlmNetOutputPort     CNTPSIRQ_CPU2;
    tlmNetOutputPort     CNTPNSIRQ_CPU2;
    tlmNetOutputPort     CNTPHPIRQ_CPU2;
    tlmNetOutputPort     IRQOUT_CPU2;
    tlmNetOutputPort     FIQOUT_CPU2;
    tlmNetInputPort      VINITHI_CPU2;
    tlmNetInputPort      CFGEND_CPU2;
    tlmNetInputPort      CFGTE_CPU2;
    tlmNetInputPort      reset_CPU2;
    tlmNetInputPort      fiq_CPU2;
    tlmNetInputPort      irq_CPU2;
    tlmNetInputPort      sei_CPU2;
    tlmNetInputPort      vfiq_CPU2;
    tlmNetInputPort      virq_CPU2;
    tlmNetInputPort      vsei_CPU2;
    tlmNetInputPort      AXI_SLVERR_CPU2;
    tlmNetInputPort      CP15SDISABLE_CPU2;

    arm_Cortex_A15MPx3(tlmModule &parent, sc_module_name name)
    : tlmProcessor(parent, getModel(), name, paramsForProc())
    , INSTRUCTION (parent, this, "INSTRUCTION", 40)
    , DATA (parent, this, "DATA", 40)
    , GICRegisters (parent, this, "GICRegisters", 32)
    , SPI32(parent, this, "SPI32")
    , SPI33(parent, this, "SPI33")
    , SPI34(parent, this, "SPI34")
    , SPI35(parent, this, "SPI35")
    , SPI36(parent, this, "SPI36")
    , SPI37(parent, this, "SPI37")
    , SPI38(parent, this, "SPI38")
    , SPI39(parent, this, "SPI39")
    , SPI40(parent, this, "SPI40")
    , SPI41(parent, this, "SPI41")
    , SPI42(parent, this, "SPI42")
    , SPI43(parent, this, "SPI43")
    , SPI44(parent, this, "SPI44")
    , SPI45(parent, this, "SPI45")
    , SPI46(parent, this, "SPI46")
    , SPI47(parent, this, "SPI47")
    , SPI48(parent, this, "SPI48")
    , SPI49(parent, this, "SPI49")
    , SPI50(parent, this, "SPI50")
    , SPI51(parent, this, "SPI51")
    , SPI52(parent, this, "SPI52")
    , SPI53(parent, this, "SPI53")
    , SPI54(parent, this, "SPI54")
    , SPI55(parent, this, "SPI55")
    , SPI56(parent, this, "SPI56")
    , SPI57(parent, this, "SPI57")
    , SPI58(parent, this, "SPI58")
    , SPI59(parent, this, "SPI59")
    , SPI60(parent, this, "SPI60")
    , SPI61(parent, this, "SPI61")
    , SPI62(parent, this, "SPI62")
    , SPI63(parent, this, "SPI63")
    , SPI64(parent, this, "SPI64")
    , SPI65(parent, this, "SPI65")
    , SPI66(parent, this, "SPI66")
    , SPI67(parent, this, "SPI67")
    , SPI68(parent, this, "SPI68")
    , SPI69(parent, this, "SPI69")
    , SPI70(parent, this, "SPI70")
    , SPI71(parent, this, "SPI71")
    , SPI72(parent, this, "SPI72")
    , SPI73(parent, this, "SPI73")
    , SPI74(parent, this, "SPI74")
    , SPI75(parent, this, "SPI75")
    , SPI76(parent, this, "SPI76")
    , SPI77(parent, this, "SPI77")
    , SPI78(parent, this, "SPI78")
    , SPI79(parent, this, "SPI79")
    , SPI80(parent, this, "SPI80")
    , SPI81(parent, this, "SPI81")
    , SPI82(parent, this, "SPI82")
    , SPI83(parent, this, "SPI83")
    , SPI84(parent, this, "SPI84")
    , SPI85(parent, this, "SPI85")
    , SPI86(parent, this, "SPI86")
    , SPI87(parent, this, "SPI87")
    , SPI88(parent, this, "SPI88")
    , SPI89(parent, this, "SPI89")
    , SPI90(parent, this, "SPI90")
    , SPI91(parent, this, "SPI91")
    , SPI92(parent, this, "SPI92")
    , SPI93(parent, this, "SPI93")
    , SPI94(parent, this, "SPI94")
    , SPI95(parent, this, "SPI95")
    , SPIVector(parent, this, "SPIVector")
    , periphReset(parent, this, "periphReset")
    , CFGSDISABLE(parent, this, "CFGSDISABLE")
    , EVENTI(parent, this, "EVENTI")
    , EVENTO(parent, this, "EVENTO")
    , PPI16_CPU0(parent, this, "PPI16_CPU0")
    , PPI17_CPU0(parent, this, "PPI17_CPU0")
    , PPI18_CPU0(parent, this, "PPI18_CPU0")
    , PPI19_CPU0(parent, this, "PPI19_CPU0")
    , PPI20_CPU0(parent, this, "PPI20_CPU0")
    , PPI21_CPU0(parent, this, "PPI21_CPU0")
    , PPI22_CPU0(parent, this, "PPI22_CPU0")
    , PPI23_CPU0(parent, this, "PPI23_CPU0")
    , PPI24_CPU0(parent, this, "PPI24_CPU0")
    , PPI25_CPU0(parent, this, "PPI25_CPU0")
    , PPI26_CPU0(parent, this, "PPI26_CPU0")
    , PPI27_CPU0(parent, this, "PPI27_CPU0")
    , PPI28_CPU0(parent, this, "PPI28_CPU0")
    , PPI29_CPU0(parent, this, "PPI29_CPU0")
    , PPI30_CPU0(parent, this, "PPI30_CPU0")
    , PPI31_CPU0(parent, this, "PPI31_CPU0")
    , CNTVIRQ_CPU0(parent, this, "CNTVIRQ_CPU0")
    , CNTPSIRQ_CPU0(parent, this, "CNTPSIRQ_CPU0")
    , CNTPNSIRQ_CPU0(parent, this, "CNTPNSIRQ_CPU0")
    , CNTPHPIRQ_CPU0(parent, this, "CNTPHPIRQ_CPU0")
    , IRQOUT_CPU0(parent, this, "IRQOUT_CPU0")
    , FIQOUT_CPU0(parent, this, "FIQOUT_CPU0")
    , CLUSTERIDAFF1(parent, this, "CLUSTERIDAFF1")
    , CLUSTERIDAFF2(parent, this, "CLUSTERIDAFF2")
    , VINITHI_CPU0(parent, this, "VINITHI_CPU0")
    , CFGEND_CPU0(parent, this, "CFGEND_CPU0")
    , CFGTE_CPU0(parent, this, "CFGTE_CPU0")
    , reset_CPU0(parent, this, "reset_CPU0")
    , fiq_CPU0(parent, this, "fiq_CPU0")
    , irq_CPU0(parent, this, "irq_CPU0")
    , sei_CPU0(parent, this, "sei_CPU0")
    , vfiq_CPU0(parent, this, "vfiq_CPU0")
    , virq_CPU0(parent, this, "virq_CPU0")
    , vsei_CPU0(parent, this, "vsei_CPU0")
    , AXI_SLVERR_CPU0(parent, this, "AXI_SLVERR_CPU0")
    , CP15SDISABLE_CPU0(parent, this, "CP15SDISABLE_CPU0")
    , PPI16_CPU1(parent, this, "PPI16_CPU1")
    , PPI17_CPU1(parent, this, "PPI17_CPU1")
    , PPI18_CPU1(parent, this, "PPI18_CPU1")
    , PPI19_CPU1(parent, this, "PPI19_CPU1")
    , PPI20_CPU1(parent, this, "PPI20_CPU1")
    , PPI21_CPU1(parent, this, "PPI21_CPU1")
    , PPI22_CPU1(parent, this, "PPI22_CPU1")
    , PPI23_CPU1(parent, this, "PPI23_CPU1")
    , PPI24_CPU1(parent, this, "PPI24_CPU1")
    , PPI25_CPU1(parent, this, "PPI25_CPU1")
    , PPI26_CPU1(parent, this, "PPI26_CPU1")
    , PPI27_CPU1(parent, this, "PPI27_CPU1")
    , PPI28_CPU1(parent, this, "PPI28_CPU1")
    , PPI29_CPU1(parent, this, "PPI29_CPU1")
    , PPI30_CPU1(parent, this, "PPI30_CPU1")
    , PPI31_CPU1(parent, this, "PPI31_CPU1")
    , CNTVIRQ_CPU1(parent, this, "CNTVIRQ_CPU1")
    , CNTPSIRQ_CPU1(parent, this, "CNTPSIRQ_CPU1")
    , CNTPNSIRQ_CPU1(parent, this, "CNTPNSIRQ_CPU1")
    , CNTPHPIRQ_CPU1(parent, this, "CNTPHPIRQ_CPU1")
    , IRQOUT_CPU1(parent, this, "IRQOUT_CPU1")
    , FIQOUT_CPU1(parent, this, "FIQOUT_CPU1")
    , VINITHI_CPU1(parent, this, "VINITHI_CPU1")
    , CFGEND_CPU1(parent, this, "CFGEND_CPU1")
    , CFGTE_CPU1(parent, this, "CFGTE_CPU1")
    , reset_CPU1(parent, this, "reset_CPU1")
    , fiq_CPU1(parent, this, "fiq_CPU1")
    , irq_CPU1(parent, this, "irq_CPU1")
    , sei_CPU1(parent, this, "sei_CPU1")
    , vfiq_CPU1(parent, this, "vfiq_CPU1")
    , virq_CPU1(parent, this, "virq_CPU1")
    , vsei_CPU1(parent, this, "vsei_CPU1")
    , AXI_SLVERR_CPU1(parent, this, "AXI_SLVERR_CPU1")
    , CP15SDISABLE_CPU1(parent, this, "CP15SDISABLE_CPU1")
    , PPI16_CPU2(parent, this, "PPI16_CPU2")
    , PPI17_CPU2(parent, this, "PPI17_CPU2")
    , PPI18_CPU2(parent, this, "PPI18_CPU2")
    , PPI19_CPU2(parent, this, "PPI19_CPU2")
    , PPI20_CPU2(parent, this, "PPI20_CPU2")
    , PPI21_CPU2(parent, this, "PPI21_CPU2")
    , PPI22_CPU2(parent, this, "PPI22_CPU2")
    , PPI23_CPU2(parent, this, "PPI23_CPU2")
    , PPI24_CPU2(parent, this, "PPI24_CPU2")
    , PPI25_CPU2(parent, this, "PPI25_CPU2")
    , PPI26_CPU2(parent, this, "PPI26_CPU2")
    , PPI27_CPU2(parent, this, "PPI27_CPU2")
    , PPI28_CPU2(parent, this, "PPI28_CPU2")
    , PPI29_CPU2(parent, this, "PPI29_CPU2")
    , PPI30_CPU2(parent, this, "PPI30_CPU2")
    , PPI31_CPU2(parent, this, "PPI31_CPU2")
    , CNTVIRQ_CPU2(parent, this, "CNTVIRQ_CPU2")
    , CNTPSIRQ_CPU2(parent, this, "CNTPSIRQ_CPU2")
    , CNTPNSIRQ_CPU2(parent, this, "CNTPNSIRQ_CPU2")
    , CNTPHPIRQ_CPU2(parent, this, "CNTPHPIRQ_CPU2")
    , IRQOUT_CPU2(parent, this, "IRQOUT_CPU2")
    , FIQOUT_CPU2(parent, this, "FIQOUT_CPU2")
    , VINITHI_CPU2(parent, this, "VINITHI_CPU2")
    , CFGEND_CPU2(parent, this, "CFGEND_CPU2")
    , CFGTE_CPU2(parent, this, "CFGTE_CPU2")
    , reset_CPU2(parent, this, "reset_CPU2")
    , fiq_CPU2(parent, this, "fiq_CPU2")
    , irq_CPU2(parent, this, "irq_CPU2")
    , sei_CPU2(parent, this, "sei_CPU2")
    , vfiq_CPU2(parent, this, "vfiq_CPU2")
    , virq_CPU2(parent, this, "virq_CPU2")
    , vsei_CPU2(parent, this, "vsei_CPU2")
    , AXI_SLVERR_CPU2(parent, this, "AXI_SLVERR_CPU2")
    , CP15SDISABLE_CPU2(parent, this, "CP15SDISABLE_CPU2")
    {
    }

    arm_Cortex_A15MPx3(tlmModule &parent, sc_module_name name, params p, Uns32 INSTRUCTIONWidth=40, Uns32 DATAWidth=40, Uns32 GICRegistersWidth=32)
    : tlmProcessor(parent, getModel(), name, paramsForProc(p))
    , INSTRUCTION (parent, this, "INSTRUCTION", INSTRUCTIONWidth)
    , DATA (parent, this, "DATA", DATAWidth)
    , GICRegisters (parent, this, "GICRegisters", GICRegistersWidth)
    , SPI32(parent, this, "SPI32")
    , SPI33(parent, this, "SPI33")
    , SPI34(parent, this, "SPI34")
    , SPI35(parent, this, "SPI35")
    , SPI36(parent, this, "SPI36")
    , SPI37(parent, this, "SPI37")
    , SPI38(parent, this, "SPI38")
    , SPI39(parent, this, "SPI39")
    , SPI40(parent, this, "SPI40")
    , SPI41(parent, this, "SPI41")
    , SPI42(parent, this, "SPI42")
    , SPI43(parent, this, "SPI43")
    , SPI44(parent, this, "SPI44")
    , SPI45(parent, this, "SPI45")
    , SPI46(parent, this, "SPI46")
    , SPI47(parent, this, "SPI47")
    , SPI48(parent, this, "SPI48")
    , SPI49(parent, this, "SPI49")
    , SPI50(parent, this, "SPI50")
    , SPI51(parent, this, "SPI51")
    , SPI52(parent, this, "SPI52")
    , SPI53(parent, this, "SPI53")
    , SPI54(parent, this, "SPI54")
    , SPI55(parent, this, "SPI55")
    , SPI56(parent, this, "SPI56")
    , SPI57(parent, this, "SPI57")
    , SPI58(parent, this, "SPI58")
    , SPI59(parent, this, "SPI59")
    , SPI60(parent, this, "SPI60")
    , SPI61(parent, this, "SPI61")
    , SPI62(parent, this, "SPI62")
    , SPI63(parent, this, "SPI63")
    , SPI64(parent, this, "SPI64")
    , SPI65(parent, this, "SPI65")
    , SPI66(parent, this, "SPI66")
    , SPI67(parent, this, "SPI67")
    , SPI68(parent, this, "SPI68")
    , SPI69(parent, this, "SPI69")
    , SPI70(parent, this, "SPI70")
    , SPI71(parent, this, "SPI71")
    , SPI72(parent, this, "SPI72")
    , SPI73(parent, this, "SPI73")
    , SPI74(parent, this, "SPI74")
    , SPI75(parent, this, "SPI75")
    , SPI76(parent, this, "SPI76")
    , SPI77(parent, this, "SPI77")
    , SPI78(parent, this, "SPI78")
    , SPI79(parent, this, "SPI79")
    , SPI80(parent, this, "SPI80")
    , SPI81(parent, this, "SPI81")
    , SPI82(parent, this, "SPI82")
    , SPI83(parent, this, "SPI83")
    , SPI84(parent, this, "SPI84")
    , SPI85(parent, this, "SPI85")
    , SPI86(parent, this, "SPI86")
    , SPI87(parent, this, "SPI87")
    , SPI88(parent, this, "SPI88")
    , SPI89(parent, this, "SPI89")
    , SPI90(parent, this, "SPI90")
    , SPI91(parent, this, "SPI91")
    , SPI92(parent, this, "SPI92")
    , SPI93(parent, this, "SPI93")
    , SPI94(parent, this, "SPI94")
    , SPI95(parent, this, "SPI95")
    , SPIVector(parent, this, "SPIVector")
    , periphReset(parent, this, "periphReset")
    , CFGSDISABLE(parent, this, "CFGSDISABLE")
    , EVENTI(parent, this, "EVENTI")
    , EVENTO(parent, this, "EVENTO")
    , PPI16_CPU0(parent, this, "PPI16_CPU0")
    , PPI17_CPU0(parent, this, "PPI17_CPU0")
    , PPI18_CPU0(parent, this, "PPI18_CPU0")
    , PPI19_CPU0(parent, this, "PPI19_CPU0")
    , PPI20_CPU0(parent, this, "PPI20_CPU0")
    , PPI21_CPU0(parent, this, "PPI21_CPU0")
    , PPI22_CPU0(parent, this, "PPI22_CPU0")
    , PPI23_CPU0(parent, this, "PPI23_CPU0")
    , PPI24_CPU0(parent, this, "PPI24_CPU0")
    , PPI25_CPU0(parent, this, "PPI25_CPU0")
    , PPI26_CPU0(parent, this, "PPI26_CPU0")
    , PPI27_CPU0(parent, this, "PPI27_CPU0")
    , PPI28_CPU0(parent, this, "PPI28_CPU0")
    , PPI29_CPU0(parent, this, "PPI29_CPU0")
    , PPI30_CPU0(parent, this, "PPI30_CPU0")
    , PPI31_CPU0(parent, this, "PPI31_CPU0")
    , CNTVIRQ_CPU0(parent, this, "CNTVIRQ_CPU0")
    , CNTPSIRQ_CPU0(parent, this, "CNTPSIRQ_CPU0")
    , CNTPNSIRQ_CPU0(parent, this, "CNTPNSIRQ_CPU0")
    , CNTPHPIRQ_CPU0(parent, this, "CNTPHPIRQ_CPU0")
    , IRQOUT_CPU0(parent, this, "IRQOUT_CPU0")
    , FIQOUT_CPU0(parent, this, "FIQOUT_CPU0")
    , CLUSTERIDAFF1(parent, this, "CLUSTERIDAFF1")
    , CLUSTERIDAFF2(parent, this, "CLUSTERIDAFF2")
    , VINITHI_CPU0(parent, this, "VINITHI_CPU0")
    , CFGEND_CPU0(parent, this, "CFGEND_CPU0")
    , CFGTE_CPU0(parent, this, "CFGTE_CPU0")
    , reset_CPU0(parent, this, "reset_CPU0")
    , fiq_CPU0(parent, this, "fiq_CPU0")
    , irq_CPU0(parent, this, "irq_CPU0")
    , sei_CPU0(parent, this, "sei_CPU0")
    , vfiq_CPU0(parent, this, "vfiq_CPU0")
    , virq_CPU0(parent, this, "virq_CPU0")
    , vsei_CPU0(parent, this, "vsei_CPU0")
    , AXI_SLVERR_CPU0(parent, this, "AXI_SLVERR_CPU0")
    , CP15SDISABLE_CPU0(parent, this, "CP15SDISABLE_CPU0")
    , PPI16_CPU1(parent, this, "PPI16_CPU1")
    , PPI17_CPU1(parent, this, "PPI17_CPU1")
    , PPI18_CPU1(parent, this, "PPI18_CPU1")
    , PPI19_CPU1(parent, this, "PPI19_CPU1")
    , PPI20_CPU1(parent, this, "PPI20_CPU1")
    , PPI21_CPU1(parent, this, "PPI21_CPU1")
    , PPI22_CPU1(parent, this, "PPI22_CPU1")
    , PPI23_CPU1(parent, this, "PPI23_CPU1")
    , PPI24_CPU1(parent, this, "PPI24_CPU1")
    , PPI25_CPU1(parent, this, "PPI25_CPU1")
    , PPI26_CPU1(parent, this, "PPI26_CPU1")
    , PPI27_CPU1(parent, this, "PPI27_CPU1")
    , PPI28_CPU1(parent, this, "PPI28_CPU1")
    , PPI29_CPU1(parent, this, "PPI29_CPU1")
    , PPI30_CPU1(parent, this, "PPI30_CPU1")
    , PPI31_CPU1(parent, this, "PPI31_CPU1")
    , CNTVIRQ_CPU1(parent, this, "CNTVIRQ_CPU1")
    , CNTPSIRQ_CPU1(parent, this, "CNTPSIRQ_CPU1")
    , CNTPNSIRQ_CPU1(parent, this, "CNTPNSIRQ_CPU1")
    , CNTPHPIRQ_CPU1(parent, this, "CNTPHPIRQ_CPU1")
    , IRQOUT_CPU1(parent, this, "IRQOUT_CPU1")
    , FIQOUT_CPU1(parent, this, "FIQOUT_CPU1")
    , VINITHI_CPU1(parent, this, "VINITHI_CPU1")
    , CFGEND_CPU1(parent, this, "CFGEND_CPU1")
    , CFGTE_CPU1(parent, this, "CFGTE_CPU1")
    , reset_CPU1(parent, this, "reset_CPU1")
    , fiq_CPU1(parent, this, "fiq_CPU1")
    , irq_CPU1(parent, this, "irq_CPU1")
    , sei_CPU1(parent, this, "sei_CPU1")
    , vfiq_CPU1(parent, this, "vfiq_CPU1")
    , virq_CPU1(parent, this, "virq_CPU1")
    , vsei_CPU1(parent, this, "vsei_CPU1")
    , AXI_SLVERR_CPU1(parent, this, "AXI_SLVERR_CPU1")
    , CP15SDISABLE_CPU1(parent, this, "CP15SDISABLE_CPU1")
    , PPI16_CPU2(parent, this, "PPI16_CPU2")
    , PPI17_CPU2(parent, this, "PPI17_CPU2")
    , PPI18_CPU2(parent, this, "PPI18_CPU2")
    , PPI19_CPU2(parent, this, "PPI19_CPU2")
    , PPI20_CPU2(parent, this, "PPI20_CPU2")
    , PPI21_CPU2(parent, this, "PPI21_CPU2")
    , PPI22_CPU2(parent, this, "PPI22_CPU2")
    , PPI23_CPU2(parent, this, "PPI23_CPU2")
    , PPI24_CPU2(parent, this, "PPI24_CPU2")
    , PPI25_CPU2(parent, this, "PPI25_CPU2")
    , PPI26_CPU2(parent, this, "PPI26_CPU2")
    , PPI27_CPU2(parent, this, "PPI27_CPU2")
    , PPI28_CPU2(parent, this, "PPI28_CPU2")
    , PPI29_CPU2(parent, this, "PPI29_CPU2")
    , PPI30_CPU2(parent, this, "PPI30_CPU2")
    , PPI31_CPU2(parent, this, "PPI31_CPU2")
    , CNTVIRQ_CPU2(parent, this, "CNTVIRQ_CPU2")
    , CNTPSIRQ_CPU2(parent, this, "CNTPSIRQ_CPU2")
    , CNTPNSIRQ_CPU2(parent, this, "CNTPNSIRQ_CPU2")
    , CNTPHPIRQ_CPU2(parent, this, "CNTPHPIRQ_CPU2")
    , IRQOUT_CPU2(parent, this, "IRQOUT_CPU2")
    , FIQOUT_CPU2(parent, this, "FIQOUT_CPU2")
    , VINITHI_CPU2(parent, this, "VINITHI_CPU2")
    , CFGEND_CPU2(parent, this, "CFGEND_CPU2")
    , CFGTE_CPU2(parent, this, "CFGTE_CPU2")
    , reset_CPU2(parent, this, "reset_CPU2")
    , fiq_CPU2(parent, this, "fiq_CPU2")
    , irq_CPU2(parent, this, "irq_CPU2")
    , sei_CPU2(parent, this, "sei_CPU2")
    , vfiq_CPU2(parent, this, "vfiq_CPU2")
    , virq_CPU2(parent, this, "virq_CPU2")
    , vsei_CPU2(parent, this, "vsei_CPU2")
    , AXI_SLVERR_CPU2(parent, this, "AXI_SLVERR_CPU2")
    , CP15SDISABLE_CPU2(parent, this, "CP15SDISABLE_CPU2")
    {
    }

    void before_end_of_elaboration() {
        DATA.bindIfNotBound();
        GICRegisters.bindIfNotBound();
    }

    void dmi(bool on) {
        INSTRUCTION.dmi(on);
        DATA.dmi(on);
        GICRegisters.dmi(on);
    }
}; /* class arm_Cortex_A15MPx3 */

