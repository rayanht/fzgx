#include "types.h"

struct fn_80046C28_Arg1 {
    u32 unk_0;
};
struct fn_80046C28_Arg2 {
    u16 unk_0;
};
struct fn_80046C28_Arg3 {
    u8 unk_0;
};
struct fn_80046C28_Arg4 {
    s8 unk_0;
};
struct fn_80046C28_Arg5 {
    s8 unk_0;
};
struct fn_80046C28_Arg6 {
    u8 unk_0;
};
struct fn_80046C28_Arg7 {
    u32 unk_0;
};
struct fn_80046C28_Data {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
    u8 b4;
    u8 b5;
    u8 b6;
    u8 b7;
    u8 b8;
    u8 b9;
    u8 b10;
    u8 b11;
    u8 b12;
    u8 b13;
    u8 b14;
    u8 b15;
};

s32 fn_80046C28(struct fn_80046C28_Data *arg0, u32 arg1, struct fn_80046C28_Arg2 *arg2, struct fn_80046C28_Arg3 *arg3, struct fn_80046C28_Arg4 *arg4, struct fn_80046C28_Arg5 *arg5, struct fn_80046C28_Arg6 *arg6, struct fn_80046C28_Arg7 *arg7, struct fn_80046C28_Arg1 *arg8, struct fn_80046C28_Arg1 *arg9) {
    if ((s32)arg1 < 16) {
        return -1;
    }
    if ((u16)((arg0->b0 << 8) | arg0->b1) != 32768) {
        return -2;
    }
    arg2->unk_0 = ((arg0->b2 << 8) | arg0->b3) + 4;
    arg3->unk_0 = arg0->b4;
    arg5->unk_0 = arg0->b5;
    arg4->unk_0 = arg0->b6;
    arg6->unk_0 = arg0->b7;
    arg7->unk_0 = (arg0->b8 << 24) | (arg0->b9 << 16) | (arg0->b10 << 8) | arg0->b11;
    arg8->unk_0 = (arg0->b12 << 24) | (arg0->b13 << 16) | (arg0->b14 << 8) | arg0->b15;
    if (arg4->unk_0 == 0) {
        arg9->unk_0 = 0;
    } else {
        arg9->unk_0 = ((arg5->unk_0 - 2) << 3) / arg4->unk_0;
    }
    return 0;
}
