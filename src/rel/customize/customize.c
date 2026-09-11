#include "types.h"
extern s32 lbl_3_bss_120;
extern u32 lbl_3_bss_F0[12];
extern s32 fn_1_4C10(void);
extern s16 fn_3_B270(void);
extern u16 lbl_1_bss_96A;
extern u32 lbl_3_bss_20850;
extern u32 lbl_3_bss_243A8[6];
extern void fn_1_4A00(s32, s32, u32);
extern u16 lbl_3_bss_20[104];
extern u32 lbl_3_bss_2C7C0[66624];
extern void fn_80008BEC(void *, s32, s32);
extern void fn_1_FDFF4(void);
extern void fn_1_FC4E0(void *, s32);
extern u32 lbl_3_bss_7EBA4;
extern u32 lbl_3_bss_7EBA8;
extern u8 lbl_3_data_11DC[84];
extern u32 lbl_801A6410;
extern void fn_1_7F3AC(u32);
extern void fn_1_46B4(u32, u32, u8 *, s32);
extern void fn_1_BC29C(u32 *arg0);
extern void fn_1_B9C0C(void);
extern char lbl_3_data_1A1C[17];
extern u8 fn_1_B7C00(void);
extern s32 fn_1_B7CD4(void);
extern s32 fn_1_B7C5C(void);
extern void OSReport(const char *, ...);
extern u32 lbl_3_bss_A179C;
extern u32 lbl_3_data_1A14;

/* fzgx:begin fn_3_B5FC */
void fn_3_B5FC(void) {
    u32 flags;
    s32 ready;

    if (lbl_3_bss_120 == -1) {
        fn_1_4C10();
    }

    flags = lbl_3_bss_F0[9];
    if ((flags & (~((u32)-1 >> 1))) != 0 &&
        (flags & 1) == 0 &&
        (lbl_3_bss_F0[0] & 2) == 0) {
        ready = 1;
    } else if (fn_1_4C10() != 0) {
        ready = 1;
    } else {
        ready = 0;
    }

    if (ready == 0) {
        if (lbl_3_bss_120 != -1) {
            s32 value = lbl_3_bss_120;
            lbl_3_bss_120 = -1;
            lbl_1_bss_96A = (u16)value;
        } else if (fn_3_B270() == (s16)-1) {
            fn_1_4A00(0, 15, lbl_3_bss_20850);
            lbl_3_bss_243A8[0] = 0;
            lbl_3_bss_120 = 110;
        }
    }
}
/* fzgx:end fn_3_B5FC */

/* fzgx:begin fn_3_B984 */
void fn_3_B984(void *entries, u8 *table) {
    u8 i;
    u8 j;
    u32 offset;

    for (i = 0; i < 3; i++) {
        offset = ((u32)i) << 3;
        if (table[offset + 0x81a4] != ((u8 *)lbl_3_bss_20)[offset]) {
            for (j = 0; j < 4; j++) {
                u8 *entry = (u8 *)entries + (u32)j * 0x2060;
                if ((*(u32 *)(entry + 0x24) & ((u32)1 << 31)) != 0) {
                    s16 *field = (s16 *)(entry + 0x20);
                    if (*field == i) {
                        fn_80008BEC(field, 0, 0x2060);
                    }
                }
            }
            fn_1_FDFF4();
            fn_1_FC4E0((u8 *)lbl_3_bss_2C7C0 +
                (s32)((s16 *)lbl_3_bss_F0)[4] * 0x10440, 1);
        }
    }
}
/* fzgx:end fn_3_B984 */

/* fzgx:begin fn_3_BC60 */
void fn_3_BC60(void) {
    u32 *value;

    value = &lbl_3_bss_7EBA4;
    if (*value != 0) {
        fn_1_7F3AC(*value);
    }
    if (lbl_3_bss_7EBA8 != 0) {
        fn_1_46B4(lbl_801A6410, lbl_3_bss_7EBA8, lbl_3_data_11DC, 0x12ad);
    }
    if (lbl_3_bss_7EBA4 != 0) {
        fn_1_46B4(lbl_801A6410, lbl_3_bss_7EBA4, lbl_3_data_11DC, 0x12af);
    }
    lbl_3_bss_7EBA4 = 0;
    lbl_3_bss_7EBA8 = 0;
}
/* fzgx:end fn_3_BC60 */

