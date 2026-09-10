#include <types.h>
#include "sdk_addresses.h"

typedef u8 GXBool;

typedef enum _GXTexMapID {
    GX_TEXMAP0,
    GX_TEXMAP1,
    GX_TEXMAP2,
    GX_TEXMAP3,
    GX_TEXMAP4,
    GX_TEXMAP5,
    GX_TEXMAP6,
    GX_TEXMAP7,
    GX_MAX_TEXMAP,
    GX_TEXMAP_NULL = 255,
    GX_TEXMAP_DISABLE,
} GXTexMapID;

typedef enum _GXTexCoordID {
    GX_TEXCOORD0,
    GX_TEXCOORD1,
    GX_TEXCOORD2,
    GX_TEXCOORD3,
    GX_TEXCOORD4,
    GX_TEXCOORD5,
    GX_TEXCOORD6,
    GX_TEXCOORD7,
    GX_MAXCOORD,
    GX_TEXCOORD_NULL = 255,
} GXTexCoordID;

typedef enum _GXAttr {
    GX_VA_PNMTXIDX,
    GX_VA_TEX0MTXIDX,
    GX_VA_TEX1MTXIDX,
    GX_VA_TEX2MTXIDX,
    GX_VA_TEX3MTXIDX,
    GX_VA_TEX4MTXIDX,
    GX_VA_TEX5MTXIDX,
    GX_VA_TEX6MTXIDX,
    GX_VA_TEX7MTXIDX,
    GX_VA_POS,
    GX_VA_NRM,
    GX_VA_CLR0,
    GX_VA_CLR1,
    GX_VA_TEX0,
    GX_VA_TEX1,
    GX_VA_TEX2,
    GX_VA_TEX3,
    GX_VA_TEX4,
    GX_VA_TEX5,
    GX_VA_TEX6,
    GX_VA_TEX7,
    GX_POS_MTX_ARRAY,
    GX_NRM_MTX_ARRAY,
    GX_TEX_MTX_ARRAY,
    GX_LIGHT_ARRAY,
    GX_VA_NBT,
    GX_VA_MAX_ATTR,
    GX_VA_NULL = 255,
} GXAttr;

typedef enum _GXAttrType {
    GX_NONE,
    GX_DIRECT,
    GX_INDEX8,
    GX_INDEX16,
} GXAttrType;

typedef enum _GXTlut {
    GX_TLUT0,
    GX_TLUT1,
    GX_TLUT2,
    GX_TLUT3,
    GX_TLUT4,
    GX_TLUT5,
    GX_TLUT6,
    GX_TLUT7,
    GX_TLUT8,
    GX_TLUT9,
    GX_TLUT10,
    GX_TLUT11,
    GX_TLUT12,
    GX_TLUT13,
    GX_TLUT14,
    GX_TLUT15,
    GX_MAX_TLUT,
    GX_BIGTLUT0 = 0x10,
    GX_BIGTLUT1,
    GX_BIGTLUT2,
    GX_BIGTLUT3,
    GX_MAX_BIGTLUT = 4,
    GX_MAX_TLUT_ALL = GX_MAX_TLUT + GX_MAX_BIGTLUT,
} GXTlut;

typedef enum _GXTexGenType {
    GX_TG_MTX3x4,
    GX_TG_MTX2x4,
    GX_TG_BUMP0,
    GX_TG_BUMP1,
    GX_TG_BUMP2,
    GX_TG_BUMP3,
    GX_TG_BUMP4,
    GX_TG_BUMP5,
    GX_TG_BUMP6,
    GX_TG_BUMP7,
    GX_TG_SRTG,
} GXTexGenType;

