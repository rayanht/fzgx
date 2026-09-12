#include "types.h"

typedef struct fn_80049BF4_Vtbl {
    u8 pad_0[0x18];
    void (*unk18)(void *, s32, s32, void *);
    void (*unk1C)(void *, s32, void *);
    void (*unk20)(void *, s32, void *);
} fn_80049BF4_Vtbl;

typedef struct fn_80049BF4_Obj {
    fn_80049BF4_Vtbl *vtbl;
} fn_80049BF4_Obj;

typedef struct fn_80049BF4_Buf {
    void *data;
    u32 size;
} fn_80049BF4_Buf;

struct fn_80049BF4_Arg0 {
    u8 pad_0[0xC];
    fn_80049BF4_Obj *unk_C;
};

extern void * memcpy(void *, const void *, u32);

u32 fn_80049BF4(struct fn_80049BF4_Arg0 *arg0) {
    u8 *p1 = (u8 *)arg0;
    u8 *p2 = (u8 *)arg0;
    s32 i = 0;
    u32 sum = 0;
    fn_80049BF4_Obj *v0 = arg0->unk_C;
    s16 v5;
    s16 d;
    s32 x;
    s16 v7;
    fn_80049BF4_Buf b1;
    fn_80049BF4_Buf b2;
    fn_80049BF4_Buf b3;
    u8 b8[4];

    while (i < (s32)*(u32 *)((u8 *)arg0 + 0x58)) {
        v5 = *(s16 *)((u8 *)arg0 + 0x2D0);
        d = *(s16 *)(p1 + 0x290) - 1;
        x = d ^ v5;
        *(s16 *)((u8 *)arg0 + 0x2D0) =
            (s16)(*(s16 *)((u8 *)arg0 + 0x2D4) + v5 * *(s16 *)((u8 *)arg0 + 0x2D2));
        *(s16 *)((u8 *)arg0 + 0x2D0) = *(s16 *)((u8 *)arg0 + 0x2D0) & 0x7FFF;
        if (*(s32 *)(p2 + 0x2A8) == 0 && *(s32 *)(p2 + 0x2AC) == 0 &&
            *(s32 *)(p2 + 0x2B0) == 0 && *(s32 *)(p2 + 0x2B4) == 0) {
            x = 0;
        }
        v7 = (s16)x;
        b8[0] = (s32)v7 >> 8;
        v0->vtbl->unk18(v0, 0, 1, &b1);
        if ((s32)b1.size < 1) {
            v0->vtbl->unk1C(v0, 0, &b1);
        } else {
            memcpy(b1.data, b8, 1);
            v0->vtbl->unk20(v0, 1, &b1);
        }
        b8[0] = v7;
        v0->vtbl->unk18(v0, 0, 1, &b2);
        if ((s32)b2.size < 1) {
            v0->vtbl->unk1C(v0, 0, &b2);
        } else {
            memcpy(b2.data, b8, 1);
            v0->vtbl->unk20(v0, 1, &b2);
        }
        v0->vtbl->unk18(v0, 0, 16, &b3);
        if ((s32)b3.size < 16) {
            v0->vtbl->unk1C(v0, 0, &b3);
        } else {
            memcpy(b3.data, p2 + 0x2A8, 16);
            v0->vtbl->unk20(v0, 1, &b3);
        }
        sum += 18;
        p1 += 2;
        p2 += 0x10;
        i++;
    }
    return sum;
}
