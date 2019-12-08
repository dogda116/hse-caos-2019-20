#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main(void) {
    uint32_t m1, m2, d;
    scanf("%" SCNu32 "%" SCNu32, &m1, &m2);
    if (m1 < m2) {
        d = m2;
        m2 = m1;
        m1 = d;
    }
    while (scanf("%" SCNu32, &d) != EOF) {
        if (d > m1) {
            m2 = m1;
            m1 = d;
        } else if (d > m2) {
            m2 = d;
        }
    }
    printf("%" PRIu32 "\n", m1 * m2);
    return 0;
}
