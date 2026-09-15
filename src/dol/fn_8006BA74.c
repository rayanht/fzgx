#include "types.h"

typedef struct Fn8006BA74Base {
    u8 pad_0[0xf4];
    void *items[64];
} Fn8006BA74Base;

typedef struct Fn8006BA74Record {
    u8 pad_0[0x24];
    void *owner;
} Fn8006BA74Record;

extern u32 fn_8006BC84(void *arg0);
extern void fn_8006BCF8(void *arg0);
extern s32 fn_8006BE0C(void *arg0, u8 *arg1);

s32 fn_8006BA74(Fn8006BA74Base *arg0, u32 *out, u8 *status) {
    u32 value;
    s32 result;
    s32 state;
    u32 index;
    Fn8006BA74Record *record;

    result = 0;
    *out = fn_8006BC84(arg0);
    value = *out;
    if (value == 0xFFFFFFFF) {
        result = -5;
    } else {
        index = value & 0x3F;
        state = *status;
        record = (Fn8006BA74Record *)((u8 *)arg0 + (index << 6) + 0x1F4);
        switch (state) {
case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: {

            fn_8006BCF8(record);
            record->owner = arg0;
            fn_8006BE0C(record, status);
        
} break;
default: {

            *out = 0xFFFFFFFF;
            result = -2;
        
} break;
}
        if (record != 0) {
            arg0->items[index] = record;
        }
    }
    return result;
}
