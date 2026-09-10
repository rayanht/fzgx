
#include "types.h"

typedef enum {
    VI_TVMODE_NTSC_INT = ((((0)) << 2) + ((0))),
    VI_TVMODE_NTSC_DS = ((((0)) << 2) + ((1))),
    VI_TVMODE_NTSC_PROG = ((((0)) << 2) + ((2))),
    VI_TVMODE_NTSC_3D = ((((0)) << 2) + ((3))),
    VI_TVMODE_PAL_INT = ((((1)) << 2) + ((0))),
    VI_TVMODE_PAL_DS = ((((1)) << 2) + ((1))),
    VI_TVMODE_MPAL_INT = ((((2)) << 2) + ((0))),
    VI_TVMODE_MPAL_DS = ((((2)) << 2) + ((1))),
    VI_TVMODE_DEBUG_INT = ((((3)) << 2) + ((0))),
    VI_TVMODE_DEBUG_PAL_INT = ((((4)) << 2) + ((0))),
    VI_TVMODE_DEBUG_PAL_DS = ((((4)) << 2) + ((1))),
    VI_TVMODE_EURGB60_INT = ((((5)) << 2) + ((0))),
    VI_TVMODE_EURGB60_DS = ((((5)) << 2) + ((1))),
    VI_TVMODE_GCA_INT = ((((6)) << 2) + ((0))),
    VI_TVMODE_GCA_DS = ((((6)) << 2) + ((1))),
    VI_TVMODE_GCA_PROG = ((((6)) << 2) + ((2))),
} VITVMode;

typedef enum {
    VI_XFBMODE_SF = 0,
    VI_XFBMODE_DF = 1,
} VIXFBMode;

typedef struct _GXRenderModeObj {
    VITVMode viTVmode;
    u16 fbWidth;
    u16 efbHeight;
    u16 xfbHeight;
    u16 viXOrigin;
    u16 viYOrigin;
    u16 viWidth;
    u16 viHeight;
    VIXFBMode xFBmode;
    u8 field_rendering;
    u8 aa;
    u8 sample_pattern[12][2];
    u8 vfilter[7];
} GXRenderModeObj;

void fn_8003493C(GXRenderModeObj *rmin, GXRenderModeObj *rmout, u16 hor, u16 ver) {
    unsigned short hor2 = hor * 2;
    unsigned short ver2 = ver * 2;
    unsigned long verf;
    if (rmin != rmout) {
        *rmout = *rmin;
    }
    rmout->fbWidth = rmin->fbWidth - hor2;
    verf = (ver2 * rmin->efbHeight) / (u32)rmin->xfbHeight;
    rmout->efbHeight = rmin->efbHeight - verf;
    if (rmin->xFBmode == VI_XFBMODE_SF && (rmin->viTVmode & 2) != 2) {
        rmout->xfbHeight = rmin->xfbHeight - ver;
    } else {
        rmout->xfbHeight = rmin->xfbHeight - ver2;
    }
    rmout->viWidth = rmin->viWidth - hor2;
    rmout->viHeight = rmin->viHeight - ver2;
    rmout->viXOrigin = rmin->viXOrigin + hor;
    rmout->viYOrigin = rmin->viYOrigin + ver;
}
