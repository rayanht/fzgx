#include "types.h"

typedef struct MovieSub {
    u8 pad_00[0x14];
    s32 unk_14;
    void *unk_18;
} MovieSub;

typedef struct MovieModule {
    u8 pad_00[0x78];
    s32 unk_78;
    u8 pad_7c[0x58];
    u8 unk_d4[1];
} MovieModule;

void *fn_12_23F00(MovieModule *self) {
    void *base = (u8 *)self + 0xd4;

    if (self->unk_78 == 0) {
        return (void *)-1;
    }
    if (((MovieSub *)base)->unk_14 != 0) {
        return ((MovieSub *)base)->unk_18;
    }
    return (void *)-1;
}
