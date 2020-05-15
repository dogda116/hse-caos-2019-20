#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

void copy_file(int in_fd, int out_fd) {
    ssize_t r, t;
    char buffer[4096];
    /* 
    ssize_t read(int filedes, void *buf, size_t nbytes);
    returns the number of successfully read bytes 
    or 0 if reached the end of file 
    or -1 if an error occured
    */
    while ((r = read(in_fd, buffer, sizeof(buffer))) > 0) {
        ssize_t w = 0;
        /*
        ssize_t write(int filedes, const void *buf, size_t nbytes);
        returns the number of successfully written bytes
        or -1 if an error occured
        */
        while (w != r) {
            if ((t = write(out_fd, buffer + w, r - w)) == -1)
                exit(1);
            w += t;
        }
    }
}
