#include "types.h"
typedef struct Sig_fn_12_3A36C_Fn12_3A36C_Object {
    u32 unk0;
    u32 unk4;
} Sig_fn_12_3A36C_Fn12_3A36C_Object;

extern u32 fn_12_3A36C(Sig_fn_12_3A36C_Fn12_3A36C_Object *);
extern u32 fn_80056730(u32, u32);
static const char fzgx_pool_strings_lbl_12_rodata_12E0_0[44] = "E1122642: mwPlyLinkStm: handle is invalid.";
static const char fzgx_pool_strings_lbl_12_rodata_12E0_2C[44] = "E99072101 mwPlyLinkStm: can't link stream";
static const char fzgx_pool_strings_lbl_12_rodata_12E0_58[48] = "E1122637: mwPlyGetSlFname: handle is invalid.";
static const char fzgx_pool_strings_lbl_12_rodata_12E0_88[40] = "E10821B : Invalid value of stm_no : %d";
static const char fzgx_pool_strings_lbl_12_rodata_12E0_B0[48] = "E1122632: mwPlyStartAfsLp: handle is invalid.";
static const char fzgx_pool_strings_lbl_12_rodata_12E0_E0[44] = "E1122636: mwPlyEntryAfs: handle is invalid.";
static const char fzgx_pool_strings_lbl_12_rodata_12E0_10C[52] = "E008311 mwPlyEntryAfs: can't entry pid=%d fid=%d";
static const char fzgx_pool_strings_lbl_12_rodata_12E0_140[44] = "E1122641: mwPlySetLpFlg: handle is invalid.";
static const char fzgx_pool_strings_lbl_12_rodata_12E0_16C[52] = "E1122634: mwPlyStartSeamless: handle is invalid.";
static const char fzgx_pool_strings_lbl_12_rodata_12E0_1A0[52] = "E1122635: mwPlyReleaseSeamless: handle is invalid.";
static const char fzgx_pool_strings_lbl_12_rodata_12E0_1D4[48] = "E1122631: mwPlyReleaseLp: handle is invalid.";

extern void MWSFSVM_Error(const char *, ...);

void fn_12_346BC(u32 arg0) {
    
    u32 v0;
    u32 t0;
    u32 t2;
    u32 t4;
    s32 t5;
    u32 t7;
    
    t0 = fn_12_3A36C((Sig_fn_12_3A36C_Fn12_3A36C_Object *)arg0);
    v0 = t0;
    if ((s32)t0 == 0) {
    v0 = (u32)(((u8 *)fzgx_pool_strings_lbl_12_rodata_12E0_1D4));
    MWSFSVM_Error((const char *)(u32)v0);
    } else {
    v0 = arg0;
    t2 = fn_12_3A36C((Sig_fn_12_3A36C_Fn12_3A36C_Object *)v0);
    v0 = t2;
    if ((s32)v0 == 0) {
    v0 = (u32)(((u8 *)fzgx_pool_strings_lbl_12_rodata_12E0_140));
    MWSFSVM_Error((const char *)(u32)v0);
    } else {
    v0 = *(u32 *)((u8 *)arg0 + 76);
    t4 = fn_80056730(v0, 0);
    v0 = t4;
    }
    v0 = arg0;
    t5 = fn_12_3A36C((Sig_fn_12_3A36C_Fn12_3A36C_Object *)v0);
    v0 = t5;
    if (((0) == ((s32)v0))) {
    v0 = (u32)(((u8 *)fzgx_pool_strings_lbl_12_rodata_12E0_1A0));
    MWSFSVM_Error((const char *)(u32)v0);
    } else {
    v0 = arg0;
    t7 = fn_12_3A36C((Sig_fn_12_3A36C_Fn12_3A36C_Object *)v0);
    v0 = t7;
    if ((s32)v0 == 0) {
    v0 = (u32)(((u8 *)fzgx_pool_strings_lbl_12_rodata_12E0_0));
    MWSFSVM_Error((const char *)(u32)v0);
    } else {
    if ((s32)*(u8 *)((u8 *)arg0 + 112) == 1) {
    *(u8 *)((u8 *)arg0 + 113) = 1;
    }
    *(u8 *)((u8 *)arg0 + 112) = 0;
    }
    }
    }
}
