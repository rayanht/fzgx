#include "types.h"
#include "sofdec/sfd.h"

void SFTMR_AddTsum(SfdTimerSummary *summary, long long elapsed) {
    long long minimum;
    long long maximum;
    summary->total += elapsed;
    minimum = summary->minimum;
    if (elapsed < minimum) {
        minimum = elapsed;
    }
    summary->minimum = minimum;
    maximum = summary->maximum;
    elapsed = maximum < elapsed ? elapsed : maximum;
    summary->maximum = elapsed;
    summary->count++;
}
