#include "types.h"

typedef struct Fn12_3A600_Object {
    u8 _pad0[0x04];
    s32 value;
    u8 _pad8[0x38];
    void *data;
} Fn12_3A600_Object;

typedef struct Fn12_3A600_Result {
    u8 _pad0[0x04];
    s32 start;
    u8 _pad8[0x08];
    s32 end;
    u8 _pad14[0x2c];
} Fn12_3A600_Result;

extern char lbl_12_rodata_2848[49];
extern void MWSFSVM_Error(const char *format, ...);
extern char lbl_12_rodata_2718[304];
extern void fn_12_2D58C(void *data, Fn12_3A600_Result *result);

s32 fn_12_3A600(Fn12_3A600_Object *object) {
    s32 value;
    Fn12_3A600_Result result;
    void *data;

    if (object == 0) {
        value = 0;
    } else {
        value = object->value;
    }

    if (value == 0) {
        MWSFSVM_Error(lbl_12_rodata_2848);
        return 0;
    }

    if (object == 0) {
        value = 0;
    } else {
        value = object->value;
    }

    if (value == 0) {
        MWSFSVM_Error(lbl_12_rodata_2718);
        data = 0;
    } else {
        data = object->data;
    }

    fn_12_2D58C(data, &result);
    return result.start - result.end;
}
