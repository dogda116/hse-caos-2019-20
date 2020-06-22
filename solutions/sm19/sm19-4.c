#include <errno.h>
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

volatile sig_atomic_t sig_term = 0;
volatile sig_atomic_t fd_is_closed = 1;
volatile sig_atomic_t fd = 0;

void sig_handler(int sig) {
    if (sig == SIGTERM) {
        sig_term = 1;
        fd_is_closed = 0;
    } else if (SIGRTMIN <= sig && sig <= SIGRTMAX) {
        fd = sig - SIGRTMIN;
        fd_is_closed = 0;
    }
}


int main(int argc, const char *argv[]) {
    int n = argc - 1;
    
    int64_t sums[n];
    int fds[n];
    bool is_opened[n];
    
    /* set up handler for signals */
    struct sigaction sa;
    sa.sa_handler = sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGTERM, &sa, NULL);
    
    sigset_t mask_block, mask_unblock;
    sigemptyset(&mask_block);
    sigemptyset(&mask_unblock);
    sigaddset(&mask_block, SIGTERM);
    
    for (int i = 0; i != n; ++i) {
        fds[i] = open(argv[i+1], O_RDONLY, S_IRUSR);
        is_opened[i] = true;
        sums[i] = 0;
        
        sigaction(SIGRTMIN + i, &sa, NULL);
        sigaddset(&mask_block, SIGRTMIN + i);
    }
    
    sigprocmask(SIG_BLOCK, &mask_block, NULL);
    
    printf("%d\n", getpid());
    fflush(stdout);
    
    while (1) {
        /* wait for the first signal or wait for a new signal 
        if current file has already been closed */
        while (fd_is_closed) {
            sigsuspend(&mask_unblock);
        }
        
        /* output accumulated sums after SIGTERM */
        if (sig_term) {
            for (int i = 0; i != n; ++i) {
                printf("%" PRId64 "\n", sums[i]);
                fflush(stdout);
                if (is_opened[i]) {
                    close(fds[i]);
                }
            }
            _exit(0);
        }
        
        if (!is_opened[fd]) {
            fd_is_closed = 1;
            continue;
        }
        
        errno = 0;
        char buffer[16];
        
        sigprocmask(SIG_UNBLOCK, &mask_block, NULL);
        int r = read(fds[fd], buffer, 16);
        sigprocmask(SIG_BLOCK, &mask_block, NULL);
        
        /* got new signal during read call */
        if (errno == EINTR) {
            continue;
        }
        
        if (r == 16) {
            int64_t num;
            sscanf(buffer, "%" SCNd64, &num);
            sums[fd] += num;
        } else {
            /* end of file */
            close(fds[fd]);
            fd_is_closed = 1;
            is_opened[fd] = false;
        }
    }
    return 0;
}
