#include "types.h"

typedef struct Fn12_3A300_Object {
    u8 _pad0[4];
    u32 unk4;
    u8 _pad8[0x38];
    u32 unk40;
} Fn12_3A300_Object;

extern char lbl_12_rodata_2B50[48];
extern void MWSFSVM_Error(char *message, ...);
extern void fn_12_2D888(u32 value, u32 type, u32 duration);

void fn_12_3A300(Fn12_3A300_Object *object, u32 value) {
    int state;
    u32 duration;
    u32 resource;

    if (object == 0) {
        state = 0;
    } else {
        state = object->unk4;
    }

    if (state == 0) {
        MWSFSVM_Error(lbl_12_rodata_2B50);
    } else {
        duration = value * 1000;
        if (object) {
            resource = object->unk40;
        } else {
            resource = 0;
        }
        fn_12_2D888(resource, 54, duration);
    }
}
