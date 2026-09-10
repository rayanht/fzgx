#include "types.h"

typedef struct Fn12_39CF8_Object {
    u8 _pad0[4];
    s32 unk4;
    u8 _pad8[0x38];
    u32 unk40;
} Fn12_39CF8_Object;

extern char lbl_12_rodata_28E0[52];
extern char lbl_12_rodata_2718[304];
extern void MWSFSVM_Error(const char *message, ...);
extern s32 fn_12_2D888(u32 resource, s32 arg, s32 flag);

s32 fn_12_39CF8(Fn12_39CF8_Object *object, s32 mode) {
    s32 state;
    u32 resource;

    if (object == 0) {
        state = 0;
    } else {
        state = object->unk4;
    }

    if (state == 0) {
        MWSFSVM_Error(lbl_12_rodata_28E0);
        return;
    }

    if (object == 0) {
        state = 0;
    } else {
        state = object->unk4;
    }

    if (state == 0) {
        MWSFSVM_Error(lbl_12_rodata_2718);
        resource = 0;
    } else {
        resource = object->unk40;
    }

    return fn_12_2D888(resource, 7, mode != 1);
}
