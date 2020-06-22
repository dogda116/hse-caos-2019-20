/* частичное решение на 140 баллов (не работает для чисел >64 бит) */
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <limits.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/timerfd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, const char *argv[]) {   
    if (argc == 2) {
        printf("0");
        return 0;
    }
    
    uint64_t k = strtoull(argv[1], NULL, 10);
    uint64_t max_rem = 0;
    for (int i = 2; i < argc; ++i) {
        uint64_t num = strtoull(argv[i], NULL, 10);
        uint64_t rem = num % k;
        if (rem > max_rem) {
            max_rem = rem;
        }
    }
    printf("%" PRIu64 "\n", max_rem);
    return 0;
}
