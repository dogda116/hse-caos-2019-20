#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main(void) {
    uint32_t a, b, result;
    scanf("%" SCNu32 "%u" SCNu32, &a, &b);
    result = a / 2 + b / 2;
    if (a % 2 == 1 && b % 2 == 1) {
        ++result;
    }
    printf("%" PRIu32 "\n", result);
    return 0;
}
