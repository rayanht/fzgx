#ifndef SOFDEC_SFTST_H
#define SOFDEC_SFTST_H

#include "types.h"

typedef struct SFTST_Time {
    long long value;
    long long scale;
} SFTST_Time;

typedef struct SFTST_Work {
    int test_enabled;
    int paused;
    int reset_history;
    int adjust_enabled;
    int average_count;
    int average_index;
    int errors[60];
    SFTST_Time input_time;
    SFTST_Time sample_time;
    SFTST_Time output_time;
    SFTST_Time tolerance;
    SFTST_Time excess_error;
    SFTST_Time adjustment_start;
    SFTST_Time adjustment_offset;
    long long previous_sample;
    long long adjusted_time;
    long long maximum_time;
    int adjustment_count;
    int positive_adjustments;
    int negative_adjustments;
    int history_resets;
    int excess_resets;
    int average;
    int adjusted_average;
    int front_max;
    int front_min;
    int rear_max;
    int rear_min;
    int field_0x1BC;
} SFTST_Work;

void SFTST_Create(SFTST_Work* work);

#endif
