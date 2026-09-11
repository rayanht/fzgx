#include "types.h"

typedef struct MovieModule {
    u8 _pad110[0x110];
    u32 field_110;
    u8 _pad114[4];
    u32 field_118;
    u8 _pad11c[0x118];
    u32 field_234;
    u8 _pad238[0x1c];
    u32 field_254;
    u8 _pad258[0x68];
    u32 field_2c0;
    u8 _pad2c4[0x50];
    u32 field_314;
} MovieModule;

extern void fn_12_847C(MovieModule *, u32, u32 *, u32 *, u32 *);
extern void fn_12_8344(u32, u32 *, u32);

#pragma opt_propagation off
void fn_12_879C(MovieModule *module) {
    u32 *field110 = &module->field_110;
    u32 value;

    fn_12_847C(module, module->field_118, &value, &module->field_234, &module->field_2c0);
    {
        u32 old_value = module->field_254;
        module->field_254 = old_value + 0x180;
        fn_12_8344(old_value, field110, module->field_314);
    }
}
#pragma opt_propagation reset
