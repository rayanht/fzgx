#include "types.h"
#include "dolphin/os/OSTime.h"

typedef u32 (*fn_80021930_Fn0)(void);

typedef struct fn_80021930_State {
    u8 pad_0[0x47D0];
    OSTime unk_47D0;
    OSTime unk_47D8;
    OSTime unk_47E0;
    OSTime unk_47E8;
    OSTime unk_47F0;
    OSTime unk_47F8;
    u32 unk_4800;
} fn_80021930_State;

extern u8 lbl_80160500[];
extern u32 lbl_801A6B10;
extern u32 lbl_801A6B20;

extern OSTime OSGetTime(void);
extern u32 DSPCheckMailToDSP(void);
extern void DSPSendMailToDSP(u32);
extern void AIInitDMA(u32, u32);
extern u32 fn_80022BF4(u32);
extern u32 fn_80022028(void);
extern u8 * fn_80021200(void);
extern void fn_80020800(void);
extern u32 fn_80020FA4(void);
extern u32 fn_8002123C(u32, u32);
extern u32 fn_800224E4(void);
extern u32 fn_800235D4(void);

void fn_80021930(u32 arg0, u32 arg1) {
    fn_80021930_State *p;
    u8 *ptr;
    u8 *dst;
    u32 v;
    u32 i;

    p = (fn_80021930_State *)lbl_80160500;
    p->unk_47D0 = OSGetTime();
    fn_80022BF4(arg0);
    fn_80022028();
    ptr = fn_80021200();
    DSPSendMailToDSP(0xBABE0180);
    while (DSPCheckMailToDSP())
        ;
    DSPSendMailToDSP((u32)ptr);
    while (DSPCheckMailToDSP())
        ;
    fn_80020800();
    p->unk_47D8 = OSGetTime();
    fn_80020FA4();
    p->unk_47E0 = OSGetTime();
    p->unk_47E8 = OSGetTime();
    if (lbl_801A6B20 != 0) {
        ((fn_80021930_Fn0)lbl_801A6B20)();
    }
    p->unk_47F0 = OSGetTime();
    fn_8002123C((u32)((u8 *)p + 0x500), (u32)((u8 *)p + lbl_801A6B10 * 640));
    v = lbl_801A6B10;
    lbl_801A6B10 = v + 1;
    lbl_801A6B10 &= 1;
    AIInitDMA((u32)((u8 *)p + lbl_801A6B10 * 640), 640);
    p->unk_47F8 = OSGetTime();
    p->unk_4800 = fn_800224E4();
    dst = (u8 *)fn_800235D4();
    if (dst != 0) {
        u8 *s = (u8 *)p + 0x47D0;
        for (i = 0; i < 56; i++) {
            *dst++ = *s++;
        }
    }
}
