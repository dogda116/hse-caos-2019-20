#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* thread_func(void* arg) {
    int num;
    if (scanf("%d", &num) != 1) {
        return NULL;
    }
    pthread_t t;
    pthread_create(&t, NULL, thread_func, NULL);
    pthread_join(t, NULL);
    printf("%d\n", num);
    return NULL;
}


int main(int argc, const char *argv[]) {
    pthread_t t;
    pthread_create(&t, NULL, thread_func, NULL);
    pthread_join(t, NULL);
    return 0;
}
