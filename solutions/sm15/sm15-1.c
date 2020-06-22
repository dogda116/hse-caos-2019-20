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

int main(int argc, char* argv[]) {
    int fd = open(argv[1], O_RDONLY);
    if (fd < 1) {
        // failed to open file
        exit(EXIT_FAILURE);
    }
    
    struct stat file_meta;
    if (fstat(fd, &file_meta) == -1) {
        // failed to stat
        exit(EXIT_FAILURE);
    }
    
    void *addr = mmap(NULL, file_meta.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (addr == MAP_FAILED) {
        // failed to mmap
        exit(EXIT_FAILURE);
    }
    const double* arr = addr;
    
    size_t n = file_meta.st_size / sizeof(*arr);
    double num_sum = 0;
    for (size_t i = 0; i != n; ++i) {
        num_sum += arr[i];
    }
    printf("%a\n", num_sum / n);
    
    munmap(addr, file_meta.st_size);
    close(fd);
    return 0;
}