typedef enum _GXTexGenSrc {
    GX_TG_POS,
    GX_TG_NRM,
    GX_TG_BINRM,
    GX_TG_TANGENT,
    GX_TG_TEX0,
    GX_TG_TEX1,
    GX_TG_TEX2,
    GX_TG_TEX3,
    GX_TG_TEX4,
    GX_TG_TEX5,
    GX_TG_TEX6,
    GX_TG_TEX7,
    GX_TG_TEXCOORD0,
    GX_TG_TEXCOORD1,
    GX_TG_TEXCOORD2,
    GX_TG_TEXCOORD3,
    GX_TG_TEXCOORD4,
    GX_TG_TEXCOORD5,
    GX_TG_TEXCOORD6,
    GX_TG_COLOR0,
    GX_TG_COLOR1,
} GXTexGenSrc;

typedef enum _GXPerf0 {
    GX_PERF0_VERTICES = 0,
    GX_PERF0_CLIP_VTX = 1,
    GX_PERF0_CLIP_CLKS = 2,
    GX_PERF0_XF_WAIT_IN = 3,
    GX_PERF0_XF_WAIT_OUT = 4,
    GX_PERF0_XF_XFRM_CLKS = 5,
    GX_PERF0_XF_LIT_CLKS = 6,
    GX_PERF0_XF_BOT_CLKS = 7,
    GX_PERF0_XF_REGLD_CLKS = 8,
    GX_PERF0_XF_REGRD_CLKS = 9,
    GX_PERF0_CLIP_RATIO = 10,
    GX_PERF0_TRIANGLES = 11,
    GX_PERF0_TRIANGLES_CULLED = 12,
    GX_PERF0_TRIANGLES_PASSED = 13,
    GX_PERF0_TRIANGLES_SCISSORED = 14,
    GX_PERF0_TRIANGLES_0TEX = 15,
    GX_PERF0_TRIANGLES_1TEX = 16,
    GX_PERF0_TRIANGLES_2TEX = 17,
    GX_PERF0_TRIANGLES_3TEX = 18,
    GX_PERF0_TRIANGLES_4TEX = 19,
    GX_PERF0_TRIANGLES_5TEX = 20,
    GX_PERF0_TRIANGLES_6TEX = 21,
    GX_PERF0_TRIANGLES_7TEX = 22,
    GX_PERF0_TRIANGLES_8TEX = 23,
    GX_PERF0_TRIANGLES_0CLR = 24,
    GX_PERF0_TRIANGLES_1CLR = 25,
    GX_PERF0_TRIANGLES_2CLR = 26,
    GX_PERF0_QUAD_0CVG = 27,
    GX_PERF0_QUAD_NON0CVG = 28,
    GX_PERF0_QUAD_1CVG = 29,
    GX_PERF0_QUAD_2CVG = 30,
    GX_PERF0_QUAD_3CVG = 31,
    GX_PERF0_QUAD_4CVG = 32,
    GX_PERF0_AVG_QUAD_CNT = 33,
    GX_PERF0_CLOCKS = 34,
    GX_PERF0_NONE = 35,
} GXPerf0;

typedef enum _GXPerf1 {
    GX_PERF1_TEXELS = 0,
    GX_PERF1_TX_IDLE = 1,
    GX_PERF1_TX_REGS = 2,
    GX_PERF1_TX_MEMSTALL = 3,
    GX_PERF1_TC_CHECK1_2 = 4,
    GX_PERF1_TC_CHECK3_4 = 5,
    GX_PERF1_TC_CHECK5_6 = 6,
    GX_PERF1_TC_CHECK7_8 = 7,
    GX_PERF1_TC_MISS = 8,
    GX_PERF1_VC_ELEMQ_FULL = 9,
    GX_PERF1_VC_MISSQ_FULL = 10,
    GX_PERF1_VC_MEMREQ_FULL = 11,
    GX_PERF1_VC_STATUS7 = 12,
    GX_PERF1_VC_MISSREP_FULL = 13,
    GX_PERF1_VC_STREAMBUF_LOW = 14,
    GX_PERF1_VC_ALL_STALLS = 15,
    GX_PERF1_VERTICES = 16,
    GX_PERF1_FIFO_REQ = 17,
    GX_PERF1_CALL_REQ = 18,
    GX_PERF1_VC_MISS_REQ = 19,
    GX_PERF1_CP_ALL_REQ = 20,
    GX_PERF1_CLOCKS = 21,
    GX_PERF1_NONE = 22,
} GXPerf1;

