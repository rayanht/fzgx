#include "types.h"

extern u32 memcpy(u32, u32, u32);
extern void fn_8008E73C(void *);
extern void fn_8008E718(void *);

struct fn_8008E114_Arg0 {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
    u32 unk_c;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
};

s32 fn_8008E114(struct fn_8008E114_Arg0 *arg0, u32 arg1, u32 arg2) {
    u32 v2;

    if (arg2 > arg0->unk_10) {
        return -1;
    }
    fn_8008E73C(&arg0->unk_18);
    v2 = arg0->unk_c - (arg0->unk_0 - arg0->unk_8);
    if (arg2 < v2) {
        memcpy(arg1, arg0->unk_0, arg2);
        arg0->unk_0 += arg2;
    } else {
        memcpy(arg1, arg0->unk_0, v2);
        memcpy(arg1 + v2, arg0->unk_8, arg2 - v2);
        arg0->unk_0 = arg0->unk_8 + arg2 - v2;
    }
    if (arg0->unk_c == arg0->unk_0 - arg0->unk_8) {
        arg0->unk_0 = arg0->unk_8;
    }
    arg0->unk_14 += arg2;
    arg0->unk_10 -= arg2;
    fn_8008E718(&arg0->unk_18);
    return 0;
}
