#include "types.h"

typedef struct MovieContext {
    u8 unk_000[0x1d8];
    u32 unk_1d8;
} MovieContext;

typedef struct MovieDimensions {
    u8 unk_00[0x0c];
    s16 width;
    s16 height;
} MovieDimensions;

typedef struct DivResult {
    s32 quot;
    s32 rem;
} DivResult;

extern DivResult fn_8007E914(s32 value, s32 context);

void fn_12_11188(MovieContext *movie, u32 value, u32 *out, const MovieDimensions *dimensions) {
    DivResult d = fn_8007E914(value, movie->unk_1d8);
    s32 width = dimensions->width;
    s32 height = dimensions->height;

    out[0] = (d.quot << 3) * width + (d.rem << 3);
    out[1] = (d.quot << 4) * height + (d.rem << 4);
}
