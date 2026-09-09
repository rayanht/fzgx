#include "types.h"

typedef struct Fn12_3A52C_Object {
    u8 _pad0[0x04];
    u32 value;
    u8 _pad8[0x38];
    void *movie;
} Fn12_3A52C_Object;

extern char lbl_12_rodata_2C3C[45];
extern void MWSFSVM_Error(const char *format, ...);
extern int fn_12_2AD10(void *movie);
extern char lbl_12_rodata_2C6C[40];

void fn_12_3A52C(Fn12_3A52C_Object *object) {
    int value;

    if (object == 0) {
        value = 0;
    } else {
        value = object->value;
    }

    if (value == 0) {
        MWSFSVM_Error(lbl_12_rodata_2C3C);
    } else if (fn_12_2AD10(object->movie) != 0) {
        MWSFSVM_Error(lbl_12_rodata_2C6C);
    }
}
