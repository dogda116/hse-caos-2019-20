#include <inttypes.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/eventfd.h>
#include <sys/mman.h>
#include <sys/timerfd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

enum { MAXLEN = 4096 };

void play(char* shared, int fd1, int fd2, int child, int max, int k) {
    while (1) {
        unsigned long long counter;
        if (read(fd1, &counter, sizeof(counter)) < sizeof(counter)) {
            exit(EXIT_FAILURE);
        }
        if (counter > max) {
            exit(0);
        }
        printf("%d %s\n", child, shared);
        fflush(stdout);
        
        char* buf = shared;
        while (++(*buf) == '0' + k) {
            *buf = '0';
            ++buf;
        }
        if (*buf == 1) {
            *buf = '1';
            ++buf;
            *buf = 0;
        }
        ++counter;
        
        if (write(fd2, &counter, sizeof(counter)) < sizeof(counter)) {
            exit(EXIT_FAILURE);
        }
        if (counter > max) {
            exit(0);
        }
    }
}


int main(int argc, char* argv[]) {
    unsigned n;
    sscanf(argv[1], "%u", &n);
    if (n == 0) {
        printf("Done\n");
        fflush(stdout);
        return 0;
    }
    
    int k;
    sscanf(argv[2], "%d", &k);
    char * s = argv[3];
    
    int fd1 = eventfd(1, 0);
    int fd2 = eventfd(0, 0);
    
    char* buf = mmap(NULL, MAXLEN, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    strcpy(buf, s);
    
    pid_t pid1;
    if ((pid1 = fork()) == -1) {
        // failed to create a new process
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        play(buf, fd1, fd2, 1, n, k);
    }
    
    pid_t pid2;
    if ((pid2 = fork()) == -1) {
        // failed to create a new process
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        play(buf, fd2, fd1, 2, n, k);
    }
    
    close(fd1);
    close(fd2);
    wait(NULL);
    wait(NULL);
    printf("Done\n");
    fflush(stdout);
    return 0;
}
