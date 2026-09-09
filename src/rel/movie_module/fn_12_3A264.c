#include "types.h"

typedef struct Fn12_3A264_Object {
    u8 _pad0[4];
    s32 unk4;
    s32 unk8;
    u8 _padC[0x34];
    u32 unk40;
} Fn12_3A264_Object;

extern const char lbl_12_rodata_2B28[38];
extern void fn_12_38A0C(s32 value);
extern void MWSFSVM_Error(const char *message, ...);
extern s32 fn_12_2DA6C(u32 resource);

s32 fn_12_3A264(Fn12_3A264_Object *object) {
    s32 state;

    if (object == 0) {
        state = 0;
    } else {
        state = object->unk4;
    }

    if (state == 0) {
        fn_12_38A0C(-12);
        MWSFSVM_Error(lbl_12_rodata_2B28);
        return 0;
    }

    if (object->unk8 == 2) {
        state = fn_12_2DA6C(object->unk40);
        if (state == 4 || state == 6) {
            return 2;
        }
        if (state < 0) {
            return 4;
        }
        return 1;
    }

    return object->unk8;
}
