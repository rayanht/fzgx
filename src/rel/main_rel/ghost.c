#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/ghost.h"

extern void fn_1_F23E8(void);
extern void fn_1_EE530(void);
extern u8 fn_1_B7C00(void);
extern void fn_1_B9BE0(void);
extern void fn_1_B9DE8(Obj_1_bss_7ECB4 *obj);
extern u8 lbl_1_bss_7EA00[56];
extern int fn_1_B7CD4(void);
extern int fn_1_B7C5C(void);
extern u32 lbl_1_bss_7B19C[2];
extern u32 lbl_801A6410[];
extern void fn_1_46B4(u32, u32, void *, u32);
extern void fn_1_C1394(void);
extern void OSReport(const char *, ...);
extern void fn_1_49410(void);
extern void fn_1_495FC(void);
extern const f32 lbl_1_rodata_6D20;
extern const f32 lbl_1_rodata_6D24;
extern void fn_1_496FC(f32, f32);
extern void fn_1_495C8(s32);
extern s32 lbl_1_bss_7B198;
extern void fn_1_4AE0C(void *, ...);
extern u8 lbl_1_bss_7C8CE[70];
extern void fn_1_F1D70(void);
extern u32 lbl_1_bss_7EA38[159];
extern const f64 lbl_1_rodata_6B68;
extern const f32 lbl_1_rodata_6D10;
extern const f32 lbl_1_rodata_6D44;
extern void fn_80008BEC(void *dst, int value, int size);
extern void fn_1_F1950(void);
extern u32 fn_8002071C(void *arg);
extern void fn_800206FC(u32 arg);
extern u32 ARGetDMAStatus(void);
extern void DCFlushRange(void *addr, u32 size);
extern u32 lbl_1_bss_7C848[2];
extern u8 lbl_1_bss_7C8CD;
extern u32 lbl_1_bss_7C948;
extern void fn_1_12EF80(s16 arg, s16 *out_a, s16 *out_b);
extern u32 lbl_1_bss_7B190[2];
extern u32 lbl_1_bss_7ED58[158];

extern void fn_1_12EF80(s16 arg, s16 *out_a, s16 *out_b);

extern void OSReport(const char *, ...);
extern void fn_1_12EF80(s16 arg, s16 *out_a, s16 *out_b);

extern void fn_1_12EF80(s16 arg, s16 *out_a, s16 *out_b);

extern void fn_1_12EF80(s16 arg, s16 *out_a, s16 *out_b);
extern f64 lbl_1_rodata_6C88;
extern void fn_80008BA8(u32 *out, const void *value, s32 size);

/* fzgx:begin fn_1_EC900 */
// Return the current ghost state value.
u32 fn_1_EC900(void) {
    return lbl_1_bss_7B1A4;
}
/* fzgx:end fn_1_EC900 */

/* fzgx:begin fn_1_ECDFC */
// fn_1_ECDFC: empty in retail (single blr).
void fn_1_ECDFC(void) {
}
/* fzgx:end fn_1_ECDFC */

/* fzgx:begin fn_1_ECE00 */
// fn_1_ECE00: empty in retail (single blr).
void fn_1_ECE00(void) {
}
/* fzgx:end fn_1_ECE00 */

/* fzgx:begin fn_1_ECF68 */
void fn_1_ECF68(void) {
    fn_1_F23E8();
}
/* fzgx:end fn_1_ECF68 */

/* fzgx:begin fn_1_EF0A0 */
// fn_1_EF0A0: empty in retail (single blr).
void fn_1_EF0A0(void) {
}
/* fzgx:end fn_1_EF0A0 */

/* fzgx:begin fn_1_EF0A4 */
// fn_1_EF0A4: empty in retail (single blr).
void fn_1_EF0A4(void) {
}
/* fzgx:end fn_1_EF0A4 */

/* fzgx:begin fn_1_EF484 */
// fn_1_EF484: empty in retail (single blr).
void fn_1_EF484(void) {
}
/* fzgx:end fn_1_EF484 */

