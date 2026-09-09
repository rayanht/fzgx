#include "types.h"

extern u32 lbl_801A6C80;

void fn_8006A1F8(void) {
    u32 i;

    *(u8 *)((u8 *)lbl_801A6C80 + 0x5a08) = 0x7f;
    *(u32 *)((u8 *)lbl_801A6C80 + 0x5a0c) = 1;

    for (i = 0; i < 0x100; i += 0x80) {
        *(u8 *)((u8 *)lbl_801A6C80 + i + 0x496) = 0x7f;
        *(u8 *)((u8 *)lbl_801A6C80 + i + 0x497) = 0x40;
        *(u8 *)((u8 *)lbl_801A6C80 + i + 0x4a6) = 0x7f;
        *(u8 *)((u8 *)lbl_801A6C80 + i + 0x4a7) = 0x40;
        *(u8 *)((u8 *)lbl_801A6C80 + i + 0x4b6) = 0x7f;
        *(u8 *)((u8 *)lbl_801A6C80 + i + 0x4b7) = 0x40;
        *(u8 *)((u8 *)lbl_801A6C80 + i + 0x4c6) = 0x7f;
        *(u8 *)((u8 *)lbl_801A6C80 + i + 0x4c7) = 0x40;
        *(u8 *)((u8 *)lbl_801A6C80 + i + 0x4d6) = 0x7f;
        *(u8 *)((u8 *)lbl_801A6C80 + i + 0x4d7) = 0x40;
        *(u8 *)((u8 *)lbl_801A6C80 + i + 0x4e6) = 0x7f;
        *(u8 *)((u8 *)lbl_801A6C80 + i + 0x4e7) = 0x40;
        *(u8 *)((u8 *)lbl_801A6C80 + i + 0x4f6) = 0x7f;
        *(u8 *)((u8 *)lbl_801A6C80 + i + 0x4f7) = 0x40;
        *(u8 *)((u8 *)lbl_801A6C80 + i + 0x506) = 0x7f;
        *(u8 *)((u8 *)lbl_801A6C80 + i + 0x507) = 0x40;
    }

    for (i = 0; i < 0x4600; i += 0x8c0) {
        *(u32 *)((u8 *)lbl_801A6C80 + i + 0x1430) = 0;
        *(u8 *)((u8 *)lbl_801A6C80 + i + 0x1413) = 0xff;
        *(u32 *)((u8 *)lbl_801A6C80 + i + 0x1548) = 0;
        *(u8 *)((u8 *)lbl_801A6C80 + i + 0x152b) = 0xff;
        *(u32 *)((u8 *)lbl_801A6C80 + i + 0x1660) = 0;
        *(u8 *)((u8 *)lbl_801A6C80 + i + 0x1643) = 0xff;
        *(u32 *)((u8 *)lbl_801A6C80 + i + 0x1778) = 0;
        *(u8 *)((u8 *)lbl_801A6C80 + i + 0x175b) = 0xff;
        *(u32 *)((u8 *)lbl_801A6C80 + i + 0x1890) = 0;
        *(u8 *)((u8 *)lbl_801A6C80 + i + 0x1873) = 0xff;
        *(u32 *)((u8 *)lbl_801A6C80 + i + 0x19a8) = 0;
        *(u8 *)((u8 *)lbl_801A6C80 + i + 0x198b) = 0xff;
        *(u32 *)((u8 *)lbl_801A6C80 + i + 0x1ac0) = 0;
        *(u8 *)((u8 *)lbl_801A6C80 + i + 0x1aa3) = 0xff;
        *(u32 *)((u8 *)lbl_801A6C80 + i + 0x1bd8) = 0;
        *(u8 *)((u8 *)lbl_801A6C80 + i + 0x1bbb) = 0xff;
    }
}
