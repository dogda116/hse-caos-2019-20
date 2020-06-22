#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>

enum
{
    LINE_BYTES = 16,
    NUM_BYTES = 4
};

int main() {
    uint32_t swapped = 0;
    int num;
    int count = 0, two_hex = 0;
    while (scanf("%x", &num) == 1) {
        if (count++ == LINE_BYTES) {
            count = 0;
            swapped <<= 8;
            swapped += num;
            two_hex = 0;
            printf("%" PRIu32 "\n", swapped);
            swapped = 0;
        } else if (count > 1) {
            swapped <<= 8;
            swapped += num;
            if (++two_hex == NUM_BYTES) {
                printf("%" PRIu32 "\n", swapped);
                swapped = 0;
                two_hex = 0;
            }
        }
    }
    return 0;
}
