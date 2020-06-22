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

volatile bool sq = false;

void sig_usr1(int c) {
    sq = false;
}

void sig_usr2(int c) {
    sq = true;
}


int main() {
    signal(SIGUSR1, sig_usr1);
    signal(SIGUSR2, sig_usr2);
    printf("%d\n", getpid());
    fflush(stdout);
    int num;
    while (scanf("%d", &num) == 1) {
        if (sq) {
            printf("%d\n", num * num);
        } else {
            printf("%d\n", -num);
        }
        fflush(stdout);
    }
    return 0;
}
