#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#include <inttypes.h>
#include <stdint.h>
#include <stdbool.h>


int main(int argc, char* argv[]) {
    DIR* dirp = opendir(argv[1]);
    if (dirp == NULL) {
        return 42;
    }
    char* name_max = NULL;
    uint64_t max_allowed = strtoull(argv[2], NULL, 10);
    uint64_t current = 0;
    uint64_t size_max = 0;
    struct dirent* dir_entry;
    while ((dir_entry = readdir(dirp)) != NULL) {
        struct stat file_meta;
        char buffer[PATH_MAX + 1];
        
        if (!strcmp(dir_entry->d_name, ".") || !strcmp(dir_entry->d_name, "..")) {
            continue;
        }

        snprintf(buffer, PATH_MAX, "%s/%s", argv[1], dir_entry->d_name);
        
        if (lstat(buffer, &file_meta) == 0 && S_ISREG(file_meta.st_mode) && !S_ISLNK(file_meta.st_mode)) {
            uint64_t file_size = file_meta.st_size;
            current += file_size;
            if ((size_max == file_size && (name_max == NULL || strcmp(dir_entry->d_name, name_max) < 0))  
                || (file_size > size_max)) {
                    size_max = file_size;
                    name_max = dir_entry->d_name;
                }
        }
    }
    closedir(dirp);
    if (current > max_allowed) {
        printf("%s\n", name_max);
    }
    return 0;
}
