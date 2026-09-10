#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/font.h"

extern const f32 lbl_1_rodata_10D4;
extern void fn_1_4955C(f32 value1, f32 value2);
extern f32 lbl_1_rodata_10C0[5];
extern f32 fn_1_4B1D4(s32 mode, s32 value);
extern u32 strlen(const char *str);
extern void sprintf(void *arg0, void *arg1, u32 arg2, ...);
extern f32 lbl_1_rodata_26B8[16];
extern void fn_1_4D10C(void *data, f32 scale, f32 value);
extern void fn_1_4D2AC(void *data, f32 scale, f32 value);
extern int fn_1_3F164(void);
extern void fn_800724C8(void);
extern void fn_8007245C(int);
extern void fn_80074788(int);
extern void fn_80074660(int);
extern void fn_80073678(int);
extern void fn_80073898(int);
extern void fn_80073C6C(int);
extern void fn_800745A4(int, int, int, int, int, int);
extern void fn_800734A8(int, int, int, int);
extern void fn_80072AB0(int, int, int);
extern void fn_80072C24(int, int, int, int, int);
extern void fn_80072D64(int, int, int, int, int, int);
extern void fn_80072CC4(int, int, int, int, int);
extern void fn_80072E20(int, int, int, int, int, int);
extern void fn_80074918(s32, s32, s32);
extern void fn_800728A8(int, int, int, int);
extern void fn_800720B0(int);
extern void fn_80072864(int);
extern void fn_1_A71CC(void);
extern void lbl_8006D758(void);
extern void fn_80072558(void);
extern f32 lbl_1_rodata_26F8[22];
extern f32 fn_1_A6FE8(void);
extern void *lbl_801A6D00;
extern void fn_80015E18(void *, f32, f32, f32, f32);
extern void fn_80015EE8(void *, f32, f32, f32, f32, f32, f32);
extern void fn_800737E4(void *, s32);
extern void fn_1_A722C(void);
extern void fn_1_50190(f32 a, f32 b, f32 c, f32 d, f32 e, f32 f);
extern void fn_1_52BF8(void *arg0, void *arg1, s32 arg2);
extern void *fn_1_541A8(void *arg, s32 value);
extern u32 lbl_801A66B4;
extern void fn_1_54320(void);
extern void fn_1_9FA18(void);
extern void fn_1_58248(void);
extern void fn_1_54848(void);
extern void fn_800794F0(u8 *data, void *value, s32 size);
extern s32 fn_1_54F5C(u8 *data, f32 value, f32 scale);
extern void fn_1_55210(void *value);
extern void fn_1_56530(void);
extern const f32 lbl_1_rodata_28A8;
extern void fn_1_557C4(void *value);
extern void fn_1_556B8(void *value);
extern void fn_1_563E4(void *data);
extern void fn_80077E7C(void *value);
extern void fn_80077F8C(void *value);
extern void fn_80074CF4(void);
extern void lbl_8006DD14(void *arg0, void *arg1);
extern void fn_800749B0(s32 arg0, void *arg1);
extern const f32 lbl_1_rodata_28AC;
extern void fn_80074C74(u8 *value);
extern void fn_80074A7C(void);
extern void fn_80077BAC(void);
extern u8 lbl_1_bss_6C7DC[100];
extern u8 *fn_1_565E8(void);
extern void fn_1_45730(void);
extern void fn_1_45B2C(void);
extern void fn_1_458A0(void);
extern void fn_1_45850(void);
extern void fn_1_565F4(void);
extern void fn_80070D60(void *);

extern u8 *fn_1_565E8(void);
extern void fn_1_45730(void);
extern void fn_1_45B2C(void);
extern void fn_1_458A0(void);
extern void fn_1_45850(void);
extern void fn_1_565F4(void);
extern void fn_80070D60(void *);
extern u8 *lbl_801A66CC;
extern void fn_80008BA8(void *, void *, u32);
extern f64 lbl_1_rodata_2778[2];
extern s8 fn_1_A5DC4(s32 value);
extern f32 lbl_1_rodata_2788[6];

/* fzgx:begin fn_1_494CC */
void fn_1_494CC(u8 value) {
    lbl_1_bss_4B9CC.unk_44 = value;
}
/* fzgx:end fn_1_494CC */

/* fzgx:begin fn_1_494DC */
void fn_1_494DC(s16 index) {
    lbl_1_bss_4B9CC.unk_C = index;
    fn_1_4955C(lbl_1_rodata_10D4, lbl_1_rodata_10D4);
}
/* fzgx:end fn_1_494DC */

/* fzgx:begin fn_1_49514 */
void fn_1_49514(u32 *value) {
    lbl_1_bss_4B9CC.unk_10 = *value;
}
/* fzgx:end fn_1_49514 */

/* fzgx:begin fn_1_49528 */
void fn_1_49528(u32 *value) {
    lbl_1_bss_4B9CC.unk_14 = *value;
}
/* fzgx:end fn_1_49528 */

/* fzgx:begin fn_1_4953C */
void fn_1_4953C(s16 value) {
    lbl_1_bss_4B9CC.unk_E = value;
}
/* fzgx:end fn_1_4953C */

/* fzgx:begin fn_1_4954C */
void fn_1_4954C(f32 value) {
    lbl_1_bss_4B9CC.unk_18 = value;
}
/* fzgx:end fn_1_4954C */

/* fzgx:begin fn_1_4955C */
void fn_1_4955C(f32 value1, f32 value2) {
    s16 index = lbl_1_bss_4B9CC.unk_C;
    Obj_1_data_1AEA8 *font = (Obj_1_data_1AEA8 *)((u8 *)&lbl_1_data_1AEA8 + index * 0x38);
    f32 scale = font->unk_34;

    // Scale both font dimensions using the active font's metrics.
    lbl_1_bss_4B9CC.unk_1C = value1 * scale;
    lbl_1_bss_4B9CC.unk_20 = value2 * scale;
}
/* fzgx:end fn_1_4955C */

/* fzgx:begin fn_1_49590 */
void fn_1_49590(f32 value) {
    lbl_1_bss_4B9CC.unk_24 = value;
}
/* fzgx:end fn_1_49590 */

/* fzgx:begin fn_1_495A0 */
void fn_1_495A0(f32 value) {
    lbl_1_bss_4B9CC.unk_28 = value;
}
/* fzgx:end fn_1_495A0 */

/* fzgx:begin fn_1_495B0 */
void fn_1_495B0(u32 value) {
    lbl_1_bss_4B9CC.unk_2C |= value;
}
/* fzgx:end fn_1_495B0 */

/* fzgx:begin fn_1_495C8 */
void fn_1_495C8(u8 value) {
    // Update the current font state flag.
    lbl_1_bss_4B9CC.unk_36 = value;
}
/* fzgx:end fn_1_495C8 */

/* fzgx:begin fn_1_495D8 */
void fn_1_495D8(u16 value1, u16 value2, f32 value3) {
    lbl_1_bss_4B9CC.unk_32 = value1;
    lbl_1_bss_4B9CC.unk_2C |= 0x40000000;
    lbl_1_bss_4B9CC.unk_34 = value2;
    lbl_1_bss_4B9CC.unk_38 = value3;
}
/* fzgx:end fn_1_495D8 */

/* fzgx:begin fn_1_495FC */
void fn_1_495FC(void) {
    lbl_1_bss_4B9CC.unk_2C |= 0x40000000;
}
/* fzgx:end fn_1_495FC */

/* fzgx:begin fn_1_49614 */
void fn_1_49614(void) {
    lbl_1_bss_4B9CC.unk_2C &= 0xBFFFFFFF;
}
/* fzgx:end fn_1_49614 */

/* fzgx:begin fn_1_4962C */
void fn_1_4962C(void) {
    lbl_1_bss_4B9CC.unk_2C |= 0x20000000;
}
/* fzgx:end fn_1_4962C */

/* fzgx:begin fn_1_49644 */
void fn_1_49644(void) {
    lbl_1_bss_4B9CC.unk_2C &= 0xDFFFFFFF;
}
/* fzgx:end fn_1_49644 */

/* fzgx:begin fn_1_4965C */
void fn_1_4965C(u8 value) {
    lbl_1_bss_4B9CC.unk_37 = value;
}
/* fzgx:end fn_1_4965C */

/* fzgx:begin fn_1_4966C */
void fn_1_4966C(f32 value1, f32 value2) {
    // Store the two font scale values used by the renderer.
    lbl_1_bss_4B9CC.unk_3C = value1;
    lbl_1_bss_4B9CC.unk_40 = value2;
}
/* fzgx:end fn_1_4966C */

/* fzgx:begin fn_1_49680 */
// Scale the active font entry's byte dimensions into the shared bounds.
void fn_1_49680(f32 value1, f32 value2) {
    Obj_1_data_1AEA8 *entry;
    s16 index;
    f32 result1;
    f32 result2;

    index = lbl_1_bss_4B9CC.unk_C;
    entry = (Obj_1_data_1AEA8 *)((u8 *)&lbl_1_data_1AEA8 + index * 0x38);
    result1 = entry->unk_34 * (value1 * (f32)entry->unk_4);
    result2 = entry->unk_34 * (value2 * (f32)entry->unk_5);
    lbl_1_bss_4B9CC.unk_4 = result1;
    lbl_1_bss_4B9CC.unk_0 = result1;
    lbl_1_bss_4B9CC.unk_8 = result2;
}
/* fzgx:end fn_1_49680 */

/* fzgx:begin fn_1_496FC */
 // Store the two font coordinates in the shared state.
void fn_1_496FC(f32 value1, f32 value2) {
    lbl_1_bss_4B9CC.unk_4 = value1;
    lbl_1_bss_4B9CC.unk_0 = value1;
    lbl_1_bss_4B9CC.unk_8 = value2;
}
/* fzgx:end fn_1_496FC */

/* fzgx:begin fn_1_49714 */
void fn_1_49714(f32 value1, f32 value2, f32 value3) {
    lbl_1_bss_4B9CC.unk_0 = value3;
    lbl_1_bss_4B9CC.unk_4 = value1;
    lbl_1_bss_4B9CC.unk_8 = value2;
}
/* fzgx:end fn_1_49714 */

/* fzgx:begin fn_1_49728 */
void fn_1_49728(u8 value) {
    lbl_1_bss_4B9CC.unk_45 = value;
}
/* fzgx:end fn_1_49728 */

/* fzgx:begin fn_1_49738 */
 // Store the supplied value in the font state used by subsequent rendering.
void fn_1_49738(u32 value) {
    lbl_1_bss_4B9CC.unk_54 = value;
}
/* fzgx:end fn_1_49738 */

/* fzgx:begin fn_1_49748 */
void fn_1_49748(f32 value) {
    lbl_1_bss_4B9CC.unk_50 = value;
}
/* fzgx:end fn_1_49748 */

/* fzgx:begin fn_1_49758 */
void fn_1_49758(u8 value) {
    lbl_1_bss_4B9CC.unk_46 = value;
}
/* fzgx:end fn_1_49758 */

