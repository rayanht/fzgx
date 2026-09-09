#include "types.h"

struct fn_8005174C_Arg0 {
    u8 pad_0[0x346];
    s8 index;
    u8 pad_347[9];
    u32 field350;
};

extern u32 fn_80053A38(u32);
extern u32 memset(u32, u32, u32);
extern u32 lbl_80187330[16];

void fn_8005174C(struct fn_8005174C_Arg0 *arg0) {
    struct fn_8005174C_Arg0 *obj;
    s32 index;
    u32 field350;

    obj = arg0;
    field350 = obj->field350;
    index = obj->index;
    if (field350 != 0) {
        obj->field350 = 0;
        fn_80053A38(field350);
    }
    memset((u32)obj, 0, 3000);
    lbl_80187330[index] = 0;
}
