#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <locale.h>
#include <wctype.h>
#include <wchar.h>
#include <malloc.h>

static int cmp(const void* elem1, const void* elem2, void* ar) {
    int e2 = *(int*)elem2;
    int e1 = *(int*)elem1;
    if (((int*)ar)[e1] == ((int*)ar)[e2]) {
        if (e1 >= e2) {
            return e1 != e2;
        } else {
            return -1;
        }
    } else if (((int*)ar)[e1] < ((int*)ar)[e2]) {
        return -1;
    } else {
        return 1;
    }
}

void process(size_t count, const int *data, int *order) {
    for (size_t i = 0; i != count; ++i) {
        order[i] = i;
    }
    qsort_r(order, count, sizeof(int), cmp, (void*)data);
}
