#include "types.h"

typedef struct MovieTime {
    u8 padding0[8];
    s32 hours;
    s32 minutes;
    s32 seconds;
    s32 milliseconds;
    s32 extra;
} MovieTime;

void fn_12_2E334(s32 value, MovieTime *time, s32 *result, s32 *out_value) {
    s32 ms;
    s32 total;

    ms = (time->milliseconds + time->extra) * 0x3e8;
    total = time->minutes * 0x3c + time->hours * 0xe10 + time->seconds;
    *result = total * value + ms;
    *out_value = value;
}
