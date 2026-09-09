#include "types.h"

typedef struct Fn12_3A784_Object {
    u8 _pad0[0x4];
    s32 value;
    u8 _pad8[0x40];
    u32 result;
} Fn12_3A784_Object;

extern char lbl_12_rodata_2CC4[45];
extern void MWSFSVM_Error(char *, ...);

u32 fn_12_3A784(Fn12_3A784_Object *object) {
    s32 value;

    if (object == 0) {
        value = 0;
    } else {
        value = object->value;
    }

    if (value == 0) {
        MWSFSVM_Error(lbl_12_rodata_2CC4);
        return 0;
    }

    return object->result;
}
