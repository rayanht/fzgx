#include <types.h>
#include <dolphin/dvd.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/types.h>

void DVDPause();

void DVDResume();

BOOL fn_800198FC(DVDCommandBlock *block, DVDCBCallback callback);

BOOL DVDCancelAllAsync(DVDCBCallback callback);

void __DVDClearWaitingQueue();

DVDCommandBlock *__DVDPopWaitingQueue();

DVDCommandBlock *__DVDPopWaitingQueue();

extern DVDCommandBlock *executing_801A68C0;

// Hardware or OS state can change asynchronously.
extern volatile BOOL PauseFlag_801A68CC; // fzgx-allow: S2 SDK asynchronous state

// Hardware or OS state can change asynchronously.
extern volatile BOOL PausingFlag_801A68D0; // fzgx-allow: S2 SDK asynchronous state

extern vu32 lbl_801A68E0;

extern DVDCBCallback lbl_801A68E4;

void stateReady();

void stateReady();

static inline void DVDPause(void) {
    BOOL level;
    level = OSDisableInterrupts();
    PauseFlag_801A68CC = 1;
    if (executing_801A68C0 == (DVDCommandBlock *)0) {
        PausingFlag_801A68D0 = 1;
    }
    OSRestoreInterrupts(level);
}

static inline void DVDResume(void) {
    BOOL level;
    level = OSDisableInterrupts();
    PauseFlag_801A68CC = 0;
    if (PausingFlag_801A68D0) {
        PausingFlag_801A68D0 = 0;
        stateReady();
    }
    OSRestoreInterrupts(level);
}

static inline BOOL DVDCancelAllAsync(DVDCBCallback callback) {
    BOOL enabled;
    DVDCommandBlock *p;
    BOOL retVal;
    enabled = OSDisableInterrupts();
    DVDPause();
    while ((p = __DVDPopWaitingQueue()) != 0) {
        fn_800198FC(p, 0);
    }
    if (executing_801A68C0)
        retVal = fn_800198FC(executing_801A68C0, callback);
    else {
        retVal = 1;
        if (callback)
            (*callback)(0, 0);
    }
    DVDResume();
    OSRestoreInterrupts(enabled);
    return retVal;
}

void fn_80019D48(DVDCBCallback callback) {
    BOOL enabled;
    enabled = OSDisableInterrupts();
    __DVDClearWaitingQueue();
    if (lbl_801A68E0) {
        lbl_801A68E4 = callback;
    } else {
        if (executing_801A68C0) {
            executing_801A68C0->callback = 0;
        }
        DVDCancelAllAsync(callback);
    }
    OSRestoreInterrupts(enabled);
}
