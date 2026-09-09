#include "types.h"

typedef struct Fn12_3A078_Object {
    u32 unk0;
    s32 unk4;
    u8 _pad[0x38];
    u32 unk40;
} Fn12_3A078_Object;

extern char lbl_12_rodata_2A48[49];
extern void MWSFSVM_Error(const char *fmt, ...);
extern s32 fn_12_2A55C(u32 value, u32 *result);
extern char lbl_12_rodata_2A7C[28];

u32 fn_12_3A078(Fn12_3A078_Object *object) {
    s32 value;
    u32 result;

    if (object == 0) {
        value = 0;
    } else {
        value = object->unk4;
    }
    if (value == 0) {
        MWSFSVM_Error(lbl_12_rodata_2A48);
        return 0;
    }

    if (fn_12_2A55C(object->unk40, &result) != 0) {
        MWSFSVM_Error(lbl_12_rodata_2A7C);
    }
    return result;
}
