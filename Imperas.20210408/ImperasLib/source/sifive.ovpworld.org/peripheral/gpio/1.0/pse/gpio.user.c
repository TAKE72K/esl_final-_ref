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
//                           Imperas/OVP Generated
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>

#include "pse.igen.h"

#define PREFIX "GPIO"

// Switch 0, 1 and 2 value not GPIO
Uns32 sw0_2;
// GPIO pin values
Uns32 dataPinIn;         // current input
Uns32 dataPinInLast;     // previous before change
Uns32 dataPinOut;        // current output


#define FLIP_BIT(_d, _b) ((_d & (1<<_b)) ? (_d &= ~(1<<_b)) : (_d |= (1<<_b)))
#define GET_BIT(_d, _b)  ((_d & (1<<_b)) ? 1 : 0)

#define SW0  0
#define SW1  1
#define SW2  2

#define SW3   3
#define BTN0  4
#define BTN1  5
#define BTN2  6
#define BTN3  7

#define LED0R 0
#define LED0G 1
#define LED0B 2

static BHM_HTTP_GET_FN(get) {

    bhmHTTPElementOpen(ch, "ovpelement");

    bhmHTTPKeyPrintf(ch, "switches", "0x%0x", ((dataPinIn & (1<<SW3)) | sw0_2));

    bhmHTTPKeyPrintf(ch, "sw0", "%d", GET_BIT(sw0_2, SW0));
    bhmHTTPKeyPrintf(ch, "sw1", "%d", GET_BIT(sw0_2, SW1));
    bhmHTTPKeyPrintf(ch, "sw2", "%d", GET_BIT(sw0_2, SW2));
    bhmHTTPKeyPrintf(ch, "sw3", "%d", GET_BIT(dataPinIn, SW3));

    bhmHTTPKeyPrintf(ch, "btn0", "%d", GET_BIT(dataPinIn, BTN0));
    bhmHTTPKeyPrintf(ch, "btn1", "%d", GET_BIT(dataPinIn, BTN1));
    bhmHTTPKeyPrintf(ch, "btn2", "%d", GET_BIT(dataPinIn, BTN2));
    bhmHTTPKeyPrintf(ch, "btn3", "%d", GET_BIT(dataPinIn, BTN3));

    bhmHTTPKeyPrintf(ch, "led0R", "%d", GET_BIT(dataPinOut, LED0R));
    bhmHTTPKeyPrintf(ch, "led0G", "%d", GET_BIT(dataPinOut, LED0G));
    bhmHTTPKeyPrintf(ch, "led0B", "%d", GET_BIT(dataPinOut, LED0B));

    bhmHTTPKeyPrintf(ch, "power0", "");

    bhmHTTPElementClose(ch, "ovpelement");
    bhmHTTPSend(ch);
}

static void toggleNet(const char *name, ppmNetHandle netHandle) {
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX"_TL","Toggle %s Local Interrupt", name);
    }

    Uns32 current = ppmReadNet(netHandle);
    if(current) {
        ppmWriteNet(netHandle, 0 );
    } else {
        ppmWriteNet(netHandle, 1 );
    }

}

// early declaration
static void updateInterrupts(void);
static void updatePins (void);

static BHM_HTTP_POST_FN(post) {
    Uns32 gpio = dataPinIn;
    if        (strstr(body, "sw0=clicked")) {
        FLIP_BIT(sw0_2, SW0);
        toggleNet("SW0", handles.intSW0);
    } else if (strstr(body, "sw1=clicked")) {
        FLIP_BIT(sw0_2, SW1);
        toggleNet("SW1", handles.intSW1);
    } else if (strstr(body, "sw2=clicked")) {
        FLIP_BIT(sw0_2, SW2);
        toggleNet("SW2", handles.intSW2);
    } else if (strstr(body, "sw3=clicked")) {
        FLIP_BIT(gpio, SW3);
        toggleNet("SW3", handles.intSW3);
    } else if (strstr(body, "btn0=clicked")) {
        FLIP_BIT(gpio, BTN0);
        toggleNet("BTN0", handles.intBTN0);
    } else if (strstr(body, "btn1=clicked")) {
        FLIP_BIT(gpio, BTN1);
        toggleNet("BTN1", handles.intBTN1);
    } else if (strstr(body, "btn2=clicked")) {
        FLIP_BIT(gpio, BTN2);
        toggleNet("BTN2", handles.intBTN2);
    } else if (strstr(body, "btn3=clicked")) {
        FLIP_BIT(gpio, BTN3);
        toggleNet("BTN3", handles.intBTN3);
    } else if (strstr(body, "power0=clicked")) {
        bhmMessage("I", "SW_LED", "Power Switch pushed - terminating simulation.");
        bhmFinish();
    }
    if(gpio != dataPinIn) {
        if (PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX"_GI","GPIO IN Changed 0x%x -> 0x%x", dataPinIn, gpio);
        }
        dataPinIn = gpio;
        updatePins();
    }

}

