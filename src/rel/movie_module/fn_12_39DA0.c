#include "types.h"

typedef struct Fn12_39DA0_Object {
    u32 unk0;
    s32 unk4;
    u8 _pad[0x38];
    void *unk40;
} Fn12_39DA0_Object;

typedef struct Fn12_39DA0_Result {
    u8 _pad[0x10];
    u32 value;
    u8 _tail[0x2c];
} Fn12_39DA0_Result;

extern char lbl_12_rodata_287C[52];
extern void MWSFSVM_Error(const char *format, ...);
extern void fn_12_2D58C(void *object, Fn12_39DA0_Result *result);

u32 fn_12_39DA0(Fn12_39DA0_Object *object) {
    s32 valid;
    Fn12_39DA0_Result result;

    if (object == 0) {
        valid = 0;
    } else {
        valid = object->unk4;
    }
    if (valid == 0) {
        MWSFSVM_Error(lbl_12_rodata_287C);
        return 0;
    }
    fn_12_2D58C(object->unk40, &result);
    return result.value;
}
