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

#include "pse.igen.h"
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define PREFIX "NCEPLMT100"

#define MAXHARTS 32

// Timer clock duration in USEC
#define CLOCK_DURATION_USEC (1.0 / clockMHz)

// Use a rounding factor of 1/10th the counter clock duration to avoid jitter
#define ROUNDING_FACTOR_USEC (CLOCK_DURATION_USEC / 10)

// Convert a floating point time in microseconds to the corresponding
// number of ticks that will elapse in that time at the configured clock frequency
// NOTE: Add clockDelta before truncating double to integer to avoid jitter
//       for floating point calculations that round to just below an integer value
#define USECS_TO_TICKS(_U) ((Uns64)(((_U) * clockMHz) + clockDelta))

// Convert a number of ticks to the floating point time in microseconds
// at the configured clock frequency
#define TICKS_TO_USEC(_T) (((double)(_T)) / clockMHz)

// Convert a simulated time counter value to the mtime register
// counter value, taking into account most recent write to the mtime register
// (both the time of the write and the value written)
#define TIME_TO_MTIME(_T) ((_T) - mtimeOffset)

// Value to indicate a NULL handle (event or thread)
#define NULL_HANDLE -1

//
// State info for each timer
//
typedef struct timerDataS {
    Uns32           hartid;             // this timer's hartid
    double          startTime;          // Time thread started in microseconds
    Uns64           startCount;         // Starting counter value
    Uns64           stopCount;          // Ending counter value
    double          threadDelay;        // Duration of timer in micro-seconds
    double          expirationTime;     // Time this event expires
    Bool            intSet;             // True when interrupt net is set
} timerData, *timerDataP;

//
// Global Variables
//
static Uns32           numharts;         // Number of timers
static double          clockMHz;         // Clock frequency in MHz from user parameter
static double          clockDelta;       // Delta to use to avoid rounding errors
static Uns64           mtimeOffset = 0;  // Offset to adjust for writes to mtime
static timerData       timers[MAXHARTS]; // Info for each timer
static timerDataP      scheduledTimer;   // Currently scheduled timer
static bhmThreadHandle timerHandle;      // Handle for timer thread
static bhmEventHandle  timerEvent;       // Handle for triggering a timer event

// Forward reference
static void timerThread(void *user);

//
// Return timerData for given hartid
// - aborts on invalid hartid
//
static timerDataP getTimer(Uns32 hartid) {
    if (hartid > numharts) {
        bhmMessage("F", PREFIX, "Invalid hartid %d", hartid);
    }
    return timers+hartid;
}

//
// Compute the current mtime counter value for the given time in microseconds
// - the value is adjusted based on any writes to the mtime register
// - ticksNowP, if not NULL, can be used to also get the number of ticks
//   starting from the beginning of simulation (which will equal the returned
//   value if mtime has not been written)
//
static Uns64 currentMTime(double timeNow, Uns64 *ticksNowP) {
    Uns64  ticksNow  = USECS_TO_TICKS(timeNow);
    Uns64  mtimeNow  = TIME_TO_MTIME(ticksNow);

    if (ticksNowP) {
        *ticksNowP = ticksNow;
    }

    return mtimeNow;
}

//
// Workaround for PSE compiler bug when using printf %lld
// - buffer is only valid until next call (do not use multiple times on same
//   printf call)
//
static const char *uns64ToDecimal(Uns64 value) {
    static char buf[32];
    char *s = buf + sizeof(buf) - 1;

    // Zero terminate the string
    *s = '\0';

    do {
        *--s = '0' + (value % 10);
        value /= 10;
    } while (value != 0 && s != buf);

    return s;
}

//
// Set interrupt output net if not currently set
// - Issue diagnostic message if the current time does not match the
//   time that the timer was expected to expire, ehich can happen if
//   a timer is scheduled to expire before the end of the quantum it
//   was scheduled from.
//
static void setInterrupt(timerDataP timer) {

    if (!timer->intSet) {
        Uns32  hartid = timer->hartid;
        double now    = bhmGetLocalTime();
        double delta  = fabs(now - timer->expirationTime);
        Bool   error  = delta > (timer->threadDelay / 100.0);

        // Issue one time warning if more than 1% error due to quantum effects
        static Bool quantumWarningIssued = False;
        if (!quantumWarningIssued && error) {
            bhmMessage("W", PREFIX"_QTS",
                    "Quantum size is limiting timer accuracy. "
                    "Reduce quantum size if precise timer accuracy required.");
            quantumWarningIssued = True;
        }

        if (PSE_DIAG_MEDIUM) {
            bhmMessage("I", PREFIX "_INTC",
                "timer[%d] @ %10.3fus: Timer expired - interrupt set",
                timer->hartid, now);
            if (error) {
                bhmMessage("I", PREFIX "_INTC",
                    "\t(Expected expiration time @ %10.3fus)",
                    timer->expirationTime);
            }
        }

        // trigger interrupt
        timer->intSet = True;
        ppmWriteNet(handles.intOut_[hartid], 1);
    }
}

