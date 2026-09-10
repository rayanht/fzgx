#include "types.h"
#include "dol/globals.h"

extern void fn_80037128(s32, s32, s32, s32, u8, s32);

void fn_80072D64(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    u8 *entry;

    entry = (u8 *)lbl_801A6D38 + arg0 * 0x14 + 0x2F0;
    if (*(s32 *)(entry + 0x10) == arg5 &&
        *(s32 *)(entry + 0x8) == arg3 &&
        *(u8 *)(entry + 0xc) == arg4 &&
        *(s32 *)(entry + 0x0) == arg1 &&
        *(s32 *)(entry + 0x4) == arg2) {
        return;
    }

    fn_80037128(arg0, arg1, arg2, arg3, arg4, arg5);
    *(s32 *)(entry + 0x0) = arg1;
    *(s32 *)(entry + 0x4) = arg2;
    *(s32 *)(entry + 0x8) = arg3;
    *(u8 *)(entry + 0xc) = arg4;
    *(s32 *)(entry + 0x10) = arg5;
}
