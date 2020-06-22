#include <inttypes.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/signalfd.h>
#include <sys/timerfd.h>
#include <sys/time.h>
#include <unistd.h>


int main() {
    int64_t sec, nsec, msec;
    if (scanf("%" SCNd64 "%" SCNd64, &sec, &nsec) != 2) {
        exit(EXIT_FAILURE);
    }
    
    sec *= 1000;
    sec += (nsec + 500000) / 1000000; // correct rounding
    msec = sec; // milliseconds
    
    struct timeval cur;
    gettimeofday(&cur, NULL);
    int64_t cur_msec = cur.tv_sec * 1000LL + (cur.tv_usec + 500) / 1000;

    if (cur_msec >= msec) {
        return 0;
    }
    msec -= cur_msec;
    
    int sfd;
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);
    if (sigprocmask(SIG_BLOCK, &mask, NULL) < 0) {
        exit(EXIT_FAILURE);
    }
    
    sfd = signalfd(-1, &mask, 0);
    if (sfd < 0) {
        exit(EXIT_FAILURE);
    }
    
    struct itimerval to = {};
    to.it_value.tv_sec = msec / 1000;
    to.it_value.tv_usec = (msec % 1000) * 1000;
    setitimer(ITIMER_REAL, &to, NULL);
    
    struct signalfd_siginfo si;
    if (read(sfd, &si, sizeof(si)) < sizeof(si)) {
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
