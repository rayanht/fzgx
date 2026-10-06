#include "types.h"

typedef struct Fn8004A5F4_Stm {
    u8 pad_0[0x1];
    s8 stat;
    s8 unk_2;
    u8 pad_3[0x5];
    void *fs;
    s32 ofst;
    s32 len;
    u8 pad_14[0x2D];
    s8 req_open;
    s8 req_close;
    s8 unk_43;
    s8 req_stop;
    s8 opened;
    u8 pad_46[0x6];
    char *fname;
    void *dir;
    s32 pos;
} Fn8004A5F4_Stm;

extern char lbl_80090990[];
extern void fn_80054AB0(void *fs);
extern void fn_80059B44(void);
extern void fn_80059AB4(void);
extern void *fn_80054B6C(char *fname, void *dir, s32 mode);
extern void fn_80047464(char *msg, char *fname);
extern void fn_80054930(void *fs, s32 offset, s32 origin);
extern s32 fn_800549F0(void *fs);
extern void fn_8004A80C(Fn8004A5F4_Stm *stm);

void fn_8004A5F4(Fn8004A5F4_Stm *stm) {
    void *fs;
    s32 size;
    s32 bytes;

    if (stm->unk_2 == 0) {
        if (stm->req_stop == 1) {
            stm->req_stop = 0;
            if (stm->unk_43 == 0) {
                stm->stat = 1;
            }
        }
        if (stm->req_close == 1) {
            if ((fs = stm->fs) != NULL) {
                stm->fs = NULL;
                fn_80054AB0(fs);
            }
            stm->req_close = 0;
            stm->opened = 0;
        }
        fn_80059B44();
        if (stm->req_open == 1) {
            stm->opened = 1;
            fn_80059AB4();
            if (stm->fs == NULL) {
                if ((stm->fs = fn_80054B6C(stm->fname, stm->dir, 0)) == NULL) {
                    fn_80047464(lbl_80090990, stm->fname);
                    stm->stat = 4;
                    stm->opened = 0;
                    stm->req_open = 0;
                    return;
                }
                fn_80054930(stm->fs, 0, 2);
                size = fn_800549F0(stm->fs);
                bytes = size << 11;
                fn_80054930(stm->fs, 0, 0);
                if (stm->len == 0x7FFFF800) {
                    stm->len = bytes;
                } else {
                    if (stm->ofst > size) {
                        stm->ofst = size;
                    }
                    if (stm->len / 0x800 + stm->ofst > size) {
                        stm->len = (size - stm->ofst) << 11;
                    }
                }
                stm->pos = 0;
                if ((stm->pos << 11) > stm->len) {
                    stm->pos = stm->len / 0x800 + (stm->len % 0x800 > 0);
                }
                stm->req_open = 0;
            }
        } else {
            fn_80059AB4();
        }
        if (stm->unk_43 == 1) {
            stm->unk_43 = 0;
        }
    }
    if (stm->stat == 2 && stm->opened == 1) {
        fn_8004A80C(stm);
    }
}
