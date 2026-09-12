#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/relocation.h"

extern u8 *lbl_801A6CF4;
extern u32 lbl_1_bss_6F5F4;
extern u8 lbl_801A66B0[];
extern s32 OSGetResetCode(void);
extern u32 OSGetProgressiveMode(void);
extern void OSSetProgressiveMode(s32);
extern void fn_1_A6870(u32 *);
extern void fn_1_A5F44(void);
extern s32 fn_1_A6480(void);

/* fzgx:begin fn_1_A5C98 */
#include "types.h"

extern u32 lbl_1_bss_6F5C0;
extern u8 lbl_1_bss_6F5C4[44];




extern u8 *lbl_801A6410;

extern void OSUnlink(void *);
extern void OSPanic(void *, ...);
extern void fn_1_46B4(void *, void *, void *, int);

typedef struct Fn1A5C98Object {
    void *unk0;
    void *unk4;
    u8 pad8[0x30];
    void (*unk38)(void *);
} Fn1A5C98Object;

void fn_1_A5C98(Fn1A5C98Object *self) {
    u32 v1;
    if (self->unk0 != 0) {
        ((Fn1A5C98Object *)self->unk0)->unk38(self->unk0);
        OSUnlink(self->unk0);

        v1 = (u32)lbl_1_bss_6F5C4;
        v1 = (u32)((u8 *)v1 + (lbl_1_bss_6F5C0 << 2));
        if (*(u32 *)((u8 *)v1 - 4) != (u32)self) {
            OSPanic((*(u8 (*)[84])&lbl_1_data_34140), 0x78, (*(char (*)[31])&lbl_1_data_34194));
        }

        lbl_1_bss_6F5C0--;

        if (self->unk4 != 0) {
            fn_1_46B4(lbl_801A6410, self->unk4, (*(u8 (*)[84])&lbl_1_data_34140), 0x7b);
        }
        fn_1_46B4(lbl_801A6410, self->unk0, (*(u8 (*)[84])&lbl_1_data_34140), 0x7c);

        self->unk0 = 0;
        self->unk4 = 0;
    }
}
/* fzgx:end fn_1_A5C98 */

/* fzgx:begin fn_1_A5D88 */
u16 fn_1_A5D88(void) {
    return *(u16 *)(lbl_801A6CF4 + 4);
}
/* fzgx:end fn_1_A5D88 */

/* fzgx:begin fn_1_A5D9C */
u16 fn_1_A5D9C(void) {
    return *(u16 *)(lbl_801A6CF4 + 6);
}
/* fzgx:end fn_1_A5D9C */

/* fzgx:begin fn_1_A5DB0 */
u16 fn_1_A5DB0(void) {
    return *(u16 *)(lbl_801A6CF4 + 8);
}
/* fzgx:end fn_1_A5DB0 */

/* fzgx:begin fn_1_A5DC4 */
// Return whether relocation processing is in one of the active states.
s32 fn_1_A5DC4(void) {
    if ((s32)lbl_1_bss_6F5F0 == 1 || (s32)lbl_1_bss_6F5F0 == 2) {
        return 1;
    }
    return 0;
}
/* fzgx:end fn_1_A5DC4 */

/* fzgx:begin fn_1_A5DEC */
#include "types.h"
#include "dolphin/os/OSTime.h"




extern u32 VIGetDTVStatus(void);
extern void fn_1_3308(void);
extern OSTick OSGetTick(void);
extern u32 OSGetProgressiveMode(void);

