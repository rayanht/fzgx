#include "types.h"
#include "dol/globals.h"

typedef struct {
    s32 unk_0;
    u8 pad_4[0xA8];
    s32 unk_AC;
    void *unk_B0;
    s32 unk_B4;
    u8 pad_B8[0x1C];
    void (*unk_D4)(s32, s32);
} BlockWriteControlBlock;

extern void BlockWriteCallback(s32 index, s32 result);
extern s32 __CARDWritePage(s32 index, void (*callback)(s32, s32));

s32 __CARDWrite(s32 index, void *buffer, u32 length, s32 offset,
                void (*callback)(s32, s32)) {
    BlockWriteControlBlock *block;

    block = (BlockWriteControlBlock *)((u8 *)&lbl_80177960 + index * 0x110);
    if (block->unk_0 == 0) {
        return -3;
    }
    block->unk_D4 = callback;
    block->unk_AC = length >> 7;
    block->unk_B0 = buffer;
    block->unk_B4 = offset;
    return __CARDWritePage(index, BlockWriteCallback);
}
