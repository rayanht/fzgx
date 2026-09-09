#include "types.h"

extern int fn_12_CAB4(void *movie, void *out_a, void *out_b);
extern int fn_12_A660(int arg0, u32 arg1);

int fn_12_AA38(void *movie, void *out_a, void *out_b, void *out_c) {
    s32 scale;

    if (fn_12_CAB4(movie, out_a, out_b)) {
        return fn_12_A660(0, 0xff03020f);
    }

    *(u32 *)out_a = *(u32 *)((u8 *)movie + 0x27c) << 11;
    *(u32 *)out_b = *(u32 *)((u8 *)movie + 0x28c);
    scale = *(s32 *)((u8 *)movie + 0x278);

    if (scale == 0x3FFFF) {
        *(u32 *)out_c = -1;
    } else {
        *(s32 *)out_c =
            (*(s32 *)((u8 *)movie + 0x28c) * scale) / 1800;
    }

    return 0;
}
