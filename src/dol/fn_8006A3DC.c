#include "types.h"

extern char lbl_80132788[34];
extern char lbl_801A6610[6];
extern void OSPanic(const char *file, int line, const char *format, ...);

typedef struct Fn8006A3DCHeader {
    u32 magic;
    u32 data_offset;
    u32 unk_8;
    u32 table_offset;
} Fn8006A3DCHeader;

typedef struct Fn8006A3DCResult {
    void *header;
    void *data;
    void *table;
    u32 count;
    void *end;
    u32 unk_14;
    u32 unk_18;
} Fn8006A3DCResult;

u32 fn_8006A3DC(Fn8006A3DCHeader *src, Fn8006A3DCResult *dst) {
    u8 *data;
    if (src->magic != 0x55AA382D) {
        OSPanic(lbl_801A6610, 0x3b, lbl_80132788);
    }

    dst->header = src;
    data = (u8 *)src + src->data_offset;
    dst->data = data;
    dst->table = (u8 *)src + src->table_offset;
    dst->count = ((u32 *)data)[2];
    dst->end = data + dst->count * 0xc;
    dst->unk_14 = src->unk_8;
    dst->unk_18 = 0;
    return 1;
}
