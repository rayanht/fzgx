#include "types.h"

struct fn_80017590_Arg1 {
    u8 pad_0[0x38];
    u32 unk_38;
};

void fn_80017590(u32 arg0, struct fn_80017590_Arg1 *arg1) {
    if (arg1->unk_38 != 0) {
        ((void (*)(void))arg1->unk_38)();
    }
}
