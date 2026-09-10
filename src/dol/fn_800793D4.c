#include "types.h"

extern void *memset(void *, int, u32);
extern void DCFlushRangeNoSync(void *, u32);
extern u32 LCStoreBlocks(void *, void *, u32);
extern u32 fn_8000B8AC(u32);
extern u32 lbl_801A6DB0;
extern s32 lbl_801A6DB8;

u32 fn_800793D4(u8 *arg0, u32 arg1, u32 arg2) {
    u32 i;
    u32 blocks;
    u32 tail;
    u32 chunks;
    s32 did;

    did = 0;
    if (lbl_801A6DB8 == 0) {
        return (u32)memset(arg0, arg1 & 0xFF, arg2);
    }
    tail = arg2 & 0x1F;
    blocks = arg2 >> 10;
    chunks = ((arg2 - (arg2 & ~0x3FF)) - tail) >> 5;
    DCFlushRangeNoSync(arg0, arg2);
    if (blocks != 0) {
        memset((void *)lbl_801A6DB0, arg1 & 0xFF, 0x400);
        did = 1;
        for (i = 0; i < blocks; i++) {
            fn_8000B8AC(0xE);
            LCStoreBlocks(arg0, (void *)lbl_801A6DB0, 0x20);
            arg0 += 0x400;
        }
    }
    if (chunks != 0) {
        if (did == 0) {
            memset((void *)lbl_801A6DB0, arg1 & 0xFF, chunks << 5);
        }
        fn_8000B8AC(0xE);
        LCStoreBlocks(arg0, (void *)lbl_801A6DB0, chunks);
        arg0 += chunks << 5;
    }
    if (tail != 0) {
        memset(arg0, arg1 & 0xFF, tail);
    }
    return fn_8000B8AC(0);
}
