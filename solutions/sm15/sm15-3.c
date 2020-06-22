#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <dirent.h>

int count_lines(const char* filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 1) {
        // failed to open file
        return -1;
    }
    
    struct stat file_meta;
    if (fstat(fd, &file_meta) == -1) {
        // failed to stat
        return -1;
    }
    int n = file_meta.st_size;
    if (n == 0) {
        return 0;
    }

    void *addr = mmap(NULL, n, PROT_READ, MAP_PRIVATE, fd, 0);
    if (addr == MAP_FAILED) {
        // failed to mmap
        return -1;
    }
    int count = 0;
    const char* data = addr;
    
    for (int i = 0; i < n; ++i)
        if (data[i] == '\n') ++count;
    if (data[n - 1] != '\n') ++count;

    munmap(addr, n);
    close(fd);
    return count;
}

int main(int argc, char* argv[]) {
    for (int i = 1; i != argc; ++i) {
        printf("%d\n", count_lines(argv[i]));
    }
    return 0;
}
