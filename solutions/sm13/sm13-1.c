#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

int main() {
    time_t curr;
    time(&curr);
    int diff;
    while (scanf("%d", &diff) == 1) {
        time_t res;
        time_t tmp;
        if (__builtin_mul_overflow(24 * 60 * 60, diff, &tmp) || __builtin_add_overflow(tmp, curr, &res)) {
            printf("OVERFLOW\n");
        } else {
            struct tm * local_nt = localtime(&res);
            printf("%04d-%02d-%02d\n", local_nt->tm_year + 1900, local_nt->tm_mon + 1, local_nt->tm_mday);
        }
    }
}
