#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>

size_t process_2(const char *str, const char *range) {
    size_t i = 0;
    while (str[i] != '\0' && range[0] <= str[i] && str[i] <= range[2])
        ++i;
    return i;
}
