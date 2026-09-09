#include "types.h"

extern u32 lbl_801A6D38;
extern void fn_80037BC0(u8 arg0, s32 arg1, u8 arg2);

typedef struct CacheData {
    u8 unk_00;
    u8 unk_01[3];
    s32 unk_04;
    u8 unk_08;
} CacheData;

void fn_80074918(u8 arg0, s32 arg1, u8 arg2) {
    CacheData *cache;

    cache = (CacheData *)lbl_801A6D38;
    if (cache->unk_00 == arg0 && cache->unk_04 == arg1 && cache->unk_08 == arg2) {
        return;
    }

    fn_80037BC0(arg0, arg1, arg2);
    ((CacheData *)lbl_801A6D38)->unk_00 = arg0;
    ((CacheData *)lbl_801A6D38)->unk_04 = arg1;
    ((CacheData *)lbl_801A6D38)->unk_08 = arg2;
}
