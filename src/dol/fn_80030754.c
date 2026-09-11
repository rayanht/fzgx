#include "types.h"

struct fn_80030754_Local {
    u8 pad_0[0x34];
    u8 unk_34;
    u8 pad_35[0x0B];
};

extern s32 fn_80030380(void *arg0, void *arg1, struct fn_80030754_Local *arg2);
extern void fn_8003043C(void *arg0, void *arg1, struct fn_80030754_Local *arg2, void *arg3);

s32 fn_80030754(void *arg0, void *arg1, u8 arg2, void *arg3) {
    struct fn_80030754_Local local;
    s32 result;

    result = fn_80030380(arg0, arg1, &local);
    if (result < 0) {
        return result;
    }
    local.unk_34 = arg2;
    fn_8003043C(arg0, arg1, &local, arg3);
}
