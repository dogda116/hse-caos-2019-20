#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main() {
    int curr = 1;
    pid_t pid;
    pid_t child_pid;
    pid_t main_pid = getpid();
    
    while (scanf("%d", &curr) == 1) {
        if ((pid = fork()) == -1) {
            /* failed to create a new process */
            exit(1);
        } else if (pid == 0) {
            /* this piece of code is executed by child */
            /* descent further down */
            continue;
        } else if (pid > 0) {
            /* this piece of code is executed by parent */
            int wstatus;
            waitpid(pid, &wstatus, 0);
            if (WIFEXITED(wstatus) && (WEXITSTATUS(wstatus) == 0)) {
                printf("%d\n", curr);
                exit(0);
            } else {
                child_pid = getpid();
                if (child_pid == main_pid) {
                    /* then it is actually not a child,
                    we are back in main */
                    printf("-1\n");
                    exit(0);
                } else {
                    /* climbing up until returned back to main */
                    exit(1);
                }
            }            
        }
    }
    return 0;
}