//
// Clear interrupt output net if currently set
//
static void clearInterrupt(timerDataP timer) {

    if (timer->intSet) {
        Uns32 hartid = timer->hartid;

        if (PSE_DIAG_MEDIUM) {
            double now = bhmGetLocalTime();
            bhmMessage("I", PREFIX "_INTC",
                "timer[%d] @ %10.3fus: Interrupt cleared",
                timer->hartid, now);
        }

        // clear interrupt
        timer->intSet = False;
        ppmWriteNet(handles.intOut_[hartid], 0);
    }
}

//
// Trigger a timer event
//  - call this to schedule an event for the timer's expiration
//  - call with timer == NULL after timer registers are modified to recalculate
//    and schedule the next timer expiration
//  - creates a timer event and/or thread if they do not exist
//
static void scheduleTimer(timerDataP timer) {

    if (timerHandle == NULL_HANDLE) {
        timerHandle = bhmCreateThread(timerThread, NULL, "Timer", 0);
    }

    if (timerEvent == NULL_HANDLE) {
        timerEvent = bhmCreateNamedEvent("TimerEvent", "Event on timer thread");
    }

    if (timer) {
        double delay = timer->expirationTime - bhmGetLocalTime();

        if (PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX "_SCHD",
                    "Next event scheduled: timer[%d] in %10.3fus @ %10.3fus",
                    timer->hartid, delay, timer->expirationTime);
        }

        if (delay < 0.0) {
            // This can happen because calling bhmGetLocalTime() from the thread
            // (i.e. non-processor) context can only give times at quantum
            // boundaries, and an event cannot be scheduled within a quantum
            // once that quantum has started. So just schedule event as early as
            // possible.
            delay = 0.0;
        }

        scheduledTimer = timer;
        bhmTriggerAfter(timerEvent, delay);

    } else {

        scheduledTimer = NULL;
        bhmTriggerEvent(timerEvent);

    }
}

//
// Timer loop:
// - Find the next timer that will expire
// - If a timer is found schedule an event to trigger at that time
// - Wait for an event:
//     - if scheduledTimer is not NULL then the event is that timer's expiration
// - Repeat loop
//
static void timerThread(void *user) {
    while (1) {
        timerDataP nextTimer = NULL;

        // Find next timer scheduled to expire
        Uns32 i;
        for (i = 0; i < numharts; i++) {
            timerDataP timer = getTimer(i);

            if (timer->expirationTime == DBL_MAX) {
                // Skip timers that have not been programmed yet or have been
                // set to the maximum value
            } else if (timer->intSet) {
                // Skip currently pending timers
            } else if (!nextTimer || nextTimer->expirationTime > timer->expirationTime) {
                // Earliest timer seen so far
                nextTimer = timer;
            }
        }

        if (nextTimer) {
            // schedule event for next timer expiration
            // - replaces any existing pending timer expiration
            scheduleTimer(nextTimer);
        }

        // Wait for a timer event
        bhmRestartReason reason = bhmWaitEvent(timerEvent);

        if (reason != BHM_RR_TRIGGERED) {
            bhmMessage("F", PREFIX, "Unexpected bhmRestartReason %d", reason);
        }

        // If this is a timer expiration event then trigger an interrupt
        if (scheduledTimer) {
            setInterrupt(scheduledTimer);

            // Clear currently scheduled timer after triggering
            scheduledTimer = NULL;
        }
    }
}

