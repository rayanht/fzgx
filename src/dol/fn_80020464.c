#include <types.h>

typedef void (*ARQCallback)(u32 pointerToARQRequest);

typedef struct ARQRequest {
    struct ARQRequest *next;
    u32 owner;
    u32 type;
    u32 priority;
    u32 source;
    u32 dest;
    u32 length;
    ARQCallback callback;
} ARQRequest;

void ARStartDMA(u32 type, u32 mainmem_addr, u32 aram_addr, u32 length);

extern ARQRequest *lbl_801A6A00;

extern ARQRequest *lbl_801A6A10;

extern ARQRequest *lbl_801A6A14;

extern ARQCallback lbl_801A6A18;

extern ARQCallback lbl_801A6A1C;

void __ARQPopTaskQueueHi(void);

void fn_80020360(void);

static inline void __ARQPopTaskQueueHi(void) {
    if (lbl_801A6A00) {
        if (lbl_801A6A00->type == 0x00) {
            ARStartDMA(lbl_801A6A00->type, lbl_801A6A00->source, lbl_801A6A00->dest,
                       lbl_801A6A00->length);
        } else {
            ARStartDMA(lbl_801A6A00->type, lbl_801A6A00->dest, lbl_801A6A00->source,
                       lbl_801A6A00->length);
        }
        lbl_801A6A18 = lbl_801A6A00->callback;
        lbl_801A6A10 = lbl_801A6A00;
        lbl_801A6A00 = lbl_801A6A00->next;
    }
}

void fn_80020464(void) {
    if (lbl_801A6A18) {
        (*lbl_801A6A18)((u32)lbl_801A6A10);
        lbl_801A6A10 = 0;
        lbl_801A6A18 = 0;
    } else if (lbl_801A6A1C) {
        (*lbl_801A6A1C)((u32)lbl_801A6A14);
        lbl_801A6A14 = 0;
        lbl_801A6A1C = 0;
    }
    __ARQPopTaskQueueHi();
    if (lbl_801A6A10 == 0)
        fn_80020360();
}
