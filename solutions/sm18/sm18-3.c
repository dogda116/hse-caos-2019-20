#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, const char *argv[]) {
    int fd[2];
    if (pipe(fd) < 0) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }
    
    mode_t f_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    int out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, f_mode);
    
    /* data is written to fd[1] (or copies of it), 
    is read from fd[0] (or copies of it) */
    pid_t pid1, pid2, pid3;
    if ((pid3 = fork()) == -1) {
        /* failed to create a new process */
        exit(EXIT_FAILURE);
    } else if (pid3 == 0) {
        /* cmd3 */
        close(STDIN_FILENO);
        dup2(fd[0], STDIN_FILENO);
        close(STDOUT_FILENO);
        dup2(out, STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp(argv[3], argv[3], NULL);
        /* if execlp failed: */
        perror("execlp failed");
        _exit(EXIT_FAILURE);
    }
    close(fd[0]);
    
    if ((pid1 = fork()) == -1) {
        /* failed to create a new process */
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        /* cmd1 */
        close(STDOUT_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        execlp(argv[1], argv[1], NULL);
        /* if execlp failed: */
        perror("execlp failed");
        _exit(EXIT_FAILURE);
    }
    wait(NULL);
    
    if ((pid2 = fork()) == -1) {
        /* failed to create a new process */
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        /* cmd2 */
        close(STDOUT_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        execlp(argv[2], argv[2], NULL);
        /* if execlp failed: */
        perror("execlp failed");
        _exit(EXIT_FAILURE);
    }
    close(fd[1]);
    
    /* wait for all processes to finish */
    while (wait(NULL) > 0) {}
    return 0;
}
