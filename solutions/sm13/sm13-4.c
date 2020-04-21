#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <stdlib.h>

const char *perms_to_str(char *buf, size_t size, int perms) {
    if (size == 0) return buf;
    else --size;
    char permissions[] = "---------";
    permissions[0] = (perms & S_IRUSR) ? 'r' : '-';
    permissions[1] = (perms & S_IWUSR) ? 'w' : '-';
    permissions[2] = (perms & S_IXUSR) ? 'x' : '-';
    permissions[3] = (perms & S_IRGRP) ? 'r' : '-';
    permissions[4] = (perms & S_IWGRP) ? 'w' : '-';
    permissions[5] = (perms & S_IXGRP) ? 'x' : '-';
    permissions[6] = (perms & S_IROTH) ? 'r' : '-';
    permissions[7] = (perms & S_IWOTH) ? 'w' : '-';
    permissions[8] = (perms & S_IXOTH) ? 'x' : '-';
    if ((perms & S_ISUID) && (perms & S_IXGRP))
        permissions[2] = 's';
    if ((perms & S_ISUID) && (perms & S_IXOTH))
        permissions[2] = 's';
    if ((perms & S_ISGID) && (perms & S_IXOTH))
        permissions[5] = 's';
    if ((perms & S_ISVTX) && (perms & S_IWOTH) && (perms & S_IXOTH))
        permissions[8] = 't';
    size_t k = (size < 9) ? size : 9;
    for (size_t i = 0; i != k; ++i)
        *(buf++) = permissions[i];
    *buf = '\0';
    return buf - k;
}
