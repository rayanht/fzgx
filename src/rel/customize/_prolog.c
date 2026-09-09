#include "types.h"

/* fzgx:begin fn_3_844 */
extern void fn_3_2B774(void);
extern void fn_3_BD30(void);
extern void fn_1_4A00(u32, u32, u32);
extern void fn_1_A2D84(u32);

extern s16 lbl_1_bss_962;
extern struct {
    u8 pad[8];
    u16 flags;
} lbl_1_bss_9F8;
extern s32 lbl_1_bss_970;
extern s16 lbl_1_bss_968;
extern u32 lbl_1_bss_6EAB4;
extern u32 lbl_3_bss_20850;

void fn_3_844(void) {
    fn_3_2B774();
    fn_3_BD30();

    if (lbl_1_bss_962 == 0x5c) {
        if ((lbl_1_bss_9F8.flags >> 9) & 1) {
            fn_1_4A00(0, 0xf, lbl_3_bss_20850);
            lbl_1_bss_970 = 0x10;
            fn_1_A2D84(0xA9010200);
            lbl_1_bss_6EAB4 |= 0x24;
        }

        if (lbl_1_bss_970 > 0) {
            if (--lbl_1_bss_970 == 0) {
                lbl_1_bss_968 = 1;
            }
        }
    }
}
/* fzgx:end fn_3_844 */

/* fzgx:begin fn_3_8F8 */
extern u32 lbl_3_bss_2084C;
extern u32 lbl_3_bss_20850;

extern void fn_1_435C(u32 value);
extern void fn_1_407C(void);
extern void fn_1_3CC4(void);
extern void camera_update(void);

void fn_3_8F8(void) {
    fn_1_435C(lbl_3_bss_2084C);
    fn_1_407C();
    fn_1_3CC4();
    camera_update();
    fn_1_435C(lbl_3_bss_20850);
    fn_1_407C();
}
/* fzgx:end fn_3_8F8 */

/* fzgx:begin fn_3_AF8 */
extern u8 lbl_3_bss_140[132868];

typedef struct {
    s16 index;
} Fn3AF8Arg;

int fn_3_AF8(Fn3AF8Arg *arg) {
    u32 *entry = (u32 *)(lbl_3_bss_140 + arg->index * 0x81c0);

    *entry |= (u32)1 << 31;
    *entry &= 0xBFFFFFFF;
    return 0;
}
/* fzgx:end fn_3_AF8 */

/* fzgx:begin fn_3_B30 */
extern u8 lbl_3_bss_140[132868];

typedef struct {
    s16 index;
} Fn3B30Data;

s32 fn_3_B30(Fn3B30Data *data) {
    s16 index = data->index;
    u32 *entry = (u32 *)(lbl_3_bss_140 + index * 0x81c0);
    *entry |= (u32)1 << 31;
    *entry |= (u32)1 << 30;
    return 0;
}
/* fzgx:end fn_3_B30 */

/* fzgx:begin fn_3_B68 */
extern u8 lbl_3_bss_140[132868];

s32 fn_3_B68(const s16 *value) {
    u8 *base = lbl_3_bss_140;
    s32 offset = (s32)*value * 0x81c0;
    u32 *entry = (u32 *)(base + offset);

    *entry &= 0xbfffffffu;
    *entry &= 0x7fffffffu;
    return 0;
}
/* fzgx:end fn_3_B68 */

/* fzgx:begin fn_3_BFC */
extern void fn_80083DB0(char *destination, const char *source);
extern char *fn_80083970(char *buffer, const char *source);
extern unsigned int strlen(const char *string);
extern char *strncpy(char *destination, const char *source, unsigned int count);
extern char *strcat(char *destination, const char *source);

void fn_3_BFC(char *destination, void *unused, const char *source, const char *suffix) {
    char buffer[0x400];
    char *prefix;
    unsigned int source_length;
    unsigned int prefix_length;

    fn_80083DB0(buffer, unused);
    prefix = fn_80083970(buffer, source);
    if (prefix == 0) {
        fn_80083DB0(destination, buffer);
    } else {
        source_length = strlen(source);
        if (prefix != buffer) {
            prefix_length = (unsigned int)(prefix - buffer);
            strncpy(destination, buffer, prefix_length);
            destination[prefix_length] = 0;
        } else {
            destination[0] = 0;
        }
        strcat(destination, suffix);
        strcat(destination, prefix + source_length);
    }
}
/* fzgx:end fn_3_BFC */

/* fzgx:begin fn_3_14C4 */
extern void fn_3_E64(void);

void fn_3_14C4(void) {
    fn_3_E64();
}
/* fzgx:end fn_3_14C4 */

/* fzgx:begin fn_3_33A0 */
extern void fn_1_131004(void);
extern void fn_1_435C(u32 value);
extern void fn_1_426C(u32 value);
extern void fn_1_47F74(int value);

