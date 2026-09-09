#include "types.h"

typedef struct Fn12_3A400_Object {
    u32 _pad0;
    u32 value;
    u8 _pad8[0x38];
    void *data;
} Fn12_3A400_Object;

typedef struct Fn12_3A400_Result {
    u8 _pad0[0x28];
    s32 value;
    u8 _pad2c[0x10];
} Fn12_3A400_Result;

extern char lbl_12_rodata_2B80[48];
extern void MWSFSVM_Error(char *message, ...);
extern void fn_12_2D664(void *data, Fn12_3A400_Result *result);

s32 fn_12_3A400(Fn12_3A400_Object *object) {
    Fn12_3A400_Result result;
    s32 value;

    if (object == 0) {
        value = 0;
    } else {
        value = object->value;
    }
    if (value == 0) {
        MWSFSVM_Error(lbl_12_rodata_2B80);
        return -1;
    }
    fn_12_2D664(object->data, &result);
    return result.value;
}
