#include "types.h"

typedef struct Fn12_3A82C_Object {
    u8 _pad0[4];
    s32 value;
    u8 _pad1[0x38];
    void *target;
} Fn12_3A82C_Object;

extern char lbl_12_rodata_2CF4[45];
extern void MWSFSVM_Error(char *message, ...);
extern void fn_12_2D888(void *target, s32 value, void *argument);

void fn_12_3A82C(Fn12_3A82C_Object *object, void *argument) {
    s32 value;

    if (object == 0) {
        value = 0;
    } else {
        value = object->value;
    }
    if (value == 0) {
        MWSFSVM_Error(lbl_12_rodata_2CF4);
    } else {
        fn_12_2D888(object->target, 6, argument);
    }
}
