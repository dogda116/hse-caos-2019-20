#include <sys/eventfd.h>
#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int n;
int * threads_states;
pthread_t * threads;

void* thread_func(void* arg) {
    int thread_num = (int)(intptr_t)arg;
    
    while (1) {
        unsigned long long counter;
        if (read(threads_states[thread_num], &counter, sizeof(counter)) < sizeof(counter)) {
            exit(EXIT_FAILURE);
        }
        
        int num;
        if (scanf("%d", &num) == 1) {
            printf("%d %d\n", thread_num, num);
        } else {
            for (int i = 0; i != n; ++i) {
                // destroy all threads except itself
                if (i != thread_num) {
                    pthread_cancel(threads[i]);
                }
            }
            break;
        }
        
        int fwd = num % n;
        if (fwd < 0) {
            fwd += n;
        }
        
        ++counter;
        if (write(threads_states[fwd], &counter, sizeof(counter)) < sizeof(counter)) {
            exit(EXIT_FAILURE);
        }
    }
   
    return NULL;
}


int main(int argc, const char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    
    n = strtol(argv[1], NULL, 10);
    threads = (pthread_t *) calloc(n, sizeof(*threads));
    threads_states = (int *) calloc(n, sizeof(*threads_states));
    
    threads_states[0] = eventfd(1, 0);
    for (int i = 1; i != n; ++i) {
        threads_states[i] = eventfd(0, 0);
    }
    
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);
    
    for (int i = n-1; i != -1; --i) {
        pthread_create(&threads[i], &attr, thread_func, (void*)(intptr_t)i);
    }
    pthread_attr_destroy(&attr);
    
    for (int i = 0; i != n; ++i) {
        pthread_join(threads[i], NULL);
    }
    
    for (int i = 0; i != n; ++i) {
        close(threads_states[i]);
    }
    
    free(threads);
    free(threads_states);
    return 0;
}
