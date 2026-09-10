#include "types.h"

/* fzgx:begin fn_15_1F4 */
extern s32 lbl_15_bss_14;
extern s32 lbl_15_bss_1C;
extern void fn_15_B90(void);

void fn_15_1F4(void) {
    if ((lbl_15_bss_14 & 0x10000000) != 0) {
        if (lbl_15_bss_1C != 0) {
            lbl_15_bss_1C -= 1;
        }
        if (lbl_15_bss_1C == 0) {
            lbl_15_bss_14 &= ~0x10000000;
            fn_15_B90();
        }
    }
}
/* fzgx:end fn_15_1F4 */

/* fzgx:begin fn_15_260 */
extern struct fn_15_260_lbl_15_bss_0 lbl_15_bss_0;
extern u32 fn_1_435C(u32);
extern void fn_1_407C(void);
extern void fn_1_3CC4(void);
extern s32 fn_1_8DB94(void);
extern void fn_1_86254(u32);
extern void fn_1_106EB0(void);
extern s32 camera_get_flags(void);
extern void camera_update(void);
extern u32 fn_1_58C4(void);
extern void fn_1_5948(s32);
extern void fn_1_9A770(void);
extern void fn_1_627C(s32);

struct fn_15_260_lbl_15_bss_0 {
    u8 pad_0[0xC];
    u32 unk_C;
    u32 unk_10;
    u8 pad_14[0xD];
    u8 unk_21;
    u8 pad_22[2];
    u32 unk_24;
    u32 unk_28;
};

void fn_15_260(void) {
    struct fn_15_260_lbl_15_bss_0 *p_lbl_15_bss_0;
    u32 count;
    s32 i;
    s16 index;

    p_lbl_15_bss_0 = (struct fn_15_260_lbl_15_bss_0 *)&lbl_15_bss_0;
    if (p_lbl_15_bss_0->unk_21 != 0) {
        fn_1_435C(p_lbl_15_bss_0->unk_24);
        fn_1_407C();
    }
    fn_1_435C(p_lbl_15_bss_0->unk_C);
    fn_1_407C();
    fn_1_3CC4();
    if (fn_1_8DB94() != 0) {
        fn_1_86254(0);
        fn_1_106EB0();
    }
    if (camera_get_flags() != 0) {
        camera_update();
    }
    count = fn_1_58C4();
    i = 0;
    while ((s16)i < count) {
        index = (s16)i;
        fn_1_5948(index);
        fn_1_9A770();
        if (p_lbl_15_bss_0->unk_21 != 0) {
            fn_1_435C(p_lbl_15_bss_0->unk_28);
            fn_1_407C();
        }
        fn_1_435C(p_lbl_15_bss_0->unk_10);
        fn_1_407C();
        fn_1_627C(index);
        i++;
    }
}
/* fzgx:end fn_15_260 */

/* fzgx:begin fn_15_350 */
typedef void (*fn_15_350_Fn0)(void);
struct fn_15_350_lbl_15_data_70_0_E16 {
    u8 pad_0[0x4];
    u32 unk_4;
    u32 unk_8;
    u32 unk_C;
};

extern s16 lbl_1_bss_962;
extern u8 lbl_15_data_70[32];
extern u32 lbl_1_bss_71688;
extern u32 lbl_1_bss_7168C;

void fn_15_350(void) {
    u32 v0;
    struct fn_15_350_lbl_15_data_70_0_E16 *p;
    p = (struct fn_15_350_lbl_15_data_70_0_E16 *)&lbl_15_data_70;
    p += lbl_1_bss_962 - 183;
    lbl_1_bss_71688 = p->unk_8;
    v0 = p->unk_C;
    lbl_1_bss_7168C = v0;
    ((fn_15_350_Fn0)p->unk_4)();
}
/* fzgx:end fn_15_350 */

/* fzgx:begin fn_15_B8C */
// fn_15_B8C: empty in retail (single blr).
void fn_15_B8C(void) {
}
/* fzgx:end fn_15_B8C */

