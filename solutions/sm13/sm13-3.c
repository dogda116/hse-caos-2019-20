#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
    time_t prev = 0;
    time_t curr = 0;
    struct tm time_info;
    FILE * fin = fopen(argv[1], "r");
    while (fscanf(fin, " %d/%d/%d %d:%d:%d ", 
                    &time_info.tm_year,
                    &time_info.tm_mon,
                    &time_info.tm_mday,
                    &time_info.tm_hour,
                    &time_info.tm_min,
                    &time_info.tm_sec
            ) == 6) {
        time_info.tm_isdst = -1;
        time_info.tm_year -= 1900;
        time_info.tm_mon -=1;
        
        curr = mktime(&time_info);
        
        if (prev != 0) {
            printf("%ld\n", curr - prev);
        }
        prev = curr;
    }
    fclose(fin);
}
