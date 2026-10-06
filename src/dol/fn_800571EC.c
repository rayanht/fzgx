#include "types.h"

typedef struct Fn800571EC_Stream Fn800571EC_Stream;

typedef struct Fn800571EC_StreamVtbl {
    u8 pad_0[0x24];
    s32 (*unk_24)(Fn800571EC_Stream *, s32);
} Fn800571EC_StreamVtbl;

struct Fn800571EC_Stream {
    Fn800571EC_StreamVtbl *vtbl;
};

typedef struct Fn800571EC_Slot {
    u8 pad_0[0x18];
    s32 unk_18;
    u8 pad_1C[0x4];
} Fn800571EC_Slot;

typedef struct Fn800571EC_Entry {
    s8 unk_0;
    s8 unk_1;
    u8 pad_2[0x6];
    Fn800571EC_Stream *unk_8;
    u8 pad_C[0x8];
    s32 unk_14;
    s32 unk_18;
    u8 pad_1C[0x1C];
    Fn800571EC_Slot slots[16];
} Fn800571EC_Entry;

extern char lbl_80092238[];
extern char lbl_80092264[];
extern Fn800571EC_Entry lbl_80188A8C[16];
extern void fn_800565FC(const char *, ...);
extern void fn_80056710(void *);
extern void fn_800566F0(void *);

static inline Fn800571EC_Entry *fn_800571EC_FindFree(void) {
    Fn800571EC_Entry *entry = NULL;
    s32 i;

    for (i = 0; i < 16; i++) {
        if (lbl_80188A8C[i].unk_0 == 0) {
            entry = &lbl_80188A8C[i];
            break;
        }
    }
    return entry;
}

Fn800571EC_Entry *fn_800571EC(Fn800571EC_Stream *stream) {
    u8 lock[8];
    Fn800571EC_Entry *entry;
    s32 i;

    if (stream == NULL) {
        fn_800565FC(lbl_80092238);
        return NULL;
    }

    fn_80056710(lock);
    entry = fn_800571EC_FindFree();

    if (entry == NULL) {
        fn_800565FC(lbl_80092264);
    } else {
        entry->unk_8 = stream;
        entry->unk_1 = 0;
        entry->unk_18 = stream->vtbl->unk_24(stream, 0) + stream->vtbl->unk_24(stream, 1);
        entry->unk_14 = entry->unk_18 * 8 / 10;
        for (i = 0; i < 16; i++) {
            entry->slots[i].unk_18 = 0;
        }
        entry->unk_0 = 1;
    }
    fn_800566F0(lock);
    return entry;
}
