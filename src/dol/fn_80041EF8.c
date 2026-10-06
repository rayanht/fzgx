#include "types.h"

typedef struct fn_80041EF8_Chunk {
    u8 *data;
    s32 len;
} fn_80041EF8_Chunk;

typedef struct fn_80041EF8_SjObj fn_80041EF8_SjObj;

typedef struct fn_80041EF8_SjIf {
    u8 pad_0[0x18];
    void (*GetChunk)(fn_80041EF8_SjObj *sj, s32 id, s32 nbyte, fn_80041EF8_Chunk *ck);
    void (*UngetChunk)(fn_80041EF8_SjObj *sj, s32 id, fn_80041EF8_Chunk *ck);
    void (*PutChunk)(fn_80041EF8_SjObj *sj, s32 id, fn_80041EF8_Chunk *ck);
} fn_80041EF8_SjIf;

struct fn_80041EF8_SjObj {
    fn_80041EF8_SjIf *vtbl;
};

typedef struct fn_80041EF8_Adxt {
    u8 pad_0[0x1];
    s8 stat;
    u8 pad_2[0x1];
    s8 unk_3;
    void *adxb;
    fn_80041EF8_SjObj *sji;
    u8 pad_C[0x4C];
    u8 hdr[0x40];
    s32 hdrlen;
} fn_80041EF8_Adxt;

extern s32 fn_800455B8(void *adxb, u8 *data, s32 len);
extern s32 fn_8004559C(void *adxb);
extern void fn_80047464(const char *msg1, const char *msg2);
extern void *memcpy(void *, const void *, u32);
extern void fn_800589BC(fn_80041EF8_Chunk *ck, s32 len, fn_80041EF8_Chunk *ck1, fn_80041EF8_Chunk *ck2);

void fn_80041EF8(fn_80041EF8_Adxt *adxt) {
    void *adxb;
    fn_80041EF8_SjObj *sj;
    fn_80041EF8_Chunk ck;
    fn_80041EF8_Chunk ck2;
    s32 hdrlen;
    s32 fmt;

    sj = adxt->sji;
    adxb = adxt->adxb;
    sj->vtbl->GetChunk(sj, 1, 0x1000, &ck);
    if (ck.len < 0x10) {
        sj->vtbl->UngetChunk(sj, 1, &ck);
        return;
    }
    hdrlen = fn_800455B8(adxb, ck.data, ck.len);
    if (hdrlen == 0 || hdrlen > ck.len) {
        sj->vtbl->UngetChunk(sj, 1, &ck);
        return;
    }
    if (hdrlen < 0) {
        sj->vtbl->UngetChunk(sj, 1, &ck);
        fn_80047464("E03010901 ADXB_DecodeHeader: ", "Can not decode this file format.");
        adxt->stat = 4;
        return;
    }
    adxt->hdrlen = hdrlen;
    if (fn_8004559C(adxb) == 4) {
        adxt->unk_3 = 1;
    }
    if (fn_8004559C(adxb) == 2) {
        memcpy(adxt->hdr, ck.data, (ck.len < 0x40) ? ck.len : 0x40);
    }
    fmt = fn_8004559C(adxb);
    if (fmt == 10 || fmt == 11 || fmt == 20 || fmt == 15) {
        sj->vtbl->UngetChunk(sj, 1, &ck);
    } else {
        fn_800589BC(&ck, hdrlen, &ck, &ck2);
        sj->vtbl->PutChunk(sj, 0, &ck);
        sj->vtbl->UngetChunk(sj, 1, &ck2);
    }
    adxt->stat = 2;
}
