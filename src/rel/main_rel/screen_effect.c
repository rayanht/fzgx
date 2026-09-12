#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/screen_effect.h"

extern u32 lbl_1_bss_6C8DC[2];
extern u32 lbl_801A6410;
extern void fn_1_46B4(u32 arg0, u32 arg1, void *arg2, u32 arg3);
extern void fn_1_727BC(u32 arg0, u32 arg1, void *arg2);
extern void fn_1_76A94(void *arg0, u32 arg1);
extern void fn_1_76DBC(void);
extern void fn_1_4E500(void);
extern void fn_1_4E638(int);
extern void fn_1_4E6F4(void);
extern void fn_80073778(void *arg0, int arg1);
extern s32 fn_1_A5D9C(void);
extern const f32 lbl_1_rodata_31AC;
extern u32 fn_80008E84(u32 arg);
extern void fn_1_77238(void);
extern void fn_1_772E0(void);
extern void fn_1_77384(void *arg);
extern void fn_80072864(int arg0);
extern void fn_800745A4(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5);
extern void fn_80074660(int arg0);
extern void fn_80073678(int arg0);
extern void fn_80073898(int arg0);
extern void fn_80074788(int arg0);
extern void fn_800738E0(int arg0, int arg1, int arg2);
extern void fn_80073D60(int arg0, int arg1, int arg2, int arg3, int arg4);
extern void fn_800734A8(int arg0, int arg1, int arg2, int arg3);
extern void fn_80072EDC(int arg0, int arg1);
extern f32 lbl_1_rodata_31B0[10];
extern const f64 lbl_1_rodata_31A0;
extern void lbl_8006D784(f32 *arg);
extern void fn_80073A58(int arg0, f32 *arg1, int arg2);
extern void fn_800739E0(int arg0, int arg1, int arg2);
extern void GXLoadTexMtxImm(f32 *arg0, int arg1, int arg2);
extern void fn_8006FDEC(void);
extern void fn_8006FEFC(void);
extern void fn_8006FD1C(void);
extern void fn_1_79810(void);
extern void fn_1_79948(void);
extern void fn_1_791B0(void);
extern void fn_1_9A1E8(void);
extern void fn_1_9A864(void);
extern u8 fn_1_7B074(void);
extern void fn_80071718(void *arg);
extern void fn_800711A8(void *arg);
extern void fn_1_14CB4(void);
extern void fn_1_FA84(void);
extern const f32 lbl_1_rodata_32CC;
extern void fn_1_79C88(void *arg0, s32 arg1, f32 arg2, s32 arg3);
extern void lbl_8006DBAC(void *arg0);
extern void lbl_8006E1B0(void *arg0, void *arg1);
extern void sprintf(char *dst, const char *format, ...);
extern void fn_1_465D0(char *text, int arg);
extern void fn_1_14D5C(void *object, int arg);
extern void fn_1_46EA8(int value);
extern void fn_1_12620(void *object);
extern void fn_1_46DC4(void *obj);

extern void fn_1_727BC();
extern void fn_8006FDEC(void);
extern void fn_80071718(void *);
extern void fn_800711A8(void *);
extern u32 fn_8003526C(u32, u32);
extern u32 fn_80074300(u32, u32, u32, u32);
extern u32 fn_80074438(u32, u32, u32, u32);

/* fzgx:begin fn_1_72648 */
void fn_1_72648(void) {
    if (lbl_1_bss_6C8DC[0] != 0) {
        fn_1_46B4(lbl_801A6410, lbl_1_bss_6C8DC[0], lbl_1_data_1DAC0, 0xf9);
        lbl_1_bss_6C8DC[0] = 0;
    }
}
/* fzgx:end fn_1_72648 */

/* fzgx:begin fn_1_7269C */
typedef struct {
    u8 pad_0[0xa0];
    u32 unk_A0;
    u8 pad_A4[0x24];
    u32 unk_C8;
} fn_1_7269C_ScreenEffectEntry;

void fn_1_7269C(u32 arg0, u32 arg1, void *arg2) {
    fn_1_7269C_ScreenEffectEntry *object;

    object = (fn_1_7269C_ScreenEffectEntry *)((u8 *)&lbl_1_bss_6C8EC + (arg0 & 0xff) * 0x10c);
    fn_1_727BC(arg0, arg1, arg2);
    ((fn_1_7269C_ScreenEffectEntry *)((u8 *)object + (arg1 & 0xff) * 4))->unk_A0 = (u32)arg2;
    ((fn_1_7269C_ScreenEffectEntry *)((u8 *)object + (arg1 & 0xff) * 4))->unk_C8 = 1;
    fn_1_76A94(object, arg1);
    fn_1_76DBC();
}
/* fzgx:end fn_1_7269C */

/* fzgx:begin fn_1_72714 */
// Initialize the effect system and return the requested slot subregion.
void *fn_1_72714(u8 slot, u32 subregion) {
    Obj_1_bss_6C8EC *entry;
    u32 offset;

    fn_1_727BC();
    entry = (Obj_1_bss_6C8EC *)((u8 *)&lbl_1_bss_6C8EC + slot * 0x10c);
    offset = (subregion & 0xff) * 0x20;
    return (u8 *)entry + offset;
}
/* fzgx:end fn_1_72714 */

/* fzgx:begin fn_1_72768 */
// Initialize the selected screen-effect slot with its requested value.
void fn_1_72768(u32 arg0, u32 arg1) {
    Obj_1_bss_6C8EC *entry;
    u32 index;

    fn_1_727BC(arg0, 0);
    index = (u8)arg0;
    entry = (Obj_1_bss_6C8EC *)((u8 *)&lbl_1_bss_6C8EC + index * 0x10c);
    entry->unk_104 = arg1;
}
/* fzgx:end fn_1_72768 */

/* fzgx:begin fn_1_72848 */
extern void fn_1_76650(void *);

void fn_1_72848(void) {
    u8 i;

    // Reset each screen-effect entry before clearing the active-effect flag.
    for (i = 0; i < 8; i++) {
        fn_1_76650((u8 *)&lbl_1_bss_6C8EC + i * 0x10c);
    }
    lbl_1_bss_6D14C.unk_0 = 0;
}
/* fzgx:end fn_1_72848 */

/* fzgx:begin fn_1_728B0 */
typedef struct {
    u8 pad_0[0xdc];
    s32 unk_DC;
    s32 unk_E0;
    u8 pad_E4[0x20];
    void (*unk_104)(void *);
} fn_1_728B0_ScreenEffectEntry;

extern void fn_1_72980(fn_1_728B0_ScreenEffectEntry *);
extern void *fn_1_729F8(fn_1_728B0_ScreenEffectEntry *);

void fn_1_728B0(void) {
    u8 i;
    u8 *base;
    fn_1_728B0_ScreenEffectEntry *obj;
    void *result;

    if (lbl_1_bss_6D14C.unk_0 == 0) {
        fn_1_4E500();
        fn_1_4E638(0);
        base = (u8 *)&lbl_1_bss_6C8EC;
        for (i = 0; i < 8; i++) {
            obj = (fn_1_728B0_ScreenEffectEntry *)(base + i * 0x10c);
            if (obj->unk_DC != 0) {
                if (obj->unk_DC == 0xe && obj->unk_E0 == 0) {
                    obj->unk_E0 = obj->unk_E0 + 1;
                } else {
                    fn_1_72980(obj);
                    result = fn_1_729F8(obj);
                    if (obj->unk_104 != 0) {
                        obj->unk_104(result);
                    }
                }
            }
        }
        fn_1_4E6F4();
    }
}
/* fzgx:end fn_1_728B0 */

/* fzgx:begin fn_1_72980 */
typedef struct {
    u8 pad_0[0xdc];
    u32 unk_dc;
} Fn_1_72980_Obj;

void fn_1_72980(Fn_1_72980_Obj *arg0) {
    int index;
    u8 *entry;
    int i;

    entry = (u8 *)arg0;
    i = 0;
    index = 0;
    while (i < ((u8 *)&lbl_1_data_1D9B8)[arg0->unk_dc * 6 + 5]) {
        fn_80073778(entry, index);
        index++;
        entry += 0x20;
        i++;
    }
}
/* fzgx:end fn_1_72980 */

/* fzgx:begin fn_1_729F8 noprologue */
#include "types.h"

struct fn_1_729F8_Arg0 {
    u8 pad_0[0xDC];
    s32 unk_DC;
    s32 unk_E0;
    f32 unk_E4;
    u16 unk_E8;
    u16 unk_EA;
    s16 unk_EC;
    s16 unk_EE;
    u16 unk_F0;
    u16 unk_F2;
    u32 unk_F4;
    u16 unk_F8;
    u16 unk_FA;
    u16 unk_FC;
    u16 unk_FE;
    u16 unk_100;
    u16 unk_102;
    u32 unk_104;
};

struct fn_1_729F8_Bss {
    u8 pad_0[0x8D0];
    u32 unk_8D0;
    u16 unk_8D4;
    u16 unk_8D6;
    u16 unk_8D8;
    u8 unk_8DA;
};

struct fn_1_729F8_Data {
    u8 pad_0[0x150];
    u8 unk_150[4];
    f32 unk_154;
    f32 unk_158;
};

struct fn_1_729F8_RoData {
    u32 w0;
    u32 w1;
    u32 w2;
    u32 w3;
    u32 w4;
    u32 w5;
    u32 w6;
    u32 w7;
};

