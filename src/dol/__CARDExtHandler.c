#include "types.h"
#include "dol/globals.h"

extern void EXISetExiCallback(s32 chan, void *callback);
extern void OSCancelAlarm(void *arg);

typedef void (*CardExtCallback)(s32 chan, s32 result);

void __CARDExtHandler(s32 chan) {
    Obj_80177960 *card;
    CardExtCallback callback;

    card = (Obj_80177960 *)((u8 *)&lbl_80177960 + chan * 0x110);
    if ((s32)card->unk_0 != 0) {
        card->unk_0 = 0;
        EXISetExiCallback(chan, 0);
        OSCancelAlarm((u8 *)card + 0xe0);

        callback = (CardExtCallback)card->unk_CC;
        if (callback != 0) {
            card->unk_CC = 0;
            callback(chan, -3);
        }

        if ((s32)card->unk_4 != -1) {
            card->unk_4 = -3;
        }

        callback = (CardExtCallback)card->unk_C4;
        if (callback != 0 && (s32)card->unk_24 >= 7) {
            card->unk_C4 = 0;
            callback(chan, -3);
        }
    }
}
