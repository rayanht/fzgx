#include "types.h"

typedef struct Fn8006BBDCData {
    u8 _pad[0xf4];
    void *items[64];
} Fn8006BBDCData;

extern s32 fn_8006C17C(void *value);

s32 fn_8006BBDC(Fn8006BBDCData *data, u32 index) {
    u32 result;

    result = -2;
    if (data->items[index & 0x3f] != 0) {
        result = fn_8006C17C(data->items[index & 0x3f]);
    }
    return result;
}