extern u32 lbl_3_data_BC[2];
extern u32 lbl_3_bss_20850;
extern u16 lbl_3_bss_F0[24];

void fn_3_33A0(void) {
    fn_1_131004();
    if (*(s32 *)lbl_3_data_BC != -1) {
        fn_1_435C(lbl_3_bss_20850);
        fn_1_426C(lbl_3_data_BC[0]);
        lbl_3_data_BC[0] = (u32)-1;
    }
    if (*(u32 *)lbl_3_bss_F0 & ((u32)1 << 31)) {
        fn_1_47F74(0x85);
        fn_1_47F74(0xa1);
    }
    *(u32 *)lbl_3_bss_F0 &= 0x02ffffff;
}
/* fzgx:end fn_3_33A0 */

/* fzgx:begin fn_3_368C */
struct fn_3_368C_lbl_3_data_0 {
    u8 pad_0[0xB8];
    u32 unk_B8;
};
struct fn_3_368C_lbl_3_bss_0 {
    u8 pad_0[0xF0];
    u32 unk_F0;
    u8 pad_F4[0x2C];
    u32 unk_120;
};

extern struct fn_3_368C_lbl_3_bss_0 lbl_3_bss_0;
extern struct fn_3_368C_lbl_3_data_0 lbl_3_data_0;
extern u32 fn_1_130EE8(u32, u32);
extern u32 fn_1_3F8C(u32, u32, u32, u32);
extern u32 fn_1_47F74(u32);
extern u32 fn_3_4218(void);
extern u32 fn_3_4C58(void);
extern u32 fn_3_7CF8(void);
extern u32 fn_3_9800(void);
extern void fn_3_255DC(void);
extern void fn_3_273F4(void);
extern void fn_3_29508(void);
extern void fn_3_29C94(void);
extern void fn_3_2AAF4(void);

u32 fn_3_368C(void) {
    struct fn_3_368C_lbl_3_data_0 *p_lbl_3_data_0;
    struct fn_3_368C_lbl_3_bss_0 *p_lbl_3_bss_0;
    u32 v0;
    u32 v1;
    u32 v2;
    u32 v3;
    u32 t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;
    p_lbl_3_bss_0 = (struct fn_3_368C_lbl_3_bss_0 *)&lbl_3_bss_0;
    p_lbl_3_data_0 = &lbl_3_data_0;
    v0 = ((u32)p_lbl_3_bss_0 + 0x20000);
    *(u8 *)((u8 *)v0 + 17316) = 0;
    v1 = *(u32 *)((u8 *)v0 + 2124);
    *(u32 *)((u8 *)v0 + 17312) = 0;
    fn_1_130EE8(v1, *(u32 *)((u8 *)v0 + 2128));
    v2 = p_lbl_3_bss_0->unk_F0;
    p_lbl_3_bss_0->unk_120 = -1;
    v3 = v2;
    if ((v2 & 0x40000000) != 0 && (s32)p_lbl_3_data_0->unk_B8 == -1) {
    t1 = fn_3_7CF8();
    v3 = t1;
    v3 = (u32)((u8 *)(u32)p_lbl_3_data_0 + 5736);
    t2 = fn_1_3F8C((u32)v3, (u32)fn_3_255DC, 0, 8);
    v3 = t2;
    p_lbl_3_data_0->unk_B8 = v3;
    } else {
    if ((v3 & 0x20000000) != 0 && (s32)p_lbl_3_data_0->unk_B8 == -1) {
    t3 = fn_3_9800();
    v3 = t3;
    v3 = (u32)((u8 *)(u32)p_lbl_3_data_0 + 5752);
    t4 = fn_1_3F8C((u32)v3, (u32)fn_3_273F4, 0, 8);
    v3 = t4;
    p_lbl_3_data_0->unk_B8 = v3;
    } else {
    if ((v3 & 0x10000000) != 0 && (s32)p_lbl_3_data_0->unk_B8 == -1) {
    t5 = fn_3_4218();
    v3 = t5;
    v3 = (u32)((u8 *)(u32)p_lbl_3_data_0 + 5768);
    t6 = fn_1_3F8C((u32)v3, (u32)fn_3_29508, 0, 8);
    v3 = t6;
    p_lbl_3_data_0->unk_B8 = v3;
    } else {
    if ((v3 & 0x8000000) == 0 || (s32)p_lbl_3_data_0->unk_B8 != -1) {
    if ((v3 & 0x4000000) != 0 && (s32)p_lbl_3_data_0->unk_B8 == -1) {
    t7 = fn_3_4C58();
    v3 = t7;
    v3 = (u32)((u8 *)(u32)p_lbl_3_data_0 + 5784);
    t8 = fn_1_3F8C((u32)v3, (u32)fn_3_29C94, 0, 8);
    v3 = t8;
    p_lbl_3_data_0->unk_B8 = v3;
    } else {
    if ((v3 & 0x1000000) != 0 && (s32)p_lbl_3_data_0->unk_B8 == -1) {
    v3 = 163;
    t9 = fn_1_47F74(v3);
    v3 = t9;
    v3 = (u32)((u8 *)(u32)p_lbl_3_data_0 + 5800);
    t10 = fn_1_3F8C((u32)v3, (u32)fn_3_2AAF4, 0, 8);
    v3 = t10;
    p_lbl_3_data_0->unk_B8 = v3;
    }
    }
    }
    }
    }
    }
    return v3;
}
/* fzgx:end fn_3_368C */

