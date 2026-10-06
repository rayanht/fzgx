#include "types.h"

typedef struct Fn12_23410_Decoder {
    void *funcs[14];
} Fn12_23410_Decoder;

typedef struct Fn12_23410_Info {
    u8 pad_0[0xC];
    const Fn12_23410_Decoder *decoder;
    u8 pad_10[0x18];
    u8 channels;
    u8 pad_29[0x3];
    u32 sample_rate;
} Fn12_23410_Info;

extern u8 lbl_12_bss_7250[0x800];
extern const Fn12_23410_Decoder lbl_12_rodata_A18;
extern s32 fn_12_215F4(u8 *data, s32 size, u32 *out);
extern void *memcpy(void *, const void *, u32);

static inline BOOL fn_12_23410_probe(u8 *data, s32 size, Fn12_23410_Info *info) {
    s32 len;
    u8 *p;
    u32 tmp;

    len = 0x800;
    if (size < 0x800) {
        len = size;
    }
    memcpy(lbl_12_bss_7250, data, len);
    for (p = lbl_12_bss_7250; len > 0; p += 4, len -= 4) {
        if (fn_12_215F4(p, len, &tmp)) {
            info->decoder = &lbl_12_rodata_A18;
            info->channels = p[7];
            info->sample_rate = (p[8] << 24) | (p[9] << 16) | (p[10] << 8) | p[11];
            return TRUE;
        }
    }
    return FALSE;
}

s32 fn_12_23410(u8 *data, s32 size, Fn12_23410_Info *info) {
    if (fn_12_23410_probe(data, size, info)) {
        return 1;
    }
    if (fn_12_23410_probe(data + 2, size - 2, info)) {
        return 1;
    }
    if (fn_12_23410_probe(data + 1, size - 1, info)) {
        return 1;
    }
    if (fn_12_23410_probe(data + 3, size - 3, info)) {
        return 1;
    }
    return 0;
}