typedef struct _GXTexObj {
    u32 texture_filter;
    u32 texture_lod;
    u32 texture_size;
    u32 texture_address;
    u32 user_data;
    u32 texture_format;
    u32 tlut_name;
    u16 texture_time_count;
    u8 texture_tile_type;
    u8 texture_flags;
} GXTexObj;

typedef struct _GXTlutObj {
    u32 format;
    u32 address;
    u32 numEntries;
} GXTlutObj;

typedef struct _GXTexRegion {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u8 unkC;
    u8 unkD;
} GXTexRegion;

typedef struct _GXTlutRegion {
    u32 unk0;
    GXTlutObj tlutObj;
} GXTlutRegion;

typedef GXTexRegion *(*GXTexRegionCallback)(const GXTexObj *t_obj, GXTexMapID id);

typedef GXTlutRegion *(*GXTlutRegionCallback)(u32 idx);

typedef struct _GXData {
    u16 vNumNot;
    u16 bpSentNot;
    u16 vNum;
    u16 vLim;
    u32 cpEnable;
    u32 cpStatus;
    u32 cpClr;
    u32 vcdLo;
    u32 vcdHi;
    u32 vatA[8];
    u32 vatB[8];
    u32 vatC[8];
    u32 lpSize;
    u32 matIdxA;
    u32 matIdxB;
    u32 indexBase[4];
    u32 indexStride[4];
    u32 ambColor[2];
    u32 matColor[2];
    u32 suTs0[8];
    u32 suTs1[8];
    u32 suScis0;
    u32 suScis1;
    u32 tref[8];
    u32 iref;
    u32 bpMask;
    u32 IndTexScale0;
    u32 IndTexScale1;
    u32 tevc[16];
    u32 teva[16];
    u32 tevKsel[8];
    u32 cmode0;
    u32 cmode1;
    u32 zmode;
    u32 peCtrl;
    u32 cpDispSrc;
    u32 cpDispSize;
    u32 cpDispStride;
    u32 cpDisp;
    u32 cpTexSrc;
    u32 cpTexSize;
    u32 cpTexStride;
    u32 cpTex;
    GXBool cpTexZ;
    u32 genMode;
    GXTexRegion TexRegions0[GX_MAX_TEXMAP];
    GXTexRegion TexRegions1[4];
    u32 nextTexRgn;
    u32 nextTexRgnCI;
    GXTlutRegion TlutRegions[GX_MAX_TLUT_ALL];
    GXTexRegionCallback texRegionCallback;
    GXTlutRegionCallback tlutRegionCallback;
    GXAttrType nrmType;
    GXBool hasNrms;
    GXBool hasBiNrms;
    u32 projType;
    f32 projMtx[6];
    f32 vpLeft;
    f32 vpTop;
    f32 vpWd;
    f32 vpHt;
    f32 vpNearz;
    f32 vpFarz;
    f32 zOffset;
    f32 zScale;
    u32 tImage0[8];
    u32 tMode0[8];
    u32 texmapId[16];
    u32 tcsManEnab;
    u32 tevTcEnab;
    GXPerf0 perf0;
    GXPerf1 perf1;
    u32 perfSel;
    GXBool inDispList;
    GXBool dlSaveContext;
    u8 dirtyVAT;
    u32 dirtyState;
} GXData;

typedef union {
    u8 u8;
    u16 u16;
    u32 u32;
    u64 u64;
    s8 s8;
    s16 s16;
    s32 s32;
    s64 s64;
    f32 f32;
    f64 f64;
} PPCWGPipe;