/* fzgx:begin fn_3_3E58 */
extern struct fn_3_3E58_lbl_3_bss_20850 lbl_3_bss_20850;
extern struct fn_3_3E58_lbl_3_data_0 lbl_3_data_0;
extern u32 fn_1_3F8C(u32, u32, u32, u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_47F74(u32);
extern u32 fn_1_4A00(u32, u32, u32);
extern u32 fn_1_A176C(u32, u32);
extern u32 lbl_1_bss_6EAD0;
extern u32 lbl_3_bss_120;
extern u32 lbl_3_bss_243A8;
extern void fn_3_2C164(void);

struct fn_3_3E58_lbl_3_data_0 {
    u8 pad_0[0xB8];
    u32 unk_B8;
    u8 pad_BC[0x8];
    s16 unk_C4;
};
struct fn_3_3E58_lbl_3_bss_20850 {
    u32 unk_0;
};

u32 fn_3_3E58(u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    struct fn_3_3E58_lbl_3_data_0 *p_lbl_3_data_0;
    u32 v0;
    u32 v1;
    u32 v2;
    u32 v3;
    u32 t1, t2, t3, t4, t5;
    p_lbl_3_data_0 = (struct fn_3_3E58_lbl_3_data_0 *)&lbl_3_data_0;
    fn_1_4A00(1, 15, lbl_3_bss_20850.unk_0);
    lbl_3_bss_243A8 = 0;
    p_lbl_3_data_0->unk_C4 = -1;
    t1 = fn_1_435C(lbl_3_bss_20850.unk_0);
    v0 = arg1;
    v1 = t1;
    v2 = arg2;
    v3 = arg3;
    if ((s32)p_lbl_3_data_0->unk_B8 == -1) {
    v1 = (u32)((u8 *)p_lbl_3_data_0 + 6144);
    v0 = (u32)fn_3_2C164;
    v2 = 0;
    v3 = 8;
    t2 = fn_1_3F8C((u32)v1, (u32)v0, v2, v3);
    v1 = t2;
    p_lbl_3_data_0->unk_B8 = v1;
    }
    v0 = 46;
    v1 = (u32)&lbl_1_bss_6EAD0;
    v1 = *(u32 *)((u8 *)v1 + 0);
    v1 = *(u32 *)((u8 *)v1 + 0);
    t3 = fn_1_A176C(v1, v0);
    v1 = t3;
    v0 = (u32)&lbl_3_bss_120;
    v1 = 133;
    *(u32 *)((u8 *)v0 + 0) = -1;
    t4 = fn_1_47F74(v1);
    v1 = t4;
    v1 = 161;
    t5 = fn_1_47F74(v1);
    v1 = t5;
    return v1;
}
/* fzgx:end fn_3_3E58 */

/* fzgx:begin fn_3_41B0 */
extern s32 lbl_3_data_B8;
extern s32 lbl_3_bss_20850;
extern void fn_1_435C(s32);
extern void fn_1_426C(s32);
extern void fn_1_48140(int);

void fn_3_41B0(void) {
    if (lbl_3_data_B8 != -1) {
        fn_1_435C(lbl_3_bss_20850);
        fn_1_426C(lbl_3_data_B8);
        lbl_3_data_B8 = -1;
    }
    fn_1_48140(0x85);
    fn_1_48140(0xa1);
}
/* fzgx:end fn_3_41B0 */

/* fzgx:begin fn_3_4218 */
extern void fn_3_5F28(void);
extern void fn_1_47F74(int);

void fn_3_4218(void) {
    fn_3_5F28();
    fn_1_47F74(0x4a);
    fn_1_47F74(0x54);
    fn_1_47F74(0x38);
    fn_1_47F74(0x3e);
    fn_1_47F74(0x37);
    fn_1_47F74(0x55);
    fn_1_47F74(0x30);
    fn_1_47F74(0x35);
    fn_1_47F74(0x3a);
    fn_1_47F74(0x40);
    fn_1_47F74(0x44);
    fn_1_47F74(0x50);
    fn_1_47F74(0x33);
    fn_1_47F74(0x2e);
    fn_1_47F74(0x31);
    fn_1_47F74(0x4f);
    fn_1_47F74(0x39);
    fn_1_47F74(0x3d);
    fn_1_47F74(0x4c);
    fn_1_47F74(0x3f);
    fn_1_47F74(0x48);
    fn_1_47F74(0x52);
    fn_1_47F74(0x45);
    fn_1_47F74(0x53);
    fn_1_47F74(0x3c);
    fn_1_47F74(0x56);
    fn_1_47F74(0x43);
    fn_1_47F74(0x42);
    fn_1_47F74(0x32);
    fn_1_47F74(0x2f);
    fn_1_47F74(0x34);
    fn_1_47F74(0x36);
    fn_1_47F74(0x4d);
    fn_1_47F74(0x46);
    fn_1_47F74(0x41);
    fn_1_47F74(0x51);
    fn_1_47F74(0x4e);
    fn_1_47F74(0x47);
    fn_1_47F74(0x3b);
    fn_1_47F74(0x4b);
    fn_1_47F74(0x49);
}
/* fzgx:end fn_3_4218 */

/* fzgx:begin fn_3_4A84 */
extern void fn_3_60C8(void);
extern void fn_1_48140(int);

void fn_3_4A84(void) {
    fn_3_60C8();
    fn_1_48140(0x4a);
    fn_1_48140(0x54);
    fn_1_48140(0x38);
    fn_1_48140(0x3e);
    fn_1_48140(0x37);
    fn_1_48140(0x55);
    fn_1_48140(0x30);
    fn_1_48140(0x35);
    fn_1_48140(0x3a);
    fn_1_48140(0x40);
    fn_1_48140(0x44);
    fn_1_48140(0x50);
    fn_1_48140(0x33);
    fn_1_48140(0x2e);
    fn_1_48140(0x31);
    fn_1_48140(0x4f);
    fn_1_48140(0x39);
    fn_1_48140(0x3d);
    fn_1_48140(0x4c);
    fn_1_48140(0x3f);
    fn_1_48140(0x48);
    fn_1_48140(0x52);
    fn_1_48140(0x45);
    fn_1_48140(0x53);
    fn_1_48140(0x3c);
    fn_1_48140(0x56);
    fn_1_48140(0x43);
    fn_1_48140(0x42);
    fn_1_48140(0x32);
    fn_1_48140(0x2f);
    fn_1_48140(0x34);
    fn_1_48140(0x36);
    fn_1_48140(0x4d);
    fn_1_48140(0x46);
    fn_1_48140(0x41);
    fn_1_48140(0x51);
    fn_1_48140(0x4e);
    fn_1_48140(0x47);
    fn_1_48140(0x3b);
    fn_1_48140(0x4b);
    fn_1_48140(0x49);
}
/* fzgx:end fn_3_4A84 */

/* fzgx:begin fn_3_4BEC */
struct fn_3_4BEC_lbl_3_data_B8 {
    u32 unk_0;
};

extern struct fn_3_4BEC_lbl_3_data_B8 lbl_3_data_B8;
extern u32 fn_1_426C(u32);
extern u32 fn_1_435C(u32);
extern u32 fn_3_4A84(void);
extern u32 lbl_3_bss_20850;
extern u32 lbl_3_bss_F0;

void fn_3_4BEC(u32 arg0) {
    u32 v0;
    u32 t0, t1, t2;
    v0 = arg0;
    if ((lbl_3_bss_F0 & 0x10000000) == 0) {
    t0 = fn_3_4A84();
    v0 = t0;
    if ((s32)lbl_3_data_B8.unk_0 != -1) {
    v0 = (u32)&lbl_3_bss_20850;
    v0 = *(u32 *)((u8 *)v0 + 0);
    t1 = fn_1_435C(v0);
    v0 = t1;
    v0 = (u32)&lbl_3_data_B8;
    v0 = *(u32 *)((u8 *)v0 + 0);
    t2 = fn_1_426C(v0);
    v0 = t2;
    lbl_3_data_B8.unk_0 = -1;
    }
    }
}
/* fzgx:end fn_3_4BEC */

/* fzgx:begin fn_3_5C4C */
extern u8 lbl_1_bss_970[];
extern u32 lbl_3_bss_20850;
extern void fn_1_4A00(int, int, u32);

void fn_3_5C4C(void) {
    lbl_1_bss_970[4] = 0;
    fn_1_4A00(1, 15, lbl_3_bss_20850);
}
/* fzgx:end fn_3_5C4C */

/* fzgx:begin fn_3_5C8C */
extern u8 lbl_3_data_1814[208];
extern void fn_3_3AE8(int, u8 *, int);

void fn_3_5C8C(void) {
    fn_3_3AE8(2, lbl_3_data_1814, 0x5d);
}
/* fzgx:end fn_3_5C8C */

/* fzgx:begin fn_3_5CBC */
extern f32 lbl_3_rodata_44[45];
extern void fn_8006CE1C(f32);

void fn_3_5CBC(void) {
    fn_8006CE1C(lbl_3_rodata_44[0]);
}
/* fzgx:end fn_3_5CBC */

/* fzgx:begin fn_3_61B8 */
struct fn_3_61B8_lbl_3_data_0 {
    u8 pad_0[0xB8];
    u32 unk_B8;
};
struct fn_3_61B8_lbl_3_bss_20850 {
    u32 unk_0;
};
struct fn_3_61B8_lbl_3_bss_243A8 {
    u32 unk_0;
};
struct fn_3_61B8_lbl_3_bss_120 {
    u32 unk_0;
};
struct fn_3_61B8_lbl_1_bss_6EAD0 {
    u32 unk_0;
};

extern struct fn_3_61B8_lbl_1_bss_6EAD0 lbl_1_bss_6EAD0;
extern struct fn_3_61B8_lbl_3_bss_120 lbl_3_bss_120;
extern struct fn_3_61B8_lbl_3_bss_20850 lbl_3_bss_20850;
extern struct fn_3_61B8_lbl_3_bss_243A8 lbl_3_bss_243A8;
extern struct fn_3_61B8_lbl_3_data_0 lbl_3_data_0;
extern u32 fn_1_15BB34(u32);
extern u32 fn_1_3F8C(u32, u32, u32, u32);
extern u32 fn_1_47F74(u32);
extern u32 fn_1_4A00(u32, u32, u32);
extern u32 fn_1_A176C(u32, u32);
extern u32 fn_8006FDEC(void);
extern void fn_3_2AAF4(void);

void fn_3_61B8(void) {
    struct fn_3_61B8_lbl_3_data_0 *p_lbl_3_data_0;
    u32 v0;
    u32 v1;
    u32 v2;
    u32 v3;
    u32 t0, t1;
    p_lbl_3_data_0 = (struct fn_3_61B8_lbl_3_data_0 *)&lbl_3_data_0;
    if ((s32)p_lbl_3_data_0->unk_B8 == -1) {
    t0 = fn_8006FDEC();
    v1 = t0;
    v1 = (u32)((u8 *)(u32)p_lbl_3_data_0 + 5800);
    v0 = (u32)fn_3_2AAF4;
    v2 = 0;
    v3 = 8;
    t1 = fn_1_3F8C((u32)v1, (u32)v0, v2, v3);
    v1 = t1;
    p_lbl_3_data_0->unk_B8 = v1;
    }
    fn_1_4A00(1, 15, lbl_3_bss_20850.unk_0);
    lbl_3_bss_243A8.unk_0 = 0;
    lbl_3_bss_120.unk_0 = -1;
    fn_1_47F74(163);
    fn_1_A176C(*(u32 *)((u8 *)lbl_1_bss_6EAD0.unk_0 + 0), 15);
    fn_1_15BB34((u32)((u8 *)(u32)p_lbl_3_data_0 + 4444));
}
/* fzgx:end fn_3_61B8 */

/* fzgx:begin fn_3_6540 */
extern s16 lbl_1_bss_96A;
extern s32 lbl_3_data_B8;
extern u32 lbl_3_bss_20850;
extern void fn_1_435C(u32);
extern void fn_1_426C(s32);
extern void fn_1_48140(int);

void fn_3_6540(void) {
    if (lbl_1_bss_96A != 0x5d) {
        if (lbl_3_data_B8 != -1) {
            fn_1_435C(lbl_3_bss_20850);
            fn_1_426C(lbl_3_data_B8);
            lbl_3_data_B8 = -1;
        }
        fn_1_48140(0xa3);
    }
}
/* fzgx:end fn_3_6540 */

/* fzgx:begin fn_3_65B0 */
extern u8 jumptable_3_data_18E4[40];

extern void fn_1_F7D6C(void);
extern void fn_1_F7E24(void);
extern void fn_1_F7D18(void);
extern void fn_1_F7DC0(void);
extern s32 fn_1_F8A38(s32);
extern void fn_1_F8AD4(s32);
extern void fn_1_F8A58(s32);
extern void fn_1_F83F0(s32);
extern u8 fn_1_F8C50(s32);
extern void fn_1_F8C74(s32);
extern void fn_1_F8C00(s32);

void fn_3_65B0(u32 value) {
    switch ((u16)value) {
    case 0:
        fn_1_F7D6C();
        fn_1_F7E24();
        break;
    case 1:
        fn_1_F7D18();
        fn_1_F7DC0();
        break;
    case 2:
        if (fn_1_F8A38(0) == 0) {
            fn_1_F8AD4(0);
        }
        fn_1_F8A58(0);
        if (fn_1_F8A38(1) == 0) {
            fn_1_F8AD4(1);
        }
        fn_1_F8A58(1);
        if (fn_1_F8A38(2) == 0) {
            fn_1_F8AD4(2);
        }
        fn_1_F8A58(2);
        if (fn_1_F8A38(3) == 0) {
            fn_1_F8AD4(3);
        }
        fn_1_F8A58(3);
        if (fn_1_F8A38(4) == 0) {
            fn_1_F8AD4(4);
        }
        fn_1_F8A58(4);
        if (fn_1_F8A38(5) == 0) {
            fn_1_F8AD4(5);
        }
        fn_1_F8A58(5);
        break;
    case 3:
        fn_1_F83F0(0x11);
        fn_1_F83F0(0x26);
        fn_1_F83F0(0x34);
        break;
    case 4:
        fn_1_F83F0(0x16);
        fn_1_F83F0(0x30);
        fn_1_F83F0(0x3e);
        break;
    case 5:
        fn_1_F83F0(8);
        fn_1_F83F0(0x2c);
        fn_1_F83F0(0x49);
        break;
    case 6:
        fn_1_F83F0(0xb);
        fn_1_F83F0(0x2e);
        fn_1_F83F0(0x39);
        break;
    case 7:
        fn_1_F83F0(1);
        fn_1_F83F0(0x1a);
        fn_1_F83F0(0x46);
        break;
    case 8:
        if (fn_1_F8C50(1) == 0) {
            fn_1_F8C74(1);
        }
        fn_1_F8C00(1);
        break;
    case 9:
        if (fn_1_F8C50(0) == 0) {
            fn_1_F8C74(0);
        }
        fn_1_F8C00(0);
        break;
    }
}
/* fzgx:end fn_3_65B0 */

/* fzgx:begin fn_3_7688 */
extern s32 lbl_3_bss_8;
extern s32 lbl_3_bss_C[3];
extern s32 lbl_3_data_11D8;
extern u8 lbl_3_bss_6DE20[64832];
extern s32 lbl_3_data_B8;
extern s32 lbl_3_bss_20850;

extern void fn_1_F8580(void);
extern void fn_1_12A2B8(int);
extern void fn_1_12A2D0(int);
extern void fn_1_14DC68(void *, int);
extern void fn_1_12A734(int);
extern void fn_1_435C(int);
extern void fn_1_426C(int);
extern void fn_1_48140(int);

void fn_3_7688(void) {
    if (lbl_3_bss_8 != 0 && lbl_3_bss_C[0] != 0) {
        fn_1_F8580();
    }

    if (lbl_3_data_11D8 != -1) {
        fn_1_12A2B8(1);
        fn_1_12A2D0(lbl_3_data_11D8);
    }

    fn_1_14DC68(lbl_3_bss_6DE20, 25);
    fn_1_12A2B8(0);

    if (lbl_3_data_11D8 != -1) {
        fn_1_12A734(lbl_3_data_11D8);
    }

    lbl_3_data_11D8 = -1;

    if (lbl_3_data_B8 != -1) {
        fn_1_435C(lbl_3_bss_20850);
        fn_1_426C(lbl_3_data_B8);
        lbl_3_data_B8 = -1;
    }

    fn_1_48140(163);
}
/* fzgx:end fn_3_7688 */

/* fzgx:begin fn_3_7770 */
extern u32 lbl_3_bss_20850;
extern s16 lbl_3_data_A8[6];
extern void fn_1_4A00(s32, s32, u32);

void fn_3_7770(void) {
    fn_1_4A00(1, 0xf, lbl_3_bss_20850);
    lbl_3_data_A8[0] = (u16)-1;
}
/* fzgx:end fn_3_7770 */

/* fzgx:begin fn_3_7864 */
// fn_3_7864: empty in retail (single blr).
void fn_3_7864(void) {
}
/* fzgx:end fn_3_7864 */

/* fzgx:begin fn_3_7868 */
// fn_3_7868: empty in retail (single blr).
void fn_3_7868(void) {
}
/* fzgx:end fn_3_7868 */

/* fzgx:begin fn_3_786C */
// fn_3_786C: empty in retail (single blr).
void fn_3_786C(void) {
}
/* fzgx:end fn_3_786C */

/* fzgx:begin fn_3_7870 */
extern s32 lbl_3_data_B8;
extern u32 lbl_3_bss_20850;
extern void fn_1_435C(u32);
extern void fn_1_426C(s32);

void fn_3_7870(void) {
    if (lbl_3_data_B8 != -1) {
        fn_1_435C(lbl_3_bss_20850);
        fn_1_426C(lbl_3_data_B8);
        lbl_3_data_B8 = -1;
    }
}
/* fzgx:end fn_3_7870 */

/* fzgx:begin fn_3_78C8 */
typedef struct CustomizeEntry {
    u8 pad[0x20];
    s16 count;
    s16 values[0x0a];
} CustomizeEntry;

extern CustomizeEntry lbl_3_bss_20[3];
extern void fn_80008BEC(void *, s32, u32);
extern s32 fn_1_F8334(s32);
extern s32 fn_1_14D6D8(s32);
extern s16 fn_1_14F344(s32);
extern s32 fn_1_F809C(s32);

void fn_3_78C8(s32 enabled) {
    s32 i;

    fn_80008BEC((u8 *)lbl_3_bss_20 + 0x20, 0, 0xa2);
    i = 0;
    while ((s16)i < 0x4b) {
        if (enabled != 0) {
            if (fn_1_F8334(i) != 0 &&
                (fn_1_14D6D8(i) & 0x40000000) == 0) {
                s16 index = fn_1_14F344(i);
                CustomizeEntry *entry = &lbl_3_bss_20[index];

                entry->values[entry->count++] = (s16)i;
            }
        } else if (fn_1_F809C(i) != 0) {
            s16 index = fn_1_14F344(i);
            CustomizeEntry *entry = &lbl_3_bss_20[index];

            entry->values[entry->count++] = (s16)i;
        }
        i++;
    }
    lbl_3_bss_20[0].values[lbl_3_bss_20[0].count] = -1;
    lbl_3_bss_20[1].values[lbl_3_bss_20[1].count] = -1;
    lbl_3_bss_20[2].values[lbl_3_bss_20[2].count] = -1;
}
/* fzgx:end fn_3_78C8 */

/* fzgx:begin fn_3_7A08 */
extern s16 lbl_3_bss_20[104];

void fn_3_7A08(s16 *arg0, s16 *arg1, int arg2) {
    *arg0 = -lbl_3_bss_20[98];
    *arg1 = *arg0 + arg2 - 1;
}
/* fzgx:end fn_3_7A08 */

/* fzgx:begin fn_3_7A30 */
extern void fn_1_47F74(int);

void fn_3_7A30(void) {
    fn_1_47F74(0x65);
    fn_1_47F74(0x6d);
    fn_1_47F74(0x80);
    fn_1_47F74(0x58);
    fn_1_47F74(0x69);
    fn_1_47F74(0x75);
    fn_1_47F74(0x64);
    fn_1_47F74(0x74);
    fn_1_47F74(0x63);
    fn_1_47F74(0x6c);
    fn_1_47F74(0x5a);
    fn_1_47F74(0x6e);
    fn_1_47F74(0x82);
    fn_1_47F74(0x6b);
    fn_1_47F74(0x79);
    fn_1_47F74(0x68);
    fn_1_47F74(0x6a);
    fn_1_47F74(0x59);
    fn_1_47F74(0x6f);
    fn_1_47F74(0x57);
    fn_1_47F74(0x72);
    fn_1_47F74(0x7e);
    fn_1_47F74(0x73);
    fn_1_47F74(0x71);
    fn_1_47F74(0x5b);
    fn_1_47F74(0x81);
    fn_1_47F74(0x62);
    fn_1_47F74(0x7a);
    fn_1_47F74(0x5d);
    fn_1_47F74(0x7c);
    fn_1_47F74(0x5c);
    fn_1_47F74(0x61);
    fn_1_47F74(0x60);
    fn_1_47F74(0x5e);
    fn_1_47F74(0x7f);
    fn_1_47F74(0x5f);
    fn_1_47F74(0x77);
    fn_1_47F74(0x70);
    fn_1_47F74(0x76);
    fn_1_47F74(0x78);
    fn_1_47F74(0x7d);
}
/* fzgx:end fn_3_7A30 */

/* fzgx:begin fn_3_7B94 */
extern void fn_1_48140(int);

void fn_3_7B94(void) {
    fn_1_48140(0x65);
    fn_1_48140(0x6d);
    fn_1_48140(0x80);
    fn_1_48140(0x58);
    fn_1_48140(0x69);
    fn_1_48140(0x75);
    fn_1_48140(0x64);
    fn_1_48140(0x74);
    fn_1_48140(0x63);
    fn_1_48140(0x6c);
    fn_1_48140(0x5a);
    fn_1_48140(0x6e);
    fn_1_48140(0x82);
    fn_1_48140(0x6b);
    fn_1_48140(0x79);
    fn_1_48140(0x68);
    fn_1_48140(0x6a);
    fn_1_48140(0x59);
    fn_1_48140(0x6f);
    fn_1_48140(0x57);
    fn_1_48140(0x72);
    fn_1_48140(0x7e);
    fn_1_48140(0x73);
    fn_1_48140(0x71);
    fn_1_48140(0x5b);
    fn_1_48140(0x81);
    fn_1_48140(0x62);
    fn_1_48140(0x7a);
    fn_1_48140(0x5d);
    fn_1_48140(0x7c);
    fn_1_48140(0x5c);
    fn_1_48140(0x61);
    fn_1_48140(0x60);
    fn_1_48140(0x5e);
    fn_1_48140(0x7f);
    fn_1_48140(0x5f);
    fn_1_48140(0x77);
    fn_1_48140(0x70);
    fn_1_48140(0x76);
    fn_1_48140(0x78);
    fn_1_48140(0x7d);
}
/* fzgx:end fn_3_7B94 */

/* fzgx:begin fn_3_968C */
struct fn_3_968C_lbl_3_data_11D8 {
    u32 unk_0;
};

extern struct fn_3_968C_lbl_3_data_11D8 lbl_3_data_11D8;
extern u32 fn_1_12A2B8(u32);
extern u32 fn_1_12A2D0(u32);
extern u32 fn_1_12A734(u32);
extern u32 fn_1_14DC68(u32, u32);
extern u32 fn_3_7B94(void);
extern u32 lbl_3_bss_6DE20;

void fn_3_968C(u32 arg0) {
    u32 v0;
    u32 v1;
    u32 t0, t1;
    v0 = arg0;
    if ((s32)lbl_3_data_11D8.unk_0 != -1) {
    v0 = 1;
    t0 = fn_1_12A2B8(v0);
    v0 = t0;
    v0 = (u32)&lbl_3_data_11D8;
    v0 = *(u32 *)((u8 *)v0 + 0);
    t1 = fn_1_12A2D0(v0);
    v0 = t1;
    }
    fn_1_14DC68((u32)&lbl_3_bss_6DE20, 25);
    fn_1_12A2B8(0);
    v1 = lbl_3_data_11D8.unk_0;
    if ((s32)v1 != -1) {
    fn_1_12A734(v1);
    }
    lbl_3_data_11D8.unk_0 = -1;
    fn_3_7B94();
}
/* fzgx:end fn_3_968C */

/* fzgx:begin fn_3_9710 */
struct fn_3_9710_lbl_3_data_11D8 {
    u32 unk_0;
};
struct fn_3_9710_lbl_3_data_B8 {
    u32 unk_0;
};

extern struct fn_3_9710_lbl_3_data_11D8 lbl_3_data_11D8;
extern struct fn_3_9710_lbl_3_data_B8 lbl_3_data_B8;
extern u32 fn_1_12A734(u32);
extern u32 fn_1_426C(u32);
extern u32 fn_1_435C(u32);
extern u32 lbl_3_bss_20850;
extern u32 lbl_3_bss_6DE20;
extern u32 lbl_3_bss_F0;
extern void fn_1_12A2B8(u32);
extern void fn_1_12A2D0(s32);
extern void fn_1_14DC68(void *, int);
extern void fn_1_151BDC(u32);
extern void fn_1_FE5C4(u8, u32, u32, u8);
extern void fn_3_7B94(void);
extern void fn_3_BC60(void);

void fn_3_9710(u32 arg0, u32 arg1) {
    u32 v0;
    u32 v1;
    u32 t4, t6, t7;
    v1 = arg1;
    if ((lbl_3_bss_F0 & 0x40000000) == 0) {
    if ((s32)lbl_3_data_11D8.unk_0 != -1) {
    v0 = 1;
    fn_1_12A2B8(v0);
    v0 = (u32)&lbl_3_data_11D8;
    v0 = *(u32 *)((u8 *)v0 + 0);
    fn_1_12A2D0(v0);
    }
    v1 = 25;
    v0 = (u32)&lbl_3_bss_6DE20;
    fn_1_14DC68((void *)(u32)v0, v1);
    v0 = 0;
    fn_1_12A2B8(v0);
    v0 = (u32)&lbl_3_data_11D8;
    v0 = *(u32 *)((u8 *)v0 + 0);
    if ((s32)v0 != -1) {
    t4 = fn_1_12A734(v0);
    v0 = t4;
    }
    lbl_3_data_11D8.unk_0 = -1;
    fn_3_7B94();
    if ((s32)lbl_3_data_B8.unk_0 != -1) {
    v0 = (u32)&lbl_3_bss_20850;
    v0 = *(u32 *)((u8 *)v0 + 0);
    t6 = fn_1_435C(v0);
    v0 = t6;
    v0 = (u32)&lbl_3_data_B8;
    v0 = *(u32 *)((u8 *)v0 + 0);
    t7 = fn_1_426C(v0);
    v0 = t7;
    lbl_3_data_B8.unk_0 = -1;
    }
    v0 = 0;
    fn_1_151BDC(v0);
    }
    fn_3_BC60();
    fn_1_FE5C4(0, 0, 0, 0);
}
/* fzgx:end fn_3_9710 */
