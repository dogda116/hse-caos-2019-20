#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main() {
    pid_t pid1, pid2;
    if ((pid1 = fork()) == 0) {
        /* this piece of code is executed by child */
        if ((pid2 = fork()) == 0) {
            /* this piece of code is executed by child of child */
            printf("3 ");
            return 0;
        } else if (pid2 > 0) {
            wait(NULL);
            printf("2 ");
            return 0;
        }
    } else if (pid1 > 0) {
        /* this piece of code is executed by parent */
        wait(NULL);
        printf("1\n");
    }
    return 0;
}
