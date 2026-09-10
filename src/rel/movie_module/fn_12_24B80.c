#include "types.h"

extern u32 lbl_12_bss_7C64[137];
extern int fn_12_2B6B0(void *);
extern void fn_12_2F19C(void *);
extern void fn_12_22FB4(void *);
extern int fn_12_2F730(void *);
extern void fn_12_24904(void);
extern void fn_80058630(void);

int fn_12_24B80(void) {
    u32 *entry;
    int result;
    int final_result;
    int i;
    int rv;

    entry = &lbl_12_bss_7C64[129];
    result = 0;
    i = 0;
    for (; i < 8; i++) {
        if (*entry != 0) {
            result = fn_12_2B6B0((void *)*entry);
        }
        entry++;
    }
    fn_12_2F19C((void *)&lbl_12_bss_7C64[108]);
    fn_12_22FB4((void *)&lbl_12_bss_7C64[111]);
    final_result = fn_12_2F730((void *)&lbl_12_bss_7C64[112]);
    fn_12_24904();
    fn_80058630();
    if (final_result != 0) {
        return final_result;
    }
    rv = 0;
    if (result != 0) {
        rv = result;
    }
    return rv;
}
