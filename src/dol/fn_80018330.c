#include "types.h"

extern void __DVDStoreErrorCode(s32 error);
extern void DVDReset(void);
extern void cbForStateError(s32 state);
extern void fn_80017838(void);
extern void fn_800178CC(void);
extern void fn_80016524(u32, u32, u32, u32);
extern void fn_80017B14(void);
extern void fn_800169AC(void (*callback)(void));
extern void OSPanic(const char *, ...);

extern u32 lbl_801A6904;
extern u32 lbl_801A68F4;
extern char lbl_80123FE4[52];
extern char lbl_801A6484[6];

typedef struct ExecutingState {
    u8 _pad[0xc];
    s32 error;
} ExecutingState;

typedef struct BootInfo {
    u8 _pad38[0x38];
    u32 field38;
    u32 field3c;
} BootInfo;

extern ExecutingState *executing_801A68C0;
extern BootInfo *bootInfo_801A68C8;
extern u32 BB2_8015CE40[];

void fn_80018330(u32 state) {
    if (state == 0x10) {
        executing_801A68C0->error = -1;
        __DVDStoreErrorCode(0x01234568);
        DVDReset();
        cbForStateError(0);
    } else if (state & 1) {
        lbl_801A68F4 = 0;
        lbl_801A6904 = (u32)fn_80017838;
        if (bootInfo_801A68C8->field3c < BB2_8015CE40[2]) {
            OSPanic(lbl_801A6484, 0x287, lbl_80123FE4);
        }
        fn_80016524(bootInfo_801A68C8->field38,
                    (BB2_8015CE40[2] + 0x1f) & ~0x1f,
                    BB2_8015CE40[1],
                    (u32)fn_800178CC);
    } else {
        fn_800169AC(fn_80017B14);
    }
}
