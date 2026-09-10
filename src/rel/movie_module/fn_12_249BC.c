#include "types.h"

extern u32 lbl_12_bss_7C64[137];
extern u32 lbl_12_bss_7C5C[2];

typedef void (*MovieCallback)(void *, u32);

typedef struct MovieObject {
    u8 pad48[0x48];
    s32 field48;
    u8 pad98c[0x940];
    void *field98c;
    void *field990;
} MovieObject;

s32 fn_12_249BC(MovieObject *obj, void *arg0, void *arg1) {
    s32 result;

    if (obj == 0) {
        lbl_12_bss_7C64[0x19c / 4] = (u32)arg0;
        lbl_12_bss_7C64[0x1a0 / 4] = (u32)arg1;
    } else {
        lbl_12_bss_7C5C[0] = (u32)obj;
        if (obj == 0) {
            result = -1;
        } else if (obj->field48 == 0) {
            result = -1;
        } else {
            result = 0;
        }
        if ((s32)result != 0) {
            if ((s32)lbl_12_bss_7C64[0x1a4 / 4] == 0) {
                lbl_12_bss_7C64[0x1a4 / 4] = 0xff000101;
            }
            if (lbl_12_bss_7C64[0x19c / 4] != 0) {
                ((MovieCallback)(u32)lbl_12_bss_7C64[0x19c / 4])(
                    (void *)lbl_12_bss_7C64[0x1a0 / 4], 0xff000101);
            }
            return 0xff000101;
        }
        obj->field98c = arg0;
        obj->field990 = arg1;
    }
    return 0;
}