/* fzgx:begin fn_15_1D7C */
extern struct fn_15_1D7C_lbl_15_bss_0 lbl_15_bss_0;
extern u32 fn_15_1F28(u32, u32);
extern u32 fn_15_FCC(void);
extern u32 fn_1_4A00(u32, u32, u32);

struct fn_15_1D7C_lbl_15_bss_0 {
    u8 pad_0[0xC];
    u32 unk_C;
    u32 unk_10;
    u32 unk_14;
};

u32 fn_15_1D7C(u32 arg0, u32 arg1, u32 arg2) {
    struct fn_15_1D7C_lbl_15_bss_0 *p_lbl_15_bss_0;
    u32 v0;
    u32 v1;
    u32 v2;
    u32 t0, t1, t2, t3;
    p_lbl_15_bss_0 = (struct fn_15_1D7C_lbl_15_bss_0 *)&lbl_15_bss_0;
    v0 = arg2;
    v1 = arg0;
    v2 = arg1;
    if ((p_lbl_15_bss_0->unk_14 & 0x78) == 0) {
    v0 = p_lbl_15_bss_0->unk_10;
    v1 = 1;
    v2 = 30;
    t0 = fn_1_4A00(v1, v2, v0);
    v1 = t0;
    } else {
    v0 = p_lbl_15_bss_0->unk_10;
    v1 = 0;
    v2 = 0;
    t1 = fn_1_4A00(v1, v2, v0);
    v1 = t1;
    }
    v1 = p_lbl_15_bss_0->unk_C;
    v2 = p_lbl_15_bss_0->unk_10;
    t2 = fn_15_1F28(v1, v2);
    v1 = t2;
    if ((p_lbl_15_bss_0->unk_14 & 0x1) != 0) {
    t3 = fn_15_FCC();
    v1 = t3;
    }
    return v1;
}
/* fzgx:end fn_15_1D7C */

/* fzgx:begin fn_15_1EE0 */
extern struct fn_15_1EE0_lbl_15_bss_0 lbl_15_bss_0;
extern u32 camera_enable_flags(u32);
extern u32 fn_15_236C(u32, u32);

struct fn_15_1EE0_lbl_15_bss_0 {
    u8 pad_0[0xC];
    u32 unk_C;
    u32 unk_10;
    u32 unk_14;
};

void fn_15_1EE0(void) {
    struct fn_15_1EE0_lbl_15_bss_0 *p_lbl_15_bss_0;
    u32 t0;
    p_lbl_15_bss_0 = (struct fn_15_1EE0_lbl_15_bss_0 *)&lbl_15_bss_0;
    t0 = fn_15_236C(p_lbl_15_bss_0->unk_C, p_lbl_15_bss_0->unk_10);
    if ((p_lbl_15_bss_0->unk_14 & 0x1) != 0) {
    camera_enable_flags(t0);
    }
}
/* fzgx:end fn_15_1EE0 */

/* fzgx:begin fn_15_2228 */
extern u32 fn_15_2CEC(void);
extern u32 fn_15_3AFC(void);
extern u32 fn_15_401C(void);
extern u32 fn_15_4124(void);
extern u32 lbl_15_bss_14;
extern u8 lbl_15_bss_21;

void fn_15_2228(void) {
    if ((lbl_15_bss_14 & ~0x7FFFFFFF) != 0) {
    fn_15_4124();
    }
    fn_15_2CEC();
    fn_15_3AFC();
    if (lbl_15_bss_21 != 0) {
    fn_15_401C();
    }
}
/* fzgx:end fn_15_2228 */

/* fzgx:begin fn_15_2274 */
struct fn_15_2274_lbl_15_bss_0 {
    u8 pad_0[0x14];
    u32 unk_14;
    u8 pad_18[0x9];
    u8 unk_21;
    u8 pad_22[0x4E];
    u32 unk_70;
};

struct fn_15_2274_lbl_15_rodata_0 {
    u8 pad_0[0xA8];
    u32 unk_A8;
    u32 unk_AC;
    u32 unk_B0;
    u32 unk_B4;
    u32 unk_B8;
};

