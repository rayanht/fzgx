#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/ptclput.h"

extern u16 lbl_1_bss_6EA94;
extern struct fn_1_9F870_lbl_801A6410 lbl_801A6410;
extern u32 fn_1_46B4(u32, u32, void *, u32);

/* fzgx:begin fn_1_9F870 */
#include "types.h"

struct fn_1_9F870_lbl_1_bss_6EA88 {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
};
struct fn_1_9F870_lbl_801A6410 {
    u32 unk_0;
};

void fn_1_9F870(void) {
    struct fn_1_9F870_lbl_1_bss_6EA88 *p_lbl_1_bss_6EA88;
    p_lbl_1_bss_6EA88 = (struct fn_1_9F870_lbl_1_bss_6EA88 *)&lbl_1_bss_6EA88;
    fn_1_46B4(lbl_801A6410.unk_0, p_lbl_1_bss_6EA88->unk_0, &lbl_1_data_2CD20, 1226);
    fn_1_46B4(lbl_801A6410.unk_0, p_lbl_1_bss_6EA88->unk_4, &lbl_1_data_2CD20, 1227);
    fn_1_46B4(lbl_801A6410.unk_0, p_lbl_1_bss_6EA88->unk_8, &lbl_1_data_2CD20, 1228);
}
/* fzgx:end fn_1_9F870 */

/* fzgx:begin fn_1_9F8FC */
void fn_1_9F8FC(void) {
    lbl_1_bss_6EA94 = 0;
    lbl_1_bss_6EA96 = 0;
}
/* fzgx:end fn_1_9F8FC */

/* fzgx:begin fn_1_9F914 */
extern void fn_80008BA8(void *, const void *, u32);

int fn_1_9F914(const void *src0, const void *src1) {
    Obj_1_bss_6EA88 *obj = &lbl_1_bss_6EA88;

    if (*(u16 *)((u8 *)obj + 0xc) == 0x100) {
        return 0;
    }
    fn_80008BA8((u8 *)obj->unk_0 +
                    ((*(u16 *)((u8 *)obj + 0xc) & 0xffff) << 6),
                src0, 0x40);
    fn_80008BA8((u8 *)obj->unk_4 +
                    (*(u16 *)((u8 *)obj + 0xc) << 6),
                src1, 0x40);
    *(u16 *)((u8 *)obj + 0xc) = *(u16 *)((u8 *)obj + 0xc) + 1;
    return 1;
}
/* fzgx:end fn_1_9F914 */

/* fzgx:begin fn_1_9F9A4 */
struct fn_1_9F9A4_Blk {
    u32 w0;
    u32 w1;
    u32 w2;
    u32 w3;
    u32 w4;
    u32 w5;
};

extern u32 lbl_1_bss_6EA90;
extern u16 lbl_1_bss_6EA96;

s32 fn_1_9F9A4(u32 arg0) {
    u16 v0;
    u32 v1;
    u32 v2;

    v0 = lbl_1_bss_6EA96;
    v1 = arg0;
    if (v0 == 256) {
        v1 = 0;
        return v1;
    }
    v2 = (lbl_1_bss_6EA90 + (v0 * 24));
    *(struct fn_1_9F9A4_Blk *)v2 = *(struct fn_1_9F9A4_Blk *)v1;
    lbl_1_bss_6EA96++;
    return 1;
}
/* fzgx:end fn_1_9F9A4 */