/* fzgx:begin fn_1_49768 */
void fn_1_49768(u8 value) {
    lbl_1_bss_4B9CC.unk_47 = value;
}
/* fzgx:end fn_1_49768 */

/* fzgx:begin fn_1_49778 */
void fn_1_49778(s16 value1, s16 value2, s16 value3, s16 value4) {
    lbl_1_bss_4B9CC.unk_48 = value1;
    lbl_1_bss_4B9CC.unk_4A = value2;
    lbl_1_bss_4B9CC.unk_4C = value3;
    lbl_1_bss_4B9CC.unk_4E = value4;
}
/* fzgx:end fn_1_49778 */

/* fzgx:begin fn_1_49794 */
u32 fn_1_49794(u32 c) {
    if ((u16)c >= 'A' && (u16)c <= 'Z') {
        return c + 0x821F;
    }
    if ((u16)c >= 'a' && (u16)c <= 'z') {
        return c + 0x8220;
    }
    if ((u16)c >= '0' && (u16)c <= '9') {
        return c + 0x821F;
    }

    switch ((u8)c) {
    case '!':
        return 0x8149;
    case '"':
        return 0x8168;
    case '#':
        return 0x8194;
    case '$':
        return 0x8190;
    case '%':
        return 0x8193;
    case '&':
        return 0x8195;
    case '\'':
        return 0x8166;
    case '(':
        return 0x8169;
    case ')':
        return 0x816A;
    case '*':
        return 0x8196;
    case '+':
        return 0x817B;
    case ',':
        return 0x8143;
    case '-':
        return 0x817C;
    case '.':
        return 0x8144;
    case '/':
        return 0x815E;
    case ':':
        return 0x8146;
    case ';':
        return 0x8147;
    case '<':
        return 0x8171;
    case '=':
        return 0x8181;
    case '>':
        return 0x8172;
    case '?':
        return 0x8148;
    case '@':
        return 0x8197;
    case '[':
        if ((s32)lbl_1_bss_3E058 == 0) {
            return 0x816D;
        }
        break;
    case '\\':
        return 0x815F;
    case ']':
        if ((s32)lbl_1_bss_3E058 == 0) {
            return 0x816E;
        }
        break;
    case '^':
        return 0x814F;
    case '_':
        return 0x8151;
    case '`':
        return 0x8165;
    case '{':
        return 0x816F;
    case '|':
        return 0x8162;
    case '}':
        return 0x8170;
    case '~':
        return 0x8160;
    }

    return c;
}
/* fzgx:end fn_1_49794 */

/* fzgx:begin fn_1_499BC */
extern u8 jumptable_1_data_1BEFC[220];

u16 fn_1_499BC(const u8 *value) {
    u16 result;
    s32 i;
    s32 shift;
    const u8 *p;

    if (value[0] != 'c') {
        return value[0];
    }
    if (value[1] != '0') {
        return value[0];
    }
    p = value + 2;
    if (value[2] != 'x') {
        return value[0];
    }
    result = 0;
    shift = 12;
    for (i = 0; i < 4; i++) {
        switch (p[i + 1]) {
        case '0':
            result |= 1 << shift;
            break;
        case '1':
            result |= 2 << shift;
            break;
        case '2':
            result |= 3 << shift;
            break;
        case '3':
            result |= 4 << shift;
            break;
        case '4':
            result |= 5 << shift;
            break;
        case '5':
            result |= 6 << shift;
            break;
        case '6':
            result |= 7 << shift;
            break;
        case '7':
            result |= 8 << shift;
            break;
        case '8':
            result |= 9 << shift;
            break;
        case '9':
            result |= 10 << shift;
            break;
        case 'A':
        case 'a':
            result |= 11 << shift;
            break;
        case 'B':
        case 'b':
            result |= 12 << shift;
            break;
        case 'C':
        case 'c':
            result |= 13 << shift;
            break;
        case 'D':
        case 'd':
            result |= 14 << shift;
            break;
        case 'E':
        case 'e':
            result |= 15 << shift;
            break;
        case 'F':
        case 'f':
            break;
        default:
            break;
        }
        shift -= 4;
    }
    return result;
}
/* fzgx:end fn_1_499BC */

/* fzgx:begin fn_1_4AC20 */
extern f32 fn_1_519FC(f32 value);
extern f32 fn_1_51AC0(f32 value);
extern f32 fn_1_51B84(f32 value);
extern f32 fn_1_51BFC(f32 value);
extern const f64 lbl_1_rodata_10F8;
extern void fn_1_4F734(void *value);
extern void fn_1_4E500(void);
extern void fn_1_48D80(void *value);
extern void fn_1_4E6F4(void);
extern void fn_1_4E724(void *value);

typedef struct {
    u32 unk_0;
    f32 x;
    f32 y;
    u8 pad_C[4];
    f32 z;
    f32 w;
    u8 pad_20[0x18];
    u32 flag;
    u8 tail[0x24];
} FontData;

void fn_1_4AC20(FontData *value) {
    FontData local = *value;
    int x_max;
    int x_ok;
    int y_max;
    int y_ok;

    if (lbl_1_bss_4B9CC.unk_45 != 0) {
        local.x = fn_1_519FC(local.x);
        local.y = fn_1_51AC0(local.y);
        local.z = fn_1_51B84(local.z);
        local.w = fn_1_51BFC(local.w);
    }

    if (lbl_1_bss_4B9CC.unk_47 != 0) {
        x_ok = (local.x > (f32)(lbl_1_bss_4B9CC.unk_48 + lbl_1_bss_4B9CC.unk_4C))
                   ? 0
                   : ((local.x < (f32)lbl_1_bss_4B9CC.unk_48) ? 0 : 1);
        if (x_ok == 0 ||
            (y_ok = (local.y > (f32)(lbl_1_bss_4B9CC.unk_4A + lbl_1_bss_4B9CC.unk_4E))
                        ? 0
                        : ((local.y < (f32)lbl_1_bss_4B9CC.unk_4A) ? 0 : 1)) == 0) {
            return;
        }
    }

    if (lbl_1_bss_4B9CC.unk_44 != 0) {
        fn_1_4F734(&local);
    } else if ((local.flag & 0x400000) != 0) {
        if (lbl_1_bss_4B9CC.unk_46 == 0) {
            fn_1_4E500();
        }
        fn_1_48D80(&local);
        if (lbl_1_bss_4B9CC.unk_46 == 0) {
            fn_1_4E6F4();
        }
    } else {
        fn_1_4E724(&local);
    }
}
/* fzgx:end fn_1_4AC20 */

/* fzgx:begin fn_1_4AE0C */
#include "runtime/va_list.h"
#include "font.h"

int fn_8008077C(char* output, const char* format, __va_list args);

void fn_1_4AE0C(const char* format, ...) {
    char buffer[512];
    __va_list args;
    __builtin_va_info(&args);
    fn_8008077C(buffer, format, args);
    fn_1_4A0D8(buffer);
}
/* fzgx:end fn_1_4AE0C */

/* fzgx:begin fn_1_4AEB4 */
void fn_1_4AEB4(f32 value) {
    lbl_1_bss_3E05C = value;
}
/* fzgx:end fn_1_4AEB4 */

/* fzgx:begin fn_1_4AEC0 */
u32 fn_1_4AEC0(u32 value) {
    u32 previous = lbl_1_bss_3E058;

    lbl_1_bss_3E05C = lbl_1_rodata_10C0[0];
    lbl_1_bss_3E058 = value;

    return previous;
}
/* fzgx:end fn_1_4AEC0 */

/* fzgx:begin fn_1_4B040 */
void fn_1_4B040(s32 value) {
    fn_1_4B1D4(0, value);
}
/* fzgx:end fn_1_4B040 */

/* fzgx:begin fn_1_4B068 */
void fn_1_4B068(s32 value) {
    fn_1_4B1D4(1, value);
}
/* fzgx:end fn_1_4B068 */

/* fzgx:begin fn_1_4B16C */
s32 fn_1_4B16C(s32 value) {
    return (s32)fn_1_4B1D4(2, value);
}
/* fzgx:end fn_1_4B16C */

/* fzgx:begin fn_1_4B1A0 */
s32 fn_1_4B1A0(s32 value) {
    return (s32)fn_1_4B1D4(3, value);
}
/* fzgx:end fn_1_4B1A0 */

/* fzgx:begin fn_1_4B83C */
void fn_1_4B83C(void *arg0, void *arg1, u32 arg2, const char *arg3) {
    u32 length;
    s32 converted;

    length = strlen(arg3);
    converted = (s32)fn_1_4B1D4(3, arg2 + length);
    sprintf(arg0, arg1, length + converted);
}
/* fzgx:end fn_1_4B83C */

/* fzgx:begin fn_1_4B8BC */
void fn_1_4B8BC(void) {
    lbl_1_bss_4BA58 = 0;
}
/* fzgx:end fn_1_4B8BC */

/* fzgx:begin fn_1_4B8CC */
void fn_1_4B8CC(void) {
    lbl_1_bss_4BA5C = 0;
}
/* fzgx:end fn_1_4B8CC */

/* fzgx:begin fn_1_4BD48 */
// fn_1_4BD48: empty in retail (single blr).
void fn_1_4BD48(void) {
}
/* fzgx:end fn_1_4BD48 */

/* fzgx:begin fn_1_4CDE4 */
/* Convert the selected font entry's byte metrics to floating-point coordinates. */
void fn_1_4CDE4(f32 *x, f32 *y) {
    Obj_1_data_1AEA8 *entry;
    s16 index;

    index = lbl_1_bss_4B9CC.unk_C;
    entry = (Obj_1_data_1AEA8 *)((u8 *)&lbl_1_data_1AEA8 + index * 0x38);
    *x = (f32)(u32)entry->unk_4;
    *y = (f32)(u32)entry->unk_5;
}
/* fzgx:end fn_1_4CDE4 */

/* fzgx:begin fn_1_4CE48 noprologue */
#include "types.h"
#include "rel/main_rel/font.h"

extern f32 fn_1_4B1D4(s32, Obj_1_bss_4B9CC *);
extern f64 lbl_1_rodata_10F8[688];
extern void fn_1_4A0D8(Obj_1_bss_4B9CC *);

void fn_1_4CE48(Obj_1_bss_4B9CC *obj, f32 limit) {
    f32 saved;
    f32 first;
    f32 adjusted;
    s32 count;

    saved = lbl_1_bss_4B9CC.unk_1C;
    first = fn_1_4B1D4(1, obj);
    count = (s32)fn_1_4B1D4(3, obj);
    count = count - 1;
    adjusted = lbl_1_bss_4B9CC.unk_3C * (f32)count;
    adjusted = first + adjusted;
    if (adjusted > limit) {
        lbl_1_bss_4B9CC.unk_1C =
            lbl_1_bss_4B9CC.unk_1C * (limit / adjusted);
    }
    fn_1_4A0D8(obj);
    lbl_1_bss_4B9CC.unk_1C = saved;
}
/* fzgx:end fn_1_4CE48 */

