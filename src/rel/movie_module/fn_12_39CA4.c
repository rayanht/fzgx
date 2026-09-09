#include "types.h"

typedef struct MovieObject {
    u8 pad0[4];
    s32 value;
    u8 pad8[0x124];
    u32 result;
} MovieObject;

extern char lbl_12_rodata_28B0[46];
extern void MWSFSVM_Error(const char *message, ...);

s32 fn_12_39CA4(MovieObject *object) {
    s32 value;

    if (object == 0) {
        value = 0;
    } else {
        value = object->value;
    }

    if (value == 0) {
        MWSFSVM_Error(lbl_12_rodata_28B0);
        return 0;
    }

    return object->result;
}
