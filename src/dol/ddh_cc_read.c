#include "types.h"

extern u32 MWTRACE(u32, ...);
extern u32 fn_8008EED8(void);
extern u32 fn_8008EFE0(void *, u32);
extern u32 fn_8008E21C(u8 *, void *, u32);
extern u32 fn_8008E374(u8 *);
extern u32 fn_8008E114(u8 *, u32, u32);
extern s32 lbl_801A6E08;
extern u32 lbl_80095D2C[];
extern u32 lbl_80095D54[];
extern u8 lbl_801A5E58[];

s32 ddh_cc_read(u32 arg0, s32 arg1) {
    u8 buffer[0x800];
    s32 len;
    u32 result;
    u32 chunk;

    len = arg1;
    result = 0;
    if (lbl_801A6E08 == 0) {
        return -10001;
    }

    MWTRACE(1, (u32)&lbl_80095D2C, len, len);
    while (fn_8008E374(lbl_801A5E58) < len) {
        result = 0;
        chunk = fn_8008EED8();
        if (chunk != 0) {
            result = fn_8008EFE0(buffer, chunk);
            if (result == 0) {
                fn_8008E21C(lbl_801A5E58, buffer, chunk);
            }
        }
    }

    if (result == 0) {
        fn_8008E114(lbl_801A5E58, arg0, arg1);
    } else {
        MWTRACE(8, (u32)&lbl_80095D54, result);
    }
    return result;
}
