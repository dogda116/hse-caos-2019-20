#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>

void representation(float num) {
    const int e = 8;
    const int m = 23;
    union {
        float f;
        uint32_t u;
    } fu = { .f = num};
    uint32_t sgn = 1 & (fu.u >> (m + e));
    uint32_t exp = ((1 << e) - 1) & (fu.u >> m);
    uint32_t man = ((1 << m) - 1) & fu.u;
    printf("%u %u %x\n", sgn, exp, man);
}

int main(void) {
    float num;
    while (scanf("%f", &num) != EOF) {
        representation(num);
    }
    return 0;
}
