#include "types.h"

struct fn_80065A7C_State {
    u8 pad_0[0x340];
    u32 unk_340[0x40];
    u8 pad_440[0x19];
    u8 unk_459;
};

extern struct fn_80065A7C_State *lbl_801A6C80;

void fn_80065A7C(u32 arg0) {
    if (lbl_801A6C80->pad_440[0] >= 0x40) {
        return;
    }
    lbl_801A6C80->unk_340[lbl_801A6C80->unk_459] = arg0;
    lbl_801A6C80->unk_459 = (lbl_801A6C80->unk_459 + 1) & 0x3f;
    lbl_801A6C80->pad_440[0] = lbl_801A6C80->pad_440[0] + 1;
}
