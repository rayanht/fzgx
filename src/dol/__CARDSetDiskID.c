#include <dolphin/card/CARDPriv.h>

struct CARDBiosBss {
    CARDControl blocks[2];
    DVDDiskID diskNone;
};

extern struct CARDBiosBss lbl_80177960;

void __CARDSetDiskID(const DVDDiskID *id) {
    struct CARDBiosBss *storage = &lbl_80177960;

    (storage->blocks)[0].diskID = id ? id : &(storage->diskNone);
    (storage->blocks)[1].diskID = id ? id : &(storage->diskNone);
}
