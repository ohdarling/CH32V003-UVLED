
#include <stdio.h>

int format_number(char *buf, int32_t num) {
    int len = 1;
    int32_t div = 10;
    int32_t num_orig = num;
    num = num / 10;
    while (num > 0) {
        len++;
        div *= 10;
        num /= 10;
    }
    div /= 10;
    num = num_orig;
    for (int i = 0; i < len; ++i) {
        buf[i] = (num / div) + '0';
        num = num % div;
        div /= 10;
    }
    return len;
}

void my_printf(char *buf, int max_len, const char *format, int nums[]) {
    int i = 0;
    int fi = 0;
    int ni = 0;
    while (i < max_len && format[fi] != 0) {
        if (format[fi] == '%') {
            if (format[fi+1] == 'd') {
                int len = format_number(buf + i, nums[ni]);
                i += len;
                fi += 2;
                ni++;
                continue;;
            }
        }
        buf[i] = format[fi];
        i++;
        fi++;
    }
    buf[i] = 0;
}

void my_printf1(char *buf, int max_len, const char *format, int num) {
    my_printf(buf, max_len, format, &num);
}

void my_printf2(char *buf, int max_len, const char *format, int num1, int num2) {
    int nums[] = { num1, num2 };
    my_printf(buf, max_len, format, nums);
}

void my_printf3(char *buf, int max_len, const char *format, int num1, int num2, int num3) {
    int nums[] = { num1, num2, num3 };
    my_printf(buf, max_len, format, nums);
}