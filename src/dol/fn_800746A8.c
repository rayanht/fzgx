#include "types.h"

typedef struct GlobalState {
    u8 unk_00[9];
    u8 unk_09;
    u8 unk_0A[2];
    s32 unk_0C;
} GlobalState;

extern GlobalState *lbl_801A6D38;
extern void GXSetLineWidth(u8, s32);

void fn_800746A8(u8 value, s32 arg, u32 lab_unused0) {
    if (lbl_801A6D38->unk_09 != value || lbl_801A6D38->unk_0C != arg) {
        GXSetLineWidth(value, arg);
        lbl_801A6D38->unk_09 = value;
        lbl_801A6D38->unk_0C = arg;
    }
}
