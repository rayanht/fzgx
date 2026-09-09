#ifndef DOLPHIN_OS_OSTIME_H
#define DOLPHIN_OS_OSTIME_H

#include <dolphin/types.h>

typedef s64 OSTime;

typedef struct OSCalendarTime {
    int sec;
    int min;
    int hour;
    int mday;
    int mon;
    int year;
    int wday;
    int yday;
    int msec;
    int usec;
} OSCalendarTime;
#endif