extern struct fn_15_2274_lbl_15_bss_0 lbl_15_bss_0;
extern struct fn_15_2274_lbl_15_rodata_0 lbl_15_rodata_0;
extern void fn_15_435C(void);
extern void fn_15_405C(void);
extern void fn_15_2D74(void);
extern void fn_80007AB4(void *);

void fn_15_2274(void) {
    struct fn_15_2274_lbl_15_rodata_0 *p_lbl_15_rodata_0;
    struct fn_15_2274_lbl_15_bss_0 *p_lbl_15_bss_0;
    u32 v0;
    p_lbl_15_rodata_0 = &lbl_15_rodata_0;
    p_lbl_15_bss_0 = &lbl_15_bss_0;
    if ((p_lbl_15_bss_0->unk_14 & 0x80000000) != 0) {
        fn_15_435C();
    }
    v0 = p_lbl_15_bss_0->unk_70;
    switch (v0) {
    case 0: {
        u32 local0;
        local0 = p_lbl_15_rodata_0->unk_A8;
        fn_80007AB4(&local0);
        break;
    }
    case 1: {
        u32 local1;
        local1 = p_lbl_15_rodata_0->unk_AC;
        fn_80007AB4(&local1);
        break;
    }
    case 2: {
        u32 local2;
        local2 = p_lbl_15_rodata_0->unk_B0;
        fn_80007AB4(&local2);
        break;
    }
    case 3: {
        u32 local3;
        local3 = p_lbl_15_rodata_0->unk_B4;
        fn_80007AB4(&local3);
        break;
    }
    default: {
        u32 local4;
        local4 = p_lbl_15_rodata_0->unk_B8;
        fn_80007AB4(&local4);
        break;
    }
    }
    if (p_lbl_15_bss_0->unk_21 != 0) {
        fn_15_405C();
    }
    if ((p_lbl_15_bss_0->unk_14 & 0x80) != 0) {
        fn_15_2D74();
    }
}
/* fzgx:end fn_15_2274 */

/* fzgx:begin fn_15_236C */
struct fn_15_236C_lbl_15_bss_0 {
    u8 pad_0[0x8];
    u32 unk_8;
    u8 pad_C[0x8];
    u32 unk_14;
    u8 pad_18[0x9];
    u8 unk_21;
};
struct fn_15_236C_lbl_1_bss_6EAD0 {
    u32 unk_0;
};

