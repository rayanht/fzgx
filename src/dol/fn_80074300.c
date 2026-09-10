#include "types.h"
#include "dol/globals.h"

typedef struct {
    u8 pad[0xb08];
    u16 unk_b08;
    u16 unk_b0a;
    u16 unk_b0c;
    u16 unk_b0e;
} Fn80074300State;

extern void GXSetTexCopySrc(u16, u16, u16, u16);

void fn_80074300(u16 arg0, u16 arg1, u16 arg2, u16 arg3, u32 lab_unused0) {
    if (((Fn80074300State *)lbl_801A6D38)->unk_b08 != arg0 ||
        ((Fn80074300State *)lbl_801A6D38)->unk_b0a != arg1 ||
        ((Fn80074300State *)lbl_801A6D38)->unk_b0c != arg2 ||
        ((Fn80074300State *)lbl_801A6D38)->unk_b0e != arg3) {
        GXSetTexCopySrc(arg0, arg1, arg2, arg3);
        ((Fn80074300State *)lbl_801A6D38)->unk_b08 = arg0;
        ((Fn80074300State *)lbl_801A6D38)->unk_b0a = arg1;
        ((Fn80074300State *)lbl_801A6D38)->unk_b0c = arg2;
        ((Fn80074300State *)lbl_801A6D38)->unk_b0e = arg3;
    }
}
