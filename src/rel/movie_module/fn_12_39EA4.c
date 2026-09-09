#include "types.h"

typedef struct Fn12_39EA4_Object {
    u32 unk0;
    u32 unk4;
} Fn12_39EA4_Object;

extern char lbl_12_rodata_296C[44];
extern void MWSFSVM_Error(char *, ...);
extern s32 fn_12_34174(void);

s32 fn_12_39EA4(Fn12_39EA4_Object *object) {
    s32 value;

    if (object == 0) {
        value = 0;
    } else {
        value = object->unk4;
    }

    if (value == 0) {
        MWSFSVM_Error(lbl_12_rodata_296C);
        return 0;
    } else {
        return fn_12_34174();
    }
}
