#include "types.h"
#include "rel/sel/globals.h"

extern int fn_1_152970(int, int, int, int, struct Fn10Data *, int, int);
extern u32 lbl_10_bss_49384;
extern void fn_1_435C(u32);
extern void fn_1_407C(void);
extern void fn_1_3CC4(void);
extern int fn_1_4C10(void);
extern struct Fn10834State lbl_1_bss_8B3A0;
extern struct Fn10834Status lbl_1_bss_962;
extern u16 lbl_1_bss_968;
extern void fn_10_CFDC(void);
extern void fn_1_12C060(void *);
extern void fn_1_A266C(void);
extern u32 lbl_10_bss_14;
extern struct Fn10834Event lbl_1_bss_9C;
extern u8 lbl_1_bss_8CA28;
extern void fn_1_A2D84(u32);

/* fzgx:begin fn_10_0 noprologue */
#include "types.h"

extern struct Fn10Data lbl_10_bss_0;
extern int fn_1_152970(int, int, int, int, struct Fn10Data *, int, int);

struct Fn10Data {
    u8 pad[0x18];
    s16 value_18;
    s16 value_1a;
};

s16 fn_10_0(int first, int second, int third, int fourth) {
    return (s16)fn_1_152970(second, first, third, fourth,
        (struct Fn10Data *)((u8 *)&lbl_10_bss_0 + 0x1c),
        lbl_10_bss_0.value_1a, lbl_10_bss_0.value_18);
}
/* fzgx:end fn_10_0 */

/* fzgx:begin fn_10_834 */
struct Fn10834State {
    u8 pad_0[0x94];
    u32 flags;
    u8 pad_98[0xC];
    u32 entries;
    u8 pad_A8[0x7C];
    u32 countdown;
    u8 ready;
    u8 pad_129[0x17];
    u32 mode;
};
struct Fn10834Status { s16 value; };
struct Fn10834Event {
    u8 pad_0[2];
    u8 value_2;
    u8 pad_3[1];
    u16 value_4;
    u8 pad_6[2];
    u32 value_8;
};

void fn_10_834(void) {
    struct Fn10834State *state;
    u8 *entry;
    s16 i;

    fn_10_CFDC();
    lbl_1_bss_8CA28 = 0;
    if ((lbl_1_bss_8B3A0.countdown + 0x10000) != 65535 &&
        lbl_1_bss_8B3A0.ready == 0) {
        lbl_1_bss_8B3A0.countdown -= 1;
    }

    state = &lbl_1_bss_8B3A0;
    if (((state->flags >> 11) & 1) == 0 && lbl_1_bss_8B3A0.countdown <= 300) {
        if (lbl_1_bss_8B3A0.countdown % 60 == 0 && lbl_1_bss_8B3A0.countdown != 0 &&
            (s32)fn_1_4C10() == 0) {
            fn_1_A2D84(0xA9010C00);
        }
    }
    if ((s32)lbl_10_bss_14 == -1) {
        fn_1_4C10();
    }

    {
        int active;
        if ((lbl_1_bss_8B3A0.mode & 0x80000000) != 0 &&
            (lbl_1_bss_8B3A0.mode & 0x40000000) == 0 &&
            (state->flags & 0x8) == 0) {
            active = 1;
        } else {
            if (fn_1_4C10()) active = 1;
            else active = 0;
        }
        if (active == 0) {
            entry = (u8 *)lbl_1_bss_8B3A0.entries +
                (s16)(lbl_1_bss_962.value - 14) * 148;
            for (i = 0; i < 4; i++) {
                fn_1_12C060(entry + 36);
                entry += 28;
            }
            if (lbl_1_bss_962.value != 20) {
                if ((s32)fn_1_4C10() == 0) {
                    if ((state->flags & 0x8000000) != 0) {
                        if ((state->flags & 0x200000) != 0) {
                            lbl_1_bss_9C.value_2 = lbl_1_bss_8B3A0.pad_0[0x9e];
                            lbl_1_bss_9C.value_4 = 6;
                            lbl_1_bss_9C.value_8 = 134;
                            lbl_1_bss_968 = 9;
                        } else if ((state->flags & 0x100000) != 0) {
                            lbl_1_bss_968 = 3;
                        } else if ((state->flags & 0x80000) != 0) {
                            lbl_1_bss_968 = 5;
                        } else if ((state->flags & 0x80) != 0) {
                            lbl_1_bss_968 = 12;
                        } else if ((state->flags & 0x40) != 0) {
                            lbl_1_bss_968 = 15;
                        } else {
                            lbl_1_bss_968 = 2;
                        }
                    } else if ((state->flags & 0x4000000) != 0) {
                        lbl_1_bss_968 = 10;
                    } else if ((state->flags & 0x1000000) != 0) {
                        lbl_1_bss_968 = 9;
                    }
                }
                fn_1_A266C();
            }
        }
    }
}
/* fzgx:end fn_10_834 */

/* fzgx:begin fn_10_AB8 */
void fn_10_AB8(void) {
    fn_1_435C(lbl_10_bss_49384);
    fn_1_407C();
    fn_1_3CC4();
    fn_1_435C(lbl_10_bss_49388);
    fn_1_407C();
}
/* fzgx:end fn_10_AB8 */
