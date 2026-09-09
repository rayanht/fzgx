#include "types.h"

typedef struct Fn12_39EF8_Object {
    u32 unk0;
    s32 unk4;
} Fn12_39EF8_Object;

extern char lbl_12_rodata_2998[44];
extern void MWSFSVM_Error(char *message, ...);
extern void fn_12_34198(void);

void fn_12_39EF8(Fn12_39EF8_Object *object) {
    s32 value;

    if (object == 0) {
        value = 0;
    } else {
        value = object->unk4;
    }

    if (value == 0) {
        MWSFSVM_Error(lbl_12_rodata_2998);
    } else {
        fn_12_34198();
    }
}
