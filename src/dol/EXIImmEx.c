#include <dolphin/exi/EXIPriv.h>
#pragma scheduling off

BOOL EXIImmEx(s32 chan, void *buf, s32 len, u32 mode) {
    s32 xLen;
    while (len) {
        xLen = (len < 4) ? len : 4;
        if (!EXIImm(chan, buf, xLen, mode, ((void *)0))) {
            return 0;
        }
        if (!EXISync(chan)) {
            return 0;
        }
        (u8 *)buf += xLen;
        len -= xLen;
    }
    return 1;
}
