#include "types.h"

extern const char lbl_80095648[];
extern void TRK_board_display(const char *);


void TRKNubWelcome(void) {
    TRK_board_display("MetroTRK for GAMECUBE v2.0");
}
