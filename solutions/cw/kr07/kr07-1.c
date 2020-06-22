#include <fcntl.h>
#include <inttypes.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, const char *argv[]) {
    int n = argc - 1;
    
    if (n < 1) {
        exit(0);
    }
    
    pid_t cpids[n + 1];
    
    cpids[0] = getpid();
    
    for (int i = 1; i != n + 1; ++i) {
        pid_t pid = fork();
        cpids[i] = pid;
        if (pid == -1) {
            /* failed to create a new process */
            exit(1);
        } else if (pid == 0) {
            int res = 0;
            int64_t input = strtoll(argv[i], NULL, 10);
            int digit;
            while (input != 0) {
                digit = input % 4;
                if (digit < 0) {
                    digit *= -1;
                }
                input /= 4;
                res += digit;
            }
            exit(res);
        }
    }
    
    for (int i = 1; i != n + 1; ++i) {
        int wstatus;
        waitpid(cpids[i], &wstatus, 0);
        printf("%d\n", WEXITSTATUS(wstatus));
    }
    return 0;
}
