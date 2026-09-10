#include <types.h>
#include <dolphin/dvd.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

typedef struct DVDDriveInfo {
    u16 revisionLevel;
    u16 deviceCode;
    u32 releaseDate;
    u8 padding[24];
} DVDDriveInfo;

typedef void (*DVDLowCallback)(u32 intType);

typedef void (*DVDOptionalCommandChecker)(DVDCommandBlock *block, void (*cb)(u32 intType));

typedef void (*stateFunc)(DVDCommandBlock *block);

BOOL fn_80016524(void *addr, u32 length, u32 offset, DVDLowCallback callback);

BOOL DVDLowSeek(u32 offset, DVDLowCallback callback);

BOOL DVDLowReadDiskID(DVDDiskID *diskID, DVDLowCallback callback);

BOOL DVDLowStopMotor(DVDLowCallback callback);

BOOL DVDLowInquiry(DVDDriveInfo *info, DVDLowCallback callback);

BOOL DVDLowAudioStream(u32 subcmd, u32 length, u32 offset, DVDLowCallback callback);

BOOL DVDLowRequestAudioStatus(u32 subcmd, DVDLowCallback callback);

BOOL DVDLowAudioBufferConfig(BOOL enable, u32 size, DVDLowCallback callback);

vu32 __DIRegs[16] : FZGX_ADDR___DIRegs;

extern stateFunc lbl_801A6904;

extern DVDCommandBlock *executing_801A68C0;

// Hardware or OS state can change asynchronously.
extern volatile BOOL lbl_801A68D4; // fzgx-allow: S2 SDK asynchronous state

extern DVDCommandBlock DummyCommandBlock_8015CE80;

void stateReady();

void fn_80018D1C(u32 intType);

extern DVDOptionalCommandChecker lbl_801A6480;

void stateReady();

void fn_80018D1C(u32 intType);

void stateBusy(DVDCommandBlock *block) {
    DVDCommandBlock *finished;
    lbl_801A6904 = stateBusy;
    switch (block->command) {
    case 5:
        __DIRegs[1] = __DIRegs[1];
        block->currTransferSize = sizeof(DVDDiskID);
        DVDLowReadDiskID(block->addr, fn_80018D1C);
        break;
    case 1:
    case 4:
        if (!block->length) {
            finished = executing_801A68C0;
            executing_801A68C0 = &DummyCommandBlock_8015CE80;
            finished->state = 0;
            if (finished->callback) {
                finished->callback(0, finished);
            }
            stateReady();
        } else {
            __DIRegs[1] = __DIRegs[1];
            block->currTransferSize = block->length - block->transferredSize > 0x80000
                                          ? 0x80000
                                          : block->length - block->transferredSize;
            fn_80016524((void *)((u8 *)block->addr + block->transferredSize),
                        block->currTransferSize, block->offset + block->transferredSize,
                        fn_80018D1C);
        }
        break;
    case 2:
        __DIRegs[1] = __DIRegs[1];
        DVDLowSeek(block->offset, fn_80018D1C);
        break;
    case 3:
        DVDLowStopMotor(fn_80018D1C);
        break;
    case 15:
        DVDLowStopMotor(fn_80018D1C);
        break;
    case 6:
        __DIRegs[1] = __DIRegs[1];
        if (lbl_801A68D4) {
            executing_801A68C0->currTransferSize = 0;
            DVDLowRequestAudioStatus(0, fn_80018D1C);
        } else {
            executing_801A68C0->currTransferSize = 1;
            DVDLowAudioStream(0, block->length, block->offset, fn_80018D1C);
        }
        break;
    case 7:
        __DIRegs[1] = __DIRegs[1];
        DVDLowAudioStream(0x10000, 0, 0, fn_80018D1C);
        break;
    case 8:
        __DIRegs[1] = __DIRegs[1];
        lbl_801A68D4 = 1;
        DVDLowAudioStream(0, 0, 0, fn_80018D1C);
        break;
    case 9:
        __DIRegs[1] = __DIRegs[1];
        DVDLowRequestAudioStatus(0, fn_80018D1C);
        break;
    case 10:
        __DIRegs[1] = __DIRegs[1];
        DVDLowRequestAudioStatus(0x10000, fn_80018D1C);
        break;
    case 11:
        __DIRegs[1] = __DIRegs[1];
        DVDLowRequestAudioStatus(0x20000, fn_80018D1C);
        break;
    case 12:
        __DIRegs[1] = __DIRegs[1];
        DVDLowRequestAudioStatus(0x30000, fn_80018D1C);
        break;
    case 13:
        __DIRegs[1] = __DIRegs[1];
        DVDLowAudioBufferConfig(block->offset, block->length, fn_80018D1C);
        break;
    case 14:
        __DIRegs[1] = __DIRegs[1];
        block->currTransferSize = sizeof(DVDDriveInfo);
        DVDLowInquiry(block->addr, fn_80018D1C);
        break;
    default:
        lbl_801A6480(block, fn_80018D1C);
        break;
    }
}