extern struct fn_1_729F8_Bss lbl_1_bss_6C8D8;
u8 lbl_1_data_1D960[88] = {0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x11,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x39,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x3A,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x13,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x27};
u8 lbl_1_data_1D9B8[248] = {0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x01,0x06,0x00,0x00,0x00,0x00,0x01,0x06,0x00,0x00,0x00,0x00,0x01,0x06,0x00,0x00,0x00,0x00,0x01,0x06,0x00,0x00,0x00,0x00,0x01,0x06,0x00,0x00,0x00,0x00,0x01,0x06,0x00,0x00,0x00,0x00,0x01,0x06,0x06,0x00,0x00,0x00,0x02,0x06,0x06,0x00,0x00,0x00,0x02,0x06,0x06,0x00,0x00,0x00,0x02,0x06,0x06,0x00,0x00,0x00,0x02,0x00,0x01,0x06,0x00,0x00,0x03,0x00,0x01,0x06,0x00,0x00,0x03,0x00,0x01,0x06,0x00,0x00,0x03,0x00,0x01,0x06,0x03,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x01,0x04,0x06,0x00,0x00,0x00,0x02,0x04,0x06,0x00,0x00,0x00,0x02,0x04,0x06,0x00,0x00,0x00,0x02,0x04,0x06,0x00,0x00,0x00,0x02,0x04,0x06,0x00,0x00,0x00,0x02,0x04,0x06,0x00,0x00,0x00,0x02,0x04,0x06,0x00,0x00,0x00,0x02,0x04,0x06,0x00,0x00,0x00,0x02,0x06,0x06,0x00,0x00,0x00,0x02,0x06,0x03,0x00,0x00,0x00,0x02,0x06,0x03,0x00,0x00,0x00,0x02,0x05,0x00,0x00,0x00,0x00,0x01,0x06,0x00,0x00,0x00,0x00,0x01,0x05,0x04,0x00,0x00,0x00,0x02,0x09,0x00,0x00,0x00,0x00,0x01,0x04,0x08,0x00,0x00,0x00,0x02,0x04,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x06,0x00,0x00,0x03,0x06,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x07,0x00,0x00,0x03,0x04,0x00,0x00,0x00,0x00,0x01,0x30,0x50,0x60,0x20,0x38,0x62,0x34,0x20,0x60,0x60,0x50,0x40,0x60,0x50,0x50,0x30,0x70,0x50,0x40,0x20};
u8 lbl_1_data_1D9B8__fzgx_offset_F8[4] = {0x30,0x50,0x60,0x20};
f32 lbl_1_data_1D9B8__fzgx_offset_FC = 1.0f;
f32 lbl_1_data_1D9B8__fzgx_offset_100 = 1.0f;
u8 lbl_1_data_1D9B8__fzgx_offset_104[4] = {0x08,0x00,0x00,0x00};
u8 lbl_1_data_1DAC0[68] = {0x73,0x63,0x72,0x65,0x65,0x6E,0x5F,0x65,0x66,0x66,0x65,0x63,0x74,0x2E,0x63,0x00,0x43,0x61,0x6E,0x27,0x74,0x20,0x44,0x6F,0x75,0x62,0x6C,0x65,0x20,0x43,0x72,0x65,0x61,0x74,0x65,0x20,0x48,0x65,0x61,0x70,0x0A,0x00,0x00,0x00,0x45,0x72,0x72,0x6F,0x72,0x21,0x20,0x3A,0x20,0x57,0x72,0x6F,0x6E,0x67,0x20,0x56,0x61,0x6C,0x75,0x65,0x2E,0x00,0x00,0x00};
extern f32 *lbl_801A6D00;
extern u32 lbl_801A66A0;



extern void fn_1_75D84(void *, void *, void *);
extern void fn_1_761B8(void *, u32);
extern void fn_1_76C60(void *);
extern void fn_1_76EB8(void);
extern void fn_1_77200(void);
extern u32 fn_1_77C5C(void *, void *, void *);
extern u32 fn_1_4E220(void *, u32, u32, u32, u32);
extern void lbl_8006D758(void);
extern void lbl_8006D784(void *);
extern void lbl_8006E1B0(void *, void *);
extern void mathutil_mtxA_rotate_z(s32);
extern void fn_800371F8(u32, void *);
extern void fn_8003726C(u32, void *);
extern void fn_800720B0(u32);
extern void fn_8007245C(u32);
extern void fn_800724C8(void);
extern void fn_80072808(void);
extern void fn_80072864(u32);
extern void fn_800728A8(s32, s32, s32, s32);
extern void fn_800729B0(s32, s32, s32, s32, s32);
extern void fn_80072AB0(s32, s32, s32);
extern void fn_80072C24(s32, s32, s32, s32, s32);
extern u32 fn_80072CC4(u32, u32, u32, u32, u32);
extern void fn_80072D64(s32, s32, s32, s32, u8, s32);
extern void fn_80072E20(s32, s32, s32, s32, u8, s32);
extern void fn_80072EDC(u32, u32);
extern void fn_800734A8(u32, s32, s32, s32);
extern void fn_800735C8(s32, s32);
extern void fn_80073620(s32, s32);
extern void fn_80073678(u32);
extern void fn_800736C0(u32, void *);
extern void fn_80073778(void *, s32);
extern void fn_80073898(u32);
extern void fn_800738E0(s32, s32, s32);
extern void fn_800739E0(s32, s32, s32);
extern void fn_80073A58(s32, void *, s8);
extern void fn_80073C6C(s32);
extern void fn_80073D60(u32, u32, u32, u32, u32);
extern void fn_800745A4(u32, s32, s32, u32, u32, u32);
extern void fn_80074660(u32);
extern void fn_80074788(u32);
extern void fn_800747D0(u32, u32, s32, s32, u32, s32, s32);
extern void fn_80074918(u8, s32, u8);
extern void GXLoadTexMtxImm(void *, u32, u32);
extern void GXSetAlphaCompare(s32, s32, s32, s32, s32);

union Color { struct {u8 r, g, b, a;} bytes; u32 word; };
#pragma fp_contract off

/* The four vec3 rows and the colour/scratch words are members of a single
   aggregate each in the original; splitting them changes the stack layout. */
#define v168 vbuf
#define v174 (vbuf + 3)
#define v180 (vbuf + 6)
#define v18C (vbuf + 9)
#define w88 color88