/* fzgx:begin fn_1_EF488 */
void fn_1_EF488(void) {
    fn_1_EE530();
    if (!fn_1_B7C00()) {
        fn_1_B9BE0();
        fn_1_B9DE8(&lbl_1_bss_7ECB4);
        lbl_1_bss_7ECB4.unk_0 = 4;
        lbl_1_bss_7ECB4.unk_4 = 9;
        lbl_1_bss_7EA00[0] = 0;
        lbl_1_data_3E52C = 13;
    }
}
/* fzgx:end fn_1_EF488 */

/* fzgx:begin fn_1_EF4F4 */
// fn_1_EF4F4: empty in retail (single blr).
void fn_1_EF4F4(void) {
}
/* fzgx:end fn_1_EF4F4 */

/* fzgx:begin fn_1_EF5DC */
// fn_1_EF5DC: empty in retail (single blr).
void fn_1_EF5DC(void) {
}
/* fzgx:end fn_1_EF5DC */

/* fzgx:begin fn_1_EF764 */
// fn_1_EF764: empty in retail (single blr).
void fn_1_EF764(void) {
}
/* fzgx:end fn_1_EF764 */

/* fzgx:begin fn_1_EF85C */
// fn_1_EF85C: empty in retail (single blr).
void fn_1_EF85C(void) {
}
/* fzgx:end fn_1_EF85C */

/* fzgx:begin fn_1_EF860 */
void fn_1_EF860(void) {
    u8 *base = lbl_1_data_3E358;
    u32 value;

    fn_1_EE530();
    if (!fn_1_B7C00()) {
        if (!fn_1_B7CD4()) {
            value = fn_1_B7C5C();
            OSReport((const char *)(base + 0x3ac), value);
        }
        if (lbl_1_bss_7B19C[0] != 0) {
            fn_1_46B4(lbl_801A6410[0], lbl_1_bss_7B19C[0],
                      (void *)(base + 0x2d4), 0xf44);
            lbl_1_bss_7B19C[0] = 0;
        }
        if (lbl_1_bss_7ECB4.unk_14 == (s8)8) {
            fn_1_C1394();
            *((u32 *)(base + 0x1d4)) = 0xd;
        } else {
            *((u32 *)(base + 0x1d4)) = 8;
        }
    }
}
/* fzgx:end fn_1_EF860 */

/* fzgx:begin fn_1_EF920 */
// fn_1_EF920: empty in retail (single blr).
void fn_1_EF920(void) {
}
/* fzgx:end fn_1_EF920 */

/* fzgx:begin fn_1_EF978 */
// fn_1_EF978: empty in retail (single blr).
void fn_1_EF978(void) {
}
/* fzgx:end fn_1_EF978 */

/* fzgx:begin fn_1_EF97C */
void fn_1_EF97C(void) {
    u8 *base = lbl_1_data_3E358;

    fn_1_EE530();

    if ((lbl_1_bss_9F8.unk_8 >> 8) & 1) {
        *(s32 *)(base + 0x1D4) = 10;
    }

    fn_1_49410();
    fn_1_495FC();
    fn_1_496FC(lbl_1_rodata_6D20, lbl_1_rodata_6D24);
    fn_1_495C8(9);

    if (lbl_1_bss_7B198) {
        fn_1_4AE0C(base + 0x40C);
    } else {
        fn_1_4AE0C(base + 0x458);
    }
}
/* fzgx:end fn_1_EF97C */

/* fzgx:begin fn_1_EFA18 */
// fn_1_EFA18: empty in retail (single blr).
void fn_1_EFA18(void) {
}
/* fzgx:end fn_1_EFA18 */

/* fzgx:begin fn_1_EFA4C */
// fn_1_EFA4C: empty in retail (single blr).
void fn_1_EFA4C(void) {
}
/* fzgx:end fn_1_EFA4C */

/* fzgx:begin ghost_reset */
void ghost_reset(void) {
    lbl_1_bss_7C8CE[0] = 0;
    lbl_1_data_3E52C = -1;
    fn_1_F1D70();
}
/* fzgx:end ghost_reset */

/* fzgx:begin fn_1_EFA88 */
// fn_1_EFA88: empty in retail (single blr).
void fn_1_EFA88(void) {
}
/* fzgx:end fn_1_EFA88 */

