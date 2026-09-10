
#include "types.h"

typedef struct MkVaListState {
    signed char gpr;
    signed char fpr;
    unsigned short reserved;
    char *input_arg_area;
    char *reg_save_area;
} __va_list[1];

typedef __va_list va_list;

enum justification_options { left_justification, right_justification, zero_fill };

enum sign_options { only_minus, sign_always, space_holder };

enum argument_options {
    normal_argument,
    char_argument,
    short_argument,
    long_argument,
    long_long_argument,
    long_double_argument,
    wchar_argument
};

typedef struct {
    unsigned char justification_options;
    unsigned char sign_options;
    unsigned char precision_specified;
    unsigned char alternate_form;
    unsigned char argument_options;
    unsigned char conversion_char;
    int field_width;
    int precision;
} print_format;

const char *parse_format(const char *format_string, va_list *arg, print_format *format);

void *__va_arg(__va_list args, int type);

extern unsigned char lbl_8015B100[];

static inline int isdigit(int c) { return (int)(lbl_8015B100[(unsigned char)c] & 0x10); }

const char *parse_format(const char *format_string, va_list *arg, print_format *format) {
    print_format f;
    const char *s = format_string;
    int c;
    int flag_found;
    f.justification_options = right_justification;
    f.sign_options = only_minus;
    f.precision_specified = 0;
    f.alternate_form = 0;
    f.argument_options = normal_argument;
    f.field_width = 0;
    f.precision = 0;
    if ((c = *++s) == '%') {
        f.conversion_char = c;
        *format = f;
        return ((const char *)s + 1);
    }
    for (;;) {
        flag_found = 1;
        switch (c) {
        case '-':
            f.justification_options = left_justification;
            break;
        case '+':
            f.sign_options = sign_always;
            break;
        case ' ':
            if (f.sign_options != sign_always) {
                f.sign_options = space_holder;
            }
            break;
        case '#':
            f.alternate_form = 1;
            break;
        case '0':
            if (f.justification_options != left_justification) {
                f.justification_options = zero_fill;
            }
            break;
        default:
            flag_found = 0;
            break;
        }
        if (flag_found) {
            c = *++s;
        } else {
            break;
        }
    }
    if (c == '*') {
        if ((f.field_width = (*((int *)__va_arg((*arg), _var_arg_typeof(int))))) < 0) {
            f.justification_options = left_justification;
            f.field_width = -f.field_width;
        }
        c = *++s;
    } else {
        while (isdigit(c)) {
            f.field_width = (f.field_width * 10) + (c - '0');
            c = *++s;
        }
    }
    if (f.field_width > 509) {
        f.conversion_char = 0xFF;
        *format = f;
        return ((const char *)s + 1);
    }
    if (c == '.') {
        f.precision_specified = 1;
        if ((c = *++s) == '*') {
            if ((f.precision = (*((int *)__va_arg((*arg), _var_arg_typeof(int))))) < 0) {
                f.precision_specified = 0;
            }
            c = *++s;
        } else {
            while (isdigit(c)) {
                f.precision = (f.precision * 10) + (c - '0');
                c = *++s;
            }
        }
    }
    flag_found = 1;
    switch (c) {
    case 'h':
        f.argument_options = short_argument;
        if (s[1] == 'h') {
            f.argument_options = char_argument;
            c = *++s;
        }
        break;
    case 'l':
        f.argument_options = long_argument;
        if (s[1] == 'l') {
            f.argument_options = long_long_argument;
            c = *++s;
        }
        break;
    case 'L':
        f.argument_options = long_double_argument;
        break;
    default:
        flag_found = 0;
        break;
    }
    if (flag_found) {
        c = *++s;
    }
    f.conversion_char = c;
    switch (c) {
    case 'd':
    case 'i':
    case 'u':
    case 'o':
    case 'x':
    case 'X':
        if (f.argument_options == long_double_argument) {
            f.conversion_char = 0xFF;
            break;
        }
        if (!f.precision_specified) {
            f.precision = 1;
        } else if (f.justification_options == zero_fill) {
            f.justification_options = right_justification;
        }
        break;
    case 'f':
    case 'F':
        if (f.argument_options == short_argument || f.argument_options == long_long_argument) {
            f.conversion_char = 0xFF;
            break;
        }
        if (!f.precision_specified) {
            f.precision = 6;
        }
        break;
    case 'a':
    case 'A':
        if (!f.precision_specified) {
            f.precision = 0xD;
        }
        if (f.argument_options == short_argument || f.argument_options == long_long_argument ||
            f.argument_options == char_argument) {
            f.conversion_char = 0xFF;
        }
        break;
    case 'g':
    case 'G':
        if (!f.precision) {
            f.precision = 1;
        }
    case 'e':
    case 'E':
        if (f.argument_options == short_argument || f.argument_options == long_long_argument ||
            f.argument_options == char_argument) {
            f.conversion_char = 0xFF;
            break;
        }
        if (!f.precision_specified) {
            f.precision = 6;
        }
        break;
    case 'p':
        f.conversion_char = 'x';
        f.alternate_form = 1;
        f.argument_options = long_argument;
        f.precision = 8;
        break;
    case 'c':
        if (f.argument_options == long_argument) {
            f.argument_options = wchar_argument;
        } else {
            if (f.precision_specified || f.argument_options != normal_argument) {
                f.conversion_char = 0xFF;
            }
        }
        break;
    case 's':
        if (f.argument_options == long_argument) {
            f.argument_options = wchar_argument;
        } else {
            if (f.argument_options != normal_argument) {
                f.conversion_char = 0xFF;
            }
        }
        break;
    case 'n':
        if (f.argument_options == long_double_argument) {
            f.conversion_char = 0xFF;
        }
        break;
    default:
        f.conversion_char = 0xFF;
        break;
    }
    *format = f;
    return ((const char *)s + 1);
}
