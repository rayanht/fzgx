#include "types.h"

typedef struct Fn12_39E00_Object {
    u32 unk0;
    s32 unk4;
} Fn12_39E00_Object;

extern char lbl_12_rodata_2914[44];
extern void fn_12_34B88(char *message, ...);
extern s32 fn_12_3412C(Fn12_39E00_Object *object);

s32 fn_12_39E00(Fn12_39E00_Object *object) {
    s32 value;

    if (object == 0) {
        value = 0;
    } else {
        value = object->unk4;
    }

    if (value == 0) {
        fn_12_34B88(lbl_12_rodata_2914);
        return 0;
    } else {
        return fn_12_3412C(object);
    }
}
