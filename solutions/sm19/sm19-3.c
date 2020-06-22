#include <fcntl.h>
#include <inttypes.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

volatile sig_atomic_t exit_f = 0;
volatile sig_atomic_t flag1 = 0;
volatile sig_atomic_t count2 = 0;

void sig_term(int c) {
    exit_f = 1;
}

void sig_usr1(int c) {
    flag1 = 1;
}

void sig_usr2(int c) {
    ++count2;
}


int main() {
    signal(SIGTERM, sig_term);
    signal(SIGUSR1, sig_usr1);
    signal(SIGUSR2, sig_usr2);
    sigset_t mask_block, mask_unblock;
    sigemptyset(&mask_block);
    sigemptyset(&mask_unblock);
    sigaddset(&mask_block, SIGTERM);
    sigaddset(&mask_block, SIGUSR1);
    sigaddset(&mask_block, SIGUSR2);
    sigprocmask(SIG_BLOCK, &mask_block, NULL);
    int count1 = 0;
    printf("%d\n", getpid());
    fflush(stdout);
    while (1) {
        if (!exit_f && !flag1) {
            sigsuspend(&mask_unblock);
        }
        if (exit_f) {
            exit(0);
        }
        if (flag1) {
            printf("%d %d\n", count1++, count2);
            fflush(stdout);
            flag1 = 0;
        }
    }
    return 0;
}
