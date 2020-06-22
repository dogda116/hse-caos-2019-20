#include <inttypes.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/signalfd.h>
#include <sys/timerfd.h>
#include <sys/time.h>
#include <unistd.h>

volatile uint32_t last = 0;
volatile uint32_t counter = 0;

void sig_handler(int sig) {
    printf("%" PRIu32 "\n", last);
    fflush(stdout);
    if (++counter == 8) {
        exit(0);
    }
}

int is_prime(size_t num) {
    for (size_t j = 3; j * j < num; j += 2) {
        if (num % j == 0) {
            return 0;
        }
    }
    return 1;
}


int main() {
    signal(SIGVTALRM, sig_handler);
    uint32_t low, high;
    if (scanf("%" SCNu32 "%" SCNu32, &low, &high) != 2) {
        exit(EXIT_FAILURE);
    }
    
    struct itimerval to = {};
    to.it_interval.tv_usec = 100000; // every 10^5 microseconds = 0.1 sec 
    to.it_value.tv_usec = 100000; // first time in 0.1 sec 
    setitimer(ITIMER_VIRTUAL, &to, NULL);
    
    if (low <= 2) {
        last = 2;
        low = 3;
    }
    for (size_t i = low; i < high; ++i) {
        if (i % 2 == 0) {
            continue;
        }
        if (is_prime(i)) {
            last = i;
        }
    }
    printf("-1\n");
    fflush(stdout);
    return 0;
}
