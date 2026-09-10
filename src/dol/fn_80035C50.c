
#include "types.h"

typedef enum _GXTexFmt {
    GX_TF_I4 = 0x0,
    GX_TF_I8 = 0x1,
    GX_TF_IA4 = 0x2,
    GX_TF_IA8 = 0x3,
    GX_TF_RGB565 = 0x4,
    GX_TF_RGB5A3 = 0x5,
    GX_TF_RGBA8 = 0x6,
    GX_TF_CMPR = 0xE,
    GX_CTF_R4 = 0x0 | 0x20,
    GX_CTF_RA4 = 0x2 | 0x20,
    GX_CTF_RA8 = 0x3 | 0x20,
    GX_CTF_YUVA8 = 0x6 | 0x20,
    GX_CTF_A8 = 0x7 | 0x20,
    GX_CTF_R8 = 0x8 | 0x20,
    GX_CTF_G8 = 0x9 | 0x20,
    GX_CTF_B8 = 0xA | 0x20,
    GX_CTF_RG8 = 0xB | 0x20,
    GX_CTF_GB8 = 0xC | 0x20,
    GX_TF_Z8 = 0x1 | 0x10,
    GX_TF_Z16 = 0x3 | 0x10,
    GX_TF_Z24X8 = 0x6 | 0x10,
    GX_CTF_Z4 = 0x0 | 0x10 | 0x20,
    GX_CTF_Z8M = 0x9 | 0x10 | 0x20,
    GX_CTF_Z8L = 0xA | 0x10 | 0x20,
    GX_CTF_Z16L = 0xC | 0x10 | 0x20,
    GX_TF_A8 = GX_CTF_A8,
} GXTexFmt;

typedef enum _GXTexWrapMode {
    GX_CLAMP,
    GX_REPEAT,
    GX_MIRROR,
    GX_MAX_TEXWRAPMODE,
} GXTexWrapMode;

typedef struct _GXTexObj {
    u32 dummy[8];
} GXTexObj;

typedef struct __GXTexObjInt_struct {
    u32 mode0;
    u32 mode1;
    u32 image0;
    u32 image3;
    void *userData;
    GXTexFmt fmt;
    u32 tlutName;
    u16 loadCnt;
    u8 loadFmt;
    u8 flags;
} __GXTexObjInt;

void (*DVDLowClearCallback())(u32);

void fn_80035C50(GXTexObj *obj, void *image_ptr, u16 width, u16 height, GXTexFmt format,
                 GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, u8 mipmap) {
    u32 imageBase;
    u32 maxLOD;
    u16 rowT;
    u16 colT;
    u32 rowC;
    u32 colC;
    __GXTexObjInt *t = (__GXTexObjInt *)obj;
    memset(t, 0, 0x20);
    do {
        (t->mode0) = ((u32)(t->mode0) & ~(((1 << (2)) - 1) << (0))) | ((u32)(wrap_s) << (0));
    } while (0);
    do {
        (t->mode0) = ((u32)(t->mode0) & ~(((1 << (2)) - 1) << (2))) | ((u32)(wrap_t) << (2));
    } while (0);
    do {
        (t->mode0) = ((u32)(t->mode0) & ~(((1 << (1)) - 1) << (4))) | ((u32)(1) << (4));
    } while (0);
    if (mipmap != 0) {
        u8 lmax;
        t->flags |= 1;
        if ((u32)format - 8 <= 2)
            t->mode0 = (t->mode0 & 0xFFFFFF1F) | 0xA0;
        else
            t->mode0 = (t->mode0 & 0xFFFFFF1F) | 0xC0;
        if (width > height) {
            maxLOD = 31 - __cntlzw(width);
        } else {
            maxLOD = 31 - __cntlzw(height);
        }
        lmax = 16.0f * maxLOD;
        do {
            (t->mode1) = ((u32)(t->mode1) & ~(((1 << (8)) - 1) << (8))) | ((u32)(lmax) << (8));
        } while (0);
    } else {
        t->mode0 = (t->mode0 & 0xFFFFFF1F) | 0x80;
    }
    t->fmt = format;
    do {
        (t->image0) = ((u32)(t->image0) & ~(((1 << (10)) - 1) << (0))) | ((u32)(width - 1) << (0));
    } while (0);
    do {
        (t->image0) =
            ((u32)(t->image0) & ~(((1 << (10)) - 1) << (10))) | ((u32)(height - 1) << (10));
    } while (0);
    do {
        (t->image0) =
            ((u32)(t->image0) & ~(((1 << (4)) - 1) << (20))) | ((u32)(format & 0xF) << (20));
    } while (0);
    imageBase = (u32)((u32)image_ptr >> 5) & 0x01FFFFFF;
    do {
        (t->image3) = ((u32)(t->image3) & ~(((1 << (21)) - 1) << (0))) | ((u32)(imageBase) << (0));
    } while (0);
    switch (format & 0xF) {
    case 0:
    case 8:
        t->loadFmt = 1;
        rowT = 3;
        colT = 3;
        break;
    case 1:
    case 2:
    case 9:
        t->loadFmt = 2;
        rowT = 3;
        colT = 2;
        break;
    case 3:
    case 4:
    case 5:
    case 10:
        t->loadFmt = 2;
        rowT = 2;
        colT = 2;
        break;
    case 6:
        t->loadFmt = 3;
        rowT = 2;
        colT = 2;
        break;
    case 14:
        t->loadFmt = 0;
        rowT = 3;
        colT = 3;
        break;
    default:
        t->loadFmt = 2;
        rowT = 2;
        colT = 2;
        break;
    }
    rowC = (width + (1 << rowT) - 1) >> rowT;
    colC = (height + (1 << colT) - 1) >> colT;
    t->loadCnt = (rowC * colC) & 0x7FFF;
    t->flags |= 2;
}