void fn_1_729F8(struct fn_1_729F8_Arg0 *arg0)
{
    struct fn_1_729F8_Bss *p_bss;
    f32 vbuf[12];
    f32 m138[12];
    f32 m108[12];
    f32 mD8[12];
    f32 aC0[6];
    f32 aA8[6];
    f32 a90[6];
    union Color color84 = {{0xFF,0xFF,0xFF,0xFF}};
    union Color color80;
    u32 color7c;
    u32 s78;
    u32 s74;
    u32 s70;
    u32 s6C;
    u32 s68;
    u32 s64;
    u32 s60;
    u32 s5C;
    u32 s58;
    u32 s54;
    u32 s50;
    u32 s4C;
    u32 s48;
    u32 s44;
    u32 s40;
    u32 s3C;
    u32 s38;
    u32 s34;
    u32 s30;
    u32 s2C;
    u32 s28;
    u32 s24;
    u32 s20;
    s32 mode;
    s32 flag;
    s32 i;
    s32 id;

    f32 w;


    mode = 0;
    flag = 0;
    i = 0;
    id = 0;

    p_bss = &lbl_1_bss_6C8D8;

    { const union Color initial = {{0xFF,0xFF,0xFF,0xFF}}; color80 = initial; }
    v18C[0] = 0.0f;
    v168[0] = 0.0f;
    w = (f32)(s32)arg0->unk_EC;
    v174[1] = 0.0f;
    v168[1] = 0.0f;
    v180[0] = w;
    v174[0] = w;
    w = (f32)(s32)arg0->unk_EE;
    v18C[1] = w;
    v180[1] = w;

    switch (arg0->unk_DC) {
    case 0:
    case 37:
        break;
    case 3:
        mode = 4;
        goto common012; /* MF: three D-C entry points share this tail in retail. */
    case 2:
        mode = 2;
        goto common012; /* MF: same shared tail. */
    case 1:
        mode = 1;
    common012:
        color84.bytes.a = (u8)(s32)(255.0f - (f32)(s32)(arg0->unk_E0 * 255) / 40.0f);
        color7c = color84.word;
        fn_800371F8(1, (&color7c));
        fn_1_761B8(arg0, mode);
        fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        break;

    case 4:
        if (arg0->unk_E0 == 0)
            arg0->unk_E4 = 1.0f;
        v168[0] = v18C[0] = -(0.5f * (f32)(s32)arg0->unk_EC) * arg0->unk_E4;
        v174[0] = v180[0] = (0.5f * (f32)(s32)arg0->unk_EC) * arg0->unk_E4;
        v168[1] = v174[1] = -(0.5f * (f32)(s32)arg0->unk_EE) * arg0->unk_E4;
        v180[1] = v18C[1] = (0.5f * (f32)(s32)arg0->unk_EE) * arg0->unk_E4;
        lbl_8006D758();
        v168[0] = v168[0] + 0.5f * (f32)(s32)arg0->unk_EC;
        v174[0] = v174[0] + 0.5f * (f32)(s32)arg0->unk_EC;
        v180[0] = v180[0] + 0.5f * (f32)(s32)arg0->unk_EC;
        v18C[0] = v18C[0] + 0.5f * (f32)(s32)arg0->unk_EC;
        v168[1] = v168[1] + 0.5f * (f32)(s32)arg0->unk_EE;
        v174[1] = v174[1] + 0.5f * (f32)(s32)arg0->unk_EE;
        v180[1] = v180[1] + 0.5f * (f32)(s32)arg0->unk_EE;
        v18C[1] = v18C[1] + 0.5f * (f32)(s32)arg0->unk_EE;
        arg0->unk_E0++;
        arg0->unk_E4 -= 0.025f;
        if (arg0->unk_E4 < 0.025f)
            fn_1_76C60(arg0);
        s78 = color84.word;
        fn_800371F8(1, &s78);
        fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        break;

    case 5:
        if (arg0->unk_E0 == 0)
            arg0->unk_E4 = 1.0f;
        v168[0] = v18C[0] = -(0.5f * (f32)(s32)arg0->unk_EC) * arg0->unk_E4;
        v174[0] = v180[0] = (0.5f * (f32)(s32)arg0->unk_EC) * arg0->unk_E4;
        v168[1] = v174[1] = -(0.5f * (f32)(s32)arg0->unk_EE) * arg0->unk_E4;
        v180[1] = v18C[1] = (0.5f * (f32)(s32)arg0->unk_EE) * arg0->unk_E4;
        lbl_8006D758();
        mathutil_mtxA_rotate_z((s32)(-(40.96f * (f32)(s32)(arg0->unk_E0 * arg0->unk_E0))));
        lbl_8006E1B0(v168, v168);
        lbl_8006E1B0(v174, v174);
        lbl_8006E1B0(v180, v180);
        lbl_8006E1B0(v18C, v18C);
        v168[0] = v168[0] + 0.5f * (f32)(s32)arg0->unk_EC;
        v174[0] = v174[0] + 0.5f * (f32)(s32)arg0->unk_EC;
        v180[0] = v180[0] + 0.5f * (f32)(s32)arg0->unk_EC;
        v18C[0] = v18C[0] + 0.5f * (f32)(s32)arg0->unk_EC;
        v168[1] = v168[1] + 0.5f * (f32)(s32)arg0->unk_EE;
        v174[1] = v174[1] + 0.5f * (f32)(s32)arg0->unk_EE;
        v180[1] = v180[1] + 0.5f * (f32)(s32)arg0->unk_EE;
        v18C[1] = v18C[1] + 0.5f * (f32)(s32)arg0->unk_EE;
        arg0->unk_E0++;
        arg0->unk_E4 -= 0.025f;
        if (arg0->unk_E4 < 0.025f)
            fn_1_76C60(arg0);
        s74 = color84.word;
        fn_800371F8(1, &s74);
        fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        break;

    case 6:
        v168[0] = v18C[0] = (f32)(s32)arg0->unk_E0 * ((f32)(s32)(-arg0->unk_EC) / 40.0f);
        v174[0] = v180[0] = (f32)(s32)arg0->unk_EC + (f32)(s32)arg0->unk_E0 * ((f32)(s32)(-arg0->unk_EC) / 40.0f);
        v168[1] = v174[1] = 0.0f;
        v180[1] = v18C[1] = (f32)(s32)arg0->unk_EE;
        fn_1_761B8(arg0, 1);
        s70 = color84.word;
        fn_800371F8(1, &s70);
        fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        break;

    case 7:
        v168[0] = v18C[0] = 0.0f;
        v174[0] = v180[0] = (f32)(s32)arg0->unk_EC;
        v168[1] = v174[1] = 0.0f;
        v180[1] = v18C[1] = (f32)(s32)arg0->unk_EE;
        lbl_8006D758();
        mathutil_mtxA_rotate_z((s32)(-(409.6f * (f32)(s32)arg0->unk_E0)));
        lbl_8006E1B0(v168, v168);
        lbl_8006E1B0(v174, v174);
        lbl_8006E1B0(v180, v180);
        lbl_8006E1B0(v18C, v18C);
        fn_1_761B8(arg0, 1);
        s6C = color84.word;
        fn_800371F8(1, &s6C);
        fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        break;

    case 8:
        if (arg0->unk_E0 == 0)
            arg0->unk_E4 = 0.0f;
        v168[0] = v18C[0] = 0.0f;
        v174[0] = v180[0] = (f32)(s32)arg0->unk_EC;
        v168[1] = v174[1] = 0.0f;
        v180[1] = v18C[1] = (f32)(s32)arg0->unk_EE;
        s68 = color84.word;
        fn_800371F8(1, &s68);
        fn_800734A8(0, 0, 0, 255);
        fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        v168[0] = v18C[0] = -(0.5f * (f32)(s32)arg0->unk_EC) * arg0->unk_E4;
        v174[0] = v180[0] = (0.5f * (f32)(s32)arg0->unk_EC) * arg0->unk_E4;
        v168[1] = v174[1] = -(0.5f * (f32)(s32)arg0->unk_EE) * arg0->unk_E4;
        v180[1] = v18C[1] = (0.5f * (f32)(s32)arg0->unk_EE) * arg0->unk_E4;
        v168[0] = v168[0] + 0.5f * (f32)(s32)arg0->unk_EC;
        v174[0] = v174[0] + 0.5f * (f32)(s32)arg0->unk_EC;
        v180[0] = v180[0] + 0.5f * (f32)(s32)arg0->unk_EC;
        v18C[0] = v18C[0] + 0.5f * (f32)(s32)arg0->unk_EC;
        v168[1] = v168[1] + 0.5f * (f32)(s32)arg0->unk_EE;
        v174[1] = v174[1] + 0.5f * (f32)(s32)arg0->unk_EE;
        v180[1] = v180[1] + 0.5f * (f32)(s32)arg0->unk_EE;
        v18C[1] = v18C[1] + 0.5f * (f32)(s32)arg0->unk_EE;
        arg0->unk_E0++;
        arg0->unk_E4 += 0.025f;
        if (arg0->unk_E4 > 1.0f)
            arg0->unk_E4 = 1.0f;
        if ((f32)(s32)arg0->unk_E0 > 40.0f)
            fn_1_76C60(arg0);
        s64 = color84.word;
        fn_800371F8(1, &s64);
        fn_800734A8(0, 0, 1, 255);
        fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        break;

    case 9:
        if (arg0->unk_E0 == 0)
            arg0->unk_E4 = 0.0f;
        v168[0] = v18C[0] = 0.0f;
        v174[0] = v180[0] = (f32)(s32)arg0->unk_EC;
        v168[1] = v174[1] = 0.0f;
        v180[1] = v18C[1] = (f32)(s32)arg0->unk_EE;
        s60 = color84.word;
        fn_800371F8(1, &s60);
        fn_800734A8(0, 0, 0, 255);
        fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        v168[0] = v18C[0] = -(0.5f * (f32)(s32)arg0->unk_EC) * arg0->unk_E4;
        v174[0] = v180[0] = (0.5f * (f32)(s32)arg0->unk_EC) * arg0->unk_E4;
        v168[1] = v174[1] = -(0.5f * (f32)(s32)arg0->unk_EE) * arg0->unk_E4;
        v180[1] = v18C[1] = (0.5f * (f32)(s32)arg0->unk_EE) * arg0->unk_E4;
        lbl_8006D758();
        mathutil_mtxA_rotate_z((s32)(-(40.96f * ((40.0f - (f32)(s32)arg0->unk_E0) * (40.0f - (f32)(s32)arg0->unk_E0)))));
        lbl_8006E1B0(v168, v168);
        lbl_8006E1B0(v174, v174);
        lbl_8006E1B0(v180, v180);
        lbl_8006E1B0(v18C, v18C);
        v168[0] = v168[0] + 0.5f * (f32)(s32)arg0->unk_EC;
        v174[0] = v174[0] + 0.5f * (f32)(s32)arg0->unk_EC;
        v180[0] = v180[0] + 0.5f * (f32)(s32)arg0->unk_EC;
        v18C[0] = v18C[0] + 0.5f * (f32)(s32)arg0->unk_EC;
        v168[1] = v168[1] + 0.5f * (f32)(s32)arg0->unk_EE;
        v174[1] = v174[1] + 0.5f * (f32)(s32)arg0->unk_EE;
        v180[1] = v180[1] + 0.5f * (f32)(s32)arg0->unk_EE;
        v18C[1] = v18C[1] + 0.5f * (f32)(s32)arg0->unk_EE;
        arg0->unk_E0++;
        arg0->unk_E4 += 0.025f;
        if (arg0->unk_E4 > 1.0f)
            arg0->unk_E4 = 1.0f;
        if ((f32)(s32)arg0->unk_E0 > 40.0f)
            fn_1_76C60(arg0);
        s5C = color84.word;
        fn_800371F8(1, &s5C);
        fn_800734A8(0, 0, 1, 255);
        fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        break;

    case 10:
        v168[0] = v18C[0] = 0.0f;
        v174[0] = v180[0] = (f32)(s32)arg0->unk_EC;
        v168[1] = v174[1] = 0.0f;
        v180[1] = v18C[1] = (f32)(s32)arg0->unk_EE;
        s58 = color84.word;
        fn_800371F8(1, &s58);
        fn_800734A8(0, 0, 0, 255);
        fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        v168[0] = v18C[0] = (40.0f - (f32)(s32)arg0->unk_E0) * ((f32)(s32)(-arg0->unk_EC) / 40.0f);
        v174[0] = v180[0] = (f32)(s32)arg0->unk_EC + (40.0f - (f32)(s32)arg0->unk_E0) * ((f32)(s32)(-arg0->unk_EC) / 40.0f);
        v168[1] = v174[1] = 0.0f;
        v180[1] = v18C[1] = (f32)(s32)arg0->unk_EE;
        fn_1_761B8(arg0, 1);
        s54 = color84.word;
        fn_800371F8(1, &s54);
        fn_800734A8(0, 0, 1, 255);
        fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        break;

    case 11:
        v168[0] = v18C[0] = 0.0f;
        v174[0] = v180[0] = (f32)(s32)arg0->unk_EC;
        v168[1] = v174[1] = 0.0f;
        v180[1] = v18C[1] = (f32)(s32)arg0->unk_EE;
        s50 = color84.word;
        fn_800371F8(1, &s50);
        fn_800734A8(0, 0, 0, 255);
        fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        lbl_8006D758();
        mathutil_mtxA_rotate_z((s32)(-(409.6f * (40.0f - (f32)(s32)arg0->unk_E0))));
        lbl_8006E1B0(v168, v168);
        lbl_8006E1B0(v174, v174);
        lbl_8006E1B0(v180, v180);
        lbl_8006E1B0(v18C, v18C);
        fn_1_761B8(arg0, 1);
        s4C = color84.word;
        fn_800371F8(1, &s4C);
        fn_800734A8(0, 0, 1, 255);
        fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        break;

    case 12:
    case 13:
        v168[0] = v18C[0] = 0.0f;
        v174[0] = v180[0] = (f32)(s32)arg0->unk_EC;
        v168[1] = v174[1] = 0.0f;
        v180[1] = v18C[1] = (f32)(s32)arg0->unk_EE;
        color84.bytes.a = 0xff;
        flag = (arg0->unk_DC == 12);
        s48 = color84.word;
        fn_800371F8(2, &s48);
        color84.bytes.a = flag ? 0xfe : 0xff;
        s44 = color84.word;
        fn_800371F8(1, &s44);
        lbl_8006D758();
        lbl_801A6D00[3] = 2.0f / (f32)(s32)arg0->unk_EC;
        lbl_801A6D00[7] = 2.0f / (f32)(s32)arg0->unk_EE;
        GXLoadTexMtxImm(lbl_801A6D00, 30, 1);
        lbl_801A6D00[3] = 2.0f / (f32)(s32)arg0->unk_EC;
        lbl_801A6D00[7] = -2.0f / (f32)(s32)arg0->unk_EE;
        GXLoadTexMtxImm(lbl_801A6D00, 33, 1);
        lbl_801A6D00[3] = -2.0f / (f32)(s32)arg0->unk_EC;
        lbl_801A6D00[7] = -2.0f / (f32)(s32)arg0->unk_EE;
        GXLoadTexMtxImm(lbl_801A6D00, 36, 1);
        lbl_801A6D00[3] = -2.0f / (f32)(s32)arg0->unk_EC;
        lbl_801A6D00[7] = 2.0f / (f32)(s32)arg0->unk_EE;
        GXLoadTexMtxImm(lbl_801A6D00, 39, 1);
        fn_800724C8();
        fn_8007245C(0x2200);
        fn_80074788(0);
        fn_80074660(5);
        fn_80073678(6);
        fn_80073898(0);
        fn_800745A4(0, 1, 4, 30, 0, 125);
        fn_800745A4(1, 1, 4, 33, 0, 125);
        fn_800745A4(2, 1, 4, 36, 0, 125);
        fn_800745A4(3, 1, 4, 39, 0, 125);
        fn_800745A4(4, 1, 4, 60, 0, 125);
        fn_80073C6C(0);
        fn_80073C6C(1);
        fn_80073C6C(2);
        fn_80073C6C(3);
        fn_80073C6C(4);
        fn_80073C6C(5);
        fn_800734A8(0, 0, 2, 255);
        fn_800734A8(1, 1, 2, 255);
        fn_800734A8(2, 2, 2, 255);
        fn_800734A8(3, 3, 2, 255);
        fn_800734A8(4, 4, 0, 255);
        fn_800734A8(5, 4, 1, 255);
        fn_80072AB0(0, 0, 0);
        fn_80072AB0(1, 0, 0);
        fn_80072AB0(2, 0, 0);
        fn_80072AB0(3, 0, 0);
        fn_80072AB0(4, 0, 0);
        fn_80072AB0(5, 0, 0);
        fn_800735C8(0, 4);
        fn_80072C24(0, 15, 8, 14, 15);
        fn_80072D64(0, 0, 0, 0, 0, 0);
        fn_800735C8(1, 4);
        fn_80072C24(1, 15, 8, 14, 0);
        fn_80072D64(1, 0, 0, 0, 0, 0);
        fn_800735C8(2, 4);
        fn_80072C24(2, 15, 8, 14, 0);
        fn_80072D64(2, 0, 0, 0, 0, 0);
        fn_800735C8(3, 4);
        fn_80072C24(3, 15, 8, 14, 0);
        fn_80072D64(3, 0, 0, 3, 1, 0);
        fn_800735C8(4, 0);
        fn_80073620(4, 0);
        fn_80072C24(4, 15, 15, 15, 0);
        fn_80072D64(4, 0, 0, 0, 1, 0);
        if (flag)
            fn_80072CC4(4, 4, 1, 6, 7);
        else
            fn_80072CC4(4, 1, 4, 6, 7);
        fn_80072E20(4, 14, 0, 0, 1, 0);
        fn_800735C8(5, 0);
        fn_80073620(5, 0);
        fn_80072C24(5, 15, 15, 15, 0);
        fn_80072D64(5, 0, 0, 0, 1, 0);
        if (flag)
            fn_80072CC4(5, 7, 4, 0, 7);
        else
            fn_80072CC4(5, 6, 7, 4, 0);
        fn_80072E20(5, 0, 0, 0, 1, 0);
        fn_800747D0(4, 0, 0, 0, 0, 2, 2);
        fn_80074918(1, 7, 0);
        fn_800728A8(1, 4, 5, 0);
        fn_800720B0(0);
        fn_80072864(2);
        fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        break;

    case 14:
    case 15:
        v168[0] = v18C[0] = 0.0f;
        v174[0] = v180[0] = (f32)(s32)arg0->unk_EC;
        v168[1] = v174[1] = 0.0f;
        v180[1] = v18C[1] = (f32)(s32)arg0->unk_EE;
        if (arg0->unk_DC == 12) {
            color84.bytes.a = 0xff;
            flag = 1;
        } else if (arg0->unk_DC == 13) {
            color84.bytes.a = 0xff;
            flag = 0;
        } else if (arg0->unk_DC == 14) {
            color84.bytes.a = 0x80;
            flag = 0;
        } else {
            color84.bytes.a = 0x80;
            flag = 0;
        }
        s40 = color84.word;
        fn_800371F8(2, &s40);
        color84.bytes.a = flag ? 0xfe : 0xff;
        s3C = color84.word;
        fn_800371F8(1, &s3C);
        fn_800724C8();
        fn_8007245C(0x2200);
        fn_80074788(0);
        fn_80074660(1);
        fn_80073678(3);
        fn_80073898(0);
        fn_80073C6C(0);
        fn_80073C6C(1);
        fn_80073C6C(2);
        fn_800745A4(0, 1, 4, 60, 0, 125);
        fn_800734A8(0, 0, 0, 255);
        fn_800734A8(1, 0, 1, 255);
        fn_800734A8(2, 0, 2, 255);
        fn_80072AB0(0, 0, 0);
        fn_80072AB0(1, 0, 0);
        fn_80072AB0(2, 0, 0);
        fn_800735C8(0, 0);
        fn_80073620(0, 0);
        fn_80072C24(0, 15, 15, 15, 14);
        fn_80072D64(0, 0, 0, 0, 1, 0);
        if (flag)
            fn_80072CC4(0, 4, 1, 6, 7);
        else
            fn_80072CC4(0, 1, 4, 6, 7);
        fn_80072E20(0, 14, 0, 0, 1, 0);
        fn_800735C8(1, 0);
        fn_80073620(1, 0);
        fn_80072C24(1, 15, 15, 15, 14);
        fn_80072D64(1, 0, 0, 0, 1, 0);
        if (flag)
            fn_80072CC4(1, 7, 4, 0, 7);
        else
            fn_80072CC4(1, 6, 7, 4, 0);
        fn_80072E20(1, 0, 0, 0, 1, 0);
        fn_80072C24(2, 15, 15, 15, 8);
        fn_80072D64(2, 0, 0, 0, 1, 0);
        fn_80072CC4(2, 7, 2, 0, 7);
        fn_80072E20(2, 0, 0, 0, 1, 0);
        fn_800747D0(4, 0, 0, 0, 0, 2, 2);
        fn_80074918(1, 7, 0);
        fn_800728A8(1, 4, 5, 0);
        fn_800720B0(0);
        fn_80072864(2);
        if (arg0->unk_DC == 15) {
            lbl_8006D784(m138);
            aC0[0] = 0.5f * m138[0];
            aC0[1] = 0.5f * m138[1];
            aC0[2] = 0.0f;
            aC0[3] = 0.5f * m138[4];
            aC0[4] = 0.5f * m138[5];
            aC0[5] = 0.0f;
            fn_80073A58(1, aC0, 1);
            fn_80073898(1);
            fn_800738E0(0, 0, 3);
            fn_80073D60(2, 0, 1, 0, 1);
        }
        fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        fn_80073678(1);
        fn_80073898(0);
        fn_80072C24(0, 15, 2, 8, 4);
        fn_80072D64(0, 0, 0, 0, 1, 0);
        fn_80072CC4(0, 7, 1, 4, 2);
        fn_80072E20(0, 0, 0, 0, 1, 0);
        break;

    case 36:
        v168[0] = v18C[0] = 0.0f;
        v174[0] = v180[0] = (f32)(s32)arg0->unk_EC;
        v168[1] = v174[1] = 0.0f;
        v180[1] = v18C[1] = (f32)(s32)arg0->unk_EE;
        color84.bytes.a = 0xff;
        s38 = color84.word;
        fn_800371F8(2, &s38);
        color84.bytes.a = 0xfe;
        s34 = color84.word;
        fn_800371F8(1, &s34);
        fn_800724C8();
        fn_8007245C(0x2200);
        fn_80074788(0);
        fn_80074660(1);
        fn_80073678(3);
        fn_80073898(0);
        fn_80073C6C(0);
        fn_80073C6C(1);
        fn_80073C6C(2);
        fn_800745A4(0, 1, 4, 60, 0, 125);
        fn_800734A8(0, 0, 0, 255);
        fn_800734A8(1, 0, 1, 255);
        fn_800734A8(2, 0, 2, 255);
        fn_80072AB0(0, 0, 0);
        fn_80072AB0(1, 0, 0);
        fn_80072AB0(2, 0, 0);
        fn_80073620(0, 0);
        fn_80072C24(0, 15, 15, 15, 15);
        fn_80072D64(0, 0, 0, 0, 1, 0);
        fn_80072CC4(0, 4, 1, 6, 7);
        fn_80072E20(0, 14, 0, 0, 1, 0);
        fn_80072C24(1, 15, 15, 15, 15);
        fn_80072D64(1, 0, 0, 0, 1, 0);
        fn_80072CC4(1, 7, 4, 0, 7);
        fn_80072E20(1, 0, 0, 0, 1, 0);
        fn_800735C8(2, 0);
        fn_80072C24(2, 14, 15, 8, 15);
        fn_80072D64(2, 0, 0, 0, 1, 0);
        fn_80072CC4(2, 7, 4, 0, 7);
        fn_80072E20(2, 0, 0, 0, 1, 0);
        fn_800747D0(4, 0, 0, 0, 0, 2, 2);
        fn_80074918(1, 7, 0);
        fn_800728A8(1, 4, 5, 0);
        fn_800720B0(0);
        fn_80072864(2);
        if (arg0->unk_DC == 15) {
            lbl_8006D784(m108);
            aA8[0] = 0.5f * m108[0];
            aA8[1] = 0.5f * m108[1];
            aA8[2] = 0.0f;
            aA8[3] = 0.5f * m108[4];
            aA8[4] = 0.5f * m108[5];
            aA8[5] = 0.0f;
            fn_80073A58(1, aA8, 1);
            fn_80073898(1);
            fn_800738E0(0, 0, 3);
            fn_80073D60(2, 0, 1, 0, 1);
        }
        fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        fn_80073678(1);
        fn_80073898(0);
        fn_80072C24(0, 15, 2, 8, 4);
        fn_80072D64(0, 0, 0, 0, 1, 0);
        fn_80072CC4(0, 7, 1, 4, 2);
        fn_80072E20(0, 0, 0, 0, 1, 0);
        break;

    case 16:
        v168[0] = v18C[0] = 0.0f;
        v174[0] = v180[0] = (f32)(s32)arg0->unk_EC;
        v168[1] = v174[1] = 0.0f;
        v180[1] = v18C[1] = (f32)(s32)arg0->unk_EE;
        lbl_8006D758();
        GXLoadTexMtxImm(lbl_801A6D00, 30, 1);
        lbl_801A6D00[3] = 2.0f / (f32)(s32)arg0->unk_EC;
        lbl_801A6D00[7] = 2.0f / (f32)(s32)arg0->unk_EE;
        GXLoadTexMtxImm(lbl_801A6D00, 33, 1);
        lbl_801A6D00[3] = 2.0f / (f32)(s32)arg0->unk_EC;
        lbl_801A6D00[7] = -2.0f / (f32)(s32)arg0->unk_EE;
        GXLoadTexMtxImm(lbl_801A6D00, 36, 1);
        lbl_801A6D00[3] = -2.0f / (f32)(s32)arg0->unk_EC;
        lbl_801A6D00[7] = -2.0f / (f32)(s32)arg0->unk_EE;
        GXLoadTexMtxImm(lbl_801A6D00, 39, 1);
        lbl_801A6D00[3] = -2.0f / (f32)(s32)arg0->unk_EC;
        lbl_801A6D00[7] = 2.0f / (f32)(s32)arg0->unk_EE;
        GXLoadTexMtxImm(lbl_801A6D00, 42, 1);
        fn_800724C8();
        fn_8007245C(0x2200);
        fn_80074660(2);
        fn_80074788(0);
        fn_80073678(2);
        fn_80073898(0);
        fn_800729B0(2, 0, 1, 2, 2);
        fn_80073C6C(0);
        fn_80072AB0(0, 0, 2);
        fn_80073C6C(1);
        fn_80072AB0(1, 0, 2);
        fn_800734A8(0, 0, 0, 255);
        fn_80072EDC(0, 3);
        fn_800734A8(1, 1, 0, 255);
        fn_80072C24(1, 15, 15, 15, 15);
        fn_80072D64(1, 0, 0, 0, 1, 0);
        fn_80072CC4(1, 4, 7, 7, 0);
        fn_80072E20(1, 1, 0, 0, 0, 0);
        GXSetAlphaCompare(4, 1, 0, 1, 255);
        fn_80074918(1, 7, 0);
        fn_800745A4(0, 1, 4, 30, 0, 125);
        i = 0;
        id = 0x21;
        for (; i < 4; i++) {
            fn_800745A4(1, 1, 4, id, 0, 125);
            id += 3;
            fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        }
        break;

    case 23:
        fn_1_76EB8();
        break;

    case 24: {
        if (lbl_1_data_1D9B8__fzgx_offset_F8[0] < 255)
            lbl_1_data_1D9B8__fzgx_offset_F8[0]++;
        if (lbl_1_data_1D9B8__fzgx_offset_F8[1] < 255)
            lbl_1_data_1D9B8__fzgx_offset_F8[1]++;
        if (lbl_1_data_1D9B8__fzgx_offset_F8[2] < 255)
            lbl_1_data_1D9B8__fzgx_offset_F8[2]++;
        if (lbl_1_data_1D9B8__fzgx_offset_F8[3] < 255)
            lbl_1_data_1D9B8__fzgx_offset_F8[3]++;
        if (lbl_1_data_1D9B8__fzgx_offset_F8[0] == 255 && lbl_1_data_1D9B8__fzgx_offset_F8[1] == 255 && lbl_1_data_1D9B8__fzgx_offset_F8[2] == 255 && lbl_1_data_1D9B8__fzgx_offset_F8[3] == 255) {
            fn_1_76C60(arg0);
        } else {
            lbl_1_data_1D9B8__fzgx_offset_FC = lbl_1_data_1D9B8__fzgx_offset_FC + 0.01f * (1.0f - lbl_1_data_1D9B8__fzgx_offset_FC);
            lbl_1_data_1D9B8__fzgx_offset_100 = lbl_1_data_1D9B8__fzgx_offset_100 + 0.01f * (1.0f - lbl_1_data_1D9B8__fzgx_offset_FC);
            fn_1_76EB8();
        }
        break;
    }

    case 25:
        v168[0] = v18C[0] = 0.0f;
        v174[0] = v180[0] = (f32)(s32)arg0->unk_EC;
        v168[1] = v174[1] = 0.0f;
        v180[1] = v18C[1] = (f32)(s32)arg0->unk_EE;
        fn_800724C8();
        fn_8007245C(0x2200);
        fn_80074660(1);
        fn_80074788(0);
        fn_80073678(1);
        fn_80073898(0);
        fn_80072EDC(0, 3);
        fn_800734A8(0, 0, 0, 255);
        fn_80074918(1, 7, 0);
        fn_800745A4(0, 1, 4, 30, 0, 125);
        lbl_8006D758();
        GXLoadTexMtxImm(lbl_801A6D00, 30, 1);
        fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        break;

    case 26:
        v168[0] = v18C[0] = 0.0f;
        v174[0] = v180[0] = (f32)(s32)arg0->unk_EC;
        v168[1] = v174[1] = 0.0f;
        v180[1] = v18C[1] = (f32)(s32)arg0->unk_EE;
        fn_1_77200();
        fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        break;

    case 27:
        v168[0] = v18C[0] = 0.0f;
        v174[0] = v180[0] = (f32)(s32)arg0->unk_EC;
        v168[1] = v174[1] = 0.0f;
        v180[1] = v18C[1] = (f32)(s32)arg0->unk_EE;
        fn_1_77200();
        fn_1_4E220((u8 *)&p_bss->unk_8D0 - 0x58, 1, 1, 2, 33);
        fn_80074660(2);
        fn_80073678(2);
        fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        break;

    case 28:
        fn_80074788(0);
        fn_80074660(1);
        fn_80073678(1);
        fn_80073898(0);
        fn_80073C6C(0);
        fn_800745A4(0, 1, 4, 60, 0, 125);
        fn_800734A8(0, 0, 0, 255);
        fn_80072AB0(0, 0, 0);
        fn_80072EDC(0, 3);
        fn_800729B0(2, 3, 1, 2, 3);
        fn_80072AB0(0, 0, 2);
        color84.bytes.r = 0xf0;
        color84.bytes.g = 0xff;
        s30 = color84.word;
        fn_800736C0(0, &s30);
        fn_800735C8(0, 12);
        fn_80072C24(0, 8, 14, 12, 15);
        fn_80072D64(0, 10, 0, 0, 1, 0);
        fn_800728A8(1, 3, 3, 0);
        fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        break;

    case 29:
        fn_80073D60(0, 0, 1, 0, 1);
        fn_80073678(1);
        fn_800734A8(0, 0, 0, 4);
        fn_80073898(1);
        fn_800738E0(0, 1, 1);
        fn_80074660(2);
        fn_800745A4(0, 1, 4, 60, 0, 125);
        fn_800745A4(1, 1, 4, 36, 0, 125);
        fn_80074788(1);
        fn_800747D0(0, 0, 0, 0, 0, 0, 2);
        fn_800747D0(2, 0, 0, 1, 0, 0, 2);
        fn_80073778((void *)p_bss->unk_8D0, 1);
        a90[0] = 0.0f;
        a90[1] = 0.0f;
        a90[2] = 0.003f;
        a90[3] = 0.0f;
        a90[4] = 0.0f;
        a90[5] = 0.003f;
        fn_80073A58(1, a90, 1);
        fn_800739E0(0, 0, 0);
        lbl_8006D784(mD8);
        mD8[0] = 5.0f;
        mD8[5] = 15.0f;
        mD8[3] = 0.0f;
        mD8[7] = 0.01f * (f32)lbl_801A66A0;
        GXLoadTexMtxImm(mD8, 36, 1);
        fn_80072C24(0, 15, 15, 15, 8);
        fn_80072D64(0, 0, 0, 0, 1, 0);
        fn_80072CC4(0, 7, 7, 7, 5);
        fn_80072E20(0, 0, 0, 0, 1, 0);
        fn_800728A8(1, 4, 5, 0);
        fn_80074918(1, 7, 0);
        fn_1_77C5C(v168, &arg0->unk_E8, &arg0->unk_F8);
        break;

    case 30:
        fn_80074788(0);
        fn_80074660(1);
        fn_80073678(2);
        fn_80073898(0);
        fn_80073C6C(0);
        fn_80073C6C(1);
        fn_800745A4(0, 1, 4, 60, 0, 125);
        fn_800734A8(0, 0, 0, 255);
        fn_800734A8(1, 0, 1, 255);
        fn_80072AB0(0, 0, 0);
        fn_80072AB0(1, 0, 0);
        fn_800729B0(2, 3, 1, 2, 3);
        fn_80072AB0(0, 0, 2);
        color84.bytes.r = (u8)p_bss->unk_8D4;
        color84.bytes.g = (p_bss->unk_8D4 >> 8) & 0xff;
        color84.bytes.a = (u8)p_bss->unk_8D6;
        s2C = color84.word;
        fn_800371F8(1, &s2C);
        s28 = color84.word;
        fn_800736C0(0, &s28);
        fn_800735C8(0, 12);
        fn_80072C24(0, 8, 14, 3, 15);
        fn_80072D64(0, 10, 0, 0, 1, 0);
        fn_80072CC4(0, 7, 7, 7, 7);
        fn_80072E20(0, 0, 0, 0, 1, 0);
        color80.bytes.r = (u8)p_bss->unk_8D8;
        s24 = color80.word;
        fn_800736C0(1, &s24);
        fn_800735C8(1, 13);
        fn_80072C24(1, 8, 14, 0, 0);
        fn_80072D64(1, 8, 0, 0, 1, 0);
        fn_80072CC4(1, 7, 7, 7, 7);
        fn_80072E20(1, 0, 0, 0, 1, 0);
        fn_800728A8(1, 1, 5, 0);
        fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        break;

    case 31:
        v168[0] = v18C[0] = 0.0f;
        v174[0] = v180[0] = (f32)(s32)arg0->unk_EC;
        v168[1] = v174[1] = 0.0f;
        v180[1] = v18C[1] = (f32)(s32)arg0->unk_EE;
        s20 = color84.word;
        fn_800371F8(1, &s20);
        fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        break;

    case 32:
        v168[0] = v18C[0] = 0.0f;
        v174[0] = v180[0] = (f32)(s32)arg0->unk_EC;
        v168[1] = v174[1] = 0.0f;
        v180[1] = v18C[1] = (f32)(s32)arg0->unk_EE;
        fn_80074660(2);
        fn_800745A4(0, 1, 4, 60, 0, 125);
        fn_800745A4(1, 1, 4, 60, 0, 125);
        fn_80073678(4);
        fn_80073C6C(0);
        fn_80073C6C(1);
        fn_80073C6C(2);
        fn_80073C6C(3);
        fn_800734A8(0, 0, 1, 255);
        fn_80072C24(0, 15, 8, 14, 2);
        fn_80072D64(0, 0, 0, 0, 0, 0);
        fn_80072CC4(0, 7, 4, 6, 1);
        fn_80072E20(0, 1, 0, 0, 0, 0);
        fn_800735C8(0, 12);
        fn_80073620(0, 28);
        fn_80072AB0(0, 0, 1);
        fn_800734A8(1, 1, 0, 255);
        fn_80072C24(1, 15, 8, 14, 0);
        fn_80072D64(1, 0, 0, 1, 0, 0);
        fn_80072CC4(1, 7, 4, 6, 0);
        fn_80072E20(1, 0, 0, 1, 0, 0);
        fn_800735C8(1, 13);
        fn_80073620(1, 29);
        fn_80072AB0(1, 0, 0);
        fn_800734A8(2, 0, 1, 255);
        fn_80072C24(2, 15, 8, 14, 0);
        fn_80072D64(2, 0, 0, 0, 1, 0);
        fn_80072CC4(2, 7, 4, 6, 0);
        fn_80072E20(2, 1, 0, 0, 1, 0);
        fn_800735C8(2, 14);
        fn_80073620(2, 30);
        fn_80072AB0(2, 0, 2);
        fn_800734A8(3, 255, 255, 255);
        fn_80072C24(3, 0, 1, 14, 15);
        fn_80072D64(3, 0, 0, 0, 1, 0);
        fn_80072CC4(3, 7, 7, 7, 7);
        fn_80072E20(3, 0, 0, 0, 1, 0);
        fn_80072AB0(3, 0, 0);
        fn_800735C8(3, 15);
        { union Color color88[2] = {{{0xFF,0x91,0x00,0x00}},{{0xFF,0x76,0x00,0x44}}};
        fn_8003726C(1, w88); }
        { union Color s1C = {{0x66,0x00,0xFF,0x32}};
        fn_800736C0(0, &s1C); }
        { union Color s18 = {{0x94,0x00,0x94,0x94}};
        fn_800736C0(1, &s18); }
        { union Color s14 = {{0xCB,0x00,0x05,0xCF}};
        fn_800736C0(2, &s14); }
        { union Color s10 = {{0x00,0xFF,0x00,0x00}};
        fn_800736C0(3, &s10); }
        fn_800729B0(0, 0, 1, 2, 3);
        fn_800729B0(1, 0, 3, 3, 3);
        fn_800729B0(2, 0, 0, 3, 0);
        fn_80074788(0);
        fn_80073898(0);
        fn_800728A8(1, 1, 0, 0);
        fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        fn_80072808();
        break;

    case 33:
        color84.bytes.a = (u8)(255 - p_bss->unk_8DA);
        { union Color s0C = color84;
        fn_800371F8(1, &s0C); }
        fn_80072C24(0, 8, 15, 15, 15);
        fn_80072D64(0, 0, 0, 0, 1, 0);
        fn_80072CC4(0, 7, 7, 7, 1);
        fn_80072E20(0, 0, 0, 0, 1, 0);
        fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        break;

    case 34:
        fn_80074788(0);
        fn_80074660(1);
        fn_80073678(3);
        fn_80073898(0);
        fn_80073C6C(0);
        fn_80073C6C(1);
        fn_80073C6C(2);
        fn_800745A4(0, 1, 4, 60, 0, 125);
        fn_800734A8(0, 0, 0, 255);
        fn_800734A8(1, 0, 1, 255);
        fn_800734A8(2, 0, 2, 255);
        fn_80072AB0(0, 0, 0);
        fn_80072AB0(1, 0, 0);
        fn_80072AB0(2, 0, 0);
        fn_80072EDC(0, 3);
        fn_80072C24(1, 15, 8, 12, 0);
        fn_80072D64(1, 1, 0, 0, 1, 0);
        fn_80072CC4(1, 7, 7, 7, 7);
        fn_80072E20(1, 0, 0, 0, 1, 0);
        { union Color s08 = color84;
        fn_800736C0(0, &s08); }
        fn_800735C8(2, 12);
        fn_80072C24(2, 0, 14, 8, 15);
        fn_80072D64(2, 0, 0, 0, 1, 0);
        fn_80072CC4(2, 7, 7, 7, 7);
        fn_80072E20(2, 0, 0, 0, 1, 0);
        fn_80073678(3);
        fn_800728A8(1, 1, 0, 0);
        fn_1_75D84(v168, &arg0->unk_E8, &arg0->unk_F8);
        break;
    }
}
/* fzgx:end fn_1_729F8 */

