#include <dlfcn.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    void* handle;
    void* function;
    double input, output;
    
    if ((handle = dlopen("/lib/libm.so.6", RTLD_LAZY)) == NULL || 
        (function = dlsym(handle, argv[1])) == NULL) {
        return 69;
    } else {
        while (scanf("%lf", &input) == 1) {
            output = ((double (*)(double)) function)(input);
            printf("%.10g\n", output);
        }
    }
    dlclose(handle);
    return 0;
}
