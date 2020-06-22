#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

enum { PROC_NUM = 3 };
enum { BUF_SIZE = 8 };


int main() {
    setbuf(stdin, NULL);
    for (int i = 1; i <= PROC_NUM; ++i) {
        if (!fork()) {
            int x;
            char buffer[BUF_SIZE];
            read(STDIN_FILENO, buffer, BUF_SIZE);
            sscanf(buffer, "%d", &x);
            printf("%d %d\n", i, x * x);
            return 0;
        }
    }
    /* wait for all processes to finish */
    while (wait(NULL) > 0) {}
    return 0;
}
