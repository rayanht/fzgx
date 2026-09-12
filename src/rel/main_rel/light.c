#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/light.h"

extern u16 lbl_1_bss_6D7C0[20];

extern void *lbl_801A6410;
extern u32 fn_1_4630(u32, int, void *, int);
extern void fn_800793D4(u32, int, int);
extern void fn_1_7C13C(void *);
extern void fn_1_7C1E8(u32);
extern u8 fn_1_816E8(void *, u8);
extern const f32 lbl_1_rodata_33A8;
extern void fn_1_495D8(int, int, f32);
extern void fn_1_495FC(void);
extern void OSPanic(const char *, int, const char *, ...);

/* fzgx:begin fn_1_7BCCC */
typedef struct {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
} Triple_80074D28;

typedef struct {
    u8 pad_0[0x2];
    u16 unk_2;
    u8 pad_4[0x12];
    u16 unk_16;
    u8 pad_18[0x8];
    u32 unk_20;
} Fn17BCCCState;

extern void fn_80074D28(Triple_80074D28 *);

void fn_1_7BCCC(Triple_80074D28 *arg0) {
    Fn17BCCCState *state;

    state = (Fn17BCCCState *)&lbl_1_bss_6D7A8;
    if (state->unk_16 >= state->unk_2) {
        OSPanic((const char *)lbl_1_data_1EE44, 143, (const char *)lbl_1_data_1EE70);
    }
    *(Triple_80074D28 *)((u8 *)state->unk_20 + state->unk_16 * 12) = *arg0;
    fn_80074D28(arg0);
    state->unk_16++;
    return;
}
/* fzgx:end fn_1_7BCCC */

/* fzgx:begin fn_1_7BE94 */
u16 fn_1_7BE94(void) {
    return lbl_1_bss_6D7C0[0] - 1;
}
/* fzgx:end fn_1_7BE94 */

/* fzgx:begin fn_1_7BF9C */
typedef struct {
    void *unk_0;
    u8 unk_4;
    u8 unk_5;
    u8 unk_6;
    s8 unk_7;
    u8 unk_8;
    u8 unk_9[3];
    void *unk_c;
    void *unk_10;
    void *unk_14;
    void *unk_18;
    void *unk_1c;
    u32 unk_20;
    u8 unk_24;
} LightState;

// Initialize the shared light state and its required resources.
void fn_1_7BF9C(void *arg, s8 flag) {
    u8 *resource_table;
    u32 resource_18;
    u32 resource_1c;
    u32 resource_c;

    resource_table = (u8 *)&lbl_1_data_1EEB0;
    lbl_1_bss_6D7E8 = fn_1_4630(
        (u32)lbl_801A6410, 0x2c, resource_table + 0xac, 0x33);
    resource_18 = fn_1_4630(
        (u32)lbl_801A6410, 4, resource_table + 0xac, 0x34);
    resource_1c = fn_1_4630(
        (u32)lbl_801A6410, 0x18, resource_table + 0xac, 0x35);
    resource_c = fn_1_4630(
        (u32)lbl_801A6410, 0xa4, resource_table + 0xac, 0x36);

    fn_800793D4(resource_c, 0xff, 0xa4);
    fn_1_7C13C(arg);
    fn_1_7C1E8(resource_1c);

    ((LightState *)lbl_1_bss_6D7E8)->unk_0 = arg;
    ((LightState *)lbl_1_bss_6D7E8)->unk_4 = 2;
    ((LightState *)lbl_1_bss_6D7E8)->unk_6 = 2;
    ((LightState *)lbl_1_bss_6D7E8)->unk_24 = 0;
    ((LightState *)lbl_1_bss_6D7E8)->unk_8 = fn_1_816E8(
        (u8 *)((LightState *)lbl_1_bss_6D7E8)->unk_0 +
            ((LightState *)lbl_1_bss_6D7E8)->unk_7 * 0x440,
        ((LightState *)lbl_1_bss_6D7E8)->unk_24);

    ((LightState *)lbl_1_bss_6D7E8)->unk_c = (void *)resource_c;
    ((LightState *)lbl_1_bss_6D7E8)->unk_10 = resource_table + 0x48;
    ((LightState *)lbl_1_bss_6D7E8)->unk_14 = resource_table + 0x94;
    ((LightState *)lbl_1_bss_6D7E8)->unk_18 = (void *)resource_18;
    ((LightState *)lbl_1_bss_6D7E8)->unk_1c = (void *)resource_1c;

    if (flag == 0) {
        ((LightState *)lbl_1_bss_6D7E8)->unk_20 |= 0x40000000;
    }

    fn_1_495D8(2, 2, lbl_1_rodata_33A8);
    fn_1_495FC();
}
/* fzgx:end fn_1_7BF9C */
