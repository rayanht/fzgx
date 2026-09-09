#include "types.h"

typedef struct Fn12_3A1A4_Object {
    u8 _pad0[4];
    s32 unk4;
    u8 _pad8[4];
    s32 unkC;
    u8 _pad10[0x30];
    u32 unk40;
} Fn12_3A1A4_Object;

extern const char lbl_12_rodata_2AF8[47];
extern void MWSFSVM_Error(const char *message, ...);
extern void fn_12_2D888(u32 resource, s32 value, s32 mode);

void fn_12_3A1A4(Fn12_3A1A4_Object *object, s32 mode) {
    s32 state;
    u32 resource;

    if (object == 0) {
        state = 0;
    } else {
        state = object->unk4;
    }

    if (state == 0) {
        MWSFSVM_Error(lbl_12_rodata_2AF8);
        return;
    }

    resource = object->unk40;
    if (mode == 0) {
        fn_12_2D888(resource, 15, 0);
        return;
    }

    if (mode == 1) {
        fn_12_2D888(resource, 15, 1);
        return;
    }

    if (mode == 2) {
        if (object->unkC == 1) {
            fn_12_2D888(resource, 15, 2);
        } else {
            fn_12_2D888(resource, 15, 1);
        }
    }
}