/* fzgx:begin fn_1_761B8 */
struct fn_1_761B8_Arg0 {
    u8 pad_0[0xE0];
    u32 unk_E0;
};

extern const f32 lbl_1_rodata_31A8;
extern const f64 lbl_1_rodata_31D8[2];
extern void fn_1_76C60(void);

void fn_1_761B8(struct fn_1_761B8_Arg0 *arg0, u32 arg1) {
    u32 v0;
    f32 v1;
    v0 = (arg0->unk_E0 + arg1);
    arg0->unk_E0 = v0;
    v1 = (f32)(s32)arg0->unk_E0;
    if (v1 > lbl_1_rodata_31A8) {
        fn_1_76C60();
    }
}
/* fzgx:end fn_1_761B8 */

/* fzgx:begin fn_1_76218 noprologue */
#include "types.h"

struct Sig_fn_8004E278_fn_8004E278_Arg0 {
    u32 unk_0;
};

struct Sig_fn_1_76448_fn_1_76448_Arg0 {
    u8 pad_0[0xA0];
    u32 unk_A0[1];
    u8 pad_A4[0x38];
    u32 unk_DC;
    u8 pad_E0[0x18];
    s16 unk_F8;
};

typedef struct {
    u8 pad_0[0xa0];
    u32 unk_a0[5];
    u32 unk_b4[5];
    s32 unk_c8[5];
    u32 unk_dc;
    u32 unk_e0;
    f32 unk_e4;
    u16 unk_e8;
    u16 unk_ea;
    u16 unk_ec;
    u16 unk_ee;
    u16 unk_f0;
    u16 unk_f2;
    u32 unk_f4;
    u16 unk_f8;
    u16 unk_fa;
    u16 unk_fc;
    u16 unk_fe;
    u16 unk_100;
    u16 unk_102;
    u32 unk_104;
    u8 unk_108;
} Sig_fn_1_76C60_FnScreenEffect;