/* fzgx:begin fn_1_F0164 */
// fn_1_F0164: empty in retail (single blr).
void fn_1_F0164(void) {
}
/* fzgx:end fn_1_F0164 */

/* fzgx:begin fn_1_F1588 */
u32 fn_1_F1588(void) {
    u32 value = lbl_1_bss_7EA38[0];

    if (value == 0) {
        return 0;
    }

    if ((f32)value < lbl_1_rodata_6D10) {
        return value % 6 == 0;
    }

    if ((f32)value < lbl_1_rodata_6D44) {
        return value % 10 == 0;
    }

    return (value & 0xf) == 0;
}
/* fzgx:end fn_1_F1588 */

/* fzgx:begin fn_1_F17B4 */
#include "types.h"

s32 fn_1_F17B4(const void *value) {
    u32 bits;
    s32 exponent;
    s32 sign;
    s32 fraction;
    f64 converted;
    s32 magnitude;
    s32 result;

    fn_80008BA8(&bits, value, 4);

    exponent = (s32)((bits >> 23) & 0xff) - 0x7f;
    sign = bits >> 31;
    fraction = bits & 0x7fffff;

    if (exponent >= 0) {
        exponent = (exponent << 27) >> 27;
        exponent += 0xf;
    } else {
        converted = (f32)exponent;
        converted = __fabs(converted);
        magnitude = (s32)converted;
        magnitude = (magnitude << 27) >> 27;
        exponent = ~magnitude + 0x10;
        exponent = (exponent << 27) >> 27;
    }

    result = sign << 20;
    result += exponent << 15;
    result += fraction >> 8;
    return result;
}
/* fzgx:end fn_1_F17B4 */

/* fzgx:begin ghost_pack_bits */
void ghost_pack_bits(u32 *out, const u32 *x, const u32 *y, const u32 *z) {
    out[0] = 0;
    out[1] = 0;
    out[0] += x[0] << 10;
    out[0] += y[0] >> 11;
    out[1] += y[0] << 21;
    out[1] += z[0];
}
/* fzgx:end ghost_pack_bits */

/* fzgx:begin fn_1_F18C0 */
void fn_1_F18C0(const u32 *in, u32 *x, u32 *y, u32 *z) {
    x[0] = (in[0] >> 10) & 0x1fffff;
    y[0] = 0;
    y[0] += (in[0] & 0x3ff) << 11;
    y[0] += in[1] >> 21;
    z[0] = in[1] & 0x1fffff;
}
/* fzgx:end fn_1_F18C0 */

/* fzgx:begin fn_1_F190C */
void fn_1_F190C(void) {
    fn_80008BEC(&lbl_1_bss_7B1AC, 0, 0x13d8);
    fn_80008BEC(&lbl_1_bss_7C584, 0, 0x1fc);
}
/* fzgx:end fn_1_F190C */

/* fzgx:begin fn_1_F1950 */
// Set the transfer completion flag for the asynchronous callback.
void fn_1_F1950(void) {
    lbl_1_bss_7ECFC.unk_0 = 1;
}
/* fzgx:end fn_1_F1950 */

/* fzgx:begin fn_1_F1960 */
extern void fn_800205A0(void *arg0, u32 arg1, u32 arg2, u32 arg3,
                        void *arg4, void *arg5, u32 arg6,
                        void (*callback)(void));

void fn_1_F1960(void *arg0, void *arg1, u32 arg2) {
    u32 result;
    u8 temp[0x20];
    // The completion flag is updated asynchronously by the callback.
    volatile u32 *flag;

    result = fn_8002071C(arg0);
    fn_800206FC(arg2);
    lbl_1_bss_7ECFC.unk_0 = 0;
    while (ARGetDMAStatus() != 0) {
    }
    DCFlushRange(arg1, arg2);
    fn_800205A0(temp, 1, 0, 1, arg1, arg0, arg2, fn_1_F1950);
    flag = &lbl_1_bss_7ECFC.unk_0;
    while ((s32)*flag == 0) {
    }
    fn_800206FC(result);
}
/* fzgx:end fn_1_F1960 */

