#include "types.h"

typedef struct MovieModule MovieModule;

struct MovieModule {
    u8 unk_000[0x110];
    u8 unk_110[0x8];
    u32 unk_118;
    u8 unk_11c[0x4];
    u32 unk_120;
    u32 unk_124;
    u8 unk_128[0x4];
    u32 unk_12c;
    u8 unk_130[0x4];
    u32 unk_134;
    u8 unk_138[0x4];
    u32 unk_13c;
    u8 unk_140[0x4];
    u32 unk_144;
    u8 unk_148[0x4];
    u32 unk_14c;
    u8 unk_150[0x114];
    u32 unk_264;
    u32 unk_268;
    u32 unk_26c;
    u8 unk_270[0x2];
    s16 unk_272;
    u8 unk_274[0x4c];
    u8 unk_2c0[0x54];
    u32 unk_314;
};

extern void fn_12_11F5C(MovieModule *, u32, u32 *, void *, void *);
extern void fn_12_11CE0(void *, void *, u32);

#pragma opt_dead_assignments off
void fn_12_12270(MovieModule *module) {
    u32 local[2];
    u32 lab_t1;
    u8 *base;

    base = (u8 *)module + 0x110;
    lab_t1 = module->unk_118;
    fn_12_11F5C(module, lab_t1, local, (u8 *)module + 0x234, (u8 *)module + 0x2c0);
    module->unk_124 = module->unk_264 + local[0];
    module->unk_12c = module->unk_268 + local[0];
    module->unk_134 = module->unk_26c + local[1];
    module->unk_13c = module->unk_134 + 8;
    module->unk_144 = module->unk_134 + ((s32)module->unk_272 << 3);
    module->unk_14c = module->unk_144 + 8;
    {
        u8 *p120 = (u8 *)module + 0x120;
        fn_12_11CE0(base, p120, module->unk_314);
    }
}
#pragma opt_dead_assignments reset

