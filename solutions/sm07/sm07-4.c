#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <locale.h>
#include <wctype.h>
#include <wchar.h>
#include <malloc.h>

int next(void* rr);

void destroy(void* rr) {
    free(rr);
}

typedef struct RandomOperations
{
    int (*next)(void*);
    void (*destroy)(void*);
} Operation;

const Operation oper = (Operation) { &next, &destroy };

typedef struct RandomGenerator
{
    int seed;
    Operation *ops;
} RandomGenerator;

int next(void* rr) {
    RandomGenerator* rand_gen = rr;
    int next = (rand_gen->seed * 1103515245U + 12345) % (1U << 31);
    rand_gen->seed = next;
    return next;
}

RandomGenerator *random_create(int seed) {
    RandomGenerator *rr = malloc(sizeof(RandomGenerator));
    rr->ops = (Operation*)&oper;
    rr->seed = seed;
    return rr;
}
