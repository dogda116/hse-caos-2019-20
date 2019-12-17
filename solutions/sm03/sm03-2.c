#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>

int32_t satsum(int32_t v1, int32_t v2) {
    int32_t sum_no_of;
    if (__builtin_add_overflow(v1, v2, &sum_no_of)) {
        uint32_t sum_of = 0 - 1u;
        if (v1 < 0 && v2 < 0) {
            return ~(sum_of / 2);
        } else {
            return sum_of / 2;
        }
    }
    return sum_no_of;
}