struct fn_1_76218_jumptable_1_data_1DBC0 {
    u32 unk_0[1];
};
extern struct fn_1_76218_jumptable_1_data_1DBC0 jumptable_1_data_1DBC0;
extern u8 lbl_1_bss_6C8EC[];
extern void DCInvalidateRange(struct Sig_fn_8004E278_fn_8004E278_Arg0 *, u32);
extern void fn_1_76448(struct Sig_fn_1_76448_fn_1_76448_Arg0 *, u32);
extern void fn_1_76C60(Sig_fn_1_76C60_FnScreenEffect *);
extern u32 fn_1_7880C(void);
extern u32 fn_1_788B0(void);
extern void GXInvalidateTexAll(void);


void fn_1_76218(s32 arg0) {
    s32 temp_r4;
    s32 var_r5;
    u8 var_r29;
    u8 var_r29_2;
    struct Sig_fn_1_76448_fn_1_76448_Arg0 *temp_r28;
    struct Sig_fn_1_76448_fn_1_76448_Arg0 *temp_r28_2;

    var_r5 = 0;
    if (arg0 != 0) {
        var_r29 = 0;
        while (var_r29 < 8U) {
            temp_r28 = (struct Sig_fn_1_76448_fn_1_76448_Arg0 *)((u8 *)(lbl_1_bss_6C8EC) + (var_r29 * 0x10C));
            if ((s32) temp_r28->unk_DC == 0x25) {
                DCInvalidateRange((struct Sig_fn_8004E278_fn_8004E278_Arg0 *)(*(struct Sig_fn_8004E278_fn_8004E278_Arg0 **)((u8 *)(temp_r28) + 160)), (u32)(*(u32 *)((u8 *)(temp_r28) + 180)));
                fn_1_76448((struct Sig_fn_1_76448_fn_1_76448_Arg0 *)(temp_r28), (u32)(0U));
                fn_1_76C60((Sig_fn_1_76C60_FnScreenEffect *)((Sig_fn_1_76C60_FnScreenEffect *) temp_r28));
                var_r5 = 1;
            }
            var_r29 += 1;
                    }
    }
    var_r29_2 = 0;
    while (var_r29_2 < 8U) {
        temp_r28_2 = (struct Sig_fn_1_76448_fn_1_76448_Arg0 *)((u8 *)(lbl_1_bss_6C8EC) + (var_r29_2 * 0x10C));
        temp_r4 = temp_r28_2->unk_DC;
        if ((temp_r4 != 0) && ((u8) (*(u8 *)((u8 *)(temp_r28_2) + 264)) == 0)) {
            if (arg0 != 0) {
                switch (temp_r4) {
                case 0xE:
                    fn_1_76448((struct Sig_fn_1_76448_fn_1_76448_Arg0 *)(temp_r28_2), (u32)(2U));
                    break;
                case 0x17:
                case 0x18:
                    fn_1_76448((struct Sig_fn_1_76448_fn_1_76448_Arg0 *)(temp_r28_2), (u32)(0U));
                    fn_1_76448((struct Sig_fn_1_76448_fn_1_76448_Arg0 *)(temp_r28_2), (u32)(1U));
                    break;
                }
            } else {
                switch (temp_r4) {
                case 16:
                case 25:
                case 26:
                case 27:
                case 28:
                case 29:
                case 33:
                case 35:
                    fn_1_76448((struct Sig_fn_1_76448_fn_1_76448_Arg0 *)(temp_r28_2), (u32)(0U));
                    break;
                case 14:
                case 30:
                    fn_1_76448((struct Sig_fn_1_76448_fn_1_76448_Arg0 *)(temp_r28_2), (u32)(0U));
                    fn_1_76448((struct Sig_fn_1_76448_fn_1_76448_Arg0 *)(temp_r28_2), (u32)(1U));
                    break;
                case 12:
                case 13:
                case 15:
                case 36:
                    fn_1_76448((struct Sig_fn_1_76448_fn_1_76448_Arg0 *)(temp_r28_2), (u32)(0U));
                    fn_1_76448((struct Sig_fn_1_76448_fn_1_76448_Arg0 *)(temp_r28_2), (u32)(1U));
                    fn_1_76448((struct Sig_fn_1_76448_fn_1_76448_Arg0 *)(temp_r28_2), (u32)(2U));
                    break;
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                    if ((s32) (*(s32 *)((u8 *)(temp_r28_2) + 224)) == 0) {
                        fn_1_76448((struct Sig_fn_1_76448_fn_1_76448_Arg0 *)(temp_r28_2), (u32)(0U));
                    }
                    break;
                case 8:
                case 9:
                case 10:
                case 11:
                    if ((s32) (*(s32 *)((u8 *)(temp_r28_2) + 224)) == 0) {
                        fn_1_76448((struct Sig_fn_1_76448_fn_1_76448_Arg0 *)(temp_r28_2), (u32)(0U));
                    }
                    fn_1_76448((struct Sig_fn_1_76448_fn_1_76448_Arg0 *)(temp_r28_2), (u32)(1U));
                    break;
                case 34:
                    fn_1_76448((struct Sig_fn_1_76448_fn_1_76448_Arg0 *)(temp_r28_2), (u32)(2U));
                    fn_1_7880C();
                    fn_1_76448((struct Sig_fn_1_76448_fn_1_76448_Arg0 *)(temp_r28_2), (u32)(0U));
                    fn_1_788B0();
                    fn_1_76448((struct Sig_fn_1_76448_fn_1_76448_Arg0 *)(temp_r28_2), (u32)(1U));
                    break;
                }
            }
            var_r5 = 1;
        }
        var_r29_2 += 1;
            }
    if (var_r5 != 0) {
        GXInvalidateTexAll();
    }
}
/* fzgx:end fn_1_76218 */

