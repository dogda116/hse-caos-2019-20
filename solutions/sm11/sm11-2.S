#include <asm/unistd_32.h>


int read(int fd, void *buf, int size) {
    int r;
    /* asm volatile(assembly code : inputs : outputs : clobbers); */
    asm volatile(
        "movl    %1, %%eax\n"
        "movl    %2, %%ebx\n"
        "movl    %3, %%ecx\n"
        "movl    %4, %%edx\n"
        "int     $0x80\n"
        "movl    %%eax, %0\n"
        :   "=g" (r)
        :   "g" (__NR_read), 
            "g" (fd),
            "g" (buf),
            "g" (size)
        : "%eax", "%ebx", "%ecx", "%edx", "memory"
    );
    return r;
}


int write(int fd, const void *buf, int size) {
    int r;
    /* asm volatile(assembly code : inputs : outputs : clobbers); */
    asm volatile(
        "movl    %1, %%eax\n"
        "movl    %2, %%ebx\n"
        "movl    %3, %%ecx\n"
        "movl    %4, %%edx\n"
        "int     $0x80\n"
        "movl    %%eax, %0\n"
        :   "=g" (r)
        :   "g" (__NR_write), 
            "g" (fd),
            "g" (buf),
            "g" (size)
        : "%eax", "%ebx", "%ecx", "%edx", "memory"
    );
    return r;
}


void my_exit(int return_code) {
    asm volatile(
        "movl    %0, %%eax\n"
        "movl    %1, %%ebx\n"
        "int     $0x80\n"
        :
        :   "g" (__NR_exit), 
            "g" (return_code)
        : "%eax", "%ebx"
    );
}


void _start() {
    char c;
    while(read(0, &c, 1) == 1) {
        if ('a' <= c && c <= 'z')
            c += 'A' - 'a';
        write(1, &c, 1);
    }
    my_exit(0);
}
