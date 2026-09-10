#include "types.h"

extern u32 lbl_801A6834;
extern void SIGetResponse(u32, void *);
extern void SISetCommand(u32, u32);
extern void SIEnablePolling(u32);

void fn_8001375C(u32 channel) {
    u32 mask;
    u32 command;
    u32 response;

    mask = ((u32)0x8000 << 16) >> channel;
    if ((lbl_801A6834 & mask) == 0) {
        lbl_801A6834 |= mask;
        SIGetResponse(channel, &response);
        command = 0x300000;
        mask = command + 0x680;
        SISetCommand(channel, mask);
        SIEnablePolling(lbl_801A6834);
    }
}
