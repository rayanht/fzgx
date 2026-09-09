#include "types.h"
#include "dol/globals.h"

typedef struct {
    u8 pad_0[0xAC];
    s32 unk_AC;
    s32 unk_B0;
    s32 unk_B4;
    s32 unk_B8;
    u8 pad_BC[0x14];
    u32 unk_D0;
    void (*unk_D4)(s32, s32);
} BlockWriteControlBlock;

extern s32 __CARDWritePage(s32 index, void (*callback)(s32, s32));
extern void __CARDPutControlBlock(BlockWriteControlBlock *block, s32 result);

void BlockWriteCallback(s32 index, s32 result) {
    BlockWriteControlBlock *block;
    void (*callback)(s32, s32);

    block = (BlockWriteControlBlock *)((u8 *)&lbl_80177960 + index * 0x110);
    if (result >= 0) {
        block->unk_B8 += 0x80;
        block->unk_B0 += 0x80;
        block->unk_B4 += 0x80;
        if (--block->unk_AC > 0) {
            result = __CARDWritePage(index, BlockWriteCallback);
            if (result >= 0) {
                return;
            }
        }
    }
    if (block->unk_D0 == 0) {
        __CARDPutControlBlock(block, result);
    }
    callback = block->unk_D4;
    if (callback != 0) {
        block->unk_D4 = 0;
        callback(index, result);
    }
}
