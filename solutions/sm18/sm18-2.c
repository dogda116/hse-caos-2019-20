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
    
    pid_t child, grand_child;
    if ((child = fork()) == -1) {
        /* failed to create a new process */
        exit(EXIT_FAILURE);
    } else if (child == 0) {
        /* child */
        close(fd[1]);
        if ((grand_child = fork()) == -1) {
            /* failed to create a new process */
            exit(EXIT_FAILURE);
        } else if (grand_child == 0) {
            /* grand_child */
            int64_t sum = 0;
            int32_t num = 0;
            int r;
            while ((r = read(fd[0], &num, sizeof(num))) > 0) {
                if (r < sizeof(num)) {
                    // failed to read
                    exit(EXIT_FAILURE);
                } else {
                    sum += num;
                }
            }
            printf("%" PRId64 "\n", sum);
            exit(0);
        } else {
            close(fd[0]);
            /* wait for grand_child */
            wait(NULL);
            exit(0);
        }
    } else {
        /* parent */
        close(fd[0]);
        int32_t value;
        while (scanf("%" SCNd32, &value) == 1) {
            if (write(fd[1], &value, sizeof(value)) < sizeof(value)) {
                // failed to write
                exit(EXIT_FAILURE);
            }
        }
        close(fd[1]);
    }
    
    /* wait for all processes to finish */
    while (wait(NULL) > 0) {}
    return 0;
}
