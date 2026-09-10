#include "types.h"

typedef struct TRKBuffer TRKBuffer;
struct TRKBuffer {
    u32 mutex;
    u32 isInUse;
    u32 length;
    u32 position;
    u8 data[(0x800 + 0x80)];
};

extern s32 fn_80089144(TRKBuffer *, u32);
extern void MWTRACE(u32, ...);
extern char lbl_80095850[];
extern char lbl_8009586C[];
extern s32 fn_8008A6E4(TRKBuffer *);
extern s32 fn_8008A66C(TRKBuffer *);
extern s32 fn_8008A614(TRKBuffer *);
extern s32 fn_8008A5BC(TRKBuffer *);
extern s32 fn_8008A5B4(TRKBuffer *);
extern s32 fn_8008A5AC(TRKBuffer *);
extern s32 fn_8008A3C0(TRKBuffer *);
extern s32 fn_8008A1CC(TRKBuffer *);
extern s32 fn_80089EEC(TRKBuffer *);
extern s32 fn_80089C5C(TRKBuffer *);
extern s32 fn_80089BAC(TRKBuffer *);
extern s32 fn_8008998C(TRKBuffer *);
extern s32 fn_800898E4(TRKBuffer *);
extern s32 fn_8008983C(TRKBuffer *);

s32 TRKDispatchMessage(TRKBuffer * arg0) {
    s32 result = 0x500;

    fn_80089144(arg0, 0);
    MWTRACE(1, lbl_80095850, arg0->data[4]);
    switch (arg0->data[4]) {
    case 26:
        result = fn_8008A6E4(arg0);
        break;
    case 12:
        result = fn_8008A66C(arg0);
        break;
    case 11:
        result = fn_8008A614(arg0);
        break;
    case 10:
        result = fn_8008A5BC(arg0);
        break;
    case 9:
        result = fn_8008A5B4(arg0);
        break;
    case 8:
        result = fn_8008A5AC(arg0);
        break;
    case 7:
        result = fn_8008A3C0(arg0);
        break;
    case 6:
        result = fn_8008A1CC(arg0);
        break;
    case 5:
        result = fn_80089EEC(arg0);
        break;
    case 4:
        result = fn_80089C5C(arg0);
        break;
    case 3:
        result = fn_80089BAC(arg0);
        break;
    case 2:
        result = fn_8008998C(arg0);
        break;
    case 1:
        result = fn_800898E4(arg0);
        break;
    case 0:
        result = fn_8008983C(arg0);
        break;
    }
    MWTRACE(1, lbl_8009586C, result);
    return result;
}
