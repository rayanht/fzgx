#include "types.h"

typedef struct Fn12_39A18_Object {
    u8 unk0[0x40];
    u32 unk40;
} Fn12_39A18_Object;

extern s32 fn_12_2B634(u32 value);
extern void fn_12_38A0C(s32 value);
extern const char lbl_12_rodata_26FC[27];
extern void MWSFSVM_Error(const char *format, ...);

s32 fn_12_39A18(Fn12_39A18_Object *object) {
    if (fn_12_2B634(object->unk40) != 0) {
        fn_12_38A0C(-0x133);
        MWSFSVM_Error(lbl_12_rodata_26FC);
        return -0x133;
    }
    return 0;
}
