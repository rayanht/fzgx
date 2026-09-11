#include "types.h"

extern u32 fn_80007654(u32);
extern void fn_80007664(void *, u32, u32);
extern u32 fn_80007730(u32, u32, u32, u32, u32);
extern u32 lbl_801221A0[];
extern u32 lbl_801A6400;
extern void OSPanic(u8 *, s32, u8 *, ...);

typedef struct Entry {
    u32 a : 1;
    u32 b : 24;
    u32 c : 1;
    u32 d : 6;
    u8 pad[3];
    u8 e : 1;
    u8 f : 1;
    u8 g : 1;
    u8 h : 3;
    u8 i : 2;
} Entry;

void fn_8000740C(u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4) {
    u32 v0;
    u32 v1;
    u32 v2;
    u32 unk_1;
    u8 loc_20;
    Entry *t0;
    u32 t2;

    t0 = (Entry *)fn_80007730(arg0, arg1, arg2, arg3, arg4);
    v1 = (u32)t0;
    if (t0 == 0) {
        v1 = (u32)&lbl_801A6400;
        v2 = (u32)&lbl_801221A0;
        v0 = 461;
        OSPanic((u8 *)(u32)v1, v0, (u8 *)(u32)v2);
    }
    t2 = fn_80007654(arg0);
    t0->b = t2;
    t0->d = arg0 >> 22;
    t0->f = arg2;
    t0->g = arg3;
    t0->i = arg4;
    fn_80007664(t0, arg0, arg1);
}
