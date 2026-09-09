#ifndef DOLPHIN_DSP_H
#define DOLPHIN_DSP_H

#include <dolphin/os/OSTime.h>

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

#endif
