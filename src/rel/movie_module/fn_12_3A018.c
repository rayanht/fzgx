#include "types.h"

typedef struct Fn12_3A018_Object {
    u32 unk0;
    s32 unk4;
    u8 _pad[0x38];
    u32 unk40;
} Fn12_3A018_Object;

extern char lbl_12_rodata_2A14[50];
extern void MWSFSVM_Error(char *message, ...);
extern void fn_12_2D58C(u32 value, u32 *result);

u32 fn_12_3A018(Fn12_3A018_Object *object) {
    s32 value;
    u8 local[0x3c];

    if (object == 0) {
        value = 0;
    } else {
        value = object->unk4;
    }
    if (value == 0) {
        MWSFSVM_Error(lbl_12_rodata_2A14);
        return 0;
    }
    fn_12_2D58C(object->unk40, (u32 *)local);
    return *(u32 *)local;
}