/* fzgx:begin fn_1_4D0A0 */
extern u8 lbl_1_rodata_FD0[];

void fn_1_4D0A0(void) {
    Obj_1_bss_4BA30 *bss = &lbl_1_bss_4BA30;
    f32 *rodata = (f32 *)lbl_1_rodata_FD0;

    bss->unk_0 = 1;
    bss->unk_4 = rodata[0x16ac / 4];
    bss->unk_8 = rodata[0xf0 / 4];
    bss->unk_C = rodata[0x16b0 / 4];
    bss->unk_10 = rodata[0xf0 / 4];
}
/* fzgx:end fn_1_4D0A0 */

/* fzgx:begin fn_1_4D0D4 */
void fn_1_4D0D4(u32 *object, f32 value) {
    u32 data = *object;
    fn_1_4D10C(&data, lbl_1_rodata_26B8[0], value);
}
/* fzgx:end fn_1_4D0D4 */

/* fzgx:begin fn_1_4D274 */
void fn_1_4D274(u32 *object, f32 value) {
    u32 data = *object;
    fn_1_4D2AC(&data, lbl_1_rodata_26B8[0], value);
}
/* fzgx:end fn_1_4D274 */

/* fzgx:begin fn_1_4DC20 */
typedef struct {
    u32 words[23];
} FontStateCopy;

void fn_1_4DC20(void) {
    *(FontStateCopy *)&lbl_1_bss_4BB40 =
        *(FontStateCopy *)&lbl_1_bss_4B9CC;
    lbl_1_bss_4BB3C = 1;
}
/* fzgx:end fn_1_4DC20 */

/* fzgx:begin fn_1_4DC6C */
void fn_1_4DC6C(void) {
    lbl_1_bss_4B9CC = *(Obj_1_bss_4B9CC *)&lbl_1_bss_4BB40;
    lbl_1_bss_4BB3C = 0;
}
/* fzgx:end fn_1_4DC6C */

/* fzgx:begin fn_1_4DCB8 */
// Replaces the stored font state value and returns its previous value.
u32 fn_1_4DCB8(u32 value) {
    u32 old_value = lbl_1_bss_4B9CC.unk_58;
    lbl_1_bss_4B9CC.unk_58 = value;
    return old_value;
}
/* fzgx:end fn_1_4DCB8 */

/* fzgx:begin fn_1_4DCD0 */
// Returns the address of the font data embedded in the global object.
u8 *fn_1_4DCD0(void) {
    return (u8 *)&lbl_1_bss_4C688.unk_C;
}
/* fzgx:end fn_1_4DCD0 */

/* fzgx:begin fn_1_4DCE0 */
u8 *fn_1_4DCE0(void) {
    return (u8 *)&lbl_1_bss_4C688 + 0x10;
}
/* fzgx:end fn_1_4DCE0 */

/* fzgx:begin fn_1_4DCF0 */
u8 *fn_1_4DCF0(void) {
    return (u8 *)&lbl_1_bss_4C688 + 0x14;
}
/* fzgx:end fn_1_4DCF0 */

/* fzgx:begin fn_1_4DD00 */
u8 *fn_1_4DD00(void) {
    return (u8 *)&lbl_1_bss_4C688 + 0x18;
}
/* fzgx:end fn_1_4DD00 */

/* fzgx:begin fn_1_4DD10 */
u8 *fn_1_4DD10(void) {
    return &lbl_1_bss_4C688.pad_10[0xc];
}
/* fzgx:end fn_1_4DD10 */

/* fzgx:begin fn_1_4DD20 */
u8 *fn_1_4DD20(void) {
    return (u8 *)&lbl_1_bss_4C688 + 0x30;
}
/* fzgx:end fn_1_4DD20 */

/* fzgx:begin fn_1_4DD30 */
u8 *fn_1_4DD30(void) {
    return &lbl_1_bss_4C688.pad_4[0x30];
}
/* fzgx:end fn_1_4DD30 */

/* fzgx:begin fn_1_4DD40 */
u8 *fn_1_4DD40(void) {
    return (u8 *)&lbl_1_bss_4C688 + 0x40;
}
/* fzgx:end fn_1_4DD40 */

/* fzgx:begin fn_1_4DD50 */
u8 *fn_1_4DD50(void) {
    // Return the byte address used by the font data at offset 0x41.
    return &lbl_1_bss_4C688.pad_4[0x3d];
}
/* fzgx:end fn_1_4DD50 */

/* fzgx:begin fn_1_4DD60 */
u8 *fn_1_4DD60(void) {
    return &lbl_1_bss_4C688.pad_4[0x3e];
}
/* fzgx:end fn_1_4DD60 */

/* fzgx:begin fn_1_4DD70 */
u8 *fn_1_4DD70(void) {
    return (u8 *)&lbl_1_bss_4C688 + 0x44;
}
/* fzgx:end fn_1_4DD70 */

/* fzgx:begin fn_1_4DD80 */
u8 *fn_1_4DD80(void) {
    return &lbl_1_bss_4C688.pad_4[0x41];
}
/* fzgx:end fn_1_4DD80 */

/* fzgx:begin fn_1_4DD90 */
u8 *fn_1_4DD90(void) {
    return &lbl_1_bss_4C688.pad_4[0x42];
}
/* fzgx:end fn_1_4DD90 */

/* fzgx:begin fn_1_4DDA0 */
 // Return the byte address six bytes into the shared font state.
u8 *fn_1_4DDA0(void) {
    return &lbl_1_bss_4C688.pad_4[2];
}
/* fzgx:end fn_1_4DDA0 */

/* fzgx:begin fn_1_4DDB0 */
u8 *fn_1_4DDB0(void) {
    return &lbl_1_bss_4C688.pad_10[0x50];
}
/* fzgx:end fn_1_4DDB0 */

/* fzgx:begin fn_1_4DE44 */
// Dispatch callbacks for each active font entry.
void fn_1_4DE44(void) {
    int i;
    u32 *entry;

    if (fn_1_3F164() == 0) {
        entry = &lbl_1_bss_4C688.unk_0;
        for (i = 0; i < 0x40; i++, entry += 0x20) {
            if ((int)entry[0] != 0 && entry[0x1e] != 0) {
                ((void (*)(u32 *))entry[0x1e])(entry);
            }
        }
    }
}
/* fzgx:end fn_1_4DE44 */

/* fzgx:begin fn_1_4DEC0 noprologue */
#include "types.h"
#include "font.h"

typedef u32 (*fn_1_4DEC0_Fn0)(u32);
struct fn_1_4DEC0_Copy88 { u32 a[22]; };
extern u32 lbl_1_bss_4C688;
extern int fn_1_4F734(FontDrawPacket *);

struct FzgxCopy_88 { u32 words[22]; };
void fn_1_4DEC0(void) {
    struct FzgxCopy_88 loc_8;
    s32 sp4;
    s32 (*temp_r12)(u32 *);
    s32 var_r31;
    u32 *var_r30;

    var_r31 = 0;
    var_r30 = (u32 *)(&lbl_1_bss_4C688);
    do {
        if ((s32) (*(u32 *)((u8 *)(var_r30) + 0)) != 0) {
            temp_r12 = (s32 (*)(u32 *))(*(s32 (**)(u32 *))((u8 *)(var_r30) + 124));
            if (temp_r12 == NULL) {
                loc_8 = *(const struct FzgxCopy_88 *)((((s32)(((u8 *)(var_r30) + 4))) + 4));
                fn_1_4F734((FontDrawPacket *)((FontDrawPacket *) &loc_8));
            } else {
                temp_r12((u32 *)(var_r30));
            }
        }
        var_r31 += 1;
        var_r30 = (u32 *)((u8 *)(var_r30) + 0x80);
    } while (var_r31 < 0x40);
}
/* fzgx:end fn_1_4DEC0 */

/* fzgx:begin fn_1_4DF60 */
extern f32 lbl_1_rodata_26F8[22];
extern const f32 lbl_1_rodata_2750;

typedef struct {
    u32 values[22];
} InitData;

typedef struct {
    s32 unk_0;
    u8 pad[0x7c];
} Slot;

Slot *fn_1_4DF60(void) {
    int i;
    Slot *p;

    p = (Slot *)&lbl_1_bss_4C688;
    for (i = 0; i < 64; i++, p++) {
        if (p->unk_0 == 0) {
            break;
        }
    }

    if (p->unk_0 != 0) {
        return 0;
    }

    *(s32 *)((u8 *)p + 0) = 1;
    *(InitData *)((u8 *)p + 8) = *(InitData *)lbl_1_rodata_26F8;
    *(u16 *)((u8 *)p + 6) = 0;
    *(u32 *)((u8 *)p + 0x68) = 0;
    *(u32 *)((u8 *)p + 0x64) = 0;
    *(u32 *)((u8 *)p + 0x60) = 0;
    *(f32 *)((u8 *)p + 0x74) = lbl_1_rodata_2750;
    *(f32 *)((u8 *)p + 0x70) = lbl_1_rodata_2750;
    *(f32 *)((u8 *)p + 0x6c) = lbl_1_rodata_2750;
    *(u32 *)((u8 *)p + 0x7c) = 0;
    *(u32 *)((u8 *)p + 0x78) = 0;
    *(u8 *)((u8 *)p + 4) = 0;
    return p;
}
/* fzgx:end fn_1_4DF60 */

/* fzgx:begin fn_1_4E0A4 */
typedef struct FontMetric {
    f32 value;
    u8 pad[0x54];
} FontMetric;

int fn_1_4E0A4(u16 *left, u16 *right) {
    u16 left_index;
    FontMetric *metrics;
    u16 right_index;
    f32 left_value;
    f32 right_value;

    left_index = *left;
    metrics = (FontMetric *)(*(u32 *)&lbl_1_data_1C504 + 0xc);
    right_index = *right;

    left_value = metrics[left_index].value;
    right_value = metrics[right_index].value;
    if (left_value > right_value) {
        return -1;
    }
    if (left_value == right_value) {
        return 0;
    }
    return 1;
}
/* fzgx:end fn_1_4E0A4 */

/* fzgx:begin fn_1_4E0F4 */
void fn_1_4E0F4(void) {
    fn_800724C8();
    fn_8007245C(0x2200);
    fn_80074788(0);
    fn_80074660(1);
    fn_80073678(1);
    fn_80073898(0);
    fn_80073C6C(0);
    fn_800745A4(0, 1, 4, 0x3c, 0, 0x7d);
    fn_800734A8(0, 0, 0, 0xff);
    fn_80072AB0(0, 0, 0);
    fn_80072C24(0, 0xf, 2, 8, 4);
    fn_80072D64(0, 0, 0, 0, 1, 0);
    fn_80072CC4(0, 7, 1, 4, 2);
    fn_80072E20(0, 0, 0, 0, 1, 0);
    fn_80074918(1, 7, 0);
    fn_800728A8(1, 4, 5, 0);
    fn_800720B0(0);
    fn_80072864(2);
}
/* fzgx:end fn_1_4E0F4 */

