#include "types.h"
#include "rel/customize/globals.h"
#include "rel/customize/editor.h"


extern struct Obj *fn_3_14074(void);
extern u8 lbl_3_bss_A2408[8];
extern void *fn_1_45D0(void *, u32, char *, u32);
extern void fn_80008BEC(void *, u32, u32);
extern void fn_3_17100(void);
extern u32 lbl_801A6410;
extern void fn_1_46B4(u32, u32, char *, int);
extern const f32 lbl_3_rodata_5FC[3];

/* fzgx:begin fn_3_1552C */
struct Obj {
    u8 pad[0x10];
    u16 width;
    u16 height;
};

void fn_3_1552C(void) {
    struct Obj *ptr;

    ptr = fn_3_14074();
    ptr->width = 0x20;
    ptr->height = 0x20;
    *(u32 *)((*(u8 (*)[28])&lbl_3_bss_A23EC) + 0xC) = 0x20000000;
    *(u8 *)((*(u8 (*)[28])&lbl_3_bss_A23EC) + 0x11) = 1;
    *(u8 *)((*(u8 (*)[28])&lbl_3_bss_A23EC) + 0x16) = 0;
    *(u8 *)((*(u8 (*)[28])&lbl_3_bss_A23EC) + 0x0) = 0;
    *(u32 *)((*(u8 (*)[28])&lbl_3_bss_A23EC) + 0x4) =
        (u32)fn_1_45D0((*(void * *)&lbl_801A6410), 0x2000, (*(char (*)[9])&lbl_3_data_35B0), 0x4A);
    *(u32 *)((*(u8 (*)[28])&lbl_3_bss_A23EC) + 0x8) =
        (u32)fn_1_45D0((*(void * *)&lbl_801A6410), 0x2000, (*(char (*)[9])&lbl_3_data_35B0), 0x4B);
    fn_80008BEC(*(void **)((*(u8 (*)[28])&lbl_3_bss_A23EC) + 0x4), 0, 0x2000);
    fn_80008BEC(*(void **)((*(u8 (*)[28])&lbl_3_bss_A23EC) + 0x8), 0, 0x2000);
    *lbl_3_bss_A2408 = 0;
}
/* fzgx:end fn_3_1552C */

/* fzgx:begin fn_3_1560C */



void fn_3_1560C(void) {
    *(u32 *)((*(u8 (*)[28])&lbl_3_bss_A23EC) + 0xC) = (u32)1 << 31;
}
/* fzgx:end fn_3_1560C */

/* fzgx:begin fn_3_15620 */



void fn_3_15620(void) {
    *(u8 *)((*(u8 (*)[28])&lbl_3_bss_A23EC) + 0x10) = 0;
    *(u32 *)((*(u8 (*)[28])&lbl_3_bss_A23EC) + 0xc) = 0x40000000;
}
/* fzgx:end fn_3_15620 */

/* fzgx:begin fn_3_1563C */
void fn_3_1563C(void) {
    fn_1_46B4(lbl_801A6410, *(u32 *)((*(u8 (*)[28])&lbl_3_bss_A23EC) + 0x4),
              (*(char (*)[9])&lbl_3_data_35B0), 0x71);
    fn_1_46B4(lbl_801A6410, *(u32 *)((*(u8 (*)[28])&lbl_3_bss_A23EC) + 0x8),
              (*(char (*)[9])&lbl_3_data_35B0), 0x72);
}
/* fzgx:end fn_3_1563C */

/* fzgx:begin fn_3_156A8 */



void fn_3_156A8(void) {
    u8 value = ((*(u8 (*)[28])&lbl_3_bss_A23EC)[0x11] & 0x7f) << 1;
    (*(u8 (*)[28])&lbl_3_bss_A23EC)[0x11] = value;
    if (value > 6) {
        (*(u8 (*)[28])&lbl_3_bss_A23EC)[0x11] = 1;
    }
}
/* fzgx:end fn_3_156A8 */

/* fzgx:begin fn_3_170E0 */
void fn_3_170E0(void) {
    fn_3_17100();
}
/* fzgx:end fn_3_170E0 */

/* fzgx:begin fn_3_17820 */



u32 fn_3_17820(void) {
    return *(u32 *)&(*(u16 (*)[20])&lbl_3_bss_A2410)[2];
}
/* fzgx:end fn_3_17820 */

/* fzgx:begin fn_3_17830 */
typedef struct CustomizeState {
    u8 _pad0[8];
    u32 flags;
    u8 _pad1[16];
    f32 field_1c;
} CustomizeState;

void fn_3_17830(void) {
    (*(CustomizeState *)&lbl_3_bss_A2410).field_1c = lbl_3_rodata_5FC[0];
    (*(CustomizeState *)&lbl_3_bss_A2410).flags |= 0x20000000u;
}
/* fzgx:end fn_3_17830 */
