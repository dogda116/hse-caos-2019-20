#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum { THREADS_COUNT = 10 };

pthread_t threads[THREADS_COUNT];

void* thread_func(void* arg) {
    int id = (int)(intptr_t)arg;
    if (id != 0) {
        pthread_join(threads[id - 1], NULL);
    }
    printf("%d\n", id);
    return NULL;
}


int main(int argc, const char *argv[]) {
    for (int i = 0; i != THREADS_COUNT; ++i) {
        pthread_create(&threads[i], NULL, thread_func, (void*)(intptr_t)i);
    }
    pthread_join(threads[THREADS_COUNT - 1], NULL);
    return 0;
}
