#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile int is_ready;
volatile unsigned long long curr_prime;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

int is_prime(unsigned long long num) {
    if (num <= 1) return 0;
    for (unsigned long long i = 2; i * i <= num; ++i) {
        if (!(num % i)) {
            return 0;
        }
    }
    return 1;
}


void* thread_func(void* arg) {
    unsigned long long num = *(unsigned long long*)arg;
    while (1) {
        if (is_prime(num)) {
            pthread_mutex_lock(&m);
            is_ready = 1;
            curr_prime = num;
            pthread_cond_signal(&c);
            pthread_mutex_unlock(&m);
        }
        ++num;
    }
    return NULL;
}


int main(int argc, const char *argv[]) {
    unsigned long long base;
    int count;
    if (scanf("%llu%d", &base, &count) != 2) {
        exit(EXIT_FAILURE);
    }
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, &base);
    
    for (int i = 0; i != count; ++i) {
        unsigned long long prime;
        pthread_mutex_lock(&m);
        while (!is_ready) {
            pthread_cond_wait(&c, &m);
        }
        prime = curr_prime;
        is_ready = 0;
        pthread_mutex_unlock(&m);
        printf("%llu\n", prime);
    }
    return 0;
}
