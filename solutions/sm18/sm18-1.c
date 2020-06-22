#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, const char *argv[]) {
    pid_t pid1, pid2;
    int fd[2];
    if (pipe(fd) < 0) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }
    
    if ((pid1 = fork()) == -1) {
        /* failed to create a new process */
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        /* child1: cmd1 */
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        execlp(argv[1], argv[1], NULL);
        /* if execlp failed: */
        perror("execlp failed");
        _exit(EXIT_FAILURE);
    }
    close(fd[1]);
    
    if ((pid2 = fork()) == -1) {
        /* failed to create a new process */
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        /* child2: cmd2 */
        dup2(fd[0], 0);
        close(fd[0]);
        execlp(argv[2], argv[2], NULL);
        /* if execlp failed: */
        perror("execlp failed");
        _exit(EXIT_FAILURE);
    }
    close(fd[0]);
    
    /* wait for all processes to finish */
    while (wait(NULL) > 0) {}
    return 0;
}
