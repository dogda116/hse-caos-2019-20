#include <limits.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void* thread_func(void* arg) {
    long long * s = (long long *) arg;
    int num;
    while (scanf("%d", &num) == 1) {
        *s += (long long) num;
        sched_yield();
    }
    return NULL;
}


int main(int argc, const char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    
    int n = strtol(argv[1], NULL, 10);
    pthread_t * threads = (pthread_t *) calloc(n, sizeof(*threads));
    long long * sums = (long long *) calloc(n, sizeof(*sums));
    
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);
    pthread_attr_setguardsize(&attr, 0);
    
    for (int i = 0; i != n; ++i) {
        pthread_create(&threads[i], &attr, thread_func, &sums[i]);
    }
    pthread_attr_destroy(&attr);
    
    long long res = 0;
    for (int i = 0; i != n; ++i) {
        pthread_join(threads[i], NULL);
        res += sums[i];
    }
    
    free(threads);
    free(sums);
    printf("%lld\n", res);
    return 0;
}
