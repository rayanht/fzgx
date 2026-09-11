#include "types.h"

struct MovieModule {
    u32 pad_0;
    void *field_4;
    char pad_8[0x38];
    u32 field_40;
};

extern void *lbl_12_bss_7C64[137];
extern s32 fn_12_24A88(int arg0, u32 arg1);
extern void *fn_12_2BAE0(struct MovieModule *module, s32 arg);

void *fn_12_2BCF4(struct MovieModule *module, s32 arg) {
    int index;
    int i;
    void **table;
    void **p;
    int valid;
    void *movie;

    table = &lbl_12_bss_7C64[129];
    if (module->field_4 == 0) {
        valid = -1;
    } else if (module->field_40 < 0x29f8) {
        valid = -1;
    } else {
        valid = 0;
    }
    if (valid != 0) {
        fn_12_24A88(0, 0xff000203);
        return 0;
    }
    p = table;
    for (i = 0; i < 8; i++) {
        if (*p == 0) {
            index = i;
            goto found; /* search result, common exit */
        }
        p++;
    }
    index = -1;
found:
    if (index == -1) {
        return 0;
    }
    movie = fn_12_2BAE0(module, arg);
    table[index] = movie;
    return movie;
}
