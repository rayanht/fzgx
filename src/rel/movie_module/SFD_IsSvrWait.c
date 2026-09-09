#include "types.h"
#include "sofdec/sfd.h"

extern SfdLibraryWork lbl_12_bss_7C64;



int SFD_IsSvrWait(void) {
    SfdHandle **handles = lbl_12_bss_7C64.handles;
    int i;
    int waiting;
    SfdHandle *handle;
    for (i = 0; i < 8; i++) {
        handle = *handles;
        if (handle != 0) {
            if ((unsigned int)(handle->playback_state - 1) > 3) {
                waiting = 1;
            } else if (handle->field_0044 != 0) {
                waiting = 0;
            } else {
                waiting = 1;
            }
            if (waiting == 0) {
                return 0;
            }
        }
        handles++;
    }
    return 1;
}
