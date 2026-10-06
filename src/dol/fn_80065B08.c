#include "types.h"

typedef struct Fn80065B08_Pool {
    u32 addr[16];
    u32 size[17];
    u8 pad_84[0x10];
    u32 length;
    u32 free_start;
    u32 free_size;
    u8 pad_A0[0x8];
} Fn80065B08_Pool;

typedef struct Fn80065B08_Synth {
    u8 pad_0[0x100];
    Fn80065B08_Pool pools[2];
    u8 pad_250[0x20F];
    u8 ready;
} Fn80065B08_Synth;

extern Fn80065B08_Synth *lbl_801A6C80;

s32 fn_80065B08(u32 *sizes) {
    s32 i;
    u32 end;
    u32 total;
    s32 result;

    result = 0;
    total = 0;
    for (i = 1; i < 16; i++) {
        end = lbl_801A6C80->pools[0].addr[i] + *sizes;
        total += *sizes;
        lbl_801A6C80->pools[0].size[i] = *sizes;
        if (end <= lbl_801A6C80->pools[0].addr[1] + lbl_801A6C80->pools[0].length) {
            lbl_801A6C80->pools[0].addr[i + 1] = end;
        } else {
            result = -1;
            break;
        }
        sizes++;
    }
    if (result == 0) {
        total += *sizes;
        lbl_801A6C80->pools[0].size[16] = *sizes;
        lbl_801A6C80->pools[0].free_start = lbl_801A6C80->pools[0].addr[1] + total;
        lbl_801A6C80->pools[0].free_size = lbl_801A6C80->pools[0].length - total;
        sizes++;
        for (i = 1; i < 16; i++) {
            end = lbl_801A6C80->pools[1].addr[i] + *sizes;
            lbl_801A6C80->pools[1].size[i] = *sizes;
            if (end <= lbl_801A6C80->pools[1].addr[1] + lbl_801A6C80->pools[1].length) {
                lbl_801A6C80->pools[1].addr[i + 1] = end;
            } else {
                result = -1;
                break;
            }
            sizes++;
        }
        if (result == 0) {
            lbl_801A6C80->pools[1].size[16] = *sizes;
        }
    }
    if (result == 0) {
        lbl_801A6C80->ready = 1;
    }
    return result;
}
