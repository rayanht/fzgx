#include <types.h>
#include <dolphin/types.h>

typedef enum _GXBlendMode {
    GX_BM_NONE,
    GX_BM_BLEND,
    GX_BM_LOGIC,
    GX_BM_SUBTRACT,
    GX_MAX_BLENDMODE,
} GXBlendMode;

typedef enum _GXBlendFactor {
    GX_BL_ZERO,
    GX_BL_ONE,
    GX_BL_SRC_COLOR,
    GX_BL_DST_COLOR = 2,
    GX_BL_INV_SRC_COLOR,
    GX_BL_INV_DST_COLOR = 3,
    GX_BL_SRC_ALPHA,
    GX_BL_INV_SRC_ALPHA,
    GX_BL_DST_ALPHA,
    GX_BL_INV_DST_ALPHA,
} GXBlendFactor;

typedef enum _GXLogicOp {
    GX_LO_CLEAR,
    GX_LO_AND,
    GX_LO_REV_AND,
    GX_LO_COPY,
    GX_LO_INV_AND,
    GX_LO_NOOP,
    GX_LO_XOR,
    GX_LO_OR,
    GX_LO_NOR,
    GX_LO_EQUIV,
    GX_LO_INV,
    GX_LO_REV_OR,
    GX_LO_INV_COPY,
    GX_LO_INV_OR,
    GX_LO_NAND,
    GX_LO_SET,
} GXLogicOp;

extern u16 *__peReg;

void GXPokeBlendMode(GXBlendMode mode, GXBlendFactor srcFactor, GXBlendFactor destFactor,
                 GXLogicOp op) {
    u32 reg;
    reg = (*(vu16 *)((vu16 *)(__peReg) + (1)));
    (reg) = (reg & ~(((1 << ((31 - 31 + 1))) - 1) << (31 - (31) - ((31 - 31 + 1)) + 1))) |
            ((int)((mode == GX_BM_BLEND) || (mode == GX_BM_SUBTRACT))
             << (31 - (31) - ((31 - 31 + 1)) + 1));
    (reg) = (reg & ~(((1 << ((20 - 20 + 1))) - 1) << (31 - (20) - ((20 - 20 + 1)) + 1))) |
            ((int)((mode == GX_BM_SUBTRACT)) << (31 - (20) - ((20 - 20 + 1)) + 1));
    (reg) = (reg & ~(((1 << ((30 - 30 + 1))) - 1) << (31 - (30) - ((30 - 30 + 1)) + 1))) |
            ((int)((mode == GX_BM_LOGIC)) << (31 - (30) - ((30 - 30 + 1)) + 1));
    (reg) = (reg & ~(((1 << ((19 - 16 + 1))) - 1) << (31 - (16) - ((19 - 16 + 1)) + 1))) |
            ((int)(op) << (31 - (16) - ((19 - 16 + 1)) + 1));
    (reg) = (reg & ~(((1 << ((23 - 21 + 1))) - 1) << (31 - (21) - ((23 - 21 + 1)) + 1))) |
            ((int)(srcFactor) << (31 - (21) - ((23 - 21 + 1)) + 1));
    (reg) = (reg & ~(((1 << ((26 - 24 + 1))) - 1) << (31 - (24) - ((26 - 24 + 1)) + 1))) |
            ((int)(destFactor) << (31 - (24) - ((26 - 24 + 1)) + 1));
    (reg) = (reg & ~(((1 << ((7 - 0 + 1))) - 1) << (31 - (0) - ((7 - 0 + 1)) + 1))) |
            ((int)(0x41) << (31 - (0) - ((7 - 0 + 1)) + 1));
    (*(vu16 *)((vu16 *)(__peReg) + (1)) = reg);
}
