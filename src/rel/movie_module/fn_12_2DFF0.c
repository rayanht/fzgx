#include "types.h"

typedef struct MovieModule {
    u8 pad_0[0x920];
    s32 movie_index;
    u8 pad_924[0xF24 - 0x924];
    s32 total_a;
    u8 pad_F28[0xF48 - 0xF28];
    s32 total_b;
    u8 pad_F4C[0xF58 - 0xF4C];
    s32 total_c;
    s32 movie_id;
} MovieModule;

extern u32 lbl_12_rodata_E10[9];
extern u32 lbl_12_bss_7C64[137];
extern s32 UTY_MulDiv(s32 arg0, s32 arg1, s32 arg2);

void fn_12_2DFF0(MovieModule *module, s32 mode) {
    s32 value;
    s32 duration;
    s32 result;

    switch (mode) {
    case 0:
    case 1:
        break;
    case 2:
        if (module->movie_index == 0) {
            value = 0;
            duration = 0x7512;
        } else {
            value = 0x3e8;
            duration = lbl_12_rodata_E10[module->movie_index];
        }

        result = UTY_MulDiv(lbl_12_bss_7C64[0x6e], value, duration);
        module->total_a += result;
        module->total_b += result;
        result = UTY_MulDiv(module->movie_id, value, duration);
        module->total_c += result;
        break;
    }
}