//
// Show current state of GPIO
//
void showState() {
    Uns32 i;
    char  gpioString[18];
    for (i=0;i<16;i++) {
        gpioString[15-i] = (char)(dataPinIn & (1<<i)) ? 'O' : '-';
    }
    // terminate
    gpioString[16]=0;
    bhmMessage("I", PREFIX "_UGPIO", "15: %s :0", gpioString);
}

static void writeInterrupt(Uns32 intState) {

    static Uns32 intStateLast = 0;
    if(intState != intStateLast) {
        intStateLast = intState;
        if (PSE_DIAG_MEDIUM) {
            bhmMessage("I", PREFIX"_INT","Write Interrupt %d", intState);
        }

        // update interrupts
        Uns32 i;
        for (i=0;i<16;i++) {
            ppmNetHandle intHandle=(ppmNetHandle)((&handles.intOut0+(i*sizeof(ppmNetHandle))));
            if(intState & (1<<i))
                ppmWriteNet(intHandle, 1);
            else
                ppmWriteNet(intHandle, 0);
        }
    }
}

static void updateInterrupts() {

    // work out if any are satisfied
    bport1_REG_data.RISE_IP.value = dataPinIn & ~dataPinInLast;
    bport1_REG_data.FALL_IP.value = dataPinIn & ~dataPinInLast;
    bport1_REG_data.LOW_IP.value  = ~dataPinIn;
    bport1_REG_data.HIGH_IP.value = dataPinIn;

    Uns32 intStatus = 0;

    intStatus |= bport1_REG_data.RISE_IE.value & bport1_REG_data.RISE_IP.value;
    intStatus |= bport1_REG_data.FALL_IE.value & bport1_REG_data.FALL_IP.value;
    intStatus |= bport1_REG_data.LOW_IE.value  & bport1_REG_data.RISE_IP.value;
    intStatus |= bport1_REG_data.HIGH_IE.value & bport1_REG_data.RISE_IP.value;

    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_US", "Update Interrupt 0x%0x", intStatus);

    writeInterrupt(intStatus);
}

// update the output
static void updatePins () {

    // dataPin bitwise set from DATA if output enabled
    dataPinOut = (bport1_REG_data.PORT.value & bport1_REG_data.OUTPUT_EN.value);
    dataPinIn  = (dataPinIn & ~bport1_REG_data.OUTPUT_EN.value) | dataPinOut;
    ppmWriteNet(handles.gpioout, dataPinOut);

    // update the pin register
    bport1_REG_data.VALUE.value = dataPinIn;

    if(PSE_DIAG_MEDIUM) showState();

    updateInterrupts();
}

//////////////////////////////// Callback stubs ////////////////////////////////

// update the input GPIO
PPM_NET_CB(gpioinCB) {

    // update bits set as input (switches)
    // input is from pin or is the data output register if direction output and output enabled
    Uns32 dirm = bport1_REG_data.OUTPUT_EN.value;

    dataPinInLast = dataPinIn;    // save so that we can determine how the pin changed
    dataPinIn     = (value & ~dirm) | dataPinOut;

    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_GPIO_IN", "Update input 0x%x (GPIO Out 0x%08x dirm 0x%08x) GPIO In 0x%x ",
                                            (Uns32)value, dataPinIn, dirm, dataPinIn);

    // update the pin register
    bport1_REG_data.VALUE.value = dataPinIn;

    if(PSE_DIAG_MEDIUM) showState();

    updateInterrupts();
}



PPM_NBYTE_READ_CB(defaultMemRead) {
    bhmMessage("I", "PPM_DFRD",
        "Default Read   bytes:%u  Offset:0x%x",
        bytes,
        offset
    );
    memset(data, 0, bytes);
}

PPM_NBYTE_WRITE_CB(defaultMemWrite) {
    bhmMessage("I", "PPM_DFWR",
        "Default Write   bytes:%u  Offset:0x%x",
        bytes,
        offset
    );
}

PPM_NET_CB(resetCB) {

    reset_resetNet(1,0);
}

PPM_REG_WRITE_CB(wrInputEn) {

    *(Uns32*)user = data;

    updatePins();
}

PPM_REG_WRITE_CB(wrOutputEn) {

    *(Uns32*)user = data;

    updatePins();
}

PPM_REG_WRITE_CB(wrPort) {

    *(Uns32*)user = data;

    updatePins();
}

PPM_REG_WRITE_CB(wrRIE) {

    *(Uns32*)user = data;

    updateInterrupts();
}

PPM_REG_WRITE_CB(wrFIE) {

    *(Uns32*)user = data;

    updateInterrupts();
}

PPM_REG_WRITE_CB(wrHIE) {

    *(Uns32*)user = data;

    updateInterrupts();
}

PPM_REG_WRITE_CB(wrLIE) {

    *(Uns32*)user = data;

    updateInterrupts();
}


#define BUFSIZE 128000
static char space[BUFSIZE];

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    bhmHTTPMethods m = { .get=get, .post=post, .message=space, .length=BUFSIZE, .userData=0 };

    bhmHTTPOpen(&m, "httpvis");

}

PPM_DESTRUCTOR_CB(destructor) {

}


PPM_SAVE_STATE_FN(peripheralSaveState) {

}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {

}