extern u32 __OSBusClock : 0x800000F8; /* fzgx-allow: A1 OS globals block */
void fn_1_A5DEC(void) {
    u32 temp_r28;
    u32 temp_r29;

    if (VIGetDTVStatus() != 0) {
        fn_1_3308();
        temp_r29 = OSGetTick();
        do {
            temp_r28 = (__OSBusClock >> 2) / 1000;
        } while ((u32) ((OSGetTick() / temp_r28) - (temp_r29 / temp_r28)) < 0x1F4U);
        fn_1_3308();
        if ((((u16) (*(u16 *)((u8 *)(&(*(u16 *)&lbl_1_bss_9F8)) + 0)) >> 9U) & 1) || (((u16) (*(u16 *)((u8 *)(&(*(u16 *)&lbl_1_bss_9F8)) + 20)) >> 9U) & 1) || (((u16) (*(u16 *)((u8 *)(&(*(u16 *)&lbl_1_bss_9F8)) + 40)) >> 9U) & 1) || (((u16) (*(u16 *)((u8 *)(&(*(u16 *)&lbl_1_bss_9F8)) + 60)) >> 9U) & 1) || (OSGetProgressiveMode() != 0)) {
            (*(s32 *)((u8 *)((*(u32 *)((u8 *)(&(*(u32 *)&lbl_1_data_341B8)) + 0))) + 0)) = 1;
            return;
        }
        (*(s32 *)((u8 *)((*(u32 *)((u8 *)(&(*(u32 *)&lbl_1_data_341B8)) + 0))) + 0)) = 0;
        return;
    }
    (*(s32 *)((u8 *)((*(u32 *)((u8 *)(&(*(u32 *)&lbl_1_data_341B8)) + 0))) + 0)) = 0;
}
/* fzgx:end fn_1_A5DEC */

/* fzgx:begin fn_1_A5EFC */
void fn_1_A5EFC(void) {
    lbl_1_bss_6F5F0 = 0;
    if ((s32)lbl_1_data_341B8->unk_0 != 0) {
        lbl_1_data_341B8->unk_4 = 0;
        lbl_1_data_341B8->unk_5 = 1;
        lbl_1_data_341B8->unk_6 = 0x258;
    }
}
/* fzgx:end fn_1_A5EFC */

/* fzgx:begin fn_1_A66FC */
// Records the reset state and performs the appropriate relocation startup or recovery.
s32 fn_1_A66FC(s32 value) {
    s32 result;

    lbl_1_bss_6F5F4 = value;
    if (((u32)__cntlzw((u32)((-2147483647 - 1) - OSGetResetCode())) >> 5) != 0) {
        if (OSGetProgressiveMode() != 0) {
            result = 1;
        } else {
            OSSetProgressiveMode(0);
            lbl_1_data_341B8->unk_0 = 0;
            result = 1;
        }
        if (lbl_801A66B0[3] != 0) {
            lbl_1_bss_6F5F0 = 1;
            fn_1_A6870(&lbl_1_bss_6F5F0);
        }
    } else if ((s32)lbl_1_data_341B8->unk_0 != 0) {
        fn_1_A5F44();
        result = fn_1_A6480();
    } else {
        OSSetProgressiveMode(0);
        lbl_1_data_341B8->unk_0 = 0;
        result = 1;
    }
    return result;
}
/* fzgx:end fn_1_A66FC */

/* fzgx:begin fn_1_A67E8 */
#include "types.h"

struct fn_1_A67E8_lbl_1_bss_6F5F0 {
    u32 unk_0;
};


extern void fn_1_A6870(u32 *);

void fn_1_A67E8(void) {
    s32 var_r0;
    s32 temp_r3;

    temp_r3 = (*(struct fn_1_A67E8_lbl_1_bss_6F5F0 *)&lbl_1_bss_6F5F0).unk_0 + 1;
    if (temp_r3 > 3) {
        var_r0 = 0;
    } else {
        var_r0 = 3;
        if (temp_r3 >= 0) {
            var_r0 = temp_r3;
        }
    }
    (*(struct fn_1_A67E8_lbl_1_bss_6F5F0 *)&lbl_1_bss_6F5F0).unk_0 = (u32) var_r0;
    fn_1_A6870((u32 *)(&(*(struct fn_1_A67E8_lbl_1_bss_6F5F0 *)&lbl_1_bss_6F5F0).unk_0));
}
/* fzgx:end fn_1_A67E8 */

/* fzgx:begin fn_1_A6840 */
void fn_1_A6840(u32 value) {
    u32 *value_ptr;

    value_ptr = &lbl_1_bss_6F5F0;
    *value_ptr = value & 0xff;
    fn_1_A6870(value_ptr);
}
/* fzgx:end fn_1_A6840 */
