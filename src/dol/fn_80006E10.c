#include "types.h"

extern BOOL DVDChangeDir(char *);
extern void fn_80083DB0(void *, const void *);
extern size_t strlen(const char *);
extern s32 strncmp(const char *, const char *, size_t);
extern char *strcat(char *, const char *);
extern u8 lbl_8015BD40[256];
extern char lbl_801A63F8[2];
extern char lbl_801A63FC[3];

void fn_80006E10(u32 arg0) {
    u8 *p_lbl_8015BD40;
    u8 *v0;
    s32 v2;

    v0 = (u8 *)arg0;
    DVDChangeDir((char *)arg0);
    p_lbl_8015BD40 = lbl_8015BD40;
    while (*v0 != 0) {
        if (*v0 == '/') {
            for (v2 = 1; v2 < strlen((const char *)v0) + 1; v2++) {
                if (v0[v2] != '/') {
                    fn_80083DB0(lbl_8015BD40, &v0[v2 - 1]);
                    v0 += v2;
                    break;
                }
            }
        } else if (strncmp((const char *)v0, lbl_801A63FC, 2) == 0) {
            for (v2 = strlen((const char *)lbl_8015BD40) - 1; v2 >= 0; v2--) {
                if (lbl_8015BD40[v2] == '/') {
                    lbl_8015BD40[v2] = 0;
                    v0 += 2;
                    break;
                }
            }
            if (lbl_8015BD40[0] == 0) {
                fn_80083DB0(lbl_8015BD40, lbl_801A63F8);
            }
        } else {
            if (lbl_8015BD40[0] != '/' || p_lbl_8015BD40[1] != 0) {
                strcat((char *)lbl_8015BD40, lbl_801A63F8);
            }
            strcat((char *)lbl_8015BD40, (const char *)v0);
            v0 += strlen((const char *)v0);
        }
        if (p_lbl_8015BD40[0] != '/' || p_lbl_8015BD40[1] != 0) {
            v2 = strlen((const char *)lbl_8015BD40) - 1;
            if (lbl_8015BD40[v2] == '/') {
                lbl_8015BD40[v2] = 0;
            }
        }
    }
}