/* fzgx:begin fn_1_F1B78 */
void fn_1_F1B78(u32 value) {
    lbl_1_bss_7C848[0] = value;
}
/* fzgx:end fn_1_F1B78 */

/* fzgx:begin fn_1_F1B84 */
u8 fn_1_F1B84(void) {
    return lbl_1_bss_7C8CD;
}
/* fzgx:end fn_1_F1B84 */

/* fzgx:begin fn_1_F1D60 */
u32 fn_1_F1D60(void) {
    return lbl_1_bss_7C948;
}
/* fzgx:end fn_1_F1D60 */

/* fzgx:begin fn_1_F1D70 */
void fn_1_F1D70(void) {
    lbl_1_bss_7E9E8.unk_0 = 0;
    lbl_1_bss_7E9E8.unk_4 = 0;
    lbl_1_bss_7E9E8.unk_8 = 0;
    lbl_1_bss_7E9E8.unk_C = 0;
}
/* fzgx:end fn_1_F1D70 */

/* fzgx:begin fn_1_F1D8C */
void fn_1_F1D8C(s32 index) {
    if (index < 0x20) {
        lbl_1_bss_7E9E8.unk_0 |= 1 << index;
        return;
    }
    if (index < 0x40) {
        lbl_1_bss_7E9E8.unk_4 |= 1 << (index - 0x20);
        return;
    }
    if (index < 0x60) {
        lbl_1_bss_7E9E8.unk_8 |= 1 << (index - 0x40);
        return;
    }
    lbl_1_bss_7E9E8.unk_C |= 1 << (index - 0x60);
}
/* fzgx:end fn_1_F1D8C */

/* fzgx:begin fn_1_F1E30 */
void fn_1_F1E30(s32 index) {
    if (index < 0x20) {
        lbl_1_bss_7E9E8.unk_0 &= ~(1 << index);
    } else if (index < 0x40) {
        lbl_1_bss_7E9E8.unk_4 &= ~(1 << (index - 0x20));
    } else if (index < 0x60) {
        lbl_1_bss_7E9E8.unk_8 &= ~(1 << (index - 0x40));
    } else {
        lbl_1_bss_7E9E8.unk_C &= ~(1 << (index - 0x60));
    }
}
/* fzgx:end fn_1_F1E30 */

/* fzgx:begin fn_1_F1ED0 */
void fn_1_F1ED0(s32 index) {
    if (index < 0x20) {
        lbl_1_bss_7E9E8.unk_0 ^= 1 << index;
        return;
    }
    if (index < 0x40) {
        lbl_1_bss_7E9E8.unk_4 ^= 1 << (index - 0x20);
        return;
    }
    if (index < 0x60) {
        lbl_1_bss_7E9E8.unk_8 ^= 1 << (index - 0x40);
        return;
    }
    lbl_1_bss_7E9E8.unk_C ^= 1 << (index - 0x60);
}
/* fzgx:end fn_1_F1ED0 */

/* fzgx:begin ghost_test_flag */
// Tests whether a ghost flag is set in the corresponding 32-bit flag word.
u32 ghost_test_flag(s32 index) {
    if (index < 0x20) {
        return lbl_1_bss_7E9E8.unk_0 & (1 << index);
    }
    if (index < 0x40) {
        return lbl_1_bss_7E9E8.unk_4 & (1 << (index - 0x20));
    }
    if (index < 0x60) {
        return lbl_1_bss_7E9E8.unk_8 & (1 << (index - 0x40));
    }
    return lbl_1_bss_7E9E8.unk_C & (1 << (index - 0x60));
}
/* fzgx:end ghost_test_flag */

/* fzgx:begin fn_1_F2008 */
// Records the flag for the ghost entry identified by the decoded pair.
void fn_1_F2008(s32 arg) {
    s16 a;
    s16 b;
    s32 index;
    u8 *ghost_data;

    fn_1_12EF80((s16)arg, &a, &b);
    index = (a - 1) * 6 + b;
    ghost_data = (u8 *)&lbl_1_bss_7F0C0;
    ghost_data[0x4938 + index] |= 1;
}
/* fzgx:end fn_1_F2008 */

