#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void process(FILE* a, FILE* b, FILE* c, FILE* d, int64_t num, int64_t n) {
    /* close other ends of pipes */
    fclose(a);
    fclose(b);
    
    int64_t input;
    while (fscanf(c, "%" SCNd64, &input) != EOF && input != n) {
        printf("%" PRId64 " %" PRId64 "\n", num, input);
        fprintf(d, "%" PRId64 "\n", ++input);
        fflush(stdout);
        fflush(d);
    }
    
    /* close pipes */
    fclose(c);
    fclose(d);
    
    exit(0);
}


int main(int argc, const char *argv[]) {
    int64_t n = strtoll(argv[1], NULL, 10);
    
    int p1[2], p2[2];
    if (pipe(p1) < 0 || pipe(p2) < 0) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }
    
    int64_t one = 1, two = 2;
    
    FILE* r1 = fdopen(p1[0], "r");
    FILE* w1 = fdopen(p2[1], "w");
    FILE* r2 = fdopen(p2[0], "r");
    FILE* w2 = fdopen(p1[1], "w");
    
    fprintf(w2, "%" PRId64 "\n", one);
    fflush(w2);
    
    pid_t pid1, pid2;
    if ((pid1 = fork()) == -1) {
        /* failed to create a new process */
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        /* child1 */        
        process(r2, w2, r1, w1, one, n);
    }
    
    if ((pid2 = fork()) == -1) {
        /* failed to create a new process */
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        /* child2 */
        process(r1, w1, r2, w2, two, n);
    }
    
    fclose(r1);
    fclose(w1);
    fclose(r2);
    fclose(w2);
    
    /* wait for all processes to finish */
    while (wait(NULL) > 0) {}
    
    printf("Done\n");
    fflush(stdout);
    return 0;
}
