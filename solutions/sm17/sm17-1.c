#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, const char *argv[]) {
    pid_t pid;
    
    int input_fd = open(argv[2], O_RDONLY | O_CLOEXEC);
    if (input_fd == -1) {
        perror("can't open a file");
        exit(EXIT_FAILURE);
    }
    
    int output_fd = open(argv[3], O_WRONLY | O_CREAT | O_CLOEXEC | O_TRUNC, 0666);
    if (output_fd == -1) {
        perror("can't open a file");
        exit(EXIT_FAILURE);
    }
    
    if ((pid = fork()) == -1) {
        perror("can't create a process");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        close(STDIN_FILENO);
        dup2(input_fd, STDIN_FILENO);
        close(STDOUT_FILENO);
        dup2(output_fd, STDOUT_FILENO);
        
        execlp(argv[1], argv[1], NULL);
    } else if (pid > 0) {
        wait(NULL);
    }
    return 0;
}
