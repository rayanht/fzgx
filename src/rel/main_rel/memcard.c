#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/memcard.h"
extern void* lbl_801A6410;
extern int fn_1_45D0(void *arg0, int arg1, Obj_1_data_3C7B8 *arg2, int arg3);
extern void fn_1_AB45C(void);
extern void CARDMountAsync(u8, u32, void (*)(void), s32);
extern int CARDGetSerialNo(u8 value, void *data);
extern void CARDCheckAsync(u8 byte_val, int value);
extern void CARDFormatAsync(u8 byte, int value);
extern const f32 lbl_1_rodata_4CA8;
extern const f64 lbl_1_rodata_4CB0;
extern const f32 lbl_1_rodata_4CAC;
extern void fn_80083DB0(void *dst, void *src);
extern void strcat(void *dst, void *src);
extern void CARDDeleteAsync(u8 byte, void *data, int arg);
extern s32 CARDFreeBlocks(u8 byte_val, void *arg1, void *arg2);
extern s32 CARDOpen(u8 byte_val, void *arg1, void *arg2);
extern void CARDFastDeleteAsync(u8 byte_val, void *arg, s32 zero);
extern void CARDCreateAsync(u8 byte_val, void *arg1, void *arg2, void *arg3, u32 arg4);
extern void CARDSetStatusAsync(u8 id, void *arg, void *data, int zero);
extern void CARDRenameAsync(u8 id, void *data1, void *data2, int zero);
extern void CARDReadAsync(void *arg0, void *arg1, void *arg2, int arg3, int arg4);
extern const f64 lbl_1_rodata_4CC8;
extern void fn_80030754(u8 value, void *data, int size, int mode);
extern u8 lbl_1_bss_71810[161];
extern u8 lbl_1_bss_718B8;
extern u8 lbl_1_bss_718B9[7];
extern int fn_8002A744(void);
extern void fn_8002A74C(u16 value);
extern int fn_8002DFE0(int arg0, u32 arg1, int arg2);
extern int CARDCheck(int arg0);
extern void fn_1_B9C38(s32 index);
extern void fn_1_1596DC(u32);
extern void fn_1_484CC(u32);
extern void fn_80008BEC(void *dst, s32 value, s32 size);
extern void fn_1_AA6D8(s32 arg0, u32 arg1, void *arg2);
extern void fn_1_F755C(u8 value);
extern void fn_1_A6840(u8 value);
extern void OSPanic(void *arg0, u32 arg1, ...);
extern void fn_1_F79C8(void);
extern void *lbl_801A6410;
extern void strncpy(void *arg0, void *arg1, int arg2);
extern u32 lbl_1_bss_77310[28];
extern u32 lbl_1_bss_7730C;
extern u8 lbl_1_bss_772C8[66];
extern u32 fn_1_4630(void *heap, u32 size, void *file, s32 line);
extern s32 fn_8002FC14(s32 chan, void *fileName);
extern s32 fn_80030338(s32 chan, void *oldName, void *newName);

/* fzgx:begin fn_1_AB478 */
#include "rel/main_rel/memcard.h"

typedef struct {
    u8 pad_0[2];
    u16 unk_2;
} Fn1AB478Sub;

typedef struct {
    u8 unk_0;
    u8 pad_1[6];
    u8 unk_7;
    u8 pad_8[4];
    u32 unk_C;
    u8 pad_10[0x14];
    Fn1AB478Sub *unk_24;
} Fn1AB478Obj;

void fn_1_AB478(Fn1AB478Obj *obj) {
    obj->unk_C = fn_1_45D0((void *)lbl_801A6410, 0xA000,
                           &lbl_1_data_3C7B8, 0x657);
    obj->unk_24->unk_2 = 0x12c;
    obj->unk_7 = 0;
    CARDMountAsync(obj->unk_0, obj->unk_C, fn_1_AB45C, 0);
}
/* fzgx:end fn_1_AB478 */

/* fzgx:begin fn_1_AB4F4 */
typedef struct {
    u8 pad[0x2];
    s16 field_0x2;
    int field_0x4;
} StatusStruct;

typedef struct {
    u8 byte_0;
    s8 byte_1;
    u8 pad[0x22];
    StatusStruct *ptr_0x24;
    u8 pad2[0x70];
    int field_0x98;
    int field_0x9c;
} fn_1_AB4F4_ArgStruct;

void fn_1_AB4F4(fn_1_AB4F4_ArgStruct *arg) {
    int status;

    status = CARDGetResultCode(arg->byte_0);
    arg->ptr_0x24->field_0x4 = status;
    if (arg->ptr_0x24->field_0x4 == -3 && arg->byte_1 == -2) {
        arg->ptr_0x24->field_0x4 = arg->byte_1;
    }
    if (arg->ptr_0x24->field_0x4 != -1 &&
        CARDGetSerialNo(arg->byte_0, &arg->field_0x98)) {
        arg->field_0x9c = 0;
        arg->field_0x98 = 0;
    }
    if (arg->ptr_0x24->field_0x4 != -1) {
        arg->ptr_0x24->field_0x2 = 0;
    }
}
/* fzgx:end fn_1_AB4F4 */

/* fzgx:begin fn_1_AB598 */
typedef struct {
    u8 pad[0x2];
    u16 field_0x2;
} fn_1_AB598_OffsetStruct;

typedef struct {
    u8 byte_0;
    u8 pad[0x23];
    fn_1_AB598_OffsetStruct *ptr_0x24;
} fn_1_AB598_ArgStruct;

void fn_1_AB598(fn_1_AB598_ArgStruct *arg) {
    arg->ptr_0x24->field_0x2 = 300;
    CARDCheckAsync(arg->byte_0, 0);
}
/* fzgx:end fn_1_AB598 */

/* fzgx:begin fn_1_AB5CC */
typedef struct {
    u8 pad[0x2];
    u16 field_0x2;
    s32 field_0x4;
} fn_1_AB5CC_OffsetStruct;

typedef struct {
    u8 byte_0;
    u8 pad[0x23];
    fn_1_AB5CC_OffsetStruct *ptr_0x24;
} fn_1_AB5CC_ArgStruct;

// fn_1_AB5CC: main_rel .text:0x000AB5CC size 0x50
// Load byte from arg, call CARDGetResultCode, store result at struct offset 0x4, clear offset 0x2 if not -1.

void fn_1_AB5CC(fn_1_AB5CC_ArgStruct *arg) {
    u8 byte_val = arg->byte_0;
    int result = CARDGetResultCode(byte_val);
    
    fn_1_AB5CC_OffsetStruct *s = arg->ptr_0x24;
    s->field_0x4 = result;
    
    s = arg->ptr_0x24;
    if (s->field_0x4 != -1) {
        s->field_0x2 = 0;
    }
}
/* fzgx:end fn_1_AB5CC */

/* fzgx:begin fn_1_AB61C */
typedef struct {
    u8 pad[1];
    u8 field_0x1;
} fn_1_AB61C_MemcardState;

typedef struct {
    u8 pad_0x24[0x24];
    fn_1_AB61C_MemcardState *state;
    u8 pad_0x2a[0x2];
    u8 field_0x2a;
} fn_1_AB61C_MemcardArg;

void fn_1_AB61C(fn_1_AB61C_MemcardArg *arg) {
    fn_1_AB61C_MemcardState *state = arg->state;
    state->field_0x1 = 1;
    *(s16 *)((u8 *)arg + 0x8) = -1;
    *(s16 *)((u8 *)arg + 0xa) = -1;
    arg->field_0x2a = arg->field_0x2a & 0xFE;
    arg->field_0x2a = 0;
}
/* fzgx:end fn_1_AB61C */

/* fzgx:begin fn_1_AB75C */
typedef struct {
    u8 pad[0x2];
    u16 field_0x2;
} fn_1_AB75C_OffsetStruct;

typedef struct {
    u8 byte_0;
    u8 pad_0x1[0x23];
    fn_1_AB75C_OffsetStruct *ptr_0x24;
    u8 pad_0x28[0x2];
    u8 flags_0x2a;
    u8 pad_0x2b[0x5];
    s32 field_0x30;
    u8 pad_0x34[0x4];
    f32 field_0x38;
} fn_1_AB75C_ArgStruct;

// fn_1_AB75C: main_rel .text:0x000AB75C size 0x68
void fn_1_AB75C(fn_1_AB75C_ArgStruct *arg) {
    arg->ptr_0x24->field_0x2 = 0x12c;
    arg->field_0x30 = fn_8002C0A0(arg->byte_0);
    arg->field_0x38 = lbl_1_rodata_4CA8;
    arg->flags_0x2a |= 2;
    CARDFormatAsync(arg->byte_0, 0);
}
/* fzgx:end fn_1_AB75C */

/* fzgx:begin fn_1_AB7C4 */
typedef struct {
    u8 pad[0x2];
    u16 field_0x2;
    s32 field_0x4;
} fn_1_AB7C4_OffsetStruct;

typedef struct {
    u8 byte_0;
    u8 pad_0x1[0x23];
    fn_1_AB7C4_OffsetStruct *ptr_0x24;
    u8 pad_0x28[0x2];
    u8 flags_0x2a;
    u8 pad_0x2b[0x5];
    s32 field_0x30;
    u8 pad_0x34[0x4];
    f32 field_0x38;
} fn_1_AB7C4_ArgStruct;

void fn_1_AB7C4(fn_1_AB7C4_ArgStruct *arg) {
    arg->ptr_0x24->field_0x4 = CARDGetResultCode(arg->byte_0);
    arg->field_0x38 = (fn_8002C0A0(arg->byte_0) - arg->field_0x30) / lbl_1_rodata_4CAC;
    if (arg->ptr_0x24->field_0x4 != -1) {
        arg->flags_0x2a &= ~2;
        arg->ptr_0x24->field_0x2 = 0;
        arg->flags_0x2a &= ~16;
    }
}
/* fzgx:end fn_1_AB7C4 */

/* fzgx:begin fn_1_AB870 */
typedef struct {
    u8 pad[0x2];
    u16 field_0x2;
} fn_1_AB870_OffsetStruct;

typedef struct {
    u8 pad[0x24];
    fn_1_AB870_OffsetStruct *ptr_0x24;
} fn_1_AB870_ArgStruct;

// fn_1_AB870: main_rel .text:0x000AB870 size 0x10
void fn_1_AB870(fn_1_AB870_ArgStruct *arg) {
    arg->ptr_0x24->field_0x2 = 0x12c;
}
/* fzgx:end fn_1_AB870 */

/* fzgx:begin fn_1_AB880 */
typedef struct {
    u8 pad[0x2];
    u16 field_0x2;
    s32 field_0x4;
} fn_1_AB880_OffsetStruct;

typedef struct {
    u8 byte_0;
    u8 pad[0x23];
    fn_1_AB880_OffsetStruct *ptr_0x24;
} fn_1_AB880_ArgStruct;

