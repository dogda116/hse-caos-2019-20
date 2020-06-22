#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
    struct tm time_info;
    sscanf(argv[1], "%d", &time_info.tm_year);
    sscanf(argv[2], "%d", &time_info.tm_mon);
    time_info.tm_year -= 1900;
    time_info.tm_mon -= 1;
    time_info.tm_sec = 1;
    time_info.tm_min = 1;
    time_info.tm_hour = 1;
    int input_month = time_info.tm_mon;
    int work_hours = 0;
    for (int day = 1; day <= 31; ++day) {
        time_info.tm_mday = day;
        mktime(&time_info);
        if (time_info.tm_mon != input_month) {
            break;
        }
        if (time_info.tm_wday == 5) {
            work_hours += 6;
        }
        if (0 < time_info.tm_wday && time_info.tm_wday < 5) {
            work_hours += 8;
        }
    }
    printf("%d\n", work_hours);
    return 0;
}
