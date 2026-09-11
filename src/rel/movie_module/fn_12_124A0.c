#include "types.h"

typedef struct MovieModule MovieModule;
typedef void (*MovieCallback)(MovieModule *, s32, void *, void *);

struct MovieModule {
    u8 unk_000[0x40];
    void *unk_040;
    u8 unk_044[0x24c];
    MovieCallback callback;
    u8 unk_294[0x14];
    u8 unk_2a8[0x60];
    s32 unk_308;
    u8 unk_30c[0x34];
    u8 unk_340[0x28];
};

typedef struct MovieData MovieData;
struct MovieData {
    s32 value_0;
    s32 value_4;
    s32 value_8;
    s16 value_c;
    s16 value_e;
};

typedef struct MovieOutput MovieOutput;
struct MovieOutput {
    u8 unk_000[4];
    u32 value_4;
    u8 unk_008[4];
    u32 value_c;
    u8 unk_010[4];
    u32 value_14;
    u8 unk_018[4];
    u32 value_1c;
    u8 unk_020[4];
    u32 value_24;
    u8 unk_028[4];
    u32 value_2c;
};

extern void fn_12_12324(void *, void *, void *);

void fn_12_124A0(MovieModule *module) {
    u32 local[2];
    MovieOutput *output = (MovieOutput *)((u8 *)module + 0x120);
    MovieData *data = (MovieData *)((u8 *)module + 0x264);
    s32 offset;

    module->callback(module, module->unk_308, local, data);
    offset = data->value_e;
    offset = offset << 3;
    output->value_4 = data->value_0 + local[0];
    output->value_c = data->value_4 + local[0];
    output->value_14 = data->value_8 + local[1];
    output->value_1c = output->value_14 + 8;
    output->value_24 = output->value_14 + offset;
    output->value_2c = output->value_24 + 8;
    fn_12_12324((u8 *)module + 0x340, output, module->unk_040);
}
