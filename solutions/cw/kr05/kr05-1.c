#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

int main(int argc, char* argv[]) {
    int f = open(argv[1], O_RDWR);
    if (f < 0)
        exit(1);
    struct stat file_meta;
    if (lstat(argv[1], &file_meta) < 0)
        exit(1);
    if (file_meta.st_size < 2 * sizeof(int))
        exit(1);
    char buf_right[sizeof(int)];
    char buf_left[sizeof(int)];
    if (read(f, buf_left, sizeof(int)) < sizeof(int))
        exit(1);
    if (lseek(f, file_meta.st_size - sizeof(int), SEEK_SET) < 0)
        exit(1);
    if (read(f, buf_right, sizeof(int)) < sizeof(int))
        exit(1);
    if (lseek(f, file_meta.st_size - sizeof(int), SEEK_SET) < 0)
        exit(1);
    if (write(f, buf_left, sizeof(int)) < sizeof(int))
        exit(1);
    if (lseek(f, 0, SEEK_SET) < 0)
        exit(1);
    if (write(f, buf_right, sizeof(int)) < sizeof(int))
        exit(1);
    int p = close(f);
    if (p < 0)
        exit(1);
    return 0;
}