//
// Update the timer's data based on current mtime/mtimecmp[hartid] values
// - Call after change to mtimecmp for a single timer
// - Call after change to mtime for each timer
// The interrupt for the timer is updated based on the computed values
//
static void updateTimerData(timerDataP timer) {
    Uns32 hartid         = timer->hartid;
    Uns64 timecmp        = bport1_ab_data.mtimecmp[hartid].value;
    Uns64 prevExpiration = timer->expirationTime;

    timer->startTime      = bhmGetLocalTime();
    timer->startCount     = currentMTime(timer->startTime, NULL);
    timer->stopCount      = timecmp;

    if (timer->stopCount < timer->startCount) {
        // Don't allow negative delays - just trigger timer immediately
        timer->stopCount = timer->startCount;
    }

    if (timecmp == -1ULL) {

        // Disable timer when mtimecmp is at the max value for simulator
        // efficiency
        timer->threadDelay    = DBL_MAX;
        timer->expirationTime = DBL_MAX;

        if (PSE_DIAG_MEDIUM && prevExpiration != timer->expirationTime) {
            bhmMessage("I", PREFIX "_SCHD",
                    "timer[%d] @ %10.3fus disabled: mtimecmp=-1",
                    timer->hartid, timer->startTime);
        }

    } else {

        timer->threadDelay    = TICKS_TO_USEC(timer->stopCount - timer->startCount);
        timer->expirationTime = timer->startTime + timer->threadDelay;

        if (PSE_DIAG_MEDIUM && prevExpiration != timer->expirationTime) {
            bhmMessage("I", PREFIX "_SCHD", "timer[%d] @ %10.3fus", timer->hartid, timer->startTime);
            bhmMessage("I", PREFIX "_SCHD", "  mtime=%s", uns64ToDecimal(timer->startCount));
            bhmMessage("I", PREFIX "_SCHD", "  mtimecmp=%s", uns64ToDecimal(timecmp));
            bhmMessage("I", PREFIX "_SCHD", "  threadDelay=%10.3fus", timer->threadDelay);
            bhmMessage("I", PREFIX "_SCHD", "  expirationTime=%10.3fus", timer->expirationTime);
        }
    }

    // Update interrupt based on current mtime and mtimecmp values
    // - this is required to reflect changes due to writes to mtime register
    if (timer->stopCount <= timer->startCount) {
        // timecmp value has already been reached
        setInterrupt(timer);
    } else {
        clearInterrupt(timer);
    }
}

//
// Update all timers
//
static void updateAllTimerData() {
    Uns32 hartid;

    for (hartid = 0; hartid < numharts; hartid++) {
        updateTimerData(getTimer(hartid));
    }

    // Recalulate next timer expiration
    scheduleTimer(NULL);
}

static Bool hartidInRange(Uns32 hartid, const char *type) {
    if (hartid >= numharts) {
        bhmMessage("W", PREFIX,
                "mtimecmp %s ignored. hartid=%d exceeds number of harts implemented = %d",
                type, hartid, numharts);
        return False;
    }
    return True;
}

static Bool accessOk(Uns32 bytes, Uns32 offset, const char *name) {
    if ((bytes != 4) && (bytes != 8)) {
        bhmMessage("W", PREFIX,
            "%d byte access to %s ignored. Only size of 4 or 8 allowed.",
            bytes, name);
        return False;
    }

    Uns32 offsetAlign = offset & (bytes-1);
    if (offsetAlign) {
        bhmMessage("W", PREFIX,
            "%d byte access with alignment of %d bytes to %s ignored.",
            bytes, offsetAlign, name);
        return False;
    }
    return True;
}

static void copyBytes(
    void       *dst,
    const void *src,
    Uns32       dstOffset,
    Uns32       srcOffset,
    Uns32       bytes
 ) {
    Uns8       *dst8 = dst+dstOffset;
    const Uns8 *src8 = src+srcOffset;
    Uns32       i;

    for(i=0; i<bytes; i++) {
        *dst8++ = *src8++;
    }
}

//////////////////////////////// Callbacks ////////////////////////////////

PPM_NBYTE_READ_CB(defaultMemRead) {
    bhmMessage("I", "PPM_DFRD",
        "Read at offset 0x%x ignored - no register defined at this offset",
        offset
    );
    memset(data, 0, bytes);
}

PPM_NBYTE_WRITE_CB(defaultMemWrite) {
    bhmMessage("I", "PPM_DFWR",
        "Write at offset 0x%x ignored - no register defined at this offset",
        offset
    );
}

//
// Read the mtime register
// - compute value based on current simulated time, clock frequency,
//   most recent time mtime was written and the value written at that time
//
PPM_NBYTE_READ_CB(rdMTIME) {
    if (accessOk(bytes, offset, "mtime")) {
        double timeNow   = bhmGetLocalTime();
        Uns64  mtimeNow  = currentMTime(timeNow, NULL);

        copyBytes(data, &mtimeNow, 0, offset & 0x7, bytes);
    }
}