/* fzgx:begin fn_1_76448 */
#include "types.h"

struct fn_1_76448_Arg0 {
    u8 pad_0[0xA0];
    u32 unk_A0[1];
    u8 pad_A4[0x38];
    u32 unk_DC;
    u8 pad_E0[0x18];
    s16 unk_F8;
};

void fn_1_76448(struct fn_1_76448_Arg0 *arg0, u32 arg1) {
    u32 v0;
    s32 v1;
    u8 v2;
    u32 v3;
    v0 = (arg1 & 0xFF);
    v1 = (arg0->unk_DC * 6);
    v2 = *(u8 *)((u8 *)((u8 *)&lbl_1_data_1D9B8 + v1) + v0);
    v3 = (u32)((u8 *)&lbl_1_data_1D960 + (v2 << 3));
    fn_80074300((arg0->unk_F8 & 0xFFFF), (*(s16 *)((u8 *)(u32)arg0 + 250) & 0xFFFF), (*(s16 *)((u8 *)(u32)arg0 + 252) & 0xFFFF), (*(s16 *)((u8 *)(u32)arg0 + 254) & 0xFFFF));
    fn_80074438((*(s16 *)((u8 *)(u32)arg0 + 256) & 0xFFFF), (*(s16 *)((u8 *)(u32)arg0 + 258) & 0xFFFF), *(u32 *)((u8 *)v3 + 4), (*(u32 *)((u8 *)(u32)arg0 + 244) & 0xFF));
    fn_8003526C(arg0->unk_A0[v0], 0);
}
/* fzgx:end fn_1_76448 */

/* fzgx:begin fn_1_76650 */
typedef struct fn_1_76650_ScreenEffect {
    u8 pad_00[0xa0];
    s32 field_a0;
    s32 field_a4;
    s32 field_a8;
    s32 field_ac;
    s32 field_b0;
    u8 pad_b4[0x14];
    s32 field_c8;
    s32 field_cc;
    s32 field_d0;
    s32 field_d4;
    s32 field_d8;
    s32 field_dc;
    s32 field_e0;
    f32 field_e4;
    s16 field_e8;
    s16 field_ea;
    s16 field_ec;
    s16 field_ee;
    s16 field_f0;
    s16 field_f2;
    s32 field_f4;
    s16 field_f8;
    s16 field_fa;
    s16 field_fc;
    s16 field_fe;
    s16 field_100;
    s16 field_102;
    s32 field_104;
    u8 field_108;
} fn_1_76650_ScreenEffect;

