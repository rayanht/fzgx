#include <types.h>
#include <dolphin/dsp.h>
#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

u32 DSPCheckMailToDSP(void);

u32 DSPCheckMailFromDSP(void);

u32 DSPReadMailFromDSP(void);

void DSPSendMailToDSP(u32 mail);

extern DSPTaskInfo *lbl_801A6BBC;

extern DSPTaskInfo *lbl_801A6BB4;

extern DSPTaskInfo *lbl_801A6BB8;

void __DSP_exec_task(DSPTaskInfo *, DSPTaskInfo *);

void __DSP_remove_task(DSPTaskInfo *task);

vu16 __DSPRegs[32] : FZGX_ADDR___DSPRegs;

extern DSPTaskInfo *lbl_801A6BAC;

extern BOOL lbl_801A6BA8;

void __DSP_exec_task(DSPTaskInfo *curr, DSPTaskInfo *next);

void __DSPHandler(__OSInterrupt, OSContext *context) {
    DSPTaskInfo *tmp_task;
    OSContext exceptionContext;
    u16 tmp;
    u32 mail;
    tmp = __DSPRegs[5];
    tmp = (u16)(tmp & ~0x28) | 0x80;
    __DSPRegs[5] = tmp;
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);
    while (!DSPCheckMailFromDSP())
        ;
    mail = DSPReadMailFromDSP();
    if ((lbl_801A6BBC->flags & 0x00000002) && (mail == 0xDCD10002)) {
        mail = 0xDCD10003;
    }
    switch (mail) {
    case 0xDCD10000:
        lbl_801A6BBC->state = 1;
        if (lbl_801A6BBC->init_cb) {
            (*(lbl_801A6BBC->init_cb))((void *)(lbl_801A6BBC));
        }
        break;
    case 0xDCD10001:
        lbl_801A6BBC->state = 1;
        if (lbl_801A6BBC->res_cb) {
            (*(lbl_801A6BBC->res_cb))((void *)(lbl_801A6BBC));
        }
        break;
    case 0xDCD10002:
        if (lbl_801A6BA8) {
            if (lbl_801A6BBC == lbl_801A6BAC) {
                DSPSendMailToDSP(0xCDD10003);
                while (DSPCheckMailToDSP()) {
                }
                lbl_801A6BAC = 0;
                lbl_801A6BA8 = 0;
                if (lbl_801A6BBC->res_cb) {
                    (*(lbl_801A6BBC->res_cb))((void *)(lbl_801A6BBC));
                }
                break;
            } else {
                DSPSendMailToDSP(0xCDD10001);
                while (DSPCheckMailToDSP())
                    ;
                __DSP_exec_task(lbl_801A6BBC, lbl_801A6BAC);
                lbl_801A6BBC->state = 2;
                lbl_801A6BBC = lbl_801A6BAC;
                lbl_801A6BAC = 0;
                lbl_801A6BA8 = 0;
                break;
            }
        }
        if (lbl_801A6BBC->next == 0) {
            if (lbl_801A6BBC == lbl_801A6BB8) {
                DSPSendMailToDSP(0xCDD10003);
                while (DSPCheckMailToDSP())
                    ;
                if (lbl_801A6BBC->res_cb) {
                    (*(lbl_801A6BBC->res_cb))((void *)(lbl_801A6BBC));
                }
            } else {
                DSPSendMailToDSP(0xCDD10001);
                while (DSPCheckMailToDSP()) {
                }
                __DSP_exec_task(lbl_801A6BBC, lbl_801A6BB8);
                lbl_801A6BBC->state = 2;
                lbl_801A6BBC = lbl_801A6BB8;
            }
        } else {
            DSPSendMailToDSP(0xCDD10001);
            while (DSPCheckMailToDSP()) {
            }
            __DSP_exec_task(lbl_801A6BBC, lbl_801A6BBC->next);
            lbl_801A6BBC->state = 2;
            lbl_801A6BBC = lbl_801A6BBC->next;
        }
        break;
    case 0xDCD10003:
        if (lbl_801A6BA8) {
            if (lbl_801A6BBC->done_cb) {
                (*(lbl_801A6BBC->done_cb))((void *)(lbl_801A6BBC));
            }
            DSPSendMailToDSP(0xCDD10001);
            while (DSPCheckMailToDSP())
                ;
            __DSP_exec_task(0, lbl_801A6BAC);
            __DSP_remove_task(lbl_801A6BBC);
            lbl_801A6BBC = lbl_801A6BAC;
            lbl_801A6BAC = 0;
            lbl_801A6BA8 = 0;
            break;
        }
        if (lbl_801A6BBC->next == 0) {
            if (lbl_801A6BBC == lbl_801A6BB8) {
                if (lbl_801A6BBC->done_cb) {
                    (*(lbl_801A6BBC->done_cb))((void *)(lbl_801A6BBC));
                }
                DSPSendMailToDSP(0xCDD10002);
                while (DSPCheckMailToDSP())
                    ;
                lbl_801A6BBC->state = 3;
                __DSP_remove_task(lbl_801A6BBC);
            } else {
                if (lbl_801A6BBC->done_cb) {
                    (*(lbl_801A6BBC->done_cb))((void *)(lbl_801A6BBC));
                }
                DSPSendMailToDSP(0xCDD10001);
                while (DSPCheckMailToDSP())
                    ;
                lbl_801A6BBC->state = 3;
                __DSP_exec_task(0, lbl_801A6BB8);
                lbl_801A6BBC = lbl_801A6BB8;
                __DSP_remove_task(lbl_801A6BB4);
            }
        } else {
            if (lbl_801A6BBC->done_cb) {
                (*(lbl_801A6BBC->done_cb))((void *)(lbl_801A6BBC));
            }
            DSPSendMailToDSP(0xCDD10001);
            while (DSPCheckMailToDSP())
                ;
            lbl_801A6BBC->state = 3;
            __DSP_exec_task(0, lbl_801A6BBC->next);
            lbl_801A6BBC = lbl_801A6BBC->next;
            __DSP_remove_task(lbl_801A6BBC->prev);
        }
        break;
    case 0xDCD10004:
        if (lbl_801A6BBC->req_cb) {
            (*(lbl_801A6BBC->req_cb))((void *)(lbl_801A6BBC));
        }
        break;
    default:
        break;
    }
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}
