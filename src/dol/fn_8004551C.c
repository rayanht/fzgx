#include "types.h"


struct fn_8004551C_Arg0 {
    u8 pad_0[0x98];
    s16 unk_98;
    s16 unk_9A;
};

u32 fn_8004551C(struct fn_8004551C_Arg0 *arg0) {
    if (arg0->unk_98 == 0) {
        return 0x10;
    }
    if (arg0->unk_98 == 2) {
        if (arg0->unk_9A == 2) {
            return 4;
        }
        if (arg0->unk_9A == 1) {
            return 8;
        }
        return 0x10;
    }
    if (arg0->unk_98 == 1) {
        return arg0->unk_9A == 2 ? 4 : 0x10;
    }
    return 0x10;
}
