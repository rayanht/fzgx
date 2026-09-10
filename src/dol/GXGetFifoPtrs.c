
#include "types.h"

typedef struct {
    u8 pad[128];
} GXFifoObj;

struct __GXFifoObj {
    u8 *base;
    u8 *top;
    u32 size;
    u32 hiWatermark;
    u32 loWatermark;
    void *rdPtr;
    void *wrPtr;
    s32 count;
    u8 bind_cpu;
    u8 bind_gp;
};

void (*DVDLowClearCallback())(u32);

extern u16 *__cpReg;

extern u32 *__piReg;

extern struct __GXFifoObj *lbl_801A6BF0;

extern struct __GXFifoObj *lbl_801A6BF4;

void GXGetFifoPtrs(GXFifoObj *fifo, void **readPtr, void **writePtr) {
    struct __GXFifoObj *realFifo = (struct __GXFifoObj *)fifo;
    if (realFifo == lbl_801A6BF0) {
        realFifo->wrPtr = ((void *)((u32)((0x8000 << 16) + (u32)(__piReg[5] & 0xFBFFFFFF))));
    }
    if (realFifo == lbl_801A6BF4) {
        do {
            u32 temp = __cpReg[29] << 16;
            temp |= __cpReg[28];
            realFifo->rdPtr = ((void *)((u32)((0x8000 << 16) + (u32)(temp))));
        } while (0);
        do {
            u32 temp = __cpReg[25] << 16;
            temp |= __cpReg[24];
            realFifo->count = temp;
        } while (0);
    } else {
        realFifo->count = (u8 *)realFifo->wrPtr - (u8 *)realFifo->rdPtr;
        if (realFifo->count < 0) {
            realFifo->count += realFifo->size;
        }
    }
    *readPtr = realFifo->rdPtr;
    *writePtr = realFifo->wrPtr;
}
