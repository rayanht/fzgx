#include "types.h"

typedef void (*fn_8004C980_Fn0)(u32, u32);
struct fn_8004C980_Callback {
    u8 pad_0[20];
    fn_8004C980_Fn0 fn;
};
struct fn_8004C980_Arg0 {
    u8 pad_0[0x8];
    u32 unk_8;
    u8 pad_C[0x30];
    s16 unk_3C;
    s16 unk_3E;
};

extern void fn_8004A550(u32, u32, u32);
extern u32 fn_8004AC04(u32, u32);
extern u32 fn_8004AC4C(u32, u32, u32);
extern u32 fn_8004AE94(u32, u32);
extern void fn_8004AD84(u32);
extern void fn_8004B0EC(u32);
extern void fn_8004B180(u32, u32, u32, u32, u32);
extern s32 fn_8004ADF4(u32);
extern u32 fn_80042198(u32, u32);
extern u32 fn_8004212C(u32);
extern u32 ADXAMP_Start(u32);
extern u32 lbl_80178CB8[];

void fn_8004C980(struct fn_8004C980_Arg0 *arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4) {
    s32 v2;
    u32 v0;
    u32 v1;
    u32 v3;
    u32 v4;

    fn_8004A550(arg0->unk_8, (s32)arg0->unk_3E << 11, (s32)arg0->unk_3C << 11);
    fn_8004AC04(arg0->unk_8, 25);
    fn_8004AC4C(arg0->unk_8, 0, 0);
    fn_8004AE94(arg0->unk_8, 0);
    fn_8004AD84(arg0->unk_8);
    fn_8004B0EC(arg0->unk_8);
    fn_8004B180(arg0->unk_8, arg1, arg2, arg3, arg4);
    fn_8004ADF4(arg0->unk_8);
    v0 = *(u32 *)((u8 *)arg0 + 16);
    v1 = (u32)arg0;
    v2 = 0;
    while (v2 < (s8)*(u8 *)((u8 *)arg0 + 3)) {
        ((struct fn_8004C980_Callback *)(*(u32 *)((u8 *)*(u32 *)((u8 *)v1 + 24))))->fn(
            *(u32 *)((u8 *)v1 + 24),
            *(u32 *)((u8 *)*(u32 *)((u8 *)v1 + 24)));
        v1 += 4;
        v2++;
    }
    fn_80042198(*(u32 *)((u8 *)arg0 + 4), v0);
    *(u32 *)((u8 *)arg0 + 20) = v0;
    fn_8004212C(*(u32 *)((u8 *)arg0 + 4));
    *(u8 *)((u8 *)arg0 + 1) = 1;
    v3 = (0x80000000 - 1);
    *(u32 *)((u8 *)arg0 + 76) = 0;
    *(u8 *)((u8 *)arg0 + 113) = 0;
    *(u32 *)((u8 *)arg0 + 140) = v3;
    *(u32 *)((u8 *)arg0 + 144) = -1;
    *(u32 *)((u8 *)arg0 + 156) = 0;
    *(u32 *)((u8 *)arg0 + 164) = 0;
    *(u32 *)((u8 *)arg0 + 160) = lbl_80178CB8[0];
    v4 = *(u32 *)((u8 *)arg0 + 116);
    if (v4 != 0) {
        ADXAMP_Start(v4);
    }
}