// fn_1_AB880: main_rel .text:0x000AB880 size 0x58
void fn_1_AB880(fn_1_AB880_ArgStruct *arg) {
    fn_1_AB880_OffsetStruct *s = arg->ptr_0x24;
    int result = CARDGetSerialNo(arg->byte_0, (u8 *)s + 0x18);

    s = arg->ptr_0x24;
    s->field_0x4 = result;

    s = arg->ptr_0x24;
    if (s->field_0x4 != -1) {
        s->field_0x2 = 0;
    }
}
/* fzgx:end fn_1_AB880 */

/* fzgx:begin fn_1_AB8D8 */
typedef struct {
    u8 byte_0;
    u8 pad_0x1[0x23];
    void *ptr_0x24;
} fn_1_AB8D8_ArgStruct;

void fn_1_AB8D8(fn_1_AB8D8_ArgStruct *arg) {
    u8 data[0x40];

    fn_80083DB0(data, (u8 *)arg->ptr_0x24 + 0x98);
    strcat(data, lbl_1_data_3C89C);
    ((u16 *)arg->ptr_0x24)[1] = 0x12c;
    CARDDeleteAsync(arg->byte_0, data, 0);
}
/* fzgx:end fn_1_AB8D8 */

/* fzgx:begin fn_1_AB93C */
typedef struct {
    u8 pad[0x2];
    u16 field_0x2;
    s32 field_0x4;
} fn_1_AB93C_OffsetStruct;

typedef struct {
    u8 byte_0;
    u8 pad[0x23];
    fn_1_AB93C_OffsetStruct *ptr_0x24;
} fn_1_AB93C_ArgStruct;

// fn_1_AB93C: main_rel .text:0x000AB93C size 0x50
void fn_1_AB93C(fn_1_AB93C_ArgStruct *arg) {
    u8 byte_val = arg->byte_0;
    int result = CARDGetResultCode(byte_val);

    fn_1_AB93C_OffsetStruct *s = arg->ptr_0x24;
    s->field_0x4 = result;

    s = arg->ptr_0x24;
    if (s->field_0x4 != -1) {
        s->field_0x2 = 0;
    }
}
/* fzgx:end fn_1_AB93C */

/* fzgx:begin fn_1_AB98C */
typedef struct {
    u8 pad[0x2];
    u16 field_0x2;
} fn_1_AB98C_OffsetStruct;

typedef struct {
    u8 pad[0x24];
    fn_1_AB98C_OffsetStruct *ptr_0x24;
} fn_1_AB98C_ArgStruct;

void fn_1_AB98C(fn_1_AB98C_ArgStruct *arg) {
    arg->ptr_0x24->field_0x2 = 300;
}
/* fzgx:end fn_1_AB98C */

/* fzgx:begin fn_1_AB99C */
typedef struct {
    u8 pad[0x2];
    u16 field_0x2;
    s32 field_0x4;
    s32 field_0x8;
    u8 pad_0xc[0x4];
    u8 data[0x8];
} fn_1_AB99C_OffsetStruct;

typedef struct {
    u8 byte_0;
    u8 pad[0x23];
    fn_1_AB99C_OffsetStruct *ptr_0x24;
} fn_1_AB99C_ArgStruct;

void fn_1_AB99C(fn_1_AB99C_ArgStruct *arg) {
    s32 result = CARDFreeBlocks(arg->byte_0, arg->ptr_0x24->data,
        &arg->ptr_0x24->data[0x4]);
    arg->ptr_0x24->field_0x4 = result;
    if (arg->ptr_0x24->field_0x4 == 0) {
        arg->ptr_0x24->field_0x8 |= 0x80;
    }
    if (arg->ptr_0x24->field_0x4 != -1) {
        arg->ptr_0x24->field_0x2 = 0;
    }
}
/* fzgx:end fn_1_AB99C */

/* fzgx:begin fn_1_ABA14 */
typedef struct {
    u8 pad[0x2];
    u16 field_0x2;
} fn_1_ABA14_OffsetStruct;

typedef struct {
    u8 pad[0x24];
    fn_1_ABA14_OffsetStruct *ptr_0x24;
} fn_1_ABA14_ArgStruct;

void fn_1_ABA14(fn_1_ABA14_ArgStruct *arg) {
    arg->ptr_0x24->field_0x2 = 0x12c;
}
/* fzgx:end fn_1_ABA14 */

/* fzgx:begin fn_1_ABA24 */
typedef struct {
    u8 pad[0x2];
    u16 field_0x2;
    s32 field_0x4;
    s32 field_0x8;
    u8 pad_0xc[0x4];
    u8 data[0x8];
} fn_1_ABA24_OffsetStruct;

typedef struct {
    u8 byte_0;
    u8 pad[0x23];
    fn_1_ABA24_OffsetStruct *ptr_0x24;
} fn_1_ABA24_ArgStruct;

void fn_1_ABA24(fn_1_ABA24_ArgStruct *arg) {
    s32 result = CARDFreeBlocks(arg->byte_0, arg->ptr_0x24->data,
        &arg->ptr_0x24->data[0x4]);
    arg->ptr_0x24->field_0x4 = result;
    if (arg->ptr_0x24->field_0x4 == 0) {
        arg->ptr_0x24->field_0x8 |= 0x80;
    }
    if (arg->ptr_0x24->field_0x4 != -1) {
        arg->ptr_0x24->field_0x2 = 0;
    }
}
/* fzgx:end fn_1_ABA24 */

/* fzgx:begin fn_1_ABA9C */
typedef struct {
    u8 pad[0x2];
    u16 field_0x2;
} fn_1_ABA9C_OffsetStruct;

typedef struct {
    u8 pad[0x24];
    fn_1_ABA9C_OffsetStruct *ptr_0x24;
} fn_1_ABA9C_ArgStruct;

void fn_1_ABA9C(fn_1_ABA9C_ArgStruct *arg) {
    arg->ptr_0x24->field_0x2 = 0x12c;
}
/* fzgx:end fn_1_ABA9C */

/* fzgx:begin fn_1_ABAAC */
typedef struct {
    u8 pad[0x2];
    u16 field_0x2;
    s32 field_0x4;
} fn_1_ABAAC_ResultStruct;

typedef struct {
    u8 byte_0;
    u8 pad_0x1[0xf];
    u8 data_0x10[0x14];
    fn_1_ABAAC_ResultStruct *ptr_0x24;
} fn_1_ABAAC_ArgStruct;

void fn_1_ABAAC(fn_1_ABAAC_ArgStruct *arg) {
    u8 local[0x40];

    fn_80083DB0(local, (u8 *)arg->ptr_0x24 + 0x98);
    strcat(local, lbl_1_data_3C7C4);
    arg->ptr_0x24->field_0x4 =
        CARDOpen(arg->byte_0, local, arg->data_0x10);
    if (arg->ptr_0x24->field_0x4 != -1) {
        arg->ptr_0x24->field_0x2 = 0;
    }
}
/* fzgx:end fn_1_ABAAC */

/* fzgx:begin fn_1_ABB24 */
typedef struct {
    u8 pad_0x0[0x1];
    u8 field_0x1;
    u8 pad_0x2[0x6];
    s16 field_0x8;
    s16 field_0xa;
} fn_1_ABB24_MemcardState;

typedef struct {
    u8 pad_0x0[0x8];
    s16 field_0x8;
    s16 field_0xa;
    u8 pad_0xc[0x18];
    fn_1_ABB24_MemcardState *ptr_0x24;
    u8 pad_0x28[0x2];
    u8 field_0x2a;
} fn_1_ABB24_MemcardArg;

void fn_1_ABB24(fn_1_ABB24_MemcardArg *arg) {
    arg->ptr_0x24->field_0x1 = 1;
    arg->field_0x8 = -1;
    arg->field_0xa = -1;
    arg->field_0x2a &= 0xfe;
}
/* fzgx:end fn_1_ABB24 */

/* fzgx:begin fn_1_ABC5C */
typedef struct {
    u8 byte_0;
    u8 pad_0x1[0x13];
    void *field_0x14;
} fn_1_ABC5C_ArgStruct;

typedef struct {
    u8 pad[0x2];
    u16 field_0x2;
} fn_1_ABC5C_ResultStruct;

typedef struct {
    u8 pad[0x24];
    fn_1_ABC5C_ResultStruct *ptr_0x24;
} StateStruct;

void fn_1_ABC5C(fn_1_ABC5C_ArgStruct *arg) {
    StateStruct *state;

    state = (StateStruct *)arg;
    state->ptr_0x24->field_0x2 = 0x12c;
    CARDFastDeleteAsync(arg->byte_0, arg->field_0x14, 0);
}
/* fzgx:end fn_1_ABC5C */

/* fzgx:begin fn_1_ABC98 */
typedef struct {
    u8 pad[0x2];
    u16 field_0x2;
    s32 field_0x4;
} fn_1_ABC98_ResultStruct;

typedef struct {
    u8 byte_0;
    u8 pad_0x1[0x23];
    fn_1_ABC98_ResultStruct *ptr_0x24;
} fn_1_ABC98_ArgStruct;

void fn_1_ABC98(fn_1_ABC98_ArgStruct *arg) {
    arg->ptr_0x24->field_0x4 = CARDGetResultCode(arg->byte_0);
    if (arg->ptr_0x24->field_0x4 != -1) {
        arg->ptr_0x24->field_0x2 = 0;
    }
}
/* fzgx:end fn_1_ABC98 */

/* fzgx:begin fn_1_ABCE8 */
typedef struct {
    u8 pad[0x2];
    u16 field_0x2;
    u8 pad_0x4[0x8];
    void *ptr_0xc;
} fn_1_ABCE8_ResultStruct;

typedef struct {
    u8 byte_0;
    u8 pad_0x1[0xf];
    u8 data_0x10[0x14];
    fn_1_ABCE8_ResultStruct *ptr_0x24;
} fn_1_ABCE8_ArgStruct;

void fn_1_ABCE8(fn_1_ABCE8_ArgStruct *arg) {
    u8 local[0x40];

    fn_80083DB0(local, (u8 *)arg->ptr_0x24 + 0x98);
    strcat(local, lbl_1_data_3C89C);
    arg->ptr_0x24->field_0x2 = 0x12c;
    CARDCreateAsync(arg->byte_0, local, arg->ptr_0x24->ptr_0xc,
        arg->data_0x10, 0);
}
/* fzgx:end fn_1_ABCE8 */

/* fzgx:begin fn_1_ABD58 */
typedef struct {
    u8 pad[0x2];
    u16 field_0x2;
    s32 field_0x4;
} fn_1_ABD58_ResultStruct;

typedef struct {
    u8 byte_0;
    u8 pad_0x1[0x23];
    fn_1_ABD58_ResultStruct *ptr_0x24;
} fn_1_ABD58_ArgStruct;

void fn_1_ABD58(fn_1_ABD58_ArgStruct *arg) {
    arg->ptr_0x24->field_0x4 = CARDGetResultCode(arg->byte_0);
    if (arg->ptr_0x24->field_0x4 != -1) {
        arg->ptr_0x24->field_0x2 = 0;
    }
}
/* fzgx:end fn_1_ABD58 */

