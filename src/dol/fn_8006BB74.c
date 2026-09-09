#include "types.h"

typedef struct Fn8006BB74Data {
    u8 _pad[0xf4];
    void *items[64];
} Fn8006BB74Data;

s32 fn_8006BB74(Fn8006BB74Data *data, u32 index) {
    s32 result;

    result = -2;
    if (data->items[index & 0x3f] != 0) {
        data->items[index & 0x3f] = 0;
        result = 0;
    }
    return result;
}