/* fzgx:begin fn_3_BD00 noprologue */
#include "types.h"

extern u16 lbl_3_bss_F0[24];

void fn_3_BD00(u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    *(u32 *)&lbl_3_bss_F0[18] = 0;
    *(u32 *)&lbl_3_bss_F0[18] |= 0x80000000;
    *(u32 *)&lbl_3_bss_F0[18] |= arg3;
    *(s16 *)&lbl_3_bss_F0[20] = arg0;
    *(s16 *)&lbl_3_bss_F0[21] = arg1;
    *(s16 *)&lbl_3_bss_F0[22] = arg2;
}
/* fzgx:end fn_3_BD00 */

/* fzgx:begin fn_3_BD30 noprologue */
#include "types.h"

extern u16 lbl_3_bss_F0[24];

void fn_3_BD30(void) {
    s16 current;
    s16 value;

    if ((*(u32 *)&lbl_3_bss_F0[18] & 0x80000000) == 0) {
        return;
    }
    value = *(s16 *)&lbl_3_bss_F0[20];
    current = *(s16 *)&lbl_3_bss_F0[21];
    current += value;
    *(s16 *)&lbl_3_bss_F0[21] = current;
    if (value <= 0 || current < *(s16 *)&lbl_3_bss_F0[22]) {
        if (value >= 0) {
            return;
        }
        if (*(s16 *)&lbl_3_bss_F0[21] > *(s16 *)&lbl_3_bss_F0[22]) {
            return;
        }
    }
    *(u32 *)&lbl_3_bss_F0[18] = 0;
}
/* fzgx:end fn_3_BD30 */

/* fzgx:begin fn_3_BD98 */
struct CustomizeState {
    u32 flags;
    u8 unk4;
};

extern struct CustomizeState lbl_3_bss_7ED58;
extern u32 lbl_3_data_1A18;
extern void fn_1_B9BE0(void);
extern void fn_1_B9DE8(struct CustomizeState *);

extern u32 fn_3_1307C(void);
extern u32 lbl_3_bss_A1784[5];
extern u32 lbl_3_data_1A10;
extern u32 lbl_3_bss_7EDA0[8];

void fn_3_BD98(void) {
    fn_1_B9BE0();
    fn_1_B9DE8(&lbl_3_bss_7ED58);
    lbl_3_bss_7ED58.flags |= 0x10;
    lbl_3_bss_7ED58.unk4 = 9;
    lbl_3_data_1A18 = 0;
    lbl_3_data_1A10 = fn_3_1307C() & 0xff;
    lbl_3_bss_7EDA0[0] = lbl_3_bss_A1784[0];
}
/* fzgx:end fn_3_BD98 */

/* fzgx:begin fn_3_BE10 */
extern struct fn_3_BE10_lbl_3_bss_7ED58 lbl_3_bss_7ED58;
extern struct fn_3_BE10_lbl_3_bss_A1784 lbl_3_bss_A1784;
extern u32 fn_1_B9BE0(void);
extern u32 fn_1_B9DE8(u32);
extern u32 fn_3_1307C(void);
extern u32 lbl_3_bss_7EDA0;
extern u32 lbl_3_data_1A10;
extern u32 lbl_3_data_1A18;

struct fn_3_BE10_lbl_3_bss_7ED58 {
    u32 unk_0;
    u8 unk_4;
};
struct fn_3_BE10_lbl_3_bss_A1784 {
    u32 unk_0;
};

void fn_3_BE10(void) {
    u32 v0;
    u32 v1;
    u32 v2;
    u32 t2;
    fn_1_B9BE0();
    fn_1_B9DE8((u32)&lbl_3_bss_7ED58);
    v0 = lbl_3_bss_7ED58.unk_0;
    v1 = (v0 | 16);
    lbl_3_bss_7ED58.unk_4 = 10;
    lbl_3_bss_7ED58.unk_0 = v1;
    lbl_3_data_1A18 = 0;
    t2 = fn_3_1307C();
    v2 = lbl_3_bss_A1784.unk_0;
    lbl_3_data_1A10 = (t2 & 0xFF);
    lbl_3_bss_7EDA0 = v2;
}
/* fzgx:end fn_3_BE10 */

/* fzgx:begin fn_3_BEF0 */
extern u32 lbl_3_bss_7ED58[18];
extern void fn_1_BC29C(u32 *);
extern void fn_1_B9C0C(void);

