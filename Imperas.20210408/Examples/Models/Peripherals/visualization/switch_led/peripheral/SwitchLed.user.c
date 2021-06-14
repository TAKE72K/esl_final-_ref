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


#include "peripheral/ppm.h"
#include "peripheral/bhm.h"
#include "peripheral/bhmHttp.h"

#include "pse.igen.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#define PREFIX "SW_LED"

static void redraw (bhmHTTPChannel ch) {

    Uns32 led = bport_reg_data.led.value;
    Uns32 sw = bport_reg_data.sw.value;
    
    bhmHTTPElementOpen(ch, "ovpelement");
    bhmHTTPKeyPrintf(ch, "led0", "%d", led);
    bhmHTTPKeyPrintf(ch, "sw0", "%d", sw);
    
    bhmHTTPKeyPrintf(ch, "power0", "");
    
    bhmHTTPElementClose(ch, "ovpelement");
    bhmHTTPSend(ch);
}

static BHM_HTTP_GET_FN(get) {
    redraw (ch);
}

static BHM_HTTP_POST_FN(post) {
    if (strstr(body, "sw0=clicked")) {
        bport_reg_data.sw.value = (~bport_reg_data.sw.value) & 0x01;
    } else if (strstr(body, "power0=clicked")) {
        bhmMessage("I", PREFIX "_SW", "Power Switch pushed - terminating simulation.");
        bhmFinish();
    }
    redraw (ch);
}

PPM_REG_READ_CB(ReadSwitch) {
    if(PSE_DIAG_LOW) bhmMessage("I", PREFIX "_SW", "Read sw %d", *(Uns32*)user);
    return *(Uns32*)user;
}

PPM_REG_WRITE_CB(WriteLed) {
    if(PSE_DIAG_LOW) bhmMessage("I", PREFIX "_LED", "Write led %d", data);
    *(Uns32*)user = data;
}

#define BUFSIZE 128000
static char space[BUFSIZE];

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();

    if(PSE_DIAG_LOW) bhmMessage("I", PREFIX, "Starting");

    bhmHTTPMethods m = { .get=get, .post=post, .message=space, .length=BUFSIZE, .userData=0 };
    bhmHTTPOpen(&m, "httpvis");
}

PPM_DESTRUCTOR_CB(destructor) {
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

