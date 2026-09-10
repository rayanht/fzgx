#include "types.h"

extern void __begin_critical_region(s32 region);
extern u32 lbl_801A6DE0[2];
extern void __end_critical_region(s32 region);

typedef struct Fn8007FE70Object {
    u8 pad0[4];
    u16 flags;
    u8 pad6[2];
    u8 state;
    u8 pad9[1];
    u8 active;
    u8 padb[0xd];
    void *next;
    u8 *field1c;
    u8 pad20[4];
    u8 *field24;
    u8 pad28[0xc];
    u8 *base;
} Fn8007FE70Object;

void *fn_8007FE70(Fn8007FE70Object *obj) {
    u8 kind;
    u32 lab_v;

    __begin_critical_region(2);
    lab_v = obj->flags;
    if ((((lab_v >> 6) & 7) != 1 && ((lab_v >> 6) & 7) != 2) ||
        obj->active != 0) {
        obj = (Fn8007FE70Object *)-1;
        lbl_801A6DE0[0] = 0x28;
    } else {
        kind = (obj->state >> 5) & 7;
        if (kind == 0) {
            obj = (Fn8007FE70Object *)obj->next;
        } else {
            obj = (Fn8007FE70Object *)(obj->base + (obj->field24 - obj->field1c));
            if (kind >= 3) {
                obj = (Fn8007FE70Object *)((u8 *)obj - (kind - 2));
            }
        }
    }
    __end_critical_region(2);
    return obj;
}
