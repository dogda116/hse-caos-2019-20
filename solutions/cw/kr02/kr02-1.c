#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

int main(int argc, char *argv[]) {
    uint64_t ans = 0;
    if (argc == 1) {
        printf("%" PRIx64 "\n", ans);
        return 0;
    }
    char *p = strtok(argv[1], ",");
    while (p) {
        int i;
        if (sscanf(p, "%o", &i) == 1) {
            ans = ans | (1LLU << (i-1));
        }
        p = strtok(NULL, ",");
    }
    printf("%" PRIx64 "\n", ans);
}
