#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>


int main(int argc, char* argv[]) {
    /* O_RDONLY Open for reading only. */
    int f = open(argv[1], O_RDWR);
    if (f < 1) {
        // failed to open the file
        exit(EXIT_FAILURE);
    }
    
    int64_t n = lseek(f, 0, SEEK_END) / sizeof(int64_t);
    if (n == 0) {
        return 0;
    }
    
    if (lseek(f, 0, SEEK_SET) < 0) {
        // failed to change the postion
        exit(EXIT_FAILURE);
    }
    int64_t min_val = 0;
    int64_t pos = 0;
    if (read(f, &min_val, sizeof(int64_t)) < sizeof(int64_t)) {
        // failed to read
        exit(EXIT_FAILURE);
    }
    int64_t curr;
    for (int64_t i = 1; i != n; ++i) {
        if (lseek(f, i * sizeof(int64_t), SEEK_SET) < 0) {
            // failed to change the postion
            exit(EXIT_FAILURE);
        }
        if (read(f, &curr, sizeof(int64_t)) < sizeof(int64_t)) {
            // failed to read
            exit(EXIT_FAILURE);
        }
        if (curr < min_val) {
            min_val = curr;
            pos = i;
        }
    }
    uint64_t tmp = (uint64_t) min_val;
    tmp *= -1;
    int64_t neg_min_val = (int64_t) tmp;
    if (lseek(f, pos * sizeof(int64_t), SEEK_SET) < 0) {
        // failed to change the postion
        exit(EXIT_FAILURE);
    }
    if (write(f, &neg_min_val, sizeof(int64_t)) < sizeof(int64_t)) {
        // failed to write
        exit(EXIT_FAILURE);
    }
    close(f);
    return 0;
}
