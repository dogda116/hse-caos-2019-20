#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>

int is_possibly_float(uint32_t f) {
    for (int i = 0; i != 9; ++i) {
        if (f % 2 == 0) {
            f = f >> 1;
        } else {
            break;
        }
    }
    return (f >> 24) == 0;
}

int main(void) {
    uint32_t num;
    while (scanf("%" SCNu32, &num) != EOF) {
        printf("%d\n", is_possibly_float(num));
    }
    return 0;
}
