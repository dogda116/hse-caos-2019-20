#include <fcntl.h>
#include <inttypes.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int counter = 0;

void handle_sig_int(int c) {
    if (counter < 4) {
        printf("%d\n", counter++);
        fflush(stdout);
    } else {
        exit(0);
    }
}


int main(int argc, const char *argv[]) {
    sigaction(SIGINT, &(struct sigaction){.sa_handler = handle_sig_int, .sa_flags = SA_RESTART}, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    while (1) {
        pause();
    }
    return 0;
}
