#include "types.h"

struct fn_80070A58_State {
    u8 unk_0[0x198];
    f32 unk_198;
    f32 unk_19c;
    f32 unk_1a0;
    f32 unk_1a4;
    s32 unk_1a8;
    u8 unk_1ac;
    u8 unk_1ad;
    u8 unk_1ae;
    u8 unk_1af;
};

extern const f32 lbl_801A7410;
extern const f32 lbl_801A7414;
extern const f32 lbl_801A7420;
extern const f32 lbl_801A7424;
extern struct fn_80070A58_State *lbl_801A6D00;

void fn_80070A58(void) {
    lbl_801A6D00->unk_198 = lbl_801A7410;
    lbl_801A6D00->unk_19c = lbl_801A7414;
    lbl_801A6D00->unk_1a0 = lbl_801A7420;
    lbl_801A6D00->unk_1a4 = lbl_801A7424;
    lbl_801A6D00->unk_1a8 = -1;
    lbl_801A6D00->unk_1ac = 0;
    lbl_801A6D00->unk_1ad = 1;
    lbl_801A6D00->unk_1ae = 1;
    lbl_801A6D00->unk_1af = 0;
}
