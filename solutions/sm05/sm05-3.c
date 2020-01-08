#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

int check_argument(char* arg, int base) {
    errno = 0;
    int64_t parsed_number;
    char* str_end;
    parsed_number = (int64_t) strtol(arg, &str_end, base);
    if (errno || *str_end || !*arg) {
        return -1;
    } else if ((int8_t) parsed_number == parsed_number) {
        return 1;
    } else if ((int16_t) parsed_number == parsed_number) {
        return 2;
    } else if ((int32_t) parsed_number == parsed_number) {
        return 4;
    } else {
        return -1;
    }
}

int main(int argc, char *argv[]) {
    int base = 10;
    for (int i = 1; i != argc; ++i) {
        printf("%d\n", check_argument(argv[i], base));
    }
}
