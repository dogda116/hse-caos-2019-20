#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char* argv[]) {
    struct stat file_meta;
    long long total_space = 0;
    
    for (int i = 1; i < argc; ++i) {
        if (lstat(argv[i], &file_meta) == 0 && S_ISREG(file_meta.st_mode) && file_meta.st_nlink == 1) {
            total_space += file_meta.st_size;
        }
    }
    printf("%lld\n", total_space);
}
