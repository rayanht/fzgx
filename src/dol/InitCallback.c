#include "types.h"
#include "dolphin/sdk/mkdd/card/CARDUnlock.h"

extern CARDControl lbl_80177960[2];

extern unsigned long int next;

void InitCallback(void *_task) {
    s32 chan;
    CARDControl *card;
    DSPTaskInfo *task;
    DecodeParameters *param;
    task = _task;
    for (chan = 0; chan < 2; ++chan) {
        card = &lbl_80177960[chan];
        if ((DSPTaskInfo *)&card->task == task) {
            break;
        }
    }
    param = (DecodeParameters *)card->workArea;
    DSPSendMailToDSP(0xff000000);
    while (DSPCheckMailToDSP())
        ;
    DSPSendMailToDSP((u32)param);
    while (DSPCheckMailToDSP())
        ;
}