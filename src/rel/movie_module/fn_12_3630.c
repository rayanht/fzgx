#include "types.h"

typedef struct MovieData {
    u8 _pad0[0x3c];
    f32 value0;
    f32 value1;
} MovieData;

extern const f32 lbl_12_rodata_4E8;

s32 fn_12_3630(const MovieData *movie) {
    f32 value0 = movie->value0;
    f32 value1 = movie->value1;
    s32 result = 1;

    if (lbl_12_rodata_4E8 == value0 && lbl_12_rodata_4E8 == value1) {
        result = 0;
    }
    return result;
}
