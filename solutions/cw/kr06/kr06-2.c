#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 


int main(int argc, char* argv[]) {
    void* handle;
    void* function;
    char* prev = argv[2];
    char* curr;
    int i = 2;
    float input = strtof(argv[1], NULL);
    float output = input;
    
    while (i + 1 < argc) {
        curr = argv[i];
        if (strlen(curr) == 1 && curr[0] == '-') {
            curr = prev;
        }
        
        if ((handle = dlopen(curr, RTLD_LAZY)) == NULL || 
            (function = dlsym(handle, argv[i+1])) == NULL) {
        } else {
            output = ((float (*)(float)) function)(output);
            prev = curr;
            dlclose(handle);
        }
        i += 2;
    }    
    printf("%.6g", output);
    return 0;
}
