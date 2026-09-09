#include "types.h"

extern u32 fn_8008AF50(void *);
extern u32 fn_8008AF48(void *);
extern u32 fn_8008AF40(void *);
extern u8 lbl_801A36B8[40];

struct TRKInitializeEventQueue_Queue {
    u8 pad_0[4];
    u32 unk_4;
    u32 unk_8;
    u8 pad_C[0x18];
    u32 unk_24;
};

s32 TRKInitializeEventQueue(void) {
    fn_8008AF50(&lbl_801A36B8);
    fn_8008AF48(&lbl_801A36B8);
    ((struct TRKInitializeEventQueue_Queue *)&lbl_801A36B8)->unk_4 = 0;
    ((struct TRKInitializeEventQueue_Queue *)&lbl_801A36B8)->unk_8 = 0;
    ((struct TRKInitializeEventQueue_Queue *)&lbl_801A36B8)->unk_24 = 0x100;
    fn_8008AF40(&lbl_801A36B8);
    return 0;
}
