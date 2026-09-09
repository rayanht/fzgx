#include <dolphin/os.h>
#include <dolphin/dvd.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"
#pragma peephole off

typedef struct DVDDriveInfo {
    u16 revisionLevel;
    u16 deviceCode;
    u32 releaseDate;
    u8 padding[24];
} DVDDriveInfo;

vu16 __OSDeviceCode : FZGX_ADDR___OSDeviceCode;

extern DVDDriveInfo DriveInfo_8015BF00;

void InquiryCallback(s32 result, DVDCommandBlock *block) {
    switch (block->state) {
    case 0:
        __OSDeviceCode = (u16)(0x8000 | DriveInfo_8015BF00.deviceCode);
        break;
    default:
        __OSDeviceCode = 1;
        break;
    }
}
