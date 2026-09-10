#include "types.h"

typedef struct MovieModule {
    u8 pad10[0x10];
    u32 state;
    u32 arg1;
    u32 arg2;
    u8 pad1c[4];
    void *value;
} MovieModule;

extern char lbl_12_rodata_58[8];
extern char lbl_12_rodata_50[5];

typedef struct Sig_SJ_SearchTag_SJCK {
    unsigned char *data;
    int len;
} Sig_SJ_SearchTag_SJCK;

extern unsigned char *SJ_SearchTag(const Sig_SJ_SearchTag_SJCK *needle, const char *name, const char *tag, Sig_SJ_SearchTag_SJCK *out);
extern void fn_12_47C8(void *value, u32 arg1, u32 arg2);

void fn_12_818(MovieModule *self, u32 arg1, u32 arg2) {
    void *value = self->value;
    Sig_SJ_SearchTag_SJCK tag;
    Sig_SJ_SearchTag_SJCK out;

    self->arg1 = arg1;
    self->arg2 = arg2;
    tag.data = (unsigned char *)arg1;
    tag.len = arg2;
    if (SJ_SearchTag(&tag, lbl_12_rodata_50, lbl_12_rodata_58, &out) == 0) {
        fn_12_47C8(value, 0, 0);
    } else {
        fn_12_47C8(value, (u32)out.data, (u32)out.len);
    }
    self->state = 1;
}
