
#include "types.h"

typedef void (*MfCiErrorCallback)(void *object, const char *message, void *handle);

int sprintf(char *output, const char *format, ...);

unsigned long strtoul(const char *str, char **end, int base);

unsigned long strlen(const char *string);

extern const char lbl_800925B8[];

extern const char lbl_800925F8[];

struct mfciBss {
    MfCiErrorCallback mfci_err_func;
    void *mfci_err_obj;
    char mfci_err_str[300];
};
extern struct mfciBss lbl_80190178;

static inline unsigned char *mfci_get_adr_size(const char *filename, int *file_size) {
    struct mfciBss *bss = &lbl_80190178;

    char *end;
    unsigned long address;
    if (strlen(filename) != 17) {
        sprintf((bss->mfci_err_str), lbl_800925B8, filename);
        if ((bss->mfci_err_func) != 0) {
            (bss->mfci_err_func)((bss->mfci_err_obj), (bss->mfci_err_str), 0);
        }
    }
    if (filename[8] != '.') {
        sprintf((bss->mfci_err_str), lbl_800925F8, filename);
        if ((bss->mfci_err_func) != 0) {
            (bss->mfci_err_func)((bss->mfci_err_obj), (bss->mfci_err_str), 0);
        }
    }
    end = (char *)filename;
    address = strtoul(filename, &end, 16);
    if (*end != '\0') {
        end++;
    }
    if (file_size != 0) {
        *file_size = (int)strtoul(end, &end, 16);
    }
    return (unsigned char *)address;
}

int mfCiGetFileSize(const char *filename) {
    int file_size;
    mfci_get_adr_size(filename, &file_size);
    return file_size;
}
