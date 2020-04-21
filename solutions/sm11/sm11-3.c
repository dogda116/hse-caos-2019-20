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

struct FileReadState
{
    int fd;              // "файловый дескриптор", для чтения со стандартного потока ввода - 0
    unsigned char *buf;  // указатель на буфер
    int bufsize;         // размер буфера
    int lc;              // последний считанный символ
    // здесь потребуется добавить поля для реализации буферизованного чтения
    int eof;
    int curr_byte;
    int occupied_buffer;
};

// const int bsz = 4 * 1024;
unsigned char buffer[4 * 1024];

struct FileReadState frs = {
        0, buffer, 4 * 1024, -1, 0, 0, 0
};
struct FileReadState *stin = &frs;


int nextchar() {
    if (stin->eof == 1) return -1;
    
    if (stin->curr_byte == stin->occupied_buffer) {
        if (stin->occupied_buffer == stin->bufsize) {
            stin->occupied_buffer = 0;
            stin->curr_byte = 0;
        }
        int r = read(stin->fd, stin->buf + stin->occupied_buffer, stin->bufsize - stin->occupied_buffer);
        if (r <= 0) {
            stin->eof = 1;
            return -1;
        } else {
            stin->occupied_buffer += r;
        }
    }    
    
    stin->lc = stin->buf[stin->curr_byte];
    ++stin->curr_byte;
    
    return stin->lc;
}


int lastchar() {
    return stin->lc;
}
