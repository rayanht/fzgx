#include <dolphin/os.h>
#include <dolphin/os/OSThread.h>
#include "sdk_addresses.h"

u32 fn_8000BFC0();

OSThread *__OSCurrentThread : FZGX_ADDR___OSCurrentThread;

void OSClearStack(u8 val) {
    register u32 sp;
    register u32 *p;
    register u32 pattern;
    pattern = ((u32)val << 24) | ((u32)val << 16) | ((u32)val << 8) | (u32)val;
    sp = fn_8000BFC0();
    for (p = __OSCurrentThread->stackEnd + 1; p < (u32 *)sp; ++p) {
        *p = pattern;
    }
}
