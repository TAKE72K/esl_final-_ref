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


#include "pse.igen.h"
/////////////////////////////// Port Declarations //////////////////////////////

bport1_ab_dataT bport1_ab_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisVREF", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_SC_maskWrite) {
    bport1_ab_data.SC.value = (bport1_ab_data.SC.value & BPORT1_AB_SC_WRNMASK) | (data & BPORT1_AB_SC_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TRM_maskWrite) {
    bport1_ab_data.TRM.value = (bport1_ab_data.TRM.value & BPORT1_AB_TRM_WRNMASK) | (data & BPORT1_AB_TRM_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abTRM_reg = ppmCreateRegister(
            "ab_TRM",
            "VREF Trim Register, offset: 0x0 ",
            handles.bport1,
            0x0,
            1,
            read_8,
            bport1_ab_TRM_maskWrite,
            view8,
            &(bport1_ab_data.TRM.value),
            True
        );

        ppmCreateRegisterField(abTRM_reg, "TRIM", 0, 0, 6, 1, 1);
    }
    {
        registerHandle abSC_reg = ppmCreateRegister(
            "ab_SC",
            "VREF Status and Control Register, offset: 0x1 ",
            handles.bport1,
            0x1,
            1,
            read_8,
            bport1_ab_SC_maskWrite,
            view8,
            &(bport1_ab_data.SC.value),
            True
        );

        ppmCreateRegisterField(abSC_reg, "MODE_LV", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(abSC_reg, "REGEN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abSC_reg, "VREFEN", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abSC_reg, "VREFST", 0, 2, 1, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.SC.value = (Uns8)(bport1_ab_data.SC.value & ~(0xff)) | ((0xff) & (0x00));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the VREF peripheral used on the Freescale Kinetis platform");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "Provides the base behaviour for the OVP Freescale Kinetis platforms");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "www.freescale.com/Kinetis");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_32_node, "Open Source Apache 2.0");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    reset_Reset(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