extern struct fn_15_236C_lbl_15_bss_0 lbl_15_bss_0;
extern struct fn_15_236C_lbl_1_bss_6EAD0 lbl_1_bss_6EAD0;
extern u32 fn_15_2CF0(u32);
extern u32 fn_15_38FC(u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_46B4(u32, u32, u32, u32);
extern u32 fn_1_A0AA4(u32);
extern u32 ADXT_Stop(u32);
extern u32 lbl_15_data_A4;
extern u32 lbl_801A6410;
extern void fn_15_3B00(void);
extern void fn_15_4060(void);
extern void fn_1_410A0(void);
extern void fn_1_41A8(void);
extern void fn_1_469BC(void);
extern void fn_1_6400(void);

void fn_15_236C(u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    struct fn_15_236C_lbl_15_bss_0 *p_lbl_15_bss_0;
    u32 v0;
    u32 v1;
    u32 v2;
    u32 v3;
    u32 t2, t3, t4, t8;
    p_lbl_15_bss_0 = (struct fn_15_236C_lbl_15_bss_0 *)&lbl_15_bss_0;
    fn_1_469BC();
    ADXT_Stop(*(u32 *)((u8 *)lbl_1_bss_6EAD0.unk_0 + 0));
    t2 = ADXT_Stop(*(u32 *)((u8 *)lbl_1_bss_6EAD0.unk_0 + 4));
    t3 = fn_1_A0AA4(t2);
    t4 = fn_15_2CF0(t3);
    if ((p_lbl_15_bss_0->unk_14 & 0x80) == 0) {
    fn_15_38FC(t4);
    }
    fn_15_3B00();
    if (p_lbl_15_bss_0->unk_21 != 0) {
    fn_15_4060();
    }
    v0 = p_lbl_15_bss_0->unk_8;
    v3 = arg3;
    if (v0 != 0) {
    v3 = (u32)&lbl_801A6410;
    v1 = (u32)&lbl_15_data_A4;
    v2 = *(u32 *)((u8 *)v3 + 0);
    v3 = 1768;
    t8 = fn_1_46B4(v2, v0, (u32)v1, v3);
    v2 = t8;
    p_lbl_15_bss_0->unk_8 = 0;
    }
    fn_1_435C(arg0);
    fn_1_41A8();
    fn_1_435C(arg1);
    fn_1_41A8();
    fn_1_410A0();
    fn_1_6400();
}
/* fzgx:end fn_15_236C */

/* fzgx:begin fn_15_2CEC */
// fn_15_2CEC: empty in retail (single blr).
void fn_15_2CEC(void) {
}
/* fzgx:end fn_15_2CEC */

/* fzgx:begin fn_15_30E8 */
extern struct fn_15_30E8_lbl_15_bss_0 lbl_15_bss_0;
extern void fn_15_3368(s16);

struct fn_15_30E8_entry {
    u32 unk_0;
    u8 unk_4;
    u8 value;
    u8 unk_6[2];
};

struct fn_15_30E8_object {
    u8 unk_0[0x81a0];
    u8 value;
};

struct fn_15_30E8_lbl_15_bss_0 {
    u8 unk_0[0x2c];
    struct fn_15_30E8_entry *entries;
    u8 unk_30[8];
    s16 entry_offset;
    u8 unk_3a[0x112];
    s16 entry_count;
};

void fn_15_30E8(void) {
    struct fn_15_30E8_lbl_15_bss_0 *state;
    struct fn_15_30E8_entry *entry;
    s32 i;
    s16 value;

    state = &lbl_15_bss_0;
    entry = state->entries;
    i = 0;
    while (i < state->entry_count) {
        value = entry[i + state->entry_offset].value;
        if ((s16)value >= 0x29) {
            value = ((struct fn_15_30E8_object *)entry[i + state->entry_offset].unk_0)->value;
        }
        fn_15_3368((s16)value);
        i++;
    }
}
/* fzgx:end fn_15_30E8 */

/* fzgx:begin fn_15_3A14 */
extern struct fn_15_3A14_lbl_15_bss_74 lbl_15_bss_74;
extern struct fn_15_3A14_lbl_15_bss_78 lbl_15_bss_78;
extern u32 fn_1_3F8C(u32, u32, u32, u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_7ACDC(u32);
extern u32 fn_1_7EAE8(void);
extern u8 lbl_15_data_0[];
extern void fn_1_789E8(void);
extern void fn_1_78EBC(void);
extern void fn_1_7E9C4(void);
extern void fn_1_9A5CC(void);
extern void fn_1_9A7BC(void);

struct fn_15_3A14_lbl_15_bss_74 {
    u32 unk_0;
};
struct fn_15_3A14_lbl_15_bss_78 {
    u32 unk_0;
};

void fn_15_3A14(void) {
    u8 *p_lbl_15_data_0;
    p_lbl_15_data_0 = (u8 *)&lbl_15_data_0;
    fn_1_435C(lbl_15_bss_74.unk_0);
    fn_1_3F8C((u32)((u8 *)p_lbl_15_data_0 + 608), (u32)fn_1_789E8, 0, 21);
    fn_1_3F8C((u32)((u8 *)p_lbl_15_data_0 + 620), (u32)fn_1_9A5CC, 0, 23);
    fn_1_435C(lbl_15_bss_78.unk_0);
    fn_1_3F8C((u32)((u8 *)p_lbl_15_data_0 + 636), (u32)fn_1_7E9C4, 0, 4);
    fn_1_3F8C((u32)((u8 *)p_lbl_15_data_0 + 644), (u32)fn_1_7EAE8, 0, 29);
    fn_1_3F8C((u32)((u8 *)p_lbl_15_data_0 + 652), (u32)fn_1_78EBC, 0, 7);
    fn_1_3F8C((u32)((u8 *)p_lbl_15_data_0 + 664), (u32)fn_1_9A7BC, 0, 10);
    fn_1_7EAE8();
    fn_1_7ACDC(50);
}
/* fzgx:end fn_15_3A14 */

/* fzgx:begin fn_15_3AFC */
// fn_15_3AFC: empty in retail (single blr).
void fn_15_3AFC(void) {
}
/* fzgx:end fn_15_3AFC */

/* fzgx:begin fn_15_3B00 */
extern u32 fn_1_79100(void);
extern u32 fn_1_7EAE8(u32);

void fn_15_3B00(void) {
    u32 t0;
    t0 = fn_1_79100();
    fn_1_7EAE8(t0);
}
/* fzgx:end fn_15_3B00 */

/* fzgx:begin fn_15_401C */
extern u32 fn_1_C6F80(u32);
extern u32 lbl_15_bss_14;

u32 fn_15_401C(u32 arg0) {
    u32 v0;
    u32 t0, t1;
    v0 = arg0;
    if ((lbl_15_bss_14 & 0x40000000) != 0) {
    v0 = 1;
    t0 = fn_1_C6F80(v0);
    v0 = t0;
    } else {
    v0 = 0;
    t1 = fn_1_C6F80(v0);
    v0 = t1;
    }
    return v0;
}
/* fzgx:end fn_15_401C */

/* fzgx:begin fn_15_405C */
// fn_15_405C: empty in retail (single blr).
void fn_15_405C(void) {
}
/* fzgx:end fn_15_405C */

/* fzgx:begin fn_15_4060 */
extern struct fn_15_4060_lbl_15_bss_0 lbl_15_bss_0;
extern struct fn_15_4060_lbl_801A6410 lbl_801A6410;
extern u32 fn_1_41A8(u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_46B4(u32, u32, void *, u32);
extern u32 fn_1_58854(u32);
extern u32 fn_1_85878(void);
extern u32 fn_1_982C4(u32);
extern u32 fn_1_C47B4(u32);
extern u32 fn_1_C6F80(u32);
extern u32 lbl_15_data_A4;

struct fn_15_4060_lbl_15_bss_0 {
    u8 pad_0[0x21];
    u8 unk_21;
    u8 pad_22[0x2];
    u32 unk_24;
    u32 unk_28;
    u8 pad_2C[0x124];
    u32 unk_150;
};
struct fn_15_4060_lbl_801A6410 {
    u32 unk_0;
};

void fn_15_4060(void) {
    struct fn_15_4060_lbl_15_bss_0 *p_lbl_15_bss_0;
    u32 t0, t1, t2, t6, t8;
    p_lbl_15_bss_0 = (struct fn_15_4060_lbl_15_bss_0 *)&lbl_15_bss_0;
    t0 = fn_1_85878();
    t1 = fn_1_982C4(t0);
    t2 = fn_1_58854(t1);
    fn_1_C47B4(t2);
    fn_1_C6F80(0);
    fn_1_46B4(lbl_801A6410.unk_0, p_lbl_15_bss_0->unk_150, &lbl_15_data_A4, 2849);
    t6 = fn_1_435C(p_lbl_15_bss_0->unk_24);
    fn_1_41A8(t6);
    t8 = fn_1_435C(p_lbl_15_bss_0->unk_28);
    fn_1_41A8(t8);
    fn_1_46B4(lbl_801A6410.unk_0, p_lbl_15_bss_0->unk_24, &lbl_15_data_A4, 2854);
    fn_1_46B4(lbl_801A6410.unk_0, p_lbl_15_bss_0->unk_28, &lbl_15_data_A4, 2855);
    p_lbl_15_bss_0->unk_21 = 0;
}
/* fzgx:end fn_15_4060 */

/* fzgx:begin fn_15_4568 */
extern u16 lbl_15_bss_154;

void fn_15_4568(void) {
    lbl_15_bss_154 = 0;
}
/* fzgx:end fn_15_4568 */

/* fzgx:begin fn_15_545C */
// fn_15_545C: empty in retail (single blr).
void fn_15_545C(void) {
}
/* fzgx:end fn_15_545C */
