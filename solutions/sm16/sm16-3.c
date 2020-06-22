#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        printf("%d%c", i, " \n"[i == n]);
        fflush(stdout);
        if (i < n && fork() > 0) {
            wait(NULL);
            break;
        }
    }
    return 0;
}
