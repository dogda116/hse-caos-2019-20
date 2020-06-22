#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum
{
    THREAD_NUM = 3,
    ITERATIONS = 1000000
};

volatile double arr[THREAD_NUM];
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void* thread_func(void* arg) {
    int t = (int)(intptr_t)arg;
    for (int i = 0; i != ITERATIONS; ++i) {
        pthread_mutex_lock(&m);
        arr[t] += (t + 1) * 100.;
        arr[(t + 1) % THREAD_NUM] -= (t + 1) * 100. + 1;
        pthread_mutex_unlock(&m);
    }
    return NULL;
}


int main(int argc, const char *argv[]) {
    pthread_t threads[THREAD_NUM];
    for (int i = 0; i != THREAD_NUM; ++i) {
        pthread_create(&threads[i], NULL, thread_func, (void*)(intptr_t)i);
    }
    for (int i = 0; i != THREAD_NUM; ++i) {
        pthread_join(threads[i], NULL);
    }
    for (int i = 0; i != THREAD_NUM; ++i) {
        printf("%.10g\n", arr[i]);
    }
    return 0;
}
