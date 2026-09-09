#include <dolphin/os.h>
#include "sdk_addresses.h"
#pragma peephole off

typedef struct Unk {
    u8 pad[0x24];
    u32 resetCode;
} Unk;

// Hardware or OS state can change asynchronously.
volatile u8
    DAT_800030e2 : FZGX_ADDR_DAT_800030e2; // fzgx-allow: S2 SDK asynchronous state

// Hardware or OS state can change asynchronously.
volatile Unk
    DAT_cc003000 : FZGX_ADDR_DAT_cc003000; // fzgx-allow: S2 SDK asynchronous state

u32 OSGetResetCode(void) {
    if (DAT_800030e2 != 0) {
        return 0x80000000;
    }
    return ((DAT_cc003000.resetCode & ~7) >> 3);
}
