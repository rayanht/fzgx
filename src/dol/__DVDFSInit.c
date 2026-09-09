#include "types.h"

extern u32 BootInfo_801A68A0;
extern u32 FstStart_801A68A4;
extern u32 FstStringStart_801A68A8;
extern u32 MaxEntryNum_801A68AC;

void __DVDFSInit(void) {
    BootInfo_801A68A0 = 0x80000000; /* fzgx-allow: A1,A2 unnamed OS memory */
    FstStart_801A68A4 = *(u32 *)0x80000038; /* fzgx-allow: A1,A2 unnamed OS memory */
    if (FstStart_801A68A4 == 0) {
        return;
    }
    MaxEntryNum_801A68AC = *(u32 *)(FstStart_801A68A4 + 0x8);
    FstStringStart_801A68A8 = FstStart_801A68A4 + MaxEntryNum_801A68AC * 0xc;
}
