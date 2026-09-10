#include "types.h"
#include "dol/globals.h"

typedef struct Fn80067898Queue {
    u8 _pad_240[0x240];
    u32 slots[0x40];
    u8 _pad_340[0x101];
    u8 count;
    u8 _pad_442;
    u8 index;
    u8 _pad_444[0x20];
    s8 busy;
} Fn80067898Queue;

extern u32 lbl_801A6C78;

extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32);

s32 fn_80067898(u32 value) {
    s32 result = 0;
    Fn80067898Queue *queue;

    queue = (Fn80067898Queue *)lbl_801A6C80;
    if (queue->busy != 0) {
        return -3;
    }

    queue->busy = -1;
    if ((value & 0x80000000) == 0) {
        result = -2;
    } else {
        lbl_801A6C78 = OSDisableInterrupts();
        queue = (Fn80067898Queue *)lbl_801A6C80;
        if (queue->count < 0x40 && queue->slots[queue->index] == 0) {
            queue->slots[queue->index] = value;
            queue = (Fn80067898Queue *)lbl_801A6C80;
            queue->index = (queue->index + 1) & 0x3f;
            queue = (Fn80067898Queue *)lbl_801A6C80;
            queue->count++;
        } else {
            result = -1;
        }
        OSRestoreInterrupts(lbl_801A6C78);
    }

    queue = (Fn80067898Queue *)lbl_801A6C80;
    queue->busy = 0;
    return result;
}
