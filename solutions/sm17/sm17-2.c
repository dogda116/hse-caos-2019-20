#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int mysys(const char *str) {
    pid_t pid;
    if ((pid = fork()) == -1) {
        return -1;
    } else if (pid == 0) {
        execlp("/bin/sh", "sh", "-c", str, NULL);
        _exit(127);
    }
    int wstatus;
    
    waitpid(pid, &wstatus, 0);
    if (WIFEXITED(wstatus)) {
        return WEXITSTATUS(wstatus);
    } else {
        return WTERMSIG(wstatus) + 128;
    }
}
