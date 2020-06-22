#include <ctype.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h> 
#include <inttypes.h>
#include <stdint.h>
#include <unistd.h>

int my_cmp(const void* d1, const void* d2) {
    double a = *(double*)d1;
    double b = *(double*)d2;
    if (a < b) {
        return -1;
    } else if (a > b) {
        return 1;
    } else {
        return 0;
    }
}


int main(int argc, char* argv[]) {
    int fd = open(argv[1], O_RDONLY, S_IRUSR | S_IWUSR);
    if (fd < 1) {
        // failed to open file
        exit(EXIT_FAILURE);
    }
    
    struct stat file_meta;
    if (fstat(fd, &file_meta) == -1) {
        // failed to stat
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    void *addr = mmap(NULL, file_meta.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (addr == MAP_FAILED) {
        // failed to mmap
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    double* arr = addr;
    size_t n = file_meta.st_size / sizeof(*arr);
    
    if (n == 0) {
        printf("0");
        munmap(addr, file_meta.st_size);
        close(fd);
        return 0;
    }
    size_t t = n / 10;
    size_t m = n - 2 * t;
    size_t p = n - t;
    qsort(&arr[t], n - 2 * t, sizeof(double), my_cmp);
    
    
    size_t r = m / 10;
    
    double sum = 0;
    double cnt = 0;
    for (size_t i = t + r; i != p - r; ++i) {
        sum += arr[i];
        ++cnt;
    }
    munmap(addr, file_meta.st_size);
    close(fd);
    
    sum /= cnt;
    printf("%.10g\n", sum);
    return 0;
}
