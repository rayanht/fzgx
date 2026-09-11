#include "types.h"

#pragma use_lmw_stmw on

struct fn_12_CCC4_lbl_12_bss_6900 {
    u32 unk_0;
};
struct fn_12_CCC4_lbl_12_bss_6904 {
    u32 unk_0;
};
struct fn_12_CCC4_lbl_12_bss_528C {
    u8 pad_0[0x50];
    u32 unk_50;
};
struct fn_12_CCC4_lbl_12_bss_6908 {
    u32 unk_0;
};
struct fn_12_CCC4_lbl_12_bss_527C {
    u32 unk_0;
};

extern struct fn_12_CCC4_lbl_12_bss_527C lbl_12_bss_527C;
extern struct fn_12_CCC4_lbl_12_bss_528C lbl_12_bss_528C;
extern struct fn_12_CCC4_lbl_12_bss_6900 lbl_12_bss_6900;
extern struct fn_12_CCC4_lbl_12_bss_6904 lbl_12_bss_6904;
extern struct fn_12_CCC4_lbl_12_bss_6908 lbl_12_bss_6908;
extern u32 fn_12_33364(u32, u32, u32);
extern u32 fn_12_8B4C(u32);
extern u32 fn_12_A774(u32);
extern u32 fn_12_CA84(u32, u32, u32);
extern u32 fn_12_CA98(u32, u32, u32, u32, u32);
extern u32 lbl_12_bss_68F0;
extern u32 lbl_12_bss_68F4;
extern u32 lbl_12_bss_68F8;
extern u32 lbl_12_bss_68FC;
extern u32 lbl_12_bss_6914;
extern u32 lbl_12_bss_6918;
extern void fn_12_5548(void *);
#include "sofdec/mpvabdec.h"
extern s32 MPVABDEC_IntraBlock(MPVABDECContext *, MPVABDECBlock *);
extern s32 MPVABDEC_NintraBlock(MPVABDECContext *, MPVABDECBlock *);

