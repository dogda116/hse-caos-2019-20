#include <stdlib.h>
#include <stdio.h>

struct Pair
{
    int key;
    int value;
};


void my_mergesort(int l, int r, struct Pair *data) {
    if (l < r) {
        int m = (r + l) / 2;

        my_mergesort(l, m, data);
        my_mergesort(m + 1, r, data);

        int s1 = 1 + m - l;
        int s2 = r - m;

        struct Pair *first = calloc(s1, sizeof(struct Pair));
        struct Pair *second = calloc(s2, sizeof(struct Pair));

        for (int i = 0; i != s1; ++i) {
            first[i] = data[i + l];
        }

        for (int i = 0; i != s2; ++i) {
            second[i] = data[i + 1 + m];
        }

        int t = l, i = 0, j = 0;

        while (j < s2 && i < s1) {
            if (first[i].key <= second[j].key) {
                data[t] = first[i];
                ++i;
            } else {
                data[t] = second[j];
                ++j;
            }
            ++t;
        }

        while (i < s1) {
            data[t] = first[i];
            ++t;
            ++i;
        }

        while (j < s2) {
            data[t] = second[j];
            ++t;
            ++j;
        }

        free(first);
        free(second);
    }
}

void process(struct Pair *data, size_t size) {
    if (1 < size) {
        my_mergesort(0, size - 1, data);
    }
}
