#include <dolphin/os.h>
#include <dolphin/os/OSError.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSThread.h>
#include "sdk_addresses.h"

u32 PPCMfmsr(void);

void PPCMtmsr(u32 val);

u32 PPCMffpscr(void);

void PPCMtfpscr(u32 val);

extern OSErrorHandler __OSErrorTable[(16 + 1)];

extern u32 lbl_801A6430;

OSThreadQueue __OSActiveThreadQueue : FZGX_ADDR___OSActiveThreadQueue;

OSErrorHandler OSSetErrorHandler(OSError error, OSErrorHandler handler) {
    OSErrorHandler oldHandler;
    BOOL enabled;
    enabled = OSDisableInterrupts();
    oldHandler = __OSErrorTable[error];
    __OSErrorTable[error] = handler;
    if (error == 16) {
        u32 msr;
        u32 fpscr;
        OSThread *thread;
        msr = PPCMfmsr();
        PPCMtmsr(msr | (1 << (31 - 18)));
        fpscr = PPCMffpscr();
        if (handler) {
            for (thread = __OSActiveThreadQueue.head; thread; thread = thread->linkActive.next) {
                thread->context.srr1 |= (1 << (31 - 20)) | (1 << (31 - 23));
                if ((thread->context.state & 0x01u) == 0) {
                    int i;
                    thread->context.state |= 0x01u;
                    for (i = 0; i < 32; ++i) {
                        *(u64 *)&thread->context.fpr[i] = (u64)0xffffffffffffffffLL;
                        *(u64 *)&thread->context.psf[i] = (u64)0xffffffffffffffffLL;
                    }
                    thread->context.fpscr = (1 << (31 - 29));
                }
                thread->context.fpscr |=
                    lbl_801A6430 & ((1 << (31 - 24)) | (1 << (31 - 25)) | (1 << (31 - 26)) |
                                    (1 << (31 - 27)) | (1 << (31 - 28)));
                thread->context.fpscr &=
                    ~((1 << (31 - 12)) | (1 << (31 - 11)) | (1 << (31 - 10)) | (1 << (31 - 9)) |
                      (1 << (31 - 8)) | (1 << (31 - 7)) | (1 << (31 - 21)) | (1 << (31 - 22)) |
                      (1 << (31 - 23)) | (1 << (31 - 6)) | (1 << (31 - 5)) | (1 << (31 - 4)) |
                      (1 << (31 - 3)) | (1 << (31 - 0)) | (1 << (31 - 14)));
            }
            fpscr |= lbl_801A6430 & ((1 << (31 - 24)) | (1 << (31 - 25)) | (1 << (31 - 26)) |
                                     (1 << (31 - 27)) | (1 << (31 - 28)));
            msr |= (1 << (31 - 20)) | (1 << (31 - 23));
        } else {
            for (thread = __OSActiveThreadQueue.head; thread; thread = thread->linkActive.next) {
                thread->context.srr1 &= ~((1 << (31 - 20)) | (1 << (31 - 23)));
                thread->context.fpscr &= ~((1 << (31 - 24)) | (1 << (31 - 25)) | (1 << (31 - 26)) |
                                           (1 << (31 - 27)) | (1 << (31 - 28)));
                thread->context.fpscr &=
                    ~((1 << (31 - 12)) | (1 << (31 - 11)) | (1 << (31 - 10)) | (1 << (31 - 9)) |
                      (1 << (31 - 8)) | (1 << (31 - 7)) | (1 << (31 - 21)) | (1 << (31 - 22)) |
                      (1 << (31 - 23)) | (1 << (31 - 6)) | (1 << (31 - 5)) | (1 << (31 - 4)) |
                      (1 << (31 - 3)) | (1 << (31 - 0)) | (1 << (31 - 14)));
            }
            fpscr &= ~((1 << (31 - 24)) | (1 << (31 - 25)) | (1 << (31 - 26)) | (1 << (31 - 27)) |
                       (1 << (31 - 28)));
            msr &= ~((1 << (31 - 20)) | (1 << (31 - 23)));
        }
        fpscr &= ~((1 << (31 - 12)) | (1 << (31 - 11)) | (1 << (31 - 10)) | (1 << (31 - 9)) |
                   (1 << (31 - 8)) | (1 << (31 - 7)) | (1 << (31 - 21)) | (1 << (31 - 22)) |
                   (1 << (31 - 23)) | (1 << (31 - 6)) | (1 << (31 - 5)) | (1 << (31 - 4)) |
                   (1 << (31 - 3)) | (1 << (31 - 0)) | (1 << (31 - 14)));
        PPCMtfpscr(fpscr);
        PPCMtmsr(msr);
    }
    OSRestoreInterrupts(enabled);
    return oldHandler;
}
