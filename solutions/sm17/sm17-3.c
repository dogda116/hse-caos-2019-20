#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// (modify function mysys from previous task)
// returns 1 if finished successfully, 0 otherwise
int mysys(const char *str) {
    pid_t pid;
    if ((pid = fork()) == -1) {
        // interpret 0 as false, not as success return code
        return 0;
    } else if (pid == 0) {
        execlp(str, str, NULL);
        exit(0);
    }
    int wstatus;
    
    waitpid(pid, &wstatus, 0);
    if (WIFEXITED(wstatus)) {
        return !WEXITSTATUS(wstatus);
    } else {
        return 0;
    }
}


int main(int argc, const char *argv[]) {
    // returns 0 if finished successfully, 1 otherwise
    if (mysys(argv[1]) || mysys(argv[2])) {
        if (mysys(argv[3])) {
            return 0;
        } else {
            return 1;
        }
    } else {
        return 1;
    }
}
