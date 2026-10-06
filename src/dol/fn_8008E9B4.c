#include <dolphin/exi/EXIPriv.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

vu32 __EXIRegs[16] : FZGX_ADDR___EXIRegs;

extern EXIControl *lbl_801A6678;

static inline void CompleteTransfer(void) {
    u8 *buf;
    u32 data;
    int i;
    int len;

    if (lbl_801A6678->state & (0x01 | 0x02)) {
        if ((lbl_801A6678->state & 0x02) && (len = lbl_801A6678->immLen)) {
            buf = lbl_801A6678->immBuf;
            data = __EXIRegs[2 * 5 + 4];
            for (i = 0; i < len; i++) {
                *buf++ = (u8)((data >> ((3 - i) * 8)) & 0xff);
            }
        }
        lbl_801A6678->state &= ~(0x01 | 0x02);
    }
}

void fn_8008E9B4(void) {
    EXIControl *exi = lbl_801A6678;
    BOOL enabled;

    while (exi->state & 0x04) {
        if ((__EXIRegs[2 * 5 + 3] & 1) == 0) {
            enabled = OSDisableInterrupts();
            CompleteTransfer();
            OSRestoreInterrupts(enabled);
            break;
        }
    }
}
