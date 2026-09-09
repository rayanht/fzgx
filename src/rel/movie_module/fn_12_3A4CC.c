#include "types.h"

typedef struct Fn12_3A4CC_Object {
    u8 _pad0[0x04];
    s32 value;
    u8 _pad8[0x38];
    void *data;
} Fn12_3A4CC_Object;

typedef struct Fn12_3A4CC_Result {
    u8 _pad0[0x24];
    s32 value;
    u8 _pad28[0x20];
} Fn12_3A4CC_Result;

extern char lbl_12_rodata_2C0C[48];
extern void MWSFSVM_Error(const char *format, ...);
extern void fn_12_2D664(void *data, Fn12_3A4CC_Result *result);

s32 fn_12_3A4CC(Fn12_3A4CC_Object *object) {
    s32 value;
    Fn12_3A4CC_Result result;

    if (object == 0) {
        value = 0;
    } else {
        value = object->value;
    }

    if (value == 0) {
        MWSFSVM_Error(lbl_12_rodata_2C0C);
        return -1;
    }

    fn_12_2D664(object->data, &result);
    return result.value;
}
