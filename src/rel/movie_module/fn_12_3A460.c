#include "types.h"

typedef struct Fn12_3A460_Object {
    u32 unk0;
    s32 unk4;
    u8 _pad[0x38];
    void *unk40;
} Fn12_3A460_Object;

extern char lbl_12_rodata_2BB0[45];
extern char lbl_12_rodata_2BE0[41];
extern void MWSFSVM_Error(char *message, ...);
extern int fn_12_2ACA8(void *value);

void fn_12_3A460(Fn12_3A460_Object *object) {
    s32 value;

    if (object == 0) {
        value = 0;
    } else {
        value = object->unk4;
    }

    if (value == 0) {
        MWSFSVM_Error(lbl_12_rodata_2BB0);
    } else if (fn_12_2ACA8(object->unk40) != 0) {
        MWSFSVM_Error(lbl_12_rodata_2BE0);
    }
}
