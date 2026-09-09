#include <dolphin/si/SIPriv.h>
#include <dolphin/os/OSAlarm.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSRtc.h>
#include <dolphin/si.h>

extern SIPacket Packet_8015CA10[4];

extern OSAlarm lbl_8015CA90[4];

static BOOL __SITransfer(s32 chan, void *output, u32 outputBytes, void *input, u32 inputBytes,
                         SICallback callback);

BOOL __SITransfer(s32 chan, void *output, u32 outputBytes, void *input, u32 inputBytes,
                  SICallback callback);

void AlarmHandler_SIBios(OSAlarm *alarm, OSContext *context) {
    s32 chan;
    SIPacket *packet;
    chan = alarm - lbl_8015CA90;
    packet = &Packet_8015CA10[chan];
    if (packet->chan != -1) {
        if (__SITransfer(packet->chan, packet->output, packet->outputBytes, packet->input,
                         packet->inputBytes, packet->callback)) {
            packet->chan = -1;
        }
    }
}
