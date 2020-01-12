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
    int64_t x, b, res = 0;
    scanf("%" SCNd64 "%" SCNd64, &x, &b);
    while (x != 0) {
        res += x % b;
        x /= b;
    }
    if (res > 0) {
        printf("%" PRId64 "\n", res);
    } else {
        printf("%" PRId64 "\n", -res);
    }
    return 0;
}