extern GXData *const gx;

void fn_80039088(GXAttr index);

// Hardware or OS state can change asynchronously.
volatile PPCWGPipe
    GXFIFO : FZGX_ADDR_GXFIFO; // fzgx-allow: S2 SDK asynchronous state

void fn_80033A7C(GXTexCoordID dst_coord, GXTexGenType func, GXTexGenSrc src_param, u32 mtx,
                 GXBool normalize, u32 pt_texmtx) {
    u32 reg = 0;
    u32 row;
    u32 bumprow;
    u32 form;
    GXAttr mtxIdAttr;
    form = 0;
    row = 5;
    switch (src_param) {
    case GX_TG_POS:
        row = 0;
        form = 1;
        break;
    case GX_TG_NRM:
        row = 1;
        form = 1;
        break;
    case GX_TG_BINRM:
        row = 3;
        form = 1;
        break;
    case GX_TG_TANGENT:
        row = 4;
        form = 1;
        break;
    case GX_TG_COLOR0:
        row = 2;
        break;
    case GX_TG_COLOR1:
        row = 2;
        break;
    case GX_TG_TEX0:
        row = 5;
        break;
    case GX_TG_TEX1:
        row = 6;
        break;
    case GX_TG_TEX2:
        row = 7;
        break;
    case GX_TG_TEX3:
        row = 8;
        break;
    case GX_TG_TEX4:
        row = 9;
        break;
    case GX_TG_TEX5:
        row = 10;
        break;
    case GX_TG_TEX6:
        row = 11;
        break;
    case GX_TG_TEX7:
        row = 12;
        break;
    case GX_TG_TEXCOORD0:
        bumprow;
        break;
    case GX_TG_TEXCOORD1:
        bumprow;
        break;
    case GX_TG_TEXCOORD2:
        bumprow;
        break;
    case GX_TG_TEXCOORD3:
        bumprow;
        break;
    case GX_TG_TEXCOORD4:
        bumprow;
        break;
    case GX_TG_TEXCOORD5:
        bumprow;
        break;
    case GX_TG_TEXCOORD6:
        bumprow;
        break;
    default:
        break;
    }
    switch (func) {
    case GX_TG_MTX2x4:
        (reg) = ((u32)(reg) & ~(((1 << (1)) - 1) << (1))) | ((u32)(0) << (1));
        ;
        (reg) = ((u32)(reg) & ~(((1 << (1)) - 1) << (2))) | ((u32)(form) << (2));
        ;
        (reg) = ((u32)(reg) & ~(((1 << (3)) - 1) << (4))) | ((u32)(0) << (4));
        ;
        (reg) = ((u32)(reg) & ~(((1 << (5)) - 1) << (7))) | ((u32)(row) << (7));
        ;
        break;
    case GX_TG_MTX3x4:
        (reg) = ((u32)(reg) & ~(((1 << (1)) - 1) << (1))) | ((u32)(1) << (1));
        ;
        (reg) = ((u32)(reg) & ~(((1 << (1)) - 1) << (2))) | ((u32)(form) << (2));
        ;
        (reg) = ((u32)(reg) & ~(((1 << (3)) - 1) << (4))) | ((u32)(0) << (4));
        ;
        (reg) = ((u32)(reg) & ~(((1 << (5)) - 1) << (7))) | ((u32)(row) << (7));
        ;
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        (reg) = ((u32)(reg) & ~(((1 << (1)) - 1) << (1))) | ((u32)(0) << (1));
        ;
        (reg) = ((u32)(reg) & ~(((1 << (1)) - 1) << (2))) | ((u32)(form) << (2));
        ;
        (reg) = ((u32)(reg) & ~(((1 << (3)) - 1) << (4))) | ((u32)(1) << (4));
        ;
        (reg) = ((u32)(reg) & ~(((1 << (5)) - 1) << (7))) | ((u32)(row) << (7));
        ;
        (reg) = ((u32)(reg) & ~(((1 << (3)) - 1) << (12))) | ((u32)(src_param - 12) << (12));
        ;
        (reg) = ((u32)(reg) & ~(((1 << (3)) - 1) << (15))) | ((u32)(func - 2) << (15));
        ;
        break;
    case GX_TG_SRTG:
        (reg) = ((u32)(reg) & ~(((1 << (1)) - 1) << (1))) | ((u32)(0) << (1));
        ;
        (reg) = ((u32)(reg) & ~(((1 << (1)) - 1) << (2))) | ((u32)(form) << (2));
        ;
        if (src_param == GX_TG_COLOR0) {
            (reg) = ((u32)(reg) & ~(((1 << (3)) - 1) << (4))) | ((u32)(2) << (4));
            ;
        } else {
            (reg) = ((u32)(reg) & ~(((1 << (3)) - 1) << (4))) | ((u32)(3) << (4));
            ;
        }
        (reg) = ((u32)(reg) & ~(((1 << (5)) - 1) << (7))) | ((u32)(2) << (7));
        ;
        break;
    default:
        break;
    }
    do {
        GXFIFO.u8 = (u8)(0x10);
        GXFIFO.u32 = (u32)(0x1000 + (dst_coord + 0x40));
        GXFIFO.u32 = (u32)(reg);
        ;
    } while (0);
    reg = 0;
    (reg) = ((u32)(reg) & ~(((1 << (6)) - 1) << (0))) | ((u32)(pt_texmtx - 64) << (0));
    ;
    (reg) = ((u32)(reg) & ~(((1 << (1)) - 1) << (8))) | ((u32)(normalize) << (8));
    ;
    do {
        GXFIFO.u8 = (u8)(0x10);
        GXFIFO.u32 = (u32)(0x1000 + (dst_coord + 0x50));
        GXFIFO.u32 = (u32)(reg);
        ;
    } while (0);
    switch (dst_coord) {
    case GX_TEXCOORD0:
        (gx->matIdxA) = ((u32)(gx->matIdxA) & ~(((1 << (6)) - 1) << (6))) | ((u32)(mtx) << (6));
        ;
        break;
    case GX_TEXCOORD1:
        (gx->matIdxA) = ((u32)(gx->matIdxA) & ~(((1 << (6)) - 1) << (12))) | ((u32)(mtx) << (12));
        ;
        break;
    case GX_TEXCOORD2:
        (gx->matIdxA) = ((u32)(gx->matIdxA) & ~(((1 << (6)) - 1) << (18))) | ((u32)(mtx) << (18));
        ;
        break;
    case GX_TEXCOORD3:
        (gx->matIdxA) = ((u32)(gx->matIdxA) & ~(((1 << (6)) - 1) << (24))) | ((u32)(mtx) << (24));
        ;
        break;
    case GX_TEXCOORD4:
        (gx->matIdxB) = ((u32)(gx->matIdxB) & ~(((1 << (6)) - 1) << (0))) | ((u32)(mtx) << (0));
        ;
        break;
    case GX_TEXCOORD5:
        (gx->matIdxB) = ((u32)(gx->matIdxB) & ~(((1 << (6)) - 1) << (6))) | ((u32)(mtx) << (6));
        ;
        break;
    case GX_TEXCOORD6:
        (gx->matIdxB) = ((u32)(gx->matIdxB) & ~(((1 << (6)) - 1) << (12))) | ((u32)(mtx) << (12));
        ;
        break;
    default:
        (gx->matIdxB) = ((u32)(gx->matIdxB) & ~(((1 << (6)) - 1) << (18))) | ((u32)(mtx) << (18));
        ;
        break;
    }
    mtxIdAttr = dst_coord + 1;
    fn_80039088(mtxIdAttr);
}
