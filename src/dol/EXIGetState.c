#include <dolphin/exi/EXIPriv.h>
#pragma scheduling off

extern EXIControl Ecb_8015CCB0[3];

u32 EXIGetState(s32 chan) {
    EXIControl *exi = &Ecb_8015CCB0[chan];
    return (u32)exi->state;
}
