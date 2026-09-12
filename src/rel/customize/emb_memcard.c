#include "types.h"
#include "rel/customize/globals.h"
#include "rel/customize/emb_memcard.h"


extern u32 lbl_3_bss_7ED58[18];
extern u32 lbl_801A6410;
extern u32 lbl_3_data_1A18;
extern u8 fn_1_B7C00(void);
extern void fn_1_C1394(u32 *arg0);
extern void fn_1_46B4(u32 arg0, u32 arg1, char *arg2, u32 arg3);
extern u32 lbl_3_rodata_288[60];
extern void lbl_8006DCA4(void);
extern void lbl_8006E1D8(struct Vec3 *, f32, f32, f32);
extern void fn_1_7BCCC(struct Vec3 *);
extern void fn_80035680(struct GXLightObj *, f32, f32, f32);
extern void fn_80035690(struct GXLightObj *, f32, f32, f32);
extern void fn_80035420(struct GXLightObj *, f32, int);
extern void fn_800356AC(struct GXLightObj *, u32 *);
extern void GXInitLightDistAttn(struct GXLightObj *, f32, f32, int);
extern void fn_1_7BB80(struct GXLightObj *, int);
extern void fn_1_7BD6C(int);
extern void fn_80074CF4(f32, f32, f32);

/* fzgx:begin fn_3_C328 noprologue */
#include "types.h"

extern u32 lbl_3_bss_7ED58[18];
extern u32 lbl_801A6410;
extern char lbl_3_data_1A30[14];
extern u32 lbl_3_data_1A18;
extern u8 fn_1_B7C00(void);
extern void fn_1_C1394(u32 *arg0);
extern void fn_1_46B4(u32 arg0, u32 arg1, char *arg2, u32 arg3);

void fn_3_C328(void) {
    u32 *state;

    if (!fn_1_B7C00()) {
        state = lbl_3_bss_7ED58;
        fn_1_C1394(state);
        if (state[2] != 0) {
            fn_1_46B4(lbl_801A6410, state[2], lbl_3_data_1A30, 0x154);
            state[2] = 0;
            state[3] = 0;
        }
        lbl_3_data_1A18 = 0;
    }
}
/* fzgx:end fn_3_C328 */

/* fzgx:begin fn_3_F878 */
struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
};

struct GXLightObj {
    u32 dummy[16];
};

struct CustomizeData {
    u8 pad34[0x34];
    f32 value34;
    u8 pad1ac[0x174];
    f32 value1ac;
    u8 pad1bc[0xc];
    u32 value1bc;
    f32 value1c0;
};

void fn_3_F878(void) {
    struct GXLightObj second;
    struct Vec3 first;
    u32 value;
    f32 scale;
    struct CustomizeData *data;

    data = (struct CustomizeData *)lbl_3_rodata_288;
    lbl_8006DCA4();
    scale = data->value1c0;
    lbl_8006E1D8(&first, scale, scale, scale);
    fn_1_7BCCC(&first);
    fn_80035680(&second, first.x, first.y, first.z);
    fn_80035690(&second, first.x, first.y, first.z);
    fn_80035420(&second, data->value34, 0);
    value = data->value1bc;
    fn_800356AC(&second, &value);
    GXInitLightDistAttn(&second, data->value34, data->value34, 0);
    fn_1_7BB80(&second, 1);
    fn_1_7BD6C(1);
    scale = data->value1ac;
    fn_80074CF4(scale, scale, scale);
}
/* fzgx:end fn_3_F878 */

/* fzgx:begin fn_3_F948 */
typedef struct MemCardSlot {
    u32 unk0;
    u32 flags;
    u8 pad[0x2058];
} MemCardSlot;

s16 fn_3_F948(MemCardSlot *slot) {
    s16 i;
    s16 count = 0;
    i = 0;

    while (i < 4) {
        if (slot->flags & (1u << 31)) {
            count++;
        }
        slot++;
        i++;
    }
    return count;
}
/* fzgx:end fn_3_F948 */

/* fzgx:begin fn_3_11FD0 */
u32 fn_3_11FD0(u32 index, u32 value) {
    return ((u32 *)(lbl_3_data_2F78 + (__cntlzw(value) * 24)))[index];
}
/* fzgx:end fn_3_11FD0 */

/* fzgx:begin fn_3_12E4C */





typedef struct { u32 x; u32 y; u32 z; } Vec3;
typedef struct { u32 unused0; u32 unused1; Vec3 first; Vec3 second; } Data;
typedef struct { u8 pad_000[0x508]; Vec3 first; Vec3 second; } SpecialData;
typedef struct {
    u8 pad_000[0x328];
    s8 state;
    u8 pad_329[0x67];
    u32 flags;
    u8 pad_394[0xc];
    s16 *indices;
} Customize;

#pragma opt_strength_reduction off
#pragma opt_common_subs off
void fn_3_12E4C(Customize *self, u8 index, Vec3 *first, Vec3 *second) {
    Data *data;
    SpecialData *special;
    u8 state;

    if (self->flags & 0x04000000) {
        data = (Data *)(*(u8 (*)[2400])&lbl_3_data_246C);
        data = (Data *)((u8 *)data +
                        ((u8)((self->indices)[(u32)index * 0x1b0]) << 5));
        *first = data->first;
        *second = data->second;
        return;
    }

    state = self->state;
    if (state == 4) {
        if (index != 0) {
            data = (Data *)((u8 *)(*(u32 (*)[352])&lbl_3_data_1EEC) + 0x560);
            *first = data->first;
            *second = data->second;
            return;
        }
        data = (Data *)((u8 *)(*(u32 (*)[352])&lbl_3_data_1EEC) + ((u8)state << 5));
        *first = data->first;
        *second = data->second;
        return;
    }

    if ((u8)state == 0x28) {
        special = (SpecialData *)((u8 *)(*(u32 (*)[352])&lbl_3_data_1EEC) + ((u8)index << 5));
        *first = special->first;
        *second = special->second;
        return;
    }

    data = (Data *)((u8 *)(*(u32 (*)[352])&lbl_3_data_1EEC) + ((u8)state << 5));
    *first = data->first;
    *second = data->second;
}
#pragma opt_common_subs reset

#pragma opt_strength_reduction reset
/* fzgx:end fn_3_12E4C */
