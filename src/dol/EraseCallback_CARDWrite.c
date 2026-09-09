#include "types.h"
#include "dol/globals.h"

typedef struct {
    u8 pad_0[0xC];
    s32 unk_C;
    u8 pad_10[0xA4];
    s32 unk_B4;
    u8 pad_B8[0x8];
    void *unk_C0;
    u8 pad_C4[0xC];
    void (*unk_D0)(s32, s32);
} EraseCallbackControlBlock;

extern s32 __CARDWrite(s32 index, s32 length, s32 offset, s32 buffer,
                       void (*callback)(s32, s32));
extern void __CARDPutControlBlock(EraseCallbackControlBlock *block, s32 result);
extern void WriteCallback_CARDWrite(s32 index, s32 result);

void EraseCallback_CARDWrite(s32 index, s32 result) {
    EraseCallbackControlBlock *block;
    void (*callback)(s32, s32);

    block = (EraseCallbackControlBlock *)((u8 *)&lbl_80177960 + index * 0x110);
    if (result >= 0) {
        result = __CARDWrite(index, block->unk_C * *(u16 *)((u8 *)block->unk_C0 + 0x10),
                             block->unk_C, block->unk_B4, WriteCallback_CARDWrite);
        if (result >= 0) {
            return;
        }
    }
    callback = block->unk_D0;
    block->unk_D0 = 0;
    __CARDPutControlBlock(block, result);
    callback(index, result);
}