void fn_3_BEF0(void) {
    fn_1_BC29C(lbl_3_bss_7ED58);
    fn_1_B9C0C();
}
/* fzgx:end fn_3_BEF0 */

/* fzgx:begin fn_3_C128 */
extern u32 lbl_3_bss_7ED58[18];
extern u32 lbl_3_bss_A179C;
extern u32 lbl_3_data_1A18;

extern s8 fn_1_BA144(u32 *);

void fn_3_C128(void) {
    s16 result;

    lbl_3_bss_A179C = 0;
    result = fn_1_BA144(lbl_3_bss_7ED58);
    if (result == 0) {
        lbl_3_data_1A18 = 1;
    } else if (result == 1) {
        lbl_3_bss_A179C = 1;
    }
}
/* fzgx:end fn_3_C128 */

/* fzgx:begin fn_3_C188 */
extern u32 lbl_3_bss_7ED58[18];
extern u32 lbl_3_data_1A10;
extern u32 *lbl_3_bss_7EDA0;
extern u32 lbl_3_data_1A18;

extern void fn_1_C0510(u32 *arg0);

void fn_3_C188(void) {
    s8 status;

    status = ((s8 *)lbl_3_bss_7ED58)[0x14];
    if (status == 1) {
        lbl_3_bss_7ED58[2] = lbl_3_bss_7EDA0[lbl_3_data_1A10];
        lbl_3_bss_7ED58[3] = 0x2000;
        lbl_3_bss_7ED58[4] = 4;
        lbl_3_data_1A18 = 2;
    } else if (status == 2) {
        lbl_3_data_1A18 = 3;
    } else if (status == 8) {
        lbl_3_data_1A18 = 4;
    }
    fn_1_C0510(lbl_3_bss_7ED58);
}
/* fzgx:end fn_3_C188 */

/* fzgx:begin fn_3_C234 */
extern char lbl_3_data_1A1C[17];
extern u32 lbl_3_data_1A18;

extern u8 fn_1_B7C00(void);
extern s32 fn_1_B7CD4(void);
extern s32 fn_1_B7C5C(void);
extern void OSReport(const char *, ...);

void fn_3_C234(void) {
    if (!fn_1_B7C00()) {
        if (fn_1_B7CD4() == 0) {
            OSReport(lbl_3_data_1A1C, fn_1_B7C5C());
        }
        lbl_3_data_1A18 = 5;
    }
}
/* fzgx:end fn_3_C234 */

/* fzgx:begin fn_3_C28C noprologue */
#include "types.h"

extern u32 lbl_3_bss_7EDA0[8];
extern u32 lbl_3_data_1958[6];
extern u32 lbl_3_bss_7ED58[18];
extern u32 lbl_801A6410[1];

extern void fn_80008BA8(u32, u32, u32);
extern void fn_1_46B4(u32, u32, void *, u32);

typedef struct CustomizeData {
    u8 pad0[0xb8];
    u32 index;
    u8 padbc[4];
    u32 state;
    u8 padc4[0x14];
    u8 tail[0xd8 - 0xd8];
} CustomizeData;

void fn_3_C28C(void) {
    CustomizeData *data = (CustomizeData *)lbl_3_data_1958;
    u32 *table = (u32 *)lbl_3_bss_7EDA0[0];
    u32 *work = lbl_3_bss_7ED58;
    fn_80008BA8(table[data->index], work[2], work[3]);
    if (work[2] != 0) {
        fn_1_46B4(lbl_801A6410[0], work[2], &data->tail[0], 0x13c);
        work[2] = 0;
        work[3] = 0;
    }
    data->state = 5;
}
/* fzgx:end fn_3_C28C */

/* fzgx:begin fn_3_C3B4 */
extern u32 lbl_3_bss_7ED58[18];
extern u32 lbl_3_bss_A179C;
extern u32 lbl_3_data_1A14;
extern u32 lbl_3_data_1A18;

extern void fn_1_BC29C(u32 *arg0);
extern void fn_1_B9C0C(void);

void fn_3_C3B4(void) {
    fn_1_BC29C(lbl_3_bss_7ED58);
    fn_1_B9C0C();
    lbl_3_bss_A179C = 1;
    lbl_3_data_1A14 = -1;
    lbl_3_data_1A18 = -1;
}
/* fzgx:end fn_3_C3B4 */
