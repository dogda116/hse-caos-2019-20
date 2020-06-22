#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, const char *argv[]) {
    int n = argc - 1;
    
    if (n == 0)
        return 0;
    
    pid_t cpids[n + 1];
    cpids[0] = getpid();
    int fd[2];
    
    if (pipe(fd) < 0) {
        _exit(1);
    }
    
    pid_t pid1 = fork();
    cpids[1] = pid1;
    if (pid1 == -1) {
        /* failed to create a new process */
        close(fd[0]);
        close(fd[1]);
        _exit(1);
    } else if (pid1 == 0) {
        /* child1: cmd1 */
        if (n != 1)
            dup2(fd[1], STDOUT_FILENO);        
        close(fd[1]);
        close(fd[0]);
        execlp(argv[1], argv[1], NULL);
        /* if execlp failed: */
        _exit(1);
    }
    
    int prev_in_fd = fd[0];
    close(fd[1]);
     
    for (int i = 2; i != n + 1; ++i) {
        if (pipe(fd) < 0) {
            for (int j = 1; j != i; ++j) {
                kill(cpids[j], SIGKILL);
            }
            while (wait(NULL) > 0) {}
            _exit(1);
        }
        
        pid_t pid_i = fork();
        cpids[i] = pid_i;
        if (pid_i == -1) {
            /* failed to create a new process */
            for (int j = 1; j != i; ++j) {
                kill(cpids[j], SIGKILL);
            }
            while (wait(NULL) > 0) {}
            _exit(1);
        } else if (pid_i == 0) {
            /* child_i: cmd_i */
            close(fd[0]);
            if (i != n) {
                /* if it is not last cmd, write to pipe, not stdout */                
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
            }
            
            /* read from previous cmd, not stdin */
            dup2(prev_in_fd, STDIN_FILENO);
            close(prev_in_fd);
            
            execlp(argv[i], argv[i], NULL);
            /* if execlp failed: */
            _exit(1);
        }
        
        close(prev_in_fd);
        if (i == n) {
            close(fd[0]);
            close(fd[1]);
            break;
        } else {
            prev_in_fd = fd[0];
            close(fd[1]);            
        }
    }
    
    
    /* wait for all processes to finish */
    while (wait(NULL) > 0) {}
    return 0;
}
