#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    uint64_t first = 0, second = 0, total = 0;
    char line[100000];
    while (fgets(line, 100000, stdin)) {
        sscanf(line, "%lx-%lx", &first, &second);
        total += second - first;
    }
    printf("%" PRIu64 "\n", total);
    return 0;
}
