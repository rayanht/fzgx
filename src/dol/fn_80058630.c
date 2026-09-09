#include "types.h"

struct Counter {
    u32 value;
};

extern void fn_800576DC(void);
extern void fn_80057728(void);
extern u32 memset(u32, u32, u32);
extern u32 lbl_8018B2A0[];
extern u32 lbl_8018B2A4[4097];

void fn_80058630(void) {
    struct Counter *counter;
    fn_80057728();
    counter = (struct Counter *)&lbl_8018B2A0;
    if (--counter->value == 0) {
        memset((u32)&lbl_8018B2A4, 0, 0x4000);
    }
    fn_800576DC();
}
