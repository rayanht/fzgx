#ifndef DOLPHIN_SI_SIPRIV_H
#define DOLPHIN_SI_SIPRIV_H
#include <dolphin/si.h>
#include <dolphin/os.h>

#define SI_COMCSR_TCINT 0x80000000u
#define SI_COMCSR_TSTART 0x00000001u

typedef struct SIControl {
    s32 chan;
    u32 poll;
    u32 inputBytes;
    void *input;
    SICallback callback;
} SIControl;

typedef struct SIPacket {
    s32 chan;
    void *output;
    u32 outputBytes;
    void *input;
    u32 inputBytes;
    SICallback callback;
    OSTime fire;
} SIPacket;
#endif