/* fzgx:begin fn_1_ABDA8 */
typedef struct {
    u8 pad[0x2];
    u16 field_0x2;
} fn_1_ABDA8_OffsetStruct;

typedef struct {
    u8 pad[0x24];
    fn_1_ABDA8_OffsetStruct *ptr_0x24;
} fn_1_ABDA8_ArgStruct;

void fn_1_ABDA8(fn_1_ABDA8_ArgStruct *arg) {
    arg->ptr_0x24->field_0x2 = 0x12c;
}
/* fzgx:end fn_1_ABDA8 */

/* fzgx:begin fn_1_ABDB8 */
#include "rel/main_rel/globals.h"

typedef struct {
    u8 pad_0x0[0x2];
    u16 unk_0x2;
    s32 unk_0x4;
    u8 pad_0x8[0x18];
    u8 unk_0x20[1];
} fn_1_ABDB8_ResultStruct;

typedef struct {
    u8 byte_0x0;
    u8 pad_0x1[0x13];
    void *ptr_0x14;
    u8 pad_0x18[0xc];
    fn_1_ABDB8_ResultStruct *ptr_0x24;
} fn_1_ABDB8_ArgStruct;

// Loads the payload into its result buffer and clears the stale offset on success.
void fn_1_ABDB8(fn_1_ABDB8_ArgStruct *arg) {
    arg->ptr_0x24->unk_0x4 =
        CARDGetStatus(arg->byte_0x0, arg->ptr_0x14, arg->ptr_0x24->unk_0x20);
    if (arg->ptr_0x24->unk_0x4 != -1) {
        arg->ptr_0x24->unk_0x2 = 0;
    }
}
/* fzgx:end fn_1_ABDB8 */

/* fzgx:begin fn_1_ABE14 */
typedef struct Fn1ABE14Sub {
    u8 pad_00[0x2];
    u16 value;
    u8 pad_04[0x8];
    void *arg_0xC;
    u8 pad_10[0x84];
    void *arg_0x94;
} Fn1ABE14Sub;

typedef struct Fn1ABE14Arg {
    u8 id;
    u8 pad_01[0x23];
    Fn1ABE14Sub *sub;
    u8 pad_28[0x2];
    u8 flags;
    u8 pad_2B[0x4];
    s32 result;
    u8 pad_34[0x4];
    f32 value;
    u8 pad_3C[0x58];
} Fn1ABE14Arg;

extern s32 fn_8002C0A0(u8 id);
extern void CARDWriteAsync(void *data, void *arg_0x94, void *arg_0xC, int zero_1, int zero_2);

void fn_1_ABE14(Fn1ABE14Arg *arg) {
    arg->sub->value = 300;
    arg->result = fn_8002C0A0(arg->id);
    arg->value = lbl_1_rodata_4CA8;
    arg->flags |= 2;
    CARDWriteAsync((u8 *)arg + 0x10, arg->sub->arg_0x94, arg->sub->arg_0xC, 0, 0);
}
/* fzgx:end fn_1_ABE14 */

/* fzgx:begin fn_1_ABF44 */
typedef struct {
    u8 pad_00[0x2];
    u16 field_0x2;
    s32 field_0x4;
    u8 pad_08[0x84];
    void *field_0x8c;
    s32 field_0x90;
    s32 field_0x94;
    u8 field_0x98[0x10];
} Fn1ABF44State;

typedef struct {
    u8 id;
    u8 pad_01[0xF];
    u8 data_0x10[0x14];
    Fn1ABF44State *state;
    u8 pad_28[0x2];
    u8 flags_0x2a;
    u8 pad_2b[0x5];
    s32 value_0x30;
    u8 pad_34[0x4];
    f32 value_0x38;
} Fn1ABF44Object;

void fn_1_ABF44(Fn1ABF44Object *arg) {
    u8 work[0x40];
    s32 value;
    s32 size;
    s32 aligned;

    arg->state->field_0x2 = 300;
    fn_80083DB0(work, (u8 *)arg->state + 0x98);
    strcat(work, lbl_1_data_3C7C4);
    value = CARDOpen(arg->id, work, arg->data_0x10);
    arg->state->field_0x4 = value;
    arg->value_0x30 = fn_8002C0A0(arg->id);
    arg->value_0x38 = lbl_1_rodata_4CA8;
    arg->flags_0x2a |= 2;
    size = arg->state->field_0x94 +
        *(s32 *)((u8 *)arg->state->field_0x8c + 0x44);
    aligned = (*(s32 *)((u8 *)arg->state->field_0x8c + 0x48) + 0x1fff) &
        ~0x1fff;
    CARDWriteAsync(arg->data_0x10, size, aligned,
                *(s32 *)((u8 *)arg->state->field_0x8c + 0x44), 0);
}
/* fzgx:end fn_1_ABF44 */

/* fzgx:begin fn_1_AC12C */
extern int fn_1_45D0(void *arg0, int arg1, Obj_1_data_3C7B8 *arg2, int arg3);
extern void fn_1_AB45C(void);
extern void CARDMountAsync(u8, u32, void (*)(void), s32);
extern int CARDGetSerialNo(u8 value, void *data);
extern void CARDCheckAsync(u8 byte_val, int value);
extern void CARDFormatAsync(u8 byte, int value);
extern const f64 lbl_1_rodata_4CB0;
extern void fn_80083DB0(void *dst, void *src);
extern void strcat(void *dst, void *src);
extern void CARDDeleteAsync(u8 byte, void *data, int arg);
extern s32 CARDFreeBlocks(u8 byte_val, void *arg1, void *arg2);
extern s32 CARDOpen(u8 byte_val, void *arg1, void *arg2);
extern void CARDFastDeleteAsync(u8 byte_val, void *arg, s32 zero);
extern void CARDCreateAsync(u8 byte_val, void *arg1, void *arg2, void *arg3, u32 arg4);
extern void CARDSetStatusAsync(u8 id, void *arg, void *data, int zero);
extern void CARDRenameAsync(u8 id, void *data1, void *data2, int zero);
extern void CARDReadAsync(void *arg0, void *arg1, void *arg2, int arg3, int arg4);
extern const f64 lbl_1_rodata_4CC8;
extern void fn_80030754(u8 value, void *data, int size, int mode);
extern u8 lbl_1_bss_71810[161];
extern u8 lbl_1_bss_718B8;
extern u8 lbl_1_bss_718B9[7];
extern int fn_8002A744(void);
extern void fn_8002A74C(u16 value);
extern int fn_8002DFE0(int arg0, u32 arg1, int arg2);
extern int CARDCheck(int arg0);
extern void fn_1_484CC(u32);
extern void fn_80008BEC(void *dst, s32 value, s32 size);
extern void fn_1_AA6D8(s32 arg0, u32 arg1, void *arg2);
extern void fn_1_F755C(u8 value);
extern void fn_1_A6840(u8 value);
extern void OSPanic(void *arg0, u32 arg1, ...);
extern void fn_1_F79C8(void);
extern void strncpy(void *arg0, void *arg1, int arg2);
extern u32 lbl_1_bss_77310[28];
extern u32 lbl_1_bss_7730C;

typedef struct MemcardRequestState {
    u8 pad_00[0x2];
    u16 value;
    u8 pad_04[0x90];
    void *data;
} MemcardRequestState;

typedef struct MemcardRequest {
    u8 id;
    u8 pad_01[0xF];
    u8 buffer[0x14];
    MemcardRequestState *state;
    u8 pad_28[0x8];
    void *result;
} MemcardRequest;

extern void *fn_8002C0A0(u8 id);
extern void CARDWriteAsync(void *dst, void *src, int size, int zero, int flags);

// Initializes the request state, records the backing resource, and starts its transfer.
void fn_1_AC12C(MemcardRequest *request) {
    request->state->value = 300;
    request->result = fn_8002C0A0(request->id);
    CARDWriteAsync(request->buffer, request->state->data, 0x4000, 0, 0);
}
/* fzgx:end fn_1_AC12C */

/* fzgx:begin fn_1_AC294 */
typedef struct Fn1AC294State {
    u8 pad_00[0x2];
    u16 value;
} Fn1AC294State;

typedef struct Fn1AC294Target {
    u8 id;
    u8 pad_01[0x13];
    void *arg;
    u8 pad_18[0xC];
    Fn1AC294State *state;
} Fn1AC294Target;

void fn_1_AC294(Fn1AC294Target *target) {
    target->state->value = 300;
    CARDSetStatusAsync(target->id, target->arg, (u8 *)target->state + 0x20, 0);
}
/* fzgx:end fn_1_AC294 */

/* fzgx:begin fn_1_AC2D8 */
typedef struct Fn1AC2D8State {
    u8 pad_00[0x2];
    u16 value;
    s32 status;
} Fn1AC2D8State;

typedef struct Fn1AC2D8Target {
    u8 id;
    u8 pad_01[0x23];
    Fn1AC2D8State *state;
} Fn1AC2D8Target;

void fn_1_AC2D8(Fn1AC2D8Target *target) {
    target->state->status = CARDGetResultCode(target->id);
    if (target->state->status != -1) {
        target->state->value = 0;
    }
}
/* fzgx:end fn_1_AC2D8 */

/* fzgx:begin fn_1_AC328 */
typedef struct Fn1AC328State {
    u8 pad_00[0x2];
    u16 value;
    u8 pad_04[0x94];
} Fn1AC328State;

typedef struct Fn1AC328Target {
    u8 id;
    u8 pad_01[0x23];
    Fn1AC328State *state;
} Fn1AC328Target;

void fn_1_AC328(Fn1AC328Target *target) {
    u8 data[0x40];

    fn_80083DB0(data, (u8 *)target->state + 0x98);
    strcat(data, lbl_1_data_3C7C4);
    target->state->value = 300;
    CARDDeleteAsync(target->id, data, 0);
}
/* fzgx:end fn_1_AC328 */

/* fzgx:begin fn_1_AC38C */
typedef struct Fn1AC38Data {
    u8 pad_00[0x2];
    u16 value;
    int status;
} Fn1AC38Data;

typedef struct Fn1AC38Target {
    u8 id;
    u8 pad_01[0x23];
    Fn1AC38Data *data;
} Fn1AC38Target;

void fn_1_AC38C(Fn1AC38Target *target) {
    target->data->status = CARDGetResultCode(target->id);
    if (target->data->status != -1) {
        target->data->value = 0;
    }
}
/* fzgx:end fn_1_AC38C */

/* fzgx:begin fn_1_AC3DC */
typedef struct Fn1AC3DCState {
    u8 pad_00[0x2];
    u16 value;
    u8 pad_04[0x94];
} Fn1AC3DCState;

typedef struct Fn1AC3DCTarget {
    u8 id;
    u8 pad_01[0x23];
    Fn1AC3DCState *state;
} Fn1AC3DCTarget;

void fn_1_AC3DC(Fn1AC3DCTarget *target) {
    u8 data1[0x40];
    u8 data2[0x40];

    fn_80083DB0(data1, (u8 *)target->state + 0x98);
    fn_80083DB0(data2, (u8 *)target->state + 0x98);
    strcat(data1, lbl_1_data_3C89C);
    strcat(data2, lbl_1_data_3C7C4);
    target->state->value = 300;
    CARDRenameAsync(target->id, data1, data2, 0);
}
/* fzgx:end fn_1_AC3DC */

