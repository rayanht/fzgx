#include "types.h"

typedef void *(*Fn8003D918_Alloc)(u32 size);
typedef void (*Fn8003D918_Free)(void *ptr);

typedef struct Fn8003D918_Buffer {
    void *data;
    u32 unk_4;
    u8 pad_8[0x8];
} Fn8003D918_Buffer;

typedef struct Fn8003D918_Slot {
    u32 unk_0;
    u8 pad_4[0x4];
    s32 unk_8;
    u8 pad_C[0x4];
} Fn8003D918_Slot;

extern const char *lbl_801A6580;
extern Fn8003D918_Alloc lbl_801A6C34;
extern Fn8003D918_Free lbl_801A6C38;
extern u32 lbl_801A6C58;
extern u32 lbl_801A6C54;
extern u32 lbl_801A6C50;
extern Fn8003D918_Buffer *lbl_801A6C4C;
extern Fn8003D918_Slot *lbl_801A6C48;
extern void OSRegisterVersion(const char *);
extern void fn_8003E9EC(u32);
extern void fn_8003D698(void);
extern void fn_80034378(void (*)(void));
extern void fn_80039B38(void);

u32 fn_8003D918(u32 buffer_size, u32 buffer_count, u32 slot_count, Fn8003D918_Alloc alloc,
                Fn8003D918_Free free, u32 arg5) {
    u32 total;
    u32 i;

    OSRegisterVersion(lbl_801A6580);
    lbl_801A6C34 = alloc;
    lbl_801A6C38 = free;
    lbl_801A6C58 = buffer_count;
    lbl_801A6C54 = slot_count;
    lbl_801A6C50 = buffer_size;
    total = buffer_count * sizeof(Fn8003D918_Buffer);
    total += buffer_count * (buffer_size * 0xB0);
    total += slot_count * sizeof(Fn8003D918_Slot);
    lbl_801A6C4C = alloc(buffer_count * sizeof(Fn8003D918_Buffer));
    for (i = 0; i < lbl_801A6C58; i++) {
        lbl_801A6C4C[i].data = lbl_801A6C34(buffer_size * 0xB0);
        lbl_801A6C4C[i].unk_4 = 0;
    }
    lbl_801A6C48 = lbl_801A6C34(slot_count * sizeof(Fn8003D918_Slot));
    for (i = 0; i < slot_count; i++) {
        lbl_801A6C48[i].unk_0 = 0;
        lbl_801A6C48[i].unk_8 = -1;
    }
    fn_8003E9EC(arg5);
    fn_80034378(fn_8003D698);
    fn_80039B38();
    return total;
}
