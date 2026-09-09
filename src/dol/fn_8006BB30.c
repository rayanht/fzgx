#include "types.h"

typedef struct Fn8006BB30Data {
    u8 _pad[0xf4];
    void *items[64];
} Fn8006BB30Data;

extern s32 fn_8006BE0C(void *value, u32 arg);

s32 fn_8006BB30(Fn8006BB30Data *data, u32 index, u32 arg) {
    s32 result;

    result = -2;
    if (data->items[index & 0x3f] != 0) {
        result = fn_8006BE0C(data->items[index & 0x3f], arg);
    }
    return result;
}
