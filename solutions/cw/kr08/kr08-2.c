#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <limits.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/timerfd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
extern double balances[1024];
struct Transfer
{
    size_t from_index;
    size_t to_index;
    double amount;
};
void process(size_t count, const struct Transfer *data) {
    for (size_t i = 0; i != count; ++i) {
        pthread_mutex_lock(&m);
        balances[data->from_index] -= data->amount;
        balances[data->to_index] += data->amount;
        pthread_mutex_unlock(&m);
    }
}
