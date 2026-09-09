#include "types.h"
#include "dol/globals.h"

struct WriteCallbackControlBlock {
    u8 pad_0[0x80];
    u32 unk_80;
    u8 pad_84[0x4];
    u32 unk_88;
    u8 pad_8C[0x44];
    u32 unk_D0;
    u8 pad_D4[0x4];
    void (*unk_D8)(s32, s32);
    u8 pad_DC[0x34];
};

extern void __CARDPutControlBlock(struct WriteCallbackControlBlock *block, s32 result);
extern void memcpy(void *dst, const void *src, u32 size);

void WriteCallback(s32 index, s32 result) {
    struct WriteCallbackControlBlock *block;
    u32 source;
    u32 destination;
    u32 alternate;
    void (*callback)(s32, s32);

    block = (struct WriteCallbackControlBlock *)((u8 *)&lbl_80177960 + index * 0x110);
    if (result >= 0) {
        source = block->unk_80;
        destination = source + 0x6000;
        alternate = source + 0x8000;
        if (block->unk_88 == destination) {
            block->unk_88 = alternate;
            memcpy((void *)alternate, (void *)destination, 0x2000);
        } else {
            block->unk_88 = destination;
            memcpy((void *)destination, (void *)alternate, 0x2000);
        }
    }
    if (block->unk_D0 == 0) {
        __CARDPutControlBlock(block, result);
    }
    callback = block->unk_D8;
    if (callback != 0) {
        block->unk_D8 = 0;
        callback(index, result);
    }
}