//
// Write the mtime register
// - compute a new offset based on current simulated time, clock frequency,
//   current time and the value written
//
PPM_NBYTE_WRITE_CB(wrMTIME) {
    if (accessOk(bytes, offset, "mtime")) {
        Uns64  ticksNow;
        double timeNow   = bhmGetLocalTime();
        Uns64  mtimeNow  = currentMTime(timeNow, &ticksNow);

        copyBytes(&bport1_ab_data.mtime.value, data, offset & 0x7, 0, bytes);

        // If value does not match the current computed value for mtime
        // then need to compute a new offset and update everything
        if (bport1_ab_data.mtime.value != mtimeNow) {
            mtimeOffset = ticksNow - bport1_ab_data.mtime.value;

            if (PSE_DIAG_LOW) {
                bhmMessage("I", PREFIX, "new mtime=%s", uns64ToDecimal(bport1_ab_data.mtime.value));
            }

            updateAllTimerData();
        }
    }
}

//
// Write the mtimecmp registers
//
// Note: if the 64 bit value is written 32 bits at a time this can result in
//       extra interrupts, but that is how the hardware works. The RiscV
//       privilige spec suggests writing all 1's to the low 32 bits, then writing
//       the high word value, then the low word value
//
PPM_NBYTE_WRITE_CB(wrMTIMECMP) {
    Uns32 hartid = PTR_TO_UNS32(userData);


    if (!accessOk(bytes, offset, "mtimecmp")) {
        // Ignore invalid access size/align
    } else if (!hartidInRange(hartid, "write")) {
        // Ignore out of range accesses
    } else {
        Uns64 oldValue = bport1_ab_data.mtimecmp[hartid].value;

        copyBytes(&bport1_ab_data.mtimecmp[hartid].value, data, offset & 0x7, 0, bytes);

        if (bport1_ab_data.mtimecmp[hartid].value == oldValue) {
            // Ignore if value has not changed
        } else {
            timerDataP timer = getTimer(hartid);

            if (PSE_DIAG_LOW) {
                bhmMessage("I", PREFIX,
                    "new mtimecmp[%d]=%s",
                    hartid, uns64ToDecimal(bport1_ab_data.mtimecmp[hartid].value));
            }

            // Spec states the timer interrupt is de-asserted when the mtimecmp
            // register is written.
            clearInterrupt(timer);

            updateTimerData(timer);

            // Recalculate next timer event which could be modified by this change
            scheduleTimer(NULL);
        }
    }
}

PPM_NBYTE_READ_CB(rdMTIMECMP) {
    Uns32 hartid = PTR_TO_UNS32(userData);

    if (!accessOk(bytes, offset, "mtimecmp")) {
        // Ignore invalid access size/align
    } else if (!hartidInRange(hartid, "read")) {
        // Ignore out of range accesses
    } else {
        copyBytes(data, &bport1_ab_data.mtimecmp[hartid].value, 0, offset & 0x7, bytes);
    }
}

///////////////
// RESET NET //
///////////////

PPM_NET_CB(resetCB) {
    if (PSE_DIAG_LOW) {
        bhmMessage(
            "I", PREFIX "_RNC",
            "Reset net set to %d",
            (Uns32)value
        );
    }
    reset_resetNet(value, NULL);
    updateAllTimerData();
}


PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    bhmDoubleParamValue("clockMHz", &clockMHz);
    if (clockMHz == 0.0) {
        bhmMessage("E", PREFIX, "clockMHz = 0.0 is not legal");
        clockMHz = 1.0;
    }

    bhmUns32ParamValue("numharts", &numharts);
    if (numharts < 1 || numharts > MAXHARTS) {
        bhmMessage("E", PREFIX, "Invalid numharts=%d. Must be between 1 and %d", numharts, MAXHARTS);
        numharts = MAXHARTS;
    }

    // Compute only once to improve performance
    clockDelta = ROUNDING_FACTOR_USEC;

    // Initialize hartid and expiration time for each timer
    Uns32 i;
    for (i = 0; i < numharts; i++) {
        timerDataP timer = getTimer(i);

        timer->hartid = i;
        timer->expirationTime = DBL_MAX;
    }

    timerHandle = NULL_HANDLE;
    timerEvent  = NULL_HANDLE;
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}


