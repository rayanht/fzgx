#include "types.h"

typedef struct MovieHeader MovieHeader;
typedef struct MovieModule MovieModule;

struct MovieHeader {
    u8 unk_00[0xc];
    void *unk_0c;
};

struct MovieModule {
    u8 unk_000[0x110];
    u32 unk_110;
    u32 unk_114;
    void *unk_118;
    void *unk_11c;
    u32 unk_120;
    u32 unk_124;
    u32 unk_128;
    u32 unk_12c;
    u32 unk_130;
    u32 unk_134;
    u32 unk_138;
    u32 unk_13c;
    u32 unk_140;
    u32 unk_144;
    u32 unk_148;
    u32 unk_14c;
    u8 unk_150[0xe4];
    u32 unk_234;
    u8 unk_238[0x2c];
    u32 unk_264;
    u32 unk_268;
    u32 unk_26c;
    u8 unk_270[2];
    s16 unk_272;
    u8 unk_274[0x4c];
    u32 unk_2c0;
    u8 unk_2c4[0x20];
    u32 unk_2e4;
    u8 unk_2e8[0x2c];
    void *unk_314;
};

extern void fn_12_11F5C(void *, void *, void *, void *, void *);
extern void fn_12_118E8(void *, void *, void *);

#pragma opt_propagation off
void fn_12_120E4(MovieModule *module) {
    u32 local[2];
    void *data = (u8 *)module + 0x234;
    MovieHeader *header = (MovieHeader *)((u8 *)module + 0x110);
    void *end = (u8 *)module + 0x2c0;

    fn_12_11F5C(module, module->unk_118, local, data, end);
    fn_12_11F5C(module, header->unk_0c, local,
                (u8 *)data + 0x10, (u8 *)module + 0x2e4);

    module->unk_124 = module->unk_264 + local[0];
    module->unk_12c = module->unk_268 + local[0];
    module->unk_134 = module->unk_26c + local[1];
    module->unk_13c = module->unk_134 + 8;
    module->unk_144 = module->unk_134 + ((s32)module->unk_272 << 3);
    module->unk_14c = module->unk_144 + 8;

    {
        u8 *p120 = (u8 *)module + 0x120;
        fn_12_118E8(header, p120, module->unk_314);
    }
}
#pragma opt_propagation reset
