#include "types.h"

typedef struct InitData {
    u32 unk0;
    u32 unk4;
    u32 unk8;
} InitData;

extern void fn_80088764(InitData *data, int value);
extern u32 lbl_801A5098[6];
extern void TRKPostEvent(InitData *data);

void fn_8008944C(u32 value) {

{
    InitData data;
    fn_80088764(&data, 2);
    data.unk8 = value;
    lbl_801A5098[0] = (u32)-1;
    TRKPostEvent(&data);
}
}
