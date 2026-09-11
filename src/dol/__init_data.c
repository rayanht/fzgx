#include "types.h"

typedef struct {
    void *src;  /* 0x0 */
    void *dst;  /* 0x4 */
    u32 size;   /* 0x8 */
} RomCopyInfo;

typedef struct {
    void *addr; /* 0x0 */
    u32 size;   /* 0x4 */
} BssInitInfo;

extern RomCopyInfo _rom_copy_info[];
extern BssInitInfo _bss_init_info[];
extern void *memcpy(void *, const void *, u32);
extern void *memset(void *, int, u32);
extern void __flush_cache(void *, u32);

#pragma peephole off
__declspec(section ".init") void __init_data(void) {
    void *src;
    void *dst;
    void *addr;
    u32 size;
    RomCopyInfo *p;
    BssInitInfo *q;

    for (p = _rom_copy_info; ; p++) {
        if ((size = p->size) == 0) {
            break;
        }
        src = p->src;
        dst = p->dst;
        if (size != 0 && dst != src) {
            memcpy(dst, src, size);
            __flush_cache(dst, size);
        }
    }

    for (q = _bss_init_info; ; q++) {
        if ((size = q->size) == 0) {
            break;
        }
        addr = q->addr;
        if (size != 0) {
            memset(addr, 0, size);
        }
    }
}
#pragma peephole reset

