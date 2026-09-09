#include "types.h"

typedef struct Fn12_39F48_Object {
    u32 unk0;
    s32 unk4;
    u8 _pad[0x38];
    u32 unk40;
} Fn12_39F48_Object;

extern char lbl_12_rodata_29C4[42];
extern void MWSFSVM_Error(const char *fmt, ...);
extern s32 fn_12_2E8C8(u32 value, u32 *result, u32 *status);
extern void fn_12_38A0C(s32 error);
extern char lbl_12_rodata_29F0[35];

void fn_12_39F48(Fn12_39F48_Object *object, s32 *result, s32 *status) {
    s32 value;

    if (object == 0) {
        value = 0;
    } else {
        value = object->unk4;
    }
    if (value == 0) {
        MWSFSVM_Error(lbl_12_rodata_29C4);
        *result = 0;
        *status = 1;
        return;
    }

    if (fn_12_2E8C8(object->unk40, (u32 *)result, (u32 *)status) != 0) {
        fn_12_38A0C(-0x135);
        MWSFSVM_Error(lbl_12_rodata_29F0);
        *result = 0;
        *status = 1;
    }
    if (*result < 0) {
        *result = 0;
        *status = 1;
    }
}