/* fzgx:begin fn_1_AC464 */
typedef struct Fn1AC464State {
    u16 pad_00;
    u16 value;
    s32 result;
} Fn1AC464State;

typedef struct Fn1AC464Target {
    u8 value;
    u8 pad_01[0x23];
    Fn1AC464State *state;
} Fn1AC464Target;

void fn_1_AC464(Fn1AC464Target *target) {
    target->state->result = CARDGetResultCode(target->value);
    if (target->state->result != -1) {
        target->state->value = 0;
    }
}
/* fzgx:end fn_1_AC464 */

/* fzgx:begin fn_1_AC4B4 */
typedef struct Fn1AC4B4Target {
    u8 pad_00[0x24];
    struct Fn1AC4B4State *state;
} Fn1AC4B4Target;

typedef struct Fn1AC4B4State {
    u8 pad_00[0x2];
    u16 value;
} Fn1AC4B4State;

void fn_1_AC4B4(Fn1AC4B4Target *target) {
    target->state->value = 300;
}
/* fzgx:end fn_1_AC4B4 */

/* fzgx:begin fn_1_AC4C4 */
typedef struct Fn1AC4C4State {
    u16 pad_00;
    u16 value_02;
    s32 result;
    u32 flags;
    u8 pad_0c[0x4];
    u8 data_10[0x4];
    u8 data_14[0x4];
} Fn1AC4C4State;

typedef struct Fn1AC4C4Target {
    u8 value;
    u8 pad_01[0x23];
    Fn1AC4C4State *state;
} Fn1AC4C4Target;

void fn_1_AC4C4(Fn1AC4C4Target *target) {
    target->state->result =
        CARDFreeBlocks(target->value, &target->state->data_10, &target->state->data_14);
    if (target->state->result == 0) {
        target->state->flags |= 0x80;
    }
    if (target->state->result != -1) {
        target->state->value_02 = 0;
    }
}
/* fzgx:end fn_1_AC4C4 */

/* fzgx:begin fn_1_AC53C noprologue */
#include "types.h"

struct fn_1_AC53C_Arg0 {
    u8 pad_0[0xC];
    u32 unk_C;
};
struct fn_1_AC53C_lbl_801A6410 {
    u32 unk_0;
};
struct fn_1_AC53C_lbl_1_bss_716C0 {
    u8 unk_0;
};
extern struct fn_1_AC53C_lbl_1_bss_716C0 lbl_1_bss_716C0;
extern struct fn_1_AC53C_lbl_801A6410 lbl_801A6410;
extern u32 lbl_1_data_3C7B8;
extern s32 CARDUnmount(void *);
extern void fn_1_46B4(u32, u32, const char *, int);

void fn_1_AC53C(void *arg0) {
    u32 temp_r4;
    u32 temp_r5_2;
    void *temp_r3;
    void *temp_r3_2;
    void *temp_r5;
    void *temp_r6;

    if ((u32) (*(u32 *)((u8 *)(arg0) + 12)) != 0) {
        do {

        } while (CARDUnmount((void *)((void *)((*(u8 *)((u8 *)(arg0) + 0))))) == -1);
        fn_1_46B4(lbl_801A6410.unk_0, *(u32 *)((u8 *)(arg0) + 12), (const char *)((s8 *) &lbl_1_data_3C7B8), 0x3C8);
        (*(s8 *)((u8 *)(arg0) + 7)) = 0;
        (*(u32 *)((u8 *)(arg0) + 12)) = 0U;
        temp_r3 = (void *)(*(void **)((u8 *)(arg0) + 36));
        (*(s32 *)((u8 *)(temp_r3) + 28)) = 0;
        (*(s32 *)((u8 *)(temp_r3) + 24)) = 0;
    }
    temp_r3_2 = (void *)(*(void **)((u8 *)(arg0) + 36));
    if ((*(s32 *)((u8 *)(temp_r3_2) + 8)) & 0x80) {
        (*(s32 *)((u8 *)(arg0) + 60)) = (s32) ((s32) (*(s32 *)((u8 *)(temp_r3_2) + 16)) / 8192);
        (*(s32 *)((u8 *)(arg0) + 64)) = (s32) (*(s32 *)((u8 *)((*(void **)((u8 *)(arg0) + 36))) + 20));
    }
    temp_r5 = (void *)(*(void **)((u8 *)(arg0) + 36));
    if (!((*(s32 *)((u8 *)(temp_r5) + 8)) & 0x20)) {
        fn_1_46B4(lbl_801A6410.unk_0, *(u32 *)((u8 *)(temp_r5) + 148), (const char *)((s8 *) &lbl_1_data_3C7B8), 0x3D4);
    }
    if ((u8) (*(u8 *)((u8 *)(arg0) + 2)) == 4) {
        if ((u8) lbl_1_bss_716C0.unk_0 != 0) {
            temp_r6 = (void *)(*(void **)((u8 *)(arg0) + 36));
            temp_r5_2 = *(u32 *)((u8 *)(temp_r6) + 148);
            (*(u32 *)((u8 *)(temp_r6) + 148)) = (u32) (*(u32 *)((u8 *)(temp_r6) + 220));
            (*(u32 *)((u8 *)(temp_r6) + 220)) = temp_r5_2;
            lbl_1_bss_716C0.unk_0 = 0;
        }
        temp_r4 = *(u32 *)((u8 *)((*(void **)((u8 *)(arg0) + 36))) + 220);
        if (temp_r4 != 0) {
            fn_1_46B4(lbl_801A6410.unk_0, temp_r4, (const char *)((s8 *) &lbl_1_data_3C7B8), 0x3DE);
            (*(u32 *)((u8 *)((*(void **)((u8 *)(arg0) + 36))) + 220)) = 0U;
        }
    }
    (*(s16 *)((u8 *)(arg0) + 8)) = 0x30;
    (*(s16 *)((u8 *)(arg0) + 10)) = 0xE;
    (*(u8 *)((u8 *)(arg0) + 42)) = (u8) ((*(u8 *)((u8 *)(arg0) + 42)) | 4);
}
/* fzgx:end fn_1_AC53C */

/* fzgx:begin fn_1_AC6A4 */
// fn_1_AC6A4: empty in retail (single blr).
void fn_1_AC6A4(void) {
}
/* fzgx:end fn_1_AC6A4 */

/* fzgx:begin fn_1_AC6A8 */
typedef struct {
    u8 unk0[8];
    u16 unk8;
    u16 unka;
    u8 unkC[0x1e];
    u8 unk2a;
} Fn1AC6A8Data;

void fn_1_AC6A8(Fn1AC6A8Data *data) {
    data->unk8 = 0x33;
    data->unka = 0xe;
    data->unk2a |= 4;
}
/* fzgx:end fn_1_AC6A8 */

/* fzgx:begin fn_1_AC6C8 */
// fn_1_AC6C8: empty in retail (single blr).
void fn_1_AC6C8(void) {
}
/* fzgx:end fn_1_AC6C8 */

/* fzgx:begin fn_1_AC6CC */
typedef struct fn_1_AC6CC_MemCardState {
    u8 padding[0x2a];
    u8 flags;
} fn_1_AC6CC_MemCardState;

void fn_1_AC6CC(fn_1_AC6CC_MemCardState *self) {
    self->flags |= 4;
}
/* fzgx:end fn_1_AC6CC */

/* fzgx:begin fn_1_AC6DC */
// fn_1_AC6DC: empty in retail (single blr).
void fn_1_AC6DC(void) {
}
/* fzgx:end fn_1_AC6DC */

/* fzgx:begin fn_1_AC6E0 */
// fn_1_AC6E0: Write struct fields at offsets 0x8, 0xa, and 0x2a (with OR).
void fn_1_AC6E0(void *r3) {
    *(u16 *)((u8 *)r3 + 0x8) = 0x34;
    *(u16 *)((u8 *)r3 + 0xa) = 0xe;
    *(((u8 *)r3) + 0x2a) |= 0x4;
}
/* fzgx:end fn_1_AC6E0 */

/* fzgx:begin fn_1_AC700 */
// fn_1_AC700: empty in retail (single blr).
void fn_1_AC700(void) {
}
/* fzgx:end fn_1_AC700 */

/* fzgx:begin fn_1_AC704 */
void fn_1_AC704(void *r3) {
    *(u16 *)((u8 *)*(void **)((u8 *)r3 + 0x24) + 0x2) = 0x12c;
    CARDReadAsync((u8 *)r3 + 0x10,
                *(void **)((u8 *)*(void **)((u8 *)r3 + 0x24) + 0x94),
                *(void **)((u8 *)*(void **)((u8 *)r3 + 0x24) + 0xc),
                0,
                0);
}
/* fzgx:end fn_1_AC704 */

/* fzgx:begin fn_1_AC74C */
void fn_1_AC74C(void *r3) {
    s32 result;

    result = CARDGetResultCode(*(u8 *)r3);
    *(s32 *)((u8 *)*(void **)((u8 *)r3 + 0x24) + 0x4) = result;
    if (*(s32 *)((u8 *)*(void **)((u8 *)r3 + 0x24) + 0x4) != -1) {
        *(u16 *)((u8 *)*(void **)((u8 *)r3 + 0x24) + 0x2) = 0;
    }
}
/* fzgx:end fn_1_AC74C */

/* fzgx:begin fn_1_AC79C noprologue */
#include "types.h"

struct fn_1_AC79C_Arg0 {
    u8 pad_0[0xC];
    u32 unk_C;
};
struct fn_1_AC79C_lbl_801A6410 {
    u32 unk_0;
};
struct fn_1_AC79C_lbl_1_bss_716C0 {
    u8 unk_0;
};
extern struct fn_1_AC79C_lbl_1_bss_716C0 lbl_1_bss_716C0;
extern struct fn_1_AC79C_lbl_801A6410 lbl_801A6410;
extern u32 lbl_1_data_3C7B8;
extern s32 CARDUnmount(void *);
extern void fn_1_46B4(u32, u32, const char *, int);

