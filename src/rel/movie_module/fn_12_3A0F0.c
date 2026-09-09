#include "types.h"

typedef struct Fn12_3A0F0_Object {
    u32 unk0;
    s32 unk4;
    u8 _pad[0x38];
    u32 unk40;
} Fn12_3A0F0_Object;

extern char lbl_12_rodata_2A98[47];
extern void MWSFSVM_Error(const char *message, ...);
extern void fn_12_2D74C(u32 value, u32 type, s32 *result);
extern char lbl_12_rodata_2AC8[45];

s32 fn_12_3A0F0(Fn12_3A0F0_Object *object) {
    s32 value;
    s32 result;

    if (object == 0) {
        value = 0;
    } else {
        value = object->unk4;
    }
    if (value == 0) {
        MWSFSVM_Error(lbl_12_rodata_2A98);
        return -1;
    }

    fn_12_2D74C(object->unk40, 15, &result);
    switch (result) {
    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        return 2;
    default:
        MWSFSVM_Error(lbl_12_rodata_2AC8);
        return -1;
    }
}