/* fzgx:begin fn_1_4E500 */
void fn_1_4E500(void) {
    fn_1_A71CC();
    fn_800724C8();
    fn_8007245C(0x2200);
    fn_80074788(0);
    fn_80074660(1);
    fn_80073678(1);
    fn_80073898(0);
    fn_80073C6C(0);
    fn_800745A4(0, 1, 4, 0x3c, 0, 0x7d);
    fn_800734A8(0, 0, 0, 0xff);
    fn_80072AB0(0, 0, 0);
    fn_80072C24(0, 0xf, 2, 8, 4);
    fn_80072D64(0, 0, 0, 0, 1, 0);
    fn_80072CC4(0, 7, 1, 4, 2);
    fn_80072E20(0, 0, 0, 0, 1, 0);
    fn_80074918(1, 7, 0);
    fn_800728A8(1, 4, 5, 0);
    fn_800720B0(0);
    fn_80072864(2);
    lbl_8006D758();
    fn_80072558();
}
/* fzgx:end fn_1_4E500 */

/* fzgx:begin fn_1_4E638 */
void fn_1_4E638(s32 arg) {
    f32 *values;

    values = lbl_1_rodata_26F8;
    if (arg != 0) {
        fn_80015E18((u8 *)lbl_801A6D00 + 0xc8,
                    values[26], fn_1_A6FE8(), values[27], values[28]);
        fn_800737E4((u8 *)lbl_801A6D00 + 0xc8, 0);
    } else {
        fn_80015EE8((u8 *)lbl_801A6D00 + 0xc8,
                    values[22], values[29], values[22], values[30],
                    values[22], values[28]);
        fn_800737E4((u8 *)lbl_801A6D00 + 0xc8, 1);
    }
}
/* fzgx:end fn_1_4E638 */

/* fzgx:begin fn_1_4E6F4 */
void fn_1_4E6F4(void) {
    fn_1_A722C();
    fn_80074918(1, 3, 1);
}
/* fzgx:end fn_1_4E6F4 */

/* fzgx:begin fn_1_4E724 */
typedef struct FontParams {
    u8 unk_00[0x30];
    u32 unk_30;
    f32 unk_34;
    u8 unk_38[0x58 - 0x38];
} FontParams;

extern s32 fn_1_4EC74(FontParams *);
extern s32 fn_1_4EB74(FontParams *);
extern void *lbl_801A6D00;

// Initialize the font system and return the selected font resource.
s32 fn_1_4E724(FontParams *arg) {
    FontParams local = *arg;
    s32 ret;

    fn_1_A71CC();
    fn_800724C8();
    fn_8007245C(0x2200);
    fn_80074788(0);
    fn_80074660(1);
    fn_80073678(1);
    fn_80073898(0);
    fn_80073C6C(0);
    fn_800745A4(0, 1, 4, 0x3c, 0, 0x7d);
    fn_800734A8(0, 0, 0, 0xff);
    fn_80072AB0(0, 0, 0);
    fn_80072C24(0, 0xf, 2, 8, 4);
    fn_80072D64(0, 0, 0, 0, 1, 0);
    fn_80072CC4(0, 7, 1, 4, 2);
    fn_80072E20(0, 0, 0, 0, 1, 0);
    fn_80074918(1, 7, 0);
    fn_800728A8(1, 4, 5, 0);
    fn_800720B0(0);
    fn_80072864(2);
    lbl_8006D758();
    fn_80072558();

    if ((s32)lbl_1_bss_4E6A8 != 0) {
        local.unk_30 |= 0x08000000;
        local.unk_34 = (f32)(s32)lbl_1_bss_4E6AC;
    }

    ((u8 *)lbl_801A6D00)[0x197] = 0xff;

    if (local.unk_30 & 0x00800000) {
        ret = fn_1_4EC74(&local);
    } else {
        ret = fn_1_4EB74(&local);
    }

    fn_1_A722C();
    fn_80074918(1, 3, 1);

    return ret;
}
/* fzgx:end fn_1_4E724 */

/* fzgx:begin fn_1_4F724 */
// Clear the font state value before the next initialization.
void fn_1_4F724(void) {
    lbl_1_bss_646D2.unk_0 = 0;
}
/* fzgx:end fn_1_4F724 */

/* fzgx:begin fn_1_4F734 noprologue */
#include "types.h"
#include "font.h"

typedef struct State {
    FontDrawPacket *current;
    s32 warned;
    u8 unk_8[0x2028];
    s32 override_enabled, override_value;
    u32 texture[8];
} State;
typedef struct Config {
    u32 capacity;
    FontDrawPacket *packets;
    u8 unk_8[0x44];
    char warning[1];
} Config;
typedef struct ImageInfo {
    u8 unk_0[8];
    u16 width, height;
    u32 unk_C;
} ImageInfo;
typedef struct Images {
    u32 unk_0;
    ImageInfo *info;
    u32 unk_8;
    u32 (*textures)[8];
} Images;
typedef struct Resource {
    s32 loaded;
    u8 unk_4[0x1c];
    Images *images;
    u32 unk_24;
} Resource;
extern State lbl_1_bss_4C678;
extern Config lbl_1_data_1C500;
extern u16 lbl_1_bss_646D2;
extern u8 *lbl_801A6D00;
extern Resource lbl_1_data_FCD4[];
extern void fn_1_A71CC(void), fn_800724C8(void), lbl_8006D758(void), fn_80072558(void),
    fn_1_A722C(void);
extern void fn_8007245C(u32), fn_80074788(u32), fn_80074660(u32), fn_80073678(u32),
    fn_80073898(u32), fn_80073C6C(u32), fn_800720B0(u32), fn_80072864(u32);
extern void fn_800745A4(u32, u32, u32, u32, u32, u32), fn_80072D64(u32, u32, u32, u32, u32, u32),
    fn_80072E20(u32, u32, u32, u32, u32, u32);
extern void fn_800734A8(u32, u32, u32, u32), fn_800728A8(u32, u32, u32, u32);
extern void fn_80072AB0(u32, u32, u32), fn_80074918(u32, u32, u32);
extern void fn_80072C24(u32, u32, u32, u32, u32), fn_80072CC4(u32, u32, u32, u32, u32);
extern f32 fn_1_519AC(u32);
extern void DCFlushRange(void *, u32);
extern void GXInitTexObj(void *, void *, u16, u16, u32, u32, u32, u8);
extern void GXInitTexObjLOD(void *, u32, u32, f32, f32, f32, u8, u8, u32);
extern void fn_80073778(void *, u32);
extern void fn_1_4EDAC(FontDrawPacket *, f32, f32);
extern void fn_1_159588(u32);
extern void OSReport(const char *, ...);
extern void *fn_80008BA8(void *, const void *, u32);
extern s32 fn_1_54298(void), fn_1_542A8(void);
extern f32 fn_1_542B8(void);
int fn_1_4F734(FontDrawPacket *input) {
    State *state = &lbl_1_bss_4C678;
    Config *config = &lbl_1_data_1C500;
    if (input->image >= 0xffff0000u)
        return 0;
    if (input->flags & 0x20000) {
        FontDrawPacket local = *input;
        int result;
        fn_1_A71CC();
        fn_800724C8();
        fn_8007245C(0x2200);
        fn_80074788(0);
        fn_80074660(1);
        fn_80073678(1);
        fn_80073898(0);
        fn_80073C6C(0);
        fn_800745A4(0, 1, 4, 0x3c, 0, 0x7d);
        fn_800734A8(0, 0, 0, 0xff);
        fn_80072AB0(0, 0, 0);
        fn_80072C24(0, 0xf, 2, 8, 4);
        fn_80072D64(0, 0, 0, 0, 1, 0);
        fn_80072CC4(0, 7, 1, 4, 2);
        fn_80072E20(0, 0, 0, 0, 1, 0);
        fn_80074918(1, 7, 0);
        fn_800728A8(1, 4, 5, 0);
        fn_800720B0(0);
        fn_80072864(2);
        lbl_8006D758();
        fn_80072558();
        if (state->override_enabled) {
            local.flags |= 0x08000000;
            local.depth = (f32)state->override_value;
        }
        lbl_801A6D00[0x197] = 0xff;
        if (local.flags & 0x800000) {
            if (local.flags & 0x2000000)
                result = 0;
            else {

                DCFlushRange(local.pixels, (u32)((f32)local.height *
                                                 ((f32)local.width * fn_1_519AC(local.format))));
                {
                    u32 width = local.width, height = local.height;
                    GXInitTexObj(state->texture, local.pixels, width, height, local.format, 0, 0, 0);
                }
                GXInitTexObjLOD(state->texture, 0, 0, 0.0f, 0.0f, 0.0f, 0, 0, 0);
                fn_80073778(state->texture, 0);
                fn_1_4EDAC(&local, (f32)local.width, (f32)local.height);
                result = 1;
            }
        } else {
            if (local.flags & 0x2000000)
                result = 0;
            else {
                Resource *resource;
                Resource *table;
                u32 id, index;
                fn_1_159588(local.image);
                table = lbl_1_data_FCD4;
                id = local.image;
                index = (id >> 8) & 0xffff;
                if (!table[index].loaded)
                    result = 0;
                else {
                    ImageInfo *info;
                    f32 height, width;
                    resource = table;
                    resource += index;
                    info = &resource->images->info[(u8)id];
                    width = (f32)info->width;
                    height = (f32)info->height;
                    fn_80073778(resource->images->textures[(u8)id], 0);
                    fn_1_4EDAC(&local, width, height);
                    result = 1;
                }
            }
        }
        fn_1_A722C();
        fn_80074918(1, 3, 1);
        return result;
    } else {
        u16 count = lbl_1_bss_646D2;
        FontDrawPacket *dst;
        if (count >= config->capacity) {
            if (!state->warned) {
                OSReport(config->warning);
                state->warned = 1;
            }
            return 0;
        }
        dst = &config->packets[count];
        fn_80008BA8(dst, input, 0x58);
        dst->x += (f32)fn_1_54298();
        dst->y += (f32)fn_1_542A8();
        dst->alpha *= fn_1_542B8();
        if (state->override_enabled) {
            dst->flags |= 0x08000000;
            dst->depth = (f32)state->override_value;
        }
        lbl_1_bss_646D2++;
        return 1;
    }
}
/* fzgx:end fn_1_4F734 */

/* fzgx:begin fn_1_4FC50 */
typedef struct {
    u32 unk_0;
} InputObject;

s32 fn_1_4FC50(InputObject *obj, u32 arg1, u16 arg2, u16 arg3, u32 arg4) {
    Obj_1_data_1C504_Target *entry;
    u16 index;

    if (obj->unk_0 >= 0xffff0000) {
        return 0;
    }
    index = lbl_1_bss_646D2.unk_0;
    if (index >= lbl_1_data_1C500) {
        return 0;
    }

    entry = (Obj_1_data_1C504_Target *)((u8 *)lbl_1_data_1C504 + index * 0x58);
    fn_80008BA8(entry, obj, 0x58);
    entry->unk_30 |= (u32)1 << 23;
    entry->unk_40 = arg1;
    entry->unk_44 = arg2;
    entry->unk_46 = arg3;
    entry->unk_48 = arg4;

    if ((s32)lbl_1_bss_4E6A8 != 0) {
        entry->unk_30 |= (u32)1 << 27;
        entry->unk_34 = (f32)(s32)lbl_1_bss_4E6AC;
    }

    lbl_1_bss_646D2.unk_0++;
    return 1;
}
/* fzgx:end fn_1_4FC50 */