void fn_1_AC79C(void *arg0) {
    u32 temp_r4;
    u32 temp_r5_2;
    void *temp_r3;
    void *temp_r3_2;
    void *temp_r5;
    void *temp_r6;

    if ((u32) (*(u32 *)((u8 *)(arg0) + 12)) != 0) {
        do {

        } while (CARDUnmount((void *)((void *)((*(u8 *)((u8 *)(arg0) + 0))))) == -1);
        fn_1_46B4(lbl_801A6410.unk_0, *(u32 *)((u8 *)(arg0) + 12), (const char *)((s8 *) &lbl_1_data_3C7B8), 0x3C8);
        (*(s8 *)((u8 *)(arg0) + 7)) = 0;
        (*(u32 *)((u8 *)(arg0) + 12)) = 0U;
        temp_r3 = (void *)(*(void **)((u8 *)(arg0) + 36));
        (*(s32 *)((u8 *)(temp_r3) + 28)) = 0;
        (*(s32 *)((u8 *)(temp_r3) + 24)) = 0;
    }
    temp_r3_2 = (void *)(*(void **)((u8 *)(arg0) + 36));
    if ((*(s32 *)((u8 *)(temp_r3_2) + 8)) & 0x80) {
        (*(s32 *)((u8 *)(arg0) + 60)) = (s32) ((s32) (*(s32 *)((u8 *)(temp_r3_2) + 16)) / 8192);
        (*(s32 *)((u8 *)(arg0) + 64)) = (s32) (*(s32 *)((u8 *)((*(void **)((u8 *)(arg0) + 36))) + 20));
    }
    temp_r5 = (void *)(*(void **)((u8 *)(arg0) + 36));
    if (!((*(s32 *)((u8 *)(temp_r5) + 8)) & 0x20)) {
        fn_1_46B4(lbl_801A6410.unk_0, *(u32 *)((u8 *)(temp_r5) + 148), (const char *)((s8 *) &lbl_1_data_3C7B8), 0x3D4);
    }
    if ((u8) (*(u8 *)((u8 *)(arg0) + 2)) == 4) {
        if ((u8) lbl_1_bss_716C0.unk_0 != 0) {
            temp_r6 = (void *)(*(void **)((u8 *)(arg0) + 36));
            temp_r5_2 = *(u32 *)((u8 *)(temp_r6) + 148);
            (*(u32 *)((u8 *)(temp_r6) + 148)) = (u32) (*(u32 *)((u8 *)(temp_r6) + 220));
            (*(u32 *)((u8 *)(temp_r6) + 220)) = temp_r5_2;
            lbl_1_bss_716C0.unk_0 = 0;
        }
        temp_r4 = *(u32 *)((u8 *)((*(void **)((u8 *)(arg0) + 36))) + 220);
        if (temp_r4 != 0) {
            fn_1_46B4(lbl_801A6410.unk_0, temp_r4, (const char *)((s8 *) &lbl_1_data_3C7B8), 0x3DE);
            (*(u32 *)((u8 *)((*(void **)((u8 *)(arg0) + 36))) + 220)) = 0U;
        }
    }
    (*(s16 *)((u8 *)(arg0) + 8)) = 0x35;
    (*(s16 *)((u8 *)(arg0) + 10)) = 0xE;
    (*(u8 *)((u8 *)(arg0) + 42)) = (u8) ((*(u8 *)((u8 *)(arg0) + 42)) | 4);
}
/* fzgx:end fn_1_AC79C */

/* fzgx:begin fn_1_AC904 */
// fn_1_AC904: empty in retail (single blr).
void fn_1_AC904(void) {
}
/* fzgx:end fn_1_AC904 */

/* fzgx:begin fn_1_AC908 */
typedef struct {
    u8 unk0[8];
    u16 field8;
    u16 fieldA;
    u8 unkC[0x1e];
    u8 flags;
} Fn1AC908State;

void fn_1_AC908(Fn1AC908State *state) {
    state->field8 = 0x3c;
    state->fieldA = 0xe;
    state->flags |= 4;
}
/* fzgx:end fn_1_AC908 */

/* fzgx:begin fn_1_AC928 */
// fn_1_AC928: empty in retail (single blr).
void fn_1_AC928(void) {
}
/* fzgx:end fn_1_AC928 */

/* fzgx:begin fn_1_AC92C */
struct fn_1_AC92C_Arg0 {
    u8 pad_0[0x24];
    u32 unk_24;
    u8 pad_28[0x2];
    u8 unk_2A;
    u8 pad_2B[0x1];
    u8 unk_2C;
    u8 unk_2D;
    u8 pad_2E[0xA];
    f32 unk_38;
};

u32 fn_1_AC92C(struct fn_1_AC92C_Arg0 *arg0) {
    u32 v0;
    arg0->unk_2C = 0;
    arg0->unk_2D = 0;
    arg0->unk_38 = lbl_1_rodata_4CA8;
    arg0->unk_2A = (arg0->unk_2A | 2);
    v0 = arg0->unk_24;
    *(u16 *)((u8 *)v0 + 2) = 300;
    return v0;
}
/* fzgx:end fn_1_AC92C */

/* fzgx:begin fn_1_AC960 */
struct MemcardData {
    u8 pad0[2];
    u16 status;
    s32 result;
};

struct MemcardObject {
    u8 id;
    u8 pad1[0x23];
    struct MemcardData *data;
    u8 pad28[2];
    u8 flags;
    u8 pad2b;
    u8 state;
    u8 pad2d[0xb];
    f32 progress;
};

void fn_1_AC960(struct MemcardObject *obj) {
    s32 result;

    result = CARDGetStatus(obj->id, obj->state,
                          (void *)((u8 *)obj->data + 0x20));
    obj->data->result = result;
    obj->progress = (f32)((f64)obj->state / lbl_1_rodata_4CC8);
    if (obj->state == 0x7e) {
        obj->flags = obj->flags & 0xfffffffd;
        obj->data->status = 0;
    }
}
/* fzgx:end fn_1_AC960 */

/* fzgx:begin fn_1_ACA00 */
typedef struct Fn1Aca00Target {
    u8 _pad00[0x24];
    struct Fn1Aca00Child *child;
    u8 _pad28[4];
    u8 flag_2c;
    u8 flag_2d;
} Fn1Aca00Target;

typedef struct Fn1Aca00Child {
    u8 _pad00[2];
    u16 value;
} Fn1Aca00Child;

void fn_1_ACA00(Fn1Aca00Target *self) {
    self->flag_2c = 0;
    self->flag_2d = 0;
    self->child->value = 300;
}
/* fzgx:end fn_1_ACA00 */

/* fzgx:begin fn_1_ACA1C */
typedef struct MemCardData {
    u8 pad0[4];
    s32 value;
    u8 pad8[0x18];
} MemCardData;

typedef struct fn_1_ACA1C_MemCardState {
    u8 id;
    u8 pad1[0x23];
    MemCardData *data;
    u8 pad28[4];
    u8 slot;
} fn_1_ACA1C_MemCardState;

void fn_1_ACA1C(fn_1_ACA1C_MemCardState *state) {
    state->data->value = CARDGetStatus(state->id, state->slot,
        (u8 *)state->data + 0x20);
    if (state->slot == 0x7e) {
        *(u16 *)((u8 *)state->data + 2) = 0;
    }
}
/* fzgx:end fn_1_ACA1C */

/* fzgx:begin fn_1_ACD00 */
// fn_1_ACD00: empty in retail (single blr).
void fn_1_ACD00(void) {
}
/* fzgx:end fn_1_ACD00 */

/* fzgx:begin fn_1_ACD04 */
#include "rel/main_rel/globals.h"
#include "rel/main_rel/memcard.h"

typedef struct {
    u8 pad_0[0x8];
    u32 unk_8;
    u8 pad_c[0x4];
    s32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u32 unk_1c;
    u8 pad_20[0x74];
    void *unk_94;
    u8 pad_98[0x44];
    void *unk_dc;
} Fn1Acd04Inner;

typedef struct {
    u8 unk_0;
    u8 pad_1[0x1];
    u8 unk_2;
    u8 pad_3[0x4];
    u8 unk_7;
    u16 unk_8;
    u16 unk_a;
    void *unk_c;
    u8 pad_10[0x14];
    Fn1Acd04Inner *unk_24;
    u8 pad_28[0x2];
    u8 unk_2a;
    u8 pad_2b[0x11];
    s32 unk_3c;
    s32 unk_40;
} Fn1Acd04Obj;

// Reset completed card work and mark the operation ready for its next state.
void fn_1_ACD04(Fn1Acd04Obj *obj) {
    int result;

    if (obj->unk_c != 0) {
        do {
            result = CARDUnmount(obj->unk_0);
        } while (result == -1);

        fn_1_46B4(lbl_801A6410, obj->unk_c, &lbl_1_data_3C7B8, 0x3c8);
        obj->unk_7 = 0;
        obj->unk_c = 0;

        {
            Fn1Acd04Inner *card_state = obj->unk_24;

            card_state->unk_1c = 0;
            card_state->unk_18 = 0;
        }
    }

    if ((obj->unk_24->unk_8 & 0x80) != 0) {
        obj->unk_3c = obj->unk_24->unk_10 / 8192;
        obj->unk_40 = obj->unk_24->unk_14;
    }

    if ((obj->unk_24->unk_8 & 0x20) == 0) {
        fn_1_46B4(lbl_801A6410, obj->unk_24->unk_94,
                  &lbl_1_data_3C7B8, 0x3d4);
    }

    if (obj->unk_2 == 4) {
        if (lbl_1_bss_716C0 != 0) {
            void *previous_buffer;
            Fn1Acd04Inner *card_state;

            card_state = obj->unk_24;
            previous_buffer = card_state->unk_94;
            card_state->unk_94 = card_state->unk_dc;
            card_state->unk_dc = previous_buffer;
            lbl_1_bss_716C0 = 0;
        }

        if (obj->unk_24->unk_dc != 0) {
            fn_1_46B4(lbl_801A6410, obj->unk_24->unk_dc,
                      &lbl_1_data_3C7B8, 0x3de);
            obj->unk_24->unk_dc = 0;
        }
    }

    obj->unk_8 = 0x3f;
    obj->unk_a = 0xe;
    obj->unk_2a |= 4;
    obj->unk_24->unk_8 |= 4;
}
/* fzgx:end fn_1_ACD04 */

/* fzgx:begin fn_1_ACE7C */
// fn_1_ACE7C: empty in retail (single blr).
void fn_1_ACE7C(void) {
}
/* fzgx:end fn_1_ACE7C */

/* fzgx:begin fn_1_ACE80 */
typedef struct {
    u8 field_0;
    u8 pad_1[0x23];
    void* field_24;
} fn_1_ACE80_SomeObject;

// fn_1_ACE80: writes 0x12c to pointed structure, then calls CARDDeleteAsync
void fn_1_ACE80(fn_1_ACE80_SomeObject* obj) {
    *(u16*)((u8*)obj->field_24 + 0x2) = 0x12c;
    CARDDeleteAsync(obj->field_0, (u8*)obj->field_24 + 0x98, 0);
}
/* fzgx:end fn_1_ACE80 */

/* fzgx:begin fn_1_ACEBC */
typedef struct {
    u8 field_0;
    u8 pad_1[0x23];
    void* field_24;
} fn_1_ACEBC_SomeObject;

void fn_1_ACEBC(fn_1_ACEBC_SomeObject* obj) {
    s32 value;
    value = CARDGetResultCode(obj->field_0);
    *(s32*)((u8*)obj->field_24 + 0x4) = value;
    if (*(s32*)((u8*)obj->field_24 + 0x4) != -1) {
        *(u16*)((u8*)obj->field_24 + 0x2) = 0;
    }
}
/* fzgx:end fn_1_ACEBC */

/* fzgx:begin fn_1_ACF0C */
typedef struct {
    u8 pad_0[0x8];
    u16 field_8;
    u16 field_A;
    u8 pad_C[0x1E];
    u8 flags_2A;
} Object;

