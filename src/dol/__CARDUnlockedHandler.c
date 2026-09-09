#include "types.h"

extern s32 EXIProbe(s32 chan);
extern u32 lbl_80177960[];

typedef void (*CardUnlockedCallback)(s32 chan, s32 result);

void __CARDUnlockedHandler(s32 chan) {
    u32 offset;
    u32 callback;

    offset = chan * 272;
    callback = *(u32 *)((u8 *)((u8 *)&lbl_80177960 + offset) + 220);
    if (callback != 0) {
        *(u32 *)((u8 *)((u8 *)&lbl_80177960 + offset) + 220) = 0;
        ((CardUnlockedCallback)callback)(chan, EXIProbe(chan) != 0 ? 1 : -3);
    }
}
