#include "types.h"

typedef struct Fn8006B3F0Data {
    u8 pad_0[4];
    struct {
        u8 enabled:1;
        u8 active:1;
        u8 rest:6;
    } flags;
    u8 pad_5[3];
    s32 status;
    u8 pad_c[0x44];
    u8 data_50[1];
} Fn8006B3F0Data;

extern void fn_8006BC50(void *data);

s32 fn_8006B3F0(Fn8006B3F0Data *data) {
    if (data == 0 || (u32)data + 0x10000 == 0xffff) {
        return -2;
    }
    if (data->flags.enabled == 0) {
        return -2;
    }
    data->flags.enabled = 0;
    data->flags.active = 0;
    fn_8006BC50(data->data_50);
    data->status = -1;
    return 0;
}
