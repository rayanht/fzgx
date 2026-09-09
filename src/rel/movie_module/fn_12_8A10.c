#include "types.h"

typedef u32 (*fn_12_8A10_Fn0)(u32, u32, void *, u32);
struct fn_12_8A10_Arg0 {
    u8 pad_0[0x254];
    u32 unk_254;
    u8 pad_258[0x38];
    u32 unk_290;
    u8 pad_294[0x74];
    u32 unk_308;
};

extern void fn_12_8878(void *, u32, void *, void *);

void fn_12_8A10(struct fn_12_8A10_Arg0 *arg0) {
    u32 v0;
    u32 v1;
    u32 v2;
    s16 v3;
    u32 v4;
    struct { u32 a[2]; } loc_8;
    /* frame */
    v0 = ((u32)arg0 + 288);
    v1 = ((u32)arg0 + 580);
    v2 = arg0->unk_254;
    arg0->unk_254 = (v2 + 384);
    ((fn_12_8A10_Fn0)arg0->unk_290)((u32)arg0, arg0->unk_308, &loc_8, v1);
    v3 = *(s16 *)((u8 *)v1 + 14);
    *(u32 *)((u8 *)v0 + 4) = (*(u32 *)((u8 *)v1 + 0) + loc_8.a[0]);
    *(u32 *)((u8 *)v0 + 12) = (*(u32 *)((u8 *)v1 + 4) + loc_8.a[0]);
    v4 = *(u32 *)((u8 *)v1 + 8);
    *(u32 *)((u8 *)v0 + 20) = (v4 + loc_8.a[1]);
    *(u32 *)((u8 *)v0 + 28) = (*(u32 *)((u8 *)v0 + 20) + 8);
    *(u32 *)((u8 *)v0 + 36) = (*(u32 *)((u8 *)v0 + 20) + (v3 << 3));
    *(u32 *)((u8 *)v0 + 44) = (*(u32 *)((u8 *)v0 + 36) + 8);
    fn_12_8878((void *)((u32)arg0 + 832), v2, (void *)v0, (void *)*(u32 *)((u8 *)(u32)arg0 + 64));
}
