#include "types.h"

extern u32 fn_8008A754(void);
extern void OSReport(const char *);
extern void fn_8008A748(u32);

s32 fn_8008963C(const char *arg0) {
    s32 rc = 0;
    s8 ch;
    s32 r;
    struct {
        u8 a[2];
    } loc_8;

    while (rc == 0 && (ch = *arg0++) != 0) {
        r = fn_8008A754();
        loc_8.a[0] = ch;
        loc_8.a[1] = '\0';
        fn_8008A748(0);
        OSReport((const char *)&loc_8);
        fn_8008A748(r);
        rc = 0;
    }
    return rc;
}
