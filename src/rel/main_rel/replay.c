#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/replay.h"

extern u32 OSGetTick(void);

/* fzgx:begin fn_1_F2CD8 */
void fn_1_F2CD8(u8 *value, u8 **cursor, u32 index) {
    s32 target;
    Obj_1_bss_7EFD8_At40 *entries_end;
    u8 *entry;

    // Move backward through replay entries until the requested flag or boundary is found.
    target = (index | 4) & 0xff;
    entries_end = lbl_1_bss_7EFD8.unk_40 + 1;
    *cursor = value;

    while (*cursor >= (u8 *)entries_end) {
        entry = *cursor;
        if ((entry[0] & 7) == target) {
            break;
        }
        *cursor -= 7;
    }

    if (*cursor < (u8 *)entries_end) {
        *cursor = value;
    }
}
/* fzgx:end fn_1_F2CD8 */

/* fzgx:begin fn_1_F2D30 */
u8 fn_1_F2D30(u8 *value, u8 **cursor, u32 index) {
    u8 target;
    u32 step;
    Obj_1_bss_7EFD8_At40 *entries_end;
    u8 raw;
    u8 flags;

    target = (index | 4) & 0xff;
    entries_end = lbl_1_bss_7EFD8.unk_40 + 1;

    if (lbl_1_bss_7EFD8.unk_1A != 0) {
        lbl_1_bss_7EFD8.unk_1A = 0;
        step = 0;
    } else {
        step = 1;
    }
    *cursor = value + step * 7;

    while (*cursor < (u8 *)entries_end + lbl_1_bss_7EFD8.unk_14 * 7) {
        raw = (*cursor)[0];
        flags = raw & 7;
        if ((raw & 4) == 0 || flags == target) {
            break;
        }
        *cursor += 7;
    }

    return *cursor != (u8 *)entries_end + lbl_1_bss_7EFD8.unk_14 * 7;
}
/* fzgx:end fn_1_F2D30 */

/* fzgx:begin fn_1_F2EB8 noprologue */
#include "types.h"

struct fn_1_F2EB8_lbl_1_bss_7EFD4 {
    s8 unk_0;
};

extern struct fn_1_F2EB8_lbl_1_bss_7EFD4 lbl_1_bss_7EFD4;

void fn_1_F2EB8(void) {
    u8 v0;
    v0 = lbl_1_bss_7EFD4.unk_0;
    if ((v0 & 0x1) == 0) { return; }
    lbl_1_bss_7EFD4.unk_0 = (v0 & -41);
}
/* fzgx:end fn_1_F2EB8 */

/* fzgx:begin fn_1_F2EDC noprologue */
#include "types.h"

struct fn_1_F2EDC_lbl_1_bss_7EFD4 {
    s8 unk_0;
};

extern struct fn_1_F2EDC_lbl_1_bss_7EFD4 lbl_1_bss_7EFD4;

void fn_1_F2EDC(void) {
    u8 v0;
    v0 = lbl_1_bss_7EFD4.unk_0;
    if ((v0 & 0x1) == 0) { return; }
    lbl_1_bss_7EFD4.unk_0 = (v0 | 8);
}
/* fzgx:end fn_1_F2EDC */

/* fzgx:begin fn_1_F2EFC */
// Clears the active replay flag and marks the replay entry as ready.
void fn_1_F2EFC(void) {
    u8 flags = lbl_1_bss_7EFD4;

    if ((flags & 1) == 0) {
        return;
    }
    if (((flags >> 5) & 1) != 0) {
        return;
    }

    lbl_1_bss_7EFD4 = flags & ~8;
    lbl_1_bss_7EFD8.unk_19 = 1;
}
/* fzgx:end fn_1_F2EFC */

/* fzgx:begin fn_1_F2F34 noprologue */
#include "types.h"

extern struct fn_1_F2F34_lbl_1_bss_7EFD4 lbl_1_bss_7EFD4;

struct fn_1_F2F34_lbl_1_bss_7EFD4 {
    u8 unk_0;
};

u32 fn_1_F2F34(void) {
    u8 v0;
    v0 = lbl_1_bss_7EFD4.unk_0;
    if ((lbl_1_bss_7EFD4.unk_0 & 0x1) == 0) {
    v0 = 0;
    return v0;
    }
    v0 = ((v0 >> 2) & 0x1);
    return v0;
}
/* fzgx:end fn_1_F2F34 */

/* fzgx:begin fn_1_F2F58 */
u32 fn_1_F2F58(void) {
    u8 flags = lbl_1_bss_7EFD4;

    if ((flags & 1) == 0) {
        return 0;
    }
    return (u32)__cntlzw((u32)((flags >> 2) & 1)) >> 5;
}
/* fzgx:end fn_1_F2F58 */

/* fzgx:begin fn_1_F4594 */
u32 fn_1_F4594(void) {
    return lbl_1_bss_7EFD8.unk_4;
}
/* fzgx:end fn_1_F4594 */

/* fzgx:begin fn_1_F45A4 */
u32 fn_1_F45A4(void) {
    return lbl_1_bss_7EFD8.unk_8;
}
/* fzgx:end fn_1_F45A4 */

/* fzgx:begin fn_1_F45B4 */
u32 fn_1_F45B4(void) {
    return ((__cntlzw(((lbl_1_bss_7EFD4 >> 4) & 0x1)) >> 5) & 0xFF);
}
/* fzgx:end fn_1_F45B4 */

/* fzgx:begin fn_1_F4794 */
void fn_1_F4794(u16 value) {
    lbl_1_bss_7F01C = value;
}
/* fzgx:end fn_1_F4794 */

/* fzgx:begin fn_1_F47A0 */
void fn_1_F47A0(u32 value) {
    lbl_1_bss_7F020 = value;
}
/* fzgx:end fn_1_F47A0 */

/* fzgx:begin fn_1_F47AC */
u32 fn_1_F47AC(void) {
    u32 tick;
    u8 flags;

    tick = OSGetTick();
    flags = lbl_1_bss_7EFD4;
    if ((flags & 1) == 0) {
        return tick;
    }
    if (((flags >> 1) & 1) != 0) {
        lbl_1_bss_7F020 = tick;
    } else if (((flags >> 2) & 1) != 0) {
        tick = lbl_1_bss_7F020;
    }
    return tick;
}
/* fzgx:end fn_1_F47AC */
