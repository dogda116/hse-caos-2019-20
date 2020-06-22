#include <limits.h>
#include <pthread.h>
#include <sched.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct Params
{
    size_t iterations;
    
    size_t first_acc;
    double first_transaction;
    
    size_t second_acc;
    double second_transaction;
    
    pthread_mutex_t * ms;
    double * accs;
};

void* thread_func(void* arg) {
    struct Params * p = (struct Params*)arg;
    for (size_t i = 0; i != p->iterations; ++i) {
        pthread_mutex_lock(&p->ms[p->first_acc]);
        pthread_mutex_lock(&p->ms[p->second_acc]);
        
        p->accs[p->first_acc] += p->first_transaction;
        p->accs[p->second_acc] += p->second_transaction;
        
        pthread_mutex_unlock(&p->ms[p->second_acc]);
        pthread_mutex_unlock(&p->ms[p->first_acc]);
    }
    
    return NULL;
}


int main(int argc, const char *argv[]) {
    size_t acc_count, thr_count;
    if (scanf("%zu%zu", &acc_count, &thr_count) != 2) {
        exit(EXIT_FAILURE);
    }
    struct Params thr_params[thr_count];
    double accounts[acc_count];
    pthread_t threads[thr_count];
    pthread_mutex_t mutexes[acc_count];
    for (size_t i = 0; i != acc_count; ++i) {
        accounts[i] = 0;
        pthread_mutex_init(&mutexes[i], NULL);
    }
    
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);
    
    for (size_t i = 0; i != thr_count; ++i) {
        if (scanf("%zu%zu%lf%zu%lf", 
                    &thr_params[i].iterations, 
                    &thr_params[i].first_acc, 
                    &thr_params[i].first_transaction,
                    &thr_params[i].second_acc,
                    &thr_params[i].second_transaction) != 5) {
            exit(EXIT_FAILURE);
        }
        thr_params[i].accs = accounts;
        thr_params[i].ms = mutexes;
        
        if (thr_params[i].first_acc > thr_params[i].second_acc) {
            // avoid deadlock (dinning philosophers problem)
            double tmp2 = thr_params[i].first_transaction;
            thr_params[i].first_transaction = thr_params[i].second_transaction;
            thr_params[i].second_transaction = tmp2;
            
            size_t tmp1 = thr_params[i].first_acc;
            thr_params[i].first_acc = thr_params[i].second_acc;
            thr_params[i].second_acc = tmp1;
        }
        
        pthread_create(&threads[i], &attr, thread_func, &thr_params[i]);
    }
    pthread_attr_destroy(&attr);
    
    for (size_t i = 0; i != thr_count; ++i) {
        pthread_join(threads[i], NULL);
    }
    
    for (size_t i = 0; i != acc_count; ++i) {
        printf("%.10g\n", accounts[i]);
    }    
    return 0;
}
