#include "types.h"

typedef struct MovieModuleData {
    u8 pad_0[0x0c];
    s32 field_0c;
    u8 pad_10[0x118];
    u64 field_128;
    u64 field_130;
} MovieModuleData;

typedef struct Fn12_30930_Arg {
    u64 field_0;
    u32 field_8;
    u32 field_c;
} Fn12_30930_Arg;

extern u64 __div2i(u32, u32, u32, u32);

void fn_12_30930(MovieModuleData *data, Fn12_30930_Arg *arg) {
    if (data->field_0c == 0) {
        data->field_128 += (u64)((s64)(data->field_130 * arg->field_0) /
            (s64)(((u64)arg->field_8 << 32) | arg->field_c));
    }
}
