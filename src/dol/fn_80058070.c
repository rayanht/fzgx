#include "types.h"

typedef struct Fn80058070_Ring {
    u8 pad_0[0xC];
    s32 unk_C;
    s32 unk_10;
    u8 pad_14[0x8];
    u8 *base;
    s32 size;
    s32 mirror;
    u8 pad_28[0x4];
    s32 unk_2C;
    u8 pad_30[0x4];
    s32 unk_34;
    void (*callback)(s32, s32);
    s32 callback_arg;
} Fn80058070_Ring;

typedef struct Fn80058070_Chunk {
    u8 *ptr;
    s32 len;
} Fn80058070_Chunk;

extern u32 fn_80057728(void);
extern void *memcpy(void *, const void *, u32);
extern u32 fn_800576DC(void);

u32 fn_80058070(Fn80058070_Ring *ring, s32 mode, Fn80058070_Chunk *chunk) {
    s32 offset;
    s32 end;
    s32 n;

    if (chunk->len > 0) {
        if (chunk->ptr == NULL) {
            return (u32)ring;
        }

        fn_80057728();
        if (mode == 1) {
            ring->unk_C += chunk->len;
            offset = chunk->ptr - ring->base;
            if (offset < ring->mirror) {
                n = ring->mirror - offset;
                if (chunk->len < n) {
                    n = chunk->len;
                }
                memcpy(&ring->base[ring->size + offset], chunk->ptr, n);
            }
            end = chunk->len + (chunk->ptr - ring->base);
            if (end > ring->size) {
                n = end - ring->size;
                if (chunk->len < n) {
                    n = chunk->len;
                }
                memcpy(ring->base, ring->base + (end - n), n);
            }
            ring->unk_34 += chunk->len;
        } else if (mode == 0) {
            ring->unk_10 += chunk->len;
            ring->unk_2C += chunk->len;
        } else {
            chunk->len = 0;
            chunk->ptr = NULL;
            if (ring->callback != NULL) {
                ring->callback(ring->callback_arg, -3);
            }
        }
        return fn_800576DC();
    }
    return (u32)ring;
}
