#include "types.h"
#include "dol/globals.h"

extern void GXSetTevOrder(s32, s32, s32, s32);

void fn_800734A8(u32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *p;
    u8 *q;

    p = (u8 *)lbl_801A6D38 + (arg0 << 4) + 0x570;
    if (arg2 >= 8) {
        if (*(s32 *)(p + 0) != arg1 || *(s32 *)(p + 4) != 0xff ||
            *(s32 *)(p + 8) != arg3) {
            GXSetTevOrder(arg0, arg1, arg2, arg3);
            *(s32 *)(p + 0) = arg1;
            *(s32 *)(p + 4) = 0xff;
            *(s32 *)(p + 8) = arg3;
            *(u16 *)(p + 0xc) = 0;
            *(u16 *)(p + 0xe) = 0;
        }
    } else {
        q = (u8 *)lbl_801A6D38 + arg2 * 36 + 0x720;
        if (*(s32 *)(p + 0) != arg1 || *(s32 *)(p + 4) != arg2 ||
            *(s32 *)(p + 8) != arg3 ||
            *(u16 *)(p + 0xc) != *(u16 *)(q + 0x20) ||
            *(u16 *)(p + 0xe) != *(u16 *)(q + 0x22)) {
            GXSetTevOrder(arg0, arg1, arg2, arg3);
            *(s32 *)(p + 0) = arg1;
            *(s32 *)(p + 4) = arg2;
            *(s32 *)(p + 8) = arg3;
            *(u16 *)(p + 0xc) = *(u16 *)(q + 0x20);
            *(u16 *)(p + 0xe) = *(u16 *)(q + 0x22);
        }
    }
}