/* fzgx:begin fn_1_50164 */
void fn_1_50164(f32 a, f32 b, f32 c, f32 d) {
    fn_1_50190(a, b, c, c, d, d);
}
/* fzgx:end fn_1_50164 */

/* fzgx:begin fn_1_51564 */
// Update the six halfwords that define the active font state.
void fn_1_51564(u16 first, u16 second, u16 third, u16 fourth, u16 fifth, u16 sixth) {
    ((u16 *)&lbl_1_bss_4C678)[0xC02e] = first;
    ((u16 *)&lbl_1_bss_4C678)[0xC02f] = second;
    ((u16 *)&lbl_1_bss_4C678)[0xC030] = third;
    ((u16 *)&lbl_1_bss_4C678)[0xC031] = fourth;
    ((u16 *)&lbl_1_bss_4C678)[0xC032] = fifth;
    ((u16 *)&lbl_1_bss_4C678)[0xC033] = sixth;
}
/* fzgx:end fn_1_51564 */

/* fzgx:begin fn_1_51678 */
#include "font.h"

extern s16 fn_1_48690(u32), fn_1_486C4(u32);
void fn_1_51678(FontDrawPacket *p, u32 image, s16 x, s16 y, s16 width, s16 height) {
    f32 inv_height, inv_width;
    s32 texture_height, texture_width;
    p->image = image;
    texture_height = fn_1_486C4(image);
    texture_width = fn_1_48690(image);
    inv_width = 1.0f / texture_width;
    inv_height = 1.0f / texture_height;
    {
        f32 v, u, sy, sx;
        sx = (f32)width * inv_width;
        sy = (f32)height * inv_height;
        u = (f32)x * inv_width;
        v = (f32)y * inv_height;
        p->scale_x *= sx;
        p->scale_y *= sy;
        p->u0 = u;
        p->v0 = v;
    }
    p->u1 = inv_width * (f32)(x + width);
    p->v1 = inv_height * (f32)(y + height);
}
/* fzgx:end fn_1_51678 */

/* fzgx:begin fn_1_517EC */
#include "font.h"

void fn_1_517EC(FontDrawPacket *p, s16 x, s16 y, s16 width, s16 height, s16 texture_width,
                s16 texture_height) {
    f32 inv_height, inv_width;
    inv_width = 1.0f / texture_width;
    inv_height = 1.0f / texture_height;
    p->scale_x *= (f32)width * inv_width;
    p->scale_y *= (f32)height * inv_height;
    p->u0 = (f32)x * inv_width;
    p->v0 = (f32)y * inv_height;
    p->u1 = inv_width * (f32)(x + width);
    p->v1 = inv_height * (f32)(y + height);
}
/* fzgx:end fn_1_517EC */

/* fzgx:begin fn_1_51914 */
typedef struct {
    u32 words[22];
} fn_1_51914_state;

extern void fn_1_4F734(void *);

void fn_1_51914(const fn_1_51914_state *src) {
    fn_1_51914_state state = *src;

    lbl_1_bss_4C678 = (u32)lbl_1_data_1C504 +
        (u32)lbl_1_bss_646D2.unk_0 * 0x58;
    state.words[12] |= 0x2000000;
    fn_1_4F734(&state);
}
/* fzgx:end fn_1_51914 */

/* fzgx:begin fn_1_51990 */
// Copy the font state value and enable the corresponding object flag.
void fn_1_51990(void *obj) {
    *(u32 *)((u8 *)obj + 0x4c) = lbl_1_bss_4C678;
    *(u32 *)((u8 *)obj + 0x30) |= 0x01000000;
}
/* fzgx:end fn_1_51990 */

/* fzgx:begin fn_1_51AC0 */
extern void fn_80038F10(void *result);
extern u32 fn_1_A5DB0(void);
extern const f64 lbl_1_rodata_2758;
extern const f32 lbl_1_rodata_276C;

typedef struct {
    u8 unk0[4];
    f32 value0;
    u8 unk10[4];
    f32 value1;
    u8 tail[8];
} FnData;

f32 fn_1_51AC0(f32 value) {
    f32 input = value;
    f32 value0;
    f32 value1;
    f32 part;
    f32 denom;
    f32 result;
    FnData data;
    u64 padding;

    fn_80038F10(&data);
    value0 = data.value0;
    value1 = data.value1;
    denom = (f32)(fn_1_A5DB0() & 0xffff);
    part = lbl_1_rodata_276C * value0 / denom;
    denom = (f32)(fn_1_A5DB0() & 0xffff);
    result = input * value1 / denom;
    return result + part;
}
/* fzgx:end fn_1_51AC0 */

/* fzgx:begin fn_1_51B84 */
extern void fn_80038F10(void *obj);
extern u16 fn_1_A5D88(void);

typedef struct Fn151B84Tmp {
    u8 unk[8];
    f32 value;
    u8 rest[12];
} Fn151B84Tmp;

f32 fn_1_51B84(f32 value) {
    Fn151B84Tmp tmp;
    f32 factor;
    f32 input;
    input = value;
    fn_80038F10(&tmp);
    factor = tmp.value;
    return input * factor / (f32)fn_1_A5D88();
}
/* fzgx:end fn_1_51B84 */

/* fzgx:begin fn_1_51BFC */
typedef struct {
    u8 pad[0x0c];
    f32 value;
    u8 tail[8];
} Fn51BFCData;

extern void fn_80038F10(Fn51BFCData *data);
extern u32 fn_1_A5DB0(void);
extern const f64 lbl_1_rodata_2758;

f32 fn_1_51BFC(f32 value) {
    Fn51BFCData data;
    f32 factor;
    u32 count;

    fn_80038F10(&data);
    factor = data.value;
    return value * factor / (f32)(fn_1_A5DB0() & 0xffff);
}
/* fzgx:end fn_1_51BFC */

/* fzgx:begin fn_1_52070 */
void fn_1_52070(u32 value) {
    lbl_1_bss_4E6A8 = 1;
    lbl_1_bss_4E6AC = value;
}
/* fzgx:end fn_1_52070 */

/* fzgx:begin fn_1_52088 */
void fn_1_52088(void) {
    lbl_1_bss_4E6A8 = 0;
    lbl_1_bss_4E6AC = 0;
}
/* fzgx:end fn_1_52088 */

/* fzgx:begin fn_1_520A0 */
void fn_1_520A0(void) {
    u32 value_a;
    u32 value_b;

    value_a = lbl_1_bss_4E6A8;
    value_b = lbl_1_bss_4E6AC;
    lbl_1_bss_646E0 = value_a;
    lbl_1_bss_646E4 = value_b;
}
/* fzgx:end fn_1_520A0 */

/* fzgx:begin fn_1_520CC */
void fn_1_520CC(void) {
    u32 value_a;
    u32 value_b;

    value_a = lbl_1_bss_646E0;
    value_b = lbl_1_bss_646E4;
    lbl_1_bss_4E6A8 = value_a;
    lbl_1_bss_4E6AC = value_b;
}
/* fzgx:end fn_1_520CC */

/* fzgx:begin fn_1_520F8 noprologue */
#include "types.h"

extern s8 fn_1_A5DC4(s32 value);
extern s32 lbl_1_bss_4E6A8;
extern s32 lbl_1_bss_4E6AC;
extern f64 lbl_1_rodata_2778[2];
extern f32 lbl_1_rodata_2788[6];

f32 fn_1_520F8(s32 value) {
    s32 base;
    f32 scaled;

    if (fn_1_A5DC4(value) && lbl_1_bss_4E6A8 != 0) {
        base = lbl_1_bss_4E6AC;
        scaled = (f32)(value - base) * lbl_1_rodata_2788[0];
        return (f32)base + scaled;
    }
    return (f32)value;
}
/* fzgx:end fn_1_520F8 */

/* fzgx:begin fn_1_521B8 */
// Convert a font value to its scaled coordinate when the font system is active.
f32 fn_1_521B8(s32 value) {
    if (fn_1_A5DC4(value) && (s32)lbl_1_bss_4E6A8 != 0) {
        return lbl_1_rodata_2788[0] * (f32)value;
    }

    return (f32)value;
}
/* fzgx:end fn_1_521B8 */

/* fzgx:begin fn_1_52250 */
struct fn_1_52250_Arg0 {
    u8 pad_0[0x54];
    f32 unk_54;
};

struct fn_1_52250_Arg1 {
    f32 unk_0;
    u8 pad_4[0x8];
    f32 unk_C;
};

void fn_1_52250(struct fn_1_52250_Arg0 *arg0, struct fn_1_52250_Arg1 *arg1) {
    f32 addend;
    f32 current;

    current = arg1->unk_0;
    addend = arg0->unk_54;
    current = current + addend;
    arg1->unk_0 = current;
    current = arg1->unk_C;
    current = current + addend;
    arg1->unk_C = current;
}
/* fzgx:end fn_1_52250 */

/* fzgx:begin fn_1_527B4 noprologue */
#include "types.h"
#include "rel/main_rel/font.h"

extern const f32 lbl_1_rodata_2750;
extern const f32 lbl_1_rodata_2754;

typedef struct {
    u32 unk_0;
    f32 unk_4;
    f32 unk_8;
    u8 pad_C[0x4];
    f32 unk_10;
    f32 unk_14;
    u8 pad_18[0x10];
    s16 unk_28;
} FontState;

typedef struct {
    u8 pad_0[0x20];
    Obj_1_data_FCD4_At20 *unk_20;
    u8 pad_24[0x4];
} FontTableEntry;

