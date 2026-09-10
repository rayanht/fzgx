#include "types.h"

typedef struct Fn12_3A598_Object {
    u32 unk0;
    u32 unk4;
    u8 _pad[0x38];
    u32 unk40;
} Fn12_3A598_Object;

extern char lbl_12_rodata_2C94[47];
extern void MWSFSVM_Error(const char *message, ...);
extern void fn_12_2D888(u32 value, u32 arg, u32 flag);

#pragma opt_propagation off
void fn_12_3A598(Fn12_3A598_Object *object, s32 value) {
    int status;
    u32 resource;

    if (object == 0) {
        status = 0;
    } else {
        status = object->unk4;
    }
    if (status == 0) {
        MWSFSVM_Error(lbl_12_rodata_2C94);
    } else {
        resource = object->unk40;
        fn_12_2D888(resource, 4, value != 1);
    }
}
#pragma opt_propagation reset

