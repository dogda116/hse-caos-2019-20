#include <ctype.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char* argv[]) {
    unsigned long long total_space = 0;
    
    uid_t user_id = getuid();
    
    DIR* dirp = opendir(argv[1]);
    
    if (dirp == NULL) {
        printf("%llu\n", total_space);
        return 0;
    }
    
    struct dirent* dir_entry;
    while ((dir_entry = readdir(dirp)) != NULL) {
        struct stat file_meta;
        char buffer[PATH_MAX];
        
        int wrtn = snprintf(buffer, PATH_MAX, "%s/%s", argv[1], dir_entry->d_name);
        if (wrtn < 0 || wrtn >= sizeof(buffer)) {
            exit(EXIT_FAILURE);
        }
        
        if (stat(buffer, &file_meta) == 0 && S_ISREG(file_meta.st_mode) 
            && isupper(dir_entry->d_name[0]) && user_id == file_meta.st_uid) {
            total_space += file_meta.st_size;
        }
    }
    closedir(dirp);
    
    printf("%llu\n", total_space);
    return 0;
}