extern void fn_80074918(s32 arg0, s32 arg1, s32 arg2);
extern void lbl_8006D7F4(f32 arg0, f32 arg1, f32 arg2);
extern void lbl_8006E15C(f32 arg0, f32 arg1, f32 arg2);
extern void mathutil_mtxA_rotate_z(s16 arg0);
extern void lbl_8006DD7C(void);
extern void lbl_8006DB74(void *arg0);
extern void fn_800745A4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
extern void GXLoadTexMtxImm(void *arg0, s32 arg1, s32 arg2);
extern void fn_80073778(void *arg0, s32 arg1);
extern void fn_80074660(s32 arg0);
extern void fn_80073678(s32 arg0);
extern void fn_80073C6C(s32 arg0);
extern void fn_800734A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void fn_80072C24(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void fn_80072D64(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
extern void fn_80072CC4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void fn_80072E20(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

void fn_1_527B4(void) {
    u8 scratch[0x30];
    FontState *state;
    FontTableEntry *entry;
    Obj_1_data_FCD4_At20 *obj;
    u32 value;
    u32 index;

    state = (FontState *)lbl_1_bss_4C678;
    if (state != 0) {
        fn_80074918(1, 3, 1);
        lbl_8006D7F4(state->unk_4, state->unk_8, lbl_1_rodata_2750);
        lbl_8006E15C(state->unk_10, state->unk_14, lbl_1_rodata_2754);
        mathutil_mtxA_rotate_z(state->unk_28);
        lbl_8006DD7C();
        lbl_8006DB74(&scratch[0]);
        fn_800745A4(1, 1, 4, 0x21, 0, 0x7d);
        GXLoadTexMtxImm(&scratch[0], 0x21, 1);
        value = state->unk_0;
        index = ((value >> 8) & 0xffff) * 0x28;
        entry = (FontTableEntry *)&lbl_1_data_FCD4;
        entry = (FontTableEntry *)((u8 *)entry + index);
        obj = entry->unk_20;
        if (lbl_1_rodata_2750 == state->unk_10 ||
            lbl_1_rodata_2750 == state->unk_14 ||
            obj == 0) {
            return;
        }
        fn_80073778((void *)((u8 *)obj->unk_C + ((value & 0xff) << 5)), 1);
    }
    fn_80074660(2);
    fn_80073678(2);
    fn_80073C6C(1);
    fn_800734A8(1, 1, 1, 0xff);
    fn_80072C24(0, 0xf, 0xf, 0xf, 0xf);
    fn_80072C24(1, 4, 0xc, 8, 0xf);
    fn_80072D64(1, 0, 0, 0, 1, 0);
    fn_80072CC4(1, 7, 7, 7, 0);
    fn_80072E20(1, 0, 0, 0, 1, 0);
}
/* fzgx:end fn_1_527B4 */

/* fzgx:begin fn_1_52B68 */
void fn_1_52B68(void *arg0, void *arg1) {
    fn_1_52BF8(arg0, arg1, 0);
}
/* fzgx:end fn_1_52B68 */

/* fzgx:begin fn_1_52B8C */
void fn_1_52B8C(void *arg0, void *arg1) {
    fn_1_52BF8(arg0, arg1, 0x1000);
}
/* fzgx:end fn_1_52B8C */

/* fzgx:begin fn_1_52BB0 */
void fn_1_52BB0(void *arg0, void *arg1) {
    fn_1_52BF8(arg0, arg1, 0x2000);
}
/* fzgx:end fn_1_52BB0 */

/* fzgx:begin fn_1_52BD4 */
void fn_1_52BD4(void *arg0, void *arg1) {
    fn_1_52BF8(arg0, arg1, 0x3000);
}
/* fzgx:end fn_1_52BD4 */

/* fzgx:begin fn_1_5415C */
void fn_1_5415C(void *arg, s32 value) {
    fn_1_541A8(arg, value);
}
/* fzgx:end fn_1_5415C */

/* fzgx:begin fn_1_5417C */
void fn_1_5417C(void *arg) {
    fn_1_541A8(arg, lbl_801A66B4);
}
/* fzgx:end fn_1_5417C */

/* fzgx:begin fn_1_541A8 */
// Select the localized form for a number and column, including the special 10–20 range.
void *fn_1_541A8(void *arg, s32 column) {
    s32 is_special;
    u32 remainder;
    s32 row_index;
    u32 *row;
    u32 number = (u32)arg;

    if (number == 0) {
        return &lbl_1_data_1C5DC;
    }

    remainder = number - (number / 100) * 100;
    is_special = 0;
    if (remainder >= 10 && remainder <= 20) {
        is_special = 1;
    }

    if (is_special != 0) {
        row_index = 3;
    } else {
        number = remainder - (remainder / 10) * 10;
        is_special = 0;
        if (number >= 4 || number == 0) {
            is_special = 1;
        }
        row_index = 3;
        if (is_special == 0) {
            row_index = number - 1;
        }
    }

    row = (u32 *)(lbl_1_data_1C5EC + row_index * 24);
    return (void *)row[column < 0 ? 0 : (column > 5 ? 5 : column)];
}
/* fzgx:end fn_1_541A8 */

/* fzgx:begin fn_1_54278 */
void fn_1_54278(u32 arg0, u32 arg1) {
    lbl_1_bss_4C680 = arg0;
    lbl_1_bss_4C684 = arg1;
}
/* fzgx:end fn_1_54278 */

/* fzgx:begin fn_1_5428C */
void fn_1_5428C(f32 value) {
    lbl_1_data_1C508.unk_0 = value;
}
/* fzgx:end fn_1_5428C */

/* fzgx:begin fn_1_54298 */
u32 fn_1_54298(void) {
    return lbl_1_bss_4C680;
}
/* fzgx:end fn_1_54298 */

/* fzgx:begin fn_1_542A8 */
u32 fn_1_542A8(void) {
    return lbl_1_bss_4C684;
}
/* fzgx:end fn_1_542A8 */

/* fzgx:begin fn_1_542B8 */
f32 fn_1_542B8(void) {
    return lbl_1_data_1C508.unk_0;
}
/* fzgx:end fn_1_542B8 */

/* fzgx:begin fn_1_542C4 */
extern void fn_1_54320(void);
extern u8 *lbl_801A66CC;

typedef struct fn_1_542C4_FontState {
    u8 pad30[0x30];
    void *unk_30;
    void *unk_34;
    f32 unk_38;
    f32 unk_3C;
    f32 unk_40;
    u8 pad44[8];
    f32 unk_4C;
} fn_1_542C4_FontState;

// Volatile preserves the repeated loads of the shared font state.
#define FONT_STATE ((volatile fn_1_542C4_FontState *)lbl_801A66CC)

// Store the current font parameters and notify the font system.
void fn_1_542C4(void *arg0, void *arg1, f32 arg2, f32 arg3, f32 arg4) {
    FONT_STATE->unk_30 = arg0;
    FONT_STATE->unk_34 = arg1;
    FONT_STATE->unk_38 = arg2;
    FONT_STATE->unk_3C = arg3;
    FONT_STATE->unk_40 = arg4;
    FONT_STATE->unk_4C = arg4 - arg3;
    fn_1_54320();
}
/* fzgx:end fn_1_542C4 */

/* fzgx:begin fn_1_54320 noprologue */
#include "types.h"

extern struct fn_1_54320_lbl_801A66CC lbl_801A66CC;
extern u32 fn_1_54668(u32, u32, u32);

struct fn_1_54320_lbl_801A66CC {
    u32 unk_0;
};

u32 fn_1_54320(void) {
    u32 v0;
    u32 v1;
    u32 v2;
    v0 = lbl_801A66CC.unk_0;
    fn_1_54668(*(u32 *)((u8 *)v0 + 48), *(u32 *)((u8 *)v0 + 52), 1);
    v1 = lbl_801A66CC.unk_0;
    *(u32 *)((u8 *)v1 + 68) = (*(u32 *)((u8 *)v1 + 48) + ((*(u32 *)((u8 *)v1 + 52) - 1) << 3));
    v2 = lbl_801A66CC.unk_0;
    *(u32 *)((u8 *)v2 + 72) = *(u32 *)((u8 *)v2 + 48);
    return v2;
}
/* fzgx:end fn_1_54320 */

/* fzgx:begin fn_1_54384 noprologue */
#include "types.h"
#include "rel/main_rel/globals.h"

typedef struct FontState {
    u8 pad_00[0x30];
    u8 *glyphs;
    s32 glyph_count;
    f32 start;
    f32 end;
    u8 pad_40[4];
    u8 *lower;
    u8 *upper;
    f32 step;
} FontState;

extern FontState *lbl_801A66CC;
extern const f32 lbl_1_rodata_2870;
extern const f64 lbl_1_rodata_2878;

u8 *fn_1_54384(f32 value) {
    FontState *state = lbl_801A66CC;
    f32 pos = -value + state->start;
    f32 adjusted = pos - state->end;
    s32 index;
    s32 count;
    u8 *entry;

    if (adjusted < lbl_1_rodata_2870) {
        index = 0;
    } else {
        count = state->glyph_count;
        index = (s32)((f32)(s32)count * adjusted /
                      (adjusted + state->step));
        if (index >= count) {
            index = count - 1;
        }
    }

    entry = state->glyphs + index * 8;
    if (state->lower > entry) {
        state->lower = entry;
    }
    if (lbl_801A66CC->upper < entry) {
        lbl_801A66CC->upper = entry;
    }
    return entry;
}
/* fzgx:end fn_1_54384 */

/* fzgx:begin fn_1_54448 noprologue */
#include "types.h"

struct fn_1_54448_lbl_801A66CC {
    u32 unk_0;
};
extern struct fn_1_54448_lbl_801A66CC lbl_801A66CC;
extern void * * fn_1_54448(s32);

void **fn_1_54448(s32 arg0) {
    void **temp_r3;

    temp_r3 = (void **)((*(s32 *)((u8 *)(lbl_801A66CC.unk_0) + 48)) + (arg0 * 8));
    if ((void **) (*(void ***)((u8 *)(lbl_801A66CC.unk_0) + 68)) > temp_r3) {
        (*(void ***)((u8 *)(lbl_801A66CC.unk_0) + 68)) = (void **)(temp_r3);
    }
    if ((void **) (*(void ***)((u8 *)(lbl_801A66CC.unk_0) + 72)) < temp_r3) {
        (*(void ***)((u8 *)(lbl_801A66CC.unk_0) + 72)) = (void **)(temp_r3);
        return temp_r3;
    }
    return temp_r3;
}
/* fzgx:end fn_1_54448 */

/* fzgx:begin fn_1_545B8 */
typedef struct fn_1_545B8_manager {
    u8 unk_00[0x30];
    void *unk_30;
    u32 unk_34;
    u8 unk_38[0x0C];
    u32 *unk_44;
    u32 *unk_48;
} fn_1_545B8_manager;

extern void fn_1_547F8(void *node);
extern void fn_1_54668(void *arg0, u32 arg1, u32 arg2);

// Reset the font manager's node list and process any completed nodes.
void fn_1_545B8(void) {
    if (((fn_1_545B8_manager *)lbl_801A66CC)->unk_48 >=
        ((fn_1_545B8_manager *)lbl_801A66CC)->unk_44) {
        if (((fn_1_545B8_manager *)lbl_801A66CC)->unk_44 >
            (u32 *)((fn_1_545B8_manager *)lbl_801A66CC)->unk_30) {
            *(((fn_1_545B8_manager *)lbl_801A66CC)->unk_44 - 2) = 0;
        }
        fn_1_547F8(((fn_1_545B8_manager *)lbl_801A66CC)->unk_48);
    }

    fn_1_54668(((fn_1_545B8_manager *)lbl_801A66CC)->unk_30,
                ((fn_1_545B8_manager *)lbl_801A66CC)->unk_34, 1);
    ((fn_1_545B8_manager *)lbl_801A66CC)->unk_44 =
        (u32 *)((u8 *)((fn_1_545B8_manager *)lbl_801A66CC)->unk_30 +
                (((fn_1_545B8_manager *)lbl_801A66CC)->unk_34 - 1) * 8);
    ((fn_1_545B8_manager *)lbl_801A66CC)->unk_48 =
        (u32 *)((fn_1_545B8_manager *)lbl_801A66CC)->unk_30;
    fn_1_9FA18();
    fn_1_58248();
}
/* fzgx:end fn_1_545B8 */

/* fzgx:begin fn_1_54668 */
typedef struct fn_1_54668_node {
    struct fn_1_54668_node *next;
    void *data;
} fn_1_54668_node;

// Initialize a forward- or reverse-linked list and notify the allocator.
void fn_1_54668(fn_1_54668_node *node, s32 count, u32 reverse) {
    s32 i;

    if (reverse == 0) {
        i = count - 1;
        for (; i > 0; i--) {
            node->next = node + 1;
            node->data = 0;
            node++;
        }
        node->next = 0;
        node->data = 0;
    } else {
        i = count - 1;
        node += i;
        for (; i > 0; i--) {
            node->next = node - 1;
            node->data = 0;
            node--;
        }
        node->next = 0;
        node->data = 0;
    }
    fn_1_54848();
}
/* fzgx:end fn_1_54668 */

/* fzgx:begin fn_1_547F8 */
typedef struct fn_1_547F8_node {
    struct fn_1_547F8_node *next;
    void (*callback)(struct fn_1_547F8_node *);
} fn_1_547F8_node;

// Invoke each node callback while walking the linked list.
void fn_1_547F8(fn_1_547F8_node *node) {
    while (node != 0) {
        if (node->callback != 0) {
            node->callback(node);
        }
        node = node->next;
    }
}
/* fzgx:end fn_1_547F8 */

/* fzgx:begin fn_1_54848 */
extern u8 *lbl_801A66CC;

typedef struct fn_1_54848_FontState {
    u8 pad_1a0[0x1a0];
    u32 unk_1a0;
    u32 unk_1a4;
    u32 unk_1a8;
    u32 unk_1ac;
} fn_1_54848_FontState;

// Volatile forces each global-state access to retain the retail load ordering.
typedef volatile fn_1_54848_FontState fn_1_54848_VolatileFontState;

// Synchronize the current and previous font-state values for the next update.
void fn_1_54848(void) {
    ((fn_1_54848_VolatileFontState *)lbl_801A66CC)->unk_1a0 =
        ((fn_1_54848_VolatileFontState *)lbl_801A66CC)->unk_1a4;
    ((fn_1_54848_VolatileFontState *)lbl_801A66CC)->unk_1ac =
        ((fn_1_54848_VolatileFontState *)lbl_801A66CC)->unk_1a8;
}
/* fzgx:end fn_1_54848 */

/* fzgx:begin fn_1_54868 */
typedef struct fn_1_54868_FontState {
    u8 pad_1a0[0x1a0];
    u32 unk_1a0;
    u32 unk_1a4;
    u32 unk_1a8;
    u32 unk_1ac;
} fn_1_54868_FontState;

extern u8 *lbl_801A66CC;

// Copies the current font state's two counter values into its active fields.
void fn_1_54868(u32 arg0, u32 arg1) {
    // Volatile access preserves the first retail global-pointer load.
    ((volatile fn_1_54868_FontState *)lbl_801A66CC)->unk_1a4 = arg0;
    // Volatile access preserves the second retail global-pointer load.
    ((volatile fn_1_54868_FontState *)lbl_801A66CC)->unk_1a8 = arg1;
    // Volatile access preserves the third retail global-pointer load.
    ((volatile fn_1_54868_FontState *)lbl_801A66CC)->unk_1a0 = ((volatile fn_1_54868_FontState *)lbl_801A66CC)->unk_1a4;
    // Volatile access preserves the fourth retail global-pointer load.
    ((volatile fn_1_54868_FontState *)lbl_801A66CC)->unk_1ac = ((volatile fn_1_54868_FontState *)lbl_801A66CC)->unk_1a8;
}
/* fzgx:end fn_1_54868 */

/* fzgx:begin fn_1_5489C */
void fn_1_5489C(void **arg0, void **arg1) {
    void *value = *arg0;
    *arg1 = value;
    *arg0 = (void *)arg1;
}
/* fzgx:end fn_1_5489C */

/* fzgx:begin fn_1_548AC */
typedef struct FontCounterState {
    u8 pad_1a0[0x1a0];
    u32 unk_1a0;
    u8 pad_1a4[8];
    u32 unk_1ac;
} FontCounterState;

/* The shared declaration is opaque; this union gives it the recovered layout. */
typedef union FontCounterStateView {
    u8 *raw;
    FontCounterState *typed;
} FontCounterStateView;

// Advances the font counter when enough capacity remains and returns its prior value.
u32 fn_1_548AC(u32 amount) {
    FontCounterStateView view;
    FontCounterState *state;
    u32 previous;

    view.raw = lbl_801A66CC;
    state = view.typed;
    if (state->unk_1ac < amount) {
        return 0;
    }

    previous = state->unk_1a0;
    state->unk_1a0 = previous + amount;
    view.raw = lbl_801A66CC;
    state = view.typed;
    state->unk_1ac -= amount;
    return previous;
}
/* fzgx:end fn_1_548AC */

/* fzgx:begin fn_1_548EC noprologue */
#include "types.h"
#include "rel/main_rel/globals.h"

typedef struct FontState {
    u8 pad30[0x30];
    u8 *field_30;
} FontState;

extern FontState *lbl_801A66CC;

s32 fn_1_548EC(void *arg0) {
    u8 *base;
    FontState *fs;
    s32 offset;
    s32 i;

    i = 0;
    offset = 0;
    fs = lbl_801A66CC;
    while (i < 0x1000) {
        base = fs->field_30;
        if (arg0 == base + offset) {
            return i;
        }
        offset += 8;
        i++;
    }
    return -1;
}
/* fzgx:end fn_1_548EC */

/* fzgx:begin fn_1_54DCC */
void fn_1_54DCC(u8 *data) {
    fn_800794F0(data, (u8 *)lbl_801A66CC + 0x50, 0x84);
}
/* fzgx:end fn_1_54DCC */

/* fzgx:begin fn_1_54E00 */
void fn_1_54E00(void *value) {
    fn_800794F0((u8 *)lbl_801A66CC + 0x50, value, 0x84);
}
/* fzgx:end fn_1_54E00 */

/* fzgx:begin fn_1_54F5C noprologue */
#include "types.h"
#include "rel/main_rel/globals.h"

typedef struct {
    u8 pad0[0x8c];
    f32 plane0[3];
    f32 plane1[3];
    f32 plane2[3];
    f32 plane3[3];
    u8 pad_bc[0x18];
    f32 value_d4;
    f32 value_d8;
    f32 value_dc;
} Fn154F5CData;

extern void *lbl_801A66CC;
extern void lbl_8006E1B0(void *arg0, void *arg1);

s32 fn_1_54F5C(void *arg0, f32 arg1, f32 arg2) {
    Fn154F5CData *data;
    f32 *p;
    f32 d4;
    f32 d8;
    f32 dc;
    f32 m0;
    f32 m1;
    f32 m2;
    s32 i;

    data = (Fn154F5CData *)lbl_801A66CC;
    lbl_8006E1B0(arg0, &data->value_d4);
    data = (Fn154F5CData *)lbl_801A66CC;
    arg1 = arg1 * arg2;
    dc = data->value_dc;
    if (dc > arg1) {
        return 0;
    }
    d4 = data->value_d4;
    d8 = data->value_d8;
    arg1 = -arg1;
    p = data->plane0;
    for (i = 0; i < 4; i++) {
        m0 = d4 * p[0];
        m1 = d8 * p[1];
        m2 = dc * p[2];
        if (m0 + m1 + m2 < arg1) {
            return 0;
        }
        p += 3;
    }
    return 1;
}
/* fzgx:end fn_1_54F5C */

/* fzgx:begin fn_1_550A8 */
void fn_1_550A8(void) {
    fn_800794F0(lbl_1_bss_6C710, (u8 *)lbl_801A66CC + 0x50, 0x84);
}
/* fzgx:end fn_1_550A8 */

/* fzgx:begin fn_1_550E0 */
void fn_1_550E0(void) {
    fn_800794F0((u8 *)lbl_801A66CC + 0x50, lbl_1_bss_6C710, 0x84);
}
/* fzgx:end fn_1_550E0 */

/* fzgx:begin fn_1_5557C */
typedef struct {
    u8 unk_00[8];
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
    f32 unk_14;
} Fn1_5557CObject;

void fn_1_5557C(Fn1_5557CObject *value) {
    if (fn_1_54F5C((u8 *)&value->unk_08, value->unk_14, lbl_1_bss_6C7A0)) {
        fn_1_55210(value);
        return;
    }

    fn_1_56530();
}
/* fzgx:end fn_1_5557C */

/* fzgx:begin fn_1_555D0 */
typedef struct {
    u8 unk_00[8];
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
    f32 unk_14;
} Fn1_555D0Object;

void fn_1_555D0(Fn1_555D0Object *value) {
    if (fn_1_54F5C((u8 *)&value->unk_08, value->unk_14, lbl_1_bss_6C7A0)) {
        fn_80072558();
        fn_1_55210(value);
        return;
    }

    fn_1_56530();
}
/* fzgx:end fn_1_555D0 */

/* fzgx:begin fn_1_55628 */
typedef struct {
    u8 pad_00[0x1C];
    u16 unk_1C;
} Fn1_55628Object;

void fn_1_55628(Fn1_55628Object *value) {
    if (value->unk_1C != 0 || lbl_1_rodata_28A8 != lbl_1_bss_6C7A4.unk_8) {
        fn_1_557C4(value);
    } else {
        fn_1_556B8(value);
    }
}
/* fzgx:end fn_1_55628 */

/* fzgx:begin fn_1_55678 */
void fn_1_55678(void *value) {
    fn_1_563E4(&lbl_1_bss_6C7A4);
    fn_80077E7C(value);
    fn_1_56530();
}
/* fzgx:end fn_1_55678 */

/* fzgx:begin fn_1_556B8 */
/* Completes the font operation for the supplied value. */
void fn_1_556B8(void *value) {
    fn_1_563E4(&lbl_1_bss_6C7A4);
    fn_80077F8C(value);
    fn_1_56530();
}
/* fzgx:end fn_1_556B8 */

/* fzgx:begin fn_1_556F8 */
typedef struct {
    u8 unk_00[8];
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
    f32 unk_14;
} Fn1_556F8Object;

/* Finishes the current font operation after testing its scale threshold. */
void fn_1_556F8(Fn1_556F8Object *value) {
    if (fn_1_54F5C((u8 *)&value->unk_08, value->unk_14, lbl_1_bss_6C7A0)) {
        fn_1_563E4(&lbl_1_bss_6C7A4);
        fn_80077F8C(value);
        fn_1_56530();
        return;
    }

    fn_1_56530();
}
/* fzgx:end fn_1_556F8 */

/* fzgx:begin fn_1_5575C */
typedef struct {
    u8 unk_00[8];
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
    f32 unk_14;
} Fn1_5575CObject;

void fn_1_5575C(Fn1_5575CObject *value) {
    if (fn_1_54F5C((u8 *)&value->unk_08, value->unk_14, lbl_1_bss_6C7A0)) {
        fn_80072558();
        fn_1_563E4(&lbl_1_bss_6C7A4);
        fn_80077F8C(value);
        fn_1_56530();
        return;
    }

    fn_1_56530();
}
/* fzgx:end fn_1_5575C */

/* fzgx:begin fn_1_55FC4 */
void fn_1_55FC4(f32 value) {
    lbl_1_bss_6C7A0 = value;
}
/* fzgx:end fn_1_55FC4 */

/* fzgx:begin fn_1_55FD0 */
void fn_1_55FD0(void) {
    fn_80074CF4();
}
/* fzgx:end fn_1_55FD0 */

/* fzgx:begin fn_1_55FF0 */
void fn_1_55FF0(f32 value) {
    lbl_1_bss_6C7A4.unk_8 = value;
}
/* fzgx:end fn_1_55FF0 */

/* fzgx:begin fn_1_56000 */
void fn_1_56000(u8 value0, u8 value1, u8 value2) {
    lbl_1_bss_6C7A4.unk_C = value0;
    lbl_1_bss_6C7A4.unk_D = value1;
    lbl_1_bss_6C7A4.unk_E = value2;
}
/* fzgx:end fn_1_56000 */

/* fzgx:begin fn_1_560F0 */
// Marks the selected font resource as active before handing it to the loader.
void fn_1_560F0(s32 index, void *arg) {
    if (arg != NULL) {
        lbl_1_bss_6C7CC.unk_0 |= (1u << 31) >> index;
        lbl_8006DD14(arg, lbl_801A66CC + index * 0x30 + 0xe0);
    }
    fn_800749B0(index, arg);
}
/* fzgx:end fn_1_560F0 */

/* fzgx:begin fn_1_5616C noprologue */
#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/font.h"

/* 0x30-byte slot in the table lbl_801A66CC points at */
typedef struct {
    f32 unk_0[12];
} FontSlot;

extern FontSlot *lbl_801A66CC;
extern void lbl_8006D784(void *arg);
extern void fn_800749B0(s32 arg0, void *arg1);

void fn_1_5616C(s32 value, f32 value1, f32 value2) {
    lbl_1_bss_6C7CC.unk_0 |= ((u32)1 << 31) >> value;

    lbl_8006D784(&lbl_801A66CC[value].unk_0[0x38]);

    lbl_801A66CC[value].unk_0[0x3b] = value1;
    lbl_801A66CC[value].unk_0[0x3f] = value2;

    fn_800749B0(value, &lbl_801A66CC[value].unk_0[0x38]);
}
/* fzgx:end fn_1_5616C */

/* fzgx:begin fn_1_56298 */
void fn_1_56298(f32 value0, f32 value1, f32 value2, f32 value3) {
    f32 scale = lbl_1_rodata_28AC;

    lbl_1_bss_6C7A4.unk_4 = (u8)(scale * value0);
    lbl_1_bss_6C7A4.unk_5 = (u8)(scale * value1);
    lbl_1_bss_6C7A4.unk_6 = (u8)(scale * value2);
    lbl_1_bss_6C7A4.unk_7 = (u8)(scale * value3);
    fn_80074C74(&lbl_1_bss_6C7A4.unk_4);
}
/* fzgx:end fn_1_56298 */

/* fzgx:begin fn_1_5631C */
void fn_1_5631C(const u32 *value) {
    Obj_1_bss_6C7A4 *state = &lbl_1_bss_6C7A4;

    // Store the incoming value in the shared font state before notifying the subsystem.
    *(volatile u32 *)&state->unk_4 = *value;
    fn_80074C74((u8 *)value);
}
/* fzgx:end fn_1_5631C */

/* fzgx:begin fn_1_5634C */
void fn_1_5634C(u8 value) {
    lbl_1_bss_6C7A4.unk_12 = value;
}
/* fzgx:end fn_1_5634C */

/* fzgx:begin fn_1_5635C */
void fn_1_5635C(u8 value, f32 value2, f32 value3) {
    lbl_1_bss_6C7A4.unk_13 = value;
    *(f32 *)&lbl_1_bss_6C7A4.unk_18 = value2;
    *(f32 *)&lbl_1_bss_6C7A4.unk_1C = value3;
}
/* fzgx:end fn_1_5635C */

/* fzgx:begin fn_1_56374 */
void fn_1_56374(u8 value1, u8 value2, u8 value3) {
    lbl_1_bss_6C7A4.unk_14 = value1;
    lbl_1_bss_6C7A4.unk_15 = value2;
    lbl_1_bss_6C7A4.unk_16 = value3;
}
/* fzgx:end fn_1_56374 */

/* fzgx:begin fn_1_5638C */
// Stores the current value for the font subsystem and refreshes its state.
void fn_1_5638C(u32 value) {
    lbl_1_bss_6C7A4.unk_20 = value;
    fn_80074A7C();
}
/* fzgx:end fn_1_5638C */

/* fzgx:begin fn_1_563B8 */
void fn_1_563B8(u32 value) {
    lbl_1_bss_6C7A4.unk_24 = value;
    fn_80077BAC();
}
/* fzgx:end fn_1_563B8 */

/* fzgx:begin fn_1_563E4 noprologue */
#include "types.h"

typedef struct fn_1_563E4_FontState {
    u8 pad_00[8];
    f32 scale;
    u8 pad_0C[6];
    u8 enabled;
    u8 color;
    u32 value;
    f32 x;
    f32 y;
    u8 pad_20[4];
    u32 state;
} fn_1_563E4_FontState;

extern void fn_80077B04(f32 scale);
extern void fn_80074918(u8 a, u8 b, u8 c);
extern void fn_80071ED4(u8 value, f32 x, f32 y);
extern void fn_80072014(u32 *value);
extern void fn_800720B0(u32 value);

void fn_1_563E4(fn_1_563E4_FontState *font) {
    u32 value;
    u32 lab_t0;
    u32 lab_t2;

    fn_80077B04(font->scale);
    lab_t0 = font->pad_0C[0];
    lab_t2 = font->pad_0C[2];
    fn_80074918(lab_t0, font->pad_0C[1], lab_t2);
    if (font->state == 0) {
        if (font->enabled != 0) {
            fn_80071ED4(font->color, font->x, font->y);
            value = font->value;
            fn_80072014(&value);
            fn_800720B0(1);
        } else {
            fn_800720B0(0);
        }
    }
}
/* fzgx:end fn_1_563E4 */

/* fzgx:begin fn_1_56470 noprologue */
#include "types.h"

typedef struct fn_1_56470_FontState {
    u8 unk_00[4];
    void *unk_04;
    f32 unk_08;
    s8 unk_0C;
    u8 unk_0D;
    s8 unk_0E;
    u8 unk_0F;
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    u8 unk_13;
    u32 unk_14;
    f32 unk_18;
    f32 unk_1C;
    u32 unk_20;
    u32 unk_24;
} fn_1_56470_FontState;

extern void fn_80077B04(fn_1_56470_FontState *state, f32 value);
extern void fn_80074B40(fn_1_56470_FontState *state);
extern void fn_80074C74(void *value);
extern void fn_80074918(u8 a, u8 b, u8 c);
extern void fn_80077BBC(u8 value);
extern void fn_80037D40(u8 a, u8 b);
extern void fn_80074A7C(u32 value);
extern void fn_80077BAC(u32 value);
extern void fn_80071ED4(u8 value, f32 a, f32 b);
extern void fn_80072014(void *value);
extern void fn_800720B0(u32 value);

void fn_1_56470(fn_1_56470_FontState *state) {
    u32 value;

    fn_80077B04(state, state->unk_08);
    fn_80074B40(state);
    fn_80074C74(&state->unk_04);
    fn_80074918(state->unk_0C, state->unk_0D, state->unk_0E);
    fn_80077BBC(state->unk_0F);
    fn_80037D40(state->unk_10, state->unk_11);
    fn_80074A7C(state->unk_20);
    fn_80077BAC(state->unk_24);
    if (state->unk_24 == 0) {
        if (state->unk_12 != 0) {
            fn_80071ED4(state->unk_13, state->unk_18, state->unk_1C);
            value = state->unk_14;
            fn_80072014(&value);
            fn_800720B0(1);
        } else {
            fn_800720B0(0);
        }
    }
}
/* fzgx:end fn_1_56470 */

/* fzgx:begin fn_1_56530 */
void fn_1_56530(void) {
    lbl_1_bss_6C7A0 = lbl_1_rodata_28A8;
    lbl_1_bss_6C7A4.unk_8 = lbl_1_rodata_28A8;
}
/* fzgx:end fn_1_56530 */

/* fzgx:begin fn_1_56554 noprologue */
#include "types.h"
#include "rel/main_rel/font.h"

extern void fn_80074B40(void *value);
extern void fn_80074C74(void *value);
extern void fn_80074918(u8 value0, u8 value1, u8 value2);
extern void fn_80077BBC(u8 value);
extern void fn_80037D40(u8 value0, u8 value1);
extern void fn_80074A7C(u32 value);
extern void fn_80077BAC(u32 value);

void fn_1_56554(void) {
    u32 lab_t0;
    u32 lab_t2;
    Obj_1_bss_6C7A4 *font = &lbl_1_bss_6C7A4;

    fn_80074B40(font);
    fn_80074C74(&font->unk_4);
    lab_t0 = font->unk_C;
    lab_t2 = font->unk_E;
    fn_80074918(lab_t0, font->unk_D, lab_t2);
    fn_80077BBC(font->unk_F);
    fn_80037D40(font->unk_10, font->unk_11);
    fn_80074A7C(font->unk_20);
    fn_80077BAC(font->unk_24);
}
/* fzgx:end fn_1_56554 */

/* fzgx:begin fn_1_565E8 */
// Return the font data buffer used by the font subsystem.
u8 *fn_1_565E8(void) {
    return lbl_1_bss_6C7DC;
}
/* fzgx:end fn_1_565E8 */

/* fzgx:begin fn_1_565F4 */
// fn_1_565F4: empty in retail (single blr).
void fn_1_565F4(void) {
}
/* fzgx:end fn_1_565F4 */

/* fzgx:begin fn_1_565F8 */
// Registers the font initialization callbacks with the shared dispatcher.
void fn_1_565F8(void) {
    void (*callbacks[6])(void);

    callbacks[0] = (void (*)(void))fn_1_565E8;
    callbacks[1] = fn_1_45730;
    callbacks[2] = fn_1_45B2C;
    callbacks[3] = fn_1_458A0;
    callbacks[4] = fn_1_45850;
    callbacks[5] = fn_1_565F4;
    fn_80070D60(callbacks);
}
/* fzgx:end fn_1_565F8 */
