#include "types.h"
#include "sofdec/sfd.h"

extern const int lbl_12_rodata_E10[9];

void SFTIM_GetTimeOneFrmVideo(SfdHandle *handle, int *value, int *scale) {
    int code = handle->playback_settings.frame_rate_code;
    if (code == 0) {
        *value = 0;
        *scale = 29970;
    } else {
        *value = 1000;
        *scale = lbl_12_rodata_E10[code];
    }
}
