#include "types.h"

typedef s32 (*fn_8007FC34_Fn0)(u32, u32 *, s32, u32);

typedef struct fn_8007FC34_Mode {
    u32 open_mode : 2;
    u32 io_mode : 3;
    u32 buffer_mode : 2;
    u32 file_kind : 3;
    u32 file_orientation : 2;
    u32 binary_io : 1;
} fn_8007FC34_Mode;

typedef struct fn_8007FC34_State {
    u8 io_state : 3;
    u8 free_buffer : 1;
    u8 eof : 1;
    u8 error : 1;
    u8 pad : 2;
} fn_8007FC34_State;

struct fn_8007FC34_Arg0 {
    u32 unk_0;
    fn_8007FC34_Mode mode;
    fn_8007FC34_State state;
    u8 unk_9;
    u8 unk_A;
    u8 pad_B[0xD];
    u32 unk_18;
    u32 unk_1C;
    u8 pad_20[4];
    u32 unk_24;
    u32 unk_28;
    u8 pad_2C[8];
    u32 unk_34;
    fn_8007FC34_Fn0 unk_38;
    u8 pad_3C[0xC];
    u32 unk_48;
};

extern s32 __flush_buffer(struct fn_8007FC34_Arg0 *, u32);
extern u32 lbl_801A6DE0;

s32 fn_8007FC34(struct fn_8007FC34_Arg0 *arg0, u32 arg1, s32 arg2) {
    u32 v0;
    u32 v3;
    u32 loc_8;
    s32 t0;

    loc_8 = arg1;
    if (arg0->mode.file_kind != 1 || arg0->unk_A != 0) {
        lbl_801A6DE0 = 40;
        return -1;
    }
    if (arg0->state.io_state == 1) {
        t0 = __flush_buffer(arg0, 0);
        if (t0 != 0) {
            arg0->unk_A = 1;
            arg0->unk_28 = 0;
            lbl_801A6DE0 = 40;
            return -1;
        }
    }
    if (arg2 == 1) {
        arg2 = 0;
        if ((arg0->mode.file_kind != 1 && arg0->mode.file_kind != 2) || arg0->unk_A != 0) {
            lbl_801A6DE0 = 40;
            v0 = -1;
        } else {
            v3 = arg0->state.io_state;
            if (v3 == 0) {
                v0 = arg0->unk_18;
            } else {
                v0 = arg0->unk_34 + (arg0->unk_24 - arg0->unk_1C);
                if (v3 >= 3) {
                    v0 -= v3 - 2;
                }
            }
        }
        loc_8 += v0;
    }
    if (arg2 != 2 && arg0->mode.io_mode != 3 &&
        (arg0->state.io_state == 2 || arg0->state.io_state == 3)) {
        if (loc_8 >= arg0->unk_18 || loc_8 < arg0->unk_34) {
            arg0->state.io_state = 0;
        } else {
            arg0->unk_24 = arg0->unk_1C + (loc_8 - arg0->unk_34);
            arg0->unk_28 = arg0->unk_18 - loc_8;
            arg0->state.io_state = 2;
        }
    } else {
        arg0->state.io_state = 0;
    }
    if (arg0->state.io_state == 0) {
        if (arg0->unk_38 != 0) {
            t0 = arg0->unk_38(arg0->unk_0, &loc_8, arg2, arg0->unk_48);
            if (t0 != 0) {
                arg0->unk_A = 1;
                arg0->unk_28 = 0;
                lbl_801A6DE0 = 40;
                return -1;
            }
        }
        arg0->unk_9 = 0;
        arg0->unk_18 = loc_8;
        arg0->unk_28 = 0;
    }
    return 0;
}
