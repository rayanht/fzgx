#include "types.h"

typedef struct Object {
    u32 flags;
    u16 index;
    u16 pad06;
    u32 value;
} Object;

typedef struct Entry {
    u32 pad00;
    u32 data;
} Entry;

extern void fn_800718BC(Object *, void *, Entry *);

void fn_80071C04(Object *obj, Entry *entry) {
    if (obj->flags & 0x00200000) {
        obj->value = 0;
    } else if (entry == 0) {
        obj->value = 0;
    } else {
        fn_800718BC(obj, (u8 *)entry->data + obj->index * 16, entry);
    }
}
