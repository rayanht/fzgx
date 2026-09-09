#include "types.h"

struct fn_800455B8_Arg1 {
    u16 type;
};

extern s32 fn_800456A0(void *arg0);
extern s32 fn_80045FEC(struct fn_800455B8_Arg1 *arg0);
extern s32 fn_800462F8(void *arg0, struct fn_800455B8_Arg1 *arg1, void *arg2);
extern s32 fn_80042568(struct fn_800455B8_Arg1 *arg0);
extern s32 fn_80043050(void *arg0, struct fn_800455B8_Arg1 *arg1, void *arg2);
extern s32 fn_80043CCC(struct fn_800455B8_Arg1 *arg0);
extern s32 fn_80043B48(void *arg0, struct fn_800455B8_Arg1 *arg1, void *arg2);
extern s32 fn_80044C0C(struct fn_800455B8_Arg1 *arg0);
extern s32 fn_80044A94(void *arg0, struct fn_800455B8_Arg1 *arg1, void *arg2);

s32 fn_800455B8(void *arg0, struct fn_800455B8_Arg1 *arg1, void *arg2) {
    if (arg1->type == 0x8000) {
        return fn_800456A0(arg0);
    }
    if (fn_80045FEC(arg1)) {
        return fn_800462F8(arg0, arg1, arg2);
    }
    if (fn_80042568(arg1)) {
        return fn_80043050(arg0, arg1, arg2);
    }
    if (fn_80043CCC(arg1)) {
        return fn_80043B48(arg0, arg1, arg2);
    }
    if (fn_80044C0C(arg1)) {
        return fn_80044A94(arg0, arg1, arg2);
    }
    return -1;
}
