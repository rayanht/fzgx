
#include "types.h"

// Hardware or OS state can change asynchronously.
typedef volatile u32 vu32;

typedef s64 OSTime;

typedef void (*DSPCallback)(void *task);

typedef struct STRUCT_DSP_TASK {
    vu32 state;
    vu32 priority;
    vu32 flags;
    u16 *iram_mmem_addr;
    u32 iram_length;
    u32 iram_addr;
    u16 *dram_mmem_addr;
    u32 dram_length;
    u32 dram_addr;
    u16 dsp_init_vector;
    u16 dsp_resume_vector;
    DSPCallback init_cb;
    DSPCallback res_cb;
    DSPCallback done_cb;
    DSPCallback req_cb;
    struct STRUCT_DSP_TASK *next;
    struct STRUCT_DSP_TASK *prev;
    OSTime t_context;
    OSTime t_task;
} DSPTaskInfo;

u32 DSPCheckMailToDSP(void);

u32 DSPCheckMailFromDSP(void);

u32 DSPReadMailFromDSP(void);

void DSPSendMailToDSP(u32 mail);

void fn_80028F50(const char *fmt, ...);

void __DSP_boot_task(DSPTaskInfo *task) {
// Hardware or OS state can change asynchronously.
    volatile u32 mail;
    while (!DSPCheckMailFromDSP())
        ;
    mail = DSPReadMailFromDSP();
    DSPSendMailToDSP(0x80F30000 | 0xA001); // fzgx-allow: A1 DSP mailbox command, not an address
    while (DSPCheckMailToDSP()) {
    }
    DSPSendMailToDSP((u32)(task->iram_mmem_addr));
    while (DSPCheckMailToDSP()) {
    }
    DSPSendMailToDSP(0x80F30000 | 0xC002); // fzgx-allow: A1 DSP mailbox command, not an address
    while (DSPCheckMailToDSP()) {
    }
    DSPSendMailToDSP((u32)(task->iram_addr & 0xffff));
    while (DSPCheckMailToDSP()) {
    }
    DSPSendMailToDSP(0x80F30000 | 0xA002); // fzgx-allow: A1 DSP mailbox command, not an address
    while (DSPCheckMailToDSP()) {
    }
    DSPSendMailToDSP(task->iram_length);
    while (DSPCheckMailToDSP()) {
    }
    DSPSendMailToDSP(0x80F30000 | 0xB002); // fzgx-allow: A1 DSP mailbox command, not an address
    while (DSPCheckMailToDSP()) {
    }
    DSPSendMailToDSP(0x00000000);
    while (DSPCheckMailToDSP()) {
    }
    DSPSendMailToDSP(0x80F30000 | 0xD001); // fzgx-allow: A1 DSP mailbox command, not an address
    while (DSPCheckMailToDSP()) {
    }
    DSPSendMailToDSP((u32)(0xffff & task->dsp_init_vector));
    while (DSPCheckMailToDSP()) {
    }
    fn_80028F50("DSP is booting task: 0x%08X\n", task);
    fn_80028F50("__DSP_boot_task()  : IRAM MMEM ADDR: 0x%08X\n", (u32)(task->iram_mmem_addr));
    fn_80028F50("__DSP_boot_task()  : IRAM DSP ADDR : 0x%08X\n", (u32)(task->iram_addr));
    fn_80028F50("__DSP_boot_task()  : IRAM LENGTH   : 0x%08X\n", (u32)(task->iram_length));
    fn_80028F50("__DSP_boot_task()  : DRAM MMEM ADDR: 0x%08X\n", (u32)(task->dram_length));
    fn_80028F50("__DSP_boot_task()  : Start Vector  : 0x%08X\n", (u32)(task->dsp_init_vector));
}
