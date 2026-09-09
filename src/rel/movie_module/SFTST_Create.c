#include "sofdec/sftst.h"

typedef struct SFTST_Header {
    char text[274];
} SFTST_Header;

void *memset(void *destination, int value, unsigned long size);

char *fn_80083DB0(char *destination, const char *source);

unsigned long strlen(const char *string);

extern const SFTST_Header lbl_12_rodata_F00;

struct SFTST_DebugOutput {
    int size;
    char *buffer;
    char *wrap;
    char *cursor;
    SFTST_Work *last;
};
extern struct SFTST_DebugOutput lbl_12_bss_1B740;

void SFTST_Create(SFTST_Work *work) {
    struct SFTST_DebugOutput *const debug = &lbl_12_bss_1B740;

    memset(work, 0, sizeof(*work));
    work->test_enabled = 1;
    work->paused = 0;
    work->reset_history = 0;
    work->adjust_enabled = 1;
    work->average_count = 10;
    memset(work->errors, 0, sizeof(work->errors));
    work->average_index = 0;
    work->history_resets++;
    work->input_time.value = 0;
    work->input_time.scale = 1;
    work->sample_time.value = 0;
    work->sample_time.scale = 1;
    work->output_time.value = 0;
    work->output_time.scale = 1;
    work->tolerance.value = 0x412b;
    work->tolerance.scale = 1000000;
    work->excess_error.value = 200000;
    work->excess_error.scale = 1000000;
    work->adjustment_start.value = -0x412b;
    work->adjustment_start.scale = 1000000;
    work->adjustment_offset.value = -0x412b;
    work->adjustment_offset.scale = 1000000;
    work->previous_sample = -1;
    work->adjusted_time = 0;
    work->maximum_time = 0;
    work->adjustment_count = 0;
    work->positive_adjustments = 0;
    work->negative_adjustments = 0;
    work->history_resets = 0;
    work->excess_resets = 0;
    work->average = 0;
    work->adjusted_average = 0;
    work->front_max = 0;
    work->front_min = 0;
    work->rear_max = 0;
    work->rear_min = 0;
    {
        SFTST_Header header = lbl_12_rodata_F00;
        if ((debug->buffer) != 0) {
            memset((debug->buffer), 0, (debug->size));
            (debug->cursor) = (debug->buffer);
            fn_80083DB0((debug->buffer), header.text);
            (debug->cursor) += strlen(header.text);
            (debug->wrap) = (debug->cursor);
        }
    }
}