u32 fn_12_CCC4(u32 arg0) {
    struct fn_12_CCC4_lbl_12_bss_6900 *p_lbl_12_bss_6900;
    struct fn_12_CCC4_lbl_12_bss_6904 *p_lbl_12_bss_6904;
    struct fn_12_CCC4_lbl_12_bss_6908 *p_lbl_12_bss_6908;
    struct fn_12_CCC4_lbl_12_bss_527C *p_lbl_12_bss_527C;
    u32 v3;
    u32 v6;
    u32 v7;
    s32 v8;
    v3 = lbl_12_bss_528C.unk_50;
    p_lbl_12_bss_6900 = (struct fn_12_CCC4_lbl_12_bss_6900 *)&lbl_12_bss_6900;
    p_lbl_12_bss_6904 = (struct fn_12_CCC4_lbl_12_bss_6904 *)&lbl_12_bss_6904;
    p_lbl_12_bss_6908 = (struct fn_12_CCC4_lbl_12_bss_6908 *)&lbl_12_bss_6908;
    p_lbl_12_bss_527C = (struct fn_12_CCC4_lbl_12_bss_527C *)&lbl_12_bss_527C;
    *(u32 *)((u8 *)arg0 + 16) = lbl_12_bss_68F0;
    *(u32 *)((u8 *)arg0 + 20) = (lbl_12_bss_68F4 - 16);
    *(u32 *)((u8 *)arg0 + 24) = (lbl_12_bss_68F8 - 32);
    *(u32 *)((u8 *)arg0 + 28) = (lbl_12_bss_68FC - 32);
    *(u32 *)((u8 *)arg0 + 32) = p_lbl_12_bss_6900->unk_0;
    *(u32 *)((u8 *)arg0 + 36) = p_lbl_12_bss_6904->unk_0;
    *(u32 *)((u8 *)arg0 + 40) = p_lbl_12_bss_6908->unk_0;
    *(u32 *)((u8 *)arg0 + 56) = (v3 + 352);
    *(u32 *)((u8 *)arg0 + 60) = (v3 + 384);
    *(u32 *)((u8 *)arg0 + 44) = (v3 + 32);
    *(u32 *)((u8 *)arg0 + 48) = v3;
    *(u32 *)((u8 *)arg0 + 52) = (v3 + 96);
    *(u32 *)((u8 *)arg0 + 64) = p_lbl_12_bss_527C->unk_0;
    *(u32 *)((u8 *)arg0 + 272) = *(u32 *)((u8 *)arg0 + 64);
    *(u32 *)((u8 *)arg0 + 276) = (arg0 + 832);
    *(u32 *)((u8 *)arg0 + 280) = (arg0 + 3264);
    v6 = (*(u32 *)((u8 *)arg0 + 280) + 384);
    *(u32 *)((u8 *)arg0 + 284) = v6;
    *(u32 *)((u8 *)arg0 + 804) = (arg0 + 1088);
    *(u32 *)((u8 *)arg0 + 808) = (arg0 + 1216);
    *(u32 *)((u8 *)arg0 + 812) = (arg0 + 1344);
    *(u32 *)((u8 *)arg0 + 816) = (arg0 + 1472);
    *(u32 *)((u8 *)arg0 + 820) = (arg0 + 832);
    *(u32 *)((u8 *)arg0 + 824) = (arg0 + 960);
    *(u32 *)((u8 *)arg0 + 696) = 0;
    *(u32 *)((u8 *)arg0 + 396) = 0;
    fn_12_33364((arg0 + 400), (u32)&lbl_12_bss_528C, 16);
    fn_12_A774((arg0 + 544));
    fn_12_8B4C(arg0);
    v7 = (arg0 + 120);
    fn_12_5548((void *)v7);
    *(u32 *)((u8 *)v7 + 72) = (arg0 + 3264);
    *(u32 *)((u8 *)v7 + 44) = (arg0 + 1600);
    *(u32 *)((u8 *)v7 + 48) = (arg0 + 804);
    *(u32 *)((u8 *)arg0 + 464) = 0;
    *(u32 *)((u8 *)arg0 + 468) = 0;
    *(u32 *)((u8 *)arg0 + 472) = 0;
    *(u32 *)((u8 *)arg0 + 476) = 0;
    *(u32 *)((u8 *)arg0 + 480) = 0;
    *(u32 *)((u8 *)arg0 + 484) = 0;
    *(u32 *)((u8 *)arg0 + 488) = 0;
    *(u32 *)((u8 *)arg0 + 492) = 0;
    *(u32 *)((u8 *)arg0 + 496) = 0;
    *(u32 *)((u8 *)arg0 + 500) = 0;
    *(u32 *)((u8 *)arg0 + 504) = 0;
    *(u32 *)((u8 *)arg0 + 508) = 0;
    *(u32 *)((u8 *)arg0 + 512) = 0;
    *(u32 *)((u8 *)arg0 + 516) = 3;
    *(u32 *)((u8 *)arg0 + 520) = 1;
    *(u32 *)((u8 *)arg0 + 524) = -1;
    *(u32 *)((u8 *)arg0 + 528) = -1;
    *(u32 *)((u8 *)arg0 + 532) = -1;
    *(u32 *)((u8 *)arg0 + 536) = 1;
    *(u32 *)((u8 *)arg0 + 540) = 1;
    *(u32 *)((u8 *)arg0 + 4800) = 0;
    *(u32 *)((u8 *)arg0 + 4804) = 0;
    *(u32 *)((u8 *)arg0 + 4856) = lbl_12_bss_6918;
    *(u32 *)((u8 *)arg0 + 4860) = lbl_12_bss_6914;
    *(u32 *)((u8 *)arg0 + 4820) = 0;
    *(u32 *)((u8 *)arg0 + 4824) = 0;
    *(u32 *)((u8 *)arg0 + 4828) = 0;
    *(u32 *)((u8 *)arg0 + 4832) = 0;
    *(u32 *)((u8 *)arg0 + 4836) = 0;
    *(u32 *)((u8 *)arg0 + 4840) = (u32)MPVABDEC_IntraBlock;
    *(u32 *)((u8 *)arg0 + 4844) = (u32)MPVABDEC_NintraBlock;
    *(u32 *)((u8 *)arg0 + 4852) = *(u32 *)((u8 *)arg0 + 428);
    v8 = 0;
    do {
    fn_12_CA98(arg0, v8, 0, 0, 0);
    v8++;
    } while ((s32)v8 < 4);
    fn_12_CA84(arg0, 0, 0);
    *(u32 *)((u8 *)arg0 + 392) = 2;
    return arg0;
}
