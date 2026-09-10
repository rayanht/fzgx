
#include "types.h"

typedef struct SJCK {
    unsigned char *data;
    int len;
} SJCK;

int strncmp(const char *lhs, const char *rhs, unsigned long count);

extern int lbl_80132330[0x70];

static inline int sj_hexstr_to_val(const unsigned char *text, const int *table) {
    int value;
    value = table[(signed char)text[0]];
    value = (value << 4) + table[(signed char)text[1]];
    value = (value << 4) + table[(signed char)text[2]];
    value = (value << 4) + table[(signed char)text[3]];
    value = (value << 4) + table[(signed char)text[4]];
    value = (value << 4) + table[(signed char)text[5]];
    value = (value << 4) + table[(signed char)text[6]];
    return value;
}

unsigned char *SJ_SearchTag(const SJCK *source, const char *tag, const char *terminator,
                           SJCK *result) {
    unsigned char *current;
    unsigned char *end;
    unsigned char *start;
    const int *table;
    result->data = 0;
    table = lbl_80132330;
    result->len = 0;
    start = source->data;
    current = start;
    end = start + source->len;
    while (current < end) {
        if (strncmp((const char *)current, tag, 7) == 0) {
            result->data = current + 0x10;
            result->len = sj_hexstr_to_val(current + 8, lbl_80132330);
            break;
        }
        if (terminator != 0 && strncmp((const char *)current, terminator, 7) == 0) {
            return 0;
        }
        current += sj_hexstr_to_val(current + 8, table) + 0x10;
    }
    return current < end ? current : 0;
}
