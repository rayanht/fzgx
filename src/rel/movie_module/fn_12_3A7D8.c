#include "types.h"

typedef struct Fn12_3A7D8_Object {
    u32 _pad0;
    s32 value;
    u8 _pad8[0x38];
    void *result;
} Fn12_3A7D8_Object;

extern u8 lbl_12_rodata_2718[304];
extern void MWSFSVM_Error(const char *, ...);

void *fn_12_3A7D8(Fn12_3A7D8_Object *object) {
    s32 value;

    if (object == 0) {
        value = 0;
    } else {
        value = object->value;
    }
    if (value == 0) {
        MWSFSVM_Error((const char *)&lbl_12_rodata_2718);
        return 0;
    }
    return object->result;
}
