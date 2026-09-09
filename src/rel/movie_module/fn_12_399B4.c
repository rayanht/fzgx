#include "types.h"

typedef struct Fn12_399B4_Object {
    u8 _pad[0x40];
    u32 value;
} Fn12_399B4_Object;

extern s32 fn_12_2B138(u32 value);
extern char lbl_12_rodata_26CC[46];
extern void MWSFSVM_Error(const char *format, ...);

s32 fn_12_399B4(Fn12_399B4_Object *object) {
    s32 result = fn_12_2B138(object->value);

    switch (result) {
    case 1:
        return 1;
    case 0:
        return 0;
    default:
        MWSFSVM_Error(lbl_12_rodata_26CC, result);
        return 0;
    }
}
