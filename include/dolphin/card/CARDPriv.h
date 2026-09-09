#ifndef DOLPHIN_CARD_CARDPRIV_H
#define DOLPHIN_CARD_CARDPRIV_H

#include <dolphin/card.h>
#include <dolphin/dsp.h>
#include <dolphin/dvd.h>
#include <dolphin/os/OSAlarm.h>
#include <dolphin/os/OSThread.h>
#include <dolphin/os/OSRtc.h>

typedef struct CARDDir {
    u8 gameName[4];
    u8 company[2];
    u8 _padding0;
    u8 bannerFormat;
    u8 fileName[32];
    u32 time;
    u32 iconAddr;
    u16 iconFormat;
    u16 iconSpeed;
    u8 permission;
    u8 copyTimes;
    u16 startBlock;
    u16 length;
    u8 _padding1[2];
    u32 commentAddr;
} CARDDir;

typedef struct CARDControl {
    BOOL attached;
    s32 result;
    u16 size;
    u16 pageSize;
    s32 sectorSize;
    u16 cBlock;
    u16 vendorID;
    s32 latency;
    u8 id[12];
    int mountStep;
    int formatStep;
    u32 scramble;
    DSPTaskInfo task;
    void *workArea;
    CARDDir *currentDir;
    u16 *currentFat;
    OSThreadQueue threadQueue;
    u8 cmd[9];
    s32 cmdlen;
    vu32 mode;
    int retry;
    int repeat;
    u32 addr;
    void *buffer;
    s32 xferred;
    u16 freeNo;
    u16 startBlock;
    CARDFileInfo *fileInfo;
    CARDCallback extCallback;
    CARDCallback txCallback;
    CARDCallback exiCallback;
    CARDCallback apiCallback;
    CARDCallback xferCallback;
    CARDCallback eraseCallback;
    CARDCallback unlockCallback;
    OSAlarm alarm;
    u32 cid;
    const DVDDiskID *diskID;
} CARDControl;

typedef struct CARDID {
    u8 serial[32];
    u16 deviceID;
    u16 size;
    u16 encode;
    u8 padding[512 - 32 - 5 * 2];
    u16 checkSum;
    u16 checkSumInv;
} CARDID;

typedef struct DecodeParameters {
    u8 *inputAddr;
    u32 inputLength;
    u32 aramAddr;
    u8 *outputAddr;
} DecodeParameters;

typedef struct CARDDirCheck {
    u8 padding0[64 - 2 * 4];
    u16 padding1;
    s16 checkCode;
    u16 checkSum;
    u16 checkSumInv;
} CARDDirCheck;

s32 __CARDAccess(CARDControl *card, CARDDir *ent);
s32 __CARDAllocBlock(s32 chan, u32 cBlock, CARDCallback callback);
void __CARDCheckSum(void *ptr, int length, u16 *checksum, u16 *checksumInv);
s32 __CARDClearStatus(s32 chan);
BOOL __CARDCompareFileName(CARDDir *ent, const char *fileName);
s32 __CARDEraseSector(s32 chan, u32 addr, CARDCallback callback);
void __CARDExiHandler(s32 chan, OSContext *context);
void __CARDExtHandler(s32 chan, OSContext *context);
s32 __CARDFormatRegionAsync(s32 chan, u16 encode, CARDCallback callback);
s32 __CARDFreeBlock(s32 chan, u16 nBlock, CARDCallback callback);
s32 __CARDGetControlBlock(s32 chan, CARDControl **pcard);
CARDDir *__CARDGetDirBlock(CARDControl *card);
u16 *__CARDGetFatBlock(CARDControl *card);
s32 __CARDGetFileNo(CARDControl *card, const char *fileName, s32 *pfileNo);
s32 __CARDIsPublic(CARDDir *ent);
void __CARDMountCallback(s32 chan, s32 result);
s32 __CARDRead(s32 chan, u32 addr, s32 length, void *dst, CARDCallback callback);
s32 __CARDReadSegment(s32 chan, CARDCallback callback);
s32 __CARDReadStatus(s32 chan, u8 *status);
s32 __CARDSeek(CARDFileInfo *fileInfo, s32 length, s32 offset, CARDControl **pcard);
void __CARDSetDiskID(const DVDDiskID *id);
s32 __CARDStart(s32 chan, CARDCallback txCallback, CARDCallback exiCallback);
s32 __CARDSync(s32 channel);
void __CARDSyncCallback(s32 channel, s32 result);
void __CARDTxHandler(s32 chan, OSContext *context);
void __CARDUnlockedHandler(s32 chan, OSContext *context);
s32 __CARDUpdateDir(s32 chan, CARDCallback callback);
s32 __CARDUpdateFatBlock(s32 chan, u16 *fat, CARDCallback callback);
s32 __CARDVerify(CARDControl *card);
s32 __CARDWrite(s32 chan, u32 addr, s32 length, void *dst, CARDCallback callback);
s32 __CARDWritePage(s32 chan, CARDCallback callback);

#endif