void fn_1_76650(fn_1_76650_ScreenEffect *effect) {
    s32 value;

    effect->field_f2 = 0;
    effect->field_f0 = 0;
    effect->field_ea = 0;
    effect->field_e8 = 0;
    effect->field_ec = 0x280;
    effect->field_ee = 0x1e0;
    effect->field_f4 = 0;
    effect->field_fa = 0;
    effect->field_f8 = 0;
    effect->field_100 = 0x280;
    effect->field_fc = 0x280;
    value = fn_1_A5D9C();
    effect->field_102 = value;
    effect->field_fe = value;
    effect->field_dc = 0;
    effect->field_e0 = 0;
    effect->field_e4 = lbl_1_rodata_31AC;
    effect->field_104 = 0;
    effect->field_108 = 0;
    effect->field_a0 = 0;
    effect->field_c8 = 0;
    effect->field_a4 = 0;
    effect->field_cc = 0;
    effect->field_a8 = 0;
    effect->field_d0 = 0;
    effect->field_ac = 0;
    effect->field_d4 = 0;
    effect->field_b0 = 0;
    effect->field_d8 = 0;
}
/* fzgx:end fn_1_76650 */

/* fzgx:begin fn_1_76964 */
typedef struct {
    u8 pad_0[0xB4];
    u32 unk_B4[6];
    u8 pad_CC[0x10];
    u32 unk_DC;
    u8 pad_E0[0x20];
    s16 unk_100;
    s16 unk_102;
} Fn1_76964Obj;

typedef struct {
    u8 unk_0[5];
    u8 unk_5;
} Fn1_76964Record;

typedef u8 Sig_GXGetTexBufferSize_GXBool;
extern u32 GXGetTexBufferSize(u16, u16, u32, Sig_GXGetTexBufferSize_GXBool, u8);

void fn_1_76964(Fn1_76964Obj *obj) {
    int i;

    for (i = 0; i < ((Fn1_76964Record *)&lbl_1_data_1D9B8)[obj->unk_DC].unk_5; i++) {
        obj->unk_B4[i] = GXGetTexBufferSize(
            obj->unk_100,
            obj->unk_102,
            *(u32 *)((u8 *)&lbl_1_data_1D960 +
                     ((*(u8 *)((u8 *)&lbl_1_data_1D9B8 + obj->unk_DC * 6 + i)) << 3)),
            0,
            0);
    }
}
/* fzgx:end fn_1_76964 */

/* fzgx:begin fn_1_76BD0 */
void fn_1_76BD0(u8 index, u8 value) {
    Obj_1_bss_6C8EC *obj =
        (Obj_1_bss_6C8EC *)((u8 *)&lbl_1_bss_6C8EC + index * 0x10c);

    if ((s32)obj->unk_DC != 0) {
        obj->unk_108 = value;
    }
}
/* fzgx:end fn_1_76BD0 */

/* fzgx:begin fn_1_76BF8 */
extern void fn_1_76C60(void);

typedef struct {
    u8 pad_0[0xDC];
    s32 unk_DC;
    u8 pad_E0[0x2C];
} fn_1_76BF8_ScreenEffectEntry;

void fn_1_76BF8(void) {
    u8 i;
    fn_1_76BF8_ScreenEffectEntry *entry;

    entry = (fn_1_76BF8_ScreenEffectEntry *)&lbl_1_bss_6C8EC;
    for (i = 0; i < 8; i++) {
        entry = (fn_1_76BF8_ScreenEffectEntry *)((u8 *)&lbl_1_bss_6C8EC + i * 0x10C);
        if (entry->unk_DC != 0) {
            fn_1_76C60();
        }
    }
}
/* fzgx:end fn_1_76BF8 */

/* fzgx:begin fn_1_76C60 */
typedef struct {
    u8 pad_0[0xa0];
    u32 unk_a0[5];
    u32 unk_b4[5];
    s32 unk_c8[5];
    u32 unk_dc;
    u32 unk_e0;
    f32 unk_e4;
    u16 unk_e8;
    u16 unk_ea;
    u16 unk_ec;
    u16 unk_ee;
    u16 unk_f0;
    u16 unk_f2;
    u32 unk_f4;
    u16 unk_f8;
    u16 unk_fa;
    u16 unk_fc;
    u16 unk_fe;
    u16 unk_100;
    u16 unk_102;
    u32 unk_104;
    u8 unk_108;
} FnScreenEffect;

// Clears the active screen-effect state and resets its rendering parameters.
void fn_1_76C60(FnScreenEffect *arg) {
    u8 i;
    u16 value;

    lbl_1_bss_6C8E8 = fn_80008E84(lbl_1_bss_6C8E4);
    i = 0;
    while (i < ((u8 *)&lbl_1_data_1D9B8)[arg->unk_dc * 6 + 5]) {
        if (arg->unk_c8[i] == 0) {
            fn_1_46B4(lbl_801A6410, arg->unk_a0[i], lbl_1_data_1DAC0, 0x9a1);
            arg->unk_a0[i] = 0;
        }
        i++;
    }
    fn_80008E84(lbl_1_bss_6C8E8);
    arg->unk_f2 = 0;
    arg->unk_f0 = 0;
    arg->unk_ea = 0;
    arg->unk_e8 = 0;
    arg->unk_ec = 0x280;
    arg->unk_ee = 0x1e0;
    arg->unk_f4 = 0;
    arg->unk_fa = 0;
    arg->unk_f8 = 0;
    arg->unk_100 = 0x280;
    arg->unk_fc = 0x280;
    value = fn_1_A5D9C();
    arg->unk_102 = value;
    arg->unk_fe = value;
    arg->unk_dc = 0;
    arg->unk_e0 = 0;
    arg->unk_e4 = lbl_1_rodata_31AC;
    arg->unk_104 = 0;
    arg->unk_108 = 0;
    arg->unk_a0[0] = 0;
    arg->unk_c8[0] = 0;
    arg->unk_a0[1] = 0;
    arg->unk_c8[1] = 0;
    arg->unk_a0[2] = 0;
    arg->unk_c8[2] = 0;
    arg->unk_a0[3] = 0;
    arg->unk_c8[3] = 0;
    arg->unk_a0[4] = 0;
    arg->unk_c8[4] = 0;
    fn_1_76DBC();
}
/* fzgx:end fn_1_76C60 */

/* fzgx:begin fn_1_76DBC */
// fn_1_76DBC: empty in retail (single blr).
void fn_1_76DBC(void) {
}
/* fzgx:end fn_1_76DBC */

/* fzgx:begin fn_1_77200 */
void fn_1_77200(void *arg) {
    fn_1_77238();
    fn_1_772E0();
    fn_1_77384(arg);
}
/* fzgx:end fn_1_77200 */

/* fzgx:begin fn_1_77238 */
void fn_1_77238(void) {
    fn_80072864(2);
    fn_800745A4(0, 1, 4, 30, 0, 125);
    fn_80074660(1);
    fn_80073678(1);
    fn_80073898(1);
    fn_80074788(0);
    fn_800738E0(0, 0, 1);
    fn_80073D60(0, 0, 1, 0, 1);
    fn_800734A8(0, 0, 0, 255);
    fn_80072EDC(0, 3);
}
/* fzgx:end fn_1_77238 */

/* fzgx:begin fn_1_772E0 */
void fn_1_772E0(void) {
    f32 first[16];
    f32 second[8];
    f32 values[6];

    lbl_8006D784(&first[4]);
    values[0] = lbl_1_rodata_31B0[0] * first[4];
    values[1] = lbl_1_rodata_31B0[0] * first[5];
    values[2] = *(const f32 *)&lbl_1_rodata_31A0;
    values[3] = lbl_1_rodata_31B0[0] * first[8];
    values[4] = lbl_1_rodata_31B0[0] * first[9];
    values[5] = *(const f32 *)&lbl_1_rodata_31A0;
    fn_80073A58(1, values, 1);
    fn_800739E0(0, 0, 0);
    lbl_8006D784(second);
    GXLoadTexMtxImm(second, 30, 1);
}
/* fzgx:end fn_1_772E0 */

/* fzgx:begin fn_1_7879C */
extern const f32 lbl_1_rodata_323C;
extern const f64 lbl_1_rodata_31D8;

u8 fn_1_7879C(u32 arg0) {
    s32 v0;

    v0 = (s32)(lbl_1_rodata_323C * (f32)(s32)((arg0 - 0x1000000) + 2048));
    return (u8)(v0 < 0 ? 0 : (v0 <= 255 ? v0 : 0xff));
}
/* fzgx:end fn_1_7879C */

/* fzgx:begin fn_1_78950 */
// Reset the screen effect state and refresh its processing stages twice.
void fn_1_78950(void) {
    int i;

    lbl_1_bss_6D14C.unk_0 = 1;
    for (i = 0; i < 2; i++) {
        fn_8006FDEC();
        fn_8006FEFC();
        fn_8006FD1C();
    }
}
/* fzgx:end fn_1_78950 */

/* fzgx:begin fn_1_7899C */
// Reset the screen-effect state before the next effect begins.
void fn_1_7899C(void) {
    lbl_1_bss_6D14C.unk_0 = 0;
}
/* fzgx:end fn_1_7899C */

/* fzgx:begin fn_1_789AC */
void fn_1_789AC(void) {
    fn_1_79810();
    fn_1_79948();
    fn_1_791B0();
    fn_1_9A1E8();
    lbl_1_data_1DFA4.unk_4 = 0;
}
/* fzgx:end fn_1_789AC */

/* fzgx:begin fn_1_79100 */
// Release the active screen-effect resources and reset the effect state.
void fn_1_79100(void) {
    fn_1_9A864();

    if (!fn_1_7B074()) {
        if (lbl_1_bss_6D770 != 0 || lbl_1_bss_6D774 != 0) {
            fn_8006FDEC();
        }

        if (lbl_1_bss_6D770 != 0) {
            fn_80071718((void *)lbl_1_bss_6D770);
            lbl_1_bss_6D770 = 0;
        }

        if (lbl_1_bss_6D774 != 0) {
            fn_800711A8((void *)lbl_1_bss_6D774);
            lbl_1_bss_6D774 = 0;
        }
    }

    fn_1_14CB4();
    fn_1_FA84();
    lbl_1_data_1DFA4.unk_8 = -1;
}
/* fzgx:end fn_1_79100 */

/* fzgx:begin fn_1_79810 */
typedef struct {
    f32 unk_0;
    f32 unk_4;
    f32 unk_8;
    s16 unk_C;
    s16 unk_E;
    s16 unk_10;
    u8 pad_12[0x6];
    f32 unk_18;
    f32 unk_1C;
    f32 unk_20;
    u8 pad_24[0xd0];
    void *unk_F4;
    u8 pad_F8[0xc];
    u32 unk_104;
} ScreenEffectSource;

