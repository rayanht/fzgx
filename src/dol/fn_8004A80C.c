#include "types.h"

typedef struct Fn8004A80C_Chunk {
    u8 *data;
    s32 len;
} Fn8004A80C_Chunk;

typedef struct Fn8004A80C_SJ Fn8004A80C_SJ;

typedef struct Fn8004A80C_SJVtbl {
    u8 pad_0[0x18];
    void (*GetChunk)(Fn8004A80C_SJ *sj, s32 id, s32 nbyte, Fn8004A80C_Chunk *ck);
    void (*UngetChunk)(Fn8004A80C_SJ *sj, s32 id, Fn8004A80C_Chunk *ck);
    void (*PutChunk)(Fn8004A80C_SJ *sj, s32 id, Fn8004A80C_Chunk *ck);
    s32 (*GetNumData)(Fn8004A80C_SJ *sj, s32 id);
} Fn8004A80C_SJVtbl;

struct Fn8004A80C_SJ {
    Fn8004A80C_SJVtbl *vtbl;
};

typedef struct Fn8004A80C_Stm {
    u8 pad_0[0x1];
    s8 stat;
    s8 rqrd;
    s8 retry;
    Fn8004A80C_SJ *sj;
    void *fs;
    s32 ofst;
    s32 len;
    s32 rdsize;
    s32 minsize;
    s32 nrd;
    Fn8004A80C_Chunk ck;
    s32 maxsct;
    s32 eossct;
    u32 total;
    void (*eoscb)(void *obj);
    void *eosobj;
    s32 bufsize;
    s8 unk_40;
    u8 pad_41[0x3];
    s8 req_stop;
    u8 pad_45[0xF];
    s32 pos;
    u32 limit;
} Fn8004A80C_Stm;

extern s32 lbl_8017D700;
extern s32 lbl_8017D704;
extern s32 fn_800546A0(void *fs);
extern void fn_80059B44(void);
extern void fn_80059AB4(void);
extern void fn_800589BC(Fn8004A80C_Chunk *ck, s32 nbyte, Fn8004A80C_Chunk *ck1, Fn8004A80C_Chunk *ck2);
extern void fn_80054930(void *fs, s32 offset, s32 origin);
extern s32 fn_80054870(void *fs, s32 nsct, u8 *buf);

static inline void fn_8004A80C_retry(Fn8004A80C_Stm *stm) {
    if (lbl_8017D700 >= 0) {
        if (stm->retry >= lbl_8017D700) {
            stm->stat = 4;
        } else {
            stm->retry++;
        }
    }
}

void fn_8004A80C(Fn8004A80C_Stm *stm) {
    Fn8004A80C_SJ *sj;
    s32 stat;
    s32 nbyte;
    s32 nsct;
    s32 end;
    Fn8004A80C_Chunk ck1;
    Fn8004A80C_Chunk ck2;
    Fn8004A80C_Chunk ck;

    sj = stm->sj;
    stat = fn_800546A0(stm->fs);
    fn_80059B44();
    if (stm->rqrd == 1) {
        if (stat == 1) {
            stm->rqrd = 0;
            fn_80059AB4();
            nbyte = stm->nrd << 11;
            fn_800589BC(&stm->ck, nbyte, &ck1, &ck2);
            sj->vtbl->PutChunk(sj, 1, &ck1);
            sj->vtbl->UngetChunk(sj, 0, &ck2);
            stm->pos += stm->nrd;
            stm->total += nbyte;
            stm->ck.data = NULL;
            stm->ck.len = 0;
            end = stm->len / 0x800 + (stm->len % 0x800 > 0);
            if (stm->pos == stm->eossct && stm->eoscb != NULL) {
                stm->eoscb(stm->eosobj);
            }
            if (stm->pos >= end) {
                stm->stat = 3;
            } else if ((stm->total >> 11) >= stm->limit && stm->limit < 0xFFFFF) {
                stm->stat = 3;
            }
            stm->retry = 0;
        } else if (stat == 3) {
            stm->rqrd = 0;
            fn_80059AB4();
            sj->vtbl->UngetChunk(sj, 0, &stm->ck);
            stm->ck.data = NULL;
            stm->ck.len = 0;
            fn_8004A80C_retry(stm);
        } else {
            fn_80059AB4();
        }
        return;
    }

    stm->rqrd = 1;
    stm->ck.data = NULL;
    stm->ck.len = 0;
    fn_80059AB4();
    if (stm->unk_40 == 1 || stm->req_stop == 1) {
        stm->rqrd = 0;
        return;
    }
    if (stm->len == 0) {
        stm->rqrd = 0;
        stm->nrd = 0;
        stm->stat = 3;
        return;
    }
    if (sj == NULL || sj->vtbl == NULL) {
        stm->rqrd = 0;
        lbl_8017D704++;
        return;
    }
    if (stm->bufsize - sj->vtbl->GetNumData(sj, 0) >= stm->minsize) {
        stm->rqrd = 0;
        return;
    }
    sj->vtbl->GetChunk(sj, 0, stm->rdsize, &ck);
    nsct = ck.len / 0x800;
    end = (nsct < stm->eossct - stm->pos) ? nsct : stm->eossct - stm->pos;
    nsct = stm->len / 0x800 - stm->pos;
    if (end < nsct) {
        nsct = end;
    }
    end = stm->maxsct;
    if (nsct < end) {
        end = nsct;
    }
    fn_80054930(stm->fs, stm->ofst + stm->pos, 0);
    stm->nrd = fn_80054870(stm->fs, end, ck.data);
    stm->ck.data = ck.data;
    stm->ck.len = ck.len;
    if (stm->nrd > 0) {
        return;
    }
    sj->vtbl->UngetChunk(sj, 0, &stm->ck);
    stm->ck.data = NULL;
    stm->ck.len = 0;
    stm->rqrd = 0;
    if (fn_800546A0(stm->fs) == 3) {
        fn_8004A80C_retry(stm);
    }
}
