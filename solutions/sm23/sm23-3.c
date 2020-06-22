#include <limits.h>
#include <pthread.h>
#include <sched.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum
{
    THREADS = 100,
    ELEMENTS = 1000
};

struct Item
{
    struct Item *next;
    long long value;
};

struct Item* _Atomic head;

void* thread_func(void* arg) {
    int num = (int)(intptr_t)arg;
    for (int i = 0; i != ELEMENTS; ++i) {
        struct Item* node = calloc(1, sizeof(*node));
        node->value = num * ELEMENTS + i;
        node->next = atomic_exchange_explicit(&head, node, memory_order_relaxed);
        sched_yield();
    }
    return NULL;
}


int main(int argc, const char *argv[]) {
    pthread_t threads[THREADS];
    
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);
    
    for (int i = 0; i != THREADS; ++i) {
        pthread_create(&threads[i], &attr, thread_func, (void*)(intptr_t)i);
    }
    pthread_attr_destroy(&attr);
    
    for (int i = 0; i!= THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
    
    while (head) {
        printf("%lld\n", head->value);
        struct Item* prev = head;
        head = head->next;
        free(prev);
    }
    return 0;
}
