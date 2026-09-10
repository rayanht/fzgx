#include "types.h"

typedef struct MovieModule {
    u8 unk0[4];
    s32 field4;
    u8 unk8[0x18];
    u32 field20;
} MovieModule;

typedef struct MovieArg {
    s32 value;
} MovieArg;

extern u8 lbl_12_rodata_60[];

extern u32 fn_12_3074(void *arg0, const void *arg1);
extern s32 fn_12_3630(u32 value);
extern void fn_12_309C(void *arg0, void *arg1, const void *arg2);
extern void fn_12_A5C(void *arg0, void *arg1, s32 arg2, void *arg3);
extern void fn_12_8E4(void *arg0, void *arg1, s32 arg2, void *arg3);

void fn_12_C60(MovieModule *module, MovieArg *arg1, s32 arg2, void *arg3) {
    u8 *table = (u8 *)&lbl_12_rodata_60;

    if (module->field4 == 0) {
        module->field4 = fn_12_3074(arg1, table + 0x60);
    }

    if (fn_12_3630(module->field20) != 1) {
        fn_12_309C(module, arg1, table + 0x164);
    } else {
        switch (arg1->value) {
        case 3:
            fn_12_A5C(module, arg1, arg2, arg3);
            break;
        case 2:
            fn_12_8E4(module, arg1, arg2, arg3);
            break;
        case 1:
        default:
            fn_12_309C(module, arg1, table + 0x194);
            break;
        }
    }
}