extern void fn_80008BEC(void *arg0, s32 arg1, u32 arg2);
extern void lbl_8006D758(void);
extern void lbl_8006DB74(void *arg);
extern void lbl_8006E0C8(void *arg);

void fn_1_79810(void) {
    u32 source_flags;
    Obj_1_bss_3BE4 *dst;
    ScreenEffectSource *src;
    s32 i;

    i = 0;
    dst = *(Obj_1_bss_3BE4 **)&lbl_1_bss_3BE4;
    src = (ScreenEffectSource *)lbl_1_bss_3BE0->unk_1C;
    while (i < (s32)lbl_1_bss_3BE0->unk_18) {
        source_flags = dst->unk_9C;
        fn_80008BEC(dst, 0, 0xa0);
        dst->unk_9C = source_flags;
        dst->unk_8 = src->unk_0;
        dst->unk_C = src->unk_4;
        dst->unk_10 = src->unk_8;
        dst->unk_14 = src->unk_0 - src->unk_18;
        dst->unk_18 = src->unk_4 - src->unk_1C;
        dst->unk_1C = src->unk_8 - src->unk_20;
        dst->unk_20 = src->unk_C;
        dst->unk_22 = src->unk_E;
        dst->unk_24 = src->unk_10;
        dst->unk_26 = src->unk_C;
        dst->unk_28 = src->unk_E;
        dst->unk_2A = src->unk_10;
        lbl_8006D758();
        lbl_8006DB74((u8 *)dst + 0x2c);
        lbl_8006E0C8((u8 *)src + 0x18);
        lbl_8006DB74((u8 *)dst + 0x5c);
        if (src->unk_F4 != 0) {
            dst->unk_98 = *(f32 *)((u8 *)src->unk_F4 + 0xc);
        }
        source_flags = src->unk_104;
        dst->unk_0 |= source_flags;
        i++;
        src = (ScreenEffectSource *)((u8 *)src + 0x4b0);
        dst = (Obj_1_bss_3BE4 *)((u8 *)dst + 0xa0);
    }
}
/* fzgx:end fn_1_79810 */

/* fzgx:begin fn_1_79C88 noprologue */
#include "types.h"

typedef struct {
    u32 flags;
    s32 count;
    void *nodes;
} EffectManager;

typedef struct {
    u32 type;
    u32 unk04;
    void *resource;
    f32 threshold;
} EffectNode;

typedef struct {
    u8 unk00[0x14];
    f32 scale;
} EffectData;

typedef struct {
    u8 unk00[0x8];
    f32 angle;
} EffectResult;

typedef struct {
    u8 unk00[0x2c];
    f32 value;
} GlobalData;

extern f32 lbl_1_rodata_3278[20];
extern GlobalData *lbl_801A6D00;
extern void lbl_8006E1B0(void *arg0, void *arg1);
extern f32 fn_1_A71AC(void);

static inline f32 fn_1_79C88_operand(f32 left, f32 right) { return left * right; }
s32 fn_1_79C88(EffectManager *manager, u32 *out, s32 reverse, f32 value) {
    void * fzgx_live;
    EffectData *data;
    f32 *rodata = lbl_1_rodata_3278;
    EffectNode *node;
    EffectResult result;
    f32 phase;
    f32 limit;
    f32 inv;
    f32 factor;
    f32 tmp;
    s32 index;
    s32 i;

    node = (EffectNode *)manager->nodes;
    data = (EffectData *)node->resource;
    if (((0) == (data))) {
        return 0;
    }

    lbl_8006E1B0((u8 *)data + 8, &result);
    phase = -result.angle;
    limit = -lbl_801A6D00->value;
    if ((manager->flags & 2) != 0) {
        if (limit < rodata[43]) {
            index = 0;
        } else {
            index = 0;
            while (index < manager->count) {
                if (limit < node->threshold) {
                    break;
                }
                index++;
                node++;
            }
        }
    } else {
        if (phase < rodata[43]) {
            index = 0;
        } else {
            tmp = rodata[44] * data->scale;
            value = tmp * value;
            factor = phase * fn_1_A71AC();
            inv = rodata[32];
            index = 0;
            while (index < manager->count) {
                if (value > fn_1_79C88_operand((node->threshold / inv), (factor))) {
                    break;
                }
                index++;
                node++;
            }
        }
    }

    if (node->resource != 0 && index < manager->count) {
        if (reverse != 0) {
            for (i = index; i < manager->count; i++) {
                if (node->resource == 0) {
                    break;
                }
                node++;
            }
            node--;
        }
        if (out != 0) {
            *out = node->type;
        }
        fzgx_live = node->resource;
        return (s32)fzgx_live;
    }
    if (out != 0) {
        *out = 0;
    }
    return 0;
}
/* fzgx:end fn_1_79C88 */

/* fzgx:begin fn_1_7A648 */
void fn_1_7A648(void *arg0) {
    fn_1_79C88(arg0, 0, lbl_1_rodata_32CC, 0);
}
/* fzgx:end fn_1_7A648 */

/* fzgx:begin fn_1_7A67C */
typedef struct {
    u32 flags;
    s32 count;
    void *entries;
} EffectTable;

typedef struct {
    u8 unk00[0x8];
    void *value;
    u32 unk0c;
} EffectEntry;

void *fn_1_7A67C(EffectTable *table) {
    s32 index;
    EffectEntry *entry;

    index = table->count - 1;
    if ((table->flags & 1) != 0) {
        index--;
    }
    if ((table->flags & 0x40) != 0) {
        index -= 2;
    }
    entry = (EffectEntry *)table->entries;
    entry += index;
    return entry->value;
}
/* fzgx:end fn_1_7A67C */

/* fzgx:begin fn_1_7A9B8 */
typedef struct {
    u8 pad_0[0xf4];
    void *resource;
    u8 pad_f8[0x4b0 - 0xf8];
} fn_1_7A9B8_ScreenEffect;

typedef struct {
    u8 pad_0[0x2c];
    u8 reset_data[0x60];
    u8 load_data[0x14];
} fn_1_7A9B8_ScreenEffectEntry;

// Resets the active screen-effect entries and releases each attached resource.
void fn_1_7A9B8(void) {
    fn_1_7A9B8_ScreenEffectEntry *entry;
    fn_1_7A9B8_ScreenEffect *effect;
    s32 i;

    i = 0;
    entry = (fn_1_7A9B8_ScreenEffectEntry *)lbl_1_bss_3BE4.unk_0;
    effect = (fn_1_7A9B8_ScreenEffect *)lbl_1_bss_3BE0->unk_1C;
    while (i < (s32)lbl_1_bss_3BE0->unk_18) {
        if (effect->resource != 0) {
            lbl_8006DBAC(&entry->reset_data);
            lbl_8006E1B0(effect->resource, &entry->load_data);
        }
        i++;
        entry++;
        effect++;
    }
}
/* fzgx:end fn_1_7A9B8 */

/* fzgx:begin fn_1_7B054 */
// Return the current screen effect value.
s16 fn_1_7B054(void) {
    return lbl_1_data_1DFA4.unk_8;
}
/* fzgx:end fn_1_7B054 */

/* fzgx:begin fn_1_7B064 */
u32 fn_1_7B064(void) {
    return lbl_1_bss_6D774;
}
/* fzgx:end fn_1_7B064 */

/* fzgx:begin fn_1_7B074 */
u8 fn_1_7B074(void) {
    return lbl_1_bss_6D600.unk_0;
}
/* fzgx:end fn_1_7B074 */

/* fzgx:begin fn_1_7B084 */
void fn_1_7B084(void *object, int value) {
    char text_a[32];
    char text_b[32];
    const char *data = (const char *)&lbl_1_data_1DCF0;

    sprintf(text_a, data + 0x7d0, data + 0x7e0, object);
    sprintf(text_b, data + 0x7e8, data + 0x7e0, object);
    if (value == 0) {
        fn_1_465D0(text_a, 1);
        fn_1_465D0(text_b, 1);
        fn_1_14D5C(object, 0);
    } else {
        fn_1_465D0(text_a, 2);
        fn_1_465D0(text_b, 2);
        fn_1_14D5C(object, 1);
    }
    fn_1_46EA8(value);
    fn_1_12620(object);
    sprintf(text_a, data + 0x7f8, object);
    fn_1_465D0(text_a, 1);
    fn_1_46EA8(0);
}
/* fzgx:end fn_1_7B084 */

/* fzgx:begin fn_1_7B184 */
void fn_1_7B184(void *arg) {
    char buf_48[0x20];
    char buf_28[0x20];
    char buf_08[0x20];
    u8 *base = (u8 *)&lbl_1_data_1DCF0;

    sprintf(buf_48, (const char *)(base + 0x7d0), (const char *)(base + 0x7e0), arg);
    sprintf(buf_28, (const char *)(base + 0x7e8), (const char *)(base + 0x7e0), arg);
    sprintf(buf_08, (const char *)(base + 0x810), arg);

    fn_1_46DC4(buf_48);
    fn_1_46DC4(buf_28);
    fn_1_46DC4(buf_08);
}
/* fzgx:end fn_1_7B184 */

/* fzgx:begin fn_1_7B218 noprologue */
#include "types.h"
#include "rel/main_rel/screen_effect.h"

typedef struct {
    u8 pad_0[0x7e0];
    char unk_7e0[0x4c];
    char unk_82c[0x14];
    char unk_840[0x20];
} ScreenEffectData;

extern u16 fn_1_12EF24(s16 value, s16 index);
extern void sprintf(char *dst, const char *format, const char *text, ...);
extern void fn_1_465D0(char *text, s32 mode);

void fn_1_7B218(s32 enabled) {
    char text_a[0x20];
    char text_b[0x20];
    s32 i;
    s16 index;
    ScreenEffectData *data = (ScreenEffectData *)&lbl_1_data_1DCF0;

    i = 0;
    do {
        index = fn_1_12EF24(lbl_1_bss_8B3A0.unk_8C, i);
        if (index >= 0) {
            sprintf(text_a, data->unk_82c, data->unk_7e0, index);
            sprintf(text_b, data->unk_840, data->unk_7e0, index);
            if (enabled == 0) {
                fn_1_465D0(text_a, 1);
                fn_1_465D0(text_b, 1);
            } else {
                fn_1_465D0(text_a, 2);
                fn_1_465D0(text_b, 2);
            }
        }
        i++;
    } while (i < 6);
}
/* fzgx:end fn_1_7B218 */

/* fzgx:begin fn_1_7B4C0 */
// Releases active screen effects and resets the effect state.
void fn_1_7B4C0(void) {
    if (lbl_1_bss_6D770 != 0 || lbl_1_bss_6D774 != 0) {
        fn_8006FDEC();
    }

    if (lbl_1_bss_6D770 != 0) {
        fn_80071718((void *)lbl_1_bss_6D770);
        lbl_1_bss_6D770 = 0;
    }

    if (lbl_1_bss_6D774 != 0) {
        fn_800711A8((void *)lbl_1_bss_6D774);
        lbl_1_bss_6D774 = 0;
    }

    lbl_1_data_1DFA4.unk_8 = -1;
}
/* fzgx:end fn_1_7B4C0 */