void fn_1_ACF0C(Object* obj) {
    obj->field_8 = 0x40;
    obj->field_A = 0xE;
    obj->flags_2A |= 0x4;
}
/* fzgx:end fn_1_ACF0C */

/* fzgx:begin fn_1_ACF2C */
// fn_1_ACF2C: empty in retail (single blr).
void fn_1_ACF2C(void) {
}
/* fzgx:end fn_1_ACF2C */

/* fzgx:begin fn_1_ACF30 */
#include "rel/main_rel/globals.h"
#include "rel/main_rel/memcard.h"

typedef struct MemcardState MemcardState;

typedef struct {
    u8 id;
    u8 pad_1;
    u8 type;
    u8 pad_3[0x4];
    u8 ready;
    u16 field_8;
    u16 field_A;
    void* card;
    u8 pad_10[0x14];
    MemcardState* sub;
    u8 pad_28[0x2];
    u8 flags_2A;
    u8 pad_2B[0x11];
    s32 value_3C;
    s32 value_40;
} MemcardObject;

struct MemcardState {
    u8 pad_0[0x8];
    u32 flags_8;
    u8 pad_C[0x4];
    s32 value_10;
    s32 value_14;
    u32 field_18;
    u32 field_1C;
    u8 pad_20[0x74];
    void* value_94;
    u8 pad_98[0x44];
    void* value_DC;
};

// Cleans up pending card data, updates state values, and marks the object ready.
void fn_1_ACF30(MemcardObject* obj) {
    if (obj->card != 0) {
        do {
            if (CARDUnmount(obj->id) != -1) {
                fn_1_46B4(lbl_801A6410, obj->card, &lbl_1_data_3C7B8, 0x3C8);
                obj->ready = 0;
                obj->card = 0;
                {
                    MemcardState* state = obj->sub;
                    state->field_1C = 0;
                    state->field_18 = 0;
                }
                break;
            }
        } while (1);
    }

    if ((obj->sub->flags_8 & 0x80) != 0) {
        obj->value_3C = obj->sub->value_10 / 0x2000;
        obj->value_40 = obj->sub->value_14;
    }
    if ((obj->sub->flags_8 & 0x20) == 0) {
        fn_1_46B4(lbl_801A6410, obj->sub->value_94, &lbl_1_data_3C7B8, 0x3D4);
    }
    if (obj->type == 4) {
        if (lbl_1_bss_716C0 != 0) {
            void* temp;
            MemcardState* state;
            state = obj->sub;
            temp = state->value_94;
            state->value_94 = state->value_DC;
            state->value_DC = temp;
            lbl_1_bss_716C0 = 0;
        }
        if (obj->sub->value_DC != 0) {
            fn_1_46B4(lbl_801A6410, obj->sub->value_DC, &lbl_1_data_3C7B8, 0x3DE);
            obj->sub->value_DC = 0;
        }
    }
    obj->field_8 = 0x41;
    obj->field_A = 0xE;
    obj->flags_2A |= 0x4;
}
/* fzgx:end fn_1_ACF30 */

/* fzgx:begin fn_1_AD098 */
// fn_1_AD098: empty in retail (single blr).
void fn_1_AD098(void) {
}
/* fzgx:end fn_1_AD098 */

/* fzgx:begin fn_1_AD09C */
// fn_1_AD09C: empty in retail (single blr).
void fn_1_AD09C(void) {
}
/* fzgx:end fn_1_AD09C */

/* fzgx:begin fn_1_AD0A0 noprologue */
#include "types.h"
#include "dolphin/card.h"
#include "dolphin/card/CARDPriv.h"

struct fn_1_AD0A0_Arg0 {
    u8 pad_0[0x2C];
    u8 unk_2C;
};
extern f32 lbl_1_rodata_4CD0;
extern f64 lbl_1_rodata_4CB8;
extern s32 CARDGetStatus(s32, s32, CARDStat *);


void fn_1_AD0A0(void *arg0) {
    u8 temp_r4;

    temp_r4 = *(u8 *)((u8 *)(arg0) + 44);
    if (temp_r4 < 0x7FU) {
        (*(s32 *)((u8 *)((*(void **)((u8 *)(arg0) + 36))) + 4)) = CARDGetStatus((s32) (*(u8 *)((u8 *)(arg0) + 0)), (s32) temp_r4, (CARDStat *)((u8 *)((*(void **)((u8 *)(arg0) + 36))) + 0x20));
    }
    (*(f32 *)((u8 *)(arg0) + 56)) = (f32) ((f32) (*(u8 *)((u8 *)(arg0) + 44)) / (*(f32 *)((u8 *)(&lbl_1_rodata_4CD0) + 0)));
    if ((u8) (*(u8 *)((u8 *)(arg0) + 44)) == 0x7E) {
        (*(u8 *)((u8 *)(arg0) + 42)) = (u8) ((*(u8 *)((u8 *)(arg0) + 42)) & 0xFFFFFFFD);
        (*(s16 *)((u8 *)((*(void **)((u8 *)(arg0) + 36))) + 2)) = 0;
    }
}
/* fzgx:end fn_1_AD0A0 */

/* fzgx:begin fn_1_AD140 */
#include "rel/main_rel/globals.h"

extern int fn_1_B7FDC(u8 value);

// Dispatches the memory-card status byte to the shared status handler.
int fn_1_AD140(const u8 *status_byte) {
    return fn_1_B7FDC(*status_byte);
}
/* fzgx:end fn_1_AD140 */

/* fzgx:begin fn_1_AD164 */
// fn_1_AD164: empty in retail (single blr).
void fn_1_AD164(void) {
}
/* fzgx:end fn_1_AD164 */

/* fzgx:begin fn_1_AD168 */
typedef struct Fn1AD168Obj {
    u8 field0;
    u8 _pad1[0x13];
    void *field14;
    u8 _pad18[0xc];
    u8 *field24;
} Fn1AD168Obj;

void fn_1_AD168(Fn1AD168Obj *obj) {
    if (obj->field24[0] == 1) {
        fn_80030754(obj->field0, obj->field14, 0x1c, 0);
    }
}
/* fzgx:end fn_1_AD168 */

/* fzgx:begin fn_1_AD1AC */
extern int fn_1_45D0(void *arg0, int arg1, Obj_1_data_3C7B8 *arg2, int arg3);
extern void fn_1_AB45C(void);
extern void CARDMountAsync(u8, u32, void (*)(void), s32);
extern int CARDGetSerialNo(u8 value, void *data);
extern void CARDCheckAsync(u8 byte_val, int value);
extern void CARDFormatAsync(u8 byte, int value);
extern const f64 lbl_1_rodata_4CB0;
extern void fn_80083DB0(void *dst, void *src);
extern void strcat(void *dst, void *src);
extern void CARDDeleteAsync(u8 byte, void *data, int arg);
extern s32 CARDFreeBlocks(u8 byte_val, void *arg1, void *arg2);
extern s32 CARDOpen(u8 byte_val, void *arg1, void *arg2);
extern void CARDFastDeleteAsync(u8 byte_val, void *arg, s32 zero);
extern void CARDCreateAsync(u8 byte_val, void *arg1, void *arg2, void *arg3, u32 arg4);
extern void CARDSetStatusAsync(u8 id, void *arg, void *data, int zero);
extern void CARDRenameAsync(u8 id, void *data1, void *data2, int zero);
extern void CARDReadAsync(void *arg0, void *arg1, void *arg2, int arg3, int arg4);
extern const f64 lbl_1_rodata_4CC8;
extern void fn_80030754(u8 value, void *data, int size, int mode);
extern u8 lbl_1_bss_71810[161];
extern u8 lbl_1_bss_718B8;
extern u8 lbl_1_bss_718B9[7];
extern int fn_8002A744(void);
extern void fn_8002A74C(u16 value);
extern int fn_8002DFE0(int arg0, u32 arg1, int arg2);
extern int CARDCheck(int arg0);
extern void fn_1_484CC(u32);
extern void fn_80008BEC(void *dst, s32 value, s32 size);
extern void fn_1_AA6D8(s32 arg0, u32 arg1, void *arg2);
extern void fn_1_F755C(u8 value);
extern void fn_1_A6840(u8 value);
extern void OSPanic(void *arg0, u32 arg1, ...);
extern void fn_1_F79C8(void);
extern void strncpy(void *arg0, void *arg1, int arg2);
extern u32 lbl_1_bss_77310[28];
extern u32 lbl_1_bss_7730C;

typedef struct Fn1AD1ACOutput {
    u8 unk_00[4];
    void *unk_04;
} Fn1AD1ACOutput;

typedef struct Fn1AD1ACObject {
    u8 unk_00;
    u8 unk_01[0x23];
    Fn1AD1ACOutput *unk_24;
} Fn1AD1ACObject;

extern void *CARDGetResultCode(u8 arg0);

// Store the generated value in the object's output record.
void fn_1_AD1AC(Fn1AD1ACObject *object) {
    object->unk_24->unk_04 = CARDGetResultCode(object->unk_00);
}
/* fzgx:end fn_1_AD1AC */

/* fzgx:begin fn_1_AD1E4 */
typedef struct Fn1AD1E4State {
    u8 unk_00[8];
    void *unk_08;
    void *unk_0C;
} Fn1AD1E4State;

typedef struct Fn1AD1E4Data {
    u8 unk_00[8];
    u32 unk_08;
    u8 unk_0C[0x88];
    void *unk_94;
    u8 unk_98[0x20];
    void *unk_B8;
} Fn1AD1E4Data;

typedef struct Fn1AD1E4Object {
    u8 unk_00[3];
    u8 unk_03;
    u8 unk_04[0x20];
    Fn1AD1E4Data *unk_24;
} Fn1AD1E4Object;

// Copy pending data when the object is not already marked, then advance its state.
void fn_1_AD1E4(Fn1AD1E4State *state, Fn1AD1E4Object *object) {
    if ((object->unk_24->unk_08 & 0x20) == 0) {
        if (state->unk_08 != 0) {
            strncpy((u8 *)object->unk_24->unk_94 + 0x24,
                        state->unk_08, 0x20);
        }
        fn_80008BA8((u8 *)object->unk_24->unk_94 + 0x2060,
                    state->unk_0C, object->unk_24->unk_B8);
    }
    object->unk_03 = 3;
}
/* fzgx:end fn_1_AD1E4 */

/* fzgx:begin fn_1_AEC34 */
typedef struct Fn1AEC34A {
    u8 pad0[8];
    void *payload;
    void *result;
} Fn1AEC34A;

typedef struct Fn1AEC34P {
    u8 pad0[8];
    u32 flags;
    u8 padC[0x88];
    void *buffer;
    u8 pad98[0x4c];
    void *length;
} Fn1AEC34P;

typedef struct Fn1AEC34B {
    u8 pad0[3];
    u8 state;
    u8 pad4[0x20];
    Fn1AEC34P *card;
} Fn1AEC34B;

