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
//                          Tue Jul 23 15:40:45 2013
//
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"

#define PREFIX "IntervalTimer"

struct {
    Uns32 irq;
    Uns32 TimerRunning;
} state;

typedef union {
    Uns32 w32;
    Uns16 s16[2];
} periodT;

periodT period;

typedef struct threadInfoS {
    bhmThreadHandle handle;
    Uns64 timeout;
    double start;
} threadInfoT;
threadInfoT tinfo = { 0 };

void interruptSet(Uns32 value);

void timerStart(Uns64 timeout);
void timerStop();

double freq_mhz;

//
// Write the irq if the value changes
//
void interruptSet(Uns32 value) {
    if (state.irq != value) {
        state.irq = value;
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Setting irq=%d @ %eUS", state.irq, bhmGetCurrentTime());
        ppmWriteNet(handles.irq, state.irq);
    }
}

void timerExpired() {
    if (PSE_DIAG_HIGH) {
        double now = bhmGetCurrentTime();
        bhmMessage("I", PREFIX, "timerExpired time=%e\n", now);
    }

    //
    // irq is active
    //
    if (sp1_reg0_data.control.bits.ITO) {
        //
        // Generate timeout interrupt
        //
        sp1_reg0_data.status.bits.TO = 1;
        interruptSet(1);
    }
}

Uns32 getTimeout () {
    Uns32 count;
    //
    // Calculate remaining time
    //
    count = 0;

    return count;
}

void timerThread(void *user) {
    Uns64 timeout = tinfo.timeout;

    do {
        double start = bhmGetCurrentTime();
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Start Timer Begin at %e timeout=%llu US", start, timeout);

        tinfo.start = bhmGetCurrentTime();
        bhmWaitDelay(timeout);

        double end = bhmGetCurrentTime();
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "End Timer Expired at %e", end);

        timerExpired();

    } while (sp1_reg0_data.control.bits.CONT);
}

void timerStop() {
    static int cnt=0;
    state.TimerRunning = 0;
    sp1_reg0_data.status.bits.RUN = 0;

    if (tinfo.handle) {
        cnt++;
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Delete Timer Thread cnt=%d time=%e", cnt, bhmGetCurrentTime());
        bhmDeleteThread(tinfo.handle);
        tinfo.handle = 0;
    }
}

void timerStart(Uns64 timeout) {
    static int cnt=0;
    state.TimerRunning = 1;
    sp1_reg0_data.status.bits.RUN = 1;

    // The timers actual period is one cycle greater than the value stored
    // in the period_n registers, the counter assumes the value zero
    // for one clock cycle, so never allow timeout to be zero
    tinfo.timeout = (timeout) / freq_mhz;
    if (tinfo.timeout == 0) {
        tinfo.timeout = 1;
    }

    if (PSE_DIAG_HIGH) {
        cnt++;
        bhmMessage("I", PREFIX, "tinfo.timeout = %llu", tinfo.timeout);
        bhmMessage("I", PREFIX, "Create Timer Thread cnt=%d time=%e", cnt, bhmGetCurrentTime());
    }

    tinfo.handle = bhmCreateThread(timerThread, 0, "Timer", 0);
}

Uns32 clocksRemaining () {
    double now     = bhmGetCurrentTime();
    double start   = tinfo.start;
    double timeout = tinfo.timeout;
    double remain;
    //
    // Is this counting up or down
    //
    Uns32 value;
    remain = (start + timeout) - now;

    value = remain * freq_mhz;

    return value;
}


//////////////////////////////// Callback stubs ////////////////////////////////

//
// Transfer current countdown value to snap[index] register
//
PPM_REG_WRITE_CB(write_snap) {
    periodT p;
    p.w32 = clocksRemaining();
    sp1_reg0_data.snapl.value = p.s16[0];
    sp1_reg0_data.snaph.value = p.s16[1];
}

//
// Transfer current countdown to snap register
//
PPM_REG_READ_CB(read_snap) {
    Uns32 ud = PTR_TO_UNS32(user);

    if (ud==0) {
        return sp1_reg0_data.snapl.value;
    } else {
        return sp1_reg0_data.snaph.value;
    }
}

PPM_REG_WRITE_CB(write_control) {
    sp1_reg0_data.control.value = data;

    if (sp1_reg0_data.control.bits.START) {
        //
        // Start timer
        //
        sp1_reg0_data.control.bits.START = 0;
        if (state.TimerRunning == 0) {
            timerStart(period.w32);
        }
    }

    if (sp1_reg0_data.control.bits.STOP) {
        //
        // Stop timer
        //
        sp1_reg0_data.control.bits.STOP  = 0;
        if (state.TimerRunning == 1) {
            timerStop();
        }
    }
}

PPM_REG_READ_CB(read_control) {
    //
    // Only read bits are [1][0]
    //
    return sp1_reg0_data.control.value & 0x3;
}

PPM_REG_WRITE_CB(write_period) {
    Uns32 ud = PTR_TO_UNS32(user);

    if (ud==0) {
        sp1_reg0_data.periodl.value = data;
        period.s16[ud] = data;
    } else {
        sp1_reg0_data.periodh.value = data;
        period.s16[ud] = data;
    }
}

PPM_REG_READ_CB(read_period) {
    bhmMessage("F", "UNSUPP", "read_period");
    return 0;
}

PPM_REG_WRITE_CB(write_status) {

    sp1_reg0_data.status.value = data;
    if (sp1_reg0_data.status.bits.TO == 0) {
        interruptSet(0);
    }
}

PPM_REG_READ_CB(read_status) {
    bhmMessage("F", "UNSUPP", "read_status");
    return *(Uns16*)user;
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();

    // Setup timeout period
    bhmUns32ParamValue("timeoutPeriod",&(period.w32));

    // Setup the timer frequency
    bhmDoubleParamValue("timerFrequency", &freq_mhz);

    if (BHM_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "frequency %fMHz", freq_mhz);
    }

    //
    // Calculate clock frequency, only updated if set
    //
    state.TimerRunning = 0;
    interruptSet(0);
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

