#include <types.h>
#include <dolphin/dvd.h>

typedef struct DVDBB2 {
    u32 bootFilePosition;
    u32 FSTPosition;
    u32 FSTLength;
    u32 FSTMaxLength;
    void *FSTAddress;
    u32 userPosition;
    u32 userLength;
    u32 padding0;
} DVDBB2;

void DVDReset();

BOOL DVDReadDiskID(DVDCommandBlock *block, DVDDiskID *diskID, DVDCBCallback callback);

BOOL fn_80019430(DVDCommandBlock *block, void *addr, s32 length, s32 offset,
                 DVDCBCallback callback);

extern s32 lbl_801A6910;

extern DVDBB2 *bb2_801A6914;

extern DVDDiskID *idTmp_801A6918;

void cb(s32 result, DVDCommandBlock *block) {
    if (result > 0) {
        switch (lbl_801A6910) {
        case 0:
            lbl_801A6910 = 1;
            fn_80019430(block, bb2_801A6914, ((((u32)sizeof(bb2_801A6914) + 31) & ~31)), 0x420, cb);
            break;
        case 1:
            lbl_801A6910 = 2;
            fn_80019430(block, bb2_801A6914->FSTAddress,
                        ((((u32)bb2_801A6914->FSTLength + 31) & ~31)), bb2_801A6914->FSTPosition,
                        cb);
        }
    } else if (result == -1) {
    } else if (result == -4) {
        lbl_801A6910 = 0;
        DVDReset();
        DVDReadDiskID(block, idTmp_801A6918, cb);
    }
}
