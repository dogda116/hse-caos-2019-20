#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>

uint32_t satsum(uint32_t v1, uint32_t v2) {
    if (v1 + v2 < v2) {
        uint32_t sum_of = 0 - 1u;
        return sum_of;
    } else {
        return v1 + v2;
    }
}
