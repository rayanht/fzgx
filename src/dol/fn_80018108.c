#include "types.h"

extern struct fn_80018108_IDShouldBe_801A68C4_T *IDShouldBe_801A68C4;
extern u32 DVDLowAudioBufferConfig(u32, u32, u32);
extern void cbForStateCheckID3(void);

struct fn_80018108_IDShouldBe_801A68C4_T {
    u8 pad_0[0x8];
    u8 unk_8;
};

void fn_80018108(void) {
    DVDLowAudioBufferConfig(IDShouldBe_801A68C4->unk_8, 10, (u32)cbForStateCheckID3);
}
