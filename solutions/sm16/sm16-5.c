#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc < 6)
        exit(EXIT_FAILURE);
    
    int n = strtol(argv[1], NULL, 10);
    char* name = argv[2];
    int a_0 = strtol(argv[3], NULL, 10);
    int d = strtol(argv[4], NULL, 10);
    int k = strtol(argv[5], NULL, 10);
    
    mode_t f_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    int fd = open(name, O_RDWR | O_CREAT | O_TRUNC, f_mode);
    if (fd < 1) {
        // failed to open file
        exit(EXIT_FAILURE);
    }
    int c = close(fd);
    if (c == -1) {
        // failed to close file
        exit(EXIT_FAILURE);
    }
    
    pid_t pid;
    for (int i = 0; i != n; ++i) {
        if ((pid = fork()) == -1) {
            /* failed to create a new process */
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            /* this piece of code is executed by child */
            int f = open(name, O_RDWR, f_mode);
            if (f < 1) {
                // failed to open file
                exit(EXIT_FAILURE);
            }
            for (int j = 0; j != k; ++j) {
                int ind = i + j * n;
                if (lseek(f, ind * sizeof(int), SEEK_SET) < 0) {
                    // failed to change the postion
                    exit(EXIT_FAILURE);
                }
                int num = a_0 + ind * d;
                if (write(f, &num, sizeof(int)) < sizeof(int)) {
                    // failed to write
                    exit(EXIT_FAILURE);
                }
            }
            int cl = close(f);
            if (cl == -1) {
                // failed to close file
                exit(EXIT_FAILURE);
            }
            exit(0);
        }
    }
    
    /* wait for all processes to finish */
    while (wait(NULL) > 0) {}
    return 0;
}
