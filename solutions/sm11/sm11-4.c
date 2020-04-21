#include <asm/unistd_32.h>


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


struct FileWriteState
{
    int fd;              // "файловый дескриптор", для вывода на стандартный поток вывода - 1
    unsigned char *buf;  // указатель на буфер
    int bufsize;         // размер буфера
    // здесь потребуется добавить поля для реализации буферизованной записи
    int occupied_buffer;
    int error_occured;
};

static unsigned char buffer[4 * 1024];

struct FileWriteState fws = {
    1, buffer, 4 * 1024, 0, 0
};

struct FileWriteState *stout = &fws;

__attribute__((fastcall))
void flush(struct FileWriteState *out) {
    int w = write(out->fd, out->buf, out->occupied_buffer);
    if (w < 0) out->error_occured = 1;
}

__attribute__((fastcall))
void writechar(int c, struct FileWriteState *out) {
    if (out->occupied_buffer == out->bufsize) {
        flush(out);
        out->occupied_buffer = 0;
    }
    
    out->buf[out->occupied_buffer] = c;
    ++out->occupied_buffer;
}