/* fzgx:begin ghost_test_record_flag0 */
// Tests the record flag selected by the supplied ghost identifier.
u32 ghost_test_record_flag0(s32 arg) {
    s16 a;
    s16 b;
    s32 index;
    u8 *record_flags;

    fn_1_12EF80((s16)arg, &a, &b);
    index = (a - 1) * 6 + b;
    record_flags = (u8 *)&lbl_1_bss_7F0C0;
    return record_flags[0x4938 + index] & 1;
}
/* fzgx:end ghost_test_record_flag0 */

/* fzgx:begin ghost_set_record_flag1 */
// Sets the second record flag for the record associated with arg.
void ghost_set_record_flag1(s32 arg) {
    s16 a;
    s16 b;
    s32 index;
    u8 *record_flags;

    fn_1_12EF80((s16)arg, &a, &b);
    index = (a - 1) * 6 + b;
    record_flags = (u8 *)&lbl_1_bss_7F0C0;
    record_flags[0x4938 + index] |= 2;
}
/* fzgx:end ghost_set_record_flag1 */

/* fzgx:begin fn_1_F210C */
extern void fn_1_12EF80(s16 arg, s16 *out_a, s16 *out_b);
extern Obj_1_bss_7F0C0 lbl_1_bss_7F0C0;

u32 fn_1_F210C(s32 arg) {
    s16 out_a;
    s16 out_b;
    s32 index;
    u8 *flags;

    fn_1_12EF80((s16)arg, &out_a, &out_b);
    index = (out_a - 1) * 6 + out_b;
    flags = (u8 *)&lbl_1_bss_7F0C0;
    return flags[0x4938 + index] & 2;
}
/* fzgx:end fn_1_F210C */

/* fzgx:begin ghost_set_record_flag2 */
// Set the second flag on the record selected by the argument.
void ghost_set_record_flag2(s32 arg) {
    s16 record_group;
    s16 record_index;
    s32 flag_index;
    u8 *flags;

    fn_1_12EF80((s16)arg, &record_group, &record_index);
    flag_index = (record_group - 1) * 6 + record_index;
    flags = (u8 *)&lbl_1_bss_7F0C0;
    flags[0x4938 + flag_index] |= 4;
}
/* fzgx:end ghost_set_record_flag2 */

/* fzgx:begin fn_1_F21B8 */
// Return the selected record's second flag bit after decoding its table position.
s32 fn_1_F21B8(s32 arg) {
    s16 a;
    s16 b;
    s32 index;
    u8 *flags;

    fn_1_12EF80((s16)arg, &a, &b);
    index = (a - 1) * 6 + b;
    flags = (u8 *)&lbl_1_bss_7F0C0;
    return flags[0x4938 + index] & 4;
}
/* fzgx:end fn_1_F21B8 */

/* fzgx:begin fn_1_F220C */
// Logs the resolved course coordinates and marks the corresponding course as visited.
void fn_1_F220C(s32 arg) {
    s16 a;
    s16 b;
    s32 index;

    fn_1_12EF80((s16)arg, &a, &b);
    index = (a - 1) * 6 + b;
    OSReport((const char *)lbl_1_data_3E8A0, a, b, index);
    ((u8 *)&lbl_1_bss_7F0C0)[0x4938 + index] |= 8;
}
/* fzgx:end fn_1_F220C */

/* fzgx:begin fn_1_F2280 */
// Returns the flag for the state selected by the converted coordinates.
s32 fn_1_F2280(s32 arg) {
    s16 group;
    s16 entry;
    s32 index;
    u8 *state_flags;

    fn_1_12EF80((s16)arg, &group, &entry);
    index = (group - 1) * 6 + entry;
    state_flags = (u8 *)&lbl_1_bss_7F0C0;
    return state_flags[0x4938 + index] & 8;
}
/* fzgx:end fn_1_F2280 */

/* fzgx:begin fn_1_F22D4 */
u32 fn_1_F22D4(void) {
    return lbl_1_bss_7B190[0];
}
/* fzgx:end fn_1_F22D4 */

/* fzgx:begin fn_1_F23D8 */
void fn_1_F23D8(void) {
    lbl_1_bss_7ED58[0] = 0;
}
/* fzgx:end fn_1_F23D8 */
