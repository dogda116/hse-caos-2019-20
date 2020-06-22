#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 1) {
        // failed to open file
        exit(EXIT_FAILURE);
    }
    int rows = strtol(argv[2], NULL, 10);
    int cols = strtol(argv[3], NULL, 10);
    size_t sz = rows * cols * sizeof(int);
    if (ftruncate(fd, sz) == -1) {
        // failed to truncate file;
        exit(EXIT_FAILURE);
    }

    void *addr = mmap(NULL, sz, PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED) {
        // failed to mmap
        exit(EXIT_FAILURE);
    }
    int (*matrix)[cols] = addr;
    
    int curr = 1;
    int row0 = 0, col0 = 0, rown = rows - 1, coln = cols - 1;
    while (rown - row0 >= 0 && coln - col0 >= 0) {
        for (int i = col0; i <= coln; ++i)
            matrix[row0][i] = curr++;
        for (int i = row0 + 1; i <= rown; ++i)
            matrix[i][coln] = curr++;
        if (row0 != rown) {
            for (int i = coln - 1; i >= col0; --i)
                matrix[rown][i] = curr++;
        }
        if (col0 != coln) {
            for (int i = rown - 1; i >= row0 + 1; --i)
                matrix[i][col0] = curr++;
        }
        ++row0, ++col0, --rown, --coln;
    }

    munmap(addr, sz);
    close(fd);
    return 0;
}
