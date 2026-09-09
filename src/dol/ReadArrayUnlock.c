#include "types.h"
#include "dol/globals.h"

extern s32 EXISelect(s32 chan, s32 dev, s32 freq);
extern s32 EXIImmEx(s32 chan, void *buf, s32 len, s32 type);
extern s32 EXIDeselect(s32 chan);

s32 ReadArrayUnlock(s32 chan, u32 address, void *buffer, s32 length, s32 use_full_address) {
    u8 command[5];
    s32 failed;
    Obj_80177960 *work;

    work = (Obj_80177960 *)((u8 *)&lbl_80177960 + chan * 0x110);
    if (!EXISelect(chan, 0, 4)) {
        return -3;
    }

    address &= ~0xfff;
    memset(command, 0, 5);
    command[0] = 0x52;
    if (!use_full_address) {
        command[1] = (address >> 29) & 3;
        command[2] = (address >> 21) & 0xff;
        command[3] = (address >> 19) & 3;
        command[4] = (address >> 12) & 0x7f;
    } else {
        command[1] = address >> 24;
        command[2] = address >> 16;
    }

    failed = !EXIImmEx(chan, command, 5, 1);
    failed |= !EXIImmEx(chan, (u8 *)work->unk_80 + 0x200, work->unk_14, 1);
    failed |= !EXIImmEx(chan, buffer, length, 0);
    failed |= !EXIDeselect(chan);

    if (failed) {
        return -3;
    }
    return 0;
}
