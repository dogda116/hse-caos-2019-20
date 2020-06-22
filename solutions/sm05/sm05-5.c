#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


char *getline2(FILE *f) {
    size_t length = 0;
    size_t capacity = 1; // let capacity be a power of two (same as std::vector)
    char * line = calloc(capacity, sizeof(*line));
    if (line == NULL) return NULL;
    
    line[0] = '\0';
    
    char c;
    while (fscanf(f, "%c", &c) != EOF) {
        if (++length == capacity) {
            capacity <<= 1;
            char * reallocated = realloc(line, capacity * sizeof(*line));
            if (reallocated == NULL) {
                free(line);
                return NULL;
            }
            line = reallocated;
        }
        
        line[length - 1] = c;
        line[length] = '\0';
        if (c == '\n') {
            return line;
        }
    }
    if (length == 0) {
        free(line);
        return NULL;
    }
    return line;
}
