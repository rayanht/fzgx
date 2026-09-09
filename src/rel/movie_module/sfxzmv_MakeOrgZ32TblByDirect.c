#include "types.h"
#include "sofdec/sfx.h"

void sfxzmv_MakeOrgZ32TblByDirect(SFXZObject *object, u32 near_z, u32 far_z, u32 *table) {
    s32 i;
    if (far_z == 0x80000000U) {
        far_z = 0x7FFFFFFF;
    }
    if (near_z == 0x80000000U) {
        near_z = 0x7FFFFFFF;
    }
    for (i = 0; i < 9; i++) {
        table[i] = 0;
    }
    for (i = 9; i < 17; i++) {
        table[i] = near_z;
    }
    if (near_z == far_z) {
        for (i = 17; i < 224; i++) {
            table[i] = near_z;
        }
    } else {
        for (i = 17; i < 224; i++) {
            table[i] = near_z + (i - 17) * ((far_z - near_z) / 207);
        }
    }
    for (i = 224; i < 240; i++) {
        table[i] = far_z;
    }
    for (i = 240; i < 256; i++) {
        table[i] = 0x7FFFFFFF;
    }
}
