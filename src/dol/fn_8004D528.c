#include "types.h"

typedef struct Fn8004D528_Obj Fn8004D528_Obj;

typedef struct Fn8004D528_Vtbl {
    u8 pad_0[0x14];
    void (*stop)(Fn8004D528_Obj *obj);
} Fn8004D528_Vtbl;

struct Fn8004D528_Obj {
    Fn8004D528_Vtbl *vtbl;
};

typedef struct Fn8004D528_Adxt {
    u8 used;
    s8 stat;
    s8 pmode;
    s8 maxnch;
    void *sjd;
    void *stm;
    void *rna;
    Fn8004D528_Obj *sji;
    u8 pad_14[0x24];
    s32 unk_38;
    u8 pad_3C[0x4];
    s16 unk_40;
    u8 pad_42[0x6];
    s32 unk_48;
    u8 pad_4C[0x4];
    s32 unk_50;
    u8 pad_54[0x20];
    void *unk_74;
    u8 pad_78[0x14];
    s32 unk_8C;
    s32 unk_90;
    u8 pad_94[0x14];
    s8 unk_A8;
    u8 pad_A9[0x7];
    s32 unk_B0;
    s32 unk_B4;
    s32 unk_B8;
    s32 unk_BC;
} Fn8004D528_Adxt;

extern char lbl_800910C4[];
extern s32 fn_8004AEE4(void *stm);
extern void fn_8004C980(Fn8004D528_Adxt *, s32, s32, s32, s32);
extern s32 fn_800421C0(void *sjd);
extern s32 fn_80041660(void *sjd);
extern void fn_80046F88(s32, s32, char *, s32);
extern void fn_80047464(const char *, char *);
extern void ADXT_Stop(Fn8004D528_Adxt *);
extern s32 fn_80041684(void *sjd);
extern s32 fn_800415D0(void *sjd);
extern s32 fn_80041618(void *sjd);
extern void fn_80042170(void *sjd, s32);
extern s32 fn_80041530(void *sjd);
extern void fn_8004AC04(void *stm, s32);
extern void fn_8004AC4C(void *stm, void (*)(Fn8004D528_Adxt *), Fn8004D528_Adxt *);
extern void adxt_eos_entry(Fn8004D528_Adxt *);
extern void fn_80041554(void *sjd);
extern s32 fn_800415AC(void *sjd);
extern void fn_800416DC(void *sjd, s32);
extern void fn_800416CC(void *sjd, s32);
extern void fn_800416D4(void *sjd, s32);
extern void fn_800416E4(void *sjd, void (*)(Fn8004D528_Adxt *), Fn8004D528_Adxt *);
extern void fn_8004DFF0(Fn8004D528_Adxt *);
extern void fn_8004D8DC(Fn8004D528_Adxt *);
extern s32 fn_800415F4(void *sjd);
extern s32 fn_8004163C(void *sjd);
extern void fn_8004EDA4(void *rna, s32);
extern void fn_8004EE04(void *rna, s32);
extern void fn_8004EE24(void *rna, s32);
extern void fn_8004ED80(void *rna, s32);
extern s16 fn_800414D0(void *sjd);
extern void fn_8004EDE4(void *rna, s32);
extern void fn_8004BBC4(Fn8004D528_Adxt *, s32 *, s32 *);
extern void fn_8004BBC8(Fn8004D528_Adxt *, s32, s32);
extern void adxt_set_outpan(Fn8004D528_Adxt *);
extern void fn_80046508(void *, s32);
extern s32 fn_800416A8(void *sjd);
extern s32 fn_80041458(void *sjd);
extern void fn_8004ED5C(void *rna, s32);
extern void fn_8004EEC4(void *rna, s32);

void fn_8004D528(Fn8004D528_Adxt *adxt) {
    void *sjd;
    s32 nch;
    s32 sfreq;
    s32 total;
    s32 block;
    s32 offset;
    s32 nsmpl;
    s32 nsct;
    s32 format;
    s32 loop;
    s32 lvol;
    s32 rvol;
    char buf[32];

    sjd = adxt->sjd;
    lvol = 0;
    rvol = 0;
    if ((adxt->pmode == 0 || adxt->pmode == 1) && adxt->unk_A8 == 1) {
        if (fn_8004AEE4(adxt->stm) == 2) {
            return;
        }
        if (adxt->sji != NULL) {
            adxt->sji->vtbl->stop(adxt->sji);
        }
        fn_8004C980(adxt, adxt->unk_B0, adxt->unk_B4, adxt->unk_B8, adxt->unk_BC);
        adxt->unk_A8 = 0;
    }
    if (fn_800421C0(sjd) != 2) {
        return;
    }
    nch = fn_80041660(sjd);
    if (nch > adxt->maxnch) {
        fn_80046F88(nch, adxt->maxnch, buf, 16);
        fn_80047464(lbl_800910C4, buf);
        ADXT_Stop(adxt);
        return;
    }

    sfreq = fn_80041684(sjd);
    total = fn_800415D0(sjd);
    if (total > 0) {
        adxt->unk_48 = sfreq / adxt->unk_38 * 3;
    } else {
        adxt->unk_48 = sfreq / adxt->unk_38 * 3 / 2;
    }
    block = fn_80041618(sjd) * 2;
    adxt->unk_48 = (adxt->unk_48 + block) / block * block;
    fn_80042170(sjd, adxt->unk_48);

    if (total > 0) {
        if (adxt->pmode == 2) {
            adxt->unk_50 = 0;
        } else {
            offset = fn_80041530(sjd);
            adxt->unk_50 = 0x800 - offset % 0x800;
            adxt->unk_50 = adxt->unk_50 % 0x800;
            nsct = (offset + 0x7FF) / 0x800;
            adxt->unk_8C = nsct;
            fn_8004AC04(adxt->stm, nsct);
            fn_8004AC4C(adxt->stm, adxt_eos_entry, adxt);
        }
        fn_80041554(sjd);
        adxt->unk_90 = fn_800415AC(sjd);
        fn_800416DC(sjd, adxt->unk_90);
        fn_800416CC(sjd, 0);
        fn_800416D4(sjd, 0);
        fn_800416E4(sjd, fn_8004DFF0, adxt);
    } else {
        if (adxt->stm != NULL) {
            fn_8004AC04(adxt->stm, 0x7FFFFFFF);
        }
        fn_800416DC(sjd, fn_800415F4(sjd));
        fn_800416CC(sjd, 0);
        fn_800416D4(sjd, 0);
        fn_800416E4(sjd, fn_8004D8DC, adxt);
    }

    sfreq = fn_80041684(sjd);
    nch = fn_80041660(sjd);
    nsmpl = fn_800415F4(sjd);
    format = fn_8004163C(sjd);
    fn_8004EDA4(adxt->rna, format);
    fn_8004EE04(adxt->rna, sfreq);
    fn_8004EE24(adxt->rna, nch);
    fn_8004ED80(adxt->rna, nsmpl);
    fn_8004EDE4(adxt->rna, adxt->unk_40 + fn_800414D0(adxt->sjd));
    fn_8004BBC4(adxt, &lvol, &rvol);
    if (lvol != 0 || rvol != 0) {
        fn_8004BBC8(adxt, lvol, rvol);
    }
    adxt_set_outpan(adxt);
    if (adxt->unk_74 != NULL) {
        fn_80046508(adxt->unk_74, sfreq);
    }
    if (fn_800416A8(sjd) == 2) {
        loop = fn_80041458(sjd);
        fn_8004ED5C(adxt->rna, loop);
    }
    fn_8004EEC4(adxt->rna, 1);
    adxt->stat = 2;
}
