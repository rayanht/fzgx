#include "types.h"

extern const f32 lbl_12_rodata_4E8;
extern void SJ_SearchTag(u32 *, const char *, const char *, u32 *);

typedef struct MovieData {
    u8 unk0[8];
    u32 state;
    u32 source;
    u32 size;
    u8 unk14[4];
    u32 width;
    u32 unk1c;
    u32 unk20;
    u8 unk24[4];
    u32 height;
    u32 unk2c;
    u32 unk30;
} MovieData;

void fn_12_47C8(MovieData *movie, u32 source, u32 size) {
    const char *base = (const char *)&lbl_12_rodata_4E8;
    u32 output[2];
    u32 input[2];

    movie->state = 1;
    movie->source = source;
    movie->size = size;
    if (movie->source == 0) {
        movie->width = 1;
        movie->unk1c = 0;
        movie->unk20 = 0;
        movie->height = 1;
        movie->unk2c = 0;
        movie->unk30 = 0;
    } else {
        input[0] = movie->source;
        input[1] = movie->size;
        SJ_SearchTag(input, base + 0x98, base + 0x60, output);
        movie->width = 1;
        movie->unk1c = output[0];
        movie->unk20 = output[1];
        SJ_SearchTag(input, base + 0xa0, base + 0x60, output);
        movie->height = 1;
        movie->unk2c = output[0];
        movie->unk30 = output[1];
    }
}
