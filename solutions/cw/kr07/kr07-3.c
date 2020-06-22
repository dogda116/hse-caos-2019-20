#include <fcntl.h>
#include <inttypes.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, const char *argv[]) {
    FILE* f1 = fopen(argv[1], "r");
    FILE* f2 = fopen(argv[2], "r");
    
    int p1[2], p2[2];
    if (pipe(p1) < 0 || pipe(p2) < 0) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }
    
    FILE* r1 = fdopen(p1[0], "r");
    FILE* w1 = fdopen(p2[1], "w");
    FILE* r2 = fdopen(p2[0], "r");
    FILE* w2 = fdopen(p1[1], "w");
    
    pid_t pid1, pid2;
    if ((pid1 = fork()) == -1) {
        /* failed to create a new process */
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        /* child1 */
        
        uint64_t res = 0;
        int32_t num;
        
        fclose(f2);
        fclose(r1);
        fclose(r2);
        fclose(w1);
        
        while (fscanf(f1, "%" SCNd32, &num) == 1) {
            res += num;
        }
        
        fclose(f1);
        
        int a = (int)res;
        fprintf(w2, "%d\n", a);
        fflush(w2);
        fclose(w2);
        exit(0);
    }
    
    if ((pid2 = fork()) == -1) {
        /* failed to create a new process */
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        /* child2 */
        uint64_t res = 0;
        int32_t num;
        
        fclose(f1);
        fclose(r1);
        fclose(r2);
        fclose(w2);
        
        while (fscanf(f2, "%" SCNd32, &num) == 1) {
            res += num;
        }
        
        fclose(f2);
        
        int a = (int)res;
        fprintf(w1, "%d\n", a);
        fflush(w1);
        fclose(w1);
        exit(0);
    }
    fclose(w1);
    fclose(w2);
    fclose(f2);
    fclose(f1);
    
    int res1, res2;
    
    waitpid(pid2, NULL, 0);
    fscanf(r2, "%d", &res2);
    fclose(r2);
    
    waitpid(pid1, NULL, 0);
    fscanf(r1, "%d", &res1);
    
    int64_t of = (int64_t)res2 + res1;
    int32_t ans = (int32_t)of;
    printf("%d %d %" PRId32 "\n", res2, res1, ans);
    return 0;
}
