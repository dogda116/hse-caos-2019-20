#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <locale.h>
#include <wctype.h>
#include <wchar.h>

int main(void) {
    int64_t a, b, c, k, c1, c2, c3, diff1;
    scanf("%" SCNd64 "%" SCNd64, &a, &b);
    if (!(a % b)) {
        c = a;
    } else if (a > 0) {
        k = a / b;
        c1 = k * b;
        diff1 = llabs(a - c1);
        c = c1;
        int64_t tmp = (int64_t) (k + 1) * b;
        if (tmp > (int64_t)INT32_MAX) {
            c2 = (k - 1) * b;
        } else {
            c2 = (k + 1) * b;
        }
        if (llabs(a - c2) < diff1) {
            diff1 = llabs(a - c2);
            c = c2;
        }
        if (llabs(a - c2) == diff1 && c2 > c) {
            c = c2;
        }
        c3 = 0;
        if (llabs(a - c3) < diff1) {
            c = c3;
        }
        if (llabs(a - c3) == diff1 && c3 > c) {
            c = c3;
        }
    } else {
        k = a / b;
        c1 = k * b;
        diff1 = llabs(a - c1);
        c = c1;
        int64_t tmp = (int64_t) (k - 1) * b;
        if ((int32_t)tmp != tmp) {
            c2 = (k + 1) * b;
        } else {
            c2 = (k - 1) * b;
        }
        if (llabs(a - c2) < diff1) {
            diff1 = llabs(a - c2);
            c = c2;
        }
        if (llabs(a - c2) == diff1 && c2 > c) {
            c = c2;
        }
        if (a == INT32_MIN) {
            printf("%" PRId64 "\n", c);
            return 0;
        }
        c3 = 0;
        if (llabs(a - c3) < diff1) {
            c = c3;
        }
        if (llabs(a - c3) == diff1 && c3 > c) {
            c = c3;
        }
    }
    printf("%" PRId64 "\n", c);
    return 0;
}
