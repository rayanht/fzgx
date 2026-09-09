#include "types.h"
#include "dolphin/sdk/mkdd/card/CARDBios.h"

struct SDK_CARDBios____bss_0 {
    CARDControl sdk___CARDBlock[2];
    DVDDiskID sdk___CARDDiskNone;
};

extern struct SDK_CARDBios____bss_0 lbl_80177960;

void __CARDSetDiskID(const DVDDiskID *id) {
    struct SDK_CARDBios____bss_0 *sdk_storage____bss_0 = &lbl_80177960;

    (sdk_storage____bss_0->sdk___CARDBlock)[0].diskID =
        id ? id : &(sdk_storage____bss_0->sdk___CARDDiskNone);
    (sdk_storage____bss_0->sdk___CARDBlock)[1].diskID =
        id ? id : &(sdk_storage____bss_0->sdk___CARDDiskNone);
}