// Finalize the card operation and publish its completion state.
void fn_1_AEC34(Fn1AEC34A *request, Fn1AEC34B *operation) {
    if ((operation->card->flags & 0x20) == 0) {
        if (request->payload != 0) {
            strncpy((u8 *)operation->card->buffer + 0x24,
                        request->payload, 0x20);
        }
        fn_80008BA8((u8 *)operation->card->buffer + 0x2060,
                    request->result, operation->card->length);
    }
    operation->state = 3;
    lbl_1_bss_77310[0] = 1;
    lbl_1_bss_7730C = 0;
}
/* fzgx:end fn_1_AEC34 */

/* fzgx:begin fn_1_B03A8 */
void fn_1_B03A8(void *arg0, void *arg1) {
    void *child = *(void **)((u8 *)arg1 + 0x24);
    if ((*(u32 *)((u8 *)child + 0x8) & 0x20) == 0) {
        *(u32 *)((u8 *)child + 0x90) = *(u32 *)((u8 *)arg0 + 0xc);
    }
    *(u8 *)((u8 *)arg1 + 0x3) = 0x3;
}
/* fzgx:end fn_1_B03A8 */

/* fzgx:begin fn_1_B1710 */
void fn_1_B1710(int unused, void *ptr) {
    *(u8 *)((u8 *)ptr + 3) = 0x3;
}
/* fzgx:end fn_1_B1710 */

/* fzgx:begin fn_1_B2770 */
// fn_1_B2770: main_rel .text:0x000B2770 size 0xC
// Store byte 0x3 at offset 3 of the pointer argument

void fn_1_B2770(int unused, void *ptr) {
    *(u8 *)((u8 *)ptr + 3) = 0x3;
}
/* fzgx:end fn_1_B2770 */

/* fzgx:begin fn_1_B38F4 */
void fn_1_B38F4(int unused, void *ptr) {
    *(u8 *)((u8 *)ptr + 3) = 0x3;
}
/* fzgx:end fn_1_B38F4 */

/* fzgx:begin fn_1_B40B4 */
void fn_1_B40B4(int unused, void *ptr) {
    *(u8 *)((u8 *)ptr + 3) = 0x3;
}
/* fzgx:end fn_1_B40B4 */

/* fzgx:begin fn_1_B5258 noprologue */
#include "types.h"

extern void fn_80083DB0(char *destination, const char *source);
extern char *fn_80083970(char *buffer, const char *source);
extern unsigned int strlen(const char *string);
extern char *strncpy(char *destination, const char *source, unsigned int count);
extern char *strcat(char *destination, const char *source);

void fn_1_B5258(char *destination, void *unused, const char *source, const char *suffix) {
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
/* fzgx:end fn_1_B5258 */

/* fzgx:begin fn_1_B5F00 */
typedef struct {
    u8 pad0[0x54];
    f32 value;
} B5F00Source;

typedef struct {
    f32 value0;
    u8 pad4[8];
    f32 valueC;
} B5F00Dest;

void fn_1_B5F00(B5F00Source *source, B5F00Dest *dest) {
    f32 value = dest->value0;
    f32 increment = source->value;
    value += increment;
    dest->value0 = value;
    value = dest->valueC;
    value += increment;
    dest->valueC = value;
}
/* fzgx:end fn_1_B5F00 */

/* fzgx:begin fn_1_B7C00 */
#include "rel/main_rel/memcard.h"

u8 fn_1_B7C00(void) {
    u8 result = 0;

    if (lbl_1_bss_716C8.unk_2 != 0xff) {
        result |= 1;
    }
    if (lbl_1_bss_716C8.pad_A0[2] != 0xff) {
        result |= 2;
    }
    if (lbl_1_bss_71810[2] != 0xff) {
        result |= 4;
    }

    return result;
}
/* fzgx:end fn_1_B7C00 */

/* fzgx:begin fn_1_B7C5C */
u32 fn_1_B7C5C(void) {
    return lbl_1_bss_718B4;
}
/* fzgx:end fn_1_B7C5C */

/* fzgx:begin fn_1_B7CD4 */
u8 fn_1_B7CD4(void) {
    return lbl_1_bss_718B8;
}
/* fzgx:end fn_1_B7CD4 */

/* fzgx:begin fn_1_B7E14 */
#include "rel/main_rel/memcard.h"
#include "rel/main_rel/globals.h"

// Save the current memory-card state in the global work buffer.

void fn_1_B7E14(void *memory_card_state) {
    strncpy(lbl_1_bss_716C8.pad_54, memory_card_state, 0x20);
}
/* fzgx:end fn_1_B7E14 */

/* fzgx:begin fn_1_B7E48 */
#include "rel/main_rel/memcard.h"
#include "rel/main_rel/globals.h"

// Return whether either tracked object has its active flag set.
int fn_1_B7E48(void) {
    int result = 0;
    Obj_1_bss_716C8_At24 *object = lbl_1_bss_716C8.unk_24;

    if (object != 0 && (object->unk_8 & 0x200) != 0) {
        result = 1;
    }

    object = *(Obj_1_bss_716C8_At24 **)(lbl_1_bss_716C8.pad_A0 + 0x24);
    if (object != 0 && (object->unk_8 & 0x200) != 0) {
        result = 1;
    }

    return result;
}
/* fzgx:end fn_1_B7E48 */

/* fzgx:begin fn_1_B7E98 */
#include "rel/main_rel/memcard.h"
#include "rel/main_rel/globals.h"

// Return whether the indexed memory-card entry is not in the unavailable state.
int fn_1_B7E98(int index) {
    return (s8)lbl_1_bss_716C8.pad_A0[index * 0xa0 - 0x9f] != -3;
}
/* fzgx:end fn_1_B7E98 */

/* fzgx:begin fn_1_B7EC4 */
int fn_1_B7EC4(int index) {
    int result = 0;
    s8 value = (s8)lbl_1_bss_716C8.pad_A0[index * 0xa0 - 0x9f];

    if (value != -1 && value != -3) {
        result = 1;
    }
    return result;
}
/* fzgx:end fn_1_B7EC4 */

/* fzgx:begin fn_1_B7EF8 */
// fn_1_B7EF8: Load and return first byte from lbl_1_bss_718B9
u8 fn_1_B7EF8(void) {
    return lbl_1_bss_718B9[0];
}
/* fzgx:end fn_1_B7EF8 */

/* fzgx:begin fn_1_B7F08 */
u32 fn_1_B7F08(void) {
    return lbl_1_bss_718B4 != 0;
}
/* fzgx:end fn_1_B7F08 */

/* fzgx:begin fn_1_B7F24 */
typedef struct {
    u8 pad_0[0x48];
    u32 unk_48;
    u32 unk_4C;
    u32 unk_50;
    u8 pad_54[0x94];
    u32 unk_E8;
    u32 unk_EC;
    u32 unk_F0;
} MemcardResetView;

// Clear the operation state and mark the memory card as unavailable.
void fn_1_B7F24(void) {
#define reset_state (*(MemcardResetView *)&lbl_1_bss_716C8)

    reset_state.unk_50 = 0;
    reset_state.unk_F0 = 0;
    reset_state.unk_4C = 0;
    reset_state.unk_48 = 0;
    reset_state.unk_EC = 0;
    reset_state.unk_E8 = 0;
    *(s8 *)&lbl_1_bss_7730A = -1;
}
/* fzgx:end fn_1_B7F24 */

/* fzgx:begin fn_1_B7FC8 */
#include "rel/main_rel/memcard.h"

u32 fn_1_B7FC8(void) {
    return lbl_1_bss_718C0.unk_0->unk_0;
}
/* fzgx:end fn_1_B7FC8 */

/* fzgx:begin fn_1_B7FDC */
// Toggles the low 16-bit status value and stores the result.
void fn_1_B7FDC(void) {
    u16 value = (u16)fn_8002A744();
    value = (u16)(value ^ 1);
    fn_8002A74C(value);
}
/* fzgx:end fn_1_B7FDC */

/* fzgx:begin fn_1_B800C */
#include "rel/main_rel/globals.h"
#include "rel/main_rel/memcard.h"

// Loads a memory-card slot, retrying transient operations and cleaning up failures.
int fn_1_B800C(int index) {
    int status;
    Obj_1_bss_716C8 *card;

    card = (Obj_1_bss_716C8 *)((u8 *)&lbl_1_bss_716C8 + index * 0xa0);
    card->unk_C = fn_1_45D0(lbl_801A6410, 0xA000, &lbl_1_data_3C7B8, 0x256D);
    for (;;) {
        status = fn_8002DFE0(index, card->unk_C, 0);
        if (status == -1) {
            continue;
        }
        if (status != 0 && status != -6) {
            if (card->unk_C != 0) {
                fn_1_46B4(lbl_801A6410, card->unk_C, &lbl_1_data_3C7B8, 0x2573);
                card->unk_C = 0;
            }
            return status;
        }
        do {
            status = CARDCheck(index);
        } while (status == -1);
        return status;
    }
}
/* fzgx:end fn_1_B800C */

/* fzgx:begin fn_1_B80F0 */
#include "rel/main_rel/globals.h"
#include "rel/main_rel/memcard.h"

// Wait for the card operation to finish, then release its temporary result.
void fn_1_B80F0(int index) {
    Obj_1_bss_716C8 *entry =
        (Obj_1_bss_716C8 *)((u8 *)&lbl_1_bss_716C8 + index * 0xa0);

    for (;;) {
        if (CARDUnmount(index) != -1) {
            break;
        }
    }

    if (entry->unk_C != 0) {
        fn_1_46B4(lbl_801A6410, entry->unk_C,
                  &lbl_1_data_3C7B8, 0x258c);
        entry->unk_C = 0;
    }
}
/* fzgx:end fn_1_B80F0 */

/* fzgx:begin fn_1_B9BE0 */
void fn_1_B9BE0(void) {
    fn_1_B9C38(0);
    fn_1_B9C38(1);
}
/* fzgx:end fn_1_B9BE0 */

/* fzgx:begin fn_1_B9C0C */
void fn_1_B9C0C(void) {
    fn_1_B9C38(0);
    fn_1_B9C38(1);
}
/* fzgx:end fn_1_B9C0C */

/* fzgx:begin fn_1_B9C38 */
#include "rel/main_rel/memcard.h"

// Saves populated slots before resetting each slot for reuse.
void fn_1_B9C38(s32 index) {
    Obj_1_bss_77380 *slot;
    u8 *slot_bytes;
    s32 slot_index;

    slot = (Obj_1_bss_77380 *)((u8 *)&lbl_1_bss_77380 + index * 0x1800);
    for (slot_index = 0; slot_index < 0x7f; slot_index++) {
        slot_bytes = (u8 *)slot;
        if (slot->unk_2C != 0) {
            fn_1_46B4(lbl_801A6410, slot->unk_2C, &lbl_1_data_3C7B8, 0x2776);
        }

        slot_bytes[1] = 0;
        slot_bytes[2] = 0;
        slot->unk_24 = 0;
        slot->unk_28 = 0;
        slot->unk_2C = 0;
        slot = (Obj_1_bss_77380 *)(slot_bytes + 0x30);
    }
}
/* fzgx:end fn_1_B9C38 */

/* fzgx:begin fn_1_BC29C */
#include "rel/main_rel/memcard.h"

// Completes the pending memory-card operation and resets the card state when needed.
void fn_1_BC29C(void) {
    if (lbl_1_bss_7A380 != 0) {
        fn_1_46B4(lbl_801A6410, lbl_1_bss_7A380, &lbl_1_data_3C7B8, 0x2ad4);
        lbl_1_bss_7A380 = 0;
    }
    if (*(s16 *)&lbl_1_bss_960 != 2) {
        fn_1_1596DC(2);
        fn_1_484CC(2);
    }
}
/* fzgx:end fn_1_BC29C */

/* fzgx:begin fn_1_C0510 noprologue */
#include "types.h"

typedef struct {
    u8 pad_0[0x14];
    s8 type;
    s16 first;
    s16 second;
    s16 third;
    s16 fourth;
} Fn1C0510Obj;

extern u64 OSGetTime(void);
extern u64 __div2i(u64, u32, u32);
extern u8 lbl_1_bss_77380[];
extern u32 lbl_1_bss_7AB90[36];
extern void fn_1_C062C(Fn1C0510Obj *, void *, void *);
extern void fn_1_C0B0C(Fn1C0510Obj *, void *, void *);
extern void fn_1_C0E00(Fn1C0510Obj *, void *, void *);
extern void fn_1_C132C(Fn1C0510Obj *, void *, void *);

void fn_1_C0510(Fn1C0510Obj *obj) {
    u64 time;
    void *first;
    void *second;

    time = OSGetTime();
    // fzgx-allow: A1 fixed SDK OS global
    // fzgx-allow: A2 fixed SDK OS global
    lbl_1_bss_7AB90[0] = __div2i(time, 0, (*(u32 *)0x800000F8) >> 2);  /* fzgx-allow: A1,A2 unnamed OS/hardware memory */

    if (obj->first != -1 && obj->second != -1) {
        first = lbl_1_bss_77380 + obj->first * 0x1800 + obj->second * 0x30;
    } else {
        first = 0;
    }

    if (obj->third != -1 && obj->fourth != -1) {
        second = lbl_1_bss_77380 + obj->third * 0x1800 + obj->fourth * 0x30;
    } else {
        second = 0;
    }

    switch (obj->type) {
    case 1:
        fn_1_C062C(obj, first, second);
        break;
    case 2:
        fn_1_C0B0C(obj, first, second);
        break;
    case 4:
        fn_1_C0E00(obj, first, second);
        break;
    case 8:
        fn_1_C132C(obj, first, second);
        break;
    }
}
/* fzgx:end fn_1_C0510 */

/* fzgx:begin fn_1_C132C */
typedef struct {
    u8 unk0[0x16];
    s16 unk16;
} Fn1C132CObject;

void fn_1_C132C(Fn1C132CObject *object, u8 *data) {
    u8 local[0x24];

    fn_80008BEC(local, 0, 0x24);
    local[0] = data[1];
    *(u8 **)(local + 0x14) = data + 2;
    fn_1_AA6D8(5, (u8)object->unk16, local);
}
/* fzgx:end fn_1_C132C */

/* fzgx:begin fn_1_C17CC */
// fn_1_C17CC: empty in retail (single blr).
void fn_1_C17CC(void) {
}
/* fzgx:end fn_1_C17CC */

/* fzgx:begin fn_1_C2454 */
extern void fn_1_C36EC(void);

void fn_1_C2454(void) {
    u8 *state = (u8 *)&lbl_1_bss_716C0 + 0x10000;

    state[-0x6b04] = 0;
    state[-0x6afc] = 0;
    fn_1_C36EC();
    *(u32 *)(state - 0x6af8) = 3;
    state[-0x6af4] = 0;
}
/* fzgx:end fn_1_C2454 */

/* fzgx:begin fn_1_C34F0 */
#include "rel/main_rel/globals.h"
#include "rel/main_rel/memcard.h"

// Initializes the memory-card state and restores the persistent card data.
void fn_1_C34F0(void) {
    Obj_1_bss_718C0_At0 *card_buffer;
    u8 *serialized_data;

    fn_1_F755C(lbl_1_bss_718E0.unk_2);
    fn_80008BA8(lbl_1_data_2AC0, (u8 *)&lbl_1_bss_718E0 + 0x8, 0x40);
    fn_80008BA8(lbl_1_data_2B40, (u8 *)&lbl_1_bss_718E0 + 0x48, 0x8);
    fn_80008BA8(&lbl_1_data_2B50, (u8 *)&lbl_1_bss_718E0 + 0x5542, 0x8);
    fn_80008BA8(&lbl_1_data_2B58, (u8 *)&lbl_1_bss_718E0 + 0x554A, 0x8);
    fn_80008BA8(lbl_1_bss_AA0, (u8 *)&lbl_1_bss_718E0 + 0x50, 0x150);
    fn_80008BA8(&lbl_1_data_2B60, (u8 *)&lbl_1_bss_718E0 + 0x5556, 0x4);

    fn_1_A6840(lbl_1_bss_718E0.unk_3 <= 1 ? lbl_1_bss_718E0.unk_3 : 1);

    card_buffer = lbl_1_bss_718C0.unk_0;
    serialized_data = (u8 *)card_buffer + 0x4;
    fn_80008BA8(&lbl_1_bss_8B3A0.unk_9F, serialized_data, 0x4);
    fn_80008BA8(&lbl_1_bss_8B3A0.unk_8C, serialized_data + 0x4, 0x6);
    fn_80008BA8((u8 *)&lbl_1_bss_8B3A0 + 0xC, serialized_data + 0xA, 0x80);

    if ((u32)(serialized_data + 0x8A -
              ((u8 *)lbl_1_bss_718C0.unk_0 + 0x4)) != 0x8A) {
        OSPanic(&lbl_1_data_3C7B8, 0x3532, lbl_1_data_3D124);
    }
    fn_1_F79C8();
}
/* fzgx:end fn_1_C34F0 */

/* fzgx:begin fn_1_C3688 */
typedef struct TimeParts {
    u32 unused;
    u32 field_4;
    u32 field_8;
    u32 field_C;
    u32 field_10;
    u32 field_14;
    u32 spare_18;
    u32 spare_1C;
} TimeParts;

extern u64 OSGetTime(void);
extern void OSTicksToCalendarTime(u32 high, u32 low, TimeParts *parts);

u32 fn_1_C3688(void) {
    TimeParts parts;
    u64 time;
    u32 result;

    time = OSGetTime();
    OSTicksToCalendarTime((u32)(time >> 32), (u32)time, &parts);
    result = (parts.field_4 & 0x3F) + ((parts.field_8 & 0x1F) << 6);
    result += (parts.field_C & 0x1F) << 11;
    result += (parts.field_10 & 0x0F) << 16;
    result += ((parts.field_14 - 0x7D3) & 0x3F) << 20;
    return result;
}
/* fzgx:end fn_1_C3688 */

/* fzgx:begin fn_1_C36EC */
#include "rel/main_rel/globals.h"
#include "rel/main_rel/memcard.h"

// Writes the in-memory card fields to the active serialized card buffer.
void fn_1_C36EC(void) {
    u8 *serialized_data = &lbl_1_bss_718C0.unk_0->unk_4;

    fn_80008BA8(serialized_data, &lbl_1_bss_8B3A0.unk_9F, 4);
    fn_80008BA8(serialized_data + 4, &lbl_1_bss_8B3A0.unk_8C, 6);
    fn_80008BA8(serialized_data + 0xA, (u8 *)&lbl_1_bss_8B3A0 + 0xC, 0x80);

    if ((u32)(serialized_data + 0x8A -
              ((u8 *)lbl_1_bss_718C0.unk_0 + 4)) != 0x8A) {
        OSPanic(&lbl_1_data_3C7B8, 0x3578, lbl_1_data_3D124);
    }
}
/* fzgx:end fn_1_C36EC */

/* fzgx:begin fn_1_C37A0 */
extern void fn_1_46B4(void *heap, u32 ptr, void *file, s32 line);
extern s32 CARDGetResultCode(s32 chan);
extern s32 CARDUnmount(s32 chan);

typedef struct CARDFileInfo {
    s32 chan;
    s32 fileNo;
    s32 offset;
    s32 length;
    u16 iBlock;
    u16 padding;
} CARDFileInfo;

// Unmount the memory card, repair its save-file names, and release its work area.
void fn_1_C37A0(void) {
    CARDFileInfo fileInfo;
    char sp28[32];
    char sp8[32];
    char *base = (char *)&lbl_1_data_35AC8;
    s32 chan;
    u32 workArea;
    s32 res;

    if (lbl_1_bss_772C8[0] == 0) {
        return;
    }

    chan = lbl_1_bss_718B1;
    workArea = fn_1_4630(lbl_801A6410, 0xA000, base + 0x6cf0, 0x3594);

    do {
        res = CARDGetResultCode(chan);
    } while (res == -1);

    do {
        res = CARDUnmount(chan);
    } while (res == -1);

    do {
        res = fn_8002DFE0(chan, workArea, 0);
    } while (res == -1);

    if (res != 0) {
        if (workArea != 0) {
            fn_1_46B4(lbl_801A6410, workArea, base + 0x6cf0, 0x35ab);
        }
        lbl_1_bss_772C8[0] = 0;
        return;
    }

    fn_80083DB0(sp28, lbl_1_bss_772C8);
    strcat(sp28, base + 0x6dd4);

    do {
        res = CARDOpen(chan, sp28, &fileInfo);
    } while (res == -1);

    if (res != 0) {
        do {
            res = CARDUnmount(chan);
        } while (res == -1);

        if (workArea != 0) {
            fn_1_46B4(lbl_801A6410, workArea, base + 0x6cf0, 0x35c2);
        }
        lbl_1_bss_772C8[0] = 0;
        return;
    }

    fn_80083DB0(sp28, lbl_1_bss_772C8);
    strcat(sp28, base + 0x6cfc);

    do {
        res = CARDOpen(chan, sp28, &fileInfo);
    } while (res == -1);

    if (res == 0) {
        fn_80083DB0(sp28, lbl_1_bss_772C8);
        strcat(sp28, base + 0x6dd4);

        while (fn_8002FC14(chan, sp28) == -1) {
        }
    } else if (res == -4) {
        fn_80083DB0(sp8, lbl_1_bss_772C8);
        strcat(sp8, base + 0x6dd4);

        while (fn_80030338(chan, sp8, sp28) == -1) {
        }
    }

    do {
        res = CARDUnmount(chan);
    } while (res == -1);

    if (workArea != 0) {
        fn_1_46B4(lbl_801A6410, workArea, base + 0x6cf0, 0x35ef);
    }
    lbl_1_bss_772C8[0] = 0;
}
/* fzgx:end fn_1_C37A0 */

/* fzgx:begin fn_1_C39FC */
u32 fn_1_C39FC(void) {
    return lbl_1_data_3D230;
}
/* fzgx:end fn_1_C39FC */
